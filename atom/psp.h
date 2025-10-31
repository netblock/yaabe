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

enum psp_rsa_key_usage:uint32_t {
	PSP_RSA_AMD_ROOT = 0, // sign PSP bootloader, PSP FW, SMU FW
	PSP_RSA_BIOS     = 1,
	PSP_RSA_PSP_FW   = 2, // both AMD and OEM
	PSP_RSA_SEV     = 19,
};
struct psp_rsa_key_header {
	uint32_t version;
	uint8_t this_key_id[16];
	uint8_t certifying_key_id[16];
	enum psp_rsa_key_usage usage;
	uint8_t reserved[16];
	uint32_t public_exponent_size; // bits
	uint32_t modulus_size; // bits
};
struct psp_rsa_key_2048 {
	struct psp_rsa_key_header header;
	uint8_t public_exponent[256]; // 0x010001
	uint8_t modulus[256];
};
struct psp_rsa_key_4096 {
	struct psp_rsa_key_header header;
	uint8_t public_exponent[512]; // 0x010001
	uint8_t modulus[512];
};



/*
psp-bios mailbox stuff for x86
see also:
coreboot/src/soc/amd/common/block/{psp/psp_def.h,include/amdblocks/psp.h}

Uses TPM command/response buffer interface?
https://learn.microsoft.com/en-us/windows-hardware/test/hlk/testref/trusted-execution-environment-acpi-profile
https://trustedcomputinggroup.org/wp-content/uploads/Mobile-Command-Response-Buffer-Interface-v2-r12-Specification_FINAL2.pdf

C2PMSG 0~31 4 byte MMIO registers
bios-to-psp is at the tail; 28~31
psp-to-bios PSPSMMDataRegion
*/

struct tpm2_control_area {
	uint32_t request; // Used to control power state transition.
	uint32_t error;
	uint32_t cancel; // SET by the DRIVER to abort command processing
	uint32_t start; // SET by the DRIVER to indicate that a command is available for processing.
	uint64_t interrupt_control; // Reserved. (MUST be zero.)
	uint32_t cmd_size;
	uint64_t cmd_addr; // This field contains the physical address of the command buffer. Note that the actual command buffer (not the physical address of command buffer) is in big-endian format as mandated by TCG.
	uint32_t resp_size;
	uint64_t resp_addr; // This field contains the physical address of the response buffer. Note that the actual response buffer (not the physical address of response buffer) is in big-endian format as mandated by TCG.
};

struct c2pmsg0_15 {
	uint64_t interface_identifier;
	struct tpm2_control_area control;
	uint32_t cmd_resp_hw_buffer;
};

enum psp_fw_status:uint32_t {
	BL_ERROR_INVALID_BOOTMODE          = 0x01, // consult with AMD FCH/PSP team
	BL_ERROR_INVALID_APERCONFIG        = 0x02, // consult with AMD PSP FW team
	BL_ERROR_SMUFW                     = 0x03, // Preclusion check if SMU FW content/signature is corrupted or correctly placed in BIOS
	BL_ERROR_OEMSIGNING                = 0x04, // Preclusion check if OEM signing key content/signature is corrupted or correctly placed in BIOS
	BL_ERROR_BIOS_PEI                  = 0x05, // Preclusion check if BIOS PEI volume or PSP directory table content/signature is corrupted or correctly placed in BIOS
	BL_ERROR_SECUREOS                  = 0x06, // Preclusion check if PSP SecureOS content/signature is corrupted or correctly placed in BIOS
	BL_ERROR_LOAD_SMUFW                = 0x07, // Can not locate SMU FW in PSP directory table, preclusion check the PSP directory table.
	BL_ERROR_LOAD_OEMSIGNING           = 0x08, // Can not locate OEM SINGING KEY in PSP directory table, preclusion check the PSP directory table.
	BL_ERROR_LOAD_BIOS_PEI             = 0x09, // Can not locate BIOS PEI in PSP directory table, preclusion check the PSP directory table.
	BL_ERROR_LOAD_TRUSLETKEY           = 0x0a, // Can not locate Truslet key in PSP directory table, preclusion check the PSP directory table.
	BL_ERROR_LOAD_SECUREOS             = 0x0b, // Can not locate SECURE OS in PSP directory table, preclusion check the PSP directory table.
	BL_ERROR_INVALID_PSP_DIRENTRY      = 0x0c, // invalid PSP directory entry, preclusion  check the PSP directory table.
	BL_ERROR_RELEASE_BSPCORE_FAIL      = 0x0d, // Fail to release the BSP Core/x86 - consult  with AMD PSP FW team
	BL_ERROR_RETURNED_FROM_OS          = 0x0e, // Control is not returned from secure OS, abnormal status - consult with AMD PSP FW team
	BL_ERROR_LOAD_RESTOREVEC_FAIL      = 0x0f, // Preclusion check if SPI-ROM S3 datablob  content/signature is corrupted in SPI-ROM
	BL_ERROR_RESTORE_SECUREBOOT_REG    = 0x10, // Only available for A0, consult with AMD  FCH/PSP team
	BL_ERROR_S0I3_STEPS_FAIL           = 0x11, // consult with AMD FCH/PSP team

	BL_SUCCESS_C_MAIN                  = 0x40, // Entered Boot Loader
	BL_SUCCESS_CONFIG_FCHSB            = 0x41, // configured FCH/SB
	BL_SUCCESS_BOOTMODE_S4S5           = 0x42, // entered S4/S5 bootmode
	BL_SUCCESS_COLD_CRYPTO_POINTER     = 0x43, // passed function pointers from Boot Rom
	BL_SUCCESS_COLD_LOAD_SMUFW         = 0x44, // loaded SMU FW
	BL_SUCCESS_COLD_VERIFY_SMUFW       = 0x45, // verified SMU FW
	BL_SUCCESS_COLD_LOAD_OEM_KEY       = 0x46, // loaded OEM Signing Key
	BL_SUCCESS_COLD_VERIFY_OEM_KEY     = 0x47, // verified OEM Signing Key
	BL_SUCCESS_COLD_LOAD_BIOS_PEI      = 0x48, // loaded BIOS PEI segment
	BL_SUCCESS_COLD_VERIFY_BIOS_PSPDIR = 0x49, // verified BIOS PEI segment and PSP  directory table
	BL_SUCCESS_COLD_RELEASE_BSPCORE    = 0x4a, // released BSPCORE
	BL_SUCCESS_COLD_LOAD_TRUSTLETKEY   = 0x4b, // loaded Truslet Key
	BL_SUCCESS_COLD_VERIFY_TRUSTLETKEY = 0x4c, // verified Truslet Key and hash the Truslet  Key
	BL_SUCCESS_COLD_LOAD_SECURE_OS     = 0x4d, // loaded secure OS
	BL_SUCCESS_COLD_VERIFY_SECURE_OS   = 0x4e, // verified secure OS
	BL_SUCCESS_COLD_MB_BL_SECURE_OS    = 0x4f, // set up Bootloader-to-SecureOS mailbox
	BL_SUCCESS_COLD_TRANSFER_SECURE_OS = 0x50, // Bootloader transfer control to secure OS
	BL_SUCCESS_BOOTMODE_S3S0I3         = 0x51, // entered S3/S0i3 bootmode - Warm Boot
	BL_SUCCESS_WARM_CRYPTO_POINTER     = 0x52, // passed function pointers - Warm Boot
	BL_SUCCESS_WARM_LOAD_RESTORE       = 0x53, // loaded DRAM restore data - Warm  Boot
	BL_SUCCESS_WARM_VERIFY_RESTORE     = 0x54, // verified DRAM restore data - Warm  Boot
	BL_SUCCESS_WARM_AGESA_RESTORE      = 0x55, // restored DRAM access - Warm Boot
	BL_SUCCESS_WARM_SETS3EXIT_BIT      = 0x56, // set the S3 Exit Bit
	BL_SUCCESS_WARM_RELEASE_BSPCORE    = 0x57, // released BSPCORE - Warm Boot
	BL_SUCCESS_WARM_S0I3_STEP_DONE     = 0x58, // executed S0i3 steps on resume - Warm  Boot
	BL_SUCCESS_WARM_LOAD_SECURE_OS     = 0x59, // unused
	BL_SUCCESS_WARM_VERIFY_SECURE_OS   = 0x5a, // verified secure OS - Warm Boot
	BL_SUCCESS_WARM_MB_BL_SECURE_OS    = 0x5b, // set up Bootloader-to-SecureOS mailbox  - Warm Boot
	BL_SUCCESS_WARM_MB_SRAMHMAC_PASS   = 0x5c, // successfully verified the signature of  SRAM - Warm Boot
	BL_SUCCESS_WARM_MB_TRANSFER2OS     = 0x5d, // successfully transferred control to  Secure OS - Warm Boot
	BL_ERROR_WARM_MB_SRAMHMAC_FAIL     = 0x5e, // failed validation of SRAM signature -  Warm Boot
};

enum sos_progress_codes:uint32_t {
	SOS_PROGRESS_ENTERED_OS       = 0x01,
	SOS_PROGRESS_CC6              = 0x02, // Successfully initialized access to CC6 buffers (if stuck at previous code, check CC6 configuration)
	SOS_PROGRESS_NEXT_STEP_OS     = 0x03, // Next step in OS init process (contact PSP FW team)
	SOS_PROGRESS_INTERNAL_STRUCTS = 0x04, // Initialized internal data structures and mailbox buffers
	SOS_PROGRESS_SWD_AND_NOTIFY   = 0x05, // Initialized Swd part of the OS and started notification handler thread
	SOS_PROGRESS_SYS_TRUSTLETS    = 0x06, // Loaded and initialized System Trustlets (if stuck at previous code, check Trustlet binary in SPI ROM)
	SOS_PROGRESS_FINISHED         = 0x07, // Finished Secure OS initialization, entered steady state
	SOS_PROGRESS_S3               = 0x20, // Secure OS Entered S3 suspend
	SOS_PROGRESS_IDLE_S3          = 0x21, // Secure OS entered idle state before suspend
	SOS_PROGRESS_NWD              = 0x22, // Secure OS resumed to the Nwd part
	SOS_PROGRESS_S3_RESUME        = 0x23, // Secure OS finished S3 resume
};


enum bios_psp_command:uint32_t {
// both psp_to_bios_command and bios_to_psp_command
	MBOX_CMD_ABORT              = 0xFE, // Abort/timeout of last command
};
enum bios_to_psp_command:uint32_t { // <= 0x7F
	MBOX_BIOS_CMD_DRAM_INFO     = 0x01, // Notification that DRAM is trained and ready for use.
	MBOX_BIOS_CMD_SMM_INFO      = 0x02, // Provides details on SMM memory area reserved for PSP. It includes the physical addresses of SMM Base and PSP SMM data region and the length of PSP SMM data region.
	MBOX_BIOS_CMD_SX_INFO       = 0x03, // Notification that the platform is entering S3-suspend state.
	MBOX_BIOS_CMD_RSM_INFO      = 0x04, // Information on BIOS Resume Module stored in SMM memory which includes the BIOS resume vector and size of the resume code.
	MBOX_BIOS_CMD_PSP_QUERY     = 0x05, // Command to get the list of capabilities supported by PSP FW. This is used to communicate if iTPM is supported or not in PSP FW.
	MBOX_BIOS_CMD_BOOT_DONE     = 0x06, // Notification that BIOS has completed BIOS POST.
	MBOX_BIOS_CMD_CLEAR_S3      = 0x07, // Inform PSP clear S3ExitReset
	MBOX_BIOS_S3_DATA_INFO      = 0x08, // Bios will send this command to inform PSP to save the blob, which needed to restore memory during resume from S3
	MBOX_BIOS_CMD_NOP           = 0x09, // Notification that BIOS has completed PSP-to-BIOS command submitted via PSP-to-BIOS mailbox interface.
};
enum psp_to_bios_command:uint32_t { // 0x80 <=
	MBOX_PSP_CMD_SPI_GET_ATTRIB = 0x81, // Get SPI-ROM attributes such as the size and polarity
	MBOX_PSP_CMD_SPI_SET_ATTRIB = 0x82, // Set SPI-ROM attributes
	MBOX_PSP_CMD_GET_BLOCK_SIZE = 0x83, // Get SPI-ROM block size
	MBOX_PSP_CMD_READ_FV        = 0x84, // Read PSP NVRAM firmware volume
	MBOX_PSP_CMD_WRITE_FV       = 0x85, // Write SP NVRAM firmware volume
	MBOX_PSP_CMD_ERASE_FV       = 0x86, // Erase PSP NVRAM firmware volume
};

union fw_status_reg {
	uint32_t raw;
	union {
		enum psp_fw_status       status   :15-0 +1;
		enum sos_progress_codes  progress :23-16 +1;
		enum bios_to_psp_command command  :30-24 +1;
		uint32_t passed_to_secure_os      :31-31 +1;
	};
};

union bios_psp_mbox_status { // set by the target for the last command
	uint32_t raw;
	union { uint32_t
		mbox_initialised  :0-0 +1,
		error             :1-1 +1,
		terminated        :2-2 +1,
		halt              :3-3 +1, // unrecoverable error
		recovery_required :4-4 +1, // some psp entry by the dir is corrupted
		rsvd             :31-5 +1;
	};
};

struct bios_to_psp { // c2pmsg 28 ~ 31
	enum bios_to_psp_command command;
	union bios_psp_mbox_status Status;
	uint64_t CmdRspBufAddr; // physical address pointing to struct mbox_buffer_header
};

struct mbox_buffer_header { 
	uint32_t TotalSize;
	union bios_psp_mbox_status Status;
};

struct smm_trigger_info {  
	uint64_t Address;
	uint32_t AddressType;
	uint32_t ValueWidth;
	uint32_t ValueAndMask;
	uint32_t ValueOrMask;
};
struct smm_req_buffer {  // MBOX_BIOS_CMD_PSP_QUERY
	uint64_t SmmBase;
	uint64_t SmmLength;
	uint64_t PsPSmmDataRegion;
	uint64_t PspSmmDataLength;
	struct smm_trigger_info SmmTrigInfo;
};

struct mbox_sx_buffer {  // MBOX_BIOS_CMD_SX_INFO
	struct mbox_buffer_header Header;
	uint8_t SleepType;
};

struct mbox_rsm_buffer {  // MBOX_BIOS_CMD_RSM_INFO
	struct mbox_buffer_header Header;
	uint64_t ResumeVectorAddress;
	uint64_t ResumeVectorLength;
};


struct caps_req_buffer { 
	uint32_t Capabilities;
};
// Bitmap defining capabilities
#define PSP_CAP_TPM (1 << 0)
struct mbox_caps_buffer {  // MBOX_BIOS_CMD_PSP_QUERY
	struct mbox_buffer_header Header;
	uint32_t Capability;
};



struct s3data_req_buffer { 
	uint64_t S3RestoreBufferBase; // Address
	uint64_t S3RestoreBufferSize;
};
struct mbox_s3data_buffer {  //  MBOX_BIOS_S3_DATA_INFO
	struct mbox_buffer_header Header;
	struct s3data_req_buffer Req;
};

struct bios_mbox { // psp to bios
	volatile enum bios_psp_command MboxCmd;
	volatile union bios_psp_mbox_status MboxSts;
	struct mbox_buffer_header* Buffer;
};

struct spi_attrib_request {  // MBOX_PSP_CMD_SPI_GET_ATTRIB
	uint64_t Attribute; // UEFI enum EFI_FVB_ATTRIBUTES_2
};


// like UEFI EFI_FVB_GET_BLOCK_SIZE but spi_info_req is absolute
struct spi_info_req {  // MBOX_PSP_CMD_GET_BLOCK_SIZE
	uint64_t Lba;
	uint64_t BlockSize;
	uint64_t NumberOfBlocks;
};

struct spi_rw_req {  // MBOX_PSP_CMD_READ_FV / MBOX_PSP_CMD_WRITE_FV
	uint64_t Lba;
	uint64_t Offset;
	uint64_t NumByte;
	uint8_t  Buffer[] __counted_by(NumByte);
};

struct spi_erase_req {  // MBOX_PSP_CMD_ERASE_FV
	uint64_t Lba;
	uint64_t NumberOfBlocks;
};

#pragma pack(pop)
#endif
