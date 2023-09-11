# Yet Another AtomBIOS Editor

YAABE is an AMD/ATI GPU VBIOS editor with a major focus on exposing the full
data structures of the VBIOS, rather than just the notable tidbits an
overclocker may want.

This VBIOS editor does not hold your hand; it exposes a lot and you should have
an idea what you're looking for and what it does. Until I get descriptions up
and running, it is reccommended to view the header files under `amd/` in tandem.

## TODO

This BIOS editor is still in its early stages. The most important thing is
simply populating the tables; making ATUI representations for the tables within
`atomfirmware.h` et al. and hooking it up into the atomtree. There is also a
bunch of smaller things to figure out, which can be be found through
`grep -RHine TODO`.

## Compiling

YAABE uses GTK 4.10 and the (upcoming) C standard C23/C2x. 

### Linux

Make sure you have the GTK 4 suite installed. For Debian and kin,
`# apt-get install libgtk-4-dev`

then `$ make -j $(nproc) release`

### Windows

TODO https://www.gtk.org/docs/installations/windows

## Useful Resources

https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/drivers/gpu/drm/amd

https://github.com/OhGodAPet/amdtimingcopy

https://github.com/IndeedMiners/PolarisBiosEditor

https://www.overclock.net/threads/polaris-bios-editing-rx5xx-rx4xx.1604567/page-271

https://github.com/Eliovp/amdmemorytweak

https://github.com/andybf/atombioseditor

https://www.igorslab.de/red-bios-editor-bios-eintraege-anpassen-optimieren-und-noch-stabiler-uebertakten-navi-unlimited

https://github.com/cyring/CoreFreq

https://www.jedec.org/standards-documents/docs/jesd250d
