#ifndef ATUI_ALLOCATOR_H
#define ATUI_ALLOCATOR_H

// atui allocator functions internal structs:
static constexpr uint16_t ATUI_STACK_DEPTH = 16;

typedef struct atui_func_args {
	char const* rename;
	// optionally rename the branch.

	void const* atomtree;
	// Pointer to the relevant atomtree struct. Mainly for the bios pointer,
	// but is necessary if atomtree-computer data needs to be pulled in. Can be
	// optional depending on defined atui branch; use bios instead.

	void const* bios;
	// Optional. A pointer to somewhere in the bios memory; mainly useful for
	// looping across an array within an atom struct.

	atui_node* const* import_branches;
	// If the child branches are preallocated, walk across this. This array
	// must have num_import_branches elements. NULLs allowed.

	uint8_t num_import_branches;
	// Number of imported child branches this atui_node will have.*/
} atuifunc_args;

struct subleaf_meta {
	uint32_t element_size;   // Size of bios element. For pointer math.
	uint8_t dynarray_length; // The number of elements in the bios array
	bool deferred_start_array;

	uint8_t numleaves; // number of leaves within the pattern.
	atui_node const* sub_leaves;

	// optional enum for name sprintf'ing
	struct atui_enum const* enum_taglist;
};

struct atui_branch_data {
	atui_node seed;

	uint32_t computed_num_leaves; // the "computed" is the final amount of X
	uint32_t computed_num_graft;
	uint32_t computed_num_shoot;

	uint16_t num_leaves_init;
	atui_node const* leaves_init;
};

atui_node*
atui_branch_allocator(
	struct atui_branch_data const* embryo,
	atuifunc_args const* args
	);

// atui has auxiliary pointers to hang extra data off of and this deallocator
// doesn't consider.
void
atui_destroy_tree(
		atui_node* tree
		);

// Destructively take all leaves and child branches of all source branches.
// Does not modify bios mapping info
void
atui_assimilate(
		atui_node* dest,
		atui_node* const* src_array,
		uint16_t src_array_len
		);

#include "auto_includes.h"

#endif
