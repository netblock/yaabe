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



PPATUI_FUNCIFY(union, atombios_firmware_capability_v1, atomtree_firmware_info,
	(bios->FirmwareCapability, "FirmwareCapability",
		(ATUI_BIN, ATUI_BITFIELD, (
			("FirmwarePosted",         0,0, ATUI_DEC, (ATUI_NODESCR)),
			("DualCRTC_Support",       1,1, ATUI_DEC, (ATUI_NODESCR)),
			("ExtendedDesktopSupport", 2,2, ATUI_DEC, (ATUI_NODESCR)),
			("MemoryClockSS_Support",  3,3, ATUI_DEC, (ATUI_NODESCR)),
			("EngineClockSS_Support",  4,4, ATUI_DEC, (ATUI_NODESCR)),
			("GPUControlsBL",          5,5, ATUI_DEC, (ATUI_NODESCR)),
			("WMI_SUPPORT",            6,6, ATUI_DEC, (ATUI_NODESCR)),
			("PPMode_Assigned",        7,7, ATUI_DEC, (ATUI_NODESCR)),
			("HyperMemory_Support",    8,8, ATUI_DEC, (ATUI_NODESCR)),
			("HyperMemory_Size",      12,9, ATUI_DEC, (ATUI_NODESCR)),
			("PostWithoutModeSet",    13,13, ATUI_DEC, (ATUI_NODESCR)),
			("SCL2Redefined",         14,14, ATUI_DEC, (ATUI_NODESCR)),
			("Reserved",              15,15, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v1_0, atomtree_firmware_info,
	(bios->table_header, "table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->FirmwareRevision, "FirmwareRevision",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DefaultEngineClock, "DefaultEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->DefaultMemoryClock, "DefaultMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->DriverTargetEngineClock, "DriverTargetEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->DriverTargetMemoryClock, "DriverTargetMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Output, "MaxEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Output, "MaxMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Output, "MaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->ASICMaxEngineClock, "ASICMaxEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->ASICMaxMemoryClock, "ASICMaxMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->ASICMaxTemperature, "ASICMaxTemperature",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding, "Padding",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "Don't use them"))
	),
	(bios->aulReservedForBIOS, "aulReservedForBIOS",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "Don't use them"))
	),
	(bios->MinEngineClockPLL_Input, "MinEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Input, "MaxEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Output, "MinEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Input, "MinMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Input, "MaxMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Output, "MinMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxPixelClock, "MaxPixelClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit, Max.  Pclk"))
	),
	(bios->MinPixelClockPLL_Input, "MinPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Input, "MaxPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinPixelClockPLL_Output, "MinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit, the definitions above can't change!!!"))
	),
	(bios->FirmwareCapability, "FirmwareCapability",
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability_v1),
		(ATUI_NODESCR)
	),
	(bios->ReferenceClock, "ReferenceClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->PM_RTS_Location, "PM_RTS_Location",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "RTS PM4 starting location in ROM in 1Kb unit"))
	),
	(bios->PM_RTS_StreamSize, "PM_RTS_StreamSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "RTS PM4 packets in Kb unit"))
	),
	(bios->Design_ID, "Design_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Indicate what is the board design"))
	),
	(bios->MemoryModule_ID, "MemoryModule_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Indicate what is the board design"))
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v1_2, atomtree_firmware_info,
	(bios->table_header, "table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->FirmwareRevision, "FirmwareRevision",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DefaultEngineClock, "DefaultEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->DefaultMemoryClock, "DefaultMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->DriverTargetEngineClock, "DriverTargetEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->DriverTargetMemoryClock, "DriverTargetMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Output, "MaxEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Output, "MaxMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Output, "MaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->ASICMaxEngineClock, "ASICMaxEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->ASICMaxMemoryClock, "ASICMaxMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->ASICMaxTemperature, "ASICMaxTemperature",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MinAllowedBL_Level, "MinAllowedBL_Level",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding, "Padding",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "Don't use them"))
	),
	(bios->aulReservedForBIOS, "aulReservedForBIOS",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "Don't use them"))
	),
	(bios->MinPixelClockPLL_Output, "MinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Input, "MinEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Input, "MaxEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Output, "MinEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Input, "MinMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Input, "MaxMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Output, "MinMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxPixelClock, "MaxPixelClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit, Max.  Pclk"))
	),
	(bios->MinPixelClockPLL_Input, "MinPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Input, "MaxPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinPixelClockPLL_Output_lower, "MinPixelClockPLL_Output_lower",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit - lower 16bit of ulMinPixelClockPLL_Output"))
	),
	(bios->FirmwareCapability, "FirmwareCapability",
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability_v1),
		(ATUI_NODESCR)
	),
	(bios->ReferenceClock, "ReferenceClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->PM_RTS_Location, "PM_RTS_Location",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "RTS PM4 starting location in ROM in 1Kb unit"))
	),
	(bios->PM_RTS_StreamSize, "PM_RTS_StreamSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "RTS PM4 packets in Kb unit"))
	),
	(bios->Design_ID, "Design_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Indicate what is the board design"))
	),
	(bios->MemoryModule_ID, "MemoryModule_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Indicate what is the board design"))
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v1_3, atomtree_firmware_info,
	(bios->table_header, "table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->FirmwareRevision, "FirmwareRevision",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DefaultEngineClock, "DefaultEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->DefaultMemoryClock, "DefaultMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->DriverTargetEngineClock, "DriverTargetEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->DriverTargetMemoryClock, "DriverTargetMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Output, "MaxEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Output, "MaxMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Output, "MaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->ASICMaxEngineClock, "ASICMaxEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->ASICMaxMemoryClock, "ASICMaxMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->ASICMaxTemperature, "ASICMaxTemperature",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MinAllowedBL_Level, "MinAllowedBL_Level",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding, "Padding",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "Don't use them"))
	),
	(bios->aulReservedForBIOS, "aulReservedForBIOS",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Don't use them"))
	),
	(bios->_3DAccelerationEngineClock, "_3DAccelerationEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinPixelClockPLL_Output, "MinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Input, "MinEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Input, "MaxEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Output, "MinEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Input, "MinMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Input, "MaxMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Output, "MinMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxPixelClock, "MaxPixelClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit, Max.  Pclk"))
	),
	(bios->MinPixelClockPLL_Input, "MinPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Input, "MaxPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinPixelClockPLL_Output_lower, "MinPixelClockPLL_Output_lower",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit - lower 16bit of ulMinPixelClockPLL_Output"))
	),
	(bios->FirmwareCapability, "FirmwareCapability",
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability_v1),
		(ATUI_NODESCR)
	),
	(bios->ReferenceClock, "ReferenceClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->PM_RTS_Location, "PM_RTS_Location",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "RTS PM4 starting location in ROM in 1Kb unit"))
	),
	(bios->PM_RTS_StreamSize, "PM_RTS_StreamSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "RTS PM4 packets in Kb unit"))
	),
	(bios->Design_ID, "Design_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Indicate what is the board design"))
	),
	(bios->MemoryModule_ID, "MemoryModule_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Indicate what is the board design"))
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v1_4, atomtree_firmware_info,
	(bios->table_header, "table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->FirmwareRevision, "FirmwareRevision",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DefaultEngineClock, "DefaultEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->DefaultMemoryClock, "DefaultMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->DriverTargetEngineClock, "DriverTargetEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->DriverTargetMemoryClock, "DriverTargetMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Output, "MaxEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Output, "MaxMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Output, "MaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->ASICMaxEngineClock, "ASICMaxEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->ASICMaxMemoryClock, "ASICMaxMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->ASICMaxTemperature, "ASICMaxTemperature",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MinAllowedBL_Level, "MinAllowedBL_Level",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BootUpVDDCVoltage, "BootUpVDDCVoltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In MV unit"))
	),
	(bios->LcdMinPixelClockPLL_Output, "LcdMinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In MHz unit"))
	),
	(bios->LcdMaxPixelClockPLL_Output, "LcdMaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In MHz unit"))
	),
	(bios->_3DAccelerationEngineClock, "_3DAccelerationEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinPixelClockPLL_Output, "MinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Input, "MinEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Input, "MaxEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Output, "MinEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Input, "MinMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Input, "MaxMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Output, "MinMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxPixelClock, "MaxPixelClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit, Max.  Pclk"))
	),
	(bios->MinPixelClockPLL_Input, "MinPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Input, "MaxPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinPixelClockPLL_Output_lower, "MinPixelClockPLL_Output_lower",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit - lower 16bit of ulMinPixelClockPLL_Output"))
	),
	(bios->FirmwareCapability, "FirmwareCapability",
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability_v1),
		(ATUI_NODESCR)
	),
	(bios->ReferenceClock, "ReferenceClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->PM_RTS_Location, "PM_RTS_Location",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "RTS PM4 starting location in ROM in 1Kb unit"))
	),
	(bios->PM_RTS_StreamSize, "PM_RTS_StreamSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "RTS PM4 packets in Kb unit"))
	),
	(bios->Design_ID, "Design_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Indicate what is the board design"))
	),
	(bios->MemoryModule_ID, "MemoryModule_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Indicate what is the board design"))
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v2_1, atomtree_firmware_info,
	(bios->table_header, "table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->FirmwareRevision, "FirmwareRevision",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DefaultEngineClock, "DefaultEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->DefaultMemoryClock, "DefaultMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->Reserved1, "Reserved1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved2, "Reserved2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MaxEngineClockPLL_Output, "MaxEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Output, "MaxMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Output, "MaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->BinaryAlteredInfo, "BinaryAlteredInfo",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Was ulASICMaxEngineClock"))
	),
	(bios->DefaultDispEngineClkFreq, "DefaultDispEngineClkFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->Reserved3, "Reserved3",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Was ucASICMaxTemperature;"))
	),
	(bios->MinAllowedBL_Level, "MinAllowedBL_Level",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BootUpVDDCVoltage, "BootUpVDDCVoltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In MV unit"))
	),
	(bios->LcdMinPixelClockPLL_Output, "LcdMinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In MHz unit"))
	),
	(bios->LcdMaxPixelClockPLL_Output, "LcdMaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In MHz unit"))
	),
	(bios->Reserved4, "Reserved4",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Was ulAsicMaximumVoltage"))
	),
	(bios->MinPixelClockPLL_Output, "MinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Input, "MinEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Input, "MaxEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Output, "MinEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Input, "MinMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Input, "MaxMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Output, "MinMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxPixelClock, "MaxPixelClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit, Max.  Pclk"))
	),
	(bios->MinPixelClockPLL_Input, "MinPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Input, "MaxPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MinPixelClockPLL_Output_lower, "MinPixelClockPLL_Output_lower",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit - lower 16bit of ulMinPixelClockPLL_Output"))
	),
	(bios->FirmwareCapability, "FirmwareCapability",
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability_v1),
		(ATUI_NODESCR)
	),
	(bios->CoreReferenceClock, "CoreReferenceClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MemoryReferenceClock, "MemoryReferenceClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->UniphyDPModeExtClkFreq, "UniphyDPModeExtClkFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit, if it is 0, In DP Mode Uniphy Input clock from internal PPLL, otherwise Input clock from external Spread clock"))
	),
	(bios->MemoryModule_ID, "MemoryModule_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Indicate what is the board design"))
	),
	(bios->Reserved5, "Reserved5",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, product_branding_v2, atomtree_firmware_info,
	(bios->ProductBranding, "ProductBranding",
		(ATUI_BIN, ATUI_BITFIELD, (
			("EMBEDDED_CAP", 1,0, ATUI_DEC,
				((LANG_ENG, "Embedded feature level"))
			),
			("Reserved",     3,2, ATUI_DEC, ((LANG_ENG, "Reserved"))),
			("BRANDING_ID",  7,4, ATUI_DEC, ((LANG_ENG, "Branding ID")))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_firmware_info_v2_2, atomtree_firmware_info,
	(bios->table_header, "table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->FirmwareRevision, "FirmwareRevision",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DefaultEngineClock, "DefaultEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->DefaultMemoryClock, "DefaultMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->SPLL_OutputFreq, "SPLL_OutputFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->GPUPLL_OutputFreq, "GPUPLL_OutputFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->Reserved1, "Reserved1",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Was ulMaxEngineClockPLL_Output; //In 10Khz unit*"))
	),
	(bios->Reserved2, "Reserved2",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Was ulMaxMemoryClockPLL_Output; //In 10Khz unit*"))
	),
	(bios->MaxPixelClockPLL_Output, "MaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->BinaryAlteredInfo, "BinaryAlteredInfo",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Was ulASICMaxEngineClock  ?"))
	),
	(bios->DefaultDispEngineClkFreq, "DefaultDispEngineClkFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit. This is the frequency before DCDTO, corresponding to usBootUpVDDCVoltage."))
	),
	(bios->Reserved3, "Reserved3",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Was ucASICMaxTemperature;"))
	),
	(bios->MinAllowedBL_Level, "MinAllowedBL_Level",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BootUpVDDCVoltage, "BootUpVDDCVoltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In MV unit"))
	),
	(bios->LcdMinPixelClockPLL_Output, "LcdMinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In MHz unit"))
	),
	(bios->LcdMaxPixelClockPLL_Output, "LcdMaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In MHz unit"))
	),
	(bios->Reserved4, "Reserved4",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Was ulAsicMaximumVoltage"))
	),
	(bios->MinPixelClockPLL_Output, "MinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->RemoteDisplayConfig, "RemoteDisplayConfig",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0=disable 1=enable"))
	),
	(bios->Reserved5, "Reserved5",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "Was usMinEngineClockPLL_Input and usMaxEngineClockPLL_Input"))
	),
	(bios->Reserved6, "Reserved6",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Was usMinEngineClockPLL_Output and usMinMemoryClockPLL_Input"))
	),
	(bios->Reserved7, "Reserved7",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "Was usMaxMemoryClockPLL_Input and usMinMemoryClockPLL_Output"))
	),
	(bios->MaxPixelClock, "MaxPixelClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit, Max.  Pclk used only for DAC"))
	),
	(bios->MinPixelClockPLL_Input, "MinPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Input, "MaxPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->BootUpVDDCIVoltage, "BootUpVDDCIVoltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In unit of mv; Was usMinPixelClockPLL_Output;"))
	),
	(bios->FirmwareCapability, "FirmwareCapability",
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability_v1),
		(ATUI_NODESCR)
	),
	(bios->CoreReferenceClock, "CoreReferenceClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->MemoryReferenceClock, "MemoryReferenceClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit"))
	),
	(bios->UniphyDPModeExtClkFreq, "UniphyDPModeExtClkFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In 10Khz unit, if it is 0, In DP Mode Uniphy Input clock from internal PPLL, otherwise Input clock from external Spread clock"))
	),
	(bios->MemoryModule_ID, "MemoryModule_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Indicate what is the board design"))
	),
	(bios->CoolingSolution_ID, "CoolingSolution_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0: Air cooling; 1: Liquid cooling ... [COOLING_SOLUTION]"))
	),
	(bios->ProductBranding, "ProductBranding",
		(ATUI_NODISPLAY, ATUI_INLINE, product_branding_v2),
		(ATUI_NODESCR)
	),
	(bios->Reserved9, "Reserved9",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BootUpMVDDCVoltage, "BootUpMVDDCVoltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In unit of mv; Was usMinPixelClockPLL_Output;"))
	),
	(bios->BootUpVDDGFXVoltage, "BootUpVDDGFXVoltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In unit of mv;"))
	),
	(bios->Reserved10, "Reserved10",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "New added comparing to previous version"))
	)
)
