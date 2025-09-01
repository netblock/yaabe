/*
gatui is a GObject-based wrapper to atui. Start at gatui_trunk.
Since it's GObject, there is thread-safe reference counting.
However bios-data IO is not thread-safe (spinlock? mode-based lock?).
*/

#ifndef GATUI_H
#define GATUI_H

#include "atui.h"

#define GATUI_TYPE_REGEX_NODE gatui_regex_node_get_type()
G_DECLARE_FINAL_TYPE(GATUIRegexNode, gatui_regex_node, GATUI, REGEX_NODE, GObject)

typedef struct _GATUILeaf GATUILeaf;
typedef struct _GATUIBranch GATUIBranch;
typedef struct _GATUITree GATUITree;

enum gatui_search_domain {
	GATUI_SEARCH_NAMES    = 0,
	GATUI_SEARCH_VALUES   = 1,
};
struct gatui_search_flags {
	enum gatui_search_domain domain; // values is only leaves
	bool leaves;
	bool branches; // gets ignored if domain is value
};
struct atui_regex_node {
	GObject* gatui;
	GMatchInfo* match_info;
	char* text; // literal matching text
	char* markup_text; // matching text but with markup
	bool is_leaf; // false means branch
	struct gatui_search_flags flags;
};

struct atui_regex_node const* // all data is owned by the instance
gatui_regex_node_peek(
		GATUIRegexNode* self
		);

#include "gatui_node.h"
#include "gatui_branch.h"
#include "gatui_leaf.h"
#include "gatui_tree.h"

#endif
