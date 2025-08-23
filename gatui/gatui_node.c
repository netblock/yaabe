#include "standard.h"
#include "gatui_private.h"

enum GATUINodeSignal {
	VALUE_CHANGED,
	LAST_SIGNAL
};
static guint gatui_signals[LAST_SIGNAL] = {};

enum GATUINodeProperty:uint32_t {
	PROP_ATUI = 1,
	PROP_ROOT,
	PROP_TYPESTR,
	N_PROPERTIES
};

static GParamSpec* obj_properties[N_PROPERTIES] = {};

typedef struct _GATUINodePrivate {
	GObject parent_instance;

	GATUITree* root;
	GATUINode* parent; // weak ref
	atui_node* atui;

	uint16_t num_leaves; // same as atui_node.leaves.count
	GATUILeaf** leaves;

	char typestr[GATUI_TYPESTR_LEN];
	GVariantType* capsule_type;
} GATUINodePrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GATUINode, gatui_node, G_TYPE_OBJECT)


static void
gatui_node_set_property(
		GObject* const object,
		enum GATUINodeProperty const prop_id,
		GValue const* const value,
		GParamSpec* const pspec
		) {
	GATUINodePrivate* const priv = gatui_node_get_instance_private(
		GATUI_NODE(object)
	);
	switch (prop_id) {
		case PROP_ATUI:
			assert(NULL == priv->atui);
			priv->atui = g_value_get_pointer(value);
			assert(priv->atui);
			break;
		case PROP_ROOT:
			GATUITree* const root = g_value_get_pointer(value);
			assert(NULL == priv->root);
			if (root) {
				priv->root = g_value_get_pointer(value);
				g_object_ref(priv->root);
			}
			break;
		case PROP_TYPESTR:
			char const* typestr = g_value_get_pointer(value);
			assert(typestr);
			memcpy(priv->typestr, typestr, GATUI_TYPESTR_LEN);
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
			break;
	}
};
static void
gatui_node_get_property(
		GObject* const object,
		enum GATUINodeProperty const prop_id,
		GValue* const value __unused,
		GParamSpec* const pspec
		) {
	GATUINodePrivate* const priv __unused = gatui_node_get_instance_private(
		GATUI_NODE(object)
	);
	switch (prop_id) {
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
			break;
	}
};

static void
gatui_node_dispose(
		GObject* const object
		) {
	GATUINodePrivate* const priv = gatui_node_get_instance_private(
		GATUI_NODE(object)
	);
	if (priv->root) {
		g_object_unref(priv->root);
		priv->root = NULL;
	}

	if (priv->leaves) {
		for (uint16_t i=0; i < priv->num_leaves; i++) {
			//leaves[i]->parent_leaf = NULL;
			g_object_unref(priv->leaves[i]);
		}
		free(priv->leaves);
		priv->leaves = NULL;
	}

	// weak references
	priv->parent = NULL;
	priv->atui->self = NULL;

	if (priv->capsule_type) {
		g_free(priv->capsule_type);
		priv->capsule_type = NULL;
	}

	G_OBJECT_CLASS(gatui_node_parent_class)->dispose(object);
}

/*
void* 
gatui_node_new(
		GType const object_type,
		atui_node* const atui,
		GATUITree* const root,
		char const* const typestr
		) {
	char const* const prop_names[] = {"atui", "root", "typestr"};
	GValue prop_vals[lengthof(prop_names)] = {};
	g_value_set_pointer(g_value_init(&(prop_vals[0]), G_TYPE_POINTER), atui);
	g_value_set_pointer(g_value_init(&(prop_vals[2]), G_TYPE_POINTER), root);
	g_value_set_pointer(g_value_init(&(prop_vals[2]), G_TYPE_POINTER), typestr);
	return g_object_new_with_properties(
		object_type,  lengthof(prop_names), (char const**)prop_names, prop_vals
	);
}
*/

static void 
gatui_node_constructed(
		GObject* const object
		) {
	GATUINode* const self = GATUI_NODE(object);
	GATUINodePrivate* const priv = gatui_node_get_instance_private(self);
	atui_node* const atui = priv->atui;

	assert(NULL == atui->self);
	atui->self = self;

	if (atui->parent) {
		priv->parent = atui->parent->self; // soft-ref to not ref-loop
	}

	if (NULL == priv->root) {
		assert(priv->parent);
		priv->root = gatui_node_get_root(priv->parent);
		g_object_ref(priv->root);
	} 

	priv->capsule_type = g_variant_type_new(priv->typestr);

	struct atui_children const* const children = &(atui->leaves);
	if (children->count) { // generate leaves_model
		priv->leaves = cralloc(atui->leaves.count * sizeof(GATUILeaf*));
		priv->num_leaves = children->count;
		for (uint16_t i=0; i < children->count; i++) {
			GATUILeaf* leaf = gatui_leaf_new(
				//&(children->nodes[i]), self, priv->root
				&(children->nodes[i]), priv->root
			);
			// TODO
			g_signal_connect_swapped(self, "value-changed",
				G_CALLBACK(gatui_leaf_emit_val_changed), leaf
			);
			priv->leaves[i] = leaf; // keep the ref
		}
	}
}

static void
gatui_node_class_init(
		GATUINodeClass* const node_class
		) {
	GObjectClass* const object_class = G_OBJECT_CLASS(node_class);

	object_class->set_property = gatui_node_set_property;
	object_class->get_property = gatui_node_get_property;
	object_class->dispose = gatui_node_dispose;
	object_class->constructed = gatui_node_constructed;

	gatui_signals[VALUE_CHANGED] = g_signal_new(
		"value-changed",
		G_TYPE_FROM_CLASS(node_class),
		(G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE),
		0,
		NULL, NULL,
		NULL,
		G_TYPE_NONE, 0
	);

	obj_properties[PROP_ATUI] = g_param_spec_pointer(
		"atui",  NULL, NULL,
		(G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE)
	);
	obj_properties[PROP_ROOT] = g_param_spec_pointer(
		"root",  NULL, NULL,
		(G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE)
	);
	obj_properties[PROP_TYPESTR] = g_param_spec_pointer(
		"typestr",  NULL, NULL,
		(G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE)
	);
	g_object_class_install_properties(
		object_class, N_PROPERTIES, obj_properties
	);

	node_class->get_value = NULL;
}
static void
gatui_node_init(
		GATUINode* const self __unused
		) {
	//GATUINodePrivate* const priv = gatui_node_get_instance_private(self);
}


GATUITree*
gatui_node_get_root(
		GATUINode* const self
		) {
	g_return_val_if_fail(GATUI_IS_NODE(self), NULL);
	GATUINodePrivate* const priv = gatui_node_get_instance_private(self);
	return priv->root;
}

char*
gatui_node_to_path(
		GATUINode* const self
		) {
	g_return_val_if_fail(GATUI_IS_NODE(self), NULL);
	GATUINodePrivate* const priv = gatui_node_get_instance_private(self);
	return atui_node_to_path(priv->atui);
}

GVariantType const*
gatui_node_get_gvariant_type(
		GATUINode* const self
		) {
	g_return_val_if_fail(GATUI_IS_NODE(self), NULL);
	GATUINodePrivate* const priv = gatui_node_get_instance_private(self);
	return priv->capsule_type;
}

GVariant*
gatui_node_get_value(
		GATUINode* const self
		) {
	g_return_val_if_fail(GATUI_IS_NODE(self), NULL);

	GATUINodePrivate* const priv = gatui_node_get_instance_private(self);
	GATUINodeClass* const nodeclass = GATUI_NODE_GET_CLASS(self);
	return nodeclass->get_value(self, priv->capsule_type);
}


char*
gatui_node_to_base64(
		GATUINode* const self,
		bool const leaves_package
		) {
	// TODO take enum gatui_b64_target instead of bool leaves_package
	// contig; leaves_package; value
	g_return_val_if_fail(GATUI_IS_NODE(self), NULL);

	GATUINodePrivate* const priv = gatui_node_get_instance_private(self);
	GATUINodeClass* const nodeclass = GATUI_NODE_GET_CLASS(self);
	atui_node const* const atui = priv->atui;

	GVariant* val;
	uint16_t num_segments;
	enum gatui_b64_target target;

	if (leaves_package) {
		return NULL;
		/* TODO: pull prefer_contiguous and num_copyable_leaves into node
		if (atui->branch.prefer_contiguous
				|| !atui->branch.num_copyable_leaves
				) {
			return NULL;
		}
		gatui_node_get_leaves_memory_package(self, &val, &num_segments);
		target = B64_BRANCH_LEAVES;
		*/
	} else { // contiguous
		if (!atui->num_bytes) {
			return NULL;
		}
		target = B64_BRANCH_CONTIGUOUS;
		num_segments = 1;
		GVariantType* const contiguous_type = g_variant_type_new("ay");
		val = nodeclass->get_value(self, contiguous_type);
		free(contiguous_type);
	}
	char* const b64_text = b64_packet_encode(val, target, num_segments);

	g_variant_unref(val);
	return b64_text;
}

GListModel*
leaves_treelist_generate_children_2(
		gpointer const selfptr,
		gpointer const user_data __unused
		) {
// GtkTreeListModelCreateModelFunc for leaves
	GATUINodePrivate* const priv = gatui_node_get_instance_private(GATUI_NODE(
		selfptr
	));
	if (priv->num_leaves) {
		GListStore* const children = g_list_store_new(GATUI_TYPE_LEAF);
		g_list_store_splice(children, 0,0,
			(void**)priv->leaves, priv->num_leaves
		);
		return G_LIST_MODEL(children);
	} else {
		return NULL;
	}
}

char const*
gatui_node_get_name(
		GATUINode* const self
		) {
	g_return_val_if_fail(GATUI_IS_NODE(self), NULL);
	GATUINodePrivate* const priv = gatui_node_get_instance_private(self);
	return priv->atui->name;
}
char const*
gatui_node_get_description(
		GATUINode* const self,
		enum i18n_languages const lang
		) {
	g_return_val_if_fail(GATUI_IS_NODE(self), NULL);
	GATUINodePrivate* const priv = gatui_node_get_instance_private(self);
	return priv->atui->description[lang];
}

size_t
gatui_node_get_region_bounds(
		GATUINode* const self,
		size_t* start,
		size_t* end
		) {
	g_return_val_if_fail(GATUI_IS_NODE(self), 0);
	GATUINodePrivate* const priv = gatui_node_get_instance_private(self);

	atui_node const* const atui = priv->atui;
	if (atui->num_bytes) {
		size_t bios_size;
		void const* const bios = gatui_tree_get_bios_pointer(
			priv->root, &bios_size
		);
		ptrdiff_t const offset_start = atui->data.data - bios;
		size_t const offset_end = offset_start + atui->num_bytes - 1;
		assert(0 <= offset_start);
		assert(offset_end < bios_size);
		if (start) {
			*start = offset_start;
		}
		if (end) {
			*end = offset_end;
		}
	}

	return atui->num_bytes;
}



GATUILeaf**
_gatui_node_get_leaf_array(
		GATUINode* const self
		) {
	g_return_val_if_fail(GATUI_IS_NODE(self), NULL);
	GATUINodePrivate* const priv = gatui_node_get_instance_private(self);
	return priv->leaves;
}
