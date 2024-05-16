#include "gatui_private.h"

enum {
	VALUE_CHANGED,
	LAST_SIGNAL
};
static guint gatui_signals[LAST_SIGNAL] = {0};

struct _GATUILeaf {
	GObject parent_instance;

	atui_leaf* atui;
	GATUILeaf* parent_leaf;

	// for inter-family signal propagation
	gulong parent_number; 
	gulong* phone_book;

	uint16_t num_child_leaves;
	GATUILeaf** child_leaves;
	// may be different from atui_leaf.num_child_leaves due to ATUI_SUBONLY

	GVariantType* capsule_type;
	GtkSelectionModel* enum_model;
};
G_DEFINE_TYPE(GATUILeaf, gatui_leaf, G_TYPE_OBJECT)


static void
gatui_leaf_dispose(
		GObject* const object
		) {
	GATUILeaf* const self = GATUI_LEAF(object);

	// no need to kill the val-changed connection with parent leaf because
	// parent holds ref; we wouldn't be here if parent is alive.

	if (self->child_leaves) {
		GATUILeaf** const child_leaves = self->child_leaves;
		self->child_leaves = NULL;
		uint16_t const num_leaves = self->num_child_leaves;
		for (uint16_t i = 0; i < num_leaves; i++) {
			child_leaves[i]->parent_leaf = NULL;
			g_signal_handler_disconnect(child_leaves[i], self->phone_book[i]);
			g_object_unref(child_leaves[i]);
		}
		free(child_leaves);
		free(self->phone_book);
		self->phone_book = NULL;
	}
	if (self->enum_model) {
		g_object_unref(self->enum_model);
		self->enum_model = NULL;
	}
	if (self->capsule_type) {
		g_free(self->capsule_type);
		self->capsule_type = NULL;
	}

	self->atui->self = NULL; // weak reference

	G_OBJECT_CLASS(gatui_leaf_parent_class)->dispose(object);
}

static void
emit_val_changed(
		GATUILeaf* const self
		) {
	// make sure everyone in the family tree understands there exists a change,
	// but don't allow the parent or child to tell self that a family member
	// (which happens to be self) made a change.

	// opt out of everyone's mailing lists
	if (self->parent_leaf) {
		g_signal_handler_block(self->parent_leaf, self->parent_number);
	}
	for (uint16_t i=0; i < self->num_child_leaves; i++) {
		g_signal_handler_block(self->child_leaves[i], self->phone_book[i]);
	}

	g_signal_emit(self, gatui_signals[VALUE_CHANGED], 0); // spread a rumour

	// opt back in
	if (self->parent_leaf) {
		g_signal_handler_unblock(self->parent_leaf, self->parent_number);
	}
	for (uint16_t i=0; i < self->num_child_leaves; i++) {
		g_signal_handler_unblock(self->child_leaves[i], self->phone_book[i]);
	}
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
	self->parent_leaf = NULL;	

	self->parent_number = 0;
	self->phone_book = NULL;

	self->child_leaves = NULL;
	self->num_child_leaves = 0;

	self->capsule_type = NULL;
	self->enum_model = NULL;
}

inline static GVariantType*
get_capsule_type(
		atui_leaf const* const leaf
		) {
	gchar typestr[4] = {0};
	union atui_type const a_type = leaf->type;
	if ((a_type.fancy == ATUI_ARRAY) && (a_type.radix)) {
		typestr[0] = 'a';
		switch (leaf->total_bits) {
			case 8:typestr[1] = 'y'; break;
			case 16: typestr[1] = 'q'; break;
			case 32: typestr[1] = 'u'; break;
			case 64: typestr[1] = 't'; break;
			default: assert(0); break;
		}
	} else if ((a_type.fancy==ATUI_STRING) || (a_type.fancy==ATUI_ARRAY)) {
		typestr[0] = 's';
	} else if (a_type.radix) {
		if (a_type.fraction) {
			typestr[0] = 'd';
		} else if (a_type.signed_num) {
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
	} else if (leaf->num_bytes) { // raw data
		typestr[0] = 'a';
		typestr[1] = 'y';
	} else {
		return NULL;
	}
	return g_variant_type_new(typestr);
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
	
		self->phone_book = malloc(num_children * sizeof(gulong));

		GATUILeaf* child;
		for (uint16_t i = 0; i < num_children; i++) {
			child = g_list_model_get_item(child_model, i); // refs for us
			self->child_leaves[i] = child;

			self->phone_book[i] = g_signal_connect_data(child,
				"value-changed", G_CALLBACK(emit_val_changed), self,
				NULL, G_CONNECT_SWAPPED
			);

			child->parent_leaf = self;
			child->parent_number = g_signal_connect_data(self,
				"value-changed", G_CALLBACK(emit_val_changed), child,
				NULL, G_CONNECT_SWAPPED
			);
		}

		g_object_unref(child_model);
	}

	self->capsule_type = get_capsule_type(leaf);

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

union atui_type
gatui_leaf_get_atui_type(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), (union atui_type){0});
	return self->atui->type;
}
uint32_t
gatui_leaf_num_bytes(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), 0);
	return self->atui->num_bytes;
}

GVariantType const*
gatui_leaf_get_gvariant_type(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	return self->capsule_type;
}

GVariant*
gatui_leaf_get_value(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);


	if (self->capsule_type) {
		atui_leaf const* const leaf = self->atui;

		union {
			uint64_t u64;
			int64_t  s64;
		} bfval;
		const void* valptr;
		if (leaf->type.fancy == _ATUI_BITCHILD) {
			valptr = &bfval;
			if (leaf->type.signed_num) {
				bfval.s64 = atui_leaf_get_val_signed(leaf);
			} else {
				bfval.u64 = atui_leaf_get_val_unsigned(leaf);
			}
		} else {
			valptr = leaf->val;
		}
		// g_variant_new_from_data is effectively a pointer container so we
		// need to duplicate the data and free on notify
		void* const valcopy = malloc(leaf->num_bytes);
		memcpy(valcopy, valptr, leaf->num_bytes);
		return g_variant_new_from_data(
			// won't work on big-endian, but I'm not supporting BE.
			self->capsule_type,
			valcopy, leaf->num_bytes,
			false,
			free_notify, valcopy
		);
	}
	return NULL;
};

bool
gatui_leaf_set_value(
		GATUILeaf* const self,
		GVariant* const value
		) {
	// generalise the g_variant_type_new stuff in get_value to be a part of the
	// object instance
	g_return_val_if_fail(GATUI_IS_LEAF(self), false);
	g_return_val_if_fail(NULL != value, false);


	atui_leaf const* const leaf = self->atui;
	if (g_variant_is_of_type(value, self->capsule_type)
			&& (leaf->type.fancy != _ATUI_BITCHILD)
			) {
		if (leaf->type.fancy == ATUI_STRING) {
			size_t n;
			char8_t const* const input_str = g_variant_get_string(value, &n);
			char8_t* const buffer = malloc(n + 1);
			buffer[n] = '\0';
			memcpy(buffer, input_str, n);
			atui_leaf_from_text(leaf, buffer); // has special bounds checks
			free(buffer);
			goto success_exit;
		} else {
			void const* const input_data = g_variant_get_data(value);
			assert(input_data);

			if (input_data) {
				// won't work on big-endian, but I'm not supporting BE.
				memcpy(self->atui->u8, input_data, self->atui->num_bytes);
				goto success_exit;
			}
		}
	} else { // loose compliance
		char8_t const* const typestr = g_variant_get_type_string(value);
		if ('a' == typestr[0]) {
			if (char_in_string(typestr[1], "ynqiuxt")) {
				// un/signed 8-bit~64-bit
				void const* const input_data = g_variant_get_data(value);
				assert(input_data);
				if (input_data) {
					memcpy(self->atui->u8, input_data, self->atui->num_bytes);
					goto success_exit;
				}
			}
		} else {
			union {
				uint64_t u64;
				int64_t  s64;
			} val;
			switch (typestr[0]) {
				case 'y': val.u64 = g_variant_get_byte(value);   break;
				case 'n': val.s64 = g_variant_get_int16(value);  break;
				case 'q': val.u64 = g_variant_get_uint16(value); break;
				case 'i': val.s64 = g_variant_get_int32(value);  break;
				case 'u': val.u64 = g_variant_get_uint32(value); break;
				case 'x': val.s64 = g_variant_get_int64(value);  break;
				case 't': val.u64 = g_variant_get_uint64(value); break;
				default: assert(0); goto fail_exit;
			}
			if (leaf->type.signed_num) {
				atui_leaf_set_val_signed(leaf, val.s64);
			} else {
				atui_leaf_set_val_unsigned(leaf, val.u64);
			}
			goto success_exit;
		}
	}

	fail_exit:
	return false;

	success_exit:
	emit_val_changed(self);
	return true;
}

void
gatui_leaf_set_value_from_text(
		GATUILeaf* self,
		char8_t const* text
		) {
	g_return_if_fail(GATUI_IS_LEAF(self));
	atui_leaf_from_text(self->atui, text);
	emit_val_changed(self);
}
char8_t*
gatui_leaf_value_to_text(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	return atui_leaf_to_text(self->atui);
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
char8_t*
gatui_leaf_enum_entry_to_text(
		GATUILeaf* const self,
		struct atui_enum_entry const* const enum_entry
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	return atui_enum_entry_to_text(self->atui, enum_entry);
}
bool
gatui_leaf_enum_entry_sets_value(
		GATUILeaf* const self,
		struct atui_enum_entry const* const enum_entry
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), false);
	g_return_val_if_fail(NULL != self->atui->enum_options, false);

	struct atui_enum const* const enum_set = self->atui->enum_options;
	struct atui_enum_entry const* const start = enum_set->enum_array;
	struct atui_enum_entry const* const end = start + enum_set->num_entries;

	if ((start <= enum_entry) && (enum_entry < end)) {
		if (self->atui->type.signed_num) {
			atui_leaf_set_val_signed(self->atui, enum_entry->val);
		} else {
			atui_leaf_set_val_unsigned(self->atui, enum_entry->val);
		}
		emit_val_changed(self);
		return true;
	}
	return false;
};

int16_t
gatui_leaf_enum_entry_get_possible_index(
		GATUILeaf* const self
		) {
	int64_t val;
	if (self->atui->type.signed_num) {
		val = atui_leaf_get_val_signed(self->atui);
	} else {
		val = atui_leaf_get_val_unsigned(self->atui);
	}
	return atui_enum_lsearch(self->atui->enum_options, val);
}

atui_leaf*
gatui_leaf_get_atui(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	return self->atui;
}
