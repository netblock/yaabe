/*
For atomtree's abstract, check out data_tables.h
atomtree.h is mainly about header conglomeration, fundamental atomtree types and
initial bios crawling.
*/

#ifndef ATOMTREE_H
#define ATOMTREE_H

#include "bios_headers.h"

#include "atui_types.h"

#include "atomtree_tools.h"
#include "pci_id_lut.h"
#include "data_tables.h"
#include "nonatom_tables.h"



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

	atui_node* atui_root;
	GATUITree* self;
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
