#include "atomtree.h"
#include "atui.h"
#include "yaabe_gtk4.h"

static char8_t const yaabe_name[] = "YAABE BIOS Editor";
#define PATHBAR_BUFFER_SIZE 256

struct pane_context {
	GtkColumnView* view; // so branches can set leaves, and loading bios
	GtkPopover* rightclick;
};
typedef struct yaabegtk_commons { // global state tracker
	struct atom_tree* atomtree_root;
	GtkApplication* yaabe_gtk;

	GtkEditable* pathbar;

	struct pane_context branches;
	struct pane_context leaves;

	// For gtk_widget_set_sensitive() -- don't allow when no bios is loaded
	GtkWidget* save_buttons;
	GtkWidget* reload_button;

	char8_t pathbar_string[PATHBAR_BUFFER_SIZE];
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
	GObject* gobj_atui; // obtainable from row anyway; for convenience
};

static void
_atui_destroy_leaves_with_gtk(
		atui_leaf* const leaves,
		uint16_t const num_leaves
		) {
	atui_leaf* leaf = leaves;
	atui_leaf* leaf_end = leaves + num_leaves;
	for (; leaf < leaf_end; leaf++) {
		if (leaf->child_gobj_cache) {
			for (uint16_t g=0; g < leaf->num_gobj; g++) {
				g_object_unref(leaf->child_gobj_cache[g]);
			}
			free(leaf->child_gobj_cache);
		}
		if (leaf->num_child_leaves) {
			_atui_destroy_leaves_with_gtk(
				leaf->child_leaves, leaf->num_child_leaves
			);
			free(leaf->child_leaves);
		}
		if (leaf->enum_model) {
			g_object_unref(leaf->enum_model);
		}
		if (leaf->self_gobj) {
			g_object_unref(leaf->self_gobj);
		}
	}
}
void
atui_destroy_tree_with_gtk(
		atui_branch* const tree
		) {
// Free and unref all the atui branches/leaves and the GTK-relevant stuff
// See also destroy_atomtree_with_gtk

	if (tree->child_gobj_cache) {
		for (uint16_t g=0; g < tree->num_gobj; g++) {
			g_object_unref(tree->child_gobj_cache[g]);
		}
		free(tree->child_gobj_cache);
	}
	if (tree->leaves_model) {
		g_object_unref(tree->leaves_model);
	}
	if (tree->self_gobj) {
		g_object_unref(tree->self_gobj);
	}

	_atui_destroy_leaves_with_gtk(tree->leaves, tree->leaf_count);

	atui_branch* child_branch;
	while (tree->max_all_branch_count) {
		(tree->max_all_branch_count)--;
		child_branch = tree->all_branches[tree->max_all_branch_count];
		if (child_branch) {
			atui_destroy_tree_with_gtk(child_branch);
		}
	}

	free(tree);

}
void
destroy_atomtree_with_gtk(
		struct atom_tree* const atree,
		bool const free_bios
		) {
// Free and unref
	if (atree) {
		atui_destroy_tree_with_gtk(atree->atui_root);

		if (free_bios) {
			free(atree->alloced_bios);
			if (atree->biosfile) {
				g_object_unref(atree->biosfile);
			}
		}

		free(atree);
	}
}



static void
pathbar_update_path(
		GtkSingleSelection* const model,
		guint const position,
		guint const n_items,
		yaabegtk_commons* const commons
		) {
// callback; sets path based on branches selection
	GObject* const gobj_branch = gtk_tree_list_row_get_item(GTK_TREE_LIST_ROW(
		gtk_single_selection_get_selected_item(model)
	));
	char8_t* eos = atui_branch_to_path(
		g_object_get_data(gobj_branch, "branch"),
		commons->pathbar_string
	);
	assert(eos < (commons->pathbar_string + PATHBAR_BUFFER_SIZE));
	g_object_unref(gobj_branch);
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
	struct atui_path_map* const map = path_to_atui(
		editable_text,
		commons->atomtree_root->atui_root
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
		target = map->branch_path[map->branch_depth - 1]->self_gobj;
		questioned = gtk_tree_list_row_get_item(GTK_TREE_LIST_ROW(
			gtk_single_selection_get_selected_item(GTK_SINGLE_SELECTION(
				branch_model
			))
		));
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
				target = map->branch_path[depth_i]->self_gobj;
				while (true) {
					model_i++;
					tree_item = GTK_TREE_LIST_ROW(
						g_list_model_get_object(branch_model, model_i)
					);
					questioned = gtk_tree_list_row_get_item(tree_item);
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
				target = map->leaf_path[depth_i]->self_gobj;
				while (true) {
					model_i++;
					tree_item = GTK_TREE_LIST_ROW(
						g_list_model_get_object(leaf_model, model_i)
					);
					questioned = gtk_tree_list_row_get_item(tree_item);
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
atui_leaves_pullin_gliststore(
		atui_leaf* const leaves,
		GListStore* const list,
		uint16_t const num_leaves
		) {
// If the parent leaf has children that aren't adjacent, but the parent is
// labeled with ATUI_SUBONLY, pull them in.
	GObject* gobj_child;
	atui_leaf* leaf;
	for(uint16_t i=0; i < num_leaves; i++) {
		leaf = &(leaves[i]);
		if (leaf->type & ATUI_NODISPLAY) {
			// ignore the leaf
		} else if (leaf->type & ATUI_SUBONLY) {
			assert(leaf->type & (ATUI_BITFIELD|ATUI_INLINE|ATUI_DYNARRAY));
			if (leaf->type & ATUI_INLINE) {
				atui_branch* const branch = *(leaf->inline_branch);
				atui_leaves_pullin_gliststore(
					branch->leaves, list, branch->leaf_count
				);
			//} else if (leaf->type & (ATUI_BITFIELD|ATUI_DYNARRAY)) {
			} else {
				atui_leaves_pullin_gliststore(
					leaf->child_leaves, list, leaf->num_child_leaves
				);
			}
		} else {
			gobj_child = g_object_new(G_TYPE_OBJECT, NULL);
			g_object_set_data(gobj_child, "leaf", leaf);
			g_list_store_append(list, gobj_child);
			leaf->self_gobj = gobj_child;
			//g_object_unref(gobj_child); // keep ref for self
		}
	}
}
inline static GListModel*
atui_leaves_to_glistmodel(
		atui_leaf* const children,
		uint16_t const num_children
		) {
// Creates a rudimentary model from an array of atui_leaf's
	GListStore* const child_list = g_list_store_new(G_TYPE_OBJECT);
	atui_leaves_pullin_gliststore(children, child_list, num_children);
	return G_LIST_MODEL(child_list);
}
static GListModel*
leaves_treelist_generate_children(
		gpointer const parent_ptr,
		gpointer const const d // unused
		) {
// GtkTreeListModelCreateModelFunc for leaves
// Creates the children models for the collapsable tree, of the leaves pane.
	GListModel* children_model = NULL;

	GObject* const gobj_parent = parent_ptr;
	atui_leaf* const parent = g_object_get_data(gobj_parent, "leaf");

	if (parent->type & (ATUI_BITFIELD|ATUI_INLINE|ATUI_DYNARRAY)
			&& (-1 < parent->num_gobj)
			) {
		if (NULL == parent->child_gobj_cache) {
			atui_leaf* leaves;
			uint16_t num_leaves;
			if (parent->type & ATUI_INLINE) {
				atui_branch* const branch = *(parent->inline_branch);
				leaves = branch->leaves;
				num_leaves = branch->leaf_count;
			} else {
			//} else if (parent->type & (ATUI_BITFIELD | ATUI_DYNARRAY)) {
				leaves = parent->child_leaves;
				num_leaves = parent->num_child_leaves;
			}
			if (num_leaves) {
				children_model = atui_leaves_to_glistmodel(leaves, num_leaves);
				parent->num_gobj = g_list_model_get_n_items(children_model);
				parent->child_gobj_cache = malloc(
					parent->num_gobj * sizeof(GObject*)
				);
				uint16_t i;
				for (i=0; i < parent->num_gobj; i++) {
					// g_list_model_get_item refs the gobject for us
					parent->child_gobj_cache[i] = g_list_model_get_item(
						children_model, i
					);
				}
				assert(i < INT16_MAX); // 32k leaves?!
			} else {
				parent->num_gobj = -1; // flag for dead-ends
			}
		} else {
			GListStore* const children = g_list_store_new(G_TYPE_OBJECT);
			g_list_store_splice(children,0,  0,
				(void**)parent->child_gobj_cache, parent->num_gobj
			);
			children_model = G_LIST_MODEL(children);
		}
	}
	return children_model;
}
inline static void
branchleaves_to_treemodel(
		atui_branch* const branch
		) {
// Turns the 'level 0' leaves of a branch into a model for the leaves pane.
// Also generates its cache.
	branch->leaves_model = GTK_SELECTION_MODEL(
		gtk_no_selection_new(G_LIST_MODEL(
			gtk_tree_list_model_new(
				atui_leaves_to_glistmodel(branch->leaves, branch->leaf_count),
				false, true, leaves_treelist_generate_children, NULL,NULL
			)
		))
	); // the later models take ownership of the earlier


	g_object_ref(branch->leaves_model); // to cache
}
static void
branch_selection_sets_leaves_list(
		GtkSingleSelection* const model,
		guint const position,
		guint const n_items,
		yaabegtk_commons* const commons
		) {
// Signal callback
// Change the leaves pane's model based on the what is selected in brances
	GtkTreeListRow* const tree_row = gtk_single_selection_get_selected_item(
		model
	);
	GObject* const gobj_branch = gtk_tree_list_row_get_item(tree_row);
	atui_branch* const branch = g_object_get_data(gobj_branch, "branch");
	g_object_unref(gobj_branch);

	if (NULL == branch->leaves_model) { // if not cached, generate.
		branchleaves_to_treemodel(branch);
	}

	gtk_column_view_set_model(commons->leaves.view, branch->leaves_model);
}
static void
atui_branches_pullin_gliststore(
		atui_branch const* const parent,
		GListStore* const list
		) {
	GObject* gobj_child;
	atui_branch* child;
	uint16_t i;
	for (i=0; i < parent->num_inline_branches; i++) {
		atui_branches_pullin_gliststore(parent->inline_branches[i], list);
	}
	for (i=0; i < parent->num_branches; i++) {
		gobj_child = g_object_new(G_TYPE_OBJECT, NULL);
		g_object_set_data(gobj_child, "branch", parent->child_branches[i]);
		g_list_store_append(list, gobj_child);
		parent->child_branches[i]->self_gobj = gobj_child;
		//g_object_unref(gobj_child); // keep ref for self
	}
}
static GListModel*
branches_treelist_generate_children(
		gpointer const parent_ptr,
		gpointer const const data
		) {
// GtkTreeListModelCreateModelFunc for branches
// Creates the children models for the collapsable tree, of the branches pane.
	GObject* const gobj_parent = parent_ptr;
	atui_branch* const parent = g_object_get_data(gobj_parent, "branch");

	GListModel* children_model = NULL;

	if (parent->max_all_branch_count && (-1 < parent->num_gobj)) {
		GListStore* const children = g_list_store_new(G_TYPE_OBJECT);
		if (NULL == parent->child_gobj_cache) {
			atui_branches_pullin_gliststore(parent, children);
			children_model = G_LIST_MODEL(children);
			
			parent->num_gobj = g_list_model_get_n_items(children_model);
			if (parent->num_gobj) {
				parent->child_gobj_cache = malloc(
					parent->num_gobj * sizeof(GObject*)
				);
				uint16_t i;
				for (i=0; i < parent->num_gobj; i++) {
					// g_list_model_get_item refs the gobject for us
					parent->child_gobj_cache[i] = g_list_model_get_item(
						children_model, i
					);
				}
				assert(i < INT16_MAX); // 32k branches?!
			} else {
				g_object_unref(children_model);
				children_model = NULL;
				parent->num_gobj = -1; // flag for dead-ends
			}
		} else {
			g_list_store_splice(children,0,  0,
				(void**)parent->child_gobj_cache, parent->num_gobj
			);
			children_model = G_LIST_MODEL(children);
		}
	}
	return children_model;
}
inline static GtkSelectionModel*
create_root_model(
		yaabegtk_commons* const commons
		) {
// Generate the very first model, of the tippy top of the tree, for the
// branches pane
	atui_branch* const atui_root = commons->atomtree_root->atui_root;

	GObject* const gbranch = g_object_new(G_TYPE_OBJECT, NULL);
	g_object_set_data(gbranch, "branch", atui_root);
	GListStore* const ls_model = g_list_store_new(G_TYPE_OBJECT);
	g_list_store_append(ls_model, gbranch);
	atui_root->self_gobj = gbranch;
	//g_object_unref(gbranch); // keep ref for self

	// TreeList, along with branches_treelist_generate_children, creates our
	// collapsable model.
	GtkSingleSelection* const sel_model = gtk_single_selection_new(G_LIST_MODEL(
		gtk_tree_list_model_new(
			G_LIST_MODEL(ls_model),  false, true,
			branches_treelist_generate_children,  NULL,NULL
		)
	)); // the later models take ownership of the earlier

	g_object_connect(sel_model,
		"signal::selection-changed",
			G_CALLBACK(branch_selection_sets_leaves_list), commons,
		"signal::selection-changed", G_CALLBACK(pathbar_update_path), commons,
		NULL
	);

	return GTK_SELECTION_MODEL(sel_model);
	// Does not need to be unref'd if used with a new().
	// Needs to be unref'd if used with a set().
}
static void
create_and_set_active_atui_model(
		yaabegtk_commons* const commons
		) {
// create and set the main branch model
	GtkSelectionModel* const branches_model = create_root_model(commons);
	gtk_column_view_set_model(commons->branches.view, branches_model);
	g_object_unref(branches_model);

	// TODO divorce into notify::model signal/callback in create_branches_pane?
	atui_branch* const root = commons->atomtree_root->atui_root;
	assert(NULL == root->leaves_model);
	branchleaves_to_treemodel(root);
	gtk_column_view_set_model(commons->leaves.view, root->leaves_model);

	char8_t* eos = atui_branch_to_path(root, commons->pathbar_string);
	assert(eos < (commons->pathbar_string + PATHBAR_BUFFER_SIZE));

	gtk_editable_set_text(commons->pathbar, commons->pathbar_string);

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
	g_signal_connect_swapped(context->view, // reference janitorial
		"destroy", G_CALLBACK(gtk_widget_unparent), popup_menu
	);
	context->rightclick = popup_menu;
}
static void
free_closure(
		gpointer data,
		GClosure* closure
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

		g_signal_connect_data(click_sense,
			"pressed", G_CALLBACK(gesture_cb), pack,
			free_closure,
			G_CONNECT_DEFAULT
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

	g_signal_connect_swapped(path_bar,
		"activate", G_CALLBACK(pathbar_sets_branch_selection), commons
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
		GtkListItem* const column_cell
		) {
//TODO use https://docs.gtk.org/gtk4/class.Inscription.html
	GtkWidget* const label = gtk_label_new(NULL);
	gtk_label_set_xalign(GTK_LABEL(label), 0);
	gtk_list_item_set_child(column_cell, label);
}
static void
tree_label_column_setup(
		void const* const _null, // swapped-signal:: with factory
		GtkListItem* const column_cell
		) {
// setup to spawn a UI skeleton
	GtkWidget* const label = gtk_label_new(NULL);
	gtk_label_set_xalign(GTK_LABEL(label), 0);

	GtkWidget* const expander = gtk_tree_expander_new();
	gtk_tree_expander_set_indent_for_icon(GTK_TREE_EXPANDER(expander), true);
	gtk_tree_expander_set_child(GTK_TREE_EXPANDER(expander), label);
	gtk_list_item_set_child(column_cell, expander);
}

static void
leaves_name_column_bind(
		void const* const _null, // swapped-signal:: with factory
		GtkListItem* const column_cell
		) {
// bind data to the UI skeleton
	GtkTreeListRow* const tree_row = gtk_list_item_get_item(column_cell);
	GObject* const gobj_leaf = gtk_tree_list_row_get_item(tree_row);
	atui_leaf* const leaf = g_object_get_data(gobj_leaf, "leaf");
	g_object_unref(gobj_leaf);

	GtkTreeExpander* const expander = GTK_TREE_EXPANDER(
		gtk_list_item_get_child(column_cell)
	);
	gtk_tree_expander_set_list_row(expander, tree_row);

	GtkWidget* const label = gtk_tree_expander_get_child(expander);
	gtk_label_set_text(GTK_LABEL(label), leaf->name);
	uint8_t const current_lang = LANG_ENGLISH;
	gtk_widget_set_tooltip_text(label, leaf->description[current_lang]);
}
inline static void
leaf_sets_editable(
		atui_leaf const* const leaf,
		GtkEditable* const editable
		) {
	char8_t stack_buff[ATUI_LEAVES_STR_BUFFER];
	stack_buff[0] = '\0';
	char8_t* buff = stack_buff;
	uint16_t const has_mallocd = atui_leaf_to_text(leaf, &buff);
	gtk_editable_set_text(editable, buff);
	if (has_mallocd) {
		free(buff);
	}
}
static void
leaves_editable_stray_reset(
		GtkListItem* const column_cell
		) {
// If the value wasn't applied with enter, sync the text back to the actual
// data when keyboard leaves the textbox
	GtkTreeListRow* const tree_row = gtk_list_item_get_item(column_cell);
	GObject* const gobj_leaf = gtk_tree_list_row_get_item(tree_row);
	atui_leaf const* const leaf = g_object_get_data(gobj_leaf, "leaf");
	g_object_unref(gobj_leaf);

	GtkEditable* const editable = GTK_EDITABLE(
		gtk_stack_get_child_by_name(
			GTK_STACK(gtk_list_item_get_child(column_cell)), "text"
		)
	); // enum and text share same EntryBuffer

	leaf_sets_editable(leaf, editable);
}
static void
editable_sets_leaf(
		GtkEditable* const editable,
		GtkListItem* const column_cell
		) {
// Only way to apply the value is to hit enter
	GtkTreeListRow* const tree_row = gtk_list_item_get_item(column_cell);
	GObject* const gobj_leaf = gtk_tree_list_row_get_item(tree_row);
	atui_leaf* const leaf = g_object_get_data(gobj_leaf, "leaf");
	g_object_unref(gobj_leaf);

	atui_leaf_from_text(leaf, gtk_editable_get_text(editable));
	leaf_sets_editable(leaf, editable);
}

static void
enum_label_column_bind(
		void const* const _null, // swapped-signal:: with factory
		GtkListItem* const column_cell
		) {
// bind
	GtkLabel* const label = GTK_LABEL(gtk_list_item_get_child(column_cell));

	GObject* const enum_gobj = gtk_list_item_get_item(column_cell);
	struct atui_enum_entry const* const enum_entry = g_object_get_data(
		enum_gobj, "enum"
	);
	atui_leaf const* const leaf = g_object_get_data(enum_gobj, "leaf");
	char8_t stack_buff[ATUI_LEAVES_STR_BUFFER];
	stack_buff[0] = '\0';
	atui_enum_entry_to_text(stack_buff, leaf, enum_entry);
	gtk_label_set_text(label, stack_buff);
	uint8_t const current_lang = LANG_ENGLISH;
	gtk_widget_set_tooltip_text(
		GTK_WIDGET(label), enum_entry->description[current_lang]
	);

	// g_object_unref(enum_gobj); // no need to unref from list_item_get_item
}
static void
enum_list_sets_editable(
		GtkListView* const enum_list,
		guint const position,
		GtkEditable* const editable
		) {
	GObject* const enum_gobj = gtk_single_selection_get_selected_item(
		GTK_SINGLE_SELECTION(gtk_list_view_get_model(enum_list))
	);
	struct atui_enum_entry const* const enum_entry = g_object_get_data(
		enum_gobj, "enum"
	);
	atui_leaf const* const leaf = g_object_get_data(enum_gobj, "leaf");
	char8_t stack_buff[ATUI_LEAVES_STR_BUFFER];
	stack_buff[0] = '\0';
	atui_enum_entry_to_text(stack_buff, leaf, enum_entry);
	gtk_editable_set_text(editable, stack_buff);
	// g_object_unref(enum_gobj); // no need to unref from single..get_selected
}
static void
enum_list_sets_leaf(
		GtkListView* const enum_list
		) {
	GObject* const enum_gobj = gtk_single_selection_get_selected_item(
		GTK_SINGLE_SELECTION(gtk_list_view_get_model(enum_list))
	);
	struct atui_enum_entry const* const enum_entry = g_object_get_data(
		enum_gobj, "enum"
	);
	atui_leaf* const leaf = g_object_get_data(
		enum_gobj, "leaf"
	);
	if (leaf->type & ATUI_SIGNED) {
		atui_leaf_set_val_signed(leaf, enum_entry->val);
	} else {
		atui_leaf_set_val_unsigned(leaf, enum_entry->val);
	}
	// g_object_unref(enum_gobj); // no need to unref from single..get_selected
}
static void
enummenu_sets_selection(
		GtkToggleButton* const button,
		GtkListView* const enum_list
		) {
	if (gtk_toggle_button_get_active(button)) {
		GtkSingleSelection* const enum_model = GTK_SINGLE_SELECTION(
			gtk_list_view_get_model(enum_list)
		);
		//gtk_single_selection_set_selected(enum_model, 0);
		GObject* const enum_gobj = gtk_single_selection_get_selected_item(
			enum_model
		);
		atui_leaf* const leaf = g_object_get_data(
			enum_gobj, "leaf"
		);

		int64_t val;
		if (leaf->type & ATUI_SIGNED) {
			val = atui_leaf_get_val_signed(leaf);
		} else {
			val = atui_leaf_get_val_unsigned(leaf);
		}
		int16_t index = atui_enum_lsearch(leaf->enum_options, val);
		if (-1 < index) {
			gtk_single_selection_set_selected(enum_model, index);
		} else {
			gtk_single_selection_set_selected(
				enum_model, GTK_INVALID_LIST_POSITION
			);
			//gtk_selection_model_unselect_all(GTK_SELECTION_MODEL(enum_model));
		}
	}
}
inline static GtkWidget*
construct_enum_dropdown(
		GtkEntryBuffer* const entry_buffer,
		GtkListItem* const column_cell
		) {
	GtkEditable* const enumentry = GTK_EDITABLE(gtk_entry_new_with_buffer(
		entry_buffer
	));
	g_signal_connect(enumentry,
		"activate", G_CALLBACK(editable_sets_leaf), column_cell
	);
	gtk_widget_set_hexpand(GTK_WIDGET(enumentry), true);

	GtkListItemFactory* const list_factory = gtk_signal_list_item_factory_new();
	g_object_connect(list_factory,
		"swapped-signal::setup", G_CALLBACK(label_column_setup), NULL,
		"swapped-signal::bind", G_CALLBACK(enum_label_column_bind), NULL,
		NULL
	);
	GtkWidget* const enum_list = gtk_list_view_new(NULL, list_factory);

	GtkPopover* const popover = GTK_POPOVER(gtk_popover_new());
	gtk_popover_set_has_arrow(popover, false);
	gtk_popover_set_child(popover, enum_list);

	g_object_connect(enum_list,
		"signal::activate", G_CALLBACK(enum_list_sets_editable), enumentry,
		"signal::activate", G_CALLBACK(enum_list_sets_leaf), NULL,
		"swapped-signal::activate", G_CALLBACK(gtk_popover_popdown), popover,
		NULL
	);

	GtkMenuButton* const enummenu = GTK_MENU_BUTTON(gtk_menu_button_new());
	gtk_menu_button_set_direction(enummenu, GTK_ARROW_RIGHT);
	g_signal_connect(gtk_widget_get_first_child(GTK_WIDGET(enummenu)),
		// ToggleButton. MenuButton's 'activate' is broken?
		// TODO notify::active and gtk_menu_button_get_active
		"toggled", G_CALLBACK(enummenu_sets_selection), enum_list
	);
	gtk_menu_button_set_popover(enummenu, GTK_WIDGET(popover));


	GtkWidget* const enumdropdown = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_append(GTK_BOX(enumdropdown), GTK_WIDGET(enummenu));
	gtk_box_append(GTK_BOX(enumdropdown), GTK_WIDGET(enumentry));
	return enumdropdown;
}
inline static GtkSelectionModel*
get_enum_menu_listmodel(
		atui_leaf* const leaf
		) {
	if (NULL == leaf->enum_model) {
		GListStore* list = g_list_store_new(G_TYPE_OBJECT);
		struct atui_enum const* const atuienum = leaf->enum_options;
		GObject* gobj_child;

		for (uint8_t i=0; i < atuienum->num_entries; i++) {
			gobj_child = g_object_new(G_TYPE_OBJECT, NULL);
			g_object_set_data(gobj_child, "enum",
				(struct atui_enum_entry*) &(atuienum->enum_array[i]) // de-const
			);
			g_object_set_data(gobj_child, "leaf", leaf);
			g_list_store_append(list, gobj_child);
			g_object_unref(gobj_child);
		}
		GtkSingleSelection* const enum_model = gtk_single_selection_new(
			G_LIST_MODEL(list)
		);
		gtk_single_selection_set_can_unselect(enum_model, true);
		gtk_single_selection_set_autoselect(enum_model, false);
		leaf->enum_model = GTK_SELECTION_MODEL(enum_model);
		g_object_ref(leaf->enum_model); // to cache
	}
	return leaf->enum_model;
}
static void
leaves_val_column_setup(
		void const* const _null, // swapped-signal:: with factory
		GtkListItem* const column_cell
		) {
// setup
	GtkStack* const widget_bag = GTK_STACK(gtk_stack_new());
	gtk_list_item_set_child(column_cell, GTK_WIDGET(widget_bag));
	GtkEventController* const focus_sense = gtk_event_controller_focus_new();
	g_signal_connect_swapped(focus_sense,
		"leave", G_CALLBACK(leaves_editable_stray_reset), column_cell
	);
	gtk_widget_add_controller(GTK_WIDGET(widget_bag), focus_sense);
	// widget takes ownership of the controller, no need to unref.


	GtkEntryBuffer* const entry_buffer = gtk_entry_buffer_new(
		NULL, ATUI_LEAVES_STR_BUFFER
	);

	// numbers, strings
	//sub_widget = gtk_text_new();
	GtkWidget* const regular = gtk_entry_new_with_buffer(entry_buffer);
	gtk_stack_add_named(widget_bag, regular, "text");
	g_signal_connect(GTK_EDITABLE(regular),
		"activate", G_CALLBACK(editable_sets_leaf), column_cell
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
		GtkListItem* const column_cell
		) {
// bind
	GtkTreeListRow* const tree_row = gtk_list_item_get_item(column_cell);
	GObject* const gobj_leaf = gtk_tree_list_row_get_item(tree_row);
	atui_leaf* const leaf = g_object_get_data(gobj_leaf, "leaf");
	GtkStack* const widget_bag = GTK_STACK(
		gtk_list_item_get_child(column_cell)
	);

	if (leaf->type & (ATUI_ANY|ATUI_STRING|ATUI_ARRAY)) {
		gtk_widget_set_visible(GTK_WIDGET(widget_bag), true);
		GtkWidget* editable;
		if (leaf->type & ATUI_ENUM) {
			gtk_stack_set_visible_child_name(widget_bag, "enum");
			GtkWidget* const enumbox = gtk_stack_get_visible_child(widget_bag);
			GtkListView* const enum_list = GTK_LIST_VIEW(gtk_popover_get_child(
				gtk_menu_button_get_popover(
					GTK_MENU_BUTTON(gtk_widget_get_first_child(enumbox))
				)
			));
			GtkSelectionModel* const enum_model = get_enum_menu_listmodel(leaf);

			gtk_list_view_set_model(enum_list, enum_model);
			editable = gtk_widget_get_last_child(enumbox);
		} else {
			gtk_stack_set_visible_child_name(widget_bag, "text");
			editable = gtk_stack_get_visible_child(widget_bag);
		}

		leaf_sets_editable(leaf, GTK_EDITABLE(editable));
	} else {
		gtk_widget_set_visible(GTK_WIDGET(widget_bag), false);
	}
	g_object_unref(gobj_leaf);
}
static void
leaves_offset_column_bind(
		yaabegtk_commons* const commons,
		GtkListItem* const column_cell
		) {
// bind data to the UI skeleton
	GtkWidget* const label = gtk_list_item_get_child(column_cell);

	GtkTreeListRow* const tree_row = gtk_list_item_get_item(column_cell);
	GObject* const gobj_leaf = gtk_tree_list_row_get_item(tree_row);
	atui_leaf* const leaf = g_object_get_data(gobj_leaf, "leaf");
	g_object_unref(gobj_leaf);

	char8_t buffer[18];
	if (leaf->type & _ATUI_BITCHILD) {
		sprintf(buffer, "[%u:%u]",
			leaf->bitfield_hi, leaf->bitfield_lo
		);
	} else if (leaf->num_bytes) {
		uint32_t const start = leaf->val - commons->atomtree_root->bios;
		uint32_t const end = (start + leaf->num_bytes -1);
		sprintf(buffer, "[%05X - %05X]", start, end);
	} else {
		buffer[0] = '\0';
	}
	gtk_label_set_text(GTK_LABEL(label), buffer);
}



static void
leaf_right_click_copy_path(
		GSimpleAction* const action,
		GVariant* const parameter,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	atui_leaf const* const leaf = g_object_get_data(pack->gobj_atui, "leaf");

	char8_t pathstring[PATHBAR_BUFFER_SIZE];
	char8_t* eos = atui_leaf_to_path(leaf, pathstring);
	assert(eos < (pathstring + PATHBAR_BUFFER_SIZE));

	gdk_clipboard_set_text(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		pathstring
	);
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
static void
leaf_right_click_copy_data(
		GSimpleAction* const action,
		GVariant* const parameter,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	atui_leaf const* const leaf = g_object_get_data(pack->gobj_atui, "leaf");
	assert(leaf->num_bytes || leaf->type & _ATUI_BITCHILD);

	gchar* b64_text;
	if (leaf->type & _ATUI_BITCHILD) {
		uint64_t const val = atui_leaf_get_val_unsigned(leaf);
		b64_text = g_base64_encode((void const*)&val, sizeof(val));
	} else {
		assert(leaf->val);
		b64_text = g_base64_encode(leaf->val, leaf->num_bytes);
	}
	gdk_clipboard_set_text(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		b64_text
	);
	g_free(b64_text);
}
static void
leaf_right_click_paste_data_set_data(
		GObject* const clipboard,
		GAsyncResult* const async_data,
		gpointer const pack_ptr
		) {
// AsyncReadyCallback
	struct rightclick_pack const* const pack = pack_ptr;
	atui_leaf* const leaf = g_object_get_data(pack->gobj_atui, "leaf");
	assert(leaf->num_bytes || leaf->type & _ATUI_BITCHILD);

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

	GtkAlertDialog* error_popup = NULL;
	size_t num_bytes = 0;
	void* const raw_data = g_base64_decode(b64_text, &num_bytes);
	if (num_bytes) {
		if (leaf->type & _ATUI_BITCHILD) {
			uint64_t const* const val = raw_data;
			uint64_t const oldval = atui_leaf_get_val_unsigned(leaf);
			atui_leaf_set_val_unsigned(leaf, *val);

			if (*val != atui_leaf_get_val_unsigned(leaf)) {
				atui_leaf_set_val_unsigned(leaf, oldval);
				error_popup = gtk_alert_dialog_new(
					"Wrong size: "
					"pasted raw value 0x%X has too many bits for %s",
					*val, leaf->name
				);
			}
		} else {
			assert(leaf->val);
			if (num_bytes == leaf->num_bytes) {
				memcpy(leaf->u8, raw_data, num_bytes);
			} else {
				error_popup = gtk_alert_dialog_new(
					"Wrong size: pasted base64 data decodes to %u bytes, "
					"but %s is %u bytes.",
					num_bytes, leaf->name, leaf->num_bytes
				);
			}
		}
	} else {
		error_popup = gtk_alert_dialog_new("Base64 decode error!");
	}

	if (error_popup) {
		gtk_alert_dialog_set_detail(error_popup, b64_text);
		gtk_alert_dialog_show(
			error_popup,
			gtk_application_get_active_window(pack->commons->yaabe_gtk)
		);
		g_object_unref(error_popup);
	}
	g_free(raw_data);
	g_free(b64_text);
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

	GObject* const gobj_leaf = gtk_tree_list_row_get_item(
		gtk_column_view_row_get_item(pack->row)
	);
	g_object_unref(gobj_leaf); // we don't need a second reference
	pack->gobj_atui = gobj_leaf;
	atui_leaf const* const leaf = g_object_get_data(pack->gobj_atui, "leaf");


	// see also create_leaves_rightclick_menu
	GActionEntry actions[3] = {0};
	actions[0] = (GActionEntry) {"path", leaf_right_click_copy_path};
	uint8_t num_actions = 1;
	if (leaf->num_bytes || leaf->type & _ATUI_BITCHILD) {
		actions[num_actions].name = "copy_data";
		actions[num_actions].activate = leaf_right_click_copy_data;
		num_actions++;
		actions[num_actions].name = "paste_data";
		actions[num_actions].activate = leaf_right_click_paste_data;
		num_actions++;
	}

	assert(num_actions <= sizeof(actions)/sizeof(GActionEntry));
	GActionMap* const action_set = G_ACTION_MAP(g_simple_action_group_new());
	g_action_map_add_action_entries(action_set,
		actions, num_actions,
		pack
	);

	gtk_widget_insert_action_group(GTK_WIDGET(leaves_context->view),
		"leaves", G_ACTION_GROUP(action_set)
	);
	// we cannot disconnect action group on popdown because it kills the
	// actions. Simply replacing them seems to be fine.
	g_object_unref(action_set);

	calculate_rightclick_popup_location(
		click_sense, x,y, leaves_context, pack->row_hack->owner
	);
}
inline static void
create_leaves_rightclick_menu(
		yaabegtk_commons* const commons
		) {
	GMenu* const menu_model = g_menu_new();
	g_menu_append(menu_model, "Copy Path", "leaves.path");
	g_menu_append(menu_model, "Copy Data As Base64", "leaves.copy_data");
	g_menu_append(menu_model, "Paste Data From Base64", "leaves.paste_data");
	// see also leaves_rightclick_popup

	columnview_create_rightclick_popup(
		G_MENU_MODEL(menu_model), &commons->leaves
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
	GtkWidget* const frame = gtk_frame_new(NULL);
	gtk_frame_set_child(GTK_FRAME(frame), scrolledlist);

	create_leaves_rightclick_menu(commons);

	return frame;
}


static void
branch_name_column_bind(
		void const* const _null, // swapped-signal:: with factory
		GtkListItem* const column_cell
		) {
// bind data to the UI skeleton
	GtkTreeListRow* const tree_row = gtk_list_item_get_item(column_cell);
	GObject* const gobj_branch = gtk_tree_list_row_get_item(tree_row);
	atui_branch* const branch = g_object_get_data(gobj_branch, "branch");
	g_object_unref(gobj_branch);

	GtkTreeExpander* const expander = GTK_TREE_EXPANDER(
		gtk_list_item_get_child(column_cell)
	);
	gtk_tree_expander_set_list_row(expander, tree_row);

	GtkWidget* const label = gtk_tree_expander_get_child(expander);
	gtk_label_set_text(GTK_LABEL(label), branch->name);
	uint8_t const current_lang = LANG_ENGLISH;
	gtk_widget_set_tooltip_text(label, branch->description[current_lang]);
}
static void
branch_type_column_bind(
		void const* const _null, // swapped-signal:: with factory
		GtkListItem* const column_cell
		) {
// bind
	GtkWidget* const label = gtk_list_item_get_child(column_cell);

	GtkTreeListRow* const tree_row = gtk_list_item_get_item(column_cell);
	GObject* const gobj_branch = gtk_tree_list_row_get_item(tree_row);
	atui_branch* const branch = g_object_get_data(gobj_branch, "branch");
	g_object_unref(gobj_branch);

	gtk_label_set_text(GTK_LABEL(label), branch->origname);
}

static void
branch_right_click_copy_path(
		GSimpleAction* const action,
		GVariant* const parameter,
		gpointer const pack_ptr
		) {
	struct rightclick_pack const* const pack = pack_ptr;
	atui_branch const* const branch = g_object_get_data(
		pack->gobj_atui, "branch"
	);

	char8_t pathstring[PATHBAR_BUFFER_SIZE];
	char8_t* eos = atui_branch_to_path(branch, pathstring);
	assert(eos < (pathstring + PATHBAR_BUFFER_SIZE));

	gdk_clipboard_set_text(
		gdk_display_get_clipboard(
			gdk_display_get_default()
		),
		pathstring
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

	GObject* const gobj_branch = gtk_tree_list_row_get_item(
		gtk_column_view_row_get_item(pack->row)
	);
	g_object_unref(gobj_branch); // we don't need a second reference.
	pack->gobj_atui = gobj_branch;

	// see also create_branches_rightclick_menu
	GActionEntry actions[1] = {0};
	actions[0] = (GActionEntry) {"path", branch_right_click_copy_path};
	uint8_t num_actions = 1;
	GActionMap* const action_set = G_ACTION_MAP(g_simple_action_group_new());
	g_action_map_add_action_entries(action_set,
		actions, num_actions,
		pack
	);
	gtk_widget_insert_action_group(GTK_WIDGET(branches_context->view),
		"branches", G_ACTION_GROUP(action_set)
	);
	// we cannot disconnect action group on popdown because it kills the
	// actions. Simply replacing them seems to be fine.
	g_object_unref(action_set);

	calculate_rightclick_popup_location(
		click_sense, x,y, branches_context, pack->row_hack->owner
	);
}
inline static void
create_branches_rightclick_menu(
		yaabegtk_commons* const commons
		) {
	GMenu* const menu_model = g_menu_new();
	g_menu_append(menu_model, "Copy Path", "branches.path");
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
	GtkWidget* const frame = gtk_frame_new(NULL);
	gtk_frame_set_child(GTK_FRAME(frame), scrolledlist);

	create_branches_rightclick_menu(commons);

	return frame;
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





struct atom_tree*
atomtree_load_from_gfile(
		GFile* const biosfile,
		GError** const ferror_out
		) {
// Geneate the atom_tree and atui from a GIO File
	GError* ferror = NULL;
	void* bios = NULL;

	GFileInputStream* const readstream = g_file_read(biosfile, NULL, &ferror);
	if (ferror) {
		goto exit1;
	}

	GFileInfo* const fi_size = g_file_query_info(biosfile,
		G_FILE_ATTRIBUTE_STANDARD_SIZE, G_FILE_QUERY_INFO_NONE, NULL, &ferror
	);
	if (ferror) {
		goto exit2;
	}

	int64_t const filesize = g_file_info_get_size(fi_size);
	g_object_unref(fi_size);
	// TODO possible warning if the file size is too big? too small?

	bios = malloc(filesize);
	g_input_stream_read(G_INPUT_STREAM(readstream),
		bios, filesize, NULL, &ferror
	);
	if (ferror) {
		free(bios);
		goto exit2;
	}

	struct atom_tree* const atree = atombios_parse(bios, filesize, true);
	if (atree == NULL) {
		free(bios);
		goto exit2;
	}

	g_object_ref(biosfile);
	atree->biosfile = biosfile;
	atree->biosfile_size = filesize;

	g_input_stream_close(G_INPUT_STREAM(readstream), NULL, &ferror);

	exit2:
	g_object_unref(readstream);
	exit1:
	if (ferror_out) {
		*ferror_out = ferror;
	} else if (ferror) {
		g_error_free(ferror);
	}

	return atree;
}
void
atomtree_save_to_gfile(
		struct atom_tree* const atree,
		GError** const ferror_out
		) {
	atomtree_bios_checksum(atree);

	GError* ferror = NULL;

	GFileIOStream* biosfilestream = g_file_create_readwrite(
		atree->biosfile, G_FILE_CREATE_PRIVATE, NULL, &ferror
	);
	if (ferror && (ferror->code == G_IO_ERROR_EXISTS)) {
		g_error_free(ferror);
		ferror = NULL;
		biosfilestream = g_file_open_readwrite(
			atree->biosfile, NULL, &ferror
		);
	}
	if (ferror) {
		goto ferr0;
	}

	GIOStream* const biosstream = G_IO_STREAM(biosfilestream);
	GOutputStream* const writestream = g_io_stream_get_output_stream(
		biosstream
	);

	g_output_stream_write_all(
		writestream,  atree->alloced_bios,
		atree->biosfile_size,  NULL,NULL,  &ferror
	);
	if (ferror) {
		goto ferr1;
	}

	g_output_stream_close(writestream, NULL, &ferror);
	if (ferror) {
		goto ferr1;
	}
	g_io_stream_close(biosstream, NULL, &ferror);
	if (ferror) {
		goto ferr1;
	}


	ferr1:
	g_object_unref(biosstream);
	ferr0:

	if (ferror_out) {
		*ferror_out = ferror;
	} else {
		g_error_free(ferror);
	}

	return;
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
	if (commons->atomtree_root) {
		filename = g_file_get_basename(commons->atomtree_root->biosfile);
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

	struct atom_tree* const atree = atomtree_load_from_gfile(biosfile, &ferror);
	if (ferror) {
		goto ferr;
	}

	if (atree) {
		struct atom_tree* const oldtree = commons->atomtree_root;
		commons->atomtree_root = atree;
		create_and_set_active_atui_model(commons);
		destroy_atomtree_with_gtk(oldtree, true);

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
	if (commons->atomtree_root) {
		working_dir = g_file_get_parent(commons->atomtree_root->biosfile);
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
	struct atom_tree* const old_tree = commons->atomtree_root;
	struct atom_tree* const new_tree = atombios_parse(
		old_tree->alloced_bios, old_tree->biosfile_size, true
	);
	new_tree->biosfile = old_tree->biosfile;
	new_tree->biosfile_size = old_tree->biosfile_size;
	commons->atomtree_root = new_tree;
	create_and_set_active_atui_model(commons);
	destroy_atomtree_with_gtk(old_tree, false);
}
static void
save_button_same_file(
		yaabegtk_commons* const commons
		) {
// signal callback
	GError* ferror = NULL;

	atomtree_save_to_gfile(commons->atomtree_root, &ferror);
	if (ferror) {
		goto ferr;
	}

	return;

	ferr:
	filer_error_window(commons, ferror, "Save BIOS error");
	g_error_free(ferror);
	return;
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


	GFile* const old_biosfile = commons->atomtree_root->biosfile;
	commons->atomtree_root->biosfile = new_biosfile;
	atomtree_save_to_gfile(commons->atomtree_root, &ferror);
	if (ferror) {
		commons->atomtree_root->biosfile = old_biosfile;
		g_object_unref(new_biosfile);
		goto ferr_msg;
	}
	set_editor_titlebar(commons);
	g_object_unref(old_biosfile);
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
	GFile* const working_dir = g_file_get_parent(
		commons->atomtree_root->biosfile
	);
	gtk_file_dialog_set_initial_file(filer, commons->atomtree_root->biosfile);
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
	g_signal_connect_swapped(load_button,
		"clicked", G_CALLBACK(load_button_open_bios), commons
	);
	GtkWidget* const reload_button = gtk_button_new_with_label("Reload");
	g_signal_connect_swapped(reload_button,
		"clicked", G_CALLBACK(reload_button_reload_bios), commons
	);
	GtkWidget* const load_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_append(GTK_BOX(load_buttons), load_button);
	gtk_box_append(GTK_BOX(load_buttons), reload_button);


	GtkWidget* const save_button = gtk_button_new_with_label("Save");
	g_signal_connect_swapped(save_button,
		"clicked", G_CALLBACK(save_button_same_file), commons
	);
	GtkWidget* const saveas_button = gtk_button_new_with_label("Save As");
	g_signal_connect_swapped(saveas_button,
		"clicked", G_CALLBACK(saveas_button_name_bios), commons
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
	if (commons->atomtree_root == NULL) {
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
	g_signal_connect(dropfile,
		"drop", G_CALLBACK(dropped_file_open_bios), commons
	);

	GtkWindow* const window = GTK_WINDOW(gtk_application_window_new(gtkapp));
	gtk_widget_add_controller(
		GTK_WIDGET(window), GTK_EVENT_CONTROLLER(dropfile)
	);

	gtk_window_set_default_size(window, 1400,700); // 2:1
	gtk_window_set_child(window, GTK_WIDGET(main_box));
	gtk_widget_grab_focus(tree_divider);
	gtk_widget_grab_focus(GTK_WIDGET(commons->branches.view));

	if (commons->atomtree_root) {
		create_and_set_active_atui_model(commons);
	}

	set_editor_titlebar(commons);
	gtk_window_present(window);
}
int8_t
yaabe_gtk(
		struct atom_tree** const atree
		) {
	yaabegtk_commons commons = {0};
	commons.atomtree_root = *atree;

	commons.yaabe_gtk = gtk_application_new(NULL, G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(commons.yaabe_gtk,
		"activate", G_CALLBACK(yaabe_app_activate), &commons
	);
	int8_t const status = g_application_run(
		G_APPLICATION(commons.yaabe_gtk), 0,NULL
	);

	*atree = commons.atomtree_root;
	g_object_unref(commons.yaabe_gtk);

	return status;
}
