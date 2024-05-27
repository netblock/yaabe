#!/usr/bin/env python
# -*- coding: utf-8 -*-

from sys import argv
import os
import shutil
import subprocess

# enviornment assumes msys2

def enlist_shared_objs(
		linked_obj:str,
		objs:set
		):
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

def copy_skeuos(
		source_dir:str,
		themes_dir:str
		):
	skeuos_themes = os.path.join(source_dir, "skeuos-gtk", "themes")
	blue_light = "Skeuos-Blue-Light"
	blue_light_src = os.path.join(skeuos_themes, blue_light)
	if os.path.isdir(blue_light_src):
		shutil.copytree(
			blue_light_src,
			os.path.join(themes_dir, blue_light),
			dirs_exist_ok=True
		)
	blue_dark = "Skeuos-Blue-Dark"
	blue_dark_src = os.path.join(skeuos_themes, blue_dark)
	if os.path.isdir(blue_dark_src):
		shutil.copytree(
			blue_dark_src,
			os.path.join(themes_dir, blue_dark),
			dirs_exist_ok=True
		)

def gather_assets(
		source_dir:str,
		exe_file:str,
		stage_dir:str
		):
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
	shutil.copy(os.path.join(source_dir, "THIRD_PARTY_LICENSE"), stage_dir)

	copy_skeuos(source_dir, themes_dir)

	# cygpath translates / into an absolute path drive letter and all
	root = subprocess.check_output(("cygpath", "-m", "/"), text=True)
	root = root.strip().replace("/", os.path.sep)
	host_share_dir = os.path.join(root, "mingw64", "share")
	shutil.copytree(
		os.path.join(host_share_dir, "glib-2.0", "schemas"),
		os.path.join(glib_dir, "schemas"),
		dirs_exist_ok=True
	)
	shutil.copytree(
		os.path.join(host_share_dir, "icons"),
		os.path.join(share_dir, "icons"),
		dirs_exist_ok=True
	)

	# gtk is nonstandard on windows; find all relevant mingw .dlls
	shared_objs = set()
	enlist_shared_objs(exe_file, shared_objs)
	for obj in shared_objs:
		obj_cleaned_path = os.path.join(
			root,
			obj[1:].replace("/", os.path.sep) # strip first /, replace
		)
		shutil.copy(obj_cleaned_path, stage_dir)

def main(
		argc:int,
		argv:list
		):
	assert (argc >= 7)
	nsis_conf = argv[1]
	source_dir = argv[2]
	exe_file = argv[3]
	stage_dir = argv[4]
	output_exe = argv[5]
	project_ver = argv[6]

	gather_assets(source_dir, exe_file, stage_dir)

	subprocess.run((
		"glib-compile-schemas",
		os.path.join(stage_dir, "share", "glib-2.0", "schemas"),
	))

	subprocess.run((
		"makensis",
		"-NOCD", # nsis would cd to the .nsi
		"-V2",
		"-Dyaabe_version=" + project_ver,
		"-Dnsis_stage_dir=" + stage_dir,
		"-Dyaabe_outfile=" + output_exe,
		nsis_conf,
	))

if (__name__ == "__main__"):
	main(len(argv), argv)
