#include "standard.h"
#include "atomtree.h"
#include "atui.h"

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
static regset_bsearch_func const regset_bsearch_bool[] = {
	regset_bsearch_left,
	regset_bsearch_right,
};

static bool
register_index_is_meta(
		uint8_t PreRegDataLength,
		bool* access_range
		) {
	uint8_t const pre_reg_data_lo = PreRegDataLength & 0xF;
	if (VALUE_SAME_AS_ABOVE == pre_reg_data_lo) {
		return true;
	}
	if (*access_range) {
		if (INDEX_ACCESS_RANGE_END == pre_reg_data_lo) {
			*access_range = false;
		}
		return true;
	}
	if (INDEX_ACCESS_RANGE_BEGIN == pre_reg_data_lo) {
		*access_range = true;
		return false;
	}
	return false;
}

struct register_set_entry*
register_set_build_atuifunc_playlist(
		struct atomtree_init_reg_block const* const at_regblock,
		struct register_set const* const reg_set,
		bool const newest
		) {
	if (0 == at_regblock->num_data_entries) {
		return NULL;
	}
	struct atom_init_reg_index_format const* const register_index =
		at_regblock->register_index;
	regset_bsearch_func const regset_bsearch = regset_bsearch_bool[newest];

	struct register_set_entry* playlist = malloc(
		at_regblock->num_data_entries * sizeof(struct register_set_entry)
	);
	uint8_t playlist_i = 0;

	bool access_range = 0;
	for (uint8_t rii=0; rii < (at_regblock->num_index-1); rii++) {
		bool should_continue = register_index_is_meta(
			register_index[rii].PreRegDataLength,  &access_range
		);
		if (should_continue) {
			continue;
		}
		int16_t set_loc = regset_bsearch(reg_set, register_index[rii].RegIndex);
		if (0 <= set_loc) {
			playlist[playlist_i] = reg_set->entries[set_loc];
		} else { // unknown index
			playlist[playlist_i] = (struct register_set_entry) {
				.address = register_index[rii].RegIndex,				
				.atui_branch_func = ATUI_FUNC(unknown_reg_data),
			};
		}
		playlist_i++;
	}

	return playlist;
}


void
register_set_print_tables(
		struct atomtree_init_reg_block const* const at_regblock,
		struct register_set const* const reg_set,
		bool const newest,
		char const* name
		) {
	regset_bsearch_func const regset_bsearch = regset_bsearch_bool[newest];

	if (NULL == name) {
		name = "";
	}

	struct atom_init_reg_index_format const* const register_index =
		at_regblock->register_index;
	char const* const struct_entry = "\tunion %s  %s;\n";

	char const* reg_name;
	char const* union_name;
	char* token_save;
	char const* token;
	char tokens[16][16];
	uint8_t num_tokens;
	uint8_t tokens_i;
	char temp_buffer[64];
	char name_buffer[64];
	char* name_ptr;
	uint8_t str_i;

	int16_t set_loc;

	// print assert-reg-index body
	printf(
		"{type: \"uint16_t\", name: \"%s\", // %u+1\n"
		"\tconstants: [\n",
		name, (at_regblock->num_index-1)
	);
	for (uint8_t rii=0; rii < (at_regblock->num_index-1); rii++) {
		set_loc = regset_bsearch(reg_set, register_index[rii].RegIndex);
		// if this fails, we don't have the index and thus bitfield
		assert(0 <= set_loc);
		printf("\t\t\"%s\",\n", reg_set->entries[set_loc].index_name);
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
	for (uint8_t rii=0; rii < (at_regblock->num_index-1); rii++) {
		bool should_continue = register_index_is_meta(
			register_index[rii].PreRegDataLength,  &access_range
		);
		if (should_continue) {
			continue;
		}

		set_loc = regset_bsearch(reg_set, register_index[rii].RegIndex);
		union_name = reg_set->entries[set_loc].field_name;

		// lop off the version bits at the end
		strcpy(temp_buffer, union_name);
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
