/*
 * Copyright 2018 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef SMU_11_0_PPTABLE_H
#define SMU_11_0_PPTABLE_H

#pragma pack(push, 1) // bios data must use byte alignment

#define SMU_11_0_TABLE_FORMAT_REVISION   12
#define SMU_11_0_7_TABLE_FORMAT_REVISION 15

// POWERPLAYTABLE::ulPlatformCaps
/*
#define SMU_11_0_PP_PLATFORM_CAP_POWERPLAY        0x1
#define SMU_11_0_PP_PLATFORM_CAP_SBIOSPOWERSOURCE 0x2
#define SMU_11_0_PP_PLATFORM_CAP_HARDWAREDC       0x4
#define SMU_11_0_PP_PLATFORM_CAP_BACO             0x8
#define SMU_11_0_PP_PLATFORM_CAP_MACO             0x10
#define SMU_11_0_PP_PLATFORM_CAP_SHADOWPSTATE     0x20
*/

// SMU_11_0_PP_THERMALCONTROLLER - Thermal Controller Type
#define SMU_11_0_PP_THERMALCONTROLLER_NONE  0
#define SMU_11_0_7_PP_THERMALCONTROLLER_SIENNA_CICHLID 28

//#define SMU_11_0_PP_OVERDRIVE_VERSION        0x0800
//#define SMU_11_0_PP_POWERSAVINGCLOCK_VERSION 0x0100
#define SMU_11_F12_OVERDRIVE_VERSION        0x80
#define SMU_11_F12_POWERSAVINGCLOCK_VERSION 0x01

#define SMU_11_0_7_PP_OVERDRIVE_VERSION        0x81 // OverDrive 8 Table Version 0.2
#define SMU_11_0_7_PP_POWERSAVINGCLOCK_VERSION 0x01 // Power Saving Clock Table Version 1.00

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

enum SMU_11_0_7_ODFEATURE_CAP {
	SMU_11_0_7_ODCAP_GFXCLK_LIMITS         = 0,
	SMU_11_0_7_ODCAP_GFXCLK_CURVE          = 1,
	SMU_11_0_7_ODCAP_UCLK_LIMITS           = 2,
	SMU_11_0_7_ODCAP_POWER_LIMIT           = 3,
	SMU_11_0_7_ODCAP_FAN_ACOUSTIC_LIMIT    = 4,
	SMU_11_0_7_ODCAP_FAN_SPEED_MIN         = 5,
	SMU_11_0_7_ODCAP_TEMPERATURE_FAN       = 6,
	SMU_11_0_7_ODCAP_TEMPERATURE_SYSTEM    = 7,
	SMU_11_0_7_ODCAP_MEMORY_TIMING_TUNE    = 8,
	SMU_11_0_7_ODCAP_FAN_ZERO_RPM_CONTROL  = 9,
	SMU_11_0_7_ODCAP_AUTO_UV_ENGINE        = 10,
	SMU_11_0_7_ODCAP_AUTO_OC_ENGINE        = 11,
	SMU_11_0_7_ODCAP_AUTO_OC_MEMORY        = 12,
	SMU_11_0_7_ODCAP_FAN_CURVE             = 13,
	SMU_11_0_ODCAP_AUTO_FAN_ACOUSTIC_LIMIT = 14,
	SMU_11_0_7_ODCAP_POWER_MODE            = 15,
	SMU_11_0_7_ODCAP_COUNT                 = 16,
};
#define SMU_11_0_7_MAX_ODFEATURE 32 // Maximum Number of OD Features


/*
// 14 bits; when does this get used?
enum SMU_11_0_ODFEATURE_ID { // this isn't a necessary way to do it, AMD. Wasteful.
	SMU_11_0_ODFEATURE_GFXCLK_LIMITS        = 1 << SMU_11_0_ODCAP_GFXCLK_LIMITS,        // GFXCLK Limit feature
	SMU_11_0_ODFEATURE_GFXCLK_CURVE         = 1 << SMU_11_0_ODCAP_GFXCLK_CURVE,         // GFXCLK Curve feature
	SMU_11_0_ODFEATURE_UCLK_MAX             = 1 << SMU_11_0_ODCAP_UCLK_MAX,             // UCLK Limit feature
	SMU_11_0_ODFEATURE_POWER_LIMIT          = 1 << SMU_11_0_ODCAP_POWER_LIMIT,          // Power Limit feature
	SMU_11_0_ODFEATURE_FAN_ACOUSTIC_LIMIT   = 1 << SMU_11_0_ODCAP_FAN_ACOUSTIC_LIMIT,   // Fan Acoustic RPM feature
	SMU_11_0_ODFEATURE_FAN_SPEED_MIN        = 1 << SMU_11_0_ODCAP_FAN_SPEED_MIN,        // Minimum Fan Speed feature
	SMU_11_0_ODFEATURE_TEMPERATURE_FAN      = 1 << SMU_11_0_ODCAP_TEMPERATURE_FAN,      // Fan Target Temperature Limit feature
	SMU_11_0_ODFEATURE_TEMPERATURE_SYSTEM   = 1 << SMU_11_0_ODCAP_TEMPERATURE_SYSTEM,   // Operating Temperature Limit feature
	SMU_11_0_ODFEATURE_MEMORY_TIMING_TUNE   = 1 << SMU_11_0_ODCAP_MEMORY_TIMING_TUNE,   // AC Timing Tuning feature
	SMU_11_0_ODFEATURE_FAN_ZERO_RPM_CONTROL = 1 << SMU_11_0_ODCAP_FAN_ZERO_RPM_CONTROL, // Zero RPM feature
	SMU_11_0_ODFEATURE_AUTO_UV_ENGINE       = 1 << SMU_11_0_ODCAP_AUTO_UV_ENGINE,       // Auto Under Volt GFXCLK feature
	SMU_11_0_ODFEATURE_AUTO_OC_ENGINE       = 1 << SMU_11_0_ODCAP_AUTO_OC_ENGINE,       // Auto Over Clock GFXCLK feature
	SMU_11_0_ODFEATURE_AUTO_OC_MEMORY       = 1 << SMU_11_0_ODCAP_AUTO_OC_MEMORY,       // Auto Over Clock MCLK feature
	SMU_11_0_ODFEATURE_FAN_CURVE            = 1 << SMU_11_0_ODCAP_FAN_CURVE,            // Fan Curve feature
	SMU_11_0_ODFEATURE_COUNT                = 14,
};
*/

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
#define SMU_11_0_MAX_ODSETTING    32          // Maximum Number of ODSettings

enum SMU_11_0_7_ODSETTING_ID {
	SMU_11_0_7_ODSETTING_GFXCLKFMAX              = 0,
	SMU_11_0_7_ODSETTING_GFXCLKFMIN              = 1,
	SMU_11_0_7_ODSETTING_CUSTOM_GFX_VF_CURVE_A   = 2,
	SMU_11_0_7_ODSETTING_CUSTOM_GFX_VF_CURVE_B   = 3,
	SMU_11_0_7_ODSETTING_CUSTOM_GFX_VF_CURVE_C   = 4,
	SMU_11_0_7_ODSETTING_CUSTOM_CURVE_VFT_FMIN   = 5,
	SMU_11_0_7_ODSETTING_UCLKFMIN                = 6,
	SMU_11_0_7_ODSETTING_UCLKFMAX                = 7,
	SMU_11_0_7_ODSETTING_POWERPERCENTAGE         = 8,
	SMU_11_0_7_ODSETTING_FANRPMMIN               = 9,
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
	SMU_11_0_7_PMSETTING_POWER_LIMIT_QUIET           = 0,
	SMU_11_0_7_PMSETTING_POWER_LIMIT_BALANCE         = 1,
	SMU_11_0_7_PMSETTING_POWER_LIMIT_TURBO           = 2,
	SMU_11_0_7_PMSETTING_POWER_LIMIT_RAGE            = 3,
	SMU_11_0_7_PMSETTING_ACOUSTIC_TEMP_QUIET         = 4,
	SMU_11_0_7_PMSETTING_ACOUSTIC_TEMP_BALANCE       = 5,
	SMU_11_0_7_PMSETTING_ACOUSTIC_TEMP_TURBO         = 6,
	SMU_11_0_7_PMSETTING_ACOUSTIC_TEMP_RAGE          = 7,
	SMU_11_0_7_PMSETTING_ACOUSTIC_TARGET_RPM_QUIET   = 8,
	SMU_11_0_7_PMSETTING_ACOUSTIC_TARGET_RPM_BALANCE = 9,
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
	SMU_11_0_7_PPCLOCK_PIXCLK  = 10,
	SMU_11_0_7_PPCLOCK_PHYCLK  = 11,
	SMU_11_0_7_PPCLOCK_DTBCLK  = 12,
	SMU_11_0_7_PPCLOCK_COUNT   = 13,
};
#define SMU_11_0_7_MAX_PPCLOCK 16 // Maximum Number of PP Clocks


struct smu_11_0_power_saving_clock_table {
	uint8_t  revision;   // Revision = SMU_11_0_PP_POWERSAVINGCLOCK_VERSION
	uint8_t  reserve[3]; // Zero filled field reserved for future use
	uint32_t count;      // power_saving_clock_count = SMU_11_0_PPCLOCK_COUNT
	uint32_t max[SMU_11_0_MAX_PPCLOCK]; // PowerSavingClock Mode Clock Maximum array In MHz
	uint32_t min[SMU_11_0_MAX_PPCLOCK]; // PowerSavingClock Mode Clock Minimum array In MHz
};
struct smu_11_0_7_power_saving_clock_table {
	uint8_t  revision;   // Revision = SMU_11_0_7_PP_POWERSAVINGCLOCK_VERSION
	uint8_t  reserve[3]; // Zero filled field reserved for future use
	uint32_t count;      // power_saving_clock_count = SMU_11_0_7_PPCLOCK_COUNT
	uint32_t max[SMU_11_0_7_MAX_PPCLOCK]; // PowerSavingClock Mode Clock Maximum array In MHz
	uint32_t min[SMU_11_0_7_MAX_PPCLOCK]; // PowerSavingClock Mode Clock Minimum array In MHz
};



union smu11_smc_pptables {
	uint32_t smc_pptable_ver;
	struct smu11_smcpptable_v3 v3;
	struct smu11_smcpptable_v8 v8;
	struct smu11_smcpptable_v7 v7;
};

struct smu_11_0_powerplay_table {
	struct smu_powerplay_table_header header;
	uint32_t golden_pp_id;
	uint32_t golden_revision;
	uint16_t format_id;
	union powerplay_platform_caps platform_caps;

	uint8_t  thermal_controller_type; // one of SMU_11_0_PP_THERMALCONTROLLER

	uint16_t small_power_limit1;
	uint16_t small_power_limit2;
	uint16_t boost_power_limit;
	uint16_t od_turbo_power_limit;      // Power limit setting for Turbo mode in Performance UI Tuning.
	uint16_t od_power_save_power_limit; // Power limit setting for PowerSave/Optimal mode in Performance UI Tuning.
	uint16_t software_shutdown_temp;

	uint16_t reserve[6]; // Zero filled field reserved for future use

	struct smu_11_0_power_saving_clock_table power_saving_clock;
	struct smu_11_0_overdrive_table overdrive_table;

	union smu11_smc_pptables smc_pptable; // PPTable_t in the driver_if.h
};

struct smu_11_0_7_powerplay_table {
	struct smu_powerplay_table_header header;
	uint32_t golden_pp_id;    // PPGen use only: PP Table ID on the Golden Data Base
	uint32_t golden_revision; // PPGen use only: PP Table Revision on the Golden Data Base
	uint16_t format_id;       // PPGen use only: PPTable for different ASICs. For sienna_cichlid this should be 0x80
	union powerplay_platform_caps platform_caps; // POWERPLAYABLE::ulPlatformCaps
	uint8_t  thermal_controller_type; // one of SMU_11_0_7_PP_THERMALCONTROLLER

	uint16_t small_power_limit1;
	uint16_t small_power_limit2;
	uint16_t boost_power_limit; // For Gemini Board, when the slave adapter is in BACO mode, the master adapter will use this boost power limit instead of the default power limit to boost the power limit.
	uint16_t software_shutdown_temp;

	uint16_t reserve[8]; // Zero filled field reserved for future use

	struct smu_11_0_7_power_saving_clock_table power_saving_clock;
	struct smu_11_0_7_overdrive_table overdrive_table;

	union smu11_smc_pptables smc_pptable; // PPTable_t in smu11_driver_if.h
};


#pragma pack(pop) // restore old packing

#endif
