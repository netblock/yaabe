#ifndef POWERPLAY_SMU_H
#define POWERPLAY_SMU_H

#include "smu_driver_if.h"
#include "smu_v11_0_pptable.h"
#include "smu_v13_0_7_pptable.h"

#pragma pack(push, 1) // bios data must use byte alignment

union smu_powerplay {
	// for Navi and newer, the driver uses MP0_HWID in the Discovery.
	// Vega uses the classic PCI ID method.
	// The names here however are based off of the atom_common_table_header
	struct atom_common_table_header    table_header;
	struct smu_powerplay_table_header  pphead;
	struct atom_vega20_powerplay_table v11_0;
	struct smu_11_0_powerplay_table    v12_0; // v12 ~ v14
	struct smu_11_0_7_powerplay_table  v15_0; // V15 ~ v18

	// struct smu_13_0_7_powerplay_table v15_0; // navi3?
    // 13_0 is different from 13_0_0, and 13_0 is only used in aldebaran
    // 13_0 has more stuff than 13_0_0; I wonder if they can be spliced
    //struct smu_13_0_powerplay_table* aldebaran;

};

#pragma pack(pop) // restore old packing
#endif
