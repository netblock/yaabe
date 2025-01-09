// see coreboot's amdfwtool for other PSP stuff.
// https://github.com/coreboot/coreboot/blob/c421ed6f819ac3140176a0c347d7fa6778465f9a/util/amdfwtool/

#ifndef PSP_H
#define PSP_H
#pragma pack(push, 1) // bios data must use byte alignment

#define MAX_PSP_ENTRIES 0xFF
union psp_directory_additional_info {
	uint32_t additional_info;
	struct { uint32_t
		dir_size        :9-0 +1,
		spi_block_size :13-10 +1,
		base_addr      :28-14 +1,
		address_mode   :30-29 +1,
		not_used       :31-31 +1;
	};
};
// Define structure for PSP directory
//         little-endian: 3 2 1 0
//                        P S P $
#define PSP_COOKIE     0x50535024
#define PSP_COOKIE_STR "$PSP"
struct psp_directory_header {
	union magic_32 pspcookie; // $PSP
	uint32_t checksum; // 32 bit CRC of header items below and the entire table
	uint32_t totalentries;
	union psp_directory_additional_info additional_info;
};

enum psp_entry_type:uint8_t {
	AMD_PUBLIC_KEY               = 0, // AMD public key
	PSP_FW_BOOT_LOADER           = 1, // PSP boot loader in SPI space
	PSP_FW_TRUSTED_OS            = 2, // PSP Firmware region in SPI space
	PSP_FW_RECOVERY_BOOT_LOADER  = 3, // PSP recovery region.
	PSP_NV_DATA                  = 4, // PSP data region in SPI space
	BIOS_PUBLIC_KEY              = 5, // BIOS public key stored in SPI space
	BIOS_RTM_FIRMWARE            = 6, // BIOS RTM code (PEI volume) in SPI space
	BIOS_RTM_SIGNATURE           = 7, // signed BIOS RTM hash stored  in SPI space
	SMU_OFFCHIP_FW               = 8, // SMU image
	PSP_AMD_SECURE_DEBUG_KEY     = 9, // AMD Secure Debug key
	PSP_SECURE_OS_SIGNING_KEY   = 10, // PSP Secure OS OEM signing key
	AMD_SOFT_FUSE_CHAIN_01      = 11, // 64bit PSP Soft Fuse Chain
	PSP_BOOT_TIME_TRUSTLETS     = 12, // boot-loaded trustlet binaries
	PSP_BOOT_TIME_TRUSTLETS_KEY = 13, // key of the boot-loaded trustlet binaries

	AMD_FW_PSP_SMU_FIRMWARE2    = 18,
	AMD_DEBUG_UNLOCK            = 19,

	AMD_BOOT_DRIVER             = 27,
	AMD_SOC_DRIVER              = 28,
	AMD_DEBUG_DRIVER            = 29,
	AMD_INTERFACE_DRIVER        = 31,
	AMD_HW_IPCFG                = 32,
	AMD_WRAPPED_IKEK            = 33,
	AMD_TOKEN_UNLOCK            = 34,
	AMD_SEC_GASKET              = 36,

	AMD_MP2_FW                  = 37,

	AMD_DRIVER_ENTRIES          = 40,
	AMD_FW_KVM_IMAGE            = 41,
	AMD_FW_MP5                  = 42,

	AMD_S0I3_DRIVER             = 45,

	AMD_ABL0                    = 48,
	AMD_ABL1                    = 49,
	AMD_ABL2                    = 50,
	AMD_ABL3                    = 51,
	AMD_ABL4                    = 52,
	AMD_ABL5                    = 53,
	AMD_ABL6                    = 54,
	AMD_ABL7                    = 55,
	AMD_SEV_DATA                = 56,
	AMD_SEV_CODE                = 57,
	AMD_FW_PSP_WHITELIST        = 58,

	AMD_VBIOS_BTLOADER          = 60,

	AMD_FW_L2_PTR               = 64,

	AMD_FW_DXIO                 = 66,

	AMD_FW_USB_PHY              = 68,
	AMD_FW_TOS_SEC_POLICY       = 69,

	AMD_FW_DRTM_TA              = 71,
	AMD_FW_RECOVERYAB_A         = 72,
	AMD_FW_BIOS_TABLE           = 73,
	AMD_FW_RECOVERYAB_B         = 74,

	AMD_FW_KEYDB_BL             = 80,
	AMD_FW_KEYDB_TOS            = 81,
	AMD_FW_PSP_VERSTAGE         = 82,
	AMD_FW_VERSTAGE_SIG         = 83,
	AMD_RPMC_NVRAM              = 84,
	AMD_FW_SPL                  = 85,

	AMD_FW_DMCU_ERAM            = 88,
	AMD_FW_DMCU_ISR             = 89,
	AMD_FW_MSMU                 = 90,

	AMD_FW_SPIROM_CFG           = 92,
	AMD_FW_MPIO                 = 93,

	AMD_FW_TPMLITE              = 95, // family 17h & 19h
	AMD_FW_PSP_SMUSCS           = 95, // family 15h & 16h

	AMD_FW_DMCUB               = 113,

	AMD_FW_PSP_BOOTLOADER_AB   = 115,

	AMD_RIB                    = 118,
	AMD_FW_AMF_SRAM            = 133,

	AMD_FW_AMF_DRAM            = 134,

	AMD_FW_AMF_WLAN            = 136,
	AMD_FW_AMF_MFD             = 137,

	AMD_FW_MPDMA_TF            = 140,
	AMD_TA_IKEK                = 141,

	AMD_FW_MPCCX               = 144,
	AMD_FW_GMI3_PHY            = 145,
	AMD_FW_MPDMA_PM            = 146,
	AMD_FW_LSDMA               = 148,
	AMD_FW_C20_MP              = 149,

	AMD_FW_FCFG_TABLE          = 152,

	AMD_FW_MINIMSMU            = 154,

	AMD_FW_SRAM_FW_EXT         = 157,

	AMD_FW_UMSMU               = 162,
/*
	AMD_FW_IMC                 = 512, // Large enough to be larger than the top BHD entry type.
	AMD_FW_GEC,
	AMD_FW_XHCI,
	AMD_FW_INVALID,	// Real last one to detect the last entry in table.
	AMD_FW_SKIP    // This is for non-applicable options.
*/
};

// Structure for PSP Entry
union psp_directory_entry_extra {
	uint16_t extra;
	struct { uint16_t
		rom_id   :1-0 +1,
		writable :2-2 +1,
		inst     :6-3 +1,
		rsvd_1  :15-7 +1;
	};
};

// TODO no clue where "partition offset" is relative to.
// Seems per-entry ad-hoc since directory entries offset+size overlap.
union psp_directory_entry_address {
	uint64_t location;
	struct { uint64_t
		address :61-0 +1,
		mode    :63-62 +1; // 0=physical address; 1=bios offset; 2=dir header offset; 3=partition offset
	};
};
struct psp_directory_entry {
	enum psp_entry_type type;
	uint8_t subprog;
	union psp_directory_entry_extra extra;
	uint32_t size;     // Size of PSP Entry in bytes
	union psp_directory_entry_address address;
};

// Structure for PSP directory
struct psp_directory {
	struct psp_directory_header  header;
	struct psp_directory_entry   pspentry[] __counted_by(header.totalentries); // Array of PSP entries each pointing to a binary in SPI flash
};

//            little-endian: 3 2 1 0
//                           1 S P $
#define PS1_SIGNATURE     0x31535024
#define PS1_SIGNATURE_STR "$PS1"
struct amd_fw_header {
	uint8_t  reserved_0[16];
	union magic_32 signature;
	uint32_t fw_size_signed;
	uint8_t  reserved_18[24];
	uint32_t sig_opt; // 1 if the image is signed, 0 otherwise
	uint32_t sig_id;
	uint8_t  sig_param[16];
	uint32_t comp_opt;
	uint8_t  reserved_4c[4];
	uint32_t uncomp_size;
	uint32_t comp_size;
	uint16_t fw_id;
	uint8_t  reserved_5a[6];
	uint8_t  version[4];
	uint8_t  reserved_64[8];
	uint32_t size_total;
	uint8_t  reserved_70[12];
	enum psp_entry_type fw_type; // Starting MDN fw_id is populated instead of fw_type. fw_type will still be around for backwards compatibility.
	uint8_t  fw_subtype;
	uint8_t  fw_subprog;
	uint8_t  reserved_7f;
	uint8_t  reserved_80[128];
};

// TODO some Navi3/7900XT bioses from TPU, especially the 2MiB ones, have this
// psp struct embedded_firmware at the beginning
#define FIRMWARE_TABLE_SIGNATURE  0x55AA55AA
#define EFS_SECOND_GEN 0
#define EFS_BEFORE_SECOND_GEN 1
struct second_gen_efs { /* todo: expand for Server products */
	uint32_t gen:1; /* Client products only use bit 0 */
	uint32_t reserved:31;
};
struct embedded_firmware {
	uint32_t signature; /* 0x55aa55aa */
	uint32_t imc_entry;
	uint32_t gec_entry;
	uint32_t xhci_entry;
	uint32_t psp_directory;
	uint32_t new_psp_directory; /* also used as combo_psp_directory */
	uint32_t bios0_entry; /* todo: add way to select correct entry */
	uint32_t bios1_entry;
	uint32_t bios2_entry;
	struct second_gen_efs efs_gen;
	uint32_t bios3_entry;
	uint32_t psp_bak_directory;
	uint32_t promontory_fw_ptr;
	uint32_t lp_promontory_fw_ptr;
	uint32_t reserved_38h;
	uint32_t reserved_3Ch;
	uint8_t spi_readmode_f15_mod_60_6f;
	uint8_t fast_speed_new_f15_mod_60_6f;
	uint8_t reserved_42h;
	uint8_t spi_readmode_f17_mod_00_2f;
	uint8_t spi_fastspeed_f17_mod_00_2f;
	uint8_t qpr_dummy_cycle_f17_mod_00_2f;
	uint8_t reserved_46h;
	uint8_t spi_readmode_f17_mod_30_3f;
	uint8_t spi_fastspeed_f17_mod_30_3f;
	uint8_t micron_detect_f17_mod_30_3f;
	uint8_t reserved_4Ah;
	uint8_t reserved_4Bh;
	uint32_t reserved_4Ch;
} __attribute__((aligned(16)));

#pragma pack(pop)
#endif
