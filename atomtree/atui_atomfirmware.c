/*
AtomTree iterable interface for UIs.

See ppatui.h for the metaprogramming and atui.h for general API.

********************************************************************************
************************** Basic Usage and Namespaces **************************
********************************************************************************
There are two namespaces available, bios and atomtree.
bios is the struct that the branch represents, straightforward.
atomtree is an optional atomtree association that could be useful to pull in
computed data; or even represent atomtree-computed data as leaves.

declaration pseudo example:
PPATUI_FUNCIFY(struct|union, bios_struct_namespace, atomtree_struct_namespace
	(bios->namespace_var, "UI display name",
		(radix, fancy, optional_fancy_args),
		(
			(lang, description),
			(lang, description)
		)
	),
	(atomtree->namespace_var, "UI display name",
		(radix, fancy, optional_fancy_args),
		(
			(lang, "description"),
			(lang, "description")
		)
	)
)

instantiation pseudo example:
atui_branch* foba = ATUI_MAKE_BRANCH(name_of_bios_struct,
	"optional UI rename",
	atomtree_pointer, bios_pointer,
	number_of_child_branches, child_branches_array
)


After instantiation, to add a branch as a child to another branch,
ATUI_ADD_BRANCH(parent_branch, child_branch);


WARNING: always have the last comma removed:
This is bad:  arg,arg,)
This is good: arg,arg)

********************************************************************************
*********************************** Radix *************************************
********************************************************************************

If the table element should be viewed as a number, set a radix. radix is one of
ATUI_NAN, ATUI_DEC, ATUI_HEX, ATUI_OCT, ATUI_BIN.
If the element should be omitted from UI display, set radix to ATUI_NODISPLAY

ATUI_FRAC can signify if it should be viewed as a decimal fraction number. This
is usually automatically set based on the orignial C type.

ATUI_SIGNED can signify if it's a signed number. This is usually automatically
set based on the orignial C type.

********************************************************************************
********************************* Fancy Types: *********************************
********************************************************************************
ATUI_BITFIELD:
If the element should be viewed in base 2, but also has bitfields for children:
	(source->namespace_var, "UI display name",
		(radix, ATUI_BITFIELD, (
			("bitfield entry name 0", end_bit, start_bit, radix,
				(lang, "description"),
				(lang, "description")
			),
			("bitfield entry name 1", 7, 0, ATUI_DEC, (ATUI_NODESCR)),
			("bitfield entry name 2", 31,8, (ATUI_DEC|ATUI_SIGNED),
				(ATUI_NODESCR)
			),
		)), (ATUI_NODESCR)
	)

The child leaves will be marked with _ATUI_BITCHILD in its type to aid UI
layout.

If a child is should be signed with Two's Complement, set ATUI_SIGNED in its
radix alongside its main radix.

********************************************************************************
ATUI_ENUM:
If the element should have a list of text-val pairs, an enum,
First populate the atui enum:
	PPATUI_ENUMER(enum_struct_name,
		ENUM_ENTRY1,
		ENUM_ENTRY2,
		ENUM_ENTRY3,
	)
And then for the atui table,
	(source->namespace_var, "UI display name",
		(radix, ATUI_ENUM, enum_struct_name),
		(ATUI_NODESCR)
	)

********************************************************************************
ATUI_INLINE:
If the element should reference a table, a atui_branch to inline as a
collection of leaves,
	(source->namespace_var, "UI display name",
		(ATUI_NAN, ATUI_INLINE, table_to_inline),
		(ATUI_NODESCR)
	)
If you want to import just the leaves of the table, as if it was the leaves of
the branch you're constructing, set the radix to ATUI_NODISPLAY.

While not practically useful, the name of the branch object will copy the UI
display name of the leaf.

Also make sure the table is defined with an ATUI_FUNCIFY().

********************************************************************************
ATUI_PETIOLE:
If the element should reference a table, a atui_branch to integrate as a child
branch
	(source->namespace_var, "UI display name",
		(ATUI_NAN, ATUI_PETIOLE, table_to_reference),
		(ATUI_NODESCR)
	)
Since it isn't a leaf, but a reference to another branch, radix is ignored.
The name of the branch object will copy the UI display name of the leaf.

Also make sure the table is populated with an ATUI_FUNCIFY().

********************************************************************************
ATUI_STRING, ATUI_ARRAY:
If the element is a dynanmically-sized 0-terminated string,
	(source->namespace_var, "UI display name",
		(ATUI_NAN, ATUI_STRING),
		(ATUI_NODESCR)
	),
or otherwise an array,
	(source->namespace_var, "UI display name",
		(ATUI_HEX, ATUI_ARRAY),
		(ATUI_NODESCR)
	),

If it's an array, data will be represented in the radix of your choosing, with
the exception of fractions.

If the array is text but has a static size, set the fancy to ATUI_ARRAY and
radix to ATUI_NAN.

********************************************************************************
ATUI_DYNARRAY:
	(source->array_start_pointer, "leaf top UI name",
		(ATUI_NODISPLAY, ATUI_DYNARRAY, (
			// Leaf pattern:
			(ATUI_NULL, "UI display name",
				(radix, fancy, optional_fancy_args),
				(
					(lang, "description"),
					(lang, "description")
				)
			),
			source->deferred_pointers, source->dynarray_number_of_elements,
			enum_name
		)),
		(ATUI_NODESCR)
	)

If there is an array or number of leaves that is dynamically sized, especially
if it has a dynamic allocation, ATUI_DYNARRY can pull in the boundaries from
atomtree.

The leaf pattern follows regular syntax, and can be a bitfield.

dynarray_start_pointer is a direct pointer that is treated as the beginning of
the array, such that access would be effectively,
	datatype* dataptr = &(source->array_start_pointer[i]);

deferred_pointers is an array of pointers, each of which points an element,
such that access would be effectively,
	datatype* dataptr = source->deferred_pointers[i];

dynarray_start_pointer is for contiguous isometric arrays; deferred_pointers is
for arrays whose elements are not necessarily contiguous, and/or not
necessarily equally-sized (eg strings, for ATUI_STRING).
array_start_pointer takes precedence over deferred pointers; to use
deferred_pointers, array_start_pointer must be NULL.

dynarray_number_of_elements counts how long the array goes on for.

If an enum should tag along for UI/naming purposes, state an enum; otherwise
state the enum name as ATUI_NULL . The enum will be walked through sequentually
in the order as it is defined with PPATUI_ENUMER().
Futhermore, make sure the enum has an associated PPATUI_ENUMER() definition.

Leaf top UI name won't get displayed if ATUI_NODISPLAY is set for the radix

********************************************************************************



python function to convert your bog-standard C struct into a basic ATUI format
def struct_to_atui(s):
	import re
	#
	s = re.sub("(\n\t*)    ","\g<1>\t", s)
	s = re.sub("(\n\t*)    ","\g<1>\t", s)
	s = re.sub("(\n\t*)    ","\g<1>\t", s)
	s = re.sub("(\n\t*)    ","\g<1>\t", s)
	s = re.sub("[ \t]+\n", "\n", s)
	#
	# self struct:
	s = re.sub("(struct) ([a-zA-Z0-9_]+) {", "PPATUI_FUNCIFY(\g<1>, \g<2>, atui_nullstruct,",s)
	#
	# dynarrays part 1 (bulk of it):
	s = re.sub("(((struct|union)\s+[a-zA-Z0-9_]+)\s+([a-zA-Z0-9_]+))\[([a-zA-Z0-9_]*)\];",
		"(bios->\g<4>, u8\"\g<4>\", // start, name\n\t\t(ATUI_NAN, ATUI_DYNARRAY, (\n\t\t\t\g<1>;\n\t\t\tNULL, \g<5>, // deferred start, count\n\t\t\tATUI_NULL // enum\n\t\t)), (ATUI_NODESCR)\n\t),",s)
	s = re.sub("((u?int[0-9]+_t|char[0-9]+_t|float[0-9]+_t|uq[0-9]+_[0-9]+_t)\s+([a-zA-Z0-9_]+))\[([a-zA-Z_][a-zA-Z0-9_]*)\];",
		"(bios->\g<3>, u8\"\g<3>\", // start, name\n\t\t(ATUI_NAN, ATUI_DYNARRAY, (\n\t\t\t\g<1>;\n\t\t\tNULL, \g<4>, // deferred start, count\n\t\t\tATUI_NULL // enum\n\t\t)), (ATUI_NODESCR)\n\t),",s)
	#
	# embedded structs, create ATUI_INLINES from them:
	s = re.sub("(\t+)(union|struct)\s+([a-zA-Z0-9_]+)\s+([a-zA-Z0-9_]+)(\[[0-9]+\])?;", "\g<1>(bios->\g<4>, u8\"\g<4>\",\n\g<1>\t(ATUI_NAN, ATUI_INLINE, \g<3>),\n\g<1>\t(ATUI_NODESCR)\n\g<1>),", s)
	#
	# embdedded enums; very similar to structs/unions:
	s = re.sub("(\t+)(enum)\s+([a-zA-Z0-9_]+)\s+([a-zA-Z0-9_]+)(\[[0-9]+\])?;", "\g<1>(bios->\g<4>, u8\"\g<4>\",\n\g<1>\t(ATUI_DEC, ATUI_ENUM, \g<3>),\n\g<1>\t(ATUI_NODESCR)\n\g<1>),", s)
	#
	# integers: intn_t/uintn_t/charn_t/floatn_t/uqn_n_t
	s = re.sub("(\t+)(u?int[0-9]+_t|char[0-9]+_t|float[0-9]+_t|uq[0-9]+_[0-9]+_t)\s+([a-zA-Z0-9_]+)(\s+)?;", "\g<1>(bios->\g<3>, u8\"\g<3>\",\n\g<1>\t(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)\n\g<1>),", s)
	#
	# integer arrays, won't do embedded enums
	s = re.sub("(\t+)(u?int[0-9]+_t|char[0-9]+_t)\s+([a-zA-Z0-9_]+)\s?+\[[0-9]+\]\s?+;", "\g<1>(bios->\g<3>, u8\"\g<3>\",\n\g<1>\t(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)\n\g<1>),", s)
	#
	# take care of //-based comments
	s = re.sub("(\s+)?\(ATUI_NODESCR\)(\n\t\),)(\s+)?//(\s+)?(.*)", "\n\t\t((LANG_ENG, u8\"\g<5>\"))\g<2>", s)
	s = re.sub("\),(\s+)?};", ")\n)", s)
	#
	# dynarrays part 2: "(ATUI_NULL" for leaf; and  "%02u" for pattern name
	s = re.sub("(\(ATUI_NAN, ATUI_DYNARRAY, \(\n\t+\()[^,]+, ([^,]+)\"","\g<1>ATUI_NULL, \g<2> [%02u]\"",s)
	#
	print(s)


def bitfield_to_atui(s):
	import re
	s = re.sub("(\n\t*)    ","\g<1>\t", s)
	s = re.sub("(\n\t*)    ","\g<1>\t", s)
	s = re.sub("(\n\t*)    ","\g<1>\t", s)
	s = re.sub("(\n\t*)    ","\g<1>\t", s)
	s = re.sub("[ \t]+\n", "\n", s)
	#
	# self (union):
	s = re.sub("union\s+([a-zA-Z0-9_]+)\s*{", "PPATUI_FUNCIFY(union, \g<1>, atui_nullstruct,",s)
	#
	# raw data -> main bitfield leaf
	s = re.sub("uint[0-9]+_t\s+([a-zA-Z0-9_]+);","(bios->\g<1>, u8\"\g<1>\",\n\t\t(ATUI_BIN, ATUI_BITFIELD, (", s)
	#
	# delete 'struct { type'
	s = re.sub("\tstruct { uint[0-9]+_t\n", "", s)
	#
	# bitfield children:
	s = re.sub("([a-zA-Z0-9_]+)( *):([0-9]+)-([0-9]+) \+1[,;]", "\t(u8\"\g<1>\",\g<2>\g<3>,\g<4>, ATUI_DEC, (ATUI_NODESCR)),", s)
	#
	# child comments:
	s = re.sub(" \(ATUI_NODESCR\)\),(\s*)//\s*(.*)","\n\t\t\t\t((LANG_ENG, u8\"\g<2>\"))\n\t\t\t),",s)
	#
	# final:
	s = re.sub(",\n\t};\n};", "\n\t\t)), (ATUI_NODESCR)\n\t)\n)", s)
	print(s)


*/

/* for atomfirmware.h */

#include "atomtree.h"
#include "atui.h"

// basic empty branch mainly to have collapsables
PPATUI_FUNCIFY(struct, atui_nullstruct, atui_nullstruct)

PPATUI_FUNCIFY(struct, atombios_image, atom_tree,
	(bios->atombios_magic, u8"atombios_magic",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"little endian: 0xAA55"))
	),
	(bios->image_size, u8"image_size",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"0x02"))
	),
	(bios->reserved0, u8"reserved0",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->checksum, u8"checksum",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"0x21"))
	),
	(bios->reserved1, u8"reserved1",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->number_of_strings, u8"number_of_strings",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"0x2F"))
	),
	(bios->atomati_magic, u8"atomati_magic",
		(ATUI_NAN, ATUI_ARRAY),
		((LANG_ENG, u8"0x30; \" 761295520\" There is a space."))
	),
	(bios->reserved2, u8"reserved2",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->bios_header, u8"bios_header",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"0x48"))
	),
	(bios->reserved3, u8"reserved3",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->bios_date, u8"bios_date",
		(ATUI_NAN, ATUI_ARRAY),
		((LANG_ENG, u8"0x50"))
	),
	(bios->reserved4, u8"reserved4",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->atombios_strings_offset, u8"atombios_strings_offset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"0x6E"))
	),
	(bios->reserved5, u8"reserved5",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->vbios_part_number, u8"vbios_part_number",
		(ATUI_NAN, ATUI_STRING), // 0-term'd string
		((LANG_ENG, u8"0x80 ; only use if number_of_strings == 0"))
	),
	(bios->reserved6, u8"reserved6",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->asic_bus_mem_type, u8"asic_bus_mem_type",
		(ATUI_NAN, ATUI_ARRAY),
		((LANG_ENG, u8"0x94;  ATI days; AMD uses atombios_strings_offset."))
	),
	(NULL, u8"atombios strings", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"string [%02u]",
				(ATUI_NAN, ATUI_STRING), (ATUI_NODESCR)
			),
			atomtree->atombios_strings, // deferred start
			atomtree->num_of_crawled_strings, // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, atom_common_table_header, atui_nullstruct,
	(bios->structuresize, u8"structuresize",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->format_revision, u8"format_revision",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mainly used for a hw function, when the parser is not backward compatible"))
	),
	(bios->content_revision, u8"content_revision",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"change it when a data table has a structure change, or a hw function has a input/output parameter change"))
	)
)


PPATUI_FUNCIFY(struct, atom_rom_header_v2_2,
		atom_tree, // THE atom_tree struct

	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->atom_bios_string, u8"atom_bios_string",
		(ATUI_NAN, ATUI_ARRAY),
		((LANG_ENG, u8"enum atom_string_def atom_bios_string. Signature to distinguish between Atombios and non-atombios,"))
	),
	(bios->bios_segment_address, u8"bios_segment_address",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->protectedmodeoffset, u8"protectedmodeoffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->configfilenameoffset, u8"configfilenameoffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->crc_block_offset, u8"crc_block_offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vbios_bootupmessageoffset, u8"vbios_bootupmessageoffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->int10_offset, u8"int10_offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pcibusdevinitcode, u8"pcibusdevinitcode",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->iobaseaddress, u8"iobaseaddress",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->subsystem_vendor_id, u8"subsystem_vendor_id",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->subsystem_id, u8"subsystem_id",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pci_info_offset, u8"pci_info_offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->masterhwfunction_offset, u8"masterhwfunction_offset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Offest for SW to get all command function offsets, Don't change the position"))
	),
	(bios->masterdatatable_offset, u8"masterdatatable_offset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Offest for SW to get all data table offsets, Don't change the position"))
	),
	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pspdirtableoffset, u8"pspdirtableoffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)





PPATUI_FUNCIFY(struct, atom_master_data_table_v2_1,
		atomtree_master_datatable_v2_1,

	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->utilitypipeline, u8"utilitypipeline",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Offest for the utility to get parser info, Don't change this position!"))
	),
	(bios->multimedia_info, u8"multimedia_info",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smc_dpm_info, u8"smc_dpm_info",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable3, u8"sw_datatable3",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->firmwareinfo, u8"firmwareinfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components"))
	),
	(bios->sw_datatable5, u8"sw_datatable5",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->lcd_info, u8"lcd_info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components"))
	),
	(bios->sw_datatable7, u8"sw_datatable7",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smu_info, u8"smu_info",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable9, u8"sw_datatable9",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable10, u8"sw_datatable10",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vram_usagebyfirmware, u8"vram_usagebyfirmware",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components"))
	),
	(bios->gpio_pin_lut, u8"gpio_pin_lut",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components"))
	),
	(bios->sw_datatable13, u8"sw_datatable13",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfx_info, u8"gfx_info",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->powerplayinfo, u8"powerplayinfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components"))
	),
	(bios->sw_datatable16, u8"sw_datatable16",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable17, u8"sw_datatable17",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable18, u8"sw_datatable18",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable19, u8"sw_datatable19",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable20, u8"sw_datatable20",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable21, u8"sw_datatable21",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->displayobjectinfo, u8"displayobjectinfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components"))
	),
	(bios->indirectioaccess, u8"indirectioaccess",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"used as an internal one"))
	),
	(bios->umc_info, u8"umc_info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components"))
	),
	(bios->sw_datatable25, u8"sw_datatable25",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable26, u8"sw_datatable26",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dce_info, u8"dce_info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components"))
	),
	(bios->vram_info, u8"vram_info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components"))
	),
	(bios->sw_datatable29, u8"sw_datatable29",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->integratedsysteminfo, u8"integratedsysteminfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components"))
	),
	(bios->asic_profiling_info, u8"asic_profiling_info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components"))
	),
	(bios->voltageobject_info, u8"voltageobject_info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"shared by various SW components"))
	),
	(bios->sw_datatable33, u8"sw_datatable33",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sw_datatable34, u8"sw_datatable34",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, psi_sel_mask, atui_nullstruct,
	(bios->sel_mask, u8"sel_mask",
		(ATUI_NODISPLAY, ATUI_BITFIELD, (
			(u8"VR0_PLANE0_PSI0", 0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"VR0_PLANE0_PSI1", 1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"VR0_PLANE1_PSI0", 2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"VR0_PLANE1_PSI1", 3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"VR1_PLANE0_PSI0", 4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"VR1_PLANE0_PSI1", 5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"VR1_PLANE1_PSI0", 6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"VR1_PLANE1_PSI1", 7,7, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)




PPATUI_FUNCIFY(struct, atom_smc_dpm_info_v4_1, atomtree_smc_dpm_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header), (ATUI_NODESCR)
	),
	(bios->liquid1_i2c_address, u8"liquid1_i2c_address",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->liquid2_i2c_address, u8"liquid2_i2c_address",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr_i2c_address, u8"vr_i2c_address",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->plx_i2c_address, u8"plx_i2c_address",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->liquid_i2c_linescl, u8"liquid_i2c_linescl",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->liquid_i2c_linesda, u8"liquid_i2c_linesda",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr_i2c_linescl, u8"vr_i2c_linescl",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr_i2c_linesda, u8"vr_i2c_linesda",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->plx_i2c_linescl, u8"plx_i2c_linescl",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->plx_i2c_linesda, u8"plx_i2c_linesda",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vrsensorpresent, u8"vrsensorpresent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->liquidsensorpresent, u8"liquidsensorpresent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->maxvoltagestepgfx, u8"maxvoltagestepgfx",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->maxvoltagestepsoc, u8"maxvoltagestepsoc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->vddgfxvrmapping, u8"vddgfxvrmapping",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddsocvrmapping, u8"vddsocvrmapping",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddmem0vrmapping, u8"vddmem0vrmapping",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddmem1vrmapping, u8"vddmem1vrmapping",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->gfxulvphasesheddingmask, u8"gfxulvphasesheddingmask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask), (ATUI_NODESCR)
	),
	(bios->soculvphasesheddingmask, u8"soculvphasesheddingmask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask), (ATUI_NODESCR)
	),
	(bios->padding8_v, u8"padding8_v",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->gfxmaxcurrent, u8"gfxmaxcurrent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxoffset, u8"gfxoffset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrygfx, u8"padding_telemetrygfx",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->socmaxcurrent, u8"socmaxcurrent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->socoffset, u8"socoffset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrysoc, u8"padding_telemetrysoc",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->mem0maxcurrent, u8"mem0maxcurrent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem0offset, u8"mem0offset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrymem0, u8"padding_telemetrymem0",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->mem1maxcurrent, u8"mem1maxcurrent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem1offset, u8"mem1offset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrymem1, u8"padding_telemetrymem1",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->acdcgpio, u8"acdcgpio",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->acdcpolarity, u8"acdcpolarity",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr0hotgpio, u8"vr0hotgpio",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr0hotpolarity, u8"vr0hotpolarity",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->vr1hotgpio, u8"vr1hotgpio",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr1hotpolarity, u8"vr1hotpolarity",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding1, u8"padding1",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding2, u8"padding2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->ledpin0, u8"ledpin0",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ledpin1, u8"ledpin1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ledpin2, u8"ledpin2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding8_4, u8"padding8_4",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->pllgfxclkspreadenabled, u8"pllgfxclkspreadenabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pllgfxclkspreadpercent, u8"pllgfxclkspreadpercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pllgfxclkspreadfreq, u8"pllgfxclkspreadfreq",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->uclkspreadenabled, u8"uclkspreadenabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->uclkspreadpercent, u8"uclkspreadpercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->uclkspreadfreq, u8"uclkspreadfreq",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->socclkspreadenabled, u8"socclkspreadenabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->socclkspreadpercent, u8"socclkspreadpercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->socclkspreadfreq, u8"socclkspreadfreq",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->acggfxclkspreadenabled, u8"acggfxclkspreadenabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->acggfxclkspreadpercent, u8"acggfxclkspreadpercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->acggfxclkspreadfreq, u8"acggfxclkspreadfreq",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Vr2_I2C_address, u8"Vr2_I2C_address",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_vr2, u8"padding_vr2",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->boardreserved, u8"boardreserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_smc_dpm_info_v4_3, atomtree_smc_dpm_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header), (ATUI_NODESCR)
	),
	(bios->liquid1_i2c_address, u8"liquid1_i2c_address",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->liquid2_i2c_address, u8"liquid2_i2c_address",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr_i2c_address, u8"vr_i2c_address",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->plx_i2c_address, u8"plx_i2c_address",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->liquid_i2c_linescl, u8"liquid_i2c_linescl",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->liquid_i2c_linesda, u8"liquid_i2c_linesda",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr_i2c_linescl, u8"vr_i2c_linescl",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr_i2c_linesda, u8"vr_i2c_linesda",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->plx_i2c_linescl, u8"plx_i2c_linescl",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->plx_i2c_linesda, u8"plx_i2c_linesda",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vrsensorpresent, u8"vrsensorpresent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->liquidsensorpresent, u8"liquidsensorpresent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->maxvoltagestepgfx, u8"maxvoltagestepgfx",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->maxvoltagestepsoc, u8"maxvoltagestepsoc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->vddgfxvrmapping, u8"vddgfxvrmapping",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddsocvrmapping, u8"vddsocvrmapping",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddmem0vrmapping, u8"vddmem0vrmapping",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddmem1vrmapping, u8"vddmem1vrmapping",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->gfxulvphasesheddingmask, u8"gfxulvphasesheddingmask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask), (ATUI_NODESCR)
	),
	(bios->soculvphasesheddingmask, u8"soculvphasesheddingmask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask), (ATUI_NODESCR)
	),
	(bios->externalsensorpresent, u8"externalsensorpresent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding8_v, u8"padding8_v",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->gfxmaxcurrent, u8"gfxmaxcurrent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxoffset, u8"gfxoffset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrygfx, u8"padding_telemetrygfx",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->socmaxcurrent, u8"socmaxcurrent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->socoffset, u8"socoffset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrysoc, u8"padding_telemetrysoc",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->mem0maxcurrent, u8"mem0maxcurrent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem0offset, u8"mem0offset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrymem0, u8"padding_telemetrymem0",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->mem1maxcurrent, u8"mem1maxcurrent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem1offset, u8"mem1offset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrymem1, u8"padding_telemetrymem1",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->acdcgpio, u8"acdcgpio",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->acdcpolarity, u8"acdcpolarity",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr0hotgpio, u8"vr0hotgpio",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr0hotpolarity, u8"vr0hotpolarity",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->vr1hotgpio, u8"vr1hotgpio",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr1hotpolarity, u8"vr1hotpolarity",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding1, u8"padding1",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding2, u8"padding2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->ledpin0, u8"ledpin0",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ledpin1, u8"ledpin1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ledpin2, u8"ledpin2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding8_4, u8"padding8_4",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->pllgfxclkspreadenabled, u8"pllgfxclkspreadenabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pllgfxclkspreadpercent, u8"pllgfxclkspreadpercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pllgfxclkspreadfreq, u8"pllgfxclkspreadfreq",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->uclkspreadenabled, u8"uclkspreadenabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->uclkspreadpercent, u8"uclkspreadpercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->uclkspreadfreq, u8"uclkspreadfreq",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->fclkspreadenabled, u8"fclkspreadenabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fclkspreadpercent, u8"fclkspreadpercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fclkspreadfreq, u8"fclkspreadfreq",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->fllgfxclkspreadenabled, u8"fllgfxclkspreadenabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fllgfxclkspreadpercent, u8"fllgfxclkspreadpercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fllgfxclkspreadfreq, u8"fllgfxclkspreadfreq",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->boardreserved, u8"boardreserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(struct, i2ccontrollerconfig_u32, atui_nullstruct,
	(bios->enabled, u8"enabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->slaveaddress, u8"slaveaddress",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->controllerport, u8"controllerport",
		(ATUI_DEC, ATUI_ENUM, I2cControllerPort_e),
		(ATUI_NODESCR)
	),
	(bios->controllername, u8"controllername",
		(ATUI_DEC, ATUI_ENUM, I2cControllerName_e),
		(ATUI_NODESCR)
	),
	(bios->thermalthrottler, u8"thermalthrottler",
		(ATUI_DEC, ATUI_ENUM, I2cControllerThrottler_e),
		(ATUI_NODESCR)
	),
	(bios->i2cprotocol, u8"i2cprotocol",
		(ATUI_DEC, ATUI_ENUM, I2cControllerProtocol_e),
		(ATUI_NODESCR)
	),
	(bios->i2cspeed, u8"i2cspeed",
		(ATUI_DEC, ATUI_ENUM, I2cControllerSpeed_e),
		(ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, i2ccontrollerconfig_u8, atui_nullstruct,
	(bios->enabled, u8"enabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->speed, u8"speed",
		(ATUI_DEC, ATUI_ENUM, I2cControllerSpeed_e),
		(ATUI_NODESCR)
	),
	(bios->slaveaddress, u8"slaveaddress",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->controllerport, u8"controllerport",
		(ATUI_DEC, ATUI_ENUM, I2cControllerPort_e),
		(ATUI_NODESCR)
	),
	(bios->controllername, u8"controllername",
		(ATUI_DEC, ATUI_ENUM, I2cControllerName_e),
		(ATUI_NODESCR)
	),
	(bios->thermalthrottler, u8"thermalthrottler",
		(ATUI_DEC, ATUI_ENUM, I2cControllerThrottler_e),
		(ATUI_NODESCR)
	),
	(bios->i2cprotocol, u8"i2cprotocol",
		(ATUI_DEC, ATUI_ENUM, I2cControllerProtocol_e),
		(ATUI_NODESCR)
	),
	(bios->padding, u8"padding",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, i2ccontrollerconfig_u8_mixed, atui_nullstruct,
	(bios->enabled, u8"enabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->speed, u8"speed",
		(ATUI_DEC, ATUI_ENUM, I2cControllerSpeed_e),
		(ATUI_NODESCR)
	),
	(bios->padding, u8"padding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->slaveaddress, u8"slaveaddress",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->controllerport, u8"controllerport",
		(ATUI_DEC, ATUI_ENUM, I2cControllerPort_e),
		(ATUI_NODESCR)
	),
	(bios->controllername, u8"controllername",
		(ATUI_DEC, ATUI_ENUM, I2cControllerName_e),
		(ATUI_NODESCR)
	),
	(bios->thermalthrottler, u8"thermalthrottler",
		(ATUI_DEC, ATUI_ENUM, I2cControllerThrottler_e),
		(ATUI_NODESCR)
	),
	(bios->i2cprotocol, u8"i2cprotocol",
		(ATUI_DEC, ATUI_ENUM, I2cControllerProtocol_e),
		(ATUI_NODESCR)
	)
)




PPATUI_FUNCIFY(struct, atom_smc_dpm_info_v4_4, atomtree_smc_dpm_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header), (ATUI_NODESCR)
	),
	(bios->i2c_padding, u8"i2c_padding",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),

	(bios->maxvoltagestepgfx, u8"maxvoltagestepgfx",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->maxvoltagestepsoc, u8"maxvoltagestepsoc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->vddgfxvrmapping, u8"vddgfxvrmapping",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddsocvrmapping, u8"vddsocvrmapping",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddmem0vrmapping, u8"vddmem0vrmapping",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vddmem1vrmapping, u8"vddmem1vrmapping",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->gfxulvphasesheddingmask, u8"gfxulvphasesheddingmask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask), (ATUI_NODESCR)
	),
	(bios->soculvphasesheddingmask, u8"soculvphasesheddingmask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask), (ATUI_NODESCR)
	),
	(bios->externalsensorpresent, u8"externalsensorpresent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding8_v, u8"padding8_v",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->gfxmaxcurrent, u8"gfxmaxcurrent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxoffset, u8"gfxoffset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrygfx, u8"padding_telemetrygfx",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->socmaxcurrent, u8"socmaxcurrent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->socoffset, u8"socoffset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrysoc, u8"padding_telemetrysoc",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->mem0maxcurrent, u8"mem0maxcurrent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem0offset, u8"mem0offset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrymem0, u8"padding_telemetrymem0",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->mem1maxcurrent, u8"mem1maxcurrent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem1offset, u8"mem1offset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding_telemetrymem1, u8"padding_telemetrymem1",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->acdcgpio, u8"acdcgpio",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->acdcpolarity, u8"acdcpolarity",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr0hotgpio, u8"vr0hotgpio",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr0hotpolarity, u8"vr0hotpolarity",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->vr1hotgpio, u8"vr1hotgpio",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vr1hotpolarity, u8"vr1hotpolarity",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding1, u8"padding1",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding2, u8"padding2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->ledpin0, u8"ledpin0",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ledpin1, u8"ledpin1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ledpin2, u8"ledpin2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->padding8_4, u8"padding8_4",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->pllgfxclkspreadenabled, u8"pllgfxclkspreadenabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pllgfxclkspreadpercent, u8"pllgfxclkspreadpercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pllgfxclkspreadfreq, u8"pllgfxclkspreadfreq",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->uclkspreadenabled, u8"uclkspreadenabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->uclkspreadpercent, u8"uclkspreadpercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->uclkspreadfreq, u8"uclkspreadfreq",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->fclkspreadenabled, u8"fclkspreadenabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fclkspreadpercent, u8"fclkspreadpercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fclkspreadfreq, u8"fclkspreadfreq",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->fllgfxclkspreadenabled, u8"fllgfxclkspreadenabled",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fllgfxclkspreadpercent, u8"fllgfxclkspreadpercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fllgfxclkspreadfreq, u8"fllgfxclkspreadfreq",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),


	(bios->i2ccontrollers, u8"I2C Controllers", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_NAN, ATUI_PETIOLE, i2ccontrollerconfig_u32),
				(ATUI_NODESCR)
			),
			NULL, // deferred start
			// count:
			sizeof(bios->i2ccontrollers)/sizeof(bios->i2ccontrollers[0]),
			I2cControllerName_SMU_11_0_0_e // enum
		)), (ATUI_NODESCR)
	),


	(bios->boardreserved, u8"boardreserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, atom_smc_dpm_info_v4_5, atomtree_smc_dpm_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header), (ATUI_NODESCR)
	),
	(bios->I2cControllers, u8"I2C Controllers", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_NAN, ATUI_PETIOLE, i2ccontrollerconfig_u8_mixed),
				(ATUI_NODESCR)
			),
			NULL, // deferred start
			// count:
			sizeof(bios->I2cControllers)/sizeof(bios->I2cControllers[0]),
			I2cControllerName_SMU_11_0_7_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->MaxVoltageStepGfx, u8"MaxVoltageStepGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value."))
	),
	(bios->MaxVoltageStepSoc, u8"MaxVoltageStepSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value."))
	),

	(bios->VddGfxVrMapping, u8"VddGfxVrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),
	(bios->VddSocVrMapping, u8"VddSocVrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),
	(bios->VddMem0VrMapping, u8"VddMem0VrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),
	(bios->VddMem1VrMapping, u8"VddMem1VrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),

	(bios->GfxUlvPhaseSheddingMask, u8"GfxUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->SocUlvPhaseSheddingMask, u8"SocUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->ExternalSensorPresent, u8"ExternalSensorPresent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"External RDI connected to TMON (aka TEMP IN)"))
	),
	(bios->Padding8_V, u8"Padding8_V",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Telemetry Settings"))
	),
	(bios->GfxMaxCurrent, u8"GfxMaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->GfxOffset, u8"GfxOffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryGfx, u8"Padding_TelemetryGfx",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocMaxCurrent, u8"SocMaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->SocOffset, u8"SocOffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetrySoc, u8"Padding_TelemetrySoc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem0MaxCurrent, u8"Mem0MaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Mem0Offset, u8"Mem0Offset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryMem0, u8"Padding_TelemetryMem0",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem1MaxCurrent, u8"Mem1MaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Mem1Offset, u8"Mem1Offset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryMem1, u8"Padding_TelemetryMem1",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO Settings"))
	),
	(bios->AcDcGpio, u8"AcDcGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for AC/DC switching"))
	),
	(bios->AcDcPolarity, u8"AcDcPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for AC/DC switching"))
	),
	(bios->VR0HotGpio, u8"VR0HotGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for VR0 HOT event"))
	),
	(bios->VR0HotPolarity, u8"VR0HotPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR0 HOT event"))
	),

	(bios->VR1HotGpio, u8"VR1HotGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for VR1 HOT event"))
	),
	(bios->VR1HotPolarity, u8"VR1HotPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR1 HOT event"))
	),
	(bios->GthrGpio, u8"GthrGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for GTHR Event"))
	),
	(bios->GthrPolarity, u8"GthrPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"replace GPIO polarity for GTHR"))
	),

	(bios->LedPin0, u8"LedPin0",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"LED Display Settings GPIO number for LedPin[0]"))
	),
	(bios->LedPin1, u8"LedPin1",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[1]"))
	),
	(bios->LedPin2, u8"LedPin2",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[2]"))
	),
	(bios->padding8_4, u8"padding8_4",
		(ATUI_DEC, ATUI_NOFANCY),
		(ATUI_NODESCR)
	),
	(bios->PllGfxclkSpreadEnabled, u8"PllGfxclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->PllGfxclkSpreadPercent, u8"PllGfxclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->PllGfxclkSpreadFreq, u8"PllGfxclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->DfllGfxclkSpreadEnabled, u8"DfllGfxclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GFXCLK DFLL Spread Spectrum on or off"))
	),
	(bios->DfllGfxclkSpreadPercent, u8"DfllGfxclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->DfllGfxclkSpreadFreq, u8"DfllGfxclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->UclkSpreadEnabled, u8"UclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"UCLK Spread Spectrum  on or off"))
	),
	(bios->UclkSpreadPercent, u8"UclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->UclkSpreadFreq, u8"UclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->SoclkSpreadEnabled, u8"SoclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"SOCCLK Spread Spectrum on or off"))
	),
	(bios->SocclkSpreadPercent, u8"SocclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->SocclkSpreadFreq, u8"SocclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->TotalBoardPower, u8"TotalBoardPower",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Only needed for TCP Estimated case, where TCP = TGP+Total Board Power"))
	),
	(bios->BoardPadding, u8"BoardPadding",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Mvdd Svi2 Div Ratio Setting"))
	),
	(bios->MvddRatio, u8"MvddRatio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"This is used for MVDD Vid workaround. It has 16 fractional bits (Q16.16)"))
	),

	(bios->BoardReserved, u8"BoardReserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_smc_dpm_info_v4_6, atui_nullstruct,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header), (ATUI_NODESCR)
	),
	(bios->i2c_padding, u8"i2c_padding",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"old i2c control are moved to new area"))
	),

	(bios->maxvoltagestepgfx, u8"maxvoltagestepgfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in mv(q2) max voltage step that smu will request. multiple steps are taken if voltage change exceeds this value."))
	),
	(bios->maxvoltagestepsoc, u8"maxvoltagestepsoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in mv(q2) max voltage step that smu will request. multiple steps are taken if voltage change exceeds this value."))
	),

	(bios->vddgfxvrmapping, u8"vddgfxvrmapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"use vr_mapping* bitfields"))
	),
	(bios->vddsocvrmapping, u8"vddsocvrmapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"use vr_mapping* bitfields"))
	),
	(bios->vddmemvrmapping, u8"vddmemvrmapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"use vr_mapping* bitfields"))
	),
	(bios->boardvrmapping, u8"boardvrmapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"use vr_mapping* bitfields"))
	),

	(bios->gfxulvphasesheddingmask, u8"gfxulvphasesheddingmask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, u8"set this to 1 to set psi0/1 to 1 in ulv mode"))
	),
	(bios->externalsensorpresent, u8"externalsensorpresent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"external rdi connected to tmon (aka temp in)"))
	),
	(bios->padding8_v, u8"padding8_v",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"telemetry settings"))
	),
	(bios->gfxmaxcurrent, u8"gfxmaxcurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in amps"))
	),
	(bios->gfxoffset, u8"gfxoffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in amps"))
	),
	(bios->padding_telemetrygfx, u8"padding_telemetrygfx",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->socmaxcurrent, u8"socmaxcurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in amps"))
	),
	(bios->socoffset, u8"socoffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in amps"))
	),
	(bios->padding_telemetrysoc, u8"padding_telemetrysoc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->memmaxcurrent, u8"memmaxcurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in amps"))
	),
	(bios->memoffset, u8"memoffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in amps"))
	),
	(bios->padding_telemetrymem, u8"padding_telemetrymem",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->boardmaxcurrent, u8"boardmaxcurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in amps"))
	),
	(bios->boardoffset, u8"boardoffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in amps"))
	),
	(bios->padding_telemetryboardinput, u8"padding_telemetryboardinput",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"gpio settings"))
	),
	(bios->vr0hotgpio, u8"vr0hotgpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"gpio pin configured for vr0 hot event"))
	),
	(bios->vr0hotpolarity, u8"vr0hotpolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"gpio polarity for vr0 hot event"))
	),
	(bios->vr1hotgpio, u8"vr1hotgpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"gpio pin configured for vr1 hot event"))
	),
	(bios->vr1hotpolarity, u8"vr1hotpolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"gpio polarity for vr1 hot event"))
	),

	(bios->pllgfxclkspreadenabled, u8"pllgfxclkspreadenabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->pllgfxclkspreadpercent, u8"pllgfxclkspreadpercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pllgfxclkspreadfreq, u8"pllgfxclkspreadfreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"khz"))
	),

	(bios->uclkspreadenabled, u8"uclkspreadenabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->uclkspreadpercent, u8"uclkspreadpercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->uclkspreadfreq, u8"uclkspreadfreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"khz"))
	),

	(bios->fclkspreadenabled, u8"fclkspreadenabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->fclkspreadpercent, u8"fclkspreadpercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fclkspreadfreq, u8"fclkspreadfreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"khz"))
	),

	(bios->fllgfxclkspreadenabled, u8"fllgfxclkspreadenabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->fllgfxclkspreadpercent, u8"fllgfxclkspreadpercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fllgfxclkspreadfreq, u8"fllgfxclkspreadfreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"khz"))
	),

	(bios->i2ccontrollers, u8"i2ccontrollers", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_NAN, ATUI_PETIOLE, i2ccontrollerconfig_u8_mixed),
				(ATUI_NODESCR)
			),
			NULL, // deferred start
			// count:
			sizeof(bios->i2ccontrollers)/sizeof(bios->i2ccontrollers[0]),
			I2cControllerName_SMU_11_0_7_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->memorychannelenabled, u8"memorychannelenabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"for dram use only, max 32 channels enabled bit mask."))
	),

	(bios->drambitwidth, u8"drambitwidth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"for dram use only. see dram bit width type defines"))
	),
	(bios->paddingmem, u8"paddingmem",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"total board power"))
	),
	(bios->totalboardpower, u8"totalboardpower",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"only needed for tcp estimated case, where tcp = tgp+total board power"))
	),
	(bios->boardpadding, u8"boardpadding",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"section: xgmi training"))
	),
	(bios->xgmilinkspeed, u8"xgmilinkspeed",
		(ATUI_DEC, ATUI_ENUM, XGMI_LINK_RATE_e),
		(ATUI_NODESCR)
	),
	(bios->xgmilinkwidth, u8"xgmilinkwidth",
		(ATUI_DEC, ATUI_ENUM, XGMI_LINK_WIDTH_e),
		(ATUI_NODESCR)
	),

	(bios->xgmifclkfreq, u8"xgmifclkfreq",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->xgmisocvoltage, u8"xgmisocvoltage",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"reserved"))
	),
	(bios->boardreserved, u8"boardreserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_smc_dpm_info_v4_7, atui_nullstruct,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header), (ATUI_NODESCR)
	),
	(bios->I2cControllers, u8"I2cControllers", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_NAN, ATUI_PETIOLE, i2ccontrollerconfig_u8_mixed),
				(ATUI_NODESCR)
			),
			NULL, // deferred start
			// count:
			sizeof(bios->I2cControllers)/sizeof(bios->I2cControllers[0]),
			I2cControllerName_SMU_11_0_7_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->MaxVoltageStepGfx, u8"MaxVoltageStepGfx",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value."))
	),
	(bios->MaxVoltageStepSoc, u8"MaxVoltageStepSoc",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken if voltage change exceeds this value."))
	),

	(bios->VddGfxVrMapping, u8"VddGfxVrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),
	(bios->VddSocVrMapping, u8"VddSocVrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),
	(bios->VddMem0VrMapping, u8"VddMem0VrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),
	(bios->VddMem1VrMapping, u8"VddMem1VrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),

	(bios->GfxUlvPhaseSheddingMask, u8"GfxUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->SocUlvPhaseSheddingMask, u8"SocUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->ExternalSensorPresent, u8"ExternalSensorPresent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"External RDI connected to TMON (aka TEMP IN)"))
	),
	(bios->Padding8_V, u8"Padding8_V",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Telemetry Settings"))
	),
	(bios->GfxMaxCurrent, u8"GfxMaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->GfxOffset, u8"GfxOffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryGfx, u8"Padding_TelemetryGfx",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocMaxCurrent, u8"SocMaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->SocOffset, u8"SocOffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetrySoc, u8"Padding_TelemetrySoc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem0MaxCurrent, u8"Mem0MaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Mem0Offset, u8"Mem0Offset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryMem0, u8"Padding_TelemetryMem0",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem1MaxCurrent, u8"Mem1MaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Mem1Offset, u8"Mem1Offset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryMem1, u8"Padding_TelemetryMem1",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO Settings"))
	),
	(bios->AcDcGpio, u8"AcDcGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for AC/DC switching"))
	),
	(bios->AcDcPolarity, u8"AcDcPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for AC/DC switching"))
	),
	(bios->VR0HotGpio, u8"VR0HotGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for VR0 HOT event"))
	),
	(bios->VR0HotPolarity, u8"VR0HotPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR0 HOT event"))
	),

	(bios->VR1HotGpio, u8"VR1HotGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for VR1 HOT event"))
	),
	(bios->VR1HotPolarity, u8"VR1HotPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR1 HOT event"))
	),
	(bios->GthrGpio, u8"GthrGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for GTHR Event"))
	),
	(bios->GthrPolarity, u8"GthrPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"replace GPIO polarity for GTHR"))
	),

	(bios->LedPin0, u8"LedPin0",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[0]"))
	),
	(bios->LedPin1, u8"LedPin1",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[1]"))
	),
	(bios->LedPin2, u8"LedPin2",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[2]"))
	),
	(bios->padding8_4, u8"padding8_4",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GFXCLK PLL Spread Spectrum"))
	),
	(bios->PllGfxclkSpreadEnabled, u8"PllGfxclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->PllGfxclkSpreadPercent, u8"PllGfxclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PllGfxclkSpreadFreq, u8"PllGfxclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->DfllGfxclkSpreadEnabled, u8"DfllGfxclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->DfllGfxclkSpreadPercent, u8"DfllGfxclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DfllGfxclkSpreadFreq, u8"DfllGfxclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->UclkSpreadEnabled, u8"UclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->UclkSpreadPercent, u8"UclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->UclkSpreadFreq, u8"UclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->SoclkSpreadEnabled, u8"SoclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->SocclkSpreadPercent, u8"SocclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SocclkSpreadFreq, u8"SocclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->TotalBoardPower, u8"TotalBoardPower",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Only needed for TCP Estimated case, where TCP = TGP+Total Board Power"))
	),
	(bios->BoardPadding, u8"BoardPadding",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Mvdd Svi2 Div Ratio Setting"))
	),

	(bios->MvddRatio, u8"MvddRatio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"This is used for MVDD Vid workaround. It has 16 fractional bits (Q16.16)"))
	),

	(bios->GpioI2cScl, u8"GpioI2cScl",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Serial Clock"))
	),
	(bios->GpioI2cSda, u8"GpioI2cSda",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Serial Data"))
	),
	(bios->GpioPadding, u8"GpioPadding",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Additional LED Display Settings"))
	),
	(bios->LedPin3, u8"LedPin3",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[3] - PCIE GEN Speed"))
	),
	(bios->LedPin4, u8"LedPin4",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[4] - PMFW Error Status"))
	),
	(bios->LedEnableMask, u8"LedEnableMask",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->PowerLimitScalar, u8"PowerLimitScalar",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"[PPT_THROTTLER_COUNT]"))
	),

	(bios->MvddUlvPhaseSheddingMask, u8"MvddUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		(ATUI_NODESCR)
	),
	(bios->VddciUlvPhaseSheddingMask, u8"VddciUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		(ATUI_NODESCR)
	),
	(bios->Padding8_Psi1, u8"Padding8_Psi1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding8_Psi2, u8"Padding8_Psi2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->BoardReserved, u8"BoardReserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_smc_dpm_info_v4_9, atui_nullstruct,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header), (ATUI_NODESCR)
	),

	(bios->I2cControllers, u8"I2cControllers", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_NAN, ATUI_PETIOLE, i2ccontrollerconfig_u8),
				(ATUI_NODESCR)
			),
			NULL, // deferred start
			I2C_CONTROLLER_NAME_COUNT_SMU11_PPT7, // count
			I2cControllerName_SMU_11_0_7_e // enum
		)), (ATUI_NODESCR)
	),
	(bios->I2cControllers, u8"Undefined I2cControllers", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"I2cControllers [8 + %02u]",
				(ATUI_NAN, ATUI_INLINE, i2ccontrollerconfig_u8),
				(ATUI_NODESCR)
			),
			NULL, // deferred start
			// count:
			((sizeof(bios->I2cControllers)/sizeof(bios->I2cControllers[0]))
			- I2C_CONTROLLER_NAME_COUNT_SMU11_PPT7
			),
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	),

	(bios->GpioScl, u8"GpioScl",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO Number for SCL Line, used only for CKSVII2C1"))
	),
	(bios->GpioSda, u8"GpioSda",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO Number for SDA Line, used only for CKSVII2C1"))
	),
	(bios->FchUsbPdSlaveAddr, u8"FchUsbPdSlaveAddr",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"For requesting USB PD controller S-states via FCH I2C when entering PME turn off"))
	),
	(bios->I2cSpare, u8"I2cSpare",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"SECTION: SVI2 Board Parameters"))
	),
	(bios->VddGfxVrMapping, u8"VddGfxVrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),
	(bios->VddSocVrMapping, u8"VddSocVrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),
	(bios->VddMem0VrMapping, u8"VddMem0VrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),
	(bios->VddMem1VrMapping, u8"VddMem1VrMapping",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Use VR_MAPPING* bitfields"))
	),

	(bios->GfxUlvPhaseSheddingMask, u8"GfxUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->SocUlvPhaseSheddingMask, u8"SocUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->VddciUlvPhaseSheddingMask, u8"VddciUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),
	(bios->MvddUlvPhaseSheddingMask, u8"MvddUlvPhaseSheddingMask",
		(ATUI_NAN, ATUI_INLINE, psi_sel_mask),
		((LANG_ENG, u8"set this to 1 to set PSI0/1 to 1 in ULV mode"))
	),

	(bios->GfxMaxCurrent, u8"GfxMaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->GfxOffset, u8"GfxOffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryGfx, u8"Padding_TelemetryGfx",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->SocMaxCurrent, u8"SocMaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->SocOffset, u8"SocOffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetrySoc, u8"Padding_TelemetrySoc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem0MaxCurrent, u8"Mem0MaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Mem0Offset, u8"Mem0Offset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryMem0, u8"Padding_TelemetryMem0",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->Mem1MaxCurrent, u8"Mem1MaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Mem1Offset, u8"Mem1Offset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryMem1, u8"Padding_TelemetryMem1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->MvddRatio, u8"MvddRatio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"This is used for MVDD  Svi2 Div Ratio workaround. It has 16 fractional bits (Q16.16)"))
	),

	(bios->AcDcGpio, u8"AcDcGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for AC/DC switching"))
	),
	(bios->AcDcPolarity, u8"AcDcPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for AC/DC switching"))
	),
	(bios->VR0HotGpio, u8"VR0HotGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for VR0 HOT event"))
	),
	(bios->VR0HotPolarity, u8"VR0HotPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR0 HOT event"))
	),

	(bios->VR1HotGpio, u8"VR1HotGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for VR1 HOT event"))
	),
	(bios->VR1HotPolarity, u8"VR1HotPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR1 HOT event"))
	),
	(bios->GthrGpio, u8"GthrGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for GTHR Event"))
	),
	(bios->GthrPolarity, u8"GthrPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"replace GPIO polarity for GTHR"))
	),

	(bios->LedPin0, u8"LedPin0",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[0]"))
	),
	(bios->LedPin1, u8"LedPin1",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[1]"))
	),
	(bios->LedPin2, u8"LedPin2",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for LedPin[2]"))
	),
	(bios->LedEnableMask, u8"LedEnableMask",
		(ATUI_NODISPLAY, ATUI_INLINE, led_display_control),
		(ATUI_NODESCR)
	),

	(bios->LedPcie, u8"LedPcie",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for PCIE results"))
	),
	(bios->LedError, u8"LedError",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO number for Error Cases"))
	),
	(bios->LedSpare1, u8"LedSpare1",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"SECTION: Clock Spread Spectrum"))
	),

	(bios->PllGfxclkSpreadEnabled, u8"PllGfxclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->PllGfxclkSpreadPercent, u8"PllGfxclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->PllGfxclkSpreadFreq, u8"PllGfxclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->DfllGfxclkSpreadEnabled, u8"DfllGfxclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->DfllGfxclkSpreadPercent, u8"DfllGfxclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->DfllGfxclkSpreadFreq, u8"DfllGfxclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->UclkSpreadEnabled, u8"UclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->UclkSpreadPercent, u8"UclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->UclkSpreadFreq, u8"UclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->FclkSpreadEnabled, u8"FclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->FclkSpreadPercent, u8"FclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->FclkSpreadFreq, u8"FclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->MemoryChannelEnabled, u8"MemoryChannelEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"For DRAM use only, Max 32 channels enabled bit mask."))
	),

	(bios->DramBitWidth, u8"DramBitWidth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"For DRAM use only. See Dram Bit width type defines"))
	),
	(bios->PaddingMem1, u8"PaddingMem1",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"Section: Total Board Power"))
	),
	(bios->TotalBoardPower, u8"TotalBoardPower",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Only needed for TCP Estimated case, where TCP = TGP+Total Board Power"))
	),
	(bios->BoardPowerPadding, u8"BoardPowerPadding",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"SECTION: XGMI Training"))
	),
	(bios->xgmilinkspeed, u8"xgmilinkspeed",
		(ATUI_DEC, ATUI_ENUM, XGMI_LINK_RATE_e),
		(ATUI_NODESCR)
	),
	(bios->xgmilinkwidth, u8"xgmilinkwidth",
		(ATUI_DEC, ATUI_ENUM, XGMI_LINK_WIDTH_e),
		(ATUI_NODESCR)
	),

	(bios->XgmiFclkFreq, u8"XgmiFclkFreq",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->XgmiSocVoltage, u8"XgmiSocVoltage",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"SECTION: Board Reserved"))
	),
	(bios->BoardReserved, u8"BoardReserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_smc_dpm_info_v4_10, atui_nullstruct,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header), (ATUI_NODESCR)
	),
	(bios->GfxMaxCurrent, u8"GfxMaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->GfxOffset, u8"GfxOffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryGfx, u8"Padding_TelemetryGfx",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->SocMaxCurrent, u8"SocMaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->SocOffset, u8"SocOffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetrySoc, u8"Padding_TelemetrySoc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->MemMaxCurrent, u8"MemMaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->MemOffset, u8"MemOffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryMem, u8"Padding_TelemetryMem",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->BoardMaxCurrent, u8"BoardMaxCurrent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->BoardOffset, u8"BoardOffset",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in Amps"))
	),
	(bios->Padding_TelemetryBoardInput, u8"Padding_TelemetryBoardInput",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Platform input telemetry voltage coefficient"))
	),
	(bios->BoardVoltageCoeffA, u8"BoardVoltageCoeffA",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"decode by /1000"))
	),
	(bios->BoardVoltageCoeffB, u8"BoardVoltageCoeffB",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"decode by /1000"))
	),

	(bios->VR0HotGpio, u8"VR0HotGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for VR0 HOT event"))
	),
	(bios->VR0HotPolarity, u8"VR0HotPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR0 HOT event"))
	),
	(bios->VR1HotGpio, u8"VR1HotGpio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO pin configured for VR1 HOT event"))
	),
	(bios->VR1HotPolarity, u8"VR1HotPolarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR1 HOT event"))
	),

	(bios->UclkSpreadEnabled, u8"UclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->UclkSpreadPercent, u8"UclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->UclkSpreadFreq, u8"UclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->FclkSpreadEnabled, u8"FclkSpreadEnabled",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"on or off"))
	),
	(bios->FclkSpreadPercent, u8"FclkSpreadPercent",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Q4.4"))
	),
	(bios->FclkSpreadFreq, u8"FclkSpreadFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"kHz"))
	),

	(bios->I2cControllers, u8"I2cControllers", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"%s",
				(ATUI_NAN, ATUI_PETIOLE, i2ccontrollerconfig_u8),
				(ATUI_NODESCR)
			),
			NULL, // deferred start
			I2C_CONTROLLER_NAME_COUNT_SMU11_PPT7, // count
			I2cControllerName_SMU_11_0_7_e // enum
		)), (ATUI_NODESCR)
	),

	(bios->GpioI2cScl, u8"GpioI2cScl",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Serial Clock"))
	),
	(bios->GpioI2cSda, u8"GpioI2cSda",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Serial Data"))
	),
	(bios->spare5, u8"spare5",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, atombios_firmware_capability_v3, atui_nullstruct,
	(bios->firmware_capability, u8"firmware_capability",
		(ATUI_HEX, ATUI_BITFIELD, (
			(u8"FIRMWARE_POSTED",         0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GPU_VIRTUALIZATION",      1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved0",               5,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"WMI_SUPPORT",             6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"HWEMU_ENABLE",            7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"HWEMU_UMC_CFG",           8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SRAM_ECC",                9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ENABLE_2STAGE_BIST_TRAINING", 10,10, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved1",              14,11, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ENABLE_2ND_USB20PORT",   15,15, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved2",              16,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DYNAMIC_BOOT_CFG_ENABLE",17,17, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved3",              31,18, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v3_1, atomtree_firmware_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->firmware_revision, u8"firmware_revision",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_sclk_in10khz, u8"bootup_sclk_in10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mclk_in10khz, u8"bootup_mclk_in10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->firmware_capability, u8"firmware_capability",
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability_v3),
		(ATUI_NODESCR)
	),
	(bios->main_call_parser_entry, u8"main_call_parser_entry",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"direct address of main parser call in VBIOS binary."))
	),
	(bios->bios_scratch_reg_startaddr, u8"bios_scratch_reg_startaddr",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"1st bios scratch register dword address"))
	),
	(bios->bootup_vddc_mv, u8"bootup_vddc_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vddci_mv, u8"bootup_vddci_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvddc_mv, u8"bootup_mvddc_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vddgfx_mv, u8"bootup_vddgfx_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem_module_id, u8"mem_module_id",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->coolingsolution_id, u8"coolingsolution_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"0: Air cooling; 1: Liquid cooling ..."))
	),
	(bios->reserved1, u8"reserved1",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->mc_baseaddr_high, u8"mc_baseaddr_high",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_baseaddr_low, u8"mc_baseaddr_low",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved2, u8"reserved2",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v3_2, atomtree_firmware_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->firmware_revision, u8"firmware_revision",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_sclk_in10khz, u8"bootup_sclk_in10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mclk_in10khz, u8"bootup_mclk_in10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->firmware_capability, u8"firmware_capability",
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability_v3),
		(ATUI_NODESCR)
	),
	(bios->main_call_parser_entry, u8"main_call_parser_entry",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"direct address of main parser call in VBIOS binary."))
	),
	(bios->bios_scratch_reg_startaddr, u8"bios_scratch_reg_startaddr",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"1st bios scratch register dword address"))
	),
	(bios->bootup_vddc_mv, u8"bootup_vddc_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vddci_mv, u8"bootup_vddci_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvddc_mv, u8"bootup_mvddc_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vddgfx_mv, u8"bootup_vddgfx_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem_module_id, u8"mem_module_id",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->coolingsolution_id, u8"coolingsolution_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"0: Air cooling; 1: Liquid cooling ..."))
	),
	(bios->reserved1, u8"reserved1",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->mc_baseaddr_high, u8"mc_baseaddr_high",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_baseaddr_low, u8"mc_baseaddr_low",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->board_i2c_feature_id, u8"board_i2c_feature_id",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"enum of atom_board_i2c_feature_id_def"))
	),
	(bios->board_i2c_feature_gpio_id, u8"board_i2c_feature_gpio_id",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"i2c id find in gpio_lut data table gpio_id"))
	),
	(bios->board_i2c_feature_slave_addr, u8"board_i2c_feature_slave_addr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved3, u8"reserved3",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvddq_mv, u8"bootup_mvddq_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvpp_mv, u8"bootup_mvpp_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->zfbstartaddrin16mb, u8"zfbstartaddrin16mb",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved2, u8"reserved2",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v3_3, atomtree_firmware_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->firmware_revision, u8"firmware_revision",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_sclk_in10khz, u8"bootup_sclk_in10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mclk_in10khz, u8"bootup_mclk_in10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->firmware_capability, u8"firmware_capability",
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability_v3),
		(ATUI_NODESCR)
	),
	(bios->main_call_parser_entry, u8"main_call_parser_entry",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"direct address of main parser call in VBIOS binary."))
	),
	(bios->bios_scratch_reg_startaddr, u8"bios_scratch_reg_startaddr",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"1st bios scratch register dword address"))
	),
	(bios->bootup_vddc_mv, u8"bootup_vddc_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vddci_mv, u8"bootup_vddci_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvddc_mv, u8"bootup_mvddc_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vddgfx_mv, u8"bootup_vddgfx_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem_module_id, u8"mem_module_id",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->coolingsolution_id, u8"coolingsolution_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"0: Air cooling; 1: Liquid cooling ..."))
	),
	(bios->reserved1, u8"reserved1",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->mc_baseaddr_high, u8"mc_baseaddr_high",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_baseaddr_low, u8"mc_baseaddr_low",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->board_i2c_feature_id, u8"board_i2c_feature_id",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"enum of atom_board_i2c_feature_id_def"))
	),
	(bios->board_i2c_feature_gpio_id, u8"board_i2c_feature_gpio_id",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"i2c id find in gpio_lut data table gpio_id"))
	),
	(bios->board_i2c_feature_slave_addr, u8"board_i2c_feature_slave_addr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved3, u8"reserved3",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvddq_mv, u8"bootup_mvddq_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvpp_mv, u8"bootup_mvpp_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->zfbstartaddrin16mb, u8"zfbstartaddrin16mb",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pplib_pptable_id, u8"pplib_pptable_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"if pplib_pptable_id!=0, pplib get powerplay table inside driver instead of from VBIOS"))
	),
	(bios->reserved2, u8"reserved2",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v3_4, atomtree_firmware_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->firmware_revision, u8"firmware_revision",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_sclk_in10khz, u8"bootup_sclk_in10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mclk_in10khz, u8"bootup_mclk_in10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->firmware_capability, u8"firmware_capability",
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability_v3),
		(ATUI_NODESCR)
	),
	(bios->main_call_parser_entry, u8"main_call_parser_entry",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"direct address of main parser call in VBIOS binary."))
	),
	(bios->bios_scratch_reg_startaddr, u8"bios_scratch_reg_startaddr",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"1st bios scratch register dword address"))
	),
	(bios->bootup_vddc_mv, u8"bootup_vddc_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vddci_mv, u8"bootup_vddci_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvddc_mv, u8"bootup_mvddc_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vddgfx_mv, u8"bootup_vddgfx_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem_module_id, u8"mem_module_id",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->coolingsolution_id, u8"coolingsolution_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"0: Air cooling; 1: Liquid cooling ... */"))
	),
	(bios->reserved1, u8"reserved1",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->mc_baseaddr_high, u8"mc_baseaddr_high",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_baseaddr_low, u8"mc_baseaddr_low",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->board_i2c_feature_id, u8"board_i2c_feature_id",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"enum of atom_board_i2c_feature_id_def"))
	),
	(bios->board_i2c_feature_gpio_id, u8"board_i2c_feature_gpio_id",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"i2c id find in gpio_lut data table gpio_id"))
	),
	(bios->board_i2c_feature_slave_addr, u8"board_i2c_feature_slave_addr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ras_rom_i2c_slave_addr, u8"ras_rom_i2c_slave_addr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvddq_mv, u8"bootup_mvddq_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mvpp_mv, u8"bootup_mvpp_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->zfbstartaddrin16mb, u8"zfbstartaddrin16mb",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pplib_pptable_id, u8"pplib_pptable_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"if pplib_pptable_id!=0, pplib get powerplay table inside driver instead of from VBIOS"))
	),
	(bios->mvdd_ratio, u8"mvdd_ratio",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mvdd_raio = (real mvdd in power rail)*1000/(mvdd_output_from_svi2)"))
	),
	(bios->hw_bootup_vddgfx_mv, u8"hw_bootup_vddgfx_mv",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"hw default vddgfx voltage level decide by board strap"))
	),
	(bios->hw_bootup_vddc_mv, u8"hw_bootup_vddc_mv",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"hw default vddc voltage level decide by board strap"))
	),
	(bios->hw_bootup_mvddc_mv, u8"hw_bootup_mvddc_mv",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"hw default mvddc voltage level decide by board strap"))
	),
	(bios->hw_bootup_vddci_mv, u8"hw_bootup_vddci_mv",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"hw default vddci voltage level decide by board strap"))
	),
	(bios->maco_pwrlimit_mw, u8"maco_pwrlimit_mw",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"bomaco mode power limit in unit of m-watt"))
	),
	(bios->usb_pwrlimit_mw, u8"usb_pwrlimit_mw",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"power limit when USB is enable in unit of m-watt"))
	),
	(bios->fw_reserved_size_in_kb, u8"fw_reserved_size_in_kb",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"VBIOS reserved extra fw size in unit of kb."))
	),
	(bios->pspbl_init_done_reg_addr, u8"pspbl_init_done_reg_addr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pspbl_init_done_value, u8"pspbl_init_done_value",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pspbl_init_done_check_timeout, u8"pspbl_init_done_check_timeout",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"time out in unit of us when polling pspbl init done"))
	),
	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)





PPATUI_FUNCIFY(union, atom_dtd_format_modemiscinfo, atomtree_lcd_info,
	(bios->miscinfo, u8"miscinfo",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"HORIZONTAL_CUTOFF",0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"HSYNC_POLARITY",    1,1, ATUI_DEC,
				((LANG_ENG, u8"0=Active High, 1=Active Low"))
			),
			(u8"VSYNC_POLARITY",    2,2, ATUI_DEC,
				((LANG_ENG, u8"0=Active High, 1=Active Low"))
			),
			(u8"VERTICAL_CUTOFF",   3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"H_REPLICATIONBY2",  4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"V_REPLICATIONBY2",  5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"COMPOSITESYNC",     6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"INTERLACE",         7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DOUBLECLOCK",       8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"RGB888",            9,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved",         15,10, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_dtd_format, atomtree_lcd_info,
	(bios->pixclk, u8"pixclk",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->h_active, u8"h_active",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->h_blanking_time, u8"h_blanking_time",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->v_active, u8"v_active",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->v_blanking_time, u8"v_blanking_time",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->h_sync_offset, u8"h_sync_offset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->h_sync_width, u8"h_sync_width",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->v_sync_offset, u8"v_sync_offset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->v_syncwidth, u8"v_syncwidth",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->image_h_size, u8"image_h_size",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->image_v_size, u8"image_v_size",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->h_border, u8"h_border",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->v_border, u8"v_border",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->miscinfo, u8"miscinfo",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_dtd_format_modemiscinfo),
		(ATUI_NODESCR)
	),
	(bios->atom_mode_id, u8"atom_mode_id",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->refreshrate, u8"refreshrate",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(struct, atom_lcd_info_v2_1, atomtree_lcd_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
		(bios->lcd_timing, u8"lcd_timing",
		(ATUI_NAN, ATUI_PETIOLE, atom_dtd_format),
		(ATUI_NODESCR)
	),
	(bios->backlight_pwm, u8"backlight_pwm",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->special_handle_cap, u8"special_handle_cap",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->panel_misc, u8"panel_misc",
		(ATUI_DEC, ATUI_ENUM, atom_lcd_info_panel_misc), (ATUI_NODESCR)
	),
	(bios->lvds_max_slink_pclk, u8"lvds_max_slink_pclk",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->lvds_ss_percentage, u8"lvds_ss_percentage",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->lvds_ss_rate_10hz, u8"lvds_ss_rate_10hz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pwr_on_digon_to_de, u8"pwr_on_digon_to_de",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"all pwr sequence numbers below are in uint of 4ms"))
	),
	(bios->pwr_on_de_to_vary_bl, u8"pwr_on_de_to_vary_bl",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pwr_down_vary_bloff_to_de, u8"pwr_down_vary_bloff_to_de",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pwr_down_de_to_digoff, u8"pwr_down_de_to_digoff",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pwr_off_delay, u8"pwr_off_delay",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pwr_on_vary_bl_to_blon, u8"pwr_on_vary_bl_to_blon",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pwr_down_bloff_to_vary_bloff, u8"pwr_down_bloff_to_vary_bloff",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->panel_bpc, u8"panel_bpc",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dpcd_edp_config_cap, u8"dpcd_edp_config_cap",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dpcd_max_link_rate, u8"dpcd_max_link_rate",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dpcd_max_lane_count, u8"dpcd_max_lane_count",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dpcd_max_downspread, u8"dpcd_max_downspread",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->min_allowed_bl_level, u8"min_allowed_bl_level",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_allowed_bl_level, u8"max_allowed_bl_level",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_bl_level, u8"bootup_bl_level",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dplvdsrxid, u8"dplvdsrxid",
		(ATUI_DEC, ATUI_ENUM, atom_lcd_info_dptolvds_rx_id),
		((LANG_ENG, u8"eDP->LVDS translator chip. non-common like Realtek might require AMD SW init"))
	),
	(bios->reserved1, u8"reserved1",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)





PPATUI_FUNCIFY(struct, atom_smu_info_v3_1, atomtree_smu_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->smuip_min_ver, u8"smuip_min_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smuip_max_ver, u8"smuip_max_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smu_rsd1, u8"smu_rsd1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpuclk_ss_mode, u8"gpuclk_ss_mode",
		(ATUI_DEC, ATUI_ENUM, atom_spread_spectrum_mode),
		(ATUI_NODESCR)
	),
	(bios->sclk_ss_percentage, u8"sclk_ss_percentage",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sclk_ss_rate_10hz, u8"sclk_ss_rate_10hz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpuclk_ss_percentage, u8"gpuclk_ss_percentage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in unit of 0.001%"))
	),
	(bios->gpuclk_ss_rate_10hz, u8"gpuclk_ss_rate_10hz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->core_refclk_10khz, u8"core_refclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ac_dc_gpio_bit, u8"ac_dc_gpio_bit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO bit shift in SMU_GPIOPAD_A  configured for AC/DC switching, =0xff means invalid"))
	),
	(bios->ac_dc_polarity, u8"ac_dc_polarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for AC/DC switching"))
	),
	(bios->vr0hot_gpio_bit, u8"vr0hot_gpio_bit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO bit shift in SMU_GPIOPAD_A  configured for VR0 HOT event, =0xff means invalid"))
	),
	(bios->vr0hot_polarity, u8"vr0hot_polarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR0 HOT event"))
	),
	(bios->vr1hot_gpio_bit, u8"vr1hot_gpio_bit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO bit shift in SMU_GPIOPAD_A configured for VR1 HOT event , =0xff means invalid"))
	),
	(bios->vr1hot_polarity, u8"vr1hot_polarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR1 HOT event"))
	),
	(bios->fw_ctf_gpio_bit, u8"fw_ctf_gpio_bit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO bit shift in SMU_GPIOPAD_A configured for CTF, =0xff means invalid"))
	),
	(bios->fw_ctf_polarity, u8"fw_ctf_polarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for CTF"))
	)
)

PPATUI_FUNCIFY(struct, atom_smu_info_v3_2, atomtree_smu_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->smuip_min_ver, u8"smuip_min_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smuip_max_ver, u8"smuip_max_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smu_rsd1, u8"smu_rsd1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpuclk_ss_mode, u8"gpuclk_ss_mode",
		(ATUI_DEC, ATUI_ENUM, atom_spread_spectrum_mode),
		(ATUI_NODESCR)
	),
	(bios->sclk_ss_percentage, u8"sclk_ss_percentage",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sclk_ss_rate_10hz, u8"sclk_ss_rate_10hz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpuclk_ss_percentage, u8"gpuclk_ss_percentage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in unit of 0.001%"))
	),
	(bios->gpuclk_ss_rate_10hz, u8"gpuclk_ss_rate_10hz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->core_refclk_10khz, u8"core_refclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ac_dc_gpio_bit, u8"ac_dc_gpio_bit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO bit shift in SMU_GPIOPAD_A  configured for AC/DC switching, =0xff means invalid"))
	),
	(bios->ac_dc_polarity, u8"ac_dc_polarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for AC/DC switching"))
	),
	(bios->vr0hot_gpio_bit, u8"vr0hot_gpio_bit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO bit shift in SMU_GPIOPAD_A  configured for VR0 HOT event, =0xff means invalid"))
	),
	(bios->vr0hot_polarity, u8"vr0hot_polarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR0 HOT event"))
	),
	(bios->vr1hot_gpio_bit, u8"vr1hot_gpio_bit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO bit shift in SMU_GPIOPAD_A configured for VR1 HOT event , =0xff means invalid"))
	),
	(bios->vr1hot_polarity, u8"vr1hot_polarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR1 HOT event"))
	),
	(bios->fw_ctf_gpio_bit, u8"fw_ctf_gpio_bit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO bit shift in SMU_GPIOPAD_A configured for CTF, =0xff means invalid"))
	),
	(bios->fw_ctf_polarity, u8"fw_ctf_polarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for CTF"))
	),
	(bios->pcc_gpio_bit, u8"pcc_gpio_bit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO bit shift in SMU_GPIOPAD_A configured for PCC, =0xff means invalid"))
	),
	(bios->pcc_gpio_polarity, u8"pcc_gpio_polarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for CTF"))
	),
	(bios->smugoldenoffset, u8"smugoldenoffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpupll_vco_freq_10khz, u8"gpupll_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_smnclk_10khz, u8"bootup_smnclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_socclk_10khz, u8"bootup_socclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mp0clk_10khz, u8"bootup_mp0clk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mp1clk_10khz, u8"bootup_mp1clk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_lclk_10khz, u8"bootup_lclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_dcefclk_10khz, u8"bootup_dcefclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ctf_threshold_override_value, u8"ctf_threshold_override_value",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_smu_info_v3_3, atomtree_smu_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->smuip_min_ver, u8"smuip_min_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smuip_max_ver, u8"smuip_max_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->waflclk_ss_mode, u8"waflclk_ss_mode",
		(ATUI_DEC, ATUI_ENUM, atom_spread_spectrum_mode),
		(ATUI_NODESCR)
	),
	(bios->gpuclk_ss_mode, u8"gpuclk_ss_mode",
		(ATUI_DEC, ATUI_ENUM, atom_spread_spectrum_mode),
		(ATUI_NODESCR)
	),
	(bios->sclk_ss_percentage, u8"sclk_ss_percentage",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sclk_ss_rate_10hz, u8"sclk_ss_rate_10hz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpuclk_ss_percentage, u8"gpuclk_ss_percentage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in unit of 0.001%"))
	),
	(bios->gpuclk_ss_rate_10hz, u8"gpuclk_ss_rate_10hz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->core_refclk_10khz, u8"core_refclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ac_dc_gpio_bit, u8"ac_dc_gpio_bit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO bit shift in SMU_GPIOPAD_A  configured for AC/DC switching, =0xff means invalid"))
	),
	(bios->ac_dc_polarity, u8"ac_dc_polarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for AC/DC switching"))
	),
	(bios->vr0hot_gpio_bit, u8"vr0hot_gpio_bit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO bit shift in SMU_GPIOPAD_A  configured for VR0 HOT event, =0xff means invalid"))
	),
	(bios->vr0hot_polarity, u8"vr0hot_polarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR0 HOT event"))
	),
	(bios->vr1hot_gpio_bit, u8"vr1hot_gpio_bit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO bit shift in SMU_GPIOPAD_A configured for VR1 HOT event , =0xff means invalid"))
	),
	(bios->vr1hot_polarity, u8"vr1hot_polarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for VR1 HOT event"))
	),
	(bios->fw_ctf_gpio_bit, u8"fw_ctf_gpio_bit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO bit shift in SMU_GPIOPAD_A configured for CTF, =0xff means invalid"))
	),
	(bios->fw_ctf_polarity, u8"fw_ctf_polarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for CTF"))
	),
	(bios->pcc_gpio_bit, u8"pcc_gpio_bit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO bit shift in SMU_GPIOPAD_A configured for PCC, =0xff means invalid"))
	),
	(bios->pcc_gpio_polarity, u8"pcc_gpio_polarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for CTF"))
	),
	(bios->smugoldenoffset, u8"smugoldenoffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpupll_vco_freq_10khz, u8"gpupll_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_smnclk_10khz, u8"bootup_smnclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_socclk_10khz, u8"bootup_socclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mp0clk_10khz, u8"bootup_mp0clk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mp1clk_10khz, u8"bootup_mp1clk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_lclk_10khz, u8"bootup_lclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_dcefclk_10khz, u8"bootup_dcefclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ctf_threshold_override_value, u8"ctf_threshold_override_value",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->syspll3_0_vco_freq_10khz, u8"syspll3_0_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->syspll3_1_vco_freq_10khz, u8"syspll3_1_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_fclk_10khz, u8"bootup_fclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_waflclk_10khz, u8"bootup_waflclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smu_info_caps, u8"smu_info_caps",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->waflclk_ss_percentage, u8"waflclk_ss_percentage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in unit of 0.001%"))
	),
	(bios->smuinitoffset, u8"smuinitoffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, u8"reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_smu_info_v3_5, atomtree_smu_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->smuip_min_ver, u8"smuip_min_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smuip_max_ver, u8"smuip_max_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->waflclk_ss_mode, u8"waflclk_ss_mode",
		(ATUI_DEC, ATUI_ENUM, atom_spread_spectrum_mode),
		(ATUI_NODESCR)
	),
	(bios->gpuclk_ss_mode, u8"gpuclk_ss_mode",
		(ATUI_DEC, ATUI_ENUM, atom_spread_spectrum_mode),
		(ATUI_NODESCR)
	),
	(bios->sclk_ss_percentage, u8"sclk_ss_percentage",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sclk_ss_rate_10hz, u8"sclk_ss_rate_10hz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpuclk_ss_percentage, u8"gpuclk_ss_percentage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in unit of 0.001%"))
	),
	(bios->gpuclk_ss_rate_10hz, u8"gpuclk_ss_rate_10hz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->core_refclk_10khz, u8"core_refclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->syspll0_1_vco_freq_10khz, u8"syspll0_1_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->syspll0_2_vco_freq_10khz, u8"syspll0_2_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pcc_gpio_bit, u8"pcc_gpio_bit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO bit shift in SMU_GPIOPAD_A configured for PCC, =0xff means invalid"))
	),
	(bios->pcc_gpio_polarity, u8"pcc_gpio_polarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for CTF"))
	),
	(bios->smugoldenoffset, u8"smugoldenoffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->syspll0_0_vco_freq_10khz, u8"syspll0_0_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_smnclk_10khz, u8"bootup_smnclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_socclk_10khz, u8"bootup_socclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mp0clk_10khz, u8"bootup_mp0clk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mp1clk_10khz, u8"bootup_mp1clk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_lclk_10khz, u8"bootup_lclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_dcefclk_10khz, u8"bootup_dcefclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ctf_threshold_override_value, u8"ctf_threshold_override_value",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->syspll3_0_vco_freq_10khz, u8"syspll3_0_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->syspll3_1_vco_freq_10khz, u8"syspll3_1_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_fclk_10khz, u8"bootup_fclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_waflclk_10khz, u8"bootup_waflclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smu_info_caps, u8"smu_info_caps",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->waflclk_ss_percentage, u8"waflclk_ss_percentage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in unit of 0.001%"))
	),
	(bios->smuinitoffset, u8"smuinitoffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_dprefclk_10khz, u8"bootup_dprefclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_usbclk_10khz, u8"bootup_usbclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smb_slave_address, u8"smb_slave_address",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_fdo_ctrl0_val, u8"cg_fdo_ctrl0_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_fdo_ctrl1_val, u8"cg_fdo_ctrl1_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_fdo_ctrl2_val, u8"cg_fdo_ctrl2_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gdfll_as_wait_ctrl_val, u8"gdfll_as_wait_ctrl_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gdfll_as_step_ctrl_val, u8"gdfll_as_step_ctrl_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_dtbclk_10khz, u8"bootup_dtbclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fclk_syspll_refclk_10khz, u8"fclk_syspll_refclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svc0_val, u8"smusvi_svc0_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svc1_val, u8"smusvi_svc1_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svd0_val, u8"smusvi_svd0_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svd1_val, u8"smusvi_svd1_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svt0_val, u8"smusvi_svt0_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svt1_val, u8"smusvi_svt1_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_tach_ctrl_val, u8"cg_tach_ctrl_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_pump_ctrl1_val, u8"cg_pump_ctrl1_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_pump_tach_ctrl_val, u8"cg_pump_tach_ctrl_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->thm_ctf_delay_val, u8"thm_ctf_delay_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->thm_thermal_int_ctrl_val, u8"thm_thermal_int_ctrl_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->thm_tmon_config_val, u8"thm_tmon_config_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_smu_info_v3_6, atomtree_smu_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->smuip_min_ver, u8"smuip_min_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smuip_max_ver, u8"smuip_max_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->waflclk_ss_mode, u8"waflclk_ss_mode",
		(ATUI_DEC, ATUI_ENUM, atom_spread_spectrum_mode),
		(ATUI_NODESCR)
	),
	(bios->gpuclk_ss_mode, u8"gpuclk_ss_mode",
		(ATUI_DEC, ATUI_ENUM, atom_spread_spectrum_mode),
		(ATUI_NODESCR)
	),
	(bios->sclk_ss_percentage, u8"sclk_ss_percentage",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sclk_ss_rate_10hz, u8"sclk_ss_rate_10hz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpuclk_ss_percentage, u8"gpuclk_ss_percentage",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpuclk_ss_rate_10hz, u8"gpuclk_ss_rate_10hz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->core_refclk_10khz, u8"core_refclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->syspll0_1_vco_freq_10khz, u8"syspll0_1_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->syspll0_2_vco_freq_10khz, u8"syspll0_2_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pcc_gpio_bit, u8"pcc_gpio_bit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO bit shift in SMU_GPIOPAD_A configured for PCC, =0xff means invalid"))
	),
	(bios->pcc_gpio_polarity, u8"pcc_gpio_polarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for CTF"))
	),
	(bios->smugoldenoffset, u8"smugoldenoffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->syspll0_0_vco_freq_10khz, u8"syspll0_0_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_smnclk_10khz, u8"bootup_smnclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_socclk_10khz, u8"bootup_socclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mp0clk_10khz, u8"bootup_mp0clk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mp1clk_10khz, u8"bootup_mp1clk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_lclk_10khz, u8"bootup_lclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_dxioclk_10khz, u8"bootup_dxioclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ctf_threshold_override_value, u8"ctf_threshold_override_value",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->syspll3_0_vco_freq_10khz, u8"syspll3_0_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->syspll3_1_vco_freq_10khz, u8"syspll3_1_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_fclk_10khz, u8"bootup_fclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_waflclk_10khz, u8"bootup_waflclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smu_info_caps, u8"smu_info_caps",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->waflclk_ss_percentage, u8"waflclk_ss_percentage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in unit of 0.001%"))
	),
	(bios->smuinitoffset, u8"smuinitoffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_gfxavsclk_10khz, u8"bootup_gfxavsclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mpioclk_10khz, u8"bootup_mpioclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smb_slave_address, u8"smb_slave_address",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_fdo_ctrl0_val, u8"cg_fdo_ctrl0_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_fdo_ctrl1_val, u8"cg_fdo_ctrl1_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_fdo_ctrl2_val, u8"cg_fdo_ctrl2_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gdfll_as_wait_ctrl_val, u8"gdfll_as_wait_ctrl_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gdfll_as_step_ctrl_val, u8"gdfll_as_step_ctrl_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved_clk, u8"reserved_clk",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fclk_syspll_refclk_10khz, u8"fclk_syspll_refclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svc0_val, u8"smusvi_svc0_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svc1_val, u8"smusvi_svc1_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svd0_val, u8"smusvi_svd0_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svd1_val, u8"smusvi_svd1_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svt0_val, u8"smusvi_svt0_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svt1_val, u8"smusvi_svt1_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_tach_ctrl_val, u8"cg_tach_ctrl_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_pump_ctrl1_val, u8"cg_pump_ctrl1_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_pump_tach_ctrl_val, u8"cg_pump_tach_ctrl_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->thm_ctf_delay_val, u8"thm_ctf_delay_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->thm_thermal_int_ctrl_val, u8"thm_thermal_int_ctrl_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->thm_tmon_config_val, u8"thm_tmon_config_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vclk_10khz, u8"bootup_vclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_dclk_10khz, u8"bootup_dclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smu_gpiopad_pu_en_val, u8"smu_gpiopad_pu_en_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smu_gpiopad_pd_en_val, u8"smu_gpiopad_pd_en_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_smu_info_v4_0, atomtree_smu_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->bootup_gfxclk_bypass_10khz, u8"bootup_gfxclk_bypass_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_usrclk_10khz, u8"bootup_usrclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_csrclk_10khz, u8"bootup_csrclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->core_refclk_10khz, u8"core_refclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->syspll1_vco_freq_10khz, u8"syspll1_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->syspll2_vco_freq_10khz, u8"syspll2_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pcc_gpio_bit, u8"pcc_gpio_bit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO bit shift in SMU_GPIOPAD_A configured for PCC, =0xff means invalid"))
	),
	(bios->pcc_gpio_polarity, u8"pcc_gpio_polarity",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO polarity for CTF"))
	),
	(bios->bootup_vddusr_mv, u8"bootup_vddusr_mv",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->syspll0_vco_freq_10khz, u8"syspll0_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_smnclk_10khz, u8"bootup_smnclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_socclk_10khz, u8"bootup_socclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mp0clk_10khz, u8"bootup_mp0clk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mp1clk_10khz, u8"bootup_mp1clk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_lclk_10khz, u8"bootup_lclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_dcefclk_10khz, u8"bootup_dcefclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ctf_threshold_override_value, u8"ctf_threshold_override_value",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->syspll3_vco_freq_10khz, u8"syspll3_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mm_syspll_vco_freq_10khz, u8"mm_syspll_vco_freq_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_fclk_10khz, u8"bootup_fclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_waflclk_10khz, u8"bootup_waflclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smu_info_caps, u8"smu_info_caps",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->waflclk_ss_percentage, u8"waflclk_ss_percentage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"in unit of 0.001%"))
	),
	(bios->smuinitoffset, u8"smuinitoffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_dprefclk_10khz, u8"bootup_dprefclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_usbclk_10khz, u8"bootup_usbclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smb_slave_address, u8"smb_slave_address",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_fdo_ctrl0_val, u8"cg_fdo_ctrl0_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_fdo_ctrl1_val, u8"cg_fdo_ctrl1_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_fdo_ctrl2_val, u8"cg_fdo_ctrl2_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gdfll_as_wait_ctrl_val, u8"gdfll_as_wait_ctrl_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gdfll_as_step_ctrl_val, u8"gdfll_as_step_ctrl_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_dtbclk_10khz, u8"bootup_dtbclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->fclk_syspll_refclk_10khz, u8"fclk_syspll_refclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svc0_val, u8"smusvi_svc0_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svc1_val, u8"smusvi_svc1_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svd0_val, u8"smusvi_svd0_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svd1_val, u8"smusvi_svd1_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svt0_val, u8"smusvi_svt0_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smusvi_svt1_val, u8"smusvi_svt1_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_tach_ctrl_val, u8"cg_tach_ctrl_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_pump_ctrl1_val, u8"cg_pump_ctrl1_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cg_pump_tach_ctrl_val, u8"cg_pump_tach_ctrl_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->thm_ctf_delay_val, u8"thm_ctf_delay_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->thm_thermal_int_ctrl_val, u8"thm_thermal_int_ctrl_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->thm_tmon_config_val, u8"thm_tmon_config_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smbus_timing_cntrl0_val, u8"smbus_timing_cntrl0_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smbus_timing_cntrl1_val, u8"smbus_timing_cntrl1_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->smbus_timing_cntrl2_val, u8"smbus_timing_cntrl2_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->pwr_disp_timer_global_control_val, u8"pwr_disp_timer_global_control_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_mpioclk_10khz, u8"bootup_mpioclk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_dclk0_10khz, u8"bootup_dclk0_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vclk0_10khz, u8"bootup_vclk0_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_dclk1_10khz, u8"bootup_dclk1_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_vclk1_10khz, u8"bootup_vclk1_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_baco400clk_10khz, u8"bootup_baco400clk_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_baco1200clk_bypass_10khz, u8"bootup_baco1200clk_bypass_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->bootup_baco700clk_bypass_10khz, u8"bootup_baco700clk_bypass_10khz",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(struct, vram_usagebyfirmware_v2_1,
		atomtree_vram_usagebyfirmware,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->start_address_in_kb, u8"start_address_in_kb",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->used_by_firmware_in_kb, u8"used_by_firmware_in_kb",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->used_by_driver_in_kb, u8"used_by_driver_in_kb",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, vram_usagebyfirmware_v2_2,
		atomtree_vram_usagebyfirmware,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->fw_region_start_address_in_kb, u8"fw_region_start_address_in_kb",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->used_by_firmware_in_kb, u8"used_by_firmware_in_kb",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, u8"reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->driver_region0_start_address_in_kb, u8"driver_region0_start_address_in_kb",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->used_by_driver_region0_in_kb, u8"used_by_driver_region0_in_kb",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved32, u8"reserved32",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, atom_i2c_id_config, atui_nullstruct,
	(bios->i2c_id, u8"i2c_id",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"i2c_line_mux", 3,0, ATUI_DEC,
				((LANG_ENG, u8"A Mux number when it's HW assisted I2C or GPIO ID when it's SW I2C"))
			),
			(u8"hw_engine_id", 6,4, ATUI_DEC,
				((LANG_ENG, u8"=1 HW engine for NON multimedia use; =2 HW engine for Multimedia use; 3-7 Reserved for future I2C engines"))
			),
			(u8"hw_capable",   7,7, ATUI_DEC,
				((LANG_ENG, u8"=0 SW assisted I2C ID; =1 HW assisted I2C ID(HW line selection)"))
			)
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, atom_gpioi2c_pin_id, atomtree_gpio_pin_lut,
	(bios->gpio_id, u8"gpio_id",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"i2c_line_mux", 3,0, ATUI_DEC,
				((LANG_ENG, u8"A Mux number when it's HW assisted I2C or GPIO ID when it's SW I2C"))
			),
			(u8"hw_engine_id", 6,4, ATUI_DEC,
				((LANG_ENG, u8"=1 HW engine for NON multimedia use; =2 HW engine for Multimedia use; 3-7 Reserved for future I2C engines"))
			),
			(u8"hw_capable",   7,7, ATUI_DEC,
				((LANG_ENG, u8"only when the I2C_HW_CAP is set, the pin ID is assigned to an I2C pin pair, otherwise, it's an generic GPIO pin"))
			)
			(u8"GPIO_PINID", 6,0, ATUI_DEC, ((LANG_ENG, u8"enum of atom_gpio_pin_assignment_gpio_id")))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_gpio_pin_assignment_v2_1, atomtree_gpio_pin_lut,
	(bios->data_a_reg_index, u8"data_a_reg_index",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpio_bitshift, u8"gpio_bitshift",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpio_mask_bitshift, u8"gpio_mask_bitshift",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpio_id, u8"gpio_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_gpioi2c_pin_id),
		(ATUI_NODESCR)
	),
	(bios->reserved, u8"reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_gpio_pin_lut_v2_1, atomtree_gpio_pin_lut,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),

	(bios->gpio_pin, u8"gpio_pin", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(bios->gpio_pin, u8"gpio_pin [%02u]",
				(ATUI_NAN, ATUI_PETIOLE, atom_gpio_pin_assignment_v2_1),
				(ATUI_NODESCR)
			),
			NULL, atomtree->num_gpio_pins, // deferred start, count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, atom_gfx_info_v2_2, atomtree_gfx_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->gfxip_min_ver, u8"gfxip_min_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxip_max_ver, u8"gfxip_max_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_shader_engines, u8"max_shader_engines",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_tile_pipes, u8"max_tile_pipes",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_cu_per_sh, u8"max_cu_per_sh",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_sh_per_se, u8"max_sh_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_backends_per_se, u8"max_backends_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_texture_channel_caches, u8"max_texture_channel_caches",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr, u8"regaddr_cp_dma_src_addr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr_hi, u8"regaddr_cp_dma_src_addr_hi",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr, u8"regaddr_cp_dma_dst_addr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr_hi, u8"regaddr_cp_dma_dst_addr_hi",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_command, u8"regaddr_cp_dma_command",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_status, u8"regaddr_cp_status",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_rlc_gpu_clock_32, u8"regaddr_rlc_gpu_clock_32",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->rlc_gpu_timer_refclk, u8"rlc_gpu_timer_refclk",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_gfx_info_v2_3, atomtree_gfx_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->gfxip_min_ver, u8"gfxip_min_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxip_max_ver, u8"gfxip_max_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_shader_engines, u8"max_shader_engines",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_tile_pipes, u8"max_tile_pipes",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_cu_per_sh, u8"max_cu_per_sh",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_sh_per_se, u8"max_sh_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_backends_per_se, u8"max_backends_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_texture_channel_caches, u8"max_texture_channel_caches",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr, u8"regaddr_cp_dma_src_addr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr_hi, u8"regaddr_cp_dma_src_addr_hi",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr, u8"regaddr_cp_dma_dst_addr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr_hi, u8"regaddr_cp_dma_dst_addr_hi",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_command, u8"regaddr_cp_dma_command",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_status, u8"regaddr_cp_status",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_rlc_gpu_clock_32, u8"regaddr_rlc_gpu_clock_32",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->rlc_gpu_timer_refclk, u8"rlc_gpu_timer_refclk",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_cu_per_sh, u8"active_cu_per_sh",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_rb_per_se, u8"active_rb_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gcgoldenoffset, u8"gcgoldenoffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->rm21_sram_vmin_value, u8"rm21_sram_vmin_value",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_gfx_info_v2_4, atomtree_gfx_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->gfxip_min_ver, u8"gfxip_min_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxip_max_ver, u8"gfxip_max_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_shader_engines, u8"max_shader_engines",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, u8"reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_cu_per_sh, u8"max_cu_per_sh",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_sh_per_se, u8"max_sh_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_backends_per_se, u8"max_backends_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_texture_channel_caches, u8"max_texture_channel_caches",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr, u8"regaddr_cp_dma_src_addr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr_hi, u8"regaddr_cp_dma_src_addr_hi",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr, u8"regaddr_cp_dma_dst_addr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr_hi, u8"regaddr_cp_dma_dst_addr_hi",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_command, u8"regaddr_cp_dma_command",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_status, u8"regaddr_cp_status",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_rlc_gpu_clock_32, u8"regaddr_rlc_gpu_clock_32",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->rlc_gpu_timer_refclk, u8"rlc_gpu_timer_refclk",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_cu_per_sh, u8"active_cu_per_sh",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_rb_per_se, u8"active_rb_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gcgoldenoffset, u8"gcgoldenoffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_num_gprs, u8"gc_num_gprs",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_gsprim_buff_depth, u8"gc_gsprim_buff_depth",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_parameter_cache_depth, u8"gc_parameter_cache_depth",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_wave_size, u8"gc_wave_size",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_max_waves_per_simd, u8"gc_max_waves_per_simd",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_lds_size, u8"gc_lds_size",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_num_max_gs_thds, u8"gc_num_max_gs_thds",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_gs_table_depth, u8"gc_gs_table_depth",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_double_offchip_lds_buffer, u8"gc_double_offchip_lds_buffer",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_max_scratch_slots_per_cu, u8"gc_max_scratch_slots_per_cu",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sram_rm_fuses_val, u8"sram_rm_fuses_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sram_custom_rm_fuses_val, u8"sram_custom_rm_fuses_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_gfx_info_v2_5, atomtree_gfx_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->gfxip_min_ver, u8"gfxip_min_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxip_max_ver, u8"gfxip_max_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_shader_engines, u8"max_shader_engines",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, u8"reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_cu_per_sh, u8"max_cu_per_sh",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_sh_per_se, u8"max_sh_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_backends_per_se, u8"max_backends_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_texture_channel_caches, u8"max_texture_channel_caches",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr, u8"regaddr_cp_dma_src_addr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr_hi, u8"regaddr_cp_dma_src_addr_hi",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr, u8"regaddr_cp_dma_dst_addr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr_hi, u8"regaddr_cp_dma_dst_addr_hi",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_command, u8"regaddr_cp_dma_command",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_status, u8"regaddr_cp_status",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_rlc_gpu_clock_32, u8"regaddr_rlc_gpu_clock_32",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->rlc_gpu_timer_refclk, u8"rlc_gpu_timer_refclk",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_cu_per_sh, u8"active_cu_per_sh",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_rb_per_se, u8"active_rb_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gcgoldenoffset, u8"gcgoldenoffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_num_gprs, u8"gc_num_gprs",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_gsprim_buff_depth, u8"gc_gsprim_buff_depth",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_parameter_cache_depth, u8"gc_parameter_cache_depth",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_wave_size, u8"gc_wave_size",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_max_waves_per_simd, u8"gc_max_waves_per_simd",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_lds_size, u8"gc_lds_size",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_num_max_gs_thds, u8"gc_num_max_gs_thds",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_gs_table_depth, u8"gc_gs_table_depth",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_double_offchip_lds_buffer, u8"gc_double_offchip_lds_buffer",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_max_scratch_slots_per_cu, u8"gc_max_scratch_slots_per_cu",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sram_rm_fuses_val, u8"sram_rm_fuses_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sram_custom_rm_fuses_val, u8"sram_custom_rm_fuses_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cut_cu, u8"cut_cu",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_cu_total, u8"active_cu_total",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cu_reserved, u8"cu_reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->gc_config, u8"gc_config",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->inactive_cu_per_se, u8"inactive_cu_per_se",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_gfx_info_v2_7, atomtree_gfx_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->gfxip_min_ver, u8"gfxip_min_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxip_max_ver, u8"gfxip_max_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_shader_engines, u8"max_shader_engines",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, u8"reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_cu_per_sh, u8"max_cu_per_sh",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_sh_per_se, u8"max_sh_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_backends_per_se, u8"max_backends_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_texture_channel_caches, u8"max_texture_channel_caches",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr, u8"regaddr_cp_dma_src_addr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_src_addr_hi, u8"regaddr_cp_dma_src_addr_hi",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr, u8"regaddr_cp_dma_dst_addr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_dst_addr_hi, u8"regaddr_cp_dma_dst_addr_hi",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_dma_command, u8"regaddr_cp_dma_command",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_cp_status, u8"regaddr_cp_status",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_rlc_gpu_clock_32, u8"regaddr_rlc_gpu_clock_32",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->rlc_gpu_timer_refclk, u8"rlc_gpu_timer_refclk",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_cu_per_sh, u8"active_cu_per_sh",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_rb_per_se, u8"active_rb_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gcgoldenoffset, u8"gcgoldenoffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_num_gprs, u8"gc_num_gprs",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_gsprim_buff_depth, u8"gc_gsprim_buff_depth",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_parameter_cache_depth, u8"gc_parameter_cache_depth",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_wave_size, u8"gc_wave_size",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_max_waves_per_simd, u8"gc_max_waves_per_simd",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_lds_size, u8"gc_lds_size",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_num_max_gs_thds, u8"gc_num_max_gs_thds",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_gs_table_depth, u8"gc_gs_table_depth",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_double_offchip_lds_buffer, u8"gc_double_offchip_lds_buffer",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_max_scratch_slots_per_cu, u8"gc_max_scratch_slots_per_cu",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sram_rm_fuses_val, u8"sram_rm_fuses_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sram_custom_rm_fuses_val, u8"sram_custom_rm_fuses_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cut_cu, u8"cut_cu",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_cu_total, u8"active_cu_total",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->cu_reserved, u8"cu_reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->gc_config, u8"gc_config",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->inactive_cu_per_se, u8"inactive_cu_per_se",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->reserved2, u8"reserved2",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(struct, atom_gfx_info_v3_0, atomtree_gfx_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->gfxip_min_ver, u8"gfxip_min_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gfxip_max_ver, u8"gfxip_max_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_shader_engines, u8"max_shader_engines",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_tile_pipes, u8"max_tile_pipes",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_cu_per_sh, u8"max_cu_per_sh",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_sh_per_se, u8"max_sh_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_backends_per_se, u8"max_backends_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->max_texture_channel_caches, u8"max_texture_channel_caches",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_lsdma_queue0_rb_rptr, u8"regaddr_lsdma_queue0_rb_rptr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_lsdma_queue0_rb_rptr_hi, u8"regaddr_lsdma_queue0_rb_rptr_hi",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_lsdma_queue0_rb_wptr, u8"regaddr_lsdma_queue0_rb_wptr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_lsdma_queue0_rb_wptr_hi, u8"regaddr_lsdma_queue0_rb_wptr_hi",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_lsdma_command, u8"regaddr_lsdma_command",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_lsdma_status, u8"regaddr_lsdma_status",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->regaddr_golden_tsc_count_lower, u8"regaddr_golden_tsc_count_lower",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->golden_tsc_count_lower_refclk, u8"golden_tsc_count_lower_refclk",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_wgp_per_se, u8"active_wgp_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_rb_per_se, u8"active_rb_per_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->active_se, u8"active_se",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved1, u8"reserved1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sram_rm_fuses_val, u8"sram_rm_fuses_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->sram_custom_rm_fuses_val, u8"sram_custom_rm_fuses_val",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->inactive_sa_mask, u8"inactive_sa_mask",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gc_config, u8"gc_config",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->inactive_wgp, u8"inactive_wgp",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->inactive_rb, u8"inactive_rb",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->gdfll_as_wait_ctrl_val, u8"gdfll_as_wait_ctrl_val",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gdfll_as_step_ctrl_val, u8"gdfll_as_step_ctrl_val",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, dphy_bitremap0, atui_nullstruct,
	(bios->raw_data, u8"dphy_bitremap",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"bit0",     3,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"bit1",     7,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"bit2",     11,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"bit3",    15,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"bit4",    19,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"bit5",    23,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"bit6",    27,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"bit7",    31,28, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, dphy_byteremap0, atui_nullstruct,
	(bios->raw_data, u8"dphy_byteremap",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"byte0",     3,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"byte1",     7,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"byte2",     11,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"byte3",    15,12, ATUI_DEC, (ATUI_NODESCR)),
			(u8"byte4",    19,16, ATUI_DEC, (ATUI_NODESCR)),
			(u8"byte5",    23,20, ATUI_DEC, (ATUI_NODESCR)),
			(u8"byte6",    27,24, ATUI_DEC, (ATUI_NODESCR)),
			(u8"byte7",    31,28, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_gddr6_bit_byte_remap, atui_nullstruct,
	(bios->dphy_byteremap, u8"dphy_byteremap",
		(ATUI_NAN, ATUI_INLINE, dphy_byteremap0),
		(ATUI_NODESCR)
	),
	(bios->dphy_bitremap0, u8"dphy_bitremap0",
		(ATUI_NAN, ATUI_INLINE, dphy_bitremap0),
		(ATUI_NODESCR)
	),
	(bios->dphy_bitremap1, u8"dphy_bitremap1",
		(ATUI_NAN, ATUI_INLINE, dphy_bitremap0),
		(ATUI_NODESCR)
	),
	(bios->dphy_bitremap2, u8"dphy_bitremap2",
		(ATUI_NAN, ATUI_INLINE, dphy_bitremap0),
		(ATUI_NODESCR)
	),
	(bios->aphy_bitremap0, u8"aphy_bitremap0",
		(ATUI_NAN, ATUI_INLINE, dphy_bitremap0),
		(ATUI_NODESCR)
	),
	(bios->aphy_bitremap1, u8"aphy_bitremap1",
		(ATUI_NAN, ATUI_INLINE, dphy_bitremap0),
		(ATUI_NODESCR)
	),
	(bios->phy_dram, u8"phy_dram",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"mmUMC_PHY_DRAM"))
	)
)
PPATUI_FUNCIFY(struct, atom_gddr6_dram_data_remap, atui_nullstruct,
	(bios->table_size, u8"table_size",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->phyintf_ck_inverted, u8"phyintf_ck_inverted",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"UMC_PHY_PHYINTF_CNTL.INV_CK"))
	),
	(bios->bit_byte_remap, u8"atom_gddr6_bit_byte_remap", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"bit_byte_remap [%02u]",
				(ATUI_NAN, ATUI_INLINE, atom_gddr6_bit_byte_remap),
				(ATUI_NODESCR)
			),
			NULL, // deferred start
			((bios->table_size - offsetof(typeof(*bios), bit_byte_remap))
				/ sizeof(struct atom_gddr6_bit_byte_remap)
			), // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, memory_vendor_id, atui_nullstruct,
	(bios->memory_vendor_id, u8"memory_vendor_id",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"vendor_code", 3,0, ATUI_HEX,
				((LANG_ENG, u8"GDDR vendor ID"))
			),
			(u8"revision",    7,4, ATUI_HEX, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, atom_umc_register_addr_info_access,
		atomtree_umc_init_reg_block,
	// the uint32_t* typecast is about stripping the 'union' abstraction so that
	// the preprocessor can correctly calculate the bitfield
	(((uint32_t*)atomtree->register_info), u8"umc_reg_list", // start, name
		(ATUI_NODISPLAY, ATUI_DYNARRAY, (
			// Leaf pattern:
			(ATUI_NULL, u8"umc_reg_addr [%02u]",
				(ATUI_HEX, ATUI_BITFIELD, (
					(u8"umc_register_addr", 23, 0, ATUI_HEX, (ATUI_NODESCR)),
					(u8"umc_reg_type_ind",  24,24, ATUI_DEC, (ATUI_NODESCR)),
					(u8"umc_reg_rsvd",      31,25, ATUI_BIN, (ATUI_NODESCR))
				)), (ATUI_NODESCR)
			),
			NULL, // deferred start
			atomtree->num_info, // count
			ATUI_NULL // enum
		)),
		(ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(union, atom_mc_register_setting_id, atui_nullstruct,
	(bios->id_access, u8"id_access",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"mem_clock_range", 23, 0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"mem_block_id",    31,24, ATUI_DEC, (ATUI_NODESCR))
		)),
		(ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_umc_reg_setting_data_block,
		atomtree_umc_init_reg_block,
	(bios->block_id, u8"UMC block ID",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->umc_reg_data, u8"umc_reg_data",
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"umc_reg_data [%02u]",
				(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, atomtree->num_data_entries, // deferred start. count
			ATUI_NULL // enum
		)),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, umc_reg_settings_dummy, atomtree_umc_init_reg_block,
	(ATUI_NULL, u8"umc_reg_setting_list", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"umc_reg_setting_list [%02u]",
				(ATUI_NAN, ATUI_PETIOLE, atom_umc_reg_setting_data_block),
				(ATUI_NODESCR)
			),
			atomtree->data_blocks, // deferred start
			atomtree->num_data_blocks, // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_umc_init_reg_block,
		atomtree_umc_init_reg_block,
	(bios->umc_reg_num, u8"umc_reg_num",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, u8"reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	// data for umc_reg_list, umc_reg_setting_list are through atomtree
	(ATUI_NULL, u8"umc_reg_list",
		(ATUI_NAN, ATUI_PETIOLE, atom_umc_register_addr_info_access),
		(ATUI_NODESCR)
	),
	(ATUI_NULL, u8"umc_reg_setting_list",
		(ATUI_NAN, ATUI_PETIOLE, umc_reg_settings_dummy),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_vram_module_v9, atui_nullstruct,
	(bios->memory_size, u8"memory_size",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Total memory size in unit of MB for CONFIG_MEMSIZE zeros"))
	),
	(bios->channel_enable, u8"channel_enable",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"bit vector, each bit indicate specific channel enable or not"))
	),
	(bios->max_mem_clk, u8"max_mem_clk",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"max memory clock of this memory in unit of 10kHz, =0 means it is not defined"))
	),
	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->mem_voltage, u8"mem_voltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mem_voltage"))
	),
	(bios->vram_module_size, u8"vram_module_size",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Size of atom_vram_module_v9"))
	),
	(bios->ext_memory_id, u8"ext_memory_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Current memory module ID"))
	),
	(bios->memory_type, u8"memory_type",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		((LANG_ENG, u8"enum of atom_dgpu_vram_type"))
	),
	(bios->channel_num, u8"channel_num",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of mem. channels supported in this module"))
	),
	(bios->channel_width, u8"channel_width",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT"))
	),
	(bios->density, u8"density",
		(ATUI_HEX, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->tunningset_id, u8"tunningset_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"MC phy registers set per."))
	),
	(bios->vendor_rev_id, u8"vendor_rev_id",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->refreshrate, u8"refreshrate",
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, u8"[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(bios->hbm_ven_rev_id, u8"hbm_ven_rev_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"hbm_ven_rev_id"))
	),
	(bios->vram_rsd2, u8"vram_rsd2",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"reserved"))
	),
	(bios->dram_pnstring, u8"dram_pnstring",
		(ATUI_NAN, ATUI_STRING),
		((LANG_ENG, u8"part number end with '0'."))
	)
)
PPATUI_FUNCIFY(struct, atom_vram_info_header_v2_3, atui_nullstruct,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->mem_adjust_tbloffset, u8"mem_adjust_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of atom_umc_init_reg_block structure for memory vendor specific UMC adjust setting"))
	),
	(bios->mem_clk_patch_tbloffset, u8"mem_clk_patch_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of atom_umc_init_reg_block structure for memory clock specific UMC setting"))
	),
	(bios->mc_adjust_pertile_tbloffset, u8"mc_adjust_pertile_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of atom_umc_init_reg_block structure for Per Byte Offset Preset Settings"))
	),
	(bios->mc_phyinit_tbloffset, u8"mc_phyinit_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of atom_umc_init_reg_block structure for MC phy init set"))
	),
	(bios->dram_data_remap_tbloffset, u8"dram_data_remap_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"reserved for now"))
	),
	(bios->tmrs_seq_offset, u8"tmrs_seq_offset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of HBM tmrs"))
	),
	(bios->post_ucode_init_offset, u8"post_ucode_init_offset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of atom_umc_init_reg_block structure for MC phy init after MC uCode complete umc init"))
	),
	(bios->vram_rsd2, u8"vram_rsd2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vram_module_num, u8"vram_module_num",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"indicate number of VRAM module"))
	),
	(bios->umcip_min_ver, u8"umcip_min_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->umcip_max_ver, u8"umcip_max_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_phy_tile_num, u8"mc_phy_tile_num",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"indicate the MCD tile number which use in DramDataRemapTbl and usMcAdjustPerTileTblOffset"))
	)
)


PPATUI_FUNCIFY(struct, atom_vram_module_v10, atomtree_vram_info_header_v2_4,
	(bios->memory_size, u8"memory_size",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Total memory size in unit of MB for CONFIG_MEMSIZE zeros"))
	),
	(bios->channel_enable, u8"channel_enable",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"bit vector, each bit indicate specific channel enable or not"))
	),
	(bios->max_mem_clk, u8"max_mem_clk",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"max memory clock of this memory in unit of 10kHz, =0 means it is not defined"))
	),
	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->mem_voltage, u8"mem_voltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mem_voltage"))
	),
	(bios->vram_module_size, u8"vram_module_size",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Size of atom_vram_module_v9"))
	),
	(bios->ext_memory_id, u8"ext_memory_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Current memory module ID"))
	),
	(bios->memory_type, u8"memory_type",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		((LANG_ENG, u8"enum of atom_dgpu_vram_type"))
	),
	(bios->channel_num, u8"channel_num",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of mem. channels supported in this module"))
	),
	(bios->channel_width, u8"channel_width",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT"))
	),
	(bios->density, u8"density",
		(ATUI_HEX, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->tunningset_id, u8"tunningset_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"MC phy registers set per"))
	),
	(bios->vendor_rev_id, u8"vendor_rev_id",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->refreshrate, u8"refreshrate",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(bios->vram_flags, u8"vram_flags",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"bit0= bankgroup enable"))
	),
	(bios->vram_rsd2, u8"vram_rsd2",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"reserved"))
	),
	(bios->gddr6_mr10, u8"gddr6_mr10",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr10),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr1, u8"gddr6_mr1",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr1),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr2, u8"gddr6_mr2",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr2),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr7, u8"gddr6_mr7",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr7),
		(ATUI_NODESCR)
	),
	(bios->dram_pnstring, u8"dram_pnstring",
		(ATUI_NAN, ATUI_STRING),
		((LANG_ENG, u8"part number end with '0'."))
	)
)
PPATUI_FUNCIFY(struct, atom_vram_info_header_v2_4,
		atomtree_vram_info_header_v2_4,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->mem_adjust_tbloffset, u8"mem_adjust_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of atom_umc_init_reg_block structure for memory vendor specific UMC adjust setting"))
	),
	(bios->mem_clk_patch_tbloffset, u8"mem_clk_patch_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of atom_umc_init_reg_block structure for memory clock specific UMC setting"))
	),
	(bios->mc_adjust_pertile_tbloffset, u8"mc_adjust_pertile_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of atom_umc_init_reg_block structure for Per Byte Offset Preset Settings"))
	),
	(bios->mc_phyinit_tbloffset, u8"mc_phyinit_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of atom_umc_init_reg_block structure for MC phy init set"))
	),
	(bios->dram_data_remap_tbloffset, u8"dram_data_remap_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"reserved for now"))
	),
	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of reserved"))
	),
	(bios->post_ucode_init_offset, u8"post_ucode_init_offset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of atom_umc_init_reg_block structure for MC phy init after MC uCode complete umc init"))
	),
	(bios->vram_rsd2, u8"vram_rsd2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vram_module_num, u8"vram_module_num",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"indicate number of VRAM module"))
	),
	(bios->umcip_min_ver, u8"umcip_min_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->umcip_max_ver, u8"umcip_max_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_phy_tile_num, u8"mc_phy_tile_num",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"indicate the MCD tile number which use in DramDataRemapTbl and usMcAdjustPerTileTblOffset"))
	)
)


PPATUI_FUNCIFY(struct, atom_vram_module_v11,
		atomtree_vram_info_header_v2_5,

	(bios->memory_size, u8"memory_size",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Total memory size in unit of MB for CONFIG_MEMSIZE zeros"))
	),
	(bios->channel_enable, u8"channel_enable",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"bit vector, each bit indicate specific channel enable or not"))
	),
	(bios->mem_voltage, u8"mem_voltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"mem_voltage"))
	),
	(bios->vram_module_size, u8"vram_module_size",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Size of atom_vram_module_v9"))
	),
	(bios->ext_memory_id, u8"ext_memory_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Current memory module ID"))
	),
	(bios->memory_type, u8"memory_type",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		((LANG_ENG, u8"enum of atom_dgpu_vram_type"))
	),
	(bios->channel_num, u8"channel_num",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of mem. channels supported in this module"))
	),
	(bios->channel_width, u8"channel_width",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT"))
	),
	(bios->density, u8"density",
		(ATUI_HEX, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->tunningset_id, u8"tunningset_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"MC phy registers set per."))
	),
	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"reserved"))
	),
	(bios->vendor_rev_id, u8"vendor_rev_id",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->refreshrate, u8"refreshrate",
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, u8"[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(bios->vram_flags, u8"vram_flags",
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, u8"bit0= bankgroup enable"))
	),
	(bios->vram_rsd2, u8"vram_rsd2",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"reserved"))
	),

	(bios->gddr6_mr10, u8"gddr6_mr10",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr10),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr0, u8"gddr6_mr0",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr0),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr1, u8"gddr6_mr1",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr1),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr2, u8"gddr6_mr2",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr2),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr4, u8"gddr6_mr4",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr4),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr7, u8"gddr6_mr7",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr7),
		(ATUI_NODESCR)
	),
	(bios->gddr6_mr8, u8"gddr6_mr8",
		(ATUI_NODISPLAY, ATUI_INLINE, gddr6_mr8),
		(ATUI_NODESCR)
	),

	(bios->dram_pnstring, u8"dram_pnstring",
		(ATUI_NAN, ATUI_STRING),
		((LANG_ENG, u8"part number end with '0'."))
	)
)
PPATUI_FUNCIFY(struct, atom_gddr6_ac_timing_v2_5,
		atomtree_vram_info_header_v2_5,
	(bios->block_id, u8"block_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->RL, u8"RL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->WL, u8"WL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRAS, u8"tRAS",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRC, u8"tRC",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tREFI, u8"tREFI",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRFC, u8"tRFC",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRFCpb, u8"tRFCpb",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tRREFD, u8"tRREFD",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRCDRD, u8"tRCDRD",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRCDWR, u8"tRCDWR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRP, u8"tRP",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tRRDS, u8"tRRDS",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRRDL, u8"tRRDL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWR, u8"tWR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWTRS, u8"tWTRS",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tWTRL, u8"tWTRL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tFAW, u8"tFAW",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCCDS, u8"tCCDS",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCCDL, u8"tCCDL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tCRCRL, u8"tCRCRL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCRCWL, u8"tCRCWL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCKE, u8"tCKE",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCKSRE, u8"tCKSRE",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tCKSRX, u8"tCKSRX",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRTPS, u8"tRTPS",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRTPL, u8"tRTPL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tMRD, u8"tMRD",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tMOD, u8"tMOD",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tXS, u8"tXS",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tXHP, u8"tXHP",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tXSMRS, u8"tXSMRS",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tXSH, u8"tXSH",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tPD, u8"tPD",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tXP, u8"tXP",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCPDED, u8"tCPDED",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tACTPDE, u8"tACTPDE",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tPREPDE, u8"tPREPDE",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tREFPDE, u8"tREFPDE",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tMRSPDEN, u8"tMRSPDEN",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRDSRE, u8"tRDSRE",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tWRSRE, u8"tWRSRE",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tPPD, u8"tPPD",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCCDMW, u8"tCCDMW",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWTRTR, u8"tWTRTR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),

	(bios->tLTLTR, u8"tLTLTR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tREFTR, u8"tREFTR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->VNDR, u8"VNDR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_vram_info_header_v2_5,
		atomtree_vram_info_header_v2_5,

	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->mem_adjust_tbloffset, u8"mem_adjust_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of atom_umc_init_reg_block structure for memory vendor specific UMC adjust settings"))
	),
	(bios->gddr6_ac_timing_offset, u8"gddr6_ac_timing_offset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of atom_gddr6_ac_timing_v2_5 structure for memory clock specific UMC settings"))
	),
	(bios->mc_adjust_pertile_tbloffset, u8"mc_adjust_pertile_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of atom_umc_init_reg_block structure for Per Byte Offset Preset Settings"))
	),
	(bios->mc_phyinit_tbloffset, u8"mc_phyinit_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of atom_umc_init_reg_block structure for MC phy init set"))
	),
	(bios->dram_data_remap_tbloffset, u8"dram_data_remap_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of atom_gddr6_dram_data_remap array to indicate DRAM data lane to GPU mapping"))
	),
	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of reserved"))
	),
	(bios->post_ucode_init_offset, u8"post_ucode_init_offset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of atom_umc_init_reg_block structure for MC phy init after MC uCode complete umc init"))
	),
	(bios->strobe_mode_patch_tbloffset, u8"strobe_mode_patch_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of atom_umc_init_reg_block structure for Strobe Mode memory clock specific UMC settings"))
	),
	(bios->vram_module_num, u8"vram_module_num",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"indicate number of VRAM module"))
	),
	(bios->umcip_min_ver, u8"umcip_min_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->umcip_max_ver, u8"umcip_max_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_phy_tile_num, u8"mc_phy_tile_num",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"indicate the MCD tile number which use in DramDataRemapTbl and usMcAdjustPerTileTblOffset"))
	)
)

PPATUI_FUNCIFY(struct, atom_vram_info_header_v2_6,
		atomtree_vram_info_header_v2_6,
	(bios->table_header, u8"table_header",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->mem_adjust_tbloffset, u8"mem_adjust_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem_clk_patch_tbloffset, u8"mem_clk_patch_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_adjust_pertile_tbloffset, u8"mc_adjust_pertile_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_phyinit_tbloffset, u8"mc_phyinit_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dram_data_remap_tbloffset, u8"dram_data_remap_tbloffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tmrs_seq_offset, u8"tmrs_seq_offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->post_ucode_init_offset, u8"post_ucode_init_offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vram_rsd2, u8"vram_rsd2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vram_module_num, u8"vram_module_num",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->umcip_min_ver, u8"umcip_min_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->umcip_max_ver, u8"umcip_max_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_phy_tile_num, u8"mc_phy_tile_num",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_vram_module_v3_0,
		atomtree_vram_info_header_v3_0,
	(bios->density, u8"density",
		(ATUI_HEX, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->tunningset_id, u8"tunningset_id",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ext_memory_id, u8"ext_memory_id",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dram_vendor_id, u8"dram_vendor_id",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->dram_info_offset, u8"dram_info_offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mem_tuning_offset, u8"mem_tuning_offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tmrs_seq_offset, u8"tmrs_seq_offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved1, u8"reserved1",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dram_size_per_ch, u8"dram_size_per_ch",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->dram_pnstring, u8"dram_pnstring",
		(ATUI_NAN, ATUI_STRING), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_vram_info_header_v3_0,
		atomtree_vram_info_header_v3_0,
	(bios->table_header, u8"table_header",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->mem_tuning_table_offset, u8"mem_tuning_table_offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dram_info_table_offset, u8"dram_info_table_offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tmrs_table_offset, u8"tmrs_table_offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_init_table_offset, u8"mc_init_table_offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->dram_data_remap_table_offset, u8"dram_data_remap_table_offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->umc_emuinit_table_offset, u8"umc_emuinit_table_offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved_sub_table_offset, u8"reserved_sub_table_offset",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->vram_module_num, u8"vram_module_num",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->umcip_min_ver, u8"umcip_min_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->umcip_max_ver, u8"umcip_max_ver",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->mc_phy_tile_num, u8"mc_phy_tile_num",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->memory_type, u8"memory_type",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type), (ATUI_NODESCR)
	),
	(bios->channel_num, u8"channel_num",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->channel_width, u8"channel_width",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved1, u8"reserved1",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->channel_enable, u8"channel_enable",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->channel1_enable, u8"channel1_enable",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->feature_enable, u8"feature_enable",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->feature1_enable, u8"feature1_enable",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->hardcode_mem_size, u8"hardcode_mem_size",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved4, u8"reserved4",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(struct, atom_voltage_object_header_v4, atui_nullstruct,
	(bios->voltage_type, u8"voltage_type",
		(ATUI_DEC, ATUI_ENUM, atom_voltage_type), (ATUI_NODESCR)
	),
	(bios->voltage_mode, u8"voltage_mode",
		(ATUI_DEC, ATUI_ENUM, atom_voltage_object_mode), (ATUI_NODESCR)
	),
	(bios->object_size, u8"object_size",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_voltage_gpio_map_lut, atomtree_voltage_object_v4,
	(bios->voltage_gpio_reg_val, u8"voltage_gpio_reg_val",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"The Voltage ID which is used to program GPIO register"))
	),
	(bios->voltage_level_mv, u8"voltage_level_mv",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"The corresponding Voltage Value, in mV"))
	)
)
PPATUI_FUNCIFY(struct, atom_gpio_voltage_object_v4, atomtree_voltage_object_v4,
	(bios->header, u8"header",
		(ATUI_NAN, ATUI_INLINE, atom_voltage_object_header_v4), (ATUI_NODESCR)
	),
	(bios->gpio_control_id, u8"gpio_control_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"default is 0 which indicate control through CG VID mode"))
	),
	(bios->gpio_entry_num, u8"gpio_entry_num",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"indiate the entry numbers of Votlage/Gpio value Look up table"))
	),
	(bios->phase_delay_us, u8"phase_delay_us",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"phase delay in unit of micro second"))
	),
	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->gpio_mask_val, u8"gpio_mask_val",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"GPIO Mask value"))
	),
	(bios->voltage_gpio_lut, u8"voltage_gpio_lut",
		(ATUI_NAN, ATUI_INLINE, atom_voltage_gpio_map_lut),
		(ATUI_NODESCR)
	)
	(bios->voltage_gpio_lut, u8"voltage_gpio_lut", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"voltage_gpio_lut [%u]",
				(ATUI_NODISPLAY, ATUI_INLINE, atom_voltage_gpio_map_lut),
				(ATUI_NODESCR)
			),
			NULL, atomtree->lut_entries, // deferred start, count
			ATUI_NULL // enum
		)),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct,  atom_i2c_data_entry, atomtree_voltage_object_v4,
	(bios->i2c_reg_index, u8"i2c_reg_index",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"i2c register address, can be up to 16bit"))
	),
	(bios->i2c_reg_data, u8"i2c_reg_data",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"i2c register data, can be up to 16bit"))
	)
)
PPATUI_FUNCIFY(struct, atom_i2c_voltage_object_v4, atomtree_voltage_object_v4,
	(bios->header, u8"header",
		(ATUI_NAN, ATUI_INLINE, atom_voltage_object_header_v4), (ATUI_NODESCR)
	),
	(bios->regulator_id, u8"regulator_id",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Indicate Voltage Regulator Id"))
	),
	(bios->i2c_id, u8"i2c_id",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_i2c_id_config),
		(ATUI_NODESCR)
	),
	(bios->i2c_slave_addr, u8"i2c_slave_addr",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->i2c_control_offset, u8"i2c_control_offset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->i2c_flag, u8"i2c_flag",
		(ATUI_BIN, ATUI_NOFANCY),
		((LANG_ENG, u8"Bit0: 0 - One byte data; 1 - Two byte data"))
	),
	(bios->i2c_speed, u8"i2c_speed",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"=0, use default i2c speed, otherwise use it in unit of kHz."))
	),
	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->i2cdatalut, u8"i2cdatalut", // start, name
		(ATUI_NODISPLAY, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"i2cdatalut [%u]",
				(ATUI_NAN, ATUI_INLINE, atom_i2c_data_entry),
				(ATUI_NODESCR)
			),
			NULL, atomtree->lut_entries, // deferred start, count
			ATUI_NULL // enum
		)),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_svid2_voltage_object_v4, atomtree_voltage_object_v4,
	(bios->header, u8"header",
		(ATUI_NAN, ATUI_INLINE, atom_voltage_object_header_v4), (ATUI_NODESCR)
	),
	(bios->loadline_psi1.loadline_psi1, u8"loadline_psi1",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"offset_trim",    1,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"loadline_slope", 4,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PSI1_L_enable",  5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved",       7,6, ATUI_HEX, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	),
	(bios->psi0_l_vid_thresd, u8"psi0_l_vid_thresd",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"VR PSI0_L VID threshold"))
	),
	(bios->psi0_enable, u8"psi0_enable",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->maxvstep, u8"maxvstep",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->telemetry_offset, u8"telemetry_offset",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->telemetry_gain, u8"telemetry_gain",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->reserved1, u8"reserved1",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_merged_voltage_object_v4, atui_nullstruct,
	(bios->header, u8"header",
		(ATUI_NAN, ATUI_INLINE, atom_voltage_object_header_v4), (ATUI_NODESCR)
	),
	(bios->merged_powerrail_type, u8"merged_powerrail_type",
		(ATUI_DEC, ATUI_ENUM, atom_voltage_type), (ATUI_NODESCR)
	),
	(bios->reserved, u8"reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)


