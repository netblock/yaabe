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

#pragma pack(push, 1) // bios data must use byte alignment

// *** IMPORTANT ***
#define SMU13_0_7_DRIVER_IF_VERSION  0x35

// Increment this version if SkuTable_t or BoardTable_t change
#define PPTABLE_VERSION 0x27

#define NUM_GFXCLK_DPM_LEVELS_SMU13   16
#define NUM_VCLK_DPM_LEVELS_SMU13     8
#define NUM_DCLK_DPM_LEVELS_SMU13     8
// ECLK
#define NUM_MP0CLK_DPM_LEVELS_SMU13   2
#define NUM_SOCCLK_DPM_LEVELS_SMU13   8
#define NUM_UCLK_DPM_LEVELS_SMU13     4
#define NUM_FCLK_DPM_LEVELS_SMU13     8
#define NUM_DCFCLK_DPM_LEVELS_SMU13   8 // DCEF?
#define NUM_DISPCLK_DPM_LEVELS_SMU13  8
// PIXCLK
// PHYCLK
#define NUM_LINK_LEVELS_SMU13         3
// XGMI
#define NUM_DPPCLK_DPM_LEVELS_SMU13   8
#define NUM_DPREFCLK_DPM_LEVELS_SMU13 8
#define NUM_DTBCLK_DPM_LEVELS_SMU13   8
#define NUM_OD_FAN_MAX_POINTS_SMU13   6

union powerplay_feature_control_smu13 {
    uint64_t feature_control;
    struct { uint64_t
		FW_DATA_READ            :0-0 +1,
		DPM_GFXCLK              :1-1 +1,
		DPM_GFX_POWER_OPTIMIZER :2-2 +1,
		DPM_UCLK                :3-3 +1,
		DPM_FCLK                :4-4 +1,
		DPM_SOCCLK              :5-5 +1,
		DPM_MP0CLK              :6-6 +1,
		DPM_LINK                :7-7 +1,
		DPM_DCN                 :8-8 +1,
		VMEMP_SCALING           :9-9 +1,
		VDDIO_MEM_SCALING      :10-10 +1,
		DS_GFXCLK              :11-11 +1,
		DS_SOCCLK              :12-12 +1,
		DS_FCLK                :13-13 +1,
		DS_LCLK                :14-14 +1,
		DS_DCFCLK              :15-15 +1,
		DS_UCLK                :16-16 +1,
		GFX_ULV                :17-17 +1,
		FW_DSTATE              :18-18 +1,
		GFXOFF                 :19-19 +1,
		BACO                   :20-20 +1,
		MM_DPM                 :21-21 +1,
		SOC_MPCLK_DS           :22-22 +1,
		BACO_MPCLK_DS          :23-23 +1,
		THROTTLERS             :24-24 +1,
		SMARTSHIFT             :25-25 +1,
		GTHR                   :26-26 +1,
		ACDC                   :27-27 +1,
		VR0HOT                 :28-28 +1,
		FW_CTF                 :29-29 +1,
		FAN_CONTROL            :30-30 +1,
		GFX_DCS                :31-31 +1,
		GFX_READ_MARGIN        :32-32 +1,
		LED_DISPLAY            :33-33 +1,
		GFXCLK_SPREAD_SPECTRUM :34-34 +1,
		OUT_OF_BAND_MONITOR    :35-35 +1,
		OPTIMIZED_VMIN         :36-36 +1,
		GFX_IMU                :37-37 +1,
		BOOT_TIME_CAL          :38-38 +1,
		GFX_PCC_DFLL           :39-39 +1,
		SOC_CG                 :40-40 +1,
		DF_CSTATE              :41-41 +1,
		GFX_EDC                :42-42 +1,
		BOOT_POWER_OPT         :43-43 +1,
		CLOCK_POWER_DOWN_BYPASS:44-44 +1,
		DS_VCN                 :45-45 +1,
		BACO_CG                :46-46 +1,
		MEM_TEMP_READ          :47-47 +1,
		ATHUB_MMHUB_PG         :48-48 +1,
		SOC_PCC                :49-49 +1,
		EDC_PWRBRK             :50-50 +1,
		SPARE_51               :51-51 +1,
		SPARE_52               :52-52 +1,
		SPARE_53               :53-53 +1,
		SPARE_54               :54-54 +1,
		SPARE_55               :55-55 +1,
		SPARE_56               :56-56 +1,
		SPARE_57               :57-57 +1,
		SPARE_58               :58-58 +1,
		SPARE_59               :59-59 +1,
		SPARE_60               :60-60 +1,
		SPARE_61               :61-61 +1,
		SPARE_62               :62-62 +1,
		SPARE_63               :63-63 +1;
	};
};


union dpm_debug_override_smu13 {
	uint32_t DebugOverrides;
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
union throttler_control_smu13_0x35 {
	uint32_t ThrottlerControlMask;
	struct { uint32_t
		TEMP_EDGE      :0-0 +1,
		TEMP_HOTSPOT   :1-1 +1,
		TEMP_HOTSPOT_G :2-2 +1,
		TEMP_HOTSPOT_M :3-3 +1,
		TEMP_MEM       :4-4 +1,
		TEMP_VR_GFX    :5-5 +1,
		TEMP_VR_MEM0   :6-6 +1,
		TEMP_VR_MEM1   :7-7 +1,
		TEMP_VR_SOC    :8-8 +1,
		TEMP_VR_U      :9-9 +1,
		TEMP_LIQUID0  :10-10 +1,
		TEMP_LIQUID1  :11-11 +1,
		TEMP_PLX      :12-12 +1,
		TDC_GFX       :13-13 +1,
		TDC_SOC       :14-14 +1,
		TDC_U         :15-15 +1,
		PPT0          :16-16 +1,
		PPT1          :17-17 +1,
		PPT2          :18-18 +1,
		PPT3          :19-19 +1,
		FIT           :20-20 +1,
		GFX_APCC_PLUS :21-21 +1,
		reserved      :31-22 +1;
	};
};

// FW DState Features Control Bits
union fw_dstate_features_smu13_0x35 {
	uint32_t FwDStateMask;
	struct { uint32_t
		SOC_ULV           :0-0 +1,
		G6_HSR            :1-1 +1,
		G6_PHY_VMEMP_OFF  :2-2 +1,
		SMN_DS            :3-3 +1,
		MP1_WHISPER_MODE  :4-4 +1,
		SOC_LIV_MIN       :5-5 +1,
		SOC_PLL_PWRDN     :6-6 +1,
		MEM_PLL_PWRDN     :7-7 +1,
		MALL_ALLOC        :8-8 +1,
		MEM_PSI           :9-9 +1,
		HSR_NON_STROBE    :10-10 +1,
		MP0_ENTER_WFI     :11-11 +1,
		U_ULV             :12-12 +1,
		MALL_FLUSH        :13-13 +1,
		SOC_PSI           :14-14 +1,
		U_PSI             :15-15 +1,
		UCP_DS            :16-16 +1,
		CSRCLK_DS         :17-17 +1,
		MMHUB_INTERLOCK   :18-18 +1,
		D0i3_2_QUIET_FW   :19-19 +1,
		CLDO_PRG          :20-20 +1,
		DF_PLL_PWRDN      :21-21 +1,
		U_LOW_PWR_MODE_EN :22-22 +1,
		GFX_PSI6          :23-23 +1,
		GFX_VR_PWR_STAGE  :24-24 +1,
		reserved          :31-25 +1;
	};
};

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


enum DRAM_BIT_WIDTH_TYPE_e:uint8_t { // uint8_t  DramWidth;
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

#define CMDCONFIG_STOP_BIT      0
#define CMDCONFIG_RESTART_BIT   1
#define CMDCONFIG_READWRITE_BIT 2 // bit should be 0 for read, 1 for write

// TODO
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

enum DCS_ARCH_e {
	DCS_ARCH_DISABLED = 0,
	DCS_ARCH_FADCS    = 1,
	DCS_ARCH_ASYNC    = 2,
};

// Only Clks that have DPM descriptors are listed here
enum SMU13_PPCLK_e {
	SMU13_PPCLK_GFXCLK   = 0,
	SMU13_PPCLK_SOCCLK   = 1,
	SMU13_PPCLK_UCLK     = 2,
	SMU13_PPCLK_FCLK     = 3,
	SMU13_PPCLK_DCLK_0   = 4,
	SMU13_PPCLK_VCLK_0   = 5,
	SMU13_PPCLK_DCLK_1   = 6,
	SMU13_PPCLK_VCLK_1   = 7,
	SMU13_PPCLK_DISPCLK  = 8,
	SMU13_PPCLK_DPPCLK   = 9,
	SMU13_PPCLK_DPREFCLK = 10,
	SMU13_PPCLK_DCFCLK   = 11,
	SMU13_PPCLK_DTBCLK   = 12,
	SMU13_PPCLK_COUNT    = 13,
};

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

enum GpioIntPolarity_e {
	GPIO_INT_POLARITY_ACTIVE_LOW  = 0,
	GPIO_INT_POLARITY_ACTIVE_HIGH = 1,
};

enum FOPT_CALC_e:uint8_t {
	FOPT_CALC_AC_CALC_DC       = 0,
	FOPT_PPTABLE_AC_CALC_DC    = 1,
	FOPT_CALC_AC_PPTABLE_DC    = 2,
	FOPT_PPTABLE_AC_PPTABLE_DC = 3,
};

struct DpmDescriptor_t {
	uint8_t  Padding;
	uint8_t  SnapToDiscrete;        // 0 - Fine grained DPM, 1 - Discrete DPM
	uint8_t  NumDiscreteLevels;     // Set to 2 (Fmin, Fmax) when using fine grained DPM, otherwise set to # discrete levels used
	enum FOPT_CALC_e CalculateFopt; // Indication whether FW should calculate Fopt or use values below. Reference FOPT_CALC_e
	struct linear_f32 ConversionToAvfsClk; // Transfer function to AVFS Clock (GHz->GHz)
	uint32_t Padding3[3];
	uint16_t Padding4;
	uint16_t FoptimalDc; // Foptimal frequency in DC power mode.
	uint16_t FoptimalAc; // Foptimal frequency in AC power mode.
	uint16_t Padding2;
};


enum SMU_13_0_7_TEMP_e {
	SMU_13_0_7_TEMP_EDGE      = 0,
	SMU_13_0_7_TEMP_HOTSPOT   = 1,
	SMU_13_0_7_TEMP_HOTSPOT_G = 2,
	SMU_13_0_7_TEMP_HOTSPOT_M = 3,
	SMU_13_0_7_TEMP_MEM       = 4,
	SMU_13_0_7_TEMP_VR_GFX    = 5,
	SMU_13_0_7_TEMP_VR_MEM0   = 6,
	SMU_13_0_7_TEMP_VR_MEM1   = 7,
	SMU_13_0_7_TEMP_VR_SOC    = 8,
	SMU_13_0_7_TEMP_VR_U      = 9,
	SMU_13_0_7_TEMP_LIQUID0   = 10,
	SMU_13_0_7_TEMP_LIQUID1   = 11,
	SMU_13_0_7_TEMP_PLX       = 12,
	SMU_13_0_7_TEMP_COUNT     = 13,
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


// VBIOS or PPLIB configures telemetry slope and offset. Only slope expected to be set for SVI3
// Slope Q1.7, Offset Q1.2
struct SviTelemetryScale_t {
	int8_t   Offset; // in Amps
	uint8_t  Padding;
	uint16_t MaxCurrent; // in Amps
};
#define PP_NUM_RTAVFS_PWL_ZONES 5
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
	int16_t  VoltageOffsetPerZoneBoundary[PP_NUM_OD_VF_CURVE_POINTS];

	uint32_t Reserved;

	// Frequency changes
	int16_t  GfxclkFmin; // MHz
	int16_t  GfxclkFmax; // MHz
	uint16_t UclkFmin;   // MHz
	uint16_t UclkFmax;   // MHz

	// PPT
	int16_t  Ppt; // %
	int16_t  Tdc;

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

	int16_t  VoltageOffsetPerZoneBoundary;
	uint16_t Reserved1;

	uint16_t Reserved2;

	int16_t  GfxclkFmin; // MHz
	int16_t  GfxclkFmax; // MHz
	uint16_t UclkFmin;   // MHz
	uint16_t UclkFmax;   // MHz

	// PPT
	int16_t  Ppt; // %
	int16_t  Tdc;

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
	uq14_2_t InitGfx; // In mV(Q2) ,  should be 0?
	uq14_2_t InitSoc; // In mV(Q2)
	uq14_2_t InitU;   // In Mv(Q2) not applicable

	uint16_t Padding2;

	uint32_t Spare[8];

};


struct MsgLimits_t {
	uint16_t Power[PPT_THROTTLER_COUNT][POWER_SOURCE_COUNT]; // Watts
	uint16_t Tdc[TDC_THROTTLER_COUNT_SMU13]; // Amps

	uint16_t Temperature[SMU_13_0_7_TEMP_COUNT]; // Celsius

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

	uq14_2_t DcTol;    // mV Q2
	uq14_2_t DcBtcGb;  // mV Q2

	uq14_2_t DcBtcMin; // mV Q2
	uq14_2_t DcBtcMax; // mV Q2

	struct linear_f32 DcBtcGbScalar;

};

struct AvfsFuseOverride_smu13 {
	uint16_t AvfsTemp[AVFS_TEMP_COUNT]; // in degrees C
	uint16_t VftFMin;    // in MHz
	uq14_2_t VInversion; // in mV Q2
	struct quadratic_f32 qVft[AVFS_TEMP_COUNT];
	struct quadratic_f32 qAvfsGb;
	struct quadratic_f32 qAvfsGb2;
};

struct smu13_skutable_v39 { // SECTION: Version

	uint32_t Version; // should be unique to each SKU(i.e if any value changes in below structure then this value must be different)
	// SECTION: Feature Control

	union powerplay_feature_control_smu13 features;

	// SECTION: Miscellaneous Configuration
	enum PwrConfig_e TotalPowerConfig; // Determines how PMFW calculates the power.
	enum CUSTOMER_VARIANT_e CustomerVariant;  // To specify if this PPTable is intended for a particular customer.
	uint8_t  MemoryTemperatureTypeMask; // Bit mapping indicating which methods of memory temperature reading are enabled. Use defines from MEM_TEMP_*BIT
	enum SMARTSHIFT_VERSION_e SmartShiftVersion; // Determine what SmartShift feature version is supported
	// SECTION: Infrastructure Limits
	uint16_t SocketPowerLimitAc[PPT_THROTTLER_COUNT]; // In Watts. Power limit that PMFW attempts to control to in AC mode. Multiple limits supported
	uint16_t SocketPowerLimitDc[PPT_THROTTLER_COUNT]; // In Watts. Power limit that PMFW attempts to control to in DC mode. Multiple limits supported

	uint16_t SocketPowerLimitSmartShift2; // In Watts. Power limit used SmartShift
	uint8_t  EnableLegacyPptLimit; // if set to 1, SocketPowerLimitAc and SocketPowerLimitDc will be interpreted as legacy programs(i.e absolute power). If 0, all except index 0 will be scalars // relative index 0
	uint8_t  UseInputTelemetry; // applicable to SVI3 only and only to be set if VRs support
	uint8_t  SmartShiftMinReportedPptinDcs; // minimum possible active power consumption for this SKU. Used for SmartShift power reporting

	uint8_t  PaddingPpt[1];

	uint16_t VrTdcLimit[TDC_THROTTLER_COUNT_SMU13];       // In Amperes. Current limit associated with VR regulator maximum temperature

	uint16_t PlatformTdcLimit[TDC_THROTTLER_COUNT_SMU13]; // In Amperes. Current limit associated with platform maximum temperature per VR current rail

	uint16_t TemperatureLimit[SMU_13_0_7_TEMP_COUNT]; // In degrees Celsius. Temperature limit associated with each input

	uint16_t HwCtfTempLimit; // In degrees Celsius. Temperature above which HW will trigger CTF. Consumed by VBIOS only

	uint16_t PaddingInfra;
	// Per year normalized Vmax state failure rates (sum of the two domains divided by life time in years)
	float32_t FitControllerFailureRateLimit; // Expected GFX Duty Cycle at Vmax.
	float32_t FitControllerGfxDutyCycle; // Expected SOC Duty Cycle at Vmax.
	float32_t FitControllerSocDutyCycle;
	// This offset will be deducted from the controller output to before it goes through the SOC Vset limiter block.
	float32_t FitControllerSocOffset;

	uint32_t GfxApccPlusResidencyLimit; // Percentage value. Used by APCC+ controller to control PCC residency to some value
	// SECTION: Throttler settings
	union throttler_control_smu13_0x35 ThrottlerControlMask;
	// SECTION: FW DSTATE Settings
	union fw_dstate_features_smu13_0x35 FwDStateMask;
	// SECTION: Voltage Control Parameters
	uq14_2_t UlvVoltageOffset[PMFW_VOLT_PLANE_COUNT]; // In mV(Q2). ULV offset used in either GFX_ULV or SOC_ULV(part of FW_DSTATE)

	uq14_2_t UlvVoltageOffsetU;       // In mV(Q2). ULV offset used in either U_ULV(part of FW_DSTATE)
	uq14_2_t DeepUlvVoltageOffsetSoc; // In mV(Q2)  Long Idle Vmin (deep ULV), for VDD_SOC as part of FW_DSTATE
	// Voltage Limits
	uq14_2_t DefaultMaxVoltage[PMFW_VOLT_PLANE_COUNT]; // In mV(Q2) Maximum voltage without FIT controller enabled
	uq14_2_t BoostMaxVoltage[PMFW_VOLT_PLANE_COUNT];   // In mV(Q2) Maximum voltage with FIT controller enabled
	// Vmin Optimizations
	int16_t  VminTempHystersis[PMFW_VOLT_PLANE_COUNT];  // Celsius Temperature hysteresis for switching between low/high temperature values for Vmin
	int16_t  VminTempThreshold[PMFW_VOLT_PLANE_COUNT];  // Celsius Temperature threshold for switching between low/high temperature values for Vmin
	uq14_2_t Vmin_Hot_T0[PMFW_VOLT_PLANE_COUNT];       // In mV(Q2) Initial (pre-aging) Vset to be used at hot.
	uq14_2_t Vmin_Cold_T0[PMFW_VOLT_PLANE_COUNT];      // In mV(Q2) Initial (pre-aging) Vset to be used at cold.
	uq14_2_t Vmin_Hot_Eol[PMFW_VOLT_PLANE_COUNT];      // In mV(Q2) End-of-life Vset to be used at hot.
	uq14_2_t Vmin_Cold_Eol[PMFW_VOLT_PLANE_COUNT];     // In mV(Q2) End-of-life Vset to be used at cold.
	uq14_2_t Vmin_Aging_Offset[PMFW_VOLT_PLANE_COUNT]; // In mV(Q2) Worst-case aging margin
	uq14_2_t Spare_Vmin_Plat_Offset_Hot[PMFW_VOLT_PLANE_COUNT];  // In mV(Q2) Platform offset apply to T0 Hot
	uq14_2_t Spare_Vmin_Plat_Offset_Cold[PMFW_VOLT_PLANE_COUNT]; // In mV(Q2) Platform offset apply to T0 Cold
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

	struct quadratic_f32 Vmin_droop;
	uint32_t SpareVmin[9];

	// SECTION: DPM Configuration 1
	struct DpmDescriptor_t DpmDescriptor[SMU13_PPCLK_COUNT];

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

	uint32_t DcModeMaxFreq[SMU13_PPCLK_COUNT];                 // In MHz
	// SECTION: DPM Configuration 2
	uint16_t Mp0clkFreq[NUM_MP0CLK_DPM_LEVELS_SMU13];          // in MHz
	uq14_2_t Mp0DpmVoltage[NUM_MP0CLK_DPM_LEVELS_SMU13];       // mV(Q2)

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
	int32_t  DfllBtcMasterScalerB;
	uint32_t DfllBtcSlaveScalerM;
	int32_t  DfllBtcSlaveScalerB;
	uint32_t DfllPccAsWaitCtrl; // GDFLL_AS_WAIT_CTRL_PCC register value to be passed to RLC msg
	uint32_t DfllPccAsStepCtrl; // GDFLL_AS_STEP_CTRL_PCC register value to be passed to RLC msg
	uint32_t GfxGpoSpare[10];
	// GFX DCS

	uq14_2_t DcsGfxOffVoltage;  // Voltage in mV(Q2) applied to VDDGFX when entering DCS GFXOFF phase
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

	enum DPM_PSTATES_e UclkDpmPstates[NUM_UCLK_DPM_LEVELS_SMU13];   // 4 DPM states
	enum UCLK_DIV_e FreqTableUclkDiv[NUM_UCLK_DPM_LEVELS_SMU13];

	uq14_2_t MemVmempVoltage[NUM_UCLK_DPM_LEVELS_SMU13]; // mV(Q2)
	uq14_2_t MemVddioVoltage[NUM_UCLK_DPM_LEVELS_SMU13]; // mV(Q2)
	// FCLK Section

	uint8_t  FclkDpmUPstates[NUM_FCLK_DPM_LEVELS_SMU13]; // U P-state ID associated with each FCLK DPM state.
	uq14_2_t FclkDpmVddU[NUM_FCLK_DPM_LEVELS_SMU13]; // mV(Q2) Vset U voltage associated with each FCLK DPM state.
	uint16_t FclkDpmUSpeed[NUM_FCLK_DPM_LEVELS_SMU13]; // U speed associated with each FCLK DPM state
	uint16_t FclkDpmDisallowPstateFreq;  // Frequency which FW will target when indicated that display config cannot support P-state. Set to 0 use FW calculated value
	uint16_t PaddingFclk;
	// Link DPM Settings
	enum PCIE_SPEED_e PcieGenSpeed[NUM_LINK_LEVELS_SMU13];
	enum PCIE_WIDTH_e PcieLaneCount[NUM_LINK_LEVELS_SMU13];
	uint16_t LclkFreq[NUM_LINK_LEVELS_SMU13];
	// SECTION: Fan Control
	uint16_t FanStopTemp[SMU_13_0_7_TEMP_COUNT];  // Celsius
	uint16_t FanStartTemp[SMU_13_0_7_TEMP_COUNT]; // Celsius

	uint16_t FanGain[SMU_13_0_7_TEMP_COUNT];
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
	uint16_t FanTargetTemperature[SMU_13_0_7_TEMP_COUNT];
	// The following are AFC override parameters. Leave at 0 to use FW defaults.
	int16_t  FuzzyFan_ErrorSetDelta;
	int16_t  FuzzyFan_ErrorRateSetDelta;
	int16_t  FuzzyFan_PwmSetDelta;
	uint16_t FuzzyFan_Reserved;

	uint16_t FwCtfLimit[SMU_13_0_7_TEMP_COUNT];

	uint16_t IntakeTempEnableRPM;
	int16_t  IntakeTempOffsetTemp;
	uint16_t IntakeTempReleaseTemp;
	uint16_t IntakeTempHighIntakeAcousticLimit;
	uint16_t IntakeTempAcouticLimitReleaseRate;

	int16_t  FanAbnormalTempLimitOffset;
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

	struct droop_f32 dBtcGbSoc[AVFS_D_COUNT]; // GHz->V BtcGb

	struct linear_f32 qAgingGb[AVFS_D_COUNT]; // GHz->V

	struct quadratic_f32 qStaticVoltageOffset[AVFS_D_COUNT]; // GHz->V

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

	int16_t  TotalIdleBoardPowerM;
	int16_t  TotalIdleBoardPowerB;
	int16_t  TotalBoardPowerM;
	int16_t  TotalBoardPowerB;

	struct quadratic_f32 qFeffCoeffGameClock[POWER_SOURCE_COUNT];
	struct quadratic_f32 qFeffCoeffBaseClock[POWER_SOURCE_COUNT];
	struct quadratic_f32 qFeffCoeffBoostClock[POWER_SOURCE_COUNT];
	// SECTION: Sku Reserved
	uint32_t Spare[43];
	// Padding for MMHUB - do not modify this
	uint32_t MmHubPadding[8];

};

struct smu13_boardtable_v39 {
	// SECTION: Version
	uint32_t Version; // should be unique to each board type

	// SECTION: I2C Control
	struct i2ccontrollerconfig_u8 I2cControllers[NUM_I2C_CONTROLLERS];
	// SECTION: SVI2 Board Parameters
	uint8_t  VddGfxVrMapping;  // Use VR_MAPPING* bitfields
	uint8_t  VddSocVrMapping;  // Use VR_MAPPING* bitfields
	uint8_t  VddMem0VrMapping; // Use VR_MAPPING* bitfields
	uint8_t  VddMem1VrMapping; // Use VR_MAPPING* bitfields

	union psi_sel_mask GfxUlvPhaseSheddingMask;   // set this to 1 to set PSI0/1 to 1 in ULV mode
	union psi_sel_mask SocUlvPhaseSheddingMask;   // set this to 1 to set PSI0/1 to 1 in ULV mode
	union psi_sel_mask VmempUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
	union psi_sel_mask VddioUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
	// SECTION SVI3 Board Parameters
	uint8_t  SlaveAddrMapping[SVI_PLANE_COUNT];
	uint8_t  VrPsiSupport[SVI_PLANE_COUNT];

	uint8_t  PaddingPsi[SVI_PLANE_COUNT];
	uint8_t  EnablePsi6[SVI_PLANE_COUNT]; // only applicable in SVI3
	// SECTION: Voltage Regulator Settings
	struct SviTelemetryScale_t SviTelemetryScale[SVI_PLANE_COUNT];
	uq16_16_t VoltageTelemetryRatio[SVI_PLANE_COUNT]; // This is used for VDDIO  Svi2 Div Ratio workaround. It has 16 fractional bits (Q16.16)

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
	union led_display_control LedEnableMask;

	uint8_t  LedPcie;        // GPIO number for PCIE results
	uint8_t  LedError;       // GPIO number for Error Cases
	// SECTION: Clock Spread Spectrum
	// UCLK Spread Spectrum
	uq4_4_t  UclkTrainingModeSpreadPercent; // Q4.4
	uint8_t  UclkSpreadPadding;
	uint16_t UclkSpreadFreq; // kHz
	// UCLK Spread Spectrum
	uint8_t  UclkSpreadPercent[MEM_VENDOR_COUNT];
	// FCLK Spread Spectrum
	uint8_t  FclkSpreadPadding;
	uq4_4_t  FclkSpreadPercent;  // Q4.4
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

struct smu13_smcpptable_v39 {
	struct smu13_skutable_v39 SkuTable;
	struct smu13_boardtable_v39 BoardTable;
};

#pragma pack(pop) // restore old packing

#endif
