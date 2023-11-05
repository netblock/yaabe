/*
For smu_v11_pptable.h and smu11_driver_if.h -- navi1 PowerPlay tables
See atui_atomfirmware.c for how to use PPATUI_FUNCIFY()
*/

#include "atomtree.h"
#include "atui.h"

PPATUI_FUNCIFY(struct, smu_powerplay_table_header, atui_nullstruct,
	(bios->header, atom_common_table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->table_revision, table_revision,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->table_size, table_size,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Driver portion table size. The offset to smc_pptable including header size"))
	)
)




PPATUI_FUNCIFY(struct, quadratic_f32, atomtree_powerplaytable,
	(bios->a, a (float),
		(ATUI_FRAC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->b, b (float),
		(ATUI_FRAC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->c, c (float),
		(ATUI_FRAC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->a, a (raw),
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->b, b (raw),
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->c, c (raw),
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, linear_f32, atomtree_powerplaytable,
	(bios->m, m (float),
		(ATUI_FRAC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->b, b (float),
		(ATUI_FRAC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->m, m (raw),
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->b, b (raw),
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, droop_f32, atomtree_powerplaytable,
	(bios->a, a (float),
		(ATUI_FRAC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->b, b (float),
		(ATUI_FRAC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->c, c (float),
		(ATUI_FRAC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->a, a (raw),
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->b, b (raw),
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->c, c (raw),
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, dpm_descriptor, atomtree_powerplaytable,
	(bios->VoltageMode, VoltageMode,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SnapToDiscrete, SnapToDiscrete,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->NumDiscreteLevels, NumDiscreteLevels,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding, padding,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ConversionToAvfsClk, ConversionToAvfsClk,
		(ATUI_NAN, ATUI_INLINE, linear_f32),
		(ATUI_NODESCR)
	),
	(bios->SsCurve, SsCurve,
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, powerplay_feature_control_smu11, atomtree_powerplaytable,
	(bios->feature_control, feature_control,
		(ATUI_BIN, ATUI_BITFIELD, (
			(dpm_prefetcher, 0,0, ATUI_DEC, (ATUI_NODESCR)),
			(dpm_gfxclk,     1,1, ATUI_DEC, (ATUI_NODESCR)),
			(dpm_uclk,       2,2, ATUI_DEC, (ATUI_NODESCR)),
			(dpm_socclk,     3,3, ATUI_DEC, (ATUI_NODESCR)),
			(dpm_uvd,        4,4, ATUI_DEC, (ATUI_NODESCR)),
			(dpm_vce,        5,5, ATUI_DEC, (ATUI_NODESCR)),
			(ulv,            6,6, ATUI_DEC, (ATUI_NODESCR)),
			(dpm_mp0clk,     7,7, ATUI_DEC, (ATUI_NODESCR)),
			(dpm_link,       8,8, ATUI_DEC, (ATUI_NODESCR)),
			(dpm_dcefclk,    9,9, ATUI_DEC, (ATUI_NODESCR)),
			(ds_gfxclk,     10,10, ATUI_DEC, (ATUI_NODESCR)),
			(ds_socclk,     11,11, ATUI_DEC, (ATUI_NODESCR)),
			(ds_lclk,       12,12, ATUI_DEC, (ATUI_NODESCR)),
			(ppt,           13,13, ATUI_DEC, (ATUI_NODESCR)),
			(tdc,           14,14, ATUI_DEC, (ATUI_NODESCR)),
			(thermal,       15,15, ATUI_DEC, (ATUI_NODESCR)),
			(gfx_per_cu_cg, 16,16, ATUI_DEC, (ATUI_NODESCR)),
			(rm,            17,17, ATUI_DEC, (ATUI_NODESCR)),
			(ds_dcefclk,    18,18, ATUI_DEC, (ATUI_NODESCR)),
			(acdc,          19,19, ATUI_DEC, (ATUI_NODESCR)),
			(vr0hot,        20,20, ATUI_DEC, (ATUI_NODESCR)),
			(vr1hot,        21,21, ATUI_DEC, (ATUI_NODESCR)),
			(fw_ctf,        22,22, ATUI_DEC, (ATUI_NODESCR)),
			(led_display,   23,23, ATUI_DEC, (ATUI_NODESCR)),
			(fan_control,   24,24, ATUI_DEC, (ATUI_NODESCR)),
			(gfx_edc,       25,25, ATUI_DEC, (ATUI_NODESCR)),
			(gfxoff,        26,26, ATUI_DEC, (ATUI_NODESCR)),
			(cg,            27,27, ATUI_DEC, (ATUI_NODESCR)),
			(dpm_fclk,      28,28, ATUI_DEC, (ATUI_NODESCR)),
			(ds_fclk,       29,29, ATUI_DEC, (ATUI_NODESCR)),
			(ds_mp1clk,     30,30, ATUI_DEC, (ATUI_NODESCR)),
			(ds_mp0clk,     31,31, ATUI_DEC, (ATUI_NODESCR)),
			(xgmi,          32,32, ATUI_DEC, (ATUI_NODESCR)),
			(ecc,           33,33, ATUI_DEC, (ATUI_NODESCR)),
			(spare_34,      34,34, ATUI_DEC, (ATUI_NODESCR)),
			(spare_35,      35,35, ATUI_DEC, (ATUI_NODESCR)),
			(spare_36,      36,36, ATUI_DEC, (ATUI_NODESCR)),
			(spare_37,      37,37, ATUI_DEC, (ATUI_NODESCR)),
			(spare_38,      38,38, ATUI_DEC, (ATUI_NODESCR)),
			(spare_39,      39,39, ATUI_DEC, (ATUI_NODESCR)),
			(spare_40,      40,40, ATUI_DEC, (ATUI_NODESCR)),
			(spare_41,      41,41, ATUI_DEC, (ATUI_NODESCR)),
			(spare_42,      42,42, ATUI_DEC, (ATUI_NODESCR)),
			(spare_43,      43,43, ATUI_DEC, (ATUI_NODESCR)),
			(spare_44,      44,44, ATUI_DEC, (ATUI_NODESCR)),
			(spare_45,      45,45, ATUI_DEC, (ATUI_NODESCR)),
			(spare_46,      46,46, ATUI_DEC, (ATUI_NODESCR)),
			(spare_47,      47,47, ATUI_DEC, (ATUI_NODESCR)),
			(spare_48,      48,48, ATUI_DEC, (ATUI_NODESCR)),
			(spare_49,      49,49, ATUI_DEC, (ATUI_NODESCR)),
			(spare_50,      50,50, ATUI_DEC, (ATUI_NODESCR)),
			(spare_51,      51,51, ATUI_DEC, (ATUI_NODESCR)),
			(spare_52,      52,52, ATUI_DEC, (ATUI_NODESCR)),
			(spare_53,      53,53, ATUI_DEC, (ATUI_NODESCR)),
			(spare_54,      54,54, ATUI_DEC, (ATUI_NODESCR)),
			(spare_55,      55,55, ATUI_DEC, (ATUI_NODESCR)),
			(spare_56,      56,56, ATUI_DEC, (ATUI_NODESCR)),
			(spare_57,      57,57, ATUI_DEC, (ATUI_NODESCR)),
			(spare_58,      58,58, ATUI_DEC, (ATUI_NODESCR)),
			(spare_59,      59,59, ATUI_DEC, (ATUI_NODESCR)),
			(spare_60,      60,60, ATUI_DEC, (ATUI_NODESCR)),
			(spare_61,      61,61, ATUI_DEC, (ATUI_NODESCR)),
			(spare_62,      62,62, ATUI_DEC, (ATUI_NODESCR)),
			(spare_63,      63,63, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, dpm_debug_override_smu11, atui_nullstruct,
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



PPATUI_FUNCIFY(struct, pptable_i2c_u32_smu11, atomtree_powerplaytable,
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

/*
'<,'>s@\(u\?int[0-9]\+_t\s\+\)\([a-zA-Z0-9_]\+\)\[\([a-zA-Z0-9_]\+\)\]@(NULL,
\2,\r\t\t(ATUI_NAN, ATUI_DYNARRAY, (\r\t\t\t(ATUI_NULL, \2 [%02u],\r\t\t\t\t(ATU
I_DEC, ATUI_NOFANCY), (ATUI_NODESCR)\r\t\t\t),\r\t\t\tbios->\2, \3 \/\/start, co
unt\r\t\t)), (ATUI_NODESCR)\r\t),@
*/
PPATUI_FUNCIFY(struct, smc_pptable, atomtree_powerplaytable,
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
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TdcLimitSocTau, TdcLimitSocTau,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TdcLimitGfx, TdcLimitGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TdcLimitGfxTau, TdcLimitGfxTau,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->TedgeLimit, TedgeLimit,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ThotspotLimit, ThotspotLimit,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ThbmLimit, ThbmLimit,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Tvr_gfxLimit, Tvr_gfxLimit,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Tvr_memLimit, Tvr_memLimit,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Tliquid1Limit, Tliquid1Limit,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Tliquid2Limit, Tliquid2Limit,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->TplxLimit, TplxLimit,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FitLimit, FitLimit,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->PpmPowerLimit, PpmPowerLimit,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PpmTemperatureThreshold, PpmTemperatureThreshold,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->MemoryOnPackage, MemoryOnPackage,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding8_limits, padding8_limits,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Tvr_SocLimit, Tvr_SocLimit,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->UlvVoltageOffsetSoc, UlvVoltageOffsetSoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->UlvVoltageOffsetGfx, UlvVoltageOffsetGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->UlvSmnclkDid, UlvSmnclkDid,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->UlvMp1clkDid, UlvMp1clkDid,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->UlvGfxclkBypass, UlvGfxclkBypass,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding234, Padding234,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->MinVoltageGfx, MinVoltageGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MinVoltageSoc, MinVoltageSoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MaxVoltageGfx, MaxVoltageGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MaxVoltageSoc, MaxVoltageSoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->LoadLineResistanceGfx, LoadLineResistanceGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->LoadLineResistanceSoc, LoadLineResistanceSoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	//struct dpm_descriptor DpmDescriptor[PPCLK_SMU11_COUNT];

	(NULL, FreqTableGfx,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableGfx [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableGfx, NUM_GFXCLK_DPM_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, FreqTableVclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableVclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableVclk, NUM_VCLK_DPM_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, FreqTableDclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableDclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableDclk, NUM_DCLK_DPM_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, FreqTableEclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableEclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableEclk, NUM_ECLK_DPM_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, FreqTableSocclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableSocclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableSocclk, NUM_SOCCLK_DPM_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, FreqTableUclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableUclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableUclk, NUM_UCLK_DPM_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, FreqTableFclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableFclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableFclk, NUM_FCLK_DPM_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, FreqTableDcefclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableDcefclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableDcefclk, NUM_DCEFCLK_DPM_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, FreqTableDispclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTableDispclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTableDispclk, NUM_DISPCLK_DPM_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, FreqTablePixclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTablePixclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTablePixclk, NUM_PIXCLK_DPM_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, FreqTablePhyclk,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, FreqTablePhyclk [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->FreqTablePhyclk, NUM_PHYCLK_DPM_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),

    (bios->DcModeMaxFreq[PPCLK_SMU11_GFXCLK], DcModeMaxFreq (GFXCLK),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->DcModeMaxFreq[PPCLK_SMU11_VCLK], DcModeMaxFreq (VCLK),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->DcModeMaxFreq[PPCLK_SMU11_DCLK], DcModeMaxFreq (DCLK),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->DcModeMaxFreq[PPCLK_SMU11_ECLK], DcModeMaxFreq (ECLK),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->DcModeMaxFreq[PPCLK_SMU11_SOCCLK], DcModeMaxFreq (SOCCLK),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->DcModeMaxFreq[PPCLK_SMU11_UCLK], DcModeMaxFreq (UCLK),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->DcModeMaxFreq[PPCLK_SMU11_DCEFCLK], DcModeMaxFreq (DCEFCLK),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->DcModeMaxFreq[PPCLK_SMU11_DISPCLK], DcModeMaxFreq (DISPCLK),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->DcModeMaxFreq[PPCLK_SMU11_PIXCLK], DcModeMaxFreq (PIXCLK),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->DcModeMaxFreq[PPCLK_SMU11_PHYCLK], DcModeMaxFreq (PHYCLK),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->DcModeMaxFreq[PPCLK_SMU11_FCLK], DcModeMaxFreq (FCLK),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),


	(bios->Padding8_Clks, Padding8_Clks,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(NULL, Mp0clkFreq,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, Mp0clkFreq [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->Mp0clkFreq, NUM_MP0CLK_DPM_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, Mp0DpmVoltage,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, Mp0DpmVoltage [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->Mp0DpmVoltage, NUM_MP0CLK_DPM_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),


	(bios->GfxclkFidle, GfxclkFidle,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxclkSlewRate, GfxclkSlewRate,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->CksEnableFreq, CksEnableFreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding789, Padding789,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->CksVoltageOffset, CksVoltageOffset,
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->Padding567, Padding567,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->GfxclkDsMaxFreq, GfxclkDsMaxFreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxclkSource, GfxclkSource,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding456, Padding456,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->LowestUclkReservedForUlv, LowestUclkReservedForUlv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding8_Uclk, Padding8_Uclk,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),


	(NULL, PcieGenSpeed,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, PcieGenSpeed [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->PcieGenSpeed, NUM_LINK_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, PcieLaneCount,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, PcieLaneCount [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->PcieLaneCount, NUM_LINK_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, LclkFreq,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, LclkFreq [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->LclkFreq, NUM_LINK_LEVELS_SMU11 //start, count
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
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->FanStopTemp, FanStopTemp,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanStartTemp, FanStartTemp,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
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

	(bios->OverrideAvfsGbGfx, OverrideAvfsGbGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->OverrideAvfsGbSoc, OverrideAvfsGbSoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Padding8_Avfs, Padding8_Avfs,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->qAvfsGbGfx, qAvfsGbGfx,
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->qAvfsGbSoc, qAvfsGbSoc,
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
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
		(ATUI_NODESCR)
	),
	(bios->dBtcGbSoc, dBtcGbSoc,
		(ATUI_NAN, ATUI_INLINE, droop_f32),
		(ATUI_NODESCR)
	),
	(bios->qAgingGbGfx, qAgingGbGfx,
		(ATUI_NAN, ATUI_INLINE, linear_f32),
		(ATUI_NODESCR)
	),
	(bios->qAgingGbSoc, qAgingGbSoc,
		(ATUI_NAN, ATUI_INLINE, linear_f32),
		(ATUI_NODESCR)
	),


	(bios->qStaticVoltageOffsetGfx, qStaticVoltageOffsetGfx,
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),
	(bios->qStaticVoltageOffsetSoc, qStaticVoltageOffsetSoc,
		(ATUI_NAN, ATUI_INLINE, quadratic_f32),
		(ATUI_NODESCR)
	),


	(bios->DcTolGfx, DcTolGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DcTolSoc, DcTolSoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->DcBtcEnabledGfx, DcBtcEnabledGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DcBtcEnabledSoc, DcBtcEnabledSoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Padding8_GfxBtc, Padding8_GfxBtc,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->DcBtcMinGfx, DcBtcMinGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DcBtcMinSoc, DcBtcMinSoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->DcBtcMaxGfx, DcBtcMaxGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DcBtcMaxSoc, DcBtcMaxSoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(NULL, XgmiLinkSpeed,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, XgmiLinkSpeed [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->XgmiLinkSpeed, NUM_XGMI_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, XgmiLinkWidth,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, XgmiLinkWidth [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->XgmiLinkWidth, NUM_XGMI_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, XgmiFclkFreq,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, XgmiFclkFreq [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->XgmiFclkFreq, NUM_XGMI_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, XgmiUclkFreq,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, XgmiUclkFreq [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->XgmiUclkFreq, NUM_XGMI_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, XgmiSocclkFreq,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, XgmiSocclkFreq [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->XgmiSocclkFreq, NUM_XGMI_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),
	(NULL, XgmiSocVoltage,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, XgmiSocVoltage [%02u],
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->XgmiSocVoltage, NUM_XGMI_LEVELS_SMU11 //start, count
		)), (ATUI_NODESCR)
	),

	(bios->DebugOverrides, DebugOverrides,
		(ATUI_NODISPLAY, ATUI_INLINE, dpm_debug_override_smu11),
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
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MinVoltageUlvSoc, MinVoltageUlvSoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->MGpuFanBoostLimitRpm, MGpuFanBoostLimitRpm,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding16_Fan, padding16_Fan,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FanGainVrMem0, FanGainVrMem0,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FanGainVrMem1, FanGainVrMem1,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->DcBtcGbGfx, DcBtcGbGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DcBtcGbSoc, DcBtcGbSoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Reserved, Reserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->Padding32, Padding32,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->MaxVoltageStepGfx, MaxVoltageStepGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MaxVoltageStepSoc, MaxVoltageStepSoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
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
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocUlvPhaseSheddingMask, SocUlvPhaseSheddingMask,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ExternalSensorPresent, ExternalSensorPresent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding8_V, Padding8_V,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->GfxMaxCurrent, GfxMaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->GfxOffset, GfxOffset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding_TelemetryGfx, Padding_TelemetryGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->SocMaxCurrent, SocMaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocOffset, SocOffset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding_TelemetrySoc, Padding_TelemetrySoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem0MaxCurrent, Mem0MaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Mem0Offset, Mem0Offset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding_TelemetryMem0, Padding_TelemetryMem0,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem1MaxCurrent, Mem1MaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Mem1Offset, Mem1Offset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding_TelemetryMem1, Padding_TelemetryMem1,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->AcDcGpio, AcDcGpio,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->AcDcPolarity, AcDcPolarity,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->VR0HotGpio, VR0HotGpio,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->VR0HotPolarity, VR0HotPolarity,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->VR1HotGpio, VR1HotGpio,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->VR1HotPolarity, VR1HotPolarity,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding1, Padding1,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding2, Padding2,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),



	(bios->LedPin0, LedPin0,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->LedPin1, LedPin1,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->LedPin2, LedPin2,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding8_4, padding8_4,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->PllGfxclkSpreadEnabled, PllGfxclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PllGfxclkSpreadPercent, PllGfxclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PllGfxclkSpreadFreq, PllGfxclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->UclkSpreadEnabled, UclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->UclkSpreadPercent, UclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->UclkSpreadFreq, UclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FclkSpreadEnabled, FclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FclkSpreadPercent, FclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FclkSpreadFreq, FclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->FllGfxclkSpreadEnabled, FllGfxclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FllGfxclkSpreadPercent, FllGfxclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->FllGfxclkSpreadFreq, FllGfxclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
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
	(bios->cap[SMU_11_0_ODCAP_GFXCLK_LIMITS], gfxclk limits,
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
	),
	(bios->cap[SMU_11_0_ODCAP_GFXCLK_CURVE], gfxclk curve,
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
	),
	(bios->cap[SMU_11_0_ODCAP_UCLK_MAX], uclk max,
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
	),
	(bios->cap[SMU_11_0_ODCAP_POWER_LIMIT], power limit,
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
	),
	(bios->cap[SMU_11_0_ODCAP_FAN_ACOUSTIC_LIMIT], fan acoustic limit,
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
	),
	(bios->cap[SMU_11_0_ODCAP_FAN_SPEED_MIN], fan speed min,
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
	),
	(bios->cap[SMU_11_0_ODCAP_TEMPERATURE_FAN], temperature fan,
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
	),
	(bios->cap[SMU_11_0_ODCAP_TEMPERATURE_SYSTEM], temperature system,
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
	),
	(bios->cap[SMU_11_0_ODCAP_MEMORY_TIMING_TUNE], memory timing tune,
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
	),
	(bios->cap[SMU_11_0_ODCAP_FAN_ZERO_RPM_CONTROL], fan zero rpm control,
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
	),
	(bios->cap[SMU_11_0_ODCAP_AUTO_UV_ENGINE], auto uv engine,
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
	),
	(bios->cap[SMU_11_0_ODCAP_AUTO_OC_ENGINE], auto oc engine,
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
	),
	(bios->cap[SMU_11_0_ODCAP_AUTO_OC_MEMORY], auto oc memory,
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
	),
	(bios->cap[SMU_11_0_ODCAP_FAN_CURVE], fan curve,
		(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
	),
	(NULL, other OD feature support flags,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, OD feature [14 + %02u],
					// if CAP_COUNT changes, please change this 14
				(ATUI_DEC, ATUI_NOFANCY), ((LANG_ENG, "support flag"))
			),
			(&(bios->cap[SMU_11_0_ODCAP_COUNT])), // start
			(SMU_11_0_MAX_ODSETTING - SMU_11_0_ODCAP_COUNT) // count
		)), (ATUI_NODESCR)
	),
    (bios->max[SMU_11_0_ODSETTING_GFXCLKFMAX], gfx clk fmax (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_GFXCLKFMAX], gfx clk fmax (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_GFXCLKFMIN], gfx clk fmin (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_GFXCLKFMIN], gfx clk fmin (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P1], vddgfx curve freq p1 (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P1], vddgfx curve freq p1 (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P1], vddgfx curve voltage p1 (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P1], vddgfx curve voltage p1 (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P2], vddgfx curve freq p2 (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P2], vddgfx curve freq p2 (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P2], vddgfx curve voltage p2 (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P2], vddgfx curve voltage p2 (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P3], vddgfx curve freq p3 (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P3], vddgfx curve freq p3 (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P3], vddgfx curve voltage p3 (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P3], vddgfx curve voltage p3 (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_UCLKFMAX], uclk fmax (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_UCLKFMAX], uclk fmax (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_POWERPERCENTAGE], power percentage (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_POWERPERCENTAGE], power percentage (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_FANRPMMIN], fan rpm min (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_FANRPMMIN], fan rpm min (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_FANRPMACOUSTICLIMIT], fan rpm acoustic limit (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_FANRPMACOUSTICLIMIT], fan rpm acoustic limit (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_FANTARGETTEMPERATURE], fan target temperature (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_FANTARGETTEMPERATURE], fan target temperature (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_OPERATINGTEMPMAX], operating temp max (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_OPERATINGTEMPMAX], operating temp max (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_ACTIMING], ac timing (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_ACTIMING], ac timing (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_FAN_ZERO_RPM_CONTROL], fan zero rpm control (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_FAN_ZERO_RPM_CONTROL], fan zero rpm control (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_AUTOUVENGINE], auto uv engine (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_AUTOUVENGINE], auto uv engine (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_AUTOOCENGINE], auto oc engine (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_AUTOOCENGINE], auto oc engine (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_ODSETTING_AUTOOCMEMORY], auto oc memory (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_ODSETTING_AUTOOCMEMORY], auto oc memory (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
	(NULL, other OD settings (max),
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, OD setting  (max) [19 + %02u],
					// if ODSETTING_COUNT changes, please change this 19
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			(&(bios->max[SMU_11_0_ODSETTING_COUNT])), // start
			(SMU_11_0_MAX_ODSETTING - SMU_11_0_ODSETTING_COUNT) // count
		)), (ATUI_NODESCR)
	),
	(NULL, other OD settings (min),
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, OD setting (min) [19 + %02u],
					// if ODSETTING_COUNT changes, please change this 19
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			(&(bios->min[SMU_11_0_ODSETTING_COUNT])), // start
			(SMU_11_0_MAX_ODSETTING - SMU_11_0_ODSETTING_COUNT) // count
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, smu_11_0_power_saving_clock_table, atomtree_powerplaytable,
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
    (bios->max[SMU_11_0_PPCLOCK_GFXCLK], GFXCLK (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_PPCLOCK_GFXCLK], GFXCLK (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_PPCLOCK_VCLK], VCLK (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_PPCLOCK_VCLK], VCLK (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_PPCLOCK_DCLK], DCLK (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_PPCLOCK_DCLK], DCLK (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_PPCLOCK_ECLK], ECLK (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_PPCLOCK_ECLK], ECLK (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_PPCLOCK_SOCCLK], SOCCLK (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_PPCLOCK_SOCCLK], SOCCLK (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_PPCLOCK_UCLK], UCLK (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_PPCLOCK_UCLK], UCLK (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_PPCLOCK_DCEFCLK], DCEFCLK (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_PPCLOCK_DCEFCLK], DCEFCLK (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_PPCLOCK_DISPCLK], DISPCLK (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_PPCLOCK_DISPCLK], DISPCLK (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_PPCLOCK_PIXCLK], PIXCLK (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_PPCLOCK_PIXCLK], PIXCLK (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->max[SMU_11_0_PPCLOCK_PHYCLK], PHYCLK (max),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
    (bios->min[SMU_11_0_PPCLOCK_PHYCLK], PHYCLK (min),
        (ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
    ),
	(NULL, other PowerSavingClock Modes (max),
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, PowerSavingClock Mode (max) [10 + %02u],
					// if PPCLOCK_COUNT changes, please change this 10
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			(&(bios->max[SMU_11_0_PPCLOCK_COUNT])), // start
			(SMU_11_0_MAX_PPCLOCK - SMU_11_0_PPCLOCK_COUNT) // count
		)), (ATUI_NODESCR)
	),
	(NULL, other PowerSavingClock Modes(min),
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, PowerSavingClock Mode (min) [10 + %02u],
					// if PPCLOCK_COUNT changes, please change this 10
				(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			(&(bios->min[SMU_11_0_PPCLOCK_COUNT])), // start
			(SMU_11_0_MAX_PPCLOCK - SMU_11_0_PPCLOCK_COUNT) // count
		)), (ATUI_NODESCR)
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
		(ATUI_BIN, ATUI_BITFIELD, (
			(powerplay,     0,0, ATUI_DEC, (ATUI_NODESCR)),
			(sbios_powersource, 1,1, ATUI_DEC, (ATUI_NODESCR)),
			(hardware_dc,   2,2, ATUI_DEC, (ATUI_NODESCR)),
			(BACO,          3,3, ATUI_DEC, (ATUI_NODESCR)),
			(MACO,          4,4, ATUI_DEC, (ATUI_NODESCR)),
			(shadow_pstate, 5,5, ATUI_DEC, (ATUI_NODESCR)),
			(reserved,     31,6, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
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
