subdir('atui_tables')

include_dirs += include_directories('.')

yaabe_src += files(
	'atomtree.c',
	'asic_reg_tools.c',
	'atui_branch_allocator.c',
	'atui.c',
)

register_index_searchfields = files(
	'gmc_searchfield.json5',
)
internal_depends += declare_dependency( # header generaton
	sources: json5_to_h.process(
		register_index_searchfields,
	),
)
yaabe_src += json5_to_c.process( # c file generaton
	register_index_searchfields,
)
