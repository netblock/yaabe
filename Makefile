CC=cc

SRCS = $(wildcard *.c atom/*.c atomtree/*.c gtk/*.c)
OBJS = $(SRCS:%.c=out/%.o)


GTK_CFLAGS = `pkg-config --cflags gtk4`
GTK_LDFLAGS = `pkg-config --libs gtk4`
YAABE_LDFLAGS := -pthread -lz -lm -ldl $(GTK_LDFLAGS)
YAABE_CFLAGS = -g -Og -std=c2x -Iamd -Iatomtree -Igtk $(GTK_CFLAGS)

all: yaabe

-include $(SRCS:%.c=out/%.d)

yaabe: $(OBJS)
	$(CC) $(OBJS) -o $@ $(YAABE_LDFLAGS)

out/%.o: %.c out/atom/.keep out/atomtree/.keep out/gtk/.keep
	$(CC) $(YAABE_CFLAGS) -c -o $@ $<

out/atom/.keep out/atomtree/.keep out/gtk/.keep:
	mkdir -p $(@D)	
	touch $@

clean:
	rm -rf yaabe out

