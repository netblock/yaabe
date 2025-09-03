#ifndef GATUI_NODE_H
#define GATUI_NODE_H

G_BEGIN_DECLS

#define GATUI_TYPE_NODE gatui_node_get_type()
G_DECLARE_DERIVABLE_TYPE(GATUINode, gatui_node, GATUI, NODE, GObject)

struct _GATUINodeClass {
	GObjectClass parent_class;

	GVariant*
	(* get_value)(
			GATUINode* self
			);
	bool
	(* set_value)(
			GATUINode* self,
			GVariant* value
			);
};
void
gatui_node_emit_value_changed(
		GATUINode* self
		);

/*
void* 
gatui_node_new( // convenience function
		GType object_type, // derived type
		atui_node* atui,
		GATUITree* root,
		char const* const typestr
		);
*/

GVariantType const*
gatui_node_get_capsule_type(
		GATUINode* const self
		);

GVariant* // caller takes ownership
gatui_node_get_value( // fancy value, if applicable
		GATUINode* self
		);
bool // sucess
gatui_node_set_value(
		GATUINode* self,
		GVariant* value
		);

GVariant* // caller takes ownership
gatui_node_get_contiguous_data( // as raw byte array
		GATUINode* self
		);
bool // sucess
gatui_node_set_contiguous_data( // as raw byte array
		GATUINode* self,
		GVariant* value
		);

bool // success
gatui_node_get_leaves_package( // get byte array of all leaves that have data
		GATUINode* self,
		GVariant** value, // required
		uint16_t* num_copyable_leaves // num segments
		); 
bool // success
gatui_node_set_leaves_memory_package( // set leaves based on a byte array
		GATUINode* self,
		GVariant* value,
		uint16_t num_copyable_leaves // num segments
		);

#pragma pack(push, 1)
#define GATUI_TYPESTR_LEN 3
#define GATUI_NODE_B64_HEADER_VER_CURRENT 1
enum gatui_node_b64_target:uint64_t { // TODO reorder on next version bump
	GATUI_NODE_B64_CONTIGUOUS,
	GATUI_NODE_B64_LEAVES_PACKAGE,
	GATUI_NODE_B64_VALUE
};
struct gatui_node_b64_header { // paste header
	uint32_t crc; // everything not crc, including rest of header.
	struct {
		uint64_t version                  :1-0 +1;
		enum gatui_node_b64_target target :4-2 +1;
		uint64_t num_segments            :15-5 +1; // 2048 leaves
		uint64_t num_bytes               :37-16 +1; // 4MiB
		uint64_t padding                 :63-38 +1;
	};
	char typestr[GATUI_TYPESTR_LEN];
	uint8_t bytes[] __counted_by(num_bytes);
};
#pragma pack(pop)

char* // must be freed
gatui_node_to_base64(
		GATUINode* const self,
		enum gatui_node_b64_target format
		);
bool // success
gatui_node_from_base64(
		GATUINode* self,
		char const* b64_text,
		struct gatui_node_b64_header** error_out // optional
		);

GListModel*
leaves_treelist_generate_children(
        gpointer parent,
        gpointer data // unused
		);

GATUITree*
gatui_node_get_root( // root object this node descends from; does not ref
		GATUINode* self
		);
char* // needs to be freed
gatui_node_to_path(
		GATUINode* self
		);
char const*
gatui_node_get_name(
		GATUINode* self
		);
char const*
gatui_node_get_origname(
		GATUINode* self
		);
char const*
gatui_node_get_structname(
		GATUINode* self
		);
char const*
gatui_node_get_description(
		GATUINode* self,
		enum i18n_languages lang
		);

size_t
gatui_node_get_region_bounds(
		GATUINode* self,
		size_t* start, // can be NULL
		size_t* end // can be NULL; -1 last byte within 
		);

G_END_DECLS
#endif
