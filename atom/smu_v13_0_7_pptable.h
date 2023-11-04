/*
 * Copyright 2022 Advanced Micro Devices, Inc.
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
#ifndef SMU_13_0_7_PPTABLE_H
#define SMU_13_0_7_PPTABLE_H

#pragma pack(push, 1)

#define SMU_13_0_7_TABLE_FORMAT_REVISION 15

// POWERPLAYTABLE::ulPlatformCaps
#define SMU_13_0_7_PP_PLATFORM_CAP_POWERPLAY 0x1        // This cap indicates whether CCC need to show Powerplay page.
#define SMU_13_0_7_PP_PLATFORM_CAP_SBIOSPOWERSOURCE 0x2 // This cap indicates whether power source notificaiton is done by SBIOS instead of OS.
#define SMU_13_0_7_PP_PLATFORM_CAP_HARDWAREDC 0x4       // This cap indicates whether DC mode notificaiton is done by GPIO pin directly.
#define SMU_13_0_7_PP_PLATFORM_CAP_BACO 0x8             // This cap indicates whether board supports the BACO circuitry.
#define SMU_13_0_7_PP_PLATFORM_CAP_MACO 0x10            // This cap indicates whether board supports the MACO circuitry.
#define SMU_13_0_7_PP_PLATFORM_CAP_SHADOWPSTATE 0x20    // This cap indicates whether board supports the Shadow Pstate.

// SMU_13_0_7_PP_THERMALCONTROLLER - Thermal Controller Type
#define SMU_13_0_7_PP_THERMALCONTROLLER_NONE 0
#define SMU_13_0_7_PP_THERMALCONTROLLER_NAVI21 28

#define SMU_13_0_7_PP_OVERDRIVE_VERSION 0x83        // OverDrive 8 Table Version 0.2
#define SMU_13_0_7_PP_POWERSAVINGCLOCK_VERSION 0x01 // Power Saving Clock Table Version 1.00

enum SMU_13_0_7_ODFEATURE_CAP {
    SMU_13_0_7_ODCAP_GFXCLK_LIMITS           = 0,
    SMU_13_0_7_ODCAP_UCLK_LIMITS             = 1,
    SMU_13_0_7_ODCAP_POWER_LIMIT             = 2,
    SMU_13_0_7_ODCAP_FAN_ACOUSTIC_LIMIT      = 3,
    SMU_13_0_7_ODCAP_FAN_SPEED_MIN           = 4,
    SMU_13_0_7_ODCAP_TEMPERATURE_FAN         = 5,
    SMU_13_0_7_ODCAP_TEMPERATURE_SYSTEM      = 6,
    SMU_13_0_7_ODCAP_MEMORY_TIMING_TUNE      = 7,
    SMU_13_0_7_ODCAP_FAN_ZERO_RPM_CONTROL    = 8,
    SMU_13_0_7_ODCAP_AUTO_UV_ENGINE          = 9,
    SMU_13_0_7_ODCAP_AUTO_OC_ENGINE          = 10,
    SMU_13_0_7_ODCAP_AUTO_OC_MEMORY          = 11,
    SMU_13_0_7_ODCAP_FAN_CURVE               = 12,
    SMU_13_0_7_ODCAP_AUTO_FAN_ACOUSTIC_LIMIT = 13,
    SMU_13_0_7_ODCAP_POWER_MODE              = 14,
    SMU_13_0_7_ODCAP_PER_ZONE_GFX_VOLTAGE_OFFSET = 15,
    SMU_13_0_7_ODCAP_COUNT = 16,
};

enum SMU_13_0_7_ODFEATURE_ID {
    SMU_13_0_7_ODFEATURE_GFXCLK_LIMITS           = 1 << SMU_13_0_7_ODCAP_GFXCLK_LIMITS,           // GFXCLK Limit feature
    SMU_13_0_7_ODFEATURE_UCLK_LIMITS             = 1 << SMU_13_0_7_ODCAP_UCLK_LIMITS,             // UCLK Limit feature
    SMU_13_0_7_ODFEATURE_POWER_LIMIT             = 1 << SMU_13_0_7_ODCAP_POWER_LIMIT,             // Power Limit feature
    SMU_13_0_7_ODFEATURE_FAN_ACOUSTIC_LIMIT      = 1 << SMU_13_0_7_ODCAP_FAN_ACOUSTIC_LIMIT,      // Fan Acoustic RPM feature
    SMU_13_0_7_ODFEATURE_FAN_SPEED_MIN           = 1 << SMU_13_0_7_ODCAP_FAN_SPEED_MIN,           // Minimum Fan Speed feature
    SMU_13_0_7_ODFEATURE_TEMPERATURE_FAN         = 1 << SMU_13_0_7_ODCAP_TEMPERATURE_FAN,         // Fan Target Temperature Limit feature
    SMU_13_0_7_ODFEATURE_TEMPERATURE_SYSTEM      = 1 << SMU_13_0_7_ODCAP_TEMPERATURE_SYSTEM,      // Operating Temperature Limit feature
    SMU_13_0_7_ODFEATURE_MEMORY_TIMING_TUNE      = 1 << SMU_13_0_7_ODCAP_MEMORY_TIMING_TUNE,      // AC Timing Tuning feature
    SMU_13_0_7_ODFEATURE_FAN_ZERO_RPM_CONTROL    = 1 << SMU_13_0_7_ODCAP_FAN_ZERO_RPM_CONTROL,    // Zero RPM feature
    SMU_13_0_7_ODFEATURE_AUTO_UV_ENGINE          = 1 << SMU_13_0_7_ODCAP_AUTO_UV_ENGINE,          // Auto Under Volt GFXCLK feature
    SMU_13_0_7_ODFEATURE_AUTO_OC_ENGINE          = 1 << SMU_13_0_7_ODCAP_AUTO_OC_ENGINE,          // Auto Over Clock GFXCLK feature
    SMU_13_0_7_ODFEATURE_AUTO_OC_MEMORY          = 1 << SMU_13_0_7_ODCAP_AUTO_OC_MEMORY,          // Auto Over Clock MCLK feature
    SMU_13_0_7_ODFEATURE_FAN_CURVE               = 1 << SMU_13_0_7_ODCAP_FAN_CURVE,               // Fan Curve feature
    SMU_13_0_7_ODFEATURE_AUTO_FAN_ACOUSTIC_LIMIT = 1 << SMU_13_0_7_ODCAP_AUTO_FAN_ACOUSTIC_LIMIT, // Auto Fan Acoustic RPM feature
    SMU_13_0_7_ODFEATURE_POWER_MODE              = 1 << SMU_13_0_7_ODCAP_POWER_MODE,              // Optimized GPU Power Mode feature
    SMU_13_0_7_ODFEATURE_PER_ZONE_GFX_VOLTAGE_OFFSET = 1 << SMU_13_0_7_ODCAP_PER_ZONE_GFX_VOLTAGE_OFFSET, // Perzone voltage offset feature
    SMU_13_0_7_ODFEATURE_COUNT                   = 16,
};

#define SMU_13_0_7_MAX_ODFEATURE 32 // Maximum Number of OD Features

enum SMU_13_0_7_ODSETTING_ID {
    SMU_13_0_7_ODSETTING_GFXCLKFMAX              = 0,
    SMU_13_0_7_ODSETTING_GFXCLKFMIN              = 1,
    SMU_13_0_7_ODSETTING_UCLKFMIN                = 2,
    SMU_13_0_7_ODSETTING_UCLKFMAX                = 3,
    SMU_13_0_7_ODSETTING_POWERPERCENTAGE         = 4,
    SMU_13_0_7_ODSETTING_FANRPMMIN               = 5,
    SMU_13_0_7_ODSETTING_FANRPMACOUSTICLIMIT     = 6,
    SMU_13_0_7_ODSETTING_FANTARGETTEMPERATURE    = 7,
    SMU_13_0_7_ODSETTING_OPERATINGTEMPMAX        = 8,
    SMU_13_0_7_ODSETTING_ACTIMING                = 9,
    SMU_13_0_7_ODSETTING_FAN_ZERO_RPM_CONTROL    = 10,
    SMU_13_0_7_ODSETTING_AUTOUVENGINE            = 11,
    SMU_13_0_7_ODSETTING_AUTOOCENGINE            = 12,
    SMU_13_0_7_ODSETTING_AUTOOCMEMORY            = 13,
    SMU_13_0_7_ODSETTING_FAN_CURVE_TEMPERATURE_1 = 14,
    SMU_13_0_7_ODSETTING_FAN_CURVE_SPEED_1       = 15,
    SMU_13_0_7_ODSETTING_FAN_CURVE_TEMPERATURE_2 = 16,
    SMU_13_0_7_ODSETTING_FAN_CURVE_SPEED_2       = 17,
    SMU_13_0_7_ODSETTING_FAN_CURVE_TEMPERATURE_3 = 18,
    SMU_13_0_7_ODSETTING_FAN_CURVE_SPEED_3       = 19,
    SMU_13_0_7_ODSETTING_FAN_CURVE_TEMPERATURE_4 = 20,
    SMU_13_0_7_ODSETTING_FAN_CURVE_SPEED_4       = 21,
    SMU_13_0_7_ODSETTING_FAN_CURVE_TEMPERATURE_5 = 22,
    SMU_13_0_7_ODSETTING_FAN_CURVE_SPEED_5       = 23,
    SMU_13_0_7_ODSETTING_AUTO_FAN_ACOUSTIC_LIMIT = 24,
    SMU_13_0_7_ODSETTING_POWER_MODE              = 25,
    SMU_13_0_7_ODSETTING_PER_ZONE_GFX_VOLTAGE_OFFSET_POINT_1 = 26,
    SMU_13_0_7_ODSETTING_PER_ZONE_GFX_VOLTAGE_OFFSET_POINT_2 = 27,
    SMU_13_0_7_ODSETTING_PER_ZONE_GFX_VOLTAGE_OFFSET_POINT_3 = 28,
    SMU_13_0_7_ODSETTING_PER_ZONE_GFX_VOLTAGE_OFFSET_POINT_4 = 29,
    SMU_13_0_7_ODSETTING_PER_ZONE_GFX_VOLTAGE_OFFSET_POINT_5 = 30,
    SMU_13_0_7_ODSETTING_PER_ZONE_GFX_VOLTAGE_OFFSET_POINT_6 = 31,
    SMU_13_0_7_ODSETTING_COUNT = 32,
};
#define SMU_13_0_7_MAX_ODSETTING 64 // Maximum Number of ODSettings

enum SMU_13_0_7_PWRMODE_SETTING {
    SMU_13_0_7_PMSETTING_POWER_LIMIT_QUIET           = 0,
    SMU_13_0_7_PMSETTING_POWER_LIMIT_BALANCE         = 1,
    SMU_13_0_7_PMSETTING_POWER_LIMIT_TURBO           = 2,
    SMU_13_0_7_PMSETTING_POWER_LIMIT_RAGE            = 3,
    SMU_13_0_7_PMSETTING_ACOUSTIC_TEMP_QUIET         = 4,
    SMU_13_0_7_PMSETTING_ACOUSTIC_TEMP_BALANCE       = 5,
    SMU_13_0_7_PMSETTING_ACOUSTIC_TEMP_TURBO         = 6,
    SMU_13_0_7_PMSETTING_ACOUSTIC_TEMP_RAGE          = 7,
    SMU_13_0_7_PMSETTING_ACOUSTIC_TARGET_RPM_QUIET   = 8,
    SMU_13_0_7_PMSETTING_ACOUSTIC_TARGET_RPM_BALANCE = 9,
    SMU_13_0_7_PMSETTING_ACOUSTIC_TARGET_RPM_TURBO   = 10,
    SMU_13_0_7_PMSETTING_ACOUSTIC_TARGET_RPM_RAGE    = 11,
    SMU_13_0_7_PMSETTING_ACOUSTIC_LIMIT_RPM_QUIET    = 12,
    SMU_13_0_7_PMSETTING_ACOUSTIC_LIMIT_RPM_BALANCE  = 13,
    SMU_13_0_7_PMSETTING_ACOUSTIC_LIMIT_RPM_TURBO    = 14,
    SMU_13_0_7_PMSETTING_ACOUSTIC_LIMIT_RPM_RAGE     = 15,
};
#define SMU_13_0_7_MAX_PMSETTING 32 // Maximum Number of PowerMode Settings

struct smu_13_0_7_overdrive_table {
    uint8_t revision;                             // Revision = SMU_13_0_7_PP_OVERDRIVE_VERSION
    uint8_t reserve[3];                           // Zero filled field reserved for future use
    uint32_t feature_count;                       // Total number of supported features
    uint32_t setting_count;                       // Total number of supported settings
    uint8_t cap[SMU_13_0_7_MAX_ODFEATURE];        // OD feature support flags
    uint32_t max[SMU_13_0_7_MAX_ODSETTING];       // default maximum settings
    uint32_t min[SMU_13_0_7_MAX_ODSETTING];       // default minimum settings
    int16_t pm_setting[SMU_13_0_7_MAX_PMSETTING]; // Optimized power mode feature settings
};

enum SMU_13_0_7_PPCLOCK_ID {
    SMU_13_0_7_PPCLOCK_GFXCLK  = 0,
    SMU_13_0_7_PPCLOCK_SOCCLK  = 1,
    SMU_13_0_7_PPCLOCK_UCLK    = 2,
    SMU_13_0_7_PPCLOCK_FCLK    = 3,
    SMU_13_0_7_PPCLOCK_DCLK_0  = 4,
    SMU_13_0_7_PPCLOCK_VCLK_0  = 5,
    SMU_13_0_7_PPCLOCK_DCLK_1  = 6,
    SMU_13_0_7_PPCLOCK_VCLK_1  = 7,
    SMU_13_0_7_PPCLOCK_DCEFCLK = 8,
    SMU_13_0_7_PPCLOCK_DISPCLK = 9,
    SMU_13_0_7_PPCLOCK_PIXCLK  = 10,
    SMU_13_0_7_PPCLOCK_PHYCLK  = 11,
    SMU_13_0_7_PPCLOCK_DTBCLK  = 12,
    SMU_13_0_7_PPCLOCK_COUNT   = 13,
};

#define SMU_13_0_7_MAX_PPCLOCK 16 // Maximum Number of PP Clocks

struct smu_13_0_7_powerplay_table {
    struct atom_common_table_header header; // For PLUM_BONITO, header.format_revision = 15, header.content_revision = 0
    uint8_t table_revision;   // For PLUM_BONITO, table_revision = 2
    uint8_t padding;
    uint16_t table_size;      // Driver portion table size. The offset to smc_pptable including header size
    uint32_t golden_pp_id;    // PPGen use only: PP Table ID on the Golden Data Base
    uint32_t golden_revision; // PPGen use only: PP Table Revision on the Golden Data Base
    uint16_t format_id;       // PPGen use only: PPTable for different ASICs. For PLUM_BONITO this should be 0x80
    uint32_t platform_caps;   // POWERPLAYABLE::ulPlatformCaps

    uint8_t thermal_controller_type; // one of SMU_13_0_7_PP_THERMALCONTROLLER

    uint16_t small_power_limit1;
    uint16_t small_power_limit2;
    uint16_t boost_power_limit; // For Gemini Board, when the slave adapter is in BACO mode, the master adapter will use this boost power limit instead of the default power limit to boost the power limit.
    uint16_t software_shutdown_temp;

    uint32_t reserve[45];

    struct smu_13_0_7_overdrive_table overdrive_table;
    uint8_t padding1;
    struct pptable_smu13 smc_pptable; // PPTable_t in driver_if.h
};

#pragma pack(pop)

#endif
