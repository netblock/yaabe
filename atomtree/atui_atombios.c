#include "atomtree.h"
#include "atui.h"

PPATUI_FUNCIFY(struct, atom_rom_header_v1_1, atui_nullstruct,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->FirmWareSignature, u8"FirmWareSignature",
		(ATUI_NAN, ATUI_ARRAY),
		((LANG_ENG, u8"Signature to distinguish between Atombios and non-atombios, atombios should init it as \"ATOM\", don't change the position"))
	),
	(bios->BiosRuntimeSegmentAddress, u8"BiosRuntimeSegmentAddress",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ProtectedModeInfoOffset, u8"ProtectedModeInfoOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ConfigFilenameOffset, u8"ConfigFilenameOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->CRC_BlockOffset, u8"CRC_BlockOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BIOS_BootupMessageOffset, u8"BIOS_BootupMessageOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Int10Offset, u8"Int10Offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PciBusDevInitCode, u8"PciBusDevInitCode",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->IoBaseAddress, u8"IoBaseAddress",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SubsystemVendorID, u8"SubsystemVendorID",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SubsystemID, u8"SubsystemID",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PCI_InfoOffset, u8"PCI_InfoOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MasterCommandTableOffset, u8"MasterCommandTableOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Offest for SW to get all command table offsets, Don't change the position"))
	),
	(bios->MasterDataTableOffset, u8"MasterDataTableOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Offest for SW to get all data table offsets, Don't change the position"))
	),
	(bios->ExtendedFunctionCode, u8"ExtendedFunctionCode",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved, u8"Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_rom_header_v2_1, atui_nullstruct,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->FirmWareSignature, u8"FirmWareSignature",
		(ATUI_NAN, ATUI_ARRAY),
		((LANG_ENG, u8"Signature to distinguish between Atombios and non-atombios, atombios should init it as \"ATOM\", don't change the position"))
	),
	(bios->BiosRuntimeSegmentAddress, u8"BiosRuntimeSegmentAddress",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ProtectedModeInfoOffset, u8"ProtectedModeInfoOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ConfigFilenameOffset, u8"ConfigFilenameOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->CRC_BlockOffset, u8"CRC_BlockOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BIOS_BootupMessageOffset, u8"BIOS_BootupMessageOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Int10Offset, u8"Int10Offset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PciBusDevInitCode, u8"PciBusDevInitCode",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->IoBaseAddress, u8"IoBaseAddress",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SubsystemVendorID, u8"SubsystemVendorID",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->SubsystemID, u8"SubsystemID",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PCI_InfoOffset, u8"PCI_InfoOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MasterCommandTableOffset, u8"MasterCommandTableOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Offest for SW to get all command table offsets, Don't change the position"))
	),
	(bios->MasterDataTableOffset, u8"MasterDataTableOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Offest for SW to get all data table offsets, Don't change the position"))
	),
	(bios->ExtendedFunctionCode, u8"ExtendedFunctionCode",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved, u8"Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->PSPDirTableOffset, u8"PSPDirTableOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_master_data_table_v1_1, atui_nullstruct,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->UtilityPipeLine, u8"UtilityPipeLine",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Offest for the utility to get parser info,Don't change this position!"))
	),
	(bios->MultimediaCapabilityInfo, u8"MultimediaCapabilityInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Only used by MM Lib,latest version 1.1, not configuable from Bios, need to include the table to build Bios"))
	),
	(bios->MultimediaConfigInfo, u8"MultimediaConfigInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Only used by MM Lib,latest version 2.1, not configuable from Bios, need to include the table to build Bios"))
	),
	(bios->StandardVESA_Timing, u8"StandardVESA_Timing",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Only used by Bios"))
	),
	(bios->FirmwareInfo, u8"FirmwareInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components,latest version 1.4"))
	),
	(bios->PaletteData, u8"PaletteData",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Only used by BIOS"))
	),
	(bios->LCD_Info, u8"LCD_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components,latest version 1.3, was called LVDS_Info"))
	),
	(bios->DIGTransmitterInfo, u8"DIGTransmitterInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Internal used by VBIOS only version 3.1"))
	),
	(bios->SMU_Info, u8"SMU_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components,latest version 1.1"))
	),
	(bios->SupportedDevicesInfo, u8"SupportedDevicesInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Will be obsolete from R600"))
	),
	(bios->GPIO_I2C_Info, u8"GPIO_I2C_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components,latest version 1.2 will be used from R600"))
	),
	(bios->VRAM_UsageByFirmware, u8"VRAM_UsageByFirmware",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components,latest version 1.3 will be used from R600"))
	),
	(bios->GPIO_Pin_LUT, u8"GPIO_Pin_LUT",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components,latest version 1.1"))
	),
	(bios->VESA_ToInternalModeLUT, u8"VESA_ToInternalModeLUT",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Only used by Bios"))
	),
	(bios->GFX_Info, u8"GFX_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components,latest version 2.1 will be used from R600"))
	),
	(bios->PowerPlayInfo, u8"PowerPlayInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components,latest version 2.1,new design from R600"))
	),
	(bios->GPUVirtualizationInfo, u8"GPUVirtualizationInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Will be obsolete from R600"))
	),
	(bios->SaveRestoreInfo, u8"SaveRestoreInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Only used by Bios"))
	),
	(bios->PPLL_SS_Info, u8"PPLL_SS_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components,latest version 1.2, used to call SS_Info, change to new name because of int ASIC SS info"))
	),
	(bios->OemInfo, u8"OemInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Defined and used by external SW, should be obsolete soon"))
	),
	(bios->XTMDS_Info, u8"XTMDS_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Will be obsolete from R600"))
	),
	(bios->MclkSS_Info, u8"MclkSS_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components,latest version 1.1, only enabled when ext SS chip is used"))
	),
	(bios->Object_Header, u8"Object_Header",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components,latest version 1.1"))
	),
	(bios->IndirectIOAccess, u8"IndirectIOAccess",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Only used by Bios,this table position can't change at all!!"))
	),
	(bios->MC_InitParameter, u8"MC_InitParameter",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Only used by command table"))
	),
	(bios->ASIC_VDDC_Info, u8"ASIC_VDDC_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Will be obsolete from R600"))
	),
	(bios->ASIC_InternalSS_Info, u8"ASIC_InternalSS_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"New tabel name from R600, used to be called \"ASIC_MVDDC_Info\""))
	),
	(bios->TV_VideoMode, u8"TV_VideoMode",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Only used by command table"))
	),
	(bios->VRAM_Info, u8"VRAM_Info",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Only used by command table, latest version 1.3"))
	),
	(bios->MemoryTrainingInfo, u8"MemoryTrainingInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Used for VBIOS and Diag utility for memory training purpose since R600. the new table rev start from 2.1"))
	),
	(bios->IntegratedSystemInfo, u8"IntegratedSystemInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components"))
	),
	(bios->ASIC_ProfilingInfo, u8"ASIC_ProfilingInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"New table name from R600, used to be called \"ASIC_VDDCI_Info\" for pre-R600"))
	),
	(bios->VoltageObjectInfo, u8"VoltageObjectInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components, latest version 1.1"))
	),
	(bios->PowerSourceInfo, u8"PowerSourceInfo",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Shared by various SW components, latest versoin 1.1"))
	),
	(bios->ServiceInfo, u8"ServiceInfo",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)



PPATUI_FUNCIFY(union, atombios_firmware_capability_v1, atomtree_firmware_info,
	(bios->FirmwareCapability, u8"FirmwareCapability",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"FirmwarePosted",         0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"DualCRTC_Support",       1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ExtendedDesktopSupport", 2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"MemoryClockSS_Support",  3,3, ATUI_DEC, (ATUI_NODESCR)),
			(u8"EngineClockSS_Support",  4,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"GPUControlsBL",          5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"WMI_SUPPORT",            6,6, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PPMode_Assigned",        7,7, ATUI_DEC, (ATUI_NODESCR)),
			(u8"HyperMemory_Support",    8,8, ATUI_DEC, (ATUI_NODESCR)),
			(u8"HyperMemory_Size",      12,9, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PostWithoutModeSet",    13,13, ATUI_DEC, (ATUI_NODESCR)),
			(u8"SCL2Redefined",         14,14, ATUI_DEC, (ATUI_NODESCR)),
			(u8"Reserved",              15,15, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v1_0, atomtree_firmware_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->FirmwareRevision, u8"FirmwareRevision",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DefaultEngineClock, u8"DefaultEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->DefaultMemoryClock, u8"DefaultMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->DriverTargetEngineClock, u8"DriverTargetEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->DriverTargetMemoryClock, u8"DriverTargetMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Output, u8"MaxEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Output, u8"MaxMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Output, u8"MaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->ASICMaxEngineClock, u8"ASICMaxEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->ASICMaxMemoryClock, u8"ASICMaxMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->ASICMaxTemperature, u8"ASICMaxTemperature",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding, u8"Padding",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"Don't use them"))
	),
	(bios->aulReservedForBIOS, u8"aulReservedForBIOS",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"Don't use them"))
	),
	(bios->MinEngineClockPLL_Input, u8"MinEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Input, u8"MaxEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Output, u8"MinEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Input, u8"MinMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Input, u8"MaxMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Output, u8"MinMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxPixelClock, u8"MaxPixelClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit, Max.  Pclk"))
	),
	(bios->MinPixelClockPLL_Input, u8"MinPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Input, u8"MaxPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinPixelClockPLL_Output, u8"MinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit, the definitions above can't change!!!"))
	),
	(bios->FirmwareCapability, u8"FirmwareCapability",
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability_v1),
		(ATUI_NODESCR)
	),
	(bios->ReferenceClock, u8"ReferenceClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->PM_RTS_Location, u8"PM_RTS_Location",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"RTS PM4 starting location in ROM in 1Kb unit"))
	),
	(bios->PM_RTS_StreamSize, u8"PM_RTS_StreamSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"RTS PM4 packets in Kb unit"))
	),
	(bios->Design_ID, u8"Design_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Indicate what is the board design"))
	),
	(bios->MemoryModule_ID, u8"MemoryModule_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Indicate what is the board design"))
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v1_2, atomtree_firmware_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->FirmwareRevision, u8"FirmwareRevision",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DefaultEngineClock, u8"DefaultEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->DefaultMemoryClock, u8"DefaultMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->DriverTargetEngineClock, u8"DriverTargetEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->DriverTargetMemoryClock, u8"DriverTargetMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Output, u8"MaxEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Output, u8"MaxMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Output, u8"MaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->ASICMaxEngineClock, u8"ASICMaxEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->ASICMaxMemoryClock, u8"ASICMaxMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->ASICMaxTemperature, u8"ASICMaxTemperature",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MinAllowedBL_Level, u8"MinAllowedBL_Level",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding, u8"Padding",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"Don't use them"))
	),
	(bios->aulReservedForBIOS, u8"aulReservedForBIOS",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"Don't use them"))
	),
	(bios->MinPixelClockPLL_Output, u8"MinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Input, u8"MinEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Input, u8"MaxEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Output, u8"MinEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Input, u8"MinMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Input, u8"MaxMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Output, u8"MinMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxPixelClock, u8"MaxPixelClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit, Max.  Pclk"))
	),
	(bios->MinPixelClockPLL_Input, u8"MinPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Input, u8"MaxPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinPixelClockPLL_Output_lower, u8"MinPixelClockPLL_Output_lower",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit - lower 16bit of ulMinPixelClockPLL_Output"))
	),
	(bios->FirmwareCapability, u8"FirmwareCapability",
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability_v1),
		(ATUI_NODESCR)
	),
	(bios->ReferenceClock, u8"ReferenceClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->PM_RTS_Location, u8"PM_RTS_Location",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"RTS PM4 starting location in ROM in 1Kb unit"))
	),
	(bios->PM_RTS_StreamSize, u8"PM_RTS_StreamSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"RTS PM4 packets in Kb unit"))
	),
	(bios->Design_ID, u8"Design_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Indicate what is the board design"))
	),
	(bios->MemoryModule_ID, u8"MemoryModule_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Indicate what is the board design"))
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v1_3, atomtree_firmware_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->FirmwareRevision, u8"FirmwareRevision",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DefaultEngineClock, u8"DefaultEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->DefaultMemoryClock, u8"DefaultMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->DriverTargetEngineClock, u8"DriverTargetEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->DriverTargetMemoryClock, u8"DriverTargetMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Output, u8"MaxEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Output, u8"MaxMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Output, u8"MaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->ASICMaxEngineClock, u8"ASICMaxEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->ASICMaxMemoryClock, u8"ASICMaxMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->ASICMaxTemperature, u8"ASICMaxTemperature",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MinAllowedBL_Level, u8"MinAllowedBL_Level",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Padding, u8"Padding",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"Don't use them"))
	),
	(bios->aulReservedForBIOS, u8"aulReservedForBIOS",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Don't use them"))
	),
	(bios->_3DAccelerationEngineClock, u8"_3DAccelerationEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinPixelClockPLL_Output, u8"MinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Input, u8"MinEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Input, u8"MaxEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Output, u8"MinEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Input, u8"MinMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Input, u8"MaxMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Output, u8"MinMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxPixelClock, u8"MaxPixelClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit, Max.  Pclk"))
	),
	(bios->MinPixelClockPLL_Input, u8"MinPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Input, u8"MaxPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinPixelClockPLL_Output_lower, u8"MinPixelClockPLL_Output_lower",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit - lower 16bit of ulMinPixelClockPLL_Output"))
	),
	(bios->FirmwareCapability, u8"FirmwareCapability",
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability_v1),
		(ATUI_NODESCR)
	),
	(bios->ReferenceClock, u8"ReferenceClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->PM_RTS_Location, u8"PM_RTS_Location",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"RTS PM4 starting location in ROM in 1Kb unit"))
	),
	(bios->PM_RTS_StreamSize, u8"PM_RTS_StreamSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"RTS PM4 packets in Kb unit"))
	),
	(bios->Design_ID, u8"Design_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Indicate what is the board design"))
	),
	(bios->MemoryModule_ID, u8"MemoryModule_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Indicate what is the board design"))
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v1_4, atomtree_firmware_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->FirmwareRevision, u8"FirmwareRevision",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DefaultEngineClock, u8"DefaultEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->DefaultMemoryClock, u8"DefaultMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->DriverTargetEngineClock, u8"DriverTargetEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->DriverTargetMemoryClock, u8"DriverTargetMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Output, u8"MaxEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Output, u8"MaxMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Output, u8"MaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->ASICMaxEngineClock, u8"ASICMaxEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->ASICMaxMemoryClock, u8"ASICMaxMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->ASICMaxTemperature, u8"ASICMaxTemperature",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MinAllowedBL_Level, u8"MinAllowedBL_Level",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BootUpVDDCVoltage, u8"BootUpVDDCVoltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In MV unit"))
	),
	(bios->LcdMinPixelClockPLL_Output, u8"LcdMinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In MHz unit"))
	),
	(bios->LcdMaxPixelClockPLL_Output, u8"LcdMaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In MHz unit"))
	),
	(bios->_3DAccelerationEngineClock, u8"_3DAccelerationEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinPixelClockPLL_Output, u8"MinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Input, u8"MinEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Input, u8"MaxEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Output, u8"MinEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Input, u8"MinMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Input, u8"MaxMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Output, u8"MinMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxPixelClock, u8"MaxPixelClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit, Max.  Pclk"))
	),
	(bios->MinPixelClockPLL_Input, u8"MinPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Input, u8"MaxPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinPixelClockPLL_Output_lower, u8"MinPixelClockPLL_Output_lower",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit - lower 16bit of ulMinPixelClockPLL_Output"))
	),
	(bios->FirmwareCapability, u8"FirmwareCapability",
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability_v1),
		(ATUI_NODESCR)
	),
	(bios->ReferenceClock, u8"ReferenceClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->PM_RTS_Location, u8"PM_RTS_Location",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"RTS PM4 starting location in ROM in 1Kb unit"))
	),
	(bios->PM_RTS_StreamSize, u8"PM_RTS_StreamSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"RTS PM4 packets in Kb unit"))
	),
	(bios->Design_ID, u8"Design_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Indicate what is the board design"))
	),
	(bios->MemoryModule_ID, u8"MemoryModule_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Indicate what is the board design"))
	)
)

PPATUI_FUNCIFY(struct, atom_firmware_info_v2_1, atomtree_firmware_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->FirmwareRevision, u8"FirmwareRevision",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DefaultEngineClock, u8"DefaultEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->DefaultMemoryClock, u8"DefaultMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->Reserved1, u8"Reserved1",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved2, u8"Reserved2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MaxEngineClockPLL_Output, u8"MaxEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Output, u8"MaxMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Output, u8"MaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->BinaryAlteredInfo, u8"BinaryAlteredInfo",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Was ulASICMaxEngineClock"))
	),
	(bios->DefaultDispEngineClkFreq, u8"DefaultDispEngineClkFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->Reserved3, u8"Reserved3",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Was ucASICMaxTemperature;"))
	),
	(bios->MinAllowedBL_Level, u8"MinAllowedBL_Level",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BootUpVDDCVoltage, u8"BootUpVDDCVoltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In MV unit"))
	),
	(bios->LcdMinPixelClockPLL_Output, u8"LcdMinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In MHz unit"))
	),
	(bios->LcdMaxPixelClockPLL_Output, u8"LcdMaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In MHz unit"))
	),
	(bios->Reserved4, u8"Reserved4",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Was ulAsicMaximumVoltage"))
	),
	(bios->MinPixelClockPLL_Output, u8"MinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Input, u8"MinEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxEngineClockPLL_Input, u8"MaxEngineClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinEngineClockPLL_Output, u8"MinEngineClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Input, u8"MinMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxMemoryClockPLL_Input, u8"MaxMemoryClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinMemoryClockPLL_Output, u8"MinMemoryClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxPixelClock, u8"MaxPixelClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit, Max.  Pclk"))
	),
	(bios->MinPixelClockPLL_Input, u8"MinPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Input, u8"MaxPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MinPixelClockPLL_Output_lower, u8"MinPixelClockPLL_Output_lower",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit - lower 16bit of ulMinPixelClockPLL_Output"))
	),
	(bios->FirmwareCapability, u8"FirmwareCapability",
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability_v1),
		(ATUI_NODESCR)
	),
	(bios->CoreReferenceClock, u8"CoreReferenceClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MemoryReferenceClock, u8"MemoryReferenceClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->UniphyDPModeExtClkFreq, u8"UniphyDPModeExtClkFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit, if it is 0, In DP Mode Uniphy Input clock from internal PPLL, otherwise Input clock from external Spread clock"))
	),
	(bios->MemoryModule_ID, u8"MemoryModule_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Indicate what is the board design"))
	),
	(bios->Reserved5, u8"Reserved5",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, product_branding_v2, atomtree_firmware_info,
	(bios->ProductBranding, u8"ProductBranding",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"EMBEDDED_CAP", 1,0, ATUI_DEC,
				((LANG_ENG, u8"Embedded feature level"))
			),
			(u8"Reserved",     3,2, ATUI_DEC, ((LANG_ENG, u8"Reserved"))),
			(u8"BRANDING_ID",  7,4, ATUI_DEC, ((LANG_ENG, u8"Branding ID")))
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_firmware_info_v2_2, atomtree_firmware_info,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->FirmwareRevision, u8"FirmwareRevision",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->DefaultEngineClock, u8"DefaultEngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->DefaultMemoryClock, u8"DefaultMemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->SPLL_OutputFreq, u8"SPLL_OutputFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->GPUPLL_OutputFreq, u8"GPUPLL_OutputFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->Reserved1, u8"Reserved1",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Was ulMaxEngineClockPLL_Output; //In 10Khz unit*"))
	),
	(bios->Reserved2, u8"Reserved2",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Was ulMaxMemoryClockPLL_Output; //In 10Khz unit*"))
	),
	(bios->MaxPixelClockPLL_Output, u8"MaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->BinaryAlteredInfo, u8"BinaryAlteredInfo",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Was ulASICMaxEngineClock  ?"))
	),
	(bios->DefaultDispEngineClkFreq, u8"DefaultDispEngineClkFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit. This is the frequency before DCDTO, corresponding to usBootUpVDDCVoltage."))
	),
	(bios->Reserved3, u8"Reserved3",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Was ucASICMaxTemperature;"))
	),
	(bios->MinAllowedBL_Level, u8"MinAllowedBL_Level",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BootUpVDDCVoltage, u8"BootUpVDDCVoltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In MV unit"))
	),
	(bios->LcdMinPixelClockPLL_Output, u8"LcdMinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In MHz unit"))
	),
	(bios->LcdMaxPixelClockPLL_Output, u8"LcdMaxPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In MHz unit"))
	),
	(bios->Reserved4, u8"Reserved4",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Was ulAsicMaximumVoltage"))
	),
	(bios->MinPixelClockPLL_Output, u8"MinPixelClockPLL_Output",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->RemoteDisplayConfig, u8"RemoteDisplayConfig",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"0=disable 1=enable"))
	),
	(bios->Reserved5, u8"Reserved5",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"Was usMinEngineClockPLL_Input and usMaxEngineClockPLL_Input"))
	),
	(bios->Reserved6, u8"Reserved6",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Was usMinEngineClockPLL_Output and usMinMemoryClockPLL_Input"))
	),
	(bios->Reserved7, u8"Reserved7",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"Was usMaxMemoryClockPLL_Input and usMinMemoryClockPLL_Output"))
	),
	(bios->MaxPixelClock, u8"MaxPixelClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit, Max.  Pclk used only for DAC"))
	),
	(bios->MinPixelClockPLL_Input, u8"MinPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MaxPixelClockPLL_Input, u8"MaxPixelClockPLL_Input",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->BootUpVDDCIVoltage, u8"BootUpVDDCIVoltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In unit of mv; Was usMinPixelClockPLL_Output;"))
	),
	(bios->FirmwareCapability, u8"FirmwareCapability",
		(ATUI_NODISPLAY, ATUI_INLINE, atombios_firmware_capability_v1),
		(ATUI_NODESCR)
	),
	(bios->CoreReferenceClock, u8"CoreReferenceClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->MemoryReferenceClock, u8"MemoryReferenceClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit"))
	),
	(bios->UniphyDPModeExtClkFreq, u8"UniphyDPModeExtClkFreq",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In 10Khz unit, if it is 0, In DP Mode Uniphy Input clock from internal PPLL, otherwise Input clock from external Spread clock"))
	),
	(bios->MemoryModule_ID, u8"MemoryModule_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Indicate what is the board design"))
	),
	(bios->CoolingSolution_ID, u8"CoolingSolution_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"0: Air cooling; 1: Liquid cooling ... [COOLING_SOLUTION]"))
	),
	(bios->ProductBranding, u8"ProductBranding",
		(ATUI_NODISPLAY, ATUI_INLINE, product_branding_v2),
		(ATUI_NODESCR)
	),
	(bios->Reserved9, u8"Reserved9",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->BootUpMVDDCVoltage, u8"BootUpMVDDCVoltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In unit of mv; Was usMinPixelClockPLL_Output;"))
	),
	(bios->BootUpVDDGFXVoltage, u8"BootUpVDDGFXVoltage",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In unit of mv;"))
	),
	(bios->Reserved10, u8"Reserved10",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"New added comparing to previous version"))
	)
)



PPATUI_FUNCIFY(struct, atom_init_reg_index_format, atui_nullstruct,
	(bios->RegIndex, u8"RegIndex",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"MC register index"))
	),
	(bios->PreRegDataLength, u8"PreRegDataLength",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset in ATOM_INIT_REG_DATA_BLOCK.saRegDataBuf"))
	)
)
PPATUI_FUNCIFY(struct, atom_reg_setting_data_block,
		atomtree_init_reg_block,
	(bios->block_id, u8"block ID",
		(ATUI_NODISPLAY, ATUI_INLINE, atom_mc_register_setting_id),
		(ATUI_NODESCR)
	),
	(bios->reg_data, u8"reg_data",
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"reg_data [%02u]",
				(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
			),
			NULL, atomtree->num_data_entries, // deferred start. count
			ATUI_NULL // enum
		)),
		(ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, reg_index_dummy, atomtree_init_reg_block,
	(atomtree->register_index, u8"RegIndexBuf", // start, name
		(ATUI_NODISPLAY, ATUI_DYNARRAY, (
			// Leaf pattern:
			(ATUI_NULL, u8"RegIndexBuf [%02u]",
				(ATUI_NAN, ATUI_INLINE, atom_init_reg_index_format),
				(ATUI_NODESCR)
			),
			NULL, // deferred start
			atomtree->num_index, // count
			ATUI_NULL // enum
		)),
		(ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, reg_settings_dummy, atomtree_init_reg_block,
	(ATUI_NULL, u8"reg_setting_list", // start, name
		(ATUI_NAN, ATUI_DYNARRAY, (
			(ATUI_NULL, u8"reg_setting_list [%02u]",
				(ATUI_NAN, ATUI_PETIOLE, atom_reg_setting_data_block),
				(ATUI_NODESCR)
			),
			atomtree->data_blocks, // deferred start
			atomtree->num_data_blocks, // count
			ATUI_NULL // enum
		)), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, atom_init_reg_block,
		atomtree_init_reg_block,
	(bios->RegIndexTblSize, u8"RegIndexTblSize",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->RegDataBlkSize, u8"RegDataBlkSize",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	// data for RegIndexBuf and RegDataBuf is through atomtree
	(ATUI_NULL, u8"RegIndexBuf",
		(ATUI_NAN, ATUI_PETIOLE, reg_index_dummy),
		(ATUI_NODESCR)
	),
	(ATUI_NULL, u8"RegDataBuf",
		(ATUI_NAN, ATUI_PETIOLE, reg_settings_dummy),
		(ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(union, vram_module_channel_config, atui_nullstruct,
	(bios->ChannelConfig, u8"ChannelConfig",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"channel_combo", 3,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"channel_width", 7,4, ATUI_DEC,
				((LANG_ENG, u8"in number of 2"))
			)
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, npl_rtdelay, atui_nullstruct,
	(bios->NPL_RT, u8"NPL_RT",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"npl_round_trip",   3,0, ATUI_DEC,
				((LANG_ENG, u8"MC_SEQ_CAS_TIMING [28:24]:TCL=CL+NPL_RT-2). Always 2."))
			),
			(u8"reserved",         5,4, ATUI_DEC, (ATUI_NODESCR)),
			(u8"battery_odt_mask", 7,6, ATUI_DEC, (ATUI_NODESCR))
		)), ((LANG_ENG, u8"board dependent parameter:NPL round trip delay, used for calculate memory timing parameters"))
	)
)

PPATUI_FUNCIFY(union, mem_preamble, atui_nullstruct,
	(bios->Preamble, u8"Preamble",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"read",  3,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"write", 7,4, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, vrammodule_misc, atui_nullstruct,
	(bios->Misc, u8"Misc",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"dual_rank",     0,0, ATUI_DEC,
				((LANG_ENG, u8"0=single rank; 1=dual"))
			),
			(u8"Burstlength_8", 1,1, ATUI_DEC,
				((LANG_ENG, u8"0=BL4; 1=BL8"))
			),
			(u8"reserved1",     4,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"dual_cs",       5,5, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved2",     7,6, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, cdr_bandwidth, atui_nullstruct,
	(bios->CDR_Bandwidth, u8"CDR_Bandwidth",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"read_bandwidth",  3,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"write_bandwidth", 7,4, ATUI_DEC, (ATUI_NODESCR))
		)), ((LANG_ENG, u8"clock and data recovery?"))
	)
)

PPATUI_FUNCIFY(union, bank_col_counts, atui_nullstruct,
	(bios->BankCol, u8"BankCol",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"num_columns", 1,0, ATUI_DEC,
				((LANG_ENG, u8"encoded; actual = 8+n bits"))
			),
			(u8"num_banks",   3,2, ATUI_DEC,
				((LANG_ENG, u8"encoded; actual = 2**(n+2) banks"))
			)
		)), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, mc_atom_dram_data_remap, atui_nullstruct,
	(bios->ByteRemapCh0, u8"ByteRemapCh0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_byte_remap_d0_6_0_o),
		(ATUI_NODESCR)
	),
	(bios->ByteRemapCh1, u8"ByteRemapCh1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_byte_remap_d0_6_0_o),
		(ATUI_NODESCR)
	),
	(bios->Byte0BitRemapCh0, u8"Byte0BitRemapCh0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_bit_remap_b0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->Byte1BitRemapCh0, u8"Byte1BitRemapCh0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_bit_remap_b0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->Byte2BitRemapCh0, u8"Byte2BitRemapCh0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_bit_remap_b0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->Byte3BitRemapCh0, u8"Byte3BitRemapCh0",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_bit_remap_b0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->Byte0BitRemapCh1, u8"Byte0BitRemapCh1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_bit_remap_b0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->Byte1BitRemapCh1, u8"Byte1BitRemapCh1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_bit_remap_b0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->Byte2BitRemapCh1, u8"Byte2BitRemapCh1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_bit_remap_b0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->Byte3BitRemapCh1, u8"Byte3BitRemapCh1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_bit_remap_b0_d0_6_0),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_vram_module_v1, atomtree_vram_module,
	(bios->Reserved, u8"Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->EMRSValue, u8"EMRSValue",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MRSValue, u8"MRSValue",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved2, u8"Reserved2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ExtMemoryID, u8"ExtMemoryID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"An external indicator (by hardcode, callback or pin) to tell what is the current memory module"))
	),
	(bios->MemoryType, u8"MemoryType",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		(ATUI_NODESCR)
	),
	(bios->MemoryVendorID, u8"MemoryVendorID",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->MemoryDeviceCfg, u8"MemoryDeviceCfg",
		(ATUI_HEX, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->Row, u8"Row",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of Row,in power of 2;"))
	),
	(bios->Column, u8"Column",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of Column,in power of 2;"))
	),
	(bios->Bank, u8"Bank",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Nunber of Bank;"))
	),
	(bios->Rank, u8"Rank",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of Rank, in power of 2"))
	),
	(bios->ChannelNum, u8"ChannelNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of channel;"))
	),
	(bios->ChannelConfig, u8"ChannelConfig",
		(ATUI_NODISPLAY, ATUI_INLINE, vram_module_channel_config),
		(ATUI_NODESCR)
	),
	(bios->DefaultMVDDQ_ID, u8"DefaultMVDDQ_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Default MVDDQ setting for this memory block, ID linking to MVDDQ info table to find real set-up data;"))
	),
	(bios->DefaultMVDDC_ID, u8"DefaultMVDDC_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Default MVDDC setting for this memory block, ID linking to MVDDC info table to find real set-up data;"))
	),
	(bios->Reserved3, u8"Reserved3",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, atom_vram_module_v2, atomtree_vram_module,
	(bios->Reserved, u8"Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Flags, u8"Flags",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"To enable/disable functionalities based on memory type"))
	),
	(bios->EngineClock, u8"EngineClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Override of default engine clock for particular memory type"))
	),
	(bios->MemoryClock, u8"MemoryClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Override of default memory clock for particular memory type"))
	),
	(bios->MR2, u8"MR2",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"EMRS2 Value is used for GDDR2 and GDDR4 memory type"))
	),
	(bios->MR3, u8"MR3",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"EMRS3 Value is used for GDDR2 and GDDR4 memory type"))
	),
	(bios->EMRSValue, u8"EMRSValue",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MRSValue, u8"MRSValue",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved2, u8"Reserved2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ExtMemoryID, u8"ExtMemoryID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"An external indicator (by hardcode, callback or pin) to tell what is the current memory module"))
	),
	(bios->MemoryType, u8"MemoryType",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		(ATUI_NODESCR)
	),
	(bios->MemoryVendorID, u8"MemoryVendorID",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->MemoryDeviceCfg, u8"MemoryDeviceCfg",
		(ATUI_HEX, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->Row, u8"Row",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of Row in power of 2"))
	),
	(bios->Column, u8"Column",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of Column in power of 2"))
	),
	(bios->Bank, u8"Bank",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Nunber of Bank"))
	),
	(bios->Rank, u8"Rank",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of Rank, in power of 2"))
	),
	(bios->ChannelNum, u8"ChannelNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of channel"))
	),
	(bios->ChannelConfig, u8"ChannelConfig",
		(ATUI_NODISPLAY, ATUI_INLINE, vram_module_channel_config),
		(ATUI_NODESCR)
	),
	(bios->DefaultMVDDQ_ID, u8"DefaultMVDDQ_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Default MVDDQ setting for this memory block, ID linking to MVDDQ info table to find real set-up data;"))
	),
	(bios->DefaultMVDDC_ID, u8"DefaultMVDDC_ID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Default MVDDC setting for this memory block, ID linking to MVDDC info table to find real set-up data;"))
	),
	(bios->RefreshRateFactor, u8"RefreshRateFactor",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved3, u8"Reserved3",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_memory_timing_format_v0, atomtree_vram_module,
	(bios->ClkRange, u8"ClkRange",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"memory clock in 10kHz unit, when target memory clock is below this clock, use this memory timing"))
	),
	(bios->MR0, u8"MR0",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR1, u8"MR1",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->CL, u8"CL",
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
	(bios->tRFC, u8"tRFC",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRCDR, u8"tRCDR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRCDW, u8"tRCDW",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRP, u8"tRP",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRRD, u8"tRRD",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWR, u8"tWR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWTR, u8"tWTR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tPDIX, u8"tPDIX",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tFAW, u8"tFAW",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tAOND, u8"tAOND",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR2, u8"MR2",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"flag to control memory timing calculation. bit0= control EMRS2 Infineon"))
	)
)

PPATUI_FUNCIFY(struct, atom_memory_timing_format_v1, atomtree_vram_module,
	(bios->ClkRange, u8"ClkRange",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"memory clock in 10kHz unit, when target memory clock is below this clock, use this memory timing"))
	),
	(bios->MRS, u8"MRS",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"mode register"))
	),
	(bios->EMRS, u8"EMRS",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"extended mode register"))
	),
	(bios->CL, u8"CL",
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
	(bios->tRFC, u8"tRFC",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRCDR, u8"tRCDR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRCDW, u8"tRCDW",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRP, u8"tRP",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRRD, u8"tRRD",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWR, u8"tWR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWTR, u8"tWTR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tPDIX, u8"tPDIX",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tFAW, u8"tFAW",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tAOND, u8"tAOND",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->flag, u8"flag",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"flag to control memory timing calculation. bit0= control EMRS2 Infineon"))
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
	(bios->tCKRSE, u8"tCKRSE",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCKRSX, u8"tCKRSX",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tFAW32, u8"tFAW32",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR5, u8"MR5",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Terminator, u8"Terminator",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_memory_timing_format_v2, atomtree_vram_module,
	(bios->ClkRange, u8"ClkRange",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"memory clock in 10kHz unit, when target memory clock is below this clock, use this memory timing"))
	),
	(bios->MRS, u8"MRS",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"mode register"))
	),
	(bios->EMRS, u8"EMRS",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"extended mode register"))
	),
	(bios->CL, u8"CL",
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
	(bios->tRFC, u8"tRFC",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRCDR, u8"tRCDR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRCDW, u8"tRCDW",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRP, u8"tRP",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tRRD, u8"tRRD",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWR, u8"tWR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tWTR, u8"tWTR",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tPDIX, u8"tPDIX",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tFAW, u8"tFAW",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tAOND, u8"tAOND",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->flag, u8"flag",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"flag to control memory timing calculation. bit0= control EMRS2 Infineon"))
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
	(bios->tCKRSE, u8"tCKRSE",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tCKRSX, u8"tCKRSX",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->tFAW32, u8"tFAW32",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR4, u8"MR4",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR5, u8"MR5",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Terminator, u8"Terminator",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved, u8"Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, atom_vram_module_v3, atomtree_vram_module,
	(bios->ChannelMapCfg, u8"ChannelMapCfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_shared_chremap_6_0),
		(ATUI_NODESCR)
	),
	(bios->ModuleSize, u8"ModuleSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"size of ATOM_VRAM_MODULE_V3"))
	),
	(bios->DefaultMVDDQ, u8"DefaultMVDDQ",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"board dependent parameter:Default Memory Core Voltage"))
	),
	(bios->DefaultMVDDC, u8"DefaultMVDDC",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"board dependent parameter:Default Memory IO Voltage"))
	),
	(bios->ExtMemoryID, u8"ExtMemoryID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"An external indicator (by hardcode, callback or pin) to tell what is the current memory module"))
	),
	(bios->ChannelNum, u8"ChannelNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"board dependent parameter:Number of channel;"))
	),
	(bios->ChannelSize, u8"ChannelSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"board dependent parameter:32bit or 64bit"))
	),
	(bios->VREFI, u8"VREFI",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"board dependnt parameter: EXT or INT +160mv to -140mv"))
	),
	(bios->NPL_RT, u8"NPL_RT",
		(ATUI_NODISPLAY, ATUI_INLINE, npl_rtdelay),
		(ATUI_NODESCR)
	),
	(bios->Flag, u8"Flag",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"To enable/disable functionalities based on memory type"))
	),

	(bios->DllDisClock, u8"DllDisClock",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"memory DLL will be disable when target memory clock is below this clock"))
	),
	(bios->MR2, u8"MR2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR3, u8"MR3",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MemoryType, u8"MemoryType",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		(ATUI_NODESCR)
	),
	(bios->MemoryVendorID, u8"MemoryVendorID",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->Row, u8"Row",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of Row,in power of 2;"))
	),
	(bios->Column, u8"Column",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of Column,in power of 2;"))
	),
	(bios->Bank, u8"Bank",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Nunber of Bank;"))
	),
	(bios->Rank, u8"Rank",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of Rank, in power of 2"))
	),
	(bios->BurstSize, u8"BurstSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"burst size, 0= burst size=4  1= burst size=8"))
	),
	(bios->DllDisBit, u8"DllDisBit",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"position of DLL Enable/Disable bit in EMRS ( Extended Mode Register )"))
	),
	(bios->RefreshRateFactor, u8"RefreshRateFactor",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"memory refresh rate in unit of ms"))
	),
	(bios->Density, u8"Density",
		(ATUI_DEC, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->Preamble, u8"Preamble",
		(ATUI_NODISPLAY, ATUI_INLINE, mem_preamble),
		(ATUI_NODESCR)
	),
	(bios->MemAttrib, u8"MemAttrib",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Memory Device Addribute, like RDBI/WDBI etc"))
	)
)

PPATUI_FUNCIFY(struct, atom_vram_module_v4, atomtree_vram_module,
	(bios->ChannelMapCfg, u8"ChannelMapCfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_shared_chremap_6_0),
		(ATUI_NODESCR)
	),
	(bios->ModuleSize, u8"ModuleSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"size of ATOM_VRAM_MODULE_V4, make it easy for VBIOS to look for next entry of VRAM_MODULE"))
	),
	(bios->PrivateReserved, u8"PrivateReserved",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!! MC_ARB_RAMCFG (includes NOOFBANK,NOOFRANKS,NOOFROWS,NOOFCOLS"))
	),
	(bios->Reserved, u8"Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ExtMemoryID, u8"ExtMemoryID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"An external indicator (by hardcode, callback or pin) to tell what is the current memory module"))
	),
	(bios->MemoryType, u8"MemoryType",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		(ATUI_NODESCR)
	),
	(bios->ChannelNum, u8"ChannelNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of channels present in this module config"))
	),
	(bios->ChannelWidth, u8"ChannelWidth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"0 - 32 bits; 1 - 64 bits"))
	),
	(bios->Density, u8"Density",
		(ATUI_DEC, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->Flag, u8"Flag",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"To enable/disable functionalities based on memory type"))
	),
	(bios->Misc, u8"Misc",
		(ATUI_NODISPLAY, ATUI_INLINE, vrammodule_misc),
		(ATUI_NODESCR)
	),
	(bios->VREFI, u8"VREFI",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"board dependent parameter"))
	),
	(bios->NPL_RT, u8"NPL_RT",
		(ATUI_NODISPLAY, ATUI_INLINE, npl_rtdelay),
		(ATUI_NODESCR)
	),
	(bios->Preamble, u8"Preamble",
		(ATUI_NODISPLAY, ATUI_INLINE, mem_preamble),
		(ATUI_NODESCR)
	),
	(bios->MemorySize, u8"MemorySize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!! Total memory size in unit of 16MB for CONFIG_MEMSIZE - bit[23:0] zeros"))
	),
	(bios->Reserved2, u8"Reserved2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR2, u8"MR2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR3, u8"MR3",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MemoryVendorID, u8"MemoryVendorID",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->RefreshRateFactor, u8"RefreshRateFactor",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(bios->Reserved3, u8"Reserved3",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, atom_vram_module_v5, atomtree_vram_module,
	(bios->ChannelMapCfg, u8"ChannelMapCfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_shared_chremap_6_0),
		(ATUI_NODESCR)
	),
	(bios->ModuleSize, u8"ModuleSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"size of ATOM_VRAM_MODULE_V4, make it easy for VBIOS to look for next entry of VRAM_MODULE"))
	),
	(bios->PrivateReserved, u8"PrivateReserved",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!! MC_ARB_RAMCFG (includes NOOFBANK,NOOFRANKS,NOOFROWS,NOOFCOLS"))
	),
	(bios->Reserved, u8"Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ExtMemoryID, u8"ExtMemoryID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"An external indicator (by hardcode, callback or pin) to tell what is the current memory module"))
	),
	(bios->MemoryType, u8"MemoryType",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		(ATUI_NODESCR)
	),
	(bios->ChannelNum, u8"ChannelNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of channels present in this module config"))
	),
	(bios->ChannelWidth, u8"ChannelWidth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"0 - 32 bits; 1 - 64 bits"))
	),
	(bios->Density, u8"Density",
		(ATUI_DEC, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->Flag, u8"Flag",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"To enable/disable functionalities based on memory type"))
	),
	(bios->Misc, u8"Misc",
		(ATUI_NODISPLAY, ATUI_INLINE, vrammodule_misc),
		(ATUI_NODESCR)
	),
	(bios->VREFI, u8"VREFI",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"board dependent parameter"))
	),
	(bios->NPL_RT, u8"NPL_RT",
		(ATUI_NODISPLAY, ATUI_INLINE, npl_rtdelay),
		(ATUI_NODESCR)
	),
	(bios->Preamble, u8"Preamble",
		(ATUI_NODISPLAY, ATUI_INLINE, mem_preamble),
		(ATUI_NODESCR)
	),
	(bios->MemorySize, u8"MemorySize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!! Total memory size in unit of 16MB for CONFIG_MEMSIZE - bit[23:0] zeros"))
	),
	(bios->Reserved3, u8"Reserved3",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR2, u8"MR2",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"EMRS2 Value is used for GDDR2 and GDDR4 memory type"))
	),
	(bios->MR3, u8"MR3",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"EMRS3 Value is used for GDDR2 and GDDR4 memory type"))
	),
	(bios->MemoryVendorID, u8"MemoryVendorID",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->RefreshRateFactor, u8"RefreshRateFactor",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(bios->FIFODepth, u8"FIFODepth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"FIFO depth supposes to be detected during vendor detection, but if we dont do vendor detection we have to hardcode FIFO Depth"))
	),
	(bios->CDR_Bandwidth, u8"CDR_Bandwidth",
		(ATUI_NODISPLAY, ATUI_INLINE, cdr_bandwidth),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_vram_module_v6, atomtree_vram_module,
	(bios->ChannelMapCfg, u8"ChannelMapCfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_shared_chremap_6_0),
		(ATUI_NODESCR)
	),
	(bios->ModuleSize, u8"ModuleSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"size of ATOM_VRAM_MODULE_V4, make it easy for VBIOS to look for next entry of VRAM_MODULE"))
	),
	(bios->PrivateReserved, u8"PrivateReserved",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!! MC_ARB_RAMCFG (includes NOOFBANK,NOOFRANKS,NOOFROWS,NOOFCOLS"))
	),
	(bios->Reserved, u8"Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->ExtMemoryID, u8"ExtMemoryID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"An external indicator (by hardcode, callback or pin) to tell what is the current memory module"))
	),
	(bios->MemoryType, u8"MemoryType",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		(ATUI_NODESCR)
	),
	(bios->ChannelNum, u8"ChannelNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of channels present in this module config"))
	),
	(bios->ChannelWidth, u8"ChannelWidth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"0 - 32 bits; 1 - 64 bits"))
	),
	(bios->Density, u8"Density",
		(ATUI_DEC, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->Flag, u8"Flag",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"To enable/disable functionalities based on memory type"))
	),
	(bios->Misc, u8"Misc",
		(ATUI_NODISPLAY, ATUI_INLINE, vrammodule_misc),
		(ATUI_NODESCR)
	),
	(bios->VREFI, u8"VREFI",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"board dependent parameter"))
	),
	(bios->NPL_RT, u8"NPL_RT",
		(ATUI_NODISPLAY, ATUI_INLINE, npl_rtdelay),
		(ATUI_NODESCR)
	),
	(bios->Preamble, u8"Preamble",
		(ATUI_NODISPLAY, ATUI_INLINE, mem_preamble),
		(ATUI_NODESCR)
	),
	(bios->MemorySize, u8"MemorySize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!! Total memory size in unit of 16MB for CONFIG_MEMSIZE - bit[23:0] zeros"))
	),
	(bios->Reserved2, u8"Reserved2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR2, u8"MR2",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"EMRS2 Value is used for GDDR2 and GDDR4 memory type"))
	),
	(bios->MR3, u8"MR3",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"EMRS3 Value is used for GDDR2 and GDDR4 memory type"))
	),
	(bios->MemoryVendorID, u8"MemoryVendorID",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->RefreshRateFactor, u8"RefreshRateFactor",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(bios->FIFODepth, u8"FIFODepth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"FIFO depth supposes to be detected during vendor detection, but if we dont do vendor detection we have to hardcode FIFO Depth"))
	),
	(bios->CDR_Bandwidth, u8"CDR_Bandwidth",
		(ATUI_NODISPLAY, ATUI_INLINE, cdr_bandwidth),
		(ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_vram_module_v7, atomtree_vram_module,
	(bios->ModuleSize, u8"ModuleSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Size of ATOM_VRAM_MODULE_V7"))
	),
	(bios->PrivateReserved, u8"PrivateReserved",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"MC_ARB_RAMCFG (includes NOOFBANK,NOOFRANKS,NOOFROWS,NOOFCOLS)"))
	),
	(bios->EnableChannels, u8"EnableChannels",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"bit vector which indicate which channels are enabled"))
	),
	(bios->ExtMemoryID, u8"ExtMemoryID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Current memory module ID"))
	),
	(bios->MemoryType, u8"MemoryType",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		(ATUI_NODESCR)
	),
	(bios->ChannelNum, u8"ChannelNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of mem. channels supported in this module"))
	),
	(bios->ChannelWidth, u8"ChannelWidth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT"))
	),
	(bios->Density, u8"Density",
		(ATUI_DEC, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->Reserve, u8"Reserve",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"In MC7x, the lower 4 bits are used as bit8-11 of memory size. In other MC code, it's not used."))
	),
	(bios->Misc, u8"Misc",
		(ATUI_NODISPLAY, ATUI_INLINE, vrammodule_misc),
		(ATUI_NODESCR)
	),
	(bios->VREFI, u8"VREFI",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Not used."))
	),
	(bios->NPL_RT, u8"NPL_RT",
		(ATUI_NODISPLAY, ATUI_INLINE, npl_rtdelay),
		(ATUI_NODESCR)
	),
	(bios->Preamble, u8"Preamble",
		(ATUI_NODISPLAY, ATUI_INLINE, mem_preamble),
		(ATUI_NODESCR)
	),
	(bios->MemorySize, u8"MemorySize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Total memory size in unit of 16MB for CONFIG_MEMSIZE - bit[23:0] zeros"))
	),
	(bios->SEQSettingOffset, u8"SEQSettingOffset",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved, u8"Reserved",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR2, u8"MR2",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"EMRS2/MR2 Value."))
	),
	(bios->MR3, u8"MR3",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"EMRS3/MR3 Value."))
	),
	(bios->MemoryVendorID, u8"MemoryVendorID",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->RefreshRateFactor, u8"RefreshRateFactor",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(bios->FIFODepth, u8"FIFODepth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"FIFO depth can be detected during vendor detection, here is hardcoded per memory"))
	),
	(bios->CDR_Bandwidth, u8"CDR_Bandwidth",
		(ATUI_NODISPLAY, ATUI_INLINE, cdr_bandwidth),
		(ATUI_NODESCR)
	),
	(bios->strMemPNString, u8"strMemPNString",
		(ATUI_NAN, ATUI_STRING),
		((LANG_ENG, u8"part number end with '0'."))
	)
)

PPATUI_FUNCIFY(struct, atom_vram_module_v8, atomtree_vram_module,
	(bios->ChannelMapCfg, u8"ChannelMapCfg",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_shared_chremap_7_1),
		(ATUI_NODESCR)
	),
	(bios->ModuleSize, u8"ModuleSize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Size of ATOM_VRAM_MODULE_V7"))
	),
	(bios->McRamCfg, u8"McRamCfg",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"MC_ARB_RAMCFG (includes NOOFBANK,NOOFRANKS,NOOFROWS,NOOFCOLS)"))
	),
	(bios->EnableChannels, u8"EnableChannels",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"bit vector which indicate which channels are enabled"))
	),
	(bios->ExtMemoryID, u8"ExtMemoryID",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Current memory module ID"))
	),
	(bios->MemoryType, u8"MemoryType",
		(ATUI_HEX, ATUI_ENUM, atom_dgpu_vram_type),
		(ATUI_NODESCR)
	),
	(bios->ChannelNum, u8"ChannelNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Number of mem. channels supported in this module"))
	),
	(bios->ChannelWidth, u8"ChannelWidth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT"))
	),
	(bios->Density, u8"Density",
		(ATUI_DEC, ATUI_ENUM, DRAM_DENSITY_e),
		(ATUI_NODESCR)
	),
	(bios->BankCol, u8"BankCol",
		(ATUI_NODISPLAY, ATUI_INLINE, bank_col_counts),
		(ATUI_NODESCR)
	),
	(bios->Misc, u8"Misc",
		(ATUI_NODISPLAY, ATUI_INLINE, vrammodule_misc),
		(ATUI_NODESCR)
	),
	(bios->VREFI, u8"VREFI",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Not used."))
	),
	(bios->Reserved, u8"Reserved",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Not used"))
	),
	(bios->MemorySize, u8"MemorySize",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Total memory size in unit of MB for CONFIG_MEMSIZE zeros"))
	),
	(bios->McTunningSetId, u8"McTunningSetId",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"MC phy registers set per."))
	),
	(bios->RowNum, u8"RowNum",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MR2, u8"MR2",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"EMRS2/MR2 Value."))
	),
	(bios->MR3, u8"MR3",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"EMRS3/MR3 Value."))
	),
	(bios->MemoryVendorID, u8"MemoryVendorID",
		(ATUI_NODISPLAY, ATUI_INLINE, memory_vendor_id),
		(ATUI_NODESCR)
	),
	(bios->RefreshRateFactor, u8"RefreshRateFactor",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"[1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)"))
	),
	(bios->FIFODepth, u8"FIFODepth",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"FIFO depth can be detected during vendor detection, here is hardcoded per memory"))
	),
	(bios->CDR_Bandwidth, u8"CDR_Bandwidth",
		(ATUI_NODISPLAY, ATUI_INLINE, cdr_bandwidth),
		(ATUI_NODESCR)
	),

	(bios->ChannelMapCfg1, u8"ChannelMapCfg1",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_shared_chremap2_7_1),
		((LANG_ENG, u8"channel mapping for channel8~15"))
	),
	(bios->BankMapCfg, u8"BankMapCfg",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->Reserved2, u8"Reserved2",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->strMemPNString, u8"strMemPNString",
		(ATUI_NAN, ATUI_STRING),
		((LANG_ENG, u8"part number end with '0'."))
	)
)

PPATUI_FUNCIFY(struct, atom_vram_info_v1_2, atomtree_vram_info_v1_2,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->NumOfVRAMModule, u8"NumOfVRAMModule",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_vram_info_v1_3, atomtree_vram_info_v1_3,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->MemAdjustTblOffset, u8"MemAdjustTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of ATOM_INIT_REG_BLOCK structure for memory vendor specific MC adjust setting"))
	),
	(bios->MemClkPatchTblOffset, u8"MemClkPatchTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of ATOM_INIT_REG_BLOCK structure for memory clock specific MC setting"))
	),
	(bios->Reserved, u8"Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->VID_PinsShift, u8"VID_PinsShift",
		(ATUI_HEX, ATUI_ARRAY),
		((LANG_ENG, u8"8 bit strap maximum+terminator"))
	),
	(bios->NumOfVRAMModule, u8"NumOfVRAMModule",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_vram_info_v1_4, atomtree_vram_info_v1_4,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->MemAdjustTblOffset, u8"MemAdjustTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of ATOM_INIT_REG_BLOCK structure for memory vendor specific MC adjust setting"))
	),
	(bios->MemClkPatchTblOffset, u8"MemClkPatchTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of ATOM_INIT_REG_BLOCK structure for memory clock specific MC setting"))
	),
	(bios->Reserved, u8"Reserved",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->MemDQ7_0ByteRemap, u8"MemDQ7_0ByteRemap",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_byte_remap_d0_6_0_o),
		(ATUI_NODESCR)
	),
	(bios->MemDQ7_0BitRemap, u8"MemDQ7_0BitRemap",
		(ATUI_NODISPLAY, ATUI_INLINE, mc_seq_bit_remap_b0_d0_6_0),
		(ATUI_NODESCR)
	),
	(bios->VID_PinsShift, u8"VID_PinsShift",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->NumOfVRAMModule, u8"NumOfVRAMModule",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_vram_info_header_v2_1,
		atomtree_vram_info_header_v2_1,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->MemAdjustTblOffset, u8"MemAdjustTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of ATOM_INIT_REG_BLOCK structure for memory vendor specific MC adjust setting"))
	),
	(bios->MemClkPatchTblOffset, u8"MemClkPatchTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of ATOM_INIT_REG_BLOCK structure for memory clock specific MC setting"))
	),
	(bios->PerBytePresetOffset, u8"PerBytePresetOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of ATOM_INIT_REG_BLOCK structure for Per Byte Offset Preset Settings"))
	),
	(bios->Reserved, u8"Reserved",
		(ATUI_HEX, ATUI_ARRAY), (ATUI_NODESCR)
	),
	(bios->NumOfVRAMModule, u8"NumOfVRAMModule",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"indicate number of VRAM module"))
	),
	(bios->MemoryClkPatchTblVer, u8"MemoryClkPatchTblVer",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"version of memory AC timing register list"))
	),
	(bios->VramModuleVer, u8"VramModuleVer",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"indicate ATOM_VRAM_MODUE version"))
	),
	(bios->Reserved2, u8"Reserved2",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(struct, atom_vram_info_header_v2_2,
		atomtree_vram_info_header_v2_2,
	(bios->table_header, u8"table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->MemAdjustTblOffset, u8"MemAdjustTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of ATOM_INIT_REG_BLOCK structure for memory vendor specific MC adjust setting"))
	),
	(bios->MemClkPatchTblOffset, u8"MemClkPatchTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of ATOM_INIT_REG_BLOCK structure for memory clock specific MC setting"))
	),
	(bios->McAdjustPerTileTblOffset, u8"McAdjustPerTileTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of ATOM_INIT_REG_BLOCK structure for Per Byte Offset Preset Settings"))
	),
	(bios->McPhyInitTableOffset, u8"McPhyInitTableOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of ATOM_INIT_REG_BLOCK structure for MC phy init set"))
	),
	(bios->DramDataRemapTblOffset, u8"DramDataRemapTblOffset",
		(ATUI_HEX, ATUI_NOFANCY),
		((LANG_ENG, u8"offset of ATOM_DRAM_DATA_REMAP array to indicate DRAM data lane to GPU mapping"))
	),
	(bios->Reserved1, u8"Reserved1",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->NumOfVRAMModule, u8"NumOfVRAMModule",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"indicate number of VRAM module"))
	),
	(bios->MemoryClkPatchTblVer, u8"MemoryClkPatchTblVer",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"version of memory AC timing register list"))
	),
	(bios->VramModuleVer, u8"VramModuleVer",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"indicate ATOM_VRAM_MODUE version"))
	),
	(bios->McPhyTileNum, u8"McPhyTileNum",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"indicate the MCD tile number which use in DramDataRemapTbl and usMcAdjustPerTileTblOffset"))
	)
)
