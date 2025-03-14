#include "yaabe_gtk_internal.h"

static constexpr char yaabe_name[] = "YAABE BIOS Editor";

void
free_closure(
		gpointer data,
		GClosure* closure __unused
		) {
	free(data);
}
void
free_notify(
		gpointer data
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


static void
pathbar_update_path(
		GtkSingleSelection* const model,
		guint const position __unused,
		guint const n_items __unused,
		yaabegtk_commons* const commons
		) {
// callback; sets path based on branches selection
	GATUIBranch* const g_branch = GATUI_BRANCH(
		gtk_tree_list_row_get_item(GTK_TREE_LIST_ROW(
			gtk_single_selection_get_selected_item(model)
		))
	);
	assert(commons->pathbar_string);
	free(commons->pathbar_string);
	commons->pathbar_string = gatui_branch_to_path(g_branch);
	g_object_unref(g_branch);
	gtk_editable_set_text(commons->pathbar, commons->pathbar_string);
}
static gboolean
pathbar_editable_reset(
		GtkWidget* const pathbar,
		GVariant* const shortcut_args __unused,
		gpointer const commons_ptr
		) {
// callback; resets pathbar if focus is lost
	yaabegtk_commons* const commons = commons_ptr;
	gtk_editable_set_text(GTK_EDITABLE(pathbar), commons->pathbar_string);
	return true;
}

static void
pathbar_sets_branch_selection(
		yaabegtk_commons* const commons
		) {
// callback; go to branch based on path string
	char const* const editable_text = gtk_editable_get_text(commons->pathbar);

	GATUIBranch* g_root = gatui_tree_get_trunk(commons->root);
	g_object_unref(g_root); // we don't need a 2nd reference
	struct atui_path_map* const map = path_to_atui(
		editable_text,
		gatui_branch_get_atui(g_root)
	);

	if (NULL == map->not_found) { // if directory is found
		GObject const* target;
		GObject* questioned;
		GtkTreeListRow* tree_item;
		uint16_t model_i;
		uint8_t depth_i;

		GListModel* const branch_model = G_LIST_MODEL(gtk_column_view_get_model(
			commons->branches.view
		));

		// test to see if our target is already selected
		target = G_OBJECT(map->branch_path[map->branch_depth - 1]->self);
		questioned = G_OBJECT(gtk_tree_list_row_get_item(GTK_TREE_LIST_ROW(
			gtk_single_selection_get_selected_item(GTK_SINGLE_SELECTION(
				branch_model
			))
		)));
		g_object_unref(questioned); // we don't need a 2nd reference
		if (target == questioned) {
			model_i = gtk_single_selection_get_selected(GTK_SINGLE_SELECTION(
				branch_model
			));
			pathbar_update_path(
				GTK_SINGLE_SELECTION(branch_model), 0,0, commons
			);
		} else {
			// map has an objective form of the path string.
			// Even though branch_model will have the final destination, it
			// might not yet due to it being under a GtkTreeListModel
			// collapsable.
			model_i = -1;
			depth_i = 0;
			do {
				target = G_OBJECT(map->branch_path[depth_i]->self);
				while (true) {
					model_i++;
					tree_item = GTK_TREE_LIST_ROW(
						g_list_model_get_object(branch_model, model_i)
					);
					questioned = G_OBJECT(
						gtk_tree_list_row_get_item(tree_item)
					);
					g_object_unref(questioned); // we don't need a 2nd reference
					if (target == questioned) {
						break;
					}
					g_object_unref(tree_item);
				};
				gtk_tree_list_row_set_expanded(tree_item, true);
				// may be collapsed
				g_object_unref(tree_item);
				depth_i++;
			} while (depth_i < map->branch_depth);
		}

		gtk_column_view_scroll_to(commons->branches.view,
			model_i, NULL,
			(GTK_LIST_SCROLL_FOCUS | GTK_LIST_SCROLL_SELECT),
			NULL
		);

		if (map->leaf_depth) { // if a leaf
			// the exact same idea as what happened with the branhes
			GListModel* const leaf_model = G_LIST_MODEL(
				gtk_column_view_get_model(commons->leaves.view)
			);
			model_i = -1;
			depth_i = 0;
			do {
				target = G_OBJECT(map->leaf_path[depth_i]->self);
				while (true) {
					model_i++;
					tree_item = GTK_TREE_LIST_ROW(
						g_list_model_get_object(leaf_model, model_i)
					);
					questioned = G_OBJECT(
						gtk_tree_list_row_get_item(tree_item)
					);
					g_object_unref(questioned); // we don't need a 2nd reference
					if (target == questioned) {
						break;
					}
					g_object_unref(tree_item);
				};
				// may be collapsed
				gtk_tree_list_row_set_expanded(tree_item, true);
				g_object_unref(tree_item);
				depth_i++;
			} while (depth_i < map->leaf_depth);

			gtk_column_view_scroll_to(commons->leaves.view,
				model_i, NULL,
				GTK_LIST_SCROLL_FOCUS,
				NULL
			);
		}
	} else {
		GtkWindow* const editor_window = gtk_application_get_active_window(
			commons->yaabe_gtk
		);
		GtkAlertDialog* alert;
		if (map->branch_depth) {
			alert = gtk_alert_dialog_new(
				"\n%s\n not found in:\n %s\n",
				map->not_found,
				map->branch_path[map->branch_depth-1]->name
			);
		} else {
			alert = gtk_alert_dialog_new("bad root");
		}
		gtk_alert_dialog_set_detail(alert, editable_text);
		gtk_alert_dialog_show(alert, editor_window);

		g_object_unref(alert);
	}
	free(map);
}
inline static GtkWidget*
construct_path_bar(
		yaabegtk_commons* const commons
		) {
	GtkWidget* const path_bar = gtk_entry_new();
	commons->pathbar = GTK_EDITABLE(path_bar);

	g_signal_connect_swapped(path_bar, "activate",
		G_CALLBACK(pathbar_sets_branch_selection), commons
	);

	GtkEventController* const escape_reset = gtk_shortcut_controller_new();
	gtk_shortcut_controller_add_shortcut(
		GTK_SHORTCUT_CONTROLLER(escape_reset),
		gtk_shortcut_new(
			gtk_shortcut_trigger_parse_string("Escape"),
			gtk_callback_action_new(pathbar_editable_reset, commons, NULL)
		)
	);
	gtk_widget_add_controller(path_bar, escape_reset);

	return path_bar;
}


static void
leaves_view_deferred_restore_position(
		GtkAdjustment* const adj,
		yaabegtk_commons* const commons
		) {
// restore scroll position if branches have similar leaves
	gtk_adjustment_set_value(adj, commons->previous_scroll_position);

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
		yaabegtk_commons* const commons
		) {
// Signal callback
// Change the leaves pane's model based on the what is selected in brances
	GATUIBranch* const new_selection = GATUI_BRANCH(
		gtk_tree_list_row_get_item(
			gtk_single_selection_get_selected_item(model)
		)
	);
	atui_branch const* const a_branch_new = gatui_branch_get_atui(
		new_selection
	);
	atui_branch const* const a_branch_old = gatui_branch_get_atui(
		commons->previous_selection
	);

	bool const similar_branches = (
		(a_branch_new->leaf_count == a_branch_old->leaf_count)
		&& (0 == strcmp(a_branch_new->origname, a_branch_old->origname))
	);
	if (similar_branches) { // restore scroll if compatible
		GtkAdjustment* const adj = gtk_scrollable_get_vadjustment(
			GTK_SCROLLABLE(commons->leaves.view)
		);
		commons->previous_scroll_position = gtk_adjustment_get_value(adj);
		// we can't immedately set the new position because it takes a while
		// for the set_model to propagate.
		g_signal_connect(adj, "value-changed",
			G_CALLBACK(leaves_view_deferred_restore_position), commons
		);
	}

	gtk_column_view_set_model(
		commons->leaves.view,
		gatui_branch_get_leaves_model(new_selection)
	);
	commons->previous_selection = new_selection;

	g_object_unref(new_selection);
}
void
create_and_set_active_gatui_model(
		yaabegtk_commons* const commons,
		GATUITree* const new_root
		) {
// create and set the main branch model
	GtkSelectionModel* const new_model = gatui_tree_create_trunk_model(
		new_root
	);
	g_object_connect(new_model,
		"signal::selection-changed", G_CALLBACK(select_changes_leaves), commons,
		"signal::selection-changed", G_CALLBACK(pathbar_update_path), commons,
		NULL
	);

	commons->root = new_root;
	GATUIBranch* const trunk = gatui_tree_get_trunk(new_root);
	commons->previous_selection = trunk;

	gtk_column_view_set_model(commons->branches.view, new_model);

	// TODO eject leaves model first-time loader into a notify::model callback
	// in create_branches_pane?
	gtk_column_view_set_model(
		commons->leaves.view,
		gatui_branch_get_leaves_model(trunk)
	);

	if (commons->pathbar_string) {
		free(commons->pathbar_string);
	}
	commons->pathbar_string = gatui_branch_to_path(trunk);
	gtk_editable_set_text(commons->pathbar, commons->pathbar_string);

	g_object_unref(trunk);
	g_object_unref(new_model);
	// TODO move the call of set_editor_titlebar in here?
}


void
set_editor_titlebar(
		yaabegtk_commons* const commons
		) {
// Set the window name to the name of the currently-open bios.
	char const print_format_file[] = "%s (%s)";
	char const print_format_nofile[] = "%s";

	char* filename;
	uint16_t filename_length;
	char const* formatstr;
	if (commons->root) {
		filename = g_file_get_basename(
			gatui_tree_get_bios_file(commons->root)
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

	GtkWindow* const editor_window = gtk_application_get_active_window(
		commons->yaabe_gtk
	);
	gtk_window_set_title(editor_window, window_title);

	free(window_title);
	if (filename_length) {
		g_free(filename);
	}
}


static void
yaabe_app_activate(
		GtkApplication* const gtkapp,
		yaabegtk_commons* const commons
		) {
	construct_menu_bar(commons);

	GtkWidget* const path_bar = construct_path_bar(commons);
	GtkWidget* const tree_divider = construct_tree_panes(commons);
	GtkWidget* const button_box = construct_loadsave_buttons_box(commons);

	GtkBox* const main_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_VERTICAL, 0));
	gtk_box_append(main_box, path_bar);
	gtk_box_append(main_box, tree_divider);
	gtk_box_append(main_box, button_box);

	GtkDropTarget* const dropfile = gtk_drop_target_new(
		G_TYPE_FILE, GDK_ACTION_COPY
	);
	g_signal_connect(dropfile, "drop",
		G_CALLBACK(dropped_file_open_bios), commons
	);

	GtkApplicationWindow* const app_window = GTK_APPLICATION_WINDOW(
		gtk_application_window_new(gtkapp)
	);
	gtk_application_window_set_show_menubar(app_window, true);
	gtk_widget_add_controller(
		GTK_WIDGET(app_window), GTK_EVENT_CONTROLLER(dropfile)
	);

	GtkWindow* const window = GTK_WINDOW(app_window);
	gtk_window_set_default_size(window, 1400,700); // 2:1
	gtk_window_set_child(window, GTK_WIDGET(main_box));

	gtk_widget_grab_focus(tree_divider);
	gtk_widget_grab_focus(GTK_WIDGET(commons->branches.view));

	if (commons->root) {
		create_and_set_active_gatui_model(commons, commons->root);
	}

	set_editor_titlebar(commons);
	gtk_window_present(window);
}
int8_t
yaabe_gtk(
		GATUITree** const root
		) {
	yaabegtk_commons commons = {0};
	commons.root = *root;

	commons.yaabe_gtk = gtk_application_new(NULL, G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(commons.yaabe_gtk, "activate",
		G_CALLBACK(yaabe_app_activate), &commons
	);
	int8_t const status = g_application_run(
		G_APPLICATION(commons.yaabe_gtk), 0,NULL
	);

	*root = commons.root;
	g_object_unref(commons.yaabe_gtk);

	if (commons.pathbar_string) {
		free(commons.pathbar_string);
	}

	return status;
}
