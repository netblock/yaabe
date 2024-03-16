internal_depends += declare_dependency(
	sources: json5_to_h.process(
		'atui_enums.json5',
	),
)

include_dirs += include_directories('.')

atui_tables_sources = json5_to_c.process(
	'atui_gmc.json5', # extra long
	'atui_atomfirmware.json5',
	'atui_smu_v13_pptable.json5',
	'atui_smu_v11_pptable.json5',
	'atui_ddrmoderegisters.json5',
	'atui_atombios.json5',
	'atui_powerplay.json5',
	'atui_umctimings.json5',
)
atomtree_sources = files(
	'atomtree.c',
	'asic_reg_indices.c',
	'atui_branch_allocator.c',
	'atui.c',
)
yaabe_src += [
	atui_tables_sources,
	atomtree_sources,
]
