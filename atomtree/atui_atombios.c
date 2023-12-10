#include "atomtree.h"
#include "atui.h"

PPATUI_FUNCIFY(struct, atom_rom_header_v1_1, atui_nullstruct,
	(bios->table_header, "table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->FirmWareSignature, "FirmWareSignature",
		(ATUI_NAN, ATUI_ARRAY),
		((LANG_ENG, "Signature to distinguish between Atombios and non-atombios, atombios should init it as \"ATOM\", don't change the position"))
	),
	(bios->BiosRuntimeSegmentAddress, "BiosRuntimeSegmentAddress",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ProtectedModeInfoOffset, "ProtectedModeInfoOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ConfigFilenameOffset, "ConfigFilenameOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->CRC_BlockOffset, "CRC_BlockOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BIOS_BootupMessageOffset, "BIOS_BootupMessageOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Int10Offset, "Int10Offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PciBusDevInitCode, "PciBusDevInitCode",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->IoBaseAddress, "IoBaseAddress",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SubsystemVendorID, "SubsystemVendorID",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SubsystemID, "SubsystemID",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PCI_InfoOffset, "PCI_InfoOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MasterCommandTableOffset, "MasterCommandTableOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Offest for SW to get all command table offsets, Don't change the position"))
	),
	(bios->MasterDataTableOffset, "MasterDataTableOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Offest for SW to get all data table offsets, Don't change the position"))
	),
	(bios->ExtendedFunctionCode, "ExtendedFunctionCode",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved, "Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_rom_header_v2_1, atui_nullstruct,
	(bios->table_header, "table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->FirmWareSignature, "FirmWareSignature",
		(ATUI_NAN, ATUI_ARRAY),
		((LANG_ENG, "Signature to distinguish between Atombios and non-atombios, atombios should init it as \"ATOM\", don't change the position"))
	),
	(bios->BiosRuntimeSegmentAddress, "BiosRuntimeSegmentAddress",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ProtectedModeInfoOffset, "ProtectedModeInfoOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ConfigFilenameOffset, "ConfigFilenameOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->CRC_BlockOffset, "CRC_BlockOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BIOS_BootupMessageOffset, "BIOS_BootupMessageOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Int10Offset, "Int10Offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PciBusDevInitCode, "PciBusDevInitCode",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->IoBaseAddress, "IoBaseAddress",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SubsystemVendorID, "SubsystemVendorID",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SubsystemID, "SubsystemID",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PCI_InfoOffset, "PCI_InfoOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MasterCommandTableOffset, "MasterCommandTableOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Offest for SW to get all command table offsets, Don't change the position"))
	),
	(bios->MasterDataTableOffset, "MasterDataTableOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Offest for SW to get all data table offsets, Don't change the position"))
	),
	(bios->ExtendedFunctionCode, "ExtendedFunctionCode",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved, "Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PSPDirTableOffset, "PSPDirTableOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)
