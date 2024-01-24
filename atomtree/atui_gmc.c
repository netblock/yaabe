/*
For gmc.h
See atui_atomfirmware.c for how to use PPATUI_FUNCIFY()
*/

#include "atomtree.h"
#include "atui.h"

PPATUI_FUNCIFY(union, mc_arb_dram_timing_6_0, atui_nullstruct, // 6_0, 7_0, 7_1, 8_1, 8_2
	(bios->raw_data, "mc_arb_dram_timing",
		(ATUI_BIN, ATUI_BITFIELD, (
			("actrd",      7,0, ATUI_DEC, (ATUI_NODESCR)),
			("actwr",     15,8, ATUI_DEC, (ATUI_NODESCR)),
			("rasmactrd", 23,16, ATUI_DEC, (ATUI_NODESCR)),
			("rasmactwr", 31,24, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mc_arb_dram_timing2_6_0, atui_nullstruct, // 6_0, 7_0, 7_1, 8_1, 8_2
	(bios->raw_data, "mc_arb_dram_timing2",
		(ATUI_BIN, ATUI_BITFIELD, (
			("ras2ras",   7,0, ATUI_DEC, (ATUI_NODESCR)),
			("rp",       15,8, ATUI_DEC, (ATUI_NODESCR)),
			("wrplusrp", 23,16, ATUI_DEC, (ATUI_NODESCR)),
			("bus_turn", 28,24, ATUI_DEC, (ATUI_NODESCR)),
			("_rsvd00",  31,29, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mc_seq_cas_timing_6_0, atui_nullstruct, // 6_0, 7_1, 8_1
	(bios->raw_data, "mc_seq_cas_timing",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tnopw",    1,0, ATUI_DEC, (ATUI_NODESCR)),
			("tnopr",    3,2, ATUI_DEC, (ATUI_NODESCR)),
			("tr2w",     8,4, ATUI_DEC, (ATUI_NODESCR)),
			("tccdl",   11,9, ATUI_DEC, (ATUI_NODESCR)),
			("tr2r",    15,12, ATUI_DEC, (ATUI_NODESCR)),
			("tw2r",    20,16, ATUI_DEC, (ATUI_NODESCR)),
			("_rsvd00", 23,21, ATUI_DEC, (ATUI_NODESCR)),
			("tcl",     28,24, ATUI_DEC, (ATUI_NODESCR)),
			("_rsvd01", 31,29, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mc_seq_misc_timing_6_0, atui_nullstruct, // 6_0, 7_1, 8_1
	(bios->raw_data, "mc_seq_misc_timing",
		(ATUI_BIN, ATUI_BITFIELD, (
			("trp_wra",  5,0, ATUI_DEC, (ATUI_NODESCR)),
			("_rsvd00",  7,6, ATUI_DEC, (ATUI_NODESCR)),
			("trp_rda", 13,8, ATUI_DEC, (ATUI_NODESCR)),
			("_rsvd01", 14,14, ATUI_DEC, (ATUI_NODESCR)),
			("trp",     19,15, ATUI_DEC, (ATUI_NODESCR)),
			("trfc",    28,20, ATUI_DEC, (ATUI_NODESCR)),
			("_rsvd02", 31,29, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mc_seq_misc_timing2_6_0, atui_nullstruct, // 6_0, 7_1, 8_1
	(bios->raw_data, "mc_seq_misc_timing2",
		(ATUI_BIN, ATUI_BITFIELD, (
			("pa2rdata",  2,0, ATUI_DEC, (ATUI_NODESCR)),
			("_rsvd00",   3,3, ATUI_DEC, (ATUI_NODESCR)),
			("pa2wdata",  6,4, ATUI_DEC, (ATUI_NODESCR)),
			("_rsvd01",   7,7, ATUI_DEC, (ATUI_NODESCR)),
			("faw",      12,8, ATUI_DEC, (ATUI_NODESCR)),
			("tredc",    15,13, ATUI_DEC, (ATUI_NODESCR)),
			("twedc",    20,16, ATUI_DEC, (ATUI_NODESCR)),
			("t32aw",    24,21, ATUI_DEC, (ATUI_NODESCR)),
			("_rsvd02",  27,25, ATUI_DEC, (ATUI_NODESCR)),
			("twdatatr", 31,28, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mc_seq_pmg_timing_6_0, atui_nullstruct, // 6_0, 7_1, 8_1
	(bios->raw_data, "mc_seq_pmg_timing",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tcksre",          2,0, ATUI_DEC, (ATUI_NODESCR)),
			("_rsvd00",         3,3, ATUI_DEC, (ATUI_NODESCR)),
			("tcksrx",          6,4, ATUI_DEC, (ATUI_NODESCR)),
			("_rsvd01",         7,7, ATUI_DEC, (ATUI_NODESCR)),
			("tcke_pulse",     11,8, ATUI_DEC, (ATUI_NODESCR)),
			("tcke",           17,12, ATUI_DEC, (ATUI_NODESCR)),
			("seq_idle",       20,18, ATUI_DEC, (ATUI_NODESCR)),
			("_rsvd02",        22,21, ATUI_DEC, (ATUI_NODESCR)),
			("tcke_pulse_msb", 23,23, ATUI_DEC, (ATUI_NODESCR)),
			("seq_idle_ss",    31,24, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mc_seq_ras_timing_6_0, atui_nullstruct, // 6_0, 7_1, 8_1
	(bios->raw_data, "mc_seq_ras_timing",
		(ATUI_BIN, ATUI_BITFIELD, (
			("trcdw",    4,0, ATUI_DEC, (ATUI_NODESCR)),
			("trcdwa",   9,5, ATUI_DEC, (ATUI_NODESCR)),
			("trcdr",   14,10, ATUI_DEC, (ATUI_NODESCR)),
			("trcdra",  19,15, ATUI_DEC, (ATUI_NODESCR)),
			("trrd",    23,20, ATUI_DEC, (ATUI_NODESCR)),
			("trc",     30,24, ATUI_DEC, (ATUI_NODESCR)),
			("_rsvd00", 31,31, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
) 


PPATUI_FUNCIFY(union, mc_seq_wr_ctl_2_6_0, atui_nullstruct, // 6_0, 7_1, 8_1
	(bios->raw_data, "mc_seq_wr_ctl_2",
		(ATUI_BIN, ATUI_BITFIELD, (
			("dat_dly_h_d0", 0,0, ATUI_DEC, (ATUI_NODESCR)),
			("dqs_dly_h_d0", 1,1, ATUI_DEC, (ATUI_NODESCR)),
			("oen_dly_h_d0", 2,2, ATUI_DEC, (ATUI_NODESCR)),
			("dat_dly_h_d1", 3,3, ATUI_DEC, (ATUI_NODESCR)),
			("dqs_dly_h_d1", 4,4, ATUI_DEC, (ATUI_NODESCR)),
			("oen_dly_h_d1", 5,5, ATUI_DEC, (ATUI_NODESCR)),
			("wcdr_en",      6,6, ATUI_DEC, (ATUI_NODESCR)),
			("_rsvd00",     31,7, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mc_seq_wr_ctl_d0_6_0, atui_nullstruct, // 6_0, 7_1, 8_1
	(bios->raw_data, "mc_seq_wr_ctl_d0",
		(ATUI_BIN, ATUI_BITFIELD, (
			("dat_dly",     3,0, ATUI_DEC, (ATUI_NODESCR)),
			("dqs_dly",     7,4, ATUI_DEC, (ATUI_NODESCR)),
			("dqs_xtr",     8,8, ATUI_DEC, (ATUI_NODESCR)),
			("dat_2y_dly",  9,9, ATUI_DEC, (ATUI_NODESCR)),
			("adr_2y_dly", 10,10, ATUI_DEC, (ATUI_NODESCR)),
			("cmd_2y_dly", 11,11, ATUI_DEC, (ATUI_NODESCR)),
			("oen_dly",    15,12, ATUI_DEC, (ATUI_NODESCR)),
			("oen_ext",    19,16, ATUI_DEC, (ATUI_NODESCR)),
			("oen_sel",    21,20, ATUI_DEC, (ATUI_NODESCR)),
			("_rsvd00",    23,22, ATUI_DEC, (ATUI_NODESCR)),
			("odt_dly",    27,24, ATUI_DEC, (ATUI_NODESCR)),
			("odt_ext",    28,28, ATUI_DEC, (ATUI_NODESCR)),
			("adr_dly",    29,29, ATUI_DEC, (ATUI_NODESCR)),
			("cmd_dly",    30,30, ATUI_DEC, (ATUI_NODESCR)),
			("_rsvd01",    31,31, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mc_shared_chremap_6_0, atui_nullstruct, // 6_0, 7_0
	(bios->raw_data, "mc_shared_chremap",
		(ATUI_BIN, ATUI_BITFIELD, (
			("chan0",    2,0, ATUI_DEC, (ATUI_NODESCR)),
			("chan1",    5,3, ATUI_DEC, (ATUI_NODESCR)),
			("chan2",    8,6, ATUI_DEC, (ATUI_NODESCR)),
			("chan3",   11,9, ATUI_DEC, (ATUI_NODESCR)),
			("chan4",   14,12, ATUI_DEC, (ATUI_NODESCR)),
			("chan5",   17,15, ATUI_DEC, (ATUI_NODESCR)),
			("chan6",   20,18, ATUI_DEC, (ATUI_NODESCR)),
			("chan7",   23,21, ATUI_DEC, (ATUI_NODESCR)),
			("_rsvd00", 31,24, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, mc_shared_chremap_7_1, atui_nullstruct, // 7_1, 8_1, 8_2
	(bios->raw_data, "mc_shared_chremap",
		(ATUI_BIN, ATUI_BITFIELD, (
			("chan0",  3,0, ATUI_DEC, (ATUI_NODESCR)),
			("chan1",  7,4, ATUI_DEC, (ATUI_NODESCR)),
			("chan2", 11,8, ATUI_DEC, (ATUI_NODESCR)),
			("chan3", 15,12, ATUI_DEC, (ATUI_NODESCR)),
			("chan4", 19,16, ATUI_DEC, (ATUI_NODESCR)),
			("chan5", 23,20, ATUI_DEC, (ATUI_NODESCR)),
			("chan6", 27,24, ATUI_DEC, (ATUI_NODESCR)),
			("chan7", 31,28, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, mc_shared_chremap2_7_1, atui_nullstruct, // 7_1, 8_1, 8_2
	(bios->raw_data, "raw_data",
		(ATUI_BIN, ATUI_BITFIELD, (
			("chan8",   3,0, ATUI_DEC, (ATUI_NODESCR)),
			("chan9",   7,4, ATUI_DEC, (ATUI_NODESCR)),
			("chan10", 11,8, ATUI_DEC, (ATUI_NODESCR)),
			("chan11", 15,12, ATUI_DEC, (ATUI_NODESCR)),
			("chan12", 19,16, ATUI_DEC, (ATUI_NODESCR)),
			("chan13", 23,20, ATUI_DEC, (ATUI_NODESCR)),
			("chan14", 27,24, ATUI_DEC, (ATUI_NODESCR)),
			("chan15", 31,28, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
