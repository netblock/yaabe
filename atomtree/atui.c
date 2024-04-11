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
		const char8_t* const text
		) {
	// set the value of the leaf based on input text. Currently only support for
	// numbers (including bitfields) and strings.
	assert(leaf->val);

	const uint8_t bases[] = {0, 10, 16, 8, 2};

	uint8_t err = 0;
	uint16_t i,j;
	char8_t buffer[65];

	const uint8_t array_size = leaf->array_size;
	const uint8_t radix = leaf->type & ATUI_ANY;


	if ((leaf->type & ATUI_ARRAY) && (radix != ATUI_NAN)) {
		const uint8_t base = bases[radix];
		const uint8_t num_digits = ceil(
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
				const uint16_t bytes_left = leaf->u8 + array_size - null_exit;
				memset(null_exit-1, ' ', bytes_left); // -1 eats memccpy's 0.
			}
			leaf->u8[array_size-1] = '\0';
		}
	} else if (radix) {
		if (leaf->type & ATUI_ENUM) {
			const struct atui_enum* const enum_set = leaf->enum_options;
			const struct atui_enum_entry* entry;
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
		const atui_leaf* const leaf
		) {
#ifdef C2X_COMPAT
	const char8_t* const prefixes[] = {"", "%0", "0x%0", "0o%0", "0x%0"};
	const char8_t* const suffixes_unsigned[] = {"", "llu", "llX", "llo", "llX"};
	const char8_t* const suffixes_signed[]   = {"", "lli", "llX", "llo", "llX"};
	const uint8_t bases[] = {0, 10, 16, 8, 16};
#else
	const char8_t* const prefixes[] = {"", "%0", "0x%0", "0o%0", "0b%0"};
	const char8_t* const suffixes_unsigned[] = {"", "llu", "llX", "llo", "llb"};
	const char8_t* const suffixes_signed[]   = {"", "lli", "llX", "llo", "llb"};
	const uint8_t bases[] = {0, 10, 16, 8, 2};
#endif
	const char8_t* const metaformat = "%s%u%s"; // amogus


	const uint8_t radix = leaf->type & ATUI_ANY;
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
		const atui_leaf* const leaf,
		char8_t** buffer_ptr
		) {
	// Convert the value of a leaf to text. Currently only support for numbers,
	// and strings.

	assert(leaf->val);

	uint16_t malloc_size = 0;
	char8_t* buffer = *buffer_ptr;

	char8_t format[10];
	const uint8_t radix = leaf->type & ATUI_ANY;
	const uint8_t num_digits = _get_sprintf_format_from_leaf(format, leaf);

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

				char8_t* walked = stpcpy(
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

	const uint8_t num_bits = (leaf->bitfield_hi - leaf->bitfield_lo) +1;
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
	const uint64_t tokeep_mask = ~(maxval << leaf->bitfield_lo);
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
		const atui_leaf* const leaf
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

	const uint8_t num_unused_bits_hi = (
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
		const int64_t val
		) {
	assert(leaf->type & ATUI_ANY);
	assert(leaf->val);

	// handle Two's Complement on arbitrarily-sized ints
	uint64_t raw_val; // some bit math preserves the sign
	const uint8_t num_bits = (leaf->bitfield_hi - leaf->bitfield_lo) +1;
	const uint64_t mask = (1ULL << num_bits) - 1;
	const int64_t maxval = mask>>1; // max positive val 0111...
	if (val > maxval) {
		raw_val = maxval;
	} else if (val < -maxval) {
		raw_val = maxval+1; // Two's overflow. 1000.. is negative-most.
	} else {
		raw_val = val & mask; // Two's sign repeats to the right
	}

	// ...11111 000.. 1111...
	const uint64_t tokeep_mask = ~(mask << leaf->bitfield_lo);
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
		const atui_leaf* const leaf
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

	const uint8_t num_unused_bits_hi = (
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
		const float64_t val) {
	assert(leaf->type & ATUI_FRAC);
	assert(leaf->val);

	if (leaf->fractional_bits) {
		const float64_t max_val = (
			(float64_t)(1<<(leaf->total_bits - leaf->fractional_bits))
			- ( (float64_t)(1) / (float64_t)(1<<leaf->fractional_bits))
		);
		uint64_t fixed_val;
		if (val > max_val) {
			fixed_val = (1<<leaf->total_bits)-1;
		} else {
			fixed_val = floor(val);
			const float64_t frac = (
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
		const atui_leaf* const leaf
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



void
atui_enum_entry_to_text(
		char8_t* const buffer,
		const atui_leaf* const leaf,
		const struct atui_enum_entry* const enum_entry
		) {
	assert(leaf->type & (ATUI_ANY|ATUI_ENUM));

	char8_t format_1[10]; // stage 1
	char8_t format_2[15]; // stage 2
	_get_sprintf_format_from_leaf(format_1, leaf);
	assert(strlen(format_1) < sizeof(format_1));
	sprintf(format_2, " : %s", format_1);
	assert(strlen(format_2) < sizeof(format_2));

	char8_t* walked = stpcpy(buffer, enum_entry->name); // walk the buffer
	sprintf(walked, format_2, enum_entry->val);  // eats previous \0
	assert(strlen(buffer) < ATUI_LEAVES_STR_BUFFER);
}

int16_t
atui_enum_bsearch(
		const struct atui_enum* const enum_set,
		const int64_t val
		) {
	// binary search for atui_enum arrays.
	// as a result, it assumes the array is sorted.
	// this algo also finds the leftmost if there are duplicates
	const struct atui_enum_entry* const enum_array = enum_set->enum_array;
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
		const struct atui_enum* const enum_set,
		const int64_t val
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
		const uint8_t num_leaves
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


int64_t
strtoll_2(
		const char8_t* str
		) {
	// TODO it seems the C2X's changes for the strto* hasn't landed yet
	uint8_t base = 0; // 0 = auto
	if ((str[0] == '0') && (str[1] == 'b')) {
		base = 2;
		str += 2;
	}
	return strtoll(str, NULL, base);
}
uint64_t
strtoull_2(
		const char8_t* str
		) {
	// TODO it seems the C2X's changes for the strto* hasn't landed yet
	uint8_t base = 0; // 0 = auto
	if ((str[0] == '0') && (str[1] == 'b')) {
		base = 2;
		str += 2;
	}
	return strtoull(str, NULL, base);
}

