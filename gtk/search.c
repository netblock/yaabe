#include "yaabe_gtk_internal.h"

static void
execute_regex_search(
		GtkEntry* const search_entry,
		yaabegtk_commons* const commons
		) {
	char const* const regex_text = gtk_editable_get_text(GTK_EDITABLE(
		search_entry
	));
	GError* err = NULL;
	GRegex* const regex = g_regex_new(
		regex_text, G_REGEX_OPTIMIZE, G_REGEX_MATCH_DEFAULT, &err
	);
	if (err) {
		generic_error_popup("regex error", err->message, commons->yaabe_gtk);
		g_error_free(err);
	} else {
		GtkSelectionModel* const results_model = gatui_tree_regex_search(
			commons->root, regex, &(commons->search.flags)
		);
		gtk_column_view_set_model(commons->search.pane.view, results_model);
		g_object_unref(results_model);
		g_regex_unref(regex);
	}
}

inline static GtkWidget*
create_search_entry(
		yaabegtk_commons* const commons
		) {
	GtkWidget* const search_entry = gtk_entry_new();
	commons->search.entry = search_entry;
	gtk_widget_set_tooltip_text(
		search_entry,
		"PCRE2 Regex\n"
		"Prefix with (?i) for case insensitive"
	);

	g_signal_connect(search_entry, "activate",
		G_CALLBACK(execute_regex_search), commons
	);

	return search_entry;
}

static void
search_options_set_domain(
		GtkDropDown* const domain_select,
		GParamSpec* const pspec __unused,
		yaabegtk_commons* const commons
		) {
	commons->search.flags.domain = gtk_drop_down_get_selected(domain_select);
	switch (commons->search.flags.domain) {
		case GATUI_SEARCH_NAMES:
			gtk_widget_set_sensitive(commons->search.branches_checkbox, true);
			break;
		case GATUI_SEARCH_VALUES:
			gtk_widget_set_sensitive(commons->search.branches_checkbox, false);
			break;
		default: assert(0);
	}
}
static void
search_options_toggle_check(
		bool* const store
		) {
	*store = ! *store;
}
inline static GtkWidget*
create_search_options(
		yaabegtk_commons* const commons
		) {
	struct gatui_search_flags* const flags = &(commons->search.flags);

	GtkDropDown* const domain = GTK_DROP_DOWN(gtk_drop_down_new_from_strings(
		(char const* const[]) {
			[GATUI_SEARCH_NAMES] = "Names",
			[GATUI_SEARCH_VALUES] = "Values",
			NULL
		}
	));
	gtk_drop_down_set_show_arrow(domain, true);
	g_signal_connect(domain, "notify::selected",
		G_CALLBACK(search_options_set_domain), commons
	);
	gtk_drop_down_set_selected(domain, flags->domain);

	GtkWidget* const leaves = gtk_check_button_new_with_label("Search leaves");
	gtk_check_button_set_active(GTK_CHECK_BUTTON(leaves), flags->leaves);
	g_signal_connect_swapped(leaves, "toggled",
		G_CALLBACK(search_options_toggle_check), &(flags->leaves)
	);

	GtkWidget* const branches = gtk_check_button_new_with_label(
		"Search branches"
	);
	gtk_check_button_set_active(GTK_CHECK_BUTTON(branches), flags->branches);
	g_signal_connect_swapped(branches, "toggled",
		G_CALLBACK(search_options_toggle_check), &(flags->branches)
	);
	commons->search.branches_checkbox = branches;
	gtk_widget_set_sensitive(branches, GATUI_SEARCH_VALUES != flags->domain);

	GtkGrid* const search_options = GTK_GRID(gtk_grid_new());
	gtk_grid_attach(search_options, GTK_WIDGET(domain), 0,3, 1,2);
	gtk_grid_attach(search_options, leaves, 2,1, 1,3);
	gtk_grid_attach(search_options, branches, 2,4, 1,3);

	return GTK_WIDGET(search_options);
}



struct scroll_to_in_main_window_pack {
	yaabegtk_commons* commons;
	GtkColumnViewCell* column_cell;
};
static void
scroll_to_in_main_window_button(
		struct scroll_to_in_main_window_pack* const pack
		) {
	yaabe_gtk_scroll_to_object(
		pack->commons,
		gatui_regex_node_peek(
			gtk_column_view_cell_get_item(pack->column_cell)
		)->tree_node
	);
}
static void
goto_column_setup(
		yaabegtk_commons* const commons, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
	struct scroll_to_in_main_window_pack* const pack = cralloc(
		sizeof(struct scroll_to_in_main_window_pack)
	);
	pack->commons = commons;
	pack->column_cell = column_cell;

	GtkWidget* const goto_button = gtk_button_new_with_label("Go To");
	g_signal_connect_data(goto_button, "clicked",
		G_CALLBACK(scroll_to_in_main_window_button), pack,
		free_closure, G_CONNECT_SWAPPED
	);
	gtk_column_view_cell_set_child(column_cell, goto_button);
}

static void
node_type_column_bind(
		void const* const _null __unused, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
	struct atui_regex_node const* regex = gatui_regex_node_peek(
		gtk_column_view_cell_get_item(column_cell)
	);
	assert(regex);
	GtkInscription* const label = GTK_INSCRIPTION(
		gtk_column_view_cell_get_child(column_cell)
	);
	char const* const branchleaf = (char const* const[]) {
		"Branch", "Leaf"
	} [GATUI_IS_LEAF(regex->tree_node)];
	gtk_inscription_set_text(label, branchleaf);
	gtk_inscription_set_nat_chars(label, sizeof("Branch"));
}

static void
highlight_name_column_bind(
		void const* const _null __unused, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
	struct atui_regex_node const* regex = gatui_regex_node_peek(
		gtk_column_view_cell_get_item(column_cell)
	);
	assert(regex);
	char const* const name = gatui_node_get_name(regex->tree_node);

	GtkInscription* const label = GTK_INSCRIPTION(
		gtk_column_view_cell_get_child(column_cell)
	);

	if (GATUI_SEARCH_NAMES == regex->flags.domain) {
		gtk_inscription_set_markup(label, regex->markup_text);
	} else {
		gtk_inscription_set_text(label, name);
	}
	gtk_inscription_set_nat_chars(label, strlen(name) +2);

}
static void
highlight_value_column_bind(
		yaabegtk_commons const* const commons, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
	struct atui_regex_node const* regex = gatui_regex_node_peek(
		gtk_column_view_cell_get_item(column_cell)
	);
	assert(regex);
	GtkInscription* const label = GTK_INSCRIPTION(
		gtk_column_view_cell_get_child(column_cell)
	);

	size_t string_length = 0;
	if (GATUI_IS_LEAF(regex->tree_node)) {
		if (GATUI_SEARCH_VALUES == regex->flags.domain) {
			gtk_inscription_set_markup(label, regex->markup_text);
			string_length = strlen(regex->text);
		} else {
			GATUILeaf* const leaf = GATUI_LEAF(regex->tree_node);
			char* text = NULL;
			if (gatui_leaf_has_textable_value(leaf)) {
				text = gatui_leaf_value_to_text(leaf, commons->big_endian);
				string_length = strlen(text);
			}
			gtk_inscription_set_text(label, text);
			free(text);
		}
	} else {
		gtk_inscription_set_text(label, NULL);
	}
	gtk_inscription_set_nat_chars(label, string_length);
}

static void
regex_offset_column_bind(
		offset_sprintf const endian_sprintf, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
	struct atui_regex_node const* regex = gatui_regex_node_peek(
		gtk_column_view_cell_get_item(column_cell)
	);
	assert(regex);
	GtkInscription* const label = GTK_INSCRIPTION(
		gtk_column_view_cell_get_child(column_cell)
	);

	size_t end;
	size_t start;
	offset_buffer buffer = {[0]='\0'};
	if (gatui_node_get_region_bounds(regex->tree_node, &end, &start)) {
		endian_sprintf(buffer, BYTE_ARRAY_FORMAT, end, start);
	}

	assert(strlen(buffer) < sizeof(buffer));
	gtk_inscription_set_text(label, buffer);
}

inline static GtkWidget*
create_results_view(
		yaabegtk_commons* const commons
		) {
	// type result_text goto
	GtkColumnView* const search_view = GTK_COLUMN_VIEW(
		gtk_column_view_new(NULL)
	);
	commons->search.pane.view = search_view;
	gtk_column_view_set_reorderable(search_view, true);
	gtk_column_view_set_show_row_separators(search_view, true);

	// Create and attach columns
	GtkListItemFactory* factory;
	GtkColumnViewColumn* column;

	factory = g_object_connect(gtk_signal_list_item_factory_new(),
		//"swapped-signal::setup", G_CALLBACK(search_row_setup), NULL,
		"swapped-signal::bind", G_CALLBACK(search_rightclick_row_bind), commons,
		NULL
	);
	gtk_column_view_set_row_factory(search_view, factory);

	factory = g_object_connect(gtk_signal_list_item_factory_new(),
		"swapped-signal::setup", G_CALLBACK(goto_column_setup), commons,
		NULL
	);
	column = gtk_column_view_column_new("Go To", factory);
	gtk_column_view_append_column(search_view, column);
	g_object_unref(column);

	factory = g_object_connect(gtk_signal_list_item_factory_new(),
		"swapped-signal::setup", G_CALLBACK(label_column_setup), NULL,
		"swapped-signal::bind", G_CALLBACK(node_type_column_bind), NULL,
		NULL
	);
	column = gtk_column_view_column_new("Type", factory);
	gtk_column_view_append_column(search_view, column);
	g_object_unref(column);

	factory = g_object_connect(gtk_signal_list_item_factory_new(),
		"swapped-signal::setup", G_CALLBACK(label_column_setup), NULL,
		"swapped-signal::bind", G_CALLBACK(highlight_name_column_bind), NULL,
		NULL
	);
	column = gtk_column_view_column_new("Name", factory);
	gtk_column_view_column_set_resizable(column, true);
	gtk_column_view_append_column(search_view, column);
	g_object_unref(column);

	factory = g_object_connect(gtk_signal_list_item_factory_new(),
		"swapped-signal::setup", G_CALLBACK(label_column_setup), NULL,
		"swapped-signal::bind", G_CALLBACK(highlight_value_column_bind),commons,
		NULL
	);
	column = gtk_column_view_column_new("Value", factory);
	gtk_column_view_column_set_resizable(column, true);
	gtk_column_view_column_set_expand(column, true);
	gtk_column_view_append_column(search_view, column);
	g_object_unref(column);


	factory = g_object_connect(gtk_signal_list_item_factory_new(),
		"swapped-signal::setup", G_CALLBACK(label_column_setup), NULL,
		"swapped-signal::bind", G_CALLBACK(regex_offset_column_bind),
			commons->endian_sprintf,
		NULL
	);
	column = gtk_column_view_column_new("BIOS Offset", factory);
	gtk_column_view_append_column(search_view, column);
	g_object_unref(column);

	GtkWidget* const scrolled_search_view = gtk_scrolled_window_new();
	gtk_scrolled_window_set_child(
		GTK_SCROLLED_WINDOW(scrolled_search_view), GTK_WIDGET(search_view)
	);
	gtk_widget_set_vexpand(scrolled_search_view, true);

	create_search_rightclick_menu(commons);

	return scrolled_search_view;
}

static void
search_window_cleanup(
		yaabegtk_commons* const commons
		) {
	commons->search.window = NULL;
}

void
create_search_window(
		yaabegtk_commons* const commons
		) {
	// TODO:
	// right-click: copy path; data?
	// static name/value

	GtkWidget* const search_entry = create_search_entry(commons);
	GtkWidget* const search_options = create_search_options(commons);
	GtkWidget* const search_results = create_results_view(commons);

	GtkBox* const main_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_VERTICAL, 0));
	gtk_box_append(main_box, search_entry);
	gtk_box_append(main_box, search_options);
	gtk_box_append(main_box, search_results);

	GtkWindow* const search_window = GTK_WINDOW(gtk_application_window_new(
		commons->yaabe_gtk // application window allows us to inherit keybinds
	));

	commons->search.window = search_window;
	g_signal_connect_swapped(GTK_WIDGET(search_window), "destroy",
		G_CALLBACK(search_window_cleanup), commons
	);
	gtk_window_set_default_size(search_window, 800,700);
	gtk_window_set_title(search_window, "Regex Search");
	gtk_window_set_destroy_with_parent(search_window, true);
	gtk_window_set_transient_for(search_window, commons->yaabe_primary);
	gtk_window_set_child(search_window, GTK_WIDGET(main_box));
	gtk_window_present(search_window);
}
