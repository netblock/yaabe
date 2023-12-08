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
	const uint64_t maxval = (1ULL << num_bits) - 1;
	if (val > maxval)
		val = maxval;

	// ...11111 000.. 1111...
	const uint64_t tokeep_mask = ~(maxval << leaf->bitfield_lo);
	val <<= leaf->bitfield_lo;
	*(leaf->u64) = (*(leaf->u64) & tokeep_mask) | val;
}
uint64_t atui_leaf_get_val_unsigned(atui_leaf* leaf) {
	if (!(leaf->type & ATUI_ANY)) {
		assert(0);
	}
	uint64_t val = *(leaf->u64);
	const uint8_t num_unused_bits_hi = sizeof(val)*8 - leaf->bitfield_hi -1;
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
	*(leaf->u64) = (*(leaf->u64) & tokeep_mask) | raw_val;
}
int64_t atui_leaf_get_val_signed(atui_leaf* leaf) {
	if (!(leaf->type & ATUI_ANY)) {
		assert(0);
	}

	int64_t val = *(leaf->u64);
	const uint8_t num_unused_bits_hi = sizeof(val)*8 - leaf->bitfield_hi -1;
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
		const float64_t frac = (val - floor(val)) * (1<<leaf->fractional_bits);
		uint64_t fixed_val = floor(val);
		fixed_val <<= leaf->fractional_bits;
		fixed_val += frac;
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
					leaf->u8[i] = (uint8_t)strtoll(buffer, NULL, base);
					j += num_digits;
					if (text[j] == ' ')
						j++;
				}
				break;
			case 16:
				for(; i < leaf->array_size; i++) {
					memcpy(buffer, text+j, num_digits);
					leaf->u16[i] = (uint16_t)strtoll(buffer, NULL, base);
					j += num_digits;
					if (text[j] == ' ')
						j++;
				}
				break;
			case 32:
				for(; i < leaf->array_size; i++) {
					memcpy(buffer, text+j, num_digits);
					leaf->u32[i] = (uint32_t)strtoll(buffer, NULL, base);
					j += num_digits;
					if (text[j] == ' ')
						j++;
				}
				break;
			case 64:
				for(; i < leaf->array_size; i++) {
					memcpy(buffer, text+j, num_digits);
					leaf->u64[i] = (uint64_t)strtoll(buffer, NULL, base);
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
	const char8_t* const suffixes_unsigned[] = {"", "u", "X", "o", "X"};
	const char8_t* const suffixes_signed[]   = {"", "i", "X", "o", "X"};
	const uint8_t bases[] = {0, 10, 16, 8, 16};
#else
	const char8_t* const prefixes[] = {"", "%0", "0x%0", "0o%0", "0b%0"};
	const char8_t* const suffixes_unsigned[] = {"", "u", "X", "o", "b"};
	const char8_t* const suffixes_signed[]   = {"", "i", "X", "o", "b"};
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



void atui_destroy_tree(atui_branch* tree) { // a reference implementation
	while(tree->max_all_branch_count--)
		atui_destroy_tree(tree->all_branches[tree->max_all_branch_count]);
	free(tree);
}
