/*
AtomTree iterable interface for UIs.

See ppatui.h for the metaprogramming and atui.h for general API.
*/

#include "standard.h"
#include "atui.h"
#include "atui_allocator.h"
#include <math.h>

#ifdef C2X_COMPAT
static constexpr char prefixes_int[][5] = {"", "%0", "0x%0", "0o%0", "0x%0"};
static constexpr char suffixes_uint[][4] = {"", "llu", "llX", "llo", "llX"};
static constexpr char suffixes_int[][4]  = {"", "lli", "llX", "llo", "llX"};
static constexpr uint8_t bases[] = {0, 10, 16, 8, 16};
#else
static constexpr char prefixes_int[][5] = {"", "%0", "0x%0", "0o%0", "0b%0"};
static constexpr char suffixes_uint[][4] = {"", "llu", "llX", "llo", "llb"};
static constexpr char suffixes_int[][4]  = {"", "lli", "llX", "llo", "llb"};
static constexpr uint8_t bases[] = {0, 10, 16, 8, 2};
#endif


void
atui_leaf_from_text(
		atui_node const* const leaf,
		char const* const text
		) {
// set the value of the leaf based on input text. Currently only support for
// numbers (including bitfields) and strings.
	assert(leaf->is_leaf);
	assert(leaf->data.input);

	union bios_data const data = leaf->data;
	struct atui_leaf const* const meta = &(leaf->leaf);
	uint32_t const array_size = meta->array_size;
	enum atui_leaf_type_radix const radix = meta->type.radix;
	enum atui_leaf_type_fancy const fancy = meta->type.fancy;

	if ((fancy == ATUI_ARRAY) && radix) {
		uint8_t const base = bases[radix];
		// strto* doesn't guarantee const in endptr
		char* const token_buffer = strdup(text);
		char* walker = token_buffer;
		switch (meta->total_bits) {
			case  8:
				for (uint32_t i=0; i < array_size; i++) {
					data.u8[i] = strtoul(walker, &walker, base);
				}
				break;
			case 16:
				for (uint32_t i=0; i < array_size; i++) {
					data.u16[i] = strtoul(walker, &walker, base);
				}
				break;
			case 32:
				for (uint32_t i=0; i < array_size; i++) {
					data.u32[i] = strtoul(walker, &walker, base);
				}
				break;
			case 64:
				for (uint32_t i=0; i < array_size; i++) {
					data.u64[i] = strtoull(walker, &walker, base);
				}
				break;
			default:
				assert(0);
		}
		free(token_buffer);
	} else if ((fancy==ATUI_STRING) || (fancy==ATUI_ARRAY)) {
		assert(radix == ATUI_NAN); // mainly for ATUI_ARRAY && ATUI_NAN
		char* const null_exit = memccpy(data.c8, text, '\0', array_size);
		if (fancy == ATUI_STRING) {
			/* ATUI_STRING's length is implicitly defined by the null
			termination. If the input buffer 0-terminates before array_size,
			then we will lose the intended allocation size in the bios. So fill
			the remaining bytes with spaces to push the null back to its
			original position.
			*/
			if (null_exit) {
				uint16_t const bytes_left = (
					data.c8 + array_size - null_exit
				);
				memset(null_exit-1, ' ', bytes_left); // -1 eats memccpy's 0.
			}
			data.c8[array_size-1] = '\0';
		}
	} else if (radix) {
		if (meta->type.has_enum) {
			struct atui_enum const* const enum_set = meta->enum_options;
			struct atui_enum_entry const* entry;
			int16_t str_diff = 1;
			size_t const word_length = length_of_word(text);
			for (uint16_t i=0; i < enum_set->num_entries; i++) {
				entry = &(enum_set->enum_array[i]);
				if (word_length == entry->name_length) {
					str_diff = strcmp(entry->name, text);
					if (0 == str_diff) {
						break;
					}
				}
			}
			if (0 == str_diff) {
				if (meta->type.signed_num) {
					atui_leaf_set_val_signed(leaf, entry->val);
				} else {
					atui_leaf_set_val_unsigned(leaf, entry->val);
				}
				return;
			}
		}
		if (meta->type.fraction) {
			atui_leaf_set_val_fraction(leaf, strtod(text, NULL));
		} else if (meta->type.signed_num) {
			atui_leaf_set_val_signed(leaf, strtoll_2(text));
		} else {
			atui_leaf_set_val_unsigned(leaf, strtoull_2(text));
		}
	} else {
		assert(0);
		return;
	}
}

size_t
get_sprintf_format_from_leaf(
		char* const format,
		atui_node const* const leaf
		) {
	assert(leaf->is_leaf);

// get reccomended sprintf format based on radix and other factors
	size_t print_alloc_width; // caller handles the counting of \0
	struct atui_leaf const* const meta = &(leaf->leaf);
	enum atui_leaf_type_radix const radix = meta->type.radix;
	enum atui_leaf_type_fancy const fancy = meta->type.fancy;

	if (radix) {
		char const* const metaformat = "%s%u%s"; // amogus

		uint8_t num_print_digits = 0;
		uint8_t num_digits;

		if (meta->type.fraction) {
			num_digits = 32; // we're using %G anyway
		} else {
			uint64_t max_val;
			uint8_t const num_bits = meta->total_bits;
			if (num_bits == UINT64_WIDTH) { // (UINT64_C(1)<<64) == 1
				max_val = UINT64_MAX;
			} else {
				max_val = (UINT64_C(1) << num_bits) - 1;
			}
			num_digits = ceil( // round up because it's gonna be like x.9999
				log(max_val) / log(bases[radix])
			);
		}

		print_alloc_width = num_digits;

		if (radix == ATUI_DEC) {
			// leading 0s for base 10 feels a little weird
			num_print_digits = 0;
		} else {
			num_print_digits = num_digits;
			print_alloc_width += 2; // 0x / 0b
		}

		if (meta->type.fancy == ATUI_ARRAY) {
			assert(!(meta->type.fraction)); // TODO %G ?
			sprintf(format, "%s%u%s ",
				"%0", num_print_digits, suffixes_uint[radix]
			);
			print_alloc_width += 1-2;
			// 1 for the space in between segments ; -2 to undo 0x/0b
		} else if (meta->type.fraction) {
			// %G format can have agressive rounding:
			// Q14.2 16383.75 -> 16383.8
			strcpy(format, "%G");
		} else if (meta->type.signed_num) {
			print_alloc_width += 1; // sign
			sprintf(format, metaformat,
				prefixes_int[radix], num_print_digits, suffixes_int[radix]
			);
		} else {
			sprintf(format, metaformat,
				prefixes_int[radix], num_print_digits, suffixes_uint[radix]
			);
		}
	} else if ((fancy==ATUI_ARRAY) || (fancy==ATUI_STRING)) {
		strcpy(format, "%s");
		print_alloc_width = meta->array_size;
	} else {
		format[0] = '\0';
		print_alloc_width = 0;
	}

	assert(strlen(format) < LEAF_SPRINTF_FORMAT_SIZE);
	return print_alloc_width;
}

char*
atui_leaf_to_text(
		atui_node const* const leaf
		) {
// Convert the value of a leaf to text. Currently only support for numbers,
// and strings.

	assert(leaf->is_leaf);
	assert(leaf->data.input);

	union bios_data const data = leaf->data;
	struct atui_leaf const* const meta = &(leaf->leaf);
	size_t buffer_size;
	char* buffer = NULL;

	char format[LEAF_SPRINTF_FORMAT_SIZE];
	uint32_t const array_size = meta->array_size;
	enum atui_leaf_type_radix const radix = meta->type.radix;
	enum atui_leaf_type_fancy const fancy = meta->type.fancy;
	uint32_t const num_digits = get_sprintf_format_from_leaf(format, leaf);

	if ((fancy == ATUI_ARRAY) && radix) {
		assert(!(meta->type.fraction));
		if (meta->total_bits == -1) {
			return NULL;
			assert(0);
		}

		buffer_size = (num_digits * array_size) + 1;
		buffer = cralloc(buffer_size);
		char* buffer_walk = buffer;
		switch (meta->total_bits) {
			case  8:
				for (uint32_t i=0; i < array_size; i++) {
					buffer_walk += sprintf(buffer_walk, format, data.u8[i]);
				}
				break;
			case 16:
				for (uint32_t i=0; i < array_size; i++) {
					buffer_walk += sprintf(buffer_walk, format, data.u16[i]);
				}
				break;
			case 32:
				for (uint32_t i=0; i < array_size; i++) {
					buffer_walk += sprintf(buffer_walk, format, data.u32[i]);
				}
				break;
			case 64:
				for (uint32_t i=0; i < array_size; i++) {
					buffer_walk += sprintf(buffer_walk, format, data.u64[i]);
				}
				break;
			default:
				assert(0); // why are we here? perhaps _PPATUI_LEAF_BITNESS()?
				free(buffer);
				return NULL;
		}
		*(buffer_walk-1) = '\0'; // eat the final space
	} else if ((fancy==ATUI_STRING) || (fancy==ATUI_ARRAY)) {
		assert(radix == ATUI_NAN); // mainly for ATUI_ARRAY && ATUI_NAN
		buffer_size = array_size + 1;
		buffer = cralloc(buffer_size);
		memcpy(buffer, data.c8, array_size);
		buffer[array_size] = '\0'; // if array is not null-terminated
	} else if (radix) {
		assert(num_digits);
		buffer_size = num_digits+1; // +1 is \0
		if (meta->type.has_enum) {
			int64_t val;
			if (meta->type.signed_num) {
				val = atui_leaf_get_val_signed(leaf);
			} else {
				val = atui_leaf_get_val_unsigned(leaf);
			}

			int16_t index = atui_enum_lsearch(meta->enum_options, val);
			if (-1 < index) {
				struct atui_enum_entry const* const entry = &(
					meta->enum_options->enum_array[index]
				);
				buffer_size += entry->name_length + sizeof(" : ");
				buffer = cralloc(buffer_size);

				char format_2[LEAF_SPRINTF_FORMAT_SIZE + 5]; // stage 2
				sprintf(format_2, " : %s", format);
				assert(strlen(format_2) < sizeof(format_2));

				char* walked = stopcopy(buffer, entry->name);
				sprintf(walked, format_2, val); // eats previous \0
			} else {
				buffer = cralloc(buffer_size);
				sprintf(buffer, format, val);
			}
		} else {
			buffer = cralloc(buffer_size);
			if (meta->type.fraction) {
				// %G format can have agressive rounding:
				// Q14.2 16383.75 -> 16383.8
				sprintf(buffer, "%G", atui_leaf_get_val_fraction(leaf));
			} else if (meta->type.signed_num) {
				sprintf(buffer, format, atui_leaf_get_val_signed(leaf));
			} else {
				sprintf(buffer, format, atui_leaf_get_val_unsigned(leaf));
			}
		}
	}
	assert(strlen(format) < sizeof(format));
	assert(buffer);
	assert(strlen(buffer) < buffer_size);
	return buffer;
}



void
atui_leaf_set_val_unsigned(
		atui_node const* const leaf,
		uint64_t val
		) {
	assert(leaf->is_leaf);
	assert(leaf->leaf.type.radix);
	assert(leaf->data.input);

	union bios_data const data = leaf->data;
	struct atui_leaf const* const meta = &(leaf->leaf);
	uint8_t const num_bits = (meta->bitfield_hi - meta->bitfield_lo) +1;
	uint64_t max_val;
	if (num_bits == UINT64_WIDTH) { // (UINT64_C(1)<<64) == 1
		max_val = UINT64_MAX;
	} else {
		max_val = (UINT64_C(1) << num_bits) - 1;
	}
	if (val > max_val) {
		val = max_val;
	}

	// ...11111 000.. 1111...
	uint64_t const tokeep_mask = ~(max_val << meta->bitfield_lo);
	val <<= meta->bitfield_lo;
	switch (meta->total_bits) {
		case  8: *(data.u8)  = ( *(data.u8) & tokeep_mask) | val; break;
		case 16: *(data.u16) = (*(data.u16) & tokeep_mask) | val; break;
		case 24:
			uint32_t val_temp = val;
			*(data.u24) = pt_to_npt_downgrade(&val_temp);
			break;
		case 32: *(data.u32) = (*(data.u32) & tokeep_mask) | val; break;
		case 64: *(data.u64) = (*(data.u64) & tokeep_mask) | val; break;
		default: assert(0); break;
	}

}
uint64_t
atui_leaf_get_val_unsigned(
		atui_node const* const leaf
		) {
	assert(leaf->leaf.type.radix);
	assert(leaf->data.input);

	union bios_data const data = leaf->data;
	struct atui_leaf const* const meta = &(leaf->leaf);
	uint64_t val;
	switch (meta->total_bits) {
		case  8: val =  *(data.u8); break;
		case 16: val = *(data.u16); break;
		case 24: val = npt_to_pt_upgrade(data.u24); break;
		case 32: val = *(data.u32); break;
		case 64: val = *(data.u64); break;
		default: assert(0); break;
	}

	uint8_t const num_unused_bits_hi = (
		(sizeof(val) * CHAR_BIT)
		 - meta->bitfield_hi
		 -1
	 );
	val <<= num_unused_bits_hi; // delete unused upper
	val >>= (num_unused_bits_hi + meta->bitfield_lo); // delete lower

	return val;
}

void
atui_leaf_set_val_signed(
		atui_node const* const leaf,
		int64_t const val
		) {
	assert(leaf->is_leaf);
	assert(leaf->leaf.type.radix);
	assert(leaf->data.input);

	union bios_data const data = leaf->data;
	struct atui_leaf const* const meta = &(leaf->leaf);
	// handle Two's Complement on arbitrarily-sized ints
	uint64_t raw_val; // some bit math preserves the sign
	uint8_t const num_bits = (meta->bitfield_hi - meta->bitfield_lo) +1;
	uint64_t mask;
	if (num_bits == UINT64_WIDTH) { // (UINT64_C(1)<<64) == 1
		mask = UINT64_MAX;
	} else {
		mask = (UINT64_C(1) << num_bits) - 1;
	}
	int64_t const max_val = mask>>1; // max positive val 0111...
	if (val > max_val) {
		raw_val = max_val;
	} else if (val < -max_val) {
		raw_val = max_val+1; // Two's overflow. 1000.. is negative-most.
		// GCC's -fwrapv can play
	} else {
		raw_val = val & mask; // Two's sign repeats to the right
	}

	// ...11111 000.. 1111...
	uint64_t const tokeep_mask = ~(mask << meta->bitfield_lo);
	raw_val <<= meta->bitfield_lo;

	switch (meta->total_bits) {
		case  8:  *(data.u8) = ( *(data.u8) & tokeep_mask) | raw_val;  break;
		case 16: *(data.u16) = (*(data.u16) & tokeep_mask) | raw_val;  break;
		case 24:
			int32_t val_temp = raw_val;
			*(data.s24) = pt_to_npt_downgrade(&val_temp);
			break;
		case 32: *(data.u32) = (*(data.u32) & tokeep_mask) | raw_val;  break;
		case 64: *(data.u64) = (*(data.u64) & tokeep_mask) | raw_val;  break;
		default: assert(0); break;
	}
}

int64_t
atui_leaf_get_val_signed(
		atui_node const* const leaf
		) {
	assert(leaf->is_leaf);
	assert(leaf->leaf.type.radix);
	assert(leaf->data.input);

	union bios_data const data = leaf->data;
	struct atui_leaf const* const meta = &(leaf->leaf);
	int64_t val;
	switch (meta->total_bits) {
		case  8: val =  *(data.s8); break;
		case 16: val = *(data.s16); break;
		case 24: val = npt_to_pt_upgrade(data.s24); break;
		case 32: val = *(data.s32); break;
		case 64: val = *(data.s64); break;
		default: assert(0); break;
	}

	uint8_t const num_unused_bits_hi = (
		(sizeof(val) * CHAR_BIT)
		- meta->bitfield_hi
		- 1
	);
	val <<= num_unused_bits_hi; // delete unused upper
	// rightshift on signed repeats sign
	val >>= (num_unused_bits_hi + meta->bitfield_lo); // delete lower
	return val;
}

void
atui_leaf_set_val_fraction(
		atui_node const* const leaf,
		float64_t const val) {
	assert(leaf->is_leaf);
	assert(leaf->leaf.type.fraction);
	assert(leaf->data.input);

	union bios_data const data = leaf->data;
	struct atui_leaf const* const meta = &(leaf->leaf);

	if (meta->fractional_bits) {
		float64_t const max_val = (
			(float64_t)(1<<(meta->total_bits - meta->fractional_bits))
			- ( (float64_t)(1) / (float64_t)(1<<meta->fractional_bits))
		);
		uint64_t fixed_val;
		if (val > max_val) {
			fixed_val = (1<<meta->total_bits)-1;
		} else {
			fixed_val = floor(val);
			float64_t const frac = (
				(val - floor(val)) * (1<<meta->fractional_bits)
			);
			fixed_val <<= meta->fractional_bits;
			fixed_val += frac;
		}
		switch (meta->total_bits) {
			case  8:  *(data.u8) = fixed_val; return;
			case 16: *(data.u16) = fixed_val; return;
			case 32: *(data.u32) = fixed_val; return;
			case 64: *(data.u64) = fixed_val; return;
			default: assert(0); break;
		}
	}

	switch (meta->total_bits) { // else float
		case 16: *(data.f16) = val; return;
		case 32: *(data.f32) = val; return;
		case 64: *(data.f64) = val; return;
		default: assert(0); break;
	}

	assert(0);
}
float64_t
atui_leaf_get_val_fraction(
		atui_node const* const leaf
		) {
	assert(leaf->is_leaf);
	assert(leaf->leaf.type.fraction);
	assert(leaf->data.input);

	struct atui_leaf const* const meta = &(leaf->leaf);
	union bios_data const data = leaf->data;

	if (meta->fractional_bits) { // fixed-point
		// f64 can represent represent ints up to 2**53 without rounding.
		assert((meta->total_bits - meta->fractional_bits) < 53);
		float64_t val;
		switch (meta->total_bits) {
			case  8: val =  *(data.u8); break;
			case 16: val = *(data.u16); break;
			case 32: val = *(data.u32); break;
			case 64: val = *(data.u64); break;
			default: assert(0); break;
		};
		val /= (1 << meta->fractional_bits);
		return val;
	};

	// else native float
	switch (meta->total_bits) {
		case 16: return *(data.f16);
		case 32: return *(data.f32);
		case 64: return *(data.f64);
		default: assert(0); break;
	}

	assert(0);
	return NAN;
}

char*
atui_node_to_path(
		atui_node const* const tip
		) {
	assert(tip);

	bool const final_slash = ! tip->is_leaf;
	size_t string_length = 1 + final_slash; // +1 for inital /
	atui_node const* stack[ATUI_STACK_DEPTH];
	uint8_t stack_i = 0;

	stack[0] = tip;
	do {
		string_length += strlen(stack[stack_i]->name) + 1; // +1 for /
		stack[stack_i+1] = stack[stack_i]->parent;
		stack_i++;
	} while (stack[stack_i]);
	assert(stack_i < lengthof(stack));

	char* const pathstring = cralloc(string_length);
	char* path_walk = pathstring;
	path_walk[0] = '/';
	path_walk++;
	do {
		stack_i--;
		path_walk = stopcopy(path_walk, stack[stack_i]->name);
		*path_walk = '/'; // eats the previous \0
		path_walk++;
	} while (stack_i);
	path_walk -= ! final_slash; // eat the final / if leaf
	*path_walk = '\0';
	assert(path_walk == (pathstring+string_length-1));
	assert(strlen(pathstring) == (string_length-1));

	return pathstring;
}


inline static uint8_t
path_to_atui_has_branch(
		atui_node const* node,
		atui_node const** const target,
		char const** const path_token_io,
		char** const token_save
		) {
	char const* path_token = *path_token_io;
	uint8_t depth = 0;
	uint16_t i=1;
	atui_node const* const* branch_nodes = &node;
	do {
		assert(true == node->branch.branches.indirect);
		do {
			if (0 == i) {
				goto not_found; // no dir found; could be a leaf?
			}
			i--;
		} while (strcmp(path_token, branch_nodes[i]->name));
		node = branch_nodes[i];
		branch_nodes = node->branch.branches.addresses_ro;
		i = node->branch.branches.count;
		depth++;
		path_token = strtok_r(NULL, "/", token_save);
	} while (path_token);

	not_found:
	*target = node;
	*path_token_io = path_token;

	return depth;
}
inline static uint8_t
path_to_atui_has_leaf(
		atui_node const* node,
		atui_node const** const target,
		char const** const path_token_io,
		char** const token_save
		) {
	char const* path_token = *path_token_io;
	uint8_t depth = 0;
	do {
		assert(false == node->leaves.indirect);
		uint16_t i = node->leaves.count;
		atui_node const* leaf_nodes = node->leaves.nodes_ro;
		do {
			if (0 == i) {
				goto not_found;
			}
			i--;
		} while (strcmp(path_token, leaf_nodes[i].name));
		node = &(leaf_nodes[i]);
		depth++;
		path_token = strtok_r(NULL, "/", token_save);
	} while (path_token);

	*target = node;

	not_found:
	*path_token_io = path_token;
	return depth;
}
struct atui_path_goto*
path_to_atui(
		atui_node const* const root,
		char const* const path
		) {
	size_t not_found_arraylen = 0; // for an error message

	atui_node const* file = NULL;
	atui_node const* dir = NULL;
	uint8_t leaf_depth = 0;
	uint8_t branch_depth = 0;
	char* const token_buffer = strdup(path);
	char* token_save;
	char const* path_token = strtok_r(token_buffer, "/", &token_save);

	if (path_token) {
		branch_depth = path_to_atui_has_branch(
			root, &dir,
			&path_token, &token_save
		);
		if (path_token && dir) {
			leaf_depth = path_to_atui_has_leaf(
				dir, &file,
				&path_token, &token_save
			);
		}
	}

	if (path_token) {
		not_found_arraylen = 1 + strlen(path_token);
	} else if (NULL == dir) { // if there's no path to parse, error
		not_found_arraylen = 1;
		path_token = "";
	}

	void* partition = cralloc(
		sizeof(struct atui_path_goto)
		+ not_found_arraylen
	);

	struct atui_path_goto* const map = partition;
	map->branch.node = (atui_node*) dir;
	map->branch.depth = branch_depth;
	map->leaf.node = (atui_node*) file;
	map->leaf.depth = leaf_depth;

	partition += sizeof(struct atui_path_goto);
	if (not_found_arraylen) {
		map->not_found = partition;
		strcpy(map->not_found, path_token);
	} else {
		map->not_found = NULL;
	}
	partition = NULL; // we're done partitioning

	free(token_buffer);
	return map;
}



char*
atui_enum_entry_to_text(
		atui_node const* const leaf,
		struct atui_enum_entry const* const enum_entry
		) {
	assert(leaf->is_leaf);
	assert(leaf->leaf.type.has_enum && leaf->leaf.type.radix);

	char format_1[LEAF_SPRINTF_FORMAT_SIZE]; // stage 1
	char format_2[LEAF_SPRINTF_FORMAT_SIZE + 5]; // stage 2
	uint8_t const num_digits = get_sprintf_format_from_leaf(format_1, leaf);
	assert(strlen(format_1) < sizeof(format_1));
	sprintf(format_2, " : %s", format_1);
	assert(strlen(format_2) < sizeof(format_2));

	size_t const buffer_size = (
		enum_entry->name_length + sizeof(" : 0x") + num_digits
	);
	char* const buffer = cralloc(buffer_size);

	char* walked = stopcopy(buffer, enum_entry->name); // walk the buffer
	sprintf(walked, format_2, enum_entry->val);  // eats previous \0
	assert(strlen(buffer) < buffer_size);
	return buffer;
}

int16_t
atui_enum_bsearch(
		struct atui_enum const* const enum_set,
		int64_t const val
		) {
	// binary search for atui_enum arrays.
	// as a result, it assumes the array is sorted.
	// this algo also finds the leftmost if there are duplicates
	struct atui_enum_entry const* const enum_array = enum_set->enum_array;
	uint8_t left = 0;
	uint8_t mid;
	uint8_t right = enum_set->num_entries;
	while (left != right) {
		mid = (left + right) >> 1;  // bitshift div-by-2
		if (val <= enum_array[mid].val) {
			right = mid;
		} else {
			left = mid + 1;
		}
	}
	// left==right. mid will be off by 1, leftwise, if it's unique.
	if (val == enum_array[left].val) {
		return left;
	} else {
		return -1;
	}
}
int16_t
atui_enum_lsearch(
		struct atui_enum const* const enum_set,
		int64_t const val
		) {
	// linear search for atui_enum arrays.
	// this algo also finds the leftmost if there are duplicates
	for (uint8_t i=0; i < enum_set->num_entries; i++) {
		if (val == enum_set->enum_array[i].val) {
			return i;
		}
	}
	return -1;
}
