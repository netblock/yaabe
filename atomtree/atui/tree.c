/*
atui counterpart to atomtree/atomtree.c
walks the atomtree to construct the ATUI tree
*/

#include "standard.h"
#include "atomtree.h"
#include "atui.h"

inline static atui_branch*
grow_smc_dpm_info(
		struct atomtree_smc_dpm_info const* const smc_dpm_info,
		struct atom_tree const* const atree __unused
		) {
	if (NULL == smc_dpm_info->leaves) {
		return NULL;
	}

	atuifunc atui_func;
	atuifunc_args atui_args = {
		.atomtree = smc_dpm_info,
		.suggestbios = smc_dpm_info->leaves,
	};
	switch (smc_dpm_info->ver) {
		case v4_1:  atui_func = _atui_atom_smc_dpm_info_v4_1;  break;
		case v4_3:  atui_func = _atui_atom_smc_dpm_info_v4_3;  break;
		case v4_4:  atui_func = _atui_atom_smc_dpm_info_v4_4;  break;
		case v4_5:  atui_func = _atui_atom_smc_dpm_info_v4_5;  break;
		case v4_6:  atui_func = _atui_atom_smc_dpm_info_v4_6;  break;
		case v4_7:  atui_func = _atui_atom_smc_dpm_info_v4_7;  break;
		case v4_9:  atui_func = _atui_atom_smc_dpm_info_v4_9;  break;
		case v4_10: atui_func = _atui_atom_smc_dpm_info_v4_10; break;
		case v5_0:  atui_func = _atui_atom_smc_dpm_info_table_13_0_7; break;
		default:
			atui_args.rename = "smc_dpm_info (header only stub)";
			atui_func = _atui_atom_common_table_header;
			break;
	}
	return atui_func(&atui_args);
}


inline static atui_branch*
grow_firmwareinfo(
		struct atomtree_firmware_info const* const firmwareinfo,
		struct atom_tree const* const atree __unused
		) {
	if (NULL == firmwareinfo->leaves) {
		return NULL;
	}

	atuifunc atui_func;
	atuifunc_args atui_args = {
		.atomtree = firmwareinfo,
		.suggestbios = firmwareinfo->leaves,
	};
	switch (firmwareinfo->ver) {
		case v1_0: atui_func = _atui_atom_firmware_info_v1_0; break;
		case v1_2: atui_func = _atui_atom_firmware_info_v1_2; break;
		case v1_3: atui_func = _atui_atom_firmware_info_v1_3; break;
		case v1_4: atui_func = _atui_atom_firmware_info_v1_4; break;
		case v2_1: atui_func = _atui_atom_firmware_info_v2_1; break;
		case v2_2: atui_func = _atui_atom_firmware_info_v2_2; break;
		case v3_1: atui_func = _atui_atom_firmware_info_v3_1; break;
		case v3_2: atui_func = _atui_atom_firmware_info_v3_2; break;
		case v3_3: atui_func = _atui_atom_firmware_info_v3_3; break;
		case v3_4: atui_func = _atui_atom_firmware_info_v3_4; break;
		default:
			atui_args.rename = "firmwareinfo (header only stub)";
			atui_func = _atui_atom_common_table_header;
			break;
	}
	return atui_func(&atui_args);
}


inline static atui_branch*
grow_lcd_info(
		struct atomtree_lcd_info const* const lcd_info,
		struct atom_tree const* const atree __unused
		) {
	if (NULL == lcd_info->leaves) {
		return NULL;
	}

	atuifunc atui_func;
	atuifunc_args atui_args = {
		.atomtree =  lcd_info,
		.suggestbios = lcd_info->leaves,
	};
	switch (lcd_info->ver) {
		case v1_1: atui_func = _atui_atom_lvds_info_v1_1;
			// TODO atom_lvds_info_v1_1's ModePatchTableOffset;
			// see amdgpu_atombios_encoder_get_lcd_info
			assert(0);
			break;
		case v1_2: atui_func = _atui_atom_lvds_info_v1_2; break;
		case v1_3: atui_func = _atui_atom_lcd_info_v1_3;  break;
		case v2_1: atui_func = _atui_atom_lcd_info_v2_1;  break;
		default:
			atui_args.rename = "lcd_info (header only stub)";
			atui_func = _atui_atom_common_table_header;
			break;
	}
	return atui_func(&atui_args);
}


inline static atui_branch*
grow_smu_info(
		struct atomtree_smu_info const* const smu_info,
		struct atom_tree const* const atree __unused
		) {
	if (NULL == smu_info->leaves) {
		return NULL;
	}

	atuifunc atui_func;
	atuifunc_args atui_args = {
		.atomtree =  smu_info,
		.suggestbios = smu_info->leaves,
	};
	switch (smu_info->ver) {
		case v3_1: atui_func = _atui_atom_smu_info_v3_1; break;
		case v3_2: atui_func = _atui_atom_smu_info_v3_2; break;
		case v3_3: atui_func = _atui_atom_smu_info_v3_3; break;
		case v3_4: atui_args.rename = "atom_smu_info_v3_5 (forced)"; fall;
		case v3_5: atui_func = _atui_atom_smu_info_v3_5; break;
		case v3_6: atui_func = _atui_atom_smu_info_v3_6; break;
		case v4_0: atui_func = _atui_atom_smu_info_v4_0; break;
		default:
			atui_func = _atui_atom_common_table_header;
			atui_args.rename = "smu_info (header only stub)";
			break;
	}
	return atui_func(&atui_args);
}


inline static atui_branch*
grow_vram_usagebyfirmware(
		struct atomtree_vram_usagebyfirmware const* const fw_vram,
		struct atom_tree const* const atree __unused
		) {
	if (NULL == fw_vram->leaves) {
		return NULL;
	}

	atuifunc atui_func;
	atuifunc_args atui_args = {
		.atomtree =  fw_vram,
		.suggestbios = fw_vram->leaves,
	};
	switch (fw_vram->ver) {
		case v2_1: atui_func = _atui_vram_usagebyfirmware_v2_1; break;
		case v2_2: atui_func = _atui_vram_usagebyfirmware_v2_2; break;
		default:
			atui_func = _atui_atom_common_table_header;
			atui_args.rename = "vram_usagebyfirmware (header only stub)";
			break;
	}
	return atui_func(&atui_args);
}


inline static atui_branch*
grow_gpio_pin_lut(
		struct atomtree_gpio_pin_lut const* const gpio_pin_lut,
		struct atom_tree const* const atree __unused
		) {
	if (NULL == gpio_pin_lut->leaves) {
		return NULL;
	}

	atuifunc atui_func;
	atuifunc_args atui_args = {
		.atomtree = gpio_pin_lut,
		.suggestbios = gpio_pin_lut->leaves,
	};
	switch (gpio_pin_lut->ver) {
		case v2_1: atui_func = _atui_atom_gpio_pin_lut_v2_1; break;
		default:
			atui_func = _atui_atom_common_table_header;
			atui_args.rename = "gpio_pin_lut (header only stub)";
			break;
	}
	return atui_func(&atui_args);
}


inline static atui_branch*
grow_gfx_info(
		struct atomtree_gfx_info const* const gfx_info,
		struct atom_tree const* const atree __unused
		) {
	if (NULL == gfx_info->leaves) {
		return NULL;
	}

	atuifunc atui_func;
	atui_branch* subtables[2] = {NULL};
	atuifunc_args atui_args = {
		.atomtree =  gfx_info,
		.suggestbios = gfx_info->leaves,
		.import_branches = subtables,
		.num_import_branches = lengthof(subtables),
	};

	switch (gfx_info->ver) {
		case v2_1: atui_func = _atui_atom_gfx_info_v2_1; break;
		case v2_2: atui_func = _atui_atom_gfx_info_v2_2; break;
		case v2_3:
			if (gfx_info->table_header->structuresize
					== sizeof(*gfx_info->v2_3)
					) {
				atui_func = _atui_atom_gfx_info_v2_3;
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
				atui_func = _atui_atom_gfx_info_v2_3_2;
			}
			break;
		case v2_4: atui_func = _atui_atom_gfx_info_v2_4; break;
		case v2_6: atui_args.rename = "atom_gfx_info_v2_5 (forced)"; fall;
		case v2_5: atui_func = _atui_atom_gfx_info_v2_5; break;
		case v2_7: atui_func = _atui_atom_gfx_info_v2_7; break;
		case v3_0: atui_func = _atui_atom_gfx_info_v3_0; break;
		default:
			atui_func = _atui_atom_common_table_header;
			atui_args.rename = "gfx_info (header only stub)";
			break;
	}
	return atui_func(&atui_args);
}



inline static atui_branch*
grow_pplib_ppt_state_array(
		struct atomtree_powerplay_table_v4_1 const* const ppt41
		) {
	if (nover == ppt41->state_array_ver) {
		return NULL;
	}

	atui_branch* base;
	atuifunc_args atui_args = {
		.atomtree =  ppt41,
		.suggestbios = ppt41->state_array_base,
		.num_import_branches = ppt41->num_state_array_entries,
	};
	atuifunc atui_state_func;

	switch (ppt41->state_array_ver) {
		case v1_0:
			base = _atui_atom_pplib_state_v1_array(&atui_args);
			atui_state_func = _atui_atom_pplib_state_v1;
			break;
		case v2_0:
			base = _atui_atom_pplib_state_array_v2(&atui_args);
			atui_state_func = _atui_atom_pplib_state_v2;
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
		struct atomtree_powerplay_table_v4_1 const* const ppt41,
		union atom_pplib_clock_info_arrays* const clock_info
		) {
	
	atuifunc_args atui_args = {
		.atomtree = ppt41,
		.suggestbios = clock_info,
	};
	switch (ppt41->clock_info_ver) {
		case ATOM_PPLIB_CLOCK_INFO_R600:
			return _atui_atom_pplib_r600_clock_info_array(&atui_args);
		case ATOM_PPLIB_CLOCK_INFO_RS780:
			return _atui_atom_pplib_rs780_clock_info_array(&atui_args);
		case ATOM_PPLIB_CLOCK_INFO_GREEN:
			return _atui_atom_pplib_evergreen_clock_info_array(&atui_args);
		case ATOM_PPLIB_CLOCK_INFO_SOUTH:
			return _atui_atom_pplib_si_clock_info_array(&atui_args);
		case ATOM_PPLIB_CLOCK_INFO_SEA:
			return _atui_atom_pplib_ci_clock_info_array(&atui_args);
		case ATOM_PPLIB_CLOCK_INFO_SUMO:
			return _atui_atom_pplib_sumo_clock_info_array(&atui_args);
		case ATOM_PPLIB_CLOCK_INFO_CARRIZO:
			return _atui_atom_pplib_cz_clock_info_array(&atui_args);
		default:
			atui_args.rename = "clock_info (header only stub)";
			return _atui_atom_pplib_sized_array_header(&atui_args);
	}
	
	return NULL;
}
inline static atui_branch*
grow_pplib_ppt_extended_header(
		struct atomtree_powerplay_table_v4_1 const* const ppt41
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
		atuifunc_args atui_args = {
			.atomtree = ppt41,
			.suggestbios = ppt41->powertune,
		};
		switch (ppt41->powertune->RevId) {
			case 0:
				powertune = _atui_atom_pplib_powertune_table_v0(&atui_args);
				break;
			case 1:
				powertune = _atui_atom_pplib_powertune_table_v1(&atui_args);
				break;
			default:
				assert(0);
				atui_args.rename = "powertune (header only stub)";
				powertune = _atui_pplib_subtable_header(&atui_args);
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
	atuifunc_args const atui_args = {
		.atomtree = ppt41,
		.suggestbios = ppt41->extended_header,
		.import_branches = extended_children,
		.num_import_branches = lengthof(extended_children),
	};
	switch (ppt41->extended_header_ver) {
		case v1_0: return _atui_atom_pplib_extended_header_v1(&atui_args);
		case v2_0: return _atui_atom_pplib_extended_header_v2(&atui_args);
		case v3_0: return _atui_atom_pplib_extended_header_v3(&atui_args);
		case v4_0: return _atui_atom_pplib_extended_header_v4(&atui_args);
		case v5_0: return _atui_atom_pplib_extended_header_v5(&atui_args);
		case v6_0: return _atui_atom_pplib_extended_header_v6(&atui_args);
		case v7_0: return _atui_atom_pplib_extended_header_v7(&atui_args);
		case v8_0: return _atui_atom_pplib_extended_header_v8(&atui_args);
		case v9_0: return _atui_atom_pplib_extended_header_v9(&atui_args);
		default: assert(0); return NULL; // TODO return size
	}
}
inline static atui_branch*
grow_pplib_ppt(
		struct atomtree_powerplay_table_v4_1 const* const ppt41
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
		atuifunc_args atui_args = {
			.atomtree = ppt41,
			.suggestbios = ppt41->nonclock_info,
		};
		switch (ppt41->nonclock_info_ver) {
			case v1_0:
				nonclock_info = _atui_atom_pplib_nonclock_info_array_v1(
					&atui_args
				);
				break;
			case v2_0:
				nonclock_info = _atui_atom_pplib_nonclock_info_array_v2(
					&atui_args
				);
				break;
			default:
				atui_args.rename = "nonclock_info (header only stub)";
				nonclock_info = _atui_atom_pplib_sized_array_header(
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
		atuifunc_args atui_args = {
			.atomtree = ppt41,
			.suggestbios = ppt41->fan_table,
		};
		switch (ppt41->fan_table->RevId) {
			case 1: fan_table = _atui_atom_pplib_fan_table_v1(&atui_args);break;
			case 2: fan_table = _atui_atom_pplib_fan_table_v2(&atui_args);break;
			case 5:
			case 4:
			case 3: fan_table = _atui_atom_pplib_fan_table_v3(&atui_args);break;
			case 6: fan_table = _atui_atom_pplib_fan_table_v6(&atui_args);break;
			case 7: fan_table = _atui_atom_pplib_fan_table_v7(&atui_args);break;
			default:
				atui_args.rename = "fan_table (header only stub)";
				fan_table = _atui_pplib_subtable_header(&atui_args);
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
		atuifunc_args const atui_args = {
			.atomtree = ppt41,
			.suggestbios = ppt41->cac_leakage,
		};
		if (ppt41->leaves->v1.PlatformCaps.EVV) {
			cac_leakage = _atui_atom_pplib_cac_leakage_record_evv(&atui_args);
		} else {
			cac_leakage = _atui_atom_pplib_cac_leakage_record(&atui_args);
		}
	}

	atui_branch* const ppt41_children[] = {
		state_array, clock_info, nonclock_info,
		//boot_clock_info, boot_nonclock_info,
		thermal_policy, fan_table, extended_header,
		vddc_sclk, vddci_mclk, vddc_mclk, max_on_dc, phase_shed, mvdd_mclk,
		cac_leakage,
	};
	atuifunc_args atui_args = {
		.atomtree =  ppt41,
		.suggestbios = ppt41->leaves,
		.import_branches = ppt41_children,
		.num_import_branches = lengthof(ppt41_children),
	};
	switch (ppt41->pplib_ver) {
		case v5_0: return _atui_atom_pplib_powerplaytable_v5(&atui_args);
		case v4_0: return _atui_atom_pplib_powerplaytable_v4(&atui_args);
		case v3_0: return _atui_atom_pplib_powerplaytable_v3(&atui_args);
		case v2_0: return _atui_atom_pplib_powerplaytable_v2(&atui_args);
		case v1_0: return _atui_atom_pplib_powerplaytable_v1(&atui_args);
		default: return NULL;
	}
}
inline static atui_branch*
atui_generate_pptablev1_ppt(
		struct atomtree_powerplay_table_v7_1 const* const ppt71
		) {
	atui_branch* state_array = NULL;
	if (ppt71->state_array) {
		state_array = ATUI_MAKE_BRANCH(atom_pptable_state_array, NULL,
			ppt71,ppt71->state_array,  0,NULL
		);
	}

	atui_branch* fan_table = NULL;
	if (ppt71->fan_table) {
		atuifunc_args atui_args = {
			.atomtree = ppt71,
			.suggestbios = ppt71->fan_table,
		};
		uint8_t const RevId = ppt71->fan_table->RevId;
		if (7 >= RevId) {
			fan_table = _atui_atom_pptable_fan_table(&atui_args);
		} else if (8 == RevId) {
			fan_table = _atui_atom_fiji_fan_table(&atui_args);
		} else if (9 == RevId) {
			fan_table = _atui_atom_polaris_fan_table(&atui_args);
		} else {
			atui_args.rename = "fan_table (header only stub)";
			fan_table = _atui_pplib_subtable_header(&atui_args);
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
		atuifunc_args atui_args = {
			.atomtree = ppt71,
			.suggestbios = ppt71->sclk_dependency
		};
		switch (ppt71->sclk_dependency->RevId) {
			case 0:
				atui_func = _atui_atom_pptable_sclk_dependency_table;
				break;
			case 1:
				atui_func = _atui_atom_polaris_sclk_dependency_table;
				break;
			default:
				atui_args.rename = "sclk_dependency (header only stub)";
				atui_func = _atui_pplib_subtable_header;
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
		atuifunc_args atui_args = {
			.atomtree = ppt71,
			.suggestbios = ppt71->powertune,
		};
		uint8_t const RevId = ppt71->powertune->RevId;
		if (2 >= RevId) {
			powertune = _atui_atom_pptable_powertune_table(&atui_args);
		} else if (3 == RevId) {
			powertune = _atui_atom_fiji_powertune_table(&atui_args);
		} else if (4 == RevId) {
			powertune = _atui_atom_polaris_powertune_table(&atui_args);
		} else {
			atui_args.rename = "powertune (header only stub)";
			powertune = _atui_pplib_subtable_header(&atui_args);
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
		atuifunc_args atui_args = {
			.atomtree = ppt71,
			.suggestbios = ppt71->pcie_table,
		};
		switch (ppt71->pcie_table->RevId) {
			case 0: atui_func = _atui_atom_pptable_pcie_table; break;
			case 1: atui_func = _atui_atom_polaris_pcie_table; break;
			default:
				atui_args.rename = "pcie_table (header only stub)";
				atui_func = _atui_pplib_subtable_header;
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
		struct atomtree_powerplay_table_v8_1 const* const ppt81
		) {
	atui_branch* state_array = NULL;
	if (ppt81->state_array) {
		state_array = ATUI_MAKE_BRANCH(atom_vega10_state_array, NULL,
			ppt81,ppt81->state_array,  0,NULL
		);
	}

	atui_branch* fan_table = NULL;
	if (ppt81->fan_table) {
		atuifunc_args atui_args = {
			.atomtree = ppt81,
			.suggestbios = ppt81->fan_table,
		};
		uint8_t const RevId = ppt81->fan_table->RevId;
		if (10 == RevId) {
			fan_table = _atui_atom_vega10_fan_table_v1(&atui_args);
		} else if (11 == RevId) {
			fan_table = _atui_atom_vega10_fan_table_v2(&atui_args);
		} else if (12 >= RevId) {
			fan_table = _atui_atom_vega10_fan_table_v3(&atui_args);
		} else {
			atui_args.rename = "fan_table (header only stub)";
			fan_table = _atui_pplib_subtable_header(&atui_args);
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
		atuifunc_args atui_args = {
			.atomtree = ppt81,
			.suggestbios = ppt81->gfxclk_dependency,
		};
		switch (ppt81->gfxclk_dependency->RevId) {
			case 0:
				atui_func = _atui_atom_vega10_gfxclk_dependency_table_v1;
				break;
			case 1:
				atui_func = _atui_atom_vega10_gfxclk_dependency_table_v2;
				break;
			default:
				atui_args.rename = "gfxclk_dependency (header only stub)";
				atui_func = _atui_pplib_subtable_header;
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
		atuifunc_args atui_args = {
			.atomtree = ppt81,
			.suggestbios = ppt81->powertune
		};
		switch (ppt81->powertune->RevId) {
			case 5: atui_func = _atui_atom_vega10_powertune_table_v1;break;
			case 6: atui_func = _atui_atom_vega10_powertune_table_v2;break;
			default:atui_func = _atui_atom_vega10_powertune_table_v3;break;
			/*
			default:
				atui_args.rename = "powertune (header only stub)";
				atui_func = _atui_pplib_subtable_header;
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
		struct atomtree_powerplay_table const* const ppt,
		void const* const smc_pptable
		) {
	atuifunc_args atui_args = {
		.atomtree = ppt,
		.suggestbios = smc_pptable,
	};
	switch (ver) {
		case v3_0: return _atui_smu11_smcpptable_v3(&atui_args);
		case v5_0: return _atui_smu11_smcpptable_v5(&atui_args);
		case v6_0: atui_args.rename = "smu11_smcpptable_v7 (forced)"; fall;
		case v7_0: return _atui_smu11_smcpptable_v7(&atui_args);
		case v8_0: return _atui_smu11_smcpptable_v8(&atui_args);
		default: assert(0);
	}
	return NULL;
}
inline static atui_branch*
grow_ppt(
		struct atomtree_powerplay_table const* const ppt,
		struct atom_tree const* const atree __unused
		) {
	if (NULL == ppt->leaves) {
		return NULL;
	}

	atui_branch* atui_ppt;
	atui_branch* atui_smctable = NULL;
	atuifunc atui_func;
	atuifunc_args atui_args = {
		.atomtree = ppt,
		.suggestbios = ppt->leaves,
		.import_branches = &atui_smctable,
		.num_import_branches = 1,
	};
	switch (ppt->ver) {
		case v1_1:
			atui_ppt = _atui_atom_powerplay_info_v1(&atui_args);
			break;
		case v2_1:
			atui_ppt = _atui_atom_powerplay_info_v2(&atui_args);
			break;
		case v3_1:
			atui_ppt = _atui_atom_powerplay_info_v3(&atui_args);
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
			atui_ppt = _atui_atom_vega20_powerplay_table(&atui_args);
			break;
		case v14_0:
		case v12_0:
			atui_smctable = atui_generate_smc_pptable(
				ppt->v12_0.smc_pptable_ver,
				ppt, &(ppt->v12_0.leaves->smc_pptable)
			);
			atui_ppt = _atui_smu_11_0_powerplay_table(&atui_args);
			break;
		case v19_0: // 6400
		case v18_0: // navi2 xx50
		case v16_0: // 6700XT
		case v15_0:
			atui_smctable = atui_generate_smc_pptable(
				ppt->v15_0.smc_pptable_ver,
				ppt, &(ppt->v15_0.leaves->smc_pptable)
			);
			atui_ppt = _atui_smu_11_0_7_powerplay_table(&atui_args);
			break;
		default:
			atui_args.rename = (
				"smu_powerplay_table_header (header only stub)"
			);
			atui_ppt = _atui_smu_powerplay_table_header(&atui_args);
			break;
	}
	return atui_ppt;
}



static atui_branch*
autogen_regblock_register_sequence(
		struct register_set_entry const* const func_playlist,
		struct atom_reg_setting_data_block const* const data_block,
		struct atomtree_init_reg_block const* const at_regblock
		) {
	uint8_t const num_data_entries = at_regblock->num_data_entries;
	atuifunc_args atui_args = {
		.suggestbios = &(data_block->block_id)
	};
	atui_branch** const all_fields = cralloc(
		(1+num_data_entries) * sizeof(atui_branch*)
	);
	all_fields[0] = _atui_atom_mc_register_setting_id(&atui_args);
	atui_branch** const reg_data_fields = all_fields + 1;

	for (uint8_t i=0; i < num_data_entries; i++) {
		atui_args.suggestbios = &(data_block->reg_data[i]);

		reg_data_fields[i] = func_playlist[i].atui_branch_func(&atui_args);
		if  (_atui_unknown_reg_data == func_playlist[i].atui_branch_func) {
			sprintf(reg_data_fields[i]->leaves[0].name,
				"bad register index [%02u]: 0x%04X",
				i,  func_playlist[i].address
			);
		}
	}

	atui_branch* const auto_sequence = ATUI_MAKE_BRANCH(atui_nullstruct, NULL,
		NULL,NULL,  0,NULL
	);
	// set size metadata for copy/paste
	auto_sequence->prefer_contiguous = true;
	auto_sequence->table_start = (void*) data_block;
	auto_sequence->table_size = at_regblock->data_block_element_size;

	// steal leaves
	atui_assimilate(auto_sequence, all_fields, (1+num_data_entries));
	free(all_fields);

	return auto_sequence;
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
grow_init_reg_block(
		struct atomtree_init_reg_block const* const at_regblock,
		struct atomtree_vram_module const* const vram_modules,
		atuifunc const atui_strap_func
		) {
	enum register_block_type const reg_type = at_regblock->reg_type;
	struct atom_reg_setting_data_block const* const* const data_blocks =
		(void*) at_regblock->data_blocks;
	enum atomtree_common_version const vram_module_ver =
		vram_modules[0].vram_module_ver;

	assert(reg_type);
	assert(
		(COMMON_SET_UNKNOWN == at_regblock->reg_set)
		== (NULL == atui_strap_func)
	);

	atui_branch* const atui_strap_set = ATUI_MAKE_BRANCH(atui_nullstruct, NULL,
		NULL,NULL,  at_regblock->num_data_blocks, NULL
	);

	struct register_set_entry* func_playlist = NULL;
	if ((NULL == atui_strap_func) && at_regblock->num_data_blocks) {
		func_playlist = register_set_build_atuifunc_playlist(
			at_regblock, &GMC_reg_set, true
		);
	}

	char const* table_name;
	char const* strap_format_new;
	char const* strap_format_old;
	switch (reg_type) {
		case REG_BLOCK_MEM_ADJUST:
			table_name = "mem_adjust_table";
			strap_format_new = "vendor adjust [%02u]: %s (%s)";
			strap_format_old = "vendor adjust [%02u]: %s";
			break;
		case REG_BLOCK_MEM_CLK_PATCH:
			table_name = "mem_clk_patch";
			strap_format_new = "Timings [%02u]: %s (%s): %u MHz";
			strap_format_old = "Timings [%02u]: %s %u MHz";
			break;
		case REG_BLOCK_MC_TILE_ADJUST:
			table_name = "mc_tile_adjust";
			strap_format_new = "tile adjust [%02u]";
			strap_format_old = NULL;
			break;
		case REG_BLOCK_MC_PHY_INIT:
			table_name = "mc_phy_init";
			strap_format_new = "phy init [%02u]";
			strap_format_old = NULL;
			break;
	};

	atui_branch* atui_strap;
	atuifunc_args atui_args = {0};
	char const* vendor_part[2] = {0};
	bool const uses_vendor_parts = (NULL != strap_format_old);
	bool const vram_module_v8_hack = (
		// uniquely, atom_vram_module_v8 uses McTunningSetId to ID
		// mem_adjust table. It seems to exist as a way to exlude the
		// 'generic' vram_module.
		(REG_BLOCK_MEM_ADJUST == reg_type)
		&& (v1_8 == vram_modules[0].vram_module_ver)
		&& (GENERIC == vram_modules[0].v1_8->MemoryVendorID.vendor_code)
	);

	for (uint8_t i = 0; i < at_regblock->num_data_blocks; i++) {
		if (atui_strap_func) {
			atui_args.suggestbios = data_blocks[i];
			atui_strap = atui_strap_func(&atui_args);
		} else {
			atui_strap = autogen_regblock_register_sequence(
				func_playlist, data_blocks[i], at_regblock
			);
		}
		ATUI_ADD_BRANCH(atui_strap_set, atui_strap);

		union atom_mc_register_setting_id block_id = data_blocks[i]->block_id;
		if (uses_vendor_parts) {
			struct atomtree_vram_module const* vmod =  &(
				vram_modules[block_id.mem_block_id + vram_module_v8_hack]
			);
			get_memory_vendor_part_strs(vmod, vendor_part);
			#ifndef NDEBUG // test if vram_module_v8_hack is sane
			if ((v1_8==vram_module_ver) && (REG_BLOCK_MEM_ADJUST==reg_type)) {
				assert(vmod->v1_8->McTunningSetId == block_id.mem_block_id);
			}
			#endif
		}
		if (v1_7 <= vram_module_ver) {
			sprintf(atui_strap->name, strap_format_new,
				i,  vendor_part[1], vendor_part[0],
				(block_id.mem_clock_range / 100)
			);
		} else { // atom_vram_module_v6 and older don't have part strings
			sprintf(atui_strap->name, strap_format_old,
				i,                  vendor_part[0],
				(block_id.mem_clock_range / 100)
			);
		}
		assert(strlen(atui_strap->name) < sizeof(atui_strap->name));
	}
	if (at_regblock->num_data_blocks) {
		if (atui_strap_func) {
			strcpy(atui_strap_set->name, atui_strap->origname);
		} else {
			sprintf(atui_strap_set->name, "%s (auto decode; has inaccuracies)",
				table_name
			);
			free(func_playlist);
		}
		atui_strap_set->prefer_contiguous = true;
		atui_strap_set->table_start = at_regblock->data_blocks[0];
		atui_strap_set->table_size = at_regblock->data_block_table_size;
	}

	return ATUI_MAKE_BRANCH(atom_init_reg_block,  table_name,
		at_regblock, at_regblock->leaves,  1, &atui_strap_set
	);
}

static atui_branch*
grow_mem_adjust_table(
		struct atomtree_init_reg_block const* const mem_adjust_table,
		struct atomtree_vram_module const* const vram_modules
		) {
	atuifunc atui_strap_func = NULL;
	switch (mem_adjust_table->reg_set) {
	}
	return grow_init_reg_block(mem_adjust_table, vram_modules, atui_strap_func);
}

static atui_branch*
grow_mem_clk_patch(
		struct atomtree_init_reg_block const* const mem_clk_patch,
		struct atomtree_vram_module const* const vram_modules
		) {
	atuifunc atui_strap_func = NULL;
	switch (mem_clk_patch->reg_set) {
		case TIMINGS_SET_POLARIS:
			atui_strap_func = _atui_timings_set_polaris;
			break;
		case TIMINGS_SET_ISLANDS_DDR3:
			atui_strap_func = _atui_timings_set_islands_ddr3;
			break;
		case TIMINGS_SET_ISLANDS_GDDR5:
			atui_strap_func = _atui_timings_set_islands_gddr5;
			break;
		case TIMINGS_SET_FIJI:
			atui_strap_func = _atui_timings_set_fiji;
			break;
	}
	return grow_init_reg_block(mem_clk_patch, vram_modules, atui_strap_func);
}

static atui_branch*
grow_mc_tile_adjust(
		struct atomtree_init_reg_block const* const mc_tile_adjust,
		struct atomtree_vram_module const* const vram_modules
		) {
	atuifunc atui_strap_func = NULL;
	switch (mc_tile_adjust->reg_set) {
	}
	return grow_init_reg_block(mc_tile_adjust, vram_modules, atui_strap_func);
}

static atui_branch*
grow_init_mc_phy_init(
		struct atomtree_init_reg_block const* const mc_phy_init,
		struct atomtree_vram_module const* const vram_modules
		) {
	atuifunc atui_strap_func = NULL;
	switch (mc_phy_init->reg_set) {
	}
	return grow_init_reg_block(mc_phy_init, vram_modules, atui_strap_func);
}


static atui_branch*
grow_umc_init_reg_block(
		struct atomtree_umc_init_reg_block const* const at_regblock,
		uint8_t const num_extra_atuibranches
		) {
	return ATUI_MAKE_BRANCH(atom_umc_init_reg_block,  NULL,
		at_regblock, at_regblock->leaves,  num_extra_atuibranches, NULL
	);
}


inline static atui_branch*
grow_atom_memory_timing_format(
		struct atomtree_vram_module const* const vram_module,
		enum atom_dgpu_vram_type const memory_type,
		union atom_memory_timing_format const* const timing_format_start
		) {
	union {
		void const* raw;
		struct atom_memory_timing_format_v0 const* v1_0;
		struct atom_memory_timing_format_v1 const* v1_1;
		struct atom_memory_timing_format_v2 const* v1_2;
	} strap = {
		.raw = timing_format_start
	};
	uint8_t const count = vram_module->num_memory_timing_format;

	atui_branch* const atui_straps = ATUI_MAKE_BRANCH(atui_nullstruct,  NULL,
		NULL,NULL,  count,NULL
	);
	atui_straps->prefer_contiguous = true;
	atui_straps->table_start = (void*) timing_format_start;
	atui_straps->table_size = vram_module->memory_timing_format_total_size;


	atui_branch* atui_mrs[4] = {NULL};
	atuifunc_args atui_mrs_args = {0};
	atuifunc atui_mrs_funcs[lengthof(atui_mrs)] = {
		_atui_atui_nullstruct // easier than null-testing
	};
	switch (memory_type) { // mrs in straps
		case ATOM_DGPU_VRAM_TYPE_DDR2: // non-G
			atui_mrs_funcs[0] = _atui_ddr2_mr0;
			atui_mrs_funcs[1] = _atui_ddr2_emr1;
			atui_mrs_funcs[2] = _atui_ddr2_emr2;
			break;
		case ATOM_DGPU_VRAM_TYPE_DDR3: // non-G
			atui_mrs_funcs[0] = _atui_ddr3_mr0;
			atui_mrs_funcs[1] = _atui_ddr3_mr1;
			atui_mrs_funcs[2] = _atui_ddr3_mr2;
			break;
		case ATOM_DGPU_VRAM_TYPE_GDDR3:
			atui_mrs_funcs[0] = _atui_gddr3_mr0;
			atui_mrs_funcs[1] = _atui_gddr3_emr1;
			// GDDR3 has no MR2
			break;
		case ATOM_DGPU_VRAM_TYPE_GDDR4:
			atui_mrs_funcs[0] = _atui_gddr4_mr0;
			atui_mrs_funcs[1] = _atui_gddr4_emr1;
			atui_mrs_funcs[2] = _atui_gddr4_emr2;
			break;
		case ATOM_DGPU_VRAM_TYPE_GDDR5_2:
		case ATOM_DGPU_VRAM_TYPE_GDDR5:
			atui_mrs_funcs[0] = _atui_gddr5_mr0;
			atui_mrs_funcs[1] = _atui_gddr5_mr1;
			atui_mrs_funcs[2] = _atui_gddr5_mr4;
			atui_mrs_funcs[3] = _atui_gddr5_mr5;
			break;
		default:
			assert(0);
			break;
	};
	

	atui_branch* atui_timings;
	atuifunc_args atui_args = {
		.atomtree = vram_module,
		.import_branches = atui_mrs,
		.num_import_branches = lengthof(atui_mrs),
	};

	switch (vram_module->memory_timing_format_ver) {
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
				atui_args.suggestbios = strap.v1_0;
				atui_timings = _atui_atom_memory_timing_format_v0(&atui_args);
				sprintf(atui_timings->name, "MemTiming (%u MHz)",
					(strap.v1_0->ClkRange / 100)
				);
				ATUI_ADD_BRANCH(atui_straps, atui_timings);
				strap.v1_0++;
			}
			strcpy(atui_straps->name, "atom_memory_timing_format_v0");
			break;
		case v1_1:
			for (uint8_t i=0; i < count; i++) {
				atui_mrs_args.suggestbios = &(strap.v1_1->MR0);
				atui_mrs[0] = atui_mrs_funcs[0](&atui_mrs_args);
				atui_mrs_args.suggestbios = &(strap.v1_1->MR1);
				atui_mrs[1] = atui_mrs_funcs[1](&atui_mrs_args);
				atui_mrs_args.suggestbios = &(strap.v1_1->MR5);
				atui_mrs[3] = atui_mrs_funcs[3](&atui_mrs_args);
				atui_args.suggestbios = strap.v1_1;
				atui_timings = _atui_atom_memory_timing_format_v1(&atui_args);
				sprintf(atui_timings->name, "MemTiming (%u MHz)",
					(strap.v1_1->ClkRange / 100)
				);
				ATUI_ADD_BRANCH(atui_straps, atui_timings);
				strap.v1_1++;
			}
			strcpy(atui_straps->name, "atom_memory_timing_format_v1");
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
				atui_args.suggestbios = strap.v1_2;
				atui_timings = _atui_atom_memory_timing_format_v2(&atui_args);
				sprintf(atui_timings->name, "MemTiming (%u MHz)",
					(strap.v1_2->ClkRange / 100)
				);
				ATUI_ADD_BRANCH(atui_straps, atui_timings);
				strap.v1_2++;
			}
			strcpy(atui_straps->name, "atom_memory_timing_format_v2");
			break;
	};

	return atui_straps;
}

static void
grow_mr2_mr3(
		enum atom_dgpu_vram_type const memory_type,
		atui_branch** const targets,
		void* const mr2,
		void* const mr3
		) {
	atuifunc_args atui_mrs_args = {0};
	switch (memory_type) {
		case ATOM_DGPU_VRAM_TYPE_DDR2: // non-G
			atui_mrs_args.suggestbios = mr2;
			targets[0] = _atui_ddr2_emr2(&atui_mrs_args);
			atui_mrs_args.suggestbios = mr3;
			targets[1] = _atui_ddr2_emr3(&atui_mrs_args);
			break;
		case ATOM_DGPU_VRAM_TYPE_DDR3: // non-G
			atui_mrs_args.suggestbios = mr2;
			targets[0] = _atui_ddr3_mr2(&atui_mrs_args);
			atui_mrs_args.suggestbios = mr3;
			targets[1] = _atui_ddr3_mr3(&atui_mrs_args);
			break;
		case ATOM_DGPU_VRAM_TYPE_GDDR4:
			atui_mrs_args.suggestbios = mr2;
			targets[0] = _atui_gddr4_emr2(&atui_mrs_args);
			atui_mrs_args.suggestbios = mr3;
			targets[1] = _atui_gddr4_emr3(&atui_mrs_args);
			break;
		case ATOM_DGPU_VRAM_TYPE_GDDR5_2:
		case ATOM_DGPU_VRAM_TYPE_GDDR5:
			atui_mrs_args.suggestbios = mr2;
			targets[0] = _atui_gddr5_mr2(&atui_mrs_args);
			atui_mrs_args.suggestbios = mr3;
			targets[1] = _atui_gddr5_mr3(&atui_mrs_args);
			break;
		case ATOM_DGPU_VRAM_TYPE_HBM:
			atui_mrs_args.suggestbios = mr2;
			targets[0] = _atui_hbm_mr2(&atui_mrs_args);
			atui_mrs_args.suggestbios = mr3;
			targets[1] = _atui_hbm_mr3(&atui_mrs_args);
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
		union memory_vendor_id const vendor_id,
		uint8_t const index
		) {
	struct atui_enum const* const gddr_vendors = &ATUI_ENUM(GDDR_MEM_VENDOR_e);
	enum GDDR_MEM_VENDOR_e const code = vendor_id.vendor_code;
	assert(code <= gddr_vendors->num_entries);
	if (code <= gddr_vendors->num_entries) {
		sprintf(atui_vmod->name, "%s [%02u]: %s",
			atui_vmod->origname,  index,  gddr_vendors->enum_array[code].name
		);
	}
}

static atui_branch*
grow_vram_module(
		struct atomtree_vram_module const* const vram_modules,
		enum atomtree_common_version const vram_modules_ver,
		uint8_t const count
		) {
	atui_branch* const atui_vram_modules = ATUI_MAKE_BRANCH(atui_nullstruct,
		NULL,  NULL,NULL,  count,NULL
	);

	if (count) {
		atui_vram_modules->prefer_contiguous = true;
		atui_vram_modules->table_start = vram_modules[0].leaves;
		atui_vram_modules->table_size = (
			vram_modules[count-1].leaves
			- vram_modules[0].leaves
			//pseudo: + vram_modules[count-1].leaves->ModuleSize
		);
	}

	// all the grows should look somewhat similar
	// v1_3 to v1_8 should look very similar to each other
	// v1_9 to v3_0 should look very similar to each other
	struct atomtree_vram_module const* vmod;
	atui_branch* atui_vmod;
	atui_branch* atui_children[3] = {}; // both mrs and timings
	switch (vram_modules_ver) {
		case v1_3:
			for (uint8_t i=0; i < count; i++) {
				vmod = &(vram_modules[i]);

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
				ATUI_ADD_BRANCH(atui_vram_modules, atui_vmod);
				rename_vram_module_with_vendor(
					atui_vmod, vmod->v1_3->MemoryVendorID, i
				);
			}
			strcpy(atui_vram_modules->name, "atom_vram_module_v3");
			if (count) {
				atui_vram_modules->table_size += (
					vram_modules[count-1].v1_3->ModuleSize
				);
			}
			break;
		case v1_4:
			for (uint8_t i=0; i < count; i++) {
				vmod = &(vram_modules[i]);

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
				ATUI_ADD_BRANCH(atui_vram_modules, atui_vmod);
				rename_vram_module_with_vendor(
					atui_vmod, vmod->v1_4->MemoryVendorID, i
				);
			}
			strcpy(atui_vram_modules->name, "atom_vram_module_v4");
			if (count) {
				atui_vram_modules->table_size += (
					vram_modules[count-1].v1_4->ModuleSize
				);
			}
			break;
		case v1_7:
			atuifunc_args atui_map_args = {
				.rename = "ChannelMapCfg"
			};
			atuifunc chremap;
			if (count) {
				if (v7_1 == vram_modules[0].gmc_bitfields_ver) {
					chremap = _atui_mc_shared_chremap_7_1;
				} else {
					chremap = _atui_mc_shared_chremap_6_0;
				}
			}
			for (uint8_t i=0; i < count; i++) {
				vmod = &(vram_modules[i]);

				atui_map_args.suggestbios = &(vmod->v1_7->ChannelMapCfg);
				atui_children[0] = chremap(&atui_map_args);

				grow_mr2_mr3(
					vmod->v1_7->MemoryType, atui_children+1,
					&(vmod->v1_7->MR2), &(vmod->v1_7->MR3)
				);

				atui_vmod = ATUI_MAKE_BRANCH(atom_vram_module_v7,  NULL,
					vmod, vmod->v1_7,  lengthof(atui_children), atui_children
				);
				ATUI_ADD_BRANCH(atui_vram_modules, atui_vmod);
				rename_vram_module_with_vendor(
					atui_vmod, vmod->v1_7->MemoryVendorID, i
				);
			}
			if (count) {
				atui_vram_modules->table_size += (
					vram_modules[count-1].v1_7->ModuleSize
				);
			}
			strcpy(atui_vram_modules->name, "atom_vram_module_v7");
			break;
		case v1_8:
			for (uint8_t i=0; i < count; i++) {
				vmod = &(vram_modules[i]);

				grow_mr2_mr3(
					vmod->v1_8->MemoryType, atui_children,
					&(vmod->v1_8->MR2), &(vmod->v1_8->MR3)
				);

				atui_vmod = ATUI_MAKE_BRANCH(atom_vram_module_v8,  NULL,
					vmod, vmod->v1_8,  lengthof(atui_children), atui_children
				);
				ATUI_ADD_BRANCH(atui_vram_modules, atui_vmod);
				rename_vram_module_with_vendor(
					atui_vmod, vmod->v1_8->MemoryVendorID, i
				);
			}
			strcpy(atui_vram_modules->name, "atom_vram_module_v8");
			if (count) {
				atui_vram_modules->table_size += (
					vram_modules[count-1].v1_8->ModuleSize
				);
			}
			break;
		case v1_9:
			for (uint8_t i=0; i < count; i++) {
				vmod = &(vram_modules[i]);

				atui_vmod = ATUI_MAKE_BRANCH(atom_vram_module_v9, NULL,
					vmod, vmod->v1_9,  lengthof(atui_children), atui_children
				);
				ATUI_ADD_BRANCH(atui_vram_modules, atui_vmod);
				rename_vram_module_with_vendor(
					atui_vmod, vmod->v1_9->vendor_rev_id, i
				);
			}
			strcpy(atui_vram_modules->name, "atom_vram_module_v9");
			if (count) {
				atui_vram_modules->table_size += (
					vram_modules[count-1].v1_9->vram_module_size
				);
			}
			break;
		case v1_10:
			for (uint8_t i=0; i < count; i++) {
				vmod = &(vram_modules[i]);

				atui_vmod = ATUI_MAKE_BRANCH(atom_vram_module_v10,  NULL,
					vmod, vmod->v1_10,  lengthof(atui_children), atui_children
				);
				ATUI_ADD_BRANCH(atui_vram_modules, atui_vmod);
				rename_vram_module_with_vendor(
					atui_vmod, vmod->v1_10->vendor_rev_id, i
				);
			}
			strcpy(atui_vram_modules->name, "atom_vram_module_v10");
			if (count) {
				atui_vram_modules->table_size += (
					vram_modules[count-1].v1_10->vram_module_size
				);
			}
			break;
		case v1_11:
			for (uint8_t i=0; i < count; i++) {
				vmod = &(vram_modules[i]);

				atui_vmod = ATUI_MAKE_BRANCH(atom_vram_module_v11,  NULL,
					vmod, vmod->v1_11,  lengthof(atui_children), atui_children
				);
				ATUI_ADD_BRANCH(atui_vram_modules, atui_vmod);
				rename_vram_module_with_vendor(
					atui_vmod, vmod->v1_11->vendor_rev_id, i
				);
			}
			strcpy(atui_vram_modules->name, "atom_vram_module_v11");
			if (count) {
				atui_vram_modules->table_size += (
					vram_modules[count-1].v1_11->vram_module_size
				);
			}
			break;
		case v3_0:
			for (uint8_t i=0; i < count; i++) {
				vmod = &(vram_modules[i]);

				atui_vmod = ATUI_MAKE_BRANCH(atom_vram_module_v3_0,  NULL,
					vmod, vmod->v3_0,  lengthof(atui_children), atui_children
				);
				ATUI_ADD_BRANCH(atui_vram_modules, atui_vmod);
				rename_vram_module_with_vendor(
					atui_vmod, vmod->v3_0->dram_vendor_id, i
				);
			}
			strcpy(atui_vram_modules->name, "atom_vram_module_v3_0");
			atui_vram_modules->table_size += sizeof(*(vram_modules[0].v3_0));
			break;
		default:
			assert(0); // TODO implement
			break;
	}
	return atui_vram_modules;
}

inline static atui_branch*
grow_gddr6_dram_data_remap(
		struct atomtree_gddr6_dram_data_remap const* const at_remap
		) {
	if (NULL == at_remap->dram_data_remap) {
		return NULL;
	}
	return ATUI_MAKE_BRANCH(atom_gddr6_dram_data_remap,  NULL,
		at_remap, at_remap->dram_data_remap,  0,NULL
	);
}

inline static atui_branch*
grow_vram_info_v1_2(
		struct atomtree_vram_info const* const vram_info
		) {
	struct atomtree_vram_info_v1_2 const* const vi12 = &(vram_info->v1_2);

	atui_branch* atui_vram_modules = NULL;
	if (vi12->leaves->NumOfVRAMModule) {
		atui_vram_modules = grow_vram_module(
			vi12->vram_modules,
			vi12->vram_module_ver,
			vi12->leaves->NumOfVRAMModule
		);
	}

	return ATUI_MAKE_BRANCH(atom_vram_info_v1_2,  NULL,
		vi12,vi12->leaves,  1,&atui_vram_modules
	);
}

inline static atui_branch*
grow_vram_info_v1_3(
		struct atomtree_vram_info const* const vram_info
		) {
	struct atomtree_vram_info_v1_3 const* const vi13 = &(vram_info->v1_3);

	atui_branch* atui_mem_adjust = NULL;
	if (vi13->mem_adjust_table.leaves) {
		atui_mem_adjust = ATUI_MAKE_BRANCH(atom_init_reg_block,
			"mem_adjust_table",
			&(vi13->mem_adjust_table), vi13->mem_adjust_table.leaves,  0,NULL
		);
	}

	atui_branch* atui_memclkpatch = NULL;
	if (vi13->mem_clk_patch.leaves) {
		atui_memclkpatch = ATUI_MAKE_BRANCH(atom_init_reg_block,
			"mem_clk_patch_table",
			&(vi13->mem_clk_patch), vi13->mem_clk_patch.leaves,  0,NULL
		);
	}

	atui_branch* atui_vram_modules = NULL;
	if (vi13->leaves->NumOfVRAMModule) {
		atui_vram_modules = grow_vram_module(
			vi13->vram_modules,
			vi13->vram_module_ver,
			vi13->leaves->NumOfVRAMModule
		);
	}

	atui_branch* const vi13_children[] = {
		atui_mem_adjust, atui_memclkpatch, atui_vram_modules
	};
	return ATUI_MAKE_BRANCH(atom_vram_info_v1_3,  NULL,
		vi13,vi13->leaves,  lengthof(vi13_children), vi13_children
	);
}

inline static atui_branch*
grow_vram_info_v1_4(
		struct atomtree_vram_info const* const vram_info
		) {
	struct atomtree_vram_info_v1_4 const* const vi14 = &(vram_info->v1_4);

	atui_branch* atui_mem_adjust = NULL;
	if (vi14->mem_adjust_table.leaves) {
		atui_mem_adjust = ATUI_MAKE_BRANCH(atom_init_reg_block,
			"mem_adjust_table",
			&(vi14->mem_adjust_table), vi14->mem_adjust_table.leaves,  0,NULL
		);
	}

	atui_branch* atui_memclkpatch = NULL;
	if (vi14->mem_clk_patch.leaves) {
		// TODO See grow_vram_info_v1_3
		atui_memclkpatch = ATUI_MAKE_BRANCH(atom_init_reg_block,
			"mem_clk_patch_table",
			&(vi14->mem_clk_patch), vi14->mem_clk_patch.leaves,  0,NULL
		);
	}

	atui_branch* atui_vram_modules = NULL;
	if (vi14->leaves->NumOfVRAMModule) {
		atui_vram_modules = grow_vram_module(
			vi14->vram_modules,
			vi14->vram_module_ver,
			vi14->leaves->NumOfVRAMModule
		);
	}

	atui_branch* const vi14_children[] = {
		atui_mem_adjust, atui_memclkpatch, atui_vram_modules,
	};
	return ATUI_MAKE_BRANCH(atom_vram_info_v1_4,  NULL,
		vi14,vi14->leaves,  lengthof(vi14_children), vi14_children
	);
}

inline static atui_branch*
grow_vram_info_v2_1(
		struct atomtree_vram_info const* const vram_info
		) {
	struct atomtree_vram_info_header_v2_1 const* const vi21 = &(vram_info->v2_1);

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
		atui_perbytepreset = ATUI_MAKE_BRANCH(atom_init_reg_block,
			"per_byte_preset_table",
			&(vi21->per_byte_preset), vi21->per_byte_preset.leaves,  0,NULL
		);
	}

	atui_branch* atui_vram_modules = NULL;
	if (vi21->leaves->NumOfVRAMModule) {
		atui_vram_modules = grow_vram_module(
			vi21->vram_modules,
			vi21->vram_module_ver,
			vi21->leaves->NumOfVRAMModule
		);
	}

	atui_branch* const vi21_children[] = {
		atui_mem_adjust, atui_memclkpatch, atui_perbytepreset, atui_vram_modules
	};
	return ATUI_MAKE_BRANCH(atom_vram_info_header_v2_1,  NULL,
		vi21,vi21->leaves,  lengthof(vi21_children), vi21_children
	);
}

inline static atui_branch*
grow_vram_info_v2_2(
		struct atomtree_vram_info const* const vram_info
		) {
	struct atomtree_vram_info_header_v2_2 const* const vi22 = &(vram_info->v2_2);

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

	atui_branch* atui_vram_modules = NULL;
	if (vi22->leaves->NumOfVRAMModule) {
		atui_vram_modules = grow_vram_module(
			vi22->vram_modules,
			vi22->vram_module_ver,
			vi22->leaves->NumOfVRAMModule
		);
	}

	atui_branch* const vi22_children[] = {
		atui_mem_adjust, atui_memclkpatch, atui_mc_tile_adjust, atui_phyinit,
		atui_dram_remap, atui_vram_modules
	};
	return ATUI_MAKE_BRANCH(atom_vram_info_header_v2_2,  NULL,
		vi22,vi22->leaves,  lengthof(vi22_children), vi22_children
	);

}

inline static atui_branch*
grow_vram_info_v2_3(
		struct atomtree_vram_info const* const vram_info
		) {
	struct atomtree_vram_info_header_v2_3 const* const vi23 = &(vram_info->v2_3);

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
		atuifunc_args atui_args = {0};
		if (vi23->uses_vega20_timings) {
			atui_strap_func = _atui_timings_set_vega20;
		} else {
			atui_strap_func = _atui_timings_set_vega10;
		}
		char const* vendor_part[2];
		for (uint16_t i=0; i < mem_clk_patch->num_data_blocks; i++) {
			atui_args.suggestbios = data_blocks[i];
			atui_strap = atui_strap_func(&atui_args);
			ATUI_ADD_BRANCH(atui_mem_timings, atui_strap);

			union atom_mc_register_setting_id block_id = (
				data_blocks[i]->block_id
			);
			get_memory_vendor_part_strs(
				&(vi23->vram_modules[block_id.mem_block_id]),
				vendor_part
			);
			sprintf(atui_strap->name, "Timings [%02u]: %s (%s): %u MHz",
				i,  vendor_part[1], vendor_part[0],
				(block_id.mem_clock_range / 100)
			);
			assert(strlen(atui_strap->name) < sizeof(atui_strap->name));
		}
		if (mem_clk_patch->num_data_blocks) {
			strcpy(atui_mem_timings->name, atui_strap->origname);
			atui_mem_timings->prefer_contiguous = true;
			atui_mem_timings->table_start = mem_clk_patch->data_blocks[0];
			atui_mem_timings->table_size = mem_clk_patch->data_block_table_size;
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

	atui_branch* atui_vram_modules = NULL;
	if (vi23->leaves->vram_module_num) {
		atui_vram_modules = grow_vram_module(
			vi23->vram_modules,
			vi23->vram_module_ver,
			vi23->leaves->vram_module_num
		);
	}

	atui_branch* const vi23_children[] = {
		atui_mem_adjust, atui_memclkpatch, atui_mc_tile_adjust, atui_phyinit,
		atui_dram_remap, atui_hbm_tmrs, atui_postucode_init,
		atui_vram_modules
	};

	return ATUI_MAKE_BRANCH(atom_vram_info_header_v2_3,  NULL,
		vi23,vi23->leaves,  lengthof(vi23_children), vi23_children
	);
}

inline static atui_branch*
grow_vram_info_v2_4(
		struct atomtree_vram_info const* const vram_info
		) {
	struct atomtree_vram_info_header_v2_4 const* const vi24 = &(vram_info->v2_4);
	struct atom_vram_info_header_v2_4 const* const leaves = vram_info->leaves;

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
		atuifunc const atui_strap_func = _atui_timings_set_navi1;
		atuifunc_args atui_args = {0};
		char const* vendor_part[2];
		for (uint16_t i=0; i < mem_clk_patch->num_data_blocks; i++) {
			atui_args.suggestbios = data_blocks[i];
			atui_strap = atui_strap_func(&atui_args);
			ATUI_ADD_BRANCH(atui_mem_timings, atui_strap);

			union atom_mc_register_setting_id block_id = (
				data_blocks[i]->block_id
			);
			get_memory_vendor_part_strs(
				&(vi24->vram_modules[data_blocks[i]->block_id.mem_block_id]),
				vendor_part
			);
			sprintf(atui_strap->name, "Timings [%02u]: %s (%s): %u MHz",
				i,  vendor_part[1], vendor_part[0],
				(block_id.mem_clock_range / 100)
			);
			assert(strlen(atui_strap->name) < sizeof(atui_strap->name));
		}
		if (mem_clk_patch->num_data_blocks) {
			strcpy(atui_mem_timings->name, atui_strap->origname);
			atui_mem_timings->prefer_contiguous = true;
			atui_mem_timings->table_start = mem_clk_patch->data_blocks[0];
			atui_mem_timings->table_size = mem_clk_patch->data_block_table_size;
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

	atui_branch* atui_vram_modules = NULL;
	if (vi24->leaves->vram_module_num) {
		atui_vram_modules = grow_vram_module(
			vi24->vram_modules,
			vi24->vram_module_ver,
			vi24->leaves->vram_module_num
		);
	}

	atui_branch* const vi24_children[] = {
		atui_mem_adjust, atui_memclkpatch, atui_mc_tile_adjust,
		atui_dram_remap, atui_phyinit, atui_postucode_init,
		atui_vram_modules
	};
	return ATUI_MAKE_BRANCH(atom_vram_info_header_v2_4,  NULL,
		vi24,vi24->leaves,  lengthof(vi24_children), vi24_children
	);
}

inline static atui_branch*
grow_vram_info_v2_5(
		struct atomtree_vram_info const* const vram_info
		) {
	struct atomtree_vram_info_header_v2_5 const* const vi25 = &(vram_info->v2_5);

	atui_branch* atui_mem_adjust = NULL;
	if (vi25->mem_adjust_table.leaves) {
		atui_mem_adjust = grow_umc_init_reg_block(&(vi25->mem_adjust_table), 0);
		strcpy(atui_mem_adjust->name, "mem_adjust_table");
	}

	atui_branch* atui_gddr6_ac_timings = NULL;
	if (vi25->gddr6_ac_timings) {
		struct atom_gddr6_ac_timing_v2_5 const* const timings =
			vi25->gddr6_ac_timings;
		uint8_t const count = vi25->gddr6_acstrap_count;

		atui_gddr6_ac_timings = ATUI_MAKE_BRANCH(atui_nullstruct,
			"atom_gddr6_ac_timing_v2_5",
			NULL,NULL,  count,NULL
		);
		atui_gddr6_ac_timings->prefer_contiguous = true;
		atui_gddr6_ac_timings->table_start = (void*) timings;
		atui_gddr6_ac_timings->table_size = count * sizeof(timings[0]);

		atui_branch* atui_strap;
		char const* vendor_part[2];
		for (uint8_t i=0; i < count; i++) {
			atui_strap = ATUI_MAKE_BRANCH(atom_gddr6_ac_timing_v2_5,  NULL,
				NULL,&(timings[i]),  0,NULL
			);
			ATUI_ADD_BRANCH(atui_gddr6_ac_timings, atui_strap);

			union atom_mc_register_setting_id block_id = timings[i].block_id;
			get_memory_vendor_part_strs(
				&(vi25->vram_modules[block_id.mem_block_id]),
				vendor_part
			);
			sprintf(atui_strap->name, "Timings [%02u]: %s (%s): %u MHz",
				i,  vendor_part[1], vendor_part[0],
				(block_id.mem_clock_range / 100)
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

	atui_branch* const atui_dram_remap = grow_gddr6_dram_data_remap(
		&(vi25->dram_data_remap)
	);

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

	atui_branch* atui_vram_modules = NULL;
	if (vi25->leaves->vram_module_num) {
		atui_vram_modules = grow_vram_module(
			vi25->vram_modules,
			vi25->vram_module_ver,
			vi25->leaves->vram_module_num
		);
	}

	atui_branch* const vi25_children[] = {
		atui_mem_adjust, atui_gddr6_ac_timings, atui_mc_tile_adjust,
		atui_phyinit, atui_dram_remap, atui_postucode_init,
		atui_strobe_mode_patch, atui_vram_modules,
	};
	return ATUI_MAKE_BRANCH(atom_vram_info_header_v2_5,  NULL,
		vi25,vi25->leaves,  lengthof(vi25_children), vi25_children
	);
}

inline static atui_branch*
grow_vram_info_v2_6(
		struct atomtree_vram_info const* const vram_info
		) {
	struct atomtree_vram_info_header_v2_6 const* const vi26 = &(vram_info->v2_6);

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

	atui_branch* const atui_dram_remap = grow_gddr6_dram_data_remap(
		&(vi26->dram_data_remap)
	);

	atui_branch* atui_postucode_init = NULL;
	if (vi26->post_ucode_init.leaves) {
		atui_postucode_init = grow_umc_init_reg_block(
			&(vi26->post_ucode_init), 0
		);
		strcpy(atui_postucode_init->name, "post_ucode_init");
	}

	atui_branch* atui_vram_modules = NULL;
	if (vi26->leaves->vram_module_num) {
		atui_vram_modules = grow_vram_module(
			vi26->vram_modules,
			vi26->vram_module_ver,
			vi26->leaves->vram_module_num
		);
	}

	atui_branch* const vi26_children[] = {
		atui_mem_adjust, atui_mc_tile_adjust, atui_phyinit,
		atui_dram_remap, atui_tmrs_seq, atui_postucode_init,
		atui_vram_modules,
	};
	return ATUI_MAKE_BRANCH(atom_vram_info_header_v2_5,  NULL,
		vi26,vi26->leaves,  lengthof(vi26_children), vi26_children
	);
}

inline static atui_branch*
grow_vram_info_v3_0( // TODO finish this
		struct atomtree_vram_info const* const vram_info
		) {
	struct atomtree_vram_info_header_v3_0 const* const vi30 = &(vram_info->v3_0);

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

	atui_branch* const atui_dram_remap = grow_gddr6_dram_data_remap(
		&(vi30->dram_data_remap)
	);

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

	atui_branch* atui_vram_modules = NULL;
	if (vi30->leaves->vram_module_num) {
		atui_vram_modules = grow_vram_module(
			vi30->vram_modules,
			vi30->vram_module_ver,
			vi30->leaves->vram_module_num
		);
	}

	atui_branch* const vi30_children[] = {
		atui_mem_tuning, atui_dram_info, atui_tmrs_seq, atui_mc_init,
		atui_dram_remap, atui_umc_emuinit, atui_vram_modules,
	};
	return ATUI_MAKE_BRANCH(atom_vram_info_header_v3_0,  NULL,
		vi30,vi30->leaves,  lengthof(vi30_children), vi30_children
	);
}

inline static atui_branch*
grow_vram_info(
		struct atomtree_vram_info const* const vram_info,
		struct atom_tree const* const atree __unused
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
		enum  atom_voltage_type const type,
		uint16_t const absolute_index
		) {
	struct atui_enum const* const volt_types = & ATUI_ENUM(atom_voltage_type);
	int16_t const naming_enum_i = atui_enum_bsearch(volt_types, type);
	if (0 <= naming_enum_i) {
		sprintf(atui_volt_object->name, "%s [%u]: %s",
			atui_volt_object->origname,
			absolute_index,
			volt_types->enum_array[naming_enum_i].name
		);
	} else {
		sprintf(atui_volt_object->name, "%s [%u]: type %x",
			atui_volt_object->origname,
			absolute_index,
			type
		);
	}
	assert(strlen(atui_volt_object->name) < sizeof(atui_volt_object->name));
}

inline static atui_branch*
grow_voltageobject_info_v1_1(
		struct atomtree_voltageobject_info const* const vo_info
		) {
	struct atomtree_voltage_object const* const voltage_objects = (
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
			atui_volt_object,
			voltage_objects[i].obj->volt_obj_v1.VoltageType,
			i
		);
		ATUI_ADD_BRANCH(atui_vo_info, atui_volt_object);
	};
	return atui_vo_info;
}

inline static atui_branch*
grow_voltageobject_info_v1_2(
		struct atomtree_voltageobject_info const* const vo_info
		) {
	struct atomtree_voltage_object const* const voltage_objects = (
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
			atui_volt_object,
			voltage_objects[i].obj->volt_obj_v2.VoltageType,
			i
		);
		ATUI_ADD_BRANCH(atui_vo_info, atui_volt_object);
	};
	return atui_vo_info;
}

inline static atui_branch*
grow_voltageobject_info_v3_1(
		struct atomtree_voltageobject_info const* const vo_info
		) {
	struct atomtree_voltage_object const* const voltage_objects = (
		vo_info->voltage_objects
	);

	atui_branch* const atui_vo_info = ATUI_MAKE_BRANCH(atom_common_table_header,
		"atom_voltage_objects_info_v3_1",
		NULL,vo_info->leaves,  vo_info->num_voltage_objects,NULL
	);

	atui_branch* atui_volt_object;
	atuifunc_args atui_args = {0};
	atuifunc atui_vobj_func;
	for (uint16_t i=0; i < vo_info->num_voltage_objects; i++) {
		switch (voltage_objects[i].obj->header.voltage_mode) {
			case VOLTAGE_OBJ_GPIO_LUT:
			case VOLTAGE_OBJ_PHASE_LUT:
				atui_vobj_func = _atui_atom_gpio_voltage_object_v1;
				break;
			case VOLTAGE_OBJ_VR_I2C_INIT_SEQ:
				atui_vobj_func = _atui_atom_i2c_voltage_object_v1;
				break;
			case VOLTAGE_OBJ_SVID2:
				atui_vobj_func = _atui_atom_svid2_voltage_object_v1;
				break;
			case VOLTAGE_OBJ_MERGED_POWER:
				atui_vobj_func = _atui_atom_merged_voltage_object_v1;
				break;
			case VOLTAGE_OBJ_EVV:
				atui_vobj_func = _atui_atom_evv_voltage_object_v1;
				break;
			case VOLTAGE_OBJ_PWRBOOST_LEAKAGE_LUT:
			case VOLTAGE_OBJ_HIGH_STATE_LEAKAGE_LUT:
			case VOLTAGE_OBJ_HIGH1_STATE_LEAKAGE_LUT:
				atui_vobj_func = _atui_atom_leakage_voltage_object_v1;
				break;
			default:
				atui_vobj_func = _atui_atom_voltage_object_header;
				assert(0);
				break;
		}
		atui_args.atomtree = &(voltage_objects[i]);
		atui_args.suggestbios = voltage_objects[i].obj;
		atui_volt_object = atui_vobj_func(&atui_args);
		rename_volt_object_with_type(
			atui_volt_object,
			voltage_objects[i].obj->header.voltage_type,
			i
		);
		ATUI_ADD_BRANCH(atui_vo_info, atui_volt_object);
	}
	return atui_vo_info;
}


inline static atui_branch*
grow_voltageobject_info_v4_1(
		struct atomtree_voltageobject_info const* const vo_info
		) {
	struct atomtree_voltage_object const* const voltage_objects = (
		vo_info->voltage_objects
	);
	atui_branch* atui_vo_info = NULL;
	atui_vo_info = ATUI_MAKE_BRANCH(atom_common_table_header,
		"atom_voltage_objects_info_v4_1",
		NULL,vo_info->leaves,  vo_info->num_voltage_objects,NULL
	);

	atui_branch* atui_volt_object;
	atuifunc_args atui_args = {0};
	atuifunc atui_vobj_func;
	for (uint16_t i=0; i < vo_info->num_voltage_objects; i++) {
		switch (voltage_objects[i].obj->header.voltage_mode) {
			case VOLTAGE_OBJ_GPIO_LUT:
			case VOLTAGE_OBJ_PHASE_LUT:
				atui_vobj_func = _atui_atom_gpio_voltage_object_v1;
				break;
			case VOLTAGE_OBJ_VR_I2C_INIT_SEQ:
				atui_vobj_func = _atui_atom_i2c_voltage_object_v1;
				break;
			case VOLTAGE_OBJ_SVID2:
				atui_vobj_func = _atui_atom_svid2_voltage_object_v2;
				break;
			case VOLTAGE_OBJ_MERGED_POWER:
				atui_vobj_func = _atui_atom_merged_voltage_object_v1;
				break;
			case VOLTAGE_OBJ_EVV:
			case VOLTAGE_OBJ_PWRBOOST_LEAKAGE_LUT:
			case VOLTAGE_OBJ_HIGH_STATE_LEAKAGE_LUT:
			case VOLTAGE_OBJ_HIGH1_STATE_LEAKAGE_LUT:
				assert(0);
			default:
				atui_vobj_func = _atui_atom_voltage_object_header;
				assert(0);
				break;
		}
		atui_args.atomtree = &(voltage_objects[i]);
		atui_args.suggestbios = voltage_objects[i].obj;
		atui_volt_object = atui_vobj_func(&atui_args);
		rename_volt_object_with_type(
			atui_volt_object,
			voltage_objects[i].obj->header.voltage_type,
			i
		);
		ATUI_ADD_BRANCH(atui_vo_info, atui_volt_object);
	}
	return atui_vo_info;
}


inline static atui_branch*
grow_voltageobject_info(
		struct atomtree_voltageobject_info const* const vo_info,
		struct atom_tree const* const atree __unused
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
		struct atomtree_master_datatable const* const data_table,
		struct atom_tree const* const atree
		) {
	struct atomtree_master_datatable_v1_1 const* const dt11 = &(
		data_table->v1_1
	);

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
		struct atomtree_master_datatable_v2_1 const* const data_table,
		struct atom_tree const* const atree __unused
		) {
	atui_branch* sw_datatable3 = NULL;
	if (data_table->sw_datatable3.leaves) {
		sw_datatable3 = ATUI_MAKE_BRANCH(atom_common_table_header,
			"sw_datatable3",  NULL,data_table->sw_datatable3.leaves,  0,NULL
		);
	}

	atui_branch* sw_datatable5 = NULL;
	if (data_table->sw_datatable5.leaves) {
		sw_datatable5 = ATUI_MAKE_BRANCH(atom_common_table_header,
			"sw_datatable5",  NULL,data_table->sw_datatable5.leaves,  0,NULL
		);
	}

	atui_branch* sw_datatable7 = NULL;
	if (data_table->sw_datatable7.leaves) {
		sw_datatable7 = ATUI_MAKE_BRANCH(atom_common_table_header,
			"sw_datatable7",  NULL,data_table->sw_datatable7.leaves,  0,NULL
		);
	}

	atui_branch* sw_datatable9 = NULL;
	if (data_table->sw_datatable9.leaves) {
		sw_datatable9 = ATUI_MAKE_BRANCH(atom_common_table_header,
			"sw_datatable9",  NULL,data_table->sw_datatable9.leaves,  0,NULL
		);
	}

	atui_branch* sw_datatable10 = NULL;
	if (data_table->sw_datatable10.leaves) {
		sw_datatable10 = ATUI_MAKE_BRANCH(atom_common_table_header,
			"sw_datatable10",  NULL,data_table->sw_datatable10.leaves,  0,NULL
		);
	}

	atui_branch* sw_datatable13 = NULL;
	if (data_table->sw_datatable13.leaves) {
		sw_datatable13 = ATUI_MAKE_BRANCH(atom_common_table_header,
			"sw_datatable13",  NULL,data_table->sw_datatable13.leaves,  0,NULL
		);
	}

	atui_branch* sw_datatable16 = NULL;
	if (data_table->sw_datatable16.leaves) {
		sw_datatable16 = ATUI_MAKE_BRANCH(atom_common_table_header,
			"sw_datatable16",  NULL,data_table->sw_datatable16.leaves,  0,NULL
		);
	}

	atui_branch* sw_datatable17 = NULL;
	if (data_table->sw_datatable17.leaves) {
		sw_datatable17 = ATUI_MAKE_BRANCH(atom_common_table_header,
			"sw_datatable17",  NULL,data_table->sw_datatable17.leaves,  0,NULL
		);
	}

	atui_branch* sw_datatable18 = NULL;
	if (data_table->sw_datatable18.leaves) {
		sw_datatable18 = ATUI_MAKE_BRANCH(atom_common_table_header,
			"sw_datatable18",  NULL,data_table->sw_datatable18.leaves,  0,NULL
		);
	}

	atui_branch* sw_datatable19 = NULL;
	if (data_table->sw_datatable19.leaves) {
		sw_datatable19 = ATUI_MAKE_BRANCH(atom_common_table_header,
			"sw_datatable19",  NULL,data_table->sw_datatable19.leaves,  0,NULL
		);
	}

	atui_branch* sw_datatable20 = NULL;
	if (data_table->sw_datatable20.leaves) {
		sw_datatable20 = ATUI_MAKE_BRANCH(atom_common_table_header,
			"sw_datatable20",  NULL,data_table->sw_datatable20.leaves,  0,NULL
		);
	}

	atui_branch* sw_datatable21 = NULL;
	if (data_table->sw_datatable21.leaves) {
		sw_datatable21 = ATUI_MAKE_BRANCH(atom_common_table_header,
			"sw_datatable21",  NULL,data_table->sw_datatable21.leaves,  0,NULL
		);
	}

	atui_branch* sw_datatable25 = NULL;
	if (data_table->sw_datatable25.leaves) {
		sw_datatable25 = ATUI_MAKE_BRANCH(atom_common_table_header,
			"sw_datatable25",  NULL,data_table->sw_datatable25.leaves,  0,NULL
		);
	}

	atui_branch* sw_datatable26 = NULL;
	if (data_table->sw_datatable26.leaves) {
		sw_datatable26 = ATUI_MAKE_BRANCH(atom_common_table_header,
			"sw_datatable26",  NULL,data_table->sw_datatable26.leaves,  0,NULL
		);
	}

	atui_branch* sw_datatable29 = NULL;
	if (data_table->sw_datatable29.leaves) {
		sw_datatable29 = ATUI_MAKE_BRANCH(atom_common_table_header,
			"sw_datatable29",  NULL,data_table->sw_datatable29.leaves,  0,NULL
		);
	}

	atui_branch* sw_datatable33 = NULL;
	if (data_table->sw_datatable33.leaves) {
		sw_datatable33 = ATUI_MAKE_BRANCH(atom_common_table_header,
			"sw_datatable33",  NULL,data_table->sw_datatable33.leaves,  0,NULL
		);
	}

	atui_branch* sw_datatable34 = NULL;
	if (data_table->sw_datatable34.leaves) {
		sw_datatable34 = ATUI_MAKE_BRANCH(atom_common_table_header,
			"sw_datatable34",  NULL,data_table->sw_datatable34.leaves,  0,NULL
		);
	}


	atui_branch* const atui_sw_datatables[] = {
		sw_datatable3,  sw_datatable5,  sw_datatable7,  sw_datatable9,
		sw_datatable10, sw_datatable13, sw_datatable16, sw_datatable17,
		sw_datatable18, sw_datatable19, sw_datatable20, sw_datatable21,
		sw_datatable25, sw_datatable26, sw_datatable29, sw_datatable33,
		sw_datatable34,
	};
	return ATUI_MAKE_BRANCH(atui_nullstruct,  "sw_datatables",
		NULL,NULL,  lengthof(atui_sw_datatables), atui_sw_datatables
	);
}
inline static atui_branch*
grow_master_datatable_v2_1(
		struct atomtree_master_datatable const* const data_table,
		struct atom_tree const* const atree 
		) {
	struct atomtree_master_datatable_v2_1 const* const dt21 = &(data_table->v2_1);

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

	atui_branch* const atui_sw_datatables =
		atomtree_datatable_v2_1_populate_sw_datatables(dt21, atree);

	atui_branch* const child_branches[] = {
		// utility, multimedia
		atui_smc_dpm_info, atui_firmwareinfo, atui_lcd_info, atui_smu_info,
		atui_fw_vram, atui_gpio_pin_lut, atui_gfx_info, atui_ppt,
		// disp obj, indirect, umc, dce,
		atui_vram_info,
		// integrated, asic
		atui_voltageobject_info,
		atui_sw_datatables,
	};
	return ATUI_MAKE_BRANCH(atom_master_data_table_v2_1,  NULL,
		dt21,dt21->leaves,  lengthof(child_branches), child_branches
	);
}

inline static atui_branch*
grow_datatables(
		//struct atomtree_master_datatable const* const data_table,
		struct atom_tree const* const atree
		) {
	struct atomtree_master_datatable const* const data_table = &(
		atree->data_table
	);
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
		struct atomtree_rom_header const* const rom_header,
		struct atom_tree const* const atree
		) {
	if (NULL == rom_header->leaves) {
		return NULL;
	}
	atui_branch* const atui_dt = grow_datatables(atree);
	atui_branch* atui_rom_header;
	atuifunc atui_func;
	atuifunc_args atui_args = {
		.atomtree = rom_header,
		.suggestbios = rom_header->leaves,
		.import_branches = &atui_dt,
		.num_import_branches = 1,
	};
	switch (rom_header->ver) {
		case v1_1: atui_func = _atui_atom_rom_header_v1_1; break;
		case v2_1: atui_func = _atui_atom_rom_header_v2_1; break;
		case v2_3: atui_args.rename = "atom_rom_header_v2_2 (forced)"; fall;
		case v2_2: atui_func = _atui_atom_rom_header_v2_2; break;
		default:
			atui_args.rename = "atom_rom_header (header only stub)";
			atui_func = _atui_atom_common_table_header;
			break;
	}
	return atui_func(&atui_args);
}

inline static atui_branch*
grow_pci_tables(
		struct atomtree_pci_tables const* const atree_pci
		) {
	struct pci_rom_tables const* const tables = atree_pci->pci_tables;

	atui_branch* const atui_pci_tables = ATUI_MAKE_BRANCH(atui_nullstruct,
		"PCI Tables",
		NULL,NULL,  atree_pci->num_images, NULL
	);

	atui_branch* atui_pci;
	atuifunc_args atui_args = {0};
	atuifunc const atui_pci_func[] = { // jump table
		_atui_pci_rom_tables,
		_atui_efi_pci_device_driver_image,
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

atui_branch*
generate_atui(
		struct atom_tree const* const atree
		) {
	atui_branch* const atui_atom_rom_header = grow_atom_rom_header(
		&(atree->rom_header), atree
	);
	atui_branch* const atui_pci_tables = grow_pci_tables(&(atree->pci_tables));

	atui_branch* const child_branches[] = {
		atui_pci_tables, atui_atom_rom_header
	};
	return ATUI_MAKE_BRANCH(vbios_rom_header, NULL,
		atree, atree->image,  lengthof(child_branches), child_branches
	);
}
