// consider linux/drivers/gpu/drm/amd/include/pptable.h

#ifndef VEGA10_PPTABLE_H
#define VEGA10_PPTABLE_H
#pragma pack(push, 1) // bios data must use byte alignment

#define ATOM_Vega10_TABLE_REVISION_VEGA10 8

union vega10_powerplay_platform_caps {
	uint32_t platform_caps;
	struct { uint32_t
		powerplay                       :0-0 +1, // whether CCC needs to show Powerplay page.
		sbios_powersource               :1-1 +1, // whether power source notificaiton is done by SBIOS instead of OS.
		hardware_dc                     :2-2 +1, // whether DC mode notificaiton is done by GPIO pin directly.
		BACO                            :3-3 +1, // whether board supports the BACO circuitry. BACO is Bus Active, Chip Off. A low-power mode whereby most of the GPU is shut-off during idle periods in order to drastically cut the power consumption of the graphics card. BACO is also known as AMD ZeroCore Power mode.
		combine_pcc_with_thermal_signal :4-4 +1,
		reserved                       :31-5 +1;
	};
};


enum atom_vega10_voltagemode:uint8_t {
	ATOM_VEGA10_VOLTAGEMODE_AVFS_INTERPOLATE = 0,
	ATOM_VEGA10_VOLTAGEMODE_AVFS_WORSTCASE   = 1,
	ATOM_VEGA10_VOLTAGEMODE_STATIC           = 2,
};

struct atom_vega10_powerplaytable {
	struct smu_powerplay_table_header header;
	union vega10_powerplay_platform_caps PlatformCaps;
	uint32_t MaxODEngineClock; // For Overdrive.
	uint32_t MaxODMemoryClock; // For Overdrive.
	uint16_t PowerControlLimit;
	uint16_t UlvVoltageOffset; // in mv units
	uint16_t UlvSmnclkDid;
	uint16_t UlvMp1clkDid;
	uint16_t UlvGfxclkBypass;
	uint16_t GfxclkSlewRate;
	enum atom_vega10_voltagemode  GfxVoltageMode;
	enum atom_vega10_voltagemode  SocVoltageMode;
	enum atom_vega10_voltagemode  UclkVoltageMode;
	enum atom_vega10_voltagemode  UvdVoltageMode;
	enum atom_vega10_voltagemode  VceVoltageMode;
	enum atom_vega10_voltagemode  Mp0VoltageMode;
	enum atom_vega10_voltagemode  DcefVoltageMode;
	uint16_t StateArrayOffset;
	uint16_t FanTableOffset;
	uint16_t ThermalControllerOffset;
	uint16_t SocclkDependencyTableOffset;
	uint16_t MclkDependencyTableOffset;
	uint16_t GfxclkDependencyTableOffset;
	uint16_t DcefclkDependencyTableOffset;
	uint16_t VddcLookupTableOffset;
	uint16_t VddmemLookupTableOffset;
	uint16_t MMDependencyTableOffset;
	uint16_t VCEStateTableOffset;
	uint16_t Reserve; // No PPM Support for Vega10
	uint16_t PowerTuneTableOffset;
	uint16_t HardLimitTableOffset;
	uint16_t VddciLookupTableOffset;
	uint16_t PCIETableOffset;
	uint16_t PixclkDependencyTableOffset;
	uint16_t DispClkDependencyTableOffset;
	uint16_t PhyClkDependencyTableOffset;
};

struct atom_vega10_state {
	uint8_t  SocClockIndexHigh;
	uint8_t  SocClockIndexLow;
	uint8_t  GfxClockIndexHigh;
	uint8_t  GfxClockIndexLow;
	uint8_t  MemClockIndexHigh;
	uint8_t  MemClockIndexLow;
	union atom_pplib_classification    Classification;
	union atom_pplib_caps_and_settings CapsAndSettings;
	union atom_pplib_classification2   Classification2;
};

struct atom_vega10_state_array {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_vega10_state  states[1];
};

struct atom_vega10_clk_dependency_record {
	uint32_t Clk;    // Frequency of Clock
	uint8_t  VddInd; // Base voltage ; SOC_VDD index
};
struct atom_vega10_clk_dependency_table {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_vega10_clk_dependency_record  entries[1];
};


union clock_stretch_config_u16 {
	uint16_t CKSVOffsetandDisable; // clock stretch
	struct { uint16_t
		cks_voltage_offset :14-0 +1,
		disable_stretch    :15-15 +1;
	};
};
struct atom_vega10_gfxclk_dependency_record {
	struct atom_vega10_clk_dependency_record  base;
	union clock_stretch_config_u16  CKSVOffsetandDisable;
	uint16_t AVFSOffset; // AVFS Voltage offset
};
struct atom_vega10_gfxclk_dependency_table_v1 {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_vega10_gfxclk_dependency_record  entries[1];
};
struct atom_vega10_gfxclk_dependency_record_v2 {
	struct atom_vega10_clk_dependency_record  base;
	union clock_stretch_config_u16  CKSVOffsetandDisable;
	uint16_t AVFSOffset; // AVFS Voltage offset
	uint8_t  ACGEnable;
	uint8_t  Reserved[3];
};
struct atom_vega10_gfxclk_dependency_table_v2 {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_vega10_gfxclk_dependency_record_v2  entries[1];
};
union atom_vega10_gfxclk_dependency_tables {
	uint8_t  RevId;
	struct atom_vega10_gfxclk_dependency_table_v1 v1;
	struct atom_vega10_gfxclk_dependency_table_v2 v2;
};

struct atom_vega10_mclk_dependency_record {
	struct atom_vega10_clk_dependency_record  base;
	uint8_t  VddMemInd; // MEM_VDD - only non zero for MCLK record
	uint8_t  VddciInd;  // VDDCI   = only non zero for MCLK record
};
struct atom_vega10_mclk_dependency_table {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_vega10_mclk_dependency_record  entries[1];
};




struct atom_vega10_mm_dependency_record {
	uint8_t  VddcInd; // SOC_VDD voltage
	uint32_t DClk;    // UVD D-clock
	uint32_t VClk;    // UVD V-clock
	uint32_t EClk;    // VCE clock
	uint32_t PSPClk;  // PSP clock
};

struct atom_vega10_mm_dependency_table {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_vega10_mm_dependency_record  entries[1];
};

struct atom_vega10_pcie_record {
	uint32_t LCLK;          // LClock
	uint8_t  PCIEGenSpeed;  // PCIE Speed
	uint8_t  PCIELaneWidth; // PCIE Lane Width
};

struct atom_vega10_pcie_table {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_vega10_pcie_record  entries[1];
};

/*struct atom_vega10_voltage_lookup_record {
	uint16_t Vdd; // Base voltage
};*/
struct atom_vega10_voltage_lookup_table {
	uint8_t  RevId;
	uint8_t  NumEntries;
	uint16_t vdd_entries[1];
};

struct atom_vega10_fan_table_v1 {
	uint8_t  RevId;
	uint16_t FanOutputSensitivity; // Sensitivity of fan reaction to temepature changes.
	uint16_t FanRPMMax;            // The default value in RPM.
	uint16_t ThrottlingRPM;
	uint16_t FanAcousticLimit;     // Minimum Fan Controller Frequency Acoustic Limit.
	uint16_t TargetTemperature;    // The default ideal temperature in Celcius.
	uint16_t MinimumPWMLimit;      // The minimum PWM that the advanced fan controller can set.
	uint16_t TargetGfxClk;         // The ideal Fan Controller GFXCLK Frequency Acoustic Limit.
	uint16_t FanGainEdge;
	uint16_t FanGainHotspot;
	uint16_t FanGainLiquid;
	uint16_t FanGainVrVddc;
	uint16_t FanGainVrMvdd;
	uint16_t FanGainPlx;
	uint16_t FanGainHbm;
	uint8_t  EnableZeroRPM;
	uint16_t FanStopTemperature;
	uint16_t FanStartTemperature;
};
struct atom_vega10_fan_table_v2 {
	uint8_t  RevId;
	uint16_t FanOutputSensitivity; // Sensitivity of fan reaction to temepature changes.
	uint16_t FanAcousticLimit;     // Minimum Fan Controller Frequency Acoustic Limit.
	uint16_t ThrottlingRPM;
	uint16_t TargetTemperature;    // The default ideal temperature in Celcius.
	uint16_t MinimumPWMLimit;      // The minimum PWM that the advanced fan controller can set.
	uint16_t TargetGfxClk;         // The ideal Fan Controller GFXCLK Frequency Acoustic Limit.

	uint16_t FanGainEdge;
	uint16_t FanGainHotspot;
	uint16_t FanGainLiquid;
	uint16_t FanGainVrVddc;
	uint16_t FanGainVrMvdd;
	uint16_t FanGainPlx;
	uint16_t FanGainHbm;
	uint8_t  EnableZeroRPM;
	uint16_t FanStopTemperature;
	uint16_t FanStartTemperature;
	union atom_pp_fanparameters  FanParameters;
	uint8_t  FanMinRPM;
	uint8_t  FanMaxRPM;
};
struct atom_vega10_fan_table_v3 {
	uint8_t  RevId;
	uint16_t FanOutputSensitivity; // Sensitivity of fan reaction to temepature changes.
	uint16_t FanAcousticLimit;     // Minimum Fan Controller Frequency Acoustic Limit.
	uint16_t ThrottlingRPM;
	uint16_t TargetTemperature;    // The default ideal temperature in Celcius.
	uint16_t MinimumPWMLimit;      // The minimum PWM that the advanced fan controller can set.
	uint16_t TargetGfxClk;         // The ideal Fan Controller GFXCLK Frequency Acoustic Limit.
	uint16_t FanGainEdge;
	uint16_t FanGainHotspot;
	uint16_t FanGainLiquid;
	uint16_t FanGainVrVddc;
	uint16_t FanGainVrMvdd;
	uint16_t FanGainPlx;
	uint16_t FanGainHbm;
	uint8_t  EnableZeroRPM;
	uint16_t FanStopTemperature;
	uint16_t FanStartTemperature;
	union atom_pp_fanparameters  FanParameters;
	uint8_t  FanMinRPM;
	uint8_t  FanMaxRPM;
	uint16_t MGpuThrottlingRPM;
};
union atom_vega10_fan_tables {
	uint8_t  RevId;
	struct atom_vega10_fan_table_v1 v1;
	struct atom_vega10_fan_table_v2 v2;
	struct atom_vega10_fan_table_v3 v3;
};

struct atom_vega10_thermal_controller {
	uint8_t  RevId;
	enum ATOM_PP_THERMALCONTROLLER  Type;
	uint8_t  I2cLine; // as interpreted by DAL I2C
	uint8_t  I2cAddress;
	union atom_pp_fanparameters  FanParameters;
	uint8_t  FanMinRPM; // Fan Minimum RPM (hundreds) -- for display purposes only.
	uint8_t  FanMaxRPM; // Fan Maximum RPM (hundreds) -- for display purposes only.
	uint8_t  Flags;     // to be defined
};

struct atom_vega10_vce_state_record {
	uint8_t  VCEClockIndex; // index into usVCEDependencyTableOffset of 'ATOM_Vega10_MM_Dependency_Table' type
	uint8_t  Flag;          // 2 bits indicates memory p-states
	uint8_t  SCLKIndex;     // index into ATOM_Vega10_SCLK_Dependency_Table
	uint8_t  MCLKIndex;     // index into ATOM_Vega10_MCLK_Dependency_Table
};
struct atom_vega10_vce_state_table {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_vega10_vce_state_record  entries[1];
};

struct atom_vega10_powertune_table_v1 {
	uint8_t  RevId;
	uint16_t SocketPowerLimit;
	uint16_t BatteryPowerLimit;
	uint16_t SmallPowerLimit;
	uint16_t TdcLimit;
	uint16_t EdcLimit;
	uint16_t SoftwareShutdownTemp;
	uint16_t TemperatureLimitHotSpot;
	uint16_t TemperatureLimitLiquid1;
	uint16_t TemperatureLimitLiquid2;
	uint16_t TemperatureLimitHBM;
	uint16_t TemperatureLimitVrSoc;
	uint16_t TemperatureLimitVrMem;
	uint16_t TemperatureLimitPlx;
	uint16_t LoadLineResistance;
	uint8_t  Liquid1_I2C_address;
	uint8_t  Liquid2_I2C_address;
	uint8_t  Vr_I2C_address;
	uint8_t  Plx_I2C_address;
	uint8_t  Liquid_I2C_LineSCL;
	uint8_t  Liquid_I2C_LineSDA;
	uint8_t  Vr_I2C_LineSCL;
	uint8_t  Vr_I2C_LineSDA;
	uint8_t  Plx_I2C_LineSCL;
	uint8_t  Plx_I2C_LineSDA;
	uint16_t TemperatureLimitTedge;
};
struct atom_vega10_powertune_table_v2 {
	uint8_t  RevId;
	uint16_t SocketPowerLimit;
	uint16_t BatteryPowerLimit;
	uint16_t SmallPowerLimit;
	uint16_t TdcLimit;
	uint16_t EdcLimit;
	uint16_t SoftwareShutdownTemp;
	uint16_t TemperatureLimitHotSpot;
	uint16_t TemperatureLimitLiquid1;
	uint16_t TemperatureLimitLiquid2;
	uint16_t TemperatureLimitHBM;
	uint16_t TemperatureLimitVrSoc;
	uint16_t TemperatureLimitVrMem;
	uint16_t TemperatureLimitPlx;
	uint16_t LoadLineResistance;
	uint8_t  Liquid1_I2C_address;
	uint8_t  Liquid2_I2C_address;
	uint8_t  Liquid_I2C_Line;
	uint8_t  Vr_I2C_address;
	uint8_t  Vr_I2C_Line;
	uint8_t  Plx_I2C_address;
	uint8_t  Plx_I2C_Line;
	uint16_t TemperatureLimitTedge;
};
struct atom_vega10_powertune_table_v3 {
	uint8_t  RevId;
	uint16_t SocketPowerLimit;
	uint16_t BatteryPowerLimit;
	uint16_t SmallPowerLimit;
	uint16_t TdcLimit;
	uint16_t EdcLimit;
	uint16_t SoftwareShutdownTemp;
	uint16_t TemperatureLimitHotSpot;
	uint16_t TemperatureLimitLiquid1;
	uint16_t TemperatureLimitLiquid2;
	uint16_t TemperatureLimitHBM;
	uint16_t TemperatureLimitVrSoc;
	uint16_t TemperatureLimitVrMem;
	uint16_t TemperatureLimitPlx;
	uint16_t LoadLineResistance;
	uint8_t  Liquid1_I2C_address;
	uint8_t  Liquid2_I2C_address;
	uint8_t  Liquid_I2C_Line;
	uint8_t  Vr_I2C_address;
	uint8_t  Vr_I2C_Line;
	uint8_t  Plx_I2C_address;
	uint8_t  Plx_I2C_Line;
	uint16_t TemperatureLimitTedge;
	uint16_t BoostStartTemperature;
	uint16_t BoostStopTemperature;
	uint32_t BoostClock;
	uint32_t Reserved[2];
};
union atom_vega10_powertune_tables {
	uint8_t  RevId;
	struct atom_vega10_powertune_table_v1 v1;
	struct atom_vega10_powertune_table_v2 v2;
	struct atom_vega10_powertune_table_v3 v3;
};

struct atom_vega10_hard_limit_record {
	uint32_t SOCCLKLimit;
	uint32_t GFXCLKLimit;
	uint32_t MCLKLimit;
	uint16_t VddcLimit;
	uint16_t VddciLimit;
	uint16_t VddMemLimit;
};

struct atom_vega10_hard_limit_table {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_vega10_hard_limit_record  entries[1];
};

#pragma pack(pop) // restore old packing
#endif
