/*
For main API use, see atui.h
See ppatui.h for the metaprogramming

atui_includes.h is about the headers for the ATUI_FUNCIFY() products, via
ATUI_HEADERIFY()

'<,'>s/\(^\s\*\)\?\([^,]\+\),\?/PPATUI_HEADERIFY(\2);
*/

#ifndef ATUI_INCLUDES_H
#define ATUI_INCLUDES_H


/******************************************************************************/
// atui_atomfirmware.c / atomfirmware.h

// blank branch
PPATUI_HEADERIFY(atui_nullstruct);

PPATUI_HEADERIFY(atombios_image);
PPATUI_HEADERIFY(atom_common_table_header);
PPATUI_HEADERIFY(atom_rom_header_v2_2);
PPATUI_HEADERIFY(atom_master_data_table_v2_1);


PPATUI_HEADERIFY(i2ccontrollerconfig_u32);
PPATUI_HEADERIFY(i2ccontrollerconfig_u8);
PPATUI_HEADERIFY(i2ccontrollerconfig_u8_mixed);

PPATUI_HEADERIFY(psi_sel_mask);
PPATUI_HEADERIFY(led_display_control);

PPATUI_HEADERIFY(atom_smc_dpm_info_v4_1);
PPATUI_HEADERIFY(atom_smc_dpm_info_v4_3);
PPATUI_HEADERIFY(atom_smc_dpm_info_v4_4);
PPATUI_HEADERIFY(atom_smc_dpm_info_v4_5);
PPATUI_HEADERIFY(atom_smc_dpm_info_v4_6);
PPATUI_HEADERIFY(atom_smc_dpm_info_v4_7);
PPATUI_HEADERIFY(atom_smc_dpm_info_v4_9);
PPATUI_HEADERIFY(atom_smc_dpm_info_v4_10);


PPATUI_HEADERIFY(atom_firmware_info_v3_1);
PPATUI_HEADERIFY(atom_firmware_info_v3_2);
PPATUI_HEADERIFY(atom_firmware_info_v3_3);
PPATUI_HEADERIFY(atom_firmware_info_v3_4);


PPATUI_HEADERIFY(vram_usagebyfirmware_v2_1);
PPATUI_HEADERIFY(vram_usagebyfirmware_v2_2);


PPATUI_HEADERIFY(atom_gpio_pin_assignment_v2_1);
PPATUI_HEADERIFY(atom_gpio_pin_lut_v2_1);



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
//PPATUI_HEADERIFY(atom_umc_register_addr_info_access);
PPATUI_HEADERIFY(atom_umc_init_reg_block);
PPATUI_HEADERIFY(atom_umc_reg_setting_data_block);
PPATUI_HEADERIFY(atom_mc_register_setting_id);

PPATUI_HEADERIFY(atom_gddr6_bit_byte_remap);
PPATUI_HEADERIFY(atom_gddr6_dram_data_remap);

PPATUI_HEADERIFY(memory_vendor_id);

PPATUI_HEADERIFY(atom_vram_module_v9);
PPATUI_HEADERIFY(atom_vram_info_header_v2_3);

PPATUI_HEADERIFY(atom_vram_module_v10);
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


/******************************************************************************/
// atui_umctimings.c / umctimings.h

PPATUI_HEADERIFY(umc_block_vega10_timings);
PPATUI_HEADERIFY(umc_block_vega21_timings);
PPATUI_HEADERIFY(umc_block_navi1_timings);


/******************************************************************************/
// atui_atombios.c / atombios.h

PPATUI_HEADERIFY(atom_rom_header_v1_1);
PPATUI_HEADERIFY(atom_rom_header_v2_1);

PPATUI_HEADERIFY(atom_master_data_table_v1_1);

PPATUI_HEADERIFY(atom_firmware_info_v1_0);
PPATUI_HEADERIFY(atom_firmware_info_v1_2);
PPATUI_HEADERIFY(atom_firmware_info_v1_3);
PPATUI_HEADERIFY(atom_firmware_info_v1_4);
PPATUI_HEADERIFY(atom_firmware_info_v2_1);
PPATUI_HEADERIFY(atom_firmware_info_v2_2);

PPATUI_HEADERIFY(atom_init_reg_block);
PPATUI_HEADERIFY(atom_vram_module_v1);
PPATUI_HEADERIFY(atom_vram_module_v2);
PPATUI_HEADERIFY(atom_memory_timing_format_v0);
PPATUI_HEADERIFY(atom_memory_timing_format_v1);
PPATUI_HEADERIFY(atom_memory_timing_format_v2);
PPATUI_HEADERIFY(atom_vram_module_v3);
PPATUI_HEADERIFY(atom_vram_module_v4);
PPATUI_HEADERIFY(atom_vram_module_v5);
PPATUI_HEADERIFY(atom_vram_module_v6);
PPATUI_HEADERIFY(atom_vram_module_v7);
PPATUI_HEADERIFY(atom_vram_module_v8);

PPATUI_HEADERIFY(atom_vram_info_v1_2);
PPATUI_HEADERIFY(atom_vram_info_v1_3);
PPATUI_HEADERIFY(atom_vram_info_v1_4);
PPATUI_HEADERIFY(atom_vram_info_header_v2_1);
PPATUI_HEADERIFY(atom_vram_info_header_v2_2);


/******************************************************************************/
// atui_ddrmoderegisters.c / ddrmoderegisters.h

PPATUI_HEADERIFY(ddr1_mr0);
PPATUI_HEADERIFY(ddr1_emr1);

PPATUI_HEADERIFY(ddr2_mr0);
PPATUI_HEADERIFY(ddr2_emr1);
PPATUI_HEADERIFY(ddr2_emr2);
PPATUI_HEADERIFY(ddr2_emr3);

PPATUI_HEADERIFY(ddr3_mr0);
PPATUI_HEADERIFY(ddr3_mr1);
PPATUI_HEADERIFY(ddr3_mr2);
PPATUI_HEADERIFY(ddr3_mr3);

PPATUI_HEADERIFY(gddr2_mr0);
PPATUI_HEADERIFY(gddr2_emr1);
PPATUI_HEADERIFY(gddr2_emr2);

PPATUI_HEADERIFY(gddr3_mr0);
PPATUI_HEADERIFY(gddr3_emr1);

PPATUI_HEADERIFY(gddr4_mr0);
PPATUI_HEADERIFY(gddr4_emr1);
PPATUI_HEADERIFY(gddr4_emr2);
PPATUI_HEADERIFY(gddr4_emr3);

PPATUI_HEADERIFY(gddr5_mr0);
PPATUI_HEADERIFY(gddr5_mr1);
PPATUI_HEADERIFY(gddr5_mr2);
PPATUI_HEADERIFY(gddr5_mr3);
PPATUI_HEADERIFY(gddr5_mr4);
PPATUI_HEADERIFY(gddr5_mr5);
PPATUI_HEADERIFY(gddr5_mr6);
PPATUI_HEADERIFY(gddr5_mr7);
PPATUI_HEADERIFY(gddr5_mr8);
PPATUI_HEADERIFY(gddr5_mr9);
PPATUI_HEADERIFY(gddr5_mr10);
PPATUI_HEADERIFY(gddr5_mr11);
PPATUI_HEADERIFY(gddr5_mr12);
PPATUI_HEADERIFY(gddr5_mr13);
PPATUI_HEADERIFY(gddr5_mr14);
PPATUI_HEADERIFY(gddr5_mr15);

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

PPATUI_HEADERIFY(hbm_mr0);
PPATUI_HEADERIFY(hbm_mr1);
PPATUI_HEADERIFY(hbm_mr2);
PPATUI_HEADERIFY(hbm_mr3);
PPATUI_HEADERIFY(hbm_mr4);
PPATUI_HEADERIFY(hbm_mr5);
PPATUI_HEADERIFY(hbm_mr6);
PPATUI_HEADERIFY(hbm_mr7);
PPATUI_HEADERIFY(hbm_mr8);
PPATUI_HEADERIFY(hbm_mr9);
PPATUI_HEADERIFY(hbm_mr10);
PPATUI_HEADERIFY(hbm_mr11);
PPATUI_HEADERIFY(hbm_mr12);
PPATUI_HEADERIFY(hbm_mr13);
PPATUI_HEADERIFY(hbm_mr14);
PPATUI_HEADERIFY(hbm_mr15);

PPATUI_HEADERIFY(hbm3_mr0);
PPATUI_HEADERIFY(hbm3_mr1);
PPATUI_HEADERIFY(hbm3_mr2);
PPATUI_HEADERIFY(hbm3_mr3);
PPATUI_HEADERIFY(hbm3_mr4);
PPATUI_HEADERIFY(hbm3_mr5);
PPATUI_HEADERIFY(hbm3_mr6);
PPATUI_HEADERIFY(hbm3_mr7);
PPATUI_HEADERIFY(hbm3_mr8);
PPATUI_HEADERIFY(hbm3_mr9);
PPATUI_HEADERIFY(hbm3_mr10);
PPATUI_HEADERIFY(hbm3_mr11);
PPATUI_HEADERIFY(hbm3_mr12);
PPATUI_HEADERIFY(hbm3_mr13);
PPATUI_HEADERIFY(hbm3_mr14);
PPATUI_HEADERIFY(hbm3_mr15);


/******************************************************************************/
// atui_powerplay.c / powerplay.h

PPATUI_HEADERIFY(smu_powerplay_table_header);
PPATUI_HEADERIFY(powerplay_platform_caps);
PPATUI_HEADERIFY(quadratic_f32);
PPATUI_HEADERIFY(linear_f32);
PPATUI_HEADERIFY(droop_f32);


/******************************************************************************/
// atui_smu_v11_pptable.c / smu_v11_pptable.h , smu11_driver_if.h

PPATUI_HEADERIFY(smu_11_0_powerplay_table);
PPATUI_HEADERIFY(smu11_smcpptable_v3);
PPATUI_HEADERIFY(smu11_smcpptable_v8);
PPATUI_HEADERIFY(smu_11_0_7_powerplay_table);
PPATUI_HEADERIFY(smu11_smcpptable_v7);


/******************************************************************************/
// atui_smu_v13_pptable.c / smu_v13_0_7_pptable.h , smu13_driver_if_v13_0_7.h

PPATUI_HEADERIFY(smu_13_0_7_powerplay_table);
PPATUI_HEADERIFY(smu13_smcpptable_v39);
PPATUI_HEADERIFY(atom_smc_dpm_info_table_13_0_7);
#endif
