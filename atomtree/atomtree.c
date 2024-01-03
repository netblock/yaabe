/* For atomtree's abstract, check out atomtree_data_tables.h */

#include "atomtree.h"
#include "atui.h"

// TODO take advantage of ATUI_PETIOLE as much as possible

inline static atui_branch*
atomtree_dt_populate_smc_dpm_info(
		struct atomtree_smc_dpm_info* smc_dpm_info,
		struct atom_tree* atree,
		uint16_t bios_offset,
		bool generate_atui
		) {
	atui_branch* atui_smc_dpm_info = NULL;
	atui_branch* atui_smudpm_i2c = NULL;
	uint16_t i = 0;

	if (bios_offset) {
		// leaves is in a union with the structs.
		smc_dpm_info->leaves = atree->bios + bios_offset;
		smc_dpm_info->ver = get_ver(smc_dpm_info->table_header);
		if (generate_atui) {
			switch (smc_dpm_info->ver) {
				case v4_1:
					atui_smc_dpm_info = ATUI_MAKE_BRANCH(atom_smc_dpm_info_v4_1,
						NULL,  NULL,smc_dpm_info->v4_1, 0,NULL
					);
					break;
				/*
				case v4_2:
					break;
				*/
				case v4_3:
					atui_smc_dpm_info = ATUI_MAKE_BRANCH(atom_smc_dpm_info_v4_3,
						NULL,  NULL,smc_dpm_info->v4_3, 0,NULL
					);
					break;
				case v4_4:
					atui_smc_dpm_info = ATUI_MAKE_BRANCH(atom_smc_dpm_info_v4_4,
						NULL,  NULL,smc_dpm_info->v4_4,  0,NULL
					);
					break;
				case v4_5:
					atui_smc_dpm_info = ATUI_MAKE_BRANCH(atom_smc_dpm_info_v4_5,
						NULL,  NULL,smc_dpm_info->v4_5,  0,NULL
					);
					break;
				case v4_6:
					atui_smc_dpm_info = ATUI_MAKE_BRANCH(atom_smc_dpm_info_v4_6,
						NULL,  NULL,smc_dpm_info->v4_6,  0,NULL
					);
					break;
				case v4_7:
					atui_smc_dpm_info = ATUI_MAKE_BRANCH(atom_smc_dpm_info_v4_7,
						NULL,  NULL,smc_dpm_info->v4_7,  0,NULL
					);
					break;
				case v4_9:
					atui_smc_dpm_info = ATUI_MAKE_BRANCH(atom_smc_dpm_info_v4_9,
						NULL,  NULL,smc_dpm_info->v4_9,  0,NULL
					);
					break;
				case v4_10:
					atui_smc_dpm_info = ATUI_MAKE_BRANCH(
						atom_smc_dpm_info_v4_10,
						NULL,  NULL,smc_dpm_info->v4_10,  0,NULL
					);
					break;
				case v5_0:
					atui_smc_dpm_info = ATUI_MAKE_BRANCH(
						atom_smc_dpm_info_table_13_0_7,
						NULL,  NULL,smc_dpm_info->v5_0,  0,NULL
					);
					break;
				default:
					atui_smc_dpm_info = ATUI_MAKE_BRANCH(
						atom_common_table_header,
						"smc_dpm_info (header only stub)",
						NULL, smc_dpm_info->table_header,  0,NULL
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


inline static atui_branch*
atomtree_dt_populate_firmwareinfo(
		struct atomtree_firmware_info* firmwareinfo,
		struct atom_tree* atree,
		uint16_t bios_offset,
		bool generate_atui
		) {
	atui_branch* atui_firmwareinfo = NULL;

	if (bios_offset) {
		// leaves is in a union with the structs.
		firmwareinfo->leaves = atree->bios + bios_offset;
		firmwareinfo->ver = get_ver(firmwareinfo->table_header);
		if (generate_atui) {
			switch (firmwareinfo->ver) {
				case v1_0:
					atui_firmwareinfo = ATUI_MAKE_BRANCH(
						atom_firmware_info_v1_0,  NULL,
						NULL,firmwareinfo->v1_0,  0,NULL
					);
					break;
				case v1_2:
					atui_firmwareinfo = ATUI_MAKE_BRANCH(
						atom_firmware_info_v1_2,  NULL,
						NULL,firmwareinfo->v1_2,  0,NULL
					);
					break;
				case v1_3:
					atui_firmwareinfo = ATUI_MAKE_BRANCH(
						atom_firmware_info_v1_3,  NULL,
						NULL,firmwareinfo->v1_3,  0,NULL
					);
					break;
				case v1_4:
					atui_firmwareinfo = ATUI_MAKE_BRANCH(
						atom_firmware_info_v1_4,  NULL,
						NULL,firmwareinfo->v1_4,  0,NULL
					);
					break;
				case v2_1:
					atui_firmwareinfo = ATUI_MAKE_BRANCH(
						atom_firmware_info_v2_1,  NULL,
						NULL,firmwareinfo->v2_1,  0,NULL
					);
					break;
				case v2_2:
					atui_firmwareinfo = ATUI_MAKE_BRANCH(
						atom_firmware_info_v2_2,  NULL,
						NULL,firmwareinfo->v2_2,  0,NULL
					);
					break;
				case v3_1:
					atui_firmwareinfo = ATUI_MAKE_BRANCH(
						atom_firmware_info_v3_1,  NULL,
						NULL,firmwareinfo->v3_1,  0,NULL
					);
					break;
				case v3_2:
					atui_firmwareinfo = ATUI_MAKE_BRANCH(
						atom_firmware_info_v3_2,  NULL,
						NULL,firmwareinfo->v3_2,  0,NULL
					);
					break;
				case v3_3:
					atui_firmwareinfo = ATUI_MAKE_BRANCH(
						atom_firmware_info_v3_3,  NULL,
						NULL,firmwareinfo->v3_3,  0,NULL
					);
					break;
				case v3_4:
					atui_firmwareinfo = ATUI_MAKE_BRANCH(
						atom_firmware_info_v3_4,  NULL,
						NULL,firmwareinfo->v3_4,  0,NULL
					);
					break;
				default:
					atui_firmwareinfo = ATUI_MAKE_BRANCH(
						atom_common_table_header,
						"firmwareinfo (header only stub)",
						NULL,firmwareinfo->table_header,  0,NULL
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


inline static atui_branch*
atomtree_dt_populate_lcd_info(
		struct atomtree_lcd_info* lcd_info,
		struct atom_tree* atree,
		uint16_t bios_offset,
		bool generate_atui
		) {
	atui_branch* atui_lcd_info = NULL;
	atui_branch* atui_lcd_timing = NULL;

	if (bios_offset) {
		lcd_info->leaves = atree->bios + bios_offset;
		lcd_info->ver = get_ver(lcd_info->table_header);
		if (generate_atui) {
			switch (lcd_info->ver) {
				/*case v1_3: TODO from atombios.h */
				case v2_1:
					atui_lcd_info = ATUI_MAKE_BRANCH(atom_lcd_info_v2_1,
						NULL,  NULL,lcd_info->leaves,  0,NULL
					);
					break;
				default:
					atui_lcd_info = ATUI_MAKE_BRANCH(
						atom_common_table_header,
						"lcd_info (header only stub)",
						NULL,lcd_info->table_header,  0,NULL
					);
					break;
			}
		}
	} else {
		lcd_info->leaves = NULL;
		lcd_info->ver = nover;
	}

	return atui_lcd_info;
}


inline static atui_branch*
atomtree_dt_populate_smu_info(
		struct atomtree_smu_info* smu_info,
		struct atom_tree* atree,
		uint16_t bios_offset,
		bool generate_atui
		) {
	atui_branch* atui_smu_info = NULL;

	smu_info->smugolden = NULL;
	smu_info->smuinit = NULL;

	// leaves is in a union with the structs.
	if (bios_offset) {
		smu_info->leaves = atree->bios + bios_offset;
		smu_info->ver = get_ver(smu_info->table_header);
		switch (smu_info->ver) { // TODO if init,golden are 0, catch them.
			case v3_1:
				if (generate_atui) {
					atui_smu_info = ATUI_MAKE_BRANCH(atom_smu_info_v3_1,
						NULL,  NULL,smu_info->v3_1,  0,NULL
					);
				}
				break;
			case v3_2:
				if (generate_atui) {
					atui_smu_info = ATUI_MAKE_BRANCH(atom_smu_info_v3_2,
						NULL,  NULL,smu_info->v3_2,  0,NULL
					);
				}
				if (smu_info->v3_2->smugoldenoffset) {
					smu_info->smugolden =
						smu_info->leaves + smu_info->v3_2->smugoldenoffset;
				}
				break;
			case v3_3:
				if (generate_atui) {
					atui_smu_info = ATUI_MAKE_BRANCH(atom_smu_info_v3_3,
						NULL,  NULL,smu_info->v3_3,  0,NULL
					);
				}
				if (smu_info->v3_3->smugoldenoffset) {
					smu_info->smugolden =
						smu_info->leaves + smu_info->v3_3->smugoldenoffset;
				}
				if (smu_info->v3_3->smuinitoffset) {
					smu_info->smuinit =
						smu_info->leaves + smu_info->v3_3->smuinitoffset;
				}
				break;
			case v3_4: // bios reports 244 bytes. v3_5 is 240 bytes.
			case v3_5:
				if (generate_atui) {
					atui_smu_info = ATUI_MAKE_BRANCH(atom_smu_info_v3_5,
						NULL,  NULL,smu_info->v3_5,  0,NULL
					);
					if (smu_info->ver == v3_4) {
						sprintf(atui_smu_info->name, "%s (forced)",
							atui_smu_info->varname
						);
					}
				}
				if (smu_info->v3_5->smugoldenoffset) {
					smu_info->smugolden =
						smu_info->leaves + smu_info->v3_5->smugoldenoffset;
				}
				if (smu_info->v3_5->smuinitoffset) {
					smu_info->smuinit =
						smu_info->leaves + smu_info->v3_5->smuinitoffset;
				}
				break;
			case v3_6:
				if (generate_atui) {
					atui_smu_info = ATUI_MAKE_BRANCH(atom_smu_info_v3_6,
						NULL,  NULL,smu_info->v3_6,  0,NULL
					);
				}
				if (smu_info->v3_6->smugoldenoffset) {
					smu_info->smugolden =
						smu_info->leaves + smu_info->v3_6->smugoldenoffset;
				}
				if (smu_info->v3_6->smuinitoffset) {
					smu_info->smuinit =
						smu_info->leaves + smu_info->v3_6->smuinitoffset;
				}
				break;
			case v4_0:
				if (generate_atui) {
					atui_smu_info = ATUI_MAKE_BRANCH(atom_smu_info_v4_0,
						NULL,  NULL,smu_info->v4_0,  0,NULL
					);
				}
				if (smu_info->v4_0->smuinitoffset) {
					smu_info->smuinit =
						smu_info->leaves + smu_info->v4_0->smuinitoffset;
				}
				break;
			default:
				if (generate_atui) {
					atui_smu_info = ATUI_MAKE_BRANCH(atom_common_table_header,
						"smu_info (header only stub)",
						NULL,smu_info->table_header,  0,NULL
					);
				}
				break;
		}
	} else {
		smu_info->leaves = NULL;
		 smu_info->ver = nover;
	}
	return atui_smu_info;
}


inline static atui_branch*
atomtree_dt_populate_vram_usagebyfirmware(
		struct atomtree_vram_usagebyfirmware* fw_vram,
		struct atom_tree* atree,
		uint16_t bios_offset,
		bool generate_atui) {

	atui_branch* atui_fw_vram = NULL;

	if (bios_offset) {
		// leaves is in a union with the structs.
		fw_vram->leaves = atree->bios + bios_offset;
		fw_vram->ver = get_ver(fw_vram->table_header);
		if (generate_atui) {
			switch(fw_vram->ver) {
				case v2_1:
					atui_fw_vram = ATUI_MAKE_BRANCH(vram_usagebyfirmware_v2_1,
						NULL,  NULL,fw_vram->v2_1,  0,NULL
					);
					break;
				case v2_2:
					atui_fw_vram = ATUI_MAKE_BRANCH(vram_usagebyfirmware_v2_2,
						NULL,  NULL,fw_vram->v2_2,  0,NULL
					);
					break;
				default:
					atui_fw_vram = ATUI_MAKE_BRANCH(atom_common_table_header,
						"vram_usagebyfirmware (header only stub)",
						NULL,fw_vram->table_header,  0,NULL
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


inline static atui_branch*
atomtree_dt_populate_gpio_pin_lut(
		struct atomtree_gpio_pin_lut* gpio_pin_lut,
		struct atom_tree* atree,
		uint16_t bios_offset,
		bool generate_atui
		) {
	atui_branch* atui_gpio_pin_lut = NULL;
	atui_branch* atui_gpio_pin = NULL;
	uint16_t i;

	if (bios_offset) {
		gpio_pin_lut->leaves = atree->bios + bios_offset;
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
					atui_gpio_pin_lut = ATUI_MAKE_BRANCH(atom_gpio_pin_lut_v2_1,
						NULL,  gpio_pin_lut,gpio_pin_lut->v2_1,  0,NULL
					);
				}
				break;
			default:
				gpio_pin_lut->num_gpio_pins = 0;
				if (generate_atui) {
					atui_gpio_pin_lut = ATUI_MAKE_BRANCH(
						atom_common_table_header,
						"gpio_pin_lut (header only stub)",
						NULL,gpio_pin_lut->table_header,  0,NULL
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


inline static atui_branch*
atomtree_dt_populate_gfx_info(
		struct atomtree_gfx_info* gfx_info,
		struct atom_tree* atree,
		uint16_t bios_offset,
		bool generate_atui
		) {
	atui_branch* atui_gfx_info = NULL;

	gfx_info->gcgolden = NULL;

	if (bios_offset) {
		// leaves is in a union with the structs.
		gfx_info->leaves = atree->bios + bios_offset;
		gfx_info->ver = get_ver(gfx_info->table_header);
		switch(gfx_info->ver) {
			case v2_2:
				if (generate_atui) {
					atui_gfx_info = ATUI_MAKE_BRANCH(atom_gfx_info_v2_2,
						NULL,  NULL,gfx_info->v2_2,  0,NULL
					);
				}
				break;
			case v2_3:
				if (gfx_info->v2_3->gcgoldenoffset) {
					gfx_info->gcgolden =
						gfx_info->leaves + gfx_info->v2_3->gcgoldenoffset;
				}
				if (generate_atui) {
					atui_gfx_info = ATUI_MAKE_BRANCH(atom_gfx_info_v2_3,
						NULL,  NULL,gfx_info->v2_3,  0,NULL
					);
				}
				break;
			case v2_4:
				if (gfx_info->v2_4->gcgoldenoffset) {
					gfx_info->gcgolden =
						gfx_info->leaves + gfx_info->v2_4->gcgoldenoffset;
				}
				if (generate_atui) {
					atui_gfx_info = ATUI_MAKE_BRANCH(atom_gfx_info_v2_4,
						NULL,  NULL,gfx_info->v2_4,  0,NULL
					);
				}
				break;
			case v2_5:
				if (gfx_info->v2_5->gcgoldenoffset) {
					gfx_info->gcgolden =
						gfx_info->leaves + gfx_info->v2_5->gcgoldenoffset;
				}
				if (generate_atui) {
					atui_gfx_info = ATUI_MAKE_BRANCH(atom_gfx_info_v2_5,
						NULL,  NULL,gfx_info->v2_5,  0,NULL
					);
				}
				break;
			case v2_6: // force v2.5
				if (gfx_info->v2_6->gcgoldenoffset) {
					gfx_info->gcgolden =
						gfx_info->leaves + gfx_info->v2_6->gcgoldenoffset;
				}
				if (generate_atui) {
					atui_gfx_info = ATUI_MAKE_BRANCH(atom_gfx_info_v2_5,
						"atom_gfx_info_v2_5 (forced)",
						NULL,gfx_info->v2_6,  0,NULL
					);
				}
				break;
			case v2_7:
				if (gfx_info->v2_7->gcgoldenoffset) {
					gfx_info->gcgolden =
						gfx_info->leaves + gfx_info->v2_7->gcgoldenoffset;
				}
				if (generate_atui) {
					atui_gfx_info = ATUI_MAKE_BRANCH(atom_gfx_info_v2_7,
						NULL,  NULL,gfx_info->v2_7,  0,NULL
					);
				}
				break;
			case v3_0:
				if (generate_atui) {
					atui_gfx_info = ATUI_MAKE_BRANCH(atom_gfx_info_v3_0,
						NULL,  NULL,gfx_info->v3_0,  0,NULL
					);
				}
				break;
			default:
				if (generate_atui) {
					atui_gfx_info = ATUI_MAKE_BRANCH(atom_common_table_header,
						"gfx_info (header only stub)",
						NULL,gfx_info->table_header,  0,NULL
					);
				}
				break;
		}
	} else {
		gfx_info->leaves = NULL;
		gfx_info->ver = nover;
	}
	return atui_gfx_info;
}


inline static atui_branch*
atomtree_dt_populate_ppt(
		struct atomtree_powerplaytable* ppt,
		struct atom_tree* atree,
		uint16_t bios_offset,
		bool generate_atui
		) {
	atui_branch* atui_ppt = NULL;
	atui_branch* atui_smc_pptable = NULL;

	if (bios_offset) {
		ppt->leaves = atree->bios + bios_offset;
		ppt->powerplay_table_ver = &(ppt->pphead->table_revision);
		// leaves is in a union with the structs.
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
							atui_smc_pptable = ATUI_MAKE_BRANCH(
								smu11_smcpptable_v3,
								NULL,  NULL,&(ppt->v12_0->smc_pptable),  0,NULL
							);
							break;
						default:
						case 8:
							atui_smc_pptable = ATUI_MAKE_BRANCH(
								smu11_smcpptable_v8,
								NULL,  NULL,&(ppt->v12_0->smc_pptable),  0,NULL
							);
							break;
					}
					atui_ppt = ATUI_MAKE_BRANCH(smu_11_0_powerplay_table,
						NULL,  NULL,ppt->v12_0,  1,&atui_smc_pptable
					);
				}
				break;

			case v18_0: // navi2 xx50
			case v16_0: // 6700XT
			case v15_0:
				ppt->smc_pptable_ver = &(
					ppt->v15_0->smc_pptable.smc_pptable_ver
				);
				if (generate_atui) {
					atui_smc_pptable = ATUI_MAKE_BRANCH(smu11_smcpptable_v7,
						NULL,  NULL,&(ppt->v15_0->smc_pptable),  0,NULL
					);
					atui_ppt = ATUI_MAKE_BRANCH(smu_11_0_7_powerplay_table,
						NULL,  NULL,ppt->v15_0,  1,&atui_smc_pptable
					);
				};
				break;
			default:
				if (generate_atui) {
					atui_ppt = ATUI_MAKE_BRANCH(smu_powerplay_table_header,
						"smu_powerplay_table_header (header only stub)",
						NULL,ppt->leaves,  0,NULL
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


static atui_branch*
atomtree_populate_umc_init_reg_block(
		struct atomtree_umc_init_reg_block* at_regblock,
		bool generate_atui,
		uint8_t num_extra_atuibranches
		) {
	// TODO: something something end is 0xFFFF ???

	// regblock->leaves must be already populated.
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
	uint16_t i = 0;

	at_regblock->umc_reg_list = at_regblock->leaves->umc_reg_list;
	at_regblock->umc_number_of_registers = &(at_regblock->leaves->umc_reg_num);
	const uint16_t umc_reg_list_size = (
		sizeof(union atom_umc_register_addr_info_access)
		* (*at_regblock->umc_number_of_registers)
	);

	// regsettingblock_starting_point is umc_reg_setting_list[0]
	void* const regsettingblock_starting_point = (
		(void*)at_regblock->leaves
		+ sizeof(struct atom_umc_init_reg_block_header)
		+ umc_reg_list_size
	);

	// the -1 is from the data_block struct already having the first element,
	// the "u32umc_reg_data[1]".
	const uint16_t regsetting_elementsize = (
		sizeof(struct atom_umc_reg_setting_data_block)
		+ ((*at_regblock->umc_number_of_registers-1) * sizeof(uint32_t))
	);
	at_regblock->umc_reg_setting_list_element_size = regsetting_elementsize;

	struct atom_umc_reg_setting_data_block* loc;
	for (i=0; i < *at_regblock->umc_number_of_registers ; i++) {
		loc = regsettingblock_starting_point + regsetting_elementsize*i;
		if (loc->block_id.u32umc_id_access == 0) {
			break; // AtomBIOS ends the datablock list with 0-fill.
		}
		assert(ATOMTREE_UMC_REG_MAX > i);
		at_regblock->umc_reg_setting_list[i] = loc;
	}
	at_regblock->umc_reg_setting_list_length = i;

	atui_branch* atui_regblock = NULL;
	if (generate_atui) {
		atui_regblock = ATUI_MAKE_BRANCH(atom_umc_init_reg_block,
			NULL,  at_regblock, at_regblock->leaves,
			num_extra_atuibranches, NULL
		);
	}
	return atui_regblock;
}


inline static void
atomtree_populate_atom_memory_timing_format_v0(
		atui_branch* parent,
		enum atom_dgpu_vram_type memory_type,
		struct atom_memory_timing_format_v0* format_v0_array,
		uint8_t count
		) {
	uint8_t i;
	atui_branch* atui_formattimings;
	atui_branch* atui_mrs[3] = {NULL};

	for (i=0; i < count; i++) {
		switch (memory_type) { // mrs in straps
			case ATOM_DGPU_VRAM_TYPE_DDR3: // non-G
				atui_mrs[0] = ATUI_MAKE_BRANCH(ddr3_mr0,
					NULL,  NULL,&(format_v0_array[i].MR0),  0,NULL
				);
				atui_mrs[1] = ATUI_MAKE_BRANCH(ddr3_mr1,
					NULL,  NULL,&(format_v0_array[i].MR1),  0,NULL
				);
				atui_mrs[2] = ATUI_MAKE_BRANCH(ddr3_mr2,
					NULL,  NULL,&(format_v0_array[i].MR2),  0,NULL
				);
				break;
			case ATOM_DGPU_VRAM_TYPE_GDDR3:
				atui_mrs[0] = ATUI_MAKE_BRANCH(gddr3_mr0,
					NULL,  NULL,&(format_v0_array[i].MR0),  0,NULL
				);
				atui_mrs[1] = ATUI_MAKE_BRANCH(gddr3_emr1,
					NULL,  NULL,&(format_v0_array[i].MR1),  0,NULL
				);
				// GDDR3 has no MR2
				break;
			case ATOM_DGPU_VRAM_TYPE_GDDR4:
				atui_mrs[0] = ATUI_MAKE_BRANCH(gddr4_mr0,
					NULL,  NULL,&(format_v0_array[i].MR0),  0,NULL
				);
				atui_mrs[1] = ATUI_MAKE_BRANCH(gddr4_emr1,
					NULL,  NULL,&(format_v0_array[i].MR1),  0,NULL
				);
				atui_mrs[2] = ATUI_MAKE_BRANCH(gddr4_emr2,
					NULL,  NULL,&(format_v0_array[i].MR2),  0,NULL
				);
				break;
			default:
				break;
		};
		atui_formattimings = ATUI_MAKE_BRANCH(atom_memory_timing_format_v0,
			NULL,  NULL,&(format_v0_array[i]),
			(sizeof(atui_mrs)/sizeof(atui_branch*)), atui_mrs
		);
		sprintf(atui_formattimings->name, "MemTiming (%u MHz)",
			(format_v0_array[i].ClkRange/100)
		);
		ATUI_ADD_BRANCH(parent, atui_formattimings);
	}
}


inline static atui_branch*
atomtree_populate_vram_module(
		struct atomtree_vram_info* vram_info,
		bool generate_atui
		) {
	enum atomtree_common_version module_ver;
	struct atomtree_vram_module* vram_modules;
	uint8_t count;
	void* vram_module_offset;

	switch (vram_info->ver) {
		case v1_2:
			module_ver = vram_info->v1_2.vram_module_ver;
			vram_modules = vram_info->v1_2.vram_modules;
			count = vram_info->v1_2.leaves->NumOfVRAMModule;
			vram_module_offset = vram_info->v1_2.leaves->vram_module;
			break;
		case v1_3:
			module_ver = vram_info->v1_3.vram_module_ver;
			vram_modules = vram_info->v1_3.vram_modules;
			count = vram_info->v1_3.leaves->NumOfVRAMModule;
			vram_module_offset = vram_info->v1_3.leaves->vram_module;
			break;
		case v1_4:
			module_ver = vram_info->v1_4.vram_module_ver;
			vram_modules = vram_info->v1_4.vram_modules;
			count = vram_info->v1_4.leaves->NumOfVRAMModule;
			vram_module_offset = vram_info->v1_4.leaves->vram_module;
			break;
		case v2_1:
			module_ver = vram_info->v2_1.vram_module_ver;
			vram_modules = vram_info->v2_1.vram_modules;
			count = vram_info->v2_1.leaves->NumOfVRAMModule;
			vram_module_offset = vram_info->v2_1.leaves->vram_module;
			break;
		case v2_2:
			module_ver = vram_info->v2_2.vram_module_ver;
			vram_modules = vram_info->v2_2.vram_modules;
			count = vram_info->v2_2.leaves->NumOfVRAMModule;
			vram_module_offset = vram_info->v2_2.leaves->vram_module;
			break;
		case v2_3:
			module_ver = vram_info->v2_3.vram_module_ver;
			vram_modules = vram_info->v2_3.vram_modules;
			count = vram_info->v2_3.leaves->vram_module_num;
			vram_module_offset = vram_info->v2_3.leaves->vram_module;
			break;
		case v2_4:
			module_ver = vram_info->v2_4.vram_module_ver;
			vram_modules = vram_info->v2_4.vram_modules;
			count = vram_info->v2_4.leaves->vram_module_num;
			vram_module_offset = vram_info->v2_4.leaves->vram_module;
			break;
		case v2_5:
			module_ver = vram_info->v2_5.vram_module_ver;
			vram_modules = vram_info->v2_5.vram_modules;
			count = vram_info->v2_5.leaves->vram_module_num;
			vram_module_offset = vram_info->v2_5.leaves->vram_module;
			break;
		case v2_6:
			module_ver = vram_info->v2_6.vram_module_ver;
			vram_modules = vram_info->v2_6.vram_modules;
			count = vram_info->v2_6.leaves->vram_module_num;
			vram_module_offset = vram_info->v2_6.leaves->vram_module;
			break;
		case v3_0:
			module_ver = vram_info->v3_0.vram_module_ver;
			vram_modules = vram_info->v3_0.vram_modules;
			count = vram_info->v3_0.leaves->vram_module_num;
			vram_module_offset = vram_info->v3_0.leaves->vram_module;
			break;
	};
	assert(count <= ATOMTREE_VRAM_MODULES_MAX);

	enum atom_dgpu_vram_type memory_type;
	uint8_t num_memory_timing_format;
	uint8_t i=0;

	atui_branch* atui_module_entry;
	atui_branch* atui_vrammodules = NULL;
	atui_branch* atui_mrs[2] = {NULL};
	if (generate_atui) {
		atui_vrammodules = ATUI_MAKE_BRANCH(atui_nullstruct,
			NULL,  NULL,NULL,  count,NULL
		);
	}

	switch(module_ver) {
		case v1_3: // atom_vram_module_v3. Will look very similar to v4
			for (i=0; i < count; i++) {
				vram_modules[i].v1_3 = vram_module_offset;
				vram_modules[i].num_memory_timing_format = (
					(vram_modules[i].v1_3->ModuleSize
						- offsetof(struct atom_vram_module_v3, MemTiming)
					) / sizeof(struct atom_memory_timing_format_v0)
				);
				vram_module_offset += vram_modules[i].v1_3->ModuleSize;
			}

			if (generate_atui) {
				for (i=0; i < count; i++) {
					num_memory_timing_format =
							vram_modules[i].num_memory_timing_format;
					memory_type = vram_modules[i].v1_3->MemoryType;

					atui_module_entry = ATUI_MAKE_BRANCH(atom_vram_module_v3,
						NULL,  &(vram_modules[i]), vram_modules[i].v1_3,
						(2+num_memory_timing_format), NULL // 2 is for MRs
					);
					ATUI_ADD_BRANCH(atui_vrammodules, atui_module_entry);

					assert(vram_modules[i].v1_3->MemoryVendorID.vendor_code
						<= ( sizeof(PPATUI_ENUM_NAME(GDDR_MEM_VENDOR_e))
								/ sizeof(struct atui_enum)
							)
					);
					sprintf(atui_module_entry->name, "%s (%s)",
						atui_module_entry->varname,
						PPATUI_ENUM_NAME(GDDR_MEM_VENDOR_e)[
							vram_modules[i].v1_3->MemoryVendorID.vendor_code
						].name
					);

					switch (memory_type) { // mode registers directly in module
						case ATOM_DGPU_VRAM_TYPE_DDR3: // non-G
							ATUI_ADD_BRANCH(atui_module_entry,
								ATUI_MAKE_BRANCH(ddr3_mr2,  NULL,
									NULL,&(vram_modules[i].v1_3->MR2),  0,NULL
								)
							);
							ATUI_ADD_BRANCH(atui_module_entry,
								ATUI_MAKE_BRANCH(ddr3_mr3,  NULL,
									NULL,&(vram_modules[i].v1_3->MR3),  0,NULL
								)
							);
							break;
						case ATOM_DGPU_VRAM_TYPE_GDDR4:
							ATUI_ADD_BRANCH(atui_module_entry,
								ATUI_MAKE_BRANCH(gddr4_emr2,  NULL,
									NULL,&(vram_modules[i].v1_3->MR2),  0,NULL
								)
							);
							ATUI_ADD_BRANCH(atui_module_entry,
								ATUI_MAKE_BRANCH(gddr4_emr3,  NULL,
									NULL,&(vram_modules[i].v1_3->MR3),  0,NULL
								)
							);
							break;
						case ATOM_DGPU_VRAM_TYPE_GDDR3: // GDDR3 has no MR2,MR3
						default:
							break;
					};

					atomtree_populate_atom_memory_timing_format_v0(
						atui_module_entry,
						memory_type,
						vram_modules[i].v1_3->MemTiming,
						num_memory_timing_format
					);
				} // v3 per-module loop
				strcpy(atui_vrammodules->name, atui_module_entry->varname);
			} // v3 generate atui
			break;

		case v1_4: // atom_vram_module_v4. Will look very similar to v3
			for (i=0; i < count; i++) {
				vram_modules[i].v1_4 = vram_module_offset;
				vram_modules[i].num_memory_timing_format = (
					(vram_modules[i].v1_4->ModuleSize
					- offsetof(struct atom_vram_module_v4, MemTiming)
					) / sizeof(struct atom_memory_timing_format_v0)
				);
				vram_module_offset += vram_modules[i].v1_4->ModuleSize;
			}

			if (generate_atui) {
				for (i=0; i < count; i++) {
					num_memory_timing_format =
							vram_modules[i].num_memory_timing_format;
					memory_type = vram_modules[i].v1_4->MemoryType;

					atui_module_entry = ATUI_MAKE_BRANCH(atom_vram_module_v4,
						NULL,  &(vram_modules[i]), vram_modules[i].v1_4,
						(2+num_memory_timing_format), NULL // 2 is for MRs
					);
					ATUI_ADD_BRANCH(atui_vrammodules, atui_module_entry);

					assert(vram_modules[i].v1_4->MemoryVendorID.vendor_code
						<= ( sizeof(PPATUI_ENUM_NAME(GDDR_MEM_VENDOR_e))
								/ sizeof(struct atui_enum)
							)
					);
					sprintf(atui_module_entry->name, "%s (%s)",
						atui_module_entry->varname,
						PPATUI_ENUM_NAME(GDDR_MEM_VENDOR_e)[
							vram_modules[i].v1_4->MemoryVendorID.vendor_code
						].name
					);

					switch (memory_type) { // mode registers directly in module
						case ATOM_DGPU_VRAM_TYPE_DDR3: // non-G
							ATUI_ADD_BRANCH(atui_module_entry,
								ATUI_MAKE_BRANCH(ddr3_mr2,  NULL,
									NULL,&(vram_modules[i].v1_4->MR2),  0,NULL
								)
							);
							ATUI_ADD_BRANCH(atui_module_entry,
								ATUI_MAKE_BRANCH(ddr3_mr3,  NULL,
									NULL,&(vram_modules[i].v1_4->MR3),  0,NULL
								)
							);
							break;
						case ATOM_DGPU_VRAM_TYPE_GDDR4:
							ATUI_ADD_BRANCH(atui_module_entry,
								ATUI_MAKE_BRANCH(gddr4_emr2,  NULL,
									NULL,&(vram_modules[i].v1_4->MR2),  0,NULL
								)
							);
							ATUI_ADD_BRANCH(atui_module_entry,
								ATUI_MAKE_BRANCH(gddr4_emr3,  NULL,
									NULL,&(vram_modules[i].v1_4->MR3),  0,NULL
								)
							);
							break;
						case ATOM_DGPU_VRAM_TYPE_GDDR3: // GDDR3 has no MR2,MR3
						default:
							break;
					};

					atomtree_populate_atom_memory_timing_format_v0(
						atui_module_entry,
						memory_type,
						vram_modules[i].v1_4->MemTiming,
						num_memory_timing_format
					);

				} // v4 per-module loop
				strcpy(atui_vrammodules->name, atui_module_entry->varname);
			} // v4 generate atui
			break;

		case v1_7:
			for (i=0; i < count; i++) {
				vram_modules[i].v1_7 = vram_module_offset;
				vram_module_offset += vram_modules[i].v1_7->ModuleSize;
			}
			if (generate_atui) {
				for (i=0; i < count; i++) {
					memory_type = vram_modules[i].v1_7->MemoryType;
					switch (memory_type) { // mode registers directly in module
						case ATOM_DGPU_VRAM_TYPE_GDDR5:
							atui_mrs[0] = ATUI_MAKE_BRANCH(gddr5_mr2,  NULL,
								NULL,&(vram_modules[i].v1_7->MR2),  0,NULL
							);
							atui_mrs[1] = ATUI_MAKE_BRANCH(gddr5_mr3,  NULL,
								NULL,&(vram_modules[i].v1_7->MR3),  0,NULL
							);
							break;
						case ATOM_DGPU_VRAM_TYPE_HBM:
							atui_mrs[0] = ATUI_MAKE_BRANCH(hbm_mr2,  NULL,
								NULL,&(vram_modules[i].v1_7->MR2),  0,NULL
							);
							atui_mrs[1] = ATUI_MAKE_BRANCH(hbm_mr3,  NULL,
								NULL,&(vram_modules[i].v1_7->MR3),  0,NULL
							);
							break;
						default:
							break;
					};

					atui_module_entry = ATUI_MAKE_BRANCH(atom_vram_module_v7,
						NULL,  &(vram_modules[i]), vram_modules[i].v1_7,
						2, atui_mrs // 2 is for MRs
					);
					ATUI_ADD_BRANCH(atui_vrammodules, atui_module_entry);

					assert(vram_modules[i].v1_7->MemoryVendorID.vendor_code
						<= ( sizeof(PPATUI_ENUM_NAME(GDDR_MEM_VENDOR_e))
								/ sizeof(struct atui_enum)
							)
					);
					sprintf(atui_module_entry->name, "%s (%s)",
						atui_module_entry->varname,
						PPATUI_ENUM_NAME(GDDR_MEM_VENDOR_e)[
							vram_modules[i].v1_7->MemoryVendorID.vendor_code
						].name
					);
				} // v7 per-module loop
				strcpy(atui_vrammodules->name, atui_module_entry->varname);
			} // v7 generate atui
			break;
		case v1_8:
			for (i=0; i < count; i++) {
				vram_modules[i].v1_8 = vram_module_offset;
				vram_module_offset += vram_modules[i].v1_8->ModuleSize;
			}
			if (generate_atui) {
				for (i=0; i < count; i++) {
					memory_type = vram_modules[i].v1_8->MemoryType;
					switch (memory_type) { // mode registers directly in module
						case ATOM_DGPU_VRAM_TYPE_GDDR5:
							atui_mrs[0] = ATUI_MAKE_BRANCH(gddr5_mr2,  NULL,
								NULL,&(vram_modules[i].v1_8->MR2),  0,NULL
							);
							atui_mrs[1] = ATUI_MAKE_BRANCH(gddr5_mr3,  NULL,
								NULL,&(vram_modules[i].v1_8->MR3),  0,NULL
							);
							break;
						case ATOM_DGPU_VRAM_TYPE_HBM:
							atui_mrs[0] = ATUI_MAKE_BRANCH(hbm_mr2,  NULL,
								NULL,&(vram_modules[i].v1_8->MR2),  0,NULL
							);
							atui_mrs[1] = ATUI_MAKE_BRANCH(hbm_mr3,  NULL,
								NULL,&(vram_modules[i].v1_8->MR3),  0,NULL
							);
							break;
						default:
							break;
					};

					atui_module_entry = ATUI_MAKE_BRANCH(atom_vram_module_v8,
						NULL,  &(vram_modules[i]), vram_modules[i].v1_8,
						2, atui_mrs // 2 is for MRs
					);
					ATUI_ADD_BRANCH(atui_vrammodules, atui_module_entry);

					assert(vram_modules[i].v1_8->MemoryVendorID.vendor_code
						<= ( sizeof(PPATUI_ENUM_NAME(GDDR_MEM_VENDOR_e))
								/ sizeof(struct atui_enum)
							)
					);
					sprintf(atui_module_entry->name, "%s (%s)",
						atui_module_entry->varname,
						PPATUI_ENUM_NAME(GDDR_MEM_VENDOR_e)[
							vram_modules[i].v1_8->MemoryVendorID.vendor_code
						].name
					);
				} // v8 per-module loop
				strcpy(atui_vrammodules->name, atui_module_entry->varname);
			} // v8 generate atui
			break;

		case v1_9:
			for (i=0; i < count; i++) {
				vram_modules[i].v1_9 = vram_module_offset;
				vram_module_offset += vram_modules[i].v1_9->vram_module_size;
			}
			if (generate_atui) {
				for (i=0; i < count; i++) {
					memory_type = vram_modules[i].v1_9->memory_type;

					atui_module_entry = ATUI_MAKE_BRANCH(atom_vram_module_v9,
						NULL,  &(vram_modules[i]), vram_modules[i].v1_9,
						0, NULL
					);
					ATUI_ADD_BRANCH(atui_vrammodules, atui_module_entry);

					assert(vram_modules[i].v1_9->vendor_rev_id.vendor_code
						<= ( sizeof(PPATUI_ENUM_NAME(GDDR_MEM_VENDOR_e))
								/ sizeof(struct atui_enum)
							)
					);
					sprintf(atui_module_entry->name, "%s (%s)",
						atui_module_entry->varname,
						PPATUI_ENUM_NAME(GDDR_MEM_VENDOR_e)[
							vram_modules[i].v1_9->vendor_rev_id.vendor_code
						].name
					);
				} // v9 per-module loop
				strcpy(atui_vrammodules->name, atui_module_entry->varname);
			} // v9 generate atui
			break;

		case v1_10:
			for (i=0; i < count; i++) {
				vram_modules[i].v1_10 = vram_module_offset;
				vram_module_offset += vram_modules[i].v1_10->vram_module_size;
			}
			if (generate_atui) {
				for (i=0; i < count; i++) {
					memory_type = vram_modules[i].v1_10->memory_type;

					atui_module_entry = ATUI_MAKE_BRANCH(atom_vram_module_v10,
						NULL,  &(vram_modules[i]), vram_modules[i].v1_10,
						0, NULL
					);
					ATUI_ADD_BRANCH(atui_vrammodules, atui_module_entry);

					assert(vram_modules[i].v1_10->vendor_rev_id.vendor_code
						<= ( sizeof(PPATUI_ENUM_NAME(GDDR_MEM_VENDOR_e))
								/ sizeof(struct atui_enum)
							)
					);
					sprintf(atui_module_entry->name, "%s (%s)",
						atui_module_entry->varname,
						PPATUI_ENUM_NAME(GDDR_MEM_VENDOR_e)[
							vram_modules[i].v1_10->vendor_rev_id.vendor_code
						].name
					);
				} // v10 per-module loop
				strcpy(atui_vrammodules->name, atui_module_entry->varname);
			} // v10 generate atui
			break;

		case v1_11:
			for (i=0; i < count; i++) {
				vram_modules[i].v1_11 = vram_module_offset;
				vram_module_offset += vram_modules[i].v1_11->vram_module_size;
			}
			if (generate_atui) {
				for (i=0; i < count; i++) {
					memory_type = vram_modules[i].v1_11->memory_type;

					atui_module_entry = ATUI_MAKE_BRANCH(atom_vram_module_v11,
						NULL,  &(vram_modules[i]), vram_modules[i].v1_11,
						0, NULL
					);
					ATUI_ADD_BRANCH(atui_vrammodules, atui_module_entry);

					assert(vram_modules[i].v1_11->vendor_rev_id.vendor_code
						<= ( sizeof(PPATUI_ENUM_NAME(GDDR_MEM_VENDOR_e))
								/ sizeof(struct atui_enum)
							)
					);
					sprintf(atui_module_entry->name, "%s (%s)",
						atui_module_entry->varname,
						PPATUI_ENUM_NAME(GDDR_MEM_VENDOR_e)[
							vram_modules[i].v1_11->vendor_rev_id.vendor_code
						].name
					);
				} // v11 per-module loop
				strcpy(atui_vrammodules->name, atui_module_entry->varname);
			} // v11 generate atui
			break;

		case v3_0:
			for (i=0; i < count; i++) {
				vram_modules[i].v3_0 = vram_module_offset;
				//vram_module_offset += vram_modules[i].v3_0->vram_module_size;
				vram_module_offset += sizeof(struct atom_vram_module_v3_0);

				vram_modules[i].dram_info = NULL;
				if (vram_modules[i].v3_0->dram_info_offset) {
					vram_modules[i].dram_info = (
						vram_modules[i].leaves
						+ vram_modules[i].v3_0->dram_info_offset
					);
				}

				vram_modules[i].mem_tuning = NULL;
				if (vram_modules[i].v3_0->mem_tuning_offset) {
					vram_modules[i].mem_tuning = (
						vram_modules[i].leaves
						+ vram_modules[i].v3_0->mem_tuning_offset
					);
				}

				vram_modules[i].tmrs_seq = NULL;
				if (vram_modules[i].v3_0->tmrs_seq_offset) {
					vram_modules[i].tmrs_seq = (
						vram_modules[i].leaves
						+ vram_modules[i].v3_0->tmrs_seq_offset
					);
				}
			}
			if (generate_atui) {
				memory_type = vram_info->v3_0.leaves->memory_type;
				for (i=0; i < count; i++) {
					atui_module_entry = ATUI_MAKE_BRANCH(atom_vram_module_v3_0,
						NULL,  &(vram_modules[i]), vram_modules[i].v3_0,  0,NULL
					);
					ATUI_ADD_BRANCH(atui_vrammodules, atui_module_entry);

					assert(vram_modules[i].v3_0->dram_vendor_id.vendor_code
						<= ( sizeof(PPATUI_ENUM_NAME(GDDR_MEM_VENDOR_e))
								/ sizeof(struct atui_enum)
							)
					);
					sprintf(atui_module_entry->name, "%s (%s)",
						atui_module_entry->varname,
						PPATUI_ENUM_NAME(GDDR_MEM_VENDOR_e)[
							vram_modules[i].v3_0->dram_vendor_id.vendor_code
						].name
					);
				} // v3.0 per-module loop
				strcpy(atui_vrammodules->name, atui_module_entry->varname);
			} // v3.0 generate atui
			break;
		default:
			assert(0); // TODO implement
			break;
	}
	return atui_vrammodules;
}

inline static atui_branch*
atomtree_populate_vram_info_v1_2(
		struct atomtree_vram_info* vram_info,
		bool generate_atui
		) {
	struct atomtree_vram_info_v1_2* const vi12 = &(vram_info->v1_2);
	vi12->leaves = vram_info->leaves;

	vi12->vram_module_ver = v1_3;
	atui_branch* atui_vrammodules = NULL;
	if (vi12->leaves->NumOfVRAMModule) {
		atui_vrammodules = atomtree_populate_vram_module(
			vram_info, generate_atui
		);
	}

	atui_branch* atui_vi = NULL;
	if (generate_atui) {
		atui_vi = ATUI_MAKE_BRANCH(atom_vram_info_v1_2,
			NULL,  vi12,vi12->leaves,  1,&atui_vrammodules
		);
	}

	return atui_vi;
}

inline static atui_branch*
atomtree_populate_vram_info_v1_3(
		struct atomtree_vram_info* vram_info,
		bool generate_atui
		) {
	struct atomtree_vram_info_v1_3* const vi13 = &(vram_info->v1_3);
	vi13->leaves = vram_info->leaves;

	uint8_t i;

	// it might be better to keep atui generation for the reg blocks up here
	// than in the ATUI_FUNCIFY for that it might not exist, and that we might
	// want to attach stuff to it, like timing strap definitions.
	atui_branch* atui_memadjust = NULL;
	if (vi13->leaves->MemAdjustTblOffset) {
		vi13->mem_adjust_table.leaves =
			(void*)vi13->leaves + vi13->leaves->MemAdjustTblOffset;

		/* regular init, not umc init
		atui_memadjust = atomtree_populate_init_reg_block(
			&(vi13->mem_adjust_table), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_memadjust->name, "mem_adjust_table");
		}
		*/
	} else {
		vi13->mem_adjust_table.leaves = NULL;
	}

	atui_branch* atui_memclkpatch = NULL;
	if (vi13->leaves->MemClkPatchTblOffset) {
		vi13->mem_clk_patch.leaves =
			(void*)vi13->leaves + vi13->leaves->MemClkPatchTblOffset;

		/* regular init, not umc init
		atui_memclkpatch = atomtree_populate_init_reg_block(
			&(vi13->mem_clk_patch), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_memclkpatch->name, "mem_clk_patch_table");
		}
		*/
	} else {
		vi13->mem_clk_patch.leaves = NULL;
	}

	vi13->vram_module_ver = v1_3;
	atui_branch* atui_vrammodules = NULL;
	if (vi13->leaves->NumOfVRAMModule) {
		atui_vrammodules = atomtree_populate_vram_module(
			vram_info, generate_atui
		);
	}

	atui_branch* atui_vi = NULL;
	if (generate_atui) {
		atui_branch* const vi13_children[] = {
			atui_memadjust, atui_memclkpatch, atui_vrammodules
		};
		atui_vi = ATUI_MAKE_BRANCH(atom_vram_info_v1_3,
			NULL,  vi13,vi13->leaves,
			(sizeof(vi13_children)/sizeof(atui_branch*)), vi13_children
		);
	}

	return atui_vi;
}

inline static atui_branch*
atomtree_populate_vram_info_v1_4(
		struct atomtree_vram_info* vram_info,
		bool generate_atui
		) {
	struct atomtree_vram_info_v1_4* const vi14 = &(vram_info->v1_4);
	vi14->leaves = vram_info->leaves;

	uint8_t i;

	atui_branch* atui_memadjust = NULL;
	if (vi14->leaves->MemAdjustTblOffset) {
		vi14->mem_adjust_table.leaves =
			(void*)vi14->leaves + vi14->leaves->MemAdjustTblOffset;

		/* regular init, not umc init
		atui_memadjust = atomtree_populate_init_reg_block(
			&(vi14->mem_adjust_table), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_memadjust->name, "mem_adjust_table");
		}
		*/
	} else {
		vi14->mem_adjust_table.leaves = NULL;
	}

	atui_branch* atui_memclkpatch = NULL;
	if (vi14->leaves->MemClkPatchTblOffset) {
		vi14->mem_clk_patch.leaves =
			(void*)vi14->leaves + vi14->leaves->MemClkPatchTblOffset;

		/* regular init, not umc init
		atui_memclkpatch = atomtree_populate_init_reg_block(
			&(vi14->mem_clk_patch), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_memclkpatch->name, "mem_clk_patch_table");
		}
		*/
	} else {
		vi14->mem_clk_patch.leaves = NULL;
	}

	vi14->vram_module_ver = v1_4;
	atui_branch* atui_vrammodules = NULL;
	if (vi14->leaves->NumOfVRAMModule) {
		atui_vrammodules = atomtree_populate_vram_module(
			vram_info, generate_atui
		);
	}

	atui_branch* atui_vi = NULL;
	if (generate_atui) {
		atui_branch* const vi14_children[] = {
			atui_memadjust, atui_memclkpatch, atui_vrammodules,
		};
		atui_vi = ATUI_MAKE_BRANCH(atom_vram_info_v1_4,
			NULL,  vi14,vi14->leaves,
			(sizeof(vi14_children)/sizeof(atui_branch*)), vi14_children
		);
	}

	return atui_vi;
}

inline static atui_branch*
atomtree_populate_vram_info_v2_1(
		struct atomtree_vram_info* vram_info,
		bool generate_atui
		) {
	struct atomtree_vram_info_header_v2_1* const vi21 = &(vram_info->v2_1);
	vi21->leaves = vram_info->leaves;

	atui_branch* atui_memadjust = NULL;
	if (vi21->leaves->MemAdjustTblOffset) {
		vi21->mem_adjust_table.leaves =
			(void*)vi21->leaves + vi21->leaves->MemAdjustTblOffset;

		/* regular init, not umc init
		atui_memadjust = atomtree_populate_init_reg_block(
			&(vi21->mem_adjust_table), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_memadjust->name, "mem_adjust_table");
		}
		*/
	} else {
		vi21->mem_adjust_table.leaves = NULL;
	}

	atui_branch* atui_memclkpatch = NULL;
	if (vi21->leaves->MemClkPatchTblOffset) {
		vi21->mem_clk_patch.leaves =
			(void*)vi21->leaves + vi21->leaves->MemClkPatchTblOffset;

		/* regular init, not umc init
		atui_memclkpatch = atomtree_populate_init_reg_block(
			&(vi21->mem_clk_patch), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_memclkpatch->name, "mem_clk_patch_table");
		}
		*/
	} else {
		vi21->mem_clk_patch.leaves = NULL;
	}

	atui_branch* atui_perbytepreset = NULL;
	if (vi21->leaves->PerBytePresetOffset) {
		vi21->per_byte_preset.leaves =
			(void*)vi21->leaves + vi21->leaves->PerBytePresetOffset;

		/* regular init, not umc init
		atui_perbytepreset = atomtree_populate_init_reg_block(
			&(vi21->per_byte_preset), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_perbytepreset->name, "mem_clk_patch_table");
		}
		*/
	} else {
		vi21->per_byte_preset.leaves = NULL;
	}

	vi21->vram_module_ver = v1_7;
	atui_branch* atui_vrammodules = NULL;
	if (vi21->leaves->NumOfVRAMModule) {
		atui_vrammodules = atomtree_populate_vram_module(
			vram_info, generate_atui
		);
	}

	atui_branch* atui_vi = NULL;
	if (generate_atui) {
		atui_branch* const vi21_children[] = {
			atui_memadjust, atui_memclkpatch, atui_perbytepreset,
			atui_vrammodules
		};
		atui_vi = ATUI_MAKE_BRANCH(atom_vram_info_header_v2_1,
			NULL,  vi21,vi21->leaves,
			(sizeof(vi21_children)/sizeof(atui_branch*)), vi21_children
		);
	}

	return atui_vi;
}

inline static atui_branch*
atomtree_populate_vram_info_v2_2(
		struct atomtree_vram_info* vram_info,
		bool generate_atui
		) {
	struct atomtree_vram_info_header_v2_2* const vi22 = &(vram_info->v2_2);
	vi22->leaves = vram_info->leaves;

	atui_branch* atui_memadjust = NULL;
	if (vi22->leaves->MemAdjustTblOffset) {
		vi22->mem_adjust_table.leaves =
			(void*)vi22->leaves + vi22->leaves->MemAdjustTblOffset;

		/* regular init, not umc init
		atui_memadjust = atomtree_populate_init_reg_block(
			&(vi22->mem_adjust_table), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_memadjust->name, "mem_adjust_table");
		}
		*/
	} else {
		vi22->mem_adjust_table.leaves = NULL;
	}

	atui_branch* atui_memclkpatch = NULL;
	if (vi22->leaves->MemClkPatchTblOffset) {
		vi22->mem_clk_patch.leaves =
			(void*)vi22->leaves + vi22->leaves->MemClkPatchTblOffset;

		/* regular init, not umc init
		atui_memclkpatch = atomtree_populate_init_reg_block(
			&(vi22->mem_clk_patch), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_memclkpatch->name, "mem_clk_patch_table");
		}
		*/
	} else {
		vi22->mem_clk_patch.leaves = NULL;
	}

	atui_branch* atui_mcadjpertile = NULL;
	if (vi22->leaves->McAdjustPerTileTblOffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi22->mc_adjust_pertile.leaves =
			(void*)vi22->leaves + vi22->leaves->McAdjustPerTileTblOffset;
		/* regular init, not umc init
		atui_mcadjpertile = atomtree_populate_init_reg_block(
			&(vi22->mc_adjust_pertile), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_mcadjpertile->name, "mc_adjust_pertile_table");
		}
		*/
	} else {
		vi22->mc_adjust_pertile.leaves = NULL;
	}

	atui_branch* atui_phyinit = NULL;
	if (vi22->leaves->McPhyInitTableOffset) {
		vi22->mc_phyinit.leaves =
			(void*)vi22->leaves + vi22->leaves->McPhyInitTableOffset;
		/* regular init, not umc init
		atui_phyinit = atomtree_populate_umc_init_reg_block(
			&(vi22->mc_phyinit), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_phyinit->name, "mc_phyinit_table");
		}
		*/
	} else {
		vi22->mc_phyinit.leaves = NULL;
	}

	atui_branch* atui_dram_remap = NULL;
	if (vi22->leaves->DramDataRemapTblOffset) {
	// TODO
	vi22->dram_data_remap =
		(void*)vi22->leaves + vi22->leaves->DramDataRemapTblOffset;
	} else {
		vi22->dram_data_remap = NULL;
	}

	vi22->vram_module_ver = v1_8;
	atui_branch* atui_vrammodules = NULL;
	if (vi22->leaves->NumOfVRAMModule) {
		atui_vrammodules = atomtree_populate_vram_module(
			vram_info, generate_atui
		);
	}

	atui_branch* atui_vi = NULL;
	if (generate_atui) {
		atui_branch* const vi22_children[] = {
			atui_memadjust, atui_memclkpatch, atui_vrammodules
		};
		atui_vi = ATUI_MAKE_BRANCH(atom_vram_info_header_v2_2,
			NULL,  vi22,vi22->leaves,
			(sizeof(vi22_children)/sizeof(atui_branch*)), vi22_children
		);
	}

	return atui_vi;
}

inline static atui_branch*
atomtree_populate_vram_info_v2_3(
		struct atomtree_vram_info* vram_info,
		bool generate_atui
		) {
	struct atomtree_vram_info_header_v2_3* const vi23 = &(vram_info->v2_3);
	vi23->leaves = vram_info->leaves;

	uint16_t i = 0;

	atui_branch* atui_memadjust = NULL;
	if (vi23->leaves->mem_adjust_tbloffset) {
		vi23->mem_adjust_table.leaves =
			(void*)vi23->leaves + vi23->leaves->mem_adjust_tbloffset;
		atui_memadjust = atomtree_populate_umc_init_reg_block(
			&(vi23->mem_adjust_table), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_memadjust->name, "mem_adjust_table");
		}
	} else {
		vi23->mem_adjust_table.leaves = NULL;
	}

	atui_branch* atui_memclkpatch = NULL;
	if (vi23->leaves->mem_clk_patch_tbloffset) {
		vi23->mem_clk_patch.leaves =
			(void*)vi23->leaves + vi23->leaves->mem_clk_patch_tbloffset;
		atui_memclkpatch = atomtree_populate_umc_init_reg_block(
			&(vi23->mem_clk_patch), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_memclkpatch->name, "mem_clk_patch_table");
		}
	} else {
		vi23->mem_clk_patch.leaves = NULL;
	}

	atui_branch* atui_mcadjpertile = NULL;
	if (vi23->leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi23->mc_adjust_pertile.leaves =
			(void*)vi23->leaves + vi23->leaves->mc_adjust_pertile_tbloffset;
		atui_mcadjpertile = atomtree_populate_umc_init_reg_block(
			&(vi23->mc_adjust_pertile), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_mcadjpertile->name, "mc_adjust_pertile_table");
		}
	} else {
		vi23->mc_adjust_pertile.leaves = NULL;
	}

	atui_branch* atui_phyinit = NULL;
	if (vi23->leaves->mc_phyinit_tbloffset) {
		vi23->mc_phyinit.leaves =
			(void*)vi23->leaves + vi23->leaves->mc_phyinit_tbloffset;
		atui_phyinit = atomtree_populate_umc_init_reg_block(
			&(vi23->mc_phyinit), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_phyinit->name, "mc_phyinit_table");
		}
	} else {
		vi23->mc_phyinit.leaves = NULL;
	}

	atui_branch* atui_dram_remap = NULL;
	if (vi23->leaves->dram_data_remap_tbloffset) {
	// TODO does vraminfo->mc_phy_tile_num significantly affect this?
	// TODO probably has the structure in atombios.h, rather than the gddr6 one
	// in atomfirmware.h
	vi23->dram_data_remap =
		(void*)vi23->leaves + vi23->leaves->dram_data_remap_tbloffset;
	} else {
		vi23->dram_data_remap = NULL;
	}

	atui_branch* atui_hbm_tmrs = NULL;
	if (vi23->leaves->tmrs_seq_offset) {
		// TODO what is this?
		vi23->hbm_tmrs = (void*)vi23->leaves + vi23->leaves->tmrs_seq_offset;
		if (generate_atui) {
		}
	} else {
		vi23->hbm_tmrs = NULL;
	}

	atui_branch* atui_postucode_init = NULL;
	if (vi23->leaves->post_ucode_init_offset) {
		vi23->post_ucode_init.leaves =
			(void*)vi23->leaves + vi23->leaves->post_ucode_init_offset;
		atui_branch* atui_postucode_init = atomtree_populate_umc_init_reg_block(
			&(vi23->post_ucode_init), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_postucode_init->name, "post_ucode_init");
		}
	} else {
		vi23->post_ucode_init.leaves = NULL;
	}

	vi23->vram_module_ver = v1_9;
	atui_branch* atui_vrammodules = NULL;
	if (vi23->leaves->vram_module_num) {
		atui_vrammodules = atomtree_populate_vram_module(
			vram_info, generate_atui
		);
	}

	atui_branch* atui_vi = NULL;
	if (generate_atui) {
		atui_branch* const vi23_children[] = {
			atui_memadjust, atui_memclkpatch, atui_mcadjpertile, atui_phyinit,
			atui_dram_remap, atui_hbm_tmrs, atui_postucode_init,
			atui_vrammodules
		};

		atui_vi = ATUI_MAKE_BRANCH(atom_vram_info_header_v2_3,
			NULL,  vi23,vi23->leaves,
			(sizeof(vi23_children)/sizeof(atui_branch*)), vi23_children
		);
	}
	return atui_vi;
}

inline static atui_branch*
atomtree_populate_vram_info_v2_4(
		struct atomtree_vram_info* vram_info,
		bool generate_atui
		) {
	struct atomtree_vram_info_header_v2_4* const vi24 = &(vram_info->v2_4);
	vi24->leaves = vram_info->leaves;
	struct atom_vram_info_header_v2_4* const leaves = vram_info->leaves;

	uint16_t i = 0;
	atui_branch* tmp_branch = NULL;

	atui_branch* atui_memadjust = NULL;
	if (vi24->leaves->mem_adjust_tbloffset) {
		vi24->mem_adjust_table.leaves =
			(void*)vi24->leaves + vi24->leaves->mem_adjust_tbloffset;
		atui_memadjust = atomtree_populate_umc_init_reg_block(
			&(vi24->mem_adjust_table), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_memadjust->name, "mem_adjust_table");
		}
	} else {
		vi24->mem_adjust_table.leaves = NULL;
	}

	atui_branch* atui_memclkpatch = NULL;
	if (vi24->leaves->mem_clk_patch_tbloffset) {
		vi24->mem_clk_patch.leaves =
			(void*)vi24->leaves + vi24->leaves->mem_clk_patch_tbloffset;
		atui_memclkpatch = atomtree_populate_umc_init_reg_block(
			&(vi24->mem_clk_patch), generate_atui, 1 // 1 for timings
		);

		vi24->navi1_gddr6_timings = (struct umc_block_navi1_timings*)\
			vi24->mem_clk_patch.umc_reg_setting_list[0];
		vi24->num_timing_straps =
			&(vi24->mem_clk_patch.umc_reg_setting_list_length);

		if (generate_atui) {
			atui_branch* const atui_navi_timings = ATUI_MAKE_BRANCH(
				atui_nullstruct,
				"umc_block_navi1_timings",
				NULL,NULL,  *vi24->num_timing_straps,NULL
			);
			for (i=0; i < *vi24->num_timing_straps; i++) {
				tmp_branch = ATUI_MAKE_BRANCH(umc_block_navi1_timings,  NULL,
					NULL,&(vi24->navi1_gddr6_timings[i]),  0,NULL
				);
				sprintf(tmp_branch->name, "%s (%i MHz)",
					tmp_branch->varname,
					(vi24->navi1_gddr6_timings[i].block_id.memclockrange / 100)
				);
				ATUI_ADD_BRANCH(atui_navi_timings, tmp_branch);
			}

			strcpy(atui_memclkpatch->name, "mem_clk_patch_table");
			ATUI_ADD_BRANCH(atui_memclkpatch, atui_navi_timings);
		}
	} else {
		vi24->mem_clk_patch.leaves = NULL;
		vi24->navi1_gddr6_timings = NULL;
		vi24->num_timing_straps = 0;
	}

	atui_branch* atui_mcadjpertile = NULL;
	if (vi24->leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi24->mc_adjust_pertile.leaves =
			(void*)vi24->leaves + vi24->leaves->mc_adjust_pertile_tbloffset;
		atui_mcadjpertile = atomtree_populate_umc_init_reg_block(
			&(vi24->mc_adjust_pertile), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_mcadjpertile->name, "mc_adjust_pertile_table");
		}
	} else {
		vi24->mc_adjust_pertile.leaves = NULL;
	}

	atui_branch* atui_phyinit = NULL;
	if (vi24->leaves->mc_phyinit_tbloffset) {
		vi24->mc_phyinit.leaves =
			(void*)vi24->leaves + vi24->leaves->mc_phyinit_tbloffset;
		atui_phyinit = atomtree_populate_umc_init_reg_block(
			&(vi24->mc_phyinit), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_phyinit->name, "mc_phyinit_table");
		}
	} else {
		vi24->mc_phyinit.leaves = NULL;
	}

	atui_branch* atui_dram_data_remap = NULL;
	if (vi24->leaves->dram_data_remap_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi24->dram_data_remap =
			(void*)vi24->leaves + vi24->leaves->dram_data_remap_tbloffset;
		if (generate_atui) {
		}
	} else {
		vi24->dram_data_remap = NULL;
	}

	atui_branch* atui_postucode_init = NULL;
	if (vi24->leaves->post_ucode_init_offset) {
		vi24->post_ucode_init.leaves =
			(void*)vi24->leaves + vi24->leaves->post_ucode_init_offset;
		atui_postucode_init = atomtree_populate_umc_init_reg_block(
			&(vi24->post_ucode_init), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_postucode_init->name, "post_ucode_init");
		}
	} else {
		vi24->post_ucode_init.leaves = NULL;
	}

	vi24->vram_module_ver = v1_10;
	atui_branch* atui_vrammodules = NULL;
	if (vi24->leaves->vram_module_num) {
		atui_vrammodules = atomtree_populate_vram_module(
			vram_info, generate_atui
		);
	}

	atui_branch* atui_vi = NULL;
	if (generate_atui) {
		atui_branch* const vi24_children[] = {
			atui_memadjust, atui_memclkpatch, atui_mcadjpertile,
			atui_dram_data_remap, atui_phyinit, atui_postucode_init,
			atui_vrammodules
		};
		atui_vi = ATUI_MAKE_BRANCH(atom_vram_info_header_v2_4,
			NULL,  vi24,vi24->leaves,
			(sizeof(vi24_children)/sizeof(atui_branch*)), vi24_children
		);
	}
	return atui_vi;
}

inline static atui_branch*
atomtree_populate_vram_info_v2_5(
		struct atomtree_vram_info* vram_info,
		bool generate_atui
		) {
	struct atomtree_vram_info_header_v2_5* const vi25 = &(vram_info->v2_5);
	vi25->leaves = vram_info->leaves;

	uint16_t i = 0;
	atui_branch* tmp_branch = NULL;

	atui_branch* atui_memadjust = NULL;
	if (vi25->leaves->mem_adjust_tbloffset) {
		vi25->mem_adjust_table.leaves =
			(void*)vi25->leaves + vi25->leaves->mem_adjust_tbloffset;
		atui_memadjust = atomtree_populate_umc_init_reg_block(
			&(vi25->mem_adjust_table), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_memadjust->name, "mem_adjust_table");
		}
	} else {
		vi25->mem_adjust_table.leaves = NULL;
	}

	atui_branch* atui_gddr6_ac_timings = NULL;
	if (vi25->leaves->gddr6_ac_timing_offset) {
		vi25->gddr6_ac_timings =
			(void*)vi25->leaves + vi25->leaves->gddr6_ac_timing_offset;
		i = 0;
		while (vi25->gddr6_ac_timings[i].u32umc_id_access.u32umc_id_access) {
			i++;
		}
		vi25->gddr6_acstrap_count = i;
		if (generate_atui) {
			atui_gddr6_ac_timings = ATUI_MAKE_BRANCH(atui_nullstruct,
				"atom_gddr6_ac_timing_v2_5",
				NULL,NULL,  vi25->gddr6_acstrap_count,NULL
			);
			for (i=0; i < vi25->gddr6_acstrap_count; i++) {
				tmp_branch = ATUI_MAKE_BRANCH(atom_gddr6_ac_timing_v2_5,
					NULL,  NULL, &(vi25->gddr6_ac_timings[i]),  0,NULL
				);
				sprintf(tmp_branch->name, "%s (%u MHz)",
					tmp_branch->varname,
					vi25->gddr6_ac_timings[i].u32umc_id_access.memclockrange/100
				);
				ATUI_ADD_BRANCH(atui_gddr6_ac_timings, tmp_branch);
			}
		}
	} else {
		vi25->gddr6_ac_timings = NULL;
		vi25->gddr6_acstrap_count = 0;
	}

	atui_branch* atui_mcadjpertile = NULL;
	if (vi25->leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi25->mc_adjust_pertile.leaves =
			(void*)vi25->leaves + vi25->leaves->mc_adjust_pertile_tbloffset;
		atui_mcadjpertile = atomtree_populate_umc_init_reg_block(
			&(vi25->mc_adjust_pertile), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_mcadjpertile->name, "mc_adjust_pertile_table");
		}
	} else {
		vi25->mc_adjust_pertile.leaves = NULL;
	}

	atui_branch* atui_phyinit = NULL;
	if (vi25->leaves->mc_phyinit_tbloffset) {
		vi25->mc_phyinit.leaves =
			(void*)vi25->leaves + vi25->leaves->mc_phyinit_tbloffset;
		atui_phyinit = atomtree_populate_umc_init_reg_block(
			&(vi25->mc_phyinit), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_phyinit->name, "mc_phyinit_table");
		}
	} else {
		vi25->mc_phyinit.leaves = NULL;
	}

	atui_branch* atui_dram_data_remap = NULL;
	if (vi25->leaves->dram_data_remap_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi25->dram_data_remap =
			(void*)vi25->leaves + vi25->leaves->dram_data_remap_tbloffset;
		if (generate_atui) {
			atui_dram_data_remap = ATUI_MAKE_BRANCH(atom_gddr6_dram_data_remap,
				NULL,  NULL,vi25->dram_data_remap,  0,NULL
			);
		}
	} else {
		vi25->dram_data_remap = NULL;
	}

	atui_branch* atui_postucode_init = NULL;
	if (vi25->leaves->post_ucode_init_offset) {
		vi25->post_ucode_init.leaves =
			(void*)vi25->leaves + vi25->leaves->post_ucode_init_offset;
		atui_postucode_init = atomtree_populate_umc_init_reg_block(
			&(vi25->post_ucode_init), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_postucode_init->name, "post_ucode_init");
		}
	} else {
		vi25->post_ucode_init.leaves = NULL;
	}

	atui_branch* atui_strobe_mode_patch = NULL;
	if (vi25->leaves->strobe_mode_patch_tbloffset) {
		vi25->strobe_mode_patch.leaves =
			(void*)vi25->leaves + vi25->leaves->strobe_mode_patch_tbloffset;
		atui_strobe_mode_patch = atomtree_populate_umc_init_reg_block(
			&(vi25->strobe_mode_patch), generate_atui, 0
		);
	} else {
		vi25->strobe_mode_patch.leaves = NULL;
	}

	vi25->vram_module_ver = v1_11;
	atui_branch* atui_vrammodules = NULL;
	if (vi25->leaves->vram_module_num) {
		atui_vrammodules = atomtree_populate_vram_module(
			vram_info, generate_atui
		);
	}

	atui_branch* atui_vi = NULL;
	if (generate_atui) {
		atui_branch* const vi25_children[] = {
			atui_memadjust, atui_gddr6_ac_timings, atui_mcadjpertile,
			atui_phyinit, atui_dram_data_remap, atui_postucode_init,
			atui_strobe_mode_patch, atui_vrammodules,
		};
		atui_vi = ATUI_MAKE_BRANCH(atom_vram_info_header_v2_5,
			NULL,  vi25,vi25->leaves,
			(sizeof(vi25_children)/sizeof(atui_branch*)), vi25_children
		);
	}
	return atui_vi;
}

inline static atui_branch*
atomtree_populate_vram_info_v2_6(
		struct atomtree_vram_info* vram_info,
		bool generate_atui
		) {
	struct atomtree_vram_info_header_v2_6* const vi26 = &(vram_info->v2_6);
	vi26->leaves = vram_info->leaves;

	uint16_t i = 0;
	atui_branch* tmp_branch = NULL;

	atui_branch* atui_memadjust = NULL;
	if (vi26->leaves->mem_adjust_tbloffset) {
		vi26->mem_adjust_table.leaves =
			(void*)vi26->leaves + vi26->leaves->mem_adjust_tbloffset;
		atui_memadjust = atomtree_populate_umc_init_reg_block(
			&(vi26->mem_adjust_table), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_memadjust->name, "mem_adjust_table");
		}
	} else {
		vi26->mem_adjust_table.leaves = NULL;
	}

	atui_branch* atui_memclkpatch = NULL;
	if (vi26->leaves->mem_clk_patch_tbloffset) {
		vi26->mem_clk_patch.leaves =
			(void*)vi26->leaves + vi26->leaves->mem_clk_patch_tbloffset;
		atui_memclkpatch = atomtree_populate_umc_init_reg_block(
			&(vi26->mem_clk_patch), generate_atui, 0
		);

		if (generate_atui) {
			strcpy(atui_memclkpatch->name, "mem_clk_patch_table");
		}
	} else {
		vi26->mem_clk_patch.leaves = NULL;
	}

	atui_branch* atui_mcadjpertile = NULL;
	if (vi26->leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi26->mc_adjust_pertile.leaves =
			(void*)vi26->leaves + vi26->leaves->mc_adjust_pertile_tbloffset;
		atui_mcadjpertile = atomtree_populate_umc_init_reg_block(
			&(vi26->mc_adjust_pertile), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_mcadjpertile->name, "mc_adjust_pertile_table");
		}
	} else {
		vi26->mc_adjust_pertile.leaves = NULL;
	}

	atui_branch* atui_phyinit = NULL;
	if (vi26->leaves->mc_phyinit_tbloffset) {
		vi26->mc_phyinit.leaves =
			(void*)vi26->leaves + vi26->leaves->mc_phyinit_tbloffset;
		atui_phyinit = atomtree_populate_umc_init_reg_block(
			&(vi26->mc_phyinit), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_phyinit->name, "mc_phyinit_table");
		}
	} else {
		vi26->mc_phyinit.leaves = NULL;
	}

	atui_branch* atui_tmrs_seq = NULL;
	if (vi26->leaves->tmrs_seq_offset) {
		// TODO what is this?
		vi26->tmrs_seq = (void*)vi26->leaves + vi26->leaves->tmrs_seq_offset;
		if (generate_atui) {
		}
	} else {
		vi26->tmrs_seq = NULL;
	}

	atui_branch* atui_dram_data_remap = NULL;
	if (vi26->leaves->dram_data_remap_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi26->dram_data_remap =
			(void*)vi26->leaves + vi26->leaves->dram_data_remap_tbloffset;
		if (generate_atui) {
			atui_dram_data_remap = ATUI_MAKE_BRANCH(atom_gddr6_dram_data_remap,
				NULL,  NULL,vi26->dram_data_remap,  0,NULL
			);
		}
	} else {
		vi26->dram_data_remap = NULL;
	}

	atui_branch* atui_postucode_init = NULL;
	if (vi26->leaves->post_ucode_init_offset) {
		vi26->post_ucode_init.leaves =
			(void*)vi26->leaves + vi26->leaves->post_ucode_init_offset;
		atui_postucode_init = atomtree_populate_umc_init_reg_block(
			&(vi26->post_ucode_init), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_postucode_init->name, "post_ucode_init");
		}
	} else {
		vi26->post_ucode_init.leaves = NULL;
	}

	vi26->vram_module_ver = v1_9;
	atui_branch* atui_vrammodules = NULL;
	if (vi26->leaves->vram_module_num) {
		atui_vrammodules = atomtree_populate_vram_module(
			vram_info, generate_atui
		);
	}

	atui_branch* atui_vi = NULL;
	if (generate_atui) {
		atui_branch* const vi26_children[] = {
			atui_memadjust, atui_mcadjpertile, atui_phyinit,
			atui_dram_data_remap, atui_tmrs_seq, atui_postucode_init,
			atui_vrammodules,
		};
		atui_vi = ATUI_MAKE_BRANCH(atom_vram_info_header_v2_5,
			NULL,  vi26,vi26->leaves,
			(sizeof(vi26_children)/sizeof(atui_branch*)), vi26_children
		);
	}
	return atui_vi;
}

inline static atui_branch*
atomtree_populate_vram_info_v3_0(// TODO finish this
		struct atomtree_vram_info* vram_info,
		bool generate_atui
		) {
	struct atomtree_vram_info_header_v3_0* const vi30 = &(vram_info->v3_0);
	vi30->leaves = vram_info->leaves;

	uint16_t i = 0;
	atui_branch* tmp_branch = NULL;

	atui_branch* atui_mem_tuning = NULL;
	if (vi30->leaves->mem_tuning_table_offset) {
		vi30->mem_tuning =
			(void*)vi30->leaves + vi30->leaves->mem_tuning_table_offset;
	} else {
		vi30->mem_tuning = NULL;
	}

	atui_branch* atui_dram_info = NULL;
	if (vi30->leaves->dram_info_table_offset) {
		vi30->dram_info =
			(void*)vi30->leaves + vi30->leaves->dram_info_table_offset;
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
		vi30->mc_init.leaves =
			(void*)vi30->leaves + vi30->leaves->mc_init_table_offset;
		atui_mc_init = atomtree_populate_umc_init_reg_block(
			&(vi30->mc_init), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_mc_init->name, "mc_init_table");
		}
	} else {
		vi30->mc_init.leaves = NULL;
	}

	atui_branch* atui_dram_data_remap = NULL;
	if (vi30->leaves->dram_data_remap_table_offset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi30->dram_data_remap =
			(void*)vi30->leaves + vi30->leaves->dram_data_remap_table_offset;
		if (generate_atui) {
			atui_dram_data_remap = ATUI_MAKE_BRANCH(atom_gddr6_dram_data_remap,
				NULL,  NULL,vi30->dram_data_remap,  0,NULL
			);
		}
	} else {
		vi30->dram_data_remap = NULL;
	}

	atui_branch* atui_umc_emuinit = NULL;
	if (vi30->leaves->umc_emuinit_table_offset) {
		vi30->umc_emuinit.leaves =
			(void*)vi30->leaves + vi30->leaves->umc_emuinit_table_offset;
		atui_umc_emuinit = atomtree_populate_umc_init_reg_block(
			&(vi30->umc_emuinit), generate_atui, 0
		);
		if (generate_atui) {
			strcpy(atui_umc_emuinit->name, "umc_emuinit_table");
		}
	} else {
		vi30->umc_emuinit.leaves = NULL;
	}

	if (vi30->leaves->reserved_sub_table_offset[0]) {
		vi30->rsvd_tables[0] =
			(void*)vi30->leaves + vi30->leaves->reserved_sub_table_offset[0];
	} else {
		vi30->rsvd_tables[0] = NULL;
	}
	if (vi30->leaves->reserved_sub_table_offset[1]) {
		vi30->rsvd_tables[1] =
			(void*)vi30->leaves + vi30->leaves->reserved_sub_table_offset[1];
	} else {
		vi30->rsvd_tables[1] = NULL;
	}

	vi30->vram_module_ver = v3_0;
	atui_branch* atui_vrammodules = NULL;
	if (vi30->leaves->vram_module_num) {
		atui_vrammodules = atomtree_populate_vram_module(
			vram_info, generate_atui
		);
	}

	atui_branch* atui_vi = NULL;
	if (generate_atui) {
		atui_branch* const vi30_children[] = {
			atui_mem_tuning, atui_dram_info, atui_tmrs_seq, atui_mc_init,
			atui_dram_data_remap, atui_umc_emuinit, atui_vrammodules,
		};
		atui_vi = ATUI_MAKE_BRANCH(atom_vram_info_header_v3_0,
			NULL,  vi30,vi30->leaves,
			(sizeof(vi30_children)/sizeof(atui_branch*)), vi30_children
		);
	}
	return atui_vi;
}

inline static atui_branch*
atomtree_dt_populate_vram_info(
		struct atomtree_vram_info* vram_info,
		struct atom_tree* atree,
		uint16_t bios_offset,
		bool generate_atui
		) {
	atui_branch* atui_vi = NULL;

	if (bios_offset) {
		vram_info->leaves = atree->bios + bios_offset;
		vram_info->ver = get_ver(vram_info->table_header);
		switch (vram_info->ver) { // TODO: earlier tables than 2.3?
			case v1_2:
				atui_vi = atomtree_populate_vram_info_v1_2(
					vram_info, generate_atui
				);
				break;
			case v1_3:
				atui_vi = atomtree_populate_vram_info_v1_3(
					vram_info, generate_atui
				);
				break;
			case v1_4:
				atui_vi = atomtree_populate_vram_info_v1_4(
					vram_info, generate_atui
				);
				break;
			case v2_1:
				atui_vi = atomtree_populate_vram_info_v2_1(
					vram_info, generate_atui
				);
				break;
			case v2_2:
				atui_vi = atomtree_populate_vram_info_v2_2(
					vram_info, generate_atui
				);
				break;
			case v2_3:
				atui_vi = atomtree_populate_vram_info_v2_3(
					vram_info, generate_atui
				);
				break;
			case v2_4:
				atui_vi = atomtree_populate_vram_info_v2_4(
					vram_info, generate_atui
				);
				break;
			case v2_5:
				atui_vi = atomtree_populate_vram_info_v2_5(
					vram_info, generate_atui
				);
				break;
			case v2_6:
				atui_vi = atomtree_populate_vram_info_v2_6(
					vram_info, generate_atui
				);
				break;
			case v3_0:
				atui_vi = atomtree_populate_vram_info_v3_0(
					vram_info, generate_atui
				);
				break;
			default:
				if (generate_atui) {
					atui_vi = ATUI_MAKE_BRANCH(atom_common_table_header,
						"vram_info (header only stub)",
						NULL,vram_info->table_header,  0,NULL
					);
				}
				break;
		}
	} else {
		vram_info->leaves = NULL;
		vram_info->ver = nover;
	}
	return atui_vi;
}


inline static atui_branch*
atomtree_dt_populate_voltageobject_info_v4_1(
		struct atomtree_voltageobject_info* vo_info,
		bool generate_atui
		) {
	atui_branch* atui_vo_info = NULL;
	atui_branch* tmp_branch = NULL;
	uint16_t i;

	struct atomtree_voltageobject_info_v4_1* const vo41 = &(vo_info->v4_1);
	vo41->leaves = vo_info->leaves;

	// get the size ofthe dynamically-sized voltage object array, and walk
	// through the array based on what each element reports their size as.
	union atom_voltage_object_v4* vobj;
	uint16_t offset = 0;
	const uint16_t vo41_array_size = (
		vo41->leaves->table_header.structuresize
		- offsetof(struct atom_voltage_objects_info_v4_1, voltage_object[0])
	);
	void* const start = &(vo41->leaves->voltage_object[0]);
	i = 0;
	while (offset < vo41_array_size) {
		vobj = start + offset;

		assert(ATOMTREE_VOLTAGE_OBJECTS_MAX > i);
		vo41->voltage_objects[i].voltage_object = vobj;
		switch(vobj->header.voltage_mode) {
			// some voltage objects have a dynamically-sized lookup table.
			case VOLTAGE_OBJ_GPIO_LUT:
			case VOLTAGE_OBJ_PHASE_LUT:
				vo41->voltage_objects[i].lut_entries = (
					(vobj->header.object_size
						- offsetof(struct atom_gpio_voltage_object_v4,
							voltage_gpio_lut[0]
						)
					) / sizeof(struct atom_voltage_gpio_map_lut)
				);
				break;
			case VOLTAGE_OBJ_VR_I2C_INIT_SEQ:
				vo41->voltage_objects[i].lut_entries = (
					(vobj->header.object_size
						- offsetof(struct atom_i2c_voltage_object_v4,
							i2cdatalut[0]
						)
					) / sizeof(struct atom_i2c_data_entry)
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
			"atom_voltage_objects_info_v4_1",
			NULL,vo41->leaves,  vo41->num_voltage_objects,NULL
		);
		for (i=0; i < vo41->num_voltage_objects; i++) {
			at_vobj = &(vo41->voltage_objects[i]);
			switch(at_vobj->voltage_object->header.voltage_mode) {
				case VOLTAGE_OBJ_GPIO_LUT:
				case VOLTAGE_OBJ_PHASE_LUT:
					tmp_branch = ATUI_MAKE_BRANCH(atom_gpio_voltage_object_v4,
						NULL,
						at_vobj, &(at_vobj->voltage_object->gpio_voltage_obj),
						0, NULL
					);
					break;
				case VOLTAGE_OBJ_VR_I2C_INIT_SEQ:
					tmp_branch = ATUI_MAKE_BRANCH(atom_i2c_voltage_object_v4,
						NULL,
						at_vobj, &(at_vobj->voltage_object->i2c_voltage_obj),
						0, NULL
					);
					break;
				case VOLTAGE_OBJ_SVID2:
					tmp_branch = ATUI_MAKE_BRANCH(atom_svid2_voltage_object_v4,
						NULL,
						at_vobj, &(at_vobj->voltage_object->svid2_voltage_obj),
						0, NULL
					);
					break;
				case VOLTAGE_OBJ_MERGED_POWER:
					tmp_branch = ATUI_MAKE_BRANCH(atom_merged_voltage_object_v4,
						NULL,
						at_vobj, &(at_vobj->voltage_object->merged_voltage_obj),
						0, NULL
					);
					break;
				case VOLTAGE_OBJ_EVV: // TODO does this get used by v4?
				default:
					tmp_branch = ATUI_MAKE_BRANCH(atom_voltage_object_header_v4,
						NULL,
						at_vobj,&(at_vobj->voltage_object->header),  0,NULL
					);
					break;
			}
			sprintf(tmp_branch->name, "%s [%u]", tmp_branch->varname, i);
			ATUI_ADD_BRANCH(atui_vo_info, tmp_branch);
		}
	}
	return atui_vo_info;
}


inline static atui_branch*
atomtree_dt_populate_voltageobject_info(
		struct atomtree_voltageobject_info* vo_info,
		struct atom_tree* atree,
		uint16_t bios_offset,
		bool generate_atui
		) {
	atui_branch* atui_vo_info = NULL;

	if (bios_offset) {
		vo_info->leaves = atree->bios + bios_offset;
		vo_info->ver = get_ver(vo_info->table_header);
		switch (vo_info->ver) {
			case v4_1:
				atui_vo_info = atomtree_dt_populate_voltageobject_info_v4_1(
					vo_info, generate_atui
				);
				break;
			case v4_2: //hopefully v4_2 is the same
				atui_vo_info = atomtree_dt_populate_voltageobject_info_v4_1(
					vo_info, generate_atui
				);
				strcpy(atui_vo_info->name,
					"atom_voltage_objects_info_v4_1 (forced)"
				);
				break;
			default:
				if (generate_atui) {
					atui_vo_info = ATUI_MAKE_BRANCH(atom_common_table_header,
						"voltageobject_info (header only stub)",
						NULL,vo_info->table_header,  0,NULL
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


inline static atui_branch*
atomtree_populate_master_datatable_v1_1(
		struct atomtree_master_datatable* data_table,
		struct atom_tree* atree,
		bool generate_atui
		) {
	void* const bios = atree->bios;
	struct atomtree_master_datatable_v1_1* const dt11 = &(data_table->v1_1);
	dt11->leaves = data_table->leaves;
	struct atom_master_data_table_v1_1* const leaves = data_table->leaves;

	atui_branch* const atui_utilitypipeline = NULL;
	if (leaves->UtilityPipeLine) {
		dt11->utilitypipeline = bios + leaves->UtilityPipeLine;
	} else {
		dt11->utilitypipeline = NULL;
	}

	atui_branch* const atui_multimedia_capability_info = NULL; // TODO
	if (leaves->MultimediaCapabilityInfo) {
		dt11->multimedia_capability_info =
			bios + leaves->MultimediaCapabilityInfo;
	} else {
		dt11->multimedia_capability_info = NULL;
	}
	atui_branch* const atui_multimedia_config_info = NULL;
	if (leaves->MultimediaConfigInfo) {
		dt11->multimedia_config_info =
			bios + leaves->MultimediaConfigInfo;
	} else {
		dt11->multimedia_config_info = NULL;
	}

	atui_branch* const atui_vesa_timing = NULL;
	if (leaves->StandardVESA_Timing) {
		dt11->vesa_timing = bios + leaves->StandardVESA_Timing;
	} else {
		dt11->vesa_timing = NULL;
	}

	atui_branch* const atui_firmwareinfo = atomtree_dt_populate_firmwareinfo(
		&(dt11->firmwareinfo), atree, leaves->FirmwareInfo, generate_atui
	);

	atui_branch* const atui_palette_data = NULL;
	if (leaves->PaletteData) {
		dt11->palette_data = bios + leaves->PaletteData;
	} else {
		dt11->palette_data = NULL;
	}

	atui_branch* const atui_lcd_info = atomtree_dt_populate_lcd_info(
		&(dt11->lcd_info), atree, leaves->LCD_Info, generate_atui
	);

	atui_branch* const atui_dig_transmitter_info = NULL;
	if (leaves->DIGTransmitterInfo) {
		dt11->dig_transmitter_info = bios + leaves->DIGTransmitterInfo;
	} else {
		dt11->dig_transmitter_info = NULL;
	}

	atui_branch* const atui_smu_info = atomtree_dt_populate_smu_info(
		&(dt11->smu_info), atree, leaves->SMU_Info, generate_atui
	);

	atui_branch* const atui_supported_devices_info = NULL;
	if (leaves->SupportedDevicesInfo) {
		dt11->supported_devices_info = bios + leaves->SupportedDevicesInfo;
	} else {
		dt11->supported_devices_info = NULL;
	}

	atui_branch* const atui_gpio_i2c_info = NULL;
	if (leaves->GPIO_I2C_Info) {
		dt11->gpio_i2c_info = bios + leaves->GPIO_I2C_Info;
	} else {
		dt11->gpio_i2c_info = NULL;
	}

	atui_branch* const atui_fw_vram = atomtree_dt_populate_vram_usagebyfirmware(
		&(dt11->vram_usagebyfirmware), atree,
		leaves->VRAM_UsageByFirmware, generate_atui
	);

	atui_branch* const atui_gpio_pin_lut = atomtree_dt_populate_gpio_pin_lut(
		&(dt11->gpio_pin_lut), atree, leaves->GPIO_Pin_LUT, generate_atui
	);

	atui_branch* const atui_vesa_to_internal_mode = NULL;
	if (leaves->VESA_ToInternalModeLUT) {
		dt11->vesa_to_internal_mode = bios + leaves->VESA_ToInternalModeLUT;
	} else {
		dt11->vesa_to_internal_mode = NULL;
	}

	atui_branch* const atui_gfx_info = atomtree_dt_populate_gfx_info(
		&(dt11->gfx_info), atree, leaves->GFX_Info, generate_atui
	);

	atui_branch* const atui_ppt = atomtree_dt_populate_ppt(
		&(dt11->powerplayinfo), atree,
		leaves->PowerPlayInfo, generate_atui
	);

	atui_branch* const atui_gpu_virtualization_info = NULL;
	if (leaves->GPUVirtualizationInfo) {
		dt11->gpu_virtualization_info = bios + leaves->GPUVirtualizationInfo;
	} else {
		dt11->gpu_virtualization_info = NULL;
	}

	atui_branch* const atui_save_restore_info = NULL;
	if (leaves->SaveRestoreInfo) {
		dt11->save_restore_info = bios + leaves->SaveRestoreInfo;
	} else {
		dt11->save_restore_info = NULL;
	}

	atui_branch* const atui_ppll_ss_info = NULL;
	if (leaves->PPLL_SS_Info) {
		dt11->ppll_ss_info = bios + leaves->PPLL_SS_Info;
	} else {
		dt11->ppll_ss_info = NULL;
	}

	atui_branch* const atui_oem_info = NULL;
	if (leaves->OemInfo) {
		dt11->oem_info = bios + leaves->OemInfo;
	} else {
		dt11->oem_info = NULL;
	}

	atui_branch* const atui_xtmds_info = NULL;
	if (leaves->XTMDS_Info) {
		dt11->xtmds_info = bios + leaves->XTMDS_Info;
	} else {
		dt11->xtmds_info = NULL;
	}

	atui_branch* const atui_mclk_ss_info = NULL;
	if (leaves->MclkSS_Info) {
		dt11->mclk_ss_info = bios + leaves->MclkSS_Info;
	} else {
		dt11->mclk_ss_info = NULL;
	}

	atui_branch* const atui_object_header = NULL;
	if (leaves->Object_Header) {
		dt11->object_header = bios + leaves->Object_Header;
	} else {
		dt11->object_header = NULL;
	}

	atui_branch* const atui_indirect_io_access = NULL;
	if (leaves->IndirectIOAccess) {
		dt11->indirect_io_access = bios + leaves->IndirectIOAccess;
	} else {
		dt11->indirect_io_access = NULL;
	}

	atui_branch* const atui_mc_init_parameter = NULL;
	if (leaves->MC_InitParameter) {
		dt11->mc_init_parameter = bios + leaves->MC_InitParameter;
	} else {
		dt11->mc_init_parameter = NULL;
	}

	atui_branch* const atui_asic_vddc_info = NULL;
	if (leaves->ASIC_VDDC_Info) {
		dt11->asic_vddc_info = bios + leaves->ASIC_VDDC_Info;
	} else {
		dt11->asic_vddc_info = NULL;
	}

	atui_branch* const atui_asic_internal_ss_info = NULL;
	if (leaves->ASIC_InternalSS_Info) {
		dt11->asic_internal_ss_info = bios + leaves->ASIC_InternalSS_Info;
	} else {
		dt11->asic_internal_ss_info = NULL;
	}

	atui_branch* const atui_tv_video_mode = NULL;
	if (leaves->TV_VideoMode) {
		dt11->tv_video_mode = bios + leaves->TV_VideoMode;
	} else {
		dt11->tv_video_mode = NULL;
	}

	atui_branch* const atui_vram_info = atomtree_dt_populate_vram_info(
		&(dt11->vram_info), atree, leaves->VRAM_Info, generate_atui
	);

	atui_branch* const atui_memory_training_info = NULL;
	if (leaves->MemoryTrainingInfo) {
		dt11->memory_training_info = bios + leaves->MemoryTrainingInfo;
	} else {
		dt11->memory_training_info = NULL;
	}

	atui_branch* const atui_integrated_system_info = NULL;
	if (leaves->IntegratedSystemInfo) {
		dt11->integrated_system_info = bios + leaves->IntegratedSystemInfo;
	} else {
		dt11->integrated_system_info = NULL;
	}

	atui_branch* const atui_asic_profiling_info = NULL;
	if (leaves->ASIC_ProfilingInfo) {
		dt11->asic_profiling_info = bios + leaves->ASIC_ProfilingInfo;
	} else {
		dt11->asic_profiling_info = NULL;
	}

	atui_branch* const atui_voltageobject_info =
		atomtree_dt_populate_voltageobject_info(
			&(dt11->voltageobject_info), atree,
			leaves->VoltageObjectInfo, generate_atui
		);

	atui_branch* const atui_power_source_info = NULL;
	if (leaves->PowerSourceInfo) {
		dt11->power_source_info = bios + leaves->PowerSourceInfo;
	} else {
		dt11->power_source_info = NULL;
	}

	atui_branch* const atui_service_info = NULL;
	if (leaves->ServiceInfo) {
		dt11->service_info = bios + leaves->ServiceInfo;
	} else {
		dt11->service_info = NULL;
	}

	atui_branch* atui_dt = NULL;
	if (generate_atui) {
		atui_branch* const child_branches[] = {
			atui_firmwareinfo, atui_lcd_info, atui_smu_info,
			atui_fw_vram, atui_gpio_pin_lut, atui_gfx_info, atui_ppt,
			atui_vram_info,
			atui_voltageobject_info
		};
		atui_dt = ATUI_MAKE_BRANCH(atom_master_data_table_v1_1,
			NULL,  dt11,dt11->leaves,
			(sizeof(child_branches)/sizeof(atui_branch*)), child_branches
		);
	}
	return atui_dt;
}

inline static atui_branch*
atomtree_datatable_v2_1_populate_sw_datatables(
		struct atomtree_master_datatable_v2_1* data_table,
		struct atom_tree* atree,
		bool generate_atui
		) {
	// TODO have a table with a bunch of ATUI_INLINEs pointing at headers

	struct atom_master_data_table_v2_1* const leaves = data_table->leaves;
	void* const bios = atree->bios;

	data_table->sw_datatable3.leaves = NULL;
	if (leaves->sw_datatable3) {
		data_table->sw_datatable3.leaves = bios + leaves->sw_datatable3;
	}

	data_table->sw_datatable5.leaves = NULL;
	if (leaves->sw_datatable5) {
		data_table->sw_datatable5.leaves = bios + leaves->sw_datatable5;
	}

	data_table->sw_datatable7.leaves = NULL;
	if (leaves->sw_datatable7) {
		data_table->sw_datatable7.leaves = bios + leaves->sw_datatable7;
	}

	data_table->sw_datatable9.leaves = NULL;
	if (leaves->sw_datatable9) {
		data_table->sw_datatable9.leaves = bios + leaves->sw_datatable9;
	}

	data_table->sw_datatable10.leaves = NULL;
	if (leaves->sw_datatable10) {
		data_table->sw_datatable10.leaves = bios + leaves->sw_datatable10;
	}

	data_table->sw_datatable13.leaves = NULL;
	if (leaves->sw_datatable13) {
		data_table->sw_datatable13.leaves = bios + leaves->sw_datatable13;
	}

	data_table->sw_datatable16.leaves = NULL;
	if (leaves->sw_datatable16) {
		data_table->sw_datatable16.leaves = bios + leaves->sw_datatable16;
	}

	data_table->sw_datatable17.leaves = NULL;
	if (leaves->sw_datatable17) {
		data_table->sw_datatable17.leaves = bios + leaves->sw_datatable17;
	}

	data_table->sw_datatable18.leaves = NULL;
	if (leaves->sw_datatable18) {
		data_table->sw_datatable18.leaves = bios + leaves->sw_datatable18;
	}

	data_table->sw_datatable19.leaves = NULL;
	if (leaves->sw_datatable19) {
		data_table->sw_datatable19.leaves = bios + leaves->sw_datatable19;
	}

	data_table->sw_datatable20.leaves = NULL;
	if (leaves->sw_datatable20) {
		data_table->sw_datatable20.leaves = bios + leaves->sw_datatable20;
	}

	data_table->sw_datatable21.leaves = NULL;
	if (leaves->sw_datatable21) {
		data_table->sw_datatable21.leaves = bios + leaves->sw_datatable21;
	}

	data_table->sw_datatable25.leaves = NULL;
	if (leaves->sw_datatable25) {
		data_table->sw_datatable25.leaves = bios + leaves->sw_datatable25;
	}

	data_table->sw_datatable26.leaves = NULL;
	if (leaves->sw_datatable26) {
		data_table->sw_datatable26.leaves = bios + leaves->sw_datatable26;
	}

	data_table->sw_datatable29.leaves = NULL;
	if (leaves->sw_datatable29) {
		data_table->sw_datatable29.leaves = bios + leaves->sw_datatable29;
	}

	data_table->sw_datatable33.leaves = NULL;
	if (leaves->sw_datatable33) {
		data_table->sw_datatable33.leaves = bios + leaves->sw_datatable33;
	}

	data_table->sw_datatable34.leaves = NULL;
	if (leaves->sw_datatable34) {
		data_table->sw_datatable34.leaves = bios + leaves->sw_datatable34;
	}

	return NULL;
}
inline static atui_branch*
atomtree_populate_master_datatable_v2_1(
		struct atomtree_master_datatable* data_table,
		struct atom_tree* atree,
		bool generate_atui
		) {
	void* const bios = atree->bios;
	struct atomtree_master_datatable_v2_1* const dt21 = &(data_table->v2_1);
	dt21->leaves = data_table->leaves;
	struct atom_master_data_table_v2_1* const leaves = data_table->leaves;

	atui_branch* const atui_utilitypipeline = NULL;
	if (leaves->utilitypipeline) {
		dt21->utilitypipeline = bios + leaves->utilitypipeline;
	} else {
		dt21->utilitypipeline = NULL;
	}

	atui_branch* const atui_multimedia_info = NULL;
	if (leaves->multimedia_info) {
		dt21->multimedia_info = bios + leaves->multimedia_info;
	} else {
		dt21->multimedia_info = NULL;
	}

	atui_branch* const atui_smc_dpm_info = atomtree_dt_populate_smc_dpm_info(
		&(dt21->smc_dpm_info), atree, leaves->smc_dpm_info, generate_atui
	);

	atui_branch* const atui_firmwareinfo = atomtree_dt_populate_firmwareinfo(
		&(dt21->firmwareinfo), atree, leaves->firmwareinfo, generate_atui
	);

	atui_branch* const atui_lcd_info = atomtree_dt_populate_lcd_info(
		&(dt21->lcd_info), atree, leaves->lcd_info, generate_atui
	);

	atui_branch* const atui_smu_info = atomtree_dt_populate_smu_info(
		&(dt21->smu_info), atree, leaves->smu_info, generate_atui
	);

	atui_branch* const atui_fw_vram = atomtree_dt_populate_vram_usagebyfirmware(
		&(dt21->vram_usagebyfirmware), atree,
		leaves->vram_usagebyfirmware, generate_atui
	);

	atui_branch* const atui_gpio_pin_lut = atomtree_dt_populate_gpio_pin_lut(
		&(dt21->gpio_pin_lut), atree, leaves->gpio_pin_lut, generate_atui
	);

	atui_branch* const atui_gfx_info = atomtree_dt_populate_gfx_info(
		&(dt21->gfx_info), atree, leaves->gfx_info, generate_atui
	);

	atui_branch* const atui_ppt = atomtree_dt_populate_ppt(
		&(dt21->powerplayinfo), atree,
		leaves->powerplayinfo, generate_atui
	);

	//displayobjectinfo
	//indirectioaccess
	//umc_info
	//dce_info

	atui_branch* const atui_vram_info = atomtree_dt_populate_vram_info(
		&(dt21->vram_info), atree, leaves->vram_info, generate_atui
	);

	//integratedsysteminfo
	//asic_profiling_info
	//voltageobject_info
	atui_branch* const atui_voltageobject_info =
		atomtree_dt_populate_voltageobject_info(
			&(dt21->voltageobject_info), atree,
			leaves->voltageobject_info, generate_atui
		);

	atomtree_datatable_v2_1_populate_sw_datatables(dt21, atree, generate_atui);

	atui_branch* atui_dt = NULL;
	if (generate_atui) {
		atui_branch* const child_branches[] = {
			// utility, multimedia
			atui_smc_dpm_info, atui_firmwareinfo, atui_lcd_info, atui_smu_info,
			atui_fw_vram, atui_gpio_pin_lut, atui_gfx_info, atui_ppt,
			// disp obj, indirect, umc, dce,
			atui_vram_info,
			// integrated, asic
			atui_voltageobject_info
		};
		atui_dt = ATUI_MAKE_BRANCH(atom_master_data_table_v2_1,
			NULL,  dt21,dt21->leaves,
			(sizeof(child_branches)/sizeof(atui_branch*)), child_branches
		);
	}
	return atui_dt;
}

inline static atui_branch*
atomtree_populate_datatables(
		//struct atomtree_master_datatable* data_table,
		struct atom_tree* atree,
		uint16_t bios_offset,
		bool generate_atui
		) {
	struct atomtree_master_datatable* const data_table = &(atree->data_table);
	atui_branch* atui_dt = NULL;

	if (bios_offset) {
		data_table->leaves = atree->bios + bios_offset;
		data_table->ver = get_ver(data_table->table_header);
		switch (data_table->ver) {
			case v1_1:
				atui_dt = atomtree_populate_master_datatable_v1_1(
					data_table, atree, generate_atui
				);
				break;
			case v2_1:
				atui_dt = atomtree_populate_master_datatable_v2_1(
					data_table, atree, generate_atui
				);
				break;
			default:
				if (generate_atui) {
					atui_dt = ATUI_MAKE_BRANCH(
						atom_common_table_header,
						"atom_master_data_table (header only stub)",
						NULL, data_table->table_header,  0,NULL
					);
				}
				break;
		}
	} else {
		data_table->leaves = NULL;
		data_table->ver = nover;
	}

	return atui_dt;
}


inline static atui_branch*
atomtree_populate_atom_rom_header_v1_1(
		 struct atomtree_rom_header* rom_header,
		struct atom_tree* atree,
		bool generate_atui
		) {
	struct atom_rom_header_v1_1* const leaves = rom_header->v1_1;
	void* const bios = atree->bios;

	if (leaves->ProtectedModeInfoOffset) {
		atree->protected_mode = bios + leaves->ProtectedModeInfoOffset;
	} else {
		atree->protected_mode = NULL;
	}
	if (leaves->ConfigFilenameOffset) {
		atree->config_filename = bios + leaves->ConfigFilenameOffset;
	} else {
		atree->config_filename = NULL;
	}
	if (leaves->CRC_BlockOffset) {
		atree->crc_block = bios + leaves->CRC_BlockOffset;
	} else {
		atree->crc_block = NULL;
	}
	if (leaves->BIOS_BootupMessageOffset) {
		atree->bootup_mesage = bios + leaves->BIOS_BootupMessageOffset;
	} else {
		atree->bootup_mesage = NULL;
	}
	if (leaves->Int10Offset) {
		atree->int10 = bios + leaves->Int10Offset;
	} else {
		atree->int10 = NULL;
	}
	if (leaves->PCI_InfoOffset) {
		atree->pci_info = bios + leaves->PCI_InfoOffset;
	} else {
		atree->pci_info = NULL;
	}

	atree->psp_dir_table = NULL;
	

	//rom_header->data_table = &(atree->data_table);
	atui_branch* const atui_dt = atomtree_populate_datatables(
		atree, leaves->MasterDataTableOffset, generate_atui
	);

	atui_branch* atui_rom_header = NULL;
	if (generate_atui) {
		atui_rom_header = ATUI_MAKE_BRANCH(atom_rom_header_v1_1,
			NULL,  NULL,rom_header->v1_1,
			1, &atui_dt
		);
	}
	return atui_rom_header;
}

inline static atui_branch*
atomtree_populate_atom_rom_header_v2_1(
		 struct atomtree_rom_header* rom_header,
		struct atom_tree* atree,
		bool generate_atui
		) {
	struct atom_rom_header_v2_1* const leaves = rom_header->v2_1;
	void* const bios = atree->bios;

	if (leaves->ProtectedModeInfoOffset) {
		atree->protected_mode = bios + leaves->ProtectedModeInfoOffset;
	} else {
		atree->protected_mode = NULL;
	}
	if (leaves->ConfigFilenameOffset) {
		atree->config_filename = bios + leaves->ConfigFilenameOffset;
	} else {
		atree->config_filename = NULL;
	}
	if (leaves->CRC_BlockOffset) {
		atree->crc_block = bios + leaves->CRC_BlockOffset;
	} else {
		atree->crc_block = NULL;
	}
	if (leaves->BIOS_BootupMessageOffset) {
		atree->bootup_mesage = bios + leaves->BIOS_BootupMessageOffset;
	} else {
		atree->bootup_mesage = NULL;
	}
	if (leaves->Int10Offset) {
		atree->int10 = bios + leaves->Int10Offset;
	} else {
		atree->int10 = NULL;
	}
	if (leaves->PCI_InfoOffset) {
		atree->pci_info = bios + leaves->PCI_InfoOffset;
	} else {
		atree->pci_info = NULL;
	}
	if (leaves->PSPDirTableOffset) {
		atree->psp_dir_table = bios + leaves->PSPDirTableOffset;
	} else {
		atree->psp_dir_table = NULL;
	}
	

	//rom_header->data_table = &(atree->data_table);
	atui_branch* const atui_dt = atomtree_populate_datatables(
		atree, leaves->MasterDataTableOffset, generate_atui
	);

	atui_branch* atui_rom_header = NULL;
	if (generate_atui) {
		atui_rom_header = ATUI_MAKE_BRANCH(atom_rom_header_v2_1,
			NULL,  NULL,rom_header->v2_1,
			1, &atui_dt
		);
	}
	return atui_rom_header;
}

inline static atui_branch*
atomtree_populate_atom_rom_header_v2_2(
		 struct atomtree_rom_header* rom_header,
		struct atom_tree* atree,
		bool generate_atui
		) {
	struct atom_rom_header_v2_2* const leaves = rom_header->v2_2;
	void* const bios = atree->bios;

	if (leaves->protectedmodeoffset) {
		atree->protected_mode = bios + leaves->protectedmodeoffset;
	} else {
		atree->protected_mode = NULL;
	}
	if (leaves->configfilenameoffset) {
		atree->config_filename = bios + leaves->configfilenameoffset;
	} else {
		atree->config_filename = NULL;
	}
	if (leaves->crc_block_offset) {
		atree->crc_block = bios + leaves->crc_block_offset;
	} else {
		atree->crc_block = NULL;
	}
	if (leaves->vbios_bootupmessageoffset) {
		atree->bootup_mesage = bios + leaves->vbios_bootupmessageoffset;
	} else {
		atree->bootup_mesage = NULL;
	}
	if (leaves->int10_offset) {
		atree->int10 = bios + leaves->int10_offset;
	} else {
		atree->int10 = NULL;
	}
	if (leaves->pci_info_offset) {
		atree->pci_info = bios + leaves->pci_info_offset;
	} else {
		atree->pci_info = NULL;
	}
	if (leaves->pspdirtableoffset) {
		atree->psp_dir_table = bios + leaves->pspdirtableoffset;
	} else {
		atree->psp_dir_table = NULL;
	}
	

	//rom_header->data_table = &(atree->data_table);
	atui_branch* const atui_dt = atomtree_populate_datatables(
		atree, leaves->masterdatatable_offset, generate_atui
	);

	atui_branch* atui_rom_header = NULL;
	if (generate_atui) {
		atui_rom_header = ATUI_MAKE_BRANCH(atom_rom_header_v2_2,
			NULL,  NULL,rom_header->v2_2,
			1, &atui_dt
		);
	}
	return atui_rom_header;
	/*
	//atree->crc_block = bios + atree->leaves->crc_block_offset;
	TODO what are these locations?
	TODO double-check if all rom_header has same place as v2.1
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
			crc: 0x7F5E715 0x7F5E7150

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
}

inline static atui_branch*
atomtree_populate_atom_rom_header(
		struct atomtree_rom_header* rom_header,
		struct atom_tree* atree,
		uint16_t offset,
		bool generate_atui
		) {
		atui_branch* atui_rom_header = NULL;

		if (offset) {
			rom_header->leaves = atree->bios + offset;
			rom_header->ver = get_ver(rom_header->table_header);
			switch (rom_header->ver) {
				case v1_1:
					atui_rom_header = atomtree_populate_atom_rom_header_v1_1(
						rom_header, atree, generate_atui
					);
					break;
				case v2_1:
					atui_rom_header = atomtree_populate_atom_rom_header_v2_1(
						rom_header, atree, generate_atui
					);
					break;
				case v2_2:
					atui_rom_header = atomtree_populate_atom_rom_header_v2_2(
						rom_header, atree, generate_atui
					);
					break;
				case v2_3: // forced
					atui_rom_header = atomtree_populate_atom_rom_header_v2_2(
						rom_header, atree, generate_atui
					);
					if (generate_atui) {
						sprintf(atui_rom_header->name, "%s (forced)",
							atui_rom_header->varname
						);
					}
					break;
				default:
					if (generate_atui) {
						atui_rom_header = ATUI_MAKE_BRANCH(
							atom_common_table_header,
							"atom_rom_header (header only stub)",
							NULL, rom_header->table_header,  0,NULL
						);
					}
					break;
			}
		} else {
			rom_header->leaves = NULL;
			rom_header->ver = nover;
		}

	return atui_rom_header;
}


inline static void*
bios_fastforward(
		void* biosfile,
		const uint32_t size
		) {
	const struct atombios_image* image;
	const void* const end = biosfile + size;
	while (biosfile < end) {
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


struct atom_tree*
atombios_parse(
		void* alloced_bios,
		uint32_t allocsize,
		bool generate_atui
		) {
	void* const bios = bios_fastforward(alloced_bios, allocsize);
	if (bios == NULL) {
		return NULL;
	}
	struct atombios_image* const image = bios;
	struct atom_tree* const atree = malloc(sizeof(struct atom_tree));

	atree->biosfile = NULL;
	atree->biosfile_size = 0;
	atree->alloced_bios = alloced_bios;

	atree->bios = bios; //PIC code; going to be used as the '0' in places.
	atree->bios_image_size = image->image_size * BIOS_IMAGE_SIZE_UNIT;

	uint8_t* strs = atree->bios + image->atombios_strings_offset;
	uint8_t num_of_crawled_strings = 0;
	while (*strs) { // the last string ends with 00 00
		assert(num_of_crawled_strings < NUM_ATOMBIOS_STRINGS); // see def
		atree->atombios_strings[num_of_crawled_strings] = strs;
		num_of_crawled_strings++;
		strs += (strlen(strs) + 1);
	}
	atree->num_of_crawled_strings = num_of_crawled_strings;

	atui_branch* const atui_rom_header = atomtree_populate_atom_rom_header(
		&(atree->rom_header), atree, image->bios_header, generate_atui
	);

	// atomtree_populate_commandtables(atree); // TODO

	if (generate_atui) {
		atui_branch* const atui_atom_image = ATUI_MAKE_BRANCH(atombios_image,
			 NULL,  atree, atree->image,  1,&atui_rom_header
		);
		atree->atui_root = atui_atom_image;
	} else {
		atree->atui_root = NULL;
	}

	return atree;
}


inline enum atomtree_common_version
get_ver(
		struct atom_common_table_header* header
		) {
	return (header->format_revision * 100) + header->content_revision;
}
inline void
set_ver(
		enum atomtree_common_version ver,
		struct atom_common_table_header* header
		) {
	header->format_revision = ver / 100;
	header->content_revision = ver % 100;
};


void
atomtree_bios_checksum(
		struct atom_tree* atree
		) {
	const uint8_t* const bios = atree->bios;
	const uint32_t bios_size = atree->bios_image_size;
	uint8_t offset = 0;

	for (uint32_t i=0; i < bios_size; i++) {
		offset += bios[i];
	}

	atree->image->checksum -= offset;
}
