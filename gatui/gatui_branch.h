#ifndef GATUI_BRANCH_H
#define GATUI_BRANCH_H

G_BEGIN_DECLS

#define GATUI_TYPE_BRANCH gatui_branch_get_type()
G_DECLARE_FINAL_TYPE(GATUIBranch, gatui_branch, GATUI, BRANCH, GObject)

GATUIBranch*
gatui_branch_new( // including all of its descendants and leaves
		atui_branch* branch,
		GATUITree* root
		);

GListModel* // basic model for GtkTreeListModelCreateModelFunc
gatui_branch_generate_children_model(
		GATUIBranch* self
		);

GtkSelectionModel* // no-selection of a tree-model
gatui_branch_get_leaves_model(
		GATUIBranch* self
		);

// contiguous memory in the bios
GVariant*
gatui_branch_get_contiguous_memory(
		GATUIBranch* self
		);
bool // success
gatui_branch_set_contiguous_memory(
		GATUIBranch* self,
		GVariant* data
		);
// the leaves of the branch, which may have arbitrary positions in the bios
bool // success
gatui_branch_get_leaves_memory_package(
		GATUIBranch* self,
		GVariant** value,
		uint16_t* num_copyable_leaves
		);
bool // success
gatui_branch_set_leaves_memory_package(
		GATUIBranch* self,
		GVariant* value,
		uint16_t num_copyable_leaves
		);

char* // needs to be freed
gatui_branch_to_path(
		GATUIBranch* self
		);

atui_branch*
gatui_branch_get_atui(
		GATUIBranch* self
		);

G_END_DECLS
#endif
