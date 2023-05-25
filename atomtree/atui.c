/*
AtomTree iterable interface for UIs.
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

ATUI_FUNCIFY(atom_root,
	antiem, otheritem)
ATUI_FUNCIFY(atom_test1,
	smolthing, twobytes, twobytes1, twobytes2)
ATUI_FUNCIFY(atom_test1_child1,
	twobytes5, twobytes6, twobytes7, twobytes8, twobytes9, twobytes10)
ATUI_FUNCIFY(atom_test1_child2,
	antiem, otheritem, smolthing, twobytes, twobytes1, twobytes2, twobytes3,
	twobytes4, twobytes5, twobytes6, twobytes7, twobytes8, twobytes9,
	twobytes10)
ATUI_FUNCIFY(atom_test2)
ATUI_FUNCIFY(atom_test3,
	twobytes6, twobytes7, twobytes8, twobytes9, twobytes10)
ATUI_FUNCIFY(atom_test3_child1,
	twobytes7, twobytes8, twobytes9, twobytes10)
ATUI_FUNCIFY(atom_test3_child2,
	twobytes8, twobytes9, twobytes10)
ATUI_FUNCIFY(atom_test3_child3,
	twobytes9, twobytes10)
*/



ATUI_FUNCIFY(atom_common_table_header,
	structuresize,
	format_revision,
	content_revision
)



// TODO atom_bios_string
ATUI_FUNCIFY(atom_rom_header_v2_2,
	bios_segment_address,
	protectedmodeoffset,
	configfilenameoffset,
	crc_block_offset,
	vbios_bootupmessageoffset,
	int10_offset,
	pcibusdevinitcode,
	iobaseaddress,
	subsystem_vendor_id,
	subsystem_id,
	pci_info_offset,
	masterhwfunction_offset,
	masterdatatable_offset,
	reserved,
	pspdirtableoffset
)


ATUI_FUNCIFY(atom_master_data_table_v2_1,
	utilitypipeline,
	multimedia_info,
	smc_dpm_info,
	sw_datatable3,
	firmwareinfo,
	sw_datatable5,
	lcd_info,
	sw_datatable7,
	smu_info,
	sw_datatable9,
	sw_datatable10,
	vram_usagebyfirmware,
	gpio_pin_lut,
	sw_datatable13,
	gfx_info,
	powerplayinfo,
	sw_datatable16,
	sw_datatable17,
	sw_datatable18,
	sw_datatable19,
	sw_datatable20,
	sw_datatable21,
	displayobjectinfo,
	indirectioaccess,
	umc_info,
	sw_datatable25,
	sw_datatable26,
	dce_info,
	vram_info,
	sw_datatable29,
	integratedsysteminfo,
	asic_profiling_info,
	voltageobject_info,
	sw_datatable33,
	sw_datatable34
)

ATUI_FUNCIFY(atom_vram_info_header_v2_4,
	mem_adjust_tbloffset,
	mem_clk_patch_tbloffset,
	mc_adjust_pertile_tbloffset,
	mc_phyinit_tbloffset,
	dram_data_remap_tbloffset,
	reserved,
	post_ucode_init_offset,
	vram_rsd2,
	vram_module_num,
	umcip_min_ver,
	umcip_max_ver,
	mc_phy_tile_num
)

