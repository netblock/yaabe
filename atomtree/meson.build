subdir('atui')

include_dirs += include_directories('.')

yaabe_src += files(
	'atomtree.c',
	'atomtree_internal.c',
	'asic_reg_tools.c',
	'pci_id_lut.c',
)

json5_tables = files(
	'gmc_searchfield.json5',
	'asic_reg_indices.json5',
	'amd_pci_ids.json5',
)
autogen_depends += declare_dependency( # header generaton
	sources: json5_to_h.process(
		json5_tables,
	),
)
yaabe_autogen_src += json5_to_c.process( # c file generaton
	json5_tables,
)
