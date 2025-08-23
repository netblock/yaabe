#include "standard.h"
#include "gatui_private.h"

union variant_dock { // g_variant loading/unloading dock
	uint64_t  u64;
	int64_t   s64;
	float64_t f64;
};

enum {
	VALUE_CHANGED,
	LAST_SIGNAL
};
static guint gatui_signals[LAST_SIGNAL] = {0};

struct _GATUILeaf {
	GObject parent_instance;

	GATUITree* root;

	atui_node* atui;
	GATUILeaf* parent_leaf;

	// for inter-family signal propagation
	gulong parent_number;
	gulong* phone_book;

	GATUILeaf** child_leaves;
	uint16_t num_child_leaves;
	// may be different from atui_node.num_child_leaves due to ATUI_SUBONLY

	// if the leaf can support getting/setting data, capsule_type will be
	// non-null
	char typestr[GATUI_TYPESTR_LEN];
	GVariantType* capsule_type;
	bool has_textable_value;

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

	if (self->root) {
		g_object_unref(self->root);
		self->root = NULL;
	}

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
	self->parent_leaf = NULL;

	self->parent_number = 0;
	self->phone_book = NULL;

	self->child_leaves = NULL;
	self->num_child_leaves = 0;

	memset(self->typestr, 0, sizeof(self->typestr));
	self->capsule_type = NULL;
	self->enum_model = NULL;
}

inline static GVariantType*
get_capsule_type(
		GATUILeaf* const self
		) {
	atui_node const* const leaf = self->atui;
	char* const typestr = self->typestr;
	char* typestrptr = typestr;

	struct atui_leaf_type const* const type = &(leaf->leaf.type);
	if (type->radix) {
		if (type->fraction) {
			 typestr[0] = 'd';
		} else {
			if (type->fancy == ATUI_ARRAY) {
				typestr[0] = 'a';
				typestrptr++;
			}
			if (type->signed_num) {
				switch (leaf->leaf.total_bits) {
					case  8: *typestrptr = 'y'; break;
					case 16: *typestrptr = 'n'; break;
					case 32: *typestrptr = 'i'; break;
					case 64: *typestrptr = 'x'; break;
					case 48:
					case 24: typestr[0] = 'a'; typestr[1] = 'y'; break;
					default: assert(0); break;
				}
			} else  {
				switch (leaf->leaf.total_bits) {
					case  8: *typestrptr = 'y'; break;
					case 16: *typestrptr = 'q'; break;
					case 32: *typestrptr = 'u'; break;
					case 64: *typestrptr = 't'; break;
					case 48:
					case 24: typestr[0] = 'a'; typestr[1] = 'y'; break;
					default: assert(0); break;
				}
			}
		}
	} else if ((type->fancy==ATUI_STRING) || (ATUI_ARRAY==type->fancy)) {
		typestr[0] = 's';
	} else if (leaf->num_bytes) { // raw data
		typestr[0] = 'a';
		typestr[1] = 'y';
	} else {
		return NULL;
	}
	assert(sizeof(self->typestr) > strlen(typestr));
	return g_variant_type_new(typestr);
}

void
gatui_leaf_emit_val_changed(
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

GATUILeaf*
gatui_leaf_new(
		atui_node* const leaf,
		GATUITree* const root
		) {
	g_return_val_if_fail(leaf->self == NULL, NULL);
	GATUILeaf* const self = g_object_new(GATUI_TYPE_LEAF, NULL);
	self->atui = leaf;
	leaf->self = self;

	g_object_ref(root);
	self->root = root;

	if (leaf->leaf.enum_options) {
		GtkSelectionModel* const* const enum_models_cache =
			gatui_tree_get_enum_models_cache(root);
		self->enum_model = ( // the index is the same in both arrays
			enum_models_cache[leaf->leaf.enum_options - ATUI_ENUM_ARRAY]
		);
		g_object_ref(self->enum_model);
	}

	if (leaf->leaves.count) {
		uint16_t const num_child_leaves = leaf->leaves.count;

		self->num_child_leaves = num_child_leaves;
		self->child_leaves = cralloc(num_child_leaves * sizeof(GATUILeaf*));
		self->phone_book = cralloc(num_child_leaves * sizeof(gulong));

		for (uint16_t i = 0; i < num_child_leaves; i++) {
			GATUILeaf* child = gatui_leaf_new(&(leaf->leaves.nodes[i]), root);
			self->child_leaves[i] = child;

			self->phone_book[i] = g_signal_connect_data(child, "value-changed",
				G_CALLBACK(gatui_leaf_emit_val_changed), self,
				NULL, G_CONNECT_SWAPPED
			);

			child->parent_leaf = self;
			child->parent_number = g_signal_connect_data(self, "value-changed",
				G_CALLBACK(gatui_leaf_emit_val_changed), child,
				NULL, G_CONNECT_SWAPPED
			);
		}
	}

	self->capsule_type = get_capsule_type(self);
	struct atui_leaf_type const* const type = &(leaf->leaf.type);
	self->has_textable_value = (
		type->radix || ATUI_STRING==type->fancy || ATUI_ARRAY==type->fancy
	);

	return self;
}

GATUITree*
gatui_leaf_get_root(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	return self->root;
}

GListModel*
leaves_treelist_generate_children(
		gpointer const parent_leaf,
		gpointer const user_data __unused
		) {
// GtkTreeListModelCreateModelFunc for leaves
	GATUILeaf* const self = parent_leaf;
	if (self->num_child_leaves) {
		GListStore* const children = g_list_store_new(GATUI_TYPE_LEAF);
		g_list_store_splice(children, 0,0,
			(void**)self->child_leaves, self->num_child_leaves
		);
		return G_LIST_MODEL(children);
	} else {
		return NULL;
	}
}


size_t
gatui_leaf_get_region_bounds(
		GATUILeaf* const self,
		size_t* start,
		size_t* end
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), 0);

	atui_node const* const leaf = self->atui;
	if (leaf->num_bytes) {
		size_t bios_size;
		void const* const bios = gatui_tree_get_bios_pointer(
			self->root, &bios_size
		);
		ptrdiff_t const offset_start = leaf->data.data - bios;
		size_t const offset_end = offset_start + leaf->num_bytes - 1;
		assert(0 <= offset_start);
		assert(offset_end < bios_size);
		if (start) {
			*start = offset_start;
		}
		if (end) {
			*end = offset_end;
		}
	}

	return leaf->num_bytes;
}


GVariantType const*
gatui_leaf_get_gvariant_type(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), NULL);
	return self->capsule_type;
}

GVariant*
gatui_leaf_get_value(
		GATUILeaf* const self,
		bool const raw_data
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), NULL);
	g_return_val_if_fail(self->capsule_type, NULL);

	atui_node const* const leaf = self->atui;
	struct atui_leaf_type const* const type = &(leaf->leaf.type);

	
	GVariantType* capsule_type = self->capsule_type;
	size_t num_bytes;
	void* valcopy;

	if (raw_data) {
		num_bytes = leaf->num_bytes;
		valcopy = cralloc(num_bytes);
		memcpy(valcopy, leaf->data.data, num_bytes);
		capsule_type = g_variant_type_new("ay");
	} else if ((ATUI_STRING==type->fancy)
		|| ((ATUI_ARRAY==type->fancy) && (ATUI_NAN==type->radix))
		) {
		valcopy = gatui_leaf_value_to_text(self);
		num_bytes = leaf->leaf.array_size + 1;
	} else {
		union variant_dock conv_val;
		const void* valptr = &conv_val;
		if (_ATUI_BITCHILD == type->fancy) {
			if (type->signed_num) {
				conv_val.s64 = atui_leaf_get_val_signed(leaf);
			} else {
				conv_val.u64 = atui_leaf_get_val_unsigned(leaf);
			}
			num_bytes = leaf->num_bytes;
		} else if (type->radix && type->fraction) {
			conv_val.f64 = atui_leaf_get_val_fraction(leaf);
			num_bytes = sizeof(conv_val);
		} else {
			valptr = leaf->data.data;
			num_bytes = leaf->num_bytes;
		}
		valcopy = cralloc(num_bytes);
		memcpy(valcopy, valptr, num_bytes);
	}
	// g_variant_new_from_data is effectively a pointer container so we
	// need to duplicate the data and free on notify
	GVariant* const value = g_variant_new_from_data(
		// won't work on big-endian, but I'm not supporting BE.
		capsule_type,
		valcopy, num_bytes,
		false,
		(GDestroyNotify) free, valcopy
	);

	if (raw_data) {
		free(capsule_type);
	}

	return value;
}

bool
gatui_leaf_set_value(
		GATUILeaf* const self,
		GVariant* const value
		) {
	// generalise the g_variant_type_new stuff in get_value to be a part of the
	// object instance
	g_return_val_if_fail(GATUI_IS_LEAF(self), false);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), false);
	g_return_val_if_fail(NULL != value, false);
	g_return_val_if_fail(self->capsule_type, false);

	atui_node const* const leaf = self->atui;
	struct atui_leaf_type const* const type = &(leaf->leaf.type);

	void const* const input_data = g_variant_get_data(value);
	size_t const input_size = g_variant_get_size(value);
	char const* const typestr = g_variant_get_type_string(value);

	union variant_dock val;

	bool const both_are_integers = (
		char_in_string(typestr[0], "ynqiuxt")
		&& type->radix && (! type->fraction) && (1 == leaf->leaf.array_size)
	);
	if (both_are_integers) {
		switch (typestr[0]) {
			case 'y': val.u64 = g_variant_get_byte(value);   break;
			case 'n': val.s64 = g_variant_get_int16(value);  break;
			case 'q': val.u64 = g_variant_get_uint16(value); break;
			case 'i': val.s64 = g_variant_get_int32(value);  break;
			case 'u': val.u64 = g_variant_get_uint32(value); break;
			case 'x': val.s64 = g_variant_get_int64(value);  break;
			case 't': val.u64 = g_variant_get_uint64(value); break;
			default: goto fail_exit;
		}
		if (type->signed_num) {
			atui_leaf_set_val_signed(leaf, val.s64);
		} else {
			atui_leaf_set_val_unsigned(leaf, val.u64);
		}
		goto success_exit;
	} else if (0 == strcmp(typestr, self->typestr)) { // same type
		if ('s' == typestr[0]) { // string
			atui_leaf_from_text(leaf, input_data); // has special bounds checks
			goto success_exit;
		} else if ('a' == typestr[0]) {
			if (input_size != leaf->num_bytes) {
				goto fail_exit;
			}
			memcpy(leaf->data.u8, input_data, input_size);
			goto success_exit;
		} else if ('d' == typestr[0]) {
			atui_leaf_set_val_fraction(leaf, g_variant_get_double(value));
			goto success_exit;
		}
		assert(0); // should be unreachable
		goto fail_exit;
	} else if (typestr[0]=='a' && 'y'==typestr[1]) {
		if (input_size != leaf->num_bytes) {
			goto fail_exit;
		}
		memcpy(leaf->data.data, input_data, input_size);
		goto success_exit;
	}
	
	fail_exit:
	return false;

	success_exit:
	gatui_leaf_emit_val_changed(self);
	return true;
}

char*
gatui_leaf_value_to_base64(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), NULL);
	g_return_val_if_fail(self->capsule_type, NULL);

	GVariant* const val = gatui_leaf_get_value(self, false);
	char* const b64_text = b64_packet_encode(val, B64_LEAF, 1);
	g_variant_unref(val);
	return b64_text;
}
bool
gatui_leaf_value_from_base64(
		GATUILeaf* const self,
		char const* const b64_text,
		struct b64_header** const error_out
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), false);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), false);
	g_return_val_if_fail(b64_text, false);
	g_return_val_if_fail(self->capsule_type, false);

	struct b64_header* const header = b64_packet_decode(b64_text);
	if (NULL == header) {
		goto error_exit;
	}

	if (B64_LEAF != header->target) {
		goto error_exit;
	}

	GVariantType* const header_type = g_variant_type_new(header->typestr);
	GVariant* const new_val = g_variant_new_from_data(
		header_type,
		header->bytes, header->num_bytes,
		false,
		NULL, NULL
	);
	bool const success = gatui_leaf_set_value(self, new_val);
	free(header_type);
	g_variant_unref(new_val);
	if (!success) {
		goto error_exit;
	}

	//success_exit:
	free(header);
	return true;

	error_exit:
	if (error_out) {
		*error_out = header;
	} else {
		free(header);
	}
	return false;
}


bool
gatui_leaf_has_textable_value(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), false);
	return self->has_textable_value;
}

void
gatui_leaf_set_value_from_text(
		GATUILeaf* const self,
		char const* text
		) {
	g_return_if_fail(GATUI_IS_LEAF(self));
	g_return_if_fail(self->has_textable_value);
	atui_leaf_from_text(self->atui, text);
	gatui_leaf_emit_val_changed(self);
}
char*
gatui_leaf_value_to_text(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), NULL);
	g_return_val_if_fail(self->has_textable_value, NULL);

	return atui_leaf_to_text(self->atui);
}


GtkSelectionModel*
gatui_leaf_get_enum_menu_selection_model(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), NULL);
	atui_node* const leaf = self->atui;
	g_return_val_if_fail(NULL != leaf->leaf.enum_options, NULL);

	return self->enum_model;
}
char*
gatui_leaf_enum_entry_to_text(
		GATUILeaf* const self,
		struct atui_enum_entry const* const enum_entry
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), NULL);
	return atui_enum_entry_to_text(self->atui, enum_entry);
}
char*
gatui_leaf_enum_val_to_text(
		GATUILeaf* const self,
		struct atui_enum_entry const* const enum_entry
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), NULL);
	assert(self->atui->leaf.type.has_enum);

	char format[LEAF_SPRINTF_FORMAT_SIZE];
	size_t alloc_size = get_sprintf_format_from_leaf(format, self->atui);
	char* const valstr = cralloc(alloc_size + 1);
	sprintf(valstr, format, enum_entry->val);
	return valstr;
}
bool
gatui_leaf_enum_entry_sets_value(
		GATUILeaf* const self,
		struct atui_enum_entry const* const enum_entry
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), false);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), false);
	g_return_val_if_fail(NULL != self->atui->leaf.enum_options, false);

	struct atui_enum const* const enum_set = self->atui->leaf.enum_options;
	struct atui_enum_entry const* const start = enum_set->enum_array;
	struct atui_enum_entry const* const end = start + enum_set->num_entries;

	if ((start <= enum_entry) && (enum_entry < end)) {
		if (self->atui->leaf.type.signed_num) {
			atui_leaf_set_val_signed(self->atui, enum_entry->val);
		} else {
			atui_leaf_set_val_unsigned(self->atui, enum_entry->val);
		}
		gatui_leaf_emit_val_changed(self);
		return true;
	}
	return false;
}

int16_t
gatui_leaf_enum_entry_get_possible_index(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), -1);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), -1);
	int64_t val;
	if (self->atui->leaf.type.signed_num) {
		val = atui_leaf_get_val_signed(self->atui);
	} else {
		val = atui_leaf_get_val_unsigned(self->atui);
	}
	return atui_enum_lsearch(self->atui->leaf.enum_options, val);
}

char*
gatui_leaf_to_path(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), NULL);
	return atui_node_to_path(self->atui);
}

atui_node const*
gatui_leaf_get_atui(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	g_return_val_if_fail(GATUI_IS_TREE(self->root), NULL);
	return self->atui;
}


void
gatui_regex_search_recurse_leaf(
		GATUILeaf* const leaf,
		GListStore* const model,
		GRegex* const pattern,
		struct gatui_search_flags const* const flags
		) {
	atui_node* const atui = leaf->atui;
	struct atui_leaf_type const* const type = &(leaf->atui->leaf.type);
	GATUIRegexNode* node;
	GMatchInfo* match_info;
	bool matched;
	char* text = NULL; // may be freed

	if (GATUI_SEARCH_VALUES == flags->domain) {
		if (type->radix || ATUI_STRING==type->fancy || ATUI_ARRAY==type->fancy){
			text = gatui_leaf_value_to_text(leaf);
		}
	} else {
		text = atui->name;
	}
	if (text) {
		matched = g_regex_match(
			pattern, text, G_REGEX_MATCH_DEFAULT, &match_info
		);
		if (matched) {
			node = gatui_regex_node_new(
				G_OBJECT(leaf), match_info, text, true, flags
			);
			g_list_store_append(model, node);
			g_object_unref(node);
		}
		if (GATUI_SEARCH_VALUES == flags->domain) {
			free(text);
		}
		g_match_info_unref(match_info);
	}

	for (uint16_t i=0; i < atui->leaves.count; i++) {
		gatui_regex_search_recurse_leaf(
			leaf->child_leaves[i], model, pattern, flags
		);
	}
}
