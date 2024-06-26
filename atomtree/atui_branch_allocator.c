/* AtomTree iterable interface for UIs

atui_branch_allocator processes the data set up by the ATUI_FUNCIFY functions
to spit out your branch

*/

#include "atomtree.h"
#include "atui.h"

// The leaves and branches arrays will be walked through via pointer math
struct leaf_array {
	atui_leaf* pos; // position
	atui_leaf* end;
};
struct leaf_array_const {
	atui_leaf const* pos;
	atui_leaf const* end;
};
struct branch_array {
	atui_branch** pos;
	atui_branch** end;
};
struct global_tracker {
	struct branch_array inliners;
	struct branch_array branches; // initially petiole-only
	void* atomtree;
};
union dynarray_position_ptr {
	void const* ptr; // union writes
	void const* direct;
	void const* const* deffer;
};
struct dynarray_position {
	union dynarray_position_ptr pos;
	union dynarray_position_ptr end;
};

struct level_data {
	struct leaf_array target;
	struct leaf_array_const feed;

	struct dynarray_position dynpos;
	void const* suggestbios;
	char8_t const* nametag;
	void* parent;
	uint16_t name_num;
};

static void
atui_leaves_printer(
		struct global_tracker* global,
		struct level_data* level
		);


inline static void
print_atui_nofancy_leaf(
		struct global_tracker* const global,
		struct level_data* const level
		) {
	assert(level->target.pos < level->target.end);

	atui_leaf const* const leaf_src = level->feed.pos;
	atui_leaf* const leaf = level->target.pos;
	level->target.pos++;

	*leaf = *leaf_src;
	leaf->parent = level->parent;
	if (level->suggestbios) {
		leaf->val = level->suggestbios;
	}
	if (level->nametag) {
		sprintf(leaf->name, leaf->origname, level->nametag, level->name_num);
	} else {
		sprintf(leaf->name, leaf->origname, level->name_num);
	}
}


inline static void
print_atui_bitfield_leaf(
		struct global_tracker* const global,
		struct level_data* const level
		) {
	assert(level->target.pos < level->target.end);

	atui_leaf const* const leaf_src = level->feed.pos;
	atui_leaf* const leaf = level->target.pos;
	level->target.pos++;

	*leaf = *leaf_src;
	leaf->parent = level->parent;
	if (level->suggestbios) {
		leaf->val = level->suggestbios;
	}
	if (level->nametag) {
		sprintf(leaf->name, leaf->origname, level->nametag, level->name_num);
	} else {
		sprintf(leaf->name, leaf->origname, level->name_num);
	}

	uint16_t const num_leaves = leaf_src->template_leaves->numleaves;
	if (num_leaves) {
		assert(leaf->num_child_leaves == num_leaves); // ppatui.py sets
		leaf->child_leaves = malloc(num_leaves * sizeof(atui_leaf));

		struct level_data sub_leaves = {
			.parent = leaf, // ppatui.py sets parent_is_leaf
			.suggestbios = leaf->val,

			.feed.pos = leaf_src->template_leaves->sub_leaves,
			.feed.end = leaf_src->template_leaves->sub_leaves + num_leaves,
			.target.pos = leaf->child_leaves,
			.target.end = leaf->child_leaves + num_leaves,
		};

		atui_leaves_printer(global, &sub_leaves);
	};
}

inline static void
print_atui_string_leaf(
		struct global_tracker* const global,
		struct level_data* const level
		) {
	assert(level->target.pos < level->target.end);

	atui_leaf const* const leaf_src = level->feed.pos;
	atui_leaf* const leaf = level->target.pos;
	level->target.pos++;

	*leaf = *leaf_src;
	leaf->parent = level->parent;
	if (level->suggestbios) {
		leaf->val = level->suggestbios;
	}
	if (level->nametag) {
		sprintf(leaf->name, leaf->origname, level->nametag, level->name_num);
	} else {
		sprintf(leaf->name, leaf->origname, level->name_num);
	}

	leaf->array_size = 1 + strlen(leaf->u8); // +1 is NULL
	leaf->num_bytes = leaf->array_size;
}

inline static void
print_atui_graft_leaf(
		struct global_tracker* const global,
		struct level_data* const level
		) {
	assert(level->target.pos < level->target.end);
	assert(global->inliners.pos < global->inliners.end);

	atui_leaf const* const leaf_src = level->feed.pos;
	atui_leaf* const leaf = level->target.pos;
	level->target.pos++;
	atui_branch** const inliner = global->inliners.pos;
	global->inliners.pos++;

	*leaf = *leaf_src;
	leaf->parent = level->parent;
	if (level->suggestbios) {
		leaf->val = level->suggestbios;
	}
	if (level->nametag) {
		sprintf(leaf->name, leaf->origname, level->nametag, level->name_num);
	} else {
		sprintf(leaf->name, leaf->origname, level->name_num);
	}


	struct atui_funcify_args branch_args = {
		.atomtree = global->atomtree,
		.rename = leaf->name,
		.suggestbios = leaf->val,
	};
	*inliner = leaf->branch_bud(&branch_args);

	uint16_t const num_child_leaves = (*inliner)->leaf_count;
	atui_leaf* const child_leaves = (*inliner)->leaves;
	for (uint16_t i = 0; i < num_child_leaves; i++) {
		child_leaves[i].parent_leaf = leaf;
		child_leaves[i].parent_is_leaf = true;
	}

	leaf->child_leaves = child_leaves;
	leaf->num_child_leaves = num_child_leaves;
}

inline static void
print_atui_shoot_leaf(
		struct global_tracker* const global,
		struct level_data* const level
		) {
	assert(global->branches.pos < global->branches.end);

	atui_leaf const* const leaf_src = level->feed.pos;
	atui_branch** const brancher = global->branches.pos;
	global->branches.pos++;

	struct atui_funcify_args branch_args = {
		.atomtree = global->atomtree,
	};
	if (level->suggestbios) {
		branch_args.suggestbios = level->suggestbios;
	} else {
		branch_args.suggestbios = leaf_src->val;
	}

	*brancher = leaf_src->branch_bud(&branch_args);

	if (level->nametag) {
		sprintf((*brancher)->name, leaf_src->origname,
			level->nametag, level->name_num
		);
	} else {
		sprintf((*brancher)->name, leaf_src->origname,
			level->name_num
		);
	}
	// handle branch->parent later
}
inline static void
print_atui_dynarray_leaf(
		struct global_tracker* const global,
		struct level_data* const level
		) {
	assert(level->target.pos < level->target.end);

	atui_leaf const* const leaf_src = level->feed.pos;
	atui_leaf* const leaf = level->target.pos;
	level->target.pos++;

	*leaf = *leaf_src;
	leaf->parent = level->parent;
	if (level->suggestbios) {
		leaf->val = level->suggestbios;
	}
	if (level->nametag) {
		sprintf(leaf->name, leaf->origname, level->nametag, level->name_num);
	} else {
		sprintf(leaf->name, leaf->origname, level->name_num);
	}

	struct subleaf_meta const* const sub_meta = leaf_src->template_leaves;
	uint16_t const num_leaves = sub_meta->numleaves * sub_meta->dynarray_length;
	if (num_leaves) {
		atui_leaf const* const feed_start = sub_meta->sub_leaves;
		leaf->child_leaves = malloc(num_leaves * sizeof(atui_leaf));

		struct dynarray_position dynpos = { // direct/diferred positioner
			dynpos.pos.ptr = leaf_src->val,
			dynpos.end.ptr = leaf_src->val,
		};

		struct level_data sub_leaves = {
			.parent = leaf, // ppatui.py sets parent_is_leaf

			.feed.pos = feed_start,
			.feed.end = feed_start + sub_meta->numleaves,
			.target.pos = leaf->child_leaves,
			.target.end = leaf->child_leaves + num_leaves,
		};

		struct atui_enum_entry const* enum_array = NULL;
		if (sub_meta->enum_taglist) {
			enum_array = sub_meta->enum_taglist->enum_array;
		};

		if (sub_meta->deferred_start_array) { // array of arrays
			dynpos.end.deffer += sub_meta->dynarray_length;
			while (dynpos.pos.deffer < dynpos.end.deffer) {
				if (enum_array) {
					sub_leaves.nametag = enum_array[sub_leaves.name_num].name;
				}
				sub_leaves.suggestbios = *dynpos.pos.deffer;
				atui_leaves_printer(global, &sub_leaves);
				sub_leaves.feed.pos = feed_start;
				dynpos.pos.deffer++;
				sub_leaves.name_num++;
			}
		} else {
			dynpos.end.direct += (
				sub_meta->element_size * sub_meta->dynarray_length
			);
			while (dynpos.pos.direct < dynpos.end.direct) {
				if (enum_array) {
					sub_leaves.nametag = enum_array[sub_leaves.name_num].name;
				}
				sub_leaves.suggestbios = dynpos.pos.direct;
				atui_leaves_printer(global, &sub_leaves);
				sub_leaves.feed.pos = feed_start;
				dynpos.pos.direct += sub_meta->element_size;
				sub_leaves.name_num++;
			}
		}

		// petiole doesn't get counted
		leaf->num_child_leaves = sub_leaves.target.pos - leaf->child_leaves;
		if (0 == leaf->num_child_leaves) {
			free(leaf->child_leaves);
			leaf->child_leaves = NULL;
		}

		// calculate num_bytes 
		if (sub_meta->deferred_start_array) { // num_bytes
			if (leaf->num_child_leaves) {
				leaf->val = *(void const* const*)(leaf->val);
				atui_leaf const* const last_child = &(
					leaf->child_leaves[leaf->num_child_leaves - 1]
				);
				if (last_child->num_bytes) {
					assert(last_child->val >= leaf->val);
					leaf->num_bytes = (
						last_child->val + last_child->num_bytes
						- leaf->val
					);
				} else {
					goto dynarray_deferred_num_bytes_failure;
				}
			} else { // TODO consider shoot only?
				dynarray_deferred_num_bytes_failure:
				leaf->val = NULL;
				leaf->num_bytes = 0;
			}
		} else {
			leaf->num_bytes = (
				sub_meta->element_size * sub_meta->dynarray_length
			);
		}
	}
}

static void
(* const print_fancy[]) (
		struct global_tracker* global,
		struct level_data* level
		) = { // jump table
	[ATUI_NOFANCY] = print_atui_nofancy_leaf,
	[ATUI_BITFIELD] = print_atui_bitfield_leaf,
	[ATUI_ENUM] = print_atui_nofancy_leaf,
	[ATUI_STRING] = print_atui_string_leaf,
	[ATUI_ARRAY] = print_atui_nofancy_leaf,
	[ATUI_GRAFT] = print_atui_graft_leaf,
	[ATUI_SHOOT] = print_atui_shoot_leaf,
	[ATUI_DYNARRAY] = print_atui_dynarray_leaf,
	[_ATUI_BITCHILD] = print_atui_nofancy_leaf,
};
static_assert(lengthof(print_fancy) == ATUI_NUM_FANCY);
static void
atui_leaves_printer(
		struct global_tracker* const global,
		struct level_data* const level
		) {
	struct leaf_array_const* const active = &(level->feed);
	for (; active->pos < active->end; active->pos++) {
		assert(active->pos->type.fancy < ATUI_NUM_FANCY);
		print_fancy[active->pos->type.fancy](global, level);
	}
}

atui_branch*
atui_branch_allocator(
		struct atui_branch_data const* const embryo,
		struct atui_funcify_args const* const args
		) {
	struct global_tracker tracker = {
		.atomtree = args->atomtree,
	};

	atui_branch* const table = calloc(1, sizeof(atui_branch));

	atui_branch** branches = NULL;
	atui_branch** inliners = NULL;
	uint8_t const num_direct_branches = (
		embryo->computed_num_petiole + args->num_import_branches
	);
	uint8_t max_num_branches = num_direct_branches;
	if (num_direct_branches) {
		branches = malloc(num_direct_branches * sizeof(atui_branch*));
		tracker.branches.pos = branches;
		tracker.branches.end = branches + embryo->computed_num_petiole;
	}
	if (embryo->computed_num_inline) {
		inliners = malloc(embryo->computed_num_inline * sizeof(atui_branch*));
		tracker.inliners.pos = inliners;
		tracker.inliners.end = inliners + embryo->computed_num_inline;
	}

	if (embryo->computed_num_leaves) {
		table->leaves = malloc(embryo->computed_num_leaves * sizeof(atui_leaf));

		struct level_data first_leaves = {
			.parent = table,

			.feed.pos = embryo->leaves_init,
			.feed.end = embryo->leaves_init + embryo->num_leaves_init,
			.target.pos = table->leaves,
			.target.end = table->leaves + embryo->num_leaves_init,
		};
		atui_leaves_printer(&tracker, &first_leaves);

		table->max_leaves = embryo->num_leaves_init;
		// petiole doesn't get counted
		table->leaf_count = first_leaves.target.pos - table->leaves;

		for (uint16_t i=0; i < table->leaf_count; i++) {
			if (table->leaves[i].num_bytes) { // if it maps the bios
				table->num_copyable_leaves++;
			}
		}
	}
	assert(tracker.branches.pos == tracker.branches.end);
	assert(tracker.inliners.pos == tracker.inliners.end);

	if (embryo->computed_num_inline) {
		// pull in branches from all the inline branches, and free the trunks
		uint16_t num_indirect_branches = 0;
		for (uint8_t i=0; i < embryo->computed_num_inline; i++) {
			num_indirect_branches += inliners[i]->num_branches;
		}
		if (num_indirect_branches) {
			max_num_branches += num_indirect_branches;
			branches = realloc(branches, max_num_branches*sizeof(atui_branch*));

			tracker.branches.pos = branches + embryo->computed_num_petiole;
			tracker.branches.end = tracker.branches.pos + num_indirect_branches;
			for (uint8_t i=0; i < embryo->computed_num_inline; i++) {
				uint16_t const num_child_branches = inliners[i]->num_branches;
				if (num_child_branches) {
					atui_branch** const child_branches = (
						inliners[i]->child_branches
					);
					uint16_t child_i = 0;
					do {
						assert(tracker.branches.pos < tracker.branches.end);
						*(tracker.branches.pos) = child_branches[child_i];
						tracker.branches.pos++;
						child_i++;
					} while (child_i < num_child_branches);
					free(child_branches);
				}
				// don't free leaves
				free(inliners[i]); // free the trunk
			}
			assert(tracker.branches.pos == tracker.branches.end);
		} else { // no branches to pull in
			for (uint8_t i=0; i < embryo->computed_num_inline; i++) {
				// don't free leaves; there's no branches to free
				free(inliners[i]); // free the trunk
			}
		}
		free(inliners);
	}

	if (args->import_branches) {
		tracker.branches.end += args->num_import_branches;
		for (uint8_t i=0; i < args->num_import_branches; i++) {
			if (args->import_branches[i]) {
				assert(tracker.branches.pos < tracker.branches.end);
				*(tracker.branches.pos) = args->import_branches[i];
				tracker.branches.pos++;
			}
		}
	}
	table->child_branches = branches;
	table->max_num_branches = max_num_branches;
	table->num_branches = tracker.branches.pos - branches;
	for (uint8_t i=0; i < table->num_branches; i++) {
		branches[i]->parent_branch = table;
	}


	table->origname = embryo->origname;
	if (args->rename) {
		strcpy(table->name, args->rename);
	} else {
		strcpy(table->name, embryo->origname);
	}
	assert(strlen(table->name) < sizeof(((atui_branch*)0)->name));

	memcpy(table->description, embryo->description, sizeof(table->description));

	table->table_start = embryo->table_start;
	table->table_size = embryo->table_size;
	table->prefer_contiguous = (
		embryo->sizeofbios && (embryo->sizeofbios >= embryo->table_size)
	);

	return table;
}
