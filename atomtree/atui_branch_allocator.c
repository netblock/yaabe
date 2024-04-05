#include "atomtree.h"
#include "atui.h"

// TODO fake malloc that uses the precalc'd alloc

/* AtomTree iterable interface for UIs

atui_branch_allocator processes the data set up by the ATUI_FUNCIFY functions
to spit out your branch

*/

// The leaves and branches arrays will be walked through via pointer math
struct leaf_array {
	atui_leaf* pos; // position
	atui_leaf* end;
};
struct leaf_array_const {
	const atui_leaf* pos;
	const atui_leaf* end;
};
struct branch_array {
	atui_branch** pos;
	atui_branch** end;
};
struct global_tracker {
	struct branch_array inliners;
	struct branch_array branches; // initially petiole-only
	struct atui_funcify_args branch_args;
};
struct dynarray_position {
	union {
		const void* ptr; // union writes
		const void* direct;
		const void* const* deffer;
	} pos;
	union {
		const void* ptr; // union writes
		const void* direct;
		const void* const* deffer;
	} end;
};

struct level_data {
	struct leaf_array target;
	struct leaf_array_const feed;

	struct dynarray_position dynpos;
	const void* suggestbios;
	const struct atui_enum* nametag;
	uint8_t name_num;
	bool rename;
};

static void
atui_leaves_printer(
		struct global_tracker* const global,
		struct level_data* const level
		) {
	struct branch_array* const inliners = &(global->inliners);
	struct branch_array* const branches = &(global->branches);

	struct leaf_array* const leaves = &(level->target);
	struct leaf_array_const* const active = &(level->feed);

	
	const char8_t* nametag;
	if (level->nametag) {
		nametag = level->nametag->enum_array[level->name_num].name;
	} else {
		nametag = NULL;
	}

	struct level_data sub_leaves;
	const struct subleaf_meta* sub_meta;
	struct dynarray_position dynpos;
	uint8_t num_leaves;

	while (active->pos < active->end) {
		if (active->pos->type & ATUI_PETIOLE) {
			if (level->suggestbios) {
				global->branch_args.suggestbios = level->suggestbios;
			} else {
				global->branch_args.suggestbios = active->pos->val;
			}
			global->branch_args.rename = NULL;
			assert(branches->pos < branches->end);
			*(branches->pos) = active->pos->branch_bud(&(global->branch_args));
			if (level->rename) {
				if (nametag) {
					sprintf((*branches->pos)->name, active->pos->origname,
						nametag, level->name_num
					);
				} else {
					sprintf((*branches->pos)->name, active->pos->origname,
						level->name_num
					);
				}
			}

			branches->pos++;
			active->pos++;
			continue;
		}

		assert(leaves->pos < leaves->end);
		*(leaves->pos) = *(active->pos);
		if (level->suggestbios) {
			leaves->pos->val = level->suggestbios;
		}
		if (level->rename) {
			if (nametag) {
				sprintf(leaves->pos->name, leaves->pos->origname,
					nametag, level->name_num
				);
			} else {
				sprintf(leaves->pos->name, leaves->pos->origname,
					level->name_num
				);
			}
		}

		if (active->pos->type &
				(ATUI_NOFANCY|ATUI_ENUM|ATUI_ARRAY|_ATUI_BITCHILD)
				) {
			// nothing more
		} else if (active->pos->type & ATUI_BITFIELD) {
			//sub_meta = active->pos->template_leaves;
			num_leaves = active->pos->template_leaves->numleaves;
			sub_leaves = (struct level_data){0};
	
			sub_leaves.suggestbios = leaves->pos->val;
			sub_leaves.feed.pos = active->pos->template_leaves->sub_leaves;
			sub_leaves.feed.end = sub_leaves.feed.pos;
			sub_leaves.feed.end += num_leaves; // automatic pointer math
			sub_leaves.target.pos = calloc(num_leaves, sizeof(atui_leaf));
			sub_leaves.target.end = sub_leaves.target.pos;
			sub_leaves.target.end += num_leaves;

			leaves->pos->child_leaves = sub_leaves.target.pos;
			assert(leaves->pos->num_child_leaves == num_leaves);
			//leaves->pos->num_child_leaves = num_leaves;

			atui_leaves_printer(global, &sub_leaves);
		} else if (active->pos->type & ATUI_INLINE) {
			assert(inliners->pos < inliners->end);
			global->branch_args.rename = leaves->pos->name;
			global->branch_args.suggestbios = leaves->pos->val;
			*(inliners->pos) = active->pos->branch_bud(&(global->branch_args));
			leaves->pos->inline_branch = inliners->pos;
			inliners->pos++;
		} else if (active->pos->type & ATUI_DYNARRAY) {
			sub_meta = active->pos->template_leaves;
			const atui_leaf* const feed_start = sub_meta->sub_leaves;
			dynpos.pos.ptr = active->pos->val;
			dynpos.end.ptr = active->pos->val;

			//sub_leaves = (struct level_data){0};
			sub_leaves.name_num = 0;
			sub_leaves.rename = true;
			sub_leaves.nametag = sub_meta->enum_taglist;

			num_leaves = sub_meta->numleaves;
			sub_leaves.feed.pos = feed_start;
			sub_leaves.feed.end = feed_start;
			sub_leaves.feed.end += num_leaves;
			num_leaves *= sub_meta->dynarray_length;
			sub_leaves.target.pos = calloc(num_leaves, sizeof(atui_leaf));
			sub_leaves.target.end = sub_leaves.target.pos;
			sub_leaves.target.end += num_leaves;

			leaves->pos->child_leaves = sub_leaves.target.pos;

			if (sub_meta->deferred_start_array) {
				dynpos.end.deffer += sub_meta->dynarray_length;
				while (dynpos.pos.deffer < dynpos.end.deffer) {
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
					sub_leaves.suggestbios = dynpos.pos.direct;
					atui_leaves_printer(global, &sub_leaves);
					sub_leaves.feed.pos = feed_start;
					dynpos.pos.direct += sub_meta->element_size;
					sub_leaves.name_num++;
				}
			}

			leaves->pos->num_child_leaves = ( // petiole doesn't get counted
				sub_leaves.target.pos - leaves->pos->child_leaves
			);
			if (sub_meta->deferred_start_array) { // num_bytes
				if (leaves->pos->num_child_leaves) {
					leaves->pos->val = *(const void* const*)(leaves->pos->val);
					const atui_leaf* const last_child = &(
						leaves->pos->child_leaves[
							leaves->pos->num_child_leaves - 1
						]
					);
					if (last_child->num_bytes) {
						assert(last_child->val >= leaves->pos->val);
						leaves->pos->num_bytes = (
							last_child->val + last_child->num_bytes
							- leaves->pos->val
						);
					} else {
						goto dynarray_deferred_num_bytes_failure;
					}
				} else {
					dynarray_deferred_num_bytes_failure:
					leaves->pos->val = NULL;
					leaves->pos->num_bytes = 0;
				}
			} else {
				leaves->pos->num_bytes = (
					sub_meta->element_size * sub_meta->dynarray_length
				);
			}
		} else if (active->pos->type & ATUI_STRING) {
			leaves->pos->array_size = 1 + strlen(leaves->pos->u8); // +1 is NULL
			leaves->pos->num_bytes = leaves->pos->array_size;
		}
		leaves->pos++;
		active->pos++;
	}
}

atui_branch*
atui_branch_allocator(
		const struct atui_branch_data* const embryo,
		const struct atui_funcify_args* const args
		) {

	struct global_tracker tracker = {0};

	uint8_t max_num_branches = (
		embryo->computed_num_petiole + args->num_import_branches
	);
	uint8_t num_all_branches = max_num_branches + embryo->computed_num_inline;

	atui_branch* table;
	void* mallocvoid; // temporary malloc partitioning pointer
	/* topology:
	main table
	all branches:
		child
		inline
	leaves
	*/
	mallocvoid = calloc(1,
		sizeof(atui_branch)
		+ (num_all_branches * sizeof(atui_branch*))
		+ (embryo->num_leaves_init * sizeof(atui_leaf))
		//+ (embryo->computed_num_leaves * sizeof(atui_leaf)) //TODO fake malloc
	);
	table = mallocvoid;
	mallocvoid += sizeof(atui_branch);
	if (num_all_branches) {
		table->all_branches = mallocvoid;
		table->max_num_branches = max_num_branches;
		table->max_all_branch_count = num_all_branches;
		if (max_num_branches) {
			// handle table->max_num_branches at the end, for import
			table->child_branches = mallocvoid;
			tracker.branches.pos = mallocvoid;
			tracker.branches.end = mallocvoid;
			tracker.branches.end += embryo->computed_num_petiole;
			mallocvoid += (max_num_branches * sizeof(atui_branch*));
		}
		if (embryo->computed_num_inline) {
			table->num_inline_branches = embryo->computed_num_inline;
			table->inline_branches = mallocvoid;
			tracker.inliners.pos = mallocvoid;
			tracker.inliners.end = mallocvoid;
			tracker.inliners.end += embryo->computed_num_inline;
			mallocvoid += (embryo->computed_num_inline * sizeof(atui_branch*));
		}
	}

	if (embryo->computed_num_leaves) {
		table->leaves = mallocvoid;
		mallocvoid = NULL; // we are done partitioning

		tracker.branch_args.atomtree = args->atomtree;
		struct level_data first_leaves = {0};

		first_leaves.feed.pos = embryo->leaves_init;
		first_leaves.feed.end = embryo->leaves_init;
		first_leaves.feed.end += embryo->num_leaves_init;
		first_leaves.target.pos = table->leaves;
		first_leaves.target.end = table->leaves;
		first_leaves.target.end += embryo->num_leaves_init;
		atui_leaves_printer(&tracker, &first_leaves);

		//table->max_leaves = (
		//	embryo->computed_num_leaves - embryo->computed_num_petiole
		//); // TODO
		table->max_leaves = embryo->num_leaves_init;
		// petiole doesn't get counted
		table->leaf_count = first_leaves.target.pos - table->leaves;
	}
	assert(tracker.branches.pos == tracker.branches.end);
	assert(tracker.inliners.pos == tracker.inliners.end);

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
	table->num_branches = tracker.branches.pos - table->child_branches;


	table->origname = embryo->origname;
	if (args->rename) {
		strcpy(table->name, args->rename);
	} else {
		strcpy(table->name, embryo->origname);
	}
	assert(strlen(table->name) < sizeof(((atui_branch*)0)->name));

	memcpy(table->description, embryo->description, sizeof(table->description));

	return table;
}
