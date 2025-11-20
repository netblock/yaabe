#ifndef GATUI_BRANCH_H
#define GATUI_BRANCH_H
G_BEGIN_DECLS

#define GATUI_TYPE_BRANCH gatui_branch_get_type()
G_DECLARE_FINAL_TYPE(GATUIBranch, gatui_branch, GATUI, BRANCH, GATUINode)

GATUIBranch*
gatui_branch_new( // including all of its descendants and leaves
		atui_node* branch
		);

uint16_t
gatui_branch_get_num_branches(
		GATUIBranch* self
		);
GtkSelectionModel* // no-selection of a tree-model; does not ref
gatui_branch_get_leaves_model(
		GATUIBranch* self
		);

// GtkTreeListModelCreateModelFunc for branches
GListModel*
branches_treelist_generate_children(
        gpointer parent_branch,
        gpointer data // unused
        );

void
gatui_branch_right_click_expand_family( // recursively expand all sub branches
		GATUIBranch* self
		);

void
gatui_branch_load_expand_state(
		GATUIBranch* self,
		GtkTreeListRow* row
		);

G_END_DECLS
#endif
