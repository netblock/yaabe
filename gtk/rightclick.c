#include "yaabe_gtk_internal.h"

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
		GObject* obj;
		GATUIBranch* branch;
		GATUILeaf* leaf;
		GATUIRegexNode* node;
	};
};

static void
attach_actions_and_popup(
		GActionEntry const* const actions,
		uint8_t const num_actions,
		struct pane_context const* const pane,
		struct rightclick_pack* const pack,
		float64_t const x,
		float64_t const y
		) {
	GActionMap* const action_set = G_ACTION_MAP(g_simple_action_group_new());
	g_action_map_add_action_entries(action_set, actions, num_actions, pack);
	gtk_widget_insert_action_group(GTK_WIDGET(pane->view),
		"context", G_ACTION_GROUP(action_set)
	);
	// we cannot disconnect action group on popdown because it kills the
	// actions. Simply replacing them seems to be fine.
	g_object_unref(action_set);

	gtk_column_view_scroll_to(pane->view,
		gtk_column_view_row_get_position(pack->row),
		NULL,
		GTK_LIST_SCROLL_SELECT,
		NULL
	);

	// x,y is relative to the widget.
	// x,y is from row widget, translate it to the view widget.
	graphene_point_t view_coords;
	bool const computed __unused = gtk_widget_compute_point(
		pack->row_hack->owner,
		GTK_WIDGET(pane->view),
		& (graphene_point_t const) {.x=x, .y=y},
		&view_coords
	);
	assert(computed);
	gtk_popover_set_pointing_to(pane->rightclick,
		& (GdkRectangle const) {
			.x=view_coords.x, .y=view_coords.y, .width=1, .height=1
		}
	);
	gtk_popover_popup(pane->rightclick);
}

static void
columnview_create_rightclick_popup(
		GMenuModel* const menu_model,
		struct pane_context* const pane
		) {
	GtkPopover* const popup_menu = GTK_POPOVER(
		gtk_popover_menu_new_from_model(menu_model)
	);
	gtk_popover_set_has_arrow(popup_menu, false);
	gtk_widget_set_halign(GTK_WIDGET(popup_menu), GTK_ALIGN_START);

	gtk_widget_set_parent(GTK_WIDGET(popup_menu), GTK_WIDGET(pane->view));
	g_signal_connect_swapped(pane->view, "destroy",
		G_CALLBACK(gtk_widget_unparent), popup_menu
	); // reference janitorial
	pane->rightclick = popup_menu;
}

static void
columnview_row_bind_attach_gesture(
		yaabegtk_commons const* const commons,
		GtkColumnViewRow* const view_row,
		void (*gesture_cb)( // function pointer
			GtkGesture*, gint,gdouble,gdouble,
			struct rightclick_pack*
			)
		) {
// since row_setup doesn't have the row widget created yet, we need to handle
// the setup in bind
	assert(NULL == g_object_get_data(G_OBJECT(view_row), "atui")); // flag

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
	struct rightclick_pack* const pack = cralloc(
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


inline static void
clipboard_set_text(
		char const* const text
		) {
	gdk_clipboard_set_text(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		text
	);
}
static void
right_click_paste_data(
		GObject* const clipboard,
		GAsyncResult* const async_data,
		GObject* const gatui,
		struct yaabegtk_commons const* commons
		) {
	bool const is_leaf = GATUI_IS_LEAF(gatui);
	assert(GATUI_IS_LEAF(gatui) || GATUI_IS_BRANCH(gatui));

	GError* err = NULL;
	char* const b64_text = gdk_clipboard_read_text_finish(
		GDK_CLIPBOARD(clipboard), async_data, &err
	);
	if (err) {
		generic_error_popup("clipboard error", err->message, commons->yaabe_gtk
		);
		g_error_free(err);
		return;
	}

	struct b64_header* b64_error = NULL;
	bool success;
	if (is_leaf) {
		success = gatui_leaf_value_from_base64(
			GATUI_LEAF(gatui), b64_text, &b64_error
		);
	} else {
		success = gatui_branch_from_base64(
			GATUI_BRANCH(gatui), b64_text, &b64_error
		);
	}
	if (success) {
		return;
	}

	GtkAlertDialog* error_popup;
	if (b64_error) {
		char const* name;
		if (is_leaf) {
			name = gatui_leaf_get_atui(GATUI_LEAF(gatui))->name;
		} else {
			name = gatui_branch_get_atui(GATUI_BRANCH(gatui))->name;
		}
		error_popup = gtk_alert_dialog_new(
			(char const* const[2]) {
				"Incompatible data for branch %s.",
				"Incompatible data for leaf %s.",
			}[is_leaf],
			name
		);
		free(b64_error);
	} else {
		error_popup = gtk_alert_dialog_new("Broken metadata.");
	}

	gtk_alert_dialog_show(
		error_popup,
		gtk_application_get_active_window(commons->yaabe_gtk)
	);
	g_object_unref(error_popup);
}
static void
branchleaf_right_click_paste_data_set_data(
		GObject* const clipboard,
		GAsyncResult* const async_data,
		gpointer const pack_ptr
		) {
// AsyncReadyCallback
	struct rightclick_pack const* const pack = pack_ptr;
	right_click_paste_data(clipboard, async_data, pack->obj, pack->commons);
}
static void
branchleaf_right_click_paste_data(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	gdk_clipboard_read_text_async(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		NULL,
		branchleaf_right_click_paste_data_set_data,
		pack_ptr
	);
}




static void
branch_right_click_copy_name(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	atui_branch const* const a_branch = gatui_branch_get_atui(pack->branch);
	clipboard_set_text(a_branch->name);
}
static void
branch_right_click_copy_struct_name(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	atui_branch const* const a_branch = gatui_branch_get_atui(pack->branch);
	clipboard_set_text(a_branch->origname);
}
static void
branch_right_click_copy_path(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	char* const pathstring = gatui_branch_to_path(pack->branch);
	clipboard_set_text(pathstring);
	free(pathstring);
}
static void
branch_right_click_copy_contiguous(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	char* const b64_text = gatui_branch_to_base64(pack->branch, false);
	if (b64_text) {
		clipboard_set_text(b64_text);
		g_free(b64_text);
	}
}
static void
branch_right_click_copy_leaves(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	char* const b64_text = gatui_branch_to_base64(pack->branch, true);
	if (b64_text) {
		clipboard_set_text(b64_text);
		g_free(b64_text);
	}
}
static void
branch_right_click_collapse_children(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	GtkTreeListRow* const tree_row = gtk_column_view_row_get_item(pack->row);
	atui_branch const* const a_branch = gatui_branch_get_atui(pack->branch);

	for (uint16_t i=0; i < a_branch->num_branches; i++) {
		GtkTreeListRow* child = gtk_tree_list_row_get_child_row(tree_row, i);
		gtk_tree_list_row_set_expanded(child, false);
		g_object_unref(child);
	}
}
static void
branch_right_click_expand_family(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	GtkTreeListRow* const tree_row = gtk_column_view_row_get_item(pack->row);

	gtk_tree_list_row_set_expanded(tree_row, false);
	gatui_branch_right_click_expand_family(pack->branch);
	gtk_tree_list_row_set_expanded(tree_row, true);
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

	GtkTreeListRow* const tree_row = gtk_column_view_row_get_item(pack->row);
	GATUIBranch* const g_branch = gtk_tree_list_row_get_item(tree_row);
	g_object_unref(g_branch); // we don't need a second reference.
	pack->branch = g_branch;

	// see also create_branches_rightclick_menu
	GActionEntry actions[8] = {
		{.name = "name",   .activate = branch_right_click_copy_name},
		{.name = "struct", .activate = branch_right_click_copy_struct_name},
		{.name = "path",   .activate = branch_right_click_copy_path},
	};
	uint8_t act_i = 3;
	atui_branch const* const a_branch = gatui_branch_get_atui(g_branch);
	if (a_branch->num_copyable_leaves || a_branch->table_size) {
		if (a_branch->num_copyable_leaves && ! a_branch->prefer_contiguous) {
			actions[act_i].name = "copy_leaves";
			actions[act_i].activate = branch_right_click_copy_leaves;
			act_i++;
		}
		if (a_branch->table_size) {
			actions[act_i].name = "copy_contiguous";
			actions[act_i].activate = branch_right_click_copy_contiguous;
			act_i++;
		}
		actions[act_i].name = "paste_data";
		actions[act_i].activate = branchleaf_right_click_paste_data;
		act_i++;
	};
	if (a_branch->num_branches) {
		if (gtk_tree_list_row_get_expanded(tree_row)) {
			actions[act_i].name = "collapse_children";
			actions[act_i].activate = branch_right_click_collapse_children;
			act_i++;
		}
		actions[act_i].name = "expand_family";
		actions[act_i].activate = branch_right_click_expand_family;
		act_i++;
	}
	assert(act_i <= lengthof(actions));

	struct pane_context const* const pane = &(pack->commons->branches);
	attach_actions_and_popup(actions,act_i,  pane,pack,  x,y);
}

void
branches_rightclick_row_bind(
		yaabegtk_commons const* const commons,
		GtkColumnViewRow* const view_row
		) {
	if (NULL == g_object_get_data(G_OBJECT(view_row), "atui")) {
		columnview_row_bind_attach_gesture(
			commons, view_row, branches_rightclick_popup
		);
	}
}
void
create_branches_rightclick_menu(
		yaabegtk_commons* const commons
		) {
	GMenu* const menu_model = g_menu_new();
	g_menu_append(menu_model, "Copy Name", "context.name");
	g_menu_append(menu_model, "Copy Struct Name", "context.struct");
	g_menu_append(menu_model, "Copy Path", "context.path");
	g_menu_append(menu_model, "Copy Leaves", "context.copy_leaves");
	g_menu_append(menu_model,"Copy Contiguous Data", "context.copy_contiguous");
	g_menu_append(menu_model, "Paste Data", "context.paste_data");
	g_menu_append(menu_model,"Collapse Children", "context.collapse_children");
	g_menu_append(menu_model, "Expand Family", "context.expand_family");
	// see also branches_rightclick_popup

	columnview_create_rightclick_popup(
		G_MENU_MODEL(menu_model), &commons->branches
	);
}



static void
leaf_right_click_copy_name(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	atui_leaf const* const a_leaf = gatui_leaf_get_atui(pack->leaf);
	clipboard_set_text(a_leaf->name);
}
static void
leaf_right_click_copy_path(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	char* const pathstring = gatui_leaf_to_path(pack->leaf);
	clipboard_set_text(pathstring);
	free(pathstring);
}

static void
leaf_right_click_copy_data(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	char* const b64_text = gatui_leaf_value_to_base64(pack->leaf);
	if (b64_text) {
		clipboard_set_text(b64_text);
		free(b64_text);
	}
}

static void
rightclick_selection_sterilise(
		GtkColumnView* const view
		) {
	// TODO hack: gtk_column_view_row_set_selectable is broken.
	// See `leaves_row_setup`
	// This is a part of a system that only allows a selection to happen upon
	// right-click.
	GtkSelectionModel* const model = gtk_column_view_get_model(view);
	gtk_single_selection_set_selected(
		GTK_SINGLE_SELECTION(model),
		GTK_INVALID_LIST_POSITION
	);
	g_signal_connect(model, "selection-changed",
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

	GtkTreeListRow* const tree_row = gtk_column_view_row_get_item(pack->row);
	GATUILeaf* const g_leaf = gtk_tree_list_row_get_item(tree_row);
	g_object_unref(g_leaf); // we don't need a second reference
	pack->leaf = g_leaf;

	// see also create_leaves_rightclick_menu
	GActionEntry actions[4] = {
		{.name = "name", .activate = leaf_right_click_copy_name},
		{.name = "path", .activate = leaf_right_click_copy_path},
	};
	uint8_t act_i = 2;
	atui_leaf const* const a_leaf = gatui_leaf_get_atui(g_leaf);
	if (a_leaf->num_bytes || _ATUI_BITCHILD == a_leaf->type.fancy) {
		actions[act_i].name = "copy_data";
		actions[act_i].activate = leaf_right_click_copy_data;
		act_i++;
		actions[act_i].name = "paste_data";
		actions[act_i].activate = branchleaf_right_click_paste_data;
		act_i++;
	}
	assert(act_i <= lengthof(actions));

	struct pane_context const* const pane = &(pack->commons->leaves);

	// disconnect the selection blocker, and then select
	// the reconnection gets handled with rightclick_selection_sterilise
	g_signal_handlers_disconnect_matched(
		gtk_column_view_get_model(pane->view), // SelectionModel
		G_SIGNAL_MATCH_FUNC,
		0, 0, NULL,
		gtk_selection_model_unselect_item,
		NULL
	);

	attach_actions_and_popup(actions,act_i,  pane,pack,  x,y);
}
void
leaves_rightclick_row_bind(
		yaabegtk_commons const* const commons,
		GtkColumnViewRow* const view_row
		) {
	if (NULL == g_object_get_data(G_OBJECT(view_row), "atui")) {
		columnview_row_bind_attach_gesture(
			commons, view_row, leaves_rightclick_popup
		);
	}
}
void
create_leaves_rightclick_menu(
		yaabegtk_commons* const commons
		) {
	GMenu* const menu_model = g_menu_new();
	g_menu_append(menu_model, "Copy Name", "context.name");
	g_menu_append(menu_model, "Copy Path", "context.path");
	g_menu_append(menu_model, "Copy Data", "context.copy_data");
	g_menu_append(menu_model, "Paste Data", "context.paste_data");
	// see also leaves_rightclick_popup

	columnview_create_rightclick_popup(
		G_MENU_MODEL(menu_model), &commons->leaves
	);

	g_signal_connect_swapped(commons->leaves.rightclick, "closed",
		G_CALLBACK(rightclick_selection_sterilise), commons->leaves.view
	);
}



static void
search_right_click_goto(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	struct atui_regex_node const* const node = gatui_regex_node_peek(
		pack->node
	);
	yaabe_gtk_scroll_to_object(pack->commons, node->gatui);
}
static void
search_right_click_copy_name(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	struct atui_regex_node const* const node = gatui_regex_node_peek(
		pack->node
	);
	char const* text;
	if (node->is_leaf) {
		text = gatui_leaf_get_atui(GATUI_LEAF(node->gatui))->name;
	} else {
		text = gatui_branch_get_atui(GATUI_BRANCH(node->gatui))->name;
	}
	clipboard_set_text(text);
}
static void
search_right_click_copy_path(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	struct atui_regex_node const* const node = gatui_regex_node_peek(
		pack->node
	);
	char* text;
	if (node->is_leaf) {
		text = gatui_leaf_to_path(GATUI_LEAF(node->gatui));
	} else {
		text = gatui_branch_to_path(GATUI_BRANCH(node->gatui));
	}
	clipboard_set_text(text);
	free(text);
}
static void
search_right_click_copy_data(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	struct atui_regex_node const* const node = gatui_regex_node_peek(
		pack->node
	);
	char* text;
	if (node->is_leaf) {
		text = gatui_leaf_value_to_base64(GATUI_LEAF(node->gatui));
	} else {
		text = gatui_branch_to_base64(GATUI_BRANCH(node->gatui), false);
	}
	clipboard_set_text(text);
	free(text);
}
static void
search_right_click_paste_data_set_data(
		GObject* const clipboard,
		GAsyncResult* const async_data,
		gpointer const pack_ptr
		) {
// AsyncReadyCallback
	struct rightclick_pack const* const pack = pack_ptr;
	struct atui_regex_node const* const node = gatui_regex_node_peek(
		pack->node
	);
	right_click_paste_data(clipboard, async_data, node->gatui, pack->commons);
}
static void
search_right_click_paste_data(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	gdk_clipboard_read_text_async(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		NULL,
		search_right_click_paste_data_set_data,
		pack_ptr
	);
}
static void
search_rightclick_popup(
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

	pack->node = gtk_column_view_row_get_item(pack->row);

	// see also create_leaves_rightclick_menu
	GActionEntry actions[5] = {
		{.name = "goto", .activate = search_right_click_goto},
		{.name = "name", .activate = search_right_click_copy_name},
		{.name = "path", .activate = search_right_click_copy_path},
	};
	uint8_t act_i = 3;

	struct atui_regex_node const* const node = gatui_regex_node_peek(
		pack->node
	);
	bool has_data = false;
	if (node->is_leaf) {
		atui_leaf const* const a_leaf = gatui_leaf_get_atui(GATUI_LEAF(
			node->gatui
		));
		has_data = (a_leaf->num_bytes || _ATUI_BITCHILD == a_leaf->type.fancy);
	} else {
		atui_branch const* const a_branch = gatui_branch_get_atui(GATUI_BRANCH(
			node->gatui
		));
		has_data = (0 < a_branch->table_size);
	}
	if (has_data) {
		actions[act_i].name = "copy_data";
		actions[act_i].activate = search_right_click_copy_data;
		act_i++;
		actions[act_i].name = "paste_data";
		actions[act_i].activate = search_right_click_paste_data;
		act_i++;
	}
	assert(act_i <= lengthof(actions));

	struct pane_context const* const pane = &(pack->commons->search.pane);

	// disconnect the selection blocker, and then select
	// the reconnection gets handled with rightclick_selection_sterilise
	g_signal_handlers_disconnect_matched(
		gtk_column_view_get_model(pane->view), // SelectionModel
		G_SIGNAL_MATCH_FUNC,
		0, 0, NULL,
		gtk_selection_model_unselect_item,
		NULL
	);
	attach_actions_and_popup(actions,act_i,  pane,pack,  x,y);
}

void
search_rightclick_row_bind(
		yaabegtk_commons const* const commons,
		GtkColumnViewRow* const view_row
		) {
	if (NULL == g_object_get_data(G_OBJECT(view_row), "atui")) {
		columnview_row_bind_attach_gesture(
			commons, view_row, search_rightclick_popup
		);
	}
}
void
create_search_rightclick_menu(
		yaabegtk_commons* const commons
		) {
	GMenu* const menu_model = g_menu_new();
	g_menu_append(menu_model, "Go To", "context.goto");
	g_menu_append(menu_model, "Copy Name", "context.name");
	g_menu_append(menu_model, "Copy Path", "context.path");
	g_menu_append(menu_model, "Copy Data", "context.copy_data");
	g_menu_append(menu_model, "Paste Data", "context.paste_data");
	// see also search_rightclick_popup

	columnview_create_rightclick_popup(
		G_MENU_MODEL(menu_model), &commons->search.pane
	);

	g_signal_connect_swapped(commons->search.pane.rightclick, "closed",
		G_CALLBACK(rightclick_selection_sterilise), commons->search.pane.view
	);
}

/*
static void
leaves_row_setup(
		void const* const _null __unused, // swapped-signal:: with factory
		GtkColumnViewRow* const view_row
		) {
	gtk_column_view_row_set_selectable(view_row, false);
	// TODO gtk_column_view_row_set_selectable is broken, even in bind.
	// For a workaround see where `gtk_selection_model_unselect_item` and
	// `rightclick_selection_sterilise` are used.
}
*/
