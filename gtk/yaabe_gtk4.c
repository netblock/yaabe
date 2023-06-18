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
	GtkSelectionModel* leaves_model;
	uint16_t child_gobj_count;
	GObject* child_gobj[];
};

inline static void alloc_branch_cache(atui_branch* branch) {
	uint16_t gobj_count = branch->branch_count;

	branch->auxiliary = malloc(
		sizeof(struct yaabe_gtkapp_model_cache) +
		gobj_count * sizeof(GObject*)
	);

	struct yaabe_gtkapp_model_cache* models = branch->auxiliary;
	models->leaves_model = NULL;
	models->child_gobj_count = gobj_count;
	models->child_gobj[0] = NULL;
}
inline static void alloc_leaf_cache(atui_leaf* leaf, uint16_t num_children) {
	leaf->auxiliary = malloc(
		sizeof(struct yaabe_gtkapp_model_cache) +
		num_children * sizeof(GObject*)
	);

	struct yaabe_gtkapp_model_cache* models = leaf->auxiliary;
	models->leaves_model = NULL;
	models->child_gobj[0] = NULL;
	models->child_gobj_count = num_children;
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
		g_object_unref(submodels->leaves_model);
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
			g_object_unref(submodels->leaves_model);
			child_gobj_count = submodels->child_gobj_count;
			for (j=0; j < child_gobj_count; j++) {
				g_object_unref(submodels->child_gobj[j]);
			}
			free(submodels);
		}
	}

	//branches that the leaves point to should be adjacent to regular branches
	tree->max_branch_count += tree->max_inline_branch_count;
	while(tree->max_branch_count--)
		atui_destroy_tree_with_gtk(
			tree->child_branches[tree->max_branch_count]);

	free(tree);
}






static void leaves_key_column_spawner(GtkListItemFactory* factory,
		GtkListItem* list_item) { //setup to spawn a UI skeleton

	GtkWidget* expander = gtk_tree_expander_new();
	gtk_tree_expander_set_indent_for_icon(GTK_TREE_EXPANDER(expander), true);

	GtkWidget* label = gtk_label_new(NULL);
	gtk_tree_expander_set_child(GTK_TREE_EXPANDER(expander), label);

	gtk_list_item_set_child(list_item, expander);
}
static void leaves_key_column_recycler(GtkListItemFactory* factory, 
		GtkListItem* list_item) { //bind data to the UI skeleton

	GtkTreeExpander* expander = GTK_TREE_EXPANDER(
		gtk_list_item_get_child(list_item));
	GtkWidget* label = gtk_tree_expander_get_child(expander);

	GtkTreeListRow* tree_list_item = gtk_list_item_get_item(list_item);
	GObject* gobj_leaf = gtk_tree_list_row_get_item(tree_list_item);
	atui_leaf* leaf = g_object_get_data(gobj_leaf, "leaf");
	gtk_label_set_text(GTK_LABEL(label), leaf->name);

	gtk_tree_expander_set_list_row(expander, tree_list_item);
}

static void leaves_textbox_stray(GtkEventControllerFocus* focus_sense,
		gpointer leaf_gptr) {
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


static void leaves_val_column_spawner(GtkListItemFactory* factory,
		GtkListItem* list_item) { //setup

	GtkWidget* textbox = gtk_text_new();
	gtk_text_set_input_purpose(GTK_TEXT(textbox), GTK_INPUT_PURPOSE_DIGITS);

	// for leaves_textbox_stray()
	GtkEventController* focus_sense = gtk_event_controller_focus_new();
	gtk_widget_add_controller(textbox, focus_sense);

	gtk_list_item_set_child(list_item, textbox);
}
static void leaves_val_column_recycler(GtkListItemFactory* factory, 
		GtkListItem* list_item) { //bind

	GtkWidget* textbox = gtk_list_item_get_child(list_item);

	GtkTreeListRow* tree_list_item = gtk_list_item_get_item(list_item);
	GObject* gobj_leaf = gtk_tree_list_row_get_item(tree_list_item);
	atui_leaf* leaf = g_object_get_data(gobj_leaf, "leaf");

	char str_buff[ATUI_LEAVES_STR_BUFFER] = "\0";
	atui_get_to_text(leaf, str_buff);
	gtk_editable_set_text(GTK_EDITABLE(textbox), str_buff);

	g_signal_connect(textbox,"activate",
		G_CALLBACK(leaves_val_column_textbox_apply), leaf);


	GListModel* controller_list = gtk_widget_observe_controllers(textbox);
	GtkEventController* focus_sense = g_list_model_get_item(controller_list, 0);
	g_object_unref(controller_list);
	g_signal_connect(focus_sense, "leave",
		G_CALLBACK(leaves_textbox_stray), leaf);

}
static void leaves_val_column_cleaner(GtkListItemFactory* factory,
		 GtkListItem* list_item) { //unbind
// signals need to be removed, else they build up

	GtkWidget* textbox = gtk_list_item_get_child(list_item);

	//TODO: GtkText - unexpected blinking selection. Removing
	// these don't fix the warning:
	//gtk_editable_select_region(GTK_EDITABLE(textbox), 0, 0);
	//gtk_editable_set_position(GTK_EDITABLE(textbox), 0);

	g_signal_handlers_disconnect_matched(textbox, G_SIGNAL_MATCH_FUNC, 
		0,0,NULL,  G_CALLBACK(leaves_val_column_textbox_apply),  NULL);

	GListModel* controller_list = gtk_widget_observe_controllers(textbox);
	GtkEventController* focus_sense = g_list_model_get_item(controller_list, 0);
	g_object_unref(controller_list);
	g_signal_handlers_disconnect_matched(focus_sense, G_SIGNAL_MATCH_FUNC, 
		0,0,NULL,  G_CALLBACK(leaves_textbox_stray),  NULL);
}


static GListModel* leaves_tlmodel_func(gpointer parent_ptr, gpointer d){
//GtkTreeListModelCreateModelFunc for leaves

	GObject* gobj_parent = parent_ptr;
	atui_leaf* parent = g_object_get_data(gobj_parent, "leaf");
	struct yaabe_gtkapp_model_cache* leaf_models = parent->auxiliary;

	GListStore* children_model = NULL;
	uint16_t i = 0;

	if (parent->type & (ATUI_BITFIELD|ATUI_INLINE)) {
		children_model = g_list_store_new(G_TYPE_OBJECT);

		// if no cached gobjects, generate and cache them; otherwise use cache.
		if (leaf_models == NULL) {
			GObject* gobj_child;
			uint16_t num_children;
			atui_leaf* atui_children;

			if (parent->type & ATUI_INLINE) {
				atui_branch* branch = *(parent->inline_branch);
				num_children = branch->leaf_count;
				atui_children = branch->leaves;
			} else { // currently only otherwise bitfield
				num_children = parent->num_bitfield_children;
				atui_children = parent+1;
			}

			// the only time we're gonna be using this cache is in this tlmodel
			// function.
			alloc_leaf_cache(parent, num_children);
			leaf_models = parent->auxiliary;
			for(i=0; i < num_children; i++) {
				gobj_child = g_object_new(G_TYPE_OBJECT, NULL);
				g_object_set_data(gobj_child, "leaf", atui_children+i);
				leaf_models->child_gobj[i] = gobj_child;
				g_list_store_append(children_model, gobj_child);
			}


		} else { // use the cache
			for(i=0; i < leaf_models->child_gobj_count; i++) {
				g_list_store_append(children_model,
					leaf_models->child_gobj[i]);
			}
		}
	}
	return G_LIST_MODEL(children_model);
}

inline static GtkSelectionModel* create_leaves_selmodel(
		GListModel* leaves_lm) {

	/*
	GtkSingleSelection* sing_sel = gtk_single_selection_new(leaves_lm);
	gtk_single_selection_set_can_unselect(sing_sel, true);
	gtk_single_selection_set_autoselect(sing_sel, false);
	*/

	GtkNoSelection* no_sel = gtk_no_selection_new(leaves_lm);
	
	return GTK_SELECTION_MODEL(no_sel);
}

inline static void atuileaves_to_glistmodel(atui_branch* branch) {
	GObject* gobj_leaf;
	atui_leaf* leaf;
	GListStore* leavesmodel = g_list_store_new(G_TYPE_OBJECT);
	struct yaabe_gtkapp_model_cache* branch_models = branch->auxiliary;

	for(int i=0 ; i < branch->leaf_count ; i++) {
		leaf = branch->leaves + i;

		gobj_leaf = g_object_new(G_TYPE_OBJECT, NULL);
		g_object_force_floating(gobj_leaf); // so we can sink it into the model
		g_object_set_data(gobj_leaf, "leaf", leaf);
		g_list_store_append(leavesmodel, gobj_leaf);

		if (leaf->num_bitfield_children)
			i += leaf->num_bitfield_children;
	}

	GtkTreeListModel* treemodel = gtk_tree_list_model_new(
		G_LIST_MODEL(leavesmodel), false, true, leaves_tlmodel_func, NULL,NULL);
	GtkSelectionModel* sel_model = create_leaves_selmodel(
		G_LIST_MODEL(treemodel));

	branch_models->leaves_model = sel_model;

	//TODO Is this necessary?
	g_object_ref_sink(G_OBJECT(sel_model));
}

static void set_leaves_list(GtkSelectionModel* model,
		guint position, guint n_items, gpointer yaabe_commons) {

	struct yaabe_gtkapp_ptrs_commons* commons = yaabe_commons;

	GtkTreeListRow* tree_list_item = gtk_single_selection_get_selected_item(
		GTK_SINGLE_SELECTION(model));
	GObject* gobj_branch = gtk_tree_list_row_get_item(tree_list_item);
	atui_branch* branch = g_object_get_data(gobj_branch, "branch");

	struct yaabe_gtkapp_model_cache* branch_models = branch->auxiliary;
	if(branch_models->leaves_model == NULL) // if not cached, generate.
		atuileaves_to_glistmodel(branch);

	gtk_column_view_set_model(commons->leaves_columnview,
		branch_models->leaves_model);
}

inline static GtkWidget* create_leaves_pane(
		struct yaabe_gtkapp_ptrs_commons* commons) {

	atui_branch* root_branch = commons->atui_root;
	struct yaabe_gtkapp_model_cache* root_models = root_branch->auxiliary;
	
	// columnview abstract
	atuileaves_to_glistmodel(root_branch);
	GtkWidget* leaves_list = gtk_column_view_new(root_models->leaves_model);
	commons->leaves_columnview = GTK_COLUMN_VIEW(leaves_list);


	// create and attach columns
	GtkListItemFactory* factory;
	GtkColumnViewColumn* column;

	factory = gtk_signal_list_item_factory_new();
	g_signal_connect(factory,"setup",
		G_CALLBACK(leaves_key_column_spawner), NULL);
	g_signal_connect(factory,"bind",
		G_CALLBACK(leaves_key_column_recycler), NULL);
	column = gtk_column_view_column_new("names", factory);
	gtk_column_view_append_column(GTK_COLUMN_VIEW(leaves_list), column);

	factory = gtk_signal_list_item_factory_new();
	g_signal_connect(factory,"setup",
		G_CALLBACK(leaves_val_column_spawner), NULL);
	g_signal_connect(factory,"bind",
		G_CALLBACK(leaves_val_column_recycler), NULL);
	g_signal_connect(factory,"unbind",
		G_CALLBACK(leaves_val_column_cleaner), NULL);
	column = gtk_column_view_column_new("values", factory);
	gtk_column_view_append_column(GTK_COLUMN_VIEW(leaves_list), column);


	GtkWidget* scrolledlist = gtk_scrolled_window_new();
	gtk_scrolled_window_set_child(
		GTK_SCROLLED_WINDOW(scrolledlist), leaves_list);

	return scrolledlist;
}




inline static GListStore* atui_gtk_model(atui_branch* root) {
//for the tippy top of the tree

	alloc_branch_cache(root);

	GObject* gbranch = g_object_new(G_TYPE_OBJECT, NULL);
	g_object_force_floating(gbranch); // sink into model
	g_object_set_data(gbranch, "branch", root);
	GListStore* model = g_list_store_new(G_TYPE_OBJECT);
	g_list_store_append(model, gbranch);

	return model;
}

static GListModel* branch_tlmodel_func(gpointer ptr, gpointer data) {
//GtkTreeListModelCreateModelFunc for branches

	GObject* gobj_parent = ptr;
	atui_branch* parent = g_object_get_data(gobj_parent, "branch");
	struct yaabe_gtkapp_model_cache* branch_models = parent->auxiliary;

	GListStore* children = NULL; 
	int i = 0;

	if (parent->branch_count) {
		children = g_list_store_new(G_TYPE_OBJECT);

		// if no cached gobjects, generate and cache them; otherwise use cache.
		if (branch_models->child_gobj[0] == NULL) {
			GObject* gobj_child;
			for(i=0; i < parent->branch_count; i++){
				// the cache is also for the leaves
				alloc_branch_cache(parent->child_branches[i]);

				gobj_child = g_object_new(G_TYPE_OBJECT, NULL);
				g_object_set_data(gobj_child, "branch",
					parent->child_branches[i]);

				branch_models->child_gobj[i] = gobj_child;
				g_list_store_append(children, gobj_child);
			}
		} else {
			for(i=0; i < branch_models->child_gobj_count; i++) {
				g_list_store_append(children,
					branch_models->child_gobj[i]);
			}
		}
	}
	return G_LIST_MODEL(children);
}




static void branch_listitem_spawner(GtkSignalListItemFactory* factory,
		GtkListItem* list_item) { // setup
//TODO use https://docs.gtk.org/gtk4/class.Inscription.html

	GtkWidget* expander = gtk_tree_expander_new();
	gtk_tree_expander_set_indent_for_icon(GTK_TREE_EXPANDER(expander), true);
	//gtk_tree_expander_set_indent_for_depth(GTK_TREE_EXPANDER(expander), true);
	//gtk_tree_expander_set_hide_expander(GTK_TREE_EXPANDER(expander), false);

	GtkWidget* label = gtk_label_new(NULL);
	gtk_tree_expander_set_child(GTK_TREE_EXPANDER(expander), label);

	gtk_list_item_set_child(list_item, expander);
}
static void branch_listitem_recycler(GtkSignalListItemFactory* factory,
		GtkListItem* list_item) { // bind

	GtkTreeExpander* expander = GTK_TREE_EXPANDER(
		gtk_list_item_get_child(list_item));
	GtkWidget* row_label = gtk_tree_expander_get_child(expander);

	GtkTreeListRow* tree_list_item = gtk_list_item_get_item(list_item);
	GObject* gobj_branch = gtk_tree_list_row_get_item(tree_list_item);
	atui_branch* branch = g_object_get_data(gobj_branch, "branch");

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

	return scrolledlist;
}
static void app_activate(GtkApplication* gtkapp, gpointer yaabe_commons) {
	struct yaabe_gtkapp_ptrs_commons* commons = yaabe_commons;

	GListStore* atui_model = atui_gtk_model(commons->atui_root);
	
	GtkWidget* branches_pane = create_branches_pane(commons, atui_model);
	GtkWidget* leaves_pane = create_leaves_pane(commons);

	GtkWidget* divider = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_paned_set_resize_start_child (GTK_PANED(divider), true);
	gtk_paned_set_shrink_start_child (GTK_PANED(divider), false);
	gtk_paned_set_resize_end_child (GTK_PANED(divider), true);
	gtk_paned_set_shrink_end_child (GTK_PANED(divider), false);
	gtk_widget_set_size_request(branches_pane, 50, 50);
	gtk_widget_set_size_request(leaves_pane, 50, 50);
	gtk_paned_set_start_child(GTK_PANED(divider), branches_pane);
	gtk_paned_set_end_child(GTK_PANED(divider), leaves_pane);


	GtkWidget* window = gtk_application_window_new(gtkapp);
	gtk_window_set_title(GTK_WINDOW(window), "YAABE BIOS Editor");
	gtk_window_set_default_size(GTK_WINDOW(window), 550,250);

	gtk_window_set_child(GTK_WINDOW(window), divider);

	gtk_window_present(GTK_WINDOW(window)); //gtk4.10
}

int yaabe_gtk(struct atom_tree* atree) {
	struct yaabe_gtkapp_ptrs_commons commons;
	commons.atomtree_root = atree;
	commons.atui_root = atree->atui_root;

	commons.yaabe_gtk = gtk_application_new(NULL, G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(commons.yaabe_gtk, "activate", G_CALLBACK(app_activate),
        &commons);
	int status = g_application_run(G_APPLICATION(commons.yaabe_gtk), 0,NULL);

	return status;
}
