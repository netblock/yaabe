#include "standard.h"
#include "gatui_private.h"

struct _GATUIBranch {
	GATUINode parent_instance;

	atui_node* atui;

	GATUIBranch** child_branches;
	GtkSelectionModel* leaves_model; // noselection of a treelist
};
G_DEFINE_TYPE(GATUIBranch, gatui_branch, GATUI_TYPE_NODE)


static void
gatui_branch_dispose(
		GObject* const object
		) {
	GATUIBranch* const self = GATUI_BRANCH(object);

	if (self->child_branches) {
		GATUIBranch** const child_branches = self->child_branches;
		self->child_branches = NULL;
		uint16_t const num_branches = self->atui->branch.branches.count;
		for (uint16_t i = 0; i < num_branches; i++) {
			g_object_unref(child_branches[i]);
		}
		free(child_branches);
	}
	if (self->leaves_model) {
		g_object_unref(self->leaves_model);
		self->leaves_model = NULL;
	}

	G_OBJECT_CLASS(gatui_branch_parent_class)->dispose(object);
}

static void
gatui_branch_class_init(
		GATUIBranchClass* const branch_class
		) {
	GObjectClass* const object_class = G_OBJECT_CLASS(branch_class);
	object_class->dispose = gatui_branch_dispose;

	GATUINodeClass* const node_class = GATUI_NODE_CLASS(branch_class);
	node_class->get_value = gatui_node_get_contiguous_data;
	node_class->set_value = gatui_node_set_contiguous_data;
}
static void
gatui_branch_init(
		GATUIBranch* const self __unused
		) {
}

GATUIBranch*
gatui_branch_new(
		atui_node* const branch,
		GATUITree* const root
		) {
	g_return_val_if_fail(branch, NULL);
	g_return_val_if_fail(NULL == branch->self, NULL);
	g_return_val_if_fail(false == branch->is_leaf, NULL);

	GATUIBranch* const self = g_object_new(GATUI_TYPE_BRANCH,
		"atui", branch,
		"root", root,
		"typestr", "ay",
		NULL
	);

	self->atui = branch;

	struct atui_children const* const branches = &(branch->branch.branches);
	if (branches->count) {
		self->child_branches = cralloc(branches->count * sizeof(GATUIBranch*));

		for (uint16_t i = 0; i < branches->count; i++) {
			assert(branches->addresses[i]);
			self->child_branches[i] = gatui_branch_new(
				branches->addresses[i], root
			);
			assert(self->child_branches[i]);
		}
	}

	if (branch->leaves.count) { // generate leaves_model
		GtkSingleSelection* const single_model = gtk_single_selection_new(
			G_LIST_MODEL(gtk_tree_list_model_new(
				leaves_treelist_generate_children(self, NULL),
				false, true,
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

	return self;
}

GtkSelectionModel*
gatui_branch_get_leaves_model(
		GATUIBranch* const self
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), NULL);
	return self->leaves_model;
}

GATUITree*
gatui_branch_get_root(
		GATUIBranch* const self
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), NULL);
	return gatui_node_get_root(GATUI_NODE(self));
}
size_t
gatui_branch_get_region_bounds(
		GATUIBranch* const self,
		size_t* start,
		size_t* end
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), 0);
	return gatui_node_get_region_bounds(GATUI_NODE(self), start, end);
}
GVariant*
gatui_branch_get_contiguous_memory(
		GATUIBranch* const self
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), NULL);
	return gatui_node_get_contiguous_data(GATUI_NODE(self));
}
bool
gatui_branch_set_contiguous_memory(
		GATUIBranch* const self,
		GVariant* const value
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), false);
	return gatui_node_set_contiguous_data(GATUI_NODE(self), value);
}
bool
gatui_branch_get_leaves_memory_package(
		GATUIBranch* const self,
		GVariant** const value,
		uint16_t* num_copyable_leaves
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), false);
	return gatui_node_get_leaves_package(
		GATUI_NODE(self), value, num_copyable_leaves
	);
}
bool
gatui_branch_set_leaves_memory_package(
		GATUIBranch* const self,
		GVariant* const value,
		uint16_t num_copyable_leaves
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), false);
	return gatui_node_set_leaves_memory_package(GATUI_NODE(self), value, num_copyable_leaves);
}

char*
gatui_branch_to_base64(
		GATUIBranch* const self,
		bool const leaves_package
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), NULL);
	assert(0);
	return gatui_node_to_base64(GATUI_NODE(self), GATUI_NODE_B64_LEAVES_PACKAGE);
}
bool
gatui_branch_from_base64(
		GATUIBranch* const self,
		char const* const b64_text,
		struct b64_header** const error_out
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), false);
	return gatui_node_from_base64(
		GATUI_NODE(self), b64_text, (void*) error_out
	);
}
atui_node const*
gatui_branch_get_atui(
		GATUIBranch* const self
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), NULL);
	return self->atui;
}
char*
gatui_branch_to_path(
		GATUIBranch* const self
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), NULL);
	return atui_node_to_path(self->atui);
}


GListModel*
branches_treelist_generate_children(
		gpointer const parent_branch,
		gpointer const data __unused
		) {
// GtkTreeListModelCreateModelFunc for branches
	GATUIBranch* const self = parent_branch;
	if (self->atui->branch.branches.count) {
		GListStore* const children = g_list_store_new(GATUI_TYPE_BRANCH);
		g_list_store_splice(children,0,0,
			(void**)self->child_branches, self->atui->branch.branches.count
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
	branch->atui->branch.branches.expanded = gtk_tree_list_row_get_expanded(tree_row);
	if (branch->atui->branch.branches.expanded) {
		uint16_t const num_branches = branch->atui->branch.branches.count;
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
				child_row, child_branches[i]->atui->branch.branches.expanded
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
	self->atui->branch.branches.expanded = true;
	uint16_t const num_branches = self->atui->branch.branches.count;
	GATUIBranch* const* const child_branches = self->child_branches;
	for (uint16_t i=0; i < num_branches; i++) {
		gatui_branch_right_click_expand_family(child_branches[i]);
	}
}

void
gatui_regex_search_recurse_branch(
		GATUIBranch* const branch,
		GListStore* const model,
		GRegex* const pattern,
		struct gatui_search_flags const* const flags
		) {
/*
	atui_node const* const atui = branch->atui;

	if ((flags->domain == GATUI_SEARCH_NAMES) && flags->branches) {
		GMatchInfo* match_info;
		bool matched = g_regex_match(
			pattern, atui->name, G_REGEX_MATCH_DEFAULT, &match_info
		);
		if (matched) {
			GATUIRegexNode* node = gatui_regex_node_new(
				G_OBJECT(branch), match_info, atui->name, false, flags
			);
			g_list_store_append(model, node);
			g_object_unref(node);
		}
		g_match_info_unref(match_info);
	}

	if (flags->leaves) {
		for (uint16_t i=0; i < atui->leaves.count; i++) {
			gatui_regex_search_recurse_leaf(
				branch->leaves[i], model, pattern, flags
			);
		}
	}

	for (uint16_t i=0; i < atui->branch.branches.count; i++) {
		gatui_regex_search_recurse_branch(
			branch->child_branches[i], model, pattern, flags
		);
	}
*/
}
