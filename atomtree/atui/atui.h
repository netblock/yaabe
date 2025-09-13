/*
AtomTree iterable interface for UIs; chiefly for tree-view/directory interfaces.
ATUI has two main components: branches and leaves. Branches describe the
existence of structs and unions, and leaves describe the accessible elements of
those structs/unions.

Leaves contain extra details about how a paticular element should be
represented; for example what radix it is best viewed in, or has an associated
enum, or is a member of a bitfield. Furthermore, there are meta leaves that
describe or refer to other leaves.

ATUI heavily relies on metaprogramming to abstract away the programatic
consequences of the underlying allocation and setup. For how to write the tables
see atui_documentation.md

instantiation:
atui_node* foba = ATUI_MAKE_BRANCH(name_of_bios_struct,
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

enum i18n_languages:int8_t {
	LANG_ENGLISH = 0,

	LANG_TOTALLANGS,
	LANG_NOLANG = -1,
};

struct atui_enum_entry {
	char const name[64];
	char const* const description[LANG_TOTALLANGS];
	int64_t const val;
	uint16_t const name_length;
};
struct atui_enum {
	char const name[40];
	char const* const description[LANG_TOTALLANGS];
	struct atui_enum_entry const* const enum_array;
	uint8_t const num_entries;
	uint16_t const name_length;
};

enum atui_leaf_type_fancy:uint8_t { // ppatui.py has a copy
	ATUI_NOFANCY  = 0, // Nothing fancy to the leaf
	ATUI_BITFIELD = 1, // Is a bitfield parent
	ATUI_STRING   = 2, // Variable-length srings ending in \0
	ATUI_ARRAY    = 3, // staticall-sized array and strings
	ATUI_GRAFT    = 4, // Pull in leaves from other tables
	ATUI_SHOOT    = 5, // hard-attach a child branch
	ATUI_PETIOLE  = 6, // ejects off given leaves into a branch
	ATUI_DYNARRAY = 7, // For runtime array lengths
	_ATUI_BITCHILD = 8, // Internally set. If it's a bitfield child.

	ATUI_NUM_FANCY
};
enum atui_leaf_type_radix:uint8_t {
	ATUI_NAN = 0x0, // Not a number
	ATUI_DEC = 0x1,
	ATUI_HEX = 0x2,
	ATUI_OCT = 0x3,
	ATUI_BIN = 0x4,

	ATUI_NUM_RADIX,
	ATUI_ANY = 0x7, // Mask
};
enum atui_leaf_type_disable:uint8_t {
	ATUI_DISPLAY   = 0, // show everything
	ATUI_SUBONLY   = 1, // show only the children
	ATUI_NODISPLAY = 2, // Don't display this leaf or its children

	ATUI_NUM_DISPLAY
};
struct atui_leaf_type {
	enum atui_leaf_type_fancy   fancy;
	enum atui_leaf_type_radix   radix;
	enum atui_leaf_type_disable disable; // enum atui_leaf_type_disable
	bool signed_num; // Usually internally-set.
	bool fraction;   // Internally-set. Both Q and float.
	bool has_enum;   // has a struct atui_enum
};
union bios_data {
	void const* input; // setter-use only.
	void* data;
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
struct atui_children {
	/*
	Two ways to allocate a node: alone, or an in array. For memory management
	purposes (freeing), a node allocated in an array cannot be added through its
	address, and must be attached through its array.
	Generally speakingonly 'leaves' are allocated to be in an array; branches
	are individual.
	*/
	union {
		atui_node* nodes;
		atui_node** addresses;
		atui_node const* nodes_ro; // read-only
		atui_node const* const* addresses_ro; // read-only
		void* array; // indiscriminate
		void const* array_ro;
	};
	uint16_t count;
	uint16_t max_count;
	bool indirect; // indirect means to use addresses; the nodes are floating.
	bool expanded;
};

union atui_vestige { // atui_branch_allocator() use only
	atuifunc branch_bud;
	struct atui_subleaf_meta const* leaves_meta;
	struct atui_branch_meta const* branch_meta;
};
struct atui_leaf {
	struct atui_leaf_type type; // directives on how to display text

	uint32_t array_size;
	uint8_t fractional_bits; // if fixed-point
	int8_t total_bits;   // number of bits for the leaf
	uint8_t bitfield_hi; // bitfield range end
	uint8_t bitfield_lo; // bitfield range start

	struct atui_enum const* enum_options; // if it has an associated enum
};

struct atui_branch {
	struct atui_children branches; // considers shoot + import
};

struct _atui_node {
	char name[80];
	char const* origname;
	char const* structname;
	char const* description[LANG_TOTALLANGS];

	GATUINode* self; // weak reference
	atui_node* parent; // don't need parent_is_leaf

	struct atui_children leaves; // if branch, always expanded

	/*
	The C struct that the node may represent may be sizeof()'d larger than an
	explicit size declared in the bios, possibly due to padding or flex arrays.
	(eg sizeof() > struct atom_common_table_header.structuresize)
	If this is the case, a simple copy/paste of the leaves themselves might be
	out-of-bounds.
	Subleaves of leaves are guaranteed to be contiguous.
	*/
	uint16_t num_copyable_leaves; // num_leaves that maps the bios
	bool prefer_contiguous;

	// If true, this node is not alone but in an array. See struct atui_children
	// for more info.
	bool bundled;

	bool is_leaf;
	union {
		struct atui_leaf leaf;
		struct atui_branch branch;
	};
	// if the node represents a struct, the num_bytes may be following
	// programmed bios metadata
	union bios_data data;
	size_t num_bytes;

	union atui_vestige vestige;
};

atui_node*
generate_atui(
		struct atom_tree const* atree
		);

char*
atui_node_to_path( // get a full /directory/like/path/of/the/branches/and/leaf
		atui_node const* tip
		);

void
atui_leaf_from_text( // set the value from a string or array of 8-bit
		atui_node const* leaf,
		char const* buffer
		);
char* // returns an alloc
atui_leaf_to_text(
		atui_node const* leaf
		);

// set or get the number value from the leaf
void
atui_leaf_set_val_unsigned(
		atui_node const* leaf,
		uint64_t val
		);
uint64_t
atui_leaf_get_val_unsigned(
		atui_node const* leaf
		);

void
atui_leaf_set_val_signed(
		atui_node const* leaf,
		int64_t val
		);
int64_t
atui_leaf_get_val_signed(
		atui_node const* leaf
		);

void
atui_leaf_set_val_fraction(
		atui_node const* leaf,
		float64_t val
		);
float64_t
atui_leaf_get_val_fraction(
		atui_node const* leaf
		);


struct atui_path_vector {
	atui_node* node;
	uint8_t depth;
};
struct atui_path_goto { // final branch and leaf
	char* not_found; // non-NULL if error; name of the not-found branch/leaf
	struct atui_path_vector leaf;
	struct atui_path_vector branch;
};
struct atui_path_goto* // needs to be freed
path_to_atui( // crawls path and makes a map of that path
		atui_node const* root,
		char const* path
		);


static constexpr uint16_t LEAF_SPRINTF_FORMAT_SIZE = 10;
size_t // num bytes
get_sprintf_format_from_leaf(
		char* format,
		atui_node const* leaf
		);

char* // needs to be freed
atui_enum_entry_to_text( // "enum_entry_name : val"
		atui_node const* leaf,
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
#endif
