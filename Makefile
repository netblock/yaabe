CC=cc

SRCS = $(wildcard *.c atom/*.c atomtree/*.c)
OBJS = $(SRCS:%.c=out/%.o)
YAABE_LDFLAGS := -pthread -lz -lm -ldl
YAABE_CFLAGS = -Iamd -Iatomtree

all: yaabe

-include $(SRCS:%.c=out/%.d)

yaabe: $(OBJS)
	$(CC) $(OBJS) -o $@ $(YAABE_LDFLAGS)

out/%.o: %.c out/atom/.keep out/atomtree/.keep
	$(CC) $(YAABE_CFLAGS) -c -o $@ $<

out/atom/.keep out/atomtree/.keep:
	mkdir -p $(@D)	
	touch $@

clean:
	rm -rf yaabe out

