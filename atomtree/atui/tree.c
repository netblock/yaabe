/* For atomtree's abstract, check out atomtree_data_tables.h */

#include "standard.h"
#include "atomtree.h"
#include "atui.h"

inline static atui_branch*
grow_smc_dpm_info(
		struct atomtree_smc_dpm_info* const smc_dpm_info,
		struct atom_tree* const atree __unused
		) {
	if (NULL == smc_dpm_info->leaves) {
		return NULL;
	}

	atuifunc atui_func;
	struct atui_funcify_args atui_args = {
		.atomtree = smc_dpm_info,
		.suggestbios = smc_dpm_info->leaves,
	};
	switch (smc_dpm_info->ver) {
		case v4_1:  atui_func = ATUI_FUNC(atom_smc_dpm_info_v4_1);  break;
		case v4_3:  atui_func = ATUI_FUNC(atom_smc_dpm_info_v4_3);  break;
		case v4_4:  atui_func = ATUI_FUNC(atom_smc_dpm_info_v4_4);  break;
		case v4_5:  atui_func = ATUI_FUNC(atom_smc_dpm_info_v4_5);  break;
		case v4_6:  atui_func = ATUI_FUNC(atom_smc_dpm_info_v4_6);  break;
		case v4_7:  atui_func = ATUI_FUNC(atom_smc_dpm_info_v4_7);  break;
		case v4_9:  atui_func = ATUI_FUNC(atom_smc_dpm_info_v4_9);  break;
		case v4_10: atui_func = ATUI_FUNC(atom_smc_dpm_info_v4_10); break;
		case v5_0:  atui_func = ATUI_FUNC(atom_smc_dpm_info_table_13_0_7);break;
		default:
			atui_args.rename = "smc_dpm_info (header only stub)";
			atui_func = ATUI_FUNC(atom_common_table_header);
			break;
	}
	return atui_func(&atui_args);
}


inline static atui_branch*
grow_firmwareinfo(
		struct atomtree_firmware_info* const firmwareinfo,
		struct atom_tree* const atree __unused
		) {
	if (NULL == firmwareinfo->leaves) {
		return NULL;
	}

	atuifunc atui_func;
	struct atui_funcify_args atui_args = {
		.atomtree = firmwareinfo,
		.suggestbios = firmwareinfo->leaves,
	};
	switch (firmwareinfo->ver) {
		case v1_0: atui_func = ATUI_FUNC(atom_firmware_info_v1_0); break;
		case v1_2: atui_func = ATUI_FUNC(atom_firmware_info_v1_2); break;
		case v1_3: atui_func = ATUI_FUNC(atom_firmware_info_v1_3); break;
		case v1_4: atui_func = ATUI_FUNC(atom_firmware_info_v1_4); break;
		case v2_1: atui_func = ATUI_FUNC(atom_firmware_info_v2_1); break;
		case v2_2: atui_func = ATUI_FUNC(atom_firmware_info_v2_2); break;
		case v3_1: atui_func = ATUI_FUNC(atom_firmware_info_v3_1); break;
		case v3_2: atui_func = ATUI_FUNC(atom_firmware_info_v3_2); break;
		case v3_3: atui_func = ATUI_FUNC(atom_firmware_info_v3_3); break;
		case v3_4: atui_func = ATUI_FUNC(atom_firmware_info_v3_4); break;
		default:
			atui_args.rename = "firmwareinfo (header only stub)";
			atui_func = ATUI_FUNC(atom_common_table_header);
			break;
	}
	return atui_func(&atui_args);
}


inline static atui_branch*
grow_lcd_info(
		struct atomtree_lcd_info* const lcd_info,
		struct atom_tree* const atree __unused
		) {
	if (NULL == lcd_info->leaves) {
		return NULL;
	}

	atuifunc atui_func;
	struct atui_funcify_args atui_args = {
		.atomtree =  lcd_info,
		.suggestbios = lcd_info->leaves,
	};
	switch (lcd_info->ver) {
		case v1_1: atui_func = ATUI_FUNC(atom_lvds_info_v1_1);
			// TODO atom_lvds_info_v1_1's ModePatchTableOffset;
			// see amdgpu_atombios_encoder_get_lcd_info
			assert(0);
			break;
		case v1_2: atui_func = ATUI_FUNC(atom_lvds_info_v1_2); break;
		case v1_3: atui_func = ATUI_FUNC(atom_lcd_info_v1_3);  break;
		case v2_1: atui_func = ATUI_FUNC(atom_lcd_info_v2_1);  break;
		default:
			atui_args.rename = "lcd_info (header only stub)";
			atui_func = ATUI_FUNC(atom_common_table_header);
			break;
	}
	return atui_func(&atui_args);
}


inline static atui_branch*
grow_smu_info(
		struct atomtree_smu_info* const smu_info,
		struct atom_tree* const atree __unused
		) {
	if (NULL == smu_info->leaves) {
		return NULL;
	}

	atuifunc atui_func;
	struct atui_funcify_args atui_args = {
		.atomtree =  smu_info,
		.suggestbios = smu_info->leaves,
	};
	switch (smu_info->ver) {
		case v3_1: atui_func = ATUI_FUNC(atom_smu_info_v3_1); break;
		case v3_2: atui_func = ATUI_FUNC(atom_smu_info_v3_2); break;
		case v3_3: atui_func = ATUI_FUNC(atom_smu_info_v3_3); break;
		case v3_4: atui_args.rename = "atom_smu_info_v3_5 (forced)"; fall;
		case v3_5: atui_func = ATUI_FUNC(atom_smu_info_v3_5); break;
		case v3_6: atui_func = ATUI_FUNC(atom_smu_info_v3_6); break;
		case v4_0: atui_func = ATUI_FUNC(atom_smu_info_v4_0); break;
		default:
			atui_func = ATUI_FUNC(atom_common_table_header);
			atui_args.rename = "smu_info (header only stub)";
			break;
	}
	return atui_func(&atui_args);
}


inline static atui_branch*
grow_vram_usagebyfirmware(
		struct atomtree_vram_usagebyfirmware* const fw_vram,
		struct atom_tree* const atree __unused
		) {
	if (NULL == fw_vram->leaves) {
		return NULL;
	}

	atuifunc atui_func;
	struct atui_funcify_args atui_args = {
		.atomtree =  fw_vram,
		.suggestbios = fw_vram->leaves,
	};
	switch (fw_vram->ver) {
		case v2_1: atui_func = ATUI_FUNC(vram_usagebyfirmware_v2_1); break;
		case v2_2: atui_func = ATUI_FUNC(vram_usagebyfirmware_v2_2); break;
		default:
			atui_func = ATUI_FUNC(atom_common_table_header);
			atui_args.rename = "vram_usagebyfirmware (header only stub)";
			break;
	}
	return atui_func(&atui_args);
}


inline static atui_branch*
grow_gpio_pin_lut(
		struct atomtree_gpio_pin_lut* const gpio_pin_lut,
		struct atom_tree* const atree __unused
		) {
	if (NULL == gpio_pin_lut->leaves) {
		return NULL;
	}

	atuifunc atui_func;
	struct atui_funcify_args atui_args = {
		.atomtree =  gpio_pin_lut,
		.suggestbios = gpio_pin_lut->leaves,
	};
	switch (gpio_pin_lut->ver) {
		case v2_1: atui_func = ATUI_FUNC(atom_gpio_pin_lut_v2_1); break;
		default:
			atui_func = ATUI_FUNC(atom_common_table_header);
			atui_args.rename = "gpio_pin_lut (header only stub)";
			break;
	}
	return atui_func(&atui_args);
}


inline static atui_branch*
grow_gfx_info(
		struct atomtree_gfx_info* const gfx_info,
		struct atom_tree* const atree __unused
		) {
	if (NULL == gfx_info->leaves) {
		return NULL;
	}

	atuifunc atui_func;
	atui_branch* subtables[2] = {NULL};
	struct atui_funcify_args atui_args = {
		.atomtree =  gfx_info,
		.suggestbios = gfx_info->leaves,
		.import_branches = subtables,
		.num_import_branches = lengthof(subtables),
	};

	switch (gfx_info->ver) {
		case v2_1: atui_func = ATUI_FUNC(atom_gfx_info_v2_1); break;
		case v2_2: atui_func = ATUI_FUNC(atom_gfx_info_v2_2); break;
		case v2_3:
			if (gfx_info->table_header->structuresize
					== sizeof(*gfx_info->v2_3)
					) {
				atui_func = ATUI_FUNC(atom_gfx_info_v2_3);
				if (gfx_info->edc_didt_lo) {
					subtables[0] = ATUI_MAKE_BRANCH(
						dpm7_atomctrl_edc_leakge_table,  NULL,
						NULL,gfx_info->edc_didt_lo,  0,NULL
					);
				}
				if (gfx_info->edc_didt_hi) {
					subtables[1] = ATUI_MAKE_BRANCH(
						dpm7_atomctrl_edc_leakge_table,  NULL,
						NULL,gfx_info->edc_didt_hi,  0,NULL
					);
				}
			} else {
				atui_func = ATUI_FUNC(atom_gfx_info_v2_3_2);
			}
			break;
		case v2_4: atui_func = ATUI_FUNC(atom_gfx_info_v2_4); break;
		case v2_6: atui_args.rename = "atom_gfx_info_v2_5 (forced)"; fall;
		case v2_5: atui_func = ATUI_FUNC(atom_gfx_info_v2_5); break;
		case v2_7: atui_func = ATUI_FUNC(atom_gfx_info_v2_7); break;
		case v3_0: atui_func = ATUI_FUNC(atom_gfx_info_v3_0); break;
		default:
			atui_func = ATUI_FUNC(atom_common_table_header);
			atui_args.rename = "gfx_info (header only stub)";
			break;
	}
	return atui_func(&atui_args);
}



inline static atui_branch*
grow_pplib_ppt_state_array(
		struct atomtree_powerplay_table_v4_1* const ppt41
		) {
	if (nover == ppt41->state_array_ver) {
		return NULL;
	}

	atui_branch* base;
	struct atui_funcify_args atui_args = {
		.atomtree =  ppt41,
		.suggestbios = ppt41->state_array_base,
		.num_import_branches = ppt41->num_state_array_entries,
	};
	atuifunc atui_state_func;

	switch (ppt41->state_array_ver) {
		case v1_0:
			base = ATUI_FUNC(atom_pplib_state_v1_array)(&atui_args);
			atui_state_func = ATUI_FUNC(atom_pplib_state_v1);
			break;
		case v2_0:
			base = ATUI_FUNC(atom_pplib_state_array_v2)(&atui_args);
			atui_state_func = ATUI_FUNC(atom_pplib_state_v2);
			break;
		default: assert(0); return NULL;
	}

	atui_args.num_import_branches = 0;
	for (uint8_t i = 0; i < ppt41->num_state_array_entries; i++) {
		atui_args.suggestbios = ppt41->state_array[i].state;
		atui_args.atomtree = &(ppt41->state_array[i]);
		atui_branch* state_entry = atui_state_func(&atui_args);
		sprintf(state_entry->name, "%s [%02u]", state_entry->origname, i);
		ATUI_ADD_BRANCH(base, state_entry);
	}

	return base;
}
inline static atui_branch*
grow_pplib_ppt_clock_info(
		struct atomtree_powerplay_table_v4_1* const ppt41,
		union atom_pplib_clock_info_arrays* const clock_info
		) {
	
	struct atui_funcify_args atui_args = {
		.atomtree = ppt41,
		.suggestbios = clock_info,
	};
	switch (ppt41->clock_info_ver) {
		case ATOM_PPLIB_CLOCK_INFO_R600:
			return ATUI_FUNC(atom_pplib_r600_clock_info_array)(&atui_args);
		case ATOM_PPLIB_CLOCK_INFO_RS780:
			return ATUI_FUNC(atom_pplib_rs780_clock_info_array)(&atui_args);
		case ATOM_PPLIB_CLOCK_INFO_GREEN:
			return ATUI_FUNC(atom_pplib_evergreen_clock_info_array)(&atui_args);
		case ATOM_PPLIB_CLOCK_INFO_SOUTH:
			return ATUI_FUNC(atom_pplib_si_clock_info_array)(&atui_args);
		case ATOM_PPLIB_CLOCK_INFO_SEA:
			return ATUI_FUNC(atom_pplib_ci_clock_info_array)(&atui_args);
		case ATOM_PPLIB_CLOCK_INFO_SUMO:
			return ATUI_FUNC(atom_pplib_sumo_clock_info_array)(&atui_args);
		case ATOM_PPLIB_CLOCK_INFO_CARRIZO:
			return ATUI_FUNC(atom_pplib_cz_clock_info_array)(&atui_args);
		default:
			atui_args.rename = "clock_info (header only stub)";
			return ATUI_FUNC(atom_pplib_sized_array_header)(&atui_args);
	}
	
	return NULL;
}
inline static atui_branch*
grow_pplib_ppt_extended_header(
		struct atomtree_powerplay_table_v4_1* const ppt41
		) {
	atui_branch* vce = NULL;
	if (ppt41->vce_root) {
		vce = ATUI_MAKE_BRANCH(atom_pplib_vce_table, NULL,
			ppt41,ppt41->vce_root,  0,NULL
		);
	}

	atui_branch* uvd = NULL;
	if (ppt41->uvd_root) {
		uvd = ATUI_MAKE_BRANCH(atom_pplib_uvd_table, NULL,
			ppt41,ppt41->uvd_root,  0,NULL
		);
	}

	atui_branch* samu = NULL;
	if (ppt41->samu) {
		samu = ATUI_MAKE_BRANCH(atom_pplib_samu_table, NULL,
			ppt41,ppt41->samu,  0,NULL
		);
	}

	atui_branch* ppm = NULL;
	if (ppt41->ppm) {
		ppm = ATUI_MAKE_BRANCH(atom_pplib_ppm_table, NULL,
			ppt41,ppt41->ppm,  0,NULL
		);
	}

	atui_branch* acpclk = NULL;
	if (ppt41->acpclk) {
		acpclk = ATUI_MAKE_BRANCH(atom_pplib_acp_table, NULL,
			ppt41,ppt41->acpclk,  0,NULL
		);
	}

	atui_branch* powertune = NULL;
	if (ppt41->powertune) {
		struct atui_funcify_args atui_args = {
			.atomtree = ppt41,
			.suggestbios = ppt41->powertune,
		};
		switch (ppt41->powertune->RevId) {
			case 0:
				powertune = ATUI_FUNC(atom_pplib_powertune_table_v0)(
					&atui_args
				);
				break;
			case 1:
				powertune = ATUI_FUNC(atom_pplib_powertune_table_v1)(
					&atui_args
				);
				break;
			default:
				assert(0);
				atui_args.rename = "powertune (header only stub)";
				powertune = ATUI_FUNC(pplib_subtable_header)(&atui_args);
				break;
		}
	}


	atui_branch* vddgfx_sclk = NULL;
	if (ppt41->vddgfx_sclk) {
		vddgfx_sclk = ATUI_MAKE_BRANCH(
			atom_pplib_clock_voltage_dependency_table, "vddgfx_sclk",
			ppt41,ppt41->vddgfx_sclk,  0,NULL
		);
	}

	atui_branch* vq_budgeting = NULL;
	if (ppt41->vq_budgeting) {
		vq_budgeting = ATUI_MAKE_BRANCH(atom_pplib_vq_budgeting_table, NULL,
			ppt41,ppt41->vq_budgeting,  0,NULL
		);
	}

	atui_branch* const extended_children[] = {
		vce, uvd, samu, ppm, acpclk, powertune, vddgfx_sclk, vq_budgeting,
	};
	struct atui_funcify_args const atui_args = {
		.atomtree = ppt41,
		.suggestbios = ppt41->extended_header,
		.import_branches = extended_children,
		.num_import_branches = lengthof(extended_children),
	};
	switch (ppt41->extended_header_ver) {
		case v1_0: return ATUI_FUNC(atom_pplib_extended_header_v1)(&atui_args);
		case v2_0: return ATUI_FUNC(atom_pplib_extended_header_v2)(&atui_args);
		case v3_0: return ATUI_FUNC(atom_pplib_extended_header_v3)(&atui_args);
		case v4_0: return ATUI_FUNC(atom_pplib_extended_header_v4)(&atui_args);
		case v5_0: return ATUI_FUNC(atom_pplib_extended_header_v5)(&atui_args);
		case v6_0: return ATUI_FUNC(atom_pplib_extended_header_v6)(&atui_args);
		case v7_0: return ATUI_FUNC(atom_pplib_extended_header_v7)(&atui_args);
		case v8_0: return ATUI_FUNC(atom_pplib_extended_header_v8)(&atui_args);
		case v9_0: return ATUI_FUNC(atom_pplib_extended_header_v9)(&atui_args);
		default: assert(0); return NULL; // TODO return size
	}
}
inline static atui_branch*
grow_pplib_ppt(
		struct atomtree_powerplay_table_v4_1* const ppt41
		) {
	// it's possible to reword this into a switch fallthrough system; worth it?
	// v1
	atui_branch* state_array = NULL;
	if (ppt41->state_array_base) {
		state_array = grow_pplib_ppt_state_array(ppt41);
	}

	atui_branch* clock_info = NULL;
	if (ppt41->clock_info) {
		clock_info = grow_pplib_ppt_clock_info(ppt41, ppt41->clock_info);
	}

	atui_branch* nonclock_info = NULL;
	if (ppt41->nonclock_info) {
		struct atui_funcify_args atui_args = {
			.atomtree = ppt41,
			.suggestbios = ppt41->nonclock_info,
		};
		switch (ppt41->nonclock_info_ver) {
			case v1_0:
				nonclock_info = ATUI_FUNC(atom_pplib_nonclock_info_array_v1)(
					&atui_args
				);
				break;
			case v2_0:
				nonclock_info = ATUI_FUNC(atom_pplib_nonclock_info_array_v2)(
					&atui_args
				);
				break;
			default:
				atui_args.rename = "nonclock_info (header only stub)";
				nonclock_info = ATUI_FUNC(atom_pplib_sized_array_header)(
					&atui_args
				);
			break;
		};
	}

	/*
	atui_branch* boot_clock_info = NULL;
	if (ppt41->boot_clock_info) {
	}
	atui_branch* boot_nonclock_info = NULL;
	if (ppt41->boot_nonclock_info) {
	}
	*/


	// v2
	atui_branch* thermal_policy = NULL;
	if (ppt41->thermal_policy) {
		thermal_policy = ATUI_MAKE_BRANCH(
			atom_pplib_custom_thermal_policy_array, NULL,
			ppt41,ppt41->thermal_policy,  0,NULL
		);
	}


	// v3
	atui_branch* fan_table = NULL;
	if (ppt41->fan_table) {
		struct atui_funcify_args atui_args = {
			.atomtree = ppt41,
			.suggestbios = ppt41->fan_table,
		};
		switch (ppt41->fan_table->RevId) {
			case 1: fan_table = ATUI_FUNC(atom_pplib_fan_table_v1)(&atui_args);
				break;
			case 2: fan_table = ATUI_FUNC(atom_pplib_fan_table_v2)(&atui_args);
				break;
			case 5:
			case 4:
			case 3: fan_table = ATUI_FUNC(atom_pplib_fan_table_v3)(&atui_args);
				break;
			case 6: fan_table = ATUI_FUNC(atom_pplib_fan_table_v6)(&atui_args);
				break;
			case 7: fan_table = ATUI_FUNC(atom_pplib_fan_table_v7)(&atui_args);
				break;
			default:
				atui_args.rename = "fan_table (header only stub)";
				fan_table = ATUI_FUNC(pplib_subtable_header)(&atui_args);
				break;
		}
	}

	atui_branch* extended_header = NULL;
	if (ppt41->extended_header) {
		extended_header = grow_pplib_ppt_extended_header(ppt41);
	}


	// v4
	atui_branch* vddc_sclk = NULL;
	if (ppt41->vddc_sclk) {
		vddc_sclk = ATUI_MAKE_BRANCH(atom_pplib_clock_voltage_dependency_table,
			"vddc_sclk",  ppt41,ppt41->vddc_sclk,  0,NULL
		);
	}

	atui_branch* vddci_mclk = NULL;
	if (ppt41->vddci_mclk) {
		vddci_mclk = ATUI_MAKE_BRANCH(atom_pplib_clock_voltage_dependency_table,
			"vddci_mclk",  ppt41,ppt41->vddci_mclk,  0,NULL
		);
	}

	atui_branch* vddc_mclk = NULL;
	if (ppt41->vddc_mclk) {
		vddc_mclk = ATUI_MAKE_BRANCH(atom_pplib_clock_voltage_dependency_table, 
			"vddc_mclk",  ppt41,ppt41->vddc_mclk,  0,NULL
		);
	}

	atui_branch* max_on_dc = NULL;
	if (ppt41->max_on_dc) {
		max_on_dc = ATUI_MAKE_BRANCH(atom_pplib_clock_voltage_limit_table, 
			NULL,  ppt41,ppt41->max_on_dc,  0,NULL
		);
	}

	atui_branch* phase_shed = NULL;
	if (ppt41->phase_shed) {
		phase_shed = ATUI_MAKE_BRANCH(atom_pplib_phasesheddinglimits_table, 
			NULL,  ppt41,ppt41->phase_shed,  0,NULL
		);
	}

	atui_branch* mvdd_mclk = NULL;
	if (ppt41->mvdd_mclk) {
		mvdd_mclk = ATUI_MAKE_BRANCH(atom_pplib_clock_voltage_dependency_table,
			"mvdd_mclk",  ppt41,ppt41->mvdd_mclk,  0,NULL
		);
	}


	// v5
	atui_branch* cac_leakage = NULL;
	if (ppt41->cac_leakage) {
		struct atui_funcify_args const atui_args = {
			.atomtree = ppt41,
			.suggestbios = ppt41->cac_leakage,
		};
		if (ppt41->leaves->v1.PlatformCaps.EVV) {
			cac_leakage = ATUI_FUNC(atom_pplib_cac_leakage_record_evv)(
				&atui_args
			);
		} else {
			cac_leakage = ATUI_FUNC(atom_pplib_cac_leakage_record)(&atui_args);
		}
	}

	atui_branch* const ppt41_children[] = {
		state_array, clock_info, nonclock_info,
		//boot_clock_info, boot_nonclock_info,
		thermal_policy, fan_table, extended_header,
		vddc_sclk, vddci_mclk, vddc_mclk, max_on_dc, phase_shed, mvdd_mclk,
		cac_leakage, 
	};
	struct atui_funcify_args atui_args = {
		.atomtree =  ppt41,
		.suggestbios = ppt41->leaves,
		.import_branches = ppt41_children,
		.num_import_branches = lengthof(ppt41_children),
	};
	switch (ppt41->pplib_ver) {
		case v5_0: return ATUI_FUNC(atom_pplib_powerplaytable_v5)(&atui_args);
		case v4_0: return ATUI_FUNC(atom_pplib_powerplaytable_v4)(&atui_args);
		case v3_0: return ATUI_FUNC(atom_pplib_powerplaytable_v3)(&atui_args);
		case v2_0: return ATUI_FUNC(atom_pplib_powerplaytable_v2)(&atui_args);
		case v1_0: return ATUI_FUNC(atom_pplib_powerplaytable_v1)(&atui_args);
		default: return NULL;
	}
}
inline static atui_branch*
atui_generate_pptablev1_ppt(
		struct atomtree_powerplay_table_v7_1* const ppt71
		) {
	atui_branch* state_array = NULL;
	if (ppt71->state_array) {
		state_array = ATUI_MAKE_BRANCH(atom_pptable_state_array, NULL,
			ppt71,ppt71->state_array,  0,NULL
		);
	}

	atui_branch* fan_table = NULL;
	if (ppt71->fan_table) {
		struct atui_funcify_args atui_args = {
			.atomtree = ppt71,
			.suggestbios = ppt71->fan_table,
		};
		uint8_t const RevId = ppt71->fan_table->RevId;
		if (7 >= RevId) {
			fan_table = ATUI_FUNC(atom_pptable_fan_table)(&atui_args);
		} else if (8 == RevId) {
			fan_table = ATUI_FUNC(atom_fiji_fan_table)(&atui_args);
		} else if (9 == RevId) {
			fan_table = ATUI_FUNC(atom_polaris_fan_table)(&atui_args);
		} else {
			atui_args.rename = "fan_table (header only stub)";
			fan_table = ATUI_FUNC(pplib_subtable_header)(&atui_args);
			assert(0);
		}
	}

	atui_branch* thermal_controller = NULL;
	if (ppt71->thermal_controller) {
		thermal_controller = ATUI_MAKE_BRANCH(atom_pptable_thermal_controller,
			NULL,  ppt71,ppt71->thermal_controller,  0,NULL
		);
	}

	atui_branch* mclk_dependency = NULL;
	if (ppt71->mclk_dependency) {
		mclk_dependency = ATUI_MAKE_BRANCH(atom_pptable_mclk_dependency_table,
			NULL,  ppt71,ppt71->mclk_dependency,  0,NULL
		);
	}

	atui_branch* sclk_dependency = NULL;
	if (ppt71->sclk_dependency) {
		sclk_dependency = ATUI_MAKE_BRANCH(atom_pptable_mclk_dependency_table,
			NULL,  ppt71,ppt71->sclk_dependency,  0,NULL
		);
		atuifunc atui_func;
		struct atui_funcify_args atui_args = {
			.atomtree = ppt71,
			.suggestbios = ppt71->sclk_dependency
		};
		switch (ppt71->sclk_dependency->RevId) {
			case 0:
				atui_func = ATUI_FUNC(atom_pptable_sclk_dependency_table);
				break;
			case 1:
				atui_func = ATUI_FUNC(atom_polaris_sclk_dependency_table);
				break;
			default: 
				atui_args.rename = "sclk_dependency (header only stub)";
				atui_func = ATUI_FUNC(pplib_subtable_header);
				assert(0);
				break;
		};
		sclk_dependency = atui_func(&atui_args);
	}

	atui_branch* vddc_lut = NULL;
	if (ppt71->vddc_lut) {
		vddc_lut = ATUI_MAKE_BRANCH(atom_pptable_voltage_lookup_table,
			"vddc_lut",
			ppt71,ppt71->vddc_lut,  0,NULL
		);
	}

	atui_branch* vddgfx_lut = NULL;
	if (ppt71->vddgfx_lut) {
		vddgfx_lut = ATUI_MAKE_BRANCH(atom_pptable_voltage_lookup_table,
			"vddgfx_lut",
			ppt71,ppt71->vddgfx_lut,  0,NULL
		);
	}

	atui_branch* mm_dependency = NULL;
	if (ppt71->mm_dependency) {
		mm_dependency = ATUI_MAKE_BRANCH(atom_pptable_mm_dependency_table, NULL,
			ppt71,ppt71->mm_dependency,  0,NULL
		);
	}

	atui_branch* vce_state = NULL;
	if (ppt71->vce_state) {
		vce_state = ATUI_MAKE_BRANCH(atom_pptable_vce_state_table, NULL,
			ppt71,ppt71->vce_state,  0,NULL
		);
	}

	atui_branch* ppm_table = NULL;
	if (ppt71->ppm_table) {
		ppm_table = ATUI_MAKE_BRANCH(atom_pplib_ppm_table, NULL,
			ppt71,ppt71->ppm_table,  0,NULL
		);
	}

	atui_branch* powertune = NULL;
	if (ppt71->powertune) {
		struct atui_funcify_args atui_args = {
			.atomtree = ppt71,
			.suggestbios = ppt71->powertune,
		};
		uint8_t const RevId = ppt71->powertune->RevId;
		if (2 >= RevId) {
			powertune = ATUI_FUNC(atom_pptable_powertune_table)(&atui_args);
		} else if (3 == RevId) {
			powertune = ATUI_FUNC(atom_fiji_powertune_table)(&atui_args);
		} else if (4 == RevId) {
			powertune = ATUI_FUNC(atom_polaris_powertune_table)(&atui_args);
		} else {
			atui_args.rename = "powertune (header only stub)";
			powertune = ATUI_FUNC(pplib_subtable_header)(&atui_args);
			assert(0);
		}
	}

	atui_branch* hard_limit = NULL;
	if (ppt71->hard_limit) {
		hard_limit = ATUI_MAKE_BRANCH(atom_pptable_hard_limit_table, NULL,
			ppt71,ppt71->hard_limit,  0,NULL
		);
	}

	atui_branch* pcie_table = NULL;
	if (ppt71->pcie_table) {
		pcie_table = ATUI_MAKE_BRANCH(atom_pptable_pcie_table, NULL,
			ppt71,ppt71->pcie_table,  0,NULL
		);
		atuifunc atui_func;
		struct atui_funcify_args atui_args = {
			.atomtree = ppt71,
			.suggestbios = ppt71->pcie_table,
		};
		switch (ppt71->pcie_table->RevId) {
			case 0: atui_func = ATUI_FUNC(atom_pptable_pcie_table); break;
			case 1: atui_func = ATUI_FUNC(atom_polaris_pcie_table); break;
			default:
				atui_args.rename = "pcie_table (header only stub)";
				atui_func = ATUI_FUNC(pplib_subtable_header);
				break;
		}
		pcie_table = atui_func(&atui_args);
	}

	atui_branch* gpio_table = NULL;
	if (ppt71->gpio_table) {
		gpio_table = ATUI_MAKE_BRANCH(atom_pptable_gpio_table, NULL,
			ppt71,ppt71->gpio_table,  0,NULL
		);
	}

	atui_branch* const ppt71_children[] = {
		state_array, fan_table, thermal_controller, mclk_dependency,
		sclk_dependency, vddc_lut, vddgfx_lut, mm_dependency, vce_state,
		ppm_table, powertune, hard_limit, pcie_table, gpio_table,
	};
	return ATUI_MAKE_BRANCH(atom_pptable_powerplaytable_v1,  NULL,
		ppt71,ppt71->leaves,  lengthof(ppt71_children),ppt71_children
	);
}

inline static atui_branch*
atui_generate_vega10_ppt(
		struct atomtree_powerplay_table_v8_1* const ppt81
		) {
	atui_branch* state_array = NULL;
	if (ppt81->state_array) {
		state_array = ATUI_MAKE_BRANCH(atom_vega10_state_array, NULL,
			ppt81,ppt81->state_array,  0,NULL
		);
	}

	atui_branch* fan_table = NULL;
	if (ppt81->fan_table) {
		struct atui_funcify_args atui_args = {
			.atomtree = ppt81,
			.suggestbios = ppt81->fan_table,
		};
		uint8_t const RevId = ppt81->fan_table->RevId;
		if (10 == RevId) {
			fan_table = ATUI_FUNC(atom_vega10_fan_table_v1)(&atui_args);
		} else if (11 == RevId) {
			fan_table = ATUI_FUNC(atom_vega10_fan_table_v2)(&atui_args);
		} else if (12 >= RevId) {
			fan_table = ATUI_FUNC(atom_vega10_fan_table_v3)(&atui_args);
		} else {
			atui_args.rename = "fan_table (header only stub)";
			fan_table = ATUI_FUNC(pplib_subtable_header)(&atui_args);
			assert(0);
		}
	}

	atui_branch* thermal_controller = NULL;
	if (ppt81->thermal_controller) {
		thermal_controller = ATUI_MAKE_BRANCH(atom_vega10_thermal_controller,
			NULL,  ppt81,ppt81->thermal_controller,  0,NULL
		);
	}

	atui_branch* socclk_dependency = NULL;
	if (ppt81->socclk_dependency) {
		socclk_dependency = ATUI_MAKE_BRANCH(atom_vega10_clk_dependency_table,
			"socclk_dependency",
			ppt81,ppt81->socclk_dependency,  0,NULL
		);
	}

	atui_branch* mclk_dependency = NULL;
	if (ppt81->mclk_dependency) {
		mclk_dependency = ATUI_MAKE_BRANCH(atom_vega10_mclk_dependency_table,
			NULL,  ppt81,ppt81->mclk_dependency,  0,NULL
		);
	}

	atui_branch* gfxclk_dependency = NULL;
	if (ppt81->gfxclk_dependency) {
		atuifunc atui_func;
		struct atui_funcify_args atui_args = {
			.atomtree = ppt81,
			.suggestbios = ppt81->gfxclk_dependency,
		};
		switch (ppt81->gfxclk_dependency->RevId) {
			case 0:
				atui_func = ATUI_FUNC(atom_vega10_gfxclk_dependency_table_v1);
				break;
			case 1:
				atui_func = ATUI_FUNC(atom_vega10_gfxclk_dependency_table_v2);
				break;
			default:
				atui_args.rename = "gfxclk_dependency (header only stub)";
				atui_func = ATUI_FUNC(pplib_subtable_header);
				assert(0);
				break;
		}
		gfxclk_dependency = atui_func(&atui_args);
	}

	atui_branch* dcefclk_dependency = NULL;
	if (ppt81->dcefclk_dependency) {
		dcefclk_dependency = ATUI_MAKE_BRANCH(atom_vega10_clk_dependency_table,
			"dcefclk_dependency",
			ppt81,ppt81->dcefclk_dependency,  0,NULL
		);
	}

	atui_branch* vddc_lut = NULL;
	if (ppt81->vddc_lut) {
		vddc_lut = ATUI_MAKE_BRANCH(atom_vega10_voltage_lookup_table,
			"vddc_lut",
			ppt81,ppt81->vddc_lut,  0,NULL
		);
	}

	atui_branch* vdd_mem_lut = NULL;
	if (ppt81->vdd_mem_lut) {
		vdd_mem_lut = ATUI_MAKE_BRANCH(atom_vega10_voltage_lookup_table,
			"vdd_mem_lut",
			ppt81,ppt81->vdd_mem_lut,  0,NULL
		);
	}

	atui_branch* mm_dependency = NULL;
	if (ppt81->mm_dependency) {
		mm_dependency = ATUI_MAKE_BRANCH(atom_vega10_mm_dependency_table, NULL,
			ppt81,ppt81->mm_dependency,  0,NULL
		);
	}

	atui_branch* vce_state = NULL;
	if (ppt81->vce_state) {
		vce_state = ATUI_MAKE_BRANCH(atom_vega10_vce_state_table, NULL,
			ppt81,ppt81->vce_state,  0,NULL
		);
	}

	atui_branch* powertune = NULL;
	if (ppt81->powertune) {
		atuifunc atui_func;
		struct atui_funcify_args atui_args = {
			.atomtree = ppt81,
			.suggestbios = ppt81->powertune
		};
		switch (ppt81->powertune->RevId) {
			case 5: atui_func = ATUI_FUNC(atom_vega10_powertune_table_v1);break;
			case 6: atui_func = ATUI_FUNC(atom_vega10_powertune_table_v2);break;
			default:atui_func = ATUI_FUNC(atom_vega10_powertune_table_v3);break;
			/*
			default:
				atui_args.rename = "powertune (header only stub)";
				atui_func = ATUI_FUNC(pplib_subtable_header);
				break;
			*/
		};
		powertune = atui_func(&atui_args);
	}

	atui_branch* hard_limit = NULL;
	if (ppt81->hard_limit) {
		hard_limit = ATUI_MAKE_BRANCH(atom_vega10_hard_limit_table, NULL,
			ppt81,ppt81->hard_limit,  0,NULL
		);
	}

	atui_branch* vddci_lut = NULL;
	if (ppt81->vddci_lut) {
		vddci_lut = ATUI_MAKE_BRANCH(atom_vega10_voltage_lookup_table,
			"vddci_lut",
			ppt81,ppt81->vddci_lut,  0,NULL
		);
	}

	atui_branch* pcie_table = NULL;
	if (ppt81->pcie_table) {
		pcie_table = ATUI_MAKE_BRANCH(atom_vega10_pcie_table, NULL,
			ppt81,ppt81->pcie_table,  0,NULL
		);
	}

	atui_branch* pixclk_dependency = NULL;
	if (ppt81->pixclk_dependency) {
		pixclk_dependency = ATUI_MAKE_BRANCH(atom_vega10_clk_dependency_table,
			"pixclk_dependency",
			ppt81,ppt81->pixclk_dependency,  0,NULL
		);
	}

	atui_branch* dispclk_dependency = NULL;
	if (ppt81->dispclk_dependency) {
		dispclk_dependency = ATUI_MAKE_BRANCH(atom_vega10_clk_dependency_table,
			"dispclk_dependency",
			ppt81,ppt81->dispclk_dependency,  0,NULL
		);
	}

	atui_branch* phyclk_dependency = NULL;
	if (ppt81->phyclk_dependency) {
		phyclk_dependency = ATUI_MAKE_BRANCH(atom_vega10_clk_dependency_table,
			"phyclk_dependency",
			ppt81,ppt81->phyclk_dependency,  0,NULL
		);
	}
	atui_branch* const ppt81_children[] = {
		state_array, fan_table, thermal_controller, socclk_dependency,
		mclk_dependency, gfxclk_dependency, dcefclk_dependency, vddc_lut,
		vdd_mem_lut, mm_dependency, vce_state, powertune, hard_limit,
		vddci_lut, pcie_table, pixclk_dependency, dispclk_dependency,
		phyclk_dependency, 
	};
	return ATUI_MAKE_BRANCH(atom_vega10_powerplaytable,  NULL,
		ppt81,ppt81->leaves,  lengthof(ppt81_children),ppt81_children
	);
}

inline static atui_branch*
atui_generate_smc_pptable(
		enum atomtree_common_version ver,
		struct atomtree_powerplay_table* const ppt,
		void const* const smc_pptable
		) {
	struct atui_funcify_args atui_args = {
		.atomtree = ppt,
		.suggestbios = smc_pptable,
	};
	switch (ver) {
		case v3_0: return ATUI_FUNC(smu11_smcpptable_v3)(&atui_args);
		case v5_0: return ATUI_FUNC(smu11_smcpptable_v5)(&atui_args);
		case v6_0: atui_args.rename = "smu11_smcpptable_v7 (forced)"; fall;
		case v7_0: return ATUI_FUNC(smu11_smcpptable_v7)(&atui_args);
		case v8_0: return ATUI_FUNC(smu11_smcpptable_v8)(&atui_args);
		default: assert(0);
	}
	return NULL;
}
inline static atui_branch*
grow_ppt(
		struct atomtree_powerplay_table* const ppt,
		struct atom_tree* const atree __unused
		) {
	if (NULL == ppt->leaves) {
		return NULL;
	}

	atui_branch* atui_ppt;
	atui_branch* atui_smctable = NULL;
	atuifunc atui_func;
	struct atui_funcify_args atui_args = {
		.atomtree = ppt,
		.suggestbios = ppt->leaves,
		.import_branches = &atui_smctable,
		.num_import_branches = 1,
	};
	switch (ppt->ver) {
		case v1_1:
			atui_ppt = ATUI_FUNC(atom_powerplay_info_v1)(&atui_args);
			break;
		case v2_1:
			atui_ppt = ATUI_FUNC(atom_powerplay_info_v2)(&atui_args);
			break;
		case v3_1:
			atui_ppt = ATUI_FUNC(atom_powerplay_info_v3)(&atui_args);
			break;
		case v6_1:
		case v5_1:
		case v4_1:
			atui_ppt = grow_pplib_ppt(&(ppt->v4_1));
			break;
		case v7_1: // Tonga, Fiji, Polaris
			atui_ppt = atui_generate_pptablev1_ppt(&(ppt->v7_1));
			break;
		case v8_1:
			atui_ppt = atui_generate_vega10_ppt(&(ppt->v8_1));
			break;
		case v11_0:
			atui_smctable = atui_generate_smc_pptable(
				ppt->v11_0.smc_pptable_ver,
				ppt, &(ppt->v11_0.leaves->smc_pptable)
			);
			atui_ppt = ATUI_FUNC(atom_vega20_powerplay_table)(&atui_args);
			break;
		case v14_0:
		case v12_0:
			atui_smctable = atui_generate_smc_pptable(
				ppt->v12_0.smc_pptable_ver,
				ppt, &(ppt->v12_0.leaves->smc_pptable)
			);
			atui_ppt = ATUI_FUNC(smu_11_0_powerplay_table)(&atui_args);
			break;
		case v19_0: // 6400
		case v18_0: // navi2 xx50
		case v16_0: // 6700XT
		case v15_0:
			atui_smctable = atui_generate_smc_pptable(
				ppt->v15_0.smc_pptable_ver,
				ppt, &(ppt->v15_0.leaves->smc_pptable)
			);
			atui_ppt = ATUI_FUNC(smu_11_0_7_powerplay_table)(&atui_args);
			break;
		default:
			atui_args.rename = (
				"smu_powerplay_table_header (header only stub)"
			);
			atui_ppt = ATUI_FUNC(smu_powerplay_table_header)(&atui_args);
			break;
	}
	return atui_ppt;
}

static atui_branch*
autogen_regblock_register_sequence(
		atuifunc const* const func_playlist,
		struct atom_reg_setting_data_block* const data_block,
		uint8_t const num_data_entries
		) {
	struct atui_funcify_args atui_args = {
		.suggestbios = &(data_block->block_id)
	};
	atui_branch** all_fields = malloc(
		(1+num_data_entries) * sizeof(atui_branch*)
	);
	all_fields[0] = ATUI_FUNC(atom_mc_register_setting_id)(&atui_args);
	atui_branch** reg_data_fields = all_fields + 1;

	for (uint8_t i=0; i < num_data_entries; i++) {
		atui_args.suggestbios = &(data_block->reg_data[i]);
		reg_data_fields[i] = func_playlist[i](&atui_args);
	}

	// atui_add_leaves()

	atui_branch* const auto_sequence = ATUI_MAKE_BRANCH(atui_nullstruct, NULL,
		NULL,NULL,  (1+num_data_entries), all_fields
	);
	return auto_sequence;
}
static atui_branch*
grow_init_reg_block(
		struct atomtree_init_reg_block* const at_regblock,
		uint8_t const num_extra_atuibranches
		) {
	return ATUI_MAKE_BRANCH(atom_init_reg_block,  NULL,
		at_regblock, at_regblock->leaves,  num_extra_atuibranches, NULL
	);
}

static void
get_memory_vendor_part_strs(
		struct atomtree_vram_module const* const vram_module,
		char const** const vendor_part_output
		) {
	union memory_vendor_id vendor_rev_id;
	vendor_part_output[1] = NULL;
	switch (vram_module->vram_module_ver) {
		case v1_1:
			 vendor_rev_id = vram_module->v1_1->MemoryVendorID;
			 break;
		case v1_2:
			 vendor_rev_id = vram_module->v1_2->MemoryVendorID;
			 break;
		case v1_3:
			 vendor_rev_id = vram_module->v1_3->MemoryVendorID;
			 break;
		case v1_4:
			 vendor_rev_id = vram_module->v1_4->MemoryVendorID;
			 break;
		case v1_5:
			 vendor_rev_id = vram_module->v1_5->MemoryVendorID;
			 break;
		case v1_6:
			 vendor_rev_id = vram_module->v1_6->MemoryVendorID;
			 break;
		case v1_7:
			 vendor_rev_id = vram_module->v1_7->MemoryVendorID;
			 vendor_part_output[1] = vram_module->v1_7->strMemPNString;
			 break;
		case v1_8:
			 vendor_rev_id = vram_module->v1_8->MemoryVendorID;
			 vendor_part_output[1] = vram_module->v1_8->strMemPNString;
			 break;
		case v1_9:
			 vendor_rev_id = vram_module->v1_9->vendor_rev_id;
			 vendor_part_output[1] = vram_module->v1_9->dram_pnstring;
			 break;
		case v1_10:
			 vendor_rev_id = vram_module->v1_10->vendor_rev_id;
			 vendor_part_output[1] = vram_module->v1_10->dram_pnstring;
			 break;
		case v1_11:
			 vendor_rev_id = vram_module->v1_11->vendor_rev_id;
			 vendor_part_output[1] = vram_module->v1_11->dram_pnstring;
			 break;
		case v3_0:
			 vendor_rev_id = vram_module->v3_0->dram_vendor_id;
			 vendor_part_output[1] = vram_module->v3_0->dram_pnstring;
			 break;
		default: assert(0);
	}
	struct atui_enum const* const vendors = &ATUI_ENUM(GDDR_MEM_VENDOR_e);
	assert(vendor_rev_id.vendor_code < vendors->num_entries);
	vendor_part_output[0] = vendors->enum_array[vendor_rev_id.vendor_code].name;
}

static atui_branch*
grow_mem_adjust_table(
		struct atomtree_init_reg_block* const mem_adjust_table,
		struct atomtree_vram_module const* const vram_modules
		) {
	atui_branch* const atui_mem_adjust = grow_init_reg_block(
		mem_adjust_table, 1
	);
	strcpy(atui_mem_adjust->name, "mem_adjust_table");
	if (COMMON_SET_UNKNOWN == mem_adjust_table->reg_set) {
		return atui_mem_adjust;
	}
	atui_branch* const atui_adjust_set = ATUI_MAKE_BRANCH(atui_nullstruct, NULL,
		NULL,NULL,  mem_adjust_table->num_data_blocks, NULL
	);
	ATUI_ADD_BRANCH(atui_mem_adjust, atui_adjust_set);

	atuifunc atui_strap_func = NULL;
	switch (mem_adjust_table->reg_set) {
		case MEM_ADJUST_SET_GCN3_HBM1:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_gcn3_hbm1);
			break;
		case MEM_ADJUST_SET_GCN3_GDDR5_TYPE2:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_gcn3_gddr5_type2);
			break;
		case MEM_ADJUST_SET_GCN4_GDDR5_TYPE1:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_gcn4_gddr5_type1);
			break;
		case MEM_ADJUST_SET_GCN4_GDDR5_TYPE2:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_gcn4_gddr5_type2);
			break;
		case MEM_ADJUST_SET_GCN4_GDDR5_TYPE4:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_gcn4_gddr5_type4);
			break;
		case MEM_ADJUST_SET_GCN4_GDDR5_TYPE5:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_gcn4_gddr5_type5);
			break;
		case MEM_ADJUST_SET_GCN4_GDDR5_TYPE3:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_gcn4_gddr5_type3);
			break;
		case MEM_ADJUST_SET_GCN3_GDDR5_TYPE3:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_gcn3_gddr5_type3);
			break;
		case MEM_ADJUST_SET_GCN3_GDDR5_TYPE1:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_gcn3_gddr5_type1);
			break;
		case MEM_ADJUST_SET_TERASCALE2_DDR3:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_terascale2_ddr3);
			break;
		case MEM_ADJUST_SET_TERASCALE2_GDDR5_TYPE3:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_terascale2_gddr5_type3);
			break;
		case MEM_ADJUST_SET_GCN1_GDDR5_TYPE5:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_gcn1_gddr5_type5);
			break;
		case MEM_ADJUST_SET_TERASCALE2_GDDR5_TYPE4:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_terascale2_gddr5_type4);
			break;
		case MEM_ADJUST_SET_TERASCALE3_GDDR5:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_terascale3_gddr5);
			break;
		case MEM_ADJUST_SET_GCN1_GDDR5_TYPE1:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_gcn1_gddr5_type1);
			break;
		case MEM_ADJUST_SET_GCN1_GDDR5_TYPE2:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_gcn1_gddr5_type2);
			break;
		case MEM_ADJUST_SET_GCN1_GDDR5_TYPE4:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_gcn1_gddr5_type4);
			break;
		case MEM_ADJUST_SET_GCN2_GDDR5:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_gcn2_gddr5);
			break;
		case MEM_ADJUST_SET_GCN1_GDDR5_TYPE3:
			atui_strap_func = ATUI_FUNC(mem_adjust_set_gcn1_gddr5_type3);
			break;
	}
	assert(atui_strap_func);

	enum atomtree_common_version const vram_module_ver =
		vram_modules[0].vram_module_ver;
	struct atom_reg_setting_data_block const* const* const data_blocks =
		(void*) mem_adjust_table->data_blocks;

	atui_branch* atui_strap;
	struct atui_funcify_args atui_args = {0};
	char const* vendor_part[2];
	bool const atom_vram_module_v8_hack = (
		// uniquely, atom_vram_module_v8 uses McTunningSetId to ID
		// mem_adjust table. It seems to exist as a way to exlude the
		// 'generic' vram_module.
		(v1_8 == vram_modules[0].vram_module_ver)
		&& (GENERIC == vram_modules[0].v1_8->MemoryVendorID.vendor_code)
	);
	for (uint8_t i = 0; i < mem_adjust_table->num_data_blocks; i++) {
		atui_args.suggestbios = data_blocks[i];
		atui_strap = atui_strap_func(&atui_args);
		ATUI_ADD_BRANCH(atui_adjust_set, atui_strap);

		get_memory_vendor_part_strs(
			&(vram_modules[
				data_blocks[i]->block_id.mem_block_id
				+ atom_vram_module_v8_hack
			]),
			vendor_part
		);
		#ifndef NDEBUG
		if (v1_8 == vram_module_ver) {
			assert(
				(vram_modules[
					data_blocks[i]->block_id.mem_block_id
					+ atom_vram_module_v8_hack
				].v1_8->McTunningSetId
				) == (data_blocks[i]->block_id.mem_block_id)
			);
		}
		#endif
		if (v1_7 <= vram_module_ver) {
			sprintf(atui_strap->name, "vendor adjust %s (%s)",
				vendor_part[1], vendor_part[0]
			);
		} else {
			// atom_vram_module_v6 and older don't have part strings
			sprintf(atui_strap->name, "vendor adjust %s",
				vendor_part[0]
			);
		}
		assert(strlen(atui_strap->name) < sizeof(atui_strap->name));
	}
	if (mem_adjust_table->num_data_blocks) {
		sprintf(atui_adjust_set->name, "%s (has inaccuracies)",
			atui_strap->origname
		);
		assert(strlen(atui_adjust_set->name) < sizeof(atui_adjust_set->name));
	}

	return atui_mem_adjust;
}

static atui_branch*
grow_mem_clk_patch(
		struct atomtree_init_reg_block* const mem_clk_patch,
		struct atomtree_vram_module const* const vram_modules
		) {
	atui_branch* const atui_memclkpatch = grow_init_reg_block(
		mem_clk_patch, 1
	);
	strcpy(atui_memclkpatch->name, "mem_clk_patch");
	if (COMMON_SET_UNKNOWN == mem_clk_patch->reg_set) {
		return atui_memclkpatch;
	}
	atui_branch* const atui_mem_timings = ATUI_MAKE_BRANCH(
		atui_nullstruct, NULL,
		NULL,NULL,  mem_clk_patch->num_data_blocks, NULL
	);
	ATUI_ADD_BRANCH(atui_memclkpatch, atui_mem_timings);

	atuifunc atui_strap_func = NULL;
	switch (mem_clk_patch->reg_set) {
		case TIMINGS_SET_POLARIS:
			atui_strap_func = ATUI_FUNC(timings_set_polaris);
			break;
		/*
		case TIMINGS_SET_VEGAM:
			atui_strap_func = ATUI_FUNC(timings_set_vegam);
			break;
		*/
		case TIMINGS_SET_ISLANDS_DDR3:
			atui_strap_func = ATUI_FUNC(timings_set_islands_ddr3);
			break;
		case TIMINGS_SET_ISLANDS_GDDR5:
			atui_strap_func = ATUI_FUNC(timings_set_islands_gddr5);
			break;
		case TIMINGS_SET_FIJI:
			atui_strap_func = ATUI_FUNC(timings_set_fiji);
			break;
	}
	assert(atui_strap_func);

	enum atomtree_common_version const vram_module_ver =
		vram_modules[0].vram_module_ver;
	struct atom_reg_setting_data_block const* const* const data_blocks =
		(void*) mem_clk_patch->data_blocks;

	atui_branch* atui_strap;
	struct atui_funcify_args atui_args = {0};
	char const* vendor_part[2];
	for (uint8_t i = 0; i < mem_clk_patch->num_data_blocks; i++) {
		atui_args.suggestbios = data_blocks[i];
		atui_strap = atui_strap_func(&atui_args);
		ATUI_ADD_BRANCH(atui_mem_timings, atui_strap);

		get_memory_vendor_part_strs(
			&(vram_modules[data_blocks[i]->block_id.mem_block_id]),
			vendor_part
		);
		if (v1_7 <= vram_module_ver) {
			sprintf(atui_strap->name, "Timings %s (%s): %u MHz",
				vendor_part[1], vendor_part[0],
				(data_blocks[i]->block_id.mem_clock_range / 100)
			);
		} else {
			// atom_vram_module_v6 and older don't have part strings
			sprintf(atui_strap->name, "Timings %s %u MHz",
				vendor_part[0],
				(data_blocks[i]->block_id.mem_clock_range / 100)
			);
		}
		assert(strlen(atui_strap->name) < sizeof(atui_strap->name));
	}
	if (mem_clk_patch->num_data_blocks) {
		strcpy(atui_mem_timings->name, atui_strap->origname);
	}

	return atui_memclkpatch;
}

static atui_branch*
grow_mc_tile_adjust(
		struct atomtree_init_reg_block* const mc_tile_adjust,
		struct atomtree_vram_module const* const vram_modules
		) {
	atui_branch* const atui_mc_tile_adjust = grow_init_reg_block(
		mc_tile_adjust, 1
	);
	strcpy(atui_mc_tile_adjust->name, "mc_tile_adjust");
	if (COMMON_SET_UNKNOWN == mc_tile_adjust->reg_set) {
		return atui_mc_tile_adjust;
	}
	atui_branch* const atui_adjust_set = ATUI_MAKE_BRANCH(
		atui_nullstruct,  NULL,
		NULL,NULL,  mc_tile_adjust->num_data_blocks, NULL
	);
	ATUI_ADD_BRANCH(atui_mc_tile_adjust, atui_adjust_set);

	atuifunc atui_strap_func = NULL;
	switch (mc_tile_adjust->reg_set) {
		case MC_TILE_ADJUST_SET_GCN4_GDDR5:
			atui_strap_func = ATUI_FUNC(mc_tile_adjust_set_gcn4_gddr5);
			break;
		case MC_TILE_ADJUST_SET_GCN3_GDDR5:
			atui_strap_func = ATUI_FUNC(mc_tile_adjust_set_gcn3_gddr5);
			break;
	}
	assert(atui_strap_func);

	enum atomtree_common_version const vram_module_ver =
		vram_modules[0].vram_module_ver;
	struct atom_reg_setting_data_block const* const* const data_blocks =
		(void*) mc_tile_adjust->data_blocks;

	atui_branch* atui_strap;
	struct atui_funcify_args atui_args = {0};
	for (uint8_t i = 0; i < mc_tile_adjust->num_data_blocks; i++) {
		atui_args.suggestbios = data_blocks[i];
		atui_strap = atui_strap_func(&atui_args);
		ATUI_ADD_BRANCH(atui_adjust_set, atui_strap);
		sprintf(atui_strap->name, "%s [%u]",
			atui_strap->origname,   i
		);
		assert(strlen(atui_strap->name) < sizeof(atui_strap->name));
	}
	if (mc_tile_adjust->num_data_blocks) {
		sprintf(atui_adjust_set->name, "%s (has inaccuracies)",
			atui_strap->origname
		);
		assert(strlen(atui_adjust_set->name) < sizeof(atui_adjust_set->name));
		//strcpy(atui_adjust_set->name, atui_strap->origname);
	}

	return atui_mc_tile_adjust;
}

static atui_branch*
grow_init_mc_phy_init(
		struct atomtree_init_reg_block* const mc_phy_init,
		struct atomtree_vram_module const* const vram_modules
		) {
	atui_branch* const atui_phy_init = grow_init_reg_block(
		mc_phy_init, 1
	);
	strcpy(atui_phy_init->name, "mc_phy_init");
	if (COMMON_SET_UNKNOWN == mc_phy_init->reg_set) {
		return atui_phy_init;
	}
	atui_branch* const atui_phy_init_set = ATUI_MAKE_BRANCH(
		atui_nullstruct,  NULL,
		NULL,NULL,  mc_phy_init->num_data_blocks, NULL
	);
	ATUI_ADD_BRANCH(atui_phy_init, atui_phy_init_set);

	// go by static tables instead of individually constructing the bitfields
	// because static tables offers a more consise, typed API.
	atuifunc atui_strap_func = NULL;
	switch (mc_phy_init->reg_set) {
		case MC_PHY_INIT_SET_GCN4_GDDR5_TYPE4:
			atui_strap_func = ATUI_FUNC(mc_phy_init_set_gcn4_gddr5_type4);
			break;
		case MC_PHY_INIT_SET_GCN4_GDDR5_TYPE6:
			atui_strap_func = ATUI_FUNC(mc_phy_init_set_gcn4_gddr5_type6);
			break;
		case MC_PHY_INIT_SET_GCN4_GDDR5_TYPE3:
			atui_strap_func = ATUI_FUNC(mc_phy_init_set_gcn4_gddr5_type3);
			break;
		case MC_PHY_INIT_SET_GCN4_GDDR5_TYPE5:
			atui_strap_func = ATUI_FUNC(mc_phy_init_set_gcn4_gddr5_type5);
			break;
		case MC_PHY_INIT_SET_GCN3_HBM1:
			atui_strap_func = ATUI_FUNC(mc_phy_init_set_gcn3_hbm1);
			break;
		case MC_PHY_INIT_SET_GCN4_GDDR5_TYPE2:
			atui_strap_func = ATUI_FUNC(mc_phy_init_set_gcn4_gddr5_type2);
			break;
		case MC_PHY_INIT_SET_GCN4_GDDR5_TYPE1:
			atui_strap_func = ATUI_FUNC(mc_phy_init_set_gcn4_gddr5_type1);
			break;
		case MC_PHY_INIT_SET_GCN3_GDDR5_TYPE1:
			atui_strap_func = ATUI_FUNC(mc_phy_init_set_gcn3_gddr5_type1);
			break;
		case MC_PHY_INIT_SET_GCN3_GDDR5_TYPE3:
			atui_strap_func = ATUI_FUNC(mc_phy_init_set_gcn3_gddr5_type3);
			break;
		case MC_PHY_INIT_SET_GCN3_GDDR5_TYPE2:
			atui_strap_func = ATUI_FUNC(mc_phy_init_set_gcn3_gddr5_type2);
			break;
	}
	assert(atui_strap_func);

	enum atomtree_common_version const vram_module_ver =
		vram_modules[0].vram_module_ver;
	struct atom_reg_setting_data_block const* const* const data_blocks =
		(void*) mc_phy_init->data_blocks;

	atui_branch* atui_strap;
	struct atui_funcify_args atui_args = {0};
	for (uint8_t i = 0; i < mc_phy_init->num_data_blocks; i++) {
		atui_args.suggestbios = data_blocks[i];
		atui_strap = atui_strap_func(&atui_args);
		ATUI_ADD_BRANCH(atui_phy_init_set, atui_strap);
		sprintf(atui_strap->name, "%s [%u]",
			atui_strap->origname,   i
		);
		assert(strlen(atui_strap->name) < sizeof(atui_strap->name));
	}
	if (mc_phy_init->num_data_blocks) {
		sprintf(atui_phy_init_set->name, "%s (has inaccuracies)",
			atui_strap->origname
		);
		assert(strlen(atui_phy_init_set->name)
			< sizeof(atui_phy_init_set->name)
		);
		//strcpy(atui_phy_init_set->name, atui_strap->origname);
	}

	return atui_phy_init;
}


static atui_branch*
grow_umc_init_reg_block(
		struct atomtree_umc_init_reg_block* const at_regblock,
		uint8_t const num_extra_atuibranches
		) {
	return ATUI_MAKE_BRANCH(atom_umc_init_reg_block,  NULL, 
		at_regblock, at_regblock->leaves,  num_extra_atuibranches, NULL
	);
}


inline static atui_branch*
grow_atom_memory_timing_format(
		struct atomtree_vram_module* const vram_module,
		enum atom_dgpu_vram_type const memory_type,
		union atom_memory_timing_format const* const timing_format_start
		) {
	enum atomtree_common_version const timing_ver = (
		vram_module->memory_timing_format_ver
	);
	union {
		void const* raw;
		struct atom_memory_timing_format_v0 const* v1_0;
		struct atom_memory_timing_format_v1 const* v1_1;
		struct atom_memory_timing_format_v2 const* v1_2;
	} strap;
	strap.raw = timing_format_start;
	uint8_t const count = vram_module->num_memory_timing_format;

	atui_branch* const atui_straps = ATUI_MAKE_BRANCH(atui_nullstruct,  NULL,
		NULL,NULL,  count,NULL
	);

	atui_branch* atui_mrs[4] = {NULL};
	struct atui_funcify_args atui_mrs_args = {0};
	atuifunc atui_mrs_funcs[lengthof(atui_mrs)] = {
		ATUI_FUNC(atui_nullstruct) // easier than null-testing
	};
	switch (memory_type) { // mrs in straps
		case ATOM_DGPU_VRAM_TYPE_DDR2: // non-G
			atui_mrs_funcs[0] = ATUI_FUNC(ddr2_mr0);
			atui_mrs_funcs[1] = ATUI_FUNC(ddr2_emr1);
			atui_mrs_funcs[2] = ATUI_FUNC(ddr2_emr2);
			break;
		case ATOM_DGPU_VRAM_TYPE_DDR3: // non-G
			atui_mrs_funcs[0] = ATUI_FUNC(ddr3_mr0);
			atui_mrs_funcs[1] = ATUI_FUNC(ddr3_mr1);
			atui_mrs_funcs[2] = ATUI_FUNC(ddr3_mr2);
			break;
		case ATOM_DGPU_VRAM_TYPE_GDDR3:
			atui_mrs_funcs[0] = ATUI_FUNC(gddr3_mr0);
			atui_mrs_funcs[1] = ATUI_FUNC(gddr3_emr1);
			// GDDR3 has no MR2
			break;
		case ATOM_DGPU_VRAM_TYPE_GDDR4:
			atui_mrs_funcs[0] = ATUI_FUNC(gddr4_mr0);
			atui_mrs_funcs[1] = ATUI_FUNC(gddr4_emr1);
			atui_mrs_funcs[2] = ATUI_FUNC(gddr4_emr2);
			break;
		case ATOM_DGPU_VRAM_TYPE_GDDR5_2:
		case ATOM_DGPU_VRAM_TYPE_GDDR5:
			atui_mrs_funcs[0] = ATUI_FUNC(gddr5_mr0);
			atui_mrs_funcs[1] = ATUI_FUNC(gddr5_mr1);
			atui_mrs_funcs[2] = ATUI_FUNC(gddr5_mr4);
			atui_mrs_funcs[3] = ATUI_FUNC(gddr5_mr5);
			break;
		default:
			assert(0);
			break;
	};
	

	atui_branch* atui_timings;
	struct atui_funcify_args atui_args = {
		.atomtree = vram_module,
		.import_branches = atui_mrs,
		.num_import_branches = lengthof(atui_mrs),
	};

	switch (timing_ver) {
		case v1_0:
			for (uint8_t i=0; i < count; i++) {
				atui_mrs_args.suggestbios = &(strap.v1_0->MR0);
				atui_mrs[0] = atui_mrs_funcs[0](&atui_mrs_args);
				atui_mrs_args.suggestbios = &(strap.v1_0->MR1);
				atui_mrs[1] = atui_mrs_funcs[1](&atui_mrs_args);
				if (memory_type != ATOM_DGPU_VRAM_TYPE_GDDR3) {
					atui_mrs_args.suggestbios = &(strap.v1_0->MR2);
					atui_mrs[2] = atui_mrs_funcs[2](&atui_mrs_args);
				}
				atui_args.suggestbios = strap.raw;
				atui_timings = ATUI_FUNC(atom_memory_timing_format_v0)(
					&atui_args
				);
				sprintf(atui_timings->name, "MemTiming (%u MHz)",
					(strap.v1_0->ClkRange / 100)
				);
				ATUI_ADD_BRANCH(atui_straps, atui_timings);
				strap.raw += sizeof(*strap.v1_0);
			}
			break;
		case v1_1:
			for (uint8_t i=0; i < count; i++) {
				atui_mrs_args.suggestbios = &(strap.v1_1->MR0);
				atui_mrs[0] = atui_mrs_funcs[0](&atui_mrs_args);
				atui_mrs_args.suggestbios = &(strap.v1_1->MR1);
				atui_mrs[1] = atui_mrs_funcs[1](&atui_mrs_args);
				atui_mrs_args.suggestbios = &(strap.v1_1->MR5);
				atui_mrs[3] = atui_mrs_funcs[3](&atui_mrs_args);
				atui_args.suggestbios = strap.raw;
				atui_timings = ATUI_FUNC(atom_memory_timing_format_v1)(
					&atui_args
				);
				sprintf(atui_timings->name, "MemTiming (%u MHz)",
					(strap.v1_1->ClkRange / 100)
				);
				ATUI_ADD_BRANCH(atui_straps, atui_timings);
				strap.raw += sizeof(*strap.v1_1);
			}
			break;
		case v1_2:
			for (uint8_t i=0; i < count; i++) {
				atui_mrs_args.suggestbios = &(strap.v1_2->MR0);
				atui_mrs[0] = atui_mrs_funcs[0](&atui_mrs_args);
				atui_mrs_args.suggestbios = &(strap.v1_2->MR1);
				atui_mrs[1] = atui_mrs_funcs[1](&atui_mrs_args);
				atui_mrs_args.suggestbios = &(strap.v1_2->MR4);
				atui_mrs[2] = atui_mrs_funcs[2](&atui_mrs_args);
				atui_mrs_args.suggestbios = &(strap.v1_2->MR5);
				atui_mrs[3] = atui_mrs_funcs[3](&atui_mrs_args);
				atui_args.suggestbios = strap.raw;
				atui_timings = ATUI_FUNC(atom_memory_timing_format_v2)(
					&atui_args
				);
				sprintf(atui_timings->name, "MemTiming (%u MHz)",
					(strap.v1_2->ClkRange / 100)
				);
				ATUI_ADD_BRANCH(atui_straps, atui_timings);
				strap.raw += sizeof(*strap.v1_2);
			}
			break;
	};

	strcpy(atui_straps->name, atui_timings->origname);
	return atui_straps;
}

static void
grow_mr2_mr3(
		enum atom_dgpu_vram_type const memory_type,
		atui_branch** const targets,
		void* const mr2,
		void* const mr3
		) {
	struct atui_funcify_args atui_mrs_args = {0};
	switch (memory_type) {
		case ATOM_DGPU_VRAM_TYPE_DDR2: // non-G
			atui_mrs_args.suggestbios = mr2;
			targets[0] = ATUI_FUNC(ddr2_emr2)(&atui_mrs_args);
			atui_mrs_args.suggestbios = mr3;
			targets[1] = ATUI_FUNC(ddr2_emr3)(&atui_mrs_args);
			break;
		case ATOM_DGPU_VRAM_TYPE_DDR3: // non-G
			atui_mrs_args.suggestbios = mr2;
			targets[0] = ATUI_FUNC(ddr3_mr2)(&atui_mrs_args);
			atui_mrs_args.suggestbios = mr3;
			targets[1] = ATUI_FUNC(ddr3_mr3)(&atui_mrs_args);
			break;
		case ATOM_DGPU_VRAM_TYPE_GDDR4:
			atui_mrs_args.suggestbios = mr2;
			targets[0] = ATUI_FUNC(gddr4_emr2)(&atui_mrs_args);
			atui_mrs_args.suggestbios = mr3;
			targets[1] = ATUI_FUNC(gddr4_emr3)(&atui_mrs_args);
			break;
		case ATOM_DGPU_VRAM_TYPE_GDDR5_2:
		case ATOM_DGPU_VRAM_TYPE_GDDR5:
			atui_mrs_args.suggestbios = mr2;
			targets[0] = ATUI_FUNC(gddr5_mr2)(&atui_mrs_args);
			atui_mrs_args.suggestbios = mr3;
			targets[1] = ATUI_FUNC(gddr5_mr3)(&atui_mrs_args);
			break;
		case ATOM_DGPU_VRAM_TYPE_HBM:
			atui_mrs_args.suggestbios = mr2;
			targets[0] = ATUI_FUNC(hbm_mr2)(&atui_mrs_args);
			atui_mrs_args.suggestbios = mr3;
			targets[1] = ATUI_FUNC(hbm_mr3)(&atui_mrs_args);
			break;
		case ATOM_DGPU_VRAM_TYPE_GDDR3: // GDDR3 has no MR2,MR3
			targets[0] = NULL;
			targets[1] = NULL;
			break;
		default:
			assert(0);
			targets[0] = NULL;
			targets[1] = NULL;
			break;
	};
}
inline static void
rename_vram_module_with_vendor(
		atui_branch* const atui_vmod,
		union memory_vendor_id vendor_id
		) {
	struct atui_enum const* const gddr_vendors = &ATUI_ENUM(GDDR_MEM_VENDOR_e);
	enum GDDR_MEM_VENDOR_e const code = vendor_id.vendor_code;
	assert(code <= gddr_vendors->num_entries);
	if (code <= gddr_vendors->num_entries) {
		sprintf(atui_vmod->name, "%s (%s)",
			atui_vmod->origname,
			gddr_vendors->enum_array[code].name
		);
	}
}

inline static atui_branch*
grow_vram_module_v1_3(
		struct atomtree_vram_module* const vram_modules,
		uint8_t const count
		) {
	atui_branch* const atui_vrammodules = ATUI_MAKE_BRANCH(atui_nullstruct,
		NULL,  NULL,NULL,  count,NULL
	);

	atui_branch* atui_vmod;
	atui_branch* atui_children[3] = {NULL}; // both mrs and timings
	for (uint8_t i=0; i < count; i++) {
		struct atomtree_vram_module* vmod = &(vram_modules[i]);

		grow_mr2_mr3(
			vmod->v1_3->MemoryType, atui_children,
			&(vmod->v1_3->MR2), &(vmod->v1_3->MR3)
		);
		atui_children[2] = grow_atom_memory_timing_format(
			vmod, vmod->v1_3->MemoryType, vmod->v1_3->MemTiming
		);

		atui_vmod = ATUI_MAKE_BRANCH(atom_vram_module_v3,  NULL,
			vmod, vmod->v1_3,  lengthof(atui_children), atui_children
		);
		ATUI_ADD_BRANCH(atui_vrammodules, atui_vmod);
		rename_vram_module_with_vendor(atui_vmod, vmod->v1_3->MemoryVendorID);
	}
	strcpy(atui_vrammodules->name, atui_vmod->origname);
	return atui_vrammodules;
}
inline static atui_branch*
grow_vram_module_v1_4(
		struct atomtree_vram_module* const vram_modules,
		uint8_t const count
		) {
	atui_branch* const atui_vrammodules = ATUI_MAKE_BRANCH(atui_nullstruct,
		NULL,  NULL,NULL,  count,NULL
	);

	atui_branch* atui_vmod;
	atui_branch* atui_children[3] = {NULL}; // both mrs and timings
	for (uint8_t i=0; i < count; i++) {
		struct atomtree_vram_module* vmod = &(vram_modules[i]);

		grow_mr2_mr3(
			vmod->v1_4->MemoryType, atui_children,
			&(vmod->v1_4->MR2), &(vmod->v1_4->MR3)
		);
		atui_children[2] = grow_atom_memory_timing_format(
			vmod, vmod->v1_4->MemoryType, vmod->v1_4->MemTiming
		);

		atui_vmod = ATUI_MAKE_BRANCH(atom_vram_module_v4,  NULL,
			vmod, vmod->v1_4,  lengthof(atui_children), atui_children
		);
		ATUI_ADD_BRANCH(atui_vrammodules, atui_vmod);
		rename_vram_module_with_vendor(atui_vmod, vmod->v1_4->MemoryVendorID);
	}
	strcpy(atui_vrammodules->name, atui_vmod->origname);
	return atui_vrammodules;
}
inline static atui_branch*
grow_vram_module_v1_7(
		struct atomtree_vram_module* const vram_modules,
		uint8_t const count
		) {
	atui_branch* const atui_vrammodules = ATUI_MAKE_BRANCH(atui_nullstruct,
		NULL,  NULL,NULL,  count,NULL
	);

	struct atui_funcify_args atui_map_args = {
		.rename = "ChannelMapCfg"
	};
	atui_branch* atui_vmod;
	atui_branch* atui_children[3] = {NULL}; // both mrs and timings
	for (uint8_t i=0; i < count; i++) {
		struct atomtree_vram_module* vmod = &(vram_modules[i]);

		atui_map_args.suggestbios = &(vmod->v1_7->ChannelMapCfg);
		if (v7_1 == vmod->gmc_bitfields_ver) {
			atui_children[0] = ATUI_FUNC(mc_shared_chremap_7_1)(&atui_map_args);
		} else { // 6.0
			atui_children[0] = ATUI_FUNC(mc_shared_chremap_6_0)(&atui_map_args);
		}

		grow_mr2_mr3(
			vmod->v1_7->MemoryType, atui_children+1,
			&(vmod->v1_7->MR2), &(vmod->v1_7->MR3)
		);

		atui_vmod = ATUI_MAKE_BRANCH(atom_vram_module_v7,  NULL,
			vmod, vmod->v1_7,  lengthof(atui_children), atui_children
		);
		ATUI_ADD_BRANCH(atui_vrammodules, atui_vmod);
		rename_vram_module_with_vendor(atui_vmod, vmod->v1_7->MemoryVendorID);
	}
	strcpy(atui_vrammodules->name, atui_vmod->origname);
	return atui_vrammodules;
}
inline static atui_branch*
grow_vram_module_v1_8(
		struct atomtree_vram_module* const vram_modules,
		uint8_t const count
		) {
	atui_branch* const atui_vrammodules = ATUI_MAKE_BRANCH(atui_nullstruct,
		NULL,  NULL,NULL,  count,NULL
	);

	struct atui_enum const* const gddr_vendors = &ATUI_ENUM(GDDR_MEM_VENDOR_e);

	atui_branch* atui_vmod;
	atui_branch* atui_children[3] = {NULL}; // both mrs and timings
	for (uint8_t i=0; i < count; i++) {
		struct atomtree_vram_module* vmod = &(vram_modules[i]);

		grow_mr2_mr3(
			vmod->v1_8->MemoryType, atui_children,
			&(vmod->v1_8->MR2), &(vmod->v1_8->MR3)
		);

		atui_vmod = ATUI_MAKE_BRANCH(atom_vram_module_v8,  NULL,
			vmod, vmod->v1_8,  lengthof(atui_children), atui_children
		);
		ATUI_ADD_BRANCH(atui_vrammodules, atui_vmod);
		rename_vram_module_with_vendor(atui_vmod, vmod->v1_8->MemoryVendorID);
	}
	strcpy(atui_vrammodules->name, atui_vmod->origname);
	return atui_vrammodules;
}
inline static atui_branch*
grow_vram_module_v1_9(
		struct atomtree_vram_module* const vram_modules,
		uint8_t const count
		) {
	atui_branch* const atui_vrammodules = ATUI_MAKE_BRANCH(atui_nullstruct,
		NULL,  NULL,NULL,  count,NULL
	);

	atui_branch* atui_vmod;
	atui_branch* atui_children[3] = {NULL}; // both mrs and timings
	for (uint8_t i=0; i < count; i++) {
		struct atomtree_vram_module* vmod = &(vram_modules[i]);

		atui_vmod = ATUI_MAKE_BRANCH(atom_vram_module_v9, NULL,
			vmod, vmod->v1_9,  lengthof(atui_children), atui_children
		);
		ATUI_ADD_BRANCH(atui_vrammodules, atui_vmod);
		rename_vram_module_with_vendor(atui_vmod, vmod->v1_9->vendor_rev_id);
	}
	strcpy(atui_vrammodules->name, atui_vmod->origname);
	return atui_vrammodules;
}
inline static atui_branch*
grow_vram_module_v1_10(
		struct atomtree_vram_module* const vram_modules,
		uint8_t const count
		) {
	atui_branch* const atui_vrammodules = ATUI_MAKE_BRANCH(atui_nullstruct,
		NULL,  NULL,NULL,  count,NULL
	);

	struct atui_enum const* const gddr_vendors = &ATUI_ENUM(GDDR_MEM_VENDOR_e);

	atui_branch* atui_vmod;
	atui_branch* atui_children[3] = {NULL}; // both mrs and timings
	for (uint8_t i=0; i < count; i++) {
		struct atomtree_vram_module* vmod = &(vram_modules[i]);

		atui_vmod = ATUI_MAKE_BRANCH(atom_vram_module_v10,  NULL,
			vmod, vmod->v1_10,  lengthof(atui_children), atui_children
		);
		ATUI_ADD_BRANCH(atui_vrammodules, atui_vmod);
		rename_vram_module_with_vendor(atui_vmod, vmod->v1_10->vendor_rev_id);
	}
	strcpy(atui_vrammodules->name, atui_vmod->origname);
	return atui_vrammodules;
}
inline static atui_branch*
grow_vram_module_v1_11(
		struct atomtree_vram_module* const vram_modules,
		uint8_t const count
		) {
	atui_branch* const atui_vrammodules = ATUI_MAKE_BRANCH(atui_nullstruct,
		NULL,  NULL,NULL,  count,NULL
	);

	atui_branch* atui_vmod;
	atui_branch* atui_children[3] = {NULL}; // both mrs and timings
	for (uint8_t i=0; i < count; i++) {
		struct atomtree_vram_module* vmod = &(vram_modules[i]);

		atui_vmod = ATUI_MAKE_BRANCH(atom_vram_module_v11,  NULL,
			vmod, vmod->v1_11,  lengthof(atui_children), atui_children
		);
		ATUI_ADD_BRANCH(atui_vrammodules, atui_vmod);
		rename_vram_module_with_vendor(atui_vmod, vmod->v1_11->vendor_rev_id);
	}
	strcpy(atui_vrammodules->name, atui_vmod->origname);
	return atui_vrammodules;
}
inline static atui_branch*
grow_vram_module_v3_0(
		struct atomtree_vram_module* const vram_modules,
		uint8_t const count
		) {
	atui_branch* const atui_vrammodules = ATUI_MAKE_BRANCH(atui_nullstruct,
		NULL,  NULL,NULL,  count,NULL
	);

	atui_branch* atui_vmod;
	atui_branch* atui_children[3] = {NULL}; // both mrs and timings
	for (uint8_t i=0; i < count; i++) {
		struct atomtree_vram_module* vmod = &(vram_modules[i]);

		atui_vmod = ATUI_MAKE_BRANCH(atom_vram_module_v3_0,  NULL,
			vmod, vmod->v3_0,  lengthof(atui_children), atui_children
		);
		ATUI_ADD_BRANCH(atui_vrammodules, atui_vmod);
		rename_vram_module_with_vendor(atui_vmod, vmod->v3_0->dram_vendor_id);
	}
	strcpy(atui_vrammodules->name, atui_vmod->origname);
	return atui_vrammodules;
}
static atui_branch*
grow_vram_module(
		struct atomtree_vram_module* const vram_modules,
		enum atomtree_common_version const vram_modules_ver,
		uint8_t const count
		) {
	// all the grows should look somewhat similar
	// v1_3 to v1_8 should look very similar to each other
	// v1_9 to v3_0 should look very similar to each other
	switch (vram_modules_ver) {
		case v1_3:  return grow_vram_module_v1_3(vram_modules, count);
		case v1_4:  return grow_vram_module_v1_4(vram_modules, count);
		case v1_7:  return grow_vram_module_v1_7(vram_modules, count);
		case v1_8:  return grow_vram_module_v1_8(vram_modules, count);
		case v1_9:  return grow_vram_module_v1_9(vram_modules, count);
		case v1_10: return grow_vram_module_v1_10(vram_modules, count);
		case v1_11: return grow_vram_module_v1_11(vram_modules, count);
		case v3_0:  return grow_vram_module_v3_0(vram_modules, count);
		default:
			assert(0); // TODO implement
			return NULL;
	}
}

inline static atui_branch*
grow_vram_info_v1_2(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_v1_2* const vi12 = &(vram_info->v1_2);

	atui_branch* atui_vrammodules = NULL;
	if (vi12->leaves->NumOfVRAMModule) {
		atui_vrammodules = grow_vram_module(
			vi12->vram_modules,
			vi12->vram_module_ver,
			vi12->leaves->NumOfVRAMModule
		);
	}

	return ATUI_MAKE_BRANCH(atom_vram_info_v1_2,  NULL,
		vi12,vi12->leaves,  1,&atui_vrammodules
	);
}

inline static atui_branch*
grow_vram_info_v1_3(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_v1_3* const vi13 = &(vram_info->v1_3);

	atui_branch* atui_mem_adjust = NULL;
	if (vi13->mem_adjust_table.leaves) {
		atui_mem_adjust = grow_init_reg_block(&(vi13->mem_adjust_table), 0);
		strcpy(atui_mem_adjust->name, "mem_adjust_table");
	}

	atui_branch* atui_memclkpatch = NULL;
	if (vi13->mem_clk_patch.leaves) {
		atui_memclkpatch = grow_init_reg_block(&(vi13->mem_clk_patch), 0);
		strcpy(atui_memclkpatch->name, "mem_clk_patch_table");
	}

	atui_branch* atui_vrammodules = NULL;
	if (vi13->leaves->NumOfVRAMModule) {
		atui_vrammodules = grow_vram_module(
			vi13->vram_modules,
			vi13->vram_module_ver,
			vi13->leaves->NumOfVRAMModule
		);
	}

	atui_branch* const vi13_children[] = {
		atui_mem_adjust, atui_memclkpatch, atui_vrammodules
	};
	return ATUI_MAKE_BRANCH(atom_vram_info_v1_3,  NULL,
		vi13,vi13->leaves,  lengthof(vi13_children), vi13_children
	);
}

inline static atui_branch*
grow_vram_info_v1_4(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_v1_4* const vi14 = &(vram_info->v1_4);

	atui_branch* atui_mem_adjust = NULL;
	if (vi14->mem_adjust_table.leaves) {
		atui_mem_adjust = grow_init_reg_block(&(vi14->mem_adjust_table), 0);
		strcpy(atui_mem_adjust->name, "mem_adjust_table");
	}

	atui_branch* atui_memclkpatch = NULL;
	if (vi14->mem_clk_patch.leaves) {
		// TODO See grow_vram_info_v1_3
		atui_memclkpatch = grow_init_reg_block(&(vi14->mem_clk_patch), 0);
		strcpy(atui_memclkpatch->name, "mem_clk_patch_table");
	}

	atui_branch* atui_vrammodules = NULL;
	if (vi14->leaves->NumOfVRAMModule) {
		atui_vrammodules = grow_vram_module(
			vi14->vram_modules,
			vi14->vram_module_ver,
			vi14->leaves->NumOfVRAMModule
		);
	}

	atui_branch* const vi14_children[] = {
		atui_mem_adjust, atui_memclkpatch, atui_vrammodules,
	};
	return ATUI_MAKE_BRANCH(atom_vram_info_v1_4,  NULL,
		vi14,vi14->leaves,  lengthof(vi14_children), vi14_children
	);
}

inline static atui_branch*
grow_vram_info_v2_1(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_1* const vi21 = &(vram_info->v2_1);

atui_branch* atui_mem_adjust = NULL;
	if (vi21->mem_adjust_table.leaves) {
		atui_mem_adjust = grow_mem_adjust_table(
			&(vi21->mem_adjust_table), vi21->vram_modules
		);
	}

	atui_branch* atui_memclkpatch = NULL;
	if (vi21->mem_clk_patch.leaves) {
		atui_memclkpatch = grow_mem_clk_patch(
			&(vi21->mem_clk_patch), vi21->vram_modules
		);
	}

	atui_branch* atui_perbytepreset = NULL;
	if (vi21->per_byte_preset.leaves) {
		// TODO unsure what lies beyond; never seen this true.
		atui_perbytepreset = grow_init_reg_block(&(vi21->per_byte_preset), 0);
		strcpy(atui_perbytepreset->name, "per_byte_preset_table");
	}

	atui_branch* atui_vrammodules = NULL;
	if (vi21->leaves->NumOfVRAMModule) {
		atui_vrammodules = grow_vram_module(
			vi21->vram_modules,
			vi21->vram_module_ver,
			vi21->leaves->NumOfVRAMModule
		);
	}

	atui_branch* const vi21_children[] = {
		atui_mem_adjust, atui_memclkpatch, atui_perbytepreset, atui_vrammodules
	};
	return ATUI_MAKE_BRANCH(atom_vram_info_header_v2_1,  NULL,
		vi21,vi21->leaves,  lengthof(vi21_children), vi21_children
	);
}

inline static atui_branch*
grow_vram_info_v2_2(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_2* const vi22 = &(vram_info->v2_2);

	atui_branch* atui_mem_adjust = NULL;
	if (vi22->mem_adjust_table.leaves) {
		atui_mem_adjust = grow_mem_adjust_table(
			&(vi22->mem_adjust_table), vi22->vram_modules
		);
	}

	atui_branch* atui_memclkpatch = NULL;
	if (vi22->mem_clk_patch.leaves) {
		atui_memclkpatch = grow_mem_clk_patch(
			&(vi22->mem_clk_patch), vi22->vram_modules
		);
	}

	atui_branch* atui_mc_tile_adjust = NULL;
	if (vi22->mc_tile_adjust.leaves) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		atui_mc_tile_adjust = grow_mc_tile_adjust(
			&(vi22->mc_tile_adjust), vi22->vram_modules
		);
	}

	atui_branch* atui_phyinit = NULL;
	if (vi22->mc_phy_init.leaves) {
		atui_phyinit = grow_init_mc_phy_init(
			&(vi22->mc_phy_init), vi22->vram_modules
		);
	}

	atui_branch* atui_dram_remap = NULL;
	if (vi22->dram_data_remap) {
		atui_dram_remap = ATUI_MAKE_BRANCH(mc_atom_dram_data_remap,  NULL,
			NULL, vi22->dram_data_remap, 0,NULL
		);
	}

	atui_branch* atui_vrammodules = NULL;
	if (vi22->leaves->NumOfVRAMModule) {
		atui_vrammodules = grow_vram_module(
			vi22->vram_modules,
			vi22->vram_module_ver,
			vi22->leaves->NumOfVRAMModule
		);
	}

	atui_branch* const vi22_children[] = {
		atui_mem_adjust, atui_memclkpatch, atui_mc_tile_adjust, atui_phyinit,
		atui_dram_remap, atui_vrammodules
	};
	return ATUI_MAKE_BRANCH(atom_vram_info_header_v2_2,  NULL,
		vi22,vi22->leaves,  lengthof(vi22_children), vi22_children
	);

}

inline static atui_branch*
grow_vram_info_v2_3(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_3* const vi23 = &(vram_info->v2_3);

	atui_branch* atui_mem_adjust = NULL;
	if (vi23->mem_adjust_table.leaves) {
		atui_mem_adjust = grow_umc_init_reg_block(&(vi23->mem_adjust_table), 0);
		strcpy(atui_mem_adjust->name, "mem_adjust_table");
	}

	atui_branch* atui_memclkpatch = NULL;
	if (vi23->mem_clk_patch.leaves) {
		struct atomtree_umc_init_reg_block const* const mem_clk_patch =
			&(vi23->mem_clk_patch);
		struct atom_reg_setting_data_block const* const* const data_blocks =
			(void*) vi23->mem_clk_patch.data_blocks;
		atui_memclkpatch = grow_umc_init_reg_block(&(vi23->mem_clk_patch), 1);

		strcpy(atui_memclkpatch->name, "mem_clk_patch_table");
		atui_branch* const atui_mem_timings = ATUI_MAKE_BRANCH(
			atui_nullstruct, NULL,
			NULL,NULL,  mem_clk_patch->num_data_blocks,NULL
		);
		ATUI_ADD_BRANCH(atui_memclkpatch, atui_mem_timings);

		atui_branch* atui_strap;
		atuifunc atui_strap_func;
		struct atui_funcify_args atui_args = {0};
		if (vi23->uses_vega20_timings) {
			atui_strap_func = ATUI_FUNC(timings_set_vega20);
		} else {
			atui_strap_func = ATUI_FUNC(timings_set_vega10);
		}
		char const* vendor_part[2];
		for (uint16_t i=0; i < mem_clk_patch->num_data_blocks; i++) {
			atui_args.suggestbios = data_blocks[i];
			atui_strap = atui_strap_func(&atui_args);
			ATUI_ADD_BRANCH(atui_mem_timings, atui_strap);

			get_memory_vendor_part_strs(
				&(vi23->vram_modules[
					data_blocks[i]->block_id.mem_block_id
				]),
				vendor_part
			);
			sprintf(atui_strap->name, "Timings %s (%s) %u MHz",
				vendor_part[1],
				vendor_part[0],
				(data_blocks[i]->block_id.mem_clock_range / 100)
			);
			assert(strlen(atui_strap->name) < sizeof(atui_strap->name));
		}
		if (mem_clk_patch->num_data_blocks) {
			strcpy(atui_mem_timings->name, atui_strap->origname);
		}
	}

	atui_branch* atui_mc_tile_adjust = NULL;
	if (vi23->mc_tile_adjust.leaves) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		atui_mc_tile_adjust = grow_umc_init_reg_block(
			&(vi23->mc_tile_adjust), 0
		);
		strcpy(atui_mc_tile_adjust->name, "mc_tile_adjust_table");
	}

	atui_branch* atui_phyinit = NULL;
	if (vi23->mc_phy_init.leaves) {
		atui_phyinit = grow_umc_init_reg_block(&(vi23->mc_phy_init), 0);
		strcpy(atui_phyinit->name, "mc_phy_init_table");
	}

	atui_branch* atui_dram_remap = NULL;
	if (vi23->dram_data_remap) {
	}

	atui_branch* atui_hbm_tmrs = NULL;
	if (vi23->hbm_tmrs) {
	}

	atui_branch* atui_postucode_init = NULL;
	if (vi23->post_ucode_init.leaves) {
		atui_postucode_init = grow_umc_init_reg_block(
			&(vi23->post_ucode_init), 0
		);
		strcpy(atui_postucode_init->name, "post_ucode_init");
	}

	atui_branch* atui_vrammodules = NULL;
	if (vi23->leaves->vram_module_num) {
		atui_vrammodules = grow_vram_module(
			vi23->vram_modules,
			vi23->vram_module_ver,
			vi23->leaves->vram_module_num
		);
	}

	atui_branch* const vi23_children[] = {
		atui_mem_adjust, atui_memclkpatch, atui_mc_tile_adjust, atui_phyinit,
		atui_dram_remap, atui_hbm_tmrs, atui_postucode_init,
		atui_vrammodules
	};

	return ATUI_MAKE_BRANCH(atom_vram_info_header_v2_3,  NULL,
		vi23,vi23->leaves,  lengthof(vi23_children), vi23_children
	);
}

inline static atui_branch*
grow_vram_info_v2_4(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_4* const vi24 = &(vram_info->v2_4);
	struct atom_vram_info_header_v2_4* const leaves = vram_info->leaves;

	atui_branch* atui_mem_adjust = NULL;
	if (vi24->mem_adjust_table.leaves) {
		atui_mem_adjust = grow_umc_init_reg_block(&(vi24->mem_adjust_table), 0);
		strcpy(atui_mem_adjust->name, "mem_adjust_table");
	}

	atui_branch* atui_memclkpatch = NULL;
	if (vi24->mem_clk_patch.leaves) {
		atui_memclkpatch = grow_umc_init_reg_block(&(vi24->mem_clk_patch), 1);

		struct atomtree_umc_init_reg_block const* const mem_clk_patch =
			&(vi24->mem_clk_patch);
		struct atom_reg_setting_data_block const* const* const data_blocks =
			(void*) vi24->mem_clk_patch.data_blocks;

		strcpy(atui_memclkpatch->name, "mem_clk_patch_table");
		atui_branch* const atui_mem_timings = ATUI_MAKE_BRANCH(
			atui_nullstruct, NULL,
			NULL,NULL, mem_clk_patch->num_data_blocks,NULL
		);
		ATUI_ADD_BRANCH(atui_memclkpatch, atui_mem_timings);

		// to have similar topology like the rest
		atui_branch* atui_strap;
		atuifunc const atui_strap_func = ATUI_FUNC(timings_set_navi1);
		struct atui_funcify_args atui_args = {0};
		char const* vendor_part[2];
		for (uint16_t i=0; i < mem_clk_patch->num_data_blocks; i++) {
			atui_args.suggestbios = data_blocks[i];
			atui_strap = atui_strap_func(&atui_args);
			ATUI_ADD_BRANCH(atui_mem_timings, atui_strap);

			get_memory_vendor_part_strs(
				&(vi24->vram_modules[
					data_blocks[i]->block_id.mem_block_id
				]),
				vendor_part
			);
			sprintf(atui_strap->name, "Timings %s (%s) %u MHz",
				vendor_part[1],
				vendor_part[0],
				(data_blocks[i]->block_id.mem_clock_range / 100)
			);
			assert(strlen(atui_strap->name) < sizeof(atui_strap->name));
		}
		if (mem_clk_patch->num_data_blocks) {
			strcpy(atui_mem_timings->name, atui_strap->origname);
		}
	}

	atui_branch* atui_mc_tile_adjust = NULL;
	if (vi24->mc_tile_adjust.leaves) {
		atui_mc_tile_adjust = grow_umc_init_reg_block(
			&(vi24->mc_tile_adjust), 0
		);
		strcpy(atui_mc_tile_adjust->name, "mc_tile_adjust_table");
	}

	atui_branch* atui_phyinit = NULL;
	if (vi24->mc_phy_init.leaves) {
		atui_phyinit = grow_umc_init_reg_block(&(vi24->mc_phy_init), 0);
		strcpy(atui_phyinit->name, "mc_phy_init_table");
	}

	atui_branch* atui_dram_remap = NULL;
	if (vi24->dram_data_remap) {
	}

	atui_branch* atui_postucode_init = NULL;
	if (vi24->post_ucode_init.leaves) {
		atui_postucode_init = grow_umc_init_reg_block(
			&(vi24->post_ucode_init), 0
		);
		strcpy(atui_postucode_init->name, "post_ucode_init");
	}

	atui_branch* atui_vrammodules = NULL;
	if (vi24->leaves->vram_module_num) {
		atui_vrammodules = grow_vram_module(
			vi24->vram_modules,
			vi24->vram_module_ver,
			vi24->leaves->vram_module_num
		);
	}

	atui_branch* const vi24_children[] = {
		atui_mem_adjust, atui_memclkpatch, atui_mc_tile_adjust,
		atui_dram_remap, atui_phyinit, atui_postucode_init,
		atui_vrammodules
	};
	return ATUI_MAKE_BRANCH(atom_vram_info_header_v2_4,  NULL,
		vi24,vi24->leaves,  lengthof(vi24_children), vi24_children
	);
}

inline static atui_branch*
grow_vram_info_v2_5(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_5* const vi25 = &(vram_info->v2_5);

	atui_branch* atui_mem_adjust = NULL;
	if (vi25->mem_adjust_table.leaves) {
		atui_mem_adjust = grow_umc_init_reg_block(&(vi25->mem_adjust_table), 0);
		strcpy(atui_mem_adjust->name, "mem_adjust_table");
	}

	atui_branch* atui_gddr6_ac_timings = NULL;
	if (vi25->gddr6_ac_timings) {
		atui_gddr6_ac_timings = ATUI_MAKE_BRANCH(atui_nullstruct,
			"atom_gddr6_ac_timing_v2_5",
			NULL,NULL,  vi25->gddr6_acstrap_count,NULL
		);
		struct atom_gddr6_ac_timing_v2_5 const* const timings =
			vi25->gddr6_ac_timings;
		atui_branch* atui_strap;
		char const* vendor_part[2];
		for (uint16_t i=0; i < vi25->gddr6_acstrap_count; i++) {
			atui_strap = ATUI_MAKE_BRANCH(atom_gddr6_ac_timing_v2_5,  NULL,
				NULL,&(timings[i]),  0,NULL
			);
			ATUI_ADD_BRANCH(atui_gddr6_ac_timings, atui_strap);

			get_memory_vendor_part_strs(
				&(vi25->vram_modules[timings[i].block_id.mem_block_id]),
				vendor_part
			);
			sprintf(atui_strap->name, "Timings %s (%s) %u MHz",
				vendor_part[1],
				vendor_part[0],
				(timings[i].block_id.mem_clock_range / 100)
			);
			assert(strlen(atui_strap->name) < sizeof(atui_strap->name));
		}
	}

	atui_branch* atui_mc_tile_adjust = NULL;
	if (vi25->mc_tile_adjust.leaves) {
		atui_mc_tile_adjust = grow_umc_init_reg_block(
			&(vi25->mc_tile_adjust), 0
		);
		strcpy(atui_mc_tile_adjust->name, "mc_tile_adjust_table");
	}

	atui_branch* atui_phyinit = NULL;
	if (vi25->mc_phy_init.leaves) {
		atui_phyinit = grow_umc_init_reg_block(&(vi25->mc_phy_init), 0);
		strcpy(atui_phyinit->name, "mc_phy_init_table");
	}

	atui_branch* atui_dram_remap = NULL;
	if (vi25->dram_data_remap) {
		atui_dram_remap = ATUI_MAKE_BRANCH(atom_gddr6_dram_data_remap,  NULL,
			NULL,vi25->dram_data_remap,  0,NULL
		);
	}

	atui_branch* atui_postucode_init = NULL;
	if (vi25->post_ucode_init.leaves) {
		atui_postucode_init = grow_umc_init_reg_block(
			&(vi25->post_ucode_init), 0
		);
		strcpy(atui_postucode_init->name, "post_ucode_init");
	}

	atui_branch* atui_strobe_mode_patch = NULL;
	if (vi25->strobe_mode_patch.leaves) {
		atui_strobe_mode_patch = grow_umc_init_reg_block(
			&(vi25->strobe_mode_patch), 0
		);
	}

	atui_branch* atui_vrammodules = NULL;
	if (vi25->leaves->vram_module_num) {
		atui_vrammodules = grow_vram_module(
			vi25->vram_modules,
			vi25->vram_module_ver,
			vi25->leaves->vram_module_num
		);
	}

	atui_branch* const vi25_children[] = {
		atui_mem_adjust, atui_gddr6_ac_timings, atui_mc_tile_adjust,
		atui_phyinit, atui_dram_remap, atui_postucode_init,
		atui_strobe_mode_patch, atui_vrammodules,
	};
	return ATUI_MAKE_BRANCH(atom_vram_info_header_v2_5,  NULL,
		vi25,vi25->leaves,  lengthof(vi25_children), vi25_children
	);
}

inline static atui_branch*
grow_vram_info_v2_6(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_6* const vi26 = &(vram_info->v2_6);

	atui_branch* atui_mem_adjust = NULL;
	if (vi26->mem_adjust_table.leaves) {
		atui_mem_adjust = grow_umc_init_reg_block(
			&(vi26->mem_adjust_table), 0
		);
		strcpy(atui_mem_adjust->name, "mem_adjust_table");
	}

	atui_branch* atui_memclkpatch = NULL;
	if (vi26->mem_clk_patch.leaves) {
		atui_memclkpatch = grow_umc_init_reg_block(
			&(vi26->mem_clk_patch), 0
		);
		strcpy(atui_memclkpatch->name, "mem_clk_patch_table");
	}

	atui_branch* atui_mc_tile_adjust = NULL;
	if (vi26->mc_tile_adjust.leaves) {
		atui_mc_tile_adjust = grow_umc_init_reg_block(
			&(vi26->mc_tile_adjust), 0
		);
		strcpy(atui_mc_tile_adjust->name, "mc_tile_adjust_table");
	}

	atui_branch* atui_phyinit = NULL;
	if (vi26->mc_phy_init.leaves) {
		atui_phyinit = grow_umc_init_reg_block(
			&(vi26->mc_phy_init), 0
		);
		strcpy(atui_phyinit->name, "mc_phy_init_table");
	}

	atui_branch* atui_tmrs_seq = NULL;
	if (vi26->leaves->tmrs_seq_offset) {
	}

	atui_branch* atui_dram_remap = NULL;
	if (vi26->dram_data_remap) {
		atui_dram_remap = ATUI_MAKE_BRANCH(atom_gddr6_dram_data_remap,  NULL,
			NULL,vi26->dram_data_remap,  0,NULL
		);
	}

	atui_branch* atui_postucode_init = NULL;
	if (vi26->post_ucode_init.leaves) {
		atui_postucode_init = grow_umc_init_reg_block(
			&(vi26->post_ucode_init), 0
		);
		strcpy(atui_postucode_init->name, "post_ucode_init");
	}

	atui_branch* atui_vrammodules = NULL;
	if (vi26->leaves->vram_module_num) {
		atui_vrammodules = grow_vram_module(
			vi26->vram_modules,
			vi26->vram_module_ver,
			vi26->leaves->vram_module_num
		);
	}

	atui_branch* const vi26_children[] = {
		atui_mem_adjust, atui_mc_tile_adjust, atui_phyinit,
		atui_dram_remap, atui_tmrs_seq, atui_postucode_init,
		atui_vrammodules,
	};
	return ATUI_MAKE_BRANCH(atom_vram_info_header_v2_5,  NULL,
		vi26,vi26->leaves,  lengthof(vi26_children), vi26_children
	);
}

inline static atui_branch*
grow_vram_info_v3_0( // TODO finish this
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v3_0* const vi30 = &(vram_info->v3_0);

	atui_branch* atui_mem_tuning = NULL;
	if (vi30->mem_tuning) {
	}

	atui_branch* atui_dram_info = NULL;
	if (vi30->dram_info) {
	}

	atui_branch* atui_tmrs_seq = NULL;
	if (vi30->tmrs_seq) {
	}

	atui_branch* atui_mc_init = NULL;
	if (vi30->mc_init.leaves) {
		atui_mc_init = grow_umc_init_reg_block(
			&(vi30->mc_init), 0
		);
		strcpy(atui_mc_init->name, "mc_init_table");
	}

	atui_branch* atui_dram_remap = NULL;
	if (vi30->dram_data_remap) {
		atui_dram_remap = ATUI_MAKE_BRANCH(atom_gddr6_dram_data_remap,  NULL,
			NULL,vi30->dram_data_remap,  0,NULL
		);
	}

	atui_branch* atui_umc_emuinit = NULL;
	if (vi30->umc_emuinit.leaves) {
		atui_umc_emuinit = grow_umc_init_reg_block(
			&(vi30->umc_emuinit), 0
		);
		strcpy(atui_umc_emuinit->name, "umc_emuinit_table");
	}

	if (vi30->rsvd_tables[0]) {
	}
	if (vi30->rsvd_tables[1]) {
	}

	atui_branch* atui_vrammodules = NULL;
	if (vi30->leaves->vram_module_num) {
		atui_vrammodules = grow_vram_module(
			vi30->vram_modules,
			vi30->vram_module_ver,
			vi30->leaves->vram_module_num
		);
	}

	atui_branch* const vi30_children[] = {
		atui_mem_tuning, atui_dram_info, atui_tmrs_seq, atui_mc_init,
		atui_dram_remap, atui_umc_emuinit, atui_vrammodules,
	};
	return ATUI_MAKE_BRANCH(atom_vram_info_header_v3_0,  NULL,
		vi30,vi30->leaves,  lengthof(vi30_children), vi30_children
	);
}

inline static atui_branch*
grow_vram_info(
		struct atomtree_vram_info* const vram_info,
		struct atom_tree* const atree __unused
		) {
	if (NULL == vram_info->leaves) {
		return NULL;
	}

	atui_branch* atui_vi;
	switch (vram_info->ver) {
		case v1_2: atui_vi = grow_vram_info_v1_2(vram_info); break;
		case v1_3: atui_vi = grow_vram_info_v1_3(vram_info); break;
		case v1_4: atui_vi = grow_vram_info_v1_4(vram_info); break;
		case v2_1: atui_vi = grow_vram_info_v2_1(vram_info); break;
		case v2_2: atui_vi = grow_vram_info_v2_2(vram_info); break;
		case v2_3: atui_vi = grow_vram_info_v2_3(vram_info); break;
		case v2_4: atui_vi = grow_vram_info_v2_4(vram_info); break;
		case v2_5: atui_vi = grow_vram_info_v2_5(vram_info); break;
		case v2_6: atui_vi = grow_vram_info_v2_6(vram_info); break;
		case v3_0: atui_vi = grow_vram_info_v3_0(vram_info); break;
		default:
			atui_vi = ATUI_MAKE_BRANCH(atom_common_table_header,
				"vram_info (header only stub)",
				NULL,vram_info->table_header,  0,NULL
			);
			break;
	}
	return atui_vi;
}

static void
rename_volt_object_with_type(
		atui_branch* const atui_volt_object,
		enum  atom_voltage_type const type
		) {
	struct atui_enum const* const volt_types = & ATUI_ENUM(atom_voltage_type);
	int16_t const naming_enum_i = atui_enum_bsearch(volt_types, type);
	if (0 <= naming_enum_i) {
		sprintf(atui_volt_object->name, "%s (%s)",
			atui_volt_object->origname,
			volt_types->enum_array[naming_enum_i].name
		);
	} else {
		sprintf(atui_volt_object->name, "%s (type %x)",
			atui_volt_object->origname,  type
		);
	}
	assert(strlen(atui_volt_object->name) < sizeof(atui_volt_object->name));
}

inline static atui_branch*
grow_voltageobject_info_v1_1(
		struct atomtree_voltageobject_info* const vo_info
		) {
	struct atomtree_voltage_object* const voltage_objects = (
		vo_info->voltage_objects
	);

	atui_branch* const atui_vo_info = ATUI_MAKE_BRANCH(atom_common_table_header,
		"atom_voltage_objects_info_v1_1",
		NULL,vo_info->leaves,  vo_info->num_voltage_objects,NULL
	);
	atui_branch* atui_volt_object;
	for (uint16_t i=0; i < vo_info->num_voltage_objects; i++) {
		atui_volt_object = ATUI_MAKE_BRANCH(atom_voltage_object_v1, NULL,
			&(voltage_objects[i]),voltage_objects[i].obj,  0,NULL
		);
		rename_volt_object_with_type(
			atui_volt_object, voltage_objects[i].obj->volt_obj_v1.VoltageType
		);
		ATUI_ADD_BRANCH(atui_vo_info, atui_volt_object);
	};
	return atui_vo_info;
}

inline static atui_branch*
grow_voltageobject_info_v1_2(
		struct atomtree_voltageobject_info* const vo_info
		) {
	struct atomtree_voltage_object* const voltage_objects = (
		vo_info->voltage_objects
	);

	atui_branch* const atui_vo_info = ATUI_MAKE_BRANCH(atom_common_table_header,
		"atom_voltage_objects_info_v1_2",
		NULL,vo_info->leaves,  vo_info->num_voltage_objects,NULL
	);
	atui_branch* atui_volt_object;
	for (uint16_t i=0; i < vo_info->num_voltage_objects; i++) {
		atui_volt_object = ATUI_MAKE_BRANCH(atom_voltage_object_v2,  NULL,
			&(voltage_objects[i]),voltage_objects[i].obj,  0,NULL
		);
		rename_volt_object_with_type(
			atui_volt_object, voltage_objects[i].obj->volt_obj_v2.VoltageType
		);
		ATUI_ADD_BRANCH(atui_vo_info, atui_volt_object);
	};
	return atui_vo_info;
}

inline static atui_branch*
grow_voltageobject_info_v3_1(
		struct atomtree_voltageobject_info* const vo_info
		) {
	struct atomtree_voltage_object* const voltage_objects = (
		vo_info->voltage_objects
	);

	atui_branch* const atui_vo_info = ATUI_MAKE_BRANCH(atom_common_table_header,
		"atom_voltage_objects_info_v3_1",
		NULL,vo_info->leaves,  vo_info->num_voltage_objects,NULL
	);

	atui_branch* atui_volt_object;
	struct atui_funcify_args atui_args = {0};
	atuifunc atui_vobj_func;
	for (uint16_t i=0; i < vo_info->num_voltage_objects; i++) {
		switch (voltage_objects[i].obj->header.voltage_mode) {
			case VOLTAGE_OBJ_GPIO_LUT:
			case VOLTAGE_OBJ_PHASE_LUT:
				atui_vobj_func = ATUI_FUNC(atom_gpio_voltage_object_v1);
				break;
			case VOLTAGE_OBJ_VR_I2C_INIT_SEQ:
				atui_vobj_func = ATUI_FUNC(atom_i2c_voltage_object_v1);
				break;
			case VOLTAGE_OBJ_SVID2:
				atui_vobj_func = ATUI_FUNC(atom_svid2_voltage_object_v1);
				break;
			case VOLTAGE_OBJ_MERGED_POWER:
				atui_vobj_func = ATUI_FUNC(atom_merged_voltage_object_v1);
				break;
			case VOLTAGE_OBJ_EVV:
				atui_vobj_func = ATUI_FUNC(atom_evv_voltage_object_v1);
				break;
			case VOLTAGE_OBJ_PWRBOOST_LEAKAGE_LUT:
			case VOLTAGE_OBJ_HIGH_STATE_LEAKAGE_LUT:
			case VOLTAGE_OBJ_HIGH1_STATE_LEAKAGE_LUT:
				atui_vobj_func = ATUI_FUNC(atom_leakage_voltage_object_v1);
				break;
			default:
				atui_vobj_func = ATUI_FUNC(atom_voltage_object_header);
				assert(0);
				break;
		}
		atui_args.atomtree = &(voltage_objects[i]);
		atui_args.suggestbios = voltage_objects[i].obj;
		atui_volt_object = atui_vobj_func(&atui_args);
		rename_volt_object_with_type(
			atui_volt_object, voltage_objects[i].obj->header.voltage_type
		);
		ATUI_ADD_BRANCH(atui_vo_info, atui_volt_object);
	}
	return atui_vo_info;
}


inline static atui_branch*
grow_voltageobject_info_v4_1(
		struct atomtree_voltageobject_info* const vo_info
		) {
	struct atomtree_voltage_object* const voltage_objects = (
		vo_info->voltage_objects
	);
	atui_branch* atui_vo_info = NULL;
	atui_vo_info = ATUI_MAKE_BRANCH(atom_common_table_header,
		"atom_voltage_objects_info_v4_1",
		NULL,vo_info->leaves,  vo_info->num_voltage_objects,NULL
	);

	atui_branch* atui_volt_object;
	struct atui_funcify_args atui_args = {0};
	atuifunc atui_vobj_func;
	for (uint16_t i=0; i < vo_info->num_voltage_objects; i++) {
		switch (voltage_objects[i].obj->header.voltage_mode) {
			case VOLTAGE_OBJ_GPIO_LUT:
			case VOLTAGE_OBJ_PHASE_LUT:
				atui_vobj_func = ATUI_FUNC(atom_gpio_voltage_object_v1);
				break;
			case VOLTAGE_OBJ_VR_I2C_INIT_SEQ:
				atui_vobj_func = ATUI_FUNC(atom_i2c_voltage_object_v1);
				break;
			case VOLTAGE_OBJ_SVID2:
				atui_vobj_func = ATUI_FUNC(atom_svid2_voltage_object_v2);
				break;
			case VOLTAGE_OBJ_MERGED_POWER:
				atui_vobj_func = ATUI_FUNC(atom_merged_voltage_object_v1);
				break;
			case VOLTAGE_OBJ_EVV:
			case VOLTAGE_OBJ_PWRBOOST_LEAKAGE_LUT:
			case VOLTAGE_OBJ_HIGH_STATE_LEAKAGE_LUT:
			case VOLTAGE_OBJ_HIGH1_STATE_LEAKAGE_LUT:
				assert(0);
			default:
				atui_vobj_func = ATUI_FUNC(atom_voltage_object_header);
				assert(0);
				break;
		}
		atui_args.atomtree = &(voltage_objects[i]);
		atui_args.suggestbios = voltage_objects[i].obj;
		atui_volt_object = atui_vobj_func(&atui_args);
		rename_volt_object_with_type(
			atui_volt_object, voltage_objects[i].obj->header.voltage_type
		);
		ATUI_ADD_BRANCH(atui_vo_info, atui_volt_object);
	}
	return atui_vo_info;
}


inline static atui_branch*
grow_voltageobject_info(
		struct atomtree_voltageobject_info* const vo_info,
		struct atom_tree* const atree __unused
		) {
	if (NULL == vo_info->leaves) {
		return NULL;
	}
	atui_branch* atui_vo_info = NULL;

	switch (vo_info->ver) {
		case v1_1: atui_vo_info = grow_voltageobject_info_v1_1(vo_info); break;
		case v1_2: atui_vo_info = grow_voltageobject_info_v1_2(vo_info); break;
		case v3_1: atui_vo_info = grow_voltageobject_info_v3_1(vo_info); break;
		case v4_1: atui_vo_info = grow_voltageobject_info_v4_1(vo_info); break;
		case v4_2: // hopefully v4_2 is the same
			atui_vo_info = grow_voltageobject_info_v4_1(vo_info);
			strcpy(atui_vo_info->name,
				"atom_voltage_objects_info_v4_1 (forced)"
			);
			break;
		default:
			atui_vo_info = ATUI_MAKE_BRANCH(atom_common_table_header,
				"voltageobject_info (header only stub)",
				NULL,vo_info->table_header,  0,NULL
			);
			break;
	}
	return atui_vo_info;
}


inline static atui_branch*
grow_master_datatable_v1_1(
		struct atomtree_master_datatable* const data_table,
		struct atom_tree* const atree __unused
		) {
	struct atomtree_master_datatable_v1_1* const dt11 = &(data_table->v1_1);

	atui_branch* const atui_utilitypipeline = NULL;

	atui_branch* const atui_multimedia_capability_info = NULL;
	atui_branch* const atui_multimedia_config_info = NULL;
	atui_branch* const atui_vesa_timing = NULL;

	atui_branch* const atui_firmwareinfo = grow_firmwareinfo(
		&(dt11->firmwareinfo), atree
	);

	atui_branch* const atui_palette_data = NULL;

	atui_branch* const atui_lcd_info = grow_lcd_info(&(dt11->lcd_info), atree);

	atui_branch* const atui_dig_transmitter_info = NULL;

	atui_branch* const atui_smu_info = grow_smu_info(
		&(dt11->smu_info), atree
	);

	atui_branch* const atui_supported_devices_info = NULL;
	atui_branch* const atui_gpio_i2c_info = NULL;

	atui_branch* const atui_fw_vram = grow_vram_usagebyfirmware(
		&(dt11->vram_usagebyfirmware), atree
	);

	atui_branch* const atui_gpio_pin_lut = grow_gpio_pin_lut(
		&(dt11->gpio_pin_lut), atree
	);

	atui_branch* const atui_vesa_to_internal_mode = NULL;

	atui_branch* const atui_gfx_info = grow_gfx_info(&(dt11->gfx_info), atree);

	atui_branch* const atui_ppt = grow_ppt(&(dt11->powerplayinfo), atree);

	atui_branch* const atui_gpu_virtualization_info = NULL;
	atui_branch* const atui_save_restore_info = NULL;
	atui_branch* const atui_ppll_ss_info = NULL;
	atui_branch* const atui_oem_info = NULL;
	atui_branch* const atui_xtmds_info = NULL;
	atui_branch* const atui_mclk_ss_info = NULL;
	atui_branch* const atui_object_header = NULL;
	atui_branch* const atui_indirect_io_access = NULL;
	atui_branch* const atui_mc_init_parameter = NULL;
	atui_branch* const atui_asic_vddc_info = NULL;
	atui_branch* const atui_asic_internal_ss_info = NULL;
	atui_branch* const atui_tv_video_mode = NULL;

	atui_branch* const atui_vram_info = grow_vram_info(
		&(dt11->vram_info), atree
	);

	atui_branch* const atui_memory_training_info = NULL;
	atui_branch* const atui_integrated_system_info = NULL;
	atui_branch* const atui_asic_profiling_info = NULL;

	atui_branch* const atui_voltageobject_info = grow_voltageobject_info(
		&(dt11->voltageobject_info), atree
	);

	atui_branch* const atui_power_source_info = NULL;
	atui_branch* const atui_service_info = NULL;

	atui_branch* const child_branches[] = {
		atui_firmwareinfo, atui_lcd_info, atui_smu_info,
		atui_fw_vram, atui_gpio_pin_lut, atui_gfx_info, atui_ppt,
		atui_vram_info,
		atui_voltageobject_info
	};
	return ATUI_MAKE_BRANCH(atom_master_data_table_v1_1,  NULL,
		dt11,dt11->leaves,  lengthof(child_branches), child_branches
	);
}

inline static atui_branch*
atomtree_datatable_v2_1_populate_sw_datatables(
		struct atomtree_master_datatable_v2_1* const data_table,
		struct atom_tree* const atree __unused
		) {
	// TODO have a table with a bunch of ATUI_INLINEs pointing at headers
	struct atom_master_data_table_v2_1* const leaves = data_table->leaves;
	return NULL;
}
inline static atui_branch*
grow_master_datatable_v2_1(
		struct atomtree_master_datatable* const data_table,
		struct atom_tree* const atree __unused
		) {
	struct atomtree_master_datatable_v2_1* const dt21 = &(data_table->v2_1);

	atui_branch* const atui_utilitypipeline = NULL;
	atui_branch* const atui_multimedia_info = NULL;

	atui_branch* const atui_smc_dpm_info = grow_smc_dpm_info(
		&(dt21->smc_dpm_info), atree
	);

	atui_branch* const atui_firmwareinfo = grow_firmwareinfo(
		&(dt21->firmwareinfo), atree
	);

	atui_branch* const atui_lcd_info = grow_lcd_info(&(dt21->lcd_info), atree);

	atui_branch* const atui_smu_info = grow_smu_info(&(dt21->smu_info), atree);

	atui_branch* const atui_fw_vram = grow_vram_usagebyfirmware(
		&(dt21->vram_usagebyfirmware), atree
	);

	atui_branch* const atui_gpio_pin_lut = grow_gpio_pin_lut(
		&(dt21->gpio_pin_lut), atree
	);

	atui_branch* const atui_gfx_info = grow_gfx_info(&(dt21->gfx_info), atree);

	atui_branch* const atui_ppt = grow_ppt(&(dt21->powerplayinfo), atree);

	//displayobjectinfo
	//indirectioaccess
	//umc_info
	//dce_info

	atui_branch* const atui_vram_info = grow_vram_info(
		&(dt21->vram_info), atree
	);

	//integratedsysteminfo
	//asic_profiling_info
	//voltageobject_info
	atui_branch* const atui_voltageobject_info = grow_voltageobject_info(
		&(dt21->voltageobject_info), atree
	);

	atomtree_datatable_v2_1_populate_sw_datatables(dt21, atree);

	atui_branch* const child_branches[] = {
		// utility, multimedia
		atui_smc_dpm_info, atui_firmwareinfo, atui_lcd_info, atui_smu_info,
		atui_fw_vram, atui_gpio_pin_lut, atui_gfx_info, atui_ppt,
		// disp obj, indirect, umc, dce,
		atui_vram_info,
		// integrated, asic
		atui_voltageobject_info
	};
	return ATUI_MAKE_BRANCH(atom_master_data_table_v2_1,  NULL,
		dt21,dt21->leaves,  lengthof(child_branches), child_branches
	);
}

inline static atui_branch*
grow_datatables(
		//struct atomtree_master_datatable* const data_table,
		struct atom_tree* const atree __unused
		) {
	struct atomtree_master_datatable* const data_table = &(atree->data_table);
	if (NULL == data_table->leaves) {
		return NULL;
	}
	switch (data_table->ver) {
		case v1_1: return grow_master_datatable_v1_1(data_table, atree);
		case v2_1: return grow_master_datatable_v2_1(data_table, atree);
		default:
			return ATUI_MAKE_BRANCH(atom_common_table_header,
				"atom_master_data_table (header only stub)",
				NULL, data_table->table_header,  0,NULL
			);
	}
}


inline static atui_branch*
grow_atom_rom_header(
		struct atomtree_rom_header* const rom_header,
		struct atom_tree* const atree __unused
		) {
	if (NULL == rom_header->leaves) {
		return NULL;
	}
	atui_branch* const atui_dt = grow_datatables(atree);
	atui_branch* atui_rom_header;
	atuifunc atui_func;
	struct atui_funcify_args atui_args = {
		.atomtree = rom_header,
		.suggestbios = rom_header->leaves,
		.import_branches = &atui_dt,
		.num_import_branches = 1,
	};
	switch (rom_header->ver) {
		case v1_1: atui_func = ATUI_FUNC(atom_rom_header_v1_1); break;
		case v2_1: atui_func = ATUI_FUNC(atom_rom_header_v2_1); break;
		case v2_3: atui_args.rename = "atom_rom_header_v2_2 (forced)"; fall;
		case v2_2: atui_func = ATUI_FUNC(atom_rom_header_v2_2); break;
		default:
			atui_args.rename = "atom_rom_header (header only stub)";
			atui_func = ATUI_FUNC(atom_common_table_header);
			break;
	}
	return atui_func(&atui_args);
}

inline static atui_branch*
grow_pci_tables(
		struct atomtree_pci_tables* const atree_pci
		) {
	struct pci_rom_tables* const tables = atree_pci->pci_tables;

	atui_branch* const atui_pci_tables = ATUI_MAKE_BRANCH(atui_nullstruct,
		"PCI Tables",
		NULL,NULL,  atree_pci->num_images, NULL
	);

	atui_branch* atui_pci;
	struct atui_funcify_args atui_args = {0};
	atuifunc const atui_pci_func[] = { // jump table
		ATUI_FUNC(pci_rom_tables),
		ATUI_FUNC(efi_pci_device_driver_image),
	};
	for (uint8_t i=0; i < atree_pci->num_images; i++) {
		atui_args.suggestbios = tables[i].header;
		atui_args.atomtree = &(tables[i]);
		atui_pci = atui_pci_func[tables[i].is_efi](&atui_args);
		sprintf(atui_pci->name, "%s [%u]", atui_pci->origname, i);
		ATUI_ADD_BRANCH(atui_pci_tables, atui_pci);
	}

	return atui_pci_tables;
}

void
generate_atui(
		struct atom_tree* atree
		) {
	atui_branch* const atui_atom_rom_header = grow_atom_rom_header(
		&(atree->rom_header), atree
	);
	atui_branch* const atui_pci_tables = grow_pci_tables(&(atree->pci_tables));

	atui_branch* const child_branches[] = {
		atui_pci_tables, atui_atom_rom_header
	};
	atree->atui_root = ATUI_MAKE_BRANCH(vbios_rom_header, NULL,
		atree, atree->image,  lengthof(child_branches), child_branches
	);
}
