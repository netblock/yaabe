from sys import argv
import os
import shutil
import subprocess

# enviornment assumes msys2

def enlist_shared_objs(linked_obj:str, objs:set):
	# objdump -p is unnecessarily more powerful
	# ntldd is unexplored; might ultimately be the same as msys2 ldd
	out = subprocess.check_output(("ldd", linked_obj), text=True)
	lines = out.strip().split("\n")
	for l in lines:
		parts = l.split()
		if len(parts) != 4: # name => loc (addr)
			continue
		lib = parts[2]
		if (lib[:6] == "/mingw") and (lib not in objs):
			objs.add(lib)
			enlist_shared_objs(lib, objs)

def gather_assets(source_dir:str, exe_file:str, stage_dir:str):
	share_dir = os.path.join(stage_dir, "share")
	glib_dir = os.path.join(share_dir, "glib-2.0")
	themes_dir = os.path.join(stage_dir, "themes")
	shutil.copytree(
		os.path.join(source_dir, "gtk-assets"),
		stage_dir,
		dirs_exist_ok=True
	)
	shutil.copy(exe_file, stage_dir)
	shutil.copy(os.path.join(source_dir, "LICENSE"), stage_dir)
	shutil.copytree(
		"/mingw64/share/glib-2.0/schemas",
		glib_dir,
		dirs_exist_ok=True
	)
	shutil.copytree(
		"/mingw64/share/glib-2.0/icons",
		share_dir,
		dirs_exist_ok=True
	)

	# gtk is nonstandard on windows; find all relevant mingw .dlls 
	shared_objs = set()
	enlist_shared_objs(exe_file, shared_objs)
	for obj in shared_objs:
		shutil.copy(obj, stage_dir)

def main(argc:int, argv:list):
	assert (argc >= 9)
	glib_compile_schemas = argv[1]
	makensis = argv[2]
	nsis_conf = argv[3] 
	source_dir = argv[4]
	exe_file = argv[5]
	stage_dir = argv[6]
	output_exe = argv[7]
	project_ver = argv[8]

	gather_assets(source_dir, exe_file, stage_dir)

	subprocess.run((
		glib_compile_schemas,
		os.path.join(stage_dir, "share", "glib-2.0", "schemas"),
	))

	subprocess.run((
		makensis,
		"-NOCD", # nsis would cd to the .nsi
		"-V2",
		"-Dyaabe_version=" + project_ver,
		"-Dnsis_stage_dir=" + stage_dir,
		"-Dyaabe_outfile=" + output_exe,
		nsis_conf,
	))

if (__name__ == "__main__"):
	main(len(argv), argv)
