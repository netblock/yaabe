#include "gatui_private.h"

enum {
	VALUE_CHANGED,
	LAST_SIGNAL
};
static guint gatui_signals[LAST_SIGNAL] = {0};

struct _GATUILeaf {
	GObject parent_instance;

	atui_leaf* atui;
	GATUILeaf** child_leaves;
	uint16_t num_child_leaves;
	// may be different from atui_leaf.num_child_leaves due to ATUI_SUBONLY

	GtkSelectionModel* enum_model;
};
G_DEFINE_TYPE(GATUILeaf, gatui_leaf, G_TYPE_OBJECT)


static void
gatui_leaf_dispose(
		GObject* const object
		) {
	GATUILeaf* const self = GATUI_LEAF(object);
	if (self->child_leaves) {
		GATUILeaf** const child_leaves = self->child_leaves;
		self->child_leaves = NULL;
		uint16_t const num_leaves = self->num_child_leaves;
		for (uint16_t i = 0; i < num_leaves; i++) {
			g_object_unref(child_leaves[i]);
		}
		free(child_leaves);
	}
	if (self->enum_model) {
		g_object_unref(self->enum_model);
		self->enum_model = NULL;
	}

	self->atui->self = NULL; // weak reference

	G_OBJECT_CLASS(gatui_leaf_parent_class)->dispose(object);
}

static void
gatui_leaf_class_init(
		GATUILeafClass* const leaf_class
		) {
	GObjectClass* const object_class = G_OBJECT_CLASS(leaf_class);
	object_class->dispose = gatui_leaf_dispose;

	gatui_signals[VALUE_CHANGED] = g_signal_new(
		"value-changed",
		G_TYPE_FROM_CLASS(leaf_class),
		(G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE),
		0,
		NULL, NULL,
		NULL,
		G_TYPE_NONE, 0
	);
}
static void
gatui_leaf_init(
		GATUILeaf* const self
		) {
	self->child_leaves = NULL;
	self->num_child_leaves = 0;
	self->enum_model = NULL;
}


GATUILeaf*
gatui_leaf_new(
		atui_leaf* const leaf
		) {
	g_return_val_if_fail(leaf->self == NULL, NULL);
	GATUILeaf* const self = g_object_new(GATUI_TYPE_LEAF, NULL);
	self->atui = leaf;
	leaf->self = self;

	if (leaf->num_child_leaves) {
		GListStore* const child_list = g_list_store_new(GATUI_TYPE_LEAF);
		GListModel* const child_model = G_LIST_MODEL(child_list);
		atui_leaves_to_gliststore( // handles ATUI_SUBONLY
			child_list, leaf->child_leaves, leaf->num_child_leaves
		);

		uint16_t const num_children = g_list_model_get_n_items(child_model);
		self->num_child_leaves = num_children;
		self->child_leaves = malloc(num_children * sizeof(GATUILeaf*));
		for (uint16_t i = 0; i < num_children; i++) {
			// g_list_model_get_item refs for us
			self->child_leaves[i] = g_list_model_get_item(child_model, i);
		}
		g_object_unref(child_model);
	}

	return self;
}

GListModel*
gatui_leaf_generate_children_model(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);

	if (self->num_child_leaves) {
		GListStore* const children = g_list_store_new(GATUI_TYPE_LEAF);
		g_list_store_splice(children, 0,0,
			(void**)self->child_leaves, self->num_child_leaves
		);
		return G_LIST_MODEL(children);
	}
	return NULL;
}

enum atui_type
gatui_leaf_get_atui_type(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), false);
	return self->atui->type;
}
uint32_t
gatui_leaf_num_bytes(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), 0);
	return self->atui->num_bytes;
}

GVariant*
gatui_leaf_get_value(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	atui_leaf const* const leaf = self->atui;

	gchar typestr[4] = {0};
	if ((leaf->type & ATUI_ARRAY) && (leaf->type & ATUI_ANY)) {
		typestr[0] = 'a';
		switch (leaf->total_bits) {
			case 8:typestr[1] = 'y'; break;
			case 16: typestr[1] = 'q'; break;
			case 32: typestr[1] = 'u'; break;
			case 64: typestr[1] = 't'; break;
			default: assert(0); break;
		}
	} else if (leaf->type & (ATUI_STRING|ATUI_ARRAY)) {
		typestr[0] = 's';
	} else if (leaf->type & ATUI_ANY) {
		if (leaf->type & ATUI_FRAC) {
			typestr[0] = 'd';
		} else if (leaf->type & ATUI_SIGNED) {
			switch (leaf->total_bits) {
				case 8:  typestr[0] = 'y'; break;
				case 16: typestr[0] = 'n'; break;
				case 32: typestr[0] = 'i'; break;
				case 64: typestr[0] = 'x'; break;
				default: assert(0); break;
			}
		} else {
			switch (leaf->total_bits) {
				case 8:  typestr[0] = 'y'; break;
				case 16: typestr[0] = 'q'; break;
				case 32: typestr[0] = 'u'; break;
				case 64: typestr[0] = 't'; break;
				default: assert(0); break;
			}
		}
	} else {
		return NULL;
	}

	const void* valptr;
	union { // won't work on big-endian, but I'm not supporting BE.
		uint64_t u64;
		int64_t  s64;
	} bfval;
	if (leaf->type & _ATUI_BITCHILD) {
		valptr = &bfval;
		if (leaf->type & ATUI_SIGNED) {
			bfval.s64 = atui_leaf_get_val_signed(leaf);
		} else {
			bfval.u64 = atui_leaf_get_val_unsigned(leaf);
		}
	} else {
		valptr = leaf->val;
	}

	GVariantType* const type = g_variant_type_new(typestr);
	GVariant* const data = g_variant_new_from_data(
		type,
		valptr, leaf->num_bytes,
		false, NULL, NULL
	);
	g_variant_type_free(type);

	return data;
};

void
gatui_leaf_set_value(
		GATUILeaf* const self,
		GVariant const* const value
		) {
	// generalise the g_variant_type_new stuff in get_value to be a part of the
	// object instance
	g_signal_emit(self, gatui_signals[VALUE_CHANGED], 0);
}


GtkSelectionModel*
gatui_leaf_get_enum_menu_selection_model(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	atui_leaf* const leaf = self->atui;
	g_return_val_if_fail(NULL != leaf->enum_options, NULL);

	if (NULL == self->enum_model) {
		GListStore* list = g_list_store_new(G_TYPE_OBJECT);
		struct atui_enum const* const atuienum = leaf->enum_options;
		GObject* gobj_child;

		for (uint8_t i=0; i < atuienum->num_entries; i++) {
			gobj_child = g_object_new(G_TYPE_OBJECT, NULL);
			g_object_set_data(gobj_child, "enum",
				(struct atui_enum_entry*) &(atuienum->enum_array[i]) // de-const
			);
			g_object_set_data(gobj_child, "leaf", self->atui); // TODO depricate
			g_list_store_append(list, gobj_child);
			g_object_unref(gobj_child);
		}
		GtkSingleSelection* const enum_model = gtk_single_selection_new(
			G_LIST_MODEL(list)
		);
		gtk_single_selection_set_can_unselect(enum_model, true);
		gtk_single_selection_set_autoselect(enum_model, false);
		self->enum_model = GTK_SELECTION_MODEL(enum_model);
	}

	return self->enum_model;
}

atui_leaf*
gatui_leaf_get_atui(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	return self->atui;
}
