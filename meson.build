project('yaabe', 'c',
	version: '0.4.0',
	meson_version: '>= 1.2.3',
	default_options: [
  		'c_std=c2x',
  		'buildtype=debug',
		'b_ndebug=if-release',
		'warning_level=0'
	]
)

cc = meson.get_compiler('c')
ppatui = find_program('scripts/ppatui.py', native: true, required: true)

external_depends = [
	cc.find_library('m', required: true),
	dependency('gtk4', version: '>= 4.10.0', required: true),
]


include_dirs = include_directories(['atom', 'atomtree','gtk'])
subdir('atomtree')
subdir('gtk')
main_files = files('main.c')


if 'debug' == get_option('buildtype')
	add_project_arguments(
		'-fstack-protector-strong',
		language:'c'
	)
endif

if 'windows' == target_machine.system()
	# msys2 isn't caught up with C23
	add_project_arguments('-DC2X_COMPAT', language:'c')

	# windows resource compiler .rc file
	ver_array = meson.project_version().split('.')
	windows = import('windows')
	main_files += windows.compile_resources(configure_file(
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

src = atomtree_source + gtk_files + main_files
all_deps = external_depends
yaabe = executable('yaabe',
	sources: src,
	include_directories: include_dirs,
	dependencies: all_deps,
	install: true,
	win_subsystem: 'windows',
)

if get_option('nsis_installer')
	msys2_err = 'We pluck assets from MSYS2 for the installer. https://www.msys2.org'
	fs = import('fs')
	mingw64_path = run_command('cygpath', '-m', '/mingw64').stdout().strip()
	assert(fs.is_dir(mingw64_path), msys2_err)
	assert('windows' == target_machine.system(), msys2_err)

	pypath = import('python').find_installation()

	#find_program('makensis', native: true, required: true)
	#find_program('glib-compile-schemas', native: true, required: true)
	#find_program('ldd', native:true, required: true)
	#find_program('cygpath', native:true, required: true)

	nsis_target = custom_target('nsis_installer',
		depends: yaabe,
		build_always_stale: true,
		input: [
			files('yaabe.nsi'),
			yaabe,
		],
		output: 'yaabe-installer-' + meson.project_version() + '.exe',
		command: [
			pypath,
			files('scripts/nsis_helper.py'),
			'@INPUT0@', # .nsi
			'@CURRENT_SOURCE_DIR@', # gtk-assets, others
			'@INPUT1@', # yaabe.exe
			'@PRIVATE_DIR@', # stage
			'@OUTPUT@', # installer exe
			meson.project_version()
		]
	)
endif
