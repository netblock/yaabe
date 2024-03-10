atui_tables_source_files = [
#	'atui_gmc.c', # extra long
#	'atui_atomfirmware.c',
#	'atui_smu_v13_pptable.c',
#	'atui_smu_v11_pptable.c',
#	'atui_ddrmoderegisters.c',
#	'atui_atombios.c',
#	'atui_powerplay.c',
#	'atui_umctimings.c',
]
atomtree_sources = [
	'atomtree.c',
	'asic_reg_indices.c',
	'atui_branch_allocator.c',
	'atui.c',
]

json5_to_c = generator(ppatui,
	arguments: ['@INPUT@', '@OUTPUT@'],
	output: '@BASENAME@.c',
)
atui_tables_sources = json5_to_c.process(files([
	'atui_gmc.json5', # extra long
	'atui_atomfirmware.json5',
	'atui_smu_v13_pptable.json5',
	'atui_smu_v11_pptable.json5',
	'atui_ddrmoderegisters.json5',
	'atui_atombios.json5',
	'atui_powerplay.json5',
	'atui_umctimings.json5',
]))

atomtree_source = [
	atui_tables_sources,
	files(atui_tables_source_files + atomtree_sources),
]
