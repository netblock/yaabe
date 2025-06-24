#ifndef GATUI_PRIVATE_H
#define GATUI_PRIVATE_H

#include "gatui.h"
#include "atui_allocator.h"
#include "yaabe_gtk4.h"


char* // needs to be freed
b64_packet_encode(
		struct b64_header const* config,
		void const* payload
		);
struct b64_header* // NULL on error
b64_packet_decode(
		char const* b64_text
		);


GtkSelectionModel* const*
gatui_tree_get_enum_models_cache( // for GATUILeaves generation
		GATUITree* self
		);

void
gatui_leaf_emit_val_changed( // single-signal multi-user alert network
		GATUILeaf* self
		);


GATUIRegexNode*
gatui_regex_node_new(
		GObject* gatui, // branch or leaf
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

