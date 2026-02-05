#ifndef POWERPLAY_SMU_DRIVER_IF_H
#define POWERPLAY_SMU_DRIVER_IF_H
// includes are in the middle

#pragma pack(push, 1) // bios data must use byte alignment
enum smu_smc_pptable_version:uint32_t {
	PPTABLE_VEGA20_SMU = 3,
	PPTABLE_NAVI24_SMU = 5, // Beige Goby
	PPTABLE_NAVI22_SMU = 6, // Navy Flounder
	PPTABLE_NAVI21_SMU = 7, // Sienna Cichlid
	PPTABLE_NAVI10_SMU = 8,
	PPTABLE_SMU13_0_7 = 39,
};
enum smu11_driver_if_version {
	// #define SMU11_DRIVER_IF_VERSION ; smu_v11_0_check_fw_version
	// this number seems to grow fast
	smu11_driver_if_vega20 = 0x13, // with pptable v3
	smu11_driver_if_navi10 = 0x33, // with pptable v8
	smu11_driver_if_navi21 = 0x40, // Sienna Cichlid; pptable v7
	smu13_0_7_driver_if    = 0x35, // pptable v39
};
#pragma pack(pop) // restore old packing

#include "smu11_driver_if.h"
#include "smu13_driver_if_v13_0_7.h"

#pragma pack(push, 1) // bios data must use byte alignment
union smc_pptables { // PPTable_t in driver_if.h in the kernel
	enum smu_smc_pptable_version Version;
	struct smu11_smcpptable_v3   v3;
	struct smu11_smcpptable_v5   v5;
	struct smu11_smcpptable_v7   v7;
	struct smu11_smcpptable_v8   v8;

	union smu13_smcpptable_v39  v39;
};
#pragma pack(pop) // restore old packing
#endif
