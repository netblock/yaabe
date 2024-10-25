/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef _AMD_FW_TOOL_H_
#define _AMD_FW_TOOL_H_

#include <commonlib/bsd/compiler.h>
#include <commonlib/bsd/helpers.h>
#include <openssl/sha.h>
#include <stdint.h>
#include <stdbool.h>

#define ERASE_ALIGNMENT 0x1000U
#define TABLE_ALIGNMENT 0x1000U
#define TABLE_L2_SIZE_MAX 0x400U
#define BLOB_ALIGNMENT 0x100U
#define TABLE_ERASE_ALIGNMENT _MAX(TABLE_ALIGNMENT, ERASE_ALIGNMENT)
#define BLOB_ERASE_ALIGNMENT _MAX(BLOB_ALIGNMENT, ERASE_ALIGNMENT)

enum platform {
	PLATFORM_UNKNOWN,
	PLATFORM_CARRIZO,
	PLATFORM_STONEYRIDGE,
	PLATFORM_RAVEN,
	PLATFORM_PICASSO,
	PLATFORM_RENOIR,
	PLATFORM_CEZANNE,
	PLATFORM_MENDOCINO,
	PLATFORM_LUCIENNE,
	PLATFORM_PHOENIX,
	PLATFORM_GLINDA,
	PLATFORM_GENOA,
};

typedef enum _amd_fw_type {
	AMD_FW_PSP_PUBKEY = 0x00,
	AMD_FW_PSP_BOOTLOADER = 0x01,
	AMD_FW_PSP_SECURED_OS = 0x02,
	AMD_FW_PSP_RECOVERY = 0x03,
	AMD_FW_PSP_NVRAM = 0x04,
	AMD_FW_PSP_RTM_PUBKEY = 0x05,
	AMD_FW_PSP_SMU_FIRMWARE = 0x08,
	AMD_FW_PSP_SECURED_DEBUG = 0x09,
	AMD_FW_ABL_PUBKEY = 0x0a,
	AMD_PSP_FUSE_CHAIN = 0x0b,
	AMD_FW_PSP_TRUSTLETS = 0x0c,
	AMD_FW_PSP_TRUSTLETKEY = 0x0d,
	AMD_FW_PSP_SMU_FIRMWARE2 = 0x12,
	AMD_DEBUG_UNLOCK = 0x13,
	AMD_BOOT_DRIVER = 0x1b,
	AMD_SOC_DRIVER = 0x1c,
	AMD_DEBUG_DRIVER = 0x1d,
	AMD_INTERFACE_DRIVER = 0x1f,
	AMD_HW_IPCFG = 0x20,
	AMD_WRAPPED_IKEK = 0x21,
	AMD_TOKEN_UNLOCK = 0x22,
	AMD_SEC_GASKET = 0x24,
	AMD_MP2_FW = 0x25,
	AMD_DRIVER_ENTRIES = 0x28,
	AMD_FW_KVM_IMAGE = 0x29,
	AMD_FW_MP5 = 0x2a,
	AMD_S0I3_DRIVER = 0x2d,
	AMD_ABL0 = 0x30,
	AMD_ABL1 = 0x31,
	AMD_ABL2 = 0x32,
	AMD_ABL3 = 0x33,
	AMD_ABL4 = 0x34,
	AMD_ABL5 = 0x35,
	AMD_ABL6 = 0x36,
	AMD_ABL7 = 0x37,
	AMD_SEV_DATA = 0x38,
	AMD_SEV_CODE = 0x39,
	AMD_FW_PSP_WHITELIST = 0x3a,
	AMD_VBIOS_BTLOADER = 0x3c,
	AMD_FW_L2_PTR = 0x40,
	AMD_FW_DXIO = 0x42,
	AMD_FW_USB_PHY = 0x44,
	AMD_FW_TOS_SEC_POLICY = 0x45,
	AMD_FW_DRTM_TA = 0x47,
	AMD_FW_RECOVERYAB_A = 0x48,
	AMD_FW_RECOVERYAB_B = 0x4A,
	AMD_FW_BIOS_TABLE = 0x49,
	AMD_FW_KEYDB_BL = 0x50,
	AMD_FW_KEYDB_TOS = 0x51,
	AMD_FW_PSP_VERSTAGE = 0x52,
	AMD_FW_VERSTAGE_SIG = 0x53,
	AMD_RPMC_NVRAM = 0x54,
	AMD_FW_SPL = 0x55,
	AMD_FW_DMCU_ERAM = 0x58,
	AMD_FW_DMCU_ISR = 0x59,
	AMD_FW_MSMU = 0x5a,
	AMD_FW_SPIROM_CFG = 0x5c,
	AMD_FW_MPIO = 0x5d,
	AMD_FW_TPMLITE = 0x5f, /* family 17h & 19h */
	AMD_FW_PSP_SMUSCS = 0x5f, /* family 15h & 16h */
	AMD_FW_DMCUB = 0x71,
	AMD_FW_PSP_BOOTLOADER_AB = 0x73,
	AMD_RIB = 0x76,
	AMD_FW_AMF_SRAM = 0x85,
	AMD_FW_AMF_DRAM = 0x86,
	AMD_FW_AMF_WLAN = 0x88,
	AMD_FW_AMF_MFD = 0x89,
	AMD_FW_MPDMA_TF = 0x8c,
	AMD_TA_IKEK = 0x8d,
	AMD_FW_MPCCX = 0x90,
	AMD_FW_GMI3_PHY = 0x91,
	AMD_FW_MPDMA_PM = 0x92,
	AMD_FW_LSDMA = 0x94,
	AMD_FW_C20_MP = 0x95,
	AMD_FW_FCFG_TABLE = 0x98,
	AMD_FW_MINIMSMU = 0x9a,
	AMD_FW_SRAM_FW_EXT = 0x9d,
	AMD_FW_UMSMU = 0xa2,
	AMD_FW_IMC = 0x200,	/* Large enough to be larger than the top BHD entry type. */
	AMD_FW_GEC,
	AMD_FW_XHCI,
	AMD_FW_INVALID,		/* Real last one to detect the last entry in table. */
	AMD_FW_SKIP		/* This is for non-applicable options. */
} amd_fw_type;

typedef enum _amd_bios_type {
	AMD_BIOS_RTM_PUBKEY = 0x05,
	AMD_BIOS_SIG = 0x07,
	AMD_BIOS_APCB = 0x60,
	AMD_BIOS_APOB = 0x61,
	AMD_BIOS_BIN = 0x62,
	AMD_BIOS_APOB_NV = 0x63,
	AMD_BIOS_PMUI = 0x64,
	AMD_BIOS_PMUD = 0x65,
	AMD_BIOS_UCODE = 0x66,
	AMD_BIOS_APCB_BK = 0x68,
	AMD_BIOS_EARLY_VGA = 0x69,
	AMD_BIOS_MP2_CFG = 0x6a,
	AMD_BIOS_PSP_SHARED_MEM = 0x6b,
	AMD_BIOS_L2_PTR =  0x70,
	AMD_BIOS_INVALID,
	AMD_BIOS_SKIP
} amd_bios_type;

typedef enum _amd_addr_mode {
	AMD_ADDR_PHYSICAL = 0,	/* Physical address */
	AMD_ADDR_REL_BIOS,	/* Relative to beginning of image */
	AMD_ADDR_REL_TAB,	/* Relative to table */
	AMD_ADDR_REL_SLOT,	/* Relative to slot */
} amd_addr_mode;

struct second_gen_efs { /* todo: expand for Server products */
	uint32_t gen:1; /* Client products only use bit 0 */
	uint32_t reserved:31;
} __attribute__((packed));

#define EFS_SECOND_GEN 0
#define EFS_BEFORE_SECOND_GEN 1

typedef struct _embedded_firmware {
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
} __attribute__((packed, aligned(16))) embedded_firmware;

typedef struct _psp_directory_header {
	uint32_t cookie;
	uint32_t checksum;
	uint32_t num_entries;
	union {
		uint32_t additional_info;
		struct {
			uint32_t dir_size:10;
			uint32_t spi_block_size:4;
			uint32_t base_addr:15;
			uint32_t address_mode:2;
			uint32_t not_used:1;
		} __attribute__((packed)) additional_info_fields;
	};
} __attribute__((packed, aligned(16))) psp_directory_header;

typedef struct _psp_directory_entry {
	uint8_t type;
	uint8_t subprog;
	union {
		uint16_t rsvd;
		struct {
			uint8_t rom_id:2;
			uint8_t writable:1;
			uint8_t inst:4;
			uint8_t rsvd_1:1;
			uint8_t rsvd_2:8;
		} __attribute__((packed));
	};
	uint32_t size;
	uint64_t addr:62; /* or a value in some cases */
	uint64_t address_mode:2;
} __attribute__((packed)) psp_directory_entry;

typedef struct _psp_directory_table {
	psp_directory_header header;
	psp_directory_entry entries[];
} __attribute__((packed, aligned(16))) psp_directory_table;

#define MAX_PSP_ENTRIES 0xff

typedef struct _psp_combo_header {
	uint32_t cookie;
	uint32_t checksum;
	uint32_t num_entries;
	uint32_t lookup;
	uint64_t reserved[2];
} __attribute__((packed, aligned(16))) psp_combo_header;

typedef struct _psp_combo_entry {
	uint32_t id_sel;
	uint32_t id;
	uint64_t lvl2_addr;
} __attribute__((packed)) psp_combo_entry;

typedef struct _psp_combo_directory {
	psp_combo_header header;
	psp_combo_entry entries[];
} __attribute__((packed, aligned(16))) psp_combo_directory;

#define MAX_COMBO_ENTRIES 2

typedef struct _bios_directory_hdr {
	uint32_t cookie;
	uint32_t checksum;
	uint32_t num_entries;
	union {
		uint32_t additional_info;
		struct {
			uint32_t dir_size:10;
			uint32_t spi_block_size:4;
			uint32_t base_addr:15;
			uint32_t address_mode:2;
			uint32_t not_used:1;
		} __attribute__((packed)) additional_info_fields;
	};
} __attribute__((packed, aligned(16))) bios_directory_hdr;

typedef struct _bios_directory_entry {
	uint8_t type;
	uint8_t region_type;
	int reset:1;
	int copy:1;
	int ro:1;
	int compressed:1;
	int inst:4;
	uint8_t subprog; /* b[7:3] reserved */
	uint32_t size;
	uint64_t source:62;
	uint64_t address_mode:2;
	uint64_t dest;
} __attribute__((packed)) bios_directory_entry;

typedef struct _bios_directory_table {
	bios_directory_hdr header;
	bios_directory_entry entries[];
} bios_directory_table;

#define MAX_BIOS_ENTRIES 0x2f

#define BDT_LVL1 (1 << 0)
#define BDT_LVL2 (1 << 1)
#define BDT_LVL1_AB (1 << 2)
#define BDT_LVL2_AB (1 << 3)
#define BDT_BOTH (BDT_LVL1 | BDT_LVL2)
#define BDT_BOTH_AB (BDT_LVL1_AB | BDT_LVL2_AB)
typedef struct _amd_bios_entry {
	amd_bios_type type;
	char *filename;
	int subpr;
	int region_type;
	int reset;
	int copy;
	int ro;
	int zlib;
	int inst;
	uint64_t src;
	uint64_t dest;
	size_t size;
	int level;
} amd_bios_entry;

typedef struct _ish_directory_table {
	uint32_t checksum;
	uint32_t boot_priority;
	uint32_t update_retry_count;
	uint8_t  glitch_retry_count;
	uint8_t  glitch_higherbits_reserved[3];
	uint32_t pl2_location;
	uint32_t psp_id;
	uint32_t slot_max_size;
	uint32_t reserved;
} __attribute__((packed)) ish_directory_table;

#define EMBEDDED_FW_SIGNATURE 0x55aa55aa
#define PSP_COOKIE 0x50535024		/* 'PSP$' */
#define PSPL2_COOKIE 0x324c5024		/* '2LP$' */
#define PSP2_COOKIE 0x50535032		/* 'PSP2' */
#define BHD_COOKIE 0x44484224		/* 'DHB$ */
#define BHDL2_COOKIE 0x324c4224		/* '2LB$ */
#define BHD2_COOKIE 0x44484232		/* 'DHB2' */

#define PSP_LVL1 (1 << 0)
#define PSP_LVL2 (1 << 1)
#define PSP_LVL1_AB (1 << 2)
#define PSP_LVL2_AB (1 << 3)
#define PSP_BOTH (PSP_LVL1 | PSP_LVL2)
#define PSP_BOTH_AB (PSP_LVL1_AB | PSP_LVL2_AB)

typedef enum _fwid_type {
	FWID_TYPE_FWID = 0,
	FWID_TYPE_UUID,
} fwid_type_t;

#define UUID_LEN_BYTES 16
typedef struct _amd_fw_entry_hash {
	fwid_type_t fwid_type;
	union {
		uint16_t fw_id;
		uint8_t uuid[UUID_LEN_BYTES];
	};
	uint16_t subtype;
	uint32_t sha_len;
	uint8_t sha[SHA384_DIGEST_LENGTH];
} amd_fw_entry_hash;

typedef struct _amd_fw_entry {
	amd_fw_type type;
	char *filename;
	uint8_t subprog;
	uint8_t inst;
	uint64_t dest;
	size_t size;
	int level;
	uint64_t other;
	/* If the binary is signed and the tool is invoked to keep the signed binaries separate,
	   then this field is populated with the offset of the concerned PSP binary (relative to
	   BIOS or PSP Directory table). */
	uint64_t addr_signed;
	uint32_t file_size;
	/* Some files that don't have amd_fw_header have to be skipped from hashing. These files
	   include but not limited to: *iKek*, *.tkn, *.stkn */
	bool skip_hashing;
	uint8_t hash_tbl_id;
	fwid_type_t fwid_type;
	uint32_t num_hash_entries;
	amd_fw_entry_hash *hash_entries;
	bool generate_manifest;
} amd_fw_entry;

/* Most PSP binaries, if not all, have the following header format. */
struct amd_fw_header {
	uint8_t reserved_0[20];
	uint32_t fw_size_signed;
	uint8_t reserved_18[24];
	/* 1 if the image is signed, 0 otherwise */
	uint32_t sig_opt;
	uint32_t sig_id;
	uint8_t sig_param[16];
	uint32_t comp_opt;
	uint8_t reserved_4c[4];
	uint32_t uncomp_size;
	uint32_t comp_size;
	/* Starting MDN fw_id is populated instead of fw_type. */
	uint16_t fw_id;
	uint8_t reserved_5a[6];
	uint8_t version[4];
	uint8_t reserved_64[8];
	uint32_t size_total;
	uint8_t reserved_70[12];
	/* Starting MDN fw_id is populated instead of fw_type. fw_type will still be around
	   for backwards compatibility. */
	uint8_t fw_type;
	uint8_t fw_subtype;
	uint8_t fw_subprog;
	uint8_t reserved_7f;
	uint8_t reserved_80[128];
} __packed;

/* Based on the available PSP resources and increasing number of signed PSP binaries,
   AMD recommends to split the hash table into 3 parts for now. */
#define MAX_NUM_HASH_TABLES 3
struct psp_fw_hash_table {
	uint16_t version;
	uint16_t no_of_entries_256;
	uint16_t no_of_entries_384;
	/* The next 2 elements are pointers to arrays of SHA256 and SHA384 entries. */
	/* It does not make sense to store pointers in the CBFS file */
} __packed;

typedef struct _amd_cb_config {
	bool have_whitelist;
	bool unlock_secure;
	bool use_secureos;
	bool load_mp2_fw;
	bool multi_level;
	bool s0i3;
	bool second_gen;
	bool have_mb_spl;
	bool recovery_ab;
	bool recovery_ab_single_copy;
	bool need_ish;
	bool use_combo;
	bool combo_new_rab;	/* new combo layout for recovery A/B */
	bool have_apcb_bk;
	enum platform soc_id;

	uint8_t efs_spi_readmode, efs_spi_speed, efs_spi_micron_flag;
	uint32_t body_location, efs_location;
	uint64_t signed_start_addr;
	char *manifest_file;
	const char *signed_output_file;
	char *output, *config;
	char *combo_config[MAX_COMBO_ENTRIES];
	int debug;
} amd_cb_config;

typedef struct _context {
	char *rom;		/* target buffer, size of flash device */
	uint32_t rom_size;	/* size of flash device */
	uint32_t address_mode;	/* 0:abs address; 1:relative to flash; 2: relative to table */
	uint32_t current;	/* pointer within flash & proxy buffer */
	uint32_t current_pointer_saved;
	uint32_t current_table;
	void *amd_psp_fw_table_clean;
	void *amd_bios_table_clean;
	struct _combo_apcb {
		char *filename;
		uint8_t ins;
		uint8_t sub;
	} combo_apcb[MAX_COMBO_ENTRIES], combo_apcb_bk[MAX_COMBO_ENTRIES];
	embedded_firmware *amd_romsig_ptr;
	psp_directory_table *pspdir, *pspdir_bak, *pspdir2, *pspdir2_b;
	bios_directory_table *biosdir, *biosdir2, *biosdir2_b;
	psp_combo_directory *psp_combo_dir, *bhd_combo_dir;
	ish_directory_table *ish_a_dir, *ish_b_dir;
} context;

uint8_t process_config(FILE *config, amd_cb_config *cb_config);
void process_signed_psp_firmwares(const char *signed_rom,
		amd_fw_entry *fw_table,
		uint64_t signed_start_addr,
		enum platform soc_id);
int find_bios_entry(amd_bios_type type);
bool needs_ish(enum platform platform_type);

#define EFS_FILE_SUFFIX ".efs"
#define TMP_FILE_SUFFIX ".tmp"
#define BODY_FILE_SUFFIX ".body"

void write_or_fail(int fd, void *ptr, size_t size);
ssize_t read_from_file_to_buf(int fd, void *buf, size_t buf_size);
ssize_t write_from_buf_to_file(int fd, const void *buf, size_t buf_size);
ssize_t write_body(char *output, void *body_offset, ssize_t body_size);
ssize_t copy_blob(void *dest, const char *src_file, size_t room);
#define OK 0

#define LINE_EOF (1)
#define LINE_TOO_LONG (2)

int amdfwtool_getopt(int argc, char *argv[], amd_cb_config *cb_config, context *ctx);
void register_apcb_combo(amd_cb_config *cb_config, int combo_index, context *ctx);

#endif	/* _AMD_FW_TOOL_H_ */
