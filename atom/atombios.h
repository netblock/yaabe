/*
 * Copyright 2006-2007 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// TODO: modernify atombios.h

/******************************************************************************/
// Portion I: Definitions  shared between VBIOS and Driver
/******************************************************************************/


#ifndef _ATOMBIOS_H
#define _ATOMBIOS_H

#pragma pack(push, 1) // BIOS data must use byte alignment

#define ATOM_VERSION_MAJOR 0x00020000
#define ATOM_VERSION_MINOR 0x00000002

#define ATOM_HEADER_VERSION (ATOM_VERSION_MAJOR | ATOM_VERSION_MINOR)


#define ATOM_DAC_A   0
#define ATOM_DAC_B   1
#define ATOM_EXT_DAC 2

#define ATOM_CRTC1 0
#define ATOM_CRTC2 1
#define ATOM_CRTC3 2
#define ATOM_CRTC4 3
#define ATOM_CRTC5 4
#define ATOM_CRTC6 5

#define ATOM_UNDERLAY_PIPE0 16
#define ATOM_UNDERLAY_PIPE1 17

#define ATOM_CRTC_INVALID 0xFF

#define ATOM_DIGA 0
#define ATOM_DIGB 1

#define ATOM_PPLL1 0
#define ATOM_PPLL2 1
#define ATOM_DCPLL 2
#define ATOM_PPLL0 2
#define ATOM_PPLL3 3

#define ATOM_PHY_PLL0 4
#define ATOM_PHY_PLL1 5

#define ATOM_EXT_PLL1  8
#define ATOM_GCK_DFS   8
#define ATOM_EXT_PLL2  9
#define ATOM_FCH_CLK   9
#define ATOM_EXT_CLOCK 10
#define ATOM_DP_DTO    11

#define ATOM_COMBOPHY_PLL0 20
#define ATOM_COMBOPHY_PLL1 21
#define ATOM_COMBOPHY_PLL2 22
#define ATOM_COMBOPHY_PLL3 23
#define ATOM_COMBOPHY_PLL4 24
#define ATOM_COMBOPHY_PLL5 25

#define ATOM_PPLL_INVALID  0xFF

#define ENCODER_REFCLK_SRC_P1PLL   0
#define ENCODER_REFCLK_SRC_P2PLL   1
#define ENCODER_REFCLK_SRC_DCPLL   2
#define ENCODER_REFCLK_SRC_EXTCLK  3
#define ENCODER_REFCLK_SRC_INVALID 0xFF

#define ATOM_SCALER_DISABLE   0 // For Fudo, it's bypass and auto-cengter & no replication
#define ATOM_SCALER_CENTER    1 // For Fudo, it's bypass and auto-center & auto replication
#define ATOM_SCALER_EXPANSION 2 // For Fudo, it's 2 Tap alpha blending mode
#define ATOM_SCALER_MULTI_EX  3 // For Fudo only, it's multi-tap mode only used to drive TV or CV, only used by Bios

#define ATOM_DISABLE            0
#define ATOM_ENABLE             1
#define ATOM_LCD_BLOFF          2
#define ATOM_LCD_BLON           3
#define ATOM_LCD_BL_BRIGHTNESS_CONTROL 4
#define ATOM_LCD_SELFTEST_START 5
#define ATOM_LCD_SELFTEST_STOP  6
#define ATOM_ENCODER_INIT       7
#define ATOM_INIT               7
#define ATOM_GET_STATUS         8

#define ATOM_BLANKING     1
#define ATOM_BLANKING_OFF 0


#define ATOM_CRT1 0
#define ATOM_CRT2 1

#define ATOM_TV_NTSC  1
#define ATOM_TV_NTSCJ 2
#define ATOM_TV_PAL   3
#define ATOM_TV_PALM  4
#define ATOM_TV_PALCN 5
#define ATOM_TV_PALN  6
#define ATOM_TV_PAL60 7
#define ATOM_TV_SECAM 8
#define ATOM_TV_CV    16

#define ATOM_DAC1_PS2  1
#define ATOM_DAC1_CV   2
#define ATOM_DAC1_NTSC 3
#define ATOM_DAC1_PAL  4

#define ATOM_DAC2_PS2  ATOM_DAC1_PS2
#define ATOM_DAC2_CV   ATOM_DAC1_CV
#define ATOM_DAC2_NTSC ATOM_DAC1_NTSC
#define ATOM_DAC2_PAL  ATOM_DAC1_PAL

#define ATOM_PM_ON      0
#define ATOM_PM_STANDBY 1
#define ATOM_PM_SUSPEND 2
#define ATOM_PM_OFF     3

// For ATOM_LVDS_INFO_V12
// Bit0:{=0:single, =1:dual},
// Bit1 {=0:666RGB, =1:888RGB},
// Bit2:3:{Grey level}
// Bit4:{=0:LDI format for RGB888, =1 FPDI format for RGB888}
#define ATOM_PANEL_MISC_DUAL             0x00000001
#define ATOM_PANEL_MISC_888RGB           0x00000002
#define ATOM_PANEL_MISC_GREY_LEVEL       0x0000000C
#define ATOM_PANEL_MISC_FPDI             0x00000010
#define ATOM_PANEL_MISC_GREY_LEVEL_SHIFT 2
#define ATOM_PANEL_MISC_SPATIAL          0x00000020
#define ATOM_PANEL_MISC_TEMPORAL         0x00000040
#define ATOM_PANEL_MISC_API_ENABLED      0x00000080

#define MEMTYPE_DDR1 "DDR1"
#define MEMTYPE_DDR2 "DDR2"
#define MEMTYPE_DDR3 "DDR3"
#define MEMTYPE_DDR4 "DDR4"

#define ASIC_BUS_TYPE_PCI  "PCI"
#define ASIC_BUS_TYPE_AGP  "AGP"
#define ASIC_BUS_TYPE_PCIE "PCI_EXPRESS"

// Maximum size of that FireGL flag string
#define ATOM_FIREGL_FLAG_STRING "FGL" // Flag used to enable FireGL Support
#define ATOM_MAX_SIZE_OF_FIREGL_FLAG_STRING 3 // sizeof( ATOM_FIREGL_FLAG_STRING )

#define ATOM_FAKE_DESKTOP_STRING "DSK" // Flag used to enable mobile ASIC on Desktop
#define ATOM_MAX_SIZE_OF_FAKE_DESKTOP_STRING  ATOM_MAX_SIZE_OF_FIREGL_FLAG_STRING

#define ATOM_M54T_FLAG_STRING "M54T" // Flag used to enable M54T Support
#define ATOM_MAX_SIZE_OF_M54T_FLAG_STRING 4 // sizeof( ATOM_M54T_FLAG_STRING )

#define HW_ASSISTED_I2C_STATUS_FAILURE 2
#define HW_ASSISTED_I2C_STATUS_SUCCESS 1


// Define offset to location of ROM header.
// #define OFFSET_TO_POINTER_TO_ATOM_ROM_HEADER 0x00000048L
#define OFFSET_TO_ATOM_ROM_IMAGE_SIZE 0x00000002L

#define OFFSET_TO_ATOMBIOS_ASIC_BUS_MEM_TYPE  0x94
#define MAXSIZE_OF_ATOMBIOS_ASIC_BUS_MEM_TYPE 20    // including the terminator 0x0!
#define OFFSET_TO_GET_ATOMBIOS_STRINGS_NUMBER 0x002f
#define OFFSET_TO_GET_ATOMBIOS_STRINGS_START  0x006e

/******************************************************************************/
// Common header for all tables (Data table, Command table).
// Every table pointed  _ATOM_MASTER_DATA_TABLE has this common header.
// And the pointer actually points to this header.
/******************************************************************************/
/* duplicate
struct atom_common_table_header {
	uint16_t StructureSize;
	uint8_t  TableFormatRevision;  // Change it when the Parser is not backward compatible
	uint8_t  TableContentRevision; // Change it only when the table needs to change but the firmware
                                   // Image can't be updated, while Driver needs to carry the new table!
};
*/

/******************************************************************************/
// Structure stores the ROM header.
/******************************************************************************/
struct atom_rom_header_v1_1 { // TODO is this actually v1.1?
	struct atom_common_table_header table_header;
	uint8_t  FirmWareSignature[4]; // Signature to distinguish between Atombios and non-atombios, atombios should init it as "ATOM", don't change the position
	uint16_t BiosRuntimeSegmentAddress;
	uint16_t ProtectedModeInfoOffset;
	uint16_t ConfigFilenameOffset;
	uint16_t CRC_BlockOffset;
	uint16_t BIOS_BootupMessageOffset;
	uint16_t Int10Offset;
	uint16_t PciBusDevInitCode;
	uint16_t IoBaseAddress;
	uint16_t SubsystemVendorID;
	uint16_t SubsystemID;
	uint16_t PCI_InfoOffset;
	uint16_t MasterCommandTableOffset; // Offest for SW to get all command table offsets, Don't change the position
	uint16_t MasterDataTableOffset;    // Offest for SW to get all data table offsets, Don't change the position
	uint8_t  ExtendedFunctionCode;
	uint8_t  Reserved;
};


struct atom_rom_header_v2_1 {
	struct atom_common_table_header table_header;
	uint8_t  FirmWareSignature[4]; // Signature to distinguish between Atombios and non-atombios, atombios should init it as "ATOM", don't change the position
	uint16_t BiosRuntimeSegmentAddress;
	uint16_t ProtectedModeInfoOffset;
	uint16_t ConfigFilenameOffset;
	uint16_t CRC_BlockOffset;
	uint16_t BIOS_BootupMessageOffset;
	uint16_t Int10Offset;
	uint16_t PciBusDevInitCode;
	uint16_t IoBaseAddress;
	uint16_t SubsystemVendorID;
	uint16_t SubsystemID;
	uint16_t PCI_InfoOffset;
	uint16_t MasterCommandTableOffset; // Offest for SW to get all command table offsets, Don't change the position
	uint16_t MasterDataTableOffset;    // Offest for SW to get all data table offsets, Don't change the position
	uint8_t  ExtendedFunctionCode;
	uint8_t  Reserved;
	uint32_t PSPDirTableOffset;
};


/******************************************************************************/
// Command Table Portion
/******************************************************************************/
/******************************************************************************/
// Structures used in Command.mtb
/******************************************************************************/
struct atom_master_list_of_command_tables {
	struct atom_common_table_header table_header;
	uint16_t ASIC_Init;                        // Function Table, used by various SW components,latest version 1.1
	uint16_t GetDisplaySurfaceSize;            // Atomic Table,  Used by Bios when enabling HW ICON
	uint16_t ASIC_RegistersInit;               // Atomic Table,  indirectly used by various SW components,called from ASIC_Init
	uint16_t VRAM_BlockVenderDetection;        // Atomic Table,  used only by Bios
	uint16_t DIGxEncoderControl;               // Only used by Bios
	uint16_t MemoryControllerInit;             // Atomic Table,  indirectly used by various SW components,called from ASIC_Init
	uint16_t EnableCRTCMemReq;                 // Function Table,directly used by various SW components,latest version 2.1
	uint16_t MemoryParamAdjust;                // Atomic Table,  indirectly used by various SW components,called from SetMemoryClock if needed
	uint16_t DVOEncoderControl;                // Function Table,directly used by various SW components,latest version 1.2
	uint16_t GPIOPinControl;                   // Atomic Table,  only used by Bios
	uint16_t SetEngineClock;                   // Function Table,directly used by various SW components,latest version 1.1
	uint16_t SetMemoryClock;                   // Function Table,directly used by various SW components,latest version 1.1
	uint16_t SetPixelClock;                    // Function Table,directly used by various SW components,latest version 1.2
	uint16_t EnableDispPowerGating;            // Atomic Table,  indirectly used by various SW components,called from ASIC_Init
	uint16_t ResetMemoryDLL;                   // Atomic Table,  indirectly used by various SW components,called from SetMemoryClock
	uint16_t ResetMemoryDevice;                // Atomic Table,  indirectly used by various SW components,called from SetMemoryClock
	uint16_t MemoryPLLInit;                    // Atomic Table,  used only by Bios
	uint16_t AdjustDisplayPll;                 // Atomic Table,  used by various SW componentes.
	uint16_t AdjustMemoryController;           // Atomic Table,  indirectly used by various SW components,called from SetMemoryClock
	uint16_t EnableASIC_StaticPwrMgt;          // Atomic Table,  only used by Bios
	uint16_t SetUniphyInstance;                // Atomic Table,  only used by Bios
	uint16_t DAC_LoadDetection;                // Atomic Table,  directly used by various SW components,latest version 1.2
	uint16_t LVTMAEncoderControl;              // Atomic Table,directly used by various SW components,latest version 1.3
	uint16_t HW_Misc_Operation;                // Atomic Table,  directly used by various SW components,latest version 1.1
	uint16_t DAC1EncoderControl;               // Atomic Table,  directly used by various SW components,latest version 1.1
	uint16_t DAC2EncoderControl;               // Atomic Table,  directly used by various SW components,latest version 1.1
	uint16_t DVOOutputControl;                 // Atomic Table,  directly used by various SW components,latest version 1.1
	uint16_t CV1OutputControl;                 // Atomic Table,  Atomic Table,  Obsolete from Ry6xx, use DAC2 Output instead
	uint16_t GetConditionalGoldenSetting;      // Only used by Bios
	uint16_t SMC_Init;                         // Function Table,directly used by various SW components,latest version 1.1
	uint16_t PatchMCSetting;                   // only used by BIOS
	uint16_t MC_SEQ_Control;                   // only used by BIOS
	uint16_t Gfx_Harvesting;                   // Atomic Table,  Obsolete from Ry6xx, Now only used by BIOS for GFX harvesting
	uint16_t EnableScaler;                     // Atomic Table,  used only by Bios
	uint16_t BlankCRTC;                        // Atomic Table,  directly used by various SW components,latest version 1.1
	uint16_t EnableCRTC;                       // Atomic Table,  directly used by various SW components,latest version 1.1
	uint16_t GetPixelClock;                    // Atomic Table,  directly used by various SW components,latest version 1.1
	uint16_t EnableVGA_Render;                 // Function Table,directly used by various SW components,latest version 1.1
	uint16_t GetSCLKOverMCLKRatio;             // Atomic Table,  only used by Bios
	uint16_t SetCRTC_Timing;                   // Atomic Table,  directly used by various SW components,latest version 1.1
	uint16_t SetCRTC_OverScan;                 // Atomic Table,  used by various SW components,latest version 1.1
	uint16_t GetSMUClockInfo;                  // Atomic Table,  used only by Bios
	uint16_t SelectCRTC_Source;                // Atomic Table,  directly used by various SW components,latest version 1.1
	uint16_t EnableGraphSurfaces;              // Atomic Table,  used only by Bios
	uint16_t UpdateCRTC_DoubleBufferRegisters; // Atomic Table,  used only by Bios
	uint16_t LUT_AutoFill;                     // Atomic Table,  only used by Bios
	uint16_t SetDCEClock;                      // Atomic Table,  start from DCE11.1, shared by driver and VBIOS, change DISPCLK and DPREFCLK
	uint16_t GetMemoryClock;                   // Atomic Table,  directly used by various SW components,latest version 1.1
	uint16_t GetEngineClock;                   // Atomic Table,  directly used by various SW components,latest version 1.1
	uint16_t SetCRTC_UsingDTDTiming;           // Atomic Table,  directly used by various SW components,latest version 1.1
	uint16_t ExternalEncoderControl;           // Atomic Table,  directly used by various SW components,latest version 2.1
	uint16_t LVTMAOutputControl;               // Atomic Table,  directly used by various SW components,latest version 1.1
	uint16_t VRAM_BlockDetectionByStrap;       // Atomic Table,  used only by Bios
	uint16_t MemoryCleanUp;                    // Atomic Table,  only used by Bios
	uint16_t ProcessI2cChannelTransaction;     // Function Table,only used by Bios
	uint16_t WriteOneByteToHWAssistedI2C;      // Function Table,indirectly used by various SW components
	uint16_t ReadHWAssistedI2CStatus;          // Atomic Table,  indirectly used by various SW components
	uint16_t SpeedFanControl;                  // Function Table,indirectly used by various SW components,called from ASIC_Init
	uint16_t PowerConnectorDetection;          // Atomic Table,  directly used by various SW components,latest version 1.1
	uint16_t MC_Synchronization;               // Atomic Table,  indirectly used by various SW components,called from SetMemoryClock
	uint16_t ComputeMemoryEnginePLL;           // Atomic Table,  indirectly used by various SW components,called from SetMemory/EngineClock
	uint16_t Gfx_Init;                         // Atomic Table,  indirectly used by various SW components,called from SetMemory or SetEngineClock
	uint16_t VRAM_GetCurrentInfoBlock;         // Atomic Table,  used only by Bios
	uint16_t DynamicMemorySettings;            // Atomic Table,  indirectly used by various SW components,called from SetMemoryClock
	uint16_t MemoryTraining;                   // Atomic Table,  used only by Bios
	uint16_t EnableSpreadSpectrumOnPPLL;       // Atomic Table,  directly used by various SW components,latest version 1.2
	uint16_t TMDSAOutputControl;               // Atomic Table,  directly used by various SW components,latest version 1.1
	uint16_t SetVoltage;                       // Function Table,directly and/or indirectly used by various SW components,latest version 1.1
	uint16_t DAC1OutputControl;                // Atomic Table,  directly used by various SW components,latest version 1.1
	uint16_t ReadEfuseValue;                   // Atomic Table,  directly used by various SW components,latest version 1.1
	uint16_t ComputeMemoryClockParam;          // Function Table,only used by Bios, obsolete soon.Switch to use "ReadEDIDFromHWAssistedI2C"
	uint16_t ClockSource;                      // Atomic Table,  indirectly used by various SW components,called from ASIC_Init
	uint16_t MemoryDeviceInit;                 // Atomic Table,  indirectly used by various SW components,called from SetMemoryClock
	uint16_t GetDispObjectInfo;                // Atomic Table,  indirectly used by various SW components,called from EnableVGARender
	uint16_t DIG1EncoderControl;               // Atomic Table,directly used by various SW components,latest version 1.1
	uint16_t DIG2EncoderControl;               // Atomic Table,directly used by various SW components,latest version 1.1
	uint16_t DIG1TransmitterControl;           // Atomic Table,directly used by various SW components,latest version 1.1
	uint16_t DIG2TransmitterControl;           // Atomic Table,directly used by various SW components,latest version 1.1
	uint16_t ProcessAuxChannelTransaction;     // Function Table,only used by Bios
	uint16_t DPEncoderService;                 // Function Table,only used by Bios
	uint16_t GetVoltageInfo;                   // Function Table,only used by Bios since SI
};

// For backward compatible
#define ReadEDIDFromHWAssistedI2C     ProcessI2cChannelTransaction
#define DPTranslatorControl           DIG2EncoderControl
#define UNIPHYTransmitterControl      DIG1TransmitterControl
#define LVTMATransmitterControl       DIG2TransmitterControl
#define SetCRTC_DPM_State             GetConditionalGoldenSetting
#define ASIC_StaticPwrMgtStatusChange SetUniphyInstance
#define HPDInterruptService           ReadHWAssistedI2CStatus
#define EnableVGA_Access              GetSCLKOverMCLKRatio
#define EnableYUV                     GetDispObjectInfo
#define DynamicClockGating            EnableDispPowerGating
#define SetupHWAssistedI2CStatus      ComputeMemoryClockParam
#define DAC2OutputControl             ReadEfuseValue

#define TMDSAEncoderControl           PatchMCSetting
#define LVDSEncoderControl            MC_SEQ_Control
#define LCD1OutputControl             HW_Misc_Operation
#define TV1OutputControl              Gfx_Harvesting
#define TVEncoderControl              SMC_Init
#define EnableHW_IconCursor           SetDCEClock
#define SetCRTC_Replication           GetSMUClockInfo

#define MemoryRefreshConversion       Gfx_Init

/******************************************************************************/
// Structures used in every command table
/******************************************************************************/
struct atom_table_attribute {
	uint16_t WS_SizeInBytes:8;   // [7:0]=Size of workspace in Bytes (in multiple of a dword),
	uint16_t PS_SizeInBytes:7;   // [14:8]=Size of parameter space in Bytes (multiple of a dword),
	uint16_t UpdatedByUtility:1; // [15]=Table updated by utility flag
};

/******************************************************************************/
// Common header for all command tables.
// Every table pointed by _ATOM_MASTER_COMMAND_TABLE has this common header.
// And the pointer actually points to this header.
/******************************************************************************/
struct atom_common_rom_command_table_header {
	struct atom_common_table_header table_header;
	struct atom_table_attribute TableAttribute;
};

/******************************************************************************/
// Structures used by ComputeMemoryEnginePLLTable
/******************************************************************************/

#define COMPUTE_MEMORY_PLL_PARAM 1
#define COMPUTE_ENGINE_PLL_PARAM 2
#define ADJUST_MC_SETTING_PARAM  3

/******************************************************************************/
// Structures used by AdjustMemoryControllerTable
/******************************************************************************/
struct atom_adjust_memory_clock_freq {
	uint32_t ClockFreq:24;
	uint32_t MemoryModuleNumber:7; // BYTE_3[6:0]
	uint32_t PointerReturnFlag:1;  // BYTE_3[7]=1 - Return the pointer to the right Data Block; BYTE_3[7]=0 - Program the right Data Block
};
#define POINTER_RETURN_FLAG 0x80

struct compute_memory_engine_pll_parameters {
	uint32_t Clock;    // When returen, it's the re-calculated clock based on given Fb_div Post_Div and ref_div
	uint8_t  Action;   // 0:reserved //1:Memory //2:Engine
	uint8_t  Reserved; // may expand to return larger Fbdiv later
	uint8_t  FbDiv;    // return value
	uint8_t  PostDiv;  // return value
};

struct compute_memory_engine_pll_parameters_v2 {
	uint32_t Clock;   // When return, [23:0] return real clock
	uint8_t  Action;  // 0:reserved;COMPUTE_MEMORY_PLL_PARAM:Memory;COMPUTE_ENGINE_PLL_PARAM:Engine. it return ref_div to be written to register
	uint16_t FbDiv;   // return Feedback value to be written to register
	uint8_t  PostDiv; // return post div to be written to register
};

#define SET_CLOCK_FREQ_MASK                   0x00FFFFFF // Clock change tables only take bit [23:0] as the requested clock value
#define USE_NON_BUS_CLOCK_MASK                0x01000000 // Applicable to both memory and engine clock change, when set, it uses another clock as the temporary clock (engine uses memory and vice versa)
#define USE_MEMORY_SELF_REFRESH_MASK          0x02000000 // Only applicable to memory clock change, when set, using memory self refresh during clock transition
#define SKIP_INTERNAL_MEMORY_PARAMETER_CHANGE 0x04000000 // Only applicable to memory clock change, when set, the table will skip predefined internal memory parameter change
#define FIRST_TIME_CHANGE_CLOCK               0x08000000 // Applicable to both memory and engine clock change,when set, it means this is 1st time to change clock after ASIC bootup
#define SKIP_SW_PROGRAM_PLL                   0x10000000 // Applicable to both memory and engine clock change, when set, it means the table will not program SPLL/MPLL
#define USE_SS_ENABLED_PIXEL_CLOCK            USE_NON_BUS_CLOCK_MASK

#define b3USE_NON_BUS_CLOCK_MASK                0x01 // Applicable to both memory and engine clock change, when set, it uses another clock as the temporary clock (engine uses memory and vice versa)
#define b3USE_MEMORY_SELF_REFRESH               0x02 // Only applicable to memory clock change, when set, using memory self refresh during clock transition
#define b3SKIP_INTERNAL_MEMORY_PARAMETER_CHANGE 0x04 // Only applicable to memory clock change, when set, the table will skip predefined internal memory parameter change
#define b3FIRST_TIME_CHANGE_CLOCK               0x08 // Applicable to both memory and engine clock change,when set, it means this is 1st time to change clock after ASIC bootup
#define b3SKIP_SW_PROGRAM_PLL                   0x10 // Applicable to both memory and engine clock change, when set, it means the table will not program SPLL/MPLL
#define b3DRAM_SELF_REFRESH_EXIT                0x20 // Applicable to DRAM self refresh exit only. when set, it means it will go to program DRAM self refresh exit path
#define b3SRIOV_INIT_BOOT                       0x40 // Use by HV GPU driver only, to load uCode. for ASIC_InitTable SCLK parameter only
#define b3SRIOV_LOAD_UCODE                      0x40 // Use by HV GPU driver only, to load uCode. for ASIC_InitTable SCLK parameter only
#define b3SRIOV_SKIP_ASIC_INIT                  0x02 // Use by HV GPU driver only, skip ASIC_Init for primary adapter boot. for ASIC_InitTable SCLK parameter only

struct atom_compute_clock_freq {
	uint32_t ClockFreq:24;       // in unit of 10kHz
	uint32_t ComputeClockFlag:8; // =1: COMPUTE_MEMORY_PLL_PARAM, =2: COMPUTE_ENGINE_PLL_PARAM
};

struct atom_s_mpll_fb_divider {
	// TODO Q16.16?
	uint16_t FbDivFrac;
	uint16_t FbDiv;
};

struct compute_memory_engine_pll_parameters_v3 {
	union {
		struct atom_compute_clock_freq Clock; // Input Parameter
		uint32_t ClockParams; // uint32_t access for BE
		struct atom_s_mpll_fb_divider FbDiv; // Output Parameter
	};
	uint8_t  RefDiv;   // Output Parameter
	uint8_t  PostDiv;  // Output Parameter
	uint8_t  CntlFlag; // Output Parameter
	uint8_t  Reserved;
};

// ucCntlFlag
#define ATOM_PLL_CNTL_FLAG_PLL_POST_DIV_EN  1
#define ATOM_PLL_CNTL_FLAG_MPLL_VCO_MODE    2
#define ATOM_PLL_CNTL_FLAG_FRACTION_DISABLE 4
#define ATOM_PLL_CNTL_FLAG_SPLL_ISPARE_9    8


// V4 are only used for APU which PLL outside GPU
struct compute_memory_engine_pll_parameters_v4 {
	uint32_t Clock:24;  // Input= target clock, output = actual clock
	uint32_t PostDiv:8; // return parameter: post divider which is used to program to register directly
};

struct compute_memory_engine_pll_parameters_v5 {
	union {
		struct atom_compute_clock_freq Clock; // Input Parameter
		uint32_t ClockParams; // uint32_t access for BE
		struct atom_s_mpll_fb_divider FbDiv;  // Output Parameter
	};
	uint8_t  RefDiv;  // Output Parameter
	uint8_t  PostDiv; // Output Parameter
	union {
		uint8_t  CntlFlag;  // Output Flags
		uint8_t  InputFlag; // Input Flags. ucInputFlag[0] - Strobe(1)/Performance(0) mode
	};
	uint8_t  Reserved;
};


struct compute_gpu_clock_input_parameters_v1_6 {
	struct atom_compute_clock_freq Clock; // Input Parameter
	uint32_t Reserved[2];
};

// ATOM_COMPUTE_CLOCK_FREQ.ulComputeClockFlag
#define COMPUTE_GPUCLK_INPUT_FLAG_CLK_TYPE_MASK  0x0f
#define COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK 0x00
#define COMPUTE_GPUCLK_INPUT_FLAG_SCLK           0x01


struct compute_gpu_clock_output_parameters_v1_6 {
	struct compute_memory_engine_pll_parameters_v4 Clock; // Output Parameter: ucPostDiv=DFS divider
	struct atom_s_mpll_fb_divider FbDiv; // Output Parameter: PLL FB divider
	uint8_t  PllRefDiv;   // Output Parameter: PLL ref divider
	uint8_t  PllPostDiv;  // Output Parameter: PLL post divider
	uint8_t  PllCntlFlag; // Output Flags: control flag
	uint8_t  Reserved;
};

// ucPllCntlFlag
#define SPLL_CNTL_FLAG_VCO_MODE_MASK            0x03

struct compute_gpu_clock_input_parameters_v1_7 {
	struct atom_compute_clock_freq Clock; // Input Parameter
	uint32_t Reserved[5];
};

// ATOM_COMPUTE_CLOCK_FREQ.ulComputeClockFlag
#define COMPUTE_GPUCLK_INPUT_FLAG_CLK_TYPE_MASK  0x0f
#define COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK 0x00
#define COMPUTE_GPUCLK_INPUT_FLAG_SCLK           0x01

struct compute_gpu_clock_output_parameters_v1_7 {
	struct compute_memory_engine_pll_parameters_v4 Clock; // Output Parameter: ucPostDiv=DFS divider
	// TODO Q16.16?
	uint16_t Sclk_fcw_frac; // fractional divider of fcw = usSclk_fcw_frac/65536
	uint16_t Sclk_fcw_int;  // integer divider of fcwc
	uint8_t  SclkPostDiv;   // PLL post divider = 2^ucSclkPostDiv
	uint8_t  SclkVcoMode;   // 0: 4G~8Ghz, 1:3G~6Ghz,3: 2G~4Ghz, 2:Reserved
	uint8_t  SclkPllRange;  // GreenTable SCLK PLL range entry index ( 0~7 )
	uint8_t  SscEnable;
	uint16_t Ssc_fcw1_frac; // fcw1_frac when SSC enable
	uint16_t Ssc_fcw1_int;  // fcw1_int when SSC enable
	uint16_t Reserved;
	uint16_t Pcc_fcw_int;
	uint16_t Ssc_fcw_slew_frac; // fcw_slew_frac when SSC enable
	uint16_t Pcc_fcw_slew_frac;
};

// ucInputFlag
#define ATOM_PLL_INPUT_FLAG_PLL_STROBE_MODE_EN 1 // 1-StrobeMode, 0-PerformanceMode

// use for ComputeMemoryClockParamTable
struct compute_memory_clock_param_parameters_v2_1 {
	union {
		uint32_t Clock;
		struct atom_s_mpll_fb_divider FbDiv; // Output:UPPER_WORD=FB_DIV_INTEGER,  LOWER_WORD=FB_DIV_FRAC shl (16-FB_FRACTION_BITS)
	};
	uint8_t  DllSpeed;        // Output
	uint8_t  PostDiv;         // Output
	union {
		uint8_t  InputFlag;   // Input : ATOM_PLL_INPUT_FLAG_PLL_STROBE_MODE_EN: 1-StrobeMode, 0-PerformanceMode
		uint8_t  PllCntlFlag; // Output:
	};
	uint8_t  BWCntl;
};

// definition of ucInputFlag
#define MPLL_INPUT_FLAG_STROBE_MODE_EN 0x01
// definition of ucPllCntlFlag
#define MPLL_CNTL_FLAG_VCO_MODE_MASK   0x03
#define MPLL_CNTL_FLAG_BYPASS_DQ_PLL   0x04
#define MPLL_CNTL_FLAG_QDR_ENABLE      0x08
#define MPLL_CNTL_FLAG_AD_HALF_RATE    0x10

// MPLL_CNTL_FLAG_BYPASS_AD_PLL has a wrong name, should be BYPASS_DQ_PLL
#define MPLL_CNTL_FLAG_BYPASS_AD_PLL   0x04

// use for ComputeMemoryClockParamTable
struct compute_memory_clock_param_parameters_v2_2 {
	struct compute_memory_engine_pll_parameters_v4 Clock;
	uint32_t Reserved;
};

struct compute_memory_clock_param_parameters_v2_3 {
	struct compute_memory_engine_pll_parameters_v4 Clock;
	// TODO Q16.16?
	uint16_t Mclk_fcw_frac; // fractional divider of fcw = usSclk_fcw_frac/65536
	uint16_t Mclk_fcw_int;  // integer divider of fcwc
};

// Input parameter of DynamicMemorySettingsTable
// when ATOM_COMPUTE_CLOCK_FREQ.ulComputeClockFlag = COMPUTE_MEMORY_PLL_PARAM
struct dynamice_memory_settings_parameter {
	struct atom_compute_clock_freq Clock;
	uint32_t Reserved[2];
};

// Input parameter of DynamicMemorySettingsTable
// when ATOM_COMPUTE_CLOCK_FREQ.ulComputeClockFlag == COMPUTE_ENGINE_PLL_PARAM
struct dynamice_engine_settings_parameter {
	struct atom_compute_clock_freq Clock;
	uint32_t MemoryClock;
	uint32_t Reserved;
};

// Input parameter of DynamicMemorySettingsTable ver2.1 and above
// when ATOM_COMPUTE_CLOCK_FREQ.ulComputeClockFlag == ADJUST_MC_SETTING_PARAM
struct dynamice_mc_dpm_settings_parameter {
	struct atom_compute_clock_freq Clock;
	uint8_t  MclkDPMState;
	uint8_t  Reserved[3];
	uint32_t Reserved2;
};

// ucMclkDPMState
#define DYNAMIC_MC_DPM_SETTING_LOW_DPM_STATE    0
#define DYNAMIC_MC_DPM_SETTING_MEDIUM_DPM_STATE 1
#define DYNAMIC_MC_DPM_SETTING_HIGH_DPM_STATE   2

union dynamice_memory_settings_parameter_v2_1 {
	struct dynamice_memory_settings_parameter MCReg;
	struct dynamice_engine_settings_parameter MCArbReg;
	struct dynamice_mc_dpm_settings_parameter DPMMCReg;
};


/******************************************************************************/
// Structures used by SetEngineClockTable
/******************************************************************************/
struct set_engine_clock_parameters {
	uint32_t TargetEngineClock; // In 10Khz unit
};

struct set_engine_clock_ps_allocation {
	uint32_t TargetEngineClock; // In 10Khz unit
	struct compute_memory_engine_pll_parameters Reserved;
};

struct set_engine_clock_ps_allocation_v1_2 {
	uint32_t TargetEngineClock; // In 10Khz unit
	struct compute_gpu_clock_input_parameters_v1_7 Reserved;
};


/******************************************************************************/
// Structures used by SetMemoryClockTable
/******************************************************************************/
struct set_memory_clock_parameters {
	uint32_t TargetMemoryClock; // In 10Khz unit
};

//#define COMPUTE_MEMORY_ENGINE_PLL_PARAMETERS_PS_ALLOCATION compute_memory_engine_pll_parameters
struct set_memory_clock_ps_allocation {
	uint32_t TargetMemoryClock; // In 10Khz unit
	struct compute_memory_engine_pll_parameters Reserved;
};

/******************************************************************************/
// Structures used by ASIC_Init.ctb
/******************************************************************************/
struct asic_init_parameters {
	uint32_t DefaultEngineClock; // In 10Khz unit
	uint32_t DefaultMemoryClock; // In 10Khz unit
};

struct asic_init_ps_allocation {
	struct asic_init_parameters ASICInitClocks;
	struct set_engine_clock_ps_allocation Reserved; // Caller doesn't need to init this structure
};

struct asic_init_clock_parameters {
	uint32_t ClkFreqIn10Khz:24;
	uint32_t ucClkFlag:8;
};

struct asic_init_parameters_v1_2 {
	struct asic_init_clock_parameters SclkClock; // In 10Khz unit
	struct asic_init_clock_parameters MemClock;  // In 10Khz unit
};

struct asic_init_ps_allocation_v1_2 {
	struct asic_init_parameters_v1_2 ASICInitClocks;
	uint32_t Reserved[8];
};

/******************************************************************************/
// Structure used by DynamicClockGatingTable.ctb
/******************************************************************************/
struct dynamic_clock_gating_parameters {
	uint8_t  Enable; // ATOM_ENABLE or ATOM_DISABLE
	uint8_t  Padding[3];
};
#define DYNAMIC_CLOCK_GATING_PS_ALLOCATION  DYNAMIC_CLOCK_GATING_PARAMETERS

/******************************************************************************/
// Structure used by EnableDispPowerGatingTable.ctb
/******************************************************************************/
/* duplicate
struct enable_disp_power_gating_parameters_v2_1 {
	uint8_t  DispPipeId; // ATOM_CRTC1, ATOM_CRTC2, ...
	uint8_t  Enable;     // ATOM_ENABLE or ATOM_DISABLE
	uint8_t  Padding[2];
};

struct enable_disp_power_gating_ps_allocation {
	uint8_t  DispPipeId; // ATOM_CRTC1, ATOM_CRTC2, ...
	uint8_t  Enable;     // ATOM_ENABLE/ATOM_DISABLE/ATOM_INIT
	uint8_t  Padding[2];
	uint32_t Reserved[4];
};
*/

/******************************************************************************/
// Structure used by EnableASIC_StaticPwrMgtTable.ctb
/******************************************************************************/
struct enable_asic_static_pwr_mgt_parameters {
	uint8_t  Enable; // ATOM_ENABLE or ATOM_DISABLE
	uint8_t  Padding[3];
};
#define ENABLE_ASIC_STATIC_PWR_MGT_PS_ALLOCATION  ENABLE_ASIC_STATIC_PWR_MGT_PARAMETERS

/******************************************************************************/
// Structures used by DAC_LoadDetectionTable.ctb
/******************************************************************************/
struct dac_load_detection_parameters {
	uint16_t DeviceID; // {ATOM_DEVICE_CRTx_SUPPORT,ATOM_DEVICE_TVx_SUPPORT,ATOM_DEVICE_CVx_SUPPORT}
	uint8_t  DacType;  // {ATOM_DAC_A,ATOM_DAC_B, ATOM_EXT_DAC}
	uint8_t  Misc;     // Valid only when table revision =1.3 and above
};

// DAC_LOAD_DETECTION_PARAMETERS.ucMisc
#define DAC_LOAD_MISC_YPrPb 0x01

struct dac_load_detection_ps_allocation {
	struct dac_load_detection_parameters Dacload;
	uint32_t Reserved[2];// Don't set this one, allocation for EXT DAC
};

/******************************************************************************/
// Structures used by DAC1EncoderControlTable.ctb and DAC2EncoderControlTable.ctb
/******************************************************************************/
struct dac_encoder_control_parameters {
	uint16_t PixelClock;  // in 10KHz; for bios convenient
	uint8_t  DacStandard; // See definition of ATOM_DACx_xxx, For DEC3.0, bit 7 used as internal flag to indicate DAC2 (==1) or DAC1 (==0)
	uint8_t  Action; // 0: turn off encoder
                     // 1: setup and turn on encoder
                     // 7: ATOM_ENCODER_INIT Initialize DAC
};

#define DAC_ENCODER_CONTROL_PS_ALLOCATION  DAC_ENCODER_CONTROL_PARAMETERS

/******************************************************************************/
// Structures used by DIG1EncoderControlTable
// DIG2EncoderControlTable
// ExternalEncoderControlTable
/******************************************************************************/
struct dig_encoder_control_parameters {
	uint16_t PixelClock; // in 10KHz; for bios convenient
	uint8_t  Config;
                         // [2] Link Select:
                         // =0: PHY linkA if bfLane<3
                         // =1: PHY linkB if bfLanes<3
                         // =0: PHY linkA+B if bfLanes=3
                         // [3] Transmitter Sel
                         // =0: UNIPHY or PCIEPHY
                         // =1: LVTMA
	uint8_t  Action;     // =0: turn off encoder
                         // =1: turn on encoder
	uint8_t  EncoderMode;
                         // =0: DP   encoder
                         // =1: LVDS encoder
                         // =2: DVI  encoder
                         // =3: HDMI encoder
                         // =4: SDVO encoder
	uint8_t  LaneNum;    // how many lanes to enable
	uint8_t  Reserved[2];
};
#define DIG_ENCODER_CONTROL_PS_ALLOCATION DIG_ENCODER_CONTROL_PARAMETERS
#define EXTERNAL_ENCODER_CONTROL_PARAMETER DIG_ENCODER_CONTROL_PARAMETERS

// ucConfig
#define ATOM_ENCODER_CONFIG_DPLINKRATE_MASK      0x01
#define ATOM_ENCODER_CONFIG_DPLINKRATE_1_62GHZ   0x00
#define ATOM_ENCODER_CONFIG_DPLINKRATE_2_70GHZ   0x01
#define ATOM_ENCODER_CONFIG_DPLINKRATE_5_40GHZ   0x02
#define ATOM_ENCODER_CONFIG_LINK_SEL_MASK        0x04
#define ATOM_ENCODER_CONFIG_LINKA                0x00
#define ATOM_ENCODER_CONFIG_LINKB                0x04
#define ATOM_ENCODER_CONFIG_LINKA_B              ATOM_TRANSMITTER_CONFIG_LINKA
#define ATOM_ENCODER_CONFIG_LINKB_A              ATOM_ENCODER_CONFIG_LINKB
#define ATOM_ENCODER_CONFIG_TRANSMITTER_SEL_MASK 0x08
#define ATOM_ENCODER_CONFIG_UNIPHY               0x00
#define ATOM_ENCODER_CONFIG_LVTMA                0x08
#define ATOM_ENCODER_CONFIG_TRANSMITTER1         0x00
#define ATOM_ENCODER_CONFIG_TRANSMITTER2         0x08
#define ATOM_ENCODER_CONFIG_DIGB                 0x80 // VBIOS Internal use, outside SW should set this bit=0
// ucAction
// ATOM_ENABLE:  Enable Encoder
// ATOM_DISABLE: Disable Encoder

// ucEncoderMode
#define ATOM_ENCODER_MODE_DP       0
#define ATOM_ENCODER_MODE_LVDS     1
#define ATOM_ENCODER_MODE_DVI      2
#define ATOM_ENCODER_MODE_HDMI     3
#define ATOM_ENCODER_MODE_SDVO     4
#define ATOM_ENCODER_MODE_DP_AUDIO 5
#define ATOM_ENCODER_MODE_TV       13
#define ATOM_ENCODER_MODE_CV       14
#define ATOM_ENCODER_MODE_CRT      15
#define ATOM_ENCODER_MODE_DVO      16
#define ATOM_ENCODER_MODE_DP_SST   ATOM_ENCODER_MODE_DP // For DP1.2
#define ATOM_ENCODER_MODE_DP_MST   5                    // For DP1.2


struct atom_dig_encoder_config_v2 {
	uint8_t  DPLinkRate:1;     // =0: 1.62Ghz, =1: 2.7Ghz
	uint8_t  Reserved:1;
	uint8_t  LinkSel:1;        // =0: linkA/C/E =1: linkB/D/F
	uint8_t  TransmitterSel:2; // =0: UniphyAB, =1: UniphyCD  =2: UniphyEF
	uint8_t  Reserved1:2;
};


struct dig_encoder_control_parameters_v2 {
	uint16_t PixelClock; // in 10KHz; for bios convenient
	struct atom_dig_encoder_config_v2 acConfig;
	uint8_t  Action;
	uint8_t  EncoderMode;
                      // =0: DP   encoder
                      // =1: LVDS encoder
                      // =2: DVI  encoder
                      // =3: HDMI encoder
                      // =4: SDVO encoder
	uint8_t  LaneNum; // how many lanes to enable
	uint8_t  Status;  // = DP_LINK_TRAINING_COMPLETE or DP_LINK_TRAINING_INCOMPLETE, only used by VBIOS with command ATOM_ENCODER_CMD_QUERY_DP_LINK_TRAINING_STATUS
	uint8_t  Reserved;
};

// ucConfig
#define ATOM_ENCODER_CONFIG_V2_DPLINKRATE_MASK      0x01
#define ATOM_ENCODER_CONFIG_V2_DPLINKRATE_1_62GHZ   0x00
#define ATOM_ENCODER_CONFIG_V2_DPLINKRATE_2_70GHZ   0x01
#define ATOM_ENCODER_CONFIG_V2_LINK_SEL_MASK        0x04
#define ATOM_ENCODER_CONFIG_V2_LINKA                0x00
#define ATOM_ENCODER_CONFIG_V2_LINKB                0x04
#define ATOM_ENCODER_CONFIG_V2_TRANSMITTER_SEL_MASK 0x18
#define ATOM_ENCODER_CONFIG_V2_TRANSMITTER1         0x00
#define ATOM_ENCODER_CONFIG_V2_TRANSMITTER2         0x08
#define ATOM_ENCODER_CONFIG_V2_TRANSMITTER3         0x10

// ucAction:
// ATOM_DISABLE
// ATOM_ENABLE
#define ATOM_ENCODER_CMD_DP_LINK_TRAINING_START        0x08
#define ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN1     0x09
#define ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN2     0x0a
#define ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN3     0x13
#define ATOM_ENCODER_CMD_DP_LINK_TRAINING_COMPLETE     0x0b
#define ATOM_ENCODER_CMD_DP_VIDEO_OFF                  0x0c
#define ATOM_ENCODER_CMD_DP_VIDEO_ON                   0x0d
#define ATOM_ENCODER_CMD_QUERY_DP_LINK_TRAINING_STATUS 0x0e
#define ATOM_ENCODER_CMD_SETUP                         0x0f
#define ATOM_ENCODER_CMD_SETUP_PANEL_MODE              0x10

// New Command for DIGxEncoderControlTable v1.5
#define ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN4 0x14
#define ATOM_ENCODER_CMD_STREAM_SETUP              0x0F // change name ATOM_ENCODER_CMD_SETUP
#define ATOM_ENCODER_CMD_LINK_SETUP                0x11 // internal use, called by other Command Table
#define ATOM_ENCODER_CMD_ENCODER_BLANK             0x12 // internal use, called by other Command Table

// ucStatus
#define ATOM_ENCODER_STATUS_LINK_TRAINING_COMPLETE    0x10
#define ATOM_ENCODER_STATUS_LINK_TRAINING_INCOMPLETE  0x00

// ucTableFormatRevision=1
// ucTableContentRevision=3
// Following function ENABLE sub-function will be used by driver when TMDS/HDMI/LVDS is used, disable function will be used by driver
struct atom_dig_encoder_config_v3 {
	uint8_t  DPLinkRate:1; // =0: 1.62Ghz, =1: 2.7Ghz
	uint8_t  Reserved:3;
	uint8_t  DigSel:3;     // =0/1/2/3/4/5: DIG0/1/2/3/4/5 (In register spec also referred as DIGA/B/C/D/E/F)
	uint8_t  Reserved1:1;
};

#define ATOM_ENCODER_CONFIG_V3_DPLINKRATE_MASK    0x03
#define ATOM_ENCODER_CONFIG_V3_DPLINKRATE_1_62GHZ 0x00
#define ATOM_ENCODER_CONFIG_V3_DPLINKRATE_2_70GHZ 0x01
#define ATOM_ENCODER_CONFIG_V3_ENCODER_SEL        0x70
#define ATOM_ENCODER_CONFIG_V3_DIG0_ENCODER       0x00
#define ATOM_ENCODER_CONFIG_V3_DIG1_ENCODER       0x10
#define ATOM_ENCODER_CONFIG_V3_DIG2_ENCODER       0x20
#define ATOM_ENCODER_CONFIG_V3_DIG3_ENCODER       0x30
#define ATOM_ENCODER_CONFIG_V3_DIG4_ENCODER       0x40
#define ATOM_ENCODER_CONFIG_V3_DIG5_ENCODER       0x50

struct dig_encoder_control_parameters_v3 {
	uint16_t PixelClock;      // in 10KHz; for bios convenient
	struct atom_dig_encoder_config_v3 acConfig;
	uint8_t  Action;
	union {
		uint8_t  EncoderMode;
								// =0: DP   encoder
								// =1: LVDS encoder
								// =2: DVI  encoder
								// =3: HDMI encoder
								// =4: SDVO encoder
								// =5: DP audio
		uint8_t  PanelMode;     // only valid when ucAction == ATOM_ENCODER_CMD_SETUP_PANEL_MODE
								// =0:     external DP
								// =0x1:   internal DP2
								// =0x11:  internal DP1 for NutMeg/Travis DP translator
	};
	uint8_t  LaneNum;          // how many lanes to enable
	uint8_t  BitPerColor;      // only valid for DP mode when ucAction = ATOM_ENCODER_CMD_SETUP
	uint8_t  Reserved;
};

// ucTableFormatRevision=1
// ucTableContentRevision=4
// start from NI
// Following function ENABLE sub-function will be used by driver when TMDS/HDMI/LVDS is used, disable function will be used by driver
struct atom_dig_encoder_config_v4 {
	uint8_t  DPLinkRate:2; // =0: 1.62Ghz, =1: 2.7Ghz, 2=5.4Ghz    <= Changed comparing to previous version
	uint8_t  Reserved:2;
	uint8_t  DigSel:3;     // =0/1/2/3/4/5: DIG0/1/2/3/4/5 (In register spec also referred as DIGA/B/C/D/E/F)
	uint8_t  Reserved1:1;
};

#define ATOM_ENCODER_CONFIG_V4_DPLINKRATE_MASK    0x03
#define ATOM_ENCODER_CONFIG_V4_DPLINKRATE_1_62GHZ 0x00
#define ATOM_ENCODER_CONFIG_V4_DPLINKRATE_2_70GHZ 0x01
#define ATOM_ENCODER_CONFIG_V4_DPLINKRATE_5_40GHZ 0x02
#define ATOM_ENCODER_CONFIG_V4_DPLINKRATE_3_24GHZ 0x03
#define ATOM_ENCODER_CONFIG_V4_ENCODER_SEL        0x70
#define ATOM_ENCODER_CONFIG_V4_DIG0_ENCODER       0x00
#define ATOM_ENCODER_CONFIG_V4_DIG1_ENCODER       0x10
#define ATOM_ENCODER_CONFIG_V4_DIG2_ENCODER       0x20
#define ATOM_ENCODER_CONFIG_V4_DIG3_ENCODER       0x30
#define ATOM_ENCODER_CONFIG_V4_DIG4_ENCODER       0x40
#define ATOM_ENCODER_CONFIG_V4_DIG5_ENCODER       0x50
#define ATOM_ENCODER_CONFIG_V4_DIG6_ENCODER       0x60

struct dig_encoder_control_parameters_v4 {
	uint16_t PixelClock; // in 10KHz; for bios convenient
	union {
		struct atom_dig_encoder_config_v4 acConfig;
		uint8_t  Config;
	};
	uint8_t  Action;
	union {
		uint8_t  EncoderMode;
							  // =0: DP   encoder
							  // =1: LVDS encoder
							  // =2: DVI  encoder
							  // =3: HDMI encoder
							  // =4: SDVO encoder
							  // =5: DP audio
		uint8_t  PanelMode;   // only valid when ucAction == ATOM_ENCODER_CMD_SETUP_PANEL_MODE
							  // =0:     external DP
							  // =0x1:   internal DP2
							  // =0x11:  internal DP1 for NutMeg/Travis DP translator
	};
	uint8_t  LaneNum;         // how many lanes to enable
	uint8_t  BitPerColor;     // only valid for DP mode when ucAction = ATOM_ENCODER_CMD_SETUP
	uint8_t  HPD_ID;          // HPD ID (1-6). =0 means to skip HDP programming. New comparing to previous version
};

// define ucBitPerColor:
#define PANEL_BPC_UNDEFINE    0x00
#define PANEL_6BIT_PER_COLOR  0x01
#define PANEL_8BIT_PER_COLOR  0x02
#define PANEL_10BIT_PER_COLOR 0x03
#define PANEL_12BIT_PER_COLOR 0x04
#define PANEL_16BIT_PER_COLOR 0x05

// define ucPanelMode
#define DP_PANEL_MODE_EXTERNAL_DP_MODE  0x00
#define DP_PANEL_MODE_INTERNAL_DP2_MODE 0x01
#define DP_PANEL_MODE_INTERNAL_DP1_MODE 0x11


struct encoder_stream_setup_parameters_v5 {
	uint8_t  DigId;      // 0~6 map to DIG0~DIG6
	uint8_t  Action;     // =  ATOM_ENOCODER_CMD_STREAM_SETUP
	uint8_t  DigMode;    // ATOM_ENCODER_MODE_DP/ATOM_ENCODER_MODE_DVI/ATOM_ENCODER_MODE_HDMI
	uint8_t  LaneNum;    // Lane number
	uint32_t PixelClock; // Pixel Clock in 10Khz
	uint8_t  BitPerColor;
	uint8_t  LinkRateIn270Mhz;// = DP link rate/270Mhz, =6: 1.62G  = 10: 2.7G, =20: 5.4Ghz, =30: 8.1Ghz etc
	uint8_t  Reserved[2];
};

struct encoder_link_setup_parameters_v5 {
	uint8_t  DigId;         // 0~6 map to DIG0~DIG6
	uint8_t  Action;        // =  ATOM_ENOCODER_CMD_LINK_SETUP
	uint8_t  DigMode;       // ATOM_ENCODER_MODE_DP/ATOM_ENCODER_MODE_DVI/ATOM_ENCODER_MODE_HDMI
	uint8_t  LaneNum;       // Lane number
	uint32_t SymClock;      // Symbol Clock in 10Khz
	uint8_t  HPDSel;
	uint8_t  DigEncoderSel; // DIG stream( front-end ) selection, bit0 means DIG0 FE is enable,
	uint8_t  Reserved[2];
};

struct dp_panel_mode_setup_parameters_v5 {
	uint8_t  DigId;     // 0~6 map to DIG0~DIG6
	uint8_t  Action;    // = ATOM_ENCODER_CMD_DPLINK_SETUP
	uint8_t  PanelMode; // =0:    external DP
                        // =0x1:  internal DP2
                        // =0x11: internal DP1 NutMeg/Travis DP Translator
	uint8_t  Reserved;
	uint32_t Reserved2[2];
};

struct encoder_generic_cmd_parameters_v5 {
	uint8_t  DigId;  // 0~6 map to DIG0~DIG6
	uint8_t  Action; // = rest of generic encoder command which does not carry any parameters
	uint8_t  Reserved[2];
	uint32_t Reserved2[2];
};

// ucDigId
#define ATOM_ENCODER_CONFIG_V5_DIG0_ENCODER 0x00
#define ATOM_ENCODER_CONFIG_V5_DIG1_ENCODER 0x01
#define ATOM_ENCODER_CONFIG_V5_DIG2_ENCODER 0x02
#define ATOM_ENCODER_CONFIG_V5_DIG3_ENCODER 0x03
#define ATOM_ENCODER_CONFIG_V5_DIG4_ENCODER 0x04
#define ATOM_ENCODER_CONFIG_V5_DIG5_ENCODER 0x05
#define ATOM_ENCODER_CONFIG_V5_DIG6_ENCODER 0x06


union dig_encoder_control_parameters_v5 {
	struct encoder_generic_cmd_parameters_v5 CmdParam;
	struct encoder_stream_setup_parameters_v5 StreamParam;
	struct encoder_link_setup_parameters_v5 LinkParam;
	struct dp_panel_mode_setup_parameters_v5 DPPanelModeParam;
};


/******************************************************************************/
// Structures used by UNIPHYTransmitterControlTable
// LVTMATransmitterControlTable
// DVOOutputControlTable
/******************************************************************************/
struct atom_dp_vs_mode {
	uint8_t  LaneSel;
	uint8_t  LaneSet;
};

struct dig_transmitter_control_parameters {
	union {
		uint16_t PixelClock; // in 10KHz; for bios convenient
		uint16_t InitInfo;   // when init uniphy,lower 8bit is used for connector type defined in objectid.h
		struct atom_dp_vs_mode Mode; // DP Voltage swing mode
	};
	uint8_t  Config;
					// [0]=0: 4 lane Link,
					// =1: 8 lane Link ( Dual Links TMDS )
					// [1]=0: InCoherent mode
					// =1: Coherent Mode
					// [2] Link Select:
					// =0: PHY linkA   if bfLane<3
					// =1: PHY linkB   if bfLanes<3
					// =0: PHY linkA+B if bfLanes=3
					// [5:4]PCIE lane Sel
					// =0: lane 0~3 or 0~7
					// =1: lane 4~7
					// =2: lane 8~11 or 8~15
					// =3: lane 12~15
	uint8_t  Action;// =0: turn off encoder
					// =1: turn on encoder
	uint8_t  Reserved[4];
};

#define DIG_TRANSMITTER_CONTROL_PS_ALLOCATION DIG_TRANSMITTER_CONTROL_PARAMETERS

// ucInitInfo
#define ATOM_TRAMITTER_INITINFO_CONNECTOR_MASK 0x00ff

// ucConfig
#define ATOM_TRANSMITTER_CONFIG_8LANE_LINK    0x01
#define ATOM_TRANSMITTER_CONFIG_COHERENT      0x02
#define ATOM_TRANSMITTER_CONFIG_LINK_SEL_MASK 0x04
#define ATOM_TRANSMITTER_CONFIG_LINKA         0x00
#define ATOM_TRANSMITTER_CONFIG_LINKB         0x04
#define ATOM_TRANSMITTER_CONFIG_LINKA_B       0x00
#define ATOM_TRANSMITTER_CONFIG_LINKB_A       0x04

#define ATOM_TRANSMITTER_CONFIG_ENCODER_SEL_MASK 0x08 // only used when ATOM_TRANSMITTER_ACTION_ENABLE
#define ATOM_TRANSMITTER_CONFIG_DIG1_ENCODER     0x00 // only used when ATOM_TRANSMITTER_ACTION_ENABLE
#define ATOM_TRANSMITTER_CONFIG_DIG2_ENCODER     0x08 // only used when ATOM_TRANSMITTER_ACTION_ENABLE

#define ATOM_TRANSMITTER_CONFIG_CLKSRC_MASK   0x30
#define ATOM_TRANSMITTER_CONFIG_CLKSRC_PPLL   0x00
#define ATOM_TRANSMITTER_CONFIG_CLKSRC_PCIE   0x20
#define ATOM_TRANSMITTER_CONFIG_CLKSRC_XTALIN 0x30
#define ATOM_TRANSMITTER_CONFIG_LANE_SEL_MASK 0xc0
#define ATOM_TRANSMITTER_CONFIG_LANE_0_3      0x00
#define ATOM_TRANSMITTER_CONFIG_LANE_0_7      0x00
#define ATOM_TRANSMITTER_CONFIG_LANE_4_7      0x40
#define ATOM_TRANSMITTER_CONFIG_LANE_8_11     0x80
#define ATOM_TRANSMITTER_CONFIG_LANE_8_15     0x80
#define ATOM_TRANSMITTER_CONFIG_LANE_12_15    0xc0

// ucAction
#define ATOM_TRANSMITTER_ACTION_DISABLE               0
#define ATOM_TRANSMITTER_ACTION_ENABLE                1
#define ATOM_TRANSMITTER_ACTION_LCD_BLOFF             2
#define ATOM_TRANSMITTER_ACTION_LCD_BLON              3
#define ATOM_TRANSMITTER_ACTION_BL_BRIGHTNESS_CONTROL 4
#define ATOM_TRANSMITTER_ACTION_LCD_SELFTEST_START    5
#define ATOM_TRANSMITTER_ACTION_LCD_SELFTEST_STOP     6
#define ATOM_TRANSMITTER_ACTION_INIT                  7
#define ATOM_TRANSMITTER_ACTION_DISABLE_OUTPUT        8
#define ATOM_TRANSMITTER_ACTION_ENABLE_OUTPUT         9
#define ATOM_TRANSMITTER_ACTION_SETUP                10
#define ATOM_TRANSMITTER_ACTION_SETUP_VSEMPH         11
#define ATOM_TRANSMITTER_ACTION_POWER_ON             12
#define ATOM_TRANSMITTER_ACTION_POWER_OFF            13

// Following are used for DigTransmitterControlTable ver1.2
struct atom_dig_transmitter_config_v2 {
	uint8_t  fDualLinkConnector:1; // bit0=1: Dual Link DVI connector
	uint8_t  fCoherentMode:1;      // bit1=1: Coherent Mode ( for DVI/HDMI mode )
	uint8_t  LinkSel:1;            // bit2=0: Uniphy LINKA or C or E when fDualLinkConnector=0. when fDualLinkConnector=1, it means master link of dual link is A or C or E
                                   // =1: Uniphy LINKB or D or F when fDualLinkConnector=0. when fDualLinkConnector=1, it means master link of dual link is B or D or F
	uint8_t  EncoderSel:1;         // bit3=0: Data/Clk path source from DIGA( DIG inst0 ). =1: Data/clk path source from DIGB ( DIG inst1 )
	uint8_t  fDPConnector:1;       // bit4=0: DP connector  =1: None DP connector
	uint8_t  Reserved:1;
	uint8_t  TransmitterSel:2;     // bit7:6: =0 Dig Transmitter 1 ( Uniphy AB )
                                   // =1 Dig Transmitter 2 ( Uniphy CD )
                                   // =2 Dig Transmitter 3 ( Uniphy EF )
};

// ucConfig
// Bit0
#define ATOM_TRANSMITTER_CONFIG_V2_DUAL_LINK_CONNECTOR 0x01

// Bit1
#define ATOM_TRANSMITTER_CONFIG_V2_COHERENT            0x02

// Bit2
#define ATOM_TRANSMITTER_CONFIG_V2_LINK_SEL_MASK       0x04
#define ATOM_TRANSMITTER_CONFIG_V2_LINKA               0x00
#define ATOM_TRANSMITTER_CONFIG_V2_LINKB               0x04

// Bit3
#define ATOM_TRANSMITTER_CONFIG_V2_ENCODER_SEL_MASK    0x08
#define ATOM_TRANSMITTER_CONFIG_V2_DIG1_ENCODER        0x00 // only used when ucAction == ATOM_TRANSMITTER_ACTION_ENABLE or ATOM_TRANSMITTER_ACTION_SETUP
#define ATOM_TRANSMITTER_CONFIG_V2_DIG2_ENCODER        0x08 // only used when ucAction == ATOM_TRANSMITTER_ACTION_ENABLE or ATOM_TRANSMITTER_ACTION_SETUP

// Bit4
#define ATOM_TRASMITTER_CONFIG_V2_DP_CONNECTOR         0x10

// Bit7:6
#define ATOM_TRANSMITTER_CONFIG_V2_TRANSMITTER_SEL_MASK 0xC0
#define ATOM_TRANSMITTER_CONFIG_V2_TRANSMITTER1         0x00 // AB
#define ATOM_TRANSMITTER_CONFIG_V2_TRANSMITTER2         0x40 // CD
#define ATOM_TRANSMITTER_CONFIG_V2_TRANSMITTER3         0x80 // EF

struct dig_transmitter_control_parameters_v2 {
	union {
		uint16_t PixelClock; // in 10KHz; for bios convenient
		uint16_t InitInfo;   // when init uniphy,lower 8bit is used for connector type defined in objectid.h
		struct atom_dp_vs_mode Mode; // DP Voltage swing mode
	};
	struct atom_dig_transmitter_config_v2 acConfig;
	uint8_t  Action; // define as ATOM_TRANSMITER_ACTION_XXX
	uint8_t  Reserved[4];
};

struct atom_dig_transmitter_config_v3 {
	uint8_t  fDualLinkConnector:1; // bit0=1: Dual Link DVI connector
	uint8_t  fCoherentMode:1;      // bit1=1: Coherent Mode ( for DVI/HDMI mode )
	uint8_t  LinkSel:1;            // bit2=0: Uniphy LINKA or C or E when fDualLinkConnector=0. when fDualLinkConnector=1, it means master link of dual link is A or C or E
                                   // =1: Uniphy LINKB or D or F when fDualLinkConnector=0. when fDualLinkConnector=1, it means master link of dual link is B or D or F
	uint8_t  EncoderSel:1;         // bit3=0: Data/Clk path source from DIGA/C/E. =1: Data/clk path source from DIGB/D/F
	uint8_t  RefClkSource:2;       // bit5:4: PPLL1 =0, PPLL2=1, EXT_CLK=2
	uint8_t  TransmitterSel:2;     // bit7:6: =0 Dig Transmitter 1 ( Uniphy AB )
                                   // =1 Dig Transmitter 2 ( Uniphy CD )
                                   // =2 Dig Transmitter 3 ( Uniphy EF )
};


struct dig_transmitter_control_parameters_v3 {
	union {
		uint16_t PixelClock; // in 10KHz; for bios convenient
		uint16_t InitInfo;   // when init uniphy,lower 8bit is used for connector type defined in objectid.h
		struct atom_dp_vs_mode Mode; // DP Voltage swing mode
	};
	struct atom_dig_transmitter_config_v3 acConfig;
	uint8_t  Action; // define as ATOM_TRANSMITER_ACTION_XXX
	uint8_t  LaneNum;
	uint8_t  Reserved[3];
};

// ucConfig
// Bit0
#define ATOM_TRANSMITTER_CONFIG_V3_DUAL_LINK_CONNECTOR  0x01

// Bit1
#define ATOM_TRANSMITTER_CONFIG_V3_COHERENT             0x02

// Bit2
#define ATOM_TRANSMITTER_CONFIG_V3_LINK_SEL_MASK        0x04
#define ATOM_TRANSMITTER_CONFIG_V3_LINKA                0x00
#define ATOM_TRANSMITTER_CONFIG_V3_LINKB                0x04

// Bit3
#define ATOM_TRANSMITTER_CONFIG_V3_ENCODER_SEL_MASK     0x08
#define ATOM_TRANSMITTER_CONFIG_V3_DIG1_ENCODER         0x00
#define ATOM_TRANSMITTER_CONFIG_V3_DIG2_ENCODER         0x08

// Bit5:4
#define ATOM_TRASMITTER_CONFIG_V3_REFCLK_SEL_MASK       0x30
#define ATOM_TRASMITTER_CONFIG_V3_P1PLL                 0x00
#define ATOM_TRASMITTER_CONFIG_V3_P2PLL                 0x10
#define ATOM_TRASMITTER_CONFIG_V3_REFCLK_SRC_EXT        0x20

// Bit7:6
#define ATOM_TRANSMITTER_CONFIG_V3_TRANSMITTER_SEL_MASK 0xC0
#define ATOM_TRANSMITTER_CONFIG_V3_TRANSMITTER1         0x00 // AB
#define ATOM_TRANSMITTER_CONFIG_V3_TRANSMITTER2         0x40 // CD
#define ATOM_TRANSMITTER_CONFIG_V3_TRANSMITTER3         0x80 // EF


/******************************************************************************/
// Structures used by UNIPHYTransmitterControlTable V1.4
// ASIC Families: NI
// ucTableFormatRevision=1
// ucTableContentRevision=4
/******************************************************************************/
struct atom_dp_vs_mode_v4 {
	uint8_t  LaneSel;
	union {
		uint8_t  LaneSet;
		struct {
			uint8_t  VOLTAGE_SWING:3; // Bit[2:0] Voltage Swing Level
			uint8_t  PRE_EMPHASIS:3;  // Bit[5:3] Pre-emphasis Level
			uint8_t  POST_CURSOR2:2;  // Bit[7:6] Post Cursor2 Level      <= New in V4
		};
	};
};

struct atom_dig_transmitter_config_v4 {
	uint8_t  fDualLinkConnector:1; // bit0=1: Dual Link DVI connector
	uint8_t  fCoherentMode:1;      // bit1=1: Coherent Mode ( for DVI/HDMI mode )
	uint8_t  LinkSel:1; // bit2=0: Uniphy LINKA or C or E when fDualLinkConnector=0. when fDualLinkConnector=1, it means master link of dual link is A or C or E
                        // =1: Uniphy LINKB or D or F when fDualLinkConnector=0. when fDualLinkConnector=1, it means master link of dual link is B or D or F
	uint8_t  EncoderSel:1;     // bit3=0: Data/Clk path source from DIGA/C/E. =1: Data/clk path source from DIGB/D/F
	uint8_t  RefClkSource:2;   // bit5:4: PPLL1 =0, PPLL2=1, DCPLL=2, EXT_CLK=3   <= New
	uint8_t  TransmitterSel:2; // bit7:6: =0 Dig Transmitter 1 ( Uniphy AB )
                               // =1 Dig Transmitter 2 ( Uniphy CD )
                               // =2 Dig Transmitter 3 ( Uniphy EF )
};

struct dig_transmitter_control_parameters_v4 {
	union {
		uint16_t PixelClock; // in 10KHz; for bios convenient
		uint16_t InitInfo;   // when init uniphy,lower 8bit is used for connector type defined in objectid.h
		struct atom_dp_vs_mode_v4 Mode; // DP Voltage swing mode     Redefined comparing to previous version
	};
	union {
		struct atom_dig_transmitter_config_v4 acConfig;
		uint8_t  Config;
	};
	uint8_t  Action;                // define as ATOM_TRANSMITER_ACTION_XXX
	uint8_t  LaneNum;
	uint8_t  Reserved[3];
};

// ucConfig
// Bit0
#define ATOM_TRANSMITTER_CONFIG_V4_DUAL_LINK_CONNECTOR 0x01
// Bit1
#define ATOM_TRANSMITTER_CONFIG_V4_COHERENT         0x02
// Bit2
#define ATOM_TRANSMITTER_CONFIG_V4_LINK_SEL_MASK    0x04
#define ATOM_TRANSMITTER_CONFIG_V4_LINKA            0x00
#define ATOM_TRANSMITTER_CONFIG_V4_LINKB            0x04
// Bit3
#define ATOM_TRANSMITTER_CONFIG_V4_ENCODER_SEL_MASK 0x08
#define ATOM_TRANSMITTER_CONFIG_V4_DIG1_ENCODER     0x00
#define ATOM_TRANSMITTER_CONFIG_V4_DIG2_ENCODER     0x08
// Bit5:4
#define ATOM_TRANSMITTER_CONFIG_V4_REFCLK_SEL_MASK  0x30
#define ATOM_TRANSMITTER_CONFIG_V4_P1PLL            0x00
#define ATOM_TRANSMITTER_CONFIG_V4_P2PLL            0x10
#define ATOM_TRANSMITTER_CONFIG_V4_DCPLL            0x20 // New in _V4
#define ATOM_TRANSMITTER_CONFIG_V4_REFCLK_SRC_EXT   0x30 // Changed comparing to V3
// Bit7:6
#define ATOM_TRANSMITTER_CONFIG_V4_TRANSMITTER_SEL_MASK 0xC0
#define ATOM_TRANSMITTER_CONFIG_V4_TRANSMITTER1         0x00 // AB
#define ATOM_TRANSMITTER_CONFIG_V4_TRANSMITTER2         0x40 // CD
#define ATOM_TRANSMITTER_CONFIG_V4_TRANSMITTER3         0x80 // EF


struct atom_dig_transmitter_config_v5 {
	uint8_t  Reserved:1;
	uint8_t  CoherentMode:1;
	uint8_t  PhyClkSrcId:2;
	uint8_t  HPDSel:3;
	uint8_t  Reservd1:1;
};

struct dig_transmitter_control_parameters_v1_5 {
	uint16_t SymClock;  // Encoder Clock in 10kHz,(DP mode)= linkclock/10, (TMDS/LVDS/HDMI)= pixel clock,  (HDMI deep color), =pixel clock * deep_color_ratio
	uint8_t  PhyId;     // 0=UNIPHYA, 1=UNIPHYB, 2=UNIPHYC, 3=UNIPHYD, 4= UNIPHYE 5=UNIPHYF
	uint8_t  Action;    // define as ATOM_TRANSMITER_ACTION_xxx
	uint8_t  LaneNum;   // indicate lane number 1-8
	uint8_t  ConnObjId; // Connector Object Id defined in ObjectId.h
	uint8_t  DigMode;   // indicate DIG mode
	struct atom_dig_transmitter_config_v5 Config;
	uint8_t  DigEncoderSel; // indicate DIG front end encoder
	uint8_t  DPLaneSet;
	uint8_t  Reserved;
	uint8_t  Reserved1;
};

// ucPhyId
#define ATOM_PHY_ID_UNIPHYA 0
#define ATOM_PHY_ID_UNIPHYB 1
#define ATOM_PHY_ID_UNIPHYC 2
#define ATOM_PHY_ID_UNIPHYD 3
#define ATOM_PHY_ID_UNIPHYE 4
#define ATOM_PHY_ID_UNIPHYF 5
#define ATOM_PHY_ID_UNIPHYG 6

// ucDigEncoderSel
#define ATOM_TRANMSITTER_V5__DIGA_SEL 0x01
#define ATOM_TRANMSITTER_V5__DIGB_SEL 0x02
#define ATOM_TRANMSITTER_V5__DIGC_SEL 0x04
#define ATOM_TRANMSITTER_V5__DIGD_SEL 0x08
#define ATOM_TRANMSITTER_V5__DIGE_SEL 0x10
#define ATOM_TRANMSITTER_V5__DIGF_SEL 0x20
#define ATOM_TRANMSITTER_V5__DIGG_SEL 0x40

// ucDigMode
#define ATOM_TRANSMITTER_DIGMODE_V5_DP     0
#define ATOM_TRANSMITTER_DIGMODE_V5_LVDS   1
#define ATOM_TRANSMITTER_DIGMODE_V5_DVI    2
#define ATOM_TRANSMITTER_DIGMODE_V5_HDMI   3
#define ATOM_TRANSMITTER_DIGMODE_V5_SDVO   4
#define ATOM_TRANSMITTER_DIGMODE_V5_DP_MST 5

// ucDPLaneSet
#define DP_LANE_SET__0DB_0_4V   0x00
#define DP_LANE_SET__0DB_0_6V   0x01
#define DP_LANE_SET__0DB_0_8V   0x02
#define DP_LANE_SET__0DB_1_2V   0x03
#define DP_LANE_SET__3_5DB_0_4V 0x08
#define DP_LANE_SET__3_5DB_0_6V 0x09
#define DP_LANE_SET__3_5DB_0_8V 0x0a
#define DP_LANE_SET__6DB_0_4V   0x10
#define DP_LANE_SET__6DB_0_6V   0x11
#define DP_LANE_SET__9_5DB_0_4V 0x18

// ATOM_DIG_TRANSMITTER_CONFIG_V5 asConfig;
// Bit1
#define ATOM_TRANSMITTER_CONFIG_V5_COHERENT         0x02

// Bit3:2
#define ATOM_TRANSMITTER_CONFIG_V5_REFCLK_SEL_MASK  0x0c
#define ATOM_TRANSMITTER_CONFIG_V5_REFCLK_SEL_SHIFT 0x02

#define ATOM_TRANSMITTER_CONFIG_V5_P1PLL            0x00
#define ATOM_TRANSMITTER_CONFIG_V5_P2PLL            0x04
#define ATOM_TRANSMITTER_CONFIG_V5_P0PLL            0x08
#define ATOM_TRANSMITTER_CONFIG_V5_REFCLK_SRC_EXT   0x0c
// Bit6:4
#define ATOM_TRANSMITTER_CONFIG_V5_HPD_SEL_MASK     0x70
#define ATOM_TRANSMITTER_CONFIG_V5_HPD_SEL_SHIFT    0x04

#define ATOM_TRANSMITTER_CONFIG_V5_NO_HPD_SEL       0x00
#define ATOM_TRANSMITTER_CONFIG_V5_HPD1_SEL         0x10
#define ATOM_TRANSMITTER_CONFIG_V5_HPD2_SEL         0x20
#define ATOM_TRANSMITTER_CONFIG_V5_HPD3_SEL         0x30
#define ATOM_TRANSMITTER_CONFIG_V5_HPD4_SEL         0x40
#define ATOM_TRANSMITTER_CONFIG_V5_HPD5_SEL         0x50
#define ATOM_TRANSMITTER_CONFIG_V5_HPD6_SEL         0x60

#define DIG_TRANSMITTER_CONTROL_PS_ALLOCATION_V1_5  DIG_TRANSMITTER_CONTROL_PARAMETERS_V1_5

/* duplicate
struct dig_transmitter_control_parameters_v1_6 {
	uint8_t  PhyId;         // 0=UNIPHYA, 1=UNIPHYB, 2=UNIPHYC, 3=UNIPHYD, 4= UNIPHYE 5=UNIPHYF
	uint8_t  Action;        // define as ATOM_TRANSMITER_ACTION_xxx
	union {
		uint8_t  DigMode;   // ATOM_ENCODER_MODE_DP/ATOM_ENCODER_MODE_DVI/ATOM_ENCODER_MODE_HDMI
		uint8_t  DPLaneSet; // DP voltage swing and pre-emphasis value defined in DPCD DP_LANE_SET, "DP_LANE_SET__xDB_y_zV"
	};
	uint8_t  LaneNum;       // Lane number
	uint32_t SymClock;      // Symbol Clock in 10Khz
	uint8_t  HPDSel;        // =1: HPD1, =2: HPD2, .... =6: HPD6, =0: HPD is not assigned
	uint8_t  DigEncoderSel; // DIG stream( front-end ) selection, bit0 means DIG0 FE is enable,
	uint8_t  ConnObjId;     // Connector Object Id defined in ObjectId.h
	uint8_t  Reserved;
	uint32_t Reserved2;
};
*/

// ucDigEncoderSel
#define ATOM_TRANMSITTER_V6__DIGA_SEL 0x01
#define ATOM_TRANMSITTER_V6__DIGB_SEL 0x02
#define ATOM_TRANMSITTER_V6__DIGC_SEL 0x04
#define ATOM_TRANMSITTER_V6__DIGD_SEL 0x08
#define ATOM_TRANMSITTER_V6__DIGE_SEL 0x10
#define ATOM_TRANMSITTER_V6__DIGF_SEL 0x20
#define ATOM_TRANMSITTER_V6__DIGG_SEL 0x40

// ucDigMode
#define ATOM_TRANSMITTER_DIGMODE_V6_DP     0
#define ATOM_TRANSMITTER_DIGMODE_V6_DVI    2
#define ATOM_TRANSMITTER_DIGMODE_V6_HDMI   3
#define ATOM_TRANSMITTER_DIGMODE_V6_DP_MST 5

// ucHPDSel
#define ATOM_TRANSMITTER_V6_NO_HPD_SEL 0x00
#define ATOM_TRANSMITTER_V6_HPD1_SEL   0x01
#define ATOM_TRANSMITTER_V6_HPD2_SEL   0x02
#define ATOM_TRANSMITTER_V6_HPD3_SEL   0x03
#define ATOM_TRANSMITTER_V6_HPD4_SEL   0x04
#define ATOM_TRANSMITTER_V6_HPD5_SEL   0x05
#define ATOM_TRANSMITTER_V6_HPD6_SEL   0x06


/******************************************************************************/
// Structures used by ExternalEncoderControlTable V1.3
// ASIC Families: Evergreen, Llano, NI
// ucTableFormatRevision=1
// ucTableContentRevision=3
/******************************************************************************/

struct external_encoder_control_parameters_v3 {
	union {
		uint16_t PixelClock;  // pixel clock in 10Khz, valid when ucAction=SETUP/ENABLE_OUTPUT
		uint16_t ConnectorId; // connector id, valid when ucAction = INIT
	};
	uint8_t  Config;      // indicate which encoder, and DP link rate when ucAction = SETUP/ENABLE_OUTPUT
	uint8_t  Action;      //
	uint8_t  EncoderMode; // encoder mode, only used when ucAction = SETUP/ENABLE_OUTPUT
	uint8_t  LaneNum;     // lane number, only used when ucAction = SETUP/ENABLE_OUTPUT
	uint8_t  BitPerColor; // output bit per color, only valid when ucAction = SETUP/ENABLE_OUTPUT and ucEncodeMode= DP
	uint8_t  Reserved;
};

// ucAction
#define EXTERANL_ENCODER_ACTION_V3_DISABLE_OUTPUT       0x00
#define EXTERANL_ENCODER_ACTION_V3_ENABLE_OUTPUT        0x01
#define EXTERNAL_ENCODER_ACTION_V3_ENCODER_INIT         0x07
#define EXTERNAL_ENCODER_ACTION_V3_ENCODER_SETUP        0x0f
#define EXTERNAL_ENCODER_ACTION_V3_ENCODER_BLANKING_OFF 0x10
#define EXTERNAL_ENCODER_ACTION_V3_ENCODER_BLANKING     0x11
#define EXTERNAL_ENCODER_ACTION_V3_DACLOAD_DETECTION    0x12
#define EXTERNAL_ENCODER_ACTION_V3_DDC_SETUP            0x14

// ucConfig
#define EXTERNAL_ENCODER_CONFIG_V3_DPLINKRATE_MASK    0x03
#define EXTERNAL_ENCODER_CONFIG_V3_DPLINKRATE_1_62GHZ 0x00
#define EXTERNAL_ENCODER_CONFIG_V3_DPLINKRATE_2_70GHZ 0x01
#define EXTERNAL_ENCODER_CONFIG_V3_DPLINKRATE_5_40GHZ 0x02
#define EXTERNAL_ENCODER_CONFIG_V3_ENCODER_SEL_MAKS   0x70
#define EXTERNAL_ENCODER_CONFIG_V3_ENCODER1           0x00
#define EXTERNAL_ENCODER_CONFIG_V3_ENCODER2           0x10
#define EXTERNAL_ENCODER_CONFIG_V3_ENCODER3           0x20

struct external_encoder_control_ps_allocation_v3 {
	struct external_encoder_control_parameters_v3 ExtEncoder;
	uint32_t Reserved[2];
};


/******************************************************************************/
// Structures used by DAC1OuputControlTable
// DAC2OuputControlTable
// LVTMAOutputControlTable  (Before DEC30)
// TMDSAOutputControlTable  (Before DEC30)
/******************************************************************************/
struct display_device_output_control_parameters {
	uint8_t  Action; // Possible input:ATOM_ENABLE||ATOMDISABLE
                     // When the display is LCD, in addition to above:
                     // ATOM_LCD_BLOFF|| ATOM_LCD_BLON ||ATOM_LCD_BL_BRIGHTNESS_CONTROL||ATOM_LCD_SELFTEST_START||
                     // ATOM_LCD_SELFTEST_STOP

	uint8_t  aucPadding[3]; // padding to DWORD aligned
};

#define DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION DISPLAY_DEVICE_OUTPUT_CONTROL_PARAMETERS


#define CRT1_OUTPUT_CONTROL_PARAMETERS    DISPLAY_DEVICE_OUTPUT_CONTROL_PARAMETERS
#define CRT1_OUTPUT_CONTROL_PS_ALLOCATION DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION

#define CRT2_OUTPUT_CONTROL_PARAMETERS    DISPLAY_DEVICE_OUTPUT_CONTROL_PARAMETERS
#define CRT2_OUTPUT_CONTROL_PS_ALLOCATION DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION

#define CV1_OUTPUT_CONTROL_PARAMETERS     DISPLAY_DEVICE_OUTPUT_CONTROL_PARAMETERS
#define CV1_OUTPUT_CONTROL_PS_ALLOCATION  DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION

#define TV1_OUTPUT_CONTROL_PARAMETERS     DISPLAY_DEVICE_OUTPUT_CONTROL_PARAMETERS
#define TV1_OUTPUT_CONTROL_PS_ALLOCATION  DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION

#define DFP1_OUTPUT_CONTROL_PARAMETERS    DISPLAY_DEVICE_OUTPUT_CONTROL_PARAMETERS
#define DFP1_OUTPUT_CONTROL_PS_ALLOCATION DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION

#define DFP2_OUTPUT_CONTROL_PARAMETERS    DISPLAY_DEVICE_OUTPUT_CONTROL_PARAMETERS
#define DFP2_OUTPUT_CONTROL_PS_ALLOCATION DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION

#define LCD1_OUTPUT_CONTROL_PARAMETERS    DISPLAY_DEVICE_OUTPUT_CONTROL_PARAMETERS
#define LCD1_OUTPUT_CONTROL_PS_ALLOCATION DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION

#define DVO_OUTPUT_CONTROL_PARAMETERS     DISPLAY_DEVICE_OUTPUT_CONTROL_PARAMETERS
#define DVO_OUTPUT_CONTROL_PS_ALLOCATION  DIG_TRANSMITTER_CONTROL_PS_ALLOCATION
#define DVO_OUTPUT_CONTROL_PARAMETERS_V3  DIG_TRANSMITTER_CONTROL_PARAMETERS


struct lvtma_output_control_parameters_v2 {
  // Possible value of ucAction
  // ATOM_TRANSMITTER_ACTION_LCD_BLON
  // ATOM_TRANSMITTER_ACTION_LCD_BLOFF
  // ATOM_TRANSMITTER_ACTION_BL_BRIGHTNESS_CONTROL
  // ATOM_TRANSMITTER_ACTION_POWER_ON
  // ATOM_TRANSMITTER_ACTION_POWER_OFF
	uint8_t  Action;
	uint8_t  BriLevel;
	uint16_t PwmFreq; // in unit of Hz, 200 means 200Hz
};



/******************************************************************************/
// Structures used by BlankCRTCTable
/******************************************************************************/
/* duplicate
struct blank_crtc_parameters {
	uint8_t  CRTC;     // ATOM_CRTC1 or ATOM_CRTC2
	uint8_t  Blanking; // ATOM_BLANKING or ATOM_BLANKINGOFF
	uint16_t BlackColorRCr;
	uint16_t BlackColorGY;
	uint16_t BlackColorBCb;
};
#define BLANK_CRTC_PS_ALLOCATION    BLANK_CRTC_PARAMETERS
*/
/******************************************************************************/
// Structures used by EnableCRTCTable
// EnableCRTCMemReqTable
// UpdateCRTC_DoubleBufferRegistersTable
/******************************************************************************/
/* duplicate
struct enable_crtc_parameters {
	uint8_t  CRTC;   // ATOM_CRTC1 or ATOM_CRTC2
	uint8_t  Enable; // ATOM_ENABLE or ATOM_DISABLE
	uint8_t  Padding[2];
};
*/
//#define ENABLE_CRTC_PS_ALLOCATION   ENABLE_CRTC_PARAMETERS

/******************************************************************************/
// Structures used by SetCRTC_OverScanTable
/******************************************************************************/
struct set_crtc_overscan_parameters {
	uint16_t OverscanRight;  // right
	uint16_t OverscanLeft;   // left
	uint16_t OverscanBottom; // bottom
	uint16_t OverscanTop;    // top
	uint8_t  CRTC;           // ATOM_CRTC1 or ATOM_CRTC2
	uint8_t  Padding[3];
};
//#define SET_CRTC_OVERSCAN_PS_ALLOCATION  SET_CRTC_OVERSCAN_PARAMETERS

/******************************************************************************/
// Structures used by SetCRTC_ReplicationTable
/******************************************************************************/
struct set_crtc_replication_parameters {
	uint8_t  H_Replication; // horizontal replication
	uint8_t  V_Replication; // vertical replication
	uint8_t  usCRTC;        // ATOM_CRTC1 or ATOM_CRTC2
	uint8_t  Padding;
};
#define SET_CRTC_REPLICATION_PS_ALLOCATION  SET_CRTC_REPLICATION_PARAMETERS

/******************************************************************************/
// Structures used by SelectCRTC_SourceTable
/******************************************************************************/
struct select_crtc_source_parameters {
	uint8_t  CRTC;   // ATOM_CRTC1 or ATOM_CRTC2
	uint8_t  Device; // ATOM_DEVICE_CRT1|ATOM_DEVICE_CRT2|....
	uint8_t  Padding[2];
};
//#define SELECT_CRTC_SOURCE_PS_ALLOCATION  SELECT_CRTC_SOURCE_PARAMETERS

struct select_crtc_source_parameters_v2 {
	uint8_t  CRTC;       // ATOM_CRTC1 or ATOM_CRTC2
	uint8_t  EncoderID;  // DAC1/DAC2/TVOUT/DIG1/DIG2/DVO
	uint8_t  EncodeMode; // Encoding mode, only valid when using DIG1/DIG2/DVO
	uint8_t  Padding;
};

// ucEncoderID
// #define ASIC_INT_DAC1_ENCODER_ID 0x00
// #define ASIC_INT_TV_ENCODER_ID   0x02
// #define ASIC_INT_DIG1_ENCODER_ID 0x03
// #define ASIC_INT_DAC2_ENCODER_ID 0x04
// #define ASIC_EXT_TV_ENCODER_ID   0x06
// #define ASIC_INT_DVO_ENCODER_ID  0x07
// #define ASIC_INT_DIG2_ENCODER_ID 0x09
// #define ASIC_EXT_DIG_ENCODER_ID  0x05

// ucEncodeMode
// #define ATOM_ENCODER_MODE_DP     0
// #define ATOM_ENCODER_MODE_LVDS   1
// #define ATOM_ENCODER_MODE_DVI    2
// #define ATOM_ENCODER_MODE_HDMI   3
// #define ATOM_ENCODER_MODE_SDVO   4
// #define ATOM_ENCODER_MODE_TV    13
// #define ATOM_ENCODER_MODE_CV    14
// #define ATOM_ENCODER_MODE_CRT   15


struct select_crtc_source_parameters_v3 {
	uint8_t  CRTC;       // ATOM_CRTC1 or ATOM_CRTC2
	uint8_t  EncoderID;  // DAC1/DAC2/TVOUT/DIG1/DIG2/DVO
	uint8_t  EncodeMode; // Encoding mode, only valid when using DIG1/DIG2/DVO
	uint8_t  DstBpc;     // PANEL_6/8/10/12BIT_PER_COLOR
};


/******************************************************************************/
// Structures used by SetPixelClockTable
// GetPixelClockTable
/******************************************************************************/
// Major revision=1., Minor revision=1
struct pixel_clock_parameters {
	uint16_t PixelClock; // in 10kHz unit; for bios convenient = (RefClk*FB_Div)/(Ref_Div*Post_Div)
                         // 0 means disable PPLL
	uint16_t RefDiv;     // Reference divider
	uint16_t FbDiv;      // feedback divider
	uint8_t  PostDiv;    // post divider
	uint8_t  FracFbDiv;  // fractional feedback divider
	uint8_t  Ppll;       // ATOM_PPLL1 or ATOM_PPL2
	uint8_t  RefDivSrc;  // ATOM_PJITTER or ATO_NONPJITTER
	uint8_t  CRTC;       // Which CRTC uses this Ppll
	uint8_t  Padding;
};

// Major revision=1., Minor revision=2, add ucMiscIfno
// ucMiscInfo:
#define MISC_FORCE_REPROG_PIXEL_CLOCK 0x1
#define MISC_DEVICE_INDEX_MASK        0xF0
#define MISC_DEVICE_INDEX_SHIFT       4

struct pixel_clock_parameters_v2 {
	uint16_t PixelClock; // in 10kHz unit; for bios convenient = (RefClk*FB_Div)/(Ref_Div*Post_Div)
                         // 0 means disable PPLL
	uint16_t RefDiv;     // Reference divider
	uint16_t FbDiv;      // feedback divider
	uint8_t  PostDiv;    // post divider
	uint8_t  FracFbDiv;  // fractional feedback divider
	uint8_t  Ppll;       // ATOM_PPLL1 or ATOM_PPL2
	uint8_t  RefDivSrc;  // ATOM_PJITTER or ATO_NONPJITTER
	uint8_t  CRTC;       // Which CRTC uses this Ppll
	uint8_t  MiscInfo;   // Different bits for different purpose, bit [7:4] as device index, bit[0]=Force prog
};

// Major revision=1., Minor revision=3, structure/definition change
// ucEncoderMode:
// ATOM_ENCODER_MODE_DP
// ATOM_ENOCDER_MODE_LVDS
// ATOM_ENOCDER_MODE_DVI
// ATOM_ENOCDER_MODE_HDMI
// ATOM_ENOCDER_MODE_SDVO
// ATOM_ENCODER_MODE_TV  13
// ATOM_ENCODER_MODE_CV  14
// ATOM_ENCODER_MODE_CRT 15

// ucDVOConfig
// #define DVO_ENCODER_CONFIG_RATE_SEL   0x01
// #define DVO_ENCODER_CONFIG_DDR_SPEED  0x00
// #define DVO_ENCODER_CONFIG_SDR_SPEED  0x01
// #define DVO_ENCODER_CONFIG_OUTPUT_SEL 0x0c
// #define DVO_ENCODER_CONFIG_LOW12BIT   0x00
// #define DVO_ENCODER_CONFIG_UPPER12BIT 0x04
// #define DVO_ENCODER_CONFIG_24BIT      0x08

// ucMiscInfo: also changed, see below
#define PIXEL_CLOCK_MISC_FORCE_PROG_PPLL        0x01
#define PIXEL_CLOCK_MISC_VGA_MODE               0x02
#define PIXEL_CLOCK_MISC_CRTC_SEL_MASK          0x04
#define PIXEL_CLOCK_MISC_CRTC_SEL_CRTC1         0x00
#define PIXEL_CLOCK_MISC_CRTC_SEL_CRTC2         0x04
#define PIXEL_CLOCK_MISC_USE_ENGINE_FOR_DISPCLK 0x08
#define PIXEL_CLOCK_MISC_REF_DIV_SRC            0x10
// V1.4 for RoadRunner
#define PIXEL_CLOCK_V4_MISC_SS_ENABLE           0x10
#define PIXEL_CLOCK_V4_MISC_COHERENT_MODE       0x20


struct pixel_clock_parameters_v3 {
	uint16_t PixelClock;    // in 10kHz unit; for bios convenient = (RefClk*FB_Div)/(Ref_Div*Post_Div)
                            // 0 means disable PPLL. For VGA PPLL,make sure this value is not 0.
	uint16_t RefDiv;        // Reference divider
	uint16_t FbDiv;         // feedback divider
	uint8_t  PostDiv;       // post divider
	uint8_t  FracFbDiv;     // fractional feedback divider
	uint8_t  Ppll;          // ATOM_PPLL1 or ATOM_PPL2
	uint8_t  TransmitterId; // graphic encoder id defined in objectId.h
	union {
		uint8_t  EncoderMode; // encoder type defined as ATOM_ENCODER_MODE_DP/DVI/HDMI/
		uint8_t  DVOConfig; // when use DVO, need to know SDR/DDR, 12bit or 24bit
	};
	uint8_t  MiscInfo; // bit[0]=Force program, bit[1]= set pclk for VGA, b[2]= CRTC sel
                       // bit[3]=0:use PPLL for dispclk source, =1: use engine clock for dispclock source
                       // bit[4]=0:use XTALIN as the source of reference divider,=1 use the pre-defined clock as the source of reference divider
};

#define PIXEL_CLOCK_PARAMETERS_LAST   PIXEL_CLOCK_PARAMETERS_V2
#define GET_PIXEL_CLOCK_PS_ALLOCATION PIXEL_CLOCK_PARAMETERS_LAST


struct pixel_clock_parameters_v5 {
	uint8_t  CRTC;          // ATOM_CRTC1~6, indicate the CRTC controller to
                            // drive the pixel clock. not used for DCPLL case.
	union {
		uint8_t  Reserved;
		uint8_t  FracFbDiv; // [gphan] temporary to prevent build problem.  remove it after driver code is changed.
	};
	uint16_t PixelClock;    // target the pixel clock to drive the CRTC timing
                            // 0 means disable PPLL/DCPLL.
	uint16_t FbDiv;         // feedback divider integer part.
	uint8_t  PostDiv;       // post divider.
	uint8_t  RefDiv;        // Reference divider
	uint8_t  Ppll;          // ATOM_PPLL1/ATOM_PPLL2/ATOM_DCPLL
	uint8_t  TransmitterID; // ASIC encoder id defined in objectId.h,
                            // indicate which graphic encoder will be used.
	uint8_t  EncoderMode;   // Encoder mode:
	uint8_t  MiscInfo;      // bit[0]= Force program PPLL
                            // bit[1]= when VGA timing is used.
                            // bit[3:2]= HDMI panel bit depth: =0: 24bpp =1:30bpp, =2:32bpp
                            // bit[4]= RefClock source for PPLL.
                            // =0: XTLAIN( default mode )
                            // =1: other external clock source, which is pre-defined
                            // by VBIOS depend on the feature required.
                            // bit[7:5]: reserved.
	// TODO is this Q?
	uint32_t FbDivDecFrac;  // 20 bit feedback divider decimal fraction part, range from 1~999999 ( 0.000001 to 0.999999 )

};

#define PIXEL_CLOCK_V5_MISC_FORCE_PROG_PPLL 0x01
#define PIXEL_CLOCK_V5_MISC_VGA_MODE        0x02
#define PIXEL_CLOCK_V5_MISC_HDMI_BPP_MASK   0x0c
#define PIXEL_CLOCK_V5_MISC_HDMI_24BPP      0x00
#define PIXEL_CLOCK_V5_MISC_HDMI_30BPP      0x04
#define PIXEL_CLOCK_V5_MISC_HDMI_32BPP      0x08
#define PIXEL_CLOCK_V5_MISC_REF_DIV_SRC     0x10

struct crtc_pixel_clock_freq {
	uint32_t PixelClock:24; // target the pixel clock to drive the CRTC timing.
                            // 0 means disable PPLL/DCPLL. Expanded to 24 bits comparing to previous version.
	uint32_t ucCRTC:8;      // ATOM_CRTC1~6, indicate the CRTC controller to
                            // drive the pixel clock. not used for DCPLL case.
};

struct pixel_clock_parameters_v6 {
	union {
		struct crtc_pixel_clock_freq CrtcPclkFreq; // pixel clock and CRTC id frequency
		uint32_t DispEngClkFreq; // dispclk frequency
	};
	uint16_t FbDiv;         // feedback divider integer part.
	uint8_t  PostDiv;       // post divider.
	uint8_t  RefDiv;        // Reference divider
	uint8_t  Ppll;          // ATOM_PPLL1/ATOM_PPLL2/ATOM_DCPLL
	uint8_t  TransmitterID; // ASIC encoder id defined in objectId.h,
                            // indicate which graphic encoder will be used.
	uint8_t  EncoderMode;   // Encoder mode:
	uint8_t  MiscInfo;      // bit[0]= Force program PPLL
                            // bit[1]= when VGA timing is used.
                            // bit[3:2]= HDMI panel bit depth: =0: 24bpp =1:30bpp, =2:32bpp
                            // bit[4]= RefClock source for PPLL.
                            // =0: XTLAIN( default mode )
                            // =1: other external clock source, which is pre-defined
                            // by VBIOS depend on the feature required.
                            // bit[7:5]: reserved.
	// TODO is this Q?
	uint32_t FbDivDecFrac;  // 20 bit feedback divider decimal fraction part, range from 1~999999 ( 0.000001 to 0.999999 )

};

#define PIXEL_CLOCK_V6_MISC_FORCE_PROG_PPLL 0x01
#define PIXEL_CLOCK_V6_MISC_VGA_MODE        0x02
#define PIXEL_CLOCK_V6_MISC_HDMI_BPP_MASK   0x0c
#define PIXEL_CLOCK_V6_MISC_HDMI_24BPP      0x00
#define PIXEL_CLOCK_V6_MISC_HDMI_36BPP      0x04
#define PIXEL_CLOCK_V6_MISC_HDMI_36BPP_V6   0x08 // for V6, the correct definition for 36bpp should be 2 for 36bpp(2:1)
#define PIXEL_CLOCK_V6_MISC_HDMI_30BPP      0x08
#define PIXEL_CLOCK_V6_MISC_HDMI_30BPP_V6   0x04 // for V6, the correct definition for 30bpp should be 1 for 36bpp(5:4)
#define PIXEL_CLOCK_V6_MISC_HDMI_48BPP      0x0c
#define PIXEL_CLOCK_V6_MISC_REF_DIV_SRC     0x10
#define PIXEL_CLOCK_V6_MISC_GEN_DPREFCLK    0x40
#define PIXEL_CLOCK_V6_MISC_DPREFCLK_BYPASS 0x40

struct get_disp_pll_status_input_parameters_v2 {
	struct pixel_clock_parameters_v3 DispClkInput;
};

struct get_disp_pll_status_output_parameters_v2 {
	uint8_t  Status;
	uint8_t  RefDivSrc; // =1: reference clock source from XTALIN, =0: source from PCIE ref clock
	uint8_t  Reserved[2];
};

struct get_disp_pll_status_input_parameters_v3 {
	struct pixel_clock_parameters_v5 DispClkInput;
};

struct pixel_clock_parameters_v7 {
	uint32_t PixelClock;     // target the pixel clock to drive the CRTC timing in unit of 100Hz.

	uint8_t  Ppll;           // ATOM_PHY_PLL0/ATOM_PHY_PLL1/ATOM_PPLL0
	uint8_t  TransmitterID;  // ASIC encoder id defined in objectId.h,
                             // indicate which graphic encoder will be used.
	uint8_t  EncoderMode;    // Encoder mode:
	uint8_t  MiscInfo;       // bit[0]= Force program PLL for pixclk
                             // bit[1]= Force program PHY PLL only ( internally used by VBIOS only in DP case which PHYPLL is programmed for SYMCLK, not Pixclk )
                             // bit[5:4]= RefClock source for PPLL.
                             // =0: XTLAIN( default mode )
                             // =1: pcie
                             // =2: GENLK
	uint8_t  CRTC;           // ATOM_CRTC1~6, indicate the CRTC controller to
	uint8_t  DeepColorRatio; // HDMI panel bit depth: =0: 24bpp =1:30bpp, =2:36bpp
	uint8_t  Reserved[2];
	uint32_t Reserved2;
};

// ucMiscInfo
#define PIXEL_CLOCK_V7_MISC_FORCE_PROG_PPLL    0x01
#define PIXEL_CLOCK_V7_MISC_PROG_PHYPLL        0x02
#define PIXEL_CLOCK_V7_MISC_YUV420_MODE        0x04
#define PIXEL_CLOCK_V7_MISC_DVI_DUALLINK_EN    0x08
#define PIXEL_CLOCK_V7_MISC_REF_DIV_SRC        0x30
#define PIXEL_CLOCK_V7_MISC_REF_DIV_SRC_XTALIN 0x00
#define PIXEL_CLOCK_V7_MISC_REF_DIV_SRC_PCIE   0x10
#define PIXEL_CLOCK_V7_MISC_REF_DIV_SRC_GENLK  0x20

// ucDeepColorRatio
#define PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_DIS 0x00 // 00 - DCCG_DEEP_COLOR_DTO_DISABLE: Disable Deep Color DTO
#define PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_5_4 0x01 // 01 - DCCG_DEEP_COLOR_DTO_5_4_RATIO: Set Deep Color DTO to 5:4
#define PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_3_2 0x02 // 02 - DCCG_DEEP_COLOR_DTO_3_2_RATIO: Set Deep Color DTO to 3:2
#define PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_2_1 0x03 // 03 - DCCG_DEEP_COLOR_DTO_2_1_RATIO: Set Deep Color DTO to 2:1

// SetDCEClockTable input parameter for DCE11.1
struct set_dce_clock_parameters_v1_1 {
	uint32_t DISPClkFreq;    // target DISPCLK frquency in unit of 10kHz, return real DISPCLK frequency. when ucFlag[1]=1, in unit of 100Hz.
	uint8_t  Flag;           // bit0=1: DPREFCLK bypass DFS bit0=0: DPREFCLK not bypass DFS
	uint8_t  Crtc;           // use when enable DCCG pixel clock ucFlag[1]=1
	uint8_t  PpllId;         // use when enable DCCG pixel clock ucFlag[1]=1
	uint8_t  DeepColorRatio; // use when enable DCCG pixel clock ucFlag[1]=1
};


struct set_dce_clock_ps_allocation_v1_1 {
	struct set_dce_clock_parameters_v1_1 Param;
	uint32_t Reserved[2];
};

// SET_DCE_CLOCK_PARAMETERS_V1_1.ucFlag
#define SET_DCE_CLOCK_FLAG_GEN_DPREFCLK    0x01
#define SET_DCE_CLOCK_FLAG_DPREFCLK_BYPASS 0x01
#define SET_DCE_CLOCK_FLAG_ENABLE_PIXCLK   0x02

/* duplicate
// SetDCEClockTable input parameter for DCE11.2( POLARIS10 and POLARIS11 ) and above
struct set_dce_clock_parameters_v2_1 {
	uint32_t DCEClkFreq; // target DCE frequency in unit of 10KHZ, return real DISPCLK/DPREFCLK frequency.
	uint8_t  DCEClkType; // =0: DISPCLK  =1: DPREFCLK  =2: PIXCLK
	uint8_t  DCEClkSrc;  // ATOM_PLL0 or ATOM_GCK_DFS or ATOM_FCH_CLK or ATOM_COMBOPHY_PLLx
	uint8_t  DCEClkFlag; // Bit [1:0] = PPLL ref clock source ( when ucDCEClkSrc= ATOM_PPLL0 )
	uint8_t  CRTC;       // ucDisp Pipe Id, ATOM_CRTC0/1/2/..., use only when ucDCEClkType = PIXCLK
};
*/

// ucDCEClkType
#define DCE_CLOCK_TYPE_DISPCLK  0
#define DCE_CLOCK_TYPE_DPREFCLK 1
#define DCE_CLOCK_TYPE_PIXELCLK 2 // used by VBIOS internally, called by SetPixelClockTable

// ucDCEClkFlag when ucDCEClkType == DPREFCLK
#define DCE_CLOCK_FLAG_PLL_REFCLK_SRC_MASK     0x03
#define DCE_CLOCK_FLAG_PLL_REFCLK_SRC_GENERICA 0x00
#define DCE_CLOCK_FLAG_PLL_REFCLK_SRC_GENLK    0x01
#define DCE_CLOCK_FLAG_PLL_REFCLK_SRC_PCIE     0x02
#define DCE_CLOCK_FLAG_PLL_REFCLK_SRC_XTALIN   0x03

// ucDCEClkFlag when ucDCEClkType == PIXCLK
#define DCE_CLOCK_FLAG_PCLK_DEEPCOLOR_RATIO_MASK 0x03
#define DCE_CLOCK_FLAG_PCLK_DEEPCOLOR_RATIO_DIS  0x00 // 00 - DCCG_DEEP_COLOR_DTO_DISABLE: Disable Deep Color DTO
#define DCE_CLOCK_FLAG_PCLK_DEEPCOLOR_RATIO_5_4  0x01 // 01 - DCCG_DEEP_COLOR_DTO_5_4_RATIO: Set Deep Color DTO to 5:4
#define DCE_CLOCK_FLAG_PCLK_DEEPCOLOR_RATIO_3_2  0x02 // 02 - DCCG_DEEP_COLOR_DTO_3_2_RATIO: Set Deep Color DTO to 3:2
#define DCE_CLOCK_FLAG_PCLK_DEEPCOLOR_RATIO_2_1  0x03 // 03 - DCCG_DEEP_COLOR_DTO_2_1_RATIO: Set Deep Color DTO to 2:1
#define DCE_CLOCK_FLAG_PIXCLK_YUV420_MODE        0x04

/* duplicate
struct set_dce_clock_ps_allocation_v2_1 {
	struct set_dce_clock_parameters_v2_1 Param;
	uint32_t Reserved[2];
};
*/



/******************************************************************************/
// Structures used by AdjustDisplayPllTable
/******************************************************************************/
struct adjust_display_pll_parameters {
	uint16_t PixelClock;
	uint8_t  TransmitterID;
	uint8_t  EncodeMode;
	union {
		uint8_t  DVOConfig; // if DVO, need passing link rate and output 12bitlow or 24bit
		uint8_t  Config;    // if none DVO, not defined yet
	};
	uint8_t  Reserved[3];
};

#define ADJUST_DISPLAY_CONFIG_SS_ENABLE  0x10
#define ADJUST_DISPLAY_PLL_PS_ALLOCATION ADJUST_DISPLAY_PLL_PARAMETERS

struct adjust_display_pll_input_parameters_v3 {
	uint16_t PixelClock;       // target pixel clock
	uint8_t  TransmitterID;    // GPU transmitter id defined in objectid.h
	uint8_t  EncodeMode;       // encoder mode: CRT, LVDS, DP, TMDS or HDMI
	uint8_t  DispPllConfig;    // display pll configure parameter defined as following DISPPLL_CONFIG_XXXX
	uint8_t  ExtTransmitterID; // external encoder id.
	uint8_t  Reserved[2];
};

// usDispPllConfig v1.2 for RoadRunner
#define DISPPLL_CONFIG_DVO_RATE_SEL   0x0001 // need only when ucTransmitterID = DVO
#define DISPPLL_CONFIG_DVO_DDR_SPEED  0x0000 // need only when ucTransmitterID = DVO
#define DISPPLL_CONFIG_DVO_SDR_SPEED  0x0001 // need only when ucTransmitterID = DVO
#define DISPPLL_CONFIG_DVO_OUTPUT_SEL 0x000c // need only when ucTransmitterID = DVO
#define DISPPLL_CONFIG_DVO_LOW12BIT   0x0000 // need only when ucTransmitterID = DVO
#define DISPPLL_CONFIG_DVO_UPPER12BIT 0x0004 // need only when ucTransmitterID = DVO
#define DISPPLL_CONFIG_DVO_24BIT      0x0008 // need only when ucTransmitterID = DVO
#define DISPPLL_CONFIG_SS_ENABLE      0x0010 // Only used when ucEncoderMode = DP or LVDS
#define DISPPLL_CONFIG_COHERENT_MODE  0x0020 // Only used when ucEncoderMode = TMDS or HDMI
#define DISPPLL_CONFIG_DUAL_LINK      0x0040 // Only used when ucEncoderMode = TMDS or LVDS


struct adjust_display_pll_output_parameters_v3 {
	uint32_t DispPllFreq; // return display PPLL freq which is used to generate the pixclock, and related idclk, symclk etc
	uint8_t  RefDiv;      // if it is none-zero, it is used to be calculated the other ppll parameter fb_divider and post_div ( if it is not given )
	uint8_t  PostDiv;     // if it is none-zero, it is used to be calculated the other ppll parameter fb_divider
	uint8_t  Reserved[2];
};

struct adjust_display_pll_ps_allocation_v3 {
	union {
		struct adjust_display_pll_input_parameters_v3 Input;
		struct adjust_display_pll_output_parameters_v3 Output;
	};
};

/******************************************************************************/
// Structures used by EnableYUVTable
/******************************************************************************/
struct enable_yuv_parameters {
	uint8_t  Enable; // ATOM_ENABLE:Enable YUV or ATOM_DISABLE:Disable YUV (RGB)
	uint8_t  CRTC;   // Which CRTC needs this YUV or RGB format
	uint8_t  Padding[2];
};
//#define ENABLE_YUV_PS_ALLOCATION ENABLE_YUV_PARAMETERS

/******************************************************************************/
// Structures used by GetMemoryClockTable
/******************************************************************************/
struct get_memory_clock_parameters {
	uint32_t ReturnMemoryClock; // current memory speed in 10KHz unit
};
//#define GET_MEMORY_CLOCK_PS_ALLOCATION  GET_MEMORY_CLOCK_PARAMETERS

/******************************************************************************/
// Structures used by GetEngineClockTable
/******************************************************************************/
struct get_engine_clock_parameters {
	uint32_t ReturnEngineClock; // current engine speed in 10KHz unit
};
//#define GET_ENGINE_CLOCK_PS_ALLOCATION  GET_ENGINE_CLOCK_PARAMETERS

/******************************************************************************/
// Following Structures and constant may be obsolete
/******************************************************************************/
// Maxium 8 bytes,the data read in will be placed in the parameter space.
// Read operaion successeful when the paramter space is non-zero, otherwise read operation failed
struct read_edid_from_hw_i2c_data_parameters {
	uint16_t Prescale;    // Ratio between Engine clock and I2C clock
	uint16_t VRAMAddress; // Adress in Frame Buffer where to pace raw EDID
	uint16_t Status;      // When use output: lower byte EDID checksum, high byte hardware status
                          // WHen use input:  lower byte as 'byte to read':currently limited to 128byte or 1byte
	uint8_t  SlaveAddr;   // Read from which slave
	uint8_t  LineNumber;  // Read from which HW assisted line
};
//#define READ_EDID_FROM_HW_I2C_DATA_PS_ALLOCATION  READ_EDID_FROM_HW_I2C_DATA_PARAMETERS


#define ATOM_WRITE_I2C_FORMAT_PSOFFSET_PSDATABYTE                 0
#define ATOM_WRITE_I2C_FORMAT_PSOFFSET_PSTWODATABYTES             1
#define ATOM_WRITE_I2C_FORMAT_PSCOUNTER_PSOFFSET_IDDATABLOCK      2
#define ATOM_WRITE_I2C_FORMAT_PSCOUNTER_IDOFFSET_PLUS_IDDATABLOCK 3
#define ATOM_WRITE_I2C_FORMAT_IDCOUNTER_IDOFFSET_IDDATABLOCK      4

struct write_one_byte_hw_i2c_data_parameters {
	uint16_t Prescale;   // Ratio between Engine clock and I2C clock
	uint16_t ByteOffset; // Write to which byte
                         // Upper portion of usByteOffset is Format of data
                         // 1bytePS+offsetPS
                         // 2bytesPS+offsetPS
                         // blockID+offsetPS
                         // blockID+offsetID
                         // blockID+counterID+offsetID
	uint8_t  Data;       // PS data1
	uint8_t  Status;     // Status byte 1=success, 2=failure, Also is used as PS data2
	uint8_t  SlaveAddr;  // Write to which slave
	uint8_t  LineNumber; // Write from which HW assisted line
};

//#define WRITE_ONE_BYTE_HW_I2C_DATA_PS_ALLOCATION  WRITE_ONE_BYTE_HW_I2C_DATA_PARAMETERS

struct set_up_hw_i2c_data_parameters {
	uint16_t Prescale;   // Ratio between Engine clock and I2C clock
	uint8_t  SlaveAddr;  // Write to which slave
	uint8_t  LineNumber; // Write from which HW assisted line
};

/******************************************************************************/
#define SPEED_FAN_CONTROL_PS_ALLOCATION   WRITE_ONE_BYTE_HW_I2C_DATA_PARAMETERS


/******************************************************************************/
// Structures used by PowerConnectorDetectionTable
/******************************************************************************/
struct power_connector_detection_parameters {
	uint8_t  PowerConnectorStatus; // Used for return value 0: detected, 1:not detected
	uint8_t  PwrBehaviorId;
	uint16_t PwrBudget; // how much power currently boot to in unit of watt
};

struct power_connector_detection_ps_allocation {
	uint8_t  PowerConnectorStatus; // Used for return value 0: detected, 1:not detected
	uint8_t  Reserved;
	uint16_t PwrBudget; // how much power currently boot to in unit of watt
	struct write_one_byte_hw_i2c_data_parameters i2c_Reserved;
};


/******************************************************************************/
// LVDS SS Command Table Definitions
/******************************************************************************/

/******************************************************************************/
// Structures used by EnableSpreadSpectrumOnPPLLTable
/******************************************************************************/
struct enable_lvds_ss_parameters {
	uint16_t SpreadSpectrumPercentage;
	uint8_t  SpreadSpectrumType; // Bit1=0 Down Spread,=1 Center Spread. Bit1=1 Ext. =0 Int. Others:TBD
	uint8_t  SpreadSpectrumStepSize_Delay; // bits3:2 SS_STEP_SIZE; bit 6:4 SS_DELAY
	uint8_t  Enable; // ATOM_ENABLE or ATOM_DISABLE
	uint8_t  Padding[3];
};

// ucTableFormatRevision=1,ucTableContentRevision=2
struct enable_lvds_ss_parameters_v2 {
	uint16_t SpreadSpectrumPercentage;
	uint8_t  SpreadSpectrumType; // Bit1=0 Down Spread,=1 Center Spread. Bit1=1 Ext. =0 Int. Others:TBD
	uint8_t  SpreadSpectrumStep;
	uint8_t  Enable; // ATOM_ENABLE or ATOM_DISABLE
	uint8_t  SpreadSpectrumDelay;
	uint8_t  SpreadSpectrumRange;
	uint8_t  Padding;
};

// This new structure is based on ENABLE_LVDS_SS_PARAMETERS but expands to SS on PPLL, so other devices can use SS.
struct enable_spread_spectrum_on_ppll {
	uint16_t SpreadSpectrumPercentage;
	uint8_t  SpreadSpectrumType; // Bit1=0 Down Spread,=1 Center Spread. Bit1=1 Ext. =0 Int. Others:TBD
	uint8_t  SpreadSpectrumStep;
	uint8_t  Enable; // ATOM_ENABLE or ATOM_DISABLE
	uint8_t  SpreadSpectrumDelay;
	uint8_t  SpreadSpectrumRange;
	uint8_t  Ppll; // ATOM_PPLL1/ATOM_PPLL2
};

 struct enable_spread_spectrum_on_ppll_v2 {
	uint16_t SpreadSpectrumPercentage;
	uint8_t  SpreadSpectrumType;   // Bit[0]: 0-Down Spread,1-Center Spread.
                                   // Bit[1]: 1-Ext. 0-Int.
                                   // Bit[3:2]: =0 P1PLL =1 P2PLL =2 DCPLL
                                   // Bits[7:4] reserved
	uint8_t  Enable;               // ATOM_ENABLE or ATOM_DISABLE
	uint16_t SpreadSpectrumAmount; // Includes SS_AMOUNT_FBDIV[7:0] and SS_AMOUNT_NFRAC_SLIP[11:8]
	uint16_t SpreadSpectrumStep;   // SS_STEP_SIZE_DSFRAC
};

#define ATOM_PPLL_SS_TYPE_V2_DOWN_SPREAD   0x00
#define ATOM_PPLL_SS_TYPE_V2_CENTRE_SPREAD 0x01
#define ATOM_PPLL_SS_TYPE_V2_EXT_SPREAD    0x02
#define ATOM_PPLL_SS_TYPE_V2_PPLL_SEL_MASK 0x0c
#define ATOM_PPLL_SS_TYPE_V2_P1PLL         0x00
#define ATOM_PPLL_SS_TYPE_V2_P2PLL         0x04
#define ATOM_PPLL_SS_TYPE_V2_DCPLL         0x08
#define ATOM_PPLL_SS_AMOUNT_V2_FBDIV_MASK  0x00FF
#define ATOM_PPLL_SS_AMOUNT_V2_FBDIV_SHIFT 0
#define ATOM_PPLL_SS_AMOUNT_V2_NFRAC_MASK  0x0F00
#define ATOM_PPLL_SS_AMOUNT_V2_NFRAC_SHIFT 8

// Used by DCE5.0
 struct enable_spread_spectrum_on_ppll_v3 {
	uint16_t SpreadSpectrumAmountFrac; // SS_AMOUNT_DSFRAC New in DCE5.0
	uint8_t  SpreadSpectrumType;       // Bit[0]: 0-Down Spread,1-Center Spread.
                                       // Bit[1]: 1-Ext. 0-Int.
                                       // Bit[3:2]: =0 P1PLL =1 P2PLL =2 DCPLL
                                       // Bits[7:4] reserved
	uint8_t  Enable;                   // ATOM_ENABLE or ATOM_DISABLE
	uint16_t SpreadSpectrumAmount;     // Includes SS_AMOUNT_FBDIV[7:0] and SS_AMOUNT_NFRAC_SLIP[11:8]
	uint16_t SpreadSpectrumStep;       // SS_STEP_SIZE_DSFRAC
};


#define ATOM_PPLL_SS_TYPE_V3_DOWN_SPREAD   0x00
#define ATOM_PPLL_SS_TYPE_V3_CENTRE_SPREAD 0x01
#define ATOM_PPLL_SS_TYPE_V3_EXT_SPREAD    0x02
#define ATOM_PPLL_SS_TYPE_V3_PPLL_SEL_MASK 0x0c
#define ATOM_PPLL_SS_TYPE_V3_P1PLL         0x00
#define ATOM_PPLL_SS_TYPE_V3_P2PLL         0x04
#define ATOM_PPLL_SS_TYPE_V3_DCPLL         0x08
#define ATOM_PPLL_SS_TYPE_V3_P0PLL         ATOM_PPLL_SS_TYPE_V3_DCPLL
#define ATOM_PPLL_SS_AMOUNT_V3_FBDIV_MASK  0x00FF
#define ATOM_PPLL_SS_AMOUNT_V3_FBDIV_SHIFT 0
#define ATOM_PPLL_SS_AMOUNT_V3_NFRAC_MASK  0x0F00
#define ATOM_PPLL_SS_AMOUNT_V3_NFRAC_SHIFT 8

#define ENABLE_SPREAD_SPECTRUM_ON_PPLL_PS_ALLOCATION ENABLE_SPREAD_SPECTRUM_ON_PPLL

struct set_pixel_clock_ps_allocation {
	struct pixel_clock_parameters PCLKInput;
	struct enable_spread_spectrum_on_ppll Reserved; // Caller doesn't need to init this portion
};



#define ENABLE_VGA_RENDER_PS_ALLOCATION SET_PIXEL_CLOCK_PS_ALLOCATION

/******************************************************************************/
// Structures used by ###
/******************************************************************************/
struct memory_training_parameters {
	uint32_t TargetMemoryClock; // In 10Khz unit
};
#define MEMORY_TRAINING_PS_ALLOCATION MEMORY_TRAINING_PARAMETERS


struct memory_training_parameters_v1_2 {
	uint16_t MemTrainingMode;
	uint16_t Reserved;
};

// usMemTrainingMode
#define NORMAL_MEMORY_TRAINING_MODE 0
#define ENTER_DRAM_SELFREFRESH_MODE 1
#define EXIT_DRAM_SELFRESH_MODE     2

/******************************************************************************/
// LVDS and other encoder command table definitions
/******************************************************************************/


/******************************************************************************/
// Structures used by LVDSEncoderControlTable   (Before DEC30)
// LVTMAEncoderControlTable  (Before DEC30)
// TMDSAEncoderControlTable  (Before DEC30)
/******************************************************************************/
struct lvds_encoder_control_parameters {
	uint16_t PixelClock; // in 10KHz; for bios convenient
	uint8_t  Misc; // bit0=0: Enable single link
                   // =1: Enable dual link
                   // Bit1=0: 666RGB
                   // =1: 888RGB
	uint8_t  Action; // 0: turn off encoder
                     // 1: setup and turn on encoder
};

#define LVDS_ENCODER_CONTROL_PS_ALLOCATION  LVDS_ENCODER_CONTROL_PARAMETERS

#define TMDS1_ENCODER_CONTROL_PARAMETERS    LVDS_ENCODER_CONTROL_PARAMETERS
#define TMDS1_ENCODER_CONTROL_PS_ALLOCATION TMDS1_ENCODER_CONTROL_PARAMETERS

#define TMDS2_ENCODER_CONTROL_PARAMETERS    TMDS1_ENCODER_CONTROL_PARAMETERS
#define TMDS2_ENCODER_CONTROL_PS_ALLOCATION TMDS2_ENCODER_CONTROL_PARAMETERS

// ucTableFormatRevision=1,ucTableContentRevision=2
struct lvds_encoder_control_parameters_v2 {
	uint16_t PixelClock; // in 10KHz; for bios convenient
	uint8_t  Misc;   // see PANEL_ENCODER_MISC_xx defintions below
	uint8_t  Action; // 0: turn off encoder
                     // 1: setup and turn on encoder
	uint8_t  Truncate; // bit0=0: Disable truncate
                       // =1: Enable truncate
                       // bit4=0: 666RGB
                       // =1: 888RGB
	uint8_t  Spatial; // bit0=0: Disable spatial dithering
                      // =1: Enable spatial dithering
                      // bit4=0: 666RGB
                      // =1: 888RGB
	uint8_t  Temporal; // bit0=0: Disable temporal dithering
                       // =1: Enable temporal dithering
                       // bit4=0: 666RGB
                       // =1: 888RGB
                       // bit5=0: Gray level 2
                       // =1: Gray level 4
	uint8_t  FRC; // bit4=0: 25FRC_SEL pattern E
                  // =1: 25FRC_SEL pattern F
                  // bit6:5=0: 50FRC_SEL pattern A
                  // =1: 50FRC_SEL pattern B
                  // =2: 50FRC_SEL pattern C
                  // =3: 50FRC_SEL pattern D
                  // bit7=0: 75FRC_SEL pattern E
                  // =1: 75FRC_SEL pattern F
};

#define LVDS_ENCODER_CONTROL_PS_ALLOCATION_V2  LVDS_ENCODER_CONTROL_PARAMETERS_V2

#define TMDS1_ENCODER_CONTROL_PARAMETERS_V2    LVDS_ENCODER_CONTROL_PARAMETERS_V2
#define TMDS1_ENCODER_CONTROL_PS_ALLOCATION_V2 TMDS1_ENCODER_CONTROL_PARAMETERS_V2

#define TMDS2_ENCODER_CONTROL_PARAMETERS_V2    TMDS1_ENCODER_CONTROL_PARAMETERS_V2
#define TMDS2_ENCODER_CONTROL_PS_ALLOCATION_V2 TMDS2_ENCODER_CONTROL_PARAMETERS_V2


#define LVDS_ENCODER_CONTROL_PARAMETERS_V3     LVDS_ENCODER_CONTROL_PARAMETERS_V2
#define LVDS_ENCODER_CONTROL_PS_ALLOCATION_V3  LVDS_ENCODER_CONTROL_PARAMETERS_V3

#define TMDS1_ENCODER_CONTROL_PARAMETERS_V3    LVDS_ENCODER_CONTROL_PARAMETERS_V3
#define TMDS1_ENCODER_CONTROL_PS_ALLOCATION_V3 TMDS1_ENCODER_CONTROL_PARAMETERS_V3

#define TMDS2_ENCODER_CONTROL_PARAMETERS_V3    LVDS_ENCODER_CONTROL_PARAMETERS_V3
#define TMDS2_ENCODER_CONTROL_PS_ALLOCATION_V3 TMDS2_ENCODER_CONTROL_PARAMETERS_V3

/******************************************************************************/
// Structures used by ###
/******************************************************************************/
struct enable_external_tmds_encoder_parameters {
	uint8_t  Enable; // Enable or Disable External TMDS encoder
	uint8_t  Misc;   // Bit0=0:Enable Single link;=1:Enable Dual link;Bit1 {=0:666RGB, =1:888RGB}
	uint8_t  Padding[2];
};

struct enable_external_tmds_encoder_ps_allocation {
	struct enable_external_tmds_encoder_parameters XTmdsEncoder;
	struct write_one_byte_hw_i2c_data_parameters Reserved; // Caller doesn't need to init this portion
};

//#define ENABLE_EXTERNAL_TMDS_ENCODER_PARAMETERS_V2  LVDS_ENCODER_CONTROL_PARAMETERS_V2
struct enable_external_tmds_encoder_ps_allocation_v2 {
	struct lvds_encoder_control_parameters_v2 XTmdsEncoder;
	struct write_one_byte_hw_i2c_data_parameters Reserved; // Caller doesn't need to init this portion
};

struct external_encoder_control_ps_allocation {
	struct dig_encoder_control_parameters DigEncoder;
	struct write_one_byte_hw_i2c_data_parameters Reserved;
};

/******************************************************************************/
// Structures used by DVOEncoderControlTable
/******************************************************************************/
// ucTableFormatRevision=1,ucTableContentRevision=3
// ucDVOConfig:
#define DVO_ENCODER_CONFIG_RATE_SEL   0x01
#define DVO_ENCODER_CONFIG_DDR_SPEED  0x00
#define DVO_ENCODER_CONFIG_SDR_SPEED  0x01
#define DVO_ENCODER_CONFIG_OUTPUT_SEL 0x0c
#define DVO_ENCODER_CONFIG_LOW12BIT   0x00
#define DVO_ENCODER_CONFIG_UPPER12BIT 0x04
#define DVO_ENCODER_CONFIG_24BIT      0x08

struct dvo_encoder_control_parameters_v3 {
	uint16_t PixelClock;
	uint8_t  DVOConfig;
	uint8_t  Action; // ATOM_ENABLE/ATOM_DISABLE/ATOM_HPD_INIT
	uint8_t  Reseved[4];
};
#define DVO_ENCODER_CONTROL_PS_ALLOCATION_V3 DVO_ENCODER_CONTROL_PARAMETERS_V3

struct dvo_encoder_control_parameters_v1_4 {
	uint16_t PixelClock;
	uint8_t  DVOConfig;
	uint8_t  Action; // ATOM_ENABLE/ATOM_DISABLE/ATOM_HPD_INIT
	uint8_t  BitPerColor; // please refer to definition of PANEL_xBIT_PER_COLOR
	uint8_t  Reseved[3];
};
#define DVO_ENCODER_CONTROL_PS_ALLOCATION_V1_4 DVO_ENCODER_CONTROL_PARAMETERS_V1_4


// ucTableFormatRevision=1
// ucTableContentRevision=3 structure is not changed but usMisc add bit 1 as another input for
// bit1=0: non-coherent mode
// =1: coherent mode

/******************************************************************************/
// Only change is here next time when changing encoder parameter definitions again!
#define LVDS_ENCODER_CONTROL_PARAMETERS_LAST     LVDS_ENCODER_CONTROL_PARAMETERS_V3
#define LVDS_ENCODER_CONTROL_PS_ALLOCATION_LAST  LVDS_ENCODER_CONTROL_PARAMETERS_LAST

#define TMDS1_ENCODER_CONTROL_PARAMETERS_LAST    LVDS_ENCODER_CONTROL_PARAMETERS_V3
#define TMDS1_ENCODER_CONTROL_PS_ALLOCATION_LAST TMDS1_ENCODER_CONTROL_PARAMETERS_LAST

#define TMDS2_ENCODER_CONTROL_PARAMETERS_LAST    LVDS_ENCODER_CONTROL_PARAMETERS_V3
#define TMDS2_ENCODER_CONTROL_PS_ALLOCATION_LAST TMDS2_ENCODER_CONTROL_PARAMETERS_LAST

#define DVO_ENCODER_CONTROL_PARAMETERS_LAST      DVO_ENCODER_CONTROL_PARAMETERS
#define DVO_ENCODER_CONTROL_PS_ALLOCATION_LAST   DVO_ENCODER_CONTROL_PS_ALLOCATION

/******************************************************************************/
#define PANEL_ENCODER_MISC_DUAL       0x01
#define PANEL_ENCODER_MISC_COHERENT   0x02
#define PANEL_ENCODER_MISC_TMDS_LINKB 0x04
#define PANEL_ENCODER_MISC_HDMI_TYPE  0x08

#define PANEL_ENCODER_ACTION_DISABLE     ATOM_DISABLE
#define PANEL_ENCODER_ACTION_ENABLE      ATOM_ENABLE
#define PANEL_ENCODER_ACTION_COHERENTSEQ (ATOM_ENABLE+1)

#define PANEL_ENCODER_TRUNCATE_EN           0x01
#define PANEL_ENCODER_TRUNCATE_DEPTH        0x10
#define PANEL_ENCODER_SPATIAL_DITHER_EN     0x01
#define PANEL_ENCODER_SPATIAL_DITHER_DEPTH  0x10
#define PANEL_ENCODER_TEMPORAL_DITHER_EN    0x01
#define PANEL_ENCODER_TEMPORAL_DITHER_DEPTH 0x10
#define PANEL_ENCODER_TEMPORAL_LEVEL_4      0x20
#define PANEL_ENCODER_25FRC_MASK            0x10
#define PANEL_ENCODER_25FRC_E               0x00
#define PANEL_ENCODER_25FRC_F               0x10
#define PANEL_ENCODER_50FRC_MASK            0x60
#define PANEL_ENCODER_50FRC_A               0x00
#define PANEL_ENCODER_50FRC_B               0x20
#define PANEL_ENCODER_50FRC_C               0x40
#define PANEL_ENCODER_50FRC_D               0x60
#define PANEL_ENCODER_75FRC_MASK            0x80
#define PANEL_ENCODER_75FRC_E               0x00
#define PANEL_ENCODER_75FRC_F               0x80

/******************************************************************************/
// Structures used by SetVoltageTable
/******************************************************************************/
#define SET_VOLTAGE_TYPE_ASIC_VDDC  1
#define SET_VOLTAGE_TYPE_ASIC_MVDDC 2
#define SET_VOLTAGE_TYPE_ASIC_MVDDQ 3
#define SET_VOLTAGE_TYPE_ASIC_VDDCI 4
#define SET_VOLTAGE_INIT_MODE       5
#define SET_VOLTAGE_GET_MAX_VOLTAGE 6 // Gets the Max. voltage for the soldered Asic

#define SET_ASIC_VOLTAGE_MODE_ALL_SOURCE 0x1
#define SET_ASIC_VOLTAGE_MODE_SOURCE_A   0x2
#define SET_ASIC_VOLTAGE_MODE_SOURCE_B   0x4

#define SET_ASIC_VOLTAGE_MODE_SET_VOLTAGE  0x0
#define SET_ASIC_VOLTAGE_MODE_GET_GPIOVAL  0x1
#define SET_ASIC_VOLTAGE_MODE_GET_GPIOMASK 0x2

struct set_voltage_parameters {
	uint8_t  VoltageType;  // To tell which voltage to set up, VDDC/MVDDC/MVDDQ
	uint8_t  VoltageMode;  // To set all, to set source A or source B or ...
	uint8_t  VoltageIndex; // An index to tell which voltage level
	uint8_t  Reserved;
};

struct set_voltage_parameters_v2 {
	uint8_t  VoltageType;  // To tell which voltage to set up, VDDC/MVDDC/MVDDQ
	uint8_t  VoltageMode;  // Not used, maybe use for state machine for differen power mode
	uint16_t VoltageLevel; // real voltage level
};

// used by both SetVoltageTable v1.3 and v1.4
struct set_voltage_parameters_v1_3 {
	uint8_t  VoltageType;  // To tell which voltage to set up, VDDC/MVDDC/MVDDQ/VDDCI
	uint8_t  VoltageMode;  // Indicate action: Set voltage level
	uint16_t VoltageLevel; // real voltage level in unit of mv or Voltage Phase (0, 1, 2, .. )
};

// ucVoltageType
#define VOLTAGE_TYPE_VDDC       1
#define VOLTAGE_TYPE_MVDDC      2
#define VOLTAGE_TYPE_MVDDQ      3
#define VOLTAGE_TYPE_VDDCI      4
#define VOLTAGE_TYPE_VDDGFX     5
#define VOLTAGE_TYPE_PCC        6
#define VOLTAGE_TYPE_MVPP       7
#define VOLTAGE_TYPE_LEDDPM     8
#define VOLTAGE_TYPE_PCC_MVDD   9
#define VOLTAGE_TYPE_PCIE_VDDC 10
#define VOLTAGE_TYPE_PCIE_VDDR 11

#define VOLTAGE_TYPE_GENERIC_I2C_1  0x11
#define VOLTAGE_TYPE_GENERIC_I2C_2  0x12
#define VOLTAGE_TYPE_GENERIC_I2C_3  0x13
#define VOLTAGE_TYPE_GENERIC_I2C_4  0x14
#define VOLTAGE_TYPE_GENERIC_I2C_5  0x15
#define VOLTAGE_TYPE_GENERIC_I2C_6  0x16
#define VOLTAGE_TYPE_GENERIC_I2C_7  0x17
#define VOLTAGE_TYPE_GENERIC_I2C_8  0x18
#define VOLTAGE_TYPE_GENERIC_I2C_9  0x19
#define VOLTAGE_TYPE_GENERIC_I2C_10 0x1A

// SET_VOLTAGE_PARAMETERS_V3.ucVoltageMode
#define ATOM_SET_VOLTAGE            0 // Set voltage Level
#define ATOM_INIT_VOLTAGE_REGULATOR 3 // Init Regulator
#define ATOM_SET_VOLTAGE_PHASE      4 // Set Vregulator Phase, only for SVID/PVID regulator
#define ATOM_GET_MAX_VOLTAGE        6 // Get Max Voltage, not used from SetVoltageTable v1.3
#define ATOM_GET_VOLTAGE_LEVEL      6 // Get Voltage level from vitual voltage ID, not used for SetVoltage v1.4
#define ATOM_GET_LEAKAGE_ID         8 // Get Leakage Voltage Id ( starting from SMU7x IP ), SetVoltage v1.4

// define vitual voltage id in usVoltageLevel
#define ATOM_VIRTUAL_VOLTAGE_ID0 0xff01
#define ATOM_VIRTUAL_VOLTAGE_ID1 0xff02
#define ATOM_VIRTUAL_VOLTAGE_ID2 0xff03
#define ATOM_VIRTUAL_VOLTAGE_ID3 0xff04
#define ATOM_VIRTUAL_VOLTAGE_ID4 0xff05
#define ATOM_VIRTUAL_VOLTAGE_ID5 0xff06
#define ATOM_VIRTUAL_VOLTAGE_ID6 0xff07
#define ATOM_VIRTUAL_VOLTAGE_ID7 0xff08

struct set_voltage_ps_allocation {
	struct set_voltage_parameters ASICSetVoltage;
	struct write_one_byte_hw_i2c_data_parameters Reserved;
};

// New Added from SI for GetVoltageInfoTable, input parameter structure
struct get_voltage_info_input_parameter_v1_1 {
	uint8_t  VoltageType;  // Input: To tell which voltage to set up, VDDC/MVDDC/MVDDQ/VDDCI
	uint8_t  VoltageMode;  // Input: Indicate action: Get voltage info
	uint16_t VoltageLevel; // Input: real voltage level in unit of mv or Voltage Phase (0, 1, 2, .. ) or Leakage Id
	uint32_t Reserved;
};

// New Added from SI for GetVoltageInfoTable, output parameter structure when ucVotlageMode == ATOM_GET_VOLTAGE_VID
struct get_voltage_info_output_parameter_v1_1 {
	uint32_t VotlageGpioState;
	uint32_t VoltageGPioMask;
};

// New Added from SI for GetVoltageInfoTable, output parameter structure when ucVotlageMode == ATOM_GET_VOLTAGE_STATEx_LEAKAGE_VID
struct get_leakage_voltage_info_output_parameter_v1_1 {
	uint16_t VoltageLevel;
	uint16_t VoltageId; // Voltage Id programmed in Voltage Regulator
	uint32_t Reseved;
};

// GetVoltageInfo v1.1 ucVoltageMode
#define ATOM_GET_VOLTAGE_VID              0x00
#define ATOM_GET_VOTLAGE_INIT_SEQ         0x03
#define ATOM_GET_VOLTTAGE_PHASE_PHASE_VID 0x04
#define ATOM_GET_VOLTAGE_SVID2            0x07 // Get SVI2 Regulator Info

// for SI, this state map to 0xff02 voltage state in Power Play table, which is power boost state
#define ATOM_GET_VOLTAGE_STATE0_LEAKAGE_VID 0x10
// for SI, this state map to 0xff01 voltage state in Power Play table, which is performance state
#define ATOM_GET_VOLTAGE_STATE1_LEAKAGE_VID 0x11

#define ATOM_GET_VOLTAGE_STATE2_LEAKAGE_VID 0x12
#define ATOM_GET_VOLTAGE_STATE3_LEAKAGE_VID 0x13


// New Added from CI Hawaii for GetVoltageInfoTable, input parameter structure
struct get_voltage_info_input_parameter_v1_2 {
	uint8_t  VoltageType;  // Input: To tell which voltage to set up, VDDC/MVDDC/MVDDQ/VDDCI
	uint8_t  VoltageMode;  // Input: Indicate action: Get voltage info
	uint16_t VoltageLevel; // Input: real voltage level in unit of mv or Voltage Phase (0, 1, 2, .. ) or Leakage Id
	uint32_t SCLKFreq;     // Input: when ucVoltageMode= ATOM_GET_VOLTAGE_EVV_VOLTAGE, DPM state SCLK frequency, Define in PPTable SCLK/Voltage dependence table
};

// New in GetVoltageInfo v1.2 ucVoltageMode
#define ATOM_GET_VOLTAGE_EVV_VOLTAGE        0x09

// New Added from CI Hawaii for EVV feature
struct get_evv_voltage_info_output_parameter_v1_2 {
	uint16_t VoltageLevel; // real voltage level in unit of mv
	uint16_t VoltageId;    // Voltage Id programmed in Voltage Regulator
	uint16_t TDP_Current;  // TDP_Current in unit of  0.01A
	uint16_t TDP_Power;    // TDP_Current in unit  of 0.1W
};


// New Added from CI Hawaii for GetVoltageInfoTable, input parameter structure
struct get_voltage_info_input_parameter_v1_3 {
	uint8_t  VoltageType;  // Input: To tell which voltage to set up, VDDC/MVDDC/MVDDQ/VDDCI
	uint8_t  VoltageMode;  // Input: Indicate action: Get voltage info
	uint16_t VoltageLevel; // Input: real voltage level in unit of mv or Voltage Phase (0, 1, 2, .. ) or Leakage Id
	uint32_t SCLKFreq;     // Input: when ucVoltageMode= ATOM_GET_VOLTAGE_EVV_VOLTAGE, DPM state SCLK frequency, Define in PPTable SCLK/Voltage dependence table
	uint32_t Reserved[3];
};

// New Added from CI Hawaii for EVV feature
struct get_evv_voltage_info_output_parameter_v1_3 {
	uint32_t VoltageLevel; // real voltage level in unit of 0.01mv
	uint32_t Reserved[4];
};


/******************************************************************************/
// Structures used by GetSMUClockInfo
/******************************************************************************/
struct get_smu_clock_info_input_parameter_v2_1 {
	uint32_t DfsPllOutputFreq:24;
	uint32_t ucDfsDivider:8;
};

struct get_smu_clock_info_output_parameter_v2_1 {
	uint32_t DfsOutputFreq;
};

/******************************************************************************/
// Structures used by TVEncoderControlTable
/******************************************************************************/
struct tv_encoder_control_parameters {
	uint16_t PixelClock; // in 10KHz; for bios convenient
	uint8_t  TvStandard; // See definition "ATOM_TV_NTSC ..."
	uint8_t  Action;     // 0: turn off encoder  1: setup and turn on encoder
};

struct tv_encoder_control_ps_allocation {
	struct tv_encoder_control_parameters TVEncoder;
	struct write_one_byte_hw_i2c_data_parameters Reserved; // Don't set this one
};

/******************************************************************************/
// Data Table Portion
/******************************************************************************/


/******************************************************************************/
// Structure used in Data.mtb
/******************************************************************************/
//struct atom_master_list_of_data_tables {
struct atom_master_data_table_v1_1 {
	struct atom_common_table_header table_header;
	uint16_t UtilityPipeLine;          // Offest for the utility to get parser info,Don't change this position!
	uint16_t MultimediaCapabilityInfo; // Only used by MM Lib,latest version 1.1, not configuable from Bios, need to include the table to build Bios
	uint16_t MultimediaConfigInfo;     // Only used by MM Lib,latest version 2.1, not configuable from Bios, need to include the table to build Bios
	uint16_t StandardVESA_Timing;      // Only used by Bios
	uint16_t FirmwareInfo;             // Shared by various SW components,latest version 1.4
	uint16_t PaletteData;              // Only used by BIOS
	uint16_t LCD_Info;                 // Shared by various SW components,latest version 1.3, was called LVDS_Info
	uint16_t DIGTransmitterInfo;       // Internal used by VBIOS only version 3.1
	uint16_t SMU_Info;                 // Shared by various SW components,latest version 1.1
	uint16_t SupportedDevicesInfo;     // Will be obsolete from R600
	uint16_t GPIO_I2C_Info;            // Shared by various SW components,latest version 1.2 will be used from R600
	uint16_t VRAM_UsageByFirmware;     // Shared by various SW components,latest version 1.3 will be used from R600
	uint16_t GPIO_Pin_LUT;             // Shared by various SW components,latest version 1.1
	uint16_t VESA_ToInternalModeLUT;   // Only used by Bios
	uint16_t GFX_Info;                 // Shared by various SW components,latest version 2.1 will be used from R600
	uint16_t PowerPlayInfo;            // Shared by various SW components,latest version 2.1,new design from R600
	uint16_t GPUVirtualizationInfo;    // Will be obsolete from R600
	uint16_t SaveRestoreInfo;          // Only used by Bios
	uint16_t PPLL_SS_Info;             // Shared by various SW components,latest version 1.2, used to call SS_Info, change to new name because of int ASIC SS info
	uint16_t OemInfo;                  // Defined and used by external SW, should be obsolete soon
	uint16_t XTMDS_Info;               // Will be obsolete from R600
	uint16_t MclkSS_Info;              // Shared by various SW components,latest version 1.1, only enabled when ext SS chip is used
	uint16_t Object_Header;            // Shared by various SW components,latest version 1.1
	uint16_t IndirectIOAccess;         // Only used by Bios,this table position can't change at all!!
	uint16_t MC_InitParameter;         // Only used by command table
	uint16_t ASIC_VDDC_Info;           // Will be obsolete from R600
	uint16_t ASIC_InternalSS_Info;     // New tabel name from R600, used to be called "ASIC_MVDDC_Info"
	uint16_t TV_VideoMode;             // Only used by command table
	uint16_t VRAM_Info;                // Only used by command table, latest version 1.3
	uint16_t MemoryTrainingInfo;       // Used for VBIOS and Diag utility for memory training purpose since R600. the new table rev start from 2.1
	uint16_t IntegratedSystemInfo;     // Shared by various SW components
	uint16_t ASIC_ProfilingInfo;       // New table name from R600, used to be called "ASIC_VDDCI_Info" for pre-R600
	uint16_t VoltageObjectInfo;        // Shared by various SW components, latest version 1.1
	uint16_t PowerSourceInfo;          // Shared by various SW components, latest versoin 1.1
	uint16_t ServiceInfo;
};

/*struct atom_master_data_table {
	struct atom_common_table_header table_header;
	struct atom_master_list_of_data_tables ListOfDataTables;
};*/

// For backward compatible
#define LVDS_Info          LCD_Info
#define DAC_Info           PaletteData
#define TMDS_Info          DIGTransmitterInfo
#define CompassionateData  GPUVirtualizationInfo
#define AnalogTV_Info      SMU_Info
#define ComponentVideoInfo GFX_Info

/******************************************************************************/
// Structure used in MultimediaCapabilityInfoTable
/******************************************************************************/
struct atom_multimedia_capability_info {
	struct atom_common_table_header table_header;
	uint32_t Signature;     // HW info table signature string "$ATI"
	uint8_t  I2C_Type;      // I2C type (normal GP_IO, ImpactTV GP_IO, Dedicated I2C pin, etc)
	uint8_t  TV_OutInfo;    // Type of TV out supported (3:0) and video out crystal frequency (6:4) and TV data port (7)
	uint8_t  VideoPortInfo; // Provides the video port capabilities
	uint8_t  HostPortInfo;  // Provides host port configuration information
};


/******************************************************************************/
// Structure used in MultimediaConfigInfoTable
/******************************************************************************/
struct atom_multimedia_config_info {
	struct atom_common_table_header table_header;
	uint32_t Signature;       // MM info table signature sting "$MMT"
	uint8_t  TunerInfo;       // Type of tuner installed on the adapter (4:0) and video input for tuner (7:5)
	uint8_t  AudioChipInfo;   // List the audio chip type (3:0) product type (4) and OEM revision (7:5)
	uint8_t  ProductID;       // Defines as OEM ID or ATI board ID dependent on product type setting
	uint8_t  MiscInfo1;       // Tuner voltage (1:0) HW teletext support (3:2) FM audio decoder (5:4) reserved (6) audio scrambling (7)
	uint8_t  MiscInfo2;       // I2S input config (0) I2S output config (1) I2S Audio Chip (4:2) SPDIF Output Config (5) reserved (7:6)
	uint8_t  MiscInfo3;       // Video Decoder Type (3:0) Video In Standard/Crystal (7:4)
	uint8_t  MiscInfo4;       // Video Decoder Host Config (2:0) reserved (7:3)
	uint8_t  VideoInput0Info; // Video Input 0 Type (1:0) F/B setting (2) physical connector ID (5:3) reserved (7:6)
	uint8_t  VideoInput1Info; // Video Input 1 Type (1:0) F/B setting (2) physical connector ID (5:3) reserved (7:6)
	uint8_t  VideoInput2Info; // Video Input 2 Type (1:0) F/B setting (2) physical connector ID (5:3) reserved (7:6)
	uint8_t  VideoInput3Info; // Video Input 3 Type (1:0) F/B setting (2) physical connector ID (5:3) reserved (7:6)
	uint8_t  VideoInput4Info; // Video Input 4 Type (1:0) F/B setting (2) physical connector ID (5:3) reserved (7:6)
};


/******************************************************************************/
// Structures used in FirmwareInfoTable
/******************************************************************************/

// usBIOSCapability Defintion:
// Bit 0 = 0: Bios image is not Posted, =1:Bios image is Posted;
// Bit 1 = 0: Dual CRTC is not supported, =1: Dual CRTC is supported;
// Bit 2 = 0: Extended Desktop is not supported, =1: Extended Desktop is supported;
// Others: Reserved
#define ATOM_BIOS_INFO_ATOM_FIRMWARE_POSTED         0x0001
#define ATOM_BIOS_INFO_DUAL_CRTC_SUPPORT            0x0002
#define ATOM_BIOS_INFO_EXTENDED_DESKTOP_SUPPORT     0x0004
#define ATOM_BIOS_INFO_MEMORY_CLOCK_SS_SUPPORT      0x0008 // (valid from v1.1 ~v1.4):=1: memclk SS enable, =0 memclk SS disable.
#define ATOM_BIOS_INFO_ENGINE_CLOCK_SS_SUPPORT      0x0010 // (valid from v1.1 ~v1.4):=1: engclk SS enable, =0 engclk SS disable.
#define ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU         0x0020
#define ATOM_BIOS_INFO_WMI_SUPPORT                  0x0040
#define ATOM_BIOS_INFO_PPMODE_ASSIGNGED_BY_SYSTEM   0x0080
#define ATOM_BIOS_INFO_HYPERMEMORY_SUPPORT          0x0100
#define ATOM_BIOS_INFO_HYPERMEMORY_SIZE_MASK        0x1E00
#define ATOM_BIOS_INFO_VPOST_WITHOUT_FIRST_MODE_SET 0x2000
#define ATOM_BIOS_INFO_BIOS_SCRATCH6_SCL2_REDEFINE  0x4000
#define ATOM_BIOS_INFO_MEMORY_CLOCK_EXT_SS_SUPPORT  0x0008 // (valid from v2.1 ): =1: memclk ss enable with external ss chip
#define ATOM_BIOS_INFO_ENGINE_CLOCK_EXT_SS_SUPPORT  0x0010 // (valid from v2.1 ): =1: engclk ss enable with external ss chip




union atombios_firmware_capability_v1 {
	uint16_t FirmwareCapability;
	struct { uint16_t
		FirmwarePosted         :0-0 +1,
		DualCRTC_Support       :1-1 +1,
		ExtendedDesktopSupport :2-2 +1,
		MemoryClockSS_Support  :3-3 +1,
		EngineClockSS_Support  :4-4 +1,
		GPUControlsBL          :5-5 +1,
		WMI_SUPPORT            :6-6 +1,
		PPMode_Assigned        :7-7 +1,
		HyperMemory_Support    :8-8 +1,
		HyperMemory_Size      :12-9 +1,
		PostWithoutModeSet    :13-13 +1,
		SCL2Redefined         :14-14 +1,
		Reserved              :15-15 +1;
	};
};
/* atombios_firmware_capability_v1 old:
#ifndef _H2INC
// Please don't add or expand this bitfield structure below, this one will retire soon.!
struct atom_firmware_capability {
	uint16_t FirmwarePosted:1;
	uint16_t DualCRTC_Support:1;
	uint16_t ExtendedDesktopSupport:1;
	uint16_t MemoryClockSS_Support:1;
	uint16_t EngineClockSS_Support:1;
	uint16_t GPUControlsBL:1;
	uint16_t WMI_SUPPORT:1;
	uint16_t PPMode_Assigned:1;
	uint16_t HyperMemory_Support:1;
	uint16_t HyperMemory_Size:4;
	uint16_t PostWithoutModeSet:1;
	uint16_t SCL2Redefined:1;
	uint16_t Reserved:1;
};
union atom_firmware_capability_access {
	struct atom_firmware_capability Access;
	uint16_t susAccess;
};
#else
union atom_firmware_capability_access {
	uint16_t susAccess;
};
#endif
*/

struct atom_firmware_info_v1_0 { // TODO 1.1? 1.0?
	struct atom_common_table_header table_header;
	uint32_t FirmwareRevision;
	uint32_t DefaultEngineClock;       // In 10Khz unit
	uint32_t DefaultMemoryClock;       // In 10Khz unit
	uint32_t DriverTargetEngineClock;  // In 10Khz unit
	uint32_t DriverTargetMemoryClock;  // In 10Khz unit
	uint32_t MaxEngineClockPLL_Output; // In 10Khz unit
	uint32_t MaxMemoryClockPLL_Output; // In 10Khz unit
	uint32_t MaxPixelClockPLL_Output;  // In 10Khz unit
	uint32_t ASICMaxEngineClock;       // In 10Khz unit
	uint32_t ASICMaxMemoryClock;       // In 10Khz unit
	uint8_t  ASICMaxTemperature;
	uint8_t  Padding[3];               // Don't use them
	uint32_t aulReservedForBIOS[3];    // Don't use them
	uint16_t MinEngineClockPLL_Input;  // In 10Khz unit
	uint16_t MaxEngineClockPLL_Input;  // In 10Khz unit
	uint16_t MinEngineClockPLL_Output; // In 10Khz unit
	uint16_t MinMemoryClockPLL_Input;  // In 10Khz unit
	uint16_t MaxMemoryClockPLL_Input;  // In 10Khz unit
	uint16_t MinMemoryClockPLL_Output; // In 10Khz unit
	uint16_t MaxPixelClock;            // In 10Khz unit, Max.  Pclk
	uint16_t MinPixelClockPLL_Input;   // In 10Khz unit
	uint16_t MaxPixelClockPLL_Input;   // In 10Khz unit
	uint16_t MinPixelClockPLL_Output;  // In 10Khz unit, the definitions above can't change!!!
	union atombios_firmware_capability_v1 FirmwareCapability;
	uint16_t ReferenceClock;           // In 10Khz unit
	uint16_t PM_RTS_Location;          // RTS PM4 starting location in ROM in 1Kb unit
	uint8_t  PM_RTS_StreamSize;        // RTS PM4 packets in Kb unit
	uint8_t  Design_ID;                // Indicate what is the board design
	uint8_t  MemoryModule_ID;          // Indicate what is the board design
};

struct atom_firmware_info_v1_2 {
	struct atom_common_table_header table_header;
	uint32_t FirmwareRevision;
	uint32_t DefaultEngineClock;       // In 10Khz unit
	uint32_t DefaultMemoryClock;       // In 10Khz unit
	uint32_t DriverTargetEngineClock;  // In 10Khz unit
	uint32_t DriverTargetMemoryClock;  // In 10Khz unit
	uint32_t MaxEngineClockPLL_Output; // In 10Khz unit
	uint32_t MaxMemoryClockPLL_Output; // In 10Khz unit
	uint32_t MaxPixelClockPLL_Output;  // In 10Khz unit
	uint32_t ASICMaxEngineClock;       // In 10Khz unit
	uint32_t ASICMaxMemoryClock;       // In 10Khz unit
	uint8_t  ASICMaxTemperature;
	uint8_t  MinAllowedBL_Level;
	uint8_t  Padding[2];               // Don't use them
	uint32_t aulReservedForBIOS[2];    // Don't use them
	uint32_t MinPixelClockPLL_Output;  // In 10Khz unit
	uint16_t MinEngineClockPLL_Input;  // In 10Khz unit
	uint16_t MaxEngineClockPLL_Input;  // In 10Khz unit
	uint16_t MinEngineClockPLL_Output; // In 10Khz unit
	uint16_t MinMemoryClockPLL_Input;  // In 10Khz unit
	uint16_t MaxMemoryClockPLL_Input;  // In 10Khz unit
	uint16_t MinMemoryClockPLL_Output; // In 10Khz unit
	uint16_t MaxPixelClock;            // In 10Khz unit, Max.  Pclk
	uint16_t MinPixelClockPLL_Input;   // In 10Khz unit
	uint16_t MaxPixelClockPLL_Input;   // In 10Khz unit
	uint16_t MinPixelClockPLL_Output_lower; // In 10Khz unit - lower 16bit of ulMinPixelClockPLL_Output
	union atombios_firmware_capability_v1 FirmwareCapability;
	uint16_t ReferenceClock;    // In 10Khz unit
	uint16_t PM_RTS_Location;   // RTS PM4 starting location in ROM in 1Kb unit
	uint8_t  PM_RTS_StreamSize; // RTS PM4 packets in Kb unit
	uint8_t  Design_ID;         // Indicate what is the board design
	uint8_t  MemoryModule_ID;   // Indicate what is the board design
};

struct atom_firmware_info_v1_3 {
	struct atom_common_table_header table_header;
	uint32_t FirmwareRevision;
	uint32_t DefaultEngineClock;       // In 10Khz unit
	uint32_t DefaultMemoryClock;       // In 10Khz unit
	uint32_t DriverTargetEngineClock;  // In 10Khz unit
	uint32_t DriverTargetMemoryClock;  // In 10Khz unit
	uint32_t MaxEngineClockPLL_Output; // In 10Khz unit
	uint32_t MaxMemoryClockPLL_Output; // In 10Khz unit
	uint32_t MaxPixelClockPLL_Output;  // In 10Khz unit
	uint32_t ASICMaxEngineClock;       // In 10Khz unit
	uint32_t ASICMaxMemoryClock;       // In 10Khz unit
	uint8_t  ASICMaxTemperature;
	uint8_t  MinAllowedBL_Level;
	uint8_t  Padding[2];               // Don't use them
	uint32_t aulReservedForBIOS;       // Don't use them
	uint32_t _3DAccelerationEngineClock; // In 10Khz unit
	uint32_t MinPixelClockPLL_Output;  // In 10Khz unit
	uint16_t MinEngineClockPLL_Input;  // In 10Khz unit
	uint16_t MaxEngineClockPLL_Input;  // In 10Khz unit
	uint16_t MinEngineClockPLL_Output; // In 10Khz unit
	uint16_t MinMemoryClockPLL_Input;  // In 10Khz unit
	uint16_t MaxMemoryClockPLL_Input;  // In 10Khz unit
	uint16_t MinMemoryClockPLL_Output; // In 10Khz unit
	uint16_t MaxPixelClock;            // In 10Khz unit, Max.  Pclk
	uint16_t MinPixelClockPLL_Input;   // In 10Khz unit
	uint16_t MaxPixelClockPLL_Input;   // In 10Khz unit
	uint16_t MinPixelClockPLL_Output_lower; // In 10Khz unit - lower 16bit of ulMinPixelClockPLL_Output
	union atombios_firmware_capability_v1 FirmwareCapability;
	uint16_t ReferenceClock;           // In 10Khz unit
	uint16_t PM_RTS_Location;          // RTS PM4 starting location in ROM in 1Kb unit
	uint8_t  PM_RTS_StreamSize;        // RTS PM4 packets in Kb unit
	uint8_t  Design_ID;                // Indicate what is the board design
	uint8_t  MemoryModule_ID;          // Indicate what is the board design
};

struct atom_firmware_info_v1_4 {
	struct atom_common_table_header table_header;
	uint32_t FirmwareRevision;
	uint32_t DefaultEngineClock;       // In 10Khz unit
	uint32_t DefaultMemoryClock;       // In 10Khz unit
	uint32_t DriverTargetEngineClock;  // In 10Khz unit
	uint32_t DriverTargetMemoryClock;  // In 10Khz unit
	uint32_t MaxEngineClockPLL_Output; // In 10Khz unit
	uint32_t MaxMemoryClockPLL_Output; // In 10Khz unit
	uint32_t MaxPixelClockPLL_Output;  // In 10Khz unit
	uint32_t ASICMaxEngineClock;       // In 10Khz unit
	uint32_t ASICMaxMemoryClock;       // In 10Khz unit
	uint8_t  ASICMaxTemperature;
	uint8_t  MinAllowedBL_Level;
	uint16_t BootUpVDDCVoltage;        // In MV unit
	uint16_t LcdMinPixelClockPLL_Output; // In MHz unit
	uint16_t LcdMaxPixelClockPLL_Output; // In MHz unit
	uint32_t _3DAccelerationEngineClock; // In 10Khz unit
	uint32_t MinPixelClockPLL_Output;  // In 10Khz unit
	uint16_t MinEngineClockPLL_Input;  // In 10Khz unit
	uint16_t MaxEngineClockPLL_Input;  // In 10Khz unit
	uint16_t MinEngineClockPLL_Output; // In 10Khz unit
	uint16_t MinMemoryClockPLL_Input;  // In 10Khz unit
	uint16_t MaxMemoryClockPLL_Input;  // In 10Khz unit
	uint16_t MinMemoryClockPLL_Output; // In 10Khz unit
	uint16_t MaxPixelClock;            // In 10Khz unit, Max.  Pclk
	uint16_t MinPixelClockPLL_Input;   // In 10Khz unit
	uint16_t MaxPixelClockPLL_Input;   // In 10Khz unit
	uint16_t MinPixelClockPLL_Output_lower;  // In 10Khz unit - lower 16bit of ulMinPixelClockPLL_Output
	union atombios_firmware_capability_v1 FirmwareCapability;
	uint16_t ReferenceClock;    // In 10Khz unit
	uint16_t PM_RTS_Location;   // RTS PM4 starting location in ROM in 1Kb unit
	uint8_t  PM_RTS_StreamSize; // RTS PM4 packets in Kb unit
	uint8_t  Design_ID;         // Indicate what is the board design
	uint8_t  MemoryModule_ID;   // Indicate what is the board design
};

// the structure below to be used from Cypress
struct atom_firmware_info_v2_1 {
	struct atom_common_table_header table_header;
	uint32_t FirmwareRevision;
	uint32_t DefaultEngineClock;       // In 10Khz unit
	uint32_t DefaultMemoryClock;       // In 10Khz unit
	uint32_t Reserved1;
	uint32_t Reserved2;
	uint32_t MaxEngineClockPLL_Output; // In 10Khz unit
	uint32_t MaxMemoryClockPLL_Output; // In 10Khz unit
	uint32_t MaxPixelClockPLL_Output;  // In 10Khz unit
	uint32_t BinaryAlteredInfo;        // Was ulASICMaxEngineClock
	uint32_t DefaultDispEngineClkFreq; // In 10Khz unit
	uint8_t  Reserved3;                // Was ucASICMaxTemperature;
	uint8_t  MinAllowedBL_Level;
	uint16_t BootUpVDDCVoltage;        // In MV unit
	uint16_t LcdMinPixelClockPLL_Output; // In MHz unit
	uint16_t LcdMaxPixelClockPLL_Output; // In MHz unit
	uint32_t Reserved4;                // Was ulAsicMaximumVoltage
	uint32_t MinPixelClockPLL_Output;  // In 10Khz unit
	uint16_t MinEngineClockPLL_Input;  // In 10Khz unit
	uint16_t MaxEngineClockPLL_Input;  // In 10Khz unit
	uint16_t MinEngineClockPLL_Output; // In 10Khz unit
	uint16_t MinMemoryClockPLL_Input;  // In 10Khz unit
	uint16_t MaxMemoryClockPLL_Input;  // In 10Khz unit
	uint16_t MinMemoryClockPLL_Output; // In 10Khz unit
	uint16_t MaxPixelClock;            // In 10Khz unit, Max.  Pclk
	uint16_t MinPixelClockPLL_Input;   // In 10Khz unit
	uint16_t MaxPixelClockPLL_Input;   // In 10Khz unit
	uint16_t MinPixelClockPLL_Output_lower; // In 10Khz unit - lower 16bit of ulMinPixelClockPLL_Output
	union atombios_firmware_capability_v1 FirmwareCapability;
	uint16_t CoreReferenceClock;       // In 10Khz unit
	uint16_t MemoryReferenceClock;     // In 10Khz unit
	uint16_t UniphyDPModeExtClkFreq;   // In 10Khz unit, if it is 0, In DP Mode Uniphy Input clock from internal PPLL, otherwise Input clock from external Spread clock
	uint8_t  MemoryModule_ID;          // Indicate what is the board design
	uint8_t  Reserved5[3];

};

/*
// the structure below to be used from NI
struct product_branding {
	uint8_t  EMBEDDED_CAP:2; // Bit[1:0] Embedded feature level
	uint8_t  Reserved:2;     // Bit[3:2] Reserved
	uint8_t  BRANDING_ID:4;  // Bit[7:4] Branding ID
};
*/
union product_branding_v2 {
	uint8_t ProductBranding;
	struct { uint8_t
		EMBEDDED_CAP :1-0 +1, // Embedded feature level
		Reserved     :3-2 +1, // Reserved
		BRANDING_ID  :7-4 +1; // Branding ID
	};
};
struct atom_firmware_info_v2_2 {
	struct atom_common_table_header table_header;
	uint32_t FirmwareRevision;
	uint32_t DefaultEngineClock;       // In 10Khz unit
	uint32_t DefaultMemoryClock;       // In 10Khz unit
	uint32_t SPLL_OutputFreq;          // In 10Khz unit
	uint32_t GPUPLL_OutputFreq;        // In 10Khz unit
	uint32_t Reserved1;                // Was ulMaxEngineClockPLL_Output; //In 10Khz unit*
	uint32_t Reserved2;                // Was ulMaxMemoryClockPLL_Output; //In 10Khz unit*
	uint32_t MaxPixelClockPLL_Output;  // In 10Khz unit
	uint32_t BinaryAlteredInfo;        // Was ulASICMaxEngineClock  ?
	uint32_t DefaultDispEngineClkFreq; // In 10Khz unit. This is the frequency before DCDTO, corresponding to usBootUpVDDCVoltage.
	uint8_t  Reserved3;                // Was ucASICMaxTemperature;
	uint8_t  MinAllowedBL_Level;
	uint16_t BootUpVDDCVoltage;        // In MV unit
	uint16_t LcdMinPixelClockPLL_Output; // In MHz unit
	uint16_t LcdMaxPixelClockPLL_Output; // In MHz unit
	uint32_t Reserved4;                // Was ulAsicMaximumVoltage
	uint32_t MinPixelClockPLL_Output;  // In 10Khz unit
	uint8_t  RemoteDisplayConfig;      // 0=disable 1=enable
	uint8_t  Reserved5[3];             // Was usMinEngineClockPLL_Input and usMaxEngineClockPLL_Input
	uint32_t Reserved6;                // Was usMinEngineClockPLL_Output and usMinMemoryClockPLL_Input
	uint32_t Reserved7;                // Was usMaxMemoryClockPLL_Input and usMinMemoryClockPLL_Output
	uint16_t MaxPixelClock;            //In 10Khz unit, Max.  Pclk used only for DAC
	uint16_t MinPixelClockPLL_Input;   // In 10Khz unit
	uint16_t MaxPixelClockPLL_Input;   // In 10Khz unit
	uint16_t BootUpVDDCIVoltage;       // In unit of mv; Was usMinPixelClockPLL_Output;
	union atombios_firmware_capability_v1 FirmwareCapability;
	uint16_t CoreReferenceClock;       // In 10Khz unit
	uint16_t MemoryReferenceClock;     // In 10Khz unit
	uint16_t UniphyDPModeExtClkFreq;   // In 10Khz unit, if it is 0, In DP Mode Uniphy Input clock from internal PPLL, otherwise Input clock from external Spread clock
	uint8_t  MemoryModule_ID;          // Indicate what is the board design
	uint8_t  CoolingSolution_ID;       // 0: Air cooling; 1: Liquid cooling ... [COOLING_SOLUTION]
	union  product_branding_v2 ProductBranding;
	uint8_t  Reserved9;
	uint16_t BootUpMVDDCVoltage;  // In unit of mv; Was usMinPixelClockPLL_Output;
	uint16_t BootUpVDDGFXVoltage; // In unit of mv;
	uint32_t Reserved10[3];       // New added comparing to previous version
};

#define ATOM_FIRMWARE_INFO_LAST  ATOM_FIRMWARE_INFO_V2_2


// definition of ucRemoteDisplayConfig
#define REMOTE_DISPLAY_DISABLE 0x00
#define REMOTE_DISPLAY_ENABLE  0x01

/******************************************************************************/
// Structures used in IntegratedSystemInfoTable
/******************************************************************************/
#define IGP_CAP_FLAG_DYNAMIC_CLOCK_EN  0x2
#define IGP_CAP_FLAG_AC_CARD           0x4
#define IGP_CAP_FLAG_SDVO_CARD         0x8
#define IGP_CAP_FLAG_POSTDIV_BY_2_MODE 0x10

struct atom_integrated_system_info {
	struct atom_common_table_header table_header;
	uint32_t BootUpEngineClock;    // in 10kHz unit
	uint32_t BootUpMemoryClock;    // in 10kHz unit
	uint32_t MaxSystemMemoryClock; // in 10kHz unit
	uint32_t MinSystemMemoryClock; // in 10kHz unit
	uint8_t  NumberOfCyclesInPeriodHi;
	uint8_t  LCDTimingSel; // =0:not valid.!=0 sel this timing descriptor from LCD EDID.
	uint16_t Reserved1;
	uint16_t InterNBVoltageLow;  // An intermidiate PMW value to set the voltage
	uint16_t InterNBVoltageHigh; // Another intermidiate PMW value to set the voltage
	uint32_t Reserved[2];

	uint16_t FSBClock; // In MHz unit
	uint16_t CapabilityFlag; // Bit0=1 indicates the fake HDMI support,Bit1=0/1 for Dynamic clocking dis/enable
                             // Bit[3:2]== 0:No PCIE card, 1:AC card, 2:SDVO card
                             // Bit[4]==1: P/2 mode, ==0: P/1 mode
	uint16_t PCIENBCfgReg7; // bit[7:0]=MUX_Sel, bit[9:8]=MUX_SEL_LEVEL2, bit[10]=Lane_Reversal
	uint16_t K8MemoryClock;    // in MHz unit
	uint16_t K8SyncStartDelay; // in 0.01 us unit
	uint16_t K8DataReturnTime; // in 0.01 us unit
	uint8_t  MaxNBVoltage;
	uint8_t  MinNBVoltage;
	enum atom_dgpu_vram_type MemoryType;
	uint8_t  NumberOfCyclesInPeriod; // CG.FVTHROT_PWM_CTRL_REG0.NumberOfCyclesInPeriod
	uint8_t  StartingPWM_HighTime; // CG.FVTHROT_PWM_CTRL_REG0.StartingPWM_HighTime
	uint8_t  HTLinkWidth; // 16 bit vs. 8 bit
	uint8_t  MaxNBVoltageHigh;
	uint8_t  MinNBVoltageHigh;
};

/* Explanation on entries in ATOM_INTEGRATED_SYSTEM_INFO
ulBootUpMemoryClock:    For Intel IGP,it's the UMA system memory clock
                        For AMD IGP,it's 0 if no SidePort memory installed or it's the boot-up SidePort memory clock
ulMaxSystemMemoryClock: For Intel IGP,it's the Max freq from memory SPD if memory runs in ASYNC mode or otherwise (SYNC mode) it's 0
                        For AMD IGP,for now this can be 0
ulMinSystemMemoryClock: For Intel IGP,it's 133MHz if memory runs in ASYNC mode or otherwise (SYNC mode) it's 0
                        For AMD IGP,for now this can be 0

usFSBClock:             For Intel IGP,it's FSB Freq
                        For AMD IGP,it's HT Link Speed

usK8MemoryClock:        For AMD IGP only. For RevF CPU, set it to 200
usK8SyncStartDelay:     For AMD IGP only. Memory access latency in K8, required for watermark calculation
usK8DataReturnTime:     For AMD IGP only. Memory access latency in K8, required for watermark calculation

VC:Voltage Control
ucMaxNBVoltage:         Voltage regulator dependent PWM value. Low 8 bits of the value for the max voltage.Set this one to 0xFF if VC without PWM. Set this to 0x0 if no VC at all.
ucMinNBVoltage:         Voltage regulator dependent PWM value. Low 8 bits of the value for the min voltage.Set this one to 0x00 if VC without PWM or no VC at all.

ucNumberOfCyclesInPeriod:   Indicate how many cycles when PWM duty is 100%. low 8 bits of the value.
ucNumberOfCyclesInPeriodHi: Indicate how many cycles when PWM duty is 100%. high 8 bits of the value.If the PWM has an inverter,set bit [7]==1,otherwise set it 0

ucMaxNBVoltageHigh:     Voltage regulator dependent PWM value. High 8 bits of  the value for the max voltage.Set this one to 0xFF if VC without PWM. Set this to 0x0 if no VC at all.
ucMinNBVoltageHigh:     Voltage regulator dependent PWM value. High 8 bits of the value for the min voltage.Set this one to 0x00 if VC without PWM or no VC at all.


usInterNBVoltageLow:    Voltage regulator dependent PWM value. The value makes the voltage >=Min NB voltage but <=InterNBVoltageHigh. Set this to 0x0000 if VC without PWM or no VC at all.
usInterNBVoltageHigh:   Voltage regulator dependent PWM value. The value makes the voltage >=InterNBVoltageLow but <=Max NB voltage.Set this to 0x0000 if VC without PWM or no VC at all.
*/


/*
The following IGP table is introduced from RS780, which is supposed to be put by SBIOS in FB before IGP VBIOS starts VPOST;
Then VBIOS will copy the whole structure to its image so all GPU SW components can access this data structure to get whatever they need.
The enough reservation should allow us to never change table revisions. Whenever needed, a GPU SW component can use reserved portion for new data entries.

SW components can access the IGP system infor structure in the same way as before
*/


struct atom_integrated_system_info_v2 {
	struct atom_common_table_header table_header;
	uint32_t BootUpEngineClock;   // in 10kHz unit
	uint32_t Reserved1[2];        // must be 0x0 for the reserved
	uint32_t BootUpUMAClock;      // in 10kHz unit
	uint32_t BootUpSidePortClock; // in 10kHz unit
	uint32_t MinSidePortClock;    // in 10kHz unit
	uint32_t Reserved2[6];        // must be 0x0 for the reserved
	uint32_t SystemConfig;        // see explanation below
	uint32_t BootUpReqDisplayVector;
	uint32_t OtherDisplayMisc;
	uint32_t DDISlot1Config;
	uint32_t DDISlot2Config;
	enum atom_dgpu_vram_type MemoryType;
	uint8_t  UMAChannelNumber;
	uint8_t  DockingPinBit;
	uint8_t  DockingPinPolarity;
	uint32_t DockingPinCFGInfo;
	uint32_t CPUCapInfo;
	uint16_t NumberOfCyclesInPeriod;
	uint16_t MaxNBVoltage;
	uint16_t MinNBVoltage;
	uint16_t BootUpNBVoltage;
	uint32_t HTLinkFreq; // in 10Khz
	uint16_t MinHTLinkWidth;
	uint16_t MaxHTLinkWidth;
	uint16_t UMASyncStartDelay;
	uint16_t UMADataReturnTime;
	uint16_t LinkStatusZeroTime;
	uint16_t DACEfuse; // for storing badgap value (for RS880 only)
	uint32_t HighVoltageHTLinkFreq; // in 10Khz
	uint32_t LowVoltageHTLinkFreq;  // in 10Khz
	uint16_t MaxUpStreamHTLinkWidth;
	uint16_t MaxDownStreamHTLinkWidth;
	uint16_t MinUpStreamHTLinkWidth;
	uint16_t MinDownStreamHTLinkWidth;
	uint16_t FirmwareVersion; // 0 means FW is not supported. Otherwise it's the FW version loaded by SBIOS and driver should enable FW.
	uint16_t FullT0Time;      // Input to calculate minimum HT link change time required by NB P-State. Unit is 0.01us.
	uint32_t Reserved3[96];   // must be 0x0
};

/*
ulBootUpEngineClock:   Boot-up Engine Clock in 10Khz;
ulBootUpUMAClock:      Boot-up UMA Clock in 10Khz; it must be 0x0 when UMA is not present
ulBootUpSidePortClock: Boot-up SidePort Clock in 10Khz; it must be 0x0 when SidePort Memory is not present,this could be equal to or less than maximum supported Sideport memory clock

ulSystemConfig:
Bit[0]=1: PowerExpress mode =0 Non-PowerExpress mode;
Bit[1]=1: system boots up at AMD overdrived state or user customized  mode. In this case, driver will just stick to this boot-up mode. No other PowerPlay state
      =0: system boots up at driver control state. Power state depends on PowerPlay table.
Bit[2]=1: PWM method is used on NB voltage control. =0: GPIO method is used.
Bit[3]=1: Only one power state(Performance) will be supported.
      =0: Multiple power states supported from PowerPlay table.
Bit[4]=1: CLMC is supported and enabled on current system.
      =0: CLMC is not supported or enabled on current system. SBIOS need to support HT link/freq change through ATIF interface.
Bit[5]=1: Enable CDLW for all driver control power states. Max HT width is from SBIOS, while Min HT width is determined by display requirement.
      =0: CDLW is disabled. If CLMC is enabled case, Min HT width will be set equal to Max HT width. If CLMC disabled case, Max HT width will be applied.
Bit[6]=1: High Voltage requested for all power states. In this case, voltage will be forced at 1.1v and powerplay table voltage drop/throttling request will be ignored.
      =0: Voltage settings is determined by powerplay table.
Bit[7]=1: Enable CLMC as hybrid Mode. CDLD and CILR will be disabled in this case and we're using legacy C1E. This is workaround for CPU(Griffin) performance issue.
      =0: Enable CLMC as regular mode, CDLD and CILR will be enabled.
Bit[8]=1: CDLF is supported and enabled on current system.
      =0: CDLF is not supported or enabled on current system.
Bit[9]=1: DLL Shut Down feature is enabled on current system.
      =0: DLL Shut Down feature is not enabled or supported on current system.

ulBootUpReqDisplayVector: This dword is a bit vector indicates what display devices are requested during boot-up. Refer to ATOM_DEVICE_xxx_SUPPORT for the bit vector definitions.

ulOtherDisplayMisc: [15:8]- Bootup LCD Expansion selection; 0-center, 1-full panel size expansion;
                       [7:0] - BootupTV standard selection; This is a bit vector to indicate what TV standards are supported by the system. Refer to ucTVSuppportedStd definition;

ulDDISlot1Config: Describes the PCIE lane configuration on this DDI PCIE slot (ADD2 card) or connector (Mobile design).
      [3:0]  - Bit vector to indicate PCIE lane config of the DDI slot/connector on chassis (bit 0=1 lane 3:0; bit 1=1 lane 7:4; bit 2=1 lane 11:8; bit 3=1 lane 15:12)
         [7:4]  - Bit vector to indicate PCIE lane config of the same DDI slot/connector on docking station (bit 4=1 lane 3:0; bit 5=1 lane 7:4; bit 6=1 lane 11:8; bit 7=1 lane 15:12)
      When a DDI connector is not "paired" (meaming two connections mutualexclusive on chassis or docking, only one of them can be connected at one time.
      in both chassis and docking, SBIOS has to duplicate the same PCIE lane info from chassis to docking or vice versa. For example:
      one DDI connector is only populated in docking with PCIE lane 8-11, but there is no paired connection on chassis, SBIOS has to copy bit 6 to bit 2.

         [15:8] - Lane configuration attribute;
      [23:16]- Connector type, possible value:
               CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_D
               CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_D
               CONNECTOR_OBJECT_ID_HDMI_TYPE_A
               CONNECTOR_OBJECT_ID_DISPLAYPORT
               CONNECTOR_OBJECT_ID_eDP
         [31:24]- Reserved

ulDDISlot2Config: Same as Slot1.
ucMemoryType: SidePort memory type, set it to 0x0 when Sideport memory is not installed. Driver needs this info to change sideport memory clock. Not for display in CCC.
For IGP, Hypermemory is the only memory type showed in CCC.

ucUMAChannelNumber:  how many channels for the UMA;

ulDockingPinCFGInfo: [15:0]-Bus/Device/Function # to CFG to read this Docking Pin; [31:16]-reg offset in CFG to read this pin
ucDockingPinBit:     which bit in this register to read the pin status;
ucDockingPinPolarity:Polarity of the pin when docked;

ulCPUCapInfo:        [7:0]=1:Griffin;[7:0]=2:Greyhound;[7:0]=3:K8, [7:0]=4:Pharaoh, other bits reserved for now and must be 0x0

usNumberOfCyclesInPeriod:Indicate how many cycles when PWM duty is 100%.

usMaxNBVoltage:Max. voltage control value in either PWM or GPIO mode.
usMinNBVoltage:Min. voltage control value in either PWM or GPIO mode.
	struct gpio mode: both usMaxNBVoltage & usMinNBVoltage have a valid value ulSystemConfig.SYSTEM_CONFIG_USE_PWM_ON_VOLTAGE=0
	struct pwm mode: both usMaxNBVoltage & usMinNBVoltage have a valid value ulSystemConfig.SYSTEM_CONFIG_USE_PWM_ON_VOLTAGE=1
	struct gpu W don't control mode: usMaxNBVoltage & usMinNBVoltage=0 and no care about ulSystemConfig.SYSTEM_CONFIG_USE_PWM_ON_VOLTAGE

usBootUpNBVoltage:Boot-up voltage regulator dependent PWM value.


ulHTLinkFreq:       Bootup HT link Frequency in 10Khz.
usMinHTLinkWidth:   Bootup minimum HT link width. If CDLW disabled, this is equal to usMaxHTLinkWidth.
                    If CDLW enabled, both upstream and downstream width should be the same during bootup.
usMaxHTLinkWidth:   Bootup maximum HT link width. If CDLW disabled, this is equal to usMinHTLinkWidth.
                    If CDLW enabled, both upstream and downstream width should be the same during bootup.

usUMASyncStartDelay: Memory access latency, required for watermark calculation
usUMADataReturnTime: Memory access latency, required for watermark calculation
usLinkStatusZeroTime:Memory access latency required for watermark calculation, set this to 0x0 for K8 CPU, set a proper value in 0.01 the unit of us
for Griffin or Greyhound. SBIOS needs to convert to actual time by:
                     if T0Ttime [5:4]=00b, then usLinkStatusZeroTime=T0Ttime [3:0]*0.1us (0.0 to 1.5us)
                     if T0Ttime [5:4]=01b, then usLinkStatusZeroTime=T0Ttime [3:0]*0.5us (0.0 to 7.5us)
                     if T0Ttime [5:4]=10b, then usLinkStatusZeroTime=T0Ttime [3:0]*2.0us (0.0 to 30us)
                     if T0Ttime [5:4]=11b, and T0Ttime [3:0]=0x0 to 0xa, then usLinkStatusZeroTime=T0Ttime [3:0]*20us (0.0 to 200us)

ulHighVoltageHTLinkFreq:     HT link frequency for power state with low voltage. If boot up runs in HT1, this must be 0.
                             This must be less than or equal to ulHTLinkFreq(bootup frequency).
ulLowVoltageHTLinkFreq:      HT link frequency for power state with low voltage or voltage scaling 1.0v~1.1v. If boot up runs in HT1, this must be 0.
                             This must be less than or equal to ulHighVoltageHTLinkFreq.

usMaxUpStreamHTLinkWidth:    Asymmetric link width support in the future, to replace usMaxHTLinkWidth. Not used for now.
usMaxDownStreamHTLinkWidth:  same as above.
usMinUpStreamHTLinkWidth:    Asymmetric link width support in the future, to replace usMinHTLinkWidth. Not used for now.
usMinDownStreamHTLinkWidth:  same as above.
*/

// ATOM_INTEGRATED_SYSTEM_INFO::ulCPUCapInfo  - CPU type definition
#define INTEGRATED_SYSTEM_INFO__UNKNOWN_CPU        0
#define INTEGRATED_SYSTEM_INFO__AMD_CPU__GRIFFIN   1
#define INTEGRATED_SYSTEM_INFO__AMD_CPU__GREYHOUND 2
#define INTEGRATED_SYSTEM_INFO__AMD_CPU__K8        3
#define INTEGRATED_SYSTEM_INFO__AMD_CPU__PHARAOH   4
#define INTEGRATED_SYSTEM_INFO__AMD_CPU__OROCHI    5

#define INTEGRATED_SYSTEM_INFO__AMD_CPU__MAX_CODE  INTEGRATED_SYSTEM_INFO__AMD_CPU__OROCHI    // this deff reflects max defined CPU code

#define SYSTEM_CONFIG_POWEREXPRESS_ENABLE         0x00000001
#define SYSTEM_CONFIG_RUN_AT_OVERDRIVE_ENGINE     0x00000002
#define SYSTEM_CONFIG_USE_PWM_ON_VOLTAGE          0x00000004
#define SYSTEM_CONFIG_PERFORMANCE_POWERSTATE_ONLY 0x00000008
#define SYSTEM_CONFIG_CLMC_ENABLED                0x00000010
#define SYSTEM_CONFIG_CDLW_ENABLED                0x00000020
#define SYSTEM_CONFIG_HIGH_VOLTAGE_REQUESTED      0x00000040
#define SYSTEM_CONFIG_CLMC_HYBRID_MODE_ENABLED    0x00000080
#define SYSTEM_CONFIG_CDLF_ENABLED                0x00000100
#define SYSTEM_CONFIG_DLL_SHUTDOWN_ENABLED        0x00000200

#define IGP_DDI_SLOT_LANE_CONFIG_MASK 0x000000FF

#define b0IGP_DDI_SLOT_LANE_MAP_MASK         0x0F
#define b0IGP_DDI_SLOT_DOCKING_LANE_MAP_MASK 0xF0
#define b0IGP_DDI_SLOT_CONFIG_LANE_0_3       0x01
#define b0IGP_DDI_SLOT_CONFIG_LANE_4_7       0x02
#define b0IGP_DDI_SLOT_CONFIG_LANE_8_11      0x04
#define b0IGP_DDI_SLOT_CONFIG_LANE_12_15     0x08

#define IGP_DDI_SLOT_ATTRIBUTE_MASK    0x0000FF00
#define IGP_DDI_SLOT_CONFIG_REVERSED   0x00000100
#define b1IGP_DDI_SLOT_CONFIG_REVERSED 0x01

#define IGP_DDI_SLOT_CONNECTOR_TYPE_MASK 0x00FF0000

// IntegratedSystemInfoTable new Rev is V5 after V2, because of the real rev of V2 is v1.4. This rev is used for RR
struct atom_integrated_system_info_v5 {
	struct atom_common_table_header table_header;
	uint32_t BootUpEngineClock; // in 10kHz unit
	uint32_t DentistVCOFreq;    // Dentist VCO clock in 10kHz unit, the source of GPU SCLK, LCLK, UCLK and VCLK.
	uint32_t LClockFreq;        // GPU Lclk freq in 10kHz unit, have relationship with NCLK in NorthBridge
	uint32_t BootUpUMAClock;    // in 10kHz unit
	uint32_t Reserved1[8];      // must be 0x0 for the reserved
	uint32_t BootUpReqDisplayVector;
	uint32_t OtherDisplayMisc;
	uint32_t Reserved2[4];      // must be 0x0 for the reserved
	uint32_t SystemConfig;      // TBD
	uint32_t CPUCapInfo;        // TBD
	uint16_t MaxNBVoltage;      // high NB voltage, calculated using current VDDNB (D24F2xDC) and VDDNB offset fuse;
	uint16_t MinNBVoltage;      // low NB voltage, calculated using current VDDNB (D24F2xDC) and VDDNB offset fuse;
	uint16_t BootUpNBVoltage;   // boot up NB voltage
	uint8_t  HtcTmpLmt;         // bit [22:16] of D24F3x64 Hardware Thermal Control (HTC) Register, may not be needed, TBD
	uint8_t  TjOffset;          // bit [28:22] of D24F3xE4 Thermtrip Status Register,may not be needed, TBD
	uint32_t Reserved3[4];      // must be 0x0 for the reserved
	uint32_t DDISlot1Config;    // see above ulDDISlot1Config definition
	uint32_t DDISlot2Config;
	uint32_t DDISlot3Config;
	uint32_t DDISlot4Config;
	uint32_t Reserved4[4];      // must be 0x0 for the reserved
	enum atom_dgpu_vram_type MemoryType;
	uint8_t  UMAChannelNumber;
	uint16_t Reserved;
	uint32_t Reserved5[4];      // must be 0x0 for the reserved
	uint32_t CSR_M3_ARB_CNTL_DEFAULT[10];// arrays with values for CSR M3 arbiter for default
	uint32_t CSR_M3_ARB_CNTL_UVD[10]; // arrays with values for CSR M3 arbiter for UVD playback
	uint32_t CSR_M3_ARB_CNTL_FS3D[10];// arrays with values for CSR M3 arbiter for Full Screen 3D applications
	uint32_t Reserved6[61];           // must be 0x0
};



/******************************************************************************/
// Structure used in GPUVirtualizationInfoTable
/******************************************************************************/
struct atom_gpu_virtualization_info_v2_1 {
	struct atom_common_table_header table_header;
	uint32_t MCUcodeRomStartAddr;
	uint32_t MCUcodeLength;
	uint32_t SMCUcodeRomStartAddr;
	uint32_t SMCUcodeLength;
	uint32_t RLCVUcodeRomStartAddr;
	uint32_t RLCVUcodeLength;
	uint32_t TOCUcodeStartAddr;
	uint32_t TOCUcodeLength;
	uint32_t SMCPatchTableStartAddr;
	uint32_t SmcPatchTableLength;
	uint32_t SystemFlag;
};


#define ATOM_CRT_INT_ENCODER1_INDEX 0x00000000
#define ATOM_LCD_INT_ENCODER1_INDEX 0x00000001
#define ATOM_TV_INT_ENCODER1_INDEX  0x00000002
#define ATOM_DFP_INT_ENCODER1_INDEX 0x00000003
#define ATOM_CRT_INT_ENCODER2_INDEX 0x00000004
#define ATOM_LCD_EXT_ENCODER1_INDEX 0x00000005
#define ATOM_TV_EXT_ENCODER1_INDEX  0x00000006
#define ATOM_DFP_EXT_ENCODER1_INDEX 0x00000007
#define ATOM_CV_INT_ENCODER1_INDEX  0x00000008
#define ATOM_DFP_INT_ENCODER2_INDEX 0x00000009
#define ATOM_CRT_EXT_ENCODER1_INDEX 0x0000000A
#define ATOM_CV_EXT_ENCODER1_INDEX  0x0000000B
#define ATOM_DFP_INT_ENCODER3_INDEX 0x0000000C
#define ATOM_DFP_INT_ENCODER4_INDEX 0x0000000D

// define ASIC internal encoder id ( bit vector ), used for CRTC_SourceSelTable
#define ASIC_INT_DAC1_ENCODER_ID 0x00
#define ASIC_INT_TV_ENCODER_ID   0x02
#define ASIC_INT_DIG1_ENCODER_ID 0x03
#define ASIC_INT_DAC2_ENCODER_ID 0x04
#define ASIC_EXT_TV_ENCODER_ID   0x06
#define ASIC_INT_DVO_ENCODER_ID  0x07
#define ASIC_INT_DIG2_ENCODER_ID 0x09
#define ASIC_EXT_DIG_ENCODER_ID  0x05
#define ASIC_EXT_DIG2_ENCODER_ID 0x08
#define ASIC_INT_DIG3_ENCODER_ID 0x0a
#define ASIC_INT_DIG4_ENCODER_ID 0x0b
#define ASIC_INT_DIG5_ENCODER_ID 0x0c
#define ASIC_INT_DIG6_ENCODER_ID 0x0d
#define ASIC_INT_DIG7_ENCODER_ID 0x0e

// define Encoder attribute
#define ATOM_ANALOG_ENCODER  0
#define ATOM_DIGITAL_ENCODER 1
#define ATOM_DP_ENCODER      2

#define ATOM_ENCODER_ENUM_MASK 0x70
#define ATOM_ENCODER_ENUM_ID1  0x00
#define ATOM_ENCODER_ENUM_ID2  0x10
#define ATOM_ENCODER_ENUM_ID3  0x20
#define ATOM_ENCODER_ENUM_ID4  0x30
#define ATOM_ENCODER_ENUM_ID5  0x40
#define ATOM_ENCODER_ENUM_ID6  0x50

#define ATOM_DEVICE_CRT1_INDEX 0x00000000
#define ATOM_DEVICE_LCD1_INDEX 0x00000001
#define ATOM_DEVICE_TV1_INDEX  0x00000002
#define ATOM_DEVICE_DFP1_INDEX 0x00000003
#define ATOM_DEVICE_CRT2_INDEX 0x00000004
#define ATOM_DEVICE_LCD2_INDEX 0x00000005
#define ATOM_DEVICE_DFP6_INDEX 0x00000006
#define ATOM_DEVICE_DFP2_INDEX 0x00000007
#define ATOM_DEVICE_CV_INDEX   0x00000008
#define ATOM_DEVICE_DFP3_INDEX 0x00000009
#define ATOM_DEVICE_DFP4_INDEX 0x0000000A
#define ATOM_DEVICE_DFP5_INDEX 0x0000000B

#define ATOM_DEVICE_RESERVEDC_INDEX      0x0000000C
#define ATOM_DEVICE_RESERVEDD_INDEX      0x0000000D
#define ATOM_DEVICE_RESERVEDE_INDEX      0x0000000E
#define ATOM_DEVICE_RESERVEDF_INDEX      0x0000000F
#define ATOM_MAX_SUPPORTED_DEVICE_INFO   (ATOM_DEVICE_DFP3_INDEX+1)
#define ATOM_MAX_SUPPORTED_DEVICE_INFO_2 ATOM_MAX_SUPPORTED_DEVICE_INFO
#define ATOM_MAX_SUPPORTED_DEVICE_INFO_3 (ATOM_DEVICE_DFP5_INDEX + 1 )

#define ATOM_MAX_SUPPORTED_DEVICE        (ATOM_DEVICE_RESERVEDF_INDEX+1)

#define ATOM_DEVICE_CRT1_SUPPORT         (0x1L << ATOM_DEVICE_CRT1_INDEX )
#define ATOM_DEVICE_LCD1_SUPPORT         (0x1L << ATOM_DEVICE_LCD1_INDEX )
#define ATOM_DEVICE_TV1_SUPPORT          (0x1L << ATOM_DEVICE_TV1_INDEX  )
#define ATOM_DEVICE_DFP1_SUPPORT         (0x1L << ATOM_DEVICE_DFP1_INDEX )
#define ATOM_DEVICE_CRT2_SUPPORT         (0x1L << ATOM_DEVICE_CRT2_INDEX )
#define ATOM_DEVICE_LCD2_SUPPORT         (0x1L << ATOM_DEVICE_LCD2_INDEX )
#define ATOM_DEVICE_DFP6_SUPPORT         (0x1L << ATOM_DEVICE_DFP6_INDEX )
#define ATOM_DEVICE_DFP2_SUPPORT         (0x1L << ATOM_DEVICE_DFP2_INDEX )
#define ATOM_DEVICE_CV_SUPPORT           (0x1L << ATOM_DEVICE_CV_INDEX   )
#define ATOM_DEVICE_DFP3_SUPPORT         (0x1L << ATOM_DEVICE_DFP3_INDEX )
#define ATOM_DEVICE_DFP4_SUPPORT         (0x1L << ATOM_DEVICE_DFP4_INDEX )
#define ATOM_DEVICE_DFP5_SUPPORT         (0x1L << ATOM_DEVICE_DFP5_INDEX )


#define ATOM_DEVICE_CRT_SUPPORT          (ATOM_DEVICE_CRT1_SUPPORT | ATOM_DEVICE_CRT2_SUPPORT)
#define ATOM_DEVICE_DFP_SUPPORT          (ATOM_DEVICE_DFP1_SUPPORT | ATOM_DEVICE_DFP2_SUPPORT |  ATOM_DEVICE_DFP3_SUPPORT | ATOM_DEVICE_DFP4_SUPPORT | ATOM_DEVICE_DFP5_SUPPORT | ATOM_DEVICE_DFP6_SUPPORT)
#define ATOM_DEVICE_TV_SUPPORT           ATOM_DEVICE_TV1_SUPPORT
#define ATOM_DEVICE_LCD_SUPPORT          (ATOM_DEVICE_LCD1_SUPPORT | ATOM_DEVICE_LCD2_SUPPORT)

#define ATOM_DEVICE_CONNECTOR_TYPE_MASK   0x000000F0
#define ATOM_DEVICE_CONNECTOR_TYPE_SHIFT  0x00000004
#define ATOM_DEVICE_CONNECTOR_VGA         0x00000001
#define ATOM_DEVICE_CONNECTOR_DVI_I       0x00000002
#define ATOM_DEVICE_CONNECTOR_DVI_D       0x00000003
#define ATOM_DEVICE_CONNECTOR_DVI_A       0x00000004
#define ATOM_DEVICE_CONNECTOR_SVIDEO      0x00000005
#define ATOM_DEVICE_CONNECTOR_COMPOSITE   0x00000006
#define ATOM_DEVICE_CONNECTOR_LVDS        0x00000007
#define ATOM_DEVICE_CONNECTOR_DIGI_LINK   0x00000008
#define ATOM_DEVICE_CONNECTOR_SCART       0x00000009
#define ATOM_DEVICE_CONNECTOR_HDMI_TYPE_A 0x0000000A
#define ATOM_DEVICE_CONNECTOR_HDMI_TYPE_B 0x0000000B
#define ATOM_DEVICE_CONNECTOR_CASE_1      0x0000000E
#define ATOM_DEVICE_CONNECTOR_DISPLAYPORT 0x0000000F


#define ATOM_DEVICE_DAC_INFO_MASK  0x0000000F
#define ATOM_DEVICE_DAC_INFO_SHIFT 0x00000000
#define ATOM_DEVICE_DAC_INFO_NODAC 0x00000000
#define ATOM_DEVICE_DAC_INFO_DACA  0x00000001
#define ATOM_DEVICE_DAC_INFO_DACB  0x00000002
#define ATOM_DEVICE_DAC_INFO_EXDAC 0x00000003

#define ATOM_DEVICE_I2C_ID_NOI2C 0x00000000

#define ATOM_DEVICE_I2C_LINEMUX_MASK  0x0000000F
#define ATOM_DEVICE_I2C_LINEMUX_SHIFT 0x00000000

#define ATOM_DEVICE_I2C_ID_MASK              0x00000070
#define ATOM_DEVICE_I2C_ID_SHIFT             0x00000004
#define ATOM_DEVICE_I2C_ID_IS_FOR_NON_MM_USE 0x00000001
#define ATOM_DEVICE_I2C_ID_IS_FOR_MM_USE     0x00000002
#define ATOM_DEVICE_I2C_ID_IS_FOR_SDVO_USE   0x00000003 // For IGP RS600
#define ATOM_DEVICE_I2C_ID_IS_FOR_DAC_SCL    0x00000004 // For IGP RS690

#define ATOM_DEVICE_I2C_HARDWARE_CAP_MASK      0x00000080
#define ATOM_DEVICE_I2C_HARDWARE_CAP_SHIFT     0x00000007
#define ATOM_DEVICE_USES_SOFTWARE_ASSISTED_I2C 0x00000000
#define ATOM_DEVICE_USES_HARDWARE_ASSISTED_I2C 0x00000001

// usDeviceSupport:
// Bits0   = 0 - no CRT1 support= 1- CRT1 is supported
// Bit 1   = 0 - no LCD1 support= 1- LCD1 is supported
// Bit 2   = 0 - no TV1  support= 1- TV1  is supported
// Bit 3   = 0 - no DFP1 support= 1- DFP1 is supported
// Bit 4   = 0 - no CRT2 support= 1- CRT2 is supported
// Bit 5   = 0 - no LCD2 support= 1- LCD2 is supported
// Bit 6   = 0 - no DFP6 support= 1- DFP6 is supported
// Bit 7   = 0 - no DFP2 support= 1- DFP2 is supported
// Bit 8   = 0 - no CV   support= 1- CV   is supported
// Bit 9   = 0 - no DFP3 support= 1- DFP3 is supported
// Bit 10= 0 - no DFP4 support= 1- DFP4 is supported
// Bit 11= 0 - no DFP5 support= 1- DFP5 is supported
//
//

/******************************************************************************/
// Structure used in MclkSS_InfoTable
/******************************************************************************/
// ucI2C_ConfigID
// [7:0] - I2C LINE Associate ID
// = 0   - no I2C
// [7]      -   HW_Cap        =   1,  [6:0]=HW assisted I2C ID(HW line selection)
// =   0,  [6:0]=SW assisted I2C ID
// [6-4]   - HW_ENGINE_ID  =   1,  HW engine for NON multimedia use
// =   2,   HW engine for Multimedia use
// =   3-7   Reserved for future I2C engines
// [3-0] - I2C_LINE_MUX  = A Mux number when it's HW assisted I2C or GPIO ID when it's SW I2C
/*
union atom_i2c_id_config {
	uint8_t  i2c_id;
	struct { uint8_t
		I2C_LineMux :3-0 +1, // A Mux number when it's HW assisted I2C or GPIO ID when it's SW I2C
		HW_EngineID :6-4 +1, // =1 HW engine for NON multimedia use; =2 HW engine for Multimedia use; 3-7 Reserved for future I2C engines
		HW_Capable  :7-7 +1; // =0 SW assisted I2C ID; =1 HW assisted I2C ID(HW line selection)
	};
};
*/
/*
union atom_i2c_id_config {
	union atom_i2c_id_config Access;
	uint8_t  Access;
};
*/


/******************************************************************************/
// Structure used in GPIO_I2C_InfoTable
/******************************************************************************/
struct atom_gpio_i2c_assigment {
	uint16_t ClkMaskRegisterIndex;
	uint16_t ClkEnRegisterIndex;
	uint16_t ClkY_RegisterIndex;
	uint16_t ClkA_RegisterIndex;
	uint16_t DataMaskRegisterIndex;
	uint16_t DataEnRegisterIndex;
	uint16_t DataY_RegisterIndex;
	uint16_t DataA_RegisterIndex;
	union atom_i2c_id_config I2cId;
	uint8_t  ClkMaskShift;
	uint8_t  ClkEnShift;
	uint8_t  ClkY_Shift;
	uint8_t  ClkA_Shift;
	uint8_t  DataMaskShift;
	uint8_t  DataEnShift;
	uint8_t  DataY_Shift;
	uint8_t  DataA_Shift;
	uint8_t  Reserved1;
	uint8_t  Reserved2;
};

struct atom_gpio_i2c_info {
	struct atom_common_table_header table_header;
	struct atom_gpio_i2c_assigment GPIO_Info[ATOM_MAX_SUPPORTED_DEVICE];
};

/******************************************************************************/
// Common Structure used in other structures
/******************************************************************************/
/* duplicate
#ifndef _H2INC
// Please don't add or expand this bitfield structure below, this one will retire soon.!
struct atom_mode_misc_info {
	uint16_t HorizontalCutOff:1;
	uint16_t HSyncPolarity:1; // 0=Active High, 1=Active Low
	uint16_t VSyncPolarity:1; // 0=Active High, 1=Active Low
	uint16_t VerticalCutOff:1;
	uint16_t H_ReplicationBy2:1;
	uint16_t V_ReplicationBy2:1;
	uint16_t CompositeSync:1;
	uint16_t Interlace:1;
	uint16_t DoubleClock:1;
	uint16_t RGB888:1;
	uint16_t Reserved:6;
};
union atom_dtd_format_modemiscinfo {
	struct atom_mode_misc_info Access;
	uint16_t Access;
};
#else
union atom_dtd_format_modemiscinfo {
	uint16_t Access;
};
#endif
// usModeMiscInfo-
#define ATOM_H_CUTOFF           0x01
#define ATOM_HSYNC_POLARITY     0x02 // 0=Active High, 1=Active Low
#define ATOM_VSYNC_POLARITY     0x04 // 0=Active High, 1=Active Low
#define ATOM_V_CUTOFF           0x08
#define ATOM_H_REPLICATIONBY2   0x10
#define ATOM_V_REPLICATIONBY2   0x20
#define ATOM_COMPOSITESYNC      0x40
#define ATOM_INTERLACE          0x80
#define ATOM_DOUBLE_CLOCK_MODE 0x100
#define ATOM_RGB888_MODE       0x200
*/

// usRefreshRate-
#define ATOM_REFRESH_43 43
#define ATOM_REFRESH_47 47
#define ATOM_REFRESH_56 56
#define ATOM_REFRESH_60 60
#define ATOM_REFRESH_65 65
#define ATOM_REFRESH_70 70
#define ATOM_REFRESH_72 72
#define ATOM_REFRESH_75 75
#define ATOM_REFRESH_85 85

// ATOM_MODE_TIMING data are exactly the same as VESA timing data.
// Translation from EDID to ATOM_MODE_TIMING, use the following formula.
//
// VESA_HTOTAL         =   VESA_ACTIVE + 2* VESA_BORDER + VESA_BLANK
// =   EDID_HA + EDID_HBL
// VESA_HDISP         =   VESA_ACTIVE   =   EDID_HA
// VESA_HSYNC_START   =   VESA_ACTIVE + VESA_BORDER + VESA_FRONT_PORCH
// =   EDID_HA + EDID_HSO
// VESA_HSYNC_WIDTH   =   VESA_HSYNC_TIME   =   EDID_HSPW
// VESA_BORDER         =   EDID_BORDER


/******************************************************************************/
// Structure used in SetCRTC_UsingDTDTimingTable
/******************************************************************************/
/* duplicate
struct set_crtc_using_dtd_timing_parameters {
	uint16_t H_Size;
	uint16_t H_Blanking_Time;
	uint16_t V_Size;
	uint16_t V_Blanking_Time;
	uint16_t H_SyncOffset;
	uint16_t H_SyncWidth;
	uint16_t V_SyncOffset;
	uint16_t V_SyncWidth;
	union atom_dtd_format_modemiscinfo usModeMiscInfo;
	uint8_t  H_Border; // From DFP EDID
	uint8_t  V_Border;
	uint8_t  CRTC;     // ATOM_CRTC1 or ATOM_CRTC2
	uint8_t  Padding[3];
};
*/
/******************************************************************************/
// Structure used in SetCRTC_TimingTable
/******************************************************************************/
struct set_crtc_timing_parameters {
	uint16_t H_Total;        // horizontal total
	uint16_t H_Disp;         // horizontal display
	uint16_t H_SyncStart;    // horozontal Sync start
	uint16_t H_SyncWidth;    // horizontal Sync width
	uint16_t V_Total;        // vertical total
	uint16_t V_Disp;         // vertical display
	uint16_t V_SyncStart;    // vertical Sync start
	uint16_t V_SyncWidth;    // vertical Sync width
	union atom_dtd_format_modemiscinfo usModeMiscInfo;
	uint8_t  CRTC;           // ATOM_CRTC1 or ATOM_CRTC2
	uint8_t  OverscanRight;  // right
	uint8_t  OverscanLeft;   // left
	uint8_t  OverscanBottom; // bottom
	uint8_t  OverscanTop;    // top
	uint8_t  Reserved;
};
#define SET_CRTC_TIMING_PARAMETERS_PS_ALLOCATION SET_CRTC_TIMING_PARAMETERS


/******************************************************************************/
// Structure used in StandardVESA_TimingTable
// AnalogTV_InfoTable
// ComponentVideoInfoTable
/******************************************************************************/
struct atom_mode_timing {
	uint16_t CRTC_H_Total;
	uint16_t CRTC_H_Disp;
	uint16_t CRTC_H_SyncStart;
	uint16_t CRTC_H_SyncWidth;
	uint16_t CRTC_V_Total;
	uint16_t CRTC_V_Disp;
	uint16_t CRTC_V_SyncStart;
	uint16_t CRTC_V_SyncWidth;
	uint16_t PixelClock; // in 10Khz unit
	union atom_dtd_format_modemiscinfo usModeMiscInfo;
	uint16_t CRTC_OverscanRight;
	uint16_t CRTC_OverscanLeft;
	uint16_t CRTC_OverscanBottom;
	uint16_t CRTC_OverscanTop;
	uint16_t Reserve;
	uint8_t  InternalModeNumber;
	uint8_t  RefreshRate;
};
/* duplicate
struct atom_dtd_format {
	uint16_t PixClk;
	uint16_t HActive;
	uint16_t HBlanking_Time;
	uint16_t VActive;
	uint16_t VBlanking_Time;
	uint16_t HSyncOffset;
	uint16_t HSyncWidth;
	uint16_t VSyncOffset;
	uint16_t VSyncWidth;
	uint16_t ImageHSize;
	uint16_t ImageVSize;
	uint8_t  HBorder;
	uint8_t  VBorder;
	union atom_dtd_format_modemiscinfo usModeMiscInfo;
	uint8_t  InternalModeNumber;
	uint8_t  RefreshRate;
};
*/

/******************************************************************************/
// Structure used in LVDS_InfoTable
// * Need a document to describe this table
/******************************************************************************/
#define SUPPORTED_LCD_REFRESHRATE_30Hz 0x0004
#define SUPPORTED_LCD_REFRESHRATE_40Hz 0x0008
#define SUPPORTED_LCD_REFRESHRATE_50Hz 0x0010
#define SUPPORTED_LCD_REFRESHRATE_60Hz 0x0020
#define SUPPORTED_LCD_REFRESHRATE_48Hz 0x0040

// ucTableFormatRevision=1
// ucTableContentRevision=1
struct atom_lvds_info {
	struct atom_common_table_header table_header;
	struct atom_dtd_format LCDTiming;
	uint16_t ModePatchTableOffset;
	uint16_t SupportedRefreshRate; // Refer to panel info table in ATOMBIOS extension Spec.
	uint16_t OffDelayInMs;
	uint8_t  PowerSequenceDigOntoDEin10Ms;
	uint8_t  PowerSequenceDEtoBLOnin10Ms;
	uint8_t  LVDS_Misc; // Bit0:{=0:single, =1:dual},Bit1 {=0:666RGB, =1:888RGB},Bit2:3:{Grey level}
                        // Bit4:{=0:LDI format for RGB888, =1 FPDI format for RGB888}
                        // Bit5:{=0:Spatial Dithering disabled;1 Spatial Dithering enabled}
                        // Bit6:{=0:Temporal Dithering disabled;1 Temporal Dithering enabled}
	uint8_t  PanelDefaultRefreshRate;
	uint8_t  PanelIdentification;
	uint8_t  SS_Id;
};

// ucTableFormatRevision=1
// ucTableContentRevision=2
struct atom_lvds_info_v12 {
	struct atom_common_table_header table_header;
	struct atom_dtd_format LCDTiming;
	uint16_t ExtInfoTableOffset;
	uint16_t SupportedRefreshRate;     // Refer to panel info table in ATOMBIOS extension Spec.
	uint16_t OffDelayInMs;
	uint8_t  PowerSequenceDigOntoDEin10Ms;
	uint8_t  PowerSequenceDEtoBLOnin10Ms;
	uint8_t  LVDS_Misc; // Bit0:{=0:single, =1:dual},Bit1 {=0:666RGB, =1:888RGB},Bit2:3:{Grey level}
                        // Bit4:{=0:LDI format for RGB888, =1 FPDI format for RGB888}
                        // Bit5:{=0:Spatial Dithering disabled;1 Spatial Dithering enabled}
                        // Bit6:{=0:Temporal Dithering disabled;1 Temporal Dithering enabled}
	uint8_t  PanelDefaultRefreshRate;
	uint8_t  PanelIdentification;
	uint8_t  SS_Id;
	uint16_t LCDVenderID;
	uint16_t LCDProductID;
	uint8_t  LCDPanel_SpecialHandlingCap;
	uint8_t  PanelInfoSize; // start from ATOM_DTD_FORMAT to end of panel info, include ExtInfoTable
	uint8_t  Reserved[2];
};

// Definitions for ucLCDPanel_SpecialHandlingCap:

// Once DAL sees this CAP is set, it will read EDID from LCD on its own instead of using sLCDTiming in ATOM_LVDS_INFO_V12.
// Other entries in ATOM_LVDS_INFO_V12 are still valid/useful to DAL
#define LCDPANEL_CAP_READ_EDID     0x1

// If a design supports DRR (dynamic refresh rate) on internal panels (LVDS or EDP), this cap is set in ucLCDPanel_SpecialHandlingCap together
// with multiple supported refresh rates@usSupportedRefreshRate. This cap should not be set when only slow refresh rate is supported (static
// refresh rate switch by SW. This is only valid from ATOM_LVDS_INFO_V12
#define LCDPANEL_CAP_DRR_SUPPORTED 0x2

// Use this cap bit for a quick reference whether an embadded panel (LCD1 ) is LVDS or eDP.
#define LCDPANEL_CAP_eDP           0x4

/*
Color Bit Depth definition in EDID V1.4 @BYTE 14h
Bit 6  5  4
    0  0  0 -  Color bit depth is undefined
    0  0  1 -  6 Bits per Primary Color
    0  1  0 -  8 Bits per Primary Color
    0  1  1 - 10 Bits per Primary Color
    1  0  0 - 12 Bits per Primary Color
    1  0  1 - 14 Bits per Primary Color
    1  1  0 - 16 Bits per Primary Color
    1  1  1 - Reserved
*/
#define PANEL_COLOR_BIT_DEPTH_MASK 0x70

// Bit7:{=0:Random Dithering disabled;1 Random Dithering enabled}
#define PANEL_RANDOM_DITHER 0x80
#define PANEL_RANDOM_DITHER_MASK 0x80

#define ATOM_LVDS_INFO_LAST  ATOM_LVDS_INFO_V12   // no need to change this


struct atom_lcd_refresh_rate_support {
	uint8_t  SupportedRefreshRate;
	uint8_t  MinRefreshRateForDRR;
};

/******************************************************************************/
// Structures used by LCD_InfoTable V1.3    Note: previous version was called ATOM_LVDS_INFO_V12
// ASIC Families:  NI
// ucTableFormatRevision=1
// ucTableContentRevision=3
/******************************************************************************/
struct atom_lcd_info_v13 {
	struct atom_common_table_header table_header;
	struct atom_dtd_format LCDTiming;
	uint16_t ExtInfoTableOffset;
	union {
		uint16_t SupportedRefreshRate;
		struct atom_lcd_refresh_rate_support RefreshRateSupport;
	};
	uint32_t Reserved0;
	uint8_t  LCD_Misc; // Reorganized in V13
                       // Bit0: {=0:single, =1:dual},
                       // Bit1: {=0:LDI format for RGB888, =1 FPDI format for RGB888}  // was {=0:666RGB, =1:888RGB},
                       // Bit3:2: {Grey level}
                       // Bit6:4 Color Bit Depth definition (see below definition in EDID V1.4 @BYTE 14h)
                       // Bit7   Reserved.  was for ATOM_PANEL_MISC_API_ENABLED, still need it?
	uint8_t  PanelDefaultRefreshRate;
	uint8_t  PanelIdentification;
	uint8_t  SS_Id;
	uint16_t LCDVenderID;
	uint16_t LCDProductID;
	uint8_t  LCDPanel_SpecialHandlingCap; // Reorganized in V13
                                          // Bit0: Once DAL sees this CAP is set, it will read EDID from LCD on its own
                                          // Bit1: See LCDPANEL_CAP_DRR_SUPPORTED
                                          // Bit2: a quick reference whether an embadded panel (LCD1 ) is LVDS (0) or eDP (1)
                                          // Bit7-3: Reserved
	uint8_t  PanelInfoSize;               // start from ATOM_DTD_FORMAT to end of panel info, include ExtInfoTable
	uint16_t BacklightPWM; // Backlight PWM in Hz. New in _V13

	uint8_t  PowerSequenceDIGONtoDE_in4Ms;
	uint8_t  PowerSequenceDEtoVARY_BL_in4Ms;
	uint8_t  PowerSequenceVARY_BLtoDE_in4Ms;
	uint8_t  PowerSequenceDEtoDIGON_in4Ms;

	uint8_t  OffDelay_in4Ms;
	uint8_t  PowerSequenceVARY_BLtoBLON_in4Ms;
	uint8_t  PowerSequenceBLONtoVARY_BL_in4Ms;
	uint8_t  Reserved1;

	uint8_t  DPCD_eDP_CONFIGURATION_CAP; // dpcd 0dh
	uint8_t  DPCD_MAX_LINK_RATE;         // dpcd 01h
	uint8_t  DPCD_MAX_LANE_COUNT;        // dpcd 02h
	uint8_t  DPCD_MAX_DOWNSPREAD;        // dpcd 03h

	uint16_t MaxPclkFreqInSingleLink; // Max PixelClock frequency in single link mode.
	uint8_t  eDPToLVDSRxId;
	uint8_t  LcdReservd;
	uint32_t Reserved[2];
};

#define ATOM_LCD_INFO_LAST  ATOM_LCD_INFO_V13

// Definitions for ucLCD_Misc
#define ATOM_PANEL_MISC_V13_DUAL                   0x00000001
#define ATOM_PANEL_MISC_V13_FPDI                   0x00000002
#define ATOM_PANEL_MISC_V13_GREY_LEVEL             0x0000000C
#define ATOM_PANEL_MISC_V13_GREY_LEVEL_SHIFT       2
#define ATOM_PANEL_MISC_V13_COLOR_BIT_DEPTH_MASK   0x70
#define ATOM_PANEL_MISC_V13_6BIT_PER_COLOR         0x10
#define ATOM_PANEL_MISC_V13_8BIT_PER_COLOR         0x20

// Color Bit Depth definition in EDID V1.4 @BYTE 14h
// Bit 6  5  4
//     0  0  0 -  Color bit depth is undefined
//     0  0  1 -  6 Bits per Primary Color
//     0  1  0 -  8 Bits per Primary Color
//     0  1  1 - 10 Bits per Primary Color
//     1  0  0 - 12 Bits per Primary Color
//     1  0  1 - 14 Bits per Primary Color
//     1  1  0 - 16 Bits per Primary Color
//     1  1  1 - Reserved

// Definitions for ucLCDPanel_SpecialHandlingCap:

// Once DAL sees this CAP is set, it will read EDID from LCD on its own instead of using sLCDTiming in ATOM_LVDS_INFO_V12.
// Other entries in ATOM_LVDS_INFO_V12 are still valid/useful to DAL
#define LCDPANEL_CAP_V13_READ_EDID     0x1 // = LCDPANEL_CAP_READ_EDID no change comparing to previous version

// If a design supports DRR (dynamic refresh rate) on internal panels (LVDS or EDP), this cap is set in ucLCDPanel_SpecialHandlingCap together
// with multiple supported refresh rates@usSupportedRefreshRate. This cap should not be set when only slow refresh rate is supported (static
// refresh rate switch by SW. This is only valid from ATOM_LVDS_INFO_V12
#define LCDPANEL_CAP_V13_DRR_SUPPORTED 0x2 // = LCDPANEL_CAP_DRR_SUPPORTED no change comparing to previous version

// Use this cap bit for a quick reference whether an embadded panel (LCD1 ) is LVDS or eDP.
#define LCDPANEL_CAP_V13_eDP           0x4 // = LCDPANEL_CAP_eDP no change comparing to previous version

// uceDPToLVDSRxId
#define eDP_TO_LVDS_RX_DISABLE 0x00 // no eDP->LVDS translator chip
#define eDP_TO_LVDS_COMMON_ID  0x01 // common eDP->LVDS translator chip without AMD SW init
#define eDP_TO_LVDS_RT_ID      0x02 // RT tansaltor which require AMD SW init

struct atom_patch_record_mode {
	uint8_t  RecordType;
	uint16_t HDisp;
	uint16_t VDisp;
};

struct atom_lcd_rts_record {
	uint8_t  RecordType;
	uint8_t  RTSValue;
};

// !! If the record below exits, it shoud always be the first record for easy use in command table!!!
// The record below is only used when LVDS_Info is present. From ATOM_LVDS_INFO_V12, use ucLCDPanel_SpecialHandlingCap instead.
struct atom_lcd_mode_control_cap {
	uint8_t  RecordType;
	uint16_t LCDCap;
};

#define LCD_MODE_CAP_BL_OFF    1
#define LCD_MODE_CAP_CRTC_OFF  2
#define LCD_MODE_CAP_PANEL_OFF 4


struct atom_fake_edid_patch_record {
	uint8_t  RecordType;
	uint8_t  FakeEDIDLength;   // = 128 means EDID length is 128 bytes, otherwise the EDID length = ucFakeEDIDLength*128
	uint8_t  FakeEDIDString[]; // This actually has ucFakeEdidLength elements.
};

struct atom_panel_resolution_patch_record {
	uint8_t  RecordType;
	uint16_t HSize;
	uint16_t VSize;
};

#define LCD_MODE_PATCH_RECORD_MODE_TYPE   1
#define LCD_RTS_RECORD_TYPE               2
#define LCD_CAP_RECORD_TYPE               3
#define LCD_FAKE_EDID_PATCH_RECORD_TYPE   4
#define LCD_PANEL_RESOLUTION_RECORD_TYPE  5
#define LCD_EDID_OFFSET_PATCH_RECORD_TYPE 6
#define ATOM_RECORD_END_TYPE              0xFF

/******************************************************************************/
// Spread Spectrum Info Table Definitions
/******************************************************************************/

// ucTableFormatRevision=1
// ucTableContentRevision=2
struct atom_spread_spectrum_assignment {
	uint16_t SpreadSpectrumPercentage;
	uint8_t  SpreadSpectrumType; // Bit1=0 Down Spread,=1 Center Spread. Bit1=1 Ext. =0 Int. Bit2=1: PCIE REFCLK SS =0 iternal PPLL SS  Others:TBD
	uint8_t  SS_Step;
	uint8_t  SS_Delay;
	uint8_t  SS_Id;
	uint8_t  RecommendedRef_Div;
	uint8_t  SS_Range; // it was reserved for V11
};

#define ATOM_MAX_SS_ENTRY         16
#define ATOM_DP_SS_ID1            0x0f1 // SS ID for internal DP stream at 2.7Ghz. if ATOM_DP_SS_ID2 does not exist in SS_InfoTable, it is used for internal DP stream at 1.62Ghz as well.
#define ATOM_DP_SS_ID2            0x0f2 // SS ID for internal DP stream at 1.62Ghz, if it exists in SS_InfoTable.
#define ATOM_LVLINK_2700MHz_SS_ID 0x0f3 // SS ID for LV link translator chip at 2.7Ghz
#define ATOM_LVLINK_1620MHz_SS_ID 0x0f4 // SS ID for LV link translator chip at 1.62Ghz



#define ATOM_SS_DOWN_SPREAD_MODE_MASK   0x00000000
#define ATOM_SS_DOWN_SPREAD_MODE        0x00000000
#define ATOM_SS_CENTRE_SPREAD_MODE_MASK 0x00000001
#define ATOM_SS_CENTRE_SPREAD_MODE      0x00000001
#define ATOM_INTERNAL_SS_MASK           0x00000000
#define ATOM_EXTERNAL_SS_MASK           0x00000002
#define EXEC_SS_STEP_SIZE_SHIFT         2
#define EXEC_SS_DELAY_SHIFT             4
#define ACTIVEDATA_TO_BLON_DELAY_SHIFT  4

struct atom_spread_spectrum_info {
	struct atom_common_table_header table_header;
	struct atom_spread_spectrum_assignment SS_Info[ATOM_MAX_SS_ENTRY];
};


/******************************************************************************/
// Structure used in AnalogTV_InfoTable (Top level)
/******************************************************************************/
// ucTVBootUpDefaultStd definiton:

// ATOM_TV_NTSC  1
// ATOM_TV_NTSCJ 2
// ATOM_TV_PAL   3
// ATOM_TV_PALM  4
// ATOM_TV_PALCN 5
// ATOM_TV_PALN  6
// ATOM_TV_PAL60 7
// ATOM_TV_SECAM 8

// ucTVSuppportedStd definition:
#define NTSC_SUPPORT  0x1
#define NTSCJ_SUPPORT 0x2

#define PAL_SUPPORT   0x4
#define PALM_SUPPORT  0x8
#define PALCN_SUPPORT 0x10
#define PALN_SUPPORT  0x20
#define PAL60_SUPPORT 0x40
#define SECAM_SUPPORT 0x80

#define MAX_SUPPORTED_TV_TIMING 2

struct atom_analog_tv_info {
	struct atom_common_table_header table_header;
	uint8_t  TV_SuppportedStandard;
	uint8_t  TV_BootUpDefaultStandard;
	uint8_t  Ext_TV_ASIC_ID;
	uint8_t  Ext_TV_ASIC_SlaveAddr;
	struct atom_dtd_format aModeTimings[MAX_SUPPORTED_TV_TIMING];
};

struct atom_dpcd_info {
	uint8_t  RevisionNumber; // 10h : Revision 1.0; 11h : Revision 1.1
	uint8_t  MaxLinkRate;    // 06h : 1.62Gbps per lane; 0Ah = 2.7Gbps per lane
	uint8_t  MaxLane;        // Bits 4:0 = MAX_LANE_COUNT (1/2/4). Bit 7 = ENHANCED_FRAME_CAP
	uint8_t  MaxDownSpread;  // Bit0 = 0: No Down spread; Bit0 = 1: 0.5% (Subject to change according to DP spec)
};

#define ATOM_DPCD_MAX_LANE_MASK 0x1F

/******************************************************************************/
// VRAM usage and their defintions

// One chunk of VRAM used by Bios are for HWICON surfaces,EDID data.
// Current Mode timing and Dail Timing and/or STD timing data EACH device. They can be broken down as below.
// All the addresses below are the offsets from the frame buffer start.They all MUST be Dword aligned!
// To driver: The physical address of this memory portion=mmFB_START(4K aligned)+ATOMBIOS_VRAM_USAGE_START_ADDR+ATOM_x_ADDR
// To Bios:  ATOMBIOS_VRAM_USAGE_START_ADDR+ATOM_x_ADDR->MM_INDEX

// Moved VESA_MEMORY_IN_64K_BLOCK definition to "AtomConfig.h" so that it can be redefined in design (SKU).
// #ifndef VESA_MEMORY_IN_64K_BLOCK
// #define VESA_MEMORY_IN_64K_BLOCK        0x100       //256*64K=16Mb (Max. VESA memory is 16Mb!)
// #endif

#define ATOM_EDID_RAW_DATASIZE          256  // In Bytes
#define ATOM_HWICON_SURFACE_SIZE        4096 // In Bytes
#define ATOM_HWICON_INFOTABLE_SIZE      32
#define MAX_DTD_MODE_IN_VRAM            6
#define ATOM_DTD_MODE_SUPPORT_TBL_SIZE  (MAX_DTD_MODE_IN_VRAM*28) // 28= (SIZEOF ATOM_DTD_FORMAT)
#define ATOM_STD_MODE_SUPPORT_TBL_SIZE  32*8 // 32 is a predefined number,8= (SIZEOF ATOM_STD_FORMAT)
// 20 bytes for Encoder Type and DPCD in STD EDID area
#define DFP_ENCODER_TYPE_OFFSET         (ATOM_EDID_RAW_DATASIZE + ATOM_DTD_MODE_SUPPORT_TBL_SIZE + ATOM_STD_MODE_SUPPORT_TBL_SIZE - 20)
#define ATOM_DP_DPCD_OFFSET             (DFP_ENCODER_TYPE_OFFSET + 4 )

#define ATOM_HWICON1_SURFACE_ADDR       0
#define ATOM_HWICON2_SURFACE_ADDR       (ATOM_HWICON1_SURFACE_ADDR + ATOM_HWICON_SURFACE_SIZE)
#define ATOM_HWICON_INFOTABLE_ADDR      (ATOM_HWICON2_SURFACE_ADDR + ATOM_HWICON_SURFACE_SIZE)
#define ATOM_CRT1_EDID_ADDR             (ATOM_HWICON_INFOTABLE_ADDR + ATOM_HWICON_INFOTABLE_SIZE)
#define ATOM_CRT1_DTD_MODE_TBL_ADDR     (ATOM_CRT1_EDID_ADDR + ATOM_EDID_RAW_DATASIZE)
#define ATOM_CRT1_STD_MODE_TBL_ADDR       (ATOM_CRT1_DTD_MODE_TBL_ADDR + ATOM_DTD_MODE_SUPPORT_TBL_SIZE)

#define ATOM_LCD1_EDID_ADDR             (ATOM_CRT1_STD_MODE_TBL_ADDR + ATOM_STD_MODE_SUPPORT_TBL_SIZE)
#define ATOM_LCD1_DTD_MODE_TBL_ADDR     (ATOM_LCD1_EDID_ADDR + ATOM_EDID_RAW_DATASIZE)
#define ATOM_LCD1_STD_MODE_TBL_ADDR      (ATOM_LCD1_DTD_MODE_TBL_ADDR + ATOM_DTD_MODE_SUPPORT_TBL_SIZE)

#define ATOM_TV1_DTD_MODE_TBL_ADDR      (ATOM_LCD1_STD_MODE_TBL_ADDR + ATOM_STD_MODE_SUPPORT_TBL_SIZE)

#define ATOM_DFP1_EDID_ADDR             (ATOM_TV1_DTD_MODE_TBL_ADDR + ATOM_DTD_MODE_SUPPORT_TBL_SIZE)
#define ATOM_DFP1_DTD_MODE_TBL_ADDR     (ATOM_DFP1_EDID_ADDR + ATOM_EDID_RAW_DATASIZE)
#define ATOM_DFP1_STD_MODE_TBL_ADDR       (ATOM_DFP1_DTD_MODE_TBL_ADDR + ATOM_DTD_MODE_SUPPORT_TBL_SIZE)

#define ATOM_CRT2_EDID_ADDR             (ATOM_DFP1_STD_MODE_TBL_ADDR + ATOM_STD_MODE_SUPPORT_TBL_SIZE)
#define ATOM_CRT2_DTD_MODE_TBL_ADDR     (ATOM_CRT2_EDID_ADDR + ATOM_EDID_RAW_DATASIZE)
#define ATOM_CRT2_STD_MODE_TBL_ADDR       (ATOM_CRT2_DTD_MODE_TBL_ADDR + ATOM_DTD_MODE_SUPPORT_TBL_SIZE)

#define ATOM_LCD2_EDID_ADDR             (ATOM_CRT2_STD_MODE_TBL_ADDR + ATOM_STD_MODE_SUPPORT_TBL_SIZE)
#define ATOM_LCD2_DTD_MODE_TBL_ADDR     (ATOM_LCD2_EDID_ADDR + ATOM_EDID_RAW_DATASIZE)
#define ATOM_LCD2_STD_MODE_TBL_ADDR      (ATOM_LCD2_DTD_MODE_TBL_ADDR + ATOM_DTD_MODE_SUPPORT_TBL_SIZE)

#define ATOM_DFP6_EDID_ADDR             (ATOM_LCD2_STD_MODE_TBL_ADDR + ATOM_STD_MODE_SUPPORT_TBL_SIZE)
#define ATOM_DFP6_DTD_MODE_TBL_ADDR     (ATOM_DFP6_EDID_ADDR + ATOM_EDID_RAW_DATASIZE)
#define ATOM_DFP6_STD_MODE_TBL_ADDR     (ATOM_DFP6_DTD_MODE_TBL_ADDR + ATOM_DTD_MODE_SUPPORT_TBL_SIZE)

#define ATOM_DFP2_EDID_ADDR             (ATOM_DFP6_STD_MODE_TBL_ADDR + ATOM_STD_MODE_SUPPORT_TBL_SIZE)
#define ATOM_DFP2_DTD_MODE_TBL_ADDR     (ATOM_DFP2_EDID_ADDR + ATOM_EDID_RAW_DATASIZE)
#define ATOM_DFP2_STD_MODE_TBL_ADDR     (ATOM_DFP2_DTD_MODE_TBL_ADDR + ATOM_DTD_MODE_SUPPORT_TBL_SIZE)

#define ATOM_CV_EDID_ADDR               (ATOM_DFP2_STD_MODE_TBL_ADDR + ATOM_STD_MODE_SUPPORT_TBL_SIZE)
#define ATOM_CV_DTD_MODE_TBL_ADDR       (ATOM_CV_EDID_ADDR + ATOM_EDID_RAW_DATASIZE)
#define ATOM_CV_STD_MODE_TBL_ADDR       (ATOM_CV_DTD_MODE_TBL_ADDR + ATOM_DTD_MODE_SUPPORT_TBL_SIZE)

#define ATOM_DFP3_EDID_ADDR             (ATOM_CV_STD_MODE_TBL_ADDR + ATOM_STD_MODE_SUPPORT_TBL_SIZE)
#define ATOM_DFP3_DTD_MODE_TBL_ADDR     (ATOM_DFP3_EDID_ADDR + ATOM_EDID_RAW_DATASIZE)
#define ATOM_DFP3_STD_MODE_TBL_ADDR     (ATOM_DFP3_DTD_MODE_TBL_ADDR + ATOM_DTD_MODE_SUPPORT_TBL_SIZE)

#define ATOM_DFP4_EDID_ADDR             (ATOM_DFP3_STD_MODE_TBL_ADDR + ATOM_STD_MODE_SUPPORT_TBL_SIZE)
#define ATOM_DFP4_DTD_MODE_TBL_ADDR     (ATOM_DFP4_EDID_ADDR + ATOM_EDID_RAW_DATASIZE)
#define ATOM_DFP4_STD_MODE_TBL_ADDR     (ATOM_DFP4_DTD_MODE_TBL_ADDR + ATOM_DTD_MODE_SUPPORT_TBL_SIZE)

#define ATOM_DFP5_EDID_ADDR             (ATOM_DFP4_STD_MODE_TBL_ADDR + ATOM_STD_MODE_SUPPORT_TBL_SIZE)
#define ATOM_DFP5_DTD_MODE_TBL_ADDR     (ATOM_DFP5_EDID_ADDR + ATOM_EDID_RAW_DATASIZE)
#define ATOM_DFP5_STD_MODE_TBL_ADDR     (ATOM_DFP5_DTD_MODE_TBL_ADDR + ATOM_DTD_MODE_SUPPORT_TBL_SIZE)

#define ATOM_DP_TRAINING_TBL_ADDR       (ATOM_DFP5_STD_MODE_TBL_ADDR + ATOM_STD_MODE_SUPPORT_TBL_SIZE)

#define ATOM_STACK_STORAGE_START        (ATOM_DP_TRAINING_TBL_ADDR + 1024)
#define ATOM_STACK_STORAGE_END          ATOM_STACK_STORAGE_START + 512

// The size below is in Kb!
#define ATOM_VRAM_RESERVE_SIZE         ((((ATOM_STACK_STORAGE_END - ATOM_HWICON1_SURFACE_ADDR)>>10)+4)&0xFFFC)

#define ATOM_VRAM_RESERVE_V2_SIZE      32

#define ATOM_VRAM_OPERATION_FLAGS_MASK         0xC0000000L
#define ATOM_VRAM_OPERATION_FLAGS_SHIFT        30
#define ATOM_VRAM_BLOCK_NEEDS_NO_RESERVATION   0x1
#define ATOM_VRAM_BLOCK_NEEDS_RESERVATION      0x0
#define ATOM_VRAM_BLOCK_SRIOV_MSG_SHARE_RESERVATION 0x2

/***********************************************************************************/
// Structure used in VRAM_UsageByFirmwareTable
// Note1: This table is filled by SetBiosReservationStartInFB in CoreCommSubs.asm
// at running time.
// note2: From RV770, the memory is more than 32bit addressable, so we will change
// ucTableFormatRevision=1,ucTableContentRevision=4, the strcuture remains
// exactly same as 1.1 and 1.2 (1.3 is never in use), but ulStartAddrUsedByFirmware
// (in offset to start of memory address) is KB aligned instead of byte aligend.
// Note3:
/* If we change usReserved to "usFBUsedbyDrvInKB", then to VBIOS this usFBUsedbyDrvInKB is a predefined, unchanged
constant across VGA or non VGA adapter,
for CAIL, The size of FB access area is known, only thing missing is the Offset of FB Access area, so we can  have:

If (ulStartAddrUsedByFirmware!=0)
FBAccessAreaOffset= ulStartAddrUsedByFirmware - usFBUsedbyDrvInKB;
Reserved area has been claimed by VBIOS including this FB access area; CAIL doesn't need to reserve any extra area for this purpose
else   // Non VGA case
 if (FB_Size<=2Gb)
    FBAccessAreaOffset= FB_Size - usFBUsedbyDrvInKB;
 else
     FBAccessAreaOffset= Aper_Size - usFBUsedbyDrvInKB

CAIL needs to claim an reserved area defined by FBAccessAreaOffset and usFBUsedbyDrvInKB in non VGA case.*/

/***********************************************************************************/
#define ATOM_MAX_FIRMWARE_VRAM_USAGE_INFO 1

struct atom_firmware_vram_reserve_info {
	uint32_t StartAddrUsedByFirmware;
	uint16_t FirmwareUseInKb;
	uint16_t Reserved;
};

struct atom_vram_usage_by_firmware {
	struct atom_common_table_header table_header;
	struct atom_firmware_vram_reserve_info FirmwareVramReserveInfo[ATOM_MAX_FIRMWARE_VRAM_USAGE_INFO];
};

// change verion to 1.5, when allow driver to allocate the vram area for command table access.
struct atom_firmware_vram_reserve_info_v1_5 {
	uint32_t StartAddrUsedByFirmware;
	uint16_t FirmwareUseInKb;
	uint16_t FBUsedByDrvInKb;
};

struct atom_vram_usage_by_firmware_v1_5 {
	struct atom_common_table_header table_header;
	struct atom_firmware_vram_reserve_info_v1_5 FirmwareVramReserveInfo[ATOM_MAX_FIRMWARE_VRAM_USAGE_INFO];
};

/******************************************************************************/
// Structure used in GPIO_Pin_LUTTable
/******************************************************************************/
struct atom_gpio_pin_assignment {
	uint16_t GpioPin_AIndex;
	uint8_t  GpioPinBitShift;
	uint8_t  GPIO_ID;
};

// ucGPIO_ID pre-define id for multiple usage
// GPIO use to control PCIE_VDDC in certain SLT board
#define PCIE_VDDC_CONTROL_GPIO_PINID  56

// from SMU7.x, if ucGPIO_ID=PP_AC_DC_SWITCH_GPIO_PINID in GPIO_LUTTable, AC/DC switching feature is enable
#define PP_AC_DC_SWITCH_GPIO_PINID    60
// from SMU7.x, if ucGPIO_ID=VDDC_REGULATOR_VRHOT_GPIO_PINID in GPIO_LUTable, VRHot feature is enable
#define VDDC_VRHOT_GPIO_PINID         61
// if ucGPIO_ID=VDDC_PCC_GPIO_PINID in GPIO_LUTable, Peak Current Control feature is enabled
#define VDDC_PCC_GPIO_PINID           62
// Only used on certain SLT/PA board to allow utility to cut Efuse.
#define EFUSE_CUT_ENABLE_GPIO_PINID   63
// ucGPIO=DRAM_SELF_REFRESH_GPIO_PIND uses  for memory self refresh (ucGPIO=0, DRAM self-refresh; ucGPIO=
#define DRAM_SELF_REFRESH_GPIO_PINID  64
// Thermal interrupt output->system thermal chip GPIO pin
#define THERMAL_INT_OUTPUT_GPIO_PINID 65


struct atom_gpio_pin_lut {
	struct atom_common_table_header table_header;
	struct atom_gpio_pin_assignment GPIO_Pin[];
};

/******************************************************************************/
// Structure used in ComponentVideoInfoTable
/******************************************************************************/
#define GPIO_PIN_ACTIVE_HIGH       0x1
#define MAX_SUPPORTED_CV_STANDARDS 5

// definitions for ATOM_D_INFO.ucSettings
#define ATOM_GPIO_SETTINGS_BITSHIFT_MASK  0x1F // [4:0]
#define ATOM_GPIO_SETTINGS_RESERVED_MASK  0x60 // [6:5] = must be zeroed out
#define ATOM_GPIO_SETTINGS_ACTIVE_MASK    0x80 // [7]

struct atom_gpio_info {
	uint16_t AOffset;
	uint8_t  Settings;
	uint8_t  Reserved;
};

// definitions for ATOM_COMPONENT_VIDEO_INFO.ucMiscInfo (bit vector)
#define ATOM_CV_RESTRICT_FORMAT_SELECTION           0x2

// definitions for ATOM_COMPONENT_VIDEO_INFO.uc480i/uc480p/uc720p/uc1080i
#define ATOM_GPIO_DEFAULT_MODE_EN      0x80 // [7];
#define ATOM_GPIO_SETTING_PERMODE_MASK 0x7F // [6:0]

// definitions for ATOM_COMPONENT_VIDEO_INFO.ucLetterBoxMode
// Line 3 out put 5V.
#define ATOM_CV_LINE3_ASPECTRATIO_16_9_GPIO_A     0x01 // represent gpio 3 state for 16:9
#define ATOM_CV_LINE3_ASPECTRATIO_16_9_GPIO_B     0x02 // represent gpio 4 state for 16:9
#define ATOM_CV_LINE3_ASPECTRATIO_16_9_GPIO_SHIFT 0x0

// Line 3 out put 2.2V
#define ATOM_CV_LINE3_ASPECTRATIO_4_3_LETBOX_GPIO_A 0x04 // represent gpio 3 state for 4:3 Letter box
#define ATOM_CV_LINE3_ASPECTRATIO_4_3_LETBOX_GPIO_B 0x08 // represent gpio 4 state for 4:3 Letter box
#define ATOM_CV_LINE3_ASPECTRATIO_4_3_LETBOX_GPIO_SHIFT 0x2

// Line 3 out put 0V
#define ATOM_CV_LINE3_ASPECTRATIO_4_3_GPIO_A     0x10 // represent gpio 3 state for 4:3
#define ATOM_CV_LINE3_ASPECTRATIO_4_3_GPIO_B     0x20 // represent gpio 4 state for 4:3
#define ATOM_CV_LINE3_ASPECTRATIO_4_3_GPIO_SHIFT 0x4

#define ATOM_CV_LINE3_ASPECTRATIO_MASK           0x3F // bit [5:0]

#define ATOM_CV_LINE3_ASPECTRATIO_EXIST          0x80 // bit 7

// GPIO bit index in gpio setting per mode value, also represend the block no. in gpio blocks.
#define ATOM_GPIO_INDEX_LINE3_ASPECRATIO_GPIO_A 3 // bit 3 in uc480i/uc480p/uc720p/uc1080i, which represend the default gpio bit setting for the mode.
#define ATOM_GPIO_INDEX_LINE3_ASPECRATIO_GPIO_B 4 // bit 4 in uc480i/uc480p/uc720p/uc1080i, which represend the default gpio bit setting for the mode.


struct atom_component_video_info {
	struct atom_common_table_header table_header;
	uint16_t Mask_PinRegisterIndex;
	uint16_t EN_PinRegisterIndex;
	uint16_t Y_PinRegisterIndex;
	uint16_t A_PinRegisterIndex;
	uint8_t  BitShift;
	uint8_t  PinActiveState; // Bit0=1 active high, =0 active low
	struct atom_dtd_format Reserved; // must be zeroed out
	uint8_t  MiscInfo;
	uint8_t  res_480i;
	uint8_t  res_480p;
	uint8_t  res_720p;
	uint8_t  res_1080i;
	uint8_t  LetterBoxMode;
	uint8_t  Reserved2[3];
	uint8_t  NumOfWbGpioBlocks; // For Component video D-Connector support. If zere, NTSC type connector
	struct atom_gpio_info aWbGpioStateBlock[MAX_SUPPORTED_CV_STANDARDS];
	struct atom_dtd_format aModeTimings[MAX_SUPPORTED_CV_STANDARDS];
};

// ucTableFormatRevision=2
// ucTableContentRevision=1
struct atom_component_video_info_v21 {
	struct atom_common_table_header table_header;
	uint8_t  MiscInfo;
	uint8_t  res_480i;
	uint8_t  res_480p;
	uint8_t  res_720p;
	uint8_t  res_1080i;
	uint8_t  Reserved;
	uint8_t  LetterBoxMode;
	uint8_t  NumOfWbGpioBlocks; // For Component video D-Connector support. If zere, NTSC type connector
	struct atom_gpio_info aWbGpioStateBlock[MAX_SUPPORTED_CV_STANDARDS];
	struct atom_dtd_format aModeTimings[MAX_SUPPORTED_CV_STANDARDS];
};

#define ATOM_COMPONENT_VIDEO_INFO_LAST  ATOM_COMPONENT_VIDEO_INFO_V21

/******************************************************************************/
// Structure used in object_InfoTable
/******************************************************************************/
struct atom_object_header {
	struct atom_common_table_header table_header;
	uint16_t DeviceSupport;
	uint16_t ConnectorObjectTableOffset;
	uint16_t RouterObjectTableOffset;
	uint16_t EncoderObjectTableOffset;
	uint16_t ProtectionObjectTableOffset; // only available when Protection block is independent.
	uint16_t DisplayPathTableOffset;
};

struct atom_object_header_v3 {
	struct atom_common_table_header table_header;
	uint16_t DeviceSupport;
	uint16_t ConnectorObjectTableOffset;
	uint16_t RouterObjectTableOffset;
	uint16_t EncoderObjectTableOffset;
	uint16_t ProtectionObjectTableOffset; // only available when Protection block is independent.
	uint16_t DisplayPathTableOffset;
	uint16_t MiscObjectTableOffset;
};


struct atom_display_object_path {
	uint16_t DeviceTag;       // supported device
	uint16_t Size;            // the size of ATOM_DISPLAY_OBJECT_PATH
	uint16_t ConnObjectId;    // Connector Object ID
	uint16_t GPUObjectId;     // GPU ID
	uint16_t GraphicObjIds[]; // 1st Encoder Obj source from GPU to last Graphic Obj destinate to connector.
};

struct atom_display_external_object_path {
	uint16_t DeviceTag;        // supported device
	uint16_t Size;             // the size of ATOM_DISPLAY_OBJECT_PATH
	uint16_t ConnObjectId;     // Connector Object ID
	uint16_t GPUObjectId;      // GPU ID
	uint16_t GraphicObjIds[2]; // usGraphicObjIds[0]= GPU internal encoder, usGraphicObjIds[1]= external encoder
};

struct atom_display_object_path_table {
	uint8_t  NumOfDispPath;
	uint8_t  Version;
	uint8_t  Padding[2];
	struct atom_display_object_path DispPath[];
};

struct atom_object { // each object has this structure
	uint16_t ObjectID;
	uint16_t SrcDstTableOffset;
	uint16_t RecordOffset; // this pointing to a bunch of records defined below
	uint16_t Reserved;
};

struct atom_object_table { // Above 4 object table offset pointing to a bunch of objects all have this structure
	uint8_t  NumberOfObjects;
	uint8_t  Padding[3];
	struct atom_object Objects[];
};

struct atom_src_dst_table_for_one_object { // usSrcDstTableOffset pointing to this structure
	uint8_t  NumberOfSrc;
	uint16_t SrcObjectID[1];
	uint8_t  NumberOfDst;
	uint16_t DstObjectID[1];
};


// Two definitions below are for OPM on MXM module designs

#define EXT_HPDPIN_LUTINDEX_0 0
#define EXT_HPDPIN_LUTINDEX_1 1
#define EXT_HPDPIN_LUTINDEX_2 2
#define EXT_HPDPIN_LUTINDEX_3 3
#define EXT_HPDPIN_LUTINDEX_4 4
#define EXT_HPDPIN_LUTINDEX_5 5
#define EXT_HPDPIN_LUTINDEX_6 6
#define EXT_HPDPIN_LUTINDEX_7 7
#define MAX_NUMBER_OF_EXT_HPDPIN_LUT_ENTRIES   (EXT_HPDPIN_LUTINDEX_7+1)

#define EXT_AUXDDC_LUTINDEX_0 0
#define EXT_AUXDDC_LUTINDEX_1 1
#define EXT_AUXDDC_LUTINDEX_2 2
#define EXT_AUXDDC_LUTINDEX_3 3
#define EXT_AUXDDC_LUTINDEX_4 4
#define EXT_AUXDDC_LUTINDEX_5 5
#define EXT_AUXDDC_LUTINDEX_6 6
#define EXT_AUXDDC_LUTINDEX_7 7
#define MAX_NUMBER_OF_EXT_AUXDDC_LUT_ENTRIES   (EXT_AUXDDC_LUTINDEX_7+1)

// ucChannelMapping are defined as following
// for DP connector, eDP, DP to VGA/LVDS
// Bit[1:0]: Define which pin connect to DP connector DP_Lane0, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
// Bit[3:2]: Define which pin connect to DP connector DP_Lane1, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
// Bit[5:4]: Define which pin connect to DP connector DP_Lane2, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
// Bit[7:6]: Define which pin connect to DP connector DP_Lane3, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
struct atom_dp_conn_channel_mapping {
	uint8_t  DP_Lane0_Source:2;
	uint8_t  DP_Lane1_Source:2;
	uint8_t  DP_Lane2_Source:2;
	uint8_t  DP_Lane3_Source:2;
};

// for DVI/HDMI, in dual link case, both links have to have same mapping.
// Bit[1:0]: Define which pin connect to DVI connector data Lane2, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
// Bit[3:2]: Define which pin connect to DVI connector data Lane1, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
// Bit[5:4]: Define which pin connect to DVI connector data Lane0, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
// Bit[7:6]: Define which pin connect to DVI connector clock lane, =0: source from GPU pin TX0, =1: from GPU pin TX1, =2: from GPU pin TX2, =3 from GPU pin TX3
struct atom_dvi_conn_channel_mapping {
	uint8_t  DVI_DATA2_Source:2;
	uint8_t  DVI_DATA1_Source:2;
	uint8_t  DVI_DATA0_Source:2;
	uint8_t  DVI_CLK_Source:2;
};

struct ext_display_path {
	uint16_t DeviceTag;          // A bit vector to show what devices are supported
	uint16_t DeviceACPIEnum;     // 16bit device ACPI id.
	uint16_t DeviceConnector;    // A physical connector for displays to plug in, using object connector definitions
	uint8_t  ExtAUXDDCLutIndex;  // An index into external AUX/DDC channel LUT
	uint8_t  ExtHPDPINLutIndex;  // An index into external HPD pin LUT
	uint16_t ExtEncoderObjId;    // external encoder object id
	union {
		uint8_t  ChannelMapping; // if ucChannelMapping=0, using default one to one mapping
		struct atom_dp_conn_channel_mapping DPMapping;
		struct atom_dvi_conn_channel_mapping DVIMapping;
	};
	uint8_t  ChPNInvert; // bit vector for up to 8 lanes, =0: P and N is not invert, =1 P and N is inverted
	uint16_t Caps;
	uint16_t Reserved;
};


// usCaps
#define EXT_DISPLAY_PATH_CAPS__HBR2_DISABLE           0x0001
#define EXT_DISPLAY_PATH_CAPS__DP_FIXED_VS_EN         0x0002
#define EXT_DISPLAY_PATH_CAPS__EXT_CHIP_MASK          0x007C
#define EXT_DISPLAY_PATH_CAPS__HDMI20_PI3EQX1204      (0x01 << 2 ) // PI redriver chip
#define EXT_DISPLAY_PATH_CAPS__HDMI20_TISN65DP159RSBT (0x02 << 2 ) // TI retimer chip
#define EXT_DISPLAY_PATH_CAPS__HDMI20_PARADE_PS175    (0x03 << 2 ) // Parade DP->HDMI recoverter chip



/* duplicate
#define NUMBER_OF_uint8_t_FOR_GUID    16
#define MAX_NUMBER_OF_EXT_DISPLAY_PATH 7
struct atom_external_display_connection_info {
	struct atom_common_table_header table_header;
	uint8_t  Guid [NUMBER_OF_uint8_t_FOR_GUID]; // a GUID is a 16 byte long string
	struct ext_display_path Path[MAX_NUMBER_OF_EXT_DISPLAY_PATH]; // total of fixed 7 entries.
	uint8_t  Checksum; // a simple Checksum of the sum of whole structure equal to 0x0.
	uint8_t  _3DStereoPinId; // use for eDP panel
	uint8_t  RemoteDisplayConfig;
	uint8_t  eDPToLVDSRxId;
	uint8_t  FixDPVoltageSwing; // usCaps[1]=1, this indicate DP_LANE_SET value
	uint8_t  Reserved[3];      // for potential expansion
};
// Related definitions, all records are different but they have a common header
struct atom_common_record_header {
	uint8_t  RecordType; // An emun to indicate the record type
	uint8_t  RecordSize; // The size of the whole record in byte
};
*/


#define ATOM_I2C_RECORD_TYPE                           1
#define ATOM_HPD_INT_RECORD_TYPE                       2
#define ATOM_OUTPUT_PROTECTION_RECORD_TYPE             3
#define ATOM_CONNECTOR_DEVICE_TAG_RECORD_TYPE          4
#define ATOM_CONNECTOR_DVI_EXT_INPUT_RECORD_TYPE       5 // Obsolete, switch to use GPIO_CNTL_RECORD_TYPE
#define ATOM_ENCODER_FPGA_CONTROL_RECORD_TYPE          6 // Obsolete, switch to use GPIO_CNTL_RECORD_TYPE
#define ATOM_CONNECTOR_CVTV_SHARE_DIN_RECORD_TYPE      7
#define ATOM_JTAG_RECORD_TYPE                          8 // Obsolete, switch to use GPIO_CNTL_RECORD_TYPE
#define ATOM_OBJECT_GPIO_CNTL_RECORD_TYPE              9
#define ATOM_ENCODER_DVO_CF_RECORD_TYPE                10
#define ATOM_CONNECTOR_CF_RECORD_TYPE                  11
#define ATOM_CONNECTOR_HARDCODE_DTD_RECORD_TYPE        12
#define ATOM_CONNECTOR_PCIE_SUBCONNECTOR_RECORD_TYPE   13
#define ATOM_ROUTER_DDC_PATH_SELECT_RECORD_TYPE        14
#define ATOM_ROUTER_DATA_CLOCK_PATH_SELECT_RECORD_TYPE 15
#define ATOM_CONNECTOR_HPDPIN_LUT_RECORD_TYPE          16 // This is for the case when connectors are not known to object table
#define ATOM_CONNECTOR_AUXDDC_LUT_RECORD_TYPE          17 // This is for the case when connectors are not known to object table
#define ATOM_OBJECT_LINK_RECORD_TYPE                   18 // Once this record is present under one object, it indicats the oobject is linked to another obj described by the record
#define ATOM_CONNECTOR_REMOTE_CAP_RECORD_TYPE          19
#define ATOM_ENCODER_CAP_RECORD_TYPE                   20
#define ATOM_BRACKET_LAYOUT_RECORD_TYPE                21
#define ATOM_CONNECTOR_FORCED_TMDS_CAP_RECORD_TYPE     22

// Must be updated when new record type is added,equal to that record definition!
//#define ATOM_MAX_OBJECT_RECORD_NUMBER                  ATOM_CONNECTOR_FORCED_TMDS_CAP_RECORD_TYPE

/* duplicate
struct atom_i2c_record {
	struct atom_common_record_header header;
	union atom_i2c_id_config I2cId;
	uint8_t  I2CAddr; // The slave address, it's 0 when the record is attached to connector for DDC
};

struct atom_hpd_int_record {
	struct atom_common_record_header header;
	uint8_t  HPDIntGPIOID; // Corresponding block in GPIO_PIN_INFO table gives the pin info
	uint8_t  Plugged_PinState;
};
*/

struct atom_output_protection_record {
	struct atom_common_record_header header;
	uint8_t  ProtectionFlag;
	uint8_t  Reserved;
};

struct atom_connector_device_tag {
	uint32_t ACPIDeviceEnum; // Reserved for now
	uint16_t DeviceID; // This Id is same as "ATOM_DEVICE_XXX_SUPPORT"
	uint16_t Padding;
};

struct atom_connector_device_tag_record {
	struct atom_common_record_header header;
	uint8_t  NumberOfDevice;
	uint8_t  Reserved;
	struct atom_connector_device_tag DeviceTag[]; // This Id is same as "ATOM_DEVICE_XXX_SUPPORT"
};


struct atom_connector_dvi_ext_input_record {
	struct atom_common_record_header header;
	uint8_t  ConfigGPIOID;
	uint8_t  ConfigGPIOState; // Set to 1 when it's active high to enable external flow in
	uint8_t  FlowinGPIPID;
	uint8_t  ExtInGPIPID;
};

struct atom_encoder_fpga_control_record {
	struct atom_common_record_header header;
	uint8_t  CTL1GPIO_ID;
	uint8_t  CTL1GPIOState; // Set to 1 when it's active high
	uint8_t  CTL2GPIO_ID;
	uint8_t  CTL2GPIOState; // Set to 1 when it's active high
	uint8_t  CTL3GPIO_ID;
	uint8_t  CTL3GPIOState; // Set to 1 when it's active high
	uint8_t  CTLFPGA_IN_ID;
	uint8_t  Padding[3];
};

struct atom_connector_cvtv_share_din_record {
	struct atom_common_record_header header;
	uint8_t  GPIOID;        // Corresponding block in GPIO_PIN_INFO table gives the pin info
	uint8_t  TVActiveState; // Indicating when the pin==0 or 1 when TV is connected
};

struct atom_jtag_record {
	struct atom_common_record_header header;
	uint8_t  TMSGPIO_ID;
	uint8_t  TMSGPIOState; // Set to 1 when it's active high
	uint8_t  TCKGPIO_ID;
	uint8_t  TCKGPIOState; // Set to 1 when it's active high
	uint8_t  TDOGPIO_ID;
	uint8_t  TDOGPIOState; // Set to 1 when it's active high
	uint8_t  TDIGPIO_ID;
	uint8_t  TDIGPIOState; // Set to 1 when it's active high
	uint8_t  Padding[2];
};


/* duplicate
// The following generic object gpio pin control record type will replace JTAG_RECORD/FPGA_CONTROL_RECORD/DVI_EXT_INPUT_RECORD above gradually
struct atom_gpio_pin_control_pair {
	uint8_t  GPIOID;        // GPIO_ID, find the corresponding ID in GPIO_LUT table
	uint8_t  GPIO_PinState; // Pin state showing how to set-up the pin
};

struct atom_object_gpio_cntl_record {
	struct atom_common_record_header header;
	uint8_t  Flags;        // Future expnadibility
	uint8_t  NumberOfPins; // Number of GPIO pins used to control the object
	struct atom_gpio_pin_control_pair Gpio[]; // the real gpio pin pair determined by number of pins ucNumberOfPins
};
*/

// Definitions for GPIO pin state
#define GPIO_PIN_TYPE_INPUT             0x00
#define GPIO_PIN_TYPE_OUTPUT            0x10
#define GPIO_PIN_TYPE_HW_CONTROL        0x20

// For GPIO_PIN_TYPE_OUTPUT the following is defined
#define GPIO_PIN_OUTPUT_STATE_MASK      0x01
#define GPIO_PIN_OUTPUT_STATE_SHIFT     0
#define GPIO_PIN_STATE_ACTIVE_LOW       0x0
#define GPIO_PIN_STATE_ACTIVE_HIGH      0x1

// Indexes to GPIO array in GLSync record
// GLSync record is for Frame Lock/Gen Lock feature.
#define ATOM_GPIO_INDEX_GLSYNC_REFCLK    0
#define ATOM_GPIO_INDEX_GLSYNC_HSYNC     1
#define ATOM_GPIO_INDEX_GLSYNC_VSYNC     2
#define ATOM_GPIO_INDEX_GLSYNC_SWAP_REQ  3
#define ATOM_GPIO_INDEX_GLSYNC_SWAP_GNT  4
#define ATOM_GPIO_INDEX_GLSYNC_INTERRUPT 5
#define ATOM_GPIO_INDEX_GLSYNC_V_RESET   6
#define ATOM_GPIO_INDEX_GLSYNC_SWAP_CNTL 7
#define ATOM_GPIO_INDEX_GLSYNC_SWAP_SEL  8
#define ATOM_GPIO_INDEX_GLSYNC_MAX       9

struct atom_encoder_dvo_cf_record {
	struct atom_common_record_header header;
	uint32_t StrengthControl; // DVOA strength control for CF
	uint8_t  Padding[2];
};

// Bit maps for ATOM_ENCODER_CAP_RECORD.usEncoderCap
#define ATOM_ENCODER_CAP_RECORD_HBR2         0x01 // DP1.2 HBR2 is supported by HW encoder, it is retired in NI. the real meaning from SI is MST_EN
#define ATOM_ENCODER_CAP_RECORD_MST_EN       0x01 // from SI, this bit means DP MST is enable or not.
#define ATOM_ENCODER_CAP_RECORD_HBR2_EN      0x02 // DP1.2 HBR2 setting is qualified and HBR2 can be enabled
#define ATOM_ENCODER_CAP_RECORD_HDMI6Gbps_EN 0x04 // HDMI2.0 6Gbps enable or not.
#define ATOM_ENCODER_CAP_RECORD_HBR3_EN      0x08 // DP1.3 HBR3 is supported by board.

struct atom_encoder_cap_record {
	struct atom_common_record_header header;
	union {
		uint16_t EncoderCap;
		struct {
			uint16_t HBR2Cap:1;   // Bit0 is for DP1.2 HBR2 capability.
			uint16_t HBR2En:1;    // Bit1 is for DP1.2 HBR2 enable
			uint16_t Reserved:14; // Bit1-15 may be defined for other capability in future
		};
	};
};

// Used after SI
struct atom_encoder_cap_record_v2 {
	struct atom_common_record_header header;
	union {
		uint16_t EncoderCap;
		struct {
			uint16_t MSTEn:1;     // Bit0 is for DP1.2 MST enable
			uint16_t HBR2En:1;    // Bit1 is for DP1.2 HBR2 enable
			uint16_t HDMI6GEn:1;  // Bit2 is for HDMI6Gbps enable, this bit is used starting from CZ( APU) Ellemere (dGPU)
			uint16_t HBR3En:1;    // bit3 is for DP1.3 HBR3 enable
			uint16_t Reserved:12; // Bit4-15 may be defined for other capability in future
		};
	};
};


// value for ATOM_CONNECTOR_CF_RECORD.ucConnectedDvoBundle
#define ATOM_CONNECTOR_CF_RECORD_CONNECTED_UPPER12BITBUNDLEA 1
#define ATOM_CONNECTOR_CF_RECORD_CONNECTED_LOWER12BITBUNDLEB 2

struct atom_connector_cf_record {
	struct atom_common_record_header header;
	uint16_t MaxPixClk;
	uint8_t  FlowCntlGpioId;
	uint8_t  SwapCntlGpioId;
	uint8_t  ConnectedDvoBundle;
	uint8_t  Padding;
};

struct atom_connector_hardcode_dtd_record {
	struct atom_common_record_header header;
	struct atom_dtd_format Timing;
};

struct atom_connector_pcie_subconnector_record {
	struct atom_common_record_header header; // ATOM_CONNECTOR_PCIE_SUBCONNECTOR_RECORD_TYPE
	uint8_t  SubConnectorType; // CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_D|X_ID_DUAL_LINK_DVI_D|HDMI_TYPE_A
	uint8_t  Reserved;
};


struct atom_router_ddc_path_select_record {
	struct atom_common_record_header header;
	uint8_t  MuxType; // decide the number of ucMuxState, =0, no pin state, =1: single state with complement, >1: multiple state
	uint8_t  MuxControlPin;
	uint8_t  MuxState[2]; // for alligment purpose
};

struct atom_router_data_clock_path_select_record {
	struct atom_common_record_header header;
	uint8_t  MuxType;
	uint8_t  MuxControlPin;
	uint8_t  MuxState[2]; // for alligment purpose
};

// define ucMuxType
#define ATOM_ROUTER_MUX_PIN_STATE_MASK              0x0f
#define ATOM_ROUTER_MUX_PIN_SINGLE_STATE_COMPLEMENT 0x01

/* duplicate
struct atom_connector_hpdpin_lut_record { // record for ATOM_CONNECTOR_HPDPIN_LUT_RECORD_TYPE
	struct atom_common_record_header header;
	uint8_t  HPDPINMap[MAX_NUMBER_OF_EXT_HPDPIN_LUT_ENTRIES];  // An fixed size array which maps external pins to internal GPIO_PIN_INFO table
};

struct atom_connector_auxddc_lut_record { // record for ATOM_CONNECTOR_AUXDDC_LUT_RECORD_TYPE
	struct atom_common_record_header header;
	union atom_i2c_id_config ucAUXDDCMap[MAX_NUMBER_OF_EXT_AUXDDC_LUT_ENTRIES];  // An fixed size array which maps external pins to internal DDC ID
};
*/
struct atom_object_link_record {
	struct atom_common_record_header header;
	uint16_t ObjectID; // could be connector, encorder or other object in object.h
};

struct atom_connector_remote_cap_record {
	struct atom_common_record_header header;
	uint16_t Reserved;
};

/* duplicate
struct atom_connector_forced_tmds_cap_record {
	struct atom_common_record_header header;
  // override TMDS capability on this connector when it operate in TMDS mode.  usMaxTmdsClkRate = max TMDS Clock in Mhz/2.5
	uint8_t  MaxTmdsClkRateIn2_5Mhz;
	uint8_t  Reserved;
};


struct atom_connector_layout_info {
	uint16_t ConnectorObjectId;
	uint8_t  ConnectorType;
	uint8_t  Position;
};

// define ATOM_CONNECTOR_LAYOUT_INFO.ucConnectorType to describe the display connector size
#define CONNECTOR_TYPE_DVI_D             1
#define CONNECTOR_TYPE_DVI_I             2
#define CONNECTOR_TYPE_VGA               3
#define CONNECTOR_TYPE_HDMI              4
#define CONNECTOR_TYPE_DISPLAY_PORT      5
#define CONNECTOR_TYPE_MINI_DISPLAY_PORT 6

struct atom_bracket_layout_record {
	struct atom_common_record_header header;
	uint8_t  Length;
	uint8_t  Width;
	uint8_t  ConnNum;
	uint8_t  Reserved;
	struct atom_connector_layout_info ConnInfo[];
};
*/

/******************************************************************************/
// Structure used in XXXX
/******************************************************************************/
struct atom_voltage_info_header {
	uint16_t VDDCBaseLevel; // In number of 50mv unit
	uint16_t Reserved;      // For possible extension table offset
	uint8_t  NumOfVoltageEntries;
	uint8_t  BytesPerVoltageEntry;
	uint8_t  VoltageStep;   // Indicating in how many mv increament is one step, 0.5mv unit
	uint8_t  DefaultVoltageEntry;
	uint8_t  VoltageControlI2cLine;
	uint8_t  VoltageControlAddress;
	uint8_t  VoltageControlOffset;
};

struct atom_voltage_info {
	struct atom_common_table_header table_header;
	struct atom_voltage_info_header viHeader;
	uint8_t  VoltageEntries[64]; // 64 is for allocation, the actual number of entry is present at ucNumOfVoltageEntries*ucBytesPerVoltageEntry
};


struct atom_voltage_formula {
	uint16_t VoltageBaseLevel;     // In number of 1mv unit
	uint16_t VoltageStep;          // Indicating in how many mv increament is one step, 1mv unit
	uint8_t  NumOfVoltageEntries;  // Number of Voltage Entry, which indicate max Voltage
	uint8_t  Flag;                 // bit0=0 :step is 1mv =1 0.5mv
	uint8_t  BaseVID;              // if there is no lookup table, VID= BaseVID + ( Vol - BaseLevle ) /VoltageStep
	uint8_t  Reserved;
	uint8_t  VIDAdjustEntries[32]; // 32 is for allocation, the actual number of entry is present at ucNumOfVoltageEntries
};

struct voltage_lut_entry {
	uint16_t VoltageCode;  // The Voltage ID, either GPIO or I2C code
	uint16_t VoltageValue; // The corresponding Voltage Value, in mV
};

struct atom_voltage_formula_v2 {
	uint8_t  NumOfVoltageEntries; // Number of Voltage Entry, which indicate max Voltage
	uint8_t  Reserved[3];
	struct voltage_lut_entry VIDAdjustEntries[32]; // 32 is for allocation, the actual number of entries is in ucNumOfVoltageEntries
};

struct atom_voltage_control {
	uint8_t  VoltageControlId; // Indicate it is controlled by I2C or GPIO or HW state machine
	uint8_t  VoltageControlI2cLine;
	uint8_t  VoltageControlAddress;
	uint8_t  VoltageControlOffset;
	uint16_t GpioPin_AIndex;     // GPIO_PAD register index
	uint8_t  GpioPinBitShift[9]; // at most 8 pin support 255 VIDs, termintate with 0xff
	uint8_t  Reserved;
};

// Define ucVoltageControlId
#define VOLTAGE_CONTROLLED_BY_HW         0x00
#define VOLTAGE_CONTROLLED_BY_I2C_MASK   0x7F
#define VOLTAGE_CONTROLLED_BY_GPIO       0x80
#define VOLTAGE_CONTROL_ID_LM64          0x01 // I2C control, used for R5xx Core Voltage
#define VOLTAGE_CONTROL_ID_DAC           0x02 // I2C control, used for R5xx/R6xx MVDDC,MVDDQ or VDDCI
#define VOLTAGE_CONTROL_ID_VT116xM       0x03 // I2C control, used for R6xx Core Voltage
#define VOLTAGE_CONTROL_ID_DS4402        0x04
#define VOLTAGE_CONTROL_ID_UP6266        0x05
#define VOLTAGE_CONTROL_ID_SCORPIO       0x06
#define VOLTAGE_CONTROL_ID_VT1556M       0x07
#define VOLTAGE_CONTROL_ID_CHL822x       0x08
#define VOLTAGE_CONTROL_ID_VT1586M       0x09
#define VOLTAGE_CONTROL_ID_UP1637        0x0A
#define VOLTAGE_CONTROL_ID_CHL8214       0x0B
#define VOLTAGE_CONTROL_ID_UP1801        0x0C
#define VOLTAGE_CONTROL_ID_ST6788A       0x0D
#define VOLTAGE_CONTROL_ID_CHLIR3564SVI2 0x0E
#define VOLTAGE_CONTROL_ID_AD527x        0x0F
#define VOLTAGE_CONTROL_ID_NCP81022      0x10
#define VOLTAGE_CONTROL_ID_LTC2635       0x11
#define VOLTAGE_CONTROL_ID_NCP4208       0x12
#define VOLTAGE_CONTROL_ID_IR35xx        0x13
#define VOLTAGE_CONTROL_ID_RT9403        0x14

#define VOLTAGE_CONTROL_ID_GENERIC_I2C   0x40

struct atom_voltage_object {
	uint8_t  VoltageType; // Indicate Voltage Source: VDDC, MVDDC, MVDDQ or MVDDCI
	uint8_t  Size;        // Size of Object
	struct atom_voltage_control Control; // describ how to control
	struct atom_voltage_formula Formula; // Indicate How to convert real Voltage to VID
};

struct atom_voltage_object_v2 {
	uint8_t  VoltageType; // Indicate Voltage Source: VDDC, MVDDC, MVDDQ or MVDDCI
	uint8_t  Size;        // Size of Object
	struct atom_voltage_control Control;    // describ how to control
	struct atom_voltage_formula_v2 Formula; // Indicate How to convert real Voltage to VID
};

struct atom_voltage_object_info {
	struct atom_common_table_header table_header;
	struct atom_voltage_object VoltageObj[3]; // Info for Voltage control
};

struct atom_voltage_object_info_v2 {
	struct atom_common_table_header table_header;
	struct atom_voltage_object_v2 VoltageObj[3]; // Info for Voltage control
};

struct atom_leakid_voltage {
	uint8_t  LeakageId;
	uint8_t  Reserved;
	uint16_t Voltage;
};

struct atom_voltage_object_header_v3 {
	uint8_t  VoltageType; // Indicate Voltage Source: VDDC, MVDDC, MVDDQ or MVDDCI
	uint8_t  VoltageMode; // Indicate voltage control mode: Init/Set/Leakage/Set phase
	uint16_t Size;        // Size of Object
};

// ATOM_VOLTAGE_OBJECT_HEADER_V3.ucVoltageMode
#define VOLTAGE_OBJ_GPIO_LUT                0 // VOLTAGE and GPIO Lookup table ->ATOM_GPIO_VOLTAGE_OBJECT_V3
#define VOLTAGE_OBJ_VR_I2C_INIT_SEQ         3 // VOLTAGE REGULATOR INIT sequece through I2C -> ATOM_I2C_VOLTAGE_OBJECT_V3
#define VOLTAGE_OBJ_PHASE_LUT               4 // Set Vregulator Phase lookup table ->ATOM_GPIO_VOLTAGE_OBJECT_V3
#define VOLTAGE_OBJ_SVID2                   7 // Indicate voltage control by SVID2 ->ATOM_SVID2_VOLTAGE_OBJECT_V3
#define VOLTAGE_OBJ_EVV                     8
#define VOLTAGE_OBJ_PWRBOOST_LEAKAGE_LUT    0x10 // Powerboost Voltage and LeakageId lookup table->ATOM_LEAKAGE_VOLTAGE_OBJECT_V3
#define VOLTAGE_OBJ_HIGH_STATE_LEAKAGE_LUT  0x11 // High voltage state Voltage and LeakageId lookup table->ATOM_LEAKAGE_VOLTAGE_OBJECT_V3
#define VOLTAGE_OBJ_HIGH1_STATE_LEAKAGE_LUT 0x12 // High1 voltage state Voltage and LeakageId lookup table->ATOM_LEAKAGE_VOLTAGE_OBJECT_V3

struct voltage_lut_entry_v2 {
	uint32_t VoltageId;    // The Voltage ID which is used to program GPIO register
	uint16_t VoltageValue; // The corresponding Voltage Value, in mV
};

struct leakage_voltage_lut_entry_v2 {
	uint16_t VoltageLevel; // The Voltage ID which is used to program GPIO register
	uint16_t VoltageId;
	uint16_t LeakageId;    // The corresponding Voltage Value, in mV
};


struct atom_i2c_voltage_object_v3 {
	struct atom_voltage_object_header_v3 Header; // voltage mode = VOLTAGE_OBJ_VR_I2C_INIT_SEQ
	uint8_t  VoltageRegulatorId; // Indicate Voltage Regulator Id
	uint8_t  VoltageControlI2cLine;
	uint8_t  VoltageControlAddress;
	uint8_t  VoltageControlOffset;
	uint8_t  VoltageControlFlag; // Bit0: 0 - One byte data; 1 - Two byte data
	uint8_t  ulReserved[3];
	struct voltage_lut_entry VolI2cLut[]; // end with 0xff
};

// ATOM_I2C_VOLTAGE_OBJECT_V3.ucVoltageControlFlag
#define VOLTAGE_DATA_ONE_BYTE 0
#define VOLTAGE_DATA_TWO_BYTE 1

struct atom_gpio_voltage_object_v3 {
	struct atom_voltage_object_header_v3 Header; // voltage mode = VOLTAGE_OBJ_GPIO_LUT or VOLTAGE_OBJ_PHASE_LUT
	uint8_t  VoltageGpioCntlId; // default is 0 which indicate control through CG VID mode
	uint8_t  GpioEntryNum;      // indiate the entry numbers of Votlage/Gpio value Look up table
	uint8_t  PhaseDelay;        // phase delay in unit of micro second
	uint8_t  Reserved;
	uint32_t GpioMaskVal;       // GPIO Mask value
	struct voltage_lut_entry_v2 VolGpioLut[];
};

struct atom_leakage_voltage_object_v3 {
	struct atom_voltage_object_header_v3 Header; // voltage mode = 0x10/0x11/0x12
	uint8_t  LeakageCntlId;   // default is 0
	uint8_t  LeakageEntryNum; // indicate the entry number of LeakageId/Voltage Lut table
	uint8_t  Reserved[2];
	uint32_t MaxVoltageLevel;
	struct leakage_voltage_lut_entry_v2 LeakageIdLut[];
};


struct atom_svid2_voltage_object_v3 {
	struct atom_voltage_object_header_v3 Header; // voltage mode = VOLTAGE_OBJ_SVID2
// 14:7 - PSI0_VID
// 6 - PSI0_EN
// 5 - PSI1
// 4:2 - load line slope trim.
// 1:0 - offset trim,
	uint16_t LoadLine_PSI;
// GPU GPIO pin Id to SVID2 regulator VRHot pin. possible value 0~31. 0 means GPIO0, 31 means GPIO31
	uint8_t  SVDGpioId; // 0~31 indicate GPIO0~31
	uint8_t  SVCGpioId; // 0~31 indicate GPIO0~31
	uint32_t Reserved;
};



struct atom_merged_voltage_object_v3 {
	struct atom_voltage_object_header_v3 Header; // voltage mode = VOLTAGE_OBJ_MERGED_POWER
	uint8_t  MergedVType; // VDDC/VDCCI/....
	uint8_t  Reserved[3];
};


/* duplicate
struct atom_evv_dpm_info {
	uint32_t DPMSclk;      // DPM state SCLK
	uint16_t VAdjOffset;   // Adjust Voltage offset in unit of mv
	uint8_t  DPMTblVIndex; // Voltage Index in SMC_DPM_Table structure VddcTable/VddGfxTable
	uint8_t  DPMState;     // DPMState0~7
};

// ucVoltageMode = VOLTAGE_OBJ_EVV
struct atom_evv_voltage_object_v3 {
	struct atom_voltage_object_header_v3 Header; // voltage mode = VOLTAGE_OBJ_SVID2
	struct atom_evv_dpm_info EvvDpmList[8];
};
*/


union atom_voltage_object_v3{
	struct atom_gpio_voltage_object_v3 GpioVoltageObj;
	struct atom_i2c_voltage_object_v3 I2cVoltageObj;
	struct atom_leakage_voltage_object_v3 LeakageObj;
	struct atom_svid2_voltage_object_v3 SVID2Obj;
	struct atom_evv_voltage_object_v3 EvvObj;
};

struct atom_voltage_object_info_v3_1 {
	struct atom_common_table_header table_header;
	union atom_voltage_object_v3 asVoltageObj[3];   // Info for Voltage control
};


struct atom_asic_profile_voltage {
	uint8_t  ProfileId;
	uint8_t  Reserved;
	uint16_t Size;
	uint16_t EfuseSpareStartAddr;
	uint16_t FuseIndex[8]; // from LSB to MSB, Max 8bit,end of 0xffff if less than 8 efuse id,
	struct atom_leakid_voltage LeakVol[2]; // Leakid and relatd voltage
};

// ucProfileId
#define ATOM_ASIC_PROFILE_ID_EFUSE_VOLTAGE             1
#define ATOM_ASIC_PROFILE_ID_EFUSE_PERFORMANCE_VOLTAGE 1
#define ATOM_ASIC_PROFILE_ID_EFUSE_THERMAL_VOLTAGE     2

struct atom_asic_profiling_info {
	struct atom_common_table_header table_header;
	struct atom_asic_profile_voltage Voltage;
};

struct atom_asic_profiling_info_v2_1 {
	struct atom_common_table_header table_header;
	uint8_t  LeakageBinNum;             // indicate the entry number of LeakageId/Voltage Lut table
	uint16_t LeakageBinArrayOffset;     // offset of uint16_t Leakage Bin list array ( from lower LeakageId to higher)

	uint8_t  ElbVDDC_Num;
	uint16_t ElbVDDC_IdArrayOffset;     // offset of uint16_t virtual VDDC voltage id ( 0xff01~0xff08 )
	uint16_t ElbVDDC_LevelArrayOffset;  // offset of 2 dimension voltage level uint16_t array

	uint8_t  ElbVDDCI_Num;
	uint16_t ElbVDDCI_IdArrayOffset;    // offset of uint16_t virtual VDDCI voltage id ( 0xff01~0xff08 )
	uint16_t ElbVDDCI_LevelArrayOffset; // offset of 2 dimension voltage level uint16_t array
};


// Here is parameter to convert Efuse value to Measure value
// Measured = LN((2^Bitsize-1)/EFUSE-1)*(Range)/(-alpha)+(Max+Min)/2
struct efuse_logistic_func_param {
	uint16_t EfuseIndex;         // Efuse Index in DWORD address, for example Index 911, usEuseIndex=112
	uint8_t  EfuseBitLSB;        // Efuse bit LSB in DWORD address, for example Index 911, usEfuseBitLSB= 911-112*8=15
	uint8_t  EfuseLength;        // Efuse bits length,
	uint32_t EfuseEncodeRange;   // Range = Max - Min, bit31 indicate the efuse is negative number
	uint32_t EfuseEncodeAverage; // Average = ( Max + Min )/2
};

// Linear Function: Measured = Round ( Efuse * ( Max-Min )/(2^BitSize -1 ) + Min )
struct efuse_linear_func_param {
	uint16_t EfuseIndex;       // Efuse Index in DWORD address, for example Index 911, usEuseIndex=112
	uint8_t  EfuseBitLSB;      // Efuse bit LSB in DWORD address, for example Index 911, usEfuseBitLSB= 911-112*8=15
	uint8_t  EfuseLength;      // Efuse bits length,
	uint32_t EfuseEncodeRange; // Range = Max - Min, bit31 indicate the efuse is negative number
	uint32_t EfuseMin;         // Min
};


struct atom_asic_profiling_info_v3_1 {
	struct atom_common_table_header table_header;
	uint32_t EvvDerateTdp;
	uint32_t EvvDerateTdc;
	uint32_t BoardCoreTemp;
	uint32_t MaxVddc;
	uint32_t MinVddc;
	uint32_t LoadLineSlop;
	uint32_t LeakageTemp;
	uint32_t LeakageVoltage;
	struct efuse_linear_func_param CACm;
	struct efuse_linear_func_param CACb;
	struct efuse_logistic_func_param Kt_b;
	struct efuse_logistic_func_param Kv_m;
	struct efuse_logistic_func_param Kv_b;
	uint16_t LkgEuseIndex;
	uint8_t  LkgEfuseBitLSB;
	uint8_t  LkgEfuseLength;
	uint32_t LkgEncodeLn_MaxDivMin;
	uint32_t LkgEncodeMax;
	uint32_t LkgEncodeMin;
	uint32_t EfuseLogisticAlpha;
	uint16_t PowerDpm0;
	uint16_t CurrentDpm0;
	uint16_t PowerDpm1;
	uint16_t CurrentDpm1;
	uint16_t PowerDpm2;
	uint16_t CurrentDpm2;
	uint16_t PowerDpm3;
	uint16_t CurrentDpm3;
	uint16_t PowerDpm4;
	uint16_t CurrentDpm4;
	uint16_t PowerDpm5;
	uint16_t CurrentDpm5;
	uint16_t PowerDpm6;
	uint16_t CurrentDpm6;
	uint16_t PowerDpm7;
	uint16_t CurrentDpm7;
};


struct atom_asic_profiling_info_v3_2 {
	struct atom_common_table_header table_header;
	uint32_t EvvLkgFactor;
	uint32_t BoardCoreTemp;
	uint32_t MaxVddc;
	uint32_t MinVddc;
	uint32_t LoadLineSlop;
	uint32_t LeakageTemp;
	uint32_t LeakageVoltage;
	struct efuse_linear_func_param CACm;
	struct efuse_linear_func_param CACb;
	struct efuse_logistic_func_param Kt_b;
	struct efuse_logistic_func_param Kv_m;
	struct efuse_logistic_func_param Kv_b;
	uint16_t LkgEuseIndex;
	uint8_t  LkgEfuseBitLSB;
	uint8_t  LkgEfuseLength;
	uint32_t LkgEncodeLn_MaxDivMin;
	uint32_t LkgEncodeMax;
	uint32_t LkgEncodeMin;
	uint32_t EfuseLogisticAlpha;
	uint16_t PowerDpm0;
	uint16_t PowerDpm1;
	uint16_t PowerDpm2;
	uint16_t PowerDpm3;
	uint16_t PowerDpm4;
	uint16_t PowerDpm5;
	uint16_t PowerDpm6;
	uint16_t PowerDpm7;
	uint32_t TdpDerateDPM0;
	uint32_t TdpDerateDPM1;
	uint32_t TdpDerateDPM2;
	uint32_t TdpDerateDPM3;
	uint32_t TdpDerateDPM4;
	uint32_t TdpDerateDPM5;
	uint32_t TdpDerateDPM6;
	uint32_t TdpDerateDPM7;
};


// for Tonga/Fiji speed EVV algorithm
struct atom_asic_profiling_info_v3_3 {
	struct atom_common_table_header table_header;
	uint32_t EvvLkgFactor;
	uint32_t BoardCoreTemp;
	uint32_t MaxVddc;
	uint32_t MinVddc;
	uint32_t LoadLineSlop;
	uint32_t LeakageTemp;
	uint32_t LeakageVoltage;
	struct efuse_linear_func_param CACm;
	struct efuse_linear_func_param CACb;
	struct efuse_logistic_func_param Kt_b;
	struct efuse_logistic_func_param Kv_m;
	struct efuse_logistic_func_param Kv_b;
	uint16_t LkgEuseIndex;
	uint8_t  LkgEfuseBitLSB;
	uint8_t  LkgEfuseLength;
	uint32_t LkgEncodeLn_MaxDivMin;
	uint32_t LkgEncodeMax;
	uint32_t LkgEncodeMin;
	uint32_t EfuseLogisticAlpha;

	union {
		uint16_t PowerDpm0;
		uint16_t ParamNegFlag; // bit0 =1 :indicate ulRoBeta is Negative, bit1=1 indicate Kv_m  max is postive
	};
	uint16_t PowerDpm1;
	uint16_t PowerDpm2;
	uint16_t PowerDpm3;
	uint16_t PowerDpm4;
	uint16_t PowerDpm5;
	uint16_t PowerDpm6;
	uint16_t PowerDpm7;
	uint32_t TdpDerateDPM0;
	uint32_t TdpDerateDPM1;
	uint32_t TdpDerateDPM2;
	uint32_t TdpDerateDPM3;
	uint32_t TdpDerateDPM4;
	uint32_t TdpDerateDPM5;
	uint32_t TdpDerateDPM6;
	uint32_t TdpDerateDPM7;
	struct efuse_linear_func_param RoFuse;
	uint32_t RoAlpha;
	uint32_t RoBeta;
	uint32_t RoGamma;
	uint32_t RoEpsilon;
	uint32_t ATermRo;
	uint32_t BTermRo;
	uint32_t CTermRo;
	uint32_t SclkMargin;
	uint32_t FmaxPercent;
	uint32_t CRPercent;
	uint32_t SFmaxPercent;
	uint32_t SCRPercent;
	uint32_t SDCMargine;
};

// for Fiji speed EVV algorithm
struct atom_asic_profiling_info_v3_4 {
	struct atom_common_table_header table_header;
	uint32_t EvvLkgFactor;
	uint32_t BoardCoreTemp;
	uint32_t MaxVddc;
	uint32_t MinVddc;
	uint32_t LoadLineSlop;
	uint32_t LeakageTemp;
	uint32_t LeakageVoltage;
	struct efuse_linear_func_param CACm;
	struct efuse_linear_func_param CACb;
	struct efuse_logistic_func_param Kt_b;
	struct efuse_logistic_func_param Kv_m;
	struct efuse_logistic_func_param Kv_b;
	uint16_t LkgEuseIndex;
	uint8_t  LkgEfuseBitLSB;
	uint8_t  LkgEfuseLength;
	uint32_t LkgEncodeLn_MaxDivMin;
	uint32_t LkgEncodeMax;
	uint32_t LkgEncodeMin;
	uint32_t EfuseLogisticAlpha;
	uint16_t PowerDpm0;
	uint16_t PowerDpm1;
	uint16_t PowerDpm2;
	uint16_t PowerDpm3;
	uint16_t PowerDpm4;
	uint16_t PowerDpm5;
	uint16_t PowerDpm6;
	uint16_t PowerDpm7;
	uint32_t TdpDerateDPM0;
	uint32_t TdpDerateDPM1;
	uint32_t TdpDerateDPM2;
	uint32_t TdpDerateDPM3;
	uint32_t TdpDerateDPM4;
	uint32_t TdpDerateDPM5;
	uint32_t TdpDerateDPM6;
	uint32_t TdpDerateDPM7;
	struct efuse_linear_func_param RoFuse;
	uint32_t EvvDefaultVddc;
	uint32_t EvvNoCalcVddc;
	uint16_t ParamNegFlag;
	uint16_t Speed_Model;
	uint32_t SM_A0;
	uint32_t SM_A1;
	uint32_t SM_A2;
	uint32_t SM_A3;
	uint32_t SM_A4;
	uint32_t SM_A5;
	uint32_t SM_A6;
	uint32_t SM_A7;
	uint8_t  SM_A0_sign;
	uint8_t  SM_A1_sign;
	uint8_t  SM_A2_sign;
	uint8_t  SM_A3_sign;
	uint8_t  SM_A4_sign;
	uint8_t  SM_A5_sign;
	uint8_t  SM_A6_sign;
	uint8_t  SM_A7_sign;
	uint32_t Margin_RO_a;
	uint32_t Margin_RO_b;
	uint32_t Margin_RO_c;
	uint32_t Margin_fixed;
	uint32_t Margin_Fmax_mean;
	uint32_t Margin_plat_mean;
	uint32_t Margin_Fmax_sigma;
	uint32_t Margin_plat_sigma;
	uint32_t Margin_DC_sigma;
	uint32_t Reserved[8];            // Reserved for future ASIC
};

// for  Polaris10/Polaris11 speed EVV algorithm
struct atom_asic_profiling_info_v3_5 {
	struct atom_common_table_header table_header;
	uint32_t MaxVddc;               // Maximum voltage for all parts, in unit of 0.01mv
	uint32_t MinVddc;               // Minimum voltage for all parts, in unit of 0.01mv
	uint16_t LkgEuseIndex;          // Efuse Lkg_FT address ( BYTE address )
	uint8_t  LkgEfuseBitLSB;        // Efuse Lkg_FT bit shift in 32bit DWORD
	uint8_t  LkgEfuseLength;        // Efuse Lkg_FT length
	uint32_t LkgEncodeLn_MaxDivMin; // value of ln(Max_Lkg_Ft/Min_Lkg_Ft ) in unit of 0.00001 ( unit=100000 )
	uint32_t LkgEncodeMax;          // Maximum Lkg_Ft measured value ( or efuse decode value ), in unit of 0.00001 ( unit=100000 )
	uint32_t LkgEncodeMin;          // Minimum Lkg_Ft measured value ( or efuse decode value ), in unit of 0.00001 ( unit=100000 )
	struct efuse_linear_func_param RoFuse;// Efuse RO info: DWORD address, bit shift, length, max/min measure value. in unit of 1.
	uint32_t EvvDefaultVddc;        // def="EVV_DEFAULT_VDDC" descr="return default VDDC(v) when Efuse not cut" unit="100000"/>
	uint32_t EvvNoCalcVddc;         // def="EVV_NOCALC_VDDC" descr="return VDDC(v) when Calculation is bad" unit="100000"/>
	uint32_t Speed_Model;           // def="EVV_SPEED_MODEL" descr="0 = Greek model, 1 = multivariate model" unit="1"/>
	uint32_t SM_A0;                 // def="EVV_SM_A0" descr="Leakage coeff(Multivariant Mode)." unit="100000"/>
	uint32_t SM_A1;                 // def="EVV_SM_A1" descr="Leakage/SCLK coeff(Multivariant Mode)." unit="1000000"/>
	uint32_t SM_A2;                 // def="EVV_SM_A2" descr="Alpha( Greek Mode ) or VDDC/SCLK coeff(Multivariant Mode)." unit="100000"/>
	uint32_t SM_A3;                 // def="EVV_SM_A3" descr="Beta( Greek Mode ) or SCLK coeff(Multivariant Mode)." unit="100000"/>
	uint32_t SM_A4;                 // def="EVV_SM_A4" descr="VDDC^2/SCLK coeff(Multivariant Mode)." unit="100000"/>
	uint32_t SM_A5;                 // def="EVV_SM_A5" descr="VDDC^2 coeff(Multivariant Mode)." unit="100000"/>
	uint32_t SM_A6;                 // def="EVV_SM_A6" descr="Gamma( Greek Mode ) or VDDC coeff(Multivariant Mode)." unit="100000"/>
	uint32_t SM_A7;                 // def="EVV_SM_A7" descr="Epsilon( Greek Mode ) or constant(Multivariant Mode)." unit="100000"/>
	uint8_t  SM_A0_sign;            // def="EVV_SM_A0_SIGN" descr="=0 SM_A0 is postive. =1: SM_A0 is negative" unit="1"/>
	uint8_t  SM_A1_sign;            // def="EVV_SM_A1_SIGN" descr="=0 SM_A1 is postive. =1: SM_A1 is negative" unit="1"/>
	uint8_t  SM_A2_sign;            // def="EVV_SM_A2_SIGN" descr="=0 SM_A2 is postive. =1: SM_A2 is negative" unit="1"/>
	uint8_t  SM_A3_sign;            // def="EVV_SM_A3_SIGN" descr="=0 SM_A3 is postive. =1: SM_A3 is negative" unit="1"/>
	uint8_t  SM_A4_sign;            // def="EVV_SM_A4_SIGN" descr="=0 SM_A4 is postive. =1: SM_A4 is negative" unit="1"/>
	uint8_t  SM_A5_sign;            // def="EVV_SM_A5_SIGN" descr="=0 SM_A5 is postive. =1: SM_A5 is negative" unit="1"/>
	uint8_t  SM_A6_sign;            // def="EVV_SM_A6_SIGN" descr="=0 SM_A6 is postive. =1: SM_A6 is negative" unit="1"/>
	uint8_t  SM_A7_sign;            // def="EVV_SM_A7_SIGN" descr="=0 SM_A7 is postive. =1: SM_A7 is negative" unit="1"/>
	uint32_t Margin_RO_a;           // def="EVV_MARGIN_RO_A" descr="A Term to represent RO equation in Ax2+Bx+C, unit=1"
	uint32_t Margin_RO_b;           // def="EVV_MARGIN_RO_B" descr="B Term to represent RO equation in Ax2+Bx+C, unit=1"
	uint32_t Margin_RO_c;           // def="EVV_MARGIN_RO_C" descr="C Term to represent RO equation in Ax2+Bx+C, unit=1"
	uint32_t Margin_fixed;          // def="EVV_MARGIN_FIXED" descr="Fixed MHz to add to SCLK margin, unit=1" unit="1"/>
	uint32_t Margin_Fmax_mean;      // def="EVV_MARGIN_FMAX_MEAN" descr="Percentage to add for Fmas mean margin unit=10000" unit="10000"/>
	uint32_t Margin_plat_mean;      // def="EVV_MARGIN_PLAT_MEAN" descr="Percentage to add for platform mean margin unit=10000" unit="10000"/>
	uint32_t Margin_Fmax_sigma;     // def="EVV_MARGIN_FMAX_SIGMA" descr="Percentage to add for Fmax sigma margin unit=10000" unit="10000"/>
	uint32_t Margin_plat_sigma;     // def="EVV_MARGIN_PLAT_SIGMA" descr="Percentage to add for platform sigma margin unit=10000" unit="10000"/>
	uint32_t Margin_DC_sigma;       // def="EVV_MARGIN_DC_SIGMA" descr="Regulator DC tolerance margin (mV) unit=100" unit="100"/>
	uint32_t Reserved[12];
};

/* for Polars10/11 AVFS parameters */
struct atom_asic_profiling_info_v3_6 {
	struct atom_common_table_header table_header;
	uint32_t MaxVddc;
	uint32_t MinVddc;
	uint16_t LkgEuseIndex;
	uint8_t  LkgEfuseBitLSB;
	uint8_t  LkgEfuseLength;
	uint32_t LkgEncodeLn_MaxDivMin;
	uint32_t LkgEncodeMax;
	uint32_t LkgEncodeMin;
	struct efuse_linear_func_param RoFuse;
	uint32_t EvvDefaultVddc;
	uint32_t EvvNoCalcVddc;
	uint32_t Speed_Model;
	uint32_t SM_A0;
	uint32_t SM_A1;
	uint32_t SM_A2;
	uint32_t SM_A3;
	uint32_t SM_A4;
	uint32_t SM_A5;
	uint32_t SM_A6;
	uint32_t SM_A7;
	uint8_t  SM_A0_sign;
	uint8_t  SM_A1_sign;
	uint8_t  SM_A2_sign;
	uint8_t  SM_A3_sign;
	uint8_t  SM_A4_sign;
	uint8_t  SM_A5_sign;
	uint8_t  SM_A6_sign;
	uint8_t  SM_A7_sign;
	uint32_t Margin_RO_a;
	uint32_t Margin_RO_b;
	uint32_t Margin_RO_c;
	uint32_t Margin_fixed;
	uint32_t Margin_Fmax_mean;
	uint32_t Margin_plat_mean;
	uint32_t Margin_Fmax_sigma;
	uint32_t Margin_plat_sigma;
	uint32_t Margin_DC_sigma;
	uint32_t LoadLineSlop;
	uint32_t aTDClimitPerDPM[8];
	uint32_t aNoCalcVddcPerDPM[8];
	uint32_t AVFS_meanNsigma_Acontant0;
	uint32_t AVFS_meanNsigma_Acontant1;
	uint32_t AVFS_meanNsigma_Acontant2;
	uint16_t AVFS_meanNsigma_DC_tol_sigma;
	uint16_t AVFS_meanNsigma_Platform_mean;
	uint16_t AVFS_meanNsigma_Platform_sigma;
	uint32_t GB_VDROOP_TABLE_CKSOFF_a0;
	uint32_t GB_VDROOP_TABLE_CKSOFF_a1;
	uint32_t GB_VDROOP_TABLE_CKSOFF_a2;
	uint32_t GB_VDROOP_TABLE_CKSON_a0;
	uint32_t GB_VDROOP_TABLE_CKSON_a1;
	uint32_t GB_VDROOP_TABLE_CKSON_a2;
	uint32_t AVFSGB_FUSE_TABLE_CKSOFF_m1;
	uint16_t AVFSGB_FUSE_TABLE_CKSOFF_m2;
	uint32_t AVFSGB_FUSE_TABLE_CKSOFF_b;
	uint32_t AVFSGB_FUSE_TABLE_CKSON_m1;
	uint16_t AVFSGB_FUSE_TABLE_CKSON_m2;
	uint32_t AVFSGB_FUSE_TABLE_CKSON_b;
	uint16_t MaxVoltage_0_25mv;
	uint8_t  EnableGB_VDROOP_TABLE_CKSOFF;
	uint8_t  EnableGB_VDROOP_TABLE_CKSON;
	uint8_t  EnableGB_FUSE_TABLE_CKSOFF;
	uint8_t  EnableGB_FUSE_TABLE_CKSON;
	uint16_t PSM_Age_ComFactor;
	uint8_t  EnableApplyAVFS_CKS_OFF_Voltage;
	uint8_t  Reserved;
};


struct atom_sclk_fcw_range_entry_v1{
	uint32_t MaxSclkFreq;
	uint8_t  Vco_setting; // 1: 3-6GHz, 3: 2-4GHz
	uint8_t  Postdiv;     // divide by 2^n
	uint16_t ucFcw_pcc;
	uint16_t ucFcw_trans_upper;
	uint16_t ucRcw_trans_lower;
};


// SMU_InfoTable for  Polaris10/Polaris11
struct atom_smu_info_v2_1 {
	struct atom_common_table_header table_header;
	uint8_t  SclkEntryNum; // for potential future extend, indicate the number of ATOM_SCLK_FCW_RANGE_ENTRY_V1
	uint8_t  SMUVer;
	uint8_t  SharePowerSource;
	uint8_t  Reserved;
	struct atom_sclk_fcw_range_entry_v1 SclkFcwRangeEntry[8];
};


// GFX_InfoTable for Polaris10/Polaris11
struct atom_gfx_info_v2_1 {
	struct atom_common_table_header table_header;
	uint8_t  GfxIpMinVer;
	uint8_t  GfxIpMajVer;
	uint8_t  max_shader_engines;
	uint8_t  max_tile_pipes;
	uint8_t  max_cu_per_sh;
	uint8_t  max_sh_per_se;
	uint8_t  max_backends_per_se;
	uint8_t  max_texture_channel_caches;
};

/* TODO atomfirmware.h has 2.3, and 2,2. What is this?
struct atom_gfx_info_v2_3 {
	struct atom_common_table_header table_header;
	uint8_t  GfxIpMinVer;
	uint8_t  GfxIpMajVer;
	uint8_t  max_shader_engines;
	uint8_t  max_tile_pipes;
	uint8_t  max_cu_per_sh;
	uint8_t  max_sh_per_se;
	uint8_t  max_backends_per_se;
	uint8_t  max_texture_channel_caches;
	uint16_t HiLoLeakageThreshold;
	uint16_t EdcDidtLoDpm7TableOffset; // offset of DPM7 low leakage table _ATOM_EDC_DIDT_TABLE_V1
	uint16_t EdcDidtHiDpm7TableOffset; // offset of DPM7 high leakage table _ATOM_EDC_DIDT_TABLE_V1
	uint16_t Reserverd[3];
};
*/

struct atom_power_source_object {
	uint8_t  PwrSrcId;           // Power source
	uint8_t  PwrSensorType;      // GPIO, I2C or none
	uint8_t  PwrSensId;          // if GPIO detect, it is GPIO id,  if I2C detect, it is I2C id
	uint8_t  PwrSensSlaveAddr;   // Slave address if I2C detect
	uint8_t  PwrSensRegIndex;    // I2C register Index if I2C detect
	uint8_t  PwrSensRegBitMask;  // detect which bit is used if I2C detect
	uint8_t  PwrSensActiveState; // high active or low active
	uint8_t  Reserve[3];         // reserve
	uint16_t SensPwr;            // in unit of watt
};

struct atom_power_source_info {
	struct atom_common_table_header table_header;
	uint8_t  asPwrbehave[16];
	struct atom_power_source_object PwrObj[1];
};


// Define ucPwrSrcId
#define POWERSOURCE_PCIE_ID1           0x00
#define POWERSOURCE_6PIN_CONNECTOR_ID1 0x01
#define POWERSOURCE_8PIN_CONNECTOR_ID1 0x02
#define POWERSOURCE_6PIN_CONNECTOR_ID2 0x04
#define POWERSOURCE_8PIN_CONNECTOR_ID2 0x08

// define ucPwrSensorId
#define POWER_SENSOR_ALWAYS 0x00
#define POWER_SENSOR_GPIO   0x01
#define POWER_SENSOR_I2C    0x02

struct atom_clk_volt_capability {
	uint32_t VoltageIndex;  // The Voltage Index indicated by FUSE, same voltage index shared with SCLK DPM fuse table
	uint32_t MaximumSupportedCLK; // Maximum clock supported with specified voltage index, unit in 10kHz
};


struct atom_clk_volt_capability_v2 {
	uint16_t VoltageLevel;        // The real Voltage Level round up value in unit of mv,
	uint32_t MaximumSupportedCLK; // Maximum clock supported with specified voltage index, unit in 10kHz
};

struct atom_available_sclk_list {
	uint32_t SupportedSCLK; // Maximum clock supported with specified voltage index,  unit in 10kHz
	uint16_t VoltageIndex;  // The Voltage Index indicated by FUSE for specified SCLK
	uint16_t VoltageID;     // The Voltage ID indicated by FUSE for specified SCLK
};

// ATOM_INTEGRATED_SYSTEM_INFO_V6 ulSystemConfig cap definition
#define ATOM_IGP_INFO_V6_SYSTEM_CONFIG__PCIE_POWER_GATING_ENABLE 1 // refer to ulSystemConfig bit[0]

// this IntegrateSystemInfoTable is used for Liano/Ontario APU
struct atom_integrated_system_info_v6 {
	struct atom_common_table_header table_header;
	uint32_t BootUpEngineClock;
	uint32_t DentistVCOFreq;
	uint32_t BootUpUMAClock;
	struct atom_clk_volt_capability DISPCLK_Voltage[4];
	uint32_t BootUpReqDisplayVector;
	uint32_t OtherDisplayMisc;
	uint32_t GPUCapInfo;
	uint32_t SB_MMIO_Base_Addr;
	uint16_t RequestedPWMFreqInHz;
	uint8_t  HtcTmpLmt;
	uint8_t  HtcHystLmt;
	uint32_t MinEngineClock;
	uint32_t SystemConfig;
	uint32_t CPUCapInfo;
	uint16_t NBP0Voltage;
	uint16_t NBP1Voltage;
	uint16_t BootUpNBVoltage;
	uint16_t ExtDispConnInfoOffset;
	uint16_t PanelRefreshRateRange;
	enum atom_dgpu_vram_type MemoryType;
	uint8_t  UMAChannelNumber;
	uint32_t CSR_M3_ARB_CNTL_DEFAULT[10];
	uint32_t CSR_M3_ARB_CNTL_UVD[10];
	uint32_t CSR_M3_ARB_CNTL_FS3D[10];
	struct atom_available_sclk_list Avail_SCLK[5];
	uint32_t GMCRestoreResetTime;
	uint32_t MinimumNClk;
	uint32_t IdleNClk;
	uint32_t DDR_DLL_PowerUpTime;
	uint32_t DDR_PLL_PowerUpTime;
	uint16_t PCIEClkSSPercentage;
	uint16_t PCIEClkSSType;
	uint16_t LvdsSSPercentage;
	uint16_t LvdsSSpreadRateIn10Hz;
	uint16_t HDMISSPercentage;
	uint16_t HDMISSpreadRateIn10Hz;
	uint16_t DVISSPercentage;
	uint16_t DVISSpreadRateIn10Hz;
	uint32_t SclkDpmBoostMargin;
	uint32_t SclkDpmThrottleMargin;
	uint16_t SclkDpmTdpLimitPG;
	uint16_t SclkDpmTdpLimitBoost;
	uint32_t BoostEngineCLock;
	uint8_t  ulBoostVid_2bit;
	uint8_t  EnableBoost;
	uint16_t GnbTdpLimit;
	uint16_t MaxLVDSPclkFreqInSingleLink;
	uint8_t  LvdsMisc;
	uint8_t  LVDSReserved;
	uint32_t Reserved3[15];
	struct atom_external_display_connection_info ExtDispConnInfo;
};

// ulGPUCapInfo
#define INTEGRATED_SYSTEM_INFO_V6_GPUCAPINFO__TMDSHDMI_COHERENT_SINGLEPLL_MODE 0x01
#define INTEGRATED_SYSTEM_INFO_V6_GPUCAPINFO__DISABLE_AUX_HW_MODE_DETECTION    0x08

// ucLVDSMisc:
#define SYS_INFO_LVDSMISC__888_FPDI_MODE   0x01
#define SYS_INFO_LVDSMISC__DL_CH_SWAP      0x02
#define SYS_INFO_LVDSMISC__888_BPC         0x04
#define SYS_INFO_LVDSMISC__OVERRIDE_EN     0x08
#define SYS_INFO_LVDSMISC__BLON_ACTIVE_LOW 0x10
// new since Trinity
#define SYS_INFO_LVDSMISC__TRAVIS_LVDS_VOL_OVERRIDE_EN 0x20

// not used any more
#define SYS_INFO_LVDSMISC__VSYNC_ACTIVE_LOW 0x04
#define SYS_INFO_LVDSMISC__HSYNC_ACTIVE_LOW 0x08

/**********************************************************************************************************************
	struct atom_integrated_system_info_v6 Description
ulBootUpEngineClock:              VBIOS bootup Engine clock frequency, in 10kHz unit. if it is equal 0, then VBIOS use pre-defined bootup engine clock
ulDentistVCOFreq:                 Dentist VCO clock in 10kHz unit.
ulBootUpUMAClock:                 System memory boot up clock frequency in 10Khz unit.
sDISPCLK_Voltage:                 Report Display clock voltage requirement.

ulBootUpReqDisplayVector:         VBIOS boot up display IDs, following are supported devices in Liano/Ontaio projects:
	struct atom_device_crt1_support 0x0001
	struct atom_device_crt2_support 0x0010
	struct atom_device_dfp1_support 0x0008
	struct atom_device_dfp6_support 0x0040
	struct atom_device_dfp2_support 0x0080
	struct atom_device_dfp3_support 0x0200
	struct atom_device_dfp4_support 0x0400
	struct atom_device_dfp5_support 0x0800
	struct atom_device_lcd1_support 0x0002
ulOtherDisplayMisc:                 Other display related flags, not defined yet.
ulGPUCapInfo:                     bit[0]=0: TMDS/HDMI Coherent Mode use cascade PLL mode.
                                        =1: TMDS/HDMI Coherent Mode use signel PLL mode.
                                  bit[3]=0: Enable HW AUX mode detection logic
                                        =1: Disable HW AUX mode dettion logic
ulSB_MMIO_Base_Addr:              Physical Base address to SB MMIO space. Driver needs to initialize it for SMU usage.

usRequestedPWMFreqInHz:           When it's set to 0x0 by SBIOS: the LCD BackLight is not controlled by GPU(SW).
                                  Any attempt to change BL using VBIOS function or enable VariBri from PP table is not effective since ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU==0;

                                  When it's set to a non-zero frequency, the BackLight is controlled by GPU (SW) in one of two ways below:
                                  1. SW uses the GPU BL PWM output to control the BL, in chis case, this non-zero frequency determines what freq GPU should use;
	struct vbios will set up proper PWM frequency and ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU==1,as the result,
                                  Changing BL using VBIOS function is functional in both driver and non-driver present environment;
                                  and enabling VariBri under the driver environment from PP table is optional.

                                  2. SW uses other means to control BL (like DPCD),this non-zero frequency serves as a flag only indicating
                                  that BL control from GPU is expected.
	struct vbios will NOT set up PWM frequency but make ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU==1
                                  Changing BL using VBIOS function could be functional in both driver and non-driver present environment,but
                                  it's per platform
                                  and enabling VariBri under the driver environment from PP table is optional.

ucHtcTmpLmt:                      Refer to D18F3x64 bit[22:16], HtcTmpLmt.
                                  Threshold on value to enter HTC_active state.
ucHtcHystLmt:                     Refer to D18F3x64 bit[27:24], HtcHystLmt.
                                  To calculate threshold off value to exit HTC_active state, which is Threshold on vlaue minus ucHtcHystLmt.
ulMinEngineClock:                 Minimum SCLK allowed in 10kHz unit. This is calculated based on WRCK Fuse settings.
ulSystemConfig:                   Bit[0]=0: PCIE Power Gating Disabled
                                        =1: PCIE Power Gating Enabled
                                  Bit[1]=0: DDR-DLL shut-down feature disabled.
                                         1: DDR-DLL shut-down feature enabled.
                                  Bit[2]=0: DDR-PLL Power down feature disabled.
                                         1: DDR-PLL Power down feature enabled.
ulCPUCapInfo:                     TBD
usNBP0Voltage:                    VID for voltage on NB P0 State
usNBP1Voltage:                    VID for voltage on NB P1 State
usBootUpNBVoltage:                Voltage Index of GNB voltage configured by SBIOS, which is suffcient to support VBIOS DISPCLK requirement.
usExtDispConnInfoOffset:          Offset to sExtDispConnInfo inside the structure
usPanelRefreshRateRange:          Bit vector for LCD supported refresh rate range. If DRR is requestd by the platform, at least two bits need to be set
                                  to indicate a range.
                                  SUPPORTED_LCD_REFRESHRATE_30Hz          0x0004
                                  SUPPORTED_LCD_REFRESHRATE_40Hz          0x0008
                                  SUPPORTED_LCD_REFRESHRATE_50Hz          0x0010
                                  SUPPORTED_LCD_REFRESHRATE_60Hz          0x0020
ucMemoryType:                     [3:0]=1:DDR1;=2:DDR2;=3:DDR3.[7:4] is reserved.
ucUMAChannelNumber:                 System memory channel numbers.
ulCSR_M3_ARB_CNTL_DEFAULT[10]:    Arrays with values for CSR M3 arbiter for default
ulCSR_M3_ARB_CNTL_UVD[10]:        Arrays with values for CSR M3 arbiter for UVD playback.
ulCSR_M3_ARB_CNTL_FS3D[10]:       Arrays with values for CSR M3 arbiter for Full Screen 3D applications.
sAvail_SCLK[5]:                   Arrays to provide availabe list of SLCK and corresponding voltage, order from low to high
ulGMCRestoreResetTime:            GMC power restore and GMC reset time to calculate data reconnection latency. Unit in ns.
ulMinimumNClk:                    Minimum NCLK speed among all NB-Pstates to calcualte data reconnection latency. Unit in 10kHz.
ulIdleNClk:                       NCLK speed while memory runs in self-refresh state. Unit in 10kHz.
ulDDR_DLL_PowerUpTime:            DDR PHY DLL power up time. Unit in ns.
ulDDR_PLL_PowerUpTime:            DDR PHY PLL power up time. Unit in ns.
usPCIEClkSSPercentage:            PCIE Clock Spred Spectrum Percentage in unit 0.01%; 100 mean 1%.
usPCIEClkSSType:                  PCIE Clock Spred Spectrum Type. 0 for Down spread(default); 1 for Center spread.
usLvdsSSPercentage:               LVDS panel ( not include eDP ) Spread Spectrum Percentage in unit of 0.01%, =0, use VBIOS default setting.
usLvdsSSpreadRateIn10Hz:          LVDS panel ( not include eDP ) Spread Spectrum frequency in unit of 10Hz, =0, use VBIOS default setting.
usHDMISSPercentage:               HDMI Spread Spectrum Percentage in unit 0.01%; 100 mean 1%,  =0, use VBIOS default setting.
usHDMISSpreadRateIn10Hz:          HDMI Spread Spectrum frequency in unit of 10Hz,  =0, use VBIOS default setting.
usDVISSPercentage:                DVI Spread Spectrum Percentage in unit 0.01%; 100 mean 1%,  =0, use VBIOS default setting.
usDVISSpreadRateIn10Hz:           DVI Spread Spectrum frequency in unit of 10Hz,  =0, use VBIOS default setting.
usMaxLVDSPclkFreqInSingleLink:    Max pixel clock LVDS panel single link, if=0 means VBIOS use default threhold, right now it is 85Mhz
ucLVDSMisc:                       [bit0] LVDS 888bit panel mode =0: LVDS 888 panel in LDI mode, =1: LVDS 888 panel in FPDI mode
                                  [bit1] LVDS panel lower and upper link mapping =0: lower link and upper link not swap, =1: lower link and upper link are swapped
                                  [bit2] LVDS 888bit per color mode  =0: 666 bit per color =1:888 bit per color
                                  [bit3] LVDS parameter override enable  =0: ucLvdsMisc parameter are not used =1: ucLvdsMisc parameter should be used
                                  [bit4] Polarity of signal sent to digital BLON output pin. =0: not inverted(active high) =1: inverted ( active low )
**********************************************************************************************************************/

// this Table is used for Liano/Ontario APU
struct atom_fusion_system_info_v1 {
	struct atom_integrated_system_info_v6 IntegratedSysInfo;
	uint32_t PowerplayTable[128];
};


union atom_tdp_config_bits {
	uint32_t uCTDP_Enable:2; // = (uCTDP_Value > uTDP_Value? 2: (uCTDP_Value < uTDP_Value))
	uint32_t uCTDP_Value:14; // Override value in tens of milli watts
	uint32_t uTDP_Value:14;  // Original TDP value in tens of milli watts
	uint32_t uReserved:2;
};

union atom_tdp_config {
	union atom_tdp_config_bits TDP_config;
	uint32_t TDP_config_all;
};

/**********************************************************************************************************************
	struct atom_fusion_system_info_v1 Description
sIntegratedSysInfo:               refer to ATOM_INTEGRATED_SYSTEM_INFO_V6 definition.
ulPowerplayTable[128]:            This 512 bytes memory is used to save ATOM_PPLIB_POWERPLAYTABLE3, starting form ulPowerplayTable[0]
**********************************************************************************************************************/

// this IntegrateSystemInfoTable is used for Trinity APU
struct atom_integrated_system_info_v1_7 {
	struct atom_common_table_header table_header;
	uint32_t BootUpEngineClock;
	uint32_t DentistVCOFreq;
	uint32_t BootUpUMAClock;
	struct atom_clk_volt_capability DISPCLK_Voltage[4];
	uint32_t BootUpReqDisplayVector;
	uint32_t OtherDisplayMisc;
	uint32_t GPUCapInfo;
	uint32_t SB_MMIO_Base_Addr;
	uint16_t RequestedPWMFreqInHz;
	uint8_t  HtcTmpLmt;
	uint8_t  HtcHystLmt;
	uint32_t MinEngineClock;
	uint32_t SystemConfig;
	uint32_t CPUCapInfo;
	uint16_t NBP0Voltage;
	uint16_t NBP1Voltage;
	uint16_t BootUpNBVoltage;
	uint16_t ExtDispConnInfoOffset;
	uint16_t PanelRefreshRateRange;
	enum atom_dgpu_vram_type MemoryType;
	uint8_t  UMAChannelNumber;
	uint8_t  strVBIOSMsg[40];
	union atom_tdp_config asTdpConfig;
	uint32_t Reserved[19];
	struct atom_available_sclk_list Avail_SCLK[5];
	uint32_t GMCRestoreResetTime;
	uint32_t MinimumNClk;
	uint32_t IdleNClk;
	uint32_t DDR_DLL_PowerUpTime;
	uint32_t DDR_PLL_PowerUpTime;
	uint16_t PCIEClkSSPercentage;
	uint16_t PCIEClkSSType;
	uint16_t LvdsSSPercentage;
	uint16_t LvdsSSpreadRateIn10Hz;
	uint16_t HDMISSPercentage;
	uint16_t HDMISSpreadRateIn10Hz;
	uint16_t DVISSPercentage;
	uint16_t DVISSpreadRateIn10Hz;
	uint32_t SclkDpmBoostMargin;
	uint32_t SclkDpmThrottleMargin;
	uint16_t SclkDpmTdpLimitPG;
	uint16_t SclkDpmTdpLimitBoost;
	uint32_t BoostEngineCLock;
	uint8_t  ulBoostVid_2bit;
	uint8_t  EnableBoost;
	uint16_t GnbTdpLimit;
	uint16_t MaxLVDSPclkFreqInSingleLink;
	uint8_t  LvdsMisc;
	uint8_t  TravisLVDSVolAdjust;
	uint8_t  LVDSPwrOnSeqDIGONtoDE_in4Ms;
	uint8_t  LVDSPwrOnSeqDEtoVARY_BL_in4Ms;
	uint8_t  LVDSPwrOffSeqVARY_BLtoDE_in4Ms;
	uint8_t  LVDSPwrOffSeqDEtoDIGON_in4Ms;
	uint8_t  LVDSOffToOnDelay_in4Ms;
	uint8_t  LVDSPwrOnSeqVARY_BLtoBLON_in4Ms;
	uint8_t  LVDSPwrOffSeqBLONtoVARY_BL_in4Ms;
	uint8_t  MinAllowedBL_Level;
	uint32_t LCDBitDepthControlVal;
	uint32_t NbpStateMemclkFreq[4];
	uint16_t NBP2Voltage;
	uint16_t NBP3Voltage;
	uint32_t NbpStateNClkFreq[4];
	uint8_t  NBDPMEnable;
	uint8_t  Reserved2[3];
	uint8_t  DPMState0VclkFid;
	uint8_t  DPMState0DclkFid;
	uint8_t  DPMState1VclkFid;
	uint8_t  DPMState1DclkFid;
	uint8_t  DPMState2VclkFid;
	uint8_t  DPMState2DclkFid;
	uint8_t  DPMState3VclkFid;
	uint8_t  DPMState3DclkFid;
	struct atom_external_display_connection_info ExtDispConnInfo;
};

// ulOtherDisplayMisc
#define INTEGRATED_SYSTEM_INFO__GET_EDID_CALLBACK_FUNC_SUPPORT           0x01
#define INTEGRATED_SYSTEM_INFO__GET_BOOTUP_DISPLAY_CALLBACK_FUNC_SUPPORT 0x02
#define INTEGRATED_SYSTEM_INFO__GET_EXPANSION_CALLBACK_FUNC_SUPPORT      0x04
#define INTEGRATED_SYSTEM_INFO__FAST_BOOT_SUPPORT                        0x08

// ulGPUCapInfo
#define SYS_INFO_GPUCAPS__TMDSHDMI_COHERENT_SINGLEPLL_MODE 0x01
#define SYS_INFO_GPUCAPS__DP_SINGLEPLL_MODE                0x02
#define SYS_INFO_GPUCAPS__DISABLE_AUX_MODE_DETECT          0x08
#define SYS_INFO_GPUCAPS__ENABEL_DFS_BYPASS                0x10
// ulGPUCapInfo[16]=1 indicate SMC firmware is able to support GNB fast resume function, so that driver can call SMC to program most of GNB register during resuming, from ML
#define SYS_INFO_GPUCAPS__GNB_FAST_RESUME_CAPABLE 0x00010000

// ulGPUCapInfo[17]=1 indicate battery boost feature is enable, from ML
#define SYS_INFO_GPUCAPS__BATTERY_BOOST_ENABLE    0x00020000

/**********************************************************************************************************************
	struct atom_integrated_system_info_v1_7 Description
ulBootUpEngineClock:              VBIOS bootup Engine clock frequency, in 10kHz unit. if it is equal 0, then VBIOS use pre-defined bootup engine clock
ulDentistVCOFreq:                 Dentist VCO clock in 10kHz unit.
ulBootUpUMAClock:                 System memory boot up clock frequency in 10Khz unit.
sDISPCLK_Voltage:                 Report Display clock voltage requirement.

ulBootUpReqDisplayVector:         VBIOS boot up display IDs, following are supported devices in Trinity projects:
	struct atom_device_crt1_support 0x0001
	struct atom_device_dfp1_support 0x0008
	struct atom_device_dfp6_support 0x0040
	struct atom_device_dfp2_support 0x0080
	struct atom_device_dfp3_support 0x0200
	struct atom_device_dfp4_support 0x0400
	struct atom_device_dfp5_support 0x0800
	struct atom_device_lcd1_support 0x0002
ulOtherDisplayMisc:                 bit[0]=0: INT15 callback function Get LCD EDID ( ax=4e08, bl=1b ) is not supported by SBIOS.
                                        =1: INT15 callback function Get LCD EDID ( ax=4e08, bl=1b ) is supported by SBIOS.
                                  bit[1]=0: INT15 callback function Get boot display( ax=4e08, bl=01h) is not supported by SBIOS
                                        =1: INT15 callback function Get boot display( ax=4e08, bl=01h) is supported by SBIOS
                                  bit[2]=0: INT15 callback function Get panel Expansion ( ax=4e08, bl=02h) is not supported by SBIOS
                                        =1: INT15 callback function Get panel Expansion ( ax=4e08, bl=02h) is supported by SBIOS
                                  bit[3]=0: VBIOS fast boot is disable
                                        =1: VBIOS fast boot is enable. ( VBIOS skip display device detection in every set mode if LCD panel is connect and LID is open)
ulGPUCapInfo:                     bit[0]=0: TMDS/HDMI Coherent Mode use cascade PLL mode.
                                        =1: TMDS/HDMI Coherent Mode use signel PLL mode.
                                  bit[1]=0: DP mode use cascade PLL mode ( New for Trinity )
                                        =1: DP mode use single PLL mode
                                  bit[3]=0: Enable AUX HW mode detection logic
                                        =1: Disable AUX HW mode detection logic

ulSB_MMIO_Base_Addr:              Physical Base address to SB MMIO space. Driver needs to initialize it for SMU usage.

usRequestedPWMFreqInHz:           When it's set to 0x0 by SBIOS: the LCD BackLight is not controlled by GPU(SW).
                                  Any attempt to change BL using VBIOS function or enable VariBri from PP table is not effective since ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU==0;

                                  When it's set to a non-zero frequency, the BackLight is controlled by GPU (SW) in one of two ways below:
                                  1. SW uses the GPU BL PWM output to control the BL, in chis case, this non-zero frequency determines what freq GPU should use;
	struct vbios will set up proper PWM frequency and ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU==1,as the result,
                                  Changing BL using VBIOS function is functional in both driver and non-driver present environment;
                                  and enabling VariBri under the driver environment from PP table is optional.

                                  2. SW uses other means to control BL (like DPCD),this non-zero frequency serves as a flag only indicating
                                  that BL control from GPU is expected.
	struct vbios will NOT set up PWM frequency but make ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU==1
                                  Changing BL using VBIOS function could be functional in both driver and non-driver present environment,but
                                  it's per platform
                                  and enabling VariBri under the driver environment from PP table is optional.

ucHtcTmpLmt:                      Refer to D18F3x64 bit[22:16], HtcTmpLmt.
                                  Threshold on value to enter HTC_active state.
ucHtcHystLmt:                     Refer to D18F3x64 bit[27:24], HtcHystLmt.
                                  To calculate threshold off value to exit HTC_active state, which is Threshold on vlaue minus ucHtcHystLmt.
ulMinEngineClock:                 Minimum SCLK allowed in 10kHz unit. This is calculated based on WRCK Fuse settings.
ulSystemConfig:                   Bit[0]=0: PCIE Power Gating Disabled
                                        =1: PCIE Power Gating Enabled
                                  Bit[1]=0: DDR-DLL shut-down feature disabled.
                                         1: DDR-DLL shut-down feature enabled.
                                  Bit[2]=0: DDR-PLL Power down feature disabled.
                                         1: DDR-PLL Power down feature enabled.
ulCPUCapInfo:                     TBD
usNBP0Voltage:                    VID for voltage on NB P0 State
usNBP1Voltage:                    VID for voltage on NB P1 State
usNBP2Voltage:                    VID for voltage on NB P2 State
usNBP3Voltage:                    VID for voltage on NB P3 State
usBootUpNBVoltage:                Voltage Index of GNB voltage configured by SBIOS, which is suffcient to support VBIOS DISPCLK requirement.
usExtDispConnInfoOffset:          Offset to sExtDispConnInfo inside the structure
usPanelRefreshRateRange:          Bit vector for LCD supported refresh rate range. If DRR is requestd by the platform, at least two bits need to be set
                                  to indicate a range.
                                  SUPPORTED_LCD_REFRESHRATE_30Hz          0x0004
                                  SUPPORTED_LCD_REFRESHRATE_40Hz          0x0008
                                  SUPPORTED_LCD_REFRESHRATE_50Hz          0x0010
                                  SUPPORTED_LCD_REFRESHRATE_60Hz          0x0020
ucMemoryType:                     [3:0]=1:DDR1;=2:DDR2;=3:DDR3.[7:4] is reserved.
ucUMAChannelNumber:                 System memory channel numbers.
ulCSR_M3_ARB_CNTL_DEFAULT[10]:    Arrays with values for CSR M3 arbiter for default
ulCSR_M3_ARB_CNTL_UVD[10]:        Arrays with values for CSR M3 arbiter for UVD playback.
ulCSR_M3_ARB_CNTL_FS3D[10]:       Arrays with values for CSR M3 arbiter for Full Screen 3D applications.
sAvail_SCLK[5]:                   Arrays to provide availabe list of SLCK and corresponding voltage, order from low to high
ulGMCRestoreResetTime:            GMC power restore and GMC reset time to calculate data reconnection latency. Unit in ns.
ulMinimumNClk:                    Minimum NCLK speed among all NB-Pstates to calcualte data reconnection latency. Unit in 10kHz.
ulIdleNClk:                       NCLK speed while memory runs in self-refresh state. Unit in 10kHz.
ulDDR_DLL_PowerUpTime:            DDR PHY DLL power up time. Unit in ns.
ulDDR_PLL_PowerUpTime:            DDR PHY PLL power up time. Unit in ns.
usPCIEClkSSPercentage:            PCIE Clock Spread Spectrum Percentage in unit 0.01%; 100 mean 1%.
usPCIEClkSSType:                  PCIE Clock Spread Spectrum Type. 0 for Down spread(default); 1 for Center spread.
usLvdsSSPercentage:               LVDS panel ( not include eDP ) Spread Spectrum Percentage in unit of 0.01%, =0, use VBIOS default setting.
usLvdsSSpreadRateIn10Hz:          LVDS panel ( not include eDP ) Spread Spectrum frequency in unit of 10Hz, =0, use VBIOS default setting.
usHDMISSPercentage:               HDMI Spread Spectrum Percentage in unit 0.01%; 100 mean 1%,  =0, use VBIOS default setting.
usHDMISSpreadRateIn10Hz:          HDMI Spread Spectrum frequency in unit of 10Hz,  =0, use VBIOS default setting.
usDVISSPercentage:                DVI Spread Spectrum Percentage in unit 0.01%; 100 mean 1%,  =0, use VBIOS default setting.
usDVISSpreadRateIn10Hz:           DVI Spread Spectrum frequency in unit of 10Hz,  =0, use VBIOS default setting.
usMaxLVDSPclkFreqInSingleLink:    Max pixel clock LVDS panel single link, if=0 means VBIOS use default threhold, right now it is 85Mhz
ucLVDSMisc:                       [bit0] LVDS 888bit panel mode =0: LVDS 888 panel in LDI mode, =1: LVDS 888 panel in FPDI mode
                                  [bit1] LVDS panel lower and upper link mapping =0: lower link and upper link not swap, =1: lower link and upper link are swapped
                                  [bit2] LVDS 888bit per color mode  =0: 666 bit per color =1:888 bit per color
                                  [bit3] LVDS parameter override enable  =0: ucLvdsMisc parameter are not used =1: ucLvdsMisc parameter should be used
                                  [bit4] Polarity of signal sent to digital BLON output pin. =0: not inverted(active high) =1: inverted ( active low )
                                  [bit5] Travid LVDS output voltage override enable, when =1, use ucTravisLVDSVolAdjust value to overwrite Traivs register LVDS_CTRL_4
ucTravisLVDSVolAdjust             When ucLVDSMisc[5]=1,it means platform SBIOS want to overwrite TravisLVDSVoltage. Then VBIOS will use ucTravisLVDSVolAdjust
                                  value to program Travis register LVDS_CTRL_4
ucLVDSPwrOnSeqDIGONtoDE_in4Ms:    LVDS power up sequence time in unit of 4ms, time delay from DIGON signal active to data enable signal active( DE ).
                                  =0 mean use VBIOS default which is 8 ( 32ms ). The LVDS power up sequence is as following: DIGON->DE->VARY_BL->BLON.
                                  This parameter is used by VBIOS only. VBIOS will patch LVDS_InfoTable.
ucLVDSPwrOnDEtoVARY_BL_in4Ms:     LVDS power up sequence time in unit of 4ms., time delay from DE( data enable ) active to Vary Brightness enable signal active( VARY_BL ).
                                  =0 mean use VBIOS default which is 90 ( 360ms ). The LVDS power up sequence is as following: DIGON->DE->VARY_BL->BLON.
                                  This parameter is used by VBIOS only. VBIOS will patch LVDS_InfoTable.

ucLVDSPwrOffVARY_BLtoDE_in4Ms:    LVDS power down sequence time in unit of 4ms, time delay from data enable ( DE ) signal off to LCDVCC (DIGON) off.
                                  =0 mean use VBIOS default delay which is 8 ( 32ms ). The LVDS power down sequence is as following: BLON->VARY_BL->DE->DIGON
                                  This parameter is used by VBIOS only. VBIOS will patch LVDS_InfoTable.

ucLVDSPwrOffDEtoDIGON_in4Ms:      LVDS power down sequence time in unit of 4ms, time delay from vary brightness enable signal( VARY_BL) off to data enable ( DE ) signal off.
                                  =0 mean use VBIOS default which is 90 ( 360ms ). The LVDS power down sequence is as following: BLON->VARY_BL->DE->DIGON
                                  This parameter is used by VBIOS only. VBIOS will patch LVDS_InfoTable.

ucLVDSOffToOnDelay_in4Ms:         LVDS power down sequence time in unit of 4ms. Time delay from DIGON signal off to DIGON signal active.
                                  =0 means to use VBIOS default delay which is 125 ( 500ms ).
                                  This parameter is used by VBIOS only. VBIOS will patch LVDS_InfoTable.

ucLVDSPwrOnSeqVARY_BLtoBLON_in4Ms:
	struct lvds power up sequence time in unit of 4ms. Time delay from VARY_BL signal on to DLON signal active.
                                  =0 means to use VBIOS default delay which is 0 ( 0ms ).
                                  This parameter is used by VBIOS only. VBIOS will patch LVDS_InfoTable.

ucLVDSPwrOffSeqBLONtoVARY_BL_in4Ms:
	struct lvds power down sequence time in unit of 4ms. Time delay from BLON signal off to VARY_BL signal off.
                                  =0 means to use VBIOS default delay which is 0 ( 0ms ).
                                  This parameter is used by VBIOS only. VBIOS will patch LVDS_InfoTable.

ucMinAllowedBL_Level:             Lowest LCD backlight PWM level. This is customer platform specific parameters. By default it is 0.

ulNbpStateMemclkFreq[4]:          system memory clock frequncey in unit of 10Khz in different NB pstate.

**********************************************************************************************************************/

// this IntegrateSystemInfoTable is used for Kaveri & Kabini APU
struct atom_integrated_system_info_v1_8 {
	struct atom_common_table_header table_header;
	uint32_t BootUpEngineClock;
	uint32_t DentistVCOFreq;
	uint32_t BootUpUMAClock;
	struct atom_clk_volt_capability DISPCLK_Voltage[4];
	uint32_t BootUpReqDisplayVector;
	uint32_t VBIOSMisc;
	uint32_t GPUCapInfo;
	uint32_t DISP_CLK2Freq;
	uint16_t RequestedPWMFreqInHz;
	uint8_t  HtcTmpLmt;
	uint8_t  HtcHystLmt;
	uint32_t Reserved2;
	uint32_t SystemConfig;
	uint32_t CPUCapInfo;
	uint32_t Reserved3;
	uint16_t GPUReservedSysMemSize;
	uint16_t ExtDispConnInfoOffset;
	uint16_t PanelRefreshRateRange;
	enum atom_dgpu_vram_type MemoryType;
	uint8_t  UMAChannelNumber;
	uint8_t  strVBIOSMsg[40];
	union atom_tdp_config asTdpConfig;
	uint32_t Reserved[19];
	struct atom_available_sclk_list Avail_SCLK[5];
	uint32_t GMCRestoreResetTime;
	uint32_t Reserved4;
	uint32_t IdleNClk;
	uint32_t DDR_DLL_PowerUpTime;
	uint32_t DDR_PLL_PowerUpTime;
	uint16_t PCIEClkSSPercentage;
	uint16_t PCIEClkSSType;
	uint16_t LvdsSSPercentage;
	uint16_t LvdsSSpreadRateIn10Hz;
	uint16_t HDMISSPercentage;
	uint16_t HDMISSpreadRateIn10Hz;
	uint16_t DVISSPercentage;
	uint16_t DVISSpreadRateIn10Hz;
	uint32_t GPUReservedSysMemBaseAddrLo;
	uint32_t GPUReservedSysMemBaseAddrHi;
	struct atom_clk_volt_capability fifth_DISPCLK_Voltage;
	uint32_t Reserved5;
	uint16_t MaxLVDSPclkFreqInSingleLink;
	uint8_t  LvdsMisc;
	uint8_t  TravisLVDSVolAdjust;
	uint8_t  LVDSPwrOnSeqDIGONtoDE_in4Ms;
	uint8_t  LVDSPwrOnSeqDEtoVARY_BL_in4Ms;
	uint8_t  LVDSPwrOffSeqVARY_BLtoDE_in4Ms;
	uint8_t  LVDSPwrOffSeqDEtoDIGON_in4Ms;
	uint8_t  LVDSOffToOnDelay_in4Ms;
	uint8_t  LVDSPwrOnSeqVARY_BLtoBLON_in4Ms;
	uint8_t  LVDSPwrOffSeqBLONtoVARY_BL_in4Ms;
	uint8_t  MinAllowedBL_Level;
	uint32_t LCDBitDepthControlVal;
	uint32_t NbpStateMemclkFreq[4];
	uint32_t PSPVersion;
	uint32_t NbpStateNClkFreq[4];
	uint16_t NBPStateVoltage[4];
	uint16_t BootUpNBVoltage;
	uint16_t Reserved6;
	struct atom_external_display_connection_info ExtDispConnInfo;
};

/**********************************************************************************************************************
	struct atom_integrated_system_info_v1_8 Description
ulBootUpEngineClock:              VBIOS bootup Engine clock frequency, in 10kHz unit. if it is equal 0, then VBIOS use pre-defined bootup engine clock
ulDentistVCOFreq:                 Dentist VCO clock in 10kHz unit.
ulBootUpUMAClock:                 System memory boot up clock frequency in 10Khz unit.
sDISPCLK_Voltage:                 Report Display clock frequency requirement on GNB voltage(up to 4 voltage levels).

ulBootUpReqDisplayVector:         VBIOS boot up display IDs, following are supported devices in Trinity projects:
	struct atom_device_crt1_support 0x0001
	struct atom_device_dfp1_support 0x0008
	struct atom_device_dfp6_support 0x0040
	struct atom_device_dfp2_support 0x0080
	struct atom_device_dfp3_support 0x0200
	struct atom_device_dfp4_support 0x0400
	struct atom_device_dfp5_support 0x0800
	struct atom_device_lcd1_support 0x0002

ulVBIOSMisc:                       Miscellenous flags for VBIOS requirement and interface
                                  bit[0]=0: INT15 callback function Get LCD EDID ( ax=4e08, bl=1b ) is not supported by SBIOS.
                                        =1: INT15 callback function Get LCD EDID ( ax=4e08, bl=1b ) is supported by SBIOS.
                                  bit[1]=0: INT15 callback function Get boot display( ax=4e08, bl=01h) is not supported by SBIOS
                                        =1: INT15 callback function Get boot display( ax=4e08, bl=01h) is supported by SBIOS
                                  bit[2]=0: INT15 callback function Get panel Expansion ( ax=4e08, bl=02h) is not supported by SBIOS
                                        =1: INT15 callback function Get panel Expansion ( ax=4e08, bl=02h) is supported by SBIOS
                                  bit[3]=0: VBIOS fast boot is disable
                                        =1: VBIOS fast boot is enable. ( VBIOS skip display device detection in every set mode if LCD panel is connect and LID is open)

ulGPUCapInfo:                     bit[0~2]= Reserved
                                  bit[3]=0: Enable AUX HW mode detection logic
                                        =1: Disable AUX HW mode detection logic
                                  bit[4]=0: Disable DFS bypass feature
                                        =1: Enable DFS bypass feature

usRequestedPWMFreqInHz:           When it's set to 0x0 by SBIOS: the LCD BackLight is not controlled by GPU(SW).
                                  Any attempt to change BL using VBIOS function or enable VariBri from PP table is not effective since ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU==0;

                                  When it's set to a non-zero frequency, the BackLight is controlled by GPU (SW) in one of two ways below:
                                  1. SW uses the GPU BL PWM output to control the BL, in chis case, this non-zero frequency determines what freq GPU should use;
	struct vbios will set up proper PWM frequency and ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU==1,as the result,
                                  Changing BL using VBIOS function is functional in both driver and non-driver present environment;
                                  and enabling VariBri under the driver environment from PP table is optional.

                                  2. SW uses other means to control BL (like DPCD),this non-zero frequency serves as a flag only indicating
                                  that BL control from GPU is expected.
	struct vbios will NOT set up PWM frequency but make ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU==1
                                  Changing BL using VBIOS function could be functional in both driver and non-driver present environment,but
                                  it's per platform
                                  and enabling VariBri under the driver environment from PP table is optional.

ucHtcTmpLmt:                      Refer to D18F3x64 bit[22:16], HtcTmpLmt. Threshold on value to enter HTC_active state.
ucHtcHystLmt:                     Refer to D18F3x64 bit[27:24], HtcHystLmt.
                                  To calculate threshold off value to exit HTC_active state, which is Threshold on vlaue minus ucHtcHystLmt.

ulSystemConfig:                   Bit[0]=0: PCIE Power Gating Disabled
                                        =1: PCIE Power Gating Enabled
                                  Bit[1]=0: DDR-DLL shut-down feature disabled.
                                         1: DDR-DLL shut-down feature enabled.
                                  Bit[2]=0: DDR-PLL Power down feature disabled.
                                         1: DDR-PLL Power down feature enabled.
                                  Bit[3]=0: GNB DPM is disabled
                                        =1: GNB DPM is enabled
ulCPUCapInfo:                     TBD

usExtDispConnInfoOffset:          Offset to sExtDispConnInfo inside the structure
usPanelRefreshRateRange:          Bit vector for LCD supported refresh rate range. If DRR is requestd by the platform, at least two bits need to be set
                                  to indicate a range.
                                  SUPPORTED_LCD_REFRESHRATE_30Hz          0x0004
                                  SUPPORTED_LCD_REFRESHRATE_40Hz          0x0008
                                  SUPPORTED_LCD_REFRESHRATE_50Hz          0x0010
                                  SUPPORTED_LCD_REFRESHRATE_60Hz          0x0020

ucMemoryType:                     [3:0]=1:DDR1;=2:DDR2;=3:DDR3;=5:GDDR5; [7:4] is reserved.
ucUMAChannelNumber:                 System memory channel numbers.

strVBIOSMsg[40]:                  VBIOS boot up customized message string

sAvail_SCLK[5]:                   Arrays to provide availabe list of SLCK and corresponding voltage, order from low to high

ulGMCRestoreResetTime:            GMC power restore and GMC reset time to calculate data reconnection latency. Unit in ns.
ulIdleNClk:                       NCLK speed while memory runs in self-refresh state, used to calculate self-refresh latency. Unit in 10kHz.
ulDDR_DLL_PowerUpTime:            DDR PHY DLL power up time. Unit in ns.
ulDDR_PLL_PowerUpTime:            DDR PHY PLL power up time. Unit in ns.

usPCIEClkSSPercentage:            PCIE Clock Spread Spectrum Percentage in unit 0.01%; 100 mean 1%.
usPCIEClkSSType:                  PCIE Clock Spread Spectrum Type. 0 for Down spread(default); 1 for Center spread.
usLvdsSSPercentage:               LVDS panel ( not include eDP ) Spread Spectrum Percentage in unit of 0.01%, =0, use VBIOS default setting.
usLvdsSSpreadRateIn10Hz:          LVDS panel ( not include eDP ) Spread Spectrum frequency in unit of 10Hz, =0, use VBIOS default setting.
usHDMISSPercentage:               HDMI Spread Spectrum Percentage in unit 0.01%; 100 mean 1%,  =0, use VBIOS default setting.
usHDMISSpreadRateIn10Hz:          HDMI Spread Spectrum frequency in unit of 10Hz,  =0, use VBIOS default setting.
usDVISSPercentage:                DVI Spread Spectrum Percentage in unit 0.01%; 100 mean 1%,  =0, use VBIOS default setting.
usDVISSpreadRateIn10Hz:           DVI Spread Spectrum frequency in unit of 10Hz,  =0, use VBIOS default setting.

usGPUReservedSysMemSize:          Reserved system memory size for ACP engine in APU GNB, units in MB. 0/2/4MB based on CMOS options, current default could be 0MB. KV only, not on KB.
ulGPUReservedSysMemBaseAddrLo:    Low 32 bits base address to the reserved system memory.
ulGPUReservedSysMemBaseAddrHi:    High 32 bits base address to the reserved system memory.

usMaxLVDSPclkFreqInSingleLink:    Max pixel clock LVDS panel single link, if=0 means VBIOS use default threhold, right now it is 85Mhz
ucLVDSMisc:                       [bit0] LVDS 888bit panel mode =0: LVDS 888 panel in LDI mode, =1: LVDS 888 panel in FPDI mode
                                  [bit1] LVDS panel lower and upper link mapping =0: lower link and upper link not swap, =1: lower link and upper link are swapped
                                  [bit2] LVDS 888bit per color mode  =0: 666 bit per color =1:888 bit per color
                                  [bit3] LVDS parameter override enable  =0: ucLvdsMisc parameter are not used =1: ucLvdsMisc parameter should be used
                                  [bit4] Polarity of signal sent to digital BLON output pin. =0: not inverted(active high) =1: inverted ( active low )
                                  [bit5] Travid LVDS output voltage override enable, when =1, use ucTravisLVDSVolAdjust value to overwrite Traivs register LVDS_CTRL_4
ucTravisLVDSVolAdjust             When ucLVDSMisc[5]=1,it means platform SBIOS want to overwrite TravisLVDSVoltage. Then VBIOS will use ucTravisLVDSVolAdjust
                                  value to program Travis register LVDS_CTRL_4
ucLVDSPwrOnSeqDIGONtoDE_in4Ms:
	struct lvds power up sequence time in unit of 4ms, time delay from DIGON signal active to data enable signal active( DE ).
                                  =0 mean use VBIOS default which is 8 ( 32ms ). The LVDS power up sequence is as following: DIGON->DE->VARY_BL->BLON.
                                  This parameter is used by VBIOS only. VBIOS will patch LVDS_InfoTable.
ucLVDSPwrOnDEtoVARY_BL_in4Ms:
	struct lvds power up sequence time in unit of 4ms., time delay from DE( data enable ) active to Vary Brightness enable signal active( VARY_BL ).
                                  =0 mean use VBIOS default which is 90 ( 360ms ). The LVDS power up sequence is as following: DIGON->DE->VARY_BL->BLON.
                                  This parameter is used by VBIOS only. VBIOS will patch LVDS_InfoTable.
ucLVDSPwrOffVARY_BLtoDE_in4Ms:
	struct lvds power down sequence time in unit of 4ms, time delay from data enable ( DE ) signal off to LCDVCC (DIGON) off.
                                  =0 mean use VBIOS default delay which is 8 ( 32ms ). The LVDS power down sequence is as following: BLON->VARY_BL->DE->DIGON
                                  This parameter is used by VBIOS only. VBIOS will patch LVDS_InfoTable.
ucLVDSPwrOffDEtoDIGON_in4Ms:
	struct lvds power down sequence time in unit of 4ms, time delay from vary brightness enable signal( VARY_BL) off to data enable ( DE ) signal off.
                                  =0 mean use VBIOS default which is 90 ( 360ms ). The LVDS power down sequence is as following: BLON->VARY_BL->DE->DIGON
                                  This parameter is used by VBIOS only. VBIOS will patch LVDS_InfoTable.
ucLVDSOffToOnDelay_in4Ms:
	struct lvds power down sequence time in unit of 4ms. Time delay from DIGON signal off to DIGON signal active.
                                  =0 means to use VBIOS default delay which is 125 ( 500ms ).
                                  This parameter is used by VBIOS only. VBIOS will patch LVDS_InfoTable.
ucLVDSPwrOnSeqVARY_BLtoBLON_in4Ms:
	struct lvds power up sequence time in unit of 4ms. Time delay from VARY_BL signal on to DLON signal active.
                                  =0 means to use VBIOS default delay which is 0 ( 0ms ).
                                  This parameter is used by VBIOS only. VBIOS will patch LVDS_InfoTable.

ucLVDSPwrOffSeqBLONtoVARY_BL_in4Ms:
	struct lvds power down sequence time in unit of 4ms. Time delay from BLON signal off to VARY_BL signal off.
                                  =0 means to use VBIOS default delay which is 0 ( 0ms ).
                                  This parameter is used by VBIOS only. VBIOS will patch LVDS_InfoTable.
ucMinAllowedBL_Level:             Lowest LCD backlight PWM level. This is customer platform specific parameters. By default it is 0.

ulLCDBitDepthControlVal:          GPU display control encoder bit dither control setting, used to program register mmFMT_BIT_DEPTH_CONTROL

ulNbpStateMemclkFreq[4]:          system memory clock frequncey in unit of 10Khz in different NB P-State(P0, P1, P2 & P3).
ulNbpStateNClkFreq[4]:            NB P-State NClk frequency in different NB P-State
usNBPStateVoltage[4]:             NB P-State (P0/P1 & P2/P3) voltage; NBP3 refers to lowes voltage
usBootUpNBVoltage:                NB P-State voltage during boot up before driver loaded
sExtDispConnInfo:                 Display connector information table provided to VBIOS

**********************************************************************************************************************/
/* duplicate
struct atom_i2c_reg_info {
	uint8_t  I2cRegIndex;
	uint8_t  I2cRegVal;
};
*/

// this IntegrateSystemInfoTable is used for Carrizo
struct atom_integrated_system_info_v1_9 {
	struct atom_common_table_header table_header;
	uint32_t BootUpEngineClock;
	uint32_t DentistVCOFreq;
	uint32_t BootUpUMAClock;
	struct atom_clk_volt_capability DISPCLK_Voltage[4]; // no longer used, keep it as is to avoid driver compiling error
	uint32_t BootUpReqDisplayVector;
	uint32_t VBIOSMisc;
	uint32_t GPUCapInfo;
	uint32_t DISP_CLK2Freq;
	uint16_t RequestedPWMFreqInHz;
	uint8_t  HtcTmpLmt;
	uint8_t  HtcHystLmt;
	uint32_t Reserved2;
	uint32_t SystemConfig;
	uint32_t CPUCapInfo;
	uint32_t Reserved3;
	uint16_t GPUReservedSysMemSize;
	uint16_t ExtDispConnInfoOffset;
	uint16_t PanelRefreshRateRange;
	enum atom_dgpu_vram_type MemoryType;
	uint8_t  UMAChannelNumber;
	uint8_t  strVBIOSMsg[40];
	union atom_tdp_config asTdpConfig;
	uint8_t  ExtHDMIReDrvSlvAddr;
	uint8_t  ExtHDMIReDrvRegNum;
	struct atom_i2c_reg_info ExtHDMIRegSetting[9];
	uint32_t Reserved[2];
	struct atom_clk_volt_capability_v2 DispClkVoltageMapping[8];
	struct atom_available_sclk_list Avail_SCLK[5]; // no longer used, keep it as is to avoid driver compiling error
	uint32_t GMCRestoreResetTime;
	uint32_t Reserved4;
	uint32_t IdleNClk;
	uint32_t DDR_DLL_PowerUpTime;
	uint32_t DDR_PLL_PowerUpTime;
	uint16_t PCIEClkSSPercentage;
	uint16_t PCIEClkSSType;
	uint16_t LvdsSSPercentage;
	uint16_t LvdsSSpreadRateIn10Hz;
	uint16_t HDMISSPercentage;
	uint16_t HDMISSpreadRateIn10Hz;
	uint16_t DVISSPercentage;
	uint16_t DVISSpreadRateIn10Hz;
	uint32_t GPUReservedSysMemBaseAddrLo;
	uint32_t GPUReservedSysMemBaseAddrHi;
	uint32_t Reserved5[3];
	uint16_t MaxLVDSPclkFreqInSingleLink;
	uint8_t  LvdsMisc;
	uint8_t  TravisLVDSVolAdjust;
	uint8_t  LVDSPwrOnSeqDIGONtoDE_in4Ms;
	uint8_t  LVDSPwrOnSeqDEtoVARY_BL_in4Ms;
	uint8_t  LVDSPwrOffSeqVARY_BLtoDE_in4Ms;
	uint8_t  LVDSPwrOffSeqDEtoDIGON_in4Ms;
	uint8_t  LVDSOffToOnDelay_in4Ms;
	uint8_t  LVDSPwrOnSeqVARY_BLtoBLON_in4Ms;
	uint8_t  LVDSPwrOffSeqBLONtoVARY_BL_in4Ms;
	uint8_t  MinAllowedBL_Level;
	uint32_t LCDBitDepthControlVal;
	uint32_t NbpStateMemclkFreq[4]; // only 2 level is changed.
	uint32_t PSPVersion;
	uint32_t NbpStateNClkFreq[4];
	uint16_t NBPStateVoltage[4];
	uint16_t BootUpNBVoltage;
	uint8_t  EDPv1_4VSMode;
	uint8_t  Reserved6;
	struct atom_external_display_connection_info ExtDispConnInfo;
};


// definition for ucEDPv1_4VSMode
#define EDP_VS_LEGACY_MODE        0
#define EDP_VS_LOW_VDIFF_MODE     1
#define EDP_VS_HIGH_VDIFF_MODE    2
#define EDP_VS_STRETCH_MODE       3
#define EDP_VS_SINGLE_VDIFF_MODE  4
#define EDP_VS_VARIABLE_PREM_MODE 5


// ulGPUCapInfo
#define SYS_INFO_V1_9_GPUCAPSINFO_DISABLE_AUX_MODE_DETECT 0x08
#define SYS_INFO_V1_9_GPUCAPSINFO_ENABEL_DFS_BYPASS       0x10
// ulGPUCapInfo[16]=1 indicate SMC firmware is able to support GNB fast resume function, so that driver can call SMC to program most of GNB register during resuming, from ML
#define SYS_INFO_V1_9_GPUCAPSINFO_GNB_FAST_RESUME_CAPABLE 0x00010000
// ulGPUCapInfo[18]=1 indicate the IOMMU is not available
#define SYS_INFO_V1_9_GPUCAPINFO_IOMMU_DISABLE            0x00040000
// ulGPUCapInfo[19]=1 indicate the MARC Aperture is opened.
#define SYS_INFO_V1_9_GPUCAPINFO_MARC_APERTURE_ENABLE     0x00080000


struct dphy_timing_para {
	uint8_t  ProfileID; // SENSOR_PROFILES
	uint32_t ucPara;
};

struct dphy_elec_para {
	uint16_t Para[3];
};

struct camera_module_info {
	uint8_t  ID; // 0: Rear, 1: Front right of user, 2: Front left of user
	uint8_t  strModuleName[8];
	struct dphy_timing_para TimingPara[6]; // Exact number is under estimation and confirmation from sensor vendor
};

struct flashlight_info {
	uint8_t  ID; // 0: Rear, 1: Front
	uint8_t  strName[8];
};

struct camera_data {
	uint32_t VersionCode;
	struct camera_module_info CameraInfo[3]; // Assuming 3 camera sensors max
	struct flashlight_info FlashInfo; // Assuming 1 flashlight max
	struct dphy_elec_para DphyElecPara;
	uint32_t CrcVal; // CRC
};

struct atom_integrated_system_info_v1_10 {
	struct atom_common_table_header table_header;
	uint32_t BootUpEngineClock;
	uint32_t DentistVCOFreq;
	uint32_t BootUpUMAClock;
	uint32_t Reserved0[8];
	uint32_t BootUpReqDisplayVector;
	uint32_t VBIOSMisc;
	uint32_t GPUCapInfo;
	uint32_t Reserved1;
	uint16_t RequestedPWMFreqInHz;
	uint8_t  HtcTmpLmt;
	uint8_t  HtcHystLmt;
	uint32_t Reserved2;
	uint32_t SystemConfig;
	uint32_t CPUCapInfo;
	uint32_t Reserved3;
	uint16_t GPUReservedSysMemSize;
	uint16_t ExtDispConnInfoOffset;
	uint16_t PanelRefreshRateRange;
	enum atom_dgpu_vram_type MemoryType;
	uint8_t  UMAChannelNumber;
	uint32_t MsgReserved[10];
	union atom_tdp_config asTdpConfig;
	uint32_t Reserved[7];
	struct atom_clk_volt_capability_v2 DispClkVoltageMapping[8];
	uint32_t Reserved6[10];
	uint32_t GMCRestoreResetTime;
	uint32_t Reserved4;
	uint32_t IdleNClk;
	uint32_t DDR_DLL_PowerUpTime;
	uint32_t DDR_PLL_PowerUpTime;
	uint16_t PCIEClkSSPercentage;
	uint16_t PCIEClkSSType;
	uint16_t LvdsSSPercentage;
	uint16_t LvdsSSpreadRateIn10Hz;
	uint16_t HDMISSPercentage;
	uint16_t HDMISSpreadRateIn10Hz;
	uint16_t DVISSPercentage;
	uint16_t DVISSpreadRateIn10Hz;
	uint32_t GPUReservedSysMemBaseAddrLo;
	uint32_t GPUReservedSysMemBaseAddrHi;
	uint32_t Reserved5[3];
	uint16_t MaxLVDSPclkFreqInSingleLink;
	uint8_t  LvdsMisc;
	uint8_t  TravisLVDSVolAdjust;
	uint8_t  LVDSPwrOnSeqDIGONtoDE_in4Ms;
	uint8_t  LVDSPwrOnSeqDEtoVARY_BL_in4Ms;
	uint8_t  LVDSPwrOffSeqVARY_BLtoDE_in4Ms;
	uint8_t  LVDSPwrOffSeqDEtoDIGON_in4Ms;
	uint8_t  LVDSOffToOnDelay_in4Ms;
	uint8_t  LVDSPwrOnSeqVARY_BLtoBLON_in4Ms;
	uint8_t  LVDSPwrOffSeqBLONtoVARY_BL_in4Ms;
	uint8_t  MinAllowedBL_Level;
	uint32_t LCDBitDepthControlVal;
	uint32_t NbpStateMemclkFreq[2];
	uint32_t Reserved7[2];
	uint32_t PSPVersion;
	uint32_t NbpStateNClkFreq[4];
	uint16_t NBPStateVoltage[4];
	uint16_t BootUpNBVoltage;
	uint8_t  EDPv1_4VSMode;
	uint8_t  Reserved9;
	struct atom_external_display_connection_info ExtDispConnInfo;
	struct camera_data CameraInfo;
	uint32_t Reserved8[29];
};


// this Table is used for Kaveri/Kabini APU
struct atom_fusion_system_info_v2 {
	struct atom_integrated_system_info_v1_8 IntegratedSysInfo; // refer to ATOM_INTEGRATED_SYSTEM_INFO_V1_8 definition
	uint32_t PowerplayTable[128]; // Update comments here to link new powerplay table definition structure
};


struct atom_fusion_system_info_v3 {
	struct atom_integrated_system_info_v1_10 IntegratedSysInfo; // refer to ATOM_INTEGRATED_SYSTEM_INFO_V1_8 definition
	uint32_t PowerplayTable[192]; // Reserve 768 bytes space for PowerPlayInfoTable
};

#define FUSION_V3_OFFSET_FROM_TOP_OF_FB 0x800

/******************************************************************************/
// This portion is only used when ext thermal chip or engine/memory clock SS chip is populated on a design
// Memory SS Info Table
// Define Memory Clock SS chip ID
#define ICS91719  1
#define ICS91720  2

// Define one structure to inform SW a "block of data" writing to external SS chip via I2C protocol
struct atom_i2c_data_record {
	uint8_t  NunberOfBytes; // Indicates how many bytes SW needs to write to the external ASIC for one block, besides to "Start" and "Stop"
	uint8_t  I2CData[]; // I2C data in bytes, should be less than 16 bytes usually
};


// Define one structure to inform SW how many blocks of data writing to external SS chip via I2C protocol, in addition to other information
struct atom_i2c_device_setup_info {
	union atom_i2c_id_config I2cId; // I2C line and HW/SW assisted cap.
	uint8_t  SSChipID; // SS chip being used
	uint8_t  SSChipSlaveAddr; // Slave Address to set up this SS chip
	uint8_t  NumOfI2CDataRecords; // number of data block
	struct atom_i2c_data_record I2CData[];
};

/******************************************************************************/
struct atom_asic_mvdd_info {
	struct atom_common_table_header table_header;
	struct atom_i2c_device_setup_info I2CSetup[];
};

/******************************************************************************/
#define ATOM_MCLK_SS_INFO         ATOM_ASIC_MVDD_INFO

/******************************************************************************/
/******************************************************************************/

struct atom_asic_ss_assignment {
	uint32_t TargetClockRange;   // Clock Out frequence (VCO ), in unit of 10Khz
	uint16_t SpreadSpectrumPercentage; // in unit of 0.01%
	uint16_t SpreadRateInKhz;    // in unit of kHz, modulation freq
	uint8_t  ClockIndication;    // Indicate which clock source needs SS
	uint8_t  SpreadSpectrumMode; // Bit1=0 Down Spread,=1 Center Spread.
	uint8_t  Reserved[2];
};

// Define ucClockIndication, SW uses the IDs below to search if the SS is requried/enabled on a clock branch/signal type.
// SS is not required or enabled if a match is not found.
#define ASIC_INTERNAL_MEMORY_SS      1
#define ASIC_INTERNAL_ENGINE_SS      2
#define ASIC_INTERNAL_UVD_SS         3
#define ASIC_INTERNAL_SS_ON_TMDS     4
#define ASIC_INTERNAL_SS_ON_HDMI     5
#define ASIC_INTERNAL_SS_ON_LVDS     6
#define ASIC_INTERNAL_SS_ON_DP       7
#define ASIC_INTERNAL_SS_ON_DCPLL    8
#define ASIC_EXTERNAL_SS_ON_DP_CLOCK 9
#define ASIC_INTERNAL_VCE_SS        10
#define ASIC_INTERNAL_GPUPLL_SS     11


struct atom_asic_ss_assignment_v2 {
	uint32_t TargetClockRange; // For mem/engine/uvd, Clock Out frequence (VCO ), in unit of 10Khz
                               // For TMDS/HDMI/LVDS, it is pixel clock , for DP, it is link clock ( 27000 or 16200 )
	uint16_t SpreadSpectrumPercentage; // in unit of 0.01%
	uint16_t SpreadRateIn10Hz;   // in unit of 10Hz, modulation freq
	uint8_t  ClockIndication;    // Indicate which clock source needs SS
	uint8_t  SpreadSpectrumMode; // Bit0=0 Down Spread,=1 Center Spread, bit1=0: internal SS bit1=1: external SS
	uint8_t  Reserved[2];
};

// ucSpreadSpectrumMode
// #define ATOM_SS_DOWN_SPREAD_MODE_MASK   0x00000000
// #define ATOM_SS_DOWN_SPREAD_MODE        0x00000000
// #define ATOM_SS_CENTRE_SPREAD_MODE_MASK 0x00000001
// #define ATOM_SS_CENTRE_SPREAD_MODE      0x00000001
// #define ATOM_INTERNAL_SS_MASK           0x00000000
// #define ATOM_EXTERNAL_SS_MASK           0x00000002

struct atom_asic_internal_ss_info {
	struct atom_common_table_header table_header;
	struct atom_asic_ss_assignment SpreadSpectrum[4];
};

struct atom_asic_internal_ss_info_v2 {
	struct atom_common_table_header table_header;
	struct atom_asic_ss_assignment_v2 SpreadSpectrum[]; // this is point only.
};

struct atom_asic_ss_assignment_v3 {
	uint32_t TargetClockRange;// For mem/engine/uvd, Clock Out frequence (VCO ), in unit of 10Khz
      // For TMDS/HDMI/LVDS, it is pixel clock , for DP, it is link clock ( 27000 or 16200 )
	uint16_t SpreadSpectrumPercentage; // in unit of 0.01% or 0.001%, decided by ucSpreadSpectrumMode bit4
	uint16_t SpreadRateIn10Hz;   // in unit of 10Hz, modulation freq
	uint8_t  ClockIndication;    // Indicate which clock source needs SS
	uint8_t  SpreadSpectrumMode; // Bit0=0 Down Spread,=1 Center Spread, bit1=0: internal SS bit1=1: external SS
	uint8_t  Reserved[2];
};

// ATOM_ASIC_SS_ASSIGNMENT_V3.ucSpreadSpectrumMode
#define SS_MODE_V3_CENTRE_SPREAD_MASK          0x01
#define SS_MODE_V3_EXTERNAL_SS_MASK            0x02
#define SS_MODE_V3_PERCENTAGE_DIV_BY_1000_MASK 0x10

struct atom_asic_internal_ss_info_v3 {
	struct atom_common_table_header table_header;
	struct atom_asic_ss_assignment_v3 SpreadSpectrum[]; // this is pointer only.
};


/******************************************************************************/
// Scratch Pad Definition Portion
/******************************************************************************/
#define ATOM_DEVICE_CONNECT_INFO_DEF 0
#define ATOM_ROM_LOCATION_DEF        1
#define ATOM_TV_STANDARD_DEF         2
#define ATOM_ACTIVE_INFO_DEF         3
#define ATOM_LCD_INFO_DEF            4
#define ATOM_DOS_REQ_INFO_DEF        5
#define ATOM_ACC_CHANGE_INFO_DEF     6
#define ATOM_DOS_MODE_INFO_DEF       7
#define ATOM_I2C_CHANNEL_STATUS_DEF  8
#define ATOM_I2C_CHANNEL_STATUS1_DEF 9
#define ATOM_INTERNAL_TIMER_DEF      10

// BIOS_0_SCRATCH Definition
#define ATOM_S0_CRT1_MONO       0x00000001L
#define ATOM_S0_CRT1_COLOR      0x00000002L
#define ATOM_S0_CRT1_MASK       (ATOM_S0_CRT1_MONO+ATOM_S0_CRT1_COLOR)

#define ATOM_S0_TV1_COMPOSITE_A 0x00000004L
#define ATOM_S0_TV1_SVIDEO_A    0x00000008L
#define ATOM_S0_TV1_MASK_A      (ATOM_S0_TV1_COMPOSITE_A+ATOM_S0_TV1_SVIDEO_A)

#define ATOM_S0_CV_A            0x00000010L
#define ATOM_S0_CV_DIN_A        0x00000020L
#define ATOM_S0_CV_MASK_A       (ATOM_S0_CV_A+ATOM_S0_CV_DIN_A)


#define ATOM_S0_CRT2_MONO       0x00000100L
#define ATOM_S0_CRT2_COLOR      0x00000200L
#define ATOM_S0_CRT2_MASK       (ATOM_S0_CRT2_MONO+ATOM_S0_CRT2_COLOR)

#define ATOM_S0_TV1_COMPOSITE   0x00000400L
#define ATOM_S0_TV1_SVIDEO      0x00000800L
#define ATOM_S0_TV1_SCART       0x00004000L
#define ATOM_S0_TV1_MASK        (ATOM_S0_TV1_COMPOSITE+ATOM_S0_TV1_SVIDEO+ATOM_S0_TV1_SCART)

#define ATOM_S0_CV              0x00001000L
#define ATOM_S0_CV_DIN          0x00002000L
#define ATOM_S0_CV_MASK         (ATOM_S0_CV+ATOM_S0_CV_DIN)

#define ATOM_S0_DFP1 0x00010000L
#define ATOM_S0_DFP2 0x00020000L
#define ATOM_S0_LCD1 0x00040000L
#define ATOM_S0_LCD2 0x00080000L
#define ATOM_S0_DFP6 0x00100000L
#define ATOM_S0_DFP3 0x00200000L
#define ATOM_S0_DFP4 0x00400000L
#define ATOM_S0_DFP5 0x00800000L


#define ATOM_S0_DFP_MASK ATOM_S0_DFP1 | ATOM_S0_DFP2 | ATOM_S0_DFP3 | ATOM_S0_DFP4 | ATOM_S0_DFP5 | ATOM_S0_DFP6

#define ATOM_S0_FAD_REGISTER_BUG 0x02000000L // If set, indicates we are running a PCIE asic with
                                             // the FAD/HDP reg access bug.  Bit is read by DAL, this is obsolete from RV5xx

#define ATOM_S0_THERMAL_STATE_MASK  0x1C000000L
#define ATOM_S0_THERMAL_STATE_SHIFT 26

#define ATOM_S0_SYSTEM_POWER_STATE_MASK 0xE0000000L
#define ATOM_S0_SYSTEM_POWER_STATE_SHIFT 29

#define ATOM_S0_SYSTEM_POWER_STATE_VALUE_AC     1
#define ATOM_S0_SYSTEM_POWER_STATE_VALUE_DC     2
#define ATOM_S0_SYSTEM_POWER_STATE_VALUE_LITEAC 3
#define ATOM_S0_SYSTEM_POWER_STATE_VALUE_LIT2AC 4

// Byte aligned defintion for BIOS usage
#define ATOM_S0_CRT1_MONOb0  0x01
#define ATOM_S0_CRT1_COLORb0 0x02
#define ATOM_S0_CRT1_MASKb0  (ATOM_S0_CRT1_MONOb0+ATOM_S0_CRT1_COLORb0)

#define ATOM_S0_TV1_COMPOSITEb0 0x04
#define ATOM_S0_TV1_SVIDEOb0    0x08
#define ATOM_S0_TV1_MASKb0      (ATOM_S0_TV1_COMPOSITEb0+ATOM_S0_TV1_SVIDEOb0)

#define ATOM_S0_CVb0      0x10
#define ATOM_S0_CV_DINb0  0x20
#define ATOM_S0_CV_MASKb0 (ATOM_S0_CVb0+ATOM_S0_CV_DINb0)

#define ATOM_S0_CRT2_MONOb1  0x01
#define ATOM_S0_CRT2_COLORb1 0x02
#define ATOM_S0_CRT2_MASKb1  (ATOM_S0_CRT2_MONOb1+ATOM_S0_CRT2_COLORb1)

#define ATOM_S0_TV1_COMPOSITEb1 0x04
#define ATOM_S0_TV1_SVIDEOb1    0x08
#define ATOM_S0_TV1_SCARTb1     0x40
#define ATOM_S0_TV1_MASKb1      (ATOM_S0_TV1_COMPOSITEb1+ATOM_S0_TV1_SVIDEOb1+ATOM_S0_TV1_SCARTb1)

#define ATOM_S0_CVb1      0x10
#define ATOM_S0_CV_DINb1  0x20
#define ATOM_S0_CV_MASKb1 (ATOM_S0_CVb1+ATOM_S0_CV_DINb1)

#define ATOM_S0_DFP1b2 0x01
#define ATOM_S0_DFP2b2 0x02
#define ATOM_S0_LCD1b2 0x04
#define ATOM_S0_LCD2b2 0x08
#define ATOM_S0_DFP6b2 0x10
#define ATOM_S0_DFP3b2 0x20
#define ATOM_S0_DFP4b2 0x40
#define ATOM_S0_DFP5b2 0x80


#define ATOM_S0_THERMAL_STATE_MASKb3  0x1C
#define ATOM_S0_THERMAL_STATE_SHIFTb3 2

#define ATOM_S0_SYSTEM_POWER_STATE_MASKb3 0xE0
#define ATOM_S0_LCD1_SHIFT 18

// BIOS_1_SCRATCH Definition
#define ATOM_S1_ROM_LOCATION_MASK 0x0000FFFFL
#define ATOM_S1_PCI_BUS_DEV_MASK  0xFFFF0000L

// BIOS_2_SCRATCH Definition
#define ATOM_S2_TV1_STANDARD_MASK      0x0000000FL
#define ATOM_S2_CURRENT_BL_LEVEL_MASK  0x0000FF00L
#define ATOM_S2_CURRENT_BL_LEVEL_SHIFT 8

#define ATOM_S2_FORCEDLOWPWRMODE_STATE_MASK       0x0C000000L
#define ATOM_S2_FORCEDLOWPWRMODE_STATE_MASK_SHIFT 26
#define ATOM_S2_FORCEDLOWPWRMODE_STATE_CHANGE     0x10000000L

#define ATOM_S2_DEVICE_DPMS_STATE 0x00010000L
#define ATOM_S2_VRI_BRIGHT_ENABLE 0x20000000L

#define ATOM_S2_DISPLAY_ROTATION_0_DEGREE     0x0
#define ATOM_S2_DISPLAY_ROTATION_90_DEGREE    0x1
#define ATOM_S2_DISPLAY_ROTATION_180_DEGREE   0x2
#define ATOM_S2_DISPLAY_ROTATION_270_DEGREE   0x3
#define ATOM_S2_DISPLAY_ROTATION_DEGREE_SHIFT 30
#define ATOM_S2_DISPLAY_ROTATION_ANGLE_MASK   0xC0000000L


// Byte aligned defintion for BIOS usage
#define ATOM_S2_TV1_STANDARD_MASKb0     0x0F
#define ATOM_S2_CURRENT_BL_LEVEL_MASKb1 0xFF
#define ATOM_S2_DEVICE_DPMS_STATEb2     0x01

#define ATOM_S2_TMDS_COHERENT_MODEb3  0x10          // used by VBIOS code only, use coherent mode for TMDS/HDMI mode
#define ATOM_S2_VRI_BRIGHT_ENABLEb3   0x20
#define ATOM_S2_ROTATION_STATE_MASKb3 0xC0


// BIOS_3_SCRATCH Definition
#define ATOM_S3_CRT1_ACTIVE 0x00000001L
#define ATOM_S3_LCD1_ACTIVE 0x00000002L
#define ATOM_S3_TV1_ACTIVE  0x00000004L
#define ATOM_S3_DFP1_ACTIVE 0x00000008L
#define ATOM_S3_CRT2_ACTIVE 0x00000010L
#define ATOM_S3_LCD2_ACTIVE 0x00000020L
#define ATOM_S3_DFP6_ACTIVE 0x00000040L
#define ATOM_S3_DFP2_ACTIVE 0x00000080L
#define ATOM_S3_CV_ACTIVE   0x00000100L
#define ATOM_S3_DFP3_ACTIVE 0x00000200L
#define ATOM_S3_DFP4_ACTIVE 0x00000400L
#define ATOM_S3_DFP5_ACTIVE 0x00000800L


#define ATOM_S3_DEVICE_ACTIVE_MASK 0x00000FFFL

#define ATOM_S3_LCD_FULLEXPANSION_ACTIVE         0x00001000L
#define ATOM_S3_LCD_EXPANSION_ASPEC_RATIO_ACTIVE 0x00002000L

#define ATOM_S3_CRT1_CRTC_ACTIVE 0x00010000L
#define ATOM_S3_LCD1_CRTC_ACTIVE 0x00020000L
#define ATOM_S3_TV1_CRTC_ACTIVE  0x00040000L
#define ATOM_S3_DFP1_CRTC_ACTIVE 0x00080000L
#define ATOM_S3_CRT2_CRTC_ACTIVE 0x00100000L
#define ATOM_S3_LCD2_CRTC_ACTIVE 0x00200000L
#define ATOM_S3_DFP6_CRTC_ACTIVE 0x00400000L
#define ATOM_S3_DFP2_CRTC_ACTIVE 0x00800000L
#define ATOM_S3_CV_CRTC_ACTIVE   0x01000000L
#define ATOM_S3_DFP3_CRTC_ACTIVE 0x02000000L
#define ATOM_S3_DFP4_CRTC_ACTIVE 0x04000000L
#define ATOM_S3_DFP5_CRTC_ACTIVE 0x08000000L


#define ATOM_S3_DEVICE_CRTC_ACTIVE_MASK 0x0FFF0000L
#define ATOM_S3_ASIC_GUI_ENGINE_HUNG    0x20000000L
// Below two definitions are not supported in pplib, but in the old powerplay in DAL
#define ATOM_S3_ALLOW_FAST_PWR_SWITCH   0x40000000L
#define ATOM_S3_RQST_GPU_USE_MIN_PWR    0x80000000L



// Byte aligned defintion for BIOS usage
#define ATOM_S3_CRT1_ACTIVEb0 0x01
#define ATOM_S3_LCD1_ACTIVEb0 0x02
#define ATOM_S3_TV1_ACTIVEb0  0x04
#define ATOM_S3_DFP1_ACTIVEb0 0x08
#define ATOM_S3_CRT2_ACTIVEb0 0x10
#define ATOM_S3_LCD2_ACTIVEb0 0x20
#define ATOM_S3_DFP6_ACTIVEb0 0x40
#define ATOM_S3_DFP2_ACTIVEb0 0x80
#define ATOM_S3_CV_ACTIVEb1   0x01
#define ATOM_S3_DFP3_ACTIVEb1 0x02
#define ATOM_S3_DFP4_ACTIVEb1 0x04
#define ATOM_S3_DFP5_ACTIVEb1 0x08


#define ATOM_S3_ACTIVE_CRTC1w0 0xFFF

#define ATOM_S3_CRT1_CRTC_ACTIVEb2 0x01
#define ATOM_S3_LCD1_CRTC_ACTIVEb2 0x02
#define ATOM_S3_TV1_CRTC_ACTIVEb2  0x04
#define ATOM_S3_DFP1_CRTC_ACTIVEb2 0x08
#define ATOM_S3_CRT2_CRTC_ACTIVEb2 0x10
#define ATOM_S3_LCD2_CRTC_ACTIVEb2 0x20
#define ATOM_S3_DFP6_CRTC_ACTIVEb2 0x40
#define ATOM_S3_DFP2_CRTC_ACTIVEb2 0x80
#define ATOM_S3_CV_CRTC_ACTIVEb3   0x01
#define ATOM_S3_DFP3_CRTC_ACTIVEb3 0x02
#define ATOM_S3_DFP4_CRTC_ACTIVEb3 0x04
#define ATOM_S3_DFP5_CRTC_ACTIVEb3 0x08


#define ATOM_S3_ACTIVE_CRTC2w1 0xFFF


// BIOS_4_SCRATCH Definition
#define ATOM_S4_LCD1_PANEL_ID_MASK 0x000000FFL
#define ATOM_S4_LCD1_REFRESH_MASK  0x0000FF00L
#define ATOM_S4_LCD1_REFRESH_SHIFT 8

// Byte aligned defintion for BIOS usage
#define ATOM_S4_LCD1_PANEL_ID_MASKb0 0x0FF
#define ATOM_S4_LCD1_REFRESH_MASKb1  ATOM_S4_LCD1_PANEL_ID_MASKb0
#define ATOM_S4_VRAM_INFO_MASKb2     ATOM_S4_LCD1_PANEL_ID_MASKb0

// BIOS_5_SCRATCH Definition, BIOS_5_SCRATCH is used by Firmware only !!!!
#define ATOM_S5_DOS_REQ_CRT1b0 0x01
#define ATOM_S5_DOS_REQ_LCD1b0 0x02
#define ATOM_S5_DOS_REQ_TV1b0  0x04
#define ATOM_S5_DOS_REQ_DFP1b0 0x08
#define ATOM_S5_DOS_REQ_CRT2b0 0x10
#define ATOM_S5_DOS_REQ_LCD2b0 0x20
#define ATOM_S5_DOS_REQ_DFP6b0 0x40
#define ATOM_S5_DOS_REQ_DFP2b0 0x80
#define ATOM_S5_DOS_REQ_CVb1   0x01
#define ATOM_S5_DOS_REQ_DFP3b1 0x02
#define ATOM_S5_DOS_REQ_DFP4b1 0x04
#define ATOM_S5_DOS_REQ_DFP5b1 0x08


#define ATOM_S5_DOS_REQ_DEVICEw0 0x0FFF

#define ATOM_S5_DOS_REQ_CRT1 0x0001
#define ATOM_S5_DOS_REQ_LCD1 0x0002
#define ATOM_S5_DOS_REQ_TV1  0x0004
#define ATOM_S5_DOS_REQ_DFP1 0x0008
#define ATOM_S5_DOS_REQ_CRT2 0x0010
#define ATOM_S5_DOS_REQ_LCD2 0x0020
#define ATOM_S5_DOS_REQ_DFP6 0x0040
#define ATOM_S5_DOS_REQ_DFP2 0x0080
#define ATOM_S5_DOS_REQ_CV   0x0100
#define ATOM_S5_DOS_REQ_DFP3 0x0200
#define ATOM_S5_DOS_REQ_DFP4 0x0400
#define ATOM_S5_DOS_REQ_DFP5 0x0800

#define ATOM_S5_DOS_FORCE_CRT1b2   ATOM_S5_DOS_REQ_CRT1b0
#define ATOM_S5_DOS_FORCE_TV1b2    ATOM_S5_DOS_REQ_TV1b0
#define ATOM_S5_DOS_FORCE_CRT2b2   ATOM_S5_DOS_REQ_CRT2b0
#define ATOM_S5_DOS_FORCE_CVb3     ATOM_S5_DOS_REQ_CVb1
#define ATOM_S5_DOS_FORCE_DEVICEw1 (ATOM_S5_DOS_FORCE_CRT1b2+ATOM_S5_DOS_FORCE_TV1b2+ATOM_S5_DOS_FORCE_CRT2b2+\
                                   (ATOM_S5_DOS_FORCE_CVb3<<8))
// BIOS_6_SCRATCH Definition
#define ATOM_S6_DEVICE_CHANGE         0x00000001L
#define ATOM_S6_SCALER_CHANGE         0x00000002L
#define ATOM_S6_LID_CHANGE            0x00000004L
#define ATOM_S6_DOCKING_CHANGE        0x00000008L
#define ATOM_S6_ACC_MODE              0x00000010L
#define ATOM_S6_EXT_DESKTOP_MODE      0x00000020L
#define ATOM_S6_LID_STATE             0x00000040L
#define ATOM_S6_DOCK_STATE            0x00000080L
#define ATOM_S6_CRITICAL_STATE        0x00000100L
#define ATOM_S6_HW_I2C_BUSY_STATE     0x00000200L
#define ATOM_S6_THERMAL_STATE_CHANGE  0x00000400L
#define ATOM_S6_INTERRUPT_SET_BY_BIOS 0x00000800L
#define ATOM_S6_REQ_LCD_EXPANSION_FULL        0x00001000L // Normal expansion Request bit for LCD
#define ATOM_S6_REQ_LCD_EXPANSION_ASPEC_RATIO 0x00002000L // Aspect ratio expansion Request bit for LCD

#define ATOM_S6_DISPLAY_STATE_CHANGE 0x00004000L        // This bit is recycled when ATOM_BIOS_INFO_BIOS_SCRATCH6_SCL2_REDEFINE is set,previously it's SCL2_H_expansion
#define ATOM_S6_I2C_STATE_CHANGE     0x00008000L        // This bit is recycled,when ATOM_BIOS_INFO_BIOS_SCRATCH6_SCL2_REDEFINE is set,previously it's SCL2_V_expansion

#define ATOM_S6_ACC_REQ_CRT1 0x00010000L
#define ATOM_S6_ACC_REQ_LCD1 0x00020000L
#define ATOM_S6_ACC_REQ_TV1  0x00040000L
#define ATOM_S6_ACC_REQ_DFP1 0x00080000L
#define ATOM_S6_ACC_REQ_CRT2 0x00100000L
#define ATOM_S6_ACC_REQ_LCD2 0x00200000L
#define ATOM_S6_ACC_REQ_DFP6 0x00400000L
#define ATOM_S6_ACC_REQ_DFP2 0x00800000L
#define ATOM_S6_ACC_REQ_CV   0x01000000L
#define ATOM_S6_ACC_REQ_DFP3 0x02000000L
#define ATOM_S6_ACC_REQ_DFP4 0x04000000L
#define ATOM_S6_ACC_REQ_DFP5 0x08000000L

#define ATOM_S6_ACC_REQ_MASK               0x0FFF0000L
#define ATOM_S6_SYSTEM_POWER_MODE_CHANGE   0x10000000L
#define ATOM_S6_ACC_BLOCK_DISPLAY_SWITCH   0x20000000L
#define ATOM_S6_VRI_BRIGHTNESS_CHANGE      0x40000000L
#define ATOM_S6_CONFIG_DISPLAY_CHANGE_MASK 0x80000000L

// Byte aligned defintion for BIOS usage
#define ATOM_S6_DEVICE_CHANGEb0         0x01
#define ATOM_S6_SCALER_CHANGEb0         0x02
#define ATOM_S6_LID_CHANGEb0            0x04
#define ATOM_S6_DOCKING_CHANGEb0        0x08
#define ATOM_S6_ACC_MODEb0              0x10
#define ATOM_S6_EXT_DESKTOP_MODEb0      0x20
#define ATOM_S6_LID_STATEb0             0x40
#define ATOM_S6_DOCK_STATEb0            0x80
#define ATOM_S6_CRITICAL_STATEb1        0x01
#define ATOM_S6_HW_I2C_BUSY_STATEb1     0x02
#define ATOM_S6_THERMAL_STATE_CHANGEb1  0x04
#define ATOM_S6_INTERRUPT_SET_BY_BIOSb1 0x08
#define ATOM_S6_REQ_LCD_EXPANSION_FULLb1        0x10
#define ATOM_S6_REQ_LCD_EXPANSION_ASPEC_RATIOb1 0x20

#define ATOM_S6_ACC_REQ_CRT1b2 0x01
#define ATOM_S6_ACC_REQ_LCD1b2 0x02
#define ATOM_S6_ACC_REQ_TV1b2  0x04
#define ATOM_S6_ACC_REQ_DFP1b2 0x08
#define ATOM_S6_ACC_REQ_CRT2b2 0x10
#define ATOM_S6_ACC_REQ_LCD2b2 0x20
#define ATOM_S6_ACC_REQ_DFP6b2 0x40
#define ATOM_S6_ACC_REQ_DFP2b2 0x80
#define ATOM_S6_ACC_REQ_CVb3   0x01
#define ATOM_S6_ACC_REQ_DFP3b3 0x02
#define ATOM_S6_ACC_REQ_DFP4b3 0x04
#define ATOM_S6_ACC_REQ_DFP5b3 0x08

#define ATOM_S6_ACC_REQ_DEVICEw1        ATOM_S5_DOS_REQ_DEVICEw0
#define ATOM_S6_SYSTEM_POWER_MODE_CHANGEb3 0x10
#define ATOM_S6_ACC_BLOCK_DISPLAY_SWITCHb3 0x20
#define ATOM_S6_VRI_BRIGHTNESS_CHANGEb3    0x40
#define ATOM_S6_CONFIG_DISPLAY_CHANGEb3    0x80

#define ATOM_S6_DEVICE_CHANGE_SHIFT            0
#define ATOM_S6_SCALER_CHANGE_SHIFT            1
#define ATOM_S6_LID_CHANGE_SHIFT               2
#define ATOM_S6_DOCKING_CHANGE_SHIFT           3
#define ATOM_S6_ACC_MODE_SHIFT                 4
#define ATOM_S6_EXT_DESKTOP_MODE_SHIFT         5
#define ATOM_S6_LID_STATE_SHIFT                6
#define ATOM_S6_DOCK_STATE_SHIFT               7
#define ATOM_S6_CRITICAL_STATE_SHIFT           8
#define ATOM_S6_HW_I2C_BUSY_STATE_SHIFT        9
#define ATOM_S6_THERMAL_STATE_CHANGE_SHIFT     10
#define ATOM_S6_INTERRUPT_SET_BY_BIOS_SHIFT    11
#define ATOM_S6_REQ_SCALER_SHIFT               12
#define ATOM_S6_REQ_SCALER_ARATIO_SHIFT        13
#define ATOM_S6_DISPLAY_STATE_CHANGE_SHIFT     14
#define ATOM_S6_I2C_STATE_CHANGE_SHIFT         15
#define ATOM_S6_SYSTEM_POWER_MODE_CHANGE_SHIFT 28
#define ATOM_S6_ACC_BLOCK_DISPLAY_SWITCH_SHIFT 29
#define ATOM_S6_VRI_BRIGHTNESS_CHANGE_SHIFT    30
#define ATOM_S6_CONFIG_DISPLAY_CHANGE_SHIFT    31

// BIOS_7_SCRATCH Definition, BIOS_7_SCRATCH is used by Firmware only !!!!
#define ATOM_S7_DOS_MODE_TYPEb0         0x03
#define ATOM_S7_DOS_MODE_VGAb0          0x00
#define ATOM_S7_DOS_MODE_VESAb0         0x01
#define ATOM_S7_DOS_MODE_EXTb0          0x02
#define ATOM_S7_DOS_MODE_PIXEL_DEPTHb0  0x0C
#define ATOM_S7_DOS_MODE_PIXEL_FORMATb0 0xF0
#define ATOM_S7_DOS_8BIT_DAC_ENb1       0x01
#define ATOM_S7_ASIC_INIT_COMPLETEb1    0x02
#define ATOM_S7_ASIC_INIT_COMPLETE_MASK 0x00000200
#define ATOM_S7_DOS_MODE_NUMBERw1       0x0FFFF

#define ATOM_S7_DOS_8BIT_DAC_EN_SHIFT 8

// BIOS_8_SCRATCH Definition
#define ATOM_S8_I2C_CHANNEL_BUSY_MASK   0x00000FFFF
#define ATOM_S8_I2C_HW_ENGINE_BUSY_MASK 0x0FFFF0000

#define ATOM_S8_I2C_CHANNEL_BUSY_SHIFT  0
#define ATOM_S8_I2C_ENGINE_BUSY_SHIFT   16

// BIOS_9_SCRATCH Definition
#ifndef ATOM_S9_I2C_CHANNEL_COMPLETED_MASK
#define ATOM_S9_I2C_CHANNEL_COMPLETED_MASK 0x0000FFFF
#endif
#ifndef ATOM_S9_I2C_CHANNEL_ABORTED_MASK
#define ATOM_S9_I2C_CHANNEL_ABORTED_MASK 0xFFFF0000
#endif
#ifndef ATOM_S9_I2C_CHANNEL_COMPLETED_SHIFT
#define ATOM_S9_I2C_CHANNEL_COMPLETED_SHIFT 0
#endif
#ifndef ATOM_S9_I2C_CHANNEL_ABORTED_SHIFT
#define ATOM_S9_I2C_CHANNEL_ABORTED_SHIFT 16
#endif


#define ATOM_FLAG_SET                        0x20
#define ATOM_FLAG_CLEAR                      0
#define CLEAR_ATOM_S6_ACC_MODE               ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_ACC_MODE_SHIFT | ATOM_FLAG_CLEAR)
#define SET_ATOM_S6_DEVICE_CHANGE            ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_DEVICE_CHANGE_SHIFT | ATOM_FLAG_SET)
#define SET_ATOM_S6_VRI_BRIGHTNESS_CHANGE    ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_VRI_BRIGHTNESS_CHANGE_SHIFT | ATOM_FLAG_SET)
#define SET_ATOM_S6_SCALER_CHANGE            ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_SCALER_CHANGE_SHIFT | ATOM_FLAG_SET)
#define SET_ATOM_S6_LID_CHANGE               ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_LID_CHANGE_SHIFT | ATOM_FLAG_SET)

#define SET_ATOM_S6_LID_STATE                ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_LID_STATE_SHIFT | ATOM_FLAG_SET)
#define CLEAR_ATOM_S6_LID_STATE              ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_LID_STATE_SHIFT | ATOM_FLAG_CLEAR)

#define SET_ATOM_S6_DOCK_CHANGE              ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_DOCKING_CHANGE_SHIFT | ATOM_FLAG_SET)
#define SET_ATOM_S6_DOCK_STATE               ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_DOCK_STATE_SHIFT | ATOM_FLAG_SET)
#define CLEAR_ATOM_S6_DOCK_STATE             ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_DOCK_STATE_SHIFT | ATOM_FLAG_CLEAR)

#define SET_ATOM_S6_THERMAL_STATE_CHANGE     ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_THERMAL_STATE_CHANGE_SHIFT | ATOM_FLAG_SET)
#define SET_ATOM_S6_SYSTEM_POWER_MODE_CHANGE ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_SYSTEM_POWER_MODE_CHANGE_SHIFT | ATOM_FLAG_SET)
#define SET_ATOM_S6_INTERRUPT_SET_BY_BIOS    ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_INTERRUPT_SET_BY_BIOS_SHIFT | ATOM_FLAG_SET)

#define SET_ATOM_S6_CRITICAL_STATE           ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_CRITICAL_STATE_SHIFT | ATOM_FLAG_SET)
#define CLEAR_ATOM_S6_CRITICAL_STATE         ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_CRITICAL_STATE_SHIFT | ATOM_FLAG_CLEAR)

#define SET_ATOM_S6_REQ_SCALER               ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_REQ_SCALER_SHIFT | ATOM_FLAG_SET)
#define CLEAR_ATOM_S6_REQ_SCALER             ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_REQ_SCALER_SHIFT | ATOM_FLAG_CLEAR )

#define SET_ATOM_S6_REQ_SCALER_ARATIO        ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_REQ_SCALER_ARATIO_SHIFT | ATOM_FLAG_SET )
#define CLEAR_ATOM_S6_REQ_SCALER_ARATIO      ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_REQ_SCALER_ARATIO_SHIFT | ATOM_FLAG_CLEAR )

#define SET_ATOM_S6_I2C_STATE_CHANGE         ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_I2C_STATE_CHANGE_SHIFT | ATOM_FLAG_SET )

#define SET_ATOM_S6_DISPLAY_STATE_CHANGE     ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_DISPLAY_STATE_CHANGE_SHIFT | ATOM_FLAG_SET )

#define SET_ATOM_S6_DEVICE_RECONFIG          ((ATOM_ACC_CHANGE_INFO_DEF << 8 )|ATOM_S6_CONFIG_DISPLAY_CHANGE_SHIFT | ATOM_FLAG_SET)
#define CLEAR_ATOM_S0_LCD1                   ((ATOM_DEVICE_CONNECT_INFO_DEF << 8 )|  ATOM_S0_LCD1_SHIFT | ATOM_FLAG_CLEAR )
#define SET_ATOM_S7_DOS_8BIT_DAC_EN          ((ATOM_DOS_MODE_INFO_DEF << 8 )|ATOM_S7_DOS_8BIT_DAC_EN_SHIFT | ATOM_FLAG_SET )
#define CLEAR_ATOM_S7_DOS_8BIT_DAC_EN        ((ATOM_DOS_MODE_INFO_DEF << 8 )|ATOM_S7_DOS_8BIT_DAC_EN_SHIFT | ATOM_FLAG_CLEAR )

/******************************************************************************/
// Portion II: Definitinos only used in Driver
/******************************************************************************/

// Macros used by driver

#ifdef __cplusplus
#define GetIndexIntoMasterTable(MasterOrData, FieldName) ((reinterpret_cast<char*>(&(static_cast<ATOM_MASTER_LIST_OF_##MasterOrData##_TABLES*>(0))->FieldName)-static_cast<char*>(0))/sizeof(uint16_t))

#define GET_COMMAND_TABLE_COMMANDSET_REVISION(TABLE_HEADER_OFFSET) (((static_cast<ATOM_COMMON_TABLE_HEADER*>(TABLE_HEADER_OFFSET))->ucTableFormatRevision )&0x3F)
#define GET_COMMAND_TABLE_PARAMETER_REVISION(TABLE_HEADER_OFFSET)  (((static_cast<ATOM_COMMON_TABLE_HEADER*>(TABLE_HEADER_OFFSET))->ucTableContentRevision)&0x3F)
#else // not __cplusplus
#define GetIndexIntoMasterTable(MasterOrData, FieldName) (offsetof(ATOM_MASTER_LIST_OF_##MasterOrData##_TABLES, FieldName) / sizeof(uint16_t))

#define GET_COMMAND_TABLE_COMMANDSET_REVISION(TABLE_HEADER_OFFSET) ((((ATOM_COMMON_TABLE_HEADER*)TABLE_HEADER_OFFSET)->ucTableFormatRevision)&0x3F)
#define GET_COMMAND_TABLE_PARAMETER_REVISION(TABLE_HEADER_OFFSET)  ((((ATOM_COMMON_TABLE_HEADER*)TABLE_HEADER_OFFSET)->ucTableContentRevision)&0x3F)
#endif // __cplusplus

#define GET_DATA_TABLE_MAJOR_REVISION GET_COMMAND_TABLE_COMMANDSET_REVISION
#define GET_DATA_TABLE_MINOR_REVISION GET_COMMAND_TABLE_PARAMETER_REVISION

/******************************************************************************/
// Portion III: Definitinos only used in VBIOS
/******************************************************************************/
#define ATOM_DAC_SRC  0x80
#define ATOM_SRC_DAC1 0
#define ATOM_SRC_DAC2 0x80



struct memory_pllinit_parameters {
	uint32_t TargetMemoryClock; // In 10Khz unit
	uint8_t  Action;   // not define yet
	uint8_t  FbDiv_Hi; // Fbdiv Hi byte
	uint8_t  FbDiv;    // FB value
	uint8_t  PostDiv;  // Post div
};

#define MEMORY_PLLINIT_PS_ALLOCATION  MEMORY_PLLINIT_PARAMETERS


#define GPIO_PIN_WRITE 0x01
#define GPIO_PIN_READ  0x00

struct gpio_pin_control_parameters {
	uint8_t  GPIO_ID;      // return value, read from GPIO pins
	uint8_t  GPIOBitShift; // define which bit in uGPIOBitVal need to be update
	uint8_t  GPIOBitVal;   // Set/Reset corresponding bit defined in ucGPIOBitMask
	uint8_t  Action;       // =GPIO_PIN_WRITE: Read; =GPIO_PIN_READ: Write
};

struct enable_scaler_parameters {
	uint8_t  Scaler; // ATOM_SCALER1, ATOM_SCALER2
	uint8_t  Enable; // ATOM_SCALER_DISABLE or ATOM_SCALER_CENTER or ATOM_SCALER_EXPANSION
	uint8_t  TVStandard;
	uint8_t  Padding[1];
};
#define ENABLE_SCALER_PS_ALLOCATION ENABLE_SCALER_PARAMETERS

// ucEnable:
#define SCALER_BYPASS_AUTO_CENTER_NO_REPLICATION   0
#define SCALER_BYPASS_AUTO_CENTER_AUTO_REPLICATION 1
#define SCALER_ENABLE_2TAP_ALPHA_MODE              2
#define SCALER_ENABLE_MULTITAP_MODE                3

struct enable_hardware_icon_cursor_parameters {
	uint32_t usHWIconHorzVertPosn; // Hardware Icon Vertical position
	uint8_t  HWIconVertOffset; // Hardware Icon Vertical offset
	uint8_t  HWIconHorzOffset; // Hardware Icon Horizontal offset
	uint8_t  Selection; // ATOM_CURSOR1 or ATOM_ICON1 or ATOM_CURSOR2 or ATOM_ICON2
	uint8_t  Enable;    // ATOM_ENABLE or ATOM_DISABLE
};

struct enable_hardware_icon_cursor_ps_allocation {
	struct enable_hardware_icon_cursor_parameters EnableIcon;
	struct enable_crtc_parameters Reserved;
};

struct enable_graph_surface_parameters {
	uint16_t Hight;   // Image Hight
	uint16_t Width;   // Image Width
	uint8_t  Surface; // Surface 1 or 2
	uint8_t  Padding[3];
};

struct enable_graph_surface_parameters_v1_2 {
	uint16_t Hight;   // Image Hight
	uint16_t Width;   // Image Width
	uint8_t  Surface; // Surface 1 or 2
	uint8_t  Enable;  // ATOM_ENABLE or ATOM_DISABLE
	uint8_t  Padding[2];
};

struct enable_graph_surface_parameters_v1_3 {
	uint16_t Hight;    // Image Hight
	uint16_t Width;    // Image Width
	uint8_t  Surface;  // Surface 1 or 2
	uint8_t  Enable;   // ATOM_ENABLE or ATOM_DISABLE
	uint16_t DeviceId; // Active Device Id for this surface. If no device, set to 0.
};

struct enable_graph_surface_parameters_v1_4 {
	uint16_t Hight; // Image Hight
	uint16_t Width; // Image Width
	uint16_t GraphPitch;
	uint8_t  ColorDepth;
	uint8_t  PixelFormat;
	uint8_t  Surface; // Surface 1 or 2
	uint8_t  Enable;  // ATOM_ENABLE or ATOM_DISABLE
	uint8_t  ModeType;
	uint8_t  Reserved;
};

// ucEnable
#define ATOM_GRAPH_CONTROL_SET_PITCH      0x0f
#define ATOM_GRAPH_CONTROL_SET_DISP_START 0x10

struct enable_graph_surface_ps_allocation {
	struct enable_graph_surface_parameters SetSurface;
	struct enable_yuv_parameters Reserved; // Don't set this one
};

struct memory_clean_up_parameters {
	uint16_t MemoryStart; // in 8Kb boundry, offset from memory base address
	uint16_t MemorySize;  // 8Kb blocks aligned
};

#define MEMORY_CLEAN_UP_PS_ALLOCATION MEMORY_CLEAN_UP_PARAMETERS

struct get_display_surface_size_parameters {
	uint16_t X_Size; // When use as input parameter, usX_Size indicates which CRTC
	uint16_t Y_Size;
};

struct get_display_surface_size_parameters_v2 {
	union {
		uint16_t X_Size; // When use as input parameter, usX_Size indicates which CRTC
		uint16_t Surface;
	};
	uint16_t Y_Size;
	uint16_t DispXStart;
	uint16_t DispYStart;
};


struct palette_data_control_parameters_v3 {
	uint8_t  LutId;
	uint8_t  Action;
	uint16_t LutStartIndex;
	uint16_t LutLength;
	uint16_t LutOffsetInVram;
};

// ucAction:
#define PALETTE_DATA_AUTO_FILL 1
#define PALETTE_DATA_READ      2
#define PALETTE_DATA_WRITE     3


struct interrupt_service_parameter_v2 {
	uint8_t  InterruptId;
	uint8_t  ServiceId;
	uint8_t  Status;
	uint8_t  Reserved;
};

// ucInterruptId
#define HDP1_INTERRUPT_ID 1
#define HDP2_INTERRUPT_ID 2
#define HDP3_INTERRUPT_ID 3
#define HDP4_INTERRUPT_ID 4
#define HDP5_INTERRUPT_ID 5
#define HDP6_INTERRUPT_ID 6
#define SW_INTERRUPT_ID   11

// ucAction
#define INTERRUPT_SERVICE_GEN_SW_INT 1
#define INTERRUPT_SERVICE_GET_STATUS 2

 // ucStatus
#define INTERRUPT_STATUS__INT_TRIGGER 1
#define INTERRUPT_STATUS__HPD_HIGH    2

struct efuse_input_parameter {
	uint16_t EfuseIndex;
	uint8_t  BitShift;
	uint8_t  BitLength;
};

// ReadEfuseValue command table input/output parameter
union read_efuse_value_parameter {
	struct efuse_input_parameter Efuse;
	uint32_t EfuseValue;
};

struct indirect_io_access {
	struct atom_common_table_header table_header;
	uint8_t  IOAccessSequence[256];
};

#define INDIRECT_READ      0x00
#define INDIRECT_WRITE     0x80

#define INDIRECT_IO_MM     0
#define INDIRECT_IO_PLL    1
#define INDIRECT_IO_MC     2
#define INDIRECT_IO_PCIE   3
#define INDIRECT_IO_PCIEP  4
#define INDIRECT_IO_NBMISC 5
#define INDIRECT_IO_SMU    5

#define INDIRECT_IO_PLL_READ     INDIRECT_IO_PLL   | INDIRECT_READ
#define INDIRECT_IO_PLL_WRITE    INDIRECT_IO_PLL   | INDIRECT_WRITE
#define INDIRECT_IO_MC_READ      INDIRECT_IO_MC    | INDIRECT_READ
#define INDIRECT_IO_MC_WRITE     INDIRECT_IO_MC    | INDIRECT_WRITE
#define INDIRECT_IO_PCIE_READ    INDIRECT_IO_PCIE  | INDIRECT_READ
#define INDIRECT_IO_PCIE_WRITE   INDIRECT_IO_PCIE  | INDIRECT_WRITE
#define INDIRECT_IO_PCIEP_READ   INDIRECT_IO_PCIEP | INDIRECT_READ
#define INDIRECT_IO_PCIEP_WRITE  INDIRECT_IO_PCIEP | INDIRECT_WRITE
#define INDIRECT_IO_NBMISC_READ  INDIRECT_IO_NBMISC | INDIRECT_READ
#define INDIRECT_IO_NBMISC_WRITE INDIRECT_IO_NBMISC | INDIRECT_WRITE
#define INDIRECT_IO_SMU_READ     INDIRECT_IO_SMU | INDIRECT_READ
#define INDIRECT_IO_SMU_WRITE    INDIRECT_IO_SMU | INDIRECT_WRITE


struct atom_oem_info {
	struct atom_common_table_header table_header;
	union atom_i2c_id_config I2cId;
};

struct atom_tv_mode {
	uint8_t  VMode_Num;   // Video mode number
	uint8_t  TV_Mode_Num; // Internal TV mode number
};

struct atom_bios_int_tvstd_mode {
	struct atom_common_table_header table_header;
	uint16_t TV_Mode_LUT_Offset; // Pointer to standard to internal number conversion table
	uint16_t TV_FIFO_Offset;     // Pointer to FIFO entry table
	uint16_t NTSC_Tbl_Offset;    // Pointer to SDTV_Mode_NTSC table
	uint16_t PAL_Tbl_Offset;     // Pointer to SDTV_Mode_PAL table
	uint16_t CV_Tbl_Offset;      // Pointer to SDTV_Mode_PAL table
};


struct atom_tv_mode_scaler_ptr {
	uint16_t ucFilter0_Offset; // Pointer to filter format 0 coefficients
	uint16_t Filter1_Offset;   // Pointer to filter format 0 coefficients
	uint8_t  TV_Mode_Num;
};

struct atom_standard_vesa_timing {
	struct atom_common_table_header table_header;
	struct atom_dtd_format aModeTimings[16]; // 16 is not the real array number, just for initial allocation
};


struct atom_std_format {
	uint16_t STD_HDisp;
	uint16_t STD_VDisp;
	uint16_t STD_RefreshRate;
	uint16_t Reserved;
};

struct atom_vesa_to_extended_mode {
	uint16_t VESA_ModeNumber;
	uint16_t ExtendedModeNumber;
};

//struct atom_vesa_to_intenal_mode_lut { // typo
struct atom_vesa_to_internal_mode_lut {
	struct atom_common_table_header table_header;
	struct atom_vesa_to_extended_mode VESA_ToExtendedModeInfo[76];
};

/******************************************************************************/
// ATOM Memory Related Data Structure
/******************************************************************************/
struct atom_memory_vendor_block {
	enum atom_dgpu_vram_type MemoryType;
	uint8_t  MemoryVendor;
	uint8_t  AdjMCId;
	uint8_t  DynClkId;
	uint32_t DllResetClkRange;
};


// like atom_umc_reg_setting_data_block
struct atom_memory_setting_id_config {
	uint32_t MemClockRange:24;
	uint32_t ucMemBlkId:8;
};
union atom_memory_setting_id_config_access {
	struct atom_memory_setting_id_config lAccess;
	uint32_t Access;
};
struct atom_memory_setting_data_block {
	union atom_memory_setting_id_config_access ulMemoryID;
	uint32_t aulMemData[1];
};


struct atom_init_reg_index_format {
// like atom_umc_register_addr_info_access ??
	uint16_t RegIndex;         // MC register index
	uint8_t  PreRegDataLength; // offset in ATOM_INIT_REG_DATA_BLOCK.saRegDataBuf
};


struct atom_init_reg_block { // like atom_umc_init_reg_block, but with
	uint16_t RegIndexTblSize; // size of asRegIndexBuf
	uint16_t RegDataBlkSize;  // size of ATOM_MEMORY_SETTING_DATA_BLOCK
	// of the struct itself? size of the RegDataBuf array?
	struct atom_init_reg_index_format RegIndexBuf[1];
	struct atom_memory_setting_data_block RegDataBuf[1];
};

#define END_OF_REG_INDEX_BLOCK  0xffff
#define END_OF_REG_DATA_BLOCK   0x00000000
#define ATOM_INIT_REG_MASK_FLAG 0x80 // Not used in BIOS
#define CLOCK_RANGE_HIGHEST     0x00ffffff

// #define VALUE_DWORD         SIZEOF uint32_t
#define VALUE_SAME_AS_ABOVE 0
#define VALUE_MASK_DWORD    0x84

#define INDEX_ACCESS_RANGE_BEGIN  (VALUE_DWORD + 1)
#define INDEX_ACCESS_RANGE_END    (INDEX_ACCESS_RANGE_BEGIN + 1)
#define VALUE_INDEX_ACCESS_SINGLE (INDEX_ACCESS_RANGE_END + 1)
// #define ACCESS_MCIODEBUGIND    0x40       //defined in BIOS code
#define ACCESS_PLACEHOLDER        0x80


struct atom_mc_init_param_table {
	struct atom_common_table_header table_header;
	uint16_t AdjustARB_SEQDataOffset;
	uint16_t MCInitMemTypeTblOffset;
	uint16_t MCInitCommonTblOffset;
	uint16_t MCInitPowerDownTblOffset;
	uint32_t ARB_SEQDataBuf[32];
	struct atom_init_reg_block MCInitMemType;
	struct atom_init_reg_block MCInitCommon;
};


struct atom_reg_init_setting {
	uint16_t RegIndex;
	uint32_t RegValue;
};

struct atom_mc_init_param_table_v2_1 {
	struct atom_common_table_header table_header;
	uint32_t MCUcodeVersion;
	uint32_t MCUcodeRomStartAddr;
	uint32_t MCUcodeLength;
	uint16_t McRegInitTableOffset; // offset of ATOM_REG_INIT_SETTING array for MC core register settings.
	uint16_t Reserved; // offset of ATOM_INIT_REG_BLOCK for MC SEQ/PHY register setting
};


// wordcount x wordwidth in bits.
// A 8Gbit GDDR6 has two 16-bit channels; 16 bit words and 4Gbits per channel.
// 4Gbit/16 = 256Mwords; _256Mx16.
enum DRAM_DENSITY_e:uint8_t {
	// _4Mx4 = 0x00,
	_4Mx16   = 0x02,
	_4Mx32   = 0x03,
	_8Mx16   = 0x12,
	_8Mx32   = 0x13,
	_8Mx128  = 0x15,
	_16Mx16  = 0x22,
	_16Mx32  = 0x23,
	_16Mx128 = 0x25,
	_32Mx16  = 0x32,
	_32Mx32  = 0x33,
	_32Mx128 = 0x35,
	_64Mx8   = 0x41,
	_64Mx16  = 0x42,
	_64Mx32  = 0x43,
	_64Mx128 = 0x45,
	_128Mx8  = 0x51,
	_128Mx16 = 0x52,
	_128Mx32 = 0x53,
	_256Mx8  = 0x61,
	_256Mx16 = 0x62,
	_256Mx32 = 0x63,
	_512Mx8  = 0x71,
	_512Mx16 = 0x72,

/*
	_768Mx16  = 0x82,
*/
};
/* Is this better, or stick with enum?
union dram_density { 
	uint8_t  Density;
	enum DRAM_DENSITY_e density_names;
	struct { uint8_t
		word_width :3-0 +1, // 2**(n+2)
		word_count :7-4 +1; // 2**(n+2)
	};
};
*/


union memory_vendor_id {
	uint8_t  MemoryVendorID; // Predefined,never change across designs or memory type/vender
	struct { uint8_t
		vendor_code :3-0 +1, // GDDR vendor ID
		revision    :7-4 +1; // possibly DDR gen? see enum atom_dgpu_vram_type?
	};
};
// TODO
// see MEM_VENDOR_e in smu13.0.7 ??
#define ATOM_VRAM_MODULE_MEMORY_VENDOR_ID_MASK 0xF
#define SAMSUNG  0x1
#define INFINEON 0x2
#define ELPIDA   0x3
#define ETRON    0x4
#define NANYA    0x5
#define HYNIX    0x6
#define MOSEL    0x7
#define WINBOND  0x8
#define ESMT     0x9
#define MICRON   0xF

#define QIMONDA  INFINEON
#define PROMOS   MOSEL
#define KRETON   INFINEON
#define ELIXIR   NANYA
#define MEZZA    ELPIDA


/******************************************************************************/
// Support for GDDR5 MC uCode to reside in upper 64K of ROM
/******************************************************************************/
#define UCODE_ROM_START_ADDRESS 0x1b800
#define UCODE_SIGNATURE      0x4375434d // 'MCuC' - MC uCode
// uCode block header for reference
struct mcucodeheader {
	//uint32_t Signature;
	char8_t  Signature[4]; // CuCM ?
	uint8_t  Revision;
	uint8_t  Checksum;
	uint8_t  Reserved1;
	uint8_t  Reserved2;
	uint16_t ParametersLength;
	uint16_t UCodeLength;
	uint16_t Reserved3;
	uint16_t Reserved4;
};
/******************************************************************************/

#define ATOM_MAX_NUMBER_OF_VRAM_MODULE 16
union vram_module_channel_config {
	uint8_t  ChannelConfig;
	struct { uint8_t
		channel_combo :3-0 +1,
		channel_width :7-4 +1; // in number of 2
	};
};
union mem_preamble {
	uint8_t  Preamble;
	struct { uint8_t
		read  :3-0 +1,
		write :7-4 +1;
	};
};

/*
// ATOM_VRAM_MODULE_V3.ucNPL_RT
#define NPL_RT_MASK      0x0f
#define BATTERY_ODT_MASK 0xc0
*/
union npl_rtdelay { // board dependent parameter:NPL round trip delay, used for calculate memory timing parameters
	uint8_t  NPL_RT;
	struct { uint8_t
		npl_round_trip   :3-0 +1, // MC_SEQ_CAS_TIMING [28:24]:TCL=CL+NPL_RT-2). Always 2.
		reserved         :5-4 +1,
		battery_odt_mask :7-6 +1;
	};
};


//#define ATOM_VRAM_MODULE ATOM_VRAM_MODULE_V3
/*
#define VRAM_MODULE_V4_MISC_RANK_MASK 0x3
#define VRAM_MODULE_V4_MISC_DUAL_RANK 0x1
#define VRAM_MODULE_V4_MISC_BL_MASK   0x4
#define VRAM_MODULE_V4_MISC_BL8       0x4
#define VRAM_MODULE_V4_MISC_DUAL_CS  0x10
*/
union vrammodule_misc {
	uint8_t  Misc;
	struct { uint8_t
		dual_rank     :0-0 +1, // 0=single rank; 1=dual
		Burstlength_8 :1-1 +1, // 0=BL4; 1=BL8
		reserved1     :4-2 +1,
		dual_cs       :5-5 +1,
		reserved2     :7-6 +1;
	};
};

union cdr_bandwidth { // clock and data recovery?
	uint8_t  CDR_Bandwidth;
	struct { uint8_t
		read_bandwidth  :3-0 +1,
		write_bandwidth :7-4 +1;
	};
};

union bank_col_counts {
	uint8_t BankCol;
	struct { uint8_t
		num_columns :1-0 +1, // encoded; actual = 8+n bits
		num_banks   :3-2 +1; // encoded; actual = 2**(n+2) banks
	};
};

struct atom_vram_module_v1 {
	uint32_t Reserved;
	uint16_t EMRSValue;
	uint16_t MRSValue;
	uint16_t Reserved2;
	uint8_t  ExtMemoryID;    // An external indicator (by hardcode, callback or pin) to tell what is the current memory module
	enum atom_dgpu_vram_type MemoryType;
	union memory_vendor_id MemoryVendorID;
	enum DRAM_DENSITY_e MemoryDeviceCfg;
	uint8_t  Row;        // Number of Row,in power of 2;
	uint8_t  Column;     // Number of Column,in power of 2;
	uint8_t  Bank;       // Nunber of Bank;
	uint8_t  Rank;       // Number of Rank, in power of 2
	uint8_t  ChannelNum; // Number of channel;
	union vram_module_channel_config ChannelConfig;
	uint8_t  DefaultMVDDQ_ID; // Default MVDDQ setting for this memory block, ID linking to MVDDQ info table to find real set-up data;
	uint8_t  DefaultMVDDC_ID; // Default MVDDC setting for this memory block, ID linking to MVDDC info table to find real set-up data;
	uint8_t  Reserved3[2];
};


struct atom_vram_module_v2 {
	uint32_t Reserved;
	uint32_t Flags;       // To enable/disable functionalities based on memory type
	uint32_t EngineClock; // Override of default engine clock for particular memory type
	uint32_t MemoryClock; // Override of default memory clock for particular memory type
	uint16_t EMRS2Value;  // EMRS2 Value is used for GDDR2 and GDDR4 memory type
	uint16_t EMRS3Value;  // EMRS3 Value is used for GDDR2 and GDDR4 memory type
	uint16_t EMRSValue;
	uint16_t MRSValue;
	uint16_t Reserved2;
	uint8_t  ExtMemoryID; // An external indicator (by hardcode, callback or pin) to tell what is the current memory module
	enum atom_dgpu_vram_type MemoryType;
	union memory_vendor_id MemoryVendorID;
	enum DRAM_DENSITY_e MemoryDeviceCfg;
	uint8_t  Row;        // Number of Row in power of 2
	uint8_t  Column;     // Number of Column in power of 2
	uint8_t  Bank;       // Nunber of Bank
	uint8_t  Rank;       // Number of Rank, in power of 2
	uint8_t  ChannelNum; // Number of channel
	union vram_module_channel_config ChannelConfig;
	uint8_t  DefaultMVDDQ_ID; // Default MVDDQ setting for this memory block, ID linking to MVDDQ info table to find real set-up data;
	uint8_t  DefaultMVDDC_ID; // Default MVDDC setting for this memory block, ID linking to MVDDC info table to find real set-up data;
	uint8_t  RefreshRateFactor;
	uint8_t  Reserved3[3];
};


// TODO what types? table says ddr3 and emrs, so DDR3/GDDR4?
struct atom_memory_timing_format {
	uint32_t ClkRange; // memory clock in 10kHz unit, when target memory clock is below this clock, use this memory timing
	uint16_t MR0;
	uint16_t MR1;
	uint8_t  CL;
	uint8_t  WL;
	uint8_t  tRAS;
	uint8_t  tRC;
	uint8_t  tRFC;
	uint8_t  tRCDR;
	uint8_t  tRCDW;
	uint8_t  tRP;
	uint8_t  tRRD;
	uint8_t  tWR;
	uint8_t  tWTR;
	uint8_t  tPDIX;
	uint8_t  tFAW;
	uint8_t  tAOND;
	uint16_t MR2; // flag to control memory timing calculation. bit0= control EMRS2 Infineon
};

struct atom_memory_timing_format_v1 {
	uint32_t ClkRange; // memory clock in 10kHz unit, when target memory clock is below this clock, use this memory timing
	uint16_t MRS;      // mode register
	uint16_t EMRS;     // extended mode register
	uint8_t  CL;
	uint8_t  WL;
	uint8_t  tRAS;
	uint8_t  tRC;
	uint8_t  tRFC;
	uint8_t  tRCDR;
	uint8_t  tRCDW;
	uint8_t  tRP;
	uint8_t  tRRD;
	uint8_t  tWR;
	uint8_t  tWTR;
	uint8_t  tPDIX;
	uint8_t  tFAW;
	uint8_t  tAOND;
	uint8_t  flag; // flag to control memory timing calculation. bit0= control EMRS2 Infineon
	// GDDR parameters
	uint8_t  tCCDL;
	uint8_t  tCRCRL;
	uint8_t  tCRCWL;
	uint8_t  tCKE;
	uint8_t  tCKRSE;
	uint8_t  tCKRSX;
	uint8_t  tFAW32;
	uint16_t  MR5;
	uint8_t  Terminator;
};

struct atom_memory_timing_format_v2 {
	uint32_t ClkRange; // memory clock in 10kHz unit, when target memory clock is below this clock, use this memory timing
	uint16_t MRS;      // mode register
	uint16_t EMRS;     // extended mode register
	uint8_t  CL;
	uint8_t  WL;
	uint8_t  tRAS;
	uint8_t  tRC;
	uint8_t  tRFC;
	uint8_t  tRCDR;
	uint8_t  tRCDW;
	uint8_t  tRP;
	uint8_t  tRRD;
	uint8_t  tWR;
	uint8_t  tWTR;
	uint8_t  tPDIX;
	uint8_t  tFAW;
	uint8_t  tAOND;
	uint8_t  flag; // flag to control memory timing calculation. bit0= control EMRS2 Infineon
	// GDDR parameters
	uint8_t  tCCDL;
	uint8_t  tCRCRL;
	uint8_t  tCRCWL;
	uint8_t  tCKE;
	uint8_t  tCKRSE;
	uint8_t  tCKRSX;
	uint8_t  tFAW32;
	uint16_t  MR4;
	uint16_t  MR5;
	uint8_t  Terminator;
	uint8_t  Reserved;
};

// DDR3 and GDDR2/GDDR4?
struct atom_memory_format {
	uint32_t DllDisClock;       // memory DLL will be disable when target memory clock is below this clock
	uint16_t MR2;
	uint16_t MR3;
	enum atom_dgpu_vram_type MemoryType;
	union memory_vendor_id MemoryVendorID;
	uint8_t  Row;               // Number of Row,in power of 2;
	uint8_t  Column;            // Number of Column,in power of 2;
	uint8_t  Bank;              // Nunber of Bank;
	uint8_t  Rank;              // Number of Rank, in power of 2
	uint8_t  BurstSize;         // burst size, 0= burst size=4  1= burst size=8
	uint8_t  DllDisBit;         // position of DLL Enable/Disable bit in EMRS ( Extended Mode Register )
	uint8_t  RefreshRateFactor; // memory refresh rate in unit of ms
	enum DRAM_DENSITY_e Density;
	union mem_preamble Preamble;
	uint8_t  MemAttrib;         // Memory Device Addribute, like RDBI/WDBI etc
	struct atom_memory_timing_format MemTiming[5]; // Memory Timing block sort from lower clock to higher clock
};



struct atom_vram_module_v3 {
	uint32_t ChannelMapCfg; // board dependent paramenter:Channel combination
	uint16_t ModuleSize;    // size of ATOM_VRAM_MODULE_V3
	uint16_t DefaultMVDDQ;  // board dependent parameter:Default Memory Core Voltage
	uint16_t DefaultMVDDC;  // board dependent parameter:Default Memory IO Voltage
	uint8_t  ExtMemoryID;   // An external indicator (by hardcode, callback or pin) to tell what is the current memory module
	uint8_t  ChannelNum;    // board dependent parameter:Number of channel;
	uint8_t  ChannelSize;   // board dependent parameter:32bit or 64bit
	uint8_t  VREFI;         // board dependnt parameter: EXT or INT +160mv to -140mv
	union npl_rtdelay NPL_RT;
	uint8_t  Flag;          // To enable/disable functionalities based on memory type
	struct atom_memory_format Memory; // describe all of video memory parameters from memory spec
};


struct atom_vram_module_v4 {
	uint32_t ChannelMapCfg;   // board dependent parameter: Channel combination
	uint16_t ModuleSize;      // size of ATOM_VRAM_MODULE_V4, make it easy for VBIOS to look for next entry of VRAM_MODULE
	uint16_t PrivateReserved; // BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!! MC_ARB_RAMCFG (includes NOOFBANK,NOOFRANKS,NOOFROWS,NOOFCOLS)
	uint16_t Reserved;
	uint8_t  ExtMemoryID;     // An external indicator (by hardcode, callback or pin) to tell what is the current memory module
	enum atom_dgpu_vram_type MemoryType;
	uint8_t  ChannelNum;      // Number of channels present in this module config
	uint8_t  ChannelWidth;    // 0 - 32 bits; 1 - 64 bits
	enum DRAM_DENSITY_e Density;
	uint8_t  Flag;            // To enable/disable functionalities based on memory type
	union vrammodule_misc Misc;
	uint8_t  VREFI;           // board dependent parameter
	union npl_rtdelay NPL_RT;
	union mem_preamble Preamble;
	uint8_t  MemorySize;      // BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!! Total memory size in unit of 16MB for CONFIG_MEMSIZE - bit[23:0] zeros
	uint8_t  Reserved2[3];

// compare with V3, we flat the struct by merging ATOM_MEMORY_FORMAT (as is) into V4 as the same level
	uint16_t MR2;
	uint16_t MR3;
	union memory_vendor_id MemoryVendorID;
	uint8_t  RefreshRateFactor; // [1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)
	uint8_t  Reserved3[2];
	struct atom_memory_timing_format MemTiming[5]; // Memory Timing block sort from lower clock to higher clock
};


struct atom_vram_module_v5 {
	uint32_t ChannelMapCfg;   // board dependent parameter: Channel combination
	uint16_t ModuleSize;      // size of ATOM_VRAM_MODULE_V4, make it easy for VBIOS to look for next entry of VRAM_MODULE
	uint16_t PrivateReserved; // BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!! MC_ARB_RAMCFG (includes NOOFBANK,NOOFRANKS,NOOFROWS,NOOFCOLS)
	uint16_t Reserved;
	uint8_t  ExtMemoryID;     // An external indicator (by hardcode, callback or pin) to tell what is the current memory module
	enum atom_dgpu_vram_type MemoryType;
	uint8_t  ChannelNum;      // Number of channels present in this module config
	uint8_t  ChannelWidth;    // 0 - 32 bits; 1 - 64 bits
	enum DRAM_DENSITY_e Density;
	uint8_t  Flag;            // To enable/disable functionalities based on memory type
	union vrammodule_misc Misc;
	uint8_t  VREFI;           // board dependent parameter
	union npl_rtdelay NPL_RT;
	union mem_preamble Preamble;
	uint8_t  MemorySize;      // BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!! Total memory size in unit of 16MB for CONFIG_MEMSIZE - bit[23:0] zeros
	uint8_t  Reserved3[3];

// compare with V3, we flat the struct by merging ATOM_MEMORY_FORMAT (as is) into V4 as the same level
	uint16_t EMRS2Value;        // EMRS2 Value is used for GDDR2 and GDDR4 memory type
	uint16_t EMRS3Value;        // EMRS3 Value is used for GDDR2 and GDDR4 memory type
	union memory_vendor_id MemoryVendorID;
	uint8_t  RefreshRateFactor; // [1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)
	uint8_t  FIFODepth;         // FIFO depth supposes to be detected during vendor detection, but if we dont do vendor detection we have to hardcode FIFO Depth
	union cdr_bandwidth CDR_Bandwidth;
	struct atom_memory_timing_format_v1 MemTiming[5];// Memory Timing block sort from lower clock to higher clock
};


struct atom_vram_module_v6 {
	uint32_t ChannelMapCfg;     // board dependent parameter: Channel combination
	uint16_t ModuleSize;        // size of ATOM_VRAM_MODULE_V4, make it easy for VBIOS to look for next entry of VRAM_MODULE
	uint16_t PrivateReserved;   // BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!!
                                // MC_ARB_RAMCFG (includes NOOFBANK,NOOFRANKS,NOOFROWS,NOOFCOLS)
	uint16_t Reserved;
	uint8_t  ExtMemoryID;       // An external indicator (by hardcode, callback or pin) to tell what is the current memory module
	enum atom_dgpu_vram_type MemoryType;
	uint8_t  ChannelNum;        // Number of channels present in this module config
	uint8_t  ChannelWidth;      // 0 - 32 bits; 1 - 64 bits
	enum DRAM_DENSITY_e Density;
	uint8_t  Flag;              // To enable/disable functionalities based on memory type
	union vrammodule_misc Misc;
	uint8_t  VREFI;             // board dependent parameter
	union npl_rtdelay NPL_RT;
	union mem_preamble Preamble;
	uint8_t  MemorySize;        // BIOS internal reserved space to optimize code size, updated by the compiler, shouldn't be modified manually!! Total memory size in unit of 16MB for CONFIG_MEMSIZE - bit[23:0] zeros
	uint8_t  Reserved2[3];

// compare with V3, we flat the struct by merging ATOM_MEMORY_FORMAT (as is) into V4 as the same level
	uint16_t EMRS2Value;        // EMRS2 Value is used for GDDR2 and GDDR4 memory type
	uint16_t EMRS3Value;        // EMRS3 Value is used for GDDR2 and GDDR4 memory type
	union memory_vendor_id MemoryVendorID;
	uint8_t  RefreshRateFactor; // [1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)
	uint8_t  FIFODepth;         // FIFO depth supposes to be detected during vendor detection, but if we dont do vendor detection we have to hardcode FIFO Depth
	union cdr_bandwidth CDR_Bandwidth;
	struct atom_memory_timing_format_v2 MemTiming[5]; // Memory Timing block sort from lower clock to higher clock
};

struct atom_vram_module_v7 {
// Design Specific Values
	uint32_t ChannelMapCfg;      // mmMC_SHARED_CHREMAP
	uint16_t ModuleSize;         // Size of ATOM_VRAM_MODULE_V7
	uint16_t PrivateReserved;    // MC_ARB_RAMCFG (includes NOOFBANK,NOOFRANKS,NOOFROWS,NOOFCOLS)
	uint16_t EnableChannels;     // bit vector which indicate which channels are enabled
	uint8_t  ExtMemoryID;        // Current memory module ID
	enum atom_dgpu_vram_type MemoryType;
	uint8_t  ChannelNum;         // Number of mem. channels supported in this module
	uint8_t  ChannelWidth;       // CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT
	enum DRAM_DENSITY_e Density;
	uint8_t  Reserve;            // In MC7x, the lower 4 bits are used as bit8-11 of memory size. In other MC code, it's not used.
	union vrammodule_misc Misc;
	uint8_t  VREFI;              // Not used.
	union npl_rtdelay NPL_RT;
	union mem_preamble Preamble;
	uint8_t  MemorySize;         // Total memory size in unit of 16MB for CONFIG_MEMSIZE - bit[23:0] zeros
	uint16_t SEQSettingOffset;
	uint8_t  Reserved;
// Memory Module specific values
	uint16_t EMRS2Value;         // EMRS2/MR2 Value.
	uint16_t EMRS3Value;         // EMRS3/MR3 Value.
	union memory_vendor_id MemoryVendorID;
	uint8_t  RefreshRateFactor;  // [1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)
	uint8_t  FIFODepth;          // FIFO depth can be detected during vendor detection, here is hardcoded per memory
	union cdr_bandwidth CDR_Bandwidth;
	char8_t  strMemPNString[20]; // part number end with '0'.
};

struct atom_vram_module_v8 {
// Design Specific Values
	uint32_t ChannelMapCfg;      // mmMC_SHARED_CHREMAP
	uint16_t ModuleSize;         // Size of ATOM_VRAM_MODULE_V7
	uint16_t McRamCfg;           // MC_ARB_RAMCFG (includes NOOFBANK,NOOFRANKS,NOOFROWS,NOOFCOLS)
	uint16_t EnableChannels;     // bit vector which indicate which channels are enabled
	uint8_t  ExtMemoryID;        // Current memory module ID
	enum atom_dgpu_vram_type MemoryType;
	uint8_t  ChannelNum;         // Number of mem. channels supported in this module
	uint8_t  ChannelWidth;       // CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT
	enum DRAM_DENSITY_e Density;
	union bank_col_counts BankCol;
	union vrammodule_misc Misc;
	uint8_t  VREFI;              // Not used.
	uint16_t Reserved;           // Not used
	uint16_t MemorySize;         // Total memory size in unit of MB for CONFIG_MEMSIZE zeros
	uint8_t  McTunningSetId;     // MC phy registers set per.
	uint8_t  RowNum;
// Memory Module specific values
	uint16_t EMRS2Value;         // EMRS2/MR2 Value.
	uint16_t EMRS3Value;         // EMRS3/MR3 Value.
	union memory_vendor_id MemoryVendorID;
	uint8_t  RefreshRateFactor;  // [1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)
	uint8_t  FIFODepth;          // FIFO depth can be detected during vendor detection, here is hardcoded per memory
	union cdr_bandwidth CDR_Bandwidth;

	uint32_t ChannelMapCfg1;     // channel mapping for channel8~15
	uint32_t BankMapCfg;
	uint32_t Reserved2;
	char8_t  strMemPNString[20]; // part number end with '0'.
};


struct atom_vram_info_v1_2 {
	struct atom_common_table_header table_header;
	uint8_t  NumOfVRAMModule;
	struct atom_vram_module_v3 vram_module[ATOM_MAX_NUMBER_OF_VRAM_MODULE]; // just for allocation, real number of blocks is in ucNumOfVRAMModule;
};

struct atom_vram_info_v1_3 {
	struct atom_common_table_header table_header;
	uint16_t MemAdjustTblOffset;   // offset of ATOM_INIT_REG_BLOCK structure for memory vendor specific MC adjust setting
	uint16_t MemClkPatchTblOffset; // offset of ATOM_INIT_REG_BLOCK structure for memory clock specific MC setting
	uint16_t Reserved;
	uint8_t  aVID_PinsShift[9];    // 8 bit strap maximum+terminator
	uint8_t  NumOfVRAMModule;
	struct atom_vram_module_v3 vram_module[ATOM_MAX_NUMBER_OF_VRAM_MODULE]; // just for allocation, real number of blocks is in ucNumOfVRAMModule;
	struct atom_init_reg_block MemPatch; // for allocation

};

//#define ATOM_VRAM_INFO_LAST ATOM_VRAM_INFO_V3

union mem_dq_7_0_byte_remap { // DQ line byte remap
	uint8_t MemDQ7_0ByteRemap;
	struct { uint8_t
		byte0 :0-0 +1,
		byte1 :1-1 +1,
		byte2 :2-2 +1,
		byte3 :3-3 +1,
		byte4 :4-4 +1,
		byte5 :5-5 +1,
		byte6 :6-6 +1,
		byte7 :7-7 +1;
	};
};

union mem_dq_7_0_bit_remap {
	uint32_t MemDQ7_0BitRemap;
	struct { uint32_t
		DQ0  :2-0 +1,
		DQ1  :5-3 +1,
		DQ2  :8-6 +1,
		DQ3 :11-9 +1,
		DQ4 :14-12 +1,
		DQ5 :17-15 +1,
		DQ6 :20-18 +1,
		DQ7 :23-21 +1;
	};
};
// TODO hook up vram_info v2.3 and v2.4 to this, for atui
struct atom_dram_data_remap {
	uint8_t  ByteRemapCh0;
	uint8_t  ByteRemapCh1;
	uint32_t Byte0BitRemapCh0;
	uint32_t Byte1BitRemapCh0;
	uint32_t Byte2BitRemapCh0;
	uint32_t Byte3BitRemapCh0;
	uint32_t Byte0BitRemapCh1;
	uint32_t Byte1BitRemapCh1;
	uint32_t Byte2BitRemapCh1;
	uint32_t Byte3BitRemapCh1;
};

struct atom_vram_info_v1_4 {
	struct atom_common_table_header table_header;
	uint16_t MemAdjustTblOffset;   // offset of ATOM_INIT_REG_BLOCK structure for memory vendor specific MC adjust setting
	uint16_t MemClkPatchTblOffset; // offset of ATOM_INIT_REG_BLOCK structure for memory clock specific MC setting
	uint16_t Reserved;
	union mem_dq_7_0_byte_remap MemDQ7_0ByteRemap;
	union mem_dq_7_0_bit_remap MemDQ7_0BitRemap;
	uint8_t  Reserved2[4];
	uint8_t  NumOfVRAMModule;
	struct atom_vram_module_v4 vram_module[ATOM_MAX_NUMBER_OF_VRAM_MODULE]; // just for allocation, real number of blocks is in ucNumOfVRAMModule;
	struct atom_init_reg_block MemPatch; // for allocation
};

struct atom_vram_info_header_v2_1 {
	struct atom_common_table_header table_header;
	uint16_t MemAdjustTblOffset;   // offset of ATOM_INIT_REG_BLOCK structure for memory vendor specific MC adjust setting
	uint16_t MemClkPatchTblOffset; // offset of ATOM_INIT_REG_BLOCK structure for memory clock specific MC setting
	uint16_t PerBytePresetOffset;  // offset of ATOM_INIT_REG_BLOCK structure for Per Byte Offset Preset Settings
	uint16_t Reserved[3];
	uint8_t  NumOfVRAMModule;      // indicate number of VRAM module
	uint8_t  MemoryClkPatchTblVer; // version of memory AC timing register list
	uint8_t  VramModuleVer;        // indicate ATOM_VRAM_MODUE version
	uint8_t  Reserved2;
	struct atom_vram_module_v7 vram_module[ATOM_MAX_NUMBER_OF_VRAM_MODULE]; // just for allocation, real number of blocks is in ucNumOfVRAMModule;
};

struct atom_vram_info_header_v2_2 {
	struct atom_common_table_header table_header;
	uint16_t MemAdjustTblOffset;       // offset of ATOM_INIT_REG_BLOCK structure for memory vendor specific MC adjust setting
	uint16_t MemClkPatchTblOffset;     // offset of ATOM_INIT_REG_BLOCK structure for memory clock specific MC setting
	uint16_t McAdjustPerTileTblOffset; // offset of ATOM_INIT_REG_BLOCK structure for Per Byte Offset Preset Settings
	uint16_t McPhyInitTableOffset;     // offset of ATOM_INIT_REG_BLOCK structure for MC phy init set
	uint16_t DramDataRemapTblOffset;   // offset of ATOM_DRAM_DATA_REMAP array to indicate DRAM data lane to GPU mapping
	uint16_t Reserved1;
	uint8_t  NumOfVRAMModule;          // indicate number of VRAM module
	uint8_t  MemoryClkPatchTblVer;     // version of memory AC timing register list
	uint8_t  VramModuleVer;            // indicate ATOM_VRAM_MODUE version
	uint8_t  McPhyTileNum;             // indicate the MCD tile number which use in DramDataRemapTbl and usMcAdjustPerTileTblOffset
	struct atom_vram_module_v8 vram_module[ATOM_MAX_NUMBER_OF_VRAM_MODULE]; // just for allocation, real number of blocks is in ucNumOfVRAMModule;
};


struct atom_vram_gpio_detection_info {
	struct atom_common_table_header table_header;
	uint8_t  aVID_PinsShift[9]; // 8 bit strap maximum+terminator
};


struct atom_memory_training_info {
	struct atom_common_table_header table_header;
	uint8_t  TrainingLoop;
	uint8_t  Reserved[3];
	struct atom_init_reg_block MemTrainingSetting;
};


struct atom_memory_training_info_v3_1 {
	struct atom_common_table_header table_header;
	uint32_t MCUcodeVersion;
	uint16_t MCIOInitLen;       // len of ATOM_REG_INIT_SETTING array
	uint16_t MCUcodeLen;        // len of ATOM_MC_UCODE_DATA array
	uint16_t MCIORegInitOffset; // point of offset of ATOM_REG_INIT_SETTING array
	uint16_t MCUcodeOffset;     // point of offset of MC uCode uint32_t array.
};


struct sw_i2c_cntl_data_parameters {
	uint8_t  Control;
	uint8_t  Data;
	uint8_t  Satus;
	uint8_t  Temp;
};

#define SW_I2C_CNTL_DATA_PS_ALLOCATION  SW_I2C_CNTL_DATA_PARAMETERS

struct sw_i2c_io_data_parameters {
	uint16_t GPIO_Info;
	uint8_t  Act;
	uint8_t  Data;
	};

#define SW_I2C_IO_DATA_PS_ALLOCATION  SW_I2C_IO_DATA_PARAMETERS

/******************************************************************************/
// SW I2C CNTL DEFINITIONS
/******************************************************************************/
#define SW_I2C_IO_RESET       0
#define SW_I2C_IO_GET         1
#define SW_I2C_IO_DRIVE       2
#define SW_I2C_IO_SET         3
#define SW_I2C_IO_START       4

#define SW_I2C_IO_CLOCK       0
#define SW_I2C_IO_DATA        0x80

#define SW_I2C_IO_ZERO        0
#define SW_I2C_IO_ONE         0x100

#define SW_I2C_CNTL_READ      0
#define SW_I2C_CNTL_WRITE     1
#define SW_I2C_CNTL_START     2
#define SW_I2C_CNTL_STOP      3
#define SW_I2C_CNTL_OPEN      4
#define SW_I2C_CNTL_CLOSE     5
#define SW_I2C_CNTL_WRITE1BIT 6

/******************************************************************************/
// VESA definition Portion
/******************************************************************************/
#define VESA_OEM_PRODUCT_REV "01.00"
#define VESA_MODE_ATTRIBUTE_MODE_SUPPORT 0xBB // refer to VBE spec p.32, no TTY support
#define VESA_MODE_WIN_ATTRIBUTE 7
#define VESA_WIN_SIZE          64

struct ptr_32_bit_structure {
	uint16_t Offset16;
	uint16_t Segment16;
};

union ptr_32_bit_union {
	struct ptr_32_bit_structure egmentOffset;
	uint32_t Ptr32_Bit;
};

struct vbe_1_2_info_block_updatable {
	uint8_t  VbeSignature[4];
	uint16_t VbeVersion;
	union ptr_32_bit_union OemStringPtr;
	uint8_t  Capabilities[4];
	union ptr_32_bit_union VideoModePtr;
	uint16_t TotalMemory;
};


struct vbe_2_0_info_block_updatable {
	struct vbe_1_2_info_block_updatable CommonBlock;
	uint16_t OemSoftRev;
	union ptr_32_bit_union OemVendorNamePtr;
	union ptr_32_bit_union OemProductNamePtr;
	union ptr_32_bit_union OemProductRevPtr;
};

union vbe_version_union {
	struct vbe_2_0_info_block_updatable VBE_2_0_InfoBlock;
	struct vbe_1_2_info_block_updatable VBE_1_2_InfoBlock;
};

struct vbe_info_block {
	union vbe_version_union UpdatableVBE_Info;
	uint8_t  Reserved[222];
	uint8_t  OemData[256];
};

struct vbe_fp_info {
	uint16_t HSize;
	uint16_t VSize;
	uint16_t FPType;
	uint8_t  RedBPP;
	uint8_t  GreenBPP;
	uint8_t  BlueBPP;
	uint8_t  ReservedBPP;
	uint32_t RsvdOffScrnMemSize;
	uint32_t RsvdOffScrnMEmPtr;
	uint8_t  Reserved[14];
};

struct vesa_mode_info_block {
// Mandatory information for all VBE revisions
	uint16_t ModeAttributes;  // dw   ?   ; mode attributes
	uint8_t  WinAAttributes;  // db   ?   ; window A attributes
	uint8_t  WinBAttributes;  // db   ?   ; window B attributes
	uint16_t WinGranularity;  // dw   ?   ; window granularity
	uint16_t WinSize;         // dw   ?   ; window size
	uint16_t WinASegment;     // dw   ?   ; window A start segment
	uint16_t WinBSegment;     // dw   ?   ; window B start segment
	uint32_t WinFuncPtr;      // dd   ?   ; real mode pointer to window function
	uint16_t BytesPerScanLine;// dw   ?   ; bytes per scan line

// ; Mandatory information for VBE 1.2 and above
	uint16_t XResolution;      // dw   ?   ; horizontal resolution in pixels or characters
	uint16_t YResolution;      // dw   ?   ; vertical resolution in pixels or characters
	uint8_t  XCharSize;        // db   ?   ; character cell width in pixels
	uint8_t  YCharSize;        // db   ?   ; character cell height in pixels
	uint8_t  NumberOfPlanes;   // db   ?   ; number of memory planes
	uint8_t  BitsPerPixel;     // db   ?   ; bits per pixel
	uint8_t  NumberOfBanks;    // db   ?   ; number of banks
	uint8_t  MemoryModel;      // db   ?   ; memory model type
	uint8_t  BankSize;         // db   ?   ; bank size in KB
	uint8_t  NumberOfImagePages;// db   ?   ; number of images
	uint8_t  ReservedForPageFunction;// db   1   ; reserved for page function

// ; Direct Color fields(required for direct/6 and YUV/7 memory models)
	uint8_t  RedMaskSize;        // db   ?   ; size of direct color red mask in bits
	uint8_t  RedFieldPosition;   // db   ?   ; bit position of lsb of red mask
	uint8_t  GreenMaskSize;      // db   ?   ; size of direct color green mask in bits
	uint8_t  GreenFieldPosition; // db   ?   ; bit position of lsb of green mask
	uint8_t  BlueMaskSize;       // db   ?   ; size of direct color blue mask in bits
	uint8_t  BlueFieldPosition;  // db   ?   ; bit position of lsb of blue mask
	uint8_t  RsvdMaskSize;       // db   ?   ; size of direct color reserved mask in bits
	uint8_t  RsvdFieldPosition;  // db   ?   ; bit position of lsb of reserved mask
	uint8_t  DirectColorModeInfo;// db   ?   ; direct color mode attributes

// ; Mandatory information for VBE 2.0 and above
	uint32_t PhysBasePtr;        // dd   ?   ; physical address for flat memory frame buffer
	uint32_t Reserved_1;         // dd   0   ; reserved - always set to 0
	uint16_t Reserved_2;         // dw   0   ; reserved - always set to 0

// ; Mandatory information for VBE 3.0 and above
	uint16_t LinBytesPerScanLine;  // dw   ?   ; bytes per scan line for linear modes
	uint8_t  BnkNumberOfImagePages;// db   ?   ; number of images for banked modes
	uint8_t  LinNumberOfImagPages; // db   ?   ; number of images for linear modes
	uint8_t  LinRedMaskSize;       // db   ?   ; size of direct color red mask(linear modes)
	uint8_t  LinRedFieldPosition;  // db   ?   ; bit position of lsb of red mask(linear modes)
	uint8_t  LinGreenMaskSize;     // db   ?   ; size of direct color green mask(linear modes)
	uint8_t  LinGreenFieldPosition;// db   ?   ; bit position of lsb of green mask(linear modes)
	uint8_t  LinBlueMaskSize;      // db   ?   ; size of direct color blue mask(linear modes)
	uint8_t  LinBlueFieldPosition; // db   ?   ; bit position of lsb of blue mask(linear modes)
	uint8_t  LinRsvdMaskSize;      // db   ?   ; size of direct color reserved mask(linear modes)
	uint8_t  LinRsvdFieldPosition; // db   ?   ; bit position of lsb of reserved mask(linear modes)
	uint32_t MaxPixelClock;        // dd   ?   ; maximum pixel clock(in Hz) for graphics mode
	uint8_t  Reserved;             // db   190 dup (0)
};

// BIOS function CALLS
#define ATOM_BIOS_EXTENDED_FUNCTION_CODE        0xA0 // ATI Extended Function code
#define ATOM_BIOS_FUNCTION_COP_MODE             0x00
#define ATOM_BIOS_FUNCTION_SHORT_QUERY1         0x04
#define ATOM_BIOS_FUNCTION_SHORT_QUERY2         0x05
#define ATOM_BIOS_FUNCTION_SHORT_QUERY3         0x06
#define ATOM_BIOS_FUNCTION_GET_DDC              0x0B
#define ATOM_BIOS_FUNCTION_ASIC_DSTATE          0x0E
#define ATOM_BIOS_FUNCTION_DEBUG_PLAY           0x0F
#define ATOM_BIOS_FUNCTION_STV_STD              0x16
#define ATOM_BIOS_FUNCTION_DEVICE_DET           0x17
#define ATOM_BIOS_FUNCTION_DEVICE_SWITCH        0x18

#define ATOM_BIOS_FUNCTION_PANEL_CONTROL        0x82
#define ATOM_BIOS_FUNCTION_OLD_DEVICE_DET       0x83
#define ATOM_BIOS_FUNCTION_OLD_DEVICE_SWITCH    0x84
#define ATOM_BIOS_FUNCTION_HW_ICON              0x8A
#define ATOM_BIOS_FUNCTION_SET_CMOS             0x8B
#define SUB_FUNCTION_UPDATE_DISPLAY_INFO        0x8000 // Sub function 80
#define SUB_FUNCTION_UPDATE_EXPANSION_INFO      0x8100 // Sub function 80

#define ATOM_BIOS_FUNCTION_DISPLAY_INFO         0x8D
#define ATOM_BIOS_FUNCTION_DEVICE_ON_OFF        0x8E
#define ATOM_BIOS_FUNCTION_VIDEO_STATE          0x8F
#define ATOM_SUB_FUNCTION_GET_CRITICAL_STATE    0x0300 // Sub function 03
#define ATOM_SUB_FUNCTION_GET_LIDSTATE          0x0700 // Sub function 7
#define ATOM_SUB_FUNCTION_THERMAL_STATE_NOTICE  0x1400 // Notify caller the current thermal state
#define ATOM_SUB_FUNCTION_CRITICAL_STATE_NOTICE 0x8300 // Notify caller the current critical state
#define ATOM_SUB_FUNCTION_SET_LIDSTATE          0x8500 // Sub function 85
#define ATOM_SUB_FUNCTION_GET_REQ_DISPLAY_FROM_SBIOS_MODE 0x8900 // Sub function 89
#define ATOM_SUB_FUNCTION_INFORM_ADC_SUPPORT    0x9400 // Notify caller that ADC is supported


#define ATOM_BIOS_FUNCTION_VESA_DPMS            0x4F10 // Set DPMS
#define ATOM_SUB_FUNCTION_SET_DPMS              0x0001 // BL: Sub function 01
#define ATOM_SUB_FUNCTION_GET_DPMS              0x0002 // BL: Sub function 02
#define ATOM_PARAMETER_VESA_DPMS_ON             0x0000 // BH Parameter for DPMS ON.
#define ATOM_PARAMETER_VESA_DPMS_STANDBY        0x0100 // BH Parameter for DPMS STANDBY
#define ATOM_PARAMETER_VESA_DPMS_SUSPEND        0x0200 // BH Parameter for DPMS SUSPEND
#define ATOM_PARAMETER_VESA_DPMS_OFF            0x0400 // BH Parameter for DPMS OFF
#define ATOM_PARAMETER_VESA_DPMS_REDUCE_ON      0x0800 // BH Parameter for DPMS REDUCE ON (NOT SUPPORTED)

#define ATOM_BIOS_RETURN_CODE_MASK              0x0000FF00L
#define ATOM_BIOS_REG_HIGH_MASK                 0x0000FF00L
#define ATOM_BIOS_REG_LOW_MASK                  0x000000FFL

// structure used for VBIOS only

// DispOutInfoTable
struct asic_transmitter_info {
	uint16_t TransmitterObjId;
	uint16_t SupportDevice;
	uint8_t  TransmitterCmdTblId;
	uint8_t  Config;
	uint8_t  EncoderID;                // available 1st encoder ( default )
	uint8_t  OptionEncoderID;    // available 2nd encoder ( optional )
	uint8_t  secondEncoderID;
	uint8_t  Reserved;
};

#define ASIC_TRANSMITTER_INFO_CONFIG__DVO_SDR_MODE       0x01
#define ASIC_TRANSMITTER_INFO_CONFIG__COHERENT_MODE      0x02
#define ASIC_TRANSMITTER_INFO_CONFIG__ENCODEROBJ_ID_MASK 0xc4
#define ASIC_TRANSMITTER_INFO_CONFIG__ENCODER_A          0x00
#define ASIC_TRANSMITTER_INFO_CONFIG__ENCODER_B          0x04
#define ASIC_TRANSMITTER_INFO_CONFIG__ENCODER_C          0x40
#define ASIC_TRANSMITTER_INFO_CONFIG__ENCODER_D          0x44
#define ASIC_TRANSMITTER_INFO_CONFIG__ENCODER_E          0x80
#define ASIC_TRANSMITTER_INFO_CONFIG__ENCODER_F          0x84

struct asic_encoder_info {
	uint8_t  EncoderID;
	uint8_t  EncoderConfig;
	uint16_t EncoderCmdTblId;
};

struct atom_disp_out_info {
	struct atom_common_table_header table_header;
	uint16_t ptrTransmitterInfo;
	uint16_t ptrEncoderInfo;
	struct asic_transmitter_info TransmitterInfo[1];
	struct asic_encoder_info EncoderInfo[1];
};


struct atom_disp_out_info_v2 {
	struct atom_common_table_header table_header;
	uint16_t ptrTransmitterInfo;
	uint16_t ptrEncoderInfo;
	uint16_t ptrMainCallParserFar; // direct address of main parser call in VBIOS binary.
	struct asic_transmitter_info TransmitterInfo[1];
	struct asic_encoder_info EncoderInfo[1];
};


struct atom_disp_clock_id {
	uint8_t  PpllId;
	uint8_t  PpllAttribute;
};

// ucPpllAttribute
#define CLOCK_SOURCE_SHAREABLE            0x01
#define CLOCK_SOURCE_DP_MODE              0x02
#define CLOCK_SOURCE_NONE_DP_MODE         0x04

// DispOutInfoTable
struct asic_transmitter_info_v2 {
	uint16_t TransmitterObjId;
	uint16_t DispClkIdOffset; // point to clock source id list supported by Encoder Object
	uint8_t  TransmitterCmdTblId;
	uint8_t  Config;
	uint8_t  EncoderID; // available 1st encoder ( default )
	uint8_t  OptionEncoderID; // available 2nd encoder ( optional )
	uint8_t  secondEncoderID;
	uint8_t  Reserved;
};

struct atom_disp_out_info_v3 {
	struct atom_common_table_header table_header;
	uint16_t ptrTransmitterInfo;
	uint16_t ptrEncoderInfo;
	uint16_t ptrMainCallParserFar; // direct address of main parser call in VBIOS binary.
	uint16_t Reserved;
	uint8_t  DCERevision;
	uint8_t  MaxDispEngineNum;
	uint8_t  MaxActiveDispEngineNum;
	uint8_t  MaxPPLLNum;
	uint8_t  CoreRefClkSource; // value of CORE_REF_CLK_SOURCE
	uint8_t  DispCaps;
	uint8_t  Reserved2[2];
	struct asic_transmitter_info_v2 TransmitterInfo[1]; // for alligment only
};

// ucDispCaps
#define DISPLAY_CAPS__DP_PCLK_FROM_PPLL       0x01
#define DISPLAY_CAPS__FORCE_DISPDEV_CONNECTED 0x02

enum core_ref_clk_source {
  CLOCK_SRC_XTALIN = 0,
  CLOCK_SRC_XO_IN  = 1,
  CLOCK_SRC_XO_IN2 = 2,
};

// DispDevicePriorityInfo
struct atom_display_device_priority_info {
	struct atom_common_table_header table_header;
	uint16_t asDevicePriority[16];
};

// ProcessAuxChannelTransactionTable
struct process_aux_channel_transaction_parameters {
	uint16_t lpAuxRequest;
	uint16_t lpDataOut;
	uint8_t  ChannelID;
	union {
		uint8_t  ReplyStatus;
		uint8_t  Delay;
	};
	uint8_t  DataOutLen;
	uint8_t  Reserved;
};

// ProcessAuxChannelTransactionTable
struct process_aux_channel_transaction_parameters_v2 {
	uint16_t lpAuxRequest;
	uint16_t lpDataOut;
	uint8_t  ChannelID;
	union {
		uint8_t  ReplyStatus;
		uint8_t  Delay;
	};
	uint8_t  DataOutLen;
	uint8_t  HPD_ID; // =0: HPD1, =1: HPD2, =2: HPD3, =3: HPD4, =4: HPD5, =5: HPD6
};

#define PROCESS_AUX_CHANNEL_TRANSACTION_PS_ALLOCATION         PROCESS_AUX_CHANNEL_TRANSACTION_PARAMETERS

// GetSinkType

struct dp_encoder_service_parameters {
	uint16_t ucLinkClock;
	union {
		uint8_t  Config; // for DP training command
		uint8_t  I2cId;  // use for GET_SINK_TYPE command
	};
	uint8_t  Action;
	uint8_t  Status;
	uint8_t  LaneNum;
	uint8_t  Reserved[2];
};

// ucAction
#define ATOM_DP_ACTION_GET_SINK_TYPE 0x01

#define DP_ENCODER_SERVICE_PS_ALLOCATION WRITE_ONE_BYTE_HW_I2C_DATA_PARAMETERS


struct dp_encoder_service_parameters_v2 {
	uint16_t ExtEncoderObjId; // External Encoder Object Id, output parameter only, use when ucAction = DP_SERVICE_V2_ACTION_DET_EXT_CONNECTION
	uint8_t  AuxId;
	uint8_t  Action;
	uint8_t  SinkType; // Iput and Output parameters.
	uint8_t  HPDId;    // Input parameter, used when ucAction = DP_SERVICE_V2_ACTION_DET_EXT_CONNECTION
	uint8_t  Reserved[2];
};

struct dp_encoder_service_ps_allocation_v2 {
	struct dp_encoder_service_parameters_v2 DPServiceParam;
	struct process_aux_channel_transaction_parameters_v2 AuxParam;
};

// ucAction
#define DP_SERVICE_V2_ACTION_GET_SINK_TYPE      0x01
#define DP_SERVICE_V2_ACTION_DET_LCD_CONNECTION 0x02


// DP_TRAINING_TABLE
#define DPCD_SET_LINKRATE_LANENUM_PATTERN1_TBL_ADDR  ATOM_DP_TRAINING_TBL_ADDR
#define DPCD_SET_SS_CNTL_TBL_ADDR                   (ATOM_DP_TRAINING_TBL_ADDR + 8)
#define DPCD_SET_LANE_VSWING_PREEMP_TBL_ADDR        (ATOM_DP_TRAINING_TBL_ADDR + 16)
#define DPCD_SET_TRAINING_PATTERN0_TBL_ADDR         (ATOM_DP_TRAINING_TBL_ADDR + 24)
#define DPCD_SET_TRAINING_PATTERN2_TBL_ADDR         (ATOM_DP_TRAINING_TBL_ADDR + 32)
#define DPCD_GET_LINKRATE_LANENUM_SS_TBL_ADDR       (ATOM_DP_TRAINING_TBL_ADDR + 40)
#define DPCD_GET_LANE_STATUS_ADJUST_TBL_ADDR        (ATOM_DP_TRAINING_TBL_ADDR + 48)
#define DP_I2C_AUX_DDC_WRITE_START_TBL_ADDR         (ATOM_DP_TRAINING_TBL_ADDR + 60)
#define DP_I2C_AUX_DDC_WRITE_TBL_ADDR               (ATOM_DP_TRAINING_TBL_ADDR + 64)
#define DP_I2C_AUX_DDC_READ_START_TBL_ADDR          (ATOM_DP_TRAINING_TBL_ADDR + 72)
#define DP_I2C_AUX_DDC_READ_TBL_ADDR                (ATOM_DP_TRAINING_TBL_ADDR + 76)
#define DP_I2C_AUX_DDC_WRITE_END_TBL_ADDR           (ATOM_DP_TRAINING_TBL_ADDR + 80)
#define DP_I2C_AUX_DDC_READ_END_TBL_ADDR            (ATOM_DP_TRAINING_TBL_ADDR + 84)

/* duplicate
struct process_i2c_channel_transaction_parameters {
	uint8_t  I2CSpeed;
	union {
		uint8_t  RegIndex;
		uint8_t  Status;
	};
	uint16_t lpI2CDataOut;
	uint8_t  Flag;
	uint8_t  TransBytes;
	uint8_t  SlaveAddr;
	uint8_t  LineNumber;
#define PROCESS_I2C_CHANNEL_TRANSACTION_PS_ALLOCATION       PROCESS_I2C_CHANNEL_TRANSACTION_PARAMETERS
};
*/

// ucFlag
#define HW_I2C_WRITE   1
#define HW_I2C_READ    0
#define I2C_2BYTE_ADDR 0x02

/******************************************************************************/
// Structures used by HW_Misc_OperationTable
/******************************************************************************/
struct atom_hw_misc_operation_input_parameter_v1_1 {
	uint8_t  Cmd; // Input: To tell which action to take
	uint8_t  Reserved[3];
	uint32_t Reserved2;
};

struct atom_hw_misc_operation_output_parameter_v1_1 {
	uint8_t  ReturnCode; // Output: Return value base on action was taken
	uint8_t  Reserved[3];
	uint32_t Reserved2;
};

// Actions code
#define ATOM_GET_SDI_SUPPORT 0xF0

// Return code
#define ATOM_UNKNOWN_CMD           0
#define ATOM_FEATURE_NOT_SUPPORTED 1
#define ATOM_FEATURE_SUPPORTED     2

struct atom_hw_misc_operation_ps_allocation {
	struct atom_hw_misc_operation_input_parameter_v1_1 Input_Output;
	struct process_i2c_channel_transaction_parameters Reserved;
};

/******************************************************************************/

struct set_hwblock_instance_parameter_v2 {
	uint8_t  HWBlkInst; // HW block instance, 0, 1, 2, ...
	uint8_t  Reserved[3];
};

#define HWBLKINST_INSTANCE_MASK  0x07
#define HWBLKINST_HWBLK_MASK     0xF0
#define HWBLKINST_HWBLK_SHIFT    0x04

// ucHWBlock
#define SELECT_DISP_ENGINE       0
#define SELECT_DISP_PLL          1
#define SELECT_DCIO_UNIPHY_LINK0 2
#define SELECT_DCIO_UNIPHY_LINK1 3
#define SELECT_DCIO_IMPCAL       4
#define SELECT_DCIO_DIG          6
#define SELECT_CRTC_PIXEL_RATE   7
#define SELECT_VGA_BLK           8

// DIGTransmitterInfoTable structure used to program UNIPHY settings
struct dig_transmitter_info_header_v3_1 {
	struct atom_common_table_header table_header;
	uint16_t DPVsPreEmphSettingOffset; // offset of PHY_ANALOG_SETTING_INFO * with DP Voltage Swing and Pre-Emphasis for each Link clock
	uint16_t PhyAnalogRegListOffset;   // offset of CLOCK_CONDITION_REGESTER_INFO* with None-DP mode Analog Setting's register Info
	uint16_t PhyAnalogSettingOffset;   // offset of CLOCK_CONDITION_SETTING_ENTRY* with None-DP mode Analog Setting for each link clock range
	uint16_t PhyPllRegListOffset;      // offset of CLOCK_CONDITION_REGESTER_INFO* with Phy Pll register Info
	uint16_t PhyPllSettingOffset;      // offset of CLOCK_CONDITION_SETTING_ENTRY* with Phy Pll Settings
};

struct dig_transmitter_info_header_v3_2 {
	struct atom_common_table_header table_header;
	uint16_t DPVsPreEmphSettingOffset; // offset of PHY_ANALOG_SETTING_INFO * with DP Voltage Swing and Pre-Emphasis for each Link clock
	uint16_t PhyAnalogRegListOffset;   // offset of CLOCK_CONDITION_REGESTER_INFO* with None-DP mode Analog Setting's register Info
	uint16_t PhyAnalogSettingOffset;   // offset of CLOCK_CONDITION_SETTING_ENTRY* with None-DP mode Analog Setting for each link clock range
	uint16_t PhyPllRegListOffset;      // offset of CLOCK_CONDITION_REGESTER_INFO* with Phy Pll register Info
	uint16_t PhyPllSettingOffset;      // offset of CLOCK_CONDITION_SETTING_ENTRY* with Phy Pll Settings
	uint16_t DPSSRegListOffset;        // offset of CLOCK_CONDITION_REGESTER_INFO* with Phy SS Pll register Info
	uint16_t DPSSSettingOffset;        // offset of CLOCK_CONDITION_SETTING_ENTRY* with Phy SS Pll Settings
};


struct dig_transmitter_info_header_v3_3 {
	struct atom_common_table_header table_header;
	uint16_t DPVsPreEmphSettingOffset;    // offset of PHY_ANALOG_SETTING_INFO * with DP Voltage Swing and Pre-Emphasis for each Link clock
	uint16_t PhyAnalogRegListOffset;      // offset of CLOCK_CONDITION_REGESTER_INFO* with None-DP mode Analog Setting's register Info
	uint16_t PhyAnalogSettingOffset;      // offset of CLOCK_CONDITION_SETTING_ENTRY* with None-DP mode Analog Setting for each link clock range
	uint16_t PhyPllRegListOffset;         // offset of CLOCK_CONDITION_REGESTER_INFO* with Phy Pll register Info
	uint16_t PhyPllSettingOffset;         // offset of CLOCK_CONDITION_SETTING_ENTRY* with Phy Pll Settings
	uint16_t DPSSRegListOffset;           // offset of CLOCK_CONDITION_REGESTER_INFO* with Phy SS Pll register Info
	uint16_t DPSSSettingOffset;           // offset of CLOCK_CONDITION_SETTING_ENTRY* with Phy SS Pll Settings
	uint16_t EDPVsLegacyModeOffset;       // offset of PHY_ANALOG_SETTING_INFO * with eDP Legacy Mode Voltage Swing and Pre-Emphasis for each Link clock
	uint16_t eDPVsLowVdiffModeOffset;     // offset of PHY_ANALOG_SETTING_INFO * with eDP Low VDiff Mode Voltage Swing and Pre-Emphasis for each Link clock
	uint16_t eDPVsHighVdiffModeOffset;    // offset of PHY_ANALOG_SETTING_INFO * with eDP High VDiff Mode Voltage Swing and Pre-Emphasis for each Link clock
	uint16_t eDPVsStretchModeOffset;      // offset of PHY_ANALOG_SETTING_INFO * with eDP Stretch Mode Voltage Swing and Pre-Emphasis for each Link clock
	uint16_t eDPVsSingleVdiffModeOffset;  // offset of PHY_ANALOG_SETTING_INFO * with eDP Single Vdiff Mode Voltage Swing and Pre-Emphasis for each Link clock
	uint16_t eDPVsVariablePremModeOffset; // offset of PHY_ANALOG_SETTING_INFO * with eDP Single Vidff+Variable PreEmphasis Voltage Swing and Pre-Emphasis for each Link clock
};


struct clock_condition_regester_info {
	uint16_t RegisterIndex;
	uint8_t  StartBit;
	uint8_t  EndBit;
};

struct clock_condition_setting_entry {
	uint16_t MaxClockFreq;
	uint8_t  EncodeMode;
	uint8_t  PhySel;
	uint32_t AnalogSetting[1];
};

struct clock_condition_setting_info {
	uint16_t EntrySize;
	struct clock_condition_setting_entry ClkCondSettingEntry[1];
};

struct phy_condition_reg_val {
	uint32_t Condition;
	uint32_t RegVal;
};

struct phy_condition_reg_val_v2 {
	uint32_t Condition;
	uint8_t  Condition2;
	uint32_t RegVal;
};

struct phy_condition_reg_info {
	uint16_t RegIndex;
	uint16_t Size;
	struct phy_condition_reg_val RegVal[1];
};

struct phy_condition_reg_info_v2 {
	uint16_t RegIndex;
	uint16_t Size;
	struct phy_condition_reg_val_v2 RegVal[1];
};

struct phy_analog_setting_info {
	uint8_t  EncodeMode;
	uint8_t  PhySel;
	uint16_t Size;
	struct phy_condition_reg_info AnalogSetting[1];
};

struct phy_analog_setting_info_v2 {
	uint8_t  EncodeMode;
	uint8_t  PhySel;
	uint16_t Size;
	struct phy_condition_reg_info_v2 AnalogSetting[1];
};


struct gfx_havesting_parameters {
	uint8_t  GfxBlkId;           // GFX blk id to be harvested, like CU, RB or PRIM
	uint8_t  Reserved;           // reserved
	uint8_t  ActiveUnitNumPerSH; // requested active CU/RB/PRIM number per shader array
	uint8_t  MaxUnitNumPerSH;    // max CU/RB/PRIM number per shader array
};

// ucGfxBlkId
#define GFX_HARVESTING_CU_ID   0
#define GFX_HARVESTING_RB_ID   1
#define GFX_HARVESTING_PRIM_ID 2


struct vbios_rom_header {
	uint8_t  PciRomSignature[2];
	uint8_t  PciRomSizeIn512bytes;
	uint8_t  JumpCoreMainInitBIOS;
	uint16_t LabelCoreMainInitBIOS;
	uint8_t  PciReservedSpace[18];
	uint16_t PciDataStructureOffset;
	uint8_t  Rsvd1d_1a[4];
	char8_t  strIbm[3];
	uint8_t  CheckSum[14];
	uint8_t  BiosMsgNumber;
	char8_t  str761295520[16];
	uint16_t LabelCoreVPOSTNoMode;
	uint16_t SpecialPostOffset;
	uint8_t  SpeicalPostImageSizeIn512Bytes;
	uint8_t  Rsved47_45[3];
	uint16_t ROM_HeaderInformationTableOffset;
	uint8_t  Rsved4f_4a[6];
	char8_t  strBuildTimeStamp[20];
	uint8_t  JumpCoreXFuncFarHandler;
	uint16_t CoreXFuncFarHandlerOffset;
	uint8_t  Rsved67;
	uint8_t  JumpCoreVFuncFarHandler;
	uint16_t CoreVFuncFarHandlerOffset;
	uint8_t  Rsved6d_6b[3];
	uint16_t ATOM_BIOS_MESSAGE_Offset;
};

/******************************************************************************/
// Portion VI: Definitinos for vbios MC scratch registers that driver used
/******************************************************************************/

#define MC_MISC0__MEMORY_TYPE_MASK   0xF0000000
#define MC_MISC0__MEMORY_TYPE__GDDR1 0x10000000
#define MC_MISC0__MEMORY_TYPE__DDR2  0x20000000
#define MC_MISC0__MEMORY_TYPE__GDDR3 0x30000000
#define MC_MISC0__MEMORY_TYPE__GDDR4 0x40000000
#define MC_MISC0__MEMORY_TYPE__GDDR5 0x50000000
#define MC_MISC0__MEMORY_TYPE__HBM   0x60000000
#define MC_MISC0__MEMORY_TYPE__DDR3  0xB0000000

#define ATOM_MEM_TYPE_DDR_STRING     "DDR"
#define ATOM_MEM_TYPE_DDR2_STRING    "DDR2"
#define ATOM_MEM_TYPE_GDDR3_STRING   "GDDR3"
#define ATOM_MEM_TYPE_GDDR4_STRING   "GDDR4"
#define ATOM_MEM_TYPE_GDDR5_STRING   "GDDR5"
#define ATOM_MEM_TYPE_HBM_STRING     "HBM"
#define ATOM_MEM_TYPE_DDR3_STRING    "DDR3"

/******************************************************************************/
// Portion VII: Definitinos being oboselete
/******************************************************************************/

/******************************************************************************/
// Remove the definitions below when driver is ready!
struct atom_dac_info {
	struct atom_common_table_header table_header;
	uint16_t MaxFrequency;      // in 10kHz unit
	uint16_t Reserved;
};


struct compassionate_data {
	struct atom_common_table_header table_header;

  // DAC1 portion
	uint8_t  DAC1_BG_Adjustment;
	uint8_t  DAC1_DAC_Adjustment;
	uint16_t DAC1_FORCE_Data;
  // DAC2 portion
	uint8_t  DAC2_CRT2_BG_Adjustment;
	uint8_t  DAC2_CRT2_DAC_Adjustment;
	uint16_t DAC2_CRT2_FORCE_Data;
	uint16_t DAC2_CRT2_MUX_RegisterIndex;
	uint8_t  DAC2_CRT2_MUX_RegisterInfo; // Bit[4:0]=Bit position,Bit[7]=1:Active High;=0 Active Low
	uint8_t  DAC2_NTSC_BG_Adjustment;
	uint8_t  DAC2_NTSC_DAC_Adjustment;
	uint16_t DAC2_TV1_FORCE_Data;
	uint16_t DAC2_TV1_MUX_RegisterIndex;
	uint8_t  DAC2_TV1_MUX_RegisterInfo; // Bit[4:0]=Bit position,Bit[7]=1:Active High;=0 Active Low
	uint8_t  DAC2_CV_BG_Adjustment;
	uint8_t  DAC2_CV_DAC_Adjustment;
	uint16_t DAC2_CV_FORCE_Data;
	uint16_t DAC2_CV_MUX_RegisterIndex;
	uint8_t  DAC2_CV_MUX_RegisterInfo; // Bit[4:0]=Bit position,Bit[7]=1:Active High;=0 Active Low
	uint8_t  DAC2_PAL_BG_Adjustment;
	uint8_t  DAC2_PAL_DAC_Adjustment;
	uint16_t DAC2_TV2_FORCE_Data;
};

/******************************************************************************/
// Supported Device Info Table Definitions
/******************************************************************************/
// ucConnectInfo:
// [7:4] - connector type
// = 1   - VGA connector
// = 2   - DVI-I
// = 3   - DVI-D
// = 4   - DVI-A
// = 5   - SVIDEO
// = 6   - COMPOSITE
// = 7   - LVDS
// = 8   - DIGITAL LINK
// = 9   - SCART
// = 0xA - HDMI_type A
// = 0xB - HDMI_type B
// = 0xE - Special case1 (DVI+DIN)
// Others=TBD
// [3:0] - DAC Associated
// = 0   - no DAC
// = 1   - DACA
// = 2   - DACB
// = 3   - External DAC
// Others=TBD
//

union atom_connector_info {
	uint8_t  Access;
	struct { uint8_t
		AssociatedDAC0 :3-0 +1,
		ConnectorType  :7-4 +1;
	};
};

struct atom_connector_info_i2c {
	union atom_connector_info ConnectorInfo;
	union atom_i2c_id_config I2cId;
};


struct atom_supported_devices_info {
	struct atom_common_table_header table_header;
	uint16_t DeviceSupport;
	struct atom_connector_info_i2c ConnInfo[ATOM_MAX_SUPPORTED_DEVICE_INFO];
};

#define NO_INT_SRC_MAPPED 0xFF

struct atom_connector_inc_src_bitmap {
	uint8_t  IntSrcBitmap;
};

struct atom_supported_devices_info_2 {
	struct atom_common_table_header table_header;
	uint16_t DeviceSupport;
	struct atom_connector_info_i2c ConnInfo[ATOM_MAX_SUPPORTED_DEVICE_INFO_2];
	struct atom_connector_inc_src_bitmap IntSrcInfo[ATOM_MAX_SUPPORTED_DEVICE_INFO_2];
};

struct atom_supported_devices_info_2d1 {
	struct atom_common_table_header table_header;
	uint16_t DeviceSupport;
	struct atom_connector_info_i2c ConnInfo[ATOM_MAX_SUPPORTED_DEVICE];
	struct atom_connector_inc_src_bitmap IntSrcInfo[ATOM_MAX_SUPPORTED_DEVICE];
};

#define ATOM_SUPPORTED_DEVICES_INFO_LAST ATOM_SUPPORTED_DEVICES_INFO_2d1



struct atom_misc_control_info {
	uint16_t Frequency;
	uint8_t  PLL_ChargePump;   // PLL charge-pump gain control
	uint8_t  PLL_DutyCycle;    // PLL duty cycle control
	uint8_t  PLL_VCO_Gain;     // PLL VCO gain control
	uint8_t  PLL_VoltageSwing; // PLL driver voltage swing control
};


#define ATOM_MAX_MISC_INFO       4

struct atom_tmds_info {
	struct atom_common_table_header table_header;
	uint16_t MaxFrequency; // in 10Khz
	struct atom_misc_control_info MiscInfo[ATOM_MAX_MISC_INFO];
};


struct atom_encoder_analog_attribute {
	uint8_t  TVStandard; // Same as TV standards defined above,
	uint8_t  Padding[1];
};

struct atom_encoder_digital_attribute {
	uint8_t  Attribute; // Same as other digital encoder attributes defined above
	uint8_t  Padding[1];
};

union atom_encoder_attribute {
	struct atom_encoder_analog_attribute AlgAttrib;
	struct atom_encoder_digital_attribute DigAttrib;
};


struct dvo_encoder_control_parameters {
	uint16_t PixelClock;
	uint16_t EncoderID;
	uint8_t  DeviceType; // Use ATOM_DEVICE_xxx1_Index to indicate device type only.
	uint8_t  Action;     // ATOM_ENABLE/ATOM_DISABLE/ATOM_HPD_INIT
	union atom_encoder_attribute usDevAttr;
};

struct dvo_encoder_control_ps_allocation {
	struct dvo_encoder_control_parameters DVOEncoder;
	struct write_one_byte_hw_i2c_data_parameters Reserved; // Caller doesn't need to init this portion
};


#define ATOM_XTMDS_ASIC_SI164_ID        1
#define ATOM_XTMDS_ASIC_SI178_ID        2
#define ATOM_XTMDS_ASIC_TFP513_ID       3
#define ATOM_XTMDS_SUPPORTED_SINGLELINK 0x00000001
#define ATOM_XTMDS_SUPPORTED_DUALLINK   0x00000002
#define ATOM_XTMDS_MVPU_FPGA            0x00000004


struct atom_xtmds_info {
	struct atom_common_table_header table_header;
	uint16_t SingleLinkMaxFrequency;
	union atom_i2c_id_config I2cId; // Point the ID on which I2C is used to control external chip
	uint8_t  XtransimitterID;
	uint8_t  SupportedLink;  // Bit field, bit0=1, single link supported;bit1=1,dual link supported
	uint8_t  SequnceAlterID; // Even with the same external TMDS asic, it's possible that the program seqence alters
                             // due to design. This ID is used to alert driver that the sequence is not "standard"!
	uint8_t  MasterAddress;  // Address to control Master xTMDS Chip
	uint8_t  SlaveAddress;   // Address to control Slave xTMDS Chip
};

struct dfp_dpms_status_change_parameters {
	uint8_t  Enable; // ATOM_ENABLE=On or ATOM_DISABLE=Off
	uint8_t  Device; // ATOM_DEVICE_DFP1_INDEX....
	uint8_t  Padding[2];
};

/******************************************************************************/
// Legacy Power Play Table Definitions
/******************************************************************************/

// Definitions for ulPowerPlayMiscInfo
#define ATOM_PM_MISCINFO_SPLIT_CLOCK                     0x00000000L
#define ATOM_PM_MISCINFO_USING_MCLK_SRC                  0x00000001L
#define ATOM_PM_MISCINFO_USING_SCLK_SRC                  0x00000002L

#define ATOM_PM_MISCINFO_VOLTAGE_DROP_SUPPORT            0x00000004L
#define ATOM_PM_MISCINFO_VOLTAGE_DROP_ACTIVE_HIGH        0x00000008L

#define ATOM_PM_MISCINFO_LOAD_PERFORMANCE_EN             0x00000010L

#define ATOM_PM_MISCINFO_ENGINE_CLOCK_CONTRL_EN          0x00000020L
#define ATOM_PM_MISCINFO_MEMORY_CLOCK_CONTRL_EN          0x00000040L
#define ATOM_PM_MISCINFO_PROGRAM_VOLTAGE                 0x00000080L  // When this bit set, ucVoltageDropIndex is not an index for GPIO pin, but a voltage ID that SW needs program

#define ATOM_PM_MISCINFO_ASIC_REDUCED_SPEED_SCLK_EN      0x00000100L
#define ATOM_PM_MISCINFO_ASIC_DYNAMIC_VOLTAGE_EN         0x00000200L
#define ATOM_PM_MISCINFO_ASIC_SLEEP_MODE_EN              0x00000400L
#define ATOM_PM_MISCINFO_LOAD_BALANCE_EN                 0x00000800L
#define ATOM_PM_MISCINFO_DEFAULT_DC_STATE_ENTRY_TRUE     0x00001000L
#define ATOM_PM_MISCINFO_DEFAULT_LOW_DC_STATE_ENTRY_TRUE 0x00002000L
#define ATOM_PM_MISCINFO_LOW_LCD_REFRESH_RATE            0x00004000L

#define ATOM_PM_MISCINFO_DRIVER_DEFAULT_MODE             0x00008000L
#define ATOM_PM_MISCINFO_OVER_CLOCK_MODE                 0x00010000L
#define ATOM_PM_MISCINFO_OVER_DRIVE_MODE                 0x00020000L
#define ATOM_PM_MISCINFO_POWER_SAVING_MODE               0x00040000L
#define ATOM_PM_MISCINFO_THERMAL_DIODE_MODE              0x00080000L

#define ATOM_PM_MISCINFO_FRAME_MODULATION_MASK           0x00300000L  // 0-FM Disable, 1-2 level FM, 2-4 level FM, 3-Reserved
#define ATOM_PM_MISCINFO_FRAME_MODULATION_SHIFT          20

#define ATOM_PM_MISCINFO_DYN_CLK_3D_IDLE                 0x00400000L
#define ATOM_PM_MISCINFO_DYNAMIC_CLOCK_DIVIDER_BY_2      0x00800000L
#define ATOM_PM_MISCINFO_DYNAMIC_CLOCK_DIVIDER_BY_4      0x01000000L
#define ATOM_PM_MISCINFO_DYNAMIC_HDP_BLOCK_EN            0x02000000L  // When set, Dynamic
#define ATOM_PM_MISCINFO_DYNAMIC_MC_HOST_BLOCK_EN        0x04000000L  // When set, Dynamic
#define ATOM_PM_MISCINFO_3D_ACCELERATION_EN              0x08000000L  // When set, This mode is for acceleated 3D mode

#define ATOM_PM_MISCINFO_POWERPLAY_SETTINGS_GROUP_MASK   0x70000000L  // 1-Optimal Battery Life Group, 2-High Battery, 3-Balanced, 4-High Performance, 5- Optimal Performance (Default state with Default clocks)
#define ATOM_PM_MISCINFO_POWERPLAY_SETTINGS_GROUP_SHIFT  28
#define ATOM_PM_MISCINFO_ENABLE_BACK_BIAS                0x80000000L

#define ATOM_PM_MISCINFO2_SYSTEM_AC_LITE_MODE            0x00000001L
#define ATOM_PM_MISCINFO2_MULTI_DISPLAY_SUPPORT          0x00000002L
#define ATOM_PM_MISCINFO2_DYNAMIC_BACK_BIAS_EN           0x00000004L
#define ATOM_PM_MISCINFO2_FS3D_OVERDRIVE_INFO            0x00000008L
#define ATOM_PM_MISCINFO2_FORCEDLOWPWR_MODE              0x00000010L
#define ATOM_PM_MISCINFO2_VDDCI_DYNAMIC_VOLTAGE_EN       0x00000020L
#define ATOM_PM_MISCINFO2_VIDEO_PLAYBACK_CAPABLE         0x00000040L  // If this bit is set in multi-pp mode, then driver will pack up one with the minior power consumption.
                                                                      // If it's not set in any pp mode, driver will use its default logic to pick a pp mode in video playback
#define ATOM_PM_MISCINFO2_NOT_VALID_ON_DC                0x00000080L
#define ATOM_PM_MISCINFO2_STUTTER_MODE_EN                0x00000100L
#define ATOM_PM_MISCINFO2_UVD_SUPPORT_MODE               0x00000200L

// ucTableFormatRevision=1
// ucTableContentRevision=1
struct atom_powermode_info {
	uint32_t MiscInfo;  // The power level should be arranged in ascending order
	uint32_t Reserved1; // must set to 0
	uint32_t Reserved2; // must set to 0
	uint16_t EngineClock;
	uint16_t MemoryClock;
	uint8_t  VoltageDropIndex; // index to GPIO table
	uint8_t  SelectedPanel_RefreshRate; // panel refresh rate
	uint8_t  MinTemperature;
	uint8_t  MaxTemperature;
	uint8_t  NumPciELanes; // number of PCIE lanes
};

// ucTableFormatRevision=2
// ucTableContentRevision=1
struct atom_powermode_info_v2 {
	uint32_t MiscInfo; // The power level should be arranged in ascending order
	uint32_t MiscInfo2;
	uint32_t EngineClock;
	uint32_t MemoryClock;
	uint8_t  VoltageDropIndex; // index to GPIO table
	uint8_t  SelectedPanel_RefreshRate; // panel refresh rate
	uint8_t  MinTemperature;
	uint8_t  MaxTemperature;
	uint8_t  NumPciELanes; // number of PCIE lanes
};

// ucTableFormatRevision=2
// ucTableContentRevision=2
struct atom_powermode_info_v3 {
	uint32_t MiscInfo; // The power level should be arranged in ascending order
	uint32_t MiscInfo2;
	uint32_t EngineClock;
	uint32_t MemoryClock;
	uint8_t  VoltageDropIndex; // index to Core (VDDC) votage table
	uint8_t  SelectedPanel_RefreshRate; // panel refresh rate
	uint8_t  MinTemperature;
	uint8_t  MaxTemperature;
	uint8_t  NumPciELanes; // number of PCIE lanes
	uint8_t  VDDCI_VoltageDropIndex; // index to VDDCI votage table
};


#define ATOM_MAX_NUMBEROF_POWER_BLOCK 8

#define ATOM_PP_OVERDRIVE_INTBITMAP_AUXWIN          0x01
#define ATOM_PP_OVERDRIVE_INTBITMAP_OVERDRIVE       0x02

#define ATOM_PP_OVERDRIVE_THERMALCONTROLLER_LM63    0x01
#define ATOM_PP_OVERDRIVE_THERMALCONTROLLER_ADM1032 0x02
#define ATOM_PP_OVERDRIVE_THERMALCONTROLLER_ADM1030 0x03
#define ATOM_PP_OVERDRIVE_THERMALCONTROLLER_MUA6649 0x04
#define ATOM_PP_OVERDRIVE_THERMALCONTROLLER_LM64    0x05
#define ATOM_PP_OVERDRIVE_THERMALCONTROLLER_F75375  0x06
#define ATOM_PP_OVERDRIVE_THERMALCONTROLLER_ASC7512 0x07 // Andigilog


struct atom_powerplay_info {
	struct atom_common_table_header table_header;
	uint8_t  OverdriveThermalController;
	uint8_t  OverdriveI2cLine;
	uint8_t  OverdriveIntBitmap;
	uint8_t  OverdriveControllerAddress;
	uint8_t  SizeOfPowerModeEntry;
	uint8_t  NumOfPowerModeEntries;
	struct atom_powermode_info PowerPlayInfo[ATOM_MAX_NUMBEROF_POWER_BLOCK];
};

struct atom_powerplay_info_v2 {
	struct atom_common_table_header table_header;
	uint8_t  OverdriveThermalController;
	uint8_t  OverdriveI2cLine;
	uint8_t  OverdriveIntBitmap;
	uint8_t  OverdriveControllerAddress;
	uint8_t  SizeOfPowerModeEntry;
	uint8_t  NumOfPowerModeEntries;
	struct atom_powermode_info_v2 PowerPlayInfo[ATOM_MAX_NUMBEROF_POWER_BLOCK];
};

struct atom_powerplay_info_v3 {
	struct atom_common_table_header table_header;
	uint8_t  OverdriveThermalController;
	uint8_t  OverdriveI2cLine;
	uint8_t  OverdriveIntBitmap;
	uint8_t  OverdriveControllerAddress;
	uint8_t  SizeOfPowerModeEntry;
	uint8_t  NumOfPowerModeEntries;
	struct atom_powermode_info_v3 PowerPlayInfo[ATOM_MAX_NUMBEROF_POWER_BLOCK];
};



/******************************************************************************/


// Following definitions are for compatiblity issue in different SW components.
#define ATOM_MASTER_DATA_TABLE_REVISION   0x01
#define Object_Info                       Object_Header
#define AdjustARB_SEQ                     MC_InitParameter
#define VRAM_GPIO_DetectionInfo           VoltageObjectInfo
#define ASIC_VDDCI_Info                   ASIC_ProfilingInfo
#define ASIC_MVDDQ_Info                   MemoryTrainingInfo
#define SS_Info                           PPLL_SS_Info
#define ASIC_MVDDC_Info                   ASIC_InternalSS_Info
#define DispDevicePriorityInfo            SaveRestoreInfo
#define DispOutInfo                       TV_VideoMode


#define ATOM_ENCODER_OBJECT_TABLE         ATOM_OBJECT_TABLE
#define ATOM_CONNECTOR_OBJECT_TABLE       ATOM_OBJECT_TABLE

// New device naming, remove them when both DAL/VBIOS is ready
#define DFP2I_OUTPUT_CONTROL_PARAMETERS    CRT1_OUTPUT_CONTROL_PARAMETERS
#define DFP2I_OUTPUT_CONTROL_PS_ALLOCATION DFP2I_OUTPUT_CONTROL_PARAMETERS

#define DFP1X_OUTPUT_CONTROL_PARAMETERS    CRT1_OUTPUT_CONTROL_PARAMETERS
#define DFP1X_OUTPUT_CONTROL_PS_ALLOCATION DFP1X_OUTPUT_CONTROL_PARAMETERS

#define DFP1I_OUTPUT_CONTROL_PARAMETERS    DFP1_OUTPUT_CONTROL_PARAMETERS
#define DFP1I_OUTPUT_CONTROL_PS_ALLOCATION DFP1_OUTPUT_CONTROL_PS_ALLOCATION

#define ATOM_DEVICE_DFP1I_SUPPORT          ATOM_DEVICE_DFP1_SUPPORT
#define ATOM_DEVICE_DFP1X_SUPPORT          ATOM_DEVICE_DFP2_SUPPORT

#define ATOM_DEVICE_DFP1I_INDEX            ATOM_DEVICE_DFP1_INDEX
#define ATOM_DEVICE_DFP1X_INDEX            ATOM_DEVICE_DFP2_INDEX

#define ATOM_DEVICE_DFP2I_INDEX            0x00000009
#define ATOM_DEVICE_DFP2I_SUPPORT          (0x1L << ATOM_DEVICE_DFP2I_INDEX)

#define ATOM_S0_DFP1I                      ATOM_S0_DFP1
#define ATOM_S0_DFP1X                      ATOM_S0_DFP2

#define ATOM_S0_DFP2I                      0x00200000L
#define ATOM_S0_DFP2Ib2                    0x20

#define ATOM_S2_DFP1I_DPMS_STATE           ATOM_S2_DFP1_DPMS_STATE
#define ATOM_S2_DFP1X_DPMS_STATE           ATOM_S2_DFP2_DPMS_STATE

#define ATOM_S2_DFP2I_DPMS_STATE           0x02000000L
#define ATOM_S2_DFP2I_DPMS_STATEb3         0x02

#define ATOM_S3_DFP2I_ACTIVEb1             0x02

#define ATOM_S3_DFP1I_ACTIVE               ATOM_S3_DFP1_ACTIVE
#define ATOM_S3_DFP1X_ACTIVE               ATOM_S3_DFP2_ACTIVE

#define ATOM_S3_DFP2I_ACTIVE               0x00000200L

#define ATOM_S3_DFP1I_CRTC_ACTIVE          ATOM_S3_DFP1_CRTC_ACTIVE
#define ATOM_S3_DFP1X_CRTC_ACTIVE          ATOM_S3_DFP2_CRTC_ACTIVE
#define ATOM_S3_DFP2I_CRTC_ACTIVE          0x02000000L


#define ATOM_S3_DFP2I_CRTC_ACTIVEb3        0x02
#define ATOM_S5_DOS_REQ_DFP2Ib1            0x02

#define ATOM_S5_DOS_REQ_DFP2I              0x0200
#define ATOM_S6_ACC_REQ_DFP1I              ATOM_S6_ACC_REQ_DFP1
#define ATOM_S6_ACC_REQ_DFP1X              ATOM_S6_ACC_REQ_DFP2

#define ATOM_S6_ACC_REQ_DFP2Ib3            0x02
#define ATOM_S6_ACC_REQ_DFP2I              0x02000000L

#define TMDS1XEncoderControl               DVOEncoderControl
#define DFP1XOutputControl                 DVOOutputControl

#define ExternalDFPOutputControl           DFP1XOutputControl
#define EnableExternalTMDS_Encoder         TMDS1XEncoderControl

#define DFP1IOutputControl                 TMDSAOutputControl
#define DFP2IOutputControl                 LVTMAOutputControl

#define DAC1_ENCODER_CONTROL_PARAMETERS    DAC_ENCODER_CONTROL_PARAMETERS
#define DAC1_ENCODER_CONTROL_PS_ALLOCATION DAC_ENCODER_CONTROL_PS_ALLOCATION

#define DAC2_ENCODER_CONTROL_PARAMETERS    DAC_ENCODER_CONTROL_PARAMETERS
#define DAC2_ENCODER_CONTROL_PS_ALLOCATION DAC_ENCODER_CONTROL_PS_ALLOCATION

#define ucDac1Standard  ucDacStandard
#define ucDac2Standard  ucDacStandard

#define TMDS1EncoderControl TMDSAEncoderControl
#define TMDS2EncoderControl LVTMAEncoderControl

#define DFP1OutputControl TMDSAOutputControl
#define DFP2OutputControl LVTMAOutputControl
#define CRT1OutputControl DAC1OutputControl
#define CRT2OutputControl DAC2OutputControl

// These two lines will be removed for sure in a few days, will follow up with Michael V.
#define EnableLVDS_SS   EnableSpreadSpectrumOnPPLL
#define ENABLE_LVDS_SS_PARAMETERS_V3  ENABLE_SPREAD_SPECTRUM_ON_PPLL

#define ATOM_S2_CRT1_DPMS_STATE 0x00010000L
#define ATOM_S2_LCD1_DPMS_STATE ATOM_S2_CRT1_DPMS_STATE
#define ATOM_S2_TV1_DPMS_STATE  ATOM_S2_CRT1_DPMS_STATE
#define ATOM_S2_DFP1_DPMS_STATE ATOM_S2_CRT1_DPMS_STATE
#define ATOM_S2_CRT2_DPMS_STATE ATOM_S2_CRT1_DPMS_STATE

#define ATOM_S6_ACC_REQ_TV2     0x00400000L
#define ATOM_DEVICE_TV2_INDEX   0x00000006
#define ATOM_DEVICE_TV2_SUPPORT (0x1L << ATOM_DEVICE_TV2_INDEX)
#define ATOM_S0_TV2             0x00100000L
#define ATOM_S3_TV2_ACTIVE      ATOM_S3_DFP6_ACTIVE
#define ATOM_S3_TV2_CRTC_ACTIVE ATOM_S3_DFP6_CRTC_ACTIVE

/*********************************************************************************/


struct atom_hole_info {
	uint16_t Offset; // offset of the hole ( from the start of the binary )
	uint16_t Length; // length of the hole ( in bytes )
};

struct atom_service_description {
	uint8_t  Revision;  // Holes set revision
	uint8_t  Algorithm; // Hash algorithm
	uint8_t  SignatureType;	// Signature type ( 0 - no signature, 1 - test, 2 - production )
	uint8_t  Reserved;
	uint16_t SigOffset;	// Signature offset ( from the start of the binary )
	uint16_t SigLength; // Signature length
};


struct atom_service_info {
	struct atom_common_table_header table_header;
	struct atom_service_description Descr;
	uint8_t  holesNo; // number of holes that follow
	struct atom_hole_info holes[1]; // array of hole descriptions
};

//
// AMD ACPI Table
//

/* duplicate
struct amd_acpi_description_header {
	uint32_t Signature;
	uint32_t TableLength; // Length
	uint8_t  Revision;
	uint8_t  Checksum;
	uint8_t  OemId[6];
	uint64_t OemTableId; // uint8_t  OemTableId[8];
	uint32_t OemRevision;
	uint32_t CreatorId;
	uint32_t CreatorRevision;
};
*/
/*
// EFI_ACPI_DESCRIPTION_HEADER from AcpiCommon.h
struct efi_acpi_description_header {
	uint32_t Signature;       // 0x0
	uint32_t Length;          // 0x4
	uint8_t  Revision;        // 0x8
	uint8_t  Checksum;        // 0x9
	uint8_t  OemId[6];        // 0xA
	uint64_t OemTableId;      // 0x10
	uint32_t OemRevision;     // 0x18
	uint32_t CreatorId;       // 0x1C
	uint32_t CreatorRevision; // 0x20
};
*/
/* duplicate
struct uefi_acpi_vfct {
	struct amd_acpi_description_header Header;
	uint8_t  TableUUID[16];    // 0x24
	uint32_t VBIOSImageOffset; // 0x34. Offset to the first GOP_VBIOS_CONTENT block from the beginning of the stucture.
	uint32_t Lib1ImageOffset;  // 0x38. Offset to the first GOP_LIB1_CONTENT block from the beginning of the stucture.
	uint32_t Reserved[4];      // 0x3C
};

struct vfct_image_header {
	uint32_t PCIBus;      // 0x4C
	uint32_t PCIDevice;   // 0x50
	uint32_t PCIFunction; // 0x54
	uint16_t VendorID;    // 0x58
	uint16_t DeviceID;    // 0x5A
	uint16_t SSVID;       // 0x5C
	uint16_t SSID;        // 0x5E
	uint32_t Revision;    // 0x60
	uint32_t ImageLength; // 0x64
};

struct gop_vbios_content {
	struct vfct_image_header VbiosHeader;
	uint8_t  VbiosContent[];
};

struct gop_lib1_content {
	struct vfct_image_header Lib1Header;
	uint8_t  Lib1Content[1];
};
*/

#pragma pack(pop) // restore old packing

#endif /* _ATOMBIOS_H */
