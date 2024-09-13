// this technically compiles without standard.h, but takes forever to link
#include "standard.h"

#include "atomtree.h"
#include "atui.h"
#include "gatui.h"
#include "yaabe_gtk4.h"

// landing is in main
static struct error error = {}; // error handling

void
gatui_leaf_test(
		GATUILeaf* const leaf,
		GATUITree* const root
		) {
	// TODO actually test stuff
	atui_leaf const* const atui = gatui_leaf_get_atui(leaf);
	struct atom_tree* const a_root = gatui_tree_get_atom_tree(root);

	if (atui->val) {
		error_assert(&error, ERROR_CRASH,
			"leaf bios val out of bounds",
			a_root->bios <= atui->val
		);
		error_assert(&error, ERROR_CRASH,
			"leaf bios val out of bounds",
			(atui->val + atui->num_bytes - 1)
			<= (a_root->bios + a_root->biosfile_size)
		);
	}

	error_assert(&error, ERROR_CRASH,
		"leaf name too long",
		strlen(atui->name) < sizeof(atui->name)
	);

	GListModel* const leaves = gatui_leaf_generate_children_model(leaf);
	if (leaves) {
		GObject* child = NULL;
		uint16_t const num_leaves = g_list_model_get_n_items(leaves);
		error_assert(&error, ERROR_CRASH,
			"gatui leaf count incorrect",
			atui->num_child_leaves <= num_leaves
			// would be == but ATUI_SUBONLY is not handled at allocation time
		);
		for (uint16_t i=0; i < num_leaves; i++) {
			child = g_list_model_get_object(leaves, i);
			gatui_leaf_test(GATUI_LEAF(child), root);
			g_object_unref(child);
		}
		g_object_unref(leaves);
	}
}

void
gatui_branch_test(
		GATUIBranch* const branch,
		GATUITree* const root
		) {
	// TODO actually test stuff
	atui_branch const* const atui = gatui_branch_get_atui(branch);
	struct atom_tree* const a_root = gatui_tree_get_atom_tree(root);

	if (atui->table_start) {
		error_assert(&error, ERROR_CRASH,
			"branch bios val out of bounds",
			a_root->bios <= atui->table_start
		);
		error_assert(&error, ERROR_CRASH,
			"branch bios val out of bounds",
			(atui->table_start + atui->table_size - 1)
			<= (a_root->bios + a_root->biosfile_size)
		);
	}

	error_assert(&error, ERROR_CRASH,
		"branch name too long",
		strlen(atui->name) < sizeof(atui->name)
	);


	GObject* child = NULL;
	GtkSelectionModel* const leaves = gatui_branch_get_leaves_model(branch);
	if (leaves) {
		GListModel* const leaves_model = G_LIST_MODEL(leaves);
		uint16_t const num_leaves = g_list_model_get_n_items(leaves_model);
		/* ATUI_SUBONLY complications
		error_assert(&error, ERROR_CRASH,
			"gatui leaf count incorrect",
			atui->leaf_count == num_leaves
		);
		*/
		GtkTreeListRow* row = NULL;
		for (uint16_t i=0; i < num_leaves; i++) {
			row = GTK_TREE_LIST_ROW(g_list_model_get_object(leaves_model, i));
			child = gtk_tree_list_row_get_item(row);
			gatui_leaf_test(GATUI_LEAF(child), root);
			g_object_unref(row);
			g_object_unref(child);
		}
	}


	GListModel* const branches = gatui_branch_generate_children_model(branch);
	if (branches) {
		uint16_t const num_branches = g_list_model_get_n_items(branches);
		error_assert(&error, ERROR_CRASH,
			"incorrect number of branches",
			atui->num_branches == num_branches
		);
		for (uint16_t i=0; i < num_branches; i++) {
			child = g_list_model_get_object(branches, i);
			gatui_branch_test(GATUI_BRANCH(child), root);
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
	enum error_severity ret_val = NO_ERROR;
	GATUITree* root = NULL;

	setjmp(error.env);
	ret_val = error.severity;
	if (error.severity) {
		return ret_val;
	}

	if (argc > 1) {
		GError* ferror = NULL;
		root = gatui_tree_new_from_path(argv[1], &ferror);
		if (ferror) {
			printf("%s\n", ferror->message);
			g_error_free(ferror);
			return 1;
		}
	}

	if (root) {
		error_assert(&error, ERROR_CRASH,
			"can't get struct atom_tree",
			gatui_tree_get_atom_tree(root)
		);

		GATUIBranch* const trunk = gatui_tree_get_trunk(root);

		gatui_branch_test(trunk, root);

		g_assert_finalize_object(trunk);
		g_assert_finalize_object(root);
	}

	return ret_val;
}
