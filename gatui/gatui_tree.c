#include "standard.h"
#include "gatui_private.h"
#include "atomtree.h"

struct _GATUITree {
	GObject parent_instance;

	GWeakRef trunk;
	GWeakRef trunk_model;
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
	GVariantType* contiguous_type; // type string of "ay"
};
G_DEFINE_TYPE(GATUITree, gatui_tree, G_TYPE_OBJECT)


static void
gatui_tree_dispose(
		GObject* const object
		) {
	GATUITree* const self = GATUI_TREE(object);

	GObject* trunk = g_weak_ref_get(&(self->trunk));
	g_assert(NULL == trunk);
	GObject* trunk_model = g_weak_ref_get(&(self->trunk_model));
	g_assert(NULL == trunk_model);

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

	free(self->contiguous_type);

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
	g_weak_ref_init(&self->trunk_model, NULL);

	self->contiguous_type = g_variant_type_new("ay");
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
GtkSelectionModel* const*
gatui_tree_get_enum_models_cache(
		GATUITree* const self
		) {
	g_return_val_if_fail(GATUI_IS_TREE(self), NULL);
	return (GtkSelectionModel* const*) self->enum_models_cache;
};

GVariantType const*
gatui_tree_get_contiguous_type(
		GATUITree* const self
		) {
	g_return_val_if_fail(GATUI_IS_TREE(self), NULL);
	return self->contiguous_type;
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

GATUIBranch*
gatui_tree_get_trunk(
		GATUITree* const self
		) {
	g_return_val_if_fail(GATUI_IS_TREE(self), NULL);

	// g_weak_ref_get refs for us
	GObject* trunk = g_weak_ref_get(&(self->trunk));
	if (NULL == trunk) { // boot the trunk
		GtkSelectionModel* enum_models_cache[ATUI_ENUM_ARRAY_LENGTH];
		self->enum_models_cache = enum_models_cache;
		generate_enum_models_cache(enum_models_cache);

		trunk = G_OBJECT(gatui_branch_new(
			self->atomtree->atui_root, self
		));
		g_weak_ref_set(&(self->trunk), trunk);

		self->enum_models_cache = NULL;
		unref_enum_models_cache(enum_models_cache);
	}

	return GATUI_BRANCH(trunk);
}

GtkSelectionModel*
gatui_tree_create_trunk_model(
		GATUITree* const self
		) {
	g_return_val_if_fail(GATUI_IS_TREE(self), NULL);

	// g_weak_ref_get refs for us
	GtkSelectionModel* trunk_model = g_weak_ref_get(&(self->trunk_model));
	if (NULL == trunk_model) { // boot the model
		// Generate the very first model, of the tippy top of the tree
		GATUIBranch* const trunk = gatui_tree_get_trunk(self);
		GListStore* const base_model = g_list_store_new(GATUI_TYPE_BRANCH);
		g_list_store_append(base_model, trunk);
		g_object_unref(trunk);

		// TreeList, along with branches_treelist_generate_children, creates our
		// collapsable model.
		trunk_model = GTK_SELECTION_MODEL(
			gtk_single_selection_new(G_LIST_MODEL(
				gtk_tree_list_model_new(
					G_LIST_MODEL(base_model),  false, false,
					branches_treelist_generate_children,  NULL,NULL
				)
			))
		); // the later models take ownership of the earlier
		g_weak_ref_set(&(self->trunk_model), trunk_model);

		/* TODO
		For some reason the GtkTreeListRow's notify breaks in a weird way if the
		gtk_tree_list_row_set_expanded is done before gtk_column_view_set_model.
		Doing it after fixes most issues, but not all of them. Furthermore,
		putting a notify connect in the ColumnView bind not only all-1 connects,
		but reliably works.
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
	}

	return trunk_model;
}



static int16_t
expand_model_with_object_path(
		GListModel* const model,
		struct atui_path_vector const* const vector
		) {
	GATUINode const* path[ATUI_STACK_DEPTH];

	assert(vector->depth);
	uint8_t depth_i = vector->depth;

	atui_node const* node = vector->node;
	do {
		depth_i--;
		path[depth_i] = node->self;
		node = node->parent;
	} while (depth_i);

	int16_t model_i = 0;
	do {
		GtkTreeListRow* tree_item;
		GATUINode* questioned;
		goto question_loop_entry;
		do {
			model_i++;
			g_object_unref(tree_item);
			question_loop_entry:

			tree_item = GTK_TREE_LIST_ROW(
				g_list_model_get_object(model, model_i)
			);
			questioned = GATUI_NODE(gtk_tree_list_row_get_item(tree_item));
			g_object_unref(questioned); // we don't need a 2nd reference
		} while (path[depth_i] != questioned);
		gtk_tree_list_row_set_expanded(tree_item, true); // may be collapsed
		g_object_unref(tree_item);
		depth_i++;
	} while (depth_i < vector->depth);

	return model_i;
};
static void
select_in_model_by_map(
		struct atui_path_goto const* const map,
		GListModel* const trunk_model,
		int16_t* const branch_index,
		int16_t* const leaf_index
		) {
	assert(NULL == map->not_found);
	assert(map->branch.depth);

	// branches
	int16_t model_i;
	model_i = expand_model_with_object_path(trunk_model, &(map->branch));
	gtk_single_selection_set_selected(
		GTK_SINGLE_SELECTION(trunk_model),
		model_i
	);
	if (branch_index) {
		*branch_index = model_i;
	}

	model_i = -1;
	if (map->leaf.depth) {
		model_i = expand_model_with_object_path(
			G_LIST_MODEL(gatui_branch_get_leaves_model(
				GATUI_BRANCH(map->branch.node->self)
			)),
			&(map->leaf)
		);
	}
	if (leaf_index) {
		*leaf_index = model_i;
	}
}

bool
gatui_tree_select_in_model_by_path(
		GATUITree* const self,
		char const* const path,
		int16_t* const branch_index,
		int16_t* const leaf_index,
		struct atui_path_goto** const map_error
		) {
	g_return_val_if_fail(GATUI_IS_TREE(self), false);

	if (NULL == path) {
		return false;
	}
	// g_weak_ref_get refs for us
	GtkSelectionModel* trunk_model = g_weak_ref_get(&(self->trunk_model));
	if (NULL == trunk_model) {
		return false;
	}
	struct atui_path_goto* const map = path_to_atui(
		self->atomtree->atui_root, path
	);
	if (map->not_found) {
		if (map_error) {
			*map_error = map;
		} else {
			free(map);
		}
		g_object_unref(trunk_model);
		return false;
	}

	select_in_model_by_map(
		map, G_LIST_MODEL(trunk_model),
		branch_index, leaf_index
	);

	free(map);
	g_object_unref(trunk_model);

	return true;
}
bool
gatui_tree_select_in_model_by_object(
		GATUITree* const self,
		GATUINode* const target,
		int16_t* const branch_index,
		int16_t* const leaf_index
		) {
	g_return_val_if_fail(GATUI_IS_TREE(self), false);
	g_return_val_if_fail(gatui_node_get_root(target) == self, false);

	struct atui_path_goto map = {};
	atui_node* parent = _gatui_node_get_atui(target);
	if (parent->is_leaf) {
		map.leaf.node = parent;
		do {
			parent = parent->parent;
			map.leaf.depth++;
		} while (parent->is_leaf);
	}
	map.branch.node = parent;
	do {
		parent = parent->parent;
		map.branch.depth++;
	} while (parent);

	// g_weak_ref_get refs for us
	GtkSelectionModel* trunk_model = g_weak_ref_get(&(self->trunk_model));
	if (NULL == trunk_model) {
		return false;
	}
	select_in_model_by_map(
		&map, G_LIST_MODEL(trunk_model),
		branch_index, leaf_index
	);

	g_object_unref(trunk_model);

	return true;
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

void const*
gatui_tree_get_bios_pointer(
		GATUITree* const self,
		size_t* const size
		) {
	g_return_val_if_fail(GATUI_IS_TREE(self), NULL);

	if (size) {
		*size = self->atomtree->biosfile_size;
	}

	return self->atomtree->bios;
}


GtkSelectionModel*
gatui_tree_regex_search(
		GATUITree* const self,
		GRegex* const pattern,
		struct gatui_search_flags const* const flags
		) {
	GATUIBranch* const root = gatui_tree_get_trunk(self);
	GListStore* const base_model = g_list_store_new(GATUI_TYPE_REGEX_NODE);
	gatui_regex_search_recurse_branch(root, base_model, pattern, flags);
	g_object_unref(root);


	GtkSingleSelection* const single_model = gtk_single_selection_new(
		G_LIST_MODEL(base_model)
	);
	gtk_single_selection_set_can_unselect(single_model, true);
	gtk_single_selection_set_autoselect(single_model, false);
	gtk_single_selection_set_selected(
		single_model, GTK_INVALID_LIST_POSITION
	);
	g_signal_connect(GTK_SELECTION_MODEL(single_model), "selection-changed",
		G_CALLBACK(gtk_selection_model_unselect_item), NULL
	);

	return GTK_SELECTION_MODEL(single_model);
}
