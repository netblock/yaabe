/*
For atomtree's abstract, check out data_tables.h
atomtree.h is mainly about header conglomeration, fundamental atomtree types and
initial bios crawling.
*/

#ifndef ATOMTREE_H
#define ATOMTREE_H

#include "bios_headers.h"

#include "atui_types.h"

#include "pci_id_lut.h"
#include "data_tables.h"
#include "asic_reg_tools.h"

// ppatui.py autogenerated:
#include "asic_reg_indices.h"

struct pci_rom_tables {
	bool is_efi;
	union {
		struct efi_pci_device_driver_image* efi;
		struct pci_rom_header* header;
	};
	struct pcir_data_structure* pcir;
};
struct atomtree_pci_tables {
	uint8_t num_images;
	struct pci_rom_tables* pci_tables;
};


struct atomtree_discovery_ip_entry {
	union {
		void* raw;
		union  discovery_ip_entry*        entry;
		struct discovery_ip_entry_header* header;
		struct discovery_ip_entry_v1*     v1;
		struct discovery_ip_entry_v3*     v3;
		struct discovery_ip_entry_v3*     v4_32;
		struct discovery_ip_entry_v4_64*  v4_64;
	};
	semver ver;
};
struct atomtree_discovery_ip_die {
	 struct ip_discovery_die_header* header;
	 struct atomtree_discovery_ip_entry* entries;
};

struct atomtree_discovery_table {
	struct discovery_fw_blob* blob;

	semver binary_ver;
	semver ip_ver;
	semver gc_ver;
	semver harvest_ver;
	semver vcn_ver;
	semver mall_ver;
	semver nps_ver;
	uint8_t num_dies;

	struct ip_discovery_header*       ip_discovery;
	struct atomtree_discovery_ip_die  dies[IP_DISCOVERY_MAX_NUM_DIES];
	union  discovery_gc_info*         gc_info;
	struct discovery_harvest_table*   harvest;
	struct discovery_vcn_info_v1_0*   vcn_info;
	union  discovery_mall_info*       mall_info;
	struct discovery_nps_info_v1_0*   nps_info;
};

enum atomtree_psp_fw_payload_type:uint8_t {
// This enum may not be technically necessary given
// struct amd_fw_header.fw_type and .fw_id
// but there's not much info about it and seems generic
	PSPFW_DISCOVERY = AMD_ABL7,
};
struct atomtree_psp_directory_entries {
	union {
		// TODO some fw blobs don't do the psp fw header
		// A trick to tell is if,
		// struct psp_directory_entry.type == struct amd_fw_header.fw_type
		void* raw;
		struct amd_fw_header* header;

		struct atomtree_discovery_table discovery;
	};

	enum atomtree_psp_fw_payload_type type;
	bool has_fw_header;
};
struct atomtree_psp_directory {
	struct psp_directory* directory;
	struct atomtree_psp_directory_entries* fw_entries;
};

struct atomtree_rom_header {
	semver ver;
	union {
		void* leaves;
		struct atom_common_table_header* table_header;
		struct atom_rom_header_v1_1* v1_1;
		struct atom_rom_header_v2_1* v2_1;
		struct atom_rom_header_v2_2* v2_2;
	};

	// have rom_header children in main atom_tree.
};

struct atom_tree {
	// file handling
	size_t biosfile_size;
	void* alloced_bios;

	// start of image; eg 0xAA55
	union {
		void* bios;
		struct vbios_rom_header* image;
	};
	uint32_t pci_first_image_size;

	// for PCI ID based HW IP designation, not for new AMD cards
	// TODO atomtree for HW IP when discovery.h is implemented.
	enum amd_asic_type chip_type;

	uint8_t num_of_crawled_strings;
	char** atombios_strings;

	struct atomtree_pci_tables pci_tables;
	struct atomtree_rom_header rom_header;
	struct atomtree_master_datatable data_table;
	//struct atom_master_cmdtable_v2_1 cmd_table; // atom_master_list_of_command_functions_v2_1 TODO


	//bios_parser2_construct populates Display Core stuff
	//https://docs.kernel.org/gpu/amdgpu/display/index.html

	void* protected_mode;
	char* config_filename;
	uint32_t* crc_block;
	char* bootup_mesage;
	void* int10;
	void* pci_info;

	struct atomtree_psp_directory psp_directory;

	atui_branch* atui_root;
};



semver 
atom_get_ver(
		struct atom_common_table_header const* header
		);
void
atom_set_ver(
		semver ver,
		struct atom_common_table_header* header
		);

void
atomtree_calculate_checksums(
		struct atom_tree* atree
		);

struct atom_tree*
atombios_parse(
		void* bios,
		uint32_t alloc_size
		);

void
atomtree_destroy(
		struct atom_tree* const atree
		);

#endif
