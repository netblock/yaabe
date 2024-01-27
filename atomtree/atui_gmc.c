/*
For gmc.h
See atui_atomfirmware.c for how to use PPATUI_FUNCIFY()
*/

#include "atomtree.h"
#include "atui.h"

PPATUI_FUNCIFY(union, mc_arb_dram_timing_6_0, atui_nullstruct, // 6_0, 7_0, 7_1, 8_1, 8_2
	(bios->raw_data, u8"mc_arb_dram_timing",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"actrd",      7,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"actwr",     15,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rasmactrd", 23,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rasmactwr", 31,24, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mc_arb_dram_timing2_6_0, atui_nullstruct, // 6_0, 7_0, 7_1, 8_1, 8_2
	(bios->raw_data, u8"mc_arb_dram_timing2",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"ras2ras",   7,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rp",       15,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"wrplusrp", 23,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"bus_turn", 28,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd00",  31,29, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mc_seq_cas_timing_6_0, atui_nullstruct, // 6_0, 7_1, 8_1
	(bios->raw_data, u8"mc_seq_cas_timing",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tnopw",    1,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tnopr",    3,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tr2w",     8,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tccdl",   11,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tr2r",    15,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tw2r",    20,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd00", 23,21, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tcl",     28,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd01", 31,29, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mc_seq_misc_timing_6_0, atui_nullstruct, // 6_0, 7_1, 8_1
	(bios->raw_data, u8"mc_seq_misc_timing",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"trp_wra",  5,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd00",  7,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"trp_rda", 13,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd01", 14,14, ATUI_DEC, (ATUI_NODESCR)),
			(u8"trp",     19,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"trfc",    28,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd02", 31,29, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mc_seq_misc_timing2_6_0, atui_nullstruct, // 6_0, 7_1, 8_1
	(bios->raw_data, u8"mc_seq_misc_timing2",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"pa2rdata",  2,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd00",   3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"pa2wdata",  6,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd01",   7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"faw",      12,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tredc",    15,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"twedc",    20,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"t32aw",    24,21, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd02",  27,25, ATUI_DEC, (ATUI_NODESCR)),
			(u8"twdatatr", 31,28, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mc_seq_pmg_timing_6_0, atui_nullstruct, // 6_0, 7_1, 8_1
	(bios->raw_data, u8"mc_seq_pmg_timing",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tcksre",          2,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd00",         3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tcksrx",          6,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd01",         7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tcke_pulse",     11,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tcke",           17,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"seq_idle",       20,18, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd02",        22,21, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tcke_pulse_msb", 23,23, ATUI_DEC, (ATUI_NODESCR)),
			(u8"seq_idle_ss",    31,24, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mc_seq_ras_timing_6_0, atui_nullstruct, // 6_0, 7_1, 8_1
	(bios->raw_data, u8"mc_seq_ras_timing",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"trcdw",    4,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"trcdwa",   9,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"trcdr",   14,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"trcdra",  19,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"trrd",    23,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"trc",     30,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd00", 31,31, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
) 


PPATUI_FUNCIFY(union, mc_seq_wr_ctl_2_6_0, atui_nullstruct, // 6_0, 7_1, 8_1
	(bios->raw_data, u8"mc_seq_wr_ctl_2",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"dat_dly_h_d0", 0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"dqs_dly_h_d0", 1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"oen_dly_h_d0", 2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"dat_dly_h_d1", 3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"dqs_dly_h_d1", 4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"oen_dly_h_d1", 5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"wcdr_en",      6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd00",     31,7, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mc_seq_wr_ctl_d0_6_0, atui_nullstruct, // 6_0, 7_1, 8_1
	(bios->raw_data, u8"mc_seq_wr_ctl_d0",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"dat_dly",     3,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"dqs_dly",     7,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"dqs_xtr",     8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"dat_2y_dly",  9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"adr_2y_dly", 10,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"cmd_2y_dly", 11,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"oen_dly",    15,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"oen_ext",    19,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"oen_sel",    21,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd00",    23,22, ATUI_DEC, (ATUI_NODESCR)),
			(u8"odt_dly",    27,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"odt_ext",    28,28, ATUI_DEC, (ATUI_NODESCR)),
			(u8"adr_dly",    29,29, ATUI_DEC, (ATUI_NODESCR)),
			(u8"cmd_dly",    30,30, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd01",    31,31, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mc_shared_chremap_6_0, atui_nullstruct, // 6_0, 7_0
	(bios->raw_data, u8"mc_shared_chremap",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"chan0",    2,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan1",    5,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan2",    8,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan3",   11,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan4",   14,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan5",   17,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan6",   20,18, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan7",   23,21, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd00", 31,24, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, mc_shared_chremap_7_1, atui_nullstruct, // 7_1, 8_1, 8_2
	(bios->raw_data, u8"mc_shared_chremap",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"chan0",  3,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan1",  7,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan2", 11,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan3", 15,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan4", 19,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan5", 23,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan6", 27,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan7", 31,28, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, mc_shared_chremap2_7_1, atui_nullstruct, // 7_1, 8_1, 8_2
	(bios->raw_data, u8"raw_data",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"chan8",   3,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan9",   7,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan10", 11,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan11", 15,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan12", 19,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan13", 23,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan14", 27,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan15", 31,28, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
