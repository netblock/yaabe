/*
AtomTree iterable interface for UIs.

See ppatui.h for the metaprogramming and atui.h for general API.

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
    s = re.sub("(union|struct)\s+([a-zA-Z0-9_]+)\s+([a-zA-Z0-9_]+)(\[[0-9]+\])?;", "(bios->\g<3>, \g<3>,\n\t\t(ATUI_NAN, ATUI_INLINE, \g<2>),\n\t\t(ATUI_NODESCR)\n\t),", s)
    s = re.sub("(u?int[0-9]+_t|char8_t)\s+([a-zA-Z0-9_]+)(\s+)?;", "(bios->\g<2>, \g<2>,\n\t\t(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)\n\t),", s)
    s = re.sub("(u?int[0-9]+_t|char8_t)\s+([a-zA-Z0-9_]+)\s?+\[[0-9]+\]\s?+;", "(bios->\g<2>, \g<2>,\n\t\t(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)\n\t),", s)
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
    s = re.sub("[ \t]*uint[0-9]+_t[ \t]+([A-Za-z0-9_]+)[ \t]*;\s+struct { uint[0-9]+_t\n", "\t(bios->\g<1>, \g<1>,\n\t\t(ATUI_BIN, ATUI_BITFIELD, (\n", s)
    s = re.sub("([a-zA-Z0-9_]+)(\s*):([0-9]+)(\s*)-(\s*)([0-9]+)(\s*)\+1[,;][ \t]*", "\t(\g<1>,\g<2>\g<3>\g<4>,\g<5>\g<6>, ATUI_DEC,", s)
    s = re.sub("ATUI_DEC,(\s*)//(\s*)(.*)", "ATUI_DEC, ((LANG_ENG, \"\g<3>\"))),", s) 
    s = re.sub("ATUI_DEC,\n", "ATUI_DEC, (ATUI_NODESCR)),\n", s)
    s = re.sub(",(\n\t\t\)\), )", "\g<1>", s) 
    print(s)
*/

/* for atomfirmware.h */

#include "atomtree.h"
#include "atui.h"

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





PPATUI_FUNCIFY(struct, atom_smc_dpm_info_v4_1, atomtree_smc_dpm_info,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->liquid1_i2c_address, liquid1_i2c_address,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->liquid2_i2c_address, liquid2_i2c_address,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr_i2c_address, vr_i2c_address,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->plx_i2c_address, plx_i2c_address,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->liquid_i2c_linescl, liquid_i2c_linescl,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->liquid_i2c_linesda, liquid_i2c_linesda,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr_i2c_linescl, vr_i2c_linescl,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr_i2c_linesda, vr_i2c_linesda,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->plx_i2c_linescl, plx_i2c_linescl,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->plx_i2c_linesda, plx_i2c_linesda,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vrsensorpresent, vrsensorpresent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->liquidsensorpresent, liquidsensorpresent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->maxvoltagestepgfx, maxvoltagestepgfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->maxvoltagestepsoc, maxvoltagestepsoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->vddgfxvrmapping, vddgfxvrmapping,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddsocvrmapping, vddsocvrmapping,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddmem0vrmapping, vddmem0vrmapping,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddmem1vrmapping, vddmem1vrmapping,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->gfxulvphasesheddingmask, gfxulvphasesheddingmask,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->soculvphasesheddingmask, soculvphasesheddingmask,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding8_v, padding8_v,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->gfxmaxcurrent, gfxmaxcurrent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxoffset, gfxoffset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrygfx, padding_telemetrygfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->socmaxcurrent, socmaxcurrent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->socoffset, socoffset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrysoc, padding_telemetrysoc,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->mem0maxcurrent, mem0maxcurrent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem0offset, mem0offset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrymem0, padding_telemetrymem0,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->mem1maxcurrent, mem1maxcurrent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem1offset, mem1offset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrymem1, padding_telemetrymem1,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->acdcgpio, acdcgpio,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->acdcpolarity, acdcpolarity,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr0hotgpio, vr0hotgpio,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr0hotpolarity, vr0hotpolarity,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->vr1hotgpio, vr1hotgpio,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr1hotpolarity, vr1hotpolarity,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding1, padding1,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding2, padding2,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->ledpin0, ledpin0,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ledpin1, ledpin1,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ledpin2, ledpin2,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding8_4, padding8_4,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->pllgfxclkspreadenabled, pllgfxclkspreadenabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pllgfxclkspreadpercent, pllgfxclkspreadpercent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pllgfxclkspreadfreq, pllgfxclkspreadfreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->uclkspreadenabled, uclkspreadenabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->uclkspreadpercent, uclkspreadpercent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->uclkspreadfreq, uclkspreadfreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->socclkspreadenabled, socclkspreadenabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->socclkspreadpercent, socclkspreadpercent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->socclkspreadfreq, socclkspreadfreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->acggfxclkspreadenabled, acggfxclkspreadenabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->acggfxclkspreadpercent, acggfxclkspreadpercent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->acggfxclkspreadfreq, acggfxclkspreadfreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Vr2_I2C_address, Vr2_I2C_address,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_vr2, padding_vr2,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->boardreserved, boardreserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_smc_dpm_info_v4_3, atomtree_smc_dpm_info,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->liquid1_i2c_address, liquid1_i2c_address,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->liquid2_i2c_address, liquid2_i2c_address,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr_i2c_address, vr_i2c_address,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->plx_i2c_address, plx_i2c_address,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->liquid_i2c_linescl, liquid_i2c_linescl,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->liquid_i2c_linesda, liquid_i2c_linesda,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr_i2c_linescl, vr_i2c_linescl,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr_i2c_linesda, vr_i2c_linesda,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->plx_i2c_linescl, plx_i2c_linescl,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->plx_i2c_linesda, plx_i2c_linesda,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vrsensorpresent, vrsensorpresent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->liquidsensorpresent, liquidsensorpresent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->maxvoltagestepgfx, maxvoltagestepgfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->maxvoltagestepsoc, maxvoltagestepsoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->vddgfxvrmapping, vddgfxvrmapping,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddsocvrmapping, vddsocvrmapping,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddmem0vrmapping, vddmem0vrmapping,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddmem1vrmapping, vddmem1vrmapping,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->gfxulvphasesheddingmask, gfxulvphasesheddingmask,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->soculvphasesheddingmask, soculvphasesheddingmask,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->externalsensorpresent, externalsensorpresent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding8_v, padding8_v,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->gfxmaxcurrent, gfxmaxcurrent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxoffset, gfxoffset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrygfx, padding_telemetrygfx,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->socmaxcurrent, socmaxcurrent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->socoffset, socoffset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrysoc, padding_telemetrysoc,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->mem0maxcurrent, mem0maxcurrent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem0offset, mem0offset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrymem0, padding_telemetrymem0,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->mem1maxcurrent, mem1maxcurrent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem1offset, mem1offset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrymem1, padding_telemetrymem1,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->acdcgpio, acdcgpio,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->acdcpolarity, acdcpolarity,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr0hotgpio, vr0hotgpio,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr0hotpolarity, vr0hotpolarity,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->vr1hotgpio, vr1hotgpio,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr1hotpolarity, vr1hotpolarity,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding1, padding1,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding2, padding2,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->ledpin0, ledpin0,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ledpin1, ledpin1,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ledpin2, ledpin2,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding8_4, padding8_4,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->pllgfxclkspreadenabled, pllgfxclkspreadenabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pllgfxclkspreadpercent, pllgfxclkspreadpercent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pllgfxclkspreadfreq, pllgfxclkspreadfreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->uclkspreadenabled, uclkspreadenabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->uclkspreadpercent, uclkspreadpercent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->uclkspreadfreq, uclkspreadfreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->fclkspreadenabled, fclkspreadenabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fclkspreadpercent, fclkspreadpercent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fclkspreadfreq, fclkspreadfreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->fllgfxclkspreadenabled, fllgfxclkspreadenabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fllgfxclkspreadpercent, fllgfxclkspreadpercent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fllgfxclkspreadfreq, fllgfxclkspreadfreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->boardreserved, boardreserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
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

PPATUI_FUNCIFY(struct, smudpm_i2ccontrollerconfig_t, atomtree_smc_dpm_info,
	(bios->enabled, enabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->slaveaddress, slaveaddress,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->controllerport, controllerport,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->controllername, controllername,
		(ATUI_DEC, ATUI_ENUM, smudpm_v4_5_i2ccontrollername_e), (ATUI_NODESCR)
	),
	(bios->thermalthrottler, thermalthrottler,
		(ATUI_DEC, ATUI_ENUM, smudpm_v4_5_i2ccontrollerthrottler_e),
		(ATUI_NODESCR)
	),
	(bios->i2cprotocol, i2cprotocol,
		(ATUI_DEC, ATUI_ENUM, smudpm_v4_5_i2ccontrollerprotocol_e),
		(ATUI_NODESCR)
	),
	(bios->i2cspeed, i2cspeed,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_smc_dpm_info_v4_4, atomtree_smc_dpm_info,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->i2c_padding, i2c_padding,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->maxvoltagestepgfx, maxvoltagestepgfx,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->maxvoltagestepsoc, maxvoltagestepsoc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->vddgfxvrmapping, vddgfxvrmapping,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddsocvrmapping, vddsocvrmapping,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddmem0vrmapping, vddmem0vrmapping,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddmem1vrmapping, vddmem1vrmapping,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->gfxulvphasesheddingmask, gfxulvphasesheddingmask,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->soculvphasesheddingmask, soculvphasesheddingmask,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->externalsensorpresent, externalsensorpresent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding8_v, padding8_v,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->gfxmaxcurrent, gfxmaxcurrent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxoffset, gfxoffset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrygfx, padding_telemetrygfx,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->socmaxcurrent, socmaxcurrent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->socoffset, socoffset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrysoc, padding_telemetrysoc,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->mem0maxcurrent, mem0maxcurrent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem0offset, mem0offset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrymem0, padding_telemetrymem0,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->mem1maxcurrent, mem1maxcurrent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem1offset, mem1offset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrymem1, padding_telemetrymem1,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->acdcgpio, acdcgpio,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->acdcpolarity, acdcpolarity,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr0hotgpio, vr0hotgpio,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr0hotpolarity, vr0hotpolarity,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->vr1hotgpio, vr1hotgpio,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr1hotpolarity, vr1hotpolarity,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding1, padding1,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding2, padding2,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->ledpin0, ledpin0,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ledpin1, ledpin1,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ledpin2, ledpin2,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding8_4, padding8_4,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->pllgfxclkspreadenabled, pllgfxclkspreadenabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pllgfxclkspreadpercent, pllgfxclkspreadpercent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pllgfxclkspreadfreq, pllgfxclkspreadfreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->uclkspreadenabled, uclkspreadenabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->uclkspreadpercent, uclkspreadpercent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->uclkspreadfreq, uclkspreadfreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->fclkspreadenabled, fclkspreadenabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fclkspreadpercent, fclkspreadpercent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fclkspreadfreq, fclkspreadfreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->fllgfxclkspreadenabled, fllgfxclkspreadenabled,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fllgfxclkspreadpercent, fllgfxclkspreadpercent,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fllgfxclkspreadfreq, fllgfxclkspreadfreq,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->i2ccontrollers, i2ccontrollers,
		(ATUI_NAN, ATUI_INLINE, smudpm_i2ccontrollerconfig_t),
		(ATUI_NODESCR)
	),


	(bios->boardreserved, boardreserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
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
		(ATUI_NODESCR)
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





PPATUI_FUNCIFY(union, atom_dtd_format_modemiscinfo, atomtree_lcd_info,
	(bios->miscinfo, miscinfo,
		(ATUI_BIN, ATUI_BITFIELD, (
			(reserved0,             0,0, ATUI_DEC, (ATUI_NODESCR)),
			(ATOM_HSYNC_POLARITY,   1,1, ATUI_DEC, (ATUI_NODESCR)),
			(ATOM_VSYNC_POLARITY,   2,2, ATUI_DEC, (ATUI_NODESCR)),
			(reserved1,             3,3, ATUI_DEC, (ATUI_NODESCR)),
			(ATOM_H_REPLICATIONBY2, 4,4, ATUI_DEC, (ATUI_NODESCR)),
			(ATOM_V_REPLICATIONBY2, 5,5, ATUI_DEC, (ATUI_NODESCR)),
			(ATOM_COMPOSITESYNC,    6,6, ATUI_DEC, (ATUI_NODESCR)),
			(ATOM_INTERLACE,        7,7, ATUI_DEC, (ATUI_NODESCR)),
			(reserved2,            15,8, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_dtd_format, atomtree_lcd_info,
	(bios->pixclk, pixclk,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->h_active, h_active,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->h_blanking_time, h_blanking_time,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->v_active, v_active,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->v_blanking_time, v_blanking_time,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->h_sync_offset, h_sync_offset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->h_sync_width, h_sync_width,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->v_sync_offset, v_sync_offset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->v_syncwidth, v_syncwidth,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved0, reserved0,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->h_border, h_border,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->v_border, v_border,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->miscinfo, miscinfo,
		(ATUI_NODISPLAY, ATUI_INLINE, atom_dtd_format_modemiscinfo),
		(ATUI_NODESCR)
	),
	(bios->atom_mode_id, atom_mode_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->refreshrate, refreshrate,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_ENUMER(atom_lcd_info_panel_misc,
	ATOM_PANEL_MISC_FPDI
)
PPATUI_ENUMER(atom_lcd_info_dptolvds_rx_id,
	eDP_TO_LVDS_RX_DISABLE,
	eDP_TO_LVDS_COMMON_ID,
	eDP_TO_LVDS_REALTEK_ID
)
PPATUI_FUNCIFY(struct, atom_lcd_info_v2_1, atomtree_lcd_info,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->backlight_pwm, backlight_pwm,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->special_handle_cap, special_handle_cap,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->panel_misc, panel_misc,
		(ATUI_DEC, ATUI_ENUM, atom_lcd_info_panel_misc), (ATUI_NODESCR)
	),
	(bios->lvds_max_slink_pclk, lvds_max_slink_pclk,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->lvds_ss_percentage, lvds_ss_percentage,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->lvds_ss_rate_10hz, lvds_ss_rate_10hz,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pwr_on_digon_to_de, pwr_on_digon_to_de,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "all pwr sequence numbers below are in uint of 4ms"))
	),
	(bios->pwr_on_de_to_vary_bl, pwr_on_de_to_vary_bl,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pwr_down_vary_bloff_to_de, pwr_down_vary_bloff_to_de,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pwr_down_de_to_digoff, pwr_down_de_to_digoff,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pwr_off_delay, pwr_off_delay,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pwr_on_vary_bl_to_blon, pwr_on_vary_bl_to_blon,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pwr_down_bloff_to_vary_bloff, pwr_down_bloff_to_vary_bloff,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->panel_bpc, panel_bpc,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dpcd_edp_config_cap, dpcd_edp_config_cap,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dpcd_max_link_rate, dpcd_max_link_rate,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dpcd_max_lane_count, dpcd_max_lane_count,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dpcd_max_downspread, dpcd_max_downspread,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->min_allowed_bl_level, min_allowed_bl_level,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_allowed_bl_level, max_allowed_bl_level,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_bl_level, bootup_bl_level,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dplvdsrxid, dplvdsrxid,
		(ATUI_DEC, ATUI_ENUM, atom_lcd_info_dptolvds_rx_id),
		((LANG_ENG, "eDP->LVDS translator chip. non-common like Realtek might require AMD SW init"))
	),
	(bios->reserved1, reserved1,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)





PPATUI_FUNCIFY(struct, vram_usagebyfirmware_v2_1,
		atomtree_vram_usagebyfirmware,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->start_address_in_kb, start_address_in_kb,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->used_by_firmware_in_kb, used_by_firmware_in_kb,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->used_by_driver_in_kb, used_by_driver_in_kb,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, vram_usagebyfirmware_v2_2,
		atomtree_vram_usagebyfirmware,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->fw_region_start_address_in_kb, fw_region_start_address_in_kb,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->used_by_firmware_in_kb, used_by_firmware_in_kb,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->driver_region0_start_address_in_kb, driver_region0_start_address_in_kb,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->used_by_driver_region0_in_kb, used_by_driver_region0_in_kb,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved32, reserved32,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)




//TODO ATUI_FANCY for bitfields
PPATUI_FUNCIFY(union, atom_gpioi2c_pin_id, atomtree_gpio_pin_lut,
	(bios->gpio_id, gpio_id,
		(ATUI_BIN, ATUI_BITFIELD, (
			(I2C_HW_LANE_MUX,       3,0, ATUI_DEC, (ATUI_NODESCR)),
			(I2C_HW_ENGINE_ID_MASK, 6,4, ATUI_DEC, (ATUI_NODESCR)),
			(HW_CAP,                7,7, ATUI_DEC, ((LANG_ENG, "only when the I2C_HW_CAP is set, the pin ID is assigned to an I2C pin pair, otherwise, it's an generic GPIO pin"))),
			(GPIO_PINID, 6,0, ATUI_DEC, ((LANG_ENG, "enum of atom_gpio_pin_assignment_gpio_id")))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_gpio_pin_assignment_v2_1, atomtree_gpio_pin_lut,
	(bios->data_a_reg_index, data_a_reg_index,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpio_bitshift, gpio_bitshift,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpio_mask_bitshift, gpio_mask_bitshift,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpio_id, gpio_id,
		(ATUI_NODISPLAY, ATUI_INLINE, atom_gpioi2c_pin_id),
		(ATUI_NODESCR)
	),
	(bios->reserved, reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)




PPATUI_FUNCIFY(struct, atom_gfx_info_v2_2, atomtree_gfx_info,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->gfxip_min_ver, gfxip_min_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxip_max_ver, gfxip_max_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_shader_engines, max_shader_engines,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_tile_pipes, max_tile_pipes,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_cu_per_sh, max_cu_per_sh,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_sh_per_se, max_sh_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_backends_per_se, max_backends_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_texture_channel_caches, max_texture_channel_caches,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr, regaddr_cp_dma_src_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr_hi, regaddr_cp_dma_src_addr_hi,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr, regaddr_cp_dma_dst_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr_hi, regaddr_cp_dma_dst_addr_hi,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_command, regaddr_cp_dma_command,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_status, regaddr_cp_status,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_rlc_gpu_clock_32, regaddr_rlc_gpu_clock_32,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->rlc_gpu_timer_refclk, rlc_gpu_timer_refclk,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_gfx_info_v2_3, atomtree_gfx_info,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->gfxip_min_ver, gfxip_min_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxip_max_ver, gfxip_max_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_shader_engines, max_shader_engines,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_tile_pipes, max_tile_pipes,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_cu_per_sh, max_cu_per_sh,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_sh_per_se, max_sh_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_backends_per_se, max_backends_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_texture_channel_caches, max_texture_channel_caches,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr, regaddr_cp_dma_src_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr_hi, regaddr_cp_dma_src_addr_hi,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr, regaddr_cp_dma_dst_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr_hi, regaddr_cp_dma_dst_addr_hi,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_command, regaddr_cp_dma_command,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_status, regaddr_cp_status,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_rlc_gpu_clock_32, regaddr_rlc_gpu_clock_32,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->rlc_gpu_timer_refclk, rlc_gpu_timer_refclk,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_cu_per_sh, active_cu_per_sh,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_rb_per_se, active_rb_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gcgoldenoffset, gcgoldenoffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->rm21_sram_vmin_value, rm21_sram_vmin_value,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_gfx_info_v2_4, atomtree_gfx_info,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->gfxip_min_ver, gfxip_min_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxip_max_ver, gfxip_max_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_shader_engines, max_shader_engines,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_cu_per_sh, max_cu_per_sh,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_sh_per_se, max_sh_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_backends_per_se, max_backends_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_texture_channel_caches, max_texture_channel_caches,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr, regaddr_cp_dma_src_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr_hi, regaddr_cp_dma_src_addr_hi,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr, regaddr_cp_dma_dst_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr_hi, regaddr_cp_dma_dst_addr_hi,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_command, regaddr_cp_dma_command,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_status, regaddr_cp_status,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_rlc_gpu_clock_32, regaddr_rlc_gpu_clock_32,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->rlc_gpu_timer_refclk, rlc_gpu_timer_refclk,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_cu_per_sh, active_cu_per_sh,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_rb_per_se, active_rb_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gcgoldenoffset, gcgoldenoffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_num_gprs, gc_num_gprs,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_gsprim_buff_depth, gc_gsprim_buff_depth,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_parameter_cache_depth, gc_parameter_cache_depth,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_wave_size, gc_wave_size,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_max_waves_per_simd, gc_max_waves_per_simd,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_lds_size, gc_lds_size,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_num_max_gs_thds, gc_num_max_gs_thds,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_gs_table_depth, gc_gs_table_depth,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_double_offchip_lds_buffer, gc_double_offchip_lds_buffer,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_max_scratch_slots_per_cu, gc_max_scratch_slots_per_cu,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sram_rm_fuses_val, sram_rm_fuses_val,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sram_custom_rm_fuses_val, sram_custom_rm_fuses_val,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_gfx_info_v2_5, atomtree_gfx_info,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->gfxip_min_ver, gfxip_min_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxip_max_ver, gfxip_max_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_shader_engines, max_shader_engines,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_cu_per_sh, max_cu_per_sh,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_sh_per_se, max_sh_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_backends_per_se, max_backends_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_texture_channel_caches, max_texture_channel_caches,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr, regaddr_cp_dma_src_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr_hi, regaddr_cp_dma_src_addr_hi,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr, regaddr_cp_dma_dst_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr_hi, regaddr_cp_dma_dst_addr_hi,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_command, regaddr_cp_dma_command,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_status, regaddr_cp_status,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_rlc_gpu_clock_32, regaddr_rlc_gpu_clock_32,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->rlc_gpu_timer_refclk, rlc_gpu_timer_refclk,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_cu_per_sh, active_cu_per_sh,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_rb_per_se, active_rb_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gcgoldenoffset, gcgoldenoffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_num_gprs, gc_num_gprs,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_gsprim_buff_depth, gc_gsprim_buff_depth,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_parameter_cache_depth, gc_parameter_cache_depth,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_wave_size, gc_wave_size,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_max_waves_per_simd, gc_max_waves_per_simd,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_lds_size, gc_lds_size,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_num_max_gs_thds, gc_num_max_gs_thds,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_gs_table_depth, gc_gs_table_depth,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_double_offchip_lds_buffer, gc_double_offchip_lds_buffer,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_max_scratch_slots_per_cu, gc_max_scratch_slots_per_cu,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sram_rm_fuses_val, sram_rm_fuses_val,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sram_custom_rm_fuses_val, sram_custom_rm_fuses_val,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cut_cu, cut_cu,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_cu_total, active_cu_total,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cu_reserved, cu_reserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->gc_config, gc_config,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->inactive_cu_per_se, inactive_cu_per_se,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_gfx_info_v2_7, atomtree_gfx_info,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->gfxip_min_ver, gfxip_min_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxip_max_ver, gfxip_max_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_shader_engines, max_shader_engines,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, reserved,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_cu_per_sh, max_cu_per_sh,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_sh_per_se, max_sh_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_backends_per_se, max_backends_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_texture_channel_caches, max_texture_channel_caches,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr, regaddr_cp_dma_src_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr_hi, regaddr_cp_dma_src_addr_hi,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr, regaddr_cp_dma_dst_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr_hi, regaddr_cp_dma_dst_addr_hi,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_command, regaddr_cp_dma_command,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_status, regaddr_cp_status,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_rlc_gpu_clock_32, regaddr_rlc_gpu_clock_32,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->rlc_gpu_timer_refclk, rlc_gpu_timer_refclk,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_cu_per_sh, active_cu_per_sh,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_rb_per_se, active_rb_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gcgoldenoffset, gcgoldenoffset,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_num_gprs, gc_num_gprs,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_gsprim_buff_depth, gc_gsprim_buff_depth,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_parameter_cache_depth, gc_parameter_cache_depth,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_wave_size, gc_wave_size,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_max_waves_per_simd, gc_max_waves_per_simd,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_lds_size, gc_lds_size,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_num_max_gs_thds, gc_num_max_gs_thds,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_gs_table_depth, gc_gs_table_depth,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_double_offchip_lds_buffer, gc_double_offchip_lds_buffer,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_max_scratch_slots_per_cu, gc_max_scratch_slots_per_cu,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sram_rm_fuses_val, sram_rm_fuses_val,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sram_custom_rm_fuses_val, sram_custom_rm_fuses_val,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cut_cu, cut_cu,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_cu_total, active_cu_total,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cu_reserved, cu_reserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->gc_config, gc_config,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->inactive_cu_per_se, inactive_cu_per_se,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->reserved2, reserved2,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(struct, atom_gfx_info_v3_0, atomtree_gfx_info,
	(bios->table_header, table_header,
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->gfxip_min_ver, gfxip_min_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxip_max_ver, gfxip_max_ver,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_shader_engines, max_shader_engines,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_tile_pipes, max_tile_pipes,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_cu_per_sh, max_cu_per_sh,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_sh_per_se, max_sh_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_backends_per_se, max_backends_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_texture_channel_caches, max_texture_channel_caches,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_lsdma_queue0_rb_rptr, regaddr_lsdma_queue0_rb_rptr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_lsdma_queue0_rb_rptr_hi, regaddr_lsdma_queue0_rb_rptr_hi,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_lsdma_queue0_rb_wptr, regaddr_lsdma_queue0_rb_wptr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_lsdma_queue0_rb_wptr_hi, regaddr_lsdma_queue0_rb_wptr_hi,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_lsdma_command, regaddr_lsdma_command,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_lsdma_status, regaddr_lsdma_status,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_golden_tsc_count_lower, regaddr_golden_tsc_count_lower,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->golden_tsc_count_lower_refclk, golden_tsc_count_lower_refclk,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_wgp_per_se, active_wgp_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_rb_per_se, active_rb_per_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_se, active_se,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved1, reserved1,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sram_rm_fuses_val, sram_rm_fuses_val,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sram_custom_rm_fuses_val, sram_custom_rm_fuses_val,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->inactive_sa_mask, inactive_sa_mask,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_config, gc_config,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->inactive_wgp, inactive_wgp,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->inactive_rb, inactive_rb,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->gdfll_as_wait_ctrl_val, gdfll_as_wait_ctrl_val,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gdfll_as_step_ctrl_val, gdfll_as_step_ctrl_val,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, reserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
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
			(ATUI_NULL, bit_byte_remap [%02u],
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
		(ATUI_NAN, ATUI_STRING),
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
		(ATUI_NODISPLAY, ATUI_INLINE, atom_umc_reg_setting_id_config_access),
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
		(ATUI_NAN, ATUI_STRING), (ATUI_NODESCR)
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
			atomtree->umc_reg_list, *(atomtree->umc_number_of_registers)
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
			bios->u32umc_reg_data, *(atomtree->umc_reg_num) //start, count
		)),
		(ATUI_NODESCR)
	)
)





PPATUI_ENUMER(atom_voltage_type,
	VOLTAGE_TYPE_VDDC,
	VOLTAGE_TYPE_MVDDC,
	VOLTAGE_TYPE_MVDDQ,
	VOLTAGE_TYPE_VDDCI,
	VOLTAGE_TYPE_VDDGFX,
	VOLTAGE_TYPE_PCC,
	VOLTAGE_TYPE_MVPP,
	VOLTAGE_TYPE_LEDDPM,
	VOLTAGE_TYPE_PCC_MVDD,
	VOLTAGE_TYPE_PCIE_VDDC,
	VOLTAGE_TYPE_PCIE_VDDR,
	VOLTAGE_TYPE_GENERIC_I2C_1,
	VOLTAGE_TYPE_GENERIC_I2C_2,
	VOLTAGE_TYPE_GENERIC_I2C_3,
	VOLTAGE_TYPE_GENERIC_I2C_4,
	VOLTAGE_TYPE_GENERIC_I2C_5,
	VOLTAGE_TYPE_GENERIC_I2C_6,
	VOLTAGE_TYPE_GENERIC_I2C_7,
	VOLTAGE_TYPE_GENERIC_I2C_8,
	VOLTAGE_TYPE_GENERIC_I2C_9,
	VOLTAGE_TYPE_GENERIC_I2C_10
)
PPATUI_ENUMER(atom_voltage_object_mode,
    VOLTAGE_OBJ_GPIO_LUT,
    VOLTAGE_OBJ_VR_I2C_INIT_SEQ,
    VOLTAGE_OBJ_PHASE_LUT,
    VOLTAGE_OBJ_SVID2,
    VOLTAGE_OBJ_EVV,
    VOLTAGE_OBJ_MERGED_POWER
)
PPATUI_FUNCIFY(struct, atom_voltage_object_header_v4, atui_nullstruct,
	(bios->voltage_type, voltage_type,
		(ATUI_DEC, ATUI_ENUM, atom_voltage_type), (ATUI_NODESCR)
	),
	(bios->voltage_mode, voltage_mode,
		(ATUI_DEC, ATUI_ENUM, atom_voltage_object_mode), (ATUI_NODESCR)
	),
	(bios->object_size, object_size,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_voltage_gpio_map_lut, atomtree_voltage_object_v4,
	(bios->voltage_gpio_reg_val, voltage_gpio_reg_val,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "The Voltage ID which is used to program GPIO register"))
	),
	(bios->voltage_level_mv, voltage_level_mv,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "The corresponding Voltage Value, in mV"))
	)
)
PPATUI_FUNCIFY(struct, atom_gpio_voltage_object_v4, atomtree_voltage_object_v4,
	(bios->header, header,
		(ATUI_NAN, ATUI_INLINE, atom_voltage_object_header_v4), (ATUI_NODESCR)
	),
	(bios->gpio_control_id, gpio_control_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "default is 0 which indicate control through CG VID mode"))
	),
	(bios->gpio_entry_num, gpio_entry_num,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "indiate the entry numbers of Votlage/Gpio value Look up table"))
	),
	(bios->phase_delay_us, phase_delay_us,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "phase delay in unit of micro second"))
	),
	(bios->reserved, reserved,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpio_mask_val, gpio_mask_val,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "GPIO Mask value"))
	),
	(bios->voltage_gpio_lut, voltage_gpio_lut,
		(ATUI_NAN, ATUI_INLINE, atom_voltage_gpio_map_lut),
		(ATUI_NODESCR)
	)
	(NULL, voltage_gpio_lut,
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, voltage_gpio_lut [%u],
				(ATUI_NODISPLAY, ATUI_INLINE, atom_voltage_gpio_map_lut),
				(ATUI_NODESCR)
			),
			bios->voltage_gpio_lut, atomtree->lut_entries //start, count
		)),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct,  atom_i2c_data_entry, atomtree_voltage_object_v4,
	(bios->i2c_reg_index, i2c_reg_index,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "i2c register address, can be up to 16bit"))
	),
	(bios->i2c_reg_data, i2c_reg_data,
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "i2c register data, can be up to 16bit"))
	)
)
PPATUI_FUNCIFY(struct, atom_i2c_voltage_object_v4, atomtree_voltage_object_v4,
	(bios->header, header,
		(ATUI_NAN, ATUI_INLINE, atom_voltage_object_header_v4), (ATUI_NODESCR)
	),
	(bios->regulator_id, regulator_id,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Indicate Voltage Regulator Id"))
	),
	(bios->i2c_id, i2c_id,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->i2c_slave_addr, i2c_slave_addr,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->i2c_control_offset, i2c_control_offset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->i2c_flag, i2c_flag,
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, "Bit0: 0 - One byte data; 1 - Two byte data"))
	),
	(bios->i2c_speed, i2c_speed,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "=0, use default i2c speed, otherwise use it in unit of kHz."))
	),
	(bios->reserved, reserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(NULL, i2cdatalut,
		(ATUI_NODISPLAY, ATUI_DYNARRAY, (
			(ATUI_NULL, i2cdatalut [%u],
				(ATUI_NAN, ATUI_INLINE, atom_i2c_data_entry),
				(ATUI_NODESCR)
			),
			bios->i2cdatalut, atomtree->lut_entries //start, count
		)),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_svid2_voltage_object_v4, atomtree_voltage_object_v4,
	(bios->header, header,
		(ATUI_NAN, ATUI_INLINE, atom_voltage_object_header_v4), (ATUI_NODESCR)
	),
	(bios->loadline_psi1.loadline_psi1, loadline_psi1,
		(ATUI_BIN, ATUI_BITFIELD, (
			(loadline_setting, 4,0, ATUI_DEC, ((LANG_ENG, "core trim and offset trim"))),
			(PSI1_L_enable,    5,5, ATUI_DEC, (ATUI_NODESCR)),
			(reserved,         7,6, ATUI_HEX, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	),
	(bios->psi0_l_vid_thresd, psi0_l_vid_thresd,
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "VR PSI0_L VID threshold"))
	),
	(bios->psi0_enable, psi0_enable,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->maxvstep, maxvstep,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->telemetry_offset, telemetry_offset,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->telemetry_gain, telemetry_gain,
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved1, reserved1,
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_merged_voltage_object_v4, atui_nullstruct,
	(bios->header, header,
		(ATUI_NAN, ATUI_INLINE, atom_voltage_object_header_v4), (ATUI_NODESCR)
	),
	(bios->merged_powerrail_type, merged_powerrail_type,
		(ATUI_DEC, ATUI_ENUM, atom_voltage_type), (ATUI_NODESCR)
	),
	(bios->reserved, reserved,
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)


