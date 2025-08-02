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
atui_leaves_printer(
		struct global_tracker* global,
		struct level_data* level
		);
static void
atui_assimilate_subonly(
		atui_node* parent,
		uint16_t num_leaves
		);

static void
atui_assimilate_nodes( // take all nodes of src_array and append them to dest. You also will need to call atui_nodes_reparent
		struct atui_children* const dest,
		struct atui_children const* const* const src_array,
		uint16_t const src_array_len
		);
static void
atui_nodes_reparent(
		atui_node* parent,
		struct atui_children const* children
		);


inline static void
print_atui_noprint(
		struct global_tracker* const global __unused,
		struct level_data* const level __unused
		) {
	assert(0);
	unreachable();
}
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

	atui_node* const branch = leaf_src->vestige.branch_bud(&branch_args);
	*brancher = branch;

	sprintf(branch->name, leaf_src->origname,level->name_num, level->nametag);
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
	atui_node* const branch = atui_branch_allocator(
		leaf_src->vestige.branch_meta, &branch_args
	);
	*brancher = branch;
	// handle branch->parent later

	if (branch->leaves.count) { // calculate bytes
		// feed the loop
		atui_node const* const leaves = branch->leaves.nodes;
		bool is_contiguous;
		void const* val_end = leaves[0].data.input;
		uint16_t i = 0;
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
	enum atui_leaf_type_disable const disable = leaf_src->leaf.type.disable;

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

	atui_node** const graft_start = global->grafters.pos;
	uint8_t const num_graft = sub_meta->computed_num_graft;
	uint16_t const num_leaves = sub_meta->computed_num_leaves;
	struct level_data sub_leaves = {
		.feed.nodes = leaf_src->leaves.nodes_ro,
		.feed.end = leaf_src->leaves.count,
		.target.end = num_leaves,
	};
	if (ATUI_DISPLAY == disable) {
		// not yet copied; parent is late to the recital :(
		sub_leaves.parent = leaf;
	} else {
		assert(ATUI_SUBONLY == leaf_src->leaf.type.disable);
		sub_leaves.parent = level->parent;
		// parenting could technically be handled in atui_assimilate_subonly,
		// but this is free
	}

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
		sprintf(leaf->name, leaf->origname, level->name_num, level->nametag);

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

	// the branches from grafters will change count and thus max_count
	struct atui_children* const branches = &(table->branch.branches);
	branches->count = embryo->computed_num_shoot;
	branches->max_count = (
		embryo->computed_num_shoot + args->num_import_branches
	);
	if (branches->max_count) {
		atui_node** const addresses = cralloc(
			branches->max_count * sizeof(atui_node*)
		);
		branches->addresses = addresses;
		tracker.branches.pos = addresses;
		tracker.branches.end = addresses + branches->count;
	}

	void* graft_arena;
	atui_node** grafters = NULL;
	struct atui_children const** graft_children;
	if (embryo->computed_num_deep_graft) {
		graft_arena = cralloc(
			(embryo->computed_num_deep_graft * sizeof(atui_node*))
			+ (embryo->computed_num_deep_graft * sizeof(struct atui_children*))
		);
		void* graft_partition = graft_arena;

		grafters = graft_partition;
		tracker.grafters.pos = graft_partition;
		tracker.grafters.end = (
			tracker.grafters.pos + embryo->computed_num_deep_graft
		);
		graft_partition += (
			embryo->computed_num_deep_graft * sizeof(atui_node*)
		);

		graft_children = graft_partition;

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
		for (uint8_t i=0; i < embryo->computed_num_deep_graft; i++) {
			graft_children[i] = &(grafters[i]->branch.branches);
		}
		atui_assimilate_nodes(
			branches,  graft_children, embryo->computed_num_deep_graft
		);
		for (uint8_t i=0; i < embryo->computed_num_deep_graft; i++) {
			free(grafters[i]->branch.branches.addresses);
			free(grafters[i]);
		}
		free(graft_arena);
	}

	if (args->import_branches) {
		atui_node** dest = branches->addresses + branches->count;
		for (uint8_t imp_i=0; imp_i < args->num_import_branches; imp_i++) {
			if (args->import_branches[imp_i]) {
				*dest = args->import_branches[imp_i];
				dest++;
			}
		}
		branches->count = dest - branches->addresses;
	}

	atui_nodes_reparent(table, branches);

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
atui_nodes_reparent(
		atui_node* const parent,
		struct atui_children const* const children
		) {
 	// TODO if there's gonna be other ways of how children works, besides
	// leaves and branches, this fails

	if (children->indirect) {
		// set the parent for all child branches
		for (uint16_t child_i = 0; child_i < children->count; child_i++) {
			children->addresses[child_i]->parent = parent;
		}
	} else {
		// set the parent for all child leaves, and set the parent for all
		// grandchildren, as a reallocs/moves changes addresses
		for (uint16_t child_i = 0; child_i < children->count; child_i++) {
			atui_node* child = &(children->nodes[child_i]);
			child->parent = parent;
			for (uint16_t grand_i=0; grand_i < child->leaves.count; grand_i++) {
				child->leaves.nodes[grand_i].parent = child;
			}
		}
	}
}

static void
atui_assimilate_subonly(
		atui_node* const parent,
		uint16_t const num_leaves
		) { // should look vaguely similar to atui_assimilate_nodes
	atui_node* const old_start = parent->leaves.nodes;
	atui_node const* const old_end = old_start + parent->leaves.count;
	atui_node const* old_walker;

	uint16_t new_count = num_leaves;
	for (old_walker = old_start; old_walker < old_end; old_walker++) {
		if (ATUI_SUBONLY == old_walker->leaf.type.disable) {
			new_count += old_walker->leaves.count;
		}
	}
	if (new_count == num_leaves) {
		assert(0); // unnecessary call?
		return;
	}
	
	atui_node* const new_start = cralloc(new_count * sizeof(atui_node));
	atui_node const* const new_end = new_start + new_count;
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

	parent->leaves.nodes = new_start;
	parent->leaves.count = new_count;
	parent->leaves.max_count = new_count;

	atui_nodes_reparent(parent, &(parent->leaves));
}


static void
atui_assimilate_nodes(
		struct atui_children* const dest,
		struct atui_children const* const* const src_array,
		uint16_t const src_array_len
		) { // should look vaguely similar to atui_assimilate_subonly
	// take all nodes of src_array and append them to dest.
	// You also will need to call atui_nodes_reparent
	uint16_t const old_count = dest->count;
	uint16_t new_count = dest->count;
	for (uint16_t i=0; i < src_array_len; i++) {
		new_count += src_array[i]->count;
	}

	if (old_count == new_count) {
		return;
	}

	size_t const entry_size = (size_t const[]) {
		[false] = sizeof(atui_node),
		[true]  = sizeof(atui_node*),
	} [dest->indirect];

	uint32_t const max_count = new_count + (dest->max_count - dest->count);
	void* const new_start = crealloc(dest->array,  max_count * entry_size);
	void const* const new_end = new_start + (new_count * entry_size);
	void* new_walker = new_start + (old_count * entry_size);

	for (uint16_t i = 0; i < src_array_len; i++) {
		assert(dest->indirect == src_array[i]->indirect);
		new_walker = mempcpy(
			new_walker, src_array[i]->array,
			(src_array[i]->count * entry_size)
		);
	}
	assert(new_walker == new_end);

	dest->nodes = new_start;
	dest->count = new_count;
	dest->max_count = max_count;
}

void
atui_assimilate(
		atui_node* const dest,
		atui_node* const* const src_array,
		uint16_t const src_array_len
		) {
	assert(false == dest->is_leaf);

	assert(src_array_len);
	if (0 == src_array_len) {
		return;
	}

	size_t const array_segment_size = (
		src_array_len * sizeof(struct atui_children*)
	);
	void* const arena = cralloc(2 * array_segment_size);
	void* partition = arena;
	struct atui_children const** const leaves = partition;
	partition += array_segment_size;
	struct atui_children const** const branches = partition;
	partition = NULL; // done partitioning.

	for (uint16_t i=0; i < src_array_len; i++) {
		assert(false == src_array[i]->is_leaf);
		leaves[i] = &(src_array[i]->leaves);
		branches[i] = &(src_array[i]->branch.branches);
	}

	atui_assimilate_nodes(&(dest->leaves),  leaves, src_array_len);
	atui_nodes_reparent(dest, &(dest->leaves));
	atui_assimilate_nodes(&(dest->branch.branches),  branches, src_array_len);
	atui_nodes_reparent(dest, &(dest->branch.branches));

	free(arena);
	for (uint16_t i=0; i < src_array_len; i++) {
		free(src_array[i]->leaves.nodes);
		free(src_array[i]->branch.branches.addresses);
		free(src_array[i]);
	}	
}
