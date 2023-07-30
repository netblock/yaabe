/*******************************************************************************
CPU AtomBIOS directory tree, or atomtree for short is a large tree of
struct-based cpu pointers with the intent to abstract away AtomBIOS
offset/pointer crawling. If a given AtomBIOS table has table offsets pointing
to other tables, they will automatically be crawled and cpu-pointed-to by
atomtree; otherwise if a given AtomBIOS table either dead-ends, or responsibly
allocates their children, then atomtree will just point to them instead with
minimised interference as reasonably possible.


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

*small:
	* do we really care about dot and dotdot?
	* make the the population code be agnostic to its table parent for dotdot?
		* void*?
	* enum type for the function returns? error tolerance; politely warn.
	* consolodiate content-revision-based commons and only differentiate the
	  when they actually differ?
		* vram_info.f2.mem_adjust_pertile
		* vram_info.f2.c5.gddr6_ac_timings
*******************************************************************************/

/*******************************************************************************
*******************************************************************************/

#ifndef ATOMTREE_DATA_TABLES_H
#define ATOMTREE_DATA_TABLES_H
#include <atomfirmware.h>
#include <powerplay.h>

#include "atomtree_common.h"




struct atomtree_smc_dpm_info {
	struct atomtree_smc_dpm_info* dot;
	struct atomtree_master_datatable_v2_1* dotdot;

	enum atomtree_common_version ver;
	union {
		void* leaves; // nonzero if populated
		struct atom_common_table_header* table_header;

		struct atom_smc_dpm_info_v4_1* v4_1;
		//struct atom_smc_dpm_info_v4_2* v4_2; // doesn't exist?
		struct atom_smc_dpm_info_v4_3* v4_3;
		struct atom_smc_dpm_info_v4_4* v4_4;
		struct atom_smc_dpm_info_v4_5* v4_5;
		struct atom_smc_dpm_info_v4_6* v4_6;
		struct atom_smc_dpm_info_v4_7* v4_7;
		struct atom_smc_dpm_info_v4_8* v4_8;
		struct atom_smc_dpm_info_v4_9* v4_9;
		struct atom_smc_dpm_info_v4_10* v4_10;
		//struct atom_smc_dpm_info_table_13_0_7 v5_0; // BoardTable_t
	};
};

struct atomtree_firmware_info {
	struct atomtree_firmware_info* dot;
	struct atomtree_master_datatable_v2_1* dotdot;

	enum atomtree_common_version ver;
	union {
		void* leaves; // nonzero if populated
		struct atom_common_table_header* table_header;

		struct atom_firmware_info_v3_1* v3_1;
		struct atom_firmware_info_v3_2* v3_2;
		struct atom_firmware_info_v3_3* v3_3;
		struct atom_firmware_info_v3_4* v3_4;
	};
};

struct atomtree_smu_info {
	// TODO explode the versions into their own atomtree entities?
	struct atomtree_smu_info* dot;
	struct atomtree_master_datatable_v2_1* dotdot;

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
		struct atom_smu_info_v3_5* v3_5;
		struct atom_smu_info_v3_6* v3_6;
		struct atom_smu_info_v4_0* v4_0;
    };
};



struct atomtree_vram_usagebyfirmware {
	struct atomtree_vram_usagebyfirmware* dot;
	struct atomtree_master_datatable_v2_1* dotdot;

	enum atomtree_common_version ver;
	union {
		void* leaves; // nonzero if populated
		struct atom_common_table_header* table_header;

		struct vram_usagebyfirmware_v2_1* v2_1;
		struct vram_usagebyfirmware_v2_2* v2_2;
	};
};


struct atomtree_gfx_info {
	// TODO explode the versions into their own atomtree entities?
	struct atomtree_gfx_info* dot;
	struct atomtree_master_datatable_v2_1* dotdot;

	void* gcgolden; // not all gfx_info versions have this

	enum atomtree_common_version ver;
    union {
        void* leaves; // nonzero if populated
        struct atom_common_table_header* table_header;

		struct atom_gfx_info_v2_2* v2_2;
		struct atom_gfx_info_v2_3* v2_3;
		struct atom_gfx_info_v2_4* v2_4;
		struct atom_gfx_info_v2_7* v2_7;
		struct atom_gfx_info_v3_0* v3_0;
    };
};

struct pp_common_table_header {
	struct atom_common_table_header table_header;
	int8_t  table_revision;
	uint16_t table_size;
};

struct atomtree_powerplaytable {
	// What the fuck, AMD.

	struct atomtree_powerplaytable* dot;
    struct atomtree_master_datatable_v2_1* dotdot;

	//struct PPTable_t* smc_pptable;
	//enum pp_rec_ver; // reccomend a path out of this hell
	enum atomtree_common_version ver;
	union {
		void* leaves; // nonzero if populated
        struct atom_common_table_header* table_header;
		struct pp_common_table_header* pphead;

		struct smu_11_0_powerplay_table* s11;
		struct smu_11_0_powerplay_table* v12_0;
		struct smu_11_0_powerplay_table* navi1;

		/*
		struct smu_13_0_0_powerplay_table* v15_0;
		struct smu_13_0_0_powerplay_table* s1300;
		struct smu_13_0_0_powerplay_table* navi2;
		struct smu_13_0_0_powerplay_table* navi3;

		// what's the difference between 13.0.7 and 13.0.0?
		//struct smu_13_0_7_powerplay_table* plum_bonito; //navi31


		// 13_0 is different from 13_0_0, and 13_0 is only used in aldebaran
		// 13_0 has more stuff than 13_0_0; I wonder if they can be spliced
		//struct smu_13_0_powerplay_table* aldebaran;

		struct ATOM_Vega10_POWERPLAYTABLE* vega10;
		*/
	};
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

// 64 is just atomtree allocation; real number is going to be less than or
// equal to umc_reg_num, I believe.
#define ATOMTREE_UMC_REG_NUM 64
struct atomtree_umc_init_reg_block{
	struct atom_umc_init_reg_block* leaves; // nonzero if populated // nonzero if populated

	struct atomtree_umc_init_reg_block* dot;
	struct atomtree_vram_info* dotdot;

	union {
		uint16_t* umc_reg_num;
		uint16_t* umc_number_of_registers;
	};

	union atom_umc_register_addr_info_access* umc_reg_list;
	uint16_t umc_reg_list_size;

	struct atom_umc_reg_setting_data_block* \
		umc_reg_setting_list[ATOMTREE_UMC_REG_NUM];
	uint16_t umc_reg_setting_list_length;
	uint16_t umc_reg_setting_list_element_size;
};

/*
struct atomtree_gddr6_dram_data_remap { //TODO do we need this?
	struct atomtree_gddr6_dram_data_remap* dot;
	struct atomtree_vram_info* dotdot;
	struct atom_gddr6_bit_byte_remap* leaves; // nonzero if populated

	//uint32_t table_size;
	//uint8_t phyintf_ck_inverted[8];	 //UMC_PHY_PHYINTF_CNTL.INV_CK
	//struct atom_gddr6_bit_byte_remap bit_byte_remap[16];
};
*/

struct atomtree_vram_info_header_v2_3 {
	struct atom_vram_info_header_v2_3* leaves; // nonzero if populated

	struct atomtree_vram_info_header_v2_3* dot;
	struct atomtree_vram_info* dotdot;

	//uint16_t mem_adjust_tbloffset;
	struct atomtree_umc_init_reg_block mem_adjust_table;

	//uint16_t mem_clk_patch_tbloffset;
	struct atomtree_umc_init_reg_block mem_clk_patch;

	//uint16_t mc_adjust_pertile_tbloffset;
	struct atomtree_umc_init_reg_block mc_adjust_pertile;

	//uint16_t mc_phyinit_tbloffset;
	struct atomtree_umc_init_reg_block mc_phyinit;

	//uint16_t dram_data_remap_tbloffset;
	struct atom_gddr6_dram_data_remap* dram_data_remap;

	//uint16_t tmrs_seq_offset;
	void* hbm_tmrs; // TODO: what is this? HBM timings?

	//uint16_t post_ucode_init_offset;
	struct atomtree_umc_init_reg_block post_ucode_init;
};

struct atomtree_vram_info_header_v2_4 {
	struct atomtree_vram_info_header_v2_4* dot;
	struct atomtree_vram_info* dotdot;
	struct atom_vram_info_header_v2_4* leaves; // nonzero if populated

	//uint16_t mem_adjust_tbloffset;
	struct atomtree_umc_init_reg_block mem_adjust_table;

	//uint16_t mem_clk_patch_tbloffset;
	struct atomtree_umc_init_reg_block mem_clk_patch;
	struct umc_block_navi1_timings* navi1_gddr6_timings;
	uint16_t* num_timing_straps;


	//uint16_t mc_adjust_pertile_tbloffset;
	struct atomtree_umc_init_reg_block mc_adjust_pertile;

	//uint16_t mc_phyinit_tbloffset;
	struct atomtree_umc_init_reg_block mc_phyinit;

	struct atom_gddr6_dram_data_remap* dram_data_remap;

	//uint16_t post_ucode_init_offset;
	struct atomtree_umc_init_reg_block post_ucode_init;
};

struct atomtree_vram_info_header_v2_5 {
	struct atomtree_vram_info_header_v2_5* dot;
	struct atomtree_vram_info* dotdot;
	struct atom_vram_info_header_v2_5* leaves; // nonzero if populated

	//uint16_t mem_adjust_tbloffset;
	struct atomtree_umc_init_reg_block mem_adjust_table;

	//uint16_t gddr6_ac_timing_offset;
	struct atom_gddr6_ac_timing_v2_5* gddr6_ac_timings; // is an array
	uint8_t gddr6_acstrap_count;

	//uint16_t mc_adjust_pertile_tbloffset;
	struct atomtree_umc_init_reg_block mc_adjust_pertile;

	//uint16_t mc_phyinit_tbloffset;
	struct atomtree_umc_init_reg_block mc_phyinit;

	//uint16_t dram_data_remap_tbloffset;
	struct atom_gddr6_dram_data_remap* dram_data_remap;

	//uint16_t reserved; // offset of reserved

	//uint16_t post_ucode_init_offset;
	struct atomtree_umc_init_reg_block post_ucode_init;

	//uint16_t strobe_mode_patch_tbloffset;
	struct atomtree_umc_init_reg_block strobe_mode_patch;

	struct atom_vram_module_v11 vram_module[16];
};

struct atomtree_vram_info_header_v2_6 {
	struct atomtree_vram_info_header_v2_6* dot;
	struct atomtree_vram_info* dotdot;
	struct atom_vram_info_header_v2_6* leaves; // nonzero if populated

	//uint16_t mem_adjust_tbloffset;
	struct atomtree_umc_init_reg_block mem_adjust_table;

	//uint16_t mem_clk_patch_tbloffset;
	struct atomtree_umc_init_reg_block mem_clk_patch;

	//uint16_t mc_adjust_pertile_tbloffset;
	struct atomtree_umc_init_reg_block mc_adjust_pertile;

	//uint16_t mc_phyinit_tbloffset;
	struct atomtree_umc_init_reg_block mc_phyinit;

	//uint16_t dram_data_remap_tbloffset;
	struct atom_gddr6_dram_data_remap* dram_data_remap;

	//uint16_t tmrs_seq_offset;
	void* tmrs_seq;

	//uint16_t post_ucode_init_offset;
	struct atomtree_umc_init_reg_block post_ucode_init;
};


struct atomtree_vram_module_v3_0 { // TODO figure out child tables
	struct atomtree_vram_module_v3_0* dot;
	struct atomtree_vram_info* dotdot;
	struct atom_vram_module_v3_0* leaves; // nonzero if populated

	//uint16_t dram_info_offset;
	void* dram_info;

	//uint16_t mem_tuning_offset;
	void* mem_tuning;

	//uint16_t tmrs_seq_offset;
	void* tmrs_seq;
};

struct atomtree_vram_info_header_v3_0 { // TODO figure out child tables
	struct atomtree_vram_info_header_v3_0* dot;
	struct atomtree_vram_info* dotdot;
	struct atom_vram_info_header_v3_0* leaves; // nonzero if populated

	//struct atom_common_table_header table_header;

	//uint16_t mem_tuning_table_offset;
	void* mem_tuning;

	//uint16_t dram_info_table_offset;
	void* dram_info;

	//uint16_t tmrs_table_offset;
	void* tmrs_seq;

	//uint16_t mc_init_table_offset;
	struct atomtree_umc_init_reg_block mc_init; // phy init? reg block anyway?

	//uint16_t dram_data_remap_table_offset;
	struct atom_gddr6_dram_data_remap* dram_data_remap;

	//uint16_t umc_emuinittable_offset;
	struct atomtree_umc_init_reg_block umc_emuinit; //TODO this is a guess

	//uint16_t reserved_sub_table_offset[2];
	void* rsvd_tables[2];

	//struct atom_vram_module_v3_0 vram_module[8];
	struct atomtree_vram_module_v3_0 vram_module[8];
};

struct atomtree_vram_info {
	struct atomtree_vram_info* dot;
	struct atomtree_master_datatable_v2_1* dotdot;
	union {
		struct atom_common_table_header* table_header;
		void* leaves; // nonzero if populated
	};

	enum atomtree_common_version ver;
	union {
		struct atomtree_vram_info_header_v2_3 v2_3;
		struct atomtree_vram_info_header_v2_4 v2_4;
		struct atomtree_vram_info_header_v2_5 v2_5;
		struct atomtree_vram_info_header_v2_6 v2_6;
		struct atomtree_vram_info_header_v3_0 v3_0;
	};
};

struct atomtree_sw_datatable {
	enum atomtree_common_version ver; // meh
    union {
        void* leaves; // nonzero if populated
        struct atom_common_table_header* table_header;
	};
};

struct atomtree_master_datatable_v2_1 {
	struct atomtree_master_datatable_v2_1* dot;
	struct atom_tree* dotdot;
	union {
        struct atom_common_table_header* table_header;
		struct atom_master_data_table_v2_1* leaves; // nonzero if populated
	};
	enum atomtree_common_version ver;

	// TODO relate these uint16t stuff to their tables.
	//struct common_header;
	struct atomtree_sw_datatable* utilitypipeline; //??

	struct atom_multimedia_info_v2_1* multimedia_info;
	struct atomtree_smc_dpm_info smc_dpm_info;
	struct atomtree_firmware_info firmwareinfo;
	struct lcd_info_v2_1* lcd_info;
	struct atomtree_smu_info smu_info;
	struct atomtree_vram_usagebyfirmware vram_usagebyfirmware;
	struct atom_gpio_pin_lut_v2_1* gpio_pin_lut; //TODO atomtree for array len?
	struct atomtree_gfx_info gfx_info;

	struct atomtree_powerplaytable powerplayinfo;

	uint16_t displayobjectinfo;
	uint16_t indirectioaccess;
	uint16_t umc_info;
	uint16_t dce_info;

	struct atomtree_vram_info vram_info;

	uint16_t integratedsysteminfo;
	uint16_t asic_profiling_info;
	uint16_t voltageobject_info;

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


#endif
