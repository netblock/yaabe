/*
Complementary register index/address tables for the register blocks like the
timings tables seen in umctimings.h. Mainly for assertion for expectation.
*/

#ifndef ASIC_REG_INDICES_H
#define ASIC_REG_INDICES_H

uint8_t
assert_reg_index(
		const struct atom_init_reg_index_format* const index,
		const uint16_t* const expectation
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

#endif
