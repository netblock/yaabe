/*
Complementary register index/address tables for the register blocks like the
timings tables seen in umctimings.h. Mainly for assertion for expectation.

Also some tools to help write register definition tables; chiefly the ones
involving struct register_set.
The intended purpose of register_set_print_tables is to have it adjacent to
atomtree_populate_init_reg_block.
*/

#ifndef ASIC_REG_INDICES_H
#define ASIC_REG_INDICES_H

// check the bottom for more includes

struct register_set { // register set entry
	uint16_t address; // mm,ix,reg prefixed defines
	const char8_t* name;
};
#define RSE(reg_name)\
	{\
		.address = reg_name,\
		.name = #reg_name,\
	},
int16_t
register_set_bsearch(
		const struct register_set* reg_set,
		uint16_t num_reg_set_addresses,
		uint16_t address
		);
void
register_set_print_tables(
		const struct atom_init_reg_index_format* register_index,
		const struct register_set* reg_set,
		uint16_t num_reg_set_addresses
		);



uint8_t
assert_reg_index(
		const struct atom_init_reg_index_format* index,
		const uint16_t* expectation
		);


static const uint16_t mc_block_polaris_timings_addresses[] = {
	mmMC_SEQ_WR_CTL_D0_6_0,
	mmMC_SEQ_WR_CTL_D1_6_0,
	mmMC_SEQ_WR_CTL_2_6_0,
	mmMC_SEQ_PMG_TIMING_6_0,
	mmMC_SEQ_RAS_TIMING_6_0,
	mmMC_SEQ_CAS_TIMING_6_0,
	mmMC_SEQ_MISC_TIMING_6_0,
	mmMC_SEQ_MISC_TIMING2_6_0,
	mmMC_SEQ_MISC1_6_0,
	mmMC_SEQ_MISC3_6_0,
	mmMC_SEQ_MISC8_6_0,
	mmMC_ARB_DRAM_TIMING_6_0,
	mmMC_ARB_DRAM_TIMING2_6_0,
	END_OF_REG_INDEX_BLOCK
};

// only used during to develop the 'addresses' tables and 'bitfield' structs
//#include "gmc_searchfield.h"

#endif
