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

PPATUI_FUNCIFY(struct, atom_master_data_table_v1_1, atui_nullstruct,
	(bios->table_header, "table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->UtilityPipeLine, "UtilityPipeLine",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Offest for the utility to get parser info,Don't change this position!"))
	),
	(bios->MultimediaCapabilityInfo, "MultimediaCapabilityInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Only used by MM Lib,latest version 1.1, not configuable from Bios, need to include the table to build Bios"))
	),
	(bios->MultimediaConfigInfo, "MultimediaConfigInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Only used by MM Lib,latest version 2.1, not configuable from Bios, need to include the table to build Bios"))
	),
	(bios->StandardVESA_Timing, "StandardVESA_Timing",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Only used by Bios"))
	),
	(bios->FirmwareInfo, "FirmwareInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components,latest version 1.4"))
	),
	(bios->PaletteData, "PaletteData",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Only used by BIOS"))
	),
	(bios->LCD_Info, "LCD_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components,latest version 1.3, was called LVDS_Info"))
	),
	(bios->DIGTransmitterInfo, "DIGTransmitterInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Internal used by VBIOS only version 3.1"))
	),
	(bios->SMU_Info, "SMU_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components,latest version 1.1"))
	),
	(bios->SupportedDevicesInfo, "SupportedDevicesInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Will be obsolete from R600"))
	),
	(bios->GPIO_I2C_Info, "GPIO_I2C_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components,latest version 1.2 will be used from R600"))
	),
	(bios->VRAM_UsageByFirmware, "VRAM_UsageByFirmware",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components,latest version 1.3 will be used from R600"))
	),
	(bios->GPIO_Pin_LUT, "GPIO_Pin_LUT",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components,latest version 1.1"))
	),
	(bios->VESA_ToInternalModeLUT, "VESA_ToInternalModeLUT",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Only used by Bios"))
	),
	(bios->GFX_Info, "GFX_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components,latest version 2.1 will be used from R600"))
	),
	(bios->PowerPlayInfo, "PowerPlayInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components,latest version 2.1,new design from R600"))
	),
	(bios->GPUVirtualizationInfo, "GPUVirtualizationInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Will be obsolete from R600"))
	),
	(bios->SaveRestoreInfo, "SaveRestoreInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Only used by Bios"))
	),
	(bios->PPLL_SS_Info, "PPLL_SS_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components,latest version 1.2, used to call SS_Info, change to new name because of int ASIC SS info"))
	),
	(bios->OemInfo, "OemInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Defined and used by external SW, should be obsolete soon"))
	),
	(bios->XTMDS_Info, "XTMDS_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Will be obsolete from R600"))
	),
	(bios->MclkSS_Info, "MclkSS_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components,latest version 1.1, only enabled when ext SS chip is used"))
	),
	(bios->Object_Header, "Object_Header",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components,latest version 1.1"))
	),
	(bios->IndirectIOAccess, "IndirectIOAccess",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Only used by Bios,this table position can't change at all!!"))
	),
	(bios->MC_InitParameter, "MC_InitParameter",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Only used by command table"))
	),
	(bios->ASIC_VDDC_Info, "ASIC_VDDC_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Will be obsolete from R600"))
	),
	(bios->ASIC_InternalSS_Info, "ASIC_InternalSS_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "New tabel name from R600, used to be called \"ASIC_MVDDC_Info\""))
	),
	(bios->TV_VideoMode, "TV_VideoMode",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Only used by command table"))
	),
	(bios->VRAM_Info, "VRAM_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Only used by command table, latest version 1.3"))
	),
	(bios->MemoryTrainingInfo, "MemoryTrainingInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Used for VBIOS and Diag utility for memory training purpose since R600. the new table rev start from 2.1"))
	),
	(bios->IntegratedSystemInfo, "IntegratedSystemInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components"))
	),
	(bios->ASIC_ProfilingInfo, "ASIC_ProfilingInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "New table name from R600, used to be called \"ASIC_VDDCI_Info\" for pre-R600"))
	),
	(bios->VoltageObjectInfo, "VoltageObjectInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components, latest version 1.1"))
	),
	(bios->PowerSourceInfo, "PowerSourceInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Shared by various SW components, latest versoin 1.1"))
	),
	(bios->ServiceInfo, "ServiceInfo",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)
