# Yet Another AtomBIOS Editor

YAABE is an AMD/ATI GPU VBIOS editor with a major focus on exposing the full
data structures of the VBIOS, rather than just the notable tidbits an
overclocker may want.

This VBIOS editor does not hold your hand; it exposes a lot and you should have
an idea what you're looking for and what it does. Until I get descriptions up
and running, it is reccommended to view the header files under `atom/` in tandem.

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

Install [MSYS2](https://www.msys2.org) (MSYS2 must be installed on an NTFS partition.
FAT and ReFS doesn't work), and when in the msys2 shell, install mingw toolchain and
the gtk4 libraries, 

```shell
pacman -Syu # update if it's an old install
pacman -S mingw-w64-x86_64-toolchain base-devel mingw-w64-x86_64-gtk4 mingw-w64-x86_64-nsis
```

(The msys2 shell root `/` is the msys2 install location. Your current working directory
when you open the msys2 shell is your username under `home/`). Plop the YAABE source in
a place you can reach it within msys2, cd to it, and then,

```shell
export PATH="$PATH:/mingw64/bin"
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/mingw64/lib/pkgconfig"
make -j $(nproc) windows
```

Optionally, create an installer wizard through NSIS,

```shell
export PATH="$PATH:/mingw64/bin"
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/mingw64/lib/pkgconfig"
make -j $(nproc) nsis-installer
```

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
