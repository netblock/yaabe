/*
For ddrmoderegisters.h
See atui_atomfirmware.c for how to use PPATUI_FUNCIFY()
*/

#include "atomtree.h"
#include "atui.h"

PPATUI_FUNCIFY(union, ddr1_mr0, atui_nullstruct,
	(bios->ddr1_mr0, "ddr1_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			("burst_length",    2,0, ATUI_DEC,
				((LANG_ENG, "1=BL2, 2=BL4, 3=BL8; all else reserved"))
			),
			("burst_type",      3,3, ATUI_DEC,
				((LANG_ENG, "0=sequential, 1=interleave"))
			),
			("tCL",             6,4, ATUI_DEC,
				((LANG_ENG, "2=2,3=3, 5=1.5,6=2.5, all else reseved"))
			),
			("test_mode",       7,7, ATUI_DEC,
				((LANG_ENG, "behaviour is vendor specific"))
			),
			("DLL_reset",       8,8, ATUI_DEC,
				((LANG_ENG, "self clearing"))
			),
			("operating_rsvd", 13,9, ATUI_DEC,
				((LANG_ENG, "operation_mode reserved"))
			),
			("ID",             15,14, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, ddr1_emr1, atui_nullstruct,
	(bios->ddr1_emr1, "ddr1_emr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			("DLL",              0,0, ATUI_DEC,
				((LANG_ENG, "0=enable"))
			),
			("drive_strength",   1,1, ATUI_DEC,
				((LANG_ENG, "0=full, 1=reduced; (see SSTL_2, Class II)"))
			),
			("reserved",         2,2, ATUI_DEC,
				((LANG_ENG, "compatibility with early DDR1"))
			),
			("operating_rsvd",  13,3, ATUI_DEC, (ATUI_NODESCR)),
			("ID",              15,14, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, ddr2_mr0, atui_nullstruct,
	(bios->ddr2_mr0, "ddr2_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			("burst_length",  2,0, ATUI_DEC,
				((LANG_ENG, "2=BL4, 3=BL8; all else reserved"))
			),
			("burst_type",    3,3, ATUI_DEC,
				((LANG_ENG, "0=sequential, 1=interleave"))
			),
			("tCL",           6,4, ATUI_DEC,
				((LANG_ENG, "tCL=n; 0,1,7=reserved"))
			),
			("test_mode",     7,7, ATUI_DEC,
				((LANG_ENG, "behaviour is vendor specific"))
			),
			("DLL_reset",     8,8, ATUI_DEC,
				((LANG_ENG, "self clearing"))
			),
			("WR",           11,9, ATUI_DEC,
				((LANG_ENG, "tWR = n+1"))
			),
			("PD_exit_time", 12,12, ATUI_DEC,
				((LANG_ENG, "0=fast, 1=slow"))
			),
			("rsvd_15_13",   15,13, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, ddr2_emr1, atui_nullstruct,
	(bios->ddr2_emr1, "ddr2_emr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			("DLL",              0,0, ATUI_DEC,
				((LANG_ENG, "0=enable"))
			),
			("drive_strength",   1,1, ATUI_DEC,
				((LANG_ENG, "0=full, 1=reduced"))
			),
			("RTT_Nom_lo_bit",   2,2, ATUI_DEC,
				((LANG_ENG, "A[6,2] -> Nom[1:0]"))
			),
			("Additive_Latency", 5,3, ATUI_DEC,
				((LANG_ENG, "0=0...  6+=reserved"))
			),
			("RTT_Nom_hi_bit",   6,6, ATUI_DEC,
				((LANG_ENG, "0=disabled, 1=75 ohms, 2=150, 3=50"))
			),
			("OCD_calibration",  9,7, ATUI_DEC,
				((LANG_ENG, "0=exit,1=drive1,2=drive2,4=adjust,7=default"))
			),
			("DQS",             10,10, ATUI_DEC,
				((LANG_ENG, "0=enable"))
			),
			("RDQS",            11,11, ATUI_DEC,
				((LANG_ENG, "0=disable"))
			),
			("output_disable",  12,12, ATUI_DEC,
				((LANG_ENG, "1=turn off drivers for DQ, DQS, RDQS"))
			),
			("rsvd_15_13",      15,13, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, ddr2_emr2, atui_nullstruct,
	(bios->ddr2_emr2, "ddr2_emr2",
		(ATUI_BIN, ATUI_BITFIELD, (
			("PASR",        2,0, ATUI_DEC,
				((LANG_ENG, "0=full (BA[2:0]=xxx), 0xx, 00x, 000, 3/4 (>1), 1xx, 11x, 111"))
			),
			("DCC",         3,3, ATUI_DEC,
				((LANG_ENG, "0=disable; Duty Cycle Correction"))
			),
			("rsvd_6_4",    6,4, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("HT_SRF",      7,7, ATUI_DEC,
				((LANG_ENG, "0=disable; hi-temp self-refresh mode"))
			),
			("rsvd_12_8",  12,8, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("rsvd_15_13", 15,13, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, ddr2_emr3, atui_nullstruct,
	(bios->ddr2_emr3, "ddr2_emr3",
		(ATUI_BIN, ATUI_BITFIELD, (
			("rsvd_15_0",  15,0, ATUI_DEC,
				((LANG_ENG, "all reserved"))
			)
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, ddr3_mr0, atui_nullstruct,
	(bios->ddr3_mr0, "ddr3_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			("burst_length",    1,0, ATUI_DEC,
				((LANG_ENG, "0=BL8, 1=OTF 4/8, 2=BC4, 3=reserved"))
			),
			("CL_hi_bit",       2,2, ATUI_DEC,
				((LANG_ENG, "A[2,6,5,4] -> CL[4:0]"))
			),
			("read_burst_type", 3,3, ATUI_DEC,
				((LANG_ENG, "0=nibble sequential, 1=interleave"))
			),
			("CL_lo_bits",      6,4, ATUI_DEC,
				((LANG_ENG, "tCL = 4+n"))
			),
			("testmode",        7,7, ATUI_DEC,
				((LANG_ENG, "behaviour is vendor specific"))
			),
			("DLL_reset",       8,8, ATUI_DEC,
				((LANG_ENG, "self clearing"))
			),
			("WR",             11,9, ATUI_DEC,
				((LANG_ENG, "tWR; 16,5,6,7,8,10,12,14"))
			),
			("DLL_PPD",        12,12, ATUI_DEC,
				((LANG_ENG, "0=slow exit (DLL off), 1=fast (DLL on)"))
			),
			("RFU_15_13",      15,13, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, ddr3_mr1, atui_nullstruct,
	(bios->ddr3_mr1, "ddr3_mr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			("DLL",              0,0, ATUI_DEC,
				((LANG_ENG, "0=enable"))
			),
			("DrvStr_lo_bit",    1,1, ATUI_DEC,
				((LANG_ENG, "0=RZQ/6, 1=RZQ/7"))
			),
			("RTTNom_lo_bit",    2,2, ATUI_DEC,
				((LANG_ENG, "A[9,6,2] -> RTT_Nom[2:0]"))
			),
			("Additive_Latency", 4,3, ATUI_DEC,
				((LANG_ENG, "0=0, 1=tCL-1, 2=tCL-2, 3=reserved"))
			),
			("DrvStr_hi_bit",    5,5, ATUI_DEC,
				((LANG_ENG, "A[5,1] -> DrvStr[1:0]; 2,3=reserved"))
			),
			("RTTNom_mid_bit",   6,6, ATUI_DEC,
				((LANG_ENG, "0=dis, RZQ/4, /2, /6, /12, /8,  6,7=rsvd"))
			),
			("write_leveling",   7,7, ATUI_DEC,
				((LANG_ENG, "0=disabled"))
			),
			("RFU_8",            8,8, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("RTTNom_hi_bit",    9,9, ATUI_DEC,
				((LANG_ENG, "2,4,6 only if writelevel on and drivers on"))
			),
			("RFU_10",          10,10, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("TDQS",            11,11, ATUI_DEC,
				((LANG_ENG, "0=disabled; Termination Data Strobe pins"))
			),
			("output_disable",  12,12, ATUI_DEC,
				((LANG_ENG, "1=turn off drivers for DQ, DQS, DQS#"))
			),
			("RFU_15_13",       15,13, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, ddr3_mr2, atui_nullstruct,
	(bios->ddr3_mr2, "ddr3_mr2",
		(ATUI_BIN, ATUI_BITFIELD, (
			("PASR",       2,0, ATUI_DEC,
				((LANG_ENG, "0=full (BA[2:0]=xxx), 0xx, 00x, 000, 3/4 (>1), 1xx, 11x, 111"))
			),
			("CWL",        5,3, ATUI_DEC,
				((LANG_ENG, "tCWl = 5+n"))
			),
			("ASR",        6,6, ATUI_DEC,
				((LANG_ENG, "0=manual; auto self refresh"))
			),
			("SRT",        7,7, ATUI_DEC,
				((LANG_ENG, "0=normal, 1=extended; self refresh temp range"))
			),
			("RFU_8",      8,8, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("RTT_WR",    10,9, ATUI_DEC,
				((LANG_ENG, "0=off, RZQ/4, /2, reserved"))
			),
			("RFU_15_11", 15,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, ddr3_mr3, atui_nullstruct,
	(bios->ddr3_mr3, "ddr3_mr3",
		(ATUI_BIN, ATUI_BITFIELD, (
			("MPR_location",  1,0, ATUI_DEC,
				((LANG_ENG, "0=predefined pattern for read sync, 1,2,3=RFU"))
			),
			("MPR_operation", 2,2, ATUI_DEC,
				((LANG_ENG, "0=normal, 1=dataflow from MPR"))
			),
			("RFU_15_3",     15,3, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, gddr2_mr0, atui_nullstruct,
	(bios->gddr2_mr0, "gddr2_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			("burst_length", 0,0, ATUI_DEC,
				((LANG_ENG, "0=4, 1=reserved"))
			),
			("WL",           3,0, ATUI_DEC,
				((LANG_ENG, "1=1..7=7; 0=reserved"))
			),
			("RL",           6,4, ATUI_DEC,
				((LANG_ENG, "8,9,10,rsvd,4,5,6,7"))
			),
			("testmode",     7,7, ATUI_DEC,
				((LANG_ENG, "behaviour is vendor specific"))
			),
			("DLL_reset",    8,8, ATUI_DEC,
				((LANG_ENG, "self clearing"))
			),
			("WR",          11,9, ATUI_DEC,
				((LANG_ENG, "tWR=n+1; 0,1,7=reserved"))
			),
			("rsvd_15_12",  15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr2_emr1, atui_nullstruct,
	(bios->gddr2_emr1, "gddr2_emr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			("addrcmd_ODT",      1,0, ATUI_DEC,
				((LANG_ENG, "0=off 1=1xDQ, 2=2x, 3=4xDQ"))
			),
			("data_ck_ODT",      3,2, ATUI_DEC,
				((LANG_ENG, "0=off, 1=auto cal., 2=60ohms, 3=120"))
			),
			("additive_latency", 4,4, ATUI_DEC,
				((LANG_ENG, "0=0, 1=1"))
			),
			("DQS",              5,5, ATUI_DEC,
				((LANG_ENG, "0=differential, 1=single"))
			),
			("DLL",              6,6, ATUI_DEC,
				((LANG_ENG, "0=off, 1=on"))
			),
			("driver_Ron",       9,7, ATUI_DEC,
				((LANG_ENG, "0=60, 1=55 ... 7=25"))
			),
			("rankness",        10,10, ATUI_DEC,
				((LANG_ENG, "0=single 1=multi"))
			),
			("vendor_id",       11,11, ATUI_DEC,
				((LANG_ENG, "0=disabled 1=enabled"))
			),
			("rsvd_15_12",      15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr2_emr2, atui_nullstruct,
	(bios->gddr2_emr2, "gddr2_emr2",
		(ATUI_BIN, ATUI_BITFIELD, (
			("rsvd_1_0",         1,0, ATUI_DEC, (ATUI_NODESCR)),
			("ODT_at_powerdown", 2,2, ATUI_DEC,
				((LANG_ENG, "0=all off except CK, CKE, 1=EMRS/EMRS2"))
			),
			("low_power_mode",   3,3, ATUI_DEC,
				((LANG_ENG, "0=self-refresh, 1=fast wakeup"))
			),
			("CK_ODT",           5,4, ATUI_DEC,
				((LANG_ENG, "0=off, 1=1xDQ, 2=2x, 3=4xDQ"))
			),
			("CS_ODT",           7,6, ATUI_DEC,
				((LANG_ENG, "0=off, 1=0.5x addrcmd, 2=1x, 3=reserved"))
			),
			("CKE_ODT",          8,8, ATUI_DEC,
				((LANG_ENG, "0=off, 1=addrcmd"))
			),
			("ODT_W_mode",       9,9, ATUI_DEC,
				((LANG_ENG, "0=enable 1=disable. \"W\" mode??"))
			),
			("rsvd_11_10",      11,10, ATUI_DEC, (ATUI_NODESCR)),
			("rsvd_15_12",      15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, gddr3_mr0, atui_nullstruct,
	(bios->gddr3_mr0, "gddr3_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			("burst_length", 1,0, ATUI_DEC,
				((LANG_ENG, "0,1=RFU, 2=BL4, 3=BL8"))
			),
			("CL_hi_bit",    2,2, ATUI_DEC,
				((LANG_ENG, "A[2,6,5,4]->tCL[3:0] | JEDEC says A[3] is for BL; BL[2:0]"))
			),
			("burst_type",   3,3, ATUI_DEC,
				((LANG_ENG, "0=sequential 1=RFU"))
			),
			("CL_lo_bits",   6,4, ATUI_DEC,
				((LANG_ENG, "8,9,10,11,rsvd,5,6,7,12,13,14,15, rsvd..."))
			),
			("test_mode",    7,7, ATUI_DEC,
				((LANG_ENG, "behaviour is vendor specific"))
			),
			("DLL_reset",    8,8, ATUI_DEC,
				((LANG_ENG, "self clearing"))
			),
			("tWL",         11,9, ATUI_DEC,
				((LANG_ENG, "0=reserved; tCWL"))
			),
			("rsvd_15_12",  15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr3_emr1, atui_nullstruct, // page 14
	(bios->gddr3_emr1, "gddr3_emr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			("drive_strength",  1,0, ATUI_DEC,
				((LANG_ENG, "0=auto cal. 1=30ohms, 2=40, 3=50"))
			),
			("data_terminaton", 3,2, ATUI_DEC,
				((LANG_ENG, "0=ALL ODT disabled, 1=rsvd, 2=ZQ/4, 3=ZQ/2"))
			),
			("WR_lo_bits",      5,4, ATUI_DEC,
				((LANG_ENG, "A[7,5,4] -> WR[2:0]; 11,13,5,6,7,8,9,10"))
			),
			("DLL",             6,6, ATUI_DEC,
				((LANG_ENG, "0=enable"))
			),
			("rsvd_8_8",        8,8, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("R_on",            8,8, ATUI_DEC,
				((LANG_ENG, "0=40 ohms, 1=60 ohms; pull-up"))
			),
			("vendor_ID",      10,10, ATUI_DEC,
				((LANG_ENG, "0=off"))
			),
			("AddrCmd_term",   11,11, ATUI_DEC,
				((LANG_ENG, "0=inherit CKE, 1=CKE/2"))
			),
			("rsvd_15_12",     15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, gddr4_mr0, atui_nullstruct,
	(bios->gddr4_mr0, "gddr4_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			("WR",        2,0, ATUI_DEC,
				((LANG_ENG, "Write recovery; 16,18,20, 6,8,10,12,14"))
			),
			("tCL",       6,3, ATUI_DEC,
				((LANG_ENG, "16,17..21,22, 7,8,9..15"))
			),
			("testmode",  7,7, ATUI_DEC,
				((LANG_ENG, "behaviour is vendor specific"))
			),
			("DLL_reset", 8,8, ATUI_DEC,
				((LANG_ENG, "self clearing"))
			),
			("WL",       11,9, ATUI_DEC,
				((LANG_ENG, "write latency; 0=RFU, 1=1..7=7"))
			),
			("RFU_12",   12,12, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("ID",       15,13, ATUI_DEC,
				((LANG_ENG, "MR 0"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr4_emr1, atui_nullstruct,
	(bios->gddr4_emr1, "gddr4_emr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			("Drive_Term", 1,0, ATUI_DEC,
				((LANG_ENG, "0=auto cal., 2=nominal (no compensation), 1,3=RFU. (drive: 40 down/60 up ; termination: 60/120; CA 60/120/240)"))
			),
			("DQ_term",    3,2, ATUI_DEC,
				((LANG_ENG, "0=all off, 1=DQ off, 2=1/4, 3=1/2"))
			),
			("tPreamble",  6,4, ATUI_DEC,
				((LANG_ENG, "0=1..  5..7=RFU. read/write preamble in tCK"))
			),
			("DLL",        7,7, ATUI_DEC,
				((LANG_ENG, "0=enable"))
			),
			("read_DBI",   8,8, ATUI_DEC,
				((LANG_ENG, "0=disable. data bus iversion"))
			),
			("write_DBI",  9,9, ATUI_DEC,
				((LANG_ENG, "0=disable"))
			),
			("DBI_mode",  10,10, ATUI_DEC,
				((LANG_ENG, "0=DC, 1=AC. optimise for DC/AC power reduction"))
			),
			("Vendor_ID", 11,11, ATUI_DEC,
				((LANG_ENG, "0=disable"))
			),
			("RFU_12",    12,12, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("ID",        15,13, ATUI_DEC,
				((LANG_ENG, "EMR 1"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr4_emr2, atui_nullstruct,
	(bios->gddr4_emr2, "gddr4_emr2",
		(ATUI_BIN, ATUI_BITFIELD, (
			("OCD_down_offset", 2,0, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, "Two's Compl. Driver/term pulldown offset"))
			),
			("OCD_up_offset",   5,3, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, "Two's Compl. Driver/terminator pullup offset"))
			),
			("tRAS",           11,6, ATUI_DEC,
				((LANG_ENG, "tRAS latency; 0=RFU, 1=1..63=63"))
			),
			("RFU_12",         12,12, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("ID",             15,13, ATUI_DEC,
				((LANG_ENG, "EMR 2"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr4_emr3, atui_nullstruct,
	(bios->gddr4_emr3, "gddr4_emr3",
		(ATUI_BIN, ATUI_BITFIELD, (
			("RFU",           4,0, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("LP_term",       5,5, ATUI_DEC,
				((LANG_ENG, "0=disabled"))
			),
			("DRAM_info",     7,6, ATUI_DEC,
				((LANG_ENG, "0=vendor ID, 1=PERR_Info, 2,3=vendor specific"))
			),
			("parity_reset",  8,8, ATUI_DEC,
				((LANG_ENG, "0=store, 1=reset; clear PERR_Info"))
			),
			("parity_enable", 9,9, ATUI_DEC,
				((LANG_ENG, "0=disable"))
			),
			("parity_mask",  11,10, ATUI_DEC,
				((LANG_ENG, "0=DQ[7:0], 1=[15:8], 2=[23:16], 3=[31:24]"))
			),
			("RFU_12",       12,12, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("ID",           15,13, ATUI_DEC,
				((LANG_ENG, "EMR 3"))
			)
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, gddr5_mr0, atui_nullstruct,
	(bios->gddr5_mr0, "gddr5_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			("WLmrs",       2,0, ATUI_DEC,
				((LANG_ENG, "0=RFU 1=1..7=7"))
			),
			("CLmrs_lo",    6,3, ATUI_DEC,
				((LANG_ENG, "tCL = 5+n. [MR8[0], MR0[6:3]] -> tCL[4:0]"))
			),
			("testmode",    7,7, ATUI_DEC,
				((LANG_ENG, "behavior is vendor specific"))
			),
			("WR",         11,8, ATUI_DEC,
				((LANG_ENG, "tWR = 4+n. [MR8[1], MR0[11:8]] -> tWR[4:0]"))
			),
			("rsvd_15_12", 15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr1, atui_nullstruct,
	(bios->gddr5_mr1, "gddr5_mr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			("drive_strength",     1,0, ATUI_DEC,
				((LANG_ENG, "0=auto cal., 1,3=vendor, 2=nom (60/40)"))
			),
			("data_termination",   3,2, ATUI_DEC,
				((LANG_ENG, "0=disabled, 1=ZQ, 2=ZQ/2, 3=RFU"))
			),
			("addrcmd_term",       5,4, ATUI_DEC,
				((LANG_ENG, "0=inherit CKE_n, 1=ZQ, 2=ZQ/2, 3=disabled"))
			),
			("calibration_update", 6,6, ATUI_DEC,
				((LANG_ENG, "0=on; impedance calibration engine"))
			),
			("PLL_DLL",            7,7, ATUI_DEC,
				((LANG_ENG, "0=off"))
			),
			("read_DBI",           8,8, ATUI_DEC,
				((LANG_ENG, "0=on; data bus inversion"))
			),
			("write_DBI",          9,9, ATUI_DEC,
				((LANG_ENG, "0=on; data bus inversion"))
			),
			("address_BI",        10,10, ATUI_DEC,
				((LANG_ENG, "0=on; address bus inversion"))
			),
			("PLLDLL_reset",      11,11, ATUI_DEC,
				((LANG_ENG, "self clearing"))
			),
			("rsvd_15_12",        15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr2, atui_nullstruct,
	(bios->gddr5_mr2, "gddr5_mr2",
		(ATUI_BIN, ATUI_BITFIELD, (
			("drive_pulldown_offset", 2,0, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, "Two's Compl. vendor specific"))
			),
			("drive_pullup_offset",   5,3, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, "Two's Compl. vendor specific"))
			),
			("data_wck_term_offset",  8,6, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, "Two's Compl. vendor specific"))
			),
			("AddrCmd_term_offset",  11,9, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, "Two's Compl. vendor specific"))
			),
			("rsvd_15_12",           15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr3, atui_nullstruct,
	(bios->gddr5_mr3, "gddr5_mr3",
		(ATUI_BIN, ATUI_BITFIELD, (
			("self_refresh",    1,0, ATUI_DEC,
				((LANG_ENG, "0=32ms 1,2=vendor, 3=temp controlled"))
			),
			("WCK01_invert",    2,2, ATUI_DEC,
				((LANG_ENG, "phase invert"))
			),
			("WCK23_invert",    3,3, ATUI_DEC,
				((LANG_ENG, "phase invert"))
			),
			("WCK2CK_training", 4,4, ATUI_DEC,
				((LANG_ENG, "0=off; WCK to CK alignment training"))
			),
			("RDQS_mode",       5,5, ATUI_DEC,
				((LANG_ENG, "0=off; EDC becomes RDQS"))
			),
			("DRAM_info",       7,6, ATUI_DEC,
				((LANG_ENG, "0=off, 1=vendor ID, 2=temp, 3=vemdor spec."))
			),
			("WCK_termination", 9,8, ATUI_DEC,
				((LANG_ENG, "0=dis, 1=ZQ/2, 2=ZQ, 3=RFU"))
			),
			("bank_groups",    11,10, ATUI_DEC,
				((LANG_ENG, "0,1=off, 2=on tCCDL=4, 3=on tCCL=3"))
			),
			("rsvd_15_12",     15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr4, atui_nullstruct,
	(bios->gddr5_mr4, "gddr5_mr4",
		(ATUI_BIN, ATUI_BITFIELD, (
			("EDC_pattern",  3,0, ATUI_DEC,
				((LANG_ENG, "little-endian-based burst position"))
			),
			("CRCWL",        6,4, ATUI_DEC,
				((LANG_ENG, "7+n; CRC write latency"))
			),
			("CRCRL",        8,8, ATUI_DEC,
				((LANG_ENG, "4,1,2,3; CRC read laency"))
			),
			("read_CRC",     9,9, ATUI_DEC,
				((LANG_ENG, "0=on"))
			),
			("write_crc",   10,10, ATUI_DEC,
				((LANG_ENG, "0=on"))
			),
			("hold_invert", 11,11, ATUI_DEC,
				((LANG_ENG, "1=inverted; EDC hold pattern inversion"))
			),
			("rsvd_15_12",  15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr5, atui_nullstruct,
	(bios->gddr5_mr5, "gddr5_mr5",
		(ATUI_BIN, ATUI_BITFIELD, (
			("LP1",         0,0, ATUI_DEC,
				((LANG_ENG, "0=off; power saving, relaxed core"))
			),
			("LP2",         1,1, ATUI_DEC,
				((LANG_ENG, "0=off; power saving, WCK off during powerdown"))
			),
			("LP3",         2,2, ATUI_DEC,
				((LANG_ENG, "0=off; training during refresh disabled"))
			),
			("PLLDLL_BW",   5,3, ATUI_DEC,
				((LANG_ENG, "vendor specific; PLL bandwidth"))
			),
			("tRAS",       11,6, ATUI_DEC,
				((LANG_ENG, "0=RFU, 1=1..63=63"))
			),
			("rsvd_15_12", 15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr6, atui_nullstruct,
	(bios->gddr5_mr6, "gddr5_mr6",
		(ATUI_BIN, ATUI_BITFIELD, (
			("WCK2CK_alignment", 0,0, ATUI_DEC,
				((LANG_ENG, "0=inside DRAM, 1=at balls"))
			),
			("VREFD_merge",      1,1, ATUI_DEC,
				((LANG_ENG, "0=off 1=average VREFD and internal vref"))
			),
			("VREFD_training",   2,2, ATUI_DEC,
				((LANG_ENG, "0=ff 1=train; self clearing"))
			),
			("VREFD_source",     3,3, ATUI_DEC,
				((LANG_ENG, "0=VREFD pins, 1=internally generated"))
			),
			("VREFD_offset_MU",  7,4, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, "semi Two's Compl. -8 = 0/auto"))
			),
			("VREFD_offset_AF", 11,8, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, "semi Two's Compl. -8 = 0/auto"))
			),
			("rsvd_15_12",      15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr7, atui_nullstruct,
	(bios->gddr5_mr7, "gddr5_mr7",
		(ATUI_BIN, ATUI_BITFIELD, (
			("PLL_standby",     0,0, ATUI_DEC,
				((LANG_ENG, "0=off 1=standby when self-refresh"))
			),
			("PLL_fast_lock",   1,1, ATUI_DEC,
				((LANG_ENG, "1=faster lock but higher power; self clears"))
			),
			("PLL_delay_comp",  2,2, ATUI_DEC,
				((LANG_ENG, "1=PLL feedback = WCK clock tree delay"))
			),
			("low_freq_mode",   3,3, ATUI_DEC,
				((LANG_ENG, "1=reduced power for low freq"))
			),
			("WCK2CK_autosync", 4,4, ATUI_DEC,
				((LANG_ENG, "1=auto WCK2CK after PD exit"))
			),
			("DQ_preamble",     5,5, ATUI_DEC,
				((LANG_ENG, "1=non-gapped READs will have 4UI preamble"))
			),
			("temp_sensor",     6,6, ATUI_DEC,
				((LANG_ENG, "1=enable temperature sense"))
			),
			("half_VREFD",      7,7, ATUI_DEC,
				((LANG_ENG, "0=0.7x 1=0.5x VDDQ"))
			),
			("VDD_range",       9,8, ATUI_DEC,
				((LANG_ENG, "0=1.5V 1,2,3=vendor; adapt to different VDD"))
			),
			("DCC",            11,10, ATUI_DEC,
				((LANG_ENG, "0=off, 1=start, 2=reset, 3=RFU; Duty Cycle Correction"))
			),
			("rsvd_15_12",     15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr8, atui_nullstruct,
	(bios->gddr5_mr8, "gddr5_mr8",
		(ATUI_BIN, ATUI_BITFIELD, (
			("CL_EHF",      0,0, ATUI_DEC,
				((LANG_ENG, "tCL range extension; see MR0"))
			),
			("WR_EHF",      1,1, ATUI_DEC,
				((LANG_ENG, "tWR range extension; see MR0"))
			),
			("EDC_HiZ",     2,2, ATUI_DEC,
				((LANG_ENG, "1=Hi-Z state; precedence over all other states"))
			),
			("REFPB",       3,3, ATUI_DEC,
				((LANG_ENG, "1=per-bank refresh feature enable"))
			),
			("rsvd_11_4",  11,4, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("rsvd_15_12", 15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr9, atui_nullstruct,
	(bios->gddr5_mr9, "gddr5_mr9",
		(ATUI_BIN, ATUI_BITFIELD, (
			("vendor_specific", 11,0, ATUI_DEC,
				((LANG_ENG, "vendor specific features."))
			),
			("rsvd_15_12",      15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr10, atui_nullstruct,
	(bios->gddr5_mr10, "gddr5_mr10",
		(ATUI_BIN, ATUI_BITFIELD, (
			("vendor_specific", 11,0, ATUI_DEC,
				((LANG_ENG, "vendor specific features."))
			),
			("rsvd_15_12",      15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr11, atui_nullstruct,
	(bios->gddr5_mr11, "gddr5_mr11",
		(ATUI_BIN, ATUI_BITFIELD, (
			("PASR_banks_01",   0,0, ATUI_DEC,
				((LANG_ENG, "exclude banks 0, 1"))
			),
			("PASR_banks_23",   1,1, ATUI_DEC,
				((LANG_ENG, "exclude banks 2, 3"))
			),
			("PASR_banks_45",   2,2, ATUI_DEC,
				((LANG_ENG, "exclude banks 4, 5"))
			),
			("PASR_banks_67",   3,3, ATUI_DEC,
				((LANG_ENG, "exclude banks 6, 7"))
			),
			("PASR_banks_89",   4,4, ATUI_DEC,
				((LANG_ENG, "exclude banks 8, 9"))
			),
			("PASR_banks_1011", 5,5, ATUI_DEC,
				((LANG_ENG, "exclude banks 10, 11"))
			),
			("PASR_banks_1213", 6,6, ATUI_DEC,
				((LANG_ENG, "exclude banks 12, 13"))
			),
			("PASR_banks_1415", 7,7, ATUI_DEC,
				((LANG_ENG, "exclude banks 14, 15"))
			),
			("PASR_row_00",     8,8, ATUI_DEC,
				((LANG_ENG, "exclude row segment A[13:12]=00 (MSB)"))
			),
			("PASR_row_01",     9,9, ATUI_DEC,
				((LANG_ENG, "exclude row segment A[13:12]=01 (MSB)"))
			),
			("PASR_row_10",    10,10, ATUI_DEC,
				((LANG_ENG, "exclude row segment A[13:12]=10 (MSB)"))
			),
			("PASR_row_11",    11,11, ATUI_DEC,
				((LANG_ENG, "exclude row segment A[13:12]=11 (MSB)"))
			),
			("rsvd_15_12",     15,12, ATUI_DEC, (ATUI_NODESCR)),
			("PASR_bank_mask",         7,0, ATUI_DEC,
				((LANG_ENG, "bank exclusion mask"))
			),
			("PASR_row_segment_mask", 11,8, ATUI_DEC,
				((LANG_ENG, "row exclusion mask"))
			),
			("rsvd_15_12__2",         15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr12, atui_nullstruct,
	(bios->gddr5_mr12, "gddr5_mr12",
		(ATUI_BIN, ATUI_BITFIELD, (
			("vendor_specific", 11,0, ATUI_DEC,
				((LANG_ENG, "vendor specific features."))
			),
			("rsvd_15_12",      15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr13, atui_nullstruct,
	(bios->gddr5_mr13, "gddr5_mr13",
		(ATUI_BIN, ATUI_BITFIELD, (
			("vendor_specific", 11,0, ATUI_DEC,
				((LANG_ENG, "vendor specific features."))
			),
			("rsvd_15_12",      15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr14, atui_nullstruct,
	(bios->gddr5_mr14, "gddr5_mr14",
		(ATUI_BIN, ATUI_BITFIELD, (
			("vendor_specific", 11,0, ATUI_DEC,
				((LANG_ENG, "vendor specific features."))
			),
			("rsvd_15_12",      15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr15, atui_nullstruct,
	(bios->gddr5_mr15, "gddr5_mr15",
		(ATUI_BIN, ATUI_BITFIELD, (
			("rsvd_7_0",          7,0, ATUI_DEC, (ATUI_NODESCR)),
			("MRE_0_disable",     8,8, ATUI_DEC,
				((LANG_ENG, "1=disable MRS commands on channel 0"))
			),
			("MRE_1_disable",     9,9, ATUI_DEC,
				((LANG_ENG, "1=disable MRS commands on channel 1"))
			),
			("address_training", 10,10, ATUI_DEC,
				((LANG_ENG, "1=address training mode"))
			),
			("RFU",              11,11, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("rsvd_15_12",       15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, gddr6_mr0, atui_nullstruct,
	(bios->gddr6_mr0, "gddr6_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			("WLmrs",    2,0, ATUI_DEC,
				((LANG_ENG, "tCWL, 8,9,10,11,12,5,6,7."))
			),
			("RLmrs_lo", 6,3, ATUI_DEC,
				((LANG_ENG, "tCL = 5+n. [MR12[3], MR8[8], MR0[6:3]] -> tCL[5:0]"))
			),
			("testmode", 7,7, ATUI_DEC,
				((LANG_ENG, "Test mode; behavior is vendor specific"))
			),
			("WRmrs",   11,8, ATUI_DEC,
				((LANG_ENG, "tWR for auto-pre, 0=4,1=5..47=51. See MR8, MR12"))
			),
			("ID",      15,12, ATUI_DEC,
				((LANG_ENG, "MR 0"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr1, atui_nullstruct,
	(bios->gddr6_mr1, "gddr6_mr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			("drive_stren",   1,0, ATUI_DEC,
				((LANG_ENG, "0=Auto Cal.(60/40), 1=AC(48/40). 2,3 vndr spec"))
			),
			("data_term",     3,2, ATUI_DEC,
				((LANG_ENG, "0=disabled 1=60ohm 2=120ohm 3=48ohm"))
			),
			("PLLDLL_range",  5,4, ATUI_DEC,
				((LANG_ENG, "min-to-max WCK freq, vendor specific"))
			),
			("Cal_Upd",       6,6, ATUI_DEC,
				((LANG_ENG, "Auto Calibration Engine, 0=enabled."))
			),
			("PLL_DLL",       7,7, ATUI_DEC,
				((LANG_ENG, "0=disabled 1=enabled"))
			),
			("read_DBI",      8,8, ATUI_DEC,
				((LANG_ENG, "Data Bus Inversion, for reads.   0=enabled"))
			),
			("write_DBI",     9,9, ATUI_DEC,
				((LANG_ENG, "Data Bus Inversion, for writes.  1=disabled"))
			),
			("addrcmd_BI",   10,10, ATUI_DEC,
				((LANG_ENG, "Command-address bus inversion.  0=enabled"))
			),
			("PLLDLL_reset", 14,11, ATUI_DEC,
				((LANG_ENG, "1 = reset. self-clears after reset."))
			),
			("ID",           15,12, ATUI_DEC,
				((LANG_ENG, "MR 1"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr2, atui_nullstruct,
	(bios->gddr6_mr2, "gddr6_mr2",
		(ATUI_BIN, ATUI_BITFIELD, (
			("OCD_up",       2,0, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, "output driver pullup offset. 0=0, Two's Compl."))
			),
			("OCD_down",     5,3, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, "pulldown. See JES250D Figure 33."))
			),
			("self_refresh", 7,6, ATUI_DEC,
				((LANG_ENG, "0=32ms, 1-2 vendor specific, 3=temp controlled"))
			),
			("EDC_mode",     8,8, ATUI_DEC,
				((LANG_ENG, "0=full data rate, 1=half"))
			),
			("RDQS",         9,9, ATUI_DEC,
				((LANG_ENG, "1 = EDC pins will act as RDQS; no CRC."))
			),
			("CADT_SRF",    10,10, ATUI_DEC,
				((LANG_ENG, "Self refesh while CA training"))
			),
			("EDC_HR",      11,11, ATUI_DEC,
				((LANG_ENG, "EDC hold data rate 0=full, 1=half"))
			),
			("ID",          15,12, ATUI_DEC,
				((LANG_ENG, "MR 2"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr3, atui_nullstruct,
	(bios->gddr6_mr3, "gddr6_mr3",
		(ATUI_BIN, ATUI_BITFIELD, (
			("dataWCK_term_offset", 2,0, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, "DQ, DBI & WCK termination offset. Two's"))
			),
			("CA_term_offset",      5,3, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, "command address. See MR2."))
			),
			("DRAM_info",           7,6, ATUI_DEC,
				((LANG_ENG, "0=off 1=vndr ID1 2=temp 3=vndr ID2"))
			),
			("WR_scaling",          9,8, ATUI_DEC,
				((LANG_ENG, "1x 2x 3x value of tWR in MR8 and MR0"))
			),
			("bank_groups",        11,10, ATUI_DEC,
				((LANG_ENG, "0,1=off, 2=on tCCDL=4, 3=on tCCDL=3"))
			),
			("ID",                 15,12, ATUI_DEC,
				((LANG_ENG, "MR 3"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr4, atui_nullstruct,
	(bios->gddr6_mr4, "gddr6_mr4",
		(ATUI_BIN, ATUI_BITFIELD, (
			("EDC_hold_pattern", 3,0, ATUI_DEC,
				((LANG_ENG, "little-endian. pattern during EDC idle"))
			),
			("CRCWL",            6,4, ATUI_DEC,
				((LANG_ENG, "15,16,RFU,10,11..21,RFU. See MR12 OP4"))
			),
			("CRCRL",            8,7, ATUI_DEC,
				((LANG_ENG, "CRC latency for reads. 4,1,2,3."))
			),
			("RDCRC",            9,9, ATUI_DEC,
				((LANG_ENG, "read CRC 0=enable"))
			),
			("WRCRC",           10,10, ATUI_DEC,
				((LANG_ENG, "write CRC 0=enable"))
			),
			("EDC_hold_invert", 11,11, ATUI_DEC,
				((LANG_ENG, "0 = EDC hold pattern not inverted"))
			),
			("ID",              15,12, ATUI_DEC,
				((LANG_ENG, "MR 4"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr5, atui_nullstruct,
	(bios->gddr6_mr5, "gddr6_mr5",
		(ATUI_BIN, ATUI_BITFIELD, (
			("LP1",       0,0, ATUI_DEC,
				((LANG_ENG, "0=off, Low Power Mode 1, relax several core params"))
			),
			("LP2",       1,1, ATUI_DEC,
				((LANG_ENG, "WCK recievers turned off during powerdown."))
			),
			("LP3",       2,2, ATUI_DEC,
				((LANG_ENG, "no read/write training and temp reads during REFab"))
			),
			("PLLDLL_BW", 5,3, ATUI_DEC,
				((LANG_ENG, "PLL/DLL bandwidth. All except 0 vendor specific"))
			),
			("RAS",      11,6, ATUI_DEC,
				((LANG_ENG, "0,1,2...63. tRAS for auto precharge"))
			),
			("ID",       15,12, ATUI_DEC,
				((LANG_ENG, "MR 5"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr6, atui_nullstruct,
	(bios->gddr6_mr6, "gddr6_mr6",
		(ATUI_BIN, ATUI_BITFIELD, (
			("VREFD_level",  6,0, ATUI_DEC,
				((LANG_ENG, "0.005x steps of VDDQ, from 0=0.49x to 95=0.965x"))
			),
			("pin_subaddr", 11,7, ATUI_DEC,
				((LANG_ENG, "pin to configure the VREFD for. See JESD250"))
			),
			("ID",          15,12, ATUI_DEC,
				((LANG_ENG, "MR 6"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr7, atui_nullstruct,
	(bios->gddr6_mr7, "gddr6_mr7",
		(ATUI_BIN, ATUI_BITFIELD, (
			("WCK2CK_AP",       0,0, ATUI_DEC,
				((LANG_ENG, "WCK alignment point. 0=inside 1=at balls"))
			),
			("hibernate",       1,1, ATUI_DEC,
				((LANG_ENG, "1=Hibernate Self Refresh mode. self clearing"))
			),
			("PLL_delay_comp",  2,2, ATUI_DEC,
				((LANG_ENG, "1=(PLL feedback delay == WCK clock tree)"))
			),
			("low_freq_mode",   3,3, ATUI_DEC,
				((LANG_ENG, "1=reduce power of input RX, clock trees"))
			),
			("WCK2CK_autosync", 4,4, ATUI_DEC,
				((LANG_ENG, "1=auto sync, reduces WCK2CK MRS to 2."))
			),
			("DQ_preamble",     5,5, ATUI_DEC,
				((LANG_ENG, "1=preamble on DQ, DBI_n for gapped reads."))
			),
			("half_VREFC",      6,6, ATUI_DEC,
				((LANG_ENG, "0=0.7x VDDQ, 1=0.5x See MR6, MR9"))
			),
			("half_VREFD",      7,7, ATUI_DEC,
				((LANG_ENG, "0=prog'd VREFD,DFE. 1=0.5x VDDQ. See MR6,MR9"))
			),
			("VDD_range",       9,8, ATUI_DEC,
				((LANG_ENG, "0>1>2>3. Adapt to lower VDD voltages"))
			),
			("WCK_DCC",        11,10, ATUI_DEC,
				((LANG_ENG, "Duty Cycle Corr. 0=off,1=start,2=RFU,3=hold"))
			),
			("ID",             15,12, ATUI_DEC,
				((LANG_ENG, "MR 7"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr8, atui_nullstruct,
	(bios->gddr6_mr8, "gddr6_mr8",
		(ATUI_BIN, ATUI_BITFIELD, (
			("CA_low_term",  1,0, ATUI_DEC,
				((LANG_ENG, "0=disable, 1=60ohm, 2=120, 3=rsvd. For CA[3:0]"))
			),
			("CA_high_term", 3,2, ATUI_DEC,
				((LANG_ENG, "For CA[10:4]"))
			),
			("CA_TO",        4,4, ATUI_DEC,
				((LANG_ENG, "Command Address Termin. Override 1=use CAL,CAH"))
			),
			("EDC_hiZ",      5,5, ATUI_DEC,
				((LANG_ENG, "1=Hi-Z state. Precidence over all other states."))
			),
			("CK_auto_cal",  6,6, ATUI_DEC,
				((LANG_ENG, "0=auto calib. during REFab disabled, 1=enabled"))
			),
			("REFpb",        7,7, ATUI_DEC,
				((LANG_ENG, "0=per-bank, 1=per-2-bank"))
			),
			("RL_EHF",       8,8, ATUI_DEC,
				((LANG_ENG, "Extends RLmrs of MR0 from 4 to 5 bits."))
			),
			("WR_EHF",       9,9, ATUI_DEC,
				((LANG_ENG, "Extends WRmrs of MR0 from 4 to 5 bits."))
			),
			("CK_term",     11,10, ATUI_DEC,
				((LANG_ENG, "0=reset, 1=60ohm,2=120-ohm, 3=disabled"))
			),
			("ID",          15,12, ATUI_DEC,
				((LANG_ENG, "MR 8"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr9, atui_nullstruct,
	(bios->gddr6_mr9, "gddr6_mr9",
		(ATUI_BIN, ATUI_BITFIELD, (
			("DFE",          3,0, ATUI_DEC,
				((LANG_ENG, "0=off, in steps of +-0.5% VDDQ or 7mV"))
			),
			("RFU",          6,4, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("pin_subaddr", 11,7, ATUI_DEC,
				((LANG_ENG, "see JESD250"))
			),
			("ID",          15,12, ATUI_DEC,
				((LANG_ENG, "MR 9"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr10, atui_nullstruct,
	(bios->gddr6_mr10, "gddr6_mr10",
		(ATUI_BIN, ATUI_BITFIELD, (
			("VREFC_offset",  3,0, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, "CA bus. semi Two's Complement: -8=0"))
			),
			("WCK_inv_byte0", 5,4, ATUI_DEC,
				((LANG_ENG, "for WCK2CK training 0=0;1=90 degr;2=180;3=270"))
			),
			("WCK_inv_byte1", 7,6, ATUI_DEC,
				((LANG_ENG, "B1 on chan A, B0 on chan B ignored if WCK/word"))
			),
			("WCK2CK",        8,8, ATUI_DEC,
				((LANG_ENG, "1=enable WCK2CK alignment training"))
			),
			("WCK_ratio",     9,9, ATUI_DEC,
				((LANG_ENG, "0=half data rate, 1=full data rate"))
			),
			("WCK_term",     11,10, ATUI_DEC,
				((LANG_ENG, "0=disabled, 1=60 ohm, 2=120, 3=reserved"))
			),
			("ID",           15,12, ATUI_DEC,
				((LANG_ENG, "MR 10"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr11, atui_nullstruct,
	(bios->gddr6_mr11, "gddr6_mr11",
		(ATUI_BIN, ATUI_BITFIELD, (
			("PASR_banks_01",   0,0, ATUI_DEC,
				((LANG_ENG, "exclude banks 0, 1"))),
			("PASR_banks_23",   1,1, ATUI_DEC,
				((LANG_ENG, "exclude banks 2, 3"))),
			("PASR_banks_45",   2,2, ATUI_DEC,
				((LANG_ENG, "exclude banks 4, 5"))),
			("PASR_banks_67",   3,3, ATUI_DEC,
				((LANG_ENG, "exclude banks 6, 7"))),
			("PASR_banks_89",   4,4, ATUI_DEC,
				((LANG_ENG, "exclude banks 8, 9"))),
			("PASR_banks_1011", 5,5, ATUI_DEC,
				((LANG_ENG, "exclude banks 10, 11"))),
			("PASR_banks_1213", 6,6, ATUI_DEC,
				((LANG_ENG, "exclude banks 12, 13"))),
			("PASR_banks_1415", 7,7, ATUI_DEC,
				((LANG_ENG, "exclude banks 14, 15"))),
			("PASR_row_00",     8,8, ATUI_DEC,
				((LANG_ENG, "exclude row segment R[13:12]=00 (MSB)"))),
			("PASR_row_01",     9,9, ATUI_DEC,
				((LANG_ENG, "exclude row segment R[13:12]=01 (MSB)"))),
			("PASR_row_10",    10,10, ATUI_DEC,
				((LANG_ENG, "exclude row segment R[13:12]=10 (MSB)"))),
			("PASR_row_11",    11,11, ATUI_DEC,
				((LANG_ENG, "exclude row segment R[13:12]=11 (MSB)"))),
			("ID",             15,12, ATUI_DEC,
				((LANG_ENG, "MR 11"))),
			("PASR_bank_mask",         7,0, ATUI_DEC,
				((LANG_ENG, "bank exclusion mask"))),
			("PASR_row_segment_mask", 11,8, ATUI_DEC,
				((LANG_ENG, "row exclusion mask"))),
			("ID__2",                 15,12, ATUI_DEC,
				((LANG_ENG, "MR 11")))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr12, atui_nullstruct,
	(bios->gddr6_mr12, "gddr6_mr12",
		(ATUI_BIN, ATUI_BITFIELD, (
			("VDDQ_off",  0,0, ATUI_DEC,
				((LANG_ENG, "0=disabled. For Hibernate Self Refresh"))
			),
			("P2BR_addr", 1,1, ATUI_DEC,
				((LANG_ENG, "0=LSB/BA0 1=MSB/BA3. Select \"Dont Care\" for REFp2b"))
			),
			("PRBS",      2,2, ATUI_DEC,
				((LANG_ENG, "1=Psudorandom bit stream instead of EDC hold"))
			),
			("RL_EHF2",   3,3, ATUI_DEC,
				((LANG_ENG, "Extends RLmrs from 5 bits to 6 bits. See MR0, MR8"))
			),
			("CRCWL_EHF", 4,4, ATUI_DEC,
				((LANG_ENG, "Extends CRCWL from 3 bits to 4 bits. See MR4."))
			),
			("WR_EHF2",   5,5, ATUI_DEC,
				((LANG_ENG, "Extends WRmrs from 5 bits to 6 bits. See MR0, MR8"))
			),
			("RFU",      11,6, ATUI_DEC,
				((LANG_ENG, "reserved."))
			),
			("ID",       15,12, ATUI_DEC,
				((LANG_ENG, "MR 12"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr13, atui_nullstruct,
	(bios->gddr6_mr13, "gddr6_mr13",
		(ATUI_BIN, ATUI_BITFIELD, (
			("vendor_specific", 11,0, ATUI_DEC,
				((LANG_ENG, "vendor specific features."))
			),
			("ID",              15,12, ATUI_DEC,
				((LANG_ENG, "MR 13"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr14, atui_nullstruct,
	(bios->gddr6_mr14, "gddr6_mr14",
		(ATUI_BIN, ATUI_BITFIELD, (
			("vendor_specific", 11,0, ATUI_DEC,
				((LANG_ENG, "vendor specific features."))
			),
			("ID",              15,12, ATUI_DEC,
				((LANG_ENG, "MR 14"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr15, atui_nullstruct,
	(bios->gddr6_mr15, "gddr6_mr15",
		(ATUI_BIN, ATUI_BITFIELD, (
			("MRS_to_chan_A", 0,0, ATUI_DEC,
				((LANG_ENG, "MRS to the two channels for individual config"))
			),
			("MRS_to_chan_B", 1,1, ATUI_DEC,
				((LANG_ENG, "0=unblocked 1=blocked"))
			),
			("CA_training",   3,2, ATUI_DEC,
				((LANG_ENG, "0=off 1=rising of CK, 2=falling, 3=CABI_n,CA10"))
			),
			("unused",        11,4, ATUI_DEC,
				((LANG_ENG, "defined to be absent"))
			),
			("ID",            15,12, ATUI_DEC,
				((LANG_ENG, "MR 15"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, hbm_mr0, atui_nullstruct,
	(bios->hbm_mr0, "hbm_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			("read_DBI",       0,0, ATUI_DEC,
				((LANG_ENG, "1=enable; data bus inversion, AC."))
			),
			("write_DBI",      1,1, ATUI_DEC,
				((LANG_ENG, "1=enable; data bus inversion, AC."))
			),
			("TCSR",           2,2, ATUI_DEC,
				((LANG_ENG, "1=enable; temperature-controlled self-refresh"))
			),
			("rsvd_3_3",       3,3, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("read_parity",    4,4, ATUI_DEC,
				((LANG_ENG, "0=disable; DQ parity"))
			),
			("write_parity",   5,5, ATUI_DEC,
				((LANG_ENG, "0=disable; DQ parity"))
			),
			("addrcmd_parity", 6,6, ATUI_DEC,
				((LANG_ENG, "0=disable; command-address parity"))
			),
			("test_mode",      7,7, ATUI_DEC,
				((LANG_ENG, "1=Test mode; behavior is vendor specific"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr1, atui_nullstruct,
	(bios->hbm_mr1, "hbm_mr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tWR",       4,0, ATUI_DEC,
				((LANG_ENG, "3=3,4=4...31=31. 0..2=reserved"))
			),
			("nom_drive", 7,5, ATUI_DEC,
				((LANG_ENG, "6mA,9,12,15,18, 5..7=reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr2, atui_nullstruct,
	(bios->hbm_mr2, "hbm_mr2",
		(ATUI_BIN, ATUI_BITFIELD, (
			("WL", 2,0, ATUI_DEC,
				((LANG_ENG, "[MR4[4], MR2[2:0]] -> WL[3:0]; tWL=1+n"))
			),
			("RL", 7,3, ATUI_DEC,
				((LANG_ENG, "[MR4[5], MR2[7:3]] -> RL[5:0]; tRL=2+n"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr3, atui_nullstruct,
	(bios->hbm_mr3, "hbm_mr3",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tRAS",         5,0, ATUI_DEC,
				((LANG_ENG, "3=3... 63=63; 0,1,2=reserved"))
			),
			("bank_groups",  6,6, ATUI_DEC,
				((LANG_ENG, "1=enable"))
			),
			("burst_length", 7,7, ATUI_DEC,
				((LANG_ENG, "0=BL2, 1=BL4"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr4, atui_nullstruct,
	(bios->hbm_mr4, "hbm_mr4",
		(ATUI_BIN, ATUI_BITFIELD, (
			("ECC",      0,0, ATUI_DEC,
				((LANG_ENG, "0=disabled; ECC and WDM are mutually exlusive."))
			),
			("WDM",      1,1, ATUI_DEC,
				((LANG_ENG, "0=enabled; write data mask"))
			),
			("PL",       3,2, ATUI_DEC,
				((LANG_ENG, "0=0..3=3; parity latency"))
			),
			("EWL",      4,4, ATUI_DEC,
				((LANG_ENG, "extended write latency; see MR0"))
			),
			("ERL",      5,5, ATUI_DEC,
				((LANG_ENG, "extended read latency; see MR0"))
			),
			("reserved", 7,6, ATUI_DEC,
				((LANG_ENG, "reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr5, atui_nullstruct,
	(bios->hbm_mr5, "hbm_mr5",
		(ATUI_BIN, ATUI_BITFIELD, (
			("TRR_bank_address", 3,0, ATUI_DEC,
				((LANG_ENG, "0=0; target bank of target row"))
			),
			("reserved",         5,4, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("TRR_peudochannel", 6,6, ATUI_DEC,
				((LANG_ENG, "0=PC0, 1=PC1"))
			),
			("TRR_mode",         7,7, ATUI_DEC,
				((LANG_ENG, "0=disable; Target Row Refresh for rowhammer"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr6, atui_nullstruct,
	(bios->hbm_mr6, "hbm_mr6",
		(ATUI_BIN, ATUI_BITFIELD, (
			("reserved",    2,0, ATUI_DEC, (ATUI_NODESCR)),
			("implicit_RP", 7,3, ATUI_DEC,
				((LANG_ENG, "tRP=n+2; imPRE has PRE implied with ACT."))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr7, atui_nullstruct,
	(bios->hbm_mr7, "hbm_mr7",
		(ATUI_BIN, ATUI_BITFIELD, (
			("DWORD_loopback", 0,0, ATUI_DEC,
				((LANG_ENG, "0=disable; 1=link test (MISR) mode"))
			),
			("DWORD_read_mux", 2,1, ATUI_DEC,
				((LANG_ENG, "1=MISR regs, 2=Rx path, 3=LFSR sticky"))
			),
			("DWORD_MISR",     5,3, ATUI_DEC,
				((LANG_ENG, "0=preset 0xAAAAA/0x00000, 1=LFSR read, 2=register (R/W), 3=MISR write, 4=LFSR write"))
			),
			("reserved",       6,6, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("CATTRIP",        7,7, ATUI_DEC,
				((LANG_ENG, "0=clear pin, 1=assert to 1."))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr8, atui_nullstruct,
	(bios->hbm_mr8, "hbm_mr8",
		(ATUI_BIN, ATUI_BITFIELD, (
			("DA28_lockout", 0,0, ATUI_DEC,
				((LANG_ENG, "1=if on chan A or E, hardlock DA port"))
			),
			("reserved", 7,1, ATUI_DEC,
				((LANG_ENG, "reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr9, atui_nullstruct,
	(bios->hbm_mr9, "hbm_mr9",
		(ATUI_BIN, ATUI_BITFIELD, (
			("reserved", 7,0, ATUI_DEC,
				((LANG_ENG, "reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr10, atui_nullstruct,
	(bios->hbm_mr10, "hbm_mr10",
		(ATUI_BIN, ATUI_BITFIELD, (
			("reserved", 7,0, ATUI_DEC,
				((LANG_ENG, "reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr11, atui_nullstruct,
	(bios->hbm_mr11, "hbm_mr11",
		(ATUI_BIN, ATUI_BITFIELD, (
			("reserved", 7,0, ATUI_DEC,
				((LANG_ENG, "reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr12, atui_nullstruct,
	(bios->hbm_mr12, "hbm_mr12",
		(ATUI_BIN, ATUI_BITFIELD, (
			("reserved", 7,0, ATUI_DEC,
				((LANG_ENG, "reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr13, atui_nullstruct,
	(bios->hbm_mr13, "hbm_mr13",
		(ATUI_BIN, ATUI_BITFIELD, (
			("reserved", 7,0, ATUI_DEC,
				((LANG_ENG, "reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr14, atui_nullstruct,
	(bios->hbm_mr14, "hbm_mr14",
		(ATUI_BIN, ATUI_BITFIELD, (
			("reserved", 7,0, ATUI_DEC,
				((LANG_ENG, "reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr15, atui_nullstruct,
	(bios->hbm_mr15, "hbm_mr15",
		(ATUI_BIN, ATUI_BITFIELD, (
			("internal_vref", 2,0, ATUI_DEC,
				((LANG_ENG, "Two's: 0.50 - 0.04*n; 0=.50, 1=.46, 4=.54"))
			),
			("reserved", 7,3, ATUI_DEC,
				((LANG_ENG, "reserved"))
			)
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, hbm3_mr0, atui_nullstruct,
	(bios->hbm3_mr0, "hbm3_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			("read_DBI",       0,0, ATUI_DEC,
				((LANG_ENG, "1=enable; data bus inversion, AC."))
			),
			("write_DBI",      1,1, ATUI_DEC,
				((LANG_ENG, "1=enable; data bus inversion, AC."))
			),
			("TCSR",           2,2, ATUI_DEC,
				((LANG_ENG, "1=enable; temperature-controlled self-refresh"))
			),
			("rsvd_3_3",       3,3, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("read_parity",    4,4, ATUI_DEC,
				((LANG_ENG, "0=disable; DQ parity"))
			),
			("write_parity",   5,5, ATUI_DEC,
				((LANG_ENG, "0=disable; DQ parity"))
			),
			("addrcmd_parity", 6,6, ATUI_DEC,
				((LANG_ENG, "0=disable; command-address parity"))
			),
			("test_mode",      7,7, ATUI_DEC,
				((LANG_ENG, "1=Test mode; behavior is vendor specific"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr1, atui_nullstruct,
	(bios->hbm3_mr1, "hbm3_mr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tWL", 4,0, ATUI_DEC,
				((LANG_ENG, "4=4..16=16,  0..3,17+ reserved"))
			),
			("tPL", 7,5, ATUI_DEC,
				((LANG_ENG, "0=0..4=4, 5+ reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr2, atui_nullstruct,
	(bios->hbm3_mr2, "hbm3_mr2",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tRL", 7,0, ATUI_DEC,
				((LANG_ENG, "4=4..63=63,  0..3,64+ reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr3, atui_nullstruct,
	(bios->hbm3_mr3, "hbm3_mr3",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tWR", 7,0, ATUI_DEC,
				((LANG_ENG, "4=4..63=63,  0..3,64+ reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr4, atui_nullstruct,
	(bios->hbm3_mr4, "hbm3_mr4",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tRAS", 7,0, ATUI_DEC,
				((LANG_ENG, "4=4..63=63,  0..3,64+ reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr5, atui_nullstruct,
	(bios->hbm3_mr5, "hbm3_mr5",
		(ATUI_BIN, ATUI_BITFIELD, (
			("tRTP", 7,0, ATUI_DEC,
				((LANG_ENG, "2=2..15=15,  0,1 reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr6, atui_nullstruct,
	(bios->hbm3_mr6, "hbm3_mr6",
		(ATUI_BIN, ATUI_BITFIELD, (
			("drive_down_strength", 2,0, ATUI_DEC,
				((LANG_ENG, "0=8mA, 1=10, *2=12, 3=14, 4+ reserved"))
			),
			("drive_up_strength",   5,3, ATUI_DEC,
				((LANG_ENG, "0=8mA, 1=10, *2=12, 3=14, 4+ reserved"))
			),
			("reserved",            7,6, ATUI_DEC,
				((LANG_ENG, "reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr7, atui_nullstruct,
	(bios->hbm3_mr7, "hbm3_mr7",
		(ATUI_BIN, ATUI_BITFIELD, (
			("DWORD_loopback", 0,0, ATUI_DEC,
				((LANG_ENG, "0=disable; 1=link test (MISR) mode"))
			),
			("DWORD_read_mux", 1,1, ATUI_DEC,
				((LANG_ENG, "0=MISR regs, 3=LFSR sticky"))
			),
			("reserved_2_2",   2,2, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("DWORD_MISR",     5,3, ATUI_DEC,
				((LANG_ENG, "0=preset, 1=LFSR read, 2=register (R/W), 3=MISR write, 4=LFSR write"))
			),
			("reserved_6_6",   6,6, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("CATTRIP",        7,7, ATUI_DEC,
				((LANG_ENG, "0=auto, 1=assert to 1."))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr8, atui_nullstruct,
	(bios->hbm3_mr8, "hbm3_mr8",
		(ATUI_BIN, ATUI_BITFIELD, (
			("DA_lockout",         0,0, ATUI_DEC,
				((LANG_ENG, "1=if on chan A or E, hardlock DA port"))
			),
			("duty_cycle_monitor", 1,1, ATUI_DEC,
				((LANG_ENG, "0=disabled"))
			),
			("ECS_log_auto_clear", 2,2, ATUI_DEC,
				((LANG_ENG, "0=disabled"))
			),
			("WDQS2CK_training",   3,3, ATUI_DEC,
				((LANG_ENG, "0=disabled"))
			),
			("RFM_levels",         5,4, ATUI_DEC,
				((LANG_ENG, "0=default, 1=A,2=B,3=C (1+ RFM required)"))
			),
			("reserved",           7,6, ATUI_DEC,
				((LANG_ENG, "reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr9, atui_nullstruct,
	(bios->hbm3_mr9, "hbm3_mr9",
		(ATUI_BIN, ATUI_BITFIELD, (
			("metadata",           0,0, ATUI_DEC,
				((LANG_ENG, "1=read/writes have metadata"))
			),
			("severity_reporting", 1,1, ATUI_DEC,
				((LANG_ENG, "1=repoting"))
			),
			("ECC_testmode",       2,2, ATUI_DEC,
				((LANG_ENG, "0=disable ECC engine test mode"))
			),
			("ECC_test_pattern",   3,3, ATUI_DEC,
				((LANG_ENG, "0=CW0 (1's are errors), 1=CW1 (0=error)"))
			),
			("ECS_via_REFab",      4,4, ATUI_DEC,
				((LANG_ENG, "0=disabled"))
			),
			("ECS_during_SRF",     5,5, ATUI_DEC,
				((LANG_ENG, "0=disabled"))
			),
			("ECS_multibit",       6,6, ATUI_DEC,
				((LANG_ENG, "0=correction of multibit errors disabled"))
			),
			("ECS_logging",        7,7, ATUI_DEC,
				((LANG_ENG, "0=maintain, 1=reset"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr10, atui_nullstruct,
	(bios->hbm3_mr10, "hbm3_mr10",
		(ATUI_BIN, ATUI_BITFIELD, (
			("vendor_specific", 7,0, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr11, atui_nullstruct,
	(bios->hbm3_mr11, "hbm3_mr11",
		(ATUI_BIN, ATUI_BITFIELD, (
			("DCA_WDQS0", 3,0, ATUI_DEC,
				((LANG_ENG, "broken Two's: 0=0, 7=-7, 8=reserved, 9=+1 15=+7"))
			),
			("DCA_WDQS1", 7,4, ATUI_DEC,
				((LANG_ENG, "broken Two's: 0=0, 7=-7, 8=reserved, 9=+1 15=+7"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr12, atui_nullstruct,
	(bios->hbm3_mr12, "hbm3_mr12",
		(ATUI_BIN, ATUI_BITFIELD, (
			("vendor_specific", 7,0, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr13, atui_nullstruct,
	(bios->hbm3_mr13, "hbm3_mr13",
		(ATUI_BIN, ATUI_BITFIELD, (
			("reserved", 7,0, ATUI_DEC,
				((LANG_ENG, "reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr14, atui_nullstruct,
	(bios->hbm3_mr14, "hbm3_mr14",
		(ATUI_BIN, ATUI_BITFIELD, (
			("reserved_0_0", 0,0, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("VrefCA",       6,1, ATUI_DEC,
				((LANG_ENG, "0.18 + 0.01*n; 1=0.19, 63=.81. (32=.50)"))
			),
			("reserved_7_7", 7,7, ATUI_DEC,
				((LANG_ENG, "reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr15, atui_nullstruct,
	(bios->hbm3_mr15, "hbm3_mr15",
		(ATUI_BIN, ATUI_BITFIELD, (
			("reserved_0_0", 0,0, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			("VrefD",        6,1, ATUI_DEC,
				((LANG_ENG, "0.18 + 0.01*n; 1=0.19, 63=.81. (32=.50)"))
			),
			("reserved_7_7", 7,7, ATUI_DEC,
				((LANG_ENG, "reserved"))
			)
		)), (ATUI_NODESCR)
	)
)


