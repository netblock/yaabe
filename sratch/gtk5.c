// still GTK 4

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
/*
cc gtk.c `pkg-config --cflags --libs gtk4`

https://docs.gtk.org/gtk4/section-list-widget.html#list-styles
https://blog.gtk.org/2020/09/05/a-primer-on-gtklistview/
https://toshiocp.github.io/Gtk4-tutorial/sec26.html

https://blog.gtk.org/2020/09/21/gtkcolumnview/

https://stackoverflow.com/questions/74556059/how-to-build-a-tree-in-gtk4-4-10
*/


struct atom_test_raw {
	uint32_t antiem;
	uint32_t otheritem;
	uint8_t smolthing;
	uint16_t twobytes;
	uint16_t twobytes1;
	uint16_t twobytes2;
	uint16_t twobytes3;
	uint16_t twobytes4;
	uint16_t twobytes5;
	uint16_t twobytes6;
	uint16_t twobytes7;
	uint16_t twobytes8;
	uint16_t twobytes9;
	uint16_t twobytes10;
};





typedef struct atui_branch_ atui_branch;
typedef struct atui_leaf_ atui_leaf;
struct atui_leaf_ {
	char name[40];
	char* description;
	uint8_t type;
	char fieldbits; //bitfield portion, if it's a bitfield
	union {
		void*     val;
		uint8_t*  u8;
		uint16_t* u16;
		uint32_t* u32;
		uint64_t* u64;
	};
	void* auxilary;
};
struct  atui_branch_ {
	char name[40];
	char* description;

	atui_branch** child_branches;
	int branch_count;

	void* branch_aux; // alternative representation to leaves, if necessary
	atui_leaf* leaves;
	int leaf_count;

	void* atomleaves;
};
void atui_leaf_set_val(atui_leaf* leaf, uint64_t val) {
	uint64_t maxval = (1ULL << (leaf->type)) - 1; //needs the ULL for 64-bit
	if (val > maxval)
		val = maxval;
	switch(leaf->type) { // might be needed for bitfield structs
		case 8:
			*(leaf->u8) = val;
			break;
		case 16:
			*(leaf->u16) = val;
			break;
		case 32:
			*(leaf->u32) = val;
			break;
		case 64:
			*(leaf->u64) = val;
			break;
	}
}
uint64_t atui_leaf_get_val(atui_leaf* leaf) {
//  return *(leaf->u64) & ((1<<leaf->type)-1);
	switch(leaf->type) {
		case 8:
			return *(leaf->u8);
		case 16:
			return *(leaf->u16);
		case 32:
			return *(leaf->u32);
		case 64:
			return *(leaf->u64);
	}
}
uint64_t strtol_2(const char* str) {
	// TODO better compatibility with binary, hex, etc.
	char base = 0;
	if ((str[0] == '0') && (str[1] == 'b'))
		base = 2;
	return (uint64_t)strtol(str+base, NULL, base);
}


struct yaabe_gtkapp_ptrs_commons {
	atui_branch* root;
	GtkColumnView* leaves_columnview; // so branches can set leaves
	GListModel* stray_text_history; // un-Enter-key'd textbox resets
};
struct yaabe_gtkapp_branch_models { // to cache generated atui gobjects
	GListModel* leaves_model;
	GObject* child_gobj_branches[];
};
void alloc_aux_branch_models(atui_branch* branch) {
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

	while(tree->branch_count--)
		atui_destroy_tree_with_gtk(tree->child_branches[tree->branch_count]);

	free(tree);
}
void atui_destroy_tree(atui_branch* tree) {
	// I wonder if an iterative version would be better...
	while(tree->branch_count--)
		atui_destroy_tree(tree->child_branches[tree->branch_count]);
	free(tree);
}




#define ATUI_LEAF_TYPE(var) _Generic((var), \
	uint8_t:8, uint16_t:16, uint32_t:32, uint64_t:64, default:1)
#define LEAF(var) {.val=&(bios->var), .name=#var, .type=ATUI_LEAF_TYPE(bios->var)},
#define ATUI_FUNCIFY(PP_NAME, ...) \
static atui_branch* _##PP_NAME##_atui(struct atom_test_raw * bios, \
		unsigned int num_branches, atui_branch** import_children) { \
	int i = 0; \
	void* scratch;\
\
	atui_branch* table = NULL; \
	scratch = malloc( \
		sizeof(atui_branch) + \
		(sizeof(atui_branch*) * num_branches) +  \
		(sizeof(atui_leaf) * PP_NUM_ARG(__VA_ARGS__)) \
	); \
	table = scratch;\
	scratch = scratch + sizeof(atui_branch);\
\
	atui_branch** branches = NULL; \
	if (num_branches) { \
		branches = scratch; \
		if (import_children != NULL) { \
			for (i=0; i<num_branches; i++) { \
				branches[i] = import_children[i]; \
			} \
		} \
	} \
	scratch = scratch + num_branches * sizeof(atui_branch*);\
\
	atui_leaf* leaves = NULL; \
	if(PP_NUM_ARG(__VA_ARGS__)) { \
		leaves = scratch;\
		atui_leaf leavinit[] = {LEAVES(__VA_ARGS__)};\
		for(i=0; i < PP_NUM_ARG(__VA_ARGS__); i++) {\
			leaves[i] = leavinit[i]; \
		}\
	} \
\
	*table = (atui_branch) { \
		.name=#PP_NAME,.leaves=(atui_leaf*)leaves,\
		.leaf_count=PP_NUM_ARG(__VA_ARGS__), .atomleaves=bios, \
		.child_branches=branches, .branch_count=num_branches \
	}; \
	return table; \
}


// Throw the to-be-counted args into the depthcan and then measure the how
// full the depthcan is with the depthstick.
// Scale both dipstick and depthcan if you want to count more than 63 args.
#define PP_ARGCOUNTER_DIPSTICK \
	63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40, \
	39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16, \
	15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0
#define PP_ARGCOUNTER_DEPTHCAN_( \
	_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
	_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38, \
	_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56, \
	_57,_58,_59,_60,_61,_62,_63,N,...) N
#define PP_ARGCOUNTER_DEPTHCAN(...) PP_ARGCOUNTER_DEPTHCAN_(__VA_ARGS__)
#define PP_NUM_ARG(...) \
	PP_ARGCOUNTER_DEPTHCAN(__VA_ARGS__ __VA_OPT__(,) PP_ARGCOUNTER_DIPSTICK)

#define LEAVES(...) LEAVES_HELPER1(PP_NUM_ARG(__VA_ARGS__), __VA_ARGS__)
#define LEAVES_HELPER1(...) LEAVES_HELPER2(__VA_ARGS__)
#define LEAVES_HELPER2(N,...) L##N(__VA_ARGS__)
#define L0(...)
#define L1(var,...) LEAF(var)
#define L2(var,...) LEAF(var) L1(__VA_ARGS__)
#define L3(var,...) LEAF(var) L2(__VA_ARGS__)
#define L4(var,...) LEAF(var) L3(__VA_ARGS__)
#define L5(var,...) LEAF(var) L4(__VA_ARGS__)
#define L6(var,...) LEAF(var) L5(__VA_ARGS__)
#define L7(var,...) LEAF(var) L6(__VA_ARGS__)
#define L8(var,...) LEAF(var) L7(__VA_ARGS__)
#define L9(var,...) LEAF(var) L8(__VA_ARGS__)
#define L10(var,...) LEAF(var) L9(__VA_ARGS__)
#define L11(var,...) LEAF(var) L10(__VA_ARGS__)
#define L12(var,...) LEAF(var) L11(__VA_ARGS__)
#define L13(var,...) LEAF(var) L12(__VA_ARGS__)
#define L14(var,...) LEAF(var) L13(__VA_ARGS__)
#define L15(var,...) LEAF(var) L14(__VA_ARGS__)
#define L16(var,...) LEAF(var) L15(__VA_ARGS__)
#define L17(var,...) LEAF(var) L16(__VA_ARGS__)
#define L18(var,...) LEAF(var) L17(__VA_ARGS__)
#define L19(var,...) LEAF(var) L18(__VA_ARGS__)
#define L20(var,...) LEAF(var) L19(__VA_ARGS__)



/*
ATUI_FUNCIFY(atom_root)
ATUI_FUNCIFY(atom_test1)
ATUI_FUNCIFY(atom_test1_child1)
ATUI_FUNCIFY(atom_test1_child2)
ATUI_FUNCIFY(atom_test2)
ATUI_FUNCIFY(atom_test3)
ATUI_FUNCIFY(atom_test3_child1)
ATUI_FUNCIFY(atom_test3_child2)
ATUI_FUNCIFY(atom_test3_child3)
*/
ATUI_FUNCIFY(atom_root,
	antiem, otheritem)
ATUI_FUNCIFY(atom_test1,
	smolthing, twobytes, twobytes1, twobytes2)
ATUI_FUNCIFY(atom_test1_child1,
	twobytes5, twobytes6, twobytes7, twobytes8, twobytes9, twobytes10)
ATUI_FUNCIFY(atom_test1_child2,
	antiem, otheritem, smolthing, twobytes, twobytes1, twobytes2, twobytes3,
	twobytes4, twobytes5, twobytes6, twobytes7, twobytes8, twobytes9,
	twobytes10)
ATUI_FUNCIFY(atom_test2)
ATUI_FUNCIFY(atom_test3,
	twobytes6, twobytes7, twobytes8, twobytes9, twobytes10)
ATUI_FUNCIFY(atom_test3_child1,
	twobytes7, twobytes8, twobytes9, twobytes10)
ATUI_FUNCIFY(atom_test3_child2,
	twobytes8, twobytes9, twobytes10)
ATUI_FUNCIFY(atom_test3_child3,
	twobytes9, twobytes10)


atui_branch* atui_build_tree(struct atom_test_raw* atest) {
	// TODO a preproccessor func to calc the array size 
	// may freak out syntax highlighers

	return _atom_root_atui(atest, 3, (atui_branch*[]){
		_atom_test1_atui(atest, 2, (atui_branch*[]){ 
			_atom_test1_child1_atui(atest,0,NULL),
			_atom_test1_child2_atui(atest,0,NULL),
		}),
		_atom_test2_atui(atest,0,NULL),
		_atom_test3_atui(atest, 3, (atui_branch*[]){ 
			_atom_test3_child1_atui(atest,0,NULL),
			_atom_test3_child2_atui(atest,0,NULL),
			_atom_test3_child3_atui(atest,0,NULL),
		})
	});

}




/************************************/





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
	int n = sprintf(str_buff, "%u", atui_leaf_get_val(leaf)); // TODO atom type?
	GtkEntryBuffer* buffer = gtk_text_get_buffer(GTK_TEXT(textbox));
	gtk_entry_buffer_set_text(buffer, str_buff, n);
}
static void leaves_val_column_textbox_apply(
		GtkEditable* textbox, gpointer leaf_gptr) {
	atui_leaf* leaf = leaf_gptr;
	printf("before: (%d-bit: %d , %d); input: (%s , %d); ",
		leaf->type,    atui_leaf_get_val(leaf),    *(leaf->u32), 
		gtk_editable_get_text(textbox), 
		strtol_2(gtk_editable_get_text(textbox)));
	atui_leaf_set_val(leaf, strtol_2(gtk_editable_get_text(textbox)));
	
	char str_buff[20];
	sprintf(str_buff, "%d", atui_leaf_get_val(leaf));
	gtk_editable_set_text(textbox, str_buff);
	printf("after: %d (%s; %d)\n",
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
	int n = sprintf(str_buff, "%d", *(leaf->u16));
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

static GtkWidget* create_leaves_pane(
		struct yaabe_gtkapp_ptrs_commons* commons) {
	
	// columnview abstract
	GListModel* model = atuileaves_to_glistmodel(commons->root);
	GtkSelectionModel* sel_model = create_leaves_selmodel(model);
	GtkWidget* leaves_list = gtk_column_view_new(sel_model);
	commons->leaves_columnview = GTK_COLUMN_VIEW(leaves_list);

	commons->stray_text_history = model;


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





GListStore* atui_gtk_model(atui_branch* root) {
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
	sprintf(buff, "%s (depth %i)", branch->name,
		gtk_tree_list_row_get_depth(tree_list_item));
	gtk_label_set_text(GTK_LABEL(row_label), buff);

	gtk_tree_expander_set_list_row(expander, tree_list_item);
}


GtkWidget* create_branches_pane(struct yaabe_gtkapp_ptrs_commons* commons,
		GListStore* atui_model) {

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

	GListStore* atui_model = atui_gtk_model(commons->root);
	
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
	gtk_window_set_default_size(GTK_WINDOW(window), 350,250);

	gtk_window_set_child(GTK_WINDOW(window), divider);

	gtk_window_present(GTK_WINDOW(window)); //gtk4.10
}


int main(int argc, char* argv[]) {
	struct atom_test_raw atest = { //pretend vals from bios
		.antiem = 1, \
		.otheritem = 3, \
		.smolthing = 5, \
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
