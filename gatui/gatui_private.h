#ifndef GATUI_PRIVATE_H
#define GATUI_PRIVATE_H

#include "gatui.h"
#include "atui_allocator.h"
#include "yaabe_gtk4.h"

// amalgam of various private methods

GtkSelectionModel* const*
gatui_tree_get_enum_models_cache( // for GATUILeaves generation
		GATUITree* self
		);
GVariantType const*
gatui_tree_get_contiguous_type(
		GATUITree* self
		);

void
_gatui_node_emit_value_changed(
		GATUINode* self
		);
GATUILeaf**
_gatui_node_get_leaf_array(
		GATUINode* self
		);
atui_node*
_gatui_node_get_atui(
		GATUINode* self
		);

GATUIBranch**
_gatui_branch_get_branches_array(
		GATUIBranch* self
		);

GATUIRegexNode*
gatui_regex_node_new(
		GATUINode* tree_node,
		GMatchInfo* match_info, // regex match info
		char const* text, // matching text
		bool is_leaf,
		struct gatui_search_flags const* flags
		);
void
gatui_regex_search_recurse_leaf(
		GATUILeaf* leaf,
		GListStore* model, // destination model
		GRegex* pattern,
		struct gatui_search_flags const* flags
		);
void
gatui_regex_search_recurse_branch(
		GATUIBranch* branch,
		GListStore* model, // destination model
		GRegex* pattern,
		struct gatui_search_flags const* flags
		);
#endif
