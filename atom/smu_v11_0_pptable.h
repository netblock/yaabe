#ifndef SMU_11_0_PPTABLE_H
#define SMU_11_0_PPTABLE_H
#pragma pack(push, 1) // bios data must use byte alignment

#define ATOM_VEGA20_TABLE_REVISION_VEGA20 11
#define SMU_11_0_TABLE_FORMAT_REVISION    12
#define SMU_11_0_7_TABLE_FORMAT_REVISION  15


#define SMU_11_F12_POWERSAVINGCLOCK_VERSION    0x01
#define SMU_11_0_7_PP_POWERSAVINGCLOCK_VERSION 0x01 // Power Saving Clock Table Version 1.00

#define SMU_11_F12_OVERDRIVE_VERSION    0x80
#define SMU_11_0_7_PP_OVERDRIVE_VERSION 0x81 // OverDrive 8 Table Version 0.2

enum SMU_11_0_ODFEATURE_CAP {
	SMU_11_0_ODCAP_GFXCLK_LIMITS        = 0,
	SMU_11_0_ODCAP_GFXCLK_CURVE         = 1,
	SMU_11_0_ODCAP_UCLK_MAX             = 2,
	SMU_11_0_ODCAP_POWER_LIMIT          = 3,
	SMU_11_0_ODCAP_FAN_ACOUSTIC_LIMIT   = 4,
	SMU_11_0_ODCAP_FAN_SPEED_MIN        = 5,
	SMU_11_0_ODCAP_TEMPERATURE_FAN      = 6,
	SMU_11_0_ODCAP_TEMPERATURE_SYSTEM   = 7,
	SMU_11_0_ODCAP_MEMORY_TIMING_TUNE   = 8,
	SMU_11_0_ODCAP_FAN_ZERO_RPM_CONTROL = 9,
	SMU_11_0_ODCAP_AUTO_UV_ENGINE      = 10,
	SMU_11_0_ODCAP_AUTO_OC_ENGINE      = 11,
	SMU_11_0_ODCAP_AUTO_OC_MEMORY      = 12,
	SMU_11_0_ODCAP_FAN_CURVE           = 13,
	SMU_11_0_ODCAP_COUNT               = 14,
};
#define SMU_11_0_MAX_ODFEATURE 32 // Maximum Number of OD Features

enum ATOM_VEGA20_ODFEATURE_ID {
	ATOM_VEGA20_ODFEATURE_GFXCLK_LIMITS        = 0,
	ATOM_VEGA20_ODFEATURE_GFXCLK_CURVE         = 1,
	ATOM_VEGA20_ODFEATURE_UCLK_MAX             = 2,
	ATOM_VEGA20_ODFEATURE_POWER_LIMIT          = 3,
	ATOM_VEGA20_ODFEATURE_FAN_ACOUSTIC_LIMIT   = 4,
	ATOM_VEGA20_ODFEATURE_FAN_SPEED_MIN        = 5,
	ATOM_VEGA20_ODFEATURE_TEMPERATURE_FAN      = 6,
	ATOM_VEGA20_ODFEATURE_TEMPERATURE_SYSTEM   = 7,
	ATOM_VEGA20_ODFEATURE_MEMORY_TIMING_TUNE   = 8,
	ATOM_VEGA20_ODFEATURE_FAN_ZERO_RPM_CONTROL = 9,
	ATOM_VEGA20_ODFEATURE_COUNT               = 10,
};
#define ATOM_VEGA20_ODFEATURE_MAX_COUNT 32

enum SMU_11_0_7_ODFEATURE_CAP {
	SMU_11_0_7_ODCAP_GFXCLK_LIMITS          = 0,
	SMU_11_0_7_ODCAP_GFXCLK_CURVE           = 1,
	SMU_11_0_7_ODCAP_UCLK_LIMITS            = 2,
	SMU_11_0_7_ODCAP_POWER_LIMIT            = 3,
	SMU_11_0_7_ODCAP_FAN_ACOUSTIC_LIMIT     = 4,
	SMU_11_0_7_ODCAP_FAN_SPEED_MIN          = 5,
	SMU_11_0_7_ODCAP_TEMPERATURE_FAN        = 6,
	SMU_11_0_7_ODCAP_TEMPERATURE_SYSTEM     = 7,
	SMU_11_0_7_ODCAP_MEMORY_TIMING_TUNE     = 8,
	SMU_11_0_7_ODCAP_FAN_ZERO_RPM_CONTROL   = 9,
	SMU_11_0_7_ODCAP_AUTO_UV_ENGINE        = 10,
	SMU_11_0_7_ODCAP_AUTO_OC_ENGINE        = 11,
	SMU_11_0_7_ODCAP_AUTO_OC_MEMORY        = 12,
	SMU_11_0_7_ODCAP_FAN_CURVE             = 13,
	SMU_11_0_ODCAP_AUTO_FAN_ACOUSTIC_LIMIT = 14,
	SMU_11_0_7_ODCAP_POWER_MODE            = 15,
	SMU_11_0_7_ODCAP_COUNT                 = 16,
};
#define SMU_11_0_7_MAX_ODFEATURE 32 // Maximum Number of OD Features



enum SMU_11_0_ODSETTING_ID { // index into array
	SMU_11_0_ODSETTING_GFXCLKFMAX            = 0,
	SMU_11_0_ODSETTING_GFXCLKFMIN            = 1,
	SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P1    = 2,
	SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P1 = 3,
	SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P2    = 4,
	SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P2 = 5,
	SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P3    = 6,
	SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P3 = 7,
	SMU_11_0_ODSETTING_UCLKFMAX              = 8,
	SMU_11_0_ODSETTING_POWERPERCENTAGE       = 9,
	SMU_11_0_ODSETTING_FANRPMMIN            = 10,
	SMU_11_0_ODSETTING_FANRPMACOUSTICLIMIT  = 11,
	SMU_11_0_ODSETTING_FANTARGETTEMPERATURE = 12,
	SMU_11_0_ODSETTING_OPERATINGTEMPMAX     = 13,
	SMU_11_0_ODSETTING_ACTIMING             = 14,
	SMU_11_0_ODSETTING_FAN_ZERO_RPM_CONTROL = 15,
	SMU_11_0_ODSETTING_AUTOUVENGINE         = 16,
	SMU_11_0_ODSETTING_AUTOOCENGINE         = 17,
	SMU_11_0_ODSETTING_AUTOOCMEMORY         = 18,
	SMU_11_0_ODSETTING_COUNT                = 19,
};
#define SMU_11_0_MAX_ODSETTING 32 // Maximum Number of ODSettings

enum ATOM_VEGA20_ODSETTING_ID {
	ATOM_VEGA20_ODSETTING_GFXCLKFMAX                  = 0,
	ATOM_VEGA20_ODSETTING_GFXCLKFMIN                  = 1,
	ATOM_VEGA20_ODSETTING_VDDGFXCURVEFREQ_P1          = 2,
	ATOM_VEGA20_ODSETTING_VDDGFXCURVEVOLTAGEOFFSET_P1 = 3,
	ATOM_VEGA20_ODSETTING_VDDGFXCURVEFREQ_P2          = 4,
	ATOM_VEGA20_ODSETTING_VDDGFXCURVEVOLTAGEOFFSET_P2 = 5,
	ATOM_VEGA20_ODSETTING_VDDGFXCURVEFREQ_P3          = 6,
	ATOM_VEGA20_ODSETTING_VDDGFXCURVEVOLTAGEOFFSET_P3 = 7,
	ATOM_VEGA20_ODSETTING_UCLKFMAX                    = 8,
	ATOM_VEGA20_ODSETTING_POWERPERCENTAGE             = 9,
	ATOM_VEGA20_ODSETTING_FANRPMMIN                  = 10,
	ATOM_VEGA20_ODSETTING_FANRPMACOUSTICLIMIT        = 11,
	ATOM_VEGA20_ODSETTING_FANTARGETTEMPERATURE       = 12,
	ATOM_VEGA20_ODSETTING_OPERATINGTEMPMAX           = 13,
	ATOM_VEGA20_ODSETTING_COUNT                      = 14,
};
#define ATOM_VEGA20_ODSETTING_MAX_COUNT 32

enum SMU_11_0_7_ODSETTING_ID {
	SMU_11_0_7_ODSETTING_GFXCLKFMAX               = 0,
	SMU_11_0_7_ODSETTING_GFXCLKFMIN               = 1,
	SMU_11_0_7_ODSETTING_CUSTOM_GFX_VF_CURVE_A    = 2,
	SMU_11_0_7_ODSETTING_CUSTOM_GFX_VF_CURVE_B    = 3,
	SMU_11_0_7_ODSETTING_CUSTOM_GFX_VF_CURVE_C    = 4,
	SMU_11_0_7_ODSETTING_CUSTOM_CURVE_VFT_FMIN    = 5,
	SMU_11_0_7_ODSETTING_UCLKFMIN                 = 6,
	SMU_11_0_7_ODSETTING_UCLKFMAX                 = 7,
	SMU_11_0_7_ODSETTING_POWERPERCENTAGE          = 8,
	SMU_11_0_7_ODSETTING_FANRPMMIN                = 9,
	SMU_11_0_7_ODSETTING_FANRPMACOUSTICLIMIT     = 10,
	SMU_11_0_7_ODSETTING_FANTARGETTEMPERATURE    = 11,
	SMU_11_0_7_ODSETTING_OPERATINGTEMPMAX        = 12,
	SMU_11_0_7_ODSETTING_ACTIMING                = 13,
	SMU_11_0_7_ODSETTING_FAN_ZERO_RPM_CONTROL    = 14,
	SMU_11_0_7_ODSETTING_AUTOUVENGINE            = 15,
	SMU_11_0_7_ODSETTING_AUTOOCENGINE            = 16,
	SMU_11_0_7_ODSETTING_AUTOOCMEMORY            = 17,
	SMU_11_0_7_ODSETTING_FAN_CURVE_TEMPERATURE_1 = 18,
	SMU_11_0_7_ODSETTING_FAN_CURVE_SPEED_1       = 19,
	SMU_11_0_7_ODSETTING_FAN_CURVE_TEMPERATURE_2 = 20,
	SMU_11_0_7_ODSETTING_FAN_CURVE_SPEED_2       = 21,
	SMU_11_0_7_ODSETTING_FAN_CURVE_TEMPERATURE_3 = 22,
	SMU_11_0_7_ODSETTING_FAN_CURVE_SPEED_3       = 23,
	SMU_11_0_7_ODSETTING_FAN_CURVE_TEMPERATURE_4 = 24,
	SMU_11_0_7_ODSETTING_FAN_CURVE_SPEED_4       = 25,
	SMU_11_0_7_ODSETTING_FAN_CURVE_TEMPERATURE_5 = 26,
	SMU_11_0_7_ODSETTING_FAN_CURVE_SPEED_5       = 27,
	SMU_11_0_7_ODSETTING_AUTO_FAN_ACOUSTIC_LIMIT = 28,
	SMU_11_0_7_ODSETTING_POWER_MODE              = 29,
	SMU_11_0_7_ODSETTING_COUNT                   = 30,
};
#define SMU_11_0_7_MAX_ODSETTING 64 // Maximum Number of ODSettings

enum SMU_11_0_7_PWRMODE_SETTING {
	SMU_11_0_7_PMSETTING_POWER_LIMIT_QUIET            = 0,
	SMU_11_0_7_PMSETTING_POWER_LIMIT_BALANCE          = 1,
	SMU_11_0_7_PMSETTING_POWER_LIMIT_TURBO            = 2,
	SMU_11_0_7_PMSETTING_POWER_LIMIT_RAGE             = 3,
	SMU_11_0_7_PMSETTING_ACOUSTIC_TEMP_QUIET          = 4,
	SMU_11_0_7_PMSETTING_ACOUSTIC_TEMP_BALANCE        = 5,
	SMU_11_0_7_PMSETTING_ACOUSTIC_TEMP_TURBO          = 6,
	SMU_11_0_7_PMSETTING_ACOUSTIC_TEMP_RAGE           = 7,
	SMU_11_0_7_PMSETTING_ACOUSTIC_TARGET_RPM_QUIET    = 8,
	SMU_11_0_7_PMSETTING_ACOUSTIC_TARGET_RPM_BALANCE  = 9,
	SMU_11_0_7_PMSETTING_ACOUSTIC_TARGET_RPM_TURBO   = 10,
	SMU_11_0_7_PMSETTING_ACOUSTIC_TARGET_RPM_RAGE    = 11,
	SMU_11_0_7_PMSETTING_ACOUSTIC_LIMIT_RPM_QUIET    = 12,
	SMU_11_0_7_PMSETTING_ACOUSTIC_LIMIT_RPM_BALANCE  = 13,
	SMU_11_0_7_PMSETTING_ACOUSTIC_LIMIT_RPM_TURBO    = 14,
	SMU_11_0_7_PMSETTING_ACOUSTIC_LIMIT_RPM_RAGE     = 15,
	SMU_11_0_7_PMSETTING_COUNT                       = 16,
};
#define SMU_11_0_7_MAX_PMSETTING 32 // Maximum Number of PowerMode Settings

struct smu_11_0_overdrive_table {
	uint8_t  revision;      // Revision = SMU_11_0_PP_OVERDRIVE_VERSION
	uint8_t  reserve[3];    // Zero filled field reserved for future use
	uint32_t feature_count; // Total number of supported features
	uint32_t setting_count; // Total number of supported settings
	uint8_t  cap[SMU_11_0_MAX_ODFEATURE]; // OD feature support flags
	uint32_t max[SMU_11_0_MAX_ODSETTING]; // default maximum settings
	uint32_t min[SMU_11_0_MAX_ODSETTING]; // default minimum settings
};
struct atom_vega20_overdrive8_record {
	uint8_t  ODTableRevision;
	uint32_t ODFeatureCount;
	uint8_t  ODFeatureCapabilities[ATOM_VEGA20_ODFEATURE_MAX_COUNT]; // OD feature support flags
	uint32_t ODSettingCount;
	uint32_t ODSettingsMax[ATOM_VEGA20_ODSETTING_MAX_COUNT]; // Upper Limit for each OD Setting
	uint32_t ODSettingsMin[ATOM_VEGA20_ODSETTING_MAX_COUNT]; // Lower Limit for each OD Setting
};
struct smu_11_0_7_overdrive_table {
	uint8_t  revision;      // Revision = SMU_11_0_7_PP_OVERDRIVE_VERSION
	uint8_t  reserve[3];    // Zero filled field reserved for future use
	uint32_t feature_count; // Total number of supported features
	uint32_t setting_count; // Total number of supported settings
	uint8_t  cap[SMU_11_0_7_MAX_ODFEATURE]; // OD feature support flags
	uint32_t max[SMU_11_0_7_MAX_ODSETTING]; // default maximum settings
	uint32_t min[SMU_11_0_7_MAX_ODSETTING]; // default minimum settings
	int16_t  pm_setting[SMU_11_0_7_MAX_PMSETTING]; // Optimized power mode feature settings
};

enum SMU_11_0_PPCLOCK_ID {
	SMU_11_0_PPCLOCK_GFXCLK  = 0,
	SMU_11_0_PPCLOCK_VCLK    = 1,
	SMU_11_0_PPCLOCK_DCLK    = 2,
	SMU_11_0_PPCLOCK_ECLK    = 3,
	SMU_11_0_PPCLOCK_SOCCLK  = 4,
	SMU_11_0_PPCLOCK_UCLK    = 5,
	SMU_11_0_PPCLOCK_DCEFCLK = 6,
	SMU_11_0_PPCLOCK_DISPCLK = 7,
	SMU_11_0_PPCLOCK_PIXCLK  = 8,
	SMU_11_0_PPCLOCK_PHYCLK  = 9,
	SMU_11_0_PPCLOCK_COUNT  = 10,
};
#define SMU_11_0_MAX_PPCLOCK 16 // Maximum Number of PP Clocks
enum ATOM_VEGA20_PPCLOCK_ID {
	ATOM_VEGA20_PPCLOCK_GFXCLK  = 0,
	ATOM_VEGA20_PPCLOCK_VCLK    = 1,
	ATOM_VEGA20_PPCLOCK_DCLK    = 2,
	ATOM_VEGA20_PPCLOCK_ECLK    = 3,
	ATOM_VEGA20_PPCLOCK_SOCCLK  = 4,
	ATOM_VEGA20_PPCLOCK_UCLK    = 5,
	ATOM_VEGA20_PPCLOCK_FCLK    = 6,
	ATOM_VEGA20_PPCLOCK_DCEFCLK = 7,
	ATOM_VEGA20_PPCLOCK_DISPCLK = 8,
	ATOM_VEGA20_PPCLOCK_PIXCLK  = 9,
	ATOM_VEGA20_PPCLOCK_PHYCLK = 10,
	ATOM_VEGA20_PPCLOCK_COUNT  = 11,
};
#define ATOM_VEGA20_PPCLOCK_MAX_COUNT 16
enum SMU_11_0_7_PPCLOCK_ID {
	SMU_11_0_7_PPCLOCK_GFXCLK  = 0,
	SMU_11_0_7_PPCLOCK_SOCCLK  = 1,
	SMU_11_0_7_PPCLOCK_UCLK    = 2,
	SMU_11_0_7_PPCLOCK_FCLK    = 3,
	SMU_11_0_7_PPCLOCK_DCLK_0  = 4,
	SMU_11_0_7_PPCLOCK_VCLK_0  = 5,
	SMU_11_0_7_PPCLOCK_DCLK_1  = 6,
	SMU_11_0_7_PPCLOCK_VCLK_1  = 7,
	SMU_11_0_7_PPCLOCK_DCEFCLK = 8,
	SMU_11_0_7_PPCLOCK_DISPCLK = 9,
	SMU_11_0_7_PPCLOCK_PIXCLK = 10,
	SMU_11_0_7_PPCLOCK_PHYCLK = 11,
	SMU_11_0_7_PPCLOCK_DTBCLK = 12,
	SMU_11_0_7_PPCLOCK_COUNT  = 13,
};
#define SMU_11_0_7_MAX_PPCLOCK 16 // Maximum Number of PP Clocks


struct smu_11_0_power_saving_clock_table {
	uint8_t  revision;   // Revision = SMU_11_0_PP_POWERSAVINGCLOCK_VERSION
	uint8_t  reserve[3]; // Zero filled field reserved for future use
	uint32_t count;      // power_saving_clock_count = SMU_11_0_PPCLOCK_COUNT
	uint32_t max[SMU_11_0_MAX_PPCLOCK]; // PowerSavingClock Mode Clock Maximum array In MHz
	uint32_t min[SMU_11_0_MAX_PPCLOCK]; // PowerSavingClock Mode Clock Minimum array In MHz
};
struct atom_vega20_power_saving_clock_record {
	uint8_t TableRevision;
	uint32_t PowerSavingClockCount; // Count of PowerSavingClock Mode
	uint32_t PowerSavingClockMax[ATOM_VEGA20_PPCLOCK_MAX_COUNT]; // PowerSavingClock Mode Clock Maximum array In MHz
	uint32_t PowerSavingClockMin[ATOM_VEGA20_PPCLOCK_MAX_COUNT]; // PowerSavingClock Mode Clock Minimum array In MHz
};
struct smu_11_0_7_power_saving_clock_table {
	uint8_t  revision;   // Revision = SMU_11_0_7_PP_POWERSAVINGCLOCK_VERSION
	uint8_t  reserve[3]; // Zero filled field reserved for future use
	uint32_t count;      // power_saving_clock_count = SMU_11_0_7_PPCLOCK_COUNT
	uint32_t max[SMU_11_0_7_MAX_PPCLOCK]; // PowerSavingClock Mode Clock Maximum array In MHz
	uint32_t min[SMU_11_0_7_MAX_PPCLOCK]; // PowerSavingClock Mode Clock Minimum array In MHz
};



union smu11_smc_pptables {
	uint32_t ver;
	struct smu11_smcpptable_v3  v3;
	struct smu11_smcpptable_v8  v8;
	struct smu11_smcpptable_v7  v7;
};

struct smu_11_0_powerplay_table {
	struct smu_powerplay_table_header  header;
	union powerplay_platform_caps  platform_caps;

	enum ATOM_PP_THERMALCONTROLLER  thermal_controller_type;

	uint16_t small_power_limit1;
	uint16_t small_power_limit2;
	uint16_t boost_power_limit;
	uint16_t od_turbo_power_limit;      // Power limit setting for Turbo mode in Performance UI Tuning.
	uint16_t od_power_save_power_limit; // Power limit setting for PowerSave/Optimal mode in Performance UI Tuning.
	uint16_t software_shutdown_temp;

	uint16_t reserve[6]; // Zero filled field reserved for future use

	struct smu_11_0_power_saving_clock_table  power_saving_clock;
	struct smu_11_0_overdrive_table  overdrive_table;

	union smu11_smc_pptables  smc_pptable; // PPTable_t in the driver_if.h
};

struct atom_vega20_powerplay_table {
	struct smu_powerplay_table_header header;

	union powerplay_platform_caps  platform_caps;

	enum ATOM_PP_THERMALCONTROLLER  ThermalControllerType;

	uint16_t SmallPowerLimit1;
	uint16_t SmallPowerLimit2;
	uint16_t BoostPowerLimit;
	uint16_t ODTurboPowerLimit;
	uint16_t ODPowerSavePowerLimit;
	uint16_t SoftwareShutdownTemp;

	struct atom_vega20_power_saving_clock_record PowerSavingClockTable; //PowerSavingClock Mode Clock Min/Max array

	struct atom_vega20_overdrive8_record OverDrive8Table; // OverDrive8 Feature capabilities and Settings Range (Max and Min)

	uint16_t Reserve[5];

	union smu11_smc_pptables  smc_pptable; // PPTable_t in the driver_if.h
};

struct smu_11_0_7_powerplay_table {
	struct smu_powerplay_table_header  header;
	union powerplay_platform_caps  platform_caps; // POWERPLAYABLE::ulPlatformCaps
	enum ATOM_PP_THERMALCONTROLLER  thermal_controller_type;

	uint16_t small_power_limit1;
	uint16_t small_power_limit2;
	uint16_t boost_power_limit; // For Gemini Board, when the slave adapter is in BACO mode, the master adapter will use this boost power limit instead of the default power limit to boost the power limit.
	uint16_t software_shutdown_temp;

	uint16_t reserve[8]; // Zero filled field reserved for future use

	struct smu_11_0_7_power_saving_clock_table  power_saving_clock;
	struct smu_11_0_7_overdrive_table  overdrive_table;

	union smu11_smc_pptables  smc_pptable; // PPTable_t in smu11_driver_if.h
};


#pragma pack(pop) // restore old packing
#endif
