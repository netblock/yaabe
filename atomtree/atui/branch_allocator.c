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
	atui_node* pos; // position
	atui_node* end;
};
struct leaf_array_const {
	atui_node const* pos;
	atui_node const* end;
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
		struct global_tracker* const global __unused,
		struct level_data* const level
		) {
	assert(level->target.pos < level->target.end);

	atui_node const* const leaf_src = level->feed.pos;
	atui_node* const leaf = level->target.pos;
	level->target.pos++;

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
	assert(level->target.pos < level->target.end);

	atui_node const* const leaf_src = level->feed.pos;
	atui_node* const leaf = level->target.pos;
	level->target.pos++;

	*leaf = *leaf_src;
	leaf->parent = level->parent;
	if (level->bios) {
		leaf->data.input = level->bios;
	}
	sprintf(leaf->name, leaf->origname, level->name_num, level->nametag);

	uint16_t const num_leaves = leaf_src->leaf.vestige.template_leaves->numleaves;
	if (num_leaves) {
		assert(leaf->leaves.count == num_leaves); // ppatui.py sets
		leaf->leaves.nodes = cralloc(num_leaves * sizeof(atui_node));

		struct level_data sub_leaves = {
			.parent = leaf, // ppatui.py sets parent_is_leaf
			.bios = leaf->data.input,

			.feed.pos = leaf_src->leaf.vestige.template_leaves->sub_leaves,
			.feed.end = leaf_src->leaf.vestige.template_leaves->sub_leaves + num_leaves,
			.target.pos = leaf->leaves.nodes,
			.target.end = leaf->leaves.nodes + num_leaves,
		};

		atui_leaves_printer(global, &sub_leaves);
	};
}

inline static void
print_atui_string_leaf(
		struct global_tracker* const global __unused,
		struct level_data* const level
		) {
	assert(level->target.pos < level->target.end);

	atui_node const* const leaf_src = level->feed.pos;
	atui_node* const leaf = level->target.pos;
	level->target.pos++;

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
	assert(level->target.pos < level->target.end);
	assert(global->grafters.pos < global->grafters.end);

	atui_node const* const leaf_src = level->feed.pos;
	atui_node* const leaf = level->target.pos;
	level->target.pos++;
	atui_node** const grafter = global->grafters.pos;
	global->grafters.pos++;

	*leaf = *leaf_src;
	leaf->parent = level->parent;
	if (level->bios) {
		leaf->data.input = level->bios;
	}
	sprintf(leaf->name, leaf->origname, level->name_num, level->nametag);

	atuiargs branch_args = {
		.atomtree = global->atomtree,
		.rename = leaf->name,
		.bios = leaf->data.input,
	};
	*grafter = leaf->leaf.vestige.branch_bud(&branch_args);

	uint16_t const num_child_leaves = (*grafter)->leaves.count;
	atui_node* const child_leaves = (*grafter)->leaves.nodes;
	for (uint16_t i = 0; i < num_child_leaves; i++) {
		child_leaves[i].parent = leaf;
		//child_leaves[i].parent_is_leaf = true;
	}

	leaf->leaves.nodes = child_leaves;
	leaf->leaves.count = num_child_leaves;
}

inline static void
print_atui_shoot_leaf(
		struct global_tracker* const global,
		struct level_data* const level
		) {
	assert(global->branches.pos < global->branches.end);

	atui_node const* const leaf_src = level->feed.pos;
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

	*brancher = leaf_src->leaf.vestige.branch_bud(&branch_args);

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
	atui_node const* const leaf_src = level->feed.pos;
	atui_node** const brancher = global->branches.pos;
	global->branches.pos++;

	atuiargs branch_args = {};
	if (level->bios) {
		branch_args.bios = level->bios;
	} else {
		branch_args.bios = leaf_src->data.input;
	}
	*brancher = atui_branch_allocator(leaf_src->leaf.vestige.template_branch, &branch_args);
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
			branch->data.input = (void*) leaves[0].data.input;
			branch->num_bytes = val_end - leaves[0].data.input;
		}
	}
}
inline static void
print_atui_dynarray_leaf(
		struct global_tracker* const global,
		struct level_data* const level
		) {
	assert(level->target.pos < level->target.end);

	atui_node const* const leaf_src = level->feed.pos;
	atui_node* const leaf = level->target.pos;
	level->target.pos++;

	*leaf = *leaf_src;
	leaf->parent = level->parent;
	if (level->bios) {
		leaf->data.input = level->bios;
	}
	sprintf(leaf->name, leaf->origname, level->name_num, level->nametag);

	struct subleaf_meta const* const sub_meta = leaf_src->leaf.vestige.template_leaves;
	uint16_t const num_leaves = sub_meta->numleaves * sub_meta->dynarray_length;
	if (num_leaves) {
		atui_node const* const feed_start = sub_meta->sub_leaves;
		leaf->leaves.nodes = cralloc(num_leaves * sizeof(atui_node));

		struct dynarray_position dynpos = { // direct/diferred positioner
			.pos.ptr = leaf_src->data.input,
			.end.ptr = leaf_src->data.input,
		};

		struct level_data sub_leaves = {
			.parent = leaf, // ppatui.py sets parent_is_leaf

			.feed.pos = feed_start,
			.feed.end = feed_start + sub_meta->numleaves,
			.target.pos = leaf->leaves.nodes,
			.target.end = leaf->leaves.nodes + num_leaves,
		};

		struct atui_enum_entry const* enum_array = NULL;
		struct atui_enum const* taglist __unused = NULL;
		if (sub_meta->enum_taglist) {
			taglist = sub_meta->enum_taglist;
			enum_array = sub_meta->enum_taglist->enum_array;
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
				sub_leaves.bios = dynpos.pos.direct;
				atui_leaves_printer(global, &sub_leaves);
				sub_leaves.feed.pos = feed_start;
				dynpos.pos.direct += sub_meta->element_size;
				sub_leaves.name_num++;
			}
		}

		// shoot doesn't get counted
		leaf->leaves.count = sub_leaves.target.pos - leaf->leaves.nodes;
		if (0 == leaf->leaves.count) {
			free(leaf->leaves.nodes);
			leaf->leaves.nodes = NULL;
		}
	}

	// calculate num_bytes 
	if (sub_meta->deferred_start_array) { // num_bytes
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
		leaf->num_bytes = sub_meta->element_size * sub_meta->dynarray_length;
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
	for (; active->pos < active->end; active->pos++) {
		assert(active->pos->leaf.type.fancy < ATUI_NUM_FANCY);
		print_fancy[active->pos->leaf.type.fancy](global, level);
	}
}


static void
atui_subonly_pullin(
		atui_node** parent_leaves, 
		uint16_t* num_child_leaves,
		void* parent
		) {
	// pull in the child leaves from all children grandchildren etc where the
	// parent is marked ATUI_SUBONLY
	if (0 == num_child_leaves) {
		return;
	}
	struct {
		atui_node* start;
		atui_node* pos;
		atui_node* end;
	} stack[ATUI_STACK_DEPTH];

	uint8_t stack_i = 0;

	uint16_t num_new_leaves = 0;
	uint16_t num_subonlys = 0;

	stack[0].pos = *parent_leaves;
	stack[0].end = *parent_leaves + *num_child_leaves;
	goto counter_loop_entry;
	do { // iterative form
		stack_i--;
		counter_loop_entry:
		while (stack[stack_i].pos < stack[stack_i].end) {
			if (ATUI_SUBONLY == stack[stack_i].pos->leaf.type.disable) {
				stack[stack_i+1].pos = stack[stack_i].pos->leaves.nodes;
				stack[stack_i+1].end = (
					stack[stack_i].pos->leaves.nodes
					+ stack[stack_i].pos->leaves.count
				);
				stack[stack_i].pos++;
				stack_i++;
				num_subonlys++;
				assert(stack_i < lengthof(stack));
			} else {
				stack[stack_i].pos++;
				num_new_leaves++;
			}
		}
	} while (stack_i);

	if (0 == num_subonlys) {
		goto handle_subonly_on_grandchildren;
	}

	atui_node* const newleaves = cralloc(sizeof(atui_node) * num_new_leaves);
	atui_node* walker = newleaves;

	stack[0].start = *parent_leaves;
	stack[0].pos = *parent_leaves;
	goto puller_loop_entry;
	do {
		stack_i--;
		puller_loop_entry:
		while (stack[stack_i].pos < stack[stack_i].end) {
			if (ATUI_SUBONLY == stack[stack_i].pos->leaf.type.disable) {
				stack[stack_i+1].start = stack[stack_i].pos->leaves.nodes;
				stack[stack_i+1].pos = stack[stack_i].pos->leaves.nodes;
				stack[stack_i+1].end = (
					stack[stack_i].pos->leaves.nodes
					+ stack[stack_i].pos->leaves.count
				);
				stack[stack_i].pos++;
				stack_i++;
			} else {
				*walker = *stack[stack_i].pos;
				// handle parent association outside of this
				walker++;
				stack[stack_i].pos++;
			}
		}
		free(stack[stack_i].start);
	} while (stack_i);
	assert(num_new_leaves == (walker - newleaves));

	(*parent_leaves) = newleaves;
	(*num_child_leaves) = num_new_leaves;

	handle_subonly_on_grandchildren:
	// needs to happen on child leaves as well.
	// branch -> display -> subonly -> display
	//              ^<-------------------<v
	uint16_t const num_leaves = *num_child_leaves;
	for (uint16_t i=0; i < num_leaves; i++) {
		atui_node* leaf = &((*parent_leaves)[i]);
		assert(ATUI_DISPLAY == leaf->leaf.type.disable);
		// setting parent_is_leaf should not be necessary for leaves <- leaves
		leaf->parent = parent;
		if (leaf->leaves.count) {
			atui_subonly_pullin(
				&(leaf->leaves.nodes), &(leaf->leaves.count),  leaf
			);
		}
	}
}

atui_node*
atui_branch_allocator(
		struct atui_branch_data const* const embryo,
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
	if (embryo->computed_num_graft) {
		grafters = cralloc(embryo->computed_num_graft * sizeof(atui_node*));
		tracker.grafters.pos = grafters;
		tracker.grafters.end = grafters + embryo->computed_num_graft;
	}

	if (embryo->computed_num_leaves) {
		table->leaves.nodes = cralloc(
			embryo->computed_num_leaves * sizeof(atui_node)
		);

		struct level_data first_leaves = {
			.parent = table,

			.feed.pos = embryo->leaves_init,
			.feed.end = embryo->leaves_init + embryo->num_leaves_init,
			.target.pos = table->leaves.nodes,
			.target.end = table->leaves.nodes + embryo->num_leaves_init,
		};
		atui_leaves_printer(&tracker, &first_leaves);

		// shoot doesn't get counted
		table->leaves.count = first_leaves.target.pos - table->leaves.nodes;

		atui_subonly_pullin(&(table->leaves.nodes), &(table->leaves.count), table);

		for (uint16_t i=0; i < table->leaves.count; i++) {
			if (table->leaves.nodes[i].num_bytes) { // if it maps the bios
				table->branch.num_copyable_leaves++;
			}

			// see atui_subonly_pullin
			//table->leaves.nodes[i].parent_is_leaf = false;
		}
	}
	assert(tracker.branches.pos == tracker.branches.end);
	assert(tracker.grafters.pos == tracker.grafters.end);

	if (embryo->computed_num_graft) {
		// pull in branches from all the graft branches, and free the trunks
		uint16_t num_indirect_branches = 0;
		for (uint8_t i=0; i < embryo->computed_num_graft; i++) {
			num_indirect_branches += grafters[i]->branch.branches.count;
		}
		if (num_indirect_branches) {
			max_num_branches += num_indirect_branches;
			branches = crealloc(
				branches, max_num_branches*sizeof(atui_node*)
			);

			tracker.branches.pos = branches + embryo->computed_num_shoot;
			tracker.branches.end = tracker.branches.pos + num_indirect_branches;
			for (uint8_t i=0; i < embryo->computed_num_graft; i++) {
				uint16_t const num_child_branches = grafters[i]->branch.branches.count;
				if (num_child_branches) {
					atui_node** const child_branches = (
						grafters[i]->branch.branches.nodes
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
			for (uint8_t i=0; i < embryo->computed_num_graft; i++) {
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

	table->branch.branches.nodes = branches;
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
		atui_node* const leaves,
		uint16_t const num_leaves
		) {
	for (uint16_t i = 0; i < num_leaves; i++) {
		if (leaves[i].leaves.count) {
			_atui_destroy_leaves(
				leaves[i].leaves.nodes, leaves[i].leaves.count
			);
			free(leaves[i].leaves.nodes);
		}
	}
}
void
atui_destroy_tree(
		atui_node* const tree
		) {
	// a reference implementation. deallocates the data set up by
	// atui_branch_allocator
	if (tree->leaves.count) {
		_atui_destroy_leaves(tree->leaves.nodes, tree->leaves.count);
		free(tree->leaves.nodes);
	}
	while (tree->branch.branches.count) {
		tree->branch.branches.count--;
		atui_destroy_tree(tree->branch.branches.nodes[tree->branch.branches.count]);
	}
	free(tree->branch.branches.nodes);
	free(tree);
}


static void
atui_assimilate_leaves(
		atui_node* const dest,
		atui_node* const* const src_array,
		uint16_t const src_array_len
		) {
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

	while (dest_leaf_i) { // the realloc may change parent leaf address
		dest_leaf_i--;
		atui_node* grandchildren = leaves[dest_leaf_i].leaves.nodes;
		uint16_t num_grandchildren = leaves[dest_leaf_i].leaves.count;
		int16_t grand_child_i = 0;
		for (; grand_child_i < num_grandchildren; grand_child_i++) {
			grandchildren[grand_child_i].parent = &(leaves[dest_leaf_i]);
		}
	}
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
		dest->branch.branches.nodes,  (new_num_branches * sizeof(atui_node*))
	);
	dest->branch.branches.nodes = branches;
	dest->branch.branches.count = new_num_branches;

	uint16_t dest_branch_i = dest->branch.branches.count;
	for (uint16_t i=0; i < src_array_len; i++) {
		atui_node const* src = src_array[i];
		uint16_t src_branch_i = 0;
		while (src_branch_i < src->branch.branches.count) {
			branches[dest_branch_i] = src->branch.branches.nodes[src_branch_i];
			branches[dest_branch_i]->parent = dest;
			src_branch_i++;
			dest_branch_i++;
		}
	}
	assert(dest_branch_i == new_num_branches);

	while (dest_branch_i) { // the realloc may change parent branch address
		dest_branch_i--;
		atui_node** grandchildren = branches[dest_branch_i]->branch.branches.nodes;
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
		free(src_array[i]->branch.branches.nodes);
		free(src_array[i]);
	}	
}
