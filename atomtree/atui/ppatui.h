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
		&(struct atui_funcify_args const) {\
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
	child->parent_branch = parent;\
	parent->num_branches++;

// ATUI function access
#define ATUI_FUNC(atomstruct)\
	_##atomstruct##_atui

// enum access
// ATUI_ENUM_ARRAY_LENGTH is predefined
#define ATUI_ENUM_ARRAY _atui_enumarray
#define ATUI_ENUM_INDEX(enum_name) _atui_enum_index_##enum_name
#define ATUI_ENUM(enum_name) ATUI_ENUM_ARRAY[ATUI_ENUM_INDEX(enum_name)]

/***************************** PREPROCESSOR TOOLS *****************************/

#define _atui_enum_ATUI_NULL ATUI_NULL

// To define the header entries for the aformentioned allocator functions.
#define PPATUI_HEADERIFY(atom_struct)\
	atui_branch* ATUI_FUNC(atom_struct)(\
		struct atui_funcify_args const* const args\
	)

#define _PPATUI_NULLPTR(var) _Generic((var),\
	nullptr_t: nullptr,\
	default: &(var)\
)
#define _PPATUI_NULLPTR_SIZE(var) _Generic((var),\
	nullptr_t: 0,\
	atui_nullstruct: 0,\
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
	uint24_t:24, uint24_t*:24, uint24_t const*:24,\
	uint48_t:48, uint48_t*:48, uint48_t const*:48,\
	int24_t:24, int24_t*:24, int24_t const*:24,\
	int48_t:48, int48_t*:48, int48_t const*:48,\
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
	default:-1\
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
	int8_t:true, int8_t*:true, int8_t const*:true,\
	int16_t:true, int16_t*:true, int16_t const*:true,\
	int32_t:true, int32_t*:true, int32_t const*:true,\
	int64_t:true, int64_t*:true, int64_t const*:true,\
\
	int24_t:true, int24_t*:true, int24_t const*:true,\
	int48_t:true, int48_t*:true, int48_t const*:true,\
\
/*
	float16_t:true, float16_t*:true,\
	float16_t const*:true,\
	float32_t:true, float32_t*:true,\
	float32_t const*:true,\
	float64_t:true, float64_t*:true,\
	float64_t const*:true,\
*/\
\
	default:false\
)

#define _PPATUI_LEAF_FRACTION(var) _Generic((var),\
	float16_t:true, float16_t*:true, float16_t const*:true,\
	float32_t:true, float32_t*:true, float32_t const*:true,\
	float64_t:true, float64_t*:true, float64_t const*:true,\
\
	uq6_2_t:true, uq6_2_t*:true, uq6_2_t const*:true,\
	uq4_4_t:true, uq4_4_t*:true, uq4_4_t const*:true,\
\
	uq14_2_t:true, uq14_2_t*:true, uq14_2_t const*:true,\
	uq8_8_t:true, uq8_8_t*:true, uq8_8_t const*:true,\
\
	uq30_2_t:true, uq30_2_t*:true, uq30_2_t const*:true,\
	uq16_16_t:true, uq16_16_t*:true, uq16_16_t const*:true,\
\
	default:false\
)

#endif
