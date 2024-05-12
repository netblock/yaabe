#include "gatui_private.h"

struct _GATUIBranch {
	GObject parent_instance;

	atui_branch* atui;
	GATUIBranch** child_branches;
	GtkSelectionModel* leaves_model; // noselection of a treelist
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

	G_OBJECT_CLASS(gatui_branch_parent_class)->dispose(object);
}

static void
gatui_branch_class_init(
		GATUIBranchClass* const branch_class
		) {
	GObjectClass* const object_class = G_OBJECT_CLASS(branch_class);

	object_class->dispose = gatui_branch_dispose;
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
	g_return_val_if_fail(branch->self == NULL, NULL);
	GATUIBranch* const self = g_object_new(GATUI_TYPE_BRANCH, NULL);
	self->atui = branch;
	branch->self = self;

	uint8_t const num_branches = branch->num_branches;
	if (num_branches) {
		self->child_branches = malloc(num_branches * sizeof(GATUIBranch*));

		for (uint8_t i = 0; i < num_branches; i++) {
			self->child_branches[i] = gatui_branch_new_tree(
				branch->child_branches[i]
			);
		}
	}

	if (branch->leaf_count) {
		GListStore* const leaf_list = g_list_store_new(GATUI_TYPE_LEAF);
		atui_leaves_to_gliststore(
			leaf_list, branch->leaves, branch->leaf_count
		);
		self->leaves_model = GTK_SELECTION_MODEL(
			gtk_no_selection_new(G_LIST_MODEL(
				gtk_tree_list_model_new(
					G_LIST_MODEL(leaf_list),
					false, true, leaves_treelist_generate_children, NULL,NULL
				)
			))
		); // the later models take ownership of the earlier
	}

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


atui_branch*
gatui_branch_get_atui(
		GATUIBranch* const self
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), NULL);
	return self->atui;
}
