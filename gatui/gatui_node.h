#ifndef GATUI_NODE_H
#define GATUI_NODE_H

G_BEGIN_DECLS

#define GATUI_TYPE_NODE gatui_node_get_type()
G_DECLARE_DERIVABLE_TYPE(GATUINode, gatui_node, GATUI, NODE, GObject)

struct _GATUINodeClass {
	GObjectClass parent_class;

	GVariant*
	(* get_value)(
			GATUINode* self,
			GVariantType const* capsule_type
			);
};

/*
void* 
gatui_node_new( // convenience function
		GType object_type, // derived type
		atui_node* atui,
		GATUITree* root,
		char const* const typestr
		);
*/

GATUITree*
gatui_node_get_root( // root object this node descends from; does not ref
		GATUINode* self
		);

char* // needs to be freed
gatui_node_to_path(
		GATUINode* self
		);

GVariantType const*
gatui_node_get_gvariant_type(
		GATUINode* const self
		);

GListModel*
leaves_treelist_generate_children_2(
        gpointer parent,
        gpointer data // unused
		);

char const*
gatui_node_get_name(
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

GVariant*
gatui_node_get_value(
		GATUINode* const self
		);
char* // must be freed
gatui_node_to_base64(
		GATUINode* const self,
		bool const leaves_package // if leaves package; else as value
		);

G_END_DECLS
#endif
