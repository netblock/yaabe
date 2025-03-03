#include "standard.h"
#include "atomtree.h"
#include "atui.h"
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
	atui_destroy_tree(self->atomtree->atui_root);
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

	GtkSelectionModel* enum_models_cache[ATUI_ENUM_ARRAY_LENGTH];
	self->enum_models_cache = enum_models_cache;
	generate_enum_models_cache(enum_models_cache);

	GObject* const trunk = G_OBJECT(gatui_branch_new(
		self->atomtree->atui_root, self
	));

	self->enum_models_cache = NULL;
	unref_enum_models_cache(enum_models_cache);

	g_weak_ref_set(&(self->trunk), trunk);

	return trunk;
}


GATUITree*
gatui_tree_new_from_gfile(
		GFile* const biosfile,
		GError** const ferror_out
		) {
	g_return_val_if_fail(G_IS_FILE(biosfile), NULL);

	g_object_ref(biosfile);

	char* bios;
	size_t filesize;
	bool const success = g_file_load_contents(
		biosfile,
		NULL,
		&bios, &filesize,
		NULL, ferror_out
	);
	if (!success) {
		goto bios_read_err;
	}

	struct atom_tree* const atree = atombios_parse(bios, filesize);
	if (NULL == atree) {
		goto bios_parse_err;
	}
	atree->atui_root = generate_atui(atree);

	GATUITree* const self = g_object_new(GATUI_TYPE_TREE, NULL);
	self->atomtree = atree;
	self->biosfile = biosfile;

	// it's possible to leak if we boot the trunk now
	//gatui_tree_boot_gatui_trunk(self);

	return self;

	bios_parse_err:
	free(bios);
	bios_read_err:
	g_object_unref(biosfile);
	return NULL;
}
GATUITree*
gatui_tree_new_from_path(
		char const* const path,
		GError** const ferror_out
		) {
	GFile* const biosfile = g_file_new_for_path(path);
	GATUITree* const tree = gatui_tree_new_from_gfile(biosfile, ferror_out);
	g_object_unref(biosfile);
	return tree;
}

void
gatui_tree_save(
		GATUITree* const self,
		GError** const ferror_out
		) {
	g_return_if_fail(GATUI_IS_TREE(self));

	atomtree_calculate_checksums(self->atomtree);
	g_file_replace_contents(
		self->biosfile,
		self->atomtree->alloced_bios, self->atomtree->biosfile_size,
		NULL, false, G_FILE_CREATE_NONE, NULL, NULL, ferror_out
	);
}
void
gatui_tree_saveas(
		GATUITree* const self,
		GFile* const biosfile,
		GError** const ferror_out
		) {
	g_return_if_fail(GATUI_IS_TREE(self));

	atomtree_calculate_checksums(self->atomtree);
	bool const success = g_file_replace_contents(
		biosfile,
		self->atomtree->alloced_bios, self->atomtree->biosfile_size,
		NULL, false, G_FILE_CREATE_NONE, NULL, NULL, ferror_out
	);
	if (success) {
		g_object_unref(self->biosfile);
		self->biosfile = biosfile;
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


GtkSelectionModel*
gatui_tree_create_trunk_model(
		GATUITree* const self
		) {
// Generate the very first model, of the tippy top of the tree
	GATUIBranch* const trunk = gatui_tree_get_trunk(self);
	GListStore* const base_model = g_list_store_new(GATUI_TYPE_BRANCH);
	g_list_store_append(base_model, trunk);
	g_object_unref(trunk);

	// TreeList, along with branches_treelist_generate_children, creates our
	// collapsable model.
	GtkTreeListModel* tree_model = gtk_tree_list_model_new(
		G_LIST_MODEL(base_model),  false, false,
		branches_treelist_generate_children,  NULL,NULL
	);
	GtkSelectionModel* const trunk_model = GTK_SELECTION_MODEL(
		gtk_single_selection_new(G_LIST_MODEL(tree_model
		))
	); // the later models take ownership of the earlier

	/* TODO
	For some reason the GtkTreeListRow's notify breaks in a weird way if the
	gtk_tree_list_row_set_expanded is done before gtk_column_view_set_model.
	Doing it after fixes most issues, but not all of them. Furthermore, putting 
	a notify connect in the ColumnView bind not only all-1 connects, but
	reliably works.
	It seems like the rows get stolen/copied?
	*/
	GtkTreeListRow* const root_row = GTK_TREE_LIST_ROW(
		g_list_model_get_item(G_LIST_MODEL(trunk_model), 0)
	);
	g_signal_connect(root_row,
		"notify::expanded", G_CALLBACK(branches_track_expand_state), NULL
	);
	gtk_tree_list_row_set_expanded(root_row, true);
	g_object_unref(root_row);

	return GTK_SELECTION_MODEL(trunk_model);
}

GATUITree*
gatui_tree_copy_core(
		GATUITree* const src
		) {
	g_return_val_if_fail(GATUI_IS_TREE(src), NULL);

	size_t const biosfile_size = src->atomtree->biosfile_size;
	void* const alloced_bios = cralloc(biosfile_size);
	memcpy(alloced_bios, src->atomtree->alloced_bios, biosfile_size);

	struct atom_tree* const atree = atombios_parse(alloced_bios, biosfile_size);
	if (NULL == atree) {
		free(alloced_bios);
		return NULL;
	}
	atree->atui_root = generate_atui(atree);

	GATUITree* const self = g_object_new(GATUI_TYPE_TREE, NULL);
	self->atomtree = atree;
	self->biosfile = src->biosfile;
	g_object_ref(self->biosfile);

	return self;
}


struct atom_tree*
gatui_tree_get_atom_tree(
		GATUITree* const self
		) {
	g_return_val_if_fail(GATUI_IS_TREE(self), NULL);
	return self->atomtree;
}
