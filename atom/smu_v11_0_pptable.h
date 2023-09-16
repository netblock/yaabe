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

#pragma pack(push, 1)


struct smu_powerplay_table_header {
	struct atom_common_table_header header;
	uint8_t  table_revision;
	uint16_t table_size; //Driver portion table size. The offset to smc_pptable including header size
};

#define SMU_11_0_TABLE_FORMAT_REVISION                  12

//// POWERPLAYTABLE::ulPlatformCaps
#define SMU_11_0_PP_PLATFORM_CAP_POWERPLAY              0x1
#define SMU_11_0_PP_PLATFORM_CAP_SBIOSPOWERSOURCE       0x2
#define SMU_11_0_PP_PLATFORM_CAP_HARDWAREDC             0x4
#define SMU_11_0_PP_PLATFORM_CAP_BACO                   0x8
#define SMU_11_0_PP_PLATFORM_CAP_MACO                   0x10
#define SMU_11_0_PP_PLATFORM_CAP_SHADOWPSTATE           0x20
union smu11_platform_caps {
	uint32_t platform_caps; 
	struct { uint32_t
		powerplay     :0-0 +1,
		sbios_powersource :1-1 +1,
		hardware_dc   :2-2 +1,
		BACO          :3-3 +1,
		MACO          :4-4 +1,
		shadow_pstate :5-5 +1,
		reserved     :31-6 +1;
	};
};


// SMU_11_0_PP_THERMALCONTROLLER - Thermal Controller Type
#define SMU_11_0_PP_THERMALCONTROLLER_NONE   0

#define SMU_11_0_PP_OVERDRIVE_VERSION        0x0800
#define SMU_11_0_PP_POWERSAVINGCLOCK_VERSION 0x0100

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

// 14 bits; when does this get used?
enum SMU_11_0_ODFEATURE_ID { // this isn't a necessary way to do it, AMD. Wasteful.
	SMU_11_0_ODFEATURE_GFXCLK_LIMITS        = 1 << SMU_11_0_ODCAP_GFXCLK_LIMITS,        //GFXCLK Limit feature
	SMU_11_0_ODFEATURE_GFXCLK_CURVE         = 1 << SMU_11_0_ODCAP_GFXCLK_CURVE,         //GFXCLK Curve feature
	SMU_11_0_ODFEATURE_UCLK_MAX             = 1 << SMU_11_0_ODCAP_UCLK_MAX,             //UCLK Limit feature
	SMU_11_0_ODFEATURE_POWER_LIMIT          = 1 << SMU_11_0_ODCAP_POWER_LIMIT,          //Power Limit feature
	SMU_11_0_ODFEATURE_FAN_ACOUSTIC_LIMIT   = 1 << SMU_11_0_ODCAP_FAN_ACOUSTIC_LIMIT,   //Fan Acoustic RPM feature
	SMU_11_0_ODFEATURE_FAN_SPEED_MIN        = 1 << SMU_11_0_ODCAP_FAN_SPEED_MIN,        //Minimum Fan Speed feature
	SMU_11_0_ODFEATURE_TEMPERATURE_FAN      = 1 << SMU_11_0_ODCAP_TEMPERATURE_FAN,      //Fan Target Temperature Limit feature
	SMU_11_0_ODFEATURE_TEMPERATURE_SYSTEM   = 1 << SMU_11_0_ODCAP_TEMPERATURE_SYSTEM,   //Operating Temperature Limit feature
	SMU_11_0_ODFEATURE_MEMORY_TIMING_TUNE   = 1 << SMU_11_0_ODCAP_MEMORY_TIMING_TUNE,   //AC Timing Tuning feature
	SMU_11_0_ODFEATURE_FAN_ZERO_RPM_CONTROL = 1 << SMU_11_0_ODCAP_FAN_ZERO_RPM_CONTROL, //Zero RPM feature
	SMU_11_0_ODFEATURE_AUTO_UV_ENGINE       = 1 << SMU_11_0_ODCAP_AUTO_UV_ENGINE,       //Auto Under Volt GFXCLK feature
	SMU_11_0_ODFEATURE_AUTO_OC_ENGINE       = 1 << SMU_11_0_ODCAP_AUTO_OC_ENGINE,       //Auto Over Clock GFXCLK feature
	SMU_11_0_ODFEATURE_AUTO_OC_MEMORY       = 1 << SMU_11_0_ODCAP_AUTO_OC_MEMORY,       //Auto Over Clock MCLK feature
	SMU_11_0_ODFEATURE_FAN_CURVE            = 1 << SMU_11_0_ODCAP_FAN_CURVE,            //Fan Curve feature
	SMU_11_0_ODFEATURE_COUNT                = 14,
};
#define SMU_11_0_MAX_ODFEATURE 32 //Maximum Number of OD Features

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
#define SMU_11_0_MAX_ODSETTING    32          //Maximum Number of ODSettings



struct smu_11_0_overdrive_table {
	uint8_t  revision;      //Revision = SMU_11_0_PP_OVERDRIVE_VERSION
	uint8_t  reserve[3];    //Zero filled field reserved for future use
	uint32_t feature_count; //Total number of supported features
	uint32_t setting_count; //Total number of supported settings
	uint8_t  cap[SMU_11_0_MAX_ODFEATURE]; //OD feature support flags
	uint32_t max[SMU_11_0_MAX_ODSETTING]; //default maximum settings
	uint32_t min[SMU_11_0_MAX_ODSETTING]; //default minimum settings
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
#define SMU_11_0_MAX_PPCLOCK 16 //Maximum Number of PP Clocks

struct smu_11_0_power_saving_clock_table {
	uint8_t  revision;   //Revision = SMU_11_0_PP_POWERSAVINGCLOCK_VERSION
	uint8_t  reserve[3]; //Zero filled field reserved for future use
	uint32_t count;      //power_saving_clock_count = SMU_11_0_PPCLOCK_COUNT
	uint32_t max[SMU_11_0_MAX_PPCLOCK]; //PowerSavingClock Mode Clock Maximum array In MHz
	uint32_t min[SMU_11_0_MAX_PPCLOCK]; //PowerSavingClock Mode Clock Minimum array In MHz
};

struct smu_11_0_powerplay_table {
	struct smu_powerplay_table_header header;
	uint32_t golden_pp_id;
	uint32_t golden_revision;
	uint16_t format_id;
	union smu11_platform_caps platform_caps;
										
	uint8_t  thermal_controller_type; //one of SMU_11_0_PP_THERMALCONTROLLER

	uint16_t small_power_limit1;
	uint16_t small_power_limit2;
	uint16_t boost_power_limit;
	uint16_t od_turbo_power_limit;      //Power limit setting for Turbo mode in Performance UI Tuning. 
	uint16_t od_power_save_power_limit; //Power limit setting for PowerSave/Optimal mode in Performance UI Tuning. 
	uint16_t software_shutdown_temp;

	uint16_t reserve[6]; //Zero filled field reserved for future use

	struct smu_11_0_power_saving_clock_table power_saving_clock;
	struct smu_11_0_overdrive_table overdrive_table;

	struct smc_pptable smc_pptable; // PPTable_t in smu11_driver_if.h
};

#pragma pack(pop)

#endif
