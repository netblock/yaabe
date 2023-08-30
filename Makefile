CC=cc
WIN_CC=x86_64-w64-mingw32-gcc
# TODO https://www.gtk.org/docs/installations/windows/

GTK_CFLAGS = `pkg-config --cflags gtk4`
GTK_LDFLAGS = `pkg-config --libs gtk4`
YAABE_LDFLAGS :=  $(GTK_LDFLAGS)
YAABE_CFLAGS = -std=c2x -Iamd -Iatomtree -Igtk $(GTK_CFLAGS)

YAABE_DEBUG_CFLAGS = -g -Og
YAABE_RELEASE_CFLAGS = -O2 -flto=jobserver


SRCS = $(wildcard *.c atom/*.c atomtree/*.c gtk/*.c)
OBJS = $(SRCS:%.c=out/%.o)
DIRS = out/atom/.keep out/atomtree/.keep out/gtk/.keep

all: debug

debug: CFLAGS := $(YAABE_CFLAGS) $(YAABE_DEBUG_CFLAGS)
debug: LDFLAGS := $(YAABE_LDFLAGS) $(YAABE_DEBUG_LDFLAGS)
debug: yaabe

release: CFLAGS := $(YAABE_CFLAGS) $(YAABE_RELEASE_CFLAGS)
release: LDFLAGS := $(YAABE_LDFLAGS) $(YAABE_RELEASE_LDFLAGS)
release: strip #yaabe

windows: CC := $(WIN_CC)
windows: release

strip: yaabe
	strip -s $<

yaabe: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

out/%.o: %.c dirs
	$(CC) $(CFLAGS) -c -o $@ $<

dirs: $(DIRS)
$(DIRS):
	mkdir -p $(@D)	
	touch $@

clean:
	rm -rf yaabe out
