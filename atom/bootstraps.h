/*
These concern the 33 32-bit bitfields between 0x70 and 0xF4.
There's limited information about what exists there.
*/


#ifndef BOOTSTRAPS_H
#define BOOTSTRAPS_H
#pragma pack(push, 1) // bios data must use byte alignment

union STRAP_BIF_STRAP_64BAR_DIS_DEV0_F0 {
	uint32_t raw_data;
	struct { uint32_t
		rsvd_25_0                   :25-0 +1,
		BIF_STRAP_64BAR_DIS_DEV0_F0 :26-26 +1, // Disable 64-bit Base Address Register for Device 0 Function 0 (1 = disable). Affects bit 2 of BLOCK_MEM_TYPE for each BAR register in the PCI configuration space.
		rsvd_31_27                  :31-27 +1;
	};
};

union BIF_STRAP_SUBSYS_ID_DEV0_F0 {
	uint32_t raw_data;
	struct { uint32_t
		rsvd_3_0                     :3-0 +1,
		BIF_STRAP_SUBSYS_ID_DEV0_F0 :19-4 +1, // Subsystem ID (SSID) for the PCI configuration space for Function 0. If enabled, the SSID for the secondary display function (F1) is the set to the same value as the primary display function (F0) with bit 0 inverted.
		rsvd_31_20                  :31-20 +1;
	};
};

union bif_strap_pci_func {
	uint64_t raw_data;
	struct { uint64_t
		rsvd_11_0                       :11-0 +1,
		BIF_STRAP_FUNC_EN_DEV0_F1       :12-12 +1, // Multi-function device select. Affects bit 7 of the Header register in PCI configuration space. 0 = no audio.
		rsvd_28_13                      :28-13 +1,
		BIF_STRAP_SUBSYS_VEN_ID_DEV0_F0 :44-29 +1, // Subsystem Vendor ID (SSVID) in the PCI configuration space. If the VBIOS ROM is not used, then the SBIOS is permitted to overwrite this register for each PCI function on the device before the enumeration cycle is initiated, otherwise the default value is used.
		rsvd_63_45                      :63-45 +1;
	};
};


enum MEM_AP_SIZE:uint32_t {
	MEM_AP_SIZE_256MB = 0,
	MEM_AP_SIZE_512MB = 1,
	MEM_AP_SIZE_1GB   = 2,
	MEM_AP_SIZE_2GB   = 3,
	MEM_AP_SIZE_4GB   = 4,
	MEM_AP_SIZE_8GB   = 5,
	MEM_AP_SIZE_16GB  = 6,
	MEM_AP_SIZE_32GB  = 7,
};

union BIF_STRAP_MEM_AP_SIZE_DEV0_F0 {
	uint32_t raw_data;
	struct {
		uint32_t rsvd_6_0                              :6-0 +1;
		enum MEM_AP_SIZE BIF_STRAP_MEM_AP_SIZE_DEV0_F0 :9-7 +1;
		uint32_t rsvd_21_10                           :21-10 +1;
		uint32_t BIF_STRAP_VGA_DIS_DEV0_F0            :22-22 +1; // VGA Disable determines whether or not the card will be recognized as the system's VGA controller (via the SUBCLASS field in the PCI configuration space). 1 = disable VGA
		uint32_t rsvd_31_23                           :31-23 +1;
	};
};


struct vega_boot_straps {
	uint32_t unknown0[14];
	union STRAP_BIF_STRAP_64BAR_DIS_DEV0_F0 bar_disable;
	uint32_t unknown1;
	union BIF_STRAP_SUBSYS_ID_DEV0_F0  ssid;
	uint32_t unknown2;
	union bif_strap_pci_func  ssvid;
	union BIF_STRAP_MEM_AP_SIZE_DEV0_F0  mem_ap_size;
	uint32_t unknown3[12];
};

#pragma pack(pop) // restore old packing
#endif
