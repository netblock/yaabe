/*
AtomBIOS crawler.
see atomtree.h and data_tables.h
*/

#include "standard.h"
#include "atomtree.h"
#include "atomtree_internal.h"

// for non-sophisticated atomtree bios pointers.
// takes a double-pointer to an atombios struct that has 
// struct atom_common_table_header table_header; 
// in it. If it fails, it resets the pointer to NULL.
#define offrst_atom_table(com, at_ptr) ({\
	struct atomtree_commons* const _c = (com);\
	auto const _at_ptr = (at_ptr);\
	auto const bios = *_at_ptr;\
	bool err = offchk(_c, bios);\
	if (!err) {\
		err = offchk(_c, bios, bios->table_header.structuresize);\
	}\
	if (err) {\
		*at_ptr = NULL;\
	}\
	err;\
})

static bool // error
populate_atom(
		struct atomtree_commons* const com,
		atomtree_atom* const atom,
		uint16_t const bios_offset
		) {
	if (0 == bios_offset) {
		return true;
	}
	struct atom_common_table_header* const header = com->bios + bios_offset;
	if (offchk(com, header)) {
		return true;
	}
	atom->table_header = header; // set it anyway for diagnostic
	if (offchk(com, header, header->structuresize)) {
		return true;
	}

	atom->ver = atom_get_ver(header);
	return false;
}



inline static void
populate_smc_dpm_info(
		struct atomtree_commons* const com,
		struct atomtree_smc_dpm_info* const smc_dpm_info,
		uint16_t const bios_offset
		) {
	if (populate_atom(com, &(smc_dpm_info->atom), bios_offset)) {
		return;
	}

	size_t size = 0;
	switch (smc_dpm_info->ver.ver) {
		case V(4,1):  size = sizeof(*smc_dpm_info->v4_1);  break;
		case V(4,3):  size = sizeof(*smc_dpm_info->v4_3);  break;
		case V(4,4):  size = sizeof(*smc_dpm_info->v4_4);  break;
		case V(4,5):  size = sizeof(*smc_dpm_info->v4_5);  break;
		case V(4,6):  size = sizeof(*smc_dpm_info->v4_6);  break;
		case V(4,7):  size = sizeof(*smc_dpm_info->v4_7);  break;
		case V(4,9):  size = sizeof(*smc_dpm_info->v4_9);  break;
		case V(4,10): size = sizeof(*smc_dpm_info->v4_10); break;
		case V(5,0):  size = sizeof(*smc_dpm_info->v5_0);  break;
	}
	if (offchk(com, smc_dpm_info->leaves, size)) { // partial crawl error
		smc_dpm_info->ver = SET_VER(0);
		return;
	}
}


inline static void
populate_firmwareinfo(
		struct atomtree_commons* const com,
		struct atomtree_firmware_info* const firmwareinfo,
		uint16_t const bios_offset
		) {
	if (populate_atom(com, &(firmwareinfo->atom), bios_offset)) {
		return;
	}
	size_t size = 0;
	switch (firmwareinfo->ver.ver) {
		case V(1,0):  size = sizeof(*firmwareinfo->v1_0);  break;
		case V(1,2):  size = sizeof(*firmwareinfo->v1_2);  break;
		case V(1,3):  size = sizeof(*firmwareinfo->v1_3);  break;
		case V(1,4):  size = sizeof(*firmwareinfo->v1_4);  break;
		case V(2,1):  size = sizeof(*firmwareinfo->v2_1);  break;
		case V(2,2):  size = sizeof(*firmwareinfo->v2_2);  break;
		case V(3,1):  size = sizeof(*firmwareinfo->v3_1);  break;
		case V(3,2):  size = sizeof(*firmwareinfo->v3_2);  break;
		case V(3,3):  size = sizeof(*firmwareinfo->v3_3);  break;
		case V(3,4):  size = sizeof(*firmwareinfo->v3_4);  break;
	}
	if (offchk(com, firmwareinfo->leaves, size)) { // partial crawl error
		firmwareinfo->ver = SET_VER(0);
		return;
	}
}


inline static void
populate_lcd_info_record_table(
		struct atomtree_commons* const com,
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
	while (! offchk(com, r.raw, sizeof(*r.RecordType))) {
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
			case LCD_RECORD_END_TYPE:
				goto record_counter_loop_uberbreak;
			case LCD_EDID_OFFSET_PATCH_RECORD_TYPE: // no idea
			default:
				assert(0);
				goto record_counter_loop_uberbreak;
		}
		num_records++;
	}
	num_records--; // fails offchk; only good way out is uberbreak
	record_counter_loop_uberbreak:

	lcd_info->record_table_size = r.raw - record_start;
	lcd_info->num_records = num_records;

	if (num_records) {
		lcd_info->record_table = arena_alloc(
			&(com->alloc_arena), &(com->error),
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
		struct atomtree_commons* const com,
		struct atomtree_lcd_info* const lcd_info,
		uint16_t const bios_offset
		) {
	if (populate_atom(com, &(lcd_info->atom), bios_offset)) {
		return;
	}

	size_t size = 0;
	switch (lcd_info->ver.ver) {
		case V(1,1):  size = sizeof(*lcd_info->v1_1);  break;
		case V(1,2):  size = sizeof(*lcd_info->v1_2);  break;
		case V(1,3):  size = sizeof(*lcd_info->v1_3);  break;
		case V(2,1):  size = sizeof(*lcd_info->v2_1);  break;
	}
	if (offchk(com, lcd_info->leaves, size)) { // partial crawl error
		lcd_info->ver = SET_VER(0);
		return;
	}

	void* record_start = NULL;
	switch (lcd_info->ver.ver) {
		case V(1,1):
			if (lcd_info->v1_1->ModePatchTableOffset) {
				record_start = ( // v1_1 uses an absolute position
					com->bios + lcd_info->v1_1->ModePatchTableOffset
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
	populate_lcd_info_record_table(com, lcd_info, record_start);
}


inline static void
populate_analog_tv_info(
		struct atomtree_commons* const com,
		struct atomtree_analog_tv_info* const atv,
		uint16_t const bios_offset
		) {
	if (populate_atom(com, &(atv->atom), bios_offset)) {
		return;
	}

	size_t size = 0;
	switch (atv->ver.ver) {
		case V(1,1):  size = sizeof(*atv->v1_1);  break;
		case V(1,2):  size = sizeof(*atv->v1_2);  break;
	}
	if (offchk(com, atv->leaves, size)) { // partial crawl error
		atv->ver = SET_VER(0);
		return;
	}
}

inline static void
populate_smu_info(
		struct atomtree_commons* const com,
		struct atomtree_smu_info* const smu_info,
		uint16_t const bios_offset
		) {
	if (populate_atom(com, &(smu_info->atom), bios_offset)) {
		return;
	}

	size_t size = 0;
	switch (smu_info->ver.ver) {
		case V(3,1):  size = sizeof(*smu_info->v3_1);  break;
		case V(3,2):  size = sizeof(*smu_info->v3_2);  break;
		case V(3,3):  size = sizeof(*smu_info->v3_3);  break;
		case V(3,4):  size = sizeof(*smu_info->v3_4);  break;
		case V(3,5):  size = sizeof(*smu_info->v3_5);  break;
		case V(3,6):  size = sizeof(*smu_info->v3_6);  break;
		case V(4,0):  size = sizeof(*smu_info->v4_0);  break;
	}
	if (offchk(com, smu_info->leaves, size)) { // partial crawl error
		smu_info->ver = SET_VER(0);
		return;
	}

	switch (smu_info->ver.ver) {
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
	if (offchk(com, smu_info->smugolden, 1)) {
		 smu_info->smugolden = NULL;
	}
	if (offchk(com, smu_info->smuinit, 1)) {
		 smu_info->smuinit = NULL;
	}
}


inline static void
populate_vram_usagebyfirmware(
		struct atomtree_commons* const com,
		struct atomtree_vram_usagebyfirmware* const fw_vram,
		uint16_t const bios_offset) {
	if (populate_atom(com, &(fw_vram->atom), bios_offset)) {
		return;
	}
	size_t size = 0;
	switch (fw_vram->ver.ver) {
		case V(2,1):  size = sizeof(*fw_vram->v2_1);  break;
		case V(2,2):  size = sizeof(*fw_vram->v2_2);  break;
	}
	if (offchk(com, fw_vram->leaves, size)) { // partial crawl error
		fw_vram->ver = SET_VER(0);
		return;
	}
}


inline static void
populate_gpio_pin_lut(
		struct atomtree_commons* const com,
		struct atomtree_gpio_pin_lut* const gpio_pin_lut,
		uint16_t const bios_offset
		) {
	if (populate_atom(com, &(gpio_pin_lut->atom), bios_offset)) {
		return;
	}
	switch (gpio_pin_lut->ver.ver) {
		case V(2,1):
			gpio_pin_lut->num_gpio_pins = (
				// dynamic array length of nothing but pins after the header
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
		struct atomtree_commons* const com,
		struct atomtree_gfx_info* const gfx_info,
		uint16_t const bios_offset
		) {
	if (populate_atom(com, &(gfx_info->atom), bios_offset)) {
		return;
	}
	size_t size = 0;
	switch (gfx_info->ver.ver) {
		case V(2,1):  size = sizeof(*gfx_info->v2_1);  break;
		case V(2,2):  size = sizeof(*gfx_info->v2_2);  break;
		case V(2,3):  size = sizeof(*gfx_info->v2_3);  break;
		//case V(2,3,2):size = sizeof(*gfx_info->v2_3_2);break;
		case V(2,4):  size = sizeof(*gfx_info->v2_4);  break;
		case V(2,5):  size = sizeof(*gfx_info->v2_5);  break;
		case V(2,6):  size = sizeof(*gfx_info->v2_6);  break;
		case V(2,7):  size = sizeof(*gfx_info->v2_7);  break;
		case V(3,0):  size = sizeof(*gfx_info->v3_0);  break;
	}
	if (offchk(com, gfx_info->leaves, size)) { // partial crawl error
		gfx_info->ver = SET_VER(0);
		return;
	}
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
	offrst(com, &(gfx_info->gcgolden), 1);
	offrst(com, &(gfx_info->edc_didt_hi));
	offrst(com, &(gfx_info->edc_didt_lo));
}

inline static bool // error
populate_powerplay_info(
		struct atomtree_commons* const com,
		struct atomtree_powerplay_table* const ppt
		) {
	bool err;
	switch (ppt->ver.ver) {
		case V(1,1):
			err = offchk_flex(com, ppt->v1_1,
				PowerPlayInfo, ppt->v1_1->NumOfPowerModeEntries
			);
			break;
		case V(2,1):
			err = offchk_flex(com, ppt->v2_1,
				PowerPlayInfo, ppt->v2_1->NumOfPowerModeEntries
			);
			break;
		case V(3,1):
			err = offchk_flex(com, ppt->v3_1,
				PowerPlayInfo, ppt->v3_1->NumOfPowerModeEntries
			);
			break;
		default: assert(0);
	}
	return err;
}


inline static void
populate_pplib_ppt_state_array(
		struct atomtree_commons* const com,
		struct atomtree_powerplay_table* const ppt
		) {
	struct atomtree_powerplay_table_v4_1* const ppt41 = &(ppt->v4_1);
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
	bool oob = false; // out of bounds
	uint8_t i = 0;


	// driver gates with the atom ver
	if (V(6,0) > ppt->ver.ver) {
		ppt41->state_array_ver = SET_VER(1);
		ppt41->num_state_array_entries = pplibv1->NumStates;

		if (pplibv1->NumStates) {
			ppt41->state_array = arena_alloc(
				&(com->alloc_arena), &(com->error),
				pplibv1->NumStates * sizeof(ppt41->state_array[0])
			);

			uint8_t const entry_size = pplibv1->StateEntrySize;
			uint8_t const num_levels = (
				(entry_size - sizeof(base->v1))
				/ sizeof(base->v1.ClockStateIndices[0])
			);
			walker.raw = &(base->v1);
			for (i=0, oob=false; i < pplibv1->NumStates && !oob; i++) {
				oob = offchk(com, walker.raw, entry_size);
				ppt41->state_array[i].num_levels = num_levels;
				ppt41->state_array[i].state = walker.states;
				ppt41->state_array[i].size = entry_size;
				walker.raw += entry_size;
			}
			ppt41->state_array_size = (
				i * pplibv1->StateEntrySize
			);
		}
	} else {
		ppt41->state_array_ver = SET_VER(2);
		ppt41->num_state_array_entries = base->v2.NumEntries;

		if (base->v2.NumEntries) {
			ppt41->state_array = arena_alloc(
				&(com->alloc_arena), &(com->error),
				base->v2.NumEntries * sizeof(ppt41->state_array[0])
			);

			uint16_t entry_size = sizeof(*walker.v2);
			walker.v2 = base->v2.states;
			oob = offchk(com, walker.raw, entry_size);
			for (i=0; i < base->v2.NumEntries && !oob; i++) {
				ppt41->state_array[i].num_levels = walker.v2->NumDPMLevels;
				ppt41->state_array[i].state = walker.states;
				entry_size = sizeof_flex(
					walker.v2, clockInfoIndex, walker.v2->NumDPMLevels
				);
				ppt41->state_array[i].size = entry_size;
				oob = offchk(com, walker.raw, entry_size);
				walker.raw += entry_size;
			}
			ppt41->state_array_size = walker.raw - (void*)base;
		}
	}
	if (oob && ppt41->state_array_size) {
		ppt41->num_state_array_entries = i - 1;
	}
}
inline static void
populate_pplib_ppt_extended_table(
		struct atomtree_commons* const com,
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
			if (ext->v9.UVDTableOffset) {
				ppt41->uvd_root = raw + ext->v9.UVDTableOffset;
			}
			fall;
		case V(2):
			if (ext->v9.VCETableOffset) {
				ppt41->vce_root = raw + ext->v9.VCETableOffset;
			}
			fall;
		case V(1): break;
		default: assert(0); break;
	}
	offrst_flex(com, &(ppt41->vq_budgeting),
		entries, ppt41->vq_budgeting->NumEntries
	);
	offrst_flex(com, &(ppt41->vddgfx_sclk),
		entries, ppt41->vddgfx_sclk->NumEntries
	);
	if (ppt41->powertune) {
		size_t size = sizeof(ppt41->powertune->RevId);
		switch (ppt41->powertune->RevId) {
			case 0: size = sizeof(ppt41->powertune->v0); break;
			case 1: size = sizeof(ppt41->powertune->v1); break;
		}
		offrst(com, &(ppt41->powertune), size);
	}
	offrst_flex(com, &(ppt41->acpclk),
		entries, ppt41->acpclk->NumEntries
	);
	offrst(com, &(ppt41->ppm));
	offrst_flex(com, &(ppt41->samu),
		entries, ppt41->samu->NumEntries
	);

	if (ppt41->uvd_root) { // 2 flex subtables in the table
		bool err = false;
		void* walker = ppt41->uvd_root;
		err = offrst(com, &(ppt41->uvd_root));
		if (err) {
			goto uvd_err;
		}

		ppt41->uvd_info = walker + sizeof(*(ppt41->uvd_root));
		err = offrst_flex(com, &(ppt41->uvd_info),
			entries, ppt41->uvd_info->NumEntries
		);
		if (err) {
			goto uvd_err;
		}

		ppt41->uvd_limits = walker + sizeof_flex(
			ppt41->uvd_info, entries, ppt41->uvd_info->NumEntries
		);
		err = offrst_flex(com, &(ppt41->uvd_limits),
			entries, ppt41->uvd_limits->NumEntries
		);
		if (err) {
			goto uvd_err;
		}

		walker = ppt41->uvd_limits;
		walker += sizeof_flex(
			ppt41->uvd_limits, entries, ppt41->uvd_limits->NumEntries
		);
		uvd_err:
		ppt41->uvd_table_size = walker - (void*)(ppt41->uvd_root);
	}

	if (ppt41->vce_root) { // 3 flex subtables in the table
		bool err = false;
		void* walker = ppt41->vce_root;
		err = offrst(com, &(ppt41->vce_root));
		if (err) {
			goto vce_err;
		}

		ppt41->vce_info = walker + sizeof(*(ppt41->vce_root));
		err = offrst_flex(com, &(ppt41->vce_info),
			entries, ppt41->vce_info->NumEntries
		);
		if (err) {
			goto vce_err;
		}

		ppt41->vce_limits = walker + sizeof_flex(
			ppt41->vce_info, entries, ppt41->vce_info->NumEntries
		);
		err = offrst_flex(com, &(ppt41->vce_limits),
			entries, ppt41->vce_limits->NumEntries
		);
		if (err) {
			goto vce_err;
		}

		ppt41->vce_states = walker + sizeof_flex(
			ppt41->vce_limits, entries, ppt41->vce_info->NumEntries
		);
		err = offrst_flex(com, &(ppt41->vce_states),
			entries, ppt41->vce_states->NumEntries
		);
		if (err) {
			goto vce_err;
		}

		walker = ppt41->vce_states;
		walker += sizeof_flex(
			ppt41->vce_states, entries, ppt41->vce_states->NumEntries
		);
		vce_err:
		ppt41->vce_table_size = walker - (void*)(ppt41->vce_root);
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
		struct atomtree_commons* const com,
		struct atomtree_powerplay_table_v4_1* const ppt41
		) {
	union atom_pplib_clock_info_arrays const* const ci = ppt41->clock_info;

	// radeon driver's codepaths for r600, r7xxx, evergeeen is a tangled mess
	switch (com->atree->chip_type) {
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
	if (offchk(com, ppt41->clock_info, ppt41->clock_info_size)) {
		ppt41->clock_info_ver = ATOM_PPLIB_CLOCK_INFO_UNKNOWN;
		ppt41->clock_info_size = 0;
		ppt41->num_clock_info_entries = 0;
		ppt41->clock_info = NULL;
	}
}
inline static bool // error
populate_pplib_ppt(
		struct atomtree_commons* const com,
		struct atomtree_powerplay_table* const ppt
		) {
	struct atomtree_powerplay_table_v4_1* const ppt41 = &(ppt->v4_1);
	union {
		void* raw;
		union atom_pplib_powerplaytables* all;
		struct atom_pplib_powerplaytable_v5* v5;
	} const b = {
		.raw = ppt41->leaves
	};

	if (offchk(com, b.raw, sizeof(b.all->v1))) { // to access TableSize
		return true;
	}

	switch (b.v5->TableSize) {
		case sizeof(b.all->v5): ppt41->pplib_ver = SET_VER(5); break;
		case sizeof(b.all->v4): ppt41->pplib_ver = SET_VER(4); break;
		case sizeof(b.all->v3): ppt41->pplib_ver = SET_VER(3); break;
		case sizeof(b.all->v2): ppt41->pplib_ver = SET_VER(2); break;
		case 0: // R600
		case sizeof(b.all->v1): ppt41->pplib_ver = SET_VER(1); break;
		default: assert(0);
	};

	size_t size;
	switch (ppt41->pplib_ver.ver) {
		case V(5): size = sizeof(b.all->v5); break;
		case V(4): size = sizeof(b.all->v4); break;
		case V(3): size = sizeof(b.all->v3); break;
		case V(2): size = sizeof(b.all->v2); break;
		case V(1): size = sizeof(b.all->v1); break;
		default:   size = 0; // tolerate unknown because we can
	};
	if (offchk(com, b.raw, size)) {
		return true;
	}

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
			}
			if (b.v5->ClockInfoArrayOffset) {
				ppt41->clock_info = b.raw + b.v5->ClockInfoArrayOffset;
			}
			if (b.v5->NonClockInfoArrayOffset) {
				ppt41->nonclock_info = b.raw + b.v5->NonClockInfoArrayOffset;
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
	}
	offrst(com, &(ppt41->state_array_base));
	offrst(com, &(ppt41->clock_info),
		sizeof(ppt41->clock_info->header)
	);
	offrst(com, &(ppt41->nonclock_info),
		sizeof(ppt41->nonclock_info->header)
	);
	offrst(com, &(ppt41->boot_clock_info), 1);
	offrst(com, &(ppt41->boot_nonclock_info), 1);
	offrst(com, &(ppt41->thermal_policy));
	offrst(com, &(ppt41->fan_table),
		sizeof(ppt41->fan_table->RevId)
	);
	offrst(com, &(ppt41->extended_header),
		sizeof(ppt41->extended_header->Size)
	);
	offrst_flex(com, &(ppt41->vddc_sclk),
		entries, ppt41->vddc_sclk->NumEntries
	);
	offrst_flex(com, &(ppt41->vddci_mclk),
		entries, ppt41->vddci_mclk->NumEntries
	);
	offrst_flex(com, &(ppt41->vddc_mclk),
		entries, ppt41->vddc_mclk->NumEntries
	);
	offrst_flex(com, &(ppt41->max_on_dc),
		entries, ppt41->max_on_dc->NumEntries
	);
	offrst_flex(com, &(ppt41->phase_shed),
		entries, ppt41->phase_shed->NumEntries
	);
	offrst_flex(com, &(ppt41->mvdd_mclk),
		entries, ppt41->mvdd_mclk->NumEntries
	);
	offrst(com, &(ppt41->cac_leakage),
		sizeof(ppt41->cac_leakage->NumEntries)
	);

	if (ppt41->state_array_base) {
		populate_pplib_ppt_state_array(com, ppt);
	};
	if (ppt41->clock_info) {
		set_pplib_ppt_clock_info(com, ppt41);
	};
	if (ppt41->nonclock_info) {
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
	};
	if (ppt41->fan_table) {
		switch (ppt41->fan_table->RevId) {
			case 1:  size = sizeof(ppt41->fan_table->v1); break;
			case 2:  size = sizeof(ppt41->fan_table->v2); break;
			case 5: 
			case 4: 
			case 3:  size = sizeof(ppt41->fan_table->v3); break;
			case 6:  size = sizeof(ppt41->fan_table->v6); break;
			case 7:  size = sizeof(ppt41->fan_table->v7); break;
			default: size = sizeof(ppt41->fan_table->RevId); break;
		}
		offrst(com, &(ppt41->fan_table), size);
	}
	if (ppt41->extended_header) {
		populate_pplib_ppt_extended_table(com, ppt41);
	}
	if (ppt41->cac_leakage) {
		union atom_pplib_cac_leakage_tables const* const cac = (
			ppt41->cac_leakage
		);
		if (ppt41->leaves->v1.PlatformCaps.EVV) {
			size = sizeof_flex(&(cac->evv), entries, cac->NumEntries);
		} else {
			size = sizeof_flex(&(cac->non_evv), entries, cac->NumEntries);
		}
		offrst(com, &(ppt41->cac_leakage), size);
	}

	return false;
}

inline static bool // error
populate_pptablev1_ppt(
		struct atomtree_commons* const com,
		struct atomtree_powerplay_table* const ppt
		) {
	struct atomtree_powerplay_table_v7_1* const ppt71 = &(ppt->v7_1);
	union {
		void* raw;
		struct atom_pptable_powerplaytable_v1* ppt;
	} const b = {
		.raw = ppt71->leaves
	};

	if (offchk(com, b.ppt)) {
		return true;
	}

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

	offrst_flex(com, &(ppt71->state_array),
		entries, ppt71->state_array->NumEntries
	);
	offrst(com, &(ppt71->fan_table),
		sizeof(ppt71->fan_table->RevId)
	);
	offrst(com, &(ppt71->thermal_controller));
	offrst_flex(com, &(ppt71->mclk_dependency),
		entries, ppt71->mclk_dependency->NumEntries
	);
	offrst(com, &(ppt71->sclk_dependency));
	offrst_flex(com, &(ppt71->vddc_lut),
		entries, ppt71->vddc_lut->NumEntries
	);
	offrst_flex(com, &(ppt71->vddgfx_lut),
		entries, ppt71->vddgfx_lut->NumEntries
	);
	offrst_flex(com, &(ppt71->mm_dependency),
		entries, ppt71->mm_dependency->NumEntries
	);
	offrst_flex(com, &(ppt71->vce_state),
		entries, ppt71->vce_state->NumEntries
	);
	offrst(com, &(ppt71->powertune),
		sizeof(ppt71->powertune->RevId)
	);
	offrst_flex(com, &(ppt71->hard_limit),
		entries, ppt71->hard_limit->NumEntries
	);
	offrst(com, &(ppt71->pcie_table));
	offrst(com, &(ppt71->gpio_table));

	if (ppt71->fan_table) {
		uint8_t RevId = ppt71->fan_table->RevId;
		size_t size = sizeof(RevId);
		if (7 >= RevId)      size = sizeof(ppt71->fan_table->v0);
		else if (8 == RevId) size = sizeof(ppt71->fan_table->v8);
		else if (9 == RevId) size = sizeof(ppt71->fan_table->v9);
		offrst(com, &(ppt71->fan_table), size);
	}
	if (ppt71->sclk_dependency) {
		union atom_pptable_sclk_dependency_tables const* const sclk = (
			ppt71->sclk_dependency
		);
		size_t size = sizeof(sclk->RevId);
		switch (sclk->RevId) {
			case 0:
				size = sizeof_flex(&(sclk->v0), entries, sclk->v0.NumEntries);
				break;
			case 1:
				size = sizeof_flex(&(sclk->v1), entries, sclk->v1.NumEntries);
				break;
		}
		offrst(com, &(ppt71->sclk_dependency), size);
	}
	if (ppt71->powertune) {
		uint8_t const RevId = ppt71->powertune->RevId;
		size_t size = sizeof(RevId);
		if (2 >= RevId)      size = sizeof(ppt71->powertune->v0);
		else if (3 == RevId) size = sizeof(ppt71->powertune->v3);
		else if (4 == RevId) size = sizeof(ppt71->powertune->v4);
		offrst(com, &(ppt71->powertune), size);
	}
	if (ppt71->pcie_table) {
		union atom_pptable_pcie_tables const* const pcie = ppt71->pcie_table;
		size_t size = sizeof(pcie->RevId);
		switch (pcie->RevId) {
			case 0:
				size = sizeof_flex(&(pcie->v0), entries, pcie->v0.NumEntries);
				break;
			case 1:
				size = sizeof_flex(&(pcie->v1), entries, pcie->v1.NumEntries);
				break;
		}
		offrst(com, &(ppt71->pcie_table), size);
	}

	return false;
}

inline static bool // error
populate_vega10_ppt(
		struct atomtree_commons* const com,
		struct atomtree_powerplay_table* const ppt
		) {
	struct atomtree_powerplay_table_v8_1* const ppt81 = &(ppt->v8_1);
	union {
		void* raw;
		struct atom_vega10_powerplaytable* ppt;
	} const b = {
		.raw = ppt81->leaves
	};

	if (offchk(com, b.ppt)) {
		return true;
	}

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

	offrst_flex(com, &(ppt81->state_array),
		states, ppt81->state_array->NumEntries
	);
	offrst(com, &(ppt81->fan_table),
		sizeof(ppt81->fan_table->RevId)
	);
	offrst(com, &(ppt81->thermal_controller));
	offrst_flex(com, &(ppt81->socclk_dependency),
		entries, ppt81->socclk_dependency->NumEntries
	);
	offrst_flex(com, &(ppt81->mclk_dependency),
		entries, ppt81->mclk_dependency->NumEntries
	);
	offrst(com, &(ppt81->gfxclk_dependency));
	offrst_flex(com, &(ppt81->dcefclk_dependency),
		entries, ppt81->dcefclk_dependency->NumEntries
	);
	offrst_flex(com, &(ppt81->vddc_lut),
		vdd_entries, ppt81->vddc_lut->NumEntries
	);
	offrst_flex(com, &(ppt81->vdd_mem_lut),
		vdd_entries, ppt81->vdd_mem_lut->NumEntries
	);
	offrst_flex(com, &(ppt81->mm_dependency),
		entries, ppt81->mm_dependency->NumEntries
	);
	offrst_flex(com, &(ppt81->vce_state),
		entries, ppt81->vce_state->NumEntries
	);
	offrst(com, &(ppt81->powertune),
		sizeof(ppt81->powertune->RevId)
	);
	offrst_flex(com, &(ppt81->hard_limit),
		entries, ppt81->hard_limit->NumEntries
	);
	offrst_flex(com, &(ppt81->vddci_lut),
		vdd_entries, ppt81->vddci_lut->NumEntries
	);
	offrst_flex(com, &(ppt81->pcie_table),
		entries, ppt81->pcie_table->NumEntries
	);
	offrst_flex(com, &(ppt81->pixclk_dependency),
		entries, ppt81->pixclk_dependency->NumEntries
	);
	offrst_flex(com, &(ppt81->dispclk_dependency),
		entries, ppt81->dispclk_dependency->NumEntries
	);
	offrst_flex(com, &(ppt81->phyclk_dependency),
		entries, ppt81->phyclk_dependency->NumEntries
	);
	if (ppt81->fan_table) {
		uint8_t const RevId = ppt81->fan_table->RevId;
		size_t size = sizeof(RevId);
		if (10 == RevId)      size = sizeof(ppt81->fan_table->v1);
		else if (11 == RevId) size = sizeof(ppt81->fan_table->v2);
		else if (12 >= RevId) size = sizeof(ppt81->fan_table->v3);
		offrst(com, &(ppt81->fan_table), size);
	}
	if (ppt81->gfxclk_dependency) {
		union atom_vega10_gfxclk_dependency_tables const* const gfx = (
			ppt81->gfxclk_dependency
		);
		size_t size = sizeof(*gfx);
		switch (ppt81->gfxclk_dependency->RevId) {
			case 0:
				size = sizeof_flex(&(gfx->v1), entries, gfx->v1.NumEntries);
				break;
			case 1:
				size = sizeof_flex(&(gfx->v2), entries, gfx->v2.NumEntries);
				break;
		}
		offrst(com, &(ppt81->gfxclk_dependency), size);
	}
	if (ppt81->powertune) {
		size_t size;
		switch (ppt81->powertune->RevId) {
			case 5:  size = sizeof(ppt81->powertune->v1); break;
			case 6:  size = sizeof(ppt81->powertune->v2); break;
			default: size = sizeof(ppt81->powertune->v3); break;
		}
		offrst(com, &(ppt81->powertune), size);
	}

	return false;
}

inline static bool
populate_ppt_smu(
		struct atomtree_commons* const com,
		struct atomtree_powerplay_table* const ppt
		) {
	struct atomtree_powerplay_smu* const smu = &(ppt->smu);
	union smu_powerplay* const leaves = ppt->smu.leaves;

	union smc_pptables* smc;
	size_t size;
	switch (ppt->ver.ver) {
		case V(11,0):
			size = offsetof(typeof(leaves->v11_0), smc_pptable);
			smc = &(leaves->v11_0.smc_pptable);
			break;
		case V(14,0):
		case V(12,0):
			size = offsetof(typeof(leaves->v12_0), smc_pptable);
			smc = &(leaves->v12_0.smc_pptable);
			break;
		case V(19,0):
		case V(18,0):
		case V(16,0):
		case V(15,0):
			size = offsetof(typeof(leaves->v15_0), smc_pptable);
			smc = &(leaves->v15_0.smc_pptable);
			break;
		default:
			size = sizeof(leaves->pphead);
			smc = NULL;
			break;
	}
	if (offchk(com, leaves, size)) {
		return true;
	}
	smu->ver = ppt->ver;

	if (! offchk(com, smc, sizeof(smc->Version))) {
		smu->smc_pptable = smc;
		switch (smc->Version) {
			case PPTABLE_VEGA20_SMU: size = sizeof(smc->v3); break;
			case PPTABLE_NAVI24_SMU: size = sizeof(smc->v5); break;
			case PPTABLE_NAVI22_SMU:
			case PPTABLE_NAVI21_SMU: size = sizeof(smc->v7); break;
			case PPTABLE_NAVI10_SMU: size = sizeof(smc->v8); break;
			default: size = sizeof(smc->Version); break;
		}
		if (! offchk(com, smc, size)) {
			smu->smc_pptable_ver = smc->Version;
		}
	}

	return false;
}

inline static void
populate_ppt(
		struct atomtree_commons* const com,
		struct atomtree_powerplay_table* const ppt,
		uint16_t const bios_offset
		) {
	if (populate_atom(com, &(ppt->atom), bios_offset)) {
		return;
	}

	bool err = false;
	switch (ppt->ver.ver) {
		case V(1,1):
		case V(2,1):
		case V(3,1):
			err = populate_powerplay_info(com, ppt);
			break;
		case V(6,1):
		case V(5,1):
		case V(4,1):
			err = populate_pplib_ppt(com, ppt);
			break;
		case V(7,1): // Tonga, Fiji, Polaris ; pptable and vega10 look similar
			err = populate_pptablev1_ppt(com, ppt);
			break;
		case V(8,1):
			err = populate_vega10_ppt(com, ppt);
			break;
		case V(11,0): // Vega20
		case V(12,0): // Navi10
		case V(14,0):
		case V(15,0):
		case V(16,0): // 6700XT
		case V(18,0): // navi2 xx50
		case V(19,0): // 6400
			err = populate_ppt_smu(com, ppt);
			break;
		default:
			assert(0);
			break;
	}
	if (err) { // partial crawl error
		ppt->ver = SET_VER(0);
	}
}


static void
populate_display_object_records(
		struct atomtree_commons* const com,
		struct atomtree_display_path_record_set* const set,
		void* const start
		) {
	union {
		void* raw;
		struct atom_common_record_header* header;
		union display_records* records;
	} r = {
		.records = start
	};

	bool err = offchk(com, r.header);
	bool end = false;
	uint8_t size = 1;
	while (!(err || end || 0 == size)) {
		end = (ATOM_RECORD_END_TYPE == r.header->record_type);
		set->num_records++;
		size = r.header->record_size;
		r.raw += r.header->record_size;
		err = offchk(com, r.header);
	}
	set->num_records -= end;

	if (0 == set->num_records) {
		return;
	}
	set->records = arena_alloc(
		&(com->alloc_arena), &(com->error),
		set->num_records * sizeof(set->records[0])
	);

	r.records = start;
	for (uint8_t i=0; i < set->num_records; i++) {
		set->records[i] = r.records;
		r.raw += r.header->record_size;
	}
	set->records_size = r.raw - start;
}

inline static bool
populate_atom_object_table_srcdst(
		struct atomtree_commons* const com,
		struct atomtree_object_table_tables* const object,
		void* const srcdst
		) {
	object->src = srcdst;
	bool err = offrst_flex(com, &(object->src),
		object_id, object->src->num_of_objs
	);
	if (err) {
		return err;
	}
	object->dst = srcdst + sizeof_flex(
		object->src, object_id, object->src->num_of_objs
	);
	err = offrst_flex(com, &(object->dst),
		object_id, object->dst->num_of_objs
	);
	return err;
}
static bool
populate_atom_object_table(
		struct atomtree_commons* const com,
		struct atomtree_object_table* const table,
		void* const bios,
		uint16_t const offset
		) {
	struct atom_object_table* const header = bios + offset;
	if (offchk_flex(com, header, Objects, header->NumberOfObjects)) {
		return true;
	}

	table->table = header;
	uint8_t const num_objects = header->NumberOfObjects;
	struct atomtree_object_table_tables* const objects = arena_alloc(
		&(com->alloc_arena), &(com->error),
		num_objects * sizeof(objects[0])
	);
	table->objects = objects;

	for (uint8_t i=0; i < num_objects; i++) {
		if (header->Objects[i].SrcDstTableOffset) {
			populate_atom_object_table_srcdst(
				com, &(objects[i]),
				bios + header->Objects[i].SrcDstTableOffset
			);
		}
		if (header->Objects[i].RecordOffset) {
			populate_display_object_records(
				com, &(objects[i].records),
				bios + header->Objects[i].RecordOffset
			);
		}
	}
	return false;
}
inline static void
populate_display_object_path_table(
		struct atomtree_commons* const com,
		struct atomtree_object_path* const table,
		void* const bios,
		uint16_t const offset
		) {
	struct atom_display_object_path_table* const header = bios + offset;
	if (offchk_flex(com, header, DispPath, header->NumOfDispPath)) {
		// heuristic; atom_display_object_path_table is flex 2D
		return;
	}

	table->header = header;
	uint8_t const num_paths = header->NumOfDispPath;
	if (0 == num_paths) {
		return;
	}
	struct atomtree_object_path_entry* const paths = arena_alloc(
		&(com->alloc_arena), &(com->error),
		num_paths * sizeof(paths[0])
	);
	table->paths = paths;

	void* pos = header->DispPath;

	uint8_t i = 0;
	bool err;
	do {
		paths[i].path = pos;
		paths[i].num_graphic_ids = (
			(paths[i].path->Size - sizeof(*(paths[i].path)))
			/ sizeof(paths[i].path->GraphicObjIds[0])
		);
		err = offchk(com, pos, paths[i].path->Size);
		pos += paths[i].path->Size;
		i++;
	} while ((i < num_paths) && (! err));
	i -= err;

	table->num_paths = i;
	table->total_size = pos - (void*) header;
	if (err) {
		table->total_size -= paths[i+err-1].path->Size; // 0 == err-1
	}
}
inline static bool
populate_atom_object_header(
		struct atomtree_commons* const com,
		struct atomtree_display_object* const disp
		) {
	// v1.1 .. 1.3
	size_t size;
	void* bios; // 1.1 is absolute; 1.2<= is relative
	if (1 == disp->ver.minor) {
		size = sizeof(*disp->v1_1);
		bios = com->bios;
	} else {
		size = sizeof(*disp->v1_3);
		bios = disp->leaves;
	}
	if (offchk(com, disp->leaves, size)) {
		return true;
	}
	switch (disp->ver.ver) {
		case V(1,3):
			if (disp->v1_3->MiscObjectTableOffset) {
				populate_atom_object_table(com, &(disp->misc),
					bios, disp->v1_3->MiscObjectTableOffset
				);
			}
			fall;
		case V(1,1):
			if (disp->v1_1->ConnectorObjectTableOffset) {
				populate_atom_object_table(com, &(disp->connector),
					bios, disp->v1_1->ConnectorObjectTableOffset
				);
			}
			if (disp->v1_1->RouterObjectTableOffset) {
				populate_atom_object_table(com, &(disp->router),
					bios, disp->v1_1->RouterObjectTableOffset
				);
			}
			if (disp->v1_1->EncoderObjectTableOffset) {
				populate_atom_object_table(com, &(disp->encoder),
					bios, disp->v1_1->EncoderObjectTableOffset
				);
			}
			if (disp->v1_1->ProtectionObjectTableOffset) {
				populate_atom_object_table(com, &(disp->protection),
					bios, disp->v1_1->ProtectionObjectTableOffset
				);
			}
			if (disp->v1_1->DisplayPathTableOffset) {
				populate_display_object_path_table(com, &(disp->path),
					bios, disp->v1_1->DisplayPathTableOffset
				);
			}
	}
	return false;
}
inline static bool
populate_display_object_info_table( // v1.4, 1.5
		struct atomtree_commons* const com,
		struct atomtree_display_object* const disp
		) {
	bool err;
	if (V(1,4) == disp->ver.ver) {
		err = offchk_flex(com, disp->v1_4,
			display_path, disp->v1_4->number_of_path
		);
	} else {
		err = offchk_flex(com, disp->v1_5,
			display_path, disp->v1_5->number_of_path
		);
	}
	if (err) {
		return true;
	}

	void* const leaves = disp->leaves;
	uint8_t const number_of_path = disp->v1_4->number_of_path;
	struct atomtree_display_path_records* const records = arena_alloc(
		&(com->alloc_arena), &(com->error),
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
					com, &(records[i].connector),
					leaves + path[i].disp_recordoffset
				);
			}
			if (path[i].encoder_recordoffset) {
				populate_display_object_records(
					com, &(records[i].encoder),
					leaves + path[i].encoder_recordoffset
				);
			}
			if (path[i].extencoder_recordoffset) {
				populate_display_object_records(
					com, &(records[i].extern_encoder),
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
					com, &(records[i].connector),
					leaves + path[i].disp_recordoffset
				);
			}
		}
	}
	return false;
}

inline static void
populate_display_object(
		struct atomtree_commons* const com,
		struct atomtree_display_object* const disp,
		uint16_t const bios_offset
		) {
	if (populate_atom(com, &(disp->atom), bios_offset)) {
		return;
	}
	bool err;
	switch (disp->ver.ver) {
		case V(1,1):
		case V(1,2):
		case V(1,3): err = populate_atom_object_header(com, disp); break;
		case V(1,4):
		case V(1,5): err = populate_display_object_info_table(com, disp); break;
	}
	if (err) { // partial crawl error
		disp->ver = SET_VER(0);
	}
}
inline static void
populate_iio(
		struct atomtree_commons* const com,
		struct atomtree_iio_access* const iio,
		uint16_t const bios_offset
		) {
	if (populate_atom(com, &(iio->atom), bios_offset)) {
		return;
	}

	// iio size is wholly based off of atom_common_table_header
	assert(V(1,1) == iio->ver.ver);

	iio->num_entries = (
		(iio->table_header->structuresize - sizeof(*iio->table_header))
		/ sizeof(iio->v1_1->IOAccessSequence[0])
	);
}

inline static void
populate_umc_info(
		struct atomtree_commons* const com,
		struct atomtree_umc_info* const umc,
		uint16_t const bios_offset
		) {
	if (populate_atom(com, &(umc->atom), bios_offset)) {
		return;
	}
	size_t size = 0;
	switch (umc->ver.ver) {
		case V(3,1):  size = sizeof(*umc->v3_1);  break;
		case V(3,2):  size = sizeof(*umc->v3_2);  break;
		case V(3,3):  size = sizeof(*umc->v3_3);  break;
		case V(4,0):  size = sizeof(*umc->v4_0);  break;
	}
	if (offchk(com, umc->leaves, size)) { // partial crawl error
		umc->ver = SET_VER(0);
		return;
	}
}

inline static void
populate_dce_info(
		struct atomtree_commons* const com,
		struct atomtree_dce_info* const dce,
		uint16_t const bios_offset
		) {
	if (populate_atom(com, &(dce->atom), bios_offset)) {
		return;
	}
	size_t size = 0;
	switch (dce->ver.ver) {
		case V(4,1):  size = sizeof(*dce->v4_1);  break;
		case V(4,2):  size = sizeof(*dce->v4_2);  break;
		case V(4,3):  size = sizeof(*dce->v4_3);  break;
		case V(4,4):  size = sizeof(*dce->v4_4);  break;
		case V(4,5):  size = sizeof(*dce->v4_5);  break;
	}
	if (offchk(com, dce->leaves, size)) { // partial crawl error
		dce->ver = SET_VER(0);
		return;
	}

	switch (dce->ver.ver) {
		case V(4,4):
			dce->golden_ver.major = dce->v4_4->dc_golden_table_ver;
			if (dce->v4_4->dc_golden_table_offset) {
				dce->golden = dce->leaves + dce->v4_4->dc_golden_table_offset;
			}
			break;
		case V(4,5):
			// dc_golden_table_ver == 4096
			dce->golden_ver.ver = dce->v4_5->dc_golden_table_ver<<8;
			dce->golden = &(dce->v4_5->golden_table);
			break;
	}
	offrst(com, &(dce->golden));
}

static bool
populate_init_reg_block(
		struct atomtree_commons* const com,
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

	if (offrst(com, &(at_regblock->leaves))) {
		return true;
	}
	if (offchk(com, leaves->RegIndexBuf, leaves->RegIndexTblSize)) {
		return true;
	}
	bool err = false;

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
		struct atom_reg_setting_data_block* block;
		union atom_mc_register_setting_id* block_id;
		void* raw;
	} w;
	struct atom_reg_setting_data_block* const block_start = (
		(void*)leaves->RegIndexBuf + leaves->RegIndexTblSize
	);
	w.block = block_start;
	err = offchk(com, w.block_id);
	bool not_end = true;
	while ((!err) && not_end) {
		not_end = (0 < w.block_id->id_access);
		at_regblock->num_data_blocks += not_end;
		w.raw += at_regblock->data_block_element_size;
		err = offchk(com, w.block_id);
	}

	if (at_regblock->num_data_blocks) {
		at_regblock->data_blocks = arena_alloc(
			&(com->alloc_arena), &(com->error),
			at_regblock->num_data_blocks * sizeof(at_regblock->data_blocks[0])
		);
		w.block = block_start;
		uint8_t i = 0;
		do {
			at_regblock->data_blocks[i] = w.block;
			w.raw += at_regblock->data_block_element_size;
			i++;
		} while (i < at_regblock->num_data_blocks);
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

	return err;
}

static bool
populate_mem_adjust_table(
		struct atomtree_commons* const com,
		struct atomtree_vram_info const* const vram_info __unused,
		struct atomtree_init_reg_block* const mem_adjust_table
		) {
	if (populate_init_reg_block(com, mem_adjust_table)) {
		return true;
	}
	mem_adjust_table->reg_type = REG_BLOCK_MEM_ADJUST;

	if (COMMON_SET_UNKNOWN != mem_adjust_table->reg_set) {
		mem_adjust_table->data_sets = mem_adjust_table->data_blocks[0];
	}

	return false;
}

static bool
populate_mem_clk_patch(
		struct atomtree_commons* const com,
		struct atomtree_vram_info const* const vram_info,
		struct atomtree_init_reg_block* const mem_clk_patch
		) {
	if (populate_init_reg_block(com, mem_clk_patch)) {
		return true;
	}
	mem_clk_patch->reg_type = REG_BLOCK_MEM_CLK_PATCH;

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
			if (vram_info->memory_type == ATOM_DGPU_VRAM_TYPE_DDR3) {
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

	size_t size = mem_clk_patch->data_block_element_size;
	switch (mem_clk_patch->reg_set) {
		case TIMINGS_SET_ISLANDS_DDR3:
			size = sizeof(*mem_clk_patch->timings_set_islands_ddr3); break;
		case TIMINGS_SET_ISLANDS_GDDR5:
			size = sizeof(*mem_clk_patch->timings_set_islands_gddr5); break;
		case TIMINGS_SET_FIJI:
			size = sizeof(*mem_clk_patch->timings_set_fiji); break;
		case TIMINGS_SET_POLARIS:
			size = sizeof(*mem_clk_patch->timings_set_polaris); break;
	};

	if (size != mem_clk_patch->data_block_element_size) {
		error_assert(&(com->error), ERROR_WARNING,
			"buggy atom_init_reg_block",
			size == mem_clk_patch->data_block_element_size
		);
		mem_clk_patch->reg_set = COMMON_SET_UNKNOWN;
		return true;
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
	return false;
}

static bool
populate_mc_tile_adjust(
		struct atomtree_commons* const com,
		struct atomtree_vram_info const* const vram_info __unused,
		struct atomtree_init_reg_block* const mc_tile_adjust
		) {
	if (populate_init_reg_block(com, mc_tile_adjust)) {
		return true;
	}
	mc_tile_adjust->reg_type = REG_BLOCK_MC_TILE_ADJUST;

	if (COMMON_SET_UNKNOWN != mc_tile_adjust->reg_set) {
		mc_tile_adjust->data_sets = mc_tile_adjust->data_blocks[0];
	}

	return false;
}

static bool
populate_init_mc_phy_init(
		struct atomtree_commons* const com,
		struct atomtree_vram_info const* const vram_info __unused,
		struct atomtree_init_reg_block* const mc_phy_init
		) {
	if (populate_init_reg_block(com, mc_phy_init)) {
		return true;
	}
	mc_phy_init->reg_type = REG_BLOCK_MC_PHY_INIT;

	if (COMMON_SET_UNKNOWN != mc_phy_init->reg_set) {
		mc_phy_init->data_sets = mc_phy_init->data_blocks[0];
	}

	return false;
}


static bool
populate_umc_init_reg_block(
		struct atomtree_commons* const com,
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

	if (offrst(com, &(at_regblock->leaves))) {
		return true;
	}

	bool err = offchk_flex(com, at_regblock->leaves,
		umc_reg_list, leaves->umc_reg_num
	);
	if (err) {
		return true;
	}

	at_regblock->register_info = leaves->umc_reg_list;
	at_regblock->num_info = leaves->umc_reg_num;

	at_regblock->num_data_entries = leaves->umc_reg_num;
	at_regblock->data_block_element_size = sizeof_flex(
		((struct atom_umc_reg_setting_data_block*)0), 
		umc_reg_data, at_regblock->num_data_entries
	);

	struct atom_umc_reg_setting_data_block* const block_start = (
		(void*)leaves
		+ sizeof_flex(leaves, umc_reg_list, at_regblock->num_info)
	);
	union {
		struct atom_umc_reg_setting_data_block* block;
		union atom_mc_register_setting_id* block_id;
		void* raw;
	} w;
	w.block = block_start;
	err = offchk(com, w.block_id);
	bool not_end = true;
	while ((!err) && not_end) {
		not_end = (0 < w.block_id->id_access);
		at_regblock->num_data_blocks += not_end;
		w.raw += at_regblock->data_block_element_size;
		err = offchk(com, w.block_id);
	}

	if (at_regblock->num_data_blocks) {
		at_regblock->data_blocks = arena_alloc(
			&(com->alloc_arena), &(com->error),
			at_regblock->num_data_blocks * sizeof(at_regblock->data_blocks[0])
		);
		w.block = block_start;
		uint8_t i = 0;
		while (i < at_regblock->num_data_blocks) {
			at_regblock->data_blocks[i] = w.block;
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

	return err;
}


static bool
populate_atom_memory_timing_format(
		struct atomtree_commons* const com,
		struct atomtree_vram_info const* const vram_info,
		struct atomtree_vram_module* const vram_module,
		union atom_memory_timing_format* const timings,
		uint16_t const straps_total_size
		) {
	uint8_t table_size;
	if ((ATOM_DGPU_VRAM_TYPE_GDDR5 == vram_info->memory_type)
			|| (ATOM_DGPU_VRAM_TYPE_GDDR5_2 == vram_info->memory_type)
			) {
		if (offchk(com, &(timings->v1_1))) {
			return true;
		}
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

	vram_module->timing_format = timings;
	vram_module->num_memory_timing_format = straps_total_size / table_size;
	vram_module->memory_timing_format_total_size = straps_total_size;

	error_assert(&(com->error), ERROR_WARNING,
		"atom_memory_timing_format: buggy table sizes",
		 (vram_module->num_memory_timing_format * table_size)
		 == straps_total_size
	);
	return false;
}


inline static void
populate_vram_modules(
		struct atomtree_commons* const com,
		struct atomtree_vram_info* const vram_info,
		void* bios_offset,
		uint8_t const vram_module_num
		) {
	if (0 == vram_module_num) {
		return;
	}

	vram_info->vram_modules = arena_alloc(
		&(com->alloc_arena), &(com->error),
		vram_module_num * sizeof(vram_info->vram_modules[0])
	);

	struct atomtree_vram_module* const vmods = vram_info->vram_modules;
	uint8_t i = 0;
	switch (vram_info->vram_module_ver.ver) {
		case V(1,3): // atom_vram_module_v3. Will look very similar to v1_4
			if (! offchk(com, bios_offset, sizeof(*vmods[i].v1_3))) {
				struct atom_vram_module_v3 const* const v1_3 = bios_offset;
				vram_info->memory_type = v1_3->MemoryType;
			}
			do {
				if (offchk(com, bios_offset, sizeof(*vmods[i].v1_3))) {
					break;
				}
				vmods[i].leaves = bios_offset;
				vmods[i].gmc_bitfields_ver = SET_VER(0); // TODO
				populate_atom_memory_timing_format(
					com, vram_info, &(vmods[i]),
					vmods[i].v1_3->MemTiming,
					(vmods[i].v1_3->ModuleSize
						- offsetof(typeof(*vmods[i].v1_3), MemTiming)
					)
				);
				bios_offset += vmods[i].v1_3->ModuleSize;
				i++;
			} while (i < vram_module_num);
			break;

		case V(1,4): // atom_vram_module_v4. Will look very similar to v1_3
			if (! offchk(com, bios_offset, sizeof(*vmods[i].v1_4))) {
				struct atom_vram_module_v4 const* const v1_4 = bios_offset;
				vram_info->memory_type = v1_4->MemoryType;
			}
			do {
				if (offchk(com, bios_offset, sizeof(*vmods[i].v1_4))) {
					break;
				}
				vmods[i].leaves = bios_offset;
				vmods[i].gmc_bitfields_ver = SET_VER(0); // TODO

				populate_atom_memory_timing_format(
					com, vram_info, &(vmods[i]),
					vmods[i].v1_4->MemTiming,
					(vmods[i].v1_4->ModuleSize
						- offsetof(typeof(*vmods[i].v1_4), MemTiming)
					)
				);

				bios_offset += vmods[i].v1_4->ModuleSize;
				i++;
			} while (i < vram_module_num);
			break;

		case V(1,7):
			semver gmc_bitfields_ver = SET_VER(0);
			if (! offchk(com, bios_offset, sizeof(*vmods[i].v1_7))) {
				struct atom_vram_module_v7 const* const v1_7 = bios_offset;
				if (v1_7->ChannelMapCfg >> 24) { // infer
					// TODO explicit way to find GMC?
					// does it follow vram_module ver? doesn't seem so
					gmc_bitfields_ver = SET_VER(7,1);
				} else {
					gmc_bitfields_ver = SET_VER(6,0);
				}
				vram_info->memory_type = v1_7->MemoryType;
			}
			do {
				if (offchk(com, bios_offset, sizeof(*vmods[i].v1_7))) {
					break;
				}
				vmods[i].leaves = bios_offset;
				vmods[i].gmc_bitfields_ver = gmc_bitfields_ver;
				bios_offset += vmods[i].v1_7->ModuleSize;
				i++;
			} while (i < vram_module_num);
			break;

		case V(1,8):
			if (! offchk(com, bios_offset, sizeof(*vmods[i].v1_8))) {
				struct atom_vram_module_v8 const* const v1_8 = bios_offset;
				vram_info->memory_type = v1_8->MemoryType;
			}
			do {
				if (offchk(com, bios_offset, sizeof(*vmods[i].v1_8))) {
					break;
				}
				vmods[i].leaves = bios_offset;
				vmods[i].gmc_bitfields_ver = SET_VER(0); // TODO
				bios_offset += vmods[i].v1_8->ModuleSize;
				i++;
			} while (i < vram_module_num);
			break;

		case V(1,9):
			if (! offchk(com, bios_offset, sizeof(*vmods[i].v1_9))) {
				struct atom_vram_module_v9 const* const v1_9 = bios_offset;
				vram_info->memory_type = v1_9->memory_type;
			}
			do {
				if (offchk(com, bios_offset, sizeof(*vmods[i].v1_9))) {
					break;
				}
				vmods[i].leaves = bios_offset;
				vmods[i].gmc_bitfields_ver = SET_VER(0); // TODO
				bios_offset += vmods[i].v1_9->vram_module_size;
				i++;
			} while (i < vram_module_num);
			break;

		case V(1,10):
			if (! offchk(com, bios_offset, sizeof(*vmods[i].v1_10))) {
				struct atom_vram_module_v10 const* const v1_10 = bios_offset;
				vram_info->memory_type = v1_10->memory_type;
			}
			do {
				if (offchk(com, bios_offset, sizeof(*vmods[i].v1_10))) {
					break;
				}
				vmods[i].leaves = bios_offset;
				vmods[i].gmc_bitfields_ver = SET_VER(0); // TODO
				bios_offset += vmods[i].v1_10->vram_module_size;
				i++;
			} while (i < vram_module_num);
			break;

		case V(1,11):
			if (! offchk(com, bios_offset, sizeof(*vmods[i].v1_11))) {
				struct atom_vram_module_v11 const* const v1_11 = bios_offset;
				vram_info->memory_type = v1_11->memory_type;
			}
			do {
				if (offchk(com, bios_offset, sizeof(*vmods[i].v1_11))) {
					break;
				}
				vmods[i].leaves = bios_offset;
				vmods[i].gmc_bitfields_ver = SET_VER(0); // TODO
				bios_offset += vmods[i].v1_11->vram_module_size;
				i++;
			} while (i < vram_module_num);
			break;

		case V(3,0):
			// let populate_vram_info_* handle vram_info->memory_type
			do {
				if (offchk(com, bios_offset, sizeof(*vmods[i].v3_0))) {
					break;
				}
				vmods[i].leaves = bios_offset;
				vmods[i].gmc_bitfields_ver = SET_VER(0); // TODO

				if (vmods[i].v3_0->dram_info_offset) {
					vmods[i].dram_info = (
						bios_offset + vmods[i].v3_0->dram_info_offset
					);
					offrst(com, &(vmods[i].dram_info), 1);
				}
				if (vmods[i].v3_0->mem_tuning_offset) {
					vmods[i].mem_tuning = (
						bios_offset
						+ vmods[i].v3_0->mem_tuning_offset
					);
					offrst(com, &(vmods[i].mem_tuning), 1);
				}
				if (vmods[i].v3_0->tmrs_seq_offset) {
					vmods[i].tmrs_seq = (
						bios_offset + vmods[i].v3_0->tmrs_seq_offset
					);
					offrst(com, &(vmods[i].tmrs_seq), 1);
				}
				//bios_offset += vmods[i].v3_0->vram_module_size;
				bios_offset += sizeof(*vmods[i].v3_0);
				i++;
			} while (i < vram_module_num);
			break;

		default:
			assert(0); // TODO implement
			break;
	}
	vram_info->vram_module_num = i;
}


inline static bool
populate_gddr6_dram_data_remap(
		struct atomtree_commons* const com,
		struct atomtree_gddr6_dram_data_remap* const at_remap,
		void* const remap_ptr
		) {
	struct atom_gddr6_dram_data_remap const* const dram_data_remap = remap_ptr;
	if (offchk(com, dram_data_remap)) {
		return true;
	}
	if (offchk(com, dram_data_remap, dram_data_remap->table_size)) {
		return true;
	}
	at_remap->dram_data_remap = remap_ptr;
	at_remap->bit_byte_remap_count = (
		(dram_data_remap->table_size - sizeof(*dram_data_remap))
		/ sizeof(dram_data_remap->bit_byte_remap[0])
	);
	return false;
}

inline static bool
populate_vram_info_v1_2(
		struct atomtree_commons* const com,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_v1_2* const vi12 = &(vram_info->v1_2);
	struct atom_vram_info_v1_2* const leaves = vi12->leaves;
	if (offchk(com, leaves)) {
		return true;
	}

	if (vi12->leaves->NumOfVRAMModule) {
		vram_info->vram_module_ver = SET_VER(1,3);
		populate_vram_modules(
			com, vram_info,
			vi12->leaves->vram_module,  vi12->leaves->NumOfVRAMModule
		);
	}
	return false;
}

inline static bool
populate_vram_info_v1_3(
		struct atomtree_commons* const com,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_v1_3* const vi13 = &(vram_info->v1_3);
	struct atom_vram_info_v1_3* const leaves = vi13->leaves;
	if (offchk(com, leaves)) {
		return true;
	}

	if (vi13->leaves->NumOfVRAMModule) {
		vram_info->vram_module_ver = SET_VER(1,3);
		populate_vram_modules(
			com, vram_info,
			vi13->leaves->vram_module,  vi13->leaves->NumOfVRAMModule
		);
	}

	if (vi13->leaves->MemAdjustTblOffset) {
		vi13->mem_adjust_table.leaves =
			(void*)vi13->leaves + vi13->leaves->MemAdjustTblOffset;
		populate_init_reg_block(com, &(vi13->mem_adjust_table));
	}

	if (vi13->leaves->MemClkPatchTblOffset) {
		// TODO at least for R600, what is in here isn't timings, and gmc.h
		// doesn't decode them right.
		vi13->mem_clk_patch.leaves =
			(void*)vi13->leaves + vi13->leaves->MemClkPatchTblOffset;
		populate_init_reg_block(com, &(vi13->mem_clk_patch));
	}
	return false;
}

inline static bool
populate_vram_info_v1_4(
		struct atomtree_commons* const com,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_v1_4* const vi14 = &(vram_info->v1_4);
	struct atom_vram_info_v1_4* const leaves = vi14->leaves;
	if (offchk(com, leaves)) {
		return true;
	}

	if (vi14->leaves->NumOfVRAMModule) {
		vram_info->vram_module_ver = SET_VER(1,4);
		populate_vram_modules(
			com, vram_info,
			vi14->leaves->vram_module,  vi14->leaves->NumOfVRAMModule
		);
	}

	if (vi14->leaves->MemAdjustTblOffset) {
		vi14->mem_adjust_table.leaves =
			(void*)vi14->leaves + vi14->leaves->MemAdjustTblOffset;
		populate_init_reg_block(com, &(vi14->mem_adjust_table));
	}

	if (vi14->leaves->MemClkPatchTblOffset) {
		// TODO See populate_vram_info_v1_3
		vi14->mem_clk_patch.leaves =
			(void*)vi14->leaves + vi14->leaves->MemClkPatchTblOffset;
		populate_init_reg_block(com, &(vi14->mem_clk_patch));
	}
	return false;
}

inline static bool
populate_vram_info_v2_1(
		struct atomtree_commons* const com,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_1* const vi21 = &(vram_info->v2_1);
	struct atom_vram_info_header_v2_1* const leaves = vi21->leaves;
	if (offchk(com, leaves)) {
		return true;
	}

	if (vi21->leaves->NumOfVRAMModule) {
		vram_info->vram_module_ver = SET_VER(1,7);
		populate_vram_modules(
			com, vram_info,
			vi21->leaves->vram_module,  vi21->leaves->NumOfVRAMModule
		);
	}

	if (vi21->leaves->MemAdjustTblOffset) {
		vi21->mem_adjust_table.leaves =
			(void*)vi21->leaves + vi21->leaves->MemAdjustTblOffset;
		populate_mem_adjust_table(com, vram_info, &(vi21->mem_adjust_table));
	}

	if (vi21->leaves->MemClkPatchTblOffset) {
		vi21->mem_clk_patch.leaves =
			(void*)vi21->leaves + vi21->leaves->MemClkPatchTblOffset;
		populate_mem_clk_patch(com, vram_info, &(vi21->mem_clk_patch));
	}

	if (vi21->leaves->PerBytePresetOffset) {
		// TODO unsure what lies beyond; never seen this true.
		vi21->per_byte_preset.leaves =
			(void*)vi21->leaves + vi21->leaves->PerBytePresetOffset;
		populate_init_reg_block(com, &(vi21->per_byte_preset));
	}
	return false;
}

inline static bool
populate_vram_info_v2_2(
		struct atomtree_commons* const com,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_2* const vi22 = &(vram_info->v2_2);
	struct atom_vram_info_header_v2_2* const leaves = vi22->leaves;
	if (offchk(com, leaves)) {
		return true;
	}

	if (vi22->leaves->NumOfVRAMModule) {
		vram_info->vram_module_ver = SET_VER(1,8);
		populate_vram_modules(
			com, vram_info,
			vi22->leaves->vram_module,  vi22->leaves->NumOfVRAMModule
		);
	}

	if (vi22->leaves->MemAdjustTblOffset) {
		vi22->mem_adjust_table.leaves =
			(void*)vi22->leaves + vi22->leaves->MemAdjustTblOffset;
		populate_mem_adjust_table(com, vram_info, &(vi22->mem_adjust_table));
	}

	if (vi22->leaves->MemClkPatchTblOffset) {
		vi22->mem_clk_patch.leaves =
			(void*)vi22->leaves + vi22->leaves->MemClkPatchTblOffset;
		populate_mem_clk_patch(com, vram_info, &(vi22->mem_clk_patch));
	}

	if (vi22->leaves->McAdjustPerTileTblOffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi22->mc_tile_adjust.leaves =
			(void*)vi22->leaves + vi22->leaves->McAdjustPerTileTblOffset;
		populate_mc_tile_adjust(com, vram_info, &(vi22->mc_tile_adjust));
	}

	if (vi22->leaves->McPhyInitTableOffset) {
		vi22->mc_phy_init.leaves =
			(void*)vi22->leaves + vi22->leaves->McPhyInitTableOffset;
		populate_init_mc_phy_init(com, vram_info, &(vi22->mc_phy_init));
	}

	if (vi22->leaves->DramDataRemapTblOffset) {
		vi22->dram_data_remap =
			(void*)vi22->leaves + vi22->leaves->DramDataRemapTblOffset;
		offrst(com, &(vi22->dram_data_remap));
	}
	return false;
}

inline static bool
populate_vega_timings( // TODO collapse into UMC mem_clk_patch
		struct atomtree_commons* const com,
		struct atomtree_vram_info_header_v2_3* const vi23
		) {
	struct atomtree_umc_init_reg_block* const mem_clk_patch = &(
		vi23->mem_clk_patch
	);
	if (populate_umc_init_reg_block(com, mem_clk_patch)) {
		return true;
	}

	if (mem_clk_patch->num_data_blocks) {
		vi23->num_timing_straps = mem_clk_patch->num_data_blocks;
		vi23->mem_timings = mem_clk_patch->data_blocks[0];
	}
	switch (mem_clk_patch->data_block_element_size) {
		case sizeof(*vi23->vega10): vi23->uses_vega20_timings = false; break;
		case sizeof(*vi23->vega20): vi23->uses_vega20_timings = true;  break;
		default:
			assert(0); // don't know what else.
			vi23->num_timing_straps = 0;
			vi23->mem_timings = NULL;
			break;
	}
	return false;
}

inline static bool
populate_vram_info_v2_3(
		struct atomtree_commons* const com,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_3* const vi23 = &(vram_info->v2_3);
	struct atom_vram_info_header_v2_3* const leaves = vi23->leaves;
	if (offchk(com, leaves)) {
		return true;
	}

	if (vi23->leaves->vram_module_num) {
		vram_info->vram_module_ver = SET_VER(1,9);
		populate_vram_modules(
			com, vram_info,
			vi23->leaves->vram_module,  vi23->leaves->vram_module_num
		);
	}

	if (vi23->leaves->mem_adjust_tbloffset) {
		vi23->mem_adjust_table.leaves =
			(void*)vi23->leaves + vi23->leaves->mem_adjust_tbloffset;
		populate_umc_init_reg_block(com, &(vi23->mem_adjust_table));
	}

	if (vi23->leaves->mem_clk_patch_tbloffset) {
		vi23->mem_clk_patch.leaves =
			(void*)vi23->leaves + vi23->leaves->mem_clk_patch_tbloffset;
		populate_vega_timings(com, vi23);
	}

	if (vi23->leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi23->mc_tile_adjust.leaves =
			(void*)vi23->leaves + vi23->leaves->mc_adjust_pertile_tbloffset;
		populate_umc_init_reg_block(com, &(vi23->mc_tile_adjust));
	}

	if (vi23->leaves->mc_phyinit_tbloffset) {
		vi23->mc_phy_init.leaves =
			(void*)vi23->leaves + vi23->leaves->mc_phyinit_tbloffset;
		populate_umc_init_reg_block(com, &(vi23->mc_phy_init));
	}

	if (vi23->leaves->dram_data_remap_tbloffset) {
	// TODO does vraminfo->mc_phy_tile_num significantly affect this?
	vi23->dram_data_remap =
		(void*)vi23->leaves + vi23->leaves->dram_data_remap_tbloffset;
		offrst(com, &(vi23->dram_data_remap), 1);
	}

	if (vi23->leaves->tmrs_seq_offset) {
		// TODO what is this?
		vi23->hbm_tmrs = (void*)vi23->leaves + vi23->leaves->tmrs_seq_offset;
		offrst(com, &(vi23->hbm_tmrs), 1);
	}

	if (vi23->leaves->post_ucode_init_offset) {
		vi23->post_ucode_init.leaves =
			(void*)vi23->leaves + vi23->leaves->post_ucode_init_offset;
		populate_umc_init_reg_block(com, &(vi23->post_ucode_init));
	}
	return false;
}

inline static bool
populate_navi_timings( // TODO collapse into UMC mem_clk_patch
		struct atomtree_commons* const com,
		struct atomtree_vram_info_header_v2_4* const vi24
		) {
	struct atomtree_umc_init_reg_block* const mem_clk_patch = &(
		vi24->mem_clk_patch
	);
	if (populate_umc_init_reg_block(com, mem_clk_patch)) {
		return true;
	}

	if (sizeof(*vi24->navi1_gddr6_timings) != mem_clk_patch->data_block_element_size) {
		assert(0); // don't know what else.
		return false;
	}
	if (mem_clk_patch->num_data_blocks) {
		vi24->num_timing_straps = mem_clk_patch->num_data_blocks;
		vi24->navi1_gddr6_timings = (void*) mem_clk_patch->data_blocks[0];
	}

	return false;
}

inline static bool
populate_vram_info_v2_4(
		struct atomtree_commons* const com,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_4* const vi24 = &(vram_info->v2_4);
	struct atom_vram_info_header_v2_4* const leaves = vram_info->leaves;
	if (offchk(com, leaves)) {
		return true;
	}

	if (leaves->vram_module_num) {
		vram_info->vram_module_ver = SET_VER(1,10);
		populate_vram_modules(
			com, vram_info,
			leaves->vram_module,  leaves->vram_module_num
		);
	}

	if (leaves->mem_adjust_tbloffset) {
		vi24->mem_adjust_table.leaves =
			(void*)leaves + leaves->mem_adjust_tbloffset;
		populate_umc_init_reg_block(com, &(vi24->mem_adjust_table));
	}

	if (leaves->mem_clk_patch_tbloffset) {
		vi24->mem_clk_patch.leaves =
			(void*)leaves + leaves->mem_clk_patch_tbloffset;
		populate_navi_timings(com, vi24);
	}

	if (leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi24->mc_tile_adjust.leaves =
			(void*)leaves + leaves->mc_adjust_pertile_tbloffset;
		populate_umc_init_reg_block(com, &(vi24->mc_tile_adjust));
	}

	if (leaves->mc_phyinit_tbloffset) {
		vi24->mc_phy_init.leaves =
			(void*)leaves + leaves->mc_phyinit_tbloffset;
		populate_umc_init_reg_block(com, &(vi24->mc_phy_init));
	}

	if (leaves->dram_data_remap_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi24->dram_data_remap =
			(void*)leaves + leaves->dram_data_remap_tbloffset;
		offrst(com, &(vi24->dram_data_remap), 1);
	}

	if (leaves->post_ucode_init_offset) {
		vi24->post_ucode_init.leaves =
			(void*)leaves + leaves->post_ucode_init_offset;
		populate_umc_init_reg_block(com, &(vi24->post_ucode_init));
	}
	return false;
}

inline static bool
populate_vram_info_v2_5(
		struct atomtree_commons* const com,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_5* const vi25 = &(vram_info->v2_5);
	struct atom_vram_info_header_v2_5* const leaves = vram_info->leaves;
	if (offchk(com, leaves)) {
		return true;
	}

	if (leaves->vram_module_num) {
		vram_info->vram_module_ver = SET_VER(1,11);
		populate_vram_modules(
			com, vram_info,
			leaves->vram_module,  leaves->vram_module_num
		);
	}

	if (leaves->mem_adjust_tbloffset) {
		vi25->mem_adjust_table.leaves =
			(void*)leaves + leaves->mem_adjust_tbloffset;
		populate_umc_init_reg_block(com, &(vi25->mem_adjust_table));
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
		populate_umc_init_reg_block(com, &(vi25->mc_tile_adjust));
	}

	if (leaves->mc_phyinit_tbloffset) {
		vi25->mc_phy_init.leaves =
			(void*)leaves + leaves->mc_phyinit_tbloffset;
		populate_umc_init_reg_block(com, &(vi25->mc_phy_init));
	}

	if (leaves->dram_data_remap_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		populate_gddr6_dram_data_remap(
			com,  &vi25->dram_data_remap,
			(void*)leaves + leaves->dram_data_remap_tbloffset
		);
	}

	if (leaves->post_ucode_init_offset) {
		vi25->post_ucode_init.leaves =
			(void*)leaves + leaves->post_ucode_init_offset;
		populate_umc_init_reg_block(com, &(vi25->post_ucode_init));
	}

	if (leaves->strobe_mode_patch_tbloffset) {
		vi25->strobe_mode_patch.leaves =
			(void*)leaves + leaves->strobe_mode_patch_tbloffset;
		populate_umc_init_reg_block(com, &(vi25->strobe_mode_patch));
	}
	return false;
}

inline static bool
populate_vram_info_v2_6(
		struct atomtree_commons* const com,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v2_6* const vi26 = &(vram_info->v2_6);
	struct atom_vram_info_header_v2_6* const leaves = vram_info->leaves;
	if (offchk(com, leaves)) {
		return true;
	}

	if (leaves->vram_module_num) {
		vram_info->vram_module_ver = SET_VER(1,9);
		populate_vram_modules(
			com, vram_info,
			leaves->vram_module,  leaves->vram_module_num
		);
	}

	if (leaves->mem_adjust_tbloffset) {
		vi26->mem_adjust_table.leaves =
			(void*)leaves + leaves->mem_adjust_tbloffset;
		populate_umc_init_reg_block(com, &(vi26->mem_adjust_table));
	}

	if (leaves->mem_clk_patch_tbloffset) {
		vi26->mem_clk_patch.leaves =
			(void*)leaves + leaves->mem_clk_patch_tbloffset;
		populate_umc_init_reg_block(com, &(vi26->mem_clk_patch));
	}

	if (leaves->mc_adjust_pertile_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		vi26->mc_tile_adjust.leaves =
			(void*)leaves + leaves->mc_adjust_pertile_tbloffset;
		populate_umc_init_reg_block(com, &(vi26->mc_tile_adjust));
	}

	if (leaves->mc_phyinit_tbloffset) {
		vi26->mc_phy_init.leaves =
			(void*)leaves + leaves->mc_phyinit_tbloffset;
		populate_umc_init_reg_block(com, &(vi26->mc_phy_init));
	}

	if (leaves->tmrs_seq_offset) {
		// TODO what is this?
		vi26->tmrs_seq = (void*)leaves + leaves->tmrs_seq_offset;
		offrst(com, &(vi26->tmrs_seq), 1);
	}

	if (leaves->dram_data_remap_tbloffset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		populate_gddr6_dram_data_remap(
			com,  &vi26->dram_data_remap,
			(void*)leaves + leaves->dram_data_remap_tbloffset
		);
	}

	if (leaves->post_ucode_init_offset) {
		vi26->post_ucode_init.leaves =
			(void*)leaves + leaves->post_ucode_init_offset;
		populate_umc_init_reg_block(com, &(vi26->post_ucode_init));
	}
	return false;
}

inline static bool
populate_vram_info_v3_0( // TODO finish this
		struct atomtree_commons* const com,
		struct atomtree_vram_info* const vram_info
		) {
	struct atomtree_vram_info_header_v3_0* const vi30 = &(vram_info->v3_0);
	struct atom_vram_info_header_v3_0* const leaves = vram_info->leaves;
	if (offchk(com, leaves)) {
		return true;
	}

	vram_info->memory_type = leaves->memory_type;

	if (leaves->vram_module_num) {
		vram_info->vram_module_ver = SET_VER(3,0);
		populate_vram_modules(
			com, vram_info,
			leaves->vram_module, leaves->vram_module_num
		);
	}

	if (leaves->mem_tuning_table_offset) {
		vi30->mem_tuning =
			(void*)leaves + leaves->mem_tuning_table_offset;
		offrst(com, &(vi30->mem_tuning), 1);
	}

	if (leaves->dram_info_table_offset) {
		vi30->dram_info =
			(void*)leaves + leaves->dram_info_table_offset;
		offrst(com, &(vi30->dram_info), 1);
	}

	if (leaves->tmrs_table_offset) {
		vi30->tmrs_seq = (void*)leaves + leaves->tmrs_table_offset;
		offrst(com, &(vi30->tmrs_seq), 1);
	}

	if (leaves->mc_init_table_offset) {
		vi30->mc_init.leaves =
			(void*)leaves + leaves->mc_init_table_offset;
		populate_umc_init_reg_block(com, &(vi30->mc_init));
	}

	if (leaves->dram_data_remap_table_offset) {
		//TODO does vraminfo->mc_phy_tile_num significantly affect this?
		populate_gddr6_dram_data_remap(
			com,  &vi30->dram_data_remap,
			(void*)leaves + leaves->dram_data_remap_table_offset
		);
	}

	if (leaves->umc_emuinit_table_offset) {
		vi30->umc_emuinit.leaves =
			(void*)leaves + leaves->umc_emuinit_table_offset;
		populate_umc_init_reg_block(com, &(vi30->umc_emuinit));
	}

	if (leaves->reserved_sub_table_offset[0]) {
		vi30->rsvd_tables[0] =
			(void*)leaves + leaves->reserved_sub_table_offset[0];
		offrst(com, &(vi30->rsvd_tables[0]), 1);
	}
	if (leaves->reserved_sub_table_offset[1]) {
		vi30->rsvd_tables[1] =
			(void*)leaves + leaves->reserved_sub_table_offset[1];
		offrst(com, &(vi30->rsvd_tables[1]), 1);
	}
	return false;
}

inline static void
populate_vram_info(
		struct atomtree_commons* const com,
		struct atomtree_vram_info* const vram_info,
		uint16_t const bios_offset
		) {
	if (populate_atom(com, &(vram_info->atom), bios_offset)) {
		return;
	}
	bool err = false;
	switch (vram_info->ver.ver) {
		case V(1,2): err = populate_vram_info_v1_2(com, vram_info); break;
		case V(1,3): err = populate_vram_info_v1_3(com, vram_info); break;
		case V(1,4): err = populate_vram_info_v1_4(com, vram_info); break;
		case V(2,1): err = populate_vram_info_v2_1(com, vram_info); break;
		case V(2,2): err = populate_vram_info_v2_2(com, vram_info); break;
		case V(2,3): err = populate_vram_info_v2_3(com, vram_info); break;
		case V(2,4): err = populate_vram_info_v2_4(com, vram_info); break;
		case V(2,5): err = populate_vram_info_v2_5(com, vram_info); break;
		case V(2,6): err = populate_vram_info_v2_6(com, vram_info); break;
		case V(3,0): err = populate_vram_info_v3_0(com, vram_info); break;
		default: break;
	}
	if (err) { // partial crawl error
		vram_info->ver = SET_VER(0);
	}
}

inline static bool
populate_voltageobject_info_v1_1(
		struct atomtree_commons* const com,
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

	error_assert(&(com->error), ERROR_WARNING,
		"voltageobject_info_v1_1 buggy table sizes",
		vobj.raw == end
	);
	vo_info->num_voltage_objects -= (vobj.raw != end);

	if (vo_info->num_voltage_objects) {
		struct atomtree_voltage_object* const voltage_objects = arena_alloc(
			&(com->alloc_arena), &(com->error),
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
	return false;
}

inline static bool
populate_voltageobject_info_v1_2(
		struct atomtree_commons* const com,
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

	error_assert(&(com->error), ERROR_WARNING,
		"voltageobject_info_v1_2 buggy table sizes",
		vobj.raw == end
	);
	vo_info->num_voltage_objects -= (vobj.raw != end);

	if (vo_info->num_voltage_objects) {
		struct atomtree_voltage_object* const voltage_objects = arena_alloc(
			&(com->alloc_arena), &(com->error),
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
	return false;
}

inline static bool
populate_voltageobject_info_v3_1(
		struct atomtree_commons* const com,
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

	error_assert(&(com->error), ERROR_WARNING,
		"voltageobject_info_v3_1 buggy table sizes",
		vobj.raw == end
	);
	vo_info->num_voltage_objects -= (vobj.raw != end);

	if (vo_info->num_voltage_objects) {
		struct atomtree_voltage_object* const voltage_objects = arena_alloc(
			&(com->alloc_arena), &(com->error),
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
	return false;
}


inline static bool
populate_voltageobject_info_v4_1(
		struct atomtree_commons* const com,
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

	error_assert(&(com->error), ERROR_WARNING,
		"voltageobject_info_v4_1 buggy table sizes",
		vobj.raw == end
	);
	vo_info->num_voltage_objects -= (vobj.raw != end); // buggy V620

	if (vo_info->num_voltage_objects) {
		struct atomtree_voltage_object* const voltage_objects = arena_alloc(
			&(com->alloc_arena), &(com->error),
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
	return false;
}


inline static void
populate_voltageobject_info(
		struct atomtree_commons* const com,
		struct atomtree_voltageobject_info* const vo_info,
		uint16_t const bios_offset
		) {
	if (populate_atom(com, &(vo_info->atom), bios_offset)) {
		return;
	}
	bool err = false;
	switch (vo_info->ver.ver) {
		case V(1,1): err = populate_voltageobject_info_v1_1(com, vo_info);break;
		case V(1,2): err = populate_voltageobject_info_v1_2(com, vo_info);break;
		case V(3,1): err = populate_voltageobject_info_v3_1(com, vo_info);break;
		case V(4,2): // hopefully v4_2 is the same
		case V(4,1): err = populate_voltageobject_info_v4_1(com, vo_info);break;
		case V(1,0): assert(0);
		default: break;
	}
	if (err) { // partial crawl error
		vo_info->ver = SET_VER(0);
	}
}


inline static bool
populate_datatable_v1_1(
		struct atomtree_commons* const com,
		struct atomtree_master_datatable* const data_table
		) {
	void* const bios = com->bios;
	struct atomtree_master_datatable_v1_1* const dt11 = &(data_table->v1_1);
	struct atom_master_data_table_v1_1* const leaves = data_table->leaves;
	if (offchk(com, leaves)) {
		return true;
	}

	populate_atom(com, &(dt11->utilitypipeline.atom), leaves->UtilityPipeLine);

	if (leaves->MultimediaCapabilityInfo) {
		dt11->multimedia_capability_info = (
			bios + leaves->MultimediaCapabilityInfo
		);
		offrst_atom_table(com, &(dt11->multimedia_capability_info));

	}

	if (leaves->MultimediaConfigInfo) {
		dt11->multimedia_config_info =
			bios + leaves->MultimediaConfigInfo;
		offrst_atom_table(com, &(dt11->multimedia_config_info));
	}

	if (leaves->StandardVESA_Timing) {
		dt11->vesa_timing = bios + leaves->StandardVESA_Timing;
		offrst_atom_table(com, &(dt11->vesa_timing));
	}

	populate_firmwareinfo(com, &(dt11->firmwareinfo), leaves->FirmwareInfo);

	if (leaves->PaletteData) {
		dt11->palette_data = bios + leaves->PaletteData;
		offrst(com, &(dt11->palette_data), 1);
	}

	populate_lcd_info(com, &(dt11->lcd_info), leaves->LCD_Info);

	if (leaves->DIGTransmitterInfo) {
		dt11->dig_transmitter_info = bios + leaves->DIGTransmitterInfo;
		offrst(com, &(dt11->dig_transmitter_info), 1);
	}

	if (leaves->ATV_SMU_Info) {
		struct atom_common_table_header const* header = (
			bios + leaves->ATV_SMU_Info
		);
		if (1 == header->format_revision) {
			populate_analog_tv_info(
				com, &(dt11->analog_tv), leaves->ATV_SMU_Info
			);
		} else {
			populate_smu_info(com, &(dt11->smu_info), leaves->ATV_SMU_Info);
		}
	}

	if (leaves->SupportedDevicesInfo) {
		dt11->supported_devices_info = bios + leaves->SupportedDevicesInfo;
		offrst(com, &(dt11->supported_devices_info), 1);
	}

	if (leaves->GPIO_I2C_Info) {
		dt11->gpio_i2c_info = bios + leaves->GPIO_I2C_Info;
		offrst(com, &(dt11->gpio_i2c_info), 1);
	}

	populate_vram_usagebyfirmware(
		com, &(dt11->vram_usagebyfirmware), leaves->VRAM_UsageByFirmware
	);

	populate_gpio_pin_lut(com, &(dt11->gpio_pin_lut), leaves->GPIO_Pin_LUT);

	if (leaves->VESA_ToInternalModeLUT) {
		dt11->vesa_to_internal_mode = bios + leaves->VESA_ToInternalModeLUT;
		offrst(com, &(dt11->vesa_to_internal_mode), 1);
	}

	populate_gfx_info(com, &(dt11->gfx_info), leaves->GFX_Info);

	populate_ppt(com, &(dt11->powerplayinfo), leaves->PowerPlayInfo);

	if (leaves->GPUVirtualizationInfo) {
		dt11->gpu_virtualization_info = bios + leaves->GPUVirtualizationInfo;
		offrst(com, &(dt11->gpu_virtualization_info), 1);
	}

	if (leaves->SaveRestoreInfo) {
		dt11->save_restore_info = bios + leaves->SaveRestoreInfo;
		offrst(com, &(dt11->save_restore_info), 1);
	}

	if (leaves->PPLL_SS_Info) {
		dt11->ppll_ss_info = bios + leaves->PPLL_SS_Info;
		offrst(com, &(dt11->ppll_ss_info), 1);
	}

	if (leaves->OemInfo) {
		dt11->oem_info = bios + leaves->OemInfo;
		offrst(com, &(dt11->oem_info), 1);
	}

	if (leaves->XTMDS_Info) {
		dt11->xtmds_info = bios + leaves->XTMDS_Info;
		offrst(com, &(dt11->xtmds_info), 1);
	}

	if (leaves->MclkSS_Info) {
		dt11->mclk_ss_info = bios + leaves->MclkSS_Info;
		offrst(com, &(dt11->mclk_ss_info), 1);
	}

	populate_display_object(
		com, &(dt11->display_object), leaves->Object_Header
	);


	populate_iio(com, &(dt11->iio), leaves->IndirectIOAccess);

	if (leaves->MC_InitParameter) {
		dt11->mc_init_parameter = bios + leaves->MC_InitParameter;
		offrst(com, &(dt11->mc_init_parameter), 1);
	}

	if (leaves->ASIC_VDDC_Info) {
		dt11->asic_vddc_info = bios + leaves->ASIC_VDDC_Info;
		offrst(com, &(dt11->asic_vddc_info), 1);
	}

	if (leaves->ASIC_InternalSS_Info) {
		dt11->asic_internal_ss_info = bios + leaves->ASIC_InternalSS_Info;
		offrst(com, &(dt11->asic_internal_ss_info), 1);
	}

	if (leaves->TV_VideoMode) {
		dt11->tv_video_mode = bios + leaves->TV_VideoMode;
		offrst(com, &(dt11->tv_video_mode), 1);
	}

	populate_vram_info(com, &(dt11->vram_info), leaves->VRAM_Info);

	if (leaves->MemoryTrainingInfo) {
		dt11->memory_training_info = bios + leaves->MemoryTrainingInfo;
		offrst(com, &(dt11->memory_training_info), 1);
	}

	if (leaves->IntegratedSystemInfo) {
		dt11->integrated_system_info = bios + leaves->IntegratedSystemInfo;
		offrst(com, &(dt11->integrated_system_info), 1);
	}

	if (leaves->ASIC_ProfilingInfo) {
		dt11->asic_profiling_info = bios + leaves->ASIC_ProfilingInfo;
		offrst(com, &(dt11->asic_profiling_info), 1);
	}

	populate_voltageobject_info(
		com, &(dt11->voltageobject_info), leaves->VoltageObjectInfo
	);

	if (leaves->PowerSourceInfo) {
		dt11->power_source_info = bios + leaves->PowerSourceInfo;
		offrst(com, &(dt11->power_source_info), 1);
	}

	if (leaves->ServiceInfo) {
		dt11->service_info = bios + leaves->ServiceInfo;
		offrst(com, &(dt11->service_info), 1);
	}
	return false;
}

inline static void
atomtree_datatable_v2_1_populate_sw_datatables(
		struct atomtree_commons* const com,
		struct atomtree_master_datatable_v2_1* const dt21
		) {
	struct atom_master_data_table_v2_1* const leaves = dt21->leaves;

	populate_atom(com, &(dt21->sw_datatable3.atom),  leaves->sw_datatable3);
	populate_atom(com, &(dt21->sw_datatable5.atom),  leaves->sw_datatable5);
	populate_atom(com, &(dt21->sw_datatable7.atom),  leaves->sw_datatable7);
	populate_atom(com, &(dt21->sw_datatable9.atom),  leaves->sw_datatable9);
	populate_atom(com, &(dt21->sw_datatable10.atom), leaves->sw_datatable10);
	populate_atom(com, &(dt21->sw_datatable13.atom), leaves->sw_datatable13);
	populate_atom(com, &(dt21->sw_datatable16.atom), leaves->sw_datatable16);
	populate_atom(com, &(dt21->sw_datatable17.atom), leaves->sw_datatable17);
	populate_atom(com, &(dt21->sw_datatable18.atom), leaves->sw_datatable18);
	populate_atom(com, &(dt21->sw_datatable19.atom), leaves->sw_datatable19);
	populate_atom(com, &(dt21->sw_datatable20.atom), leaves->sw_datatable20);
	populate_atom(com, &(dt21->sw_datatable21.atom), leaves->sw_datatable21);
	populate_atom(com, &(dt21->sw_datatable25.atom), leaves->sw_datatable25);
	populate_atom(com, &(dt21->sw_datatable26.atom), leaves->sw_datatable26);
	populate_atom(com, &(dt21->sw_datatable29.atom), leaves->sw_datatable29);
	populate_atom(com, &(dt21->sw_datatable33.atom), leaves->sw_datatable33);
	populate_atom(com, &(dt21->sw_datatable34.atom), leaves->sw_datatable34);
}
inline static bool
populate_datatable_v2_1(
		struct atomtree_commons* const com,
		struct atomtree_master_datatable* const data_table
		) {
	void* const bios = com->bios;
	struct atomtree_master_datatable_v2_1* const dt21 = &(data_table->v2_1);
	struct atom_master_data_table_v2_1* const leaves = data_table->leaves;
	if (offchk(com, leaves)) {
		return true;
	}

	populate_atom(com, &(dt21->utilitypipeline.atom), leaves->utilitypipeline);

	if (leaves->multimedia_info) {
		dt21->multimedia_info = bios + leaves->multimedia_info;
		offrst_atom_table(com, &(dt21->multimedia_info));
	}

	populate_smc_dpm_info(com, &(dt21->smc_dpm_info), leaves->smc_dpm_info);

	populate_firmwareinfo(com, &(dt21->firmwareinfo), leaves->firmwareinfo);

	populate_lcd_info(com, &(dt21->lcd_info), leaves->lcd_info);

	populate_smu_info(com, &(dt21->smu_info), leaves->smu_info);

	populate_vram_usagebyfirmware(
		com, &(dt21->vram_usagebyfirmware), leaves->vram_usagebyfirmware
	);

	populate_gpio_pin_lut(com, &(dt21->gpio_pin_lut), leaves->gpio_pin_lut);

	populate_gfx_info(com, &(dt21->gfx_info), leaves->gfx_info);

	populate_ppt(com, &(dt21->powerplayinfo), leaves->powerplayinfo);

	populate_display_object(
		com, &(dt21->display_object), leaves->displayobjectinfo
	);

	populate_iio(com, &(dt21->iio), leaves->indirectioaccess);

	populate_umc_info(com, &(dt21->umc_info), leaves->umc_info);

	populate_dce_info(com, &(dt21->dce_info), leaves->dce_info);


	populate_vram_info(com, &(dt21->vram_info), leaves->vram_info);

	//integratedsysteminfo
	//asic_profiling_info

	populate_voltageobject_info(
		com, &(dt21->voltageobject_info), leaves->voltageobject_info
	);

	atomtree_datatable_v2_1_populate_sw_datatables(com, dt21);
	return false;
}

inline static void
populate_datatables(
		//struct atomtree_master_datatable* const data_table,
		struct atomtree_commons* const com,
		uint16_t const bios_offset
		) {
	struct atomtree_master_datatable* const data_table = &(
		com->atree->data_table
	);
	if (populate_atom(com, &(data_table->atom), bios_offset)) {
		return;
	}
	bool err = false;
	switch (data_table->ver.ver) {
		case V(1,1): err = populate_datatable_v1_1(com, data_table); break;
		case V(2,1): err = populate_datatable_v2_1(com, data_table); break;
		default: assert(0); break;
	}
	if (err) { // partial crawl error
		data_table->ver = SET_VER(0);
	}
}

inline static bool
populate_psp_rsa(
		struct atomtree_commons* const com,
		struct atomtree_psp_rsa* const rsa
		) {
	if (offchk(com, rsa->header)) {
		return true;
	}
	size_t const size = (
		sizeof(*rsa->header)
		+ rsa->header->public_exponent_size
		+ rsa->header->modulus_size
	);
	if (offchk(com, rsa->header, size)) {
		return true;
	}

	assert(rsa->header->modulus_size == rsa->header->public_exponent_size);
	void* walker = rsa->raw + sizeof(struct psp_rsa_key_header);
	rsa->public_exponent = walker;
	walker += rsa->header->public_exponent_size;
	rsa->modulus = walker;
	return false;
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
		struct atomtree_commons* const com,
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
		if (offrst(com, &(dies[die_i].header))) {
			continue;
		}

		uint16_t num_ips = dies[die_i].header->num_ips;
		if (0 == num_ips) {
			assert(0);
			continue;
		}
		struct atomtree_discovery_ip_entry* ips = arena_alloc(
			&(com->alloc_arena), &(com->error),
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
inline static bool
populate_discovery_table(
		struct atomtree_commons* const com,
		struct atomtree_discovery_table* const dis
		) {
	if (offchk(com, dis->blob)) {
		return true;
	}
	union {
		void* raw;
		struct discovery_binary_header* bin;
	} const b = {
		.bin = & (dis->blob->binary_header)
	};
	struct discovery_table_info const* const table_list = b.bin->table_list;

	dis->binary_ver = SET_VER(b.bin->version_major, b.bin->version_minor);

	// TODO finish offset checks
	if (table_list[DISCOVERY_IP_DISCOVERY].offset) {
		dis->ip_discovery = b.raw + table_list[DISCOVERY_IP_DISCOVERY].offset;
		if (! offrst(com, &(dis->ip_discovery))) {
			dis->ip_ver = SET_VER(dis->ip_discovery->version);
			populate_discovery_table_ip_dies(com, dis, b.raw);
		}
	}

	if (table_list[DISCOVERY_GC].offset) {
		dis->gc_info = b.raw + table_list[DISCOVERY_GC].offset;
		if (! offrst(com, &(dis->gc_info), sizeof(dis->gc_info->header))) {
			dis->gc_ver = SET_VER(
				dis->gc_info->header.version_major,
				dis->gc_info->header.version_minor
			);
		}
	}
	if (table_list[DISCOVERY_HARVEST_INFO].offset) {
		dis->harvest = b.raw + table_list[DISCOVERY_HARVEST_INFO].offset;
		if (! offrst(com, &(dis->harvest))) {
			dis->harvest_ver = SET_VER(dis->harvest->header.version);
		}
	}
	if (table_list[DISCOVERY_VCN_INFO].offset) {
		dis->vcn_info = b.raw + table_list[DISCOVERY_VCN_INFO].offset;
		if (! offrst(com, &(dis->vcn_info))) {
			dis->vcn_ver = SET_VER(
				dis->vcn_info->header.version_major,
				dis->vcn_info->header.version_minor
			);
		}
	}
	if (table_list[DISCOVERY_MALL_INFO].offset) {
		dis->mall_info = b.raw + table_list[DISCOVERY_MALL_INFO].offset;
		if (! offrst(com, &(dis->mall_info), sizeof(dis->mall_info->header))) {
			dis->mall_ver = SET_VER(
				dis->mall_info->header.version_major,
				dis->mall_info->header.version_minor
			);
		}
	}
	if (table_list[DISCOVERY_NPS_INFO].offset) {
		dis->nps_info = b.raw + table_list[DISCOVERY_NPS_INFO].offset;
		if (! offrst(com, &(dis->nps_info))) {
			dis->nps_ver = SET_VER(
				dis->nps_info->header.version_major,
				dis->nps_info->header.version_minor
			);
		}
	}
	return false;
}

inline static bool
populate_psp_fw_payload_type(
		struct atomtree_commons* const com,
		struct psp_directory_entry const* const pspentry,
		struct atomtree_psp_directory_entries* const fw_entry,
		void* const bios
		) {
	if (offchk(com, bios, pspentry->size)) {
		return true;
	}
	fw_entry->raw = bios;

	bool heuristic = false;
	switch (pspentry->type) {
		case AMD_PUBLIC_KEY:
		case BIOS_RTM_SIGNATURE:
		case AMD_SEV_DATA:
			fw_entry->has_fw_header = false;
			fw_entry->type = PSPFW_RSA;
			break;
		default:
			heuristic = true;
			break;
	}

	if (heuristic) { // hack our way to something
		fw_entry->has_fw_header = (
			(sizeof(struct amd_fw_header) <= pspentry->size)
			&& (fw_entry->header->fw_type == pspentry->type)
		);
		if (fw_entry->has_fw_header) {
			bool const is_discovery = (
				(sizeof(struct discovery_fw_blob) <= pspentry->size)
				&& (
					DISCOVERY_BINARY_SIGNATURE
					== fw_entry->discovery.blob->binary_header.signature
				)
				
			);
			if (is_discovery) {
				fw_entry->type = PSPFW_DISCOVERY;
			}
		}
	}

	bool err = false;
	switch (fw_entry->type) {
		case PSPFW_RSA:
			err = populate_psp_rsa(com, &(fw_entry->rsa));
			break;
		case PSPFW_DISCOVERY: 
			err = populate_discovery_table(com, &(fw_entry->discovery));
			break;
	}
	if (err) {
		fw_entry->type = PSPFW_UNKNOWN;
	}
	return err;
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
		struct atomtree_commons* const com,
		struct atomtree_psp_directory* const pspdir,
		uint32_t const bios_offset
		) {
	void* const bios = com->bios;
	if (0 == bios_offset) {
		return;
	}
	union {
		void* raw;
		struct psp_directory* dir;
	} const d = {
		.raw = bios + bios_offset
	};
	if (offchk_flex(com, d.dir, pspentry, d.dir->header.totalentries)) {
		return;
	}
	if (PSP_COOKIE != d.dir->header.pspcookie.num) {
		return;
	};

	pspdir->directory = d.dir;

	uint32_t const totalentries = d.dir->header.totalentries;
	if (0 == totalentries) {
		return;

	}
	struct atomtree_psp_directory_entries* const fw_entries = arena_alloc(
		&(com->alloc_arena), &(com->error),
		totalentries * sizeof(pspdir->fw_entries[0])
	);
	pspdir->fw_entries = fw_entries;
	void* moded_start[4] = { // see union psp_directory_entry_address
		com->atree->alloced_bios, // physical
		bios, // bios; unsure, untested
		d.raw, // dir header; unsure, untested

		com->atree->alloced_bios, // partition; incorrect
		// partition seems per-entry ad-hoc; but relative to what?
	};
	for (uint32_t i=0; i < totalentries; i++) {
		union psp_directory_entry_address addr = d.dir->pspentry[i].address;
		if (3 == addr.mode) {
			continue; // see moded_start
		}
		populate_psp_fw_payload_type(
			com, &(d.dir->pspentry[i]), &(fw_entries[i]),
			moded_start[addr.mode] + addr.address
		);
	}
}


inline static bool
populate_atom_rom_header_v1_1(
		struct atomtree_commons* const com,
		struct atomtree_rom_header* const rom
		) {
	struct atom_tree* const atree = com->atree;
	struct atom_rom_header_v1_1* const leaves = rom->v1_1;
	void* const bios = com->bios;
	if (offchk(com, leaves)) {
		return true;
	}

	assert(ATOM_SIGNATURE == rom->v1_1->FirmWareSignature.num);

	if (leaves->ProtectedModeInfoOffset) {
		atree->protected_mode = bios + leaves->ProtectedModeInfoOffset;
		offrst(com, &(atree->protected_mode), 1);
	}
	if (leaves->ConfigFilenameOffset) {
		atree->config_filename = bios + leaves->ConfigFilenameOffset;
		offrst(com, &(atree->config_filename), 1);
	}
	if (leaves->CRC_BlockOffset) {
		atree->crc_block = bios + leaves->CRC_BlockOffset;
		offrst(com, &(atree->crc_block));
	}
	if (leaves->BIOS_BootupMessageOffset) {
		atree->bootup_mesage = bios + leaves->BIOS_BootupMessageOffset;
		offrst(com, &(atree->bootup_mesage), 1);
	}
	if (leaves->Int10Offset) {
		atree->int10 = bios + leaves->Int10Offset;
		offrst(com, &(atree->int10), 1);
	}
	if (leaves->PCI_InfoOffset) {
		atree->pci_info = bios + leaves->PCI_InfoOffset;
		offrst(com, &(atree->pci_info), 1);
	}

	//rom->data_table = &(atree->data_table);
	populate_datatables(com, leaves->MasterDataTableOffset);

	return false;
}

inline static bool
populate_atom_rom_header_v2_1(
		struct atomtree_commons* const com,
		struct atomtree_rom_header* const rom
		) {
	struct atom_tree* const atree = com->atree;
	struct atom_rom_header_v2_1* const leaves = rom->v2_1;
	void* const bios = com->bios;
	if (offchk(com, leaves)) {
		return true;
	}

	assert(ATOM_SIGNATURE == rom->v2_1->FirmWareSignature.num);

	if (leaves->ProtectedModeInfoOffset) {
		atree->protected_mode = bios + leaves->ProtectedModeInfoOffset;
		offrst(com, &(atree->protected_mode), 1);
	}
	if (leaves->ConfigFilenameOffset) {
		atree->config_filename = bios + leaves->ConfigFilenameOffset;
		offrst(com, &(atree->config_filename), 1);
	}
	if (leaves->CRC_BlockOffset) {
		atree->crc_block = bios + leaves->CRC_BlockOffset;
		offrst(com, &(atree->crc_block));
	}
	if (leaves->BIOS_BootupMessageOffset) {
		atree->bootup_mesage = bios + leaves->BIOS_BootupMessageOffset;
		offrst(com, &(atree->bootup_mesage), 1);
	}
	if (leaves->Int10Offset) {
		atree->int10 = bios + leaves->Int10Offset;
		offrst(com, &(atree->int10), 1);
	}
	if (leaves->PCI_InfoOffset) {
		atree->pci_info = bios + leaves->PCI_InfoOffset;
		offrst(com, &(atree->pci_info), 1);
	}

	populate_psp_directory_table(
		com, &(atree->psp_directory), leaves->PSPDirTableOffset
	);

	//rom->data_table = &(atree->data_table);
	populate_datatables(com, leaves->MasterDataTableOffset);

	return false;
}
inline static bool
populate_atom_rom_header_v2_2(
		struct atomtree_commons* const com,
		struct atomtree_rom_header* const rom
		) {
	struct atom_tree* const atree = com->atree;
	struct atom_rom_header_v2_2* const leaves = rom->v2_2;
	void* const bios = com->bios;
	if (offchk(com, leaves)) {
		return true;
	}

	assert(ATOM_SIGNATURE == rom->v2_2->signature.num);

	if (leaves->protectedmodeoffset) {
		atree->protected_mode = bios + leaves->protectedmodeoffset;
		offrst(com, &(atree->protected_mode), 1);
	}
	if (leaves->configfilenameoffset) {
		atree->config_filename = bios + leaves->configfilenameoffset;
		offrst(com, &(atree->config_filename), 1);
	}
	if (leaves->crc_block_offset) {
		atree->crc_block = bios + leaves->crc_block_offset;
		offrst(com, &(atree->crc_block));
	}
	if (leaves->vbios_bootupmessageoffset) {
		atree->bootup_mesage = bios + leaves->vbios_bootupmessageoffset;
		offrst(com, &(atree->bootup_mesage), 1);
	}
	if (leaves->int10_offset) {
		atree->int10 = bios + leaves->int10_offset;
		offrst(com, &(atree->int10), 1);
	}
	if (leaves->pci_info_offset) {
		atree->pci_info = bios + leaves->pci_info_offset;
		offrst(com, &(atree->pci_info), 1);
	}
	populate_psp_directory_table(
		com, &(atree->psp_directory), leaves->pspdirtableoffset
	);

	//rom->data_table = &(atree->data_table);
	populate_datatables(com, leaves->masterdatatable_offset);

	return false;

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
		struct atomtree_commons* const com,
		struct atomtree_rom_header* const rom,
		uint16_t bios_offset
		) {
	if (populate_atom(com, &(rom->atom), bios_offset)) {
		return;
	}
	bool err = false;
	switch (rom->ver.ver) {
		case V(1,1): err = populate_atom_rom_header_v1_1(com, rom); break;
		case V(2,1): err = populate_atom_rom_header_v2_1(com, rom); break;
		case V(2,3): // forced
		case V(2,2): err = populate_atom_rom_header_v2_2(com, rom); break;
		default: break;
	}
	if (err) { // partial crawl error
		rom->ver = SET_VER(0);
		return;
	}
}

inline static void
populate_pci_tables(
		struct atomtree_commons* const com,
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
			&(com->alloc_arena), &(com->error),
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

	struct atomtree_commons com = {
		.bios = b.bios,
	};

	// atomtree is highly conditional, so zeroing with calloc will make
	// population easier.
	// allocating the size of the bios for atomtree is a heuristic, but should
	// be far, far more than enough.
	arena_init(&(com.alloc_arena), biosfile_size, true);

	setjmp(com.error.env);
	if (com.error.severity) {
		free(com.alloc_arena.start);
		return NULL;
	}

	struct atom_tree* const atree = arena_alloc(
		&(com.alloc_arena), &(com.error), sizeof(struct atom_tree)
	);
	com.atree = atree;

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
			&(com.alloc_arena), &(com.error),
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


	populate_pci_tables(&com, &(atree->pci_tables), &(b.image->pci_header));
	if (atree->pci_tables.num_images) { // if this fails, no PCIR
		atree->chip_type = get_amd_chip_from_pci_id(
			atree->pci_tables.pci_tables[0].pcir->vendor_id,
			atree->pci_tables.pci_tables[0].pcir->device_id
		);
	}

	populate_atom_rom_header(
		&com, &(atree->rom_header), b.image->rom_header_info_table_offset
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
