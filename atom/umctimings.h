/*
C bitfield structs; don't forget we're little-endian.

Open your JESD and your PPR/BKDG
Some timings get removed depending on the target platform. If there's more than
4 contiguous reserved bits, there's probably a timing for a different platform
there.
*/

#ifndef _UMCTIMINGS_H_
#define _UMCTIMINGS_H_

#include "ddrmoderegisters.h"

#pragma pack(push, 1) // bios data must use byte alignment

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
		rsvd1 :31-17 +1; //1, tFAWSLR:6, 1, tFAWDLR:6, 1
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

union DRAMTiming9 {
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


union DRAMTiming9_DDR4 {
	uint32_t DRAMTiming9_DDR4;
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

union DRAMTiming22 { // "DFI" is shorthand for "DDR PHY"
	uint32_t DRAMTiming22;
	struct { uint32_t
		tRDDATA_EN   :6-0 +1, // tCL-n; GD6 n=1, D4 n=5. READ to dfi_rddata_en
		rsvd0        :7-7 +1,
		tPHY_WRLAT  :13-8 +1, // tCWL-n; GD6 n=2, D4 n=5. WRITE to dfi_wrdata_en
		rsvd1       :16-14 +1,
		tPHY_RDLAT  :22-17 +1, // dfi_rddata_en to dfi_rddata_vld dely
		rsvd2       :24-23 +1,
		tPHY_WRDATA :27-25 +1, // dfi_wrdata_en to dfi_wrdata delay
		tPARIN_LAT  :29-28 +1, // ctrl signals to parity delay
		rsvd3       :31-30 +1;
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


struct umc_block_navi1_timings {
	union atom_umc_reg_setting_id_config_access  block_id; //frequency

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

#pragma pack(pop) // restore old packing
#endif
