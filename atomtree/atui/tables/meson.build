# when adding a file here, don't forget to add to atui/auto_includes.h
atui_branches = files(
	'atui_gc.json5',
	'atui_gmc.json5', # extra long
	'atui_atombios.json5',
	'atui_atomfirmware.json5',
	'atui_powerplay.json5',
	'atui_pplib.json5',
	'atui_pptable.json5',
	'atui_pptable_vega10.json5',
	'atui_smu_v11_pptable.json5',
	'atui_smu_v13_pptable.json5',
	'atui_ddrmoderegisters.json5',
	'atui_asic_reg_data_tables.json5',
	'atui_bitfield_overrides.json5',
)
atui_const_tables = files(
	'atui_enums.json5',
)

autogen_depends += declare_dependency( # header generaton
	sources: json5_to_h.process(
		atui_branches,
		atui_const_tables,
	),
)

yaabe_autogen_src += json5_to_c.process( # c file generaton
	atui_branches,
	atui_const_tables,
)
