include_dirs += include_directories('.')

atom_array_tables = files(
	'asic_reg_indices.json5',
)
internal_depends += declare_dependency( # header generaton
	sources: json5_to_h.process(
		atom_array_tables,
	),
)
yaabe_src += json5_to_c.process( # c file generaton
	atom_array_tables,
)
