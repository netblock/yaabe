/*
AtomTree iterable interface for UIs.

See ppatui.h for the metaprogramming and atui.h for general API.
*/

#include "atomtree.h"
#include "atui.h"
#include <math.h>

void
atui_leaf_from_text(
		atui_leaf* const leaf,
		char8_t const* const text
		) {
	// set the value of the leaf based on input text. Currently only support for
	// numbers (including bitfields) and strings.
	assert(leaf->val);

	uint8_t const bases[] = {0, 10, 16, 8, 2};

	uint8_t err = 0;
	uint16_t i,j;
	char8_t buffer[65];

	uint8_t const array_size = leaf->array_size;
	uint8_t const radix = leaf->type & ATUI_ANY;


	if ((leaf->type & ATUI_ARRAY) && (radix != ATUI_NAN)) {
		uint8_t const base = bases[radix];
		uint8_t const num_digits = ceil(
			// round up because it's gonna be like x.9999
			log( (1ULL << leaf->total_bits) - 1 ) // expand num of bits to size
			/ log(base)
		);
		i = 0; j = 0;
		buffer[num_digits] = '\0';
		while(text[j] == ' ') // cut off leading spaces
			j++;
		switch (leaf->total_bits) {
			case 8:
				for(; i < leaf->array_size; i++) {
					memcpy(buffer, text+j, num_digits);
					leaf->u8[i] = strtoul(buffer, NULL, base);
					j += num_digits;
					if (text[j] == ' ')
						j++;
				}
				break;
			case 16:
				for(; i < leaf->array_size; i++) {
					memcpy(buffer, text+j, num_digits);
					leaf->u16[i] = strtoul(buffer, NULL, base);
					j += num_digits;
					if (text[j] == ' ')
						j++;
				}
				break;
			case 32:
				for(; i < leaf->array_size; i++) {
					memcpy(buffer, text+j, num_digits);
					leaf->u32[i] = strtoul(buffer, NULL, base);
					j += num_digits;
					if (text[j] == ' ')
						j++;
				}
				break;
			case 64:
				for(; i < leaf->array_size; i++) {
					memcpy(buffer, text+j, num_digits);
					leaf->u64[i] = strtoull(buffer, NULL, base);
					j += num_digits;
					if (text[j] == ' ')
						j++;
				}
				break;
			default:
				assert(0);
				return;
		}
	} else if (leaf->type & (ATUI_STRING|ATUI_ARRAY)) {
		assert(radix == ATUI_NAN); // mainly for ATUI_ARRAY && ATUI_NAN
		char8_t* const null_exit = memccpy(leaf->u8, text, '\0', array_size);

		if (leaf->type & ATUI_STRING) {
			/* ATUI_STRING's length is implicitly defined by the null
			termination. If the input buffer 0-terminates before array_size,
			then we will lose the intended allocation size in the bios. So fill
			the remaining bytes with spaces to push the null back to its
			original position.
			*/
			if (null_exit) {
				uint16_t const bytes_left = leaf->u8 + array_size - null_exit;
				memset(null_exit-1, ' ', bytes_left); // -1 eats memccpy's 0.
			}
			leaf->u8[array_size-1] = '\0';
		}
	} else if (radix) {
		if (leaf->type & ATUI_ENUM) {
			struct atui_enum const* const enum_set = leaf->enum_options;
			struct atui_enum_entry const* entry;
			int16_t str_diff;
			for (i=0; i < enum_set->num_entries; i++) {
				entry = &(enum_set->enum_array[i]);
				str_diff = strncmp(entry->name, text, entry->name_length);
				if (0 == str_diff) {
					break;
				}
			}
			if (0 == str_diff) {
				if (leaf->type & ATUI_SIGNED) {
					atui_leaf_set_val_signed(leaf, entry->val);
				} else {
					atui_leaf_set_val_unsigned(leaf, entry->val);
				}
				return;
			}
		}
		if (leaf->type & ATUI_FRAC) {
			atui_leaf_set_val_fraction(leaf, strtod(text, NULL));
		} else if (leaf->type & ATUI_SIGNED) {
			atui_leaf_set_val_signed(leaf, strtoll_2(text));
		} else {
			atui_leaf_set_val_unsigned(leaf, strtoull_2(text));
		}
	} else {
		assert(0);
		return;
	}
}

inline static uint16_t
_get_sprintf_format_from_leaf(
		char8_t* const format,
		atui_leaf const* const leaf
		) {
#ifdef C2X_COMPAT
	char8_t const* const prefixes[] = {"", "%0", "0x%0", "0o%0", "0x%0"};
	char8_t const* const suffixes_unsigned[] = {"", "llu", "llX", "llo", "llX"};
	char8_t const* const suffixes_signed[]   = {"", "lli", "llX", "llo", "llX"};
	uint8_t const bases[] = {0, 10, 16, 8, 16};
#else
	char8_t const* const prefixes[] = {"", "%0", "0x%0", "0o%0", "0b%0"};
	char8_t const* const suffixes_unsigned[] = {"", "llu", "llX", "llo", "llb"};
	char8_t const* const suffixes_signed[]   = {"", "lli", "llX", "llo", "llb"};
	uint8_t const bases[] = {0, 10, 16, 8, 2};
#endif
	char8_t const* const metaformat = "%s%u%s"; // amogus


	uint8_t const radix = leaf->type & ATUI_ANY;
	uint8_t num_digits;

#ifdef C2X_COMPAT
	if ((radix==ATUI_HEX) || (radix==ATUI_BIN)) {
		num_digits = leaf->total_bits/4;
	} else {
		num_digits = 0;
	}
#else
	if (radix == ATUI_HEX) {
		num_digits = leaf->total_bits/4;
	} else if (radix == ATUI_BIN) {
		num_digits = (leaf->bitfield_hi - leaf->bitfield_lo) +1;
	} else {
		num_digits = 0;
	}
#endif

	if ((leaf->type & ATUI_ARRAY) && (radix != ATUI_NAN)) {
		assert(!(leaf->type & ATUI_FRAC));
		// too hard cause floats can have many base-10 digits

		num_digits = ceil( // round up because it's gonna be like x.9999
			log( (1ULL << leaf->total_bits) - 1 ) // expand num of bits to size
			/ log(bases[radix])
		);

		sprintf(format, "%s%u%s ", "%0", num_digits, suffixes_unsigned[radix]);
		num_digits += 1; // 1 for the space in between segments.
	} else if (radix) {
		if (leaf->type & ATUI_FRAC) {
			// %G format can have agressive rounding: Q14.2 16383.75 -> 16383.8
			strcpy(format, "%G");
		} else if (leaf->type & ATUI_SIGNED) {
			sprintf(format, metaformat,
				prefixes[radix], num_digits, suffixes_signed[radix]
			);
		} else {
			sprintf(format, metaformat,
				prefixes[radix], num_digits, suffixes_unsigned[radix]
			);
		}
	}

	return num_digits;
}

uint16_t
atui_leaf_to_text(
		atui_leaf const* const leaf,
		char8_t** buffer_ptr
		) {
	// Convert the value of a leaf to text. Currently only support for numbers,
	// and strings.

	assert(leaf->val);

	uint16_t malloc_size = 0;
	char8_t* buffer = *buffer_ptr;

	char8_t format[10];
	uint8_t const radix = leaf->type & ATUI_ANY;
	uint8_t const num_digits = _get_sprintf_format_from_leaf(format, leaf);

	if ((leaf->type & ATUI_ARRAY) && (radix != ATUI_NAN)) {
		assert(!(leaf->type & ATUI_FRAC));
		malloc_size = (num_digits * leaf->array_size) + 1;
		if (malloc_size > ATUI_LEAVES_STR_BUFFER) {
			buffer = malloc(malloc_size);
			buffer[0] = '\0';
			*buffer_ptr = buffer;
		} else {
			malloc_size = 0;
		}
		uint16_t i=0,j=0;
		switch (leaf->total_bits) {
			case 8:
				for(; i < leaf->array_size; i++) {
					sprintf(buffer+j, format,  leaf->u8[i]);
					j += num_digits;
				}
				break;
			case 16:
				for(; i < leaf->array_size; i++) {
					sprintf(buffer+j, format,  leaf->u16[i]);
					j += num_digits;
				}
				break;
			case 32:
				for(; i < leaf->array_size; i++) {
					sprintf(buffer+j, format,  leaf->u32[i]);
					j += num_digits;
				}
				break;
			case 64:
				for(; i < leaf->array_size; i++) {
					sprintf(buffer+j, format,  leaf->u64[i]);
					j += num_digits;
				}
				break;
			default:
				assert(0); // why are we here? perhaps _PPATUI_LEAF_BITNESS()?
				return malloc_size;
		}
		buffer[j-1] = '\0'; // eat the final space

	} else if (leaf->type & (ATUI_STRING|ATUI_ARRAY)) {
		assert(radix == ATUI_NAN); // mainly for ATUI_ARRAY && ATUI_NAN
		if (leaf->array_size > ATUI_LEAVES_STR_BUFFER) {
			malloc_size = leaf->array_size + 1;
			buffer = malloc(malloc_size);
			*buffer_ptr = buffer;
		}
		memcpy(buffer, leaf->u8, leaf->array_size);
		buffer[leaf->array_size] = '\0'; // if array is not null-terminated
	} else if (radix) {
		if (leaf->type & ATUI_ENUM) {
			int64_t val;
			if (leaf->type & ATUI_SIGNED) {
				val = atui_leaf_get_val_signed(leaf);
			} else {
				val = atui_leaf_get_val_unsigned(leaf);
			}
			int16_t index = atui_enum_lsearch(leaf->enum_options, val);
			if (-1 < index) {
				char8_t format_2[15]; // stage 2
				sprintf(format_2, " : %s", format);
				assert(strlen(format_2) < sizeof(format_2));

				char8_t* walked = stopcopy(
					buffer, leaf->enum_options->enum_array[index].name
				); // walk the buffer
				sprintf(walked, format_2, val); // eats previous \0
				assert(strlen(buffer) < ATUI_LEAVES_STR_BUFFER);
			} else {
				sprintf(buffer, format, val);
			}
		} else if (leaf->type & ATUI_FRAC) {
			// %G format can have agressive rounding: Q14.2 16383.75 -> 16383.8
			sprintf(buffer, "%G", atui_leaf_get_val_fraction(leaf));
		} else if (leaf->type & ATUI_SIGNED) {
			sprintf(buffer, format, atui_leaf_get_val_signed(leaf));
		} else {
			sprintf(buffer, format, atui_leaf_get_val_unsigned(leaf));
		}
	}
	assert(strlen(format) < sizeof(format));
	return malloc_size;
}



void
atui_leaf_set_val_unsigned(
		atui_leaf* const leaf,
		uint64_t val
		) {
	assert(leaf->type & ATUI_ANY);
	assert(leaf->val);

	uint8_t const num_bits = (leaf->bitfield_hi - leaf->bitfield_lo) +1;
	uint64_t maxval;
	if (num_bits == (sizeof(maxval) * CHAR_BIT)) { // (1ULL<<64) == 1
		maxval = ~0ULL;
	} else {
		maxval = (1ULL << num_bits) - 1;
	}
	if (val > maxval) {
		val = maxval;
	}

	// ...11111 000.. 1111...
	uint64_t const tokeep_mask = ~(maxval << leaf->bitfield_lo);
	val <<= leaf->bitfield_lo;

	switch (leaf->total_bits) {
		case 8:
			*(leaf->u8) = (*(leaf->u8) & tokeep_mask) | val;
			break;
		case 16:
			*(leaf->u16) = (*(leaf->u16) & tokeep_mask) | val;
			break;
		case 32:
			*(leaf->u32) = (*(leaf->u32) & tokeep_mask) | val;
			break;
		case 64:
			*(leaf->u64) = (*(leaf->u64) & tokeep_mask) | val;
			break;
		default:
			assert(0);
			break;
	}
}
uint64_t
atui_leaf_get_val_unsigned(
		atui_leaf const* const leaf
		) {
	assert(leaf->type & ATUI_ANY);
	assert(leaf->val);

	uint64_t val;
	switch (leaf->total_bits) {
		case 8:
			val = *(leaf->u8);
			break;
		case 16:
			val = *(leaf->u16);
			break;
		case 32:
			val = *(leaf->u32);
			break;
		case 64:
			val = *(leaf->u64);
			break;
		default:
			assert(0);
			break;
	}

	uint8_t const num_unused_bits_hi = (
		(sizeof(val) * CHAR_BIT)
		 - leaf->bitfield_hi
		 -1
	 );
	val <<= num_unused_bits_hi; // delete unused upper
	val >>= (num_unused_bits_hi + leaf->bitfield_lo); // delete lower

	return val;
}

void
atui_leaf_set_val_signed(
		atui_leaf* const leaf,
		int64_t const val
		) {
	assert(leaf->type & ATUI_ANY);
	assert(leaf->val);

	// handle Two's Complement on arbitrarily-sized ints
	uint64_t raw_val; // some bit math preserves the sign
	uint8_t const num_bits = (leaf->bitfield_hi - leaf->bitfield_lo) +1;
	uint64_t const mask = (1ULL << num_bits) - 1;
	int64_t const maxval = mask>>1; // max positive val 0111...
	if (val > maxval) {
		raw_val = maxval;
	} else if (val < -maxval) {
		raw_val = maxval+1; // Two's overflow. 1000.. is negative-most.
	} else {
		raw_val = val & mask; // Two's sign repeats to the right
	}

	// ...11111 000.. 1111...
	uint64_t const tokeep_mask = ~(mask << leaf->bitfield_lo);
	raw_val <<= leaf->bitfield_lo;

	switch (leaf->total_bits) {
		case 8:
			*(leaf->u8) = (*(leaf->u8) & tokeep_mask) | raw_val;
			break;
		case 16:
			*(leaf->u16) = (*(leaf->u16) & tokeep_mask) | raw_val;
			break;
		case 32:
			*(leaf->u32) = (*(leaf->u32) & tokeep_mask) | raw_val;
			break;
		case 64:
			*(leaf->u64) = (*(leaf->u64) & tokeep_mask) | raw_val;
			break;
		default:
			assert(0);
			break;
	}
}
int64_t
atui_leaf_get_val_signed(
		atui_leaf const* const leaf
		) {
	assert(leaf->type & ATUI_ANY);
	assert(leaf->val);

	int64_t val;
	switch (leaf->total_bits) {
		case 8:
			val = *(leaf->s8);
			break;
		case 16:
			val = *(leaf->s16);
			break;
		case 32:
			val = *(leaf->s32);
			break;
		case 64:
			val = *(leaf->s64);
			break;
		default:
			assert(0);
			break;
	}

	uint8_t const num_unused_bits_hi = (
		(sizeof(val) * CHAR_BIT)
		- leaf->bitfield_hi
		- 1
	);
	val <<= num_unused_bits_hi; // delete unused upper
	// rightshift on signed repeats sign
	val >>= (num_unused_bits_hi + leaf->bitfield_lo); // delete lower
	return val;
}

void
atui_leaf_set_val_fraction(
		atui_leaf* const leaf,
		float64_t const val) {
	assert(leaf->type & ATUI_FRAC);
	assert(leaf->val);

	if (leaf->fractional_bits) {
		float64_t const max_val = (
			(float64_t)(1<<(leaf->total_bits - leaf->fractional_bits))
			- ( (float64_t)(1) / (float64_t)(1<<leaf->fractional_bits))
		);
		uint64_t fixed_val;
		if (val > max_val) {
			fixed_val = (1<<leaf->total_bits)-1;
		} else {
			fixed_val = floor(val);
			float64_t const frac = (
				(val - floor(val)) * (1<<leaf->fractional_bits)
			);
			fixed_val <<= leaf->fractional_bits;
			fixed_val += frac;
		}
		switch(leaf->total_bits) {
			case 8:
				*(leaf->u8) = fixed_val;
				return;
			case 16:
				*(leaf->u16) = fixed_val;
				return;
			case 32:
				*(leaf->u32) = fixed_val;
				return;
			case 64:
				*(leaf->u64) = fixed_val;
				return;
			default:
				assert(0);
				break;
		}
	}

	switch(leaf->total_bits) { // else float
		case 16:
			*(leaf->f16) = val;
			return;
		case 32:
			*(leaf->f32) = val;
			return;
		case 64:
			*(leaf->f64) = val;
			return;
		default:
			assert(0);
			break;
	}

	assert(0);
}
float64_t
atui_leaf_get_val_fraction(
		atui_leaf const* const leaf
		) {
	assert(leaf->type & ATUI_FRAC);
	assert(leaf->val);

	if (leaf->fractional_bits) { // fixed-point
		// f64 can represent represent ints up to 2**53 without rounding.
		assert((leaf->total_bits - leaf->fractional_bits) < 53);
		float64_t val;
		switch(leaf->total_bits) {
			case 8:
				val = *(leaf->u8);
				break;
			case 16:
				val = *(leaf->u16);
				break;
			case 32:
				val = *(leaf->u32);
				break;
			case 64:
				val = *(leaf->u64);
				break;
			default:
				assert(0);
				break;
		};
		val /= (1 << leaf->fractional_bits);
		return val;
	};

	// else native float
	switch(leaf->total_bits) {
		case 16:
			return *(leaf->f16);
		case 32:
			return *(leaf->f32);
		case 64:
			return *(leaf->f64);
		default:
			assert(0);
			break;
	}

	assert(0);
}

char8_t*
atui_branch_to_path(
		atui_branch const* const tip,
		char8_t* const pathstring
		) {
	assert(tip);

	atui_branch const* branchstack[16];
	branchstack[0] = tip;
	uint8_t i = 0;
	uint16_t string_length = 1+1; // 1 for the initial / and 1 is for str \0
	do {
		string_length += 1 + strlen(branchstack[i]->name);
		assert(i < (sizeof(branchstack)/sizeof(atui_branch*)));
		branchstack[i+1] = branchstack[i]->parent_branch;
		i++;
	} while (branchstack[i]);

	pathstring[string_length-1] = '\0';
	pathstring[0] = '/';
	char8_t* path_walk = pathstring+1; // +1 is the first /
	while (i) {
		i--;
		path_walk = stopcopy(path_walk, branchstack[i]->name);
		*path_walk = '/'; // eats the previous \0
		path_walk++;
	}
	assert(path_walk == (pathstring+string_length-1));

	return (pathstring + string_length);
}
char8_t*
atui_leaf_to_path(
		atui_leaf const* const tip,
		char8_t* const pathstring
		) {
	union { // due to ATUI_INLINE, the leaf's parent may be a branch
		void const* atui;
		atui_leaf const* leaf;
		atui_branch const* branch;
	} leanch_stack[16];
	bool is_leaf[16];

	leanch_stack[0].leaf = tip;
	is_leaf[0] = true;
	uint8_t i = 0;
	uint16_t string_length = 0;
	do {
		assert(i < (sizeof(leanch_stack)/sizeof(atui_branch*)));
		if (is_leaf[i]) {
			leanch_stack[i+1].atui = leanch_stack[i].leaf->parent;
			is_leaf[i+1] = leanch_stack[i].leaf->parent_is_leaf;
			string_length += strlen(leanch_stack[i].leaf->name);
		} else {
			leanch_stack[i+1].atui = leanch_stack[i].branch->parent;
			is_leaf[i+1] = leanch_stack[i].branch->parent_is_leaf;
			string_length += strlen(leanch_stack[i].branch->name);
		}
		string_length += 1;
		i++;
	} while (leanch_stack[i].atui);

	char8_t* path_walk = pathstring;
	char8_t const* name;
	while (i) {
		i--;
		if (is_leaf[i]) {
			if (leanch_stack[i].leaf->type & ATUI_SUBONLY) {
				continue; // leaf's children only
			}
			name = leanch_stack[i].leaf->name;
		} else {
			if (leanch_stack[i].branch->parent_is_leaf) {
				continue; // skip the branch of ATUI_INLINE
			}
			name = leanch_stack[i].branch->name;
		}
		*path_walk = '/'; // eats the previous \0
		path_walk = stopcopy(path_walk+1, name);
	}
	assert(path_walk <= (pathstring+string_length));

	return path_walk;
}

//static const atui_leaf*
static uint8_t
_path_to_atui_has_leaf(
		atui_leaf const* const leaves,
		uint16_t const num_leaves,
		char8_t const** const path_token,
		char** const token_save,
		atui_leaf const** const target
		) {
	atui_leaf const* child_leaves;
	uint16_t num_child_leaves;

	for (uint16_t i = 0; i < num_leaves; i++) {
		if (leaves[i].type & ATUI_NODISPLAY) {
			continue;
		} else if (leaves[i].type & (ATUI_BITFIELD|ATUI_INLINE|ATUI_DYNARRAY)) {
			// has child leaves
			if (0 == (leaves[i].type & ATUI_SUBONLY)) {
				// ATUI_SUBONLY pseudo-orphans their children
				if (strcmp(*path_token, leaves[i].name)) { // 0 is equal
					continue;
				}
				*path_token = strtok_r(NULL, u8"/", token_save);
				if (NULL == *path_token) {
					*target = &(leaves[i]);
					return 1;
				}
			}
			if (leaves[i].type & ATUI_INLINE) {
				// always ignore branch for ATUI_INLINE
				atui_branch const* inl = *(leaves[i].inline_branch);
				child_leaves = inl->leaves;
				num_child_leaves = inl->leaf_count;
			} else {
				child_leaves = leaves[i].child_leaves;
				num_child_leaves = leaves[i].num_child_leaves;
			}
			uint8_t depth = _path_to_atui_has_leaf(
				child_leaves, num_child_leaves,
				path_token, token_save,
				target
			);
			if (depth) { // can be NULL if no match against a child/grand-child
				return depth + (0 == (leaves[i].type & ATUI_SUBONLY));
			}
		} else if (0 == strcmp(*path_token, leaves[i].name)) {
			*path_token = strtok_r(NULL, u8"/", token_save);
			*target = &(leaves[i]);
			return 1;
		}
	}

	return 0;
}
struct atui_path_map*
path_to_atui(
		char8_t const* const path,
		atui_branch const* const root
		) {
	char8_t* const token_buffer = strdup(path);
	char* token_save;
	char8_t const* path_token = strtok_r(token_buffer, u8"/", &token_save);
	size_t not_found_arraylen = 0; // for an error message

	atui_leaf const* file = NULL;
	atui_branch const* dir = NULL;
	uint8_t leaf_depth = 0;
	uint8_t branch_depth = 0;

	atui_branch const* const* child_dirs = &root;
	uint16_t i = 1;
	// this method of latching allows us to enter the loop with a named root
	// while also saving the last-known-good dir

	while (path_token) { // go through branches and verify path
		do {
			if (0 == i) {
				goto find_leaves; // no dir found; could be a leaf?
			}
			i--;
		} while (strcmp(path_token, child_dirs[i]->name)); // 0 means ==
		dir = child_dirs[i];
		child_dirs = (atui_branch const* const*) dir->child_branches;
		i = dir->num_branches;
		branch_depth++; // the previously poped token is a branch
		path_token = strtok_r(NULL, u8"/", &token_save);
	}
	if (path_token) {
		find_leaves:
		if (dir) {
			leaf_depth = _path_to_atui_has_leaf(
				dir->leaves, dir->leaf_count,
				&path_token, &token_save,
				&file
			);
		}
	}
	if (path_token) {
		not_found_arraylen = 1 + strlen(path_token);
	} else if (NULL == dir) { // if there's no path to parse, error
		not_found_arraylen = 1;
		path_token = "";
	}

	void* partition = malloc(
		sizeof(struct atui_path_map)
		+ (branch_depth * sizeof(atui_branch*))
		+ (leaf_depth * sizeof(atui_leaf*))
		+ not_found_arraylen
	);
	struct atui_path_map* const map = partition;
	partition += sizeof(struct atui_path_map);
	if (branch_depth) {
		map->branch_path = partition;
		partition += (branch_depth * sizeof(atui_branch*));
	} else {
		map->branch_path = NULL;
	}
	if (leaf_depth) {
		map->leaf_path = partition;
		partition += (leaf_depth * sizeof(atui_leaf*));
	} else {
		map->leaf_path = NULL;
	}
	if (not_found_arraylen) {
		map->not_found = partition;
	} else {
		map->not_found = NULL;
	}
	partition = NULL; // we're done partitioning

	map->branch_depth = branch_depth;
	map->leaf_depth = leaf_depth;
	while (branch_depth) {
		branch_depth--;
		map->branch_path[branch_depth] = (atui_branch*) dir;
		dir = dir->parent_branch;
	}
	while (leaf_depth) {
		leaf_depth--;
		map->leaf_path[leaf_depth] = (atui_leaf*) file;
		if (file->parent_is_leaf) {
			file = file->parent_leaf;
		} else { // ATUI_INLINE; skip over branch
			file = file->parent_branch->parent_leaf;
		}
	}
	if (not_found_arraylen) {
		strcpy(map->not_found, path_token);
	}

	free(token_buffer);
	return map;
}





void
atui_enum_entry_to_text(
		char8_t* const buffer,
		atui_leaf const* const leaf,
		struct atui_enum_entry const* const enum_entry
		) {
	assert(leaf->type & (ATUI_ANY|ATUI_ENUM));

	char8_t format_1[10]; // stage 1
	char8_t format_2[15]; // stage 2
	_get_sprintf_format_from_leaf(format_1, leaf);
	assert(strlen(format_1) < sizeof(format_1));
	sprintf(format_2, " : %s", format_1);
	assert(strlen(format_2) < sizeof(format_2));

	char8_t* walked = stopcopy(buffer, enum_entry->name); // walk the buffer
	sprintf(walked, format_2, enum_entry->val);  // eats previous \0
	assert(strlen(buffer) < ATUI_LEAVES_STR_BUFFER);
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
	while(left != right) {
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


void
_atui_destroy_leaves(
		atui_leaf* const leaves,
		uint16_t const num_leaves
		) {
	for (uint16_t i = 0; i < num_leaves; i++) {
		if (leaves[i].num_child_leaves) {
			_atui_destroy_leaves(
				leaves[i].child_leaves, leaves[i].num_child_leaves
			);
			free(leaves[i].child_leaves);
		}
	}
}
void
atui_destroy_tree(
		atui_branch* const tree
		) { // a reference implementation
	while(tree->max_all_branch_count--) {
		atui_destroy_tree(tree->all_branches[tree->max_all_branch_count]);
	}
	_atui_destroy_leaves(tree->leaves, tree->leaf_count);
	free(tree);
}


