#TODO move to a build system like meson
CC=cc
WINDRES=windres

VER_MAJOR = 0
VER_MINOR = 1
VER_PATCH = 1
VERSION = $(VER_MAJOR).$(VER_MINOR).$(VER_PATCH)
VER_WINRC = $(VER_MAJOR),$(VER_MINOR),$(VER_PATCH),0 #for MS Resource Compiler

YAABE_DEBUG_CFLAGS = -g -Og
YAABE_RELEASE_CFLAGS = -DNDEBUG -O3 -flto=auto -fuse-linker-plugin
GTK_CFLAGS = `pkg-config --cflags gtk4`
GTK_LDFLAGS = `pkg-config --libs gtk4`
YAABE_LDFLAGS =  -lm -lz $(GTK_LDFLAGS)
YAABE_CFLAGS = -std=c2x -Iatom -Iatomtree -Igtk -DYAABE_VERSION="$(VERSION)" $(GTK_CFLAGS)

SRCS = $(wildcard *.c atom/*.c atomtree/*.c gtk/*.c)
OBJS = $(SRCS:%.c=out/%.o)
DIRS = out/atom/.keep out/atomtree/.keep out/gtk/.keep
NSIS_STAGE_DIR = nsis_stage



.PHONY: all
all: debug
.PHONY: debug
debug: CFLAGS = $(YAABE_CFLAGS) $(YAABE_DEBUG_CFLAGS)
debug: LDFLAGS = $(YAABE_LDFLAGS) $(YAABE_DEBUG_LDFLAGS)
debug: YAABE_EXE = yaabe
debug: _yaabe-linux

.PHONY: release
release: CFLAGS = $(YAABE_CFLAGS) $(YAABE_RELEASE_CFLAGS)
release: LDFLAGS = $(YAABE_LDFLAGS) $(YAABE_RELEASE_LDFLAGS)
release: YAABE_EXE = yaabe
release: _yaabe-linux
	strip -s $(YAABE_EXE)

.PHONY: windows-debug
windows-debug: CFLAGS = $(YAABE_CFLAGS) $(YAABE_DEBUG_CFLAGS) -DC2X_COMPAT # msys2 isn't caught up with C23
windows-debug: LDFLAGS = $(YAABE_LDFLAGS) $(YAABE_DEBUG_LDFLAGS) -mwindows
windows-debug: YAABE_EXE = yaabe.exe
windows-debug: WIN_DEBUG = -DVER_WIN_DBG
windows-debug: _yaabe-windows

.PHONY: windows
windows: CFLAGS = $(YAABE_CFLAGS) $(YAABE_RELEASE_CFLAGS) -DC2X_COMPAT # msys2 isn't caught up with C23
windows: LDFLAGS = $(YAABE_LDFLAGS) $(YAABE_RELEASE_LDFLAGS) -mwindows
windows: YAABE_EXE = yaabe.exe
windows: _yaabe-windows
	strip -s $(YAABE_EXE)

.PHONY: nsis-installer
nsis-installer: windows
	mkdir -p $(NSIS_STAGE_DIR)/share/glib-2.0 $(NSIS_STAGE_DIR)/share/themes
	cp yaabe.exe $(NSIS_STAGE_DIR)
	ldd $(NSIS_STAGE_DIR)/yaabe.exe | \
		grep "\/mingw.*\.dll" -o | \
		xargs -I{} cp "{}" $(NSIS_STAGE_DIR)
	cp -r gtk-assets/* $(NSIS_STAGE_DIR)
	cp -r /mingw64/share/glib-2.0/schemas $(NSIS_STAGE_DIR)/share/glib-2.0
	cp -r /mingw64/share/icons $(NSIS_STAGE_DIR)/share
	if [ -d third-party/Windows-10/gtk-4.0/ ]; then \
		mkdir -p $(NSIS_STAGE_DIR)/share/themes/Windows-10; \
		cp -r third-party/Windows-10/gtk-4.0 $(NSIS_STAGE_DIR)/share/themes/Windows-10; \
	fi
	glib-compile-schemas $(NSIS_STAGE_DIR)/share/glib-2.0/schemas
	makensis -Dnsis_stage_dir=$(NSIS_STAGE_DIR) -Dyaabe_version="$(VERSION)" yaabe.nsi





.PHONY: _yaabe-linux
_yaabe-linux: $(OBJS)
	$(CC) $? -o $(YAABE_EXE) $(LDFLAGS) $(CFLAGS)

.PHONY: _yaabe-windows
_yaabe-windows: $(OBJS) out/yaabe_rc.o
	$(CC) $? -o $(YAABE_EXE) $(LDFLAGS) $(CFLAGS)

out/yaabe_rc.o: yaabewindows.rc
	$(WINDRES) -DVER_WINRC="$(VER_WINRC)" $(WIN_DEBUG) -DVER_STR="$(VERSION)" -o $@ $<

out/%.o: %.c dirs
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: dirs
dirs: $(DIRS)
$(DIRS):
	mkdir -p $(@D)	

.PHONY: clean
clean:
	rm -rf yaabe yaabeinstaller-$(VERSION).exe
	rm -rf out $(NSIS_STAGE_DIR)
