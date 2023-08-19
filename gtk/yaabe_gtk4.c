#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include <atui.h>
#include <atomtree.h>

struct yaabe_gtkapp_ptrs_commons {
	GtkApplication* yaabe_gtk;

	struct atom_tree* atomtree_root;
	atui_branch* atui_root;

	GtkColumnView* leaves_columnview; // so branches can set leaves
};

struct yaabe_gtkapp_model_cache { // to cache
	// If this struct is attached to a branch, this caches the depth 0
	// TreeListModel elements of the branch's leaves if it has leaves.
	GtkSelectionModel* leaves_model;

	/*
	If this struct is attached to a branch, child_gobj caches the simple
	GOBject wrapper for the child branches, to be used in the TreeListModel in
	the branches pane.

	If this struct is attached to a leaf, child_gobj caches the simple
	GOBject wrapper for the child leaves, to be used if the TreeListModel in
	the leaves pane.
	*/
	uint16_t child_gobj_count;
	GObject* child_gobj[];
};

inline static void alloc_branch_cache(atui_branch* branch) {
	uint16_t gobj_count = branch->num_child_branches;

	branch->auxiliary = malloc(
		sizeof(struct yaabe_gtkapp_model_cache)
		+ (gobj_count * sizeof(GObject*))
	);

	struct yaabe_gtkapp_model_cache* models = branch->auxiliary;
	models->leaves_model = NULL;
	models->child_gobj_count = gobj_count;
	if (gobj_count)
		models->child_gobj[0] = NULL;
}
inline static void alloc_leaf_cache(atui_leaf* leaf, uint16_t num_children) {
	leaf->auxiliary = malloc(
		sizeof(struct yaabe_gtkapp_model_cache)
		+ (num_children * sizeof(GObject*))
	);

	struct yaabe_gtkapp_model_cache* models = leaf->auxiliary;
	models->leaves_model = NULL;
	models->child_gobj_count = num_children;
	if (num_children)
		models->child_gobj[0] = NULL;
}


void atui_destroy_tree_with_gtk(atui_branch* tree) {
	uint16_t i = 0;
	uint16_t j = 0;
	uint16_t child_gobj_count;
	struct yaabe_gtkapp_model_cache* submodels;

	// the leaves gobjects should be sunk into the model, and auxiliary points
	// to the model.
	if (tree->auxiliary != NULL) {
		submodels = tree->auxiliary;

		if(submodels->leaves_model != NULL) {
			g_object_unref(submodels->leaves_model);
		}

		child_gobj_count = submodels->child_gobj_count;
		for (i=0; i < child_gobj_count; i++) {
			g_object_unref(submodels->child_gobj[i]);
		}

		free(submodels);
	}

	//collapsable leaves in the leaves pane
	uint16_t leaf_count = tree->leaf_count;
	for(i=0; i < leaf_count; i++) {
		submodels = tree->leaves[i].auxiliary;
		if (submodels != NULL) {
			if(submodels->leaves_model) // should always be false
				g_object_unref(submodels->leaves_model);

			child_gobj_count = submodels->child_gobj_count;
			for (j=0; j < child_gobj_count; j++) {
				g_object_unref(submodels->child_gobj[j]);
			}

			free(submodels);
		}
	}

	atui_branch* child_branch;
	while(tree->max_branch_count) {
		(tree->max_branch_count)--;
		child_branch = tree->all_branches[tree->max_branch_count];
		if (child_branch != NULL)
			atui_destroy_tree_with_gtk(child_branch);
	}

	free(tree);

}






static void leaves_key_column_spawner(
		GtkListItemFactory* factory, GtkListItem* list_item) { 
//setup to spawn a UI skeleton

	GtkWidget* expander = gtk_tree_expander_new();
	gtk_tree_expander_set_indent_for_icon(GTK_TREE_EXPANDER(expander), true);

	GtkWidget* label = gtk_label_new(NULL);
	gtk_tree_expander_set_child(GTK_TREE_EXPANDER(expander), label);

	gtk_list_item_set_child(list_item, expander);
}
static void leaves_key_column_recycler(
		GtkListItemFactory* factory, GtkListItem* list_item) {
//bind data to the UI skeleton

	GtkTreeExpander* expander = GTK_TREE_EXPANDER(
		gtk_list_item_get_child(list_item));
	GtkWidget* label = gtk_tree_expander_get_child(expander);

	GtkTreeListRow* tree_list_item = gtk_list_item_get_item(list_item);
	GObject* gobj_leaf = gtk_tree_list_row_get_item(tree_list_item);
	atui_leaf* leaf = g_object_get_data(gobj_leaf, "leaf");
	g_object_unref(gobj_leaf);
	gtk_label_set_text(GTK_LABEL(label), leaf->name);

	gtk_tree_expander_set_list_row(expander, tree_list_item);
}

static void leaves_textbox_stray(
		GtkEventControllerFocus* focus_sense, gpointer leaf_gptr) {
//if the value wasn't applied with enter, sync the text back to the actual data
//when keyboard leaves the textbox
	GtkWidget* textbox = gtk_event_controller_get_widget(
		GTK_EVENT_CONTROLLER(focus_sense));
	atui_leaf* leaf = leaf_gptr;

	char str_buff[ATUI_LEAVES_STR_BUFFER] = "\0";
	atui_get_to_text(leaf, str_buff);
	gtk_editable_set_text(GTK_EDITABLE(textbox), str_buff);
}
static void leaves_val_column_textbox_apply(
		GtkEditable* textbox, gpointer leaf_gptr) {
// only way to apply the value is to hit enter

	atui_leaf* leaf = leaf_gptr;

	atui_set_from_text(leaf, gtk_editable_get_text(textbox));
	
	char str_buff[ATUI_LEAVES_STR_BUFFER] = "\0";
	atui_get_to_text(leaf, str_buff);
	gtk_editable_set_text(textbox, str_buff);
}


static void leaves_val_column_spawner(
		GtkListItemFactory* factory, GtkListItem* list_item) {
// setup

	GtkWidget* textbox = gtk_text_new();
	gtk_text_set_input_purpose(GTK_TEXT(textbox), GTK_INPUT_PURPOSE_DIGITS);

	// for leaves_textbox_stray()
	GtkEventController* focus_sense = gtk_event_controller_focus_new();
	gtk_widget_add_controller(textbox, focus_sense);
	// widget takes ownership of the controller, no need to unref.

	gtk_list_item_set_child(list_item, textbox);
}
static void leaves_val_column_recycler(
		GtkListItemFactory* factory, GtkListItem* list_item) {
// bind

	GtkWidget* textbox = gtk_list_item_get_child(list_item);

	GtkTreeListRow* tree_list_item = gtk_list_item_get_item(list_item);
	GObject* gobj_leaf = gtk_tree_list_row_get_item(tree_list_item);
	atui_leaf* leaf = g_object_get_data(gobj_leaf, "leaf");
	g_object_unref(gobj_leaf);

	char str_buff[ATUI_LEAVES_STR_BUFFER] = "\0";
	atui_get_to_text(leaf, str_buff);
	gtk_editable_set_text(GTK_EDITABLE(textbox), str_buff);

	g_signal_connect(textbox,
		"activate", G_CALLBACK(leaves_val_column_textbox_apply), leaf
	);


	GListModel* controller_list = gtk_widget_observe_controllers(textbox);
	GtkEventController* focus_sense = g_list_model_get_item(controller_list, 0);
	g_signal_connect(focus_sense,
		"leave", G_CALLBACK(leaves_textbox_stray), leaf
	);
	g_object_unref(controller_list);
	g_object_unref(focus_sense);

}
static void leaves_val_column_cleaner(
		GtkListItemFactory* factory, GtkListItem* list_item) {
// unbind
// signals need to be removed, else they build up

	GtkWidget* textbox = gtk_list_item_get_child(list_item);

	//TODO: GtkText - unexpected blinking selection. Removing
	// these don't fix the warning:
	//gtk_editable_select_region(GTK_EDITABLE(textbox), 0, 0);
	//gtk_editable_set_position(GTK_EDITABLE(textbox), 0);

	g_signal_handlers_disconnect_matched(textbox, G_SIGNAL_MATCH_FUNC, 
		0,0,NULL,  G_CALLBACK(leaves_val_column_textbox_apply),  NULL
	);

	GListModel* controller_list = gtk_widget_observe_controllers(textbox);
	GtkEventController* focus_sense = g_list_model_get_item(controller_list, 0);
	g_signal_handlers_disconnect_matched(focus_sense, G_SIGNAL_MATCH_FUNC, 
		0,0,NULL,  G_CALLBACK(leaves_textbox_stray),  NULL
	);
	g_object_unref(controller_list);
	g_object_unref(focus_sense);
}


static void atui_inline_pullin_gliststore(atui_leaf* parent, GListStore* list) {
// if the parent leaf has children that aren't adjacent, but the parent is
// labeled with ATUI_NODISPLAY, pull them in.

	GObject* gobj_child = NULL;
	atui_leaf* atui_children = NULL;
	atui_leaf* leaf = NULL;
	uint16_t num_children = 0;
	uint16_t i = 0;

	if (parent->type & ATUI_INLINE) {
		atui_branch* branch = *(parent->inline_branch);
		num_children = branch->leaf_count;
		atui_children = branch->leaves;
	}

	for(i=0; i < num_children; i++) {
		leaf = atui_children+i;

		if ( (leaf->type & ATUI_NODISPLAY)==0 ) {
			gobj_child = g_object_new(G_TYPE_OBJECT, NULL);
			g_object_set_data(gobj_child, "leaf", leaf);
			g_list_store_append(list, gobj_child);
			g_object_unref(gobj_child);
			i += leaf->num_child_leaves;
		} else if (leaf->type & ATUI_INLINE) {
			atui_inline_pullin_gliststore(leaf, list);
		}
	}
}
static inline GListModel* atui_leaves_to_glistmodel(
		atui_leaf* children, uint16_t num_children) {

	atui_leaf* leaf = NULL;
	GObject* gobj_child = NULL;
	uint16_t i = 0;

	GListStore* child_list = g_list_store_new(G_TYPE_OBJECT);

	for(i=0; i < num_children; i++) {
		leaf = children+i;
		if ( (leaf->type & ATUI_NODISPLAY)==0 ) {
			gobj_child = g_object_new(G_TYPE_OBJECT, NULL);
			g_object_set_data(gobj_child, "leaf", leaf);
			g_list_store_append(child_list, gobj_child);
			g_object_unref(gobj_child);
			i += leaf->num_child_leaves;
		} else if (leaf->type & ATUI_INLINE) {
			atui_inline_pullin_gliststore(leaf, child_list);
		}
	}

	return G_LIST_MODEL(child_list);
}

static GListModel* leaves_tlmodel_func(gpointer parent_ptr, gpointer d) {
//GtkTreeListModelCreateModelFunc for leaves

	GObject* gobj_parent = parent_ptr;
	atui_leaf* parent = g_object_get_data(gobj_parent, "leaf");
	struct yaabe_gtkapp_model_cache* leaf_cache = parent->auxiliary;

	GListModel* children_model = NULL;
	uint16_t i = 0;

	if (parent->type & (ATUI_BITFIELD|ATUI_INLINE|ATUI_DYNARRAY)) {

		// if no cached gobjects, generate and cache them; otherwise use cache.
		if (leaf_cache == NULL) {
			uint16_t num_children = 0;
			atui_leaf* child_leaves = NULL;

			if (parent->type & ATUI_INLINE) {
				atui_branch* branch = *(parent->inline_branch);
				num_children = branch->leaf_count;
				child_leaves = branch->leaves;
			} else if (parent->type & (ATUI_BITFIELD | ATUI_DYNARRAY)) {
				num_children = parent->num_child_leaves;
				child_leaves = parent+1;
			}
			children_model = atui_leaves_to_glistmodel(
				child_leaves, num_children
			);

			uint16_t child_gobj_count =\
				g_list_model_get_n_items(children_model);
			alloc_leaf_cache(parent, child_gobj_count);
			leaf_cache = parent->auxiliary;
			for(i=0; i < child_gobj_count; i++) {
				// cache the gobjects because TreeListModel eats the GListStore
				leaf_cache->child_gobj[i] = g_list_model_get_item(
					children_model, i
				); // get_item automatically ref++'s the object.
			}

		} else { // use the cache
			GListStore* child_list = g_list_store_new(G_TYPE_OBJECT);
			for(i=0; i < leaf_cache->child_gobj_count; i++)
				g_list_store_append(child_list, leaf_cache->child_gobj[i]);
			children_model = G_LIST_MODEL(child_list);
		}
	}
	return children_model;
}

inline static void branchleaves_to_treemodel(atui_branch* branch) {
	GListModel* leavesmodel = atui_leaves_to_glistmodel(
		branch->leaves, branch->leaf_count
	);

	GtkTreeListModel* treemodel = gtk_tree_list_model_new(
		leavesmodel, false, true, leaves_tlmodel_func, NULL,NULL
	);
	GtkSelectionModel* sel_model = GTK_SELECTION_MODEL(
		gtk_no_selection_new(G_LIST_MODEL(treemodel))
	);
	// no_selection takes ownership of treemodel.
	
	struct yaabe_gtkapp_model_cache* branch_models = branch->auxiliary;
	branch_models->leaves_model = sel_model;
	g_object_ref(sel_model); // to cache
}


static void set_leaves_list(GtkSelectionModel* model,
		guint position, guint n_items, gpointer yaabe_commons) {

	struct yaabe_gtkapp_ptrs_commons* commons = yaabe_commons;

	GtkTreeListRow* tree_list_item = gtk_single_selection_get_selected_item(
		GTK_SINGLE_SELECTION(model)
	);
	GObject* gobj_branch = gtk_tree_list_row_get_item(tree_list_item);
	atui_branch* branch = g_object_get_data(gobj_branch, "branch");
	g_object_unref(gobj_branch);

	struct yaabe_gtkapp_model_cache* branch_models = branch->auxiliary;
	if(branch_models->leaves_model == NULL) // if not cached, generate.
		branchleaves_to_treemodel(branch);

	gtk_column_view_set_model(commons->leaves_columnview,
		branch_models->leaves_model
	);
}

inline static GtkWidget* create_leaves_pane(
		struct yaabe_gtkapp_ptrs_commons* commons) {

	atui_branch* root_branch = commons->atui_root;
	struct yaabe_gtkapp_model_cache* root_models = root_branch->auxiliary;
	
	// columnview abstract
	branchleaves_to_treemodel(root_branch);
	GtkWidget* leaves_list = gtk_column_view_new(root_models->leaves_model);
	commons->leaves_columnview = GTK_COLUMN_VIEW(leaves_list);


	// create and attach columns
	GtkListItemFactory* factory;
	GtkColumnViewColumn* column;

	factory = gtk_signal_list_item_factory_new();
	g_signal_connect(factory,
		"setup", G_CALLBACK(leaves_key_column_spawner), NULL
	);
	g_signal_connect(factory,
		"bind", G_CALLBACK(leaves_key_column_recycler), NULL
	);
	column = gtk_column_view_column_new("names", factory);
	gtk_column_view_append_column(GTK_COLUMN_VIEW(leaves_list), column);
	g_object_unref(column);

	factory = gtk_signal_list_item_factory_new();
	g_signal_connect(factory,
		"setup", G_CALLBACK(leaves_val_column_spawner), NULL
	);
	g_signal_connect(factory,
		"bind", G_CALLBACK(leaves_val_column_recycler), NULL
	);
	g_signal_connect(factory,
		"unbind", G_CALLBACK(leaves_val_column_cleaner), NULL
	);
	column = gtk_column_view_column_new("values", factory);
	gtk_column_view_append_column(GTK_COLUMN_VIEW(leaves_list), column);
	g_object_unref(column);


	GtkWidget* scrolledlist = gtk_scrolled_window_new();
	gtk_scrolled_window_set_child(
		GTK_SCROLLED_WINDOW(scrolledlist), leaves_list
	);

	GtkWidget* frame = gtk_frame_new(NULL);
	gtk_frame_set_child(GTK_FRAME(frame), scrolledlist);

	return frame;
}




inline static GListStore* atui_gtk_model(atui_branch* root) {
//for the tippy top of the tree

	alloc_branch_cache(root);

	GObject* gbranch = g_object_new(G_TYPE_OBJECT, NULL);
	g_object_set_data(gbranch, "branch", root);
	GListStore* model = g_list_store_new(G_TYPE_OBJECT);
	g_list_store_append(model, gbranch);
	g_object_unref(gbranch);

	return model;
}

static GListModel* branch_tlmodel_func(gpointer ptr, gpointer data) {
//GtkTreeListModelCreateModelFunc for branches

	GObject* gobj_parent = ptr;
	atui_branch* parent = g_object_get_data(gobj_parent, "branch");
	struct yaabe_gtkapp_model_cache* branch_models = parent->auxiliary;

	GListStore* children = NULL; 
	int i = 0;

	if (parent->num_child_branches) {
		children = g_list_store_new(G_TYPE_OBJECT);

		// if no cached gobjects, generate and cache them; otherwise use cache.
		if (branch_models->child_gobj[0] == NULL) {
			GObject* gobj_child;
			for(i=0; i < parent->num_child_branches; i++) {
				// the cache is also for the leaves
				alloc_branch_cache(parent->child_branches[i]);

				gobj_child = g_object_new(G_TYPE_OBJECT, NULL);
				g_object_set_data(gobj_child,
					"branch", parent->child_branches[i]
				);

				branch_models->child_gobj[i] = gobj_child;
				g_list_store_append(children, gobj_child);
			}
		} else {
			for(i=0; i < branch_models->child_gobj_count; i++) {
				g_list_store_append(children, branch_models->child_gobj[i]);
			}
		}
	}
	return G_LIST_MODEL(children);
}




static void branch_listitem_spawner(
		GtkSignalListItemFactory* factory, GtkListItem* list_item) {
// setup
//TODO use https://docs.gtk.org/gtk4/class.Inscription.html

	GtkWidget* expander = gtk_tree_expander_new();
	gtk_tree_expander_set_indent_for_icon(GTK_TREE_EXPANDER(expander), true);
	//gtk_tree_expander_set_indent_for_depth(GTK_TREE_EXPANDER(expander), true);
	//gtk_tree_expander_set_hide_expander(GTK_TREE_EXPANDER(expander), false);

	GtkWidget* label = gtk_label_new(NULL);
	gtk_tree_expander_set_child(GTK_TREE_EXPANDER(expander), label);

	gtk_list_item_set_child(list_item, expander);
}
static void branch_listitem_recycler(
		GtkSignalListItemFactory* factory, GtkListItem* list_item) {
// bind

	GtkTreeExpander* expander = GTK_TREE_EXPANDER(
		gtk_list_item_get_child(list_item));
	GtkWidget* row_label = gtk_tree_expander_get_child(expander);

	GtkTreeListRow* tree_list_item = gtk_list_item_get_item(list_item);
	GObject* gobj_branch = gtk_tree_list_row_get_item(tree_list_item);
	atui_branch* branch = g_object_get_data(gobj_branch, "branch");
	g_object_unref(gobj_branch);

	gtk_label_set_text(GTK_LABEL(row_label), branch->name);

	gtk_tree_expander_set_list_row(expander, tree_list_item);
}



inline static GtkWidget* create_branches_pane(
		struct yaabe_gtkapp_ptrs_commons* commons, GListStore* atui_model) {

	//TreeList, along with branch_tlmodel_func, creates our collapsable model.
	GtkTreeListModel* tlist_atui = gtk_tree_list_model_new(
		G_LIST_MODEL(atui_model), false, true, branch_tlmodel_func, NULL,NULL);

	GtkSingleSelection* sel_model = gtk_single_selection_new(
		G_LIST_MODEL(tlist_atui));

	// change the leaves pane's model based on the what is selected in brances
	g_signal_connect(sel_model, "selection-changed",
		G_CALLBACK(set_leaves_list), commons);
	gtk_single_selection_set_autoselect(sel_model, false);


	GtkListItemFactory* branch_list_factory =
		gtk_signal_list_item_factory_new();
	g_signal_connect(branch_list_factory, "setup",
		G_CALLBACK(branch_listitem_spawner), NULL);
	g_signal_connect(branch_list_factory, "bind",
		G_CALLBACK(branch_listitem_recycler), NULL);
	GtkWidget* listview = gtk_list_view_new(GTK_SELECTION_MODEL(sel_model),
		branch_list_factory);

	GtkWidget* scrolledlist = gtk_scrolled_window_new();
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolledlist), listview);

	GtkWidget* frame = gtk_frame_new(NULL);
	gtk_frame_set_child(GTK_FRAME(frame), scrolledlist);

	return frame;
}

static void filedialog_load_and_set_bios(
		GObject* gobj_filedialog, GAsyncResult* asyncfile,
		gpointer yaabe_commons) {
// AsyncReadyCallback

	struct yaabe_gtkapp_ptrs_commons* commons = yaabe_commons;
	GtkFileDialog* filer = GTK_FILE_DIALOG(gobj_filedialog);
	GError* ferror = NULL;

	GFile* biosfile = gtk_file_dialog_open_finish(filer, asyncfile, &ferror);
	if (ferror) {
		g_object_unref(G_OBJECT(ferror));
		return;
	}

	g_object_unref(gobj_filedialog);
	g_object_unref(G_OBJECT(asyncfile));
}

static void load_button_open_bios(GtkWidget* button, gpointer yaabe_commons) {
	struct yaabe_gtkapp_ptrs_commons* commons = yaabe_commons;
// compress this lot into a open_bios_dialog to use with a 
//  g_signal_connect_swapped  ? Might not be necessary cause when else?

	GtkFileDialog* filer = gtk_file_dialog_new();

	GFile* working_dir = g_file_new_for_path(g_get_current_dir());
	GtkWindow* active_window = gtk_application_get_active_window(
		commons->yaabe_gtk
	);
	gtk_file_dialog_set_initial_folder(filer, working_dir);

	gtk_file_dialog_open(filer,
		active_window, NULL, filedialog_load_and_set_bios, commons
	);


	g_object_unref(working_dir);
}

inline static GtkWidget* buttons_box(
		struct yaabe_gtkapp_ptrs_commons* commons) {

	GtkWidget* load_button = gtk_button_new_with_label("Load");
	g_signal_connect(load_button,
		"clicked", G_CALLBACK(load_button_open_bios), commons
	);

	GtkWidget* reload_button = gtk_button_new_with_label("Reload");
	GtkWidget* load_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_append(GTK_BOX(load_buttons),
		gtk_separator_new(GTK_ORIENTATION_HORIZONTAL)
	);
	gtk_box_append(GTK_BOX(load_buttons), load_button);
	gtk_box_append(GTK_BOX(load_buttons), reload_button);

	GtkWidget* save_button = gtk_button_new_with_label("Save");
	GtkWidget* saveas_button = gtk_button_new_with_label("Save As");
	GtkWidget* save_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_append(GTK_BOX(save_buttons), save_button);
	gtk_box_append(GTK_BOX(save_buttons), saveas_button);


	GtkWidget* cf_button = gtk_button_new_with_label("Function Tables");

	GtkWidget* buttonboxes = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 30);
	gtk_box_append(GTK_BOX(buttonboxes), load_buttons);

	gtk_box_append(GTK_BOX(buttonboxes), save_buttons);
	gtk_box_append(GTK_BOX(buttonboxes), cf_button);

	return buttonboxes;
}

static void app_activate(GtkApplication* gtkapp, gpointer yaabe_commons) {
	struct yaabe_gtkapp_ptrs_commons* commons = yaabe_commons;

	GListStore* atui_model = atui_gtk_model(commons->atui_root);
	
	GtkWidget* branches_pane = create_branches_pane(commons, atui_model);
	GtkWidget* leaves_pane = create_leaves_pane(commons);

	GtkWidget* tree_divider = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_paned_set_resize_start_child(GTK_PANED(tree_divider), true);
	gtk_paned_set_shrink_start_child(GTK_PANED(tree_divider), false);
	gtk_paned_set_resize_end_child(GTK_PANED(tree_divider), true);
	gtk_paned_set_shrink_end_child(GTK_PANED(tree_divider), false);
	gtk_widget_set_size_request(branches_pane, 50, 50);
	gtk_widget_set_size_request(leaves_pane, 50, 50);
	gtk_paned_set_start_child(GTK_PANED(tree_divider), branches_pane);
	gtk_paned_set_end_child(GTK_PANED(tree_divider), leaves_pane);

	

	GtkWidget* button_pane_complex = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	GtkWidget* buttonboxes = buttons_box(commons);
	gtk_widget_set_vexpand(tree_divider, true);
	gtk_box_append(GTK_BOX(button_pane_complex), tree_divider);
	gtk_box_append(GTK_BOX(button_pane_complex), buttonboxes);
	gtk_box_append(GTK_BOX(button_pane_complex),
		gtk_separator_new(GTK_ORIENTATION_HORIZONTAL));
	

	GtkWidget* window = gtk_application_window_new(gtkapp);
	gtk_window_set_title(GTK_WINDOW(window), "YAABE BIOS Editor");
	gtk_window_set_default_size(GTK_WINDOW(window), 800,500);

	//gtk_window_set_child(GTK_WINDOWYea, th(window), tree_divider);
	gtk_window_set_child(GTK_WINDOW(window), button_pane_complex);
	//gtk_window_set_child(GTK_WINDOW(window), buttonboxes);

	gtk_window_present(GTK_WINDOW(window)); //gtk4.10
}

int8_t yaabe_gtk(struct atom_tree* atree) {
	/* TODO  https://docs.gtk.org/gtk4/visual_index.html

	set title bar to currently open file
	path bar
	changelog of what was changed before the save? feels hard to impement
	menubar? of what?
		https://github.com/luigifab/awf-extended/blob/levelup/src/awf.c#L692
		file save/load ; about ; light-dark 
	extra columns like bit count, bios position, description.
		User selectable. Reorderable
	*/

	//TODO malloc this? g_application_run() is the main loop.
	struct yaabe_gtkapp_ptrs_commons commons;
	commons.atomtree_root = atree;
	commons.atui_root = atree->atui_root;

	commons.yaabe_gtk = gtk_application_new(NULL, G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(commons.yaabe_gtk,
		"activate", G_CALLBACK(app_activate), &commons
	);
	int16_t status = g_application_run(G_APPLICATION(commons.yaabe_gtk),0,NULL);
	g_object_unref(commons.yaabe_gtk);
	return status;
}
