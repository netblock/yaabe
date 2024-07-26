#ifndef TONGA_PPTABLE_H
#define TONGA_PPTABLE_H

/** \file
 * This is a PowerPlay table header file
 */
#pragma pack(push, 1)

// #include "hwmgr.h" // this included in a packed state!

#define ATOM_TONGA_PP_FANPARAMETERS_TACHOMETER_PULSES_PER_REVOLUTION_MASK 0x0f
#define ATOM_TONGA_PP_FANPARAMETERS_NOFAN                                 0x80  /* No fan is connected to this controller. */

#define ATOM_TONGA_PP_THERMALCONTROLLER_NONE    0
#define ATOM_TONGA_PP_THERMALCONTROLLER_LM96163 17
#define ATOM_TONGA_PP_THERMALCONTROLLER_TONGA   21
#define ATOM_TONGA_PP_THERMALCONTROLLER_FIJI    22
/*
 * Thermal controller 'combo type' to use an external controller for Fan control and an internal controller for thermal.
 * We probably should reserve the bit 0x80 for this use.
 * To keep the number of these types low we should also use the same code for all ASICs (i.e. do not distinguish RV6xx and RV7xx Internal here).
 * The driver can pick the correct internal controller based on the ASIC.
 */
#define ATOM_TONGA_PP_THERMALCONTROLLER_ADT7473_WITH_INTERNAL   0x89    // ADT7473 Fan Control + Internal Thermal Controller
#define ATOM_TONGA_PP_THERMALCONTROLLER_EMC2103_WITH_INTERNAL   0x8D    // EMC2103 Fan Control + Internal Thermal Controller

#define ATOM_Tonga_TABLE_REVISION_TONGA 7


union tonga_powerplay_platform_caps {
	uint32_t platform_caps;
	struct { uint32_t
		VDDGFX_control           :0-0 +1, // if vddgfx will be a separated power rail.
		powerplay                :1-1 +1, // if this is a mobile part and CCC need to show Powerplay page.
		SBIOS_powersource        :2-2 +1, // if power source notificaiton is done by SBIOS directly.
		disable_voltage_island   :3-3 +1, // option to overwrite voltage island feature, regardless of VddGfx power rail support.
		reserved_4               :4-4 +1,
		hardware_DC              :5-5 +1, // if power source notificaiton is done by GPIO directly.
		reserved_11_6           :11-6 +1,
		MVDD_control            :12-12 +1, // if dynamic MVDD is required. Uncheck to disable it.
		reserved_14_13          :14-13 +1,
		VDDCI_control           :15-15 +1, // if dynamic VDDCI is required. Uncheck to disable it.
		reserved_16             :16-16 +1,
		BACO                    :17-17 +1, // Enable to indicate the driver supports BACO state.
		reserved_19_18          :19-18 +1,
		output_thermal2GPIO17   :20-20 +1, // Enable to indicate the driver supports thermal2GPIO17.
		reserved_23_21          :23-21 +1,
		PCC_shares_thermal_GPIO :24-24 +1, // Enable to indicate if thermal and PCC are sharing the same GPIO
		load_post_production_FW :25-25 +1,
		reserved_31_26          :31-26 +1;
	};
};


struct atom_tonga_powerplaytable {
	struct smu_powerplay_table_header header;

	uint16_t VoltageTime;  // in microseconds
	union tonga_powerplay_platform_caps PlatformCaps;

	uint32_t MaxODEngineClock; // For Overdrive.
	uint32_t MaxODMemoryClock; // For Overdrive.

	uint16_t PowerControlLimit;
	uint16_t UlvVoltageOffset; // in mv units

	uint16_t StateArrayOffset; // points to ATOM_Tonga_State_Array
	uint16_t FanTableOffset;   // points to ATOM_Tonga_Fan_Table
	uint16_t ThermalControllerOffset; // points to ATOM_Tonga_Thermal_Controller
	uint16_t Reserved0;    // CustomThermalPolicy removed for Tonga. Keep this filed as reserved.

	uint16_t MclkDependencyTableOffset; // points to ATOM_Tonga_MCLK_Dependency_Table
	uint16_t SclkDependencyTableOffset; // points to ATOM_Tonga_SCLK_Dependency_Table
	uint16_t VddcLookupTableOffset;     // points to ATOM_Tonga_Voltage_Lookup_Table
	uint16_t VddgfxLookupTableOffset;   // points to ATOM_Tonga_Voltage_Lookup_Table

	uint16_t MMDependencyTableOffset;    // points to ATOM_Tonga_MM_Dependency_Table

	uint16_t VCEStateTableOffset;       // points to ATOM_Tonga_VCE_State_Table;

	uint16_t PPMTableOffset;    // points to ATOM_Tonga_PPM_Table
	uint16_t PowerTuneTableOffset;    // points to ATOM_PowerTune_Table

	uint16_t HardLimitTableOffset;    // points to ATOM_Tonga_Hard_Limit_Table

	uint16_t PCIETableOffset;    // points to ATOM_Tonga_PCIE_Table

	uint16_t GPIOTableOffset;    // points to ATOM_Tonga_GPIO_Table

	uint16_t Reserved1[6]; // TODO: modify reserved size to fit structure aligning
};

struct atom_tonga_state {
	uint8_t  EngineClockIndexHigh;
	uint8_t  EngineClockIndexLow;

	uint8_t  MemoryClockIndexHigh;
	uint8_t  MemoryClockIndexLow;

	uint8_t  PCIEGenLow;
	uint8_t  PCIEGenHigh;

	uint8_t  PCIELaneLow;
	uint8_t  PCIELaneHigh;

    union atom_pplib_classification    Classification;
    union atom_pplib_caps_and_settings CapsAndSettings;                         
    union atom_pplib_classification2   Classification2;

	uint8_t  Unused[4];
};

struct atom_tonga_state_array {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_tonga_state  entries[];
};

struct atom_tonga_mclk_dependency_record {
	uint8_t  VddcInd; // Base voltage ; SOC_VDD index
	uint16_t Vddci;
	uint16_t VddgfxOffset; // Offset relative to Vddc voltage
	uint16_t Mvdd;
	uint32_t Mclk;
	uint16_t Reserved;
};

struct atom_tonga_mclk_dependency_table {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_tonga_mclk_dependency_record  entries[];
};

union clock_stretch_config_u8 {
	uint8_t CKSVOffsetandDisable; // clock stretch
	struct { uint8_t
		cks_voltage_offset :6-0 +1,
		disable_stretch    :7-7 +1;
	};
};

struct atom_tonga_sclk_dependency_record {
	uint8_t  VddInd; // Base voltage ; SOC_VDD index
	uint16_t VddcOffset; // Offset relative to base voltage
	uint32_t Sclk;
	uint16_t EdcCurrent;
	uint8_t  ReliabilityTemperature;
	union clock_stretch_config_u8  CKSVOffsetandDisable;

};

struct atom_tonga_sclk_dependency_table {
	uint8_t  RevId;
	uint8_t  NumEntries; 
	struct atom_tonga_sclk_dependency_record  entries[];
};

struct atom_polaris_sclk_dependency_record {
	uint8_t  VddInd; // Base voltage ; SOC_VDD index
	uint16_t VddcOffset;
	uint32_t Sclk;
	uint16_t EdcCurrent;
	uint8_t  ReliabilityTemperature;
	union clock_stretch_config_u8  CKSVOffsetandDisable;
	uint32_t SclkOffset;
};

struct atom_polaris_sclk_dependency_table {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_polaris_sclk_dependency_record  entries[];
};

struct atom_tonga_pcie_record {
	uint8_t  PCIEGenSpeed;
	uint8_t  PCIELaneWidth;
	uint8_t  Reserved[2];
};

struct atom_tonga_pcie_table {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_tonga_pcie_record  entries[];
};

struct atom_polaris10_pcie_record {
	uint8_t  PCIEGenSpeed;
	uint8_t  PCIELaneWidth;
	uint8_t  Reserved[2];
	uint32_t PCIE_Sclk;
};

struct atom_polaris10_pcie_table {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_polaris10_pcie_record  entries[];
};


struct atom_tonga_mm_dependency_record {
	uint8_t  VddcInd; // Base voltage ; SOC_VDD index
	uint16_t VddgfxOffset; // Offset relative to VDDC voltage
	uint32_t DClk;    // UVD D-clock
	uint32_t VClk;    // UVD V-clock
	uint32_t EClk;    // VCE clock
	uint32_t AClk;    // ACP clock
	uint32_t SAMUClk; // SAMU clock
};

struct atom_tonga_mm_dependency_table {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_tonga_mm_dependency_record  entries[];
};

struct atom_tonga_voltage_lookup_record {
	uint16_t Vdd;    // Base voltage
	uint16_t CACLow;
	uint16_t CACMid;
	uint16_t CACHigh;
};

struct atom_tonga_voltage_lookup_table {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_tonga_voltage_lookup_record  entries[];
};

struct atom_tonga_fan_table {
	uint8_t  RevId;                   // Change this if the table format changes or version changes so that the other fields are not the same.
	uint8_t  THyst;                   // Temperature hysteresis. Integer.
	uint16_t TMin;                    // The temperature, in 0.01 centigrades, below which we just run at a minimal PWM.
	uint16_t TMed;                    // The middle temperature where we change slopes.
	uint16_t THigh;                   // The high point above TMed for adjusting the second slope.
	uint16_t PWMMin;                  // The minimum PWM value in percent (0.01% increments).
	uint16_t PWMMed;                  // The PWM value (in percent) at TMed.
	uint16_t PWMHigh;                 // The PWM value at THigh.
	uint16_t TMax;                    // The max temperature
	uint8_t  FanControlMode;          // Legacy or Fuzzy Fan mode
	uint16_t FanPWMMax;               // Maximum allowed fan power in percent
	uint16_t FanOutputSensitivity;    // Sensitivity of fan reaction to temepature changes
	uint16_t FanRPMMax;               // The default value in RPM
	uint32_t MinFanSCLKAcousticLimit; // Minimum Fan Controller SCLK Frequency Acoustic Limit.
	uint8_t  TargetTemperature;       // Advanced fan controller target temperature.
	uint8_t  MinimumPWMLimit;         // The minimum PWM that the advanced fan controller can set.	This should be set to the highest PWM that will run the fan at its lowest RPM.
	uint16_t Reserved;
};

struct atom_fiji_fan_table {
	uint8_t  RevId;                   // Change this if the table format changes or version changes so that the other fields are not the same.
	uint8_t  THyst;                   // Temperature hysteresis. Integer.
	uint16_t TMin;                    // The temperature, in 0.01 centigrades, below which we just run at a minimal PWM.
	uint16_t TMed;                    // The middle temperature where we change slopes.
	uint16_t THigh;                   // The high point above TMed for adjusting the second slope.
	uint16_t PWMMin;                  // The minimum PWM value in percent (0.01% increments).
	uint16_t PWMMed;                  // The PWM value (in percent) at TMed.
	uint16_t PWMHigh;                 // The PWM value at THigh.
	uint16_t TMax;                    // The max temperature
	uint8_t  FanControlMode;          // Legacy or Fuzzy Fan mode
	uint16_t FanPWMMax;               // Maximum allowed fan power in percent
	uint16_t FanOutputSensitivity;    // Sensitivity of fan reaction to temepature changes
	uint16_t FanRPMMax;               // The default value in RPM
	uint32_t MinFanSCLKAcousticLimit; // Minimum Fan Controller SCLK Frequency Acoustic Limit.
	uint8_t  TargetTemperature;       // Advanced fan controller target temperature.
	uint8_t  MinimumPWMLimit;         // The minimum PWM that the advanced fan controller can set.	This should be set to the highest PWM that will run the fan at its lowest RPM.
	uint16_t FanGainEdge;
	uint16_t FanGainHotspot;
	uint16_t FanGainLiquid;
	uint16_t FanGainVrVddc;
	uint16_t FanGainVrMvdd;
	uint16_t FanGainPlx;
	uint16_t FanGainHbm;
	uint16_t Reserved;
};

struct atom_polaris_fan_table {
	uint8_t  RevId;                   // Change this if the table format changes or version changes so that the other fields are not the same.
	uint8_t  THyst;                   // Temperature hysteresis. Integer.
	uint16_t TMin;                    // The temperature, in 0.01 centigrades, below which we just run at a minimal PWM.
	uint16_t TMed;                    // The middle temperature where we change slopes.
	uint16_t THigh;                   // The high point above TMed for adjusting the second slope.
	uint16_t PWMMin;                  // The minimum PWM value in percent (0.01% increments).
	uint16_t PWMMed;                  // The PWM value (in percent) at TMed.
	uint16_t PWMHigh;                 // The PWM value at THigh.
	uint16_t TMax;                    // The max temperature
	uint8_t  FanControlMode;          // Legacy or Fuzzy Fan mode
	uint16_t FanPWMMax;               // Maximum allowed fan power in percent
	uint16_t FanOutputSensitivity;    // Sensitivity of fan reaction to temepature changes
	uint16_t FanRPMMax;               // The default value in RPM
	uint32_t MinFanSCLKAcousticLimit; // Minimum Fan Controller SCLK Frequency Acoustic Limit.
	uint8_t  TargetTemperature;       // Advanced fan controller target temperature.
	uint8_t  MinimumPWMLimit;         // The minimum PWM that the advanced fan controller can set.	This should be set to the highest PWM that will run the fan at its lowest RPM.
	uint16_t FanGainEdge;
	uint16_t FanGainHotspot;
	uint16_t FanGainLiquid;
	uint16_t FanGainVrVddc;
	uint16_t FanGainVrMvdd;
	uint16_t FanGainPlx;
	uint16_t FanGainHbm;
	uint8_t  EnableZeroRPM;
	uint8_t  FanStopTemperature;
	uint8_t  FanStartTemperature;
	uint16_t Reserved;
};

struct atom_tonga_thermal_controller {
	uint8_t  RevId;
	uint8_t  Type;          // one of ATOM_TONGA_PP_THERMALCONTROLLER_*
	uint8_t  I2cLine;       // as interpreted by DAL I2C
	uint8_t  I2cAddress;
	union atom_pp_fanparameters FanParameters;
	uint8_t  FanMinRPM;     // Fan Minimum RPM (hundreds) -- for display purposes only.
	uint8_t  FanMaxRPM;     // Fan Maximum RPM (hundreds) -- for display purposes only.
	uint8_t  Reserved;
	uint8_t  Flags;         // to be defined
};

struct atom_tonga_vce_state_record {
	uint8_t  VCEClockIndex; // index into usVCEDependencyTableOffset of 'ATOM_Tonga_MM_Dependency_Table' type
	uint8_t  Flag;          // 2 bits indicates memory p-states
	uint8_t  SCLKIndex;     // index into ATOM_Tonga_SCLK_Dependency_Table
	uint8_t  MCLKIndex;     // index into ATOM_Tonga_MCLK_Dependency_Table
};

struct atom_tonga_vce_state_table {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_tonga_vce_state_record  entries[];
};

struct atom_tonga_powertune_table {
	uint8_t  RevId;
	uint16_t TDP;
	uint16_t ConfigurableTDP;
	uint16_t TDC;
	uint16_t BatteryPowerLimit;
	uint16_t SmallPowerLimit;
	uint16_t LowCACLeakage;
	uint16_t HighCACLeakage;
	uint16_t MaximumPowerDeliveryLimit;
	uint16_t TjMax;
	uint16_t PowerTuneDataSetID;
	uint16_t EDCLimit;
	uint16_t SoftwareShutdownTemp;
	uint16_t ClockStretchAmount;
	uint16_t Reserved[2];
};

struct atom_fiji_powertune_table {
	uint8_t  RevId;
	uint16_t TDP;
	uint16_t ConfigurableTDP;
	uint16_t TDC;
	uint16_t BatteryPowerLimit;
	uint16_t SmallPowerLimit;
	uint16_t LowCACLeakage;
	uint16_t HighCACLeakage;
	uint16_t MaximumPowerDeliveryLimit;
	uint16_t TjMax; // For Fiji, this is also usTemperatureLimitEdge;
	uint16_t PowerTuneDataSetID;
	uint16_t EDCLimit;
	uint16_t SoftwareShutdownTemp;
	uint16_t ClockStretchAmount;
	uint16_t TemperatureLimitHotspot; // The following are added for Fiji
	uint16_t TemperatureLimitLiquid1;
	uint16_t TemperatureLimitLiquid2;
	uint16_t TemperatureLimitVrVddc;
	uint16_t TemperatureLimitVrMvdd;
	uint16_t TemperatureLimitPlx;
	uint8_t  Liquid1_I2C_address; // Liquid
	uint8_t  Liquid2_I2C_address;
	uint8_t  Liquid_I2C_Line;
	uint8_t  Vr_I2C_address; // VR
	uint8_t  Vr_I2C_Line;
	uint8_t  Plx_I2C_address; // PLX
	uint8_t  Plx_I2C_Line;
	uint16_t Reserved;
};

struct atom_polaris_powertune_table {
	uint8_t  RevId;
	uint16_t TDP;
	uint16_t ConfigurableTDP;
	uint16_t TDC;
	uint16_t BatteryPowerLimit;
	uint16_t SmallPowerLimit;
	uint16_t LowCACLeakage;
	uint16_t HighCACLeakage;
	uint16_t MaximumPowerDeliveryLimit;
	uint16_t TjMax; // For Fiji, this is also usTemperatureLimitEdge;
	uint16_t PowerTuneDataSetID;
	uint16_t EDCLimit;
	uint16_t SoftwareShutdownTemp;
	uint16_t ClockStretchAmount;
	uint16_t TemperatureLimitHotspot; // The following are added for Fiji
	uint16_t TemperatureLimitLiquid1;
	uint16_t TemperatureLimitLiquid2;
	uint16_t TemperatureLimitVrVddc;
	uint16_t TemperatureLimitVrMvdd;
	uint16_t TemperatureLimitPlx;
	uint8_t  Liquid1_I2C_address; // Liquid
	uint8_t  Liquid2_I2C_address;
	uint8_t  Liquid_I2C_Line;
	uint8_t  Vr_I2C_address; // VR
	uint8_t  Vr_I2C_Line;
	uint8_t  Plx_I2C_address; // PLX
	uint8_t  Plx_I2C_Line;
	uint16_t BoostPowerLimit;
	uint8_t  CKS_LDO_REFSEL;
	uint8_t  HotSpotOnly;
	uint8_t  Reserved0;
	uint16_t Reserved1;
};

enum atom_ppm:uint8_t {
	ATOM_PPM_A_A = 1,
	ATOM_PPM_A_I = 2,
};
struct atom_tonga_ppm_table {
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

struct atom_tonga_hard_limit_record {
	uint32_t SCLKLimit;
	uint32_t MCLKLimit;
	uint16_t VddcLimit;
	uint16_t VddciLimit;
	uint16_t VddgfxLimit;
};
struct atom_tonga_hard_limit_table {
	uint8_t  RevId;
	uint8_t  NumEntries;
	struct atom_tonga_hard_limit_record  entries[];
};

struct atom_tonga_gpio_table {
	uint8_t  RevId;
	uint8_t  VRHotTriggeredSclkDpmIndex; // If VRHot signal is triggered SCLK will be limited to this DPM level
	uint8_t  Reserve[5];
};

#pragma pack(pop)

#endif
