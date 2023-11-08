#ifndef POWERPLAY_H
#define POWERPLAY_H
// common powerplay definitions
// check bottom for includes


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
	float a;
	float b;
	float c;
};

//typedef struct linear_f32 LinearInt_t;
struct linear_f32 {
	float m;
	float b;
};

//typedef struct droop_f32 DroopInt_t;
struct droop_f32 {
	float a;
	float b;
	float c;
};

enum PPT_THROTTLER_e {
	PPT_THROTTLER_PPT0  = 0,
	PPT_THROTTLER_PPT1  = 1,
	PPT_THROTTLER_PPT2  = 2,
	PPT_THROTTLER_PPT3  = 3,
	PPT_THROTTLER_COUNT = 4,
};

// navi10
#include <smu11_driver_if.h>
#include <smu_v11_0_pptable.h>

#endif
