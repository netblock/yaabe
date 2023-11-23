#ifndef POWERPLAY_H
#define POWERPLAY_H

// common powerplay definitions
// check bottom for includes

#pragma pack(push, 1) // bios data must use byte alignment

struct smu_powerplay_table_header {
	struct atom_common_table_header header;
	uint8_t  table_revision;
	uint16_t table_size; // Driver portion table size. The offset to smc_pptable including header size
};

// SMU 11, 13
union powerplay_platform_caps {
	uint32_t platform_caps;
	struct { uint32_t
		powerplay     :0-0 +1, // whether CCC needs to show Powerplay page.
		sbios_powersource :1-1 +1, // whether power source notificaiton is done by SBIOS instead of OS.
		hardware_dc   :2-2 +1, // whether DC mode notificaiton is done by GPIO pin directly.
		BACO          :3-3 +1, // whether board supports the BACO circuitry. BACO is Bus Active, Chip Off. A low-power mode whereby most of the GPU is shut-off during idle periods in order to drastically cut the power consumption of the graphics card. BACO is also known as AMD ZeroCore Power mode.
		MACO          :4-4 +1, // whether board supports the MACO circuitry.
		shadow_pstate :5-5 +1, // whether board supports the Shadow Pstate.
		reserved     :31-6 +1;
	};
};


//typedef struct quadratic_f32 QuadraticInt_t;
struct quadratic_f32 {
	float32_t a;
	float32_t b;
	float32_t c;
};

//typedef struct linear_f32 LinearInt_t;
struct linear_f32 {
	float32_t m;
	float32_t b;
};

//typedef struct droop_f32 DroopInt_t;
struct droop_f32 {
	float32_t a;
	float32_t b;
	float32_t c;
};

enum XGMI_LINK_RATE_e:uint8_t { // rate x Gbps
	XGMI_LINK_RATE_2  = 2,
	XGMI_LINK_RATE_4  = 4,
	XGMI_LINK_RATE_8  = 8,
	XGMI_LINK_RATE_12 = 12,
	XGMI_LINK_RATE_16 = 16,
	XGMI_LINK_RATE_17 = 17,
	XGMI_LINK_RATE_18 = 18,
	XGMI_LINK_RATE_19 = 19,
	XGMI_LINK_RATE_20 = 20,
	XGMI_LINK_RATE_21 = 21,
	XGMI_LINK_RATE_22 = 22,
	XGMI_LINK_RATE_23 = 23,
	XGMI_LINK_RATE_24 = 24,
	XGMI_LINK_RATE_25 = 25,
	XGMI_LINK_RATE_COUNT = 26,
};

enum XGMI_LINK_WIDTH_e:uint8_t {
	XGMI_LINK_WIDTH_1  = 0,
	XGMI_LINK_WIDTH_2  = 2,
	XGMI_LINK_WIDTH_4  = 3,
	XGMI_LINK_WIDTH_8  = 4,
	XGMI_LINK_WIDTH_9  = 5,
	XGMI_LINK_WIDTH_16 = 6,
	XGMI_LINK_WIDTH_COUNT = 7,
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


#pragma pack(pop) // restore old packing

#include "smu11_driver_if.h"
#include "smu_v11_0_pptable.h"
#include "smu13_driver_if_v13_0_7.h"
#include "smu_v13_0_7_pptable.h"

#endif
