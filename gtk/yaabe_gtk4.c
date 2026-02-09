#include "yaabe_gtk_internal.h"

static constexpr char yaabe_name[] = "YAABE BIOS Editor";
static constexpr char yaabe_dbus_name[] = "yaabe.editor";
static constexpr char yaabe_url[] = "https://github.com/netblock/yaabe";

void
free_closure(
		gpointer data,
		GClosure* const closure __unused
		) {
	free(data);
}

void
generic_error_popup(
		char const* const primary,
		char const* const secondary,
		GtkApplication* const parent_app
		) {
	GtkAlertDialog* const alert = gtk_alert_dialog_new("%s", primary);
	gtk_alert_dialog_set_detail(alert, secondary);
	gtk_alert_dialog_show(
		alert,
		gtk_application_get_active_window(parent_app)
	);

	g_object_unref(alert);
}

void
offset_sprintf_big(
		offset_buffer buffer,
		char const* const restrict format,
		size_t const end,
		size_t const start
		) {
	sprintf(buffer, format, start, end);
}
void
offset_sprintf_little(
		offset_buffer buffer,
		char const* const restrict format,
		size_t const end,
		size_t const start
		) {
	sprintf(buffer, format, end, start);
}

void
set_tooltip_to_description(
		GtkWidget* const widget,
		char const* const name,
		char const* const description
		) {
	char buffer[lengthof((atui_node){}.name) + 2 + ATUI_MAX_DESCRIPTION_LENGTH];
	char* walker = buffer;
	walker = stopcopy(walker, name);
	if (description) {
		walker = stopcopy(walker, "\n\n");
		walker = stopcopy(walker, description);
	}
	assert((size_t)(walker - buffer) < lengthof(buffer));
	gtk_widget_set_tooltip_text(widget, buffer);
}

void
create_about_window(
		yaabegtk_commons* const com
		) {
	GtkAboutDialog* const about = GTK_ABOUT_DIALOG(gtk_about_dialog_new());
	gtk_about_dialog_set_version(about, YAABE_VER);
	gtk_about_dialog_set_website(about, yaabe_url);
	gtk_about_dialog_set_website_label(about, yaabe_url);
	gtk_about_dialog_set_license_type(about, GTK_LICENSE_AGPL_3_0);

	GtkWindow* const about_window = GTK_WINDOW(about);
	gtk_window_set_destroy_with_parent(about_window, true);
	gtk_window_set_transient_for(about_window, com->yaabe_primary);
	gtk_window_present(about_window);
}

static void
pathbar_update_path(
		GtkSingleSelection* const model,
		guint const position __unused,
		guint const n_items __unused,
		yaabegtk_commons* const com
		) {
// callback; sets path based on branches selection
	GATUINode* const node = GATUI_NODE(
		gtk_tree_list_row_get_item(GTK_TREE_LIST_ROW(
			gtk_single_selection_get_selected_item(model)
		))
	);
	assert(com->pathbar_string);
	free(com->pathbar_string);
	com->pathbar_string = gatui_node_to_path(node);
	g_object_unref(node);
	gtk_editable_set_text(com->pathbar, com->pathbar_string);
}
static gboolean
pathbar_editable_reset(
		GtkWidget* const pathbar,
		GVariant* const shortcut_args __unused,
		gpointer const commons_ptr
		) {
// callback; resets pathbar if focus is lost
	yaabegtk_commons* const com = commons_ptr;
	gtk_editable_set_text(GTK_EDITABLE(pathbar), com->pathbar_string);
	return true;
}


void
yaabe_gtk_scroll_to_object(
		yaabegtk_commons const* const com,
		GATUINode* const tree_node
		) {
	int16_t branch_index;
	int16_t leaf_index;
	bool const success __unused = gatui_tree_select_in_model_by_object(
		com->root, tree_node, &branch_index, &leaf_index
	);
	assert(success);
	if (-1 < branch_index) {
		gtk_column_view_scroll_to(com->branches.view,
			branch_index, NULL, GTK_LIST_SCROLL_FOCUS, NULL
		);
	}
	if (-1 < leaf_index) {
		gtk_column_view_scroll_to(com->leaves.view,
			leaf_index, NULL, GTK_LIST_SCROLL_FOCUS, NULL
		);
	}
}
void
yaabe_gtk_scroll_to_path(
		yaabegtk_commons const* const com,
		char const* const path,
		struct atui_path_goto** const map_error
		) {
	int16_t branch_index;
	int16_t leaf_index;
	bool const success = gatui_tree_select_in_model_by_path(com->root,
		path,  &branch_index, &leaf_index, map_error
	);
	if (success) {
		if (-1 < branch_index) {
			gtk_column_view_scroll_to(com->branches.view,
				branch_index, NULL, GTK_LIST_SCROLL_FOCUS, NULL
			);
		}
		if (-1 < leaf_index) {
			gtk_column_view_scroll_to(com->leaves.view,
				leaf_index, NULL, GTK_LIST_SCROLL_FOCUS, NULL
			);
		}
	}
}
void
first_load_restore_path(
		yaabegtk_commons* const com
		) {
	char* const path = get_cached_scroll_path();
	yaabe_gtk_scroll_to_path(com, path, NULL);
	free(path);
}

static void
pathbar_sets_branch_selection(
		yaabegtk_commons* const com
		) {
// callback; go to branch based on path string
	char const* const editable_text = gtk_editable_get_text(com->pathbar);
	struct atui_path_goto* map_error = NULL;

	yaabe_gtk_scroll_to_path(com, editable_text, &map_error);

	if (map_error) {
		GtkWindow* const editor_window = gtk_application_get_active_window(
			com->yaabe_gtk
		);
		GtkAlertDialog* alert;
		if (map_error->branch.depth) {
			alert = gtk_alert_dialog_new(
				"\n%s\n not found in:\n %s\n",
				map_error->not_found,
				map_error->branch.node->name
			);
		} else {
			alert = gtk_alert_dialog_new("bad root");
		}
		gtk_alert_dialog_set_detail(alert, editable_text);
		gtk_alert_dialog_show(alert, editor_window);

		g_object_unref(alert);
		free(map_error);
	}
}
inline static GtkWidget*
construct_path_bar(
		yaabegtk_commons* const com
		) {
	GtkWidget* const path_bar = gtk_entry_new();
	com->pathbar = GTK_EDITABLE(path_bar);

	g_signal_connect_swapped(path_bar, "activate",
		G_CALLBACK(pathbar_sets_branch_selection), com
	);

	GtkEventController* const escape_reset = gtk_shortcut_controller_new();
	gtk_shortcut_controller_add_shortcut(
		GTK_SHORTCUT_CONTROLLER(escape_reset),
		gtk_shortcut_new(
			gtk_shortcut_trigger_parse_string("Escape"),
			gtk_callback_action_new(pathbar_editable_reset, com, NULL)
		)
	);
	gtk_widget_add_controller(path_bar, escape_reset);

	return path_bar;
}


static void
leaves_view_deferred_restore_position(
		GtkAdjustment* const adj,
		yaabegtk_commons* const com
		) {
// restore scroll position if branches have similar leaves
	gtk_adjustment_set_value(adj, com->previous_scroll_position);

	g_signal_handlers_disconnect_matched(
		adj,  G_SIGNAL_MATCH_FUNC,
		0,0, NULL,  G_CALLBACK(leaves_view_deferred_restore_position),  NULL
	);
}
static void
select_changes_leaves(
		GtkSingleSelection* const model,
		guint const position __unused,
		guint const n_items __unused,
		yaabegtk_commons* const com
		) {
// Signal callback
// Change the leaves pane's model based on the what is selected in brances
	GATUIBranch* const new_selection = GATUI_BRANCH(
		gtk_tree_list_row_get_item(
			gtk_single_selection_get_selected_item(model)
		)
	);

	GATUINode* const new_node = GATUI_NODE(new_selection);
	GATUINode* const old_node = GATUI_NODE(com->previous_selection);
	bool const similar_branches = (
		(
			gatui_node_get_num_leaves(new_node)
			== gatui_node_get_num_leaves(old_node)
		) && (0 == strcmp(
			gatui_node_get_origname(new_node),
			gatui_node_get_origname(old_node)
		))
	);

	if (similar_branches) { // restore scroll if compatible
		GtkAdjustment* const adj = gtk_scrollable_get_vadjustment(
			GTK_SCROLLABLE(com->leaves.view)
		);
		com->previous_scroll_position = gtk_adjustment_get_value(adj);
		// we can't immedately set the new position because it takes a while
		// for the set_model to propagate.
		g_signal_connect(adj, "value-changed",
			G_CALLBACK(leaves_view_deferred_restore_position), com
		);
	}

	gtk_column_view_set_model(
		com->leaves.view,
		gatui_branch_get_leaves_model(new_selection)
	);
	com->previous_selection = new_selection;

	g_object_unref(new_selection);
}
void
create_and_set_active_gatui_model(
		yaabegtk_commons* const com,
		GATUITree* const new_root
		) {
// create and set the main branch model
	GtkSelectionModel* const new_model = gatui_tree_create_trunk_model(
		new_root
	);
	g_object_connect(new_model,
		"signal::selection-changed", G_CALLBACK(select_changes_leaves), com,
		"signal::selection-changed", G_CALLBACK(pathbar_update_path), com,
		NULL
	);

	com->root = new_root;
	GATUIBranch* const trunk = gatui_tree_get_trunk(new_root);
	com->previous_selection = trunk;

	gtk_column_view_set_model(com->branches.view, new_model);

	// TODO eject leaves model first-time loader into a notify::model callback
	// in create_branches_pane?
	gtk_column_view_set_model(
		com->leaves.view,
		gatui_branch_get_leaves_model(trunk)
	);

	if (com->pathbar_string) {
		free(com->pathbar_string);
	}
	com->pathbar_string = gatui_node_to_path(GATUI_NODE(trunk));
	gtk_editable_set_text(com->pathbar, com->pathbar_string);

	g_object_unref(trunk);
	g_object_unref(new_model);
	// TODO move the call of set_editor_titlebar in here?
}


void
set_editor_titlebar(
		yaabegtk_commons* const com
		) {
// Set the window name to the name of the currently-open bios.
	char const print_format_file[] = "%s (%s)";
	char const print_format_nofile[] = "%s";

	char* filename;
	uint16_t filename_length;
	char const* formatstr;
	if (com->root) {
		filename = g_file_get_basename(
			gatui_tree_get_bios_file(com->root)
		);
		filename_length = strlen(filename);
		formatstr = print_format_file;
	} else {
		filename = NULL;
		filename_length = 0;
		formatstr = print_format_nofile;
	}

	char* const window_title = cralloc(
		sizeof(yaabe_name)
		+ filename_length
		+ sizeof(print_format_file) // largest
	);
	sprintf(window_title, formatstr, yaabe_name, filename);

	gtk_window_set_title(com->yaabe_primary, window_title);

	free(window_title);
	if (filename_length) {
		g_free(filename);
	}
}


static void
yaabe_gtk_activate(
		GtkApplication* const gtkapp,
		yaabegtk_commons* const com
		) {
	construct_menu_bar(com);

	GtkWidget* const path_bar = construct_path_bar(com);
	GtkWidget* const tree_divider = construct_tree_panes(com);
	GtkWidget* const button_box = construct_loadsave_buttons_box(com);

	GtkBox* const main_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_VERTICAL, 0));
	gtk_box_append(main_box, path_bar);
	gtk_box_append(main_box, tree_divider);
	gtk_box_append(main_box, button_box);

	GtkDropTarget* const dropfile = gtk_drop_target_new(
		G_TYPE_FILE, GDK_ACTION_COPY
	);
	g_signal_connect(dropfile, "drop",
		G_CALLBACK(dropped_file_open_bios), com
	);

	GtkApplicationWindow* const app_window = GTK_APPLICATION_WINDOW(
		gtk_application_window_new(gtkapp)
	);
	gtk_application_window_set_show_menubar(app_window, true);
	gtk_widget_add_controller(
		GTK_WIDGET(app_window), GTK_EVENT_CONTROLLER(dropfile)
	);

	GtkWindow* const window = GTK_WINDOW(app_window);
	com->yaabe_primary = window;
	gtk_window_set_default_size(window, 1400,700); // 2:1
	gtk_window_set_child(window, GTK_WIDGET(main_box));

	gtk_widget_grab_focus(tree_divider);
	gtk_widget_grab_focus(GTK_WIDGET(com->branches.view));

	if (com->root) {
		create_and_set_active_gatui_model(com, com->root);
		//first_load_restore_path(com); // TODO
		// columnview scroll position bugs out when done here
	}

	set_editor_titlebar(com);
	gtk_window_present(window);
}
static void
yaabe_gtk_save_path(
		yaabegtk_commons* const com
		) {
	if (com->pathbar_string) {
		set_cached_scroll_path(com->pathbar_string);
	}
}
int8_t
yaabe_gtk(
		GATUITree** const root
		) {
	bool const big_endian = get_big_endianness();

	yaabegtk_commons com = {
		.root = *root,
		.big_endian = big_endian,
		.endian_sprintf = (offset_sprintf const[]) {
			offset_sprintf_little,
			offset_sprintf_big,
		}[big_endian],
		.search.flags = {
			.domain = GATUI_SEARCH_NAMES,
			.leaves = true,
			.branches = true,
		},
	};

	com.yaabe_gtk = gtk_application_new(
		yaabe_dbus_name,
		(G_APPLICATION_HANDLES_OPEN|G_APPLICATION_NON_UNIQUE)
	);
	g_object_connect(com.yaabe_gtk,
		"signal::activate", G_CALLBACK(yaabe_gtk_activate), &com,
		"swapped-signal::shutdown", G_CALLBACK(yaabe_gtk_save_path), &com,
		NULL
	);
	int8_t const status = g_application_run(
		G_APPLICATION(com.yaabe_gtk), 0,NULL
	);

	*root = com.root;
	g_object_unref(com.yaabe_gtk);

	if (com.pathbar_string) {
		free(com.pathbar_string);
	}

	return status;
}
