#include <zlib.h>

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
	uint8_t bytes[] __counted_by(num_bytes);
};
#pragma pack(pop)

static gchar*
b64_packet_encode(
		void const* const payload,
		size_t const payload_size,
		enum b64_header_target const target,
		uint8_t const num_segments
		) {
	size_t const packet_size = sizeof(struct b64_header) + payload_size;
	union {
		void* raw;
		struct b64_header* header;
	} const h = {
		.header = cralloc(packet_size)
	};

	h.header->header_ver = 0;
	h.header->target = target;
	h.header->num_segments = num_segments;
	h.header->num_bytes = payload_size;
	memcpy(h.header->bytes, payload, payload_size);
	h.header->crc = crc32(
		0,
		(h.raw + sizeof(h.header->crc)), // exclude crc
		(packet_size - sizeof(h.header->crc))
	);

	gchar* const b64_text = g_base64_encode(h.raw, packet_size);
	free(h.header);
	return b64_text;
}
static bool // decode error
b64_packet_decode(
		char const* const b64_text,
		struct b64_header** const header_out
		) {
	size_t b64_num_bytes = 0;
	union {
		void* raw;
		struct b64_header* header;
	} const h = {
		.raw = g_base64_decode(b64_text, &b64_num_bytes)
	};

	if (0 == b64_num_bytes) {
		return true;
	}
	*header_out = h.header;
	if (b64_num_bytes < sizeof(*h.header)) {
		return true;
	}
	if (b64_num_bytes < (h.header->num_bytes + sizeof(*h.header))) {
		return true;
	}
	uint32_t const crc = crc32(
		0,
		(h.raw + sizeof(h.header->crc)),
		(sizeof(*h.header)-sizeof(h.header->crc)  +  h.header->num_bytes)
	);
	if (crc != h.header->crc) {
		return true;
	}

	// strict compliance
	if ((B64_BRANCH_CONTIGUOUS == h.header->target)
			&& (1 != h.header->num_segments)
			) {
		return true;
	}
	if ((B64_LEAF==h.header->target) && (1!=h.header->num_segments)) {
		return true;
	}
	return false;
}


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
		GSimpleAction* const action __unused,
		GVariant* const parameter __unused,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	GVariant* val = NULL;
	uint16_t num_copyable_leaves;
	gatui_branch_get_leaves_memory_package(
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

	GtkAlertDialog* error_popup;
	struct b64_header* header = NULL;
	bool const decode_error = b64_packet_decode(b64_text, &header);
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
			header->bytes, header->num_bytes,
			false,
			(GDestroyNotify) free, header
		);
		g_free(raw_type);
		if (header->target == B64_BRANCH_CONTIGUOUS) {
			if (header->num_bytes != a_branch->table_size) {
				error_popup = gtk_alert_dialog_new(
					"%s has %zu contiguous bytes, but pasted data is %u bytes.",
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

	GtkAlertDialog* error_popup;
	struct b64_header* header = NULL;
	bool const decode_error = b64_packet_decode(b64_text, &header);
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

	uint32_t const leaf_num_bytes = gatui_leaf_get_atui(pack->leaf)->num_bytes;
	if (a_leaf->type.fancy == ATUI_STRING) {
		void const* const bytes = header->bytes;
		size_t const str_length = strnlen(bytes,  header->num_bytes
		);
		if (str_length < header->num_bytes) {
			gatui_leaf_set_value_from_text(pack->leaf, bytes);
			goto success_exit;
		} else {
			error_popup = gtk_alert_dialog_new(
				"%s takes a string, but the base64 data does not decode to"
				" a proper string.",
				 a_leaf->name
			);
			goto error_exit;
		}
	} else if (header->num_bytes == leaf_num_bytes) {
		GVariantType* const raw_type = g_variant_type_new("ay");
		GVariant* const new_val = g_variant_new_from_data(
			raw_type,
			header->bytes, header->num_bytes,
			false,
			(GDestroyNotify) free, header
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
