#include "standard.h"
#include "gatui_private.h"

struct _GATUIRegexNode {
	GObject parent_instance;

	struct atui_regex_node node;
};
G_DEFINE_TYPE(GATUIRegexNode, gatui_regex_node, G_TYPE_OBJECT)

static void
gatui_regex_node_dispose(
		GObject* const object
		) {
	GATUIRegexNode* const self = GATUI_REGEX_NODE(object);
	if (self->node.tree_node) {
		g_object_unref(self->node.tree_node);
		g_match_info_unref(self->node.match_info);
		free(self->node.text);
		free(self->node.markup_text);

		self->node.tree_node = NULL;
		self->node.match_info = NULL;
		self->node.text = NULL;
		self->node.markup_text = NULL;
	};
};
static void
gatui_regex_node_class_init(
		GATUIRegexNodeClass* const regex_node_class
		) {
	GObjectClass* const object_class = G_OBJECT_CLASS(regex_node_class);

	object_class->dispose = gatui_regex_node_dispose;
}
static void
gatui_regex_node_init(
		GATUIRegexNode* const self __unused
		) {
}
GATUIRegexNode*
gatui_regex_node_new(
		GATUINode* const tree_node,
		GMatchInfo* const match_info,
		char const* const text,
		struct gatui_search_flags const* const flags
		) {
	GATUIRegexNode* const self = g_object_new(GATUI_TYPE_REGEX_NODE, NULL);
	g_object_ref(tree_node);
	g_match_info_ref(match_info);

	self->node.tree_node = tree_node;
	self->node.match_info = match_info;
	self->node.flags = *flags;

	size_t const text_len = strlen(text) + 1;
	self->node.text = cralloc(text_len);
	memcpy(self->node.text, text, text_len);

	constexpr char markup_prefix[] = "<span color=\"red\">";
	constexpr char markup_suffix[] = "</span>";
	size_t const markup_len = (
		lengthof(markup_prefix)-1
		+ text_len
		+ lengthof(markup_suffix)-1
	);
	self->node.markup_text = cralloc(markup_len);

	int32_t start = 0;
	int32_t end = 0;
	bool const fetched __unused = g_match_info_fetch_pos(
		match_info, 0, &start, &end
	);
	assert(fetched);
	assert(text_len - start);
	assert(text_len - end);

	char* out_walker = self->node.markup_text;
	char const* in_walker = text;
	out_walker = mempcpy(out_walker, in_walker, start);
	in_walker += start;
	out_walker = mempcpy(out_walker, markup_prefix, lengthof(markup_prefix)-1);
	out_walker = mempcpy(out_walker, in_walker, end-start);
	in_walker += end-start;
	out_walker = mempcpy(out_walker, markup_suffix, lengthof(markup_suffix)-1);
	out_walker = mempcpy(out_walker, in_walker, text_len-end);

	assert(*(out_walker-1) == '\0');
	in_walker += text_len-end;
	assert(in_walker == (text+text_len));
	assert(out_walker == (self->node.markup_text+markup_len));

	return self;
}
struct atui_regex_node const*
gatui_regex_node_peek(
		GATUIRegexNode* const self
		) {
	g_return_val_if_fail(GATUI_IS_REGEX_NODE(self), NULL);

	return &(self->node);
}
