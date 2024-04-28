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

// see bottom for more includes

// GTK4 stuff; header simplification because we're dealing with only pointers.
typedef struct _GObject GObject;
typedef struct _GtkSelectionModel GtkSelectionModel;

// https://open-std.org/JTC1/SC22/WG14/www/docs/n3042.htm
static const nullptr_t ATUI_NULL = nullptr; // to satisfy _Generics
// purely to satisfy the args of PPATUI_FUNCIFY if no atomtree struct is
// relevant for that branch:
struct atui_nullstruct;

struct atui_funcify_args; // internal use; see below


enum i18n_languages:int8_t {
	LANG_NOLANG = -1,

	LANG_ENGLISH = 0,

	LANG_TOTALLANGS
};

struct atui_enum_entry {
	char8_t const* const name;
	char8_t const* const description[LANG_TOTALLANGS];
	int64_t const val;
	uint16_t const name_length;
};
struct atui_enum {
	char8_t const* const name;
	char8_t const* const description[LANG_TOTALLANGS];
	struct atui_enum_entry const* const enum_array;
	uint8_t const num_entries;
	uint16_t const name_length;
};


// TODO move to bitfield?
enum atui_type:uint32_t {
	ATUI_NAN  = 0x0, // Don't display a value
	ATUI_DEC  = 0x1,
	ATUI_HEX  = 0x2,
	ATUI_OCT  = 0x3, // TODO not implemented
	ATUI_BIN  = 0x4,
	ATUI_ANY  = 0x7, // Mask

	ATUI_SUBONLY   = 1<<4, // show only the children
	ATUI_NODISPLAY = 1<<5, // Don't display this leaf itself

	ATUI_NOFANCY   = 1<<8, // Nothing fancy to the leaf
	ATUI_BITFIELD  = 1<<9, // Is a bitfield parent
	ATUI_ENUM     = 1<<10, // See also PPATUI_FUNCIFY()
	ATUI_STRING   = 1<<11, // Meant for human-readable text
	ATUI_ARRAY    = 1<<12, // No technical difference from string
	ATUI_INLINE   = 1<<13, // Pull in leaves from other tables
	ATUI_PETIOLE  = 1<<14, // hard-attach a child branch
	ATUI_DYNARRAY = 1<<15, // For runtime array lengths


	_ATUI_BITCHILD = 1<<17, // Internally set. If it's a bitfield child.
	ATUI_SIGNED    = 1<<18, // Internally-set. If it has a signing bit.
	ATUI_FRAC      = 1<<19, // Internally-set. Both Q and float.
};
typedef struct _atui_branch atui_branch;
typedef struct _atui_leaf atui_leaf;
struct _atui_leaf {
	char8_t name[72];
	char8_t const* origname;
	char8_t const* description[LANG_TOTALLANGS];

	uint32_t num_bytes;  // number of bytes for quick leaf size
	enum atui_type type; // how to display text, and other config data
	uint8_t array_size;

	uint8_t fractional_bits; // if fixed-point
	uint8_t total_bits;  // number of bits for the leaf
	uint8_t bitfield_hi; // bitfield range end
	uint8_t bitfield_lo; // bitfield range start

	uint16_t num_child_leaves;

	int16_t num_gobj; // for child_gobj_cache

	struct atui_enum const* enum_options; // if it has an associated enum
	GtkSelectionModel* enum_model; // composited enum cache for GTK

	union {
		atui_branch** inline_branch;
		atui_leaf* child_leaves;

		// allocator-funcify use only:
		atui_branch* (* branch_bud)(struct atui_funcify_args const*);
		struct subleaf_meta const* template_leaves;
	};

	union {
		void const* val;

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

	bool parent_is_leaf;
	union {
		void* parent;
		atui_leaf* parent_leaf;
		atui_branch* parent_branch;
	};

	GObject** child_gobj_cache; // GObject cache of child leaves for GTK
	GObject* self_gobj;
};
struct _atui_branch {
	char8_t name[64];
	char8_t const* origname;

	char8_t const* description[LANG_TOTALLANGS];

	atui_branch** child_branches;  // petiole + import
	atui_branch** inline_branches; // ATUI_INLINE; to present branches as leaves
	atui_branch** all_branches;    // child + inline

	uint8_t num_branches;     // child branches
	uint8_t max_num_branches; // import alloc'd but may not use
	uint8_t num_inline_branches;
	uint8_t max_all_branch_count; // child+inline, import alloc'd may not use


	uint16_t leaf_count;
	uint16_t max_leaves;
	atui_leaf* leaves;

	union {
		void* parent;
		atui_leaf* parent_leaf;
		atui_branch* parent_branch;
	};
	bool parent_is_leaf;

	int16_t num_gobj;
	GObject** child_gobj_cache; // GObject cache of child branches for GTK
	GtkSelectionModel* leaves_model; // composited leaves cache for GTK
	GObject* self_gobj;
};



// reccomended buffer size for the upcomming text functions
#define ATUI_LEAVES_STR_BUFFER 128

void
atui_leaf_from_text( // set the value from a string or array of 8-bit
		atui_leaf* leaf,
		char8_t const* buffer
		);
uint16_t // returns malloc size
atui_leaf_to_text(
		atui_leaf const* leaf,
		char8_t** buffer_ptr
		);

// set or get the number value from the leaf
void
atui_leaf_set_val_unsigned(
		atui_leaf* leaf,
		uint64_t val
		);
uint64_t
atui_leaf_get_val_unsigned(
		atui_leaf const* leaf
		);

void
atui_leaf_set_val_signed(
		atui_leaf* leaf,
		int64_t val
		);
int64_t
atui_leaf_get_val_signed(
		atui_leaf const* leaf
		);

void
atui_leaf_set_val_fraction(
		atui_leaf* leaf,
		float64_t val
		);
float64_t
atui_leaf_get_val_fraction(
		atui_leaf const* leaf
		);


char8_t*
atui_branch_to_path( // get a full /directory/like/path/of/the/branches/
		atui_branch const* tip,
		char8_t* buffer
		);
char8_t*
atui_leaf_to_path( // get a full /directory/like/path/of/the/branches/and/leaf
		atui_leaf const* tip,
		char8_t* buffer
		);

struct atui_path_map { // the trail of objects for a map
	char8_t* not_found; // non-NULL if error; name of the not-found branch/leaf
	atui_branch** branch_path;
	atui_leaf** leaf_path;
	uint8_t branch_depth;
	uint8_t leaf_depth;
};
struct atui_path_map* // needs to be freed
path_to_atui( // crawls path and makes a map of that path
		char8_t const* path,
		atui_branch const* root
		);

void
atui_enum_entry_to_text(
		char8_t* buffer,
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
void
_atui_destroy_leaves( 
		atui_leaf* leaves,
		uint16_t num_leaves
		);


// funcify internal structs:

struct atui_funcify_args {
	char8_t const* rename;
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
};

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
	char8_t const* const origname;
	char8_t const* const description[LANG_TOTALLANGS];

	// leaves straightforward:
	atui_leaf const* const leaves_init;

	uint32_t const num_leaves_init; // sizeof(); does not include kids
	uint32_t const computed_num_leaves;
	uint32_t const computed_num_inline;
	uint32_t const computed_num_petiole;
};

atui_branch*
atui_branch_allocator(
	struct atui_branch_data const* const embryo,
	struct atui_funcify_args const* const args
	);


#include "ppatui.h"
#include "atui_includes.h"

#endif
