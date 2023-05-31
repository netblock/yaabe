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
	uint64_t maxval = (1ULL << (leaf->type)) - 1; //needs the ULL for 64-bit
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
	switch(leaf->type) {
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

PPATUI_FUNCIFY(atom_root,
	antiem, otheritem)
PPATUI_FUNCIFY(atom_test1,
	smolthing, twobytes, twobytes1, twobytes2)
PPATUI_FUNCIFY(atom_test1_child1,
	twobytes5, twobytes6, twobytes7, twobytes8, twobytes9, twobytes10)
PPATUI_FUNCIFY(atom_test1_child2,
	antiem, otheritem, smolthing, twobytes, twobytes1, twobytes2, twobytes3,
	twobytes4, twobytes5, twobytes6, twobytes7, twobytes8, twobytes9,
	twobytes10)
PPATUI_FUNCIFY(atom_test2)
PPATUI_FUNCIFY(atom_test3,
	twobytes6, twobytes7, twobytes8, twobytes9, twobytes10)
PPATUI_FUNCIFY(atom_test3_child1,
	twobytes7, twobytes8, twobytes9, twobytes10)
PPATUI_FUNCIFY(atom_test3_child2,
	twobytes8, twobytes9, twobytes10)
PPATUI_FUNCIFY(atom_test3_child3,
	twobytes9, twobytes10)
*/



PPATUI_FUNCIFY(atom_common_table_header,
	structuresize, ATUI_DEC,
	format_revision, ATUI_DEC,
	content_revision, ATUI_DEC
)


// TODO atom_bios_string
PPATUI_FUNCIFY(atom_rom_header_v2_2,
	bios_segment_address, ATUI_DEC,
	protectedmodeoffset, ATUI_DEC,
	configfilenameoffset, ATUI_DEC,
	crc_block_offset, ATUI_DEC,
	vbios_bootupmessageoffset, ATUI_DEC,
	int10_offset, ATUI_DEC,
	pcibusdevinitcode, ATUI_DEC,
	iobaseaddress, ATUI_DEC,
	subsystem_vendor_id, ATUI_DEC,
	subsystem_id, ATUI_DEC,
	pci_info_offset, ATUI_DEC,
	masterhwfunction_offset, ATUI_DEC,
	masterdatatable_offset, ATUI_DEC,
	reserved, ATUI_DEC,
	pspdirtableoffset, ATUI_DEC
)


PPATUI_FUNCIFY(atom_master_data_table_v2_1,
	utilitypipeline, ATUI_DEC,
	multimedia_info, ATUI_DEC,
	smc_dpm_info, ATUI_DEC,
	sw_datatable3, ATUI_DEC,
	firmwareinfo, ATUI_DEC,
	sw_datatable5, ATUI_DEC,
	lcd_info, ATUI_DEC,
	sw_datatable7, ATUI_DEC,
	smu_info, ATUI_DEC,
	sw_datatable9, ATUI_DEC,
	sw_datatable10, ATUI_DEC,
	vram_usagebyfirmware, ATUI_DEC,
	gpio_pin_lut, ATUI_DEC,
	sw_datatable13, ATUI_DEC,
	gfx_info, ATUI_DEC,
	powerplayinfo, ATUI_DEC,
	sw_datatable16, ATUI_DEC,
	sw_datatable17, ATUI_DEC,
	sw_datatable18, ATUI_DEC,
	sw_datatable19, ATUI_DEC,
	sw_datatable20, ATUI_DEC,
	sw_datatable21, ATUI_DEC,
	displayobjectinfo, ATUI_DEC,
	indirectioaccess, ATUI_DEC,
	umc_info, ATUI_DEC,
	sw_datatable25, ATUI_DEC,
	sw_datatable26, ATUI_DEC,
	dce_info, ATUI_DEC,
	vram_info, ATUI_DEC,
	sw_datatable29, ATUI_DEC,
	integratedsysteminfo, ATUI_DEC,
	asic_profiling_info, ATUI_DEC,
	voltageobject_info, ATUI_DEC,
	sw_datatable33, ATUI_DEC,
	sw_datatable34, ATUI_DEC
)

PPATUI_FUNCIFY(atom_vram_info_header_v2_4,
	mem_adjust_tbloffset, ATUI_DEC,
	mem_clk_patch_tbloffset, ATUI_DEC,
	mc_adjust_pertile_tbloffset, ATUI_DEC,
	mc_phyinit_tbloffset, ATUI_DEC,
	dram_data_remap_tbloffset, ATUI_DEC,
	reserved, ATUI_DEC,
	post_ucode_init_offset, ATUI_DEC,
	vram_rsd2, ATUI_DEC,
	vram_module_num, ATUI_DEC,
	umcip_min_ver, ATUI_DEC,
	umcip_max_ver, ATUI_DEC,
	mc_phy_tile_num, ATUI_DEC
)


//TODO reserved, ATUI_DEC, dram_pnstring
PPATUI_FUNCIFY(atom_vram_module_v10,
	memory_size, ATUI_DEC,
	channel_enable, ATUI_DEC,
	max_mem_clk, ATUI_DEC,
	mem_voltage, ATUI_DEC,
	vram_module_size, ATUI_DEC,
	ext_memory_id, ATUI_DEC,
	memory_type, ATUI_DEC,
	channel_num, ATUI_DEC,
	channel_width, ATUI_DEC,
	density, ATUI_DEC,
	tunningset_id, ATUI_DEC,
	vender_rev_id, ATUI_DEC,
	refreshrate, ATUI_DEC,
	vram_flags, ATUI_DEC,
	vram_rsd2, ATUI_DEC,
	gddr6_mr10, ATUI_DEC,
	gddr6_mr1, ATUI_DEC,
	gddr6_mr2, ATUI_DEC,
	gddr6_mr7, ATUI_DEC
)
