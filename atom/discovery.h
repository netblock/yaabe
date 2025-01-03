#ifndef DISCOVERY_H
#define DISCOVERY_H


#define PSP_HEADER_SIZE           256

enum discovery_tables {
	DISCOVERY_IP_DISCOVERY = 0,
	DISCOVERY_GC           = 1,
	DISCOVERY_HARVEST_INFO = 2,
	DISCOVERY_VCN_INFO     = 3,
	DISCOVERY_MALL_INFO    = 4,
	DISCOVERY_NPS_INFO     = 5,
	DISCOVERY_TOTAL_TABLES = 6,
};

#define HWIP_MAX_INSTANCE 44
enum soc15_hwid:uint16_t {
	MP1_HWID          = 1,
	MP2_HWID          = 2,
	THM_HWID          = 3,
	SMUIO_HWID        = 4,
	FUSE_HWID         = 5,
	CLKA_HWID         = 6,
	PWR_HWID         = 10,
	GC_HWID          = 11,
	UVD_HWID         = 12,
	VCN_HWID         = UVD_HWID,
	AUDIO_AZ_HWID    = 13,
	ACP_HWID         = 14,
	DCI_HWID         = 15,
	DCO_HWID         = 16,
	XDMA_HWID        = 17,
	DCEAZ_HWID       = 18,
	SDPMUX_HWID      = 19,
	NTB_HWID         = 20,
	VPE_HWID         = 21,
	IOHC_HWID        = 24,
	L2IMU_HWID       = 28,
	VCE_HWID         = 32,
	MMHUB_HWID       = 34,
	ATHUB_HWID       = 35,
	DBGU_NBIO_HWID   = 36,
	DFX_HWID         = 37,
	DBGU0_HWID       = 38,
	DBGU1_HWID       = 39,
	OSSSYS_HWID      = 40,
	HDP_HWID         = 41,
	SDMA0_HWID       = 42,
	SDMA1_HWID       = 43,
	ISP_HWID         = 44,
	DBGU_IO_HWID     = 45,
	DF_HWID          = 46,
	CLKB_HWID        = 47,
	FCH_HWID         = 48,
	DFX_DAP_HWID     = 49,
	L1IMU_PCIE_HWID  = 50,
	L1IMU_NBIF_HWID  = 51,
	L1IMU_IOAGR_HWID = 52,
	L1IMU3_HWID      = 53,
	L1IMU4_HWID      = 54,
	L1IMU5_HWID      = 55,
	L1IMU6_HWID      = 56,
	L1IMU7_HWID      = 57,
	L1IMU8_HWID      = 58,
	L1IMU9_HWID      = 59,
	L1IMU10_HWID     = 60,
	L1IMU11_HWID     = 61,
	L1IMU12_HWID     = 62,
	L1IMU13_HWID     = 63,
	L1IMU14_HWID     = 64,
	L1IMU15_HWID     = 65,
	WAFLC_HWID       = 66,
	FCH_USB_PD_HWID  = 67,
	SDMA2_HWID       = 68,
	SDMA3_HWID       = 69,
	PCIE_HWID        = 70,
	PCS_HWID         = 80,
	DDCL_HWID        = 89,
	SST_HWID         = 90,
	LSDMA_HWID       = 91,
	IOAGR_HWID      = 100,
	NBIF_HWID       = 108,
	IOAPIC_HWID     = 124,
	SYSTEMHUB_HWID  = 128,
	NTBCCP_HWID     = 144,
	UMC_HWID        = 150,
	SATA_HWID       = 168,
	USB_HWID        = 170,
	CCXSEC_HWID     = 176,
	XGMI_HWID       = 200,
	XGBE_HWID       = 216,
	MP0_HWID        = 255,
	DMU_HWID        = 271,
	DIO_HWID        = 272,
	DAZ_HWID        = 274,
	HWID_MAX        = 300,
};

#pragma pack(push, 1) // bios data must use byte alignment

struct discovery_table_info {
	uint16_t offset; 
	uint16_t checksum; // Byte sum of the table 
	uint16_t size;
	uint16_t padding;
};

#define DISCOVERY_BINARY_SIGNATURE    0x28211407
struct discovery_binary_header {
	uint32_t signature;
	uint16_t version_major;
	uint16_t version_minor;
	uint16_t binary_checksum; // Byte sum of the binary after this field 
	uint16_t binary_size;
	struct discovery_table_info table_list[DISCOVERY_TOTAL_TABLES];
};
struct discovery_fw_blob {
	struct amd_fw_header           firmware_header;
	struct discovery_binary_header binary_header;
};

struct ip_die_info {
	uint16_t die_id;
	uint16_t die_offset;
};
union ip_discovery_header_flags_v4 { // reserved in v3
	uint16_t flags;
	struct { uint16_t
		base_addr_64_bit :0-0 +1, // ip structures are using 64 bit base address
		reserved        :15-1 +1;
	};
};
#define IP_DISCOVERY_MAX_NUM_DIES 16
//                        little-endian: 3 2 1 0
//                                       S D P I
#define DISCOVERY_TABLE_SIGNATURE     0x53445049
#define DISCOVERY_TABLE_SIGNATURE_STR "IPDS"
struct ip_discovery_header {
	union magic_32 signature; // IPDS
	uint16_t version;
	uint16_t size;
	uint32_t id;
	uint16_t num_dies;
	struct ip_die_info die_info[IP_DISCOVERY_MAX_NUM_DIES];
	union ip_discovery_header_flags_v4 flags; // reserved in v3 and older
};

struct ip_discovery_die_header {
	uint16_t die_id;
	uint16_t num_ips;
};

union ip_harvest {
	uint8_t raw;
	struct { uint8_t
		harvest  :3-0 +1,
		reserved :7-4 +1; 
	};
};

struct discovery_ip_entry_header {
	enum soc15_hwid hardware_id;
	uint8_t instance_number; // max: HWIP_MAX_INSTANCE
	uint8_t num_base_address;
	uint8_t major;
	uint8_t minor;
	uint8_t revision;
};

struct discovery_ip_entry_v1 {
	struct discovery_ip_entry_header header;
	union ip_harvest harvest;
	uint32_t base_address[] __counted_by(header.num_base_address);
};
union ip_hcid_sub {
	uint8_t raw;
	struct { uint8_t
		sub_revision :3-0 +1,
		variant      :7-4 +1;
	};
};
struct discovery_ip_entry_v3 {
	struct discovery_ip_entry_header header;
	union ip_hcid_sub sub;
	uint32_t base_address[] __counted_by(header.num_base_address);
};
struct discovery_ip_entry_v4_64 {
	struct discovery_ip_entry_header header;
	union ip_hcid_sub sub;
	uint64_t base_address[] __counted_by(header.num_base_address);
};

union discovery_ip_entry {
	struct discovery_ip_entry_header header;
	struct discovery_ip_entry_v1    v1;
	struct discovery_ip_entry_v3    v3;
	struct discovery_ip_entry_v3    v4_32;
	struct discovery_ip_entry_v4_64 v4_64;
};
struct discovery_ip_die {
	struct ip_discovery_die_header header;
	union discovery_ip_entry entries[] __counted_by(header.num_ips);
};

// GPU core info
//                        little-endian: 3 2 1 0
//                                           C G
#define GC_TABLE_SIGNATURE            0x00004347
#define GC_TABLE_SIGNATURE_STR        "GC"
struct discovery_gc_info_header {
	union magic_32 signature; // GC
	uint16_t version_major;
	uint16_t version_minor;
	uint32_t size;
};

struct discovery_gc_info_v1_0 {
	struct discovery_gc_info_header header;
	uint32_t num_se;
	uint32_t num_wgp0_per_sa;
	uint32_t num_wgp1_per_sa;
	uint32_t num_rb_per_se;
	uint32_t num_gl2c;
	uint32_t num_gprs;
	uint32_t num_max_gs_thds;
	uint32_t gs_table_depth;
	uint32_t gsprim_buff_depth;
	uint32_t parameter_cache_depth;
	uint32_t double_offchip_lds_buffer;
	uint32_t wave_size;
	uint32_t max_waves_per_simd;
	uint32_t max_scratch_slots_per_cu;
	uint32_t lds_size;
	uint32_t num_sc_per_se;
	uint32_t num_sa_per_se;
	uint32_t num_packer_per_sc;
	uint32_t num_gl2a;
};

struct discovery_gc_info_v1_1 {
	struct discovery_gc_info_header header;
	uint32_t num_se;
	uint32_t num_wgp0_per_sa;
	uint32_t num_wgp1_per_sa;
	uint32_t num_rb_per_se;
	uint32_t num_gl2c;
	uint32_t num_gprs;
	uint32_t num_max_gs_thds;
	uint32_t gs_table_depth;
	uint32_t gsprim_buff_depth;
	uint32_t parameter_cache_depth;
	uint32_t double_offchip_lds_buffer;
	uint32_t wave_size;
	uint32_t max_waves_per_simd;
	uint32_t max_scratch_slots_per_cu;
	uint32_t lds_size;
	uint32_t num_sc_per_se;
	uint32_t num_sa_per_se;
	uint32_t num_packer_per_sc;
	uint32_t num_gl2a;
	uint32_t num_tcp_per_sa;
	uint32_t num_sdp_interface;
	uint32_t num_tcps;
};

struct discovery_gc_info_v1_2 {
	struct discovery_gc_info_header header;
	uint32_t num_se;
	uint32_t num_wgp0_per_sa;
	uint32_t num_wgp1_per_sa;
	uint32_t num_rb_per_se;
	uint32_t num_gl2c;
	uint32_t num_gprs;
	uint32_t num_max_gs_thds;
	uint32_t gs_table_depth;
	uint32_t gsprim_buff_depth;
	uint32_t parameter_cache_depth;
	uint32_t double_offchip_lds_buffer;
	uint32_t wave_size;
	uint32_t max_waves_per_simd;
	uint32_t max_scratch_slots_per_cu;
	uint32_t lds_size;
	uint32_t num_sc_per_se;
	uint32_t num_sa_per_se;
	uint32_t num_packer_per_sc;
	uint32_t num_gl2a;
	uint32_t num_tcp_per_sa;
	uint32_t num_sdp_interface;
	uint32_t num_tcps;
	uint32_t num_tcp_per_wpg;
	uint32_t tcp_l1_size;
	uint32_t num_sqc_per_wgp;
	uint32_t l1_instruction_cache_size_per_sqc;
	uint32_t l1_data_cache_size_per_sqc;
	uint32_t gl1c_per_sa;
	uint32_t gl1c_size_per_instance;
	uint32_t gl2c_per_gpu;
};

struct discovery_gc_info_v1_3 {
    struct discovery_gc_info_header header;
    uint32_t num_se;
    uint32_t num_wgp0_per_sa;
    uint32_t num_wgp1_per_sa;
    uint32_t num_rb_per_se;
    uint32_t num_gl2c;
    uint32_t num_gprs;
    uint32_t num_max_gs_thds;
    uint32_t gs_table_depth;
    uint32_t gsprim_buff_depth;
    uint32_t parameter_cache_depth;
    uint32_t double_offchip_lds_buffer;
    uint32_t wave_size;
    uint32_t max_waves_per_simd;
    uint32_t max_scratch_slots_per_cu;
    uint32_t lds_size;
    uint32_t num_sc_per_se;
    uint32_t num_sa_per_se;
    uint32_t num_packer_per_sc;
    uint32_t num_gl2a;
    uint32_t num_tcp_per_sa;
    uint32_t num_sdp_interface;
    uint32_t num_tcps;
    uint32_t num_tcp_per_wpg;
    uint32_t tcp_l1_size;
    uint32_t num_sqc_per_wgp;
    uint32_t l1_instruction_cache_size_per_sqc;
    uint32_t l1_data_cache_size_per_sqc;
    uint32_t gl1c_per_sa;
    uint32_t gl1c_size_per_instance;
    uint32_t gl2c_per_gpu;
    uint32_t tcp_size_per_cu;
    uint32_t tcp_cache_line_size;
    uint32_t instruction_cache_size_per_sqc;
    uint32_t instruction_cache_line_size;
    uint32_t scalar_data_cache_size_per_sqc;
    uint32_t scalar_data_cache_line_size;
    uint32_t tcc_size;
    uint32_t tcc_cache_line_size;
};

struct discovery_gc_info_v2_0 {
	struct discovery_gc_info_header header;
	uint32_t num_se;
	uint32_t num_cu_per_sh;
	uint32_t num_sh_per_se;
	uint32_t num_rb_per_se;
	uint32_t num_tccs;
	uint32_t num_gprs;
	uint32_t num_max_gs_thds;
	uint32_t gs_table_depth;
	uint32_t gsprim_buff_depth;
	uint32_t parameter_cache_depth;
	uint32_t double_offchip_lds_buffer;
	uint32_t wave_size;
	uint32_t max_waves_per_simd;
	uint32_t max_scratch_slots_per_cu;
	uint32_t lds_size;
	uint32_t num_sc_per_se;
	uint32_t num_packer_per_sc;
};

struct discovery_gc_info_v2_1 {
	struct discovery_gc_info_header header;
	uint32_t num_se;
	uint32_t num_cu_per_sh;
	uint32_t num_sh_per_se;
	uint32_t num_rb_per_se;
	uint32_t num_tccs;
	uint32_t num_gprs;
	uint32_t num_max_gs_thds;
	uint32_t gs_table_depth;
	uint32_t gsprim_buff_depth;
	uint32_t parameter_cache_depth;
	uint32_t double_offchip_lds_buffer;
	uint32_t wave_size;
	uint32_t max_waves_per_simd;
	uint32_t max_scratch_slots_per_cu;
	uint32_t lds_size;
	uint32_t num_sc_per_se;
	uint32_t num_packer_per_sc;
	uint32_t num_tcp_per_sh;
	uint32_t tcp_size_per_cu;
	uint32_t num_sdp_interface;
	uint32_t num_cu_per_sqc;
	uint32_t instruction_cache_size_per_sqc;
	uint32_t scalar_data_cache_size_per_sqc;
	uint32_t tcc_size;
};

union discovery_gc_info {
	struct discovery_gc_info_header header;
	struct discovery_gc_info_v1_0   v1_0;
	struct discovery_gc_info_v1_1   v1_1;
	struct discovery_gc_info_v1_2   v1_2;
	struct discovery_gc_info_v1_3   v1_3;
	struct discovery_gc_info_v2_0   v2_0;
	struct discovery_gc_info_v2_1   v2_1;
};

//                        little-endian: 3 2 1 0
//                                       V R A H
#define HARVEST_TABLE_SIGNATURE       0x56524148
#define HARVEST_TABLE_SIGNATURE_STR   "HARV"

struct discovery_harvest_info_header {
	union magic_32 signature; // HARV
	uint32_t version;
};

struct discovery_harvest_info {
	enum soc15_hwid hardware_id;
	uint8_t ip_instance_number;
	uint8_t reserved;
};

struct discovery_harvest_table {
	struct discovery_harvest_info_header header;
	struct discovery_harvest_info list[32];
};

//                        little-endian: 3 2 1 0
//                                         N C V
#define VCN_INFO_TABLE_SIGNATURE      0x004E4356
#define VCN_INFO_TABLE_SIGNATURE_STR  "VCN"

struct discovery_vcn_info_header {
	union magic_32 signature; // VCN
    uint16_t version_major;
    uint16_t version_minor;
    uint32_t size_bytes;
};
union vcn_fuse_data {
	uint32_t fuse_data;
	struct { uint32_t
		av1_disabled  :0-0 +1,
		vp9_disabled  :1-1 +1,
		hevc_disabled :2-2 +1,
		h264_disabled :3-3 +1,
		reserved     :31-4 +1;
	};	
};
struct discovery_vcn_instance_info_v1_0 {
	uint32_t instance_num; // VCN IP instance number. 0 - VCN0; 1 - VCN1 etc
	union vcn_fuse_data fuse_data;
	uint32_t reserved[2];
};
#define DISCOVERY_VCN_INFO_TABLE_MAX_NUM_INSTANCES 4
struct discovery_vcn_info_v1_0 {
	struct discovery_vcn_info_header header;
	uint32_t num_of_instances; // number of entries used in instance_info below
	struct discovery_vcn_instance_info_v1_0 instance_info[
		DISCOVERY_VCN_INFO_TABLE_MAX_NUM_INSTANCES
	];
	uint32_t reserved[4];
};


//                        little-endian: 3 2 1 0
//                                       L L A M
#define MALL_INFO_TABLE_SIGNATURE     0x4C4C414D
#define MALL_INFO_TABLE_SIGNATURE_STR "MALL"
struct discovery_mall_info_header {
	union magic_32 signature; // MALL
	uint16_t version_major;
	uint16_t version_minor;
	uint32_t size_bytes;
};

struct discovery_mall_info_v1_0 {
	struct discovery_mall_info_header header;
	uint32_t mall_size_per_m;
	uint32_t m_s_present;
	uint32_t m_half_use;
	uint32_t m_mall_config;
	uint32_t reserved[5];
};

struct discovery_mall_info_v2_0 {
	struct discovery_mall_info_header header;
	uint32_t mall_size_per_umc;
	uint32_t reserved[8];
};

union discovery_mall_info {
	struct discovery_mall_info_header header;
	struct discovery_mall_info_v1_0   v1_0;
	struct discovery_mall_info_v2_0   v2_0;
};


#define DISCOVERY_NPS_INFO_TABLE_MAX_NUM_INSTANCES 12

//                        little-endian: 3 2 1 0
//                                         S P N
#define NPS_INFO_TABLE_SIGNATURE      0x0053504E
#define NPS_INFO_TABLE_SIGNATURE_STR  "NPS"
struct discovery_nps_info_header {
	union magic_32 signature; // NPS
	uint16_t version_major;
	uint16_t version_minor;
	uint32_t size_bytes;
};

struct discovery_nps_instance_info_v1_0 {
	uint64_t base_address;
	uint64_t limit_address;
};

struct discovery_nps_info_v1_0 {
	struct discovery_nps_info_header header;
	uint32_t nps_type;
	uint32_t count;
	struct discovery_nps_instance_info_v1_0 instance_info[
		DISCOVERY_NPS_INFO_TABLE_MAX_NUM_INSTANCES
	];
};

#pragma pack(pop) // restore old packing
#endif
