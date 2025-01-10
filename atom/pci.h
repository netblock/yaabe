#ifndef PCI_H
#define PCI_H
#pragma pack(push, 1) // bios data must use byte alignment

// https://uefi.org/specs/UEFI/2.10/14_Protocols_PCI_Bus_Support.html#recommended-pci-device-driver-layout
#define PCI_HEADER_MAGIC 0xAA55
#define BIOS_IMAGE_SIZE_UNIT 512
struct pci_rom_header { // standard PCIe ROM header
	uint16_t pci_rom_signature; // 0xAA55 has been around since IBM PC; is a part of PCIe, and a part of ATOM.
	uint8_t  pci_rom_size_in_512; // in 512 Bytes
	uint8_t  jump_core_main_init_bios; // x86 init code
	uint16_t label_core_main_init_bios;
	uint8_t  pci_reserved[18]; // reserved for user
	uint16_t pcir_structure_offset;
};


union pcir_indicator_byte {
	uint8_t indicator;
	struct { uint8_t
		indicator_reserved :6-0 +1,
		last_image         :7-7 +1;
	};
};

//             little-endian: 3 2 1 0
//                            R I C P
#define PCIR_SIGNATURE     0x52494350
#define PCIR_SIGNATURE_STR "PCIR"
struct pcir_data_structure {  // PCI Rom
	union magic_32 signature; // PCIR
	uint16_t vendor_id;
	uint16_t device_id;
	uint16_t vpd_reserved;    // was PCI Vital Product Data (VPD)
	uint16_t structure_length;
	uint8_t  structure_revision;
	uint8_t  class_code[3];
	uint16_t image_length_in_512;
	uint16_t code_revision;
	uint8_t  code_type;
	union pcir_indicator_byte last;
	uint16_t end_reserved;
};

enum efi_pci_driver_subsystem_value:uint16_t {
	// values other than these are from PE/COFF header
	EFI_PCI_DRIVER_SUBSYSTEM_BOOT_SERVICE = 0x0B,
	EFI_PCI_DRIVER_SUBSYSTEM_RUNTIME      = 0x0C,
};
enum efi_pci_driver_machine_type:uint16_t {
	// values other than these are from PE/COFF header
	EFI_PCI_DRIVER_MACHINE_TYPE_IA32    = 0x014C,
	EFI_PCI_DRIVER_MACHINE_TYPE_ITANIUM = 0x0200,
	EFI_PCI_DRIVER_MACHINE_TYPE_EBC     = 0x0EBC, // EFI byte code
	EFI_PCI_DRIVER_MACHINE_TYPE_X64     = 0x8664,
	EFI_PCI_DRIVER_MACHINE_TYPE_ARM32   = 0x01c2,
	EFI_PCI_DRIVER_MACHINE_TYPE_ARM64   = 0xAA64,
};
#define EFI_SIGNATURE 0xEF1
struct efi_pci_device_driver_image {
	uint16_t pci_rom_signature; // 0xAA55
	uint16_t pci_rom_size_in_512; // in 512 Bytes
	uint32_t efi_signature; // 0xEF1
	enum efi_pci_driver_subsystem_value subsystem_value;
	enum efi_pci_driver_machine_type machine_type;
	uint16_t compression_type; // 1 = Compressed following the UEFI algo
	uint64_t reserved;
	uint16_t efi_image_offset;
	uint16_t pcir_structure_offset;
	uint16_t pcir_padding;
	struct pcir_data_structure  pcir;
};

#pragma pack(pop) // restore old packing
#endif
