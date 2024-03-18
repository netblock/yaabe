/*
C preprocessor side of ATUI table generation
*/

#ifndef PPATUI_H
#define PPATUI_H

/******************************* MAIN FUNCTIONS *******************************/

// Thing to call to instanciate an atui_branch
#define ATUI_MAKE_BRANCH(\
		atom_struct_name,\
		new_name, atomtree_pointer, bios_pointer,\
		num_branches, branch_import_pointer)\
\
	_##atom_struct_name##_atui(\
		&(const struct atui_funcify_args) {\
			.rename = new_name,\
			.atomtree = atomtree_pointer,\
			.suggestbios = bios_pointer,\
			.import_branches = branch_import_pointer,\
			.num_import_branches = num_branches,\
		}\
	)

// Add a child branch to a parent branch
#define ATUI_ADD_BRANCH(parent, child)\
	assert(parent->num_branches < parent->max_num_branches);\
	parent->child_branches[parent->num_branches] = child;\
	parent->num_branches++;

// ATUI function access
#define ATUI_FUNC(atomstruct)\
	_##atomstruct##_atui

// enum access
#define ATUI_ENUM(enum_name) _atui_enum_##enum_name

/***************************** PREPROCESSOR TOOLS *****************************/

#define _atui_enum_ATUI_NULL ATUI_NULL

// To define the header entries for the aformentioned allocator functions.
#define PPATUI_HEADERIFY(atom_struct)\
	atui_branch* ATUI_FUNC(atom_struct)(\
		const struct atui_funcify_args* const args\
	)

#define _PPATUI_NULLPTR(var) _Generic((var),\
	nullptr_t: nullptr,\
	default: &(var)\
)
#define _PPATUI_NULLPTR_SIZE(var) _Generic((var),\
	nullptr_t: 0,\
	default: sizeof(var)\
)

#define _PPATUI_LEAF_BITNESS(var) _Generic((var),\
	uint8_t:8, uint8_t*:8, uint8_t const*:8,\
	uint16_t:16, uint16_t*:16, uint16_t const*:16,\
	uint32_t:32, uint32_t*:32, uint32_t const*:32,\
	uint64_t:64, uint64_t*:64, uint64_t const*:64,\
\
	int8_t:8, int8_t*:8, int8_t const*:8,\
	int16_t:16, int16_t*:16, int16_t const*:16,\
	int32_t:32, int32_t*:32, int32_t const*:32,\
	int64_t:64, int64_t*:64, int64_t const*:64,\
\
	uq6_2_t:8, uq6_2_t*:8, uq6_2_t const*:8,\
	uq4_4_t:8, uq4_4_t*:8, uq4_4_t const*:8,\
	uq14_2_t:16, uq14_2_t*:16, uq14_2_t const*:16,\
	uq8_8_t:16, uq8_8_t*:16, uq8_8_t const*:16,\
	uq30_2_t:32, uq30_2_t*:32, uq30_2_t const*:32,\
	uq16_16_t:32, uq16_16_t*:32, uq16_16_t const*:32,\
\
	float16_t:16, float16_t*:16, float16_t const*:16,\
	float32_t:32, float32_t*:32, float32_t const*:32,\
	float64_t:64, float64_t*:64, float64_t const*:64,\
\
	default:0\
)

#define _PPATUI_LEAF_FIXED_FRACTION_BITS(var) _Generic((var),\
	uq6_2_t:2, uq6_2_t*:2, uq6_2_t const*:2,\
	uq4_4_t:4, uq4_4_t*:4, uq4_4_t const*:4,\
\
	uq14_2_t:2, uq14_2_t*:2, uq14_2_t const*:2,\
	uq8_8_t:8, uq8_8_t*:8, uq8_8_t const*:8,\
\
	uq30_2_t:2, uq30_2_t*:2, uq30_2_t const*:2,\
	uq16_16_t:16, uq16_16_t*:16, uq16_16_t const*:16,\
\
	default:0\
)

#define _PPATUI_LEAF_SIGNED(var) _Generic((var),\
	int8_t:ATUI_SIGNED, int8_t*:ATUI_SIGNED, int8_t const*:ATUI_SIGNED,\
	int16_t:ATUI_SIGNED, int16_t*:ATUI_SIGNED, int16_t const*:ATUI_SIGNED,\
	int32_t:ATUI_SIGNED, int32_t*:ATUI_SIGNED, int32_t const*:ATUI_SIGNED,\
	int64_t:ATUI_SIGNED, int64_t*:ATUI_SIGNED, int64_t const*:ATUI_SIGNED,\
\
/*
	float16_t:ATUI_SIGNED, float16_t*:ATUI_SIGNED,\
	float16_t const*:ATUI_SIGNED,\
	float32_t:ATUI_SIGNED, float32_t*:ATUI_SIGNED,\
	float32_t const*:ATUI_SIGNED,\
	float64_t:ATUI_SIGNED, float64_t*:ATUI_SIGNED,\
	float64_t const*:ATUI_SIGNED,\
*/\
\
	default:0\
)

#define _PPATUI_LEAF_FRACTION(var) _Generic((var),\
	float16_t:ATUI_FRAC, float16_t*:ATUI_FRAC, float16_t const*:ATUI_FRAC,\
	float32_t:ATUI_FRAC, float32_t*:ATUI_FRAC, float32_t const*:ATUI_FRAC,\
	float64_t:ATUI_FRAC, float64_t*:ATUI_FRAC, float64_t const*:ATUI_FRAC,\
\
	uq6_2_t:ATUI_FRAC, uq6_2_t*:ATUI_FRAC, uq6_2_t const*:ATUI_FRAC,\
	uq4_4_t:ATUI_FRAC, uq4_4_t*:ATUI_FRAC, uq4_4_t const*:ATUI_FRAC,\
\
	uq14_2_t:ATUI_FRAC, uq14_2_t*:ATUI_FRAC, uq14_2_t const*:ATUI_FRAC,\
	uq8_8_t:ATUI_FRAC, uq8_8_t*:ATUI_FRAC, uq8_8_t const*:ATUI_FRAC,\
\
	uq30_2_t:ATUI_FRAC, uq30_2_t*:ATUI_FRAC, uq30_2_t const*:ATUI_FRAC,\
	uq16_16_t:ATUI_FRAC, uq16_16_t*:ATUI_FRAC, uq16_16_t const*:ATUI_FRAC,\
\
	default:0\
)

#endif
