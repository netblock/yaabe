/*
For smu_v11_pptable.h and smu11_driver_if.h -- navi1 PowerPlay tables
See atui_atomfirmware.c for how to use PPATUI_FUNCIFY()
*/

#include "atomtree.h"
#include "atui.h"

/*
import re

names = ('SMU_11_0_ODSETTING_GFXCLKFMAX', 'SMU_11_0_ODSETTING_GFXCLKFMIN', 'SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P1', 'SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P1', 'SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P2', 'SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P2', 'SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P3', 'SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P3', 'SMU_11_0_ODSETTING_UCLKFMAX', 'SMU_11_0_ODSETTING_POWERPERCENTAGE', 'SMU_11_0_ODSETTING_FANRPMMIN', 'SMU_11_0_ODSETTING_FANRPMACOUSTICLIMIT', 'SMU_11_0_ODSETTING_FANTARGETTEMPERATURE', 'SMU_11_0_ODSETTING_OPERATINGTEMPMAX', 'SMU_11_0_ODSETTING_ACTIMING', 'SMU_11_0_ODSETTING_FAN_ZERO_RPM_CONTROL', 'SMU_11_0_ODSETTING_AUTOUVENGINE', 'SMU_11_0_ODSETTING_AUTOOCENGINE', 'SMU_11_0_ODSETTING_AUTOOCMEMORY')

pat = '    (bios->%s[%s], %s,\n        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)\n    ),'

for n in names:
	s = re.sub("(SMU_11_0_ODSETTING_)", "", n)
	s = re.sub("_", "", s.lower())
	print(pat % ("max", n, ("%s (max)"% s)))
	print(pat % ("min", n, ("%s (min)"% s)))

for n in names:
	s = re.sub("(SMU_11_0_PPCLOCK_)", "", n)
	s = re.sub("_", "", s)
	print(pat % ("max", n, ("%s (max)"% s)))
	print(pat % ("min", n, ("%s (min)"% s)))
*/

PPATUI_FUNCIFY(struct, smu_11_0_overdrive_table, atomtree_powerplaytable,
	(bios->revision, u8"revision",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Revision = SMU_11_0_PP_OVERDRIVE_VERSION"))
	),
	(bios->reserve, u8"reserve",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"Zero filled field reserved for future use"))
	),
	(bios->feature_count, u8"feature_count",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Total number of supported features"))
	),
	(bios->setting_count, u8"setting_count",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Total number of supported settings"))
	),

	(bios->cap, u8"Supported OD feature support flags", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_11_0_ODCAP_COUNT, // deferred start, count
			 SMU_11_0_ODFEATURE_CAP // enum
		)), ((LANG_ENG, u8"support flag"))
	),
	((&(bios->cap[SMU_11_0_ODCAP_COUNT])), // start
		u8"Undefined OD feature support flags", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"OD feature [14 + %02u]",
					// if COUNT changes, please change this 14
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			(SMU_11_0_MAX_ODFEATURE - SMU_11_0_ODCAP_COUNT), // count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"support flag"))
	),

	(bios->max, u8"Supported Overdrive settings (max)", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"max: %s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_11_0_ODSETTING_COUNT, // deferred start, count
			SMU_11_0_ODSETTING_ID // enum
		)), (ATUI_NODESCR)
	),
	(bios->min, u8"Supported Overdrive settings (min)",
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"min: %s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_11_0_ODSETTING_COUNT, // deferred start, count
			SMU_11_0_ODSETTING_ID // enum
		)), (ATUI_NODESCR)
	),


	((&(bios->max[SMU_11_0_ODSETTING_COUNT])), // start
		u8"Undefined OD settings (max)", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"max: [19 + %02u]",
					// if COUNT changes, please change this 19
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			(SMU_11_0_MAX_ODSETTING - SMU_11_0_ODSETTING_COUNT), // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	((&(bios->min[SMU_11_0_ODSETTING_COUNT])), // start
		u8"Undefined OD settings (min)", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"min: [19 + %02u]",
					// if COUNT changes, please change this 19
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			(SMU_11_0_MAX_ODSETTING - SMU_11_0_ODSETTING_COUNT), // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, smu_11_0_7_overdrive_table, atui_nullstruct,
	(bios->revision, u8"revision",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Revision = SMU_11_0_7_PP_OVERDRIVE_VERSION"))
	),
	(bios->reserve, u8"reserve",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"Zero filled field reserved for future use"))
	),
	(bios->feature_count, u8"feature_count",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Total number of supported features"))
	),
	(bios->setting_count, u8"setting_count",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Total number of supported settings"))
	),

	(bios->cap, u8"Supported OD feature support flags", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_11_0_7_ODCAP_COUNT, // deferred start, count
			SMU_11_0_7_ODFEATURE_CAP // enum
		)), ((LANG_ENG, u8"OD feature support flags"))
	),

	(bios->max, u8"Supported Overdrive settings (max)", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"max: %s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_11_0_7_ODSETTING_COUNT, // deferred start, count
			SMU_11_0_7_ODSETTING_ID // enum
		)), ((LANG_ENG, u8"default maximum settings"))
	),
	(bios->min, u8"Supported Overdrive settings (min)", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"min: %s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_11_0_7_ODSETTING_COUNT, // deferred start, count
			SMU_11_0_7_ODSETTING_ID // enum
		)), ((LANG_ENG, u8"default minimum settings"))
	),
	(bios->pm_setting, u8"Supported Power Mode settings", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_11_0_7_PMSETTING_COUNT, // deferred start, count
			SMU_11_0_7_PWRMODE_SETTING // enum
		)), ((LANG_ENG, u8"Optimized power mode feature settings"))
	),

	((&(bios->cap[SMU_11_0_7_ODCAP_COUNT])), // start
		u8"Undefined OD feature support flags", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"OD feature [16 + %02u]",
					// if COUNT changes, please change this 16
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			(SMU_11_0_7_MAX_ODFEATURE - SMU_11_0_7_ODCAP_COUNT), // count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"OD feature support flags"))
	),
	((&(bios->max[SMU_11_0_7_ODSETTING_COUNT])), // start
		u8"Undefined Overdrive settings (max)", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"max: [30 + %02u]",
					// if COUNT changes, please change this 30
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			(SMU_11_0_7_MAX_ODSETTING - SMU_11_0_7_ODSETTING_COUNT), // count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"default maximum settings"))
	),
	((&(bios->min[SMU_11_0_7_ODSETTING_COUNT])), // start
		u8"Undefined Overdrive settings (min)", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"min: [30 + %02u]",
					// if COUNT changes, please change this 30
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			(SMU_11_0_7_MAX_ODSETTING - SMU_11_0_7_ODSETTING_COUNT), // count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"default minimum settings"))
	),
	((&(bios->pm_setting[SMU_11_0_7_PMSETTING_COUNT])),
		u8"Undefined Power Mode settings",
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"pm_setting: [16 + %02u]",
					// if COUNT changes, please change this 16
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			(SMU_11_0_7_MAX_PMSETTING - SMU_11_0_7_PMSETTING_COUNT), // count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"Optimized power mode feature settings"))
	)
)


PPATUI_FUNCIFY(struct, smu_11_0_power_saving_clock_table,
		atomtree_powerplaytable,
	(bios->revision, u8"revision",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Revision = SMU_11_0_PP_POWERSAVINGCLOCK_VERSION"))
	),
	(bios->reserve, u8"reserve",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"Zero filled field reserved for future use"))
	),
	(bios->count, u8"count",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"power_saving_clock_count = SMU_11_0_PPCLOCK_COUNT"))
	),

	(bios->max, u8"PowerSavingClock modes (max)", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"max: %s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_11_0_PPCLOCK_COUNT, // deferred start, count
			SMU_11_0_PPCLOCK_ID // enum
		)), (ATUI_NODESCR)
	),
	(bios->min, u8"PowerSavingClock modes (min)", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"min: %s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_11_0_PPCLOCK_COUNT, // deferred start, count
			SMU_11_0_PPCLOCK_ID // enum
		)), (ATUI_NODESCR)
	),

	((&(bios->max[SMU_11_0_PPCLOCK_COUNT])), // start
		u8"Undefined PowerSavingClock Modes (max)", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"max: [10 + %02u]",
					// if COUNT changes, please change this 10
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			(SMU_11_0_MAX_PPCLOCK - SMU_11_0_PPCLOCK_COUNT), // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	((&(bios->min[SMU_11_0_PPCLOCK_COUNT])), // start
		u8"Undefined PowerSavingClock Modes (min)", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"min: [10 + %02u]",
					// if COUNT changes, please change this 10
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			(SMU_11_0_MAX_PPCLOCK - SMU_11_0_PPCLOCK_COUNT), // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, smu_11_0_7_power_saving_clock_table, atui_nullstruct,
	(bios->revision, u8"revision",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Revision = SMU_11_0_7_PP_POWERSAVINGCLOCK_VERSION"))
	),
	(bios->reserve, u8"reserve",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"Zero filled field reserved for future use"))
	),
	(bios->count, u8"count",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"power_saving_clock_count = SMU_11_0_7_PPCLOCK_COUNT"))
	),

	(bios->max,
		u8"PowerSavingClock modes (max)", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"max: %s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_11_0_7_PPCLOCK_COUNT, // deferred start, count
			SMU_11_0_7_PPCLOCK_ID // enum
		)),
		((LANG_ENG, u8"PowerSavingClock Mode Clock Maximum array In MHz"))
	),
	(bios->min,
		u8"PowerSavingClock modes (min)", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"min: %s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_11_0_7_PPCLOCK_COUNT, // deferred start, count
			SMU_11_0_7_PPCLOCK_ID // enum
		)),
		((LANG_ENG, u8"PowerSavingClock Mode Clock Minimum array In MHz"))
	),

	((&(bios->max[SMU_11_0_7_PPCLOCK_COUNT])), // start
		u8"Undefined PowerSavingClock Modes (max)", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"max: [13 + %02u]",
					// if COUNT changes, please change this 13
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			(SMU_11_0_7_MAX_PPCLOCK - SMU_11_0_7_PPCLOCK_COUNT), // count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"PowerSavingClock Mode Clock Maximum array In MHz"))
	),
	((&(bios->min[SMU_11_0_7_PPCLOCK_COUNT])), // start
		u8"Undefined PowerSavingClock Modes (min)", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"min: [13 + %02u]",
					// if COUNT changes, please change this 13
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			(SMU_11_0_7_MAX_PPCLOCK - SMU_11_0_7_PPCLOCK_COUNT), // count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"PowerSavingClock Mode Clock Minimum array In MHz"))
	)
)


PPATUI_FUNCIFY(union, powerplay_feature_control_smu11_0x13, atomtree_powerplaytable,
	(bios->feature_control, u8"feature_control",
		(ATUI_HEX, ATUI_BITFIELD, (
			(u8"DPM_PREFETCHER", 0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_GFXCLK",     1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_UCLK",       2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_SOCCLK",     3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_UVD",        4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_VCE",        5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ULV",            6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_MP0CLK",     7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_LINK",       8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_DCEFCLK",    9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_GFXCLK",     10,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_SOCCLK",     11,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_LCLK",       12,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPT",           13,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TDC",           14,14, ATUI_DEC, (ATUI_NODESCR)),
			(u8"THERMAL",       15,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_PER_CU_CG", 16,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"RM",            17,17, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_DCEFCLK",    18,18, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ACDC",          19,19, ATUI_DEC, (ATUI_NODESCR)),
			(u8"VR0HOT",        20,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"VR1HOT",        21,21, ATUI_DEC, (ATUI_NODESCR)),
			(u8"FW_CTF",        22,22, ATUI_DEC, (ATUI_NODESCR)),
			(u8"LED_DISPLAY",   23,23, ATUI_DEC, (ATUI_NODESCR)),
			(u8"FAN_CONTROL",   24,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_EDC",       25,25, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFXOFF",        26,26, ATUI_DEC, (ATUI_NODESCR)),
			(u8"CG",            27,27, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_FCLK",      28,28, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_FCLK",       29,29, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_MP1CLK",     30,30, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_MP0CLK",     31,31, ATUI_DEC, (ATUI_NODESCR)),
			(u8"XGMI",          32,32, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ECC",           33,33, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_34",      34,34, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_35",      35,35, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_36",      36,36, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_37",      37,37, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_38",      38,38, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_39",      39,39, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_40",      40,40, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_41",      41,41, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_42",      42,42, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_43",      43,43, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_44",      44,44, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_45",      45,45, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_46",      46,46, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_47",      47,47, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_48",      48,48, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_49",      49,49, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_50",      50,50, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_51",      51,51, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_52",      52,52, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_53",      53,53, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_54",      54,54, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_55",      55,55, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_56",      56,56, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_57",      57,57, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_58",      58,58, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_59",      59,59, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_60",      60,60, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_61",      61,61, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_62",      62,62, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_63",      63,63, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, powerplay_feature_control_smu11_0x33, atomtree_powerplaytable,
	(bios->feature_control, u8"feature_control",
		(ATUI_HEX, ATUI_BITFIELD, (
			(u8"DPM_PREFETCHER",      0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_GFXCLK",          1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_GFX_PACE",        2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_UCLK",            3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_SOCCLK",          4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_MP0CLK",          5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_LINK",            6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_DCEFCLK",         7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MEM_VDDCI_SCALING",   8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MEM_MVDD_SCALING",    9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_GFXCLK",           10,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_SOCCLK",           11,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_LCLK",             12,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_DCEFCLK",          13,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_UCLK",             14,14, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_ULV",             15,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"FW_DSTATE",           16,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFXOFF",              17,17, ATUI_DEC, (ATUI_NODESCR)),
			(u8"BACO",                18,18, ATUI_DEC, (ATUI_NODESCR)),
			(u8"VCN_PG",              19,19, ATUI_DEC, (ATUI_NODESCR)),
			(u8"JPEG_PG",             20,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"USB_PG",              21,21, ATUI_DEC, (ATUI_NODESCR)),
			(u8"RSMU_SMN_CG",         22,22, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPT",                 23,23, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TDC",                 24,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_EDC",             25,25, ATUI_DEC, (ATUI_NODESCR)),
			(u8"APCC_PLUS",           26,26, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GTHR",                27,27, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ACDC",                28,28, ATUI_DEC, (ATUI_NODESCR)),
			(u8"VR0HOT",              29,29, ATUI_DEC, (ATUI_NODESCR)),
			(u8"VR1HOT",              30,30, ATUI_DEC, (ATUI_NODESCR)),
			(u8"FW_CTF",              31,31, ATUI_DEC, (ATUI_NODESCR)),
			(u8"FAN_CONTROL",         32,32, ATUI_DEC, (ATUI_NODESCR)),
			(u8"THERMAL",             33,33, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_DCS",             34,34, ATUI_DEC, (ATUI_NODESCR)),
			(u8"RM",                  35,35, ATUI_DEC, (ATUI_NODESCR)),
			(u8"LED_DISPLAY",         36,36, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_SS",              37,37, ATUI_DEC, (ATUI_NODESCR)),
			(u8"OUT_OF_BAND_MONITOR", 38,38, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_DEPENDENT_VMIN", 39,39, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MMHUB_PG",            40,40, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ATHUB_PG",            41,41, ATUI_DEC, (ATUI_NODESCR)),
			(u8"APCC_DFLL",           42,42, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_43",            43,43, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_44",            44,44, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_45",            45,45, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_46",            46,46, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_47",            47,47, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_48",            48,48, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_49",            49,49, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_50",            50,50, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_51",            51,51, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_52",            52,52, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_53",            53,53, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_54",            54,54, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_55",            55,55, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_56",            56,56, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_57",            57,57, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_58",            58,58, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_59",            59,59, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_60",            60,60, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_61",            61,61, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_62",            62,62, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_63",            63,63, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, powerplay_feature_control_smu11_0x40, atui_nullstruct,
	(bios->feature_control, u8"feature_control",
		(ATUI_HEX, ATUI_BITFIELD, (
			(u8"DPM_PREFETCHER",       0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_GFXCLK",           1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_GFX_GPO",          2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_UCLK",             3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_FCLK",             4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_SOCCLK",           5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_MP0CLK",           6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_LINK",             7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_DCEFCLK",          8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_XGMI",             9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MEM_VDDCI_SCALING",   10,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MEM_MVDD_SCALING",    11,11, ATUI_DEC, (ATUI_NODESCR)),

			(u8"DS_GFXCLK",           12,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_SOCCLK",           13,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_FCLK",             14,14, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_LCLK",             15,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_DCEFCLK",          16,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_UCLK",             17,17, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_ULV",             18,18, ATUI_DEC, (ATUI_NODESCR)),
			(u8"FW_DSTATE",           19,19, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFXOFF",              20,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"BACO",                21,21, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MM_DPM_PG",           22,22, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_23",            23,23, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPT",                 24,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TDC",                 25,25, ATUI_DEC, (ATUI_NODESCR)),
			(u8"APCC_PLUS",           26,26, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GTHR",                27,27, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ACDC",                28,28, ATUI_DEC, (ATUI_NODESCR)),
			(u8"VR0HOT",              29,29, ATUI_DEC, (ATUI_NODESCR)),
			(u8"VR1HOT",              30,30, ATUI_DEC, (ATUI_NODESCR)),
			(u8"FW_CTF",              31,31, ATUI_DEC, (ATUI_NODESCR)),
			(u8"FAN_CONTROL",         32,32, ATUI_DEC, (ATUI_NODESCR)),
			(u8"THERMAL",             33,33, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_DCS",             34,34, ATUI_DEC, (ATUI_NODESCR)),
			(u8"RM",                  35,35, ATUI_DEC, (ATUI_NODESCR)),
			(u8"LED_DISPLAY",         36,36, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_SS",              37,37, ATUI_DEC, (ATUI_NODESCR)),
			(u8"OUT_OF_BAND_MONITOR", 38,38, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_DEPENDENT_VMIN", 39,39, ATUI_DEC, (ATUI_NODESCR)),

			(u8"MMHUB_PG",            40,40, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ATHUB_PG",            41,41, ATUI_DEC, (ATUI_NODESCR)),
			(u8"APCC_DFLL",           42,42, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DF_SUPERV",           43,43, ATUI_DEC, (ATUI_NODESCR)),
			(u8"RSMU_SMN_CG",         44,44, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DF_CSTATE",           45,45, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TWO_STEP_PSTATE",     46,46, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SMNCLK_DPM",          47,47, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PERLINK_GMIDOWN",     48,48, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_EDC",             49,49, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_PER_PART_VMIN",   50,50, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SMART_SHIFT",         51,51, ATUI_DEC, (ATUI_NODESCR)),
			(u8"APT",                 52,52, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_53",            53,53, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_54",            54,54, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_55",            55,55, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_56",            56,56, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_57",            57,57, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_58",            58,58, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_59",            59,59, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_60",            60,60, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_61",            61,61, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_62",            62,62, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_63",            63,63, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, dpm_debug_override_smu11_0x13, atomtree_powerplaytable,
	(bios->DebugOverrides, u8"DebugOverrides",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"disable_socclk_pid",              0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"disable_uclk_pid",                1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_volt_link_uvd_socclk",     2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_volt_link_uvd_uclk",       3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_freq_link_vclk_socclk",    4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_freq_link_vclk_uclk",      5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_freq_link_dclk_socclk",    6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_freq_link_dclk_uclk",      7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_volt_link_vce_socclk",     8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_volt_link_vce_uclk",       9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_freq_link_eclk_socclk",   10,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_freq_link_eclk_uclk",     11,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_freq_link_gfxclk_socclk", 12,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_freq_link_gfxclk_uclk",   13,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_gfxoff_gfxclk_switch",    14,14, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_gfxoff_socclk_switch",    15,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_gfxoff_uclk_switch",      16,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_gfxoff_fclk_switch",      17,17, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved",                       31,18, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, dpm_debug_override_smu11_0x33, atomtree_powerplaytable,
	(bios->DebugOverrides, u8"DebugOverrides",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"disable_socclk_pid",               0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"disable_uclk_pid",                 1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"disable_volt_link_vcn_socclk",     2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_freq_link_vclk_socclk",     3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_freq_link_dclk_socclk",     4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_freq_link_gfxclk_socclk",   5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_freq_link_gfxclk_uclk",     6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"disable_volt_link_dce_socclk",     7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"disable_volt_link_mp0_socclk",     8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"disable_dfll_pll_shutdown",        9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"disable_memory_temperature_read", 10,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved",                        31,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, dpm_debug_override_smu11_0x40, atui_nullstruct,
	(bios->DebugOverrides, u8"DebugOverrides",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"DISABLE_FCLK_PID",                 0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DISABLE_UCLK_PID",                 1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DISABLE_VOLT_LINK_VCN_FCLK",       2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ENABLE_FREQ_LINK_VCLK_FCLK",       3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ENABLE_FREQ_LINK_DCLK_FCLK",       4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ENABLE_FREQ_LINK_GFXCLK_SOCCLK",   5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ENABLE_FREQ_LINK_GFXCLK_UCLK",     6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DISABLE_VOLT_LINK_DCE_FCLK",       7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DISABLE_VOLT_LINK_MP0_SOCCLK",     8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DISABLE_DFLL_PLL_SHUTDOWN",        9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DISABLE_MEMORY_TEMPERATURE_READ", 11,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DISABLE_VOLT_LINK_VCN_DCEFCLK",   12,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DISABLE_FAST_FCLK_TIMER",         13,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DISABLE_VCN_PG",                  14,14, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DISABLE_FMAX_VMAX",               15,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ENABLE_eGPU_USB_WA",              16,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved",                        31,17, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, throttler_control_smu11_0x13, atui_nullstruct,
	(bios->ThrottlerControlMask, u8"ThrottlerControlMask",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"PADDING",      0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_EDGE",    1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_HOTSPOT", 2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_HBM",     3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_VR_GFX",  4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_VR_SOC",  5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_VR_MEM0", 6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_VR_MEM1", 7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_LIQUID",  8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_PLX",     9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_SKIN",   10,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TDC_GFX",     11,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TDC_SOC",     12,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPT",         13,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"FIT",         14,14, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPM",         15,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved",    31,16, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, throttler_control_smu11_0x33, atui_nullstruct,
	(bios->ThrottlerControlMask, u8"ThrottlerControlMask",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"PADDING",      0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_EDGE",    1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_HOTSPOT", 2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_MEM",     3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_VR_GFX",  4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_VR_MEM0", 5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_VR_MEM1", 6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_VR_SOC",  7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_LIQUID0", 8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_LIQUID1", 9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_PLX",    10,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_SKIN",   11,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TDC_GFX",     12,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TDC_SOC",     13,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPT0",        14,14, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPT1",        15,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPT2",        16,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPT3",        17,17, ATUI_DEC, (ATUI_NODESCR)),
			(u8"FIT",         18,18, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPM",         19,19, ATUI_DEC, (ATUI_NODESCR)),
			(u8"APCC",        20,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved",    31,21, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, throttler_control_smu11_0x40, atui_nullstruct,
	(bios->ThrottlerControlMask, u8"ThrottlerControlMask",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"PADDING",      0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_EDGE",    1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_HOTSPOT", 2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_MEM",     3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_VR_GFX",  4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_VR_MEM0", 5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_VR_MEM1", 6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_VR_SOC",  7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_LIQUID0", 8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_LIQUID1", 9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_PLX",    10,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TDC_GFX",     11,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TDC_SOC",     12,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPT0",        13,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPT1",        14,14, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPT2",        15,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPT3",        16,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"FIT",         17,17, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPM",         18,18, ATUI_DEC, (ATUI_NODESCR)),
			(u8"APCC",        19,19, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved",    31,20, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, fw_dstate_features_smu11_0x33, atui_nullstruct,
	(bios->FwDStateMask, u8"FwDStateMask",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"SOC_ULV",          0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"G6_HSR",           1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"G6_PHY_VDDCI_OFF", 2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MP0_DS",           3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SMN_DS",           4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MP1_DS",           5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MP1_WHISPER_MODE", 6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"LIV_MIN",          7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SOC_PLL_PWRDN",    8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved",        31,9, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, fw_dstate_features_smu11_0x40, atui_nullstruct,
	(bios->FwDStateMask, u8"FwDStateMask",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"SOC_ULV",                0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"G6_HSR",                 1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"G6_PHY_VDDCI_OFF",       2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MP0_DS",                 3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SMN_DS",                 4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MP1_DS",                 5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MP1_WHISPER_MODE",       6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SOC_LIV_MIN",            7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SOC_PLL_PWRDN",          8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MEM_PLL_PWRDN",          9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"OPTIMIZE_MALL_REFRESH", 10,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MEM_PSI",               11,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"HSR_NON_STROBE",        12,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MP0_ENTER_WFI",         13,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved",              31,14, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, gfx_gpo_features, atui_nullstruct,
	(bios->GfxGpoSubFeatureMask, u8"GfxGpoSubFeatureMask",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"PACE",     0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DEM",      1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved", 7,2, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, PiecewiseLinearDroopInt_t, atui_nullstruct,
	(bios->Fset, u8"Fset", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Fset [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			NUM_PIECE_WISE_LINEAR_DROOP_MODEL_VF_POINTS, // count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"in GHz"))
	),
	(bios->Vdroop, u8"Vdroop", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Vdroop [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			NUM_PIECE_WISE_LINEAR_DROOP_MODEL_VF_POINTS, // count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"in V"))
	)
)

PPATUI_FUNCIFY(struct, dpm_descriptor_smu11, atomtree_powerplaytable,
	(bios->VoltageMode, u8"VoltageMode",
		(ATUI_DEC, ATUI_ENUM, VOLTAGE_MODE_e),
		(ATUI_NODESCR)
	),
	(bios->SnapToDiscrete, u8"SnapToDiscrete",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"0 - Fine grained DPM, 1 - Discrete DPM"))
	),
	(bios->NumDiscreteLevels, u8"NumDiscreteLevels",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Set to 2 (Fmin, Fmax) when using fine grained  DPM, otherwise set to # discrete levels used"))
	),
	(bios->padding, u8"padding",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ConversionToAvfsClk, u8"ConversionToAvfsClk",
		(ATUI_NAN, ATUI_INLINE, linear_f32),
		((LANG_ENG, u8"Transfer function to AVFS Clock (GHz->GHz)"))
	),
	(bios->slowslow_curve, u8"slowslow_curve",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		((LANG_ENG, u8"Slow-slow curve (GHz->V)"))
	)
)
PPATUI_FUNCIFY(struct, dpm_descriptor_smu11_0x40, atui_nullstruct,
	(bios->VoltageMode, u8"VoltageMode",
		(ATUI_DEC, ATUI_ENUM, VOLTAGE_MODE_e),
		(ATUI_NODESCR)
	),
	(bios->SnapToDiscrete, u8"SnapToDiscrete",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"0 - Fine grained DPM, 1 - Discrete DPM"))
	),
	(bios->NumDiscreteLevels, u8"NumDiscreteLevels",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Set to 2 (Fmin, Fmax) when using fine grained DPM, otherwise set to # discrete levels used"))
	),
	(bios->Padding, u8"Padding",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ConversionToAvfsClk, u8"ConversionToAvfsClk",
		(ATUI_NAN, ATUI_INLINE, linear_f32),
		((LANG_ENG, u8"Transfer function to AVFS Clock (GHz->GHz)"))
	),
	(bios->SsCurve, u8"SsCurve",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		((LANG_ENG, u8"Slow-slow curve (GHz->V)"))
	),
	(bios->SsFmin, u8"SsFmin",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Fmin for SS curve. If SS curve is selected, will use V@SSFmin for F <= Fmin"))
	),
	(bios->Padding16, u8"Padding16",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, UclkDpmChangeRange_t, atui_nullstruct,
	(bios->Fmin, u8"Fmin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Fmax, u8"Fmax",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, smu11_smcpptable_v3_i2c_control, atomtree_powerplaytable,
	(bios->I2cControllers, u8"I2cControllers", // start, name
		(ATUI_NODISPLAY, ATUI_DYNARRAY, (
			(bios->I2cControllers, u8"%s",
				(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u32),
				(ATUI_NODESCR)
			),
			NULL, I2C_CONTROLLER_NAME_COUNT_SMU11_PPT3, // deferred start, count
			I2cControllerName_SMU_11_0_0_e // enum
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, smu11_smcpptable_v8_i2c_control, atomtree_powerplaytable,
	(bios->I2cControllers, u8"I2cControllers", // start, name
		(ATUI_NODISPLAY, ATUI_DYNARRAY, (
			(bios->I2cControllers, u8"%s",
				(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u8_mixed),
				(ATUI_NODESCR)
			),
			NULL, I2C_CONTROLLER_NAME_COUNT_SMU11_PPT8, // deferred start, count
			I2cControllerName_SMU_11_0_7_e // enum
		)), (ATUI_NODESCR)
	)
)

/* does not account for dynarray's enum
'<,'>s@\(u\?int[0-9]\+_t\s\+\)\([a-zA-Z0-9_]\+\)\[\([a-zA-Z0-9_]\+\)\]@(NULL, \2,\r\t\t(ATUI_NAN, ATUI_DYNARRAY, (\r\t\t\t(ATUI_NULL, \2 [%02u],\r\t\t\t\t(ATU
I_DEC, ATUI_NOFANCY), (ATUI_NODESCR)\r\t\t\t),\r\t\t\tbios->\2, \3 \/\/ start, count\r\t\t)), (ATUI_NODESCR)\r\t),@
*/
PPATUI_FUNCIFY(struct, smu11_smcpptable_v3, atomtree_powerplaytable,
	(bios->Version, u8"Version",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->features, u8"features",
		(ATUI_NAN, ATUI_INLINE, powerplay_feature_control_smu11_0x13),
		(ATUI_NODESCR)
	),

	(bios->SocketPowerLimitAc0, u8"SocketPowerLimitAc0",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitAc0Tau, u8"SocketPowerLimitAc0Tau",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitAc1, u8"SocketPowerLimitAc1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitAc1Tau, u8"SocketPowerLimitAc1Tau",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitAc2, u8"SocketPowerLimitAc2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitAc2Tau, u8"SocketPowerLimitAc2Tau",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitAc3, u8"SocketPowerLimitAc3",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitAc3Tau, u8"SocketPowerLimitAc3Tau",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitDc, u8"SocketPowerLimitDc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitDcTau, u8"SocketPowerLimitDcTau",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TdcLimitSoc, u8"TdcLimitSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Amps"))
	),
	(bios->TdcLimitSocTau, u8"TdcLimitSocTau",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Time constant of LPF in ms"))
	),
	(bios->TdcLimitGfx, u8"TdcLimitGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Amps"))
	),
	(bios->TdcLimitGfxTau, u8"TdcLimitGfxTau",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Time constant of LPF in ms"))
	),



	(bios->TedgeLimit, u8"TedgeLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->ThotspotLimit, u8"ThotspotLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->ThbmLimit, u8"ThbmLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->Tvr_gfxLimit, u8"Tvr_gfxLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->Tliquid1Limit, u8"Tliquid1Limit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->Tliquid2Limit, u8"Tliquid2Limit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->TplxLimit, u8"TplxLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->FitLimit, u8"FitLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Failures in time (failures per million parts over the defined lifetime)"))
	),

	(bios->PpmPowerLimit, u8"PpmPowerLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Switch this this power limit when temperature is above PpmTempThreshold"))
	),
	(bios->PpmTemperatureThreshold, u8"PpmTemperatureThreshold",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->MemoryOnPackage, u8"MemoryOnPackage",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding8_limits, u8"padding8_limits",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Tvr_SocLimit, u8"Tvr_SocLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),

	(bios->UlvVoltageOffsetSoc, u8"UlvVoltageOffsetSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2)"))
	),
	(bios->UlvVoltageOffsetGfx, u8"UlvVoltageOffsetGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2)"))
	),

	(bios->UlvSmnclkDid, u8"UlvSmnclkDid",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"DID for ULV mode. 0 means CLK will not be modified in ULV."))
	),
	(bios->UlvMp1clkDid, u8"UlvMp1clkDid",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"DID for ULV mode. 0 means CLK will not be modified in ULV."))
	),
	(bios->UlvGfxclkBypass, u8"UlvGfxclkBypass",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"1 to turn off/bypass Gfxclk during ULV, 0 to leave Gfxclk on during ULV"))
	),
	(bios->Padding234, u8"Padding234",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->MinVoltageGfx, u8"MinVoltageGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Minimum Voltage (\"Vmin\") of VDD_GFX"))
	),
	(bios->MinVoltageSoc, u8"MinVoltageSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Minimum Voltage (\"Vmin\") of VDD_SOC"))
	),
	(bios->MaxVoltageGfx, u8"MaxVoltageGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Maximum Voltage allowable of VDD_GFX"))
	),
	(bios->MaxVoltageSoc, u8"MaxVoltageSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Maximum Voltage allowable of VDD_SOC"))
	),

	(bios->LoadLineResistanceGfx, u8"LoadLineResistanceGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mOhms with 8 fractional bits"))
	),
	(bios->LoadLineResistanceSoc, u8"LoadLineResistanceSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mOhms with 8 fractional bits"))
	),

	// struct dpm_descriptor_smu11 DpmDescriptor[SMU11_PPT3_PPCLK_COUNT];

	(bios->FreqTableGfx, u8"FreqTableGfx", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableGfx [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_GFXCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableVclk, u8"FreqTableVclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableVclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_VCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableDclk, u8"FreqTableDclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableDclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableEclk, u8"FreqTableEclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableEclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_ECLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableSocclk, u8"FreqTableSocclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableSocclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_SOCCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableUclk, u8"FreqTableUclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableUclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableFclk, u8"FreqTableFclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableFclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_FCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableDcefclk, u8"FreqTableDcefclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableDcefclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DCEFCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableDispclk, u8"FreqTableDispclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableDispclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DISPCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTablePixclk, u8"FreqTablePixclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTablePixclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_PIXCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTablePhyclk, u8"FreqTablePhyclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTablePhyclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_PHYCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"In MHz"))
	),

	(bios->DcModeMaxFreq, u8"DcModeMaxFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTablePhyclk[%s]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU11_PPT3_PPCLK_COUNT, // deferred start, count
			SMU11_PPT3_PPCLK // enum
		)), ((LANG_ENG, u8"In MHz"))
	),

	(bios->Padding8_Clks, u8"Padding8_Clks",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mp0clkFreq, u8"Mp0clkFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Mp0clkFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_MP0CLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"In MHz"))
	),
	(bios->Mp0DpmVoltage, u8"Mp0DpmVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Mp0DpmVoltage [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_MP0CLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"mV(Q2)"))
	),

	(bios->GfxclkFidle, u8"GfxclkFidle",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->GfxclkSlewRate, u8"GfxclkSlewRate",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"for PLL babystepping???"))
	),
	(bios->CksEnableFreq, u8"CksEnableFreq",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding789, u8"Padding789",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->CksVoltageOffset, u8"CksVoltageOffset",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->Padding567, u8"Padding567",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->GfxclkDsMaxFreq, u8"GfxclkDsMaxFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Mhz"))
	),
	(bios->GfxclkSource, u8"GfxclkSource",
		(ATUI_DEC, ATUI_ENUM, GFXCLK_SOURCE_e),
		((LANG_ENG, u8"0 = PLL, 1 = DFLL"))
	),
	(bios->Padding456, u8"Padding456",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->LowestUclkReservedForUlv, u8"LowestUclkReservedForUlv",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Set this to 1 if UCLK DPM0 is reserved for ULV-mode only"))
	),
	(bios->Padding8_Uclk, u8"Padding8_Uclk",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->PcieGenSpeed, u8"PcieGenSpeed", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PcieGenSpeed [%02u]",
				(ATUI_DEC, ATUI_ENUM, PCIE_SPEED_e), (ATUI_NODESCR)
			),
			NULL, NUM_LINK_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->PcieLaneCount, u8"PcieLaneCount", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PcieLaneCount [%02u]",
				(ATUI_DEC, ATUI_ENUM, PCIE_WIDTH_e), (ATUI_NODESCR)
			),
			NULL, NUM_LINK_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->LclkFreq, u8"LclkFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"LclkFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_LINK_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->EnableTdpm, u8"EnableTdpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TdpmHighHystTemperature, u8"TdpmHighHystTemperature",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TdpmLowHystTemperature, u8"TdpmLowHystTemperature",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxclkFreqHighTempLimit, u8"GfxclkFreqHighTempLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"High limit on GFXCLK when temperature is high, for reliability."))
	),

	(bios->FanStopTemp, u8"FanStopTemp",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->FanStartTemp, u8"FanStartTemp",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),

	(bios->FanGainEdge, u8"FanGainEdge",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainHotspot, u8"FanGainHotspot",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainLiquid, u8"FanGainLiquid",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainVrGfx, u8"FanGainVrGfx",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainVrSoc, u8"FanGainVrSoc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainPlx, u8"FanGainPlx",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainHbm, u8"FanGainHbm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanPwmMin, u8"FanPwmMin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanAcousticLimitRpm, u8"FanAcousticLimitRpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanThrottlingRpm, u8"FanThrottlingRpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanMaximumRpm, u8"FanMaximumRpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetTemperature, u8"FanTargetTemperature",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetGfxclk, u8"FanTargetGfxclk",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanZeroRpmEnable, u8"FanZeroRpmEnable",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTachEdgePerRev, u8"FanTachEdgePerRev",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FuzzyFan_ErrorSetDelta, u8"FuzzyFan_ErrorSetDelta",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_ErrorRateSetDelta, u8"FuzzyFan_ErrorRateSetDelta",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_PwmSetDelta, u8"FuzzyFan_PwmSetDelta",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_Reserved, u8"FuzzyFan_Reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->OverrideAvfsGb[AVFS_VOLTAGE_GFX], u8"OverrideAvfsGb (GFX)",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->OverrideAvfsGb[AVFS_VOLTAGE_SOC], u8"OverrideAvfsGb (SOC)",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Padding8_Avfs, u8"Padding8_Avfs",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->qAvfsGb[AVFS_VOLTAGE_GFX], u8"qAvfsGb (GFX)",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		((LANG_ENG, u8"GHz->V Override of fused curve"))
	),
	(bios->qAvfsGb[AVFS_VOLTAGE_SOC], u8"qAvfsGb (SOC)",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		((LANG_ENG, u8"GHz->V Override of fused curve"))
	),

	(bios->dBtcGbGfxCksOn, u8"dBtcGbGfxCksOn",
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		(ATUI_NODESCR)
	),
	(bios->dBtcGbGfxCksOff, u8"dBtcGbGfxCksOff",
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		(ATUI_NODESCR)
	),
	(bios->dBtcGbGfxAfll, u8"dBtcGbGfxAfll",
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		((LANG_ENG, u8"dfll?"))
	),
	(bios->dBtcGbSoc, u8"dBtcGbSoc",
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		(ATUI_NODESCR)
	),
	(bios->qAgingGb[AVFS_VOLTAGE_GFX], u8"qAgingGb (GFX)",
		(ATUI_NAN, ATUI_INLINE, linear_f32),
		((LANG_ENG, u8"GHz->V"))
	),
	(bios->qAgingGb[AVFS_VOLTAGE_SOC], u8"qAgingGb (SOC)",
		(ATUI_NAN, ATUI_INLINE, linear_f32),
		((LANG_ENG, u8"GHz->V"))
	),

	(bios->qStaticVoltageOffset[AVFS_VOLTAGE_GFX], u8"qStaticVoltageOffset (GFX)",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		((LANG_ENG, u8"GHz->V"))
	),
	(bios->qStaticVoltageOffset[AVFS_VOLTAGE_SOC], u8"qStaticVoltageOffset (SOC)",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		((LANG_ENG, u8"GHz->V"))
	),


	(bios->DcTol[AVFS_VOLTAGE_GFX], u8"DcTol (GFX)",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV(Q2)"))
	),
	(bios->DcTol[AVFS_VOLTAGE_SOC], u8"DcTol (SOC)",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV(Q2)"))
	),


	(bios->DcBtcEnabled[AVFS_VOLTAGE_GFX], u8"DcBtcEnabled (GFX)",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DcBtcEnabled[AVFS_VOLTAGE_SOC], u8"DcBtcEnabled (SOC)",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Padding8_GfxBtc, u8"Padding8_GfxBtc",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->DcBtcMin[AVFS_VOLTAGE_GFX], u8"DcBtcMin (GFX)",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"mV(Q2)"))
	),
	(bios->DcBtcMin[AVFS_VOLTAGE_SOC], u8"DcBtcMin (SOC)",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"mV(Q2)"))
	),
	(bios->DcBtcMax[AVFS_VOLTAGE_GFX], u8"DcBtcMax (GFX)",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"mV(Q2)"))
	),
	(bios->DcBtcMax[AVFS_VOLTAGE_SOC], u8"DcBtcMax (SOC)",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"mV(Q2)"))
	),


	(bios->XgmiLinkSpeed, u8"XgmiLinkSpeed", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"XgmiLinkSpeed [%02u]",
				(ATUI_DEC, ATUI_ENUM, XGMI_LINK_RATE_e), (ATUI_NODESCR)
			),
			NULL, NUM_XGMI_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->XgmiLinkWidth, u8"XgmiLinkWidth", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"XgmiLinkWidth [%02u]",
				(ATUI_DEC, ATUI_ENUM, XGMI_LINK_WIDTH_e), (ATUI_NODESCR)
			),
			NULL, NUM_XGMI_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->XgmiFclkFreq, u8"XgmiFclkFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"XgmiFclkFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_XGMI_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->XgmiUclkFreq, u8"XgmiUclkFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"XgmiUclkFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_XGMI_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->XgmiSocclkFreq, u8"XgmiSocclkFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"XgmiSocclkFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_XGMI_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->XgmiSocVoltage, u8"XgmiSocVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"XgmiSocVoltage [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_XGMI_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->DebugOverrides, u8"DebugOverrides",
		(ATUI_NODISPLAY, ATUI_INLINE, dpm_debug_override_smu11_0x13),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation0, u8"ReservedEquation0",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation1, u8"ReservedEquation1",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation2, u8"ReservedEquation2",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation3, u8"ReservedEquation3",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),

	(bios->MinVoltageUlvGfx, u8"MinVoltageUlvGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2)  Minimum Voltage (\"Vmin\") of VDD_GFX in ULV mode"))
	),
	(bios->MinVoltageUlvSoc, u8"MinVoltageUlvSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2)  Minimum Voltage (\"Vmin\") of VDD_SOC in ULV mode"))
	),



	(bios->MGpuFanBoostLimitRpm, u8"MGpuFanBoostLimitRpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding16_Fan, u8"padding16_Fan",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FanGainVrMem0, u8"FanGainVrMem0",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainVrMem1, u8"FanGainVrMem1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->DcBtcGb[AVFS_VOLTAGE_GFX], u8"DcBtcGb (GFX)",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DcBtcGb[AVFS_VOLTAGE_SOC], u8"DcBtcGb (SOC)",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Reserved, u8"Reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->Padding32, u8"Padding32",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->MaxVoltageStepGfx, u8"MaxVoltageStepGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"n mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value."))
	),
	(bios->MaxVoltageStepSoc, u8"MaxVoltageStepSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value."))
	),

	(bios->VddGfxVrMapping, u8"VddGfxVrMapping",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->VddSocVrMapping, u8"VddSocVrMapping",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->VddMem0VrMapping, u8"VddMem0VrMapping",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->VddMem1VrMapping, u8"VddMem1VrMapping",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->GfxUlvPhaseSheddingMask, u8"GfxUlvPhaseSheddingMask",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->SocUlvPhaseSheddingMask, u8"SocUlvPhaseSheddingMask",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->ExternalSensorPresent, u8"ExternalSensorPresent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"External RDI connected to TMON (aka TEMP IN)"))
	),
	(bios->Padding8_V, u8"Padding8_V",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->GfxMaxCurrent, u8"GfxMaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->GfxOffset, u8"GfxOffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryGfx, u8"Padding_TelemetryGfx",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->SocMaxCurrent, u8"SocMaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->SocOffset, u8"SocOffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetrySoc, u8"Padding_TelemetrySoc",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem0MaxCurrent, u8"Mem0MaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Mem0Offset, u8"Mem0Offset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryMem0, u8"Padding_TelemetryMem0",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem1MaxCurrent, u8"Mem1MaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Mem1Offset, u8"Mem1Offset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryMem1, u8"Padding_TelemetryMem1",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->AcDcGpio, u8"AcDcGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for AC/DC switching"))
	),
	(bios->AcDcPolarity, u8"AcDcPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for AC/DC switching"))
	),
	(bios->VR0HotGpio, u8"VR0HotGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for VR0 HOT event"))
	),
	(bios->VR0HotPolarity, u8"VR0HotPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR0 HOT event"))
	),

	(bios->VR1HotGpio, u8"VR1HotGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for VR1 HOT event"))
	),
	(bios->VR1HotPolarity, u8"VR1HotPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR1 HOT event"))
	),
	(bios->Padding1, u8"Padding1",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for GTHR Event"))
	),
	(bios->Padding2, u8"Padding2",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"replace GPIO polarity for GTHR"))
	),


	(bios->LedPin0, u8"LedPin0",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[0]"))
	),
	(bios->LedPin1, u8"LedPin1",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[1]"))
	),
	(bios->LedPin2, u8"LedPin2",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[2]"))
	),
	(bios->padding8_4, u8"padding8_4",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->PllGfxclkSpreadEnabled, u8"PllGfxclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->PllGfxclkSpreadPercent, u8"PllGfxclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->PllGfxclkSpreadFreq, u8"PllGfxclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->UclkSpreadEnabled, u8"UclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->UclkSpreadPercent, u8"UclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->UclkSpreadFreq, u8"UclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->FclkSpreadEnabled, u8"FclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->FclkSpreadPercent, u8"FclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->FclkSpreadFreq, u8"FclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->FllGfxclkSpreadEnabled, u8"FllGfxclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->FllGfxclkSpreadPercent, u8"FllGfxclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->FllGfxclkSpreadFreq, u8"FllGfxclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->I2cControllers, u8"I2cControllers",
		(ATUI_NAN, ATUI_PETIOLE, smu11_smcpptable_v3_i2c_control),
		(ATUI_NODESCR)
	),


	(bios->BoardReserved, u8"BoardReserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->MmHubPadding, u8"MmHubPadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)





PPATUI_FUNCIFY(struct, smu11_smcpptable_v8, atomtree_powerplaytable, // Navi10
	(bios->Version, u8"Version",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->features, u8"features",
		(ATUI_NAN, ATUI_PETIOLE, powerplay_feature_control_smu11_0x33),
		(ATUI_NODESCR)
	),

	(bios->SocketPowerLimitAc, u8"SocketPowerLimitAc", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PPT %u",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PPT_THROTTLER_COUNT, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitAcTau, u8"SocketPowerLimitAcTau", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PPT %u",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PPT_THROTTLER_COUNT, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitDc, u8"SocketPowerLimitDc", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PPT %u",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PPT_THROTTLER_COUNT, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitDcTau, u8"SocketPowerLimitDcTau", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PPT %u",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PPT_THROTTLER_COUNT, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->TdcLimitSoc, u8"TdcLimitSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Amps"))
	),
	(bios->TdcLimitSocTau, u8"TdcLimitSocTau",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Time constant of LPF in ms"))
	),
	(bios->TdcLimitGfx, u8"TdcLimitGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Amps"))
	),
	(bios->TdcLimitGfxTau, u8"TdcLimitGfxTau",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Time constant of LPF in ms"))
	),

	(bios->TedgeLimit, u8"TedgeLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->ThotspotLimit, u8"ThotspotLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->TmemLimit, u8"TmemLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->Tvr_gfxLimit, u8"Tvr_gfxLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->Tvr_mem0Limit, u8"Tvr_mem0Limit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->Tvr_mem1Limit, u8"Tvr_mem1Limit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->Tvr_socLimit, u8"Tvr_socLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->Tliquid0Limit, u8"Tliquid0Limit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->Tliquid1Limit, u8"Tliquid1Limit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->TplxLimit, u8"TplxLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->FitLimit, u8"FitLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Failures in time (failures per million parts over the defined lifetime)"))
	),

	(bios->PpmPowerLimit, u8"PpmPowerLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Switch this this power limit when temperature is above PpmTempThreshold"))
	),
	(bios->PpmTemperatureThreshold, u8"PpmTemperatureThreshold",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->ThrottlerControlMask, u8"ThrottlerControlMask",
		(ATUI_NAN, ATUI_PETIOLE, throttler_control_smu11_0x33),
		(ATUI_NODESCR)
	),

	(bios->FwDStateMask, u8"FwDStateMask",
		(ATUI_NODISPLAY, ATUI_INLINE, fw_dstate_features_smu11_0x33),
		(ATUI_NODESCR)
	),

	(bios->UlvVoltageOffsetSoc, u8"UlvVoltageOffsetSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2)"))
	),
	(bios->UlvVoltageOffsetGfx, u8"UlvVoltageOffsetGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2)"))
	),

	(bios->GceaLinkMgrIdleThreshold, u8"GceaLinkMgrIdleThreshold",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Set by SMU FW during enablment of SOC_ULV. Controls delay for GFX SDP port disconnection during idle events"))
	),
	(bios->paddingRlcUlvParams, u8"paddingRlcUlvParams",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->UlvSmnclkDid, u8"UlvSmnclkDid",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"DID for ULV mode. 0 means CLK will not be modified in ULV."))
	),
	(bios->UlvMp1clkDid, u8"UlvMp1clkDid",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"DID for ULV mode. 0 means CLK will not be modified in ULV."))
	),
	(bios->UlvGfxclkBypass, u8"UlvGfxclkBypass",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"1 to turn off/bypass Gfxclk during ULV, 0 to leave Gfxclk on during ULV"))
	),
	(bios->Padding234, u8"Padding234",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->MinVoltageUlvGfx, u8"MinVoltageUlvGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2)  Minimum Voltage (\"Vmin\") of VDD_GFX in ULV mode"))
	),
	(bios->MinVoltageUlvSoc, u8"MinVoltageUlvSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2)  Minimum Voltage (\"Vmin\") of VDD_SOC in ULV mode"))
	),


	(bios->MinVoltageGfx, u8"MinVoltageGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Minimum Voltage (\"Vmin\") of VDD_GFX"))
	),
	(bios->MinVoltageSoc, u8"MinVoltageSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Minimum Voltage (\"Vmin\") of VDD_SOC"))
	),
	(bios->MaxVoltageGfx, u8"MaxVoltageGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Maximum Voltage allowable of VDD_GFX"))
	),
	(bios->MaxVoltageSoc, u8"MaxVoltageSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Maximum Voltage allowable of VDD_SOC"))
	),

	(bios->LoadLineResistanceGfx, u8"LoadLineResistanceGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mOhms with 8 fractional bits"))
	),
	(bios->LoadLineResistanceSoc, u8"LoadLineResistanceSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mOhms with 8 fractional bits"))
	),

	//struct dpm_descriptor_smu11 DpmDescriptor[SMU11_PPT8_PPCLK_COUNT];

	(bios->FreqTableGfx, u8"FreqTableGfx", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableGfx [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_GFXCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,u8"In MHz"))
	),
	(bios->FreqTableVclk, u8"FreqTableVclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableVclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_VCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,u8"In MHz"))
	),
	(bios->FreqTableDclk, u8"FreqTableDclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableDclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,u8"In MHz"))
	),
	(bios->FreqTableSocclk, u8"FreqTableSocclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableSocclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_SOCCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,u8"In MHz"))
	),
	(bios->FreqTableUclk, u8"FreqTableUclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableUclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,u8"In MHz"))
	),
	(bios->FreqTableDcefclk, u8"FreqTableDcefclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableDcefclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DCEFCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,u8"In MHz"))
	),
	(bios->FreqTableDispclk, u8"FreqTableDispclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableDispclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DISPCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,u8"In MHz"))
	),
	(bios->FreqTablePixclk, u8"FreqTablePixclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTablePixclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_PIXCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,u8"In MHz"))
	),
	(bios->FreqTablePhyclk, u8"FreqTablePhyclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTablePhyclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_PHYCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,u8"In MHz"))
	),
	(bios->Paddingclks, u8"Paddingclks",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->DcModeMaxFreq, u8"DcModeMaxFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"DcModeMaxFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU11_PPT8_PPCLK_COUNT, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,u8"In MHz"))
	),

	(bios->Padding8_Clks, u8"Padding8_Clks",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FreqTableUclkDiv, u8"FreqTableUclkDiv", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableUclkDiv [%02u]",
				(ATUI_DEC, ATUI_ENUM, UCLK_DIV_e), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->Mp0clkFreq, u8"Mp0clkFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Mp0clkFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_MP0CLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,u8"in MHz"))
	),
	(bios->Mp0DpmVoltage, u8"Mp0DpmVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Mp0DpmVoltage [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_MP0CLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,u8"mV(Q2)"))
	),
	(bios->MemVddciVoltage, u8"MemVddciVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"MemVddciVoltage [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,u8"mV(Q2)"))
	),
	(bios->MemMvddVoltage, u8"MemMvddVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"MemMvddVoltage [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,u8"mV(Q2)"))
	),
	(bios->GfxclkFgfxoffEntry, u8"GfxclkFgfxoffEntry",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Mhz"))
	),
	(bios->GfxclkFinit, u8"GfxclkFinit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Mhz"))
	),
	(bios->GfxclkFidle, u8"GfxclkFidle",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in MHz"))
	),
	(bios->GfxclkSlewRate, u8"GfxclkSlewRate",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"for PLL babystepping???"))
	),
	(bios->GfxclkFopt, u8"GfxclkFopt",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Mhz"))
	),
	(bios->Padding567, u8"Padding567",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->GfxclkDsMaxFreq, u8"GfxclkDsMaxFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in MHz"))
	),
	(bios->GfxclkSource, u8"GfxclkSource",
		(ATUI_DEC, ATUI_ENUM, GFXCLK_SOURCE_e),
		((LANG_ENG, u8"0 = PLL, 1 = DFLL"))
	),
	(bios->Padding456, u8"Padding456",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->LowestUclkReservedForUlv, u8"LowestUclkReservedForUlv",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Set this to 1 if UCLK DPM0 is reserved for ULV-mode only"))
	),
	(bios->paddingUclk, u8"paddingUclk",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->MemoryType, u8"MemoryType",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"0-GDDR6, 1-HBM"))
	),
	(bios->MemoryChannels, u8"MemoryChannels",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PaddingMem, u8"PaddingMem",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->PcieGenSpeed, u8"PcieGenSpeed", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PcieGenSpeed [%02u]",
				(ATUI_DEC, ATUI_ENUM, PCIE_SPEED_e), (ATUI_NODESCR)
			),
			NULL, NUM_LINK_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->PcieLaneCount, u8"PcieLaneCount", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PcieLaneCount [%02u]",
				(ATUI_DEC, ATUI_ENUM, PCIE_WIDTH_e), (ATUI_NODESCR)
			),
			NULL, NUM_LINK_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->LclkFreq, u8"LclkFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"LclkFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_LINK_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->EnableTdpm, u8"EnableTdpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TdpmHighHystTemperature, u8"TdpmHighHystTemperature",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TdpmLowHystTemperature, u8"TdpmLowHystTemperature",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxclkFreqHighTempLimit, u8"GfxclkFreqHighTempLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"High limit on GFXCLK when temperature is high, for reliability."))
	),

	(bios->FanStopTemp, u8"FanStopTemp",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->FanStartTemp, u8"FanStartTemp",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),

	(bios->FanGainEdge, u8"FanGainEdge",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainHotspot, u8"FanGainHotspot",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainLiquid0, u8"FanGainLiquid0",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainLiquid1, u8"FanGainLiquid1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainVrGfx, u8"FanGainVrGfx",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainVrSoc, u8"FanGainVrSoc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainVrMem0, u8"FanGainVrMem0",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainVrMem1, u8"FanGainVrMem1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainPlx, u8"FanGainPlx",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainMem, u8"FanGainMem",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanPwmMin, u8"FanPwmMin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanAcousticLimitRpm, u8"FanAcousticLimitRpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanThrottlingRpm, u8"FanThrottlingRpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanMaximumRpm, u8"FanMaximumRpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetTemperature, u8"FanTargetTemperature",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetGfxclk, u8"FanTargetGfxclk",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTempInputSelect, u8"FanTempInputSelect",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanPadding, u8"FanPadding",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanZeroRpmEnable, u8"FanZeroRpmEnable",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTachEdgePerRev, u8"FanTachEdgePerRev",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FuzzyFan_ErrorSetDelta, u8"FuzzyFan_ErrorSetDelta",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_ErrorRateSetDelta, u8"FuzzyFan_ErrorRateSetDelta",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_PwmSetDelta, u8"FuzzyFan_PwmSetDelta",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_Reserved, u8"FuzzyFan_Reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->OverrideAvfsGb[AVFS_VOLTAGE_GFX], u8"OverrideAvfsGb (GFX)",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->OverrideAvfsGb[AVFS_VOLTAGE_SOC], u8"OverrideAvfsGb (SOC)",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->Padding8_Avfs, u8"Padding8_Avfs",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->qAvfsGb[AVFS_VOLTAGE_GFX], u8"qAvfsGb (GFX)",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		((LANG_ENG, u8"GHz->V Override of fused curve"))
	),
	(bios->qAvfsGb[AVFS_VOLTAGE_SOC], u8"qAvfsGb (SOC)",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		((LANG_ENG, u8"GHz->V Override of fused curve"))
	),

	(bios->dBtcGbGfxPll, u8"dBtcGbGfxPll",
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		((LANG_ENG, u8"GHz->V BtcGb"))
	),
	(bios->dBtcGbGfxDfll, u8"dBtcGbGfxDfll",
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		((LANG_ENG, u8"GHz->V BtcGb"))
	),
	(bios->dBtcGbSoc, u8"dBtcGbSoc",
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		((LANG_ENG, u8"GHz->V BtcGb"))
	),
	(bios->qAgingGb[AVFS_VOLTAGE_GFX], u8"qAgingGb (GFX)",
		(ATUI_NAN, ATUI_INLINE, linear_f32),
		((LANG_ENG, u8"GHz->V"))
	),
	(bios->qAgingGb[AVFS_VOLTAGE_SOC], u8"qAgingGb (SOC)",
		(ATUI_NAN, ATUI_INLINE, linear_f32),
		((LANG_ENG, u8"GHz->V"))
	),

	(bios->qStaticVoltageOffset[AVFS_VOLTAGE_GFX], u8"qStaticVoltageOffset (GFX)",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		((LANG_ENG, u8"GHz->V"))
	),
	(bios->qStaticVoltageOffset[AVFS_VOLTAGE_SOC], u8"qStaticVoltageOffset (SOC)",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		((LANG_ENG, u8"GHz->V"))
	),

	(bios->DcTol[AVFS_VOLTAGE_GFX], u8"DcTol (GFX)",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV(Q2)"))
	),
	(bios->DcTol[AVFS_VOLTAGE_SOC], u8"DcTol (SOC)",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV(Q2)"))
	),

	(bios->DcBtcEnabled[AVFS_VOLTAGE_GFX], u8"DcBtcEnabled (GFX)",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DcBtcEnabled[AVFS_VOLTAGE_SOC], u8"DcBtcEnabled (SOC)",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Padding8_GfxBtc, u8"Padding8_GfxBtc",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->DcBtcMin[AVFS_VOLTAGE_GFX], u8"DcBtcMin (GFX)",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV(Q2)"))
	),
	(bios->DcBtcMin[AVFS_VOLTAGE_SOC], u8"DcBtcMin (SOC)",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV(Q2)"))
	),
	(bios->DcBtcMax[AVFS_VOLTAGE_GFX], u8"DcBtcMax (GFX)",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV(Q2)"))
	),
	(bios->DcBtcMax[AVFS_VOLTAGE_SOC], u8"DcBtcMax (SOC)",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV(Q2)"))
	),

	(bios->DebugOverrides, u8"DebugOverrides",
		(ATUI_NODISPLAY, ATUI_INLINE, dpm_debug_override_smu11_0x33),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation0, u8"ReservedEquation0",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation1, u8"ReservedEquation1",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation2, u8"ReservedEquation2",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation3, u8"ReservedEquation3",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),

	(bios->TotalPowerConfig, u8"TotalPowerConfig",
		(ATUI_DEC, ATUI_ENUM, PwrConfig_e), (ATUI_NODESCR)
	),
	(bios->TotalPowerSpare1, u8"TotalPowerSpare1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TotalPowerSpare2, u8"TotalPowerSpare2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->PccThresholdLow, u8"PccThresholdLow",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PccThresholdHigh, u8"PccThresholdHigh",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MGpuFanBoostLimitRpm, u8"MGpuFanBoostLimitRpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PaddingAPCC, u8"PaddingAPCC",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->VDDGFX_TVmin, u8"VDDGFX_TVmin",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->VDDSOC_TVmin, u8"VDDSOC_TVmin",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->VDDGFX_Vmin_HiTemp, u8"VDDGFX_Vmin_HiTemp",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV Q2"))
	),
	(bios->VDDGFX_Vmin_LoTemp, u8"VDDGFX_Vmin_LoTemp",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV Q2"))
	),
	(bios->VDDSOC_Vmin_HiTemp, u8"VDDSOC_Vmin_HiTemp",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV Q2"))
	),
	(bios->VDDSOC_Vmin_LoTemp, u8"VDDSOC_Vmin_LoTemp",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV Q2"))
	),

	(bios->VDDGFX_TVminHystersis, u8"VDDGFX_TVminHystersis",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->VDDSOC_TVminHystersis, u8"VDDSOC_TVminHystersis",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),

	(bios->BtcConfig, u8"BtcConfig",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->SsFmin, u8"SsFmin",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"PPtable value to function similar to VFTFmin for SS Curve; Size is SMU11_PPT8_PPCLK_COUNT rounded to nearest multiple of 2"))
	),
	(bios->DcBtcGb[AVFS_VOLTAGE_GFX], u8"DcBtcGb (GFX)",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DcBtcGb[AVFS_VOLTAGE_SOC], u8"DcBtcGb (SOC)",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->Reserved, u8"Reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->I2cControllers, u8"I2cControllers",
		(ATUI_NAN, ATUI_PETIOLE, smu11_smcpptable_v8_i2c_control),
		(ATUI_NODESCR)
	),

	(bios->MaxVoltageStepGfx, u8"MaxVoltageStepGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value."))
	),
	(bios->MaxVoltageStepSoc, u8"MaxVoltageStepSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value."))
	),

	(bios->VddGfxVrMapping, u8"VddGfxVrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),
	(bios->VddSocVrMapping, u8"VddSocVrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),
	(bios->VddMem0VrMapping, u8"VddMem0VrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),
	(bios->VddMem1VrMapping, u8"VddMem1VrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),

	(bios->GfxUlvPhaseSheddingMask, u8"GfxUlvPhaseSheddingMask",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->SocUlvPhaseSheddingMask, u8"SocUlvPhaseSheddingMask",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->ExternalSensorPresent, u8"ExternalSensorPresent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"External RDI connected to TMON (aka TEMP IN)"))
	),
	(bios->Padding8_V, u8"Padding8_V",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->GfxMaxCurrent, u8"GfxMaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->GfxOffset, u8"GfxOffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryGfx, u8"Padding_TelemetryGfx",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->SocMaxCurrent, u8"SocMaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->SocOffset, u8"SocOffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetrySoc, u8"Padding_TelemetrySoc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem0MaxCurrent, u8"Mem0MaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Mem0Offset, u8"Mem0Offset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryMem0, u8"Padding_TelemetryMem0",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem1MaxCurrent, u8"Mem1MaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Mem1Offset, u8"Mem1Offset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryMem1, u8"Padding_TelemetryMem1",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->AcDcGpio, u8"AcDcGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for AC/DC switching"))
	),
	(bios->AcDcPolarity, u8"AcDcPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for AC/DC switching"))
	),
	(bios->VR0HotGpio, u8"VR0HotGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for VR0 HOT event"))
	),
	(bios->VR0HotPolarity, u8"VR0HotPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR0 HOT event"))
	),

	(bios->VR1HotGpio, u8"VR1HotGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for VR1 HOT event"))
	),
	(bios->VR1HotPolarity, u8"VR1HotPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR1 HOT event"))
	),
	(bios->GthrGpio, u8"GthrGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for GTHR Event"))
	),
	(bios->GthrPolarity, u8"GthrPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"replace GPIO polarity for GTHR"))
	),

	(bios->LedPin0, u8"LedPin0",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[0]"))
	),
	(bios->LedPin1, u8"LedPin1",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[1]"))
	),
	(bios->LedPin2, u8"LedPin2",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[2]"))
	),
	(bios->padding8_4, u8"padding8_4",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->PllGfxclkSpreadEnabled, u8"PllGfxclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->PllGfxclkSpreadPercent, u8"PllGfxclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->PllGfxclkSpreadFreq, u8"PllGfxclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->DfllGfxclkSpreadEnabled, u8"DfllGfxclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->DfllGfxclkSpreadPercent, u8"DfllGfxclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->DfllGfxclkSpreadFreq, u8"DfllGfxclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->UclkSpreadEnabled, u8"UclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->UclkSpreadPercent, u8"UclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->UclkSpreadFreq, u8"UclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->SoclkSpreadEnabled, u8"SoclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->SocclkSpreadPercent, u8"SocclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->SocclkSpreadFreq, u8"SocclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->TotalBoardPower, u8"TotalBoardPower",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Only needed for TCP Estimated case, where TCP = TGP+Total Board Power"))
	),
	(bios->BoardPadding, u8"BoardPadding",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->MvddRatio, u8"MvddRatio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"This is used for MVDD Vid workaround. It has 16 fractional bits (Q16.16)"))
	),

	(bios->RenesesLoadLineEnabled, u8"RenesesLoadLineEnabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxLoadlineResistance, u8"GfxLoadlineResistance",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocLoadlineResistance, u8"SocLoadlineResistance",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding8_Loadline, u8"Padding8_Loadline",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->BoardReserved, u8"BoardReserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->MmHubPadding, u8"MmHubPadding",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"SMU internal use"))
	)
)


PPATUI_FUNCIFY(struct, smu11_smcpptable_v7_infrastructure_limits,
		atui_nullstruct,
	(bios->SocketPowerLimitAc, u8"SocketPowerLimitAc", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"SocketPowerLimitAc [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PPT_THROTTLER_COUNT, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"Watts"))
	),
	(bios->SocketPowerLimitAcTau, u8"SocketPowerLimitAcTau", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"SocketPowerLimitAcTau [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PPT_THROTTLER_COUNT, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"Time constant of LPF in ms"))
	),
	(bios->SocketPowerLimitDc, u8"SocketPowerLimitDc", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"SocketPowerLimitDc [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PPT_THROTTLER_COUNT, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"Watts"))
	),
	(bios->SocketPowerLimitDcTau, u8"SocketPowerLimitDcTau", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"SocketPowerLimitDcTau [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PPT_THROTTLER_COUNT, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"Time constant of LPF in ms"))
	),

	(bios->TdcLimit, u8"TdcLimit", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"TdcLimit [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, TDC_THROTTLER_COUNT_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"Amps"))
	),
	(bios->TdcLimitTau, u8"TdcLimitTau", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"TdcLimitTau [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, TDC_THROTTLER_COUNT_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"Time constant of LPF in ms"))
	),

	(bios->TemperatureLimit, u8"TemperatureLimit", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, TEMP_SMU_11_0_7_COUNT, // deferred start, count
			TEMP_SMU11_0_7_e // enum
		)),
		((LANG_ENG, u8"Celcius"))
	),

	(bios->FitLimit, u8"FitLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Failures in time (failures per million parts over the defined lifetime)"))
	)
)


PPATUI_FUNCIFY(struct, smu11_smcpptable_v7_dpm_freq_tables, atui_nullstruct,
	(bios->FreqTableGfx, u8"FreqTableGfx", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableGfx [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_GFXCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableVclk, u8"FreqTableVclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableVclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_VCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableDclk, u8"FreqTableDclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableDclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableSocclk, u8"FreqTableSocclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableSocclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_SOCCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableUclk, u8"FreqTableUclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableUclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableDcefclk, u8"FreqTableDcefclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableDcefclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DCEFCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableDispclk, u8"FreqTableDispclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableDispclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DISPCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTablePixclk, u8"FreqTablePixclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTablePixclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_PIXCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTablePhyclk, u8"FreqTablePhyclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTablePhyclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_PHYCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableDtbclk, u8"FreqTableDtbclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableDtbclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DTBCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableFclk, u8"FreqTableFclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableFclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_FCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	)
)

PPATUI_FUNCIFY(struct, smu11_smcpptable_v7_dpm_config, atui_nullstruct,
	(bios->DpmDescriptor, u8"DpmDescriptor", // start, name
		(ATUI_NODISPLAY, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_NAN, ATUI_PETIOLE, dpm_descriptor_smu11_0x40),
				(ATUI_NODESCR)
			),
			NULL, SMU11_PPT7_PPCLK_COUNT, // deferred start, count
			SMU11_PPT7_PPCLK_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->freq_tables, u8"freq_tables",
		(ATUI_NAN, ATUI_PETIOLE, smu11_smcpptable_v7_dpm_freq_tables),
		(ATUI_NODESCR)
	),

	(bios->Paddingclks, u8"Paddingclks",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->PerPartDroopModelGfxDfll, u8"PerPartDroopModelGfxDfll", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PerPartDroopModelGfxDfll [%02u]",
				(ATUI_NAN, ATUI_INLINE, droop_f32),
				(ATUI_NODESCR)
			),
			NULL, // deferred start,
			NUM_PIECE_WISE_LINEAR_DROOP_MODEL_VF_POINTS, // count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"GHz ->V"))
	),

	(bios->DcModeMaxFreq, u8"DcModeMaxFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU11_PPT7_PPCLK_COUNT, // deferred start, count
			SMU11_PPT7_PPCLK_e // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),

	(bios->FreqTableUclkDiv, u8"FreqTableUclkDiv", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableUclkDiv [%02u]",
				(ATUI_DEC, ATUI_ENUM, UCLK_DIV_e), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->FclkBoostFreq, u8"FclkBoostFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In Mhz"))
	),
	(bios->FclkParamPadding, u8"FclkParamPadding",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mp0clkFreq, u8"Mp0clkFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Mp0clkFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_MP0CLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"in MHz"))
	),
	(bios->Mp0DpmVoltage, u8"Mp0DpmVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Mp0DpmVoltage [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_MP0CLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"mV(Q2)"))
	),
	(bios->MemVddciVoltage, u8"MemVddciVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"MemVddciVoltage [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"mV(Q2)"))
	),
	(bios->MemMvddVoltage, u8"MemMvddVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"MemMvddVoltage [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"mV(Q2)"))
	),
	(bios->GfxclkFgfxoffEntry, u8"GfxclkFgfxoffEntry",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Mhz"))
	),
	(bios->GfxclkFinit, u8"GfxclkFinit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Mhz"))
	),
	(bios->GfxclkFidle, u8"GfxclkFidle",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in MHz"))
	),
	(bios->GfxclkSource, u8"GfxclkSource",
		(ATUI_DEC, ATUI_ENUM, GFXCLK_SOURCE_e),
		((LANG_ENG, u8"0 = PLL, 1 = DFLL"))
	),
	(bios->GfxclkPadding, u8"GfxclkPadding",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->GfxGpoSubFeatureMask, u8"GfxGpoSubFeatureMask",
		(ATUI_NAN, ATUI_INLINE, gfx_gpo_features),
		(ATUI_NODESCR)
	),
	(bios->GfxGpoEnabledWorkPolicyMask, u8"GfxGpoEnabledWorkPolicyMask",
		(ATUI_NAN, ATUI_INLINE, gfx_gpo_features),
		((LANG_ENG, u8"Any policy that GPO can be enabled"))
	),
	(bios->GfxGpoDisabledWorkPolicyMask, u8"GfxGpoDisabledWorkPolicyMask",
		(ATUI_NAN, ATUI_INLINE, gfx_gpo_features),
		((LANG_ENG, u8"Any policy that GPO can be disabled"))
	),
	(bios->GfxGpoPadding, u8"GfxGpoPadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->GfxGpoVotingAllow, u8"GfxGpoVotingAllow",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"For indicating which feature changes should result in a GPO table recalculation"))
	),

	(bios->GfxGpoPadding32, u8"GfxGpoPadding32",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->GfxDcsFopt, u8"GfxDcsFopt",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Optimal GFXCLK for DCS in Mhz"))
	),
	(bios->GfxDcsFclkFopt, u8"GfxDcsFclkFopt",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Optimal FCLK for DCS in Mhz"))
	),
	(bios->GfxDcsUclkFopt, u8"GfxDcsUclkFopt",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Optimal UCLK for DCS in Mhz"))
	),

	(bios->DcsGfxOffVoltage, u8"DcsGfxOffVoltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Voltage in mV(Q2) applied to VDDGFX when entering DCS GFXOFF phase"))
	),

	(bios->DcsMinGfxOffTime, u8"DcsMinGfxOffTime",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Minimum amount of time PMFW shuts GFX OFF as part of GFX DCS phase"))
	),
	(bios->DcsMaxGfxOffTime, u8"DcsMaxGfxOffTime",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Maximum amount of time PMFW can shut GFX OFF as part of GFX DCS phase at a stretch."))
	),

	(bios->DcsMinCreditAccum, u8"DcsMinCreditAccum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Min amount of positive credit accumulation before waking GFX up as part of DCS."))
	),

	(bios->DcsExitHysteresis, u8"DcsExitHysteresis",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"The min amount of time power credit accumulator should have a value > 0 before SMU exits the DCS throttling phase."))
	),
	(bios->DcsTimeout, u8"DcsTimeout",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"This is the amount of time SMU FW waits for RLC to put GFX into GFXOFF before reverting to the fallback mechanism of throttling GFXCLK to Fmin."))
	),

	(bios->DcsParamPadding, u8"DcsParamPadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->FlopsPerByteTable, u8"FlopsPerByteTable", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FlopsPerByteTable [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, RLC_PACE_TABLE_NUM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"Q8.8"))
	),

	(bios->LowestUclkReservedForUlv, u8"LowestUclkReservedForUlv",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Set this to 1 if UCLK DPM0 is reserved for ULV-mode only"))
	),
	(bios->PaddingMem, u8"PaddingMem",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->UclkDpmPstates, u8"UclkDpmPstates", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"UclkDpmPstates [%02u]",
				(ATUI_DEC, ATUI_ENUM, DPM_PSTATES_e),
				(ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"4 DPM states."))
	),

	(bios->UclkDpmSrcFreqRange, u8"UclkDpmSrcFreqRange",
		(ATUI_NAN, ATUI_INLINE, UclkDpmChangeRange_t),
		((LANG_ENG, u8"In Mhz"))
	),
	(bios->UclkDpmTargFreqRange, u8"UclkDpmTargFreqRange",
		(ATUI_NAN, ATUI_INLINE, UclkDpmChangeRange_t),
		((LANG_ENG, u8"In Mhz"))
	),
	(bios->UclkDpmMidstepFreq, u8"UclkDpmMidstepFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In Mhz"))
	),
	(bios->UclkMidstepPadding, u8"UclkMidstepPadding",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->PcieGenSpeed, u8"PcieGenSpeed", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PcieGenSpeed [%02u]",
				(ATUI_DEC, ATUI_ENUM, PCIE_SPEED_e),
				(ATUI_NODESCR)
			),
			NULL, NUM_LINK_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->PcieLaneCount, u8"PcieLaneCount", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PcieLaneCount [%02u]",
				(ATUI_DEC, ATUI_ENUM, PCIE_WIDTH_e),
				(ATUI_NODESCR)
			),
			NULL, NUM_LINK_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->LclkFreq, u8"LclkFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"LclkFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_LINK_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	)

)
PPATUI_FUNCIFY(struct, smu11_smcpptable_v7_fan_control, atui_nullstruct,
	(bios->FanStopTemp, u8"FanStopTemp",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->FanStartTemp, u8"FanStartTemp",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),

	(bios->FanGain, u8"FanGain", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, TEMP_SMU_11_0_7_COUNT, // deferred start, count
			TEMP_SMU11_0_7_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->FanPwmMin, u8"FanPwmMin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanAcousticLimitRpm, u8"FanAcousticLimitRpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanThrottlingRpm, u8"FanThrottlingRpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanMaximumRpm, u8"FanMaximumRpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MGpuFanBoostLimitRpm, u8"MGpuFanBoostLimitRpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetTemperature, u8"FanTargetTemperature",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetGfxclk, u8"FanTargetGfxclk",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanPadding16, u8"FanPadding16",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTempInputSelect, u8"FanTempInputSelect",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanPadding, u8"FanPadding",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanZeroRpmEnable, u8"FanZeroRpmEnable",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTachEdgePerRev, u8"FanTachEdgePerRev",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FuzzyFan_ErrorSetDelta, u8"FuzzyFan_ErrorSetDelta",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_ErrorRateSetDelta, u8"FuzzyFan_ErrorRateSetDelta",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_PwmSetDelta, u8"FuzzyFan_PwmSetDelta",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_Reserved, u8"FuzzyFan_Reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, smu11_smcpptable_v7_avfs, atui_nullstruct,
	(bios->OverrideAvfsGb, u8"OverrideAvfsGb", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, AVFS_VOLTAGE_COUNT, // deferred start, count
			AVFS_VOLTAGE_TYPE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->dBtcGbGfxDfllModelSelect, u8"dBtcGbGfxDfllModelSelect",
		(ATUI_DEC, ATUI_ENUM, DfllDroopModelSelect_e),
		(ATUI_NODESCR)
	),
	(bios->Padding8_Avfs, u8"Padding8_Avfs",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->qAvfsGb, u8"qAvfsGb", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"qAvfsGb: %s",
				(ATUI_NAN, ATUI_INLINE, quadratic_f32),
				(ATUI_NODESCR)
			),
			NULL, AVFS_VOLTAGE_COUNT, // deferred start, count
			AVFS_VOLTAGE_TYPE_e // enum
		)),
		((LANG_ENG, u8"GHz->V Override of fused curve"))
	),
	(bios->dBtcGbGfxPll, u8"dBtcGbGfxPll",
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		((LANG_ENG, u8"GHz->V BtcGb"))
	),
	(bios->dBtcGbGfxDfll, u8"dBtcGbGfxDfll",
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		((LANG_ENG, u8"GHz->V BtcGb"))
	),
	(bios->dBtcGbSoc, u8"dBtcGbSoc",
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		((LANG_ENG, u8"GHz->V BtcGb"))
	),
	(bios->qAgingGb, u8"qAgingGb", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_NAN, ATUI_INLINE, linear_f32),
				(ATUI_NODESCR)
			),
			NULL, AVFS_VOLTAGE_COUNT, // deferred start, count
			AVFS_VOLTAGE_TYPE_e // enum
		)),
		((LANG_ENG, u8"GHz->V"))
	),

	(bios->PiecewiseLinearDroopIntGfxDfll, u8"PiecewiseLinearDroopIntGfxDfll",
		(ATUI_NAN, ATUI_INLINE, PiecewiseLinearDroopInt_t),
		((LANG_ENG, u8"GHz ->V"))
	),

	(bios->qStaticVoltageOffset, u8"qStaticVoltageOffset", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_NAN, ATUI_INLINE, quadratic_f32),
				(ATUI_NODESCR)
			),
			NULL, AVFS_VOLTAGE_COUNT, // deferred start, count
			AVFS_VOLTAGE_TYPE_e // enum
		)),
		((LANG_ENG, u8"GHz->V"))
	),

	(bios->DcTol, u8"DcTol", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, AVFS_VOLTAGE_COUNT, // deferred start, count
			AVFS_VOLTAGE_TYPE_e // enum
		)),
		((LANG_ENG, u8"mV Q2"))
	),

	(bios->DcBtcEnabled, u8"DcBtcEnabled", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, AVFS_VOLTAGE_COUNT, // deferred start, count
			AVFS_VOLTAGE_TYPE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->Padding8_GfxBtc, u8"Padding8_GfxBtc",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->DcBtcMin, u8"DcBtcMin", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, AVFS_VOLTAGE_COUNT, // deferred start, count
			AVFS_VOLTAGE_TYPE_e // enum
		)),
		((LANG_ENG, u8"mV Q2"))
	),
	(bios->DcBtcMax, u8"DcBtcMax", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, AVFS_VOLTAGE_COUNT, // deferred start, count
			AVFS_VOLTAGE_TYPE_e // enum
		)),
		((LANG_ENG, u8"mV Q2"))
	),

	(bios->DcBtcGb, u8"DcBtcGb", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, AVFS_VOLTAGE_COUNT, // deferred start, count
			AVFS_VOLTAGE_TYPE_e // enum
		)),
		((LANG_ENG, u8"mV Q2"))
	)
)

PPATUI_FUNCIFY(struct, smu11_smcpptable_v7_i2c_control, atui_nullstruct,
	(bios->I2cControllers, u8"Supported I2cControllers", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_NAN, ATUI_PETIOLE, i2ccontrollerconfig_u8),
				(ATUI_NODESCR)
			),
			NULL, // deferred start
			I2C_CONTROLLER_NAME_COUNT_SMU11_PPT7, // count
			I2cControllerName_SMU_11_0_7_e // enum
		)), (ATUI_NODESCR)
	),
	((&(bios->I2cControllers[I2C_CONTROLLER_NAME_COUNT_SMU11_PPT7])), // start
		u8"Undefined I2cControllers", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"I2cControllers [8 + %02u]",
					// if COUNT changes, please change this 8
				(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u8),
				(ATUI_NODESCR)
			),
			NULL, // deferred start
			(NUM_I2C_CONTROLLERS_SMU11_0_7
				- I2C_CONTROLLER_NAME_COUNT_SMU11_PPT7
			), // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),


	(bios->GpioScl, u8"GpioScl",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO Number for SCL Line, used only for CKSVII2C1"))
	),
	(bios->GpioSda, u8"GpioSda",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO Number for SDA Line, used only for CKSVII2C1"))
	),
	(bios->FchUsbPdSlaveAddr, u8"FchUsbPdSlaveAddr",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"For requesting USB PD controller S-states via FCH I2C when entering PME turn off"))
	),
	(bios->I2cSpare, u8"I2cSpare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, smu11_smcpptable_v7, atui_nullstruct,

	(bios->Version, u8"Version",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->features, u8"features",
		(ATUI_NAN, ATUI_PETIOLE, powerplay_feature_control_smu11_0x40),
		(ATUI_NODESCR)
	),

	(bios->infrastructure_limits, u8"infrastructure_limits",
		(ATUI_NAN, ATUI_PETIOLE, smu11_smcpptable_v7_infrastructure_limits),
		(ATUI_NODESCR)
	),


	(bios->TotalPowerConfig, u8"TotalPowerConfig",
		(ATUI_DEC, ATUI_ENUM, PwrConfig_e),
		((LANG_ENG, u8"Determines how PMFW calculates the power."))
	),
	(bios->TotalPowerPadding, u8"TotalPowerPadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->ApccPlusResidencyLimit, u8"ApccPlusResidencyLimit",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->SmnclkDpmFreq, u8"SmnclkDpmFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"SmnclkDpmFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_SMNCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"in MHz"))
	),
	(bios->SmnclkDpmVoltage, u8"SmnclkDpmVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"SmnclkDpmVoltage [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_SMNCLK_DPM_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"mV(Q2)"))
	),

	(bios->PaddingAPCC, u8"PaddingAPCC",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PerPartDroopVsetGfxDfll, u8"PerPartDroopVsetGfxDfll", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PerPartDroopVsetGfxDfll [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			NUM_PIECE_WISE_LINEAR_DROOP_MODEL_VF_POINTS, // count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In mV(Q2)"))
	),
	(bios->PaddingPerPartDroop, u8"PaddingPerPartDroop",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->ThrottlerControlMask, u8"ThrottlerControlMask",
		(ATUI_NAN, ATUI_PETIOLE, throttler_control_smu11_0x40),
		(ATUI_NODESCR)
	),

	(bios->FwDStateMask, u8"FwDStateMask",
		(ATUI_NAN, ATUI_PETIOLE, fw_dstate_features_smu11_0x40),
		(ATUI_NODESCR)
	),

	(bios->UlvVoltageOffsetSoc, u8"UlvVoltageOffsetSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2)"))
	),
	(bios->UlvVoltageOffsetGfx, u8"UlvVoltageOffsetGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2)"))
	),

	(bios->MinVoltageUlvGfx, u8"MinVoltageUlvGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2)  Minimum Voltage ("Vminu8") of VDD_GFX in ULV mode"))
	),
	(bios->MinVoltageUlvSoc, u8"MinVoltageUlvSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2)  Minimum Voltage ("Vminu8") of VDD_SOC in ULV mode"))
	),

	(bios->SocLIVmin, u8"SocLIVmin",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2)  Long Idle Vmin (deep ULV), for VDD_SOC"))
	),
	(bios->PaddingLIVmin, u8"PaddingLIVmin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->GceaLinkMgrIdleThreshold, u8"GceaLinkMgrIdleThreshold",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Set by SMU FW during enablment of GFXOFF. Controls delay for GFX SDP port disconnection during idle events"))
	),
	(bios->paddingRlcUlvParams, u8"paddingRlcUlvParams",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->MinVoltageGfx, u8"MinVoltageGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Minimum Voltage (\"Vmin\") of VDD_GFX"))
	),
	(bios->MinVoltageSoc, u8"MinVoltageSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Minimum Voltage (\"Vmin\") of VDD_SOC"))
	),
	(bios->MaxVoltageGfx, u8"MaxVoltageGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Maximum Voltage allowable of VDD_GFX"))
	),
	(bios->MaxVoltageSoc, u8"MaxVoltageSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Maximum Voltage allowable of VDD_SOC"))
	),

	(bios->LoadLineResistanceGfx, u8"LoadLineResistanceGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mOhms Q8.8 with 8 fractional bits"))
	),
	(bios->LoadLineResistanceSoc, u8"LoadLineResistanceSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mOhms with 8 fractional bits"))
	),

	(bios->VDDGFX_TVmin, u8"VDDGFX_TVmin",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->VDDSOC_TVmin, u8"VDDSOC_TVmin",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->VDDGFX_Vmin_HiTemp, u8"VDDGFX_Vmin_HiTemp",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV Q2"))
	),
	(bios->VDDGFX_Vmin_LoTemp, u8"VDDGFX_Vmin_LoTemp",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV Q2"))
	),
	(bios->VDDSOC_Vmin_HiTemp, u8"VDDSOC_Vmin_HiTemp",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV Q2"))
	),
	(bios->VDDSOC_Vmin_LoTemp, u8"VDDSOC_Vmin_LoTemp",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV Q2"))
	),

	(bios->VDDGFX_TVminHystersis, u8"VDDGFX_TVminHystersis",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),
	(bios->VDDSOC_TVminHystersis, u8"VDDSOC_TVminHystersis",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Celcius"))
	),

	(bios->dpm_config, u8"dpm_config",
		(ATUI_NAN, ATUI_PETIOLE, smu11_smcpptable_v7_dpm_config),
		(ATUI_NODESCR)
	),
	(bios->fan_control, u8"fan_control",
		(ATUI_NAN, ATUI_PETIOLE, smu11_smcpptable_v7_fan_control),
		(ATUI_NODESCR)
	),
	(bios->avfs, u8"avfs",
		(ATUI_NAN, ATUI_PETIOLE, smu11_smcpptable_v7_avfs),
		(ATUI_NODESCR)
	),

	(bios->XgmiDpmPstates, u8"XgmiDpmPstates", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"XgmiDpmPstates [%02u]",
				(ATUI_DEC, ATUI_ENUM, DPM_PSTATES_e),
				(ATUI_NODESCR)
			),
			NULL, NUM_XGMI_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"2 DPM states, high and low."))
	),
	(bios->XgmiDpmSpare, u8"XgmiDpmSpare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->DebugOverrides, u8"DebugOverrides",
		(ATUI_NODISPLAY, ATUI_INLINE, dpm_debug_override_smu11_0x40),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation0, u8"ReservedEquation0",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation1, u8"ReservedEquation1",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation2, u8"ReservedEquation2",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation3, u8"ReservedEquation3",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),

	(bios->CustomerVariant, u8"CustomerVariant",
		(ATUI_DEC, ATUI_ENUM, CUSTOMER_VARIANT_e),
		(ATUI_NODESCR)
	),

	(bios->VcBtcEnabled, u8"VcBtcEnabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->VcBtcVminT0, u8"VcBtcVminT0",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"T0_VMIN"))
	),
	(bios->VcBtcFixedVminAgingOffset, u8"VcBtcFixedVminAgingOffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"FIXED_VMIN_AGING_OFFSET"))
	),
	(bios->VcBtcVmin2PsmDegrationGb, u8"VcBtcVmin2PsmDegrationGb",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"VMIN_TO_PSM_DEGRADATION_GB"))
	),
	(bios->VcBtcPsmA, u8"VcBtcPsmA",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"A_PSM"))
	),
	(bios->VcBtcPsmB, u8"VcBtcPsmB",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"B_PSM"))
	),
	(bios->VcBtcVminA, u8"VcBtcVminA",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"A_VMIN"))
	),
	(bios->VcBtcVminB, u8"VcBtcVminB",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"B_VMIN"))
	),

	(bios->LedGpio, u8"LedGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GeneriA GPIO flag used to control the radeon LEDs"))
	),
	(bios->GfxPowerStagesGpio, u8"GfxPowerStagesGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Genlk_vsync GPIO flag used to control gfx power stages"))
	),

	(bios->SkuReserved, u8"SkuReserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),


	(bios->GamingClk, u8"GamingClk",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->i2c_control, u8"i2c_control",
		(ATUI_NAN, ATUI_PETIOLE, smu11_smcpptable_v7_i2c_control),
		(ATUI_NODESCR)
	),


	(bios->VddGfxVrMapping, u8"VddGfxVrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),
	(bios->VddSocVrMapping, u8"VddSocVrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),
	(bios->VddMem0VrMapping, u8"VddMem0VrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),
	(bios->VddMem1VrMapping, u8"VddMem1VrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),

	(bios->GfxUlvPhaseSheddingMask, u8"GfxUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->SocUlvPhaseSheddingMask, u8"SocUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->VddciUlvPhaseSheddingMask, u8"VddciUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->MvddUlvPhaseSheddingMask, u8"MvddUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),

	(bios->GfxMaxCurrent, u8"GfxMaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->GfxOffset, u8"GfxOffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryGfx, u8"Padding_TelemetryGfx",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->SocMaxCurrent, u8"SocMaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->SocOffset, u8"SocOffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetrySoc, u8"Padding_TelemetrySoc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem0MaxCurrent, u8"Mem0MaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Mem0Offset, u8"Mem0Offset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryMem0, u8"Padding_TelemetryMem0",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem1MaxCurrent, u8"Mem1MaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Mem1Offset, u8"Mem1Offset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryMem1, u8"Padding_TelemetryMem1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->MvddRatio, u8"MvddRatio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"This is used for MVDD  Svi2 Div Ratio workaround. It has 16 fractional bits (Q16.16)"))
	),

	(bios->AcDcGpio, u8"AcDcGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for AC/DC switching"))
	),
	(bios->AcDcPolarity, u8"AcDcPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for AC/DC switching"))
	),
	(bios->VR0HotGpio, u8"VR0HotGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for VR0 HOT event"))
	),
	(bios->VR0HotPolarity, u8"VR0HotPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR0 HOT event"))
	),

	(bios->VR1HotGpio, u8"VR1HotGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for VR1 HOT event"))
	),
	(bios->VR1HotPolarity, u8"VR1HotPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR1 HOT event"))
	),
	(bios->GthrGpio, u8"GthrGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for GTHR Event"))
	),
	(bios->GthrPolarity, u8"GthrPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"replace GPIO polarity for GTHR"))
	),

	(bios->LedPin0, u8"LedPin0",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[0]"))
	),
	(bios->LedPin1, u8"LedPin1",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[1]"))
	),
	(bios->LedPin2, u8"LedPin2",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[2]"))
	),
	(bios->LedEnableMask, u8"LedEnableMask",
		(ATUI_NAN, ATUI_INLINE, led_display_control),
		(ATUI_NODESCR)
	),

	(bios->LedPcie, u8"LedPcie",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for PCIE results"))
	),
	(bios->LedError, u8"LedError",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for Error Cases"))
	),
	(bios->LedSpare1, u8"LedSpare1",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),


	(bios->PllGfxclkSpreadEnabled, u8"PllGfxclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->PllGfxclkSpreadPercent, u8"PllGfxclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->PllGfxclkSpreadFreq, u8"PllGfxclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->DfllGfxclkSpreadEnabled, u8"DfllGfxclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->DfllGfxclkSpreadPercent, u8"DfllGfxclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->DfllGfxclkSpreadFreq, u8"DfllGfxclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->UclkSpreadPadding, u8"UclkSpreadPadding",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->UclkSpreadFreq, u8"UclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->FclkSpreadEnabled, u8"FclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->FclkSpreadPercent, u8"FclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->FclkSpreadFreq, u8"FclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->MemoryChannelEnabled, u8"MemoryChannelEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"For DRAM use only, Max 32 channels enabled bit mask."))
	),

	(bios->DramBitWidth, u8"DramBitWidth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"For DRAM use only.  See Dram Bit width type defines"))
	),
	(bios->PaddingMem1, u8"PaddingMem1",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->TotalBoardPower, u8"TotalBoardPower",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Only needed for TCP Estimated case, where TCP = TGP+Total Board Power"))
	),
	(bios->BoardPowerPadding, u8"BoardPowerPadding",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->XgmiLinkSpeed, u8"XgmiLinkSpeed", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"XgmiLinkSpeed [%02u]",
				(ATUI_DEC, ATUI_ENUM, XGMI_LINK_RATE_e),
				(ATUI_NODESCR)
			),
			NULL, NUM_XGMI_PSTATE_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->XgmiLinkWidth, u8"XgmiLinkWidth", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"XgmiLinkWidth [%02u]",
				(ATUI_DEC, ATUI_ENUM, XGMI_LINK_WIDTH_e),
				(ATUI_NODESCR)
			),
			NULL, NUM_XGMI_PSTATE_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->XgmiFclkFreq, u8"XgmiFclkFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"XgmiFclkFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_XGMI_PSTATE_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->XgmiSocVoltage, u8"XgmiSocVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"XgmiSocVoltage [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_XGMI_PSTATE_LEVELS_SMU11, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->HsrEnabled, u8"HsrEnabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->VddqOffEnabled, u8"VddqOffEnabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PaddingUmcFlags, u8"PaddingUmcFlags",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->UclkSpreadPercent, u8"UclkSpreadPercent", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"UclkSpreadPercent [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			// count:
			sizeof(bios->UclkSpreadPercent)/sizeof(bios->UclkSpreadPercent[0]),
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->BoardReserved, u8"BoardReserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),


	(bios->MmHubPadding, u8"MmHubPadding",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"SMU internal use"))
	)
)





PPATUI_FUNCIFY(struct, smu_11_0_powerplay_table, atomtree_powerplaytable,
	(bios->header, u8"header",
		(ATUI_NAN, ATUI_INLINE, smu_powerplay_table_header),
		(ATUI_NODESCR)
	),
	(bios->golden_pp_id, u8"golden_pp_id",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->golden_revision, u8"golden_revision",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->format_id, u8"format_id",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->platform_caps.platform_caps, u8"platform_caps",
		(ATUI_NODISPLAY, ATUI_INLINE, powerplay_platform_caps),
		(ATUI_NODESCR)
	),
	(bios->thermal_controller_type, u8"thermal_controller_type",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"one of SMU_11_0_PP_THERMALCONTROLLER"))
	),
	(bios->small_power_limit1, u8"small_power_limit1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->small_power_limit2, u8"small_power_limit2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->boost_power_limit, u8"boost_power_limit",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->od_turbo_power_limit, u8"od_turbo_power_limit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Power limit setting for Turbo mode in Performance UI Tuning."))
	),
	(bios->od_power_save_power_limit, u8"od_power_save_power_limit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Power limit setting for PowerSave/Optimal mode in Performance UI Tuning."))
	),
	(bios->software_shutdown_temp, u8"software_shutdown_temp",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->reserve, u8"reserve",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"Zero filled field reserved for future use"))
	),

	(bios->power_saving_clock, u8"power_saving_clock",
		(ATUI_NAN, ATUI_PETIOLE, smu_11_0_power_saving_clock_table),
		(ATUI_NODESCR)
	),
	(bios->overdrive_table, u8"overdrive_table",
		(ATUI_NAN, ATUI_PETIOLE, smu_11_0_overdrive_table),
		(ATUI_NODESCR)
	)

)

PPATUI_FUNCIFY(struct, smu_11_0_7_powerplay_table, atui_nullstruct,
	(bios->header, u8"header",
		(ATUI_NAN, ATUI_INLINE, smu_powerplay_table_header),
		(ATUI_NODESCR)
	),
	(bios->golden_pp_id, u8"golden_pp_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"PPGen use only: PP Table ID on the Golden Data Base"))
	),
	(bios->golden_revision, u8"golden_revision",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"PPGen use only: PP Table Revision on the Golden Data Base"))
	),
	(bios->format_id, u8"format_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"PPGen use only: PPTable for different ASICs. For sienna_cichlid this should be 0x80"))
	),
	(bios->platform_caps, u8"platform_caps",
		(ATUI_NAN, ATUI_PETIOLE, powerplay_platform_caps),
		((LANG_ENG, u8"POWERPLAYABLE::ulPlatformCaps"))
	),
	(bios->thermal_controller_type, u8"thermal_controller_type",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"one of SMU_11_0_7_PP_THERMALCONTROLLER"))
	),

	(bios->small_power_limit1, u8"small_power_limit1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->small_power_limit2, u8"small_power_limit2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->boost_power_limit, u8"boost_power_limit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"For Gemini Board, when the slave adapter is in BACO mode, the master adapter will use this boost power limit instead of the default power limit to boost the power limit."))
	),
	(bios->software_shutdown_temp, u8"software_shutdown_temp",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->reserve, u8"reserve",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"Zero filled field reserved for future use"))
	),

	(bios->power_saving_clock, u8"power_saving_clock",
		(ATUI_NAN, ATUI_PETIOLE, smu_11_0_7_power_saving_clock_table),
		(ATUI_NODESCR)
	),
	(bios->overdrive_table, u8"overdrive_table",
		(ATUI_NAN, ATUI_PETIOLE, smu_11_0_7_overdrive_table),
		(ATUI_NODESCR)
	)

)

