/*
For smu_v11_pptable.h and smu11_driver_if.h -- navi1 PowerPlay tables
See atui_atomfirmware.c for how to use PPATUI_FUNCIFY()
*/

#include "atomtree.h"
#include "atui.h"

PPATUI_FUNCIFY(struct, dpm_descriptor_smu11, atui_nullstruct,
	(bios->VoltageMode, VoltageMode,
		(ATUI_DEC, ATUI_ENUM, VOLTAGE_MODE_e),
		(ATUI_NODESCR)
	),
	(bios->SnapToDiscrete, SnapToDiscrete,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0 - Fine grained DPM, 1 - Discrete DPM"))
	),
	(bios->NumDiscreteLevels, NumDiscreteLevels,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Set to 2 (Fmin, Fmax) when using fine grained  DPM, otherwise set to # discrete levels used"))
	),
	(bios->padding, padding,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ConversionToAvfsClk, ConversionToAvfsClk,
		(ATUI_NAN, ATUI_INLINE, linear_f32),
		((LANG_ENG, "Transfer function to AVFS Clock (GHz->GHz)"))
	),
	(bios->slowslow_curve, slowslow_curve,
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		((LANG_ENG, "Slow-slow curve (GHz->V)"))
	)
)

PPATUI_FUNCIFY(union, powerplay_feature_control_smu11_19, atomtree_powerplaytable,
	(bios->feature_control, feature_control,
		(ATUI_BIN, ATUI_BITFIELD, (
			(DPM_PREFETCHER, 0,0, ATUI_DEC, (ATUI_NODESCR)),
			(DPM_GFXCLK,     1,1, ATUI_DEC, (ATUI_NODESCR)),
			(DPM_UCLK,       2,2, ATUI_DEC, (ATUI_NODESCR)),
			(DPM_SOCCLK,     3,3, ATUI_DEC, (ATUI_NODESCR)),
			(DPM_UVD,        4,4, ATUI_DEC, (ATUI_NODESCR)),
			(DPM_VCE,        5,5, ATUI_DEC, (ATUI_NODESCR)),
			(ULV,            6,6, ATUI_DEC, (ATUI_NODESCR)),
			(DPM_MP0CLK,     7,7, ATUI_DEC, (ATUI_NODESCR)),
			(DPM_LINK,       8,8, ATUI_DEC, (ATUI_NODESCR)),
			(DPM_DCEFCLK,    9,9, ATUI_DEC, (ATUI_NODESCR)),
			(DS_GFXCLK,     10,10, ATUI_DEC, (ATUI_NODESCR)),
			(DS_SOCCLK,     11,11, ATUI_DEC, (ATUI_NODESCR)),
			(DS_LCLK,       12,12, ATUI_DEC, (ATUI_NODESCR)),
			(PPT,           13,13, ATUI_DEC, (ATUI_NODESCR)),
			(TDC,           14,14, ATUI_DEC, (ATUI_NODESCR)),
			(THERMAL,       15,15, ATUI_DEC, (ATUI_NODESCR)),
			(GFX_PER_CU_CG, 16,16, ATUI_DEC, (ATUI_NODESCR)),
			(RM,            17,17, ATUI_DEC, (ATUI_NODESCR)),
			(DS_DCEFCLK,    18,18, ATUI_DEC, (ATUI_NODESCR)),
			(ACDC,          19,19, ATUI_DEC, (ATUI_NODESCR)),
			(VR0HOT,        20,20, ATUI_DEC, (ATUI_NODESCR)),
			(VR1HOT,        21,21, ATUI_DEC, (ATUI_NODESCR)),
			(FW_CTF,        22,22, ATUI_DEC, (ATUI_NODESCR)),
			(LED_DISPLAY,   23,23, ATUI_DEC, (ATUI_NODESCR)),
			(FAN_CONTROL,   24,24, ATUI_DEC, (ATUI_NODESCR)),
			(GFX_EDC,       25,25, ATUI_DEC, (ATUI_NODESCR)),
			(GFXOFF,        26,26, ATUI_DEC, (ATUI_NODESCR)),
			(CG,            27,27, ATUI_DEC, (ATUI_NODESCR)),
			(DPM_FCLK,      28,28, ATUI_DEC, (ATUI_NODESCR)),
			(DS_FCLK,       29,29, ATUI_DEC, (ATUI_NODESCR)),
			(DS_MP1CLK,     30,30, ATUI_DEC, (ATUI_NODESCR)),
			(DS_MP0CLK,     31,31, ATUI_DEC, (ATUI_NODESCR)),
			(XGMI,          32,32, ATUI_DEC, (ATUI_NODESCR)),
			(ECC,           33,33, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_34,      34,34, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_35,      35,35, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_36,      36,36, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_37,      37,37, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_38,      38,38, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_39,      39,39, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_40,      40,40, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_41,      41,41, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_42,      42,42, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_43,      43,43, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_44,      44,44, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_45,      45,45, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_46,      46,46, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_47,      47,47, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_48,      48,48, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_49,      49,49, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_50,      50,50, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_51,      51,51, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_52,      52,52, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_53,      53,53, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_54,      54,54, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_55,      55,55, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_56,      56,56, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_57,      57,57, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_58,      58,58, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_59,      59,59, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_60,      60,60, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_61,      61,61, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_62,      62,62, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_63,      63,63, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, powerplay_feature_control_smu11_51, atomtree_powerplaytable,
	(bios->feature_control, feature_control,
		(ATUI_BIN, ATUI_BITFIELD, (
			(DPM_PREFETCHER,      0,0, ATUI_DEC, (ATUI_NODESCR)),
			(DPM_GFXCLK,          1,1, ATUI_DEC, (ATUI_NODESCR)),
			(DPM_GFX_PACE,        2,2, ATUI_DEC, (ATUI_NODESCR)),
			(DPM_UCLK,            3,3, ATUI_DEC, (ATUI_NODESCR)),
			(DPM_SOCCLK,          4,4, ATUI_DEC, (ATUI_NODESCR)),
			(DPM_MP0CLK,          5,5, ATUI_DEC, (ATUI_NODESCR)),
			(DPM_LINK,            6,6, ATUI_DEC, (ATUI_NODESCR)),
			(DPM_DCEFCLK,         7,7, ATUI_DEC, (ATUI_NODESCR)),
			(MEM_VDDCI_SCALING,   8,8, ATUI_DEC, (ATUI_NODESCR)),
			(MEM_MVDD_SCALING,    9,9, ATUI_DEC, (ATUI_NODESCR)),
			(DS_GFXCLK,           10,10, ATUI_DEC, (ATUI_NODESCR)),
			(DS_SOCCLK,           11,11, ATUI_DEC, (ATUI_NODESCR)),
			(DS_LCLK,             12,12, ATUI_DEC, (ATUI_NODESCR)),
			(DS_DCEFCLK,          13,13, ATUI_DEC, (ATUI_NODESCR)),
			(DS_UCLK,             14,14, ATUI_DEC, (ATUI_NODESCR)),
			(GFX_ULV,             15,15, ATUI_DEC, (ATUI_NODESCR)),
			(FW_DSTATE,           16,16, ATUI_DEC, (ATUI_NODESCR)),
			(GFXOFF,              17,17, ATUI_DEC, (ATUI_NODESCR)),
			(BACO,                18,18, ATUI_DEC, (ATUI_NODESCR)),
			(VCN_PG,              19,19, ATUI_DEC, (ATUI_NODESCR)),
			(JPEG_PG,             20,20, ATUI_DEC, (ATUI_NODESCR)),
			(USB_PG,              21,21, ATUI_DEC, (ATUI_NODESCR)),
			(RSMU_SMN_CG,         22,22, ATUI_DEC, (ATUI_NODESCR)),
			(PPT,                 23,23, ATUI_DEC, (ATUI_NODESCR)),
			(TDC,                 24,24, ATUI_DEC, (ATUI_NODESCR)),
			(GFX_EDC,             25,25, ATUI_DEC, (ATUI_NODESCR)),
			(APCC_PLUS,           26,26, ATUI_DEC, (ATUI_NODESCR)),
			(GTHR,                27,27, ATUI_DEC, (ATUI_NODESCR)),
			(ACDC,                28,28, ATUI_DEC, (ATUI_NODESCR)),
			(VR0HOT,              29,29, ATUI_DEC, (ATUI_NODESCR)),
			(VR1HOT,              30,30, ATUI_DEC, (ATUI_NODESCR)),
			(FW_CTF,              31,31, ATUI_DEC, (ATUI_NODESCR)),
			(FAN_CONTROL,         32,32, ATUI_DEC, (ATUI_NODESCR)),
			(THERMAL,             33,33, ATUI_DEC, (ATUI_NODESCR)),
			(GFX_DCS,             34,34, ATUI_DEC, (ATUI_NODESCR)),
			(RM,                  35,35, ATUI_DEC, (ATUI_NODESCR)),
			(LED_DISPLAY,         36,36, ATUI_DEC, (ATUI_NODESCR)),
			(GFX_SS,              37,37, ATUI_DEC, (ATUI_NODESCR)),
			(OUT_OF_BAND_MONITOR, 38,38, ATUI_DEC, (ATUI_NODESCR)),
			(TEMP_DEPENDENT_VMIN, 39,39, ATUI_DEC, (ATUI_NODESCR)),
			(MMHUB_PG,            40,40, ATUI_DEC, (ATUI_NODESCR)),
			(ATHUB_PG,            41,41, ATUI_DEC, (ATUI_NODESCR)),
			(APCC_DFLL,           42,42, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_43,            43,43, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_44,            44,44, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_45,            45,45, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_46,            46,46, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_47,            47,47, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_48,            48,48, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_49,            49,49, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_50,            50,50, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_51,            51,51, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_52,            52,52, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_53,            53,53, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_54,            54,54, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_55,            55,55, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_56,            56,56, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_57,            57,57, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_58,            58,58, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_59,            59,59, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_60,            60,60, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_61,            61,61, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_62,            62,62, ATUI_DEC, (ATUI_NODESCR)),
			(SPARE_63,            63,63, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, dpm_debug_override_smu11_19, atomtree_powerplaytable,
	(bios->dpm_debug_override_flags, dpm_debug_override_flags,
		(ATUI_BIN, ATUI_BITFIELD, (
			(disable_socclk_pid,              0,0, ATUI_DEC, (ATUI_NODESCR)),
			(disable_uclk_pid,                1,1, ATUI_DEC, (ATUI_NODESCR)),
			(enable_volt_link_uvd_socclk,     2,2, ATUI_DEC, (ATUI_NODESCR)),
			(enable_volt_link_uvd_uclk,       3,3, ATUI_DEC, (ATUI_NODESCR)),
			(enable_freq_link_vclk_socclk,    4,4, ATUI_DEC, (ATUI_NODESCR)),
			(enable_freq_link_vclk_uclk,      5,5, ATUI_DEC, (ATUI_NODESCR)),
			(enable_freq_link_dclk_socclk,    6,6, ATUI_DEC, (ATUI_NODESCR)),
			(enable_freq_link_dclk_uclk,      7,7, ATUI_DEC, (ATUI_NODESCR)),
			(enable_volt_link_vce_socclk,     8,8, ATUI_DEC, (ATUI_NODESCR)),
			(enable_volt_link_vce_uclk,       9,9, ATUI_DEC, (ATUI_NODESCR)),
			(enable_freq_link_eclk_socclk,   10,10, ATUI_DEC, (ATUI_NODESCR)),
			(enable_freq_link_eclk_uclk,     11,11, ATUI_DEC, (ATUI_NODESCR)),
			(enable_freq_link_gfxclk_socclk, 12,12, ATUI_DEC, (ATUI_NODESCR)),
			(enable_freq_link_gfxclk_uclk,   13,13, ATUI_DEC, (ATUI_NODESCR)),
			(enable_gfxoff_gfxclk_switch,    14,14, ATUI_DEC, (ATUI_NODESCR)),
			(enable_gfxoff_socclk_switch,    15,15, ATUI_DEC, (ATUI_NODESCR)),
			(enable_gfxoff_uclk_switch,      16,16, ATUI_DEC, (ATUI_NODESCR)),
			(enable_gfxoff_fclk_switch,      17,17, ATUI_DEC, (ATUI_NODESCR)),
			(reserved,                       31,18, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, dpm_debug_override_smu11_51, atomtree_powerplaytable,
	(bios->dpm_debug_override_flags, dpm_debug_override_flags,
		(ATUI_BIN, ATUI_BITFIELD, (
			(disable_socclk_pid,               0,0, ATUI_DEC, (ATUI_NODESCR)),
			(disable_uclk_pid,                 1,1, ATUI_DEC, (ATUI_NODESCR)),
			(disable_volt_link_vcn_socclk,     2,2, ATUI_DEC, (ATUI_NODESCR)),
			(enable_freq_link_vclk_socclk,     3,3, ATUI_DEC, (ATUI_NODESCR)),
			(enable_freq_link_dclk_socclk,     4,4, ATUI_DEC, (ATUI_NODESCR)),
			(enable_freq_link_gfxclk_socclk,   5,5, ATUI_DEC, (ATUI_NODESCR)),
			(enable_freq_link_gfxclk_uclk,     6,6, ATUI_DEC, (ATUI_NODESCR)),
			(disable_volt_link_dce_socclk,     7,7, ATUI_DEC, (ATUI_NODESCR)),
			(disable_volt_link_mp0_socclk,     8,8, ATUI_DEC, (ATUI_NODESCR)),
			(disable_dfll_pll_shutdown,        9,9, ATUI_DEC, (ATUI_NODESCR)),
			(disable_memory_temperature_read, 10,10, ATUI_DEC, (ATUI_NODESCR)),
			(reserved,                        31,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, smu11_pptable_v3_i2c_u32, atomtree_powerplaytable,
	(bios->i2ccontroller_vr_gfx, i2ccontroller_vr_gfx,
		(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u32),
		(ATUI_NODESCR)
	),
	(bios->i2ccontroller_vr_soc, i2ccontroller_vr_soc,
		(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u32),
		(ATUI_NODESCR)
	),
	(bios->i2ccontroller_vr_vddci, i2ccontroller_vr_vddci,
		(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u32),
		(ATUI_NODESCR)
	),
	(bios->i2ccontroller_vr_mvdd, i2ccontroller_vr_mvdd,
		(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u32),
		(ATUI_NODESCR)
	),
	(bios->i2ccontroller_liquid_0, i2ccontroller_liquid_0,
		(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u32),
		(ATUI_NODESCR)
	),
	(bios->i2ccontroller_liquid_1, i2ccontroller_liquid_1,
		(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u32),
		(ATUI_NODESCR)
	),
	(bios->i2ccontroller_plx, i2ccontroller_plx,
		(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u32),
		(ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, smu11_pptable_v8_i2c_u8mixed, atomtree_powerplaytable,
	(bios->i2ccontroller_vr_gfx, i2ccontroller_vr_gfx,
		(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u8_mixed),
		(ATUI_NODESCR)
	),
	(bios->i2ccontroller_vr_soc, i2ccontroller_vr_soc,
		(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u8_mixed),
		(ATUI_NODESCR)
	),
	(bios->i2ccontroller_vr_vddci, i2ccontroller_vr_vddci,
		(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u8_mixed),
		(ATUI_NODESCR)
	),
	(bios->i2ccontroller_vr_mvdd, i2ccontroller_vr_mvdd,
		(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u8_mixed),
		(ATUI_NODESCR)
	),
	(bios->i2ccontroller_liquid_0, i2ccontroller_liquid_0,
		(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u8_mixed),
		(ATUI_NODESCR)
	),
	(bios->i2ccontroller_liquid_1, i2ccontroller_liquid_1,
		(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u8_mixed),
		(ATUI_NODESCR)
	),
	(bios->i2ccontroller_plx, i2ccontroller_plx,
		(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u8_mixed),
		(ATUI_NODESCR)
	),
	(bios->i2ccontroller_spare, i2ccontroller_spare,
		(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u8_mixed),
		(ATUI_NODESCR)
	)
)

/* does not account for dynarray's enum
'<,'>s@\(u\?int[0-9]\+_t\s\+\)\([a-zA-Z0-9_]\+\)\[\([a-zA-Z0-9_]\+\)\]@(NULL, \2,\r\t\t(ATUI_NAN, ATUI_DYNARRAY, (\r\t\t\t(ATUI_NULL, \2 [%02u],\r\t\t\t\t(ATU
I_DEC, ATUI_NOFANCY), (ATUI_NODESCR)\r\t\t\t),\r\t\t\tbios->\2, \3 \/\/ start, count\r\t\t)), (ATUI_NODESCR)\r\t),@
*/
PPATUI_FUNCIFY(struct, smu11_smcpptable_v3, atomtree_powerplaytable,
	(bios->Version, Version,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->SocketPowerLimitAc0, SocketPowerLimitAc0,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitAc0Tau, SocketPowerLimitAc0Tau,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitAc1, SocketPowerLimitAc1,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitAc1Tau, SocketPowerLimitAc1Tau,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitAc2, SocketPowerLimitAc2,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitAc2Tau, SocketPowerLimitAc2Tau,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitAc3, SocketPowerLimitAc3,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitAc3Tau, SocketPowerLimitAc3Tau,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitDc, SocketPowerLimitDc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocketPowerLimitDcTau, SocketPowerLimitDcTau,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TdcLimitSoc, TdcLimitSoc,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Amps"))
	),
	(bios->TdcLimitSocTau, TdcLimitSocTau,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Time constant of LPF in ms"))
	),
	(bios->TdcLimitGfx, TdcLimitGfx,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Amps"))
	),
	(bios->TdcLimitGfxTau, TdcLimitGfxTau,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Time constant of LPF in ms"))
	),



	(bios->TedgeLimit, TedgeLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->ThotspotLimit, ThotspotLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->ThbmLimit, ThbmLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->Tvr_gfxLimit, Tvr_gfxLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->Tliquid1Limit, Tliquid1Limit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->Tliquid2Limit, Tliquid2Limit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->TplxLimit, TplxLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->FitLimit, FitLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Failures in time (failures per million parts over the defined lifetime)"))
	),

	(bios->PpmPowerLimit, PpmPowerLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Switch this this power limit when temperature is above PpmTempThreshold"))
	),
	(bios->PpmTemperatureThreshold, PpmTemperatureThreshold,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->MemoryOnPackage, MemoryOnPackage,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding8_limits, padding8_limits,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Tvr_SocLimit, Tvr_SocLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),

	(bios->UlvVoltageOffsetSoc, UlvVoltageOffsetSoc,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2)"))
	),
	(bios->UlvVoltageOffsetGfx, UlvVoltageOffsetGfx,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2)"))
	),

	(bios->UlvSmnclkDid, UlvSmnclkDid,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "DID for ULV mode. 0 means CLK will not be modified in ULV."))
	),
	(bios->UlvMp1clkDid, UlvMp1clkDid,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "DID for ULV mode. 0 means CLK will not be modified in ULV."))
	),
	(bios->UlvGfxclkBypass, UlvGfxclkBypass,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "1 to turn off/bypass Gfxclk during ULV, 0 to leave Gfxclk on during ULV"))
	),
	(bios->Padding234, Padding234,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->MinVoltageGfx, MinVoltageGfx,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2) Minimum Voltage (\"Vmin\") of VDD_GFX"))
	),
	(bios->MinVoltageSoc, MinVoltageSoc,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2) Minimum Voltage (\"Vmin\") of VDD_SOC"))
	),
	(bios->MaxVoltageGfx, MaxVoltageGfx,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2) Maximum Voltage allowable of VDD_GFX"))
	),
	(bios->MaxVoltageSoc, MaxVoltageSoc,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2) Maximum Voltage allowable of VDD_SOC"))
	),

	(bios->LoadLineResistanceGfx, LoadLineResistanceGfx,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mOhms with 8 fractional bits"))
	),
	(bios->LoadLineResistanceSoc, LoadLineResistanceSoc,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mOhms with 8 fractional bits"))
	),

	// struct dpm_descriptor_smu11 DpmDescriptor[SMU11_PPT3_PPCLK_COUNT];

	(NULL, FreqTableGfx,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableGfx [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableGfx, NUM_GFXCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, "In MHz"))
	),
	(NULL, FreqTableVclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableVclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableVclk, NUM_VCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, "In MHz"))
	),
	(NULL, FreqTableDclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableDclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableDclk, NUM_DCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, "In MHz"))
	),
	(NULL, FreqTableEclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableEclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableEclk, NUM_ECLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, "In MHz"))
	),
	(NULL, FreqTableSocclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableSocclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableSocclk, NUM_SOCCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, "In MHz"))
	),
	(NULL, FreqTableUclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableUclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableUclk, NUM_UCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, "In MHz"))
	),
	(NULL, FreqTableFclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableFclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableFclk, NUM_FCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, "In MHz"))
	),
	(NULL, FreqTableDcefclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableDcefclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			// start, count
			bios->FreqTableDcefclk, NUM_DCEFCLK_DPM_LEVELS_SMU11,
			ATUI_NULL // enum
		)), ((LANG_ENG, "In MHz"))
	),
	(NULL, FreqTableDispclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableDispclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			// start, count
			bios->FreqTableDispclk, NUM_DISPCLK_DPM_LEVELS_SMU11,
			ATUI_NULL // enum
		)), ((LANG_ENG, "In MHz"))
	),
	(NULL, FreqTablePixclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTablePixclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTablePixclk, NUM_PIXCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, "In MHz"))
	),
	(NULL, FreqTablePhyclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTablePhyclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTablePhyclk, NUM_PHYCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, "In MHz"))
	),

    (NULL, DcModeMaxFreq,
        (ATUI_NAN, ATUI_DYNARRAY, (
            (ATUI_NULL, FreqTablePhyclk[%s],
                (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
            ),
            bios->DcModeMaxFreq, SMU11_PPT3_PPCLK_COUNT, // start, count
            SMU11_PPT3_PPCLK // enum
        )), ((LANG_ENG, "In MHz"))
    ),

	(bios->Padding8_Clks, Padding8_Clks,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(NULL, Mp0clkFreq,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, Mp0clkFreq [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->Mp0clkFreq, NUM_MP0CLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, "In MHz"))
	),
	(NULL, Mp0DpmVoltage,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, Mp0DpmVoltage [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->Mp0DpmVoltage, NUM_MP0CLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, "mV(Q2)"))
	),

	(bios->GfxclkFidle, GfxclkFidle,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In MHz"))
	),
	(bios->GfxclkSlewRate, GfxclkSlewRate,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "for PLL babystepping???"))
	),
	(bios->CksEnableFreq, CksEnableFreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding789, Padding789,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->CksVoltageOffset, CksVoltageOffset,
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->Padding567, Padding567,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->GfxclkDsMaxFreq, GfxclkDsMaxFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Mhz"))
	),
	(bios->GfxclkSource, GfxclkSource,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0 = PLL, 1 = DFLL"))
	),
	(bios->Padding456, Padding456,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->LowestUclkReservedForUlv, LowestUclkReservedForUlv,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Set this to 1 if UCLK DPM0 is reserved for ULV-mode only"))
	),
	(bios->Padding8_Uclk, Padding8_Uclk,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(NULL, PcieGenSpeed,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, PcieGenSpeed [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->PcieGenSpeed, NUM_LINK_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, "< 0:PciE-gen1 1:PciE-gen2 2: PciE-gen3 3:PciE-gen4"))
	),
	(NULL, PcieLaneCount,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, PcieLaneCount [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->PcieLaneCount, NUM_LINK_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG, "< 1=x1, 2=x2, 3=x4, 4=x8, 5=x12, 6=x16"))
	),
	(NULL, LclkFreq,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, LclkFreq [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->LclkFreq, NUM_LINK_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->EnableTdpm, EnableTdpm,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TdpmHighHystTemperature, TdpmHighHystTemperature,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TdpmLowHystTemperature, TdpmLowHystTemperature,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxclkFreqHighTempLimit, GfxclkFreqHighTempLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "High limit on GFXCLK when temperature is high, for reliability."))
	),

	(bios->FanStopTemp, FanStopTemp,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->FanStartTemp, FanStartTemp,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),

	(bios->FanGainEdge, FanGainEdge,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainHotspot, FanGainHotspot,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainLiquid, FanGainLiquid,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainVrGfx, FanGainVrGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainVrSoc, FanGainVrSoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainPlx, FanGainPlx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainHbm, FanGainHbm,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanPwmMin, FanPwmMin,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanAcousticLimitRpm, FanAcousticLimitRpm,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanThrottlingRpm, FanThrottlingRpm,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanMaximumRpm, FanMaximumRpm,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetTemperature, FanTargetTemperature,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetGfxclk, FanTargetGfxclk,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanZeroRpmEnable, FanZeroRpmEnable,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTachEdgePerRev, FanTachEdgePerRev,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FuzzyFan_ErrorSetDelta, FuzzyFan_ErrorSetDelta,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_ErrorRateSetDelta, FuzzyFan_ErrorRateSetDelta,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_PwmSetDelta, FuzzyFan_PwmSetDelta,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_Reserved, FuzzyFan_Reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->OverrideAvfsGb[AVFS_VOLTAGE_GFX], OverrideAvfsGb (GFX),
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->OverrideAvfsGb[AVFS_VOLTAGE_SOC], OverrideAvfsGb (SOC),
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Padding8_Avfs, Padding8_Avfs,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->qAvfsGb[AVFS_VOLTAGE_GFX], qAvfsGb (GFX),
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		((LANG_ENG, "GHz->V Override of fused curve"))
	),
	(bios->qAvfsGb[AVFS_VOLTAGE_SOC], qAvfsGb (SOC),
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		((LANG_ENG, "GHz->V Override of fused curve"))
	),

	(bios->dBtcGbGfxCksOn, dBtcGbGfxCksOn,
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		(ATUI_NODESCR)
	),
	(bios->dBtcGbGfxCksOff, dBtcGbGfxCksOff,
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		(ATUI_NODESCR)
	),
	(bios->dBtcGbGfxAfll, dBtcGbGfxAfll,
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		((LANG_ENG, "dfll?"))
	),
	(bios->dBtcGbSoc, dBtcGbSoc,
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		(ATUI_NODESCR)
	),
	(bios->qAgingGb[AVFS_VOLTAGE_GFX], qAgingGb (GFX),
		(ATUI_NAN, ATUI_INLINE, linear_f32),
		((LANG_ENG, "GHz->V"))
	),
	(bios->qAgingGb[AVFS_VOLTAGE_SOC], qAgingGb (SOC),
		(ATUI_NAN, ATUI_INLINE, linear_f32),
		((LANG_ENG, "GHz->V"))
	),

	(bios->qStaticVoltageOffset[AVFS_VOLTAGE_GFX], qStaticVoltageOffset (GFX),
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		((LANG_ENG, "GHz->V"))
	),
	(bios->qStaticVoltageOffset[AVFS_VOLTAGE_SOC], qStaticVoltageOffset (SOC),
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		((LANG_ENG, "GHz->V"))
	),


	(bios->DcTol[AVFS_VOLTAGE_GFX], DcTol (GFX),
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mV(Q2)"))
	),
	(bios->DcTol[AVFS_VOLTAGE_SOC], DcTol (SOC),
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mV(Q2)"))
	),


	(bios->DcBtcEnabled[AVFS_VOLTAGE_GFX], DcBtcEnabled (GFX),
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DcBtcEnabled[AVFS_VOLTAGE_SOC], DcBtcEnabled (SOC),
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Padding8_GfxBtc, Padding8_GfxBtc,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->DcBtcMin[AVFS_VOLTAGE_GFX], DcBtcMin (GFX),
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "mV(Q2)"))
	),
	(bios->DcBtcMin[AVFS_VOLTAGE_SOC], DcBtcMin (SOC),
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "mV(Q2)"))
	),
	(bios->DcBtcMax[AVFS_VOLTAGE_GFX], DcBtcMax (GFX),
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "mV(Q2)"))
	),
	(bios->DcBtcMax[AVFS_VOLTAGE_SOC], DcBtcMax (SOC),
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "mV(Q2)"))
	),


	(NULL, XgmiLinkSpeed,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, XgmiLinkSpeed [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->XgmiLinkSpeed, NUM_XGMI_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(NULL, XgmiLinkWidth,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, XgmiLinkWidth [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->XgmiLinkWidth, NUM_XGMI_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(NULL, XgmiFclkFreq,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, XgmiFclkFreq [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->XgmiFclkFreq, NUM_XGMI_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(NULL, XgmiUclkFreq,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, XgmiUclkFreq [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->XgmiUclkFreq, NUM_XGMI_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(NULL, XgmiSocclkFreq,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, XgmiSocclkFreq [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->XgmiSocclkFreq, NUM_XGMI_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(NULL, XgmiSocVoltage,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, XgmiSocVoltage [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->XgmiSocVoltage, NUM_XGMI_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->DebugOverrides, DebugOverrides,
		(ATUI_NODISPLAY, ATUI_INLINE, dpm_debug_override_smu11_19),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation0, ReservedEquation0,
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation1, ReservedEquation1,
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation2, ReservedEquation2,
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation3, ReservedEquation3,
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),

	(bios->MinVoltageUlvGfx, MinVoltageUlvGfx,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2)  Minimum Voltage (\"Vmin\") of VDD_GFX in ULV mode"))
	),
	(bios->MinVoltageUlvSoc, MinVoltageUlvSoc,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2)  Minimum Voltage (\"Vmin\") of VDD_SOC in ULV mode"))
	),



	(bios->MGpuFanBoostLimitRpm, MGpuFanBoostLimitRpm,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding16_Fan, padding16_Fan,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FanGainVrMem0, FanGainVrMem0,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainVrMem1, FanGainVrMem1,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->DcBtcGb[AVFS_VOLTAGE_GFX], DcBtcGb (GFX),
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DcBtcGb[AVFS_VOLTAGE_SOC], DcBtcGb (SOC),
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Reserved, Reserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->Padding32, Padding32,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->MaxVoltageStepGfx, MaxVoltageStepGfx,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "n mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value."))
	),
	(bios->MaxVoltageStepSoc, MaxVoltageStepSoc,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value."))
	),

	(bios->VddGfxVrMapping, VddGfxVrMapping,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->VddSocVrMapping, VddSocVrMapping,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->VddMem0VrMapping, VddMem0VrMapping,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->VddMem1VrMapping, VddMem1VrMapping,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->GfxUlvPhaseSheddingMask, GfxUlvPhaseSheddingMask,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->SocUlvPhaseSheddingMask, SocUlvPhaseSheddingMask,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->ExternalSensorPresent, ExternalSensorPresent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "External RDI connected to TMON (aka TEMP IN)"))
	),
	(bios->Padding8_V, Padding8_V,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->GfxMaxCurrent, GfxMaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->GfxOffset, GfxOffset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Padding_TelemetryGfx, Padding_TelemetryGfx,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->SocMaxCurrent, SocMaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->SocOffset, SocOffset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Padding_TelemetrySoc, Padding_TelemetrySoc,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem0MaxCurrent, Mem0MaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Mem0Offset, Mem0Offset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Padding_TelemetryMem0, Padding_TelemetryMem0,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem1MaxCurrent, Mem1MaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Mem1Offset, Mem1Offset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Padding_TelemetryMem1, Padding_TelemetryMem1,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->AcDcGpio, AcDcGpio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for AC/DC switching"))
	),
	(bios->AcDcPolarity, AcDcPolarity,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO polarity for AC/DC switching"))
	),
	(bios->VR0HotGpio, VR0HotGpio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for VR0 HOT event"))
	),
	(bios->VR0HotPolarity, VR0HotPolarity,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO polarity for VR0 HOT event"))
	),

	(bios->VR1HotGpio, VR1HotGpio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for VR1 HOT event"))
	),
	(bios->VR1HotPolarity, VR1HotPolarity,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO polarity for VR1 HOT event"))
	),
	(bios->Padding1, Padding1,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for GTHR Event"))
	),
	(bios->Padding2, Padding2,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "replace GPIO polarity for GTHR"))
	),


	(bios->LedPin0, LedPin0,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO number for LedPin[0]"))
	),
	(bios->LedPin1, LedPin1,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO number for LedPin[1]"))
	),
	(bios->LedPin2, LedPin2,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO number for LedPin[2]"))
	),
	(bios->padding8_4, padding8_4,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->PllGfxclkSpreadEnabled, PllGfxclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "on or off"))
	),
	(bios->PllGfxclkSpreadPercent, PllGfxclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(bios->PllGfxclkSpreadFreq, PllGfxclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),

	(bios->UclkSpreadEnabled, UclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "on or off"))
	),
	(bios->UclkSpreadPercent, UclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(bios->UclkSpreadFreq, UclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),

	(bios->FclkSpreadEnabled, FclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "on or off"))
	),
	(bios->FclkSpreadPercent, FclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(bios->FclkSpreadFreq, FclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),

	(bios->FllGfxclkSpreadEnabled, FllGfxclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "on or off"))
	),
	(bios->FllGfxclkSpreadPercent, FllGfxclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(bios->FllGfxclkSpreadFreq, FllGfxclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),

//struct i2ccontrollerconfig_u32 I2cControllers[I2C_CONTROLLER_NAME_COUNT_SMU11];

	(bios->BoardReserved, BoardReserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->MmHubPadding, MmHubPadding,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)





/*
import re

names = ('SMU_11_0_ODSETTING_GFXCLKFMAX', 'SMU_11_0_ODSETTING_GFXCLKFMIN', 'SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P1', 'SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P1', 'SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P2', 'SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P2', 'SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P3', 'SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P3', 'SMU_11_0_ODSETTING_UCLKFMAX', 'SMU_11_0_ODSETTING_POWERPERCENTAGE', 'SMU_11_0_ODSETTING_FANRPMMIN', 'SMU_11_0_ODSETTING_FANRPMACOUSTICLIMIT', 'SMU_11_0_ODSETTING_FANTARGETTEMPERATURE', 'SMU_11_0_ODSETTING_OPERATINGTEMPMAX', 'SMU_11_0_ODSETTING_ACTIMING', 'SMU_11_0_ODSETTING_FAN_ZERO_RPM_CONTROL', 'SMU_11_0_ODSETTING_AUTOUVENGINE', 'SMU_11_0_ODSETTING_AUTOOCENGINE', 'SMU_11_0_ODSETTING_AUTOOCMEMORY')

pat = '    (bios->%s[%s], %s,\n        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)\n    ),'

for n in names:
	s = re.sub("(SMU_11_0_ODSETTING_)", "", n)
	s = re.sub("_", " ", s.lower())
	print(pat % ("max", n, ("%s (max)" % s)))
	print(pat % ("min", n, ("%s (min)" % s)))

for n in names:
	s = re.sub("(SMU_11_0_PPCLOCK_)", "", n)
	s = re.sub("_", " ", s)
	print(pat % ("max", n, ("%s (max)" % s)))
	print(pat % ("min", n, ("%s (min)" % s)))
*/

PPATUI_FUNCIFY(struct, smu_11_0_overdrive_table, atomtree_powerplaytable,
	(bios->revision, revision,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Revision = SMU_11_0_PP_OVERDRIVE_VERSION"))
	),
	(bios->reserve, reserve,
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "Zero filled field reserved for future use"))
	),
	(bios->feature_count, feature_count,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Total number of supported features"))
	),
	(bios->setting_count, setting_count,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Total number of supported settings"))
	),

	(NULL, supported OD feature support flags,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, %s,
				(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
			),
			bios->cap, SMU_11_0_ODCAP_COUNT, // start, count
			 SMU_11_0_ODFEATURE_CAP // enum
		)), (ATUI_NODESCR)
	),
	(NULL, undefined OD feature support flags,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, OD feature [14 + %02u],
					// if CAP_COUNT changes, please change this 14
				(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
			),
			(&(bios->cap[SMU_11_0_ODCAP_COUNT])), // start
			(SMU_11_0_MAX_ODFEATURE - SMU_11_0_ODCAP_COUNT), // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(NULL, supported Overdrive settings (max),
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, max: %s,
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->max, SMU_11_0_ODSETTING_COUNT, // start, count
			SMU_11_0_ODSETTING_ID // enum
		)), (ATUI_NODESCR)
	),
	(NULL, supported Overdrive settings (min),
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, min: %s,
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->min, SMU_11_0_ODSETTING_COUNT, // start, count
			SMU_11_0_ODSETTING_ID // enum
		)), (ATUI_NODESCR)
	),


	(NULL, undefined OD settings (max),
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, max: [19 + %02u],
					// if ODSETTING_COUNT changes, please change this 19
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			(&(bios->max[SMU_11_0_ODSETTING_COUNT])), // start
			(SMU_11_0_MAX_ODSETTING - SMU_11_0_ODSETTING_COUNT), // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(NULL, undefined OD settings (min),
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, min: [19 + %02u],
					// if ODSETTING_COUNT changes, please change this 19
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			(&(bios->min[SMU_11_0_ODSETTING_COUNT])), // start
			(SMU_11_0_MAX_ODSETTING - SMU_11_0_ODSETTING_COUNT), // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, smu_11_0_power_saving_clock_table,
		atomtree_powerplaytable,
	(bios->revision, revision,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Revision = SMU_11_0_PP_POWERSAVINGCLOCK_VERSION"))
	),
	(bios->reserve, reserve,
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "Zero filled field reserved for future use"))
	),
	(bios->count, count,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "power_saving_clock_count = SMU_11_0_PPCLOCK_COUNT"))
	),

	(NULL, PowerSavingClock modes (max),
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, max: %s,
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->max, SMU_11_0_PPCLOCK_COUNT, // start, count
			SMU_11_0_PPCLOCK_ID // enum
		)), (ATUI_NODESCR)
	),
	(NULL, PowerSavingClock modes (min),
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, min: %s,
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->min, SMU_11_0_PPCLOCK_COUNT, // start, count
			SMU_11_0_PPCLOCK_ID // enum
		)), (ATUI_NODESCR)
	),

	(NULL, undefined PowerSavingClock Modes (max),
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, max: [10 + %02u],
					// if PPCLOCK_COUNT changes, please change this 10
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			(&(bios->max[SMU_11_0_PPCLOCK_COUNT])), // start
			(SMU_11_0_MAX_PPCLOCK - SMU_11_0_PPCLOCK_COUNT), // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(NULL, undefined PowerSavingClock Modes (min),
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, min: [10 + %02u],
					// if PPCLOCK_COUNT changes, please change this 10
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			(&(bios->min[SMU_11_0_PPCLOCK_COUNT])), // start
			(SMU_11_0_MAX_PPCLOCK - SMU_11_0_PPCLOCK_COUNT), // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	)
)





PPATUI_FUNCIFY(struct, smu11_smcpptable_v8, atomtree_powerplaytable, // Navi10
	(bios->Version, Version,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(NULL, SocketPowerLimitAc,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, PPT %u,
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->SocketPowerLimitAc, PPT_THROTTLER_COUNT, // start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(NULL, SocketPowerLimitAcTau,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, PPT %u,
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->SocketPowerLimitAcTau, PPT_THROTTLER_COUNT, // start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(NULL, SocketPowerLimitDc,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, PPT %u,
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->SocketPowerLimitDc, PPT_THROTTLER_COUNT, // start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),
	(NULL, SocketPowerLimitDcTau,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, PPT %u,
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->SocketPowerLimitDcTau, PPT_THROTTLER_COUNT, // start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->TdcLimitSoc, TdcLimitSoc,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Amps"))
	),
	(bios->TdcLimitSocTau, TdcLimitSocTau,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Time constant of LPF in ms"))
	),
	(bios->TdcLimitGfx, TdcLimitGfx,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Amps"))
	),
	(bios->TdcLimitGfxTau, TdcLimitGfxTau,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Time constant of LPF in ms"))
	),

	(bios->TedgeLimit, TedgeLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->ThotspotLimit, ThotspotLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->TmemLimit, TmemLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->Tvr_gfxLimit, Tvr_gfxLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->Tvr_mem0Limit, Tvr_mem0Limit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->Tvr_mem1Limit, Tvr_mem1Limit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->Tvr_socLimit, Tvr_socLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->Tliquid0Limit, Tliquid0Limit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->Tliquid1Limit, Tliquid1Limit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->TplxLimit, TplxLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->FitLimit, FitLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Failures in time (failures per million parts over the defined lifetime)"))
	),

	(bios->PpmPowerLimit, PpmPowerLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Switch this this power limit when temperature is above PpmTempThreshold"))
	),
	(bios->PpmTemperatureThreshold, PpmTemperatureThreshold,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->ThrottlerControlMask, ThrottlerControlMask,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "See Throtter masks defines"))
	),

	(bios->FwDStateMask, FwDStateMask,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "See FW DState masks defines"))
	),

	(bios->UlvVoltageOffsetSoc, UlvVoltageOffsetSoc,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2)"))
	),
	(bios->UlvVoltageOffsetGfx, UlvVoltageOffsetGfx,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2)"))
	),

	(bios->GceaLinkMgrIdleThreshold, GceaLinkMgrIdleThreshold,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Set by SMU FW during enablment of SOC_ULV. Controls delay for GFX SDP port disconnection during idle events"))
	),
	(bios->paddingRlcUlvParams, paddingRlcUlvParams,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->UlvSmnclkDid, UlvSmnclkDid,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "DID for ULV mode. 0 means CLK will not be modified in ULV."))
	),
	(bios->UlvMp1clkDid, UlvMp1clkDid,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "DID for ULV mode. 0 means CLK will not be modified in ULV."))
	),
	(bios->UlvGfxclkBypass, UlvGfxclkBypass,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "1 to turn off/bypass Gfxclk during ULV, 0 to leave Gfxclk on during ULV"))
	),
	(bios->Padding234, Padding234,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->MinVoltageUlvGfx, MinVoltageUlvGfx,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2)  Minimum Voltage (\"Vmin\") of VDD_GFX in ULV mode"))
	),
	(bios->MinVoltageUlvSoc, MinVoltageUlvSoc,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2)  Minimum Voltage (\"Vmin\") of VDD_SOC in ULV mode"))
	),


	(bios->MinVoltageGfx, MinVoltageGfx,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2) Minimum Voltage (\"Vmin\") of VDD_GFX"))
	),
	(bios->MinVoltageSoc, MinVoltageSoc,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2) Minimum Voltage (\"Vmin\") of VDD_SOC"))
	),
	(bios->MaxVoltageGfx, MaxVoltageGfx,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2) Maximum Voltage allowable of VDD_GFX"))
	),
	(bios->MaxVoltageSoc, MaxVoltageSoc,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2) Maximum Voltage allowable of VDD_SOC"))
	),

	(bios->LoadLineResistanceGfx, LoadLineResistanceGfx,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mOhms with 8 fractional bits"))
	),
	(bios->LoadLineResistanceSoc, LoadLineResistanceSoc,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mOhms with 8 fractional bits"))
	),

	//struct dpm_descriptor_smu11 DpmDescriptor[SMU11_PPT8_PPCLK_COUNT];

	(NULL, FreqTableGfx,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableGfx [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableGfx, NUM_GFXCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,"In MHz"))
	),
	(NULL, FreqTableVclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableVclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableVclk, NUM_VCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,"In MHz"))
	),
	(NULL, FreqTableDclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableDclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableDclk, NUM_DCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,"In MHz"))
	),
	(NULL, FreqTableSocclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableSocclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableSocclk, NUM_SOCCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,"In MHz"))
	),
	(NULL, FreqTableUclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableUclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableUclk, NUM_UCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,"In MHz"))
	),
	(NULL, FreqTableDcefclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableDcefclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			// start, count
			bios->FreqTableDcefclk, NUM_DCEFCLK_DPM_LEVELS_SMU11,
			ATUI_NULL // enum
		)), ((LANG_ENG,"In MHz"))
	),
	(NULL, FreqTableDispclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableDispclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			// start, count
			bios->FreqTableDispclk, NUM_DISPCLK_DPM_LEVELS_SMU11,
			ATUI_NULL // enum
		)), ((LANG_ENG,"In MHz"))
	),
	(NULL, FreqTablePixclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTablePixclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTablePixclk, NUM_PIXCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,"In MHz"))
	),
	(NULL, FreqTablePhyclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTablePhyclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTablePhyclk, NUM_PHYCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,"In MHz"))
	),
	(bios->Paddingclks, Paddingclks,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(NULL, DcModeMaxFreq,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, DcModeMaxFreq [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->DcModeMaxFreq, SMU11_PPT8_PPCLK_COUNT, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,"In MHz"))
	),

	(bios->Padding8_Clks, Padding8_Clks,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(NULL, FreqTableUclkDiv,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableUclkDiv [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableUclkDiv, NUM_UCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,"0:Div-1, 1:Div-1/2, 2:Div-1/4, 3:Div-1/8"))
	),

	(NULL, Mp0clkFreq,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, Mp0clkFreq [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->Mp0clkFreq, NUM_MP0CLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,"in MHz"))
	),
	(NULL, Mp0DpmVoltage,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, Mp0DpmVoltage [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->Mp0DpmVoltage, NUM_MP0CLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,"mV(Q2)"))
	),
	(NULL, MemVddciVoltage,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, MemVddciVoltage [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->MemVddciVoltage, NUM_UCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,"mV(Q2)"))
	),
	(NULL, MemMvddVoltage,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, MemMvddVoltage [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->MemMvddVoltage, NUM_UCLK_DPM_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,"mV(Q2)"))
	),
	(bios->GfxclkFgfxoffEntry, GfxclkFgfxoffEntry,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Mhz"))
	),
	(bios->GfxclkFinit, GfxclkFinit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Mhz"))
	),
	(bios->GfxclkFidle, GfxclkFidle,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in MHz"))
	),
	(bios->GfxclkSlewRate, GfxclkSlewRate,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "for PLL babystepping???"))
	),
	(bios->GfxclkFopt, GfxclkFopt,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Mhz"))
	),
	(bios->Padding567, Padding567,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->GfxclkDsMaxFreq, GfxclkDsMaxFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in MHz"))
	),
	(bios->GfxclkSource, GfxclkSource,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0 = PLL, 1 = DFLL"))
	),
	(bios->Padding456, Padding456,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->LowestUclkReservedForUlv, LowestUclkReservedForUlv,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Set this to 1 if UCLK DPM0 is reserved for ULV-mode only"))
	),
	(bios->paddingUclk, paddingUclk,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->MemoryType, MemoryType,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0-GDDR6, 1-HBM"))
	),
	(bios->MemoryChannels, MemoryChannels,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PaddingMem, PaddingMem,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(NULL, PcieGenSpeed,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, PcieGenSpeed [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->PcieGenSpeed, NUM_LINK_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,"< 0:PciE-gen1 1:PciE-gen2 2:PciE-gen3 3:PciE-gen4"))
	),
	(NULL, PcieLaneCount,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, PcieLaneCount [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->PcieLaneCount, NUM_LINK_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), ((LANG_ENG,"< 1=x1, 2=x2, 3=x4, 4=x8, 5=x12, 6=x16"))
	),
	(NULL, LclkFreq,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, LclkFreq [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->LclkFreq, NUM_LINK_LEVELS_SMU11, // start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->EnableTdpm, EnableTdpm,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TdpmHighHystTemperature, TdpmHighHystTemperature,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TdpmLowHystTemperature, TdpmLowHystTemperature,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxclkFreqHighTempLimit, GfxclkFreqHighTempLimit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "High limit on GFXCLK when temperature is high, for reliability."))
	),

	(bios->FanStopTemp, FanStopTemp,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->FanStartTemp, FanStartTemp,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),

	(bios->FanGainEdge, FanGainEdge,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainHotspot, FanGainHotspot,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainLiquid0, FanGainLiquid0,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainLiquid1, FanGainLiquid1,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainVrGfx, FanGainVrGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainVrSoc, FanGainVrSoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainVrMem0, FanGainVrMem0,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainVrMem1, FanGainVrMem1,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainPlx, FanGainPlx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainMem, FanGainMem,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanPwmMin, FanPwmMin,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanAcousticLimitRpm, FanAcousticLimitRpm,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanThrottlingRpm, FanThrottlingRpm,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanMaximumRpm, FanMaximumRpm,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetTemperature, FanTargetTemperature,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTargetGfxclk, FanTargetGfxclk,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTempInputSelect, FanTempInputSelect,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanPadding, FanPadding,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanZeroRpmEnable, FanZeroRpmEnable,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanTachEdgePerRev, FanTachEdgePerRev,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FuzzyFan_ErrorSetDelta, FuzzyFan_ErrorSetDelta,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_ErrorRateSetDelta, FuzzyFan_ErrorRateSetDelta,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_PwmSetDelta, FuzzyFan_PwmSetDelta,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FuzzyFan_Reserved, FuzzyFan_Reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->OverrideAvfsGb[AVFS_VOLTAGE_GFX], OverrideAvfsGb (GFX),
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->OverrideAvfsGb[AVFS_VOLTAGE_SOC], OverrideAvfsGb (SOC),
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->Padding8_Avfs, Padding8_Avfs,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->qAvfsGb[AVFS_VOLTAGE_GFX], qAvfsGb (GFX),
		(ATUI_NAN, ATUI_INLINE, quadratic_f32), 
		((LANG_ENG, "GHz->V Override of fused curve"))
	),
	(bios->qAvfsGb[AVFS_VOLTAGE_SOC], qAvfsGb (SOC),
		(ATUI_NAN, ATUI_INLINE, quadratic_f32), 
		((LANG_ENG, "GHz->V Override of fused curve"))
	),

	(bios->dBtcGbGfxPll, dBtcGbGfxPll,
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		((LANG_ENG, "GHz->V BtcGb"))
	),
	(bios->dBtcGbGfxDfll, dBtcGbGfxDfll,
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		((LANG_ENG, "GHz->V BtcGb"))
	),
	(bios->dBtcGbSoc, dBtcGbSoc,
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		((LANG_ENG, "GHz->V BtcGb"))
	),
	(bios->qAgingGb[AVFS_VOLTAGE_GFX], qAgingGb (GFX),
		(ATUI_NAN, ATUI_INLINE, linear_f32), 
		((LANG_ENG, "GHz->V"))
	),
	(bios->qAgingGb[AVFS_VOLTAGE_SOC], qAgingGb (SOC),
		(ATUI_NAN, ATUI_INLINE, linear_f32), 
		((LANG_ENG, "GHz->V"))
	),

	(bios->qStaticVoltageOffset[AVFS_VOLTAGE_GFX], qStaticVoltageOffset (GFX),
		(ATUI_NAN, ATUI_INLINE, quadratic_f32), 
		((LANG_ENG, "GHz->V"))
	),
	(bios->qStaticVoltageOffset[AVFS_VOLTAGE_SOC], qStaticVoltageOffset (SOC),
		(ATUI_NAN, ATUI_INLINE, quadratic_f32), 
		((LANG_ENG, "GHz->V"))
	),

	(bios->DcTol[AVFS_VOLTAGE_GFX], DcTol (GFX),
		(ATUI_HEX, ATUI_NOFANCY), 
		((LANG_ENG, "mV(Q2)"))
	),
	(bios->DcTol[AVFS_VOLTAGE_SOC], DcTol (SOC),
		(ATUI_HEX, ATUI_NOFANCY), 
		((LANG_ENG, "mV(Q2)"))
	),

	(bios->DcBtcEnabled[AVFS_VOLTAGE_GFX], DcBtcEnabled (GFX),
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DcBtcEnabled[AVFS_VOLTAGE_SOC], DcBtcEnabled (SOC),
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Padding8_GfxBtc, Padding8_GfxBtc,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->DcBtcMin[AVFS_VOLTAGE_GFX], DcBtcMin (GFX),
		(ATUI_HEX, ATUI_NOFANCY), 
		((LANG_ENG, "mV(Q2)"))
	),
	(bios->DcBtcMin[AVFS_VOLTAGE_SOC], DcBtcMin (SOC),
		(ATUI_HEX, ATUI_NOFANCY), 
		((LANG_ENG, "mV(Q2)"))
	),
	(bios->DcBtcMax[AVFS_VOLTAGE_GFX], DcBtcMax (GFX),
		(ATUI_HEX, ATUI_NOFANCY), 
		((LANG_ENG, "mV(Q2)"))
	),
	(bios->DcBtcMax[AVFS_VOLTAGE_SOC], DcBtcMax (SOC),
		(ATUI_HEX, ATUI_NOFANCY), 
		((LANG_ENG, "mV(Q2)"))
	),

	(bios->DebugOverrides, DebugOverrides,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ReservedEquation0, ReservedEquation0,
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation1, ReservedEquation1,
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation2, ReservedEquation2,
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->ReservedEquation3, ReservedEquation3,
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),

	(bios->TotalPowerConfig, TotalPowerConfig,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0-TDP, 1-TGP, 2-TCP Estimated, 3-TCP Measured"))
	),
	(bios->TotalPowerSpare1, TotalPowerSpare1,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TotalPowerSpare2, TotalPowerSpare2,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->PccThresholdLow, PccThresholdLow,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PccThresholdHigh, PccThresholdHigh,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MGpuFanBoostLimitRpm, MGpuFanBoostLimitRpm,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PaddingAPCC, PaddingAPCC,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->VDDGFX_TVmin, VDDGFX_TVmin,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->VDDSOC_TVmin, VDDSOC_TVmin,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->VDDGFX_Vmin_HiTemp, VDDGFX_Vmin_HiTemp,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mV Q2"))
	),
	(bios->VDDGFX_Vmin_LoTemp, VDDGFX_Vmin_LoTemp,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mV Q2"))
	),
	(bios->VDDSOC_Vmin_HiTemp, VDDSOC_Vmin_HiTemp,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mV Q2"))
	),
	(bios->VDDSOC_Vmin_LoTemp, VDDSOC_Vmin_LoTemp,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mV Q2"))
	),

	(bios->VDDGFX_TVminHystersis, VDDGFX_TVminHystersis,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),
	(bios->VDDSOC_TVminHystersis, VDDSOC_TVminHystersis,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Celcius"))
	),

	(bios->BtcConfig, BtcConfig,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->SsFmin, SsFmin,
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "PPtable value to function similar to VFTFmin for SS Curve; Size is SMU11_PPT8_PPCLK_COUNT rounded to nearest multiple of 2"))
	),
	(bios->DcBtcGb[AVFS_VOLTAGE_GFX], DcBtcGb (GFX),
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DcBtcGb[AVFS_VOLTAGE_SOC], DcBtcGb (SOC),
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->Reserved, Reserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	//struct i2ccontrollerconfig_u8_mixed I2cControllers[I2C_CONTROLLER_NAME_COUNT_SMU11_PPT8];

	(bios->MaxVoltageStepGfx, MaxVoltageStepGfx,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value."))
	),
	(bios->MaxVoltageStepSoc, MaxVoltageStepSoc,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value."))
	),

	(bios->VddGfxVrMapping, VddGfxVrMapping,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Use VR_MAPPING* bitfields"))
	),
	(bios->VddSocVrMapping, VddSocVrMapping,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Use VR_MAPPING* bitfields"))
	),
	(bios->VddMem0VrMapping, VddMem0VrMapping,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Use VR_MAPPING* bitfields"))
	),
	(bios->VddMem1VrMapping, VddMem1VrMapping,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Use VR_MAPPING* bitfields"))
	),

	(bios->GfxUlvPhaseSheddingMask, GfxUlvPhaseSheddingMask,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->SocUlvPhaseSheddingMask, SocUlvPhaseSheddingMask,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->ExternalSensorPresent, ExternalSensorPresent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "External RDI connected to TMON (aka TEMP IN)"))
	),
	(bios->Padding8_V, Padding8_V,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->GfxMaxCurrent, GfxMaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->GfxOffset, GfxOffset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Padding_TelemetryGfx, Padding_TelemetryGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->SocMaxCurrent, SocMaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->SocOffset, SocOffset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Padding_TelemetrySoc, Padding_TelemetrySoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem0MaxCurrent, Mem0MaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Mem0Offset, Mem0Offset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Padding_TelemetryMem0, Padding_TelemetryMem0,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem1MaxCurrent, Mem1MaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Mem1Offset, Mem1Offset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Padding_TelemetryMem1, Padding_TelemetryMem1,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->AcDcGpio, AcDcGpio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for AC/DC switching"))
	),
	(bios->AcDcPolarity, AcDcPolarity,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO polarity for AC/DC switching"))
	),
	(bios->VR0HotGpio, VR0HotGpio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for VR0 HOT event"))
	),
	(bios->VR0HotPolarity, VR0HotPolarity,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO polarity for VR0 HOT event"))
	),

	(bios->VR1HotGpio, VR1HotGpio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for VR1 HOT event"))
	),
	(bios->VR1HotPolarity, VR1HotPolarity,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO polarity for VR1 HOT event"))
	),
	(bios->GthrGpio, GthrGpio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for GTHR Event"))
	),
	(bios->GthrPolarity, GthrPolarity,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "replace GPIO polarity for GTHR"))
	),

	(bios->LedPin0, LedPin0,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO number for LedPin[0]"))
	),
	(bios->LedPin1, LedPin1,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO number for LedPin[1]"))
	),
	(bios->LedPin2, LedPin2,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO number for LedPin[2]"))
	),
	(bios->padding8_4, padding8_4,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->PllGfxclkSpreadEnabled, PllGfxclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "on or off"))
	),
	(bios->PllGfxclkSpreadPercent, PllGfxclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(bios->PllGfxclkSpreadFreq, PllGfxclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),

	(bios->DfllGfxclkSpreadEnabled, DfllGfxclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "on or off"))
	),
	(bios->DfllGfxclkSpreadPercent, DfllGfxclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(bios->DfllGfxclkSpreadFreq, DfllGfxclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),

	(bios->UclkSpreadEnabled, UclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "on or off"))
	),
	(bios->UclkSpreadPercent, UclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(bios->UclkSpreadFreq, UclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),

	(bios->SoclkSpreadEnabled, SoclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "on or off"))
	),
	(bios->SocclkSpreadPercent, SocclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(bios->SocclkSpreadFreq, SocclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),

	(bios->TotalBoardPower, TotalBoardPower,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Only needed for TCP Estimated case, where TCP = TGP+Total Board Power"))
	),
	(bios->BoardPadding, BoardPadding,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->MvddRatio, MvddRatio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "This is used for MVDD Vid workaround. It has 16 fractional bits (Q16.16)"))
	),

	(bios->RenesesLoadLineEnabled, RenesesLoadLineEnabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxLoadlineResistance, GfxLoadlineResistance,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocLoadlineResistance, SocLoadlineResistance,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding8_Loadline, Padding8_Loadline,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->BoardReserved, BoardReserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->MmHubPadding, MmHubPadding,
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "SMU internal use"))
	)
)










PPATUI_FUNCIFY(struct, smu_11_0_powerplay_table, atomtree_powerplaytable,
	(bios->header, header,
		(ATUI_NAN, ATUI_INLINE, smu_powerplay_table_header),
		(ATUI_NODESCR)
	),
	(bios->golden_pp_id, golden_pp_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->golden_revision, golden_revision,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->format_id, format_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->platform_caps.platform_caps, platform_caps,
		(ATUI_NODISPLAY, ATUI_INLINE, powerplay_platform_caps),
		(ATUI_NODESCR)
	),
	(bios->thermal_controller_type, thermal_controller_type,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "one of SMU_11_0_PP_THERMALCONTROLLER"))
	),
	(bios->small_power_limit1, small_power_limit1,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->small_power_limit2, small_power_limit2,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->boost_power_limit, boost_power_limit,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->od_turbo_power_limit, od_turbo_power_limit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Power limit setting for Turbo mode in Performance UI Tuning."))
	),
	(bios->od_power_save_power_limit, od_power_save_power_limit,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Power limit setting for PowerSave/Optimal mode in Performance UI Tuning."))
	),
	(bios->software_shutdown_temp, software_shutdown_temp,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->reserve, reserve,
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "Zero filled field reserved for future use"))
	)
)
