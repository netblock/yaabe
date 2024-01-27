/*
For powerplay.h -- common powerplay definitions
See atui_atomfirmware.c for how to use PPATUI_FUNCIFY()
*/

#include "atomtree.h"
#include "atui.h"

PPATUI_FUNCIFY(struct, smu_powerplay_table_header, atomtree_powerplaytable,
	(bios->header, u8"atom_common_table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->table_revision, u8"table_revision",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->table_size, u8"table_size",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, u8"Driver portion table size. The offset to smc_pptable including header size"))
	)
)

PPATUI_FUNCIFY(union, powerplay_platform_caps, atomtree_powerplaytable,
	(bios->platform_caps, u8"platform_caps",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"powerplay",     0,0, ATUI_DEC, ((LANG_ENG, u8"whether CCC needs to show Powerplay page."))),
			(u8"sbios_powersource", 1,1, ATUI_DEC, ((LANG_ENG, u8"whether power source notificaiton is done by SBIOS instead of OS."))),
			(u8"hardware_dc",   2,2, ATUI_DEC, ((LANG_ENG, u8"whether DC mode notificaiton is done by GPIO pin directly."))),
			(u8"BACO",          3,3, ATUI_DEC, ((LANG_ENG, u8"whether board supports the BACO circuitry. BACO is Bus Active, Chip Off. A low-power mode whereby most of the GPU is shut-off during idle periods in order to drastically cut the power consumption of the graphics card. BACO is also known as AMD ZeroCore Power mode."))),
			(u8"MACO",          4,4, ATUI_DEC, ((LANG_ENG, u8"whether board supports the MACO circuitry."))),
			(u8"shadow_pstate", 5,5, ATUI_DEC, ((LANG_ENG, u8"whether board supports the Shadow Pstate."))),
			(u8"reserved",     31,6, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, quadratic_f32, atomtree_powerplaytable,
	(bios->a, u8"a",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->b, u8"b",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->c, u8"c",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, linear_f32, atomtree_powerplaytable,
	(bios->m, u8"m",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->b, u8"b",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, droop_f32, atomtree_powerplaytable,
	(bios->a, u8"a",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->b, u8"b",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->c, u8"c",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, led_display_control, atui_nullstruct,
	(bios->LedEnableMask, u8"LedEnableMask",
		(ATUI_BIN, ATUI_BITFIELD, (
			(u8"GFX_DPM",  0,0, ATUI_DEC, (ATUI_NODESCR)),
			(u8"PCIE",     1,1, ATUI_DEC, (ATUI_NODESCR)),
			(u8"ERROR",    2,2, ATUI_DEC, (ATUI_NODESCR)),
			(u8"reserved", 7,3, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

