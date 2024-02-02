/*
Complementary register index/address tables for the register blocks like the
timings tables seen in umctimings.h. Mainly for assertion for expectation.

Also some tools to help write register definition tables; chiefly the ones
involving struct register_set.
The intended purpose of register_set_print_tables is to have it adjacent to
atomtree_populate_init_reg_block.

register_set_print_tables(&(vi21->mem_clk_patch), &GMC_reg_set);
*/

#ifndef ASIC_REG_INDICES_H
#define ASIC_REG_INDICES_H

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
register_set_print_tables(
		const struct atomtree_init_reg_block* at_regblock,
		const struct register_set* reg_set
		);


// compare register index sequences. expectation asserts END_OF_REG_INDEX_BLOCK
uint8_t
regcmp(
		const struct atom_init_reg_index_format* index,
		const uint16_t* expectation
		);


static const uint16_t mc_block_islands_gddr5_timings_addresses[] = {
	// Northern, Southern, Sea, Volcanic Islands
	mmMC_SEQ_WR_CTL_D0_6_0,
	mmMC_SEQ_WR_CTL_D1_6_0,
	mmMC_SEQ_WR_CTL_2_6_0,
	mmMC_SEQ_RAS_TIMING_6_0,
	mmMC_SEQ_CAS_TIMING_6_0,
	mmMC_SEQ_MISC_TIMING_6_0,
	mmMC_SEQ_MISC_TIMING2_6_0,
	mmMC_SEQ_PMG_TIMING_6_0,
	mmMC_SEQ_MISC1_6_0,
	mmMC_SEQ_MISC3_6_0,
	mmMC_SEQ_MISC8_6_0,
	mmMC_ARB_DRAM_TIMING_6_0,
	mmMC_ARB_DRAM_TIMING2_6_0,
	END_OF_REG_INDEX_BLOCK
};
static const uint16_t mc_block_islands_gddr5_timings_addresses_type2[] = {
	mmMC_SEQ_WR_CTL_D0_6_0,
	mmMC_SEQ_WR_CTL_D1_6_0,
	mmMC_SEQ_WR_CTL_2_6_0,
	mmMC_SEQ_RAS_TIMING_6_0,
	mmMC_SEQ_CAS_TIMING_6_0,
	mmMC_SEQ_MISC_TIMING_6_0,
	mmMC_SEQ_MISC_TIMING2_6_0,
	mmMC_SEQ_PMG_TIMING_6_0,
	mmMC_SEQ_MISC1_6_0,
	mmMC_SEQ_RESERVE_M_6_0,
	mmMC_SEQ_MISC8_6_0,
	mmMC_ARB_DRAM_TIMING_6_0,
	mmMC_ARB_DRAM_TIMING2_6_0,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t mc_block_fiji_timings_addresses[] = {
	mmMC_SEQ_CAS_TIMING_6_0,
	mmMC_SEQ_MISC_TIMING2_6_0,
	mmMC_SEQ_RD_CTL_D0_6_0,
	mmMC_SEQ_WR_CTL_D0_6_0,
	mmMC_SEQ_CMD_6_0,
	mmMC_SEQ_RXFRAMING_EDC_D1_6_0,
	mmMC_ARB_DRAM_TIMING_6_0,
	mmMC_ARB_DRAM_TIMING2_6_0,
	mmMC_ARB_BURST_TIME_6_0,
	END_OF_REG_INDEX_BLOCK
};

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

#include "gmc_searchfield.h"

#endif
