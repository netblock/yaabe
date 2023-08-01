/*
AtomTree iterable interface for UIs.
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
	//set the value of the leaf based on input text. Currently only support for
	// numbers (including bitfields) and strings.

	int err = 0;

	if(leaf->type & ATUI_ANY) {
		atui_leaf_set_val(leaf, strtoll_2(buffer));

	} else if (leaf->type & ATUI_STRING) {
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
	// Convert the value of a leaf to text. Currently only support for numbers,
	// and strings.
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

	} else if (leaf->type & ATUI_STRING) {
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
PPATUI_FUNCIFY(atomprefix, atomtype, atomtree_type,
	(namespace_var, UI display name,
		(radix, fancy, optional_fancy_args),
		((lang, description)
			(lang, description)
		)
	),
	(namespace_var, UI display name,
		(radix, fancy, optional_fancy_args),
		((lang, description)
			(lang, description)
		)
	)
)

WARNING: always have the last comma removed:
	This is bad:  arg,arg,)
	This is good: arg,arg)


If the table element should be viewed as a number, set a radix. radix is one of
ATUI_NAN, ATUI_DEC, ATUI_HEX, ATUI_OCT, ATUI_BIN.
If the element should be omitted from UI display, set radix to ATUI_NODISPLAY


Fancy types:

ATUI_BITFIELD:
If the element should be viewed in base 2, but also has bitfields for children:
	(namespace_var, UI display name,
		(ATUI_BIN, ATUI_BITFIELD, (
			(bitfield entry name, end_bit, start,  ATUI_DEC, (ATUI_NODESCR)),
			(bitfield entry name, 7, 0,  ATUI_DEC, (ATUI_NODESCR)),
			(bitfield entry name, 31,8,  ATUI_DEC, (ATUI_NODESCR)),
		)), (ATUI_NODESCR)
	)


ATUI_ENUM:
If the element should have a list of text-val pairs, an enum,
First populate the atui enum:
	PPATUI_ENUMER(enum_struct_name,
		ENUM_ENTRY1,
		ENUM_ENTRY2,
		ENUM_ENTRY3,
	)
And then for the atui table,
	(namespace_var, UI display name,
		(ATUI_HEX, ATUI_ENUM, enum_struct_name),
		(ATUI_NODESCR)
	)


ATUI_INLINE:
If the element should reference a table, a atui_branch to inline,
	(namespace_var, UI display name,
		(ATUI_NAN, ATUI_INLINE, table_to_inline),
		(ATUI_NODESCR)
	)
If you want to import just the leaves of the table, as if it was the leaves of
the branch you're constructing, set the radix to ATUI_NODISPLAY
Also make sure the table is populated with an ATUI_FUNCIFY()


ATUI_STRING, ATUI_ARRAY:
If the element is a string,
	(namespace_var, UI display name,
		(ATUI_NAN, ATUI_STRING),
		(ATUI_NODESCR)
	),
or otherwise an array,
	(namespace_var, UI display name,
		(ATUI_HEX, ATUI_ARRAY),
		(ATUI_NODESCR)
	),
If it's an array, data will be represented in the radix of your choosing.


ATUI_DYNARRAY:
	(useless, leaf top UI name,
		(ATUI_NODISPLAY, ATUI_DYNARRAY, (
			// Leaf pattern:
			(namespace_var, UI display name,
				(radix, fancy, optional_fancy_args),
				((lang, description)
					(lang, description)
				)
			)
			source->dynarray_start_pointer, source->dynarray_number_of_elements
		)),
		(ATUI_NODESCR)
	)
If there is an array or number of leaves that is dynamically sized, especially
if it has a dynamic allocation, ATUI_DYNARRY can pull in the boundaries from
atomtree.

The leaf pattern follows regular syntax, and can be a bitfield.

dynarray_start_pointeris the pointer where to start the array within the bios,
and dynarray_number_of_elements counts how long the array goes on for.
Both dynarray_start_pointer and dynarray_number_of_elements can be either from
the relevant atom struct (bios->), or atomtree struct (atomtree->)

Leaf top UI name won't get displayed if ATUI_NODISPLAY is set.

(it is originally written for atom_umc_init_reg_block.)



python function to convert your bog-standard C struct into a basic ATUI format
def struct_to_atui(s):
    import re
    s = re.sub("\n    ","\n\t", s)
    s = re.sub("\n\t    ","\n\t\t", s)
    s = re.sub("\n\t\t    ","\n\t\t\t", s)
    s = re.sub("[ \t]+\n", "\n", s)
    s = re.sub("(struct) ([a-zA-Z0-9_]+) {", "PPATUI_FUNCIFY(\g<1>, \g<2>, atui_nullstruct,",s)
    s = re.sub("(union|struct)\s+([a-zA-Z0-9_]+)\s+([a-zA-Z0-9_]+)(\[[0-9]+\])?;", "(\g<3>, \g<3>,\n\t\t(ATUI_NODISPLAY, ATUI_INLINE, \g<2>),\n\t\t(ATUI_NODESCR)\n\t),", s)
    s = re.sub("(u?int[0-9]+_t|char)\s+([a-zA-Z0-9_]+)(\s+)?;", "(\g<2>, \g<2>,\n\t\t(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)\n\t),", s)
    s = re.sub("(u?int[0-9]+_t|char)\s+([a-zA-Z0-9_]+)\s?+\[[0-9]+\]\s?+;", "(\g<2>, \g<2>,\n\t\t(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)\n\t),", s)
    s = re.sub("(\s+)?\(ATUI_NODESCR\)(\n\t\),)(\s+)?//(\s+)?(.*)", "\n\t\t((LANG_ENG, \"\g<5>\"))\g<2>", s)
    s = re.sub("\),(\s+)?};", ")\n)", s)
    print(s)


def bitfield_to_atui(s):
    import re
    s = re.sub("\n    ","\n\t", s)
    s = re.sub("\n\t    ","\n\t\t", s)
    s = re.sub("\n\t\t    ","\n\t\t\t", s)
    s = re.sub("[ \t]+\n", "\n", s)                                             
    s = s = re.sub("(union) ([a-zA-Z0-9_]+) {", "PPATUI_FUNCIFY(\g<1>, \g<2>, atui_nullstruct,",s)
    s = re.sub("(PPATUI_FUNCIFY\([A-Za-z0-9_, ]+)(//.*)?\n((.*\n)+)?\s};\n};", "\g<1>\n\g<3>\t\t)), (ATUI_NODESCR)\g<2>\n\t)\n)", s)
    s = re.sub("\(ATUI_NODESCR\)(\s*)//(\s*)(.*)", "((LANG_ENG, \"\g<3>\"))", s)
    s = re.sub("[ \t]*uint[0-9]+_t ([A-Za-z0-9_]+)[ \t]*;\s+struct { uint[0-9]+_t\n", "\t(\g<1>, \g<1>,\n\t\t(ATUI_BIN, ATUI_BITFIELD, (\n", s)
    s = re.sub("([a-zA-Z0-9_]+)(\s*):([0-9]+)(\s*)-(\s*)([0-9]+)(\s*)\+1[,;][ \t]*", "\t(\g<1>,\g<2>\g<3>\g<4>,\g<5>\g<6>, ATUI_DEC,", s)
    s = re.sub("ATUI_DEC,(\s*)//(\s*)(.*)", "ATUI_DEC, ((LANG_ENG, \"\g<3>\"))),", s) 
    s = re.sub("ATUI_DEC,\n", "ATUI_DEC, (ATUI_NODESCR)),\n", s)
    s = re.sub(",(\n\t\t\)\), )", "\g<1>", s) 
    print(s)
*/


// basic empty branch mainly to have collapsables
PPATUI_FUNCIFY(struct, atui_nullstruct, atui_nullstruct)


PPATUI_FUNCIFY(struct, atom_common_table_header, atui_nullstruct,
	(structuresize, structuresize,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(format_revision, format_revision,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mainly used for a hw function, when the parser is not backward compatible"))
	),
	(content_revision, content_revision,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "change it when a data table has a structure change, or a hw function has a input/output parameter change"))
	)
)


PPATUI_FUNCIFY(struct, atom_rom_header_v2_2,
		atom_tree, //THE atom_tree struct

	(table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(atom_bios_string, atom_bios_string,
		(ATUI_NAN, ATUI_STRING),
		((LANG_ENG, "enum atom_string_def atom_bios_string. Signature to distinguish between Atombios and non-atombios,"))
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
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Offest for SW to get all command function offsets, Don't change the position"))
	),
	(masterdatatable_offset, masterdatatable_offset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Offest for SW to get all data table offsets, Don't change the position"))
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

	(table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(utilitypipeline, utilitypipeline,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Offest for the utility to get parser info, Don't change this position!"))
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
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(sw_datatable5, sw_datatable5,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(lcd_info, lcd_info,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
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
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(gpio_pin_lut, gpio_pin_lut,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(sw_datatable13, sw_datatable13,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(gfx_info, gfx_info,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(powerplayinfo, powerplayinfo,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
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
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(indirectioaccess, indirectioaccess,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "used as an internal one"))
	),
	(umc_info, umc_info,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(sw_datatable25, sw_datatable25,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable26, sw_datatable26,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(dce_info, dce_info,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(vram_info, vram_info,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(sw_datatable29, sw_datatable29,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(integratedsysteminfo, integratedsysteminfo,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(asic_profiling_info, asic_profiling_info,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(voltageobject_info, voltageobject_info,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "shared by various SW components"))
	),
	(sw_datatable33, sw_datatable33,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(sw_datatable34, sw_datatable34,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)



// TODO ATUI_DYNARRAY with multiple leaves
PPATUI_FUNCIFY(struct, smudpm_i2c_controller_config_v2, atomtree_smc_dpm_info,
	(Enabled, Enabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(Speed, Speed,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(Padding, Padding,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(SlaveAddress, SlaveAddress,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(ControllerPort, ControllerPort,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(ControllerName, ControllerName,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(ThermalThrotter, ThermalThrotter,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(I2cProtocol, I2cProtocol,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_smc_dpm_info_v4_5, atomtree_smc_dpm_info,
	(table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header), (ATUI_NODESCR)
	),

	(MaxVoltageStepGfx, MaxVoltageStepGfx,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value."))
	),
	(MaxVoltageStepSoc, MaxVoltageStepSoc,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value."))
	),

	(VddGfxVrMapping, VddGfxVrMapping,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Use VR_MAPPING* bitfields"))
	),
	(VddSocVrMapping, VddSocVrMapping,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Use VR_MAPPING* bitfields"))
	),
	(VddMem0VrMapping, VddMem0VrMapping,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Use VR_MAPPING* bitfields"))
	),
	(VddMem1VrMapping, VddMem1VrMapping,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Use VR_MAPPING* bitfields"))
	),

	(GfxUlvPhaseSheddingMask, GfxUlvPhaseSheddingMask,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(SocUlvPhaseSheddingMask, SocUlvPhaseSheddingMask,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(ExternalSensorPresent, ExternalSensorPresent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "External RDI connected to TMON (aka TEMP IN)"))
	),
	(Padding8_V, Padding8_V,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Telemetry Settings"))
	),
	(GfxMaxCurrent, GfxMaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(GfxOffset, GfxOffset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(Padding_TelemetryGfx, Padding_TelemetryGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(SocMaxCurrent, SocMaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(SocOffset, SocOffset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(Padding_TelemetrySoc, Padding_TelemetrySoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(Mem0MaxCurrent, Mem0MaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(Mem0Offset, Mem0Offset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(Padding_TelemetryMem0, Padding_TelemetryMem0,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(Mem1MaxCurrent, Mem1MaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(Mem1Offset, Mem1Offset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(Padding_TelemetryMem1, Padding_TelemetryMem1,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO Settings"))
	),
	(AcDcGpio, AcDcGpio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for AC/DC switching"))
	),
	(AcDcPolarity, AcDcPolarity,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO polarity for AC/DC switching"))
	),
	(VR0HotGpio, VR0HotGpio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for VR0 HOT event"))
	),
	(VR0HotPolarity, VR0HotPolarity,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO polarity for VR0 HOT event"))
	),

	(VR1HotGpio, VR1HotGpio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for VR1 HOT event"))
	),
	(VR1HotPolarity, VR1HotPolarity,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO polarity for VR1 HOT event"))
	),
	(GthrGpio, GthrGpio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for GTHR Event"))
	),
	(GthrPolarity, GthrPolarity,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "replace GPIO polarity for GTHR"))
	),

	(LedPin0, LedPin0,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "LED Display Settings GPIO number for LedPin[0]"))
	),
	(LedPin1, LedPin1,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO number for LedPin[1]"))
	),
	(LedPin2, LedPin2,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO number for LedPin[2]"))
	),
	(padding8_4, padding8_4,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GFXCLK PLL Spread Spectrum"))
	),
	(PllGfxclkSpreadEnabled, PllGfxclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "on or off"))
	),
	(PllGfxclkSpreadPercent, PllGfxclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(PllGfxclkSpreadFreq, PllGfxclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),

	(DfllGfxclkSpreadEnabled, DfllGfxclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GFXCLK DFLL Spread Spectrum on or off"))
	),
	(DfllGfxclkSpreadPercent, DfllGfxclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(DfllGfxclkSpreadFreq, DfllGfxclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),

	(UclkSpreadEnabled, UclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "UCLK Spread Spectrum  on or off"))
	),
	(UclkSpreadPercent, UclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(UclkSpreadFreq, UclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),

	(SoclkSpreadEnabled, SoclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "SOCCLK Spread Spectrum on or off"))
	),
	(SocclkSpreadPercent, SocclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(SocclkSpreadFreq, SocclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),

	(TotalBoardPower, TotalBoardPower,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Only needed for TCP Estimated case, where TCP = TGP+Total Board Power"))
	),
	(BoardPadding, BoardPadding,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Mvdd Svi2 Div Ratio Setting"))
	),
	(MvddRatio, MvddRatio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "This is used for MVDD Vid workaround. It has 16 fractional bits (Q16.16)"))
	),

	(BoardReserved, BoardReserved,
		(ATUI_NAN, ATUI_ARRAY), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, atombios_firmware_capability, atui_nullstruct,
	(firmware_capability, firmware_capability,
		(ATUI_HEX, ATUI_BITFIELD, (
			(FIRMWARE_POSTED,         0,0, ATUI_DEC, (ATUI_NODESCR)),
			(GPU_VIRTUALIZATION,      1,1, ATUI_DEC, (ATUI_NODESCR)),
			(reserved0,               5,2, ATUI_DEC, (ATUI_NODESCR)),
			(WMI_SUPPORT,             6,6, ATUI_DEC, (ATUI_NODESCR)),
			(HWEMU_ENABLE,            7,7, ATUI_DEC, (ATUI_NODESCR)),
			(HWEMU_UMC_CFG,           8,8, ATUI_DEC, (ATUI_NODESCR)),
			(SRAM_ECC,                9,9, ATUI_DEC, (ATUI_NODESCR)),
			(ENABLE_2STAGE_BIST_TRAINING, 10,10, ATUI_DEC, (ATUI_NODESCR)),
			(reserved1,              14,11, ATUI_DEC, (ATUI_NODESCR)),
			(ENABLE_2ND_USB20PORT,   15,15, ATUI_DEC, (ATUI_NODESCR)),
			(reserved2,              16,16, ATUI_DEC, (ATUI_NODESCR)),
			(DYNAMIC_BOOT_CFG_ENABLE,17,17, ATUI_DEC, (ATUI_NODESCR)),
			(reserved3,              31,18, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, atom_firmware_info_v3_1, atomtree_firmware_info,
	(table_header, table_header,
		(ATUI_NODISPLAY, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(firmware_revision, firmware_revision,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_sclk_in10khz, bootup_sclk_in10khz,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_mclk_in10khz, bootup_mclk_in10khz,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(firmware_capability, firmware_capability,
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability),
		(ATUI_NODESCR)
	),
	(main_call_parser_entry, main_call_parser_entry,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "direct address of main parser call in VBIOS binary."))
	),
	(bios_scratch_reg_startaddr, bios_scratch_reg_startaddr,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "1st bios scratch register dword address"))
	),
	(bootup_vddc_mv, bootup_vddc_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_vddci_mv, bootup_vddci_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_mvddc_mv, bootup_mvddc_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_vddgfx_mv, bootup_vddgfx_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(mem_module_id, mem_module_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(coolingsolution_id, coolingsolution_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0: Air cooling; 1: Liquid cooling ..."))
	),
	(reserved1, reserved1,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(mc_baseaddr_high, mc_baseaddr_high,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(mc_baseaddr_low, mc_baseaddr_low,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(reserved2, reserved2,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v3_2, atomtree_firmware_info,
	(table_header, table_header,
		(ATUI_NODISPLAY, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(firmware_revision, firmware_revision,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_sclk_in10khz, bootup_sclk_in10khz,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_mclk_in10khz, bootup_mclk_in10khz,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(firmware_capability, firmware_capability,
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability),
		(ATUI_NODESCR)
	),
	(main_call_parser_entry, main_call_parser_entry,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "direct address of main parser call in VBIOS binary."))
	),
	(bios_scratch_reg_startaddr, bios_scratch_reg_startaddr,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "1st bios scratch register dword address"))
	),
	(bootup_vddc_mv, bootup_vddc_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_vddci_mv, bootup_vddci_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_mvddc_mv, bootup_mvddc_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_vddgfx_mv, bootup_vddgfx_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(mem_module_id, mem_module_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(coolingsolution_id, coolingsolution_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0: Air cooling; 1: Liquid cooling ..."))
	),
	(reserved1, reserved1,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(mc_baseaddr_high, mc_baseaddr_high,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(mc_baseaddr_low, mc_baseaddr_low,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(board_i2c_feature_id, board_i2c_feature_id,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "enum of atom_board_i2c_feature_id_def"))
	),
	(board_i2c_feature_gpio_id, board_i2c_feature_gpio_id,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "i2c id find in gpio_lut data table gpio_id"))
	),
	(board_i2c_feature_slave_addr, board_i2c_feature_slave_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(reserved3, reserved3,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_mvddq_mv, bootup_mvddq_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_mvpp_mv, bootup_mvpp_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(zfbstartaddrin16mb, zfbstartaddrin16mb,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(reserved2, reserved2,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v3_3, atomtree_firmware_info,
	(table_header, table_header,
		(ATUI_NODISPLAY, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(firmware_revision, firmware_revision,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_sclk_in10khz, bootup_sclk_in10khz,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_mclk_in10khz, bootup_mclk_in10khz,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(firmware_capability, firmware_capability,
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability),
		(ATUI_NODESCR)
	),
	(main_call_parser_entry, main_call_parser_entry,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "direct address of main parser call in VBIOS binary."))
	),
	(bios_scratch_reg_startaddr, bios_scratch_reg_startaddr,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "1st bios scratch register dword address"))
	),
	(bootup_vddc_mv, bootup_vddc_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_vddci_mv, bootup_vddci_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_mvddc_mv, bootup_mvddc_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_vddgfx_mv, bootup_vddgfx_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(mem_module_id, mem_module_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(coolingsolution_id, coolingsolution_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0: Air cooling; 1: Liquid cooling ..."))
	),
	(reserved1, reserved1,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(mc_baseaddr_high, mc_baseaddr_high,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(mc_baseaddr_low, mc_baseaddr_low,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(board_i2c_feature_id, board_i2c_feature_id,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "enum of atom_board_i2c_feature_id_def"))
	),
	(board_i2c_feature_gpio_id, board_i2c_feature_gpio_id,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "i2c id find in gpio_lut data table gpio_id"))
	),
	(board_i2c_feature_slave_addr, board_i2c_feature_slave_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(reserved3, reserved3,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_mvddq_mv, bootup_mvddq_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_mvpp_mv, bootup_mvpp_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(zfbstartaddrin16mb, zfbstartaddrin16mb,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(pplib_pptable_id, pplib_pptable_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "if pplib_pptable_id!=0, pplib get powerplay table inside driver instead of from VBIOS"))
	),
	(reserved2, reserved2,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v3_4, atomtree_firmware_info,
	(table_header, table_header,
		(ATUI_NODISPLAY, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(firmware_revision, firmware_revision,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_sclk_in10khz, bootup_sclk_in10khz,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_mclk_in10khz, bootup_mclk_in10khz,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(firmware_capability, firmware_capability,
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability),
		(ATUI_NODESCR)
	),
	(main_call_parser_entry, main_call_parser_entry,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "direct address of main parser call in VBIOS binary."))
	),
	(bios_scratch_reg_startaddr, bios_scratch_reg_startaddr,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "1st bios scratch register dword address"))
	),
	(bootup_vddc_mv, bootup_vddc_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_vddci_mv, bootup_vddci_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_mvddc_mv, bootup_mvddc_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_vddgfx_mv, bootup_vddgfx_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(mem_module_id, mem_module_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(coolingsolution_id, coolingsolution_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0: Air cooling; 1: Liquid cooling ... */"))
	),
	(reserved1, reserved1,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(mc_baseaddr_high, mc_baseaddr_high,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(mc_baseaddr_low, mc_baseaddr_low,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(board_i2c_feature_id, board_i2c_feature_id,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "enum of atom_board_i2c_feature_id_def"))
	),
	(board_i2c_feature_gpio_id, board_i2c_feature_gpio_id,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "i2c id find in gpio_lut data table gpio_id"))
	),
	(board_i2c_feature_slave_addr, board_i2c_feature_slave_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(ras_rom_i2c_slave_addr, ras_rom_i2c_slave_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_mvddq_mv, bootup_mvddq_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bootup_mvpp_mv, bootup_mvpp_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(zfbstartaddrin16mb, zfbstartaddrin16mb,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(pplib_pptable_id, pplib_pptable_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "if pplib_pptable_id!=0, pplib get powerplay table inside driver instead of from VBIOS"))
	),
	(mvdd_ratio, mvdd_ratio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mvdd_raio = (real mvdd in power rail)*1000/(mvdd_output_from_svi2)"))
	),
	(hw_bootup_vddgfx_mv, hw_bootup_vddgfx_mv,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "hw default vddgfx voltage level decide by board strap"))
	),
	(hw_bootup_vddc_mv, hw_bootup_vddc_mv,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "hw default vddc voltage level decide by board strap"))
	),
	(hw_bootup_mvddc_mv, hw_bootup_mvddc_mv,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "hw default mvddc voltage level decide by board strap"))
	),
	(hw_bootup_vddci_mv, hw_bootup_vddci_mv,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "hw default vddci voltage level decide by board strap"))
	),
	(maco_pwrlimit_mw, maco_pwrlimit_mw,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "bomaco mode power limit in unit of m-watt"))
	),
	(usb_pwrlimit_mw, usb_pwrlimit_mw,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "power limit when USB is enable in unit of m-watt"))
	),
	(fw_reserved_size_in_kb, fw_reserved_size_in_kb,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "VBIOS reserved extra fw size in unit of kb."))
	),
	(pspbl_init_done_reg_addr, pspbl_init_done_reg_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(pspbl_init_done_value, pspbl_init_done_value,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(pspbl_init_done_check_timeout, pspbl_init_done_check_timeout,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "time out in unit of us when polling pspbl init done"))
	),
	(reserved, reserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)








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
			(OCD_up,       2,0, ATUI_DEC, (ATUI_NODESCR)),
			(OCD_down,     5,3, ATUI_DEC, (ATUI_NODESCR)),
			(self_refresh, 7,6, ATUI_DEC, (ATUI_NODESCR)),
			(EDC_mode,     8,8, ATUI_DEC, (ATUI_NODESCR)),
			(RDQS,         9,9, ATUI_DEC, (ATUI_NODESCR)),
			(CADT_SRF,    10,10, ATUI_DEC, (ATUI_NODESCR)),
			(EDC_HR,      11,11, ATUI_DEC, (ATUI_NODESCR)),
			(ID,          15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr3, atui_nullstruct,
	(gddr6_mr3, gddr6_mr3,
		(ATUI_BIN, ATUI_BITFIELD, (
			(dataWCK_term_offset, 2,0, ATUI_DEC, (ATUI_NODESCR)),
			(CA_term_offset,      5,3, ATUI_DEC, (ATUI_NODESCR)),
			(DRAM_info,           7,6, ATUI_DEC, (ATUI_NODESCR)),
			(WR_scaling,          9,8, ATUI_DEC, (ATUI_NODESCR)),
			(bank_groups,        11,10, ATUI_DEC, (ATUI_NODESCR)),
			(ID,                 15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr4, atui_nullstruct,
	(gddr6_mr4, gddr6_mr4,
		(ATUI_BIN, ATUI_BITFIELD, (
			(EDC_hold_pattern, 3,0, ATUI_DEC, (ATUI_NODESCR)),
			(CRCWL,            6,4, ATUI_DEC, (ATUI_NODESCR)),
			(CRCRL,            8,7, ATUI_DEC, (ATUI_NODESCR)),
			(RDCRC,            9,9, ATUI_DEC, (ATUI_NODESCR)),
			(WRCRC,           10,10, ATUI_DEC, (ATUI_NODESCR)),
			(EDC_hold_invert, 11,11, ATUI_DEC, (ATUI_NODESCR)),
			(ID,              15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr5, atui_nullstruct,
	(gddr6_mr5, gddr6_mr5,
		(ATUI_BIN, ATUI_BITFIELD, (
			(LP1,       0,0, ATUI_DEC, (ATUI_NODESCR)),
			(LP2,       1,1, ATUI_DEC, (ATUI_NODESCR)),
			(LP3,       2,2, ATUI_DEC, (ATUI_NODESCR)),
			(PLLDLL_BW, 5,3, ATUI_DEC, (ATUI_NODESCR)),
			(RAS,      11,6, ATUI_DEC, (ATUI_NODESCR)),
			(ID,       15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr6, atui_nullstruct,
	(gddr6_mr6, gddr6_mr6,
		(ATUI_BIN, ATUI_BITFIELD, (
			(VREFD_level,  6,0, ATUI_DEC, (ATUI_NODESCR)),
			(pin_subaddr, 11,7, ATUI_DEC, (ATUI_NODESCR)),
			(ID,          15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr7, atui_nullstruct,
	(gddr6_mr7, gddr6_mr7,
		(ATUI_BIN, ATUI_BITFIELD, (
			(WCK2CK_AP,       0,0, ATUI_DEC, (ATUI_NODESCR)),
			(hibernate,       1,1, ATUI_DEC, (ATUI_NODESCR)),
			(PLL_delay_comp,  2,2, ATUI_DEC, (ATUI_NODESCR)),
			(low_freq_mode,   3,3, ATUI_DEC, (ATUI_NODESCR)),
			(WCK2CK_autosync, 4,4, ATUI_DEC, (ATUI_NODESCR)),
			(DQ_preamble,     5,5, ATUI_DEC, (ATUI_NODESCR)),
			(half_VREFC,      6,6, ATUI_DEC, (ATUI_NODESCR)),
			(half_VREFD,      7,7, ATUI_DEC, (ATUI_NODESCR)),
			(VDD_range,       9,8, ATUI_DEC, (ATUI_NODESCR)),
			(WCK_DCC,        11,10, ATUI_DEC, (ATUI_NODESCR)),
			(ID,             15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr8, atui_nullstruct,
	(gddr6_mr8, gddr6_mr8,
		(ATUI_BIN, ATUI_BITFIELD, (
			(CA_low_term,  1,0, ATUI_DEC, (ATUI_NODESCR)),
			(CA_high_term, 3,2, ATUI_DEC, (ATUI_NODESCR)),
			(CA_TO,        4,4, ATUI_DEC, (ATUI_NODESCR)),
			(EDC_hiZ,      5,5, ATUI_DEC, (ATUI_NODESCR)),
			(CK_auto_cal,  6,6, ATUI_DEC, (ATUI_NODESCR)),
			(REFpb,        7,7, ATUI_DEC, (ATUI_NODESCR)),
			(RL_EHF,       8,8, ATUI_DEC, (ATUI_NODESCR)),
			(WR_EHF,       9,9, ATUI_DEC, (ATUI_NODESCR)),
			(CK_term,     11,10, ATUI_DEC, (ATUI_NODESCR)),
			(ID,          15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr9, atui_nullstruct,
	(gddr6_mr9, gddr6_mr9,
		(ATUI_BIN, ATUI_BITFIELD, (
			(DFE,          3,0, ATUI_DEC, (ATUI_NODESCR)),
			(RFU,          6,4, ATUI_DEC, (ATUI_NODESCR)),
			(pin_subaddr, 11,7, ATUI_DEC, (ATUI_NODESCR)),
			(ID,          15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr10, atui_nullstruct,
	(gddr6_mr10, gddr6_mr10,
		(ATUI_BIN, ATUI_BITFIELD, (
			(VREFC_offset,  3,0, ATUI_DEC, (ATUI_NODESCR)),
			(WCK_inv_byte0, 5,4, ATUI_DEC, (ATUI_NODESCR)),
			(WCK_inv_byte1, 7,6, ATUI_DEC, (ATUI_NODESCR)),
			(WCK2CK,        8,8, ATUI_DEC, (ATUI_NODESCR)),
			(WCK_ratio,     9,9, ATUI_DEC, (ATUI_NODESCR)),
			(WCK_term,     11,10, ATUI_DEC, (ATUI_NODESCR)),
			(ID,           15,12, ATUI_DEC, (ATUI_NODESCR))
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
			(VDDQ_off,  0,0, ATUI_DEC, (ATUI_NODESCR)),
			(P2BR_addr, 1,1, ATUI_DEC, (ATUI_NODESCR)),
			(PRBS,      2,2, ATUI_DEC, (ATUI_NODESCR)),
			(RL_EHF2,   3,3, ATUI_DEC, (ATUI_NODESCR)),
			(CRCWL_EHF, 4,4, ATUI_DEC, (ATUI_NODESCR)),
			(WR_EHF2,   5,5, ATUI_DEC, (ATUI_NODESCR)),
			(RFU,      11,6, ATUI_DEC, (ATUI_NODESCR)),
			(ID,       15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr13, atui_nullstruct,
	(gddr6_mr13, gddr6_mr13,
		(ATUI_BIN, ATUI_BITFIELD, (
			(vendor_specific, 11,0, ATUI_DEC, (ATUI_NODESCR)),
			(ID,              15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr14, atui_nullstruct,
	(gddr6_mr14, gddr6_mr14,
		(ATUI_BIN, ATUI_BITFIELD, (
			(vendor_specific, 11,0, ATUI_DEC, (ATUI_NODESCR)),
			(ID,              15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr15, atui_nullstruct,
	(gddr6_mr15, gddr6_mr15,
		(ATUI_BIN, ATUI_BITFIELD, (
			(MRS_to_chan_A, 0,0, ATUI_DEC, (ATUI_NODESCR)),
			(MRS_to_chan_B, 1,1, ATUI_DEC, (ATUI_NODESCR)),
			(CA_training,   3,2, ATUI_DEC, (ATUI_NODESCR)),
			(unused,        11,4, ATUI_DEC, (ATUI_NODESCR)),
			(ID,            15,12, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)




PPATUI_FUNCIFY(union, DRAMTiming1, atui_nullstruct,
	(DRAMTiming1, DRAMTiming1,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tCL,     5, 0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,   7, 6, ATUI_DEC, (ATUI_NODESCR)),
			(tRAS,   14, 8, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,  15,15, ATUI_DEC, (ATUI_NODESCR)),
			(tRCDRD, 21,16, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd2,  23,22, ATUI_DEC, (ATUI_NODESCR)),
			(tRCDWR, 29,24, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd3,  31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming2, atui_nullstruct,
	(DRAMTiming2, DRAMTiming2,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tRC_S,  7, 0, ATUI_DEC, (ATUI_NODESCR)),
			(tRC_L, 15, 8, ATUI_DEC, (ATUI_NODESCR)),
			(tRP_S, 21,16, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0, 23,22, ATUI_DEC, (ATUI_NODESCR)),
			(tRP_L, 29,24, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1, 31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming3, atui_nullstruct,
	(DRAMTiming3, DRAMTiming3,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tRRD_S,  4,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,   7,5, ATUI_DEC, (ATUI_NODESCR)),
			(tRRD_L, 12,8, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,  23,13, ATUI_DEC, (ATUI_NODESCR)),
			(tRTP,   28,24, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd2,  31,29, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming4, atui_nullstruct,
	(DRAMTiming4, DRAMTiming4,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tFAW,   6,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,  7,7, ATUI_DEC, (ATUI_NODESCR)),
			(t32AW, 16,8, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1, 31,17, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming5, atui_nullstruct,
	(DRAMTiming5, DRAMTiming5,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tWL,    5,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,  7,6, ATUI_DEC, (ATUI_NODESCR)),
			(tWTRS, 12,8, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1, 15,13, ATUI_DEC, (ATUI_NODESCR)),
			(tWTRL, 22,16, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd2, 31,23, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming6, atui_nullstruct,
	(DRAMTiming6, DRAMTiming6,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tWR,    6,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0, 31,7, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming7, atui_nullstruct,
	(DRAMTiming7, DRAMTiming7,
		(ATUI_HEX, ATUI_BITFIELD, (
			(PPD,      2,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,    3,3, ATUI_DEC, (ATUI_NODESCR)),
			(tCRCRL,   6,4, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,    7,7, ATUI_DEC, (ATUI_NODESCR)),
			(tRREFD,  13,8, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd2,   14,14, ATUI_DEC, (ATUI_NODESCR)),
			(tCRCWL,  19,15, ATUI_DEC, (ATUI_NODESCR)),
			(tRCPAGE, 31,20, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming8, atui_nullstruct,
	(DRAMTiming8, DRAMTiming8,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tRDRD_DD,   3,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,      7,4, ATUI_DEC, (ATUI_NODESCR)),
			(tRDRD_SD,  11,8, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,     15,12, ATUI_DEC, (ATUI_NODESCR)),
			(tRDRD_SC,  19,16, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd2,     23,20, ATUI_DEC, (ATUI_NODESCR)),
			(tRDRD_SCL, 27,24, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd3,     29,28, ATUI_DEC, (ATUI_NODESCR)),
			(tRDRD_BAN, 31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming9, atui_nullstruct,
	(DRAMTiming9, DRAMTiming9,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tWRWR_MW,   4,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,     15,5, ATUI_DEC, (ATUI_NODESCR)),
			(tWRWR_SC,  19,16, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,     23,20, ATUI_DEC, (ATUI_NODESCR)),
			(tWRWR_SCL, 29,24, ATUI_DEC, (ATUI_NODESCR)),
			(tWRWR_BAN, 31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming10, atui_nullstruct,
	(DRAMTiming10, DRAMTiming10,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tWRRD,       3,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,       7,4, ATUI_DEC, (ATUI_NODESCR)),
			(tRDWR,      13,8, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,      15,14, ATUI_DEC, (ATUI_NODESCR)),
			(RDRspDelay, 21,16, ATUI_DEC, (ATUI_NODESCR)),
			(tREFTTAdj,  28,17, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd2,      31,29, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming12, atui_nullstruct,
	(DRAMTiming12, DRAMTiming12,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tREFI, 15,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0, 31,16, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming13, atui_nullstruct,
	(DRAMTiming13, DRAMTiming13,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tMRD,   5,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,  7,6, ATUI_DEC, (ATUI_NODESCR)),
			(tMOD,  13,8, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1, 31,14, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming14, atui_nullstruct,
	(DRAMTiming14, DRAMTiming14,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tXS,   10,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0, 15,11, ATUI_DEC, (ATUI_NODESCR)),
			(tDLLK, 26,16, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1, 31,27, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming15, atui_nullstruct,
	(DRAMTiming15, DRAMTiming15,
		(ATUI_HEX, ATUI_BITFIELD, (
			(AlertCrcDly,  6,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,        7,7, ATUI_DEC, (ATUI_NODESCR)),
			(AlertParDly, 14,8, ATUI_DEC, (ATUI_NODESCR)),
			(PL,          18,15, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,       22,19, ATUI_DEC, (ATUI_NODESCR)),
			(RankBusyDly, 29,23, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd2,       31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming16, atui_nullstruct,
	(DRAMTiming16, DRAMTiming16,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tXSMRS, 10,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,  31,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming17, atui_nullstruct,
	(DRAMTiming17, DRAMTiming17,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tPD,           4,0, ATUI_DEC, (ATUI_NODESCR)),
			(tCKSRE,        10,5, ATUI_DEC, (ATUI_NODESCR)),
			(tCKSRX,        16,11, ATUI_DEC, (ATUI_NODESCR)),
			(PwrDownDly,    24,17, ATUI_DEC, (ATUI_NODESCR)),
			(AggPwrDownDly, 30,25, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,         31,31, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming20, atui_nullstruct,
	(DRAMTiming20, DRAMTiming20,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tRFCSB, 10,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,  15,11, ATUI_DEC, (ATUI_NODESCR)),
			(tSTAG,  23,16, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,  31,24, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming21, atui_nullstruct,
	(DRAMTiming21, DRAMTiming21,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tXP,     5,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,  15,6, ATUI_DEC, (ATUI_NODESCR)),
			(tCPDED, 19,16, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,  23,20, ATUI_DEC, (ATUI_NODESCR)),
			(tCKE,   28,24, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd2,  31,29, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming22, atui_nullstruct,
	(DRAMTiming22, DRAMTiming22,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tRDDATA_EN,   6,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,        7,7, ATUI_DEC, (ATUI_NODESCR)),
			(tPHY_WRLAT,  13,8, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,       16,14, ATUI_DEC, (ATUI_NODESCR)),
			(tPHY_RDLAT,  22,17, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd2,       24,23, ATUI_DEC, (ATUI_NODESCR)),
			(tPHY_WRDATA, 27,25, ATUI_DEC, (ATUI_NODESCR)),
			(tPARIN_LAT,  29,28, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd3,       31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming23, atui_nullstruct,
	(DRAMTiming23, DRAMTiming23,
		(ATUI_HEX, ATUI_BITFIELD, (
			(LpDly,      5,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,      7,6, ATUI_DEC, (ATUI_NODESCR)),
			(LpExitDly,  13,8, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,      15,14, ATUI_DEC, (ATUI_NODESCR)),
			(CKESTAGDLY, 19,16, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd3,      31,20, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming34, atui_nullstruct,
	(DRAMTiming34, DRAMTiming34,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tPhyupd_resp, 3,0, ATUI_DEC, (ATUI_NODESCR)),
			(tRDEDC_EN,    10,4, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,        11,11, ATUI_DEC, (ATUI_NODESCR)),
			(tWREDC_EN,    18,12, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,        31,19, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, DRAMTiming35, atui_nullstruct,
	(DRAMTiming35, DRAMTiming35,
		(ATUI_HEX, ATUI_BITFIELD, (
			(ReceiverWait, 10,0, ATUI_DEC, (ATUI_NODESCR)),
			(CmdStageCnt,  21,11, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,        23,22, ATUI_DEC, (ATUI_NODESCR)),
			(tWRMPR,       29,24, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,        31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming36, atui_nullstruct,
	(DRAMTiming36, DRAMTiming36,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tWTRTR,     5,0, ATUI_DEC, (ATUI_NODESCR)),
			(tREFTR,     11,6, ATUI_DEC, (ATUI_NODESCR)),
			(tTTROW,     17,12, ATUI_DEC, (ATUI_NODESCR)),
			(tLDTLD,     23,18, ATUI_DEC, (ATUI_NODESCR)),
			(tUPDN,      29,24, ATUI_DEC, (ATUI_NODESCR)),
			(tREFTR_MSB, 30,30, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,      31,31, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, TRFCTimingCS01, atui_nullstruct,
	(TRFCTimingCS01, TRFCTimingCS01,
		(ATUI_HEX, ATUI_BITFIELD, (
			(tRFC,  10,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0, 31,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, ChanPipeDly, atui_nullstruct,
	(ChanPipeDly, ChanPipeDly,
		(ATUI_HEX, ATUI_BITFIELD, (
			(TXCtrlChanDly, 2,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,         3,3, ATUI_DEC, (ATUI_NODESCR)),
			(TXDataChanDly, 6,4, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,         7,7, ATUI_DEC, (ATUI_NODESCR)),
			(RXDataChanDly, 10,8, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd2,        31,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, atom_gddr6_bit_byte_remap, atui_nullstruct,
	(dphy_byteremap, dphy_byteremap,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mmUMC_DPHY_ByteRemap"))
	),
	(dphy_bitremap0, dphy_bitremap0,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mmUMC_DPHY_BitRemap0"))
	),
	(dphy_bitremap1, dphy_bitremap1,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mmUMC_DPHY_BitRemap1"))
	),
	(dphy_bitremap2, dphy_bitremap2,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mmUMC_DPHY_BitRemap2"))
	),
	(aphy_bitremap0, aphy_bitremap0,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mmUMC_APHY_BitRemap0"))
	),
	(aphy_bitremap1, aphy_bitremap1,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mmUMC_APHY_BitRemap1"))
	),
	(phy_dram, phy_dram,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mmUMC_PHY_DRAM"))
	)
)

PPATUI_FUNCIFY(struct, atom_gddr6_dram_data_remap, atui_nullstruct,
	(table_size, table_size,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(phyintf_ck_inverted, phyintf_ck_inverted,
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "UMC_PHY_PHYINTF_CNTL.INV_CK"))
	)
)


PPATUI_ENUMER(atom_dgpu_vram_type,
  ATOM_DGPU_VRAM_TYPE_GDDR5,
  ATOM_DGPU_VRAM_TYPE_HBM2,
  ATOM_DGPU_VRAM_TYPE_HBM2E,
  ATOM_DGPU_VRAM_TYPE_GDDR6
)



PPATUI_FUNCIFY(struct, atom_vram_module_v9, atui_nullstruct,
	(memory_size, memory_size,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Total memory size in unit of MB for CONFIG_MEMSIZE zeros"))
	),
	(channel_enable, channel_enable,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "bit vector, each bit indicate specific channel enable or not"))
	),
	(max_mem_clk, max_mem_clk,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "max memory clock of this memory in unit of 10kHz, =0 means it is not defined"))
	),
	(reserved, reserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(mem_voltage, mem_voltage,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mem_voltage"))
	),
	(vram_module_size, vram_module_size,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Size of atom_vram_module_v9"))
	),
	(ext_memory_id, ext_memory_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Current memory module ID"))
	),
	(memory_type, memory_type,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "enum of atom_dgpu_vram_type"))
	),
	(channel_num, channel_num,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of mem. channels supported in this module"))
	),
	(channel_width, channel_width,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT"))
	),
	(density, density,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "_8Mx32, _16Mx32, _16Mx16, _32Mx16"))
	),
	(tunningset_id, tunningset_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "MC phy registers set per."))
	),
	(vender_rev_id, vender_rev_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "[7:4] Revision, [3:0] Vendor code"))
	),
	(refreshrate, refreshrate,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(hbm_ven_rev_id, hbm_ven_rev_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "hbm_ven_rev_id"))
	),
	(vram_rsd2, vram_rsd2,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "reserved"))
	),
	(dram_pnstring, dram_pnstring,
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "part number end with '0'."))
	)
)
PPATUI_FUNCIFY(struct, atom_vram_info_header_v2_3, atui_nullstruct,
	(table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(mem_adjust_tbloffset, mem_adjust_tbloffset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for memory vendor specific UMC adjust setting"))
	),
	(mem_clk_patch_tbloffset, mem_clk_patch_tbloffset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for memory clock specific UMC setting"))
	),
	(mc_adjust_pertile_tbloffset, mc_adjust_pertile_tbloffset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for Per Byte Offset Preset Settings"))
	),
	(mc_phyinit_tbloffset, mc_phyinit_tbloffset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for MC phy init set"))
	),
	(dram_data_remap_tbloffset, dram_data_remap_tbloffset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "reserved for now"))
	),
	(tmrs_seq_offset, tmrs_seq_offset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "offset of HBM tmrs"))
	),
	(post_ucode_init_offset, post_ucode_init_offset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for MC phy init after MC uCode complete umc init"))
	),
	(vram_rsd2, vram_rsd2,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(vram_module_num, vram_module_num,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "indicate number of VRAM module"))
	),
	(umcip_min_ver, umcip_min_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(umcip_max_ver, umcip_max_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(mc_phy_tile_num, mc_phy_tile_num,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "indicate the MCD tile number which use in DramDataRemapTbl and usMcAdjustPerTileTblOffset"))
	)
)


PPATUI_FUNCIFY(struct, atom_vram_info_header_v2_4,
		atomtree_vram_info_header_v2_4,
	(table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(mem_adjust_tbloffset, mem_adjust_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for memory vendor specific UMC adjust setting"))
	),
	(mem_clk_patch_tbloffset, mem_clk_patch_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for memory clock specific UMC setting"))
	),
	(mc_adjust_pertile_tbloffset, mc_adjust_pertile_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),// offset of atom_umc_init_reg_block structure for Per Byte Offset Preset Settings
	(mc_phyinit_tbloffset, mc_phyinit_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for MC phy init set"))
	),
	(dram_data_remap_tbloffset, dram_data_remap_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "reserved for now"))
	),
	(reserved, reserved,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of reserved"))
	),
	(post_ucode_init_offset, post_ucode_init_offset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for MC phy init after MC uCode complete umc init"))
	),
	(vram_rsd2, vram_rsd2,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(vram_module_num, vram_module_num,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "indicate number of VRAM module"))
	),
	(umcip_min_ver, umcip_min_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(umcip_max_ver, umcip_max_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(mc_phy_tile_num, mc_phy_tile_num,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "indicate the MCD tile number which use in DramDataRemapTbl and usMcAdjustPerTileTblOffset"))
	)
)


PPATUI_FUNCIFY(struct, atom_vram_module_v10, atomtree_vram_info_header_v2_4,
	(memory_size, memory_size,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Total memory size in unit of MB for CONFIG_MEMSIZE zeros"))
	),
	(channel_enable, channel_enable,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "bit vector, each bit indicate specific channel enable or not"))
	),
	(max_mem_clk, max_mem_clk,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "max memory clock of this memory in unit of 10kHz, =0 means it is not defined"))
	),
	(reserved, reserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(mem_voltage, mem_voltage,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mem_voltage"))
	),
	(vram_module_size, vram_module_size,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Size of atom_vram_module_v9"))
	),
	(ext_memory_id, ext_memory_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Current memory module ID"))
	),
	(memory_type, memory_type,
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		((LANG_ENG, "enum of atom_dgpu_vram_type"))
	),
	(channel_num, channel_num,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of mem. channels supported in this module"))
	),
	(channel_width, channel_width,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT"))
	),
	(density, density,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "_8Mx32, _16Mx32, _16Mx16, _32Mx16"))
	),
	(tunningset_id, tunningset_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "MC phy registers set per"))
	),
	(vender_rev_id, vender_rev_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "[7:4] Revision, [3:0] Vendor code"))
	),
	(refreshrate, refreshrate,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(vram_flags, vram_flags,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "bit0= bankgroup enable"))
	),
	(vram_rsd2, vram_rsd2,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "reserved"))
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
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "part number end with '0'"))
	)
)
PPATUI_FUNCIFY(struct, umc_block_navi1_timings, atui_nullstruct,
	( block_id,  block_id,
		(ATUI_NODISPLAY, ATUI_INLINE, atom_umc_reg_setting_id_config_access),
		(ATUI_NODESCR)
	),

	(gddr6_mr5.gddr6_mr5, gddr6_mr5,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr5),
		(ATUI_NODESCR)
	),
	(gddr6_mr5.reserved, gddr6_mr5_reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(gddr6_mr0.gddr6_mr0, gddr6_mr0,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr0),
		(ATUI_NODESCR)
	),
	(gddr6_mr0.reserved, gddr6_mr0_reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(UMCCTRL_PMG_CMD_EMRS, UMCCTRL_PMG_CMD_EMRS,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(gddr6_mr4.gddr6_mr4, gddr6_mr4,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr4),
		(ATUI_NODESCR)
	),
	(gddr6_mr4.reserved, gddr6_mr4_reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(gddr6_mr8.gddr6_mr8, gddr6_mr8,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr8),
		(ATUI_NODESCR)
	),
	(gddr6_mr8.reserved, gddr6_mr8_reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(DRAMTiming1, DRAMTiming1,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming1),
		(ATUI_NODESCR)
	),
	(DRAMTiming2, DRAMTiming2,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming2),
		(ATUI_NODESCR)
	),
	(DRAMTiming3, DRAMTiming3,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming3),
		(ATUI_NODESCR)
	),
	(DRAMTiming4, DRAMTiming4,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming4),
		(ATUI_NODESCR)
	),
	(DRAMTiming5, DRAMTiming5,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming5),
		(ATUI_NODESCR)
	),
	(DRAMTiming6, DRAMTiming6,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming6),
		(ATUI_NODESCR)
	),
	(DRAMTiming7, DRAMTiming7,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming7),
		(ATUI_NODESCR)
	),
	(DRAMTiming8, DRAMTiming8,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming8),
		(ATUI_NODESCR)
	),
	(DRAMTiming9, DRAMTiming9,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming9),
		(ATUI_NODESCR)
	),
	(DRAMTiming10, DRAMTiming10,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming10),
		(ATUI_NODESCR)
	),
	(DRAMTiming12, DRAMTiming12,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming12),
		(ATUI_NODESCR)
	),
	(DRAMTiming13, DRAMTiming13,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming13),
		(ATUI_NODESCR)
	),
	(DRAMTiming14, DRAMTiming14,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming14),
		(ATUI_NODESCR)
	),
	(DRAMTiming16, DRAMTiming16,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming16),
		(ATUI_NODESCR)
	),
	(DRAMTiming17, DRAMTiming17,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming17),
		(ATUI_NODESCR)
	),
	(DRAMTiming20, DRAMTiming20,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming20),
		(ATUI_NODESCR)
	),
	(DRAMTiming21, DRAMTiming21,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming21),
		(ATUI_NODESCR)
	),
	(DRAMTiming22, DRAMTiming22,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming22),
		(ATUI_NODESCR)
	),
	(DRAMTiming23, DRAMTiming23,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming23),
		(ATUI_NODESCR)
	),
	(DRAMTiming35, DRAMTiming35,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming35),
		(ATUI_NODESCR)
	),
	(DRAMTiming36, DRAMTiming36,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming36),
		(ATUI_NODESCR)
	),
	(tRFC, tRFC,
		(ATUI_NODISPLAY, ATUI_INLINE, TRFCTimingCS01),
		(ATUI_NODESCR)
	),
	(ChanPipeDly, ChanPipeDly,
		(ATUI_NODISPLAY, ATUI_INLINE, ChanPipeDly),
		(ATUI_NODESCR)
	)
)




PPATUI_FUNCIFY(union, atom_umc_register_addr_info_access,
		atomtree_umc_init_reg_block,
	(umc_reg_list, umc_reg_list,
		(ATUI_NODISPLAY, ATUI_DYNARRAY, (
			// Leaf pattern:
			(u32umc_reg_addr, u32umc_reg_addr [%02u],
				(ATUI_HEX, ATUI_BITFIELD, (
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
			(u32umc_reg_data, u32umc_reg_data [%02u],
				(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->u32umc_reg_data, atomtree->umc_reg_num //start, count
		)),
		(ATUI_NODESCR)
	)
)
