/*
Register index playback of common asic register tables
See also asic_reg_data_tables.h
*/

#ifndef ASIC_REG_INDICES_H
#define ASIC_REG_INDICES_H

#define END_OF_REG_INDEX_BLOCK  0xFFFF

/******************************************************************************/
// Address arrays from reg_index as a fingerprint for what struct to use.
// see umctimings.h and gmc.h
/******************************************************************************/

/******************************************************************************/
// mem_clk_patch table; timings
/******************************************************************************/

static const uint16_t mc_block_r600_gddr3_memclkpatch_addresses[] = { // 20+1
	mmMC_ARB_PERF_CID_7_1,
	mmMC_ARB_SNOOP_8_1,
	mmMC_ARB_LAZY1_WR_6_0,
	mmMC_ARB_AGE_RD_6_0,
	mmMC_ARB_GRUB_8_1,
	mmMC_ARB_GECC2_6_0,
	mmMC_ARB_AGE_WR_6_0,
	mmMC_ARB_RFSH_CNTL_6_0,
	mmMC_ARB_RTT_CNTL0_6_0,
	mmMC_ARB_RTT_CNTL1_6_0,
	mmMC_ARB_REMREQ_6_0,
	mmMC_ARB_REPLAY_6_0,
	mmMC_ARB_RTT_CNTL2_6_0,
	mmMC_ARB_RTT_DEBUG_6_0,
	mmMC_ARB_RET_CREDITS_RD_6_0,
	mmMC_ARB_RET_CREDITS_WR_6_0,
	mmMC_ARB_RAMCFG_6_0,
	mmMC_ARB_POP_6_0,
	mmMC_ARB_CG_6_0,
	mmMC_ARB_GRUB_REALTIME_WR_8_1,
	END_OF_REG_INDEX_BLOCK
};
static const uint16_t mc_block_r600_gddr4_memclkpatch_addresses[] = { // 16+1
	mmMC_ARB_PERF_CID_7_1,
	mmMC_ARB_SNOOP_8_1,
	mmMC_ARB_LAZY1_WR_6_0,
	mmMC_ARB_AGE_RD_6_0,
	mmMC_ARB_GRUB_8_1,
	mmMC_ARB_GECC2_6_0,
	mmMC_ARB_AGE_WR_6_0,
	mmMC_ARB_RFSH_CNTL_6_0,
	mmMC_ARB_RTT_CNTL0_6_0,
	mmMC_ARB_RTT_CNTL1_6_0,
	mmMC_ARB_REMREQ_6_0,
	mmMC_ARB_REPLAY_6_0,
	mmMC_ARB_RTT_CNTL2_6_0,
	mmMC_ARB_RTT_DEBUG_6_0,
	mmMC_ARB_RET_CREDITS_RD_6_0,
	mmMC_ARB_RET_CREDITS_WR_6_0,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t timings_set_islands_type1_addresses[] = { // 13+1
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
static const uint16_t timings_set_islands_type2_addresses[] = { // 13+1
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

static const uint16_t timings_set_fiji_addresses[] = { // 9+1
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

static const uint16_t timings_set_polaris_addresses[] = { // 13+1
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

/******************************************************************************/
// mem_adjust table
// uncertain the accuracy of all of these tables.
/******************************************************************************/

static const uint16_t mem_adjust_set_terascale2_ddr3_addresses[] = { // 53+1
	mmMC_SEQ_IO_RESERVE_D0_6_0,
	mmMC_SEQ_IO_RESERVE_D1_6_0,
	mmMC_IO_TXCNTL_DPHY0_D0_6_0,
	mmMC_IO_TXCNTL_DPHY0_D1_6_0,
	mmMC_IO_TXCNTL_DPHY1_D0_6_0,
	mmMC_IO_TXCNTL_DPHY1_D1_6_0,
	mmMC_IO_TXCNTL_APHY_D0_6_0,
	mmMC_IO_TXCNTL_APHY_D1_6_0,
	mmMC_IO_RXCNTL_DPHY0_D0_6_0,
	mmMC_IO_RXCNTL_DPHY0_D1_6_0,
	mmMC_IO_RXCNTL_DPHY1_D0_6_0,
	mmMC_IO_RXCNTL_DPHY1_D1_6_0,
	mmMC_IO_DPHY_STR_CNTL_D0_7_1,
	mmMC_IO_DPHY_STR_CNTL_D1_7_1,
	mmMC_IO_APHY_STR_CNTL_D0_6_0,
	mmMC_IO_APHY_STR_CNTL_D1_6_0,
	mmMC_PMG_CFG_6_0,
	mmMC_PMG_AUTO_CFG_6_0,
	mmMC_SEQ_PMG_TIMING_6_0,
	mmMC_SEQ_WR_CTL_D0_6_0,
	mmMC_SEQ_WR_CTL_D1_6_0,
	mmMC_IO_PAD_CNTL_D0_6_0,
	mmMC_IO_PAD_CNTL_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_RXPHASE_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_RXPHASE_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_RXPHASE_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_RXPHASE_D1_6_0,
	ixMC_IO_DEBUG_WCK_RXPHASE_D0_6_0,
	ixMC_IO_DEBUG_WCK_RXPHASE_D1_6_0,
	ixMC_IO_DEBUG_EDC_RXPHASE_D0_6_0,
	ixMC_IO_DEBUG_EDC_RXPHASE_D1_6_0,
	ixMC_IO_DEBUG_DBI_RXPHASE_D0_6_0,
	ixMC_IO_DEBUG_DBI_RXPHASE_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_DBI_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_DBI_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_WCK_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_WCK_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_EDC_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_EDC_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D1_6_0,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t mem_adjust_set_terascale2_gddr5_type3_addresses[] = { // 63+1
	mmMC_SEQ_IO_RESERVE_D0_6_0,
	mmMC_SEQ_IO_RESERVE_D1_6_0,
	mmMC_IO_TXCNTL_DPHY0_D0_6_0,
	mmMC_IO_TXCNTL_DPHY0_D1_6_0,
	mmMC_IO_TXCNTL_DPHY1_D0_6_0,
	mmMC_IO_TXCNTL_DPHY1_D1_6_0,
	mmMC_IO_TXCNTL_APHY_D0_6_0,
	mmMC_IO_TXCNTL_APHY_D1_6_0,
	mmMC_IO_RXCNTL_DPHY0_D0_6_0,
	mmMC_IO_RXCNTL_DPHY0_D1_6_0,
	mmMC_IO_RXCNTL_DPHY1_D0_6_0,
	mmMC_IO_RXCNTL_DPHY1_D1_6_0,
	mmMC_IO_DPHY_STR_CNTL_D0_7_1,
	mmMC_IO_DPHY_STR_CNTL_D1_7_1,
	mmMC_IO_APHY_STR_CNTL_D0_6_0,
	mmMC_IO_APHY_STR_CNTL_D1_6_0,
	mmMC_PMG_CFG_6_0,
	mmMC_PMG_AUTO_CFG_6_0,
	mmMC_SEQ_PMG_TIMING_6_0,
	mmMC_SEQ_WR_CTL_D0_6_0,
	mmMC_SEQ_WR_CTL_D1_6_0,
	mmMC_IO_PAD_CNTL_D0_6_0,
	mmMC_IO_PAD_CNTL_D1_6_0,
	ixMC_TSM_DEBUG_GCNT_6_0,
	mmMC_CONFIG_7_1,
	ixMC_TSM_DEBUG_FLAG_6_0,
	ixMC_TSM_DEBUG_BCNT6_6_0,
	mmMC_CONFIG_7_1,
	ixMC_TSM_DEBUG_FLAG_6_0,
	ixMC_TSM_DEBUG_BCNT6_6_0,
	mmMC_CONFIG_7_1,
	ixMC_TSM_DEBUG_MISC_6_0,
	ixMC_TSM_DEBUG_BCNT0_6_0,
	ixMC_TSM_DEBUG_BCNT1_6_0,
	ixMC_TSM_DEBUG_BCNT2_6_0,
	ixMC_TSM_DEBUG_BCNT8_6_0,
	ixMC_TSM_DEBUG_BCNT9_6_0,
	ixMC_TSM_DEBUG_BCNT10_6_0,
	ixMC_IO_DEBUG_UP_14_6_0,
	ixMC_IO_DEBUG_UP_15_6_0,
	mmMC_SEQ_RESERVE_0_S_7_1,
	mmMC_SEQ_MISC5_6_0,
	mmMC_SEQ_MISC4_6_0,
	mmMC_SEQ_MISC6_6_0,
	mmMC_SEQ_MISC7_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DQB1H_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DQB2L_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DBI_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DQB0_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DQB1_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DBI_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D1_6_0,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t mem_adjust_set_terascale2_gddr5_type4_addresses[] = { // 69+1
	mmMC_SEQ_IO_RESERVE_D0_6_0,
	mmMC_SEQ_IO_RESERVE_D1_6_0,
	mmMC_IO_TXCNTL_DPHY0_D0_6_0,
	mmMC_IO_TXCNTL_DPHY0_D1_6_0,
	mmMC_IO_TXCNTL_DPHY1_D0_6_0,
	mmMC_IO_TXCNTL_DPHY1_D1_6_0,
	mmMC_IO_TXCNTL_APHY_D0_6_0,
	mmMC_IO_TXCNTL_APHY_D1_6_0,
	mmMC_IO_RXCNTL_DPHY0_D0_6_0,
	mmMC_IO_RXCNTL_DPHY0_D1_6_0,
	mmMC_IO_RXCNTL_DPHY1_D0_6_0,
	mmMC_IO_RXCNTL_DPHY1_D1_6_0,
	mmMC_IO_DPHY_STR_CNTL_D0_7_1,
	mmMC_IO_DPHY_STR_CNTL_D1_7_1,
	mmMC_IO_APHY_STR_CNTL_D0_6_0,
	mmMC_IO_APHY_STR_CNTL_D1_6_0,
	mmMC_PMG_CFG_6_0,
	mmMC_PMG_AUTO_CFG_6_0,
	mmMC_SEQ_PMG_TIMING_6_0,
	mmMC_SEQ_WR_CTL_D0_6_0,
	mmMC_SEQ_WR_CTL_D1_6_0,
	mmMC_IO_PAD_CNTL_D0_6_0,
	mmMC_IO_PAD_CNTL_D1_6_0,
	ixMC_TSM_DEBUG_GCNT_6_0,
	mmMC_CONFIG_MCD_7_1,
	ixMC_TSM_DEBUG_FLAG_6_0,
	ixMC_TSM_DEBUG_BCNT6_6_0,
	mmMC_CONFIG_MCD_7_1,
	ixMC_TSM_DEBUG_FLAG_6_0,
	ixMC_TSM_DEBUG_BCNT6_6_0,
	mmMC_CONFIG_MCD_7_1,
	ixMC_TSM_DEBUG_FLAG_6_0,
	ixMC_TSM_DEBUG_BCNT6_6_0,
	mmMC_CONFIG_MCD_7_1,
	ixMC_TSM_DEBUG_FLAG_6_0,
	ixMC_TSM_DEBUG_BCNT6_6_0,
	mmMC_CONFIG_MCD_7_1,
	ixMC_TSM_DEBUG_MISC_6_0,
	ixMC_TSM_DEBUG_BCNT0_6_0,
	ixMC_TSM_DEBUG_BCNT1_6_0,
	ixMC_TSM_DEBUG_BCNT2_6_0,
	ixMC_TSM_DEBUG_BCNT8_6_0,
	ixMC_TSM_DEBUG_BCNT9_6_0,
	ixMC_TSM_DEBUG_BCNT10_6_0,
	ixMC_IO_DEBUG_UP_14_6_0,
	ixMC_IO_DEBUG_UP_15_6_0,
	mmMC_SEQ_RESERVE_0_S_7_1,
	mmMC_SEQ_MISC5_6_0,
	mmMC_SEQ_MISC4_6_0,
	mmMC_SEQ_MISC6_6_0,
	mmMC_SEQ_MISC7_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DQB1H_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DQB2L_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DBI_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DQB0_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DQB1_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DBI_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D1_6_0,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t mem_adjust_set_terascale3_gddr5_addresses[] = { // 69+1
	mmMC_SEQ_IO_RESERVE_D0_6_0,
	mmMC_SEQ_IO_RESERVE_D1_6_0,
	mmMC_IO_TXCNTL_DPHY0_D0_6_0,
	mmMC_IO_TXCNTL_DPHY0_D1_6_0,
	mmMC_IO_TXCNTL_DPHY1_D0_6_0,
	mmMC_IO_TXCNTL_DPHY1_D1_6_0,
	mmMC_IO_TXCNTL_APHY_D0_6_0,
	mmMC_IO_TXCNTL_APHY_D1_6_0,
	mmMC_IO_RXCNTL_DPHY0_D0_6_0,
	mmMC_IO_RXCNTL_DPHY0_D1_6_0,
	mmMC_IO_RXCNTL_DPHY1_D0_6_0,
	mmMC_IO_RXCNTL_DPHY1_D1_6_0,
	mmMC_IO_DPHY_STR_CNTL_D0_6_0,
	mmMC_IO_DPHY_STR_CNTL_D1_6_0,
	mmMC_IO_APHY_STR_CNTL_D0_6_0,
	mmMC_IO_APHY_STR_CNTL_D1_6_0,
	mmMC_PMG_CFG_6_0,
	mmMC_PMG_AUTO_CFG_6_0,
	mmMC_SEQ_PMG_TIMING_6_0,
	mmMC_SEQ_WR_CTL_D0_6_0,
	mmMC_SEQ_WR_CTL_D1_6_0,
	mmMC_IO_PAD_CNTL_D0_6_0,
	mmMC_IO_PAD_CNTL_D1_6_0,
	ixMC_IO_DEBUG_UP_0_6_0,
	mmMC_CONFIG_6_0,
	ixMC_IO_DEBUG_UP_1_6_0,
	ixMC_IO_DEBUG_UP_9_6_0,
	mmMC_CONFIG_6_0,
	ixMC_IO_DEBUG_UP_1_6_0,
	ixMC_IO_DEBUG_UP_9_6_0,
	mmMC_CONFIG_6_0,
	ixMC_IO_DEBUG_UP_1_6_0,
	ixMC_IO_DEBUG_UP_9_6_0,
	mmMC_CONFIG_6_0,
	ixMC_IO_DEBUG_UP_1_6_0,
	ixMC_IO_DEBUG_UP_9_6_0,
	mmMC_CONFIG_6_0,
	ixMC_IO_DEBUG_UP_2_6_0,
	ixMC_IO_DEBUG_UP_3_6_0,
	ixMC_IO_DEBUG_UP_4_6_0,
	ixMC_IO_DEBUG_UP_5_6_0,
	ixMC_IO_DEBUG_UP_11_6_0,
	ixMC_IO_DEBUG_UP_12_6_0,
	ixMC_IO_DEBUG_UP_13_6_0,
	ixMC_IO_DEBUG_UP_14_6_0,
	ixMC_IO_DEBUG_UP_15_6_0,
	mmMC_SEQ_RESERVE_0_S_6_0,
	mmMC_SEQ_MISC5_6_0,
	mmMC_SEQ_MISC4_6_0,
	mmMC_SEQ_MISC6_6_0,
	mmMC_SEQ_MISC7_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DQB1H_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DQB2L_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DBI_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DQB0_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DQB1_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DBI_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D1_6_0,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t mem_adjust_set_gcn1_gddr5_type1_addresses[] = { // 97+1
	mmMC_SEQ_IO_RESERVE_D0_6_0,
	mmMC_SEQ_IO_RESERVE_D1_6_0,
	mmMC_IO_TXCNTL_DPHY0_D0_6_0,
	mmMC_IO_TXCNTL_DPHY0_D1_6_0,
	mmMC_IO_TXCNTL_DPHY1_D0_6_0,
	mmMC_IO_TXCNTL_DPHY1_D1_6_0,
	mmMC_IO_TXCNTL_APHY_D0_6_0,
	mmMC_IO_TXCNTL_APHY_D1_6_0,
	mmMC_IO_RXCNTL_DPHY0_D0_6_0,
	mmMC_IO_RXCNTL_DPHY0_D1_6_0,
	mmMC_IO_RXCNTL_DPHY1_D0_6_0,
	mmMC_IO_RXCNTL_DPHY1_D1_6_0,
	mmMC_IO_RXCNTL1_DPHY0_D0_6_0,
	mmMC_IO_RXCNTL1_DPHY0_D1_6_0,
	mmMC_IO_RXCNTL1_DPHY1_D0_6_0,
	mmMC_IO_RXCNTL1_DPHY1_D1_6_0,
	mmMC_IO_DPHY_STR_CNTL_D0_6_0,
	mmMC_IO_DPHY_STR_CNTL_D1_6_0,
	mmMC_IO_APHY_STR_CNTL_D0_6_0,
	mmMC_IO_APHY_STR_CNTL_D1_6_0,
	mmMC_PMG_CFG_6_0,
	mmMC_PMG_AUTO_CFG_6_0,
	mmMC_SEQ_RD_CTL_D0_6_0,
	mmMC_SEQ_RD_CTL_D1_6_0,
	mmMC_IO_PAD_CNTL_D0_6_0,
	mmMC_IO_PAD_CNTL_D1_6_0,
	mmMC_PHY_TIMING_2_6_0,
	ixMC_TSM_DEBUG_GCNT_6_0,
	ixMC_TSM_DEBUG_MISC_6_0,
	ixMC_TSM_DEBUG_BCNT0_6_0,
	ixMC_TSM_DEBUG_BCNT1_6_0,
	ixMC_TSM_DEBUG_BCNT2_6_0,
	ixMC_TSM_DEBUG_BCNT7_6_0,
	ixMC_TSM_DEBUG_BCNT8_6_0,
	ixMC_TSM_DEBUG_BCNT9_6_0,
	ixMC_TSM_DEBUG_BCNT10_6_0,
	ixMC_IO_DEBUG_UP_14_6_0,
	ixMC_IO_DEBUG_UP_15_6_0,
	mmMC_SEQ_RESERVE_0_S_6_0,
	mmMC_SEQ_MISC5_6_0,
	mmMC_SEQ_MISC4_6_0,
	mmMC_SEQ_MISC6_6_0,
	mmMC_SEQ_MISC7_6_0,
	mmMC_SEQ_MISC9_6_0,
	mmMC_ARB_RTT_CNTL0_6_0,
	mmMC_ARB_RTT_CNTL1_6_0,
	mmMC_ARB_RTT_CNTL2_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_CMD_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_CMD_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_DQB0_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DQB3_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DQB0_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DQB3_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_WCK_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_WCK_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_DBI_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_DBI_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_EDC_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_EDC_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_WCK_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_WCK_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_EDC_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_EDC_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_ACMD_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_ACMD_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_DBI_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DBI_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DBI_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_DBI_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_EDC_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_EDC_RX_EQ_D1_6_0,
	mmMC_IO_CDRCNTL_D0_6_0,
	mmMC_IO_CDRCNTL_D1_6_0,
	mmMC_IO_CDRCNTL1_D0_6_0,
	mmMC_IO_CDRCNTL1_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_WCK_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_VREF_CAL_D1_6_0,
	ixMC_IO_DEBUG_WCK_RX_VREF_CAL_D1_6_0,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t mem_adjust_set_gcn1_gddr5_type2_addresses[] = { // 123+1
	mmMC_SEQ_IO_RESERVE_D0_6_0,
	mmMC_SEQ_IO_RESERVE_D1_6_0,
	mmMC_IO_TXCNTL_DPHY0_D0_6_0,
	mmMC_IO_TXCNTL_DPHY0_D1_6_0,
	mmMC_IO_TXCNTL_DPHY1_D0_6_0,
	mmMC_IO_TXCNTL_DPHY1_D1_6_0,
	mmMC_IO_TXCNTL_APHY_D0_6_0,
	mmMC_IO_TXCNTL_APHY_D1_6_0,
	mmMC_IO_RXCNTL_DPHY0_D0_6_0,
	mmMC_IO_RXCNTL_DPHY0_D1_6_0,
	mmMC_IO_RXCNTL_DPHY1_D0_6_0,
	mmMC_IO_RXCNTL_DPHY1_D1_6_0,
	mmMC_IO_RXCNTL1_DPHY0_D0_7_1,
	mmMC_IO_RXCNTL1_DPHY0_D1_7_1,
	mmMC_IO_RXCNTL1_DPHY1_D0_7_1,
	mmMC_IO_RXCNTL1_DPHY1_D1_7_1,
	mmMC_IO_DPHY_STR_CNTL_D0_7_1,
	mmMC_IO_DPHY_STR_CNTL_D1_7_1,
	mmMC_IO_APHY_STR_CNTL_D0_6_0,
	mmMC_IO_APHY_STR_CNTL_D1_6_0,
	mmMC_PMG_CFG_6_0,
	mmMC_PMG_AUTO_CFG_6_0,
	mmMC_SEQ_RD_CTL_D0_6_0,
	mmMC_SEQ_RD_CTL_D1_6_0,
	mmMC_IO_PAD_CNTL_D0_6_0,
	mmMC_IO_PAD_CNTL_D1_6_0,
	mmMC_PHY_TIMING_2_7_1,
	ixMC_TSM_DEBUG_GCNT_6_0,
	ixMC_TSM_DEBUG_MISC_6_0,
	ixMC_TSM_DEBUG_BCNT0_6_0,
	ixMC_TSM_DEBUG_BCNT1_6_0,
	ixMC_TSM_DEBUG_BCNT2_6_0,
	ixMC_TSM_DEBUG_BCNT7_6_0,
	ixMC_TSM_DEBUG_BCNT8_6_0,
	ixMC_TSM_DEBUG_BCNT9_6_0,
	ixMC_TSM_DEBUG_BCNT10_6_0,
	ixMC_IO_DEBUG_UP_14_6_0,
	ixMC_IO_DEBUG_UP_15_6_0,
	mmMC_SEQ_RESERVE_0_S_7_1,
	mmMC_SEQ_MISC5_6_0,
	mmMC_SEQ_MISC4_6_0,
	mmMC_SEQ_MISC6_6_0,
	mmMC_SEQ_MISC7_6_0,
	mmMC_SEQ_MISC9_6_0,
	mmMC_ARB_RTT_CNTL0_6_0,
	mmMC_ARB_RTT_CNTL1_6_0,
	mmMC_ARB_RTT_CNTL2_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_CMD_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_CMD_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_DQB0_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DQB3_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DQB0_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DQB3_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_WCK_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_WCK_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_WCDR_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_WCDR_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DBI_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_DBI_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_EDC_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_EDC_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_EDC_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_EDC_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_CK_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_CK_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_CK_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_CK_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_DBI_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_DBI_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_EDC_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_EDC_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_WCK_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_WCK_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_EDC_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_EDC_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_ACMD_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_ACMD_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_DBI_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DBI_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DBI_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_DBI_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_EDC_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_EDC_RX_EQ_D1_6_0,
	mmMC_IO_CDRCNTL_D0_6_0,
	mmMC_IO_CDRCNTL_D1_6_0,
	mmMC_IO_CDRCNTL1_D0_6_0,
	mmMC_IO_CDRCNTL1_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_WCK_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_VREF_CAL_D1_6_0,
	ixMC_IO_DEBUG_WCK_RX_VREF_CAL_D1_6_0,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t mem_adjust_set_gcn1_gddr5_type3_addresses[] = { // 133+1
	mmMC_SEQ_IO_RESERVE_D0_6_0,
	mmMC_SEQ_IO_RESERVE_D1_6_0,
	mmMC_IO_TXCNTL_DPHY0_D0_6_0,
	mmMC_IO_TXCNTL_DPHY0_D1_6_0,
	mmMC_IO_TXCNTL_DPHY1_D0_6_0,
	mmMC_IO_TXCNTL_DPHY1_D1_6_0,
	mmMC_IO_TXCNTL_APHY_D0_6_0,
	mmMC_IO_TXCNTL_APHY_D1_6_0,
	mmMC_IO_RXCNTL_DPHY0_D0_6_0,
	mmMC_IO_RXCNTL_DPHY0_D1_6_0,
	mmMC_IO_RXCNTL_DPHY1_D0_6_0,
	mmMC_IO_RXCNTL_DPHY1_D1_6_0,
	mmMC_IO_RXCNTL1_DPHY0_D0_7_1,
	mmMC_IO_RXCNTL1_DPHY0_D1_7_1,
	mmMC_IO_RXCNTL1_DPHY1_D0_7_1,
	mmMC_IO_RXCNTL1_DPHY1_D1_7_1,
	mmMC_IO_DPHY_STR_CNTL_D0_7_1,
	mmMC_IO_DPHY_STR_CNTL_D1_7_1,
	mmMC_IO_APHY_STR_CNTL_D0_6_0,
	mmMC_IO_APHY_STR_CNTL_D1_6_0,
	mmMC_PMG_CFG_6_0,
	mmMC_PMG_AUTO_CFG_6_0,
	mmMC_SEQ_RD_CTL_D0_6_0,
	mmMC_SEQ_RD_CTL_D1_6_0,
	mmMC_IO_PAD_CNTL_D0_6_0,
	mmMC_IO_PAD_CNTL_D1_6_0,
	mmMC_PHY_TIMING_2_7_1,
	ixMC_TSM_DEBUG_GCNT_6_0,
	ixMC_TSM_DEBUG_MISC_6_0,
	ixMC_TSM_DEBUG_BCNT0_6_0,
	ixMC_TSM_DEBUG_BCNT1_6_0,
	ixMC_TSM_DEBUG_BCNT2_6_0,
	ixMC_TSM_DEBUG_BCNT7_6_0,
	ixMC_TSM_DEBUG_BCNT8_6_0,
	ixMC_TSM_DEBUG_BCNT9_6_0,
	ixMC_TSM_DEBUG_BCNT10_6_0,
	ixMC_IO_DEBUG_UP_14_6_0,
	ixMC_IO_DEBUG_UP_15_6_0,
	mmMC_SEQ_RESERVE_0_S_7_1,
	mmMC_SEQ_MISC5_6_0,
	mmMC_SEQ_MISC4_6_0,
	mmMC_SEQ_MISC6_6_0,
	mmMC_SEQ_MISC7_6_0,
	mmMC_SEQ_MISC9_6_0,
	mmMC_ARB_RTT_CNTL0_6_0,
	mmMC_ARB_RTT_CNTL1_6_0,
	mmMC_ARB_RTT_CNTL2_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_CMD_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_CMD_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_DQB0_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DQB3_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DQB0_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DQB3_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_WCK_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_WCK_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_WCDR_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_WCDR_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_WCDR_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_WCDR_RX_VREF_CAL_D1_6_0,
	ixMC_IO_DEBUG_WCDR_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_WCDR_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_WCDR_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_WCDR_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DBI_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_DBI_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_EDC_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_EDC_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_EDC_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_EDC_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_WCDR_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_WCDR_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_WCDR_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_WCDR_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_CK_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_CK_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_CK_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_CK_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_DBI_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_DBI_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_EDC_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_EDC_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_WCK_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_WCK_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_EDC_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_EDC_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_ACMD_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_ACMD_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_DBI_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DBI_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DBI_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_DBI_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_EDC_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_EDC_RX_EQ_D1_6_0,
	mmMC_IO_CDRCNTL_D0_6_0,
	mmMC_IO_CDRCNTL_D1_6_0,
	mmMC_IO_CDRCNTL1_D0_6_0,
	mmMC_IO_CDRCNTL1_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_WCK_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_VREF_CAL_D1_6_0,
	ixMC_IO_DEBUG_WCK_RX_VREF_CAL_D1_6_0,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t mem_adjust_set_gcn1_gddr5_type4_addresses[] = { // 63+1
	mmMC_SEQ_IO_RESERVE_D0_6_0,
	mmMC_SEQ_IO_RESERVE_D1_6_0,
	mmMC_IO_TXCNTL_DPHY0_D0_6_0,
	mmMC_IO_TXCNTL_DPHY0_D1_6_0,
	mmMC_IO_TXCNTL_DPHY1_D0_6_0,
	mmMC_IO_TXCNTL_DPHY1_D1_6_0,
	mmMC_IO_TXCNTL_APHY_D0_6_0,
	mmMC_IO_TXCNTL_APHY_D1_6_0,
	mmMC_IO_RXCNTL_DPHY0_D0_6_0,
	mmMC_IO_RXCNTL_DPHY0_D1_6_0,
	mmMC_IO_RXCNTL_DPHY1_D0_6_0,
	mmMC_IO_RXCNTL_DPHY1_D1_6_0,
	mmMC_IO_RXCNTL1_DPHY0_D0_7_1,
	mmMC_IO_RXCNTL1_DPHY0_D1_7_1,
	mmMC_IO_RXCNTL1_DPHY1_D0_7_1,
	mmMC_IO_RXCNTL1_DPHY1_D1_7_1,
	mmMC_IO_DPHY_STR_CNTL_D0_7_1,
	mmMC_IO_DPHY_STR_CNTL_D1_7_1,
	mmMC_IO_APHY_STR_CNTL_D0_6_0,
	mmMC_IO_APHY_STR_CNTL_D1_6_0,
	mmMC_PMG_CFG_6_0,
	mmMC_PMG_AUTO_CFG_6_0,
	mmMC_SEQ_RD_CTL_D0_6_0,
	mmMC_SEQ_RD_CTL_D1_6_0,
	mmMC_IO_PAD_CNTL_D0_6_0,
	mmMC_IO_PAD_CNTL_D1_6_0,
	mmMC_PHY_TIMING_2_7_1,
	ixMC_IO_DEBUG_DQB0L_RXPHASE_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_RXPHASE_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_RXPHASE_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_RXPHASE_D1_6_0,
	ixMC_IO_DEBUG_WCK_RXPHASE_D0_6_0,
	ixMC_IO_DEBUG_WCK_RXPHASE_D1_6_0,
	ixMC_IO_DEBUG_EDC_RXPHASE_D0_6_0,
	ixMC_IO_DEBUG_EDC_RXPHASE_D1_6_0,
	ixMC_IO_DEBUG_DBI_RXPHASE_D0_6_0,
	ixMC_IO_DEBUG_DBI_RXPHASE_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_DBI_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_DBI_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_WCK_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_WCK_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_EDC_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_EDC_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ADDRL_CLKSEL_D0_6_0,
	ixMC_IO_DEBUG_CMD_CLKSEL_D0_6_0,
	ixMC_IO_DEBUG_ADDRL_CLKSEL_D1_6_0,
	ixMC_IO_DEBUG_CMD_CLKSEL_D1_6_0,
	mmMC_SEQ_MISC5_6_0,
	mmMC_SEQ_FIFO_CTL_7_1,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t mem_adjust_set_gcn2_gddr5_addresses[] = { // 126+1
	mmMC_SEQ_IO_RESERVE_D0_6_0,
	mmMC_SEQ_IO_RESERVE_D1_6_0,
	mmMC_IO_TXCNTL_DPHY0_D0_6_0,
	mmMC_IO_TXCNTL_DPHY0_D1_6_0,
	mmMC_IO_TXCNTL_DPHY1_D0_6_0,
	mmMC_IO_TXCNTL_DPHY1_D1_6_0,
	mmMC_IO_TXCNTL_APHY_D0_6_0,
	mmMC_IO_TXCNTL_APHY_D1_6_0,
	mmMC_IO_RXCNTL_DPHY0_D0_6_0,
	mmMC_IO_RXCNTL_DPHY0_D1_6_0,
	mmMC_IO_RXCNTL_DPHY1_D0_6_0,
	mmMC_IO_RXCNTL_DPHY1_D1_6_0,
	mmMC_IO_RXCNTL1_DPHY0_D0_7_1,
	mmMC_IO_RXCNTL1_DPHY0_D1_7_1,
	mmMC_IO_RXCNTL1_DPHY1_D0_7_1,
	mmMC_IO_RXCNTL1_DPHY1_D1_7_1,
	mmMC_IO_DPHY_STR_CNTL_D0_7_1,
	mmMC_IO_DPHY_STR_CNTL_D1_7_1,
	mmMC_IO_APHY_STR_CNTL_D0_6_0,
	mmMC_IO_APHY_STR_CNTL_D1_6_0,
	mmMC_PMG_CFG_6_0,
	mmMC_PMG_AUTO_CFG_6_0,
	mmMC_SEQ_RD_CTL_D0_6_0,
	mmMC_SEQ_RD_CTL_D1_6_0,
	mmMC_IO_PAD_CNTL_D0_6_0,
	mmMC_IO_PAD_CNTL_D1_6_0,
	mmMC_PHY_TIMING_2_7_1,
	ixMC_TSM_DEBUG_GCNT_6_0,
	ixMC_TSM_DEBUG_MISC_6_0,
	ixMC_TSM_DEBUG_BCNT0_6_0,
	ixMC_TSM_DEBUG_BCNT1_6_0,
	ixMC_TSM_DEBUG_BCNT2_6_0,
	ixMC_TSM_DEBUG_BCNT7_6_0,
	ixMC_TSM_DEBUG_BCNT8_6_0,
	ixMC_TSM_DEBUG_BCNT9_6_0,
	ixMC_TSM_DEBUG_BCNT10_6_0,
	ixMC_IO_DEBUG_UP_14_6_0,
	ixMC_IO_DEBUG_UP_15_6_0,
	mmMC_SEQ_RESERVE_0_S_7_1,
	mmMC_SEQ_MISC5_6_0,
	mmMC_SEQ_MISC4_6_0,
	mmMC_SEQ_MISC6_6_0,
	mmMC_SEQ_MISC7_6_0,
	mmMC_SEQ_MISC9_6_0,
	mmMC_ARB_RTT_CNTL0_6_0,
	mmMC_ARB_RTT_CNTL1_6_0,
	mmMC_ARB_RTT_CNTL2_6_0,
	mmMC_SEQ_G5PDX_CTRL_7_1,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_CMD_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_CMD_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_DQB0_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DQB3_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DQB0_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DQB3_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_WCK_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_WCK_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_WCDR_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_WCDR_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_WCDR_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_WCDR_RX_VREF_CAL_D1_6_0,
	ixMC_IO_DEBUG_WCDR_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_WCDR_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_WCDR_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_WCDR_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DBI_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_DBI_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_EDC_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_EDC_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_EDC_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_EDC_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_WCDR_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_WCDR_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_WCDR_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_WCDR_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_DBI_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_DBI_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_EDC_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_EDC_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_WCK_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_WCK_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_EDC_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_EDC_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_ACMD_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_ACMD_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_DBI_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DBI_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DBI_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_DBI_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_EDC_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_EDC_RX_EQ_D1_6_0,
	mmMC_IO_CDRCNTL_D0_6_0,
	mmMC_IO_CDRCNTL_D1_6_0,
	mmMC_IO_CDRCNTL1_D0_6_0,
	mmMC_IO_CDRCNTL1_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_WCK_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_VREF_CAL_D1_6_0,
	ixMC_IO_DEBUG_WCK_RX_VREF_CAL_D1_6_0,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t mem_adjust_set_gcn3_gddr5_addresses[] = { // 45+1
	mmMC_IO_RXCNTL_DPHY0_D0_6_0,
	mmMC_IO_RXCNTL_DPHY0_D1_6_0,
	mmMC_IO_RXCNTL_DPHY1_D0_6_0,
	mmMC_IO_RXCNTL_DPHY1_D1_6_0,
	mmMC_IO_RXCNTL1_DPHY0_D0_7_1,
	mmMC_IO_RXCNTL1_DPHY0_D1_7_1,
	mmMC_IO_RXCNTL1_DPHY1_D0_7_1,
	mmMC_IO_RXCNTL1_DPHY1_D1_7_1,
	mmMC_IO_APHY_STR_CNTL_D0_6_0,
	mmMC_IO_APHY_STR_CNTL_D1_6_0,
	ixMC_TSM_DEBUG_BCNT2_6_0,
	mmMC_SEQ_RESERVE_1_S_6_0,
	mmMC_SEQ_MISC5_6_0,
	mmMC_SEQ_MISC4_6_0,
	mmMC_SEQ_MISC6_6_0,
	mmMC_SEQ_MISC7_6_0,
	mmMC_SEQ_MISC9_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRL_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ADDRH_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_ACMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_CK_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_CLKSEL_D0_6_0,
	ixMC_IO_DEBUG_EDC_CLKSEL_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_CLKSEL_D1_6_0,
	ixMC_IO_DEBUG_EDC_CLKSEL_D1_6_0,
	ixMC_IO_DEBUG_WCK_CLKSEL_D0_6_0,
	ixMC_IO_DEBUG_WCK_CLKSEL_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_DBI_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_DBI_TXPHASE_D1_6_0,
	ixMC_IO_DEBUG_WCK_TXPHASE_D0_6_0,
	ixMC_IO_DEBUG_WCK_TXPHASE_D1_6_0,
	mmMC_SEQ_TXFRAMING_BYTE0_D0_6_0,
	mmMC_SEQ_TXFRAMING_DBI_D0_6_0,
	mmMC_SEQ_TXFRAMING_BYTE0_D1_6_0,
	mmMC_SEQ_TXFRAMING_DBI_D1_6_0,
	ixMC_IO_DEBUG_EDC_RXPHASE_D0_6_0,
	ixMC_IO_DEBUG_EDC_RXPHASE_D1_6_0,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t mem_adjust_set_gcn3_hbm1_addresses[] = { // 1+1
	mmMC_SEQ_RXFRAMING_DBI_D1_6_0,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t mem_adjust_set_gcn4_gddr5_type1_addresses[] = { // 6+1
	mmMC_SEQ_MISC4_6_0,
	mmMC_SEQ_MISC5_6_0,
	mmMC_IO_PAD_CNTL_D1_6_0,
	ixMC_TSM_DEBUG_FLAG_6_0,
	mmMC_IO_APHY_STR_CNTL_D0_6_0,
	mmMC_IO_APHY_STR_CNTL_D1_6_0,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t mem_adjust_set_gcn4_gddr5_type2_addresses[] = { // 12+1
	mmMC_SEQ_MISC0_6_0,
	mmMC_SEQ_MISC4_6_0,
	mmMC_SEQ_MISC5_6_0,
	mmMC_SEQ_MISC6_6_0,
	mmMC_SEQ_RESERVE_M_6_0,
	ixMC_TSM_DEBUG_FLAG_6_0,
	ixMC_TSM_DEBUG_BCNT0_6_0,
	ixMC_IO_DEBUG_UP_15_6_0,
	mmMC_IO_DPHY_STR_CNTL_D0_7_1,
	mmMC_IO_DPHY_STR_CNTL_D1_7_1,
	mmMC_IO_APHY_STR_CNTL_D0_6_0,
	mmMC_IO_APHY_STR_CNTL_D1_6_0,
	END_OF_REG_INDEX_BLOCK
};

/******************************************************************************/
// mc_tile_adjust table
// uncertain the accuracy of all of these tables.
/******************************************************************************/

static const uint16_t mc_tile_adjust_set_gcn3_gddr5_addresses[] = { // 2+1
	ixMC_TSM_DEBUG_FLAG_6_0,
	ixMC_TSM_DEBUG_BCNT6_6_0,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t mc_tile_adjust_set_gcn4_gddr5_addresses[] = { // 1+1
	ixMC_IO_DEBUG_UP_14_6_0,
	END_OF_REG_INDEX_BLOCK
};

/******************************************************************************/
// mc_phy_init table
// uncertain the accuracy of all of these tables.
/******************************************************************************/

static const uint16_t mc_phy_init_set_gcn3_hbm1_addresses[] = { // 13+1
	mmMC_IO_PAD_CNTL_6_0,
	mmMC_IO_PAD_CNTL_D0_6_0,
	mmMC_SEQ_PERF_SEQ_CNT_A_I0_6_0,
	mmMC_FUS_DRAM0_CS1_BASE_7_0,
	mmMC_FUS_DRAM1_CS1_BASE_7_0,
	ixMC_TSM_DEBUG_GCNT_6_0,
	ixMC_TSM_DEBUG_FLAG_6_0,
	ixMC_TSM_DEBUG_MISC_6_0,
	ixMC_TSM_DEBUG_BCNT0_6_0,
	ixMC_TSM_DEBUG_BCNT1_6_0,
	ixMC_TSM_DEBUG_BCNT2_6_0,
	ixMC_TSM_DEBUG_BCNT3_6_0,
	ixMC_TSM_DEBUG_BCNT4_6_0,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t mc_phy_init_set_gcn3_gddr5_addresses[] = { // 164+1
	mmMPLL_SEQ_UCODE_1_6_0,
	mmMPLL_SEQ_UCODE_2_6_0,
	mmMC_SEQ_DRAM_7_1,
	mmMC_SEQ_DRAM_2_6_0,
	mmMC_SEQ_FIFO_CTL_7_1,
	mmMC_IO_PAD_CNTL_6_0,
	mmMC_SEQ_WR_CTL_D0_6_0,
	mmMC_SEQ_WR_CTL_D1_6_0,
	mmMC_SEQ_TRAIN_WAKEUP_MASK_7_1,
	mmMC_SEQ_PMG_DVS_CTL_7_1,
	mmMC_SEQ_PMG_DVS_CTL_LP_7_1,
	mmMC_SEQ_PMG_PG_HWCNTL_6_0,
	mmMC_SEQ_TRAIN_WAKEUP_CNTL_6_0,
	mmMC_SEQ_TRAIN_EDC_THRESHOLD_6_0,
	mmMC_SEQ_TRAIN_WAKEUP_EDGE_7_1,
	mmMC_SEQ_TRAIN_WAKEUP_CLEAR_7_1,
	mmMC_SEQ_TRAIN_TIMING_6_0,
	mmMC_SEQ_PERF_CNTL_6_0,
	mmMC_SEQ_CNTL_2_7_1,
	mmMC_SEQ_CNTL_3_7_1,
	mmMC_SEQ_PERF_SEQ_CTL_6_0,
	mmMC_IMP_CNTL_6_0,
	mmMC_SEQ_DLL_STBY_7_1,
	mmMC_SEQ_G5PDX_CMD0_7_1,
	mmMC_SEQ_G5PDX_CMD1_7_1,
	mmMC_SEQ_G5PDX_CTRL_7_1,
	ixMC_IO_DEBUG_UP_159_6_0,
	ixMC_IO_DEBUG_WCDR_RX_DYN_PM_D1_6_0,
	mmMC_SEQ_TXFRAMING_BYTE0_D0_6_0,
	mmMC_SEQ_RXFRAMING_EDC_D1_6_0,
	ixMC_IO_DEBUG_CK_CLKSEL_D0_6_0,
	ixMC_IO_DEBUG_CMD_CLKSEL_D0_6_0,
	ixMC_IO_DEBUG_CK_CLKSEL_D1_6_0,
	ixMC_IO_DEBUG_CMD_CLKSEL_D1_6_0,
	ixMC_IO_DEBUG_DQ0_RX_EQ_PM_D0_6_0,
	ixMC_IO_DEBUG_DQ0_RX_EQ_PM_D1_6_0,
	ixMC_IO_DEBUG_DQ1_RX_EQ_PM_D0_6_0,
	ixMC_IO_DEBUG_DQ1_RX_EQ_PM_D1_6_0,
	ixMC_IO_DEBUG_DQ0_RX_DYN_PM_D0_6_0,
	ixMC_IO_DEBUG_DQ0_RX_DYN_PM_D1_6_0,
	ixMC_IO_DEBUG_DQ1_RX_DYN_PM_D0_6_0,
	ixMC_IO_DEBUG_DQ1_RX_DYN_PM_D1_6_0,
	ixMC_IO_DEBUG_EDC_RX_EQ_PM_D0_6_0,
	ixMC_IO_DEBUG_EDC_RX_EQ_PM_D1_6_0,
	mmMC_PHY_TIMING_D0_6_0,
	mmMC_PHY_TIMING_D1_6_0,
	mmMC_SEQ_IO_RESERVE_D0_6_0,
	mmMC_SEQ_IO_RESERVE_D1_6_0,
	mmMC_IO_TXCNTL_DPHY0_D0_6_0,
	mmMC_IO_TXCNTL_DPHY0_D1_6_0,
	mmMC_IO_TXCNTL_DPHY1_D0_6_0,
	mmMC_IO_TXCNTL_DPHY1_D1_6_0,
	mmMC_IO_TXCNTL_APHY_D0_6_0,
	mmMC_IO_TXCNTL_APHY_D1_6_0,
	mmMC_IO_DPHY_STR_CNTL_D0_7_1,
	mmMC_IO_DPHY_STR_CNTL_D1_7_1,
	mmMC_PMG_CFG_6_0,
	mmMC_PMG_AUTO_CFG_6_0,
	mmMC_SEQ_RD_CTL_D0_6_0,
	mmMC_SEQ_RD_CTL_D1_6_0,
	mmMC_IO_PAD_CNTL_D0_6_0,
	mmMC_IO_PAD_CNTL_D1_6_0,
	ixMC_TSM_DEBUG_GCNT_6_0,
	ixMC_TSM_DEBUG_MISC_6_0,
	ixMC_TSM_DEBUG_BCNT0_6_0,
	ixMC_TSM_DEBUG_BCNT1_6_0,
	ixMC_TSM_DEBUG_BCNT7_6_0,
	ixMC_TSM_DEBUG_BCNT8_6_0,
	ixMC_TSM_DEBUG_BCNT9_6_0,
	ixMC_TSM_DEBUG_BCNT10_6_0,
	ixMC_IO_DEBUG_UP_14_6_0,
	ixMC_IO_DEBUG_UP_15_6_0,
	mmMC_ARB_RTT_CNTL0_6_0,
	mmMC_ARB_RTT_CNTL1_6_0,
	mmMC_ARB_RTT_CNTL2_6_0,
	mmMC_SEQ_G5PDX_CTRL_7_1,
	ixMC_IO_DEBUG_DQB0L_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_CMD_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_CMD_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_DQB0_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DQB3_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DQB0_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DQB3_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_WCK_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_WCK_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_WCDR_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_WCDR_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_WCDR_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_WCDR_RX_VREF_CAL_D1_6_0,
	ixMC_IO_DEBUG_WCDR_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_WCDR_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_WCDR_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_WCDR_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DBI_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_DBI_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_EDC_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_EDC_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_EDC_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_EDC_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_WCDR_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_WCDR_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_WCDR_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_WCDR_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_DQB3H_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_DQB3H_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_ACMD_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_ACMD_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_ACMD_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_ACMD_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_ADDRH_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_ADDRH_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_ADDRH_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_ADDRH_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_ADDRL_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_ADDRL_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_ADDRL_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_ADDRL_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_CK_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_CK_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_CK_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_CK_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PD_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PD_D1_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PU_D0_6_0,
	ixMC_IO_DEBUG_CMD_TXBST_PU_D1_6_0,
	ixMC_IO_DEBUG_DBI_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_DBI_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_EDC_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_EDC_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_WCK_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_WCK_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_EDC_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_EDC_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_ACMD_OFSCAL_D0_6_0,
	ixMC_IO_DEBUG_ACMD_OFSCAL_D1_6_0,
	ixMC_IO_DEBUG_DBI_CDR_PHSIZE_D0_6_0,
	ixMC_IO_DEBUG_DBI_CDR_PHSIZE_D1_6_0,
	ixMC_IO_DEBUG_DBI_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_DBI_RX_EQ_D1_6_0,
	ixMC_IO_DEBUG_EDC_RX_EQ_D0_6_0,
	ixMC_IO_DEBUG_EDC_RX_EQ_D1_6_0,
	mmMC_IO_CDRCNTL_D0_6_0,
	mmMC_IO_CDRCNTL_D1_6_0,
	mmMC_IO_CDRCNTL1_D0_6_0,
	mmMC_IO_CDRCNTL1_D1_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_WCK_RX_VREF_CAL_D0_6_0,
	ixMC_IO_DEBUG_DQB0L_RX_VREF_CAL_D1_6_0,
	ixMC_IO_DEBUG_WCK_RX_VREF_CAL_D1_6_0,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t mc_phy_init_set_gcn4_gddr5_type1_addresses[] = { // 24+1
	mmMC_SEQ_MISC0_6_0,
	mmMC_SEQ_MISC4_6_0,
	mmMC_SEQ_MISC5_6_0,
	mmMC_SEQ_MISC6_6_0,
	mmMC_SEQ_MISC7_6_0,
	mmMC_SEQ_RESERVE_M_6_0,
	mmMC_IO_PAD_CNTL_D0_6_0,
	mmMC_IO_PAD_CNTL_D1_6_0,
	ixMC_TSM_DEBUG_GCNT_6_0,
	ixMC_TSM_DEBUG_FLAG_6_0,
	ixMC_TSM_DEBUG_MISC_6_0,
	ixMC_TSM_DEBUG_BCNT0_6_0,
	ixMC_TSM_DEBUG_BCNT1_6_0,
	ixMC_TSM_DEBUG_BCNT2_6_0,
	ixMC_TSM_DEBUG_BCNT6_6_0,
	ixMC_TSM_DEBUG_BCNT7_6_0,
	ixMC_TSM_DEBUG_BCNT8_6_0,
	ixMC_TSM_DEBUG_BCNT9_6_0,
	ixMC_TSM_DEBUG_BCNT10_6_0,
	ixMC_IO_DEBUG_UP_15_6_0,
	mmMC_IO_DPHY_STR_CNTL_D0_7_1,
	mmMC_IO_DPHY_STR_CNTL_D1_7_1,
	mmMC_IO_APHY_STR_CNTL_D0_6_0,
	mmMC_IO_APHY_STR_CNTL_D1_6_0,
	END_OF_REG_INDEX_BLOCK
};

static const uint16_t mc_phy_init_set_gcn4_gddr5_type2_addresses[] = { // 18+1
	mmMC_SEQ_MISC0_6_0,
	mmMC_SEQ_MISC6_6_0,
	mmMC_SEQ_MISC7_6_0,
	mmMC_SEQ_RESERVE_M_6_0,
	mmMC_IO_PAD_CNTL_D0_6_0,
	ixMC_TSM_DEBUG_GCNT_6_0,
	ixMC_TSM_DEBUG_MISC_6_0,
	ixMC_TSM_DEBUG_BCNT0_6_0,
	ixMC_TSM_DEBUG_BCNT1_6_0,
	ixMC_TSM_DEBUG_BCNT2_6_0,
	ixMC_TSM_DEBUG_BCNT6_6_0,
	ixMC_TSM_DEBUG_BCNT7_6_0,
	ixMC_TSM_DEBUG_BCNT8_6_0,
	ixMC_TSM_DEBUG_BCNT9_6_0,
	ixMC_TSM_DEBUG_BCNT10_6_0,
	ixMC_IO_DEBUG_UP_15_6_0,
	mmMC_IO_DPHY_STR_CNTL_D0_7_1,
	mmMC_IO_DPHY_STR_CNTL_D1_7_1,
	END_OF_REG_INDEX_BLOCK
};

#endif