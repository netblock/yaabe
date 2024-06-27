#include "atomtree.h"
#include "atui.h"
#include "gatui.h"
#include "yaabe_gtk4.h"

void
gatui_leaf_test(
		GATUILeaf* const leaf
		) {
	// TODO actually test stuff
	atui_leaf const* const atui = gatui_leaf_get_atui(leaf);

	GListModel* const leaves = gatui_leaf_generate_children_model(leaf);
	if (leaves) {
		GObject* child = NULL;
		uint16_t const num_leaves = g_list_model_get_n_items(leaves);
		assert(atui->num_child_leaves <= num_leaves);
		for (uint16_t i=0; i < num_leaves; i++) {
			child = g_list_model_get_object(leaves, i);
			gatui_leaf_test(GATUI_LEAF(child));
			g_object_unref(child);
		}
		g_object_unref(leaves);
	}
}

void
gatui_branch_test(
		GATUIBranch* const branch
		) {
	// TODO actually test stuff
	atui_branch const* const atui = gatui_branch_get_atui(branch);

	GObject* child = NULL;
	GtkSelectionModel* const leaves = gatui_branch_get_leaves_model(branch);
	if (leaves) {
		GListModel* const leaves_model = G_LIST_MODEL(leaves);
		uint16_t const num_leaves = g_list_model_get_n_items(leaves_model);
		// assert(atui->leaf_count <= num_leaves); // sub_only complications
		GtkTreeListRow* row = NULL;
		for (uint16_t i=0; i < num_leaves; i++) {
			row = GTK_TREE_LIST_ROW(g_list_model_get_object(leaves_model, i));
			child = gtk_tree_list_row_get_item(row);
			gatui_leaf_test(GATUI_LEAF(child));
			g_object_unref(row);
			g_object_unref(child);
		}
	}


	GListModel* const branches = gatui_branch_generate_children_model(branch);
	if (branches) {
		uint16_t const num_branches = g_list_model_get_n_items(branches);
		assert(atui->num_branches <= num_branches);
		for (uint16_t i=0; i < num_branches; i++) {
			child = g_list_model_get_object(branches, i);
			gatui_branch_test(GATUI_BRANCH(child));
			g_object_unref(child);
		}
		g_object_unref(branches);
	}
}

int
main(
		int const argc,
		char const* const* const argv
		) {
	GATUITree* atree = NULL;

	if (argc > 1) {
		GError* ferror = NULL;
		atree = gatui_tree_new_from_path(argv[1], &ferror);
		if (ferror) {
			printf("%s\n", ferror->message);
			g_error_free(ferror);
			return 1;
		}
	}

	if (atree) {
		GATUIBranch* const trunk = gatui_tree_get_trunk(atree);
		gatui_branch_test(trunk);
		g_assert_finalize_object(trunk);
		g_assert_finalize_object(atree);
	}

	return 0;
}
