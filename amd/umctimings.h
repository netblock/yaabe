// C bitfield structs; don't forget we're little-endian.
//
// Open your JESD and your PPR/BKDG
// Muxed AMD DRAMTiming. Some timings get removed depending on the target
// platform. If there's more than 4 contiguous reserved bits, there's probably
// a timing for a different platform there.


struct DRAMTiming1 {
	uint32_t tCL    : 6;
	uint32_t rsvd0  : 2;
	uint32_t tRAS   : 7;
	uint32_t rsvd1  : 1;
	uint32_t tRCDRD : 6;
	uint32_t rsvd2  : 2;
	uint32_t tRCDWR : 6;
	uint32_t rsvd3  : 2;
};

struct DRAMTiming2 {
	uint32_t tRC_S : 8; // per-bank
	uint32_t tRC_L : 8; // all-bank?
	uint32_t tRP_S : 6;
	uint32_t rsvd0 : 2;
	uint32_t tRP_L : 6;
	uint32_t rsvd1 : 2;
};

struct DRAMTiming3 {
	uint32_t tRRDS   : 5;
	uint32_t rsvd0   : 3;
	uint32_t tRRDL   : 5;
	uint32_t rsvd1   : 3;
	uint32_t tRRDDLR : 5; // 3D die stacked memory
	uint32_t rsvd2   : 3;
	uint32_t tRTP    : 5;
	uint32_t rsvd3   : 3;
};

struct DRAMTiming4 {
	uint32_t tFAW    : 7;
	uint32_t rsvd0   : 1;
	uint32_t t32AW   : 9;
	uint32_t rsvd1   : 1;
	uint32_t tFAWSLR : 6;
	uint32_t rsvd2   : 1;
	uint32_t tFAWDLR : 6;
	uint32_t rsvd3   : 1;
};

struct DRAMTiming5 {
	uint32_t tWL   : 6;
	uint32_t rsvd0 : 2;
	uint32_t tWTRS : 5;
	uint32_t rsvd1 : 3;
	uint32_t tWTRL : 7;
	uint32_t rsvd2 : 7;
};

struct DRAMTiming6 {
	uint32_t tWR   : 7;
	uint32_t rsvd0 :25; //what are you hiding...
};

struct DRAMTiming7 { // mostly GDDR 
	uint32_t tPPD    : 3;
	uint32_t rsvd0   : 1;
	uint32_t tCRCRL  : 3;
	uint32_t rsvd1   : 1;
	uint32_t tRREFD  : 6;
	uint32_t rsvd2   : 1;
	uint32_t tCRCWL  : 5;
	uint32_t tRCPAGE :12;
};

// Specifies the minimum number of cycles from the last clock of virtual CAS of
// the first burst operation to the clock in which CAS is asserted for a
// following bust operation.
// A value of 1 means 0 idle clock cycles between two bursts; 2 = 1 idle cycle.
struct DRAMTiming8 {
	uint32_t tRDRD_DD  : 4; // Different DIMM
	uint32_t rsvd0     : 4;
	uint32_t tRDRD_SD  : 4; // Same DIMM
	uint32_t rsvd1     : 4;
	uint32_t tRDRD_SC  : 4; // JEDEC tCCD_S
	uint32_t rsvd2     : 4;
	uint32_t tRDRD_SCL : 4; // tCCD_L
	uint32_t rsvd3     : 2;
	uint32_t tRDRD_BAN : 2; // Preamble2t ?1:0. 1h=tCCD+1; 2h=tCCD+1,2
};

struct DRAMTiming9 {
	uint32_t tWRWR_MW  : 5; // masked write; GDDR
	uint32_t rsvd0     :11;
	uint32_t tWRWR_SC  : 4;
	uint32_t rsvd1     : 4;
	uint32_t tWRWR_SCL : 6;
	uint32_t tWRWR_BAN : 2;
};
struct DRAMTiming9_DDR4 {
	uint32_t tWRWR_DD    : 4;
	uint32_t rsvd0       : 4;
	uint32_t tWRWR_SD    : 4;
	uint32_t rsvd1       : 4;
	uint32_t tWRWR_SC    : 4;
	uint32_t tWRWR_SCDLR : 4;
	uint32_t tWRWR_SCL   : 6;
	uint32_t tWRWR_BAN   : 2;
};

// tWRRD and tRDWR also follows the 'last clock of virtual CAS'.
// LD = tCL - tCWL ; tWRRD has x-LD and tRDWR has y+LD.
// LD is about making sure one burst happens after the other. 
// And x and y follow the 'last clock of virtual CAS' and are about making sure
// the data bus is stable.
struct DRAMTiming10 {
	uint32_t tWRRD      : 4;
	uint32_t rsvd0      : 4;
	uint32_t tRDWR      : 6;
	uint32_t rsvd1      : 2;
	uint32_t RDRspDelay : 6;
	uint32_t tReftrAdj  : 7; // tREFTT a typo? tREFTR is a GDDR6 timing
	uint32_t rsvd2      : 3;
}; 
struct DRAMTiming10_DDR4 {
	uint32_t tWRRD      : 4;
	uint32_t rsvd0      : 4;
	uint32_t tRDWR      : 5;
	uint32_t rsvd1      : 3;
	uint32_t tWRRDSCDLR : 5; //3DS RAM
	uint32_t rsvd2      :11;
};

struct DRAMTiming11 {
	uint32_t tZQCS         : 8;
	uint32_t tZQOPER       :28; // DDR4
	uint32_t tZQCSInterval :10; // ZQCSInterval * 2^(ShortInit ?10 :20)
	uint32_t rsvd0         : 1;
	uint32_t ShortInit     : 1;
};

struct DRAMTiming12 {
	uint32_t tREFI :16; //tREF; the microseconds not milliseconds one
	uint32_t rsvd0 :16;
};

struct DRAMTiming13 {
	uint32_t tMRD    : 6;
	uint32_t rsvd0   : 2;
	uint32_t tMOD    : 6;
	uint32_t tMRDPDA : 6; //Per DRAM Addressability; PDA is for a single, specific DRAM on a rank.
	uint32_t rsvd1   : 2;
	uint32_t tMODPDA : 6;
	uint32_t rsvd2   : 2;
};

struct DRAMTiming14 {
	uint32_t tXS   :11; // exit self refreh to not requiring a locked DLL
	uint32_t rsvd0 : 5;
	uint32_t tDLLK :11; // exit self refresh to requiring a locked DLL
};

struct DRAMTiming15 { // DDR reliability RAS
	uint32_t AlertCrcDly : 7; // expected alert crc error dely; memclocks
	uint32_t rsvd0       : 1;
	uint32_t AlertParDly : 7; // Parity error
	uint32_t PL          : 4; // Cmd/Addr Parity Latency; see DDR4 MR5
	uint32_t rsvd1       : 4; 
	uint32_t RankBusyDly : 7; // max of AlertCrcDly, AlertWcrcDly, or ECC return delay
	uint32_t rsvd2       : 1;
};

struct DRAMTiming16 {
	uint32_t tXSMRS :11;
	uint32_t rsvd0  :21;
};

struct DRAMTiming17 {
	uint32_t tPD           : 5;
	uint32_t tCKSRE        : 6;
	uint32_t tCKSRX        : 6;
	uint32_t PwrDownDly    : 8; // last command to PowerDown; max of tPRPDEN, tRDAPDEN, tWRAPDEN, tREFPDEN, tMRSPDEN
	uint32_t AggPwrDownDly : 6; // last DRAM activity to precharge, for precharge powerdown. Orthogonal to IdleCycleLimit
	uint32_t rsvd0         : 1;
};

struct DRAMTiming20 {
	uint32_t tRFCSB :11;
	uint32_t rsvd0  : 5;
	uint32_t tSTAG  : 8; // ref-to-ref different rank
	uint32_t rsvd1  : 8;
}; 

struct DRAMTiming21 {
	uint32_t tXP    : 6;
	uint32_t rsvd0  :10;
	uint32_t tCPDED : 4;
	uint32_t rsvd1  : 4;
	uint32_t tCKE   : 5;
	uint32_t rsvd2  : 3;
};

struct DRAMTiming22 { // "DFI" is shorthand for "DDR PHY"
	uint32_t tRDDATA_EN  : 7; // tCL-n; GDDR6 n=1; DDR4 n=5. read command to dfi_rddata_en delay
	uint32_t rsvd0       : 1;
	uint32_t tPHY_WRLAT  : 5; // tCWL-n; GDDR6 n=2; DDR4 n=5. write to dfi_wrdata_en delay
	uint32_t rsvd1       : 3;
	uint32_t tPHY_RDLAT  : 6; // dfi_rddata_en to dfi_rddata_vld dely
	uint32_t rsvd2       : 2;
	uint32_t tPHY_WRDATA : 3; // dfi_wrdata_en to dfi_wrdata delay
	uint32_t tPARIN_LAT  : 2; // ctrl signals to parity delay
	uint32_t rsvd3       : 2;
};

struct DRAMTiming23 {
	uint32_t LpDly      : 6; // hysteresis before placing PHY into low power
	uint32_t rsvd0      : 2; 
	uint32_t LpExitDly  : 6; // min memclk before taking a rank out of powerdown
	uint32_t rsvd1      : 2;
	uint32_t CKESTAGDLY : 4;
	uint32_t rsvd3      : 4; 
	uint32_t tGearSetup : 3;  // GDM I believe
	uint32_t rsvd4      : 1; 
	uint32_t tGearHold  : 3; 
	uint32_t rsvd5      : 1; 
};

struct DRAMTiming34 {
	uint32_t tPhyupd_resp : 4;
	uint32_t tRDEDC_EN    : 7;
	uint32_t rsvd0        : 1;
	uint32_t tWREDC_EN    : 7;
	uint32_t rsvd1        :13;
};

struct DRAMTiming35 { // reliability RAS
	uint32_t ReceiverWait :11; // Wait time to start recovery sequence
	uint32_t CmdStageCnt  :11; // Recovery sequence command stagger counter. See CmdStgFrc.  CmdStgFrc:1; 1=enable recovery command stagger in recovery phase
	uint32_t rsvd0        : 2;
	uint32_t tWRMPR       : 6;
	uint32_t rsvd1        : 2;
};

struct DRAMTiming36 { // GDDR training
	uint32_t tWTRTR     : 6; // WRITE to WRTR
	uint32_t tREFTR     : 6; // was named tREFTT; REFab to RDTR/WRTR
	uint32_t tTTROW     : 6; // ??
	uint32_t tLDTLD     : 6; // JEDEC tLTLTR?
	uint32_t tUPDN      : 6; // ??
	uint32_t tREFTR_MSB : 1; // was named tREFTT
	uint32_t rsvd0      : 1;
};

struct TRFCTimingCS01 {
	uint32_t tRFC  : 11;
	uint32_t tRFC2 : 11;
	uint32_t tRFC4 : 10;
};

struct ChanPipeDly {
	uint32_t TXCtrlChanDly : 3; // Number of delay stages on DFI control signals from UMC to PHY
	uint32_t rsvd0         : 1;
	uint32_t TXDataChanDly : 3; // Number of delay stages on DFI write data from UMC to PHY
	uint32_t rsvd1         : 1;
	uint32_t RXDataChanDly : 3; // Number of delay stages on DFI read data from PHY to UMC
	uint32_t rsvd2         :21;
};






//TODO

struct UMCCTRL_MISC2 {
	GDDR6_MODE_REG_5 MR5;
	uint16_t rsvd0;
};

struct UMCCTRL_PMG_CMD_MRS {
	GDDR6_MODE_REG_0 MR0;
	uint16_t rsvd0;
};

struct UMCCTRL_PMG_CMD_MRS1 {
	GDDR6_MODE_REG_4 MR4;
	uint16_t rsvd0;
};

struct PMG_CMD {
	GDDR6_MODE_REG_8 MR8;
	uint16_t rsvd0;
};

struct navi1_timings {
	uint32_t UMCCTRL_MISC2;
	uint32_t UMCCTRL_PMG_CMD_MRS;
	uint32_t UMCCTRL_PMG_CMD_EMRS;
	uint32_t UMCCTRL_PMG_CMD_MRS1;
	uint32_t PMG_CMD;
	struct DramTiming1;
	struct DramTiming2;
	struct DramTiming3;
	struct DramTiming4;
	struct DramTiming5;
	struct DramTiming6;
	struct DramTiming7;
	struct DramTiming8;
	struct DramTiming9;
	struct DramTiming10;
	struct DramTiming12;
	struct DramTiming13;
	struct DramTiming14;
	struct DramTiming16;
	struct DramTiming17;
	struct DramTiming20;
	struct DramTiming21;
	struct DramTiming22;
	struct DramTiming23;
	struct DramTiming35;
	struct DramTiming36;
	TRFCTimingCS01 TRFC;
	uint32_t ChanPipeDly;
};
