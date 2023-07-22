/*
AtomTree iterable interface for UIs.

adding tables

vim replace patterns that help copypaste structs from atombios.h:
'<,'>s:struct :PPATUI_FUNCIFY(:g
'<,'>s:.*uint[0-9]*_t[ ,^I]*:^I:g
'<,'>s:;.*:,:g
'<,'>s:,\n},:\r):g
*/

#include "atui.h"
#include <stdio.h>


void atui_leaf_set_val(atui_leaf* leaf, uint64_t val){
	if (leaf->type & ATUI_ANY) {
		uint8_t num_bits = (leaf->bitfield_hi - leaf->bitfield_lo) +1;
		uint64_t maxval = (1ULL << num_bits) - 1;
		if (val > maxval)
			val = maxval;

		// ...11111 000.. 1111...
		uint64_t tokeep_mask = ~(maxval << leaf->bitfield_lo);
		val <<= leaf->bitfield_lo;
		*(leaf->u64) = (*(leaf->u64) & tokeep_mask) | val;
	}
}


uint64_t atui_leaf_get_val(atui_leaf* leaf) {
	if (leaf->type & ATUI_ANY) {
		uint8_t num_bits = (leaf->bitfield_hi - leaf->bitfield_lo) +1;
		uint64_t premask = (1ULL << num_bits) - 1; // 0's the hi

		return (*(leaf->u64) >> leaf->bitfield_lo) & premask;
	}
}

uint64_t strtoll_2(const char* str) {
	// TODO is there a strtoll that has 0b detection?
	uint8_t base = 0; // 0 = auto
	if ((str[0] == '0') && (str[1] == 'b')) {
		base = 2;
		str += 2;
	}
	return (uint64_t)strtoll(str, NULL, base);
}




int atui_set_from_text(atui_leaf* leaf, const char* buffer) {
    int err = 0;

    if(leaf->type & ATUI_ANY) {
        atui_leaf_set_val(leaf, strtoll_2(buffer));

    } else if( (leaf->type & (ATUI_STRING|ATUI_ARRAY)) &&
            leaf->total_bits == 8) {
		uint8_t size = leaf->array_size;
		uint8_t i;
		for(i=0; i<size; i++)
		   leaf->u8[i] = buffer[i];
		//leaf->u8[i-1] = '\0';
    } else {
        err = 1;
    }
    return err;
}
int atui_get_to_text(atui_leaf* leaf, char* buffer) {
    int err = 0;

    if(leaf->type & ATUI_ANY) {
		uint64_t val = atui_leaf_get_val(leaf);
		if ((leaf->type&ATUI_ANY) == ATUI_DEC) {
			sprintf(buffer, "%u", val);
		} else if ((leaf->type&ATUI_ANY) == ATUI_HEX) {
			sprintf(buffer, "0x%X", val);
		} else if ((leaf->type&ATUI_ANY) == ATUI_BIN) {
			uint8_t numbits = (leaf->bitfield_hi - leaf->bitfield_lo) +1;
			//sprintf adds the \0 at the end.
			char format[10] = "0b%0"; //prefix
			sprintf(format+4, "%02ub", numbits); //middle, suffix.
			sprintf(buffer, format, val);
		}

    } else if( (leaf->type & (ATUI_STRING|ATUI_ARRAY)) &&
            leaf->total_bits == 8) {
        uint8_t i = leaf->array_size;
		buffer[i] = '\0'; // for strings
        while (i--)
            buffer[i] = leaf->u8[i];
    } else {
        err = 1;
    }
    return err;
}



void atui_destroy_tree(atui_branch* tree) { //a reference implementation
	tree->max_branch_count += tree->max_inline_branch_count;
	while(tree->max_branch_count--)
		atui_destroy_tree(tree->child_branches[tree->max_branch_count]);
	free(tree);
}



/*
See ppatui.h and atui.h for more detail.

example:
PPATUI_FUNCIFY(type_prefix, atom_table_tame, atomtree_table_name,
	table_element1, radix, fancy ui representation, args for fancy,
	table_element2, radix, fancy ui representation, args for fancy,
	table_element3, radix, fancy ui representation, args for fancy
)

WARNING: always have the last comma removed:
	This is bad:  arg,arg,)
	This is good: arg,arg)


If the table element should be viewed as a number, set a radix. radix is one of
ATUI_NONE, ATUI_DEC, ATUI_HEX, ATUI_BIN

If the element should be viewed in base 2, but also has bitfields for children:
	table_element, ATUI_BIN, ATUI_BITFIELD, (
		bitfield_struct_instance_name,
		name, bitness, radix,
		name, bitness, radix
	),


if the element should have a list of text-val pairs, an enum,
first populate the atui enum:
	PPATUI_ENUMER(enum_struct_name,
		ENUM_ENTRY1,
		ENUM_ENTRY2,
		ENUM_ENTRY3,
	)
and then for the atui table,
	table_element, ATUI_HEX, ATUI_ENUM, enum_struct_name,

if the element should reference a table, a atui_branch to inline,
ake sure the table is populated with an ATUI_FUNCIFY()
	table_element, ATUI_NAN, ATUI_INLINE, table_to_inline,

if the element is a string,
	table_element, ATUI_NAN, ATUI_STRING, ATUI_NONE,
or otherwise an array,
	table_element, ATUI_HEX, ATUI_ARRAY, ATUI_NONE,



ATUI_DYNARRAY:

leaf_top_name, ATUI_NODISPLAY, ATUI_DYNARRY, (
	leaf_name, radix, fancy_ui_representation, args_for_fancy,
	start_pointer, count
)

If there is an array or number of leaves that is dynamically sized, especially
if it has a dynamic allocation, ATUI_DYNARRY can pull in the boundaries from
atomtree.
(it is originally written for atom_umc_init_reg_block.)

leaf_top_name won't get displayed if ATUI_NODISPLAY is set.

leaf_name .. args_for_fancy, is the leaf pattern to use. Can be a bitfield.
start_pointer is a pointer where to start the array within the bios, and
count is how long the array goes on for.
Both start_pointer and count are members of the Funcify-passed atomtree struct.

*/
/*
var, namedata, val display data,
var, namedata, val display data,

PPATUI_FUNCIFY(atomprefix, atomtype, atomtree_type,
	(var, display name,
		(radix, fancy, optional_fancy_args)
		(lang, description
			lang, description
		)),
	(var, display name,
		(radix, fancy, optional_fancy_args)
		(lang, description
			lang, description
		)),
	(var, display name,
		(radix, fancy, optional_fancy_args)
		(lang, description
			lang, description
		)),

)
_PPATUI_FANCY_##fancytype(\
        bios->var, var, name, desdat, radix, fancytype, __VA_ARGS__\
    )
*/

		//atom_tree, // to satisfy atomtree->leaves.
PPATUI_FUNCIFY(struct, atom_common_table_header,
		atui_nullstruct,

	(structuresize, ATOM table size (bytes),
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(format_revision, ATOM table format revision,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(content_revision, ATOM table content revision,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR))
)

PPATUI_FUNCIFY(struct, atom_rom_header_v2_2,
		atom_tree, //THE atom_tree struct

	(table_header, table header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header), (ATUI_NODESCR)
	),
	(atom_bios_string, atom_bios_string,
		(ATUI_NAN, ATUI_STRING), (ATUI_NODESCR)
	),
	(bios_segment_address, bios_segment_address,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(protectedmodeoffset, protectedmodeoffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(configfilenameoffset, configfilenameoffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(crc_block_offset, crc_block_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(vbios_bootupmessageoffset, vbios_bootupmessageoffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(int10_offset, int10_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(pcibusdevinitcode, pcibusdevinitcode,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(iobaseaddress, iobaseaddress,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(subsystem_vendor_id, subsystem_vendor_id,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(subsystem_id, subsystem_id,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(pci_info_offset, pci_info_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(masterhwfunction_offset, masterhwfunction_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(masterdatatable_offset, masterdatatable_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(reserved, reserved,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(pspdirtableoffset, pspdirtableoffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, atom_master_data_table_v2_1,
		atomtree_master_datatable_v2_1,

	(table_header, table header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(utilitypipeline, utilitypipeline,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(multimedia_info, multimedia_info,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(smc_dpm_info, smc_dpm_info,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable3, sw_datatable3,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(firmwareinfo, firmwareinfo,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable5, sw_datatable5,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(lcd_info, lcd_info,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable7, sw_datatable7,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(smu_info, smu_info,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable9, sw_datatable9,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable10, sw_datatable10,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(vram_usagebyfirmware, vram_usagebyfirmware,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(gpio_pin_lut, gpio_pin_lut,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable13, sw_datatable13,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(gfx_info, gfx_info,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(powerplayinfo, powerplayinfo,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable16, sw_datatable16,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable17, sw_datatable17,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable18, sw_datatable18,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable19, sw_datatable19,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable20, sw_datatable20,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable21, sw_datatable21,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(displayobjectinfo, displayobjectinfo,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(indirectioaccess, indirectioaccess,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(umc_info, umc_info,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable25, sw_datatable25,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable26, sw_datatable26,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(dce_info, dce_info,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(vram_info, vram_info,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable29, sw_datatable29,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(integratedsysteminfo, integratedsysteminfo,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(asic_profiling_info, asic_profiling_info,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(voltageobject_info, voltageobject_info,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable33, sw_datatable33,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable34, sw_datatable34,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)



/*
vim search-replace translation patters, from ddrmoderegisters.h to ppatui
'<,'>s/mr0/mr1/g

vim q recording:
'<,'>s/;/,/g
'<,'>s/-/,/
'<,'>s/ \+:/,\0/
'<,'>s/:/ /
'<,'>s/    /\t\t\t(/
'<,'>s/ +1,.*\n/, ATUI_DEC, (ATUI_NODESCR)),\r/
'<,'>s/,\n\n/\r/
*/

PPATUI_FUNCIFY(union, gddr6_mr0, atui_nullstruct,
	(gddr6_mr0, gddr6_mr0,
		(ATUI_BIN, ATUI_BITFIELD, (
			(WLmrs,    2, 0, ATUI_DEC, (ATUI_NODESCR)), 
			(RLmrs,    6, 3, ATUI_DEC, (ATUI_NODESCR)), 
			(testmode, 7, 7, ATUI_DEC, (ATUI_NODESCR)), 
			(WRmrs,   11, 8, ATUI_DEC, (ATUI_NODESCR)), 
			(ID,      15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr1, atui_nullstruct,
	(gddr6_mr1, gddr6_mr1,
		(ATUI_BIN, ATUI_BITFIELD, (
    		(drive_stren,   1,0, ATUI_DEC, (ATUI_NODESCR)),
			(data_term,     3,2, ATUI_DEC, (ATUI_NODESCR)),
			(PLLDLL_range,  5,4, ATUI_DEC, (ATUI_NODESCR)),
			(Cal_Upd,       6,6, ATUI_DEC, (ATUI_NODESCR)),
			(PLL_DLL,       7,7, ATUI_DEC, (ATUI_NODESCR)),
			(RDBI,          8,8, ATUI_DEC, (ATUI_NODESCR)),
			(WDBI,          9,9, ATUI_DEC, (ATUI_NODESCR)),
			(CABI,         10,10, ATUI_DEC, (ATUI_NODESCR)),
			(PLLDLL_reset, 14,11, ATUI_DEC, (ATUI_NODESCR)),
			(ID,           15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr2, atui_nullstruct,
	(gddr6_mr2, gddr6_mr2,
		(ATUI_BIN, ATUI_BITFIELD, (
			(OCD_up,        2,0, ATUI_DEC, (ATUI_NODESCR)),
			(OCD_down,      5,3, ATUI_DEC, (ATUI_NODESCR)),
			(self_refresh,  7,6, ATUI_DEC, (ATUI_NODESCR)),
			(EDC_mode,      8,8, ATUI_DEC, (ATUI_NODESCR)),
			(RDQS,          9,9, ATUI_DEC, (ATUI_NODESCR)),
			(CADT_SRF,     10,10, ATUI_DEC, (ATUI_NODESCR)),
			(EDC_HR,       11,11, ATUI_DEC, (ATUI_NODESCR)),
			(ID,           15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr3, atui_nullstruct,
	(gddr6_mr3, gddr6_mr3,
		(ATUI_BIN, ATUI_BITFIELD, (
			(dataWCK_term_offset,  2,0, ATUI_DEC, (ATUI_NODESCR)),
			(CA_term_offset,       5,3, ATUI_DEC, (ATUI_NODESCR)),
			(DRAM_info,            7,6, ATUI_DEC, (ATUI_NODESCR)),
			(WR_scaling,           9,8, ATUI_DEC, (ATUI_NODESCR)),
			(bank_groups,         11,10, ATUI_DEC, (ATUI_NODESCR)),
			(ID,                  15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr4, atui_nullstruct,
	(gddr6_mr4, gddr6_mr4,
		(ATUI_BIN, ATUI_BITFIELD, (
			(EDC_hold_pattern,  3,0, ATUI_DEC, (ATUI_NODESCR)),
			(CRCWL,             6,4, ATUI_DEC, (ATUI_NODESCR)),
			(CRCRL,             8,7, ATUI_DEC, (ATUI_NODESCR)),
			(RDCRC,             9,9, ATUI_DEC, (ATUI_NODESCR)),
			(WRCRC,            10,10, ATUI_DEC, (ATUI_NODESCR)),
			(EDC_hold_invert,  11,11, ATUI_DEC, (ATUI_NODESCR)),
			(ID,               15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr5, atui_nullstruct,
	(gddr6_mr5, gddr6_mr5,
		(ATUI_BIN, ATUI_BITFIELD, (
			(LP1,        0,0, ATUI_DEC, (ATUI_NODESCR)),
			(LP2,        1,1, ATUI_DEC, (ATUI_NODESCR)),
			(LP3,        2,2, ATUI_DEC, (ATUI_NODESCR)),
			(PLLDLL_BW,  5,3, ATUI_DEC, (ATUI_NODESCR)),
			(RAS,       11,6, ATUI_DEC, (ATUI_NODESCR)),
			(ID,        15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr6, atui_nullstruct,
	(gddr6_mr6, gddr6_mr6,
		(ATUI_BIN, ATUI_BITFIELD, (
			(VREFD_level,   6,0, ATUI_DEC, (ATUI_NODESCR)),
			(pin_subaddr,  11,7, ATUI_DEC, (ATUI_NODESCR)),
			(ID,           15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr7, atui_nullstruct,
	(gddr6_mr7, gddr6_mr7,
		(ATUI_BIN, ATUI_BITFIELD, (
			(WCK2CK_AP,        0,0, ATUI_DEC, (ATUI_NODESCR)),
			(hibernate,        1,1, ATUI_DEC, (ATUI_NODESCR)),
			(PLL_delay_comp,   2,2, ATUI_DEC, (ATUI_NODESCR)),
			(low_freq_mode,    3,3, ATUI_DEC, (ATUI_NODESCR)),
			(WCK2CK_autosync,  4,4, ATUI_DEC, (ATUI_NODESCR)),
			(DQ_preamble,      5,5, ATUI_DEC, (ATUI_NODESCR)),
			(half_VREFC,       6,6, ATUI_DEC, (ATUI_NODESCR)),
			(half_VREFD,       7,7, ATUI_DEC, (ATUI_NODESCR)),
			(VDD_range,        9,8, ATUI_DEC, (ATUI_NODESCR)),
			(WCK_DCC,         11,10, ATUI_DEC, (ATUI_NODESCR)),
			(ID,              15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr8, atui_nullstruct,
	(gddr6_mr8, gddr6_mr8,
		(ATUI_BIN, ATUI_BITFIELD, (
			(CA_low_term,   1,0, ATUI_DEC, (ATUI_NODESCR)),
			(CA_high_term,  3,2, ATUI_DEC, (ATUI_NODESCR)),
			(CA_TO,         4,4, ATUI_DEC, (ATUI_NODESCR)),
			(EDC_hiZ,       5,5, ATUI_DEC, (ATUI_NODESCR)),
			(CK_auto_cal,   6,6, ATUI_DEC, (ATUI_NODESCR)),
			(REFpb,         7,7, ATUI_DEC, (ATUI_NODESCR)),
			(RL_EHF,        8,8, ATUI_DEC, (ATUI_NODESCR)),
			(WR_EHF,        9,9, ATUI_DEC, (ATUI_NODESCR)),
			(CK_term,      11,10, ATUI_DEC, (ATUI_NODESCR)),
			(ID,           15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr9, atui_nullstruct,
	(gddr6_mr9, gddr6_mr9,
		(ATUI_BIN, ATUI_BITFIELD, (
			(DFE,           3,0, ATUI_DEC, (ATUI_NODESCR)),
			(RFU,           6,4, ATUI_DEC, (ATUI_NODESCR)),
			(pin_subaddr,  11,7, ATUI_DEC, (ATUI_NODESCR)),
			(ID,           15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr10, atui_nullstruct,
	(gddr6_mr10, gddr6_mr10,
		(ATUI_BIN, ATUI_BITFIELD, (
			(VREFC_offset,   3,0, ATUI_DEC, (ATUI_NODESCR)),
			(WCK_inv_byte0,  5,4, ATUI_DEC, (ATUI_NODESCR)),
			(WCK_inv_byte1,  7,6, ATUI_DEC, (ATUI_NODESCR)),
			(WCK2CK,         8,8, ATUI_DEC, (ATUI_NODESCR)),
			(WCK_ratio,      9,9, ATUI_DEC, (ATUI_NODESCR)),
			(WCK_term,      11,10, ATUI_DEC, (ATUI_NODESCR)),
			(ID,            15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr11, atui_nullstruct,
	(gddr6_mr11, gddr6_mr11,
		(ATUI_BIN, ATUI_BITFIELD, (
			(PASR_2bank_mask,   7,0, ATUI_DEC, (ATUI_NODESCR)),
			(PASR_rowseg_mask, 11,8, ATUI_DEC, (ATUI_NODESCR)),
			(ID,               15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr12, atui_nullstruct,
	(gddr6_mr12, gddr6_mr12,
		(ATUI_BIN, ATUI_BITFIELD, (
			(VDDQ_off,   0,0, ATUI_DEC, (ATUI_NODESCR)),
			(P2BR_addr,  1,1, ATUI_DEC, (ATUI_NODESCR)),
			(PRBS,       2,2, ATUI_DEC, (ATUI_NODESCR)),
			(RL_EHF2,    3,3, ATUI_DEC, (ATUI_NODESCR)),
			(CRCWL_EHF,  4,4, ATUI_DEC, (ATUI_NODESCR)),
			(WR_EHF2,    5,5, ATUI_DEC, (ATUI_NODESCR)),
			(RFU,       11,6, ATUI_DEC, (ATUI_NODESCR)),
			(ID,        15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr13, atui_nullstruct,
	(gddr6_mr13, gddr6_mr13,
		(ATUI_BIN, ATUI_BITFIELD, (
			(vendor_specific,  11,0, ATUI_DEC, (ATUI_NODESCR)),
			(ID,               15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr14, atui_nullstruct,
	(gddr6_mr14, gddr6_mr14,
		(ATUI_BIN, ATUI_BITFIELD, (
			(vendor_specific,  11,0, ATUI_DEC, (ATUI_NODESCR)),
			(ID,               15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr15, atui_nullstruct,
	(gddr6_mr15, gddr6_mr15,
		(ATUI_BIN, ATUI_BITFIELD, (
			(MRS_to_chan_A,  0,0, ATUI_DEC, (ATUI_NODESCR)),
			(MRS_to_chan_B,  1,1, ATUI_DEC, (ATUI_NODESCR)),
			(CA_training,    3,2, ATUI_DEC, (ATUI_NODESCR)),
			(unused,         11,4, ATUI_DEC, (ATUI_NODESCR)),
			(ID,             15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, atom_vram_info_header_v2_4,
		atomtree_vram_info_header_v2_4,

	(table_header, table header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(mem_adjust_tbloffset, mem_adjust_tbloffset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(mem_clk_patch_tbloffset, mem_clk_patch_tbloffset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(mc_adjust_pertile_tbloffset,mc_adjust_pertile_tbloffset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(mc_phyinit_tbloffset, mc_phyinit_tbloffset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(dram_data_remap_tbloffset, dram_data_remap_tbloffset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(reserved, reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(post_ucode_init_offset, post_ucode_init_offset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(vram_rsd2, vram_rsd2,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(vram_module_num, vram_module_num,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(umcip_min_ver, umcip_min_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(umcip_max_ver, umcip_max_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(mc_phy_tile_num, mc_phy_tile_num,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)



PPATUI_ENUMER(atom_dgpu_vram_type,
  ATOM_DGPU_VRAM_TYPE_GDDR5,
  ATOM_DGPU_VRAM_TYPE_HBM2,
  ATOM_DGPU_VRAM_TYPE_HBM2E,
  ATOM_DGPU_VRAM_TYPE_GDDR6
)
PPATUI_FUNCIFY(struct, atom_vram_module_v10,
		atomtree_vram_info_header_v2_4,

	(memory_size, memory_size,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(channel_enable, channel_enable,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(max_mem_clk, max_mem_clk,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(reserved, reserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(mem_voltage, mem_voltage,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(vram_module_size, vram_module_size,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(ext_memory_id, ext_memory_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(memory_type, memory_type,
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		(ATUI_NODESCR)
	),
	(channel_num, channel_num,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(channel_width, channel_width,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(density, density,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(tunningset_id, tunningset_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(vender_rev_id, vender_rev_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(refreshrate, refreshrate,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(vram_flags, vram_flags,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(vram_rsd2, vram_rsd2,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(gddr6_mr10, gddr6_mr10,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr10),
		(ATUI_NODESCR)
	),
	(gddr6_mr1, gddr6_mr1,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr1),
		(ATUI_NODESCR)
	),
	(gddr6_mr2, gddr6_mr2,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr2),
		(ATUI_NODESCR)
	),
	(gddr6_mr7, gddr6_mr7,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr7),
		(ATUI_NODESCR)
	),
	(dram_pnstring, dram_pnstring, 
		(ATUI_NAN, ATUI_ARRAY), // not text
		(ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, atom_umc_register_addr_info_access,
		atomtree_umc_init_reg_block,
	(umc_reg_list, umc_reg_list,
		(ATUI_NODISPLAY, ATUI_DYNARRAY, (
			// Leaf pattern:
			(u32umc_reg_addr, u32umc_reg_addr [%02u],
				(ATUI_BIN, ATUI_BITFIELD, (
					(umc_register_addr, 23, 0, ATUI_HEX, (ATUI_NODESCR)),
					(umc_reg_type_ind,  24,24, ATUI_DEC, (ATUI_NODESCR)),
					(umc_reg_rsvd,      31,25, ATUI_BIN, (ATUI_NODESCR))
				)), (ATUI_NODESCR)
			),
			//start, count
			atomtree->umc_reg_list, atomtree->umc_number_of_registers
		)),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_umc_init_reg_block,
		atomtree_umc_init_reg_block,
	(umc_reg_num, umc_reg_num,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(reserved, reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, atom_umc_reg_setting_id_config_access,
		atomtree_umc_init_reg_block,

	(u32umc_id_access,  u32umc_id_access,
		(ATUI_BIN, ATUI_BITFIELD, (
			(memclockrange, 23, 0, ATUI_DEC, (ATUI_NODESCR)),
			(mem_blk_id,    31,24, ATUI_DEC, (ATUI_NODESCR))
		)),
		(ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, atom_umc_reg_setting_data_block,
		atomtree_umc_init_reg_block,
	(block_id, UMC block ID,
		(ATUI_NODISPLAY, ATUI_INLINE, atom_umc_reg_setting_id_config_access),
		(ATUI_NODESCR)
	),

	(u32umc_reg_data, u32umc_reg_data,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(u32umc_reg_data, u32umc_reg_data,
				(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			//start, count
			bios->u32umc_reg_data, atomtree->umc_reg_num
		)),
		(ATUI_NODESCR)
	)

)
