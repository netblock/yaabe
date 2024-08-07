/*
Some tools to help write register definition tables; chiefly the ones involving
struct register_set.
The intended purpose of register_set_print_tables is to have it adjacent to
atomtree_populate_init_reg_block.

register_set_print_tables(&(vi21->mem_clk_patch), &GMC_reg_set, NULL);
*/

#ifndef ASIC_REG_TOOLS_H
#define ASIC_REG_TOOLS_H

// check the bottom for more includes


struct register_set_entry { // register set entry
	uint16_t address; // mm,ix,reg prefixed defines
	char const* name;
};
struct register_set {
	uint16_t num_reg_set_addresses;
	char const* set_name;
	struct register_set_entry const* entries;
};
#define RSE(reg_name)\
	{\
		.address = reg_name,\
		.name = u8###reg_name,\
	},

int16_t
regset_bsearch_left(
		struct register_set const* reg_set,
		uint16_t address
		);
int16_t
regset_bsearch_right(
		struct register_set const* reg_set,
		uint16_t address
		);
void
register_set_print_tables( // entirely a developer's tool
		struct atomtree_init_reg_block const* at_regblock,
		struct register_set const* reg_set,
		bool newest, // suggest oldest or newest if there's multiple versions
		char const* name
		);


// compare register index sequences. expectation asserts END_OF_REG_INDEX_BLOCK
uint8_t
regcmp(
		struct atom_init_reg_index_format const* index,
		uint16_t const* expectation
		);


// ppatui.py autogenerated:
#include "gmc_searchfield.h"

#endif
