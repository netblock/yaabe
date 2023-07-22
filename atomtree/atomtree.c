/* for abstract commentary, read atomtree_data_tables.h */

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <atomfirmware.h>
#include <powerplay.h>

#include "atomtree_common.h"
#include "atomtree.h"
#include "atui.h"

bool atomtree_dt_populate_smc_dpm_info(struct atom_tree* atree) {
	struct atomtree_smc_dpm_info* smc_dpm_info =
		&(atree->data_table.smc_dpm_info);

	smc_dpm_info->dot = smc_dpm_info;
	smc_dpm_info->dotdot = &(atree->data_table);

	// leaves is in a union with the structs.
	smc_dpm_info->leaves = atree->bios + atree->data_table.leaves->smc_dpm_info;

	smc_dpm_info->ver = get_ver(smc_dpm_info->table_header);
}



bool atomtree_dt_populate_firmwareinfo(struct atom_tree* atree) {
	struct atomtree_firmware_info* firmwareinfo =
		&(atree->data_table.firmwareinfo);

	firmwareinfo->dot = firmwareinfo;
	firmwareinfo->dotdot = &(atree->data_table);

	// leaves is in a union with the structs.
	firmwareinfo->leaves = atree->bios + atree->data_table.leaves->firmwareinfo;

	firmwareinfo->ver = (firmwareinfo->table_header->format_revision * 100) + 
		firmwareinfo->table_header->content_revision;
}



bool atomtree_dt_populate_smu_info(struct atom_tree* atree) {
	struct atomtree_smu_info* smu_info = &(atree->data_table.smu_info);

	smu_info->dot = smu_info;
	smu_info->dotdot = &(atree->data_table);

	// leaves is in a union with the structs.
	smu_info->leaves = atree->bios + atree->data_table.leaves->smu_info;

	smu_info->ver = get_ver(smu_info->table_header);
	switch (smu_info->ver) {
		case v3_3:
			smu_info->smugolden = smu_info->leaves + 
				smu_info->v3_3->smugoldenoffset;
			smu_info->smuinit = smu_info->leaves +
				smu_info->v3_3->smuinitoffset;
			break;
		case v3_5:
			smu_info->smugolden = smu_info->leaves + 
				smu_info->v3_5->smugoldenoffset;
			smu_info->smuinit = smu_info->leaves +
				smu_info->v3_5->smuinitoffset;
			break;
		case v3_6:
			smu_info->smugolden = smu_info->leaves + 
				smu_info->v3_6->smugoldenoffset;
			smu_info->smuinit = smu_info->leaves +
				smu_info->v3_6->smuinitoffset;
			break;
		case v4_0:
			smu_info->smuinit = smu_info->leaves +
				smu_info->v4_0->smuinitoffset;
			break;
	}
}



bool atomtree_dt_populate_vram_usagebyfirmware(struct atom_tree* atree) {
	struct atomtree_vram_usagebyfirmware* fw_vram  = 
		&(atree->data_table.vram_usagebyfirmware);

	fw_vram->dot = fw_vram;
	fw_vram->dotdot = &(atree->data_table);

	// leaves is in a union with the structs.
	fw_vram->leaves = atree->bios +
		atree->data_table.leaves->vram_usagebyfirmware;

	fw_vram->ver = get_ver(fw_vram->table_header);
}



bool atomtree_dt_populate_gfx_info(struct atom_tree* atree) {
	struct atomtree_gfx_info* gfx_info = &(atree->data_table.gfx_info);

	gfx_info->dot = gfx_info;
	gfx_info->dotdot = &(atree->data_table);

	// leaves is in a union with the structs.
	gfx_info->leaves = atree->bios + atree->data_table.leaves->gfx_info;

	gfx_info->ver = get_ver(gfx_info->table_header);
	switch(gfx_info->ver) {
		case v2_3:
			gfx_info->gcgolden = gfx_info->leaves + 
				gfx_info->v2_3->gcgoldenoffset;
			break;
		case v2_4:
			gfx_info->gcgolden = gfx_info->leaves + 
				gfx_info->v2_4->gcgoldenoffset;
			break;
		case v2_7:
			gfx_info->gcgolden = gfx_info->leaves + 
				gfx_info->v2_7->gcgoldenoffset;
			break;
	}
}


bool atomtree_dt_populate_ppt(struct atom_tree* atree) {
	struct atomtree_powerplaytable* ppt = &(atree->data_table.powerplayinfo);

	ppt->dot = ppt;
	ppt->dotdot = &(atree->data_table);

	// leaves is in a union with the structs.
	ppt->leaves = atree->bios + atree->data_table.leaves->powerplayinfo;
    ppt->ver = get_ver(ppt->table_header);

	if  (ppt->ver > maxver) { // Navi3 compatibility. TODO: wrong.
		ppt->leaves = atree->data_table.leaves +
			atree->data_table.leaves->powerplayinfo;
		ppt->ver = get_ver(ppt->table_header);
	}

	
}


static atui_branch* atomtree_populate_umc_init_reg_block(
		struct atom_tree* atree,
		struct atomtree_umc_init_reg_block* at_regblock) {
	// TODO: something something end is 0xFFFF ???

	// regblock->leaves must be already populated.
	at_regblock->dot = at_regblock;
	at_regblock->dotdot = &(atree->data_table.vram_info);

	// AMD, what the fuck? fuckin please be consistent. Use your common table
	// structure, and use your pointers. And why aren't your pointers starting
	// off from 0? So clunky. iT cOsTs TwO eXtRa ByTeS your bioses are like half
	// empty. Is this clunk from the ATI days? Even so, change the API; there is
	// room for grace.
	// hell, I'd make the pointers 64-bit so you could just plop down a struct
	// tree onto the void* bios, assume -fPIC and be done with it. 

	// Take a look at struct atom_umc_init_reg_block of atomfirmware.h.
	// This struct has 3 notable lists: 
	// umc_reg_list, umc_reg_setting_list, and 
	// atom_umc_reg_setting_data_block's u32umc_reg_data.
	// These lists are all dynamically sized. 
	//
	// umc_reg_list follows umc_reg_num.
	// umc_reg_setting_list starts immediately after umc_reg_list.
	// umc_reg_setting_list does not follow umc_reg_num. but ends with 0-fill.
	// and atom_umc_reg_setting_data_block's u32umc_reg_data follows 
	// umc_reg_num.

	at_regblock->umc_reg_list = at_regblock->leaves->umc_reg_list;
	at_regblock->umc_number_of_registers = &(at_regblock->leaves->umc_reg_num);
	uint16_t umc_reg_list_size =
		sizeof(union atom_umc_register_addr_info_access) *
		(*at_regblock->umc_number_of_registers);

	// regsettingblock_starting_point is umc_reg_setting_list[0]
	void* regsettingblock_starting_point = (void*)at_regblock->leaves +
		sizeof(struct atom_umc_init_reg_block_header) + umc_reg_list_size; 

	// the -1 is from the data_block struct already having the first element,
	// the "u32umc_reg_data[1]".
	uint16_t regsettingblock_size =
		sizeof(struct atom_umc_reg_setting_data_block) +
		sizeof(uint32_t) * (*at_regblock->umc_number_of_registers-1);

	struct atom_umc_reg_setting_data_block* loc;
	uint8_t i;
	for (i=0; i < *at_regblock->umc_number_of_registers ; i++) {
		loc = regsettingblock_starting_point + regsettingblock_size*i;
		if (loc->block_id.u32umc_id_access == 0)
			break; // AtomBIOS ends the datablock list with 0-fill.
		at_regblock->umc_reg_setting_list[i] = loc;
	}
	at_regblock->umc_reg_setting_list_size = i;
}

static inline atui_branch* atomtree_populate_vram_info_v2_3(
		struct atom_tree* atree, bool generate_atui) {
	struct atomtree_vram_info_header_v2_3* vi23 =
		&(atree->data_table.vram_info.v2_3);

	vi23->dot = vi23;
	vi23->dotdot = &(atree->data_table.vram_info);
	vi23->leaves = atree->bios +
		atree->data_table.leaves->vram_info;


	vi23->mem_adjust_table.leaves = (void*)vi23->leaves +
		vi23->leaves->mem_adjust_tbloffset;
	atomtree_populate_umc_init_reg_block(atree, &(vi23->mem_adjust_table));

	vi23->mem_clk_patch.leaves = (void*)vi23->leaves +
		vi23->leaves->mem_clk_patch_tbloffset;
	atomtree_populate_umc_init_reg_block(atree, &(vi23->mem_clk_patch));

	//TODO does vraminfo->mc_phy_tile_num significantly affect this?
	vi23->mc_adjust_pertile.leaves = (void*)vi23->leaves +
		vi23->leaves->mc_adjust_pertile_tbloffset;
	atomtree_populate_umc_init_reg_block(atree, &(vi23->mc_adjust_pertile));

	vi23->mc_phyinit.leaves = (void*)vi23->leaves +
		vi23->leaves->mc_phyinit_tbloffset;
	atomtree_populate_umc_init_reg_block(atree, &(vi23->mc_phyinit));

	//TODO does vraminfo->mc_phy_tile_num significantly affect this?
	vi23->dram_data_remap = (void*)vi23->leaves +
		vi23->leaves->dram_data_remap_tbloffset;

	// TODO what is this?
	vi23->hbm_tmrs = (void*)vi23->leaves + vi23->leaves->tmrs_seq_offset;

	vi23->post_ucode_init.leaves = (void*)vi23->leaves +
		vi23->leaves->post_ucode_init_offset;
	atomtree_populate_umc_init_reg_block(atree, &(vi23->post_ucode_init));

}

static inline atui_branch* atomtree_populate_vram_info_v2_4(
		struct atom_tree* atree, bool generate_atui) {
	struct atomtree_vram_info_header_v2_4* vi24 =
		&(atree->data_table.vram_info.v2_4);

	vi24->dot = vi24;
	vi24->dotdot = &(atree->data_table.vram_info);
	vi24->leaves = atree->bios +
		atree->data_table.leaves->vram_info;
	struct atom_vram_info_header_v2_4* leaves = vi24->leaves;


	vi24->mem_adjust_table.leaves = (void*)vi24->leaves +
		vi24->leaves->mem_adjust_tbloffset;
	atomtree_populate_umc_init_reg_block(atree, &(vi24->mem_adjust_table));

	vi24->mem_clk_patch.leaves = (void*)vi24->leaves +
		vi24->leaves->mem_clk_patch_tbloffset;
	atomtree_populate_umc_init_reg_block(atree, &(vi24->mem_clk_patch));
	vi24->navi1_gddr6_timings = (struct umc_block_navi1_timings*)\
		vi24->mem_clk_patch.umc_reg_setting_list[0]; 
	vi24->num_timing_straps = &(vi24->mem_clk_patch.umc_reg_setting_list_size);

	//TODO does vraminfo->mc_phy_tile_num significantly affect this?
	vi24->mc_adjust_pertile.leaves = (void*)vi24->leaves +
		vi24->leaves->mc_adjust_pertile_tbloffset;
	atomtree_populate_umc_init_reg_block(atree, &(vi24->mc_adjust_pertile));

	vi24->mc_phyinit.leaves = (void*)vi24->leaves +
		vi24->leaves->mc_phyinit_tbloffset;
	atomtree_populate_umc_init_reg_block(atree, &(vi24->mc_phyinit));

	//TODO does vraminfo->mc_phy_tile_num significantly affect this?
	vi24->dram_data_remap = (void*)vi24->leaves +
		vi24->leaves->dram_data_remap_tbloffset;

	vi24->post_ucode_init.leaves = (void*)vi24->leaves +
		vi24->leaves->post_ucode_init_offset;
	atomtree_populate_umc_init_reg_block(atree, &(vi24->post_ucode_init));


	atui_branch* atui_vi = NULL;
	if(generate_atui) {
		atui_branch* atui_header = ATUI_MAKE_BRANCH(atom_common_table_header,
			NULL, &(leaves->table_header),  0,NULL);


		atui_branch* memclkpatch_children[] = {
			ATUI_MAKE_BRANCH(atom_umc_register_addr_info_access,
				&(vi24->mem_clk_patch), NULL, 0,NULL
			),
/*
			ATUI_MAKE_BRANCH(atom_umc_register_addr_info_access,
				NULL, vi24->mem_clk_patch.umc_reg_list, 0,NULL
			),
*/
			ATUI_MAKE_BRANCH(atom_umc_reg_setting_data_block,
				&(vi24->mem_clk_patch),
				vi24->mem_clk_patch.umc_reg_setting_list[0],
				0,NULL
			),
			ATUI_MAKE_BRANCH(umc_block_navi1_timings,
				NULL, vi24->mem_clk_patch.umc_reg_setting_list[19],
				0,NULL
			),

		};
		const int memclkpatch_child_count = \
			sizeof(memclkpatch_children)/sizeof(atui_branch*);
		atui_branch* memclkpatch = \
			ATUI_MAKE_BRANCH(atom_umc_init_reg_block,
				&(vi24->mem_clk_patch),NULL,
				memclkpatch_child_count, memclkpatch_children
			);

		atui_branch* child_branches[] = {atui_header, memclkpatch};
		const int num_child_part = sizeof(child_branches)/sizeof(atui_branch*);
		int num_child = num_child_part + vi24->leaves->vram_module_num;

		atui_vi = ATUI_MAKE_BRANCH(atom_vram_info_header_v2_4,
			vi24,NULL,  num_child,NULL);

		int cb_depth = 0;
		int i = 0;
		for(i=0; i < num_child_part; i++)
			atui_vi->child_branches[i] = child_branches[i];
		cb_depth = cb_depth + i;

		for(i=0; i < vi24->leaves->vram_module_num; i++) {
			atui_vi->child_branches[i + cb_depth] = 
				ATUI_MAKE_BRANCH(atom_vram_module_v10, 
					vi24, &(vi24->leaves->vram_module[i]), 0,NULL);
		}
		cb_depth = cb_depth + i;
	}

	return atui_vi;
}

static inline atui_branch* atomtree_populate_vram_info_v2_5(
	struct atom_tree* atree, bool generate_atui) {
	uint8_t i=0;
	struct atomtree_vram_info_header_v2_5* vi25 =
		&(atree->data_table.vram_info.v2_5);

	vi25->dot = vi25;
	vi25->dotdot = &(atree->data_table.vram_info);
	vi25->leaves = atree->bios +
		atree->data_table.leaves->vram_info;


	vi25->mem_adjust_table.leaves = (void*)vi25->leaves +
		vi25->leaves->mem_adjust_tbloffset;
	atomtree_populate_umc_init_reg_block(atree, &(vi25->mem_adjust_table));
	
	vi25->gddr6_ac_timings = (void*)vi25->leaves +
		vi25->leaves->gddr6_ac_timing_offset;
	for(i=0; vi25->gddr6_ac_timings[i].u32umc_id_access.u32umc_id_access; i++);
	vi25->gddr6_acstrap_count = i;

	//TODO does vraminfo->mc_phy_tile_num significantly affect this?
	vi25->mc_adjust_pertile.leaves = (void*)vi25->leaves +
		vi25->leaves->mc_adjust_pertile_tbloffset;
	atomtree_populate_umc_init_reg_block(atree, &(vi25->mc_adjust_pertile));

	vi25->mc_phyinit.leaves = (void*)vi25->leaves +
		vi25->leaves->mc_phyinit_tbloffset;
	atomtree_populate_umc_init_reg_block(atree, &(vi25->mc_phyinit));

	//TODO does vraminfo->mc_phy_tile_num significantly affect this?
	vi25->dram_data_remap = (void*)vi25->leaves +
		vi25->leaves->dram_data_remap_tbloffset;

	vi25->post_ucode_init.leaves = (void*)vi25->leaves +
		vi25->leaves->post_ucode_init_offset;
	atomtree_populate_umc_init_reg_block(atree, &(vi25->post_ucode_init));

	vi25->strobe_mode_patch.leaves = (void*)vi25->leaves +
		vi25->leaves->strobe_mode_patch_tbloffset;
	atomtree_populate_umc_init_reg_block(atree, &(vi25->strobe_mode_patch));
}

static inline atui_branch* atomtree_populate_vram_info_v2_6(
		struct atom_tree* atree, bool generate_atui) {
	struct atomtree_vram_info_header_v2_6* vi26 =
		&(atree->data_table.vram_info.v2_6);

	vi26->dot = vi26;
	vi26->dotdot = &(atree->data_table.vram_info);
	vi26->leaves = atree->bios +
		atree->data_table.leaves->vram_info;


	vi26->mem_adjust_table.leaves = (void*)vi26->leaves +
		vi26->leaves->mem_adjust_tbloffset;
	atomtree_populate_umc_init_reg_block(atree, &(vi26->mem_adjust_table));

	vi26->mem_clk_patch.leaves = (void*)vi26->leaves +
		vi26->leaves->mem_clk_patch_tbloffset;
	atomtree_populate_umc_init_reg_block(atree, &(vi26->mem_clk_patch));

	//TODO does vraminfo->mc_phy_tile_num significantly affect this?
	vi26->mc_adjust_pertile.leaves = (void*)vi26->leaves +
		vi26->leaves->mc_adjust_pertile_tbloffset;
	atomtree_populate_umc_init_reg_block(atree, &(vi26->mc_adjust_pertile));

	vi26->mc_phyinit.leaves = (void*)vi26->leaves +
		vi26->leaves->mc_phyinit_tbloffset;
	atomtree_populate_umc_init_reg_block(atree, &(vi26->mc_phyinit));

	//TODO does vraminfo->mc_phy_tile_num significantly affect this?
	vi26->dram_data_remap = (void*)vi26->leaves +
		vi26->leaves->dram_data_remap_tbloffset;

	vi26->tmrs_seq = (void*)vi26->leaves + vi26->leaves->tmrs_seq_offset;

	vi26->post_ucode_init.leaves = (void*)vi26->leaves +
		vi26->leaves->post_ucode_init_offset;
	atomtree_populate_umc_init_reg_block(atree, &(vi26->post_ucode_init));

}

static inline atui_branch* atomtree_populate_vram_info_v3_0(
		struct atom_tree* atree, bool generate_atui) {
	uint8_t i=0;
	struct atomtree_vram_info_header_v3_0* vi30 =
		&(atree->data_table.vram_info.v3_0);

	vi30->dot = vi30;
	vi30->dotdot = &(atree->data_table.vram_info);
	vi30->leaves = atree->bios +
		atree->data_table.leaves->vram_info;


	vi30->mem_tuning = (void*)vi30->leaves +
		vi30->leaves->mem_tuning_table_offset;
	vi30->dram_info = (void*)vi30->leaves +
		vi30->leaves->dram_info_table_offset;
	vi30->tmrs_seq = (void*)vi30->leaves + vi30->leaves->tmrs_table_offset;

	vi30->mc_init.leaves = (void*)vi30->leaves +
		vi30->leaves->umc_emuinittable_offset;
	atomtree_populate_umc_init_reg_block(atree, &(vi30->mc_init));

	vi30->dram_data_remap = (void*)vi30->leaves +
		vi30->leaves->dram_data_remap_table_offset;

	vi30->umc_emuinit.leaves = (void*)vi30->leaves +
		vi30->leaves->umc_emuinittable_offset;
	atomtree_populate_umc_init_reg_block(atree, &(vi30->umc_emuinit));

	vi30->rsvd_tables[0] = (void*)vi30->leaves +
		vi30->leaves->reserved_sub_table_offset[0];
	vi30->rsvd_tables[1] = (void*)vi30->leaves +
		vi30->leaves->reserved_sub_table_offset[1];

	i = vi30->leaves->mc_phy_tile_num;
	struct atomtree_vram_module_v3_0* atvm;
	while (i) { // TODO: is the pointer math right?
		i--;
		atvm = &(vi30->vram_module[i]);

		atvm->dot = atvm;
		atvm->dotdot = &(atree->data_table.vram_info);
		atvm->leaves = &(vi30->leaves->vram_module[i]);

		atvm->dram_info = (void*)vi30->leaves + atvm->leaves->dram_info_offset;
		atvm->mem_tuning = (void*)vi30->leaves+atvm->leaves->mem_tuning_offset;
		atvm->tmrs_seq = (void*)vi30->leaves + atvm->leaves->tmrs_seq_offset;
	}
}

static inline atui_branch* atomtree_dt_populate_vram_info(
		struct atom_tree* atree, bool generate_atui) {
	struct atomtree_vram_info* vram_info = &(atree->data_table.vram_info);

	vram_info->dot = vram_info;
	vram_info->dotdot = &(atree->data_table);
	vram_info->table_header = atree->bios +
		atree->data_table.leaves->vram_info;


	atui_branch* atui_vi = NULL;
	vram_info->ver = get_ver(vram_info->table_header);
	switch (vram_info->ver) { // TODO: earlier tables than 2.3?
		case v2_3:
			atui_vi = atomtree_populate_vram_info_v2_3(atree, generate_atui);
			break;
		case v2_4:
			atui_vi = atomtree_populate_vram_info_v2_4(atree, generate_atui);
			break;
		case v2_5:
			atui_vi = atomtree_populate_vram_info_v2_5(atree, generate_atui);
			break;
		case v2_6:
			atui_vi = atomtree_populate_vram_info_v2_6(atree, generate_atui);
			break;
		case v3_0:
			atui_vi = atomtree_populate_vram_info_v3_0(atree, generate_atui);
			break;
		default: //TODO error handling stub
			break;
	}
	return atui_vi;
}



static inline atui_branch* atomtree_populate_datatables(
		struct atom_tree* atree, bool generate_atui) {
	//TODO double check pointer math if possible; some tables might be relative
	//    to master_datatable.

	struct atomtree_master_datatable_v2_1* data_table = &(atree->data_table);
	struct atom_master_data_table_v2_1* leaves;
	void* bios = atree->bios;

	data_table->dot = data_table;
	data_table->dotdot = atree;
	data_table->leaves = bios + atree->leaves->masterdatatable_offset;
	data_table->ver = get_ver(data_table->table_header);


	leaves = data_table->leaves;

	data_table->utilitypipeline = bios + leaves->utilitypipeline;
	data_table->multimedia_info = (void*)leaves + leaves->multimedia_info;//WTF
	atomtree_dt_populate_smc_dpm_info(atree);
	atomtree_dt_populate_firmwareinfo(atree);
	data_table->lcd_info = bios + leaves->lcd_info;
	atomtree_dt_populate_smu_info(atree);
	atomtree_dt_populate_vram_usagebyfirmware(atree);
	data_table->gpio_pin_lut = bios + leaves->gpio_pin_lut;
	atomtree_dt_populate_gfx_info(atree);
	atomtree_dt_populate_ppt(atree);
	//displayobjectinfo
	//indirectioaccess
	//umc_info
	//dce_info
	atui_branch* atui_vram_info = 
		atomtree_dt_populate_vram_info(atree, generate_atui);
	//integratedsysteminfo
	//asic_profiling_info
	//voltageobject_info

	data_table->sw_datatable3.leaves = bios + leaves->sw_datatable3;
	data_table->sw_datatable5.leaves = bios + leaves->sw_datatable5;
	data_table->sw_datatable7.leaves = bios + leaves->sw_datatable7;
	data_table->sw_datatable9.leaves = bios + leaves->sw_datatable9;
	data_table->sw_datatable10.leaves = bios + leaves->sw_datatable10;
	data_table->sw_datatable13.leaves = bios + leaves->sw_datatable13;
	data_table->sw_datatable16.leaves = bios + leaves->sw_datatable16;
	data_table->sw_datatable17.leaves = bios + leaves->sw_datatable17;
	data_table->sw_datatable18.leaves = bios + leaves->sw_datatable18;
	data_table->sw_datatable19.leaves = bios + leaves->sw_datatable19;
	data_table->sw_datatable20.leaves = bios + leaves->sw_datatable20;
	data_table->sw_datatable21.leaves = bios + leaves->sw_datatable21;
	data_table->sw_datatable25.leaves = bios + leaves->sw_datatable25;
	data_table->sw_datatable26.leaves = bios + leaves->sw_datatable26;
	data_table->sw_datatable29.leaves = bios + leaves->sw_datatable29;
	data_table->sw_datatable33.leaves = bios + leaves->sw_datatable33;
	data_table->sw_datatable34.leaves = bios + leaves->sw_datatable34;

	atui_branch* atui_dt = NULL;

	if (generate_atui) {
		atui_branch* atui_header = ATUI_MAKE_BRANCH(atom_common_table_header,
			NULL,&(leaves->table_header),  0,NULL);

		atui_branch* child_branches[] = {atui_header, atui_vram_info};
		int num_child_branches = sizeof(child_branches)/sizeof(atui_branch*);

		atui_dt = ATUI_MAKE_BRANCH(atom_master_data_table_v2_1,
			data_table,NULL,  num_child_branches,child_branches);
	}
	return atui_dt;
}


struct atom_tree* atombios_parse(void* bios, bool generate_atui) {
	if (*(uint16_t*)bios != 0xAA55)
		return NULL;
		//TODO is anyone bothering to check all the magic signs?

	struct atom_tree* atree = malloc(sizeof(struct atom_tree));
	atree->dot = atree; 
	atree->bios = bios; //PIC code; going to be used as the '0' in a lot of places.

	//TODO
	//atree->bios_size = *(uint8_t*)(bios+BIOS_IMAGE_SIZE_OFFSET) * BIOS_IMAGE_SIZE_UNIT; //wrong

	// pointer math; void is byte aligned.
	// we don't know where it is, but we can find out. Read ptr and use it.
	atree->leaves = bios +
		*(uint16_t*)(bios+OFFSET_TO_POINTER_TO_ATOM_ROM_HEADER);

	atree->protected_mode = bios + atree->leaves->protectedmodeoffset;
	atree->config_filename = bios + atree->leaves->configfilenameoffset;
	atree->crc_block = bios + atree->leaves->crc_block_offset;
	atree->bootup_mesage = bios + atree->leaves->vbios_bootupmessageoffset;
	atree->int10 = bios + atree->leaves->int10_offset;
	// any more between?
	atree->psp_dir_table = bios + atree->leaves->pspdirtableoffset;

	// atomtree_populate_commandtables(atree); // TODO


	atui_branch* atui_dt = atomtree_populate_datatables(atree, generate_atui);

	if (generate_atui) {
		atui_branch* atui_header = ATUI_MAKE_BRANCH(atom_common_table_header,
			NULL,&(atree->leaves->table_header), 0,NULL);

		atui_branch* child_branches[] = {atui_header, atui_dt};
		int num_child_branches = sizeof(child_branches)/sizeof(atui_branch*);
		atree->atui_root = ATUI_MAKE_BRANCH(atom_rom_header_v2_2,
			atree,NULL,  num_child_branches,child_branches); 
	} else {
		atree->atui_root = NULL;
	}

	return atree;
}


void* bios_fastforward(void* memory, long size) {
	// The dumped bios probably doesn't start with where atombios actually
	// begins. Go though the allocated memory to find the first magic bytes.
	uint16_t* bios = memory;
	uint16_t* end = memory+size;
	for(; bios < end; bios++)
		if (*bios == 0xAA55)
			return (void*)bios;
	return NULL;
}
void* bios_fastforward_odd(void* memory, long size) { // every 1 byte
	uint8_t* bios = memory;
	uint8_t* end = memory+size;
	for(; bios < end; bios++)
		if (*(uint16_t*)bios == 0xAA55)
			return (void*)bios;
	return NULL;
}


enum atomtree_common_version get_ver(struct atom_common_table_header* header) {
	return (header->format_revision * 100) + header->content_revision;
}
void set_ver(enum atomtree_common_version ver,
		struct atom_common_table_header* header) {
	header->format_revision = ver / 100;
	header->content_revision = ver % 100;
};
