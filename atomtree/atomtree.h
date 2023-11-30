/*
For atomtree's abstract, check out atomtree_data_tables.h
atomtree.h is mainly about atomtree metadata and initial bios crawling.
*/

#ifndef ATOMTREE_H
#define ATOMTREE_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <assert.h>

#ifdef C2X_COMPAT
typedef uint8_t char8_t;
#else
#include <uchar.h>
#endif

typedef _Float16 float16_t;
typedef _Float32 float32_t;
typedef _Float64 float64_t;
//typedef _Float128 float128_t; // currently unnecessary
// AVX-512 does partial native 128-bit?

// we're dealing with a byte-packed ABI.
static_assert(CHAR_BIT == 8);
static_assert(sizeof(uint8_t) == 1);
static_assert(sizeof(uint16_t) == 2);
static_assert(sizeof(uint32_t) == 4);
static_assert(sizeof(uint64_t) == 8);
static_assert(sizeof(int8_t) == 1);
static_assert(sizeof(int16_t) == 2);
static_assert(sizeof(int32_t) == 4);
static_assert(sizeof(int64_t) == 8);
static_assert(sizeof(char8_t) == 1);
static_assert(sizeof(float16_t) == 2);
static_assert(sizeof(float32_t) == 4);
static_assert(sizeof(float64_t) == 8);
//static_assert(sizeof(float128_t) == 16);
#pragma pack(push, 1)
struct _ninebytes { uint32_t a; uint8_t b; float32_t c; };
struct _tenbytes { int8_t a; uint64_t b; uint8_t c; };
#pragma pack(pop)
static_assert(sizeof(struct _ninebytes) == 9);
static_assert(sizeof(struct _tenbytes) == 10);

//TODO Q-notation type
// https://en.wikipedia.org/wiki/Q_(number_format)
// "Q2" means Qm.2 where m fills the rest of the natural width
/*
typedef union {
	uint16_t raw;
	struct { uint16_t
		fraction :1-0 +1,
		integer :16-2 +1;
	};
} uq14_2_t;
*/


#include "ddrmoderegisters.h"
#include "atomfirmware.h"
#include "umctimings.h"
#include "powerplay.h"
#include "atombios.h"

enum atomtree_common_version:uint16_t;
typedef struct _atui_branch atui_branch;

#include "atomtree_data_tables.h"
// see bottom for more includes



#define ATOM_BIOS_MAGIC 0xAA55
#define ATOM_ATI_MAGIC  " 761295520"
#define BIOS_IMAGE_SIZE_UNIT 512
/*
#define BIOS_IMAGE_SIZE_OFFSET 2
#define BIOS_IMAGE_SIZE_UNIT 512
#define OFFSET_TO_POINTER_TO_ATOM_ROM_HEADER 0x48
#define OFFSET_TO_ATOM_ROM_IMAGE_SIZE 0x2

#define ATOM_BIOS_MAGIC    0xAA55
#define ATOM_ATI_MAGIC_PTR 0x30
#define ATOM_ATI_MAGIC     " 761295520"
#define ATOM_ROM_TABLE_PTR 0x48
#define ATOM_ROM_PART_NUMBER_PTR 0x6E
#define ATOM_ROM_MAGIC     "ATOM"
#define ATOM_ROM_MAGIC_PTR 4
*/

#pragma pack(push, 1) // bios data must use byte alignment
struct atombios_image {
	uint16_t atombios_magic; // little endian: 0xAA55
	uint8_t  image_size; // 0x02
	uint8_t  rsvd0[30];
	uint8_t  checksum;   // 0x21
	uint8_t  rsvd1[13];
	uint8_t  number_of_strings; // 0x2F
	uint8_t  atomati_magic[11]; // 0x30; " 761295520" There is a space.
	uint8_t  rsvd2[13];
	uint16_t bios_header;   // 0x48
	uint8_t  rsvd3[6];
	uint8_t  bios_date[15]; // 0x50
	uint8_t  rsvd4[15];
	uint16_t atombios_strings_offset; // 0x6E
	uint8_t  rsvd5[16];
	uint8_t  part_number_offset; // 0x80 ; only use if number_of_strings == 0
	uint8_t  rsvd6[19];
	uint8_t  asic_bus_mem_type_offset; // 0x94; I think it's a 20-byte str
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
#pragma pack(pop) // restore old packing


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
	char8_t* config_filename;
	uint32_t* crc_block;
	char8_t* bootup_mesage;
	void* int10;
	void* psp_dir_table;

	atui_branch* atui_root;
};



enum atomtree_common_version:uint16_t {
	nover=0,
	v1_0=100, v1_1,v1_2,v1_3,v1_4,v1_5,v1_6,v1_7,v1_8,v1_9,v1_10,v1_11,v1_12,
	v2_0=200, v2_1,v2_2,v2_3,v2_4,v2_5,v2_6,v2_7,v2_8,v2_9,v2_10,v2_11,v2_12,
	v3_0=300, v3_1,v3_2,v3_3,v3_4,v3_5,v3_6,v3_7,v3_8,v3_9,v3_10,v3_11,v3_12,
	v4_0=400, v4_1,v4_2,v4_3,v4_4,v4_5,v4_6,v4_7,v4_8,v4_9,v4_10,v4_11,v4_12,
	v5_0=500, v5_1,v5_2,v5_3,v5_4,v5_5,v5_6,v5_7,v5_8,v5_9,v5_10,v5_11,v5_12,
	v6_0=600, v6_1,v6_2,v6_3,v6_4,v6_5,v6_6,v6_7,v6_8,v6_9,v6_10,v6_11,v6_12,
	v7_0=700, v7_1,v7_2,v7_3,v7_4,v7_5,v7_6,v7_7,v7_8,v7_9,v7_10,v7_11,v7_12,
	v8_0=800, v8_1,v8_2,v8_3,v8_4,v8_5,v8_6,v8_7,v8_8,v8_9,v8_10,v8_11,v8_12,
	v9_0=900, v9_1,v9_2,v9_3,v9_4,v9_5,v9_6,v9_7,v9_8,v9_9,v9_10,v9_11,v9_12,
	v10_0=1000, v10_1,v10_2,v10_3,v10_4,v10_5,v10_6,v10_7,v10_8,v10_9,v10_10,
	v10_11,v10_12,
	v11_0=1100, v11_1,v11_2,v11_3,v11_4,v11_5,v11_6,v11_7,v11_8,v11_9,v11_10,
	v11_11,v11_12,
	v12_0=1200, v12_1,v12_2,v12_3,v12_4,v12_5,v12_6,v12_7,v12_8,v12_9,v12_10,
	v12_11,v12_12,
	v13_0=1300, v13_1,v13_2,v13_3,v13_4,v13_5,v13_6,v13_7,v13_8,v13_9,v13_10,
	v13_11,v13_12,
	v14_0=1400, v14_1,v14_2,v14_3,v14_4,v14_5,v14_6,v14_7,v14_8,v14_9,v14_10,
	v14_11,v14_12,
	v15_0=1500, v15_1,v15_2,v15_3,v15_4,v15_5,v15_6,v15_7,v15_8,v15_9,v15_10,
	v15_11,v15_12,
	v16_0=1600, v16_1,v16_2,v16_3,v16_4,v16_5,v16_6,v16_7,v16_8,v16_9,v16_10,
	v16_11,v16_12,
	v17_0=1700, v17_1,v17_2,v17_3,v17_4,v17_5,v17_6,v17_7,v17_8,v17_9,v17_10,
	v17_11,v17_12,
	v18_0=1800, v18_1,v18_2,v18_3,v18_4,v18_5,v18_6,v18_7,v18_8,v18_9,v18_10,
	v18_11,v18_12,
	maxver // a test if we're sane or not
};
enum atomtree_common_version get_ver(struct atom_common_table_header* header);
void set_ver(enum atomtree_common_version ver, struct atom_common_table_header* header);


void atomtree_bios_checksum(struct atom_tree* atree);
struct atom_tree* atombios_parse(
		void* bios, uint32_t alloc_size, bool generate_atui
);

//#include "atui.h"

// make sure we're not on byte packing
struct _twentyfourbytes {uint64_t a; uint8_t b; uint64_t c;};
static_assert(sizeof(struct _twentyfourbytes) > 17);

#endif
