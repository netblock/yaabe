#include "gatui_private.h"

enum {
	VALUE_CHANGED,
	LAST_SIGNAL
};
static guint gatui_signals[LAST_SIGNAL] = {0};

struct _GATUIBranch {
	GObject parent_instance;

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
		uint8_t const num_branches = self->atui->num_branches;
		for (uint8_t i = 0; i < num_branches; i++) {
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


static GListModel*
leaves_treelist_generate_children(
		gpointer const parent_leaf,
		gpointer const unused
		) {
// GtkTreeListModelCreateModelFunc for leaves
	return gatui_leaf_generate_children_model(parent_leaf);
}

GATUIBranch*
gatui_branch_new_tree(
		atui_branch* const branch
		) {
	assert(NULL == branch->self);
	g_return_val_if_fail(branch->self == NULL, NULL);
	GATUIBranch* const self = g_object_new(GATUI_TYPE_BRANCH, NULL);
	self->atui = branch;
	branch->self = self;

	uint8_t const num_branches = branch->num_branches;
	if (num_branches) {
		self->child_branches = malloc(num_branches * sizeof(GATUIBranch*));

		for (uint8_t i = 0; i < num_branches; i++) {
			assert(branch->child_branches[i]);
			self->child_branches[i] = gatui_branch_new_tree(
				branch->child_branches[i]
			);
			assert(self->child_branches[i]);
		}
	}

	if (branch->leaf_count) {
		GListStore* const leaf_list = g_list_store_new(GATUI_TYPE_LEAF);
		atui_leaves_to_gliststore(
			leaf_list, branch->leaves, branch->leaf_count
		);
		GListModel* const leaf_list_model = G_LIST_MODEL(leaf_list);

		uint16_t const num_leaves = g_list_model_get_n_items(leaf_list_model);
		for (uint16_t i=0; i < num_leaves; i++) {
			GATUILeaf* leaf = g_list_model_get_item(leaf_list_model, i);
			g_signal_connect_swapped(self, "value-changed",
				G_CALLBACK(gatui_leaf_emit_val_changed), leaf
			);
			g_object_unref(leaf);
		}

		self->leaves_model = GTK_SELECTION_MODEL(
			gtk_no_selection_new(G_LIST_MODEL(
				gtk_tree_list_model_new(
					leaf_list_model,
					false, true, leaves_treelist_generate_children, NULL,NULL
				)
			))
		); // the later models take ownership of the earlier
	}

	self->capsule_type = g_variant_type_new("ay");

	return self;
}

GListModel*
gatui_branch_generate_children_model(
		GATUIBranch* const self
		) {
// this is intended to be used in a GtkTreeListModelCreateModelFunc
	g_return_val_if_fail(GATUI_IS_BRANCH(self), NULL);
	if (self->atui->num_branches) {
		GListStore* const children = g_list_store_new(GATUI_TYPE_BRANCH);
		g_list_store_splice(children,0,0,
			(void**)self->child_branches, self->atui->num_branches
		);
		return G_LIST_MODEL(children);
	}
	return NULL;
}

GtkSelectionModel*
gatui_branch_get_leaves_model(
		GATUIBranch* const self
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), NULL);
	return self->leaves_model;
}


GVariant*
gatui_branch_get_contiguous_memory(
		GATUIBranch* const self
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), NULL);
	atui_branch const* const branch = self->atui;
	if (branch->table_size) {
		void* const valcopy = malloc(branch->table_size);
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
	void* const bytepack = malloc(num_bytes);
	void* walker = bytepack;
	for (uint16_t i=0; i < leaf_count; i++) {
		if (leaves[i].num_bytes) {
			walker = mempcpy(walker, leaves[i].val, leaves[i].num_bytes);
		}
	}
	assert(num_bytes == (walker - bytepack));

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
		assert(num_bytes == (walker - input_data));
		g_signal_emit(self, gatui_signals[VALUE_CHANGED], 0);
		return true;
	}
	return false;
};

atui_branch*
gatui_branch_get_atui(
		GATUIBranch* const self
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), NULL);
	return self->atui;
}
