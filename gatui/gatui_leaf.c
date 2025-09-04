#include "standard.h"
#include "gatui_private.h"


static GVariant*
_gatui_leaf_get_value(
		GATUINode* self
		);
static bool
_gatui_leaf_set_value(
		GATUINode* self,
		GVariant* value
		);

union variant_dock { // g_variant loading/unloading dock
	uint64_t  u64;
	int64_t   s64;
	float64_t f64;
};

struct _GATUILeaf {
	GATUINode parent_instance;

	atui_node* atui;
	bool has_textable_value;
	GtkSelectionModel* enum_model;
};
G_DEFINE_TYPE(GATUILeaf, gatui_leaf, GATUI_TYPE_NODE)


static void
gatui_leaf_dispose(
		GObject* const object
		) {
	GATUILeaf* const self = GATUI_LEAF(object);

	if (self->enum_model) {
		g_object_unref(self->enum_model);
		self->enum_model = NULL;
	}

	G_OBJECT_CLASS(gatui_leaf_parent_class)->dispose(object);
}


static void
gatui_leaf_class_init(
		GATUILeafClass* const leaf_class
		) {
	GObjectClass* const object_class = G_OBJECT_CLASS(leaf_class);
	object_class->dispose = gatui_leaf_dispose;

	GATUINodeClass* const node_class = GATUI_NODE_CLASS(leaf_class);
	node_class->get_value = _gatui_leaf_get_value;
	node_class->set_value = _gatui_leaf_set_value;
}
static void
gatui_leaf_init(
		GATUILeaf* const self __unused
		) {
}

inline static void
set_typestr(
		atui_node const* const leaf,
		char* typestr
		) {
	struct atui_leaf_type const* const type = &(leaf->leaf.type);
	if (type->radix) {
		if (type->fraction) {
			 *typestr = 'd';
		} else {
			if (type->fancy == ATUI_ARRAY) {
				*typestr = 'a';
				typestr++;
			}
			if (type->signed_num) {
				switch (leaf->leaf.total_bits) {
					case  8: *typestr = 'y'; break;
					case 16: *typestr = 'n'; break;
					case 32: *typestr = 'i'; break;
					case 64: *typestr = 'x'; break;
					case 48:
					case 24: typestr[0] = 'a'; typestr[1] = 'y'; break;
					default: assert(0); break;
				}
			} else  {
				switch (leaf->leaf.total_bits) {
					case  8: *typestr = 'y'; break;
					case 16: *typestr = 'q'; break;
					case 32: *typestr = 'u'; break;
					case 64: *typestr = 't'; break;
					case 48:
					case 24: typestr[0] = 'a'; typestr[1] = 'y'; break;
					default: assert(0); break;
				}
			}
		}
	} else if ((type->fancy==ATUI_STRING) || (ATUI_ARRAY==type->fancy)) {
		*typestr = 's';
	} else if (leaf->num_bytes) { // raw data
		typestr[0] = 'a';
		typestr[1] = 'y';
	} else {
		// no type
	}
}


GATUILeaf*
gatui_leaf_new(
		atui_node* const leaf,
		GATUITree* const root
		) {
	g_return_val_if_fail(NULL == leaf->self, NULL);

	char typestr[GATUI_TYPESTR_LEN] = {};
	set_typestr(leaf, typestr);
	GATUILeaf* const self = g_object_new(GATUI_TYPE_LEAF,
		"atui", leaf,
		"typestr", typestr,
		NULL // get parent from atui; and root from parent
	);

	self->atui = leaf;

	if (leaf->leaf.enum_options) {
		GtkSelectionModel* const* const enum_models_cache =
			gatui_tree_get_enum_models_cache(root);
		self->enum_model = ( // the index is the same in both arrays
			enum_models_cache[leaf->leaf.enum_options - ATUI_ENUM_ARRAY]
		);
		g_object_ref(self->enum_model);
	}

	struct atui_leaf_type const* const type = &(leaf->leaf.type);
	self->has_textable_value = (
		type->radix || ATUI_STRING==type->fancy || ATUI_ARRAY==type->fancy
	);

	return self;
}

atui_node const*
gatui_leaf_get_atui(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	return self->atui;
}


static GVariant*
_gatui_leaf_get_value(
		GATUINode* const nodeself
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(nodeself), NULL);

	GATUILeaf* const self = GATUI_LEAF(nodeself);
	atui_node const* const leaf = self->atui;
	struct atui_leaf_type const* const type = &(leaf->leaf.type);

	size_t num_bytes;
	void* valcopy;

	if ((ATUI_STRING==type->fancy)
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
		gatui_node_get_capsule_type(nodeself),
		valcopy, num_bytes,
		false,
		free, valcopy
	);

	return value;
}
static bool
_gatui_leaf_set_value(
		GATUINode* const nodeself,
		GVariant* const value
		) {
	// generalise the g_variant_type_new stuff in get_value to be a part of the
	// object instance
	g_return_val_if_fail(GATUI_IS_LEAF(nodeself), false);
	g_return_val_if_fail(value, false);

	GATUILeaf* const self = GATUI_LEAF(nodeself);
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
	bool const is_same_type = g_variant_is_of_type(
		value,  gatui_node_get_capsule_type(nodeself)
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
	} else if (is_same_type) {
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
	_gatui_node_emit_value_changed(GATUI_NODE(self));
	return true;
}

struct atui_leaf_type const*
gatui_leaf_get_atui_type(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	return &(self->atui->leaf.type);
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
	_gatui_node_emit_value_changed(GATUI_NODE(self));
}
char*
gatui_leaf_value_to_text(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
	g_return_val_if_fail(self->has_textable_value, NULL);

	return atui_leaf_to_text(self->atui);
}


GtkSelectionModel*
gatui_leaf_get_enum_menu_selection_model(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
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
	return atui_enum_entry_to_text(self->atui, enum_entry);
}
char*
gatui_leaf_enum_val_to_text(
		GATUILeaf* const self,
		struct atui_enum_entry const* const enum_entry
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), NULL);
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
		_gatui_node_emit_value_changed(GATUI_NODE(self));
		return true;
	}
	return false;
}

int16_t
gatui_leaf_enum_entry_get_possible_index(
		GATUILeaf* const self
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), -1);
	int64_t val;
	if (self->atui->leaf.type.signed_num) {
		val = atui_leaf_get_val_signed(self->atui);
	} else {
		val = atui_leaf_get_val_unsigned(self->atui);
	}
	return atui_enum_lsearch(self->atui->leaf.enum_options, val);
}

size_t
gatui_leaf_get_bitfield_size(
		GATUILeaf* const self,
		size_t* const start,
		size_t* const end
		) {
	g_return_val_if_fail(GATUI_IS_LEAF(self), 0);
	struct atui_leaf const* const meta = &(self->atui->leaf);
	g_return_val_if_fail(_ATUI_BITCHILD == meta->type.fancy, 0);

	if (start) {
		*start = meta->bitfield_lo;
	}
	if (end) {
		*end = meta->bitfield_hi;
	}

	return (meta->bitfield_hi - meta->bitfield_lo) +1;
}


void
gatui_regex_search_recurse_leaf(
		GATUILeaf* const leaf,
		GListStore* const model,
		GRegex* const pattern,
		struct gatui_search_flags const* const flags
		) {
	/*
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
	*/
}
