#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include <atomtree.h>
#include <yaabe_gtk4.h>

/* TODO minor things
ATUI_FUNCIFY: make the child_branhes+inline_branches more explicit in API
	sanity pass for the free)( func
stdint-ify everything
gtk4: move gpointers to their actual things, where possible?
inline where possible
*/


int16_t getfile(char* f, void** bios, long* size){
    FILE* tm = fopen(f, "r");
	if (tm == NULL)
		return 1;
	fseek(tm,0,SEEK_END);
	*size = ftell(tm);
	fseek(tm,0,SEEK_SET);
	*bios = malloc(*size);
	fread(*bios,*size,1,tm);
	fclose(tm);
	return 0;
}

void vi24_funstuffs(struct atom_tree* atree) {
	printf("\n");
	struct atomtree_umc_init_reg_block* regblk =
		&(atree->data_table.vram_info.v2_4.mem_clk_patch);
	struct atom_umc_reg_setting_data_block** dblk= regblk->umc_reg_setting_list;
	printf("umc_reg_num: %d\n", *regblk->umc_number_of_registers);
	uint32_t memclock;
	uint16_t i,j,l = 0;
	l = (*regblk->umc_number_of_registers)*4;
	for (i=0; i < regblk->umc_reg_setting_list_length ; i++) {
		memclock = dblk[i]->block_id.memclockrange;
		printf("memclockrange %2d: %4d %4X\n    ",
			i, memclock/100, (void*)dblk[i]->u32umc_reg_data - atree->bios
		);
		for (j=0; j<l ; j++) {
			printf("%02X", ((uint8_t*)dblk[i]->u32umc_reg_data)[j]);
		}
		printf("\n");
	}
	struct atom_vram_module_v10* vram_module = 
		&(atree->data_table.vram_info.v2_4.leaves->vram_module[0]);
	printf("\n\n");
	printf("      5432109876543210\n");
	printf("MR 1: %016b\n", vram_module->gddr6_mr1);
	printf("MR 2: %016b\n", vram_module->gddr6_mr2);
	printf("MR 7: %016b\n", vram_module->gddr6_mr7);
	printf("MR10: %016b\n", vram_module->gddr6_mr10);
	printf("      5432109876543210\n");
	printf("\n\n");

	char* pnstring = vram_module->dram_pnstring;
	printf("pnstring:\"%s\"\n", pnstring);
	for(i = 0; i < 40; i++)
		printf(" %d ", pnstring[i]);
	printf("\n");
	printf("refreshrate: %i\n", vram_module->refreshrate);

}

void vi25_funstuffs(struct atom_tree* atree) {
	uint8_t i=0;
	struct atomtree_vram_info_header_v2_5* vi25 =
		&(atree->data_table.vram_info.v2_5);
	struct atom_gddr6_ac_timing_v2_5* vi25ac = &(vi25->gddr6_ac_timings)[0];
	//while (vi25ac->u32umc_id_access.u32umc_id_access) {
	for(i=0; i < vi25->gddr6_acstrap_count; i++) {
		vi25ac = &(vi25->gddr6_ac_timings)[i];
		printf("freq %4d: RL %2d, WL %d, tREFI %4d, tCCDS %d, ",
			vi25ac->u32umc_id_access.memclockrange/100,vi25ac->RL,
			vi25ac->WL,vi25ac->tREFI,vi25ac->tCCDS);
		printf("tRRDS %d, tFAW %d\n", vi25ac->tRRDS,vi25ac->tFAW);
		//i++;
	}

	struct atom_vram_module_v11* vram_module =
		&(atree->data_table.vram_info.v2_5.leaves->vram_module[0]);
	printf("\n\n");
	printf("      5432109876543210\n");
	printf("MR 0: %016b\n", vram_module->gddr6_mr0);
	printf("MR 1: %016b\n", vram_module->gddr6_mr1);
	printf("MR 2: %016b\n", vram_module->gddr6_mr2);
	printf("MR 4: %016b\n", vram_module->gddr6_mr4);
	printf("      5432109876543210\n");
	printf("MR 7: %016b\n", vram_module->gddr6_mr7);
	printf("MR 8: %016b\n", vram_module->gddr6_mr8);
	printf("MR10: %016b\n", vram_module->gddr6_mr10);
	printf("      5432109876543210\n");
	printf("bank groups enable (bit 0): %08b\n", vram_module->vram_flags);
}

void vi30_funstuffs(struct atom_tree* atree) {
	struct atomtree_vram_info_header_v3_0* vi30 =
		&(atree->data_table.vram_info.v3_0);

	struct atom_gddr6_ac_timing_v2_5* act = vi30->dram_info;
	printf("freq %4d: RL %2d, WL %d, tREFI %4d, tCCDS %d\n",
		act->u32umc_id_access.memclockrange/100,act->RL,act->WL,
		act->tREFI, act->tCCDS
	);
}


void pp1_funstuffs(struct atom_tree* atree) {
	struct smu_11_0_powerplay_table* navi1 =
		atree->data_table.powerplayinfo.navi1;

	printf("navi1 ppt: common: %d ; table_revision: %d\n",
		atree->data_table.powerplayinfo.ver, navi1->table_revision
	);
	printf("table size: common: %d ; pp %d\n",
		navi1->header.structuresize, navi1->table_size
	);
	printf("power limit:small: %d %d ; OD: %d %d\n",
		navi1->small_power_limit1, navi1->small_power_limit2,
		navi1->od_turbo_power_limit, navi1->od_power_save_power_limit
	);

	printf("\nOD:\n");
	printf("GFXCLKFMAX %d\nVDDGFXCURVEFREQ_P3 %d\nVDDGFXCURVEVOLTAGE_P3 %d\n",
		navi1->overdrive_table.max[SMU_11_0_ODSETTING_GFXCLKFMAX],
		navi1->overdrive_table.max[SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P3],
		navi1->overdrive_table.max[SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P3]
	);
	printf(
		"GFXCLK %d\nVCLK %d\nDCLK %d\nECLK %d\nSOCCLK %d\nUCLK %d\nPHYCLK %d\n",
		navi1->power_saving_clock.max[SMU_11_0_PPCLOCK_GFXCLK],
		navi1->power_saving_clock.max[SMU_11_0_PPCLOCK_VCLK],
		navi1->power_saving_clock.max[SMU_11_0_PPCLOCK_DCLK],
		navi1->power_saving_clock.max[SMU_11_0_PPCLOCK_ECLK],
		navi1->power_saving_clock.max[SMU_11_0_PPCLOCK_SOCCLK],
		navi1->power_saving_clock.max[SMU_11_0_PPCLOCK_UCLK],
		navi1->power_saving_clock.max[SMU_11_0_PPCLOCK_PHYCLK]
	);
}

void pp2_funstuffs(struct atom_tree* atree) {
}


int main(int argc, char** argv){
	printf("\n\n");
	void* bios = NULL;
	void* memfile = NULL;
	long size;
	if (getfile(argv[1], &memfile, &size)){
		printf("no file\n");
		return 1;
	}
	printf("%s: ",argv[1]);
	bios = bios_fastforward(memfile, size);
	printf("ffwd %d bytes to get to %X.\n", (bios-memfile), 0xAA55);
	struct atom_tree* atree = atombios_parse(bios, true);
	if (atree == NULL){
		printf("bad atree\n");
		return 1;
	}

	printf("master data ver: %d\n", atree->data_table.ver);
	if (atree->data_table.multimedia_info) {
		printf("multimedia_info ver: %d %d\n",
			atree->data_table.multimedia_info->table_header.format_revision,
			atree->data_table.multimedia_info->table_header.content_revision
		);
	} else {
		 printf("multimedia_info ver: not populated\n");
	}
	printf("smc_dpm_info ver: %d\n", atree->data_table.smc_dpm_info.ver);
	printf("firmwareinfo ver: %d\n", atree->data_table.firmwareinfo.ver);
	printf("smu_info ver: %d\n", atree->data_table.smu_info.ver);
	printf("lcd_info ver: %d\n", atree->data_table.lcd_info.ver);
	printf("vram_usagebyfirmware ver: %d\n",
		atree->data_table.vram_usagebyfirmware.ver
	);
	printf("gfx_info ver: %d\n", atree->data_table.gfx_info.ver);
	printf("atom pp ver: %d\n", atree->data_table.powerplayinfo.ver);
	printf("vraminfo ver: %d\n", atree->data_table.vram_info.ver);

	printf("\n");
	printf("%s\n", (char*)atree->leaves->atom_bios_string);
	printf("crc block offset: 0x%X (reg: 0x%X)\n",
		atree->leaves->crc_block_offset,
		(void*)&(atree->leaves->crc_block_offset) - atree->bios
	);



	if (0) {
		switch(atree->data_table.vram_info.ver) {
			case v2_4:
				vi24_funstuffs(atree);
				break;
			case v2_5:
				vi25_funstuffs(atree);
				break;
			case v3_0:
				vi30_funstuffs(atree);
				break;
	}}

	if (0) {
		switch(atree->data_table.powerplayinfo.pphead->table_revision) {
			case 1:
				pp1_funstuffs(atree);
				break;
			case 2:
				pp2_funstuffs(atree);
				break;
			case 0:
				//pp0_funstuffs(atree);
				break;
	}}

	yaabe_gtk(atree);
	atui_destroy_tree_with_gtk(atree->atui_root);
	free(atree->bios);
	free(atree);
	return 0;
}
