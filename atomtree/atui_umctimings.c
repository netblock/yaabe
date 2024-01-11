/*
For umctimings.h
See atui_atomfirmware.c for how to use PPATUI_FUNCIFY()
*/

#include "atomtree.h"
#include "atui.h"

PPATUI_FUNCIFY(union, DRAMTiming1, atui_nullstruct,
	(bios->DRAMTiming1, "DRAMTiming1",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tCL",     5,0, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd0",   7,6, ATUI_DEC, (ATUI_NODESCR)),
			("tRAS",   14,8, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd1",  15,15, ATUI_DEC, (ATUI_NODESCR)),
			("tRCDRD", 21,16, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd2",  23,22, ATUI_DEC, (ATUI_NODESCR)),
			("tRCDWR", 29,24, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd3",  31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming2, atui_nullstruct,
	(bios->DRAMTiming2, "DRAMTiming2",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tRC_S",  7,0, ATUI_DEC, ((LANG_ENG, "per-bank"))),
			("tRC_L", 15,8, ATUI_DEC, ((LANG_ENG, "all-bank?"))),
			("tRP_S", 21,16, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd0", 23,22, ATUI_DEC, (ATUI_NODESCR)),
			("tRP_L", 29,24, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd1", 31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming3, atui_nullstruct,
	(bios->DRAMTiming3, "DRAMTiming3",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tRRD_S",  4,0, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd0",   7,5, ATUI_DEC, (ATUI_NODESCR)),
			("tRRD_L", 12,8, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd1",  23,13, ATUI_DEC,
				((LANG_ENG, "3+5+3, middle 5 has tRRDDLR for 3D stacked memory."))
			),
			("tRTP",   28,24, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd2",  31,29, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming4, atui_nullstruct,
	(bios->DRAMTiming4, "DRAMTiming4",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tFAW",   6,0, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd0",  7,7, ATUI_DEC, (ATUI_NODESCR)),
			("t32AW", 16,8, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd1", 31,17, ATUI_DEC,
				((LANG_ENG, "1, tFAWSLR:6, 1, tFAWDLR:6, 1")))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming5, atui_nullstruct,
	(bios->DRAMTiming5, "DRAMTiming5",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tWL",    5,0, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd0",  7,6, ATUI_DEC, (ATUI_NODESCR)),
			("tWTRS", 12,8, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd1", 15,13, ATUI_DEC, (ATUI_NODESCR)),
			("tWTRL", 22,16, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd2", 31,23, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming6, atui_nullstruct,
	(bios->DRAMTiming6, "DRAMTiming6",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tWR",    6,0, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd0", 31,7, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming7, atui_nullstruct,
	(bios->DRAMTiming7, "DRAMTiming7",
		(ATUI_BIN, ATUI_BITFIELD, (
			("PPD",      2,0, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd0",    3,3, ATUI_DEC, (ATUI_NODESCR)),
			("tCRCRL",   6,4, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd1",    7,7, ATUI_DEC, (ATUI_NODESCR)),
			("tRREFD",  13,8, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd2",   14,14, ATUI_DEC, (ATUI_NODESCR)),
			("tCRCWL",  19,15, ATUI_DEC, (ATUI_NODESCR)),
			("tRCPAGE", 31,20, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming8, atui_nullstruct,
	(bios->DRAMTiming8, "DRAMTiming8",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tRDRD_DD",   3,0, ATUI_DEC,
				((LANG_ENG, "Different DIMM"))
			),
			("rsvd0",      7,4, ATUI_DEC, (ATUI_NODESCR)),
			("tRDRD_SD",  11,8, ATUI_DEC,
				((LANG_ENG, "Same DIMM"))
			),
			("rsvd1",     15,12, ATUI_DEC, (ATUI_NODESCR)),
			("tRDRD_SC",  19,16, ATUI_DEC,
				((LANG_ENG, "JEDEC tCCD_S"))
			),
			("rsvd2",     23,20, ATUI_DEC, (ATUI_NODESCR)),
			("tRDRD_SCL", 27,24, ATUI_DEC,
				((LANG_ENG, "tCCD_L"))
			),
			("rsvd3",     29,28, ATUI_DEC, (ATUI_NODESCR)),
			("tRDRD_BAN", 31,30, ATUI_DEC,
				((LANG_ENG, "Preamble2t ?1:0. Ban traffic:1=tCCD=5;2=tCCD=5,6"))
			)
		)),
		((LANG_ENG, "Specifies the minimum number of cycles from the last clock of virtual CAS of the first burst operation to the clock in which CAS is asserted for a following bust operation. A value of 1 means 0 idle clock cycles between two bursts; 2 = 1 idle cycle."))
	)
)


PPATUI_FUNCIFY(union, DRAMTiming9_HBM2, atui_nullstruct,
	(bios->DRAMTiming9, "DRAMTiming9",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tWRWR_DD",   3,0, ATUI_DEC,
				((LANG_ENG, "Different DIMM"))
			),
			("rsvd0",      7,4, ATUI_DEC, (ATUI_NODESCR)),
			("tWRWR_SD",  11,8, ATUI_DEC,
				((LANG_ENG, "Same DIMM"))
			),
			("rsvd1",     15,12, ATUI_DEC, (ATUI_NODESCR)),
			("tWRWR_SC",  19,16, ATUI_DEC,
				((LANG_ENG, "JEDEC tCCD_S"))
			),
			("rsvd2",     23,20, ATUI_DEC, (ATUI_NODESCR)),
			("tWRWR_SCL", 27,24, ATUI_DEC,
				((LANG_ENG, "tCCD_L"))
			),
			("rsvd3",     29,28, ATUI_DEC, (ATUI_NODESCR)),
			("tWRWR_BAN", 31,30, ATUI_DEC,
				((LANG_ENG, "Preamble2t ?1:0. Ban traffic:1=tCCD=5;2=tCCD=5,6"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming9, atui_nullstruct,
	(bios->DRAMTiming9, "DRAMTiming9",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tWRWR_MW",   4,0, ATUI_DEC, ((LANG_ENG, "masked write; GDDR"))),
			("rsvd0",     15,5, ATUI_DEC, (ATUI_NODESCR)),
			("tWRWR_SC",  19,16, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd1",     23,20, ATUI_DEC, (ATUI_NODESCR)),
			("tWRWR_SCL", 29,24, ATUI_DEC, (ATUI_NODESCR)),
			("tWRWR_BAN", 31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming10, atui_nullstruct,
	(bios->DRAMTiming10, "DRAMTiming10",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tWRRD",       3,0, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd0",       7,4, ATUI_DEC, (ATUI_NODESCR)),
			("tRDWR",      13,8, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd1",      15,14, ATUI_DEC, (ATUI_NODESCR)),
			("RDRspDelay", 21,16, ATUI_DEC, (ATUI_NODESCR)),
			("tREFTTAdj",  28,22, ATUI_DEC,
				((LANG_ENG, "was tREFTT; a typo? tREFTR is a GDDR6 timing"))
			),
			("rsvd2",      31,29, ATUI_DEC, (ATUI_NODESCR))
		)),
		((LANG_ENG, "tWRRD and tRDWR also follows the 'last clock of virtual CAS'. LD = tCL - tCWL ; tWRRD has x-LD and tRDWR has y+LD. LD is about making sure one burst happens after the other. And x and y follow the 'last clock of virtual CAS' and are about making sure the data bus is stable."))
	)
)


PPATUI_FUNCIFY(union, DRAMTiming12, atui_nullstruct,
	(bios->DRAMTiming12, "DRAMTiming12",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tREFI", 15,0, ATUI_DEC,
				((LANG_ENG, "tREF; the microseconds not milliseconds one"))
			),
			("rsvd0", 31,16, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming13, atui_nullstruct,
	(bios->DRAMTiming13, "DRAMTiming13",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tMRD",   5,0, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd0",  7,6, ATUI_DEC, (ATUI_NODESCR)),
			("tMOD",  13,8, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd1", 31,14, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming14_HBM2, atui_nullstruct,
	(bios->DRAMTiming14, "DRAMTiming14",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tXS",   10,0, ATUI_DEC,
				((LANG_ENG, "exit self refreh to not requiring a locked DLL"))
			),
			("rsvd0", 31,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming14, atui_nullstruct,
	(bios->DRAMTiming14, "DRAMTiming14",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tXS",   10,0, ATUI_DEC,
				((LANG_ENG, "exit self refreh to not requiring a locked DLL"))
			),
			("rsvd0", 15,11, ATUI_DEC, (ATUI_NODESCR)),
			("tDLLK", 26,16, ATUI_DEC,
				((LANG_ENG, "exit self refresh to requiring a locked DLL"))
			),
			("rsvd1", 31,27, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming15, atui_nullstruct,
	(bios->DRAMTiming15, "DRAMTiming15",
		(ATUI_BIN, ATUI_BITFIELD, (
			("AlertCrcDly",  6,0, ATUI_DEC,
				((LANG_ENG, "expected alert crc error dely, in memclocks"))
			),
			("rsvd0",        7,7, ATUI_DEC, (ATUI_NODESCR)),
			("AlertParDly", 14,8, ATUI_DEC,
				((LANG_ENG, "Parity error"))
			),
			("PL",          18,15, ATUI_DEC,
				((LANG_ENG, "Cmd/Addr Parity Latency. See DDR4 MR5"))
			),
			("rsvd1",       22,19, ATUI_DEC, (ATUI_NODESCR)),
			("RankBusyDly", 29,23, ATUI_DEC,
				((LANG_ENG, "max of CRC/ECC alert delays"))
			),
			("rsvd2",       31,30, ATUI_DEC, (ATUI_NODESCR))
		)),
		((LANG_ENG, "DDR reliability RAS"))
	)
)


PPATUI_FUNCIFY(union, DRAMTiming16, atui_nullstruct,
	(bios->DRAMTiming16, "DRAMTiming16",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tXSMRS", 10,0, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd0",  31,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming17_HBM2, atui_nullstruct,
	(bios->DRAMTiming17, "DRAMTiming17",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tPD",           3,0, ATUI_DEC, (ATUI_NODESCR)),
			("tCKSRE",        9,4, ATUI_DEC, (ATUI_NODESCR)),
			("tCKSRX",        15,10, ATUI_DEC, (ATUI_NODESCR)),
			("PwrDownDly",    23,16, ATUI_DEC,
				((LANG_ENG, "last command to PowerDown"))
			),
			("AggPwrDownDly", 29,24, ATUI_DEC,
				((LANG_ENG, "last DRAM activity to precharge, for PD"))
			),
			("rsvd2",         31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming17, atui_nullstruct,
	(bios->DRAMTiming17, "DRAMTiming17",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tPD",           4,0, ATUI_DEC, (ATUI_NODESCR)),
			("tCKSRE",        10,5, ATUI_DEC, (ATUI_NODESCR)),
			("tCKSRX",        16,11, ATUI_DEC, (ATUI_NODESCR)),
			("PwrDownDly",    24,17, ATUI_DEC,
				((LANG_ENG, "last command to PowerDown"))
			),
			("AggPwrDownDly", 30,25, ATUI_DEC,
				((LANG_ENG, "last DRAM activity to precharge, for PD"))
			),
			("rsvd0",         31,31, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming18_HBM2, atui_nullstruct,
	(bios->DRAMTiming18, "DRAMTiming18",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tRFCSB", 10,0, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd0",  15,11, ATUI_DEC, (ATUI_NODESCR)),
			("tSTAG",  23,16, ATUI_DEC,
				((LANG_ENG, "ref-to-ref different rank"))),
			("rsvd1",  31,24, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming20, atui_nullstruct,
	(bios->DRAMTiming20, "DRAMTiming20",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tRFCSB", 10,0, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd0",  15,11, ATUI_DEC, (ATUI_NODESCR)),
			("tSTAG",  23,16, ATUI_DEC,
				((LANG_ENG, "ref-to-ref different rank"))),
			("rsvd1",  31,24, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming21, atui_nullstruct,
	(bios->DRAMTiming21, "DRAMTiming21",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tXP",     5,0, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd0",  15,6, ATUI_DEC, (ATUI_NODESCR)),
			("tCPDED", 19,16, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd1",  23,20, ATUI_DEC, (ATUI_NODESCR)),
			("tCKE",   28,24, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd2",  31,29, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming22_HBM2, atui_nullstruct,
	(bios->DRAMTiming22, "DRAMTiming22",
		(ATUI_BIN, ATUI_BITFIELD, (
			("rsvd0_0",      1,0, ATUI_DEC,
				((LANG_ENG, "makes n=3,3"))
			),
			("tRDDATA_EN",   6,2, ATUI_DEC,
				((LANG_ENG, "tCL-n; GD6 n=1, D4 n=5. READ to dfi_rddata_en"))
			),
			("rsvd0",        7,7, ATUI_DEC, (ATUI_NODESCR)),
			("tPHY_WRLAT",  12,8, ATUI_DEC,
				((LANG_ENG, "tCWL-n; GD6 n=2, D4 n=5. WRITE to dfi_wrdata_en"))
			),
			("rsvd1",       15,13, ATUI_DEC, (ATUI_NODESCR)),
			("tPHY_RDLAT",  21,16, ATUI_DEC,
				((LANG_ENG, "dfi_rddata_en to dfi_rddata_vld dely"))
			),
			("rsvd2",       23,22, ATUI_DEC, (ATUI_NODESCR)),
			("tPHY_WRDATA", 26,24, ATUI_DEC,
				((LANG_ENG, "dfi_wrdata_en to dfi_wrdata delay"))
			),
			("rsvd3",       27,27, ATUI_DEC, (ATUI_NODESCR)),
			("tPARIN_LAT",  29,28, ATUI_DEC,
				((LANG_ENG, "ctrl signals to parity delay"))
			),
			("rsvd4",       31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming22, atui_nullstruct,
	(bios->DRAMTiming22, "DRAMTiming22",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tRDDATA_EN",   6,0, ATUI_DEC,
				((LANG_ENG, "tCL-n; GD6 n=1, D4 n=5. READ to dfi_rddata_en"))
			),
			("rsvd0",        7,7, ATUI_DEC, (ATUI_NODESCR)),
			("tPHY_WRLAT",  12,8, ATUI_DEC,
				((LANG_ENG, "tCWL-n; GD6 n=2, D4 n=5. WRITE to dfi_wrdata_en"))
			),
			("rsvd1",       15,13, ATUI_DEC, (ATUI_NODESCR)),
			("tPHY_RDLAT",  21,16, ATUI_DEC,
				((LANG_ENG, "dfi_rddata_en to dfi_rddata_vld dely"))
			),
			("rsvd2",       23,22, ATUI_DEC, (ATUI_NODESCR)),
			("tPHY_WRDATA", 26,24, ATUI_DEC,
				((LANG_ENG, "dfi_wrdata_en to dfi_wrdata delay"))
			),
			("rsvd3",       27,27, ATUI_DEC, (ATUI_NODESCR)),
			("tPARIN_LAT",  29,28, ATUI_DEC,
				((LANG_ENG, "ctrl signals to parity delay"))
			),
			("rsvd4",       31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, DRAMTiming23, atui_nullstruct,
	(bios->DRAMTiming23, "DRAMTiming23",
		(ATUI_BIN, ATUI_BITFIELD, (
			("LpDly",      5,0, ATUI_DEC,
				((LANG_ENG, "hysteresis before placing PHY into low power"))
			),
			("rsvd0",      7,6, ATUI_DEC, (ATUI_NODESCR)),
			("LpExitDly",  13,8, ATUI_DEC,
				((LANG_ENG, "min memclk before taking a rank out of powerdown"))
			),
			("rsvd1",      15,14, ATUI_DEC, (ATUI_NODESCR)),
			("CKESTAGDLY", 19,16, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd3",      31,20, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming34, atui_nullstruct,
	(bios->DRAMTiming34, "DRAMTiming34",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tPhyupd_resp", 3,0, ATUI_DEC, (ATUI_NODESCR)),
			("tRDEDC_EN",    10,4, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd0",        11,11, ATUI_DEC, (ATUI_NODESCR)),
			("tWREDC_EN",    18,12, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd1",        31,19, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming35, atui_nullstruct,
	(bios->DRAMTiming35, "DRAMTiming35",
		(ATUI_BIN, ATUI_BITFIELD, (
			("ReceiverWait", 10,0, ATUI_DEC,
				((LANG_ENG, "Wait time to start recovery sequence"))
			),
			("CmdStageCnt",  21,11, ATUI_DEC,
				((LANG_ENG, "Recov. seq. cmd stagger counter. See CmdStgFrc. CmdStgFrc:1; 1=enable recovery command stagger in recovery phase"))
			),
			("rsvd0",        23,22, ATUI_DEC, (ATUI_NODESCR)),
			("tWRMPR",       29,24, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd1",        31,30, ATUI_DEC, (ATUI_NODESCR))
		)),
		((LANG_ENG, "reliability RAS"))
	)
)


PPATUI_FUNCIFY(union, DRAMTiming36, atui_nullstruct,
	(bios->DRAMTiming36, "DRAMTiming36",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tWTRTR",     5,0, ATUI_DEC, ((LANG_ENG, "WRITE to WRTR"))),
			("tREFTR",     11,6, ATUI_DEC,
				((LANG_ENG, "was named tREFTT. REFab to RDTR/WRTR"))),
			("tTTROW",     17,12, ATUI_DEC, ((LANG_ENG, "??"))),
			("tLDTLD",     23,18, ATUI_DEC, ((LANG_ENG, "JEDEC tLTLTR?"))),
			("tUPDN",      29,24, ATUI_DEC, ((LANG_ENG, "??"))),
			("tREFTR_MSB", 30,30, ATUI_DEC, ((LANG_ENG, "was named tREFTT"))),
			("rsvd0",      31,31, ATUI_DEC, (ATUI_NODESCR))
		)), ((LANG_ENG, "GDDR training"))
	)
)


PPATUI_FUNCIFY(union, TRFCTimingCS01, atui_nullstruct,
	(bios->TRFCTimingCS01, "TRFCTimingCS01",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tRFC",  10,0, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd0", 31,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, TRFCTimingCS01_DDR4, atui_nullstruct,
	(bios->TRFCTimingCS01_DDR4, "TRFCTimingCS01_DDR4",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tRFC",  10,0, ATUI_DEC, (ATUI_NODESCR)),
			("tRFC2", 21,11, ATUI_DEC, (ATUI_NODESCR)),
			("tRFC4", 31,22, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, ChanPipeDly, atui_nullstruct,
	(bios->ChanPipeDly, "ChanPipeDly",
		(ATUI_BIN, ATUI_BITFIELD, (
			("TXCtrlChanDly", 2,0, ATUI_DEC,
				((LANG_ENG, "# of delay stages on DFI control from UMC to PHY"))
			),
			("rsvd0",         3,3, ATUI_DEC, (ATUI_NODESCR)),
			("TXDataChanDly", 6,4, ATUI_DEC,
				((LANG_ENG, "... on DFI write data from UMC to PHY"))
			),
			("rsvd1",         7,7, ATUI_DEC, (ATUI_NODESCR)),
			("RXDataChanDly",10,8, ATUI_DEC,
				((LANG_ENG, "... on DFI read data from PHY to UMC"))
			),
			("rsvd2",        31,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, umc_block_vega10_timings, atomtree_vram_info_header_v2_3,
	(bios->block_id, "block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming1, "DRAMTiming1",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming1),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming2, "DRAMTiming2",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming3, "DRAMTiming3",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming3),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming4, "DRAMTiming4",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming4),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming5, "DRAMTiming5",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming5),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming6, "DRAMTiming6",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming6),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming7, "DRAMTiming7",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming7),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming8, "DRAMTiming8",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming8),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming9, "DRAMTiming9",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming9_HBM2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming10, "DRAMTiming10",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming10),
		(ATUI_NODESCR)
	),

	(bios->DRAMTiming12, "DRAMTiming12",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming12),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming13, "DRAMTiming13",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming13),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming14, "DRAMTiming14",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming14_HBM2),
		(ATUI_NODESCR)
	),
	(bios->unknown15, "unknown15",
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, "unsure"))
	),
	(bios->DRAMTiming16, "DRAMTiming16",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming16),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming17, "DRAMTiming17",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming17_HBM2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming18, "DRAMTiming18",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming18_HBM2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming21, "DRAMTiming21",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming21),
		(ATUI_NODESCR)
	),
	(bios->unknown19, "unknown19",
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, "unsure"))
	),
	(bios->unknown20, "unknown20",
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, "unsure"))
	),
	(bios->tRFC, "tRFC",
		(ATUI_NODISPLAY, ATUI_INLINE, TRFCTimingCS01),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming22, "DRAMTiming22",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming22_HBM2),
		(ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, umc_block_vega21_timings, atomtree_vram_info_header_v2_3,
	(bios->block_id, "block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming1, "DRAMTiming1",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming1),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming2, "DRAMTiming2",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming3, "DRAMTiming3",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming3),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming4, "DRAMTiming4",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming4),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming5, "DRAMTiming5",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming5),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming6, "DRAMTiming6",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming6),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming7, "DRAMTiming7",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming7),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming8, "DRAMTiming8",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming8),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming9, "DRAMTiming9",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming9_HBM2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming10, "DRAMTiming10",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming10),
		(ATUI_NODESCR)
	),

	(bios->DRAMTiming12, "DRAMTiming12",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming12),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming13, "DRAMTiming13",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming13),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming14, "DRAMTiming14",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming14_HBM2),
		(ATUI_NODESCR)
	),
	(bios->unknown15, "unknown15",
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, "unsure"))
	),
	(bios->DRAMTiming16, "DRAMTiming16",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming16),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming17, "DRAMTiming17",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming17_HBM2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming18, "DRAMTiming18",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming18_HBM2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming21, "DRAMTiming21",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming21),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming22, "DRAMTiming22",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming22),
		(ATUI_NODESCR)
	),
	(bios->unknown23, "unknown23",
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, "unsure"))
	),
	(bios->tRFC, "tRFC",
		(ATUI_NODISPLAY, ATUI_INLINE, TRFCTimingCS01),
		(ATUI_NODESCR)
	),
	(bios->ChanPipeDly, "ChanPipeDly",
		(ATUI_NODISPLAY, ATUI_INLINE, ChanPipeDly),
		(ATUI_NODESCR)
	),
	(bios->unkown24, "unkown24",
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, "unsure"))
	)
)

PPATUI_FUNCIFY(struct, umc_block_navi1_timings, atomtree_vram_info_header_v2_4,

	(bios->block_id, "block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),

	(bios->gddr6_mr5.gddr6_mr5, "gddr6_mr5",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr5),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr5.reserved, "gddr6_mr5_reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gddr6_mr0.gddr6_mr0, "gddr6_mr0",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr0),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr0.reserved, "gddr6_mr0_reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->UMCCTRL_PMG_CMD_EMRS, "UMCCTRL_PMG_CMD_EMRS",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gddr6_mr4.gddr6_mr4, "gddr6_mr4",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr4),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr4.reserved, "gddr6_mr4_reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gddr6_mr8.gddr6_mr8, "gddr6_mr8",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr8),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr8.reserved, "gddr6_mr8_reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DRAMTiming1, "DRAMTiming1",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming1),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming2, "DRAMTiming2",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming3, "DRAMTiming3",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming3),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming4, "DRAMTiming4",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming4),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming5, "DRAMTiming5",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming5),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming6, "DRAMTiming6",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming6),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming7, "DRAMTiming7",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming7),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming8, "DRAMTiming8",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming8),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming9, "DRAMTiming9",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming9),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming10, "DRAMTiming10",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming10),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming12, "DRAMTiming12",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming12),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming13, "DRAMTiming13",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming13),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming14, "DRAMTiming14",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming14),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming16, "DRAMTiming16",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming16),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming17, "DRAMTiming17",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming17),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming20, "DRAMTiming20",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming20),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming21, "DRAMTiming21",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming21),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming22, "DRAMTiming22",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming22),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming23, "DRAMTiming23",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming23),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming35, "DRAMTiming35",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming35),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming36, "DRAMTiming36",
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming36),
		(ATUI_NODESCR)
	),
	(bios->tRFC, "tRFC",
		(ATUI_NODISPLAY, ATUI_INLINE, TRFCTimingCS01),
		(ATUI_NODESCR)
	),
	(bios->ChanPipeDly, "ChanPipeDly",
		(ATUI_NODISPLAY, ATUI_INLINE, ChanPipeDly),
		(ATUI_NODESCR)
	)
)
