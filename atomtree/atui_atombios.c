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



PPATUI_FUNCIFY(union, memory_vendor_id, atui_nullstruct,
	(bios->MemoryVendorID, "MemoryVendorID",
		(ATUI_BIN, ATUI_BITFIELD, (
			("vendor_code", 3,0, ATUI_DEC,
				((LANG_ENG, "GDDR vendor ID"))
			),
			("revision",    7,4, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, vram_module_channel_config, atui_nullstruct,
	(bios->ChannelConfig, "ChannelConfig",
		(ATUI_BIN, ATUI_BITFIELD, (
			("channel_combo", 3,0, ATUI_DEC, (ATUI_NODESCR)),
			("channel_width", 7,4, ATUI_DEC,
				((LANG_ENG, "in number of 2"))
			)
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, npl_rtdelay, atui_nullstruct,
	(bios->NPL_RT, "NPL_RT",
		(ATUI_BIN, ATUI_BITFIELD, (
			("npl_round_trip",   3,0, ATUI_DEC,
				((LANG_ENG, "MC_SEQ_CAS_TIMING [28:24]:TCL=CL+NPL_RT-2). Always 2."))
			),
			("reserved",         5,4, ATUI_DEC, (ATUI_NODESCR)),
			("battery_odt_mask", 7,6, ATUI_DEC, (ATUI_NODESCR))
		)), ((LANG_ENG, "board dependent parameter:NPL round trip delay, used for calculate memory timing parameters"))
	)
)

PPATUI_FUNCIFY(union, mem_preamble, atui_nullstruct,
	(bios->Preamble, "Preamble",
		(ATUI_BIN, ATUI_BITFIELD, (
			("read",  3,0, ATUI_DEC, (ATUI_NODESCR)),
			("write", 7,4, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, vrammodule_misc, atui_nullstruct,
	(bios->Misc, "Misc",
		(ATUI_BIN, ATUI_BITFIELD, (
			("dual_rank",     0,0, ATUI_DEC,
				((LANG_ENG, "0=single rank; 1=dual"))
			),
			("Burstlength_8", 1,1, ATUI_DEC,
				((LANG_ENG, "0=BL4; 1=BL8"))
			),
			("reserved1",     4,2, ATUI_DEC, (ATUI_NODESCR)),
			("dual_cs",       5,5, ATUI_DEC, (ATUI_NODESCR)),
			("reserved2",     7,6, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, cdr_bandwidth, atui_nullstruct,
	(bios->CDR_Bandwidth, "CDR_Bandwidth",
		(ATUI_BIN, ATUI_BITFIELD, (
			("read_bandwidth",  3,0, ATUI_DEC, (ATUI_NODESCR)),
			("write_bandwidth", 7,4, ATUI_DEC, (ATUI_NODESCR))
		)), ((LANG_ENG, "clock and data recovery?"))
	)
)

PPATUI_FUNCIFY(union, bank_col_counts, atui_nullstruct,
	(bios->BankCol, "BankCol",
		(ATUI_BIN, ATUI_BITFIELD, (
			("num_columns", 1,0, ATUI_DEC,
				((LANG_ENG, "encoded; actual = 8+n bits"))
			),
			("num_banks",   3,2, ATUI_DEC,
				((LANG_ENG, "encoded; actual = 2**(n+2) banks"))
			)
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, atom_vram_module_v1, atomtree_vram_module,
	(bios->Reserved, "Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->EMRSValue, "EMRSValue",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MRSValue, "MRSValue",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved2, "Reserved2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ExtMemoryID, "ExtMemoryID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "An external indicator (by hardcode, callback or pin) to tell what is the current memory module"))
	),
	(bios->MemoryType, "MemoryType",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		(ATUI_NODESCR)
	),
	(bios->MemoryVendorID, "MemoryVendorID",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->MemoryDeviceCfg, "MemoryDeviceCfg",
		(ATUI_HEX, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->Row, "Row",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of Row,in power of 2;"))
	),
	(bios->Column, "Column",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of Column,in power of 2;"))
	),
	(bios->Bank, "Bank",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Nunber of Bank;"))
	),
	(bios->Rank, "Rank",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of Rank, in power of 2"))
	),
	(bios->ChannelNum, "ChannelNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of channel;"))
	),
	(bios->ChannelConfig, "ChannelConfig",
		(ATUI_NODISPLAY, ATUI_INLINE, vram_module_channel_config),
		(ATUI_NODESCR)
	),
	(bios->DefaultMVDDQ_ID, "DefaultMVDDQ_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Default MVDDQ setting for this memory block, ID linking to MVDDQ info table to find real set-up data;"))
	),
	(bios->DefaultMVDDC_ID, "DefaultMVDDC_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Default MVDDC setting for this memory block, ID linking to MVDDC info table to find real set-up data;"))
	),
	(bios->Reserved3, "Reserved3",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, atom_vram_module_v2, atomtree_vram_module,
	(bios->Reserved, "Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Flags, "Flags",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "To enable/disable functionalities based on memory type"))
	),
	(bios->EngineClock, "EngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Override of default engine clock for particular memory type"))
	),
	(bios->MemoryClock, "MemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Override of default memory clock for particular memory type"))
	),
	(bios->EMRS2Value, "EMRS2Value",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "EMRS2 Value is used for GDDR2 and GDDR4 memory type"))
	),
	(bios->EMRS3Value, "EMRS3Value",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "EMRS3 Value is used for GDDR2 and GDDR4 memory type"))
	),
	(bios->EMRSValue, "EMRSValue",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MRSValue, "MRSValue",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved2, "Reserved2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ExtMemoryID, "ExtMemoryID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "An external indicator (by hardcode, callback or pin) to tell what is the current memory module"))
	),
	(bios->MemoryType, "MemoryType",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		(ATUI_NODESCR)
	),
	(bios->MemoryVendorID, "MemoryVendorID",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->MemoryDeviceCfg, "MemoryDeviceCfg",
		(ATUI_HEX, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->Row, "Row",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of Row in power of 2"))
	),
	(bios->Column, "Column",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of Column in power of 2"))
	),
	(bios->Bank, "Bank",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Nunber of Bank"))
	),
	(bios->Rank, "Rank",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of Rank, in power of 2"))
	),
	(bios->ChannelNum, "ChannelNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of channel"))
	),
	(bios->ChannelConfig, "ChannelConfig",
		(ATUI_NODISPLAY, ATUI_INLINE, vram_module_channel_config),
		(ATUI_NODESCR)
	),
	(bios->DefaultMVDDQ_ID, "DefaultMVDDQ_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Default MVDDQ setting for this memory block, ID linking to MVDDQ info table to find real set-up data;"))
	),
	(bios->DefaultMVDDC_ID, "DefaultMVDDC_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Default MVDDC setting for this memory block, ID linking to MVDDC info table to find real set-up data;"))
	),
	(bios->RefreshRateFactor, "RefreshRateFactor",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved3, "Reserved3",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_memory_timing_format, atomtree_vram_module,
	(bios->ClkRange, "ClkRange",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "memory clock in 10kHz unit, when target memory clock is below this clock, use this memory timing"))
	),
	(bios->MR0, "MR0",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR1, "MR1",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->CL, "CL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->WL, "WL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRAS, "tRAS",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRC, "tRC",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRFC, "tRFC",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRCDR, "tRCDR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRCDW, "tRCDW",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRP, "tRP",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRRD, "tRRD",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWR, "tWR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWTR, "tWTR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tPDIX, "tPDIX",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tFAW, "tFAW",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tAOND, "tAOND",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR2, "MR2",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "flag to control memory timing calculation. bit0= control EMRS2 Infineon"))
	)
)

PPATUI_FUNCIFY(struct, atom_memory_timing_format_v1, atomtree_vram_module,
	(bios->ClkRange, "ClkRange",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "memory clock in 10kHz unit, when target memory clock is below this clock, use this memory timing"))
	),
	(bios->MRS, "MRS",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "mode register"))
	),
	(bios->EMRS, "EMRS",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "extended mode register"))
	),
	(bios->CL, "CL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->WL, "WL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRAS, "tRAS",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRC, "tRC",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRFC, "tRFC",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRCDR, "tRCDR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRCDW, "tRCDW",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRP, "tRP",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRRD, "tRRD",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWR, "tWR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWTR, "tWTR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tPDIX, "tPDIX",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tFAW, "tFAW",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tAOND, "tAOND",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->flag, "flag",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "flag to control memory timing calculation. bit0= control EMRS2 Infineon"))
	),
	(bios->tCCDL, "tCCDL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCRCRL, "tCRCRL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCRCWL, "tCRCWL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCKE, "tCKE",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCKRSE, "tCKRSE",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCKRSX, "tCKRSX",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tFAW32, "tFAW32",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR5, "MR5",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Terminator, "Terminator",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_memory_timing_format_v2, atomtree_vram_module,
	(bios->ClkRange, "ClkRange",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "memory clock in 10kHz unit, when target memory clock is below this clock, use this memory timing"))
	),
	(bios->MRS, "MRS",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "mode register"))
	),
	(bios->EMRS, "EMRS",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "extended mode register"))
	),
	(bios->CL, "CL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->WL, "WL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRAS, "tRAS",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRC, "tRC",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRFC, "tRFC",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRCDR, "tRCDR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRCDW, "tRCDW",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRP, "tRP",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRRD, "tRRD",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWR, "tWR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWTR, "tWTR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tPDIX, "tPDIX",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tFAW, "tFAW",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tAOND, "tAOND",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->flag, "flag",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "flag to control memory timing calculation. bit0= control EMRS2 Infineon"))
	),
	(bios->tCCDL, "tCCDL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCRCRL, "tCRCRL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCRCWL, "tCRCWL",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCKE, "tCKE",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCKRSE, "tCKRSE",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCKRSX, "tCKRSX",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tFAW32, "tFAW32",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR4, "MR4",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR5, "MR5",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Terminator, "Terminator",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved, "Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_memory_format, atomtree_vram_module,
	(bios->DllDisClock, "DllDisClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "memory DLL will be disable when target memory clock is below this clock"))
	),
	(bios->MR2, "MR2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR3, "MR3",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MemoryType, "MemoryType",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		(ATUI_NODESCR)
	),
	(bios->MemoryVendorID, "MemoryVendorID",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->Row, "Row",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of Row,in power of 2;"))
	),
	(bios->Column, "Column",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of Column,in power of 2;"))
	),
	(bios->Bank, "Bank",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Nunber of Bank;"))
	),
	(bios->Rank, "Rank",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of Rank, in power of 2"))
	),
	(bios->BurstSize, "BurstSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "burst size, 0= burst size=4  1= burst size=8"))
	),
	(bios->DllDisBit, "DllDisBit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "position of DLL Enable/Disable bit in EMRS ( Extended Mode Register )"))
	),
	(bios->RefreshRateFactor, "RefreshRateFactor",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "memory refresh rate in unit of ms"))
	),
	(bios->Density, "Density",
		(ATUI_DEC, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->Preamble, "Preamble",
		(ATUI_NODISPLAY, ATUI_INLINE, mem_preamble),
		(ATUI_NODESCR)
	),
	(bios->MemAttrib, "MemAttrib",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Memory Device Addribute, like RDBI/WDBI etc"))
	),
	(bios->MemTiming, "MemTiming", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "MemTiming [%02u]",
				(ATUI_NAN, ATUI_PETIOLE, atom_memory_timing_format),
				(ATUI_NODESCR)
			),
			NULL, atomtree->num_memory_timing_format, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "Memory Timing block sort from lower clock to higher clock"))
	)
)


PPATUI_FUNCIFY(struct, atom_vram_module_v3, atomtree_vram_module,
	(bios->ChannelMapCfg, "ChannelMapCfg",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "board dependent paramenter:Channel combination"))
	),
	(bios->ModuleSize, "ModuleSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "size of ATOM_VRAM_MODULE_V3"))
	),
	(bios->DefaultMVDDQ, "DefaultMVDDQ",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "board dependent parameter:Default Memory Core Voltage"))
	),
	(bios->DefaultMVDDC, "DefaultMVDDC",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "board dependent parameter:Default Memory IO Voltage"))
	),
	(bios->ExtMemoryID, "ExtMemoryID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "An external indicator (by hardcode, callback or pin) to tell what is the current memory module"))
	),
	(bios->ChannelNum, "ChannelNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "board dependent parameter:Number of channel;"))
	),
	(bios->ChannelSize, "ChannelSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "board dependent parameter:32bit or 64bit"))
	),
	(bios->VREFI, "VREFI",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "board dependnt parameter: EXT or INT +160mv to -140mv"))
	),
	(bios->NPL_RT, "NPL_RT",
		(ATUI_NODISPLAY, ATUI_INLINE, npl_rtdelay),
		(ATUI_NODESCR)
	),
	(bios->Flag, "Flag",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "To enable/disable functionalities based on memory type"))
	),
	(bios->Memory, "Memory",
		(ATUI_NAN, ATUI_PETIOLE, atom_memory_format),
		((LANG_ENG, "describe all of video memory parameters from memory spec"))
	)
)

PPATUI_FUNCIFY(struct, atom_vram_module_v4, atomtree_vram_module,
	(bios->ChannelMapCfg, "ChannelMapCfg",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "board dependent parameter: Channel combination"))
	),
	(bios->ModuleSize, "ModuleSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "size of ATOM_VRAM_MODULE_V4, make it easy for VBIOS to look for next entry of VRAM_MODULE"))
	),
	(bios->PrivateReserved, "PrivateReserved",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!! MC_ARB_RAMCFG (includes NOOFBANK,NOOFRANKS,NOOFROWS,NOOFCOLS"))
	),
	(bios->Reserved, "Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ExtMemoryID, "ExtMemoryID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "An external indicator (by hardcode, callback or pin) to tell what is the current memory module"))
	),
	(bios->MemoryType, "MemoryType",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		(ATUI_NODESCR)
	),
	(bios->ChannelNum, "ChannelNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of channels present in this module config"))
	),
	(bios->ChannelWidth, "ChannelWidth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0 - 32 bits; 1 - 64 bits"))
	),
	(bios->Density, "Density",
		(ATUI_DEC, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->Flag, "Flag",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "To enable/disable functionalities based on memory type"))
	),
	(bios->Misc, "Misc",
		(ATUI_NODISPLAY, ATUI_INLINE, vrammodule_misc),
		(ATUI_NODESCR)
	),
	(bios->VREFI, "VREFI",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "board dependent parameter"))
	),
	(bios->NPL_RT, "NPL_RT",
		(ATUI_NODISPLAY, ATUI_INLINE, npl_rtdelay),
		(ATUI_NODESCR)
	),
	(bios->Preamble, "Preamble",
		(ATUI_NODISPLAY, ATUI_INLINE, mem_preamble),
		(ATUI_NODESCR)
	),
	(bios->MemorySize, "MemorySize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!! Total memory size in unit of 16MB for CONFIG_MEMSIZE - bit[23:0] zeros"))
	),
	(bios->Reserved2, "Reserved2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR2, "MR2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR3, "MR3",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MemoryVendorID, "MemoryVendorID",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->RefreshRateFactor, "RefreshRateFactor",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(bios->Reserved3, "Reserved3",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->MemTiming, "MemTiming", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "MemTiming [%02u]",
				(ATUI_NAN, ATUI_PETIOLE, atom_memory_timing_format),
				(ATUI_NODESCR)
			),
			NULL, atomtree->num_memory_timing_format, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "Memory Timing block sort from lower clock to higher clock"))
	)
)


PPATUI_FUNCIFY(struct, atom_vram_module_v5, atomtree_vram_module,
	(bios->ChannelMapCfg, "ChannelMapCfg",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "board dependent parameter: Channel combination"))
	),
	(bios->ModuleSize, "ModuleSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "size of ATOM_VRAM_MODULE_V4, make it easy for VBIOS to look for next entry of VRAM_MODULE"))
	),
	(bios->PrivateReserved, "PrivateReserved",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!! MC_ARB_RAMCFG (includes NOOFBANK,NOOFRANKS,NOOFROWS,NOOFCOLS"))
	),
	(bios->Reserved, "Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ExtMemoryID, "ExtMemoryID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "An external indicator (by hardcode, callback or pin) to tell what is the current memory module"))
	),
	(bios->MemoryType, "MemoryType",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		(ATUI_NODESCR)
	),
	(bios->ChannelNum, "ChannelNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of channels present in this module config"))
	),
	(bios->ChannelWidth, "ChannelWidth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0 - 32 bits; 1 - 64 bits"))
	),
	(bios->Density, "Density",
		(ATUI_DEC, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->Flag, "Flag",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "To enable/disable functionalities based on memory type"))
	),
	(bios->Misc, "Misc",
		(ATUI_NODISPLAY, ATUI_INLINE, vrammodule_misc),
		(ATUI_NODESCR)
	),
	(bios->VREFI, "VREFI",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "board dependent parameter"))
	),
	(bios->NPL_RT, "NPL_RT",
		(ATUI_NODISPLAY, ATUI_INLINE, npl_rtdelay),
		(ATUI_NODESCR)
	),
	(bios->Preamble, "Preamble",
		(ATUI_NODISPLAY, ATUI_INLINE, mem_preamble),
		(ATUI_NODESCR)
	),
	(bios->MemorySize, "MemorySize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!! Total memory size in unit of 16MB for CONFIG_MEMSIZE - bit[23:0] zeros"))
	),
	(bios->Reserved3, "Reserved3",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->EMRS2Value, "EMRS2Value",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "EMRS2 Value is used for GDDR2 and GDDR4 memory type"))
	),
	(bios->EMRS3Value, "EMRS3Value",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "EMRS3 Value is used for GDDR2 and GDDR4 memory type"))
	),
	(bios->MemoryVendorID, "MemoryVendorID",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->RefreshRateFactor, "RefreshRateFactor",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(bios->FIFODepth, "FIFODepth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "FIFO depth supposes to be detected during vendor detection, but if we dont do vendor detection we have to hardcode FIFO Depth"))
	),
	(bios->CDR_Bandwidth, "CDR_Bandwidth",
		(ATUI_NODISPLAY, ATUI_INLINE, cdr_bandwidth),
		(ATUI_NODESCR)
	),
	(bios->MemTiming, "MemTiming", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "MemTiming [%02u]",
				(ATUI_NAN, ATUI_PETIOLE, atom_memory_timing_format_v1),
				(ATUI_NODESCR)
			),
			NULL, atomtree->num_memory_timing_format, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "Memory Timing block sort from lower clock to higher clock"))
	)
)

PPATUI_FUNCIFY(struct, atom_vram_module_v6, atomtree_vram_module,
	(bios->ChannelMapCfg, "ChannelMapCfg",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "board dependent parameter: Channel combination"))
	),
	(bios->ModuleSize, "ModuleSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "size of ATOM_VRAM_MODULE_V4, make it easy for VBIOS to look for next entry of VRAM_MODULE"))
	),
	(bios->PrivateReserved, "PrivateReserved",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!! MC_ARB_RAMCFG (includes NOOFBANK,NOOFRANKS,NOOFROWS,NOOFCOLS"))
	),
	(bios->Reserved, "Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ExtMemoryID, "ExtMemoryID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "An external indicator (by hardcode, callback or pin) to tell what is the current memory module"))
	),
	(bios->MemoryType, "MemoryType",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		(ATUI_NODESCR)
	),
	(bios->ChannelNum, "ChannelNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of channels present in this module config"))
	),
	(bios->ChannelWidth, "ChannelWidth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "0 - 32 bits; 1 - 64 bits"))
	),
	(bios->Density, "Density",
		(ATUI_DEC, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->Flag, "Flag",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "To enable/disable functionalities based on memory type"))
	),
	(bios->Misc, "Misc",
		(ATUI_NODISPLAY, ATUI_INLINE, vrammodule_misc),
		(ATUI_NODESCR)
	),
	(bios->VREFI, "VREFI",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "board dependent parameter"))
	),
	(bios->NPL_RT, "NPL_RT",
		(ATUI_NODISPLAY, ATUI_INLINE, npl_rtdelay),
		(ATUI_NODESCR)
	),
	(bios->Preamble, "Preamble",
		(ATUI_NODISPLAY, ATUI_INLINE, mem_preamble),
		(ATUI_NODESCR)
	),
	(bios->MemorySize, "MemorySize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!! Total memory size in unit of 16MB for CONFIG_MEMSIZE - bit[23:0] zeros"))
	),
	(bios->Reserved2, "Reserved2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->EMRS2Value, "EMRS2Value",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "EMRS2 Value is used for GDDR2 and GDDR4 memory type"))
	),
	(bios->EMRS3Value, "EMRS3Value",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "EMRS3 Value is used for GDDR2 and GDDR4 memory type"))
	),
	(bios->MemoryVendorID, "MemoryVendorID",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->RefreshRateFactor, "RefreshRateFactor",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(bios->FIFODepth, "FIFODepth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "FIFO depth supposes to be detected during vendor detection, but if we dont do vendor detection we have to hardcode FIFO Depth"))
	),
	(bios->CDR_Bandwidth, "CDR_Bandwidth",
		(ATUI_NODISPLAY, ATUI_INLINE, cdr_bandwidth),
		(ATUI_NODESCR)
	),
	(bios->MemTiming, "MemTiming", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "MemTiming [%02u]",
				(ATUI_NAN, ATUI_PETIOLE, atom_memory_timing_format_v2),
				(ATUI_NODESCR)
			),
			NULL, atomtree->num_memory_timing_format, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "Memory Timing block sort from lower clock to higher clock"))
	)
)

PPATUI_FUNCIFY(struct, atom_vram_module_v7, atomtree_vram_module,
	(bios->ChannelMapCfg, "ChannelMapCfg",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "mmMC_SHARED_CHREMAP"))
	),
	(bios->ModuleSize, "ModuleSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Size of ATOM_VRAM_MODULE_V7"))
	),
	(bios->PrivateReserved, "PrivateReserved",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "MC_ARB_RAMCFG (includes NOOFBANK,NOOFRANKS,NOOFROWS,NOOFCOLS)"))
	),
	(bios->EnableChannels, "EnableChannels",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "bit vector which indicate which channels are enabled"))
	),
	(bios->ExtMemoryID, "ExtMemoryID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Current memory module ID"))
	),
	(bios->MemoryType, "MemoryType",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		(ATUI_NODESCR)
	),
	(bios->ChannelNum, "ChannelNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of mem. channels supported in this module"))
	),
	(bios->ChannelWidth, "ChannelWidth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT"))
	),
	(bios->Density, "Density",
		(ATUI_DEC, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->Reserve, "Reserve",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "In MC7x, the lower 4 bits are used as bit8-11 of memory size. In other MC code, it's not used."))
	),
	(bios->Misc, "Misc",
		(ATUI_NODISPLAY, ATUI_INLINE, vrammodule_misc),
		(ATUI_NODESCR)
	),
	(bios->VREFI, "VREFI",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Not used."))
	),
	(bios->NPL_RT, "NPL_RT",
		(ATUI_NODISPLAY, ATUI_INLINE, npl_rtdelay),
		(ATUI_NODESCR)
	),
	(bios->Preamble, "Preamble",
		(ATUI_NODISPLAY, ATUI_INLINE, mem_preamble),
		(ATUI_NODESCR)
	),
	(bios->MemorySize, "MemorySize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Total memory size in unit of 16MB for CONFIG_MEMSIZE - bit[23:0] zeros"))
	),
	(bios->SEQSettingOffset, "SEQSettingOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved, "Reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->EMRS2Value, "EMRS2Value",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "EMRS2/MR2 Value."))
	),
	(bios->EMRS3Value, "EMRS3Value",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "EMRS3/MR3 Value."))
	),
	(bios->MemoryVendorID, "MemoryVendorID",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->RefreshRateFactor, "RefreshRateFactor",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(bios->FIFODepth, "FIFODepth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "FIFO depth can be detected during vendor detection, here is hardcoded per memory"))
	),
	(bios->CDR_Bandwidth, "CDR_Bandwidth",
		(ATUI_NODISPLAY, ATUI_INLINE, cdr_bandwidth),
		(ATUI_NODESCR)
	),
	(bios->strMemPNString, "strMemPNString",
		(ATUI_NAN, ATUI_ARRAY),
		((LANG_ENG, "part number end with '0'."))
	)
)

PPATUI_FUNCIFY(struct, atom_vram_module_v8, atomtree_vram_module,
	(bios->ChannelMapCfg, "ChannelMapCfg",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "mmMC_SHARED_CHREMAP"))
	),
	(bios->ModuleSize, "ModuleSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Size of ATOM_VRAM_MODULE_V7"))
	),
	(bios->McRamCfg, "McRamCfg",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "MC_ARB_RAMCFG (includes NOOFBANK,NOOFRANKS,NOOFROWS,NOOFCOLS)"))
	),
	(bios->EnableChannels, "EnableChannels",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "bit vector which indicate which channels are enabled"))
	),
	(bios->ExtMemoryID, "ExtMemoryID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Current memory module ID"))
	),
	(bios->MemoryType, "MemoryType",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		(ATUI_NODESCR)
	),
	(bios->ChannelNum, "ChannelNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Number of mem. channels supported in this module"))
	),
	(bios->ChannelWidth, "ChannelWidth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT"))
	),
	(bios->Density, "Density",
		(ATUI_DEC, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->BankCol, "BankCol",
		(ATUI_NODISPLAY, ATUI_INLINE, bank_col_counts),
		(ATUI_NODESCR)
	),
	(bios->Misc, "Misc",
		(ATUI_NODISPLAY, ATUI_INLINE, vrammodule_misc),
		(ATUI_NODESCR)
	),
	(bios->VREFI, "VREFI",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Not used."))
	),
	(bios->Reserved, "Reserved",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Not used"))
	),
	(bios->MemorySize, "MemorySize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Total memory size in unit of MB for CONFIG_MEMSIZE zeros"))
	),
	(bios->McTunningSetId, "McTunningSetId",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "MC phy registers set per."))
	),
	(bios->RowNum, "RowNum",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->EMRS2Value, "EMRS2Value",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "EMRS2/MR2 Value."))
	),
	(bios->EMRS3Value, "EMRS3Value",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "EMRS3/MR3 Value."))
	),
	(bios->MemoryVendorID, "MemoryVendorID",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->RefreshRateFactor, "RefreshRateFactor",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(bios->FIFODepth, "FIFODepth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "FIFO depth can be detected during vendor detection, here is hardcoded per memory"))
	),
	(bios->CDR_Bandwidth, "CDR_Bandwidth",
		(ATUI_NODISPLAY, ATUI_INLINE, cdr_bandwidth),
		(ATUI_NODESCR)
	),

	(bios->ChannelMapCfg1, "ChannelMapCfg1",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "channel mapping for channel8~15"))
	),
	(bios->BankMapCfg, "BankMapCfg",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved2, "Reserved2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->strMemPNString, "strMemPNString",
		(ATUI_NAN, ATUI_ARRAY),
		((LANG_ENG, "part number end with '0'."))
	)
)

PPATUI_FUNCIFY(struct, atom_vram_info_v1_2, atomtree_vram_info_v1_2,
	(bios->table_header, "table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->NumOfVRAMModule, "NumOfVRAMModule",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_vram_info_v1_3, atomtree_vram_info_v1_3,
	(bios->table_header, "table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->MemAdjustTblOffset, "MemAdjustTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of ATOM_INIT_REG_BLOCK structure for memory vendor specific MC adjust setting"))
	),
	(bios->MemClkPatchTblOffset, "MemClkPatchTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of ATOM_INIT_REG_BLOCK structure for memory clock specific MC setting"))
	),
	(bios->Reserved, "Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->aVID_PinsShift, "aVID_PinsShift",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, "8 bit strap maximum+terminator"))
	),
	(bios->NumOfVRAMModule, "NumOfVRAMModule",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, mem_dq_7_0_byte_remap, atui_nullstruct,
	(bios->MemDQ7_0ByteRemap, "MemDQ7_0ByteRemap",
		(ATUI_BIN, ATUI_BITFIELD, (
			("byte0", 0,0, ATUI_DEC, (ATUI_NODESCR)),
			("byte1", 1,1, ATUI_DEC, (ATUI_NODESCR)),
			("byte2", 2,2, ATUI_DEC, (ATUI_NODESCR)),
			("byte3", 3,3, ATUI_DEC, (ATUI_NODESCR)),
			("byte4", 4,4, ATUI_DEC, (ATUI_NODESCR)),
			("byte5", 5,5, ATUI_DEC, (ATUI_NODESCR)),
			("byte6", 6,6, ATUI_DEC, (ATUI_NODESCR)),
			("byte7", 7,7, ATUI_DEC, (ATUI_NODESCR))
		)), ((LANG_ENG, "DQ line byte remap"))
	)
)
PPATUI_FUNCIFY(union, mem_dq_7_0_bit_remap, atui_nullstruct,
	(bios->MemDQ7_0BitRemap, "MemDQ7_0BitRemap",
		(ATUI_BIN, ATUI_BITFIELD, (
			("DQ0",  2,0, ATUI_DEC, (ATUI_NODESCR)),
			("DQ1",  5,3, ATUI_DEC, (ATUI_NODESCR)),
			("DQ2",  8,6, ATUI_DEC, (ATUI_NODESCR)),
			("DQ3", 11,9, ATUI_DEC, (ATUI_NODESCR)),
			("DQ4", 14,12, ATUI_DEC, (ATUI_NODESCR)),
			("DQ5", 17,15, ATUI_DEC, (ATUI_NODESCR)),
			("DQ6", 20,18, ATUI_DEC, (ATUI_NODESCR)),
			("DQ7", 23,21, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_vram_info_v1_4, atomtree_vram_info_v1_4,
	(bios->table_header, "table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->MemAdjustTblOffset, "MemAdjustTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of ATOM_INIT_REG_BLOCK structure for memory vendor specific MC adjust setting"))
	),
	(bios->MemClkPatchTblOffset, "MemClkPatchTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of ATOM_INIT_REG_BLOCK structure for memory clock specific MC setting"))
	),
	(bios->Reserved, "Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MemDQ7_0ByteRemap, "MemDQ7_0ByteRemap",
		(ATUI_NODISPLAY, ATUI_INLINE, mem_dq_7_0_byte_remap),
		(ATUI_NODESCR)
	),
	(bios->MemDQ7_0BitRemap, "MemDQ7_0BitRemap",
		(ATUI_NODISPLAY, ATUI_INLINE, mem_dq_7_0_bit_remap),
		(ATUI_NODESCR)
	),
	(bios->Reserved2, "Reserved2",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->NumOfVRAMModule, "NumOfVRAMModule",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_vram_info_header_v2_1,
		atomtree_vram_info_header_v2_1,
	(bios->table_header, "table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->MemAdjustTblOffset, "MemAdjustTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of ATOM_INIT_REG_BLOCK structure for memory vendor specific MC adjust setting"))
	),
	(bios->MemClkPatchTblOffset, "MemClkPatchTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of ATOM_INIT_REG_BLOCK structure for memory clock specific MC setting"))
	),
	(bios->PerBytePresetOffset, "PerBytePresetOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of ATOM_INIT_REG_BLOCK structure for Per Byte Offset Preset Settings"))
	),
	(bios->Reserved, "Reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->NumOfVRAMModule, "NumOfVRAMModule",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "indicate number of VRAM module"))
	),
	(bios->MemoryClkPatchTblVer, "MemoryClkPatchTblVer",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "version of memory AC timing register list"))
	),
	(bios->VramModuleVer, "VramModuleVer",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "indicate ATOM_VRAM_MODUE version"))
	),
	(bios->Reserved2, "Reserved2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->vram_module, "vram_module", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "vram_module [%02u]",
				(ATUI_NAN, ATUI_PETIOLE, atom_vram_module_v7),
				(ATUI_NODESCR)
			),
			NULL, bios->NumOfVRAMModule, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "just for allocation, real number of blocks is in ucNumOfVRAMModule;"))
	)
)

PPATUI_FUNCIFY(struct, atom_vram_info_header_v2_2,
		atomtree_vram_info_header_v2_2,
	(bios->table_header, "table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->MemAdjustTblOffset, "MemAdjustTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of ATOM_INIT_REG_BLOCK structure for memory vendor specific MC adjust setting"))
	),
	(bios->MemClkPatchTblOffset, "MemClkPatchTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of ATOM_INIT_REG_BLOCK structure for memory clock specific MC setting"))
	),
	(bios->McAdjustPerTileTblOffset, "McAdjustPerTileTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of ATOM_INIT_REG_BLOCK structure for Per Byte Offset Preset Settings"))
	),
	(bios->McPhyInitTableOffset, "McPhyInitTableOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of ATOM_INIT_REG_BLOCK structure for MC phy init set"))
	),
	(bios->DramDataRemapTblOffset, "DramDataRemapTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, "offset of ATOM_DRAM_DATA_REMAP array to indicate DRAM data lane to GPU mapping"))
	),
	(bios->Reserved1, "Reserved1",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->NumOfVRAMModule, "NumOfVRAMModule",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "indicate number of VRAM module"))
	),
	(bios->MemoryClkPatchTblVer, "MemoryClkPatchTblVer",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "version of memory AC timing register list"))
	),
	(bios->VramModuleVer, "VramModuleVer",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "indicate ATOM_VRAM_MODUE version"))
	),
	(bios->McPhyTileNum, "McPhyTileNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "indicate the MCD tile number which use in DramDataRemapTbl and usMcAdjustPerTileTblOffset"))
	),
	(bios->vram_module, "vram_module", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, "vram_module [%02u]",
				(ATUI_NAN, ATUI_PETIOLE, atom_vram_module_v8),
				(ATUI_NODESCR)
			),
			NULL, bios->NumOfVRAMModule, // deferred start, count
			ATUI_NULL // enum
		)),
		((LANG_ENG, "just for allocation, real number of blocks is in ucNumOfVRAMModule;"))
	)
)

