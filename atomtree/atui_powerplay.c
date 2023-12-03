/*
For powerplay.h -- common powerplay definitions
See atui_atomfirmware.c for how to use PPATUI_FUNCIFY()
*/

#include "atomtree.h"
#include "atui.h"

PPATUI_FUNCIFY(struct, smu_powerplay_table_header, atomtree_powerplaytable,
	(bios->header, "atom_common_table_header",
		(ATUI_NAN, ATUI_INLINE, atom_common_table_header),
		(ATUI_NODESCR)
	),
	(bios->table_revision, "table_revision",
		(ATUI_DEC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->table_size, "table_size",
		(ATUI_DEC, ATUI_NOFANCY),
		((LANG_ENG, "Driver portion table size. The offset to smc_pptable including header size"))
	)
)

PPATUI_FUNCIFY(union, powerplay_platform_caps, atomtree_powerplaytable,
	(bios->platform_caps, "platform_caps",
		(ATUI_BIN, ATUI_BITFIELD, (
			("powerplay",     0,0, ATUI_DEC, ((LANG_ENG, "whether CCC needs to show Powerplay page."))),
			("sbios_powersource", 1,1, ATUI_DEC, ((LANG_ENG, "whether power source notificaiton is done by SBIOS instead of OS."))),
			("hardware_dc",   2,2, ATUI_DEC, ((LANG_ENG, "whether DC mode notificaiton is done by GPIO pin directly."))),
			("BACO",          3,3, ATUI_DEC, ((LANG_ENG, "whether board supports the BACO circuitry. BACO is Bus Active, Chip Off. A low-power mode whereby most of the GPU is shut-off during idle periods in order to drastically cut the power consumption of the graphics card. BACO is also known as AMD ZeroCore Power mode."))),
			("MACO",          4,4, ATUI_DEC, ((LANG_ENG, "whether board supports the MACO circuitry."))),
			("shadow_pstate", 5,5, ATUI_DEC, ((LANG_ENG, "whether board supports the Shadow Pstate."))),
			("reserved",     31,6, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)


PPATUI_FUNCIFY(struct, quadratic_f32, atomtree_powerplaytable,
	(bios->a, "a (float)",
		(ATUI_FRAC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->b, "b (float)",
		(ATUI_FRAC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->c, "c (float)",
		(ATUI_FRAC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->a, "a (raw)",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->b, "b (raw)",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->c, "c (raw)",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, linear_f32, atomtree_powerplaytable,
	(bios->m, "m (float)",
		(ATUI_FRAC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->b, "b (float)",
		(ATUI_FRAC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->m, "m (raw)",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->b, "b (raw)",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)
PPATUI_FUNCIFY(struct, droop_f32, atomtree_powerplaytable,
	(bios->a, "a (float)",
		(ATUI_FRAC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->b, "b (float)",
		(ATUI_FRAC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->c, "c (float)",
		(ATUI_FRAC, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->a, "a (raw)",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->b, "b (raw)",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	),
	(bios->c, "c (raw)",
		(ATUI_HEX, ATUI_NOFANCY), (ATUI_NODESCR)
	)
)

PPATUI_FUNCIFY(union, led_display_control, atui_nullstruct,
	(bios->LedEnableMask, "LedEnableMask",
		(ATUI_BIN, ATUI_BITFIELD, (
			("GFX_DPM",  0,0, ATUI_DEC, (ATUI_NODESCR)),
			("PCIE",     1,1, ATUI_DEC, (ATUI_NODESCR)),
			("ERROR",    2,2, ATUI_DEC, (ATUI_NODESCR)),
			("reserved", 7,3, ATUI_DEC, (ATUI_NODESCR))
		)), (ATUI_NODESCR)
	)
)

