/*
ATUI, specifically atui.c is intended to as human-readable as possible,
abstracting away the programatic consequences of allocation and setup.
This means that ATUI's allocater/instanciator functions have a lot of
that can be figured out at compile time.

For ATUI_FUNCIFY headers see atui_includes.h
See ppatui.h for the metaprogramming.

atui.h is about the main API for ATUI
*/

#ifndef ATUI_H
#define ATUI_H
#include "ppatui.h"
#include <atomtree.h>


// shall be used in an array
struct atui_enum {
	const char* name;
	int64_t val;
};

enum i18n_languages {
	LANG_NOLANG = -1,

	LANG_ENGLISH = 0,

	LANG_TOTALLANGS
};

// TODO https://open-std.org/JTC1/SC22/WG14/www/docs/n3042.htm
static const void* ATUI_NULL = NULL; // to satisfy _Generics handling pointers.
enum atui_type {
	ATUI_NAN = 0b000,
	ATUI_DEC = 0b001,
	ATUI_HEX = 0b010,
	ATUI_OCT = 0b011, // TODO not implemented
	ATUI_BIN = 0b100,
	ATUI_ANY = 0b111,

	ATUI_NODISPLAY = 1<<4, // don't display this leaf itself

	ATUI_NONE     = 1<<5, //TODO depricate
	ATUI_NOFANCY  = 1<<5,
	ATUI_BITFIELD = 1<<6,
	ATUI_BITCHILD = 1<<7,
	ATUI_ENUM     = 1<<8,  // see also PPATUI_FUNCIFY()
	ATUI_STRING   = 1<<9,  // meant for human-readable text
	ATUI_ARRAY    = 1<<10, // no technical difference from string
	ATUI_INLINE   = 1<<11, // pull in leaves from other tables
	ATUI_DYNARRAY = 1<<12, // for runtime array lengths
};

typedef struct _atui_branch atui_branch;
typedef struct _atui_leaf atui_leaf;
struct _atui_leaf {
	char name[40];
	const char* origname;
	const char* varname;

	char* description[LANG_TOTALLANGS];


	enum atui_type type; // bitfield struct
	uint8_t array_size;
	uint8_t total_bits; // number of bits for the leaf

	uint8_t bitfield_hi; //bitfield range end
	uint8_t bitfield_lo; //bitfield range start

	uint8_t num_child_leaves;


	const struct atui_enum* enum_options; // array of text val pair
	uint8_t num_enum_opts;

	atui_branch** inline_branch;

	union {
		void*     val;
		uint8_t*  u8;
		uint16_t* u16;
		uint32_t* u32;
		uint64_t* u64;
	};

	void* auxiliary; // any extra info to hang off if necessary
};
struct  _atui_branch {
	char name[40];
	const char* varname;

	char* description[LANG_TOTALLANGS];

	atui_branch** child_branches;
	uint8_t num_child_branches;
	uint8_t max_num_child_branches;

	atui_branch** inline_branches; // ATUI_INLINE; to present branches as leaves
	uint8_t num_inline_branches;
	uint8_t max_num_inline_branches;

	atui_branch** all_branches;
	uint8_t max_branch_count;


	atui_leaf* leaves;
	uint16_t leaf_count;
	uint16_t max_leaves;

	void* atomleaves;
	void* auxiliary; // alternative representation to leaves, if necessary
};

// reccomended buffer size for the upcomming text functions
#define ATUI_LEAVES_STR_BUFFER 70

//set the value from a string or array of 8-bit
uint8_t atui_set_from_text(atui_leaf* leaf, const char* buffer);
uint8_t atui_get_to_text(atui_leaf*, char** buffer_ptr);


//set or get the number value from the leaf
void atui_leaf_set_val(atui_leaf* leaf, uint64_t val);
uint64_t atui_leaf_get_val(atui_leaf* leaf);




//TODO stroll that considers 0b prefix?
uint64_t strtoll_2(const char* str);

//atui has auxiliary pointers to hang extra data off of and this deallocator
//doesn't consider.
void atui_destroy_tree(atui_branch* tree);



struct atui_funcify_args {
	void* atomtree;
	// Pointer to the relevant atomtree struct. Mainly for the bios pointer,
	// but is necessary if atomtree-computer data needs to be pulled in. Can be
	// optional depending on defined atui branch; use suggestbios instead.

	void* suggestbios;
	// Optional. A pointer to somewhere in the bios memory; mainly useful for
	// looping across an array within an atom struct.

	uint16_t num_child_branches;
	// Number of child branches this atui_branch will have.*/

	atui_branch** import_children;
	// If the child branches are preallocated, walk across this. This array
	// must have num_child_branches elements.
};


// funcify internal structs
struct dynarray_bounds { // for ATUI_DYNARRAY
	void* array_start;
	uint32_t element_size; //for manual pointer math.
	uint16_t dynarray_length; // the number of members to the dynamic array.

	uint16_t numleaves; // number of leaves within the pattern.
	atui_branch* (*inl_func)(struct atui_funcify_args*);
	// function pointer to the _atui function, if the pattern is a ATUI_INLINE
};

struct atui_nullstruct {
	// purely to satisfy the args of PPATUI_FUNCIFY if no atomtree struct is
	// relevant for that branch.
	void* leaves;
};

#include "atui_includes.h"
#endif
