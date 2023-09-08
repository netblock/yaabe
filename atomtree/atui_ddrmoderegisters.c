/*
For ddrmoderegisters.h
See atui_atomfirmware.c for how to use PPATUI_FUNCIFY()
*/

#include "atomtree.h"
#include "atui.h"

PPATUI_FUNCIFY(union, gddr6_mr0, atui_nullstruct,
	(bios->gddr6_mr0, gddr6_mr0,
		(ATUI_BIN, ATUI_BITFIELD, (
			(WLmrs,    2,0, ATUI_DEC,
				((LANG_ENG, "tCWL, 8,9,10,11,12,5,6,7."))
			),
			(RLmrs,    6,3, ATUI_DEC,
				((LANG_ENG, "tCL, starting from 5. See MR8 OP8, MR12 OP3"))
			),
			(testmode, 7,7, ATUI_DEC,
				((LANG_ENG, "Test mode; behavior is vendor specific"))
			),
			(WRmrs,   11,8, ATUI_DEC,
				((LANG_ENG, "tWR for auto-pre, 0=4,1=5..47=51. See MR8, MR12"))
			),
			(ID,      15,12, ATUI_DEC,
				((LANG_ENG, "MR 0"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, gddr6_mr1, atui_nullstruct,
	(bios->gddr6_mr1, gddr6_mr1,
		(ATUI_BIN, ATUI_BITFIELD, (
			(drive_stren,  1,0, ATUI_DEC,
				((LANG_ENG, "0=Auto Cal.(60/40), 1=AC(48/40). 2,3 vndr spec"))
			),
			(data_term,    3,2, ATUI_DEC,
				((LANG_ENG, "0=disabled 1=60ohm 2=120ohm 3=48ohm"))
			),
			(PLLDLL_range, 5,4, ATUI_DEC,
				((LANG_ENG, "min-to-max WCK freq, vendor specific"))
			),
			(Cal_Upd,      6,6, ATUI_DEC,
				((LANG_ENG, "Auto Calibration Engine, 0=enabled."))
			),
			(PLL_DLL,      7,7, ATUI_DEC,
				((LANG_ENG, "0=disabled 1=enabled"))
			),
			(RDBI,         8,8, ATUI_DEC,
				((LANG_ENG, "Data Bus Inversion, for reads.   0=enabled"))
			),
			(WDBI,         9,9, ATUI_DEC,
				((LANG_ENG, "Data Bus Inversion, for writes.  1=disabled"))
			),
			(CABI,        10,10, ATUI_DEC,
				((LANG_ENG, "Command-address bus inversion.  0=enabled"))
			),
			(PLLDLL_reset,14,11, ATUI_DEC,
				((LANG_ENG, "1 = reset. self-clears after reset."))
			),
			(ID,          15,12, ATUI_DEC,
				((LANG_ENG, "MR 1"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, gddr6_mr2, atui_nullstruct,
	(bios->gddr6_mr2, gddr6_mr2,
		(ATUI_BIN, ATUI_BITFIELD, (
			(OCD_up,       2,0, ATUI_DEC,
				((LANG_ENG, "output driver pullup offset. 0=0, Two's Compl."))
			),
			(OCD_down,     5,3, ATUI_DEC,
				((LANG_ENG, "pulldown. See JES250D Figure 33."))
			),
			(self_refresh, 7,6, ATUI_DEC,
				((LANG_ENG, "0=32ms, 1-2 vendor specific, 3=temp controlled"))
			),
			(EDC_mode,     8,8, ATUI_DEC,
				((LANG_ENG, "0=full data rate, 1=half"))
			),
			(RDQS,         9,9, ATUI_DEC,
				((LANG_ENG, "1 = EDC pins will act as RDQS; no CRC."))
			),
			(CADT_SRF,    10,10, ATUI_DEC,
				((LANG_ENG, "Self refesh while CA training"))
			),
			(EDC_HR,      11,11, ATUI_DEC,
				((LANG_ENG, "EDC hold data rate 0=full, 1=half"))
			),
			(ID,          15,12, ATUI_DEC,
				((LANG_ENG, "MR 2"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, gddr6_mr3, atui_nullstruct,
	(bios->gddr6_mr3, gddr6_mr3,
		(ATUI_BIN, ATUI_BITFIELD, (
			(dataWCK_term_offset, 2,0, ATUI_DEC,
				((LANG_ENG, "DQ, DBI and WCK termination offset."))
			),
			(CA_term_offset,      5,3, ATUI_DEC,
				((LANG_ENG, "command address. See MR2."))
			),
			(DRAM_info,           7,6, ATUI_DEC,
				((LANG_ENG, "0=off 1=vndr ID1 2=temp 3=vndr ID2"))
			),
			(WR_scaling,          9,8, ATUI_DEC,
				((LANG_ENG, "1x 2x 3x value of tWR in MR8 and MR0"))
			),
			(bank_groups,        11,10, ATUI_DEC,
				((LANG_ENG, "0,1=off, 2=on tCCDL=4, 3=on tCCDL=3"))
			),
			(ID,                 15,12, ATUI_DEC,
				((LANG_ENG, "MR 3"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, gddr6_mr4, atui_nullstruct,
	(bios->gddr6_mr4, gddr6_mr4,
		(ATUI_BIN, ATUI_BITFIELD, (
			(EDC_hold_pattern, 3,0, ATUI_DEC,
				((LANG_ENG, "little-endian. pattern during EDC idle"))
			),
			(CRCWL,            6,4, ATUI_DEC,
				((LANG_ENG, "15,16,RFU,10,11..21,RFU. See MR12 OP4"))
			),
			(CRCRL,            8,7, ATUI_DEC,
				((LANG_ENG, "CRC latency for reads. 4,1,2,3."))
			),
			(RDCRC,            9,9, ATUI_DEC,
				((LANG_ENG, "read CRC 0=enable"))
			),
			(WRCRC,           10,10, ATUI_DEC,
				((LANG_ENG, "write CRC 0=enable"))
			),
			(EDC_hold_invert, 11,11, ATUI_DEC,
				((LANG_ENG, "0 = EDC hold pattern not inverted"))
			),
			(ID,              15,12, ATUI_DEC,
				((LANG_ENG, "MR 4"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, gddr6_mr5, atui_nullstruct,
	(bios->gddr6_mr5, gddr6_mr5,
		(ATUI_BIN, ATUI_BITFIELD, (
			(LP1,       0,0, ATUI_DEC,
				((LANG_ENG, "0=off, Low Power Mode 1, relax several core params"))
			),
			(LP2,       1,1, ATUI_DEC,
				((LANG_ENG, "WCK recievers turned off during powerdown."))
			),
			(LP3,       2,2, ATUI_DEC,
				((LANG_ENG, "no read/write training and temp reads during REFab"))
			),
			(PLLDLL_BW, 5,3, ATUI_DEC,
				((LANG_ENG, "PLL/DLL bandwidth. All except 0 vendor specific"))
			),
			(RAS,      11,6, ATUI_DEC,
				((LANG_ENG, "0,1,2...63. tRAS for auto precharge"))
			),
			(ID,       15,12, ATUI_DEC,
				((LANG_ENG, "MR 5"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, gddr6_mr6, atui_nullstruct,
	(bios->gddr6_mr6, gddr6_mr6,
		(ATUI_BIN, ATUI_BITFIELD, (
			(VREFD_level,  6,0, ATUI_DEC,
				((LANG_ENG, "0.005x steps of VDDQ, from 0=0.49x to 95=0.965x"))
			),
			(pin_subaddr, 11,7, ATUI_DEC,
				((LANG_ENG, "pin to configure the VREFD for. See JESD250"))
			),
			(ID,          15,12, ATUI_DEC,
				((LANG_ENG, "MR 6"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, gddr6_mr7, atui_nullstruct,
	(bios->gddr6_mr7, gddr6_mr7,
		(ATUI_BIN, ATUI_BITFIELD, (
			(WCK2CK_AP,       0,0, ATUI_DEC,
				((LANG_ENG, "WCK alignment point. 0=inside 1=at balls"))
			),
			(hibernate,       1,1, ATUI_DEC,
				((LANG_ENG, "1=Hibernate Self Refresh mode. self clearing"))
			),
			(PLL_delay_comp,  2,2, ATUI_DEC,
				((LANG_ENG, "1=(PLL feedback delay == WCK clock tree)"))
			),
			(low_freq_mode,   3,3, ATUI_DEC,
				((LANG_ENG, "1=reduce power of input RX, clock trees"))
			),
			(WCK2CK_autosync, 4,4, ATUI_DEC,
				((LANG_ENG, "1=auto sync, reduces WCK2CK MRS to 2."))
			),
			(DQ_preamble,     5,5, ATUI_DEC,
				((LANG_ENG, "1=preamble on DQ, DBI_n for gapped reads."))
			),
			(half_VREFC,      6,6, ATUI_DEC,
				((LANG_ENG, "0=0.7x VDDQ, 1=0.5x See MR6, MR9"))
			),
			(half_VREFD,      7,7, ATUI_DEC,
				((LANG_ENG, "0=prog'd VREFD,DFE. 1=0.5x VDDQ. See MR6,MR9"))
			),
			(VDD_range,       9,8, ATUI_DEC,
				((LANG_ENG, "0>1>2>3. Adapt to lower VDD voltages"))
			),
			(WCK_DCC,        11,10, ATUI_DEC,
				((LANG_ENG, "Duty Cycle Corr. 0=off,1=start,2=RFU,3=hold"))
			),
			(ID,             15,12, ATUI_DEC,
				((LANG_ENG, "MR 7"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, gddr6_mr8, atui_nullstruct,
	(bios->gddr6_mr8, gddr6_mr8,
		(ATUI_BIN, ATUI_BITFIELD, (
			(CA_low_term,  1,0, ATUI_DEC,
				((LANG_ENG, "0=disable, 1=60ohm, 2=120, 3=rsvd. For CA[3:0]"))
			),
			(CA_high_term, 3,2, ATUI_DEC,
				((LANG_ENG, "For CA[10:4]"))
			),
			(CA_TO,        4,4, ATUI_DEC,
				((LANG_ENG, "Command Address Termin. Override 1=use CAL,CAH"))
			),
			(EDC_hiZ,      5,5, ATUI_DEC,
				((LANG_ENG, "1=Hi-Z state. Precidence over all other states."))
			),
			(CK_auto_cal,  6,6, ATUI_DEC,
				((LANG_ENG, "0=auto calib. during REFab disabled, 1=enabled"))
			),
			(REFpb,        7,7, ATUI_DEC,
				((LANG_ENG, "0=per-bank, 1=per-2-bank"))
			),
			(RL_EHF,       8,8, ATUI_DEC,
				((LANG_ENG, "Extends RLmrs of MR0 from 4 to 5 bits."))
			),
			(WR_EHF,       9,9, ATUI_DEC,
				((LANG_ENG, "Extends WRmrs of MR0 from 4 to 5 bits."))
			),
			(CK_term,     11,10, ATUI_DEC,
				((LANG_ENG, "0=reset, 1=60ohm,2=120-ohm, 3=disabled"))
			),
			(ID,          15,12, ATUI_DEC,
				((LANG_ENG, "MR 8"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, gddr6_mr9, atui_nullstruct,
	(bios->gddr6_mr9, gddr6_mr9,
		(ATUI_BIN, ATUI_BITFIELD, (
			(DFE,          3,0, ATUI_DEC,
				((LANG_ENG, "0=off, in steps of +-0.5% VDDQ or 7mV"))
			),
			(RFU,          6,4, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			(pin_subaddr, 11,7, ATUI_DEC,
				((LANG_ENG, "see JESD250"))
			),
			(ID,          15,12, ATUI_DEC,
				((LANG_ENG, "MR 9"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, gddr6_mr10, atui_nullstruct,
	(bios->gddr6_mr10, gddr6_mr10,
		(ATUI_BIN, ATUI_BITFIELD, (
			(VREFC_offset,  3,0, ATUI_DEC,
				((LANG_ENG, "CA bus. Two's Complement? 0b1000=0 is a typo?"))
			),
			(WCK_inv_byte0, 5,4, ATUI_DEC,
				((LANG_ENG, "for WCK2CK training 0=0;1=90 degr;2=180;3=270"))
			),
			(WCK_inv_byte1, 7,6, ATUI_DEC,
				((LANG_ENG, "B1 on chan A, B0 on chan B ignored if WCK/word"))
			),
			(WCK2CK,        8,8, ATUI_DEC,
				((LANG_ENG, "1=enable WCK2CK alignment training"))
			),
			(WCK_ratio,     9,9, ATUI_DEC,
				((LANG_ENG, "0=half data rate, 1=full data rate"))
			),
			(WCK_term,     11,10, ATUI_DEC,
				((LANG_ENG, "0=disabled, 1=60 ohm, 2=120, 3=reserved"))
			),
			(ID,           15,12, ATUI_DEC,
				((LANG_ENG, "MR 10"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, gddr6_mr11, atui_nullstruct,
	(bios->gddr6_mr11, gddr6_mr11,
		(ATUI_BIN, ATUI_BITFIELD, (
			(PASR_2bank_mask,  7,0, ATUI_DEC,
				((LANG_ENG, "1=banks0,1; 2=2,3; 4=4,5; 8=6,7 .. 128=14,15"))
			),
			(PASR_rowseg_mask,11,8, ATUI_DEC,
				((LANG_ENG, "two MSB of row addr. 0=00;2=01;4=10;8=11 15=all"))
			),
		(ID,                  15,12, ATUI_DEC,
				((LANG_ENG, "MR 11"))
			)
		)),
		((LANG_ENG, "0=refresh enabled 1=refresh blocked for paticular segment or banks"))
	)
)


PPATUI_FUNCIFY(union, gddr6_mr12, atui_nullstruct,
	(bios->gddr6_mr12, gddr6_mr12,
		(ATUI_BIN, ATUI_BITFIELD, (
			(VDDQ_off,  0,0, ATUI_DEC,
				((LANG_ENG, "0=disabled. For Hibernate Self Refresh"))
			),
			(P2BR_addr, 1,1, ATUI_DEC,
				((LANG_ENG, "0=LSB/BA0 1=MSB/BA3. Select \"Dont Care\" for REFp2b"))
			),
			(PRBS,      2,2, ATUI_DEC,
				((LANG_ENG, "1=Psudorandom bit stream instead of EDC hold"))
			),
			(RL_EHF2,   3,3, ATUI_DEC,
				((LANG_ENG, "Extends RLmrs from 5 bits to 6 bits. See MR0, MR8"))
			),
			(CRCWL_EHF, 4,4, ATUI_DEC,
				((LANG_ENG, "Extends CRCWL from 3 bits to 4 bits. See MR4."))
			),
			(WR_EHF2,   5,5, ATUI_DEC,
				((LANG_ENG, "Extends WRmrs from 5 bits to 6 bits. See MR0, MR8"))
			),
			(RFU,      11,6, ATUI_DEC,
				((LANG_ENG, "reserved."))
			),
			(ID,       15,12, ATUI_DEC,
				((LANG_ENG, "MR 12"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, gddr6_mr13, atui_nullstruct,
	(bios->gddr6_mr13, gddr6_mr13,
		(ATUI_BIN, ATUI_BITFIELD, (
			(vendor_specific, 11,0, ATUI_DEC,
				((LANG_ENG, "vendor specific features."))
			),
			(ID,              15,12, ATUI_DEC,
				((LANG_ENG, "MR 13"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, gddr6_mr14, atui_nullstruct,
	(bios->gddr6_mr14, gddr6_mr14,
		(ATUI_BIN, ATUI_BITFIELD, (
			(vendor_specific, 11,0, ATUI_DEC,
				((LANG_ENG, "vendor specific features."))
			),
			(ID,              15,12, ATUI_DEC,
				((LANG_ENG, "MR 14"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, gddr6_mr15, atui_nullstruct,
	(bios->gddr6_mr15, gddr6_mr15,
		(ATUI_BIN, ATUI_BITFIELD, (
			(MRS_to_chan_A, 0,0, ATUI_DEC,
				((LANG_ENG, "MRS to the two channels for individual config"))
			),
			(MRS_to_chan_B, 1,1, ATUI_DEC,
				((LANG_ENG, "0=unblocked 1=blocked"))
			),
			(CA_training,   3,2, ATUI_DEC,
				((LANG_ENG, "0=off 1=rising of CK, 2=falling, 3=CABI_n,CA10"))
			),
			(unused,        11,4, ATUI_DEC,
				((LANG_ENG, "defined to be absent"))
			),
			(ID,            15,12, ATUI_DEC,
				((LANG_ENG, "MR 15"))
			)
		)), (ATUI_NODESCR)
	)
)
