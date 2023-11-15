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
// TODO Q2 means Qm.2, where m fills the rest of the natural width
// https://en.wikipedia.org/wiki/Q_(number_format)
// AMD.RX5700XT.8192.190616_1.rom has:
// MaxVoltageGfx/Soc at 0x12C0 and min at 0x0bb8
// 0x12C0>>2 == 1200 and 0x0bb8>>2 == 750 which are sensible values.

#pragma pack(push, 1) // bios data must use byte alignment

// pptable
#define PPTABLE_V20_SMU_VERSION  3 // Vega20
#define PPTABLE_NV10_SMU_VERSION 8 // Navi10


enum smu11_driver_if_version { //  #define SMU11_DRIVER_IF_VERSION
// this number seems to grow fast
	smu11_driver_if_version_vega20 = 0x13, // with pptable v3
	smu11_driver_if_version_navi10 = 0x33, // with pptable v8
};


#define NUM_GFXCLK_DPM_LEVELS_SMU11  16
#define NUM_SMNCLK_DPM_LEVELS        2 // Navi10
#define NUM_SOCCLK_DPM_LEVELS_SMU11  8
#define NUM_MP0CLK_DPM_LEVELS_SMU11  2

#define NUM_DCLK_DPM_LEVELS_SMU11    8
#define NUM_VCLK_DPM_LEVELS_SMU11    8
#define NUM_DCEFCLK_DPM_LEVELS_SMU11 8
#define NUM_PHYCLK_DPM_LEVELS_SMU11  8

#define NUM_DISPCLK_DPM_LEVELS_SMU11 8
#define NUM_PIXCLK_DPM_LEVELS_SMU11  8
#define NUM_UCLK_DPM_LEVELS_SMU11    4
#define NUM_MP1CLK_DPM_LEVELS_SMU11  2 // Navi10

#define NUM_ECLK_DPM_LEVELS_SMU11    8 // Vega20
#define NUM_FCLK_DPM_LEVELS_SMU11    8 // Vega20
#define NUM_XGMI_LEVELS_SMU11        2 // Vega20

#define NUM_LINK_LEVELS_SMU11        2


/*
#define PPSMC_GeminiModeNone   0 // Single GPU board
#define PPSMC_GeminiModeMaster 1 // Master GPU on a Gemini board
#define PPSMC_GeminiModeSlave  2 // Slave GPU on a Gemini board
*/

union powerplay_feature_control_smu11_19 {
	uint64_t feature_control;
	struct { uint64_t
		DPM_PREFETCHER :0-0 +1,
		DPM_GFXCLK     :1-1 +1,
		DPM_UCLK       :2-2 +1,
		DPM_SOCCLK     :3-3 +1,
		DPM_UVD        :4-4 +1,
		DPM_VCE        :5-5 +1,
		ULV            :6-6 +1,
		DPM_MP0CLK     :7-7 +1,
		DPM_LINK       :8-8 +1,
		DPM_DCEFCLK    :9-9 +1,
		DS_GFXCLK     :10-10 +1,
		DS_SOCCLK     :11-11 +1,
		DS_LCLK       :12-12 +1,
		PPT           :13-13 +1,
		TDC           :14-14 +1,
		THERMAL       :15-15 +1,
		GFX_PER_CU_CG :16-16 +1,
		RM            :17-17 +1,
		DS_DCEFCLK    :18-18 +1,
		ACDC          :19-19 +1,
		VR0HOT        :20-20 +1,
		VR1HOT        :21-21 +1,
		FW_CTF        :22-22 +1,
		LED_DISPLAY   :23-23 +1,
		FAN_CONTROL   :24-24 +1,
		GFX_EDC       :25-25 +1,
		GFXOFF        :26-26 +1,
		CG            :27-27 +1,
		DPM_FCLK      :28-28 +1,
		DS_FCLK       :29-29 +1,
		DS_MP1CLK     :30-30 +1,
		DS_MP0CLK     :31-31 +1,
		XGMI          :32-32 +1,
		ECC           :33-33 +1,
		SPARE_34      :34-34 +1,
		SPARE_35      :35-35 +1,
		SPARE_36      :36-36 +1,
		SPARE_37      :37-37 +1,
		SPARE_38      :38-38 +1,
		SPARE_39      :39-39 +1,
		SPARE_40      :40-40 +1,
		SPARE_41      :41-41 +1,
		SPARE_42      :42-42 +1,
		SPARE_43      :43-43 +1,
		SPARE_44      :44-44 +1,
		SPARE_45      :45-45 +1,
		SPARE_46      :46-46 +1,
		SPARE_47      :47-47 +1,
		SPARE_48      :48-48 +1,
		SPARE_49      :49-49 +1,
		SPARE_50      :50-50 +1,
		SPARE_51      :51-51 +1,
		SPARE_52      :52-52 +1,
		SPARE_53      :53-53 +1,
		SPARE_54      :54-54 +1,
		SPARE_55      :55-55 +1,
		SPARE_56      :56-56 +1,
		SPARE_57      :57-57 +1,
		SPARE_58      :58-58 +1,
		SPARE_59      :59-59 +1,
		SPARE_60      :60-60 +1,
		SPARE_61      :61-61 +1,
		SPARE_62      :62-62 +1,
		SPARE_63      :63-63 +1;
	};
};

union powerplay_feature_control_smu11_51 {
	uint64_t feature_control;
	struct { uint64_t
		DPM_PREFETCHER      :0-0 +1,
		DPM_GFXCLK          :1-1 +1,
		DPM_GFX_PACE        :2-2 +1,
		DPM_UCLK            :3-3 +1,
		DPM_SOCCLK          :4-4 +1,
		DPM_MP0CLK          :5-5 +1,
		DPM_LINK            :6-6 +1,
		DPM_DCEFCLK         :7-7 +1,
		MEM_VDDCI_SCALING   :8-8 +1,
		MEM_MVDD_SCALING    :9-9 +1,
		// Idle
		DS_GFXCLK           :10-10 +1,
		DS_SOCCLK           :11-11 +1,
		DS_LCLK             :12-12 +1,
		DS_DCEFCLK          :13-13 +1,
		DS_UCLK             :14-14 +1,
		GFX_ULV             :15-15 +1,
		FW_DSTATE           :16-16 +1,
		GFXOFF              :17-17 +1,
		BACO                :18-18 +1,
		VCN_PG              :19-19 +1,
		JPEG_PG             :20-20 +1,
		USB_PG              :21-21 +1,
		RSMU_SMN_CG         :22-22 +1,
		// Throttler/Response
		PPT                 :23-23 +1,
		TDC                 :24-24 +1,
		GFX_EDC             :25-25 +1,
		APCC_PLUS           :26-26 +1,
		GTHR                :27-27 +1,
		ACDC                :28-28 +1,
		VR0HOT              :29-29 +1,
		VR1HOT              :30-30 +1,
		FW_CTF              :31-31 +1,
		FAN_CONTROL         :32-32 +1,
		THERMAL             :33-33 +1,
		GFX_DCS             :34-34 +1,
		// VF
		RM                  :35-35 +1,
		LED_DISPLAY         :36-36 +1,
		// Other
		GFX_SS              :37-37 +1,
		OUT_OF_BAND_MONITOR :38-38 +1,
		TEMP_DEPENDENT_VMIN :39-39 +1,

		MMHUB_PG            :40-40 +1,
		ATHUB_PG            :41-41 +1,
		APCC_DFLL           :42-42 +1,
		SPARE_43            :43-43 +1,
		SPARE_44            :44-44 +1,
		SPARE_45            :45-45 +1,
		SPARE_46            :46-46 +1,
		SPARE_47            :47-47 +1,
		SPARE_48            :48-48 +1,
		SPARE_49            :49-49 +1,
		SPARE_50            :50-50 +1,
		SPARE_51            :51-51 +1,
		SPARE_52            :52-52 +1,
		SPARE_53            :53-53 +1,
		SPARE_54            :54-54 +1,
		SPARE_55            :55-55 +1,
		SPARE_56            :56-56 +1,
		SPARE_57            :57-57 +1,
		SPARE_58            :58-58 +1,
		SPARE_59            :59-59 +1,
		SPARE_60            :60-60 +1,
		SPARE_61            :61-61 +1,
		SPARE_62            :62-62 +1,
		SPARE_63            :63-63 +1;
	};
};





union dpm_debug_override_smu11_19 {
	uint32_t dpm_debug_override_flags;
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
union dpm_debug_override_smu11_51 {
	uint32_t dpm_debug_override_flags;
	struct { uint32_t
		disable_socclk_pid               :0-0 +1,
		disable_uclk_pid                 :1-1 +1,
		disable_volt_link_vcn_socclk     :2-2 +1,
		enable_freq_link_vclk_socclk     :3-3 +1,
		enable_freq_link_dclk_socclk     :4-4 +1,
		enable_freq_link_gfxclk_socclk   :5-5 +1,
		enable_freq_link_gfxclk_uclk     :6-6 +1,
		disable_volt_link_dce_socclk     :7-7 +1,
		disable_volt_link_mp0_socclk     :8-8 +1,
		disable_dfll_pll_shutdown        :9-9 +1,
		disable_memory_temperature_read :10-10 +1,
		reserved                        :31-11 +1;
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

enum SMU11_PPT3_PPCLK  {
	SMU11_PPT3_PPCLK_GFXCLK  = 0,
	SMU11_PPT3_PPCLK_VCLK    = 1,
	SMU11_PPT3_PPCLK_DCLK    = 2,
	SMU11_PPT3_PPCLK_ECLK    = 3,
	SMU11_PPT3_PPCLK_SOCCLK  = 4,
	SMU11_PPT3_PPCLK_UCLK    = 5,
	SMU11_PPT3_PPCLK_DCEFCLK = 6,
	SMU11_PPT3_PPCLK_DISPCLK = 7,
	SMU11_PPT3_PPCLK_PIXCLK  = 8,
	SMU11_PPT3_PPCLK_PHYCLK  = 9,
	SMU11_PPT3_PPCLK_FCLK   = 10,
	SMU11_PPT3_PPCLK_COUNT  = 11,
};
enum SMU11_PPT8_PPCLK {
	SMU11_PPT8_PPCLK_GFXCLK  = 0,
	SMU11_PPT8_PPCLK_SOCCLK  = 1,
	SMU11_PPT8_PPCLK_UCLK    = 2,
	SMU11_PPT8_PPCLK_DCLK    = 3,
	SMU11_PPT8_PPCLK_VCLK    = 4,
	SMU11_PPT8_PPCLK_DCEFCLK = 5,
	SMU11_PPT8_PPCLK_DISPCLK = 6,
	SMU11_PPT8_PPCLK_PIXCLK  = 7,
	SMU11_PPT8_PPCLK_PHYCLK  = 8,
	SMU11_PPT8_PPCLK_COUNT   = 9,
};

enum VOLTAGE_MODE_e:uint8_t {
	VOLTAGE_MODE_AVFS    = 0, // AVFS only
	VOLTAGE_MODE_AVFS_SS = 1, // min(AVS,SS)
	VOLTAGE_MODE_SS      = 2, // SS only
	VOLTAGE_MODE_COUNT   = 3,
};


enum AVFS_VOLTAGE_TYPE_e {
	AVFS_VOLTAGE_GFX   = 0,
	AVFS_VOLTAGE_SOC   = 1,
	AVFS_VOLTAGE_COUNT = 2,
};


//typedef struct dpm_descriptor_smu11 DpmDescriptor_t;

struct dpm_descriptor_smu11 {
	enum VOLTAGE_MODE_e VoltageMode;
	uint8_t  SnapToDiscrete;    // 0 - Fine grained DPM, 1 - Discrete DPM
	uint8_t  NumDiscreteLevels; // Set to 2 (Fmin, Fmax) when using fine grained  DPM, otherwise set to # discrete levels used
	uint8_t  padding;
	struct linear_f32 ConversionToAvfsClk; // Transfer function to AVFS Clock (GHz->GHz)
	struct quadratic_f32 slowslow_curve;   // Slow-slow curve (GHz->V)
};



struct smu11_pptable_v3_i2c_u32 {
	struct i2ccontrollerconfig_u32 i2ccontroller_vr_gfx;
	struct i2ccontrollerconfig_u32 i2ccontroller_vr_soc;
	struct i2ccontrollerconfig_u32 i2ccontroller_vr_vddci;
	struct i2ccontrollerconfig_u32 i2ccontroller_vr_mvdd;
	struct i2ccontrollerconfig_u32 i2ccontroller_liquid_0;
	struct i2ccontrollerconfig_u32 i2ccontroller_liquid_1;
	struct i2ccontrollerconfig_u32 i2ccontroller_plx;
};
struct smu11_pptable_v8_i2c_u8mixed {
	struct i2ccontrollerconfig_u8_mixed i2ccontroller_vr_gfx;
	struct i2ccontrollerconfig_u8_mixed i2ccontroller_vr_soc;
	struct i2ccontrollerconfig_u8_mixed i2ccontroller_vr_vddci;
	struct i2ccontrollerconfig_u8_mixed i2ccontroller_vr_mvdd;
	struct i2ccontrollerconfig_u8_mixed i2ccontroller_liquid_0;
	struct i2ccontrollerconfig_u8_mixed i2ccontroller_liquid_1;
	struct i2ccontrollerconfig_u8_mixed i2ccontroller_plx;
	struct i2ccontrollerconfig_u8_mixed i2ccontroller_spare;
};



struct smu11_smcpptable_v3 { // Vega20
	// copied comments from smc_smu11_pptable_v8
	uint32_t Version;

	union powerplay_feature_control_smu11_19 features;

	// SECTION: Infrastructure Limits
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
	uint16_t TdcLimitSoc;    // Amps
	uint16_t TdcLimitSocTau; // Time constant of LPF in ms
	uint16_t TdcLimitGfx;    // Amps
	uint16_t TdcLimitGfxTau; // Time constant of LPF in ms


	uint16_t TedgeLimit;    // Celcius
	uint16_t ThotspotLimit; // Celcius
	uint16_t ThbmLimit;     // Celcius
	uint16_t Tvr_gfxLimit;  // Celcius
	uint16_t Tliquid1Limit; // Celcius
	uint16_t Tliquid2Limit; // Celcius
	uint16_t TplxLimit;     // Celcius
	uint32_t FitLimit;      // Failures in time (failures per million parts over the defined lifetime)

	uint16_t PpmPowerLimit; // Switch this this power limit when temperature is above PpmTempThreshold
	uint16_t PpmTemperatureThreshold;

	uint8_t  MemoryOnPackage;
	uint8_t  padding8_limits;
	uint16_t Tvr_SocLimit; // Celcius

	// SECTION: ULV Settings
	uint16_t UlvVoltageOffsetSoc; // In mV(Q2)
	uint16_t UlvVoltageOffsetGfx; // In mV(Q2)

	uint8_t  UlvSmnclkDid; // DID for ULV mode. 0 means CLK will not be modified in ULV.
	uint8_t  UlvMp1clkDid; // DID for ULV mode. 0 means CLK will not be modified in ULV.
	uint8_t  UlvGfxclkBypass; // 1 to turn off/bypass Gfxclk during ULV, 0 to leave Gfxclk on during ULV
	uint8_t  Padding234;


	// SECTION: Voltage Control Parameters
	uint16_t MinVoltageGfx; // In mV(Q2) Minimum Voltage ("Vmin") of VDD_GFX
	uint16_t MinVoltageSoc; // In mV(Q2) Minimum Voltage ("Vmin") of VDD_SOC
	uint16_t MaxVoltageGfx; // In mV(Q2) Maximum Voltage allowable of VDD_GFX
	uint16_t MaxVoltageSoc; // In mV(Q2) Maximum Voltage allowable of VDD_SOC

	// Q8.8?
	uint16_t LoadLineResistanceGfx; // In mOhms with 8 fractional bits
	uint16_t LoadLineResistanceSoc; // In mOhms with 8 fractional bits

	//SECTION: DPM Config 1
	struct dpm_descriptor_smu11 DpmDescriptor[SMU11_PPT3_PPCLK_COUNT];

	uint16_t FreqTableGfx[NUM_GFXCLK_DPM_LEVELS_SMU11];      // In MHz
	uint16_t FreqTableVclk[NUM_VCLK_DPM_LEVELS_SMU11];       // In MHz
	uint16_t FreqTableDclk[NUM_DCLK_DPM_LEVELS_SMU11];       // In MHz
	uint16_t FreqTableEclk[NUM_ECLK_DPM_LEVELS_SMU11];       // In MHz
	uint16_t FreqTableSocclk[NUM_SOCCLK_DPM_LEVELS_SMU11];   // In MHz
	uint16_t FreqTableUclk[NUM_UCLK_DPM_LEVELS_SMU11];       // In MHz
	uint16_t FreqTableFclk[NUM_FCLK_DPM_LEVELS_SMU11];       // In MHz
	uint16_t FreqTableDcefclk[NUM_DCEFCLK_DPM_LEVELS_SMU11]; // In MHz
	uint16_t FreqTableDispclk[NUM_DISPCLK_DPM_LEVELS_SMU11]; // In MHz
	uint16_t FreqTablePixclk[NUM_PIXCLK_DPM_LEVELS_SMU11];   // In MHz
	uint16_t FreqTablePhyclk[NUM_PHYCLK_DPM_LEVELS_SMU11];   // In MHz

	uint16_t DcModeMaxFreq[SMU11_PPT3_PPCLK_COUNT]; // In MHz
	uint16_t Padding8_Clks;

	// SECTION: DPM Config 2
	uint16_t Mp0clkFreq[NUM_MP0CLK_DPM_LEVELS_SMU11];    // In MHz
	uint16_t Mp0DpmVoltage[NUM_MP0CLK_DPM_LEVELS_SMU11]; // mV(Q2)


	uint16_t GfxclkFidle;    // in MHz
	uint16_t GfxclkSlewRate; // for PLL babystepping???
	uint16_t CksEnableFreq;
	uint16_t Padding789;
	struct quadratic_f32 CksVoltageOffset;
	uint8_t  Padding567[4];
	uint16_t GfxclkDsMaxFreq; // in Mhz
	uint8_t  GfxclkSource;    // 0 = PLL, 1 = DFLL
	uint8_t  Padding456;

	uint8_t  LowestUclkReservedForUlv; // Set this to 1 if UCLK DPM0 is reserved for ULV-mode only
	uint8_t  Padding8_Uclk[3];

	// Link DPM Settings
	uint8_t  PcieGenSpeed[NUM_LINK_LEVELS_SMU11];  // < 0:PciE-gen1 1:PciE-gen2 2: PciE-gen3 3:PciE-gen4
	uint8_t  PcieLaneCount[NUM_LINK_LEVELS_SMU11]; // < 1=x1, 2=x2, 3=x4, 4=x8, 5=x12, 6=x16
	uint16_t LclkFreq[NUM_LINK_LEVELS_SMU11];

	// GFXCLK Thermal DPM (formerly 'Boost' Settings
	uint16_t EnableTdpm;
	uint16_t TdpmHighHystTemperature;
	uint16_t TdpmLowHystTemperature;
	uint16_t GfxclkFreqHighTempLimit; // High limit on GFXCLK when temperature is high, for reliability.

	// SECTION: Fan Control
	uint16_t FanStopTemp;  // Celcius
	uint16_t FanStartTemp; // Celcius

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

	// The following are AFC override parameters. Leave at 0 to use FW defaults.
	int16_t  FuzzyFan_ErrorSetDelta;
	int16_t  FuzzyFan_ErrorRateSetDelta;
	int16_t  FuzzyFan_PwmSetDelta;
	uint16_t FuzzyFan_Reserved;


	// SECTION: AVFS
	// Overrides
	uint8_t  OverrideAvfsGb[AVFS_VOLTAGE_COUNT];
	uint8_t  Padding8_Avfs[2];

	struct quadratic_f32 qAvfsGb[AVFS_VOLTAGE_COUNT]; // GHz->V Override of fused curve
	struct droop_f32  dBtcGbGfxCksOn;
	struct droop_f32  dBtcGbGfxCksOff;
	struct droop_f32  dBtcGbGfxAfll; // dfll?
	struct droop_f32  dBtcGbSoc;     // GHz->V BtcGb
	struct linear_f32 qAgingGb[AVFS_VOLTAGE_COUNT]; // GHz->V

	struct quadratic_f32 qStaticVoltageOffset[AVFS_VOLTAGE_COUNT]; // GHz->V

	uint16_t DcTol[AVFS_VOLTAGE_COUNT]; // mV(Q2)

	uint8_t  DcBtcEnabled[AVFS_VOLTAGE_COUNT];
	uint8_t  Padding8_GfxBtc[2];

	int16_t  DcBtcMin[AVFS_VOLTAGE_COUNT]; // is this actually signed? mV Q2
	uint16_t DcBtcMax[AVFS_VOLTAGE_COUNT]; // mV(Q2)

	uint8_t  XgmiLinkSpeed[NUM_XGMI_LEVELS_SMU11];
	uint8_t  XgmiLinkWidth[NUM_XGMI_LEVELS_SMU11];
	uint16_t XgmiFclkFreq[NUM_XGMI_LEVELS_SMU11];
	uint16_t XgmiUclkFreq[NUM_XGMI_LEVELS_SMU11];
	uint16_t XgmiSocclkFreq[NUM_XGMI_LEVELS_SMU11];
	uint16_t XgmiSocVoltage[NUM_XGMI_LEVELS_SMU11];


	// SECTION: Advanced Options
	union  dpm_debug_override_smu11_19 DebugOverrides;
	struct quadratic_f32 ReservedEquation0;
	struct quadratic_f32 ReservedEquation1;
	struct quadratic_f32 ReservedEquation2;
	struct quadratic_f32 ReservedEquation3;

	uint16_t MinVoltageUlvGfx; // In mV(Q2)  Minimum Voltage ("Vmin") of VDD_GFX in ULV mode
	uint16_t MinVoltageUlvSoc; // In mV(Q2)  Minimum Voltage ("Vmin") of VDD_SOC in ULV mode

	// APCC Settings
	uint16_t MGpuFanBoostLimitRpm;
	uint16_t padding16_Fan;

	uint16_t FanGainVrMem0;
	uint16_t FanGainVrMem1;

	uint16_t DcBtcGb[AVFS_VOLTAGE_COUNT];


	uint32_t Reserved[11];
	uint32_t Padding32[3];

	// SVI2 Board Parameters
	uint16_t MaxVoltageStepGfx; // In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value.
	uint16_t MaxVoltageStepSoc; // In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value.

	uint8_t  VddGfxVrMapping; // Use VR_MAPPING* bitfields
	uint8_t  VddSocVrMapping;
	uint8_t  VddMem0VrMapping;
	uint8_t  VddMem1VrMapping;

	uint8_t  GfxUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
	uint8_t  SocUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
	uint8_t  ExternalSensorPresent; // External RDI connected to TMON (aka TEMP IN)
	uint8_t  Padding8_V;


	uint16_t GfxMaxCurrent; // in Amps
	int8_t   GfxOffset;     // in Amps
	uint8_t  Padding_TelemetryGfx;

	uint16_t SocMaxCurrent; // in Amps
	int8_t   SocOffset;     // in Amps
	uint8_t  Padding_TelemetrySoc;

	uint16_t Mem0MaxCurrent; // in Amps
	int8_t   Mem0Offset;     // in Amps
	uint8_t  Padding_TelemetryMem0;

	uint16_t Mem1MaxCurrent; // in Amps
	int8_t   Mem1Offset;     // in Amps
	uint8_t  Padding_TelemetryMem1;

	uint8_t  AcDcGpio;       // GPIO pin configured for AC/DC switching
	uint8_t  AcDcPolarity;   // GPIO polarity for AC/DC switching
	uint8_t  VR0HotGpio;     // GPIO pin configured for VR0 HOT event
	uint8_t  VR0HotPolarity; // GPIO polarity for VR0 HOT event

	uint8_t  VR1HotGpio;     // GPIO pin configured for VR1 HOT event
	uint8_t  VR1HotPolarity; // GPIO polarity for VR1 HOT event
	uint8_t  Padding1;       // GPIO pin configured for GTHR Event
	uint8_t  Padding2;       // replace GPIO polarity for GTHR


	// LED Display Settings
	uint8_t  LedPin0; // GPIO number for LedPin[0]
	uint8_t  LedPin1; // GPIO number for LedPin[1]
	uint8_t  LedPin2; // GPIO number for LedPin[2]
	uint8_t  padding8_4;


	uint8_t  PllGfxclkSpreadEnabled; // on or off
	uint8_t  PllGfxclkSpreadPercent; // Q4.4
	uint16_t PllGfxclkSpreadFreq;    // kHz

	uint8_t  UclkSpreadEnabled; // on or off
	uint8_t  UclkSpreadPercent; // Q4.4
	uint16_t UclkSpreadFreq;    // kHz

	uint8_t  FclkSpreadEnabled; // on or off
	uint8_t  FclkSpreadPercent; // Q4.4
	uint16_t FclkSpreadFreq;    // kHz

	uint8_t  FllGfxclkSpreadEnabled; // on or off
	uint8_t  FllGfxclkSpreadPercent; // Q4.4
	uint16_t FllGfxclkSpreadFreq;    // kHz

	union {
		struct i2ccontrollerconfig_u32 I2cControllers[
			I2C_CONTROLLER_NAME_COUNT_SMU11_PPT3
		];
		struct smu11_pptable_v3_i2c_u32 i2c_unroll;
	};

	uint32_t BoardReserved[10];

	uint32_t MmHubPadding[8];
};


struct smu11_smcpptable_v8 { // Navi10
	uint32_t Version;

	union powerplay_feature_control_smu11_51 features;

	// SECTION: Infrastructure Limits
	uint16_t SocketPowerLimitAc[PPT_THROTTLER_COUNT];
	uint16_t SocketPowerLimitAcTau[PPT_THROTTLER_COUNT];
	uint16_t SocketPowerLimitDc[PPT_THROTTLER_COUNT];
	uint16_t SocketPowerLimitDcTau[PPT_THROTTLER_COUNT];

	uint16_t TdcLimitSoc;    // Amps
	uint16_t TdcLimitSocTau; // Time constant of LPF in ms
	uint16_t TdcLimitGfx;    // Amps
	uint16_t TdcLimitGfxTau; // Time constant of LPF in ms

	uint16_t TedgeLimit;    // Celcius
	uint16_t ThotspotLimit; // Celcius
	uint16_t TmemLimit;     // Celcius
	uint16_t Tvr_gfxLimit;  // Celcius
	uint16_t Tvr_mem0Limit; // Celcius
	uint16_t Tvr_mem1Limit; // Celcius
	uint16_t Tvr_socLimit;  // Celcius
	uint16_t Tliquid0Limit; // Celcius
	uint16_t Tliquid1Limit; // Celcius
	uint16_t TplxLimit;     // Celcius
	uint32_t FitLimit;      // Failures in time (failures per million parts over the defined lifetime)

	uint16_t PpmPowerLimit; // Switch this this power limit when temperature is above PpmTempThreshold
	uint16_t PpmTemperatureThreshold;

	// SECTION: Throttler settings
	uint32_t ThrottlerControlMask; // See Throtter masks defines

	// SECTION: FW DSTATE Settings
	uint32_t FwDStateMask; // See FW DState masks defines

	// SECTION: ULV Settings
	uint16_t UlvVoltageOffsetSoc; // In mV(Q2)
	uint16_t UlvVoltageOffsetGfx; // In mV(Q2)

	uint8_t  GceaLinkMgrIdleThreshold; // Set by SMU FW during enablment of SOC_ULV. Controls delay for GFX SDP port disconnection during idle events
	uint8_t  paddingRlcUlvParams[3];

	uint8_t  UlvSmnclkDid; // DID for ULV mode. 0 means CLK will not be modified in ULV.
	uint8_t  UlvMp1clkDid; // DID for ULV mode. 0 means CLK will not be modified in ULV.
	uint8_t  UlvGfxclkBypass; // 1 to turn off/bypass Gfxclk during ULV, 0 to leave Gfxclk on during ULV
	uint8_t  Padding234;

	uint16_t MinVoltageUlvGfx; // In mV(Q2)  Minimum Voltage ("Vmin") of VDD_GFX in ULV mode
	uint16_t MinVoltageUlvSoc; // In mV(Q2)  Minimum Voltage ("Vmin") of VDD_SOC in ULV mode


	// SECTION: Voltage Control Parameters
	uint16_t MinVoltageGfx; // In mV(Q2) Minimum Voltage ("Vmin") of VDD_GFX
	uint16_t MinVoltageSoc; // In mV(Q2) Minimum Voltage ("Vmin") of VDD_SOC
	uint16_t MaxVoltageGfx; // In mV(Q2) Maximum Voltage allowable of VDD_GFX
	uint16_t MaxVoltageSoc; // In mV(Q2) Maximum Voltage allowable of VDD_SOC

	uint16_t LoadLineResistanceGfx; // In mOhms with 8 fractional bits
	uint16_t LoadLineResistanceSoc; // In mOhms with 8 fractional bits

	//SECTION: DPM Config 1
	struct dpm_descriptor_smu11 DpmDescriptor[SMU11_PPT8_PPCLK_COUNT];

	uint16_t FreqTableGfx[NUM_GFXCLK_DPM_LEVELS_SMU11];      // In MHz
	uint16_t FreqTableVclk[NUM_VCLK_DPM_LEVELS_SMU11];       // In MHz
	uint16_t FreqTableDclk[NUM_DCLK_DPM_LEVELS_SMU11];       // In MHz
	uint16_t FreqTableSocclk[NUM_SOCCLK_DPM_LEVELS_SMU11];   // In MHz
	uint16_t FreqTableUclk[NUM_UCLK_DPM_LEVELS_SMU11];       // In MHz
	uint16_t FreqTableDcefclk[NUM_DCEFCLK_DPM_LEVELS_SMU11]; // In MHz
	uint16_t FreqTableDispclk[NUM_DISPCLK_DPM_LEVELS_SMU11]; // In MHz
	uint16_t FreqTablePixclk[NUM_PIXCLK_DPM_LEVELS_SMU11];   // In MHz
	uint16_t FreqTablePhyclk[NUM_PHYCLK_DPM_LEVELS_SMU11];   // In MHz
	uint32_t Paddingclks[16];

	uint16_t DcModeMaxFreq[SMU11_PPT8_PPCLK_COUNT]; // In MHz
	uint16_t Padding8_Clks;

	uint8_t  FreqTableUclkDiv[NUM_UCLK_DPM_LEVELS_SMU11]; // 0:Div-1, 1:Div-1/2, 2:Div-1/4, 3:Div-1/8

	// SECTION: DPM Config 2
	uint16_t Mp0clkFreq[NUM_MP0CLK_DPM_LEVELS_SMU11];    // in MHz
	uint16_t Mp0DpmVoltage[NUM_MP0CLK_DPM_LEVELS_SMU11]; // mV(Q2)
	uint16_t MemVddciVoltage[NUM_UCLK_DPM_LEVELS_SMU11]; // mV(Q2)
	uint16_t MemMvddVoltage[NUM_UCLK_DPM_LEVELS_SMU11];  // mV(Q2)
	// GFXCLK DPM
	uint16_t GfxclkFgfxoffEntry; // in Mhz
	uint16_t GfxclkFinit;        // in Mhz
	uint16_t GfxclkFidle;        // in MHz
	uint16_t GfxclkSlewRate;     // for PLL babystepping???
	uint16_t GfxclkFopt;         // in Mhz
	uint8_t  Padding567[2];
	uint16_t GfxclkDsMaxFreq;    // in MHz
	uint8_t  GfxclkSource;       // 0 = PLL, 1 = DFLL
	uint8_t  Padding456;

	// UCLK section
	uint8_t  LowestUclkReservedForUlv; // Set this to 1 if UCLK DPM0 is reserved for ULV-mode only
	uint8_t  paddingUclk[3];

	uint8_t  MemoryType; // 0-GDDR6, 1-HBM
	uint8_t  MemoryChannels;
	uint8_t  PaddingMem[2];

	// Link DPM Settings
	uint8_t  PcieGenSpeed[NUM_LINK_LEVELS_SMU11]; // < 0:PciE-gen1 1:PciE-gen2 2:PciE-gen3 3:PciE-gen4
	uint8_t  PcieLaneCount[NUM_LINK_LEVELS_SMU11]; // < 1=x1, 2=x2, 3=x4, 4=x8, 5=x12, 6=x16
	uint16_t LclkFreq[NUM_LINK_LEVELS_SMU11];

	// GFXCLK Thermal DPM (formerly 'Boost' Settings)
	uint16_t EnableTdpm;
	uint16_t TdpmHighHystTemperature;
	uint16_t TdpmLowHystTemperature;
	uint16_t GfxclkFreqHighTempLimit; // High limit on GFXCLK when temperature is high, for reliability.

	// SECTION: Fan Control
	uint16_t FanStopTemp;  // Celcius
	uint16_t FanStartTemp; // Celcius

	uint16_t FanGainEdge;
	uint16_t FanGainHotspot;
	uint16_t FanGainLiquid0;
	uint16_t FanGainLiquid1;
	uint16_t FanGainVrGfx;
	uint16_t FanGainVrSoc;
	uint16_t FanGainVrMem0;
	uint16_t FanGainVrMem1;
	uint16_t FanGainPlx;
	uint16_t FanGainMem;
	uint16_t FanPwmMin;
	uint16_t FanAcousticLimitRpm;
	uint16_t FanThrottlingRpm;
	uint16_t FanMaximumRpm;
	uint16_t FanTargetTemperature;
	uint16_t FanTargetGfxclk;
	uint8_t  FanTempInputSelect;
	uint8_t  FanPadding;
	uint8_t  FanZeroRpmEnable;
	uint8_t  FanTachEdgePerRev;

	// The following are AFC override parameters. Leave at 0 to use FW defaults.
	int16_t  FuzzyFan_ErrorSetDelta;
	int16_t  FuzzyFan_ErrorRateSetDelta;
	int16_t  FuzzyFan_PwmSetDelta;
	uint16_t FuzzyFan_Reserved;


	// SECTION: AVFS
	// Overrides
	uint8_t  OverrideAvfsGb[AVFS_VOLTAGE_COUNT];
	uint8_t  Padding8_Avfs[2];

	struct quadratic_f32 qAvfsGb[AVFS_VOLTAGE_COUNT]; // GHz->V Override of fused curve
	struct droop_f32  dBtcGbGfxPll;  // GHz->V BtcGb
	struct droop_f32  dBtcGbGfxDfll; // GHz->V BtcGb
	struct droop_f32  dBtcGbSoc;     // GHz->V BtcGb
	struct linear_f32 qAgingGb[AVFS_VOLTAGE_COUNT]; // GHz->V

	struct quadratic_f32 qStaticVoltageOffset[AVFS_VOLTAGE_COUNT]; // GHz->V

	uint16_t DcTol[AVFS_VOLTAGE_COUNT]; // mV Q2

	uint8_t  DcBtcEnabled[AVFS_VOLTAGE_COUNT];
	uint8_t  Padding8_GfxBtc[2];

	uint16_t DcBtcMin[AVFS_VOLTAGE_COUNT]; // mV Q2
	uint16_t DcBtcMax[AVFS_VOLTAGE_COUNT]; // mV Q2

	// SECTION: Advanced Options
	uint32_t DebugOverrides;
	struct quadratic_f32 ReservedEquation0;
	struct quadratic_f32 ReservedEquation1;
	struct quadratic_f32 ReservedEquation2;
	struct quadratic_f32 ReservedEquation3;

	// Total Power configuration, use defines from PwrConfig_e
	uint8_t  TotalPowerConfig; // 0-TDP, 1-TGP, 2-TCP Estimated, 3-TCP Measured
	uint8_t  TotalPowerSpare1;
	uint16_t TotalPowerSpare2;

	// APCC Settings
	uint16_t PccThresholdLow;
	uint16_t PccThresholdHigh;
	uint32_t MGpuFanBoostLimitRpm;
	uint32_t PaddingAPCC[5];

	// Temperature Dependent Vmin
	uint16_t VDDGFX_TVmin;       //Celcius
	uint16_t VDDSOC_TVmin;       //Celcius
	uint16_t VDDGFX_Vmin_HiTemp; // mV Q2
	uint16_t VDDGFX_Vmin_LoTemp; // mV Q2
	uint16_t VDDSOC_Vmin_HiTemp; // mV Q2
	uint16_t VDDSOC_Vmin_LoTemp; // mV Q2

	uint16_t VDDGFX_TVminHystersis; // Celcius
	uint16_t VDDSOC_TVminHystersis; // Celcius

	// BTC Setting
	uint32_t BtcConfig;

	uint16_t SsFmin[10]; // PPtable value to function similar to VFTFmin for SS Curve; Size is SMU11_PPT8_PPCLK_COUNT rounded to nearest multiple of 2
	uint16_t DcBtcGb[AVFS_VOLTAGE_COUNT];

	// SECTION: Board Reserved
	uint32_t Reserved[8];

	// SECTION: BOARD PARAMETERS
	// I2C Control
	union {
		struct i2ccontrollerconfig_u8_mixed I2cControllers[
			I2C_CONTROLLER_NAME_COUNT_SMU11_PPT8
		];
		struct smu11_pptable_v8_i2c_u8mixed i2c_unroll;
	};

	// SVI2 Board Parameters
	uint16_t MaxVoltageStepGfx; // In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value.
	uint16_t MaxVoltageStepSoc; // In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value.

	uint8_t  VddGfxVrMapping;  // Use VR_MAPPING* bitfields
	uint8_t  VddSocVrMapping;  // Use VR_MAPPING* bitfields
	uint8_t  VddMem0VrMapping; // Use VR_MAPPING* bitfields
	uint8_t  VddMem1VrMapping; // Use VR_MAPPING* bitfields

	uint8_t  GfxUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
	uint8_t  SocUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
	uint8_t  ExternalSensorPresent;   // External RDI connected to TMON (aka TEMP IN)
	uint8_t  Padding8_V;

	// Telemetry Settings
	uint16_t GfxMaxCurrent; // in Amps
	int8_t   GfxOffset;     // in Amps
	uint8_t  Padding_TelemetryGfx;

	uint16_t SocMaxCurrent; // in Amps
	int8_t   SocOffset;     // in Amps
	uint8_t  Padding_TelemetrySoc;

	uint16_t Mem0MaxCurrent; // in Amps
	int8_t   Mem0Offset;     // in Amps
	uint8_t  Padding_TelemetryMem0;

	uint16_t Mem1MaxCurrent; // in Amps
	int8_t   Mem1Offset;     // in Amps
	uint8_t  Padding_TelemetryMem1;

	// GPIO Settings
	uint8_t  AcDcGpio;       // GPIO pin configured for AC/DC switching
	uint8_t  AcDcPolarity;   // GPIO polarity for AC/DC switching
	uint8_t  VR0HotGpio;     // GPIO pin configured for VR0 HOT event
	uint8_t  VR0HotPolarity; // GPIO polarity for VR0 HOT event

	uint8_t  VR1HotGpio;     // GPIO pin configured for VR1 HOT event
	uint8_t  VR1HotPolarity; // GPIO polarity for VR1 HOT event
	uint8_t  GthrGpio;       // GPIO pin configured for GTHR Event
	uint8_t  GthrPolarity;   // replace GPIO polarity for GTHR

	// LED Display Settings
	uint8_t  LedPin0; // GPIO number for LedPin[0]
	uint8_t  LedPin1; // GPIO number for LedPin[1]
	uint8_t  LedPin2; // GPIO number for LedPin[2]
	uint8_t  padding8_4;

	// GFXCLK PLL Spread Spectrum
	uint8_t  PllGfxclkSpreadEnabled; // on or off
	uint8_t  PllGfxclkSpreadPercent; // Q4.4
	uint16_t PllGfxclkSpreadFreq;    // kHz

	// GFXCLK DFLL Spread Spectrum
	uint8_t  DfllGfxclkSpreadEnabled; // on or off
	uint8_t  DfllGfxclkSpreadPercent; // Q4.4
	uint16_t DfllGfxclkSpreadFreq;    // kHz

	// UCLK Spread Spectrum
	uint8_t  UclkSpreadEnabled; // on or off
	uint8_t  UclkSpreadPercent; // Q4.4
	uint16_t UclkSpreadFreq;    // kHz

	// SOCCLK Spread Spectrum
	uint8_t  SoclkSpreadEnabled;  // on or off
	uint8_t  SocclkSpreadPercent; // Q4.4
	uint16_t SocclkSpreadFreq;    // kHz

	// Total board power
	uint16_t TotalBoardPower; // Only needed for TCP Estimated case, where TCP = TGP+Total Board Power
	uint16_t BoardPadding;

	// Mvdd Svi2 Div Ratio Setting
	uint32_t MvddRatio; // This is used for MVDD Vid workaround. It has 16 fractional bits (Q16.16)

	uint8_t  RenesesLoadLineEnabled;
	uint8_t  GfxLoadlineResistance;
	uint8_t  SocLoadlineResistance;
	uint8_t  Padding8_Loadline;

	uint32_t BoardReserved[8];

	// Padding for MMHUB - do not modify this
	uint32_t MmHubPadding[8]; // SMU internal use

};

#pragma pack(pop) // restore old packing

#endif
