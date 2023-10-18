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
	rm -rf yaabe out
