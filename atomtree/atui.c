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

void atui_leaf_set_val(atui_leaf* leaf, uint64_t val) {
	//needs the ULL for 64-bit
	uint64_t maxval = (1ULL << (leaf->total_bits)) - 1; 
	if (val > maxval)
		val = maxval;
	switch(leaf->type) { // might be needed for bitfield structs
		case 8:
			*(leaf->u8) = val;
			break;
		case 16:
			*(leaf->u16) = val;
			break;
		case 32:
			*(leaf->u32) = val;
			break;
		case 64:
			*(leaf->u64) = val;
			break;
	}
}
uint64_t atui_leaf_get_val(atui_leaf* leaf) {
//  return *(leaf->u64) & ((1<<leaf->type)-1);
	switch(leaf->total_bits) {
		case 8:
			return *(leaf->u8);
		case 16:
			return *(leaf->u16);
		case 32:
			return *(leaf->u32);
		case 64:
			return *(leaf->u64);
	}
}

uint64_t strtol_2(const char* str) {
	// TODO better compatibility with binary, hex, etc.
	char base = 0;
	if ((str[0] == '0') && (str[1] == 'b'))
		base = 2;
	return (uint64_t)strtol(str+base, NULL, base);
}


void atui_destroy_tree(atui_branch* tree) { //a reference implementation
	while(tree->branch_count--)
		atui_destroy_tree(tree->child_branches[tree->branch_count]);
	free(tree);
}



/* example:
PPATUI_FUNCIFY(atom_able_tame,
	table_element1, radix, fancy ui representation, args for fancy,
	table_element2, radix, fancy ui representation, args for fancy,
	table_element3, radix, fancy ui representation, args for fancy
)
WARNING: always have the last comma removed. This is bad: ,)

If the element should be viewed as a number, set a radix. radix is one of
ATUI_NONE, ATUI_DEC, ATUI_HEX, ATUI_BIN.

If the element should be viewed in base 2, but also has bitfields for children, state:
table_element, ATUI_BIN, ATUI_BITFIELD, (
	bitfield_struct_instance_name,
	name, bitness, radix,
	name, bitness, radix
),
*/





PPATUI_FUNCIFY(atom_common_table_header,
	structuresize,    ATUI_DEC, ATUI_NONE, ATUI_NONE,
	format_revision,  ATUI_DEC, ATUI_NONE, ATUI_NONE,
	content_revision, ATUI_DEC, ATUI_NONE, ATUI_NONE
)

// TODO atom_bios_string
PPATUI_FUNCIFY(atom_rom_header_v2_2,
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


PPATUI_FUNCIFY(atom_master_data_table_v2_1,
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

PPATUI_FUNCIFY(atom_vram_info_header_v2_4,
	table_header,                ATUI_NONE, ATUI_INLINE, (table_header,
		structuresize,    ATUI_DEC, ATUI_NONE, ATUI_NONE,
		format_revision,  ATUI_DEC, ATUI_NONE, ATUI_NONE,
		content_revision, ATUI_DEC, ATUI_NONE, ATUI_NONE
	),
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


PPATUI_FUNCIFY(atom_vram_module_v10,
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
		drive_stren,   1,0,  ATUI_DEC,
		data_term,     3,2,  ATUI_DEC, 
		PLLDLL_range,  5,4,  ATUI_DEC, 
		calib_update,  6,6,  ATUI_DEC, 
		PLLDLL,        7,7,  ATUI_DEC, 
		RDBI,          8,8,  ATUI_DEC, 
		WDBI,          9,9,  ATUI_DEC, 
		CABI,         10,10, ATUI_DEC, 
		PLLDLL_reset, 14,11, ATUI_DEC, 
		ID,           15,12, ATUI_DEC 
	),
	gddr6_mr2,        ATUI_BIN, ATUI_NONE, ATUI_NONE,
	gddr6_mr7,        ATUI_BIN, ATUI_NONE, ATUI_NONE,
	dram_pnstring,    ATUI_NONE, ATUI_STRING, ATUI_NONE
)
