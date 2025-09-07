#include "yaabe_gtk_internal.h"


// widget cache for GtkColumnView. see leaves_val_column_setup for more info
struct widget_cache {
	uint32_t n_widgets;
	uint32_t max_widgets;
	GtkWidget** widget_stack;
};
static struct widget_cache*
widget_cache_new(
		) {
	struct widget_cache* const cache = cralloc(sizeof(*cache));
	cache->n_widgets = 0;
	cache->max_widgets = 256; // seems to be more than enough
	void* wha = cralloc(
		cache->max_widgets * sizeof(cache->widget_stack[0])
	);
	cache->widget_stack = wha;
	return cache;
}
static void
widget_cache_push(
		struct widget_cache* const cache,
		GtkWidget* const widget
		) {
	g_object_ref_sink(widget);
	if (cache->n_widgets == cache->max_widgets) {
		cache->max_widgets *= 2;
		cache->widget_stack = crealloc(
			cache->widget_stack,
			cache->max_widgets * sizeof(cache->widget_stack[0])
		);
	}
	cache->widget_stack[cache->n_widgets] = widget;
	cache->n_widgets++;
}
static GtkWidget*
widget_cache_pop(
		struct widget_cache* const cache
		) {
	GtkWidget* widget = NULL;
	if (cache->n_widgets) {
		cache->n_widgets--;
		widget = cache->widget_stack[cache->n_widgets];
	}
	return widget;
}
static void
widget_cache_destroy(
		struct widget_cache* const cache
		) {
	while (cache->n_widgets) {
		cache->n_widgets--;
		g_object_unref(cache->widget_stack[cache->n_widgets]);
	}
	free(cache->widget_stack);
	free(cache);
}


void
label_column_setup(
		void const* const _null __unused, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
//TODO use https://docs.gtk.org/gtk4/class.Inscription.html
	GtkWidget* const label = gtk_label_new(NULL);
	gtk_label_set_xalign(GTK_LABEL(label), 0);
	gtk_label_set_use_markup(GTK_LABEL(label), true);
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
node_name_column_bind(
		void const* const _null __unused, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
// bind data to the UI skeleton
	GtkTreeListRow* const tree_row = gtk_column_view_cell_get_item(column_cell);
	GATUINode* const node = GATUI_NODE(gtk_tree_list_row_get_item(tree_row));

	GtkTreeExpander* const expander = GTK_TREE_EXPANDER(
		gtk_column_view_cell_get_child(column_cell)
	);
	gtk_tree_expander_set_list_row(expander, tree_row);

	GtkWidget* const label = gtk_tree_expander_get_child(expander);
	gtk_label_set_text(GTK_LABEL(label), gatui_node_get_name(node));
	constexpr enum i18n_languages current_lang = LANG_ENGLISH; // TODO
	gtk_widget_set_tooltip_text(
		label,
		gatui_node_get_description(node, current_lang)
	);

	g_object_unref(node);
}
static void
node_offset_column_bind(
		void const* const _null __unused, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
// bind data to the UI skeleton
	GtkWidget* const label = gtk_column_view_cell_get_child(column_cell);

	GATUINode* const node = GATUI_NODE(gtk_tree_list_row_get_item(
		gtk_column_view_cell_get_item(column_cell)
	));

	size_t start;
	size_t end;
	char buffer[sizeof("[123456 - 123456]")] = {[0]='\0'};
	constexpr char byte_array_format[] = "[%06zX - %06zX]";
	constexpr char bit_array_format[] = "[%u:%u]";
	char const* format = byte_array_format;
	size_t success;

	if (GATUI_IS_LEAF(node)) {
		GATUILeaf* const leaf = GATUI_LEAF(node);
		if (_ATUI_BITCHILD == gatui_leaf_get_atui_type(leaf)->fancy) {
			format = bit_array_format;
			success = gatui_leaf_get_bitfield_size(leaf, &start, &end);
		} else {
			success = gatui_node_get_region_bounds(node, &start, &end);
		}
	} else {
		success = gatui_node_get_region_bounds(node, &start, &end);
	}

	if (success) {
		assert(strlen(buffer) < sizeof(buffer));
		sprintf(buffer, format, start, end);
	}
	gtk_label_set_text(GTK_LABEL(label), buffer);
	g_object_unref(node);
}




static void
branch_name_column_bind(
		void const* const _null __unused, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
// bind data to the UI skeleton
	node_name_column_bind(_null, column_cell);

	/* TODO
	This should be tucked away in the model creation, but for some reason 
	GtkColumnView (or deeper) makes GtkTreeListRow's lose their notify signals,
	or makes them unreliable. See gatui_tree_create_trunk_model for more info.

	If it weren't for this issue, node_name_column_bind should be used instead.
	*/
	GtkTreeListRow* const tree_row = gtk_column_view_cell_get_item(column_cell);
	GATUINode* const node = GATUI_NODE(gtk_tree_list_row_get_item(tree_row));
	gulong const handler_id = g_signal_handler_find(tree_row,
		G_SIGNAL_MATCH_FUNC,    0,0,NULL,
		branches_track_expand_state,  NULL
	);
	if (0 == handler_id) { // usually passes
		g_signal_connect(tree_row, "notify::expanded",
			G_CALLBACK(branches_track_expand_state), node
		);
	}
	g_object_unref(node);
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
		"swapped-signal::bind", G_CALLBACK(node_offset_column_bind), NULL,
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
leaf_sets_editable(
	GATUILeaf* const leaf,
	GtkEditable* const editable
	) {
	char* const text = gatui_leaf_value_to_text(leaf);
	assert(text);
	gtk_editable_set_text(editable, text);
	free(text);
}
static void
leaves_editable_stray_reset(
		GtkColumnViewCell* const* const cell_cache
		) {
// If the value wasn't applied with enter, sync the text back to the actual
// data when keyboard leaves the textbox
	GtkColumnViewCell* const column_cell = *cell_cache;

	GtkEditable* const editable = GTK_EDITABLE(
		gtk_stack_get_child_by_name(
			GTK_STACK(gtk_column_view_cell_get_child(column_cell)), "text"
		)
	); // enum and text share same EntryBuffer

	GATUILeaf* const leaf = gtk_tree_list_row_get_item(
		gtk_column_view_cell_get_item(column_cell)
	);
	leaf_sets_editable(leaf, editable);
	g_object_unref(leaf);
}
static void
editable_sets_leaf(
		GtkEditable* const editable,
		GtkColumnViewCell* const* const cell_cache
		) {
// Only way to apply the value is to hit enter
	GtkColumnViewCell* const column_cell = *cell_cache;
	GATUILeaf* const leaf = gtk_tree_list_row_get_item(
		gtk_column_view_cell_get_item(column_cell)
	);
	gatui_leaf_set_value_from_text(
		leaf,
		gtk_editable_get_text(editable)
	);
	g_object_unref(leaf);
}

static void
enum_name_column_bind(
		GtkColumnViewCell* const* const leaves_cell_cache __unused,
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
		GtkColumnViewCell* const* const leaves_cell_cache,
		GtkColumnViewCell* const enum_column_cell
		) {
// bind
	GtkColumnViewCell* const leaves_column_cell = *leaves_cell_cache;

	GtkLabel* const label = GTK_LABEL(gtk_column_view_cell_get_child(
		enum_column_cell
	));
	struct atui_enum_entry const* const enum_entry = g_object_get_data(
		gtk_column_view_cell_get_item(enum_column_cell),
		"enum"
	); // no need to unref from list_item_get_item

	GATUILeaf* const leaf = gtk_tree_list_row_get_item(
		gtk_column_view_cell_get_item(leaves_column_cell)
	);

	char* const text = gatui_leaf_enum_val_to_text(leaf, enum_entry);
	gtk_label_set_text(label, text);
	free(text);
	g_object_unref(leaf);

	uint8_t const current_lang = LANG_ENGLISH;
	gtk_widget_set_tooltip_text(
		GTK_WIDGET(label), enum_entry->description[current_lang]
	);
}
static void
enum_list_sets_leaf(
		GtkColumnView* const enum_list,
		guint const paosition __unused,
		GtkColumnViewCell* const* const leaves_cell_cache
		) {
	GtkColumnViewCell* const leaves_column_cell = *leaves_cell_cache;

	struct atui_enum_entry const* const enum_entry = g_object_get_data(
		gtk_single_selection_get_selected_item(
			GTK_SINGLE_SELECTION(gtk_column_view_get_model(enum_list))
		), // no need to unref from gtk_single_selection_get_selected_item
		"enum"
	);

	GATUILeaf* const leaf = gtk_tree_list_row_get_item(
		gtk_column_view_cell_get_item(leaves_column_cell)
	);

	bool const has_set __unused = gatui_leaf_enum_entry_sets_value(
		leaf, enum_entry
	);
	assert(has_set);

	g_object_unref(leaf);
}
static void
enummenu_sets_selection(
		GtkWidget* const enum_list,
		GtkColumnViewCell* const* const leaves_cell_cache
		) {
	GtkColumnViewCell* const leaves_column_cell = *leaves_cell_cache;

	GtkSingleSelection* const enum_model = GTK_SINGLE_SELECTION(
		gtk_column_view_get_model(GTK_COLUMN_VIEW(enum_list))
	);

	GATUILeaf* const leaf = gtk_tree_list_row_get_item(
		gtk_column_view_cell_get_item(leaves_column_cell)
	);
	int16_t index = gatui_leaf_enum_entry_get_possible_index(leaf);
	if (-1 < index) {
		gtk_single_selection_set_selected(enum_model, index);
	} else {
		gtk_single_selection_set_selected(
			enum_model, GTK_INVALID_LIST_POSITION
		);
	}
	g_object_unref(leaf);
}
inline static GtkWidget*
construct_enum_columnview(
		GtkColumnViewCell** const leaves_cell_cache
		) {
	GtkColumnView* const enum_list = GTK_COLUMN_VIEW(gtk_column_view_new(NULL));
	GtkListItemFactory* factory;
	GtkColumnViewColumn* column;

	factory = g_object_connect(gtk_signal_list_item_factory_new(),
		"swapped-signal::setup", G_CALLBACK(label_column_setup), NULL,
		"swapped-signal::bind", G_CALLBACK(enum_name_column_bind),
			leaves_cell_cache,
		NULL
	);
	column = gtk_column_view_column_new("name", factory);
	gtk_column_view_append_column(enum_list, column);
	g_object_unref(column);

	factory = g_object_connect(gtk_signal_list_item_factory_new(),
		"swapped-signal::setup", G_CALLBACK(label_column_setup), NULL,
		"swapped-signal::bind", G_CALLBACK(enum_val_column_bind),
			leaves_cell_cache,
		NULL
	);
	column = gtk_column_view_column_new("value", factory);
	gtk_column_view_append_column(enum_list, column);
	g_object_unref(column);

	return GTK_WIDGET(enum_list);
}
inline static GtkWidget*
construct_enum_dropdown(
		GObject* const widget_bag,
		GtkEntryBuffer* const entry_buffer,
		GtkColumnViewCell** const leaves_cell_cache
		) {
	GtkEditable* const enumentry = GTK_EDITABLE(gtk_entry_new_with_buffer(
		entry_buffer
	));
	g_signal_connect(enumentry, "activate",
		G_CALLBACK(editable_sets_leaf), leaves_cell_cache
	);
	gtk_widget_set_hexpand(GTK_WIDGET(enumentry), true);

	GtkWidget* const enum_list = construct_enum_columnview(leaves_cell_cache);

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

	// shortcut way
	g_object_set_data(widget_bag, "enum_list", GTK_COLUMN_VIEW(enum_list));
	g_object_set_data(widget_bag, "enum_editable", GTK_WIDGET(enumentry));

	g_object_connect(enum_list,
		"signal::map", G_CALLBACK(enummenu_sets_selection), leaves_cell_cache,
		"signal::activate", G_CALLBACK(enum_list_sets_leaf), leaves_cell_cache,
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
		struct widget_cache* const cache, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
// setup
/*
When moving between different models the GtkColumnView unrefs ALL of its widgets
it generated during a previous setup pass, which makes moving loading a new
branch's leaves into view, slow. So, cache them with a stack.
*/
	GtkColumnViewCell** cell_cache;
	GtkWidget* widget_bag = widget_cache_pop(cache);
	if (widget_bag) {
		cell_cache = g_object_get_data(G_OBJECT(widget_bag), "cell_cache");
	} else {
		widget_bag = gtk_stack_new();
		g_object_ref_sink(widget_bag); // ref parity with cached alternative
		cell_cache = cralloc(sizeof(column_cell));
		g_object_set_data_full(G_OBJECT(widget_bag),
			"cell_cache", cell_cache, (GDestroyNotify) free
		);

		GtkEventController* const focus_sense = (
			gtk_event_controller_focus_new());
		g_signal_connect_swapped(focus_sense, "leave",
			G_CALLBACK(leaves_editable_stray_reset), cell_cache
		);
		gtk_widget_add_controller(widget_bag, focus_sense);
		// widget takes ownership of the controller, no need to unref.

		GtkEntryBuffer* const entry_buffer = gtk_entry_buffer_new(NULL,0);

		// numbers, strings
		//sub_widget = gtk_text_new();
		GtkWidget* const regular = gtk_entry_new_with_buffer(entry_buffer);
		gtk_stack_add_named(GTK_STACK(widget_bag), regular, "text");
		g_signal_connect(GTK_EDITABLE(regular), "activate",
			G_CALLBACK(editable_sets_leaf), cell_cache
		);

		// enums
		GtkWidget* const enumdropdown = construct_enum_dropdown(
			G_OBJECT(widget_bag), entry_buffer, cell_cache
		);
		gtk_stack_add_named(GTK_STACK(widget_bag), enumdropdown, "enum");

		g_object_unref(entry_buffer);
	}

	*cell_cache = column_cell;
	gtk_column_view_cell_set_child(column_cell, widget_bag);
	g_object_unref(widget_bag);
}
static void
leaves_val_column_teardown(
		struct widget_cache* const cache, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
	GtkWidget* const widget_bag = gtk_column_view_cell_get_child(column_cell);
	/* shouldn't be necessary because we can set before parenting
	GtkColumnViewCell** const cell_cache = g_object_get_data(
		G_OBJECT(widget_bag), "cell_cache"
	);
	*cell_cache = NULL;
	*/
	widget_cache_push(cache, widget_bag);
}

static void
leaves_val_column_bind(
		void const* const _null __unused, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
// bind
	GATUILeaf* const leaf = gtk_tree_list_row_get_item(
		gtk_column_view_cell_get_item(column_cell)
	);
	GtkStack* const widget_bag = GTK_STACK(
		gtk_column_view_cell_get_child(column_cell)
	);

	struct atui_leaf_type const* const type = gatui_leaf_get_atui_type(leaf);
	bool const has_value = gatui_leaf_has_textable_value(leaf);
	gtk_widget_set_visible(GTK_WIDGET(widget_bag), has_value);
	if (has_value) {
		GtkWidget* editable;
		if (type->has_enum) {
			gtk_stack_set_visible_child_name(widget_bag, "enum");
			// technically possible to get the list through other methods
			GtkColumnView* const enum_list = g_object_get_data(
				G_OBJECT(widget_bag), "enum_list"
			);
			GtkSelectionModel* const enum_model = (
				gatui_leaf_get_enum_menu_selection_model(leaf)
			);

			gtk_column_view_set_model(enum_list, enum_model);
			// technically possible to get the editable through other methods
			editable = g_object_get_data(
				G_OBJECT(widget_bag), "enum_editable"
			);
		} else {
			gtk_stack_set_visible_child_name(widget_bag, "text");
			editable = gtk_stack_get_visible_child(widget_bag);
		}

		leaf_sets_editable(leaf, GTK_EDITABLE(editable));
		g_signal_connect(leaf, "value-changed",
			G_CALLBACK(leaf_sets_editable), GTK_EDITABLE(editable)
		);
	}
	g_object_unref(leaf);
}
static void
leaves_val_column_unbind(
		void const* const _null __unused, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
	gtk_column_view_set_model(
		g_object_get_data(
			G_OBJECT(gtk_column_view_cell_get_child(column_cell)),
			"enum_list"
		),
		NULL
	);
	GATUILeaf* const leaf = gtk_tree_list_row_get_item(
		gtk_column_view_cell_get_item(column_cell)
	);
	g_signal_handlers_disconnect_matched(
		leaf,  G_SIGNAL_MATCH_FUNC,
		0,0, NULL,   G_CALLBACK(leaf_sets_editable),   NULL

	);
	g_object_unref(leaf);
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
		"swapped-signal::bind", G_CALLBACK(node_name_column_bind), NULL,
		NULL
	);
	column = gtk_column_view_column_new("names", factory);
	gtk_column_view_column_set_resizable(column, true);
	gtk_column_view_append_column(leaves_view, column);
	g_object_unref(column);


	factory = gtk_signal_list_item_factory_new();
	// see leaves_val_column_setup for more info.
	// queue could technically be allocated on commons.
	struct widget_cache* const cache = widget_cache_new();
	g_object_set_data_full(G_OBJECT(factory),
		"widget_cache", cache, (GDestroyNotify) widget_cache_destroy
	);
	g_object_connect(factory,
		"swapped-signal::setup", G_CALLBACK(leaves_val_column_setup), cache,
		"swapped-signal::teardown",G_CALLBACK(leaves_val_column_teardown),cache,
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
		"swapped-signal::bind", G_CALLBACK(node_offset_column_bind), NULL,
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
