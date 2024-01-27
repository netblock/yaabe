#include "atomtree.h"
#include <ctype.h>
#include <string.h>

uint8_t
assert_reg_index(
		const struct atom_init_reg_index_format* const index,
		const uint16_t* const expectation
		) {
	for (uint8_t i=0; expectation[i] != END_OF_REG_INDEX_BLOCK; i++) {
		if (index[i].RegIndex != expectation[i]) {
			return 0;
		}
	}
	return 1;
}

int16_t
register_set_bsearch(
		const struct register_set* const reg_set,
		const uint16_t num_reg_set_addresses,
		const uint16_t address
		) {
	// binary search for register_set
	// as a result, it assumes the array is sorted.
	// this algo also finds the leftmost if there are duplicates
	assert(num_reg_set_addresses < 0x7FFF); // reserve leftmost bit as flag
	uint16_t left = 0;
	uint16_t mid;
	uint16_t right = num_reg_set_addresses;
	while (left != right) {
		mid = (left + right) >> 1;  // bitshift div-by-2
		if (address <= reg_set[mid].address) {
			right = mid;
		} else {
			left = mid + 1;
		}
	}
	// left==right. mid will be off by 1, leftwise, if it's unique.
	if (left == num_reg_set_addresses) {
		return -1;
	} else {
		return left;
	}
}

static inline bool
is_number(
		const char8_t* str
		) {
	if (*str) {
		do {
			if (0 == isdigit(*str)) {
				return 0;
			}
			str++;
		} while (*str);
		return 1;
	} else {
		return 0;
	}
}

void
register_set_print_tables(
		const struct atom_init_reg_index_format* const register_index,
		const struct register_set* const reg_set,
		const uint16_t num_reg_set_addresses
		) {
	const char8_t* const struct_entry = u8"\tunion %s  %s;\n";
	
	const char8_t* reg_name;
	char* token_save;
	char8_t* token;
	char8_t temp_buffer[64];
	char8_t var_name[64];
	char8_t* name;
	char8_t union_name[64];
	uint8_t s_i;

	int16_t set_loc;
	uint16_t rii, unions;

	printf("\nSTART\n\n");
	// print assert-reg-index body
	for (rii=0; register_index[rii].RegIndex != END_OF_REG_INDEX_BLOCK; rii++) {
		set_loc = register_set_bsearch(
			reg_set, num_reg_set_addresses, register_index[rii].RegIndex
		);

		// if this fails, we don't have the index and thus bitfield
		assert(0 <= set_loc);

		printf(u8"\t%s,\n", reg_set[set_loc].name);
	}

	printf(u8"\nEND: %u regs\nSTART\n\n", rii);
	// print bitfield struct body
	unions = 0;
	for (rii=0; register_index[rii].RegIndex != END_OF_REG_INDEX_BLOCK; rii++) {
		if ( 4 != (register_index[rii].PreRegDataLength&0xF) ) {
			// first nibble is byte count of reg entry; if not 4, skip
			continue;
		}
		set_loc = register_set_bsearch(
			reg_set, num_reg_set_addresses, register_index[rii].RegIndex
		);

		// lop off prefix
		reg_name = reg_set[set_loc].name;
		if (strncmp(reg_name, u8"mm",2) || strncmp(reg_name, u8"ix",2)) {
			reg_name += 2;
		} else if (strncmp(reg_name, u8"reg",3)) {
			reg_name += 3;
		} else {
			reg_name += 0;
		}

		// lower case, and copy into temp buffer for tokenisation
		for (s_i=0; reg_name[s_i]; s_i++) {
			temp_buffer[s_i] = tolower(reg_name[s_i]);
		}
		temp_buffer[s_i] = '\0';
		assert(strlen(temp_buffer) < sizeof(temp_buffer));

		strcpy(union_name, temp_buffer);

		// lop off the version bits at the end
		// could be faster, but it isn't critical
		token_save = NULL;
		name = var_name;
		token = strtok_r(temp_buffer, u8"_", &token_save);
		while (token) {
			if (0 == is_number(token)) { 
				name = memccpy(name, token, '\0', sizeof(var_name));
				*(name-1) = '_';
			}
			token = strtok_r(NULL, u8"_", &token_save);
		}
		assert(name > var_name);
		assert(strlen(var_name) < sizeof(var_name));
		*(name-1) = '\0';

		printf(struct_entry, union_name, var_name);
		unions++;
	}
	printf(u8"\nEND: %u unions\n\n",unions);
}
