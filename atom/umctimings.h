/*
Manual or otherwise hacked versions of AMD registers

Open your JESD and your PPR/BKDG
Some timings get removed depending on the target platform. If there's more than
4 contiguous reserved bits, there's probably a timing for a different platform
there.

HBM2 and vega10 is manually reverse-engineered so it can be wrong.
(vals from amdmemtweak is wrong)
*/

#ifndef _UMCTIMINGS_H_
#define _UMCTIMINGS_H_

#pragma pack(push, 1) // bios data must use byte alignment

/******************************************************************************/
// memory timings as seen in 'mem_clk_patch' based timing structures
// will duplicate gmc timing structures
/******************************************************************************/


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
		tREFI :15-0 +1, //tREF; the microseconds not milliseconds one
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


/* From ElioVP's amdmemtweak. vals don't look right.

union SEQ_WR_CTL_D0_HBM1 {
	uint32_t SEQ_WR_CTL_D0;
	struct { uint32_t
		DAT_DLY  :4-0 +1, // Data output latency
		DQS_DLY  :9-5 +1, // DQS Latency
		DQS_XTR :10-10 +1, // Write Preamble (ON/OFF)
		OEN_DLY :15-11 +1, // Write cmd enable Latency
		OEN_EXT :19-16 +1, // Output enable -> Data Burst (0 - 8 where 1 = 1 cycle, 5 = 5 cycles..)
		OEN_SEL :21-20 +1,
		CMD_DLY :22-22 +1,
		ADR_DLY :23-23 +1,
		rsvd0   :31-24 +1;
	};
};
union SEQ_WR_CTL_D0_GDDR5 {
	uint32_t SEQ_WR_CTL_D0;
	struct { uint32_t
		DAT_DLY     :3-0 +1, // Data output latency
		DQS_DLY     :7-4 +1, // DQS Latency
		DQS_XTR     :8-8 +1, // Write Preamble (ON/OFF)
		DAT_2Y_DLY  :9-9 +1, // Delay data (QDR Mode!) (ON/OFF)
		ADR_2Y_DLY :10-10 +1, // Delay addr (QDR Mode!) (ON/OFF)
		CMD_2Y_DLY :11-11 +1, // Delay cmd (QDR Mode!) (ON/OFF)
		OEN_DLY    :15-12 +1, // Write cmd enable Latency
		OEN_EXT    :19-16 +1, // Output enable -> Data Burst (0 - 8 where 1 = 1 cycle, 5 = 5 cycles..)
		OEN_SEL    :21-20 +1, 
		rsvd0      :23-22 +1, 
		ODT_DLY    :27-24 +1, // On-Die-Termination latency
		ODT_EXT    :28-28 +1, // On-Die-Termination enable after burst
		ADR_DLY    :29-29 +1,
		CMD_DLY    :30-30 +1,
		rsvd1      :31-31 +1;
	};
};
union SEQ_PMG_TIMING {
	uint32_t SEQ_PMG_TIMING;
	struct { uint32_t
		CKSRE        :2-0 +1, // Valid clock requirement after CKSRE
		CKSRX        :5-3 +1, // Valid clock requirement before CKSRX
		CKE_PULSE   :10-6 +1, // Minimum CKE pulse
		CKE         :18-11 +1, 
		SEQ_IDLE    :21-19 +1, // idle before deassert rdy to arb
		SEQ_IDLE_SS :29-22 +1, // idle before deassert rdy to arb at ss
		rsvd0       :31-30 +1;
	};
};
struct mc_block_fiji_timings { // 40 bytes.
	union atom_mc_register_setting_id block_id;
	uint32_t t0; //union SEQ_WR_CTL_D0_HBM1 SEQ_WR_CTL_D0;
	uint32_t t1; //union SEQ_WR_CTL_D0_HBM1 SEQ_WR_CTL_D1;
	uint32_t t2; //union SEQ_PMG_TIMING SEQ_PMG_TIMING;
	uint32_t t3;
	uint32_t t4;
	uint32_t t5;
	uint32_t t6;
	uint32_t t7;
	uint32_t t8;
};
*/
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

/******************************************************************************/
// mem_clk_patch
/******************************************************************************/

struct mc_block_islands_ddr3_timings { // 52 bytes
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

struct mc_block_islands_gddr5_timings { // 52 bytes
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

struct mc_block_fiji_timings { // 40 bytes
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

struct mc_block_polaris_timings { // 52 bytes.
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

struct umc_block_vega10_timings { // 92 bytes. Uncertain.
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

struct umc_block_vega21_timings { // 96 bytes. Uncertain.
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

struct umc_block_navi1_timings { // 116 bytes. A little more certain.
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
// mem_adjust_table
// uncertain the accuracy of all of these tables.
/******************************************************************************/
/*
struct mem_adjust__gddr5 { //  bytes
	union atom_mc_register_setting_id  block_id;
};
*/

struct mem_adjust_terascale2_ddr3 { // 108 bytes
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

struct mem_adjust_terascale2_gddr5_type3 { // 172 bytes
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

struct mem_adjust_terascale2_gddr5_type4 { // 196 bytes
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
struct mem_adjust_terascale3_gddr5 { // 196 bytes
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


struct mem_adjust_gcn1_gddr5_type1 { // 232 bytes
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

struct mem_adjust_gcn1_gddr5_type2 { // 284 bytes
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

struct mem_adjust_gcn1_gddr5_type3 { // 304 bytes
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

struct mem_adjust_gcn1_gddr5_type4 { // 128 bytes
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

struct mem_adjust_gcn2_gddr5 { // 288 bytes
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

struct mem_adjust_gcn3_gddr5 { // 96 bytes
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

struct mem_adjust_gcn3_hbm1 { // 8 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_rxframing_dbi_d1_6_0_o  mc_seq_rxframing_dbi_d1;
};

struct mem_adjust_gcn4_gddr5_type1 { // 24 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_seq_misc4_6_0  mc_seq_misc4;
	union mc_seq_misc5_6_0  mc_seq_misc5;
	union mc_io_pad_cntl_d1_6_0  mc_io_pad_cntl_d1;
	union mc_tsm_debug_flag_6_0  mc_tsm_debug_flag;
	union mc_io_aphy_str_cntl_d0_6_0_o mc_io_aphy_str_cntl_d0;
};

struct mem_adjust_gcn4_gddr5_type2 { // 44 bytes
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
// mc_adjust_pertile table
// uncertain the accuracy of all of these tables.
/******************************************************************************/

struct mc_adjust_gcn3_gddr5 { // 12 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_tsm_debug_flag_6_0  mc_tsm_debug_flag;
	union mc_tsm_debug_bcnt6_6_0 mc_tsm_debug_bcnt6;
};

struct mc_adjust_gcn4_gddr5 { // 8 bytes
	union atom_mc_register_setting_id  block_id;
	union mc_io_debug_up_14_6_0  mc_io_debug_up_14;
};

/******************************************************************************/
// mc_phy_init table
// uncertain the accuracy of all of these tables.
/******************************************************************************/

struct mc_phy_init_gcn3_hbm1 { // 56 bytes
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

struct mc_phy_init_gcn3_gddr5 { // 384 bytes
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

struct mc_phy_init_gcn4_gddr5_type1 { // 92 bytes
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

struct mc_phy_init_gcn4_gddr5_type2 { // 72 bytes
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

#pragma pack(pop) // restore old packing

#endif
