#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

struct mt{
	uint16_t utilitypipeline;							 /* Offest for the utility to get parser info,Don't change this position!*/
	uint16_t multimedia_info;
	uint16_t smc_dpm_info;
	uint16_t sw_datatable3;
	uint16_t firmwareinfo;									/* Shared by various SW components */
	uint16_t sw_datatable5;
	uint16_t lcd_info;											/* Shared by various SW components */
	uint16_t sw_datatable7;
	uint16_t smu_info;
	uint16_t sw_datatable9;
	uint16_t sw_datatable10;
	uint16_t vram_usagebyfirmware;					/* Shared by various SW components */
	uint16_t gpio_pin_lut;									/* Shared by various SW components */
	uint16_t sw_datatable13;
	uint16_t gfx_info;
	uint16_t powerplayinfo;								 /* Shared by various SW components */
	uint16_t sw_datatable16;
	uint16_t sw_datatable17;
	uint16_t sw_datatable18;
	uint16_t sw_datatable19;
	uint16_t sw_datatable20;
	uint16_t sw_datatable21;
	uint16_t displayobjectinfo;						 /* Shared by various SW components */
	uint16_t indirectioaccess;							/* used as an internal one */
	uint16_t umc_info;											/* Shared by various SW components */
	uint16_t sw_datatable25;
	uint16_t sw_datatable26;
	uint16_t dce_info;											/* Shared by various SW components */
	uint16_t vram_info;										 /* Shared by various SW components */
	uint16_t sw_datatable29;
	uint16_t integratedsysteminfo;					/* Shared by various SW components */
	uint16_t asic_profiling_info;					 /* Shared by various SW components */
	uint16_t voltageobject_info;						/* shared by various SW components */
	uint16_t sw_datatable33;
	uint16_t sw_datatable34;
};

struct mt2{
	uint32_t plus_four; //Rolled up for aesthetics; probably frev,crev? Also check out this loser VVV

	uint16_t utilitypipeline;      /* Offest for the utility to get parser info,Don't change this position!*/
	uint16_t multimedia_info;
	uint16_t smc_dpm_info;
	uint16_t sw_datatable3;
	uint16_t firmwareinfo;         /* Shared by various SW components */
	uint16_t sw_datatable5;
	uint16_t lcd_info;             /* Shared by various SW components */
	uint16_t sw_datatable7;
	uint16_t smu_info;
	uint16_t sw_datatable9;
	uint16_t sw_datatable10;
	uint16_t vram_usagebyfirmware; /* Shared by various SW components */
	uint16_t gpio_pin_lut;         /* Shared by various SW components */
	uint16_t sw_datatable13;
	uint16_t gfx_info;
	uint16_t powerplayinfo;        /* Shared by various SW components */
	uint16_t sw_datatable16;
	uint16_t sw_datatable17;
	uint16_t sw_datatable18;
	uint16_t sw_datatable19;
	uint16_t sw_datatable20;
	uint16_t sw_datatable21;
	uint16_t displayobjectinfo;    /* Shared by various SW components */
	uint16_t indirectioaccess;     /* used as an internal one */
	uint16_t umc_info;             /* Shared by various SW components */
	uint16_t sw_datatable25;
	uint16_t sw_datatable26;
	uint16_t dce_info;             /* Shared by various SW components */
	uint16_t vram_info;            /* Shared by various SW components */
	uint16_t sw_datatable29;
	uint16_t integratedsysteminfo; /* Shared by various SW components */
	uint16_t asic_profiling_info;  /* Shared by various SW components */
	uint16_t voltageobject_info;   /* shared by various SW components */
	uint16_t sw_datatable33;
	uint16_t sw_datatable34;
};

#define get_index(master_table, table_name) (offsetof(struct master_table, table_name) / sizeof(uint16_t))
#define get_offset(master_table, table_name) (offsetof(struct master_table, table_name))

int main(){
	char l = 35;
	char idx[] = {
		get_index(mt, utilitypipeline),
		get_index(mt, multimedia_info),
		get_index(mt, smc_dpm_info),
		get_index(mt, sw_datatable3),
		get_index(mt, firmwareinfo),
		get_index(mt, sw_datatable5),
		get_index(mt, lcd_info),
		get_index(mt, sw_datatable7),
		get_index(mt, smu_info),
		get_index(mt, sw_datatable9),
		get_index(mt, sw_datatable10),
		get_index(mt, vram_usagebyfirmware),
		get_index(mt, gpio_pin_lut),
		get_index(mt, sw_datatable13),
		get_index(mt, gfx_info),
		get_index(mt, powerplayinfo),
		get_index(mt, sw_datatable16),
		get_index(mt, sw_datatable17),
		get_index(mt, sw_datatable18),
		get_index(mt, sw_datatable19),
		get_index(mt, sw_datatable20),
		get_index(mt, sw_datatable21),
		get_index(mt, displayobjectinfo),
		get_index(mt, indirectioaccess),
		get_index(mt, umc_info),
		get_index(mt, sw_datatable25),
		get_index(mt, sw_datatable26),
		get_index(mt, dce_info),
		get_index(mt, vram_info),
		get_index(mt, sw_datatable29),
		get_index(mt, integratedsysteminfo),
		get_index(mt, asic_profiling_info),
		get_index(mt, voltageobject_info),
		get_index(mt, sw_datatable33),
		get_index(mt, sw_datatable34)
	};

	char ofst[] = {
		get_offset(mt2, utilitypipeline),
		get_offset(mt2, multimedia_info),
		get_offset(mt2, smc_dpm_info),
		get_offset(mt2, sw_datatable3),
		get_offset(mt2, firmwareinfo),
		get_offset(mt2, sw_datatable5),
		get_offset(mt2, lcd_info),
		get_offset(mt2, sw_datatable7),
		get_offset(mt2, smu_info),
		get_offset(mt2, sw_datatable9),
		get_offset(mt2, sw_datatable10),
		get_offset(mt2, vram_usagebyfirmware),
		get_offset(mt2, gpio_pin_lut),
		get_offset(mt2, sw_datatable13),
		get_offset(mt2, gfx_info),
		get_offset(mt2, powerplayinfo),
		get_offset(mt2, sw_datatable16),
		get_offset(mt2, sw_datatable17),
		get_offset(mt2, sw_datatable18),
		get_offset(mt2, sw_datatable19),
		get_offset(mt2, sw_datatable20),
		get_offset(mt2, sw_datatable21),
		get_offset(mt2, displayobjectinfo),
		get_offset(mt2, indirectioaccess),
		get_offset(mt2, umc_info),
		get_offset(mt2, sw_datatable25),
		get_offset(mt2, sw_datatable26),
		get_offset(mt2, dce_info),
		get_offset(mt2, vram_info),
		get_offset(mt2, sw_datatable29),
		get_offset(mt2, integratedsysteminfo),
		get_offset(mt2, asic_profiling_info),
		get_offset(mt2, voltageobject_info),
		get_offset(mt2, sw_datatable33),
		get_offset(mt2, sw_datatable34)
	};

	printf("%d\n", sizeof(uint16_t));
	while(l--)
		printf("index: %2d; offset = index*2+4 = %2d; ofst: %2d\n", idx[l],
			idx[l]*2+4, ofst[l]);
}
