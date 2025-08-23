#include "standard.h"
#include <zlib.h> 
#include "gatui_private.h"

union b64_header_raw {
	void* raw;
	struct b64_header* header;
};

char*
b64_packet_encode(
		GVariant* const val,
		enum gatui_b64_target const target,
		uint16_t const num_segments
		) {
	size_t const payload_size = g_variant_get_size(val);
	size_t const packet_size = sizeof(struct b64_header) + payload_size;

	union b64_header_raw const h = {.header = cralloc(packet_size)};

	*h.header = (struct b64_header) {
		.version = B64_HEADER_VER_CURRENT,
		.target = target,
		.num_segments = num_segments,
		.num_bytes = payload_size,
	};
	memcpy(h.header->typestr,g_variant_get_type_string(val), GATUI_TYPESTR_LEN);
	memcpy(h.header->bytes, g_variant_get_data(val), payload_size);
	h.header->crc = crc32(
		0,
		(h.raw + sizeof(h.header->crc)), // exclude crc
		(packet_size - sizeof(h.header->crc))
	);

	gchar* const b64_text = g_base64_encode(h.raw, packet_size);
	free(h.header);
	return b64_text;
}

struct b64_header*
b64_packet_decode(
		char const* const b64_text
		) {
	size_t b64_num_bytes = 0;
	union b64_header_raw const h = {
		.raw = g_base64_decode(b64_text, &b64_num_bytes)
	};

	if (0 == b64_num_bytes) {
		goto error_exit;
	}
	if (b64_num_bytes < sizeof(*h.header)) {
		goto error_exit;
	}
	if (b64_num_bytes < (h.header->num_bytes + sizeof(*h.header))) {
		goto error_exit;
	}
	uint32_t const crc = crc32(
		0,
		(h.raw + sizeof(h.header->crc)),
		(sizeof(*h.header)-sizeof(h.header->crc)  +  h.header->num_bytes)
	);
	if (crc != h.header->crc) {
		goto error_exit;
	}

	if (B64_HEADER_VER_CURRENT != h.header->version) {
		goto error_exit;
	}

	if (GATUI_TYPESTR_LEN <= strnlen(h.header->typestr, GATUI_TYPESTR_LEN)) {
		goto error_exit;
	}

	// strict compliance
	if ((B64_BRANCH_CONTIGUOUS == h.header->target)
			&& (1 != h.header->num_segments)
			) {
		goto error_exit;
	}
	if ((B64_LEAF==h.header->target) && (1!=h.header->num_segments)) {
		goto error_exit;
	}

	return h.header;

	error_exit:
	free(h.header);
	return NULL;
}


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
	if (self->node.gatui) {
		g_object_unref(self->node.gatui);
		g_match_info_unref(self->node.match_info);
		free(self->node.text);
		free(self->node.markup_text);

		self->node.gatui = NULL;
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
		GObject* const gatui,
		GMatchInfo* const match_info,
		char const* const text,
		bool const is_leaf,
		struct gatui_search_flags const* const flags
		) {
	GATUIRegexNode* const self = g_object_new(GATUI_TYPE_REGEX_NODE, NULL);
	g_object_ref(gatui);
	g_match_info_ref(match_info);

	self->node.gatui = gatui;
	self->node.match_info = match_info;
	self->node.is_leaf = is_leaf;
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
