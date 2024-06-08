#include <zlib.h>

#include "atomtree.h"
#include "atui.h"
#include "gatui.h"
#include "yaabe_gtk4.h"

static char8_t const yaabe_name[] = "YAABE BIOS Editor";

struct pane_context {
	GtkColumnView* view; // so branches can set leaves, and loading bios
	GtkPopover* rightclick;
};
typedef struct yaabegtk_commons { // global state tracker
	GATUITree* root;
	GtkApplication* yaabe_gtk;

	GtkEditable* pathbar;

	struct pane_context branches;
	struct pane_context leaves;

	// For gtk_widget_set_sensitive() -- don't allow when no bios is loaded
	GtkWidget* save_buttons;
	GtkWidget* reload_button;

	char8_t* pathbar_string;

} yaabegtk_commons;

// struct shamelessly stolen from https://gitlab.gnome.org/GNOME/gtk/-/blob/3fac42fd3c213e3d7c6bf3ce08c4ffd084abb45a/gtk/gtkcolumnviewrowprivate.h
// desperate times call for desperate measures
struct _GtkColumnViewRow_hack {
	GObject parent_instance;
	GtkWidget *owner; /* has a reference */
	// unnecessary bits truncated; we're only after owner
};
struct rightclick_pack { // see columnview_row_bind_attach_gesture
	struct yaabegtk_commons const* commons;
	union {
		GtkColumnViewRow* row;
		struct _GtkColumnViewRow_hack* row_hack;
	};
	union { // obtainable from row anyway; for convenience
		GATUIBranch* branch;
		GATUILeaf* leaf;
	};
};



#pragma pack(push, 1)
enum b64_header_target:uint8_t {
	B64_BRANCH_CONTIGUOUS,
	B64_BRANCH_LEAVES,
	B64_LEAF
};
struct b64_header { // paste header
	uint32_t crc; // everything not crc, including rest of header.
	struct { uint32_t
		header_ver    :1-0 +1,
		target        :4-2 +1, // enum b64_header_target
		num_segments :15-5 +1, // 2048 leaves
		num_bytes    :31-16 +1; // 64 KiBytes
	};
	// segments? uint32_t n_bytes[]; bytes[]
};
#pragma pack(pop)



static void
pathbar_update_path(
		GtkSingleSelection* const model,
		guint const position,
		guint const n_items,
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
		GVariant* const shortcut_args,
		gpointer const commons_ptr
		) {
// callback; resets pathbar if focus is lost
	yaabegtk_commons* const commons = commons_ptr;
	gtk_editable_set_text(GTK_EDITABLE(pathbar), commons->pathbar_string);
}

static void
pathbar_sets_branch_selection(
		yaabegtk_commons* const commons
		) {
// callback; go to branch based on path string
	char8_t const* const editable_text = (
		(char8_t const* const) gtk_editable_get_text(commons->pathbar)
	);
	struct atom_tree const* const a_root = gatui_tree_get_atom_tree(
		commons->root
	);
	struct atui_path_map* const map = path_to_atui(
		editable_text,
		a_root->atui_root
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

static void
select_changes_leaves(
		GtkSingleSelection* const model,
		guint const position,
		guint const n_items,
		yaabegtk_commons* const commons
		) {
// Signal callback
// Change the leaves pane's model based on the what is selected in brances
	GtkTreeListRow* const row = gtk_single_selection_get_selected_item(model);
	GATUIBranch* const g_branch = GATUI_BRANCH(gtk_tree_list_row_get_item(row));
	gtk_column_view_set_model(
		commons->leaves.view,
		gatui_branch_get_leaves_model(g_branch)
	);
	g_object_unref(g_branch);
}
static GListModel*
branches_treelist_generate_children(
		gpointer const parent_ptr,
		gpointer const data
		) {
// GtkTreeListModelCreateModelFunc for branches
// Creates the children models for the collapsable tree, of the branches pane.
	return gatui_branch_generate_children_model(parent_ptr);
}
inline static GtkSelectionModel*
create_trunk_model(
		yaabegtk_commons* const commons,
		GATUIBranch* const trunk
		) {
// Generate the very first model, of the tippy top of the tree, for the
// branches pane
	GListStore* const base_model = g_list_store_new(GATUI_TYPE_BRANCH);
	g_list_store_append(base_model, trunk);

	// TreeList, along with branches_treelist_generate_children, creates our
	// collapsable model.
	GObject* const trunk_model = G_OBJECT(gtk_single_selection_new(G_LIST_MODEL(
		gtk_tree_list_model_new(
			G_LIST_MODEL(base_model),  false, true,
			branches_treelist_generate_children,  NULL,NULL
		)
	))); // the later models take ownership of the earlier

	g_object_connect(trunk_model,
		"signal::selection-changed", G_CALLBACK(select_changes_leaves), commons,
		"signal::selection-changed", G_CALLBACK(pathbar_update_path), commons,
		NULL
	);

	return GTK_SELECTION_MODEL(trunk_model);
}
static void
create_and_set_active_atui_model(
		yaabegtk_commons* const commons,
		GATUITree* const new_root
		) {
// create and set the main branch model
	GATUIBranch* const trunk = gatui_tree_get_trunk(new_root);
	GtkSelectionModel* const new_model = create_trunk_model(commons, trunk);
	commons->root = new_root;

	gtk_column_view_set_model(commons->branches.view, new_model);

	// TODO divorce into notify::model signal/callback in create_branches_pane?
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




inline static void
calculate_rightclick_popup_location(
		GtkGesture* const click_sense,
		gdouble const x,
		gdouble const y,
		struct pane_context const* const context,
		GtkWidget* const row_widget
		) {
	// x,y is relative to the widget.
	// x,y is from row widget, translate it to the view widget.
	graphene_point_t view_coords;
	bool computed = gtk_widget_compute_point(
		row_widget,
		GTK_WIDGET(context->view),
		& (graphene_point_t const) {.x=x, .y=y},
		&view_coords
	);
	assert(computed);

	gtk_popover_set_pointing_to(context->rightclick, 
		& (GdkRectangle const) {
			.x=view_coords.x, .y=view_coords.y, .width=1, .height=1
		}
	);
	gtk_popover_popup(context->rightclick);
}
inline static void
columnview_create_rightclick_popup(
		GMenuModel* const menu_model,
		struct pane_context* const context
		) {
	GtkPopover* const popup_menu = GTK_POPOVER(
		gtk_popover_menu_new_from_model(menu_model)
	);
	gtk_popover_set_has_arrow(popup_menu, false);
	gtk_widget_set_halign(GTK_WIDGET(popup_menu), GTK_ALIGN_START);

	gtk_widget_set_parent(GTK_WIDGET(popup_menu), GTK_WIDGET(context->view));
	g_signal_connect_swapped(context->view, "destroy",
		// reference janitorial
		G_CALLBACK(gtk_widget_unparent), popup_menu
	);
	context->rightclick = popup_menu;
}

void
free_closure(
		gpointer data,
		GClosure* closure
		) {
	free(data);
}
void
free_notify(
		gpointer data
		) {
	free(data);
}

inline static void
columnview_row_bind_attach_gesture(
		yaabegtk_commons const* const commons,
		GtkColumnViewRow* const view_row,
		void (*gesture_cb)( // function pointer
			GtkGesture*, gint,gdouble,gdouble,
			struct rightclick_pack*
			)
		) {
	// since row_setup doesn't have the row widget created yet, we need to
	// handle the setup in bind
	if (0 == g_object_get_data(G_OBJECT(view_row), "atui")) {
		GtkWidget* const row_widget = ( // ColumnViewRowWidget
			((struct _GtkColumnViewRow_hack*) view_row)->owner
		);

		GtkGestureSingle* const click_sense = GTK_GESTURE_SINGLE(
			gtk_gesture_click_new()
		);
		gtk_widget_add_controller(row_widget,
			GTK_EVENT_CONTROLLER(click_sense)
		);
		gtk_gesture_single_set_exclusive(click_sense, true);
		gtk_gesture_single_set_button(click_sense, 3); // 3 is rightclick

		// the gesture call creates and binds the actions of the right click
		// menu to the view (view has the popup).
		// in order to that, the gesture call needs to pass view, row and popup
		struct rightclick_pack* const pack = malloc(
			sizeof(struct rightclick_pack)
		);
		pack->commons = commons;
		pack->row = view_row;

		g_signal_connect_data(click_sense, "pressed",
			G_CALLBACK(gesture_cb), pack,
			free_closure, G_CONNECT_DEFAULT
		);

		g_object_set_data(G_OBJECT(view_row), "atui", click_sense);
	}
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
label_column_setup(
		void const* const _null, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
//TODO use https://docs.gtk.org/gtk4/class.Inscription.html
	GtkWidget* const label = gtk_label_new(NULL);
	gtk_label_set_xalign(GTK_LABEL(label), 0);
	gtk_column_view_cell_set_child(column_cell, label);
}
static void
tree_label_column_setup(
		void const* const _null, // swapped-signal:: with factory
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
leaves_name_column_bind(
		void const* const _null, // swapped-signal:: with factory
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
	char8_t* const text = gatui_leaf_value_to_text(g_leaf);
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

	char8_t* const text = gatui_leaf_enum_val_to_text(g_leaf, enum_entry);
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
		guint const paosition,
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

	bool const has_set = gatui_leaf_enum_entry_sets_value(g_leaf, enum_entry);
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

	GtkPopover* const popover = GTK_POPOVER(gtk_popover_new());
	gtk_popover_set_has_arrow(popover, false);
	gtk_popover_set_child(popover, enum_list);

	g_object_connect(enum_list,
		"signal::realize", G_CALLBACK(enummenu_sets_selection),
			leaves_column_cell,
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
		void const* const _null, // swapped-signal:: with factory
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
		void const* const _null, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
// bind
	GATUILeaf* const g_leaf = gtk_tree_list_row_get_item(
		gtk_column_view_cell_get_item(column_cell)
	);
	GtkStack* const widget_bag = GTK_STACK(
		gtk_column_view_cell_get_child(column_cell)
	);

	union atui_type const type = gatui_leaf_get_atui_type(g_leaf);
	if (type.radix || type.fancy == ATUI_STRING || type.fancy == ATUI_ARRAY) {

		gtk_widget_set_visible(GTK_WIDGET(widget_bag), true);
		GtkWidget* editable;
		if (type.fancy == ATUI_ENUM) {
			gtk_stack_set_visible_child_name(widget_bag, "enum");
			GtkWidget* const enumbox = gtk_stack_get_visible_child(widget_bag);
			GtkColumnView* const enum_list = GTK_COLUMN_VIEW(
				gtk_popover_get_child(
					gtk_menu_button_get_popover(GTK_MENU_BUTTON(
						gtk_widget_get_first_child(enumbox)
					))
				)
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
		void const* const _null, // swapped-signal:: with factory
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

	char8_t buffer[18];
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
		sprintf(buffer, "[%05X - %05X]", start, end);
	} else {
		buffer[0] = '\0';
	}
	assert(strlen(buffer) < sizeof(buffer));
	gtk_label_set_text(GTK_LABEL(label), buffer);
	g_object_unref(g_leaf);
}


static void
leaf_right_click_copy_name(
		GSimpleAction* const action,
		GVariant* const parameter,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	atui_leaf const* const a_leaf = gatui_leaf_get_atui(pack->leaf);
	gdk_clipboard_set_text(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		a_leaf->name
	);
}
static void
leaf_right_click_copy_path(
		GSimpleAction* const action,
		GVariant* const parameter,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;

	char8_t* const pathstring = gatui_leaf_to_path(pack->leaf);

	gdk_clipboard_set_text(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		pathstring
	);

	free(pathstring);
}

inline static void
generic_error_popup(
		char8_t const* const primary,
		char8_t const* const secondary,
		GtkApplication* const parent_app
		) {
	GtkAlertDialog* const alert = gtk_alert_dialog_new(primary);
	gtk_alert_dialog_set_detail(alert, secondary);
	gtk_alert_dialog_show(
		alert,
		gtk_application_get_active_window(parent_app)
	);

	g_object_unref(alert);
}

static gchar*
b64_packet_encode(
		void const* const payload,
		size_t const payload_size,
		enum b64_header_target const target,
		uint8_t const num_segments
		) {
	size_t const packet_size = sizeof(struct b64_header) + payload_size;
	void* const data_packet = malloc(packet_size);
	struct b64_header* const header = data_packet;
	void* const payload_area = data_packet + sizeof(struct b64_header);

	header->header_ver = 0;
	header->target = target;
	header->num_segments = num_segments;
	header->num_bytes = payload_size;
	memcpy(payload_area, payload, payload_size);
	header->crc = crc32(
		0,
		(data_packet + sizeof(uint32_t)), // exclude crc
		(packet_size - sizeof(uint32_t))
	);

	gchar* const b64_text = g_base64_encode(data_packet, packet_size);
	free(data_packet);
	return b64_text;
}

static bool // decode error
b64_packet_decode(
		char8_t const* const b64_text,
		struct b64_header** const header_out,
		void** const payload
		) {
	size_t b64_num_bytes = 0;
	struct b64_header* const header = (
		(void*) g_base64_decode(b64_text, &b64_num_bytes)
	);

	if (0 == b64_num_bytes) {
		return true;
	}
	*header_out = header;
	if (b64_num_bytes < sizeof(struct b64_header)) {
		return true;
	}
	if (b64_num_bytes < header->num_bytes + sizeof(struct b64_header)) {
		return true;
	}
	uint32_t const crc = crc32(
		0,
		((void*)header + sizeof(uint32_t)),
		(header->num_bytes + sizeof(struct b64_header) - sizeof(uint32_t))
	);
	if (crc != header->crc) {
		return true;
	}

	// strict compliance
	if ((header->target==B64_BRANCH_CONTIGUOUS) && (header->num_segments!=1)) {
		return true;
	}
	if ((header->target==B64_LEAF) && (header->num_segments!=1)) {
		return true;
	}

	*payload = (void*) header + sizeof(header);
	return false;
}

static void
leaf_right_click_copy_data(
		GSimpleAction* const action,
		GVariant* const parameter,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	GVariant* const val = gatui_leaf_get_value(pack->leaf);
	void const* const payload = g_variant_get_data(val);
	size_t const payload_size = g_variant_get_size(val);
	assert(payload);
	assert(payload_size);

	gchar* const b64_text = b64_packet_encode(
		payload, payload_size, B64_LEAF, 1
	);

	gdk_clipboard_set_text(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		b64_text
	);
	g_free(b64_text);
	g_variant_unref(val);
}
static void
leaf_right_click_paste_data_set_data(
		GObject* const clipboard,
		GAsyncResult* const async_data,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	atui_leaf const* const a_leaf = gatui_leaf_get_atui(pack->leaf);

	GError* err = NULL;
	char8_t* const b64_text = gdk_clipboard_read_text_finish(
		GDK_CLIPBOARD(clipboard), async_data, &err
	);
	if (err) {
		generic_error_popup(
			"clipboard error", err->message, pack->commons->yaabe_gtk
		);
		g_error_free(err);
		return;
	}

	GtkAlertDialog* error_popup;
	struct b64_header* header = NULL;
	void* payload = NULL;
	bool const decode_error = b64_packet_decode(b64_text, &header, &payload);
	g_free(b64_text);
	if (decode_error) {
		error_popup = gtk_alert_dialog_new("Data decode error");
		goto error_exit;
	}
	if (header->target != B64_LEAF) {
		error_popup = gtk_alert_dialog_new(
			"Incompatible data for leaf %s.",
			a_leaf->name
		);
		goto error_exit;
	}

	uint32_t const leaf_num_bytes = gatui_leaf_num_bytes(pack->leaf);
	if (a_leaf->type.fancy == ATUI_STRING) {
		if (strnlen(payload, header->num_bytes) < header->num_bytes) {
			gatui_leaf_set_value_from_text(pack->leaf, payload);
			goto success_exit;
		} else {
			error_popup = gtk_alert_dialog_new(
				"%s takes a string, but the base64 data does not decode to"
				" a proper string."
			);
			goto error_exit;
		}
	} else if (header->num_bytes == leaf_num_bytes) {
		GVariantType* const raw_type = g_variant_type_new("ay");
		GVariant* const new_val = g_variant_new_from_data(
			raw_type,
			payload, header->num_bytes,
			false,
			free_notify, header
		);
		header = NULL; // g_variant_new_from_data takes ownership
		g_free(raw_type);
		bool const set_success = gatui_leaf_set_value(pack->leaf, new_val);
		g_variant_unref(new_val);
		if (set_success) {
			goto success_exit;
		} else {
			error_popup = gtk_alert_dialog_new(
				"Generic error pasting base64 data for leaf %s.",
				a_leaf->name
			);
			goto error_exit;
		}
	} else {
		error_popup = gtk_alert_dialog_new(
			"Wrong size: pasted base64 data decodes to %u bytes, "
			"but %s is %u bytes.",
			header->num_bytes, a_leaf->name, leaf_num_bytes
		);
		goto error_exit;
	}


	error_exit:
	gtk_alert_dialog_show(
		error_popup,
		gtk_application_get_active_window(pack->commons->yaabe_gtk)
	);
	g_object_unref(error_popup);

	if (header) {
		g_free(header); // g_variant_new_from_data takes ownership
	}

	success_exit:
	return;
}
static void
leaf_right_click_paste_data(
		GSimpleAction* const action,
		GVariant* const parameter,
		gpointer const pack_ptr
		) {
	gdk_clipboard_read_text_async(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		NULL,
		leaf_right_click_paste_data_set_data,
		pack_ptr
	);
}

static void
leaves_rightclick_selection_sterilise(
		GtkPopover* const rightclick,
		GtkColumnView* const view
		) {
	// TODO hack: gtk_column_view_row_set_selectable is broken.
	// See `leaves_row_setup`
	GtkSelectionModel* const leaves_model = gtk_column_view_get_model(view);
	gtk_single_selection_set_selected(
		GTK_SINGLE_SELECTION(leaves_model),
		GTK_INVALID_LIST_POSITION
	);
	g_signal_connect(leaves_model, "selection-changed",
		G_CALLBACK(gtk_selection_model_unselect_item), NULL
	);
}

static void
leaves_rightclick_popup(
		GtkGesture* const click_sense,
		gint const num_presses,
		gdouble const x,
		gdouble const y,
		struct rightclick_pack* const pack
		) {
	if (num_presses != 1) {
		return;
	}
	gtk_gesture_set_state(click_sense, GTK_EVENT_SEQUENCE_CLAIMED);

	struct pane_context const* const leaves_context = &(pack->commons->leaves);


	GATUILeaf* const g_leaf = gtk_tree_list_row_get_item(
		gtk_column_view_row_get_item(pack->row)
	);
	g_object_unref(g_leaf); // we don't need a second reference
	pack->leaf = g_leaf;
	atui_leaf const* const a_leaf = gatui_leaf_get_atui(g_leaf);


	// see also create_leaves_rightclick_menu
	GActionEntry actions[4] = {0};
	actions[0] = (GActionEntry) {"name", leaf_right_click_copy_name};
	actions[1] = (GActionEntry) {"path", leaf_right_click_copy_path};
	uint8_t num_actions = 2;
	if (a_leaf->num_bytes || a_leaf->type.fancy == _ATUI_BITCHILD) {
		actions[num_actions].name = "copy_data";
		actions[num_actions].activate = leaf_right_click_copy_data;
		num_actions++;
		actions[num_actions].name = "paste_data";
		actions[num_actions].activate = leaf_right_click_paste_data;
		num_actions++;
	}
	assert(num_actions <= lengthof(actions));
	GActionMap* const action_set = G_ACTION_MAP(g_simple_action_group_new());
	g_action_map_add_action_entries(action_set,
		actions, num_actions,
		pack
	);
	gtk_widget_insert_action_group(GTK_WIDGET(leaves_context->view),
		"leaf", G_ACTION_GROUP(action_set)
	);
	// we cannot disconnect action group on popdown because it kills the
	// actions. Simply replacing them seems to be fine.
	g_object_unref(action_set);

	// disconnect the selection blocker, and then select 
	g_signal_handlers_disconnect_matched(
		gtk_column_view_get_model(pack->commons->leaves.view), // SelectionModel
		G_SIGNAL_MATCH_FUNC,
		0, 0, NULL,
		gtk_selection_model_unselect_item,
		NULL
	);
	gtk_column_view_scroll_to(pack->commons->leaves.view,
		gtk_column_view_row_get_position(pack->row),
		NULL,
		GTK_LIST_SCROLL_SELECT,
		NULL
	);
	calculate_rightclick_popup_location(
		click_sense, x,y, leaves_context, pack->row_hack->owner
	);
}
inline static void
create_leaves_rightclick_menu(
		yaabegtk_commons* const commons
		) {
	GMenu* const menu_model = g_menu_new();
	g_menu_append(menu_model, "Copy Name", "leaf.name");
	g_menu_append(menu_model, "Copy Path", "leaf.path");
	g_menu_append(menu_model, "Copy Data", "leaf.copy_data");
	g_menu_append(menu_model, "Paste Data", "leaf.paste_data");
	// see also leaves_rightclick_popup

	columnview_create_rightclick_popup(
		G_MENU_MODEL(menu_model), &commons->leaves
	);
	g_signal_connect(commons->leaves.rightclick, "closed",
		G_CALLBACK(leaves_rightclick_selection_sterilise), commons->leaves.view
	);
}
static void
leaves_row_bind(
		yaabegtk_commons const* const commons,
		GtkColumnViewRow* const view_row
		) {
	columnview_row_bind_attach_gesture(
		commons, view_row, leaves_rightclick_popup
	);
}
static void
leaves_row_setup(
		void const* const _null, // swapped-signal:: with factory
		GtkColumnViewRow* const view_row
		) {
	gtk_column_view_row_set_selectable(view_row, false);
	// TODO gtk_column_view_row_set_selectable is broken, even in bind.
	// For a workaround see where `gtk_selection_model_unselect_item` and
	// `leaves_rightclick_selection_sterilise` are used.
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
		"swapped-signal::bind", G_CALLBACK(leaves_row_bind), commons,
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
	column = gtk_column_view_column_new("BIOS offset", factory);
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


static void
branch_name_column_bind(
		void const* const _null, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
// bind data to the UI skeleton
	GtkTreeListRow* const tree_row = gtk_column_view_cell_get_item(column_cell);
	GATUIBranch* const g_branch = gtk_tree_list_row_get_item(tree_row);
	atui_branch const* const a_branch = gatui_branch_get_atui(g_branch);
	g_object_unref(g_branch);

	GtkTreeExpander* const expander = GTK_TREE_EXPANDER(
		gtk_column_view_cell_get_child(column_cell)
	);
	gtk_tree_expander_set_list_row(expander, tree_row);

	GtkWidget* const label = gtk_tree_expander_get_child(expander);
	gtk_label_set_text(GTK_LABEL(label), a_branch->name);
	uint8_t const current_lang = LANG_ENGLISH;
	gtk_widget_set_tooltip_text(label, a_branch->description[current_lang]);
}
static void
branch_type_column_bind(
		void const* const _null, // swapped-signal:: with factory
		GtkColumnViewCell* const column_cell
		) {
// bind
	GtkWidget* const label = gtk_column_view_cell_get_child(column_cell);

	GtkTreeListRow* const tree_row = gtk_column_view_cell_get_item(column_cell);
	GATUIBranch* const g_branch = gtk_tree_list_row_get_item(tree_row);
	atui_branch const* const a_branch = gatui_branch_get_atui(g_branch);
	g_object_unref(g_branch);

	gtk_label_set_text(GTK_LABEL(label), a_branch->origname);
}

static void
branch_right_click_copy_name(
		GSimpleAction* const action,
		GVariant* const parameter,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	atui_branch const* const a_branch = gatui_branch_get_atui(pack->branch);
	gdk_clipboard_set_text(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		a_branch->name
	);
}
static void
branch_right_click_copy_struct_name(
		GSimpleAction* const action,
		GVariant* const parameter,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	atui_branch const* const a_branch = gatui_branch_get_atui(pack->branch);
	gdk_clipboard_set_text(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		a_branch->origname
	);
}
static void
branch_right_click_copy_path(
		GSimpleAction* const action,
		GVariant* const parameter,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;

	char8_t* const pathstring = gatui_branch_to_path(pack->branch);

	gdk_clipboard_set_text(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		pathstring
	);
	free(pathstring);
}
static void
branch_right_click_copy_contiguous(
		GSimpleAction* const action,
		GVariant* const parameter,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	GVariant* const val = gatui_branch_get_contiguous_memory(pack->branch);
	void const* const payload = g_variant_get_data(val);
	size_t const payload_size = g_variant_get_size(val);
	assert(payload);
	assert(payload_size);

	gchar* const b64_text = b64_packet_encode(
		payload, payload_size, B64_BRANCH_CONTIGUOUS, 1
	);
	gdk_clipboard_set_text(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		b64_text
	);
	g_free(b64_text);
	g_variant_unref(val);
}
static void
branch_right_click_copy_leaves(
		GSimpleAction* const action,
		GVariant* const parameter,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	GVariant* val = NULL;
	uint16_t num_copyable_leaves;
	bool const success = gatui_branch_get_leaves_memory_package(
		pack->branch,
		&val,
		&num_copyable_leaves
	);
	assert(val);
	void const* const payload = g_variant_get_data(val);
	size_t const payload_size = g_variant_get_size(val);
	assert(payload);
	assert(payload_size);

	gchar* const b64_text = b64_packet_encode(
		payload, payload_size, B64_BRANCH_LEAVES, num_copyable_leaves
	);
	gdk_clipboard_set_text(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		b64_text
	);
	g_free(b64_text);
	g_variant_unref(val);
}

static void
branch_right_click_paste_data_set_data(
		GObject* const clipboard,
		GAsyncResult* const async_data,
		gpointer const pack_ptr
		) {
// AsyncReadyCallback
	struct rightclick_pack const* const pack = pack_ptr;
	atui_branch const* const a_branch = gatui_branch_get_atui(pack->branch);

	GError* err = NULL;
	char8_t* const b64_text = gdk_clipboard_read_text_finish(
		GDK_CLIPBOARD(clipboard), async_data, &err
	);
	if (err) {
		generic_error_popup(
			"clipboard error", err->message, pack->commons->yaabe_gtk
		);
		g_error_free(err);
		return;
	}

	GtkAlertDialog* error_popup;
	struct b64_header* header = NULL;
	void* payload = NULL;
	bool const decode_error = b64_packet_decode(b64_text, &header, &payload);
	g_free(b64_text);
	if (decode_error) {
		error_popup = gtk_alert_dialog_new("Data decode error");
		goto error_exit;
	}

	GVariant* new_val = NULL;
	if ((header->target == B64_BRANCH_CONTIGUOUS)
			|| (header->target == B64_BRANCH_LEAVES)
			) {
		GVariantType* const raw_type = g_variant_type_new("ay");
		new_val = g_variant_new_from_data(
			raw_type,
			payload, header->num_bytes,
			false,
			free_notify, header
		);
		g_free(raw_type);
		if (header->target == B64_BRANCH_CONTIGUOUS) {
			if (header->num_bytes != a_branch->table_size) {
				error_popup = gtk_alert_dialog_new(
					"%s has %u contiguous bytes, but pasted data is %u bytes.",
					a_branch->name, a_branch->table_size, header->num_bytes
				);
				goto error_exit;
			}
			bool const set_success = gatui_branch_set_contiguous_memory(
				pack->branch, new_val
			);
			if (set_success) {
				goto success_exit;
			} else {
				error_popup = gtk_alert_dialog_new(
					"Generic error pasting contiguous data for branch %s.",
					a_branch->name
				);
				goto error_exit;
			}
		} else {
			bool const set_success = gatui_branch_set_leaves_memory_package(
				pack->branch, new_val, header->num_segments
			);
			if (set_success) {
				goto success_exit;
			} else {
				error_popup = gtk_alert_dialog_new(
					"Incompatible data for branch %s.",
					a_branch->name
				);
				goto error_exit;
			}
		}
	} else {
		error_popup = gtk_alert_dialog_new(
			"Incompatible data for branch %s.",
			a_branch->name
		);
		goto error_exit;
	}


	error_exit:
	gtk_alert_dialog_show(
		error_popup,
		gtk_application_get_active_window(pack->commons->yaabe_gtk)
	);
	g_object_unref(error_popup);

	success_exit:
	if (new_val) {
		g_variant_unref(new_val);
	} else if (header) {
		g_free(header); // g_variant_new_from_data takes ownership
	}
}
static void
branch_right_click_paste_data(
		GSimpleAction* const action,
		GVariant* const parameter,
		gpointer const pack_ptr
		) {
	gdk_clipboard_read_text_async(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		NULL,
		branch_right_click_paste_data_set_data,
		pack_ptr
	);
}
static void
branches_rightclick_popup(
		GtkGesture* const click_sense,
		gint const num_presses,
		gdouble const x,
		gdouble const y,
		struct rightclick_pack* const pack
		) {
	if (num_presses != 1) {
		return;
	}
	gtk_gesture_set_state(click_sense, GTK_EVENT_SEQUENCE_CLAIMED);
	struct pane_context const* const branches_context = &(
		pack->commons->branches
	);


	// connect  actions
	GATUIBranch* const g_branch = gtk_tree_list_row_get_item(
		gtk_column_view_row_get_item(pack->row)
	);
	g_object_unref(g_branch); // we don't need a second reference.
	pack->branch = g_branch;
	
	atui_branch const* const branch = gatui_branch_get_atui(g_branch);
	// see also create_branches_rightclick_menu
	GActionEntry actions[6] = {0};
	actions[0] = (GActionEntry) {"name", branch_right_click_copy_name};
	actions[1] = (GActionEntry) {"struct", branch_right_click_copy_struct_name};
	actions[2] = (GActionEntry) {"path", branch_right_click_copy_path};
	uint8_t num_actions = 3;
	GActionMap* const action_set = G_ACTION_MAP(g_simple_action_group_new());
	if (branch->num_copyable_leaves || branch->table_size) {
		if (branch->num_copyable_leaves && ! branch->prefer_contiguous) {
			actions[num_actions].name = "copy_leaves";
			actions[num_actions].activate = branch_right_click_copy_leaves;
			num_actions++;
		}
		if (branch->table_size) {
			actions[num_actions].name = "copy_contiguous";
			actions[num_actions].activate = branch_right_click_copy_contiguous;
			num_actions++;
		}
		actions[num_actions].name = "paste_data";
		actions[num_actions].activate = branch_right_click_paste_data;
		num_actions++;
	};
	g_action_map_add_action_entries(action_set,
		actions, num_actions,
		pack
	);
	gtk_widget_insert_action_group(GTK_WIDGET(branches_context->view),
		"branch", G_ACTION_GROUP(action_set)
	);
	// we cannot disconnect action group on popdown because it kills the
	// actions. Simply replacing them seems to be fine.
	g_object_unref(action_set);

	// select column and pop up
	gtk_column_view_scroll_to(pack->commons->branches.view,
		gtk_column_view_row_get_position(pack->row),
		NULL,
		GTK_LIST_SCROLL_SELECT,
		NULL
	);
	calculate_rightclick_popup_location(
		click_sense, x,y, branches_context, pack->row_hack->owner
	);
}
inline static void
create_branches_rightclick_menu(
		yaabegtk_commons* const commons
		) {
	GMenu* const menu_model = g_menu_new();
	g_menu_append(menu_model, "Copy Name", "branch.name");
	g_menu_append(menu_model, "Copy Struct Name", "branch.struct");
	g_menu_append(menu_model, "Copy Path", "branch.path");
	g_menu_append(menu_model, "Copy Leaves", "branch.copy_leaves");
	g_menu_append(menu_model, "Copy Contiguous Data", "branch.copy_contiguous");
	g_menu_append(menu_model, "Paste Data", "branch.paste_data");
	// see also branches_rightclick_popup

	columnview_create_rightclick_popup(
		G_MENU_MODEL(menu_model), &commons->branches
	);
}
static void
branches_row_bind(
		yaabegtk_commons const* const commons,
		GtkColumnViewRow* const view_row
		) {
	columnview_row_bind_attach_gesture(
		commons, view_row, branches_rightclick_popup
	);
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
		"swapped-signal::bind", G_CALLBACK(branches_row_bind), commons,
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
		"swapped-signal::bind", G_CALLBACK(branch_type_column_bind), NULL,
		NULL
	);
	column = gtk_column_view_column_new("Struct Type", factory);
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
inline static GtkWidget*
construct_tree_panes(
		yaabegtk_commons* const commons
		) {
	GtkWidget* const branches_pane = create_branches_pane(commons);
	GtkWidget* const leaves_pane = create_leaves_pane(commons);
	GtkWidget* const tree_divider = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_widget_set_vexpand(tree_divider, true);
	gtk_paned_set_resize_start_child(GTK_PANED(tree_divider), true);
	gtk_paned_set_shrink_start_child(GTK_PANED(tree_divider), false);
	gtk_paned_set_resize_end_child(GTK_PANED(tree_divider), true);
	gtk_paned_set_shrink_end_child(GTK_PANED(tree_divider), false);
	//gtk_widget_set_size_request(branches_pane, 34, 50); // 1/3 horizontal
	//gtk_widget_set_size_request(leaves_pane, 66, 50);  // 2/3
	gtk_paned_set_start_child(GTK_PANED(tree_divider), branches_pane);
	gtk_paned_set_end_child(GTK_PANED(tree_divider), leaves_pane);

	return tree_divider;
} 



static void
set_editor_titlebar(
		yaabegtk_commons* const commons
		) {
// Set the window name to the name of the currently-open bios.
	char8_t const print_format_file[] = "%s (%s)";
	char8_t const print_format_nofile[] = "%s";

	char8_t* filename;
	uint16_t filename_length;
	char8_t const* formatstr;
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

	char8_t* const window_title = malloc(
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

inline static void
filer_error_window(
		yaabegtk_commons const* const commons,
		GError* const ferror,
		char8_t const* const title
		) {
// Simple error popup
	GtkAlertDialog* const alert = gtk_alert_dialog_new(title);
	gtk_alert_dialog_set_detail(alert, ferror->message);
	gtk_alert_dialog_show(
		alert, 
		gtk_application_get_active_window(commons->yaabe_gtk)
	);

	g_object_unref(alert);
}
inline static void
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
		if (commons->root) {
			g_object_unref(commons->root);
		}
		create_and_set_active_atui_model(commons, new_tree);

		if (gtk_widget_get_sensitive(commons->save_buttons) == false) {
			gtk_widget_set_sensitive(commons->save_buttons, true);
			gtk_widget_set_sensitive(commons->reload_button, true);
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
static void
load_button_open_bios(
		yaabegtk_commons* const commons
		) {
// Signal callback
	GtkFileDialog* const filer = gtk_file_dialog_new();
	GtkWindow* const active_window = gtk_application_get_active_window(
		commons->yaabe_gtk
	);

	GFile* working_dir;
	if (commons->root) {
		working_dir = g_file_get_parent(
			gatui_tree_get_bios_file(commons->root)
		);
	}else {
		working_dir = g_file_new_for_path(".");
	}
	gtk_file_dialog_set_initial_folder(filer, working_dir);
	g_object_unref(working_dir);

	gtk_file_dialog_open(filer,
		active_window, NULL, filedialog_load_and_set_bios, commons
	);
	g_object_unref(filer);
}
static void
reload_button_reload_bios(
		yaabegtk_commons* const commons
		) {
// signal callback
	GError* ferror = NULL;

	GATUITree* const old_tree = commons->root;
	GFile* const biosfile = gatui_tree_get_bios_file(old_tree);
	GATUITree* const new_tree = gatui_tree_new_from_gfile(biosfile, &ferror);
	if (ferror) {
		filer_error_window(commons, ferror, "Reload BIOS error");
		g_error_free(ferror);
		return;
	}

	create_and_set_active_atui_model(commons, new_tree);
	g_object_unref(old_tree);
}
static void
save_button_same_file(
		yaabegtk_commons* const commons
		) {
// signal callback
	GError* ferror = NULL;

	gatui_tree_save(commons->root, &ferror);
	if (ferror) {
		filer_error_window(commons, ferror, "Save BIOS error");
		g_error_free(ferror);
	}
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
	return;

	ferr_msg:
	filer_error_window(commons, ferror, "Save BIOS As error");
	ferr_nomsg:
	g_error_free(ferror);
	return;
}
static void
saveas_button_name_bios(
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
inline static GtkWidget*
construct_loadsave_buttons_box(
		yaabegtk_commons* const commons
		) {
	GtkWidget* const load_button = gtk_button_new_with_label("Load");
	g_signal_connect_swapped(load_button, "clicked",
		G_CALLBACK(load_button_open_bios), commons
	);
	GtkWidget* const reload_button = gtk_button_new_with_label("Reload");
	g_signal_connect_swapped(reload_button, "clicked",
		G_CALLBACK(reload_button_reload_bios), commons
	);
	GtkWidget* const load_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_append(GTK_BOX(load_buttons), load_button);
	gtk_box_append(GTK_BOX(load_buttons), reload_button);


	GtkWidget* const save_button = gtk_button_new_with_label("Save");
	g_signal_connect_swapped(save_button, "clicked",
		G_CALLBACK(save_button_same_file), commons
	);
	GtkWidget* const saveas_button = gtk_button_new_with_label("Save As");
	g_signal_connect_swapped(saveas_button, "clicked",
		G_CALLBACK(saveas_button_name_bios), commons
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
	gtk_box_append(GTK_BOX(buttonboxes), load_buttons);
	gtk_box_append(GTK_BOX(buttonboxes), save_buttons);
	gtk_box_append(GTK_BOX(buttonboxes), cf_button);

	commons->reload_button = reload_button;
	commons->save_buttons = save_buttons;
	if (commons->root == NULL) {
		gtk_widget_set_sensitive(save_buttons, false);
		gtk_widget_set_sensitive(reload_button, false);
	}

	return buttonboxes;
}



static gboolean
dropped_file_open_bios(
		GtkDropTarget* const dropctrl,
		GValue const* const value,
		gdouble const x,
		gdouble const y,
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
yaabe_app_activate(
		GtkApplication* const gtkapp,
		yaabegtk_commons* const commons
		) {
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

	GtkWindow* const window = GTK_WINDOW(gtk_application_window_new(gtkapp));
	gtk_widget_add_controller(
		GTK_WIDGET(window), GTK_EVENT_CONTROLLER(dropfile)
	);

	gtk_window_set_default_size(window, 1400,700); // 2:1
	gtk_window_set_child(window, GTK_WIDGET(main_box));
	gtk_widget_grab_focus(tree_divider);
	gtk_widget_grab_focus(GTK_WIDGET(commons->branches.view));

	if (commons->root) {
		create_and_set_active_atui_model(commons, commons->root);
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

	return status;
}
