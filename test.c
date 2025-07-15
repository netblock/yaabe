// this technically compiles without standard.h, but takes forever to link

// gatui_tree_select_in_model_by_path makes this extremely expensive

#include "standard.h"

#include "atomtree.h"
#include "atui.h"
#include "gatui.h"
#include "yaabe_gtk4.h"

// landing is in main
static struct error error = {}; // error handling

static void
gatui_leaf_test_get_set_memory(
		GATUILeaf* const leaf
		) {
	atui_node const* const atui = gatui_leaf_get_atui(leaf);
	bool success;
	GVariant* val; 
	if (atui->num_bytes || _ATUI_BITCHILD == atui->leaf.type.fancy) {
		val = gatui_leaf_get_value(leaf, true);
		success = gatui_leaf_set_value(leaf, val);
		error_assert(&error, ERROR_CRASH, NULL,
			success
		);
		g_variant_unref(val);
		val = gatui_leaf_get_value(leaf, false);
		success = gatui_leaf_set_value(leaf, val);
		error_assert(&error, ERROR_CRASH, NULL,
			success
		);
		char* const b64_text = gatui_leaf_value_to_base64(leaf);
		success = gatui_leaf_value_from_base64(leaf, b64_text, NULL);
		error_assert(&error, ERROR_CRASH, NULL,
			success
		);
		free(b64_text);
		g_variant_unref(val);
	};
}

static char*
gatui_leaf_test_path(
		GATUILeaf* const leaf,
		GATUITree* const root
		) {
	char* const path = gatui_leaf_to_path(leaf);
	bool success;

	int16_t branch_index;
	int16_t leaf_index;
	success = gatui_tree_select_in_model_by_path(root,
		path, &branch_index, &leaf_index, NULL
	);
	error_assert(&error, ERROR_CRASH, NULL,
		success
	);

	GListModel* const branch_model = G_LIST_MODEL(
		gatui_tree_create_trunk_model(root)
	);
	GtkTreeListRow* const branch_row = GTK_TREE_LIST_ROW(
		g_list_model_get_item(branch_model, branch_index)
	);
	GATUIBranch* const owning_branch = GATUI_BRANCH(
		gtk_tree_list_row_get_item(branch_row)
	);

	GListModel* const leaves_model = G_LIST_MODEL(
		gatui_branch_get_leaves_model(owning_branch)
	);
	GtkTreeListRow* const leaf_row = GTK_TREE_LIST_ROW(
		g_list_model_get_item(leaves_model, leaf_index)
	);
	GATUILeaf* const self = GATUI_LEAF(gtk_tree_list_row_get_item(leaf_row));

	error_assert(&error, ERROR_CRASH, NULL,
		leaf == self // path uniqueness
	);

	g_object_unref(self);
	g_object_unref(leaf_row);
	//g_object_unref(leaves_model); // does not get ref'd

	g_object_unref(owning_branch);
	g_object_unref(branch_row);
	g_object_unref(branch_model);

	return path;
}

static void
gatui_leaf_test(
		GATUILeaf* const leaf,
		GATUITree* const root
		) {
	// TODO actually test stuff
	atui_node const* const atui = gatui_leaf_get_atui(leaf);
	struct atom_tree const* const a_root = gatui_tree_get_atom_tree(root);
	//bool success;

	if (atui->data.input) {
		error_assert(&error, ERROR_CRASH, NULL,
			a_root->bios <= atui->data.input
		);
		error_assert(&error, ERROR_CRASH, NULL,
			(atui->data.input + atui->num_bytes - 1)
			<= (a_root->bios + a_root->biosfile_size)
		);
	}

	error_assert(&error, ERROR_CRASH, NULL,
		strlen(atui->name) < sizeof(atui->name)
	);

	gatui_leaf_test_get_set_memory(leaf);

	char* const path = gatui_leaf_test_path(leaf, root); // free later for debug

	GListModel* const child_leaves = leaves_treelist_generate_children(
		leaf, NULL
	);
	error_assert(&error, ERROR_CRASH, NULL,
		(NULL == child_leaves) ^ (0 < atui->leaves.count)
	);
	if (child_leaves) {
		for (uint16_t i=0; i < atui->leaves.count; i++) {
			gatui_leaf_test(atui->leaves.nodes[i].self, root);
		}
		g_object_unref(child_leaves);
	}

	free(path);
}


static void
gatui_branch_test_get_set_memory(
		GATUIBranch* const branch
		) {
	atui_node const* const atui = gatui_branch_get_atui(branch);
	bool success;
	char* b64_text;
	if (atui->branch.num_copyable_leaves || atui->num_bytes) {
		GVariant* val = NULL;
		if (atui->branch.num_copyable_leaves && ! atui->branch.prefer_contiguous) {
			uint16_t num_copyable_leaves;
			success = gatui_branch_get_leaves_memory_package(
				branch, &val, &num_copyable_leaves
			);
			error_assert(&error, ERROR_CRASH, NULL,
				success
			);
			success = gatui_branch_set_leaves_memory_package(
				branch, val, num_copyable_leaves
			);
			error_assert(&error, ERROR_CRASH, NULL,
				success
			);
			g_variant_unref(val);
			b64_text = gatui_branch_to_base64(branch, true);
			error_assert(&error, ERROR_CRASH, NULL,
				b64_text
			);
			success = gatui_branch_from_base64(branch, b64_text, NULL);
			error_assert(&error, ERROR_CRASH, NULL,
				success
			);
			free(b64_text);
		}
		if (atui->num_bytes) {
			val = gatui_branch_get_contiguous_memory(branch);
			success = gatui_branch_set_contiguous_memory(branch, val);
			error_assert(&error, ERROR_CRASH, NULL,
				success
			);
			g_variant_unref(val);

			b64_text = gatui_branch_to_base64(branch, false);
			error_assert(&error, ERROR_CRASH, NULL,
				b64_text
			);

			success = gatui_branch_from_base64(branch, b64_text, NULL);
			error_assert(&error, ERROR_CRASH, NULL,
				success
			);
			free(b64_text);
		}
	};
}

static void
gatui_branch_test(
		GATUIBranch* const branch,
		GATUITree* const root
		) {
	// TODO actually test stuff
	atui_node const* const atui = gatui_branch_get_atui(branch);
	struct atom_tree const* const a_root = gatui_tree_get_atom_tree(root);
	bool success;

	if (atui->data.input) {
		error_assert(&error, ERROR_CRASH, NULL,
			a_root->bios <= atui->data.input
		);
		error_assert(&error, ERROR_CRASH, NULL,
			(atui->data.input + atui->num_bytes - 1)
			<= (a_root->bios + a_root->biosfile_size)
		);
	}

	error_assert(&error, ERROR_CRASH, NULL,
		strlen(atui->name) < sizeof(atui->name)
	);

	gatui_branch_test_get_set_memory(branch);

	char* const path = gatui_branch_to_path(branch); // free later for debug
	success = gatui_tree_select_in_model_by_path(root, path, NULL,NULL,NULL);
	error_assert(&error, ERROR_CRASH, NULL,
		success
	);

	GtkSelectionModel* const leaves = gatui_branch_get_leaves_model(branch);
	error_assert(&error, ERROR_CRASH, NULL,
		(NULL == leaves) ^ (0 < atui->leaves.count)
	);
	if (atui->leaves.count) {
		for (uint16_t i=0; i < atui->leaves.count; i++) {
			gatui_leaf_test(atui->leaves.nodes[i].self, root);
		}
	}


	GListModel* const child_branches = branches_treelist_generate_children(
		branch, NULL
	);
	error_assert(&error, ERROR_CRASH, NULL,
		(NULL == child_branches) ^ (0 < atui->branch.branches.count)
	);
	if (child_branches) {
		for (uint16_t i=0; i < atui->branch.branches.count; i++) {
			gatui_branch_test(atui->branch.branches.addresses[i]->self, root);
		}
		g_object_unref(child_branches);
	}

	free(path);
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
		error_assert(&error, ERROR_CRASH, NULL,
			gatui_tree_get_atom_tree(root)
		);

		GATUIBranch* const trunk = gatui_tree_get_trunk(root);
		GtkSelectionModel* const model = gatui_tree_create_trunk_model(root);

		gatui_branch_test(trunk, root);

		g_assert_finalize_object(model);
		g_assert_finalize_object(trunk);
		g_assert_finalize_object(root);
	}

	return ret_val;
}
