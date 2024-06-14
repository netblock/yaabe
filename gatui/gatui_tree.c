#include "gatui_private.h"

struct _GATUITree {
	GObject parent_instance;

	GWeakRef trunk;
	/*
	All branches, leaves depend on the root, the GATUITree, because it holds the
	bios memory and is responsible for freeing it. As a result the root must
	fall last; all branches, leaves must be destroyed befoe the trunk gets
	destroyed.
	If the tree has no trunk, it gets created.
	*/

	struct atom_tree* atomtree;
	GFile* biosfile;

	GtkSelectionModel** enum_models_cache; // only for tree building
};
G_DEFINE_TYPE(GATUITree, gatui_tree, G_TYPE_OBJECT)

static void
gatui_tree_dispose(
		GObject* const object
		) {
	GATUITree* const self = GATUI_TREE(object);

	GObject* trunk = g_weak_ref_get(&(self->trunk));
	g_assert(NULL == trunk);

	if (self->biosfile) {
		g_object_unref(self->biosfile);
		self->biosfile = NULL;
	}
}
static void
gatui_tree_finalize(
		GObject* const object
		) {
	GATUITree* const self = GATUI_TREE(object);
	atomtree_destroy(self->atomtree);
}
static void
gatui_tree_class_init(
		GATUITreeClass* const tree_class
		) {
	GObjectClass* const object_class = G_OBJECT_CLASS(tree_class);

	object_class->dispose = gatui_tree_dispose;
	object_class->finalize = gatui_tree_finalize;
}
static void
gatui_tree_init(
	GATUITree* const self
	) {
	g_weak_ref_init(&self->trunk, NULL);
	self->enum_models_cache = NULL;
}


static void
generate_enum_models_cache(
		GtkSelectionModel** const enum_models_cache
		) {
// a cache of selection-model'd simple-gobect of all atui_enum's and their
// entries.
// The purpose of this is to share and deduplicate enum generation
	static_assert(UINT8_MAX >= ATUI_ENUM_ARRAY_LENGTH);
	for (uint8_t set_i=0; set_i < ATUI_ENUM_ARRAY_LENGTH; set_i++) {
		struct atui_enum const* atuienum = &(ATUI_ENUM_ARRAY[set_i]);

		GListStore* list = g_list_store_new(G_TYPE_OBJECT);
		for (uint8_t entry_i=0; entry_i < atuienum->num_entries; entry_i++) {
			GObject* gobj_child = g_object_new(G_TYPE_OBJECT, NULL);
			g_object_set_data(gobj_child, "enum",
				(struct atui_enum_entry*)
				&(atuienum->enum_array[entry_i]) // de-const
			);
			g_list_store_append(list, gobj_child);
			g_object_unref(gobj_child);
		}

		GtkSingleSelection* enum_model = gtk_single_selection_new(
			G_LIST_MODEL(list)
		);
		gtk_single_selection_set_can_unselect(enum_model, true);
		gtk_single_selection_set_autoselect(enum_model, false);
		enum_models_cache[set_i] = GTK_SELECTION_MODEL(enum_model);
	}
}
static void
unref_enum_models_cache(
		GtkSelectionModel** const enum_models_cache
		) {
	static_assert(UINT8_MAX >= ATUI_ENUM_ARRAY_LENGTH);
	for (uint8_t set_i=0; set_i < ATUI_ENUM_ARRAY_LENGTH; set_i++) {
		g_clear_object(&(enum_models_cache[set_i]));
	}
}
static GObject*
gatui_tree_boot_gatui_trunk(
		GATUITree* const self
		) {
	g_return_val_if_fail(GATUI_IS_TREE(self), NULL);

	GObject* trunk = g_weak_ref_get(&(self->trunk));

	if (NULL == trunk) {
		GtkSelectionModel* enum_models_cache[ATUI_ENUM_ARRAY_LENGTH];
		self->enum_models_cache = enum_models_cache;
		generate_enum_models_cache(enum_models_cache);

		trunk = G_OBJECT(gatui_branch_new(self->atomtree->atui_root, self));

		self->enum_models_cache = NULL;
		unref_enum_models_cache(enum_models_cache);

		g_weak_ref_set(&(self->trunk), trunk);
	}

	return trunk;
}


static struct atom_tree*
atomtree_load_from_gfile(
		GFile* const biosfile,
		GError** const ferror_out
		) {
// Geneate the atom_tree and atui from a GIO File
	GError* ferror = NULL;
	void* bios = NULL;
	struct atom_tree* atree = NULL;


	GInputStream* const readstream = G_INPUT_STREAM(g_file_read(
		biosfile, NULL, &ferror
	));
	if (ferror) {
		goto exit1;
	}

	GFileInfo* const fi_size = g_file_query_info(biosfile,
		G_FILE_ATTRIBUTE_STANDARD_SIZE, G_FILE_QUERY_INFO_NONE, NULL, &ferror
	);
	if (ferror) {
		goto exit2;
	}

	size_t const filesize = g_file_info_get_size(fi_size);
	g_object_unref(fi_size);

	bios = malloc(filesize);
	g_input_stream_read(readstream, bios, filesize, NULL, &ferror);
	if (ferror) {
		goto exit3;
	}

	atree = atombios_parse(bios, filesize, true);
	if (atree == NULL) {
		goto exit3;
	}

	atree->biosfile_size = filesize;
	g_input_stream_close(readstream, NULL, &ferror);
	// TODO does close errors really matter?
	goto exit2;

	exit3:
	free(bios);

	exit2:
	g_object_unref(readstream);

	exit1:
	if (ferror_out) {
		*ferror_out = ferror;
	} else if (ferror) {
		g_error_free(ferror);
	}

	return atree;
}
GATUITree*
gatui_tree_new_from_gfile(
		GFile* const biosfile,
		GError** const ferror_out
		) {
	g_return_val_if_fail(G_IS_FILE(biosfile), NULL);

	g_object_ref(biosfile);

	GError* ferror = NULL;

	struct atom_tree* const atree = atomtree_load_from_gfile(
		biosfile, &ferror
	);
	if (ferror_out) {
		*ferror_out = ferror;
	} else if (ferror) {
		g_error_free(ferror);
	}
	if (NULL == atree) {
		g_object_unref(biosfile);
		return NULL;
	}

	GATUITree* const self = g_object_new(GATUI_TYPE_TREE, NULL);
	self->atomtree = atree;
	self->biosfile = biosfile;

	// it's possible to leak if we boot the trunk now
	//gatui_tree_boot_gatui_trunk(self);

	return self;
}
GATUITree*
gatui_tree_new_from_path(
		char8_t const* const path,
		GError** const ferror_out
		) {
	GFile* const biosfile = g_file_new_for_path(path);
	GATUITree* const tree = gatui_tree_new_from_gfile(biosfile, ferror_out);
	g_object_unref(biosfile);
	return tree;
}

static void
atomtree_save_to_gfile(
		struct atom_tree* const atree,
		GFile* const biosfile,
		GError** const ferror_out
		) {
	atomtree_bios_checksum(atree); // TODO emit change

	GError* ferror = NULL;

	GFileIOStream* biosfilestream = g_file_create_readwrite(
		biosfile, G_FILE_CREATE_PRIVATE, NULL, &ferror
	);
	if (ferror && (ferror->code == G_IO_ERROR_EXISTS)) {
		g_error_free(ferror);
		ferror = NULL;
		biosfilestream = g_file_open_readwrite(
			biosfile, NULL, &ferror
		);
	}
	if (ferror) {
		goto ferr0;
	}

	GIOStream* const biosstream = G_IO_STREAM(biosfilestream);
	GOutputStream* const writestream = g_io_stream_get_output_stream(
		biosstream
	);

	g_output_stream_write_all(
		writestream,  atree->alloced_bios,
		atree->biosfile_size,  NULL,NULL,  &ferror
	);
	if (ferror) {
		goto ferr1;
	}

	g_output_stream_close(writestream, NULL, &ferror);
	if (ferror) {
		goto ferr1;
	}
	g_io_stream_close(biosstream, NULL, &ferror);
	if (ferror) {
		goto ferr1;
	}

	ferr1:
	g_object_unref(biosstream);

	ferr0:
	if (ferror_out) {
		*ferror_out = ferror;
	} else {
		g_error_free(ferror);
	}

	return;
}
void
gatui_tree_save(
		GATUITree* const self,
		GError** const ferror_out
		) {
	g_return_if_fail(GATUI_IS_TREE(self));
	atomtree_save_to_gfile(self->atomtree, self->biosfile, ferror_out);
}
void
gatui_tree_saveas(
		GATUITree* const self,
		GFile* const biosfile,
		GError** const ferror_out
		) {
	g_return_if_fail(GATUI_IS_TREE(self));
	GError* ferror = NULL;
	atomtree_save_to_gfile(self->atomtree, biosfile, &ferror);
	if (NULL == ferror) {
		g_object_unref(self->biosfile);
		self->biosfile = biosfile;
	} else if (ferror_out) {
		*ferror_out = ferror;
	} else {
		g_error_free(ferror);
	}
}

GFile*
gatui_tree_get_bios_file(
		GATUITree* const self
		) {
	 g_return_val_if_fail(GATUI_IS_TREE(self), NULL);
	 return self->biosfile;
}


GtkSelectionModel* const*
gatui_tree_get_enum_models_cache(
		GATUITree* const self
		) {
	 g_return_val_if_fail(GATUI_IS_TREE(self), NULL);
	 return (GtkSelectionModel* const*) self->enum_models_cache;
};

GATUIBranch*
gatui_tree_get_trunk(
		GATUITree* const self
		) {
	 g_return_val_if_fail(GATUI_IS_TREE(self), NULL);

	GObject* trunk;

	// g_weak_ref_get refs for us
	trunk = g_weak_ref_get(&(self->trunk));
	if (NULL == trunk) {
		trunk = gatui_tree_boot_gatui_trunk(self);
	}

	return GATUI_BRANCH(trunk);
}


struct atom_tree*
gatui_tree_get_atom_tree(
		GATUITree* const self
		) {
	 g_return_val_if_fail(GATUI_IS_TREE(self), NULL);
	 return self->atomtree;
}
