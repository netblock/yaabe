/*
C preprocessor side of ATUI table generation
*/

#ifndef PPATUI_H
#define PPATUI_H

/******************************* MAIN FUNCTIONS *******************************/

// Thing to call to instanciate an atui_node
#define ATUI_MAKE_BRANCH(\
		atom_struct_name,  new_name,\
		atomtree_pointer, bios_pointer,\
		num_branches, branch_import_pointer)\
	_atui_##atom_struct_name(\
		& (atuifunc_args const) {\
			.rename = new_name,\
			.atomtree = atomtree_pointer,\
			.bios = bios_pointer,\
			.import_branches = branch_import_pointer,\
			.num_import_branches = num_branches,\
		}\
	)

// Add a child branch to a parent branch
#define ATUI_ADD_BRANCH(parentptr, childptr) do {\
	atui_node* const restrict parent = parentptr;\
	atui_node* const restrict child = childptr;\
	assert(parent != child);\
\
	struct atui_children* const parents_book = &(parent->branch.branches);\
	assert(parents_book->indirect);\
	assert(false == child->bundled);\
\
	assert(parents_book->count < parents_book->max_count);\
	parents_book->addresses[parents_book->count] = child;\
	child->parent = parent;\
	parents_book->count++;\
} while(0)

// enum access
// ATUI_ENUM_ARRAY_LENGTH is predefined
#define ATUI_ENUM_ARRAY _atui_enumarray
#define ATUI_ENUM_INDEX(enum_name) _atui_enum_index_##enum_name
#define ATUI_ENUM(enum_name) ATUI_ENUM_ARRAY[ATUI_ENUM_INDEX(enum_name)]

/***************************** PREPROCESSOR TOOLS *****************************/

#define _atui_enum_ATUI_NULL ATUI_NULL
#define _atui_enum_NULL NULL ATUI_NULL
#define _atui_enum_index_NULL ATUI_ENUM_ARRAY_LENGTH

#define _PPATUI_NULLPTR(var) _Generic((var),\
	nullptr_t: nullptr,\
	default: &(var)\
)
#define _PPATUI_NULLPTR_SIZE(var) _Generic((var),\
	nullptr_t: 0,\
	atui_nullstruct: 0,\
	default: sizeof(var)\
)
#define _PPATUI_PREFER_CONTIGUOUS(bios, num_bytes) (\
	(0 < _PPATUI_NULLPTR_SIZE(*(bios)))\
	&& (\
		(num_bytes)\
		<= _PPATUI_NULLPTR_SIZE(*(bios))\
	)\
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
/* no current purpose in flagging the floats
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


// bitfield tools to extract various details of a little-endian bitfield
// -O1 and higher compiles to a constexpr number
#define _PPATUI_BIT_SIZEOF(bios, f) _BIT_SIZEOF(typeof(bios), f)
#define _BIT_SIZEOF(un, f) (\
	stdc_count_ones((un) {.f = -1}.f)\
)
#define _PPATUI_BIT_LO(bios, f) _BIT_LO(typeof(bios), f)
#define _BIT_LO(un, f) (\
	stdc_first_trailing_one(\
		(union {\
			un anon;\
			uint64_t all;\
		}) {\
			.anon.f = -1\
		}.all\
	) - 1\
)
#define _PPATUI_BIT_HI(bios, f) _BIT_HI(typeof(bios), f)
#define _BIT_HI(un, f) (\
	_BIT_LO(un, f) + _BIT_SIZEOF(un, f) - 1\
)


#endif
