#ifndef SMU11_DRIVER_IF_H
#define SMU11_DRIVER_IF_H
#pragma pack(push, 1) // bios data must use byte alignment

// pptable
#define PPTABLE_V20_SMU_VERSION  3 // Vega20
#define PPTABLE_NV10_SMU_VERSION 8 // Navi10
#define PPTABLE_Sienna_Cichlid_SMU_VERSION 7 // Navi21


enum smu11_driver_if_version { //  #define SMU11_DRIVER_IF_VERSION
// this number seems to grow fast
	smu11_driver_if_version_vega20 = 0x13, // with pptable v3
	smu11_driver_if_version_navi10 = 0x33, // with pptable v8
	smu11_driver_if_version_navi21 = 0x40, // Sienna Cichlid; pptable v7
};


#define NUM_GFXCLK_DPM_LEVELS_SMU11  16
#define NUM_SMNCLK_DPM_LEVELS_SMU11  2 // Navi10
#define NUM_SOCCLK_DPM_LEVELS_SMU11  8
#define NUM_MP0CLK_DPM_LEVELS_SMU11  2

#define NUM_DCLK_DPM_LEVELS_SMU11    8
#define NUM_VCLK_DPM_LEVELS_SMU11    8
#define NUM_DCEFCLK_DPM_LEVELS_SMU11 8
#define NUM_PHYCLK_DPM_LEVELS_SMU11  8

#define NUM_DISPCLK_DPM_LEVELS_SMU11 8
#define NUM_PIXCLK_DPM_LEVELS_SMU11  8
#define NUM_UCLK_DPM_LEVELS_SMU11    4
#define NUM_MP1CLK_DPM_LEVELS_SMU11  2 // Navi10, Navi21

#define NUM_ECLK_DPM_LEVELS_SMU11    8 // Vega20, Navi21
#define NUM_FCLK_DPM_LEVELS_SMU11    8 // Vega20
#define NUM_XGMI_LEVELS_SMU11        2 // Vega20, Navi21

#define NUM_XGMI_PSTATE_LEVELS_SMU11 4 // Navi21
#define NUM_OD_FAN_MAX_POINTS_SMU11  6 // Navi21
#define NUM_DTBCLK_DPM_LEVELS_SMU11  8 // Navi21
#define RLC_PACE_TABLE_NUM_LEVELS_SMU11 16 // Navi21

#define NUM_LINK_LEVELS_SMU11        2



#define NUM_I2C_CONTROLLERS_SMU11_0_0  8
#define NUM_I2C_CONTROLLERS_SMU11_0_7 16

#define I2C_CONTROLLER_ENABLED     1
#define I2C_CONTROLLER_DISABLED    0

/*
#define PPSMC_GeminiModeNone   0 // Single GPU board
#define PPSMC_GeminiModeMaster 1 // Master GPU on a Gemini board
#define PPSMC_GeminiModeSlave  2 // Slave GPU on a Gemini board
*/

union powerplay_feature_control_smu11_0x13 {
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
union powerplay_feature_control_smu11_0x33 {
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
union powerplay_feature_control_smu11_0x40 {
	uint64_t feature_control;
	struct { uint64_t
		// DPM
		DPM_PREFETCHER       :0-0 +1,
		DPM_GFXCLK           :1-1 +1,
		DPM_GFX_GPO          :2-2 +1,
		DPM_UCLK             :3-3 +1,
		DPM_FCLK             :4-4 +1,
		DPM_SOCCLK           :5-5 +1,
		DPM_MP0CLK           :6-6 +1,
		DPM_LINK             :7-7 +1,
		DPM_DCEFCLK          :8-8 +1,
		DPM_XGMI             :9-9 +1,
		MEM_VDDCI_SCALING   :10-10 +1,
		MEM_MVDD_SCALING    :11-11 +1,

		//Idle
		DS_GFXCLK           :12-12 +1,
		DS_SOCCLK           :13-13 +1,
		DS_FCLK             :14-14 +1,
		DS_LCLK             :15-15 +1,
		DS_DCEFCLK          :16-16 +1,
		DS_UCLK             :17-17 +1,
		GFX_ULV             :18-18 +1,
		FW_DSTATE           :19-19 +1,
		GFXOFF              :20-20 +1,
		BACO                :21-21 +1,
		MM_DPM_PG           :22-22 +1,
		SPARE_23            :23-23 +1,
		//Throttler/Response
		PPT                 :24-24 +1,
		TDC                 :25-25 +1,
		APCC_PLUS           :26-26 +1,
		GTHR                :27-27 +1,
		ACDC                :28-28 +1,
		VR0HOT              :29-29 +1,
		VR1HOT              :30-30 +1,
		FW_CTF              :31-31 +1,
		FAN_CONTROL         :32-32 +1,
		THERMAL             :33-33 +1,
		GFX_DCS             :34-34 +1,
		//VF
		RM                  :35-35 +1,
		LED_DISPLAY         :36-36 +1,
		//Other
		GFX_SS              :37-37 +1,
		OUT_OF_BAND_MONITOR :38-38 +1,
		TEMP_DEPENDENT_VMIN :39-39 +1,

		MMHUB_PG            :40-40 +1,
		ATHUB_PG            :41-41 +1,
		APCC_DFLL           :42-42 +1,
		DF_SUPERV           :43-43 +1,
		RSMU_SMN_CG         :44-44 +1,
		DF_CSTATE           :45-45 +1,
		TWO_STEP_PSTATE     :46-46 +1,
		SMNCLK_DPM          :47-47 +1,
		PERLINK_GMIDOWN     :48-48 +1,
		GFX_EDC             :49-49 +1,
		GFX_PER_PART_VMIN   :50-50 +1,
		SMART_SHIFT         :51-51 +1,
		APT                 :52-52 +1,
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





union dpm_debug_override_smu11_0x13 {
	uint32_t DebugOverrides;
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
union dpm_debug_override_smu11_0x33 {
	uint32_t DebugOverrides;
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
union dpm_debug_override_smu11_0x40 {
	uint32_t DebugOverrides;
	struct { uint32_t
		DISABLE_FCLK_PID                 :0-0 +1,
		DISABLE_UCLK_PID                 :1-1 +1,
		DISABLE_VOLT_LINK_VCN_FCLK       :2-2 +1,
		ENABLE_FREQ_LINK_VCLK_FCLK       :3-3 +1,
		ENABLE_FREQ_LINK_DCLK_FCLK       :4-4 +1,
		ENABLE_FREQ_LINK_GFXCLK_SOCCLK   :5-5 +1,
		ENABLE_FREQ_LINK_GFXCLK_UCLK     :6-6 +1,
		DISABLE_VOLT_LINK_DCE_FCLK       :7-7 +1,
		DISABLE_VOLT_LINK_MP0_SOCCLK     :8-8 +1,
		DISABLE_DFLL_PLL_SHUTDOWN        :9-9 +1,
		DISABLE_MEMORY_TEMPERATURE_READ :10-10 +1,
		DISABLE_VOLT_LINK_VCN_DCEFCLK   :11-11 +1,
		DISABLE_FAST_FCLK_TIMER         :12-12 +1,
		DISABLE_VCN_PG                  :13-13 +1,
		DISABLE_FMAX_VMAX               :14-14 +1,
		ENABLE_eGPU_USB_WA              :15-15 +1,
		reserved                        :31-16 +1;
	};
};



union throttler_control_smu11_0x13 { // unused?
	uint32_t ThrottlerControlMask;
	struct { uint32_t
		PADDING      :0-0 +1,
		TEMP_EDGE    :1-1 +1,
		TEMP_HOTSPOT :2-2 +1,
		TEMP_HBM     :3-3 +1,
		TEMP_VR_GFX  :4-4 +1,
		TEMP_VR_SOC  :5-5 +1,
		TEMP_VR_MEM0 :6-6 +1,
		TEMP_VR_MEM1 :7-7 +1,
		TEMP_LIQUID  :8-8 +1,
		TEMP_PLX     :9-9 +1,
		TEMP_SKIN   :10-10 +1,
		TDC_GFX     :11-11 +1,
		TDC_SOC     :12-12 +1,
		PPT         :13-13 +1,
		FIT         :14-14 +1,
		PPM         :15-15 +1,
		reserved    :31-16 +1;
	};
};
union throttler_control_smu11_0x33 {
	uint32_t ThrottlerControlMask;
	struct { uint32_t
		PADDING      :0-0 +1,
		TEMP_EDGE    :1-1 +1,
		TEMP_HOTSPOT :2-2 +1,
		TEMP_MEM     :3-3 +1,
		TEMP_VR_GFX  :4-4 +1,
		TEMP_VR_MEM0 :5-5 +1,
		TEMP_VR_MEM1 :6-6 +1,
		TEMP_VR_SOC  :7-7 +1,
		TEMP_LIQUID0 :8-8 +1,
		TEMP_LIQUID1 :9-9 +1,
		TEMP_PLX    :10-10 +1,
		TEMP_SKIN   :11-11 +1,
		TDC_GFX     :12-12 +1,
		TDC_SOC     :13-13 +1,
		PPT0        :14-14 +1,
		PPT1        :15-15 +1,
		PPT2        :16-16 +1,
		PPT3        :17-17 +1,
		FIT         :18-18 +1,
		PPM         :19-19 +1,
		APCC        :20-20 +1,
		reserved    :31-21 +1;
	};
};
union throttler_control_smu11_0x40 {
	uint32_t ThrottlerControlMask;
	struct { uint32_t
		PADDING      :0-0 +1,
		TEMP_EDGE    :1-1 +1,
		TEMP_HOTSPOT :2-2 +1,
		TEMP_MEM     :3-3 +1,
		TEMP_VR_GFX  :4-4 +1,
		TEMP_VR_MEM0 :5-5 +1,
		TEMP_VR_MEM1 :6-6 +1,
		TEMP_VR_SOC  :7-7 +1,
		TEMP_LIQUID0 :8-8 +1,
		TEMP_LIQUID1 :9-9 +1,
		TEMP_PLX    :10-10 +1,
		TDC_GFX     :11-11 +1,
		TDC_SOC     :12-12 +1,
		PPT0        :13-13 +1,
		PPT1        :14-14 +1,
		PPT2        :15-15 +1,
		PPT3        :16-16 +1,
		FIT         :17-17 +1,
		PPM         :18-18 +1,
		APCC        :19-19 +1,
		reserved    :31-20 +1;
	};
};


union fw_dstate_features_smu11_0x33 {
	uint32_t FwDStateMask;
	struct { uint32_t
		SOC_ULV          :0-0 +1,
		G6_HSR           :1-1 +1,
		G6_PHY_VDDCI_OFF :2-2 +1,
		MP0_DS           :3-3 +1,
		SMN_DS           :4-4 +1,
		MP1_DS           :5-5 +1,
		MP1_WHISPER_MODE :6-6 +1,
		LIV_MIN          :7-7 +1,
		SOC_PLL_PWRDN    :8-8 +1,
		reserved        :31-9 +1;
	};
};
union fw_dstate_features_smu11_0x40 {
	uint32_t FwDStateMask;
	struct { uint32_t
		SOC_ULV                :0-0 +1,
		G6_HSR                 :1-1 +1,
		G6_PHY_VDDCI_OFF       :2-2 +1,
		MP0_DS                 :3-3 +1,
		SMN_DS                 :4-4 +1,
		MP1_DS                 :5-5 +1,
		MP1_WHISPER_MODE       :6-6 +1,
		SOC_LIV_MIN            :7-7 +1,
		SOC_PLL_PWRDN          :8-8 +1,
		MEM_PLL_PWRDN          :9-9 +1,
		OPTIMIZE_MALL_REFRESH :10-10 +1,
		MEM_PSI               :11-11 +1,
		HSR_NON_STROBE        :12-12 +1,
		MP0_ENTER_WFI         :13-13 +1,
		reserved              :31-14 +1;
	};
};

union gfx_gpo_features { // graphics power optimisation
	uint8_t  GfxGpoSubFeatureMask;
	struct { uint8_t
		PACE     :0-0 +1,
		DEM      :1-1 +1,
		reserved :7-2 +1;
	};
};


#define XGMI_STATE_D0 1
#define XGMI_STATE_D3 0


//Piecewise linear droop model, Sienna_Cichlid currently used only for GFX DFLL
#define NUM_PIECE_WISE_LINEAR_DROOP_MODEL_VF_POINTS 5
enum DfllDroopModelSelect_e:uint8_t {
	PIECEWISE_LINEAR_FUSED_MODEL = 0,
	PIECEWISE_LINEAR_PP_MODEL    = 1,
	QUADRATIC_PP_MODEL           = 2,
	PERPART_PIECEWISE_LINEAR_PP_MODEL = 3,
	DFLLDROOPMODELSELECT_COUNT   = 4,
};

struct PiecewiseLinearDroopInt_t {
	float32_t Fset[NUM_PIECE_WISE_LINEAR_DROOP_MODEL_VF_POINTS];   // in GHz
	float32_t Vdroop[NUM_PIECE_WISE_LINEAR_DROOP_MODEL_VF_POINTS]; // in V
};


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
enum SMU11_PPT7_PPCLK_e {
	SMU11_PPT7_PPCLK_GFXCLK  = 0,
	SMU11_PPT7_PPCLK_SOCCLK  = 1,
	SMU11_PPT7_PPCLK_UCLK    = 2,
	SMU11_PPT7_PPCLK_FCLK    = 3,
	SMU11_PPT7_PPCLK_DCLK_0  = 4,
	SMU11_PPT7_PPCLK_VCLK_0  = 5,
	SMU11_PPT7_PPCLK_DCLK_1  = 6,
	SMU11_PPT7_PPCLK_VCLK_1  = 7,
	SMU11_PPT7_PPCLK_DCEFCLK = 8,
	SMU11_PPT7_PPCLK_DISPCLK = 9,
	SMU11_PPT7_PPCLK_PIXCLK  = 10,
	SMU11_PPT7_PPCLK_PHYCLK  = 11,
	SMU11_PPT7_PPCLK_DTBCLK  = 12,
	SMU11_PPT7_PPCLK_COUNT   = 13,
};

enum TEMP_SMU11_0_0_e {
	TEMP_SMU11_0_0_EDGE    = 0,
	TEMP_SMU11_0_0_HOTSPOT = 1,
	TEMP_SMU11_0_0_LIQUID  = 2,
	TEMP_SMU11_0_0_VR_GFX  = 3,
	TEMP_SMU11_0_0_VR_SOC  = 4,
	TEMP_SMU11_0_0_PLX     = 5,
	TEMP_SMU11_0_0_HBM     = 6,
	TEMP_SMU11_0_0_COUNT   = 7,
};
enum TEMP_SMU11_SMC8 {
	TEMP_SMU11_SMC8_EDGE    = 0,
	TEMP_SMU11_SMC8_HOTSPOT = 1,
	TEMP_SMU11_SMC8_LIQUID0 = 2,
	TEMP_SMU11_SMC8_LIQUID1 = 3,
	TEMP_SMU11_SMC8_VR_GFX  = 4,
	TEMP_SMU11_SMC8_VR_SOC  = 5,
	TEMP_SMU11_SMC8_VR_MEM0 = 6,
	TEMP_SMU11_SMC8_VR_MEM1 = 7,
	TEMP_SMU11_SMC8_PLX     = 8,
	TEMP_SMU11_SMC8_MEM     = 9,
	TEMP_SMU11_SMC8_COUNT   = 10,
};
enum TEMP_SMU11_0_7_e {
	TEMP_SMU_11_0_7_EDGE    = 0,
	TEMP_SMU_11_0_7_HOTSPOT = 1,
	TEMP_SMU_11_0_7_MEM     = 2,
	TEMP_SMU_11_0_7_VR_GFX  = 3,
	TEMP_SMU_11_0_7_VR_MEM0 = 4,
	TEMP_SMU_11_0_7_VR_MEM1 = 5,
	TEMP_SMU_11_0_7_VR_SOC  = 6,
	TEMP_SMU_11_0_7_LIQUID0 = 7,
	TEMP_SMU_11_0_7_LIQUID1 = 8,
	TEMP_SMU_11_0_7_PLX     = 9,
	TEMP_SMU_11_0_7_COUNT   = 10,
};


//typedef struct dpm_descriptor_smu11  DpmDescriptor_t;
struct dpm_descriptor_smu11 { // works for driver_if ver 0x13 0x33
	enum VOLTAGE_MODE_e  VoltageMode;
	uint8_t  SnapToDiscrete;    // 0 - Fine grained DPM, 1 - Discrete DPM
	uint8_t  NumDiscreteLevels; // Set to 2 (Fmin, Fmax) when using fine grained  DPM, otherwise set to # discrete levels used
	uint8_t  padding;
	struct linear_f32  ConversionToAvfsClk; // Transfer function to AVFS Clock (GHz->GHz)
	struct quadratic_f32  slowslow_curve;   // Slow-slow curve (GHz->V)
};
struct dpm_descriptor_smu11_0x40 {
	enum VOLTAGE_MODE_e  VoltageMode;
	uint8_t  SnapToDiscrete;    // 0 - Fine grained DPM, 1 - Discrete DPM
	uint8_t  NumDiscreteLevels; // Set to 2 (Fmin, Fmax) when using fine grained DPM, otherwise set to # discrete levels used
	uint8_t  Padding;
	struct linear_f32  ConversionToAvfsClk; // Transfer function to AVFS Clock (GHz->GHz)
	struct quadratic_f32  SsCurve; // Slow-slow curve (GHz->V)
	uint16_t SsFmin; // Fmin for SS curve. If SS curve is selected, will use V@SSFmin for F <= Fmin
	uint16_t Padding16;
};

struct UclkDpmChangeRange_t { // Used for 2-step UCLK DPM change workaround
	uint16_t Fmin;
	uint16_t Fmax;
};



struct smu11_smcpptable_power_limit {
	uint16_t watts;
	uint16_t tau; // Time constant of LPF in ms
};
struct smu11_smcpptable_current_limit {
	uint16_t watts;
	uint16_t tau; // Time constant of LPF in ms
};

struct smu11_smcpptable_voltage_parameters {
	uq14_2_t MinVoltageGfx; // In mV(Q2) Minimum Voltage ("Vmin") of VDD_GFX
	uq14_2_t MinVoltageSoc; // In mV(Q2) Minimum Voltage ("Vmin") of VDD_SOC
	uq14_2_t MaxVoltageGfx; // In mV(Q2) Maximum Voltage allowable of VDD_GFX
	uq14_2_t MaxVoltageSoc; // In mV(Q2) Maximum Voltage allowable of VDD_SOC

	uq8_8_t LoadLineResistanceGfx; // In mOhms with 8 fractional bits
	uq8_8_t LoadLineResistanceSoc; // In mOhms with 8 fractional bits
};
struct smu11_smcpptable_dpm_voltage {
	uq14_2_t Mp0DpmVoltage[NUM_MP0CLK_DPM_LEVELS_SMU11]; // mV(Q2)
	uq14_2_t MemVddciVoltage[NUM_UCLK_DPM_LEVELS_SMU11]; // mV(Q2)
	uq14_2_t MemMvddVoltage[NUM_UCLK_DPM_LEVELS_SMU11];  // mV(Q2)
};
struct smu11_smcpptable_dpm_link {
	enum PCIE_SPEED_e  PcieGenSpeed[NUM_LINK_LEVELS_SMU11];
	enum PCIE_WIDTH_e  PcieLaneCount[NUM_LINK_LEVELS_SMU11];
	uint16_t LclkFreq[NUM_LINK_LEVELS_SMU11];
};
struct smu11_smcpptable_dpm_gfxclk_thermal {
	uint16_t EnableTdpm;
	uint16_t TdpmHighHystTemperature;
	uint16_t TdpmLowHystTemperature;
	uint16_t GfxclkFreqHighTempLimit; // High limit on GFXCLK when temperature is high, for reliability.
};
struct smu11_smcpptable_temp_dependent_vmin {
	uint16_t VDDGFX_TVmin;       // Celcius
	uint16_t VDDSOC_TVmin;       // Celcius
	uq14_2_t VDDGFX_Vmin_HiTemp; // mV Q2
	uq14_2_t VDDGFX_Vmin_LoTemp; // mV Q2
	uq14_2_t VDDSOC_Vmin_HiTemp; // mV Q2
	uq14_2_t VDDSOC_Vmin_LoTemp; // mV Q2
	uint16_t VDDGFX_TVminHystersis; // Celcius
	uint16_t VDDSOC_TVminHystersis; // Celcius
};
struct smu11_smcpptable_vr_mapping {
	union vr_mapping VddGfxVrMapping;
	union vr_mapping VddSocVrMapping;
	union vr_mapping VddMem0VrMapping;
	union vr_mapping VddMem1VrMapping;
};
struct smu11_smcpptable_svi2_parameters {
	uq14_2_t MaxVoltageStepGfx; // In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value.
	uq14_2_t MaxVoltageStepSoc; // In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value.

	struct smu11_smcpptable_vr_mapping vr_mapping;

	union psi_sel_mask  GfxUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
	union psi_sel_mask  SocUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
	uint8_t  ExternalSensorPresent; // External RDI connected to TMON (aka TEMP IN)
	uint8_t  Padding8_V;
};
struct smu11_smcpptable_telemetry_settings {
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
};
struct smu11_smcpptable_gpio_settings {
	uint8_t  AcDcGpio;       // GPIO pin configured for AC/DC switching
	uint8_t  AcDcPolarity;   // GPIO polarity for AC/DC switching
	uint8_t  VR0HotGpio;     // GPIO pin configured for VR0 HOT event
	uint8_t  VR0HotPolarity; // GPIO polarity for VR0 HOT event

	uint8_t  VR1HotGpio;     // GPIO pin configured for VR1 HOT event
	uint8_t  VR1HotPolarity; // GPIO polarity for VR1 HOT event
	uint8_t  GthrGpio;       // GPIO pin configured for GTHR Event
	uint8_t  GthrPolarity;   // replace GPIO polarity for GTHR
};
struct smu11_smcpptable_spread_spectrum {
	uint8_t  enabled;
	uq4_4_t  percent;
	uint16_t frequency; // kHz
};

struct smu11_smcpptable_v3_infrastructure_limits {
	struct smu11_smcpptable_power_limit  ac[PPT_THROTTLER_COUNT];
	struct smu11_smcpptable_power_limit  dc;

	struct smu11_smcpptable_current_limit tdc_soc;
	struct smu11_smcpptable_current_limit tdc_gfx;

	uint16_t TedgeLimit;    // Celcius
	uint16_t ThotspotLimit; // Celcius
	uint16_t ThbmLimit;     // Celcius
	uint16_t Tvr_gfxLimit;  // Celcius
	uint16_t Tvr_memLimit;  // Celcius
	uint16_t Tliquid1Limit; // Celcius
	uint16_t Tliquid2Limit; // Celcius
	uint16_t TplxLimit;     // Celcius
	uint32_t FitLimit;      // Failures in time (failures per million parts over the defined lifetime)

	uint16_t PpmPowerLimit; // Switch this this power limit when temperature is above PpmTempThreshold
	uint16_t PpmTemperatureThreshold;

	uint8_t  MemoryOnPackage;
	uint8_t  padding8_limits;
	uint16_t Tvr_SocLimit; // Celcius
};
struct smu11_smcpptable_v3_ulv_settings {
	uq14_2_t UlvVoltageOffsetSoc; // In mV(Q2)
	uq14_2_t UlvVoltageOffsetGfx; // In mV(Q2)

	uint8_t  UlvSmnclkDid; // DID for ULV mode. 0 means CLK will not be modified in ULV.
	uint8_t  UlvMp1clkDid; // DID for ULV mode. 0 means CLK will not be modified in ULV.
	uint8_t  UlvGfxclkBypass; // 1 to turn off/bypass Gfxclk during ULV, 0 to leave Gfxclk on during ULV
	uint8_t  Padding234;
};
struct smu11_smcpptable_v3_voltage {
	struct smu11_smcpptable_v3_ulv_settings    ulv_settings;
	struct smu11_smcpptable_voltage_parameters voltage_params;
};
struct smu11_smcpptable_v3_dpm_config_freq_tables {
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

	uint16_t Mp0clkFreq[NUM_MP0CLK_DPM_LEVELS_SMU11];    // In MHz
};
struct smu11_smcpptable_v3_dpm_gfxclk {
	uint16_t GfxclkFidle;    // in MHz
	uint16_t GfxclkSlewRate; // for PLL babystepping???
	uint16_t CksEnableFreq;
	uint16_t Padding789;
	struct quadratic_f32  CksVoltageOffset;
	uint8_t  Padding567[4];
	uint16_t GfxclkDsMaxFreq; // in Mhz
	enum GFXCLK_SOURCE_e  GfxclkSource;
	uint8_t  Padding456;
};
struct smu11_smcpptable_v3_dpm_config {
	//SECTION: DPM Config 1
	struct dpm_descriptor_smu11  DpmDescriptor[SMU11_PPT3_PPCLK_COUNT];

	struct smu11_smcpptable_v3_dpm_config_freq_tables freq_tables;

	uq14_2_t Mp0DpmVoltage[NUM_MP0CLK_DPM_LEVELS_SMU11]; // mV(Q2)

	struct smu11_smcpptable_v3_dpm_gfxclk      gfxclk;

	uint8_t  LowestUclkReservedForUlv; // Set this to 1 if UCLK DPM0 is reserved for ULV-mode only
	uint8_t  Padding8_Uclk[3];

	struct smu11_smcpptable_dpm_link           link_dpm;
	struct smu11_smcpptable_dpm_gfxclk_thermal  gfxclk_thermal;
};
struct smu11_smcpptable_v3_fan_control {
	// SECTION: Fan Control
	uint16_t FanStopTemp;  // Celcius
	uint16_t FanStartTemp; // Celcius

	uint16_t FanGain[TEMP_SMU11_0_0_COUNT];
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
};
struct smu11_smcpptable_v3_avfs_xgmi {
	enum XGMI_LINK_RATE_e  XgmiLinkSpeed[NUM_XGMI_LEVELS_SMU11];
	enum XGMI_LINK_WIDTH_e XgmiLinkWidth[NUM_XGMI_LEVELS_SMU11];
	uint16_t XgmiFclkFreq[NUM_XGMI_LEVELS_SMU11];
	uint16_t XgmiUclkFreq[NUM_XGMI_LEVELS_SMU11];
	uint16_t XgmiSocclkFreq[NUM_XGMI_LEVELS_SMU11];
	uint16_t XgmiSocVoltage[NUM_XGMI_LEVELS_SMU11];
};
struct smu11_smcpptable_v3_avfs {
	// Overrides
	uint8_t  OverrideAvfsGb[AVFS_VOLTAGE_COUNT];
	uint8_t  Padding8_Avfs[2];

	struct quadratic_f32  AvfsGb[AVFS_VOLTAGE_COUNT]; // GHz->V Override of fused curve
	struct droop_f32  BtcGbGfxCksOn;
	struct droop_f32  BtcGbGfxCksOff;
	struct droop_f32  BtcGbGfxAfll; // dfll?
	struct droop_f32  BtcGbSoc;     // GHz->V BtcGb
	struct linear_f32  AgingGb[AVFS_VOLTAGE_COUNT]; // GHz->V

	struct quadratic_f32  qStaticVoltageOffset[AVFS_VOLTAGE_COUNT]; // GHz->V

	uq14_2_t DcTol[AVFS_VOLTAGE_COUNT]; // mV(Q2)

	uint8_t  DcBtcEnabled[AVFS_VOLTAGE_COUNT];
	uint8_t  Padding8_GfxBtc[2];

	uq14_2_t DcBtcMin[AVFS_VOLTAGE_COUNT];
	uq14_2_t DcBtcMax[AVFS_VOLTAGE_COUNT]; // mV(Q2)

	struct smu11_smcpptable_v3_avfs_xgmi xgmi;
};
struct smu11_smcpptable_v3_spread_spectrum {
	struct smu11_smcpptable_spread_spectrum PllGfxclk;
	struct smu11_smcpptable_spread_spectrum Uclk;
	struct smu11_smcpptable_spread_spectrum Fclk;
	struct smu11_smcpptable_spread_spectrum FllGfxclk;
};
struct smu11_smcpptable_v3 { // Vega20
	uint32_t Version;

	union powerplay_feature_control_smu11_0x13        features;
	struct smu11_smcpptable_v3_infrastructure_limits  infrastructure_limits;
	struct smu11_smcpptable_v3_voltage     voltage_control;
	struct smu11_smcpptable_v3_dpm_config  dpm_config;
	struct smu11_smcpptable_v3_fan_control fan_control;
	struct smu11_smcpptable_v3_avfs        avfs;
	union dpm_debug_override_smu11_0x13    DebugOverrides;
	struct quadratic_f32                   ReservedEquation[4];

	uq14_2_t MinVoltageUlvGfx; // In mV(Q2)  Minimum Voltage ("Vmin") of VDD_GFX in ULV mode
	uq14_2_t MinVoltageUlvSoc; // In mV(Q2)  Minimum Voltage ("Vmin") of VDD_SOC in ULV mode

	uint16_t MGpuFanBoostLimitRpm;
	uint16_t padding16_Fan;
	uint16_t FanGainVrMem0;
	uint16_t FanGainVrMem1;

	uint16_t DcBtcGb[AVFS_VOLTAGE_COUNT];

	uint32_t Reserved[11];
	uint32_t Padding32[3];

	struct smu11_smcpptable_svi2_parameters    svi2_parameters;
	struct smu11_smcpptable_telemetry_settings telemetry;
	struct smu11_smcpptable_gpio_settings      gpio;

	// LED Display Settings
	uint8_t  LedPin[3]; // GPIO numbers
	uint8_t  padding8_4;

	struct smu11_smcpptable_v3_spread_spectrum  spread_spectrum;
	struct i2ccontrollerconfig_u32  I2cControllers[
		I2C_CONTROLLER_NAME_COUNT_SMU11_PPT3
	];

	uint32_t BoardReserved[10];
	uint32_t MmHubPadding[8];
};


struct smu11_smcpptable_v8_infrastructure_limits {
	uint16_t SocketPowerLimitAc[PPT_THROTTLER_COUNT];
	uint16_t SocketPowerLimitAcTau[PPT_THROTTLER_COUNT];
	uint16_t SocketPowerLimitDc[PPT_THROTTLER_COUNT];
	uint16_t SocketPowerLimitDcTau[PPT_THROTTLER_COUNT];

	struct smu11_smcpptable_current_limit tdc_soc;
	struct smu11_smcpptable_current_limit tdc_gfx;

	uint16_t TemperatureLimit[TEMP_SMU_11_0_7_COUNT]; // Celcius
	uint32_t FitLimit; // Failures in time (failures per million parts over the defined lifetime)

	uint16_t PpmPowerLimit; // Switch this this power limit when temperature is above PpmTempThreshold
	uint16_t PpmTemperatureThreshold;
};
struct smu11_smcpptable_v8_ulv_settings {
	uq14_2_t UlvVoltageOffsetSoc; // In mV(Q2)
	uq14_2_t UlvVoltageOffsetGfx; // In mV(Q2)

	uint8_t  GceaLinkMgrIdleThreshold; // Set by SMU FW during enablment of SOC_ULV. Controls delay for GFX SDP port disconnection during idle events
	uint8_t  paddingRlcUlvParams[3];

	uint8_t  UlvSmnclkDid; // DID for ULV mode. 0 means CLK will not be modified in ULV.
	uint8_t  UlvMp1clkDid; // DID for ULV mode. 0 means CLK will not be modified in ULV.
	uint8_t  UlvGfxclkBypass; // 1 to turn off/bypass Gfxclk during ULV, 0 to leave Gfxclk on during ULV
	uint8_t  Padding234;

	uq14_2_t MinVoltageUlvGfx; // In mV(Q2)  Minimum Voltage ("Vmin") of VDD_GFX in ULV mode
	uq14_2_t MinVoltageUlvSoc; // In mV(Q2)  Minimum Voltage ("Vmin") of VDD_SOC in ULV mode
};
struct smu11_smcpptable_v8_voltage {
	struct smu11_smcpptable_v8_ulv_settings    ulv_settings;
	struct smu11_smcpptable_voltage_parameters voltage_params;
};
struct smu11_smcpptable_v8_dpm_freq_tables {
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

	enum UCLK_DIV_e  FreqTableUclkDiv[NUM_UCLK_DPM_LEVELS_SMU11];
	uint16_t Mp0clkFreq[NUM_MP0CLK_DPM_LEVELS_SMU11];    // in MHz
};
struct smu11_smcpptable_v8_dpm_gfxclk {
	uint16_t GfxclkFgfxoffEntry; // in Mhz
	uint16_t GfxclkFinit;        // in Mhz
	uint16_t GfxclkFidle;        // in MHz
	uint16_t GfxclkSlewRate;     // for PLL babystepping???
	uint16_t GfxclkFopt;         // in Mhz
	uint8_t  Padding567[2];
	uint16_t GfxclkDsMaxFreq;    // in MHz
	enum GFXCLK_SOURCE_e  GfxclkSource;
	uint8_t  Padding456;
};
struct smu11_smcpptable_v8_dpm_uclk {
	uint8_t  LowestUclkReservedForUlv; // Set this to 1 if UCLK DPM0 is reserved for ULV-mode only
	uint8_t  paddingUclk[3];

	uint8_t  MemoryType; // 0-GDDR6, 1-HBM
	uint8_t  MemoryChannels;
	uint8_t  PaddingMem[2];
};
struct smu11_smcpptable_v8_dpm_config {
	struct dpm_descriptor_smu11  DpmDescriptor[SMU11_PPT8_PPCLK_COUNT];
	struct smu11_smcpptable_v8_dpm_freq_tables freq_tables;
	struct smu11_smcpptable_dpm_voltage        voltage;
	struct smu11_smcpptable_v8_dpm_gfxclk      gfxclk;
	struct smu11_smcpptable_v8_dpm_uclk        uclk;
	struct smu11_smcpptable_dpm_link           link_dpm;
	struct smu11_smcpptable_dpm_gfxclk_thermal gfxclk_thermal;
};
struct smu11_smcpptable_v8_fan_control {
	// SECTION: Fan Control
	uint16_t FanStopTemp;  // Celcius
	uint16_t FanStartTemp; // Celcius

	uint16_t FanGain[TEMP_SMU11_SMC8_COUNT]; // does not follow TEMP_SMU11_0_7_e for some reason
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

};
struct smu11_smcpptable_v8_avfs {
	uint8_t  OverrideAvfsGb[AVFS_VOLTAGE_COUNT];
	uint8_t  Padding8_Avfs[2];

	struct quadratic_f32  AvfsGb[AVFS_VOLTAGE_COUNT]; // GHz->V Override of fused curve
	struct droop_f32  BtcGbGfxPll;  // GHz->V BtcGb
	struct droop_f32  BtcGbGfxDfll; // GHz->V BtcGb
	struct droop_f32  BtcGbSoc;     // GHz->V BtcGb
	struct linear_f32  AgingGb[AVFS_VOLTAGE_COUNT]; // GHz->V

	struct quadratic_f32  qStaticVoltageOffset[AVFS_VOLTAGE_COUNT]; // GHz->V

	uq14_2_t DcTol[AVFS_VOLTAGE_COUNT]; // mV Q2

	uint8_t  DcBtcEnabled[AVFS_VOLTAGE_COUNT];
	uint8_t  Padding8_GfxBtc[2];

	uq14_2_t DcBtcMin[AVFS_VOLTAGE_COUNT]; // mV Q2
	uq14_2_t DcBtcMax[AVFS_VOLTAGE_COUNT]; // mV Q2
};
struct smu11_smcpptable_v8_btc {
	uint32_t BtcConfig;

	uint16_t SsFmin[SMU11_PPT8_PPCLK_COUNT]; // PPtable value to function similar to VFTFmin for SS Curve
	uint16_t SsFmin_padding;

	uint16_t DcBtcGb[AVFS_VOLTAGE_COUNT];
};
struct smu11_smcpptable_v8_spread_spectrum {
	struct smu11_smcpptable_spread_spectrum PllGfxclk;
	struct smu11_smcpptable_spread_spectrum DfllGfxclk;
	struct smu11_smcpptable_spread_spectrum Uclk;
	struct smu11_smcpptable_spread_spectrum Socclk;
};
struct smu11_smcpptable_v8 { // Navi10
	uint32_t Version;

	union powerplay_feature_control_smu11_0x33        features;
	struct smu11_smcpptable_v8_infrastructure_limits  infrastructure_limits;
	union throttler_control_smu11_0x33     ThrottlerControlMask;
	union fw_dstate_features_smu11_0x33    FwDStateMask;
	struct smu11_smcpptable_v8_voltage     voltage_control;
	struct smu11_smcpptable_v8_dpm_config  dpm_config;
	struct smu11_smcpptable_v8_fan_control fan_control;
	struct smu11_smcpptable_v8_avfs        avfs;
	union dpm_debug_override_smu11_0x33    DebugOverrides;
	struct quadratic_f32                   ReservedEquation[4];

	// Total Power configuration
	enum PwrConfig_e  TotalPowerConfig;
	uint8_t  TotalPowerPadding[3];

	// APCC Settings
	uint16_t PccThresholdLow;
	uint16_t PccThresholdHigh;
	uint32_t MGpuFanBoostLimitRpm;
	uint32_t PaddingAPCC[5];

	struct smu11_smcpptable_temp_dependent_vmin temp_vmin;
	struct smu11_smcpptable_v8_btc btc;

	uint32_t Reserved[8];

	// SECTION: BOARD PARAMETERS
	// I2C Control
	struct i2ccontrollerconfig_u8_mixed I2cControllers[
		I2C_CONTROLLER_NAME_COUNT_SMU11_PPT8
	];

	struct smu11_smcpptable_svi2_parameters    svi2_parameters;
	struct smu11_smcpptable_telemetry_settings telemetry;
	struct smu11_smcpptable_gpio_settings      gpio;

	// LED Display Settings
	uint8_t  LedPin[3]; // GPIO numbers
	uint8_t  padding8_4;

	struct smu11_smcpptable_v8_spread_spectrum spread_spectrum;

	// Total board power
	uint16_t TotalBoardPower; // Only needed for TCP Estimated case, where TCP = TGP+Total Board Power
	uint16_t BoardPadding;

	// Mvdd Svi2 Div Ratio Setting
	uq16_16_t MvddRatio; // This is used for MVDD Vid workaround. It has 16 fractional bits (Q16.16)

	uint8_t  RenesesLoadLineEnabled;
	uint8_t  GfxLoadlineResistance;
	uint8_t  SocLoadlineResistance;
	uint8_t  Padding8_Loadline;

	uint32_t BoardReserved[8];

	// Padding for MMHUB - do not modify this
	uint32_t MmHubPadding[8]; // SMU internal use
};








struct smu11_smcpptable_v7_infrastructure_limits {
	// SECTION: Infrastructure Limits
	uint16_t SocketPowerLimitAc[PPT_THROTTLER_COUNT];    // Watts
	uint16_t SocketPowerLimitAcTau[PPT_THROTTLER_COUNT]; // Time constant of LPF in ms
	uint16_t SocketPowerLimitDc[PPT_THROTTLER_COUNT];    // Watts
	uint16_t SocketPowerLimitDcTau[PPT_THROTTLER_COUNT]; // Time constant of LPF in ms

	uint16_t TdcLimit[TDC_THROTTLER_COUNT_SMU11];    // Amps
	uint16_t TdcLimitTau[TDC_THROTTLER_COUNT_SMU11]; // Time constant of LPF in ms

	uint16_t TemperatureLimit[TEMP_SMU_11_0_7_COUNT]; // Celcius

	uint32_t FitLimit; // Failures in time (failures per million parts over the defined lifetime)
};


struct smu11_smcpptable_v7_smnclk_dpm {
	uint16_t SmnclkDpmFreq[NUM_SMNCLK_DPM_LEVELS_SMU11];    // in MHz
	uq14_2_t SmnclkDpmVoltage[NUM_SMNCLK_DPM_LEVELS_SMU11]; // mV(Q2)

	uint32_t PaddingAPCC;
	uq14_2_t PerPartDroopVsetGfxDfll[NUM_PIECE_WISE_LINEAR_DROOP_MODEL_VF_POINTS];  //In mV(Q2)
	uint16_t PaddingPerPartDroop;
};
struct smu11_smcpptable_v7_ulv_settings {
	uq14_2_t UlvVoltageOffsetSoc; // In mV(Q2)
	uq14_2_t UlvVoltageOffsetGfx; // In mV(Q2)
	uq14_2_t MinVoltageUlvGfx; // In mV(Q2)  Minimum Voltage ("Vmin") of VDD_GFX in ULV mode
	uq14_2_t MinVoltageUlvSoc; // In mV(Q2)  Minimum Voltage ("Vmin") of VDD_SOC in ULV mode
	uq14_2_t SocLIVmin;        // In mV(Q2)  Long Idle Vmin (deep ULV), for VDD_SOC
	uint16_t PaddingLIVmin;
	uint8_t  GceaLinkMgrIdleThreshold; // Set by SMU FW during enablment of GFXOFF. Controls delay for GFX SDP port disconnection during idle events
	uint8_t  paddingRlcUlvParams[3];
};
struct smu11_smcpptable_v7_voltage {
	struct smu11_smcpptable_v7_ulv_settings     ulv_settings;
	struct smu11_smcpptable_voltage_parameters  voltage_params;
	struct smu11_smcpptable_temp_dependent_vmin temp_vmin;
};

struct smu11_smcpptable_v7_dpm_freq_tables {
	uint16_t FreqTableGfx[NUM_GFXCLK_DPM_LEVELS_SMU11];      // In MHz
	uint16_t FreqTableVclk[NUM_VCLK_DPM_LEVELS_SMU11];       // In MHz
	uint16_t FreqTableDclk[NUM_DCLK_DPM_LEVELS_SMU11];       // In MHz
	uint16_t FreqTableSocclk[NUM_SOCCLK_DPM_LEVELS_SMU11];   // In MHz
	uint16_t FreqTableUclk[NUM_UCLK_DPM_LEVELS_SMU11];       // In MHz
	uint16_t FreqTableDcefclk[NUM_DCEFCLK_DPM_LEVELS_SMU11]; // In MHz
	uint16_t FreqTableDispclk[NUM_DISPCLK_DPM_LEVELS_SMU11]; // In MHz
	uint16_t FreqTablePixclk[NUM_PIXCLK_DPM_LEVELS_SMU11];   // In MHz
	uint16_t FreqTablePhyclk[NUM_PHYCLK_DPM_LEVELS_SMU11];   // In MHz
	uint16_t FreqTableDtbclk[NUM_DTBCLK_DPM_LEVELS_SMU11];   // In MHz
	uint16_t FreqTableFclk[NUM_FCLK_DPM_LEVELS_SMU11];       // In MHz
	uint32_t Paddingclks;

	struct droop_f32  PerPartDroopModelGfxDfll[NUM_PIECE_WISE_LINEAR_DROOP_MODEL_VF_POINTS]; // GHz ->V

	uint32_t DcModeMaxFreq[SMU11_PPT7_PPCLK_COUNT]; // In MHz

	enum UCLK_DIV_e  FreqTableUclkDiv[NUM_UCLK_DPM_LEVELS_SMU11];

	// Used for MALL performance boost
	uint16_t FclkBoostFreq; // In Mhz
	uint16_t FclkParamPadding;

	uq14_2_t Mp0clkFreq[NUM_MP0CLK_DPM_LEVELS_SMU11]; // in MHz
};
struct smu11_smcpptable_v7_dpm_gfxclk {
	uint16_t GfxclkFgfxoffEntry; // in Mhz
	uint16_t GfxclkFinit;  // in Mhz
	uint16_t GfxclkFidle;  // in MHz
	enum GFXCLK_SOURCE_e  GfxclkSource; // 0 = PLL, 1 = DFLL
	uint8_t  GfxclkPadding;
};
struct smu11_smcpptable_v7_dpm_gfx_gpo {
	union gfx_gpo_features  GfxGpoSubFeatureMask;
	union gfx_gpo_features  GfxGpoEnabledWorkPolicyMask; // Any policy that GPO can be enabled
	union gfx_gpo_features  GfxGpoDisabledWorkPolicyMask; // Any policy that GPO can be disabled
	uint8_t  GfxGpoPadding[1];
	uint32_t GfxGpoVotingAllow; // For indicating which feature changes should result in a GPO table recalculation

	uint32_t GfxGpoPadding32[4];
};
struct smu11_smcpptable_v7_dpm_gfx_dcs {
	uint16_t GfxDcsFopt;     // Optimal GFXCLK for DCS in Mhz
	uint16_t GfxDcsFclkFopt; // Optimal FCLK for DCS in Mhz
	uint16_t GfxDcsUclkFopt; // Optimal UCLK for DCS in Mhz

	uq14_2_t DcsGfxOffVoltage;  // Voltage in mV(Q2) applied to VDDGFX when entering DCS GFXOFF phase

	uint16_t DcsMinGfxOffTime;  // Minimum amount of time PMFW shuts GFX OFF as part of GFX DCS phase
	uint16_t DcsMaxGfxOffTime;  // Maximum amount of time PMFW can shut GFX OFF as part of GFX DCS phase at a stretch.

	uint32_t DcsMinCreditAccum; // Min amount of positive credit accumulation before waking GFX up as part of DCS.

	uint16_t DcsExitHysteresis; // The min amount of time power credit accumulator should have a value > 0 before SMU exits the DCS throttling phase.
	uint16_t DcsTimeout; // This is the amount of time SMU FW waits for RLC to put GFX into GFXOFF before reverting to the fallback mechanism of throttling GFXCLK to Fmin.

	uint32_t DcsParamPadding[5];
};
struct smu11_smcpptable_v7_dpm_uclk {
	uint8_t  LowestUclkReservedForUlv; // Set this to 1 if UCLK DPM0 is reserved for ULV-mode only
	uint8_t  PaddingMem[3];

	enum DPM_PSTATES_e  UclkDpmPstates[NUM_UCLK_DPM_LEVELS_SMU11]; // 4 DPM states.
	struct UclkDpmChangeRange_t  UclkDpmSrcFreqRange;  // In Mhz
	struct UclkDpmChangeRange_t  UclkDpmTargFreqRange; // In Mhz
	uint16_t UclkDpmMidstepFreq; // In Mhz
	uint16_t UclkMidstepPadding;
};
struct smu11_smcpptable_v7_dpm_config {
	struct dpm_descriptor_smu11_0x40  DpmDescriptor[SMU11_PPT7_PPCLK_COUNT];
	struct smu11_smcpptable_v7_dpm_freq_tables freq_tables;
	struct smu11_smcpptable_dpm_voltage        voltage;
	struct smu11_smcpptable_v7_dpm_gfxclk      gfxclk;
	struct smu11_smcpptable_v7_dpm_gfx_gpo     gfx_gpo;
	struct smu11_smcpptable_v7_dpm_gfx_dcs     gfx_dcs;
	uq8_8_t FlopsPerByteTable[RLC_PACE_TABLE_NUM_LEVELS_SMU11]; // Q8.8
	struct smu11_smcpptable_v7_dpm_uclk uclk_dpm;
	struct smu11_smcpptable_dpm_link    link_dpm;
};
struct smu11_smcpptable_v7_fan_control {
	// SECTION: Fan Control
	uint16_t FanStopTemp;  // Celcius
	uint16_t FanStartTemp; // Celcius

	uint16_t FanGain[TEMP_SMU_11_0_7_COUNT];

	uint16_t FanPwmMin;
	uint16_t FanAcousticLimitRpm;
	uint16_t FanThrottlingRpm;
	uint16_t FanMaximumRpm;
	uint16_t MGpuFanBoostLimitRpm;
	uint16_t FanTargetTemperature;
	uint16_t FanTargetGfxclk;
	uint16_t FanPadding16;
	uint8_t  FanTempInputSelect;
	uint8_t  FanPadding;
	uint8_t  FanZeroRpmEnable;
	uint8_t  FanTachEdgePerRev;

	// The following are AFC override parameters. Leave at 0 to use FW defaults.
	int16_t  FuzzyFan_ErrorSetDelta;
	int16_t  FuzzyFan_ErrorRateSetDelta;
	int16_t  FuzzyFan_PwmSetDelta;
	uint16_t FuzzyFan_Reserved;
};
struct smu11_smcpptable_v7_avfs {
	// Overrides
	uint8_t  OverrideAvfsGb[AVFS_VOLTAGE_COUNT];
	enum DfllDroopModelSelect_e  BtcGbGfxDfllModelSelect;
	uint8_t  Padding8_Avfs;

	struct quadratic_f32  AvfsGb[AVFS_VOLTAGE_COUNT]; // GHz->V Override of fused curve
	struct droop_f32  BtcGbGfxPll;  // GHz->V BtcGb
	struct droop_f32  BtcGbGfxDfll; // GHz->V BtcGb
	struct droop_f32  BtcGbSoc;     // GHz->V BtcGb
	struct linear_f32 AgingGb[AVFS_VOLTAGE_COUNT]; // GHz->V

	struct PiecewiseLinearDroopInt_t  PiecewiseLinearDroopIntGfxDfll; // GHz ->V

	struct quadratic_f32  qStaticVoltageOffset[AVFS_VOLTAGE_COUNT]; // GHz->V

	uq14_2_t DcTol[AVFS_VOLTAGE_COUNT];  // mV Q2

	uint8_t  DcBtcEnabled[AVFS_VOLTAGE_COUNT];
	uint8_t  Padding8_GfxBtc[2];

	uq14_2_t DcBtcMin[AVFS_VOLTAGE_COUNT]; // mV Q2
	uq14_2_t DcBtcMax[AVFS_VOLTAGE_COUNT]; // mV Q2

	uq14_2_t DcBtcGb[AVFS_VOLTAGE_COUNT];  // mV Q2
};
struct smu11_smcpptable_v7_vc_btc { // VC BTC parameters are only applicable to VDD_GFX domain
	uint8_t  VcBtcEnabled;
	uint16_t VcBtcVminT0; // T0_VMIN
	uint16_t VcBtcFixedVminAgingOffset; // FIXED_VMIN_AGING_OFFSET
	uint16_t VcBtcVmin2PsmDegrationGb;  // VMIN_TO_PSM_DEGRADATION_GB
	float32_t VcBtcPsmA;  // A_PSM
	float32_t VcBtcPsmB;  // B_PSM
	float32_t VcBtcVminA; // A_VMIN
	float32_t VcBtcVminB; // B_VMIN
};
struct smu11_smcpptable_v7_i2c_control {
	// SECTION: I2C Control
	struct i2ccontrollerconfig_u8  I2cControllers[NUM_I2C_CONTROLLERS_SMU11_0_7];

	uint8_t  GpioScl; // GPIO Number for SCL Line, used only for CKSVII2C1
	uint8_t  GpioSda; // GPIO Number for SDA Line, used only for CKSVII2C1
	uint8_t  FchUsbPdSlaveAddr; // For requesting USB PD controller S-states via FCH I2C when entering PME turn off
	uint8_t  I2cSpare[1];
};
struct smu11_smcpptable_v7_svi2_parameters {
	struct smu11_smcpptable_vr_mapping vr_mapping;
	
	union psi_sel_mask  GfxUlvPhaseSheddingMask;   // set this to 1 to set PSI0/1 to 1 in ULV mode
	union psi_sel_mask  SocUlvPhaseSheddingMask;   // set this to 1 to set PSI0/1 to 1 in ULV mode
	union psi_sel_mask  VddciUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
	union psi_sel_mask  MvddUlvPhaseSheddingMask;  // set this to 1 to set PSI0/1 to 1 in ULV mode
};
struct smu11_smcpptable_v7_telemetry_settings {
	struct smu11_smcpptable_telemetry_settings main;
	uq16_16_t MvddRatio; // This is used for MVDD  Svi2 Div Ratio workaround. It has 16 fractional bits (Q16.16)
};
struct smu11_smcpptable_v7_led_settings {
	uint8_t  LedPin[3]; // GPIO numbers
	union led_display_control  LedEnableMask;
	uint8_t  LedPcie;  // GPIO number for PCIE results
	uint8_t  LedError; // GPIO number for Error Cases
	uint8_t  LedSpare1[2];
};
struct smu11_smcpptable_v7_spread_spectrum { // uclk is in main smcpptable
	struct smu11_smcpptable_spread_spectrum PllGfxclk;
	struct smu11_smcpptable_spread_spectrum DfllGfxclk;
	struct smu11_smcpptable_spread_spectrum Uclk; // uclk is in main smcpptable
	struct smu11_smcpptable_spread_spectrum Fclk;
};
struct smu11_smcpptable_v7_xgmi_training {
	enum XGMI_LINK_RATE_e  XgmiLinkSpeed[NUM_XGMI_PSTATE_LEVELS_SMU11];
	enum XGMI_LINK_WIDTH_e XgmiLinkWidth[NUM_XGMI_PSTATE_LEVELS_SMU11];

	uint16_t XgmiFclkFreq[NUM_XGMI_PSTATE_LEVELS_SMU11];
	uint16_t XgmiSocVoltage[NUM_XGMI_PSTATE_LEVELS_SMU11];
};

struct smu11_smcpptable_v7 { // Navi21
	// MAJOR SECTION: SKU PARAMETERS

	uint32_t Version;

	union powerplay_feature_control_smu11_0x40       features;
	struct smu11_smcpptable_v7_infrastructure_limits infrastructure_limits;

	// SECTION: Power Configuration
	enum PwrConfig_e  TotalPowerConfig; // Determines how PMFW calculates the power.
	uint8_t  TotalPowerPadding[3];

	// SECTION: APCC Settings
	uint32_t ApccPlusResidencyLimit;

	struct smu11_smcpptable_v7_smnclk_dpm  smnclk_dpm;
	union throttler_control_smu11_0x40     ThrottlerControlMask;
	union fw_dstate_features_smu11_0x40    FwDStateMask;
	struct smu11_smcpptable_v7_voltage     voltage_control;
	struct smu11_smcpptable_v7_dpm_config  dpm_config;
	struct smu11_smcpptable_v7_fan_control fan_control;
	struct smu11_smcpptable_v7_avfs        avfs;

	// SECTION: XGMI
	enum DPM_PSTATES_e  XgmiDpmPstates[NUM_XGMI_LEVELS_SMU11];
	uint8_t  XgmiDpmSpare[2];

	// SECTION: Advanced Options
	union dpm_debug_override_smu11_0x40  DebugOverrides;
	struct quadratic_f32  ReservedEquation[4];

	// SECTION: Sku Reserved
	enum CUSTOMER_VARIANT_e  CustomerVariant;

	struct smu11_smcpptable_v7_vc_btc vc_btc;

	//GPIO Board feature
	uint16_t LedGpio; // GeneriA GPIO flag used to control the radeon LEDs
	uint16_t GfxPowerStagesGpio; // Genlk_vsync GPIO flag used to control gfx power stages

	uint32_t SkuReserved[8];


	// MAJOR SECTION: BOARD PARAMETERS
	//SECTION: Gaming Clocks
	uint32_t GamingClk[6];

	struct smu11_smcpptable_v7_i2c_control        i2c_control;
	struct smu11_smcpptable_v7_svi2_parameters    svi2_parameters;
	struct smu11_smcpptable_v7_telemetry_settings telemetry;
	struct smu11_smcpptable_gpio_settings         gpio;
	struct smu11_smcpptable_v7_led_settings       led;
	struct smu11_smcpptable_v7_spread_spectrum    spread_spectrum;

	// Section: Memory Config
	uint32_t MemoryChannelEnabled; // For DRAM use only, Max 32 channels enabled bit mask.

	uint8_t  DramBitWidth; // For DRAM use only.  See Dram Bit width type defines
	uint8_t  PaddingMem1[3];

	// Section: Total Board Power
	uint16_t TotalBoardPower; // Only needed for TCP Estimated case, where TCP = TGP+Total Board Power
	uint16_t BoardPowerPadding;

	struct smu11_smcpptable_v7_xgmi_training xgmi_training;

	// SECTION: UMC feature flags
	uint8_t  HsrEnabled;
	uint8_t  VddqOffEnabled;
	uint8_t  PaddingUmcFlags[2];

	// UCLK Spread Spectrum
	uq4_4_t  UclkSpreadPercent[16]; // unsure what the 16 is.

	// SECTION: Board Reserved
	uint32_t BoardReserved[11];

	// Padding for MMHUB - do not modify this
	uint32_t MmHubPadding[8]; // SMU internal use
};




// Beige Goby / Navi24 ; follows v7, the difference is SkuReserved.
// smu11_driver_if_sienna_cichlid.h doesn't pack Goby's pptable, but packing
// satisfies the sizes in struct smu_powerplay_table_header
struct smu11_smcpptable_v5 {
	// MAJOR SECTION: SKU PARAMETERS

	uint32_t Version;

	union powerplay_feature_control_smu11_0x40       features;
	struct smu11_smcpptable_v7_infrastructure_limits infrastructure_limits;

	// SECTION: Power Configuration
	enum PwrConfig_e  TotalPowerConfig; // Determines how PMFW calculates the power.
	uint8_t  TotalPowerPadding[3];

	// SECTION: APCC Settings
	uint32_t ApccPlusResidencyLimit;

	struct smu11_smcpptable_v7_smnclk_dpm  smnclk_dpm;
	union throttler_control_smu11_0x40     ThrottlerControlMask;
	union fw_dstate_features_smu11_0x40    FwDStateMask;
	struct smu11_smcpptable_v7_voltage     voltage_control;
	struct smu11_smcpptable_v7_dpm_config  dpm_config;
	struct smu11_smcpptable_v7_fan_control fan_control;
	struct smu11_smcpptable_v7_avfs        avfs;

	// SECTION: XGMI
	enum DPM_PSTATES_e  XgmiDpmPstates[NUM_XGMI_LEVELS_SMU11];
	uint8_t  XgmiDpmSpare[2];

	// SECTION: Advanced Options
	union dpm_debug_override_smu11_0x40  DebugOverrides;
	struct quadratic_f32  ReservedEquation[4];

	// SECTION: Sku Reserved
	enum CUSTOMER_VARIANT_e  CustomerVariant;

	struct smu11_smcpptable_v7_vc_btc vc_btc;

	//GPIO Board feature
	uint16_t LedGpio; // GeneriA GPIO flag used to control the radeon LEDs
	uint16_t GfxPowerStagesGpio; // Genlk_vsync GPIO flag used to control gfx power stages

	uint32_t SkuReserved[63];


	// MAJOR SECTION: BOARD PARAMETERS
	//SECTION: Gaming Clocks
	uint32_t GamingClk[6];

	struct smu11_smcpptable_v7_i2c_control        i2c_control;
	struct smu11_smcpptable_v7_svi2_parameters    svi2_parameters;
	struct smu11_smcpptable_v7_telemetry_settings telemetry;
	struct smu11_smcpptable_gpio_settings         gpio;
	struct smu11_smcpptable_v7_led_settings       led;
	struct smu11_smcpptable_v7_spread_spectrum    spread_spectrum;

	// Section: Memory Config
	uint32_t MemoryChannelEnabled; // For DRAM use only, Max 32 channels enabled bit mask.

	uint8_t  DramBitWidth; // For DRAM use only.  See Dram Bit width type defines
	uint8_t  PaddingMem1[3];

	// Section: Total Board Power
	uint16_t TotalBoardPower; // Only needed for TCP Estimated case, where TCP = TGP+Total Board Power
	uint16_t BoardPowerPadding;

	struct smu11_smcpptable_v7_xgmi_training xgmi_training;

	// SECTION: UMC feature flags
	uint8_t  HsrEnabled;
	uint8_t  VddqOffEnabled;
	uint8_t  PaddingUmcFlags[2];

	// UCLK Spread Spectrum
	uq4_4_t  UclkSpreadPercent[16]; // unsure what the 16 is.

	// SECTION: Board Reserved
	uint32_t BoardReserved[11];

	// Padding for MMHUB - do not modify this
	uint32_t MmHubPadding[8]; // SMU internal use
};

#pragma pack(pop) // restore old packing
#endif
