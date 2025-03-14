#include "standard.h"
#include "gatui_private.h"

enum {
	VALUE_CHANGED,
	LAST_SIGNAL
};
static guint gatui_signals[LAST_SIGNAL] = {0};

struct _GATUIBranch {
	GObject parent_instance;

	GATUITree* root;

	atui_branch* atui;
	GATUIBranch** child_branches;
	GtkSelectionModel* leaves_model; // noselection of a treelist

	GVariantType* capsule_type;
};
G_DEFINE_TYPE(GATUIBranch, gatui_branch, G_TYPE_OBJECT)


static void
gatui_branch_dispose(
		GObject* const object
		) {
	GATUIBranch* const self = GATUI_BRANCH(object);

	if (self->child_branches) {
		GATUIBranch** const child_branches = self->child_branches;
		self->child_branches = NULL;
		uint16_t const num_branches = self->atui->num_branches;
		for (uint16_t i = 0; i < num_branches; i++) {
			g_object_unref(child_branches[i]);
		}
		free(child_branches);
	}
	if (self->leaves_model) {
		g_object_unref(self->leaves_model);
		self->leaves_model = NULL;
	}
	self->atui->self = NULL; // weak reference

	if (self->capsule_type) {
		g_free(self->capsule_type);
		self->capsule_type = NULL;
	}

	if (self->root) {
		g_object_unref(self->root);
		self->root = NULL;
	}

	G_OBJECT_CLASS(gatui_branch_parent_class)->dispose(object);
}

static void
gatui_branch_class_init(
		GATUIBranchClass* const branch_class
		) {
	GObjectClass* const object_class = G_OBJECT_CLASS(branch_class);

	object_class->dispose = gatui_branch_dispose;

	gatui_signals[VALUE_CHANGED] = g_signal_new(
		"value-changed",
		G_TYPE_FROM_CLASS(branch_class),
		(G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE),
		0,
		NULL, NULL,
		NULL,
		G_TYPE_NONE, 0
	);
}
static void
gatui_branch_init(
		GATUIBranch* const self
		) {
	self->child_branches = NULL;
	self->leaves_model = NULL;
}

GATUIBranch*
gatui_branch_new(
		atui_branch* const branch,
		GATUITree* const root
		) {
	assert(branch);
	assert(NULL == branch->self);
	g_return_val_if_fail(branch != NULL, NULL);
	g_return_val_if_fail(branch->self == NULL, NULL);

	GATUIBranch* const self = g_object_new(GATUI_TYPE_BRANCH, NULL);
	self->atui = branch;
	branch->self = self;

	g_object_ref(root);
	self->root = root;

	uint16_t const num_branches = branch->num_branches;
	if (num_branches) {
		self->child_branches = cralloc(num_branches * sizeof(GATUIBranch*));

		for (uint16_t i = 0; i < num_branches; i++) {
			assert(branch->child_branches[i]);
			self->child_branches[i] = gatui_branch_new(
				branch->child_branches[i], root
			);
			assert(self->child_branches[i]);
		}
	}

	if (branch->leaf_count) { // generate leaves_model
		GListStore* const leaf_list = g_list_store_new(GATUI_TYPE_LEAF);

		for (uint16_t i=0; i < branch->leaf_count; i++) {
			GATUILeaf* leaf = gatui_leaf_new(&(branch->leaves[i]), root);
			g_list_store_append(leaf_list, leaf);
			g_signal_connect_swapped(self, "value-changed",
				G_CALLBACK(gatui_leaf_emit_val_changed), leaf
			);
			g_object_unref(leaf);
		}

		GtkSingleSelection* const single_model = gtk_single_selection_new(
			G_LIST_MODEL(gtk_tree_list_model_new(
				G_LIST_MODEL(leaf_list),  false, true,
				leaves_treelist_generate_children, NULL,NULL
			))
		); // the later models take ownership of the earlier
		gtk_single_selection_set_can_unselect(single_model, true);
		gtk_single_selection_set_autoselect(single_model, false);
		gtk_single_selection_set_selected(
			single_model, GTK_INVALID_LIST_POSITION
		);
		g_signal_connect(GTK_SELECTION_MODEL(single_model), "selection-changed",
			G_CALLBACK(gtk_selection_model_unselect_item), NULL
		);
		self->leaves_model = GTK_SELECTION_MODEL(single_model);
	}

	self->capsule_type = g_variant_type_new("ay");

	return self;
}


GtkSelectionModel*
gatui_branch_get_leaves_model(
		GATUIBranch* const self
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), NULL);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), NULL);
	return self->leaves_model;
}

size_t
gatui_branch_get_region_bounds(
		GATUIBranch* const self,
		size_t* start,
		size_t* end
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), 0);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), 0);

	atui_branch const* const branch = self->atui;
	if (branch->table_size) {
		size_t const bios_offset = (
			branch->table_start - gatui_tree_get_bios_pointer(self->root)
		);
		if (start) {
			*start = bios_offset;
		}
		if (end) {
			*end = bios_offset + branch->table_size - 1;
		}
	}

	return branch->table_size;
}

GVariant*
gatui_branch_get_contiguous_memory(
		GATUIBranch* const self
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), NULL);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), NULL);
	atui_branch const* const branch = self->atui;
	if (branch->table_size) {
		void* const valcopy = cralloc(branch->table_size);
		memcpy(valcopy, branch->table_start, branch->table_size);
		return g_variant_new_from_data(
			self->capsule_type,
			valcopy, branch->table_size,
			false,
			free_notify, valcopy
		);
	}
	return NULL;
}
bool
gatui_branch_set_contiguous_memory(
		GATUIBranch* const self,
		GVariant* const value
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), false);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), false);
	g_return_val_if_fail((NULL != value), false);
	atui_branch const* const branch = self->atui;

	size_t const num_bytes = g_variant_get_size(value);
	void const* const input_data = g_variant_get_data(value);
	assert(input_data);
	assert(branch->table_size == num_bytes);
	if ((branch->table_size == num_bytes) && input_data) {
		memcpy(branch->table_start, input_data, num_bytes);
		g_signal_emit(self, gatui_signals[VALUE_CHANGED], 0);
		return true;
	}
	return false;
}
bool
gatui_branch_get_leaves_memory_package(
		GATUIBranch* const self,
		GVariant** const value,
		uint16_t* num_copyable_leaves
		) {
// copy the data of all direct child leaves that maps data into the bios,
// and pack it a contiguous byte array.

	g_return_val_if_fail(GATUI_IS_BRANCH(self), false);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), false);
	g_return_val_if_fail((NULL != value), false);
	g_return_val_if_fail((NULL != num_copyable_leaves), false);

	g_return_val_if_fail((0 < self->atui->num_copyable_leaves), false);
	*num_copyable_leaves = self->atui->num_copyable_leaves;
	atui_leaf const* const leaves = self->atui->leaves;
	uint16_t const leaf_count = self->atui->leaf_count;

	size_t num_bytes = 0;
	for (uint16_t i=0; i < leaf_count; i++) {
		num_bytes += leaves[i].num_bytes;
	}
	void* const bytepack = cralloc(num_bytes);
	void* walker = bytepack;
	for (uint16_t i=0; i < leaf_count; i++) {
		if (leaves[i].num_bytes) {
			walker = mempcpy(walker, leaves[i].val, leaves[i].num_bytes);
		}
	}
	assert(num_bytes == (size_t)(walker - bytepack));

	*value = g_variant_new_from_data(
		self->capsule_type,
		bytepack, num_bytes,
		false,
		free_notify, bytepack
	);
	return true;
}
bool
gatui_branch_set_leaves_memory_package(
		GATUIBranch* const self,
		GVariant* const value,
		uint16_t num_copyable_leaves
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), false);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), false);
	g_return_val_if_fail((NULL != value), false);

	if (num_copyable_leaves != self->atui->num_copyable_leaves) {
		return false;
	}

	atui_leaf const* const leaves = self->atui->leaves;
	uint16_t const leaf_count = self->atui->leaf_count;
	size_t num_bytes = 0;

	for (uint16_t i=0; i < leaf_count; i++) {
		num_bytes += leaves[i].num_bytes;
	}
	if (num_bytes != g_variant_get_size(value)) {
		return false;
	}

	void const* const input_data = g_variant_get_data(value);
	void const* walker = input_data;
	assert(input_data);
	if (input_data) {
		for (uint16_t i=0; i < leaf_count; i++) {
			if (leaves[i].num_bytes) {
				memcpy(leaves[i].u8, walker, leaves[i].num_bytes);
			}
			walker += leaves[i].num_bytes;
		}
		assert(num_bytes == (size_t)(walker - input_data));
		g_signal_emit(self, gatui_signals[VALUE_CHANGED], 0);
		return true;
	}
	return false;
}

char*
gatui_branch_to_path(
		GATUIBranch* const self
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), NULL);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), NULL);
	return atui_branch_to_path(self->atui);
}

atui_branch const*
gatui_branch_get_atui(
		GATUIBranch* const self
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), NULL);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), NULL);
	return self->atui;
}

GListModel*
branches_treelist_generate_children(
		gpointer const parent_branch,
		gpointer const data __unused
		) {
// GtkTreeListModelCreateModelFunc for branches
	GATUIBranch* const self = parent_branch;
	if (self->atui->num_branches) {
		GListStore* const children = g_list_store_new(GATUI_TYPE_BRANCH);
		g_list_store_splice(children,0,0,
			(void**)self->child_branches, self->atui->num_branches
		);
		return G_LIST_MODEL(children);
	} else {
		return NULL;
	}
}

void
branches_track_expand_state(
		GtkTreeListRow* const tree_row,
		GParamFlags* const param __unused,
		gpointer const data __unused
		) {
	if (false == gtk_tree_list_row_is_expandable(tree_row)) {
		return;
		/*
		upon collapse, all child rows will have their expand state change
		because the children stop being expandable if they previously were.
		As a result, the simple binding of properties that track the expand
		state, wouldn't work.
		*/
	}
	GATUIBranch* const branch = GATUI_BRANCH(gtk_tree_list_row_get_item(
		tree_row
	));
	branch->atui->expanded = gtk_tree_list_row_get_expanded(tree_row);
	if (branch->atui->expanded) {
		uint16_t const num_branches = branch->atui->num_branches;
		GATUIBranch* const* const child_branches = branch->child_branches;
		for (uint16_t i=0; i < num_branches; i++) {
			GtkTreeListRow* child_row = gtk_tree_list_row_get_child_row(
				tree_row, i
			);
			uint32_t handler_id = g_signal_handler_find(child_row,
				G_SIGNAL_MATCH_FUNC,  0,0,NULL,
				branches_track_expand_state,  NULL
			);
			if (0 == handler_id) {
				g_signal_connect(child_row, "notify::expanded",
					G_CALLBACK(branches_track_expand_state), NULL
				);
			}
			gtk_tree_list_row_set_expanded(
				child_row, child_branches[i]->atui->expanded
			);

			g_object_unref(child_row);
		}
	}
	g_object_unref(branch);
}

void
gatui_branch_right_click_expand_family(
		GATUIBranch* const self
		) {
	self->atui->expanded = true;
	uint16_t const num_branches = self->atui->num_branches;
	GATUIBranch* const* const child_branches = self->child_branches;
	for (uint16_t i=0; i < num_branches; i++) {
		gatui_branch_right_click_expand_family(child_branches[i]);
	}
}

