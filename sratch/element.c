#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct atom_vram_module_v10_biosmask {
  // Design Specific Values
  uint32_t  memory_size;                   // Total memory size in unit of MB for CONFIG_MEMSIZE zeros
  uint32_t  channel_enable;                // bit vector, each bit indicate specific channel enable or not
  uint32_t  max_mem_clk;                   // max memory clock of this memory in unit of 10kHz, =0 means it is not defined
  uint16_t  reserved[3];
  uint16_t  mem_voltage;                   // mem_voltage
  uint16_t  vram_module_size;              // Size of atom_vram_module_v9
  uint8_t   ext_memory_id;                 // Current memory module ID
  uint8_t   memory_type;                   // enum of atom_dgpu_vram_type
  uint8_t   channel_num;                   // Number of mem. channels supported in this module
  uint8_t   channel_width;                 // CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT
  uint8_t   density;                       // _8Mx32, _16Mx32, _16Mx16, _32Mx16
  uint8_t   tunningset_id;                 // MC phy registers set per
  uint8_t   vender_rev_id;                 // [7:4] Revision, [3:0] Vendor code
  uint8_t   refreshrate;                   // [1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)
  uint8_t   vram_flags;			   // bit0= bankgroup enable
  uint8_t   vram_rsd2;			   // reserved
  uint16_t  gddr6_mr10;                    // gddr6 mode register10 value
  uint16_t  gddr6_mr1;                     // gddr6 mode register1 value
  uint16_t  gddr6_mr2;                     // gddr6 mode register2 value
  uint16_t  gddr6_mr7;                     // gddr6 mode register7 value
  char    dram_pnstring[20];               // part number end with '0'
};

struct atom_vram_module_v10_pointerset {
  // Design Specific Values
  uint32_t*  memory_size;                   // Total memory size in unit of MB for CONFIG_MEMSIZE zeros
  uint32_t*  channel_enable;                // bit vector, each bit indicate specific channel enable or not
  uint32_t*  max_mem_clk;                   // max memory clock of this memory in unit of 10kHz, =0 means it is not defined
  uint16_t*  reserved[3];
  uint16_t*  mem_voltage;                   // mem_voltage
  uint16_t*  vram_module_size;              // Size of atom_vram_module_v9
  uint8_t*   ext_memory_id;                 // Current memory module ID
  uint8_t*   memory_t*ype;                   // enum of atom_dgpu_vram_t*ype
  uint8_t*   channel_num;                   // Number of mem. channels supported in this module
  uint8_t*   channel_width;                 // CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT
  uint8_t*   density;                       // _8Mx32, _16Mx32, _16Mx16, _32Mx16
  uint8_t*   tunningset_id;                 // MC phy registers set per
  uint8_t*   vender_rev_id;                 // [7:4] Revision, [3:0] Vendor code
  uint8_t*   refreshrate;                   // [1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)
  uint8_t*   vram_flags;			   // bit0= bankgroup enable
  uint8_t*   vram_rsd2;			   // reserved
  uint16_t*  gddr6_mr10;                    // gddr6 mode register10 value
  uint16_t*  gddr6_mr1;                     // gddr6 mode register1 value
  uint16_t*  gddr6_mr2;                     // gddr6 mode register2 value
  uint16_t*  gddr6_mr7;                     // gddr6 mode register7 value
  char    dram_pnstring[20];               // part number end with '0'
};

//void populate_branch(void* cpu_pointer_tree, void* bios_table_of_pointers, void* relative_zero, int count);

int main(){
	struct bee b;
	b[0];
}

/*
I want to do something like this to access the data:
atmctx->data_table->vram_info->vram_module->gddr6_mr8
Where the final element is a cpu pointer to the correct position in the
original atombios file.

Sounds simple, right? For atombios pointers, you instead replace its slot in
the structure 
The unfortunate concequence of this want is that we to create a 

cpu_atomtables
malloc like 2MiB (or w/e) and then walk the pointer with a bunch of sizeof()?

void* empty = malloc(2MIB);


//uint16_t* with a population loop?
//I basically want:
//atmctx->data_table->vram_info->vram_module->gddr6_mr8
//and
//atmctx->data_table->vram_info->gddr6_ac_timing_offset->tREFI
//I have to redo all the tables/structs to have pointers to their child structs
// how2map tree without manually mapping each branch?
//
//don't do pointers to their child structs; malloc it all?

*/
