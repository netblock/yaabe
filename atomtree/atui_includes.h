/*
For main API use, see atui.h
See ppatui.h for the metaprogramming

atui_includes.h is about the headers for the ATUI_FUNCIFY() products, via
ATUI_HEADERIFY()
*/

#ifndef ATUI_INCLUDES_H
#define ATUI_INCLUDES_H




//blank branch
PPATUI_HEADERIFY(atui_nullstruct);

/***************************************************************************************/
// atui_atomfirmware.c / atomfirmware.h

PPATUI_HEADERIFY(atom_common_table_header);

PPATUI_HEADERIFY(atom_rom_header_v2_2);
PPATUI_HEADERIFY(atom_master_data_table_v2_1);


PPATUI_HEADERIFY(atom_smc_dpm_info_v4_1);
PPATUI_HEADERIFY(atom_smc_dpm_info_v4_3);
PPATUI_HEADERIFY(smudpm_i2ccontrollerconfig_t);
PPATUI_HEADERIFY(atom_smc_dpm_info_v4_4);
PPATUI_HEADERIFY(smudpm_i2c_controller_config_v2);
PPATUI_HEADERIFY(atom_smc_dpm_info_v4_5);



PPATUI_HEADERIFY(atom_firmware_info_v3_1);
PPATUI_HEADERIFY(atom_firmware_info_v3_2);
PPATUI_HEADERIFY(atom_firmware_info_v3_3);
PPATUI_HEADERIFY(atom_firmware_info_v3_4);



PPATUI_HEADERIFY(vram_usagebyfirmware_v2_1);
PPATUI_HEADERIFY(vram_usagebyfirmware_v2_2);


PPATUI_HEADERIFY(atom_gpio_pin_assignment_v2_1);


PPATUI_HEADERIFY(atom_gfx_info_v2_2);
PPATUI_HEADERIFY(atom_gfx_info_v2_3);
PPATUI_HEADERIFY(atom_gfx_info_v2_4);
PPATUI_HEADERIFY(atom_gfx_info_v2_5);
PPATUI_HEADERIFY(atom_gfx_info_v2_6);
PPATUI_HEADERIFY(atom_gfx_info_v2_7);
PPATUI_HEADERIFY(atom_gfx_info_v3_0);



PPATUI_HEADERIFY(atom_dtd_format);
PPATUI_HEADERIFY(atom_lcd_info_v2_1);



PPATUI_HEADERIFY(atom_smu_info_v3_1);
PPATUI_HEADERIFY(atom_smu_info_v3_2);
PPATUI_HEADERIFY(atom_smu_info_v3_3);
PPATUI_HEADERIFY(atom_smu_info_v3_5);
PPATUI_HEADERIFY(atom_smu_info_v3_6);
PPATUI_HEADERIFY(atom_smu_info_v4_0);




//PPATUI_HEADERIFY(atom_umc_reg_setting_data_block);
PPATUI_HEADERIFY(atom_umc_register_addr_info_access);
PPATUI_HEADERIFY(atom_umc_init_reg_block);
PPATUI_HEADERIFY(atom_umc_reg_setting_data_block);
PPATUI_HEADERIFY(atom_umc_reg_setting_id_config_access);

PPATUI_HEADERIFY(atom_gddr6_bit_byte_remap);
PPATUI_HEADERIFY(atom_gddr6_dram_data_remap);

PPATUI_HEADERIFY(atom_vram_module_v9);
PPATUI_HEADERIFY(atom_vram_info_header_v2_3);

PPATUI_HEADERIFY(atom_vram_module_v10);
PPATUI_HEADERIFY(umc_block_navi1_timings);
PPATUI_HEADERIFY(atom_vram_info_header_v2_4);

PPATUI_HEADERIFY(atom_vram_module_v11);
PPATUI_HEADERIFY(atom_gddr6_ac_timing_v2_5);
PPATUI_HEADERIFY(atom_vram_info_header_v2_5);

PPATUI_HEADERIFY(atom_vram_info_header_v2_6);

PPATUI_HEADERIFY(atom_vram_module_v3_0);
PPATUI_HEADERIFY(atom_vram_info_header_v3_0);



PPATUI_HEADERIFY(atom_voltage_object_header_v4);
PPATUI_HEADERIFY(atom_gpio_voltage_object_v4);
PPATUI_HEADERIFY(atom_i2c_voltage_object_v4);
PPATUI_HEADERIFY(atom_svid2_voltage_object_v4);
PPATUI_HEADERIFY(atom_merged_voltage_object_v4);






/***************************************************************************************/
// atui_ddrmoderegisters.c / ddrmoderegisters.h

PPATUI_HEADERIFY(gddr6_mr0);
PPATUI_HEADERIFY(gddr6_mr1);
PPATUI_HEADERIFY(gddr6_mr2);
PPATUI_HEADERIFY(gddr6_mr3);
PPATUI_HEADERIFY(gddr6_mr4);
PPATUI_HEADERIFY(gddr6_mr5);
PPATUI_HEADERIFY(gddr6_mr6);
PPATUI_HEADERIFY(gddr6_mr7);
PPATUI_HEADERIFY(gddr6_mr8);
PPATUI_HEADERIFY(gddr6_mr9);
PPATUI_HEADERIFY(gddr6_mr10);
PPATUI_HEADERIFY(gddr6_mr11);
PPATUI_HEADERIFY(gddr6_mr12);
PPATUI_HEADERIFY(gddr6_mr13);
PPATUI_HEADERIFY(gddr6_mr14);
PPATUI_HEADERIFY(gddr6_mr15);


/***************************************************************************************/
// atui_smu_v11_pptable.c / smu_v11_pptable.h , smu11_driver_if.h

PPATUI_HEADERIFY(smu_powerplay_table_header);
PPATUI_HEADERIFY(smu_11_0_powerplay_table);
PPATUI_HEADERIFY(smu_11_0_power_saving_clock_table);
PPATUI_HEADERIFY(smu_11_0_overdrive_table);
PPATUI_HEADERIFY(smc_pptable);
PPATUI_HEADERIFY(powerplay_features);
PPATUI_HEADERIFY(smc_pptable_i2c);


#endif