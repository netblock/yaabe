/*
Manual or otherwise hacked versions of AMD registers

HBM2 and vega10 is manually reverse-engineered so it can be wrong.
(vals from amdmemtweak is wrong)

Open your JESD and your PPR/BKDG. Some timings/fields get removed depending on
the target platform. If there's more than 4 contiguous reserved bits, there's
probably a timing/field for a different platform there.
*/

#ifndef _BITFIELD_OVERRIDES_H_
#define _BITFIELD_OVERRIDES_H_

#pragma pack(push, 1) // bios data must use byte alignment

/******************************************************************************/
// GMC fields overrides
// (memory timings as seen in reg_init based timing structures in vram_info)
/******************************************************************************/
union atom_mc_register_setting_id {
	uint32_t id_access;
	struct { uint32_t
		mem_clock_range :23-0 +1,
		mem_block_id    :31-24 +1;
	};
};



union DRAMTiming1 {
	uint32_t DRAMTiming1;
	struct { uint32_t
		tCL     :5-0 +1,
		rsvd0   :7-6 +1,
		tRAS   :14-8 +1,
		rsvd1  :15-15 +1,
		tRCDRD :21-16 +1,
		rsvd2  :23-22 +1,
		tRCDWR :29-24 +1,
		rsvd3  :31-30 +1;
	};
};

union DRAMTiming2 {
	uint32_t DRAMTiming2;
	struct { uint32_t
		tRC_S  :7-0 +1, // per-bank
		tRC_L :15-8 +1, // all-bank?
		tRP_S :21-16 +1,
		rsvd0 :23-22 +1,
		tRP_L :29-24 +1,
		rsvd1 :31-30 +1;
	};
};

union DRAMTiming3 {
	uint32_t DRAMTiming3;
	struct { uint32_t
		tRRD_S  :4-0 +1,
		rsvd0   :7-5 +1,
		tRRD_L :12-8 +1,
		rsvd1  :23-13 +1, // 3+5+3, middle 5 has tRRDDLR for 3D stacked memory.
		tRTP   :28-24 +1,
		rsvd2  :31-29 +1;
	};
};

union DRAMTiming4 {
	uint32_t DRAMTiming4;
	struct { uint32_t
		tFAW   :6-0 +1,
		rsvd0  :7-7 +1,
		t32AW :16-8 +1,
		rsvd1 :31-17 +1; // 1, tFAWSLR:6, 1, tFAWDLR:6, 1
	};
};

union DRAMTiming5 {
	uint32_t DRAMTiming5;
	struct { uint32_t
		tWL    :5-0 +1,
		rsvd0  :7-6 +1,
		tWTRS :12-8 +1,
		rsvd1 :15-13 +1,
		tWTRL :22-16 +1,
		rsvd2 :31-23 +1;
	};
};

union DRAMTiming6 {
	uint32_t DRAMTiming6;
	struct { uint32_t
		tWR    :6-0 +1,
		rsvd0 :31-7 +1;
	};
};

union DRAMTiming7 {
	uint32_t DRAMTiming7;
	struct { uint32_t
		PPD      :2-0 +1,
		rsvd0    :3-3 +1,
		tCRCRL   :6-4 +1,
		rsvd1    :7-7 +1,
		tRREFD  :13-8 +1,
		rsvd2   :14-14 +1,
		tCRCWL  :19-15 +1,
		tRCPAGE :31-20 +1;
	};
};

// Specifies the minimum number of cycles from the last clock of virtual CAS of
// the first burst operation to the clock in which CAS is asserted for a
// following bust operation.
// A value of 1 means 0 idle clock cycles between two bursts; 2 = 1 idle cycle.
union DRAMTiming8 {
	uint32_t DRAMTiming8;
	struct { uint32_t
		tRDRD_DD   :3-0 +1, // Different DIMM
		rsvd0      :7-4 +1,
		tRDRD_SD  :11-8 +1, // Same DIMM
		rsvd1     :15-12 +1,
		tRDRD_SC  :19-16 +1, // JEDEC tCCD_S
		rsvd2     :23-20 +1,
		tRDRD_SCL :27-24 +1, // tCCD_L
		rsvd3     :29-28 +1,
		tRDRD_BAN :31-30 +1; // Preamble2t ?1:0. Ban traffic:1=tCCD=5;2=tCCD=5,6
	};
};

union DRAMTiming9_HBM2 {
	uint32_t DRAMTiming9;
	struct { uint32_t
		tWRWR_DD   :3-0 +1, // Different DIMM
		rsvd0      :7-4 +1,
		tWRWR_SD  :11-8 +1, // Same DIMM
		rsvd1     :15-12 +1,
		tWRWR_SC  :19-16 +1, // JEDEC tCCD_S
		rsvd2     :23-20 +1,
		tWRWR_SCL :27-24 +1, // tCCD_L
		rsvd3     :29-28 +1,
		tWRWR_BAN :31-30 +1; // Preamble2t ?1:0. Ban traffic:1=tCCD=5;2=tCCD=5,6
	};
};
union DRAMTiming9_DDR4 {
	uint32_t DRAMTiming9;
	struct { uint32_t
		tWRWR_DD     :3-0 +1,
		rsvd0        :7-4 +1,
		tWRWR_SD    :11-8 +1,
		rsvd1       :15-12 +1,
		tWRWR_SC    :19-16 +1,
		tWRWR_SCDLR :23-20 +1,
		tWRWR_SCL   :29-24 +1,
		tWRWR_BAN   :31-30 +1;
	};
};
union DRAMTiming9 { // GDDR6
	uint32_t DRAMTiming9;
	struct { uint32_t
		tWRWR_MW   :4-0 +1, // masked write; GDDR
		rsvd0     :15-5 +1,
		tWRWR_SC  :19-16 +1,
		rsvd1     :23-20 +1,
		tWRWR_SCL :29-24 +1,
		tWRWR_BAN :31-30 +1;
	};
};

// tWRRD and tRDWR also follows the 'last clock of virtual CAS'.
// LD = tCL - tCWL ; tWRRD has x-LD and tRDWR has y+LD.
// LD is about making sure one burst happens after the other.
// And x and y follow the 'last clock of virtual CAS' and are about making sure
// the data bus is stable.
union DRAMTiming10 {
	uint32_t DRAMTiming10;
	struct { uint32_t
		tWRRD       :3-0 +1,
		rsvd0       :7-4 +1,
		tRDWR      :13-8 +1,
		rsvd1      :15-14 +1,
		RDRspDelay :21-16 +1,
		tREFTTAdj  :28-22 +1, // was tREFTT; a typo? tREFTR is a GDDR6 timing
		rsvd2      :31-29 +1;
	};
};
union DRAMTiming10_DDR4 {
	uint32_t DRAMTiming10_DDR4;
	struct { uint32_t
		tWRRD       :3-0 +1,
		rsvd0       :7-4 +1,
		tRDWR      :12-8 +1,
		rsvd1      :15-13 +1,
		tWRRDSCDLR :20-16 +1, // 3DS RAM
		rsvd2      :31-21 +1;
	};
};

union DRAMTiming11_DDR4 {
	uint32_t DRAMTiming11_DDR4;
	struct { uint32_t
		tZQCS          :7-0 +1,
		tZQOPER       :19-8 +1, // DDR4
		tZQCSInterval :29-20 +1, // ZQCSInterval * 2^(ShortInit ?10 :20)
		rsvd0         :30-30 +1,
		ShortInit     :31-31 +1;
	};
};

union DRAMTiming12 {
	uint32_t DRAMTiming12;
	struct { uint32_t
		tREFI :15-0 +1, // tREFI is milliseconds; tREF is microseconds
		rsvd0 :31-16 +1;
	};
};

union DRAMTiming13 {
	uint32_t DRAMTiming13;
	struct { uint32_t
		tMRD   :5-0 +1,
		rsvd0  :7-6 +1,
		tMOD  :13-8 +1,
		rsvd1 :31-14 +1;
	};
};

union DRAMTiming13_DDR4 {
	uint32_t DRAMTiming13_DDR4;
	struct { uint32_t
		tMRD    :5-0 +1,
		rsvd0   :7-6 +1,
		tMOD    :13-8 +1,
		rsvd1   :15-14 +1,
		tMRDPDA :21-16 +1, //Per DRAM Addressability
		rsvd2   :23-22 +1,
		tMODPDA :29-24 +1,
		rsvd3   :31-30 +1;
	};
};

union DRAMTiming14_HBM2 {
	uint32_t DRAMTiming14;
	struct { uint32_t
		tXS   :10-0 +1, // exit self refreh to not requiring a locked DLL
		rsvd0 :31-11 +1;
	};
};
union DRAMTiming14 {
	uint32_t DRAMTiming14;
	struct { uint32_t
		tXS   :10-0 +1, // exit self refreh to not requiring a locked DLL
		rsvd0 :15-11 +1,
		tDLLK :26-16 +1, // exit self refresh to requiring a locked DLL
		rsvd1 :31-27 +1;
	};
};

union DRAMTiming15 { // DDR reliability RAS
	uint32_t DRAMTiming15;
	struct { uint32_t
		AlertCrcDly  :6-0 +1, // expected alert crc error dely, in memclocks
		rsvd0        :7-7 +1,
		AlertParDly :14-8 +1, // Parity error
		PL          :18-15 +1, // Cmd/Addr Parity Latency. See DDR4 MR5
		rsvd1       :22-19 +1,
		RankBusyDly :29-23 +1, // max of CRC/ECC alert delays
		rsvd2       :31-30 +1;
	};
};

union DRAMTiming16 {
	uint32_t DRAMTiming16;
	struct { uint32_t
		tXSMRS :10-0 +1,
		rsvd0  :31-11 +1;
	};
};

union DRAMTiming17_HBM2 {
	uint32_t DRAMTiming17;
	struct { uint32_t
		tPD           :3-0 +1,
		tCKSRE        :9-4 +1,
		tCKSRX        :15-10 +1,
		PwrDownDly    :23-16 +1, // last command to PowerDown
		AggPwrDownDly :29-24 +1, // last DRAM activity to precharge, for PD
		rsvd2         :31-30 +1;
	};
};
union DRAMTiming17 {
	uint32_t DRAMTiming17;
	struct { uint32_t
		tPD           :4-0 +1,
		tCKSRE        :10-5 +1,
		tCKSRX        :16-11 +1,
		PwrDownDly    :24-17 +1, // last command to PowerDown
		AggPwrDownDly :30-25 +1, // last DRAM activity to precharge, for PD
		rsvd0         :31-31 +1;
	};
};

union DRAMTiming18_HBM2 {
	uint32_t DRAMTiming18;
	struct { uint32_t
		tRFCSB :10-0 +1,
		rsvd0  :15-11 +1,
		tSTAG  :23-16 +1, // ref-to-ref different rank
		rsvd1  :31-24 +1;
	};
};

union DRAMTiming20 {
	uint32_t DRAMTiming20;
	struct { uint32_t
		tRFCSB :10-0 +1,
		rsvd0  :15-11 +1,
		tSTAG  :23-16 +1, // ref-to-ref different rank
		rsvd1  :31-24 +1;
	};
};

union DRAMTiming21 {
	uint32_t DRAMTiming21;
	struct { uint32_t
		tXP     :5-0 +1,
		rsvd0  :15-6 +1,
		tCPDED :19-16 +1,
		rsvd1  :23-20 +1,
		tCKE   :28-24 +1,
		rsvd2  :31-29 +1;
	};
};

union DRAMTiming22_HBM2 { // reverse-engineered; might be wrong.
	uint32_t DRAMTiming22;
	struct { uint32_t
		rsvd0_0      :1-0 +1, // makes n=3,3 on vega10
		tRDDATA_EN   :6-2 +1, // tCL-n; GD6 n=1, D4 n=5. READ to dfi_rddata_en
		rsvd0        :7-7 +1,
		tPHY_WRLAT  :12-8 +1, // tCWL-n; GD6 n=2, D4 n=5. WRITE to dfi_wrdata_en
		rsvd1       :15-13 +1,
		tPHY_RDLAT  :21-16 +1, // dfi_rddata_en to dfi_rddata_vld dely
		rsvd2       :23-22 +1,
		tPHY_WRDATA :26-24 +1, // dfi_wrdata_en to dfi_wrdata delay
		rsvd3       :27-27 +1,
		tPARIN_LAT  :29-28 +1, // ctrl signals to parity delay
		rsvd4       :31-30 +1;
	};
};
union DRAMTiming22 { // "DFI" is shorthand for "DDR PHY"
	uint32_t DRAMTiming22;
	struct { uint32_t
		tRDDATA_EN   :6-0 +1, // tCL-n; GD6 n=1, D4 n=5. READ to dfi_rddata_en
		rsvd0        :7-7 +1,
		tPHY_WRLAT  :12-8 +1, // tCWL-n; GD6 n=2, D4 n=5. WRITE to dfi_wrdata_en
		rsvd1       :15-13 +1,
		tPHY_RDLAT  :21-16 +1, // dfi_rddata_en to dfi_rddata_vld dely
		rsvd2       :23-22 +1,
		tPHY_WRDATA :26-24 +1, // dfi_wrdata_en to dfi_wrdata delay
		rsvd3       :27-27 +1,
		tPARIN_LAT  :29-28 +1, // ctrl signals to parity delay
		rsvd4       :31-30 +1;
	};
};

union DRAMTiming23 {
	uint32_t DRAMTiming23;
	struct { uint32_t
		LpDly      :5-0 +1, // hysteresis before placing PHY into low power
		rsvd0      :7-6 +1,
		LpExitDly  :13-8 +1, // min memclk before taking a rank out of powerdown
		rsvd1      :15-14 +1,
		CKESTAGDLY :19-16 +1,
		rsvd3      :31-20 +1;
	};
};

union DRAMTiming23_DDR4 {
	uint32_t DRAMTiming23_DDR4;
	struct { uint32_t
		LpDly      :5-0 +1, // hysteresis before placing PHY into low power
		rsvd0      :7-6 +1,
		LpExitDly  :13-8 +1, // min memclk before taking a rank out of powerdown
		rsvd1      :23-14 +1,
		tGearSetup :26-24 +1,  // GDM I believe
		rsvd4      :27-27 +1,
		tGearHold  :30-28 +1,
		rsvd5      :31-31 +1;
	};
};

union DRAMTiming34 {
	uint32_t DRAMTiming34;
	struct { uint32_t
		tPhyupd_resp :3-0 +1,
		tRDEDC_EN    :10-4 +1,
		rsvd0        :11-11 +1,
		tWREDC_EN    :18-12 +1,
		rsvd1        :31-19 +1;
	};
};

union DRAMTiming35 { // reliability RAS
	uint32_t DRAMTiming35;
	struct { uint32_t
		ReceiverWait :10-0 +1, // Wait time to start recovery sequence
		CmdStageCnt  :21-11 +1,//Recov. seq. cmd stagger counter. See CmdStgFrc
			// CmdStgFrc:1; 1=enable recovery command stagger in recovery phase
		rsvd0        :23-22 +1,
		tWRMPR       :29-24 +1,
		rsvd1        :31-30 +1;
	};
};

union DRAMTiming36 { // GDDR training
	uint32_t DRAMTiming36;
	struct { uint32_t
		tWTRTR     :5-0 +1, // WRITE to WRTR
		tREFTR     :11-6 +1, // was named tREFTT. REFab to RDTR/WRTR
		tTTROW     :17-12 +1, // ??
		tLDTLD     :23-18 +1, // JEDEC tLTLTR?
		tUPDN      :29-24 +1, // ??
		tREFTR_MSB :30-30 +1, // was named tREFTT
		rsvd0      :31-31 +1;
	};
};

union TRFCTimingCS01 {
	uint32_t TRFCTimingCS01;
	struct { uint32_t
		tRFC  :10-0 +1,
		rsvd0 :31-11 +1;
	};
};

union TRFCTimingCS01_DDR4 {
	uint32_t TRFCTimingCS01_DDR4;
	struct { uint32_t
		tRFC  :10-0 +1,
		tRFC2 :21-11 +1,
		tRFC4 :31-22 +1;
	};
};

union ChanPipeDly {
	uint32_t ChanPipeDly;
	struct { uint32_t
		TXCtrlChanDly :2-0 +1,//# of delay stages on DFI control from UMC to PHY
		rsvd0         :3-3 +1,
		TXDataChanDly :6-4 +1, // ... on DFI write data from UMC to PHY
		rsvd1         :7-7 +1,
		RXDataChanDly:10-8 +1, // ... on DFI read data from PHY to UMC
		rsvd2        :31-11 +1;
	};
};

struct UMCCTRL_MISC2 {
	union gddr6_mr5 gddr6_mr5;
	uint16_t reserved;
};
struct UMCCTRL_PMG_CMD_MRS {
	union gddr6_mr0 gddr6_mr0;
	uint16_t reserved;
};
struct UMCCTRL_PMG_CMD_MRS1 {
	union gddr6_mr4 gddr6_mr4;
	uint16_t reserved;
};
struct PMG_CMD {
	union gddr6_mr8 gddr6_mr8;
	uint16_t reserved;
};


union mc_seq_misc_timing_6_0_o { // override of mc_seq_misc_timing_6_0 -> 9.0?
	uint32_t mc_seq_misc_timing;
	struct { uint32_t
		trp_wra  :6-0 +1, // autoprecharge?
		trp_rda :13-7 +1, // autoprecharge?
		trp     :19-14 +1,
		trfc    :28-20 +1,
		rsvd2   :31-29 +1;
	};
};
union mc_seq_misc_timing2_6_0_o { // override of mc_seq_misc_timing2_6_0 -> 9.0?
	uint32_t raw_data;
	struct { uint32_t
		pa2rdata  :3-0 +1,
		pa2wdata  :7-4 +1,
		faw      :12-8 +1,
		tredc    :15-13 +1,
		twedc    :20-16 +1,
		t32aw    :24-21 +1,
		_rsvd02  :27-25 +1,
		twdatatr :31-28 +1;
	};
};
union mc_seq_cmd_6_0_o { // override of mc_seq_cmd_6_0 -> 9.0?
	uint32_t raw_data;
	struct { uint32_t
		adr      :15-0 +1,
		mop      :19-16 +1,
		end      :20-20 +1,
		csb      :22-21 +1,
		_rsvd00  :23-23 +1,
		chan0    :24-24 +1,
		chan1    :25-25 +1,
		chan2    :26-26 +1,
		chan3    :27-27 +1,
		adr_msb1 :28-28 +1,
		adr_msb0 :29-29 +1,
		_rsvd02  :31-30 +1;
	};
};
union mc_seq_cas_timing_6_0_o { // override of mc_seq_cas_timing_6_0 -> 9.0?
	uint32_t raw_data;
	struct { uint32_t
		tnopw    :4-0 +1,
		tnopr    :9-5 +1,
		tr2w    :14-10 +1,
		tr2r    :18-15 +1,
		tw2r    :23-19 +1,
		tcl     :28-24 +1,
		_rsvd01 :31-29 +1;
	};
};
union mc_seq_byte_remap_d0_6_0_o {
	uint8_t raw_data;
	struct { uint8_t
		byte0    :1-0 +1,
		byte1    :3-2 +1,
		byte2    :5-4 +1,
		byte3    :7-6 +1;
	};
};

union mc_arb_ramcfg_7_0_o {
	uint16_t raw_data;
	struct { uint16_t
		noofbank           :1-0 +1,
		noofranks          :2-2 +1,
		noofrows           :5-3 +1,
		noofcols           :7-6 +1,
		chansize           :8-8 +1,
		burstlength        :9-9 +1,
		rsv_2             :10-10 +1,
		chansize_override :11-11 +1,
		noofgroups        :12-12 +1,
		rsv_4             :15-13 +1;
	};
};
union mc_io_aphy_str_cntl_d0_6_0_o {
	uint32_t raw_data;
	struct { uint32_t
		pstr_off_a     :5-0 +1,
		nstr_off_a    :11-6 +1,
		pstr_off_d_rd :17-12 +1,
		nstr_off_d_rd :23-18 +1,
		use_a_cal     :24-24 +1,
		use_d_rd_cal  :25-25 +1,
		cal_sel       :27-26 +1,
		load_a_str    :28-28 +1,
		load_d_rd_str :29-29 +1,
		_rsvd01       :31-30 +1;
	};
};
union mc_seq_rxframing_dbi_d1_6_0_o {
	uint32_t raw_data;
	struct { uint32_t
		dbi0     :3-0 +1,
		dbi1     :7-4 +1,
		dbi2    :11-8 +1,
		dbi3    :15-12 +1,
		dbi4    :19-16 +1,
		dbi5    :23-20 +1,
		dbi6    :27-24 +1,
		dbi7    :31-28 +1;
	};
};

union mc_seq_misc0 {
	uint32_t mc_seq_misc0;
	struct { uint32_t
		refresh_factor :1-0 +1, // 1<<(n+3) = tREF millisec?
		unknown0       :7-2 +1,
		vendor        :11-8 +1,
		revision      :15-12 +1,
		unknown1      :23-16 +1,
		memory_type   :31-24 +1;
	};
};
struct mc_seq_misc1_gddr5 { // see MC_SEQ_MISC1_6_0
	union gddr5_mr0 gddr5_mr0;
	union gddr5_mr1 gddr5_mr1;
};
struct mc_seq_misc3_gddr5 { // see MC_SEQ_MISC3_6_0
	union gddr5_mr4 gddr5_mr4;
	union gddr5_mr5 gddr5_mr5;
};
struct mc_seq_misc4_gddr5 { // polaris? might be wrong
	union gddr5_mr4 gddr5_mr6;
	union gddr5_mr7 gddr5_mr7;
};
struct mc_seq_misc8_gddr5 { // see MC_SEQ_MISC8_6_0
	union gddr5_mr8 gddr5_mr8;
	union gddr5_mr7 gddr5_mr7; // guess, might be wrong
};
struct mc_seq_misc1_ddr3 {
	union ddr3_mr0  mr0;
	union ddr3_mr1  mr1;
};
struct mc_seq_misc3_ddr3 {
	union ddr3_mr2  mr2;
	union ddr3_mr3  mr3;
};

#pragma pack(pop) // restore old packing

#endif
