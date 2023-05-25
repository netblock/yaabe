#ifndef ATOMTREE_H
#define ATOMTREE_H

#include "atomtree_data_tables.h"
#include "atomtree_common.h"
#include "atui.h"


#define BIOS_IMAGE_SIZE_OFFSET 2
#define BIOS_IMAGE_SIZE_UNIT 512
#define OFFSET_TO_POINTER_TO_ATOM_ROM_HEADER 0x48
//#define OFFSET_TO_ATOM_ROM_IMAGE_SIZE 0x2

#define ATOM_BIOS_MAGIC     0xAA55
#define ATOM_ATI_MAGIC_PTR  0x30
#define ATOM_ATI_MAGIC      " 761295520"
#define ATOM_ROM_TABLE_PTR  0x48
#define ATOM_ROM_PART_NUMBER_PTR    0x6E
#define ATOM_ROM_MAGIC      "ATOM"
#define ATOM_ROM_MAGIC_PTR  4

struct atom_tree* atombios_parse(void* bios); 
void* bios_fastforward(void* memory, long size);
void* bios_fastforward_odd(void* memory, long size);
/*
enum atomtree_common_version {
    v1_0=100, v1_1,v1_2,v1_3,v1_4,v1_5,v1_6,v1_7,v1_8,v1_9,v1_10,v1_11,v1_12,
    v2_0=200, v2_1,v2_2,v2_3,v2_4,v2_5,v2_6,v2_7,v2_8,v2_9,v2_10,v2_11,v2_12,
    v3_0=300, v3_1,v3_2,v3_3,v3_4,v3_5,v3_6,v3_7,v3_8,v3_9,v3_10,v3_11,v3_12,
    v4_0=400, v4_1,v4_2,v4_3,v4_4,v4_5,v4_6,v4_7,v4_8,v4_9,v4_10,v4_11,v4_12,
    nover=0
};
enum atomtree_common_version get_ver(struct atom_common_table_header* header);
void set_ver(enum atomtree_common_version* ver, struct atom_common_table_header* header);
*/

struct atomtree_rom_header_v2_2
{
  struct atom_common_table_header table_header;
  uint8_t  atom_bios_string[4];        //enum atom_string_def atom_bios_string;     //Signature to distinguish between Atombios and non-atombios,
  uint16_t bios_segment_address;
  uint16_t protectedmodeoffset;
  uint16_t configfilenameoffset;
  uint16_t crc_block_offset; // TODO
  uint16_t vbios_bootupmessageoffset;
  uint16_t int10_offset;
  uint16_t pcibusdevinitcode;
  uint16_t iobaseaddress;
  uint16_t subsystem_vendor_id;
  uint16_t subsystem_id;
  uint16_t pci_info_offset;
  uint16_t masterhwfunction_offset;      //Offest for SW to get all command function offsets, Don't change the position
  uint16_t masterdatatable_offset;       //Offest for SW to get all data table offsets, Don't change the position
  uint16_t reserved;
  uint32_t pspdirtableoffset;
};

struct atom_tree {
	struct atom_tree* dot;
	void* dotdot;

	void* parentfile; // to keep track of mallocs, if bios > parentfile.
	long parentsize;

	struct atomtree_master_datatable_v2_1 data_table;
	//struct atom_master_cmdtable_v2_1 cmd_table; // atom_master_list_of_command_functions_v2_1 TODO

	struct atom_rom_header_v2_2* leaves;
	void* bios;
	uint32_t bios_size;	
	//bios date, etc?

	//bios_parser2_construct populates Display Core stuff
	//https://docs.kernel.org/gpu/amdgpu/display/index.html

	void* protected_mode;
	char* config_filename;
	void* crc_block;
	char* bootup_mesage;
	void* int10;
	void* psp_dir_table;

	atui_branch* atui_root;
};

struct atombios_image { // TODO: is this worth a bother?
	uint16_t rom_signature; // little endian: AA55
	uint8_t image_size; //0x2;
	uint8_t rsvd0[46];
	uint8_t amd_vbios_sig[10]; // 0x30; " 761295520" There is a space.
	uint8_t rsvd1[22];
	uint8_t vbios_date[14]; //0x30
	//...
};

#endif
