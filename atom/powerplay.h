/*
common powerplay definitions
check bottom for includes
*/

#ifndef POWERPLAY_H
#define POWERPLAY_H
#pragma pack(push, 1) // bios data must use byte alignment

struct smu_powerplay_table_header {
	struct atom_common_table_header  header;
	uint8_t  table_revision;
	uint16_t table_size; // Driver portion table size. The offset to smc_pptable including header size
	uint32_t golden_pp_id;    // PPGen use only: PP Table ID on the Golden Data Base
	uint32_t golden_revision; // PPGen use only: PP Table Revision on the Golden Data Base
	uint16_t format_id;       // PPGen use only: PPTable for different ASICs.
};

enum ATOM_PP_THERMALCONTROLLER:uint8_t {
	ATOM_PP_THERMALCONTROLLER_NONE            = 0,
	ATOM_PP_THERMALCONTROLLER_LM63            = 1,  // Not used by PPLib
	ATOM_PP_THERMALCONTROLLER_ADM1032         = 2,  // Not used by PPLib
	ATOM_PP_THERMALCONTROLLER_ADM1030         = 3,  // Not used by PPLib
	ATOM_PP_THERMALCONTROLLER_MUA6649         = 4,  // Not used by PPLib
	ATOM_PP_THERMALCONTROLLER_LM64            = 5,
	ATOM_PP_THERMALCONTROLLER_F75375          = 6,  // Not used by PPLib
	ATOM_PP_THERMALCONTROLLER_ASC7512_RV6xx   = 7,
	ATOM_PP_THERMALCONTROLLER_RV770           = 8,
	ATOM_PP_THERMALCONTROLLER_ADT7473         = 9,
	ATOM_PP_THERMALCONTROLLER_KONG           = 10,
	ATOM_PP_THERMALCONTROLLER_EXTERNAL_GPIO  = 11,
	ATOM_PP_THERMALCONTROLLER_EVERGREEN      = 12,
	ATOM_PP_THERMALCONTROLLER_EMC2103        = 13, // Only fan control will be implemented, do NOT show this in PPGen.
	ATOM_PP_THERMALCONTROLLER_SUMO           = 14, // Sumo type, used internally
	ATOM_PP_THERMALCONTROLLER_NISLANDS       = 15,
	ATOM_PP_THERMALCONTROLLER_SISLANDS       = 16,
	ATOM_PP_THERMALCONTROLLER_LM96163        = 17,
	ATOM_PP_THERMALCONTROLLER_CISLANDS       = 18,
	ATOM_PP_THERMALCONTROLLER_KAVERI         = 19,
	ATOM_PP_THERMALCONTROLLER_ICELAND        = 20,
	ATOM_PP_THERMALCONTROLLER_TONGA          = 21,
	ATOM_PP_THERMALCONTROLLER_FIJI           = 22,
	ATOM_PP_THERMALCONTROLLER_POLARIS10      = 23,
	ATOM_PP_THERMALCONTROLLER_VEGA10         = 24,
	ATOM_PP_THERMALCONTROLLER_VEGA12         = 25,
	ATOM_PP_THERMALCONTROLLER_VEGA20         = 26,
	ATOM_PP_THERMALCONTROLLER_NAVI10         = 27,
	ATOM_PP_THERMALCONTROLLER_SIENNA_CICHLID = 28,
	ATOM_PP_THERMALCONTROLLER_ADT7473_WITH_INTERNAL = 0x89, // ADT7473 Fan Control + Internal Thermal Controller
	ATOM_PP_THERMALCONTROLLER_EMC2103_WITH_INTERNAL = 0x8D, // EMC2103 Fan Control + Internal Thermal Controller
};

/******************************************************************************/
// pplib.h / pptable.h / pptable_vega10.h

struct pplib_subtable_header {
	uint8_t  RevId;
};

union atom_pp_fanparameters {
	uint8_t  FanParameters;
	struct { uint8_t
		tachometer_pulses_per_revolution :3-0 +1,
		rsvd                             :6-4 +1,
		no_fan                           :7-7 +1;
	};
};

enum atom_pplib_classification_ui:uint16_t {
	ATOM_PPLIB_CLASSIFICATION_UI_NONE         = 0,
	ATOM_PPLIB_CLASSIFICATION_UI_BATTERY      = 1,
	ATOM_PPLIB_CLASSIFICATION_UI_BALANCED     = 3,
	ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE  = 5,
};
union atom_pplib_classification {
	uint16_t Classification;
	struct { uint16_t
		ui_label           :2-0 +1, // enum atom_pplib_classification_ui
		boot               :3-3 +1,
		thermal            :4-4 +1,
		limited_power      :5-5 +1,
		reset              :6-6 +1,
		forced             :7-7 +1,
		performance_3D     :8-8 +1,
		overdrive_template :9-9 +1,
		uvd_state         :10-10 +1,
		low_3D            :11-11 +1,
		acpi              :12-12 +1,
		hd2_state         :13-13 +1,
		hd_state          :14-14 +1,
		sd_state          :15-15 +1;
	};
};

union atom_pplib_classification2 {
	uint16_t Classification2;
	struct { uint16_t
		limitedpowersource_2 :0-0 +1,
		ULV                  :1-1 +1,
		multi_view_codec     :2-2 +1, // BD-3D
		rsvd0               :15-3 +1;
	};
};

union atom_pplib_caps_and_settings {
	uint32_t CapsAndSettings;
	struct { uint32_t
		single_display_only     :0-0 +1,
		supports_video_playback :1-1 +1,
		pcie_link_speed         :2-2 +1, // 0=PCIe1, 1=PCIe2
		pcie_link_width         :7-3 +1, // lanes - 1: 1, 2, 4, 8, 12, 16 permitted by PCIE spec ; however it might be that 0=1x .. 15=16x
		limited_refreshrate    :11-8 +1, // 1=50Hz, all else = TBD
		disable_loadbalancing  :12-12 +1, // software side
		enable_timestamp_sleep :13-13 +1,
		disallow_on_dc         :14-14 +1,
		enable_varibright      :15-15 +1,
		swstate_memory_dll_off :16-16 +1,
		m3_arb                 :18-17 +1,
		enable_drr             :19-19 +1,
		rsvd0                  :31-20 +1;
	};
};

enum atom_ppm:uint8_t {
	ATOM_PPM_A_A = 1,
	ATOM_PPM_A_I = 2,
};
struct atom_pplib_ppm_table {
	uint8_t  RevId;
	enum atom_ppm PpmDesign;
	uint16_t CpuCoreNumber;
	uint32_t PlatformTDP;
	uint32_t SmallACPlatformTDP;
	uint32_t PlatformTDC;
	uint32_t SmallACPlatformTDC;
	uint32_t ApuTDP;
	uint32_t DGpuTDP;  
	uint32_t DGpuUlvPower;
	uint32_t Tjmax;
};

/******************************************************************************/
// SMU 11, 13

// SMU 11, 13
union powerplay_platform_caps {
	uint32_t platform_caps;
	struct { uint32_t
		powerplay         :0-0 +1, // whether CCC needs to show Powerplay page.
		sbios_powersource :1-1 +1, // whether power source notificaiton is done by SBIOS instead of OS.
		hardware_dc       :2-2 +1, // whether DC mode notificaiton is done by GPIO pin directly.
		BACO              :3-3 +1, // whether board supports the BACO circuitry. BACO is Bus Active, Chip Off. A low-power mode whereby most of the GPU is shut-off during idle periods in order to drastically cut the power consumption of the graphics card. BACO is also known as AMD ZeroCore Power mode.
		MACO              :4-4 +1, // whether board supports the MACO circuitry.
		shadow_pstate     :5-5 +1, // whether board supports the Shadow Pstate.
		reserved         :31-6 +1;
	};
};


//typedef struct quadratic_f32  QuadraticInt_t;
struct quadratic_f32 {
	float32_t a;
	float32_t b;
	float32_t c;
};

//typedef struct linear_f32  LinearInt_t;
struct linear_f32 {
	float32_t m;
	float32_t b;
};

//typedef struct droop_f32  DroopInt_t;
struct droop_f32 {
	float32_t a;
	float32_t b;
	float32_t c;
};

enum PPT_THROTTLER_e {
	PPT_THROTTLER_PPT0  = 0,
	PPT_THROTTLER_PPT1  = 1,
	PPT_THROTTLER_PPT2  = 2,
	PPT_THROTTLER_PPT3  = 3,
	PPT_THROTTLER_COUNT = 4,
};

enum POWER_SOURCE_e {
	POWER_SOURCE_AC    = 0,
	POWER_SOURCE_DC    = 1,
	POWER_SOURCE_COUNT = 2,
};

enum CUSTOMER_VARIANT_e:uint8_t {
	CUSTOMER_VARIANT_ROW    = 0,
	CUSTOMER_VARIANT_FALCON = 1,
	CUSTOMER_VARIANT_COUNT  = 2,
};

enum TDC_THROTTLER_e {
	TDC_THROTTLER_GFX = 0,
	TDC_THROTTLER_SOC = 1,
	TDC_THROTTLER_U   = 2,

	TDC_THROTTLER_COUNT_SMU11 = 2,
	TDC_THROTTLER_COUNT_SMU13 = 3,
};

enum UCLK_DIV_e:uint8_t {
	UCLK_DIV_BY_1 = 0,
	UCLK_DIV_BY_2 = 1,
	UCLK_DIV_BY_4 = 2,
	UCLK_DIV_BY_8 = 3,
};

enum PwrConfig_e:uint8_t {
	PWR_CONFIG_TDP = 0,
	PWR_CONFIG_TGP = 1,
	PWR_CONFIG_TCP_ESTIMATED = 2,
	PWR_CONFIG_TCP_MEASURED  = 3,
};

enum PCIE_SPEED_e:uint8_t {
	PCIE_LINK_SPEED_PCIE_1 = 0,
	PCIE_LINK_SPEED_PCIE_2 = 1,
	PCIE_LINK_SPEED_PCIE_3 = 2,
	PCIE_LINK_SPEED_PCIE_4 = 3,
	PCIE_LINK_SPEED_PCIE_5 = 4,
};
enum PCIE_WIDTH_e:uint8_t {
	PCIE_LINK_WIDTH_x1  = 1,
	PCIE_LINK_WIDTH_x2  = 2,
	PCIE_LINK_WIDTH_x4  = 3,
	PCIE_LINK_WIDTH_x8  = 4,
	PCIE_LINK_WIDTH_x12 = 5,
	PCIE_LINK_WIDTH_x16 = 6,
};

enum DPM_PSTATES_e:uint8_t { // TODO is this just PPT_THROTTLER?
	DPM_PSTATE_P0 = 0,
	DPM_PSTATE_P1 = 1,
	DPM_PSTATE_P2 = 2,
	DPM_PSTATE_P3 = 3,
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

enum GFXCLK_SOURCE_e:uint8_t {
	GFXCLK_SOURCE_PLL = 0,
	GFXCLK_SOURCE_DFLL = 1,
};

#pragma pack(pop) // restore old packing

#include "pplib.h"
#include "pptable.h"
#include "pptable_vega10.h"
#include "smu11_driver_if.h"
#include "smu_v11_0_pptable.h"
#include "smu13_driver_if_v13_0_7.h"
#include "smu_v13_0_7_pptable.h"

#endif
