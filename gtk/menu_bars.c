#include "yaabe_gtk_internal.h"

inline static void
filer_error_window(
		yaabegtk_commons const* const commons,
		GError* const ferror,
		char const* const title
		) {
// Simple error popup
	GtkAlertDialog* const alert = gtk_alert_dialog_new("%s", title);
	gtk_alert_dialog_set_detail(alert, ferror->message);
	gtk_alert_dialog_show(
		alert,
		gtk_application_get_active_window(commons->yaabe_gtk)
	);

	g_object_unref(alert);
}

inline static void
yaabegtk_load_enable_save_buttons(
		yaabegtk_commons* const commons
		) {
	gtk_widget_set_sensitive(commons->save_buttons, true);
	gtk_widget_set_sensitive(commons->reload_buttons, true);


	// the main menu bar
	GActionMap* const app_action_map = G_ACTION_MAP(commons->yaabe_gtk);
	GValue enabled = G_VALUE_INIT;
	g_value_init(&enabled, G_TYPE_BOOLEAN);
	g_value_set_boolean(&enabled, true);
	GAction* action;

	action = g_action_map_lookup_action(app_action_map, "save");
	g_object_set_property(G_OBJECT(action), "enabled", &enabled);
	action = g_action_map_lookup_action(app_action_map, "saveas");
	g_object_set_property(G_OBJECT(action), "enabled", &enabled);
	action = g_action_map_lookup_action(app_action_map, "discard");
	g_object_set_property(G_OBJECT(action), "enabled", &enabled);
	action = g_action_map_lookup_action(app_action_map, "reload");
	g_object_set_property(G_OBJECT(action), "enabled", &enabled);
	action = g_action_map_lookup_action(app_action_map, "search");
	g_object_set_property(G_OBJECT(action), "enabled", &enabled);
}
static void
yaabegtk_load_bios(
		yaabegtk_commons* const commons,
		GFile* const biosfile,
		GError** const ferror_out
		) {
// Processes necessary triggers for loading a bios, except final error handling
	GError* ferror = NULL;

	GATUITree* const new_tree = gatui_tree_new_from_gfile(biosfile, &ferror);
	if (ferror) {
		goto ferr;
	}

	if (new_tree) {
		if (commons->root) { // has loaded
			g_object_unref(commons->root);
			char* const old_path = commons->pathbar_string;
			commons->pathbar_string = NULL; // steal it
			create_and_set_active_gatui_model(commons, new_tree);
			yaabe_gtk_scroll_to_path(commons, old_path, NULL);
			free(old_path);
		} else {
			create_and_set_active_gatui_model(commons, new_tree);
			first_load_restore_path(commons);
			yaabegtk_load_enable_save_buttons(commons);
		}

		set_editor_titlebar(commons);
	}

	ferr:
	if (ferror_out) {
		*ferror_out = ferror;
	} else {
		g_error_free(ferror);
	}
	return;
}
static void
filedialog_load_and_set_bios(
		GObject* const gobj_filedialog,
		GAsyncResult* const asyncfile,
		gpointer const commonsptr
		) {
// AsyncReadyCallback for the file dialog in the load button.
	yaabegtk_commons* const commons = commonsptr;
	GtkFileDialog* const filer = GTK_FILE_DIALOG(gobj_filedialog);
	GError* ferror = NULL;

	GFile* const biosfile = gtk_file_dialog_open_finish(
		filer, asyncfile, &ferror
	);
	if (ferror) {
		goto ferr_nomsg;
	}

	yaabegtk_load_bios(commons, biosfile, &ferror);
	g_object_unref(biosfile);
	if (ferror) {
		goto ferr_msg;
	}
	return;

	ferr_msg:
	filer_error_window(commons, ferror, "Load BIOS error");
	ferr_nomsg:
	g_error_free(ferror);
	return;

}
gboolean
dropped_file_open_bios(
		GtkDropTarget* const dropctrl __unused,
		GValue const* const value,
		gdouble const x __unused,
		gdouble const y __unused,
		yaabegtk_commons* const commons
		) {
// Load a bios from a drag-n'-drop
// ???  https://gitlab.gnome.org/GNOME/gtk/-/issues/3755
	GError* ferror = NULL;

	if (G_VALUE_HOLDS(value, G_TYPE_FILE)) {
		GFile* biosfile = g_value_get_object(value);
		yaabegtk_load_bios(commons, biosfile, &ferror);
		if (ferror) {
			filer_error_window(commons, ferror, "Load dropped BIOS error");
			g_error_free(ferror);
			return false;
		}
		return true;
	}
	return false;
}


static void
yaabe_open_bios(
		yaabegtk_commons* const commons
		) {
	GtkFileDialog* const filer = gtk_file_dialog_new();
	GtkWindow* const active_window = gtk_application_get_active_window(
		commons->yaabe_gtk
	);

	GFile* working_dir;
	if (commons->root) { // if commandline file
		working_dir = g_file_get_parent(
			gatui_tree_get_bios_file(commons->root)
		);
	} else {
		working_dir = get_cached_working_dir();
		if (NULL == working_dir) {
			working_dir = g_file_new_for_path(".");
		}
	}

	gtk_file_dialog_set_initial_folder(filer, working_dir);
	g_object_unref(working_dir);

	gtk_file_dialog_open(filer,
		active_window, NULL, filedialog_load_and_set_bios, commons
	);
	g_object_unref(filer);
}
static void
yaabe_save_same_file(
		yaabegtk_commons* const commons
		) {
	GError* ferror = NULL;

	gatui_tree_save(commons->root, &ferror);
	if (ferror) {
		filer_error_window(commons, ferror, "Save BIOS error");
		g_error_free(ferror);
	}
	set_cached_working_dir(
		gatui_tree_get_bios_file(commons->root)
	);
}
static void
filedialog_saveas_bios(
		GObject* const gobj_filedialog,
		GAsyncResult* const asyncfile,
		gpointer const commonsptr
		) {
// AsyncReadyCallback for the file dialog in the Save As button.
	yaabegtk_commons* const commons = commonsptr;

	GtkFileDialog* const filer = GTK_FILE_DIALOG(gobj_filedialog);
	GError* ferror = NULL;

	GFile* const new_biosfile = gtk_file_dialog_save_finish(
		filer, asyncfile, &ferror
	);
	if (ferror) {
		goto ferr_nomsg;
	}

	gatui_tree_saveas(commons->root, new_biosfile, &ferror);
	if (ferror) {
		g_object_unref(new_biosfile);
		goto ferr_msg;
	}

	set_editor_titlebar(commons);
	set_cached_working_dir(new_biosfile);
	return;

	ferr_msg:
	filer_error_window(commons, ferror, "Save BIOS As error");
	ferr_nomsg:
	g_error_free(ferror);
	return;
}
static void
yaabe_saveas_name_bios(
		yaabegtk_commons* const commons
		) {
// Signal callback
	GtkFileDialog* const filer = gtk_file_dialog_new();
	GtkWindow* const active_window = gtk_application_get_active_window(
		commons->yaabe_gtk
	);
	GFile* const current_biosfile = gatui_tree_get_bios_file(commons->root);
	GFile* const working_dir = g_file_get_parent(current_biosfile);
	gtk_file_dialog_set_initial_file(filer, current_biosfile);
	g_object_unref(working_dir);

	gtk_file_dialog_save(filer,
		active_window, NULL, filedialog_saveas_bios, commons
	);
	g_object_unref(filer);
}
static void
yaabe_discard_changes(
		yaabegtk_commons* const commons
		) {
	GError* ferror = NULL;

	GATUITree* const old_tree = commons->root;
	GFile* const biosfile = gatui_tree_get_bios_file(old_tree);
	GATUITree* const new_tree = gatui_tree_new_from_gfile(biosfile, &ferror);
	if (ferror) {
		filer_error_window(commons, ferror, "Reload BIOS error");
		g_error_free(ferror);
		return;
	}

	create_and_set_active_gatui_model(commons, new_tree);
	g_object_unref(old_tree);
}
static void
yaabe_apply_changes(
		yaabegtk_commons* const commons
		) {
	GATUITree* const old_tree = commons->root;
	GATUITree* const new_tree = gatui_tree_copy_core(old_tree);
	assert(new_tree);
	if (NULL == new_tree) {
		return;
	}

	create_and_set_active_gatui_model(commons, new_tree);
	g_object_unref(old_tree);
}


GtkWidget*
construct_loadsave_buttons_box(
		yaabegtk_commons* const commons
		) {
	GtkWidget* const load_button = gtk_button_new_with_label("Load");
	g_signal_connect_swapped(load_button, "clicked",
		G_CALLBACK(yaabe_open_bios), commons
	);


	GtkWidget* const discard_button = gtk_button_new_with_label("Discard");
	gtk_widget_set_tooltip_text(discard_button, "Discard changes and reload");
	g_signal_connect_swapped(discard_button, "clicked",
		G_CALLBACK(yaabe_discard_changes), commons
	);
	GtkWidget* const apply_button = gtk_button_new_with_label("Apply");
	gtk_widget_set_tooltip_text(apply_button,
		"Recrawl bios based on changes"
	);
	g_signal_connect_swapped(apply_button, "clicked",
		G_CALLBACK(yaabe_apply_changes), commons
	);
	GtkWidget* const reload_buttons = gtk_box_new(
		GTK_ORIENTATION_HORIZONTAL, 5
	);
	gtk_box_append(GTK_BOX(reload_buttons), discard_button);
	gtk_box_append(GTK_BOX(reload_buttons), apply_button);



	GtkWidget* const save_button = gtk_button_new_with_label("Save");
	g_signal_connect_swapped(save_button, "clicked",
		G_CALLBACK(yaabe_save_same_file), commons
	);
	GtkWidget* const saveas_button = gtk_button_new_with_label("Save As");
	g_signal_connect_swapped(saveas_button, "clicked",
		G_CALLBACK(yaabe_saveas_name_bios), commons
	);
	GtkWidget* const save_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_append(GTK_BOX(save_buttons), save_button);
	gtk_box_append(GTK_BOX(save_buttons), saveas_button);


	GtkWidget* const cf_button = gtk_button_new_with_label("Function Tables");
	gtk_widget_set_sensitive(cf_button, false);


	GtkWidget* const buttonboxes = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 30);
	gtk_widget_set_margin_top(buttonboxes, 5);
	gtk_widget_set_margin_bottom(buttonboxes, 5);
	gtk_widget_set_margin_start(buttonboxes, 5);
	gtk_widget_set_margin_end(buttonboxes, 5);
	gtk_box_append(GTK_BOX(buttonboxes), load_button);
	gtk_box_append(GTK_BOX(buttonboxes), reload_buttons);
	gtk_box_append(GTK_BOX(buttonboxes), save_buttons);
	gtk_box_append(GTK_BOX(buttonboxes), cf_button);

	commons->reload_buttons = reload_buttons;
	commons->save_buttons = save_buttons;
	if (commons->root == NULL) {
		gtk_widget_set_sensitive(save_buttons, false);
		gtk_widget_set_sensitive(reload_buttons, false);
	}

	return buttonboxes;
}


static void
yaabe_action_load_bios(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const commons_ptr
		) {
	yaabe_open_bios(commons_ptr);
}
static void
yaabe_action_save_bios(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const commons_ptr
		) {
	yaabe_save_same_file(commons_ptr);
}
static void
yaabe_action_saveas_bios(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const commons_ptr
		) {
	yaabe_saveas_name_bios(commons_ptr);
}
static void
yaabe_action_quit(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const commons_ptr
		) {
	yaabegtk_commons const* const commons = commons_ptr;
	g_application_quit(G_APPLICATION(commons->yaabe_gtk));
	assert(0);
	exit(0);
	/*
	g_application_quit doesn't correctly unref stuff so just exit.
	A proper solution would probably involve closing all open ApplicationWindows
	but that is a lot of work for janitorial work for an exit
	*/
}
static void
yaabe_action_discard_changes(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const commons_ptr
		) {
	yaabe_discard_changes(commons_ptr);
}
static void
yaabe_action_apply_changes(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const commons_ptr
		) {
	yaabe_apply_changes(commons_ptr);
}

static void
yaabe_action_search(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const commons_ptr
		) {
	yaabegtk_commons const* const commons = commons_ptr;
	if (commons->search.window) {
		gtk_window_set_focus(commons->search.window, commons->search.entry);
		gtk_window_present(commons->search.window);
	} else {
		create_search_window(commons_ptr);
	}
}

static void
yaabe_action_about(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const commons_ptr
		) {
	create_about_window(commons_ptr);
}

void
construct_menu_bar(
		yaabegtk_commons* const commons
		) {
	GtkApplication* const gtkapp = commons->yaabe_gtk;
	// construct and attach menu model; UI portion
	GMenu* const file_menu = g_menu_new();
	g_menu_append(file_menu, "Load", "app.load");
	g_menu_append(file_menu, "Save", "app.save");
	g_menu_append(file_menu, "Save As", "app.saveas");
	g_menu_append(file_menu, "Quit", "app.quit");

	GMenu* const edit_menu = g_menu_new();
	g_menu_append(edit_menu, "Discard Changes", "app.discard");
	g_menu_append(edit_menu, "Apply Changes", "app.reload");

	GMenu* const tools_menu = g_menu_new();
	g_menu_append(tools_menu, "Search", "app.search");

	GMenu* const help_menu = g_menu_new();
	g_menu_append(help_menu, "About", "app.about");

	//GMenu* const magic_menu = g_menu_new();
	//g_menu_append(magic_menu, "Insert UEFI GOP", "app.uefi_gop");

	GMenu* const main_menu = g_menu_new();
	g_menu_append_submenu(main_menu, "File", G_MENU_MODEL(file_menu));
	g_menu_append_submenu(main_menu, "Edit", G_MENU_MODEL(edit_menu));
	g_menu_append_submenu(main_menu, "Tools", G_MENU_MODEL(tools_menu));
	g_menu_append_submenu(main_menu, "Help", G_MENU_MODEL(help_menu));
	//g_menu_append_submenu(main_menu, "Magic", G_MENU_MODEL(magic_menu));
	gtk_application_set_menubar(gtkapp, G_MENU_MODEL(main_menu));


	// keybind accelerators
	const char* accel[2] = {}; // NULL terminated list
	accel[0] = "<ctrl>q";
	gtk_application_set_accels_for_action(gtkapp, "app.quit", accel);
	accel[0] = "<ctrl>o";
	gtk_application_set_accels_for_action(gtkapp, "app.load", accel);
	accel[0] = "<ctrl>s";
	gtk_application_set_accels_for_action(gtkapp, "app.save", accel);
	accel[0] = "<shift><ctrl>s";
	gtk_application_set_accels_for_action(gtkapp, "app.saveas", accel);

	accel[0] = "<ctrl>d";
	gtk_application_set_accels_for_action(gtkapp, "app.discard", accel);
	accel[0] = "<ctrl>r";
	gtk_application_set_accels_for_action(gtkapp, "app.reload", accel);

	accel[0] = "<ctrl>f";
	gtk_application_set_accels_for_action(gtkapp, "app.search", accel);


	// construct the actions of the menus; function portion
	GActionMap* const app_action_map = G_ACTION_MAP(gtkapp);
	GActionEntry const actions[] = {
		{.name = "load",    .activate = yaabe_action_load_bios},
		{.name = "save",    .activate = yaabe_action_save_bios},
		{.name = "saveas",  .activate = yaabe_action_saveas_bios},
		{.name = "quit",    .activate = yaabe_action_quit},

		{.name = "discard", .activate = yaabe_action_discard_changes},
		{.name = "reload",  .activate = yaabe_action_apply_changes},

		{.name = "search",  .activate = yaabe_action_search},

		{.name = "about",  .activate = yaabe_action_about},
	};
	g_action_map_add_action_entries(app_action_map,
		actions, lengthof(actions),
		commons
	);
	if (NULL == commons->root) {
		// disable some menu entries if no bios is loaded
		GAction* action;
		GValue enabled = G_VALUE_INIT;
		g_value_init(&enabled, G_TYPE_BOOLEAN);
		g_value_set_boolean(&enabled, false);

		action = g_action_map_lookup_action(app_action_map, "save");
		g_object_set_property(G_OBJECT(action), "enabled", &enabled);
		action = g_action_map_lookup_action(app_action_map, "saveas");
		g_object_set_property(G_OBJECT(action), "enabled", &enabled);
		action = g_action_map_lookup_action(app_action_map, "discard");
		g_object_set_property(G_OBJECT(action), "enabled", &enabled);
		action = g_action_map_lookup_action(app_action_map, "reload");
		g_object_set_property(G_OBJECT(action), "enabled", &enabled);
		action = g_action_map_lookup_action(app_action_map, "search");
		g_object_set_property(G_OBJECT(action), "enabled", &enabled);
	}
}
