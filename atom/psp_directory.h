#ifndef PSP_DIRECTORY_H
#define PSP_DIRECTORY_H
#pragma pack(push, 1) // bios data must use byte alignment

#define FIRMWARE_TABLE_SIGNATURE  0x55AA55AA
// Define the structure OEM signature table
struct firmware_entry_table {
	uint32_t  Signature;  // Signature should be 0x55AA55AA
	uint32_t  ImcRomBase; // Base Address for Imc Firmware
	uint32_t  GecRomBase; // Base Address for Gmc Firmware
	uint32_t  XHCRomBase; // Base Address for XHCI Firmware
	uint32_t  PspDirBase; // Base Address for PSP directory
};

// Define structure for PSP directory
//     little-endian: 3 2 1 0
//                    P S P $
#define PSP_COOKIE 0x50535024
struct psp_directory_header {
	char  pspcookie[4] __nonstring; // "$PSP"
	uint32_t  checksum;     // 32 bit CRC of header items below and the entire table
	uint32_t  totalentries; // Number of PSP Entries
	uint32_t  reserved;     // Unused
};


// define various enum type for PSP entry type
enum psp_directory_entry_type:uint32_t {
	AMD_PUBLIC_KEY              = 0, // AMD public key
	PSP_FW_BOOT_LOADER          = 1, // PSP boot loader in SPI space
	PSP_FW_TRUSTED_OS           = 2, // PSP Firmware region in SPI space
	PSP_FW_RECOVERY_BOOT_LOADER = 3, // PSP recovery region.
	PSP_NV_DATA                 = 4, // PSP data region in SPI space
	BIOS_PUBLIC_KEY             = 5, // BIOS public key stored in SPI space
	BIOS_RTM_FIRMWARE           = 6, // BIOS RTM code (PEI volume) in SPI space
	BIOS_RTM_SIGNATURE          = 7, // signed BIOS RTM hash stored  in SPI space
	SMU_OFFCHIP_FW              = 8, // SMU image
};

// Structure for PSP Entry
struct psp_directory_entry {
	enum psp_directory_entry_type  type;
	uint32_t size;     // Size of PSP Entry in bytes
	uint64_t location; // Location of PSP Entry (byte offset from start of SPI-ROM)
};

// Structure for PSP directory
struct psp_directory {
	struct psp_directory_header  header; // PSP directory header
	struct psp_directory_entry   pspentry[] __counted_by(header.TotalEntries); // Array of PSP entries each pointing to a binary in SPI flash
};

#pragma pack(pop)
#endif
