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
		GATUIBranch* branch;
		GATUILeaf* leaf;
	};
};


inline static void
calculate_rightclick_popup_location(
		GtkGesture* const click_sense __unused,
		gdouble const x,
		gdouble const y,
		struct pane_context const* const context,
		GtkWidget* const row_widget
		) {
	// x,y is relative to the widget.
	// x,y is from row widget, translate it to the view widget.
	graphene_point_t view_coords;
	bool const computed __unused = gtk_widget_compute_point(
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

inline static void
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
}







static void
branch_right_click_copy_name(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
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
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
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
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	char* const pathstring = gatui_branch_to_path(pack->branch);
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
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	char* const b64_text = gatui_branch_to_base64(pack->branch, false);
	if (b64_text) {
		gdk_clipboard_set_text(
			gdk_display_get_clipboard(
				gdk_display_get_default()
			),
			b64_text
		);
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
		gdk_clipboard_set_text(
			gdk_display_get_clipboard(
				gdk_display_get_default()
			),
			b64_text
		);
		g_free(b64_text);
	}
}

static void
branch_right_click_paste_data_set_data(
		GObject* const clipboard,
		GAsyncResult* const async_data,
		gpointer const pack_ptr
		) {
// AsyncReadyCallback
	struct rightclick_pack const* const pack = pack_ptr;

	GError* err = NULL;
	char* const b64_text = gdk_clipboard_read_text_finish(
		GDK_CLIPBOARD(clipboard), async_data, &err
	);
	if (err) {
		generic_error_popup(
			"clipboard error", err->message, pack->commons->yaabe_gtk
		);
		g_error_free(err);
		return;
	}

	struct b64_header* b64_error = NULL;
	bool const success = gatui_branch_from_base64(
		pack->branch, b64_text, &b64_error
	);
	if (success) {
		return;
	}

	GtkAlertDialog* error_popup;
	if (b64_error) {
		error_popup = gtk_alert_dialog_new(
			"Incompatible data for branch %s.",
			gatui_branch_get_atui(pack->branch)->name
		);
		free(b64_error);
	} else {
		error_popup = gtk_alert_dialog_new("Broken metadata.");
	}

	gtk_alert_dialog_show(
		error_popup,
		gtk_application_get_active_window(pack->commons->yaabe_gtk)
	);
	g_object_unref(error_popup);
}
static void
branch_right_click_paste_data(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
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
	struct pane_context const* const branches_context = &(
		pack->commons->branches
	);

	// connect actions
	GtkTreeListRow* const tree_row = gtk_column_view_row_get_item(pack->row);
	GATUIBranch* const g_branch = gtk_tree_list_row_get_item(tree_row);
	g_object_unref(g_branch); // we don't need a second reference.
	pack->branch = g_branch;

	atui_branch const* const branch = gatui_branch_get_atui(g_branch);
	// see also create_branches_rightclick_menu
	GActionEntry actions[8] = {
		{.name = "name",   .activate = branch_right_click_copy_name},
		{.name = "struct", .activate = branch_right_click_copy_struct_name},
		{.name = "path",   .activate = branch_right_click_copy_path},
	};
	uint8_t act_i = 3;
	if (branch->num_copyable_leaves || branch->table_size) {
		if (branch->num_copyable_leaves && ! branch->prefer_contiguous) {
			actions[act_i].name = "copy_leaves";
			actions[act_i].activate = branch_right_click_copy_leaves;
			act_i++;
		}
		if (branch->table_size) {
			actions[act_i].name = "copy_contiguous";
			actions[act_i].activate = branch_right_click_copy_contiguous;
			act_i++;
		}
		actions[act_i].name = "paste_data";
		actions[act_i].activate = branch_right_click_paste_data;
		act_i++;
	};
	if (branch->num_branches) {
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
	GActionMap* const action_set = G_ACTION_MAP(g_simple_action_group_new());
	g_action_map_add_action_entries(action_set,
		actions, act_i,
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
void
branches_rightclick_row_bind(
		yaabegtk_commons const* const commons,
		GtkColumnViewRow* const view_row
		) {
	columnview_row_bind_attach_gesture(
		commons, view_row, branches_rightclick_popup
	);
}
void
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
	g_menu_append(menu_model, "Collapse Children", "branch.collapse_children");
	g_menu_append(menu_model, "Expand Family", "branch.expand_family");
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
	gdk_clipboard_set_text(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		a_leaf->name
	);
}
static void
leaf_right_click_copy_path(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;

	char* const pathstring = gatui_leaf_to_path(pack->leaf);

	gdk_clipboard_set_text(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		pathstring
	);

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
		gdk_clipboard_set_text(
			gdk_display_get_clipboard(
				gdk_display_get_default()
			),
			b64_text
		);
		g_free(b64_text);
	}
}
static void
leaf_right_click_paste_data_set_data(
		GObject* const clipboard,
		GAsyncResult* const async_data,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;

	GError* err = NULL;
	char* const b64_text = gdk_clipboard_read_text_finish(
		GDK_CLIPBOARD(clipboard), async_data, &err
	);
	if (err) {
		generic_error_popup(
			"clipboard error", err->message, pack->commons->yaabe_gtk
		);
		g_error_free(err);
		return;
	}

	struct b64_header* b64_error = NULL;
	bool const success = gatui_leaf_value_from_base64(
		pack->leaf, b64_text, &b64_error
	);
	if (success) {
		return;
	}

	GtkAlertDialog* error_popup;
	if (b64_error) {
		error_popup = gtk_alert_dialog_new(
			"Incompatible data for leaf %s.",
			gatui_leaf_get_atui(pack->leaf)->name
		);
		free(b64_error);
	} else {
		error_popup = gtk_alert_dialog_new("Broken metadata.");
	}

	gtk_alert_dialog_show(
		error_popup,
		gtk_application_get_active_window(pack->commons->yaabe_gtk)
	);
	g_object_unref(error_popup);
}
static void
leaf_right_click_paste_data(
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
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
		GtkPopover* const rightclick __unused,
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


	GtkTreeListRow* const tree_row = gtk_column_view_row_get_item(pack->row);
	GATUILeaf* const g_leaf = gtk_tree_list_row_get_item(tree_row);
	g_object_unref(g_leaf); // we don't need a second reference
	pack->leaf = g_leaf;
	atui_leaf const* const a_leaf = gatui_leaf_get_atui(g_leaf);


	// see also create_leaves_rightclick_menu
	GActionEntry actions[4] = {
		{.name = "name", .activate = leaf_right_click_copy_name},
		{.name = "path", .activate = leaf_right_click_copy_path},
	};
	uint8_t act_i = 2;

	if (a_leaf->num_bytes || a_leaf->type.fancy == _ATUI_BITCHILD) {
		actions[act_i].name = "copy_data";
		actions[act_i].activate = leaf_right_click_copy_data;
		act_i++;
		actions[act_i].name = "paste_data";
		actions[act_i].activate = leaf_right_click_paste_data;
		act_i++;
	}
	assert(act_i <= lengthof(actions));
	GActionMap* const action_set = G_ACTION_MAP(g_simple_action_group_new());
	g_action_map_add_action_entries(action_set,
		actions, act_i,
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
void
leaves_rightclick_row_bind(
		yaabegtk_commons const* const commons,
		GtkColumnViewRow* const view_row
		) {
	columnview_row_bind_attach_gesture(
		commons, view_row, leaves_rightclick_popup
	);
}
void
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
/*
static void
leaves_row_setup(
		void const* const _null __unused, // swapped-signal:: with factory
		GtkColumnViewRow* const view_row
		) {
	gtk_column_view_row_set_selectable(view_row, false);
	// TODO gtk_column_view_row_set_selectable is broken, even in bind.
	// For a workaround see where `gtk_selection_model_unselect_item` and
	// `leaves_rightclick_selection_sterilise` are used.
}
*/
