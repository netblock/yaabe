/*
For smu_v13_0_7_pptable.h and smu13_driver_if_v13_0_7.h
See atui_atomfirmware.c for how to use PPATUI_FUNCIFY()
*/

#include "atomtree.h"
#include "atui.h"

PPATUI_FUNCIFY(struct, smu_13_0_7_overdrive_table, atomtree_powerplaytable,
	(bios->revision, u8"revision",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Revision = SMU_13_0_7_PP_OVERDRIVE_VERSION"))
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
					// if CAP_COUNT changes, please change this 16
				(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"support flag"))
			),
			NULL, SMU_13_0_7_ODCAP_COUNT, // deferred start, count
			SMU_11_0_ODFEATURE_CAP // enum
		)), (ATUI_NODESCR)
	),
	((&(bios->cap[SMU_13_0_7_ODCAP_COUNT])), // start
		u8"Undefined OD feature support flags", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"OD feature [16 + %02u]",
					// if CAP_COUNT changes, please change this 16
				(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"support flag"))
			),
			NULL, // deferred start
			(SMU_13_0_7_MAX_ODFEATURE - SMU_13_0_7_ODCAP_COUNT), // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->max, u8"Supported Overdrive settings (max)", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"max: %s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_ODSETTING_COUNT, // deferred start, count
			SMU_13_0_7_ODSETTING_ID // enum
		)), (ATUI_NODESCR)
	),
	(bios->min, u8"Supported Overdrive settings (min)", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"min: %s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_ODSETTING_COUNT, // deferred start, count
			SMU_13_0_7_ODSETTING_ID // enum
		)), (ATUI_NODESCR)
	),
	((&(bios->max[SMU_13_0_7_ODSETTING_COUNT])), // start
		u8"Undefined OD settings (max)", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"max: [32 + %02u]",
					// if ODSETTING_COUNT changes, please change this 32
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			(SMU_13_0_7_MAX_ODSETTING - SMU_13_0_7_ODSETTING_COUNT), // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	((&(bios->min[SMU_13_0_7_ODSETTING_COUNT])), // start
		u8"Undefined OD settings (min)", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"min: [32 + %02u]",
					// if ODSETTING_COUNT changes, please change this 32
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			(SMU_13_0_7_MAX_ODSETTING - SMU_13_0_7_ODSETTING_COUNT), // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->pm_setting, u8"PowerMode feature settings", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_PMSETTING_COUNT, // deferred start, count
			SMU_13_0_7_PWRMODE_SETTING // enum
		)), ((LANG_ENG, u8"Optimized power mode feature settings"))
	),
	((&(bios->pm_setting[SMU_13_0_7_PMSETTING_COUNT])), // start
		u8"Undefined PowerMode feature settings", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"pm_setting [16 + %02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			(SMU_13_0_7_MAX_PMSETTING - SMU_13_0_7_PMSETTING_COUNT), // count
			ATUI_NULL // enum
		)), ((LANG_ENG, u8"Optimized power mode feature settings"))
	)
)

PPATUI_FUNCIFY(struct, smu_13_0_7_powerplay_table, atomtree_powerplaytable,
	(bios->header, u8"header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		((LANG_ENG, u8"For PLUM_BONITO, header.format_revision = 15, header.content_revision = 0"))
	),
	(bios->table_revision, u8"table_revision",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"For PLUM_BONITO, table_revision = 2"))
	),
	(bios->padding, u8"padding",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->table_size, u8"table_size",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Driver portion table size. The offset to smc_pptable including header size"))
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
		((LANG_ENG, u8"PPGen use only: PPTable for different ASICs. For PLUM_BONITO this should be 0x80"))
	),
	(bios->platform_caps, u8"platform_caps",
		(ATUI_NODISPLAY, ATUI_INLINE, powerplay_platform_caps),
		(ATUI_NODESCR)
	),

	(bios->thermal_controller_type, u8"thermal_controller_type",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"one of SMU_13_0_7_PP_THERMALCONTROLLER"))
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
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->overdrive_table, u8"overdrive_table",
		(ATUI_NAN, ATUI_PETIOLE, smu_13_0_7_overdrive_table),
		(ATUI_NODESCR)
	),

	(bios->padding1, u8"padding1",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)

	// struct smu13_smcpptable_v39 smc_pptable;
)



PPATUI_FUNCIFY(union, powerplay_feature_control_smu13, atomtree_powerplaytable,
	(bios->feature_control, u8"feature_control",
		(ATUI_HEX, ATUI_BITFIELD, (
			(u8"FW_DATA_READ",            0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_GFXCLK",              1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_GFX_POWER_OPTIMIZER", 2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_UCLK",                3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_FCLK",                4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_SOCCLK",              5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_MP0CLK",              6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_LINK",                7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DPM_DCN",                 8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"VMEMP_SCALING",           9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"VDDIO_MEM_SCALING",      10,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_GFXCLK",              11,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_SOCCLK",              12,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_FCLK",                13,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_LCLK",                14,14, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_DCFCLK",              15,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_UCLK",                16,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_ULV",                17,17, ATUI_DEC, (ATUI_NODESCR)),
			(u8"FW_DSTATE",              18,18, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFXOFF",                 19,19, ATUI_DEC, (ATUI_NODESCR)),
			(u8"BACO",                   20,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MM_DPM",                 21,21, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SOC_MPCLK_DS",           22,22, ATUI_DEC, (ATUI_NODESCR)),
			(u8"BACO_MPCLK_DS",          23,23, ATUI_DEC, (ATUI_NODESCR)),
			(u8"THROTTLERS",             24,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SMARTSHIFT",             25,25, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GTHR",                   26,26, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ACDC",                   27,27, ATUI_DEC, (ATUI_NODESCR)),
			(u8"VR0HOT",                 28,28, ATUI_DEC, (ATUI_NODESCR)),
			(u8"FW_CTF",                 29,29, ATUI_DEC, (ATUI_NODESCR)),
			(u8"FAN_CONTROL",            30,30, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_DCS",                31,31, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_READ_MARGIN",        32,32, ATUI_DEC, (ATUI_NODESCR)),
			(u8"LED_DISPLAY",            33,33, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFXCLK_SPREAD_SPECTRUM", 34,34, ATUI_DEC, (ATUI_NODESCR)),
			(u8"OUT_OF_BAND_MONITOR",    35,35, ATUI_DEC, (ATUI_NODESCR)),
			(u8"OPTIMIZED_VMIN",         36,36, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_IMU",                37,37, ATUI_DEC, (ATUI_NODESCR)),
			(u8"BOOT_TIME_CAL",          38,38, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_PCC_DFLL",           39,39, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SOC_CG",                 40,40, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DF_CSTATE",              41,41, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_EDC",                42,42, ATUI_DEC, (ATUI_NODESCR)),
			(u8"BOOT_POWER_OPT",         43,43, ATUI_DEC, (ATUI_NODESCR)),
			(u8"CLOCK_POWER_DOWN_BYPASS",44,44, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DS_VCN",                 45,45, ATUI_DEC, (ATUI_NODESCR)),
			(u8"BACO_CG",                46,46, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MEM_TEMP_READ",          47,47, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ATHUB_MMHUB_PG",         48,48, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SOC_PCC",                49,49, ATUI_DEC, (ATUI_NODESCR)),
			(u8"EDC_PWRBRK",             50,50, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_51",               51,51, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_52",               52,52, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_53",               53,53, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_54",               54,54, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_55",               55,55, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_56",               56,56, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_57",               57,57, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_58",               58,58, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_59",               59,59, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_60",               60,60, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_61",               61,61, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_62",               62,62, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SPARE_63",               63,63, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, dpm_debug_override_smu13, atui_nullstruct,
	(bios->DebugOverrides, u8"DebugOverrides",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"disable_volt_link_vcn_fclk",   0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"disable_volt_link_dcn_fclk",   1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"disable_volt_link_mp0_fclk",   2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"disable_volt_link_vcn_dcfclk", 3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"disable_fast_fclk_timer",      4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"disable_vcn_pg",               5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"disable_fmax_vmax",            6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"disable_imu_fw_checks",        7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"disable_d0i2_reentry_hsr_timer_check", 8,8, ATUI_DEC,
				(ATUI_NODESCR)
			),
			(u8"disable_dfll",                 9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_rlc_vf_bringup_mode",  10,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"dfll_master_mode",            11,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"enable_profiling_mode",       12,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved",                    31,13, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, throttler_control_smu13_0x35, atui_nullstruct,
	(bios->ThrottlerControlMask, u8"ThrottlerControlMask",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"TEMP_EDGE",      0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_HOTSPOT",   1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_HOTSPOT_G", 2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_HOTSPOT_M", 3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_MEM",       4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_VR_GFX",    5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_VR_MEM0",   6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_VR_MEM1",   7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_VR_SOC",    8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_VR_U",      9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_LIQUID0",  10,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_LIQUID1",  11,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TEMP_PLX",      12,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TDC_GFX",       13,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TDC_SOC",       14,14, ATUI_DEC, (ATUI_NODESCR)),
			(u8"TDC_U",         15,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPT0",          16,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPT1",          17,17, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPT2",          18,18, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPT3",          19,19, ATUI_DEC, (ATUI_NODESCR)),
			(u8"FIT",           20,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_APCC_PLUS", 21,21, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved",      31,22, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, fw_dstate_features_smu13_0x35, atui_nullstruct,
	(bios->FwDStateMask, u8"FwDStateMask",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"SOC_ULV",           0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"G6_HSR",            1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"G6_PHY_VMEMP_OFF",  2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SMN_DS",            3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MP1_WHISPER_MODE",  4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SOC_LIV_MIN",       5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SOC_PLL_PWRDN",     6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MEM_PLL_PWRDN",     7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MALL_ALLOC",        8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MEM_PSI",           9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"HSR_NON_STROBE",    10,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MP0_ENTER_WFI",     11,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"U_ULV",             12,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MALL_FLUSH",        13,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SOC_PSI",           14,14, ATUI_DEC, (ATUI_NODESCR)),
			(u8"U_PSI",             15,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"UCP_DS",            16,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"CSRCLK_DS",         17,17, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MMHUB_INTERLOCK",   18,18, ATUI_DEC, (ATUI_NODESCR)),
			(u8"D0i3_2_QUIET_FW",   19,19, ATUI_DEC, (ATUI_NODESCR)),
			(u8"CLDO_PRG",          20,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DF_PLL_PWRDN",      21,21, ATUI_DEC, (ATUI_NODESCR)),
			(u8"U_LOW_PWR_MODE_EN", 22,22, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_PSI6",          23,23, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GFX_VR_PWR_STAGE",  24,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved",          31,25, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, DpmDescriptor_t, atomtree_powerplaytable,
	(bios->Padding, u8"Padding",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SnapToDiscrete, u8"SnapToDiscrete",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"0 - Fine grained DPM, 1 - Discrete DPM"))
	),
	(bios->NumDiscreteLevels, u8"NumDiscreteLevels",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Set to 2 (Fmin, Fmax) when using fine grained DPM, otherwise set to # discrete levels used"))
	),
	(bios->CalculateFopt, u8"CalculateFopt",
		(ATUI_DEC, ATUI_ENUM, FOPT_CALC_e),
		((LANG_ENG, u8"Indication whether FW should calculate Fopt or use values below. Reference FOPT_CALC_e"))
	),
	(bios->ConversionToAvfsClk, u8"ConversionToAvfsClk",
		(ATUI_NAN, ATUI_INLINE, linear_f32),
		((LANG_ENG, u8"Transfer function to AVFS Clock (GHz->GHz)"))
	),
	(bios->Padding3, u8"Padding3",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->Padding4, u8"Padding4",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FoptimalDc, u8"FoptimalDc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Foptimal frequency in DC power mode."))
	),
	(bios->FoptimalAc, u8"FoptimalAc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Foptimal frequency in AC power mode."))
	),
	(bios->Padding2, u8"Padding2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, BootValues_t, atomtree_powerplaytable,
	(bios->InitGfxclk_bypass, u8"InitGfxclk_bypass",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 0"))
	),
	(bios->InitSocclk, u8"InitSocclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 0"))
	),
	(bios->InitMp0clk, u8"InitMp0clk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 0"))
	),
	(bios->InitMpioclk, u8"InitMpioclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 0"))
	),
	(bios->InitSmnclk, u8"InitSmnclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 0"))
	),
	(bios->InitUcpclk, u8"InitUcpclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 0"))
	),
	(bios->InitCsrclk, u8"InitCsrclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 0"))
	),

	(bios->InitDprefclk, u8"InitDprefclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 1"))
	),
	(bios->InitDcfclk, u8"InitDcfclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 1"))
	),
	(bios->InitDtbclk, u8"InitDtbclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 1"))
	),
	(bios->InitDclk, u8"InitDclk",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"PLL 2. assume same DCLK/VCLK for both instances"))
	),
	(bios->InitVclk, u8"InitVclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 2"))
	),
	(bios->InitUsbdfsclk, u8"InitUsbdfsclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 3"))
	),
	(bios->InitMp1clk, u8"InitMp1clk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 3"))
	),
	(bios->InitLclk, u8"InitLclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 3"))
	),
	(bios->InitBaco400clk_bypass, u8"InitBaco400clk_bypass",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 3"))
	),
	(bios->InitBaco1200clk_bypass, u8"InitBaco1200clk_bypass",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 3"))
	),
	(bios->InitBaco700clk_bypass, u8"InitBaco700clk_bypass",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 3"))
	),
	(bios->InitFclk, u8"InitFclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 4"))
	),
	(bios->InitGfxclk_clkb, u8"InitGfxclk_clkb",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"PLL 5"))
	),
	(bios->InitUclkDPMState, u8"InitUclkDPMState",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"PLL 6. =0,1,2,3, frequency from FreqTableUclk"))
	),

	(bios->Padding, u8"Padding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->InitVcoFreqPll0, u8"InitVcoFreqPll0",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->InitVcoFreqPll1, u8"InitVcoFreqPll1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->InitVcoFreqPll2, u8"InitVcoFreqPll2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->InitVcoFreqPll3, u8"InitVcoFreqPll3",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->InitVcoFreqPll4, u8"InitVcoFreqPll4",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->InitVcoFreqPll5, u8"InitVcoFreqPll5",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->InitVcoFreqPll6, u8"InitVcoFreqPll6",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->InitGfx, u8"InitGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) ,  should be 0?"))
	),
	(bios->InitSoc, u8"InitSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2)"))
	),
	(bios->InitU, u8"InitU",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In Mv(Q2) not applicable"))
	),

	(bios->Padding2, u8"Padding2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Spare, u8"Spare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, MsgLimits_t, atomtree_powerplaytable,
	// TODO unroll? dynarray inline?
	// uint16_t Power[PPT_THROTTLER_COUNT][POWER_SOURCE_COUNT]; // Watts

	(bios->Tdc, u8"Tdc", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Tdc (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, TDC_THROTTLER_COUNT_SMU13, // deferred start, count
			TDC_THROTTLER_e // enum
		)),
		((LANG_ENG, u8"Amps"))
	),

	(bios->Temperature, u8"Temperature", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Temperature (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_TEMP_COUNT, // deferred start, count
			SMU_13_0_7_TEMP_e // enum
		)),
		((LANG_ENG, u8"Celsius"))
	),

	(bios->PwmLimitMin, u8"PwmLimitMin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PwmLimitMax, u8"PwmLimitMax",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetTemperature, u8"FanTargetTemperature",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Spare1, u8"Spare1",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->AcousticTargetRpmThresholdMin, u8"AcousticTargetRpmThresholdMin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->AcousticTargetRpmThresholdMax, u8"AcousticTargetRpmThresholdMax",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->AcousticLimitRpmThresholdMin, u8"AcousticLimitRpmThresholdMin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->AcousticLimitRpmThresholdMax, u8"AcousticLimitRpmThresholdMax",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->PccLimitMin, u8"PccLimitMin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PccLimitMax, u8"PccLimitMax",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FanStopTempMin, u8"FanStopTempMin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanStopTempMax, u8"FanStopTempMax",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanStartTempMin, u8"FanStartTempMin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanStartTempMax, u8"FanStartTempMax",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->PowerMinPpt0, u8"PowerMinPpt0", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PowerMinPpt0 (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, POWER_SOURCE_COUNT, // deferred start, count
			POWER_SOURCE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->Spare, u8"Spare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, DriverReportedClocks_t, atomtree_powerplaytable,
	(bios->BaseClockAc, u8"BaseClockAc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GameClockAc, u8"GameClockAc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BoostClockAc, u8"BoostClockAc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BaseClockDc, u8"BaseClockDc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GameClockDc, u8"GameClockDc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BoostClockDc, u8"BoostClockDc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Reserved, u8"Reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, AvfsDcBtcParams_smu13, atomtree_powerplaytable,
	(bios->DcBtcEnabled, u8"DcBtcEnabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding, u8"Padding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->DcTol, u8"DcTol",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV Q2"))
	),
	(bios->DcBtcGb, u8"DcBtcGb",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV Q2"))
	),

	(bios->DcBtcMin, u8"DcBtcMin",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV Q2"))
	),
	(bios->DcBtcMax, u8"DcBtcMax",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mV Q2"))
	),

	(bios->DcBtcGbScalar, u8"DcBtcGbScalar",
		(ATUI_NAN, ATUI_INLINE, linear_f32),
		(ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, AvfsFuseOverride_smu13, atomtree_powerplaytable,
	(bios->AvfsTemp, u8"AvfsTemp", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"AvfsTemp (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, AVFS_TEMP_COUNT, // deferred start, count
			AVFS_TEMP_e // enum
		)),
		((LANG_ENG, u8"in degrees C"))
	),
	(bios->VftFMin, u8"VftFMin",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in MHz"))
	),
	(bios->VInversion, u8"VInversion",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in mV Q2"))
	),
	(bios->qVft, u8"qVft", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"qVft (%s)",
				(ATUI_NAN, ATUI_INLINE, quadratic_f32),
				(ATUI_NODESCR)
			),
			NULL, AVFS_TEMP_COUNT, // deferred start, count
			AVFS_TEMP_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->qAvfsGb, u8"qAvfsGb",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->qAvfsGb2, u8"qAvfsGb2",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, SviTelemetryScale_t, atomtree_powerplaytable,
	(bios->Offset, u8"Offset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding, u8"Padding",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MaxCurrent, u8"MaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	)
)


PPATUI_FUNCIFY(struct, overdrivelimits_smu13, atomtree_powerplaytable,
	(bios->FeatureCtrlMask, u8"FeatureCtrlMask",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->VoltageOffsetPerZoneBoundary, u8"VoltageOffsetPerZoneBoundary",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved1, u8"Reserved1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Reserved2, u8"Reserved2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->GfxclkFmin, u8"GfxclkFmin",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"MHz"))
	),
	(bios->GfxclkFmax, u8"GfxclkFmax",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"MHz"))
	),
	(bios->UclkFmin, u8"UclkFmin",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"MHz"))
	),
	(bios->UclkFmax, u8"UclkFmax",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"MHz"))
	),

	(bios->Ppt, u8"Ppt",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"%"))
	),
	(bios->Tdc, u8"Tdc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FanLinearPwmPoints, u8"FanLinearPwmPoints",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanLinearTempPoints, u8"FanLinearTempPoints",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanMinimumPwm, u8"FanMinimumPwm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->AcousticTargetRpmThreshold, u8"AcousticTargetRpmThreshold",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->AcousticLimitRpmThreshold, u8"AcousticLimitRpmThreshold",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetTemperature, u8"FanTargetTemperature",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Degree Celcius"))
	),
	(bios->FanZeroRpmEnable, u8"FanZeroRpmEnable",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanZeroRpmStopTemp, u8"FanZeroRpmStopTemp",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanMode, u8"FanMode",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MaxOpTemp, u8"MaxOpTemp",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding, u8"Padding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->Spare, u8"Spare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, smu13_skutable_v39, atomtree_powerplaytable,

	(bios->Version, u8"Version",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"should be unique to each SKU(i.e if any value changes in below structure then this value must be different)"))
	),

	(bios->features, u8"features",
		(ATUI_NAN, ATUI_PETIOLE, powerplay_feature_control_smu13),
		(ATUI_NODESCR)
	),

	(bios->TotalPowerConfig, u8"TotalPowerConfig",
		(ATUI_DEC, ATUI_ENUM, PwrConfig_e),
		((LANG_ENG, u8"Determines how PMFW calculates the power."))
	),
	(bios->CustomerVariant, u8"CustomerVariant",
		(ATUI_DEC, ATUI_ENUM, CUSTOMER_VARIANT_e),
		((LANG_ENG, u8"To specify if this PPTable is intended for a particular customer. Use defines from CUSTOMER_VARIANT_e"))
	),
	(bios->MemoryTemperatureTypeMask, u8"MemoryTemperatureTypeMask",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Bit mapping indicating which methods of memory temperature reading are enabled. Use defines from MEM_TEMP_*BIT"))
	),
	(bios->SmartShiftVersion, u8"SmartShiftVersion",
		(ATUI_DEC, ATUI_ENUM, SMARTSHIFT_VERSION_e),
		((LANG_ENG, u8"Determine what SmartShift feature version is supported"))
	),

	(bios->SocketPowerLimitAc, u8"SocketPowerLimitAc", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PPT %u",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PPT_THROTTLER_COUNT, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In Watts. Power limit that PMFW attempts to control to in AC mode. Multiple limits supported"))
	),
	(bios->SocketPowerLimitDc, u8"SocketPowerLimitDc", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PPT %u",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PPT_THROTTLER_COUNT, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In Watts. Power limit that PMFW attempts to control to in DC mode. Multiple limits supported"))
	),

	(bios->SocketPowerLimitSmartShift2, u8"SocketPowerLimitSmartShift2",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In Watts. Power limit used SmartShift"))
	),
	(bios->EnableLegacyPptLimit, u8"EnableLegacyPptLimit",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, u8"if set to 1, SocketPowerLimitAc and SocketPowerLimitDc will be interpreted as legacy programs(i.e absolute power). If 0, all except index 0 will be scalars. Relative index 0."))
	),
	(bios->UseInputTelemetry, u8"UseInputTelemetry",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"applicable to SVI3 only and only to be set if VRs support"))
	),
	(bios->SmartShiftMinReportedPptinDcs, u8"SmartShiftMinReportedPptinDcs",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"minimum possible active power consumption for this SKU. Used for SmartShift power reporting"))
	),

	(bios->PaddingPpt, u8"PaddingPpt",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->VrTdcLimit, u8"VrTdcLimit", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"VrTdcLimit (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, TDC_THROTTLER_COUNT_SMU13, // deferred start, count
			TDC_THROTTLER_e // enum
		)),
		((LANG_ENG, u8"In Amperes. Current limit associated with VR regulator maximum temperature"))
	),

	(bios->PlatformTdcLimit, u8"PlatformTdcLimit", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PlatformTdcLimit (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, TDC_THROTTLER_COUNT_SMU13, // deferred start, count
			TDC_THROTTLER_e // enum
		)),
		((LANG_ENG, u8"In Amperes. Current limit associated with platform maximum temperature per VR current rail"))
	),

	(bios->TemperatureLimit, u8"TemperatureLimit", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"TemperatureLimit (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_TEMP_COUNT, // deferred start, count
			SMU_13_0_7_TEMP_e // enum
		)),
		((LANG_ENG, u8"In degrees Celsius. Temperature limit associated with each input"))
	),

	(bios->HwCtfTempLimit, u8"HwCtfTempLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In degrees Celsius. Temperature above which HW will trigger CTF. Consumed by VBIOS only"))
	),

	(bios->PaddingInfra, u8"PaddingInfra",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FitControllerFailureRateLimit, u8"FitControllerFailureRateLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Expected GFX Duty Cycle at Vmax."))
	),
	(bios->FitControllerGfxDutyCycle, u8"FitControllerGfxDutyCycle",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Expected SOC Duty Cycle at Vmax."))
	),
	(bios->FitControllerSocDutyCycle, u8"FitControllerSocDutyCycle",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FitControllerSocOffset, u8"FitControllerSocOffset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->GfxApccPlusResidencyLimit, u8"GfxApccPlusResidencyLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Percentage value. Used by APCC+ controller to control PCC residency to some value"))
	),
	(bios->ThrottlerControlMask, u8"ThrottlerControlMask",
		(ATUI_NODISPLAY, ATUI_INLINE, throttler_control_smu13_0x35),
		(ATUI_NODESCR)
	),

	(bios->FwDStateMask, u8"FwDStateMask",
		(ATUI_NAN, ATUI_INLINE, fw_dstate_features_smu13_0x35),
		(ATUI_NODESCR)
	),

	(bios->UlvVoltageOffset, u8"UlvVoltageOffset", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"UlvVoltageOffset (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"In mV(Q2). ULV offset used in either GFX_ULV or SOC_ULV(part of FW_DSTATE)"))
	),

	(bios->UlvVoltageOffsetU, u8"UlvVoltageOffsetU",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2). ULV offset used in either U_ULV(part of FW_DSTATE)"))
	),
	(bios->DeepUlvVoltageOffsetSoc, u8"DeepUlvVoltageOffsetSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2)  Long Idle Vmin (deep ULV), for VDD_SOC as part of FW_DSTATE"))
	),
	(bios->DefaultMaxVoltage, u8"DefaultMaxVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"DefaultMaxVoltage (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"In mV(Q2) Maximum voltage without FIT controller enabled"))
	),
	(bios->BoostMaxVoltage, u8"BoostMaxVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"BoostMaxVoltage (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"In mV(Q2) Maximum voltage with FIT controller enabled"))
	),
	(bios->VminTempHystersis, u8"VminTempHystersis", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"VminTempHystersis (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"Celsius Temperature hysteresis for switching between low/high temperature values for Vmin"))
	),
	(bios->VminTempThreshold, u8"VminTempThreshold", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"VminTempThreshold (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"Celsius Temperature threshold for switching between low/high temperature values for Vmin"))
	),
	(bios->Vmin_Hot_T0, u8"Vmin_Hot_T0", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Vmin_Hot_T0 (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"In mV(Q2) Initial (pre-aging) Vset to be used at hot."))
	),
	(bios->Vmin_Cold_T0, u8"Vmin_Cold_T0", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Vmin_Cold_T0 (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"In mV(Q2) Initial (pre-aging) Vset to be used at cold."))
	),
	(bios->Vmin_Hot_Eol, u8"Vmin_Hot_Eol", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Vmin_Hot_Eol (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"In mV(Q2) End-of-life Vset to be used at hot."))
	),
	(bios->Vmin_Cold_Eol, u8"Vmin_Cold_Eol", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Vmin_Cold_Eol (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"In mV(Q2) End-of-life Vset to be used at cold."))
	),
	(bios->Vmin_Aging_Offset, u8"Vmin_Aging_Offset", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Vmin_Aging_Offset (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"In mV(Q2) Worst-case aging margin"))
	),
	(bios->Spare_Vmin_Plat_Offset_Hot, u8"Spare_Vmin_Plat_Offset_Hot", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Spare_Vmin_Plat_Offset_Hot (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"In mV(Q2) Platform offset apply to T0 Hot"))
	),
	(bios->Spare_Vmin_Plat_Offset_Cold, u8"Spare_Vmin_Plat_Offset_Cold", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Spare_Vmin_Plat_Offset_Cold (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"In mV(Q2) Platform offset apply to T0 Cold"))
	),
	(bios->VcBtcFixedVminAgingOffset, u8"VcBtcFixedVminAgingOffset", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"VcBtcFixedVminAgingOffset (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"Linear offset or GB term to account for mis-correlation between PSM and Vmin shift trends across parts."))
	),
	(bios->VcBtcVmin2PsmDegrationGb, u8"VcBtcVmin2PsmDegrationGb", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"VcBtcVmin2PsmDegrationGb (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"Scalar coefficient of the PSM aging degradation function"))
	),
	(bios->VcBtcPsmA, u8"VcBtcPsmA", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"VcBtcPsmA (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"A_PSM  // Exponential coefficient of the PSM aging degradation function"))
	),
	(bios->VcBtcPsmB, u8"VcBtcPsmB", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"VcBtcPsmB (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"B_PSM  // Scalar coefficient of the VMIN aging degradation function. Specified as worst case between hot and cold."))
	),
	(bios->VcBtcVminA, u8"VcBtcVminA", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"VcBtcVminA (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"A_VMIN // Exponential coefficient of the VMIN aging degradation function. Specified as worst case between hot and cold."))
	),
	(bios->VcBtcVminB, u8"VcBtcVminB", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"VcBtcVminB (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, u8"B_VMIN"))
	),

	(bios->PerPartVminEnabled, u8"PerPartVminEnabled", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PerPartVminEnabled (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->VcBtcEnabled, u8"VcBtcEnabled", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"VcBtcEnabled (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->SocketPowerLimitAcTau, u8"SocketPowerLimitAcTau", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PPT %u",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PPT_THROTTLER_COUNT, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"Time constant of LPF in ms"))
	),
	(bios->SocketPowerLimitDcTau, u8"SocketPowerLimitDcTau", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PPT %u",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PPT_THROTTLER_COUNT, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"Time constant of LPF in ms"))
	),

	(bios->Vmin_droop, u8"Vmin_droop",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->SpareVmin, u8"SpareVmin",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->DpmDescriptor, u8"DpmDescriptor", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"DpmDescriptor (%s)",
				(ATUI_NAN, ATUI_PETIOLE, DpmDescriptor_t), (ATUI_NODESCR)
			),
			NULL, SMU13_PPCLK_COUNT, // deferred start, count
			SMU13_PPCLK_e // enum
		)), (ATUI_NODESCR)
	),




	(bios->FreqTableGfx, u8"FreqTableGfx", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableGfx [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_GFXCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableVclk, u8"FreqTableVclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableVclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_VCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableDclk, u8"FreqTableDclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableDclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableSocclk, u8"FreqTableSocclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableSocclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_SOCCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableUclk, u8"FreqTableUclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableUclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableDispclk, u8"FreqTableDispclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableDispclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DISPCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableDppClk, u8"FreqTableDppClk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableDppClk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DPPCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableDprefclk, u8"FreqTableDprefclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableDprefclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DPREFCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableDcfclk, u8"FreqTableDcfclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableDcfclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DCFCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableDtbclk, u8"FreqTableDtbclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableDtbclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DTBCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->FreqTableFclk, u8"FreqTableFclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableFclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_FCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),

	(bios->DcModeMaxFreq, u8"DcModeMaxFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"DcModeMaxFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU13_PPCLK_COUNT, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->Mp0clkFreq, u8"Mp0clkFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Mp0clkFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_MP0CLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"in MHz"))
	),
	(bios->Mp0DpmVoltage, u8"Mp0DpmVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Mp0DpmVoltage [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_MP0CLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"mV(Q2)"))
	),

	(bios->GfxclkSpare, u8"GfxclkSpare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->GfxclkFreqCap, u8"GfxclkFreqCap",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxclkFgfxoffEntry, u8"GfxclkFgfxoffEntry",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Mhz"))
	),
	(bios->GfxclkFgfxoffExitImu, u8"GfxclkFgfxoffExitImu",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Mhz"))
	),
	(bios->GfxclkFgfxoffExitRlc, u8"GfxclkFgfxoffExitRlc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Mhz"))
	),
	(bios->GfxclkThrottleClock, u8"GfxclkThrottleClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Used primarily in DCS"))
	),
	(bios->EnableGfxPowerStagesGpio, u8"EnableGfxPowerStagesGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Genlk_vsync GPIO flag used to control gfx power stages"))
	),
	(bios->GfxIdlePadding, u8"GfxIdlePadding",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->SmsRepairWRCKClkDivEn, u8"SmsRepairWRCKClkDivEn",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SmsRepairWRCKClkDivVal, u8"SmsRepairWRCKClkDivVal",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxOffEntryEarlyMGCGEn, u8"GfxOffEntryEarlyMGCGEn",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxOffEntryForceCGCGEn, u8"GfxOffEntryForceCGCGEn",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxOffEntryForceCGCGDelayEn, u8"GfxOffEntryForceCGCGDelayEn",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxOffEntryForceCGCGDelayVal, u8"GfxOffEntryForceCGCGDelayVal",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in microseconds"))
	),

	(bios->GfxclkFreqGfxUlv, u8"GfxclkFreqGfxUlv",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in MHz"))
	),
	(bios->GfxIdlePadding2, u8"GfxIdlePadding2",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->GfxOffEntryHysteresis, u8"GfxOffEntryHysteresis",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"For RLC to count after it enters CGCG, and before triggers GFXOFF entry"))
	),
	(bios->GfxoffSpare, u8"GfxoffSpare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->DfllBtcMasterScalerM, u8"DfllBtcMasterScalerM",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DfllBtcMasterScalerB, u8"DfllBtcMasterScalerB",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DfllBtcSlaveScalerM, u8"DfllBtcSlaveScalerM",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DfllBtcSlaveScalerB, u8"DfllBtcSlaveScalerB",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DfllPccAsWaitCtrl, u8"DfllPccAsWaitCtrl",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GDFLL_AS_WAIT_CTRL_PCC register value to be passed to RLC msg"))
	),
	(bios->DfllPccAsStepCtrl, u8"DfllPccAsStepCtrl",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GDFLL_AS_STEP_CTRL_PCC register value to be passed to RLC msg"))
	),
	(bios->GfxGpoSpare, u8"GfxGpoSpare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->DcsGfxOffVoltage, u8"DcsGfxOffVoltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Voltage in mV(Q2) applied to VDDGFX when entering DCS GFXOFF phase"))
	),
	(bios->PaddingDcs, u8"PaddingDcs",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
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


	(bios->DcsSpare, u8"DcsSpare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->ShadowFreqTableUclk, u8"ShadowFreqTableUclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"ShadowFreqTableUclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"In MHz"))
	),
	(bios->UseStrobeModeOptimizations, u8"UseStrobeModeOptimizations",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Set to indicate that FW should use strobe mode optimizations"))
	),
	(bios->PaddingMem, u8"PaddingMem",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->UclkDpmPstates, u8"UclkDpmPstates", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"UclkDpmPstates [%02u]",
				(ATUI_DEC, ATUI_ENUM, DPM_PSTATES_e), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"4 DPM states."))
	),
	(bios->FreqTableUclkDiv, u8"FreqTableUclkDiv", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FreqTableUclkDiv [%02u]",
				(ATUI_DEC, ATUI_ENUM, UCLK_DIV_e), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->MemVmempVoltage, u8"MemVmempVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"MemVmempVoltage [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"mV(Q2)"))
	),
	(bios->MemVddioVoltage, u8"MemVddioVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"MemVddioVoltage [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"mV(Q2)"))
	),

	(bios->FclkDpmUPstates, u8"FclkDpmUPstates", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FclkDpmUPstates [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_FCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"U P-state ID associated with each FCLK DPM state."))
	),
	(bios->FclkDpmVddU, u8"FclkDpmVddU", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FclkDpmVddU [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_FCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"mV(Q2) Vset U voltage associated with each FCLK DPM state."))
	),
	(bios->FclkDpmUSpeed, u8"FclkDpmUSpeed", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FclkDpmUSpeed [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_FCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, u8"U speed associated with each FCLK DPM state"))
	),
	(bios->FclkDpmDisallowPstateFreq, u8"FclkDpmDisallowPstateFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Frequency which FW will target when indicated that display config cannot support P-state. Set to 0 use FW calculated value"))
	),
	(bios->PaddingFclk, u8"PaddingFclk",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PcieGenSpeed, u8"PcieGenSpeed", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PcieGenSpeed [%02u]",
				(ATUI_DEC, ATUI_ENUM, PCIE_SPEED_e), (ATUI_NODESCR)
			),
			NULL, NUM_LINK_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->PcieLaneCount, u8"PcieLaneCount", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"PcieLaneCount [%02u]",
				(ATUI_DEC, ATUI_ENUM, PCIE_WIDTH_e), (ATUI_NODESCR)
			),
			NULL, NUM_LINK_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->LclkFreq, u8"LclkFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"LclkFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_LINK_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->FanStopTemp, u8"FanStopTemp", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FanStopTemp (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_TEMP_COUNT, // deferred start, count
			SMU_13_0_7_TEMP_e // enum
		)),
		((LANG_ENG, u8"Celsius"))
	),
	(bios->FanStartTemp, u8"FanStartTemp", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FanStartTemp (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_TEMP_COUNT, // deferred start, count
			SMU_13_0_7_TEMP_e // enum
		)),
		((LANG_ENG, u8"Celsius"))
	),

	(bios->FanGain, u8"FanGain", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FanGain (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_TEMP_COUNT, // deferred start, count
			SMU_13_0_7_TEMP_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->FanGainPadding, u8"FanGainPadding",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FanPwmMin, u8"FanPwmMin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->AcousticTargetRpmThreshold, u8"AcousticTargetRpmThreshold",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->AcousticLimitRpmThreshold, u8"AcousticLimitRpmThreshold",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanMaximumRpm, u8"FanMaximumRpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MGpuAcousticLimitRpmThreshold, u8"MGpuAcousticLimitRpmThreshold",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetGfxclk, u8"FanTargetGfxclk",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TempInputSelectMask, u8"TempInputSelectMask",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanZeroRpmEnable, u8"FanZeroRpmEnable",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTachEdgePerRev, u8"FanTachEdgePerRev",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetTemperature, u8"FanTargetTemperature", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FanTargetTemperature (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_TEMP_COUNT, // deferred start, count
			SMU_13_0_7_TEMP_e // enum
		)), (ATUI_NODESCR)
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

	(bios->FwCtfLimit, u8"FwCtfLimit", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"FwCtfLimit (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_TEMP_COUNT, // deferred start, count
			SMU_13_0_7_TEMP_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->IntakeTempEnableRPM, u8"IntakeTempEnableRPM",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->IntakeTempOffsetTemp, u8"IntakeTempOffsetTemp",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->IntakeTempReleaseTemp, u8"IntakeTempReleaseTemp",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->IntakeTempHighIntakeAcousticLimit, u8"IntakeTempHighIntakeAcousticLimit",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->IntakeTempAcouticLimitReleaseRate, u8"IntakeTempAcouticLimitReleaseRate",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FanAbnormalTempLimitOffset, u8"FanAbnormalTempLimitOffset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanStalledTriggerRpm, u8"FanStalledTriggerRpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanAbnormalTriggerRpmCoeff, u8"FanAbnormalTriggerRpmCoeff",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanAbnormalDetectionEnable, u8"FanAbnormalDetectionEnable",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FanIntakeSensorSupport, u8"FanIntakeSensorSupport",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanIntakePadding, u8"FanIntakePadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->FanSpare, u8"FanSpare",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"SECTION: VDD_GFX AVFS"))
	),

	(bios->OverrideGfxAvfsFuses, u8"OverrideGfxAvfsFuses",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxAvfsPadding, u8"GfxAvfsPadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->L2HwRtAvfsFuses, u8"L2HwRtAvfsFuses", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"L2HwRtAvfsFuses (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_GRTAVFS_HW_FUSE_COUNT, // deferred start, count
			PP_GRTAVFS_HW_FUSE_e // enum
		)),
		((LANG_ENG, u8"see fusedoc for encoding"))
	),
	(bios->SeHwRtAvfsFuses, u8"SeHwRtAvfsFuses", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"SeHwRtAvfsFuses (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_GRTAVFS_HW_FUSE_COUNT, // deferred start, count
			PP_GRTAVFS_HW_FUSE_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->CommonRtAvfs, u8"CommonRtAvfs", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"CommonRtAvfs (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_GRTAVFS_FW_COMMON_FUSE_COUNT, // deferred start, count
			PP_GRTAVFS_FW_COMMON_FUSE_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->L2FwRtAvfsFuses, u8"L2FwRtAvfsFuses", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"L2FwRtAvfsFuses (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_GRTAVFS_FW_SEP_FUSE_COUNT, // deferred start, count
			PP_GRTAVFS_FW_SEP_FUSE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->SeFwRtAvfsFuses, u8"SeFwRtAvfsFuses", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"SeFwRtAvfsFuses (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_GRTAVFS_FW_SEP_FUSE_COUNT, // deferred start, count
			PP_GRTAVFS_FW_SEP_FUSE_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->Droop_PWL_F, u8"Droop_PWL_F", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Droop_PWL_F [%u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_NUM_RTAVFS_PWL_ZONES, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->Droop_PWL_a, u8"Droop_PWL_a", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Droop_PWL_a [%u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_NUM_RTAVFS_PWL_ZONES, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->Droop_PWL_b, u8"Droop_PWL_b", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Droop_PWL_b [%u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_NUM_RTAVFS_PWL_ZONES, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->Droop_PWL_c, u8"Droop_PWL_c", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Droop_PWL_c [%u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_NUM_RTAVFS_PWL_ZONES, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->Static_PWL_Offset, u8"Static_PWL_Offset", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"Static_PWL_Offset [%u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_NUM_RTAVFS_PWL_ZONES, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->dGbV_dT_vmin, u8"dGbV_dT_vmin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dGbV_dT_vmax, u8"dGbV_dT_vmax",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->V2F_vmin_range_low, u8"V2F_vmin_range_low",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->V2F_vmin_range_high, u8"V2F_vmin_range_high",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->V2F_vmax_range_low, u8"V2F_vmax_range_low",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->V2F_vmax_range_high, u8"V2F_vmax_range_high",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->DcBtcGfxParams, u8"DcBtcGfxParams",
		(ATUI_NAN, ATUI_INLINE, AvfsDcBtcParams_smu13),
		(ATUI_NODESCR)
	),
	(bios->GfxAvfsSpare, u8"GfxAvfsSpare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->OverrideSocAvfsFuses, u8"OverrideSocAvfsFuses",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MinSocAvfsRevision, u8"MinSocAvfsRevision",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocAvfsPadding, u8"SocAvfsPadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->SocAvfsFuseOverride, u8"SocAvfsFuseOverride", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"SocAvfsFuseOverride (%s)",
				(ATUI_NAN, ATUI_PETIOLE, AvfsFuseOverride_smu13),
				(ATUI_NODESCR)
			),
			NULL, AVFS_D_COUNT, // deferred start, count
			AVFS_D_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->dBtcGbSoc, u8"dBtcGbSoc", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"dBtcGbSoc (%s)",
				(ATUI_NAN, ATUI_INLINE, droop_f32),
				(ATUI_NODESCR)
			),
			NULL, AVFS_D_COUNT, // deferred start, count
			AVFS_D_e // enum
		)),
		((LANG_ENG, u8"GHz->V BtcGb"))
	),

	(bios->qAgingGb, u8"qAgingGb", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"qAgingGb (%s)",
				(ATUI_NAN, ATUI_INLINE, linear_f32),
				(ATUI_NODESCR)
			),
			NULL, AVFS_D_COUNT, // deferred start, count
			AVFS_D_e // enum
		)),
		((LANG_ENG, u8"GHz->V"))
	),

	(bios->qStaticVoltageOffset, u8"qStaticVoltageOffset", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"qStaticVoltageOffset (%s)",
				(ATUI_NAN, ATUI_INLINE, quadratic_f32),
				(ATUI_NODESCR)
			),
			NULL, AVFS_D_COUNT, // deferred start, count
			AVFS_D_e // enum
		)),
		((LANG_ENG, u8"GHz->V"))
	),

	(bios->DcBtcSocParams, u8"DcBtcSocParams", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"DcBtcSocParams (%s)",
				(ATUI_NAN, ATUI_INLINE, AvfsDcBtcParams_smu13),
				(ATUI_NODESCR)
			),
			NULL, AVFS_D_COUNT, // deferred start, count
			AVFS_D_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->SocAvfsSpare, u8"SocAvfsSpare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->BootValues, u8"BootValues",
		(ATUI_NAN, ATUI_PETIOLE, BootValues_t),
		(ATUI_NODESCR)
	),

	(bios->DriverReportedClocks, u8"DriverReportedClocks",
		(ATUI_NAN, ATUI_PETIOLE, DriverReportedClocks_t),
		(ATUI_NODESCR)
	),
	(bios->MsgLimits, u8"MsgLimits",
		(ATUI_NAN, ATUI_PETIOLE, MsgLimits_t),
		(ATUI_NODESCR)
	),
	(bios->OverDriveLimitsMin, u8"OverDriveLimitsMin",
		(ATUI_NAN, ATUI_PETIOLE, overdrivelimits_smu13),
		(ATUI_NODESCR)
	),
	(bios->OverDriveLimitsBasicMax, u8"OverDriveLimitsBasicMax",
		(ATUI_NAN, ATUI_PETIOLE, overdrivelimits_smu13),
		(ATUI_NODESCR)
	),
	(bios->OverDriveLimitsAdvancedMax, u8"OverDriveLimitsAdvancedMax",
		(ATUI_NAN, ATUI_PETIOLE, overdrivelimits_smu13),
		(ATUI_NODESCR)
	),
	(bios->DebugOverrides, u8"DebugOverrides",
		(ATUI_NAN, ATUI_INLINE, dpm_debug_override_smu13),
		(ATUI_NODESCR)
	),


	(bios->TotalBoardPowerSupport, u8"TotalBoardPowerSupport",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TotalBoardPowerPadding, u8"TotalBoardPowerPadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->TotalIdleBoardPowerM, u8"TotalIdleBoardPowerM",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TotalIdleBoardPowerB, u8"TotalIdleBoardPowerB",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TotalBoardPowerM, u8"TotalBoardPowerM",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TotalBoardPowerB, u8"TotalBoardPowerB",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->qFeffCoeffGameClock, u8"qFeffCoeffGameClock", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"qFeffCoeffGameClock (%s)",
				(ATUI_NAN, ATUI_INLINE, quadratic_f32),
				(ATUI_NODESCR)
			),
			NULL, POWER_SOURCE_COUNT, // deferred start, count
			POWER_SOURCE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->qFeffCoeffBaseClock, u8"qFeffCoeffBaseClock", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"qFeffCoeffBaseClock (%s)",
				(ATUI_NAN, ATUI_INLINE, quadratic_f32),
				(ATUI_NODESCR)
			),
			NULL, POWER_SOURCE_COUNT, // deferred start, count
			POWER_SOURCE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->qFeffCoeffBoostClock, u8"qFeffCoeffBoostClock", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"qFeffCoeffBoostClock (%s)",
				(ATUI_NAN, ATUI_INLINE, quadratic_f32),
				(ATUI_NODESCR)
			),
			NULL, POWER_SOURCE_COUNT, // deferred start, count
			POWER_SOURCE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->Spare, u8"Spare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->MmHubPadding, u8"MmHubPadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, smu13_boardtable_v39, atomtree_powerplaytable,
	(bios->Version, u8"Version",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"should be unique to each board type"))
	),

	(bios->I2cControllers, u8"I2cControllers", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_NAN, ATUI_PETIOLE, i2ccontrollerconfig_u8),
				(ATUI_NODESCR)
			),
			NULL, // deferred start, count
			// count:
			sizeof(bios->I2cControllers)/sizeof(bios->I2cControllers[0]),
			I2cControllerName_SMU_13_0_7_e // enum
		)), (ATUI_NODESCR)
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
	(bios->VmempUlvPhaseSheddingMask, u8"VmempUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->VddioUlvPhaseSheddingMask, u8"VddioUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),

	(bios->SlaveAddrMapping, u8"SlaveAddrMapping", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SVI_PLANE_COUNT, // deferred start, count
			SVI_PLANE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->VrPsiSupport, u8"VrPsiSupport", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SVI_PLANE_COUNT, // deferred start, count
			SVI_PLANE_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->PaddingPsi, u8"PaddingPsi", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SVI_PLANE_COUNT, // deferred start, count
			SVI_PLANE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->EnablePsi6, u8"EnablePsi6", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SVI_PLANE_COUNT, // deferred start, count
			SVI_PLANE_e // enum
		)),
		((LANG_ENG, u8"only applicable in SVI3"))
	),
	(bios->SviTelemetryScale, u8"SviTelemetryScale", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_NAN, ATUI_INLINE, SviTelemetryScale_t),
				(ATUI_NODESCR)
			),
			NULL, SVI_PLANE_COUNT, // deferred start, count
			SVI_PLANE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->VoltageTelemetryRatio, u8"VoltageTelemetryRatio", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SVI_PLANE_COUNT, // deferred start, count
			SVI_PLANE_e // enum
		)),
		((LANG_ENG, u8"This is used for VDDIO  Svi2 Div Ratio workaround. It has 16 fractional bits (Q16.16)"))
	),

	(bios->DownSlewRateVr, u8"DownSlewRateVr", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SVI_PLANE_COUNT, // deferred start, count
			SVI_PLANE_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->LedOffGpio, u8"LedOffGpio",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanOffGpio, u8"FanOffGpio",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxVrPowerStageOffGpio, u8"GfxVrPowerStageOffGpio",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
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
		(ATUI_NODISPLAY, ATUI_INLINE, led_display_control),
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
	(bios->UclkTrainingModeSpreadPercent, u8"UclkTrainingModeSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->UclkSpreadPadding, u8"UclkSpreadPadding",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->UclkSpreadFreq, u8"UclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),
	(bios->UclkSpreadPercent, u8"UclkSpreadPercent", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, MEM_VENDOR_COUNT, // deferred start, count
			MEM_VENDOR_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->FclkSpreadPadding, u8"FclkSpreadPadding",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FclkSpreadPercent, u8"FclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->FclkSpreadFreq, u8"FclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),
	(bios->DramWidth, u8"DramWidth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Width of interface to the channel for each DRAM module. See DRAM_BIT_WIDTH_TYPE_e"))
	),
	(bios->PaddingMem1, u8"PaddingMem1",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
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

	(bios->PostVoltageSetBacoDelay, u8"PostVoltageSetBacoDelay",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in microseconds. Amount of time FW will wait after power good is established or PSI0 command is issued"))
	),
	(bios->BacoEntryDelay, u8"BacoEntryDelay",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in milliseconds. Amount of time FW will wait to trigger BACO entry after receiving entry notification from OS"))
	),

	(bios->FuseWritePowerMuxPresent, u8"FuseWritePowerMuxPresent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuseWritePadding, u8"FuseWritePadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->BoardSpare, u8"BoardSpare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->MmHubPadding, u8"MmHubPadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, smu13_smcpptable_v39, atomtree_powerplaytable,
	(bios->SkuTable, u8"SkuTable",
		(ATUI_NAN, ATUI_PETIOLE, smu13_skutable_v39),
		(ATUI_NODESCR)
	),
	(bios->BoardTable, u8"BoardTable",
		(ATUI_NAN, ATUI_PETIOLE, smu13_boardtable_v39),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_smc_dpm_info_table_13_0_7, atui_nullstruct,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->BoardTable, u8"BoardTable",
		(ATUI_NODISPLAY, ATUI_PETIOLE, smu13_boardtable_v39),
		(ATUI_NODESCR)
	)
)

