/*
All tables that would map bios data
*/

#ifndef BIOS_HEADERS_H
#define BIOS_HEADERS_H

// general custom structs
#pragma pack(push, 1) // bios data must use byte alignment
union magic_16 {
	char str[2] __nonstring;
	uint16_t num;
};
union magic_24 {
	char str[3] __nonstring;
	uint24_t num;
};
union magic_32 {
	char str[4] __nonstring;
	uint32_t num;
};
union magic_64 {
	char str[8] __nonstring;
	uint64_t num;
};
#pragma pack(pop) // restore old packing

#include "gmc.h"
#include "gc.h"
#include "ddrmoderegisters.h"
#include "bitfield_overrides.h"
#include "asic_reg_data_tables.h"
#include "pci.h"
#include "psp.h"
#include "discovery.h"
#include "atombios.h"
#include "powerplay.h"
#include "atomfirmware.h"

// make sure we're not on 1-byte packing after all the including
static_assert(sizeof(struct {uint64_t a; uint8_t b; uint64_t c;}) == 24);

#endif
