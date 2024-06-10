/*
Register data block playback of common asic register tables
See also asic_reg_indicies.json5
*/

#ifndef _ASIC_REG_DATA_TABLES_H_
#define _ASIC_REG_DATA_TABLES_H_

#pragma pack(push, 1) // bios data must use byte alignment

/******************************************************************************/
/******************************************************************************/
// GMC
// see gmc.h
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
// mem_clk_patch
/******************************************************************************/

struct timings_set_islands_ddr3 { // 52 bytes
	// Northern, Southern, Sea, Volcanic Islands
	union atom_mc_register_setting_id  block_id;
	union mc_seq_wr_ctl_d0_6_0    mc_seq_wr_ctl_d0;
	union mc_seq_wr_ctl_2_6_0     mc_seq_wr_ctl;
	union mc_seq_ras_timing_6_0   mc_seq_ras_timing;
	union mc_seq_cas_timing_6_0   mc_seq_cas_timing;
	union mc_seq_misc_timing_6_0  mc_seq_misc_timing;
	union mc_seq_misc_timing2_6_0 mc_seq_misc_timing2;
	union mc_seq_pmg_timing_6_0   mc_seq_pmg_timing;
	struct mc_seq_misc1_ddr3 mc_seq_misc1;
	struct mc_seq_misc3_ddr3 mc_seq_misc3;
	union mc_seq_misc8_6_0   mc_seq_misc8;
	union mc_arb_dram_timing_6_0  mc_arb_dram_timing;
	union mc_arb_dram_timing2_6_0 mc_arb_dram_timing2;
};

struct timings_set_islands_gddr5 { // 52 bytes
	// Northern, Southern, Sea, Volcanic Islands
	union atom_mc_register_setting_id  block_id;
	union mc_seq_wr_ctl_d0_6_0     mc_seq_wr_ctl_d0;
	union mc_seq_wr_ctl_2_6_0      mc_seq_wr_ctl;
	union mc_seq_ras_timing_6_0    mc_seq_ras_timing;
	union mc_seq_cas_timing_6_0    mc_seq_cas_timing;
	union mc_seq_misc_timing_6_0   mc_seq_misc_timing;
	union mc_seq_misc_timing2_6_0  mc_seq_misc_timing2;
	union mc_seq_pmg_timing_6_0    mc_seq_pmg_timing;
	struct mc_seq_misc1_gddr5      mc_seq_misc1;
	struct mc_seq_misc3_gddr5      mc_seq_misc3;
	struct mc_seq_misc8_gddr5      mc_seq_misc8;
	union mc_arb_dram_timing_6_0   mc_arb_dram_timing;
	union mc_arb_dram_timing2_6_0  mc_arb_dram_timing2;
};

struct timings_set_fiji { // 40 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_cas_timing_6_0_o    mc_seq_cas_timing;
	union mc_seq_misc_timing2_6_0_o  mc_seq_misc_timing2;
	union mc_seq_rd_ctl_d0_6_0       mc_seq_rd_ctl_d0;
	union mc_seq_wr_ctl_d0_6_0       mc_seq_wr_ctl_d0;
	union mc_seq_cmd_6_0_o           mc_seq_cmd;
	union mc_seq_rxframing_edc_d1_6_0  mc_seq_rxframing_edc_d1;
	union mc_arb_dram_timing_6_0     mc_arb_dram_timing;
	union mc_arb_dram_timing2_6_0    mc_arb_dram_timing2;
	union mc_arb_burst_time_8_1      mc_arb_burst_time;
};

struct timings_set_polaris { // 52 bytes.
	union atom_mc_register_setting_id  block_id;
	union mc_seq_wr_ctl_d0_6_0     mc_seq_wr_ctl_d0;
	union mc_seq_wr_ctl_2_6_0      mc_seq_wr_ctl_2;
	union mc_seq_pmg_timing_6_0    mc_seq_pmg_timing;
	union mc_seq_ras_timing_6_0    mc_seq_ras_timing;
	union mc_seq_cas_timing_6_0    mc_seq_cas_timing;
	union mc_seq_misc_timing_6_0_o mc_seq_misc_timing;
	union mc_seq_misc_timing2_6_0  mc_seq_misc_timing2;
	struct mc_seq_misc1_gddr5      mc_seq_misc1;
	struct mc_seq_misc3_gddr5      mc_seq_misc3;
	struct mc_seq_misc8_gddr5      mc_seq_misc8;
	union mc_arb_dram_timing_6_0   mc_arb_dram_timing;
	union mc_arb_dram_timing2_6_0  mc_arb_dram_timing2;
};

struct timings_set_vega10 { // 92 bytes. Uncertain.
	union atom_mc_register_setting_id  block_id;
	union DRAMTiming1 DRAMTiming1;
	union DRAMTiming2 DRAMTiming2;
	union DRAMTiming3 DRAMTiming3;
	union DRAMTiming4 DRAMTiming4;
	union DRAMTiming5 DRAMTiming5;
	union DRAMTiming6 DRAMTiming6;
	union DRAMTiming7 DRAMTiming7;
	union DRAMTiming8 DRAMTiming8;
	union DRAMTiming9_HBM2 DRAMTiming9;
	union DRAMTiming10 DRAMTiming10;

	union DRAMTiming12 DRAMTiming12;
	union DRAMTiming13 DRAMTiming13;
	union DRAMTiming14_HBM2 DRAMTiming14;
	uint32_t unknown15; // unsure
	union DRAMTiming16 DRAMTiming16;
	union DRAMTiming17_HBM2 DRAMTiming17;
	union DRAMTiming18_HBM2 DRAMTiming18;
	union DRAMTiming21 DRAMTiming21;
	uint32_t unknown19; // possibly lpexit?
	uint32_t unknown20; // unsure
	union TRFCTimingCS01 tRFC;
	union DRAMTiming22_HBM2 DRAMTiming22;
};

struct timings_set_vega21 { // 96 bytes. Uncertain.
	union atom_mc_register_setting_id block_id;
	union DRAMTiming1 DRAMTiming1;
	union DRAMTiming2 DRAMTiming2;
	union DRAMTiming3 DRAMTiming3;
	union DRAMTiming4 DRAMTiming4;
	union DRAMTiming5 DRAMTiming5;
	union DRAMTiming6 DRAMTiming6;
	union DRAMTiming7 DRAMTiming7;
	union DRAMTiming8 DRAMTiming8;
	union DRAMTiming9_HBM2 DRAMTiming9;
	union DRAMTiming10 DRAMTiming10;

	union DRAMTiming12 DRAMTiming12;
	union DRAMTiming13 DRAMTiming13;
	union DRAMTiming14_HBM2 DRAMTiming14;
	uint32_t unknown15; // unsure
	union DRAMTiming16 DRAMTiming16;
	union DRAMTiming17_HBM2 DRAMTiming17;
	union DRAMTiming18_HBM2 DRAMTiming18;
	union DRAMTiming21 DRAMTiming21;
	union DRAMTiming22 DRAMTiming22;
	uint32_t unknown23; // unsure
	union TRFCTimingCS01 tRFC;
	union ChanPipeDly ChanPipeDly;
	uint32_t unkown24; // unsure
};

struct timings_set_navi1 { // 116 bytes. A little more certain.
	union atom_mc_register_setting_id block_id; //frequency

	struct UMCCTRL_MISC2 gddr6_mr5;
	struct UMCCTRL_PMG_CMD_MRS gddr6_mr0;
	uint32_t UMCCTRL_PMG_CMD_EMRS;
	struct UMCCTRL_PMG_CMD_MRS1 gddr6_mr4;
	struct PMG_CMD gddr6_mr8;
	union DRAMTiming1 DRAMTiming1;

	union DRAMTiming2 DRAMTiming2;
	union DRAMTiming3 DRAMTiming3;
	union DRAMTiming4 DRAMTiming4;
	union DRAMTiming5 DRAMTiming5;
	union DRAMTiming6 DRAMTiming6;

	union DRAMTiming7 DRAMTiming7;
	union DRAMTiming8 DRAMTiming8;

	union DRAMTiming9 DRAMTiming9;
	union DRAMTiming10 DRAMTiming10;
	union DRAMTiming12 DRAMTiming12;
	union DRAMTiming13 DRAMTiming13;
	union DRAMTiming14 DRAMTiming14;
	union DRAMTiming16 DRAMTiming16;
	union DRAMTiming17 DRAMTiming17;
	union DRAMTiming20 DRAMTiming20;
	union DRAMTiming21 DRAMTiming21;
	union DRAMTiming22 DRAMTiming22;
	union DRAMTiming23 DRAMTiming23;
	union DRAMTiming35 DRAMTiming35;
	union DRAMTiming36 DRAMTiming36;
	union TRFCTimingCS01 tRFC;
	union ChanPipeDly ChanPipeDly;
};


/******************************************************************************/
// mem_adjust table
// uncertain the accuracy of all of these tables.
/******************************************************************************/

struct mem_adjust_set_terascale2_ddr3 { // 108 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_io_reserve_d0_6_0     mc_seq_io_reserve_d0;
	union mc_io_txcntl_dphy0_d0_6_0    mc_io_txcntl_dphy0_d0;
	union mc_io_txcntl_aphy_d0_6_0     mc_io_txcntl_aphy_d0;
	union mc_io_rxcntl_dphy0_d0_6_0    mc_io_rxcntl_dphy0_d0;
	union mc_io_dphy_str_cntl_d0_7_1   mc_io_dphy_str_cntl_d0;
	union mc_io_aphy_str_cntl_d0_6_0_o mc_io_aphy_str_cntl_d0;
	union mc_pmg_cfg_6_0        mc_pmg_cfg;
	union mc_pmg_auto_cfg_6_0   mc_pmg_auto_cfg;
	union mc_seq_pmg_timing_6_0 mc_seq_pmg_timing;
	union mc_seq_wr_ctl_d0_6_0  mc_seq_wr_ctl_d0;
	union mc_io_pad_cntl_d0_6_0 mc_io_pad_cntl_d0;
	union mc_io_pad_cntl_d1_6_0 mc_io_pad_cntl_d1;
	union mc_io_debug_dqb0l_rxphase_d0_6_0 mc_io_debug_dqb0l_rxphase_d0;
	union mc_io_debug_dqb0l_rxphase_d1_6_0 mc_io_debug_dqb0l_rxphase_d1;
	union mc_io_debug_wck_rxphase_d0_6_0   mc_io_debug_wck_rxphase_d0;
	union mc_io_debug_edc_rxphase_d0_6_0   mc_io_debug_edc_rxphase_d0;
	union mc_io_debug_dbi_rxphase_d0_6_0   mc_io_debug_dbi_rxphase_d0;
	union mc_io_debug_dqb0l_txphase_d0_6_0 mc_io_debug_dqb0l_txphase_d0;
	union mc_io_debug_dqb0l_txphase_d1_6_0 mc_io_debug_dqb0l_txphase_d1;
	union mc_io_debug_dbi_txphase_d0_6_0   mc_io_debug_dbi_txphase_d0;
	union mc_io_debug_wck_txphase_d0_6_0   mc_io_debug_wck_txphase_d0;
	union mc_io_debug_edc_txphase_d0_6_0   mc_io_debug_edc_txphase_d0;
	union mc_io_debug_ck_txphase_d0_6_0    mc_io_debug_ck_txphase_d0;
	union mc_io_debug_addrl_txphase_d0_6_0 mc_io_debug_addrl_txphase_d0;
	union mc_io_debug_acmd_txphase_d0_6_0  mc_io_debug_acmd_txphase_d0;
	union mc_io_debug_cmd_txphase_d0_6_0   mc_io_debug_cmd_txphase_d0;
};

struct mem_adjust_set_terascale2_gddr5_type3 { // 172 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_io_reserve_d0_6_0     mc_seq_io_reserve_d0;
	union mc_io_txcntl_dphy0_d0_6_0    mc_io_txcntl_dphy0_d0;
	union mc_io_txcntl_aphy_d0_6_0     mc_io_txcntl_aphy_d0;
	union mc_io_rxcntl_dphy0_d0_6_0    mc_io_rxcntl_dphy0_d0;
	union mc_io_dphy_str_cntl_d0_7_1   mc_io_dphy_str_cntl_d0;
	union mc_io_aphy_str_cntl_d0_6_0_o mc_io_aphy_str_cntl_d0;
	union mc_pmg_cfg_6_0          mc_pmg_cfg;
	union mc_pmg_auto_cfg_6_0     mc_pmg_auto_cfg;
	union mc_seq_pmg_timing_6_0   mc_seq_pmg_timing;
	union mc_seq_wr_ctl_d0_6_0    mc_seq_wr_ctl_d0;
	union mc_io_pad_cntl_d0_6_0   mc_io_pad_cntl_d0;
	union mc_io_pad_cntl_d1_6_0   mc_io_pad_cntl_d1;
	union mc_tsm_debug_gcnt_6_0   mc_tsm_debug_gcnt;
	union mc_config_7_1           mc_config__0;
	union mc_tsm_debug_flag_6_0   mc_tsm_debug_flag__0;
	union mc_tsm_debug_bcnt6_6_0  mc_tsm_debug_bcnt6__0;
	union mc_config_7_1           mc_config__1;
	union mc_tsm_debug_flag_6_0   mc_tsm_debug_flag__1;
	union mc_tsm_debug_bcnt6_6_0  mc_tsm_debug_bcnt6__1;
	union mc_config_7_1           mc_config__2;
	union mc_tsm_debug_misc_6_0   mc_tsm_debug_misc;
	union mc_tsm_debug_bcnt0_6_0  mc_tsm_debug_bcnt0;
	union mc_tsm_debug_bcnt1_6_0  mc_tsm_debug_bcnt1;
	union mc_tsm_debug_bcnt2_6_0  mc_tsm_debug_bcnt2;
	union mc_tsm_debug_bcnt8_6_0  mc_tsm_debug_bcnt8;
	union mc_tsm_debug_bcnt9_6_0  mc_tsm_debug_bcnt9;
	union mc_tsm_debug_bcnt10_6_0 mc_tsm_debug_bcnt10;
	union mc_io_debug_up_14_6_0   mc_io_debug_up_14;
	union mc_io_debug_up_15_6_0   mc_io_debug_up_15;
	union mc_seq_reserve_0_s_7_1  mc_seq_reserve_0_s;
	union mc_seq_misc5_6_0  mc_seq_misc5;
	union mc_seq_misc4_6_0  mc_seq_misc4;
	union mc_seq_misc6_6_0  mc_seq_misc6;
	union mc_seq_misc7_6_0  mc_seq_misc7;
	union mc_io_debug_dqb0l_rx_vref_cal_d0_6_0 mc_io_debug_dqb0l_rx_vref_cal_d0;
	union mc_io_debug_dqb2l_rx_vref_cal_d0_6_0 mc_io_debug_dqb2l_rx_vref_cal_d0;
	union mc_io_debug_dbi_rx_vref_cal_d0_6_0   mc_io_debug_dbi_rx_vref_cal_d0;
	union mc_io_debug_dqb1_cdr_phsize_d0_6_0   mc_io_debug_dqb1_cdr_phsize_d0;
	union mc_io_debug_addrl_txphase_d0_6_0     mc_io_debug_addrl_txphase_d0;
	union mc_io_debug_acmd_txphase_d0_6_0      mc_io_debug_acmd_txphase_d0;
	union mc_io_debug_cmd_txphase_d0_6_0       mc_io_debug_cmd_txphase_d0;
	union mc_io_debug_ck_txphase_d0_6_0        mc_io_debug_ck_txphase_d0;
};

struct mem_adjust_set_terascale2_gddr5_type4 { // 196 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_io_reserve_d0_6_0     mc_seq_io_reserve_d0;
	union mc_io_txcntl_dphy0_d0_6_0    mc_io_txcntl_dphy0_d0;
	union mc_io_txcntl_aphy_d0_6_0     mc_io_txcntl_aphy_d0;
	union mc_io_rxcntl_dphy0_d0_6_0    mc_io_rxcntl_dphy0_d0;
	union mc_io_dphy_str_cntl_d0_7_1   mc_io_dphy_str_cntl_d0;
	union mc_io_aphy_str_cntl_d0_6_0_o mc_io_aphy_str_cntl_d0;
	union mc_pmg_cfg_6_0          mc_pmg_cfg;
	union mc_pmg_auto_cfg_6_0     mc_pmg_auto_cfg;
	union mc_seq_pmg_timing_6_0   mc_seq_pmg_timing;
	union mc_seq_wr_ctl_d0_6_0    mc_seq_wr_ctl_d0;
	union mc_io_pad_cntl_d0_6_0   mc_io_pad_cntl_d0;
	union mc_io_pad_cntl_d1_6_0   mc_io_pad_cntl_d1;
	union mc_tsm_debug_gcnt_6_0   mc_tsm_debug_gcnt;
	union mc_config_mcd_7_1       mc_config_mcd__0;
	union mc_tsm_debug_flag_6_0   mc_tsm_debug_flag__0;
	union mc_tsm_debug_bcnt6_6_0  mc_tsm_debug_bcnt6__0;
	union mc_config_mcd_7_1       mc_config_mcd__1;
	union mc_tsm_debug_flag_6_0   mc_tsm_debug_flag__1;
	union mc_tsm_debug_bcnt6_6_0  mc_tsm_debug_bcnt6__1;
	union mc_config_mcd_7_1       mc_config_mcd__2;
	union mc_tsm_debug_flag_6_0   mc_tsm_debug_flag__2;
	union mc_tsm_debug_bcnt6_6_0  mc_tsm_debug_bcnt6__2;
	union mc_config_mcd_7_1       mc_config_mcd__3;
	union mc_tsm_debug_flag_6_0   mc_tsm_debug_flag__3;
	union mc_tsm_debug_bcnt6_6_0  mc_tsm_debug_bcnt6__3;
	union mc_config_mcd_7_1       mc_config_mcd__4;
	union mc_tsm_debug_misc_6_0   mc_tsm_debug_misc;
	union mc_tsm_debug_bcnt0_6_0  mc_tsm_debug_bcnt0;
	union mc_tsm_debug_bcnt1_6_0  mc_tsm_debug_bcnt1;
	union mc_tsm_debug_bcnt2_6_0  mc_tsm_debug_bcnt2;
	union mc_tsm_debug_bcnt8_6_0  mc_tsm_debug_bcnt8;
	union mc_tsm_debug_bcnt9_6_0  mc_tsm_debug_bcnt9;
	union mc_tsm_debug_bcnt10_6_0 mc_tsm_debug_bcnt10;
	union mc_io_debug_up_14_6_0   mc_io_debug_up_14;
	union mc_io_debug_up_15_6_0   mc_io_debug_up_15;
	union mc_seq_reserve_0_s_7_1  mc_seq_reserve_0_s;
	union mc_seq_misc5_6_0  mc_seq_misc5;
	union mc_seq_misc4_6_0  mc_seq_misc4;
	union mc_seq_misc6_6_0  mc_seq_misc6;
	union mc_seq_misc7_6_0  mc_seq_misc7;
	union mc_io_debug_dqb0l_rx_vref_cal_d0_6_0 mc_io_debug_dqb0l_rx_vref_cal_d0;
	union mc_io_debug_dqb2l_rx_vref_cal_d0_6_0 mc_io_debug_dqb2l_rx_vref_cal_d0;
	union mc_io_debug_dbi_rx_vref_cal_d0_6_0   mc_io_debug_dbi_rx_vref_cal_d0;
	union mc_io_debug_dqb1_cdr_phsize_d0_6_0   mc_io_debug_dqb1_cdr_phsize_d0;
	union mc_io_debug_addrl_txphase_d0_6_0     mc_io_debug_addrl_txphase_d0;
	union mc_io_debug_acmd_txphase_d0_6_0      mc_io_debug_acmd_txphase_d0;
	union mc_io_debug_cmd_txphase_d0_6_0       mc_io_debug_cmd_txphase_d0;
	union mc_io_debug_ck_txphase_d0_6_0        mc_io_debug_ck_txphase_d0;

};

struct mem_adjust_set_terascale3_gddr5 { // 196 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_io_reserve_d0_6_0     mc_seq_io_reserve_d0;
	union mc_io_txcntl_dphy0_d0_6_0    mc_io_txcntl_dphy0_d0;
	union mc_io_dphy_str_cntl_d0_6_0   mc_io_dphy_str_cntl_d0;
	union mc_io_aphy_str_cntl_d0_6_0_o mc_io_aphy_str_cntl_d0;
	union mc_pmg_cfg_6_0         mc_pmg_cfg;
	union mc_pmg_auto_cfg_6_0    mc_pmg_auto_cfg;
	union mc_seq_pmg_timing_6_0  mc_seq_pmg_timing;
	union mc_seq_wr_ctl_d0_6_0   mc_seq_wr_ctl_d0;
	union mc_io_pad_cntl_d0_6_0  mc_io_pad_cntl_d0;
	union mc_io_pad_cntl_d1_6_0  mc_io_pad_cntl_d1;
	union mc_io_debug_up_0_6_0   mc_io_debug_up_0;
	union mc_config_6_0          mc_config_0;
	union mc_io_debug_up_1_6_0   mc_io_debug_up_1__0;
	union mc_io_debug_up_9_6_0   mc_io_debug_up_9__0;
	union mc_config_6_0          mc_config_1_9__0;
	union mc_io_debug_up_1_6_0   mc_io_debug_up_1__1;
	union mc_io_debug_up_9_6_0   mc_io_debug_up_9__1;
	union mc_config_6_0          mc_config_1_9__1;
	union mc_io_debug_up_1_6_0   mc_io_debug_up_1__2;
	union mc_io_debug_up_9_6_0   mc_io_debug_up_9__2;
	union mc_config_6_0          mc_config_1_9__2;
	union mc_io_debug_up_1_6_0   mc_io_debug_up_1__3;
	union mc_io_debug_up_9_6_0   mc_io_debug_up_9__3;
	union mc_config_6_0          mc_config_1_9__3;
	union mc_io_debug_up_2_6_0   mc_io_debug_up_2;
	union mc_io_debug_up_3_6_0   mc_io_debug_up_3;
	union mc_io_debug_up_4_6_0   mc_io_debug_up_4;
	union mc_io_debug_up_5_6_0   mc_io_debug_up_5;
	union mc_io_debug_up_11_6_0  mc_io_debug_up_11;
	union mc_io_debug_up_12_6_0  mc_io_debug_up_12;
	union mc_io_debug_up_13_6_0  mc_io_debug_up_13;
	union mc_io_debug_up_14_6_0  mc_io_debug_up_14;
	union mc_io_debug_up_15_6_0  mc_io_debug_up_15;
	union mc_seq_reserve_0_s_6_0 mc_seq_reserve_0_s;
	union mc_seq_misc5_6_0  mc_seq_misc5;
	union mc_seq_misc4_6_0  mc_seq_misc4;
	union mc_seq_misc6_6_0  mc_seq_misc6;
	union mc_seq_misc7_6_0  mc_seq_misc7;
	union mc_io_debug_dqb0l_rx_vref_cal_d0_6_0 mc_io_debug_dqb0l_rx_vref_cal_d0;
	union mc_io_debug_dqb2l_rx_vref_cal_d0_6_0 mc_io_debug_dqb2l_rx_vref_cal_d0;
	union mc_io_debug_dbi_rx_vref_cal_d0_6_0   mc_io_debug_dbi_rx_vref_cal_d0;
	union mc_io_debug_dqb1_cdr_phsize_d0_6_0   mc_io_debug_dqb1_cdr_phsize_d0;
	union mc_io_debug_addrl_txphase_d0_6_0     mc_io_debug_addrl_txphase_d0;
	union mc_io_debug_acmd_txphase_d0_6_0      mc_io_debug_acmd_txphase_d0;
	union mc_io_debug_cmd_txphase_d0_6_0       mc_io_debug_cmd_txphase_d0;
	union mc_io_debug_ck_txphase_d0_6_0        mc_io_debug_ck_txphase_d0;
};

struct mem_adjust_set_gcn1_gddr5_type1 { // 232 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_io_reserve_d0_6_0     mc_seq_io_reserve_d0;
	union mc_io_txcntl_dphy0_d0_6_0    mc_io_txcntl_dphy0_d0;
	union mc_io_txcntl_aphy_d0_6_0     mc_io_txcntl_aphy_d0;
	union mc_io_rxcntl_dphy0_d0_6_0    mc_io_rxcntl_dphy0_d0;
	union mc_io_rxcntl1_dphy0_d0_6_0   mc_io_rxcntl1_dphy0_d0;
	union mc_io_dphy_str_cntl_d0_6_0   mc_io_dphy_str_cntl_d0;
	union mc_io_aphy_str_cntl_d0_6_0_o mc_io_aphy_str_cntl_d0;
	union mc_pmg_cfg_6_0          mc_pmg_cfg;
	union mc_pmg_auto_cfg_6_0     mc_pmg_auto_cfg;
	union mc_seq_rd_ctl_d0_6_0    mc_seq_rd_ctl_d0;
	union mc_io_pad_cntl_d0_6_0   mc_io_pad_cntl_d0;
	union mc_io_pad_cntl_d1_6_0   mc_io_pad_cntl_d1;
	union mc_phy_timing_2_6_0     mc_phy_timing_2;
	union mc_tsm_debug_gcnt_6_0   mc_tsm_debug_gcnt;
	union mc_tsm_debug_misc_6_0   mc_tsm_debug_misc;
	union mc_tsm_debug_bcnt0_6_0  mc_tsm_debug_bcnt0;
	union mc_tsm_debug_bcnt1_6_0  mc_tsm_debug_bcnt1;
	union mc_tsm_debug_bcnt2_6_0  mc_tsm_debug_bcnt2;
	union mc_tsm_debug_bcnt7_6_0  mc_tsm_debug_bcnt7;
	union mc_tsm_debug_bcnt8_6_0  mc_tsm_debug_bcnt8;
	union mc_tsm_debug_bcnt9_6_0  mc_tsm_debug_bcnt9;
	union mc_tsm_debug_bcnt10_6_0 mc_tsm_debug_bcnt10;
	union mc_io_debug_up_14_6_0   mc_io_debug_up_14;
	union mc_io_debug_up_15_6_0   mc_io_debug_up_15;
	union mc_seq_reserve_0_s_6_0  mc_seq_reserve_0_s;
	union mc_seq_misc5_6_0  mc_seq_misc5;
	union mc_seq_misc4_6_0  mc_seq_misc4;
	union mc_seq_misc6_6_0  mc_seq_misc6;
	union mc_seq_misc7_6_0  mc_seq_misc7;
	union mc_seq_misc9_6_0  mc_seq_misc9;
	union mc_arb_rtt_cntl0_6_0  mc_arb_rtt_cntl0;
	union mc_arb_rtt_cntl1_6_0  mc_arb_rtt_cntl1;
	union mc_arb_rtt_cntl2_6_0  mc_arb_rtt_cntl2;
	union mc_io_debug_addrl_txphase_d0_6_0   mc_io_debug_addrl_txphase_d0;
	union mc_io_debug_acmd_txphase_d0_6_0    mc_io_debug_acmd_txphase_d0;
	union mc_io_debug_cmd_txphase_d0_6_0     mc_io_debug_cmd_txphase_d0;
	union mc_io_debug_ck_txphase_d0_6_0      mc_io_debug_ck_txphase_d0;
	union mc_io_debug_dqb0l_ofscal_d0_6_0    mc_io_debug_dqb0l_ofscal_d0;
	union mc_io_debug_dqb0l_ofscal_d1_6_0    mc_io_debug_dqb0l_ofscal_d1;
	union mc_io_debug_cmd_ofscal_d0_6_0      mc_io_debug_cmd_ofscal_d0;
	union mc_io_debug_dqb0_cdr_phsize_d0_6_0 mc_io_debug_dqb0_cdr_phsize_d0;
	union mc_io_debug_dqb0_cdr_phsize_d1_6_0 mc_io_debug_dqb0_cdr_phsize_d1;
	union mc_io_debug_dqb0l_rx_eq_d0_6_0     mc_io_debug_dqb0l_rx_eq_d0;
	union mc_io_debug_dqb0l_rx_eq_d1_6_0     mc_io_debug_dqb0l_rx_eq_d1;
	union mc_io_debug_wck_rx_eq_d0_6_0       mc_io_debug_wck_rx_eq_d0;
	union mc_io_debug_dbi_ofscal_d0_6_0      mc_io_debug_dbi_ofscal_d0;
	union mc_io_debug_edc_ofscal_d0_6_0      mc_io_debug_edc_ofscal_d0;
	union mc_io_debug_wck_ofscal_d0_6_0      mc_io_debug_wck_ofscal_d0;
	union mc_io_debug_edc_cdr_phsize_d0_6_0  mc_io_debug_edc_cdr_phsize_d0;
	union mc_io_debug_acmd_ofscal_d0_6_0     mc_io_debug_acmd_ofscal_d0;
	union mc_io_debug_dbi_cdr_phsize_d0_6_0  mc_io_debug_dbi_cdr_phsize_d0;
	union mc_io_debug_dbi_rx_eq_d0_6_0       mc_io_debug_dbi_rx_eq_d0;
	union mc_io_debug_edc_rx_eq_d0_6_0       mc_io_debug_edc_rx_eq_d0;
	union mc_io_cdrcntl_d0_6_0  mc_io_cdrcntl_d0;
	union mc_io_cdrcntl1_d0_6_0 mc_io_cdrcntl1_d0;
	union mc_io_debug_dqb0l_rx_vref_cal_d0_6_0 mc_io_debug_dqb0l_rx_vref_cal_d0;
	union mc_io_debug_dqb0l_rx_vref_cal_d1_6_0 mc_io_debug_dqb0l_rx_vref_cal_d1;
};

struct mem_adjust_set_gcn1_gddr5_type2 { // 284 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_io_reserve_d0_6_0     mc_seq_io_reserve_d0;
	union mc_io_txcntl_dphy0_d0_6_0    mc_io_txcntl_dphy0_d0;
	union mc_io_txcntl_aphy_d0_6_0     mc_io_txcntl_aphy_d0;
	union mc_io_rxcntl_dphy0_d0_6_0    mc_io_rxcntl_dphy0_d0;
	union mc_io_rxcntl1_dphy0_d0_7_1   mc_io_rxcntl1_dphy0_d0;
	union mc_io_dphy_str_cntl_d0_7_1   mc_io_dphy_str_cntl_d0;
	union mc_io_aphy_str_cntl_d0_6_0_o mc_io_aphy_str_cntl_d0;
	union mc_pmg_cfg_6_0          mc_pmg_cfg;
	union mc_pmg_auto_cfg_6_0     mc_pmg_auto_cfg;
	union mc_seq_rd_ctl_d0_6_0    mc_seq_rd_ctl_d0;
	union mc_io_pad_cntl_d0_6_0   mc_io_pad_cntl_d0;
	union mc_io_pad_cntl_d1_6_0   mc_io_pad_cntl_d1;
	union mc_phy_timing_2_7_1     mc_phy_timing_2;
	union mc_tsm_debug_gcnt_6_0   mc_tsm_debug_gcnt;
	union mc_tsm_debug_misc_6_0   mc_tsm_debug_misc;
	union mc_tsm_debug_bcnt0_6_0  mc_tsm_debug_bcnt0;
	union mc_tsm_debug_bcnt1_6_0  mc_tsm_debug_bcnt1;
	union mc_tsm_debug_bcnt2_6_0  mc_tsm_debug_bcnt2;
	union mc_tsm_debug_bcnt7_6_0  mc_tsm_debug_bcnt7;
	union mc_tsm_debug_bcnt8_6_0  mc_tsm_debug_bcnt8;
	union mc_tsm_debug_bcnt9_6_0  mc_tsm_debug_bcnt9;
	union mc_tsm_debug_bcnt10_6_0 mc_tsm_debug_bcnt10;
	union mc_io_debug_up_14_6_0   mc_io_debug_up_14;
	union mc_io_debug_up_15_6_0   mc_io_debug_up_15;
	union mc_seq_reserve_0_s_7_1  mc_seq_reserve_0_s;
	union mc_seq_misc5_6_0  mc_seq_misc5;
	union mc_seq_misc4_6_0  mc_seq_misc4;
	union mc_seq_misc6_6_0  mc_seq_misc6;
	union mc_seq_misc7_6_0  mc_seq_misc7;
	union mc_seq_misc9_6_0  mc_seq_misc9;
	union mc_arb_rtt_cntl0_6_0  mc_arb_rtt_cntl0;
	union mc_arb_rtt_cntl1_6_0  mc_arb_rtt_cntl1;
	union mc_arb_rtt_cntl2_6_0  mc_arb_rtt_cntl2;
	union mc_io_debug_addrl_txphase_d0_6_0     mc_io_debug_addrl_txphase_d0;
	union mc_io_debug_acmd_txphase_d0_6_0      mc_io_debug_acmd_txphase_d0;
	union mc_io_debug_cmd_txphase_d0_6_0       mc_io_debug_cmd_txphase_d0;
	union mc_io_debug_ck_txphase_d0_6_0        mc_io_debug_ck_txphase_d0;
	union mc_io_debug_dqb0l_ofscal_d0_6_0      mc_io_debug_dqb0l_ofscal_d0;
	union mc_io_debug_dqb0l_ofscal_d1_6_0      mc_io_debug_dqb0l_ofscal_d1;
	union mc_io_debug_cmd_ofscal_d0_6_0        mc_io_debug_cmd_ofscal_d0;
	union mc_io_debug_dqb0_cdr_phsize_d0_6_0   mc_io_debug_dqb0_cdr_phsize_d0;
	union mc_io_debug_dqb0_cdr_phsize_d1_6_0   mc_io_debug_dqb0_cdr_phsize_d1;
	union mc_io_debug_dqb0l_rx_eq_d0_6_0       mc_io_debug_dqb0l_rx_eq_d0;
	union mc_io_debug_dqb0l_rx_eq_d1_6_0       mc_io_debug_dqb0l_rx_eq_d1;
	union mc_io_debug_wck_rx_eq_d0_6_0         mc_io_debug_wck_rx_eq_d0;
	union mc_io_debug_wcdr_cdr_phsize_d0_6_0   mc_io_debug_wcdr_cdr_phsize_d0;
	union mc_io_debug_dbi_txbst_pd_d0_6_0      mc_io_debug_dbi_txbst_pd_d0;
	union mc_io_debug_dbi_txbst_pu_d0_6_0      mc_io_debug_dbi_txbst_pu_d0;
	union mc_io_debug_edc_txbst_pd_d0_6_0      mc_io_debug_edc_txbst_pd_d0;
	union mc_io_debug_edc_txbst_pu_d0_6_0      mc_io_debug_edc_txbst_pu_d0;
	union mc_io_debug_dqb0l_txbst_pd_d0_6_0    mc_io_debug_dqb0l_txbst_pd_d0;
	union mc_io_debug_dqb0l_txbst_pd_d1_6_0    mc_io_debug_dqb0l_txbst_pd_d1;
	union mc_io_debug_dqb0l_txbst_pu_d0_6_0    mc_io_debug_dqb0l_txbst_pu_d0;
	union mc_io_debug_dqb0l_txbst_pu_d1_6_0    mc_io_debug_dqb0l_txbst_pu_d1;
	union mc_io_debug_ck_txbst_pd_d0_6_0       mc_io_debug_ck_txbst_pd_d0;
	union mc_io_debug_ck_txbst_pd_d1_6_0       mc_io_debug_ck_txbst_pd_d1;
	union mc_io_debug_ck_txbst_pu_d0_6_0       mc_io_debug_ck_txbst_pu_d0;
	union mc_io_debug_ck_txbst_pu_d1_6_0       mc_io_debug_ck_txbst_pu_d1;
	union mc_io_debug_dbi_ofscal_d0_6_0        mc_io_debug_dbi_ofscal_d0;
	union mc_io_debug_edc_ofscal_d0_6_0        mc_io_debug_edc_ofscal_d0;
	union mc_io_debug_wck_ofscal_d0_6_0        mc_io_debug_wck_ofscal_d0;
	union mc_io_debug_edc_cdr_phsize_d0_6_0    mc_io_debug_edc_cdr_phsize_d0;
	union mc_io_debug_acmd_ofscal_d0_6_0       mc_io_debug_acmd_ofscal_d0;
	union mc_io_debug_dbi_cdr_phsize_d0_6_0    mc_io_debug_dbi_cdr_phsize_d0;
	union mc_io_debug_dbi_rx_eq_d0_6_0         mc_io_debug_dbi_rx_eq_d0;
	union mc_io_debug_edc_rx_eq_d0_6_0         mc_io_debug_edc_rx_eq_d0;
	union mc_io_cdrcntl_d0_6_0                 mc_io_cdrcntl_d0;
	union mc_io_cdrcntl1_d0_6_0                mc_io_cdrcntl1_d0;
	union mc_io_debug_dqb0l_rx_vref_cal_d0_6_0 mc_io_debug_dqb0l_rx_vref_cal_d0;
	union mc_io_debug_dqb0l_rx_vref_cal_d1_6_0 mc_io_debug_dqb0l_rx_vref_cal_d1;
};

struct mem_adjust_set_gcn1_gddr5_type3 { // 304 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_io_reserve_d0_6_0     mc_seq_io_reserve_d0;
	union mc_io_txcntl_dphy0_d0_6_0    mc_io_txcntl_dphy0_d0;
	union mc_io_txcntl_aphy_d0_6_0     mc_io_txcntl_aphy_d0;
	union mc_io_rxcntl_dphy0_d0_6_0    mc_io_rxcntl_dphy0_d0;
	union mc_io_rxcntl1_dphy0_d0_7_1   mc_io_rxcntl1_dphy0_d0;
	union mc_io_dphy_str_cntl_d0_7_1   mc_io_dphy_str_cntl_d0;
	union mc_io_aphy_str_cntl_d0_6_0_o mc_io_aphy_str_cntl_d0;
	union mc_pmg_cfg_6_0          mc_pmg_cfg;
	union mc_pmg_auto_cfg_6_0     mc_pmg_auto_cfg;
	union mc_seq_rd_ctl_d0_6_0    mc_seq_rd_ctl_d0;
	union mc_io_pad_cntl_d0_6_0   mc_io_pad_cntl_d0;
	union mc_io_pad_cntl_d1_6_0   mc_io_pad_cntl_d1;
	union mc_phy_timing_2_7_1     mc_phy_timing_2;
	union mc_tsm_debug_gcnt_6_0   mc_tsm_debug_gcnt;
	union mc_tsm_debug_misc_6_0   mc_tsm_debug_misc;
	union mc_tsm_debug_bcnt0_6_0  mc_tsm_debug_bcnt0;
	union mc_tsm_debug_bcnt1_6_0  mc_tsm_debug_bcnt1;
	union mc_tsm_debug_bcnt2_6_0  mc_tsm_debug_bcnt2;
	union mc_tsm_debug_bcnt7_6_0  mc_tsm_debug_bcnt7;
	union mc_tsm_debug_bcnt8_6_0  mc_tsm_debug_bcnt8;
	union mc_tsm_debug_bcnt9_6_0  mc_tsm_debug_bcnt9;
	union mc_tsm_debug_bcnt10_6_0 mc_tsm_debug_bcnt10;
	union mc_io_debug_up_14_6_0   mc_io_debug_up_14;
	union mc_io_debug_up_15_6_0   mc_io_debug_up_15;
	union mc_seq_reserve_0_s_7_1  mc_seq_reserve_0_s;
	union mc_seq_misc5_6_0  mc_seq_misc5;
	union mc_seq_misc4_6_0  mc_seq_misc4;
	union mc_seq_misc6_6_0  mc_seq_misc6;
	union mc_seq_misc7_6_0  mc_seq_misc7;
	union mc_seq_misc9_6_0  mc_seq_misc9;
	union mc_arb_rtt_cntl0_6_0  mc_arb_rtt_cntl0;
	union mc_arb_rtt_cntl1_6_0  mc_arb_rtt_cntl1;
	union mc_arb_rtt_cntl2_6_0  mc_arb_rtt_cntl2;
	union mc_io_debug_addrl_txphase_d0_6_0     mc_io_debug_addrl_txphase_d0;
	union mc_io_debug_acmd_txphase_d0_6_0      mc_io_debug_acmd_txphase_d0;
	union mc_io_debug_cmd_txphase_d0_6_0       mc_io_debug_cmd_txphase_d0;
	union mc_io_debug_ck_txphase_d0_6_0        mc_io_debug_ck_txphase_d0;
	union mc_io_debug_dqb0l_ofscal_d0_6_0      mc_io_debug_dqb0l_ofscal_d0;
	union mc_io_debug_dqb0l_ofscal_d1_6_0      mc_io_debug_dqb0l_ofscal_d1;
	union mc_io_debug_cmd_ofscal_d0_6_0        mc_io_debug_cmd_ofscal_d0;
	union mc_io_debug_dqb0_cdr_phsize_d0_6_0   mc_io_debug_dqb0_cdr_phsize_d0;
	union mc_io_debug_dqb0_cdr_phsize_d1_6_0   mc_io_debug_dqb0_cdr_phsize_d1;
	union mc_io_debug_dqb0l_rx_eq_d0_6_0       mc_io_debug_dqb0l_rx_eq_d0;
	union mc_io_debug_dqb0l_rx_eq_d1_6_0       mc_io_debug_dqb0l_rx_eq_d1;
	union mc_io_debug_wck_rx_eq_d0_6_0         mc_io_debug_wck_rx_eq_d0;
	union mc_io_debug_wcdr_ofscal_d0_6_0       mc_io_debug_wcdr_ofscal_d0;
	union mc_io_debug_wcdr_rx_vref_cal_d0_6_0  mc_io_debug_wcdr_rx_vref_cal_d0;
	union mc_io_debug_wcdr_rx_eq_d0_6_0        mc_io_debug_wcdr_rx_eq_d0;
	union mc_io_debug_wcdr_cdr_phsize_d0_6_0   mc_io_debug_wcdr_cdr_phsize_d0;
	union mc_io_debug_dbi_txbst_pd_d0_6_0      mc_io_debug_dbi_txbst_pd_d0;
	union mc_io_debug_dbi_txbst_pu_d0_6_0      mc_io_debug_dbi_txbst_pu_d0;
	union mc_io_debug_edc_txbst_pd_d0_6_0      mc_io_debug_edc_txbst_pd_d0;
	union mc_io_debug_edc_txbst_pu_d0_6_0      mc_io_debug_edc_txbst_pu_d0;
	union mc_io_debug_wcdr_txbst_pd_d0_6_0     mc_io_debug_wcdr_txbst_pd_d0;
	union mc_io_debug_wcdr_txbst_pu_d0_6_0     mc_io_debug_wcdr_txbst_pu_d0;
	union mc_io_debug_dqb0l_txbst_pd_d0_6_0    mc_io_debug_dqb0l_txbst_pd_d0;
	union mc_io_debug_dqb0l_txbst_pd_d1_6_0    mc_io_debug_dqb0l_txbst_pd_d1;
	union mc_io_debug_dqb0l_txbst_pu_d0_6_0    mc_io_debug_dqb0l_txbst_pu_d0;
	union mc_io_debug_dqb0l_txbst_pu_d1_6_0    mc_io_debug_dqb0l_txbst_pu_d1;
	union mc_io_debug_ck_txbst_pd_d0_6_0       mc_io_debug_ck_txbst_pd_d0;
	union mc_io_debug_ck_txbst_pd_d1_6_0       mc_io_debug_ck_txbst_pd_d1;
	union mc_io_debug_ck_txbst_pu_d0_6_0       mc_io_debug_ck_txbst_pu_d0;
	union mc_io_debug_ck_txbst_pu_d1_6_0       mc_io_debug_ck_txbst_pu_d1;
	union mc_io_debug_dbi_ofscal_d0_6_0        mc_io_debug_dbi_ofscal_d0;
	union mc_io_debug_edc_ofscal_d0_6_0        mc_io_debug_edc_ofscal_d0;
	union mc_io_debug_wck_ofscal_d0_6_0        mc_io_debug_wck_ofscal_d0;
	union mc_io_debug_edc_cdr_phsize_d0_6_0    mc_io_debug_edc_cdr_phsize_d0;
	union mc_io_debug_acmd_ofscal_d0_6_0       mc_io_debug_acmd_ofscal_d0;
	union mc_io_debug_dbi_cdr_phsize_d0_6_0    mc_io_debug_dbi_cdr_phsize_d0;
	union mc_io_debug_dbi_rx_eq_d0_6_0         mc_io_debug_dbi_rx_eq_d0;
	union mc_io_debug_edc_rx_eq_d0_6_0         mc_io_debug_edc_rx_eq_d0;
	union mc_io_cdrcntl_d0_6_0                 mc_io_cdrcntl_d0;
	union mc_io_cdrcntl1_d0_6_0                mc_io_cdrcntl1_d0;
	union mc_io_debug_dqb0l_rx_vref_cal_d0_6_0 mc_io_debug_dqb0l_rx_vref_cal_d0;
	union mc_io_debug_dqb0l_rx_vref_cal_d1_6_0 mc_io_debug_dqb0l_rx_vref_cal_d1;
};

struct mem_adjust_set_gcn1_gddr5_type4 { // 128 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_io_reserve_d0_6_0     mc_seq_io_reserve_d0;
	union mc_io_txcntl_dphy0_d0_6_0    mc_io_txcntl_dphy0_d0;
	union mc_io_txcntl_aphy_d0_6_0     mc_io_txcntl_aphy_d0;
	union mc_io_rxcntl_dphy0_d0_6_0    mc_io_rxcntl_dphy0_d0;
	union mc_io_rxcntl1_dphy0_d0_7_1   mc_io_rxcntl1_dphy0_d0;
	union mc_io_dphy_str_cntl_d0_7_1   mc_io_dphy_str_cntl_d0;
	union mc_io_aphy_str_cntl_d0_6_0_o mc_io_aphy_str_cntl_d0;
	union mc_pmg_cfg_6_0        mc_pmg_cfg;
	union mc_pmg_auto_cfg_6_0   mc_pmg_auto_cfg;
	union mc_seq_rd_ctl_d0_6_0  mc_seq_rd_ctl_d0;
	union mc_io_pad_cntl_d0_6_0 mc_io_pad_cntl_d0;
	union mc_io_pad_cntl_d1_6_0 mc_io_pad_cntl_d1;
	union mc_phy_timing_2_7_1   mc_phy_timing_2;
	union mc_io_debug_dqb0l_rxphase_d0_6_0 mc_io_debug_dqb0l_rxphase_d0;
	union mc_io_debug_dqb0l_rxphase_d1_6_0 mc_io_debug_dqb0l_rxphase_d1;
	union mc_io_debug_wck_rxphase_d0_6_0   mc_io_debug_wck_rxphase_d0;
	union mc_io_debug_edc_rxphase_d0_6_0   mc_io_debug_edc_rxphase_d0;
	union mc_io_debug_dbi_rxphase_d0_6_0   mc_io_debug_dbi_rxphase_d0;
	union mc_io_debug_dqb0l_txphase_d0_6_0 mc_io_debug_dqb0l_txphase_d0;
	union mc_io_debug_dqb0l_txphase_d1_6_0 mc_io_debug_dqb0l_txphase_d1;
	union mc_io_debug_dbi_txphase_d0_6_0   mc_io_debug_dbi_txphase_d0;
	union mc_io_debug_wck_txphase_d0_6_0   mc_io_debug_wck_txphase_d0;
	union mc_io_debug_edc_txphase_d0_6_0   mc_io_debug_edc_txphase_d0;
	union mc_io_debug_ck_txphase_d0_6_0    mc_io_debug_ck_txphase_d0;
	union mc_io_debug_addrl_txphase_d0_6_0 mc_io_debug_addrl_txphase_d0;
	union mc_io_debug_acmd_txphase_d0_6_0  mc_io_debug_acmd_txphase_d0;
	union mc_io_debug_cmd_txphase_d0_6_0   mc_io_debug_cmd_txphase_d0;
	union mc_io_debug_addrl_clksel_d0_6_0  mc_io_debug_addrl_clksel_d0;
	union mc_io_debug_addrl_clksel_d1_6_0  mc_io_debug_addrl_clksel_d1;
	union mc_seq_misc5_6_0    mc_seq_misc5;
	union mc_seq_fifo_ctl_7_1 mc_seq_fifo_ctl;
};

struct mem_adjust_set_gcn2_gddr5 { // 288 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_io_reserve_d0_6_0     mc_seq_io_reserve_d0;
	union mc_io_txcntl_dphy0_d0_6_0    mc_io_txcntl_dphy0_d0;
	union mc_io_txcntl_aphy_d0_6_0     mc_io_txcntl_aphy_d0;
	union mc_io_rxcntl_dphy0_d0_6_0    mc_io_rxcntl_dphy0_d0;
	union mc_io_rxcntl1_dphy0_d0_7_1   mc_io_rxcntl1_dphy0_d0;
	union mc_io_dphy_str_cntl_d0_7_1   mc_io_dphy_str_cntl_d0;
	union mc_io_aphy_str_cntl_d0_6_0_o mc_io_aphy_str_cntl_d0;
	union mc_pmg_cfg_6_0          mc_pmg_cfg;
	union mc_pmg_auto_cfg_6_0     mc_pmg_auto_cfg;
	union mc_seq_rd_ctl_d0_6_0    mc_seq_rd_ctl_d0;
	union mc_io_pad_cntl_d0_6_0   mc_io_pad_cntl_d0;
	union mc_io_pad_cntl_d1_6_0   mc_io_pad_cntl_d1;
	union mc_phy_timing_2_7_1     mc_phy_timing_2;
	union mc_tsm_debug_gcnt_6_0   mc_tsm_debug_gcnt;
	union mc_tsm_debug_misc_6_0   mc_tsm_debug_misc;
	union mc_tsm_debug_bcnt0_6_0  mc_tsm_debug_bcnt0;
	union mc_tsm_debug_bcnt1_6_0  mc_tsm_debug_bcnt1;
	union mc_tsm_debug_bcnt2_6_0  mc_tsm_debug_bcnt2;
	union mc_tsm_debug_bcnt7_6_0  mc_tsm_debug_bcnt7;
	union mc_tsm_debug_bcnt8_6_0  mc_tsm_debug_bcnt8;
	union mc_tsm_debug_bcnt9_6_0  mc_tsm_debug_bcnt9;
	union mc_tsm_debug_bcnt10_6_0 mc_tsm_debug_bcnt10;
	union mc_io_debug_up_14_6_0   mc_io_debug_up_14;
	union mc_io_debug_up_15_6_0   mc_io_debug_up_15;
	union mc_seq_reserve_0_s_7_1  mc_seq_reserve_0_s;
	union mc_seq_misc5_6_0  mc_seq_misc5;
	union mc_seq_misc4_6_0  mc_seq_misc4;
	union mc_seq_misc6_6_0  mc_seq_misc6;
	union mc_seq_misc7_6_0  mc_seq_misc7;
	union mc_seq_misc9_6_0  mc_seq_misc9;
	union mc_arb_rtt_cntl0_6_0  mc_arb_rtt_cntl0;
	union mc_arb_rtt_cntl1_6_0  mc_arb_rtt_cntl1;
	union mc_arb_rtt_cntl2_6_0  mc_arb_rtt_cntl2;
	union mc_seq_g5pdx_ctrl_7_1 mc_seq_g5pdx_ctrl;
	union mc_io_debug_addrl_txphase_d0_6_0     mc_io_debug_addrl_txphase_d0;
	union mc_io_debug_acmd_txphase_d0_6_0      mc_io_debug_acmd_txphase_d0;
	union mc_io_debug_cmd_txphase_d0_6_0       mc_io_debug_cmd_txphase_d0;
	union mc_io_debug_ck_txphase_d0_6_0        mc_io_debug_ck_txphase_d0;
	union mc_io_debug_dqb0l_ofscal_d0_6_0      mc_io_debug_dqb0l_ofscal_d0;
	union mc_io_debug_dqb0l_ofscal_d1_6_0      mc_io_debug_dqb0l_ofscal_d1;
	union mc_io_debug_cmd_ofscal_d0_6_0        mc_io_debug_cmd_ofscal_d0;
	union mc_io_debug_dqb0_cdr_phsize_d0_6_0   mc_io_debug_dqb0_cdr_phsize_d0;
	union mc_io_debug_dqb0_cdr_phsize_d1_6_0   mc_io_debug_dqb0_cdr_phsize_d1;
	union mc_io_debug_dqb0l_rx_eq_d0_6_0       mc_io_debug_dqb0l_rx_eq_d0;
	union mc_io_debug_dqb0l_rx_eq_d1_6_0       mc_io_debug_dqb0l_rx_eq_d1;
	union mc_io_debug_wck_rx_eq_d0_6_0         mc_io_debug_wck_rx_eq_d0;
	union mc_io_debug_wcdr_ofscal_d0_6_0       mc_io_debug_wcdr_ofscal_d0;
	union mc_io_debug_wcdr_rx_vref_cal_d0_6_0  mc_io_debug_wcdr_rx_vref_cal_d0;
	union mc_io_debug_wcdr_rx_eq_d0_6_0        mc_io_debug_wcdr_rx_eq_d0;
	union mc_io_debug_wcdr_cdr_phsize_d0_6_0   mc_io_debug_wcdr_cdr_phsize_d0;
	union mc_io_debug_dbi_txbst_pd_d0_6_0      mc_io_debug_dbi_txbst_pd_d0;
	union mc_io_debug_dbi_txbst_pu_d0_6_0      mc_io_debug_dbi_txbst_pu_d0;
	union mc_io_debug_edc_txbst_pd_d0_6_0      mc_io_debug_edc_txbst_pd_d0;
	union mc_io_debug_edc_txbst_pu_d0_6_0      mc_io_debug_edc_txbst_pu_d0;
	union mc_io_debug_wcdr_txbst_pd_d0_6_0     mc_io_debug_wcdr_txbst_pd_d0;
	union mc_io_debug_wcdr_txbst_pu_d0_6_0     mc_io_debug_wcdr_txbst_pu_d0;
	union mc_io_debug_dqb0l_txbst_pd_d0_6_0    mc_io_debug_dqb0l_txbst_pd_d0;
	union mc_io_debug_dqb0l_txbst_pd_d1_6_0    mc_io_debug_dqb0l_txbst_pd_d1;
	union mc_io_debug_dqb0l_txbst_pu_d0_6_0    mc_io_debug_dqb0l_txbst_pu_d0;
	union mc_io_debug_dqb0l_txbst_pu_d1_6_0    mc_io_debug_dqb0l_txbst_pu_d1;
	union mc_io_debug_dbi_ofscal_d0_6_0        mc_io_debug_dbi_ofscal_d0;
	union mc_io_debug_edc_ofscal_d0_6_0        mc_io_debug_edc_ofscal_d0;
	union mc_io_debug_wck_ofscal_d0_6_0        mc_io_debug_wck_ofscal_d0;
	union mc_io_debug_edc_cdr_phsize_d0_6_0    mc_io_debug_edc_cdr_phsize_d0;
	union mc_io_debug_acmd_ofscal_d0_6_0       mc_io_debug_acmd_ofscal_d0;
	union mc_io_debug_dbi_cdr_phsize_d0_6_0    mc_io_debug_dbi_cdr_phsize_d0;
	union mc_io_debug_dbi_rx_eq_d0_6_0         mc_io_debug_dbi_rx_eq_d0;
	union mc_io_debug_edc_rx_eq_d0_6_0         mc_io_debug_edc_rx_eq_d0;
	union mc_io_cdrcntl_d0_6_0                 mc_io_cdrcntl_d0;
	union mc_io_cdrcntl1_d0_6_0                mc_io_cdrcntl1_d0;
	union mc_io_debug_dqb0l_rx_vref_cal_d0_6_0 mc_io_debug_dqb0l_rx_vref_cal_d0;
	union mc_io_debug_dqb0l_rx_vref_cal_d1_6_0 mc_io_debug_dqb0l_rx_vref_cal_d1;
};

struct mem_adjust_set_gcn3_gddr5 { // 96 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_io_rxcntl_dphy0_d0_6_0    mc_io_rxcntl_dphy0_d0;
	union mc_io_rxcntl1_dphy0_d0_7_1   mc_io_rxcntl1_dphy0_d0;
	union mc_io_aphy_str_cntl_d0_6_0_o mc_io_aphy_str_cntl_d0;
	union mc_tsm_debug_bcnt2_6_0  mc_tsm_debug_bcnt2;
	union mc_seq_reserve_1_s_6_0  mc_seq_reserve_1_s;
	union mc_seq_misc5_6_0  mc_seq_misc5;
	union mc_seq_misc4_6_0  mc_seq_misc4;
	union mc_seq_misc6_6_0  mc_seq_misc6;
	union mc_seq_misc7_6_0  mc_seq_misc7;
	union mc_seq_misc9_6_0  mc_seq_misc9;
	union mc_io_debug_addrl_txphase_d0_6_0 mc_io_debug_addrl_txphase_d0;
	union mc_io_debug_acmd_txphase_d0_6_0  mc_io_debug_acmd_txphase_d0;
	union mc_io_debug_cmd_txphase_d0_6_0   mc_io_debug_cmd_txphase_d0;
	union mc_io_debug_ck_txphase_d0_6_0    mc_io_debug_ck_txphase_d0;
	union mc_io_debug_dqb0l_clksel_d0_6_0  mc_io_debug_dqb0l_clksel_d0;
	union mc_io_debug_dqb0l_clksel_d1_6_0  mc_io_debug_dqb0l_clksel_d1;
	union mc_io_debug_wck_clksel_d0_6_0    mc_io_debug_wck_clksel_d0;
	union mc_io_debug_dqb0l_txphase_d0_6_0 mc_io_debug_dqb0l_txphase_d0;
	union mc_io_debug_dqb0l_txphase_d1_6_0 mc_io_debug_dqb0l_txphase_d1;
	union mc_io_debug_wck_txphase_d0_6_0   mc_io_debug_wck_txphase_d0;
	union mc_seq_txframing_byte0_d0_6_0    mc_seq_txframing_byte0_d0;
	union mc_seq_txframing_byte0_d1_6_0    mc_seq_txframing_byte0_d1;
	union mc_io_debug_edc_rxphase_d0_6_0   mc_io_debug_edc_rxphase_d0;
};

struct mem_adjust_set_gcn3_hbm1 { // 8 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_rxframing_dbi_d1_6_0_o  mc_seq_rxframing_dbi_d1;
};

struct mem_adjust_set_gcn4_gddr5_type1 { // 24 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_misc4_6_0  mc_seq_misc4;
	union mc_seq_misc5_6_0  mc_seq_misc5;
	union mc_io_pad_cntl_d1_6_0  mc_io_pad_cntl_d1;
	union mc_tsm_debug_flag_6_0  mc_tsm_debug_flag;
	union mc_io_aphy_str_cntl_d0_6_0_o mc_io_aphy_str_cntl_d0;
};

struct mem_adjust_set_gcn4_gddr5_type2 { // 44 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_misc0_6_0  mc_seq_misc0;
	union mc_seq_misc4_6_0  mc_seq_misc4;
	union mc_seq_misc5_6_0  mc_seq_misc5;
	union mc_seq_misc6_6_0  mc_seq_misc6;
	union mc_seq_reserve_m_6_0    mc_seq_reserve_m;
	union mc_tsm_debug_flag_6_0   mc_tsm_debug_flag;
	union mc_tsm_debug_bcnt0_6_0  mc_tsm_debug_bcnt0;
	union mc_io_debug_up_15_6_0   mc_io_debug_up_15;
	union mc_io_dphy_str_cntl_d0_7_1   mc_io_dphy_str_cntl_d0;
	union mc_io_aphy_str_cntl_d0_6_0_o mc_io_aphy_str_cntl_d0;
};


/******************************************************************************/
// mc_tile_adjust table
// uncertain the accuracy of all of these tables.
/******************************************************************************/

struct mc_tile_adjust_set_gcn3_gddr5 { // 12 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_tsm_debug_flag_6_0  mc_tsm_debug_flag;
	union mc_tsm_debug_bcnt6_6_0 mc_tsm_debug_bcnt6;
};

struct mc_tile_adjust_set_gcn4_gddr5 { // 8 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_io_debug_up_14_6_0  mc_io_debug_up_14;
};


/******************************************************************************/
// mc_phy_init table
// uncertain the accuracy of all of these tables.
/******************************************************************************/

struct mc_phy_init_set_gcn3_hbm1 { // 56 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_io_pad_cntl_6_0     mc_io_pad_cntl;
	union mc_io_pad_cntl_d0_6_0  mc_io_pad_cntl_d0;
	union mc_seq_perf_seq_cnt_a_i0_6_0 mc_seq_perf_seq_cnt_a_i0;
	union mc_fus_dram0_cs1_base_7_0    mc_fus_dram0_cs1_base;
	union mc_fus_dram1_cs1_base_7_0    mc_fus_dram1_cs1_base;
	union mc_tsm_debug_gcnt_6_0  mc_tsm_debug_gcnt;
	union mc_tsm_debug_flag_6_0  mc_tsm_debug_flag;
	union mc_tsm_debug_misc_6_0  mc_tsm_debug_misc;
	union mc_tsm_debug_bcnt0_6_0 mc_tsm_debug_bcnt0;
	union mc_tsm_debug_bcnt1_6_0 mc_tsm_debug_bcnt1;
	union mc_tsm_debug_bcnt2_6_0 mc_tsm_debug_bcnt2;
	union mc_tsm_debug_bcnt3_6_0 mc_tsm_debug_bcnt3;
	union mc_tsm_debug_bcnt4_6_0 mc_tsm_debug_bcnt4;
};

struct mc_phy_init_set_gcn3_gddr5 { // 384 bytes
	union atom_mc_register_setting_id  block_id;
	union mpll_seq_ucode_1_6_0  mpll_seq_ucode_1;
	union mpll_seq_ucode_2_6_0  mpll_seq_ucode_2;
	union mc_seq_dram_7_1       mc_seq_dram;
	union mc_seq_dram_2_6_0     mc_seq_dram_2;
	union mc_seq_fifo_ctl_7_1   mc_seq_fifo_ctl;
	union mc_io_pad_cntl_6_0    mc_io_pad_cntl;
	union mc_seq_wr_ctl_d0_6_0  mc_seq_wr_ctl_d0;
	union mc_seq_wr_ctl_d1_6_0  mc_seq_wr_ctl_d1;
	union mc_seq_train_wakeup_mask_7_1     mc_seq_train_wakeup_mask;
	union mc_seq_pmg_dvs_ctl_7_1           mc_seq_pmg_dvs_ctl;
	union mc_seq_pmg_pg_hwcntl_6_0         mc_seq_pmg_pg_hwcntl;
	union mc_seq_train_wakeup_cntl_6_0     mc_seq_train_wakeup_cntl;
	union mc_seq_train_edc_threshold_6_0   mc_seq_train_edc_threshold;
	union mc_seq_train_wakeup_edge_7_1     mc_seq_train_wakeup_edge;
	union mc_seq_train_wakeup_clear_7_1    mc_seq_train_wakeup_clear;
	union mc_seq_train_timing_6_0          mc_seq_train_timing;
	union mc_seq_perf_cntl_6_0             mc_seq_perf_cntl;
	union mc_seq_cntl_2_7_1                mc_seq_cntl_2;
	union mc_seq_cntl_3_7_1                mc_seq_cntl_3;
	union mc_seq_perf_seq_ctl_6_0          mc_seq_perf_seq_ctl;
	union mc_imp_cntl_6_0                  mc_imp_cntl;
	union mc_seq_dll_stby_7_1              mc_seq_dll_stby;
	union mc_seq_g5pdx_cmd0_7_1            mc_seq_g5pdx_cmd0;
	union mc_seq_g5pdx_cmd1_7_1            mc_seq_g5pdx_cmd1;
	union mc_seq_g5pdx_ctrl_7_1            mc_seq_g5pdx_ctrl__0;
	union mc_io_debug_up_159_6_0           mc_io_debug_up_159;
	union mc_seq_txframing_byte0_d0_6_0    mc_seq_txframing_byte0_d0;
	union mc_io_debug_ck_clksel_d0_6_0     mc_io_debug_ck_clksel_d0;
	union mc_io_debug_ck_clksel_d1_6_0     mc_io_debug_ck_clksel_d1;
	union mc_io_debug_dq0_rx_eq_pm_d0_6_0  mc_io_debug_dq0_rx_eq_pm_d0;
	union mc_io_debug_dq0_rx_dyn_pm_d0_6_0 mc_io_debug_dq0_rx_dyn_pm_d0;
	union mc_io_debug_edc_rx_eq_pm_d0_6_0  mc_io_debug_edc_rx_eq_pm_d0;
	union mc_phy_timing_d0_6_0       mc_phy_timing_d0;
	union mc_seq_io_reserve_d0_6_0   mc_seq_io_reserve_d0;
	union mc_io_txcntl_dphy0_d0_6_0  mc_io_txcntl_dphy0_d0;
	union mc_io_txcntl_aphy_d0_6_0   mc_io_txcntl_aphy_d0;
	union mc_io_dphy_str_cntl_d0_7_1 mc_io_dphy_str_cntl_d0;
	union mc_pmg_cfg_6_0             mc_pmg_cfg;
	union mc_pmg_auto_cfg_6_0        mc_pmg_auto_cfg;
	union mc_seq_rd_ctl_d0_6_0       mc_seq_rd_ctl_d0;
	union mc_io_pad_cntl_d0_6_0      mc_io_pad_cntl_d0;
	union mc_io_pad_cntl_d1_6_0      mc_io_pad_cntl_d1;
	union mc_tsm_debug_gcnt_6_0      mc_tsm_debug_gcnt;
	union mc_tsm_debug_misc_6_0      mc_tsm_debug_misc;
	union mc_tsm_debug_bcnt0_6_0     mc_tsm_debug_bcnt0;
	union mc_tsm_debug_bcnt1_6_0     mc_tsm_debug_bcnt1;
	union mc_tsm_debug_bcnt7_6_0     mc_tsm_debug_bcnt7;
	union mc_tsm_debug_bcnt8_6_0     mc_tsm_debug_bcnt8;
	union mc_tsm_debug_bcnt9_6_0     mc_tsm_debug_bcnt9;
	union mc_tsm_debug_bcnt10_6_0    mc_tsm_debug_bcnt10;
	union mc_io_debug_up_14_6_0      mc_io_debug_up_14;
	union mc_io_debug_up_15_6_0      mc_io_debug_up_15;
	union mc_arb_rtt_cntl0_6_0       mc_arb_rtt_cntl0;
	union mc_arb_rtt_cntl1_6_0       mc_arb_rtt_cntl1;
	union mc_arb_rtt_cntl2_6_0       mc_arb_rtt_cntl2;
	union mc_seq_g5pdx_ctrl_7_1      mc_seq_g5pdx_ctrl__1;
	union mc_io_debug_dqb0l_ofscal_d0_6_0      mc_io_debug_dqb0l_ofscal_d0;
	union mc_io_debug_dqb0l_ofscal_d1_6_0      mc_io_debug_dqb0l_ofscal_d1;
	union mc_io_debug_cmd_ofscal_d0_6_0        mc_io_debug_cmd_ofscal_d0;
	union mc_io_debug_dqb0_cdr_phsize_d0_6_0   mc_io_debug_dqb0_cdr_phsize_d0;
	union mc_io_debug_dqb0_cdr_phsize_d1_6_0   mc_io_debug_dqb0_cdr_phsize_d1;
	union mc_io_debug_dqb0l_rx_eq_d0_6_0       mc_io_debug_dqb0l_rx_eq_d0;
	union mc_io_debug_dqb0l_rx_eq_d1_6_0       mc_io_debug_dqb0l_rx_eq_d1;
	union mc_io_debug_wck_rx_eq_d0_6_0         mc_io_debug_wck_rx_eq_d0;
	union mc_io_debug_wcdr_ofscal_d0_6_0       mc_io_debug_wcdr_ofscal_d0;
	union mc_io_debug_wcdr_rx_vref_cal_d0_6_0  mc_io_debug_wcdr_rx_vref_cal_d0;
	union mc_io_debug_wcdr_rx_eq_d0_6_0        mc_io_debug_wcdr_rx_eq_d0;
	union mc_io_debug_wcdr_cdr_phsize_d0_6_0   mc_io_debug_wcdr_cdr_phsize_d0;
	union mc_io_debug_dbi_txbst_pd_d0_6_0      mc_io_debug_dbi_txbst_pd_d0;
	union mc_io_debug_dbi_txbst_pu_d0_6_0      mc_io_debug_dbi_txbst_pu_d0;
	union mc_io_debug_edc_txbst_pd_d0_6_0      mc_io_debug_edc_txbst_pd_d0;
	union mc_io_debug_edc_txbst_pu_d0_6_0      mc_io_debug_edc_txbst_pu_d0;
	union mc_io_debug_wcdr_txbst_pd_d0_6_0     mc_io_debug_wcdr_txbst_pd_d0;
	union mc_io_debug_wcdr_txbst_pu_d0_6_0     mc_io_debug_wcdr_txbst_pu_d0;
	union mc_io_debug_dqb0l_txbst_pd_d0_6_0    mc_io_debug_dqb0l_txbst_pd_d0;
	union mc_io_debug_dqb0l_txbst_pd_d1_6_0    mc_io_debug_dqb0l_txbst_pd_d1;
	union mc_io_debug_dqb0l_txbst_pu_d0_6_0    mc_io_debug_dqb0l_txbst_pu_d0;
	union mc_io_debug_dqb0l_txbst_pu_d1_6_0    mc_io_debug_dqb0l_txbst_pu_d1;
	union mc_io_debug_acmd_txbst_pd_d0_6_0     mc_io_debug_acmd_txbst_pd_d0;
	union mc_io_debug_addrh_txbst_pd_d0_6_0    mc_io_debug_addrh_txbst_pd_d0;
	union mc_io_debug_addrl_txbst_pd_d0_6_0    mc_io_debug_addrl_txbst_pd_d0;
	union mc_io_debug_ck_txbst_pd_d0_6_0       mc_io_debug_ck_txbst_pd_d0;
	union mc_io_debug_cmd_txbst_pd_d0_6_0      mc_io_debug_cmd_txbst_pd_d0;
	union mc_io_debug_dbi_ofscal_d0_6_0        mc_io_debug_dbi_ofscal_d0;
	union mc_io_debug_edc_ofscal_d0_6_0        mc_io_debug_edc_ofscal_d0;
	union mc_io_debug_wck_ofscal_d0_6_0        mc_io_debug_wck_ofscal_d0;
	union mc_io_debug_edc_cdr_phsize_d0_6_0    mc_io_debug_edc_cdr_phsize_d0;
	union mc_io_debug_acmd_ofscal_d0_6_0       mc_io_debug_acmd_ofscal_d0;
	union mc_io_debug_dbi_cdr_phsize_d0_6_0    mc_io_debug_dbi_cdr_phsize_d0;
	union mc_io_debug_dbi_rx_eq_d0_6_0         mc_io_debug_dbi_rx_eq_d0;
	union mc_io_debug_edc_rx_eq_d0_6_0         mc_io_debug_edc_rx_eq_d0;
	union mc_io_cdrcntl_d0_6_0                 mc_io_cdrcntl_d0;
	union mc_io_cdrcntl1_d0_6_0                mc_io_cdrcntl1_d0;
	union mc_io_debug_dqb0l_rx_vref_cal_d0_6_0 mc_io_debug_dqb0l_rx_vref_cal_d0;
	union mc_io_debug_dqb0l_rx_vref_cal_d1_6_0 mc_io_debug_dqb0l_rx_vref_cal_d1;
};

struct mc_phy_init_set_gcn4_gddr5_type1 { // 92 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_misc0_6_0  mc_seq_misc0;
	union mc_seq_misc4_6_0  mc_seq_misc4;
	union mc_seq_misc5_6_0  mc_seq_misc5;
	union mc_seq_misc6_6_0  mc_seq_misc6;
	union mc_seq_misc7_6_0  mc_seq_misc7;
	union mc_seq_reserve_m_6_0    mc_seq_reserve_m;
	union mc_io_pad_cntl_d0_6_0   mc_io_pad_cntl_d0;
	union mc_io_pad_cntl_d1_6_0   mc_io_pad_cntl_d1;
	union mc_tsm_debug_gcnt_6_0   mc_tsm_debug_gcnt;
	union mc_tsm_debug_flag_6_0   mc_tsm_debug_flag;
	union mc_tsm_debug_misc_6_0   mc_tsm_debug_misc;
	union mc_tsm_debug_bcnt0_6_0  mc_tsm_debug_bcnt0;
	union mc_tsm_debug_bcnt1_6_0  mc_tsm_debug_bcnt1;
	union mc_tsm_debug_bcnt2_6_0  mc_tsm_debug_bcnt2;
	union mc_tsm_debug_bcnt6_6_0  mc_tsm_debug_bcnt6;
	union mc_tsm_debug_bcnt7_6_0  mc_tsm_debug_bcnt7;
	union mc_tsm_debug_bcnt8_6_0  mc_tsm_debug_bcnt8;
	union mc_tsm_debug_bcnt9_6_0  mc_tsm_debug_bcnt9;
	union mc_tsm_debug_bcnt10_6_0 mc_tsm_debug_bcnt10;
	union mc_io_debug_up_15_6_0   mc_io_debug_up_15;
	union mc_io_dphy_str_cntl_d0_7_1   mc_io_dphy_str_cntl_d0;
	union mc_io_aphy_str_cntl_d0_6_0_o mc_io_aphy_str_cntl_d0;
};

struct mc_phy_init_set_gcn4_gddr5_type2 { // 72 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_misc0_6_0  mc_seq_misc0;
	union mc_seq_misc6_6_0  mc_seq_misc6;
	union mc_seq_misc7_6_0  mc_seq_misc7;
	union mc_seq_reserve_m_6_0    mc_seq_reserve_m;
	union mc_io_pad_cntl_d0_6_0   mc_io_pad_cntl_d0;
	union mc_tsm_debug_gcnt_6_0   mc_tsm_debug_gcnt;
	union mc_tsm_debug_misc_6_0   mc_tsm_debug_misc;
	union mc_tsm_debug_bcnt0_6_0  mc_tsm_debug_bcnt0;
	union mc_tsm_debug_bcnt1_6_0  mc_tsm_debug_bcnt1;
	union mc_tsm_debug_bcnt2_6_0  mc_tsm_debug_bcnt2;
	union mc_tsm_debug_bcnt6_6_0  mc_tsm_debug_bcnt6;
	union mc_tsm_debug_bcnt7_6_0  mc_tsm_debug_bcnt7;
	union mc_tsm_debug_bcnt8_6_0  mc_tsm_debug_bcnt8;
	union mc_tsm_debug_bcnt9_6_0  mc_tsm_debug_bcnt9;
	union mc_tsm_debug_bcnt10_6_0 mc_tsm_debug_bcnt10;
	union mc_io_debug_up_15_6_0   mc_io_debug_up_15;
	union mc_io_dphy_str_cntl_d0_7_1  mc_io_dphy_str_cntl_d0;
};

struct mc_phy_init_set_gcn4_gddr5_type3 { // 52 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_misc7_6_0        mc_seq_misc7;
	union mc_io_pad_cntl_d0_6_0   mc_io_pad_cntl_d0;
	union mc_io_pad_cntl_d1_6_0   mc_io_pad_cntl_d1;
	union mc_tsm_debug_gcnt_6_0   mc_tsm_debug_gcnt;
	union mc_tsm_debug_misc_6_0   mc_tsm_debug_misc;
	union mc_tsm_debug_bcnt1_6_0  mc_tsm_debug_bcnt1;
	union mc_tsm_debug_bcnt2_6_0  mc_tsm_debug_bcnt2;
	union mc_tsm_debug_bcnt6_6_0  mc_tsm_debug_bcnt6;
	union mc_tsm_debug_bcnt7_6_0  mc_tsm_debug_bcnt7;
	union mc_tsm_debug_bcnt8_6_0  mc_tsm_debug_bcnt8;
	union mc_tsm_debug_bcnt9_6_0  mc_tsm_debug_bcnt9;
	union mc_tsm_debug_bcnt10_6_0 mc_tsm_debug_bcnt10;
};


/******************************************************************************/
/******************************************************************************/
// GC
// see gc.h
/******************************************************************************/
/******************************************************************************/

#pragma pack(pop) // restore old packing

#endif
