/*
Register data block playback of common asic register tables
See also asic_reg_indicies.json5
*/

#ifndef ASIC_REG_DATA_TABLES_H
#define ASIC_REG_DATA_TABLES_H
#pragma pack(push, 1) // bios data must use byte alignment

struct unknown_reg_data {
	uint32_t reg_data;
};

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
	union atom_mc_register_setting_id block_id;
	union mc_seq_cas_timing_6_0_o     mc_seq_cas_timing;
	union mc_seq_misc_timing2_6_0_o   mc_seq_misc_timing2;
	union mc_seq_rd_ctl_d0_6_0        mc_seq_rd_ctl_d0;
	union mc_seq_wr_ctl_d0_6_0        mc_seq_wr_ctl_d0;
	union mc_seq_cmd_6_0_o            mc_seq_cmd;
	union mc_seq_rxframing_edc_d1_6_0 mc_seq_rxframing_edc_d1;
	union mc_arb_dram_timing_6_0      mc_arb_dram_timing;
	union mc_arb_dram_timing2_6_0     mc_arb_dram_timing2;
	union mc_arb_burst_time_8_1       mc_arb_burst_time;
};

struct timings_set_polaris { // 52 bytes.
	union atom_mc_register_setting_id block_id;
	union mc_seq_wr_ctl_d0_6_0        mc_seq_wr_ctl_d0;
	union mc_seq_wr_ctl_2_6_0         mc_seq_wr_ctl_2;
	union mc_seq_pmg_timing_6_0       mc_seq_pmg_timing;
	union mc_seq_ras_timing_6_0       mc_seq_ras_timing;
	union mc_seq_cas_timing_6_0       mc_seq_cas_timing;
	union mc_seq_misc_timing_6_0_o    mc_seq_misc_timing;
	union mc_seq_misc_timing2_6_0     mc_seq_misc_timing2;
	struct mc_seq_misc1_gddr5         mc_seq_misc1;
	struct mc_seq_misc3_gddr5         mc_seq_misc3;
	struct mc_seq_misc8_gddr5         mc_seq_misc8;
	union mc_arb_dram_timing_6_0      mc_arb_dram_timing;
	union mc_arb_dram_timing2_6_0     mc_arb_dram_timing2;
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

struct timings_set_vega20 { // 96 bytes. Uncertain.
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



/******************************************************************************/
// mc_tile_adjust table
// uncertain the accuracy of all of these tables.
/******************************************************************************/


/******************************************************************************/
// mc_phy_init table
// uncertain the accuracy of all of these tables.
/******************************************************************************/



/******************************************************************************/
/******************************************************************************/
// GC
// see gc.h
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
// Di/Dt leakage tables
/******************************************************************************/

struct dpm7_atomctrl_edc_leakge_table {
	union didt_sq_edc_stall_pattern_1_2_9_0  didt_sq_edc_stall_pattern_1_2;
	union didt_sq_edc_stall_pattern_3_4_9_0  didt_sq_edc_stall_pattern_3_4;
	union didt_sq_edc_stall_pattern_5_6_9_0  didt_sq_edc_stall_pattern_5_6;
	union didt_sq_edc_stall_pattern_7_9_0    didt_sq_edc_stall_pattern_7;
	union didt_sq_edc_threshold_9_0          didt_sq_edc_threshold;
	union didt_sq_edc_ctrl_9_0               didt_sq_edc_ctrl;
	union didt_td_edc_stall_pattern_1_2_9_0  didt_td_edc_stall_pattern_1_2;
	union didt_td_edc_stall_pattern_3_4_9_0  didt_td_edc_stall_pattern_3_4;
	union didt_td_edc_stall_pattern_5_6_9_0  didt_td_edc_stall_pattern_5_6;
	union didt_td_edc_stall_pattern_7_9_0    didt_td_edc_stall_pattern_7;
	union didt_td_edc_threshold_9_0          didt_td_edc_threshold;
	union didt_td_edc_ctrl_9_0               didt_td_edc_ctrl;
	union didt_tcp_edc_stall_pattern_1_2_9_0 didt_tcp_edc_stall_pattern_1_2;
	union didt_tcp_edc_stall_pattern_3_4_9_0 didt_tcp_edc_stall_pattern_3_4;
	union didt_tcp_edc_stall_pattern_5_6_9_0 didt_tcp_edc_stall_pattern_5_6;
	union didt_tcp_edc_stall_pattern_7_9_0   didt_tcp_edc_stall_pattern_7;
	union didt_tcp_edc_threshold_9_0         didt_tcp_edc_threshold;
	union didt_tcp_edc_ctrl_9_0              didt_tcp_edc_ctrl;
	union didt_db_edc_stall_pattern_1_2_9_0  didt_db_edc_stall_pattern_1_2;
	union didt_db_edc_stall_pattern_3_4_9_0  didt_db_edc_stall_pattern_3_4;
	union didt_db_edc_stall_pattern_5_6_9_0  didt_db_edc_stall_pattern_5_6;
	union didt_db_edc_stall_pattern_7_9_0    didt_db_edc_stall_pattern_7;
	union didt_db_edc_threshold_9_0          didt_db_edc_threshold;
	union didt_db_edc_ctrl_9_0               didt_db_edc_ctrl;
};


#pragma pack(pop) // restore old packing
#endif
