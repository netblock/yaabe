/*
For umctimings.h
See atui_atomfirmware.c for how to use PPATUI_FUNCIFY()
*/

#include "atomtree.h"
#include "atui.h"

PPATUI_FUNCIFY(union, DRAMTiming1, atui_nullstruct,
	(bios->DRAMTiming1, u8"DRAMTiming1",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tCL",     5,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd0",   7,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tRAS",   14,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd1",  15,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tRCDRD", 21,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd2",  23,22, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tRCDWR", 29,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd3",  31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming2, atui_nullstruct,
	(bios->DRAMTiming2, u8"DRAMTiming2",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tRC_S",  7,0, ATUI_DEC, ((LANG_ENG, u8"per-bank"))),
			(u8"tRC_L", 15,8, ATUI_DEC, ((LANG_ENG, u8"all-bank?"))),
			(u8"tRP_S", 21,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd0", 23,22, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tRP_L", 29,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd1", 31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming3, atui_nullstruct,
	(bios->DRAMTiming3, u8"DRAMTiming3",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tRRD_S",  4,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd0",   7,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tRRD_L", 12,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd1",  23,13, ATUI_DEC,
				((LANG_ENG, u8"3+5+3, middle 5 has tRRDDLR for 3D stacked memory."))
			),
			(u8"tRTP",   28,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd2",  31,29, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming4, atui_nullstruct,
	(bios->DRAMTiming4, u8"DRAMTiming4",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tFAW",   6,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd0",  7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"t32AW", 16,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd1", 31,17, ATUI_DEC,
				((LANG_ENG, u8"1, tFAWSLR:6, 1, tFAWDLR:6, 1")))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming5, atui_nullstruct,
	(bios->DRAMTiming5, u8"DRAMTiming5",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tWL",    5,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd0",  7,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tWTRS", 12,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd1", 15,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tWTRL", 22,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd2", 31,23, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming6, atui_nullstruct,
	(bios->DRAMTiming6, u8"DRAMTiming6",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tWR",    6,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd0", 31,7, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming7, atui_nullstruct,
	(bios->DRAMTiming7, u8"DRAMTiming7",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"PPD",      2,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd0",    3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tCRCRL",   6,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd1",    7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tRREFD",  13,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd2",   14,14, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tCRCWL",  19,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tRCPAGE", 31,20, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming8, atui_nullstruct,
	(bios->DRAMTiming8, u8"DRAMTiming8",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tRDRD_DD",   3,0, ATUI_DEC,
				((LANG_ENG, u8"Different DIMM"))
			),
			(u8"rsvd0",      7,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tRDRD_SD",  11,8, ATUI_DEC,
				((LANG_ENG, u8"Same DIMM"))
			),
			(u8"rsvd1",     15,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tRDRD_SC",  19,16, ATUI_DEC,
				((LANG_ENG, u8"JEDEC tCCD_S"))
			),
			(u8"rsvd2",     23,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tRDRD_SCL", 27,24, ATUI_DEC,
				((LANG_ENG, u8"tCCD_L"))
			),
			(u8"rsvd3",     29,28, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tRDRD_BAN", 31,30, ATUI_DEC,
				((LANG_ENG, u8"Preamble2t ?1:0. Ban traffic:1=tCCD=5;2=tCCD=5,6"))
			)
		)),
		((LANG_ENG, u8"Specifies the minimum number of cycles from the last clock of virtual CAS of the first burst operation to the clock in which CAS is asserted for a following bust operation. A value of 1 means 0 idle clock cycles between two bursts; 2 = 1 idle cycle."))
	)
)


PPATUI_FUNCIFY(union, DRAMTiming9_HBM2, atui_nullstruct,
	(bios->DRAMTiming9, u8"DRAMTiming9",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tWRWR_DD",   3,0, ATUI_DEC,
				((LANG_ENG, u8"Different DIMM"))
			),
			(u8"rsvd0",      7,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tWRWR_SD",  11,8, ATUI_DEC,
				((LANG_ENG, u8"Same DIMM"))
			),
			(u8"rsvd1",     15,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tWRWR_SC",  19,16, ATUI_DEC,
				((LANG_ENG, u8"JEDEC tCCD_S"))
			),
			(u8"rsvd2",     23,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tWRWR_SCL", 27,24, ATUI_DEC,
				((LANG_ENG, u8"tCCD_L"))
			),
			(u8"rsvd3",     29,28, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tWRWR_BAN", 31,30, ATUI_DEC,
				((LANG_ENG, u8"Preamble2t ?1:0. Ban traffic:1=tCCD=5;2=tCCD=5,6"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming9, atui_nullstruct,
	(bios->DRAMTiming9, u8"DRAMTiming9",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tWRWR_MW",   4,0, ATUI_DEC, ((LANG_ENG, u8"masked write; GDDR"))),
			(u8"rsvd0",     15,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tWRWR_SC",  19,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd1",     23,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tWRWR_SCL", 29,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tWRWR_BAN", 31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming10, atui_nullstruct,
	(bios->DRAMTiming10, u8"DRAMTiming10",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tWRRD",       3,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd0",       7,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tRDWR",      13,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd1",      15,14, ATUI_DEC, (ATUI_NODESCR)),
			(u8"RDRspDelay", 21,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tREFTTAdj",  28,22, ATUI_DEC,
				((LANG_ENG, u8"was tREFTT; a typo? tREFTR is a GDDR6 timing"))
			),
			(u8"rsvd2",      31,29, ATUI_DEC, (ATUI_NODESCR))
		)),
		((LANG_ENG, u8"tWRRD and tRDWR also follows the 'last clock of virtual CAS'. LD = tCL - tCWL ; tWRRD has x-LD and tRDWR has y+LD. LD is about making sure one burst happens after the other. And x and y follow the 'last clock of virtual CAS' and are about making sure the data bus is stable."))
	)
)


PPATUI_FUNCIFY(union, DRAMTiming12, atui_nullstruct,
	(bios->DRAMTiming12, u8"DRAMTiming12",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tREFI", 15,0, ATUI_DEC,
				((LANG_ENG, u8"tREF; the microseconds not milliseconds one"))
			),
			(u8"rsvd0", 31,16, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming13, atui_nullstruct,
	(bios->DRAMTiming13, u8"DRAMTiming13",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tMRD",   5,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd0",  7,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tMOD",  13,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd1", 31,14, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming14_HBM2, atui_nullstruct,
	(bios->DRAMTiming14, u8"DRAMTiming14",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tXS",   10,0, ATUI_DEC,
				((LANG_ENG, u8"exit self refreh to not requiring a locked DLL"))
			),
			(u8"rsvd0", 31,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming14, atui_nullstruct,
	(bios->DRAMTiming14, u8"DRAMTiming14",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tXS",   10,0, ATUI_DEC,
				((LANG_ENG, u8"exit self refreh to not requiring a locked DLL"))
			),
			(u8"rsvd0", 15,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tDLLK", 26,16, ATUI_DEC,
				((LANG_ENG, u8"exit self refresh to requiring a locked DLL"))
			),
			(u8"rsvd1", 31,27, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming15, atui_nullstruct,
	(bios->DRAMTiming15, u8"DRAMTiming15",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"AlertCrcDly",  6,0, ATUI_DEC,
				((LANG_ENG, u8"expected alert crc error dely, in memclocks"))
			),
			(u8"rsvd0",        7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"AlertParDly", 14,8, ATUI_DEC,
				((LANG_ENG, u8"Parity error"))
			),
			(u8"PL",          18,15, ATUI_DEC,
				((LANG_ENG, u8"Cmd/Addr Parity Latency. See DDR4 MR5"))
			),
			(u8"rsvd1",       22,19, ATUI_DEC, (ATUI_NODESCR)),
			(u8"RankBusyDly", 29,23, ATUI_DEC,
				((LANG_ENG, u8"max of CRC/ECC alert delays"))
			),
			(u8"rsvd2",       31,30, ATUI_DEC, (ATUI_NODESCR))
		)),
		((LANG_ENG, u8"DDR reliability RAS"))
	)
)


PPATUI_FUNCIFY(union, DRAMTiming16, atui_nullstruct,
	(bios->DRAMTiming16, u8"DRAMTiming16",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tXSMRS", 10,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd0",  31,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming17_HBM2, atui_nullstruct,
	(bios->DRAMTiming17, u8"DRAMTiming17",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tPD",           3,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tCKSRE",        9,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tCKSRX",        15,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PwrDownDly",    23,16, ATUI_DEC,
				((LANG_ENG, u8"last command to PowerDown"))
			),
			(u8"AggPwrDownDly", 29,24, ATUI_DEC,
				((LANG_ENG, u8"last DRAM activity to precharge, for PD"))
			),
			(u8"rsvd2",         31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming17, atui_nullstruct,
	(bios->DRAMTiming17, u8"DRAMTiming17",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tPD",           4,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tCKSRE",        10,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tCKSRX",        16,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PwrDownDly",    24,17, ATUI_DEC,
				((LANG_ENG, u8"last command to PowerDown"))
			),
			(u8"AggPwrDownDly", 30,25, ATUI_DEC,
				((LANG_ENG, u8"last DRAM activity to precharge, for PD"))
			),
			(u8"rsvd0",         31,31, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming18_HBM2, atui_nullstruct,
	(bios->DRAMTiming18, u8"DRAMTiming18",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tRFCSB", 10,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd0",  15,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tSTAG",  23,16, ATUI_DEC,
				((LANG_ENG, u8"ref-to-ref different rank"))),
			(u8"rsvd1",  31,24, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming20, atui_nullstruct,
	(bios->DRAMTiming20, u8"DRAMTiming20",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tRFCSB", 10,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd0",  15,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tSTAG",  23,16, ATUI_DEC,
				((LANG_ENG, u8"ref-to-ref different rank"))),
			(u8"rsvd1",  31,24, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming21, atui_nullstruct,
	(bios->DRAMTiming21, u8"DRAMTiming21",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tXP",     5,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd0",  15,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tCPDED", 19,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd1",  23,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tCKE",   28,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd2",  31,29, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming22_HBM2, atui_nullstruct,
	(bios->DRAMTiming22, u8"DRAMTiming22",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"rsvd0_0",      1,0, ATUI_DEC,
				((LANG_ENG, u8"makes n=3,3"))
			),
			(u8"tRDDATA_EN",   6,2, ATUI_DEC,
				((LANG_ENG, u8"tCL-n; GD6 n=1, D4 n=5. READ to dfi_rddata_en"))
			),
			(u8"rsvd0",        7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tPHY_WRLAT",  12,8, ATUI_DEC,
				((LANG_ENG, u8"tCWL-n; GD6 n=2, D4 n=5. WRITE to dfi_wrdata_en"))
			),
			(u8"rsvd1",       15,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tPHY_RDLAT",  21,16, ATUI_DEC,
				((LANG_ENG, u8"dfi_rddata_en to dfi_rddata_vld dely"))
			),
			(u8"rsvd2",       23,22, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tPHY_WRDATA", 26,24, ATUI_DEC,
				((LANG_ENG, u8"dfi_wrdata_en to dfi_wrdata delay"))
			),
			(u8"rsvd3",       27,27, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tPARIN_LAT",  29,28, ATUI_DEC,
				((LANG_ENG, u8"ctrl signals to parity delay"))
			),
			(u8"rsvd4",       31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming22, atui_nullstruct,
	(bios->DRAMTiming22, u8"DRAMTiming22",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tRDDATA_EN",   6,0, ATUI_DEC,
				((LANG_ENG, u8"tCL-n; GD6 n=1, D4 n=5. READ to dfi_rddata_en"))
			),
			(u8"rsvd0",        7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tPHY_WRLAT",  12,8, ATUI_DEC,
				((LANG_ENG, u8"tCWL-n; GD6 n=2, D4 n=5. WRITE to dfi_wrdata_en"))
			),
			(u8"rsvd1",       15,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tPHY_RDLAT",  21,16, ATUI_DEC,
				((LANG_ENG, u8"dfi_rddata_en to dfi_rddata_vld dely"))
			),
			(u8"rsvd2",       23,22, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tPHY_WRDATA", 26,24, ATUI_DEC,
				((LANG_ENG, u8"dfi_wrdata_en to dfi_wrdata delay"))
			),
			(u8"rsvd3",       27,27, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tPARIN_LAT",  29,28, ATUI_DEC,
				((LANG_ENG, u8"ctrl signals to parity delay"))
			),
			(u8"rsvd4",       31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, DRAMTiming23, atui_nullstruct,
	(bios->DRAMTiming23, u8"DRAMTiming23",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"LpDly",      5,0, ATUI_DEC,
				((LANG_ENG, u8"hysteresis before placing PHY into low power"))
			),
			(u8"rsvd0",      7,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"LpExitDly",  13,8, ATUI_DEC,
				((LANG_ENG, u8"min memclk before taking a rank out of powerdown"))
			),
			(u8"rsvd1",      15,14, ATUI_DEC, (ATUI_NODESCR)),
			(u8"CKESTAGDLY", 19,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd3",      31,20, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming34, atui_nullstruct,
	(bios->DRAMTiming34, u8"DRAMTiming34",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tPhyupd_resp", 3,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tRDEDC_EN",    10,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd0",        11,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tWREDC_EN",    18,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd1",        31,19, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming35, atui_nullstruct,
	(bios->DRAMTiming35, u8"DRAMTiming35",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"ReceiverWait", 10,0, ATUI_DEC,
				((LANG_ENG, u8"Wait time to start recovery sequence"))
			),
			(u8"CmdStageCnt",  21,11, ATUI_DEC,
				((LANG_ENG, u8"Recov. seq. cmd stagger counter. See CmdStgFrc. CmdStgFrc:1; 1=enable recovery command stagger in recovery phase"))
			),
			(u8"rsvd0",        23,22, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tWRMPR",       29,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd1",        31,30, ATUI_DEC, (ATUI_NODESCR))
		)),
		((LANG_ENG, u8"reliability RAS"))
	)
)


PPATUI_FUNCIFY(union, DRAMTiming36, atui_nullstruct,
	(bios->DRAMTiming36, u8"DRAMTiming36",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tWTRTR",     5,0, ATUI_DEC, ((LANG_ENG, u8"WRITE to WRTR"))),
			(u8"tREFTR",     11,6, ATUI_DEC,
				((LANG_ENG, u8"was named tREFTT. REFab to RDTR/WRTR"))),
			(u8"tTTROW",     17,12, ATUI_DEC, ((LANG_ENG, u8"??"))),
			(u8"tLDTLD",     23,18, ATUI_DEC, ((LANG_ENG, u8"JEDEC tLTLTR?"))),
			(u8"tUPDN",      29,24, ATUI_DEC, ((LANG_ENG, u8"??"))),
			(u8"tREFTR_MSB", 30,30, ATUI_DEC, ((LANG_ENG, u8"was named tREFTT"))),
			(u8"rsvd0",      31,31, ATUI_DEC, (ATUI_NODESCR))
		)), ((LANG_ENG, u8"GDDR training"))
	)
)


PPATUI_FUNCIFY(union, TRFCTimingCS01, atui_nullstruct,
	(bios->TRFCTimingCS01, u8"TRFCTimingCS01",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tRFC",  10,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd0", 31,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, TRFCTimingCS01_DDR4, atui_nullstruct,
	(bios->TRFCTimingCS01_DDR4, u8"TRFCTimingCS01_DDR4",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tRFC",  10,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tRFC2", 21,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tRFC4", 31,22, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, ChanPipeDly, atui_nullstruct,
	(bios->ChanPipeDly, u8"ChanPipeDly",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"TXCtrlChanDly", 2,0, ATUI_DEC,
				((LANG_ENG, u8"# of delay stages on DFI control from UMC to PHY"))
			),
			(u8"rsvd0",         3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TXDataChanDly", 6,4, ATUI_DEC,
				((LANG_ENG, u8"... on DFI write data from UMC to PHY"))
			),
			(u8"rsvd1",         7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"RXDataChanDly",10,8, ATUI_DEC,
				((LANG_ENG, u8"... on DFI read data from PHY to UMC"))
			),
			(u8"rsvd2",        31,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mc_seq_misc_timing_6_0_o, atui_nullstruct,
	(bios->mc_seq_misc_timing, u8"mc_seq_misc_timing",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"trp_wra", 6,0, ATUI_DEC,
				((LANG_ENG, u8"autoprecharge?"))
			),
			(u8"trp_rda", 13,7, ATUI_DEC,
				((LANG_ENG, u8"autoprecharge?"))
			),
			(u8"trp",     19,14, ATUI_DEC, (ATUI_NODESCR)),
			(u8"trfc",    28,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd2",   31,29, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, mc_seq_misc_timing2_6_0_o, atui_nullstruct,
	(bios->raw_data, u8"mc_seq_misc_timing2",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"pa2rdata",  3,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"pa2wdata",  7,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"faw",      12,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tredc",    15,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"twedc",    20,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"t32aw",    24,21, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd02",  27,25, ATUI_DEC, (ATUI_NODESCR)),
			(u8"twdatatr", 31,28, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, mc_seq_cmd_6_0_o, atui_nullstruct,
	(bios->raw_data, u8"mc_seq_cmd",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"adr",      15,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"mop",      19,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"end",      20,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"csb",      22,21, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd00",  23,23, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan0",    24,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan1",    25,25, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan2",    26,26, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chan3",    27,27, ATUI_DEC, (ATUI_NODESCR)),
			(u8"adr_msb1", 28,28, ATUI_DEC, (ATUI_NODESCR)),
			(u8"adr_msb0", 29,29, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd02",  31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, mc_seq_cas_timing_6_0_o, atui_nullstruct,
	(bios->raw_data, u8"mc_seq_cas_timing",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tnopw",    4,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tnopr",    9,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tr2w",    14,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tr2r",    18,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tw2r",    23,19, ATUI_DEC, (ATUI_NODESCR)),
			(u8"tcl",     28,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd01", 31,29, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, mc_seq_byte_remap_d0_6_0_o, atui_nullstruct,
	(bios->raw_data, u8"mc_seq_byte_remap_d0",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"byte0",    1,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"byte1",    3,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"byte2",    5,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"byte3",    7,6, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, mc_arb_ramcfg_7_0_o, atui_nullstruct,
	(bios->raw_data, u8"mc_arb_ramcfg",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"noofbank",           1,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"noofranks",          2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"noofrows",           5,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"noofcols",           7,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chansize",           8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"burstlength",        9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsv_2",             10,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"chansize_override", 11,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"noofgroups",        12,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsv_4",             15,13, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, mc_io_aphy_str_cntl_d0_6_0_o, atui_nullstruct,
	(bios->raw_data, u8"mc_io_aphy_str_cntl_d0",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"pstr_off_a",     5,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"nstr_off_a",    11,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"pstr_off_d_rd", 17,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"nstr_off_d_rd", 23,18, ATUI_DEC, (ATUI_NODESCR)),
			(u8"use_a_cal",     24,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"use_d_rd_cal",  25,25, ATUI_DEC, (ATUI_NODESCR)),
			(u8"cal_sel",       27,26, ATUI_DEC, (ATUI_NODESCR)),
			(u8"load_a_str",    28,28, ATUI_DEC, (ATUI_NODESCR)),
			(u8"load_d_rd_str", 29,29, ATUI_DEC, (ATUI_NODESCR)),
			(u8"_rsvd01",       31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, mc_seq_rxframing_dbi_d1_6_0_o, atui_nullstruct,
	(bios->raw_data, u8"mc_seq_rxframing_dbi_d1",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"dbi0",     3,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"dbi1",     7,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"dbi2",    11,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"dbi3",    15,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"dbi4",    19,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"dbi5",    23,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"dbi6",    27,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"dbi7",    31,28, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, mc_block_islands_ddr3_timings, atui_nullstruct, // 52 bytes
	// Northern, Southern, Sea, Volcanic Islands
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_wr_ctl_d0, u8"mc_seq_wr_ctl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_wr_ctl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_wr_ctl, u8"mc_seq_wr_ctl",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_wr_ctl_2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_ras_timing, u8"mc_seq_ras_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_ras_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_cas_timing, u8"mc_seq_cas_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_cas_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc_timing, u8"mc_seq_misc_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc_timing2, u8"mc_seq_misc_timing2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc_timing2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_pmg_timing, u8"mc_seq_pmg_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_pmg_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc1.mr0, u8"mr0",
		(ATUI_NODISPLAY, ATUI_INLINE, ddr3_mr0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc1.mr1, u8"mr1",
		(ATUI_NODISPLAY, ATUI_INLINE, ddr3_mr1),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc3.mr2, u8"mr2",
		(ATUI_NODISPLAY, ATUI_INLINE, ddr3_mr2),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc3.mr3, u8"mr3",
		(ATUI_NODISPLAY, ATUI_INLINE, ddr3_mr3),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc8, u8"mc_seq_misc8",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc8_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_dram_timing, u8"mc_arb_dram_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_dram_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_dram_timing2, u8"mc_arb_dram_timing2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_dram_timing2_6_0),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, mc_block_islands_gddr5_timings, atui_nullstruct,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_wr_ctl_d0, u8"mc_seq_wr_ctl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_wr_ctl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_wr_ctl, u8"mc_seq_wr_ctl",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_wr_ctl_2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_ras_timing, u8"mc_seq_ras_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_ras_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_cas_timing, u8"mc_seq_cas_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_cas_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc_timing, u8"mc_seq_misc_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc_timing2, u8"mc_seq_misc_timing2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc_timing2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_pmg_timing, u8"mc_seq_pmg_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_pmg_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc1.gddr5_mr0, u8"gddr5_mr0",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr5_mr0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc1.gddr5_mr1, u8"gddr5_mr1",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr5_mr1),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc3.gddr5_mr4, u8"gddr5_mr4",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr5_mr4),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc3.gddr5_mr5, u8"gddr5_mr5",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr5_mr5),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc8.gddr5_mr7, u8"gddr5_mr7",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr5_mr7),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc8.gddr5_mr8, u8"gddr5_mr8",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr5_mr8),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_dram_timing, u8"mc_arb_dram_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_dram_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_dram_timing2, u8"mc_arb_dram_timing2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_dram_timing2_6_0),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, mc_block_fiji_timings, atui_nullstruct,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_cas_timing, u8"mc_seq_cas_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_cas_timing_6_0_o),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc_timing2, u8"mc_seq_misc_timing2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc_timing2_6_0_o),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_rd_ctl_d0, u8"mc_seq_rd_ctl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_rd_ctl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_wr_ctl_d0, u8"mc_seq_wr_ctl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_wr_ctl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_cmd, u8"mc_seq_cmd",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_cmd_6_0_o),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_rxframing_edc_d1, u8"mc_seq_rxframing_edc_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_rxframing_edc_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_dram_timing, u8"mc_arb_dram_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_dram_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_dram_timing2, u8"mc_arb_dram_timing2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_dram_timing2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_burst_time, u8"mc_arb_burst_time",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_burst_time_8_1),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, mc_block_polaris_timings, atui_nullstruct,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_wr_ctl_d0, u8"mc_seq_wr_ctl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_wr_ctl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_wr_ctl_2, u8"mc_seq_wr_ctl_2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_wr_ctl_2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_pmg_timing, u8"mc_seq_pmg_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_pmg_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_ras_timing, u8"mc_seq_ras_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_ras_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_cas_timing, u8"mc_seq_cas_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_cas_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc_timing, u8"mc_seq_misc_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc_timing_6_0_o),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc_timing2, u8"mc_seq_misc_timing2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc_timing2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc1.gddr5_mr0, u8"gddr5_mr0",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr5_mr0),
		((LANG_ENG, u8"seq_misc1"))
	),
	(bios->mc_seq_misc1.gddr5_mr1, u8"gddr5_mr1",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr5_mr1),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc3.gddr5_mr4, u8"gddr5_mr4",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr5_mr4),
		((LANG_ENG, u8"seq_misc3"))
	),
	(bios->mc_seq_misc3.gddr5_mr5, u8"gddr5_mr5",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr5_mr5),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc8.gddr5_mr7, u8"gddr5_mr7",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr5_mr7),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc8.gddr5_mr8, u8"gddr5_mr8",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr5_mr8),
		((LANG_ENG, u8"seq_misc8"))
	),
	(bios->mc_arb_dram_timing, u8"mc_arb_dram_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_dram_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_dram_timing2, u8"mc_arb_dram_timing2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_dram_timing2_6_0),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, umc_block_vega10_timings, atomtree_vram_info_header_v2_3,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming1, u8"DRAMTiming1",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming1),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming2, u8"DRAMTiming2",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming3, u8"DRAMTiming3",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming3),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming4, u8"DRAMTiming4",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming4),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming5, u8"DRAMTiming5",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming5),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming6, u8"DRAMTiming6",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming6),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming7, u8"DRAMTiming7",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming7),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming8, u8"DRAMTiming8",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming8),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming9, u8"DRAMTiming9",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming9_HBM2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming10, u8"DRAMTiming10",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming10),
		(ATUI_NODESCR)
	),

	(bios->DRAMTiming12, u8"DRAMTiming12",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming12),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming13, u8"DRAMTiming13",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming13),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming14, u8"DRAMTiming14",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming14_HBM2),
		(ATUI_NODESCR)
	),
	(bios->unknown15, u8"unknown15",
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, u8"unsure"))
	),
	(bios->DRAMTiming16, u8"DRAMTiming16",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming16),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming17, u8"DRAMTiming17",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming17_HBM2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming18, u8"DRAMTiming18",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming18_HBM2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming21, u8"DRAMTiming21",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming21),
		(ATUI_NODESCR)
	),
	(bios->unknown19, u8"unknown19",
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, u8"unsure"))
	),
	(bios->unknown20, u8"unknown20",
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, u8"unsure"))
	),
	(bios->tRFC, u8"tRFC",
		(ATUI_NODISPLAY, ATUI_INLINE, TRFCTimingCS01),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming22, u8"DRAMTiming22",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming22_HBM2),
		(ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, umc_block_vega21_timings, atomtree_vram_info_header_v2_3,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming1, u8"DRAMTiming1",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming1),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming2, u8"DRAMTiming2",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming3, u8"DRAMTiming3",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming3),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming4, u8"DRAMTiming4",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming4),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming5, u8"DRAMTiming5",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming5),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming6, u8"DRAMTiming6",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming6),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming7, u8"DRAMTiming7",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming7),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming8, u8"DRAMTiming8",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming8),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming9, u8"DRAMTiming9",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming9_HBM2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming10, u8"DRAMTiming10",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming10),
		(ATUI_NODESCR)
	),

	(bios->DRAMTiming12, u8"DRAMTiming12",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming12),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming13, u8"DRAMTiming13",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming13),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming14, u8"DRAMTiming14",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming14_HBM2),
		(ATUI_NODESCR)
	),
	(bios->unknown15, u8"unknown15",
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, u8"unsure"))
	),
	(bios->DRAMTiming16, u8"DRAMTiming16",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming16),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming17, u8"DRAMTiming17",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming17_HBM2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming18, u8"DRAMTiming18",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming18_HBM2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming21, u8"DRAMTiming21",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming21),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming22, u8"DRAMTiming22",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming22),
		(ATUI_NODESCR)
	),
	(bios->unknown23, u8"unknown23",
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, u8"unsure"))
	),
	(bios->tRFC, u8"tRFC",
		(ATUI_NODISPLAY, ATUI_INLINE, TRFCTimingCS01),
		(ATUI_NODESCR)
	),
	(bios->ChanPipeDly, u8"ChanPipeDly",
		(ATUI_NODISPLAY, ATUI_INLINE, ChanPipeDly),
		(ATUI_NODESCR)
	),
	(bios->unkown24, u8"unkown24",
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, u8"unsure"))
	)
)

PPATUI_FUNCIFY(struct, umc_block_navi1_timings, atomtree_vram_info_header_v2_4,

	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),

	(bios->gddr6_mr5.gddr6_mr5, u8"gddr6_mr5",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr5),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr5.reserved, u8"gddr6_mr5_reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gddr6_mr0.gddr6_mr0, u8"gddr6_mr0",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr0),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr0.reserved, u8"gddr6_mr0_reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->UMCCTRL_PMG_CMD_EMRS, u8"UMCCTRL_PMG_CMD_EMRS",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gddr6_mr4.gddr6_mr4, u8"gddr6_mr4",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr4),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr4.reserved, u8"gddr6_mr4_reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gddr6_mr8.gddr6_mr8, u8"gddr6_mr8",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr8),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr8.reserved, u8"gddr6_mr8_reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DRAMTiming1, u8"DRAMTiming1",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming1),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming2, u8"DRAMTiming2",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming3, u8"DRAMTiming3",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming3),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming4, u8"DRAMTiming4",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming4),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming5, u8"DRAMTiming5",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming5),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming6, u8"DRAMTiming6",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming6),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming7, u8"DRAMTiming7",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming7),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming8, u8"DRAMTiming8",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming8),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming9, u8"DRAMTiming9",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming9),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming10, u8"DRAMTiming10",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming10),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming12, u8"DRAMTiming12",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming12),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming13, u8"DRAMTiming13",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming13),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming14, u8"DRAMTiming14",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming14),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming16, u8"DRAMTiming16",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming16),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming17, u8"DRAMTiming17",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming17),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming20, u8"DRAMTiming20",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming20),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming21, u8"DRAMTiming21",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming21),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming22, u8"DRAMTiming22",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming22),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming23, u8"DRAMTiming23",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming23),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming35, u8"DRAMTiming35",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming35),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming36, u8"DRAMTiming36",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming36),
		(ATUI_NODESCR)
	),
	(bios->tRFC, u8"tRFC",
		(ATUI_NODISPLAY, ATUI_INLINE, TRFCTimingCS01),
		(ATUI_NODESCR)
	),
	(bios->ChanPipeDly, u8"ChanPipeDly",
		(ATUI_NODISPLAY, ATUI_INLINE, ChanPipeDly),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, mc_block_caicos_turks_ddr3_adjust, atui_nullstruct,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_io_reserve_d0, u8"mc_seq_io_reserve_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_io_reserve_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_txcntl_dphy0_d0, u8"mc_io_txcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_txcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_txcntl_aphy_d0, u8"mc_io_txcntl_aphy_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_txcntl_aphy_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_rxcntl_dphy0_d0, u8"mc_io_rxcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_rxcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_dphy_str_cntl_d0, u8"mc_io_dphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_dphy_str_cntl_d0_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_io_aphy_str_cntl_d0, u8"mc_io_aphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_aphy_str_cntl_d0_6_0_o),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_cfg, u8"mc_pmg_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_auto_cfg, u8"mc_pmg_auto_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_auto_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_pmg_timing, u8"mc_seq_pmg_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_pmg_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_wr_ctl_d0, u8"mc_seq_wr_ctl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_wr_ctl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d0, u8"mc_io_pad_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d1, u8"mc_io_pad_cntl_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rxphase_d0, u8"mc_io_debug_dqb0l_rxphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rxphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rxphase_d1, u8"mc_io_debug_dqb0l_rxphase_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rxphase_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wck_rxphase_d0, u8"mc_io_debug_wck_rxphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wck_rxphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_rxphase_d0, u8"mc_io_debug_edc_rxphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_rxphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_rxphase_d0, u8"mc_io_debug_dbi_rxphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_rxphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txphase_d0, u8"mc_io_debug_dqb0l_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txphase_d1, u8"mc_io_debug_dqb0l_txphase_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txphase_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_txphase_d0, u8"mc_io_debug_dbi_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wck_txphase_d0, u8"mc_io_debug_wck_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wck_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_txphase_d0, u8"mc_io_debug_edc_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txphase_d0, u8"mc_io_debug_ck_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_addrl_txphase_d0, u8"mc_io_debug_addrl_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_addrl_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_acmd_txphase_d0, u8"mc_io_debug_acmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_acmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_cmd_txphase_d0, u8"mc_io_debug_cmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_cmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, mc_block_turks_gddr5_adjust, atui_nullstruct,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_io_reserve_d0, u8"mc_seq_io_reserve_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_io_reserve_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_txcntl_dphy0_d0, u8"mc_io_txcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_txcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_txcntl_aphy_d0, u8"mc_io_txcntl_aphy_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_txcntl_aphy_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_rxcntl_dphy0_d0, u8"mc_io_rxcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_rxcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_dphy_str_cntl_d0, u8"mc_io_dphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_dphy_str_cntl_d0_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_io_aphy_str_cntl_d0, u8"mc_io_aphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_aphy_str_cntl_d0_6_0_o),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_cfg, u8"mc_pmg_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_auto_cfg, u8"mc_pmg_auto_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_auto_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_pmg_timing, u8"mc_seq_pmg_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_pmg_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_wr_ctl_d0, u8"mc_seq_wr_ctl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_wr_ctl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d0, u8"mc_io_pad_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d1, u8"mc_io_pad_cntl_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_gcnt, u8"mc_tsm_debug_gcnt",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_gcnt_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_config__0, u8"mc_config__0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_config_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_flag__0, u8"mc_tsm_debug_flag__0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_flag_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt6__0, u8"mc_tsm_debug_bcnt6__0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt6_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_config__1, u8"mc_config__1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_config_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_flag__1, u8"mc_tsm_debug_flag__1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_flag_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt6__1, u8"mc_tsm_debug_bcnt6__1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt6_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_config__2, u8"mc_config__2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_config_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_misc, u8"mc_tsm_debug_misc",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_misc_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt0, u8"mc_tsm_debug_bcnt0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt1, u8"mc_tsm_debug_bcnt1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt2, u8"mc_tsm_debug_bcnt2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt8, u8"mc_tsm_debug_bcnt8",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt8_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt9, u8"mc_tsm_debug_bcnt9",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt9_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt10, u8"mc_tsm_debug_bcnt10",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt10_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_14, u8"mc_io_debug_up_14",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_14_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_15, u8"mc_io_debug_up_15",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_15_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_reserve_0_s, u8"mc_seq_reserve_0_s",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_reserve_0_s_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc5, u8"mc_seq_misc5",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc5_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc4, u8"mc_seq_misc4",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc4_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc6, u8"mc_seq_misc6",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc6_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc7, u8"mc_seq_misc7",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc7_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_vref_cal_d0, u8"mc_io_debug_dqb0l_rx_vref_cal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_vref_cal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb2l_rx_vref_cal_d0, u8"mc_io_debug_dqb2l_rx_vref_cal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb2l_rx_vref_cal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_rx_vref_cal_d0, u8"mc_io_debug_dbi_rx_vref_cal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_rx_vref_cal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb1_cdr_phsize_d0, u8"mc_io_debug_dqb1_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb1_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_addrl_txphase_d0, u8"mc_io_debug_addrl_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_addrl_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_acmd_txphase_d0, u8"mc_io_debug_acmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_acmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_cmd_txphase_d0, u8"mc_io_debug_cmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_cmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txphase_d0, u8"mc_io_debug_ck_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txphase_d0_6_0),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, mc_block_barts_gddr5_adjust, atui_nullstruct,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_io_reserve_d0, u8"mc_seq_io_reserve_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_io_reserve_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_txcntl_dphy0_d0, u8"mc_io_txcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_txcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_txcntl_aphy_d0, u8"mc_io_txcntl_aphy_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_txcntl_aphy_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_rxcntl_dphy0_d0, u8"mc_io_rxcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_rxcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_dphy_str_cntl_d0, u8"mc_io_dphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_dphy_str_cntl_d0_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_io_aphy_str_cntl_d0, u8"mc_io_aphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_aphy_str_cntl_d0_6_0_o),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_cfg, u8"mc_pmg_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_auto_cfg, u8"mc_pmg_auto_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_auto_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_pmg_timing, u8"mc_seq_pmg_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_pmg_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_wr_ctl_d0, u8"mc_seq_wr_ctl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_wr_ctl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d0, u8"mc_io_pad_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d1, u8"mc_io_pad_cntl_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_gcnt, u8"mc_tsm_debug_gcnt",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_gcnt_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_config_mcd__0, u8"mc_config_mcd__0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_config_mcd_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_flag__0, u8"mc_tsm_debug_flag__0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_flag_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt6__0, u8"mc_tsm_debug_bcnt6__0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt6_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_config_mcd__1, u8"mc_config_mcd__1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_config_mcd_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_flag__1, u8"mc_tsm_debug_flag__1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_flag_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt6__1, u8"mc_tsm_debug_bcnt6__1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt6_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_config_mcd__2, u8"mc_config_mcd__2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_config_mcd_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_flag__2, u8"mc_tsm_debug_flag__2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_flag_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt6__2, u8"mc_tsm_debug_bcnt6__2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt6_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_config_mcd__3, u8"mc_config_mcd__3",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_config_mcd_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_flag__3, u8"mc_tsm_debug_flag__3",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_flag_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt6__3, u8"mc_tsm_debug_bcnt6__3",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt6_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_config_mcd__4, u8"mc_config_mcd__4",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_config_mcd_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_misc, u8"mc_tsm_debug_misc",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_misc_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt0, u8"mc_tsm_debug_bcnt0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt1, u8"mc_tsm_debug_bcnt1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt2, u8"mc_tsm_debug_bcnt2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt8, u8"mc_tsm_debug_bcnt8",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt8_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt9, u8"mc_tsm_debug_bcnt9",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt9_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt10, u8"mc_tsm_debug_bcnt10",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt10_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_14, u8"mc_io_debug_up_14",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_14_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_15, u8"mc_io_debug_up_15",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_15_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_reserve_0_s, u8"mc_seq_reserve_0_s",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_reserve_0_s_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc5, u8"mc_seq_misc5",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc5_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc4, u8"mc_seq_misc4",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc4_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc6, u8"mc_seq_misc6",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc6_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc7, u8"mc_seq_misc7",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc7_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_vref_cal_d0, u8"mc_io_debug_dqb0l_rx_vref_cal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_vref_cal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb2l_rx_vref_cal_d0, u8"mc_io_debug_dqb2l_rx_vref_cal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb2l_rx_vref_cal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_rx_vref_cal_d0, u8"mc_io_debug_dbi_rx_vref_cal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_rx_vref_cal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb1_cdr_phsize_d0, u8"mc_io_debug_dqb1_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb1_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_addrl_txphase_d0, u8"mc_io_debug_addrl_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_addrl_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_acmd_txphase_d0, u8"mc_io_debug_acmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_acmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_cmd_txphase_d0, u8"mc_io_debug_cmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_cmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txphase_d0, u8"mc_io_debug_ck_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txphase_d0_6_0),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, mc_block_cayman_gddr5_adjust, atui_nullstruct,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_io_reserve_d0, u8"mc_seq_io_reserve_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_io_reserve_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_txcntl_dphy0_d0, u8"mc_io_txcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_txcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),

	(bios->mc_io_dphy_str_cntl_d0, u8"mc_io_dphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_dphy_str_cntl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_aphy_str_cntl_d0, u8"mc_io_aphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_aphy_str_cntl_d0_6_0_o),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_cfg, u8"mc_pmg_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_auto_cfg, u8"mc_pmg_auto_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_auto_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_pmg_timing, u8"mc_seq_pmg_timing",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_pmg_timing_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_wr_ctl_d0, u8"mc_seq_wr_ctl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_wr_ctl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d0, u8"mc_io_pad_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d1, u8"mc_io_pad_cntl_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_0, u8"mc_io_debug_up_0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_config_0, u8"mc_config_0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_config_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_1__0, u8"mc_io_debug_up_1__0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_9__0, u8"mc_io_debug_up_9__0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_9_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_config_1_9__0, u8"mc_config_1_9__0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_config_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_1__1, u8"mc_io_debug_up_1__1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_9__1, u8"mc_io_debug_up_9__1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_9_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_config_1_9__1, u8"mc_config_1_9__1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_config_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_1__2, u8"mc_io_debug_up_1__2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_9__2, u8"mc_io_debug_up_9__2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_9_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_config_1_9__2, u8"mc_config_1_9__2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_config_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_1__3, u8"mc_io_debug_up_1__3",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_9__3, u8"mc_io_debug_up_9__3",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_9_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_config_1_9__3, u8"mc_config_1_9__3",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_config_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_2, u8"mc_io_debug_up_2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_3, u8"mc_io_debug_up_3",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_3_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_4, u8"mc_io_debug_up_4",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_4_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_5, u8"mc_io_debug_up_5",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_5_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_11, u8"mc_io_debug_up_11",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_11_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_12, u8"mc_io_debug_up_12",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_12_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_13, u8"mc_io_debug_up_13",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_13_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_14, u8"mc_io_debug_up_14",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_14_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_15, u8"mc_io_debug_up_15",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_15_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_reserve_0_s, u8"mc_seq_reserve_0_s",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_reserve_0_s_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc5, u8"mc_seq_misc5",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc5_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc4, u8"mc_seq_misc4",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc4_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc6, u8"mc_seq_misc6",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc6_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc7, u8"mc_seq_misc7",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc7_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_vref_cal_d0, u8"mc_io_debug_dqb0l_rx_vref_cal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_vref_cal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb2l_rx_vref_cal_d0, u8"mc_io_debug_dqb2l_rx_vref_cal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb2l_rx_vref_cal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_rx_vref_cal_d0, u8"mc_io_debug_dbi_rx_vref_cal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_rx_vref_cal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb1_cdr_phsize_d0, u8"mc_io_debug_dqb1_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb1_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_addrl_txphase_d0, u8"mc_io_debug_addrl_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_addrl_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_acmd_txphase_d0, u8"mc_io_debug_acmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_acmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_cmd_txphase_d0, u8"mc_io_debug_cmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_cmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txphase_d0, u8"mc_io_debug_ck_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txphase_d0_6_0),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, mc_block_oland_verde_gddr5_adjust, atui_nullstruct,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_io_reserve_d0, u8"mc_seq_io_reserve_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_io_reserve_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_txcntl_dphy0_d0, u8"mc_io_txcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_txcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_txcntl_aphy_d0, u8"mc_io_txcntl_aphy_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_txcntl_aphy_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_rxcntl_dphy0_d0, u8"mc_io_rxcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_rxcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_rxcntl1_dphy0_d0, u8"mc_io_rxcntl1_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_rxcntl1_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_dphy_str_cntl_d0, u8"mc_io_dphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_dphy_str_cntl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_aphy_str_cntl_d0, u8"mc_io_aphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_aphy_str_cntl_d0_6_0_o),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_cfg, u8"mc_pmg_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_auto_cfg, u8"mc_pmg_auto_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_auto_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_rd_ctl_d0, u8"mc_seq_rd_ctl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_rd_ctl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d0, u8"mc_io_pad_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d1, u8"mc_io_pad_cntl_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_phy_timing_2, u8"mc_phy_timing_2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_phy_timing_2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_gcnt, u8"mc_tsm_debug_gcnt",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_gcnt_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_misc, u8"mc_tsm_debug_misc",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_misc_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt0, u8"mc_tsm_debug_bcnt0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt1, u8"mc_tsm_debug_bcnt1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt2, u8"mc_tsm_debug_bcnt2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt7, u8"mc_tsm_debug_bcnt7",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt7_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt8, u8"mc_tsm_debug_bcnt8",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt8_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt9, u8"mc_tsm_debug_bcnt9",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt9_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt10, u8"mc_tsm_debug_bcnt10",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt10_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_14, u8"mc_io_debug_up_14",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_14_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_15, u8"mc_io_debug_up_15",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_15_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_reserve_0_s, u8"mc_seq_reserve_0_s",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_reserve_0_s_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc5, u8"mc_seq_misc5",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc5_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc4, u8"mc_seq_misc4",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc4_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc6, u8"mc_seq_misc6",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc6_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc7, u8"mc_seq_misc7",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc7_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc9, u8"mc_seq_misc9",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc9_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_rtt_cntl0, u8"mc_arb_rtt_cntl0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_rtt_cntl0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_rtt_cntl1, u8"mc_arb_rtt_cntl1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_rtt_cntl1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_rtt_cntl2, u8"mc_arb_rtt_cntl2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_rtt_cntl2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_addrl_txphase_d0, u8"mc_io_debug_addrl_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_addrl_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_acmd_txphase_d0, u8"mc_io_debug_acmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_acmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_cmd_txphase_d0, u8"mc_io_debug_cmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_cmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txphase_d0, u8"mc_io_debug_ck_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_ofscal_d0, u8"mc_io_debug_dqb0l_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_ofscal_d1, u8"mc_io_debug_dqb0l_ofscal_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_ofscal_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_cmd_ofscal_d0, u8"mc_io_debug_cmd_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_cmd_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0_cdr_phsize_d0, u8"mc_io_debug_dqb0_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0_cdr_phsize_d1, u8"mc_io_debug_dqb0_cdr_phsize_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0_cdr_phsize_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_eq_d0, u8"mc_io_debug_dqb0l_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_eq_d1, u8"mc_io_debug_dqb0l_rx_eq_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_eq_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wck_rx_eq_d0, u8"mc_io_debug_wck_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wck_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_ofscal_d0, u8"mc_io_debug_dbi_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_ofscal_d0, u8"mc_io_debug_edc_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wck_ofscal_d0, u8"mc_io_debug_wck_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wck_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_cdr_phsize_d0, u8"mc_io_debug_edc_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_acmd_ofscal_d0, u8"mc_io_debug_acmd_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_acmd_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_cdr_phsize_d0, u8"mc_io_debug_dbi_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_rx_eq_d0, u8"mc_io_debug_dbi_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_rx_eq_d0, u8"mc_io_debug_edc_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_cdrcntl_d0, u8"mc_io_cdrcntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_cdrcntl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_cdrcntl1_d0, u8"mc_io_cdrcntl1_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_cdrcntl1_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_vref_cal_d0, u8"mc_io_debug_dqb0l_rx_vref_cal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_vref_cal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_vref_cal_d1, u8"mc_io_debug_dqb0l_rx_vref_cal_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_vref_cal_d1_6_0),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, mc_block_pitcairn_gddr5_adjust, atui_nullstruct,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_io_reserve_d0, u8"mc_seq_io_reserve_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_io_reserve_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_txcntl_dphy0_d0, u8"mc_io_txcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_txcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_txcntl_aphy_d0, u8"mc_io_txcntl_aphy_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_txcntl_aphy_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_rxcntl_dphy0_d0, u8"mc_io_rxcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_rxcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_rxcntl1_dphy0_d0, u8"mc_io_rxcntl1_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_rxcntl1_dphy0_d0_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_io_dphy_str_cntl_d0, u8"mc_io_dphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_dphy_str_cntl_d0_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_io_aphy_str_cntl_d0, u8"mc_io_aphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_aphy_str_cntl_d0_6_0_o),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_cfg, u8"mc_pmg_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_auto_cfg, u8"mc_pmg_auto_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_auto_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_rd_ctl_d0, u8"mc_seq_rd_ctl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_rd_ctl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d0, u8"mc_io_pad_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d1, u8"mc_io_pad_cntl_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_phy_timing_2, u8"mc_phy_timing_2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_phy_timing_2_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_gcnt, u8"mc_tsm_debug_gcnt",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_gcnt_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_misc, u8"mc_tsm_debug_misc",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_misc_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt0, u8"mc_tsm_debug_bcnt0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt1, u8"mc_tsm_debug_bcnt1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt2, u8"mc_tsm_debug_bcnt2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt7, u8"mc_tsm_debug_bcnt7",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt7_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt8, u8"mc_tsm_debug_bcnt8",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt8_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt9, u8"mc_tsm_debug_bcnt9",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt9_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt10, u8"mc_tsm_debug_bcnt10",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt10_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_14, u8"mc_io_debug_up_14",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_14_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_15, u8"mc_io_debug_up_15",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_15_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_reserve_0_s, u8"mc_seq_reserve_0_s",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_reserve_0_s_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc5, u8"mc_seq_misc5",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc5_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc4, u8"mc_seq_misc4",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc4_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc6, u8"mc_seq_misc6",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc6_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc7, u8"mc_seq_misc7",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc7_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc9, u8"mc_seq_misc9",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc9_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_rtt_cntl0, u8"mc_arb_rtt_cntl0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_rtt_cntl0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_rtt_cntl1, u8"mc_arb_rtt_cntl1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_rtt_cntl1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_rtt_cntl2, u8"mc_arb_rtt_cntl2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_rtt_cntl2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_addrl_txphase_d0, u8"mc_io_debug_addrl_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_addrl_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_acmd_txphase_d0, u8"mc_io_debug_acmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_acmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_cmd_txphase_d0, u8"mc_io_debug_cmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_cmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txphase_d0, u8"mc_io_debug_ck_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_ofscal_d0, u8"mc_io_debug_dqb0l_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_ofscal_d1, u8"mc_io_debug_dqb0l_ofscal_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_ofscal_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_cmd_ofscal_d0, u8"mc_io_debug_cmd_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_cmd_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0_cdr_phsize_d0, u8"mc_io_debug_dqb0_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0_cdr_phsize_d1, u8"mc_io_debug_dqb0_cdr_phsize_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0_cdr_phsize_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_eq_d0, u8"mc_io_debug_dqb0l_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_eq_d1, u8"mc_io_debug_dqb0l_rx_eq_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_eq_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wck_rx_eq_d0, u8"mc_io_debug_wck_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wck_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wcdr_cdr_phsize_d0, u8"mc_io_debug_wcdr_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wcdr_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_txbst_pd_d0, u8"mc_io_debug_dbi_txbst_pd_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_txbst_pd_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_txbst_pu_d0, u8"mc_io_debug_dbi_txbst_pu_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_txbst_pu_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_txbst_pd_d0, u8"mc_io_debug_edc_txbst_pd_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_txbst_pd_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_txbst_pu_d0, u8"mc_io_debug_edc_txbst_pu_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_txbst_pu_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txbst_pd_d0, u8"mc_io_debug_dqb0l_txbst_pd_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txbst_pd_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txbst_pd_d1, u8"mc_io_debug_dqb0l_txbst_pd_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txbst_pd_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txbst_pu_d0, u8"mc_io_debug_dqb0l_txbst_pu_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txbst_pu_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txbst_pu_d1, u8"mc_io_debug_dqb0l_txbst_pu_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txbst_pu_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txbst_pd_d0, u8"mc_io_debug_ck_txbst_pd_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txbst_pd_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txbst_pd_d1, u8"mc_io_debug_ck_txbst_pd_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txbst_pd_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txbst_pu_d0, u8"mc_io_debug_ck_txbst_pu_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txbst_pu_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txbst_pu_d1, u8"mc_io_debug_ck_txbst_pu_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txbst_pu_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_ofscal_d0, u8"mc_io_debug_dbi_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_ofscal_d0, u8"mc_io_debug_edc_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wck_ofscal_d0, u8"mc_io_debug_wck_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wck_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_cdr_phsize_d0, u8"mc_io_debug_edc_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_acmd_ofscal_d0, u8"mc_io_debug_acmd_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_acmd_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_cdr_phsize_d0, u8"mc_io_debug_dbi_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_rx_eq_d0, u8"mc_io_debug_dbi_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_rx_eq_d0, u8"mc_io_debug_edc_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_cdrcntl_d0, u8"mc_io_cdrcntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_cdrcntl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_cdrcntl1_d0, u8"mc_io_cdrcntl1_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_cdrcntl1_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_vref_cal_d0, u8"mc_io_debug_dqb0l_rx_vref_cal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_vref_cal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_vref_cal_d1, u8"mc_io_debug_dqb0l_rx_vref_cal_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_vref_cal_d1_6_0),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, mc_block_tahiti_gddr5_adjust, atui_nullstruct,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_io_reserve_d0, u8"mc_seq_io_reserve_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_io_reserve_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_txcntl_dphy0_d0, u8"mc_io_txcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_txcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_txcntl_aphy_d0, u8"mc_io_txcntl_aphy_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_txcntl_aphy_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_rxcntl_dphy0_d0, u8"mc_io_rxcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_rxcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_rxcntl1_dphy0_d0, u8"mc_io_rxcntl1_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_rxcntl1_dphy0_d0_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_io_dphy_str_cntl_d0, u8"mc_io_dphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_dphy_str_cntl_d0_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_io_aphy_str_cntl_d0, u8"mc_io_aphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_aphy_str_cntl_d0_6_0_o),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_cfg, u8"mc_pmg_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_auto_cfg, u8"mc_pmg_auto_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_auto_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_rd_ctl_d0, u8"mc_seq_rd_ctl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_rd_ctl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d0, u8"mc_io_pad_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d1, u8"mc_io_pad_cntl_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_phy_timing_2, u8"mc_phy_timing_2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_phy_timing_2_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_gcnt, u8"mc_tsm_debug_gcnt",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_gcnt_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_misc, u8"mc_tsm_debug_misc",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_misc_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt0, u8"mc_tsm_debug_bcnt0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt1, u8"mc_tsm_debug_bcnt1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt2, u8"mc_tsm_debug_bcnt2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt7, u8"mc_tsm_debug_bcnt7",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt7_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt8, u8"mc_tsm_debug_bcnt8",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt8_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt9, u8"mc_tsm_debug_bcnt9",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt9_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt10, u8"mc_tsm_debug_bcnt10",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt10_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_14, u8"mc_io_debug_up_14",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_14_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_15, u8"mc_io_debug_up_15",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_15_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_reserve_0_s, u8"mc_seq_reserve_0_s",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_reserve_0_s_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc5, u8"mc_seq_misc5",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc5_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc4, u8"mc_seq_misc4",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc4_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc6, u8"mc_seq_misc6",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc6_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc7, u8"mc_seq_misc7",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc7_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc9, u8"mc_seq_misc9",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc9_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_rtt_cntl0, u8"mc_arb_rtt_cntl0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_rtt_cntl0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_rtt_cntl1, u8"mc_arb_rtt_cntl1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_rtt_cntl1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_rtt_cntl2, u8"mc_arb_rtt_cntl2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_rtt_cntl2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_addrl_txphase_d0, u8"mc_io_debug_addrl_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_addrl_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_acmd_txphase_d0, u8"mc_io_debug_acmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_acmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_cmd_txphase_d0, u8"mc_io_debug_cmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_cmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txphase_d0, u8"mc_io_debug_ck_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_ofscal_d0, u8"mc_io_debug_dqb0l_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_ofscal_d1, u8"mc_io_debug_dqb0l_ofscal_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_ofscal_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_cmd_ofscal_d0, u8"mc_io_debug_cmd_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_cmd_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0_cdr_phsize_d0, u8"mc_io_debug_dqb0_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0_cdr_phsize_d1, u8"mc_io_debug_dqb0_cdr_phsize_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0_cdr_phsize_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_eq_d0, u8"mc_io_debug_dqb0l_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_eq_d1, u8"mc_io_debug_dqb0l_rx_eq_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_eq_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wck_rx_eq_d0, u8"mc_io_debug_wck_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wck_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wcdr_ofscal_d0, u8"mc_io_debug_wcdr_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wcdr_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wcdr_rx_vref_cal_d0, u8"mc_io_debug_wcdr_rx_vref_cal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wcdr_rx_vref_cal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wcdr_rx_eq_d0, u8"mc_io_debug_wcdr_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wcdr_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wcdr_cdr_phsize_d0, u8"mc_io_debug_wcdr_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wcdr_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_txbst_pd_d0, u8"mc_io_debug_dbi_txbst_pd_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_txbst_pd_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_txbst_pu_d0, u8"mc_io_debug_dbi_txbst_pu_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_txbst_pu_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_txbst_pd_d0, u8"mc_io_debug_edc_txbst_pd_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_txbst_pd_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_txbst_pu_d0, u8"mc_io_debug_edc_txbst_pu_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_txbst_pu_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wcdr_txbst_pd_d0, u8"mc_io_debug_wcdr_txbst_pd_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wcdr_txbst_pd_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wcdr_txbst_pu_d0, u8"mc_io_debug_wcdr_txbst_pu_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wcdr_txbst_pu_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txbst_pd_d0, u8"mc_io_debug_dqb0l_txbst_pd_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txbst_pd_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txbst_pd_d1, u8"mc_io_debug_dqb0l_txbst_pd_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txbst_pd_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txbst_pu_d0, u8"mc_io_debug_dqb0l_txbst_pu_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txbst_pu_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txbst_pu_d1, u8"mc_io_debug_dqb0l_txbst_pu_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txbst_pu_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txbst_pd_d0, u8"mc_io_debug_ck_txbst_pd_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txbst_pd_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txbst_pd_d1, u8"mc_io_debug_ck_txbst_pd_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txbst_pd_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txbst_pu_d0, u8"mc_io_debug_ck_txbst_pu_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txbst_pu_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txbst_pu_d1, u8"mc_io_debug_ck_txbst_pu_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txbst_pu_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_ofscal_d0, u8"mc_io_debug_dbi_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_ofscal_d0, u8"mc_io_debug_edc_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wck_ofscal_d0, u8"mc_io_debug_wck_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wck_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_cdr_phsize_d0, u8"mc_io_debug_edc_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_acmd_ofscal_d0, u8"mc_io_debug_acmd_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_acmd_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_cdr_phsize_d0, u8"mc_io_debug_dbi_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_rx_eq_d0, u8"mc_io_debug_dbi_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_rx_eq_d0, u8"mc_io_debug_edc_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_cdrcntl_d0, u8"mc_io_cdrcntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_cdrcntl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_cdrcntl1_d0, u8"mc_io_cdrcntl1_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_cdrcntl1_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_vref_cal_d0, u8"mc_io_debug_dqb0l_rx_vref_cal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_vref_cal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_vref_cal_d1, u8"mc_io_debug_dqb0l_rx_vref_cal_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_vref_cal_d1_6_0),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, mc_block_exo_gddr5_adjust, atui_nullstruct,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_io_reserve_d0, u8"mc_seq_io_reserve_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_io_reserve_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_txcntl_dphy0_d0, u8"mc_io_txcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_txcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_txcntl_aphy_d0, u8"mc_io_txcntl_aphy_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_txcntl_aphy_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_rxcntl_dphy0_d0, u8"mc_io_rxcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_rxcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_rxcntl1_dphy0_d0, u8"mc_io_rxcntl1_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_rxcntl1_dphy0_d0_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_io_dphy_str_cntl_d0, u8"mc_io_dphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_dphy_str_cntl_d0_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_io_aphy_str_cntl_d0, u8"mc_io_aphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_aphy_str_cntl_d0_6_0_o),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_cfg, u8"mc_pmg_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_auto_cfg, u8"mc_pmg_auto_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_auto_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_rd_ctl_d0, u8"mc_seq_rd_ctl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_rd_ctl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d0, u8"mc_io_pad_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d1, u8"mc_io_pad_cntl_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_phy_timing_2, u8"mc_phy_timing_2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_phy_timing_2_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rxphase_d0, u8"mc_io_debug_dqb0l_rxphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rxphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rxphase_d1, u8"mc_io_debug_dqb0l_rxphase_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rxphase_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wck_rxphase_d0, u8"mc_io_debug_wck_rxphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wck_rxphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_rxphase_d0, u8"mc_io_debug_edc_rxphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_rxphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_rxphase_d0, u8"mc_io_debug_dbi_rxphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_rxphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txphase_d0, u8"mc_io_debug_dqb0l_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txphase_d1, u8"mc_io_debug_dqb0l_txphase_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txphase_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_txphase_d0, u8"mc_io_debug_dbi_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wck_txphase_d0, u8"mc_io_debug_wck_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wck_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_txphase_d0, u8"mc_io_debug_edc_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txphase_d0, u8"mc_io_debug_ck_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_addrl_txphase_d0, u8"mc_io_debug_addrl_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_addrl_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_acmd_txphase_d0, u8"mc_io_debug_acmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_acmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_cmd_txphase_d0, u8"mc_io_debug_cmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_cmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_addrl_clksel_d0, u8"mc_io_debug_addrl_clksel_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_addrl_clksel_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_addrl_clksel_d1, u8"mc_io_debug_addrl_clksel_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_addrl_clksel_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc5, u8"mc_seq_misc5",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc5_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_fifo_ctl, u8"mc_seq_fifo_ctl",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_fifo_ctl_7_1),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, mc_block_tonga_gddr5_adjust, atui_nullstruct,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->mc_io_rxcntl_dphy0_d0, u8"mc_io_rxcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_rxcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_rxcntl1_dphy0_d0, u8"mc_io_rxcntl1_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_rxcntl1_dphy0_d0_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_io_aphy_str_cntl_d0, u8"mc_io_aphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_aphy_str_cntl_d0_6_0_o),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt2, u8"mc_tsm_debug_bcnt2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_reserve_1_s, u8"mc_seq_reserve_1_s",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_reserve_1_s_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc5, u8"mc_seq_misc5",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc5_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc4, u8"mc_seq_misc4",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc4_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc6, u8"mc_seq_misc6",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc6_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc7, u8"mc_seq_misc7",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc7_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc9, u8"mc_seq_misc9",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc9_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_addrl_txphase_d0, u8"mc_io_debug_addrl_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_addrl_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_acmd_txphase_d0, u8"mc_io_debug_acmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_acmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_cmd_txphase_d0, u8"mc_io_debug_cmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_cmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txphase_d0, u8"mc_io_debug_ck_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_clksel_d0, u8"mc_io_debug_dqb0l_clksel_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_clksel_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_clksel_d1, u8"mc_io_debug_dqb0l_clksel_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_clksel_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wck_clksel_d0, u8"mc_io_debug_wck_clksel_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wck_clksel_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txphase_d0, u8"mc_io_debug_dqb0l_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txphase_d1, u8"mc_io_debug_dqb0l_txphase_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txphase_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wck_txphase_d0, u8"mc_io_debug_wck_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wck_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_txframing_byte0_d0, u8"mc_seq_txframing_byte0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_txframing_byte0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_txframing_byte0_d1, u8"mc_seq_txframing_byte0_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_txframing_byte0_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_rxphase_d0, u8"mc_io_debug_edc_rxphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_rxphase_d0_6_0),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, mc_block_hawaii_grenada_gddr5_adjust, atui_nullstruct,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_io_reserve_d0, u8"mc_seq_io_reserve_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_io_reserve_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_txcntl_dphy0_d0, u8"mc_io_txcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_txcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_txcntl_aphy_d0, u8"mc_io_txcntl_aphy_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_txcntl_aphy_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_rxcntl_dphy0_d0, u8"mc_io_rxcntl_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_rxcntl_dphy0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_rxcntl1_dphy0_d0, u8"mc_io_rxcntl1_dphy0_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_rxcntl1_dphy0_d0_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_io_dphy_str_cntl_d0, u8"mc_io_dphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_dphy_str_cntl_d0_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_io_aphy_str_cntl_d0, u8"mc_io_aphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_aphy_str_cntl_d0_6_0_o),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_cfg, u8"mc_pmg_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_pmg_auto_cfg, u8"mc_pmg_auto_cfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_pmg_auto_cfg_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_rd_ctl_d0, u8"mc_seq_rd_ctl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_rd_ctl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d0, u8"mc_io_pad_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d1, u8"mc_io_pad_cntl_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_phy_timing_2, u8"mc_phy_timing_2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_phy_timing_2_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_gcnt, u8"mc_tsm_debug_gcnt",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_gcnt_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_misc, u8"mc_tsm_debug_misc",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_misc_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt0, u8"mc_tsm_debug_bcnt0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt1, u8"mc_tsm_debug_bcnt1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt2, u8"mc_tsm_debug_bcnt2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt7, u8"mc_tsm_debug_bcnt7",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt7_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt8, u8"mc_tsm_debug_bcnt8",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt8_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt9, u8"mc_tsm_debug_bcnt9",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt9_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt10, u8"mc_tsm_debug_bcnt10",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt10_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_14, u8"mc_io_debug_up_14",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_14_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_15, u8"mc_io_debug_up_15",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_15_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_reserve_0_s, u8"mc_seq_reserve_0_s",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_reserve_0_s_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc5, u8"mc_seq_misc5",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc5_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc4, u8"mc_seq_misc4",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc4_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc6, u8"mc_seq_misc6",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc6_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc7, u8"mc_seq_misc7",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc7_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc9, u8"mc_seq_misc9",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc9_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_rtt_cntl0, u8"mc_arb_rtt_cntl0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_rtt_cntl0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_rtt_cntl1, u8"mc_arb_rtt_cntl1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_rtt_cntl1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_arb_rtt_cntl2, u8"mc_arb_rtt_cntl2",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_arb_rtt_cntl2_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_g5pdx_ctrl, u8"mc_seq_g5pdx_ctrl",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_g5pdx_ctrl_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_addrl_txphase_d0, u8"mc_io_debug_addrl_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_addrl_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_acmd_txphase_d0, u8"mc_io_debug_acmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_acmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_cmd_txphase_d0, u8"mc_io_debug_cmd_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_cmd_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_ck_txphase_d0, u8"mc_io_debug_ck_txphase_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_ck_txphase_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_ofscal_d0, u8"mc_io_debug_dqb0l_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_ofscal_d1, u8"mc_io_debug_dqb0l_ofscal_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_ofscal_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_cmd_ofscal_d0, u8"mc_io_debug_cmd_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_cmd_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0_cdr_phsize_d0, u8"mc_io_debug_dqb0_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0_cdr_phsize_d1, u8"mc_io_debug_dqb0_cdr_phsize_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0_cdr_phsize_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_eq_d0, u8"mc_io_debug_dqb0l_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_eq_d1, u8"mc_io_debug_dqb0l_rx_eq_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_eq_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wck_rx_eq_d0, u8"mc_io_debug_wck_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wck_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wcdr_ofscal_d0, u8"mc_io_debug_wcdr_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wcdr_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wcdr_rx_vref_cal_d0, u8"mc_io_debug_wcdr_rx_vref_cal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wcdr_rx_vref_cal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wcdr_rx_eq_d0, u8"mc_io_debug_wcdr_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wcdr_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wcdr_cdr_phsize_d0, u8"mc_io_debug_wcdr_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wcdr_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_txbst_pd_d0, u8"mc_io_debug_dbi_txbst_pd_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_txbst_pd_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_txbst_pu_d0, u8"mc_io_debug_dbi_txbst_pu_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_txbst_pu_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_txbst_pd_d0, u8"mc_io_debug_edc_txbst_pd_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_txbst_pd_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_txbst_pu_d0, u8"mc_io_debug_edc_txbst_pu_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_txbst_pu_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wcdr_txbst_pd_d0, u8"mc_io_debug_wcdr_txbst_pd_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wcdr_txbst_pd_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wcdr_txbst_pu_d0, u8"mc_io_debug_wcdr_txbst_pu_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wcdr_txbst_pu_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txbst_pd_d0, u8"mc_io_debug_dqb0l_txbst_pd_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txbst_pd_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txbst_pd_d1, u8"mc_io_debug_dqb0l_txbst_pd_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txbst_pd_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txbst_pu_d0, u8"mc_io_debug_dqb0l_txbst_pu_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txbst_pu_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_txbst_pu_d1, u8"mc_io_debug_dqb0l_txbst_pu_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_txbst_pu_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_ofscal_d0, u8"mc_io_debug_dbi_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_ofscal_d0, u8"mc_io_debug_edc_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_wck_ofscal_d0, u8"mc_io_debug_wck_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_wck_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_cdr_phsize_d0, u8"mc_io_debug_edc_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_acmd_ofscal_d0, u8"mc_io_debug_acmd_ofscal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_acmd_ofscal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_cdr_phsize_d0, u8"mc_io_debug_dbi_cdr_phsize_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_cdr_phsize_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dbi_rx_eq_d0, u8"mc_io_debug_dbi_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dbi_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_edc_rx_eq_d0, u8"mc_io_debug_edc_rx_eq_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_edc_rx_eq_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_cdrcntl_d0, u8"mc_io_cdrcntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_cdrcntl_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_cdrcntl1_d0, u8"mc_io_cdrcntl1_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_cdrcntl1_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_vref_cal_d0, u8"mc_io_debug_dqb0l_rx_vref_cal_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_vref_cal_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_dqb0l_rx_vref_cal_d1, u8"mc_io_debug_dqb0l_rx_vref_cal_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_dqb0l_rx_vref_cal_d1_6_0),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, mc_block_fiji_adjust, atui_nullstruct,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_rxframing_dbi_d1, u8"mc_seq_rxframing_dbi_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_rxframing_dbi_d1_6_0_o),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, mc_block_polaris_gddr5_type_1_adjust, atui_nullstruct,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc4, u8"mc_seq_misc4",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc4_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc5, u8"mc_seq_misc5",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc5_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_pad_cntl_d1, u8"mc_io_pad_cntl_d1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_pad_cntl_d1_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_flag, u8"mc_tsm_debug_flag",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_flag_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_aphy_str_cntl_d0, u8"mc_io_aphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_aphy_str_cntl_d0_6_0_o),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, mc_block_polaris_gddr5_type_2_adjust, atui_nullstruct,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc0, u8"mc_seq_misc0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc4, u8"mc_seq_misc4",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc4_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc5, u8"mc_seq_misc5",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc5_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_misc6, u8"mc_seq_misc6",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_misc6_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_seq_reserve_m, u8"mc_seq_reserve_m",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_reserve_m_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_flag, u8"mc_tsm_debug_flag",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_flag_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_tsm_debug_bcnt0, u8"mc_tsm_debug_bcnt0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_tsm_debug_bcnt0_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_debug_up_15, u8"mc_io_debug_up_15",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_debug_up_15_6_0),
		(ATUI_NODESCR)
	),
	(bios->mc_io_dphy_str_cntl_d0, u8"mc_io_dphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_dphy_str_cntl_d0_7_1),
		(ATUI_NODESCR)
	),
	(bios->mc_io_aphy_str_cntl_d0, u8"mc_io_aphy_str_cntl_d0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_io_aphy_str_cntl_d0_6_0_o),
		(ATUI_NODESCR)
	)
)
