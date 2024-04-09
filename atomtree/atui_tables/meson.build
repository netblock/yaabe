atui_branches = files(
	'atui_gmc.json5', # extra long
	'atui_atomfirmware.json5',
	'atui_smu_v13_pptable.json5',
	'atui_smu_v11_pptable.json5',
	'atui_ddrmoderegisters.json5',
	'atui_atombios.json5',
	'atui_powerplay.json5',
	'atui_asic_reg_data_tables.json5',
	'atui_bitfield_overrides.json5',
)

internal_depends += declare_dependency( # header generaton
	sources: json5_to_h.process(
		atui_branches,
		'atui_enums.json5',
	),
)

yaabe_src += json5_to_c.process(atui_branches) # c file generaton
