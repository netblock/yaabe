atui_branches = files(
	'atui_gmc.json5', # extra long
	'atui_atomfirmware.json5',
	'atui_smu_v13_pptable.json5',
	'atui_smu_v11_pptable.json5',
	'atui_ddrmoderegisters.json5',
	'atui_atombios.json5',
	'atui_powerplay.json5',
	'atui_umctimings.json5',
)

internal_depends += declare_dependency(
	sources: json5_to_h.process(
		atui_branches,
		'atui_enums.json5',
	),
)

include_dirs += include_directories('.')

atomtree_sources = files(
	'atomtree.c',
	'asic_reg_indices.c',
	'atui_branch_allocator.c',
	'atui.c',
)
yaabe_src += [
	json5_to_c.process(atui_branches),
	atomtree_sources,
]
