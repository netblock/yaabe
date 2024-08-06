#ifndef _PPTABLE_H
#define _PPTABLE_H

#pragma pack(1)

struct atom_pplib_thermalcontroller {
	uint8_t  Type;          // one of ATOM_PP_THERMALCONTROLLER_*
	uint8_t  I2cLine;       // as interpreted by DAL I2C
	uint8_t  I2cAddress;
	uint8_t  FanParameters; // Fan Control Parameters.
	uint8_t  FanMinRPM;     // Fan Minimum RPM (hundreds) -- for display purposes only.
	uint8_t  FanMaxRPM;     // Fan Maximum RPM (hundreds) -- for display purposes only.
	uint8_t  Reserved;
	uint8_t  Flags;         // to be defined
};

#define ATOM_PP_FANPARAMETERS_TACHOMETER_PULSES_PER_REVOLUTION_MASK 0x0f
#define ATOM_PP_FANPARAMETERS_NOFAN                                 0x80    // No fan is connected to this controller.

#define ATOM_PP_THERMALCONTROLLER_NONE      0
#define ATOM_PP_THERMALCONTROLLER_LM63      1  // Not used by PPLib
#define ATOM_PP_THERMALCONTROLLER_ADM1032   2  // Not used by PPLib
#define ATOM_PP_THERMALCONTROLLER_ADM1030   3  // Not used by PPLib
#define ATOM_PP_THERMALCONTROLLER_MUA6649   4  // Not used by PPLib
#define ATOM_PP_THERMALCONTROLLER_LM64      5
#define ATOM_PP_THERMALCONTROLLER_F75375    6  // Not used by PPLib
#define ATOM_PP_THERMALCONTROLLER_RV6xx     7
#define ATOM_PP_THERMALCONTROLLER_RV770     8
#define ATOM_PP_THERMALCONTROLLER_ADT7473   9
#define ATOM_PP_THERMALCONTROLLER_KONG      10
#define ATOM_PP_THERMALCONTROLLER_EXTERNAL_GPIO 11
#define ATOM_PP_THERMALCONTROLLER_EVERGREEN 12
#define ATOM_PP_THERMALCONTROLLER_EMC2103   13 // Only fan control will be implemented, do NOT show this in PPGen.
#define ATOM_PP_THERMALCONTROLLER_SUMO      14 // Sumo type, used internally
#define ATOM_PP_THERMALCONTROLLER_NISLANDS  15
#define ATOM_PP_THERMALCONTROLLER_SISLANDS  16
#define ATOM_PP_THERMALCONTROLLER_LM96163   17
#define ATOM_PP_THERMALCONTROLLER_CISLANDS  18
#define ATOM_PP_THERMALCONTROLLER_KAVERI    19
#define ATOM_PP_THERMALCONTROLLER_ICELAND   20
#define ATOM_PP_THERMALCONTROLLER_TONGA     21
#define ATOM_PP_THERMALCONTROLLER_FIJI      22
#define ATOM_PP_THERMALCONTROLLER_POLARIS10 23
#define ATOM_PP_THERMALCONTROLLER_VEGA10    24


// Thermal controller 'combo type' to use an external controller for Fan control and an internal controller for thermal.
// We probably should reserve the bit 0x80 for this use.
// To keep the number of these types low we should also use the same code for all ASICs (i.e. do not distinguish RV6xx and RV7xx Internal here).
// The driver can pick the correct internal controller based on the ASIC.
#define ATOM_PP_THERMALCONTROLLER_ADT7473_WITH_INTERNAL 0x89 // ADT7473 Fan Control + Internal Thermal Controller
#define ATOM_PP_THERMALCONTROLLER_EMC2103_WITH_INTERNAL 0x8D // EMC2103 Fan Control + Internal Thermal Controller

struct atom_pplib_state {
	uint8_t  NonClockStateIndex;
	uint8_t  ClockStateIndices[]; // variable-sized
};


struct atom_pplib_fantable {
	uint8_t  FanTableFormat; // Change this if the table format changes or version changes so that the other fields are not the same.
	uint8_t  THyst;          // Temperature hysteresis. Integer.
	uint16_t TMin;           // The temperature, in 0.01 centigrades, below which we just run at a minimal PWM.
	uint16_t TMed;           // The middle temperature where we change slopes.
	uint16_t THigh;          // The high point above TMed for adjusting the second slope.
	uint16_t PWMMin;         // The minimum PWM value in percent (0.01% increments).
	uint16_t PWMMed;         // The PWM value (in percent) at TMed.
	uint16_t PWMHigh;        // The PWM value at THigh.
};

struct atom_pplib_fantable2 {
	struct atom_pplib_fantable basicTable;
	uint16_t TMax; // The max temperature
};

struct atom_pplib_fantable3 {
	struct atom_pplib_fantable2 basicTable2;
	uint8_t  FanControlMode;
	uint16_t FanPWMMax;
	uint16_t FanOutputSensitivity;
};

struct atom_pplib_fantable4 {
	struct atom_pplib_fantable3 basicTable3;
	uint16_t FanRPMMax;
};

struct atom_pplib_fantable5 {
	struct atom_pplib_fantable4 basicTable4;
	uint16_t FanCurrentLow;
	uint16_t FanCurrentHigh;
	uint16_t FanRPMLow;
	uint16_t FanRPMHigh;
};

struct atom_pplib_extendedheader {
	uint16_t Size;
	uint32_t MaxEngineClock; // For Overdrive.
	uint32_t MaxMemoryClock; // For Overdrive.
	uint16_t VCETableOffset;
	uint16_t UVDTableOffset;
	uint16_t SAMUTableOffset;
	uint16_t PPMTableOffset;
	uint16_t ACPTableOffset;
	uint16_t PowerTuneTableOffset;
	uint16_t SclkVddgfxTableOffset;
	uint16_t VQBudgetingTableOffset;
};

union pptable_powerplay_platform_caps {
	uint32_t platform_caps;
	struct { uint32_t
		back_bias                :2-2 +1,
		powerplay                :3-3 +1, 
		sbios_powersource        :4-4 +1, // if power source notificaiton is done by SBIOS directly.
		ASPM_L0S                 :5-5 +1,
		ASPM_L1                  :6-6 +1,
		hardware_DC              :7-7 +1, // if power source notificaiton is done by GPIO directly.
		gemini_primary           :8-8 +1,
		step_VDDC                :9-9 +1,
		voltage_control         :10-10 +1,
		sideport_control        :11-11 +1,
		turn_off_PLL_ASPML1     :12-12 +1,
		ht_link_control         :13-13 +1,
		MVDD_control            :14-14 +1, // if dynamic MVDD is required. Uncheck to disable it.
		goto_boot_on_alert      :15-15 +1, // Go to boot state on alerts, e.g. on an AC->DC transition.
		dont_wait_for_vblank    :16-16 +1, // Do NOT wait for VBLANK during an alert (e.g. AC->DC transition).
		VDDCI_control           :17-17 +1, // Does the driver control VDDCI independently from VDDC.
		regulator_hot           :18-18 +1, // Enable the 'regulator hot' feature.
		BACO                    :19-19 +1, // Does the driver supports BACO state.
		new_CAC_voltage         :20-20 +1, // Does the driver supports new CAC voltage table.
		revert_GPIO5_polarity   :21-21 +1, // Does the driver supports revert GPIO5 polarity.
		output_thermal2GPIO17   :22-22 +1, // Does the driver supports thermal2GPIO17.
		vrhot_gpio_configurable :23-23 +1, // Does the driver supports VR HOT GPIO Configurable.
		temp_inversion          :24-24 +1, // Does the driver supports Temp Inversion feature.
		EVV                     :25-25 +1,
		PCC_shares_thermal_GPIO :26-26 +1, // Enable to indicate if thermal and PCC are sharing the same GPIO
		load_post_production_FW :27-27 +1,
		no_temp_in_power_calc   :28-28 +1, // disable using actual temperature for power calc
		VRHOT_polarity_high     :29-29 +1,
		reserved                :31-30 +1;
	};
};


// each atom_pplib_powerplaytable increment inherits all previous fields
struct atom_pplib_powerplaytable_v1 {
	struct atom_common_table_header header;

	uint8_t  DataRevision;

	uint8_t  NumStates;
	uint8_t  StateEntrySize;
	uint8_t  ClockInfoSize;
	uint8_t  NonClockSize;

	// offset from start of this table to array of ucNumStates ATOM_PPLIB_STATE structures
	uint16_t StateArrayOffset;

	// offset from start of this table to array of ASIC-specific structures,
	// currently ATOM_PPLIB_CLOCK_INFO.
	uint16_t ClockInfoArrayOffset;

	// offset from start of this table to array of ATOM_PPLIB_NONCLOCK_INFO
	uint16_t NonClockInfoArrayOffset;

	uint16_t BackbiasTime; // in microseconds
	uint16_t VoltageTime;  // in microseconds
	uint16_t TableSize;    //the size of this structure, or the extended structure

	union pptable_powerplay_platform_caps PlatformCaps;

	struct atom_pplib_thermalcontroller  ThermalController;

	uint16_t BootClockInfoOffset;
	uint16_t BootNonClockInfoOffset;
};

struct atom_pplib_powerplaytable_v2 {
	struct atom_common_table_header header;

	uint8_t  DataRevision;

	uint8_t  NumStates;
	uint8_t  StateEntrySize;
	uint8_t  ClockInfoSize;
	uint8_t  NonClockSize;

	// offset from start of this table to array of ucNumStates ATOM_PPLIB_STATE structures
	uint16_t StateArrayOffset;

	// offset from start of this table to array of ASIC-specific structures,
	// currently ATOM_PPLIB_CLOCK_INFO.
	uint16_t ClockInfoArrayOffset;

	// offset from start of this table to array of ATOM_PPLIB_NONCLOCK_INFO
	uint16_t NonClockInfoArrayOffset;

	uint16_t BackbiasTime; // in microseconds
	uint16_t VoltageTime;  // in microseconds
	uint16_t TableSize;    //the size of this structure, or the extended structure

	union pptable_powerplay_platform_caps PlatformCaps;

	struct atom_pplib_thermalcontroller  ThermalController;

	uint16_t BootClockInfoOffset;
	uint16_t BootNonClockInfoOffset;
	uint8_t  NumCustomThermalPolicy;
	uint16_t CustomThermalPolicyArrayOffset;
};

struct atom_pplib_powerplaytable_v3 {
	struct atom_common_table_header header;

	uint8_t  DataRevision;

	uint8_t  NumStates;
	uint8_t  StateEntrySize;
	uint8_t  ClockInfoSize;
	uint8_t  NonClockSize;

	// offset from start of this table to array of ucNumStates ATOM_PPLIB_STATE structures
	uint16_t StateArrayOffset;

	// offset from start of this table to array of ASIC-specific structures,
	// currently ATOM_PPLIB_CLOCK_INFO.
	uint16_t ClockInfoArrayOffset;

	// offset from start of this table to array of ATOM_PPLIB_NONCLOCK_INFO
	uint16_t NonClockInfoArrayOffset;

	uint16_t BackbiasTime; // in microseconds
	uint16_t VoltageTime;  // in microseconds
	uint16_t TableSize;    //the size of this structure, or the extended structure

	union pptable_powerplay_platform_caps PlatformCaps;

	struct atom_pplib_thermalcontroller  ThermalController;

	uint16_t BootClockInfoOffset;
	uint16_t BootNonClockInfoOffset;
	uint8_t  NumCustomThermalPolicy;
	uint16_t CustomThermalPolicyArrayOffset;
	uint16_t FormatID; // To be used ONLY by PPGen.
	uint16_t FanTableOffset;
	uint16_t ExtendendedHeaderOffset;
};

struct atom_pplib_powerplaytable_v4 {
	struct atom_common_table_header header;

	uint8_t  DataRevision;

	uint8_t  NumStates;
	uint8_t  StateEntrySize;
	uint8_t  ClockInfoSize;
	uint8_t  NonClockSize;

	// offset from start of this table to array of ucNumStates ATOM_PPLIB_STATE structures
	uint16_t StateArrayOffset;

	// offset from start of this table to array of ASIC-specific structures,
	// currently ATOM_PPLIB_CLOCK_INFO.
	uint16_t ClockInfoArrayOffset;

	// offset from start of this table to array of ATOM_PPLIB_NONCLOCK_INFO
	uint16_t NonClockInfoArrayOffset;

	uint16_t BackbiasTime; // in microseconds
	uint16_t VoltageTime;  // in microseconds
	uint16_t TableSize;    //the size of this structure, or the extended structure

	union pptable_powerplay_platform_caps PlatformCaps;

	struct atom_pplib_thermalcontroller  ThermalController;

	uint16_t BootClockInfoOffset;
	uint16_t BootNonClockInfoOffset;
	uint8_t  NumCustomThermalPolicy;
	uint16_t CustomThermalPolicyArrayOffset;
	uint16_t FormatID; // To be used ONLY by PPGen.
	uint16_t FanTableOffset;
	uint16_t ExtendendedHeaderOffset;
	uint32_t GoldenPPID;     // PPGen use only     
	uint32_t GoldenRevision; // PPGen use only
	uint16_t VddcDependencyOnSCLKOffset;
	uint16_t VddciDependencyOnMCLKOffset;
	uint16_t VddcDependencyOnMCLKOffset;
	uint16_t MaxClockVoltageOnDCOffset;
	uint16_t VddcPhaseShedLimitsTableOffset;
	uint16_t MvddDependencyOnMCLKOffset;  
};

struct atom_pplib_powerplaytable_v5 {
	struct atom_common_table_header header;

	uint8_t  DataRevision;

	uint8_t  NumStates;
	uint8_t  StateEntrySize;
	uint8_t  ClockInfoSize;
	uint8_t  NonClockSize;

	// offset from start of this table to array of ucNumStates ATOM_PPLIB_STATE structures
	uint16_t StateArrayOffset;

	// offset from start of this table to array of ASIC-specific structures,
	// currently ATOM_PPLIB_CLOCK_INFO.
	uint16_t ClockInfoArrayOffset;

	// offset from start of this table to array of ATOM_PPLIB_NONCLOCK_INFO
	uint16_t NonClockInfoArrayOffset;

	uint16_t BackbiasTime; // in microseconds
	uint16_t VoltageTime;  // in microseconds
	uint16_t TableSize;    //the size of this structure, or the extended structure

	union pptable_powerplay_platform_caps PlatformCaps;

	struct atom_pplib_thermalcontroller  ThermalController;

	uint16_t BootClockInfoOffset;
	uint16_t BootNonClockInfoOffset;
	uint8_t  NumCustomThermalPolicy;
	uint16_t CustomThermalPolicyArrayOffset;
	uint16_t FormatID; // To be used ONLY by PPGen.
	uint16_t FanTableOffset;
	uint16_t ExtendendedHeaderOffset;
	uint32_t GoldenPPID;     // PPGen use only     
	uint32_t GoldenRevision; // PPGen use only
	uint16_t VddcDependencyOnSCLKOffset;
	uint16_t VddciDependencyOnMCLKOffset;
	uint16_t VddcDependencyOnMCLKOffset;
	uint16_t MaxClockVoltageOnDCOffset;
	uint16_t VddcPhaseShedLimitsTableOffset;
	uint16_t MvddDependencyOnMCLKOffset;  
	uint32_t TDPLimit;
	uint32_t NearTDPLimit;
	uint32_t SQRampingThreshold;
	uint16_t CACLeakageTableOffset;
	uint32_t CACLeakage;    // The iLeakage for driver calculated CAC leakage table
	uint16_t TDPODLimit;
	uint16_t LoadLineSlope; // in milliOhms * 100
};
union atom_pplib_powerplaytables {
	struct atom_common_table_header header;
	struct atom_pplib_powerplaytable_v1 v1;
	struct atom_pplib_powerplaytable_v2 v2;
	struct atom_pplib_powerplaytable_v3 v3;
	struct atom_pplib_powerplaytable_v4 v4;
	struct atom_pplib_powerplaytable_v5 v5;
};

struct atom_pplib_thermal_state {
	uint8_t  MinTemperature;
	uint8_t  MaxTemperature;
	uint8_t  ThermalAction;
};

// Contained in an array starting at the offset
// in ATOM_PPLIB_POWERPLAYTABLE::usNonClockInfoArrayOffset.
// referenced from ATOM_PPLIB_STATE_INFO::ucNonClockStateIndex
#define ATOM_PPLIB_NONCLOCKINFO_VER1 12 // size of atom_pplib_nonclock_info ?
#define ATOM_PPLIB_NONCLOCKINFO_VER2 24
struct atom_pplib_nonclock_info {
	union atom_pplib_classification Classification;
	uint8_t  MinTemperature;
	uint8_t  MaxTemperature;
	union atom_pplib_caps_and_settings CapsAndSettings;
	uint8_t  RequiredPower;
	union atom_pplib_classification2 Classification2;
	uint32_t VCLK;
	uint32_t DCLK;
	uint8_t  Unused[5];
};

// Contained in an array starting at the offset
// in ATOM_PPLIB_POWERPLAYTABLE::usClockInfoArrayOffset.
// referenced from ATOM_PPLIB_STATE::ucClockStateIndices
union atom_pplib_r600_flags {
	uint32_t Flags;
	struct { uint32_t
		pciegen2       :0-0 +1,
		uvdsafe        :1-1 +1,
		backbiasenable :2-2 +1,
		memory_odt_off :3-3 +1,
		memory_dll_off :4-4 +1,
		lowpower       :5-5 +1, // On the RV770 use 'low power' setting (sequencer S0).
		reserved      :31-6 +1;
	};
};
struct atom_pplib_r600_clock_info {
	uint16_t EngineClockLow;
	uint8_t  EngineClockHigh;

	uint16_t MemoryClockLow;
	uint8_t  MemoryClockHigh;

	uint16_t VDDC;
	uint16_t Unused1;
	uint16_t Unused2;

	union atom_pplib_r600_flags Flags;
};



enum ATOM_PPLIB_RS780_VOLTAGE:uint16_t {
	ATOM_PPLIB_RS780_VOLTAGE_NONE     = 0, 
	ATOM_PPLIB_RS780_VOLTAGE_LOW      = 1, 
	ATOM_PPLIB_RS780_VOLTAGE_HIGH     = 2, 
	ATOM_PPLIB_RS780_VOLTAGE_VARIABLE = 3, 
};
enum ATOM_PPLIB_RS780_SPMCLK:uint16_t {
	ATOM_PPLIB_RS780_SPMCLK_NONE = 0,   // We cannot change the side port memory clock, leave it as it is.
	ATOM_PPLIB_RS780_SPMCLK_LOW  = 1,
	ATOM_PPLIB_RS780_SPMCLK_HIGH = 2,
};
enum ATOM_PPLIB_RS780_HTLINKFREQ:uint16_t {
	ATOM_PPLIB_RS780_HTLINKFREQ_NONE = 0, 
	ATOM_PPLIB_RS780_HTLINKFREQ_LOW  = 1, 
	ATOM_PPLIB_RS780_HTLINKFREQ_HIGH = 2, 
};
struct atom_pplib_rs780_clock_info {
	uint16_t LowEngineClockLow;  // Low Engine clock in MHz (the same way as on the R600).
	uint8_t  LowEngineClockHigh;
	uint16_t HighEngineClockLow; // High Engine clock in MHz.
	uint8_t  HighEngineClockHigh;
	enum ATOM_PPLIB_RS780_SPMCLK  MemoryClockLow;
	uint8_t  MemoryClockHigh;    // Currentyl unused.
	uint8_t  Padding;            // For proper alignment and size.
	enum ATOM_PPLIB_RS780_VOLTAGE  VDDC;
	uint8_t  MaxHTLinkWidth;     // From SBIOS - {2, 4, 8, 16}
	uint8_t  MinHTLinkWidth;     // From SBIOS - {2, 4, 8, 16}. Effective only if CDLW enabled. Minimum down stream width could 
	enum ATOM_PPLIB_RS780_HTLINKFREQ  HTLinkFreq; // See definition ATOM_PPLIB_RS780_HTLINKFREQ_xxx or in MHz(>=200).
	uint32_t Flags; 
};

struct atom_pplib_evergreen_clock_info {
	uint16_t EngineClockLow;
	uint8_t  EngineClockHigh;

	uint16_t MemoryClockLow;
	uint8_t  MemoryClockHigh;

	uint16_t VDDC;
	uint16_t VDDCI;
	uint16_t Unused;

	uint32_t Flags; // ATOM_PPLIB_R600_FLAGS_*
};

struct atom_pplib_si_clock_info {
	uint16_t EngineClockLow;
	uint8_t  EngineClockHigh;

	uint16_t MemoryClockLow;
	uint8_t  MemoryClockHigh;

	uint16_t VDDC;
	uint16_t VDDCI;
	uint8_t  PCIEGen;
	uint8_t  Unused1;

	uint32_t Flags; // ATOM_PPLIB_SI_FLAGS_*, no flag is necessary for now
};

struct atom_pplib_ci_clock_info {
	uint16_t EngineClockLow;
	uint8_t  EngineClockHigh;

	uint16_t MemoryClockLow;
	uint8_t  MemoryClockHigh;
	
	uint8_t  PCIEGen;
	uint16_t PCIELane;
};

struct atom_pplib_sumo_clock_info {
	uint16_t EngineClockLow;  //clockfrequency & 0xFFFF. The unit is in 10khz
	uint8_t  EngineClockHigh; //clockfrequency >> 16. 
	uint8_t  vddcIndex;       //2-bit vddc index;
	uint16_t tdpLimit;
	uint16_t rsv1;
	uint32_t rsv2[2];
};

struct atom_pplib_kv_clock_info {
	uint16_t EngineClockLow;
	uint8_t  EngineClockHigh;
	uint8_t  vddcIndex;
	uint16_t tdpLimit;
	uint16_t rsv1;
	uint32_t rsv2[2];
};

struct atom_pplib_cz_clock_info {
	uint8_t  index;
	uint8_t  rsv[3];
};

struct atom_pplib_state_v2 {
	uint8_t  NumDPMLevels;
	
	uint8_t  nonClockInfoIndex;
	uint8_t  clockInfoIndex[];
};

struct statearray {
	uint8_t  NumEntries;
	struct atom_pplib_state_v2 states[] /* __counted_by(ucNumEntries) */;
};


struct clockinfoarray {
	uint8_t  NumEntries;
	uint8_t  EntrySize; //sizeof(ATOM_PPLIB_CLOCK_INFO)
	uint8_t  clockInfo[];
};

struct nonclockinfoarray {
	uint8_t  NumEntries;
	uint8_t  EntrySize; // sizeof(ATOM_PPLIB_NONCLOCK_INFO)
	struct atom_pplib_nonclock_info nonClockInfo[] __counted_by(ucNumEntries);
};

struct atom_pplib_clock_voltage_dependency_record {
	uint16_t ClockLow;
	uint8_t  ClockHigh;
	uint16_t Voltage;
};

struct atom_pplib_clock_voltage_dependency_table {
	uint8_t  NumEntries;
	struct atom_pplib_clock_voltage_dependency_record entries[] __counted_by(ucNumEntries);
};

struct atom_pplib_clock_voltage_limit_record {
	uint16_t SclkLow;
	uint8_t  SclkHigh;
	uint16_t MclkLow;
	uint8_t  MclkHigh;
	uint16_t Vddc;
	uint16_t Vddci;
};

struct atom_pplib_clock_voltage_limit_table {
	uint8_t  NumEntries;
	struct atom_pplib_clock_voltage_limit_record entries[] __counted_by(ucNumEntries);
};

union atom_pplib_cac_leakage_record {
	struct {
		uint16_t Vddc;         // We use this field for the "fake" standardized VDDC for power calculations; For CI and newer, we use this as the real VDDC value. in CI we read it as StdVoltageHiSidd
		uint32_t LeakageValue; // For CI and newer we use this as the "fake" standar VDDC value. in CI we read it as StdVoltageLoSidd
	};
	struct {
		uint16_t Vddc1;
		uint16_t Vddc2;
		uint16_t Vddc3;
	};
};
struct atom_pplib_cac_leakage_table {
	uint8_t  NumEntries;
	union atom_pplib_cac_leakage_record entries[] __counted_by(ucNumEntries);
};

struct atom_pplib_phasesheddinglimits_record {
	uint16_t Voltage;
	uint16_t SclkLow;
	uint8_t  SclkHigh;
	uint16_t MclkLow;
	uint8_t  MclkHigh;
};

struct atom_pplib_phasesheddinglimits_table {
	uint8_t  NumEntries;
	struct atom_pplib_phasesheddinglimits_record entries[] __counted_by(ucNumEntries);
};

struct vceclockinfo {
	uint16_t EVClkLow;
	uint8_t  EVClkHigh;
	uint16_t ECClkLow;
	uint8_t  ECClkHigh;
};

struct vceclockinfoarray {
	uint8_t  NumEntries;
	struct vceclockinfo entries[] __counted_by(ucNumEntries);
};

struct atom_pplib_vce_clock_voltage_limit_record {
	uint16_t Voltage;
	uint8_t  VCEClockInfoIndex;
};

struct atom_pplib_vce_clock_voltage_limit_table {
	uint8_t  numEntries;
	struct atom_pplib_vce_clock_voltage_limit_record entries[] __counted_by(numEntries);
};

struct atom_pplib_vce_state_record {
	uint8_t  VCEClockInfoIndex;
	uint8_t  ClockInfoIndex; // highest 2 bits indicates memory p-states, lower 6bits indicates index to ClockInfoArrary
};

struct atom_pplib_vce_state_table {
	uint8_t  numEntries;
	struct atom_pplib_vce_state_record entries[] __counted_by(numEntries);
};


struct atom_pplib_vce_table {
	uint8_t  RevId;
//	struct vceclockinfoarray array;
//	struct atom_pplib_vce_clock_voltage_limit_table limits;
//	struct atom_pplib_vce_state_table states;
};


struct uvdclockinfo {
	uint16_t VClkLow;
	uint8_t  VClkHigh;
	uint16_t DClkLow;
	uint8_t  DClkHigh;
};

struct uvdclockinfoarray {
	uint8_t  NumEntries;
	struct uvdclockinfo entries[] __counted_by(ucNumEntries);
};

struct atom_pplib_uvd_clock_voltage_limit_record {
	uint16_t Voltage;
	uint8_t  UVDClockInfoIndex;
};

struct atom_pplib_uvd_clock_voltage_limit_table {
	uint8_t  numEntries;
	struct atom_pplib_uvd_clock_voltage_limit_record entries[] __counted_by(numEntries);
};

struct atom_pplib_uvd_table {
	uint8_t  RevId;
//	struct uvdclockinfoarray array;
//	struct atom_pplib_uvd_clock_voltage_limit_table limits;
};

struct atom_pplib_samclk_voltage_limit_record {
	uint16_t Voltage;
	uint16_t SAMClockLow;
	uint8_t  SAMClockHigh;
};

struct atom_pplib_samclk_voltage_limit_table {
	uint8_t  numEntries;
	struct atom_pplib_samclk_voltage_limit_record entries[] __counted_by(numEntries);
};

struct atom_pplib_samu_table {
	uint8_t  RevId;
	struct atom_pplib_samclk_voltage_limit_table limits;
};

struct atom_pplib_acpclk_voltage_limit_record {
	uint16_t Voltage;
	uint16_t ACPClockLow;
	uint8_t  ACPClockHigh;
};

struct atom_pplib_acpclk_voltage_limit_table {
	uint8_t  numEntries;
	struct atom_pplib_acpclk_voltage_limit_record entries[] __counted_by(numEntries);
};

struct atom_pplib_acp_table {
	uint8_t  RevId;
	struct atom_pplib_acpclk_voltage_limit_table limits;
};

struct atom_powertune_table {
	uint16_t TDP;
	uint16_t ConfigurableTDP;
	uint16_t TDC;
	uint16_t BatteryPowerLimit;
	uint16_t SmallPowerLimit;
	uint16_t LowCACLeakage;
	uint16_t HighCACLeakage;
};

struct atom_pplib_powertune_table {
	uint8_t  RevId;
	struct atom_powertune_table power_tune_table;
};

struct atom_pplib_powertune_table_v1 {
	uint8_t  RevId;
	struct atom_powertune_table power_tune_table;
	uint16_t MaximumPowerDeliveryLimit;
	uint16_t TjMax;
	uint16_t Reserve[6];
};

struct atom_pplib_ppm_table {
	uint8_t  RevId;
	enum atom_ppm PpmDesign;
	uint16_t CpuCoreNumber;
	uint32_t PlatformTDP;
	uint32_t SmallACPlatformTDP;
	uint32_t PlatformTDC;
	uint32_t SmallACPlatformTDC;
	uint32_t ApuTDP;
	uint32_t DGpuTDP;  
	uint32_t DGpuUlvPower;
	uint32_t Tjmax;
};

enum vq_dispconfig:uint8_t {
	VQ_DisplayConfig_NoneAWD = 1,
	VQ_DisplayConfig_AWD     = 2,
};
struct atom_pplib_vq_budgeting_record {
	uint32_t DeviceID;
	uint32_t SustainableSOCPowerLimitLow; // in mW
	uint32_t SustainableSOCPowerLimitHigh; // in mW

	uint32_t DClk;
	uint32_t EClk;
	uint32_t DispSclk;
	enum vq_dispconfig DispConfig;
};

struct atom_pplib_vq_budgeting_table {
	uint8_t  RevId;
	uint8_t  numEntries;
	struct atom_pplib_vq_budgeting_record entries[] __counted_by(numEntries);
};

#pragma pack()

#endif
