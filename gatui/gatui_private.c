#include "gatui_private.h"

void
atui_leaves_to_gliststore(
		GListStore* const list,
		atui_leaf* const leaves,
		uint16_t const num_leaves
		) {
// If the parent leaf has children, but the parent is labeled with ATUI_SUBONLY,
// adopt them in.
	for (uint16_t i=0; i < num_leaves; i++) {
		atui_leaf* leaf = &(leaves[i]);
		if (leaf->type & ATUI_NODISPLAY) {
			// ignore the leaf
		} else if (leaf->type & ATUI_SUBONLY) {
			atui_leaves_to_gliststore(
				list, leaf->child_leaves, leaf->num_child_leaves
			);
		} else {
			GATUILeaf* gleaf = gatui_leaf_new(leaf);
			g_list_store_append(list, gleaf);
			g_object_unref(gleaf);
		}
	}
}
