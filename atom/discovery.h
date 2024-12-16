#ifndef DISCOVERY_H
#define DISCOVERY_H

#define HWIP_MAX_INSTANCE 44
#define HW_ID_MAX         300

#define PSP_HEADER_SIZE           256

#define BINARY_SIGNATURE          0x28211407
#define DISCOVERY_TABLE_SIGNATURE 0x53445049
#define GC_TABLE_ID               0x4347
#define HARVEST_TABLE_SIGNATURE   0x56524148
#define VCN_INFO_TABLE_ID         0x004E4356
#define MALL_INFO_TABLE_ID        0x4C4C414D
#define NPS_INFO_TABLE_ID         0x0053504E

enum discovery_tables {
	DISCOVERY_IP_DISCOVERY = 0,
	DISCOVERY_GC           = 1,
	DISCOVERY_HARVEST_INFO = 2,
	DISCOVERY_VCN_INFO     = 3,
	DISCOVERY_MALL_INFO    = 4,
	DISCOVERY_NPS_INFO     = 5,
	DISCOVERY_TOTAL_TABLES = 6,
};

#pragma pack(push, 1) // bios data must use byte alignment

struct discovery_table_info {
	uint16_t offset; 
	uint16_t checksum; // Byte sum of the table 
	uint16_t size;
	uint16_t padding;
};

struct discovery_binary_header {
	struct amd_fw_header fw_header;
	uint32_t binary_signature;
	uint16_t version_major;
	uint16_t version_minor;
	uint16_t binary_checksum; // Byte sum of the binary after this field 
	uint16_t binary_size;
	struct discovery_table_info table_list[DISCOVERY_TOTAL_TABLES];
};

struct ip_die_info {
	uint16_t die_id;
	uint16_t die_offset; // Points to the corresponding die_header structure 
};
union ip_discovery_header_flags_v4 { // reserved in v3
	uint16_t flags;
	struct { uint16_t
		base_addr_64_bit :0-0 +1, // ip structures are using 64 bit base address
		reserved        :15-1 +1;
	};
};
#define IP_DISCOVERY_MAX_NUM_DIES 16
struct ip_discovery_header {
	uint32_t signature; // Table Signature 
	uint16_t version;   // Table Version 
	uint16_t size;      // Table Size 
	uint32_t id;        // Table ID 
	uint16_t num_dies;  // Number of Dies 
	struct ip_die_info die_info[IP_DISCOVERY_MAX_NUM_DIES];
	union ip_discovery_header_flags_v4 flags;
};

struct ip_die_header {
	uint16_t die_id;
	uint16_t num_ips;
	uint16_t hardware_id;    //  max: HW_ID_MAX
	uint8_t instance_number; // max: HWIP_MAX_INSTANCE
	uint8_t num_base_address;
	uint8_t major;
	uint8_t minor;
	uint8_t revision;
};

union ip_harvest {
	uint8_t raw;
	struct { uint8_t
		harvest  :3-0 +1,
		reserved :7-4 +1; 
	};
};
struct ip_v1 {
	struct ip_die_header header;
	union ip_harvest harvest;
	uint32_t base_address[] __counted_by(num_base_address);
};


union ip_hcid_sub {
	uint8_t raw;
	struct { uint8_t
		sub_revision :3-0 +1,
		variant      :7-4 +1;
	};
};
struct ip_v3 {
	struct ip_die_header header;
	union ip_hcid_sub sub;
	uint32_t base_address[] __counted_by(num_base_address);
};
struct ip_v4_64 {
	struct ip_die_header header;
	union ip_hcid_sub sub;
	uint64_t base_address[] __counted_by(num_base_address);
};

union ip_dies {
	struct ip_die_header header;
	struct ip_v1    v1;
	struct ip_v3    v3;
	struct ip_v3    v4_32;
	struct ip_v4_64 v4_64;
};


struct gpu_info_header {
	uint32_t table_id;
	uint16_t version_major;
	uint16_t version_minor;
	uint32_t size;
};


struct gc_info_v1_0 {
	struct gpu_info_header header;

	uint32_t gc_num_se;
	uint32_t gc_num_wgp0_per_sa;
	uint32_t gc_num_wgp1_per_sa;
	uint32_t gc_num_rb_per_se;
	uint32_t gc_num_gl2c;
	uint32_t gc_num_gprs;
	uint32_t gc_num_max_gs_thds;
	uint32_t gc_gs_table_depth;
	uint32_t gc_gsprim_buff_depth;
	uint32_t gc_parameter_cache_depth;
	uint32_t gc_double_offchip_lds_buffer;
	uint32_t gc_wave_size;
	uint32_t gc_max_waves_per_simd;
	uint32_t gc_max_scratch_slots_per_cu;
	uint32_t gc_lds_size;
	uint32_t gc_num_sc_per_se;
	uint32_t gc_num_sa_per_se;
	uint32_t gc_num_packer_per_sc;
	uint32_t gc_num_gl2a;
};

struct gc_info_v1_1 {
	struct gpu_info_header header;

	uint32_t gc_num_se;
	uint32_t gc_num_wgp0_per_sa;
	uint32_t gc_num_wgp1_per_sa;
	uint32_t gc_num_rb_per_se;
	uint32_t gc_num_gl2c;
	uint32_t gc_num_gprs;
	uint32_t gc_num_max_gs_thds;
	uint32_t gc_gs_table_depth;
	uint32_t gc_gsprim_buff_depth;
	uint32_t gc_parameter_cache_depth;
	uint32_t gc_double_offchip_lds_buffer;
	uint32_t gc_wave_size;
	uint32_t gc_max_waves_per_simd;
	uint32_t gc_max_scratch_slots_per_cu;
	uint32_t gc_lds_size;
	uint32_t gc_num_sc_per_se;
	uint32_t gc_num_sa_per_se;
	uint32_t gc_num_packer_per_sc;
	uint32_t gc_num_gl2a;
	uint32_t gc_num_tcp_per_sa;
	uint32_t gc_num_sdp_interface;
	uint32_t gc_num_tcps;
};

struct gc_info_v1_2 {
	struct gpu_info_header header;
	uint32_t gc_num_se;
	uint32_t gc_num_wgp0_per_sa;
	uint32_t gc_num_wgp1_per_sa;
	uint32_t gc_num_rb_per_se;
	uint32_t gc_num_gl2c;
	uint32_t gc_num_gprs;
	uint32_t gc_num_max_gs_thds;
	uint32_t gc_gs_table_depth;
	uint32_t gc_gsprim_buff_depth;
	uint32_t gc_parameter_cache_depth;
	uint32_t gc_double_offchip_lds_buffer;
	uint32_t gc_wave_size;
	uint32_t gc_max_waves_per_simd;
	uint32_t gc_max_scratch_slots_per_cu;
	uint32_t gc_lds_size;
	uint32_t gc_num_sc_per_se;
	uint32_t gc_num_sa_per_se;
	uint32_t gc_num_packer_per_sc;
	uint32_t gc_num_gl2a;
	uint32_t gc_num_tcp_per_sa;
	uint32_t gc_num_sdp_interface;
	uint32_t gc_num_tcps;
	uint32_t gc_num_tcp_per_wpg;
	uint32_t gc_tcp_l1_size;
	uint32_t gc_num_sqc_per_wgp;
	uint32_t gc_l1_instruction_cache_size_per_sqc;
	uint32_t gc_l1_data_cache_size_per_sqc;
	uint32_t gc_gl1c_per_sa;
	uint32_t gc_gl1c_size_per_instance;
	uint32_t gc_gl2c_per_gpu;
};

struct gc_info_v1_3 {
    struct gpu_info_header header;
    uint32_t gc_num_se;
    uint32_t gc_num_wgp0_per_sa;
    uint32_t gc_num_wgp1_per_sa;
    uint32_t gc_num_rb_per_se;
    uint32_t gc_num_gl2c;
    uint32_t gc_num_gprs;
    uint32_t gc_num_max_gs_thds;
    uint32_t gc_gs_table_depth;
    uint32_t gc_gsprim_buff_depth;
    uint32_t gc_parameter_cache_depth;
    uint32_t gc_double_offchip_lds_buffer;
    uint32_t gc_wave_size;
    uint32_t gc_max_waves_per_simd;
    uint32_t gc_max_scratch_slots_per_cu;
    uint32_t gc_lds_size;
    uint32_t gc_num_sc_per_se;
    uint32_t gc_num_sa_per_se;
    uint32_t gc_num_packer_per_sc;
    uint32_t gc_num_gl2a;
    uint32_t gc_num_tcp_per_sa;
    uint32_t gc_num_sdp_interface;
    uint32_t gc_num_tcps;
    uint32_t gc_num_tcp_per_wpg;
    uint32_t gc_tcp_l1_size;
    uint32_t gc_num_sqc_per_wgp;
    uint32_t gc_l1_instruction_cache_size_per_sqc;
    uint32_t gc_l1_data_cache_size_per_sqc;
    uint32_t gc_gl1c_per_sa;
    uint32_t gc_gl1c_size_per_instance;
    uint32_t gc_gl2c_per_gpu;
    uint32_t gc_tcp_size_per_cu;
    uint32_t gc_tcp_cache_line_size;
    uint32_t gc_instruction_cache_size_per_sqc;
    uint32_t gc_instruction_cache_line_size;
    uint32_t gc_scalar_data_cache_size_per_sqc;
    uint32_t gc_scalar_data_cache_line_size;
    uint32_t gc_tcc_size;
    uint32_t gc_tcc_cache_line_size;
};

struct gc_info_v2_0 {
	struct gpu_info_header header;

	uint32_t gc_num_se;
	uint32_t gc_num_cu_per_sh;
	uint32_t gc_num_sh_per_se;
	uint32_t gc_num_rb_per_se;
	uint32_t gc_num_tccs;
	uint32_t gc_num_gprs;
	uint32_t gc_num_max_gs_thds;
	uint32_t gc_gs_table_depth;
	uint32_t gc_gsprim_buff_depth;
	uint32_t gc_parameter_cache_depth;
	uint32_t gc_double_offchip_lds_buffer;
	uint32_t gc_wave_size;
	uint32_t gc_max_waves_per_simd;
	uint32_t gc_max_scratch_slots_per_cu;
	uint32_t gc_lds_size;
	uint32_t gc_num_sc_per_se;
	uint32_t gc_num_packer_per_sc;
};

struct gc_info_v2_1 {
	struct gpu_info_header header;

	uint32_t gc_num_se;
	uint32_t gc_num_cu_per_sh;
	uint32_t gc_num_sh_per_se;
	uint32_t gc_num_rb_per_se;
	uint32_t gc_num_tccs;
	uint32_t gc_num_gprs;
	uint32_t gc_num_max_gs_thds;
	uint32_t gc_gs_table_depth;
	uint32_t gc_gsprim_buff_depth;
	uint32_t gc_parameter_cache_depth;
	uint32_t gc_double_offchip_lds_buffer;
	uint32_t gc_wave_size;
	uint32_t gc_max_waves_per_simd;
	uint32_t gc_max_scratch_slots_per_cu;
	uint32_t gc_lds_size;
	uint32_t gc_num_sc_per_se;
	uint32_t gc_num_packer_per_sc;
	uint32_t gc_num_tcp_per_sh;
	uint32_t gc_tcp_size_per_cu;
	uint32_t gc_num_sdp_interface;
	uint32_t gc_num_cu_per_sqc;
	uint32_t gc_instruction_cache_size_per_sqc;
	uint32_t gc_scalar_data_cache_size_per_sqc;
	uint32_t gc_tcc_size;
};

union discovery_gc_info {
	struct gpu_info_header header;
	struct gc_info_v1_0  v1_0;
	struct gc_info_v1_1  v1_1;
	struct gc_info_v1_2  v1_2;
	struct gc_info_v1_3  v1_3;
	struct gc_info_v2_0  v2_0;
	struct gc_info_v2_1  v2_1;
};

struct discovery_harvest_info_header {
	uint32_t signature;
	uint32_t version;
};

struct discovery_harvest_info {
	uint16_t hardware_id;
	uint8_t ip_instance_number;
	uint8_t reserved;
};

struct discovery_harvest_table {
	struct discovery_harvest_info_header header;
	struct discovery_harvest_info list[32];
};

struct mall_info_header {
	uint32_t table_id;
	uint16_t version_major;
	uint16_t version_minor;
	uint32_t size_bytes;
};

struct mall_info_v1_0 {
	struct mall_info_header header;
	uint32_t mall_size_per_m;
	uint32_t m_s_present;
	uint32_t m_half_use;
	uint32_t m_mall_config;
	uint32_t reserved[5];
};

struct mall_info_v2_0 {
	struct mall_info_header header;
	uint32_t mall_size_per_umc;
	uint32_t reserved[8];
};


struct vcn_info_header {
    uint32_t table_id;
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
struct vcn_instance_info_v1_0 {
	uint32_t instance_num; // VCN IP instance number. 0 - VCN0; 1 - VCN1 etc
	union vcn_fuse_data fuse_data;
	uint32_t reserved[2];
};
#define VCN_INFO_TABLE_MAX_NUM_INSTANCES 4
struct vcn_info_v1_0 {
	struct vcn_info_header header;
	uint32_t num_of_instances; // number of entries used in instance_info below
	struct vcn_instance_info_v1_0 instance_info[VCN_INFO_TABLE_MAX_NUM_INSTANCES];
	uint32_t reserved[4];
};

#define NPS_INFO_TABLE_MAX_NUM_INSTANCES 12

struct nps_info_header {
	uint32_t table_id;
	uint16_t version_major;
	uint16_t version_minor;
	uint32_t size_bytes; // size of the entire header+data in bytes = 0x000000D4 (212) 
};

struct nps_instance_info_v1_0 {
	uint64_t base_address;
	uint64_t limit_address;
};

struct nps_info_v1_0 {
	struct nps_info_header header;
	uint32_t nps_type;
	uint32_t count;
	struct nps_instance_info_v1_0 instance_info[NPS_INFO_TABLE_MAX_NUM_INSTANCES];
};

#pragma pack(pop) // restore old packing
#endif
