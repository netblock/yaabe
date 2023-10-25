CC=cc

YAABE_DEBUG_CFLAGS = -g -Og
YAABE_RELEASE_CFLAGS = -O3 -flto=auto -fuse-linker-plugin
GTK_CFLAGS = `pkg-config --cflags gtk4`
GTK_LDFLAGS = `pkg-config --libs gtk4`
YAABE_LDFLAGS =  -lm -lz $(GTK_LDFLAGS)
YAABE_CFLAGS = -std=c2x -Iatom -Iatomtree -Igtk $(GTK_CFLAGS)

SRCS = $(wildcard *.c atom/*.c atomtree/*.c gtk/*.c)
OBJS = $(SRCS:%.c=out/%.o)
DIRS = out/atom/.keep out/atomtree/.keep out/gtk/.keep
YAABE_EXE = yaabe
NSIS_STAGE_DIR = nsis_stage

.PHONY: all
all: debug


.PHONY: debug
debug: CFLAGS = $(YAABE_CFLAGS) $(YAABE_DEBUG_CFLAGS)
debug: LDFLAGS = $(YAABE_LDFLAGS) $(YAABE_DEBUG_LDFLAGS)
debug: yaabe

.PHONY: release
release: CFLAGS = $(YAABE_CFLAGS) $(YAABE_RELEASE_CFLAGS)
release: LDFLAGS = $(YAABE_LDFLAGS) $(YAABE_RELEASE_LDFLAGS)
release: yaabe
	strip -s $(YAABE_EXE)

.PHONY: windows_debug
windows_debug: YAABE_CFLAGS += -DC2X_COMPAT # msys2 isn't caught up with C23
windows_debug: YAABE_LDFLAGS += -mwindows
windows_debug: YAABE_EXE = yaabe.exe
windows_debug: debug

.PHONY: windows
windows: YAABE_CFLAGS += -DC2X_COMPAT # msys2 isn't caught up withC23
windows: YAABE_LDFLAGS += -mwindows
windows: YAABE_EXE = yaabe.exe
windows: release


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
	makensis -Dnsis_stage_dir=$(NSIS_STAGE_DIR) yaabe.nsi


.PHONY: yaabe
yaabe: $(OBJS)
	$(CC) $(OBJS) -o $(YAABE_EXE) $(LDFLAGS) $(CFLAGS)

out/%.o: %.c dirs
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: dirs
dirs: $(DIRS)
$(DIRS):
	mkdir -p $(@D)	
	touch $@

.PHONY: clean
clean:
	rm -rf yaabe yaabeinstaller.exe
	rm -rf out $(NSIS_STAGE_DIR)
