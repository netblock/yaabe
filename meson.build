project('yaabe', 'c',
	version: '0.9.0',
	meson_version: '>= 1.2.3',
	default_options: [
		'c_std=gnu23',
		'buildtype=debug',
		'b_ndebug=if-release',
		'warning_level=2', # 2 is -Wall -Wextra
	]
)

fs = import('fs')

cc = meson.get_compiler('c')
add_project_arguments(
	'-DYAABE_VER="@0@"'.format(meson.project_version()),
	'-D_GNU_SOURCE', # implies posix 2008, isoc2x
	'-fwrapv',

	'-Wformat-security',
	'-Wstringop-overflow',
	'-Wstringop-truncation',
	'-Wno-switch',

	language: 'c',
)
mold = find_program('mold', required: false)
if mold.found()
	add_project_arguments(
		'-fuse-ld=mold',
		language: 'c',
	)
	add_project_link_arguments(
		'-fuse-ld=mold',
		language: 'c',
	)
endif
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
	dependency('zlib', required: true),
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

include_dirs = []
yaabe_src = []
autogen_depends = []
yaabe_autogen_src = []
# for YAABE, subdir order doesn't technically matter
subdir('atomtree')
subdir('atom')
subdir('gatui')
subdir('gtk')
yaabe_src += files(
	'standard.c',
)
include_dirs += include_directories('.')

yaabe_exe_src = files()
if 'windows' == target_machine.system()
	# msys2 isn't caught up with C23
	add_project_arguments('-DC2X_COMPAT', language:'c')

	# windows resource compiler .rc file
	ver_array = meson.project_version().split('.')
	windows = import('windows')
	yaabe_exe_src += windows.compile_resources(configure_file(
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

# in order to give a selection of c files their own C_FLAGS we need to group
# them into a static library. The flags in declare_dependency() are for the
# thing that uses the dependency.
# TODO see if 1.6.0's declare_dependency().as_static() is useful
libyaabe_autogen = static_library('libyaabe_autogen',
	sources: yaabe_autogen_src,
	include_directories: include_dirs,
	dependencies: (external_depends + autogen_depends),
	c_args: [ # autogen'd code is noisy; mute
		'-Wno-unused-variable',
		'-Wno-override-init',
	],
	name_prefix: '',
)
include_dirs += libyaabe_autogen.private_dir_include()

libyaabe = static_library('libyaabe',
	sources: yaabe_src,
	link_with: libyaabe_autogen,
	include_directories: include_dirs,
	dependencies: external_depends,
	name_prefix: '',
)
yaabe = executable('yaabe',
	sources: files('main.c') + yaabe_exe_src,
	link_with: libyaabe,
	include_directories: include_dirs,
	dependencies: external_depends,
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



yaabe_test = executable('yaabe_test',
	sources: files('test.c') + yaabe_exe_src,
	include_directories: [
		include_dirs,
		libyaabe.private_dir_include()
	],
	dependencies: external_depends,
	link_with: libyaabe,
	install: false,
	win_subsystem: 'windows',
	build_by_default: false,
)

# all test_roms/*.rom will become a test
# If you already built but want to change the roms,
# meson --reconfigure
test_roms_dir = 'test_roms'
test_roms_fail_dir = test_roms_dir + '_fail'
romfiles = files()
romfiles_fail = files()
if fs.is_dir(test_roms_dir)
	lsroms = run_command('ls', test_roms_dir, check:false)
	if 0 == lsroms.returncode()
		foreach name : lsroms.stdout().strip().split('\n')
			if name.endswith('.rom')
				romfiles += files(join_paths(test_roms_dir, name))
			endif
		endforeach
	endif
	lsroms = run_command('ls', test_roms_fail_dir, check:false)
	if 0 == lsroms.returncode()
		foreach name : lsroms.stdout().strip().split('\n')
			if name.endswith('.rom')
				romfiles_fail += files(join_paths(test_roms_fail_dir, name))
			endif
		endforeach
	endif
endif
foreach bios : romfiles
	test(fs.name(bios),
		yaabe_test, args: [bios],
		env: ['G_DEBUG=fatal_warnings',],
		suite: ['yaabe', 'pass'],
		timeout: 60,

	)
endforeach
foreach bios : romfiles_fail
	test(fs.name(bios),
		yaabe_test, args: [bios],
		env: ['G_DEBUG=fatal_warnings',],
		suite: ['yaabe', 'fail'],
		timeout: 60,
		should_fail: true,
	)
endforeach
