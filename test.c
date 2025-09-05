// this technically compiles without standard.h, but takes forever to link

// gatui_tree_select_in_model_by_path makes this extremely expensive

#include "standard.h"

#include "atomtree.h"
#include "atui.h"
#include "gatui_private.h"
#include "yaabe_gtk4.h"

// landing is in main
static struct error error = {}; // error handling

inline static void
gatui_leaf_test_memory(
		GATUILeaf* const leaf
		) {
	if (gatui_leaf_has_textable_value(leaf)) {
		char* value_text = NULL;
		value_text = gatui_leaf_value_to_text(leaf);
		gatui_leaf_set_value_from_text(leaf, value_text);
		free(value_text);
	}
}

inline static void
gatui_node_test_memory(
		GATUINode* const node,
		GATUITree* const root
		) {
	size_t bios_size = 0;
	void const* const bios = gatui_tree_get_bios_pointer(root, &bios_size);
	atui_node const* const atui = _gatui_node_get_atui(node);

	bool success = false;
	char* b64_text = NULL;
	GVariant* val = NULL;
	void* oldmem = NULL;

	if (atui->num_bytes) {
		oldmem = cralloc(atui->num_bytes);
		memcpy(oldmem, atui->data.input, atui->num_bytes);

		error_assert(&error, ERROR_CRASH, NULL,
			bios <= atui->data.input
		);
		error_assert(&error, ERROR_CRASH, NULL,
			(atui->data.input + atui->num_bytes - 1)
			<= (bios + bios_size)
		);

		val = gatui_node_get_contiguous_data(node);
		success = gatui_node_set_contiguous_data(node, val);
		error_assert(&error, ERROR_CRASH, NULL, success);
		success = gatui_node_set_value(node, val);
		error_assert(&error, ERROR_CRASH, NULL, success);
		g_variant_unref(val);
		val = NULL;
		
		val = gatui_node_get_value(node);
		success = gatui_node_set_value(node, val);
		error_assert(&error, ERROR_CRASH, NULL, success);
		g_variant_unref(val);
		val = NULL;


		b64_text = gatui_node_to_base64(node, GATUI_NODE_B64_CONTIGUOUS);
		success = gatui_node_from_base64(node, b64_text, NULL);
		error_assert(&error, ERROR_CRASH, NULL, success);
		free(b64_text);
		b64_text = NULL;

		b64_text = gatui_node_to_base64(node, GATUI_NODE_B64_VALUE);
		success = gatui_node_from_base64(node, b64_text, NULL);
		error_assert(&error, ERROR_CRASH, NULL, success);
		free(b64_text);
		b64_text = NULL;

		success = 0 == memcmp(oldmem, atui->data.input, atui->num_bytes);
		error_assert(&error, ERROR_CRASH, NULL, success);
	}
	if (atui->num_copyable_leaves) {
		uint16_t num_copyable_leaves = 0;
		val = NULL;
		gatui_node_get_leaves_package(node, &val, &num_copyable_leaves);
		success = gatui_node_set_leaves_memory_package(
			node, val, num_copyable_leaves
		);
		error_assert(&error, ERROR_CRASH, NULL, success);
		g_variant_unref(val);
		val = NULL;

		b64_text = gatui_node_to_base64(node, GATUI_NODE_B64_LEAVES_PACKAGE);
		success = gatui_node_from_base64(node, b64_text, NULL);
		error_assert(&error, ERROR_CRASH, NULL, success);
		free(b64_text);
		b64_text = NULL;

		success = 0 == memcmp(oldmem, atui->data.input, atui->num_bytes);
		error_assert(&error, ERROR_CRASH, NULL, success);
	}

	if (GATUI_IS_LEAF(node)) {
		gatui_leaf_test_memory(GATUI_LEAF(node));

		success = 0 == memcmp(oldmem, atui->data.input, atui->num_bytes);
		error_assert(&error, ERROR_CRASH, NULL, success);
	}

	free(oldmem);
}

inline static char*
gatui_node_test_path(
		GATUINode* const node,
		GATUITree* const root
		) {
	char* const path = gatui_node_to_path(node);
	bool success;

	int16_t branch_index = -1;
	int16_t leaf_index = -1;
	success = gatui_tree_select_in_model_by_path(
		root,  path, &branch_index, &leaf_index, NULL
	);
	error_assert(&error, ERROR_CRASH, NULL,
		success
	);

	GATUINode* node_via_roundabout = NULL;

	GListModel* const branch_model = G_LIST_MODEL(
		gatui_tree_create_trunk_model(root)
	);
	GtkTreeListRow* const branch_row = GTK_TREE_LIST_ROW(
		g_list_model_get_item(branch_model, branch_index)
	);
	GATUIBranch* const owning_branch = GATUI_BRANCH(
		gtk_tree_list_row_get_item(branch_row)
	);
	g_object_unref(branch_row);
	g_object_unref(branch_model);

	if (GATUI_IS_LEAF(node)) {
		GListModel* const leaves_model = G_LIST_MODEL(
			gatui_branch_get_leaves_model(owning_branch)
		);
		GtkTreeListRow* const leaf_row = GTK_TREE_LIST_ROW(
			g_list_model_get_item(leaves_model, leaf_index)
		);
		node_via_roundabout = GATUI_NODE(gtk_tree_list_row_get_item(leaf_row));
		g_object_unref(leaf_row);
		//g_object_unref(leaves_model); // does not get ref'd
		g_object_unref(owning_branch);
	} else {
		node_via_roundabout = GATUI_NODE(owning_branch);
	}

	error_assert(&error, ERROR_CRASH, NULL,
		node == node_via_roundabout // test uniqueness
	);
	g_object_unref(node_via_roundabout);
	return path;
}

static void
gatui_node_test(
	GATUINode* const node
	) {
	atui_node const* const atui = _gatui_node_get_atui(node);
	GATUITree* const root = gatui_node_get_root(node);

	bool success;

	bool const is_leaf = GATUI_IS_LEAF(node);
	error_assert(&error, ERROR_CRASH, NULL,
		is_leaf == atui->is_leaf
	);
	error_assert(&error, ERROR_CRASH, NULL,
		strlen(atui->name) < sizeof(atui->name)
	);

	char* const path = gatui_node_test_path(node, root); // free later for debug

	success = gatui_tree_select_in_model_by_path(root, path, NULL,NULL,NULL);
	error_assert(&error, ERROR_CRASH, NULL,
		success
	);

	gatui_node_test_memory(node, root);

	if (atui->leaves.count) {
		struct atui_children const* const leaves = &(atui->leaves);
		GATUILeaf* const* const leaves_array = _gatui_node_get_leaf_array(node);
		for (uint16_t i=0; i < leaves->count; i++) {
			gatui_node_test(GATUI_NODE(leaves_array[i]));
		}
	}

	if (! is_leaf) {
		struct atui_children const* const branches = &(atui->branch.branches);
		GATUIBranch* const* const branches_array = (
			_gatui_branch_get_branches_array(GATUI_BRANCH(node))
		);
		for (uint16_t i=0; i < branches->count; i++) {
			gatui_node_test(GATUI_NODE(branches_array[i]));
		}

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

		GATUINode* const trunk = GATUI_NODE(gatui_tree_get_trunk(root));
		GtkSelectionModel* const model = gatui_tree_create_trunk_model(root);

		gatui_node_test(trunk);

		g_assert_finalize_object(model);
		g_assert_finalize_object(trunk);
		g_assert_finalize_object(root);
	}

	return ret_val;
}
