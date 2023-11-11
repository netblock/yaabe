/* For atomtree's abstract, check out atomtree_data_tables.h */

#include "atomtree.h"
#include "atui.h"

inline static atui_branch* atomtree_dt_populate_smc_dpm_info(
		struct atom_tree* atree, bool generate_atui) {

	atui_branch* atui_smc_dpm_info = NULL;
	atui_branch* atui_smudpm_i2c = NULL;
	uint16_t i = 0;

	struct atomtree_smc_dpm_info* smc_dpm_info =
		&(atree->data_table.smc_dpm_info);
	smc_dpm_info->dot = smc_dpm_info;
	smc_dpm_info->dotdot = &(atree->data_table);

	if (atree->data_table.leaves->smc_dpm_info) {
		// leaves is in a union with the structs.
		smc_dpm_info->leaves =
			atree->bios + atree->data_table.leaves->smc_dpm_info;
		smc_dpm_info->ver = get_ver(smc_dpm_info->table_header);
		if (generate_atui) {
			switch (smc_dpm_info->ver) {
				case v4_1:
					atui_smc_dpm_info = ATUI_MAKE_BRANCH(atom_smc_dpm_info_v4_1,
						NULL,smc_dpm_info->v4_1, 0,NULL
					);
					break;
				/*
				case v4_2:
					break;
				*/
				case v4_3:
					atui_smc_dpm_info = ATUI_MAKE_BRANCH(atom_smc_dpm_info_v4_3,
						NULL,smc_dpm_info->v4_3, 0,NULL
					);
					break;
				case v4_4:
					const uint8_t num_i2c_controllers_v4_4 = (
						sizeof(smc_dpm_info->v4_4->i2ccontrollers)
						/ sizeof(struct i2ccontrollerconfig_u32)
					);

					atui_smc_dpm_info = ATUI_MAKE_BRANCH(atom_smc_dpm_info_v4_4,
						NULL,smc_dpm_info->v4_4,  num_i2c_controllers_v4_4,NULL
					);
					for(i=0; i < num_i2c_controllers_v4_4; i++) {
						atui_smudpm_i2c = ATUI_MAKE_BRANCH(
							i2ccontrollerconfig_u32,
							NULL, &(smc_dpm_info->v4_4->i2ccontrollers[i]),
							0, NULL
						);
						sprintf(atui_smudpm_i2c->name, "%s [%u]",
							atui_smudpm_i2c->varname, i
						);
						atui_smc_dpm_info->child_branches[i] = atui_smudpm_i2c;
					}
					atui_smc_dpm_info->num_child_branches =\
						num_i2c_controllers_v4_4;
					break;
				case v4_5:
					const uint8_t num_i2c_controllers_v4_5 = (
						sizeof(smc_dpm_info->v4_5->I2cControllers)
						/ sizeof(struct smudpm_i2c_controller_config_v2)
					);

					atui_smc_dpm_info = ATUI_MAKE_BRANCH(atom_smc_dpm_info_v4_5,
						NULL,smc_dpm_info->v4_5,  num_i2c_controllers_v4_5,NULL
					);
					for(i=0; i < num_i2c_controllers_v4_5; i++) {
						atui_smudpm_i2c = ATUI_MAKE_BRANCH(
							smudpm_i2c_controller_config_v2,
							NULL, &(smc_dpm_info->v4_5->I2cControllers[i]),
							0, NULL
						);
						sprintf(atui_smudpm_i2c->name, "%s [%u]",
							atui_smudpm_i2c->varname, i
						);
						atui_smc_dpm_info->child_branches[i] = atui_smudpm_i2c;
					}
					atui_smc_dpm_info->num_child_branches =\
						num_i2c_controllers_v4_5;
					break;
				/*
				case v4_6:
					break;
				case v4_7:
					break;
				case v4_8:
					break;
				case v4_9:
					break;
				case v4_10:
					break;
				case v5_0:
				*/
					break;
				default:
					atui_smc_dpm_info = ATUI_MAKE_BRANCH(
						atom_common_table_header,
						NULL, smc_dpm_info->table_header,  0,NULL
					);
					sprintf(atui_smc_dpm_info->name,
						"smc_dpm_info (header only stub)"
					);
					break;
			}
		}
	} else {
		smc_dpm_info->leaves = NULL;
		smc_dpm_info->ver = nover;
	}

	return atui_smc_dpm_info;
}


inline static atui_branch* atomtree_dt_populate_firmwareinfo(
		struct atom_tree* atree, bool generate_atui) {

	atui_branch* atui_firmwareinfo = NULL;

	struct atomtree_firmware_info* firmwareinfo =
		&(atree->data_table.firmwareinfo);
	firmwareinfo->dot = firmwareinfo;
	firmwareinfo->dotdot = &(atree->data_table);

	if (atree->data_table.leaves->firmwareinfo) {
		// leaves is in a union with the structs.
		firmwareinfo->leaves =
			atree->bios + atree->data_table.leaves->firmwareinfo;
		firmwareinfo->ver = get_ver(firmwareinfo->table_header);
		if (generate_atui) {
			switch (firmwareinfo->ver) {
				case v3_1:
					atui_firmwareinfo = ATUI_MAKE_BRANCH(
						atom_firmware_info_v3_1,
						NULL,firmwareinfo->v3_1,  0,NULL
					);
					break;
				case v3_2:
					atui_firmwareinfo = ATUI_MAKE_BRANCH(
						atom_firmware_info_v3_2,
						NULL,firmwareinfo->v3_2,  0,NULL
					);
					break;
				case v3_3:
					atui_firmwareinfo = ATUI_MAKE_BRANCH(
						atom_firmware_info_v3_3,
						NULL,firmwareinfo->v3_3,  0,NULL
					);
					break;
				case v3_4:
					atui_firmwareinfo = ATUI_MAKE_BRANCH(
						atom_firmware_info_v3_4,
						NULL,firmwareinfo->v3_4,  0,NULL
					);
					break;
				default:
					atui_firmwareinfo = ATUI_MAKE_BRANCH(
						atom_common_table_header,
						NULL,firmwareinfo->table_header,  0,NULL
					);
					sprintf(atui_firmwareinfo->name,
						"firmwareinfo (header only stub)"
					);
					break;
			}
		}
	} else {
		firmwareinfo->leaves = NULL;
		firmwareinfo->ver = nover;
	}
	return atui_firmwareinfo;
}

inline static atui_branch* atomtree_dt_populate_lcd_info(
		struct atom_tree* atree, bool generate_atui) {

	atui_branch* atui_lcd_info = NULL;
	atui_branch* atui_lcd_timing = NULL;

	struct atomtree_lcd_info* lcd_info = &(atree->data_table.lcd_info);
	lcd_info->dot = lcd_info;
	lcd_info->dotdot = &(atree->data_table);

	if (atree->data_table.leaves->lcd_info) {
		lcd_info->leaves = atree->bios + atree->data_table.leaves->lcd_info;
		lcd_info->ver = get_ver(lcd_info->table_header);
		if (generate_atui) {
			switch (lcd_info->ver) {
				/*case v1_3: TODO from atombios.h */
				case v2_1:
					atui_lcd_timing = ATUI_MAKE_BRANCH(atom_dtd_format,
						NULL,&(lcd_info->v2_1->lcd_timing),  0,NULL
					);
					atui_lcd_info = ATUI_MAKE_BRANCH(atom_lcd_info_v2_1,
						NULL, lcd_info->leaves,
						1, (atui_branch*[]){atui_lcd_timing}
					);
					break;
				default:
					atui_lcd_info = ATUI_MAKE_BRANCH(
						atom_common_table_header,
						NULL,lcd_info->table_header,  0,NULL
					);
					sprintf(atui_lcd_info->name, "lcd_info (header only stub)");
					break;
			}
		}
	} else {
		lcd_info->leaves = NULL;
		lcd_info->ver = nover;
	}

	return atui_lcd_info;
}


inline static atui_branch* atomtree_dt_populate_smu_info(
		struct atom_tree* atree, bool generate_atui) {

	atui_branch* atui_smu_info = NULL;

	struct atomtree_smu_info* smu_info = &(atree->data_table.smu_info);
	smu_info->dot = smu_info;
	smu_info->dotdot = &(atree->data_table);

	smu_info->smugolden = NULL;
	smu_info->smuinit = NULL;

	// leaves is in a union with the structs.
	if (atree->data_table.leaves->smu_info) {

		smu_info->leaves = atree->bios + atree->data_table.leaves->smu_info;

		smu_info->ver = get_ver(smu_info->table_header);
		switch (smu_info->ver) { // TODO if init,golden are 0, catch them.
			case v3_1:
				if (generate_atui) {
					atui_smu_info = ATUI_MAKE_BRANCH(atom_smu_info_v3_1,
						NULL,smu_info->v3_1,  0,NULL
					);
				}
				break;
			case v3_2:
				if (generate_atui) {
					atui_smu_info = ATUI_MAKE_BRANCH(atom_smu_info_v3_2,
						NULL,smu_info->v3_2,  0,NULL
					);
				}
				if (smu_info->v3_2->smugoldenoffset) {
					smu_info->smugolden = smu_info->leaves +
						smu_info->v3_2->smugoldenoffset;
				}
				break;
			case v3_3:
				if (generate_atui) {
					atui_smu_info = ATUI_MAKE_BRANCH(atom_smu_info_v3_3,
						NULL,smu_info->v3_3,  0,NULL
					);
				}
				if (smu_info->v3_3->smugoldenoffset) {
					smu_info->smugolden = smu_info->leaves +
						smu_info->v3_3->smugoldenoffset;
				}
				if (smu_info->v3_3->smuinitoffset) {
					smu_info->smuinit = smu_info->leaves +
						smu_info->v3_3->smuinitoffset;
				}
				break;
			case v3_4: // bios reports 244 bytes. v3_5 is 240 bytes.
			case v3_5:
				if (generate_atui) {
					atui_smu_info = ATUI_MAKE_BRANCH(atom_smu_info_v3_5,
						NULL,smu_info->v3_5,  0,NULL
					);
					if (smu_info->ver == v3_4) {
						sprintf(atui_smu_info->name,
							"%s (forced)", atui_smu_info->varname
						);
					}
				}
				if (smu_info->v3_5->smugoldenoffset) {
					smu_info->smugolden = smu_info->leaves +
						smu_info->v3_5->smugoldenoffset;
				}
				if (smu_info->v3_5->smuinitoffset) {
					smu_info->smuinit = smu_info->leaves +
						smu_info->v3_5->smuinitoffset;
				}
				break;
			case v3_6:
				if (generate_atui) {
					atui_smu_info = ATUI_MAKE_BRANCH(atom_smu_info_v3_6,
						NULL,smu_info->v3_6,  0,NULL
					);
				}
				if (smu_info->v3_6->smugoldenoffset) {
					smu_info->smugolden = smu_info->leaves +
						smu_info->v3_6->smugoldenoffset;
				}
				if (smu_info->v3_6->smuinitoffset) {
					smu_info->smuinit = smu_info->leaves +
						smu_info->v3_6->smuinitoffset;
				}
				break;
			case v4_0:
				if (generate_atui) {
					atui_smu_info = ATUI_MAKE_BRANCH(atom_smu_info_v4_0,
						NULL,smu_info->v4_0,  0,NULL
					);
				}
				if (smu_info->v4_0->smuinitoffset) {
					smu_info->smuinit = smu_info->leaves +
						smu_info->v4_0->smuinitoffset;
				}
				break;
			default:
				if (generate_atui) {
					atui_smu_info = ATUI_MAKE_BRANCH(atom_common_table_header,
						NULL,smu_info->table_header,  0,NULL
					);
					sprintf(atui_smu_info->name, "smu_info (header only stub)");
				}
				break;
		}
	} else {
		smu_info->leaves = NULL;
		 smu_info->ver = nover;
	}
	return atui_smu_info;
}



inline static atui_branch* atomtree_dt_populate_vram_usagebyfirmware(
		struct atom_tree* atree, bool generate_atui) {

	atui_branch* atui_fw_vram = NULL;

	struct atomtree_vram_usagebyfirmware* fw_vram  =
		&(atree->data_table.vram_usagebyfirmware);
	fw_vram->dot = fw_vram;
	fw_vram->dotdot = &(atree->data_table);

	if (atree->data_table.leaves->vram_usagebyfirmware) {
		// leaves is in a union with the structs.
		fw_vram->leaves = atree->bios +
			atree->data_table.leaves->vram_usagebyfirmware;

		fw_vram->ver = get_ver(fw_vram->table_header);
		if (generate_atui) {
			switch(fw_vram->ver) {
				case v2_1:
					atui_fw_vram = ATUI_MAKE_BRANCH(vram_usagebyfirmware_v2_1,
						NULL,fw_vram->v2_1,  0,NULL
					);
					break;
				case v2_2:
					atui_fw_vram = ATUI_MAKE_BRANCH(vram_usagebyfirmware_v2_2,
						NULL,fw_vram->v2_2,  0,NULL
					);
					break;
				default:
					atui_fw_vram = ATUI_MAKE_BRANCH(atom_common_table_header,
						NULL,fw_vram->table_header,  0,NULL
					);
					sprintf(atui_fw_vram->name,
						"vram_usagebyfirmware (header only stub)"
					);
					break;
			}
		}
	} else {
		fw_vram->leaves = NULL;
		fw_vram->ver = nover;
	}
	return atui_fw_vram;
}


inline static atui_branch* atomtree_dt_populate_gpio_pin_lut(
		struct atom_tree* atree, bool generate_atui) {

	atui_branch* atui_gpio_pin_lut = NULL;
	atui_branch* atui_gpio_pin = NULL;
	uint16_t i;

	struct atomtree_gpio_pin_lut* gpio_pin_lut =
		&(atree->data_table.gpio_pin_lut);
	gpio_pin_lut->dot = gpio_pin_lut;
	gpio_pin_lut->dotdot = &(atree->data_table);

	if (atree->data_table.leaves->gpio_pin_lut) {
		gpio_pin_lut->leaves =
			atree->bios + atree->data_table.leaves->gpio_pin_lut;

		gpio_pin_lut->ver = get_ver(gpio_pin_lut->table_header);
		switch(gpio_pin_lut->ver) {
			case v2_1:
				gpio_pin_lut->num_gpio_pins = (
					//dynamic array length of nothing but pins after the header
					(gpio_pin_lut->table_header->structuresize
					- sizeof(struct atom_common_table_header)
					) / sizeof(struct atom_gpio_pin_assignment_v2_1)
				);
				if (generate_atui) {
					atui_gpio_pin_lut = ATUI_MAKE_BRANCH(
						atom_common_table_header,
						NULL,gpio_pin_lut->table_header,
						gpio_pin_lut->num_gpio_pins,NULL
					);
					sprintf(atui_gpio_pin_lut->name, "atom_gpio_pin_lut_v2_1");
					for(i=0; i < gpio_pin_lut->num_gpio_pins; i++) {
							atui_gpio_pin = ATUI_MAKE_BRANCH(
								atom_gpio_pin_assignment_v2_1,
								NULL,&(gpio_pin_lut->v2_1->gpio_pin[i]),  0,NULL
							);
							sprintf(atui_gpio_pin->name, "%s [%02u]",
								atui_gpio_pin->varname, i
							);
							atui_gpio_pin_lut->child_branches[i]=atui_gpio_pin;
					}
					atui_gpio_pin_lut->num_child_branches =
						gpio_pin_lut->num_gpio_pins;
				}
				break;
			default:
				gpio_pin_lut->num_gpio_pins = 0;
				if (generate_atui) {
					atui_gpio_pin_lut = ATUI_MAKE_BRANCH(
						atom_common_table_header,
						NULL,gpio_pin_lut->table_header,  0,NULL
					);
					sprintf(atui_gpio_pin_lut->name,
						"gpio_pin_lut (header only stub)"
					);
				}
				break;
		}
	} else {
		gpio_pin_lut->leaves = NULL;
		gpio_pin_lut->num_gpio_pins = 0;
		gpio_pin_lut->ver = nover;
	}
	return atui_gpio_pin_lut;
}

inline static atui_branch* atomtree_dt_populate_gfx_info(
		struct atom_tree* atree, bool generate_atui) {

	atui_branch* atui_gfx_info = NULL;

	struct atomtree_gfx_info* gfx_info = &(atree->data_table.gfx_info);
	gfx_info->dot = gfx_info;
	gfx_info->dotdot = &(atree->data_table);
	gfx_info->gcgolden = NULL;

	if (atree->data_table.leaves->gfx_info) {
		// leaves is in a union with the structs.
		gfx_info->leaves = atree->bios + atree->data_table.leaves->gfx_info;

		gfx_info->ver = get_ver(gfx_info->table_header);
		switch(gfx_info->ver) {
			case v2_2:
				if (generate_atui) {
					atui_gfx_info = ATUI_MAKE_BRANCH(atom_gfx_info_v2_2,
						NULL,gfx_info->v2_2,  0,NULL
					);
				}
				break;
			case v2_3:
				if (gfx_info->v2_3->gcgoldenoffset) {
					gfx_info->gcgolden = gfx_info->leaves
						+ gfx_info->v2_3->gcgoldenoffset;
				}
				if (generate_atui) {
					atui_gfx_info = ATUI_MAKE_BRANCH(atom_gfx_info_v2_3,
						NULL,gfx_info->v2_3,  0,NULL
					);
				}
				break;
			case v2_4:
				if (gfx_info->v2_4->gcgoldenoffset) {
					gfx_info->gcgolden = gfx_info->leaves
						+ gfx_info->v2_4->gcgoldenoffset;
				}
				if (generate_atui) {
					atui_gfx_info = ATUI_MAKE_BRANCH(atom_gfx_info_v2_4,
						NULL,gfx_info->v2_4,  0,NULL
					);
				}
				break;
			case v2_5:
				if (gfx_info->v2_5->gcgoldenoffset) {
					gfx_info->gcgolden = gfx_info->leaves
						+ gfx_info->v2_5->gcgoldenoffset;
				}
				if (generate_atui) {
					atui_gfx_info = ATUI_MAKE_BRANCH(atom_gfx_info_v2_5,
						NULL,gfx_info->v2_5,  0,NULL
					);
				}
				break;
			case v2_6:
				if (gfx_info->v2_6->gcgoldenoffset) {
					gfx_info->gcgolden = gfx_info->leaves
						+ gfx_info->v2_6->gcgoldenoffset;
				}
				if (generate_atui) {
					atui_gfx_info = ATUI_MAKE_BRANCH(atom_common_table_header,
						NULL,gfx_info->table_header,  1,NULL
					);
					sprintf(atui_gfx_info->name, "atom_gfx_info_v2_6 (forced)");
					atui_gfx_info->num_child_branches = 1;
					atui_gfx_info->child_branches[0] = ATUI_MAKE_BRANCH(
						atom_gfx_info_v2_5,
						NULL,gfx_info->v2_6,  0,NULL
					);
				}
				break;
			case v2_7:
				if (gfx_info->v2_7->gcgoldenoffset) {
					gfx_info->gcgolden = gfx_info->leaves
						+ gfx_info->v2_7->gcgoldenoffset;
				}
				if (generate_atui) {
					atui_gfx_info = ATUI_MAKE_BRANCH(atom_gfx_info_v2_7,
						NULL,gfx_info->v2_7,  0,NULL
					);
				}
				break;
			case v3_0:
				if (generate_atui) {
					atui_gfx_info = ATUI_MAKE_BRANCH(atom_gfx_info_v3_0,
						NULL,gfx_info->v3_0,  0,NULL
					);
				}
				break;
			default:
				if (generate_atui) {
					atui_gfx_info = ATUI_MAKE_BRANCH(atom_common_table_header,
						NULL,gfx_info->table_header,  0,NULL
					);
					sprintf(atui_gfx_info->name, "gfx_info (header only stub)");
				}
				break;
		}
	} else {
		gfx_info->leaves = NULL;
		gfx_info->ver = nover;
	}
	return atui_gfx_info;
}


inline static atui_branch* atomtree_dt_populate_ppt(
		struct atom_tree* atree, bool generate_atui) {

	atui_branch* atui_ppt = NULL;

	struct atomtree_powerplaytable* ppt = &(atree->data_table.powerplayinfo);
	ppt->dot = ppt;
	ppt->dotdot = &(atree->data_table);

	if (atree->data_table.leaves->powerplayinfo) {
		atui_branch* atui_powersaving_table = NULL;
		atui_branch* atui_overdrive_table = NULL;
		atui_branch* atui_smc_pptable = NULL;
		atui_branch* atui_feature_control = NULL;
		atui_branch* atui_i2c = NULL;


		ppt->powerplay_table_ver = &(ppt->pphead->table_revision);

		// leaves is in a union with the structs.
		ppt->leaves = atree->bios + atree->data_table.leaves->powerplayinfo;
		ppt->ver = get_ver(ppt->table_header);
		switch(ppt->ver) {
			case v14_0:
			case v12_0:
				ppt->smc_pptable_ver = &(
					ppt->v12_0->smc_pptable.smc_pptable_ver
				);

				if (generate_atui) {
					switch(*(ppt->smc_pptable_ver)) {
						case 3:
							atui_feature_control = ATUI_MAKE_BRANCH(
								powerplay_feature_control_smu11_19,   NULL,
								&(ppt->v12_0->smc_pptable.v3.features),
								0,NULL
							);
							atui_i2c = ATUI_MAKE_BRANCH(
								smu11_pptable_v3_i2c_u32,   NULL,
								&(ppt->v12_0->smc_pptable.v3.I2cControllers),
								0,NULL
							);
							atui_smc_pptable = ATUI_MAKE_BRANCH(
								smu11_smcpptable_v3,
								NULL, &(ppt->v12_0->smc_pptable),
								2, NULL
							);
							break;
						default:
						case 8:
							atui_feature_control = ATUI_MAKE_BRANCH(
								powerplay_feature_control_smu11_51,   NULL,
								&(ppt->v12_0->smc_pptable.v8.features),
								0,NULL
							);
							atui_i2c = ATUI_MAKE_BRANCH(
								smu11_pptable_v8_i2c_u8mixed,   NULL,
								&(ppt->v12_0->smc_pptable.v8.I2cControllers),
								0,NULL
							);
							atui_smc_pptable = ATUI_MAKE_BRANCH(
								smu11_smcpptable_v8,
								NULL, &(ppt->v12_0->smc_pptable),
								2, NULL
							);
							break;
					}
					atui_smc_pptable->num_child_branches = 2;
					atui_smc_pptable->child_branches[0] = atui_feature_control;
					atui_smc_pptable->child_branches[1] = atui_i2c;

					atui_powersaving_table = ATUI_MAKE_BRANCH(
						smu_11_0_power_saving_clock_table,
						NULL,&(ppt->v12_0->power_saving_clock),  0,NULL
					);
					atui_overdrive_table = ATUI_MAKE_BRANCH(
						smu_11_0_overdrive_table,
						NULL,&(ppt->v12_0->overdrive_table),  0,NULL
					);

					atui_branch* atui_smu11ppt_kids[] = {
						atui_powersaving_table, atui_overdrive_table,
						atui_smc_pptable
					};
					atui_ppt = ATUI_MAKE_BRANCH(smu_11_0_powerplay_table,
						NULL,ppt->v12_0,
						sizeof(atui_smu11ppt_kids)/sizeof(atui_branch*),
						atui_smu11ppt_kids
					);
				}
				break;
			default:
				if (generate_atui) {
					atui_ppt = ATUI_MAKE_BRANCH(smu_powerplay_table_header,
						NULL,ppt->leaves,  0,NULL
					);
					sprintf(atui_ppt->name, "%s (header only stub)",
						atui_ppt->varname
					);
				}
				break;
		}

	} else {
		ppt->leaves = NULL;
		ppt->ver = nover;
	}
	return atui_ppt;
}


static atui_branch* atomtree_populate_umc_init_reg_block(
		struct atom_tree* atree,
		struct atomtree_umc_init_reg_block* at_regblock,
		bool generate_atui, uint8_t num_extra_atuibranches) {

	uint16_t i = 0;

	// TODO: something something end is 0xFFFF ???

	// regblock->leaves must be already populated.
	at_regblock->dot = at_regblock;
	at_regblock->dotdot = &(atree->data_table.vram_info);
	/*
	AMD, what the fuck? fuckin please be consistent. Use your common table
	structure, and use your pointers. And why aren't your pointers starting
	off from 0? So clunky. iT cOsTs TwO eXtRa ByTeS your bioses are like half
	empty. Is this clunk from the ATI days? Even so, change the API; there is
	room for grace.
	hell, I'd make the pointers 64-bit so you could just plop down a struct
	tree onto the void* bios, assume -fPIC and be done with it.


	Take a look at struct atom_umc_init_reg_block of atomfirmware.h.
	This struct has 3 notable lists:
	umc_reg_list, umc_reg_setting_list, and
	atom_umc_reg_setting_data_block's u32umc_reg_data.
	These lists are all dynamically sized.

	umc_reg_list follows umc_reg_num.
	umc_reg_setting_list starts immediately after umc_reg_list.
	umc_reg_setting_list does not follow umc_reg_num. but ends with 0-fill.
	and atom_umc_reg_setting_data_block's u32umc_reg_data follows
	umc_reg_num.
	*/
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
	uint16_t regsetting_elementsize =
		sizeof(struct atom_umc_reg_setting_data_block) +
		sizeof(uint32_t) * (*at_regblock->umc_number_of_registers-1);
	at_regblock->umc_reg_setting_list_element_size = regsetting_elementsize;

	struct atom_umc_reg_setting_data_block* loc;
	for (i=0; i < *at_regblock->umc_number_of_registers ; i++) {
		loc = regsettingblock_starting_point + regsetting_elementsize*i;
		if (loc->block_id.u32umc_id_access == 0)
			break; // AtomBIOS ends the datablock list with 0-fill.
		at_regblock->umc_reg_setting_list[i] = loc;
	}
	at_regblock->umc_reg_setting_list_length = i;


	atui_branch* atui_regblock = NULL;
	if(generate_atui) {
		atui_branch* tmp_branch = NULL;

		atui_branch* addr_info = ATUI_MAKE_BRANCH(
			atom_umc_register_addr_info_access,
			at_regblock,at_regblock->leaves,  0,NULL
		);

		atui_branch* datablock = ATUI_MAKE_BRANCH(atui_nullstruct,
			NULL,NULL,  at_regblock->umc_reg_setting_list_length,NULL
		);
		sprintf(datablock->name, "atom_umc_reg_setting_data_block");
		for(i=0; i < at_regblock->umc_reg_setting_list_length; i++) {
			tmp_branch = ATUI_MAKE_BRANCH(atom_umc_reg_setting_data_block,
				at_regblock,at_regblock->umc_reg_setting_list[i],  0,NULL
			);
			sprintf(tmp_branch->name, "%s [%02u]", tmp_branch->varname, i);
			datablock->child_branches[i] = tmp_branch;
		}
		datablock->num_child_branches = i;


		atui_branch* regblock_children[] = {addr_info, datablock};
		const uint8_t num_regblock_children =
			sizeof(regblock_children)/sizeof(atui_branch*);
		atui_regblock = ATUI_MAKE_BRANCH(atom_umc_init_reg_block,
			at_regblock, at_regblock->leaves,
			num_regblock_children+num_extra_atuibranches, NULL
		);
		for(i=0; i < num_regblock_children; i++) {
			atui_regblock->child_branches[i] = regblock_children[i];
		}
		atui_regblock->num_child_branches = i;
	}
	return atui_regblock;
}

inline static atui_branch* atomtree_populate_vram_info_v2_3(
		struct atom_tree* atree, bool generate_atui) {

	uint16_t i = 0;

	struct atomtree_vram_info_header_v2_3* vi23 =
		&(atree->data_table.vram_info.v2_3);
	vi23->dot = vi23;
	vi23->dotdot = &(atree->data_table.vram_info);
	vi23->leaves = atree->bios +
		atree->data_table.leaves->vram_info;


	atui_branch* atui_memadjust = NULL;
	if (vi23->leaves->mem_adjust_tbloffset) {
		vi23->mem_adjust_table.leaves = (void*)vi23->leaves +
			vi23->leaves->mem_adjust_tbloffset;
		atui_memadjust = atomtree_populate_umc_init_reg_block(
			atree, &(vi23->mem_adjust_table), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_memadjust->name, "mem_adjust_table");
	} else {
		vi23->mem_adjust_table.leaves = NULL;
	}


	atui_branch* atui_memclkpatch = NULL;
	if (vi23->leaves->mem_clk_patch_tbloffset) {
		vi23->mem_clk_patch.leaves = (void*)vi23->leaves +
			vi23->leaves->mem_clk_patch_tbloffset;
		atui_memclkpatch = atomtree_populate_umc_init_reg_block(
			atree, &(vi23->mem_clk_patch), generate_atui, 0
		);
			if (generate_atui)
				sprintf(atui_memclkpatch->name, "mem_clk_patch_table");
	} else {
		vi23->mem_clk_patch.leaves = NULL;
	}


	atui_branch* atui_mcadjpertile = NULL;
	if (vi23->leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi23->mc_adjust_pertile.leaves = (void*)vi23->leaves +
			vi23->leaves->mc_adjust_pertile_tbloffset;
		atui_mcadjpertile = atomtree_populate_umc_init_reg_block(
			atree, &(vi23->mc_adjust_pertile), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_mcadjpertile->name, "mc_adjust_pertile_table");
	} else {
		vi23->mc_adjust_pertile.leaves = NULL;
	}


	atui_branch* atui_phyinit = NULL;
	if (vi23->leaves->mc_phyinit_tbloffset) {
		vi23->mc_phyinit.leaves = (void*)vi23->leaves +
			vi23->leaves->mc_phyinit_tbloffset;
		atui_phyinit = atomtree_populate_umc_init_reg_block(
			atree, &(vi23->mc_phyinit), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_phyinit->name, "mc_phyinit_table");
	} else {
		vi23->mc_phyinit.leaves = NULL;
	}

	atui_branch* atui_dram_remap = NULL;
	if (vi23->leaves->dram_data_remap_tbloffset) {
	// TODO does vraminfo->mc_phy_tile_num significantly affect this?
	// TODO probably has the structure in atombios.h, rather than the gddr6 one
	// in atomfirmware.h
	vi23->dram_data_remap = (void*)vi23->leaves +
		vi23->leaves->dram_data_remap_tbloffset;
	} else {
		vi23->dram_data_remap = NULL;
	}


	atui_branch* atui_hbm_tmrs = NULL;
	if (vi23->leaves->tmrs_seq_offset) {
		// TODO what is this?
		vi23->hbm_tmrs = (void*)vi23->leaves + vi23->leaves->tmrs_seq_offset;
		if (generate_atui)
			;
	} else {
		vi23->hbm_tmrs = NULL;
	}


	atui_branch* atui_postucode_init = NULL;
	if (vi23->leaves->post_ucode_init_offset) {
		vi23->post_ucode_init.leaves = (void*)vi23->leaves +
			vi23->leaves->post_ucode_init_offset;
		atui_branch* atui_postucode_init = atomtree_populate_umc_init_reg_block(
			atree, &(vi23->post_ucode_init), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_postucode_init->name, "post_ucode_init");
	} else {
		vi23->post_ucode_init.leaves = NULL;
	}


	atui_branch* atui_vi = NULL;
	atui_branch* tmp_branch = NULL;
	if(generate_atui) {
		const uint8_t num_vram_modules = (
			sizeof(vi23->leaves->vram_module)
			/ sizeof(struct atom_vram_module_v9)
		);
		atui_branch* vram_module = ATUI_MAKE_BRANCH(atui_nullstruct,
			NULL,NULL,  num_vram_modules,NULL
		);
		sprintf(vram_module->name, "atom_vram_module_v9");
		for(i=0; i < num_vram_modules; i++) {
			tmp_branch = ATUI_MAKE_BRANCH(atom_vram_module_v9,
				NULL,&(vi23->leaves->vram_module[i]),  0,NULL
			);
			sprintf(tmp_branch->name, "%s [%02u]", tmp_branch->varname, i);
			vram_module->child_branches[i] = tmp_branch;
		}
		vram_module->num_child_branches = i;

		atui_branch* vi23_children[] = {
			atui_memadjust, atui_memclkpatch, atui_mcadjpertile, atui_phyinit,
			atui_dram_remap, atui_hbm_tmrs, atui_postucode_init, vram_module
		};
		const uint8_t num_children = sizeof(vi23_children)/sizeof(atui_branch*);

		atui_vi = ATUI_MAKE_BRANCH(atom_vram_info_header_v2_3,
			vi23,vi23->leaves,  num_children,vi23_children
		);
	}
	return atui_vi;
}

inline static atui_branch* atomtree_populate_vram_info_v2_4(
		struct atom_tree* atree, bool generate_atui) {

	uint16_t i,j = 0;
	atui_branch* tmp_branch = NULL;

	struct atomtree_vram_info_header_v2_4* vi24 =
		&(atree->data_table.vram_info.v2_4);
	vi24->dot = vi24;
	vi24->dotdot = &(atree->data_table.vram_info);
	vi24->leaves = atree->bios +
		atree->data_table.leaves->vram_info;
	struct atom_vram_info_header_v2_4* leaves = vi24->leaves;


	atui_branch* atui_memadjust = NULL;
	if (vi24->leaves->mem_adjust_tbloffset) {
		vi24->mem_adjust_table.leaves = (void*)vi24->leaves +
			vi24->leaves->mem_adjust_tbloffset;
		atui_memadjust = atomtree_populate_umc_init_reg_block(
			atree, &(vi24->mem_adjust_table), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_memadjust->name, "mem_adjust_table");
	} else {
		vi24->mem_adjust_table.leaves = NULL;
	}


	atui_branch* atui_memclkpatch = NULL;
	if (vi24->leaves->mem_clk_patch_tbloffset) {
		vi24->mem_clk_patch.leaves = (void*)vi24->leaves +
			vi24->leaves->mem_clk_patch_tbloffset;
		atui_memclkpatch = atomtree_populate_umc_init_reg_block(
			atree, &(vi24->mem_clk_patch), generate_atui, 1 // 1 for timings
		);

		vi24->navi1_gddr6_timings = (struct umc_block_navi1_timings*)\
			vi24->mem_clk_patch.umc_reg_setting_list[0];
		vi24->num_timing_straps =
			&(vi24->mem_clk_patch.umc_reg_setting_list_length);

		if (generate_atui) {
			atui_branch* atui_navi_timings = ATUI_MAKE_BRANCH(atui_nullstruct,
				NULL,NULL,  *vi24->num_timing_straps,NULL
			);
			for(i=0; i < *vi24->num_timing_straps; i++) {
				tmp_branch = ATUI_MAKE_BRANCH(umc_block_navi1_timings,
					NULL,&(vi24->navi1_gddr6_timings[i]),  0,NULL
				);
				sprintf(tmp_branch->name, "%s (%i MHz)",
					tmp_branch->varname,
					(vi24->navi1_gddr6_timings[i].block_id.memclockrange / 100)
				);
				atui_navi_timings->child_branches[i] = tmp_branch;
			}
			atui_navi_timings->num_child_branches = i;

			sprintf(atui_navi_timings->name, "umc_block_navi1_timings");
			sprintf(atui_memclkpatch->name, "mem_clk_patch_table");
			atui_memclkpatch->child_branches[
					atui_memclkpatch->num_child_branches
				] = atui_navi_timings;
			atui_memclkpatch->num_child_branches++;
		}
	} else {
		vi24->mem_clk_patch.leaves = NULL;
		vi24->navi1_gddr6_timings = NULL;
		vi24->num_timing_straps = 0;
	}


	atui_branch* atui_mcadjpertile = NULL;
	if (vi24->leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi24->mc_adjust_pertile.leaves = (void*)vi24->leaves +
			vi24->leaves->mc_adjust_pertile_tbloffset;
		atui_mcadjpertile = atomtree_populate_umc_init_reg_block(
			atree, &(vi24->mc_adjust_pertile), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_mcadjpertile->name, "mc_adjust_pertile_table");
	} else {
		vi24->mc_adjust_pertile.leaves = NULL;
	}


	atui_branch* atui_phyinit = NULL;
	if (vi24->leaves->mc_phyinit_tbloffset) {
		vi24->mc_phyinit.leaves = (void*)vi24->leaves +
			vi24->leaves->mc_phyinit_tbloffset;
		atui_phyinit = atomtree_populate_umc_init_reg_block(
			atree, &(vi24->mc_phyinit), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_phyinit->name, "mc_phyinit_table");
	} else {
		vi24->mc_phyinit.leaves = NULL;
	}

	atui_branch* atui_dram_data_remap = NULL;
	if (vi24->leaves->dram_data_remap_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi24->dram_data_remap = (void*)vi24->leaves +
			vi24->leaves->dram_data_remap_tbloffset;
		const uint8_t num_bit_byte_remap =
			sizeof(vi24->dram_data_remap->bit_byte_remap)
			/ sizeof(struct atom_gddr6_bit_byte_remap);
		atui_dram_data_remap = ATUI_MAKE_BRANCH(atom_gddr6_dram_data_remap,
			NULL,vi24->dram_data_remap,  num_bit_byte_remap,NULL
		);
		 atui_dram_data_remap->child_branches[0] = ATUI_MAKE_BRANCH(
			atom_gddr6_bit_byte_remap,
			NULL,&(vi24->dram_data_remap->bit_byte_remap[i]),  0,NULL
		);
	} else {
		vi24->dram_data_remap = NULL;
	}


	atui_branch* atui_postucode_init = NULL;
	if (vi24->leaves->post_ucode_init_offset) {
		vi24->post_ucode_init.leaves = (void*)vi24->leaves +
			vi24->leaves->post_ucode_init_offset;
		atui_postucode_init = atomtree_populate_umc_init_reg_block(
			atree, &(vi24->post_ucode_init), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_postucode_init->name, "post_ucode_init");
	} else {
		vi24->post_ucode_init.leaves = NULL;
	}

	atui_branch* atui_vi = NULL;
	if(generate_atui) {
		const uint8_t num_vram_modules = (
			sizeof(vi24->leaves->vram_module)
			/ sizeof(struct atom_vram_module_v10)
		);
		atui_branch* vram_module = ATUI_MAKE_BRANCH(atui_nullstruct,
			NULL,NULL,  num_vram_modules,NULL
		);
		sprintf(vram_module->name, "atom_vram_module_v10");
		for(i=0; i < num_vram_modules; i++) {
			tmp_branch = ATUI_MAKE_BRANCH(atom_vram_module_v10,
				NULL,&(vi24->leaves->vram_module[i]),  0,NULL
			);
			sprintf(tmp_branch->name, "%s [%02u]", tmp_branch->varname, i);
			vram_module->child_branches[i] = tmp_branch;
		}
		vram_module->num_child_branches = i;

		atui_branch* vi24_children[] = {
			atui_memadjust, atui_memclkpatch, atui_mcadjpertile,
			atui_dram_data_remap, atui_phyinit, atui_postucode_init,
			vram_module
		};
		const uint8_t num_children = sizeof(vi24_children)/sizeof(atui_branch*);


		atui_vi = ATUI_MAKE_BRANCH(atom_vram_info_header_v2_4,
			vi24,vi24->leaves,   num_children,vi24_children
		);
	}
	return atui_vi;
}

inline static atui_branch* atomtree_populate_vram_info_v2_5(
		struct atom_tree* atree, bool generate_atui) {

	uint16_t i = 0;
	atui_branch* tmp_branch = NULL;

	struct atomtree_vram_info_header_v2_5* vi25 =
		&(atree->data_table.vram_info.v2_5);
	vi25->dot = vi25;
	vi25->dotdot = &(atree->data_table.vram_info);
	vi25->leaves = atree->bios +
		atree->data_table.leaves->vram_info;


	atui_branch* atui_memadjust = NULL;
	if (vi25->leaves->mem_adjust_tbloffset) {
		vi25->mem_adjust_table.leaves = (void*)vi25->leaves +
			vi25->leaves->mem_adjust_tbloffset;
		atui_memadjust = atomtree_populate_umc_init_reg_block(
			atree, &(vi25->mem_adjust_table), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_memadjust->name, "mem_adjust_table");
	} else {
		vi25->mem_adjust_table.leaves = NULL;
	}


	atui_branch* atui_gddr6_ac_timings = NULL;
	if (vi25->leaves->gddr6_ac_timing_offset) {
		vi25->gddr6_ac_timings = (void*)vi25->leaves +
			vi25->leaves->gddr6_ac_timing_offset;
		i = 0;
		while(vi25->gddr6_ac_timings[i].u32umc_id_access.u32umc_id_access)
			i++;
		vi25->gddr6_acstrap_count = i;
		if (generate_atui) {
			atui_gddr6_ac_timings = ATUI_MAKE_BRANCH(atui_nullstruct,
				NULL,NULL,  vi25->gddr6_acstrap_count,NULL
			);
			sprintf(atui_gddr6_ac_timings->name, "atom_gddr6_ac_timing_v2_5");
			for(i=0; i < vi25->gddr6_acstrap_count; i++) {
				tmp_branch = ATUI_MAKE_BRANCH(atom_gddr6_ac_timing_v2_5,
					NULL, &(vi25->gddr6_ac_timings[i]),  0,NULL
				);
				sprintf(tmp_branch->name, "%s (%u MHz)",
					tmp_branch->varname,
					vi25->gddr6_ac_timings[i].u32umc_id_access.memclockrange/100
				);
				atui_gddr6_ac_timings->child_branches[i] = tmp_branch;
			}
			atui_gddr6_ac_timings->num_child_branches =
				vi25->gddr6_acstrap_count;
		}
	} else {
		vi25->gddr6_ac_timings = NULL;
		vi25->gddr6_acstrap_count = 0;
	}


	atui_branch* atui_mcadjpertile = NULL;
	if (vi25->leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi25->mc_adjust_pertile.leaves = (void*)vi25->leaves +
			vi25->leaves->mc_adjust_pertile_tbloffset;
		atui_mcadjpertile = atomtree_populate_umc_init_reg_block(
			atree, &(vi25->mc_adjust_pertile), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_mcadjpertile->name, "mc_adjust_pertile_table");
	} else {
		vi25->mc_adjust_pertile.leaves = NULL;
	}


	atui_branch* atui_phyinit = NULL;
	if (vi25->leaves->mc_phyinit_tbloffset) {
		vi25->mc_phyinit.leaves = (void*)vi25->leaves +
			vi25->leaves->mc_phyinit_tbloffset;
		atui_phyinit = atomtree_populate_umc_init_reg_block(
			atree, &(vi25->mc_phyinit), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_phyinit->name, "mc_phyinit_table");
	} else {
		vi25->mc_phyinit.leaves = NULL;
	}


	atui_branch* atui_dram_data_remap = NULL;
	if (vi25->leaves->dram_data_remap_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi25->dram_data_remap = (void*)vi25->leaves +
			vi25->leaves->dram_data_remap_tbloffset;
	} else {
		vi25->dram_data_remap = NULL;
	}


	atui_branch* atui_postucode_init = NULL;
	if (vi25->leaves->post_ucode_init_offset) {
		vi25->post_ucode_init.leaves = (void*)vi25->leaves +
			vi25->leaves->post_ucode_init_offset;
		atui_postucode_init = atomtree_populate_umc_init_reg_block(
			atree, &(vi25->post_ucode_init), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_postucode_init->name, "post_ucode_init");
	} else {
		vi25->post_ucode_init.leaves = NULL;
	}


	atui_branch* atui_strobe_mode_patch = NULL;
	if (vi25->leaves->strobe_mode_patch_tbloffset) {
		vi25->strobe_mode_patch.leaves = (void*)vi25->leaves +
			vi25->leaves->strobe_mode_patch_tbloffset;
		atui_strobe_mode_patch = atomtree_populate_umc_init_reg_block(
			atree, &(vi25->strobe_mode_patch), generate_atui, 0
		);
	} else {
		vi25->strobe_mode_patch.leaves = NULL;
	}

	atui_branch* atui_vi = NULL;
	if(generate_atui) {
		const uint8_t num_vram_modules = (
			sizeof(vi25->leaves->vram_module)
			/ sizeof(struct atom_vram_module_v11)
		);
		atui_branch* vram_module = ATUI_MAKE_BRANCH(atui_nullstruct,
			NULL,NULL,  num_vram_modules,NULL
		);
		sprintf(vram_module->name, "atom_vram_module_v11");
		for(i=0; i < num_vram_modules; i++) {
			tmp_branch = ATUI_MAKE_BRANCH(atom_vram_module_v11,
				NULL,&(vi25->leaves->vram_module[i]),  0,NULL
			);
			sprintf(tmp_branch->name, "%s [%02u]", tmp_branch->varname, i);
			vram_module->child_branches[i] = tmp_branch;
		}
		vram_module->num_child_branches = i;

		atui_branch* vi25_children[] = {
			atui_memadjust, atui_gddr6_ac_timings, atui_mcadjpertile,
			atui_phyinit, atui_dram_data_remap, atui_postucode_init,
			atui_strobe_mode_patch, vram_module,
		};
		const uint8_t num_children = sizeof(vi25_children)/sizeof(atui_branch*);


		atui_vi = ATUI_MAKE_BRANCH(atom_vram_info_header_v2_5,
			vi25,vi25->leaves,  num_children,vi25_children
		);
	}
	return atui_vi;
}

inline static atui_branch* atomtree_populate_vram_info_v2_6(
		struct atom_tree* atree, bool generate_atui) {

	uint16_t i = 0;
	atui_branch* tmp_branch = NULL;

	struct atomtree_vram_info_header_v2_6* vi26 =
		&(atree->data_table.vram_info.v2_6);
	vi26->dot = vi26;
	vi26->dotdot = &(atree->data_table.vram_info);
	vi26->leaves = atree->bios +
		atree->data_table.leaves->vram_info;


	atui_branch* atui_memadjust = NULL;
	if (vi26->leaves->mem_adjust_tbloffset) {
		vi26->mem_adjust_table.leaves = (void*)vi26->leaves +
			vi26->leaves->mem_adjust_tbloffset;
		atui_memadjust = atomtree_populate_umc_init_reg_block(
			atree, &(vi26->mem_adjust_table), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_memadjust->name, "mem_adjust_table");
	} else {
		vi26->mem_adjust_table.leaves = NULL;
	}


	atui_branch* atui_memclkpatch = NULL;
	if (vi26->leaves->mem_clk_patch_tbloffset) {
		vi26->mem_clk_patch.leaves = (void*)vi26->leaves +
			vi26->leaves->mem_clk_patch_tbloffset;
		atui_memclkpatch = atomtree_populate_umc_init_reg_block(
			atree, &(vi26->mem_clk_patch), generate_atui, 0
		);

		if (generate_atui)
			sprintf(atui_memclkpatch->name, "mem_clk_patch_table");
	} else {
		vi26->mem_clk_patch.leaves = NULL;
	}


	atui_branch* atui_mcadjpertile = NULL;
	if (vi26->leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi26->mc_adjust_pertile.leaves = (void*)vi26->leaves +
			vi26->leaves->mc_adjust_pertile_tbloffset;
		atui_mcadjpertile = atomtree_populate_umc_init_reg_block(
			atree, &(vi26->mc_adjust_pertile), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_mcadjpertile->name, "mc_adjust_pertile_table");
	} else {
		vi26->mc_adjust_pertile.leaves = NULL;
	}


	atui_branch* atui_phyinit = NULL;
	if (vi26->leaves->mc_phyinit_tbloffset) {
		vi26->mc_phyinit.leaves = (void*)vi26->leaves +
			vi26->leaves->mc_phyinit_tbloffset;
		atui_phyinit = atomtree_populate_umc_init_reg_block(
			atree, &(vi26->mc_phyinit), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_phyinit->name, "mc_phyinit_table");
	} else {
		vi26->mc_phyinit.leaves = NULL;
	}

	atui_branch* atui_tmrs_seq = NULL;
	if (vi26->leaves->tmrs_seq_offset) {
		// TODO what is this?
		vi26->tmrs_seq = (void*)vi26->leaves + vi26->leaves->tmrs_seq_offset;
		if (generate_atui)
			;
	} else {
		vi26->tmrs_seq = NULL;
	}

	atui_branch* atui_dram_data_remap = NULL;
	if (vi26->leaves->dram_data_remap_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi26->dram_data_remap = (void*)vi26->leaves +
			vi26->leaves->dram_data_remap_tbloffset;
	} else {
		vi26->dram_data_remap = NULL;
	}


	atui_branch* atui_postucode_init = NULL;
	if (vi26->leaves->post_ucode_init_offset) {
		vi26->post_ucode_init.leaves = (void*)vi26->leaves +
			vi26->leaves->post_ucode_init_offset;
		atui_postucode_init = atomtree_populate_umc_init_reg_block(
			atree, &(vi26->post_ucode_init), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_postucode_init->name, "post_ucode_init");
	} else {
		vi26->post_ucode_init.leaves = NULL;
	}

	atui_branch* atui_vi = NULL;
	if(generate_atui) {
		const uint8_t num_vram_modules = (
			sizeof(vi26->leaves->vram_module)
			/ sizeof(struct atom_vram_module_v9)
		);
		atui_branch* vram_module = ATUI_MAKE_BRANCH(atui_nullstruct,
			NULL,NULL,  num_vram_modules,NULL
		);
		sprintf(vram_module->name, "atom_vram_module_v9");
		for(i=0; i < num_vram_modules; i++) {
			tmp_branch = ATUI_MAKE_BRANCH(atom_vram_module_v9,
				NULL,&(vi26->leaves->vram_module[i]),  0,NULL
			);
			sprintf(tmp_branch->name, "%s [%02u]", tmp_branch->varname, i);
			vram_module->child_branches[i] = tmp_branch;
		}
		vram_module->num_child_branches = i;

		atui_branch* vi26_children[] = {
			atui_memadjust, atui_mcadjpertile, atui_phyinit,
			atui_dram_data_remap, atui_tmrs_seq, atui_postucode_init,
			vram_module,
		};
		const uint8_t num_children = sizeof(vi26_children)/sizeof(atui_branch*);


		atui_vi = ATUI_MAKE_BRANCH(atom_vram_info_header_v2_5,
			vi26,vi26->leaves,  num_children,vi26_children
		);
	}
	return atui_vi;
}

inline static atui_branch* atomtree_populate_vram_info_v3_0(// TODO finish this
		struct atom_tree* atree, bool generate_atui) {
	uint16_t i = 0;
	atui_branch* tmp_branch = NULL;

	struct atomtree_vram_info_header_v3_0* vi30 =
		&(atree->data_table.vram_info.v3_0);
	vi30->dot = vi30;
	vi30->dotdot = &(atree->data_table.vram_info);
	vi30->leaves = atree->bios +
		atree->data_table.leaves->vram_info;


	atui_branch* atui_mem_tuning = NULL;
	if (vi30->leaves->mem_tuning_table_offset) {
		vi30->mem_tuning = (void*)vi30->leaves +
			vi30->leaves->mem_tuning_table_offset;
	} else {
		vi30->mem_tuning = NULL;
	}


	atui_branch* atui_dram_info = NULL;
	if (vi30->leaves->dram_info_table_offset) {
		vi30->dram_info = (void*)vi30->leaves +
			vi30->leaves->dram_info_table_offset;
	} else {
		vi30->dram_info = NULL;
	}


	atui_branch* atui_tmrs_seq = NULL;
	if (vi30->leaves->tmrs_table_offset) {
		vi30->tmrs_seq = (void*)vi30->leaves + vi30->leaves->tmrs_table_offset;
	} else {
		vi30->tmrs_seq = NULL;
	}


	atui_branch* atui_mc_init = NULL;
	if (vi30->leaves->mc_init_table_offset) {
		vi30->mc_init.leaves = (void*)vi30->leaves +
			vi30->leaves->mc_init_table_offset;
		atui_mc_init = atomtree_populate_umc_init_reg_block(
			atree, &(vi30->mc_init), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_mc_init->name, "mc_init_table");
	} else {
		vi30->mc_init.leaves = NULL;
	}


	atui_branch* atui_dram_data_remap = NULL;
	if (vi30->leaves->dram_data_remap_table_offset) {
		vi30->dram_data_remap = (void*)vi30->leaves +
			vi30->leaves->dram_data_remap_table_offset;
	} else {
		vi30->dram_data_remap = NULL;
	}


	atui_branch* atui_umc_emuinit = NULL;
	if (vi30->leaves->umc_emuinit_table_offset) {
		vi30->umc_emuinit.leaves = (void*)vi30->leaves +
			vi30->leaves->umc_emuinit_table_offset;
		atui_umc_emuinit = atomtree_populate_umc_init_reg_block(
			atree, &(vi30->umc_emuinit), generate_atui, 0
		);
		if (generate_atui)
			sprintf(atui_umc_emuinit->name, "umc_emuinit_table");
	} else {
		vi30->umc_emuinit.leaves = NULL;
	}


	if (vi30->leaves->reserved_sub_table_offset[0]) {
		vi30->rsvd_tables[0] = (void*)vi30->leaves +
			vi30->leaves->reserved_sub_table_offset[0];
	} else {
		vi30->rsvd_tables[0] = NULL;
	}
	if (vi30->leaves->reserved_sub_table_offset[1]) {
		vi30->rsvd_tables[1] = (void*)vi30->leaves +
			vi30->leaves->reserved_sub_table_offset[1];
	} else {
		vi30->rsvd_tables[1] = NULL;
	}



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

	atui_branch* atui_vi = NULL;
	if(generate_atui) {
		const uint8_t num_vram_modules = (
			sizeof(vi30->leaves->vram_module)
			/ sizeof(struct atom_vram_module_v3_0)
		);
		atui_branch* vram_module = ATUI_MAKE_BRANCH(atui_nullstruct,
			NULL,NULL,  num_vram_modules,NULL
		);
		sprintf(vram_module->name, "atom_vram_module_v3.0");
		for(i=0; i < num_vram_modules; i++) {
			tmp_branch = ATUI_MAKE_BRANCH(atom_vram_module_v3_0,
				NULL,&(vi30->leaves->vram_module[i]),  0,NULL
			);
			sprintf(tmp_branch->name, "%s [%02u]", tmp_branch->varname, i);
			vram_module->child_branches[i] = tmp_branch;
		}
		vram_module->num_child_branches = i;

		atui_branch* vi30_children[] = {
			atui_mem_tuning, atui_dram_info, atui_tmrs_seq, atui_mc_init,
			atui_dram_data_remap, atui_umc_emuinit, vram_module
		};
		const uint8_t num_children = sizeof(vi30_children)/sizeof(atui_branch*);


		atui_vi = ATUI_MAKE_BRANCH(atom_vram_info_header_v3_0,
			vi30,vi30->leaves,  num_children,vi30_children
		);
	}
	return atui_vi;
}

inline static atui_branch* atomtree_dt_populate_vram_info(
		struct atom_tree* atree, bool generate_atui) {

	atui_branch* atui_vi = NULL;

	struct atomtree_vram_info* vram_info = &(atree->data_table.vram_info);
	vram_info->dot = vram_info;
	vram_info->dotdot = &(atree->data_table);

	if (atree->data_table.leaves->vram_info) {
		vram_info->table_header =
			atree->bios + atree->data_table.leaves->vram_info;
		vram_info->ver = get_ver(vram_info->table_header);
		switch (vram_info->ver) { // TODO: earlier tables than 2.3?
			case v2_3:
				atui_vi = atomtree_populate_vram_info_v2_3(atree,generate_atui);
				break;
			case v2_4:
				atui_vi = atomtree_populate_vram_info_v2_4(atree,generate_atui);
				break;
			case v2_5:
				atui_vi = atomtree_populate_vram_info_v2_5(atree,generate_atui);
				break;
			case v2_6:
				atui_vi = atomtree_populate_vram_info_v2_6(atree,generate_atui);
				break;
			case v3_0:
				atui_vi = atomtree_populate_vram_info_v3_0(atree,generate_atui);
				break;
			default:
				if (generate_atui) {
					atui_vi = ATUI_MAKE_BRANCH(atom_common_table_header,
						NULL,vram_info->table_header,  0,NULL
					);
					sprintf(atui_vi->name, "vram_info (header only stub)");
				}
				break;
		}
	} else {
		vram_info->leaves = NULL;
		vram_info->ver = nover;
	}
	return atui_vi;
}


inline static atui_branch* atomtree_dt_populate_voltageobject_info_v4_1(
		struct atom_tree* atree, bool generate_atui) {

	atui_branch* atui_vo_info = NULL;
	atui_branch* tmp_branch = NULL;
	uint16_t i;

	struct atomtree_voltageobject_info_v4_1* vo41 =
	&(atree->data_table.voltageobject_info.v4_1);
	vo41->dot = vo41;
	vo41->dotdot = &(atree->data_table.voltageobject_info);
	vo41->leaves = atree->bios + atree->data_table.leaves->voltageobject_info;


	// get the size ofthe dynamically-sized voltage object array, and walk
	// through the array based on what each element reports their size as.
	union atom_voltage_object_v4* vobj;
	uint16_t offset = 0;
	uint16_t vo41_array_size = (
		vo41->leaves->table_header.structuresize
		- offsetof(struct atom_voltage_objects_info_v4_1, voltage_object[0])
	);
	void* start = &(vo41->leaves->voltage_object[0]);
	i = 0;
	while(offset < vo41_array_size) {
		vobj = start + offset;

		vo41->voltage_objects[i].voltage_object = vobj;
		switch(vobj->header.voltage_mode) {
			// some voltage objects have a dynamically-sized lookup table.
			case VOLTAGE_OBJ_GPIO_LUT:
			case VOLTAGE_OBJ_PHASE_LUT:
				vo41->voltage_objects[i].lut_entries = (
					(vobj->header.object_size - offsetof(
						struct atom_gpio_voltage_object_v4, voltage_gpio_lut[0]
					)) / sizeof(struct atom_voltage_gpio_map_lut)
				);
				break;
			case VOLTAGE_OBJ_VR_I2C_INIT_SEQ:
				vo41->voltage_objects[i].lut_entries = (
					(vobj->header.object_size - offsetof(
						struct atom_i2c_voltage_object_v4, i2cdatalut[0]
					)) / sizeof(struct atom_i2c_data_entry)
				);
				break;
			default:
				vo41->voltage_objects[i].lut_entries = 0;
				break;
		}

		offset += vobj->header.object_size;
		i++;
	}
	vo41->num_voltage_objects = i;
	// TODO bounds checks for i and array size

	struct atomtree_voltage_object_v4* at_vobj;
	if (generate_atui) {
		atui_vo_info = ATUI_MAKE_BRANCH(atom_common_table_header,
			NULL,vo41->leaves,  vo41->num_voltage_objects,NULL
		);
		sprintf(atui_vo_info->name, "atom_voltage_objects_info_v4_1");
		for(i=0; i < vo41->num_voltage_objects; i++) {
			at_vobj = &(vo41->voltage_objects[i]);
			switch(at_vobj->voltage_object->header.voltage_mode) {
				case VOLTAGE_OBJ_GPIO_LUT:
				case VOLTAGE_OBJ_PHASE_LUT:
					tmp_branch = ATUI_MAKE_BRANCH(atom_gpio_voltage_object_v4,
						at_vobj, &(at_vobj->voltage_object->gpio_voltage_obj),
						0, NULL
					);
					break;
				case VOLTAGE_OBJ_VR_I2C_INIT_SEQ:
					tmp_branch = ATUI_MAKE_BRANCH(atom_i2c_voltage_object_v4,
						at_vobj, &(at_vobj->voltage_object->i2c_voltage_obj),
						0, NULL
					);
					break;
				case VOLTAGE_OBJ_SVID2:
					tmp_branch = ATUI_MAKE_BRANCH(atom_svid2_voltage_object_v4,
						at_vobj, &(at_vobj->voltage_object->svid2_voltage_obj),
						0, NULL
					);
					break;
				case VOLTAGE_OBJ_MERGED_POWER:
					tmp_branch = ATUI_MAKE_BRANCH(atom_merged_voltage_object_v4,
						at_vobj, &(at_vobj->voltage_object->merged_voltage_obj),
						0, NULL
					);
					break;
				case VOLTAGE_OBJ_EVV: // TODO does this get used by v4?
				default:
					tmp_branch = ATUI_MAKE_BRANCH(atom_voltage_object_header_v4,
						at_vobj,&(at_vobj->voltage_object->header),  0,NULL
					);
					break;
			}
			sprintf(tmp_branch->name,  "%s [%u]", tmp_branch->varname, i);
			atui_vo_info->child_branches[i] = tmp_branch;
		}
		atui_vo_info->num_child_branches = vo41->num_voltage_objects;
	}
	return atui_vo_info;
}


inline static atui_branch* atomtree_dt_populate_voltageobject_info(
		struct atom_tree* atree, bool generate_atui) {

	atui_branch* atui_vo_info = NULL;

	struct atomtree_voltageobject_info* vo_info =
		&(atree->data_table.voltageobject_info);
	vo_info->dot = vo_info;
	vo_info->dotdot = &(atree->data_table);

	if (atree->data_table.leaves->voltageobject_info) {
		vo_info->table_header =
			atree->bios + atree->data_table.leaves->voltageobject_info;
		vo_info->ver = get_ver(vo_info->table_header);
		switch (vo_info->ver) {
			case v4_1:
				atui_vo_info = atomtree_dt_populate_voltageobject_info_v4_1(
					atree, generate_atui
				);
				break;
			case v4_2: //hopefully v4_2 is the same
				atui_vo_info = atomtree_dt_populate_voltageobject_info_v4_1(
					atree, generate_atui
				);
				sprintf(atui_vo_info->name,
					"atom_voltage_objects_info_v4_1 (forced)");
				break;
			default:
				if (generate_atui) {
					atui_vo_info = ATUI_MAKE_BRANCH(atom_common_table_header,
						NULL,vo_info->table_header,  0,NULL
					);
					sprintf(atui_vo_info->name,
						"voltageobject_info (header only stub)"
					);
				}
				break;
		}
	} else {
		vo_info->ver = nover;
		vo_info->leaves = NULL;
	}
	return atui_vo_info;
}

inline static atui_branch* atomtree_dt_populate_sw_datatables(
		struct atom_tree* atree, bool generate_atui) {

	struct atomtree_master_datatable_v2_1* data_table = &(atree->data_table);
	struct atom_master_data_table_v2_1* leaves = data_table->leaves;
	void* bios = atree->bios;

	data_table->sw_datatable3.leaves = NULL;
	if (leaves->sw_datatable3)
		data_table->sw_datatable3.leaves = bios + leaves->sw_datatable3;

	data_table->sw_datatable5.leaves = NULL;
	if (leaves->sw_datatable5)
		data_table->sw_datatable5.leaves = bios + leaves->sw_datatable5;

	data_table->sw_datatable7.leaves = NULL;
	if (leaves->sw_datatable7)
		data_table->sw_datatable7.leaves = bios + leaves->sw_datatable7;

	data_table->sw_datatable9.leaves = NULL;
	if (leaves->sw_datatable9)
		data_table->sw_datatable9.leaves = bios + leaves->sw_datatable9;

	data_table->sw_datatable10.leaves = NULL;
	if (leaves->sw_datatable10)
		data_table->sw_datatable10.leaves = bios + leaves->sw_datatable10;

	data_table->sw_datatable13.leaves = NULL;
	if (leaves->sw_datatable13)
		data_table->sw_datatable13.leaves = bios + leaves->sw_datatable13;

	data_table->sw_datatable16.leaves = NULL;
	if (leaves->sw_datatable16)
		data_table->sw_datatable16.leaves = bios + leaves->sw_datatable16;

	data_table->sw_datatable17.leaves = NULL;
	if (leaves->sw_datatable17)
		data_table->sw_datatable17.leaves = bios + leaves->sw_datatable17;

	data_table->sw_datatable18.leaves = NULL;
	if (leaves->sw_datatable18)
		data_table->sw_datatable18.leaves = bios + leaves->sw_datatable18;

	data_table->sw_datatable19.leaves = NULL;
	if (leaves->sw_datatable19)
		data_table->sw_datatable19.leaves = bios + leaves->sw_datatable19;

	data_table->sw_datatable20.leaves = NULL;
	if (leaves->sw_datatable20)
		data_table->sw_datatable20.leaves = bios + leaves->sw_datatable20;

	data_table->sw_datatable21.leaves = NULL;
	if (leaves->sw_datatable21)
		data_table->sw_datatable21.leaves = bios + leaves->sw_datatable21;

	data_table->sw_datatable25.leaves = NULL;
	if (leaves->sw_datatable25)
		data_table->sw_datatable25.leaves = bios + leaves->sw_datatable25;

	data_table->sw_datatable26.leaves = NULL;
	if (leaves->sw_datatable26)
		data_table->sw_datatable26.leaves = bios + leaves->sw_datatable26;

	data_table->sw_datatable29.leaves = NULL;
	if (leaves->sw_datatable29)
		data_table->sw_datatable29.leaves = bios + leaves->sw_datatable29;

	data_table->sw_datatable33.leaves = NULL;
	if (leaves->sw_datatable33)
		data_table->sw_datatable33.leaves = bios + leaves->sw_datatable33;

	data_table->sw_datatable34.leaves = NULL;
	if (leaves->sw_datatable34)
		data_table->sw_datatable34.leaves = bios + leaves->sw_datatable34;


	return NULL; // TODO unsure about what UI to do here
}

inline static atui_branch* atomtree_populate_datatables(
		struct atom_tree* atree, bool generate_atui) {
	//TODO double check pointer math if possible; some tables might be relative
	// to master_datatable.

	struct atomtree_master_datatable_v2_1* data_table = &(atree->data_table);
	struct atom_master_data_table_v2_1* leaves;
	void* bios = atree->bios;
	data_table->dot = data_table;
	data_table->dotdot = atree;
	data_table->leaves = bios + atree->leaves->masterdatatable_offset;
	data_table->ver = get_ver(data_table->table_header);
	leaves = data_table->leaves;


	atui_branch* atui_utilitypipeline = NULL;
	if (leaves->utilitypipeline) {
		data_table->utilitypipeline = bios + leaves->utilitypipeline;
	} else {
		data_table->utilitypipeline = NULL;
	}


	atui_branch* atui_multimedia_info = NULL;
	if (leaves->multimedia_info) {
		data_table->multimedia_info = bios + leaves->multimedia_info;
	} else {
		data_table->multimedia_info = NULL;
	}


	atui_branch* atui_smc_dpm_info =
		atomtree_dt_populate_smc_dpm_info(atree, generate_atui);

	atui_branch* atui_firmwareinfo =
		atomtree_dt_populate_firmwareinfo(atree, generate_atui);


	atui_branch* atui_lcd_info =
		atomtree_dt_populate_lcd_info(atree, generate_atui);


	atui_branch* atui_smu_info =
		atomtree_dt_populate_smu_info(atree, generate_atui);

	atui_branch* atui_fw_vram =
		atomtree_dt_populate_vram_usagebyfirmware(atree, generate_atui);


	atui_branch* atui_gpio_pin_lut =
		atomtree_dt_populate_gpio_pin_lut(atree, generate_atui);


	atui_branch* atui_gfx_info =
		atomtree_dt_populate_gfx_info(atree, generate_atui);

	atui_branch* atui_ppt = atomtree_dt_populate_ppt(atree, generate_atui);

	//displayobjectinfo
	//indirectioaccess
	//umc_info
	//dce_info

	atui_branch* atui_vram_info =
		atomtree_dt_populate_vram_info(atree, generate_atui);

	//integratedsysteminfo
	//asic_profiling_info
	//voltageobject_info
	atui_branch* atui_voltageobject_info =
		atomtree_dt_populate_voltageobject_info(atree, generate_atui);

	atomtree_dt_populate_sw_datatables(atree, generate_atui);


	atui_branch* atui_dt = NULL;
	if (generate_atui) {
		atui_branch* child_branches[] = {
			// utility, multimedia
			atui_smc_dpm_info, atui_firmwareinfo, atui_lcd_info, atui_smu_info,
			atui_fw_vram, atui_gpio_pin_lut, atui_gfx_info, atui_ppt,
			// disp obj, indirect, umc, dce,
			atui_vram_info,
			// integrated, asic
			atui_voltageobject_info
		};
		const uint8_t num_child_branches = (
			sizeof(child_branches) / sizeof(atui_branch*)
		);

		atui_dt = ATUI_MAKE_BRANCH(atom_master_data_table_v2_1,
			data_table,data_table->leaves,  num_child_branches,child_branches
		);
	}
	return atui_dt;
}

void atomtree_bios_checksum(struct atom_tree* atree) {
	uint8_t* bios = atree->bios;
	uint32_t bios_size = atree->bios_image_size;
	uint8_t offset = 0;

	for (uint32_t i=0; i < bios_size; i++)
		offset += bios[i];

	if (offset) // this test is unnecessary
		atree->image->checksum -= offset;
}




inline static void* bios_fastforward(void* biosfile, const uint32_t size) {
	const struct atombios_image* image;
	const void* end = biosfile + size;
	while(biosfile < end) {
		image = biosfile;
		//TODO is anyone bothering to check all the magic signs?
		if ((image->atombios_magic == ATOM_BIOS_MAGIC)
			&& (0 == strcmp(ATOM_ATI_MAGIC, image->atomati_magic))
			) {
			return biosfile;
		}
		biosfile++;
	}
	return NULL;
}

struct atom_tree* atombios_parse(
		void* alloced_bios, uint32_t allocsize, bool generate_atui) {

	void* bios = bios_fastforward(alloced_bios, allocsize);
	if (bios == NULL)
		return NULL;

	struct atombios_image* image = bios;

	struct atom_tree* atree = malloc(sizeof(struct atom_tree));

	atree->dot = atree;
	atree->dotdot = NULL;

	atree->biosfile = NULL;
	atree->biosfile_size = 0;
	atree->alloced_bios = alloced_bios;

	atree->bios = bios; //PIC code; going to be used as the '0' in places.
	atree->leaves = bios + image->bios_header;

	atree->bios_image_size = image->image_size * BIOS_IMAGE_SIZE_UNIT;

	atui_branch* atui_dt = atomtree_populate_datatables(atree, generate_atui);
	// atomtree_populate_commandtables(atree); // TODO

	atree->protected_mode = bios + atree->leaves->protectedmodeoffset;
	atree->config_filename = bios + atree->leaves->configfilenameoffset;

	atree->crc_block = bios + atree->leaves->crc_block_offset;
	/* TODO what are these locations?
	uint32_t crc = *(atree->crc_block);
	zlib's crc32(0, startptr, bytes);
	see also the sratch/crc.c brute-forcing tool


	It doesn't seem that the crc_block has any importance for official release
	since many most have a programmed CRC mismatch.

	has crc match:
		6950XT.16384.220310.rom:
			address: +0x3882 ~ +0x5AE5 for 8803 bytes
			crc: 0x98174286 0x98174286

		AMD.RX480.8192.160603_1.rom:
			address: +0x14D7 ~ +0x3866 for 9103 bytes
			crc: 0x7F5E715 0x7F5E715

	doesn't have it:
		AMD.RXVega64.8192.170320.rom
		AMD.RX5700.8192.190616.rom
		Powercolor.RX6650XT.8192.220303.rom
		ASRock.RX7900XTX.24576.221128_1.rom + 262144
		AMD.RadeonPro.5600M.rom
		Sapphire.RX6800XT.16384.211230.rom
		Sapphire.RX580.8192.170320.rom
		AMD.RX5500XT.8192.191017.rom
		AMD.RX590.8192.191126.rom
		AMD.RX6700XT.12288.210125.rom
		AMD.RXVega56.8176.170730.rom
		AMD.RX6900XT.16384.210108.rom
		AMD.RX5700XT.8192.190616_1.rom
	*/


	atree->bootup_mesage = bios + atree->leaves->vbios_bootupmessageoffset;
	atree->int10 = bios + atree->leaves->int10_offset;
	// any more between?
	atree->psp_dir_table = bios + atree->leaves->pspdirtableoffset;


	if (generate_atui) {
		atui_branch* child_branches[] = {atui_dt};
		const uint8_t num_child_branches = (
			sizeof(child_branches) / sizeof(atui_branch*)
		);

		atree->atui_root = ATUI_MAKE_BRANCH(atom_rom_header_v2_2,
			atree,atree->leaves,  num_child_branches,child_branches
		);
	} else {
		atree->atui_root = NULL;
	}

	return atree;
}


inline enum atomtree_common_version get_ver(
		struct atom_common_table_header* header) {
	return (header->format_revision * 100) + header->content_revision;
}
inline void set_ver(
		enum atomtree_common_version ver,
		struct atom_common_table_header* header) {
	header->format_revision = ver / 100;
	header->content_revision = ver % 100;
};
