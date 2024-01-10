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

// see bottom for more includes


// for PPATUI_ENUMER() for ATUI_ENUM
struct atui_enum_entry {
	const char8_t* const name;
	const int64_t val;
};
struct atui_enum {
	const char8_t* const name;
	const uint8_t num_entries;
	const struct atui_enum_entry* const enum_array;
};

enum i18n_languages:int8_t {
	LANG_NOLANG = -1,

	LANG_ENGLISH = 0,

	LANG_TOTALLANGS
};

// https://open-std.org/JTC1/SC22/WG14/www/docs/n3042.htm
static const nullptr_t ATUI_NULL = nullptr; // to satisfy _Generics
// purely to satisfy the args of PPATUI_FUNCIFY if no atomtree struct is
// relevant for that branch:
struct atui_nullstruct;

// TODO move to bitfield?
enum atui_type:uint16_t {
	ATUI_NAN  = 0x0, // Don't display a value
	ATUI_DEC  = 0x1,
	ATUI_HEX  = 0x2,
	ATUI_OCT  = 0x3, // TODO not implemented
	ATUI_BIN  = 0x4,
	ATUI_ANY  = 0x7, // Mask

	ATUI_NOFANCY   = 1<<4, // Nothing fancy to the leaf
	ATUI_NODISPLAY = 1<<5, // Don't display this leaf itself
	ATUI_BITFIELD  = 1<<6, // Is a bitfield parent
	ATUI_ENUM      = 1<<7, // See also PPATUI_FUNCIFY()
	ATUI_STRING    = 1<<8, // Meant for human-readable text
	ATUI_ARRAY     = 1<<9, // No technical difference from string
	ATUI_INLINE   = 1<<10, // Pull in leaves from other tables
	ATUI_PETIOLE  = 1<<11, // hard-attach a child branch
	ATUI_DYNARRAY = 1<<12, // For runtime array lengths

	_ATUI_BITCHILD = 1<<13, // Internally set. If it's a bitfield child.
	ATUI_SIGNED    = 1<<14, // Internally-set. If it has a signing bit.
	ATUI_FRAC     = 1<<15, // Internally-set. Both Q and float.
};

struct yaabe_gtkapp_model_cache; // GTK
struct atui_funcify_args; // internal use; see below
typedef struct _atui_branch atui_branch;
typedef struct _atui_leaf atui_leaf;
struct _atui_leaf {
	char8_t name[64];
	const char8_t* origname;
	const char8_t* varname;
	const char8_t* description[LANG_TOTALLANGS];

	uint32_t num_bytes; // number of bytes for quick leaf size
	enum atui_type type; // how to display text, and other config data
	uint8_t array_size;

	uint8_t fractional_bits; // if fixed-point
	uint8_t total_bits;  // number of bits for the leaf
	uint8_t bitfield_hi; // bitfield range end
	uint8_t bitfield_lo; // bitfield range start

	uint8_t num_child_leaves;

	const struct atui_enum* enum_options; // if it has an associated enum

	union {
		atui_branch** inline_branch;
		// allocator-funcify use only:
		atui_branch* (* branch_bud)(const struct atui_funcify_args*);
	};

	union {
		const void* val;

		uint8_t*  u8;
		uint16_t* u16;
		uint32_t* u32;
		uint64_t* u64;

		int8_t*   s8;
		int16_t*  s16;
		int32_t*  s32;
		int64_t*  s64;

		uq6_2_t*     u6_2;
		uq4_4_t*     u4_4;
		uq14_2_t*   u14_2;
		uq8_8_t*     u8_8;
		uq30_2_t*   u30_2;
		uq16_16_t* u16_16;

		float16_t* f16;
		float32_t* f32;
		float64_t* f64;
	};
	union {
		void* auxiliary; // any extra info to hang off if necessary
		struct yaabe_gtkapp_model_cache* gtk_cache;
	};
};
struct  _atui_branch {
	char8_t name[64];
	const char8_t* varname;

	const char8_t* description[LANG_TOTALLANGS];

	atui_branch** child_branches;
	atui_branch** inline_branches; // ATUI_INLINE; to present branches as leaves
	atui_branch** all_branches;

	uint8_t num_branches;
	uint8_t max_num_branches;

	uint8_t num_inline_branches;
	uint8_t max_num_inline_branches;

	uint8_t max_all_branch_count;


	uint16_t leaf_count;
	uint16_t max_leaves;
	atui_leaf* leaves;

	void* atomleaves;
	union {
		void* auxiliary; // alternative representation to leaves, if necessary
		struct yaabe_gtkapp_model_cache* gtk_cache;
	};
};



// reccomended buffer size for the upcomming text functions
#define ATUI_LEAVES_STR_BUFFER 128

// set the value from a string or array of 8-bit
uint8_t
atui_set_from_text(
		atui_leaf* leaf,
		const char8_t* buffer
		);
uint16_t
atui_get_to_text(
		const atui_leaf* leaf,
		char8_t** buffer_ptr
		);
// returns malloc size

// set or get the number value from the leaf
void
atui_leaf_set_val_unsigned(
		atui_leaf* leaf,
		uint64_t val
		);
uint64_t
atui_leaf_get_val_unsigned(
		const atui_leaf* leaf
		);

void
atui_leaf_set_val_signed(
		atui_leaf* leaf,
		int64_t val
		);
int64_t
atui_leaf_get_val_signed(
		const atui_leaf* leaf
		);

void
atui_leaf_set_val_fraction(
		atui_leaf* leaf,
		float64_t val
		);
float64_t
atui_leaf_get_val_fraction(
		const atui_leaf* leaf
		);

// TODO stroll that considers 0b prefix?
int64_t
strtoll_2(
		const char8_t* str
		);
uint64_t
strtoull_2(
		const char8_t* str
		);

int16_t
atui_enum_bsearch(
		int64_t val,
		const struct atui_enum* enum_array
		);

// atui has auxiliary pointers to hang extra data off of and this deallocator
// doesn't consider.
void
atui_destroy_tree(
		atui_branch* tree
		);




// funcify internal structs:

struct atui_funcify_args {
	const char8_t* rename;
	// optionally rename the branch.

	void* atomtree;
	// Pointer to the relevant atomtree struct. Mainly for the bios pointer,
	// but is necessary if atomtree-computer data needs to be pulled in. Can be
	// optional depending on defined atui branch; use suggestbios instead.

	const void* suggestbios;
	// Optional. A pointer to somewhere in the bios memory; mainly useful for
	// looping across an array within an atom struct.

	atui_branch* const* import_branches;
	// If the child branches are preallocated, walk across this. This array
	// must have num_import_branches elements. NULLs allowed.

	uint16_t num_import_branches;
	// Number of imported child branches this atui_branch will have.*/
};

struct dynarray_bounds { // for ATUI_DYNARRAY
	const void* const* const deferred_start_array;
	const uint32_t element_size; // Size of bios element. For pointer math.
	const uint16_t dynarray_length; // The number of elements in the bios array

	const uint16_t numleaves; // number of leaves within the pattern.

	// optional enum for name sprintf'ing
	const struct atui_enum* const enum_taglist;
};

struct atui_branch_data {
	const char8_t* const varname;

	// leaves straightforward:
	const atui_leaf* const leaves_initial;

	// the collection of leaf patterns for all dynarrays in the branch:
	const atui_leaf* const dynarray_patterns;
	// dynarray metadata:
	const struct dynarray_bounds* const dynarray_boundaries;

	const uint8_t num_leaves_initial;
	const uint8_t num_dynarray_sets;

	const uint8_t num_inline_initial;
	const uint8_t num_branches_initial;

};
atui_branch*
atui_branch_allocator(
	const struct atui_branch_data* const embryo,
	const struct atui_funcify_args* const args
	);


#include "ppatui.h"
#include "atui_includes.h"
#include "atui_enums.h"

#endif
