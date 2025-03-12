#include "yaabe_gtk_internal.h"
#include "atomtree.h"

static void
label_column_setup(
		void const* const _null __unused, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
//TODO use https://docs.gtk.org/gtk4/class.Inscription.html
	GtkWidget* const label = gtk_label_new(NULL);
	gtk_label_set_xalign(GTK_LABEL(label), 0);
	gtk_column_view_cell_set_child(column_cell, label);
}
static void
tree_label_column_setup(
		void const* const _null __unused, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
// setup to spawn a UI skeleton
	GtkWidget* const label = gtk_label_new(NULL);
	gtk_label_set_xalign(GTK_LABEL(label), 0);

	GtkWidget* const expander = gtk_tree_expander_new();
	gtk_tree_expander_set_indent_for_icon(GTK_TREE_EXPANDER(expander), true);
	gtk_tree_expander_set_child(GTK_TREE_EXPANDER(expander), label);
	gtk_column_view_cell_set_child(column_cell, expander);
}




static void
branch_name_column_bind(
		void const* const _null __unused, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
// bind data to the UI skeleton
	GtkTreeListRow* const tree_row = gtk_column_view_cell_get_item(column_cell);
	GATUIBranch* const g_branch = gtk_tree_list_row_get_item(tree_row);
	atui_branch const* const a_branch = gatui_branch_get_atui(g_branch);


	/* TODO
	This should be tucked away in the model creation, but for some reason 
	GtkColumnView (or deeper) makes GtkTreeListRow's lose their notify signals,
	or makes them unreliable. See gatui_tree_create_trunk_model for more info.
	*/
	gulong const handler_id = g_signal_handler_find(tree_row,
		G_SIGNAL_MATCH_FUNC,    0,0,NULL,
		branches_track_expand_state,  NULL
	);
	if (0 == handler_id) { // usually passes
		g_signal_connect(tree_row, "notify::expanded",
			G_CALLBACK(branches_track_expand_state), g_branch
		);
	}

	GtkTreeExpander* const expander = GTK_TREE_EXPANDER(
		gtk_column_view_cell_get_child(column_cell)
	);
	gtk_tree_expander_set_list_row(expander, tree_row);

	GtkWidget* const label = gtk_tree_expander_get_child(expander);
	gtk_label_set_text(GTK_LABEL(label), a_branch->name);
	uint8_t const current_lang = LANG_ENGLISH;
	gtk_widget_set_tooltip_text(label, a_branch->description[current_lang]);

	g_object_unref(g_branch);
}
static void
branch_offset_column_bind(
		yaabegtk_commons* const commons,
		GtkColumnViewCell* const column_cell
		) {
// bind
	GtkWidget* const label = gtk_column_view_cell_get_child(column_cell);

	GtkTreeListRow* const tree_row = gtk_column_view_cell_get_item(column_cell);
	GATUIBranch* const g_branch = gtk_tree_list_row_get_item(tree_row);
	atui_branch const* const a_branch = gatui_branch_get_atui(g_branch);

	struct atom_tree const* const a_root = gatui_tree_get_atom_tree(
		commons->root
	);

	char buffer[sizeof("[123456 - 123456]")];
	if (a_branch->table_size) {
		uint32_t const start = a_branch->table_start - a_root->bios;
		uint32_t const end = (start + a_branch->table_size -1);
		sprintf(buffer, "[%06X - %06X]", start, end);
	} else {
		buffer[0] = '\0';
	}
	assert(strlen(buffer) < sizeof(buffer));
	gtk_label_set_text(GTK_LABEL(label), buffer);
	g_object_unref(g_branch);
}
inline static GtkWidget*
create_branches_pane(
		yaabegtk_commons* const commons
		) {
	// Columnview abstract
	GtkColumnView* const branches_view = GTK_COLUMN_VIEW(
		gtk_column_view_new(NULL)
	);
	gtk_column_view_set_reorderable(branches_view, true);
	//gtk_column_view_set_show_row_separators(branches_view, true);
	gtk_column_view_set_show_column_separators(branches_view, true);
	commons->branches.view = branches_view;

	// Create and attach columns
	GtkListItemFactory* factory;
	GtkColumnViewColumn* column;

	factory = g_object_connect(gtk_signal_list_item_factory_new(),
		"swapped-signal::bind",G_CALLBACK(branches_rightclick_row_bind),commons,
		NULL
	);
	gtk_column_view_set_row_factory(branches_view, factory);

	factory = g_object_connect(gtk_signal_list_item_factory_new(),
		"swapped-signal::setup", G_CALLBACK(tree_label_column_setup), NULL,
		"swapped-signal::bind", G_CALLBACK(branch_name_column_bind), NULL,
		NULL
	);
	column = gtk_column_view_column_new("Table", factory);
	gtk_column_view_column_set_resizable(column, true);
	gtk_column_view_column_set_expand(column, true);
	gtk_column_view_append_column(branches_view, column);
	g_object_unref(column);

	factory = g_object_connect(gtk_signal_list_item_factory_new(),
		"swapped-signal::setup", G_CALLBACK(label_column_setup), NULL,
		"swapped-signal::bind", G_CALLBACK(branch_offset_column_bind), commons,
		NULL
	);
	column = gtk_column_view_column_new("BIOS Offset", factory);
	gtk_column_view_column_set_resizable(column, true);
	gtk_column_view_append_column(branches_view, column);
	g_object_unref(column);


	GtkWidget* const scrolledlist = gtk_scrolled_window_new();
	gtk_scrolled_window_set_child(
		GTK_SCROLLED_WINDOW(scrolledlist), GTK_WIDGET(branches_view)
	);

	create_branches_rightclick_menu(commons);

	return scrolledlist;
}




static void
leaves_name_column_bind(
		void const* const _null __unused, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
// bind data to the UI skeleton
	GtkTreeListRow* const tree_row = gtk_column_view_cell_get_item(column_cell);
	GATUILeaf* const g_leaf = gtk_tree_list_row_get_item(tree_row);
	atui_leaf const* const a_leaf = gatui_leaf_get_atui(g_leaf);
	g_object_unref(g_leaf);

	GtkTreeExpander* const expander = GTK_TREE_EXPANDER(
		gtk_column_view_cell_get_child(column_cell)
	);
	gtk_tree_expander_set_list_row(expander, tree_row);

	GtkWidget* const label = gtk_tree_expander_get_child(expander);
	gtk_label_set_text(GTK_LABEL(label), a_leaf->name);
	uint8_t const current_lang = LANG_ENGLISH;
	gtk_widget_set_tooltip_text(label, a_leaf->description[current_lang]);
}

static void
leaf_sets_editable(
	GATUILeaf* const g_leaf,
	GtkEditable* const editable
	) {
	char* const text = gatui_leaf_value_to_text(g_leaf);
	if (text) {
		gtk_editable_set_text(editable, text);
		free(text);
	}
}
static void
leaves_editable_stray_reset(
		GtkColumnViewCell* const column_cell
		) {
// If the value wasn't applied with enter, sync the text back to the actual
// data when keyboard leaves the textbox
	GtkEditable* const editable = GTK_EDITABLE(
		gtk_stack_get_child_by_name(
			GTK_STACK(gtk_column_view_cell_get_child(column_cell)), "text"
		)
	); // enum and text share same EntryBuffer

	GATUILeaf* const g_leaf = gtk_tree_list_row_get_item(
		gtk_column_view_cell_get_item(column_cell)
	);
	leaf_sets_editable(g_leaf, editable);
	g_object_unref(g_leaf);
}
static void
editable_sets_leaf(
		GtkEditable* const editable,
		GtkColumnViewCell* const column_cell
		) {
// Only way to apply the value is to hit enter
	GATUILeaf* const g_leaf = gtk_tree_list_row_get_item(
		gtk_column_view_cell_get_item(column_cell)
	);
	gatui_leaf_set_value_from_text(
		g_leaf,
		gtk_editable_get_text(editable)
	);
	g_object_unref(g_leaf);
}

static void
enum_name_column_bind(
		GtkColumnViewCell* const leaves_column_cell __unused,
		GtkColumnViewCell* const enum_column_cell
		) {
// bind
	GtkLabel* const label = GTK_LABEL(gtk_column_view_cell_get_child(
		enum_column_cell
	));
	struct atui_enum_entry const* const enum_entry = g_object_get_data(
		gtk_column_view_cell_get_item(enum_column_cell),
		"enum"
	); // no need to unref from list_item_get_item

	gtk_label_set_text(label, enum_entry->name);
	uint8_t const current_lang = LANG_ENGLISH;
	gtk_widget_set_tooltip_text(
		GTK_WIDGET(label), enum_entry->description[current_lang]
	);
}
static void
enum_val_column_bind(
		GtkColumnViewCell* const leaves_column_cell,
		GtkColumnViewCell* const enum_column_cell
		) {
// bind
	GtkLabel* const label = GTK_LABEL(gtk_column_view_cell_get_child(
		enum_column_cell
	));
	struct atui_enum_entry const* const enum_entry = g_object_get_data(
		gtk_column_view_cell_get_item(enum_column_cell),
		"enum"
	); // no need to unref from list_item_get_item

	GATUILeaf* const g_leaf = gtk_tree_list_row_get_item(
		gtk_column_view_cell_get_item(leaves_column_cell)
	);

	char* const text = gatui_leaf_enum_val_to_text(g_leaf, enum_entry);
	gtk_label_set_text(label, text);
	free(text);
	g_object_unref(g_leaf);

	uint8_t const current_lang = LANG_ENGLISH;
	gtk_widget_set_tooltip_text(
		GTK_WIDGET(label), enum_entry->description[current_lang]
	);
}
static void
enum_list_sets_leaf(
		GtkColumnView* const enum_list,
		guint const paosition __unused,
		GtkColumnViewCell* const leaves_column_cell
		) {
	struct atui_enum_entry const* const enum_entry = g_object_get_data(
		gtk_single_selection_get_selected_item(
			GTK_SINGLE_SELECTION(gtk_column_view_get_model(enum_list))
		), // no need to unref from gtk_single_selection_get_selected_item
		"enum"
	);

	GATUILeaf* const g_leaf = gtk_tree_list_row_get_item(
		gtk_column_view_cell_get_item(leaves_column_cell)
	);

	bool const has_set __unused = gatui_leaf_enum_entry_sets_value(
		g_leaf, enum_entry
	);
	assert(has_set);

	g_object_unref(g_leaf);
}
static void
enummenu_sets_selection(
		GtkWidget* const enum_list,
		GtkColumnViewCell* const leaves_column_cell
		) {
	GtkSingleSelection* const enum_model = GTK_SINGLE_SELECTION(
		gtk_column_view_get_model(GTK_COLUMN_VIEW(enum_list))
	);

	GATUILeaf* const g_leaf = gtk_tree_list_row_get_item(
		gtk_column_view_cell_get_item(leaves_column_cell)
	);
	int16_t index = gatui_leaf_enum_entry_get_possible_index(g_leaf);
	if (-1 < index) {
		gtk_single_selection_set_selected(enum_model, index);
	} else {
		gtk_single_selection_set_selected(
			enum_model, GTK_INVALID_LIST_POSITION
		);
	}
	g_object_unref(g_leaf);
}
inline static GtkWidget*
construct_enum_columnview(
		GtkColumnViewCell* const leaves_column_cell
		) {
	GtkColumnView* const enum_list = GTK_COLUMN_VIEW(gtk_column_view_new(NULL));
	GtkListItemFactory* factory;
	GtkColumnViewColumn* column;

	factory = g_object_connect(gtk_signal_list_item_factory_new(),
		"swapped-signal::setup", G_CALLBACK(label_column_setup), NULL,
		"swapped-signal::bind", G_CALLBACK(enum_name_column_bind),
			leaves_column_cell,
		NULL
	);
	column = gtk_column_view_column_new("name", factory);
	gtk_column_view_append_column(enum_list, column);
	g_object_unref(column);

	factory = g_object_connect(gtk_signal_list_item_factory_new(),
		"swapped-signal::setup", G_CALLBACK(label_column_setup), NULL,
		"swapped-signal::bind", G_CALLBACK(enum_val_column_bind),
			leaves_column_cell,
		NULL
	);
	column = gtk_column_view_column_new("value", factory);
	gtk_column_view_append_column(enum_list, column);
	g_object_unref(column);

	return GTK_WIDGET(enum_list);
}
inline static GtkWidget*
construct_enum_dropdown(
		GtkEntryBuffer* const entry_buffer,
		GtkColumnViewCell* const leaves_column_cell
		) {
	GtkEditable* const enumentry = GTK_EDITABLE(gtk_entry_new_with_buffer(
		entry_buffer
	));
	g_signal_connect(enumentry, "activate",
		G_CALLBACK(editable_sets_leaf), leaves_column_cell
	);
	gtk_widget_set_hexpand(GTK_WIDGET(enumentry), true);

	GtkWidget* const enum_list = construct_enum_columnview(leaves_column_cell);

	// huge menus too big for the display vertical fails to spawn; so scrolled
	// window
	GtkScrolledWindow* const enum_scroll = GTK_SCROLLED_WINDOW(
		gtk_scrolled_window_new()
	);
	gtk_scrolled_window_set_propagate_natural_height(enum_scroll, true);
	gtk_scrolled_window_set_propagate_natural_width(enum_scroll, true);
	gtk_scrolled_window_set_child(enum_scroll, enum_list);


	GtkPopover* const popover = GTK_POPOVER(gtk_popover_new());
	gtk_popover_set_has_arrow(popover, false);
	gtk_popover_set_child(popover, GTK_WIDGET(enum_scroll));

	g_object_connect(enum_list,
		"signal::map", G_CALLBACK(enummenu_sets_selection), leaves_column_cell,
		"signal::activate", G_CALLBACK(enum_list_sets_leaf), leaves_column_cell,
		"swapped-signal::activate", G_CALLBACK(gtk_popover_popdown), popover,
		NULL
	);

	GtkMenuButton* const enummenu = GTK_MENU_BUTTON(gtk_menu_button_new());
	gtk_menu_button_set_direction(enummenu, GTK_ARROW_RIGHT);
	gtk_menu_button_set_popover(enummenu, GTK_WIDGET(popover));

	GtkWidget* const enumdropdown = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_append(GTK_BOX(enumdropdown), GTK_WIDGET(enummenu));
	gtk_box_append(GTK_BOX(enumdropdown), GTK_WIDGET(enumentry));
	return enumdropdown;
}
static void
leaves_val_column_setup(
		void const* const _null __unused, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
// setup
	GtkStack* const widget_bag = GTK_STACK(gtk_stack_new());
	gtk_column_view_cell_set_child(column_cell, GTK_WIDGET(widget_bag));
	GtkEventController* const focus_sense = gtk_event_controller_focus_new();
	g_signal_connect_swapped(focus_sense, "leave",
		G_CALLBACK(leaves_editable_stray_reset), column_cell
	);
	gtk_widget_add_controller(GTK_WIDGET(widget_bag), focus_sense);
	// widget takes ownership of the controller, no need to unref.

	GtkEntryBuffer* const entry_buffer = gtk_entry_buffer_new(NULL,0);

	// numbers, strings
	//sub_widget = gtk_text_new();
	GtkWidget* const regular = gtk_entry_new_with_buffer(entry_buffer);
	gtk_stack_add_named(widget_bag, regular, "text");
	g_signal_connect(GTK_EDITABLE(regular), "activate",
		G_CALLBACK(editable_sets_leaf), column_cell
	);

	// enums
	GtkWidget* const enumdropdown = construct_enum_dropdown(
		entry_buffer, column_cell
	);
	gtk_stack_add_named(widget_bag, enumdropdown, "enum");

	g_object_unref(entry_buffer);
}
static void
leaves_val_column_bind(
		void const* const _null __unused, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
// bind
	GATUILeaf* const g_leaf = gtk_tree_list_row_get_item(
		gtk_column_view_cell_get_item(column_cell)
	);
	GtkStack* const widget_bag = GTK_STACK(
		gtk_column_view_cell_get_child(column_cell)
	);

	struct atui_type const type = gatui_leaf_get_atui_type(g_leaf);
	if (type.radix || type.fancy == ATUI_STRING || type.fancy == ATUI_ARRAY) {

		gtk_widget_set_visible(GTK_WIDGET(widget_bag), true);
		GtkWidget* editable;
		if (type.has_enum) {
			gtk_stack_set_visible_child_name(widget_bag, "enum");
			GtkWidget* const enumbox = gtk_stack_get_visible_child(widget_bag);
			GtkColumnView* const enum_list = GTK_COLUMN_VIEW(
				gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(
					gtk_popover_get_child(
						gtk_menu_button_get_popover(GTK_MENU_BUTTON(
							gtk_widget_get_first_child(enumbox)
						))
					)
				))
			);
			GtkSelectionModel* const enum_model = (
				gatui_leaf_get_enum_menu_selection_model(g_leaf)
			);

			gtk_column_view_set_model(enum_list, enum_model);
			editable = gtk_widget_get_last_child(enumbox);
		} else {
			gtk_stack_set_visible_child_name(widget_bag, "text");
			editable = gtk_stack_get_visible_child(widget_bag);
		}

		leaf_sets_editable(g_leaf, GTK_EDITABLE(editable));
		g_signal_connect(g_leaf, "value-changed",
			G_CALLBACK(leaf_sets_editable), GTK_EDITABLE(editable)
		);
	} else {
		gtk_widget_set_visible(GTK_WIDGET(widget_bag), false);
	}
	g_object_unref(g_leaf);
}
static void
leaves_val_column_unbind(
		void const* const _null __unused, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
	GATUILeaf* const g_leaf = gtk_tree_list_row_get_item(
		gtk_column_view_cell_get_item(column_cell)
	);
	g_signal_handlers_disconnect_matched(
		g_leaf,  G_SIGNAL_MATCH_FUNC,
		0,0, NULL,   G_CALLBACK(leaf_sets_editable),   NULL

	);
	g_object_unref(g_leaf);
}
static void
leaves_offset_column_bind(
		yaabegtk_commons* const commons,
		GtkColumnViewCell* const column_cell
		) {
// bind data to the UI skeleton
	GtkWidget* const label = gtk_column_view_cell_get_child(column_cell);

	GATUILeaf* const g_leaf = gtk_tree_list_row_get_item(
		gtk_column_view_cell_get_item(column_cell)
	);
	atui_leaf const* const a_leaf = gatui_leaf_get_atui(g_leaf);

	char buffer[sizeof("[123456 - 123456]")];
	if (a_leaf->type.fancy == _ATUI_BITCHILD) {
		sprintf(buffer, "[%u:%u]",
			a_leaf->bitfield_hi, a_leaf->bitfield_lo
		);
	} else if (a_leaf->num_bytes) {
		struct atom_tree const* const a_root = gatui_tree_get_atom_tree(
			commons->root
		);
		uint32_t const start = a_leaf->val - a_root->bios;
		uint32_t const end = (start + a_leaf->num_bytes -1);
		sprintf(buffer, "[%06X - %06X]", start, end);
	} else {
		buffer[0] = '\0';
	}
	assert(strlen(buffer) < sizeof(buffer));
	gtk_label_set_text(GTK_LABEL(label), buffer);
	g_object_unref(g_leaf);
}
inline static GtkWidget*
create_leaves_pane(
		yaabegtk_commons* const commons
		) {
	// Columnview abstract
	GtkColumnView* const leaves_view = GTK_COLUMN_VIEW(
		gtk_column_view_new(NULL)
	);
	gtk_column_view_set_reorderable(leaves_view, true);
	gtk_column_view_set_show_row_separators(leaves_view, true);
	commons->leaves.view = leaves_view;

	// Create and attach columns
	GtkListItemFactory* factory;
	GtkColumnViewColumn* column;

	factory = g_object_connect(gtk_signal_list_item_factory_new(),
		//"swapped-signal::setup", G_CALLBACK(leaves_row_setup), NULL,
		"swapped-signal::bind", G_CALLBACK(leaves_rightclick_row_bind), commons,
		NULL
	);
	gtk_column_view_set_row_factory(leaves_view, factory);

	factory = g_object_connect(gtk_signal_list_item_factory_new(),
		"swapped-signal::setup", G_CALLBACK(tree_label_column_setup), NULL,
		"swapped-signal::bind", G_CALLBACK(leaves_name_column_bind), NULL,
		NULL
	);
	column = gtk_column_view_column_new("names", factory);
	gtk_column_view_column_set_resizable(column, true);
	gtk_column_view_append_column(leaves_view, column);
	g_object_unref(column);


	factory = g_object_connect(gtk_signal_list_item_factory_new(),
		"swapped-signal::setup", G_CALLBACK(leaves_val_column_setup), NULL,
		"swapped-signal::bind", G_CALLBACK(leaves_val_column_bind), NULL,
		"swapped-signal::unbind", G_CALLBACK(leaves_val_column_unbind), NULL,
		NULL
	);
	column = gtk_column_view_column_new("values", factory);
	gtk_column_view_column_set_resizable(column, true);
	gtk_column_view_column_set_expand(column, true);
	gtk_column_view_append_column(leaves_view, column);
	g_object_unref(column);


	factory = g_object_connect(gtk_signal_list_item_factory_new(),
		"swapped-signal::setup", G_CALLBACK(label_column_setup), NULL,
		"swapped-signal::bind", G_CALLBACK(leaves_offset_column_bind), commons,
		NULL
	);
	column = gtk_column_view_column_new("BIOS Offset", factory);
	gtk_column_view_column_set_resizable(column, true);
	gtk_column_view_append_column(leaves_view, column);
	g_object_unref(column);


	GtkWidget* const scrolledlist = gtk_scrolled_window_new();
	gtk_scrolled_window_set_child(
		GTK_SCROLLED_WINDOW(scrolledlist), GTK_WIDGET(leaves_view)
	);

	create_leaves_rightclick_menu(commons);

	return scrolledlist;
}


GtkWidget*
construct_tree_panes(
		yaabegtk_commons* const commons
		) {
	GtkWidget* const branches_pane = create_branches_pane(commons);
	GtkWidget* const leaves_pane = create_leaves_pane(commons);

	GtkPaned* const tree_divider = GTK_PANED(
		gtk_paned_new(GTK_ORIENTATION_HORIZONTAL)
	);
	gtk_paned_set_wide_handle(tree_divider, true);

	gtk_paned_set_resize_start_child(tree_divider, true);
	gtk_paned_set_shrink_start_child(tree_divider, false);
	gtk_paned_set_resize_end_child(tree_divider, true);
	gtk_paned_set_shrink_end_child(tree_divider, false);
	gtk_widget_set_size_request(leaves_pane, 60, 50);  // 60% horizontal
	gtk_paned_set_start_child(tree_divider, branches_pane);
	gtk_paned_set_end_child(tree_divider, leaves_pane);

	gtk_widget_set_vexpand(GTK_WIDGET(tree_divider), true);
	return GTK_WIDGET(tree_divider);
}
