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

size_t
gatui_branch_get_region_bounds(
		GATUIBranch* self,
		size_t* start, // can be NULL
		size_t* end // can be NULL; -1 last byte within 
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
		GVariant** value, // data package out
		uint16_t* num_copyable_leaves
		);
bool // success
gatui_branch_set_leaves_memory_package(
		GATUIBranch* self,
		GVariant* value,
		uint16_t num_copyable_leaves
		);

char* // needs to be freed
gatui_branch_to_base64(
		GATUIBranch* self,
		bool leaves_package // if leaves package; else contiguous
		);
bool // success
gatui_branch_from_base64(
		GATUIBranch* self,
		char const* b64_text,
		// error diagnostics; optional; needs to be freed:
		struct b64_header** error_out
		);

char* // needs to be freed
gatui_branch_to_path(
		GATUIBranch* self
		);

atui_branch const*
gatui_branch_get_atui( // for the trivial atui_branch data
		GATUIBranch* self
		);

void
gatui_branch_right_click_expand_family( // recursively expand all sub branches
		GATUIBranch* self
		);

// should be moved into private if the notify problem gets solved.
void
branches_track_expand_state( // branch expand/collapse state managment
        GtkTreeListRow* tree_row,
        GParamFlags* param,
        gpointer data // unused
        );

void
gatui_branch_load_expand_state(
		GATUIBranch* self,
		GtkTreeListRow* row
		);
void
gatui_branch_load_expand_state(
		GATUIBranch* self,
		GtkTreeListRow* tree_row
		);

G_END_DECLS
#endif
