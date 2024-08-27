/*
All tables that would map bios data
*/

#ifndef BIOS_HEADERS_H
#define BIOS_HEADERS_H

#include "gmc.h"
#include "gc.h"
#include "ddrmoderegisters.h"
#include "bitfield_overrides.h"
#include "asic_reg_data_tables.h"
#include "atombios.h"
#include "atomfirmware.h"
#include "powerplay.h"

// make sure we're not on 1-byte packing after all the including
static_assert(sizeof(struct {uint64_t a; uint8_t b; uint64_t c;}) == 24);

#endif
