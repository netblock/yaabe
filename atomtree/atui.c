/*
AtomTree iterable interface for UIs.

See ppatui.h for the metaprogramming and atui.h for general API.
*/

#include "atomtree.h"
#include "atui.h"
#include <math.h>

void atui_leaf_set_val_unsigned(atui_leaf* leaf, uint64_t val) {
	if (!(leaf->type & ATUI_ANY)) {
		assert(0);
	}

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
uint64_t atui_leaf_get_val_unsigned(atui_leaf* leaf) {
	if (!(leaf->type & ATUI_ANY)) {
		assert(0);
	}

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
void atui_leaf_set_val_signed(atui_leaf* leaf, int64_t val) {
	if (!(leaf->type & ATUI_ANY)) {
		assert(0);
	}

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
int64_t atui_leaf_get_val_signed(atui_leaf* leaf) {
	if (!(leaf->type & ATUI_ANY)) {
		assert(0);
	}

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
void atui_leaf_set_val_fraction(atui_leaf* leaf, float64_t val) {
	if (!(leaf->type & ATUI_FRAC)) {
		assert(0);
	}

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
float64_t atui_leaf_get_val_fraction(atui_leaf* leaf) {
	if (!(leaf->type &  ATUI_FRAC)) {
		assert(0);
	}

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

int64_t strtoll_2(const char8_t* str) {
	// TODO it seems the C2X's changes for the strto* hasn't landed yet
	uint8_t base = 0; // 0 = auto
	if ((str[0] == '0') && (str[1] == 'b')) {
		base = 2;
		str += 2;
	}
	return strtoll(str, NULL, base);
}
uint64_t strtoull_2(const char8_t* str) {
	// TODO it seems the C2X's changes for the strto* hasn't landed yet
	uint8_t base = 0; // 0 = auto
	if ((str[0] == '0') && (str[1] == 'b')) {
		base = 2;
		str += 2;
	}
	return strtoull(str, NULL, base);
}


uint8_t atui_set_from_text(atui_leaf* leaf, const char8_t* text) {
	//set the value of the leaf based on input text. Currently only support for
	// numbers (including bitfields) and strings.

	const uint8_t bases[] = {0, 10, 16, 8, 2};

	uint8_t err = 0;
	uint16_t i=0,j = 0;
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
				return 1;
		}
	} else if (leaf->type & (ATUI_STRING|ATUI_ARRAY)) {
		assert(radix == ATUI_NAN); // mainly for ATUI_ARRAY && ATUI_NAN
		char8_t* null_exit = memccpy(leaf->u8, text, '\0', array_size);

		if (leaf->type & ATUI_STRING) {
			/* ATUI_STRING's length is implicitly defined by the null
			termination. If the input buffer 0-terminates before array_size,
			then we will lose the intended allocation size in the bios. So fill
			the remaining bytes with spaces to push the null back to its
			original position.
			*/
			const uint8_t bytes_left = leaf->u8 + array_size - null_exit;
			if (null_exit && bytes_left) {
				memset(null_exit-1, ' ', bytes_left); // -1 eats memccpy's 0.
				leaf->u8[array_size-1] = '\0';
			}
		}
	} else if (radix) {
		if (leaf->type & ATUI_FRAC) {
			atui_leaf_set_val_fraction(leaf, strtod(text, NULL));
		} else if (leaf->type & ATUI_SIGNED) {
			atui_leaf_set_val_signed(leaf, strtoll_2(text));
		} else {
			atui_leaf_set_val_unsigned(leaf, strtoull_2(text));
		}
	} else {
		err = 1;
	}
	return err;
}
uint16_t atui_get_to_text(atui_leaf* leaf, char8_t** buffer_ptr) {
	// Convert the value of a leaf to text. Currently only support for numbers,
	// and strings.

	uint16_t malloc_size = 0;
	uint16_t i=0,j=0;
	char8_t* buffer = *buffer_ptr;


	// constructor arrays to be used with metaformat, and two sprintfs. See the
	// radix-only part.
	// NAN DEC HEX OCT BIN
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
	char8_t format[8];


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

		malloc_size = (num_digits * leaf->array_size) + 1;
		if (malloc_size > ATUI_LEAVES_STR_BUFFER) {
			buffer = malloc(malloc_size);
			buffer[0] = '\0';
			*buffer_ptr = buffer;
		} else {
			malloc_size = 0;
		}
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
		if (leaf->array_size >= ATUI_LEAVES_STR_BUFFER) {
			malloc_size = leaf->array_size + 1;
			buffer = malloc(malloc_size);
			*buffer_ptr = buffer;
		}
		memcpy(buffer, leaf->u8, leaf->array_size);
		buffer[leaf->array_size] = '\0'; // if array is not null-terminated
	} else if (radix) {
		if (leaf->type & ATUI_FRAC) {
			// %G format can have agressive rounding: Q14.2 16383.75 -> 16383.8
			sprintf(buffer, "%G", atui_leaf_get_val_fraction(leaf));
		} else if (leaf->type & ATUI_SIGNED) {
			sprintf(format, metaformat,
				prefixes[radix], num_digits, suffixes_signed[radix]
			);
			sprintf(buffer, format, atui_leaf_get_val_signed(leaf));
		} else {
			sprintf(format, metaformat,
				prefixes[radix], num_digits, suffixes_unsigned[radix]
			);
			sprintf(buffer, format, atui_leaf_get_val_unsigned(leaf));
		}
	}

	return malloc_size;
}

int16_t
atui_enum_bsearch(
		int64_t val,
		const struct atui_enum* const enum_set
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
	if (left == enum_set->num_entries) {
		return -1;
	} else {
		return left;
	}
}



void atui_destroy_tree(atui_branch* tree) { // a reference implementation
	while(tree->max_all_branch_count--) {
		atui_destroy_tree(tree->all_branches[tree->max_all_branch_count]);
	}
	free(tree);
}
