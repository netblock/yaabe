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
 *
 */
#ifndef SMU13_DRIVER_IF_SMU_13_0_7_H
#define SMU13_DRIVER_IF_SMU_13_0_7_H

#pragma pack(push, 1) /* BIOS data must use byte aligment*/

// *** IMPORTANT ***
// PMFW TEAM: Always increment the interface version on any change to this file
#define SMU13_0_7_DRIVER_IF_VERSION  0x35

// Increment this version if SkuTable_t or BoardTable_t change
#define PPTABLE_VERSION 0x27

#define NUM_GFXCLK_DPM_LEVELS_SMU13   16
#define NUM_VCLK_DPM_LEVELS_SMU13     8
#define NUM_DCLK_DPM_LEVELS_SMU13     8
//ECLK
#define NUM_MP0CLK_DPM_LEVELS_SMU13   2
#define NUM_SOCCLK_DPM_LEVELS_SMU13   8
#define NUM_UCLK_DPM_LEVELS_SMU13     4
#define NUM_FCLK_DPM_LEVELS_SMU13     8
#define NUM_DCFCLK_DPM_LEVELS_SMU13   8 //DCEF?
#define NUM_DISPCLK_DPM_LEVELS_SMU13  8
//PIXCLK
//PHYCLK
#define NUM_LINK_LEVELS_SMU13         3
//XGMI
#define NUM_DPPCLK_DPM_LEVELS_SMU13   8
#define NUM_DPREFCLK_DPM_LEVELS_SMU13 8
#define NUM_DTBCLK_DPM_LEVELS_SMU13   8
#define NUM_OD_FAN_MAX_POINTS_SMU13   6

/*
// Feature Control Defines
#define FEATURE_FW_DATA_READ_BIT            0
#define FEATURE_DPM_GFXCLK_BIT              1
#define FEATURE_DPM_GFX_POWER_OPTIMIZER_BIT 2
#define FEATURE_DPM_UCLK_BIT                3
#define FEATURE_DPM_FCLK_BIT                4
#define FEATURE_DPM_SOCCLK_BIT              5
#define FEATURE_DPM_MP0CLK_BIT              6
#define FEATURE_DPM_LINK_BIT                7
#define FEATURE_DPM_DCN_BIT                 8
#define FEATURE_VMEMP_SCALING_BIT           9
#define FEATURE_VDDIO_MEM_SCALING_BIT       10
#define FEATURE_DS_GFXCLK_BIT               11
#define FEATURE_DS_SOCCLK_BIT               12
#define FEATURE_DS_FCLK_BIT                 13
#define FEATURE_DS_LCLK_BIT                 14
#define FEATURE_DS_DCFCLK_BIT               15
#define FEATURE_DS_UCLK_BIT                 16
#define FEATURE_GFX_ULV_BIT                 17
#define FEATURE_FW_DSTATE_BIT               18
#define FEATURE_GFXOFF_BIT                  19
#define FEATURE_BACO_BIT                    20
#define FEATURE_MM_DPM_BIT                  21
#define FEATURE_SOC_MPCLK_DS_BIT            22
#define FEATURE_BACO_MPCLK_DS_BIT           23
#define FEATURE_THROTTLERS_BIT              24
#define FEATURE_SMARTSHIFT_BIT              25
#define FEATURE_GTHR_BIT                    26
#define FEATURE_ACDC_BIT                    27
#define FEATURE_VR0HOT_BIT                  28
#define FEATURE_FW_CTF_BIT                  29
#define FEATURE_FAN_CONTROL_BIT             30
#define FEATURE_GFX_DCS_BIT                 31
#define FEATURE_GFX_READ_MARGIN_BIT         32
#define FEATURE_LED_DISPLAY_BIT             33
#define FEATURE_GFXCLK_SPREAD_SPECTRUM_BIT  34
#define FEATURE_OUT_OF_BAND_MONITOR_BIT     35
#define FEATURE_OPTIMIZED_VMIN_BIT          36
#define FEATURE_GFX_IMU_BIT                 37
#define FEATURE_BOOT_TIME_CAL_BIT           38
#define FEATURE_GFX_PCC_DFLL_BIT            39
#define FEATURE_SOC_CG_BIT                  40
#define FEATURE_DF_CSTATE_BIT               41
#define FEATURE_GFX_EDC_BIT                 42
#define FEATURE_BOOT_POWER_OPT_BIT          43
#define FEATURE_CLOCK_POWER_DOWN_BYPASS_BIT 44
#define FEATURE_DS_VCN_BIT                  45
#define FEATURE_BACO_CG_BIT                 46
#define FEATURE_MEM_TEMP_READ_BIT           47
#define FEATURE_ATHUB_MMHUB_PG_BIT          48
#define FEATURE_SOC_PCC_BIT                 49
#define FEATURE_EDC_PWRBRK_BIT              50
#define FEATURE_SPARE_51_BIT                51
#define FEATURE_SPARE_52_BIT                52
#define FEATURE_SPARE_53_BIT                53
#define FEATURE_SPARE_54_BIT                54
#define FEATURE_SPARE_55_BIT                55
#define FEATURE_SPARE_56_BIT                56
#define FEATURE_SPARE_57_BIT                57
#define FEATURE_SPARE_58_BIT                58
#define FEATURE_SPARE_59_BIT                59
#define FEATURE_SPARE_60_BIT                60
#define FEATURE_SPARE_61_BIT                61
#define FEATURE_SPARE_62_BIT                62
#define FEATURE_SPARE_63_BIT                63
#define NUM_FEATURES                        64

#define ALLOWED_FEATURE_CTRL_DEFAULT 0xFFFFFFFFFFFFFFFFULL
#define ALLOWED_FEATURE_CTRL_SCPM ((1 << FEATURE_DPM_GFXCLK_BIT) | \
					(1 << FEATURE_DPM_GFX_POWER_OPTIMIZER_BIT) | \
					(1 << FEATURE_DPM_UCLK_BIT) | \
					(1 << FEATURE_DPM_FCLK_BIT) | \
					(1 << FEATURE_DPM_SOCCLK_BIT) | \
					(1 << FEATURE_DPM_MP0CLK_BIT) | \
					(1 << FEATURE_DPM_LINK_BIT) | \
					(1 << FEATURE_DPM_DCN_BIT) | \
					(1 << FEATURE_DS_GFXCLK_BIT) | \
					(1 << FEATURE_DS_SOCCLK_BIT) | \
					(1 << FEATURE_DS_FCLK_BIT) | \
					(1 << FEATURE_DS_LCLK_BIT) | \
					(1 << FEATURE_DS_DCFCLK_BIT) | \
					(1 << FEATURE_DS_UCLK_BIT) | \
					(1ULL << FEATURE_DS_VCN_BIT))

// For use with feature control messages
enum FEATURE_PWR_DOMAIN_e {
	FEATURE_PWR_ALL,
	FEATURE_PWR_S5,
	FEATURE_PWR_BACO,
	FEATURE_PWR_SOC,
	FEATURE_PWR_GFX,
	FEATURE_PWR_DOMAIN_COUNT,
};
*/
union powerplay_feature_control_smu13 {
    uint64_t feature_control;
    struct { uint64_t
		fw_data_read            :0-0 +1,
		dpm_gfxclk              :1-1 +1,
		dpm_gfx_power_optimizer :2-2 +1,
		dpm_uclk                :3-3 +1,
		dpm_fclk                :4-4 +1,
		dpm_socclk              :5-5 +1,
		dpm_mp0clk              :6-6 +1,
		dpm_link                :7-7 +1,
		dpm_dcn                 :8-8 +1,
		vmemp_scaling           :9-9 +1,
		vddio_mem_scaling      :10-10 +1,
		ds_gfxclk              :11-11 +1,
		ds_socclk              :12-12 +1,
		ds_fclk                :13-13 +1,
		ds_lclk                :14-14 +1,
		ds_dcfclk              :15-15 +1,
		ds_uclk                :16-16 +1,
		gfx_ulv                :17-17 +1,
		fw_dstate              :18-18 +1,
		gfxoff                 :19-19 +1,
		baco                   :20-20 +1,
		mm_dpm                 :21-21 +1,
		soc_mpclk_ds           :22-22 +1,
		baco_mpclk_ds          :23-23 +1,
		throttlers             :24-24 +1,
		smartshift             :25-25 +1,
		gthr                   :26-26 +1,
		acdc                   :27-27 +1,
		vr0hot                 :28-28 +1,
		fw_ctf                 :29-29 +1,
		fan_control            :30-30 +1,
		gfx_dcs                :31-31 +1,
		gfx_read_margin        :32-32 +1,
		led_display            :33-33 +1,
		gfxclk_spread_spectrum :34-34 +1,
		out_of_band_monitor    :35-35 +1,
		optimized_vmin         :36-36 +1,
		gfx_imu                :37-37 +1,
		boot_time_cal          :38-38 +1,
		gfx_pcc_dfll           :39-39 +1,
		soc_cg                 :40-40 +1,
		df_cstate              :41-41 +1,
		gfx_edc                :42-42 +1,
		boot_power_opt         :43-43 +1,
		clock_power_down_bypass:44-44 +1,
		ds_vcn                 :45-45 +1,
		baco_cg                :46-46 +1,
		mem_temp_read          :47-47 +1,
		athub_mmhub_pg         :48-48 +1,
		soc_pcc                :49-49 +1,
		edc_pwrbrk             :50-50 +1,
		spare_51               :51-51 +1,
		spare_52               :52-52 +1,
		spare_53               :53-53 +1,
		spare_54               :54-54 +1,
		spare_55               :55-55 +1,
		spare_56               :56-56 +1,
		spare_57               :57-57 +1,
		spare_58               :58-58 +1,
		spare_59               :59-59 +1,
		spare_60               :60-60 +1,
		spare_61               :61-61 +1,
		spare_62               :62-62 +1,
		spare_63               :63-63 +1;
	};
};


// Debug Overrides Bitmask
/*
#define DEBUG_OVERRIDE_DISABLE_VOLT_LINK_VCN_FCLK   0x00000001
#define DEBUG_OVERRIDE_DISABLE_VOLT_LINK_DCN_FCLK   0x00000002
#define DEBUG_OVERRIDE_DISABLE_VOLT_LINK_MP0_FCLK   0x00000004
#define DEBUG_OVERRIDE_DISABLE_VOLT_LINK_VCN_DCFCLK 0x00000008
#define DEBUG_OVERRIDE_DISABLE_FAST_FCLK_TIMER      0x00000010
#define DEBUG_OVERRIDE_DISABLE_VCN_PG               0x00000020
#define DEBUG_OVERRIDE_DISABLE_FMAX_VMAX            0x00000040
#define DEBUG_OVERRIDE_DISABLE_IMU_FW_CHECKS        0x00000080
#define DEBUG_OVERRIDE_DISABLE_D0i2_REENTRY_HSR_TIMER_CHECK 0x00000100
#define DEBUG_OVERRIDE_DISABLE_DFLL                 0x00000200
#define DEBUG_OVERRIDE_ENABLE_RLC_VF_BRINGUP_MODE   0x00000400
#define DEBUG_OVERRIDE_DFLL_MASTER_MODE             0x00000800
#define DEBUG_OVERRIDE_ENABLE_PROFILING_MODE        0x00001000
*/

union dpm_debug_override_smu13 {
	uint32_t dpm_debug_override_flags;
    struct { uint32_t
		disable_volt_link_vcn_fclk   :0-0 +1,
		disable_volt_link_dcn_fclk   :1-1 +1,
		disable_volt_link_mp0_fclk   :2-2 +1,
		disable_volt_link_vcn_dcfclk :3-3 +1,
		disable_fast_fclk_timer      :4-4 +1,
		disable_vcn_pg               :5-5 +1,
		disable_fmax_vmax            :6-6 +1,
		disable_imu_fw_checks        :7-7 +1,
		disable_d0i2_reentry_hsr_timer_check :8-8 +1,
		disable_dfll                 :9-9 +1,
		enable_rlc_vf_bringup_mode  :10-10 +1,
		dfll_master_mode            :11-11 +1,
		enable_profiling_mode       :12-12 +1,
		reserved                    :31-13 +1;
	};
};


// VR Mapping Bit Defines
#define VR_MAPPING_VR_SELECT_MASK  0x01
#define VR_MAPPING_VR_SELECT_SHIFT 0x00

#define VR_MAPPING_PLANE_SELECT_MASK  0x02
#define VR_MAPPING_PLANE_SELECT_SHIFT 0x01

// PSI Bit Defines
#define PSI_SEL_VR0_PLANE0_PSI0 0x01
#define PSI_SEL_VR0_PLANE0_PSI1 0x02
#define PSI_SEL_VR0_PLANE1_PSI0 0x04
#define PSI_SEL_VR0_PLANE1_PSI1 0x08
#define PSI_SEL_VR1_PLANE0_PSI0 0x10
#define PSI_SEL_VR1_PLANE0_PSI1 0x20
#define PSI_SEL_VR1_PLANE1_PSI0 0x40
#define PSI_SEL_VR1_PLANE1_PSI1 0x80

enum SVI_PSI_e {
	SVI_PSI_0, // Full phase count (default)
	SVI_PSI_1, // Phase count 1st level
	SVI_PSI_2, // Phase count 2nd level
	SVI_PSI_3, // Single phase operation + active diode emulation
	SVI_PSI_4, // Single phase operation + passive diode emulation *optional*
	SVI_PSI_5, // Reserved
	SVI_PSI_6, // Power down to 0V (voltage regulation disabled)
	SVI_PSI_7, // Automated phase shedding and diode emulation
};

// Throttler Control/Status Bits
#define THROTTLER_TEMP_EDGE_BIT      0
#define THROTTLER_TEMP_HOTSPOT_BIT   1
#define THROTTLER_TEMP_HOTSPOT_G_BIT 2
#define THROTTLER_TEMP_HOTSPOT_M_BIT 3
#define THROTTLER_TEMP_MEM_BIT       4
#define THROTTLER_TEMP_VR_GFX_BIT    5
#define THROTTLER_TEMP_VR_MEM0_BIT   6
#define THROTTLER_TEMP_VR_MEM1_BIT   7
#define THROTTLER_TEMP_VR_SOC_BIT    8
#define THROTTLER_TEMP_VR_U_BIT      9
#define THROTTLER_TEMP_LIQUID0_BIT  10
#define THROTTLER_TEMP_LIQUID1_BIT  11
#define THROTTLER_TEMP_PLX_BIT      12
#define THROTTLER_TDC_GFX_BIT       13
#define THROTTLER_TDC_SOC_BIT       14
#define THROTTLER_TDC_U_BIT         15
#define THROTTLER_PPT0_BIT          16
#define THROTTLER_PPT1_BIT          17
#define THROTTLER_PPT2_BIT          18
#define THROTTLER_PPT3_BIT          19
#define THROTTLER_FIT_BIT           20
#define THROTTLER_GFX_APCC_PLUS_BIT 21
#define THROTTLER_COUNT             22

// FW DState Features Control Bits
#define FW_DSTATE_SOC_ULV_BIT           0
#define FW_DSTATE_G6_HSR_BIT            1
#define FW_DSTATE_G6_PHY_VMEMP_OFF_BIT  2
#define FW_DSTATE_SMN_DS_BIT            3
#define FW_DSTATE_MP1_WHISPER_MODE_BIT  4
#define FW_DSTATE_SOC_LIV_MIN_BIT       5
#define FW_DSTATE_SOC_PLL_PWRDN_BIT     6
#define FW_DSTATE_MEM_PLL_PWRDN_BIT     7
#define FW_DSTATE_MALL_ALLOC_BIT        8
#define FW_DSTATE_MEM_PSI_BIT           9
#define FW_DSTATE_HSR_NON_STROBE_BIT    10
#define FW_DSTATE_MP0_ENTER_WFI_BIT     11
#define FW_DSTATE_U_ULV_BIT             12
#define FW_DSTATE_MALL_FLUSH_BIT        13
#define FW_DSTATE_SOC_PSI_BIT           14
#define FW_DSTATE_U_PSI_BIT             15
#define FW_DSTATE_UCP_DS_BIT            16
#define FW_DSTATE_CSRCLK_DS_BIT         17
#define FW_DSTATE_MMHUB_INTERLOCK_BIT   18
#define FW_DSTATE_D0i3_2_QUIET_FW_BIT   19
#define FW_DSTATE_CLDO_PRG_BIT          20
#define FW_DSTATE_DF_PLL_PWRDN_BIT      21
#define FW_DSTATE_U_LOW_PWR_MODE_EN_BIT 22
#define FW_DSTATE_GFX_PSI6_BIT          23
#define FW_DSTATE_GFX_VR_PWR_STAGE_BIT  24

// LED Display Mask & Control Bits
#define LED_DISPLAY_GFX_DPM_BIT 0
#define LED_DISPLAY_PCIE_BIT    1
#define LED_DISPLAY_ERROR_BIT   2


#define MEM_TEMP_READ_OUT_OF_BAND_BIT          0
#define MEM_TEMP_READ_IN_BAND_REFRESH_BIT      1
#define MEM_TEMP_READ_IN_BAND_DUMMY_PSTATE_BIT 2

enum SMARTSHIFT_VERSION_e:uint8_t {
	SMARTSHIFT_VERSION_1 = 0,
	SMARTSHIFT_VERSION_2 = 1,
	SMARTSHIFT_VERSION_3 = 2,
};


enum DRAM_BIT_WIDTH_TYPE_e:uint8_t {
	DRAM_BIT_WIDTH_DISABLED = 0,
	DRAM_BIT_WIDTH_X_8      = 8,
	DRAM_BIT_WIDTH_X_16    = 16,
	DRAM_BIT_WIDTH_X_32    = 32,
	DRAM_BIT_WIDTH_X_64    = 64,
	DRAM_BIT_WIDTH_X_128  = 128,
	DRAM_BIT_WIDTH_COUNT,
};

// I2C Interface
#define NUM_I2C_CONTROLLERS     8

#define I2C_CONTROLLER_ENABLED  1
#define I2C_CONTROLLER_DISABLED 0

#define MAX_SW_I2C_COMMANDS    24
/* duplicate
enum I2cControllerPort_e {
	I2C_CONTROLLER_PORT_0 = 0,  // CKSVII2C0
	I2C_CONTROLLER_PORT_1 = 1,  // CKSVII2C1
	I2C_CONTROLLER_PORT_COUNT,
};

enum I2cControllerName_e {
	I2C_CONTROLLER_NAME_VR_GFX = 0,
	I2C_CONTROLLER_NAME_VR_SOC,
	I2C_CONTROLLER_NAME_VR_VMEMP,
	I2C_CONTROLLER_NAME_VR_VDDIO,
	I2C_CONTROLLER_NAME_LIQUID0,
	I2C_CONTROLLER_NAME_LIQUID1,
	I2C_CONTROLLER_NAME_PLX,
	I2C_CONTROLLER_NAME_FAN_INTAKE,
	I2C_CONTROLLER_NAME_COUNT,
};

enum I2cControllerThrottler_e {
	I2C_CONTROLLER_THROTTLER_TYPE_NONE = 0,
	I2C_CONTROLLER_THROTTLER_VR_GFX,
	I2C_CONTROLLER_THROTTLER_VR_SOC,
	I2C_CONTROLLER_THROTTLER_VR_VMEMP,
	I2C_CONTROLLER_THROTTLER_VR_VDDIO,
	I2C_CONTROLLER_THROTTLER_LIQUID0,
	I2C_CONTROLLER_THROTTLER_LIQUID1,
	I2C_CONTROLLER_THROTTLER_PLX,
	I2C_CONTROLLER_THROTTLER_FAN_INTAKE,
	I2C_CONTROLLER_THROTTLER_INA3221,
	I2C_CONTROLLER_THROTTLER_COUNT,
};

enum I2cControllerProtocol_e {
	I2C_CONTROLLER_PROTOCOL_VR_XPDE132G5,
	I2C_CONTROLLER_PROTOCOL_VR_IR35217,
	I2C_CONTROLLER_PROTOCOL_TMP_MAX31875,
	I2C_CONTROLLER_PROTOCOL_INA3221,
	I2C_CONTROLLER_PROTOCOL_TMP_MAX6604,
	I2C_CONTROLLER_PROTOCOL_COUNT,
};

struct I2cControllerConfig_t {
	uint8_t  Enabled;
	uint8_t  Speed;
	uint8_t  SlaveAddress;
	uint8_t  ControllerPort;
	uint8_t  ControllerName;
	uint8_t  ThermalThrotter;
	uint8_t  I2cProtocol;
	uint8_t  PaddingConfig;
};

enum I2cPort_e {
	I2C_PORT_SVD_SCL = 0,
	I2C_PORT_GPIO,
};

enum I2cSpeed_e {
	I2C_SPEED_FAST_50K = 0, // 50  Kbits/s
	I2C_SPEED_FAST_100K,    // 100 Kbits/s
	I2C_SPEED_FAST_400K,    // 400 Kbits/s
	I2C_SPEED_FAST_PLUS_1M, // 1   Mbits/s (in fast mode)
	I2C_SPEED_HIGH_1M,      // 1   Mbits/s (in high speed mode)
	I2C_SPEED_HIGH_2M,      // 2.3 Mbits/s
	I2C_SPEED_COUNT,
};

enum I2cCmdType_e {
	I2C_CMD_READ = 0,
	I2C_CMD_WRITE,
	I2C_CMD_COUNT,
};
*/


#define CMDCONFIG_STOP_BIT      0
#define CMDCONFIG_RESTART_BIT   1
#define CMDCONFIG_READWRITE_BIT 2 // bit should be 0 for read, 1 for write

#define CMDCONFIG_STOP_MASK      (1 << CMDCONFIG_STOP_BIT)
#define CMDCONFIG_RESTART_MASK   (1 << CMDCONFIG_RESTART_BIT)
#define CMDCONFIG_READWRITE_MASK (1 << CMDCONFIG_READWRITE_BIT)

struct SwI2cCmd_t {
	uint8_t  ReadWriteData;  // Return data for read. Data to send for write
	uint8_t  CmdConfig; // Includes whether associated command should have a stop or restart command, and is a read or write
}; // SW I2C Command Table

struct SwI2cRequest_t {
	uint8_t  I2CcontrollerPort; // CKSVII2C0(0) or //CKSVII2C1(1)
	uint8_t  I2CSpeed;          // Use I2cSpeed_e to indicate speed to select
	uint8_t  SlaveAddress;      // Slave address of device
	uint8_t  NumCmds;           // Number of commands

	struct SwI2cCmd_t SwI2cCmds[MAX_SW_I2C_COMMANDS];
}; // SW I2C Request Table

struct SwI2cRequestExternal_t {
	struct SwI2cRequest_t SwI2cRequest;

	uint32_t Spare[8];
	uint32_t MmHubPadding[8]; // SMU internal use
};

struct EccInfo_t {
	uint64_t mca_umc_status;
	uint64_t mca_umc_addr;

	uint16_t ce_count_lo_chip;
	uint16_t ce_count_hi_chip;

	uint32_t eccPadding;
};

struct EccInfoTable_t {
	struct EccInfo_t  EccInfo[24];
};

// D3HOT sequences
enum D3HOTSequence_e {
	BACO_SEQUENCE        = 0,
	MSR_SEQUENCE         = 1,
	BAMACO_SEQUENCE      = 2,
	ULPS_SEQUENCE        = 3,
	D3HOT_SEQUENCE_COUNT = 4,
};

// This is aligned with RSMU PGFSM Register Mapping
enum PowerGatingMode_e {
	PG_DYNAMIC_MODE = 0,
	PG_STATIC_MODE  = 1,
};

// This is aligned with RSMU PGFSM Register Mapping
enum PowerGatingSettings_e {
	PG_POWER_DOWN = 0,
	PG_POWER_UP   = 1,
};

/* duplicate
struct quadratic_u32 {
	uint32_t a;  // store in IEEE float format in this variable
	uint32_t b;  // store in IEEE float format in this variable
	uint32_t c;  // store in IEEE float format in this variable
};

struct linear_u32 {
	uint32_t m;  // store in IEEE float format in this variable
	uint32_t b;  // store in IEEE float format in this variable
};

struct droop_u32 {
	uint32_t a;  // store in IEEE float format in this variable
	uint32_t b;  // store in IEEE float format in this variable
	uint32_t c;  // store in IEEE float format in this variable
};
*/

enum DCS_ARCH_e {
	DCS_ARCH_DISABLED = 0,
	DCS_ARCH_FADCS    = 1,
	DCS_ARCH_ASYNC    = 2,
};

// Only Clks that have DPM descriptors are listed here
enum PPCLK_SMU13_e {
	PPCLK_SMU13_GFXCLK   = 0,
	PPCLK_SMU13_SOCCLK   = 1,
	PPCLK_SMU13_UCLK     = 2,
	PPCLK_SMU13_FCLK     = 3,
	PPCLK_SMU13_DCLK_0   = 4,
	PPCLK_SMU13_VCLK_0   = 5,
	PPCLK_SMU13_DCLK_1   = 6,
	PPCLK_SMU13_VCLK_1   = 7,
	PPCLK_SMU13_DISPCLK  = 8,
	PPCLK_SMU13_DPPCLK   = 9,
	PPCLK_SMU13_DPREFCLK = 10,
	PPCLK_SMU13_DCFCLK   = 11,
	PPCLK_SMU13_DTBCLK   = 12,
	PPCLK_SMU13_COUNT    = 13,
};

/* duplicate
enum VOLTAGE_MODE_e { // seemingly uneeded
	VOLTAGE_MODE_PPTABLE = 0,
	VOLTAGE_MODE_FUSES   = 1,
	VOLTAGE_MODE_COUNT   = 2,
};

enum AVFS_VOLTAGE_TYPE_e {
	AVFS_VOLTAGE_GFX   = 0,
	AVFS_VOLTAGE_SOC   = 1,
	AVFS_VOLTAGE_COUNT = 2,
};
*/

enum AVFS_TEMP_e {
	AVFS_TEMP_COLD  = 0,
	AVFS_TEMP_HOT   = 1,
	AVFS_TEMP_COUNT = 2,
};

enum AVFS_D_e {
	AVFS_D_G     = 0,
	AVFS_D_M_B   = 1,
	AVFS_D_M_S   = 2,
	AVFS_D_COUNT = 3,
};

enum UCLK_DIV_e {
	UCLK_DIV_BY_1 = 0,
	UCLK_DIV_BY_2 = 1,
	UCLK_DIV_BY_4 = 2,
	UCLK_DIV_BY_8 = 3,
};

enum GpioIntPolarity_e {
	GPIO_INT_POLARITY_ACTIVE_LOW  = 0,
	GPIO_INT_POLARITY_ACTIVE_HIGH = 1,
};

enum PwrConfig_e:uint8_t {
	PWR_CONFIG_TDP = 0,
	PWR_CONFIG_TGP = 1,
	PWR_CONFIG_TCP_ESTIMATED = 2,
	PWR_CONFIG_TCP_MEASURED  = 3,
};

enum FOPT_CALC_e:uint8_t {
	FOPT_CALC_AC_CALC_DC       = 0,
	FOPT_PPTABLE_AC_CALC_DC    = 1,
	FOPT_CALC_AC_PPTABLE_DC    = 2,
	FOPT_PPTABLE_AC_PPTABLE_DC = 3,
};

struct DpmDescriptor_t {
	uint8_t  Padding;
	uint8_t  SnapToDiscrete;    // 0 - Fine grained DPM, 1 - Discrete DPM
	uint8_t  NumDiscreteLevels; // Set to 2 (Fmin, Fmax) when using fine grained DPM, otherwise set to # discrete levels used
	enum FOPT_CALC_e CalculateFopt;     // Indication whether FW should calculate Fopt or use values below. Reference FOPT_CALC_e
	struct linear_u32 ConversionToAvfsClk; // Transfer function to AVFS Clock (GHz->GHz)
	uint32_t Padding3[3];
	uint16_t Padding4;
	uint16_t FoptimalDc; // Foptimal frequency in DC power mode.
	uint16_t FoptimalAc; // Foptimal frequency in AC power mode.
	uint16_t Padding2;
};

enum PPT_THROTTLER_e {
	PPT_THROTTLER_PPT0  = 0,
	PPT_THROTTLER_PPT1  = 1,
	PPT_THROTTLER_PPT2  = 2,
	PPT_THROTTLER_PPT3  = 3,
	PPT_THROTTLER_COUNT = 4,
};

enum TEMP_e {
	TEMP_EDGE      = 0,
	TEMP_HOTSPOT   = 1,
	TEMP_HOTSPOT_G = 2,
	TEMP_HOTSPOT_M = 3,
	TEMP_MEM       = 4,
	TEMP_VR_GFX    = 5,
	TEMP_VR_MEM0   = 6,
	TEMP_VR_MEM1   = 7,
	TEMP_VR_SOC    = 8,
	TEMP_VR_U      = 9,
	TEMP_LIQUID0   = 10,
	TEMP_LIQUID1   = 11,
	TEMP_PLX       = 12,
	TEMP_COUNT     = 13,
};

enum TDC_THROTTLER_e {
	TDC_THROTTLER_GFX   = 0,
	TDC_THROTTLER_SOC   = 1,
	TDC_THROTTLER_U     = 2,
	TDC_THROTTLER_COUNT = 3,
};

enum SVI_PLANE_e {
	SVI_PLANE_GFX       = 0,
	SVI_PLANE_SOC       = 1,
	SVI_PLANE_VMEMP     = 2,
	SVI_PLANE_VDDIO_MEM = 3,
	SVI_PLANE_U         = 4,
	SVI_PLANE_COUNT     = 5,
};

enum PMFW_VOLT_PLANE_e {
	PMFW_VOLT_PLANE_GFX   = 0,
	PMFW_VOLT_PLANE_SOC   = 1,
	PMFW_VOLT_PLANE_COUNT = 2,
};

enum CUSTOMER_VARIANT_e:uint8_t {
	CUSTOMER_VARIANT_ROW    = 0,
	CUSTOMER_VARIANT_FALCON = 1,
	CUSTOMER_VARIANT_COUNT  = 2,
};

/* duplicate
enum POWER_SOURCE_e {
	POWER_SOURCE_AC    = 0,
	POWER_SOURCE_DC    = 1,
	POWER_SOURCE_COUNT = 2,
};
*/

enum MEM_VENDOR_e {
	MEM_VENDOR_SAMSUNG      = 0,
	MEM_VENDOR_INFINEON     = 1,
	MEM_VENDOR_ELPIDA       = 2,
	MEM_VENDOR_ETRON        = 3,
	MEM_VENDOR_NANYA        = 4,
	MEM_VENDOR_HYNIX        = 5,
	MEM_VENDOR_MOSEL        = 6,
	MEM_VENDOR_WINBOND      = 7,
	MEM_VENDOR_ESMT         = 8,
	MEM_VENDOR_PLACEHOLDER0 = 9,
	MEM_VENDOR_PLACEHOLDER1 = 10,
	MEM_VENDOR_PLACEHOLDER2 = 11,
	MEM_VENDOR_PLACEHOLDER3 = 12,
	MEM_VENDOR_PLACEHOLDER4 = 13,
	MEM_VENDOR_PLACEHOLDER5 = 14,
	MEM_VENDOR_MICRON       = 15,
	MEM_VENDOR_COUNT        = 16,
};

enum PP_GRTAVFS_HW_FUSE_e {
	PP_GRTAVFS_HW_CPO_CTL_ZONE0        = 0,
	PP_GRTAVFS_HW_CPO_CTL_ZONE1        = 1,
	PP_GRTAVFS_HW_CPO_CTL_ZONE2        = 2,
	PP_GRTAVFS_HW_CPO_CTL_ZONE3        = 3,
	PP_GRTAVFS_HW_CPO_CTL_ZONE4        = 4,
	PP_GRTAVFS_HW_CPO_EN_0_31_ZONE0    = 5,
	PP_GRTAVFS_HW_CPO_EN_32_63_ZONE0   = 6,
	PP_GRTAVFS_HW_CPO_EN_0_31_ZONE1    = 7,
	PP_GRTAVFS_HW_CPO_EN_32_63_ZONE1   = 8,
	PP_GRTAVFS_HW_CPO_EN_0_31_ZONE2    = 9,
	PP_GRTAVFS_HW_CPO_EN_32_63_ZONE2   = 10,
	PP_GRTAVFS_HW_CPO_EN_0_31_ZONE3    = 11,
	PP_GRTAVFS_HW_CPO_EN_32_63_ZONE3   = 12,
	PP_GRTAVFS_HW_CPO_EN_0_31_ZONE4    = 13,
	PP_GRTAVFS_HW_CPO_EN_32_63_ZONE4   = 14,
	PP_GRTAVFS_HW_ZONE0_VF             = 15,
	PP_GRTAVFS_HW_ZONE1_VF1            = 16,
	PP_GRTAVFS_HW_ZONE2_VF2            = 17,
	PP_GRTAVFS_HW_ZONE3_VF3            = 18,
	PP_GRTAVFS_HW_VOLTAGE_GB           = 19,
	PP_GRTAVFS_HW_CPOSCALINGCTRL_ZONE0 = 20,
	PP_GRTAVFS_HW_CPOSCALINGCTRL_ZONE1 = 21,
	PP_GRTAVFS_HW_CPOSCALINGCTRL_ZONE2 = 22,
	PP_GRTAVFS_HW_CPOSCALINGCTRL_ZONE3 = 23,
	PP_GRTAVFS_HW_CPOSCALINGCTRL_ZONE4 = 24,
	PP_GRTAVFS_HW_RESERVED_0           = 25,
	PP_GRTAVFS_HW_RESERVED_1           = 26,
	PP_GRTAVFS_HW_RESERVED_2           = 27,
	PP_GRTAVFS_HW_RESERVED_3           = 28,
	PP_GRTAVFS_HW_RESERVED_4           = 29,
	PP_GRTAVFS_HW_RESERVED_5           = 30,
	PP_GRTAVFS_HW_RESERVED_6           = 31,
	PP_GRTAVFS_HW_FUSE_COUNT           = 32,
};

enum PP_GRTAVFS_FW_COMMON_FUSE_e {
	PP_GRTAVFS_FW_COMMON_PPVMIN_Z1_HOT_T0  = 0,
	PP_GRTAVFS_FW_COMMON_PPVMIN_Z1_COLD_T0 = 1,
	PP_GRTAVFS_FW_COMMON_PPVMIN_Z2_HOT_T0  = 2,
	PP_GRTAVFS_FW_COMMON_PPVMIN_Z2_COLD_T0 = 3,
	PP_GRTAVFS_FW_COMMON_PPVMIN_Z3_HOT_T0  = 4,
	PP_GRTAVFS_FW_COMMON_PPVMIN_Z3_COLD_T0 = 5,
	PP_GRTAVFS_FW_COMMON_PPVMIN_Z4_HOT_T0  = 6,
	PP_GRTAVFS_FW_COMMON_PPVMIN_Z4_COLD_T0 = 7,
	PP_GRTAVFS_FW_COMMON_SRAM_RM_Z0        = 8,
	PP_GRTAVFS_FW_COMMON_SRAM_RM_Z1        = 9,
	PP_GRTAVFS_FW_COMMON_SRAM_RM_Z2        = 10,
	PP_GRTAVFS_FW_COMMON_SRAM_RM_Z3        = 11,
	PP_GRTAVFS_FW_COMMON_SRAM_RM_Z4        = 12,
	PP_GRTAVFS_FW_COMMON_FUSE_COUNT        = 13,
};

enum PP_GRTAVFS_FW_SEP_FUSE_e {
	PP_GRTAVFS_FW_SEP_FUSE_GB1_PWL_VOLTAGE_NEG_1       = 0,
	PP_GRTAVFS_FW_SEP_FUSE_GB1_PWL_VOLTAGE_0           = 1,
	PP_GRTAVFS_FW_SEP_FUSE_GB1_PWL_VOLTAGE_1           = 2,
	PP_GRTAVFS_FW_SEP_FUSE_GB1_PWL_VOLTAGE_2           = 3,
	PP_GRTAVFS_FW_SEP_FUSE_GB1_PWL_VOLTAGE_3           = 4,
	PP_GRTAVFS_FW_SEP_FUSE_GB1_PWL_VOLTAGE_4           = 5,
	PP_GRTAVFS_FW_SEP_FUSE_GB2_PWL_VOLTAGE_NEG_1       = 6,
	PP_GRTAVFS_FW_SEP_FUSE_GB2_PWL_VOLTAGE_0           = 7,
	PP_GRTAVFS_FW_SEP_FUSE_GB2_PWL_VOLTAGE_1           = 8,
	PP_GRTAVFS_FW_SEP_FUSE_GB2_PWL_VOLTAGE_2           = 9,
	PP_GRTAVFS_FW_SEP_FUSE_GB2_PWL_VOLTAGE_3           = 10,
	PP_GRTAVFS_FW_SEP_FUSE_GB2_PWL_VOLTAGE_4           = 11,
	PP_GRTAVFS_FW_SEP_FUSE_VF_NEG_1_FREQUENCY          = 12,
	PP_GRTAVFS_FW_SEP_FUSE_VF4_FREQUENCY               = 13,
	PP_GRTAVFS_FW_SEP_FUSE_FREQUENCY_TO_COUNT_SCALER_0 = 14,
	PP_GRTAVFS_FW_SEP_FUSE_FREQUENCY_TO_COUNT_SCALER_1 = 15,
	PP_GRTAVFS_FW_SEP_FUSE_FREQUENCY_TO_COUNT_SCALER_2 = 16,
	PP_GRTAVFS_FW_SEP_FUSE_FREQUENCY_TO_COUNT_SCALER_3 = 17,
	PP_GRTAVFS_FW_SEP_FUSE_FREQUENCY_TO_COUNT_SCALER_4 = 18,
	PP_GRTAVFS_FW_SEP_FUSE_COUNT                       = 19,
};


#define PP_NUM_RTAVFS_PWL_ZONES 5



// VBIOS or PPLIB configures telemetry slope and offset. Only slope expected to be set for SVI3
// Slope Q1.7, Offset Q1.2
struct SviTelemetryScale_t {
	int8_t   Offset; // in Amps
	uint8_t  Padding;
	uint16_t MaxCurrent; // in Amps
};

#define PP_NUM_OD_VF_CURVE_POINTS PP_NUM_RTAVFS_PWL_ZONES + 1


#define PP_OD_FEATURE_GFX_VF_CURVE_BIT 0
#define PP_OD_FEATURE_PPT_BIT          2
#define PP_OD_FEATURE_FAN_CURVE_BIT    3
#define PP_OD_FEATURE_GFXCLK_BIT       7
#define PP_OD_FEATURE_UCLK_BIT         8
#define PP_OD_FEATURE_ZERO_FAN_BIT     9
#define PP_OD_FEATURE_TEMPERATURE_BIT 10
#define PP_OD_FEATURE_COUNT           13

enum PP_OD_POWER_FEATURE_e {
	PP_OD_POWER_FEATURE_ALWAYS_ENABLED = 0,
	PP_OD_POWER_FEATURE_DISABLED_WHILE_GAMING = 1,
	PP_OD_POWER_FEATURE_ALWAYS_DISABLED = 2,
};

enum FanMode_e {
	FAN_MODE_AUTO = 0,
	FAN_MODE_MANUAL_LINEAR = 1,
};

struct OverDriveTable_t {
	uint32_t FeatureCtrlMask;

	// Voltage control
	int16_t VoltageOffsetPerZoneBoundary[PP_NUM_OD_VF_CURVE_POINTS];

	uint32_t Reserved;

	// Frequency changes
	int16_t GfxclkFmin; // MHz
	int16_t GfxclkFmax; // MHz
	uint16_t UclkFmin;  // MHz
	uint16_t UclkFmax;  // MHz

	// PPT
	int16_t Ppt; // %
	int16_t Tdc;

	// Fan control
	uint8_t  FanLinearPwmPoints[NUM_OD_FAN_MAX_POINTS_SMU13];
	uint8_t  FanLinearTempPoints[NUM_OD_FAN_MAX_POINTS_SMU13];
	uint16_t FanMinimumPwm;
	uint16_t AcousticTargetRpmThreshold;
	uint16_t AcousticLimitRpmThreshold;
	uint16_t FanTargetTemperature; // Degree Celcius
	uint8_t  FanZeroRpmEnable;
	uint8_t  FanZeroRpmStopTemp;
	uint8_t  FanMode;
	uint8_t  MaxOpTemp;
	uint8_t  Padding[4];

	uint32_t Spare[12];
	uint32_t MmHubPadding[8]; // SMU internal use. Adding here instead of external as a workaround
};

/*
struct OverDriveTableExternal_t {
	OverDriveTable_t OverDriveTable;

};
*/

struct overdrivelimits_smu13 {
	uint32_t FeatureCtrlMask;

	int16_t VoltageOffsetPerZoneBoundary;
	uint16_t Reserved1;

	uint16_t Reserved2;

	int16_t GfxclkFmin; // MHz
	int16_t GfxclkFmax; // MHz
	uint16_t UclkFmin;  // MHz
	uint16_t UclkFmax;  // MHz

	// PPT
	int16_t Ppt; // %
	int16_t Tdc;

	uint8_t  FanLinearPwmPoints;
	uint8_t  FanLinearTempPoints;
	uint16_t FanMinimumPwm;
	uint16_t AcousticTargetRpmThreshold;
	uint16_t AcousticLimitRpmThreshold;
	uint16_t FanTargetTemperature; // Degree Celcius
	uint8_t  FanZeroRpmEnable;
	uint8_t  FanZeroRpmStopTemp;
	uint8_t  FanMode;
	uint8_t  MaxOpTemp;
	uint8_t  Padding[4];

	uint32_t Spare[12];

};

/* Unsure what this goes to
enum BOARD_GPIO_TYPE_e {
	BOARD_GPIO_SMUIO_0        = 0,
	BOARD_GPIO_SMUIO_1        = 1,
	BOARD_GPIO_SMUIO_2        = 2,
	BOARD_GPIO_SMUIO_3        = 3,
	BOARD_GPIO_SMUIO_4        = 4,
	BOARD_GPIO_SMUIO_5        = 5,
	BOARD_GPIO_SMUIO_6        = 6,
	BOARD_GPIO_SMUIO_7        = 7,
	BOARD_GPIO_SMUIO_8        = 8,
	BOARD_GPIO_SMUIO_9        = 9,
	BOARD_GPIO_SMUIO_10       = 10,
	BOARD_GPIO_SMUIO_11       = 11,
	BOARD_GPIO_SMUIO_12       = 12,
	BOARD_GPIO_SMUIO_13       = 13,
	BOARD_GPIO_SMUIO_14       = 14,
	BOARD_GPIO_SMUIO_15       = 15,
	BOARD_GPIO_SMUIO_16       = 16,
	BOARD_GPIO_SMUIO_17       = 17,
	BOARD_GPIO_SMUIO_18       = 18,
	BOARD_GPIO_SMUIO_19       = 19,
	BOARD_GPIO_SMUIO_20       = 20,
	BOARD_GPIO_SMUIO_21       = 21,
	BOARD_GPIO_SMUIO_22       = 22,
	BOARD_GPIO_SMUIO_23       = 23,
	BOARD_GPIO_SMUIO_24       = 24,
	BOARD_GPIO_SMUIO_25       = 25,
	BOARD_GPIO_SMUIO_26       = 26,
	BOARD_GPIO_SMUIO_27       = 27,
	BOARD_GPIO_SMUIO_28       = 28,
	BOARD_GPIO_SMUIO_29       = 29,
	BOARD_GPIO_SMUIO_30       = 30,
	BOARD_GPIO_SMUIO_31       = 31,
	MAX_BOARD_GPIO_SMUIO_NUM  = 32,
	BOARD_GPIO_DC_GEN_A       = 33,
	BOARD_GPIO_DC_GEN_B       = 34,
	BOARD_GPIO_DC_GEN_C       = 35,
	BOARD_GPIO_DC_GEN_D       = 36,
	BOARD_GPIO_DC_GEN_E       = 37,
	BOARD_GPIO_DC_GEN_F       = 38,
	BOARD_GPIO_DC_GEN_G       = 39,
	BOARD_GPIO_DC_GENLK_CLK   = 40,
	BOARD_GPIO_DC_GENLK_VSYNC = 41,
	BOARD_GPIO_DC_SWAPLOCK_A  = 42,
	BOARD_GPIO_DC_SWAPLOCK_B  = 43,
	INVALID_BOARD_GPIO      = 0xFF,
};
*/



struct BootValues_t {
	// PLL 0
	uint16_t InitGfxclk_bypass;
	uint16_t InitSocclk;
	uint16_t InitMp0clk;
	uint16_t InitMpioclk;
	uint16_t InitSmnclk;
	uint16_t InitUcpclk;
	uint16_t InitCsrclk;
	// PLL 1

	uint16_t InitDprefclk;
	uint16_t InitDcfclk;
	uint16_t InitDtbclk;
	// PLL 2
	uint16_t InitDclk; // assume same DCLK/VCLK for both instances
	uint16_t InitVclk;
	// PLL 3
	uint16_t InitUsbdfsclk;
	uint16_t InitMp1clk;
	uint16_t InitLclk;
	uint16_t InitBaco400clk_bypass;
	uint16_t InitBaco1200clk_bypass;
	uint16_t InitBaco700clk_bypass;
	// PLL 4
	uint16_t InitFclk;
	// PLL 5
	uint16_t InitGfxclk_clkb;

	// PLL 6
	uint8_t  InitUclkDPMState; // =0,1,2,3, frequency from FreqTableUclk

	uint8_t  Padding[3];

	uint32_t InitVcoFreqPll0;
	uint32_t InitVcoFreqPll1;
	uint32_t InitVcoFreqPll2;
	uint32_t InitVcoFreqPll3;
	uint32_t InitVcoFreqPll4;
	uint32_t InitVcoFreqPll5;
	uint32_t InitVcoFreqPll6;

	// encoding will change depending on SVI2/SVI3
	uint16_t InitGfx; // In mV(Q2) ,  should be 0?
	uint16_t InitSoc; // In mV(Q2)
	uint16_t InitU;   // In Mv(Q2) not applicable

	uint16_t Padding2;

	uint32_t Spare[8];

};


struct MsgLimits_t {
	uint16_t Power[PPT_THROTTLER_COUNT][POWER_SOURCE_COUNT]; // Watts
	uint16_t Tdc[TDC_THROTTLER_COUNT]; // Amps

	uint16_t Temperature[TEMP_COUNT]; // Celsius

	uint8_t  PwmLimitMin;
	uint8_t  PwmLimitMax;
	uint8_t  FanTargetTemperature;
	uint8_t  Spare1[1];

	uint16_t AcousticTargetRpmThresholdMin;
	uint16_t AcousticTargetRpmThresholdMax;

	uint16_t AcousticLimitRpmThresholdMin;
	uint16_t AcousticLimitRpmThresholdMax;

	uint16_t PccLimitMin;
	uint16_t PccLimitMax;

	uint16_t FanStopTempMin;
	uint16_t FanStopTempMax;
	uint16_t FanStartTempMin;
	uint16_t FanStartTempMax;

	uint16_t PowerMinPpt0[POWER_SOURCE_COUNT];
	uint32_t Spare[11];

};

struct DriverReportedClocks_t {
	uint16_t BaseClockAc;
	uint16_t GameClockAc;
	uint16_t BoostClockAc;
	uint16_t BaseClockDc;
	uint16_t GameClockDc;
	uint16_t BoostClockDc;

	uint32_t Reserved[4];
};

struct AvfsDcBtcParams_smu13 {
	uint8_t  DcBtcEnabled;
	uint8_t  Padding[3];

	uint16_t DcTol;    // mV Q2
	uint16_t DcBtcGb;  // mV Q2

	uint16_t DcBtcMin; // mV Q2
	uint16_t DcBtcMax; // mV Q2

	struct linear_u32 DcBtcGbScalar;

};

struct AvfsFuseOverride_smu13 {
	uint16_t AvfsTemp[AVFS_TEMP_COUNT]; // in degrees C
	uint16_t VftFMin;    // in MHz
	uint16_t VInversion; // in mV Q2
	struct quadratic_u32 qVft[AVFS_TEMP_COUNT];
	struct quadratic_u32 qAvfsGb;
	struct quadratic_u32 qAvfsGb2;
};

struct skutable_smu13 { // SECTION: Version

	uint32_t Version; // should be unique to each SKU(i.e if any value changes in below structure then this value must be different)
	// SECTION: Feature Control
	//uint32_t FeaturesToRun[NUM_FEATURES / 32]; // Features that PMFW will attempt to enable. Use FEATURE_*_BIT as mapping
	union powerplay_feature_control_smu13 features;

	// SECTION: Miscellaneous Configuration
	enum PwrConfig_e TotalPowerConfig; // Determines how PMFW calculates the power. Use defines from PwrConfig_e
	enum CUSTOMER_VARIANT_e CustomerVariant;  // To specify if this PPTable is intended for a particular customer. Use defines from CUSTOMER_VARIANT_e
	uint8_t  MemoryTemperatureTypeMask; // Bit mapping indicating which methods of memory temperature reading are enabled. Use defines from MEM_TEMP_*BIT
	enum SMARTSHIFT_VERSION_e SmartShiftVersion; // Determine what SmartShift feature version is supported Use defines from SMARTSHIFT_VERSION_e
	// SECTION: Infrastructure Limits
	uint16_t SocketPowerLimitAc[PPT_THROTTLER_COUNT]; // In Watts. Power limit that PMFW attempts to control to in AC mode. Multiple limits supported
	uint16_t SocketPowerLimitDc[PPT_THROTTLER_COUNT]; // In Watts. Power limit that PMFW attempts to control to in DC mode. Multiple limits supported

	uint16_t SocketPowerLimitSmartShift2; // In Watts. Power limit used SmartShift
	// if set to 1, SocketPowerLimitAc and SocketPowerLimitDc will be interpreted as legacy programs(i.e absolute power). If 0, all except index 0 will be scalars // relative index 0
	uint8_t  EnableLegacyPptLimit;
	uint8_t  UseInputTelemetry; // applicable to SVI3 only and only to be set if VRs support
	uint8_t  SmartShiftMinReportedPptinDcs; // minimum possible active power consumption for this SKU. Used for SmartShift power reporting

	uint8_t  PaddingPpt[1];

	uint16_t VrTdcLimit[TDC_THROTTLER_COUNT];       // In Amperes. Current limit associated with VR regulator maximum temperature

	uint16_t PlatformTdcLimit[TDC_THROTTLER_COUNT]; // In Amperes. Current limit associated with platform maximum temperature per VR current rail

	uint16_t TemperatureLimit[TEMP_COUNT]; // In degrees Celsius. Temperature limit associated with each input

	uint16_t HwCtfTempLimit; // In degrees Celsius. Temperature above which HW will trigger CTF. Consumed by VBIOS only

	uint16_t PaddingInfra;
	// Per year normalized Vmax state failure rates (sum of the two domains divided by life time in years)
	uint32_t FitControllerFailureRateLimit; // in IEEE float // Expected GFX Duty Cycle at Vmax.
	uint32_t FitControllerGfxDutyCycle;     // in IEEE float // Expected SOC Duty Cycle at Vmax.
	uint32_t FitControllerSocDutyCycle;     // in IEEE float
	// This offset will be deducted from the controller output to before it goes through the SOC Vset limiter block.
	uint32_t FitControllerSocOffset;        // in IEEE float

	uint32_t GfxApccPlusResidencyLimit; // Percentage value. Used by APCC+ controller to control PCC residency to some value
	// SECTION: Throttler settings
	uint32_t ThrottlerControlMask;      // See THROTTLER_*_BIT for mapping
	// SECTION: FW DSTATE Settings
	uint32_t FwDStateMask;              // See FW_DSTATE_*_BIT for mapping
	// SECTION: Voltage Control Parameters
	uint16_t UlvVoltageOffset[PMFW_VOLT_PLANE_COUNT]; // In mV(Q2). ULV offset used in either GFX_ULV or SOC_ULV(part of FW_DSTATE)

	uint16_t UlvVoltageOffsetU;        // In mV(Q2). ULV offset used in either U_ULV(part of FW_DSTATE)
	uint16_t DeepUlvVoltageOffsetSoc;  // In mV(Q2)  Long Idle Vmin (deep ULV), for VDD_SOC as part of FW_DSTATE
	// Voltage Limits
	uint16_t DefaultMaxVoltage[PMFW_VOLT_PLANE_COUNT]; // In mV(Q2) Maximum voltage without FIT controller enabled
	uint16_t BoostMaxVoltage[PMFW_VOLT_PLANE_COUNT];   // In mV(Q2) Maximum voltage with FIT controller enabled
	// Vmin Optimizations
	int16_t VminTempHystersis[PMFW_VOLT_PLANE_COUNT];  // Celsius Temperature hysteresis for switching between low/high temperature values for Vmin
	int16_t VminTempThreshold[PMFW_VOLT_PLANE_COUNT];  // Celsius Temperature threshold for switching between low/high temperature values for Vmin
	uint16_t Vmin_Hot_T0[PMFW_VOLT_PLANE_COUNT];       // In mV(Q2) Initial (pre-aging) Vset to be used at hot.
	uint16_t Vmin_Cold_T0[PMFW_VOLT_PLANE_COUNT];      // In mV(Q2) Initial (pre-aging) Vset to be used at cold.
	uint16_t Vmin_Hot_Eol[PMFW_VOLT_PLANE_COUNT];      // In mV(Q2) End-of-life Vset to be used at hot.
	uint16_t Vmin_Cold_Eol[PMFW_VOLT_PLANE_COUNT];     // In mV(Q2) End-of-life Vset to be used at cold.
	uint16_t Vmin_Aging_Offset[PMFW_VOLT_PLANE_COUNT]; // In mV(Q2) Worst-case aging margin
	uint16_t Spare_Vmin_Plat_Offset_Hot[PMFW_VOLT_PLANE_COUNT];  // In mV(Q2) Platform offset apply to T0 Hot
	uint16_t Spare_Vmin_Plat_Offset_Cold[PMFW_VOLT_PLANE_COUNT]; // In mV(Q2) Platform offset apply to T0 Cold
	// This is a fixed/minimum VMIN aging degradation offset which is applied at T0. This reflects the minimum amount of aging already accounted for.
	uint16_t VcBtcFixedVminAgingOffset[PMFW_VOLT_PLANE_COUNT]; // Linear offset or GB term to account for mis-correlation between PSM and Vmin shift trends across parts.
	uint16_t VcBtcVmin2PsmDegrationGb[PMFW_VOLT_PLANE_COUNT];  // Scalar coefficient of the PSM aging degradation function
	uint32_t VcBtcPsmA[PMFW_VOLT_PLANE_COUNT];  // A_PSM  // Exponential coefficient of the PSM aging degradation function
	uint32_t VcBtcPsmB[PMFW_VOLT_PLANE_COUNT];  // B_PSM  // Scalar coefficient of the VMIN aging degradation function. Specified as worst case between hot and cold.
	uint32_t VcBtcVminA[PMFW_VOLT_PLANE_COUNT]; // A_VMIN // Exponential coefficient of the VMIN aging degradation function. Specified as worst case between hot and cold.
	uint32_t VcBtcVminB[PMFW_VOLT_PLANE_COUNT]; // B_VMIN

	uint8_t  PerPartVminEnabled[PMFW_VOLT_PLANE_COUNT];
	uint8_t  VcBtcEnabled[PMFW_VOLT_PLANE_COUNT];

	uint16_t SocketPowerLimitAcTau[PPT_THROTTLER_COUNT]; // Time constant of LPF in ms
	uint16_t SocketPowerLimitDcTau[PPT_THROTTLER_COUNT]; // Time constant of LPF in ms

	struct quadratic_u32 Vmin_droop;
	uint32_t SpareVmin[9];

	// SECTION: DPM Configuration 1
	struct DpmDescriptor_t DpmDescriptor[PPCLK_SMU13_COUNT];

	uint16_t FreqTableGfx[NUM_GFXCLK_DPM_LEVELS_SMU13];        // In MHz
	uint16_t FreqTableVclk[NUM_VCLK_DPM_LEVELS_SMU13];         // In MHz
	uint16_t FreqTableDclk[NUM_DCLK_DPM_LEVELS_SMU13];         // In MHz
	uint16_t FreqTableSocclk[NUM_SOCCLK_DPM_LEVELS_SMU13];     // In MHz
	uint16_t FreqTableUclk[NUM_UCLK_DPM_LEVELS_SMU13];         // In MHz
	uint16_t FreqTableDispclk[NUM_DISPCLK_DPM_LEVELS_SMU13];   // In MHz
	uint16_t FreqTableDppClk[NUM_DPPCLK_DPM_LEVELS_SMU13];     // In MHz
	uint16_t FreqTableDprefclk[NUM_DPREFCLK_DPM_LEVELS_SMU13]; // In MHz
	uint16_t FreqTableDcfclk[NUM_DCFCLK_DPM_LEVELS_SMU13];     // In MHz
	uint16_t FreqTableDtbclk[NUM_DTBCLK_DPM_LEVELS_SMU13];     // In MHz
	uint16_t FreqTableFclk[NUM_FCLK_DPM_LEVELS_SMU13];         // In MHz

	uint32_t DcModeMaxFreq[PPCLK_SMU13_COUNT];                 // In MHz
	// SECTION: DPM Configuration 2
	uint16_t Mp0clkFreq[NUM_MP0CLK_DPM_LEVELS_SMU13];          // in MHz
	uint16_t Mp0DpmVoltage[NUM_MP0CLK_DPM_LEVELS_SMU13];       // mV(Q2)

	uint8_t  GfxclkSpare[2];
	uint16_t GfxclkFreqCap;
	// GFX Idle Power Settings
	uint16_t GfxclkFgfxoffEntry;   // in Mhz
	uint16_t GfxclkFgfxoffExitImu; // in Mhz
	uint16_t GfxclkFgfxoffExitRlc; // in Mhz
	uint16_t GfxclkThrottleClock;  // Used primarily in DCS
	uint8_t  EnableGfxPowerStagesGpio; // Genlk_vsync GPIO flag used to control gfx power stages
	uint8_t  GfxIdlePadding;

	uint8_t  SmsRepairWRCKClkDivEn;
	uint8_t  SmsRepairWRCKClkDivVal;
	uint8_t  GfxOffEntryEarlyMGCGEn;
	uint8_t  GfxOffEntryForceCGCGEn;
	uint8_t  GfxOffEntryForceCGCGDelayEn;
	uint8_t  GfxOffEntryForceCGCGDelayVal; // in microseconds

	uint16_t GfxclkFreqGfxUlv; // in MHz
	uint8_t  GfxIdlePadding2[2];
	uint32_t GfxOffEntryHysteresis; // For RLC to count after it enters CGCG, and before triggers GFXOFF entry
	uint32_t GfxoffSpare[15];
	// GFX GPO
	uint32_t DfllBtcMasterScalerM;
	int32_t DfllBtcMasterScalerB;
	uint32_t DfllBtcSlaveScalerM;
	int32_t DfllBtcSlaveScalerB;
	uint32_t DfllPccAsWaitCtrl; // GDFLL_AS_WAIT_CTRL_PCC register value to be passed to RLC msg
	uint32_t DfllPccAsStepCtrl; // GDFLL_AS_STEP_CTRL_PCC register value to be passed to RLC msg
	uint32_t GfxGpoSpare[10];
	// GFX DCS

	uint16_t DcsGfxOffVoltage;  // Voltage in mV(Q2) applied to VDDGFX when entering DCS GFXOFF phase
	uint16_t PaddingDcs;

	uint16_t DcsMinGfxOffTime;  // Minimum amount of time PMFW shuts GFX OFF as part of GFX DCS phase
	uint16_t DcsMaxGfxOffTime;  // Maximum amount of time PMFW can shut GFX OFF as part of GFX DCS phase at a stretch.

	uint32_t DcsMinCreditAccum; // Min amount of positive credit accumulation before waking GFX up as part of DCS.

	uint16_t DcsExitHysteresis; // The min amount of time power credit accumulator should have a value > 0 before SMU exits the DCS throttling phase.
	uint16_t DcsTimeout;        // This is the amount of time SMU FW waits for RLC to put GFX into GFXOFF before reverting to the fallback mechanism of throttling GFXCLK to Fmin.


	uint32_t DcsSpare[14];
	// UCLK section
	uint16_t ShadowFreqTableUclk[NUM_UCLK_DPM_LEVELS_SMU13]; // In MHz
	// UCLK section
	uint8_t  UseStrobeModeOptimizations; // Set to indicate that FW should use strobe mode optimizations
	uint8_t  PaddingMem[3];

	uint8_t  UclkDpmPstates[NUM_UCLK_DPM_LEVELS_SMU13]; // 4 DPM states, 0-P0, 1-P1, 2-P2, 3-P3.
	uint8_t  FreqTableUclkDiv[NUM_UCLK_DPM_LEVELS_SMU13]; // 0:Div-1, 1:Div-1/2, 2:Div-1/4, 3:Div-1/8

	uint16_t MemVmempVoltage[NUM_UCLK_DPM_LEVELS_SMU13]; // mV(Q2)
	uint16_t MemVddioVoltage[NUM_UCLK_DPM_LEVELS_SMU13]; // mV(Q2)
	// FCLK Section

	uint8_t  FclkDpmUPstates[NUM_FCLK_DPM_LEVELS_SMU13]; // U P-state ID associated with each FCLK DPM state.
	uint16_t FclkDpmVddU[NUM_FCLK_DPM_LEVELS_SMU13]; // mV(Q2) Vset U voltage associated with each FCLK DPM state.
	uint16_t FclkDpmUSpeed[NUM_FCLK_DPM_LEVELS_SMU13]; // U speed associated with each FCLK DPM state
	uint16_t FclkDpmDisallowPstateFreq;  // Frequency which FW will target when indicated that display config cannot support P-state. Set to 0 use FW calculated value
	uint16_t PaddingFclk;
	// Link DPM Settings
	uint8_t  PcieGenSpeed[NUM_LINK_LEVELS_SMU13];  // /< 0:PciE-gen1 1:PciE-gen2 2:PciE-gen3 3:PciE-gen4
	uint8_t  PcieLaneCount[NUM_LINK_LEVELS_SMU13]; // /< 1=x1, 2=x2, 3=x4, 4=x8, 5=x12, 6=x16
	uint16_t LclkFreq[NUM_LINK_LEVELS_SMU13];
	// SECTION: Fan Control
	uint16_t FanStopTemp[TEMP_COUNT];  // Celsius
	uint16_t FanStartTemp[TEMP_COUNT]; // Celsius

	uint16_t FanGain[TEMP_COUNT];
	uint16_t FanGainPadding;

	uint16_t FanPwmMin;
	uint16_t AcousticTargetRpmThreshold;
	uint16_t AcousticLimitRpmThreshold;
	uint16_t FanMaximumRpm;
	uint16_t MGpuAcousticLimitRpmThreshold;
	uint16_t FanTargetGfxclk;
	uint32_t TempInputSelectMask;
	uint8_t  FanZeroRpmEnable;
	uint8_t  FanTachEdgePerRev;
	uint16_t FanTargetTemperature[TEMP_COUNT];
	// The following are AFC override parameters. Leave at 0 to use FW defaults.
	int16_t FuzzyFan_ErrorSetDelta;
	int16_t FuzzyFan_ErrorRateSetDelta;
	int16_t FuzzyFan_PwmSetDelta;
	uint16_t FuzzyFan_Reserved;

	uint16_t FwCtfLimit[TEMP_COUNT];

	uint16_t IntakeTempEnableRPM;
	int16_t IntakeTempOffsetTemp;
	uint16_t IntakeTempReleaseTemp;
	uint16_t IntakeTempHighIntakeAcousticLimit;
	uint16_t IntakeTempAcouticLimitReleaseRate;

	int16_t FanAbnormalTempLimitOffset;
	uint16_t FanStalledTriggerRpm;
	uint16_t FanAbnormalTriggerRpmCoeff;
	uint16_t FanAbnormalDetectionEnable;

	uint8_t  FanIntakeSensorSupport;
	uint8_t  FanIntakePadding[3];
	uint32_t FanSpare[13];	// SECTION: VDD_GFX AVFS

	uint8_t  OverrideGfxAvfsFuses;
	uint8_t  GfxAvfsPadding[3];

	uint32_t L2HwRtAvfsFuses[PP_GRTAVFS_HW_FUSE_COUNT]; // see fusedoc for encoding
	uint32_t SeHwRtAvfsFuses[PP_GRTAVFS_HW_FUSE_COUNT];

	uint32_t CommonRtAvfs[PP_GRTAVFS_FW_COMMON_FUSE_COUNT];

	uint32_t L2FwRtAvfsFuses[PP_GRTAVFS_FW_SEP_FUSE_COUNT];
	uint32_t SeFwRtAvfsFuses[PP_GRTAVFS_FW_SEP_FUSE_COUNT];

	uint32_t Droop_PWL_F[PP_NUM_RTAVFS_PWL_ZONES];
	uint32_t Droop_PWL_a[PP_NUM_RTAVFS_PWL_ZONES];
	uint32_t Droop_PWL_b[PP_NUM_RTAVFS_PWL_ZONES];
	uint32_t Droop_PWL_c[PP_NUM_RTAVFS_PWL_ZONES];

	uint32_t Static_PWL_Offset[PP_NUM_RTAVFS_PWL_ZONES];

	uint32_t dGbV_dT_vmin;
	uint32_t dGbV_dT_vmax;

	uint32_t V2F_vmin_range_low;
	uint32_t V2F_vmin_range_high;
	uint32_t V2F_vmax_range_low;
	uint32_t V2F_vmax_range_high;

	struct AvfsDcBtcParams_smu13 DcBtcGfxParams;

	uint32_t GfxAvfsSpare[32];
	// SECTION: VDD_SOC AVFS

	uint8_t  OverrideSocAvfsFuses;
	uint8_t  MinSocAvfsRevision;
	uint8_t  SocAvfsPadding[2];

	struct AvfsFuseOverride_smu13 SocAvfsFuseOverride[AVFS_D_COUNT];

	struct droop_u32 dBtcGbSoc[AVFS_D_COUNT]; // GHz->V BtcGb

	struct linear_u32 qAgingGb[AVFS_D_COUNT]; // GHz->V

	struct quadratic_u32 qStaticVoltageOffset[AVFS_D_COUNT]; // GHz->V

	struct AvfsDcBtcParams_smu13 DcBtcSocParams[AVFS_D_COUNT];

	uint32_t SocAvfsSpare[32];
	// SECTION: Boot clock and voltage values
	struct BootValues_t BootValues;
	// SECTION: Driver Reported Clocks
	struct DriverReportedClocks_t DriverReportedClocks;
	// SECTION: Message Limits
	struct MsgLimits_t MsgLimits;
	// SECTION: OverDrive Limits
	struct overdrivelimits_smu13 OverDriveLimitsMin;
	struct overdrivelimits_smu13 OverDriveLimitsBasicMax;
	struct overdrivelimits_smu13 OverDriveLimitsAdvancedMax;
	// SECTION: Advanced Options
	union dpm_debug_override_smu13 DebugOverrides;
	// Section: Total Board Power idle vs active coefficients
	uint8_t  TotalBoardPowerSupport;
	uint8_t  TotalBoardPowerPadding[3];

	int16_t TotalIdleBoardPowerM;
	int16_t TotalIdleBoardPowerB;
	int16_t TotalBoardPowerM;
	int16_t TotalBoardPowerB;

	struct quadratic_u32 qFeffCoeffGameClock[POWER_SOURCE_COUNT];
	struct quadratic_u32 qFeffCoeffBaseClock[POWER_SOURCE_COUNT];
	struct quadratic_u32 qFeffCoeffBoostClock[POWER_SOURCE_COUNT];
	// SECTION: Sku Reserved
	uint32_t Spare[43];
	// Padding for MMHUB - do not modify this
	uint32_t MmHubPadding[8];

};

struct boardtable_smu13 {
	// SECTION: Version
	uint32_t Version; // should be unique to each board type

	// SECTION: I2C Control
	struct i2ccontrollerconfig_u8 I2cControllers[NUM_I2C_CONTROLLERS];
	// SECTION: SVI2 Board Parameters
	uint8_t  VddGfxVrMapping;  // Use VR_MAPPING* bitfields
	uint8_t  VddSocVrMapping;  // Use VR_MAPPING* bitfields
	uint8_t  VddMem0VrMapping; // Use VR_MAPPING* bitfields
	uint8_t  VddMem1VrMapping; // Use VR_MAPPING* bitfields

	uint8_t  GfxUlvPhaseSheddingMask;   // set this to 1 to set PSI0/1 to 1 in ULV mode
	uint8_t  SocUlvPhaseSheddingMask;   // set this to 1 to set PSI0/1 to 1 in ULV mode
	uint8_t  VmempUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
	uint8_t  VddioUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
	// SECTION SVI3 Board Parameters
	uint8_t  SlaveAddrMapping[SVI_PLANE_COUNT];
	uint8_t  VrPsiSupport[SVI_PLANE_COUNT];

	uint8_t  PaddingPsi[SVI_PLANE_COUNT];
	uint8_t  EnablePsi6[SVI_PLANE_COUNT]; // only applicable in SVI3
	// SECTION: Voltage Regulator Settings
	struct SviTelemetryScale_t SviTelemetryScale[SVI_PLANE_COUNT];
	uint32_t VoltageTelemetryRatio[SVI_PLANE_COUNT]; // This is used for VDDIO  Svi2 Div Ratio workaround. It has 16 fractional bits (Q16.16)

	uint8_t  DownSlewRateVr[SVI_PLANE_COUNT];
	// SECTION: GPIO Settings

	uint8_t  LedOffGpio;
	uint8_t  FanOffGpio;
	uint8_t  GfxVrPowerStageOffGpio;

	uint8_t  AcDcGpio;       // GPIO pin configured for AC/DC switching
	uint8_t  AcDcPolarity;   // GPIO polarity for AC/DC switching
	uint8_t  VR0HotGpio;     // GPIO pin configured for VR0 HOT event
	uint8_t  VR0HotPolarity; // GPIO polarity for VR0 HOT event

	uint8_t  GthrGpio;       // GPIO pin configured for GTHR Event
	uint8_t  GthrPolarity;   // replace GPIO polarity for GTHR
	// LED Display Settings
	uint8_t  LedPin0;        // GPIO number for LedPin[0]
	uint8_t  LedPin1;        // GPIO number for LedPin[1]
	uint8_t  LedPin2;        // GPIO number for LedPin[2]
	uint8_t  LedEnableMask;

	uint8_t  LedPcie;        // GPIO number for PCIE results
	uint8_t  LedError;       // GPIO number for Error Cases
	// SECTION: Clock Spread Spectrum
	// UCLK Spread Spectrum
	uint8_t  UclkTrainingModeSpreadPercent; // Q4.4
	uint8_t  UclkSpreadPadding;
	uint16_t UclkSpreadFreq; // kHz
	// UCLK Spread Spectrum
	uint8_t  UclkSpreadPercent[MEM_VENDOR_COUNT];
	// FCLK Spread Spectrum
	uint8_t  FclkSpreadPadding;
	uint8_t  FclkSpreadPercent;  // Q4.4
	uint16_t FclkSpreadFreq;     // kHz
	// Section: Memory Config
	uint8_t  DramWidth; // Width of interface to the channel for each DRAM module. See DRAM_BIT_WIDTH_TYPE_e
	uint8_t  PaddingMem1[7];
	// SECTION: UMC feature flags
	uint8_t  HsrEnabled;
	uint8_t  VddqOffEnabled;
	uint8_t  PaddingUmcFlags[2];

	uint32_t PostVoltageSetBacoDelay; // in microseconds. Amount of time FW will wait after power good is established or PSI0 command is issued
	uint32_t BacoEntryDelay; // in milliseconds. Amount of time FW will wait to trigger BACO entry after receiving entry notification from OS

	uint8_t  FuseWritePowerMuxPresent;
	uint8_t  FuseWritePadding[3];
	// SECTION: Board Reserved
	uint32_t BoardSpare[63];
	// SECTION: Structure Padding
	// Padding for MMHUB - do not modify this
	uint32_t MmHubPadding[8];
};

struct pptable_smu13 {
	struct skutable_smu13 SkuTable;
	struct boardtable_smu13 BoardTable;
};




#pragma pack(pop)



/*
struct DriverSmuConfig_t {
	// Time constant parameters for clock averages in ms
	uint16_t GfxclkAverageLpfTau;
	uint16_t FclkAverageLpfTau;
	uint16_t UclkAverageLpfTau;
	uint16_t GfxActivityLpfTau;
	uint16_t UclkActivityLpfTau;
	uint16_t SocketPowerLpfTau;
	uint16_t VcnClkAverageLpfTau;
	uint16_t VcnUsageAverageLpfTau;
};

struct DriverSmuConfigExternal_t {
	DriverSmuConfig_t DriverSmuConfig;

	uint32_t Spare[8];
	// Padding - ignore
	uint32_t MmHubPadding[8]; // SMU internal use
};


struct DriverInfoTable_t {

	uint16_t FreqTableGfx      [NUM_GFXCLK_DPM_LEVELS_SMU13  ];     // In MHz
	uint16_t FreqTableVclk     [NUM_VCLK_DPM_LEVELS_SMU13    ];     // In MHz
	uint16_t FreqTableDclk     [NUM_DCLK_DPM_LEVELS_SMU13    ];     // In MHz
	uint16_t FreqTableSocclk   [NUM_SOCCLK_DPM_LEVELS_SMU13  ];     // In MHz
	uint16_t FreqTableUclk     [NUM_UCLK_DPM_LEVELS_SMU13    ];     // In MHz
	uint16_t FreqTableDispclk  [NUM_DISPCLK_DPM_LEVELS_SMU13 ];     // In MHz
	uint16_t FreqTableDppClk   [NUM_DPPCLK_DPM_LEVELS_SMU13  ];     // In MHz
	uint16_t FreqTableDprefclk [NUM_DPREFCLK_DPM_LEVELS_SMU13];     // In MHz
	uint16_t FreqTableDcfclk   [NUM_DCFCLK_DPM_LEVELS_SMU13  ];     // In MHz
	uint16_t FreqTableDtbclk   [NUM_DTBCLK_DPM_LEVELS_SMU13  ];     // In MHz
	uint16_t FreqTableFclk     [NUM_FCLK_DPM_LEVELS_SMU13    ];     // In MHz

	uint16_t DcModeMaxFreq     [PPCLK_SMU13_COUNT            ];     // In MHz

	uint16_t Padding;

	uint32_t Spare[32];

	// Padding - ignore
	uint32_t MmHubPadding[8]; // SMU internal use

};

struct SmuMetrics_t {
	uint32_t CurrClock[PPCLK_SMU13_COUNT];

	uint16_t AverageGfxclkFrequencyTarget;
	uint16_t AverageGfxclkFrequencyPreDs;
	uint16_t AverageGfxclkFrequencyPostDs;
	uint16_t AverageFclkFrequencyPreDs;
	uint16_t AverageFclkFrequencyPostDs;
	uint16_t AverageMemclkFrequencyPreDs;  // this is scaled to actual memory clock
	uint16_t AverageMemclkFrequencyPostDs; // this is scaled to actual memory clock
	uint16_t AverageVclk0Frequency;
	uint16_t AverageDclk0Frequency;
	uint16_t AverageVclk1Frequency;
	uint16_t AverageDclk1Frequency;
	uint16_t PCIeBusy;
	uint16_t dGPU_W_MAX;
	uint16_t padding;

	uint32_t MetricsCounter;

	uint16_t AvgVoltage[SVI_PLANE_COUNT];
	uint16_t AvgCurrent[SVI_PLANE_COUNT];

	uint16_t AverageGfxActivity;
	uint16_t AverageUclkActivity;
	uint16_t Vcn0ActivityPercentage;
	uint16_t Vcn1ActivityPercentage;

	uint32_t EnergyAccumulator;
	uint16_t AverageSocketPower;
	uint16_t AverageTotalBoardPower;

	uint16_t AvgTemperature[TEMP_COUNT];
	uint16_t AvgTemperatureFanIntake;

	uint8_t  PcieRate;
	uint8_t  PcieWidth;

	uint8_t  AvgFanPwm;
	uint8_t  Padding[1];
	uint16_t AvgFanRpm;


	uint8_t  ThrottlingPercentage[THROTTLER_COUNT];

	// metrics for D3hot entry/exit and driver ARM msgs
	uint32_t D3HotEntryCountPerMode[D3HOT_SEQUENCE_COUNT];
	uint32_t D3HotExitCountPerMode[D3HOT_SEQUENCE_COUNT];
	uint32_t ArmMsgReceivedCountPerMode[D3HOT_SEQUENCE_COUNT];

	uint16_t ApuSTAPMSmartShiftLimit;
	uint16_t ApuSTAPMLimit;
	uint16_t AvgApuSocketPower;

	uint16_t AverageUclkActivity_MAX;

	uint32_t PublicSerialNumberLower;
	uint32_t PublicSerialNumberUpper;
};

struct SmuMetricsExternal_t {
	SmuMetrics_t SmuMetrics;
	uint32_t Spare[30];

	// Padding - ignore
	uint32_t MmHubPadding[8]; // SMU internal use
};

struct WatermarkRowGeneric_t {
	uint8_t  WmSetting;
	uint8_t  Flags;
	uint8_t  Padding[2];

};

#define NUM_WM_RANGES 4

enum WATERMARKS_FLAGS_e {
	WATERMARKS_CLOCK_RANGE = 0,
	WATERMARKS_DUMMY_PSTATE,
	WATERMARKS_MALL,
	WATERMARKS_COUNT,
};

struct Watermarks_t {
	// Watermarks
	WatermarkRowGeneric_t WatermarkRow[NUM_WM_RANGES];
};

struct WatermarksExternal_t {
	Watermarks_t Watermarks;
	uint32_t Spare[16];

	uint32_t MmHubPadding[8]; // SMU internal use
};

struct AvfsDebugTable_t {
	uint16_t avgPsmCount[36];
	uint16_t minPsmCount[36];
	float    avgPsmVoltage[36];
	float    minPsmVoltage[36];
};

struct AvfsDebugTableExternal_t {
	AvfsDebugTable_t AvfsDebugTable;

	uint32_t MmHubPadding[8]; // SMU internal use
};


struct DpmActivityMonitorCoeffInt_t {
	uint8_t  Gfx_ActiveHystLimit;
	uint8_t  Gfx_IdleHystLimit;
	uint8_t  Gfx_FPS;
	uint8_t  Gfx_MinActiveFreqType;
	uint8_t  Gfx_BoosterFreqType;
	uint8_t  PaddingGfx;
	uint16_t Gfx_MinActiveFreq;            // MHz
	uint16_t Gfx_BoosterFreq;              // MHz
	uint16_t Gfx_PD_Data_time_constant;    // Time constant of PD controller in ms
	uint32_t Gfx_PD_Data_limit_a;          // Q16
	uint32_t Gfx_PD_Data_limit_b;          // Q16
	uint32_t Gfx_PD_Data_limit_c;          // Q16
	uint32_t Gfx_PD_Data_error_coeff;      // Q16
	uint32_t Gfx_PD_Data_error_rate_coeff; // Q16

	uint8_t  Fclk_ActiveHystLimit;
	uint8_t  Fclk_IdleHystLimit;
	uint8_t  Fclk_FPS;
	uint8_t  Fclk_MinActiveFreqType;
	uint8_t  Fclk_BoosterFreqType;
	uint8_t  PaddingFclk;
	uint16_t Fclk_MinActiveFreq;            // MHz
	uint16_t Fclk_BoosterFreq;              // MHz
	uint16_t Fclk_PD_Data_time_constant;    // Time constant of PD controller in ms
	uint32_t Fclk_PD_Data_limit_a;          // Q16
	uint32_t Fclk_PD_Data_limit_b;          // Q16
	uint32_t Fclk_PD_Data_limit_c;          // Q16
	uint32_t Fclk_PD_Data_error_coeff;      // Q16
	uint32_t Fclk_PD_Data_error_rate_coeff; // Q16

	uint32_t Mem_UpThreshold_Limit[NUM_UCLK_DPM_LEVELS_SMU13];          // Q16
	uint8_t  Mem_UpHystLimit[NUM_UCLK_DPM_LEVELS_SMU13];
	uint8_t  Mem_DownHystLimit[NUM_UCLK_DPM_LEVELS_SMU13];
	uint16_t Mem_Fps;
	uint8_t  padding[2];

};


struct DpmActivityMonitorCoeffIntExternal_t {
	DpmActivityMonitorCoeffInt_t DpmActivityMonitorCoeffInt;
	uint32_t MmHubPadding[8]; // SMU internal use
};



// Workload bits
#define WORKLOAD_PPLIB_DEFAULT_BIT        0
#define WORKLOAD_PPLIB_FULL_SCREEN_3D_BIT 1
#define WORKLOAD_PPLIB_POWER_SAVING_BIT   2
#define WORKLOAD_PPLIB_VIDEO_BIT          3
#define WORKLOAD_PPLIB_VR_BIT             4
#define WORKLOAD_PPLIB_COMPUTE_BIT        5
#define WORKLOAD_PPLIB_CUSTOM_BIT         6
#define WORKLOAD_PPLIB_WINDOW_3D_BIT      7
#define WORKLOAD_PPLIB_COUNT              8


// These defines are used with the following messages:
// SMC_MSG_TransferTableDram2Smu
// SMC_MSG_TransferTableSmu2Dram

// Table transfer status
#define TABLE_TRANSFER_OK         0x0
#define TABLE_TRANSFER_FAILED     0xFF
#define TABLE_TRANSFER_PENDING    0xAB

// Table types
#define TABLE_PPTABLE                 0
#define TABLE_COMBO_PPTABLE           1
#define TABLE_WATERMARKS              2
#define TABLE_AVFS_PSM_DEBUG          3
#define TABLE_PMSTATUSLOG             4
#define TABLE_SMU_METRICS             5
#define TABLE_DRIVER_SMU_CONFIG       6
#define TABLE_ACTIVITY_MONITOR_COEFF  7
#define TABLE_OVERDRIVE               8
#define TABLE_I2C_COMMANDS            9
#define TABLE_DRIVER_INFO             10
#define TABLE_ECCINFO                 11
#define TABLE_COUNT                   12

// IH Interupt ID
#define IH_INTERRUPT_ID_TO_DRIVER                   0xFE
#define IH_INTERRUPT_CONTEXT_ID_BACO                0x2
#define IH_INTERRUPT_CONTEXT_ID_AC                  0x3
#define IH_INTERRUPT_CONTEXT_ID_DC                  0x4
#define IH_INTERRUPT_CONTEXT_ID_AUDIO_D0            0x5
#define IH_INTERRUPT_CONTEXT_ID_AUDIO_D3            0x6
#define IH_INTERRUPT_CONTEXT_ID_THERMAL_THROTTLING  0x7
#define IH_INTERRUPT_CONTEXT_ID_FAN_ABNORMAL        0x8
#define IH_INTERRUPT_CONTEXT_ID_FAN_RECOVERY        0x9
*/
#endif
