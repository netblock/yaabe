#include "standard.h"
#include "gatui_private.h"

struct _GATUIBranch {
	GATUINode parent_instance;

	atui_node* atui;

	uint16_t num_branches; // same as atui_node.branch.branches.count
	GATUIBranch** branches;
	GtkSelectionModel* leaves_model; // noselection of a treelist
};
G_DEFINE_TYPE(GATUIBranch, gatui_branch, GATUI_TYPE_NODE)


static void
gatui_branch_dispose(
		GObject* const object
		) {
	GATUIBranch* const self = GATUI_BRANCH(object);

	if (self->branches) {
		GATUIBranch** const branches = self->branches;
		self->branches = NULL;
		for (uint16_t i = 0; i < self->num_branches; i++) {
			g_object_unref(branches[i]);
		}
		free(branches);
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
	self->num_branches = branches->count;
	if (branches->count) {
		self->branches = cralloc(branches->count * sizeof(GATUIBranch*));

		for (uint16_t i = 0; i < branches->count; i++) {
			assert(branches->addresses[i]);
			self->branches[i] = gatui_branch_new(
				branches->addresses[i], root
			);
			assert(self->branches[i]);
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

uint16_t
gatui_branch_get_num_branches(
		GATUIBranch* const self
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), 0);
	return self->num_branches;
}

GtkSelectionModel*
gatui_branch_get_leaves_model(
		GATUIBranch* const self
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), NULL);
	return self->leaves_model;
}

GATUIBranch**
_gatui_branch_get_branches_array(
		GATUIBranch* const self
		) {
	g_return_val_if_fail(GATUI_IS_BRANCH(self), NULL);
	return self->branches;
}

GListModel*
branches_treelist_generate_children(
		gpointer const parent_branch,
		gpointer const data __unused
		) {
// GtkTreeListModelCreateModelFunc for branches
	GATUIBranch* const self = parent_branch;
	if (self->num_branches) {
		GListStore* const children = g_list_store_new(GATUI_TYPE_BRANCH);
		g_list_store_splice(children,0,0,
			(void**)self->branches, self->num_branches
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
	struct atui_children* const branches = &(branch->atui->branch.branches);

	branches->expanded = gtk_tree_list_row_get_expanded(tree_row);
	if (branches->expanded) {
		uint16_t const num_branches = branches->count;
		GATUIBranch* const* const branches = branch->branches;
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
				child_row, branches[i]->atui->branch.branches.expanded
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
	g_return_if_fail(GATUI_IS_BRANCH(self));
	self->atui->branch.branches.expanded = true;
	uint16_t const num_branches = self->num_branches;
	GATUIBranch* const* const branches = self->branches;
	for (uint16_t i=0; i < num_branches; i++) {
		gatui_branch_right_click_expand_family(branches[i]);
	}
}

void
gatui_regex_search_recurse_branch(
		GATUIBranch* const branch,
		GListStore* const model,
		GRegex* const pattern,
		struct gatui_search_flags const* const flags
		) {
	// very similar to gatui_regex_search_recurse_leaf
	// possible way to deduplicate is to virtual func:  get_text(flags)
	// where search_recurse is also a virtual func so branch can append its
	// child branch loop.
	char const* text = NULL;
	if ((GATUI_SEARCH_NAMES == flags->domain) && flags->branches) {
		text = branch->atui->name;
	}
	if (text) {
		GMatchInfo* match_info;
		bool const matched = g_regex_match(
			pattern, text, G_REGEX_MATCH_DEFAULT, &match_info
		);
		if (matched) {
			GATUIRegexNode* const regex_node = gatui_regex_node_new(
				GATUI_NODE(branch), match_info, text, flags
			);
			g_list_store_append(model, regex_node);
			g_object_unref(regex_node);
		}
		g_match_info_unref(match_info);
	}

	if (flags->leaves) {
		GATUILeaf* const* const leaves = _gatui_node_get_leaf_array(GATUI_NODE(
			branch
		));
		uint16_t const count = branch->atui->leaves.count;
		for (uint16_t i=0; i < count; i++) {
			gatui_regex_search_recurse_leaf(leaves[i], model, pattern, flags);
		}
	}

	GATUIBranch* const* const branches = branch->branches;
	for (uint16_t i=0; i < branch->num_branches; i++) {
		gatui_regex_search_recurse_branch(branches[i], model, pattern, flags);
	}
}
