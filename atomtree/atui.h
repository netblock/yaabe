/*
AtomTree iterable interface for UIs; chiefly for tree-view/directory interfaces.
ATUI has two main components: branches and leaves. Branches describe the
existence of structs and unions, and leaves describe the accessable elements of
those structs/unions.

Leaves contain extra details about how a paticular element should be
represented; for example what radix it is best viewed in, or has an associated
enum, or is a member of a bitfield. Furthermore, there are meta leaves that
describe or refer to other leaves.

ATUI heavily relies on metaprogramming (currently C preprocessor) to abstract
away the programatic consequences of the underlying allocation and setup.
For how to use ATUI_FUNCIFY() see atui_atomfirmware.c
For how to use ATUI_MAKE_BRANCH() See ppatui.h


declaration: 
PPATUI_FUNCIFY(struct|union, bios_namespace, atomtree_namespace
    ...
)

instantiation:
atui_branch* foba = ATUI_MAKE_BRANCH(name_of_bios_struct,
	atomtree_pointer, bios_pointer,
	number_of_child_branches, child_branches_array
)

atui.h is about the core atui interface
*/

#ifndef ATUI_H
#define ATUI_H

#include "ppatui.h"
// see bottom for more includes


// base struct for PPATUI_ENUMER() for ATUI_ENUM
struct atui_enum {
	const char8_t* name;
	const int64_t val;
};

enum i18n_languages:int8_t {
	LANG_NOLANG = -1,

	LANG_ENGLISH = 0,

	LANG_TOTALLANGS
};

// https://open-std.org/JTC1/SC22/WG14/www/docs/n3042.htm
static nullptr_t ATUI_NULL; // to satisfy _Generics and address-of'`s

// TODO move to bitfield?
enum atui_type:uint32_t {
	ATUI_NAN  = 0x0, // Don't display a value
	ATUI_DEC  = 0x1,
	ATUI_HEX  = 0x2,
	ATUI_OCT  = 0x3, // TODO not implemented
	ATUI_BIN  = 0x4,
	ATUI_FRAC = 0x5, // Both Q and float. TODO support Q notation.
	ATUI_ANY  = 0xF, // Mask

	ATUI_NOFANCY   = 1<<5, // Nothing fancy to the leaf
	ATUI_NODISPLAY = 1<<6, // Don't display this leaf itself
	ATUI_BITFIELD  = 1<<7, // Is a bitfield parent
	ATUI_ENUM      = 1<<8, // See also PPATUI_FUNCIFY()
	ATUI_STRING    = 1<<9, // Meant for human-readable text
	ATUI_ARRAY    = 1<<10, // No technical difference from string
	ATUI_INLINE   = 1<<11, // Pull in leaves from other tables
	ATUI_DYNARRAY = 1<<12, // For runtime array lengths

	_ATUI_BITCHILD = 1<<16, // Internally set. Is a bitfield child.
	ATUI_SIGNED   = 1<<17, // Internally-set. Signifies if it has a signing bit

	// TODO unrolled array for static arrays?
	// follow dynarray, but instead of count, it's a preprocessor array with 
	// enums that get valued and texted. possible pairs?
	// start, ((val, name), (val, name))
	// alternatively, use DYNARRAY, and compile the atui_*.c with
	// and play with loop optimiser flags, like -funroll-loops

	// TODO allow DYNARRAY to pull text from an ATUI enum?

	// TODO ATUI_BRANCH for automatic branch pull-in?
};

typedef struct _atui_branch atui_branch;
typedef struct _atui_leaf atui_leaf;
struct _atui_leaf {
	char8_t name[40];
	const char8_t* origname;
	const char8_t* varname;

	char8_t* description[LANG_TOTALLANGS];


	enum atui_type type; // how to display text, and other config data
	uint8_t array_size;
	uint8_t total_bits;  // number of bits for the leaf

	uint8_t bitfield_hi; // bitfield range end
	uint8_t bitfield_lo; // bitfield range start

	uint8_t num_child_leaves;


	uint8_t num_enum_opts;
	const struct atui_enum* enum_options; // array of text val pair

	atui_branch** inline_branch;

	union {
		void*     val;
		uint8_t*  u8;
		uint16_t* u16;
		uint32_t* u32;
		uint64_t* u64;
		int8_t*   s8;
		int16_t*  s16;
		int32_t*  s32;
		int64_t*  s64;
		_Float16* f16;
		float*    f32;
		double*   f64;
	};

	void* auxiliary; // any extra info to hang off if necessary
};
struct  _atui_branch {
	char8_t name[40];
	const char8_t* varname;

	char8_t* description[LANG_TOTALLANGS];

	atui_branch** child_branches;
	atui_branch** inline_branches; // ATUI_INLINE; to present branches as leaves
	atui_branch** all_branches;

	uint8_t num_child_branches;
	uint8_t max_num_child_branches;

	uint8_t num_inline_branches;
	uint8_t max_num_inline_branches;

	uint8_t max_branch_count;


	uint16_t leaf_count;
	uint16_t max_leaves;
	atui_leaf* leaves;

	void* atomleaves;
	void* auxiliary; // alternative representation to leaves, if necessary
};



// reccomended buffer size for the upcomming text functions
#define ATUI_LEAVES_STR_BUFFER 70



// set the value from a string or array of 8-bit
uint8_t atui_set_from_text(atui_leaf* leaf, const char8_t* buffer);
uint16_t atui_get_to_text(atui_leaf*, char8_t** buffer_ptr);
// returns malloc size

// set or get the number value from the leaf
void atui_leaf_set_val_unsigned(atui_leaf* leaf, uint64_t val);
uint64_t atui_leaf_get_val_unsigned(atui_leaf* leaf);
void atui_leaf_set_val_signed(atui_leaf* leaf, int64_t val);
int64_t atui_leaf_get_val_signed(atui_leaf* leaf);
void atui_leaf_set_val_fraction(atui_leaf* leaf, double val);
double atui_leaf_get_val_fraction(atui_leaf* leaf);

// TODO stroll that considers 0b prefix?
int64_t strtoll_2(const char8_t* str);
uint64_t strtoull_2(const char8_t* str);

// atui has auxiliary pointers to hang extra data off of and this deallocator
// doesn't consider.
void atui_destroy_tree(atui_branch* tree);



struct atui_funcify_args {
	void* atomtree;
	// Pointer to the relevant atomtree struct. Mainly for the bios pointer,
	// but is necessary if atomtree-computer data needs to be pulled in. Can be
	// optional depending on defined atui branch; use suggestbios instead.

	void* suggestbios;
	// Optional. A pointer to somewhere in the bios memory; mainly useful for
	// looping across an array within an atom struct.

	atui_branch** import_children;
	// If the child branches are preallocated, walk across this. This array
	// must have num_child_branches elements.

	uint16_t num_child_branches;
	// Number of child branches this atui_branch will have.*/

};


// funcify internal structs
struct dynarray_bounds { // for ATUI_DYNARRAY
	void* array_start;
	uint32_t element_size; // for manual pointer math.
	uint16_t dynarray_length; // the number of members to the dynamic array.

	uint16_t numleaves; // number of leaves within the pattern.
	atui_branch* (*inl_func)(struct atui_funcify_args*);
	// function pointer to the _atui function, if the pattern is a ATUI_INLINE
};

struct atui_nullstruct;
// purely to satisfy the args of PPATUI_FUNCIFY if no atomtree struct is
// relevant for that branch.


#include "atui_includes.h"
#include "atui_enums.h"

#endif
