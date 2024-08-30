/* For atomtree's abstract, check out atomtree_data_tables.h */

#include "standard.h"
#include "atomtree.h"

// commented out; see message in standard.h
//landing is in atombios_parse
//static struct error error = {}; // error handling
//error_assert(&error, ERROR_WARNING, "hello!", NULL == atree);

inline static void
populate_smc_dpm_info(
		struct atomtree_smc_dpm_info* const smc_dpm_info,
		struct atom_tree* const atree,
		uint16_t const bios_offset
		) {
	if (bios_offset) {
		// leaves is in a union with the structs.
		smc_dpm_info->leaves = atree->bios + bios_offset;
		smc_dpm_info->ver = get_ver(smc_dpm_info->table_header);
	}
}


inline static void
populate_firmwareinfo(
		struct atomtree_firmware_info* const firmwareinfo,
		struct atom_tree* const atree,
		uint16_t const bios_offset
		) {
	if (bios_offset) {
		// leaves is in a union with the structs.
		firmwareinfo->leaves = atree->bios + bios_offset;
		firmwareinfo->ver = get_ver(firmwareinfo->table_header);
	}
}


inline static void
populate_lcd_info(
		struct atomtree_lcd_info* const lcd_info,
		struct atom_tree* const atree,
		uint16_t const bios_offset
		) {
	if (bios_offset) {
		lcd_info->leaves = atree->bios + bios_offset;
		lcd_info->ver = get_ver(lcd_info->table_header);
	}
}


inline static void
populate_smu_info(
		struct atomtree_smu_info* const smu_info,
		struct atom_tree* const atree,
		uint16_t const bios_offset
		) {
	// leaves is in a union with the structs.
	if (bios_offset) {
		smu_info->leaves = atree->bios + bios_offset;
		smu_info->ver = get_ver(smu_info->table_header);
		switch (smu_info->ver) { // TODO if init,golden are 0, catch them.
			case v3_2:
				if (smu_info->v3_2->smugoldenoffset) {
					smu_info->smugolden =
						smu_info->leaves + smu_info->v3_2->smugoldenoffset;
				}
				break;
			case v3_3:
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
				if (smu_info->v4_0->smuinitoffset) {
					smu_info->smuinit =
						smu_info->leaves + smu_info->v4_0->smuinitoffset;
				}
				break;
			default:
				break;
		}
	}
}


inline static void
populate_vram_usagebyfirmware(
		struct atomtree_vram_usagebyfirmware* const fw_vram,
		struct atom_tree* const atree,
		uint16_t const bios_offset) {
	if (bios_offset) {
		// leaves is in a union with the structs.
		fw_vram->leaves = atree->bios + bios_offset;
		fw_vram->ver = get_ver(fw_vram->table_header);
	}
}


inline static void
populate_gpio_pin_lut(
		struct atomtree_gpio_pin_lut* const gpio_pin_lut,
		struct atom_tree* const atree,
		uint16_t const bios_offset
		) {
	if (bios_offset) {
		gpio_pin_lut->leaves = atree->bios + bios_offset;
		gpio_pin_lut->ver = get_ver(gpio_pin_lut->table_header);
		switch (gpio_pin_lut->ver) {
			case v2_1:
				gpio_pin_lut->num_gpio_pins = (
					//dynamic array length of nothing but pins after the header
					(gpio_pin_lut->table_header->structuresize
						- sizeof(struct atom_common_table_header)
					) / sizeof(struct atom_gpio_pin_assignment_v2_1)
				);
				break;
			default:
				break;
		}
	}
}


inline static void
populate_gfx_info(
		struct atomtree_gfx_info* const gfx_info,
		struct atom_tree* const atree,
		uint16_t const bios_offset
		) {
	if (bios_offset) {
		// leaves is in a union with the structs.
		gfx_info->leaves = atree->bios + bios_offset;
		gfx_info->ver = get_ver(gfx_info->table_header);
		switch (gfx_info->ver) {
			case v2_1:
				break;
			case v2_3:
				if (gfx_info->table_header->structuresize
						== sizeof(struct atom_gfx_info_v2_3)
						) {
					if (gfx_info->v2_3->EdcDidtLoDpm7TableOffset) {
						gfx_info->edc_didt_lo = (
							gfx_info->leaves
							+ gfx_info->v2_3->EdcDidtLoDpm7TableOffset
						);
					}
					if (gfx_info->v2_3->EdcDidtHiDpm7TableOffset) {
						gfx_info->edc_didt_hi = (
							gfx_info->leaves
							+ gfx_info->v2_3->EdcDidtHiDpm7TableOffset
						);
					}
				} else if (gfx_info->table_header->structuresize
						== sizeof(struct atom_gfx_info_v2_3_2)) {
					assert(0); // unsure what uses this
					if (gfx_info->v2_3_2->gcgoldenoffset) {
						gfx_info->gcgolden =
							gfx_info->leaves + gfx_info->v2_3_2->gcgoldenoffset;
					}
				}
				break;
			case v2_4:
				if (gfx_info->v2_4->gcgoldenoffset) {
					gfx_info->gcgolden =
						gfx_info->leaves + gfx_info->v2_4->gcgoldenoffset;
				}
				break;
			case v2_5:
				if (gfx_info->v2_5->gcgoldenoffset) {
					gfx_info->gcgolden =
						gfx_info->leaves + gfx_info->v2_5->gcgoldenoffset;
				}
				break;
			case v2_6: // force v2.5
				if (gfx_info->v2_6->gcgoldenoffset) {
					gfx_info->gcgolden =
						gfx_info->leaves + gfx_info->v2_6->gcgoldenoffset;
				}
				break;
			case v2_7:
				if (gfx_info->v2_7->gcgoldenoffset) {
					gfx_info->gcgolden =
						gfx_info->leaves + gfx_info->v2_7->gcgoldenoffset;
				}
				break;
			default:
				break;
		}
	}
}


inline static void
populate_pplib_ppt_state_array(
		struct atomtree_powerplay_table_v4_1* const ppt41
		) {
	struct atom_pplib_powerplaytable_v1 const* const pplibv1 = &(
		ppt41->leaves->v1
	);
	union atom_pplib_state_arrays* const base = ppt41->state_array_base;
	union {
		void* raw;
		struct atom_pplib_state_v1* v1;
		struct atom_pplib_state_v2* v2;
		union atom_pplib_states*    states;
	} walker;

	if (v6_0 > get_ver(&(pplibv1->header))) { // driver gates with the atom ver
		assert(pplibv1->NumStates < ATOMTREE_PPLIB_STATE_ARRAY_MAX);
		ppt41->state_array_ver = v1_0;
		ppt41->num_state_array_entries = pplibv1->NumStates;

		uint8_t const entry_size = pplibv1->StateEntrySize;
		uint8_t const num_levels = (
			(entry_size - sizeof(base->v1))
			/ sizeof(base->v1.ClockStateIndices[0])
		);
		walker.raw = &(base->v1);
		for (uint8_t i=0; i < pplibv1->NumStates; i++) {
			ppt41->state_array[i].num_levels = num_levels;
			ppt41->state_array[i].state = walker.states;
			ppt41->state_array[i].size = entry_size;
			walker.raw += entry_size;
		}
		ppt41->state_array_size = pplibv1->NumStates * pplibv1->StateEntrySize;
	} else {
		assert(base->v2.NumEntries < ATOMTREE_PPLIB_STATE_ARRAY_MAX);
		ppt41->state_array_ver = v2_0;
		ppt41->num_state_array_entries = base->v2.NumEntries;

		uint16_t entry_size;
		walker.v2 = base->v2.states;
		for (uint8_t i=0; i < base->v2.NumEntries; i++) {
			ppt41->state_array[i].num_levels = walker.v2->NumDPMLevels;
			ppt41->state_array[i].state = walker.states;
			entry_size = sizeof_flex(
				walker.v2, clockInfoIndex, walker.v2->NumDPMLevels
			);
			ppt41->state_array[i].size = entry_size;
			walker.raw += entry_size;
		}
		ppt41->state_array_size = walker.raw - (void*)base;
	}
}

inline static void
populate_pplib_ppt_extended_table(
		struct atomtree_powerplay_table_v4_1* const ppt41
		) {
	void* const raw = ppt41->leaves;
	union atom_pplib_extended_headers* const ext = ppt41->extended_header;

	switch (ext->Size) {
		case sizeof(ext->v9): ppt41->extended_header_ver = v9_0; break;
		case sizeof(ext->v8): ppt41->extended_header_ver = v8_0; break;
		case sizeof(ext->v7): ppt41->extended_header_ver = v7_0; break;
		case sizeof(ext->v6): ppt41->extended_header_ver = v6_0; break;
		case sizeof(ext->v5): ppt41->extended_header_ver = v5_0; break;
		case sizeof(ext->v4): ppt41->extended_header_ver = v4_0; break;
		case sizeof(ext->v3): ppt41->extended_header_ver = v3_0; break;
		case sizeof(ext->v2): ppt41->extended_header_ver = v2_0; break;
		case sizeof(ext->v1): ppt41->extended_header_ver = v1_0; break;
		default: assert(0); break;
	}
	switch (ppt41->extended_header_ver) {
		case v9_0:
			if (ext->v9.VQBudgetingTableOffset) {
				ppt41->vq_budgeting = raw + ext->v9.VQBudgetingTableOffset;
			}
			fall;
		case v8_0:
			if (ext->v9.SclkVddgfxTableOffset) {
				ppt41->vddgfx_sclk = raw + ext->v9.SclkVddgfxTableOffset;
			}
			fall;
		case v7_0:
			if (ext->v9.PowerTuneTableOffset) {
				ppt41->powertune = raw + ext->v9.PowerTuneTableOffset;
			}
			fall;
		case v6_0:
			if (ext->v9.ACPTableOffset) {
				ppt41->acpclk = raw + ext->v9.ACPTableOffset;
			}
			fall;
		case v5_0:
			if (ext->v9.PPMTableOffset) {
				ppt41->ppm = raw + ext->v9.PPMTableOffset;
			}
			fall;
		case v4_0:
			if (ext->v9.SAMUTableOffset) {
				ppt41->samu = raw + ext->v9.SAMUTableOffset;
			}
			fall;
		case v3_0:
			if (ext->v9.UVDTableOffset) { // 2 flex subtables in the table
				void* walker = raw + ext->v9.UVDTableOffset;
				ppt41->uvd_root = walker;
				walker += sizeof(*(ppt41->uvd_root));
				ppt41->uvd_info = walker;
				walker += sizeof_flex(
					ppt41->uvd_info, entries, ppt41->uvd_info->NumEntries
				);
				ppt41->uvd_limits = walker;
				walker += sizeof_flex(
					ppt41->uvd_limits, entries, ppt41->uvd_limits->NumEntries
				);
				ppt41->uvd_table_size = walker - (void*)(ppt41->uvd_root);
			};
			fall;
		case v2_0:
			if (ext->v9.VCETableOffset) { // 3 flex subtables in the table
				void* walker = raw + ext->v9.VCETableOffset;
				ppt41->vce_root = walker;
				walker += sizeof(*(ppt41->vce_root));
				ppt41->vce_info = walker;
				walker += sizeof_flex(
					ppt41->vce_info, entries, ppt41->vce_info->NumEntries
				);
				ppt41->vce_limits = walker;
				walker += sizeof_flex(
					ppt41->vce_limits, entries, ppt41->vce_limits->NumEntries
				);
				ppt41->vce_states = walker;
				walker += sizeof_flex(
					ppt41->vce_states, entries, ppt41->vce_states->NumEntries
				);
				ppt41->vce_table_size = walker - (void*)(ppt41->vce_root);
			};
			fall;
		case v1_0: break;
		default: assert(0); break;
	}
};

inline static uint8_t
get_early_clock_info_length(
		struct atomtree_powerplay_table_v4_1 const* const ppt41
		) {
	/*
	There is no straightforward, authoritative way to count old clock_info array
	length, like what would be experienced with newer pplib flexible arrays. As
	a result, we have to infer it from something else. The driver uses the
	values in  struct atom_pplib_state_v1.ClockStateIndices  to index into
	clock_info.
	A possible optimisation is to get the value from [-1][-1] as they seem to
	count up contiguously.
	*/
	assert(v1_0 == ppt41->state_array_ver);
	uint8_t n = 0;
	for (uint8_t i = 0; i < ppt41->num_state_array_entries; i++) {
		struct atomtree_pplib_state const* state = &(ppt41->state_array[i]);
		for (uint8_t j = 0; j < state->num_levels; j++) {
			uint8_t clock_info_index = state->state->v1.ClockStateIndices[j];
			if (n < clock_info_index) {
				n = clock_info_index;
			}
		}
	}
	bool const has_state_array = (
		(0 < ppt41->num_state_array_entries)
		&& (0 < ppt41->state_array[0].num_levels)
	);
	return n + has_state_array;
};
inline static void
set_pplib_ppt_clock_info(
		struct atomtree_powerplay_table_v4_1* const ppt41,
		enum amd_asic_type const chip_type
		) {
	union atom_pplib_clock_info_arrays const* const ci = ppt41->clock_info;

	// radeon driver's codepaths for r600, r7xxx, evergeeen is a tangled mess
	switch (chip_type) {
		case CHIP_R600:
		case CHIP_RV610:
		case CHIP_RV630:
		case CHIP_RV620:
		case CHIP_RV635:
		case CHIP_RV670:
		case CHIP_RV770:
		case CHIP_RV730:
		case CHIP_RV710:
		case CHIP_RV740:
			ppt41->clock_info_ver = ATOM_PPLIB_CLOCK_INFO_R600;
			break;
		case CHIP_RS780:
		case CHIP_RS880:
			ppt41->clock_info_ver = ATOM_PPLIB_CLOCK_INFO_RS780;
			break;
		case CHIP_CEDAR:
		case CHIP_REDWOOD:
		case CHIP_JUNIPER:
		case CHIP_CYPRESS:
		case CHIP_HEMLOCK:
		case CHIP_BARTS:
		case CHIP_TURKS:
		case CHIP_CAICOS:
		case CHIP_CAYMAN:
			ppt41->clock_info_ver = ATOM_PPLIB_CLOCK_INFO_GREEN;
			break;
		case CHIP_TAHITI:
		case CHIP_PITCAIRN:
		case CHIP_VERDE:
		case CHIP_OLAND:
		case CHIP_HAINAN:
			ppt41->clock_info_ver = ATOM_PPLIB_CLOCK_INFO_SOUTH;
			break;
		case CHIP_BONAIRE:
		case CHIP_HAWAII:
			ppt41->clock_info_ver = ATOM_PPLIB_CLOCK_INFO_SEA;
			break;
		case CHIP_PALM:
		case CHIP_SUMO:
		case CHIP_SUMO2:
		case CHIP_ARUBA:
		case CHIP_KAVERI:
		case CHIP_KABINI:
		case CHIP_MULLINS:
			ppt41->clock_info_ver = ATOM_PPLIB_CLOCK_INFO_SUMO;
			break;
		case CHIP_TOPAZ:
		case CHIP_CARRIZO:
		case CHIP_STONEY:
			ppt41->clock_info_ver = ATOM_PPLIB_CLOCK_INFO_CARRIZO;
			break;
		default:
			ppt41->clock_info_ver = ATOM_PPLIB_CLOCK_INFO_UNKNOWN;
			assert(0);
			break;
	}

	switch (ppt41->clock_info_ver) {
		case ATOM_PPLIB_CLOCK_INFO_R600:
		case ATOM_PPLIB_CLOCK_INFO_RS780:
		case ATOM_PPLIB_CLOCK_INFO_GREEN:
			ppt41->num_clock_info_entries = get_early_clock_info_length(ppt41);
			ppt41->clock_info_size = (
				ppt41->num_clock_info_entries * ppt41->leaves->v1.ClockInfoSize
			);
			break;
		case ATOM_PPLIB_CLOCK_INFO_SOUTH:
		case ATOM_PPLIB_CLOCK_INFO_SEA:
		case ATOM_PPLIB_CLOCK_INFO_SUMO:
		case ATOM_PPLIB_CLOCK_INFO_CARRIZO:
			// Southern Islands and newer have the count built in.
			ppt41->num_clock_info_entries = ci->header.NumEntries;
			ppt41->clock_info_size = (
				sizeof(ci->header)
				+ (ci->header.NumEntries * ci->header.EntrySize)
			);
			break;
		default: break;
	}
}
inline static void
populate_pplib_ppt(
		struct atomtree_powerplay_table_v4_1* const ppt41,
		enum amd_asic_type const chip_type
		) {
	union {
		void* raw;
		union atom_pplib_powerplaytables* all;
		struct atom_pplib_powerplaytable_v5* v5;
	} b;
	b.raw = ppt41->leaves;
	switch (b.v5->TableSize) {
		case sizeof(b.all->v5): ppt41->pplib_ver = v5_0; break;
		case sizeof(b.all->v4): ppt41->pplib_ver = v4_0; break;
		case sizeof(b.all->v3): ppt41->pplib_ver = v3_0; break;
		case sizeof(b.all->v2): ppt41->pplib_ver = v2_0; break;
		case 0: // R600
		case sizeof(b.all->v1): ppt41->pplib_ver = v1_0; break;
		default: assert(0);
	};
	switch (ppt41->pplib_ver) {
		case v5_0:
			if (b.v5->CACLeakageTableOffset) {
				ppt41->cac_leakage = b.raw + b.v5->CACLeakageTableOffset;
			}
			fall;
		case v4_0:
			if (b.v5->VddcDependencyOnSCLKOffset) {
				ppt41->vddc_sclk = b.raw + b.v5->VddcDependencyOnSCLKOffset;
			}
			if (b.v5->VddciDependencyOnMCLKOffset) {
				ppt41->vddci_mclk = b.raw + b.v5->VddciDependencyOnMCLKOffset;
			}
			if (b.v5->VddcDependencyOnMCLKOffset) {
				ppt41->vddc_mclk = b.raw + b.v5->VddcDependencyOnMCLKOffset;
			}
			if (b.v5->MaxClockVoltageOnDCOffset) {
				ppt41->max_on_dc = b.raw + b.v5->MaxClockVoltageOnDCOffset;
			}
			if (b.v5->VddcPhaseShedLimitsTableOffset) {
				ppt41->phase_shed = (
					b.raw + b.v5->VddcPhaseShedLimitsTableOffset
				);
			}
			if (b.v5->MvddDependencyOnMCLKOffset) {
				ppt41->mvdd_mclk = b.raw + b.v5->MvddDependencyOnMCLKOffset;
			}
			fall;
		case v3_0:
			if (b.v5->FanTableOffset) {
				ppt41->fan_table = b.raw + b.v5->FanTableOffset;
			}
			if (b.v5->ExtendedHeaderOffset) {
				ppt41->extended_header = b.raw + b.v5->ExtendedHeaderOffset;
				populate_pplib_ppt_extended_table(ppt41);
			}
			fall;
		case v2_0:
			if (b.v5->CustomThermalPolicyArrayOffset) {
				ppt41->thermal_policy = (
					b.raw + b.v5->CustomThermalPolicyArrayOffset
				);
			}
			fall;
		case v1_0:
			if (b.v5->StateArrayOffset) {
				ppt41->state_array_base = b.raw + b.v5->StateArrayOffset;
				populate_pplib_ppt_state_array(ppt41);
			}
			if (b.v5->ClockInfoArrayOffset) {
				ppt41->clock_info = b.raw + b.v5->ClockInfoArrayOffset;
				set_pplib_ppt_clock_info(ppt41, chip_type);
			}
			if (b.v5->NonClockInfoArrayOffset) {
				ppt41->nonclock_info = b.raw + b.v5->NonClockInfoArrayOffset;
				
				switch (ppt41->nonclock_info->header.EntrySize) {
					case sizeof(ppt41->nonclock_info->v1.nonClockInfo[0]):
						 ppt41->nonclock_info_ver = v1_0;
						 break;
					case sizeof(ppt41->nonclock_info->v2.nonClockInfo[0]):
						 ppt41->nonclock_info_ver = v2_0;
						 break;
					case 0: break;
					default: assert(0); break;
				}
			}
			if (b.v5->BootClockInfoOffset) {
				ppt41->boot_clock_info = b.raw + b.v5->BootClockInfoOffset;
			}
			if (b.v5->BootNonClockInfoOffset) {
				ppt41->boot_nonclock_info = (
					b.raw + b.v5->BootNonClockInfoOffset
				);
			}
			break;
		default: assert(0);
	}
}

inline static void
populate_pptablev1_ppt(
		struct atomtree_powerplay_table_v7_1* const ppt71
		) {
	union {
		void* raw;
		struct atom_pptable_powerplaytable_v1* ppt;
	} b;
	b.raw = ppt71->leaves;
	if (b.ppt->StateArrayOffset) {
		ppt71->state_array = b.raw + b.ppt->StateArrayOffset;
	}
	if (b.ppt->FanTableOffset) {
		ppt71->fan_table = b.raw + b.ppt->FanTableOffset;
	}
	if (b.ppt->ThermalControllerOffset) {
		ppt71->thermal_controller = b.raw + b.ppt->ThermalControllerOffset;
	}
	if (b.ppt->MclkDependencyTableOffset) {
		ppt71->mclk_dependency = b.raw + b.ppt->MclkDependencyTableOffset;
	}
	if (b.ppt->SclkDependencyTableOffset) {
		ppt71->sclk_dependency = b.raw + b.ppt->SclkDependencyTableOffset;
	}
	if (b.ppt->VddcLookupTableOffset) {
		ppt71->vddc_lut = b.raw + b.ppt->VddcLookupTableOffset;
	}
	if (b.ppt->VddgfxLookupTableOffset) {
		ppt71->vddgfx_lut = b.raw + b.ppt->VddgfxLookupTableOffset;
	}
	if (b.ppt->MMDependencyTableOffset) {
		ppt71->mm_dependency = b.raw + b.ppt->MMDependencyTableOffset;
	}
	if (b.ppt->VCEStateTableOffset) {
		ppt71->vce_state = b.raw + b.ppt->VCEStateTableOffset;
	}
	if (b.ppt->PowerTuneTableOffset) {
		ppt71->powertune = b.raw + b.ppt->PowerTuneTableOffset;
	}
	if (b.ppt->HardLimitTableOffset) {
		ppt71->hard_limit = b.raw + b.ppt->HardLimitTableOffset;
	}
	if (b.ppt->PCIETableOffset) {
		ppt71->pcie_table = b.raw + b.ppt->PCIETableOffset;
	}
	if (b.ppt->GPIOTableOffset) {
		ppt71->gpio_table = b.raw + b.ppt->GPIOTableOffset;
	}
}

inline static void
populate_vega10_ppt(
		struct atomtree_powerplay_table_v8_1* const ppt81
		) {
	union {
		void* raw;
		struct atom_vega10_powerplaytable* ppt;
	} b;
	b.raw = ppt81->leaves;
	if (b.ppt->StateArrayOffset) {
		ppt81->state_array = b.raw + b.ppt->StateArrayOffset;
	}
	if (b.ppt->FanTableOffset) {
		ppt81->fan_table = b.raw + b.ppt->FanTableOffset;
	}
	if (b.ppt->ThermalControllerOffset) {
		ppt81->thermal_controller = b.raw + b.ppt->ThermalControllerOffset;
	}
	if (b.ppt->SocclkDependencyTableOffset) {
		ppt81->socclk_dependency = b.raw + b.ppt->SocclkDependencyTableOffset;
	}
	if (b.ppt->MclkDependencyTableOffset) {
		ppt81->mclk_dependency = b.raw + b.ppt->MclkDependencyTableOffset;
	}
	if (b.ppt->GfxclkDependencyTableOffset) {
		ppt81->gfxclk_dependency = b.raw + b.ppt->GfxclkDependencyTableOffset;
	}
	if (b.ppt->DcefclkDependencyTableOffset) {
		ppt81->dcefclk_dependency = b.raw + b.ppt->DcefclkDependencyTableOffset;
	}
	if (b.ppt->VddcLookupTableOffset) {
		ppt81->vddc_lut = b.raw + b.ppt->VddcLookupTableOffset;
	}
	if (b.ppt->VddmemLookupTableOffset) {
		ppt81->vdd_mem_lut = b.raw + b.ppt->VddmemLookupTableOffset;
	}
	if (b.ppt->MMDependencyTableOffset) {
		ppt81->mm_dependency = b.raw + b.ppt->MMDependencyTableOffset;
	}
	if (b.ppt->VCEStateTableOffset) {
		ppt81->vce_state = b.raw + b.ppt->VCEStateTableOffset;
	}
	if (b.ppt->PowerTuneTableOffset) {
		ppt81->powertune = b.raw + b.ppt->PowerTuneTableOffset;
	}
	if (b.ppt->HardLimitTableOffset) {
		ppt81->hard_limit = b.raw + b.ppt->HardLimitTableOffset;
	}
	if (b.ppt->VddciLookupTableOffset) {
		ppt81->vddci_lut = b.raw + b.ppt->VddciLookupTableOffset;
	}
	if (b.ppt->PCIETableOffset) {
		ppt81->pcie_table = b.raw + b.ppt->PCIETableOffset;
	}
	if (b.ppt->PixclkDependencyTableOffset) {
		ppt81->pixclk_dependency = b.raw + b.ppt->PixclkDependencyTableOffset;
	}
	if (b.ppt->DispClkDependencyTableOffset) {
		ppt81->dispclk_dependency = b.raw + b.ppt->DispClkDependencyTableOffset;
	}
	if (b.ppt->PhyClkDependencyTableOffset) {
		ppt81->phyclk_dependency = b.raw + b.ppt->PhyClkDependencyTableOffset;
	}
}
inline static enum atomtree_common_version
get_smc_pptable_ver(
		uint32_t const pp_ver
		) {
	assert(pp_ver < (UINT16_MAX/VER_MAJOR_MULTIPLIER));
	return pp_ver * VER_MAJOR_MULTIPLIER;
}
inline static void
populate_ppt(
		struct atomtree_powerplay_table* const ppt,
		struct atom_tree* const atree,
		uint16_t const bios_offset
		) {
	if (bios_offset) {
		ppt->leaves = atree->bios + bios_offset;
		// leaves is in a union with the structs.
		ppt->ver = get_ver(ppt->table_header);

		switch (ppt->ver) {
			case v1_1:
			case v2_1:
			case v3_1:
				break; // absurdly simple powerplay.
			case v6_1:
			case v5_1:
			case v4_1:
				populate_pplib_ppt(&(ppt->v4_1), atree->chip_type);
				break;
			case v7_1: // Tonga, Fiji, Polaris ; pptable and vega10 look similar
				populate_pptablev1_ppt(&(ppt->v7_1));
				break;
			case v8_1:
				populate_vega10_ppt(&(ppt->v8_1));
				break;
			case v11_0:
				ppt->v11_0.smc_pptable_ver = get_smc_pptable_ver(
					ppt->v11_0.leaves->smc_pptable.ver
				);
				break;
			case v14_0:
			case v12_0:
				ppt->v12_0.smc_pptable_ver = get_smc_pptable_ver(
					ppt->v12_0.leaves->smc_pptable.ver
				);
				break;
			case v19_0: // 6400
			case v18_0: // navi2 xx50
			case v16_0: // 6700XT
			case v15_0:
				ppt->v15_0.smc_pptable_ver = get_smc_pptable_ver(
					ppt->v15_0.leaves->smc_pptable.ver
				);
				break;
			default:
				assert(0);
				break;
		}
	}
}

static void
populate_init_reg_block(
		struct atomtree_init_reg_block* const at_regblock
		) {
	// MC inititialisation registers, for vram_info 2.2 and older
	// regblock->leaves must be already populated.
	/*
	This works in a somewhat similar way to umc_init.
	RegIndexTblSize determines RegIndexBuf's total size.
	RegDataBuf starts after RegIndexBuf.
	RegDataBlkSize is like a sizeof(struct) for RegDataBuf; meaning that
	struct atom_reg_setting_data_block's reg_data length is implied through
	RegDataBlkSize.
	*/

	struct atom_init_reg_block* const leaves = at_regblock->leaves;

	at_regblock->num_index = // will include END_OF_REG_INDEX_BLOCK flag
		leaves->RegIndexTblSize / sizeof(struct atom_init_reg_index_format);
	at_regblock->register_index = leaves->RegIndexBuf;

	at_regblock->data_block_element_size = leaves->RegDataBlkSize;
	at_regblock->num_data_entries = (
		(at_regblock->data_block_element_size
			- sizeof(((struct atom_reg_setting_data_block*)0)->block_id)
		) / sizeof(((struct atom_reg_setting_data_block*)0)->reg_data[0])
	);
	struct atom_reg_setting_data_block* block = (  // starting point
		(void*)leaves->RegIndexBuf + leaves->RegIndexTblSize
	);
	uint8_t i = 0;
	while (block->block_id.id_access) { // the datablock list ends with 0
		assert(ATOMTREE_MC_REG_MAX > i);
		at_regblock->data_blocks[i] = block;
		i++;
		block = (void*)block + at_regblock->data_block_element_size;
	}
	at_regblock->num_data_blocks = i;

	at_regblock->index_table_size = leaves->RegIndexTblSize;
	at_regblock->data_block_table_size = (
	 	at_regblock->data_block_element_size * at_regblock->num_data_blocks
	);
	at_regblock->total_size = (
		offsetof(struct atom_init_reg_block, RegIndexBuf) // 4 bytes
		+ at_regblock->index_table_size
		+ at_regblock->data_block_table_size
	);
}
static enum atom_dgpu_vram_type
get_vram_type(
		struct atomtree_vram_module const* const vram_module
		) {
	switch (vram_module->vram_module_ver) {
		case v1_1:  return vram_module->v1_1->MemoryType;
		case v1_2:  return vram_module->v1_2->MemoryType;
		case v1_3:  return vram_module->v1_3->MemoryType;
		case v1_4:  return vram_module->v1_4->MemoryType;
		case v1_5:  return vram_module->v1_5->MemoryType;
		case v1_6:  return vram_module->v1_6->MemoryType;
		case v1_7:  return vram_module->v1_7->MemoryType;
		case v1_8:  return vram_module->v1_8->MemoryType;
		case v1_9:  return vram_module->v1_9->memory_type;
		case v1_10: return vram_module->v1_10->memory_type;
		case v1_11: return vram_module->v1_11->memory_type;
		case v3_0:
		default: assert(0);
	}
	return ATOM_DGPU_VRAM_TYPE_NONE;
}

static void
populate_mem_adjust_table(
		struct atomtree_init_reg_block* const mem_adjust_table,
		struct atomtree_vram_module const* const vram_modules
		) {
	populate_init_reg_block(mem_adjust_table);
	mem_adjust_table->reg_type = REG_BLOCK_MEM_ADJUST;

	enum atom_dgpu_vram_type const vram_type = get_vram_type(&vram_modules[0]);
	enum atomtree_common_version const vram_module_ver =
		vram_modules[0].vram_module_ver;
	struct atom_init_reg_index_format const* const index =
		mem_adjust_table->register_index;
	struct atom_reg_setting_data_block const* const* const data_blocks =
		(void*) mem_adjust_table->data_blocks;

	/*
	if (0 == mem_adjust_table->num_index) { // heuristic
		if regcmp(index, ...) {
			mem_adjust_table->reg_set = ...
		}
	}
	*/
	if (COMMON_SET_UNKNOWN != mem_adjust_table->reg_set) {
		mem_adjust_table->data_sets = mem_adjust_table->data_blocks[0];
	}

	/*
	#ifndef NDEBUG
	if ((1 < mem_adjust_table->num_index)
			&& (COMMON_SET_UNKNOWN == mem_adjust_table->reg_set)
			) {
		register_set_print_tables(
			mem_adjust_table, &GMC_reg_set, true, "mem_adjust_set"
		);
		//assert(mem_adjust_table->reg_set); // unknown adjust sequence
	}
	#endif
	*/
}

static void
populate_mem_clk_patch(
		struct atomtree_init_reg_block* const mem_clk_patch,
		struct atomtree_vram_module const* const vram_modules
		) {
	populate_init_reg_block(mem_clk_patch);
	mem_clk_patch->reg_type = REG_BLOCK_MEM_CLK_PATCH;

	enum atom_dgpu_vram_type const vram_type = get_vram_type(&vram_modules[0]);
	enum atomtree_common_version const vram_module_ver =
		vram_modules[0].vram_module_ver;
	struct atom_init_reg_index_format const* const index =
		mem_clk_patch->register_index;
	struct atom_reg_setting_data_block const* const* const data_blocks =
		(void*) mem_clk_patch->data_blocks;

	// go by static tables instead of individually constructing the bitfields
	// because static tables offers a more consise, typed API.
	if (14 == mem_clk_patch->num_index) { // optimisation heuristic
		if (regcmp(index, timings_set_polaris_addresses)) {
			mem_clk_patch->reg_set = TIMINGS_SET_POLARIS;
		} else if (regcmp(index, timings_set_islands_type1_addresses)
				|| regcmp(index, timings_set_islands_type2_addresses)
				) {
			// Northern, Southern, Sea, Volcanic Islands
			if (vram_type == ATOM_DGPU_VRAM_TYPE_DDR3) {
				mem_clk_patch->reg_set = TIMINGS_SET_ISLANDS_DDR3;
			} else {
				mem_clk_patch->reg_set = TIMINGS_SET_ISLANDS_GDDR5;
			}
		}
	} else if (10 == mem_clk_patch->num_index) {
		if (regcmp(index, timings_set_fiji_addresses)) {
			mem_clk_patch->reg_set = TIMINGS_SET_FIJI;
		}
	}

	if (COMMON_SET_UNKNOWN != mem_clk_patch->reg_set) {
		mem_clk_patch->data_sets = mem_clk_patch->data_blocks[0];
	}

	#ifndef NDEBUG
	if ((1 < mem_clk_patch->num_index)
			&& (COMMON_SET_UNKNOWN == mem_clk_patch->reg_set)
			) {
		register_set_print_tables(
			mem_clk_patch, &GMC_reg_set, true, "timings_set"
		);
		//assert(mem_clk_patch->reg_set); // unknown timings sequence
	}
	#endif
}

static void
populate_mc_tile_adjust(
		struct atomtree_init_reg_block* const mc_tile_adjust,
		struct atomtree_vram_module const* const vram_modules
		) {
	populate_init_reg_block(mc_tile_adjust);
	mc_tile_adjust->reg_type = REG_BLOCK_MC_TILE_ADJUST;

	enum atom_dgpu_vram_type const vram_type = get_vram_type(&vram_modules[0]);
	enum atomtree_common_version const vram_module_ver =
		vram_modules[0].vram_module_ver;
	struct atom_init_reg_index_format const* const index =
		mc_tile_adjust->register_index;
	struct atom_reg_setting_data_block const* const* const data_blocks =
		(void*) mc_tile_adjust->data_blocks;
	
	/*
	if (0 == mc_tile_adjust->num_index) {
		if regcmp(index, ...) {
			mc_tile_adjust->reg_set = ...
		}
	}
	*/

	if (COMMON_SET_UNKNOWN != mc_tile_adjust->reg_set) {
		mc_tile_adjust->data_sets = mc_tile_adjust->data_blocks[0];
	}

	/*
	#ifndef NDEBUG
	if ((1 < mc_tile_adjust->num_index)
			&& (COMMON_SET_UNKNOWN == mc_tile_adjust->reg_set)
			) {
		register_set_print_tables(
			mc_tile_adjust, &GMC_reg_set, true, "mc_tile_adjust_set"
		);
	}
	#endif
	*/
}

static void
populate_init_mc_phy_init(
		struct atomtree_init_reg_block* const mc_phy_init,
		struct atomtree_vram_module const* const vram_modules
		) {
	populate_init_reg_block(mc_phy_init);
	mc_phy_init->reg_type = REG_BLOCK_MC_PHY_INIT;

	enum atom_dgpu_vram_type const vram_type = get_vram_type(&vram_modules[0]);
	enum atomtree_common_version const vram_module_ver =
		vram_modules[0].vram_module_ver;
	struct atom_init_reg_index_format const* const index =
		mc_phy_init->register_index;
	struct atom_reg_setting_data_block const* const* const data_blocks =
		(void*) mc_phy_init->data_blocks;

	/*
	if (0 == mc_phy_init->num_index) {
		if regcmp(index, ...) {
			mc_phy_init->reg_set = ...
		}
	}
	*/

	if (COMMON_SET_UNKNOWN != mc_phy_init->reg_set) {
		mc_phy_init->data_sets = mc_phy_init->data_blocks[0];
	}

	/*
	#ifndef NDEBUG
	if ((1 < mc_phy_init->num_index)
			&& (COMMON_SET_UNKNOWN == mc_phy_init->reg_set)
			) {
		register_set_print_tables(
			mc_phy_init, &GMC_reg_set, true, "mc_phy_init_set"
		);
	}
	#endif
	*/
}


static void
populate_umc_init_reg_block(
		struct atomtree_umc_init_reg_block* const at_regblock
		) {
	// UMC inititialisation registers, for vram_info 2.3 and newer
	// regblock->leaves must be already populated.
	/*
	Take a look at struct atom_umc_init_reg_block of atomfirmware.h
	This struct has 3 notable lists:
	umc_reg_list, umc_reg_setting_list, and
	atom_umc_reg_setting_data_block's umc_reg_data.
	These lists are all dynamically sized.

	umc_reg_list follows umc_reg_num.
	umc_reg_setting_list starts immediately after umc_reg_list.
	umc_reg_setting_list does not follow umc_reg_num, but ends with 0-fill.
	and atom_umc_reg_setting_data_block's umc_reg_data follows
	umc_reg_num.
	*/

	struct atom_umc_init_reg_block* const leaves = at_regblock->leaves;

	at_regblock->register_info = leaves->umc_reg_list;
	at_regblock->num_info = leaves->umc_reg_num;

	at_regblock->num_data_entries = leaves->umc_reg_num;
	at_regblock->data_block_element_size = (
		sizeof(((struct atom_umc_reg_setting_data_block*)0)->block_id)
		+ (sizeof(((struct atom_umc_reg_setting_data_block*)0)->umc_reg_data[0])
			* at_regblock->num_data_entries
		)
	);
	struct atom_umc_reg_setting_data_block* block = (   // starting point
		(void*)leaves->umc_reg_list
		+ (sizeof(union atom_umc_register_addr_info_access)
			* leaves->umc_reg_num
		) // size of umc_reg_list
	);
	uint8_t i = 0;
	while (block->block_id.id_access) { // the datablock list ends with 0
		assert(ATOMTREE_UMC_REG_MAX > i);
		at_regblock->data_blocks[i] = block;
		i++;
		block = (void*)block + at_regblock->data_block_element_size;
	}
	at_regblock->num_data_blocks = i;

	at_regblock->info_table_size = (
		at_regblock->num_info * sizeof(union atom_umc_register_addr_info_access)
	);
	at_regblock->data_block_table_size = (
	 	at_regblock->data_block_element_size * at_regblock->num_data_blocks
	);
	at_regblock->total_size = (
		offsetof(struct atom_umc_init_reg_block, umc_reg_list) // 4 bytes
		+ at_regblock->info_table_size
		+ at_regblock->data_block_table_size
	);
}


inline static void
populate_atom_memory_timing_format(
		struct atomtree_vram_module* const vram_module,
		enum atom_dgpu_vram_type const memory_type,
		union atom_memory_timing_format const* const timings,
		uint16_t const straps_total_size
		) {
	uint8_t table_size;
	if ((memory_type == ATOM_DGPU_VRAM_TYPE_GDDR5)
			|| (memory_type == ATOM_DGPU_VRAM_TYPE_GDDR5_2)
			) {
		if (0xFF == timings->v1_1.Terminator) {
			vram_module->memory_timing_format_ver = v1_1;
			table_size = sizeof(timings->v1_1);
		} else {
			assert(0xFF == timings->v1_2.Terminator);
			vram_module->memory_timing_format_ver = v1_2;
			table_size = sizeof(timings->v1_2);
		}
	} else {
		vram_module->memory_timing_format_ver = v1_0;
		table_size = sizeof(timings->v1_0);
	}
	vram_module->num_memory_timing_format = straps_total_size / table_size;
}


inline static void
populate_vram_module(
		void* vram_module_offset,
		struct atomtree_vram_module* const vram_modules,
		enum atomtree_common_version const vram_modules_ver,
		uint8_t const count
		) {
	assert(count <= ATOMTREE_VRAM_MODULES_MAX);
	uint8_t i;
	struct atomtree_vram_module* vmod;
	switch (vram_modules_ver) {
		case v1_3: // atom_vram_module_v3. Will look very similar to v4
			for (i=0; i < count; i++) {
				vmod = &(vram_modules[i]);
				vmod->leaves = vram_module_offset;
				vmod->vram_module_ver = v1_3;
				vmod->gmc_bitfields_ver = nover; // TODO
				vram_module_offset += vmod->v1_3->ModuleSize;

				populate_atom_memory_timing_format(
					vmod, vmod->v1_3->MemoryType, vmod->v1_3->MemTiming,
					(vmod->v1_3->ModuleSize
						- offsetof(typeof(*vmod->v1_3), MemTiming)
					)
				);
			} // loop
			break;

		case v1_4: // atom_vram_module_v4. Will look very similar to v3
			for (i=0; i < count; i++) {
				vmod = &(vram_modules[i]);
				vmod->leaves = vram_module_offset;
				vmod->vram_module_ver = v1_4;
				vmod->gmc_bitfields_ver = nover; // TODO
				vram_module_offset += vmod->v1_4->ModuleSize;

				populate_atom_memory_timing_format(
					vmod, vmod->v1_4->MemoryType, vmod->v1_4->MemTiming,
					(vmod->v1_4->ModuleSize
						- offsetof(typeof(*vmod->v1_4), MemTiming)
					)
				);

			} // loop
			break;

		case v1_7:
			for (i=0; i < count; i++) {
				vmod = &(vram_modules[i]);
				vmod->leaves = vram_module_offset;
				vmod->vram_module_ver = v1_7;
				if (vmod->v1_7->ChannelMapCfg >> 24) { // infer
					// TODO explicit way to find GMC?
					// does it follow vram_module ver? doesn't seem so
					vmod->gmc_bitfields_ver = v7_1;
				} else {
					vmod->gmc_bitfields_ver = v6_0;
				}
				vram_module_offset += vmod->v1_7->ModuleSize;
			}
			break;
		case v1_8:
			for (i=0; i < count; i++) {
				vmod = &(vram_modules[i]);
				vmod->leaves = vram_module_offset;
				vmod->vram_module_ver = v1_8;
				vmod->gmc_bitfields_ver = nover; // TODO
				vram_module_offset += vmod->v1_8->ModuleSize;
			}
			break;

		case v1_9:
			for (i=0; i < count; i++) {
				vmod = &(vram_modules[i]);
				vmod->leaves = vram_module_offset;
				vmod->vram_module_ver = v1_9;
				vmod->gmc_bitfields_ver = nover; // TODO
				vram_module_offset += vmod->v1_9->vram_module_size;
			}
			break;

		case v1_10:
			for (i=0; i < count; i++) {
				vmod = &(vram_modules[i]);
				vmod->leaves = vram_module_offset;
				vmod->vram_module_ver = v1_10;
				vmod->gmc_bitfields_ver = nover; // TODO
				vram_module_offset += vmod->v1_10->vram_module_size;
			}
			break;

		case v1_11:
			for (i=0; i < count; i++) {
				vmod = &(vram_modules[i]);
				vmod->leaves = vram_module_offset;
				vmod->vram_module_ver = v1_11;
				vmod->gmc_bitfields_ver = nover; // TODO
				vram_module_offset += vmod->v1_11->vram_module_size;
			}
			break;

		case v3_0:
			for (i=0; i < count; i++) {
				vmod = &(vram_modules[i]);
				vmod->leaves = vram_module_offset;
				vmod->vram_module_ver = v3_0;
				vmod->gmc_bitfields_ver = nover; // TODO
				//vram_module_offset += vmod->v3_0->vram_module_size;
				vram_module_offset += sizeof(*vmod->v3_0);

				if (vmod->v3_0->dram_info_offset) {
					vmod->dram_info = (
						vmod->leaves + vmod->v3_0->dram_info_offset
					);
				}
				if (vmod->v3_0->mem_tuning_offset) {
					vmod->mem_tuning = (
						vmod->leaves
						+ vmod->v3_0->mem_tuning_offset
					);
				}
				if (vmod->v3_0->tmrs_seq_offset) {
					vmod->tmrs_seq = (
						vmod->leaves + vmod->v3_0->tmrs_seq_offset
					);
				}
			}
			break;
		default:
			assert(0); // TODO implement
			break;
	}
}

inline static void
populate_vram_info_v1_2(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_v1_2* const vi12 = &(vram_info->v1_2);
	vi12->leaves = vram_info->leaves;

	if (vi12->leaves->NumOfVRAMModule) {
		vi12->vram_module_ver = v1_3;
		populate_vram_module(
			vi12->leaves->vram_module,
			vi12->vram_modules,
			vi12->vram_module_ver,
			vi12->leaves->NumOfVRAMModule
		);
	}
}

inline static void
populate_vram_info_v1_3(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_v1_3* const vi13 = &(vram_info->v1_3);
	vi13->leaves = vram_info->leaves;

	if (vi13->leaves->NumOfVRAMModule) {
		vi13->vram_module_ver = v1_3;
		populate_vram_module(
			vi13->leaves->vram_module,
			vi13->vram_modules,
			vi13->vram_module_ver,
			vi13->leaves->NumOfVRAMModule
		);
	}

	if (vi13->leaves->MemAdjustTblOffset) {
		vi13->mem_adjust_table.leaves =
			(void*)vi13->leaves + vi13->leaves->MemAdjustTblOffset;
		populate_init_reg_block(&(vi13->mem_adjust_table));
	}

	if (vi13->leaves->MemClkPatchTblOffset) {
		// TODO at least for R600, what is in here isn't timings, and gmc.h
		// doesn't decode them right.
		vi13->mem_clk_patch.leaves =
			(void*)vi13->leaves + vi13->leaves->MemClkPatchTblOffset;
		populate_init_reg_block(&(vi13->mem_clk_patch));
	}
}

inline static void
populate_vram_info_v1_4(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_v1_4* const vi14 = &(vram_info->v1_4);
	vi14->leaves = vram_info->leaves;

	if (vi14->leaves->NumOfVRAMModule) {
		vi14->vram_module_ver = v1_4;
		populate_vram_module(
			vi14->leaves->vram_module,
			vi14->vram_modules,
			vi14->vram_module_ver,
			vi14->leaves->NumOfVRAMModule
		);
	}

	if (vi14->leaves->MemAdjustTblOffset) {
		vi14->mem_adjust_table.leaves =
			(void*)vi14->leaves + vi14->leaves->MemAdjustTblOffset;
		populate_init_reg_block(&(vi14->mem_adjust_table));
	}

	if (vi14->leaves->MemClkPatchTblOffset) {
		// TODO See populate_vram_info_v1_3
		vi14->mem_clk_patch.leaves =
			(void*)vi14->leaves + vi14->leaves->MemClkPatchTblOffset;
		populate_init_reg_block(&(vi14->mem_clk_patch));
	}
}

inline static void
populate_vram_info_v2_1(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_1* const vi21 = &(vram_info->v2_1);
	vi21->leaves = vram_info->leaves;

	if (vi21->leaves->NumOfVRAMModule) {
		vi21->vram_module_ver = v1_7;
		populate_vram_module(
			vi21->leaves->vram_module,
			vi21->vram_modules,
			vi21->vram_module_ver,
			vi21->leaves->NumOfVRAMModule
		);
	}

	if (vi21->leaves->MemAdjustTblOffset) {
		vi21->mem_adjust_table.leaves =
			(void*)vi21->leaves + vi21->leaves->MemAdjustTblOffset;
		populate_mem_adjust_table(
			&(vi21->mem_adjust_table), vi21->vram_modules
		);
	}

	if (vi21->leaves->MemClkPatchTblOffset) {
		vi21->mem_clk_patch.leaves =
			(void*)vi21->leaves + vi21->leaves->MemClkPatchTblOffset;
		populate_mem_clk_patch(&(vi21->mem_clk_patch), vi21->vram_modules);
	}

	if (vi21->leaves->PerBytePresetOffset) {
		// TODO unsure what lies beyond; never seen this true.
		vi21->per_byte_preset.leaves =
			(void*)vi21->leaves + vi21->leaves->PerBytePresetOffset;
		populate_init_reg_block(&(vi21->per_byte_preset));
	}
}

inline static void
populate_vram_info_v2_2(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_2* const vi22 = &(vram_info->v2_2);
	vi22->leaves = vram_info->leaves;

	if (vi22->leaves->NumOfVRAMModule) {
		vi22->vram_module_ver = v1_8;
		populate_vram_module(
			vi22->leaves->vram_module,
			vi22->vram_modules,
			vi22->vram_module_ver,
			vi22->leaves->NumOfVRAMModule
		);
	}

	if (vi22->leaves->MemAdjustTblOffset) {
		vi22->mem_adjust_table.leaves =
			(void*)vi22->leaves + vi22->leaves->MemAdjustTblOffset;
		populate_mem_adjust_table(
			&(vi22->mem_adjust_table), vi22->vram_modules
		);
	}

	if (vi22->leaves->MemClkPatchTblOffset) {
		vi22->mem_clk_patch.leaves =
			(void*)vi22->leaves + vi22->leaves->MemClkPatchTblOffset;
		populate_mem_clk_patch(&(vi22->mem_clk_patch), vi22->vram_modules);
	}

	if (vi22->leaves->McAdjustPerTileTblOffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi22->mc_tile_adjust.leaves =
			(void*)vi22->leaves + vi22->leaves->McAdjustPerTileTblOffset;
		populate_mc_tile_adjust(&(vi22->mc_tile_adjust), vi22->vram_modules);
	}

	if (vi22->leaves->McPhyInitTableOffset) {
		vi22->mc_phy_init.leaves =
			(void*)vi22->leaves + vi22->leaves->McPhyInitTableOffset;
		populate_init_mc_phy_init(&(vi22->mc_phy_init), vi22->vram_modules);
	}

	if (vi22->leaves->DramDataRemapTblOffset) {
		vi22->dram_data_remap =
			(void*)vi22->leaves + vi22->leaves->DramDataRemapTblOffset;
	}
}

inline static void
populate_vram_info_v2_3(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_3* const vi23 = &(vram_info->v2_3);
	vi23->leaves = vram_info->leaves;

	if (vi23->leaves->vram_module_num) {
		vi23->vram_module_ver = v1_9;
		populate_vram_module(
			vi23->leaves->vram_module,
			vi23->vram_modules,
			vi23->vram_module_ver,
			vi23->leaves->vram_module_num
		);
	}

	if (vi23->leaves->mem_adjust_tbloffset) {
		vi23->mem_adjust_table.leaves =
			(void*)vi23->leaves + vi23->leaves->mem_adjust_tbloffset;
		populate_umc_init_reg_block(&(vi23->mem_adjust_table));
	}

	if (vi23->leaves->mem_clk_patch_tbloffset) {
		vi23->mem_clk_patch.leaves =
			(void*)vi23->leaves + vi23->leaves->mem_clk_patch_tbloffset;
		populate_umc_init_reg_block(&(vi23->mem_clk_patch));

		vi23->num_timing_straps = &(vi23->mem_clk_patch.num_data_blocks);
		vi23->mem_timings = vi23->mem_clk_patch.data_blocks[0];
		if (vi23->mem_clk_patch.data_block_element_size
			== sizeof(struct timings_set_vega10)) {
			vi23->uses_vega20_timings = false;
		} else if (vi23->mem_clk_patch.data_block_element_size
			== sizeof(struct timings_set_vega20)) {
			vi23->uses_vega20_timings = true;
		} else {
			assert(0);
		}
	}

	if (vi23->leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi23->mc_tile_adjust.leaves =
			(void*)vi23->leaves + vi23->leaves->mc_adjust_pertile_tbloffset;
		populate_umc_init_reg_block(&(vi23->mc_tile_adjust));
	}

	if (vi23->leaves->mc_phyinit_tbloffset) {
		vi23->mc_phy_init.leaves =
			(void*)vi23->leaves + vi23->leaves->mc_phyinit_tbloffset;
		populate_umc_init_reg_block(&(vi23->mc_phy_init));
	}

	if (vi23->leaves->dram_data_remap_tbloffset) {
	// TODO does vraminfo->mc_phy_tile_num significantly affect this?
	vi23->dram_data_remap =
		(void*)vi23->leaves + vi23->leaves->dram_data_remap_tbloffset;
	}

	if (vi23->leaves->tmrs_seq_offset) {
		// TODO what is this?
		vi23->hbm_tmrs = (void*)vi23->leaves + vi23->leaves->tmrs_seq_offset;
	}

	if (vi23->leaves->post_ucode_init_offset) {
		vi23->post_ucode_init.leaves =
			(void*)vi23->leaves + vi23->leaves->post_ucode_init_offset;
		populate_umc_init_reg_block(&(vi23->post_ucode_init));
	}
}

inline static void
populate_vram_info_v2_4(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_4* const vi24 = &(vram_info->v2_4);
	vi24->leaves = vram_info->leaves;
	struct atom_vram_info_header_v2_4* const leaves = vram_info->leaves;

	if (vi24->leaves->vram_module_num) {
		vi24->vram_module_ver = v1_10;
		populate_vram_module(
			vi24->leaves->vram_module,
			vi24->vram_modules,
			vi24->vram_module_ver,
			vi24->leaves->vram_module_num
		);
	}

	if (vi24->leaves->mem_adjust_tbloffset) {
		vi24->mem_adjust_table.leaves =
			(void*)vi24->leaves + vi24->leaves->mem_adjust_tbloffset;
		populate_umc_init_reg_block(&(vi24->mem_adjust_table));
	}

	if (vi24->leaves->mem_clk_patch_tbloffset) {
		vi24->mem_clk_patch.leaves =
			(void*)vi24->leaves + vi24->leaves->mem_clk_patch_tbloffset;
		populate_umc_init_reg_block(&(vi24->mem_clk_patch));

		vi24->num_timing_straps = &(vi24->mem_clk_patch.num_data_blocks);
		vi24->navi1_gddr6_timings =
			(struct timings_set_navi1*) vi24->mem_clk_patch.data_blocks[0];
	}

	if (vi24->leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi24->mc_tile_adjust.leaves =
			(void*)vi24->leaves + vi24->leaves->mc_adjust_pertile_tbloffset;
		populate_umc_init_reg_block(&(vi24->mc_tile_adjust));
	}

	if (vi24->leaves->mc_phyinit_tbloffset) {
		vi24->mc_phy_init.leaves =
			(void*)vi24->leaves + vi24->leaves->mc_phyinit_tbloffset;
		populate_umc_init_reg_block(&(vi24->mc_phy_init));
	}

	if (vi24->leaves->dram_data_remap_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi24->dram_data_remap =
			(void*)vi24->leaves + vi24->leaves->dram_data_remap_tbloffset;
	}

	if (vi24->leaves->post_ucode_init_offset) {
		vi24->post_ucode_init.leaves =
			(void*)vi24->leaves + vi24->leaves->post_ucode_init_offset;
		populate_umc_init_reg_block(&(vi24->post_ucode_init));
	}
}

inline static void
populate_vram_info_v2_5(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_5* const vi25 = &(vram_info->v2_5);
	vi25->leaves = vram_info->leaves;

	if (vi25->leaves->vram_module_num) {
		vi25->vram_module_ver = v1_11;
		populate_vram_module(
			vi25->leaves->vram_module,
			vi25->vram_modules,
			vi25->vram_module_ver,
			vi25->leaves->vram_module_num
		);
	}

	if (vi25->leaves->mem_adjust_tbloffset) {
		vi25->mem_adjust_table.leaves =
			(void*)vi25->leaves + vi25->leaves->mem_adjust_tbloffset;
		populate_umc_init_reg_block(&(vi25->mem_adjust_table));
	}

	if (vi25->leaves->gddr6_ac_timing_offset) {
		vi25->gddr6_ac_timings =
			(void*)vi25->leaves + vi25->leaves->gddr6_ac_timing_offset;
		uint16_t i = 0;
		for (; vi25->gddr6_ac_timings[i].block_id.id_access; i++);
		vi25->gddr6_acstrap_count = i;
	}

	if (vi25->leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi25->mc_tile_adjust.leaves =
			(void*)vi25->leaves + vi25->leaves->mc_adjust_pertile_tbloffset;
		populate_umc_init_reg_block(&(vi25->mc_tile_adjust));
	}

	if (vi25->leaves->mc_phyinit_tbloffset) {
		vi25->mc_phy_init.leaves =
			(void*)vi25->leaves + vi25->leaves->mc_phyinit_tbloffset;
		populate_umc_init_reg_block(&(vi25->mc_phy_init));
	}

	if (vi25->leaves->dram_data_remap_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi25->dram_data_remap =
			(void*)vi25->leaves + vi25->leaves->dram_data_remap_tbloffset;
	}

	if (vi25->leaves->post_ucode_init_offset) {
		vi25->post_ucode_init.leaves =
			(void*)vi25->leaves + vi25->leaves->post_ucode_init_offset;
		populate_umc_init_reg_block(&(vi25->post_ucode_init));
	}

	if (vi25->leaves->strobe_mode_patch_tbloffset) {
		vi25->strobe_mode_patch.leaves =
			(void*)vi25->leaves + vi25->leaves->strobe_mode_patch_tbloffset;
		populate_umc_init_reg_block(&(vi25->strobe_mode_patch));
	}
}

inline static void
populate_vram_info_v2_6(
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_6* const vi26 = &(vram_info->v2_6);
	vi26->leaves = vram_info->leaves;


	if (vi26->leaves->vram_module_num) {
		vi26->vram_module_ver = v1_9;
		populate_vram_module(
			vi26->leaves->vram_module,
			vi26->vram_modules,
			vi26->vram_module_ver,
			vi26->leaves->vram_module_num
		);
	}

	if (vi26->leaves->mem_adjust_tbloffset) {
		vi26->mem_adjust_table.leaves =
			(void*)vi26->leaves + vi26->leaves->mem_adjust_tbloffset;
		populate_umc_init_reg_block(&(vi26->mem_adjust_table));
	}

	if (vi26->leaves->mem_clk_patch_tbloffset) {
		vi26->mem_clk_patch.leaves =
			(void*)vi26->leaves + vi26->leaves->mem_clk_patch_tbloffset;
		populate_umc_init_reg_block(&(vi26->mem_clk_patch));
	}

	if (vi26->leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi26->mc_tile_adjust.leaves =
			(void*)vi26->leaves + vi26->leaves->mc_adjust_pertile_tbloffset;
		populate_umc_init_reg_block(&(vi26->mc_tile_adjust));
	}

	if (vi26->leaves->mc_phyinit_tbloffset) {
		vi26->mc_phy_init.leaves =
			(void*)vi26->leaves + vi26->leaves->mc_phyinit_tbloffset;
		populate_umc_init_reg_block(&(vi26->mc_phy_init));
	}

	if (vi26->leaves->tmrs_seq_offset) {
		// TODO what is this?
		vi26->tmrs_seq = (void*)vi26->leaves + vi26->leaves->tmrs_seq_offset;
	}

	if (vi26->leaves->dram_data_remap_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi26->dram_data_remap =
			(void*)vi26->leaves + vi26->leaves->dram_data_remap_tbloffset;
	}

	if (vi26->leaves->post_ucode_init_offset) {
		vi26->post_ucode_init.leaves =
			(void*)vi26->leaves + vi26->leaves->post_ucode_init_offset;
		populate_umc_init_reg_block(&(vi26->post_ucode_init));
	}
}

inline static void
populate_vram_info_v3_0( // TODO finish this
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v3_0* const vi30 = &(vram_info->v3_0);
	vi30->leaves = vram_info->leaves;

	if (vi30->leaves->vram_module_num) {
		vi30->vram_module_ver = v3_0;
		populate_vram_module(
			vi30->leaves->vram_module,
			vi30->vram_modules,
			vi30->vram_module_ver,
			vi30->leaves->vram_module_num
		);
	}

	if (vi30->leaves->mem_tuning_table_offset) {
		vi30->mem_tuning =
			(void*)vi30->leaves + vi30->leaves->mem_tuning_table_offset;
	}

	if (vi30->leaves->dram_info_table_offset) {
		vi30->dram_info =
			(void*)vi30->leaves + vi30->leaves->dram_info_table_offset;
	}

	if (vi30->leaves->tmrs_table_offset) {
		vi30->tmrs_seq = (void*)vi30->leaves + vi30->leaves->tmrs_table_offset;
	}

	if (vi30->leaves->mc_init_table_offset) {
		vi30->mc_init.leaves =
			(void*)vi30->leaves + vi30->leaves->mc_init_table_offset;
		populate_umc_init_reg_block(&(vi30->mc_init));
	}

	if (vi30->leaves->dram_data_remap_table_offset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi30->dram_data_remap =
			(void*)vi30->leaves + vi30->leaves->dram_data_remap_table_offset;
	}

	if (vi30->leaves->umc_emuinit_table_offset) {
		vi30->umc_emuinit.leaves =
			(void*)vi30->leaves + vi30->leaves->umc_emuinit_table_offset;
		populate_umc_init_reg_block(&(vi30->umc_emuinit));
	}

	if (vi30->leaves->reserved_sub_table_offset[0]) {
		vi30->rsvd_tables[0] =
			(void*)vi30->leaves + vi30->leaves->reserved_sub_table_offset[0];
	}
	if (vi30->leaves->reserved_sub_table_offset[1]) {
		vi30->rsvd_tables[1] =
			(void*)vi30->leaves + vi30->leaves->reserved_sub_table_offset[1];
	}
}

inline static void
populate_vram_info(
		struct atomtree_vram_info* const vram_info,
		struct atom_tree* const atree,
		uint16_t const bios_offset
		) {
	if (bios_offset) {
		vram_info->leaves = atree->bios + bios_offset;
		vram_info->ver = get_ver(vram_info->table_header);
		switch (vram_info->ver) { // TODO: earlier tables than 2.3?
			case v1_2: populate_vram_info_v1_2(vram_info); break;
			case v1_3: populate_vram_info_v1_3(vram_info); break;
			case v1_4: populate_vram_info_v1_4(vram_info); break;
			case v2_1: populate_vram_info_v2_1(vram_info); break;
			case v2_2: populate_vram_info_v2_2(vram_info); break;
			case v2_3: populate_vram_info_v2_3(vram_info); break;
			case v2_4: populate_vram_info_v2_4(vram_info); break;
			case v2_5: populate_vram_info_v2_5(vram_info); break;
			case v2_6: populate_vram_info_v2_6(vram_info); break;
			case v3_0: populate_vram_info_v3_0(vram_info); break;
			default: break;
		}
	}
}

inline static void
populate_voltageobject_info_v1_1(
		struct atomtree_voltageobject_info* const vo_info
		) {
	struct atomtree_voltage_object* const voltage_objects = (
		vo_info->voltage_objects
	);
	uint16_t i = 0;

	// get the size ofthe dynamically-sized voltage object array, and walk
	// through the array based on what each element reports their size as.
	union {
		void* raw;
		union atom_voltage_object_all* vobj;
	} vobj;
	vobj.raw = vo_info->v1_1->VoltageObj;
	void const* const end = (
		vo_info->leaves
		+ vo_info->table_header->structuresize
	);
	while (vobj.raw < end) {
		assert(ATOMTREE_VOLTAGE_OBJECTS_MAX > i);
		voltage_objects[i].obj = vobj.vobj;
		voltage_objects[i].ver = v1_0;
		// NumOfVoltageEntries lies and can be 255.
		voltage_objects[i].lut_entries = (
			(
				vobj.vobj->volt_obj_v1.Size
				- offsetof(
					struct atom_voltage_object_v1,
					Formula.VIDAdjustEntries[0]
				)
			) / sizeof(uint8_t)
		);
		vobj.raw += vobj.vobj->volt_obj_v1.Size;
		i++;
	}
	assert(vobj.raw == end);
	vo_info->num_voltage_objects = i;
}

inline static void
populate_voltageobject_info_v1_2(
		struct atomtree_voltageobject_info* const vo_info
		) {
	struct atomtree_voltage_object* const voltage_objects = (
		vo_info->voltage_objects
	);
	uint16_t i = 0;

	// get the size ofthe dynamically-sized voltage object array, and walk
	// through the array based on what each element reports their size as.
	union {
		void* raw;
		union atom_voltage_object_all* vobj;
	} vobj;
	vobj.raw = vo_info->v1_2->VoltageObj;
	void const* const end = (
		vo_info->leaves
		+ vo_info->table_header->structuresize
	);
	while (vobj.raw < end) {
		assert(ATOMTREE_VOLTAGE_OBJECTS_MAX > i);
		voltage_objects[i].obj = vobj.vobj;
		voltage_objects[i].ver = v2_0;
		// NumOfVoltageEntries lies and can be 255.
		voltage_objects[i].lut_entries = (
			(
				vobj.vobj->volt_obj_v2.Size
				- offsetof(
					struct atom_voltage_object_v2,
					Formula.VIDAdjustEntries[0]
				)
			) / sizeof(struct voltage_lut_entry)
		);
		vobj.raw += vobj.vobj->volt_obj_v2.Size;
		i++;
	}
	assert(vobj.raw == end);
	vo_info->num_voltage_objects = i;
}

inline static void
populate_voltageobject_info_v3_1(
		struct atomtree_voltageobject_info* const vo_info
		) {
	struct atomtree_voltage_object* const voltage_objects = (
		vo_info->voltage_objects
	);
	uint16_t i = 0;

	// get the size ofthe dynamically-sized voltage object array, and walk
	// through the array based on what each element reports their size as.
	union {
		void* raw;
		union atom_voltage_object_all* vobj;
	} vobj;
	vobj.raw = vo_info->v3_1->voltage_object;
	void const* const end = (
		vo_info->leaves
		+ vo_info->table_header->structuresize
	);
	while (vobj.raw < end) {
		assert(ATOMTREE_VOLTAGE_OBJECTS_MAX > i);
		voltage_objects[i].obj = vobj.vobj;
		voltage_objects[i].ver = v1_0;
		switch (vobj.vobj->header.voltage_mode) {
			// some voltage objects have a dynamically-sized lookup table.
			case VOLTAGE_OBJ_GPIO_LUT:
			case VOLTAGE_OBJ_PHASE_LUT:
				voltage_objects[i].lut_entries = (
					vobj.vobj->gpio_voltage_obj_v1.gpio_entry_num
				);
				assert(voltage_objects[i].lut_entries == (
					(
						vobj.vobj->header.object_size
						- offsetof(
							struct atom_gpio_voltage_object_v1,
							voltage_gpio_lut[0]
						)
					) / sizeof(struct atom_voltage_gpio_map_lut)
				));
				break;
			case VOLTAGE_OBJ_VR_I2C_INIT_SEQ:
				voltage_objects[i].lut_entries = (
					(
						vobj.vobj->header.object_size
						- offsetof(
							struct atom_i2c_voltage_object_v1,
							i2cdatalut[0]
						)
					) / sizeof(struct atom_i2c_data_entry)
				);
				break;
			case VOLTAGE_OBJ_EVV:
				voltage_objects[i].lut_entries = (
						(
							vobj.vobj->header.object_size
							- offsetof(
								struct atom_evv_voltage_object_v1,
								EvvDpmList[0]
							)
						) / sizeof(struct atom_evv_dpm_info)
					);
				assert(
					vobj.vobj->header.object_size
					== sizeof(struct atom_evv_voltage_object_v1)
				);
				break;
			case VOLTAGE_OBJ_PWRBOOST_LEAKAGE_LUT:
			case VOLTAGE_OBJ_HIGH_STATE_LEAKAGE_LUT:
			case VOLTAGE_OBJ_HIGH1_STATE_LEAKAGE_LUT:
				voltage_objects[i].lut_entries = (
					vobj.vobj->leakage_voltage_obj_v1.LeakageEntryNum
				);
				assert(voltage_objects[i].lut_entries == (
					(
						vobj.vobj->header.object_size
						- offsetof(
							struct atom_leakage_voltage_object_v1,
							LeakageIdLut[0]
						)
					) / sizeof(struct leakage_voltage_lut_entry_v2)
				));
				break;
			default:
				break;
		}

		vobj.raw += vobj.vobj->header.object_size;
		i++;
	}
	assert(vobj.raw == end);
	vo_info->num_voltage_objects = i;
}


inline static void
populate_voltageobject_info_v4_1(
		struct atomtree_voltageobject_info* const vo_info
		) {
	struct atomtree_voltage_object* const voltage_objects = (
		vo_info->voltage_objects
	);
	uint16_t i = 0;

	// get the size ofthe dynamically-sized voltage object array, and walk
	// through the array based on what each element reports their size as.
	union {
		void* raw;
		union atom_voltage_object_all* vobj;
	} vobj;
	vobj.raw = vo_info->v4_1->voltage_object;
	void const* const end = (
		vo_info->leaves
		+ vo_info->table_header->structuresize
	);
	while (vobj.raw < end) {
		assert(ATOMTREE_VOLTAGE_OBJECTS_MAX > i);
		voltage_objects[i].obj = vobj.vobj;
		voltage_objects[i].ver = v1_0;
		switch (vobj.vobj->header.voltage_mode) {
			// some voltage objects have a dynamically-sized lookup table.
			case VOLTAGE_OBJ_GPIO_LUT:
			case VOLTAGE_OBJ_PHASE_LUT:
				voltage_objects[i].lut_entries = (
					(
						vobj.vobj->header.object_size
						- offsetof(
							struct atom_gpio_voltage_object_v1,
							voltage_gpio_lut[0]
						)
					) / sizeof(struct atom_voltage_gpio_map_lut)
				);
				break;
			case VOLTAGE_OBJ_VR_I2C_INIT_SEQ:
				voltage_objects[i].lut_entries = (
					(
						vobj.vobj->header.object_size
						- offsetof(
							struct atom_i2c_voltage_object_v1,
							i2cdatalut[0]
						)
					) / sizeof(struct atom_i2c_data_entry)
				);
				break;
			case VOLTAGE_OBJ_SVID2:
				voltage_objects[i].ver = v2_0;
			default:
				break;
		}

		vobj.raw += vobj.vobj->header.object_size;
		i++;
	}
	assert(vobj.raw == end);
	vo_info->num_voltage_objects = i;
}


inline static void
populate_voltageobject_info(
		struct atomtree_voltageobject_info* const vo_info,
		struct atom_tree* const atree,
		uint16_t const bios_offset
		) {
	if (bios_offset) {
		vo_info->leaves = atree->bios + bios_offset;
		vo_info->ver = get_ver(vo_info->table_header);
		switch (vo_info->ver) {
			case v1_1: populate_voltageobject_info_v1_1(vo_info); break;
			case v1_2: populate_voltageobject_info_v1_2(vo_info); break;
			case v3_1: populate_voltageobject_info_v3_1(vo_info); break;
			case v4_2: // hopefully v4_2 is the same
			case v4_1: populate_voltageobject_info_v4_1(vo_info); break;
			case v1_0: assert(0);
			default: break;
		}
	}
}


inline static void
populate_master_datatable_v1_1(
		struct atomtree_master_datatable* const data_table,
		struct atom_tree* const atree
		) {
	void* const bios = atree->bios;
	struct atomtree_master_datatable_v1_1* const dt11 = &(data_table->v1_1);
	dt11->leaves = data_table->leaves;
	struct atom_master_data_table_v1_1* const leaves = data_table->leaves;

	if (leaves->UtilityPipeLine) {
		dt11->utilitypipeline = bios + leaves->UtilityPipeLine;
	}

	if (leaves->MultimediaCapabilityInfo) {
		dt11->multimedia_capability_info =
			bios + leaves->MultimediaCapabilityInfo;
	}
	if (leaves->MultimediaConfigInfo) {
		dt11->multimedia_config_info =
			bios + leaves->MultimediaConfigInfo;
	}

	if (leaves->StandardVESA_Timing) {
		dt11->vesa_timing = bios + leaves->StandardVESA_Timing;
	}

	populate_firmwareinfo(&(dt11->firmwareinfo), atree, leaves->FirmwareInfo);

	if (leaves->PaletteData) {
		dt11->palette_data = bios + leaves->PaletteData;
	}

	populate_lcd_info(&(dt11->lcd_info), atree, leaves->LCD_Info);

	if (leaves->DIGTransmitterInfo) {
		dt11->dig_transmitter_info = bios + leaves->DIGTransmitterInfo;
	}

	populate_smu_info(&(dt11->smu_info), atree, leaves->SMU_Info);

	if (leaves->SupportedDevicesInfo) {
		dt11->supported_devices_info = bios + leaves->SupportedDevicesInfo;
	}

	if (leaves->GPIO_I2C_Info) {
		dt11->gpio_i2c_info = bios + leaves->GPIO_I2C_Info;
	}

	populate_vram_usagebyfirmware(
		&(dt11->vram_usagebyfirmware), atree, leaves->VRAM_UsageByFirmware
	);

	populate_gpio_pin_lut(&(dt11->gpio_pin_lut), atree, leaves->GPIO_Pin_LUT);

	if (leaves->VESA_ToInternalModeLUT) {
		dt11->vesa_to_internal_mode = bios + leaves->VESA_ToInternalModeLUT;
	}

	populate_gfx_info(&(dt11->gfx_info), atree, leaves->GFX_Info);

	populate_ppt(&(dt11->powerplayinfo), atree, leaves->PowerPlayInfo);

	if (leaves->GPUVirtualizationInfo) {
		dt11->gpu_virtualization_info = bios + leaves->GPUVirtualizationInfo;
	}

	if (leaves->SaveRestoreInfo) {
		dt11->save_restore_info = bios + leaves->SaveRestoreInfo;
	}

	if (leaves->PPLL_SS_Info) {
		dt11->ppll_ss_info = bios + leaves->PPLL_SS_Info;
	}

	if (leaves->OemInfo) {
		dt11->oem_info = bios + leaves->OemInfo;
	}

	if (leaves->XTMDS_Info) {
		dt11->xtmds_info = bios + leaves->XTMDS_Info;
	}

	if (leaves->MclkSS_Info) {
		dt11->mclk_ss_info = bios + leaves->MclkSS_Info;
	}

	if (leaves->Object_Header) {
		dt11->object_header = bios + leaves->Object_Header;
	}

	if (leaves->IndirectIOAccess) {
		dt11->indirect_io_access = bios + leaves->IndirectIOAccess;
	}

	if (leaves->MC_InitParameter) {
		dt11->mc_init_parameter = bios + leaves->MC_InitParameter;
	}

	if (leaves->ASIC_VDDC_Info) {
		dt11->asic_vddc_info = bios + leaves->ASIC_VDDC_Info;
	}

	if (leaves->ASIC_InternalSS_Info) {
		dt11->asic_internal_ss_info = bios + leaves->ASIC_InternalSS_Info;
	}

	if (leaves->TV_VideoMode) {
		dt11->tv_video_mode = bios + leaves->TV_VideoMode;
	}

	populate_vram_info(&(dt11->vram_info), atree, leaves->VRAM_Info);

	if (leaves->MemoryTrainingInfo) {
		dt11->memory_training_info = bios + leaves->MemoryTrainingInfo;
	}

	if (leaves->IntegratedSystemInfo) {
		dt11->integrated_system_info = bios + leaves->IntegratedSystemInfo;
	}

	if (leaves->ASIC_ProfilingInfo) {
		dt11->asic_profiling_info = bios + leaves->ASIC_ProfilingInfo;
	}

	populate_voltageobject_info(
		&(dt11->voltageobject_info), atree, leaves->VoltageObjectInfo
	);

	if (leaves->PowerSourceInfo) {
		dt11->power_source_info = bios + leaves->PowerSourceInfo;
	}

	if (leaves->ServiceInfo) {
		dt11->service_info = bios + leaves->ServiceInfo;
	}
}

inline static void
atomtree_datatable_v2_1_populate_sw_datatables(
		struct atomtree_master_datatable_v2_1* const data_table,
		struct atom_tree* const atree
		) {
	struct atom_master_data_table_v2_1* const leaves = data_table->leaves;
	void* const bios = atree->bios;

	if (leaves->sw_datatable3) {
		data_table->sw_datatable3.leaves = bios + leaves->sw_datatable3;
	}

	if (leaves->sw_datatable5) {
		data_table->sw_datatable5.leaves = bios + leaves->sw_datatable5;
	}

	if (leaves->sw_datatable7) {
		data_table->sw_datatable7.leaves = bios + leaves->sw_datatable7;
	}

	if (leaves->sw_datatable9) {
		data_table->sw_datatable9.leaves = bios + leaves->sw_datatable9;
	}

	if (leaves->sw_datatable10) {
		data_table->sw_datatable10.leaves = bios + leaves->sw_datatable10;
	}

	if (leaves->sw_datatable13) {
		data_table->sw_datatable13.leaves = bios + leaves->sw_datatable13;
	}

	if (leaves->sw_datatable16) {
		data_table->sw_datatable16.leaves = bios + leaves->sw_datatable16;
	}

	if (leaves->sw_datatable17) {
		data_table->sw_datatable17.leaves = bios + leaves->sw_datatable17;
	}

	if (leaves->sw_datatable18) {
		data_table->sw_datatable18.leaves = bios + leaves->sw_datatable18;
	}

	if (leaves->sw_datatable19) {
		data_table->sw_datatable19.leaves = bios + leaves->sw_datatable19;
	}

	if (leaves->sw_datatable20) {
		data_table->sw_datatable20.leaves = bios + leaves->sw_datatable20;
	}

	if (leaves->sw_datatable21) {
		data_table->sw_datatable21.leaves = bios + leaves->sw_datatable21;
	}

	if (leaves->sw_datatable25) {
		data_table->sw_datatable25.leaves = bios + leaves->sw_datatable25;
	}

	if (leaves->sw_datatable26) {
		data_table->sw_datatable26.leaves = bios + leaves->sw_datatable26;
	}

	if (leaves->sw_datatable29) {
		data_table->sw_datatable29.leaves = bios + leaves->sw_datatable29;
	}

	if (leaves->sw_datatable33) {
		data_table->sw_datatable33.leaves = bios + leaves->sw_datatable33;
	}

	if (leaves->sw_datatable34) {
		data_table->sw_datatable34.leaves = bios + leaves->sw_datatable34;
	}
}
inline static void
populate_master_datatable_v2_1(
		struct atomtree_master_datatable* const data_table,
		struct atom_tree* const atree
		) {
	void* const bios = atree->bios;
	struct atomtree_master_datatable_v2_1* const dt21 = &(data_table->v2_1);
	dt21->leaves = data_table->leaves;
	struct atom_master_data_table_v2_1* const leaves = data_table->leaves;

	if (leaves->utilitypipeline) {
		dt21->utilitypipeline = bios + leaves->utilitypipeline;
	}

	if (leaves->multimedia_info) {
		dt21->multimedia_info = bios + leaves->multimedia_info;
	}

	populate_smc_dpm_info(&(dt21->smc_dpm_info), atree, leaves->smc_dpm_info);

	populate_firmwareinfo(&(dt21->firmwareinfo), atree, leaves->firmwareinfo);

	populate_lcd_info(&(dt21->lcd_info), atree, leaves->lcd_info);

	populate_smu_info(&(dt21->smu_info), atree, leaves->smu_info);

	populate_vram_usagebyfirmware(
		&(dt21->vram_usagebyfirmware), atree, leaves->vram_usagebyfirmware
	);

	populate_gpio_pin_lut(&(dt21->gpio_pin_lut), atree, leaves->gpio_pin_lut);

	populate_gfx_info(&(dt21->gfx_info), atree, leaves->gfx_info);

	populate_ppt(&(dt21->powerplayinfo), atree, leaves->powerplayinfo);

	//displayobjectinfo
	//indirectioaccess
	//umc_info
	//dce_info

	populate_vram_info(&(dt21->vram_info), atree, leaves->vram_info);

	//integratedsysteminfo
	//asic_profiling_info

	populate_voltageobject_info(
		&(dt21->voltageobject_info), atree, leaves->voltageobject_info
	);

	atomtree_datatable_v2_1_populate_sw_datatables(dt21, atree);
}

inline static void
populate_datatables(
		//struct atomtree_master_datatable* const data_table,
		struct atom_tree* const atree,
		uint16_t const bios_offset
		) {
	struct atomtree_master_datatable* const data_table = &(atree->data_table);

	if (bios_offset) {
		data_table->leaves = atree->bios + bios_offset;
		data_table->ver = get_ver(data_table->table_header);
		switch (data_table->ver) {
			case v1_1: populate_master_datatable_v1_1(data_table, atree); break;
			case v2_1: populate_master_datatable_v2_1(data_table, atree); break;
			default: assert(0); break;
		}
	}
}


inline static void
populate_atom_rom_header_v1_1(
		struct atomtree_rom_header* const rom_header,
		struct atom_tree* const atree
		) {
	struct atom_rom_header_v1_1* const leaves = rom_header->v1_1;
	void* const bios = atree->bios;

	if (leaves->ProtectedModeInfoOffset) {
		atree->protected_mode = bios + leaves->ProtectedModeInfoOffset;
	}
	if (leaves->ConfigFilenameOffset) {
		atree->config_filename = bios + leaves->ConfigFilenameOffset;
	}
	if (leaves->CRC_BlockOffset) {
		atree->crc_block = bios + leaves->CRC_BlockOffset;
	}
	if (leaves->BIOS_BootupMessageOffset) {
		atree->bootup_mesage = bios + leaves->BIOS_BootupMessageOffset;
	}
	if (leaves->Int10Offset) {
		atree->int10 = bios + leaves->Int10Offset;
	}
	if (leaves->PCI_InfoOffset) {
		atree->pci_info = bios + leaves->PCI_InfoOffset;
	}

	//rom_header->data_table = &(atree->data_table);
	populate_datatables(atree, leaves->MasterDataTableOffset);
}

inline static void
populate_atom_rom_header_v2_1(
		struct atomtree_rom_header* const rom_header,
		struct atom_tree* const atree
		) {
	struct atom_rom_header_v2_1* const leaves = rom_header->v2_1;
	void* const bios = atree->bios;

	if (leaves->ProtectedModeInfoOffset) {
		atree->protected_mode = bios + leaves->ProtectedModeInfoOffset;
	}
	if (leaves->ConfigFilenameOffset) {
		atree->config_filename = bios + leaves->ConfigFilenameOffset;
	}
	if (leaves->CRC_BlockOffset) {
		atree->crc_block = bios + leaves->CRC_BlockOffset;
	}
	if (leaves->BIOS_BootupMessageOffset) {
		atree->bootup_mesage = bios + leaves->BIOS_BootupMessageOffset;
	}
	if (leaves->Int10Offset) {
		atree->int10 = bios + leaves->Int10Offset;
	}
	if (leaves->PCI_InfoOffset) {
		atree->pci_info = bios + leaves->PCI_InfoOffset;
	}
	if (leaves->PSPDirTableOffset) {
		atree->psp_dir_table = bios + leaves->PSPDirTableOffset;
	}

	//rom_header->data_table = &(atree->data_table);
	populate_datatables(atree, leaves->MasterDataTableOffset);
}

inline static void
populate_atom_rom_header_v2_2(
		struct atomtree_rom_header* const rom_header,
		struct atom_tree* const atree
		) {
	struct atom_rom_header_v2_2* const leaves = rom_header->v2_2;
	void* const bios = atree->bios;

	if (leaves->protectedmodeoffset) {
		atree->protected_mode = bios + leaves->protectedmodeoffset;
	}
	if (leaves->configfilenameoffset) {
		atree->config_filename = bios + leaves->configfilenameoffset;
	}
	if (leaves->crc_block_offset) {
		atree->crc_block = bios + leaves->crc_block_offset;
	}
	if (leaves->vbios_bootupmessageoffset) {
		atree->bootup_mesage = bios + leaves->vbios_bootupmessageoffset;
	}
	if (leaves->int10_offset) {
		atree->int10 = bios + leaves->int10_offset;
	}
	if (leaves->pci_info_offset) {
		atree->pci_info = bios + leaves->pci_info_offset;
	}
	if (leaves->pspdirtableoffset) {
		atree->psp_dir_table = bios + leaves->pspdirtableoffset;
	}

	//rom_header->data_table = &(atree->data_table);
	populate_datatables(atree, leaves->masterdatatable_offset);

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

inline static void
populate_atom_rom_header(
		struct atomtree_rom_header* const rom_header,
		struct atom_tree* const atree,
		uint16_t offset
		) {
	if (offset) {
		rom_header->leaves = atree->bios + offset;
		rom_header->ver = get_ver(rom_header->table_header);
		switch (rom_header->ver) {
			case v1_1: populate_atom_rom_header_v1_1(rom_header, atree); break;
			case v2_1: populate_atom_rom_header_v2_1(rom_header, atree); break;
			case v2_3: // forced
			case v2_2: populate_atom_rom_header_v2_2(rom_header, atree); break;
			default: break;
		}
	}
}

inline static void
populate_pci_tables(
		struct atomtree_pci_tables* const atree_pci,
		struct pci_rom_header* const start
		) {
	union {
		void* raw;
		struct pci_rom_header* header;
		struct efi_pci_device_driver_image* efi;

	} header;
	union {
		void* raw;
		uint32_t* signature;
		struct pcir_data_structure* pcir;
	} pcir;

	header.header = start;
	uint8_t i = 0;
	struct pci_rom_tables* const tables = atree_pci->pci_tables;

	do {
		if (header.header->pci_rom_signature != PCI_HEADER_MAGIC) {
			break;
		}
		pcir.raw = header.raw + header.header->pcir_structure_offset;
		if (*pcir.signature != PCIR_SIGNATURE) {
			break;
		}
		tables[i].header = header.header;
		tables[i].pcir = pcir.pcir;
		tables[i].is_efi = (header.efi->efi_signature == EFI_SIGNATURE);
		i++;
		header.raw += pcir.pcir->image_length_in_512 * BIOS_IMAGE_SIZE_UNIT;
	} while (!pcir.pcir->last.last_image);
	atree_pci->num_images = i;
}

inline static void*
bios_fastforward(
		void const* const biosfile,
		uint32_t const size
		) {
	union {
		void const* bios;
		struct vbios_rom_header const* image;
	} bi;
	bi.bios = biosfile;
	void const* const end = biosfile + size;
	while (bi.bios < end) {
		if ((bi.image->pci_header.pci_rom_signature == ATOM_BIOS_MAGIC)
			&& (0 == strcmp(ATOM_ATI_MAGIC, bi.image->atomati_magic))
			) {
			return (void*)bi.bios;
		}
		bi.bios++;
	}
	return NULL;
}


struct atom_tree*
atombios_parse(
		void* const alloced_bios,
		uint32_t const allocsize
		) {
	void* const bios = bios_fastforward(alloced_bios, allocsize);
	if (bios == NULL) {
		return NULL;
	}
	struct vbios_rom_header* const image = bios;
	struct atom_tree* const atree = calloc(1,sizeof(struct atom_tree));
	// atomtree is highly conditional, so zeroing with calloc will make
	// population easier.

	/*
	setjmp(error.env);
	if (error.severity) {
		free(atree);
		return NULL;
	}
	*/


	atree->alloced_bios = alloced_bios;

	atree->bios = bios; // going to be used as the '0' in places.
	atree->pci_first_image_size = (
		image->pci_header.pci_rom_size_in_512 * BIOS_IMAGE_SIZE_UNIT
	);

	uint8_t num_of_crawled_strings = 0;
	if (image->atom_bios_message_offset) {
		char* strs = atree->bios + image->atom_bios_message_offset;
		do {
			assert(num_of_crawled_strings < NUM_ATOMBIOS_STRINGS); // see def
			atree->atombios_strings[num_of_crawled_strings] = strs;
			num_of_crawled_strings++;
			strs += (strlen(strs) + 1);
		} while (*strs); // the last string ends with 00 00
	}
	atree->num_of_crawled_strings = num_of_crawled_strings;

	populate_pci_tables(&(atree->pci_tables), &(image->pci_header));
	if (atree->pci_tables.num_images) { // if this fails, no PCIR
		atree->chip_type = get_amd_chip_from_pci_id(
			atree->pci_tables.pci_tables[0].pcir->vendor_id,
			atree->pci_tables.pci_tables[0].pcir->device_id
		);
	}

	populate_atom_rom_header(
		&(atree->rom_header), atree, image->rom_header_info_table_offset
	);

	// populate_commandtables(atree); // TODO
	return atree;
}


inline enum atomtree_common_version
get_ver(
		struct atom_common_table_header const* const header
		) {
	return (
		(header->format_revision * VER_MAJOR_MULTIPLIER)
		+ header->content_revision
	);
}
inline void
set_ver(
		enum atomtree_common_version const ver,
		struct atom_common_table_header* const header
		) {
	header->format_revision = ver / VER_MAJOR_MULTIPLIER;
	header->content_revision = ver % VER_MAJOR_MULTIPLIER;
};


void
atomtree_bios_checksum(
		struct atom_tree* const atree
		) {
	uint8_t const* const bios = atree->bios;
	uint32_t const bios_size = atree->pci_first_image_size;
	uint8_t offset = 0;

	for (uint32_t i=0; i < bios_size; i++) {
		offset += bios[i];
	}

	atree->image->checksum -= offset;
}

void
atomtree_destroy(
		struct atom_tree* const atree
		) {
	free(atree->alloced_bios);
	free(atree);
}
