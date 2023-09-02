CC=cc
WIN_CC=x86_64-w64-mingw32-gcc
# TODO https://www.gtk.org/docs/installations/windows/

YAABE_DEBUG_CFLAGS = -g -Og
YAABE_RELEASE_CFLAGS = -O3 -flto=auto -fuse-linker-plugin -fuse-ld=gold

GTK_CFLAGS = `pkg-config --cflags gtk4`
GTK_LDFLAGS = `pkg-config --libs gtk4`
YAABE_LDFLAGS =  -lm $(GTK_LDFLAGS)
YAABE_CFLAGS = -std=c2x -Iamd -Iatomtree -Igtk $(GTK_CFLAGS)



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

.PHONY: windows
windows: CC = $(WIN_CC)
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
