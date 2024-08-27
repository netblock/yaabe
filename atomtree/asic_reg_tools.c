#include "standard.h"
#include "atomtree.h"

uint8_t
regcmp(
		struct atom_init_reg_index_format const* const index,
		uint16_t const* const expectation
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
		struct register_set const* const reg_set,
		uint16_t const address
		) {
	// binary search for register_set
	// as a result, it assumes the array is sorted.
	// this algo also finds the leftmost if there are duplicates

	// reserve leftmost bit as flag

	struct register_set_entry const* const set_array = reg_set->entries;
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
		struct register_set const* const reg_set,
		uint16_t const address
		) {
	// binary search for register_set
	// as a result, it assumes the array is sorted.
	// this algo also finds the rightmost if there are duplicates

	// reserve leftmost bit as flag

	struct register_set_entry const* const set_array = reg_set->entries;
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


void
register_set_print_tables(
		struct atomtree_init_reg_block const* const at_regblock,
		struct register_set const* const reg_set,
		bool const newest,
		char const* name
		) {
	int16_t (* regset_bsearch)(
			struct register_set const* reg_set,
			uint16_t address
			); // function pointer
	if (newest) {
		regset_bsearch = regset_bsearch_right;
	} else {
		regset_bsearch = regset_bsearch_left;
	}

	if (NULL == name) {
		name = "";
	}

	struct atom_init_reg_index_format const* const register_index =
		at_regblock->register_index;
	char const* const struct_entry = "\tunion %s  %s;\n";

	char const* reg_name;
	char* token_save;
	char const* token;
	char tokens[16][16];
	uint8_t num_tokens;
	uint8_t tokens_i;
	char temp_buffer[64];
	char name_buffer[64];
	char* name_ptr;
	char union_name[64];
	uint8_t str_i;

	int16_t set_loc;
	uint16_t rii;

	// print assert-reg-index body
	for (rii=0; register_index[rii].RegIndex != END_OF_REG_INDEX_BLOCK; rii++);
	printf(
		"{type: \"uint16_t\", name: \"%s\", // %u+1\n"
		"\tconstants: [\n",
		name, rii
	);
	for (rii=0; register_index[rii].RegIndex != END_OF_REG_INDEX_BLOCK; rii++) {
		set_loc = regset_bsearch(reg_set, register_index[rii].RegIndex);
		// if this fails, we don't have the index and thus bitfield
		assert(0 <= set_loc);
		printf("\t\t\"%s\",\n", reg_set->entries[set_loc].name);
	}

	printf(
		"\t\t\"END_OF_REG_INDEX_BLOCK\",\n"
		"]},\n"
		"\n"
		"struct %s {\n"
		"\tunion atom_mc_register_setting_id  block_id;\n",
		name
	);

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
		if (strncmp(reg_name, "mm",2) || strncmp(reg_name, "ix",2)) {
			reg_name += 2;
		} else if (strncmp(reg_name, "reg",3)) {
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
		token = strtok_r(temp_buffer, "_", &token_save);
		while (token) { // tokenise the string
			assert(strlen(token) < sizeof(tokens[0]));
			strcpy(tokens[tokens_i], token);
			tokens_i++;
			token = strtok_r(NULL, "_", &token_save);
		}
		assert(tokens_i);
		// lop off trailing tokens that are numbers
		tokens_i--;
		for (; (0 < tokens_i) && is_number(tokens[tokens_i]); tokens_i--);
		num_tokens = tokens_i + 1; //tokens_i++;
		for (tokens_i=0; tokens_i < num_tokens; tokens_i++) { // join the str
			name_ptr = stopcopy(name_ptr, tokens[tokens_i]);
			*name_ptr = '_';
			name_ptr++;
			assert(name_ptr > name_buffer);
		}
		name_ptr--;
		*name_ptr = '\0';
		assert(strlen(name_buffer) < sizeof(name_buffer));


		printf(struct_entry, union_name, name_buffer);
		unions++;
	}
	printf(
		"};\n"
		"// %u bytes\n"
		"// %u+1 unions\n"
		"\n",
		(unions+1)*4,
		unions
	);
}
