project('yaabe', 'c',
	version: '0.4.0',
	meson_version: '>= 1.2.3',
	default_options: [
  		'c_std=gnu23',
  		'buildtype=debug',
		'b_ndebug=if-release',
		'warning_level=0'
	]
)

cc = meson.get_compiler('c')
add_project_arguments(
	'-D_POSIX_C_SOURCE=200809L', # for stpcpy
	language: 'c',
)
if 'debug' == get_option('buildtype')
	add_project_arguments(
		'-fstack-protector-strong',
		'-march=native',
		language: 'c',
	)
endif

external_depends = [
	cc.find_library('m', required: true),
	dependency('gtk4', version: '>= 4.12.0', required: true),
]

# source/header generators
ppatui = find_program('scripts/ppatui.py', native: true, required: true)
json5_to_c = generator(ppatui,
	arguments: '-s -o @OUTPUT@ -i @INPUT@'.split(),
	output: '@BASENAME@.c',
)
json5_to_h = generator(ppatui,
	arguments: '-d -o @OUTPUT@ -i @INPUT@'.split(),
	output: '@BASENAME@.h',
)

internal_depends = []
include_dirs = []
yaabe_src = []
subdir('atomtree')
subdir('gtk')
yaabe_src += files('main.c')
include_dirs += include_directories('atom')


if 'windows' == target_machine.system()
	# msys2 isn't caught up with C23
	add_project_arguments('-DC2X_COMPAT', language:'c')

	# windows resource compiler .rc file
	ver_array = meson.project_version().split('.')
	windows = import('windows')
	yaabe_src += windows.compile_resources(configure_file(
		input: files('yaabewindows.rc.in'),
		output: 'yaabewindows.rc',
		configuration: configuration_data({
			'IS_RELEASE': ('release' == get_option('buildtype')).to_int(),
			'VER_MAJOR': ver_array[0],
			'VER_MINOR': ver_array[1],
			'VER_PATCH': ver_array[2]
		})
	))
endif

yaabe = executable('yaabe',
	sources: yaabe_src,
	include_directories: include_dirs,
	dependencies: (external_depends + internal_depends),
	install: true,
	win_subsystem: 'windows',
)

if get_option('nsis_installer')
	# dummy requirements for nsis_helper.py
	find_program('makensis', native: true, required: true)
	find_program('glib-compile-schemas', native: true, required: true)
	find_program('ldd', native:true, required: true)

	cygpath = find_program('cygpath', native:true, required: true)
	nsis_helper = find_program('scripts/nsis_helper.py', required: true)

	msys2_err = 'We pluck assets from MSYS2 for the installer. https://www.msys2.org'
	fs = import('fs')
	mingw64_path = run_command(cygpath, '-m', '/mingw64').stdout().strip()
	assert(fs.is_dir(mingw64_path), msys2_err)
	assert('windows' == target_machine.system(), msys2_err)

	nsis_target = custom_target('nsis_installer',
		depends: yaabe,
		build_by_default: true,
		input: [
			files('yaabe.nsi'),
			yaabe,
		],
		output: 'yaabe-installer-' + meson.project_version() + '.exe',
		command: [
			nsis_helper,		
			'@INPUT0@', # .nsi
			'@CURRENT_SOURCE_DIR@', # gtk-assets, others
			'@INPUT1@', # yaabe.exe
			'@PRIVATE_DIR@', # stage
			'@OUTPUT@', # installer exe
			meson.project_version()
		],
	)
endif
