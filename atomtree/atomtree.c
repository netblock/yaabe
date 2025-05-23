/*
AtomBIOS crawler.
see atomtree.h and data_tables.h
*/

#include "standard.h"
#include "atomtree.h"

struct atomtree_commons {
    struct atom_tree*  atree;
    void* bios;
    struct error     error; // error handling; landing is in atombios_parse
    struct mem_arena alloc_arena;
};


inline static void
populate_smc_dpm_info(
		struct atomtree_commons* const commons,
		struct atomtree_smc_dpm_info* const smc_dpm_info,
		uint16_t const bios_offset
		) {
	if (0 == bios_offset) {
		return;
	}

	// leaves is in a union with the structs.
	smc_dpm_info->leaves = commons->bios + bios_offset;
	smc_dpm_info->ver = atom_get_ver(smc_dpm_info->table_header);
}


inline static void
populate_firmwareinfo(
		struct atomtree_commons* const commons,
		struct atomtree_firmware_info* const firmwareinfo,
		uint16_t const bios_offset
		) {
	if (0 == bios_offset) {
		return;
	}

	// leaves is in a union with the structs.
	firmwareinfo->leaves = commons->bios + bios_offset;
	firmwareinfo->ver = atom_get_ver(firmwareinfo->table_header);
}


inline static void
populate_lcd_info_record_table(
		struct atomtree_commons* const commons,
		struct atomtree_lcd_info* const lcd_info,
		void* const record_start
		) {
	if (NULL == record_start) {
		return;
	}
	union {
		void* raw;
		enum lcd_record_type* RecordType;
		union lcd_record* records;
	} r = {
		.raw = record_start
	};
	uint8_t num_records = 0;
	while (LCD_RECORD_END_TYPE != *r.RecordType) {
		switch (*r.RecordType) {
			case LCD_MODE_PATCH_RECORD_MODE_TYPE:
				r.raw += sizeof(r.records->patch_record);
				break;
			case LCD_RTS_RECORD_TYPE:
				r.raw += sizeof(r.records->lcd_rts_record);
				break;
			case LCD_CAP_RECORD_TYPE:
				r.raw += sizeof(r.records->lcd_mode_control_cap);
				break;
			case LCD_FAKE_EDID_PATCH_RECORD_TYPE:
				uint16_t length = (
					r.records->fake_edid_patch_record.FakeEDIDLength
				);
				if (length == 128) { // 128 is 128 (why???)
				} else if (length) { // all other non-zero is * 128
					length *= 128;
				} else {
					length = 1;
				}
				r.raw += sizeof_flex(
					&r.records->fake_edid_patch_record,
					FakeEDIDString, length
				);
				break;
			case LCD_PANEL_RESOLUTION_RECORD_TYPE:
				r.raw += sizeof(r.records->panel_resolution_patch_record);
				break;
			case LCD_EDID_OFFSET_PATCH_RECORD_TYPE: // no idea
			default:
				assert(0);
				goto record_counter_loop_uberbreak;
		}
		num_records++;
	}
	record_counter_loop_uberbreak:

	lcd_info->record_table_size = r.raw - record_start;
	lcd_info->num_records = num_records;

	if (num_records) {
		lcd_info->record_table = arena_alloc(
			&(commons->alloc_arena), &(commons->error),
			num_records * sizeof(lcd_info->record_table[0])
		);

		r.raw = record_start;
		for (uint8_t i = 0; i < num_records; i++) {
			lcd_info->record_table[i].record = r.records;
			switch (*r.RecordType) {
				case LCD_MODE_PATCH_RECORD_MODE_TYPE:
					r.raw += sizeof(r.records->patch_record);
					break;
				case LCD_RTS_RECORD_TYPE:
					r.raw += sizeof(r.records->lcd_rts_record);
					break;
				case LCD_CAP_RECORD_TYPE:
					r.raw += sizeof(r.records->lcd_mode_control_cap);
					break;
				case LCD_FAKE_EDID_PATCH_RECORD_TYPE:
					uint16_t length = (
						r.records->fake_edid_patch_record.FakeEDIDLength
					);
					if (length == 128) { // 128 is 128 (why???)
					} else if (length) { // all other non-zero is * 128
						length *= 128;
					} else {
						length = 1;
					}
					lcd_info->record_table[i].edid_length = length;
					r.raw += sizeof_flex(
						&r.records->fake_edid_patch_record,
						FakeEDIDString, length
					);
					break;
				case LCD_PANEL_RESOLUTION_RECORD_TYPE:
					r.raw += sizeof(r.records->panel_resolution_patch_record);
					break;
				case LCD_EDID_OFFSET_PATCH_RECORD_TYPE: // no idea
				default:
					assert(0);
					break;
			}
		}
	}
}
inline static void
populate_lcd_info(
		struct atomtree_commons* const commons,
		struct atomtree_lcd_info* const lcd_info,
		uint16_t const bios_offset
		) {
	if (0 == bios_offset) {
		return;
	}

	lcd_info->leaves = commons->bios + bios_offset;
	lcd_info->ver = atom_get_ver(lcd_info->table_header);

	void* record_start = NULL;

	switch (lcd_info->ver.ver) {
		case V(1,1):
			if (lcd_info->v1_1->ModePatchTableOffset) {
				// v1_1 uses an absolute position
				record_start = (
					commons->bios + lcd_info->v1_1->ModePatchTableOffset
				);
			}
			break;
		case V(1,2):
			if (lcd_info->v1_2->ExtInfoTableOffset) {
				record_start = (
					lcd_info->leaves + lcd_info->v1_2->ExtInfoTableOffset
				);
			}
			break;
		case V(1,3):
			if (lcd_info->v1_3->ExtInfoTableOffset) {
				record_start = (
					lcd_info->leaves + lcd_info->v1_3->ExtInfoTableOffset
				);
			}
			break;
	}
	populate_lcd_info_record_table(commons, lcd_info, record_start);
}


inline static void
populate_analog_tv_info(
		struct atomtree_commons* const commons,
		struct atomtree_analog_tv_info* const atv,
		uint16_t const bios_offset
		) {
	if (0 == bios_offset) {
		return;
	}

	atv->leaves = commons->bios + bios_offset;
	atv->ver = atom_get_ver(atv->table_header);
}

inline static void
populate_smu_info(
		struct atomtree_commons* const commons,
		struct atomtree_smu_info* const smu_info,
		uint16_t const bios_offset
		) {
	// leaves is in a union with the structs.
	if (0 == bios_offset) {
		return;
	}

	smu_info->leaves = commons->bios + bios_offset;
	smu_info->ver = atom_get_ver(smu_info->table_header);
	switch (smu_info->ver.ver) { // TODO if init,golden are 0, catch them.
		case V(3,2):
			if (smu_info->v3_2->smugoldenoffset) {
				smu_info->smugolden =
					smu_info->leaves + smu_info->v3_2->smugoldenoffset;
			}
			break;
		case V(3,3):
			if (smu_info->v3_3->smugoldenoffset) {
				smu_info->smugolden =
					smu_info->leaves + smu_info->v3_3->smugoldenoffset;
			}
			if (smu_info->v3_3->smuinitoffset) {
				smu_info->smuinit =
					smu_info->leaves + smu_info->v3_3->smuinitoffset;
			}
			break;
		case V(3,4): // bios reports 244 bytes. v3_5 is 240 bytes.
		case V(3,5):
			if (smu_info->v3_5->smugoldenoffset) {
				smu_info->smugolden =
					smu_info->leaves + smu_info->v3_5->smugoldenoffset;
			}
			if (smu_info->v3_5->smuinitoffset) {
				smu_info->smuinit =
					smu_info->leaves + smu_info->v3_5->smuinitoffset;
			}
			break;
		case V(3,6):
			if (smu_info->v3_6->smugoldenoffset) {
				smu_info->smugolden =
					smu_info->leaves + smu_info->v3_6->smugoldenoffset;
			}
			if (smu_info->v3_6->smuinitoffset) {
				smu_info->smuinit =
					smu_info->leaves + smu_info->v3_6->smuinitoffset;
			}
			break;
		case V(4,0):
			if (smu_info->v4_0->smuinitoffset) {
				smu_info->smuinit =
					smu_info->leaves + smu_info->v4_0->smuinitoffset;
			}
			break;
		default:
			break;
	}
}


inline static void
populate_vram_usagebyfirmware(
		struct atomtree_commons* const commons,
		struct atomtree_vram_usagebyfirmware* const fw_vram,
		uint16_t const bios_offset) {
	if (0 == bios_offset) {
		return;
	}

	// leaves is in a union with the structs.
	fw_vram->leaves = commons->bios + bios_offset;
	fw_vram->ver = atom_get_ver(fw_vram->table_header);
}


inline static void
populate_gpio_pin_lut(
		struct atomtree_commons* const commons,
		struct atomtree_gpio_pin_lut* const gpio_pin_lut,
		uint16_t const bios_offset
		) {
	if (0 == bios_offset) {
		return;
	}

	gpio_pin_lut->leaves = commons->bios + bios_offset;
	gpio_pin_lut->ver = atom_get_ver(gpio_pin_lut->table_header);
	switch (gpio_pin_lut->ver.ver) {
		case V(2,1):
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


inline static void
populate_gfx_info(
		struct atomtree_commons* const commons,
		struct atomtree_gfx_info* const gfx_info,
		uint16_t const bios_offset
		) {
	if (0 == bios_offset) {
		return;
	}

	// leaves is in a union with the structs.
	gfx_info->leaves = commons->bios + bios_offset;
	gfx_info->ver = atom_get_ver(gfx_info->table_header);
	switch (gfx_info->ver.ver) {
		case V(2,1):
			break;
		case V(2,3):
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
		case V(2,4):
			if (gfx_info->v2_4->gcgoldenoffset) {
				gfx_info->gcgolden =
					gfx_info->leaves + gfx_info->v2_4->gcgoldenoffset;
			}
			break;
		case V(2,5):
			if (gfx_info->v2_5->gcgoldenoffset) {
				gfx_info->gcgolden =
					gfx_info->leaves + gfx_info->v2_5->gcgoldenoffset;
			}
			break;
		case V(2,6): // force v2.5
			if (gfx_info->v2_6->gcgoldenoffset) {
				gfx_info->gcgolden =
					gfx_info->leaves + gfx_info->v2_6->gcgoldenoffset;
			}
			break;
		case V(2,7):
			if (gfx_info->v2_7->gcgoldenoffset) {
				gfx_info->gcgolden =
					gfx_info->leaves + gfx_info->v2_7->gcgoldenoffset;
			}
			break;
		default:
			break;
	}
}


inline static void
populate_pplib_ppt_state_array(
		struct atomtree_commons* const commons,
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


	// driver gates with the atom ver
	if (V(6,0) > atom_get_ver(&(pplibv1->header)).ver) {
		ppt41->state_array_ver = SET_VER(1);
		ppt41->num_state_array_entries = pplibv1->NumStates;

		if (pplibv1->NumStates) {
			ppt41->state_array = arena_alloc(
				&(commons->alloc_arena), &(commons->error),
				pplibv1->NumStates * sizeof(ppt41->state_array[0])
			);

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
			ppt41->state_array_size = (
				pplibv1->NumStates * pplibv1->StateEntrySize
			);
		}
	} else {
		ppt41->state_array_ver = SET_VER(2);
		ppt41->num_state_array_entries = base->v2.NumEntries;

		if (base->v2.NumEntries) {
			ppt41->state_array = arena_alloc(
				&(commons->alloc_arena), &(commons->error),
				base->v2.NumEntries * sizeof(ppt41->state_array[0])
			);

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
}

inline static void
populate_pplib_ppt_extended_table(
		struct atomtree_powerplay_table_v4_1* const ppt41
		) {
	void* const raw = ppt41->leaves;
	union atom_pplib_extended_headers* const ext = ppt41->extended_header;

	switch (ext->Size) {
		case sizeof(ext->v9): ppt41->extended_header_ver = SET_VER(9); break;
		case sizeof(ext->v8): ppt41->extended_header_ver = SET_VER(8); break;
		case sizeof(ext->v7): ppt41->extended_header_ver = SET_VER(7); break;
		case sizeof(ext->v6): ppt41->extended_header_ver = SET_VER(6); break;
		case sizeof(ext->v5): ppt41->extended_header_ver = SET_VER(5); break;
		case sizeof(ext->v4): ppt41->extended_header_ver = SET_VER(4); break;
		case sizeof(ext->v3): ppt41->extended_header_ver = SET_VER(3); break;
		case sizeof(ext->v2): ppt41->extended_header_ver = SET_VER(2); break;
		case sizeof(ext->v1): ppt41->extended_header_ver = SET_VER(1); break;
		default: assert(0); break;
	}
	switch (ppt41->extended_header_ver.ver) {
		case V(9):
			if (ext->v9.VQBudgetingTableOffset) {
				ppt41->vq_budgeting = raw + ext->v9.VQBudgetingTableOffset;
			}
			fall;
		case V(8):
			if (ext->v9.SclkVddgfxTableOffset) {
				ppt41->vddgfx_sclk = raw + ext->v9.SclkVddgfxTableOffset;
			}
			fall;
		case V(7):
			if (ext->v9.PowerTuneTableOffset) {
				ppt41->powertune = raw + ext->v9.PowerTuneTableOffset;
			}
			fall;
		case V(6):
			if (ext->v9.ACPTableOffset) {
				ppt41->acpclk = raw + ext->v9.ACPTableOffset;
			}
			fall;
		case V(5):
			if (ext->v9.PPMTableOffset) {
				ppt41->ppm = raw + ext->v9.PPMTableOffset;
			}
			fall;
		case V(4):
			if (ext->v9.SAMUTableOffset) {
				ppt41->samu = raw + ext->v9.SAMUTableOffset;
			}
			fall;
		case V(3):
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
		case V(2):
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
		case V(1): break;
		default: assert(0); break;
	}
}

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
	assert(V(1) == ppt41->state_array_ver.ver);
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
}
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
		case CHIP_TOPAZ:
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
		struct atomtree_commons* const commons,
		struct atomtree_powerplay_table_v4_1* const ppt41
		) {
	union {
		void* raw;
		union atom_pplib_powerplaytables* all;
		struct atom_pplib_powerplaytable_v5* v5;
	} const b = {
		.raw = ppt41->leaves
	};
	switch (b.v5->TableSize) {
		case sizeof(b.all->v5): ppt41->pplib_ver = SET_VER(5); break;
		case sizeof(b.all->v4): ppt41->pplib_ver = SET_VER(4); break;
		case sizeof(b.all->v3): ppt41->pplib_ver = SET_VER(3); break;
		case sizeof(b.all->v2): ppt41->pplib_ver = SET_VER(2); break;
		case 0: // R600
		case sizeof(b.all->v1): ppt41->pplib_ver = SET_VER(1); break;
		default: assert(0);
	};
	switch (ppt41->pplib_ver.ver) {
		case V(5):
			if (b.v5->CACLeakageTableOffset) {
				ppt41->cac_leakage = b.raw + b.v5->CACLeakageTableOffset;
			}
			fall;
		case V(4):
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
		case V(3):
			if (b.v5->FanTableOffset) {
				ppt41->fan_table = b.raw + b.v5->FanTableOffset;
			}
			if (b.v5->ExtendedHeaderOffset) {
				ppt41->extended_header = b.raw + b.v5->ExtendedHeaderOffset;
				populate_pplib_ppt_extended_table(ppt41);
			}
			fall;
		case V(2):
			if (b.v5->CustomThermalPolicyArrayOffset) {
				ppt41->thermal_policy = (
					b.raw + b.v5->CustomThermalPolicyArrayOffset
				);
			}
			fall;
		case V(1):
			if (b.v5->StateArrayOffset) {
				ppt41->state_array_base = b.raw + b.v5->StateArrayOffset;
				populate_pplib_ppt_state_array(commons, ppt41);
			}
			if (b.v5->ClockInfoArrayOffset) {
				ppt41->clock_info = b.raw + b.v5->ClockInfoArrayOffset;
				set_pplib_ppt_clock_info(ppt41, commons->atree->chip_type);
			}
			if (b.v5->NonClockInfoArrayOffset) {
				ppt41->nonclock_info = b.raw + b.v5->NonClockInfoArrayOffset;
				
				switch (ppt41->nonclock_info->header.EntrySize) {
					case sizeof(ppt41->nonclock_info->v1.nonClockInfo[0]):
						 ppt41->nonclock_info_ver = SET_VER(1);
						 break;
					case sizeof(ppt41->nonclock_info->v2.nonClockInfo[0]):
						 ppt41->nonclock_info_ver = SET_VER(2);
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
	} const b = {
		.raw = ppt71->leaves
	};
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
	} const b = {
		.raw = ppt81->leaves
	};
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
inline static void
populate_ppt(
		struct atomtree_commons* const commons,
		struct atomtree_powerplay_table* const ppt,
		uint16_t const bios_offset
		) {
	if (0 == bios_offset) {
		return;
	}

	ppt->leaves = commons->bios + bios_offset;
	// leaves is in a union with the structs.
	ppt->ver = atom_get_ver(ppt->table_header);

	switch (ppt->ver.ver) {
		case V(1,1):
		case V(2,1):
		case V(3,1):
			break; // absurdly simple powerplay.
		case V(6,1):
		case V(5,1):
		case V(4,1):
			populate_pplib_ppt(commons, &(ppt->v4_1));
			break;
		case V(7,1): // Tonga, Fiji, Polaris ; pptable and vega10 look similar
			populate_pptablev1_ppt(&(ppt->v7_1));
			break;
		case V(8,1):
			populate_vega10_ppt(&(ppt->v8_1));
			break;
		case V(11,0):
			ppt->v11_0.smc_pptable_ver = SET_VER(
				ppt->v11_0.leaves->smc_pptable.ver
			);
			break;
		case V(14,0):
		case V(12,0):
			ppt->v12_0.smc_pptable_ver = SET_VER(
				ppt->v12_0.leaves->smc_pptable.ver
			);
			break;
		case V(19,0): // 6400
		case V(18,0): // navi2 xx50
		case V(16,0): // 6700XT
		case V(15,0):
			ppt->v15_0.smc_pptable_ver = SET_VER(
				ppt->v15_0.leaves->smc_pptable.ver
			);
			break;
		default:
			assert(0);
			break;
	}
}


static void
populate_display_object_records(
		struct atomtree_commons* const commons,
		struct atomtree_display_path_record_set* const set,
		void* const start
		) {
	union {
		void* raw;
		 union display_records* records;
	} r = {
		.records = start
	};

	while (ATOM_RECORD_END_TYPE != r.records->header.record_type) {
		set->num_records++;
		r.raw += r.records->header.record_size;
		assert(255 > set->num_records);
	}
	set->records_size = r.raw - start;
	if (0 == set->num_records) {
		return;
	}

	set->records = arena_alloc(
		&(commons->alloc_arena), &(commons->error),
		set->num_records * sizeof(set->records[0])
	);
	r.records = start;
	for (uint8_t i=0; i < set->num_records; i++) {
		set->records[i] = r.records;
		r.raw += r.records->header.record_size;
	}
}
static void
populate_atom_object_table(
		struct atomtree_commons* const commons,
		struct atomtree_object_table* const table,
		void* const bios,
		uint16_t const offset
		) {
	struct atom_object_table* const header = bios + offset;
	table->table = header;
	uint8_t const num_objects = header->NumberOfObjects;
	struct atomtree_object_table_tables* const objects = arena_alloc(
		&(commons->alloc_arena), &(commons->error),
		num_objects * sizeof(objects[0])
	);
	table->objects = objects;

	for (uint8_t i=0; i < num_objects; i++) {
		if (header->Objects[i].SrcDstTableOffset) {
			void* srcdst = bios + header->Objects[i].SrcDstTableOffset;
			objects[i].src = srcdst;
			objects[i].dst = srcdst + sizeof_flex(
				objects[i].src, object_id, objects[i].src->num_of_objs
			);
		}
		if (header->Objects[i].RecordOffset) {
			populate_display_object_records(
				commons, &(objects[i].records),
				bios + header->Objects[i].RecordOffset
			);
		}
	}
}
inline static void
populate_display_object_path_table(
		struct atomtree_commons* const commons,
		struct atomtree_object_path* const table,
		void* const bios,
		uint16_t const offset
		) {
	struct atom_display_object_path_table* const header = bios + offset;
	table->header = header;
	uint8_t const num_paths = header->NumOfDispPath;

	if (0 == num_paths) {
		return;
	}
	struct atomtree_object_path_entry* const paths = arena_alloc(
		&(commons->alloc_arena), &(commons->error),
		num_paths * sizeof(paths[0])
	);
	table->paths = paths;

	void* pos = header->DispPath;

	for (uint8_t i=0; i < num_paths; i++) {
		paths[i].path = pos;
		paths[i].num_graphic_ids = (
			(paths[i].path->Size - sizeof(*(paths[i].path)))
			/ sizeof(paths[i].path->GraphicObjIds[0])
		);
		pos += paths[i].path->Size;
	}
	table->total_size = pos - (void*) header;
}
inline static void
populate_atom_object_header(
		struct atomtree_commons* const commons,
		struct atomtree_display_object* const disp
		) {
	// v1.1 .. 1.3
	void* bios; // 1.1 is absolute; 1.2<= is relative
	if (1 == disp->ver.minor) {
		bios = commons->bios;
	} else {
		bios = disp->leaves;
	}
	if (disp->v1_1->ConnectorObjectTableOffset) {
		populate_atom_object_table(commons, &(disp->connector),
			bios, disp->v1_1->ConnectorObjectTableOffset
		);
	}
	if (disp->v1_1->RouterObjectTableOffset) {
		populate_atom_object_table(commons, &(disp->router),
			bios, disp->v1_1->RouterObjectTableOffset
		);
	}
	if (disp->v1_1->EncoderObjectTableOffset) {
		populate_atom_object_table(commons, &(disp->encoder),
			bios, disp->v1_1->EncoderObjectTableOffset
		);
	}
	if (disp->v1_1->ProtectionObjectTableOffset) {
		populate_atom_object_table(commons, &(disp->protection),
			bios, disp->v1_1->ProtectionObjectTableOffset
		);
	}
	if (disp->v1_1->DisplayPathTableOffset) {
		populate_display_object_path_table(commons, &(disp->path),
			bios, disp->v1_1->DisplayPathTableOffset
		);
	}
	if ((3 == disp->ver.minor) && disp->v1_3->MiscObjectTableOffset) {
		populate_atom_object_table(commons, &(disp->misc),
			bios, disp->v1_3->MiscObjectTableOffset
		);
	}
}
inline static void
populate_display_object_info_table(
		struct atomtree_commons* const commons,
		struct atomtree_display_object* const disp
		) {
	// v1.4, 1.5
	void* const leaves = disp->leaves;
	uint8_t const number_of_path = disp->v1_4->number_of_path;
	struct atomtree_display_path_records* const records = arena_alloc(
		&(commons->alloc_arena), &(commons->error),
		number_of_path * sizeof(disp->records[0])
	);
	disp->records = records;

	if (V(1,4) == disp->ver.ver) {
		struct atom_display_object_path_v2 const* const path = (
			disp->v1_4->display_path
		);
		for (uint8_t i=0; i < number_of_path; i++) {
			if (path[i].disp_recordoffset) {
				populate_display_object_records(
					commons, &(records[i].connector),
					leaves + path[i].disp_recordoffset
				);
			}
			if (path[i].encoder_recordoffset) {
				populate_display_object_records(
					commons, &(records[i].encoder),
					leaves + path[i].encoder_recordoffset
				);
			}
			if (path[i].extencoder_recordoffset) {
				populate_display_object_records(
					commons, &(records[i].extern_encoder),
					leaves + path[i].extencoder_recordoffset
				);
			}
		}
	} else {
		struct atom_display_object_path_v3 const* const path = (
			disp->v1_5->display_path
		);
		for (uint8_t i=0; i < number_of_path; i++) {
			if (path[i].disp_recordoffset) {
				populate_display_object_records(
					commons, &(records[i].connector),
					leaves + path[i].disp_recordoffset
				);
			}
		}
	}
}

inline static void
populate_display_object(
		struct atomtree_commons* const commons,
		struct atomtree_display_object* const disp,
		uint16_t const bios_offset
		) {
	if (0 == bios_offset) {
		return;
	}
	disp->leaves = commons->bios + bios_offset;
	disp->ver = atom_get_ver(disp->table_header);
	switch (disp->ver.ver) {
		case V(1,1):
		case V(1,2):
		case V(1,3): populate_atom_object_header(commons, disp); break;
		case V(1,4): 
		case V(1,5): populate_display_object_info_table(commons, disp); break;
	}
}


static void
populate_init_reg_block(
		struct atomtree_commons* const commons,
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

	union {
		struct atom_reg_setting_data_block* walker;
		void* raw;
	} w;
	struct atom_reg_setting_data_block* const block_start = (
		(void*)leaves->RegIndexBuf + leaves->RegIndexTblSize
	);
	w.walker = block_start;
	while (w.walker->block_id.id_access) { // the datablock list ends with 0
		at_regblock->num_data_blocks++;
		w.raw += at_regblock->data_block_element_size;
	}

	if (at_regblock->num_data_blocks) {
		at_regblock->data_blocks = arena_alloc(
			&(commons->alloc_arena), &(commons->error),
			at_regblock->num_data_blocks * sizeof(at_regblock->data_blocks[0])
		);
		w.walker = block_start;
		uint8_t i = 0;
		while (i < at_regblock->num_data_blocks) {
			at_regblock->data_blocks[i] = w.walker;
			w.raw += at_regblock->data_block_element_size;
			i++;
		}
		at_regblock->data_block_table_size = (
			at_regblock->data_block_element_size * at_regblock->num_data_blocks
		);
	}

	at_regblock->index_table_size = leaves->RegIndexTblSize;
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
	switch (vram_module->vram_module_ver.ver) {
		case V(1,1):  return vram_module->v1_1->MemoryType;
		case V(1,2):  return vram_module->v1_2->MemoryType;
		case V(1,3):  return vram_module->v1_3->MemoryType;
		case V(1,4):  return vram_module->v1_4->MemoryType;
		case V(1,5):  return vram_module->v1_5->MemoryType;
		case V(1,6):  return vram_module->v1_6->MemoryType;
		case V(1,7):  return vram_module->v1_7->MemoryType;
		case V(1,8):  return vram_module->v1_8->MemoryType;
		case V(1,9):  return vram_module->v1_9->memory_type;
		case V(1,10): return vram_module->v1_10->memory_type;
		case V(1,11): return vram_module->v1_11->memory_type;
		case V(3,0):
		default: assert(0);
	}
	return ATOM_DGPU_VRAM_TYPE_NONE;
}

static void
populate_mem_adjust_table(
		struct atomtree_commons* const commons,
		struct atomtree_init_reg_block* const mem_adjust_table,
		struct atomtree_vram_module const* const vram_modules __unused
		) {
	populate_init_reg_block(commons, mem_adjust_table);
	mem_adjust_table->reg_type = REG_BLOCK_MEM_ADJUST;

	/*
	enum atom_dgpu_vram_type const vram_type = get_vram_type(&vram_modules[0]);
	struct atom_init_reg_index_format const* const index =
		mem_adjust_table->register_index;

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
		struct atomtree_commons* const commons,
		struct atomtree_init_reg_block* const mem_clk_patch,
		struct atomtree_vram_module const* const vram_modules
		) {
	populate_init_reg_block(commons, mem_clk_patch);
	mem_clk_patch->reg_type = REG_BLOCK_MEM_CLK_PATCH;

	enum atom_dgpu_vram_type const vram_type = get_vram_type(&vram_modules[0]);
	struct atom_init_reg_index_format const* const index =
		mem_clk_patch->register_index;

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
		struct atomtree_commons* const commons,
		struct atomtree_init_reg_block* const mc_tile_adjust,
		struct atomtree_vram_module const* const vram_modules __unused
		) {
	populate_init_reg_block(commons, mc_tile_adjust);
	mc_tile_adjust->reg_type = REG_BLOCK_MC_TILE_ADJUST;

	/*
	enum atom_dgpu_vram_type const vram_type = get_vram_type(&vram_modules[0]);

	struct atom_init_reg_index_format const* const index =
		mc_tile_adjust->register_index;

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
		struct atomtree_commons* const commons,
		struct atomtree_init_reg_block* const mc_phy_init,
		struct atomtree_vram_module const* const vram_modules __unused
		) {
	populate_init_reg_block(commons, mc_phy_init);
	mc_phy_init->reg_type = REG_BLOCK_MC_PHY_INIT;

	/*
	enum atom_dgpu_vram_type const vram_type = get_vram_type(&vram_modules[0]);
	struct atom_init_reg_index_format const* const index =
		mc_phy_init->register_index;

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
		struct atomtree_commons* const commons,
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
	union {
		struct atom_umc_reg_setting_data_block* walker;
		void* raw;
	} w;
	struct atom_umc_reg_setting_data_block* const block_start = (
		(void*)leaves->umc_reg_list
		+ (sizeof(union atom_umc_register_addr_info_access)
			* leaves->umc_reg_num
		) // size of umc_reg_list
	);
	w.walker = block_start;
	while (w.walker->block_id.id_access) { // the datablock list ends with 0
		at_regblock->num_data_blocks++;
		w.raw += at_regblock->data_block_element_size;
	}

	if (at_regblock->num_data_blocks) {
		at_regblock->data_blocks = arena_alloc(
			&(commons->alloc_arena), &(commons->error),
			at_regblock->num_data_blocks * sizeof(at_regblock->data_blocks[0])
		);
		w.walker = block_start;
		uint8_t i = 0;
		while (i < at_regblock->num_data_blocks) {
			at_regblock->data_blocks[i] = w.walker;
			w.raw += at_regblock->data_block_element_size;
			i++;
		}
		at_regblock->data_block_table_size = (
			at_regblock->data_block_element_size * at_regblock->num_data_blocks
		);
	}

	at_regblock->info_table_size = (
		at_regblock->num_info * sizeof(union atom_umc_register_addr_info_access)
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
			vram_module->memory_timing_format_ver = SET_VER(1,1);
			table_size = sizeof(timings->v1_1);
		} else {
			assert(0xFF == timings->v1_2.Terminator);
			vram_module->memory_timing_format_ver = SET_VER(1,2);
			table_size = sizeof(timings->v1_2);
		}
	} else {
		vram_module->memory_timing_format_ver = SET_VER(1,0);
		table_size = sizeof(timings->v1_0);
	}
	vram_module->num_memory_timing_format = straps_total_size / table_size;
	vram_module->memory_timing_format_total_size = straps_total_size;
}


inline static struct atomtree_vram_module*
populate_vram_module(
		struct atomtree_commons* const commons,
		void* bios_offset,
		semver const vram_modules_ver,
		uint8_t const count
		) {
	if (0 == count) {
		return NULL;
	}

	struct atomtree_vram_module* const vram_modules = arena_alloc(
		&(commons->alloc_arena), &(commons->error),
		count * sizeof(vram_modules[0])
	);
	struct atomtree_vram_module* vmod;
	switch (vram_modules_ver.ver) {
		case V(1,3): // atom_vram_module_v3. Will look very similar to v4
			for (uint8_t i=0; i < count; i++) {
				vmod = &(vram_modules[i]);
				vmod->leaves = bios_offset;
				vmod->vram_module_ver = SET_VER(1,3);
				vmod->gmc_bitfields_ver = SET_VER(0); // TODO
				bios_offset += vmod->v1_3->ModuleSize;

				populate_atom_memory_timing_format(
					vmod, vmod->v1_3->MemoryType, vmod->v1_3->MemTiming,
					(vmod->v1_3->ModuleSize
						- offsetof(typeof(*vmod->v1_3), MemTiming)
					)
				);
			}
			break;

		case V(1,4): // atom_vram_module_v4. Will look very similar to v3
			for (uint8_t i=0; i < count; i++) {
				vmod = &(vram_modules[i]);
				vmod->leaves = bios_offset;
				vmod->vram_module_ver = SET_VER(1,4);
				vmod->gmc_bitfields_ver = SET_VER(0); // TODO
				bios_offset += vmod->v1_4->ModuleSize;

				populate_atom_memory_timing_format(
					vmod, vmod->v1_4->MemoryType, vmod->v1_4->MemTiming,
					(vmod->v1_4->ModuleSize
						- offsetof(typeof(*vmod->v1_4), MemTiming)
					)
				);

			}
			break;

		case V(1,7):
			semver gmc_bitfields_ver;
			if (count) {
				struct atom_vram_module_v7 const* const zero = bios_offset;
				if (zero->ChannelMapCfg >> 24) { // infer
					// TODO explicit way to find GMC?
					// does it follow vram_module ver? doesn't seem so
					gmc_bitfields_ver = SET_VER(7,1);
				} else {
					gmc_bitfields_ver = SET_VER(6,0);
				}
			}

			for (uint8_t i=0; i < count; i++) {
				vmod = &(vram_modules[i]);
				vmod->leaves = bios_offset;
				vmod->vram_module_ver = SET_VER(1,7);
				vmod->gmc_bitfields_ver = gmc_bitfields_ver;
				bios_offset += vmod->v1_7->ModuleSize;
			}
			break;
		case V(1,8):
			for (uint8_t i=0; i < count; i++) {
				vmod = &(vram_modules[i]);
				vmod->leaves = bios_offset;
				vmod->vram_module_ver = SET_VER(1,8);
				vmod->gmc_bitfields_ver = SET_VER(0); // TODO
				bios_offset += vmod->v1_8->ModuleSize;
			}
			break;

		case V(1,9):
			for (uint8_t i=0; i < count; i++) {
				vmod = &(vram_modules[i]);
				vmod->leaves = bios_offset;
				vmod->vram_module_ver = SET_VER(1,9);
				vmod->gmc_bitfields_ver = SET_VER(0); // TODO
				bios_offset += vmod->v1_9->vram_module_size;
			}
			break;

		case V(1,10):
			for (uint8_t i=0; i < count; i++) {
				vmod = &(vram_modules[i]);
				vmod->leaves = bios_offset;
				vmod->vram_module_ver = SET_VER(1,10);
				vmod->gmc_bitfields_ver = SET_VER(0); // TODO
				bios_offset += vmod->v1_10->vram_module_size;
			}
			break;

		case V(1,11):
			for (uint8_t i=0; i < count; i++) {
				vmod = &(vram_modules[i]);
				vmod->leaves = bios_offset;
				vmod->vram_module_ver = SET_VER(1,11);
				vmod->gmc_bitfields_ver = SET_VER(0); // TODO
				bios_offset += vmod->v1_11->vram_module_size;
			}
			break;

		case V(3,0):
			for (uint8_t i=0; i < count; i++) {
				vmod = &(vram_modules[i]);
				vmod->leaves = bios_offset;
				vmod->vram_module_ver = SET_VER(3,0);
				vmod->gmc_bitfields_ver = SET_VER(0); // TODO
				//bios_offset += vmod->v3_0->vram_module_size;
				bios_offset += sizeof(*vmod->v3_0);

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
	return vram_modules;
}


inline static void
populate_gddr6_dram_data_remap(
		struct atomtree_gddr6_dram_data_remap* const at_remap,
		void* const remap_ptr
		) {
	struct atom_gddr6_dram_data_remap const* const dram_data_remap = remap_ptr;
	at_remap->dram_data_remap = remap_ptr;
	at_remap->bit_byte_remap_count = (
		(dram_data_remap->table_size - sizeof(*dram_data_remap))
		/ sizeof(dram_data_remap->bit_byte_remap[0])
	);
}

inline static void
populate_vram_info_v1_2(
		struct atomtree_commons* const commons,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_v1_2* const vi12 = &(vram_info->v1_2);

	if (vi12->leaves->NumOfVRAMModule) {
		vi12->vram_module_ver = SET_VER(1,3);
		vi12->vram_modules = populate_vram_module(
			commons,
			vi12->leaves->vram_module,
			vi12->vram_module_ver,
			vi12->leaves->NumOfVRAMModule
		);
	}
}

inline static void
populate_vram_info_v1_3(
		struct atomtree_commons* const commons,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_v1_3* const vi13 = &(vram_info->v1_3);

	if (vi13->leaves->NumOfVRAMModule) {
		vi13->vram_module_ver = SET_VER(1,3);
		vi13->vram_modules = populate_vram_module(
			commons,
			vi13->leaves->vram_module,
			vi13->vram_module_ver,
			vi13->leaves->NumOfVRAMModule
		);
	}

	if (vi13->leaves->MemAdjustTblOffset) {
		vi13->mem_adjust_table.leaves =
			(void*)vi13->leaves + vi13->leaves->MemAdjustTblOffset;
		populate_init_reg_block(commons, &(vi13->mem_adjust_table));
	}

	if (vi13->leaves->MemClkPatchTblOffset) {
		// TODO at least for R600, what is in here isn't timings, and gmc.h
		// doesn't decode them right.
		vi13->mem_clk_patch.leaves =
			(void*)vi13->leaves + vi13->leaves->MemClkPatchTblOffset;
		populate_init_reg_block(commons, &(vi13->mem_clk_patch));
	}
}

inline static void
populate_vram_info_v1_4(
		struct atomtree_commons* const commons,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_v1_4* const vi14 = &(vram_info->v1_4);

	if (vi14->leaves->NumOfVRAMModule) {
		vi14->vram_module_ver = SET_VER(1,4);
		vi14->vram_modules = populate_vram_module(
			commons,
			vi14->leaves->vram_module,
			vi14->vram_module_ver,
			vi14->leaves->NumOfVRAMModule
		);
	}

	if (vi14->leaves->MemAdjustTblOffset) {
		vi14->mem_adjust_table.leaves =
			(void*)vi14->leaves + vi14->leaves->MemAdjustTblOffset;
		populate_init_reg_block(commons, &(vi14->mem_adjust_table));
	}

	if (vi14->leaves->MemClkPatchTblOffset) {
		// TODO See populate_vram_info_v1_3
		vi14->mem_clk_patch.leaves =
			(void*)vi14->leaves + vi14->leaves->MemClkPatchTblOffset;
		populate_init_reg_block(commons, &(vi14->mem_clk_patch));
	}
}

inline static void
populate_vram_info_v2_1(
		struct atomtree_commons* const commons,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_1* const vi21 = &(vram_info->v2_1);

	if (vi21->leaves->NumOfVRAMModule) {
		vi21->vram_module_ver = SET_VER(1,7);
		vi21->vram_modules = populate_vram_module(
			commons,
			vi21->leaves->vram_module,
			vi21->vram_module_ver,
			vi21->leaves->NumOfVRAMModule
		);
	}

	if (vi21->leaves->MemAdjustTblOffset) {
		vi21->mem_adjust_table.leaves =
			(void*)vi21->leaves + vi21->leaves->MemAdjustTblOffset;
		populate_mem_adjust_table(
			commons, &(vi21->mem_adjust_table), vi21->vram_modules
		);
	}

	if (vi21->leaves->MemClkPatchTblOffset) {
		vi21->mem_clk_patch.leaves =
			(void*)vi21->leaves + vi21->leaves->MemClkPatchTblOffset;
		populate_mem_clk_patch(
			commons, &(vi21->mem_clk_patch), vi21->vram_modules
		);
	}

	if (vi21->leaves->PerBytePresetOffset) {
		// TODO unsure what lies beyond; never seen this true.
		vi21->per_byte_preset.leaves =
			(void*)vi21->leaves + vi21->leaves->PerBytePresetOffset;
		populate_init_reg_block(commons, &(vi21->per_byte_preset));
	}
}

inline static void
populate_vram_info_v2_2(
		struct atomtree_commons* const commons,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_2* const vi22 = &(vram_info->v2_2);

	if (vi22->leaves->NumOfVRAMModule) {
		vi22->vram_module_ver = SET_VER(1,8);
		vi22->vram_modules = populate_vram_module(
			commons,
			vi22->leaves->vram_module,
			vi22->vram_module_ver,
			vi22->leaves->NumOfVRAMModule
		);
	}

	if (vi22->leaves->MemAdjustTblOffset) {
		vi22->mem_adjust_table.leaves =
			(void*)vi22->leaves + vi22->leaves->MemAdjustTblOffset;
		populate_mem_adjust_table(
			commons, &(vi22->mem_adjust_table), vi22->vram_modules
		);
	}

	if (vi22->leaves->MemClkPatchTblOffset) {
		vi22->mem_clk_patch.leaves =
			(void*)vi22->leaves + vi22->leaves->MemClkPatchTblOffset;
		populate_mem_clk_patch(
			commons, &(vi22->mem_clk_patch), vi22->vram_modules
		);
	}

	if (vi22->leaves->McAdjustPerTileTblOffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi22->mc_tile_adjust.leaves =
			(void*)vi22->leaves + vi22->leaves->McAdjustPerTileTblOffset;
		populate_mc_tile_adjust(
			commons, &(vi22->mc_tile_adjust), vi22->vram_modules
		);
	}

	if (vi22->leaves->McPhyInitTableOffset) {
		vi22->mc_phy_init.leaves =
			(void*)vi22->leaves + vi22->leaves->McPhyInitTableOffset;
		populate_init_mc_phy_init(
			commons, &(vi22->mc_phy_init), vi22->vram_modules
		);
	}

	if (vi22->leaves->DramDataRemapTblOffset) {
		vi22->dram_data_remap =
			(void*)vi22->leaves + vi22->leaves->DramDataRemapTblOffset;
	}
}

inline static void
populate_vram_info_v2_3(
		struct atomtree_commons* const commons,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_3* const vi23 = &(vram_info->v2_3);

	if (vi23->leaves->vram_module_num) {
		vi23->vram_module_ver = SET_VER(1,9);
		vi23->vram_modules = populate_vram_module(
			commons,
			vi23->leaves->vram_module,
			vi23->vram_module_ver,
			vi23->leaves->vram_module_num
		);
	}

	if (vi23->leaves->mem_adjust_tbloffset) {
		vi23->mem_adjust_table.leaves =
			(void*)vi23->leaves + vi23->leaves->mem_adjust_tbloffset;
		populate_umc_init_reg_block(commons, &(vi23->mem_adjust_table));
	}

	if (vi23->leaves->mem_clk_patch_tbloffset) {
		vi23->mem_clk_patch.leaves =
			(void*)vi23->leaves + vi23->leaves->mem_clk_patch_tbloffset;
		populate_umc_init_reg_block(commons, &(vi23->mem_clk_patch));

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
		populate_umc_init_reg_block(commons, &(vi23->mc_tile_adjust));
	}

	if (vi23->leaves->mc_phyinit_tbloffset) {
		vi23->mc_phy_init.leaves =
			(void*)vi23->leaves + vi23->leaves->mc_phyinit_tbloffset;
		populate_umc_init_reg_block(commons, &(vi23->mc_phy_init));
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
		populate_umc_init_reg_block(commons, &(vi23->post_ucode_init));
	}
}

inline static void
populate_vram_info_v2_4(
		struct atomtree_commons* const commons,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_4* const vi24 = &(vram_info->v2_4);
	struct atom_vram_info_header_v2_4* const leaves = vram_info->leaves;

	if (leaves->vram_module_num) {
		vi24->vram_module_ver = SET_VER(1,10);
		vi24->vram_modules = populate_vram_module(
			commons,
			leaves->vram_module,
			vi24->vram_module_ver,
			leaves->vram_module_num
		);
	}

	if (leaves->mem_adjust_tbloffset) {
		vi24->mem_adjust_table.leaves =
			(void*)leaves + leaves->mem_adjust_tbloffset;
		populate_umc_init_reg_block(commons, &(vi24->mem_adjust_table));
	}

	if (leaves->mem_clk_patch_tbloffset) {
		vi24->mem_clk_patch.leaves =
			(void*)leaves + leaves->mem_clk_patch_tbloffset;
		populate_umc_init_reg_block(commons, &(vi24->mem_clk_patch));

		vi24->num_timing_straps = &(vi24->mem_clk_patch.num_data_blocks);
		vi24->navi1_gddr6_timings =
			(struct timings_set_navi1*) vi24->mem_clk_patch.data_blocks[0];
	}

	if (leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi24->mc_tile_adjust.leaves =
			(void*)leaves + leaves->mc_adjust_pertile_tbloffset;
		populate_umc_init_reg_block(commons, &(vi24->mc_tile_adjust));
	}

	if (leaves->mc_phyinit_tbloffset) {
		vi24->mc_phy_init.leaves =
			(void*)leaves + leaves->mc_phyinit_tbloffset;
		populate_umc_init_reg_block(commons, &(vi24->mc_phy_init));
	}

	if (leaves->dram_data_remap_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi24->dram_data_remap =
			(void*)leaves + leaves->dram_data_remap_tbloffset;
	}

	if (leaves->post_ucode_init_offset) {
		vi24->post_ucode_init.leaves =
			(void*)leaves + leaves->post_ucode_init_offset;
		populate_umc_init_reg_block(commons, &(vi24->post_ucode_init));
	}
}

inline static void
populate_vram_info_v2_5(
		struct atomtree_commons* const commons,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_5* const vi25 = &(vram_info->v2_5);
	struct atom_vram_info_header_v2_5* const leaves = vram_info->leaves;

	if (leaves->vram_module_num) {
		vi25->vram_module_ver = SET_VER(1,11);
		vi25->vram_modules = populate_vram_module(
			commons,
			leaves->vram_module,
			vi25->vram_module_ver,
			leaves->vram_module_num
		);
	}

	if (leaves->mem_adjust_tbloffset) {
		vi25->mem_adjust_table.leaves =
			(void*)leaves + leaves->mem_adjust_tbloffset;
		populate_umc_init_reg_block(commons, &(vi25->mem_adjust_table));
	}

	if (leaves->gddr6_ac_timing_offset) {
		vi25->gddr6_ac_timings =
			(void*)leaves + leaves->gddr6_ac_timing_offset;
		uint8_t i = 0;
		for (; vi25->gddr6_ac_timings[i].block_id.id_access; i++);
		vi25->gddr6_acstrap_count = i;
	}

	if (leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi25->mc_tile_adjust.leaves =
			(void*)leaves + leaves->mc_adjust_pertile_tbloffset;
		populate_umc_init_reg_block(commons, &(vi25->mc_tile_adjust));
	}

	if (leaves->mc_phyinit_tbloffset) {
		vi25->mc_phy_init.leaves =
			(void*)leaves + leaves->mc_phyinit_tbloffset;
		populate_umc_init_reg_block(commons, &(vi25->mc_phy_init));
	}

	if (leaves->dram_data_remap_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		populate_gddr6_dram_data_remap(
			&vi25->dram_data_remap,
			(void*)leaves + leaves->dram_data_remap_tbloffset
		);
	}

	if (leaves->post_ucode_init_offset) {
		vi25->post_ucode_init.leaves =
			(void*)leaves + leaves->post_ucode_init_offset;
		populate_umc_init_reg_block(commons, &(vi25->post_ucode_init));
	}

	if (leaves->strobe_mode_patch_tbloffset) {
		vi25->strobe_mode_patch.leaves =
			(void*)leaves + leaves->strobe_mode_patch_tbloffset;
		populate_umc_init_reg_block(commons, &(vi25->strobe_mode_patch));
	}
}

inline static void
populate_vram_info_v2_6(
		struct atomtree_commons* const commons,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_6* const vi26 = &(vram_info->v2_6);
	struct atom_vram_info_header_v2_6* const leaves = vram_info->leaves;

	if (leaves->vram_module_num) {
		vi26->vram_module_ver = SET_VER(1,9);
		vi26->vram_modules = populate_vram_module(
			commons,
			leaves->vram_module,
			vi26->vram_module_ver,
			leaves->vram_module_num
		);
	}

	if (leaves->mem_adjust_tbloffset) {
		vi26->mem_adjust_table.leaves =
			(void*)leaves + leaves->mem_adjust_tbloffset;
		populate_umc_init_reg_block(commons, &(vi26->mem_adjust_table));
	}

	if (leaves->mem_clk_patch_tbloffset) {
		vi26->mem_clk_patch.leaves =
			(void*)leaves + leaves->mem_clk_patch_tbloffset;
		populate_umc_init_reg_block(commons, &(vi26->mem_clk_patch));
	}

	if (leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi26->mc_tile_adjust.leaves =
			(void*)leaves + leaves->mc_adjust_pertile_tbloffset;
		populate_umc_init_reg_block(commons, &(vi26->mc_tile_adjust));
	}

	if (leaves->mc_phyinit_tbloffset) {
		vi26->mc_phy_init.leaves =
			(void*)leaves + leaves->mc_phyinit_tbloffset;
		populate_umc_init_reg_block(commons, &(vi26->mc_phy_init));
	}

	if (leaves->tmrs_seq_offset) {
		// TODO what is this?
		vi26->tmrs_seq = (void*)leaves + leaves->tmrs_seq_offset;
	}

	if (leaves->dram_data_remap_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		populate_gddr6_dram_data_remap(
			&vi26->dram_data_remap,
			(void*)leaves + leaves->dram_data_remap_tbloffset
		);
	}

	if (leaves->post_ucode_init_offset) {
		vi26->post_ucode_init.leaves =
			(void*)leaves + leaves->post_ucode_init_offset;
		populate_umc_init_reg_block(commons, &(vi26->post_ucode_init));
	}
}

inline static void
populate_vram_info_v3_0( // TODO finish this
		struct atomtree_commons* const commons,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v3_0* const vi30 = &(vram_info->v3_0);
	struct atom_vram_info_header_v3_0* const leaves = vram_info->leaves;

	if (leaves->vram_module_num) {
		vi30->vram_module_ver = SET_VER(3,0);
		vi30->vram_modules = populate_vram_module(
			commons,
			leaves->vram_module,
			vi30->vram_module_ver,
			leaves->vram_module_num
		);
	}

	if (leaves->mem_tuning_table_offset) {
		vi30->mem_tuning =
			(void*)leaves + leaves->mem_tuning_table_offset;
	}

	if (leaves->dram_info_table_offset) {
		vi30->dram_info =
			(void*)leaves + leaves->dram_info_table_offset;
	}

	if (leaves->tmrs_table_offset) {
		vi30->tmrs_seq = (void*)leaves + leaves->tmrs_table_offset;
	}

	if (leaves->mc_init_table_offset) {
		vi30->mc_init.leaves =
			(void*)leaves + leaves->mc_init_table_offset;
		populate_umc_init_reg_block(commons, &(vi30->mc_init));
	}

	if (leaves->dram_data_remap_table_offset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		populate_gddr6_dram_data_remap(
			&vi30->dram_data_remap,
			(void*)leaves + leaves->dram_data_remap_table_offset
		);
	}

	if (leaves->umc_emuinit_table_offset) {
		vi30->umc_emuinit.leaves =
			(void*)leaves + leaves->umc_emuinit_table_offset;
		populate_umc_init_reg_block(commons, &(vi30->umc_emuinit));
	}

	if (leaves->reserved_sub_table_offset[0]) {
		vi30->rsvd_tables[0] =
			(void*)leaves + leaves->reserved_sub_table_offset[0];
	}
	if (leaves->reserved_sub_table_offset[1]) {
		vi30->rsvd_tables[1] =
			(void*)leaves + leaves->reserved_sub_table_offset[1];
	}
}

inline static void
populate_vram_info(
		struct atomtree_commons* const commons,
		struct atomtree_vram_info* const vram_info,
		uint16_t const bios_offset
		) {
	if (0 == bios_offset) {
		return;
	}

	vram_info->leaves = commons->bios + bios_offset;
	vram_info->ver = atom_get_ver(vram_info->table_header);
	switch (vram_info->ver.ver) { // TODO: earlier tables than 2.3?
		case V(1,2): populate_vram_info_v1_2(commons, vram_info); break;
		case V(1,3): populate_vram_info_v1_3(commons, vram_info); break;
		case V(1,4): populate_vram_info_v1_4(commons, vram_info); break;
		case V(2,1): populate_vram_info_v2_1(commons, vram_info); break;
		case V(2,2): populate_vram_info_v2_2(commons, vram_info); break;
		case V(2,3): populate_vram_info_v2_3(commons, vram_info); break;
		case V(2,4): populate_vram_info_v2_4(commons, vram_info); break;
		case V(2,5): populate_vram_info_v2_5(commons, vram_info); break;
		case V(2,6): populate_vram_info_v2_6(commons, vram_info); break;
		case V(3,0): populate_vram_info_v3_0(commons, vram_info); break;
		default: break;
	}
}

inline static void
populate_voltageobject_info_v1_1(
		struct atomtree_commons* const commons,
		struct atomtree_voltageobject_info* const vo_info
		) {
	// get the size ofthe dynamically-sized voltage object array, and walk
	// through the array based on what each element reports their size as.
	union {
		void* raw;
		union atom_voltage_object_all* vobj;
	} vobj;
	void const* const end = (
		vo_info->leaves
		+ vo_info->table_header->structuresize
	);

	vobj.raw = vo_info->v1_1->VoltageObj;
	while (vobj.raw < end) {
		vobj.raw += vobj.vobj->volt_obj_v1.Size;
		vo_info->num_voltage_objects++;
	}

	error_assert(&(commons->error), ERROR_WARNING,
		"voltageobject_info_v1_1 buggy table sizes",
		vobj.raw == end
	);
	if (vobj.raw != end) {
		vo_info->num_voltage_objects--;
	}

	if (vo_info->num_voltage_objects) {
		struct atomtree_voltage_object* const voltage_objects = arena_alloc(
			&(commons->alloc_arena), &(commons->error),
			vo_info->num_voltage_objects * sizeof(vo_info->voltage_objects[0])
		);
		vo_info->voltage_objects = voltage_objects;

		vobj.raw = vo_info->v1_1->VoltageObj;
		for (uint16_t i=0; i < vo_info->num_voltage_objects; i++) {
			voltage_objects[i].obj = vobj.vobj;
			voltage_objects[i].ver = SET_VER(1,0);
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
		}
	}
}

inline static void
populate_voltageobject_info_v1_2(
		struct atomtree_commons* const commons,
		struct atomtree_voltageobject_info* const vo_info
		) {
	// get the size ofthe dynamically-sized voltage object array, and walk
	// through the array based on what each element reports their size as.
	union {
		void* raw;
		union atom_voltage_object_all* vobj;
	} vobj;
	void const* const end = (
		vo_info->leaves
		+ vo_info->table_header->structuresize
	);

	vobj.raw = vo_info->v1_2->VoltageObj;
	while (vobj.raw < end) {
		vobj.raw += vobj.vobj->volt_obj_v2.Size;
		vo_info->num_voltage_objects++;
	}

	error_assert(&(commons->error), ERROR_WARNING,
		"voltageobject_info_v1_2 buggy table sizes",
		vobj.raw == end
	);
	if (vobj.raw != end) {
		vo_info->num_voltage_objects--;
	}

	if (vo_info->num_voltage_objects) {
		struct atomtree_voltage_object* const voltage_objects = arena_alloc(
			&(commons->alloc_arena), &(commons->error),
			vo_info->num_voltage_objects * sizeof(vo_info->voltage_objects[0])
		);
		vo_info->voltage_objects = voltage_objects;

		vobj.raw = vo_info->v1_2->VoltageObj;
		for (uint16_t i=0; i < vo_info->num_voltage_objects; i++) {
			voltage_objects[i].obj = vobj.vobj;
			voltage_objects[i].ver = SET_VER(2,0);
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
		}
	}
}

inline static void
populate_voltageobject_info_v3_1(
		struct atomtree_commons* const commons,
		struct atomtree_voltageobject_info* const vo_info
		) {
	// get the size ofthe dynamically-sized voltage object array, and walk
	// through the array based on what each element reports their size as.
	union {
		void* raw;
		union atom_voltage_object_all* vobj;
	} vobj;
	void const* const end = (
		vo_info->leaves
		+ vo_info->table_header->structuresize
	);

	vobj.raw = vo_info->v3_1->voltage_object;
	while (vobj.raw < end) {
		vobj.raw += vobj.vobj->header.object_size;
		vo_info->num_voltage_objects++;
	}

	error_assert(&(commons->error), ERROR_WARNING,
		"voltageobject_info_v3_1 buggy table sizes",
		vobj.raw == end
	);
	if (vobj.raw != end) {
		vo_info->num_voltage_objects--;
	}

	if (vo_info->num_voltage_objects) {
		struct atomtree_voltage_object* const voltage_objects = arena_alloc(
			&(commons->alloc_arena), &(commons->error),
			vo_info->num_voltage_objects * sizeof(vo_info->voltage_objects[0])
		);
		vo_info->voltage_objects = voltage_objects;

		vobj.raw = vo_info->v3_1->voltage_object;
		for (uint16_t i=0; i < vo_info->num_voltage_objects; i++) {
			voltage_objects[i].obj = vobj.vobj;
			voltage_objects[i].ver = SET_VER(1,0); // all v3_1 have v1_0 objects
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
		}
	}
}


inline static void
populate_voltageobject_info_v4_1(
		struct atomtree_commons* const commons,
		struct atomtree_voltageobject_info* const vo_info
		) {
	// get the size ofthe dynamically-sized voltage object array, and walk
	// through the array based on what each element reports their size as.
	union {
		void* raw;
		union atom_voltage_object_all* vobj;
	} vobj;
	void const* const end = (
		vo_info->leaves
		+ vo_info->table_header->structuresize
	);

	vobj.raw = vo_info->v4_1->voltage_object;
	while (vobj.raw < end) {
		vobj.raw += vobj.vobj->header.object_size;
		vo_info->num_voltage_objects++;
	}

	error_assert(&(commons->error), ERROR_WARNING,
		"voltageobject_info_v4_1 buggy table sizes",
		vobj.raw == end
	);
	if (vobj.raw != end) { // buggy V620
		vo_info->num_voltage_objects--;
	}

	if (vo_info->num_voltage_objects) {
		struct atomtree_voltage_object* const voltage_objects = arena_alloc(
			&(commons->alloc_arena), &(commons->error),
			vo_info->num_voltage_objects * sizeof(vo_info->voltage_objects[0])
		);
		vo_info->voltage_objects = voltage_objects;

		vobj.raw = vo_info->v4_1->voltage_object;
		for (uint16_t i=0; i < vo_info->num_voltage_objects; i++) {
			voltage_objects[i].obj = vobj.vobj;
			// nearly all v4_1 have v1_0 objects
			voltage_objects[i].ver = SET_VER(1,0);
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
					voltage_objects[i].ver = SET_VER(2,0);
				default:
					break;
			}

			vobj.raw += vobj.vobj->header.object_size;
		}
	}
}


inline static void
populate_voltageobject_info(
		struct atomtree_commons* const commons,
		struct atomtree_voltageobject_info* const vo_info,
		uint16_t const bios_offset
		) {
	if (0 == bios_offset) {
		return;
	}

	vo_info->leaves = commons->bios + bios_offset;
	vo_info->ver = atom_get_ver(vo_info->table_header);
	switch (vo_info->ver.ver) {
		case V(1,1): populate_voltageobject_info_v1_1(commons, vo_info); break;
		case V(1,2): populate_voltageobject_info_v1_2(commons, vo_info); break;
		case V(3,1): populate_voltageobject_info_v3_1(commons, vo_info); break;
		case V(4,2): // hopefully v4_2 is the same
		case V(4,1): populate_voltageobject_info_v4_1(commons, vo_info); break;
		case V(1,0): assert(0);
		default: break;
	}
}


inline static void
populate_datatable_v1_1(
		struct atomtree_commons* const commons,
		struct atomtree_master_datatable* const data_table
		) {
	void* const bios = commons->bios;
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

	populate_firmwareinfo(commons, &(dt11->firmwareinfo), leaves->FirmwareInfo);

	if (leaves->PaletteData) {
		dt11->palette_data = bios + leaves->PaletteData;
	}

	populate_lcd_info(commons, &(dt11->lcd_info), leaves->LCD_Info);

	if (leaves->DIGTransmitterInfo) {
		dt11->dig_transmitter_info = bios + leaves->DIGTransmitterInfo;
	}

	if (leaves->ATV_SMU_Info) {
		struct atom_common_table_header const* header = (
			bios + leaves->ATV_SMU_Info
		);
		if (1 == header->format_revision) {
			populate_analog_tv_info(
				commons, &(dt11->analog_tv), leaves->ATV_SMU_Info
			);
		} else {
			populate_smu_info(commons, &(dt11->smu_info), leaves->ATV_SMU_Info);
		}
	}

	if (leaves->SupportedDevicesInfo) {
		dt11->supported_devices_info = bios + leaves->SupportedDevicesInfo;
	}

	if (leaves->GPIO_I2C_Info) {
		dt11->gpio_i2c_info = bios + leaves->GPIO_I2C_Info;
	}

	populate_vram_usagebyfirmware(
		commons, &(dt11->vram_usagebyfirmware), leaves->VRAM_UsageByFirmware
	);

	populate_gpio_pin_lut(commons, &(dt11->gpio_pin_lut), leaves->GPIO_Pin_LUT);

	if (leaves->VESA_ToInternalModeLUT) {
		dt11->vesa_to_internal_mode = bios + leaves->VESA_ToInternalModeLUT;
	}

	populate_gfx_info(commons, &(dt11->gfx_info), leaves->GFX_Info);

	populate_ppt(commons, &(dt11->powerplayinfo), leaves->PowerPlayInfo);

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

	populate_display_object(
		commons, &(dt11->display_object), leaves->Object_Header
	);

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

	populate_vram_info(commons, &(dt11->vram_info), leaves->VRAM_Info);

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
		commons, &(dt11->voltageobject_info), leaves->VoltageObjectInfo
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
		struct atomtree_commons* const commons,
		struct atomtree_master_datatable_v2_1* const dt21
		) {
	struct atom_master_data_table_v2_1* const leaves = dt21->leaves;
	void* const bios = commons->bios;

	if (leaves->sw_datatable3) {
		dt21->sw_datatable3.leaves = bios + leaves->sw_datatable3;
		dt21->sw_datatable3.ver = atom_get_ver(dt21->sw_datatable3.leaves);
	}

	if (leaves->sw_datatable5) {
		dt21->sw_datatable5.leaves = bios + leaves->sw_datatable5;
		dt21->sw_datatable5.ver = atom_get_ver(dt21->sw_datatable5.leaves);
	}

	if (leaves->sw_datatable7) {
		dt21->sw_datatable7.leaves = bios + leaves->sw_datatable7;
		dt21->sw_datatable7.ver = atom_get_ver(dt21->sw_datatable7.leaves);
	}

	if (leaves->sw_datatable9) {
		dt21->sw_datatable9.leaves = bios + leaves->sw_datatable9;
		dt21->sw_datatable9.ver = atom_get_ver(dt21->sw_datatable9.leaves);
	}

	if (leaves->sw_datatable10) {
		dt21->sw_datatable10.leaves = bios + leaves->sw_datatable10;
		dt21->sw_datatable10.ver = atom_get_ver(dt21->sw_datatable10.leaves);
	}

	if (leaves->sw_datatable13) {
		dt21->sw_datatable13.leaves = bios + leaves->sw_datatable13;
		dt21->sw_datatable13.ver = atom_get_ver(dt21->sw_datatable13.leaves);
	}

	if (leaves->sw_datatable16) {
		dt21->sw_datatable16.leaves = bios + leaves->sw_datatable16;
		dt21->sw_datatable16.ver = atom_get_ver(dt21->sw_datatable16.leaves);
	}

	if (leaves->sw_datatable17) {
		dt21->sw_datatable17.leaves = bios + leaves->sw_datatable17;
		dt21->sw_datatable17.ver = atom_get_ver(dt21->sw_datatable17.leaves);
	}

	if (leaves->sw_datatable18) {
		dt21->sw_datatable18.leaves = bios + leaves->sw_datatable18;
		dt21->sw_datatable18.ver = atom_get_ver(dt21->sw_datatable18.leaves);
	}

	if (leaves->sw_datatable19) {
		dt21->sw_datatable19.leaves = bios + leaves->sw_datatable19;
		dt21->sw_datatable19.ver = atom_get_ver(dt21->sw_datatable19.leaves);
	}

	if (leaves->sw_datatable20) {
		dt21->sw_datatable20.leaves = bios + leaves->sw_datatable20;
		dt21->sw_datatable20.ver = atom_get_ver(dt21->sw_datatable20.leaves);
	}

	if (leaves->sw_datatable21) {
		dt21->sw_datatable21.leaves = bios + leaves->sw_datatable21;
		dt21->sw_datatable21.ver = atom_get_ver(dt21->sw_datatable21.leaves);
	}

	if (leaves->sw_datatable25) {
		dt21->sw_datatable25.leaves = bios + leaves->sw_datatable25;
		dt21->sw_datatable25.ver = atom_get_ver(dt21->sw_datatable25.leaves);
	}

	if (leaves->sw_datatable26) {
		dt21->sw_datatable26.leaves = bios + leaves->sw_datatable26;
		dt21->sw_datatable26.ver = atom_get_ver(dt21->sw_datatable26.leaves);
	}

	if (leaves->sw_datatable29) {
		dt21->sw_datatable29.leaves = bios + leaves->sw_datatable29;
		dt21->sw_datatable29.ver = atom_get_ver(dt21->sw_datatable29.leaves);
	}

	if (leaves->sw_datatable33) {
		dt21->sw_datatable33.leaves = bios + leaves->sw_datatable33;
		dt21->sw_datatable33.ver = atom_get_ver(dt21->sw_datatable33.leaves);
	}

	if (leaves->sw_datatable34) {
		dt21->sw_datatable34.leaves = bios + leaves->sw_datatable34;
		dt21->sw_datatable34.ver = atom_get_ver(dt21->sw_datatable34.leaves);
	}
}
inline static void
populate_datatable_v2_1(
		struct atomtree_commons* const commons,
		struct atomtree_master_datatable* const data_table
		) {
	void* const bios = commons->bios;
	struct atomtree_master_datatable_v2_1* const dt21 = &(data_table->v2_1);
	dt21->leaves = data_table->leaves;
	struct atom_master_data_table_v2_1* const leaves = data_table->leaves;

	if (leaves->utilitypipeline) {
		dt21->utilitypipeline = bios + leaves->utilitypipeline;
	}

	if (leaves->multimedia_info) {
		dt21->multimedia_info = bios + leaves->multimedia_info;
	}

	populate_smc_dpm_info(commons, &(dt21->smc_dpm_info), leaves->smc_dpm_info);

	populate_firmwareinfo(commons, &(dt21->firmwareinfo), leaves->firmwareinfo);

	populate_lcd_info(commons, &(dt21->lcd_info), leaves->lcd_info);

	populate_smu_info(commons, &(dt21->smu_info), leaves->smu_info);

	populate_vram_usagebyfirmware(
		commons, &(dt21->vram_usagebyfirmware), leaves->vram_usagebyfirmware
	);

	populate_gpio_pin_lut(commons, &(dt21->gpio_pin_lut), leaves->gpio_pin_lut);

	populate_gfx_info(commons, &(dt21->gfx_info), leaves->gfx_info);

	populate_ppt(commons, &(dt21->powerplayinfo), leaves->powerplayinfo);

	populate_display_object(
		commons, &(dt21->display_object), leaves->displayobjectinfo
	);


	//displayobjectinfo
	//indirectioaccess
	//umc_info
	//dce_info

	populate_vram_info(commons, &(dt21->vram_info), leaves->vram_info);

	//integratedsysteminfo
	//asic_profiling_info

	populate_voltageobject_info(
		commons, &(dt21->voltageobject_info), leaves->voltageobject_info
	);

	atomtree_datatable_v2_1_populate_sw_datatables(commons, dt21);
}

inline static void
populate_datatables(
		//struct atomtree_master_datatable* const data_table,
		struct atomtree_commons* const commons,
		uint16_t const bios_offset
		) {
	if (0 == bios_offset) {
		return;
	}

	struct atomtree_master_datatable* const data_table = &(
		commons->atree->data_table
	);
	data_table->leaves = commons->bios + bios_offset;
	data_table->ver = atom_get_ver(data_table->table_header);
	switch (data_table->ver.ver) {
		case V(1,1): populate_datatable_v1_1(commons, data_table); break;
		case V(2,1): populate_datatable_v2_1(commons, data_table); break;
		default: assert(0); break;
	}
}

inline static bool
verify_discovery_binary_header_checksum(
		struct discovery_fw_blob const* const dis
		) {
	uint8_t const* pos = (
		(void*) & (dis->binary_header)
		+ offsetof(typeof(dis->binary_header), binary_size) // start
	);
	uint8_t const* const end = (
		(void*) & (dis->binary_header)
		+ dis->binary_header.binary_size
	);
	uint16_t sum = 0;
	for (; pos < end; pos++) {
		sum += *pos;
	};
	return sum == dis->binary_header.binary_checksum;
}
inline static void
populate_discovery_table_ip_dies(
		struct atomtree_commons* const commons,
		struct atomtree_discovery_table* const dis,
		void* const binary
		) {
	// double flex array: each die has an array of IP entries, each IP with an
	// array of base addresses.
	struct ip_die_info* const die_offsets = dis->ip_discovery->die_info;
	struct atomtree_discovery_ip_die* const dies = dis->dies;

	uint8_t const version = dis->ip_discovery->version;
	bool const base_addr_64_bit = dis->ip_discovery->flags.base_addr_64_bit;

	if (dis->ip_discovery->num_dies < IP_DISCOVERY_MAX_NUM_DIES) {
		dis->num_dies = dis->ip_discovery->num_dies;
	} else {
		dis->num_dies = IP_DISCOVERY_MAX_NUM_DIES;
	}
	for (uint8_t die_i=0; die_i < dis->num_dies; die_i++) {
		dies[die_i].header = binary + die_offsets[die_i].die_offset;

		uint16_t num_ips = dies[die_i].header->num_ips;
		if (0 == num_ips) {
			assert(0);
			continue;
		}
		struct atomtree_discovery_ip_entry* ips = arena_alloc(
			&(commons->alloc_arena), &(commons->error),
			num_ips * sizeof(dies[die_i].entries[0])
		);
		dies[die_i].entries = ips;
		union {
			void* raw;
			union discovery_ip_entry* e;
		} ip = {
			.raw = (void*)(dies[die_i].header) + sizeof(*(dies[die_i].header))
		};
		uint16_t ip_i = 0;
		do {
			ips[ip_i].raw = ip.raw;
			ips[ip_i].ver = SET_VER(
				ip.e->header.major, ip.e->header.minor, ip.e->header.revision
			);
			switch (version) {
				case 1:
				case 2:
					ip.raw += sizeof_flex(
						&(ip.e->v1),  base_address,
						ip.e->header.num_base_address
					);
					break;
				case 3:
				case 4:
					if (base_addr_64_bit) {
						ip.raw += sizeof_flex(
							&(ip.e->v4_64),  base_address,
							ip.e->header.num_base_address
						);
					} else {
						ip.raw += sizeof_flex(
							&(ip.e->v3),  base_address,
							ip.e->header.num_base_address
						);
					}
					break;
				default: assert(0);
			}
			ip_i++;
		} while (ip_i < num_ips);
	}
}
inline static void
populate_discovery_table(
		struct atomtree_commons* const commons,
		struct atomtree_discovery_table* const dis
		) {
	union {
		void* raw;
		struct discovery_binary_header* bin;
	} const b = {
		.bin = & (dis->blob->binary_header)
	};
	struct discovery_table_info const* const table_list = b.bin->table_list;

	dis->binary_ver = SET_VER(b.bin->version_major, b.bin->version_minor);

	if (table_list[DISCOVERY_IP_DISCOVERY].offset) {
		dis->ip_discovery = b.raw + table_list[DISCOVERY_IP_DISCOVERY].offset;
		dis->ip_ver = SET_VER(dis->ip_discovery->version);

		populate_discovery_table_ip_dies(commons, dis, b.raw);
	}

	if (table_list[DISCOVERY_GC].offset) {
		dis->gc_info = b.raw + table_list[DISCOVERY_GC].offset;
		dis->gc_ver = SET_VER(
			dis->gc_info->header.version_major,
			dis->gc_info->header.version_minor
		);
	}
	if (table_list[DISCOVERY_HARVEST_INFO].offset) {
		dis->harvest = b.raw + table_list[DISCOVERY_HARVEST_INFO].offset;
		dis->harvest_ver = SET_VER(dis->harvest->header.version);
	}
	if (table_list[DISCOVERY_VCN_INFO].offset) {
		dis->vcn_info = b.raw + table_list[DISCOVERY_VCN_INFO].offset;
		dis->vcn_ver = SET_VER(
			dis->vcn_info->header.version_major,
			dis->vcn_info->header.version_minor
		);
	}
	if (table_list[DISCOVERY_MALL_INFO].offset) {
		dis->mall_info = b.raw + table_list[DISCOVERY_MALL_INFO].offset;
		dis->mall_ver = SET_VER(
			dis->mall_info->header.version_major,
			dis->mall_info->header.version_minor
		);
	}
	if (table_list[DISCOVERY_NPS_INFO].offset) {
		dis->nps_info = b.raw + table_list[DISCOVERY_NPS_INFO].offset;
		dis->nps_ver = SET_VER(
			dis->nps_info->header.version_major,
			dis->nps_info->header.version_minor
		);
	}
}

inline static void
populate_psp_fw_payload_type(
		struct atomtree_commons* const commons,
		struct psp_directory_entry const* const pspentry,
		struct atomtree_psp_directory_entries* const fw_entry
		) {
	fw_entry->has_fw_header = (
		(sizeof(*fw_entry->header) <= pspentry->size)
		&& (fw_entry->header->fw_type == pspentry->type)
	);

	if (fw_entry->has_fw_header) {
		if ((sizeof(*fw_entry->discovery.blob) <= pspentry->size
				) && (
					DISCOVERY_BINARY_SIGNATURE
					== fw_entry->discovery.blob->binary_header.signature
				)) {
			fw_entry->type = PSPFW_DISCOVERY;
			populate_discovery_table(commons, &(fw_entry->discovery));
		}
	}
}
inline static void
pspdirectory_checksum(
		struct atomtree_psp_directory* const pspdir
		) {
	struct psp_directory* const dir = pspdir->directory;
	dir->header.checksum = fletcher32(
		&(dir->header.totalentries),
		(sizeof_flex(dir, pspentry, dir->header.totalentries)
			- offsetof(typeof(*dir), header.totalentries)
		)

	);
}
inline static void
populate_psp_directory_table(
		struct atomtree_commons* const commons,
		struct atomtree_psp_directory* const pspdir,
		uint32_t const bios_offset
		) {
	void* const bios = commons->bios;
	if (0 == bios_offset) {
		return;
	}
	union {
		void* raw;
		struct psp_directory* dir;
	} const d = {
		.raw = bios + bios_offset
	};
	if (PSP_COOKIE != d.dir->header.pspcookie.num) {
		return;
	};

	pspdir->directory = d.dir;

	uint8_t const totalentries = d.dir->header.totalentries;
	if (0 == totalentries) {
		return;

	}
	struct atomtree_psp_directory_entries* const fw_entries = arena_alloc(
		&(commons->alloc_arena), &(commons->error),
		totalentries * sizeof(pspdir->fw_entries[0])
	);
	void* moded_start[4] = { // see union psp_directory_entry_address
		commons->atree->alloced_bios, // physical
		bios, // bios; unsure, untested
		d.raw, // dir header; unsure, untested

		commons->atree->alloced_bios, // partition; incorrect
		// partition seems per-entry ad-hoc; but relative to what?
	};
	union psp_directory_entry_address addr;
	for (uint8_t i=0; i < totalentries; i++) {

		addr = d.dir->pspentry[i].address;
		if (3 == addr.mode) {
			continue;
		}

		fw_entries[i].raw = moded_start[addr.mode] + addr.address;
		populate_psp_fw_payload_type(
			commons, &(d.dir->pspentry[i]), &(fw_entries[i])
		);
	}

	pspdir->fw_entries = fw_entries;
}


inline static void
populate_atom_rom_header_v1_1(
		struct atomtree_commons* const commons,
		struct atomtree_rom_header* const rom
		) {
	struct atom_tree* const atree = commons->atree;
	struct atom_rom_header_v1_1* const leaves = rom->v1_1;
	void* const bios = commons->bios;
	
	assert(ATOM_SIGNATURE == rom->v1_1->FirmWareSignature.num);

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

	//rom->data_table = &(atree->data_table);
	populate_datatables(commons, leaves->MasterDataTableOffset);
}

inline static void
populate_atom_rom_header_v2_1(
		struct atomtree_commons* const commons,
		struct atomtree_rom_header* const rom
		) {
	struct atom_tree* const atree = commons->atree;
	struct atom_rom_header_v2_1* const leaves = rom->v2_1;
	void* const bios = commons->bios;

	assert(ATOM_SIGNATURE == rom->v2_1->FirmWareSignature.num);

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
	
	populate_psp_directory_table(
		commons, &(atree->psp_directory), leaves->PSPDirTableOffset
	);

	//rom->data_table = &(atree->data_table);
	populate_datatables(commons, leaves->MasterDataTableOffset);
}
inline static void
populate_atom_rom_header_v2_2(
		struct atomtree_commons* const commons,
		struct atomtree_rom_header* const rom
		) {
	struct atom_tree* const atree = commons->atree;
	struct atom_rom_header_v2_2* const leaves = rom->v2_2;
	void* const bios = commons->bios;

	assert(ATOM_SIGNATURE == rom->v2_2->signature.num);

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
	populate_psp_directory_table(
		commons, &(atree->psp_directory), leaves->pspdirtableoffset
	);

	//rom->data_table = &(atree->data_table);
	populate_datatables(commons, leaves->masterdatatable_offset);

	/*
	//atree->crc_block = bios + atree->leaves->crc_block_offset;
	TODO what are these locations?
	TODO double-check if all rom has same place as v2.1
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
		struct atomtree_commons* const commons,
		struct atomtree_rom_header* const rom,
		uint16_t offset
		) {
	if (offset) {
		rom->leaves = commons->bios + offset;
		rom->ver = atom_get_ver(rom->table_header);
		switch (rom->ver.ver) {
			case V(1,1): populate_atom_rom_header_v1_1(commons, rom); break;
			case V(2,1): populate_atom_rom_header_v2_1(commons, rom); break;
			case V(2,3): // forced
			case V(2,2): populate_atom_rom_header_v2_2(commons, rom); break;
			default: break;
		}
	}
}

inline static void
populate_pci_tables(
		struct atomtree_commons* const commons,
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
		struct pcir_data_structure* pcir;
	} pcir;

	uint8_t i = 0;
	header.header = start;
	do {
		if (PCI_HEADER_MAGIC != header.header->pci_rom_signature) {
			break;
		}
		pcir.raw = header.raw + header.header->pcir_structure_offset;
		if (PCIR_SIGNATURE != pcir.pcir->signature.num) {
			break;
		}
		i++;
		header.raw += pcir.pcir->image_length_in_512 * BIOS_IMAGE_SIZE_UNIT;
	} while (!pcir.pcir->last.last_image);
	atree_pci->num_images = i;

	if (atree_pci->num_images) {
		struct pci_rom_tables* const tables = arena_alloc(
			&(commons->alloc_arena), &(commons->error),
			atree_pci->num_images * sizeof(atree_pci->pci_tables[0])
		);
		atree_pci->pci_tables = tables;
		i = 0;
		header.header = start;
		while (i < atree_pci->num_images) {
			pcir.raw = header.raw + header.header->pcir_structure_offset;
			tables[i].header = header.header;
			tables[i].pcir = pcir.pcir;
			tables[i].is_efi = (header.efi->efi_signature == EFI_SIGNATURE);

			header.raw += pcir.pcir->image_length_in_512*BIOS_IMAGE_SIZE_UNIT;
			i++;
		}
	}
}

inline static void*
bios_fastforward(
		void const* const biosfile,
		uint32_t const size
		) {
	union {
		void const* bios;
		struct vbios_rom_header const* image;
	} bi = {
		.bios = biosfile
	};
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
		uint32_t const biosfile_size
		) {
	union {
		void* bios;
		struct vbios_rom_header* image;
	} const b = {
		.bios = bios_fastforward(alloced_bios, biosfile_size)
	};
	if (b.bios == NULL) {
		return NULL;
	}

	struct atomtree_commons commons = {
		.bios = b.bios,
	};

	// atomtree is highly conditional, so zeroing with calloc will make
	// population easier.
	// allocating the size of the bios for atomtree is a heuristic, but should
	// be far, far more than enough.
	arena_init(&(commons.alloc_arena), biosfile_size, true);

	setjmp(commons.error.env);
	if (commons.error.severity) {
		free(commons.alloc_arena.start);
		return NULL;
	}

	struct atom_tree* const atree = arena_alloc(
		&(commons.alloc_arena), &(commons.error), sizeof(struct atom_tree)
	);
	commons.atree = atree;

	atree->alloced_bios = alloced_bios;
	atree->biosfile_size = biosfile_size;

	atree->bios = b.bios; // going to be used as the '0' in places.
	atree->pci_first_image_size = (
		b.image->pci_header.pci_rom_size_in_512 * BIOS_IMAGE_SIZE_UNIT
	);

	if (b.image->atom_bios_message_offset) {
		uint8_t i = 0;
		char* strs = b.bios + b.image->atom_bios_message_offset;
		do {
			i++;
			strs += strlen(strs) + 1;
		} while (*strs); // the last string ends with 00 00
		atree->num_of_crawled_strings = i;
		atree->atombios_strings = arena_alloc(
			&(commons.alloc_arena), &(commons.error),
			atree->num_of_crawled_strings * sizeof(atree->atombios_strings[0])
		);
		i = 0;
		strs = b.bios + b.image->atom_bios_message_offset;
		do {
			atree->atombios_strings[i] = strs;
			i++;
			strs += strlen(strs) + 1;
		} while (*strs);
	}


	populate_pci_tables(&commons, &(atree->pci_tables), &(b.image->pci_header));
	if (atree->pci_tables.num_images) { // if this fails, no PCIR
		atree->chip_type = get_amd_chip_from_pci_id(
			atree->pci_tables.pci_tables[0].pcir->vendor_id,
			atree->pci_tables.pci_tables[0].pcir->device_id
		);
	}

	populate_atom_rom_header(
		&commons, &(atree->rom_header), b.image->rom_header_info_table_offset
	);

	// populate_commandtables(atree); // TODO
	return atree;
}


inline semver
atom_get_ver(
		struct atom_common_table_header const* const header
		) {
	return (semver) {
		.major = header->format_revision,
		.minor = header->content_revision,
	};
}
inline void
atom_set_ver(
		semver const ver,
		struct atom_common_table_header* const header
		) {
	header->format_revision = ver.major;
	header->content_revision = ver.minor;
}


inline static void
atombios_checksum(
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
atomtree_calculate_checksums(
		struct atom_tree* const atree
		) {
	if (atree->psp_directory.directory) {
		pspdirectory_checksum(&(atree->psp_directory));
	}
	atombios_checksum(atree);
}


void
atomtree_destroy(
		struct atom_tree* const atree
		) {
	free(atree->alloced_bios);
	free(atree);
}
