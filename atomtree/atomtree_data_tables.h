/*******************************************************************************
CPU AtomBIOS directory tree, atomtree, is a large tree of C structs with the
intent to abstract away AtomBIOS offset/pointer crawling and bounds checking.
If a given AtomBIOS table has table offsets pointing to other tables, they will
automatically be crawled and cpu-pointed-to by atomtree; otherwise if a given
AtomBIOS table either dead-ends, or responsibly allocates their children, then
atomtree will just point to them instead with minimised interference as
reasonably possible.


If there exists multiple versions of an atom table, then there is an enum-union
pair to look up and walk the correct branch. For example,
if (atree->data_table.vram_info.ver == v25)
	atree->data_table.vram_info.v25.vram_module[0].gddr6_mr8 = mr8;
	// bios edit
you could then write atree.bios to a file; provided that you've done your
sanity passes like the CRC checksum.

future ideas:
*large:
	* fdisk/parted like allocation viewer? atombios creator?
	* live i2c smu communicator?

*******************************************************************************/

/*******************************************************************************
*******************************************************************************/

#ifndef ATOMTREE_DATA_TABLES_H
#define ATOMTREE_DATA_TABLES_H

struct atomtree_smc_dpm_info {
	enum atomtree_common_version ver;
	union {
		void* leaves; // nonzero if populated
		struct atom_common_table_header* table_header;

		struct atom_smc_dpm_info_v4_1* v4_1;
		struct atom_smc_dpm_info_v4_3* v4_3;
		struct atom_smc_dpm_info_v4_4* v4_4;
		struct atom_smc_dpm_info_v4_5* v4_5;
		struct atom_smc_dpm_info_v4_6* v4_6;
		struct atom_smc_dpm_info_v4_7* v4_7;
		struct atom_smc_dpm_info_v4_8* v4_8;
		struct atom_smc_dpm_info_v4_9* v4_9;
		struct atom_smc_dpm_info_v4_10* v4_10;
		struct atom_smc_dpm_info_table_13_0_7* v5_0;
	};
};

struct atomtree_firmware_info {
	enum atomtree_common_version ver;
	union {
		void* leaves; // nonzero if populated
		struct atom_common_table_header* table_header;

		struct atom_firmware_info_v1_0* v1_0;
		struct atom_firmware_info_v1_2* v1_2;
		struct atom_firmware_info_v1_3* v1_3;
		struct atom_firmware_info_v1_4* v1_4;
		struct atom_firmware_info_v2_1* v2_1;
		struct atom_firmware_info_v2_2* v2_2;
		struct atom_firmware_info_v3_1* v3_1;
		struct atom_firmware_info_v3_2* v3_2;
		struct atom_firmware_info_v3_3* v3_3;
		struct atom_firmware_info_v3_4* v3_4;
	};
};
struct atomtree_lcd_info {
	enum atomtree_common_version ver;
	union {
		void* leaves; // nonzero if populated
		struct atom_common_table_header* table_header;

		//struct atom_lcd_info_v1_3* v1_3; // atombios.h
		struct atom_lcd_info_v2_1* v2_1;
	};
};

struct atomtree_smu_info {
	// TODO explode the versions into their own atomtree entities?
	void* smugolden; // not all smu_info versions have these
	void* smuinit;

	enum atomtree_common_version ver;
	union {
		void* leaves; // nonzero if populated
		struct atom_common_table_header* table_header;

		struct atom_smu_info_v3_1* v3_1;
		struct atom_smu_info_v3_2* v3_2;
		struct atom_smu_info_v3_3* v3_3;
		//struct atom_smu_info_v3_4* v3_4;
		struct atom_smu_info_v3_5* v3_4; // bios reports 244 bytes. v3_5 is 240 bytes.
		struct atom_smu_info_v3_5* v3_5;
		struct atom_smu_info_v3_6* v3_6;
		struct atom_smu_info_v4_0* v4_0;
	};
};



struct atomtree_vram_usagebyfirmware {
	enum atomtree_common_version ver;
	union {
		void* leaves; // nonzero if populated
		struct atom_common_table_header* table_header;

		struct vram_usagebyfirmware_v2_1* v2_1;
		struct vram_usagebyfirmware_v2_2* v2_2;
	};
};

struct atomtree_gpio_pin_lut {
	uint16_t num_gpio_pins;

	enum atomtree_common_version ver;
	union {
		void* leaves; // nonzero if populated
		struct atom_common_table_header* table_header;
		struct atom_gpio_pin_lut_v2_1* v2_1;
	};
};


struct atomtree_gfx_info {
	// TODO explode the versions into their own atomtree entities?
	void* gcgolden; // not all gfx_info versions have this

	enum atomtree_common_version ver;
	union {
		void* leaves; // nonzero if populated
		struct atom_common_table_header* table_header;

		struct atom_gfx_info_v2_2* v2_2;
		struct atom_gfx_info_v2_3* v2_3;
		struct atom_gfx_info_v2_4* v2_4;
		struct atom_gfx_info_v2_5* v2_5; // derived from 2.7
		struct atom_gfx_info_v2_5* v2_6; // 2.6 has same byte count as 2.5
		struct atom_gfx_info_v2_7* v2_7;
		struct atom_gfx_info_v3_0* v3_0;
	};
};


struct atomtree_powerplaytable {
	// What the fuck, AMD.

	//struct PPTable_t* smc_pptable;
	uint8_t* powerplay_table_ver; // as seen next to atom_common_table_header
	//uint8_t* overdrive_table_ver; // hopefully unnecessary
	//uint8_t* powersaving_table_ver;
	uint32_t* smc_pptable_ver; // as seen in driver_if*.h
	enum atomtree_common_version ver;
	union {
		void* leaves; // nonzero if populated
		struct atom_common_table_header* table_header;
		struct smu_powerplay_table_header* pphead;

		struct smu_11_0_powerplay_table* v12_0;
		struct smu_11_0_7_powerplay_table* v15_0;
		// struct smu_13_0_7_powerplay_table* v15_0; // navi3?

	};
		/*
		struct smu_13_0_0_powerplay_table* navi3;

		// what's the difference between 13.0.7 and 13.0.0?
		//struct smu_13_0_7_powerplay_table* plum_bonito; //navi31


		// 13_0 is different from 13_0_0, and 13_0 is only used in aldebaran
		// 13_0 has more stuff than 13_0_0; I wonder if they can be spliced
		//struct smu_13_0_powerplay_table* aldebaran;

		struct ATOM_Vega10_POWERPLAYTABLE* vega10;
		*/
/*
consider include/pptable.h

firmware headers: amdgpu/amdgpu_ucode.h
	we can probably get the smu version from this stuff
--
pp_dpm_load_fw
smu_load_microcode,
--


pptable is obtained via driver, via amdgpu_sriov_vf(adev)
hdr = (const struct smc_firmware_header_v1_0 *) adev->pm.fw->data
smu->smu_table.boot_values.pp_table_id

amdgpu_smu.h:481 defines struct smu_context
what the fuck is struct firmware?

smu_v11_0.c:362:
	smu->smu_table.power_play_table = table;
	smu->smu_table.power_play_table_size = size;
  but power_play_table is void*

smu_v11_0_setup_pptable
navi10_setup_pptable
ppt_funcs.setup_pptable (instance is navi10_ppt_funcs)
smu_setup_pptable

struct smu_11_0_powerplay_table defined in smu_v11_0_pptable.h
*/
};

enum register_block_type:uint8_t {
	reg_block_unknown,
	reg_block_mem_adjust,
	reg_block_mem_clk_patch,
	reg_block_mc_tile_adjust,
	reg_block_mc_phy_init,
	reg_block_last,
};
enum common_register_sequence:uint8_t {
	common_set_unknown,

	// reg_block_mem_adjust:
	mem_adjust_set_terascale2_ddr3,  // Caicos, Turks
	mem_adjust_set_terascale2_gddr5_type3, // Turks
	mem_adjust_set_terascale2_gddr5_type4, // Barts
	mem_adjust_set_terascale3_gddr5, // Cayman
	mem_adjust_set_gcn1_gddr5_type1, // Oland, Cape Verde
	mem_adjust_set_gcn1_gddr5_type2, // Pitcairn
	mem_adjust_set_gcn1_gddr5_type3, // Tahiti
	mem_adjust_set_gcn1_gddr5_type4, // Exo
	mem_adjust_set_gcn2_gddr5, // Bonaire, Hawaii, Grenada
	mem_adjust_set_gcn3_gddr5, // Tonga
	mem_adjust_set_gcn3_hbm1,  // Fiji
	mem_adjust_set_gcn4_gddr5_type1, // Polaris
	mem_adjust_set_gcn4_gddr5_type2, // Polaris

	// reg_block_mem_clk_patch:
	timings_set_islands_ddr3,
	timings_set_islands_gddr5,
	timings_set_fiji,
	timings_set_polaris,
	timings_set_vega10,
	timings_set_vega21,
	timings_set_navi1,

	// reg_block_mc_tile_adjust:
	mc_tile_adjust_set_gcn3_gddr5,
	mc_tile_adjust_set_gcn4_gddr5,

	// reg_block_mc_phy_init:
	mc_phy_init_set_gcn3_hbm1,  // Fiji
	mc_phy_init_set_gcn3_gddr5, // Tonga
	mc_phy_init_set_gcn4_gddr5_type1, // all other Polaris
	mc_phy_init_set_gcn4_gddr5_type2, // polaris20
};

#define ATOMTREE_MC_REG_MAX  24 // keep score.
// Hawaii XT is 20; Sapphire.RX580.8192.170320.rom is 24
struct atomtree_init_reg_block {
	struct atom_init_reg_block* leaves; // nonzero if populated

	uint8_t num_index;
	struct atom_init_reg_index_format* register_index;

	uint8_t num_data_blocks; // atom_init_reg_block's RegDataBuf
	uint8_t num_data_entries; // atom_reg_setting_data_block's reg_data
	uint16_t data_block_element_size;
	struct atom_reg_setting_data_block* data_blocks[ATOMTREE_MC_REG_MAX];

	// init_reg_block is a generalised structure format. The meaning of the data
	// depends on the register_index against an definition lookup table.
	// However, register_index is hard to understand, but there are common
	// sequences.
	enum register_block_type reg_type; // type of table
	enum common_register_sequence reg_set; // denote a common sequence
	union {
		void* data_sets;

		// reg_block_mem_adjust:
		struct mem_adjust_set_terascale2_ddr3*  mem_adjust_set_terascale2_ddr3;
		struct mem_adjust_set_terascale2_gddr5_type3*
			mem_adjust_set_terascale2_gddr5_type3;
		struct mem_adjust_set_terascale2_gddr5_type4*
			mem_adjust_set_terascale2_gddr5_type4;
		struct mem_adjust_set_terascale3_gddr5* mem_adjust_set_terascale3_gddr5;
		struct mem_adjust_set_gcn1_gddr5_type1* mem_adjust_set_gcn1_gddr5_type1;
		struct mem_adjust_set_gcn1_gddr5_type2* mem_adjust_set_gcn1_gddr5_type2;
		struct mem_adjust_set_gcn1_gddr5_type3* mem_adjust_set_gcn1_gddr5_type3;
		struct mem_adjust_set_gcn1_gddr5_type4* mem_adjust_set_gcn1_gddr5_type4;
		struct mem_adjust_set_gcn2_gddr5* mem_adjust_set_gcn2_gddr5;
		struct mem_adjust_set_gcn3_gddr5* mem_adjust_set_gcn3_gddr5;
		struct mem_adjust_set_gcn3_hbm1*  mem_adjust_set_gcn3_hbm1;
		struct mem_adjust_set_gcn4_gddr5_type1* mem_adjust_set_gcn4_gddr5_type1;
		struct mem_adjust_set_gcn4_gddr5_type2* mem_adjust_set_gcn4_gddr5_type2;

		// reg_block_mem_clk_patch:
		struct timings_set_islands_ddr3*  timings_set_islands_ddr3;
		struct timings_set_islands_gddr5* timings_set_islands_gddr5;
		struct timings_set_fiji*    timings_set_fiji;
		struct timings_set_polaris* timings_set_polaris;

		// reg_block_mc_tile_adjust:
		struct mc_tile_adjust_set_gcn3_gddr5* mc_tile_adjust_set_gcn3_gddr5;
		struct mc_tile_adjust_set_gcn4_gddr5* mc_tile_adjust_set_gcn4_gddr5;

		// reg_block_mc_phy_init:
		struct mc_phy_init_set_gcn3_hbm1* mc_phy_init_set_gcn3_hbm1;
		struct mc_phy_init_set_gcn3_gddr5* mc_phy_init_set_gcn3_gddr5;
		struct mc_phy_init_set_gcn4_gddr5_type1*
			mc_phy_init_set_gcn4_gddr5_type1;
		struct mc_phy_init_set_gcn4_gddr5_type2*
			mc_phy_init_set_gcn4_gddr5_type2;
	};
};
#define ATOMTREE_UMC_REG_MAX 23 // keep score. navi10 has 23
struct atomtree_umc_init_reg_block {
	struct atom_umc_init_reg_block* leaves; // nonzero if populated

	union atom_umc_register_addr_info_access* register_info;
	uint8_t num_info;

	uint8_t num_data_blocks; // atom_umc_init_reg_block's umc_reg_setting_list
	uint8_t num_data_entries; // atom_umc_reg_setting_data_block's umc_reg_data
	uint16_t data_block_element_size;
	struct atom_umc_reg_setting_data_block* data_blocks[ATOMTREE_UMC_REG_MAX];
};

/*
struct atomtree_gddr6_dram_data_remap { //TODO do we need this?
	struct atom_gddr6_bit_byte_remap* leaves; // nonzero if populated

	//uint32_t table_size;
	//uint8_t phyintf_ck_inverted[8];	 //UMC_PHY_PHYINTF_CNTL.INV_CK
	//struct atom_gddr6_bit_byte_remap bit_byte_remap[16];
};
*/

struct atomtree_vram_module {
	union {
		void* leaves;
		struct atom_vram_module_v1*   v1_1;
		struct atom_vram_module_v2*   v1_2;
		struct atom_vram_module_v3*   v1_3;
		struct atom_vram_module_v4*   v1_4;
		struct atom_vram_module_v5*   v1_5;
		struct atom_vram_module_v6*   v1_6;
		struct atom_vram_module_v7*   v1_7;
		struct atom_vram_module_v8*   v1_8;
		struct atom_vram_module_v9*   v1_9;
		struct atom_vram_module_v10*  v1_10;
		struct atom_vram_module_v11*  v1_11;
		struct atom_vram_module_v3_0* v3_0;
	};
	enum atomtree_common_version vram_module_ver;

	enum atomtree_common_version gmc_bitfields_ver;

	enum atomtree_common_version memory_timing_format_ver;
	uint8_t num_memory_timing_format; // v1.3 ~ v1.6

	// v3.0
	void* dram_info;
	void* mem_tuning;
	void* tmrs_seq;
};

#define ATOMTREE_VRAM_MODULES_MAX (3+1) // keep score.
struct atomtree_vram_info_v1_2 {
	struct atom_vram_info_v1_2* leaves; // nonzero if populated

	enum atomtree_common_version vram_module_ver;
	struct atomtree_vram_module vram_modules[ATOMTREE_VRAM_MODULES_MAX];
};

struct atomtree_vram_info_v1_3 {
	struct atom_vram_info_v1_3* leaves; // nonzero if populated

	struct atomtree_init_reg_block mem_adjust_table;
	struct atomtree_init_reg_block mem_clk_patch;

	enum atomtree_common_version vram_module_ver;
	struct atomtree_vram_module vram_modules[ATOMTREE_VRAM_MODULES_MAX];
};

struct atomtree_vram_info_v1_4 {
	struct atom_vram_info_v1_4* leaves; // nonzero if populated

	struct atomtree_init_reg_block mem_adjust_table;
	struct atomtree_init_reg_block mem_clk_patch;

	enum atomtree_common_version vram_module_ver;
	struct atomtree_vram_module vram_modules[ATOMTREE_VRAM_MODULES_MAX];
};

struct atomtree_vram_info_header_v2_1 {
	struct atom_vram_info_header_v2_1* leaves; // nonzero if populated

	struct atomtree_init_reg_block mem_adjust_table;
	struct atomtree_init_reg_block mem_clk_patch;
	struct atomtree_init_reg_block per_byte_preset;

	enum atomtree_common_version vram_module_ver;
	struct atomtree_vram_module vram_modules[ATOMTREE_VRAM_MODULES_MAX];
};

struct atomtree_vram_info_header_v2_2 {
	struct atom_vram_info_header_v2_2* leaves; // nonzero if populated

	struct atomtree_init_reg_block mem_adjust_table;

	struct atomtree_init_reg_block mem_clk_patch;

	struct atomtree_init_reg_block mc_tile_adjust;
	struct atomtree_init_reg_block mc_phy_init;
	struct mc_atom_dram_data_remap* dram_data_remap;

	enum atomtree_common_version vram_module_ver;
	struct atomtree_vram_module vram_modules[ATOMTREE_VRAM_MODULES_MAX];
};

struct atomtree_vram_info_header_v2_3 {
	struct atom_vram_info_header_v2_3* leaves; // nonzero if populated

	struct atomtree_umc_init_reg_block mem_adjust_table;

	struct atomtree_umc_init_reg_block mem_clk_patch;
	bool uses_vega21_timings;
	// TODO hoisted method stays until address sequence can be figured for
	// atomtree_umc_init_reg_block (see atomtree_init_reg_block).
	union {
		void* mem_timings;
		struct timings_set_vega10_timings* vega10;
		struct timings_set_vega21_timings* vega21;
	};
	uint8_t* num_timing_straps;

	struct atomtree_umc_init_reg_block mc_tile_adjust;
	struct atomtree_umc_init_reg_block mc_phy_init;
	//struct atom_gddr6_dram_data_remap* dram_data_remap;
	struct umc_atom_dram_data_remap* dram_data_remap;
	void* hbm_tmrs; // TODO: what is this? HBM timings?
	struct atomtree_umc_init_reg_block post_ucode_init;

	enum atomtree_common_version vram_module_ver;
	struct atomtree_vram_module vram_modules[ATOMTREE_VRAM_MODULES_MAX];
};

struct atomtree_vram_info_header_v2_4 {
	struct atom_vram_info_header_v2_4* leaves; // nonzero if populated

	struct atomtree_umc_init_reg_block mem_adjust_table;

	struct atomtree_umc_init_reg_block mem_clk_patch;
	// TODO hoisted method stays until address sequence can be figured for
	// atomtree_umc_init_reg_block (see atomtree_init_reg_block).
	struct timings_set_navi1* navi1_gddr6_timings;
	uint8_t* num_timing_straps;

	struct atomtree_umc_init_reg_block mc_tile_adjust;
	struct atomtree_umc_init_reg_block mc_phy_init;

	// probably not gddr6 remap cause data looks significantly different in
	// navi10, vs nav21 and navi31
	//struct atom_gddr6_dram_data_remap* dram_data_remap;
	void* dram_data_remap;

	struct atomtree_umc_init_reg_block post_ucode_init;

	enum atomtree_common_version vram_module_ver;
	struct atomtree_vram_module vram_modules[ATOMTREE_VRAM_MODULES_MAX];
};

struct atomtree_vram_info_header_v2_5 {
	struct atom_vram_info_header_v2_5* leaves; // nonzero if populateda
	struct atomtree_umc_init_reg_block mem_adjust_table;

	struct atom_gddr6_ac_timing_v2_5* gddr6_ac_timings; // is an array
	uint8_t gddr6_acstrap_count;

	struct atomtree_umc_init_reg_block mc_tile_adjust;
	struct atomtree_umc_init_reg_block mc_phy_init;
	struct atom_gddr6_dram_data_remap* dram_data_remap;

	struct atomtree_umc_init_reg_block post_ucode_init;
	struct atomtree_umc_init_reg_block strobe_mode_patch;

	enum atomtree_common_version vram_module_ver;
	struct atomtree_vram_module vram_modules[ATOMTREE_VRAM_MODULES_MAX];
};

struct atomtree_vram_info_header_v2_6 {
	struct atom_vram_info_header_v2_6* leaves; // nonzero if populated

	struct atomtree_umc_init_reg_block mem_adjust_table;
	struct atomtree_umc_init_reg_block mem_clk_patch;
	struct atomtree_umc_init_reg_block mc_tile_adjust;
	struct atomtree_umc_init_reg_block mc_phy_init;
	struct atom_gddr6_dram_data_remap* dram_data_remap;
	void* tmrs_seq;
	struct atomtree_umc_init_reg_block post_ucode_init;

	enum atomtree_common_version vram_module_ver;
	struct atomtree_vram_module vram_modules[ATOMTREE_VRAM_MODULES_MAX];
};

struct atomtree_vram_info_header_v3_0 { // TODO figure out child tables
	struct atom_vram_info_header_v3_0* leaves; // nonzero if populated

	void* mem_tuning;
	void* dram_info;
	void* tmrs_seq;
	struct atomtree_umc_init_reg_block mc_init; // phy init? reg block anyway?
	struct atom_gddr6_dram_data_remap* dram_data_remap;
	struct atomtree_umc_init_reg_block umc_emuinit; //TODO this is a guess
	void* rsvd_tables[2]; // reserved_sub_table_offset

	enum atomtree_common_version vram_module_ver;
	struct atomtree_vram_module vram_modules[ATOMTREE_VRAM_MODULES_MAX];
};

struct atomtree_vram_info {
	union {
		void* leaves;
		struct atom_common_table_header* table_header;
	};

	enum atomtree_common_version ver;
	union {
		struct atomtree_vram_info_v1_2 v1_2;
		struct atomtree_vram_info_v1_3 v1_3;
		struct atomtree_vram_info_v1_4 v1_4;
		struct atomtree_vram_info_header_v2_1 v2_1;
		struct atomtree_vram_info_header_v2_2 v2_2;
		struct atomtree_vram_info_header_v2_3 v2_3;
		struct atomtree_vram_info_header_v2_4 v2_4;
		struct atomtree_vram_info_header_v2_5 v2_5;
		struct atomtree_vram_info_header_v2_6 v2_6;
		struct atomtree_vram_info_header_v3_0 v3_0;
	};
};

struct atomtree_voltage_object_v4 {
	union atom_voltage_object_v4* voltage_object;
	uint16_t lut_entries; // has entries if i2c or gpio
};

#define ATOMTREE_VOLTAGE_OBJECTS_MAX 8 // keep score. navi10 has 8
struct atomtree_voltageobject_info_v4_1 {
	struct atom_voltage_objects_info_v4_1* leaves;

	uint16_t num_voltage_objects;
	struct atomtree_voltage_object_v4 voltage_objects[
		ATOMTREE_VOLTAGE_OBJECTS_MAX
	];
};


struct atomtree_voltageobject_info {
	union {
		void* leaves; // nonzero if populated
		struct atom_common_table_header* table_header;
	};

	enum atomtree_common_version ver;
	union {
		struct atomtree_voltageobject_info_v4_1 v4_1;
	};
};

struct atomtree_sw_datatable {
	enum atomtree_common_version ver; // meh
	union {
		void* leaves; // nonzero if populated
		struct atom_common_table_header* table_header;
	};
};
struct atomtree_master_datatable_v1_1 {
	union {
		struct atom_common_table_header* table_header;
		struct atom_master_data_table_v1_1* leaves; // nonzero if populated
	};

	// TODO relate these uint16t stuff to their tables.
	// a lot of the question associations are low effort.

	struct atomtree_sw_datatable* utilitypipeline; //??

	//struct atom_multimedia_info_v2_1* multimedia_info;
	struct atom_multimedia_capability_info* multimedia_capability_info;
	struct atom_multimedia_config_info* multimedia_config_info;
	struct atom_standard_vesa_timing* vesa_timing;

	struct atomtree_firmware_info firmwareinfo;

	void* palette_data; // struct atom_dac_info ?

	struct atomtree_lcd_info lcd_info;

	//dig_transmitter_info_header_v3_1  atom_tmds_info ?
	void* dig_transmitter_info;

	struct atomtree_smu_info smu_info;

	void* supported_devices_info; // atom_supported_devices_info
	void* gpio_i2c_info; // atom_gpio_i2c_info ?

	struct atomtree_vram_usagebyfirmware vram_usagebyfirmware;
	struct atomtree_gpio_pin_lut gpio_pin_lut;

	void* vesa_to_internal_mode; // atom_vesa_to_internal_mode_lut ?

	struct atomtree_gfx_info gfx_info;
	struct atomtree_powerplaytable powerplayinfo;

	// atom_gpu_virtualization_info_v2_1  compassionate_data ?
	void* gpu_virtualization_info;
	void* save_restore_info; // ??  atom_display_device_priority_info ?
	void* ppll_ss_info; // usure
	void* oem_info; // atom_oem_info ?
	void* xtmds_info; // atom_xtmds_info ?
	void* mclk_ss_info; // ??  atom_asic_mvdd_info ?
	void* object_header; // atom_object_header ?
	void* indirect_io_access; // struct indirect_io_access ?
	void* mc_init_parameter; // atom_mc_init_param_table ?
	void* asic_vddc_info; // unsure
	void* asic_internal_ss_info; // atom_asic_internal_ss_info
	void* tv_video_mode;  // atom_disp_out_info ? atom_bios_int_tvstd_mode?

	struct atomtree_vram_info vram_info;

	// atom_memory_training_info  ASIC_MVDDQ_Info?
	void* memory_training_info;
	void* integrated_system_info;
	void* asic_profiling_info;

	struct atomtree_voltageobject_info voltageobject_info;

	void* power_source_info;
	void* service_info;
};

struct atomtree_master_datatable_v2_1 {
	union {
		struct atom_common_table_header* table_header;
		struct atom_master_data_table_v2_1* leaves; // nonzero if populated
	};

	// TODO relate these uint16t stuff to their tables.
	struct atomtree_sw_datatable* utilitypipeline; //??

	struct atom_multimedia_info_v2_1* multimedia_info;
	struct atomtree_smc_dpm_info smc_dpm_info;
	struct atomtree_firmware_info firmwareinfo;
	struct atomtree_lcd_info lcd_info;
	struct atomtree_smu_info smu_info;
	struct atomtree_vram_usagebyfirmware vram_usagebyfirmware;
	struct atomtree_gpio_pin_lut gpio_pin_lut;
	struct atomtree_gfx_info gfx_info;

	struct atomtree_powerplaytable powerplayinfo;

	uint16_t displayobjectinfo;
	uint16_t indirectioaccess;
	uint16_t umc_info;
	uint16_t dce_info;

	struct atomtree_vram_info vram_info;

	struct atomtree_voltageobject_info voltageobject_info;

	// these aren't defined anywhere in AMDGPU.
	struct atomtree_sw_datatable sw_datatable3;
	struct atomtree_sw_datatable sw_datatable5;
	struct atomtree_sw_datatable sw_datatable7;
	struct atomtree_sw_datatable sw_datatable9;
	struct atomtree_sw_datatable sw_datatable10;
	struct atomtree_sw_datatable sw_datatable13;
	struct atomtree_sw_datatable sw_datatable16;
	struct atomtree_sw_datatable sw_datatable17;
	struct atomtree_sw_datatable sw_datatable18;
	struct atomtree_sw_datatable sw_datatable19;
	struct atomtree_sw_datatable sw_datatable20;
	struct atomtree_sw_datatable sw_datatable21;
	struct atomtree_sw_datatable sw_datatable25;
	struct atomtree_sw_datatable sw_datatable26;
	struct atomtree_sw_datatable sw_datatable29;
	struct atomtree_sw_datatable sw_datatable33;
	struct atomtree_sw_datatable sw_datatable34;
};

struct atomtree_master_datatable {
	union {
		void* leaves; // nonzero if populated
		struct atom_common_table_header* table_header;
	};

	enum atomtree_common_version ver;
	union {
		struct atomtree_master_datatable_v1_1 v1_1;
		struct atomtree_master_datatable_v2_1 v2_1;
	};
};

#endif
