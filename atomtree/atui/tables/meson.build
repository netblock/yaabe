# when adding a file here, don't forget to add to auto_includes.h
atui_branches = files(
	'atui_gmc.json5', # extra long
	'atui_atomfirmware.json5',
	'atui_pptable_v1_0.json5',
	'atui_smu_v9_pptable.json5',
	'atui_smu_v13_pptable.json5',
	'atui_smu_v11_pptable.json5',
	'atui_ddrmoderegisters.json5',
	'atui_atombios.json5',
	'atui_powerplay.json5',
	'atui_asic_reg_data_tables.json5',
	'atui_bitfield_overrides.json5',
	'atui_gc.json5',
)
atui_const_tables = files(
	'atui_enums.json5',
)

internal_depends += declare_dependency( # header generaton
	sources: json5_to_h.process(
		atui_branches,
		atui_const_tables,
	),
	compile_args: [
		'-Wno-unused-variable',
		'-Wno-override-init',
	],
)

yaabe_src += json5_to_c.process( # c file generaton
	atui_branches,
	atui_const_tables,
)
