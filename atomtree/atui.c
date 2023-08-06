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
	(bios->namespace_var, UI display name,
		(radix, fancy, optional_fancy_args),
		((lang, description)
			(lang, description)
		)
	),
	(bios->namespace_var, UI display name,
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
	(bios->namespace_var, UI display name,
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
	(bios->namespace_var, UI display name,
		(ATUI_HEX, ATUI_ENUM, enum_struct_name),
		(ATUI_NODESCR)
	)


ATUI_INLINE:
If the element should reference a table, a atui_branch to inline,
	(bios->namespace_var, UI display name,
		(ATUI_NAN, ATUI_INLINE, table_to_inline),
		(ATUI_NODESCR)
	)
If you want to import just the leaves of the table, as if it was the leaves of
the branch you're constructing, set the radix to ATUI_NODISPLAY
Also make sure the table is populated with an ATUI_FUNCIFY()


ATUI_STRING, ATUI_ARRAY:
If the element is a string,
	(bios->namespace_var, UI display name,
		(ATUI_NAN, ATUI_STRING),
		(ATUI_NODESCR)
	),
or otherwise an array,
	(bios->namespace_var, UI display name,
		(ATUI_HEX, ATUI_ARRAY),
		(ATUI_NODESCR)
	),
If it's an array, data will be represented in the radix of your choosing.


ATUI_DYNARRAY:
	(doesnt_do_anything, leaf top UI name,
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

dynarray_start_pointer uis the pointer where to start the array within the bios,
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
    s = re.sub("(union|struct)\s+([a-zA-Z0-9_]+)\s+([a-zA-Z0-9_]+)(\[[0-9]+\])?;", "(bios->\g<3>, \g<3>,\n\t\t(ATUI_NODISPLAY, ATUI_INLINE, \g<2>),\n\t\t(ATUI_NODESCR)\n\t),", s)
    s = re.sub("(u?int[0-9]+_t|char)\s+([a-zA-Z0-9_]+)(\s+)?;", "(bios->\g<2>, \g<2>,\n\t\t(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)\n\t),", s)
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
    s = re.sub("[ \t]*uint[0-9]+_t ([A-Za-z0-9_]+)[ \t]*;\s+struct { uint[0-9]+_t\n", "\t(bios->\g<1>, \g<1>,\n\t\t(ATUI_BIN, ATUI_BITFIELD, (\n", s)
    s = re.sub("([a-zA-Z0-9_]+)(\s*):([0-9]+)(\s*)-(\s*)([0-9]+)(\s*)\+1[,;][ \t]*", "\t(\g<1>,\g<2>\g<3>\g<4>,\g<5>\g<6>, ATUI_DEC,", s)
    s = re.sub("ATUI_DEC,(\s*)//(\s*)(.*)", "ATUI_DEC, ((LANG_ENG, \"\g<3>\"))),", s) 
    s = re.sub("ATUI_DEC,\n", "ATUI_DEC, (ATUI_NODESCR)),\n", s)
    s = re.sub(",(\n\t\t\)\), )", "\g<1>", s) 
    print(s)
*/


// basic empty branch mainly to have collapsables
PPATUI_FUNCIFY(struct, atui_nullstruct, atui_nullstruct)


PPATUI_FUNCIFY(struct, atom_common_table_header, atui_nullstruct,
	(bios->structuresize, structuresize,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->format_revision, format_revision,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mainly used for a hw function, when the parser is not backward compatible"))
	),
	(bios->content_revision, content_revision,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "change it when a data table has a structure change, or a hw function has a input/output parameter change"))
	)
)


PPATUI_FUNCIFY(struct, atom_rom_header_v2_2,
		atom_tree, //THE atom_tree struct

	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->atom_bios_string, atom_bios_string,
		(ATUI_NAN, ATUI_STRING),
		((LANG_ENG, "enum atom_string_def atom_bios_string. Signature to distinguish between Atombios and non-atombios,"))
	),
	(bios->bios_segment_address, bios_segment_address,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->protectedmodeoffset, protectedmodeoffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->configfilenameoffset, configfilenameoffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->crc_block_offset, crc_block_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vbios_bootupmessageoffset, vbios_bootupmessageoffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->int10_offset, int10_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pcibusdevinitcode, pcibusdevinitcode,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->iobaseaddress, iobaseaddress,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->subsystem_vendor_id, subsystem_vendor_id,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->subsystem_id, subsystem_id,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pci_info_offset, pci_info_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->masterhwfunction_offset, masterhwfunction_offset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Offest for SW to get all command function offsets, Don't change the position"))
	),
	(bios->masterdatatable_offset, masterdatatable_offset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Offest for SW to get all data table offsets, Don't change the position"))
	),
	(bios->reserved, reserved,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pspdirtableoffset, pspdirtableoffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(struct, atom_master_data_table_v2_1,
		atomtree_master_datatable_v2_1,

	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->utilitypipeline, utilitypipeline,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Offest for the utility to get parser info, Don't change this position!"))
	),
	(bios->multimedia_info, multimedia_info,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smc_dpm_info, smc_dpm_info,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable3, sw_datatable3,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->firmwareinfo, firmwareinfo,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(bios->sw_datatable5, sw_datatable5,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->lcd_info, lcd_info,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(bios->sw_datatable7, sw_datatable7,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smu_info, smu_info,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable9, sw_datatable9,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable10, sw_datatable10,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vram_usagebyfirmware, vram_usagebyfirmware,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(bios->gpio_pin_lut, gpio_pin_lut,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(bios->sw_datatable13, sw_datatable13,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfx_info, gfx_info,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->powerplayinfo, powerplayinfo,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(bios->sw_datatable16, sw_datatable16,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable17, sw_datatable17,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable18, sw_datatable18,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable19, sw_datatable19,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable20, sw_datatable20,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable21, sw_datatable21,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->displayobjectinfo, displayobjectinfo,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(bios->indirectioaccess, indirectioaccess,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "used as an internal one"))
	),
	(bios->umc_info, umc_info,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(bios->sw_datatable25, sw_datatable25,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable26, sw_datatable26,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dce_info, dce_info,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(bios->vram_info, vram_info,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(bios->sw_datatable29, sw_datatable29,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->integratedsysteminfo, integratedsysteminfo,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(bios->asic_profiling_info, asic_profiling_info,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(bios->voltageobject_info, voltageobject_info,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "shared by various SW components"))
	),
	(bios->sw_datatable33, sw_datatable33,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable34, sw_datatable34,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_ENUMER(smudpm_v4_5_i2ccontrollername_e,
	SMC_V4_5_I2C_CONTROLLER_NAME_VR_GFX,
	SMC_V4_5_I2C_CONTROLLER_NAME_VR_SOC,
	SMC_V4_5_I2C_CONTROLLER_NAME_VR_VDDCI,
	SMC_V4_5_I2C_CONTROLLER_NAME_VR_MVDD,
	SMC_V4_5_I2C_CONTROLLER_NAME_LIQUID0,
	SMC_V4_5_I2C_CONTROLLER_NAME_LIQUID1,
	SMC_V4_5_I2C_CONTROLLER_NAME_PLX,
	SMC_V4_5_I2C_CONTROLLER_NAME_SPARE,
	SMC_V4_5_I2C_CONTROLLER_NAME_COUNT
)
PPATUI_ENUMER(smudpm_v4_5_i2ccontrollerthrottler_e,
	SMC_V4_5_I2C_CONTROLLER_THROTTLER_TYPE_NONE,
	SMC_V4_5_I2C_CONTROLLER_THROTTLER_VR_GFX,
	SMC_V4_5_I2C_CONTROLLER_THROTTLER_VR_SOC,
	SMC_V4_5_I2C_CONTROLLER_THROTTLER_VR_VDDCI,
	SMC_V4_5_I2C_CONTROLLER_THROTTLER_VR_MVDD,
	SMC_V4_5_I2C_CONTROLLER_THROTTLER_LIQUID0,
	SMC_V4_5_I2C_CONTROLLER_THROTTLER_LIQUID1,
	SMC_V4_5_I2C_CONTROLLER_THROTTLER_PLX,
	SMC_V4_5_I2C_CONTROLLER_THROTTLER_COUNT
)
PPATUI_ENUMER(smudpm_v4_5_i2ccontrollerprotocol_e,
	SMC_V4_5_I2C_CONTROLLER_PROTOCOL_VR_0,
	SMC_V4_5_I2C_CONTROLLER_PROTOCOL_VR_1,
	SMC_V4_5_I2C_CONTROLLER_PROTOCOL_TMP_0,
	SMC_V4_5_I2C_CONTROLLER_PROTOCOL_TMP_1,
	SMC_V4_5_I2C_CONTROLLER_PROTOCOL_SPARE_0,
	SMC_V4_5_I2C_CONTROLLER_PROTOCOL_SPARE_1,
	SMC_V4_5_I2C_CONTROLLER_PROTOCOL_COUNT
)
// TODO ATUI_DYNARRAY with multiple leaves
PPATUI_FUNCIFY(struct, smudpm_i2c_controller_config_v2, atomtree_smc_dpm_info,
	(bios->Enabled, Enabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Speed, Speed,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding, Padding,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->SlaveAddress, SlaveAddress,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ControllerPort, ControllerPort,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ControllerName, ControllerName,
		(ATUI_DEC, ATUI_ENUM, smudpm_v4_5_i2ccontrollername_e),
		(ATUI_NODESCR)
	),
	(bios->Throttler, Throttler,
		(ATUI_DEC, ATUI_ENUM, smudpm_v4_5_i2ccontrollerthrottler_e),
		(ATUI_NODESCR)
	),
	(bios->I2cProtocol, I2cProtocol,
		(ATUI_DEC, ATUI_ENUM, smudpm_v4_5_i2ccontrollerprotocol_e),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_smc_dpm_info_v4_5, atomtree_smc_dpm_info,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header), (ATUI_NODESCR)
	),

	(bios->MaxVoltageStepGfx, MaxVoltageStepGfx,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value."))
	),
	(bios->MaxVoltageStepSoc, MaxVoltageStepSoc,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value."))
	),

	(bios->VddGfxVrMapping, VddGfxVrMapping,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Use VR_MAPPING* bitfields"))
	),
	(bios->VddSocVrMapping, VddSocVrMapping,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Use VR_MAPPING* bitfields"))
	),
	(bios->VddMem0VrMapping, VddMem0VrMapping,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Use VR_MAPPING* bitfields"))
	),
	(bios->VddMem1VrMapping, VddMem1VrMapping,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Use VR_MAPPING* bitfields"))
	),

	(bios->GfxUlvPhaseSheddingMask, GfxUlvPhaseSheddingMask,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->SocUlvPhaseSheddingMask, SocUlvPhaseSheddingMask,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->ExternalSensorPresent, ExternalSensorPresent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "External RDI connected to TMON (aka TEMP IN)"))
	),
	(bios->Padding8_V, Padding8_V,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Telemetry Settings"))
	),
	(bios->GfxMaxCurrent, GfxMaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->GfxOffset, GfxOffset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Padding_TelemetryGfx, Padding_TelemetryGfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocMaxCurrent, SocMaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->SocOffset, SocOffset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Padding_TelemetrySoc, Padding_TelemetrySoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem0MaxCurrent, Mem0MaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Mem0Offset, Mem0Offset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Padding_TelemetryMem0, Padding_TelemetryMem0,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem1MaxCurrent, Mem1MaxCurrent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Mem1Offset, Mem1Offset,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "in Amps"))
	),
	(bios->Padding_TelemetryMem1, Padding_TelemetryMem1,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO Settings"))
	),
	(bios->AcDcGpio, AcDcGpio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for AC/DC switching"))
	),
	(bios->AcDcPolarity, AcDcPolarity,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO polarity for AC/DC switching"))
	),
	(bios->VR0HotGpio, VR0HotGpio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for VR0 HOT event"))
	),
	(bios->VR0HotPolarity, VR0HotPolarity,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO polarity for VR0 HOT event"))
	),

	(bios->VR1HotGpio, VR1HotGpio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for VR1 HOT event"))
	),
	(bios->VR1HotPolarity, VR1HotPolarity,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO polarity for VR1 HOT event"))
	),
	(bios->GthrGpio, GthrGpio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO pin configured for GTHR Event"))
	),
	(bios->GthrPolarity, GthrPolarity,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "replace GPIO polarity for GTHR"))
	),

	(bios->LedPin0, LedPin0,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "LED Display Settings GPIO number for LedPin[0]"))
	),
	(bios->LedPin1, LedPin1,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO number for LedPin[1]"))
	),
	(bios->LedPin2, LedPin2,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO number for LedPin[2]"))
	),
	(bios->padding8_4, padding8_4,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GFXCLK PLL Spread Spectrum"))
	),
	(bios->PllGfxclkSpreadEnabled, PllGfxclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "on or off"))
	),
	(bios->PllGfxclkSpreadPercent, PllGfxclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(bios->PllGfxclkSpreadFreq, PllGfxclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),

	(bios->DfllGfxclkSpreadEnabled, DfllGfxclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GFXCLK DFLL Spread Spectrum on or off"))
	),
	(bios->DfllGfxclkSpreadPercent, DfllGfxclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(bios->DfllGfxclkSpreadFreq, DfllGfxclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),

	(bios->UclkSpreadEnabled, UclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "UCLK Spread Spectrum  on or off"))
	),
	(bios->UclkSpreadPercent, UclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(bios->UclkSpreadFreq, UclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),

	(bios->SoclkSpreadEnabled, SoclkSpreadEnabled,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "SOCCLK Spread Spectrum on or off"))
	),
	(bios->SocclkSpreadPercent, SocclkSpreadPercent,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Q4.4"))
	),
	(bios->SocclkSpreadFreq, SocclkSpreadFreq,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "kHz"))
	),

	(bios->TotalBoardPower, TotalBoardPower,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Only needed for TCP Estimated case, where TCP = TGP+Total Board Power"))
	),
	(bios->BoardPadding, BoardPadding,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Mvdd Svi2 Div Ratio Setting"))
	),
	(bios->MvddRatio, MvddRatio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "This is used for MVDD Vid workaround. It has 16 fractional bits (Q16.16)"))
	),

	(bios->BoardReserved, BoardReserved,
		(ATUI_NAN, ATUI_ARRAY), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, atombios_firmware_capability, atui_nullstruct,
	(bios->firmware_capability, firmware_capability,
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
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->firmware_revision, firmware_revision,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_sclk_in10khz, bootup_sclk_in10khz,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mclk_in10khz, bootup_mclk_in10khz,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->firmware_capability, firmware_capability,
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability),
		(ATUI_NODESCR)
	),
	(bios->main_call_parser_entry, main_call_parser_entry,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "direct address of main parser call in VBIOS binary."))
	),
	(bios->bios_scratch_reg_startaddr, bios_scratch_reg_startaddr,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "1st bios scratch register dword address"))
	),
	(bios->bootup_vddc_mv, bootup_vddc_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vddci_mv, bootup_vddci_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvddc_mv, bootup_mvddc_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vddgfx_mv, bootup_vddgfx_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem_module_id, mem_module_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->coolingsolution_id, coolingsolution_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0: Air cooling; 1: Liquid cooling ..."))
	),
	(bios->reserved1, reserved1,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->mc_baseaddr_high, mc_baseaddr_high,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_baseaddr_low, mc_baseaddr_low,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved2, reserved2,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v3_2, atomtree_firmware_info,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->firmware_revision, firmware_revision,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_sclk_in10khz, bootup_sclk_in10khz,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mclk_in10khz, bootup_mclk_in10khz,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->firmware_capability, firmware_capability,
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability),
		(ATUI_NODESCR)
	),
	(bios->main_call_parser_entry, main_call_parser_entry,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "direct address of main parser call in VBIOS binary."))
	),
	(bios->bios_scratch_reg_startaddr, bios_scratch_reg_startaddr,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "1st bios scratch register dword address"))
	),
	(bios->bootup_vddc_mv, bootup_vddc_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vddci_mv, bootup_vddci_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvddc_mv, bootup_mvddc_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vddgfx_mv, bootup_vddgfx_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem_module_id, mem_module_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->coolingsolution_id, coolingsolution_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0: Air cooling; 1: Liquid cooling ..."))
	),
	(bios->reserved1, reserved1,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->mc_baseaddr_high, mc_baseaddr_high,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_baseaddr_low, mc_baseaddr_low,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->board_i2c_feature_id, board_i2c_feature_id,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "enum of atom_board_i2c_feature_id_def"))
	),
	(bios->board_i2c_feature_gpio_id, board_i2c_feature_gpio_id,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "i2c id find in gpio_lut data table gpio_id"))
	),
	(bios->board_i2c_feature_slave_addr, board_i2c_feature_slave_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved3, reserved3,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvddq_mv, bootup_mvddq_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvpp_mv, bootup_mvpp_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->zfbstartaddrin16mb, zfbstartaddrin16mb,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved2, reserved2,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v3_3, atomtree_firmware_info,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->firmware_revision, firmware_revision,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_sclk_in10khz, bootup_sclk_in10khz,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mclk_in10khz, bootup_mclk_in10khz,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->firmware_capability, firmware_capability,
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability),
		(ATUI_NODESCR)
	),
	(bios->main_call_parser_entry, main_call_parser_entry,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "direct address of main parser call in VBIOS binary."))
	),
	(bios->bios_scratch_reg_startaddr, bios_scratch_reg_startaddr,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "1st bios scratch register dword address"))
	),
	(bios->bootup_vddc_mv, bootup_vddc_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vddci_mv, bootup_vddci_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvddc_mv, bootup_mvddc_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vddgfx_mv, bootup_vddgfx_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem_module_id, mem_module_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->coolingsolution_id, coolingsolution_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0: Air cooling; 1: Liquid cooling ..."))
	),
	(bios->reserved1, reserved1,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->mc_baseaddr_high, mc_baseaddr_high,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_baseaddr_low, mc_baseaddr_low,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->board_i2c_feature_id, board_i2c_feature_id,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "enum of atom_board_i2c_feature_id_def"))
	),
	(bios->board_i2c_feature_gpio_id, board_i2c_feature_gpio_id,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "i2c id find in gpio_lut data table gpio_id"))
	),
	(bios->board_i2c_feature_slave_addr, board_i2c_feature_slave_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved3, reserved3,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvddq_mv, bootup_mvddq_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvpp_mv, bootup_mvpp_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->zfbstartaddrin16mb, zfbstartaddrin16mb,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pplib_pptable_id, pplib_pptable_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "if pplib_pptable_id!=0, pplib get powerplay table inside driver instead of from VBIOS"))
	),
	(bios->reserved2, reserved2,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v3_4, atomtree_firmware_info,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->firmware_revision, firmware_revision,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_sclk_in10khz, bootup_sclk_in10khz,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mclk_in10khz, bootup_mclk_in10khz,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->firmware_capability, firmware_capability,
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability),
		(ATUI_NODESCR)
	),
	(bios->main_call_parser_entry, main_call_parser_entry,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "direct address of main parser call in VBIOS binary."))
	),
	(bios->bios_scratch_reg_startaddr, bios_scratch_reg_startaddr,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "1st bios scratch register dword address"))
	),
	(bios->bootup_vddc_mv, bootup_vddc_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vddci_mv, bootup_vddci_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvddc_mv, bootup_mvddc_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vddgfx_mv, bootup_vddgfx_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem_module_id, mem_module_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->coolingsolution_id, coolingsolution_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0: Air cooling; 1: Liquid cooling ... */"))
	),
	(bios->reserved1, reserved1,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->mc_baseaddr_high, mc_baseaddr_high,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_baseaddr_low, mc_baseaddr_low,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->board_i2c_feature_id, board_i2c_feature_id,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "enum of atom_board_i2c_feature_id_def"))
	),
	(bios->board_i2c_feature_gpio_id, board_i2c_feature_gpio_id,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "i2c id find in gpio_lut data table gpio_id"))
	),
	(bios->board_i2c_feature_slave_addr, board_i2c_feature_slave_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ras_rom_i2c_slave_addr, ras_rom_i2c_slave_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvddq_mv, bootup_mvddq_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvpp_mv, bootup_mvpp_mv,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->zfbstartaddrin16mb, zfbstartaddrin16mb,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pplib_pptable_id, pplib_pptable_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "if pplib_pptable_id!=0, pplib get powerplay table inside driver instead of from VBIOS"))
	),
	(bios->mvdd_ratio, mvdd_ratio,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mvdd_raio = (real mvdd in power rail)*1000/(mvdd_output_from_svi2)"))
	),
	(bios->hw_bootup_vddgfx_mv, hw_bootup_vddgfx_mv,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "hw default vddgfx voltage level decide by board strap"))
	),
	(bios->hw_bootup_vddc_mv, hw_bootup_vddc_mv,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "hw default vddc voltage level decide by board strap"))
	),
	(bios->hw_bootup_mvddc_mv, hw_bootup_mvddc_mv,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "hw default mvddc voltage level decide by board strap"))
	),
	(bios->hw_bootup_vddci_mv, hw_bootup_vddci_mv,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "hw default vddci voltage level decide by board strap"))
	),
	(bios->maco_pwrlimit_mw, maco_pwrlimit_mw,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "bomaco mode power limit in unit of m-watt"))
	),
	(bios->usb_pwrlimit_mw, usb_pwrlimit_mw,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "power limit when USB is enable in unit of m-watt"))
	),
	(bios->fw_reserved_size_in_kb, fw_reserved_size_in_kb,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "VBIOS reserved extra fw size in unit of kb."))
	),
	(bios->pspbl_init_done_reg_addr, pspbl_init_done_reg_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pspbl_init_done_value, pspbl_init_done_value,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pspbl_init_done_check_timeout, pspbl_init_done_check_timeout,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "time out in unit of us when polling pspbl init done"))
	),
	(bios->reserved, reserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)








PPATUI_FUNCIFY(union, gddr6_mr0, atui_nullstruct,
	(bios->gddr6_mr0, gddr6_mr0,
		(ATUI_BIN, ATUI_BITFIELD, (
			(WLmrs,    2,0, ATUI_DEC,
				((LANG_ENG, "tCWL, 8,9,10,11,12,5,6,7."))
			),
			(RLmrs,    6,3, ATUI_DEC,
				((LANG_ENG, "tCL, starting from 5. See MR8 OP8, MR12 OP3"))
			),
			(testmode, 7,7, ATUI_DEC,
				((LANG_ENG, "Test mode; behavior is vendor specific"))
			),
			(WRmrs,   11,8, ATUI_DEC,
				((LANG_ENG, "tWR for auto-pre, 0=4,1=5..47=51. See MR8, MR12"))
			),
			(ID,      15,12, ATUI_DEC,
				((LANG_ENG, "MR 0"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr1, atui_nullstruct,
	(bios->gddr6_mr1, gddr6_mr1,
		(ATUI_BIN, ATUI_BITFIELD, (
			(drive_stren,  1,0, ATUI_DEC,
				((LANG_ENG, "0=Auto Cal.(60/40), 1=AC(48/40). 2,3 vndr spec"))
			),
			(data_term,    3,2, ATUI_DEC,
				((LANG_ENG, "0=disabled 1=60ohm 2=120ohm 3=48ohm"))
			),
			(PLLDLL_range, 5,4, ATUI_DEC,
				((LANG_ENG, "min-to-max WCK freq, vendor specific"))
			),
			(Cal_Upd,      6,6, ATUI_DEC,
				((LANG_ENG, "Auto Calibration Engine, 0=enabled."))
			),
			(PLL_DLL,      7,7, ATUI_DEC,
				((LANG_ENG, "0=disabled 1=enabled"))
			),
			(RDBI,         8,8, ATUI_DEC,
				((LANG_ENG, "Data Bus Inversion, for reads.   0=enabled"))
			),
			(WDBI,         9,9, ATUI_DEC,
				((LANG_ENG, "Data Bus Inversion, for writes.  1=disabled"))
			),
			(CABI,        10,10, ATUI_DEC,
				((LANG_ENG, "Command-address bus inversion.  0=enabled"))
			),
			(PLLDLL_reset,14,11, ATUI_DEC,
				((LANG_ENG, "1 = reset. self-clears after reset."))
			),
			(ID,          15,12, ATUI_DEC,
				((LANG_ENG, "MR 1"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr2, atui_nullstruct,
	(bios->gddr6_mr2, gddr6_mr2,
		(ATUI_BIN, ATUI_BITFIELD, (
			(OCD_up,       2,0, ATUI_DEC,
				((LANG_ENG, "output driver pullup offset. 0=0, Two's Compl."))
			),
			(OCD_down,     5,3, ATUI_DEC,
				((LANG_ENG, "pulldown. See JES250D Figure 33."))
			),
			(self_refresh, 7,6, ATUI_DEC,
				((LANG_ENG, "0=32ms, 1-2 vendor specific, 3=temp controlled"))
			),
			(EDC_mode,     8,8, ATUI_DEC,
				((LANG_ENG, "0=full data rate, 1=half"))
			),
			(RDQS,         9,9, ATUI_DEC,
				((LANG_ENG, "1 = EDC pins will act as RDQS; no CRC."))
			),
			(CADT_SRF,    10,10, ATUI_DEC,
				((LANG_ENG, "Self refesh while CA training"))
			),
			(EDC_HR,      11,11, ATUI_DEC,
				((LANG_ENG, "EDC hold data rate 0=full, 1=half"))
			),
			(ID,          15,12, ATUI_DEC,
				((LANG_ENG, "MR 2"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr3, atui_nullstruct,
	(bios->gddr6_mr3, gddr6_mr3,
		(ATUI_BIN, ATUI_BITFIELD, (
			(dataWCK_term_offset, 2,0, ATUI_DEC,
				((LANG_ENG, "DQ, DBI and WCK termination offset."))
			),
			(CA_term_offset,      5,3, ATUI_DEC,
				((LANG_ENG, "command address. See MR2."))
			),
			(DRAM_info,           7,6, ATUI_DEC,
				((LANG_ENG, "0=off 1=vndr ID1 2=temp 3=vndr ID2"))
			),
			(WR_scaling,          9,8, ATUI_DEC,
				((LANG_ENG, "1x 2x 3x value of tWR in MR8 and MR0"))
			),
			(bank_groups,        11,10, ATUI_DEC,
				((LANG_ENG, "0,1=off, 2=on tCCDL=4, 3=on tCCDL=3"))
			),
			(ID,                 15,12, ATUI_DEC,
				((LANG_ENG, "MR 3"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr4, atui_nullstruct,
	(bios->gddr6_mr4, gddr6_mr4,
		(ATUI_BIN, ATUI_BITFIELD, (
			(EDC_hold_pattern, 3,0, ATUI_DEC,
				((LANG_ENG, "little-endian. pattern during EDC idle"))
			),
			(CRCWL,            6,4, ATUI_DEC,
				((LANG_ENG, "15,16,RFU,10,11..21,RFU. See MR12 OP4"))
			),
			(CRCRL,            8,7, ATUI_DEC,
				((LANG_ENG, "CRC latency for reads. 4,1,2,3."))
			),
			(RDCRC,            9,9, ATUI_DEC,
				((LANG_ENG, "read CRC 0=enable"))
			),
			(WRCRC,           10,10, ATUI_DEC,
				((LANG_ENG, "write CRC 0=enable"))
			),
			(EDC_hold_invert, 11,11, ATUI_DEC,
				((LANG_ENG, "0 = EDC hold pattern not inverted"))
			),
			(ID,              15,12, ATUI_DEC,
				((LANG_ENG, "MR 4"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr5, atui_nullstruct,
	(bios->gddr6_mr5, gddr6_mr5,
		(ATUI_BIN, ATUI_BITFIELD, (
			(LP1,       0,0, ATUI_DEC,
				((LANG_ENG, "0=off, Low Power Mode 1, relax several core params"))
			),
			(LP2,       1,1, ATUI_DEC,
				((LANG_ENG, "WCK recievers turned off during powerdown."))
			),
			(LP3,       2,2, ATUI_DEC,
				((LANG_ENG, "no read/write training and temp reads during REFab"))
			),
			(PLLDLL_BW, 5,3, ATUI_DEC,
				((LANG_ENG, "PLL/DLL bandwidth. All except 0 vendor specific"))
			),
			(RAS,      11,6, ATUI_DEC,
				((LANG_ENG, "0,1,2...63. tRAS for auto precharge"))
			),
			(ID,       15,12, ATUI_DEC,
				((LANG_ENG, "MR 5"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr6, atui_nullstruct,
	(bios->gddr6_mr6, gddr6_mr6,
		(ATUI_BIN, ATUI_BITFIELD, (
			(VREFD_level,  6,0, ATUI_DEC,
				((LANG_ENG, "0.005x steps of VDDQ, from 0=0.49x to 95=0.965x"))
			),
			(pin_subaddr, 11,7, ATUI_DEC,
				((LANG_ENG, "pin to configure the VREFD for. See JESD250"))
			),
			(ID,          15,12, ATUI_DEC,
				((LANG_ENG, "MR 6"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr7, atui_nullstruct,
	(bios->gddr6_mr7, gddr6_mr7,
		(ATUI_BIN, ATUI_BITFIELD, (
			(WCK2CK_AP,       0,0, ATUI_DEC,
				((LANG_ENG, "WCK alignment point. 0=inside 1=at balls"))
			),
			(hibernate,       1,1, ATUI_DEC,
				((LANG_ENG, "1=Hibernate Self Refresh mode. self clearing"))
			),
			(PLL_delay_comp,  2,2, ATUI_DEC,
				((LANG_ENG, "1=(PLL feedback delay == WCK clock tree)"))
			),
			(low_freq_mode,   3,3, ATUI_DEC,
				((LANG_ENG, "1=reduce power of input RX, clock trees"))
			),
			(WCK2CK_autosync, 4,4, ATUI_DEC,
				((LANG_ENG, "1=auto sync, reduces WCK2CK MRS to 2."))
			),
			(DQ_preamble,     5,5, ATUI_DEC,
				((LANG_ENG, "1=preamble on DQ, DBI_n for gapped reads."))
			),
			(half_VREFC,      6,6, ATUI_DEC,
				((LANG_ENG, "0=0.7x VDDQ, 1=0.5x See MR6, MR9"))
			),
			(half_VREFD,      7,7, ATUI_DEC,
				((LANG_ENG, "0=prog'd VREFD,DFE. 1=0.5x VDDQ. See MR6,MR9"))
			),
			(VDD_range,       9,8, ATUI_DEC,
				((LANG_ENG, "0>1>2>3. Adapt to lower VDD voltages"))
			),
			(WCK_DCC,        11,10, ATUI_DEC,
				((LANG_ENG, "Duty Cycle Corr. 0=off,1=start,2=RFU,3=hold"))
			),
			(ID,             15,12, ATUI_DEC,
				((LANG_ENG, "MR 7"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr8, atui_nullstruct,
	(bios->gddr6_mr8, gddr6_mr8,
		(ATUI_BIN, ATUI_BITFIELD, (
			(CA_low_term,  1,0, ATUI_DEC,
				((LANG_ENG, "0=disable, 1=60ohm, 2=120, 3=rsvd. For CA[3:0]"))
			),
			(CA_high_term, 3,2, ATUI_DEC,
				((LANG_ENG, "For CA[10:4]"))
			),
			(CA_TO,        4,4, ATUI_DEC,
				((LANG_ENG, "Command Address Termin. Override 1=use CAL,CAH"))
			),
			(EDC_hiZ,      5,5, ATUI_DEC,
				((LANG_ENG, "1=Hi-Z state. Precidence over all other states."))
			),
			(CK_auto_cal,  6,6, ATUI_DEC,
				((LANG_ENG, "0=auto calib. during REFab disabled, 1=enabled"))
			),
			(REFpb,        7,7, ATUI_DEC,
				((LANG_ENG, "0=per-bank, 1=per-2-bank"))
			),
			(RL_EHF,       8,8, ATUI_DEC,
				((LANG_ENG, "Extends RLmrs of MR0 from 4 to 5 bits."))
			),
			(WR_EHF,       9,9, ATUI_DEC,
				((LANG_ENG, "Extends WRmrs of MR0 from 4 to 5 bits."))
			),
			(CK_term,     11,10, ATUI_DEC,
				((LANG_ENG, "0=reset, 1=60ohm,2=120-ohm, 3=disabled"))
			),
			(ID,          15,12, ATUI_DEC,
				((LANG_ENG, "MR 8"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr9, atui_nullstruct,
	(bios->gddr6_mr9, gddr6_mr9,
		(ATUI_BIN, ATUI_BITFIELD, (
			(DFE,          3,0, ATUI_DEC,
				((LANG_ENG, "0=off, in steps of +-0.5% VDDQ or 7mV"))
			),
			(RFU,          6,4, ATUI_DEC,
				((LANG_ENG, "reserved"))
			),
			(pin_subaddr, 11,7, ATUI_DEC,
				((LANG_ENG, "see JESD250"))
			),
			(ID,          15,12, ATUI_DEC,
				((LANG_ENG, "MR 9"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr10, atui_nullstruct,
	(bios->gddr6_mr10, gddr6_mr10,
		(ATUI_BIN, ATUI_BITFIELD, (
			(VREFC_offset,  3,0, ATUI_DEC,
				((LANG_ENG, "CA bus. Two's Complement? 0b1000=0 is a typo?"))
			),
			(WCK_inv_byte0, 5,4, ATUI_DEC,
				((LANG_ENG, "for WCK2CK training 0=0;1=90 degr;2=180;3=270"))
			),
			(WCK_inv_byte1, 7,6, ATUI_DEC,
				((LANG_ENG, "B1 on chan A, B0 on chan B ignored if WCK/word"))
			),
			(WCK2CK,        8,8, ATUI_DEC,
				((LANG_ENG, "1=enable WCK2CK alignment training"))
			),
			(WCK_ratio,     9,9, ATUI_DEC,
				((LANG_ENG, "0=half data rate, 1=full data rate"))
			),
			(WCK_term,     11,10, ATUI_DEC,
				((LANG_ENG, "0=disabled, 1=60 ohm, 2=120, 3=reserved"))
			),
			(ID,           15,12, ATUI_DEC,
				((LANG_ENG, "MR 10"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr11, atui_nullstruct, 
	(bios->gddr6_mr11, gddr6_mr11,
		(ATUI_BIN, ATUI_BITFIELD, (
			(PASR_2bank_mask,  7,0, ATUI_DEC,
				((LANG_ENG, "1=banks0,1; 2=2,3; 4=4,5; 8=6,7 .. 128=14,15"))
			),
			(PASR_rowseg_mask,11,8, ATUI_DEC,
				((LANG_ENG, "two MSB of row addr. 0=00;2=01;4=10;8=11 15=all"))
			),
		(ID,                  15,12, ATUI_DEC,
				((LANG_ENG, "MR 11"))
			)
		)),
		((LANG_ENG, "0=refresh enabled 1=refresh blocked for paticular segment or banks"))
	)
)
PPATUI_FUNCIFY(union, gddr6_mr12, atui_nullstruct,
	(bios->gddr6_mr12, gddr6_mr12,
		(ATUI_BIN, ATUI_BITFIELD, (
			(VDDQ_off,  0,0, ATUI_DEC,
				((LANG_ENG, "0=disabled. For Hibernate Self Refresh"))
			),
			(P2BR_addr, 1,1, ATUI_DEC,
				((LANG_ENG, "0=LSB/BA0 1=MSB/BA3. Select \"Dont Care\" for REFp2b"))
			),
			(PRBS,      2,2, ATUI_DEC,
				((LANG_ENG, "1=Psudorandom bit stream instead of EDC hold"))
			),
			(RL_EHF2,   3,3, ATUI_DEC,
				((LANG_ENG, "Extends RLmrs from 5 bits to 6 bits. See MR0, MR8"))
			),
			(CRCWL_EHF, 4,4, ATUI_DEC,
				((LANG_ENG, "Extends CRCWL from 3 bits to 4 bits. See MR4."))
			),
			(WR_EHF2,   5,5, ATUI_DEC,
				((LANG_ENG, "Extends WRmrs from 5 bits to 6 bits. See MR0, MR8"))
			),
			(RFU,      11,6, ATUI_DEC,
				((LANG_ENG, "reserved."))
			),
			(ID,       15,12, ATUI_DEC,
				((LANG_ENG, "MR 12"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr13, atui_nullstruct,
	(bios->gddr6_mr13, gddr6_mr13,
		(ATUI_BIN, ATUI_BITFIELD, (
			(vendor_specific, 11,0, ATUI_DEC,
				((LANG_ENG, "vendor specific features."))
			),
			(ID,              15,12, ATUI_DEC,
				((LANG_ENG, "MR 13"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr14, atui_nullstruct,
	(bios->gddr6_mr14, gddr6_mr14,
		(ATUI_BIN, ATUI_BITFIELD, (
			(vendor_specific, 11,0, ATUI_DEC,
				((LANG_ENG, "vendor specific features."))
			),
			(ID,              15,12, ATUI_DEC,
				((LANG_ENG, "MR 14"))
			)
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, gddr6_mr15, atui_nullstruct,
	(bios->gddr6_mr15, gddr6_mr15,
		(ATUI_BIN, ATUI_BITFIELD, (
			(MRS_to_chan_A, 0,0, ATUI_DEC,
				((LANG_ENG, "MRS to the two channels for individual config"))
			),
			(MRS_to_chan_B, 1,1, ATUI_DEC,
				((LANG_ENG, "0=unblocked 1=blocked"))
			),
			(CA_training,   3,2, ATUI_DEC,
				((LANG_ENG, "0=off 1=rising of CK, 2=falling, 3=CABI_n,CA10"))
			),
			(unused,        11,4, ATUI_DEC,
				((LANG_ENG, "defined to be absent"))
			),
			(ID,            15,12, ATUI_DEC,
				((LANG_ENG, "MR 15"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, DRAMTiming1, atui_nullstruct,
	(bios->DRAMTiming1, DRAMTiming1,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tCL,     5,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,   7,6, ATUI_DEC, (ATUI_NODESCR)),
			(tRAS,   14,8, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,  15,15, ATUI_DEC, (ATUI_NODESCR)),
			(tRCDRD, 21,16, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd2,  23,22, ATUI_DEC, (ATUI_NODESCR)),
			(tRCDWR, 29,24, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd3,  31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming2, atui_nullstruct,
	(bios->DRAMTiming2, DRAMTiming2,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tRC_S,  7,0, ATUI_DEC, ((LANG_ENG, "per-bank"))),
			(tRC_L, 15,8, ATUI_DEC, ((LANG_ENG, "all-bank?"))),
			(tRP_S, 21,16, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0, 23,22, ATUI_DEC, (ATUI_NODESCR)),
			(tRP_L, 29,24, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1, 31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming3, atui_nullstruct,
	(bios->DRAMTiming3, DRAMTiming3,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tRRD_S,  4,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,   7,5, ATUI_DEC, (ATUI_NODESCR)),
			(tRRD_L, 12,8, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,  23,13, ATUI_DEC,
				((LANG_ENG, "3+5+3, middle 5 has tRRDDLR for 3D stacked memory."))
			),
			(tRTP,   28,24, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd2,  31,29, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming4, atui_nullstruct,
	(bios->DRAMTiming4, DRAMTiming4,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tFAW,   6,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,  7,7, ATUI_DEC, (ATUI_NODESCR)),
			(t32AW, 16,8, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1, 31,17, ATUI_DEC, ((LANG_ENG, "1, tFAWSLR:6, 1, tFAWDLR:6, 1")))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming5, atui_nullstruct,
	(bios->DRAMTiming5, DRAMTiming5,
		(ATUI_BIN, ATUI_BITFIELD, (
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
	(bios->DRAMTiming6, DRAMTiming6,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tWR,    6,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0, 31,7, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming7, atui_nullstruct,
	(bios->DRAMTiming7, DRAMTiming7,
		(ATUI_BIN, ATUI_BITFIELD, (
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
	(bios->DRAMTiming8, DRAMTiming8,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tRDRD_DD,   3,0, ATUI_DEC,
				((LANG_ENG, "Different DIMM"))
			),
			(rsvd0,      7,4, ATUI_DEC, (ATUI_NODESCR)),
			(tRDRD_SD,  11,8, ATUI_DEC,
				((LANG_ENG, "Same DIMM"))
			),
			(rsvd1,     15,12, ATUI_DEC, (ATUI_NODESCR)),
			(tRDRD_SC,  19,16, ATUI_DEC,
				((LANG_ENG, "JEDEC tCCD_S"))
			),
			(rsvd2,     23,20, ATUI_DEC, (ATUI_NODESCR)),
			(tRDRD_SCL, 27,24, ATUI_DEC,
				((LANG_ENG, "tCCD_L"))
			),
			(rsvd3,     29,28, ATUI_DEC, (ATUI_NODESCR)),
			(tRDRD_BAN, 31,30, ATUI_DEC,
				((LANG_ENG, "Preamble2t ?1:0. Ban traffic:1=tCCD=5;2=tCCD=5,6"))
			)
		)),
		((LANG_ENG, "Specifies the minimum number of cycles from the last clock of virtual CAS of the first burst operation to the clock in which CAS is asserted for a following bust operation. A value of 1 means 0 idle clock cycles between two bursts; 2 = 1 idle cycle."))
	)
)
PPATUI_FUNCIFY(union, DRAMTiming9, atui_nullstruct,
	(bios->DRAMTiming9, DRAMTiming9,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tWRWR_MW,   4,0, ATUI_DEC, ((LANG_ENG, "masked write; GDDR"))),
			(rsvd0,     15,5, ATUI_DEC, (ATUI_NODESCR)),
			(tWRWR_SC,  19,16, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,     23,20, ATUI_DEC, (ATUI_NODESCR)),
			(tWRWR_SCL, 29,24, ATUI_DEC, (ATUI_NODESCR)),
			(tWRWR_BAN, 31,30, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming10, atui_nullstruct, 
	(bios->DRAMTiming10, DRAMTiming10,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tWRRD,       3,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,       7,4, ATUI_DEC, (ATUI_NODESCR)),
			(tRDWR,      13,8, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,      15,14, ATUI_DEC, (ATUI_NODESCR)),
			(RDRspDelay, 21,16, ATUI_DEC, (ATUI_NODESCR)),
			(tREFTTAdj,  28,22, ATUI_DEC,
				((LANG_ENG, "was tREFTT; a typo? tREFTR is a GDDR6 timing"))
			),
			(rsvd2,      31,29, ATUI_DEC, (ATUI_NODESCR))
		)),
		((LANG_ENG, "tWRRD and tRDWR also follows the 'last clock of virtual CAS'. LD = tCL - tCWL ; tWRRD has x-LD and tRDWR has y+LD. LD is about making sure one burst happens after the other. And x and y follow the 'last clock of virtual CAS' and are about making sure the data bus is stable."))
	)
)
PPATUI_FUNCIFY(union, DRAMTiming12, atui_nullstruct,
	(bios->DRAMTiming12, DRAMTiming12,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tREFI, 15,0, ATUI_DEC,
				((LANG_ENG, "tREF; the microseconds not milliseconds one"))
			),
			(rsvd0, 31,16, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming13, atui_nullstruct,
	(bios->DRAMTiming13, DRAMTiming13,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tMRD,   5,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,  7,6, ATUI_DEC, (ATUI_NODESCR)),
			(tMOD,  13,8, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1, 31,14, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming14, atui_nullstruct,
	(bios->DRAMTiming14, DRAMTiming14,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tXS,   10,0, ATUI_DEC,
				((LANG_ENG, "exit self refreh to not requiring a locked DLL"))
			),
			(rsvd0, 15,11, ATUI_DEC, (ATUI_NODESCR)),
			(tDLLK, 26,16, ATUI_DEC,
				((LANG_ENG, "exit self refresh to requiring a locked DLL"))
			),
			(rsvd1, 31,27, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming15, atui_nullstruct, 
	(bios->DRAMTiming15, DRAMTiming15,
		(ATUI_BIN, ATUI_BITFIELD, (
			(AlertCrcDly,  6,0, ATUI_DEC,
				((LANG_ENG, "expected alert crc error dely, in memclocks"))
			),
			(rsvd0,        7,7, ATUI_DEC, (ATUI_NODESCR)),
			(AlertParDly, 14,8, ATUI_DEC,
				((LANG_ENG, "Parity error"))
			),
			(PL,          18,15, ATUI_DEC,
				((LANG_ENG, "Cmd/Addr Parity Latency. See DDR4 MR5"))
			),
			(rsvd1,       22,19, ATUI_DEC, (ATUI_NODESCR)),
			(RankBusyDly, 29,23, ATUI_DEC,
				((LANG_ENG, "max of CRC/ECC alert delays"))
			),
			(rsvd2,       31,30, ATUI_DEC, (ATUI_NODESCR))
		)),
		((LANG_ENG, "DDR reliability RAS"))
	)
)
PPATUI_FUNCIFY(union, DRAMTiming16, atui_nullstruct,
	(bios->DRAMTiming16, DRAMTiming16,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tXSMRS, 10,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,  31,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming17, atui_nullstruct,
	(bios->DRAMTiming17, DRAMTiming17,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tPD,           4,0, ATUI_DEC, (ATUI_NODESCR)),
			(tCKSRE,        10,5, ATUI_DEC, (ATUI_NODESCR)),
			(tCKSRX,        16,11, ATUI_DEC, (ATUI_NODESCR)),
			(PwrDownDly,    24,17, ATUI_DEC,
				((LANG_ENG, "last command to PowerDown"))
			),
			(AggPwrDownDly, 30,25, ATUI_DEC,
				((LANG_ENG, "last DRAM activity to precharge, for PD"))
			),
			(rsvd0,         31,31, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming20, atui_nullstruct,
	(bios->DRAMTiming20, DRAMTiming20,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tRFCSB, 10,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,  15,11, ATUI_DEC, (ATUI_NODESCR)),
			(tSTAG,  23,16, ATUI_DEC, ((LANG_ENG, "ref-to-ref different rank"))),
			(rsvd1,  31,24, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming21, atui_nullstruct,
	(bios->DRAMTiming21, DRAMTiming21,
		(ATUI_BIN, ATUI_BITFIELD, (
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
	(bios->DRAMTiming22, DRAMTiming22,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tRDDATA_EN,   6,0, ATUI_DEC,
				((LANG_ENG, "tCL-n; GD6 n=1, D4 n=5. READ to dfi_rddata_en"))
			),
			(rsvd0,        7,7, ATUI_DEC, (ATUI_NODESCR)),
			(tPHY_WRLAT,  13,8, ATUI_DEC,
				((LANG_ENG, "tCWL-n; GD6 n=2, D4 n=5. WRITE to dfi_wrdata_en"))
			),
			(rsvd1,       16,14, ATUI_DEC, (ATUI_NODESCR)),
			(tPHY_RDLAT,  22,17, ATUI_DEC,
				((LANG_ENG, "dfi_rddata_en to dfi_rddata_vld dely"))
			),
			(rsvd2,       24,23, ATUI_DEC, (ATUI_NODESCR)),
			(tPHY_WRDATA, 27,25, ATUI_DEC,
				((LANG_ENG, "dfi_wrdata_en to dfi_wrdata delay"))
			),
			(tPARIN_LAT,  29,28, ATUI_DEC,
				((LANG_ENG, "ctrl signals to parity delay"))
			),
			(rsvd3,       31,30, ATUI_DEC, (ATUI_NODESCR))
		)),
		((LANG_ENG, ""DFI" is shorthand for "DDR PHY""))
	)
)
PPATUI_FUNCIFY(union, DRAMTiming23, atui_nullstruct,
	(bios->DRAMTiming23, DRAMTiming23,
		(ATUI_BIN, ATUI_BITFIELD, (
			(LpDly,      5,0, ATUI_DEC,
				((LANG_ENG, "hysteresis before placing PHY into low power"))
			),
			(rsvd0,      7,6, ATUI_DEC, (ATUI_NODESCR)),
			(LpExitDly,  13,8, ATUI_DEC,
				((LANG_ENG, "min memclk before taking a rank out of powerdown"))
			),
			(rsvd1,      15,14, ATUI_DEC, (ATUI_NODESCR)),
			(CKESTAGDLY, 19,16, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd3,      31,20, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming34, atui_nullstruct,
	(bios->DRAMTiming34, DRAMTiming34,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tPhyupd_resp, 3,0, ATUI_DEC, (ATUI_NODESCR)),
			(tRDEDC_EN,    10,4, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0,        11,11, ATUI_DEC, (ATUI_NODESCR)),
			(tWREDC_EN,    18,12, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,        31,19, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, DRAMTiming35, atui_nullstruct, 
	(bios->DRAMTiming35, DRAMTiming35,
		(ATUI_BIN, ATUI_BITFIELD, (
			(ReceiverWait, 10,0, ATUI_DEC,
				((LANG_ENG, "Wait time to start recovery sequence"))
			),
			(CmdStageCnt,  21,11, ATUI_DEC,
				((LANG_ENG, "Recov. seq. cmd stagger counter. See CmdStgFrc. CmdStgFrc:1; 1=enable recovery command stagger in recovery phase"))
			),
			(rsvd0,        23,22, ATUI_DEC, (ATUI_NODESCR)),
			(tWRMPR,       29,24, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd1,        31,30, ATUI_DEC, (ATUI_NODESCR))
		)),
		((LANG_ENG, "reliability RAS"))
	)
)

PPATUI_FUNCIFY(union, DRAMTiming36, atui_nullstruct, 
	(bios->DRAMTiming36, DRAMTiming36,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tWTRTR,     5,0, ATUI_DEC, ((LANG_ENG, "WRITE to WRTR"))),
			(tREFTR,     11,6, ATUI_DEC, ((LANG_ENG, "was named tREFTT. REFab to RDTR/WRTR"))),
			(tTTROW,     17,12, ATUI_DEC, ((LANG_ENG, "??"))),
			(tLDTLD,     23,18, ATUI_DEC, ((LANG_ENG, "JEDEC tLTLTR?"))),
			(tUPDN,      29,24, ATUI_DEC, ((LANG_ENG, "??"))),
			(tREFTR_MSB, 30,30, ATUI_DEC, ((LANG_ENG, "was named tREFTT"))),
			(rsvd0,      31,31, ATUI_DEC, (ATUI_NODESCR))
		)), ((LANG_ENG, "GDDR training"))
	)
)
PPATUI_FUNCIFY(union, TRFCTimingCS01, atui_nullstruct,
	(bios->TRFCTimingCS01, TRFCTimingCS01,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tRFC,  10,0, ATUI_DEC, (ATUI_NODESCR)),
			(rsvd0, 31,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, TRFCTimingCS01_DDR4, atui_nullstruct,
	(bios->TRFCTimingCS01_DDR4, TRFCTimingCS01_DDR4,
		(ATUI_BIN, ATUI_BITFIELD, (
			(tRFC,  10,0, ATUI_DEC, (ATUI_NODESCR)),
			(tRFC2, 21,11, ATUI_DEC, (ATUI_NODESCR)),
			(tRFC4, 31,22, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, ChanPipeDly, atui_nullstruct,
	(bios->ChanPipeDly, ChanPipeDly,
		(ATUI_BIN, ATUI_BITFIELD, (
			(TXCtrlChanDly, 2,0, ATUI_DEC,
				((LANG_ENG, "# of delay stages on DFI control from UMC to PHY"))
			),
			(rsvd0,         3,3, ATUI_DEC, (ATUI_NODESCR)),
			(TXDataChanDly, 6,4, ATUI_DEC,
				((LANG_ENG, "... on DFI write data from UMC to PHY"))
			),
			(rsvd1,         7,7, ATUI_DEC, (ATUI_NODESCR)),
			(RXDataChanDly,10,8, ATUI_DEC,
				((LANG_ENG, "... on DFI read data from PHY to UMC"))
			),
			(rsvd2,        31,11, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_gddr6_bit_byte_remap, atui_nullstruct,
	(bios->dphy_byteremap, dphy_byteremap,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "mmUMC_DPHY_ByteRemap"))
	),
	(bios->dphy_bitremap0, dphy_bitremap0,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "mmUMC_DPHY_BitRemap0"))
	),
	(bios->dphy_bitremap1, dphy_bitremap1,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "mmUMC_DPHY_BitRemap1"))
	),
	(bios->dphy_bitremap2, dphy_bitremap2,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "mmUMC_DPHY_BitRemap2"))
	),
	(bios->aphy_bitremap0, aphy_bitremap0,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "mmUMC_APHY_BitRemap0"))
	),
	(bios->aphy_bitremap1, aphy_bitremap1,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "mmUMC_APHY_BitRemap1"))
	),
	(bios->phy_dram, phy_dram,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "mmUMC_PHY_DRAM"))
	)
)

PPATUI_FUNCIFY(struct, atom_gddr6_dram_data_remap, atui_nullstruct,
	(bios->table_size, table_size,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->phyintf_ck_inverted, phyintf_ck_inverted,
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "UMC_PHY_PHYINTF_CNTL.INV_CK"))
	),
	(NULL, atom_gddr6_bit_byte_remap,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(bios, bit_byte_remap [%02u],
				(ATUI_NAN, ATUI_INLINE, atom_gddr6_bit_byte_remap),
				(ATUI_NODESCR)
			),
			bios->bit_byte_remap, // start
			(sizeof(bios->bit_byte_remap)
			/ sizeof(struct atom_gddr6_bit_byte_remap)) // count 
		)), (ATUI_NODESCR)
	)
)


PPATUI_ENUMER(atom_dgpu_vram_type,
	ATOM_DGPU_VRAM_TYPE_GDDR5,
	ATOM_DGPU_VRAM_TYPE_HBM2,
	ATOM_DGPU_VRAM_TYPE_HBM2E,
	ATOM_DGPU_VRAM_TYPE_GDDR6,
	ATOM_DGPU_VRAM_TYPE_HBM3
)



PPATUI_FUNCIFY(struct, atom_vram_module_v9, atui_nullstruct,
	(bios->memory_size, memory_size,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Total memory size in unit of MB for CONFIG_MEMSIZE zeros"))
	),
	(bios->channel_enable, channel_enable,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "bit vector, each bit indicate specific channel enable or not"))
	),
	(bios->max_mem_clk, max_mem_clk,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "max memory clock of this memory in unit of 10kHz, =0 means it is not defined"))
	),
	(bios->reserved, reserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->mem_voltage, mem_voltage,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mem_voltage"))
	),
	(bios->vram_module_size, vram_module_size,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Size of atom_vram_module_v9"))
	),
	(bios->ext_memory_id, ext_memory_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Current memory module ID"))
	),
	(bios->memory_type, memory_type,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "enum of atom_dgpu_vram_type"))
	),
	(bios->channel_num, channel_num,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of mem. channels supported in this module"))
	),
	(bios->channel_width, channel_width,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT"))
	),
	(bios->density, density,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "_8Mx32, _16Mx32, _16Mx16, _32Mx16"))
	),
	(bios->tunningset_id, tunningset_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "MC phy registers set per."))
	),
	(bios->vender_rev_id, vender_rev_id,
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, "[7:4] Revision, [3:0] Vendor code"))
	),
	(bios->refreshrate, refreshrate,
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, "[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(bios->hbm_ven_rev_id, hbm_ven_rev_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "hbm_ven_rev_id"))
	),
	(bios->vram_rsd2, vram_rsd2,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "reserved"))
	),
	(bios->dram_pnstring, dram_pnstring,
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "part number end with '0'."))
	)
)
PPATUI_FUNCIFY(struct, atom_vram_info_header_v2_3, atui_nullstruct,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->mem_adjust_tbloffset, mem_adjust_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for memory vendor specific UMC adjust setting"))
	),
	(bios->mem_clk_patch_tbloffset, mem_clk_patch_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for memory clock specific UMC setting"))
	),
	(bios->mc_adjust_pertile_tbloffset, mc_adjust_pertile_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for Per Byte Offset Preset Settings"))
	),
	(bios->mc_phyinit_tbloffset, mc_phyinit_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for MC phy init set"))
	),
	(bios->dram_data_remap_tbloffset, dram_data_remap_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "reserved for now"))
	),
	(bios->tmrs_seq_offset, tmrs_seq_offset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of HBM tmrs"))
	),
	(bios->post_ucode_init_offset, post_ucode_init_offset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for MC phy init after MC uCode complete umc init"))
	),
	(bios->vram_rsd2, vram_rsd2,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vram_module_num, vram_module_num,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "indicate number of VRAM module"))
	),
	(bios->umcip_min_ver, umcip_min_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->umcip_max_ver, umcip_max_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_phy_tile_num, mc_phy_tile_num,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "indicate the MCD tile number which use in DramDataRemapTbl and usMcAdjustPerTileTblOffset"))
	)
)


PPATUI_FUNCIFY(struct, atom_vram_info_header_v2_4,
		atomtree_vram_info_header_v2_4,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->mem_adjust_tbloffset, mem_adjust_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for memory vendor specific UMC adjust setting"))
	),
	(bios->mem_clk_patch_tbloffset, mem_clk_patch_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for memory clock specific UMC setting"))
	),
	(bios->mc_adjust_pertile_tbloffset, mc_adjust_pertile_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for Per Byte Offset Preset Settings"))
	),
	(bios->mc_phyinit_tbloffset, mc_phyinit_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for MC phy init set"))
	),
	(bios->dram_data_remap_tbloffset, dram_data_remap_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "reserved for now"))
	),
	(bios->reserved, reserved,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of reserved"))
	),
	(bios->post_ucode_init_offset, post_ucode_init_offset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for MC phy init after MC uCode complete umc init"))
	),
	(bios->vram_rsd2, vram_rsd2,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vram_module_num, vram_module_num,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "indicate number of VRAM module"))
	),
	(bios->umcip_min_ver, umcip_min_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->umcip_max_ver, umcip_max_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_phy_tile_num, mc_phy_tile_num,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "indicate the MCD tile number which use in DramDataRemapTbl and usMcAdjustPerTileTblOffset"))
	)
)


PPATUI_FUNCIFY(struct, atom_vram_module_v10, atomtree_vram_info_header_v2_4,
	(bios->memory_size, memory_size,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Total memory size in unit of MB for CONFIG_MEMSIZE zeros"))
	),
	(bios->channel_enable, channel_enable,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "bit vector, each bit indicate specific channel enable or not"))
	),
	(bios->max_mem_clk, max_mem_clk,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "max memory clock of this memory in unit of 10kHz, =0 means it is not defined"))
	),
	(bios->reserved, reserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->mem_voltage, mem_voltage,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mem_voltage"))
	),
	(bios->vram_module_size, vram_module_size,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Size of atom_vram_module_v9"))
	),
	(bios->ext_memory_id, ext_memory_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Current memory module ID"))
	),
	(bios->memory_type, memory_type,
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		((LANG_ENG, "enum of atom_dgpu_vram_type"))
	),
	(bios->channel_num, channel_num,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of mem. channels supported in this module"))
	),
	(bios->channel_width, channel_width,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT"))
	),
	(bios->density, density,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "_8Mx32, _16Mx32, _16Mx16, _32Mx16"))
	),
	(bios->tunningset_id, tunningset_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "MC phy registers set per"))
	),
	(bios->vender_rev_id, vender_rev_id,
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, "[7:4] Revision, [3:0] Vendor code"))
	),
	(bios->refreshrate, refreshrate,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(bios->vram_flags, vram_flags,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "bit0= bankgroup enable"))
	),
	(bios->vram_rsd2, vram_rsd2,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "reserved"))
	),
	(bios->gddr6_mr10, gddr6_mr10,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr10),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr1, gddr6_mr1,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr1),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr2, gddr6_mr2,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr2),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr7, gddr6_mr7,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr7),
		(ATUI_NODESCR)
	),
	(bios->dram_pnstring, dram_pnstring,
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "part number end with '0'"))
	)
)
PPATUI_FUNCIFY(struct, umc_block_navi1_timings,
		atomtree_vram_info_header_v2_4,

	(bios->block_id,  block_id,
		(ATUI_NODISPLAY, ATUI_INLINE, atom_umc_reg_setting_id_config_access),
		(ATUI_NODESCR)
	),

	(bios->gddr6_mr5.gddr6_mr5, gddr6_mr5,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr5),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr5.reserved, gddr6_mr5_reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gddr6_mr0.gddr6_mr0, gddr6_mr0,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr0),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr0.reserved, gddr6_mr0_reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->UMCCTRL_PMG_CMD_EMRS, UMCCTRL_PMG_CMD_EMRS,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gddr6_mr4.gddr6_mr4, gddr6_mr4,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr4),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr4.reserved, gddr6_mr4_reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gddr6_mr8.gddr6_mr8, gddr6_mr8,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr8),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr8.reserved, gddr6_mr8_reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DRAMTiming1, DRAMTiming1,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming1),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming2, DRAMTiming2,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming2),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming3, DRAMTiming3,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming3),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming4, DRAMTiming4,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming4),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming5, DRAMTiming5,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming5),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming6, DRAMTiming6,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming6),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming7, DRAMTiming7,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming7),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming8, DRAMTiming8,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming8),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming9, DRAMTiming9,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming9),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming10, DRAMTiming10,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming10),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming12, DRAMTiming12,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming12),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming13, DRAMTiming13,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming13),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming14, DRAMTiming14,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming14),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming16, DRAMTiming16,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming16),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming17, DRAMTiming17,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming17),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming20, DRAMTiming20,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming20),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming21, DRAMTiming21,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming21),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming22, DRAMTiming22,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming22),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming23, DRAMTiming23,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming23),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming35, DRAMTiming35,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming35),
		(ATUI_NODESCR)
	),
	(bios->DRAMTiming36, DRAMTiming36,
		(ATUI_NODISPLAY, ATUI_INLINE, DRAMTiming36),
		(ATUI_NODESCR)
	),
	(bios->tRFC, tRFC,
		(ATUI_NODISPLAY, ATUI_INLINE, TRFCTimingCS01),
		(ATUI_NODESCR)
	),
	(bios->ChanPipeDly, ChanPipeDly,
		(ATUI_NODISPLAY, ATUI_INLINE, ChanPipeDly),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_vram_module_v11,
		atomtree_vram_info_header_v2_5,

	(bios->memory_size, memory_size,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Total memory size in unit of MB for CONFIG_MEMSIZE zeros"))
	),
	(bios->channel_enable, channel_enable,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "bit vector, each bit indicate specific channel enable or not"))
	),
	(bios->mem_voltage, mem_voltage,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "mem_voltage"))
	),
	(bios->vram_module_size, vram_module_size,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Size of atom_vram_module_v9"))
	),
	(bios->ext_memory_id, ext_memory_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Current memory module ID"))
	),
	(bios->memory_type, memory_type,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "enum of atom_dgpu_vram_type"))
	),
	(bios->channel_num, channel_num,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of mem. channels supported in this module"))
	),
	(bios->channel_width, channel_width,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT"))
	),
	(bios->density, density,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "_8Mx32, _16Mx32, _16Mx16, _32Mx16"))
	),
	(bios->tunningset_id, tunningset_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "MC phy registers set per."))
	),
	(bios->reserved, reserved,
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "reserved"))
	),
	(bios->vender_rev_id, vender_rev_id,
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, "[7:4] Revision, [3:0] Vendor code"))
	),
	(bios->refreshrate, refreshrate,
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, "[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(bios->vram_flags, vram_flags,
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, "bit0= bankgroup enable"))
	),
	(bios->vram_rsd2, vram_rsd2,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "reserved"))
	),

	(bios->gddr6_mr10, gddr6_mr10,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr10),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr0, gddr6_mr0,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr0),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr1, gddr6_mr1,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr1),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr2, gddr6_mr2,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr2),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr4, gddr6_mr4,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr4),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr7, gddr6_mr7,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr7),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr8, gddr6_mr8,
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr8),
		(ATUI_NODESCR)
	),

	(bios->dram_pnstring, dram_pnstring,
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "part number end with '0'."))
	)
)

PPATUI_FUNCIFY(struct, atom_gddr6_ac_timing_v2_5,
		atomtree_vram_info_header_v2_5,
	(bios->u32umc_id_access, u32umc_id_access,
		(ATUI_NAN, ATUI_INLINE, atom_umc_reg_setting_id_config_access),
		(ATUI_NODESCR)
	),
	(bios->RL, RL,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->WL, WL,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRAS, tRAS,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRC, tRC,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tREFI, tREFI,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRFC, tRFC,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRFCpb, tRFCpb,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tRREFD, tRREFD,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRCDRD, tRCDRD,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRCDWR, tRCDWR,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRP, tRP,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tRRDS, tRRDS,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRRDL, tRRDL,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWR, tWR,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWTRS, tWTRS,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tWTRL, tWTRL,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tFAW, tFAW,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCCDS, tCCDS,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCCDL, tCCDL,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tCRCRL, tCRCRL,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCRCWL, tCRCWL,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCKE, tCKE,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCKSRE, tCKSRE,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tCKSRX, tCKSRX,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRTPS, tRTPS,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRTPL, tRTPL,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tMRD, tMRD,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tMOD, tMOD,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tXS, tXS,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tXHP, tXHP,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tXSMRS, tXSMRS,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tXSH, tXSH,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tPD, tPD,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tXP, tXP,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCPDED, tCPDED,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tACTPDE, tACTPDE,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tPREPDE, tPREPDE,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tREFPDE, tREFPDE,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tMRSPDEN, tMRSPDEN,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRDSRE, tRDSRE,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tWRSRE, tWRSRE,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tPPD, tPPD,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCCDMW, tCCDMW,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWTRTR, tWTRTR,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tLTLTR, tLTLTR,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tREFTR, tREFTR,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->VNDR, VNDR,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, reserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_vram_info_header_v2_5,
		atomtree_vram_info_header_v2_5,

	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->mem_adjust_tbloffset, mem_adjust_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for memory vendor specific UMC adjust settings"))
	),
	(bios->gddr6_ac_timing_offset, gddr6_ac_timing_offset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_gddr6_ac_timing_v2_5 structure for memory clock specific UMC settings"))
	),
	(bios->mc_adjust_pertile_tbloffset, mc_adjust_pertile_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for Per Byte Offset Preset Settings"))
	),
	(bios->mc_phyinit_tbloffset, mc_phyinit_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for MC phy init set"))
	),
	(bios->dram_data_remap_tbloffset, dram_data_remap_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_gddr6_dram_data_remap array to indicate DRAM data lane to GPU mapping"))
	),
	(bios->reserved, reserved,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of reserved"))
	),
	(bios->post_ucode_init_offset, post_ucode_init_offset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for MC phy init after MC uCode complete umc init"))
	),
	(bios->strobe_mode_patch_tbloffset, strobe_mode_patch_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of atom_umc_init_reg_block structure for Strobe Mode memory clock specific UMC settings"))
	),
	(bios->vram_module_num, vram_module_num,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "indicate number of VRAM module"))
	),
	(bios->umcip_min_ver, umcip_min_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->umcip_max_ver, umcip_max_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_phy_tile_num, mc_phy_tile_num,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "indicate the MCD tile number which use in DramDataRemapTbl and usMcAdjustPerTileTblOffset"))
	)
)


PPATUI_FUNCIFY(struct, atom_vram_info_header_v2_6,
		atomtree_vram_info_header_v2_6,
	(bios->table_header, table_header,
		(ATUI_NODISPLAY, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->mem_adjust_tbloffset, mem_adjust_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem_clk_patch_tbloffset, mem_clk_patch_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_adjust_pertile_tbloffset, mc_adjust_pertile_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_phyinit_tbloffset, mc_phyinit_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dram_data_remap_tbloffset, dram_data_remap_tbloffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tmrs_seq_offset, tmrs_seq_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->post_ucode_init_offset, post_ucode_init_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vram_rsd2, vram_rsd2,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vram_module_num, vram_module_num,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->umcip_min_ver, umcip_min_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->umcip_max_ver, umcip_max_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_phy_tile_num, mc_phy_tile_num,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_vram_module_v3_0, 
		atomtree_vram_info_header_v3_0,
	(bios->density, density,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tunningset_id, tunningset_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ext_memory_id, ext_memory_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dram_vendor_id, dram_vendor_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dram_info_offset, dram_info_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem_tuning_offset, mem_tuning_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tmrs_seq_offset, tmrs_seq_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved1, reserved1,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dram_size_per_ch, dram_size_per_ch,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, reserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->dram_pnstring, dram_pnstring,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_vram_info_header_v3_0,
		atomtree_vram_info_header_v3_0,
	(bios->table_header, table_header,
		(ATUI_NODISPLAY, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->mem_tuning_table_offset, mem_tuning_table_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dram_info_table_offset, dram_info_table_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tmrs_table_offset, tmrs_table_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_init_table_offset, mc_init_table_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dram_data_remap_table_offset, dram_data_remap_table_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->umc_emuinit_table_offset, umc_emuinit_table_offset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved_sub_table_offset, reserved_sub_table_offset,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->vram_module_num, vram_module_num,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->umcip_min_ver, umcip_min_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->umcip_max_ver, umcip_max_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_phy_tile_num, mc_phy_tile_num,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->memory_type, memory_type,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->channel_num, channel_num,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->channel_width, channel_width,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved1, reserved1,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->channel_enable, channel_enable,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->channel1_enable, channel1_enable,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->feature_enable, feature_enable,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->feature1_enable, feature1_enable,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->hardcode_mem_size, hardcode_mem_size,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved4, reserved4,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, atom_umc_register_addr_info_access,
		atomtree_umc_init_reg_block,
	(NULL, umc_reg_list,
		(ATUI_NODISPLAY, ATUI_DYNARRAY, (
			// Leaf pattern:
			(bios->u32umc_reg_addr, u32umc_reg_addr [%02u],
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
	(bios->umc_reg_num, umc_reg_num,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, atom_umc_reg_setting_id_config_access,
		atomtree_umc_init_reg_block,

	(bios->u32umc_id_access,  u32umc_id_access,
		(ATUI_BIN, ATUI_BITFIELD, (
			(memclockrange, 23, 0, ATUI_DEC, (ATUI_NODESCR)),
			(mem_blk_id,    31,24, ATUI_DEC, (ATUI_NODESCR))
		)),
		(ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_umc_reg_setting_data_block,
		atomtree_umc_init_reg_block,
	(bios->block_id, UMC block ID,
		(ATUI_NODISPLAY, ATUI_INLINE, atom_umc_reg_setting_id_config_access),
		(ATUI_NODESCR)
	),
	(NULL, u32umc_reg_data,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(bios->u32umc_reg_data, u32umc_reg_data [%02u],
				(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			bios->u32umc_reg_data, atomtree->umc_reg_num //start, count
		)),
		(ATUI_NODESCR)
	)
)
