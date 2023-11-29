#include "atomtree.h"
#include "atui.h"

/* AtomTree iterable interface for UIs

atui_branch_allocator processes the data set up by the ATUI_FUNCIFY functions
to spit out your branch

*/
atui_branch* atui_branch_allocator(
		const struct atui_branch_data* const embryo,
		const struct atui_funcify_args* const args) {

	const atui_leaf* const leaves_initial = embryo->leaves_initial;
	const atui_leaf* const dynarray_patterns = embryo->dynarray_patterns;
	const struct dynarray_bounds* const dynarray_boundaries =\
		embryo->dynarray_boundaries;
	const uint8_t num_branches_initial = embryo->num_branches_initial;
	const uint8_t num_leaves_initial = embryo->num_leaves_initial;
	const uint8_t num_inline_initial = embryo->num_inline_initial;
	const uint8_t num_dynarray_sets = embryo->num_dynarray_sets;

	const uint16_t num_import_branches = args->num_import_branches;
	atui_branch* const* const import_branches = args->import_branches;

	void* mallocvoid = NULL; // temporary malloc partitioning pointer
	atui_branch* table = NULL;


	// child branches:
	atui_branch** branches = NULL;
	uint16_t branches_i = 0;
	uint16_t num_branches = 0; // num used
	uint16_t max_num_branches = 0; // num alloc'd

	// import allocates but doesn't necessarily populate
	uint16_t importbranches_i = 0;

	// inliners:
	uint16_t inliners_i = 0;
	atui_branch** inliners = NULL;
	uint16_t num_inliners = 0;

	// child branches + inliners.
	// alloc them adjacently for easy single-loop free().
	uint16_t max_all_branch_count = 0;
	atui_branch** all_branches = NULL;

	// arguments for inliners and petiole branches
	struct atui_funcify_args branch_funcify_args = {
		//.rename=NULL,
		.atomtree=args->atomtree, .suggestbios=NULL,
		.import_branches=NULL, .num_import_branches=0,
	};
	// leaves
	uint16_t leavesinit_i = 0;
	uint16_t leaves_i = 0;
	atui_leaf* leaves = NULL;
	uint16_t num_leaves = 0;

	max_num_branches = num_branches_initial + num_import_branches;
	uint16_t dynarray_total_branches = 0;

	if (num_leaves_initial) {
		uint16_t leafpattern_i = 0;
		uint16_t dynentry_i = 0;
		uint16_t dynarray_total_leaves = 0;
		uint16_t dynarray_total_inline = 0;
		uint16_t petiole_only_dynarrays = 0;
		for (; dynentry_i < num_dynarray_sets; dynentry_i++) {
			// except for bitfield, we assume there's gonna be exactly one
			// pattern leaf.
			if (dynarray_patterns[leafpattern_i].type & ATUI_PETIOLE) {
				dynarray_total_branches +=
					dynarray_boundaries[dynentry_i].dynarray_length;
				petiole_only_dynarrays++;
			} else if (dynarray_patterns[leafpattern_i].type & ATUI_INLINE) {
				dynarray_total_inline +=
					dynarray_boundaries[dynentry_i].dynarray_length;
			}
			dynarray_total_leaves += (
				dynarray_boundaries[dynentry_i].dynarray_length
				* dynarray_boundaries[dynentry_i].numleaves
			);

			leafpattern_i += dynarray_boundaries[dynentry_i].numleaves;
		}

		max_num_branches += dynarray_total_branches;
		num_inliners = num_inline_initial + dynarray_total_inline;
		max_all_branch_count = max_num_branches + num_inliners;
		num_leaves = (
			embryo->num_leaves_initial
			+ dynarray_total_leaves
			- num_branches_initial // ATUI_PETIOLE
			- dynarray_total_branches // ATUI_PETIOLE in ATUI_DYNARRAY
			- petiole_only_dynarrays
			// future multi-leaf dynarray support:
			// dyn petiole could be partially pp'd: count how many petiole in
			// pattern
		);
		// calloc hands over 0'd memory
		mallocvoid = calloc(1,
			sizeof(atui_branch)
			+ (max_all_branch_count * sizeof(atui_branch*))
			+ (num_leaves * sizeof(atui_leaf))
		);
		/* topology:
		main table
		all branches:
			child
			inline
		leaves
		*/
		table = mallocvoid;
		mallocvoid += sizeof(atui_branch);
		if (max_all_branch_count) {
			all_branches = mallocvoid;
			if (max_num_branches) {
				branches = mallocvoid;
				mallocvoid += (max_num_branches * sizeof(atui_branch*));
			}
			if (num_inliners) {
				inliners = mallocvoid;
				mallocvoid += (num_inliners * sizeof(atui_branch*));
			}
		}
		leaves = mallocvoid;
		mallocvoid = NULL; // we are done partitioning


		if (num_dynarray_sets) {
			// If there's more than one ATUI_DYNARRAY in this branch:
			dynentry_i = 0;

			// Array in the bios:
			const void* dynarray_start_ptr = NULL;
			uint16_t dynarray_biosarray_i = 0;
			uint32_t dynarray_elementsize = 0;
			uint16_t dynarray_length = 0;
			// for multi-leaf playback
			const void* dynarray_bios_pos = NULL;

			// Leaf playback for each element in the bios array:
			leafpattern_i = 0;
			uint16_t leafpattern_numleaves = 0;
			uint16_t leafpattern_start = 0;
			uint16_t leafpattern_end = 0;
			const struct atui_enum* dynarray_enum_taglist = NULL;

			leavesinit_i = 0;
			while (leavesinit_i < num_leaves_initial) {
				if (leaves_initial[leavesinit_i].type & ATUI_DYNARRAY) {
					dynarray_start_ptr =
						dynarray_boundaries[dynentry_i].array_start;
					dynarray_elementsize =
						dynarray_boundaries[dynentry_i].element_size;
					dynarray_length =
						dynarray_boundaries[dynentry_i].dynarray_length;
					leafpattern_numleaves =
						dynarray_boundaries[dynentry_i].numleaves;
					dynarray_enum_taglist =
						dynarray_boundaries[dynentry_i].enum_taglist;

					if (!((dynarray_patterns[leafpattern_i].type & ATUI_PETIOLE)
						&& (dynarray_boundaries[dynentry_i].numleaves == 1))) {
						leaves[leaves_i] = leaves_initial[leavesinit_i];
						leaves[leaves_i].val = dynarray_start_ptr;
						leaves[leaves_i].num_bytes = (
							dynarray_length * dynarray_elementsize
						);
						leaves[leaves_i].num_child_leaves = (
							dynarray_length * leafpattern_numleaves
						);
						leaves_i++; // we've child leaves to print
					}
					
					leafpattern_end = leafpattern_start + leafpattern_numleaves;

					// for each element in the bios array
					dynarray_biosarray_i = 0;
					while (dynarray_biosarray_i < dynarray_length) {
						dynarray_bios_pos = (
							dynarray_start_ptr
							+ (dynarray_biosarray_i * dynarray_elementsize)
						);

						// for each each leaf in the leaf pattern set
						leafpattern_i = leafpattern_start;
						while (leafpattern_i < leafpattern_end) {
							if (dynarray_patterns[leafpattern_i].type
									& ATUI_PETIOLE) {
								branch_funcify_args.suggestbios =\
									dynarray_bios_pos;
								// TODO have suggestname
								branches[branches_i] =\
									dynarray_patterns[leafpattern_i].branch_bud(
										&branch_funcify_args
									);
								branches_i++;
								leafpattern_i++;
								continue;
							}
							leaves[leaves_i] = dynarray_patterns[leafpattern_i];
							leaves[leaves_i].val = dynarray_bios_pos;

							if (dynarray_enum_taglist) { // could be hoisted
								sprintf(leaves[leaves_i].name,
									leaves[leaves_i].origname,
									dynarray_enum_taglist[
										dynarray_biosarray_i
									].name,
									dynarray_biosarray_i
								);
							} else {
								sprintf(leaves[leaves_i].name,
									leaves[leaves_i].origname,
									dynarray_biosarray_i
								);
							}

							if (leaves[leaves_i].type & ATUI_INLINE) {
								branch_funcify_args.suggestbios =\
									leaves[leaves_i].val;
								inliners[inliners_i] =\
									leaves[leaves_i].branch_bud(
										&branch_funcify_args
									);
								leaves[leaves_i].inline_branch =
									&(inliners[inliners_i]);
								inliners_i++;
							}

							leaves_i++;
							leafpattern_i++;
						}
						dynarray_biosarray_i++;
					}
					leafpattern_start = leafpattern_end;
					dynentry_i++;

// If not dynarray (still has dynarray siblings):
				} else if (leaves_initial[leavesinit_i].type & ATUI_INLINE) {
					leaves[leaves_i] = leaves_initial[leavesinit_i];
					branch_funcify_args.suggestbios = leaves[leaves_i].val;
					inliners[inliners_i] = leaves[leaves_i].branch_bud(
						&branch_funcify_args
					);
					leaves[leaves_i].inline_branch =
						&(inliners[inliners_i]);

					inliners_i++;
					leaves_i++;
				} else if (leaves_initial[leavesinit_i].type & ATUI_PETIOLE) {
					branch_funcify_args.suggestbios =\
						leaves_initial[leavesinit_i].val;
					branches[branches_i] =\
						leaves_initial[leavesinit_i].branch_bud(
							&branch_funcify_args
						);
					branches_i++;
				} else {
					leaves[leaves_i] = leaves_initial[leavesinit_i];
					leaves_i++;
				}
				leavesinit_i++;
			}
		} else {
// minor hoist:  handle leaves if there's no dynarray at all:
			inliners_i = 0;
			leaves_i = 0;
			leavesinit_i = 0;
			while (leavesinit_i < num_leaves_initial) {
				if (leaves_initial[leavesinit_i].type & ATUI_INLINE) {
					leaves[leaves_i] = leaves_initial[leavesinit_i];
					branch_funcify_args.suggestbios = leaves[leaves_i].val;
					inliners[inliners_i] = leaves[leaves_i].branch_bud(
						&branch_funcify_args
					);
					leaves[leaves_i].inline_branch = &(inliners[inliners_i]);
					inliners_i++;
					leaves_i++;
				} else if (leaves_initial[leavesinit_i].type & ATUI_PETIOLE) {
					branch_funcify_args.suggestbios =\
						leaves_initial[leavesinit_i].val;
					branches[branches_i] =\
						leaves_initial[leavesinit_i].branch_bud(
							&branch_funcify_args
						);
					branches_i++;
				} else {
					leaves[leaves_i] = leaves_initial[leavesinit_i];
					leaves_i++;
				}
				leavesinit_i++;
			}
		}

// Handle if there's no leaves at all:
	} else {
		// calloc hands over 0'd memory
		mallocvoid = calloc(1,
			sizeof(atui_branch)
			+ (max_num_branches * sizeof(atui_branch*))
		);
		table = mallocvoid;
		mallocvoid += sizeof(atui_branch);
		if (max_num_branches) {
			all_branches = mallocvoid;
			branches = mallocvoid;
		}
		mallocvoid = NULL; // we are done partitioning
	}

	assert(leaves_i == num_leaves);
	assert(inliners_i == num_inliners);
	assert(branches_i == (num_branches_initial + dynarray_total_branches));

// Handle non-inline branches:
	if (max_num_branches) {
		if (import_branches) {
			importbranches_i = 0;
			while (importbranches_i < num_import_branches) {
				if (import_branches[importbranches_i]) {
					branches[branches_i] =\
						(atui_branch*)import_branches[importbranches_i];
					branches_i++;
				}
				importbranches_i++;
			}
		}

		num_branches = branches_i;

	}

	*table = (atui_branch) {
		.varname = embryo->varname,
		.atomleaves = (void*)args->suggestbios,

		.child_branches = branches,
		.num_branches = num_branches,
		.max_num_branches = max_num_branches,

		.inline_branches = inliners,
		.num_inline_branches = num_inliners,
		.max_num_inline_branches = num_inliners,

		.all_branches = all_branches,
		.max_all_branch_count = max_all_branch_count,

		.leaves = leaves,
		.leaf_count = num_leaves,
		.max_leaves = num_leaves,
	};
	strcpy(table->name, embryo->name);
	return table;
}
