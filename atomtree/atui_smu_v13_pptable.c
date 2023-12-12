/*
For smu_v13_0_7_pptable.h and smu13_driver_if_v13_0_7.h
See atui_atomfirmware.c for how to use PPATUI_FUNCIFY()
*/

#include "atomtree.h"
#include "atui.h"

PPATUI_FUNCIFY(struct, smu_13_0_7_overdrive_table, atomtree_powerplaytable,
	(bios->revision, "revision",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Revision = SMU_13_0_7_PP_OVERDRIVE_VERSION"))
	),
	(bios->reserve, "reserve",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "Zero filled field reserved for future use"))
	),
	(bios->feature_count, "feature_count",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Total number of supported features"))
	),
	(bios->setting_count, "setting_count",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Total number of supported settings"))
	),

	(bios->cap, "Supported OD feature support flags", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "%s",
					// if CAP_COUNT changes, please change this 16
				(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
			),
			NULL, SMU_13_0_7_ODCAP_COUNT, // deferred start, count
			SMU_11_0_ODFEATURE_CAP // enum
		)), (ATUI_NODESCR)
	),
	((&(bios->cap[SMU_13_0_7_ODCAP_COUNT])), // start
		"Undefined OD feature support flags", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "OD feature [16 + %02u]",
					// if CAP_COUNT changes, please change this 16
				(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
			),
			NULL, // deferred start
			(SMU_13_0_7_MAX_ODFEATURE - SMU_13_0_7_ODCAP_COUNT), // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->max, "Supported Overdrive settings (max)", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "max: %s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_ODSETTING_COUNT, // deferred start, count
			SMU_13_0_7_ODSETTING_ID // enum
		)), (ATUI_NODESCR)
	),
	(bios->min, "Supported Overdrive settings (min)", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "min: %s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_ODSETTING_COUNT, // deferred start, count
			SMU_13_0_7_ODSETTING_ID // enum
		)), (ATUI_NODESCR)
	),
	((&(bios->max[SMU_13_0_7_ODSETTING_COUNT])), // start
		"Undefined OD settings (max)", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "max: [32 + %02u]",
					// if ODSETTING_COUNT changes, please change this 32
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			(SMU_13_0_7_MAX_ODSETTING - SMU_13_0_7_ODSETTING_COUNT), // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	((&(bios->min[SMU_13_0_7_ODSETTING_COUNT])), // start
		"Undefined OD settings (min)", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "min: [32 + %02u]",
					// if ODSETTING_COUNT changes, please change this 32
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			(SMU_13_0_7_MAX_ODSETTING - SMU_13_0_7_ODSETTING_COUNT), // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->pm_setting, "PowerMode feature settings", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_PMSETTING_COUNT, // deferred start, count
			SMU_13_0_7_PWRMODE_SETTING // enum
		)), ((LANG_ENG, "Optimized power mode feature settings"))
	),
	((&(bios->pm_setting[SMU_13_0_7_PMSETTING_COUNT])), // start
		"Undefined PowerMode feature settings", // name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "pm_setting [16 + %02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, // deferred start
			(SMU_13_0_7_MAX_PMSETTING - SMU_13_0_7_PMSETTING_COUNT), // count
			ATUI_NULL // enum
		)), ((LANG_ENG, "Optimized power mode feature settings"))
	)
)

PPATUI_FUNCIFY(struct, smu_13_0_7_powerplay_table, atomtree_powerplaytable,
	(bios->header, "header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		((LANG_ENG, "For PLUM_BONITO, header.format_revision = 15, header.content_revision = 0"))
	),
	(bios->table_revision, "table_revision",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "For PLUM_BONITO, table_revision = 2"))
	),
	(bios->padding, "padding",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->table_size, "table_size",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Driver portion table size. The offset to smc_pptable including header size"))
	),
	(bios->golden_pp_id, "golden_pp_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "PPGen use only: PP Table ID on the Golden Data Base"))
	),
	(bios->golden_revision, "golden_revision",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "PPGen use only: PP Table Revision on the Golden Data Base"))
	),
	(bios->format_id, "format_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "PPGen use only: PPTable for different ASICs. For PLUM_BONITO this should be 0x80"))
	),
	(bios->platform_caps, "platform_caps",
		(ATUI_NODISPLAY, ATUI_INLINE, powerplay_platform_caps),
		(ATUI_NODESCR)
	),

	(bios->thermal_controller_type, "thermal_controller_type",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "one of SMU_13_0_7_PP_THERMALCONTROLLER"))
	),

	(bios->small_power_limit1, "small_power_limit1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->small_power_limit2, "small_power_limit2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->boost_power_limit, "boost_power_limit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "For Gemini Board, when the slave adapter is in BACO mode, the master adapter will use this boost power limit instead of the default power limit to boost the power limit."))
	),
	(bios->software_shutdown_temp, "software_shutdown_temp",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->reserve, "reserve",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->overdrive_table, "overdrive_table",
		(ATUI_NAN, ATUI_PETIOLE, smu_13_0_7_overdrive_table),
		(ATUI_NODESCR)
	),

	(bios->padding1, "padding1",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)

	// struct smu13_smcpptable_v39 smc_pptable;
)



PPATUI_FUNCIFY(union, powerplay_feature_control_smu13, atomtree_powerplaytable,
	(bios->feature_control, "feature_control",
		(ATUI_HEX, ATUI_BITFIELD, (
			("FW_DATA_READ",            0,0, ATUI_DEC, (ATUI_NODESCR)),
			("DPM_GFXCLK",              1,1, ATUI_DEC, (ATUI_NODESCR)),
			("DPM_GFX_POWER_OPTIMIZER", 2,2, ATUI_DEC, (ATUI_NODESCR)),
			("DPM_UCLK",                3,3, ATUI_DEC, (ATUI_NODESCR)),
			("DPM_FCLK",                4,4, ATUI_DEC, (ATUI_NODESCR)),
			("DPM_SOCCLK",              5,5, ATUI_DEC, (ATUI_NODESCR)),
			("DPM_MP0CLK",              6,6, ATUI_DEC, (ATUI_NODESCR)),
			("DPM_LINK",                7,7, ATUI_DEC, (ATUI_NODESCR)),
			("DPM_DCN",                 8,8, ATUI_DEC, (ATUI_NODESCR)),
			("VMEMP_SCALING",           9,9, ATUI_DEC, (ATUI_NODESCR)),
			("VDDIO_MEM_SCALING",      10,10, ATUI_DEC, (ATUI_NODESCR)),
			("DS_GFXCLK",              11,11, ATUI_DEC, (ATUI_NODESCR)),
			("DS_SOCCLK",              12,12, ATUI_DEC, (ATUI_NODESCR)),
			("DS_FCLK",                13,13, ATUI_DEC, (ATUI_NODESCR)),
			("DS_LCLK",                14,14, ATUI_DEC, (ATUI_NODESCR)),
			("DS_DCFCLK",              15,15, ATUI_DEC, (ATUI_NODESCR)),
			("DS_UCLK",                16,16, ATUI_DEC, (ATUI_NODESCR)),
			("GFX_ULV",                17,17, ATUI_DEC, (ATUI_NODESCR)),
			("FW_DSTATE",              18,18, ATUI_DEC, (ATUI_NODESCR)),
			("GFXOFF",                 19,19, ATUI_DEC, (ATUI_NODESCR)),
			("BACO",                   20,20, ATUI_DEC, (ATUI_NODESCR)),
			("MM_DPM",                 21,21, ATUI_DEC, (ATUI_NODESCR)),
			("SOC_MPCLK_DS",           22,22, ATUI_DEC, (ATUI_NODESCR)),
			("BACO_MPCLK_DS",          23,23, ATUI_DEC, (ATUI_NODESCR)),
			("THROTTLERS",             24,24, ATUI_DEC, (ATUI_NODESCR)),
			("SMARTSHIFT",             25,25, ATUI_DEC, (ATUI_NODESCR)),
			("GTHR",                   26,26, ATUI_DEC, (ATUI_NODESCR)),
			("ACDC",                   27,27, ATUI_DEC, (ATUI_NODESCR)),
			("VR0HOT",                 28,28, ATUI_DEC, (ATUI_NODESCR)),
			("FW_CTF",                 29,29, ATUI_DEC, (ATUI_NODESCR)),
			("FAN_CONTROL",            30,30, ATUI_DEC, (ATUI_NODESCR)),
			("GFX_DCS",                31,31, ATUI_DEC, (ATUI_NODESCR)),
			("GFX_READ_MARGIN",        32,32, ATUI_DEC, (ATUI_NODESCR)),
			("LED_DISPLAY",            33,33, ATUI_DEC, (ATUI_NODESCR)),
			("GFXCLK_SPREAD_SPECTRUM", 34,34, ATUI_DEC, (ATUI_NODESCR)),
			("OUT_OF_BAND_MONITOR",    35,35, ATUI_DEC, (ATUI_NODESCR)),
			("OPTIMIZED_VMIN",         36,36, ATUI_DEC, (ATUI_NODESCR)),
			("GFX_IMU",                37,37, ATUI_DEC, (ATUI_NODESCR)),
			("BOOT_TIME_CAL",          38,38, ATUI_DEC, (ATUI_NODESCR)),
			("GFX_PCC_DFLL",           39,39, ATUI_DEC, (ATUI_NODESCR)),
			("SOC_CG",                 40,40, ATUI_DEC, (ATUI_NODESCR)),
			("DF_CSTATE",              41,41, ATUI_DEC, (ATUI_NODESCR)),
			("GFX_EDC",                42,42, ATUI_DEC, (ATUI_NODESCR)),
			("BOOT_POWER_OPT",         43,43, ATUI_DEC, (ATUI_NODESCR)),
			("CLOCK_POWER_DOWN_BYPASS",44,44, ATUI_DEC, (ATUI_NODESCR)),
			("DS_VCN",                 45,45, ATUI_DEC, (ATUI_NODESCR)),
			("BACO_CG",                46,46, ATUI_DEC, (ATUI_NODESCR)),
			("MEM_TEMP_READ",          47,47, ATUI_DEC, (ATUI_NODESCR)),
			("ATHUB_MMHUB_PG",         48,48, ATUI_DEC, (ATUI_NODESCR)),
			("SOC_PCC",                49,49, ATUI_DEC, (ATUI_NODESCR)),
			("EDC_PWRBRK",             50,50, ATUI_DEC, (ATUI_NODESCR)),
			("SPARE_51",               51,51, ATUI_DEC, (ATUI_NODESCR)),
			("SPARE_52",               52,52, ATUI_DEC, (ATUI_NODESCR)),
			("SPARE_53",               53,53, ATUI_DEC, (ATUI_NODESCR)),
			("SPARE_54",               54,54, ATUI_DEC, (ATUI_NODESCR)),
			("SPARE_55",               55,55, ATUI_DEC, (ATUI_NODESCR)),
			("SPARE_56",               56,56, ATUI_DEC, (ATUI_NODESCR)),
			("SPARE_57",               57,57, ATUI_DEC, (ATUI_NODESCR)),
			("SPARE_58",               58,58, ATUI_DEC, (ATUI_NODESCR)),
			("SPARE_59",               59,59, ATUI_DEC, (ATUI_NODESCR)),
			("SPARE_60",               60,60, ATUI_DEC, (ATUI_NODESCR)),
			("SPARE_61",               61,61, ATUI_DEC, (ATUI_NODESCR)),
			("SPARE_62",               62,62, ATUI_DEC, (ATUI_NODESCR)),
			("SPARE_63",               63,63, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, dpm_debug_override_smu13, atui_nullstruct,
	(bios->DebugOverrides, "DebugOverrides",
		(ATUI_BIN, ATUI_BITFIELD, (
			("disable_volt_link_vcn_fclk",   0,0, ATUI_DEC, (ATUI_NODESCR)),
			("disable_volt_link_dcn_fclk",   1,1, ATUI_DEC, (ATUI_NODESCR)),
			("disable_volt_link_mp0_fclk",   2,2, ATUI_DEC, (ATUI_NODESCR)),
			("disable_volt_link_vcn_dcfclk", 3,3, ATUI_DEC, (ATUI_NODESCR)),
			("disable_fast_fclk_timer",      4,4, ATUI_DEC, (ATUI_NODESCR)),
			("disable_vcn_pg",               5,5, ATUI_DEC, (ATUI_NODESCR)),
			("disable_fmax_vmax",            6,6, ATUI_DEC, (ATUI_NODESCR)),
			("disable_imu_fw_checks",        7,7, ATUI_DEC, (ATUI_NODESCR)),
			("disable_d0i2_reentry_hsr_timer_check", 8,8, ATUI_DEC,
				(ATUI_NODESCR)
			),
			("disable_dfll",                 9,9, ATUI_DEC, (ATUI_NODESCR)),
			("enable_rlc_vf_bringup_mode",  10,10, ATUI_DEC, (ATUI_NODESCR)),
			("dfll_master_mode",            11,11, ATUI_DEC, (ATUI_NODESCR)),
			("enable_profiling_mode",       12,12, ATUI_DEC, (ATUI_NODESCR)),
			("reserved",                    31,13, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, throttler_control_smu13_0x35, atui_nullstruct,
	(bios->ThrottlerControlMask, "ThrottlerControlMask",
		(ATUI_BIN, ATUI_BITFIELD, (
			("TEMP_EDGE",      0,0, ATUI_DEC, (ATUI_NODESCR)),
			("TEMP_HOTSPOT",   1,1, ATUI_DEC, (ATUI_NODESCR)),
			("TEMP_HOTSPOT_G", 2,2, ATUI_DEC, (ATUI_NODESCR)),
			("TEMP_HOTSPOT_M", 3,3, ATUI_DEC, (ATUI_NODESCR)),
			("TEMP_MEM",       4,4, ATUI_DEC, (ATUI_NODESCR)),
			("TEMP_VR_GFX",    5,5, ATUI_DEC, (ATUI_NODESCR)),
			("TEMP_VR_MEM0",   6,6, ATUI_DEC, (ATUI_NODESCR)),
			("TEMP_VR_MEM1",   7,7, ATUI_DEC, (ATUI_NODESCR)),
			("TEMP_VR_SOC",    8,8, ATUI_DEC, (ATUI_NODESCR)),
			("TEMP_VR_U",      9,9, ATUI_DEC, (ATUI_NODESCR)),
			("TEMP_LIQUID0",  10,10, ATUI_DEC, (ATUI_NODESCR)),
			("TEMP_LIQUID1",  11,11, ATUI_DEC, (ATUI_NODESCR)),
			("TEMP_PLX",      12,12, ATUI_DEC, (ATUI_NODESCR)),
			("TDC_GFX",       13,13, ATUI_DEC, (ATUI_NODESCR)),
			("TDC_SOC",       14,14, ATUI_DEC, (ATUI_NODESCR)),
			("TDC_U",         15,15, ATUI_DEC, (ATUI_NODESCR)),
			("PPT0",          16,16, ATUI_DEC, (ATUI_NODESCR)),
			("PPT1",          17,17, ATUI_DEC, (ATUI_NODESCR)),
			("PPT2",          18,18, ATUI_DEC, (ATUI_NODESCR)),
			("PPT3",          19,19, ATUI_DEC, (ATUI_NODESCR)),
			("FIT",           20,20, ATUI_DEC, (ATUI_NODESCR)),
			("GFX_APCC_PLUS", 21,21, ATUI_DEC, (ATUI_NODESCR)),
			("reserved",      31,22, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, fw_dstate_features_smu13_0x35, atui_nullstruct,
	(bios->FwDStateMask, "FwDStateMask",
		(ATUI_BIN, ATUI_BITFIELD, (
			("SOC_ULV",           0,0, ATUI_DEC, (ATUI_NODESCR)),
			("G6_HSR",            1,1, ATUI_DEC, (ATUI_NODESCR)),
			("G6_PHY_VMEMP_OFF",  2,2, ATUI_DEC, (ATUI_NODESCR)),
			("SMN_DS",            3,3, ATUI_DEC, (ATUI_NODESCR)),
			("MP1_WHISPER_MODE",  4,4, ATUI_DEC, (ATUI_NODESCR)),
			("SOC_LIV_MIN",       5,5, ATUI_DEC, (ATUI_NODESCR)),
			("SOC_PLL_PWRDN",     6,6, ATUI_DEC, (ATUI_NODESCR)),
			("MEM_PLL_PWRDN",     7,7, ATUI_DEC, (ATUI_NODESCR)),
			("MALL_ALLOC",        8,8, ATUI_DEC, (ATUI_NODESCR)),
			("MEM_PSI",           9,9, ATUI_DEC, (ATUI_NODESCR)),
			("HSR_NON_STROBE",    10,10, ATUI_DEC, (ATUI_NODESCR)),
			("MP0_ENTER_WFI",     11,11, ATUI_DEC, (ATUI_NODESCR)),
			("U_ULV",             12,12, ATUI_DEC, (ATUI_NODESCR)),
			("MALL_FLUSH",        13,13, ATUI_DEC, (ATUI_NODESCR)),
			("SOC_PSI",           14,14, ATUI_DEC, (ATUI_NODESCR)),
			("U_PSI",             15,15, ATUI_DEC, (ATUI_NODESCR)),
			("UCP_DS",            16,16, ATUI_DEC, (ATUI_NODESCR)),
			("CSRCLK_DS",         17,17, ATUI_DEC, (ATUI_NODESCR)),
			("MMHUB_INTERLOCK",   18,18, ATUI_DEC, (ATUI_NODESCR)),
			("D0i3_2_QUIET_FW",   19,19, ATUI_DEC, (ATUI_NODESCR)),
			("CLDO_PRG",          20,20, ATUI_DEC, (ATUI_NODESCR)),
			("DF_PLL_PWRDN",      21,21, ATUI_DEC, (ATUI_NODESCR)),
			("U_LOW_PWR_MODE_EN", 22,22, ATUI_DEC, (ATUI_NODESCR)),
			("GFX_PSI6",          23,23, ATUI_DEC, (ATUI_NODESCR)),
			("GFX_VR_PWR_STAGE",  24,24, ATUI_DEC, (ATUI_NODESCR)),
			("reserved",          31,25, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, DpmDescriptor_t, atomtree_powerplaytable,
	(bios->Padding, "Padding",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SnapToDiscrete, "SnapToDiscrete",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0 - Fine grained DPM, 1 - Discrete DPM"))
	),
	(bios->NumDiscreteLevels, "NumDiscreteLevels",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Set to 2 (Fmin, Fmax) when using fine grained DPM, otherwise set to # discrete levels used"))
	),
	(bios->CalculateFopt, "CalculateFopt",
		(ATUI_DEC, ATUI_ENUM, FOPT_CALC_e),
		((LANG_ENG, "Indication whether FW should calculate Fopt or use values below. Reference FOPT_CALC_e"))
	),
	(bios->ConversionToAvfsClk, "ConversionToAvfsClk",
		(ATUI_NAN, ATUI_INLINE, linear_f32),
		((LANG_ENG, "Transfer function to AVFS Clock (GHz->GHz)"))
	),
	(bios->Padding3, "Padding3",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->Padding4, "Padding4",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FoptimalDc, "FoptimalDc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Foptimal frequency in DC power mode."))
	),
	(bios->FoptimalAc, "FoptimalAc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Foptimal frequency in AC power mode."))
	),
	(bios->Padding2, "Padding2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, BootValues_t, atomtree_powerplaytable,
	(bios->InitGfxclk_bypass, "InitGfxclk_bypass",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 0"))
	),
	(bios->InitSocclk, "InitSocclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 0"))
	),
	(bios->InitMp0clk, "InitMp0clk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 0"))
	),
	(bios->InitMpioclk, "InitMpioclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 0"))
	),
	(bios->InitSmnclk, "InitSmnclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 0"))
	),
	(bios->InitUcpclk, "InitUcpclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 0"))
	),
	(bios->InitCsrclk, "InitCsrclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 0"))
	),

	(bios->InitDprefclk, "InitDprefclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 1"))
	),
	(bios->InitDcfclk, "InitDcfclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 1"))
	),
	(bios->InitDtbclk, "InitDtbclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 1"))
	),
	(bios->InitDclk, "InitDclk",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "PLL 2. assume same DCLK/VCLK for both instances"))
	),
	(bios->InitVclk, "InitVclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 2"))
	),
	(bios->InitUsbdfsclk, "InitUsbdfsclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 3"))
	),
	(bios->InitMp1clk, "InitMp1clk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 3"))
	),
	(bios->InitLclk, "InitLclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 3"))
	),
	(bios->InitBaco400clk_bypass, "InitBaco400clk_bypass",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 3"))
	),
	(bios->InitBaco1200clk_bypass, "InitBaco1200clk_bypass",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 3"))
	),
	(bios->InitBaco700clk_bypass, "InitBaco700clk_bypass",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 3"))
	),
	(bios->InitFclk, "InitFclk",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 4"))
	),
	(bios->InitGfxclk_clkb, "InitGfxclk_clkb",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "PLL 5"))
	),
	(bios->InitUclkDPMState, "InitUclkDPMState",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "PLL 6. =0,1,2,3, frequency from FreqTableUclk"))
	),

	(bios->Padding, "Padding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->InitVcoFreqPll0, "InitVcoFreqPll0",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->InitVcoFreqPll1, "InitVcoFreqPll1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->InitVcoFreqPll2, "InitVcoFreqPll2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->InitVcoFreqPll3, "InitVcoFreqPll3",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->InitVcoFreqPll4, "InitVcoFreqPll4",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->InitVcoFreqPll5, "InitVcoFreqPll5",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->InitVcoFreqPll6, "InitVcoFreqPll6",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->InitGfx, "InitGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2) ,  should be 0?"))
	),
	(bios->InitSoc, "InitSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2)"))
	),
	(bios->InitU, "InitU",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In Mv(Q2) not applicable"))
	),

	(bios->Padding2, "Padding2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Spare, "Spare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, MsgLimits_t, atomtree_powerplaytable,
	// TODO unroll? dynarray inline?
	// uint16_t Power[PPT_THROTTLER_COUNT][POWER_SOURCE_COUNT]; // Watts

	(bios->Tdc, "Tdc", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "Tdc (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, TDC_THROTTLER_COUNT_SMU13, // deferred start, count
			TDC_THROTTLER_e // enum
		)),
		((LANG_ENG, "Amps"))
	),

	(bios->Temperature, "Temperature", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "Temperature (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_TEMP_COUNT, // deferred start, count
			SMU_13_0_7_TEMP_e // enum
		)),
		((LANG_ENG, "Celsius"))
	),

	(bios->PwmLimitMin, "PwmLimitMin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PwmLimitMax, "PwmLimitMax",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetTemperature, "FanTargetTemperature",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Spare1, "Spare1",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->AcousticTargetRpmThresholdMin, "AcousticTargetRpmThresholdMin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->AcousticTargetRpmThresholdMax, "AcousticTargetRpmThresholdMax",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->AcousticLimitRpmThresholdMin, "AcousticLimitRpmThresholdMin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->AcousticLimitRpmThresholdMax, "AcousticLimitRpmThresholdMax",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->PccLimitMin, "PccLimitMin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PccLimitMax, "PccLimitMax",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FanStopTempMin, "FanStopTempMin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanStopTempMax, "FanStopTempMax",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanStartTempMin, "FanStartTempMin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanStartTempMax, "FanStartTempMax",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->PowerMinPpt0, "PowerMinPpt0", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "PowerMinPpt0 (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, POWER_SOURCE_COUNT, // deferred start, count
			POWER_SOURCE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->Spare, "Spare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, DriverReportedClocks_t, atomtree_powerplaytable,
	(bios->BaseClockAc, "BaseClockAc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GameClockAc, "GameClockAc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BoostClockAc, "BoostClockAc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BaseClockDc, "BaseClockDc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GameClockDc, "GameClockDc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BoostClockDc, "BoostClockDc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Reserved, "Reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, AvfsDcBtcParams_smu13, atomtree_powerplaytable,
	(bios->DcBtcEnabled, "DcBtcEnabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding, "Padding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->DcTol, "DcTol",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mV Q2"))
	),
	(bios->DcBtcGb, "DcBtcGb",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mV Q2"))
	),

	(bios->DcBtcMin, "DcBtcMin",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mV Q2"))
	),
	(bios->DcBtcMax, "DcBtcMax",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mV Q2"))
	),

	(bios->DcBtcGbScalar, "DcBtcGbScalar",
		(ATUI_NAN, ATUI_INLINE, linear_f32),
		(ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, AvfsFuseOverride_smu13, atomtree_powerplaytable,
	(bios->AvfsTemp, "AvfsTemp", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "AvfsTemp (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, AVFS_TEMP_COUNT, // deferred start, count
			AVFS_TEMP_e // enum
		)),
		((LANG_ENG, "in degrees C"))
	),
	(bios->VftFMin, "VftFMin",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in MHz"))
	),
	(bios->VInversion, "VInversion",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in mV Q2"))
	),
	(bios->qVft, "qVft", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "qVft (%s)",
				(ATUI_NAN, ATUI_INLINE, quadratic_f32),
				(ATUI_NODESCR)
			),
			NULL, AVFS_TEMP_COUNT, // deferred start, count
			AVFS_TEMP_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->qAvfsGb, "qAvfsGb",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->qAvfsGb2, "qAvfsGb2",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, SviTelemetryScale_t, atomtree_powerplaytable,
	(bios->Offset, "Offset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Padding, "Padding",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MaxCurrent, "MaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	)
)


PPATUI_FUNCIFY(struct, overdrivelimits_smu13, atomtree_powerplaytable,
	(bios->FeatureCtrlMask, "FeatureCtrlMask",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->VoltageOffsetPerZoneBoundary, "VoltageOffsetPerZoneBoundary",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved1, "Reserved1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Reserved2, "Reserved2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->GfxclkFmin, "GfxclkFmin",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "MHz"))
	),
	(bios->GfxclkFmax, "GfxclkFmax",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "MHz"))
	),
	(bios->UclkFmin, "UclkFmin",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "MHz"))
	),
	(bios->UclkFmax, "UclkFmax",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "MHz"))
	),

	(bios->Ppt, "Ppt",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "%"))
	),
	(bios->Tdc, "Tdc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FanLinearPwmPoints, "FanLinearPwmPoints",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanLinearTempPoints, "FanLinearTempPoints",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanMinimumPwm, "FanMinimumPwm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->AcousticTargetRpmThreshold, "AcousticTargetRpmThreshold",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->AcousticLimitRpmThreshold, "AcousticLimitRpmThreshold",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetTemperature, "FanTargetTemperature",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Degree Celcius"))
	),
	(bios->FanZeroRpmEnable, "FanZeroRpmEnable",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanZeroRpmStopTemp, "FanZeroRpmStopTemp",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanMode, "FanMode",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MaxOpTemp, "MaxOpTemp",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding, "Padding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->Spare, "Spare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, smu13_skutable_v39, atomtree_powerplaytable,

	(bios->Version, "Version",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "should be unique to each SKU(i.e if any value changes in below structure then this value must be different)"))
	),

	(bios->features, "features",
		(ATUI_NAN, ATUI_PETIOLE, powerplay_feature_control_smu13),
		(ATUI_NODESCR)
	),

	(bios->TotalPowerConfig, "TotalPowerConfig",
		(ATUI_DEC, ATUI_ENUM, PwrConfig_e),
		((LANG_ENG, "Determines how PMFW calculates the power."))
	),
	(bios->CustomerVariant, "CustomerVariant",
		(ATUI_DEC, ATUI_ENUM, CUSTOMER_VARIANT_e),
		((LANG_ENG, "To specify if this PPTable is intended for a particular customer. Use defines from CUSTOMER_VARIANT_e"))
	),
	(bios->MemoryTemperatureTypeMask, "MemoryTemperatureTypeMask",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Bit mapping indicating which methods of memory temperature reading are enabled. Use defines from MEM_TEMP_*BIT"))
	),
	(bios->SmartShiftVersion, "SmartShiftVersion",
		(ATUI_DEC, ATUI_ENUM, SMARTSHIFT_VERSION_e),
		((LANG_ENG, "Determine what SmartShift feature version is supported"))
	),

	(bios->SocketPowerLimitAc, "SocketPowerLimitAc", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "PPT %u",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PPT_THROTTLER_COUNT, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "In Watts. Power limit that PMFW attempts to control to in AC mode. Multiple limits supported"))
	),
	(bios->SocketPowerLimitDc, "SocketPowerLimitDc", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "PPT %u",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PPT_THROTTLER_COUNT, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "In Watts. Power limit that PMFW attempts to control to in DC mode. Multiple limits supported"))
	),

	(bios->SocketPowerLimitSmartShift2, "SocketPowerLimitSmartShift2",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In Watts. Power limit used SmartShift"))
	),
	(bios->EnableLegacyPptLimit, "EnableLegacyPptLimit",
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "if set to 1, SocketPowerLimitAc and SocketPowerLimitDc will be interpreted as legacy programs(i.e absolute power). If 0, all except index 0 will be scalars. Relative index 0."))
	),
	(bios->UseInputTelemetry, "UseInputTelemetry",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "applicable to SVI3 only and only to be set if VRs support"))
	),
	(bios->SmartShiftMinReportedPptinDcs, "SmartShiftMinReportedPptinDcs",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "minimum possible active power consumption for this SKU. Used for SmartShift power reporting"))
	),

	(bios->PaddingPpt, "PaddingPpt",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->VrTdcLimit, "VrTdcLimit", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "VrTdcLimit (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, TDC_THROTTLER_COUNT_SMU13, // deferred start, count
			TDC_THROTTLER_e // enum
		)),
		((LANG_ENG, "In Amperes. Current limit associated with VR regulator maximum temperature"))
	),

	(bios->PlatformTdcLimit, "PlatformTdcLimit", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "PlatformTdcLimit (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, TDC_THROTTLER_COUNT_SMU13, // deferred start, count
			TDC_THROTTLER_e // enum
		)),
		((LANG_ENG, "In Amperes. Current limit associated with platform maximum temperature per VR current rail"))
	),

	(bios->TemperatureLimit, "TemperatureLimit", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "TemperatureLimit (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_TEMP_COUNT, // deferred start, count
			SMU_13_0_7_TEMP_e // enum
		)),
		((LANG_ENG, "In degrees Celsius. Temperature limit associated with each input"))
	),

	(bios->HwCtfTempLimit, "HwCtfTempLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In degrees Celsius. Temperature above which HW will trigger CTF. Consumed by VBIOS only"))
	),

	(bios->PaddingInfra, "PaddingInfra",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FitControllerFailureRateLimit, "FitControllerFailureRateLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Expected GFX Duty Cycle at Vmax."))
	),
	(bios->FitControllerGfxDutyCycle, "FitControllerGfxDutyCycle",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Expected SOC Duty Cycle at Vmax."))
	),
	(bios->FitControllerSocDutyCycle, "FitControllerSocDutyCycle",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FitControllerSocOffset, "FitControllerSocOffset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->GfxApccPlusResidencyLimit, "GfxApccPlusResidencyLimit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Percentage value. Used by APCC+ controller to control PCC residency to some value"))
	),
	(bios->ThrottlerControlMask, "ThrottlerControlMask",
		(ATUI_NODISPLAY, ATUI_INLINE, throttler_control_smu13_0x35),
		(ATUI_NODESCR)
	),

	(bios->FwDStateMask, "FwDStateMask",
		(ATUI_NAN, ATUI_INLINE, fw_dstate_features_smu13_0x35),
		(ATUI_NODESCR)
	),

	(bios->UlvVoltageOffset, "UlvVoltageOffset", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "UlvVoltageOffset (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "In mV(Q2). ULV offset used in either GFX_ULV or SOC_ULV(part of FW_DSTATE)"))
	),

	(bios->UlvVoltageOffsetU, "UlvVoltageOffsetU",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2). ULV offset used in either U_ULV(part of FW_DSTATE)"))
	),
	(bios->DeepUlvVoltageOffsetSoc, "DeepUlvVoltageOffsetSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2)  Long Idle Vmin (deep ULV), for VDD_SOC as part of FW_DSTATE"))
	),
	(bios->DefaultMaxVoltage, "DefaultMaxVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "DefaultMaxVoltage (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "In mV(Q2) Maximum voltage without FIT controller enabled"))
	),
	(bios->BoostMaxVoltage, "BoostMaxVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "BoostMaxVoltage (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "In mV(Q2) Maximum voltage with FIT controller enabled"))
	),
	(bios->VminTempHystersis, "VminTempHystersis", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "VminTempHystersis (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "Celsius Temperature hysteresis for switching between low/high temperature values for Vmin"))
	),
	(bios->VminTempThreshold, "VminTempThreshold", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "VminTempThreshold (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "Celsius Temperature threshold for switching between low/high temperature values for Vmin"))
	),
	(bios->Vmin_Hot_T0, "Vmin_Hot_T0", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "Vmin_Hot_T0 (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "In mV(Q2) Initial (pre-aging) Vset to be used at hot."))
	),
	(bios->Vmin_Cold_T0, "Vmin_Cold_T0", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "Vmin_Cold_T0 (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "In mV(Q2) Initial (pre-aging) Vset to be used at cold."))
	),
	(bios->Vmin_Hot_Eol, "Vmin_Hot_Eol", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "Vmin_Hot_Eol (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "In mV(Q2) End-of-life Vset to be used at hot."))
	),
	(bios->Vmin_Cold_Eol, "Vmin_Cold_Eol", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "Vmin_Cold_Eol (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "In mV(Q2) End-of-life Vset to be used at cold."))
	),
	(bios->Vmin_Aging_Offset, "Vmin_Aging_Offset", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "Vmin_Aging_Offset (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "In mV(Q2) Worst-case aging margin"))
	),
	(bios->Spare_Vmin_Plat_Offset_Hot, "Spare_Vmin_Plat_Offset_Hot", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "Spare_Vmin_Plat_Offset_Hot (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "In mV(Q2) Platform offset apply to T0 Hot"))
	),
	(bios->Spare_Vmin_Plat_Offset_Cold, "Spare_Vmin_Plat_Offset_Cold", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "Spare_Vmin_Plat_Offset_Cold (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "In mV(Q2) Platform offset apply to T0 Cold"))
	),
	(bios->VcBtcFixedVminAgingOffset, "VcBtcFixedVminAgingOffset", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "VcBtcFixedVminAgingOffset (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "Linear offset or GB term to account for mis-correlation between PSM and Vmin shift trends across parts."))
	),
	(bios->VcBtcVmin2PsmDegrationGb, "VcBtcVmin2PsmDegrationGb", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "VcBtcVmin2PsmDegrationGb (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "Scalar coefficient of the PSM aging degradation function"))
	),
	(bios->VcBtcPsmA, "VcBtcPsmA", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "VcBtcPsmA (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "A_PSM  // Exponential coefficient of the PSM aging degradation function"))
	),
	(bios->VcBtcPsmB, "VcBtcPsmB", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "VcBtcPsmB (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "B_PSM  // Scalar coefficient of the VMIN aging degradation function. Specified as worst case between hot and cold."))
	),
	(bios->VcBtcVminA, "VcBtcVminA", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "VcBtcVminA (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "A_VMIN // Exponential coefficient of the VMIN aging degradation function. Specified as worst case between hot and cold."))
	),
	(bios->VcBtcVminB, "VcBtcVminB", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "VcBtcVminB (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)),
		((LANG_ENG, "B_VMIN"))
	),

	(bios->PerPartVminEnabled, "PerPartVminEnabled", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "PerPartVminEnabled (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->VcBtcEnabled, "VcBtcEnabled", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "VcBtcEnabled (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PMFW_VOLT_PLANE_COUNT, // deferred start, count
			PMFW_VOLT_PLANE_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->SocketPowerLimitAcTau, "SocketPowerLimitAcTau", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "PPT %u",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PPT_THROTTLER_COUNT, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "Time constant of LPF in ms"))
	),
	(bios->SocketPowerLimitDcTau, "SocketPowerLimitDcTau", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "PPT %u",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PPT_THROTTLER_COUNT, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "Time constant of LPF in ms"))
	),

	(bios->Vmin_droop, "Vmin_droop",
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->SpareVmin, "SpareVmin",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->DpmDescriptor, "DpmDescriptor", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "DpmDescriptor (%s)",
				(ATUI_NAN, ATUI_PETIOLE, DpmDescriptor_t), (ATUI_NODESCR)
			),
			NULL, SMU13_PPCLK_COUNT, // deferred start, count
			SMU13_PPCLK_e // enum
		)), (ATUI_NODESCR)
	),




	(bios->FreqTableGfx, "FreqTableGfx", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FreqTableGfx [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_GFXCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "In MHz"))
	),
	(bios->FreqTableVclk, "FreqTableVclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FreqTableVclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_VCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "In MHz"))
	),
	(bios->FreqTableDclk, "FreqTableDclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FreqTableDclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "In MHz"))
	),
	(bios->FreqTableSocclk, "FreqTableSocclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FreqTableSocclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_SOCCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "In MHz"))
	),
	(bios->FreqTableUclk, "FreqTableUclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FreqTableUclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "In MHz"))
	),
	(bios->FreqTableDispclk, "FreqTableDispclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FreqTableDispclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DISPCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "In MHz"))
	),
	(bios->FreqTableDppClk, "FreqTableDppClk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FreqTableDppClk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DPPCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "In MHz"))
	),
	(bios->FreqTableDprefclk, "FreqTableDprefclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FreqTableDprefclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DPREFCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "In MHz"))
	),
	(bios->FreqTableDcfclk, "FreqTableDcfclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FreqTableDcfclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DCFCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "In MHz"))
	),
	(bios->FreqTableDtbclk, "FreqTableDtbclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FreqTableDtbclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_DTBCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "In MHz"))
	),
	(bios->FreqTableFclk, "FreqTableFclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FreqTableFclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_FCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "In MHz"))
	),

	(bios->DcModeMaxFreq, "DcModeMaxFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "DcModeMaxFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU13_PPCLK_COUNT, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "In MHz"))
	),
	(bios->Mp0clkFreq, "Mp0clkFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "Mp0clkFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_MP0CLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "in MHz"))
	),
	(bios->Mp0DpmVoltage, "Mp0DpmVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "Mp0DpmVoltage [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_MP0CLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "mV(Q2)"))
	),

	(bios->GfxclkSpare, "GfxclkSpare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->GfxclkFreqCap, "GfxclkFreqCap",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxclkFgfxoffEntry, "GfxclkFgfxoffEntry",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Mhz"))
	),
	(bios->GfxclkFgfxoffExitImu, "GfxclkFgfxoffExitImu",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Mhz"))
	),
	(bios->GfxclkFgfxoffExitRlc, "GfxclkFgfxoffExitRlc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Mhz"))
	),
	(bios->GfxclkThrottleClock, "GfxclkThrottleClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Used primarily in DCS"))
	),
	(bios->EnableGfxPowerStagesGpio, "EnableGfxPowerStagesGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Genlk_vsync GPIO flag used to control gfx power stages"))
	),
	(bios->GfxIdlePadding, "GfxIdlePadding",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->SmsRepairWRCKClkDivEn, "SmsRepairWRCKClkDivEn",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SmsRepairWRCKClkDivVal, "SmsRepairWRCKClkDivVal",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxOffEntryEarlyMGCGEn, "GfxOffEntryEarlyMGCGEn",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxOffEntryForceCGCGEn, "GfxOffEntryForceCGCGEn",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxOffEntryForceCGCGDelayEn, "GfxOffEntryForceCGCGDelayEn",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxOffEntryForceCGCGDelayVal, "GfxOffEntryForceCGCGDelayVal",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in microseconds"))
	),

	(bios->GfxclkFreqGfxUlv, "GfxclkFreqGfxUlv",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in MHz"))
	),
	(bios->GfxIdlePadding2, "GfxIdlePadding2",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->GfxOffEntryHysteresis, "GfxOffEntryHysteresis",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "For RLC to count after it enters CGCG, and before triggers GFXOFF entry"))
	),
	(bios->GfxoffSpare, "GfxoffSpare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->DfllBtcMasterScalerM, "DfllBtcMasterScalerM",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DfllBtcMasterScalerB, "DfllBtcMasterScalerB",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DfllBtcSlaveScalerM, "DfllBtcSlaveScalerM",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DfllBtcSlaveScalerB, "DfllBtcSlaveScalerB",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DfllPccAsWaitCtrl, "DfllPccAsWaitCtrl",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GDFLL_AS_WAIT_CTRL_PCC register value to be passed to RLC msg"))
	),
	(bios->DfllPccAsStepCtrl, "DfllPccAsStepCtrl",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GDFLL_AS_STEP_CTRL_PCC register value to be passed to RLC msg"))
	),
	(bios->GfxGpoSpare, "GfxGpoSpare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->DcsGfxOffVoltage, "DcsGfxOffVoltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Voltage in mV(Q2) applied to VDDGFX when entering DCS GFXOFF phase"))
	),
	(bios->PaddingDcs, "PaddingDcs",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->DcsMinGfxOffTime, "DcsMinGfxOffTime",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Minimum amount of time PMFW shuts GFX OFF as part of GFX DCS phase"))
	),
	(bios->DcsMaxGfxOffTime, "DcsMaxGfxOffTime",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Maximum amount of time PMFW can shut GFX OFF as part of GFX DCS phase at a stretch."))
	),

	(bios->DcsMinCreditAccum, "DcsMinCreditAccum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Min amount of positive credit accumulation before waking GFX up as part of DCS."))
	),

	(bios->DcsExitHysteresis, "DcsExitHysteresis",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "The min amount of time power credit accumulator should have a value > 0 before SMU exits the DCS throttling phase."))
	),
	(bios->DcsTimeout, "DcsTimeout",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "This is the amount of time SMU FW waits for RLC to put GFX into GFXOFF before reverting to the fallback mechanism of throttling GFXCLK to Fmin."))
	),


	(bios->DcsSpare, "DcsSpare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->ShadowFreqTableUclk, "ShadowFreqTableUclk", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "ShadowFreqTableUclk [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "In MHz"))
	),
	(bios->UseStrobeModeOptimizations, "UseStrobeModeOptimizations",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Set to indicate that FW should use strobe mode optimizations"))
	),
	(bios->PaddingMem, "PaddingMem",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->UclkDpmPstates, "UclkDpmPstates", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "UclkDpmPstates [%02u]",
				(ATUI_DEC, ATUI_ENUM, DPM_PSTATES_e), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "4 DPM states."))
	),
	(bios->FreqTableUclkDiv, "FreqTableUclkDiv", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FreqTableUclkDiv [%02u]",
				(ATUI_DEC, ATUI_ENUM, UCLK_DIV_e), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->MemVmempVoltage, "MemVmempVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "MemVmempVoltage [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "mV(Q2)"))
	),
	(bios->MemVddioVoltage, "MemVddioVoltage", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "MemVddioVoltage [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_UCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "mV(Q2)"))
	),

	(bios->FclkDpmUPstates, "FclkDpmUPstates", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FclkDpmUPstates [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_FCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "U P-state ID associated with each FCLK DPM state."))
	),
	(bios->FclkDpmVddU, "FclkDpmVddU", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FclkDpmVddU [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_FCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "mV(Q2) Vset U voltage associated with each FCLK DPM state."))
	),
	(bios->FclkDpmUSpeed, "FclkDpmUSpeed", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FclkDpmUSpeed [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_FCLK_DPM_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "U speed associated with each FCLK DPM state"))
	),
	(bios->FclkDpmDisallowPstateFreq, "FclkDpmDisallowPstateFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Frequency which FW will target when indicated that display config cannot support P-state. Set to 0 use FW calculated value"))
	),
	(bios->PaddingFclk, "PaddingFclk",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PcieGenSpeed, "PcieGenSpeed", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "PcieGenSpeed [%02u]",
				(ATUI_DEC, ATUI_ENUM, PCIE_SPEED_e), (ATUI_NODESCR)
			),
			NULL, NUM_LINK_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->PcieLaneCount, "PcieLaneCount", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "PcieLaneCount [%02u]",
				(ATUI_DEC, ATUI_ENUM, PCIE_WIDTH_e), (ATUI_NODESCR)
			),
			NULL, NUM_LINK_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->LclkFreq, "LclkFreq", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "LclkFreq [%02u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, NUM_LINK_LEVELS_SMU13, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->FanStopTemp, "FanStopTemp", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FanStopTemp (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_TEMP_COUNT, // deferred start, count
			SMU_13_0_7_TEMP_e // enum
		)),
		((LANG_ENG, "Celsius"))
	),
	(bios->FanStartTemp, "FanStartTemp", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FanStartTemp (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_TEMP_COUNT, // deferred start, count
			SMU_13_0_7_TEMP_e // enum
		)),
		((LANG_ENG, "Celsius"))
	),

	(bios->FanGain, "FanGain", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FanGain (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_TEMP_COUNT, // deferred start, count
			SMU_13_0_7_TEMP_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->FanGainPadding, "FanGainPadding",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FanPwmMin, "FanPwmMin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->AcousticTargetRpmThreshold, "AcousticTargetRpmThreshold",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->AcousticLimitRpmThreshold, "AcousticLimitRpmThreshold",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanMaximumRpm, "FanMaximumRpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MGpuAcousticLimitRpmThreshold, "MGpuAcousticLimitRpmThreshold",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetGfxclk, "FanTargetGfxclk",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TempInputSelectMask, "TempInputSelectMask",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanZeroRpmEnable, "FanZeroRpmEnable",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTachEdgePerRev, "FanTachEdgePerRev",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetTemperature, "FanTargetTemperature", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FanTargetTemperature (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_TEMP_COUNT, // deferred start, count
			SMU_13_0_7_TEMP_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_ErrorSetDelta, "FuzzyFan_ErrorSetDelta",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_ErrorRateSetDelta, "FuzzyFan_ErrorRateSetDelta",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_PwmSetDelta, "FuzzyFan_PwmSetDelta",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_Reserved, "FuzzyFan_Reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FwCtfLimit, "FwCtfLimit", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "FwCtfLimit (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SMU_13_0_7_TEMP_COUNT, // deferred start, count
			SMU_13_0_7_TEMP_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->IntakeTempEnableRPM, "IntakeTempEnableRPM",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->IntakeTempOffsetTemp, "IntakeTempOffsetTemp",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->IntakeTempReleaseTemp, "IntakeTempReleaseTemp",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->IntakeTempHighIntakeAcousticLimit, "IntakeTempHighIntakeAcousticLimit",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->IntakeTempAcouticLimitReleaseRate, "IntakeTempAcouticLimitReleaseRate",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FanAbnormalTempLimitOffset, "FanAbnormalTempLimitOffset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanStalledTriggerRpm, "FanStalledTriggerRpm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanAbnormalTriggerRpmCoeff, "FanAbnormalTriggerRpmCoeff",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanAbnormalDetectionEnable, "FanAbnormalDetectionEnable",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FanIntakeSensorSupport, "FanIntakeSensorSupport",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanIntakePadding, "FanIntakePadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->FanSpare, "FanSpare",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "SECTION: VDD_GFX AVFS"))
	),

	(bios->OverrideGfxAvfsFuses, "OverrideGfxAvfsFuses",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxAvfsPadding, "GfxAvfsPadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->L2HwRtAvfsFuses, "L2HwRtAvfsFuses", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "L2HwRtAvfsFuses (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_GRTAVFS_HW_FUSE_COUNT, // deferred start, count
			PP_GRTAVFS_HW_FUSE_e // enum
		)),
		((LANG_ENG, "see fusedoc for encoding"))
	),
	(bios->SeHwRtAvfsFuses, "SeHwRtAvfsFuses", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "SeHwRtAvfsFuses (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_GRTAVFS_HW_FUSE_COUNT, // deferred start, count
			PP_GRTAVFS_HW_FUSE_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->CommonRtAvfs, "CommonRtAvfs", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "CommonRtAvfs (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_GRTAVFS_FW_COMMON_FUSE_COUNT, // deferred start, count
			PP_GRTAVFS_FW_COMMON_FUSE_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->L2FwRtAvfsFuses, "L2FwRtAvfsFuses", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "L2FwRtAvfsFuses (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_GRTAVFS_FW_SEP_FUSE_COUNT, // deferred start, count
			PP_GRTAVFS_FW_SEP_FUSE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->SeFwRtAvfsFuses, "SeFwRtAvfsFuses", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "SeFwRtAvfsFuses (%s)",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_GRTAVFS_FW_SEP_FUSE_COUNT, // deferred start, count
			PP_GRTAVFS_FW_SEP_FUSE_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->Droop_PWL_F, "Droop_PWL_F", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "Droop_PWL_F [%u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_NUM_RTAVFS_PWL_ZONES, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->Droop_PWL_a, "Droop_PWL_a", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "Droop_PWL_a [%u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_NUM_RTAVFS_PWL_ZONES, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->Droop_PWL_b, "Droop_PWL_b", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "Droop_PWL_b [%u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_NUM_RTAVFS_PWL_ZONES, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(bios->Droop_PWL_c, "Droop_PWL_c", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "Droop_PWL_c [%u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_NUM_RTAVFS_PWL_ZONES, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->Static_PWL_Offset, "Static_PWL_Offset", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "Static_PWL_Offset [%u]",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, PP_NUM_RTAVFS_PWL_ZONES, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->dGbV_dT_vmin, "dGbV_dT_vmin",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dGbV_dT_vmax, "dGbV_dT_vmax",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->V2F_vmin_range_low, "V2F_vmin_range_low",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->V2F_vmin_range_high, "V2F_vmin_range_high",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->V2F_vmax_range_low, "V2F_vmax_range_low",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->V2F_vmax_range_high, "V2F_vmax_range_high",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->DcBtcGfxParams, "DcBtcGfxParams",
		(ATUI_NAN, ATUI_INLINE, AvfsDcBtcParams_smu13),
		(ATUI_NODESCR)
	),
	(bios->GfxAvfsSpare, "GfxAvfsSpare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->OverrideSocAvfsFuses, "OverrideSocAvfsFuses",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MinSocAvfsRevision, "MinSocAvfsRevision",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocAvfsPadding, "SocAvfsPadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->SocAvfsFuseOverride, "SocAvfsFuseOverride", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "SocAvfsFuseOverride (%s)",
				(ATUI_NAN, ATUI_PETIOLE, AvfsFuseOverride_smu13),
				(ATUI_NODESCR)
			),
			NULL, AVFS_D_COUNT, // deferred start, count
			AVFS_D_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->dBtcGbSoc, "dBtcGbSoc", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "dBtcGbSoc (%s)",
				(ATUI_NAN, ATUI_INLINE, droop_f32),
				(ATUI_NODESCR)
			),
			NULL, AVFS_D_COUNT, // deferred start, count
			AVFS_D_e // enum
		)),
		((LANG_ENG, "GHz->V BtcGb"))
	),

	(bios->qAgingGb, "qAgingGb", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "qAgingGb (%s)",
				(ATUI_NAN, ATUI_INLINE, linear_f32),
				(ATUI_NODESCR)
			),
			NULL, AVFS_D_COUNT, // deferred start, count
			AVFS_D_e // enum
		)),
		((LANG_ENG, "GHz->V"))
	),

	(bios->qStaticVoltageOffset, "qStaticVoltageOffset", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "qStaticVoltageOffset (%s)",
				(ATUI_NAN, ATUI_INLINE, quadratic_f32),
				(ATUI_NODESCR)
			),
			NULL, AVFS_D_COUNT, // deferred start, count
			AVFS_D_e // enum
		)),
		((LANG_ENG, "GHz->V"))
	),

	(bios->DcBtcSocParams, "DcBtcSocParams", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "DcBtcSocParams (%s)",
				(ATUI_NAN, ATUI_INLINE, AvfsDcBtcParams_smu13),
				(ATUI_NODESCR)
			),
			NULL, AVFS_D_COUNT, // deferred start, count
			AVFS_D_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->SocAvfsSpare, "SocAvfsSpare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->BootValues, "BootValues",
		(ATUI_NAN, ATUI_PETIOLE, BootValues_t),
		(ATUI_NODESCR)
	),

	(bios->DriverReportedClocks, "DriverReportedClocks",
		(ATUI_NAN, ATUI_PETIOLE, DriverReportedClocks_t),
		(ATUI_NODESCR)
	),
	(bios->MsgLimits, "MsgLimits",
		(ATUI_NAN, ATUI_PETIOLE, MsgLimits_t),
		(ATUI_NODESCR)
	),
	(bios->OverDriveLimitsMin, "OverDriveLimitsMin",
		(ATUI_NAN, ATUI_PETIOLE, overdrivelimits_smu13),
		(ATUI_NODESCR)
	),
	(bios->OverDriveLimitsBasicMax, "OverDriveLimitsBasicMax",
		(ATUI_NAN, ATUI_PETIOLE, overdrivelimits_smu13),
		(ATUI_NODESCR)
	),
	(bios->OverDriveLimitsAdvancedMax, "OverDriveLimitsAdvancedMax",
		(ATUI_NAN, ATUI_PETIOLE, overdrivelimits_smu13),
		(ATUI_NODESCR)
	),
	(bios->DebugOverrides, "DebugOverrides",
		(ATUI_NAN, ATUI_INLINE, dpm_debug_override_smu13),
		(ATUI_NODESCR)
	),


	(bios->TotalBoardPowerSupport, "TotalBoardPowerSupport",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TotalBoardPowerPadding, "TotalBoardPowerPadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->TotalIdleBoardPowerM, "TotalIdleBoardPowerM",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TotalIdleBoardPowerB, "TotalIdleBoardPowerB",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TotalBoardPowerM, "TotalBoardPowerM",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TotalBoardPowerB, "TotalBoardPowerB",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->qFeffCoeffGameClock, "qFeffCoeffGameClock", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "qFeffCoeffGameClock (%s)",
				(ATUI_NAN, ATUI_INLINE, quadratic_f32),
				(ATUI_NODESCR)
			),
			NULL, POWER_SOURCE_COUNT, // deferred start, count
			POWER_SOURCE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->qFeffCoeffBaseClock, "qFeffCoeffBaseClock", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "qFeffCoeffBaseClock (%s)",
				(ATUI_NAN, ATUI_INLINE, quadratic_f32),
				(ATUI_NODESCR)
			),
			NULL, POWER_SOURCE_COUNT, // deferred start, count
			POWER_SOURCE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->qFeffCoeffBoostClock, "qFeffCoeffBoostClock", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "qFeffCoeffBoostClock (%s)",
				(ATUI_NAN, ATUI_INLINE, quadratic_f32),
				(ATUI_NODESCR)
			),
			NULL, POWER_SOURCE_COUNT, // deferred start, count
			POWER_SOURCE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->Spare, "Spare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->MmHubPadding, "MmHubPadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, smu13_boardtable_v39, atomtree_powerplaytable,
	(bios->Version, "Version",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "should be unique to each board type"))
	),

	(bios->I2cControllers, "I2cControllers", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "%s",
				(ATUI_NAN, ATUI_PETIOLE, i2ccontrollerconfig_u8),
				(ATUI_NODESCR)
			),
			NULL, // deferred start, count
			// count:
			sizeof(bios->I2cControllers)/sizeof(bios->I2cControllers[0]),
			I2cControllerName_SMU_13_0_7_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->VddGfxVrMapping, "VddGfxVrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Use VR_MAPPING* bitfields"))
	),
	(bios->VddSocVrMapping, "VddSocVrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Use VR_MAPPING* bitfields"))
	),
	(bios->VddMem0VrMapping, "VddMem0VrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Use VR_MAPPING* bitfields"))
	),
	(bios->VddMem1VrMapping, "VddMem1VrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Use VR_MAPPING* bitfields"))
	),

	(bios->GfxUlvPhaseSheddingMask, "GfxUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, "set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->SocUlvPhaseSheddingMask, "SocUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, "set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->VmempUlvPhaseSheddingMask, "VmempUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, "set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->VddioUlvPhaseSheddingMask, "VddioUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, "set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),

	(bios->SlaveAddrMapping, "SlaveAddrMapping", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SVI_PLANE_COUNT, // deferred start, count
			SVI_PLANE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->VrPsiSupport, "VrPsiSupport", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SVI_PLANE_COUNT, // deferred start, count
			SVI_PLANE_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->PaddingPsi, "PaddingPsi", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SVI_PLANE_COUNT, // deferred start, count
			SVI_PLANE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->EnablePsi6, "EnablePsi6", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SVI_PLANE_COUNT, // deferred start, count
			SVI_PLANE_e // enum
		)),
		((LANG_ENG, "only applicable in SVI3"))
	),
	(bios->SviTelemetryScale, "SviTelemetryScale", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "%s",
				(ATUI_NAN, ATUI_INLINE, SviTelemetryScale_t),
				(ATUI_NODESCR)
			),
			NULL, SVI_PLANE_COUNT, // deferred start, count
			SVI_PLANE_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->VoltageTelemetryRatio, "VoltageTelemetryRatio", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SVI_PLANE_COUNT, // deferred start, count
			SVI_PLANE_e // enum
		)),
		((LANG_ENG, "This is used for VDDIO  Svi2 Div Ratio workaround. It has 16 fractional bits (Q16.16)"))
	),

	(bios->DownSlewRateVr, "DownSlewRateVr", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, SVI_PLANE_COUNT, // deferred start, count
			SVI_PLANE_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->LedOffGpio, "LedOffGpio",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanOffGpio, "FanOffGpio",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxVrPowerStageOffGpio, "GfxVrPowerStageOffGpio",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->AcDcGpio, "AcDcGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for AC/DC switching"))
	),
	(bios->AcDcPolarity, "AcDcPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO polarity for AC/DC switching"))
	),
	(bios->VR0HotGpio, "VR0HotGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for VR0 HOT event"))
	),
	(bios->VR0HotPolarity, "VR0HotPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO polarity for VR0 HOT event"))
	),

	(bios->GthrGpio, "GthrGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for GTHR Event"))
	),
	(bios->GthrPolarity, "GthrPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "replace GPIO polarity for GTHR"))
	),
	(bios->LedPin0, "LedPin0",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO number for LedPin[0]"))
	),
	(bios->LedPin1, "LedPin1",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO number for LedPin[1]"))
	),
	(bios->LedPin2, "LedPin2",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO number for LedPin[2]"))
	),
	(bios->LedEnableMask, "LedEnableMask",
		(ATUI_NODISPLAY, ATUI_INLINE, led_display_control),
		(ATUI_NODESCR)
	),

	(bios->LedPcie, "LedPcie",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO number for PCIE results"))
	),
	(bios->LedError, "LedError",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO number for Error Cases"))
	),
	(bios->UclkTrainingModeSpreadPercent, "UclkTrainingModeSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(bios->UclkSpreadPadding, "UclkSpreadPadding",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->UclkSpreadFreq, "UclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),
	(bios->UclkSpreadPercent, "UclkSpreadPercent", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "%s",
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, MEM_VENDOR_COUNT, // deferred start, count
			MEM_VENDOR_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->FclkSpreadPadding, "FclkSpreadPadding",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FclkSpreadPercent, "FclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(bios->FclkSpreadFreq, "FclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),
	(bios->DramWidth, "DramWidth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Width of interface to the channel for each DRAM module. See DRAM_BIT_WIDTH_TYPE_e"))
	),
	(bios->PaddingMem1, "PaddingMem1",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->HsrEnabled, "HsrEnabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->VddqOffEnabled, "VddqOffEnabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PaddingUmcFlags, "PaddingUmcFlags",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->PostVoltageSetBacoDelay, "PostVoltageSetBacoDelay",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in microseconds. Amount of time FW will wait after power good is established or PSI0 command is issued"))
	),
	(bios->BacoEntryDelay, "BacoEntryDelay",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in milliseconds. Amount of time FW will wait to trigger BACO entry after receiving entry notification from OS"))
	),

	(bios->FuseWritePowerMuxPresent, "FuseWritePowerMuxPresent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuseWritePadding, "FuseWritePadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->BoardSpare, "BoardSpare",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->MmHubPadding, "MmHubPadding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, smu13_smcpptable_v39, atomtree_powerplaytable,
	(bios->SkuTable, "SkuTable",
		(ATUI_NAN, ATUI_PETIOLE, smu13_skutable_v39),
		(ATUI_NODESCR)
	),
	(bios->BoardTable, "BoardTable",
		(ATUI_NAN, ATUI_PETIOLE, smu13_boardtable_v39),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_smc_dpm_info_table_13_0_7, atui_nullstruct,
	(bios->table_header, "table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->BoardTable, "BoardTable",
		(ATUI_NODISPLAY, ATUI_PETIOLE, smu13_boardtable_v39),
		(ATUI_NODESCR)
	)
)

