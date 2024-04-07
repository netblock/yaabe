/*
Some tools to help write register definition tables; chiefly the ones involving 
struct register_set.
The intended purpose of register_set_print_tables is to have it adjacent to
atomtree_populate_init_reg_block.

register_set_print_tables(&(vi21->mem_clk_patch), &GMC_reg_set);
*/

#ifndef ASIC_REG_TOOLS_H
#define ASIC_REG_TOOLS_H

// check the bottom for more includes


struct register_set_entry { // register set entry
	uint16_t address; // mm,ix,reg prefixed defines
	const char8_t* name;
};
struct register_set {
	uint16_t num_reg_set_addresses;
	const char8_t* set_name;
	const struct register_set_entry* entries;
};
#define RSE(reg_name)\
	{\
		.address = reg_name,\
		.name = u8###reg_name,\
	},

int16_t
regset_bsearch_left(
		const struct register_set* reg_set,
		uint16_t address
		);
int16_t
regset_bsearch_right(
		const struct register_set* reg_set,
		uint16_t address
		);
void
register_set_print_tables( // entirely a developer's tool
		const struct atomtree_init_reg_block* at_regblock,
		const struct register_set* reg_set,
		bool newest // suggest oldest or newest if there's multiple versions
		);


// compare register index sequences. expectation asserts END_OF_REG_INDEX_BLOCK
uint8_t
regcmp(
		const struct atom_init_reg_index_format* index,
		const uint16_t* expectation
		);

#include "gmc_searchfield.h"

#endif
