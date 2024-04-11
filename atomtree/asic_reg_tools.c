#include "atomtree.h"
#include <ctype.h>

uint8_t
regcmp(
		const struct atom_init_reg_index_format* const index,
		const uint16_t* const expectation
		) {
	for (uint8_t i=0; expectation[i] != END_OF_REG_INDEX_BLOCK; i++) {
		assert(index[i].RegIndex != END_OF_REG_INDEX_BLOCK);
		// expectation has no end

		if (index[i].RegIndex != expectation[i]) {
			return 0;
		}
	}
	return 1;
}
int16_t
regset_bsearch_left(
		const struct register_set* const reg_set,
		const uint16_t address
		) {
	// binary search for register_set
	// as a result, it assumes the array is sorted.
	// this algo also finds the leftmost if there are duplicates

	// reserve leftmost bit as flag

	const struct register_set_entry* const set_array = reg_set->entries;
	uint16_t left = 0;
	uint16_t mid;
	uint16_t right = reg_set->num_reg_set_addresses;
	while (left != right) {
		mid = (left + right) >> 1;  // bitshift div-by-2
		if (address <= set_array[mid].address) {
			right = mid;
		} else {
			left = mid + 1;
		}
	}
	// left==right. mid will be off by 1, leftwise, if it's unique.
	if (address == set_array[left].address) {
		return left;
	} else {
		return -1;
	}
}

int16_t
regset_bsearch_right(
		const struct register_set* const reg_set,
		const uint16_t address
		) {
	// binary search for register_set
	// as a result, it assumes the array is sorted.
	// this algo also finds the rightmost if there are duplicates

	// reserve leftmost bit as flag

	const struct register_set_entry* const set_array = reg_set->entries;
	uint16_t left = 0;
	uint16_t mid;
	uint16_t right = reg_set->num_reg_set_addresses;
	while (left != right) {
		mid = (left + right) >> 1;
		if (address < set_array[mid].address) {
			right = mid;
		} else {
			left = mid + 1;
		}
	}
	// left==right.
	// left==mid==right and will be off by +1, if rightside element is unique
	// left == (mid+1) if right-side element is not unique.
	right--;
	if (address == set_array[right].address) {
		return right;
	} else {
		return -1;
	}
}

static inline bool
is_number(
		const char8_t* str
		) {
	if (str) {
		do {
			if (0 == isdigit(*str)) {
				return false;
			}
			str++;
		} while (*str);
		return true;
	} else {
		return false;
	}
}

void
register_set_print_tables(
		const struct atomtree_init_reg_block* const at_regblock,
		const struct register_set* const reg_set,
		const bool newest
		) {
	int16_t (* regset_bsearch)(
			const struct register_set* reg_set,
			uint16_t address
			); // function pointer
	if (newest) {
		regset_bsearch = regset_bsearch_right;
	} else {
		regset_bsearch = regset_bsearch_left;
	}

	const struct atom_init_reg_index_format* const register_index =
		at_regblock->register_index;
	const char8_t* const struct_entry = u8"\tunion %s  %s;\n";

	const char8_t* reg_name;
	char* token_save;
	const char8_t* token;
	char8_t tokens[16][16];
	uint8_t num_tokens;
	uint8_t tokens_i;
	char8_t temp_buffer[64];
	char8_t name_buffer[64];
	char8_t* name_ptr;
	char8_t union_name[64];
	uint8_t str_i;

	int16_t set_loc;
	uint16_t rii;

	printf(u8"\nSTART\n\n");
	// print assert-reg-index body
	for (rii=0; register_index[rii].RegIndex != END_OF_REG_INDEX_BLOCK; rii++) {
		set_loc = regset_bsearch(reg_set, register_index[rii].RegIndex);
		// if this fails, we don't have the index and thus bitfield
		assert(0 <= set_loc);
		printf(u8"\t%s,\n", reg_set->entries[set_loc].name);
	}

	printf(u8"\nEND: %u+1 regs\nSTART\n\n", rii); // +1 is end
	// print bitfield struct body

	uint16_t unions = 0;
	bool access_range = 0;
	uint8_t pre_reg_data_lo;
	for (rii=0; register_index[rii].RegIndex != END_OF_REG_INDEX_BLOCK; rii++) {
		pre_reg_data_lo = register_index[rii].PreRegDataLength & 0xF;
		if (VALUE_SAME_AS_ABOVE == pre_reg_data_lo) {
			continue;
		}
		if (access_range) {
			if (INDEX_ACCESS_RANGE_END == pre_reg_data_lo) {
				access_range = 0;
			}
			continue;
		}
		if (INDEX_ACCESS_RANGE_BEGIN == pre_reg_data_lo) {
			access_range = 1;
		}

		set_loc = regset_bsearch(reg_set, register_index[rii].RegIndex);

		// lop off prefix
		reg_name = reg_set->entries[set_loc].name;
		if (strncmp(reg_name, u8"mm",2) || strncmp(reg_name, u8"ix",2)) {
			reg_name += 2;
		} else if (strncmp(reg_name, u8"reg",3)) {
			reg_name += 3;
		} else {
			reg_name += 0;
		}

		// lower case, and copy into temp buffer for tokenisation
		for (str_i=0; reg_name[str_i]; str_i++) {
			temp_buffer[str_i] = tolower(reg_name[str_i]);
		}
		temp_buffer[str_i] = '\0';
		assert(strlen(temp_buffer) < sizeof(temp_buffer));

		strcpy(union_name, temp_buffer);


		// lop off the version bits at the end
		tokens_i = 0;
		token_save = NULL;
		name_ptr = name_buffer;
		token = strtok_r(temp_buffer, u8"_", &token_save);
		while (token) { // tokenise the string
			assert(strlen(token) < sizeof(tokens[0]));
			strcpy(tokens[tokens_i], token);
			tokens_i++;
			token = strtok_r(NULL, u8"_", &token_save);
		}
		assert(tokens_i);
		// lop off trailing tokens that are numbers
		tokens_i--;
		for (; (0 < tokens_i) && is_number(tokens[tokens_i]); tokens_i--);
		num_tokens = tokens_i + 1; //tokens_i++;
		for (tokens_i=0; tokens_i < num_tokens; tokens_i++) { // join the str
			name_ptr = stpcpy(name_ptr, tokens[tokens_i]);
			*name_ptr = '_';
			assert(name_ptr > name_buffer);
		}
		*name_ptr = '\0';
		assert(strlen(name_buffer) < sizeof(name_buffer));


		printf(struct_entry, union_name, name_buffer);
		unions++;
	}
	printf(u8"\nEND: %u+1 unions\n\n",unions); // is block_id
}
