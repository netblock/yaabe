/*
AtomTree iterable interface for UIs.

adding tables

vim replace patterns that help copypaste structs from atombios.h:
'<,'>s:struct :PPATUI_FUNCIFY(:g
'<,'>s:.*uint[0-9]*_t[ ,^I]*:^I:g
'<,'>s:;.*:,:g
'<,'>s:,\n},:\r):g
*/

#include "atui.h"
#include <stdio.h>


void atui_leaf_set_val(atui_leaf* leaf, uint64_t val){
	if (leaf->type & ATUI_ANY) {
		uint8_t num_bits = (leaf->bitfield_hi - leaf->bitfield_lo) +1;
		uint64_t maxval = (1ULL << num_bits) - 1;
		if (val > maxval)
			val = maxval;

		// ...11111 000.. 1111...
		uint64_t tokeep_mask = ~(maxval << leaf->bitfield_lo);
		val <<= leaf->bitfield_lo;
		*(leaf->u64) = (*(leaf->u64) & tokeep_mask) | val;
	}
}


uint64_t atui_leaf_get_val(atui_leaf* leaf) {
	if (leaf->type & ATUI_ANY) {
		uint8_t num_bits = (leaf->bitfield_hi - leaf->bitfield_lo) +1;
		uint64_t premask = (1ULL << num_bits) - 1; // 0's the hi

		return (*(leaf->u64) >> leaf->bitfield_lo) & premask;
	}
}

uint64_t strtoll_2(const char* str) {
	// TODO is there a strtoll that has 0b detection?
	uint8_t base = 0; // 0 = auto
	if ((str[0] == '0') && (str[1] == 'b')) {
		base = 2;
		str += 2;
	}
	return (uint64_t)strtoll(str, NULL, base);
}




int atui_set_from_text(atui_leaf* leaf, const char* buffer) {
    int err = 0;

    if(leaf->type & ATUI_ANY) {
        atui_leaf_set_val(leaf, strtoll_2(buffer));

    } else if( (leaf->type & (ATUI_STRING|ATUI_ARRAY)) && 
            leaf->total_bits == 8) {
		uint8_t size = leaf->array_size;
		uint8_t i;
		for(i=0; i<size; i++)
		   leaf->u8[i] = buffer[i];
		//leaf->u8[i-1] = '\0';
    } else {
        err = 1;
    }
    return err;
}
int atui_get_to_text(atui_leaf* leaf, char* buffer) {
    int err = 0;

    if(leaf->type & ATUI_ANY) {
		uint64_t val = atui_leaf_get_val(leaf);
		if ((leaf->type&ATUI_ANY) == ATUI_DEC) {
			sprintf(buffer, "%u", val);
		} else if ((leaf->type&ATUI_ANY) == ATUI_HEX) {
			sprintf(buffer, "0x%X", val);
		} else if ((leaf->type&ATUI_ANY) == ATUI_BIN) {
			uint8_t numbits = (leaf->bitfield_hi - leaf->bitfield_lo) +1;
			//sprintf adds the \0 at the end.
			char format[10] = "0b%0"; //prefix
			sprintf(format+4, "%02ub", numbits); //middle, suffix.
			sprintf(buffer, format, val);
		}

    } else if( (leaf->type & (ATUI_STRING|ATUI_ARRAY)) && 
            leaf->total_bits == 8) {
        uint8_t i = leaf->array_size;
		buffer[i] = '\0'; // for strings
        while (i--)
            buffer[i] = leaf->u8[i];
    } else {
        err = 1;
    }
    return err;
}



void atui_destroy_tree(atui_branch* tree) { //a reference implementation
	tree->max_branch_count += tree->max_inline_branch_count;
	while(tree->max_branch_count--)
		atui_destroy_tree(tree->child_branches[tree->max_branch_count]);
	free(tree);
}



/*
See ppatui.h and atui.h for more detail.

example:
PPATUI_FUNCIFY(type_prefix, atom_table_tame, atomtree_table_name,
	table_element1, radix, fancy ui representation, args for fancy,
	table_element2, radix, fancy ui representation, args for fancy,
	table_element3, radix, fancy ui representation, args for fancy
)

WARNING: always have the last comma removed:
	This is bad:  arg,arg,)
	This is good: arg,arg)


If the table element should be viewed as a number, set a radix. radix is one of
ATUI_NONE, ATUI_DEC, ATUI_HEX, ATUI_BIN

If the element should be viewed in base 2, but also has bitfields for children:
	table_element, ATUI_BIN, ATUI_BITFIELD, (
		bitfield_struct_instance_name,
		name, bitness, radix,
		name, bitness, radix
	),


if the element should have a list of text-val pairs, an enum,
first populate the atui enum:
	PPATUI_ENUMER(enum_struct_name,
		ENUM_ENTRY1,
		ENUM_ENTRY2,
		ENUM_ENTRY3,
	)
and then for the atui table,
	table_element, ATUI_HEX, ATUI_ENUM, enum_struct_name,

if the element should reference a table, a atui_branch to inline,
ake sure the table is populated with an ATUI_FUNCIFY()
	table_element, ATUI_NAN, ATUI_INLINE, table_to_inline,

if the element is a string,
	table_element, ATUI_NAN, ATUI_STRING, ATUI_NONE,
or otherwise an array,
	table_element, ATUI_HEX, ATUI_ARRAY, ATUI_NONE,



ATUI_DYNARRAY:

leaf_top_name, ATUI_NODISPLAY, ATUI_DYNARRY, (
	leaf_name, radix, fancy_ui_representation, args_for_fancy,
	start_pointer, count
)

If there is an array or number of leaves that is dynamically sized, especially
if it has a dynamic allocation, ATUI_DYNARRY can pull in the boundaries from
atomtree. 
(it is originally written for atom_umc_init_reg_block.)

leaf_top_name won't get displayed if ATUI_NODISPLAY is set.

leaf_name .. args_for_fancy, is the leaf pattern to use. Can be a bitfield.
start_pointer is a pointer where to start the array within the bios, and 
count is how long the array goes on for. 
Both start_pointer and count are members of the Funcify-passed atomtree struct.

*/





PPATUI_FUNCIFY(struct, atom_common_table_header,
		atom_tree, // to satisfy atomtree->leaves.
	structuresize,    ATUI_DEC, ATUI_NONE, ATUI_NONE,
	format_revision,  ATUI_DEC, ATUI_NONE, ATUI_NONE,
	content_revision, ATUI_DEC, ATUI_NONE, ATUI_NONE
)

PPATUI_FUNCIFY(struct, atom_rom_header_v2_2,
		atom_tree, //THE atom_tree struct
	table_header,              ATUI_NAN, ATUI_INLINE, 
		atom_common_table_header,
	atom_bios_string,          ATUI_NAN, ATUI_STRING, ATUI_NONE,
	bios_segment_address,      ATUI_HEX, ATUI_NONE, ATUI_NONE,
	protectedmodeoffset,       ATUI_HEX, ATUI_NONE, ATUI_NONE,
	configfilenameoffset,      ATUI_HEX, ATUI_NONE, ATUI_NONE,
	crc_block_offset,          ATUI_HEX, ATUI_NONE, ATUI_NONE,
	vbios_bootupmessageoffset, ATUI_HEX, ATUI_NONE, ATUI_NONE,
	int10_offset,              ATUI_HEX, ATUI_NONE, ATUI_NONE,
	pcibusdevinitcode,         ATUI_HEX, ATUI_NONE, ATUI_NONE,
	iobaseaddress,             ATUI_HEX, ATUI_NONE, ATUI_NONE,
	subsystem_vendor_id,       ATUI_HEX, ATUI_NONE, ATUI_NONE,
	subsystem_id,              ATUI_HEX, ATUI_NONE, ATUI_NONE,
	pci_info_offset,           ATUI_HEX, ATUI_NONE, ATUI_NONE,
	masterhwfunction_offset,   ATUI_HEX, ATUI_NONE, ATUI_NONE,
	masterdatatable_offset,    ATUI_HEX, ATUI_NONE, ATUI_NONE,
	reserved,                  ATUI_HEX, ATUI_NONE, ATUI_NONE,
	pspdirtableoffset,         ATUI_HEX, ATUI_NONE, ATUI_NONE
)


PPATUI_FUNCIFY(struct, atom_master_data_table_v2_1,
		atomtree_master_datatable_v2_1,
	table_header,         ATUI_NAN, ATUI_INLINE, 
		atom_common_table_header,
	utilitypipeline,      ATUI_HEX, ATUI_NONE, ATUI_NONE,
	multimedia_info,      ATUI_HEX, ATUI_NONE, ATUI_NONE,
	smc_dpm_info,         ATUI_HEX, ATUI_NONE, ATUI_NONE,
	sw_datatable3,        ATUI_HEX, ATUI_NONE, ATUI_NONE,
	firmwareinfo,         ATUI_HEX, ATUI_NONE, ATUI_NONE,
	sw_datatable5,        ATUI_HEX, ATUI_NONE, ATUI_NONE,
	lcd_info,             ATUI_HEX, ATUI_NONE, ATUI_NONE,
	sw_datatable7,        ATUI_HEX, ATUI_NONE, ATUI_NONE,
	smu_info,             ATUI_HEX, ATUI_NONE, ATUI_NONE,
	sw_datatable9,        ATUI_HEX, ATUI_NONE, ATUI_NONE,
	sw_datatable10,       ATUI_HEX, ATUI_NONE, ATUI_NONE,
	vram_usagebyfirmware, ATUI_HEX, ATUI_NONE, ATUI_NONE,
	gpio_pin_lut,         ATUI_HEX, ATUI_NONE, ATUI_NONE,
	sw_datatable13,       ATUI_HEX, ATUI_NONE, ATUI_NONE,
	gfx_info,             ATUI_HEX, ATUI_NONE, ATUI_NONE,
	powerplayinfo,        ATUI_HEX, ATUI_NONE, ATUI_NONE,
	sw_datatable16,       ATUI_HEX, ATUI_NONE, ATUI_NONE,
	sw_datatable17,       ATUI_HEX, ATUI_NONE, ATUI_NONE,
	sw_datatable18,       ATUI_HEX, ATUI_NONE, ATUI_NONE,
	sw_datatable19,       ATUI_HEX, ATUI_NONE, ATUI_NONE,
	sw_datatable20,       ATUI_HEX, ATUI_NONE, ATUI_NONE,
	sw_datatable21,       ATUI_HEX, ATUI_NONE, ATUI_NONE,
	displayobjectinfo,    ATUI_HEX, ATUI_NONE, ATUI_NONE,
	indirectioaccess,     ATUI_HEX, ATUI_NONE, ATUI_NONE,
	umc_info,             ATUI_HEX, ATUI_NONE, ATUI_NONE,
	sw_datatable25,       ATUI_HEX, ATUI_NONE, ATUI_NONE,
	sw_datatable26,       ATUI_HEX, ATUI_NONE, ATUI_NONE,
	dce_info,             ATUI_HEX, ATUI_NONE, ATUI_NONE,
	vram_info,            ATUI_HEX, ATUI_NONE, ATUI_NONE,
	sw_datatable29,       ATUI_HEX, ATUI_NONE, ATUI_NONE,
	integratedsysteminfo, ATUI_HEX, ATUI_NONE, ATUI_NONE,
	asic_profiling_info,  ATUI_HEX, ATUI_NONE, ATUI_NONE,
	voltageobject_info,   ATUI_HEX, ATUI_NONE, ATUI_NONE,
	sw_datatable33,       ATUI_HEX, ATUI_NONE, ATUI_NONE,
	sw_datatable34,       ATUI_HEX, ATUI_NONE, ATUI_NONE
)

PPATUI_FUNCIFY(struct, atom_vram_info_header_v2_4, 
		atomtree_vram_info_header_v2_4,
	table_header,                ATUI_NAN, ATUI_INLINE, 
		atom_common_table_header,
	mem_adjust_tbloffset,        ATUI_DEC, ATUI_NONE, ATUI_NONE,
	mem_clk_patch_tbloffset,     ATUI_DEC, ATUI_NONE, ATUI_NONE,
	mc_adjust_pertile_tbloffset, ATUI_DEC, ATUI_NONE, ATUI_NONE,
	mc_phyinit_tbloffset,        ATUI_DEC, ATUI_NONE, ATUI_NONE,
	dram_data_remap_tbloffset,   ATUI_DEC, ATUI_NONE, ATUI_NONE,
	reserved,                    ATUI_DEC, ATUI_NONE, ATUI_NONE,
	post_ucode_init_offset,      ATUI_DEC, ATUI_NONE, ATUI_NONE,
	vram_rsd2,                   ATUI_DEC, ATUI_NONE, ATUI_NONE,
	vram_module_num,             ATUI_DEC, ATUI_NONE, ATUI_NONE,
	umcip_min_ver,               ATUI_DEC, ATUI_NONE, ATUI_NONE,
	umcip_max_ver,               ATUI_DEC, ATUI_NONE, ATUI_NONE,
	mc_phy_tile_num,             ATUI_DEC, ATUI_NONE, ATUI_NONE
)



PPATUI_ENUMER(atom_dgpu_vram_type,
  ATOM_DGPU_VRAM_TYPE_GDDR5,                                             
  ATOM_DGPU_VRAM_TYPE_HBM2,
  ATOM_DGPU_VRAM_TYPE_HBM2E,
  ATOM_DGPU_VRAM_TYPE_GDDR6
)
PPATUI_FUNCIFY(struct, atom_vram_module_v10,
		atomtree_vram_info_header_v2_4,
	memory_size,      ATUI_DEC, ATUI_NONE, ATUI_NONE,
	channel_enable,   ATUI_DEC, ATUI_NONE, ATUI_NONE,
	max_mem_clk,      ATUI_DEC, ATUI_NONE, ATUI_NONE,
	reserved,         ATUI_HEX, ATUI_ARRAY, ATUI_NONE,
	mem_voltage,      ATUI_DEC, ATUI_NONE, ATUI_NONE,
	vram_module_size, ATUI_DEC, ATUI_NONE, ATUI_NONE,
	ext_memory_id,    ATUI_DEC, ATUI_NONE, ATUI_NONE,
	memory_type,      ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type,
	channel_num,      ATUI_DEC, ATUI_NONE, ATUI_NONE,
	channel_width,    ATUI_DEC, ATUI_NONE, ATUI_NONE,
	density,          ATUI_DEC, ATUI_NONE, ATUI_NONE,
	tunningset_id,    ATUI_DEC, ATUI_NONE, ATUI_NONE,
	vender_rev_id,    ATUI_DEC, ATUI_NONE, ATUI_NONE,
	refreshrate,      ATUI_DEC, ATUI_NONE, ATUI_NONE,
	vram_flags,       ATUI_DEC, ATUI_NONE, ATUI_NONE,
	vram_rsd2,        ATUI_DEC, ATUI_NONE, ATUI_NONE,
	gddr6_mr10,       ATUI_BIN, ATUI_NONE, ATUI_NONE,
	gddr6_mr1,        ATUI_BIN, ATUI_BITFIELD, (
		drive_stren,   1, 0, ATUI_DEC,
		data_term,     3, 2, ATUI_DEC, 
		PLLDLL_range,  5, 4, ATUI_DEC, 
		calib_update,  6, 6, ATUI_DEC, 
		PLLDLL,        7, 7, ATUI_DEC, 
		RDBI,          8, 8, ATUI_DEC, 
		WDBI,          9, 9, ATUI_DEC, 
		CABI,         10,10, ATUI_DEC, 
		PLLDLL_reset, 14,11, ATUI_DEC, 
		ID,           15,12, ATUI_DEC 
	),
	gddr6_mr2,        ATUI_BIN, ATUI_NONE, ATUI_NONE,
	gddr6_mr7,        ATUI_BIN, ATUI_NONE, ATUI_NONE,
	dram_pnstring,    ATUI_NAN, ATUI_ARRAY, ATUI_NONE // not text
)


PPATUI_FUNCIFY(union, atom_umc_reg_setting_id_config_access, 
		atomtree_umc_init_reg_block,
	u32umc_id_access,  ATUI_BIN, ATUI_BITFIELD, (
		memclockrange, 23, 0, ATUI_DEC,
		mem_blk_id,    31,24, ATUI_DEC
	)
)

PPATUI_FUNCIFY(union, atom_umc_register_addr_info_access, 
		atomtree_umc_init_reg_block,
	umc_reg_list, ATUI_NODISPLAY, ATUI_DYNARRAY, (
		u32umc_reg_addr,       ATUI_BIN, ATUI_BITFIELD, (
			umc_register_addr, 23, 0, ATUI_HEX,
			umc_reg_type_ind,  24,24, ATUI_DEC,
			umc_reg_rsvd,      31,25, ATUI_BIN
		),
		umc_reg_list, umc_number_of_registers // start, count
	)
)

PPATUI_FUNCIFY(struct, atom_umc_init_reg_block, 
		atomtree_umc_init_reg_block,
	umc_reg_num,  ATUI_DEC, ATUI_NONE, ATUI_NONE,
	reserved,     ATUI_HEX, ATUI_NONE, ATUI_NONE
)
