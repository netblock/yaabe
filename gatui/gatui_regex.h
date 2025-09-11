#ifndef GATUI_REGEX_H
#define GATUI_REGEX_H
G_BEGIN_DECLS

#define GATUI_TYPE_REGEX_NODE gatui_regex_node_get_type()
G_DECLARE_FINAL_TYPE(GATUIRegexNode, gatui_regex_node, GATUI, REGEX_NODE, GObject)

enum gatui_search_domain:uint8_t {
	GATUI_SEARCH_NAMES    = 0,
	GATUI_SEARCH_VALUES   = 1,
};
struct gatui_search_flags {
	enum gatui_search_domain domain; // values is only leaves
	bool leaves;
	bool branches; // gets ignored if domain is value
};
struct atui_regex_node {
	GATUINode* tree_node;
	GMatchInfo* match_info;
	char* text; // literal matching text
	char* markup_text; // matching text but with markup
	struct gatui_search_flags flags;
};

struct atui_regex_node const* // all data is owned by the instance
gatui_regex_node_peek(
		GATUIRegexNode* self
		);

G_END_DECLS
#endif
