#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include <atui.h>
#include <atomtree.h>
/*
https://docs.gtk.org/gtk4/section-list-widget.html#list-styles
https://blog.gtk.org/2020/09/05/a-primer-on-gtklistview/
https://toshiocp.github.io/Gtk4-tutorial/sec26.html

https://blog.gtk.org/2020/09/21/gtkcolumnview/

https://stackoverflow.com/questions/74556059/how-to-build-a-tree-in-gtk4-4-10
*/



struct yaabe_gtkapp_ptrs_commons {
	GtkApplication* yaabe_gtk;

	struct atom_tree* atomtree_root;
	atui_branch* atui_root;

	GtkColumnView* leaves_columnview; // so branches can set leaves
	//GListModel* stray_text_history; // un-Enter-key'd textbox resets.
};

struct yaabe_gtkapp_branch_models { // to cache generated atui gobjects
	GListModel* leaves_model;
	GObject* child_gobj_branches[];
};

void alloc_aux_branch_models(atui_branch* branch) {
		// caching; see struct
	branch->branch_aux = malloc(
		sizeof(struct yaabe_gtkapp_branch_models) +
		branch->branch_count * sizeof(GObject*)
	);
	struct yaabe_gtkapp_branch_models* models = branch->branch_aux;
	models->leaves_model = NULL;
	models->child_gobj_branches[0] = NULL;
}

void atui_destroy_tree_with_gtk(atui_branch* tree) {
	// the leaves gobjects should be sunk into the model, and branch_aux points
	// to the model.
	if (tree->branch_aux != NULL) {
		struct yaabe_gtkapp_branch_models* submodels = tree->branch_aux;
		g_object_unref(submodels->leaves_model);
		for (int i = 0; i < tree->branch_count; i++)
			g_object_unref(submodels->child_gobj_branches[i]);

		free(submodels);
	}
	tree->max_branch_count += tree->max_inline_branch_count;
	while(tree->max_branch_count--)
		atui_destroy_tree_with_gtk(
			tree->child_branches[tree->max_branch_count]);

	free(tree);
}



static void leaves_key_column_spawner(GtkListItemFactory* factory,
		GtkListItem* list_item) { //setup to spawn a UI skeleton

	gtk_list_item_set_child(list_item, gtk_label_new(NULL));
}
static void leaves_key_column_recycler(GtkListItemFactory* factory, 
		GtkListItem* list_item) { //bind data to the UI skeleton

	GtkWidget* label = gtk_list_item_get_child(list_item);
	GObject* gobj_leaf = gtk_list_item_get_item(list_item);
	atui_leaf* leaf = g_object_get_data(gobj_leaf, "leaf");
	gtk_label_set_text(GTK_LABEL(label), leaf->name);
}

static void leaves_textbox_stray(GtkEventControllerFocus* focus_sense,
		gpointer leaf_gptr) {
	GtkWidget* textbox = gtk_event_controller_get_widget(
		GTK_EVENT_CONTROLLER(focus_sense));
	atui_leaf* leaf = leaf_gptr;

	char str_buff[20];
	int n = sprintf(str_buff, "%u", atui_leaf_get_val(leaf)); 
	// TODO atom type, like for strings?
	GtkEntryBuffer* buffer = gtk_text_get_buffer(GTK_TEXT(textbox));
	gtk_entry_buffer_set_text(buffer, str_buff, n);
}
static void leaves_val_column_textbox_apply(
		GtkEditable* textbox, gpointer leaf_gptr) {
	atui_leaf* leaf = leaf_gptr;
	printf("before: (%u-bit: %u , %u); input: (%s , %u); ",
		leaf->type,    atui_leaf_get_val(leaf),    *(leaf->u16), 
		gtk_editable_get_text(textbox), 
		strtol_2(gtk_editable_get_text(textbox)));
	atui_leaf_set_val(leaf, strtol_2(gtk_editable_get_text(textbox)));
	
	char str_buff[20];
	sprintf(str_buff, "%u", atui_leaf_get_val(leaf));
	gtk_editable_set_text(textbox, str_buff);
	printf("after: %u (%s; %u)\n",
		atui_leaf_get_val(leaf), gtk_editable_get_text(textbox), *(leaf->u32));
}


static void leaves_val_column_spawner(GtkListItemFactory* factory,
		GtkListItem* list_item) { //setup

	GtkWidget* textbox = gtk_text_new();
	gtk_text_set_input_purpose(GTK_TEXT(textbox), GTK_INPUT_PURPOSE_DIGITS);

	// if the user doesn't hit enter to apply changes, clean up on focus loss
	GtkEventController* focus_sense = gtk_event_controller_focus_new();
	gtk_widget_add_controller(textbox, focus_sense);
	
	gtk_list_item_set_child(list_item, textbox);
}
static void leaves_val_column_recycler(GtkListItemFactory* factory, 
		GtkListItem* list_item) { //bind

	GtkWidget* textbox = gtk_list_item_get_child(list_item);
	GObject* gobj_leaf = gtk_list_item_get_item(list_item);
	atui_leaf* leaf = g_object_get_data(gobj_leaf, "leaf");

	char str_buff[20];
	int n = sprintf(str_buff, "%u", atui_leaf_get_val(leaf));
	GtkEntryBuffer* buffer = gtk_text_get_buffer(GTK_TEXT(textbox));
	gtk_entry_buffer_set_text(buffer, str_buff, n);

	g_signal_connect(textbox,"activate",
		G_CALLBACK(leaves_val_column_textbox_apply), leaf);


	GListModel* controller_list = gtk_widget_observe_controllers(textbox);
	GtkEventController* focus_sense = g_list_model_get_item(controller_list, 0);
	g_object_unref(controller_list);
	g_signal_connect(focus_sense, "leave",
		G_CALLBACK(leaves_textbox_stray), leaf);

	//g_signal_connect(textbox,"leave",
	//	G_CALLBACK(leaves_textbox_stray), NULL);

}
static void leaves_val_column_cleaner(GtkListItemFactory* factory,
		 GtkListItem* list_item) { //unbind
// signals need to be removed, else they build up
	GtkWidget* textbox = gtk_list_item_get_child(list_item);

	g_signal_handlers_disconnect_matched(textbox, G_SIGNAL_MATCH_FUNC, 
		0,0,NULL,  G_CALLBACK(leaves_val_column_textbox_apply),  NULL);

	GListModel* controller_list = gtk_widget_observe_controllers(textbox);
	GtkEventController* focus_sense = g_list_model_get_item(controller_list, 0);
	g_object_unref(controller_list);
	g_signal_handlers_disconnect_matched(focus_sense, G_SIGNAL_MATCH_FUNC, 
		0,0,NULL,  G_CALLBACK(leaves_textbox_stray),  NULL);
}





static GListModel* atuileaves_to_glistmodel(atui_branch* branch) {
//https://stackoverflow.com/questions/74838995/gobject-to-hold-a-pointer
	GObject* gobj_leaf;
	GListStore* leavesmodel = g_list_store_new(G_TYPE_OBJECT);

	for(int i=0 ; i < branch->leaf_count ; i++) {
		gobj_leaf = g_object_new(G_TYPE_OBJECT, NULL);
		g_object_force_floating(gobj_leaf); // so we can sink it into the model
		g_object_set_data(gobj_leaf, "leaf", &(branch->leaves[i]));
		g_list_store_append(leavesmodel, gobj_leaf);
	}

	struct yaabe_gtkapp_branch_models* branch_models = branch->branch_aux;
	branch_models->leaves_model = G_LIST_MODEL(leavesmodel);

	//TODO Is this necessary?
	g_object_ref_sink(G_OBJECT(branch_models->leaves_model));

	return G_LIST_MODEL(leavesmodel);
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


static void set_leaves_list(GtkSelectionModel* model,
		guint position, guint n_items, gpointer yaabe_commons) {
//https://docs.gtk.org/gtk4/signal.SelectionModel.selection-changed.html

	struct yaabe_gtkapp_ptrs_commons* commons = yaabe_commons;

	GtkTreeListRow* tree_list_item = gtk_single_selection_get_selected_item(
		GTK_SINGLE_SELECTION(model));
	GObject* gobj_branch = gtk_tree_list_row_get_item(tree_list_item);
	atui_branch* branch = g_object_get_data(gobj_branch, "branch");

	struct yaabe_gtkapp_branch_models* branch_models = branch->branch_aux;
	if(branch_models->leaves_model == NULL) // caching
		atuileaves_to_glistmodel(branch);


	gtk_column_view_set_model(commons->leaves_columnview,
		create_leaves_selmodel(branch_models->leaves_model)
	);
}

inline static GtkWidget* create_leaves_pane(
		struct yaabe_gtkapp_ptrs_commons* commons) {
	
	// columnview abstract
	GListModel* model = atuileaves_to_glistmodel(commons->atui_root);
	GtkSelectionModel* sel_model = create_leaves_selmodel(model);
	GtkWidget* leaves_list = gtk_column_view_new(sel_model);
	commons->leaves_columnview = GTK_COLUMN_VIEW(leaves_list);

	//commons->stray_text_history = model;


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
	alloc_aux_branch_models(root);

	GObject* gbranch = g_object_new(G_TYPE_OBJECT, NULL);
	g_object_force_floating(gbranch); // sink into model
	g_object_set_data(gbranch, "branch", root);
	GListStore* model = g_list_store_new(G_TYPE_OBJECT);
	g_list_store_append(model, gbranch);

	return model;
}

//GtkTreeListModelCreateModelFunc
static GListModel* branch_tlmodel_func(gpointer ptr, gpointer data) {
	GObject* gobj_parent = ptr;
	atui_branch* parent = g_object_get_data(gobj_parent, "branch");
	struct yaabe_gtkapp_branch_models* branch_models = parent->branch_aux;

	GListStore* children = NULL; 
	int i = 0;

	if (parent->branch_count) {
		children = g_list_store_new(G_TYPE_OBJECT);

		// if no cached gobjects, generate and cache them; otherwise use cache.
		if (branch_models->child_gobj_branches[0] == NULL) {
			GObject* gobj_child;
			for(i=0; i < parent->branch_count; i++){
				// hopefully this is the only place, besides root, where we 
				// alloc the yaabe_gtkapp_branch_models.
				alloc_aux_branch_models(parent->child_branches[i]);

				gobj_child = g_object_new(G_TYPE_OBJECT, NULL);
				g_object_set_data(gobj_child, "branch",
					parent->child_branches[i]);

				branch_models->child_gobj_branches[i] = gobj_child;
				g_list_store_append(children, gobj_child);
			}
		} else {
			for(i=0; i < parent->branch_count; i++) {
				g_list_store_append(children,
					branch_models->child_gobj_branches[i]);
			}
		}
	}
	return G_LIST_MODEL(children);
}




static void branch_listitem_spawner(GtkSignalListItemFactory* factory,
		GtkListItem* list_item) { // setup
// https://stackoverflow.com/questions/74556059/how-to-build-a-tree-in-gtk4-4-10
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

	char buff[50];
	sprintf(buff, "%s", branch->name);
	gtk_label_set_text(GTK_LABEL(row_label), buff);

	gtk_tree_expander_set_list_row(expander, tree_list_item);
}


inline static GtkWidget* create_branches_pane(
		struct yaabe_gtkapp_ptrs_commons* commons, GListStore* atui_model) {

	//Treelist, along with branch_tlmodel_func, creates our collapsable model.
	GtkTreeListModel* tlist_atui = gtk_tree_list_model_new(
		G_LIST_MODEL(atui_model), false, true, branch_tlmodel_func, NULL,NULL);

	GtkSingleSelection* sel_model = gtk_single_selection_new(
		G_LIST_MODEL(tlist_atui));

	// change the leaves pane's model based on the what is selected in brances
	g_signal_connect(sel_model, "selection-changed",
		G_CALLBACK(set_leaves_list), commons);
		//G_CALLBACK(set_leaves_list), leaves_model);
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

	//GtkWidget* scroll_frame = gtk_frame_new(NULL);
	//gtk_frame_set_child(GTK_FRAME(scroll_frame), scrolledlist);

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

/*
int main(int argc, char* argv[]) {
	struct atom_test_raw atest = { //pretend vals from bios
		.antiem = 1, \
		.otheritem = 3, \
		.smolthing = 5, \
		.strthing = "hello!", \
		.twobytes = 7,  \
		.twobytes1 = 11 , \
		.twobytes2 = 13 , \
		.twobytes3 = 17 , \
		.twobytes4 = 19 , \
		.twobytes5 = 23 , \
		.twobytes6 = 29 , \
		.twobytes7 = 31 , \
		.twobytes8 = 37 , \
		.twobytes9 = 41 , \
		.twobytes10 = 43 , \
	};
	struct yaabe_gtkapp_ptrs_commons commons2;
	commons2.root = atui_build_tree(&atest);

	GtkApplication* yaabe_gtkapp = gtk_application_new(NULL,
		G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (yaabe_gtkapp, "activate", G_CALLBACK(app_activate),
		&commons2);
	int status = g_application_run(G_APPLICATION(yaabe_gtkapp), argc, argv);

	g_object_unref(yaabe_gtkapp);
	return status;
}
*/
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
