/* AtomTree iterable interface for UIs

atui_branch_allocator is a runtime function that processes the data set up by
the JSON5 tables to generate a cralloc'd branch.

See scripts/ppatui.py for what the JSON5 tables compile to
*/

#include "standard.h"
#include "atui.h"
#include "atui_allocator.h"

// The leaves and branches arrays will be walked through via pointer math
struct leaf_array {
	atui_node* nodes;
	uint16_t i;
	uint16_t end;
};
struct leaf_array_const {
	atui_node const* nodes;
	uint16_t i;
	uint16_t end;
};
struct branch_array {
	atui_node** pos;
	atui_node** end;
};
struct global_tracker {
	struct branch_array grafters;
	struct branch_array branches; // initially shoot-only
	void const* atomtree;
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
	void const* bios;
	char const* nametag;
	atui_node* parent;
	uint16_t name_num;
};

static void
atui_assimilate_subonly(
		atui_node* parent,
		uint16_t num_leaves
		);

static void
atui_leaves_printer(
		struct global_tracker* global,
		struct level_data* level
		);


inline static void
print_atui_nofancy_leaf(
		struct global_tracker* const global __unused,
		struct level_data* const level
		) {
	assert(level->target.i < level->target.end);

	atui_node const* const leaf_src = &(level->feed.nodes[level->feed.i]);
	atui_node* const leaf = &(level->target.nodes[level->target.i]);
	level->target.i++;

	*leaf = *leaf_src;
	leaf->parent = level->parent;
	if (level->bios) {
		leaf->data.input = level->bios;
	}
	sprintf(leaf->name, leaf->origname, level->name_num, level->nametag);
}
inline static void
print_atui_noprint(
		struct global_tracker* const global __unused,
		struct level_data* const level __unused
		) {
	assert(0);
	unreachable();
}


inline static void
print_atui_bitfield_leaf(
		struct global_tracker* const global,
		struct level_data* const level
		) {
	atui_node const* const leaf_src = &(level->feed.nodes[level->feed.i]);
	atui_node* const leaf = &(level->target.nodes[level->target.i]);

	assert(level->target.i < level->target.end);
	// SUBONLY and NODISPLAY should have been handled by ppatui.py
	assert(ATUI_DISPLAY == leaf_src->leaf.type.disable);

	level->target.i++;
	*leaf = *leaf_src;
	leaf->parent = level->parent;
	if (level->bios) {
		leaf->data.input = level->bios;
	}
	sprintf(leaf->name, leaf->origname, level->name_num, level->nametag);

	uint16_t const num_leaves = leaf_src->leaves.count;
	if (num_leaves) {
		leaf->leaves.nodes = cralloc(num_leaves * sizeof(atui_node));
		leaf->leaves.max_count = num_leaves;

		struct level_data sub_leaves = {
			.parent = leaf,
			.bios = leaf->data.input,

			.feed.nodes = leaf_src->leaves.nodes_ro,
			.feed.end = num_leaves,
			.target.nodes = leaf->leaves.nodes,
			.target.end = num_leaves,
		};

		atui_leaves_printer(global, &sub_leaves);
		assert(sub_leaves.target.end == num_leaves);
		assert(sub_leaves.target.nodes == leaf->leaves.nodes);
	};
}

inline static void
print_atui_string_leaf(
		struct global_tracker* const global __unused,
		struct level_data* const level
		) {
	assert(level->target.i < level->target.end);

	atui_node const* const leaf_src = &(level->feed.nodes[level->feed.i]);
	atui_node* const leaf = &(level->target.nodes[level->target.i]);
	level->target.i++;

	*leaf = *leaf_src;
	leaf->parent = level->parent;
	if (level->bios) {
		leaf->data.input = level->bios;
	}
	sprintf(leaf->name, leaf->origname, level->name_num, level->nametag);

	leaf->leaf.array_size = 1 + strlen(leaf->data.c8); // +1 is NULL
	leaf->num_bytes = leaf->leaf.array_size;
}

inline static void
print_atui_graft_leaf(
		struct global_tracker* const global,
		struct level_data* const level
		) {
	atui_node const* const leaf_src = &(level->feed.nodes[level->feed.i]);
	atui_node* const leaf = &(level->target.nodes[level->target.i]);

	// handling ATUI_SUBONLY here is technically possible, but it's O(n^2)
	// due to the re-parenting pass.

	assert(global->grafters.pos < global->grafters.end);

	*leaf = *leaf_src;
	level->target.i++;
	leaf->parent = level->parent;
	sprintf(leaf->name, leaf->origname, level->name_num, level->nametag);

	if (level->bios) {
		leaf->data.input = level->bios;
	}

	atui_node** const grafter = global->grafters.pos;
	global->grafters.pos++;
	*grafter = leaf_src->vestige.branch_bud(& (atuiargs const) {
		.atomtree = global->atomtree,
		.bios = leaf->data.input,
		.rename = leaf->name,
	});

	leaf->leaves = (*grafter)->leaves;
	(*grafter)->leaves = (struct atui_children) {};

	if (ATUI_DISPLAY == leaf_src->leaf.type.disable) {
		for (uint16_t i = 0; i < leaf->leaves.count; i++) {
			leaf->leaves.nodes[i].parent = leaf;
		}
	}
}

inline static void
print_atui_shoot_leaf(
		struct global_tracker* const global,
		struct level_data* const level
		) {
	assert(global->branches.pos < global->branches.end);

	atui_node const* const leaf_src = &(level->feed.nodes[level->feed.i]);
	atui_node** const brancher = global->branches.pos;
	global->branches.pos++;

	atuiargs branch_args = {
		.atomtree = global->atomtree,
	};
	if (level->bios) {
		branch_args.bios = level->bios;
	} else {
		branch_args.bios = leaf_src->data.input;
	}

	*brancher = leaf_src->vestige.branch_bud(&branch_args);

	sprintf((*brancher)->name, leaf_src->origname,
		level->name_num, level->nametag
	);
	// handle branch->parent later
}
inline static void
print_atui_petiole_leaf(
		struct global_tracker* const global,
		struct level_data* const level
		) {
	atui_node const* const leaf_src = &(level->feed.nodes[level->feed.i]);
	atui_node** const brancher = global->branches.pos;
	global->branches.pos++;

	atuiargs branch_args = {};
	if (level->bios) {
		branch_args.bios = level->bios;
	} else {
		branch_args.bios = leaf_src->data.input;
	}
	*brancher = atui_branch_allocator(
		leaf_src->vestige.branch_meta, &branch_args
	);
	atui_node* const branch = *brancher;
	// handle branch->parent later

	if (branch->leaves.count) { // calculate bytes
		// feed the loop
		atui_node const* const leaves = branch->leaves.nodes;
		bool is_contiguous;
		void const* val_end = leaves[0].data.input;
		uint16_t i=0;
		do {
			is_contiguous = (
				(leaves[i].data.input == val_end)
				&& (leaves[i].num_bytes)
			);
			val_end = leaves[i].data.input + leaves[i].num_bytes;
			i++;
		} while ((i < branch->leaves.count) && is_contiguous);
		if (is_contiguous) {
			branch->branch.prefer_contiguous = true;
			branch->data.input = leaves[0].data.input;
			branch->num_bytes = val_end - leaves[0].data.input;
		}
	}
}
inline static void
print_atui_dynarray_leaf(
		struct global_tracker* const global,
		struct level_data* const level
		) {
	atui_node const* const leaf_src = &(level->feed.nodes[level->feed.i]);
	atui_node* const leaf = &(level->target.nodes[level->target.i]);
	struct atui_subleaf_meta const* const sub_meta = (
		leaf_src->vestige.leaves_meta
	);

	assert(
		(level->target.i < level->target.end)
		|| 0 == sub_meta->computed_num_leaves
	);

	void const* bios;
	if (level->bios) {
		bios = level->bios;
	} else {
		bios = leaf_src->data.input;
	}

	atui_node* parent;
	enum atui_leaf_type_disable const disable = leaf_src->leaf.type.disable;
	if (ATUI_DISPLAY == disable) {
		parent = leaf; // not yet copied; parent is late to the recital :(
	} else {
		assert(ATUI_SUBONLY == leaf_src->leaf.type.disable);
		parent = level->parent;
		// parenting could technically be handled in atui_assimilate_subonly,
		// but this is free
	}

	uint8_t const num_graft = sub_meta->computed_num_graft;
	atui_node** const graft_start = global->grafters.pos;

	uint16_t const num_leaves = sub_meta->computed_num_leaves;
	struct level_data sub_leaves = {
		.parent = parent,

		.feed.nodes = leaf_src->leaves.nodes_ro,
		.feed.end = leaf_src->leaves.count,
		.target.end = num_leaves,
	};

	if (sub_meta->dynarray_length) {
		if (ATUI_DISPLAY == disable) {
			sub_leaves.target.nodes = cralloc(
				(num_leaves + num_graft) * sizeof(atui_node)
			);
		} else {
			sub_leaves.target.nodes = level->target.nodes + level->target.i;
			level->target.i += num_leaves;
			// atui_branch_meta.computed_num_leaves already has correct end
		}

		struct atui_enum_entry const* enum_array = NULL;
		struct atui_enum const* taglist __unused = NULL;
		if (sub_meta->enum_taglist) {
			taglist = sub_meta->enum_taglist;
			enum_array = sub_meta->enum_taglist->enum_array;
		};

		struct dynarray_position dynpos = { // direct/diferred positioner
			.pos.ptr = bios,
			.end.ptr = bios,
		};
		if (sub_meta->deferred_start_array) { // array of arrays
			dynpos.end.deffer += sub_meta->dynarray_length;
			while (dynpos.pos.deffer < dynpos.end.deffer) {
				if (enum_array) {
					assert(sub_leaves.name_num < taglist->num_entries);
					sub_leaves.nametag = enum_array[sub_leaves.name_num].name;
				}
				sub_leaves.bios = *dynpos.pos.deffer;
				atui_leaves_printer(global, &sub_leaves);
				sub_leaves.feed.i = 0;
				dynpos.pos.deffer++;
				sub_leaves.name_num++;
			}
		} else {
			dynpos.end.direct += (
				sub_meta->element_size * sub_meta->dynarray_length
			);
			while (dynpos.pos.direct < dynpos.end.direct) {
				if (enum_array) {
					assert(sub_leaves.name_num < taglist->num_entries);
					sub_leaves.nametag = enum_array[sub_leaves.name_num].name;
				}
				sub_leaves.bios = dynpos.pos.direct;
				atui_leaves_printer(global, &sub_leaves);
				sub_leaves.feed.i = 0;
				dynpos.pos.direct += sub_meta->element_size;
				sub_leaves.name_num++;
			}
		}
	}
	assert(num_graft <= (global->grafters.pos - graft_start) );

	if (ATUI_DISPLAY == disable) {
		*leaf = *leaf_src;
		level->target.i++;
		leaf->parent = level->parent;
		sprintf(
			leaf->name, leaf->origname, level->name_num, level->nametag
		);

		// shoot doesn't get counted
		leaf->leaves.count = sub_leaves.target.i;
		if (leaf->leaves.count) {
			leaf->leaves.nodes = sub_leaves.target.nodes;
			leaf->leaves.max_count = sub_leaves.target.end;
			if (num_graft) {
				atui_assimilate_subonly(leaf, num_leaves);
			}
		} else {
			free(sub_leaves.target.nodes);
			leaf->leaves.nodes = NULL;
		}

		// calculate num_bytes 
		leaf->data.input = bios;
		if (sub_meta->deferred_start_array) {
			if (leaf->leaves.count) {
				leaf->data.input = *(void const* const*)(leaf->data.input);
				atui_node const* const last_child = &(
					leaf->leaves.nodes[leaf->leaves.count - 1]
				);
				if (last_child->num_bytes) {
					assert(last_child->data.input >= leaf->data.input);
					leaf->num_bytes = (
						last_child->data.input + last_child->num_bytes
						- leaf->data.input
					);
				} else {
					goto dynarray_deferred_num_bytes_failure;
				}
			} else { // TODO consider shoot only?
				dynarray_deferred_num_bytes_failure:
				leaf->data.input = NULL;
				leaf->num_bytes = 0;
			}
		} else {
			leaf->num_bytes = (
				sub_meta->element_size * sub_meta->dynarray_length
			);
		}
	}
}



void
(* const print_fancy[]) (
		struct global_tracker* global,
		struct level_data* level
		) = { // jump table
	[ATUI_NOFANCY] = print_atui_nofancy_leaf,
	[ATUI_BITFIELD] = print_atui_bitfield_leaf,
	[ATUI_STRING] = print_atui_string_leaf,
	[ATUI_ARRAY] = print_atui_nofancy_leaf,
	[ATUI_GRAFT] = print_atui_graft_leaf,
	[ATUI_SHOOT] = print_atui_shoot_leaf,
	[ATUI_PETIOLE] = print_atui_petiole_leaf,
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
	for (; active->i < active->end; active->i++) {
		assert(active->nodes[active->i].leaf.type.fancy < ATUI_NUM_FANCY);
		print_fancy[active->nodes[active->i].leaf.type.fancy](global, level);
	}
}

atui_node*
atui_branch_allocator(
		struct atui_branch_meta const* const embryo,
		atuiargs const* const args
		) {
	struct global_tracker tracker = {
		.atomtree = args->atomtree,
	};

	atui_node* const table = cralloc(sizeof(atui_node));
	*table = embryo->seed;

	atui_node** branches = NULL;
	atui_node** grafters = NULL;
	uint8_t const num_direct_branches = (
		embryo->computed_num_shoot + args->num_import_branches
	);
	uint8_t max_num_branches = num_direct_branches;
	if (num_direct_branches) {
		branches = cralloc(num_direct_branches * sizeof(atui_node*));
		tracker.branches.pos = branches;
		tracker.branches.end = branches + embryo->computed_num_shoot;
	}
	if (embryo->computed_num_deep_graft) {
		grafters = cralloc(
			embryo->computed_num_deep_graft * sizeof(atui_node*)
		);
		tracker.grafters.pos = grafters;
		tracker.grafters.end = grafters + embryo->computed_num_deep_graft;
	}

	if (embryo->seed.leaves.count) {
		uint8_t const num_subonly_graft = embryo->computed_num_shallow_graft;
		uint16_t const num_leaves = embryo->computed_num_leaves;
		struct level_data first_leaves = {
			.parent = table,

			.feed.nodes = embryo->seed.leaves.nodes_ro,
			.feed.end = embryo->seed.leaves.count,
			.target.nodes = cralloc(
				(num_leaves + num_subonly_graft) * sizeof(atui_node)
			),
			.target.end = num_leaves + num_subonly_graft,
		};
		atui_leaves_printer(&tracker, &first_leaves);
		assert(first_leaves.target.i == first_leaves.target.end);

		table->leaves.nodes = first_leaves.target.nodes;
		table->leaves.count = first_leaves.target.end;
		table->leaves.max_count = first_leaves.target.end;

		if (num_subonly_graft) {
			atui_assimilate_subonly(table, num_leaves);
		}

		for (uint16_t i=0; i < table->leaves.count; i++) {
			if (table->leaves.nodes[i].num_bytes) { // if it maps the bios
				table->branch.num_copyable_leaves++;
			}
		}
	}
	assert(tracker.branches.pos == tracker.branches.end);
	assert(tracker.grafters.pos == tracker.grafters.end);

	if (embryo->computed_num_deep_graft) {
		// pull in branches from all the graft branches, and free the trunks
		uint16_t num_indirect_branches = 0;
		for (uint8_t i=0; i < embryo->computed_num_deep_graft; i++) {
			num_indirect_branches += grafters[i]->branch.branches.count;
		}
		if (num_indirect_branches) {
			max_num_branches += num_indirect_branches;
			branches = crealloc(
				branches, max_num_branches*sizeof(atui_node*)
			);

			tracker.branches.pos = branches + embryo->computed_num_shoot;
			tracker.branches.end = tracker.branches.pos + num_indirect_branches;
			for (uint8_t i=0; i < embryo->computed_num_deep_graft; i++) {
				uint16_t const num_child_branches = grafters[i]->branch.branches.count;
				if (num_child_branches) {
					atui_node** const child_branches = (
						grafters[i]->branch.branches.addresses
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
				free(grafters[i]); // free the trunk
			}
			assert(tracker.branches.pos == tracker.branches.end);
		} else { // no branches to pull in
			for (uint8_t i=0; i < embryo->computed_num_deep_graft; i++) {
				// don't free leaves; there's no branches to free
				free(grafters[i]); // free the trunk
			}
		}
		free(grafters);
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

	table->branch.branches.addresses = branches;
	table->branch.branches.max_count = max_num_branches;
	table->branch.branches.count = tracker.branches.pos - branches;
	for (uint8_t i=0; i < table->branch.branches.count; i++) {
		branches[i]->parent = table;
	}

	if (args->rename) {
		assert(strlen(args->rename) < sizeof((atui_node){}.name));
		strcpy(table->name, args->rename);
	}

	return table;
}

static void
_atui_destroy_leaves(
		struct atui_children* const leaves
		) {
	if (leaves->count) {
		assert(false == leaves->indirect);
		do {
			leaves->count--;
			_atui_destroy_leaves(&(leaves->nodes[leaves->count].leaves));
		} while (leaves->count);
		free(leaves->nodes);
	}
}
void
atui_destroy_tree(
		atui_node* const tree
		) {
	_atui_destroy_leaves(&(tree->leaves));
	assert(false == tree->is_leaf);
	struct atui_children* const branches = &(tree->branch.branches);
	assert(branches->indirect);
	while (branches->count) {
		branches->count--;
		atui_destroy_tree(branches->addresses[branches->count]);
	}
	free(branches->addresses);
	free(tree);
}


static void
atui_leaves_reparent_regrandparent(
		atui_node* const parent
		) {
	// set the parent for all child leaves, and set the parent for all
	// grandchildren, as a reallocs/moves changes addresses

	for (uint16_t child_i = 0; child_i < parent->leaves.count; child_i++) {
		atui_node* child = &(parent->leaves.nodes[child_i]);
		child->parent = parent;
		for (uint16_t grand_i = 0; grand_i < child->leaves.count; grand_i++) {
			child->leaves.nodes[grand_i].parent = child;
		}
	}
}

static void
atui_assimilate_subonly(
		atui_node* const parent,
		uint16_t const num_leaves
		) { // should look vaguely similar to atui_assimilate_leaves
	atui_node* const old_start = parent->leaves.nodes;
	atui_node const* const old_end = old_start + parent->leaves.count;
	atui_node const* old_walker;

	uint16_t computed_num_leaves = num_leaves;
	for (old_walker = old_start; old_walker < old_end; old_walker++) {
		if (ATUI_SUBONLY == old_walker->leaf.type.disable) {
			computed_num_leaves += old_walker->leaves.count;
		}
	}
	if (computed_num_leaves == num_leaves) {
		assert(0); // unnecessary call?
		return;
	}
	
	parent->leaves.nodes = cralloc(computed_num_leaves * sizeof(atui_node));
	parent->leaves.count = computed_num_leaves;
	parent->leaves.max_count = computed_num_leaves;

	atui_node* const new_start = parent->leaves.nodes;
	atui_node const* const new_end = new_start + computed_num_leaves;
	atui_node* new_walker = new_start;

	for (old_walker = old_start; old_walker < old_end; old_walker++) {
		if (ATUI_SUBONLY == old_walker->leaf.type.disable) {
			new_walker = mempcpy(
				new_walker, old_walker->leaves.nodes,
				(old_walker->leaves.count * sizeof(atui_node))
			);
		} else {
			*new_walker = *old_walker;
			new_walker++;
		}
	}
	assert(new_walker == new_end);

	for (old_walker = old_start; old_walker < old_end; old_walker++) {
		if (ATUI_SUBONLY == old_walker->leaf.type.disable) {
			free(old_walker->leaves.nodes);
		}
	}
	free(old_start);

	atui_leaves_reparent_regrandparent(parent);
}

static void
atui_assimilate_leaves(
		atui_node* const dest,
		atui_node* const* const src_array,
		uint16_t const src_array_len
		) { // should look vaguely similar to atui_assimilate_subonly
	uint16_t const old_leaf_count = dest->leaves.count;
	uint16_t new_leaf_count = dest->leaves.count;
	for (uint16_t i=0; i < src_array_len; i++) {
		new_leaf_count += src_array[i]->leaves.count;
	}

	if (old_leaf_count == new_leaf_count) {
		return;
	}

	atui_node* const leaves = crealloc(
		dest->leaves.nodes,  (new_leaf_count * sizeof(atui_node))
	);
	dest->leaves.nodes = leaves;
	dest->leaves.count = new_leaf_count;
	dest->leaves.max_count = new_leaf_count;

	uint16_t dest_leaf_i = old_leaf_count;
	for (uint16_t src_branch_i=0; src_branch_i < src_array_len; src_branch_i++){
		atui_node const* src = src_array[src_branch_i];
		uint16_t src_leaf_i = 0;
		while (src_leaf_i < src->leaves.count) {
			leaves[dest_leaf_i] = src->leaves.nodes[src_leaf_i];
			leaves[dest_leaf_i].parent = dest;
			src_leaf_i++;
			dest_leaf_i++;
		}
	}
	assert(dest_leaf_i == new_leaf_count);

	atui_leaves_reparent_regrandparent(dest);
}
static void
atui_assimilate_branches(
		atui_node* const dest,
		atui_node* const* const src_array,
		uint16_t const src_array_len
		) {
	uint16_t const old_num_branches = dest->branch.branches.count;
	uint16_t new_num_branches = dest->branch.branches.count;
	for (uint16_t i=0; i < src_array_len; i++) {
		new_num_branches += src_array[i]->branch.branches.count;
	}

	if (old_num_branches == new_num_branches) {
		return;
	}

	atui_node** const branches = crealloc(
		dest->branch.branches.addresses,  (new_num_branches * sizeof(atui_node*))
	);
	dest->branch.branches.addresses = branches;
	dest->branch.branches.count = new_num_branches;

	uint16_t dest_branch_i = dest->branch.branches.count;
	for (uint16_t i=0; i < src_array_len; i++) {
		atui_node const* src = src_array[i];
		uint16_t src_branch_i = 0;
		while (src_branch_i < src->branch.branches.count) {
			branches[dest_branch_i] = src->branch.branches.addresses[src_branch_i];
			branches[dest_branch_i]->parent = dest;
			src_branch_i++;
			dest_branch_i++;
		}
	}
	assert(dest_branch_i == new_num_branches);

	while (dest_branch_i) { // the realloc may change parent branch address
		dest_branch_i--;
		atui_node** grandchildren = branches[dest_branch_i]->branch.branches.addresses;
		uint16_t num_grandchildren = branches[dest_branch_i]->branch.branches.count;
		int16_t grand_child_i = 0;
		for (; grand_child_i < num_grandchildren; grand_child_i++) {
			grandchildren[grand_child_i]->parent = (
				branches[dest_branch_i]
			);
		}
	}
}

void
atui_assimilate(
		atui_node* const dest,
		atui_node* const* const src_array,
		uint16_t const src_array_len
		) {
	atui_assimilate_leaves(dest, src_array, src_array_len);
	atui_assimilate_branches(dest, src_array, src_array_len);

	for (uint16_t i=0; i < src_array_len; i++) {
		free(src_array[i]->leaves.nodes);
		free(src_array[i]->branch.branches.addresses);
		free(src_array[i]);
	}	
}
