#ifndef ATOMTREE_H
#define ATOMTREE_H

#include "atomtree_common.h"
#include "atomtree_data_tables.h"
#include <gtk/gtk.h>

//#include "atui.h"
typedef struct _atui_branch atui_branch;


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

void atomtree_bios_checksum(struct atom_tree* atree);

struct atom_tree* atombios_parse(
		void* bios, uint32_t alloc_size, bool generate_atui
);

struct atombios_image {
	uint16_t atombios_magic; // little endian: 0xAA55
	uint8_t image_size; //0x02
	uint8_t rsvd0[30];
	uint8_t checksum; // 0x21
	uint8_t rsvd1[13];
	uint8_t number_of_strings; // 0x2F
	uint8_t atomati_magic[11]; // 0x30; " 761295520" There is a space.
	uint8_t rsvd2[13];
	uint16_t bios_header; // 0x48
	uint8_t rsvd3[6];
	uint8_t bios_date[15]; // 0x50
	uint8_t rsvd4[15];
	uint16_t atombios_strings_offset; // 0x6E 
	uint8_t rsvd5[16];
	uint8_t part_number_offset; // 0x80 ; only use if number_of_strings == 0
	uint8_t rsvd6[19];
	uint8_t asic_bus_mem_type_offset; // 0x94; I think it's a 20-byte str
	// any more?
/*
struct atombios_image* img = atree->bios;
uint8_t* strs = atree->bios + img->atombios_strings_offset;
uint8_t i = 0;
while(*strs) {														  
	printf("%s\n", strs);
	strs += (strlen(strs) + 1);
	i++;
}
// it seems it's always i == 13

*/
};

struct atom_tree {
	struct atom_tree* dot;
	void* dotdot;

	GFile* biosfile;
	int64_t biosfile_size;
	void* alloced_bios;

	union {
		void* bios;
		struct atombios_image* image;
	};
	struct atom_rom_header_v2_2* leaves;

	//bios date, etc?
	uint32_t bios_image_size;

	struct atomtree_master_datatable_v2_1 data_table;
	//struct atom_master_cmdtable_v2_1 cmd_table; // atom_master_list_of_command_functions_v2_1 TODO


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


#endif
