/*
For ddrmoderegisters.h
See atui_atomfirmware.c for how to use PPATUI_FUNCIFY()
*/

#include "atomtree.h"
#include "atui.h"

PPATUI_FUNCIFY(union, ddr1_mr0, atui_nullstruct,
	(bios->ddr1_mr0, u8"ddr1_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"burst_length",    2,0, ATUI_DEC,
				((LANG_ENG, u8"1=BL2, 2=BL4, 3=BL8; all else reserved"))
			),
			(u8"burst_type",      3,3, ATUI_DEC,
				((LANG_ENG, u8"0=sequential, 1=interleave"))
			),
			(u8"tCL",             6,4, ATUI_DEC,
				((LANG_ENG, u8"2=2,3=3, 5=1.5,6=2.5, all else reseved"))
			),
			(u8"test_mode",       7,7, ATUI_DEC,
				((LANG_ENG, u8"behaviour is vendor specific"))
			),
			(u8"DLL_reset",       8,8, ATUI_DEC,
				((LANG_ENG, u8"self clearing"))
			),
			(u8"operating_rsvd", 13,9, ATUI_DEC,
				((LANG_ENG, u8"operation_mode reserved"))
			),
			(u8"ID",             15,14, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, ddr1_emr1, atui_nullstruct,
	(bios->ddr1_emr1, u8"ddr1_emr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"DLL",              0,0, ATUI_DEC,
				((LANG_ENG, u8"0=enable"))
			),
			(u8"drive_strength",   1,1, ATUI_DEC,
				((LANG_ENG, u8"0=full, 1=reduced; (see SSTL_2, Class II)"))
			),
			(u8"reserved",         2,2, ATUI_DEC,
				((LANG_ENG, u8"compatibility with early DDR1"))
			),
			(u8"operating_rsvd",  13,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ID",              15,14, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, ddr2_mr0, atui_nullstruct,
	(bios->ddr2_mr0, u8"ddr2_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"burst_length",  2,0, ATUI_DEC,
				((LANG_ENG, u8"2=BL4, 3=BL8; all else reserved"))
			),
			(u8"burst_type",    3,3, ATUI_DEC,
				((LANG_ENG, u8"0=sequential, 1=interleave"))
			),
			(u8"tCL",           6,4, ATUI_DEC,
				((LANG_ENG, u8"tCL=n; 0,1,7=reserved"))
			),
			(u8"test_mode",     7,7, ATUI_DEC,
				((LANG_ENG, u8"behaviour is vendor specific"))
			),
			(u8"DLL_reset",     8,8, ATUI_DEC,
				((LANG_ENG, u8"self clearing"))
			),
			(u8"WR",           11,9, ATUI_DEC,
				((LANG_ENG, u8"tWR = n+1"))
			),
			(u8"PD_exit_time", 12,12, ATUI_DEC,
				((LANG_ENG, u8"0=fast, 1=slow"))
			),
			(u8"rsvd_15_13",   15,13, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, ddr2_emr1, atui_nullstruct,
	(bios->ddr2_emr1, u8"ddr2_emr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"DLL",              0,0, ATUI_DEC,
				((LANG_ENG, u8"0=enable"))
			),
			(u8"drive_strength",   1,1, ATUI_DEC,
				((LANG_ENG, u8"0=full, 1=reduced"))
			),
			(u8"RTT_Nom_lo_bit",   2,2, ATUI_DEC,
				((LANG_ENG, u8"A[6,2] -> Nom[1:0]"))
			),
			(u8"Additive_Latency", 5,3, ATUI_DEC,
				((LANG_ENG, u8"0=0...  6+=reserved"))
			),
			(u8"RTT_Nom_hi_bit",   6,6, ATUI_DEC,
				((LANG_ENG, u8"0=disabled, 1=75 ohms, 2=150, 3=50"))
			),
			(u8"OCD_calibration",  9,7, ATUI_DEC,
				((LANG_ENG, u8"0=exit,1=drive1,2=drive2,4=adjust,7=default"))
			),
			(u8"DQS",             10,10, ATUI_DEC,
				((LANG_ENG, u8"0=enable"))
			),
			(u8"RDQS",            11,11, ATUI_DEC,
				((LANG_ENG, u8"0=disable"))
			),
			(u8"output_disable",  12,12, ATUI_DEC,
				((LANG_ENG, u8"1=turn off drivers for DQ, DQS, RDQS"))
			),
			(u8"rsvd_15_13",      15,13, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, ddr2_emr2, atui_nullstruct,
	(bios->ddr2_emr2, u8"ddr2_emr2",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"PASR",        2,0, ATUI_DEC,
				((LANG_ENG, u8"0=full (BA[2:0]=xxx), 0xx, 00x, 000, 3/4 (>1), 1xx, 11x, 111"))
			),
			(u8"DCC",         3,3, ATUI_DEC,
				((LANG_ENG, u8"0=disable; Duty Cycle Correction"))
			),
			(u8"rsvd_6_4",    6,4, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"HT_SRF",      7,7, ATUI_DEC,
				((LANG_ENG, u8"0=disable; hi-temp self-refresh mode"))
			),
			(u8"rsvd_12_8",  12,8, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"rsvd_15_13", 15,13, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, ddr2_emr3, atui_nullstruct,
	(bios->ddr2_emr3, u8"ddr2_emr3",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"rsvd_15_0",  15,0, ATUI_DEC,
				((LANG_ENG, u8"all reserved"))
			)
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, ddr3_mr0, atui_nullstruct,
	(bios->ddr3_mr0, u8"ddr3_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"burst_length",    1,0, ATUI_DEC,
				((LANG_ENG, u8"0=BL8, 1=OTF 4/8, 2=BC4, 3=reserved"))
			),
			(u8"CL_hi_bit",       2,2, ATUI_DEC,
				((LANG_ENG, u8"A[2,6,5,4] -> CL[4:0]"))
			),
			(u8"read_burst_type", 3,3, ATUI_DEC,
				((LANG_ENG, u8"0=nibble sequential, 1=interleave"))
			),
			(u8"CL_lo_bits",      6,4, ATUI_DEC,
				((LANG_ENG, u8"tCL = 4+n"))
			),
			(u8"testmode",        7,7, ATUI_DEC,
				((LANG_ENG, u8"behaviour is vendor specific"))
			),
			(u8"DLL_reset",       8,8, ATUI_DEC,
				((LANG_ENG, u8"self clearing"))
			),
			(u8"WR",             11,9, ATUI_DEC,
				((LANG_ENG, u8"tWR; 16,5,6,7,8,10,12,14"))
			),
			(u8"DLL_PPD",        12,12, ATUI_DEC,
				((LANG_ENG, u8"0=slow exit (DLL off), 1=fast (DLL on)"))
			),
			(u8"RFU_15_13",      15,13, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, ddr3_mr1, atui_nullstruct,
	(bios->ddr3_mr1, u8"ddr3_mr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"DLL",              0,0, ATUI_DEC,
				((LANG_ENG, u8"0=enable"))
			),
			(u8"DrvStr_lo_bit",    1,1, ATUI_DEC,
				((LANG_ENG, u8"0=RZQ/6, 1=RZQ/7"))
			),
			(u8"RTTNom_lo_bit",    2,2, ATUI_DEC,
				((LANG_ENG, u8"A[9,6,2] -> RTT_Nom[2:0]"))
			),
			(u8"Additive_Latency", 4,3, ATUI_DEC,
				((LANG_ENG, u8"0=0, 1=tCL-1, 2=tCL-2, 3=reserved"))
			),
			(u8"DrvStr_hi_bit",    5,5, ATUI_DEC,
				((LANG_ENG, u8"A[5,1] -> DrvStr[1:0]; 2,3=reserved"))
			),
			(u8"RTTNom_mid_bit",   6,6, ATUI_DEC,
				((LANG_ENG, u8"0=dis, RZQ/4, /2, /6, /12, /8,  6,7=rsvd"))
			),
			(u8"write_leveling",   7,7, ATUI_DEC,
				((LANG_ENG, u8"0=disabled"))
			),
			(u8"RFU_8",            8,8, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"RTTNom_hi_bit",    9,9, ATUI_DEC,
				((LANG_ENG, u8"2,4,6 only if writelevel on and drivers on"))
			),
			(u8"RFU_10",          10,10, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"TDQS",            11,11, ATUI_DEC,
				((LANG_ENG, u8"0=disabled; Termination Data Strobe pins"))
			),
			(u8"output_disable",  12,12, ATUI_DEC,
				((LANG_ENG, u8"1=turn off drivers for DQ, DQS, DQS#"))
			),
			(u8"RFU_15_13",       15,13, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, ddr3_mr2, atui_nullstruct,
	(bios->ddr3_mr2, u8"ddr3_mr2",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"PASR",       2,0, ATUI_DEC,
				((LANG_ENG, u8"0=full (BA[2:0]=xxx), 0xx, 00x, 000, 3/4 (>1), 1xx, 11x, 111"))
			),
			(u8"CWL",        5,3, ATUI_DEC,
				((LANG_ENG, u8"tCWl = 5+n"))
			),
			(u8"ASR",        6,6, ATUI_DEC,
				((LANG_ENG, u8"0=manual; auto self refresh"))
			),
			(u8"SRT",        7,7, ATUI_DEC,
				((LANG_ENG, u8"0=normal, 1=extended; self refresh temp range"))
			),
			(u8"RFU_8",      8,8, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"RTT_WR",    10,9, ATUI_DEC,
				((LANG_ENG, u8"0=off, RZQ/4, /2, reserved"))
			),
			(u8"RFU_15_11", 15,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, ddr3_mr3, atui_nullstruct,
	(bios->ddr3_mr3, u8"ddr3_mr3",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"MPR_location",  1,0, ATUI_DEC,
				((LANG_ENG, u8"0=predefined pattern for read sync, 1,2,3=RFU"))
			),
			(u8"MPR_operation", 2,2, ATUI_DEC,
				((LANG_ENG, u8"0=normal, 1=dataflow from MPR"))
			),
			(u8"RFU_15_3",     15,3, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, gddr2_mr0, atui_nullstruct,
	(bios->gddr2_mr0, u8"gddr2_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"burst_length", 0,0, ATUI_DEC,
				((LANG_ENG, u8"0=4, 1=reserved"))
			),
			(u8"WL",           3,0, ATUI_DEC,
				((LANG_ENG, u8"1=1..7=7; 0=reserved"))
			),
			(u8"RL",           6,4, ATUI_DEC,
				((LANG_ENG, u8"8,9,10,rsvd,4,5,6,7"))
			),
			(u8"testmode",     7,7, ATUI_DEC,
				((LANG_ENG, u8"behaviour is vendor specific"))
			),
			(u8"DLL_reset",    8,8, ATUI_DEC,
				((LANG_ENG, u8"self clearing"))
			),
			(u8"WR",          11,9, ATUI_DEC,
				((LANG_ENG, u8"tWR=n+1; 0,1,7=reserved"))
			),
			(u8"rsvd_15_12",  15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr2_emr1, atui_nullstruct,
	(bios->gddr2_emr1, u8"gddr2_emr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"addrcmd_ODT",      1,0, ATUI_DEC,
				((LANG_ENG, u8"0=off 1=1xDQ, 2=2x, 3=4xDQ"))
			),
			(u8"data_ck_ODT",      3,2, ATUI_DEC,
				((LANG_ENG, u8"0=off, 1=auto cal., 2=60ohms, 3=120"))
			),
			(u8"additive_latency", 4,4, ATUI_DEC,
				((LANG_ENG, u8"0=0, 1=1"))
			),
			(u8"DQS",              5,5, ATUI_DEC,
				((LANG_ENG, u8"0=differential, 1=single"))
			),
			(u8"DLL",              6,6, ATUI_DEC,
				((LANG_ENG, u8"0=off, 1=on"))
			),
			(u8"driver_Ron",       9,7, ATUI_DEC,
				((LANG_ENG, u8"0=60, 1=55 ... 7=25"))
			),
			(u8"rankness",        10,10, ATUI_DEC,
				((LANG_ENG, u8"0=single 1=multi"))
			),
			(u8"vendor_id",       11,11, ATUI_DEC,
				((LANG_ENG, u8"0=disabled 1=enabled"))
			),
			(u8"rsvd_15_12",      15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr2_emr2, atui_nullstruct,
	(bios->gddr2_emr2, u8"gddr2_emr2",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"rsvd_1_0",         1,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ODT_at_powerdown", 2,2, ATUI_DEC,
				((LANG_ENG, u8"0=all off except CK, CKE, 1=EMRS/EMRS2"))
			),
			(u8"low_power_mode",   3,3, ATUI_DEC,
				((LANG_ENG, u8"0=self-refresh, 1=fast wakeup"))
			),
			(u8"CK_ODT",           5,4, ATUI_DEC,
				((LANG_ENG, u8"0=off, 1=1xDQ, 2=2x, 3=4xDQ"))
			),
			(u8"CS_ODT",           7,6, ATUI_DEC,
				((LANG_ENG, u8"0=off, 1=0.5x addrcmd, 2=1x, 3=reserved"))
			),
			(u8"CKE_ODT",          8,8, ATUI_DEC,
				((LANG_ENG, u8"0=off, 1=addrcmd"))
			),
			(u8"ODT_W_mode",       9,9, ATUI_DEC,
				((LANG_ENG, u8"0=enable 1=disable. \"W\" mode??"))
			),
			(u8"rsvd_11_10",      11,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"rsvd_15_12",      15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, gddr3_mr0, atui_nullstruct,
	(bios->gddr3_mr0, u8"gddr3_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"burst_length", 1,0, ATUI_DEC,
				((LANG_ENG, u8"0,1=RFU, 2=BL4, 3=BL8"))
			),
			(u8"CL_hi_bit",    2,2, ATUI_DEC,
				((LANG_ENG, u8"A[2,6,5,4]->tCL[3:0] | JEDEC says A[3] is for BL; BL[2:0]"))
			),
			(u8"burst_type",   3,3, ATUI_DEC,
				((LANG_ENG, u8"0=sequential 1=RFU"))
			),
			(u8"CL_lo_bits",   6,4, ATUI_DEC,
				((LANG_ENG, u8"8,9,10,11,rsvd,5,6,7,12,13,14,15, rsvd..."))
			),
			(u8"test_mode",    7,7, ATUI_DEC,
				((LANG_ENG, u8"behaviour is vendor specific"))
			),
			(u8"DLL_reset",    8,8, ATUI_DEC,
				((LANG_ENG, u8"self clearing"))
			),
			(u8"tWL",         11,9, ATUI_DEC,
				((LANG_ENG, u8"0=reserved; tCWL"))
			),
			(u8"rsvd_15_12",  15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr3_emr1, atui_nullstruct, // page 14
	(bios->gddr3_emr1, u8"gddr3_emr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"drive_strength",  1,0, ATUI_DEC,
				((LANG_ENG, u8"0=auto cal. 1=30ohms, 2=40, 3=50"))
			),
			(u8"data_terminaton", 3,2, ATUI_DEC,
				((LANG_ENG, u8"0=ALL ODT disabled, 1=rsvd, 2=ZQ/4, 3=ZQ/2"))
			),
			(u8"WR_lo_bits",      5,4, ATUI_DEC,
				((LANG_ENG, u8"A[7,5,4] -> WR[2:0]; 11,13,5,6,7,8,9,10"))
			),
			(u8"DLL",             6,6, ATUI_DEC,
				((LANG_ENG, u8"0=enable"))
			),
			(u8"rsvd_8_8",        8,8, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"R_on",            8,8, ATUI_DEC,
				((LANG_ENG, u8"0=40 ohms, 1=60 ohms; pull-up"))
			),
			(u8"vendor_ID",      10,10, ATUI_DEC,
				((LANG_ENG, u8"0=off"))
			),
			(u8"AddrCmd_term",   11,11, ATUI_DEC,
				((LANG_ENG, u8"0=inherit CKE, 1=CKE/2"))
			),
			(u8"rsvd_15_12",     15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, gddr4_mr0, atui_nullstruct,
	(bios->gddr4_mr0, u8"gddr4_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"WR",        2,0, ATUI_DEC,
				((LANG_ENG, u8"Write recovery; 16,18,20, 6,8,10,12,14"))
			),
			(u8"tCL",       6,3, ATUI_DEC,
				((LANG_ENG, u8"16,17..21,22, 7,8,9..15"))
			),
			(u8"testmode",  7,7, ATUI_DEC,
				((LANG_ENG, u8"behaviour is vendor specific"))
			),
			(u8"DLL_reset", 8,8, ATUI_DEC,
				((LANG_ENG, u8"self clearing"))
			),
			(u8"WL",       11,9, ATUI_DEC,
				((LANG_ENG, u8"write latency; 0=RFU, 1=1..7=7"))
			),
			(u8"RFU_12",   12,12, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"ID",       15,13, ATUI_DEC,
				((LANG_ENG, u8"MR 0"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr4_emr1, atui_nullstruct,
	(bios->gddr4_emr1, u8"gddr4_emr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"Drive_Term", 1,0, ATUI_DEC,
				((LANG_ENG, u8"0=auto cal., 2=nominal (no compensation), 1,3=RFU. (drive: 40 down/60 up ; termination: 60/120; CA 60/120/240)"))
			),
			(u8"DQ_term",    3,2, ATUI_DEC,
				((LANG_ENG, u8"0=all off, 1=DQ off, 2=1/4, 3=1/2"))
			),
			(u8"tPreamble",  6,4, ATUI_DEC,
				((LANG_ENG, u8"0=1..  5..7=RFU. read/write preamble in tCK"))
			),
			(u8"DLL",        7,7, ATUI_DEC,
				((LANG_ENG, u8"0=enable"))
			),
			(u8"read_DBI",   8,8, ATUI_DEC,
				((LANG_ENG, u8"0=disable. data bus iversion"))
			),
			(u8"write_DBI",  9,9, ATUI_DEC,
				((LANG_ENG, u8"0=disable"))
			),
			(u8"DBI_mode",  10,10, ATUI_DEC,
				((LANG_ENG, u8"0=DC, 1=AC. optimise for DC/AC power reduction"))
			),
			(u8"Vendor_ID", 11,11, ATUI_DEC,
				((LANG_ENG, u8"0=disable"))
			),
			(u8"RFU_12",    12,12, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"ID",        15,13, ATUI_DEC,
				((LANG_ENG, u8"EMR 1"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr4_emr2, atui_nullstruct,
	(bios->gddr4_emr2, u8"gddr4_emr2",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"OCD_down_offset", 2,0, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, u8"Two's Compl. Driver/term pulldown offset"))
			),
			(u8"OCD_up_offset",   5,3, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, u8"Two's Compl. Driver/terminator pullup offset"))
			),
			(u8"tRAS",           11,6, ATUI_DEC,
				((LANG_ENG, u8"tRAS latency; 0=RFU, 1=1..63=63"))
			),
			(u8"RFU_12",         12,12, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"ID",             15,13, ATUI_DEC,
				((LANG_ENG, u8"EMR 2"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr4_emr3, atui_nullstruct,
	(bios->gddr4_emr3, u8"gddr4_emr3",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"RFU",           4,0, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"LP_term",       5,5, ATUI_DEC,
				((LANG_ENG, u8"0=disabled"))
			),
			(u8"DRAM_info",     7,6, ATUI_DEC,
				((LANG_ENG, u8"0=vendor ID, 1=PERR_Info, 2,3=vendor specific"))
			),
			(u8"parity_reset",  8,8, ATUI_DEC,
				((LANG_ENG, u8"0=store, 1=reset; clear PERR_Info"))
			),
			(u8"parity_enable", 9,9, ATUI_DEC,
				((LANG_ENG, u8"0=disable"))
			),
			(u8"parity_mask",  11,10, ATUI_DEC,
				((LANG_ENG, u8"0=DQ[7:0], 1=[15:8], 2=[23:16], 3=[31:24]"))
			),
			(u8"RFU_12",       12,12, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"ID",           15,13, ATUI_DEC,
				((LANG_ENG, u8"EMR 3"))
			)
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, gddr5_mr0, atui_nullstruct,
	(bios->gddr5_mr0, u8"gddr5_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"WLmrs",       2,0, ATUI_DEC,
				((LANG_ENG, u8"0=RFU 1=1..7=7"))
			),
			(u8"CLmrs_lo",    6,3, ATUI_DEC,
				((LANG_ENG, u8"tCL = 5+n. [MR8[0], MR0[6:3]] -> tCL[4:0]"))
			),
			(u8"testmode",    7,7, ATUI_DEC,
				((LANG_ENG, u8"behavior is vendor specific"))
			),
			(u8"WR",         11,8, ATUI_DEC,
				((LANG_ENG, u8"tWR = 4+n. [MR8[1], MR0[11:8]] -> tWR[4:0]"))
			),
			(u8"rsvd_15_12", 15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr1, atui_nullstruct,
	(bios->gddr5_mr1, u8"gddr5_mr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"drive_strength",     1,0, ATUI_DEC,
				((LANG_ENG, u8"0=auto cal., 1,3=vendor, 2=nom (60/40)"))
			),
			(u8"data_termination",   3,2, ATUI_DEC,
				((LANG_ENG, u8"0=disabled, 1=ZQ, 2=ZQ/2, 3=RFU"))
			),
			(u8"addrcmd_term",       5,4, ATUI_DEC,
				((LANG_ENG, u8"0=inherit CKE_n, 1=ZQ, 2=ZQ/2, 3=disabled"))
			),
			(u8"calibration_update", 6,6, ATUI_DEC,
				((LANG_ENG, u8"0=on; impedance calibration engine"))
			),
			(u8"PLL_DLL",            7,7, ATUI_DEC,
				((LANG_ENG, u8"0=off"))
			),
			(u8"read_DBI",           8,8, ATUI_DEC,
				((LANG_ENG, u8"0=on; data bus inversion"))
			),
			(u8"write_DBI",          9,9, ATUI_DEC,
				((LANG_ENG, u8"0=on; data bus inversion"))
			),
			(u8"address_BI",        10,10, ATUI_DEC,
				((LANG_ENG, u8"0=on; address bus inversion"))
			),
			(u8"PLLDLL_reset",      11,11, ATUI_DEC,
				((LANG_ENG, u8"self clearing"))
			),
			(u8"rsvd_15_12",        15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr2, atui_nullstruct,
	(bios->gddr5_mr2, u8"gddr5_mr2",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"drive_pulldown_offset", 2,0, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, u8"Two's Compl. vendor specific"))
			),
			(u8"drive_pullup_offset",   5,3, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, u8"Two's Compl. vendor specific"))
			),
			(u8"data_wck_term_offset",  8,6, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, u8"Two's Compl. vendor specific"))
			),
			(u8"AddrCmd_term_offset",  11,9, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, u8"Two's Compl. vendor specific"))
			),
			(u8"rsvd_15_12",           15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr3, atui_nullstruct,
	(bios->gddr5_mr3, u8"gddr5_mr3",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"self_refresh",    1,0, ATUI_DEC,
				((LANG_ENG, u8"0=32ms 1,2=vendor, 3=temp controlled"))
			),
			(u8"WCK01_invert",    2,2, ATUI_DEC,
				((LANG_ENG, u8"phase invert"))
			),
			(u8"WCK23_invert",    3,3, ATUI_DEC,
				((LANG_ENG, u8"phase invert"))
			),
			(u8"WCK2CK_training", 4,4, ATUI_DEC,
				((LANG_ENG, u8"0=off; WCK to CK alignment training"))
			),
			(u8"RDQS_mode",       5,5, ATUI_DEC,
				((LANG_ENG, u8"0=off; EDC becomes RDQS"))
			),
			(u8"DRAM_info",       7,6, ATUI_DEC,
				((LANG_ENG, u8"0=off, 1=vendor ID, 2=temp, 3=vemdor spec."))
			),
			(u8"WCK_termination", 9,8, ATUI_DEC,
				((LANG_ENG, u8"0=dis, 1=ZQ/2, 2=ZQ, 3=RFU"))
			),
			(u8"bank_groups",    11,10, ATUI_DEC,
				((LANG_ENG, u8"0,1=off, 2=on tCCDL=4, 3=on tCCL=3"))
			),
			(u8"rsvd_15_12",     15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr4, atui_nullstruct,
	(bios->gddr5_mr4, u8"gddr5_mr4",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"EDC_pattern",  3,0, ATUI_DEC,
				((LANG_ENG, u8"little-endian-based burst position"))
			),
			(u8"CRCWL",        6,4, ATUI_DEC,
				((LANG_ENG, u8"7+n; CRC write latency"))
			),
			(u8"CRCRL",        8,8, ATUI_DEC,
				((LANG_ENG, u8"4,1,2,3; CRC read laency"))
			),
			(u8"read_CRC",     9,9, ATUI_DEC,
				((LANG_ENG, u8"0=on"))
			),
			(u8"write_crc",   10,10, ATUI_DEC,
				((LANG_ENG, u8"0=on"))
			),
			(u8"hold_invert", 11,11, ATUI_DEC,
				((LANG_ENG, u8"1=inverted; EDC hold pattern inversion"))
			),
			(u8"rsvd_15_12",  15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr5, atui_nullstruct,
	(bios->gddr5_mr5, u8"gddr5_mr5",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"LP1",         0,0, ATUI_DEC,
				((LANG_ENG, u8"0=off; power saving, relaxed core"))
			),
			(u8"LP2",         1,1, ATUI_DEC,
				((LANG_ENG, u8"0=off; power saving, WCK off during powerdown"))
			),
			(u8"LP3",         2,2, ATUI_DEC,
				((LANG_ENG, u8"0=off; training during refresh disabled"))
			),
			(u8"PLLDLL_BW",   5,3, ATUI_DEC,
				((LANG_ENG, u8"vendor specific; PLL bandwidth"))
			),
			(u8"tRAS",       11,6, ATUI_DEC,
				((LANG_ENG, u8"0=RFU, 1=1..63=63"))
			),
			(u8"rsvd_15_12", 15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr6, atui_nullstruct,
	(bios->gddr5_mr6, u8"gddr5_mr6",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"WCK2CK_alignment", 0,0, ATUI_DEC,
				((LANG_ENG, u8"0=inside DRAM, 1=at balls"))
			),
			(u8"VREFD_merge",      1,1, ATUI_DEC,
				((LANG_ENG, u8"0=off 1=average VREFD and internal vref"))
			),
			(u8"VREFD_training",   2,2, ATUI_DEC,
				((LANG_ENG, u8"0=ff 1=train; self clearing"))
			),
			(u8"VREFD_source",     3,3, ATUI_DEC,
				((LANG_ENG, u8"0=VREFD pins, 1=internally generated"))
			),
			(u8"VREFD_offset_MU",  7,4, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, u8"semi Two's Compl. -8 = 0/auto"))
			),
			(u8"VREFD_offset_AF", 11,8, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, u8"semi Two's Compl. -8 = 0/auto"))
			),
			(u8"rsvd_15_12",      15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr7, atui_nullstruct,
	(bios->gddr5_mr7, u8"gddr5_mr7",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"PLL_standby",     0,0, ATUI_DEC,
				((LANG_ENG, u8"0=off 1=standby when self-refresh"))
			),
			(u8"PLL_fast_lock",   1,1, ATUI_DEC,
				((LANG_ENG, u8"1=faster lock but higher power; self clears"))
			),
			(u8"PLL_delay_comp",  2,2, ATUI_DEC,
				((LANG_ENG, u8"1=PLL feedback = WCK clock tree delay"))
			),
			(u8"low_freq_mode",   3,3, ATUI_DEC,
				((LANG_ENG, u8"1=reduced power for low freq"))
			),
			(u8"WCK2CK_autosync", 4,4, ATUI_DEC,
				((LANG_ENG, u8"1=auto WCK2CK after PD exit"))
			),
			(u8"DQ_preamble",     5,5, ATUI_DEC,
				((LANG_ENG, u8"1=non-gapped READs will have 4UI preamble"))
			),
			(u8"temp_sensor",     6,6, ATUI_DEC,
				((LANG_ENG, u8"1=enable temperature sense"))
			),
			(u8"half_VREFD",      7,7, ATUI_DEC,
				((LANG_ENG, u8"0=0.7x 1=0.5x VDDQ"))
			),
			(u8"VDD_range",       9,8, ATUI_DEC,
				((LANG_ENG, u8"0=1.5V 1,2,3=vendor; adapt to different VDD"))
			),
			(u8"DCC",            11,10, ATUI_DEC,
				((LANG_ENG, u8"0=off, 1=start, 2=reset, 3=RFU; Duty Cycle Correction"))
			),
			(u8"rsvd_15_12",     15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr8, atui_nullstruct,
	(bios->gddr5_mr8, u8"gddr5_mr8",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"CL_EHF",      0,0, ATUI_DEC,
				((LANG_ENG, u8"tCL range extension; see MR0"))
			),
			(u8"WR_EHF",      1,1, ATUI_DEC,
				((LANG_ENG, u8"tWR range extension; see MR0"))
			),
			(u8"EDC_HiZ",     2,2, ATUI_DEC,
				((LANG_ENG, u8"1=Hi-Z state; precedence over all other states"))
			),
			(u8"REFPB",       3,3, ATUI_DEC,
				((LANG_ENG, u8"1=per-bank refresh feature enable"))
			),
			(u8"rsvd_11_4",  11,4, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"rsvd_15_12", 15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr9, atui_nullstruct,
	(bios->gddr5_mr9, u8"gddr5_mr9",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"vendor_specific", 11,0, ATUI_DEC,
				((LANG_ENG, u8"vendor specific features."))
			),
			(u8"rsvd_15_12",      15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr10, atui_nullstruct,
	(bios->gddr5_mr10, u8"gddr5_mr10",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"vendor_specific", 11,0, ATUI_DEC,
				((LANG_ENG, u8"vendor specific features."))
			),
			(u8"rsvd_15_12",      15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr11, atui_nullstruct,
	(bios->gddr5_mr11, u8"gddr5_mr11",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"PASR_banks_01",   0,0, ATUI_DEC,
				((LANG_ENG, u8"exclude banks 0, 1"))
			),
			(u8"PASR_banks_23",   1,1, ATUI_DEC,
				((LANG_ENG, u8"exclude banks 2, 3"))
			),
			(u8"PASR_banks_45",   2,2, ATUI_DEC,
				((LANG_ENG, u8"exclude banks 4, 5"))
			),
			(u8"PASR_banks_67",   3,3, ATUI_DEC,
				((LANG_ENG, u8"exclude banks 6, 7"))
			),
			(u8"PASR_banks_89",   4,4, ATUI_DEC,
				((LANG_ENG, u8"exclude banks 8, 9"))
			),
			(u8"PASR_banks_1011", 5,5, ATUI_DEC,
				((LANG_ENG, u8"exclude banks 10, 11"))
			),
			(u8"PASR_banks_1213", 6,6, ATUI_DEC,
				((LANG_ENG, u8"exclude banks 12, 13"))
			),
			(u8"PASR_banks_1415", 7,7, ATUI_DEC,
				((LANG_ENG, u8"exclude banks 14, 15"))
			),
			(u8"PASR_row_00",     8,8, ATUI_DEC,
				((LANG_ENG, u8"exclude row segment A[13:12]=00 (MSB)"))
			),
			(u8"PASR_row_01",     9,9, ATUI_DEC,
				((LANG_ENG, u8"exclude row segment A[13:12]=01 (MSB)"))
			),
			(u8"PASR_row_10",    10,10, ATUI_DEC,
				((LANG_ENG, u8"exclude row segment A[13:12]=10 (MSB)"))
			),
			(u8"PASR_row_11",    11,11, ATUI_DEC,
				((LANG_ENG, u8"exclude row segment A[13:12]=11 (MSB)"))
			),
			(u8"rsvd_15_12",     15,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PASR_bank_mask",         7,0, ATUI_DEC,
				((LANG_ENG, u8"bank exclusion mask"))
			),
			(u8"PASR_row_segment_mask", 11,8, ATUI_DEC,
				((LANG_ENG, u8"row exclusion mask"))
			),
			(u8"rsvd_15_12__2",         15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr12, atui_nullstruct,
	(bios->gddr5_mr12, u8"gddr5_mr12",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"vendor_specific", 11,0, ATUI_DEC,
				((LANG_ENG, u8"vendor specific features."))
			),
			(u8"rsvd_15_12",      15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr13, atui_nullstruct,
	(bios->gddr5_mr13, u8"gddr5_mr13",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"vendor_specific", 11,0, ATUI_DEC,
				((LANG_ENG, u8"vendor specific features."))
			),
			(u8"rsvd_15_12",      15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr14, atui_nullstruct,
	(bios->gddr5_mr14, u8"gddr5_mr14",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"vendor_specific", 11,0, ATUI_DEC,
				((LANG_ENG, u8"vendor specific features."))
			),
			(u8"rsvd_15_12",      15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr5_mr15, atui_nullstruct,
	(bios->gddr5_mr15, u8"gddr5_mr15",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"rsvd_7_0",          7,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MRE_0_disable",     8,8, ATUI_DEC,
				((LANG_ENG, u8"1=disable MRS commands on channel 0"))
			),
			(u8"MRE_1_disable",     9,9, ATUI_DEC,
				((LANG_ENG, u8"1=disable MRS commands on channel 1"))
			),
			(u8"address_training", 10,10, ATUI_DEC,
				((LANG_ENG, u8"1=address training mode"))
			),
			(u8"RFU",              11,11, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"rsvd_15_12",       15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, gddr6_mr0, atui_nullstruct,
	(bios->gddr6_mr0, u8"gddr6_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"WLmrs",    2,0, ATUI_DEC,
				((LANG_ENG, u8"tCWL, 8,9,10,11,12,5,6,7."))
			),
			(u8"RLmrs_lo", 6,3, ATUI_DEC,
				((LANG_ENG, u8"tCL = 5+n. [MR12[3], MR8[8], MR0[6:3]] -> tCL[5:0]"))
			),
			(u8"testmode", 7,7, ATUI_DEC,
				((LANG_ENG, u8"Test mode; behavior is vendor specific"))
			),
			(u8"WRmrs",   11,8, ATUI_DEC,
				((LANG_ENG, u8"tWR for auto-pre, 0=4,1=5..47=51. See MR8, MR12"))
			),
			(u8"ID",      15,12, ATUI_DEC,
				((LANG_ENG, u8"MR 0"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr1, atui_nullstruct,
	(bios->gddr6_mr1, u8"gddr6_mr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"drive_stren",   1,0, ATUI_DEC,
				((LANG_ENG, u8"0=Auto Cal.(60/40), 1=AC(48/40). 2,3 vndr spec"))
			),
			(u8"data_term",     3,2, ATUI_DEC,
				((LANG_ENG, u8"0=disabled 1=60ohm 2=120ohm 3=48ohm"))
			),
			(u8"PLLDLL_range",  5,4, ATUI_DEC,
				((LANG_ENG, u8"min-to-max WCK freq, vendor specific"))
			),
			(u8"Cal_Upd",       6,6, ATUI_DEC,
				((LANG_ENG, u8"Auto Calibration Engine, 0=enabled."))
			),
			(u8"PLL_DLL",       7,7, ATUI_DEC,
				((LANG_ENG, u8"0=disabled 1=enabled"))
			),
			(u8"read_DBI",      8,8, ATUI_DEC,
				((LANG_ENG, u8"Data Bus Inversion, for reads.   0=enabled"))
			),
			(u8"write_DBI",     9,9, ATUI_DEC,
				((LANG_ENG, u8"Data Bus Inversion, for writes.  1=disabled"))
			),
			(u8"addrcmd_BI",   10,10, ATUI_DEC,
				((LANG_ENG, u8"Command-address bus inversion.  0=enabled"))
			),
			(u8"PLLDLL_reset", 14,11, ATUI_DEC,
				((LANG_ENG, u8"1 = reset. self-clears after reset."))
			),
			(u8"ID",           15,12, ATUI_DEC,
				((LANG_ENG, u8"MR 1"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr2, atui_nullstruct,
	(bios->gddr6_mr2, u8"gddr6_mr2",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"OCD_up",       2,0, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, u8"output driver pullup offset. 0=0, Two's Compl."))
			),
			(u8"OCD_down",     5,3, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, u8"pulldown. See JES250D Figure 33."))
			),
			(u8"self_refresh", 7,6, ATUI_DEC,
				((LANG_ENG, u8"0=32ms, 1-2 vendor specific, 3=temp controlled"))
			),
			(u8"EDC_mode",     8,8, ATUI_DEC,
				((LANG_ENG, u8"0=full data rate, 1=half"))
			),
			(u8"RDQS",         9,9, ATUI_DEC,
				((LANG_ENG, u8"1 = EDC pins will act as RDQS; no CRC."))
			),
			(u8"CADT_SRF",    10,10, ATUI_DEC,
				((LANG_ENG, u8"Self refesh while CA training"))
			),
			(u8"EDC_HR",      11,11, ATUI_DEC,
				((LANG_ENG, u8"EDC hold data rate 0=full, 1=half"))
			),
			(u8"ID",          15,12, ATUI_DEC,
				((LANG_ENG, u8"MR 2"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr3, atui_nullstruct,
	(bios->gddr6_mr3, u8"gddr6_mr3",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"dataWCK_term_offset", 2,0, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, u8"DQ, DBI & WCK termination offset. Two's"))
			),
			(u8"CA_term_offset",      5,3, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, u8"command address. See MR2."))
			),
			(u8"DRAM_info",           7,6, ATUI_DEC,
				((LANG_ENG, u8"0=off 1=vndr ID1 2=temp 3=vndr ID2"))
			),
			(u8"WR_scaling",          9,8, ATUI_DEC,
				((LANG_ENG, u8"1x 2x 3x value of tWR in MR8 and MR0"))
			),
			(u8"bank_groups",        11,10, ATUI_DEC,
				((LANG_ENG, u8"0,1=off, 2=on tCCDL=4, 3=on tCCDL=3"))
			),
			(u8"ID",                 15,12, ATUI_DEC,
				((LANG_ENG, u8"MR 3"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr4, atui_nullstruct,
	(bios->gddr6_mr4, u8"gddr6_mr4",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"EDC_hold_pattern", 3,0, ATUI_DEC,
				((LANG_ENG, u8"little-endian. pattern during EDC idle"))
			),
			(u8"CRCWL",            6,4, ATUI_DEC,
				((LANG_ENG, u8"15,16,RFU,10,11..21,RFU. See MR12 OP4"))
			),
			(u8"CRCRL",            8,7, ATUI_DEC,
				((LANG_ENG, u8"CRC latency for reads. 4,1,2,3."))
			),
			(u8"RDCRC",            9,9, ATUI_DEC,
				((LANG_ENG, u8"read CRC 0=enable"))
			),
			(u8"WRCRC",           10,10, ATUI_DEC,
				((LANG_ENG, u8"write CRC 0=enable"))
			),
			(u8"EDC_hold_invert", 11,11, ATUI_DEC,
				((LANG_ENG, u8"0 = EDC hold pattern not inverted"))
			),
			(u8"ID",              15,12, ATUI_DEC,
				((LANG_ENG, u8"MR 4"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr5, atui_nullstruct,
	(bios->gddr6_mr5, u8"gddr6_mr5",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"LP1",       0,0, ATUI_DEC,
				((LANG_ENG, u8"0=off, Low Power Mode 1, relax several core params"))
			),
			(u8"LP2",       1,1, ATUI_DEC,
				((LANG_ENG, u8"WCK recievers turned off during powerdown."))
			),
			(u8"LP3",       2,2, ATUI_DEC,
				((LANG_ENG, u8"no read/write training and temp reads during REFab"))
			),
			(u8"PLLDLL_BW", 5,3, ATUI_DEC,
				((LANG_ENG, u8"PLL/DLL bandwidth. All except 0 vendor specific"))
			),
			(u8"RAS",      11,6, ATUI_DEC,
				((LANG_ENG, u8"0,1,2...63. tRAS for auto precharge"))
			),
			(u8"ID",       15,12, ATUI_DEC,
				((LANG_ENG, u8"MR 5"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr6, atui_nullstruct,
	(bios->gddr6_mr6, u8"gddr6_mr6",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"VREFD_level",  6,0, ATUI_DEC,
				((LANG_ENG, u8"0.005x steps of VDDQ, from 0=0.49x to 95=0.965x"))
			),
			(u8"pin_subaddr", 11,7, ATUI_DEC,
				((LANG_ENG, u8"pin to configure the VREFD for. See JESD250"))
			),
			(u8"ID",          15,12, ATUI_DEC,
				((LANG_ENG, u8"MR 6"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr7, atui_nullstruct,
	(bios->gddr6_mr7, u8"gddr6_mr7",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"WCK2CK_AP",       0,0, ATUI_DEC,
				((LANG_ENG, u8"WCK alignment point. 0=inside 1=at balls"))
			),
			(u8"hibernate",       1,1, ATUI_DEC,
				((LANG_ENG, u8"1=Hibernate Self Refresh mode. self clearing"))
			),
			(u8"PLL_delay_comp",  2,2, ATUI_DEC,
				((LANG_ENG, u8"1=(PLL feedback delay == WCK clock tree)"))
			),
			(u8"low_freq_mode",   3,3, ATUI_DEC,
				((LANG_ENG, u8"1=reduce power of input RX, clock trees"))
			),
			(u8"WCK2CK_autosync", 4,4, ATUI_DEC,
				((LANG_ENG, u8"1=auto sync, reduces WCK2CK MRS to 2."))
			),
			(u8"DQ_preamble",     5,5, ATUI_DEC,
				((LANG_ENG, u8"1=preamble on DQ, DBI_n for gapped reads."))
			),
			(u8"half_VREFC",      6,6, ATUI_DEC,
				((LANG_ENG, u8"0=0.7x VDDQ, 1=0.5x See MR6, MR9"))
			),
			(u8"half_VREFD",      7,7, ATUI_DEC,
				((LANG_ENG, u8"0=prog'd VREFD,DFE. 1=0.5x VDDQ. See MR6,MR9"))
			),
			(u8"VDD_range",       9,8, ATUI_DEC,
				((LANG_ENG, u8"0>1>2>3. Adapt to lower VDD voltages"))
			),
			(u8"WCK_DCC",        11,10, ATUI_DEC,
				((LANG_ENG, u8"Duty Cycle Corr. 0=off,1=start,2=RFU,3=hold"))
			),
			(u8"ID",             15,12, ATUI_DEC,
				((LANG_ENG, u8"MR 7"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr8, atui_nullstruct,
	(bios->gddr6_mr8, u8"gddr6_mr8",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"CA_low_term",  1,0, ATUI_DEC,
				((LANG_ENG, u8"0=disable, 1=60ohm, 2=120, 3=rsvd. For CA[3:0]"))
			),
			(u8"CA_high_term", 3,2, ATUI_DEC,
				((LANG_ENG, u8"For CA[10:4]"))
			),
			(u8"CA_TO",        4,4, ATUI_DEC,
				((LANG_ENG, u8"Command Address Termin. Override 1=use CAL,CAH"))
			),
			(u8"EDC_hiZ",      5,5, ATUI_DEC,
				((LANG_ENG, u8"1=Hi-Z state. Precidence over all other states."))
			),
			(u8"CK_auto_cal",  6,6, ATUI_DEC,
				((LANG_ENG, u8"0=auto calib. during REFab disabled, 1=enabled"))
			),
			(u8"REFpb",        7,7, ATUI_DEC,
				((LANG_ENG, u8"0=per-bank, 1=per-2-bank"))
			),
			(u8"RL_EHF",       8,8, ATUI_DEC,
				((LANG_ENG, u8"Extends RLmrs of MR0 from 4 to 5 bits."))
			),
			(u8"WR_EHF",       9,9, ATUI_DEC,
				((LANG_ENG, u8"Extends WRmrs of MR0 from 4 to 5 bits."))
			),
			(u8"CK_term",     11,10, ATUI_DEC,
				((LANG_ENG, u8"0=reset, 1=60ohm,2=120-ohm, 3=disabled"))
			),
			(u8"ID",          15,12, ATUI_DEC,
				((LANG_ENG, u8"MR 8"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr9, atui_nullstruct,
	(bios->gddr6_mr9, u8"gddr6_mr9",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"DFE",          3,0, ATUI_DEC,
				((LANG_ENG, u8"0=off, in steps of +-0.5% VDDQ or 7mV"))
			),
			(u8"RFU",          6,4, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"pin_subaddr", 11,7, ATUI_DEC,
				((LANG_ENG, u8"see JESD250"))
			),
			(u8"ID",          15,12, ATUI_DEC,
				((LANG_ENG, u8"MR 9"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr10, atui_nullstruct,
	(bios->gddr6_mr10, u8"gddr6_mr10",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"VREFC_offset",  3,0, (ATUI_DEC|ATUI_SIGNED),
				((LANG_ENG, u8"CA bus. semi Two's Complement: -8=0"))
			),
			(u8"WCK_inv_byte0", 5,4, ATUI_DEC,
				((LANG_ENG, u8"for WCK2CK training 0=0;1=90 degr;2=180;3=270"))
			),
			(u8"WCK_inv_byte1", 7,6, ATUI_DEC,
				((LANG_ENG, u8"B1 on chan A, B0 on chan B ignored if WCK/word"))
			),
			(u8"WCK2CK",        8,8, ATUI_DEC,
				((LANG_ENG, u8"1=enable WCK2CK alignment training"))
			),
			(u8"WCK_ratio",     9,9, ATUI_DEC,
				((LANG_ENG, u8"0=half data rate, 1=full data rate"))
			),
			(u8"WCK_term",     11,10, ATUI_DEC,
				((LANG_ENG, u8"0=disabled, 1=60 ohm, 2=120, 3=reserved"))
			),
			(u8"ID",           15,12, ATUI_DEC,
				((LANG_ENG, u8"MR 10"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr11, atui_nullstruct,
	(bios->gddr6_mr11, u8"gddr6_mr11",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"PASR_banks_01",   0,0, ATUI_DEC,
				((LANG_ENG, u8"exclude banks 0, 1"))),
			(u8"PASR_banks_23",   1,1, ATUI_DEC,
				((LANG_ENG, u8"exclude banks 2, 3"))),
			(u8"PASR_banks_45",   2,2, ATUI_DEC,
				((LANG_ENG, u8"exclude banks 4, 5"))),
			(u8"PASR_banks_67",   3,3, ATUI_DEC,
				((LANG_ENG, u8"exclude banks 6, 7"))),
			(u8"PASR_banks_89",   4,4, ATUI_DEC,
				((LANG_ENG, u8"exclude banks 8, 9"))),
			(u8"PASR_banks_1011", 5,5, ATUI_DEC,
				((LANG_ENG, u8"exclude banks 10, 11"))),
			(u8"PASR_banks_1213", 6,6, ATUI_DEC,
				((LANG_ENG, u8"exclude banks 12, 13"))),
			(u8"PASR_banks_1415", 7,7, ATUI_DEC,
				((LANG_ENG, u8"exclude banks 14, 15"))),
			(u8"PASR_row_00",     8,8, ATUI_DEC,
				((LANG_ENG, u8"exclude row segment R[13:12]=00 (MSB)"))),
			(u8"PASR_row_01",     9,9, ATUI_DEC,
				((LANG_ENG, u8"exclude row segment R[13:12]=01 (MSB)"))),
			(u8"PASR_row_10",    10,10, ATUI_DEC,
				((LANG_ENG, u8"exclude row segment R[13:12]=10 (MSB)"))),
			(u8"PASR_row_11",    11,11, ATUI_DEC,
				((LANG_ENG, u8"exclude row segment R[13:12]=11 (MSB)"))),
			(u8"ID",             15,12, ATUI_DEC,
				((LANG_ENG, u8"MR 11"))),
			(u8"PASR_bank_mask",         7,0, ATUI_DEC,
				((LANG_ENG, u8"bank exclusion mask"))),
			(u8"PASR_row_segment_mask", 11,8, ATUI_DEC,
				((LANG_ENG, u8"row exclusion mask"))),
			(u8"ID__2",                 15,12, ATUI_DEC,
				((LANG_ENG, u8"MR 11")))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr12, atui_nullstruct,
	(bios->gddr6_mr12, u8"gddr6_mr12",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"VDDQ_off",  0,0, ATUI_DEC,
				((LANG_ENG, u8"0=disabled. For Hibernate Self Refresh"))
			),
			(u8"P2BR_addr", 1,1, ATUI_DEC,
				((LANG_ENG, u8"0=LSB/BA0 1=MSB/BA3. Select \"Dont Care\" for REFp2b"))
			),
			(u8"PRBS",      2,2, ATUI_DEC,
				((LANG_ENG, u8"1=Psudorandom bit stream instead of EDC hold"))
			),
			(u8"RL_EHF2",   3,3, ATUI_DEC,
				((LANG_ENG, u8"Extends RLmrs from 5 bits to 6 bits. See MR0, MR8"))
			),
			(u8"CRCWL_EHF", 4,4, ATUI_DEC,
				((LANG_ENG, u8"Extends CRCWL from 3 bits to 4 bits. See MR4."))
			),
			(u8"WR_EHF2",   5,5, ATUI_DEC,
				((LANG_ENG, u8"Extends WRmrs from 5 bits to 6 bits. See MR0, MR8"))
			),
			(u8"RFU",      11,6, ATUI_DEC,
				((LANG_ENG, u8"reserved."))
			),
			(u8"ID",       15,12, ATUI_DEC,
				((LANG_ENG, u8"MR 12"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr13, atui_nullstruct,
	(bios->gddr6_mr13, u8"gddr6_mr13",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"vendor_specific", 11,0, ATUI_DEC,
				((LANG_ENG, u8"vendor specific features."))
			),
			(u8"ID",              15,12, ATUI_DEC,
				((LANG_ENG, u8"MR 13"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr14, atui_nullstruct,
	(bios->gddr6_mr14, u8"gddr6_mr14",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"vendor_specific", 11,0, ATUI_DEC,
				((LANG_ENG, u8"vendor specific features."))
			),
			(u8"ID",              15,12, ATUI_DEC,
				((LANG_ENG, u8"MR 14"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr15, atui_nullstruct,
	(bios->gddr6_mr15, u8"gddr6_mr15",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"MRS_to_chan_A", 0,0, ATUI_DEC,
				((LANG_ENG, u8"MRS to the two channels for individual config"))
			),
			(u8"MRS_to_chan_B", 1,1, ATUI_DEC,
				((LANG_ENG, u8"0=unblocked 1=blocked"))
			),
			(u8"CA_training",   3,2, ATUI_DEC,
				((LANG_ENG, u8"0=off 1=rising of CK, 2=falling, 3=CABI_n,CA10"))
			),
			(u8"unused",        11,4, ATUI_DEC,
				((LANG_ENG, u8"defined to be absent"))
			),
			(u8"ID",            15,12, ATUI_DEC,
				((LANG_ENG, u8"MR 15"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, hbm_mr0, atui_nullstruct,
	(bios->hbm_mr0, u8"hbm_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"read_DBI",       0,0, ATUI_DEC,
				((LANG_ENG, u8"1=enable; data bus inversion, AC."))
			),
			(u8"write_DBI",      1,1, ATUI_DEC,
				((LANG_ENG, u8"1=enable; data bus inversion, AC."))
			),
			(u8"TCSR",           2,2, ATUI_DEC,
				((LANG_ENG, u8"1=enable; temperature-controlled self-refresh"))
			),
			(u8"rsvd_3_3",       3,3, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"read_parity",    4,4, ATUI_DEC,
				((LANG_ENG, u8"0=disable; DQ parity"))
			),
			(u8"write_parity",   5,5, ATUI_DEC,
				((LANG_ENG, u8"0=disable; DQ parity"))
			),
			(u8"addrcmd_parity", 6,6, ATUI_DEC,
				((LANG_ENG, u8"0=disable; command-address parity"))
			),
			(u8"test_mode",      7,7, ATUI_DEC,
				((LANG_ENG, u8"1=Test mode; behavior is vendor specific"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr1, atui_nullstruct,
	(bios->hbm_mr1, u8"hbm_mr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tWR",       4,0, ATUI_DEC,
				((LANG_ENG, u8"3=3,4=4...31=31. 0..2=reserved"))
			),
			(u8"nom_drive", 7,5, ATUI_DEC,
				((LANG_ENG, u8"6mA,9,12,15,18, 5..7=reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr2, atui_nullstruct,
	(bios->hbm_mr2, u8"hbm_mr2",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"WL", 2,0, ATUI_DEC,
				((LANG_ENG, u8"[MR4[4], MR2[2:0]] -> WL[3:0]; tWL=1+n"))
			),
			(u8"RL", 7,3, ATUI_DEC,
				((LANG_ENG, u8"[MR4[5], MR2[7:3]] -> RL[5:0]; tRL=2+n"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr3, atui_nullstruct,
	(bios->hbm_mr3, u8"hbm_mr3",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tRAS",         5,0, ATUI_DEC,
				((LANG_ENG, u8"3=3... 63=63; 0,1,2=reserved"))
			),
			(u8"bank_groups",  6,6, ATUI_DEC,
				((LANG_ENG, u8"1=enable"))
			),
			(u8"burst_length", 7,7, ATUI_DEC,
				((LANG_ENG, u8"0=BL2, 1=BL4"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr4, atui_nullstruct,
	(bios->hbm_mr4, u8"hbm_mr4",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"ECC",      0,0, ATUI_DEC,
				((LANG_ENG, u8"0=disabled; ECC and WDM are mutually exlusive."))
			),
			(u8"WDM",      1,1, ATUI_DEC,
				((LANG_ENG, u8"0=enabled; write data mask"))
			),
			(u8"PL",       3,2, ATUI_DEC,
				((LANG_ENG, u8"0=0..3=3; parity latency"))
			),
			(u8"EWL",      4,4, ATUI_DEC,
				((LANG_ENG, u8"extended write latency; see MR0"))
			),
			(u8"ERL",      5,5, ATUI_DEC,
				((LANG_ENG, u8"extended read latency; see MR0"))
			),
			(u8"reserved", 7,6, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr5, atui_nullstruct,
	(bios->hbm_mr5, u8"hbm_mr5",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"TRR_bank_address", 3,0, ATUI_DEC,
				((LANG_ENG, u8"0=0; target bank of target row"))
			),
			(u8"reserved",         5,4, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"TRR_peudochannel", 6,6, ATUI_DEC,
				((LANG_ENG, u8"0=PC0, 1=PC1"))
			),
			(u8"TRR_mode",         7,7, ATUI_DEC,
				((LANG_ENG, u8"0=disable; Target Row Refresh for rowhammer"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr6, atui_nullstruct,
	(bios->hbm_mr6, u8"hbm_mr6",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"reserved",    2,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"implicit_RP", 7,3, ATUI_DEC,
				((LANG_ENG, u8"tRP=n+2; imPRE has PRE implied with ACT."))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr7, atui_nullstruct,
	(bios->hbm_mr7, u8"hbm_mr7",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"DWORD_loopback", 0,0, ATUI_DEC,
				((LANG_ENG, u8"0=disable; 1=link test (MISR) mode"))
			),
			(u8"DWORD_read_mux", 2,1, ATUI_DEC,
				((LANG_ENG, u8"1=MISR regs, 2=Rx path, 3=LFSR sticky"))
			),
			(u8"DWORD_MISR",     5,3, ATUI_DEC,
				((LANG_ENG, u8"0=preset 0xAAAAA/0x00000, 1=LFSR read, 2=register (R/W), 3=MISR write, 4=LFSR write"))
			),
			(u8"reserved",       6,6, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"CATTRIP",        7,7, ATUI_DEC,
				((LANG_ENG, u8"0=clear pin, 1=assert to 1."))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr8, atui_nullstruct,
	(bios->hbm_mr8, u8"hbm_mr8",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"DA28_lockout", 0,0, ATUI_DEC,
				((LANG_ENG, u8"1=if on chan A or E, hardlock DA port"))
			),
			(u8"reserved", 7,1, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr9, atui_nullstruct,
	(bios->hbm_mr9, u8"hbm_mr9",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"reserved", 7,0, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr10, atui_nullstruct,
	(bios->hbm_mr10, u8"hbm_mr10",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"reserved", 7,0, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr11, atui_nullstruct,
	(bios->hbm_mr11, u8"hbm_mr11",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"reserved", 7,0, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr12, atui_nullstruct,
	(bios->hbm_mr12, u8"hbm_mr12",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"reserved", 7,0, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr13, atui_nullstruct,
	(bios->hbm_mr13, u8"hbm_mr13",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"reserved", 7,0, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr14, atui_nullstruct,
	(bios->hbm_mr14, u8"hbm_mr14",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"reserved", 7,0, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm_mr15, atui_nullstruct,
	(bios->hbm_mr15, u8"hbm_mr15",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"internal_vref", 2,0, ATUI_DEC,
				((LANG_ENG, u8"Two's: 0.50 - 0.04*n; 0=.50, 1=.46, 4=.54"))
			),
			(u8"reserved", 7,3, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			)
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, hbm3_mr0, atui_nullstruct,
	(bios->hbm3_mr0, u8"hbm3_mr0",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"read_DBI",       0,0, ATUI_DEC,
				((LANG_ENG, u8"1=enable; data bus inversion, AC."))
			),
			(u8"write_DBI",      1,1, ATUI_DEC,
				((LANG_ENG, u8"1=enable; data bus inversion, AC."))
			),
			(u8"TCSR",           2,2, ATUI_DEC,
				((LANG_ENG, u8"1=enable; temperature-controlled self-refresh"))
			),
			(u8"rsvd_3_3",       3,3, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"read_parity",    4,4, ATUI_DEC,
				((LANG_ENG, u8"0=disable; DQ parity"))
			),
			(u8"write_parity",   5,5, ATUI_DEC,
				((LANG_ENG, u8"0=disable; DQ parity"))
			),
			(u8"addrcmd_parity", 6,6, ATUI_DEC,
				((LANG_ENG, u8"0=disable; command-address parity"))
			),
			(u8"test_mode",      7,7, ATUI_DEC,
				((LANG_ENG, u8"1=Test mode; behavior is vendor specific"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr1, atui_nullstruct,
	(bios->hbm3_mr1, u8"hbm3_mr1",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tWL", 4,0, ATUI_DEC,
				((LANG_ENG, u8"4=4..16=16,  0..3,17+ reserved"))
			),
			(u8"tPL", 7,5, ATUI_DEC,
				((LANG_ENG, u8"0=0..4=4, 5+ reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr2, atui_nullstruct,
	(bios->hbm3_mr2, u8"hbm3_mr2",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tRL", 7,0, ATUI_DEC,
				((LANG_ENG, u8"4=4..63=63,  0..3,64+ reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr3, atui_nullstruct,
	(bios->hbm3_mr3, u8"hbm3_mr3",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tWR", 7,0, ATUI_DEC,
				((LANG_ENG, u8"4=4..63=63,  0..3,64+ reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr4, atui_nullstruct,
	(bios->hbm3_mr4, u8"hbm3_mr4",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tRAS", 7,0, ATUI_DEC,
				((LANG_ENG, u8"4=4..63=63,  0..3,64+ reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr5, atui_nullstruct,
	(bios->hbm3_mr5, u8"hbm3_mr5",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"tRTP", 7,0, ATUI_DEC,
				((LANG_ENG, u8"2=2..15=15,  0,1 reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr6, atui_nullstruct,
	(bios->hbm3_mr6, u8"hbm3_mr6",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"drive_down_strength", 2,0, ATUI_DEC,
				((LANG_ENG, u8"0=8mA, 1=10, *2=12, 3=14, 4+ reserved"))
			),
			(u8"drive_up_strength",   5,3, ATUI_DEC,
				((LANG_ENG, u8"0=8mA, 1=10, *2=12, 3=14, 4+ reserved"))
			),
			(u8"reserved",            7,6, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr7, atui_nullstruct,
	(bios->hbm3_mr7, u8"hbm3_mr7",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"DWORD_loopback", 0,0, ATUI_DEC,
				((LANG_ENG, u8"0=disable; 1=link test (MISR) mode"))
			),
			(u8"DWORD_read_mux", 1,1, ATUI_DEC,
				((LANG_ENG, u8"0=MISR regs, 3=LFSR sticky"))
			),
			(u8"reserved_2_2",   2,2, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"DWORD_MISR",     5,3, ATUI_DEC,
				((LANG_ENG, u8"0=preset, 1=LFSR read, 2=register (R/W), 3=MISR write, 4=LFSR write"))
			),
			(u8"reserved_6_6",   6,6, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"CATTRIP",        7,7, ATUI_DEC,
				((LANG_ENG, u8"0=auto, 1=assert to 1."))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr8, atui_nullstruct,
	(bios->hbm3_mr8, u8"hbm3_mr8",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"DA_lockout",         0,0, ATUI_DEC,
				((LANG_ENG, u8"1=if on chan A or E, hardlock DA port"))
			),
			(u8"duty_cycle_monitor", 1,1, ATUI_DEC,
				((LANG_ENG, u8"0=disabled"))
			),
			(u8"ECS_log_auto_clear", 2,2, ATUI_DEC,
				((LANG_ENG, u8"0=disabled"))
			),
			(u8"WDQS2CK_training",   3,3, ATUI_DEC,
				((LANG_ENG, u8"0=disabled"))
			),
			(u8"RFM_levels",         5,4, ATUI_DEC,
				((LANG_ENG, u8"0=default, 1=A,2=B,3=C (1+ RFM required)"))
			),
			(u8"reserved",           7,6, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr9, atui_nullstruct,
	(bios->hbm3_mr9, u8"hbm3_mr9",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"metadata",           0,0, ATUI_DEC,
				((LANG_ENG, u8"1=read/writes have metadata"))
			),
			(u8"severity_reporting", 1,1, ATUI_DEC,
				((LANG_ENG, u8"1=repoting"))
			),
			(u8"ECC_testmode",       2,2, ATUI_DEC,
				((LANG_ENG, u8"0=disable ECC engine test mode"))
			),
			(u8"ECC_test_pattern",   3,3, ATUI_DEC,
				((LANG_ENG, u8"0=CW0 (1's are errors), 1=CW1 (0=error)"))
			),
			(u8"ECS_via_REFab",      4,4, ATUI_DEC,
				((LANG_ENG, u8"0=disabled"))
			),
			(u8"ECS_during_SRF",     5,5, ATUI_DEC,
				((LANG_ENG, u8"0=disabled"))
			),
			(u8"ECS_multibit",       6,6, ATUI_DEC,
				((LANG_ENG, u8"0=correction of multibit errors disabled"))
			),
			(u8"ECS_logging",        7,7, ATUI_DEC,
				((LANG_ENG, u8"0=maintain, 1=reset"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr10, atui_nullstruct,
	(bios->hbm3_mr10, u8"hbm3_mr10",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"vendor_specific", 7,0, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr11, atui_nullstruct,
	(bios->hbm3_mr11, u8"hbm3_mr11",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"DCA_WDQS0", 3,0, ATUI_DEC,
				((LANG_ENG, u8"broken Two's: 0=0, 7=-7, 8=reserved, 9=+1 15=+7"))
			),
			(u8"DCA_WDQS1", 7,4, ATUI_DEC,
				((LANG_ENG, u8"broken Two's: 0=0, 7=-7, 8=reserved, 9=+1 15=+7"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr12, atui_nullstruct,
	(bios->hbm3_mr12, u8"hbm3_mr12",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"vendor_specific", 7,0, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr13, atui_nullstruct,
	(bios->hbm3_mr13, u8"hbm3_mr13",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"reserved", 7,0, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr14, atui_nullstruct,
	(bios->hbm3_mr14, u8"hbm3_mr14",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"reserved_0_0", 0,0, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"VrefCA",       6,1, ATUI_DEC,
				((LANG_ENG, u8"0.18 + 0.01*n; 1=0.19, 63=.81. (32=.50)"))
			),
			(u8"reserved_7_7", 7,7, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, hbm3_mr15, atui_nullstruct,
	(bios->hbm3_mr15, u8"hbm3_mr15",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"reserved_0_0", 0,0, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			),
			(u8"VrefD",        6,1, ATUI_DEC,
				((LANG_ENG, u8"0.18 + 0.01*n; 1=0.19, 63=.81. (32=.50)"))
			),
			(u8"reserved_7_7", 7,7, ATUI_DEC,
				((LANG_ENG, u8"reserved"))
			)
		)), (ATUI_NODESCR)
	)
)


