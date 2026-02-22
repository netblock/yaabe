#ifndef NONATOM_TABLES_H
#define NONATOM_TABLES_H

struct pci_rom_tables {
	bool is_efi;
	union {
		struct efi_pci_device_driver_image* efi;
		struct pci_rom_header* header;
	};
	struct pcir_data_structure* pcir;
};
struct atomtree_pci_tables {
	uint8_t num_images;
	struct pci_rom_tables* pci_tables;
};


struct atomtree_psp_rsa {
	union {
		void* raw;
		struct psp_rsa_key_header* header;
		struct psp_rsa_key_2048* b2048;
		struct psp_rsa_key_4096* b4096;
	};
	uint8_t* public_exponent;
	uint8_t* modulus;
};

struct atomtree_discovery_ip_entry {
	union {
		void* raw;
		union  discovery_ip_entry*        entry;
		struct discovery_ip_entry_header* header;
		struct discovery_ip_entry_v1*     v1;
		struct discovery_ip_entry_v3*     v3;
		struct discovery_ip_entry_v3*     v4_32;
		struct discovery_ip_entry_v4_64*  v4_64;
	};
	semver ver;
};
struct atomtree_discovery_ip_die {
	struct ip_discovery_die_header* header;
	struct atomtree_discovery_ip_entry* entries;
};
struct atomtree_discovery_table {
	struct discovery_fw_blob* blob;

	semver binary_ver;
	semver ip_ver;
	semver gc_ver;
	semver harvest_ver;
	semver vcn_ver;
	semver mall_ver;
	semver nps_ver;
	uint8_t num_dies;

	struct atomtree_discovery_ip_die  dies[IP_DISCOVERY_MAX_NUM_DIES];
	struct ip_discovery_header*       ip_discovery;
	union  discovery_gc_info*         gc_info;
	struct discovery_harvest_table*   harvest;
	struct discovery_vcn_info_v1_0*   vcn_info;
	union  discovery_mall_info*       mall_info;
	struct discovery_nps_info_v1_0*   nps_info;
};

enum atomtree_psp_fw_payload_type:uint8_t {
// This enum may not be technically necessary given
// struct amd_fw_header.fw_type and .fw_id
// but there's not much info about it and seems generic
	PSPFW_UNKNOWN = 0,
	PSPFW_RSA, // AMD_PUBLIC_KEY
	PSPFW_DISCOVERY, // AMD_ABL7
};
struct atomtree_psp_directory_entries {
	union {
		// TODO some fw blobs don't do the psp fw header
		// A trick to tell is if,
		// struct psp_directory_entry.type == struct amd_fw_header.fw_type
		void* raw;
		struct amd_fw_header* header;

		struct atomtree_psp_rsa         rsa;
		struct atomtree_discovery_table discovery;
	};

	enum atomtree_psp_fw_payload_type type;
	bool has_fw_header;
};
struct atomtree_psp_directory {
	struct psp_directory* directory;
	struct atomtree_psp_directory_entries* fw_entries;
};

#endif
