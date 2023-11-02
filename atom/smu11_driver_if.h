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
 *
 */

#ifndef SMU11_DRIVER_IF_H
#define SMU11_DRIVER_IF_H


#pragma pack(push, 1)

// *** IMPORTANT ***
// SMU TEAM: Always increment the interface version if
// any structure is changed in this file
// Be aware of that the version should be updated in
// smu_v11_0.h, rename is also needed.
// #define SMU11_DRIVER_IF_VERSION 0x13

#define PPTABLE_V20_SMU_VERSION 3

#define NUM_GFXCLK_DPM_LEVELS  16
#define NUM_VCLK_DPM_LEVELS    8
#define NUM_DCLK_DPM_LEVELS    8
#define NUM_ECLK_DPM_LEVELS    8
#define NUM_MP0CLK_DPM_LEVELS  2
#define NUM_SOCCLK_DPM_LEVELS  8
#define NUM_UCLK_DPM_LEVELS    4
#define NUM_FCLK_DPM_LEVELS    8
#define NUM_DCEFCLK_DPM_LEVELS 8
#define NUM_DISPCLK_DPM_LEVELS 8
#define NUM_PIXCLK_DPM_LEVELS  8
#define NUM_PHYCLK_DPM_LEVELS  8
#define NUM_LINK_LEVELS        2
#define NUM_XGMI_LEVELS        2

#define MAX_GFXCLK_DPM_LEVEL  (NUM_GFXCLK_DPM_LEVELS  - 1)
#define MAX_VCLK_DPM_LEVEL    (NUM_VCLK_DPM_LEVELS    - 1)
#define MAX_DCLK_DPM_LEVEL    (NUM_DCLK_DPM_LEVELS    - 1)
#define MAX_ECLK_DPM_LEVEL    (NUM_ECLK_DPM_LEVELS    - 1)
#define MAX_MP0CLK_DPM_LEVEL  (NUM_MP0CLK_DPM_LEVELS  - 1)
#define MAX_SOCCLK_DPM_LEVEL  (NUM_SOCCLK_DPM_LEVELS  - 1)
#define MAX_UCLK_DPM_LEVEL    (NUM_UCLK_DPM_LEVELS    - 1)
#define MAX_FCLK_DPM_LEVEL    (NUM_FCLK_DPM_LEVELS    - 1)
#define MAX_DCEFCLK_DPM_LEVEL (NUM_DCEFCLK_DPM_LEVELS - 1)
#define MAX_DISPCLK_DPM_LEVEL (NUM_DISPCLK_DPM_LEVELS - 1)
#define MAX_PIXCLK_DPM_LEVEL  (NUM_PIXCLK_DPM_LEVELS  - 1)
#define MAX_PHYCLK_DPM_LEVEL  (NUM_PHYCLK_DPM_LEVELS  - 1)
#define MAX_LINK_LEVEL        (NUM_LINK_LEVELS        - 1)
#define MAX_XGMI_LEVEL        (NUM_XGMI_LEVELS        - 1)

#define PPSMC_GeminiModeNone   0
#define PPSMC_GeminiModeMaster 1
#define PPSMC_GeminiModeSlave  2

/*
#define FEATURE_DPM_PREFETCHER_BIT 0
#define FEATURE_DPM_GFXCLK_BIT     1
#define FEATURE_DPM_UCLK_BIT       2
#define FEATURE_DPM_SOCCLK_BIT     3
#define FEATURE_DPM_UVD_BIT        4
#define FEATURE_DPM_VCE_BIT        5
#define FEATURE_ULV_BIT            6
#define FEATURE_DPM_MP0CLK_BIT     7
#define FEATURE_DPM_LINK_BIT       8
#define FEATURE_DPM_DCEFCLK_BIT    9
#define FEATURE_DS_GFXCLK_BIT      10
#define FEATURE_DS_SOCCLK_BIT      11
#define FEATURE_DS_LCLK_BIT        12
#define FEATURE_PPT_BIT            13
#define FEATURE_TDC_BIT            14
#define FEATURE_THERMAL_BIT        15
#define FEATURE_GFX_PER_CU_CG_BIT  16
#define FEATURE_RM_BIT             17
#define FEATURE_DS_DCEFCLK_BIT     18
#define FEATURE_ACDC_BIT           19
#define FEATURE_VR0HOT_BIT         20
#define FEATURE_VR1HOT_BIT         21
#define FEATURE_FW_CTF_BIT         22
#define FEATURE_LED_DISPLAY_BIT    23
#define FEATURE_FAN_CONTROL_BIT    24
#define FEATURE_GFX_EDC_BIT        25
#define FEATURE_GFXOFF_BIT         26
#define FEATURE_CG_BIT             27
#define FEATURE_DPM_FCLK_BIT       28
#define FEATURE_DS_FCLK_BIT        29
#define FEATURE_DS_MP1CLK_BIT      30
#define FEATURE_DS_MP0CLK_BIT      31
#define FEATURE_XGMI_BIT           32
#define FEATURE_ECC_BIT            33
#define FEATURE_SPARE_34_BIT       34
#define FEATURE_SPARE_35_BIT       35
#define FEATURE_SPARE_36_BIT       36
#define FEATURE_SPARE_37_BIT       37
#define FEATURE_SPARE_38_BIT       38
#define FEATURE_SPARE_39_BIT       39
#define FEATURE_SPARE_40_BIT       40
#define FEATURE_SPARE_41_BIT       41
#define FEATURE_SPARE_42_BIT       42
#define FEATURE_SPARE_43_BIT       43
#define FEATURE_SPARE_44_BIT       44
#define FEATURE_SPARE_45_BIT       45
#define FEATURE_SPARE_46_BIT       46
#define FEATURE_SPARE_47_BIT       47
#define FEATURE_SPARE_48_BIT       48
#define FEATURE_SPARE_49_BIT       49
#define FEATURE_SPARE_50_BIT       50
#define FEATURE_SPARE_51_BIT       51
#define FEATURE_SPARE_52_BIT       52
#define FEATURE_SPARE_53_BIT       53
#define FEATURE_SPARE_54_BIT       54
#define FEATURE_SPARE_55_BIT       55
#define FEATURE_SPARE_56_BIT       56
#define FEATURE_SPARE_57_BIT       57
#define FEATURE_SPARE_58_BIT       58
#define FEATURE_SPARE_59_BIT       59
#define FEATURE_SPARE_60_BIT       60
#define FEATURE_SPARE_61_BIT       61
#define FEATURE_SPARE_62_BIT       62
#define FEATURE_SPARE_63_BIT       63

#define NUM_FEATURES               64

#define FEATURE_DPM_PREFETCHER_MASK (1 << FEATURE_DPM_PREFETCHER_BIT)
#define FEATURE_DPM_GFXCLK_MASK     (1 << FEATURE_DPM_GFXCLK_BIT)
#define FEATURE_DPM_UCLK_MASK       (1 << FEATURE_DPM_UCLK_BIT)
#define FEATURE_DPM_SOCCLK_MASK     (1 << FEATURE_DPM_SOCCLK_BIT)
#define FEATURE_DPM_UVD_MASK        (1 << FEATURE_DPM_UVD_BIT)
#define FEATURE_DPM_VCE_MASK        (1 << FEATURE_DPM_VCE_BIT)
#define FEATURE_ULV_MASK            (1 << FEATURE_ULV_BIT)
#define FEATURE_DPM_MP0CLK_MASK     (1 << FEATURE_DPM_MP0CLK_BIT)
#define FEATURE_DPM_LINK_MASK       (1 << FEATURE_DPM_LINK_BIT)
#define FEATURE_DPM_DCEFCLK_MASK    (1 << FEATURE_DPM_DCEFCLK_BIT)
#define FEATURE_DS_GFXCLK_MASK      (1 << FEATURE_DS_GFXCLK_BIT)
#define FEATURE_DS_SOCCLK_MASK      (1 << FEATURE_DS_SOCCLK_BIT)
#define FEATURE_DS_LCLK_MASK        (1 << FEATURE_DS_LCLK_BIT)
#define FEATURE_PPT_MASK            (1 << FEATURE_PPT_BIT)
#define FEATURE_TDC_MASK            (1 << FEATURE_TDC_BIT)
#define FEATURE_THERMAL_MASK        (1 << FEATURE_THERMAL_BIT)
#define FEATURE_GFX_PER_CU_CG_MASK  (1 << FEATURE_GFX_PER_CU_CG_BIT)
#define FEATURE_RM_MASK             (1 << FEATURE_RM_BIT)
#define FEATURE_DS_DCEFCLK_MASK     (1 << FEATURE_DS_DCEFCLK_BIT)
#define FEATURE_ACDC_MASK           (1 << FEATURE_ACDC_BIT)
#define FEATURE_VR0HOT_MASK         (1 << FEATURE_VR0HOT_BIT)
#define FEATURE_VR1HOT_MASK         (1 << FEATURE_VR1HOT_BIT)
#define FEATURE_FW_CTF_MASK         (1 << FEATURE_FW_CTF_BIT)
#define FEATURE_LED_DISPLAY_MASK    (1 << FEATURE_LED_DISPLAY_BIT)
#define FEATURE_FAN_CONTROL_MASK    (1 << FEATURE_FAN_CONTROL_BIT)
#define FEATURE_GFX_EDC_MASK        (1 << FEATURE_GFX_EDC_BIT)
#define FEATURE_GFXOFF_MASK         (1 << FEATURE_GFXOFF_BIT)
#define FEATURE_CG_MASK             (1 << FEATURE_CG_BIT)
#define FEATURE_DPM_FCLK_MASK       (1 << FEATURE_DPM_FCLK_BIT)
#define FEATURE_DS_FCLK_MASK        (1 << FEATURE_DS_FCLK_BIT)
#define FEATURE_DS_MP1CLK_MASK      (1 << FEATURE_DS_MP1CLK_BIT)
#define FEATURE_DS_MP0CLK_MASK      (1 << FEATURE_DS_MP0CLK_BIT)
#define FEATURE_XGMI_MASK           (1ULL << FEATURE_XGMI_BIT)
#define FEATURE_ECC_MASK            (1ULL << FEATURE_ECC_BIT)
*/
union powerplay_features {
	uint64_t features_to_run;
	struct { uint64_t
		dpm_prefetcher :0-0 +1,
		dpm_gfxclk     :1-1 +1,
		dpm_uclk       :2-2 +1,
		dpm_socclk     :3-3 +1,
		dpm_uvd        :4-4 +1,
		dpm_vce        :5-5 +1,
		ulv            :6-6 +1,
		dpm_mp0clk     :7-7 +1,
		dpm_link       :8-8 +1,
		dpm_dcefclk    :9-9 +1,
		ds_gfxclk     :10-10 +1,
		ds_socclk     :11-11 +1,
		ds_lclk       :12-12 +1,
		ppt           :13-13 +1,
		tdc           :14-14 +1,
		thermal       :15-15 +1,
		gfx_per_cu_cg :16-16 +1,
		rm            :17-17 +1,
		ds_dcefclk    :18-18 +1,
		acdc          :19-19 +1,
		vr0hot        :20-20 +1,
		vr1hot        :21-21 +1,
		fw_ctf        :22-22 +1,
		led_display   :23-23 +1,
		fan_control   :24-24 +1,
		gfx_edc       :25-25 +1,
		gfxoff        :26-26 +1,
		cg            :27-27 +1,
		dpm_fclk      :28-28 +1,
		ds_fclk       :29-29 +1,
		ds_mp1clk     :30-30 +1,
		ds_mp0clk     :31-31 +1,
		xgmi          :32-32 +1,
		ecc           :33-33 +1,
		spare_34      :34-34 +1,
		spare_35      :35-35 +1,
		spare_36      :36-36 +1,
		spare_37      :37-37 +1,
		spare_38      :38-38 +1,
		spare_39      :39-39 +1,
		spare_40      :40-40 +1,
		spare_41      :41-41 +1,
		spare_42      :42-42 +1,
		spare_43      :43-43 +1,
		spare_44      :44-44 +1,
		spare_45      :45-45 +1,
		spare_46      :46-46 +1,
		spare_47      :47-47 +1,
		spare_48      :48-48 +1,
		spare_49      :49-49 +1,
		spare_50      :50-50 +1,
		spare_51      :51-51 +1,
		spare_52      :52-52 +1,
		spare_53      :53-53 +1,
		spare_54      :54-54 +1,
		spare_55      :55-55 +1,
		spare_56      :56-56 +1,
		spare_57      :57-57 +1,
		spare_58      :58-58 +1,
		spare_59      :59-59 +1,
		spare_60      :60-60 +1,
		spare_61      :61-61 +1,
		spare_62      :62-62 +1,
		spare_63      :63-63 +1;
	};
};


/*
#define DPM_OVERRIDE_DISABLE_SOCCLK_PID             0x00000001
#define DPM_OVERRIDE_DISABLE_UCLK_PID               0x00000002
#define DPM_OVERRIDE_ENABLE_VOLT_LINK_UVD_SOCCLK    0x00000004
#define DPM_OVERRIDE_ENABLE_VOLT_LINK_UVD_UCLK      0x00000008
#define DPM_OVERRIDE_ENABLE_FREQ_LINK_VCLK_SOCCLK   0x00000010
#define DPM_OVERRIDE_ENABLE_FREQ_LINK_VCLK_UCLK     0x00000020
#define DPM_OVERRIDE_ENABLE_FREQ_LINK_DCLK_SOCCLK   0x00000040
#define DPM_OVERRIDE_ENABLE_FREQ_LINK_DCLK_UCLK     0x00000080
#define DPM_OVERRIDE_ENABLE_VOLT_LINK_VCE_SOCCLK    0x00000100
#define DPM_OVERRIDE_ENABLE_VOLT_LINK_VCE_UCLK      0x00000200
#define DPM_OVERRIDE_ENABLE_FREQ_LINK_ECLK_SOCCLK   0x00000400
#define DPM_OVERRIDE_ENABLE_FREQ_LINK_ECLK_UCLK     0x00000800
#define DPM_OVERRIDE_ENABLE_FREQ_LINK_GFXCLK_SOCCLK 0x00001000
#define DPM_OVERRIDE_ENABLE_FREQ_LINK_GFXCLK_UCLK   0x00002000
#define DPM_OVERRIDE_ENABLE_GFXOFF_GFXCLK_SWITCH    0x00004000
#define DPM_OVERRIDE_ENABLE_GFXOFF_SOCCLK_SWITCH    0x00008000
#define DPM_OVERRIDE_ENABLE_GFXOFF_UCLK_SWITCH      0x00010000
#define DPM_OVERRIDE_ENABLE_GFXOFF_FCLK_SWITCH      0x00020000
*/

union dpm_override { // what does this go to?
	uint32_t dpm_override_flags;
	struct { uint32_t
		disable_socclk_pid              :0-0 +1,
		disable_uclk_pid                :1-1 +1,
		enable_volt_link_uvd_socclk     :2-2 +1,
		enable_volt_link_uvd_uclk       :3-3 +1,
		enable_freq_link_vclk_socclk    :4-4 +1,
		enable_freq_link_vclk_uclk      :5-5 +1,
		enable_freq_link_dclk_socclk    :6-6 +1,
		enable_freq_link_dclk_uclk      :7-7 +1,
		enable_volt_link_vce_socclk     :8-8 +1,
		enable_volt_link_vce_uclk       :9-9 +1,
		enable_freq_link_eclk_socclk   :10-10 +1,
		enable_freq_link_eclk_uclk     :11-11 +1,
		enable_freq_link_gfxclk_socclk :12-12 +1,
		enable_freq_link_gfxclk_uclk   :13-13 +1,
		enable_gfxoff_gfxclk_switch    :14-14 +1,
		enable_gfxoff_socclk_switch    :15-15 +1,
		enable_gfxoff_uclk_switch      :16-16 +1,
		enable_gfxoff_fclk_switch      :17-17 +1,
		reserved                       :31-18 +1;
	};
};





#define I2C_CONTROLLER_ENABLED     1
#define I2C_CONTROLLER_DISABLED    0

#define VR_MAPPING_VR_SELECT_MASK  0x01
#define VR_MAPPING_VR_SELECT_SHIFT 0x00

#define VR_MAPPING_PLANE_SELECT_MASK  0x02
#define VR_MAPPING_PLANE_SELECT_SHIFT 0x01


#define PSI_SEL_VR0_PLANE0_PSI0  0x01
#define PSI_SEL_VR0_PLANE0_PSI1  0x02
#define PSI_SEL_VR0_PLANE1_PSI0  0x04
#define PSI_SEL_VR0_PLANE1_PSI1  0x08
#define PSI_SEL_VR1_PLANE0_PSI0  0x10
#define PSI_SEL_VR1_PLANE0_PSI1  0x20
#define PSI_SEL_VR1_PLANE1_PSI0  0x40
#define PSI_SEL_VR1_PLANE1_PSI1  0x80



#define THROTTLER_STATUS_PADDING_BIT      0
#define THROTTLER_STATUS_TEMP_EDGE_BIT    1
#define THROTTLER_STATUS_TEMP_HOTSPOT_BIT 2
#define THROTTLER_STATUS_TEMP_HBM_BIT     3
#define THROTTLER_STATUS_TEMP_VR_GFX_BIT  4
#define THROTTLER_STATUS_TEMP_VR_SOC_BIT  5
#define THROTTLER_STATUS_TEMP_VR_MEM0_BIT 6
#define THROTTLER_STATUS_TEMP_VR_MEM1_BIT 7
#define THROTTLER_STATUS_TEMP_LIQUID_BIT  8
#define THROTTLER_STATUS_TEMP_PLX_BIT     9
#define THROTTLER_STATUS_TEMP_SKIN_BIT    10
#define THROTTLER_STATUS_TDC_GFX_BIT      11
#define THROTTLER_STATUS_TDC_SOC_BIT      12
#define THROTTLER_STATUS_PPT_BIT          13
#define THROTTLER_STATUS_FIT_BIT          14
#define THROTTLER_STATUS_PPM_BIT          15


#define TABLE_TRANSFER_OK         0x0
#define TABLE_TRANSFER_FAILED     0xFF


#define WORKLOAD_DEFAULT_BIT              0
#define WORKLOAD_PPLIB_FULL_SCREEN_3D_BIT 1
#define WORKLOAD_PPLIB_POWER_SAVING_BIT   2
#define WORKLOAD_PPLIB_VIDEO_BIT          3
#define WORKLOAD_PPLIB_VR_BIT             4
#define WORKLOAD_PPLIB_COMPUTE_BIT        5
#define WORKLOAD_PPLIB_CUSTOM_BIT         6
#define WORKLOAD_PPLIB_COUNT              7


#define XGMI_STATE_D0 1
#define XGMI_STATE_D3 0

/*
typedef enum {
	I2C_CONTROLLER_PORT_0 = 0,
	I2C_CONTROLLER_PORT_1 = 1,
} I2cControllerPort_e;

typedef enum {
	I2C_CONTROLLER_NAME_VR_GFX   = 0,
	I2C_CONTROLLER_NAME_VR_SOC   = 1,
	I2C_CONTROLLER_NAME_VR_VDDCI = 2,
	I2C_CONTROLLER_NAME_VR_HBM   = 3, // MVDD
	I2C_CONTROLLER_NAME_LIQUID_0 = 4,
	I2C_CONTROLLER_NAME_LIQUID_1 = 5,
	I2C_CONTROLLER_NAME_PLX      = 6,
	I2C_CONTROLLER_NAME_COUNT    = 7,
} I2cControllerName_e;

typedef enum {
	I2C_CONTROLLER_THROTTLER_TYPE_NONE = 0,
	I2C_CONTROLLER_THROTTLER_VR_GFX    = 1,
	I2C_CONTROLLER_THROTTLER_VR_SOC    = 2,
	I2C_CONTROLLER_THROTTLER_VR_VDDCI  = 3,
	I2C_CONTROLLER_THROTTLER_VR_HBM    = 4, // MVDD
	I2C_CONTROLLER_THROTTLER_LIQUID_0  = 5,
	I2C_CONTROLLER_THROTTLER_LIQUID_1  = 6,
	I2C_CONTROLLER_THROTTLER_PLX       = 7,
} I2cControllerThrottler_e;

typedef enum {
	I2C_CONTROLLER_PROTOCOL_VR_XPDE132G5 = 0,
	I2C_CONTROLLER_PROTOCOL_VR_IR35217   = 1,
	I2C_CONTROLLER_PROTOCOL_TMP_TMP102A  = 2,
	I2C_CONTROLLER_PROTOCOL_SPARE_0 = 3, // TMP
	I2C_CONTROLLER_PROTOCOL_SPARE_1 = 4,
	I2C_CONTROLLER_PROTOCOL_SPARE_2 = 5,
} I2cControllerProtocol_e;

typedef enum {
	I2C_CONTROLLER_SPEED_SLOW = 0,
	I2C_CONTROLLER_SPEED_FAST = 1,
} I2cControllerSpeed_e;



//typedef struct pp_i2c_controller_config I2cControllerConfig_t;
struct pp_i2c_controller_config {
//see also smudpm_i2ccontrollerconfig_t and smudpm_i2c_controller_config_v2
//of atomfirmware.h
	uint32_t Enabled;
	uint32_t SlaveAddress;
	uint32_t ControllerPort;
	uint32_t ControllerName;

	uint32_t ThermalThrottler;
	uint32_t I2cProtocol;
	uint32_t I2cSpeed;
};
*/

//typedef struct quadratic_u32 QuadraticInt_t;
struct quadratic_u32 {
	uint32_t a;
	uint32_t b;
	uint32_t c;
};

//typedef struct linear_u32 LinearInt_t;
struct linear_u32 {
	uint32_t m;
	uint32_t b;
};

//typedef struct droop_u32 DroopInt_t;
struct droop_u32 {
	uint32_t a;
	uint32_t b;
	uint32_t c;
};

enum PPCLK_e {
	PPCLK_GFXCLK  = 0,
	PPCLK_VCLK    = 1,
	PPCLK_DCLK    = 2,
	PPCLK_ECLK    = 3,
	PPCLK_SOCCLK  = 4,
	PPCLK_UCLK    = 5,
	PPCLK_DCEFCLK = 6,
	PPCLK_DISPCLK = 7,
	PPCLK_PIXCLK  = 8,
	PPCLK_PHYCLK  = 9,
	PPCLK_FCLK   = 10,
	PPCLK_COUNT  = 11,
};

enum POWER_SOURCE_e {
	POWER_SOURCE_AC = 0,
	POWER_SOURCE_DC = 1,
	POWER_SOURCE_COUNT = 2,
};

enum VOLTAGE_MODE_e {
	VOLTAGE_MODE_AVFS    = 0,
	VOLTAGE_MODE_AVFS_SS = 1,
	VOLTAGE_MODE_SS      = 2,
	VOLTAGE_MODE_COUNT   = 3,
};


enum AVFS_VOLTAGE_TYPE_e {
	AVFS_VOLTAGE_GFX   = 0,
	AVFS_VOLTAGE_SOC   = 1,
	AVFS_VOLTAGE_COUNT = 2,
};


//typedef struct dpm_descriptor DpmDescriptor_t;

struct dpm_descriptor {
	uint8_t  VoltageMode;
	uint8_t  SnapToDiscrete;
	uint8_t  NumDiscreteLevels;
	uint8_t  padding;
	struct linear_u32 ConversionToAvfsClk;
	struct quadratic_u32 SsCurve;
};

struct smc_pptable_i2c {
	struct smudpm_i2ccontrollerconfig_t i2ccontroller_vr_gfx;
	struct smudpm_i2ccontrollerconfig_t i2ccontroller_vr_soc;
	struct smudpm_i2ccontrollerconfig_t i2ccontroller_vr_vddci;
	struct smudpm_i2ccontrollerconfig_t i2ccontroller_vr_mvdd;
	struct smudpm_i2ccontrollerconfig_t i2ccontroller_liquid_0;
	struct smudpm_i2ccontrollerconfig_t i2ccontroller_liquid_1;
	struct smudpm_i2ccontrollerconfig_t i2ccontroller_plx;
};

//typedef struct smc_pptable PPTable_t;
struct smc_pptable {
	uint32_t Version; //doesn't seem to be atom_common_table_header.

	union powerplay_features features;


	uint16_t SocketPowerLimitAc0;
	uint16_t SocketPowerLimitAc0Tau;
	uint16_t SocketPowerLimitAc1;
	uint16_t SocketPowerLimitAc1Tau;
	uint16_t SocketPowerLimitAc2;
	uint16_t SocketPowerLimitAc2Tau;
	uint16_t SocketPowerLimitAc3;
	uint16_t SocketPowerLimitAc3Tau;
	uint16_t SocketPowerLimitDc;
	uint16_t SocketPowerLimitDcTau;
	uint16_t TdcLimitSoc;
	uint16_t TdcLimitSocTau;
	uint16_t TdcLimitGfx;
	uint16_t TdcLimitGfxTau;

	uint16_t TedgeLimit;
	uint16_t ThotspotLimit;
	uint16_t ThbmLimit;
	uint16_t Tvr_gfxLimit;
	uint16_t Tvr_memLimit;
	uint16_t Tliquid1Limit;
	uint16_t Tliquid2Limit;
	uint16_t TplxLimit;
	uint32_t FitLimit;

	uint16_t PpmPowerLimit;
	uint16_t PpmTemperatureThreshold;

	uint8_t  MemoryOnPackage;
	uint8_t  padding8_limits;
	uint16_t Tvr_SocLimit;

	uint16_t  UlvVoltageOffsetSoc;
	uint16_t  UlvVoltageOffsetGfx;

	uint8_t  UlvSmnclkDid;
	uint8_t  UlvMp1clkDid;
	uint8_t  UlvGfxclkBypass;
	uint8_t  Padding234;


	uint16_t MinVoltageGfx;
	uint16_t MinVoltageSoc;
	uint16_t MaxVoltageGfx;
	uint16_t MaxVoltageSoc;

	uint16_t LoadLineResistanceGfx;
	uint16_t LoadLineResistanceSoc;

	struct dpm_descriptor DpmDescriptor[PPCLK_COUNT];

	uint16_t FreqTableGfx[NUM_GFXCLK_DPM_LEVELS];
	uint16_t FreqTableVclk[NUM_VCLK_DPM_LEVELS];
	uint16_t FreqTableDclk[NUM_DCLK_DPM_LEVELS];
	uint16_t FreqTableEclk[NUM_ECLK_DPM_LEVELS];
	uint16_t FreqTableSocclk[NUM_SOCCLK_DPM_LEVELS];
	uint16_t FreqTableUclk[NUM_UCLK_DPM_LEVELS];
	uint16_t FreqTableFclk[NUM_FCLK_DPM_LEVELS];
	uint16_t FreqTableDcefclk[NUM_DCEFCLK_DPM_LEVELS];
	uint16_t FreqTableDispclk[NUM_DISPCLK_DPM_LEVELS];
	uint16_t FreqTablePixclk[NUM_PIXCLK_DPM_LEVELS];
	uint16_t FreqTablePhyclk[NUM_PHYCLK_DPM_LEVELS];

	uint16_t DcModeMaxFreq[PPCLK_COUNT];
	uint16_t Padding8_Clks;

	uint16_t Mp0clkFreq[NUM_MP0CLK_DPM_LEVELS];
	uint16_t Mp0DpmVoltage[NUM_MP0CLK_DPM_LEVELS];


	uint16_t GfxclkFidle;
	uint16_t GfxclkSlewRate;
	uint16_t CksEnableFreq;
	uint16_t Padding789;
	struct quadratic_u32 CksVoltageOffset;
	uint8_t  Padding567[4];
	uint16_t GfxclkDsMaxFreq;
	uint8_t  GfxclkSource;
	uint8_t  Padding456;

	uint8_t  LowestUclkReservedForUlv;
	uint8_t  Padding8_Uclk[3];


	uint8_t  PcieGenSpeed[NUM_LINK_LEVELS];
	uint8_t  PcieLaneCount[NUM_LINK_LEVELS];
	uint16_t LclkFreq[NUM_LINK_LEVELS];


	uint16_t EnableTdpm;
	uint16_t TdpmHighHystTemperature;
	uint16_t TdpmLowHystTemperature;
	uint16_t GfxclkFreqHighTempLimit;


	uint16_t FanStopTemp;
	uint16_t FanStartTemp;

	uint16_t FanGainEdge;
	uint16_t FanGainHotspot;
	uint16_t FanGainLiquid;
	uint16_t FanGainVrGfx;
	uint16_t FanGainVrSoc;
	uint16_t FanGainPlx;
	uint16_t FanGainHbm;
	uint16_t FanPwmMin;
	uint16_t FanAcousticLimitRpm;
	uint16_t FanThrottlingRpm;
	uint16_t FanMaximumRpm;
	uint16_t FanTargetTemperature;
	uint16_t FanTargetGfxclk;
	uint8_t  FanZeroRpmEnable;
	uint8_t  FanTachEdgePerRev;



	int16_t  FuzzyFan_ErrorSetDelta;
	int16_t  FuzzyFan_ErrorRateSetDelta;
	int16_t  FuzzyFan_PwmSetDelta;
	uint16_t FuzzyFan_Reserved;

	uint8_t  OverrideAvfsGbGfx;
	uint8_t  OverrideAvfsGbSoc;

	uint8_t  Padding8_Avfs[2];

	struct quadratic_u32 qAvfsGbGfx;
	struct quadratic_u32 qAvfsGbSoc;

	struct droop_u32  dBtcGbGfxCksOn;
	struct droop_u32  dBtcGbGfxCksOff;
	struct droop_u32  dBtcGbGfxAfll;
	struct droop_u32  dBtcGbSoc;
	struct linear_u32 qAgingGbGfx;
	struct linear_u32 qAgingGbSoc;


	struct quadratic_u32 qStaticVoltageOffsetGfx;
	struct quadratic_u32 qStaticVoltageOffsetSoc;


	uint16_t DcTolGfx;
	uint16_t DcTolSoc;


	uint8_t  DcBtcEnabledGfx;
	uint8_t  DcBtcEnabledSoc;

	uint8_t  Padding8_GfxBtc[2];

	int16_t  DcBtcMinGfx;
	int16_t  DcBtcMinSoc;

	uint16_t DcBtcMaxGfx;
	uint16_t DcBtcMaxSoc;

	uint8_t  XgmiLinkSpeed[NUM_XGMI_LEVELS];
	uint8_t  XgmiLinkWidth[NUM_XGMI_LEVELS];
	uint16_t XgmiFclkFreq[NUM_XGMI_LEVELS];
	uint16_t XgmiUclkFreq[NUM_XGMI_LEVELS];
	uint16_t XgmiSocclkFreq[NUM_XGMI_LEVELS];
	uint16_t XgmiSocVoltage[NUM_XGMI_LEVELS];

	uint32_t DebugOverrides;
	struct quadratic_u32 ReservedEquation0;
	struct quadratic_u32 ReservedEquation1;
	struct quadratic_u32 ReservedEquation2;
	struct quadratic_u32 ReservedEquation3;

	uint16_t MinVoltageUlvGfx;
	uint16_t MinVoltageUlvSoc;

	uint16_t MGpuFanBoostLimitRpm;
	uint16_t padding16_Fan;

	uint16_t FanGainVrMem0;
	uint16_t FanGainVrMem1;

	uint16_t DcBtcGbGfx;
	uint16_t DcBtcGbSoc;


	uint32_t Reserved[11];

	uint32_t Padding32[3];

	uint16_t MaxVoltageStepGfx;
	uint16_t MaxVoltageStepSoc;

	uint8_t  VddGfxVrMapping;
	uint8_t  VddSocVrMapping;
	uint8_t  VddMem0VrMapping;
	uint8_t  VddMem1VrMapping;

	uint8_t  GfxUlvPhaseSheddingMask;
	uint8_t  SocUlvPhaseSheddingMask;
	uint8_t  ExternalSensorPresent;
	uint8_t  Padding8_V;


	uint16_t GfxMaxCurrent;
	int8_t   GfxOffset;
	uint8_t  Padding_TelemetryGfx;

	uint16_t SocMaxCurrent;
	int8_t   SocOffset;
	uint8_t  Padding_TelemetrySoc;

	uint16_t Mem0MaxCurrent;
	int8_t   Mem0Offset;
	uint8_t  Padding_TelemetryMem0;

	uint16_t Mem1MaxCurrent;
	int8_t   Mem1Offset;
	uint8_t  Padding_TelemetryMem1;


	uint8_t  AcDcGpio;
	uint8_t  AcDcPolarity;
	uint8_t  VR0HotGpio;
	uint8_t  VR0HotPolarity;

	uint8_t  VR1HotGpio;
	uint8_t  VR1HotPolarity;
	uint8_t  Padding1;
	uint8_t  Padding2;



	uint8_t  LedPin0;
	uint8_t  LedPin1;
	uint8_t  LedPin2;
	uint8_t  padding8_4;


	uint8_t  PllGfxclkSpreadEnabled;
	uint8_t  PllGfxclkSpreadPercent;
	uint16_t PllGfxclkSpreadFreq;

	uint8_t  UclkSpreadEnabled;
	uint8_t  UclkSpreadPercent;
	uint16_t UclkSpreadFreq;

	uint8_t  FclkSpreadEnabled;
	uint8_t  FclkSpreadPercent;
	uint16_t FclkSpreadFreq;

	uint8_t  FllGfxclkSpreadEnabled;
	uint8_t  FllGfxclkSpreadPercent;
	uint16_t FllGfxclkSpreadFreq;

	//struct smudpm_i2ccontrollerconfig_t I2cControllers[I2C_CONTROLLER_NAME_COUNT];
	struct smc_pptable_i2c I2cControllers;

	uint32_t BoardReserved[10];
	//AMD.RX5700.8192.190616.rom: smc_dpm_info v4_5 starts at BoardReserved[2]
	//sizeof(smu_11_0_powerplay_table) == 1738; header reports 1674
	//(1738 - (8*4 + 8*4)) == 1674


	uint32_t MmHubPadding[8];
};
/*
// likely only driver-side tables ahead


typedef struct {

	uint16_t     GfxclkAverageLpfTau;
	uint16_t     SocclkAverageLpfTau;
	uint16_t     UclkAverageLpfTau;
	uint16_t     GfxActivityLpfTau;
	uint16_t     UclkActivityLpfTau;
	uint16_t     SocketPowerLpfTau;


	uint32_t     MmHubPadding[8];
} DriverSmuConfig_t;

typedef struct {

	uint16_t      GfxclkFmin;
	uint16_t      GfxclkFmax;
	uint16_t      GfxclkFreq1;
	uint16_t      GfxclkVolt1;
	uint16_t      GfxclkFreq2;
	uint16_t      GfxclkVolt2;
	uint16_t      GfxclkFreq3;
	uint16_t      GfxclkVolt3;
	uint16_t      UclkFmax;
	int16_t       OverDrivePct;
	uint16_t      FanMaximumRpm;
	uint16_t      FanMinimumPwm;
	uint16_t      FanTargetTemperature;
	uint16_t      MaxOpTemp;
	uint16_t      FanZeroRpmEnable;
	uint16_t      Padding;

} OverDriveTable_t;

typedef struct {
	uint16_t CurrClock[PPCLK_COUNT];
	uint16_t AverageGfxclkFrequency;
	uint16_t AverageSocclkFrequency;
	uint16_t AverageUclkFrequency;
	uint16_t AverageGfxActivity;
	uint16_t AverageUclkActivity;
	uint8_t  CurrSocVoltageOffset;
	uint8_t  CurrGfxVoltageOffset;
	uint8_t  CurrMemVidOffset;
	uint8_t  Padding8;
	uint16_t CurrSocketPower;
	uint16_t TemperatureEdge;
	uint16_t TemperatureHotspot;
	uint16_t TemperatureHBM;
	uint16_t TemperatureVrGfx;
	uint16_t TemperatureVrSoc;
	uint16_t TemperatureVrMem0;
	uint16_t TemperatureVrMem1;
	uint16_t TemperatureLiquid;
	uint16_t TemperaturePlx;
	uint32_t ThrottlerStatus;

	uint8_t  LinkDpmLevel;
	uint16_t AverageSocketPower;
	uint8_t  Padding;


	uint32_t     MmHubPadding[7];
} SmuMetrics_t;

typedef struct {
	uint16_t MinClock;
	uint16_t MaxClock;
	uint16_t MinUclk;
	uint16_t MaxUclk;

	uint8_t  WmSetting;
	uint8_t  Padding[3];
} WatermarkRowGeneric_t;

#define NUM_WM_RANGES 4

typedef enum {
	WM_SOCCLK = 0,
	WM_DCEFCLK,
	WM_COUNT_PP,
} WM_CLOCK_e;

typedef struct {

	WatermarkRowGeneric_t WatermarkRow[WM_COUNT_PP][NUM_WM_RANGES];

	uint32_t     MmHubPadding[7];
} Watermarks_t;

typedef struct {
	uint16_t avgPsmCount[45];
	uint16_t minPsmCount[45];
	float    avgPsmVoltage[45];
	float    minPsmVoltage[45];

	uint16_t avgScsPsmCount;
	uint16_t minScsPsmCount;
	float    avgScsPsmVoltage;
	float    minScsPsmVoltage;


	uint32_t MmHubPadding[6];
} AvfsDebugTable_t;

typedef struct {
	uint8_t  AvfsVersion;
	uint8_t  AvfsEn[AVFS_VOLTAGE_COUNT];

	uint8_t  OverrideVFT[AVFS_VOLTAGE_COUNT];
	uint8_t  OverrideAvfsGb[AVFS_VOLTAGE_COUNT];

	uint8_t  OverrideTemperatures[AVFS_VOLTAGE_COUNT];
	uint8_t  OverrideVInversion[AVFS_VOLTAGE_COUNT];
	uint8_t  OverrideP2V[AVFS_VOLTAGE_COUNT];
	uint8_t  OverrideP2VCharzFreq[AVFS_VOLTAGE_COUNT];

	int32_t VFT0_m1[AVFS_VOLTAGE_COUNT];
	int32_t VFT0_m2[AVFS_VOLTAGE_COUNT];
	int32_t VFT0_b[AVFS_VOLTAGE_COUNT];

	int32_t VFT1_m1[AVFS_VOLTAGE_COUNT];
	int32_t VFT1_m2[AVFS_VOLTAGE_COUNT];
	int32_t VFT1_b[AVFS_VOLTAGE_COUNT];

	int32_t VFT2_m1[AVFS_VOLTAGE_COUNT];
	int32_t VFT2_m2[AVFS_VOLTAGE_COUNT];
	int32_t VFT2_b[AVFS_VOLTAGE_COUNT];

	int32_t AvfsGb0_m1[AVFS_VOLTAGE_COUNT];
	int32_t AvfsGb0_m2[AVFS_VOLTAGE_COUNT];
	int32_t AvfsGb0_b[AVFS_VOLTAGE_COUNT];

	int32_t AcBtcGb_m1[AVFS_VOLTAGE_COUNT];
	int32_t AcBtcGb_m2[AVFS_VOLTAGE_COUNT];
	int32_t AcBtcGb_b[AVFS_VOLTAGE_COUNT];

	uint32_t AvfsTempCold[AVFS_VOLTAGE_COUNT];
	uint32_t AvfsTempMid[AVFS_VOLTAGE_COUNT];
	uint32_t AvfsTempHot[AVFS_VOLTAGE_COUNT];

	uint32_t VInversion[AVFS_VOLTAGE_COUNT];


	int32_t P2V_m1[AVFS_VOLTAGE_COUNT];
	int32_t P2V_m2[AVFS_VOLTAGE_COUNT];
	int32_t P2V_b[AVFS_VOLTAGE_COUNT];

	uint32_t P2VCharzFreq[AVFS_VOLTAGE_COUNT];

	uint32_t EnabledAvfsModules;

	uint32_t MmHubPadding[7];
} AvfsFuseOverride_t;

typedef struct {
	uint8_t   Gfx_ActiveHystLimit;
	uint8_t   Gfx_IdleHystLimit;
	uint8_t   Gfx_FPS;
	uint8_t   Gfx_MinActiveFreqType;
	uint8_t   Gfx_BoosterFreqType;
	uint8_t   Gfx_UseRlcBusy;
	uint16_t  Gfx_MinActiveFreq;
	uint16_t  Gfx_BoosterFreq;
	uint16_t  Gfx_PD_Data_time_constant;
	uint32_t  Gfx_PD_Data_limit_a;
	uint32_t  Gfx_PD_Data_limit_b;
	uint32_t  Gfx_PD_Data_limit_c;
	uint32_t  Gfx_PD_Data_error_coeff;
	uint32_t  Gfx_PD_Data_error_rate_coeff;

	uint8_t   Soc_ActiveHystLimit;
	uint8_t   Soc_IdleHystLimit;
	uint8_t   Soc_FPS;
	uint8_t   Soc_MinActiveFreqType;
	uint8_t   Soc_BoosterFreqType;
	uint8_t   Soc_UseRlcBusy;
	uint16_t  Soc_MinActiveFreq;
	uint16_t  Soc_BoosterFreq;
	uint16_t  Soc_PD_Data_time_constant;
	uint32_t  Soc_PD_Data_limit_a;
	uint32_t  Soc_PD_Data_limit_b;
	uint32_t  Soc_PD_Data_limit_c;
	uint32_t  Soc_PD_Data_error_coeff;
	uint32_t  Soc_PD_Data_error_rate_coeff;

	uint8_t   Mem_ActiveHystLimit;
	uint8_t   Mem_IdleHystLimit;
	uint8_t   Mem_FPS;
	uint8_t   Mem_MinActiveFreqType;
	uint8_t   Mem_BoosterFreqType;
	uint8_t   Mem_UseRlcBusy;
	uint16_t  Mem_MinActiveFreq;
	uint16_t  Mem_BoosterFreq;
	uint16_t  Mem_PD_Data_time_constant;
	uint32_t  Mem_PD_Data_limit_a;
	uint32_t  Mem_PD_Data_limit_b;
	uint32_t  Mem_PD_Data_limit_c;
	uint32_t  Mem_PD_Data_error_coeff;
	uint32_t  Mem_PD_Data_error_rate_coeff;

	uint8_t   Fclk_ActiveHystLimit;
	uint8_t   Fclk_IdleHystLimit;
	uint8_t   Fclk_FPS;
	uint8_t   Fclk_MinActiveFreqType;
	uint8_t   Fclk_BoosterFreqType;
	uint8_t   Fclk_UseRlcBusy;
	uint16_t  Fclk_MinActiveFreq;
	uint16_t  Fclk_BoosterFreq;
	uint16_t  Fclk_PD_Data_time_constant;
	uint32_t  Fclk_PD_Data_limit_a;
	uint32_t  Fclk_PD_Data_limit_b;
	uint32_t  Fclk_PD_Data_limit_c;
	uint32_t  Fclk_PD_Data_error_coeff;
	uint32_t  Fclk_PD_Data_error_rate_coeff;

} DpmActivityMonitorCoeffInt_t;

#define TABLE_PPTABLE                 0
#define TABLE_WATERMARKS              1
#define TABLE_AVFS                    2
#define TABLE_AVFS_PSM_DEBUG          3
#define TABLE_AVFS_FUSE_OVERRIDE      4
#define TABLE_PMSTATUSLOG             5
#define TABLE_SMU_METRICS             6
#define TABLE_DRIVER_SMU_CONFIG       7
#define TABLE_ACTIVITY_MONITOR_COEFF  8
#define TABLE_OVERDRIVE               9
#define TABLE_COUNT                  10


#define UCLK_SWITCH_SLOW 0
#define UCLK_SWITCH_FAST 1


#define SQ_Enable_MASK 0x1
#define SQ_IR_MASK 0x2
#define SQ_PCC_MASK 0x4
#define SQ_EDC_MASK 0x8

#define TCP_Enable_MASK 0x100
#define TCP_IR_MASK 0x200
#define TCP_PCC_MASK 0x400
#define TCP_EDC_MASK 0x800

#define TD_Enable_MASK 0x10000
#define TD_IR_MASK 0x20000
#define TD_PCC_MASK 0x40000
#define TD_EDC_MASK 0x80000

#define DB_Enable_MASK 0x1000000
#define DB_IR_MASK 0x2000000
#define DB_PCC_MASK 0x4000000
#define DB_EDC_MASK 0x8000000

#define SQ_Enable_SHIFT 0
#define SQ_IR_SHIFT 1
#define SQ_PCC_SHIFT 2
#define SQ_EDC_SHIFT 3

#define TCP_Enable_SHIFT 8
#define TCP_IR_SHIFT 9
#define TCP_PCC_SHIFT 10
#define TCP_EDC_SHIFT 11

#define TD_Enable_SHIFT 16
#define TD_IR_SHIFT 17
#define TD_PCC_SHIFT 18
#define TD_EDC_SHIFT 19

#define DB_Enable_SHIFT 24
#define DB_IR_SHIFT 25
#define DB_PCC_SHIFT 26
#define DB_EDC_SHIFT 27

#define REMOVE_FMAX_MARGIN_BIT     0x0
#define REMOVE_DCTOL_MARGIN_BIT    0x1
#define REMOVE_PLATFORM_MARGIN_BIT 0x2


*/



#pragma pack(pop)
#endif
