/*
AtomTree iterable interface for UIs; chiefly for tree-view/directory interfaces.
ATUI has two main components: branches and leaves. Branches describe the
existence of structs and unions, and leaves describe the accessable elements of
those structs/unions.

Leaves contain extra details about how a paticular element should be
represented; for example what radix it is best viewed in, or has an associated
enum, or is a member of a bitfield. Furthermore, there are meta leaves that
describe or refer to other leaves.

ATUI heavily relies on metaprogramming to abstract away the programatic
consequences of the underlying allocation and setup. For how to write the tables
see atui_documentation.md

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
#include "atui_types.h"
// see bottom for more includes

// https://open-std.org/JTC1/SC22/WG14/www/docs/n3042.htm
static constexpr nullptr_t ATUI_NULL = nullptr; // to satisfy _Generics

enum i18n_languages:int8_t {
	LANG_NOLANG = -1,

	LANG_ENGLISH = 0,

	LANG_TOTALLANGS
};

struct atui_enum_entry {
	char const* const name;
	char const* const description[LANG_TOTALLANGS];
	int64_t const val;
	uint16_t const name_length;
};
struct atui_enum {
	char const* const name;
	char const* const description[LANG_TOTALLANGS];
	struct atui_enum_entry const* const enum_array;
	uint8_t const num_entries;
	uint16_t const name_length;
};

union atui_type {
	struct { uint16_t
		radix      :2-0 +1, // enum atui_type_radix
		signed_num :3-3 +1, // Usually internally-set. If it has a signing bit.
		fraction   :4-4 +1, // Internally-set. Both Q and float.
		fancy      :8-5 +1, // enum atui_type_fancy
		disable   :10-9 +1, // enum atui_type_disable
		reserved  :15-11 +1;
	};
	uint16_t type;
};
enum atui_type_radix:uint8_t {
	ATUI_NAN = 0x0, // Not a number
	ATUI_DEC = 0x1,
	ATUI_HEX = 0x2,
	ATUI_OCT = 0x3,
	ATUI_BIN = 0x4,

	ATUI_NUM_RADIX,
	ATUI_ANY = 0x7, // Mask
};
enum atui_type_fancy:uint8_t { // ppatui.py has a copy
	ATUI_NOFANCY  = 0, // Nothing fancy to the leaf
	ATUI_BITFIELD = 1, // Is a bitfield parent
	ATUI_ENUM     = 2, // has a struct atui_enum over a C enum
	ATUI_STRING   = 3, // Variable-length srings ending in \0
	ATUI_ARRAY    = 4, // staticall-sized array and strings
	ATUI_GRAFT    = 5, // Pull in leaves from other tables
	ATUI_SHOOT    = 6, // hard-attach a child branch
	ATUI_DYNARRAY = 7, // For runtime array lengths

	_ATUI_BITCHILD = 8, // Internally set. If it's a bitfield child.

	ATUI_NUM_FANCY
};
enum atui_type_disable:uint8_t {
	ATUI_DISPLAY   = 0, // show everything
	ATUI_SUBONLY   = 1, // show only the children
	ATUI_NODISPLAY = 2, // Don't display this leaf or its children

	ATUI_NUM_DISPLAY
};

struct _atui_leaf {
	char name[72];
	char const* origname;
	char const* description[LANG_TOTALLANGS];

	size_t num_bytes;  // number of bytes for quick leaf size
	size_t array_size;
	union atui_type type; // how to display text, and other config data

	uint8_t fractional_bits; // if fixed-point
	int8_t total_bits;   // number of bits for the leaf
	uint8_t bitfield_hi; // bitfield range end
	uint8_t bitfield_lo; // bitfield range start

	bool parent_is_leaf;
	uint16_t num_child_leaves;

	struct atui_enum const* enum_options; // if it has an associated enum

	union {
		void const* val;
		char* c8;

		uint8_t*  u8;
		uint16_t* u16;
		uint32_t* u32;
		uint64_t* u64;

		int8_t*   s8;
		int16_t*  s16;
		int32_t*  s32;
		int64_t*  s64;

		uint24_t* u24;
		uint48_t* u48;
		int24_t*  s24;
		int48_t*  s48;

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

	atui_leaf* child_leaves;
	union {
		void* parent;
		atui_leaf* parent_leaf;
		atui_branch* parent_branch;
	};
	GATUILeaf* self; // weak reference

	// atui_branch_allocator() use only:
	union {
		atuifunc branch_bud;
		struct subleaf_meta const* template_leaves;
	};
};
struct _atui_branch {
	char name[64];
	// name and struct ("bios" namespace) may be different
	char const* origname;
	char const* structname;

	char const* description[LANG_TOTALLANGS];

	atui_branch* parent_branch;
	atui_branch** child_branches; // shoot + import
	atui_leaf* leaves;

	GATUIBranch* self; // weak reference

	uint16_t num_branches;     // child branches
	uint16_t max_num_branches; // import alloc'd but may not use

	uint16_t leaf_count;

	uint16_t num_copyable_leaves; // num_leaves that maps the bios

	// the C struct that the branch&leaves represent may be larger than
	// table_size; if this is the case, a simple copy/paste of the leaves
	// themselves might be atom out-of-bounds.
	bool prefer_contiguous;
	void* table_start; // position and size of the struct the branch represents
	size_t table_size;
	// table_size may follow atom metadata, like
	// atom_common_table_header.structuresize
};

void
generate_atui(
		struct atom_tree* atree
		);


void
atui_leaf_from_text( // set the value from a string or array of 8-bit
		atui_leaf const* leaf,
		char const* buffer
		);
char* // returns an alloc
atui_leaf_to_text(
		atui_leaf const* leaf
		);

// set or get the number value from the leaf
void
atui_leaf_set_val_unsigned(
		atui_leaf const* leaf,
		uint64_t val
		);
uint64_t
atui_leaf_get_val_unsigned(
		atui_leaf const* leaf
		);

void
atui_leaf_set_val_signed(
		atui_leaf const* leaf,
		int64_t val
		);
int64_t
atui_leaf_get_val_signed(
		atui_leaf const* leaf
		);

void
atui_leaf_set_val_fraction(
		atui_leaf const* leaf,
		float64_t val
		);
float64_t
atui_leaf_get_val_fraction(
		atui_leaf const* leaf
		);


char* // needs to be freed
atui_branch_to_path( // get a full /directory/like/path/of/the/branches/
		atui_branch const* tip
		);
char* // needs to be freed
atui_leaf_to_path( // get a full /directory/like/path/of/the/branches/and/leaf
		atui_leaf const* tip
		);

struct atui_path_map { // the trail of objects for a map
	char* not_found; // non-NULL if error; name of the not-found branch/leaf
	atui_branch** branch_path;
	atui_leaf** leaf_path;
	uint8_t branch_depth;
	uint8_t leaf_depth;
};
struct atui_path_map* // needs to be freed
path_to_atui( // crawls path and makes a map of that path
		char const* path,
		atui_branch const* root
		);


#define LEAF_SPRINTF_FORMAT_SIZE 10
size_t // num bytes
get_sprintf_format_from_leaf(
		char* format,
		atui_leaf const* leaf
		);

char* // needs to be freed
atui_enum_entry_to_text( // "enum_entry_name : val"
		atui_leaf const* leaf,
		struct atui_enum_entry const* enum_entry
		);

int16_t
atui_enum_bsearch( // binary; left
		struct atui_enum const* enum_array,
		int64_t val
		);
int16_t
atui_enum_lsearch( // linear; left
		struct atui_enum const* enum_array,
		int64_t val
		);

// atui has auxiliary pointers to hang extra data off of and this deallocator
// doesn't consider.
void
atui_destroy_tree(
		atui_branch* tree
		);

// Destructively take all leaves and child branches of all source branches.
// Does not modify bios mapping info
void
atui_assimilate(
		atui_branch* dest,
		atui_branch* const* src_array,
		uint16_t src_array_len
		);


// atui allocator functions internal structs:
typedef struct atui_func_args {
	char const* rename;
	// optionally rename the branch.

	void* atomtree;
	// Pointer to the relevant atomtree struct. Mainly for the bios pointer,
	// but is necessary if atomtree-computer data needs to be pulled in. Can be
	// optional depending on defined atui branch; use suggestbios instead.

	void const* suggestbios;
	// Optional. A pointer to somewhere in the bios memory; mainly useful for
	// looping across an array within an atom struct.

	atui_branch* const* import_branches;
	// If the child branches are preallocated, walk across this. This array
	// must have num_import_branches elements. NULLs allowed.

	uint8_t num_import_branches;
	// Number of imported child branches this atui_branch will have.*/
} atuifunc_args;

struct subleaf_meta {
	uint32_t const element_size;   // Size of bios element. For pointer math.
	uint8_t const dynarray_length; // The number of elements in the bios array
	bool const deferred_start_array;

	uint8_t const numleaves; // number of leaves within the pattern.
	atui_leaf const* sub_leaves;

	// optional enum for name sprintf'ing
	struct atui_enum const* const enum_taglist;
};

struct atui_branch_data {
	char const* const origname;
	char const* const structname;
	char const* const description[LANG_TOTALLANGS];

	// position and size of the struct the branch represents
	void* const table_start;
	size_t const table_size;
	size_t const sizeofbios;

	// leaves straightforward:
	atui_leaf const* const leaves_init;

	uint32_t const num_leaves_init; // sizeof(); does not include kids
	uint32_t const computed_num_leaves;
	uint32_t const computed_num_graft;
	uint32_t const computed_num_shoot;
};

atui_branch*
atui_branch_allocator(
	struct atui_branch_data const* embryo,
	atuifunc_args const* args
	);

#include "auto_includes.h"

#endif
