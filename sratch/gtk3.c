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

typedef struct atui_branch_ atui_branch;
typedef struct atui_leaf_ atui_leaf;
#define STRTYPE(var) _Generic((var), \
	uint8_t:8, uint16_t:16, uint32_t:32, uint64_t:64, default:"other")
//#define LEAF(var) {.val=&(X.var), .name=#var, .type=STRTYPE(X.var)},
 
struct atui_leaf_ {
/*
description would be a 1D array per table for easy translation
for name, type, fieldbits, predefined like it is in array.c of srach
the val needs to be programmed runtime for the pointer

GTK: upper layer struct for the leftside/table selection like
	struct gtk_branches_to_leaves {
		atui_branc branch;
		GListModel* leavesmodel;

		//atui_branch* child_branches; //maybe
		//int num_child_branches;
	};
where upon listview selection of the table, we
gtk_column_view_set_model(leaves_colview, gtk_branches_to_leaves.leavesmodel);
*/
	char name[40];
	char* description;
	//enum {u8=8, u16=16, u32=32, u64=64} type;
	uint8_t type;
	char fieldbits; //bitfield portion, if it's a bitfield
	union {
		void*     val;
		uint8_t*  u8;
		uint16_t* u16;
		uint32_t* u32;
		uint64_t* u64;
	};
};
struct  atui_branch_ {
	// the branches of atomtree need to be abstract and of the same type.
	// need to figure out how 
	char name[40];
	char* description;

	atui_branch** child_branches;
	int branch_count;

	atui_leaf* leaves;
	int leaf_count;

	void* atomleaves;
};
//#define LEAF(var) {.val=&(X.var), .name=#var, .type=STRTYPE(X.var)},
#define BRANCH(var) .name=#var, leaves=var##_leaves, 

/*
#define TABLE(name, ...)
#define _LEAVES(name, ...) atui
*/

#define ATUI_LEAF_TYPE(var) _Generic((var), \
	uint8_t:8, uint16_t:16, uint32_t:32, uint64_t:64, default:1)
//#define LEAF(var) {.val=&(X.var), .name=#var, .type=ATUI_LEAF_TYPE(X.var)},
#define LEAF(var) {.val=&(bios->var), .name=#var, .type=ATUI_LEAF_TYPE(bios->var)},

//#define funcify(name, L, B) 

/*
#define ATUI_FUNCIFY(PP_NAME) \
static inline atui_branch* _##PP_NAME##_atui(struct PP_NAME * bios) { \
	atui_branch* table = malloc(sizeof(atui_branch) + \
		PP_NUM_ARG(FUNC_LEAVES) * sizeof(atui_leaf)); \
	atui_leaf* leaves = NULL;\
	if(PP_NUM_ARG(FUNC_LEAVES)) { \
		atui_leaf* leaves = (atui_leaf*)(table + sizeof(atui_branch)); \
		atui_leaf leavinit[] = {LEAVES(FUNC_LEAVES)};\
		memcpy(leaves, leavinit, PP_NUM_ARG(FUNC_LEAVES)*sizeof(atui_leaf));\
	} \
	*table = (atui_branch){.name=#PP_NAME, .leaves=leaves, .leaf_count=PP_NUM_ARG(FUNC_LEAVES), .atomleaves=bios };\
	return table;\
}
*/

#define ATUI_FUNCIFY(PP_NAME) \
struct PP_NAME;\
static atui_branch* _##PP_NAME##_atui(struct PP_NAME * bios, \
		int num_branches, atui_branch** import_children) { \
	int i = 0;/*loops*/  \
	atui_branch* table = malloc(sizeof(atui_branch) + \
		num_branches * sizeof(atui_branch*) + \
		PP_NUM_ARG(FUNC_LEAVES) * sizeof(atui_leaf) \
	); \
\
	atui_branch** branches = NULL; \
	if (num_branches) { \
		branches = (atui_branch**)(table + sizeof(atui_branch)); \
		if (import_children != NULL) { \
			for (i=0; i<num_branches; i++) { \
				branches[i] = import_children[i]; \
			} \
		} \
	} \
\
	atui_leaf* leaves = NULL; \
	if(PP_NUM_ARG(FUNC_LEAVES)) { \
		leaves = (atui_leaf*)(table + sizeof(atui_branch) + \
		num_branches * sizeof(atui_branch*) ); \
		atui_leaf leavinit[] = {LEAVES(FUNC_LEAVES)};\
		for (i=PP_NUM_ARG(FUNC_LEAVES); i--; ) {\
			leaves[i] = leavinit[i]; \
		}; \
	/*memcpy(leaves, leavinit, PP_NUM_ARG(FUNC_LEAVES)*sizeof(atui_leaf));*/ \
	} \
\
	*table = (atui_branch) { \
		.name=#PP_NAME, \
		.leaves=leaves, .leaf_count=PP_NUM_ARG(FUNC_LEAVES), .atomleaves=bios, \
		.child_branches=branches, .branch_count=num_branches \
	}; \
	return table; \
}
// Throw the to-be-counted args into the depthcan and then measure the how
// full the depthcan is with the depthstick.
// Scale both ruler and depthcan if you want to count more than 63 args.
#define PP_ARGCOUNTER_RULER \
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
	PP_ARGCOUNTER_DEPTHCAN(__VA_ARGS__ __VA_OPT__(,) PP_ARGCOUNTER_RULER)

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


#define FUNC_LEAVES

ATUI_FUNCIFY(atom_root)
ATUI_FUNCIFY(atom_test1)
ATUI_FUNCIFY(atom_test1_child1)
ATUI_FUNCIFY(atom_test1_child2)
ATUI_FUNCIFY(atom_test2)
ATUI_FUNCIFY(atom_test3)
ATUI_FUNCIFY(atom_test3_child1)
ATUI_FUNCIFY(atom_test3_child2)
ATUI_FUNCIFY(atom_test3_child3)

atui_branch* atui_build_tree() {
	// TODO a preproccessor func to calc the array size 
	// may freak out syntax highlighers
	//return _atom_root_atui(NULL, 0, NULL);

	return _atom_root_atui(NULL, 3, (atui_branch*[]){
		_atom_test1_atui(NULL, 2, (atui_branch*[]){ 
			_atom_test1_child1_atui(NULL,0,NULL),
			_atom_test1_child2_atui(NULL,0,NULL),
		}),
		_atom_test2_atui(NULL,0,NULL),
		_atom_test3_atui(NULL, 3, (atui_branch*[]){ 
			_atom_test3_child1_atui(NULL,0,NULL),
			_atom_test3_child2_atui(NULL,0,NULL),
			_atom_test3_child3_atui(NULL,0,NULL),
		})
	});

}
void atui_destroy_tree(atui_branch* tree) {
	// I wonder if an iterative version would be better...
	while(tree->branch_count--)
		atui_destroy_tree(tree->child_branches[tree->branch_count]);
	free(tree);
}

GListStore* atui_gtk_model(atui_branch* root) {
	GObject* gbranch = g_object_new(G_TYPE_OBJECT, NULL);
	g_object_set_data(gbranch, "branch", root);
	GListStore* model = g_list_store_new(G_TYPE_OBJECT);
	g_list_store_append(model, gbranch);

/*	GObject* gbranch;
	GListStore* model = g_list_store_new(G_TYPE_OBJECT);
	for(int i=0; i<root->branch_count; i++) {
		GObject* gbranch = g_object_new(G_TYPE_OBJECT, NULL);
		g_object_set_data(gbranch, "branch", root->child_branches[i]);
		g_list_store_append(model, gbranch);
	}
*/
	return model;
}



//GtkTreeListModelCreateModelFunc
static GListModel* TLModel_Func(gpointer ptr, gpointer data) {
	GObject* gobj_parent = ptr;
	atui_branch* parent = g_object_get_data(gobj_parent, "branch");
	GListStore* children = NULL;
	GObject* gobj_child_branch;
	if (parent->branch_count) {
		//g_print("%s:\n", parent->name);
		children = g_list_store_new(G_TYPE_OBJECT);

		for(int i = 0; i < parent->branch_count; i++){
			//g_print("   %s\n", parent->child_branches[i]->name);
			gobj_child_branch = g_object_new(G_TYPE_OBJECT, NULL);
			g_object_set_data(gobj_child_branch, "branch",
				parent->child_branches[i]);
			g_list_store_append(children, gobj_child_branch);
		}
	}
	return G_LIST_MODEL(children);
}
//	(GtkTreeListModelCreateModelFunc) _TLModel_Func; //typecast



// https://stackoverflow.com/questions/74556059/how-to-build-a-tree-in-gtk4-4-10
//TODO use https://docs.gtk.org/gtk4/class.Inscription.html
// attach a button widget? gridview to manually indent?

/*
static void listitem_spawner(GtkSignalListItemFactory* factory,
		GtkListItem* list_item) { // setup

	GtkWidget* expander = gtk_tree_expander_new();
	gtk_tree_expander_set_indent_for_icon(GTK_TREE_EXPANDER(expander), true);
	gtk_tree_expander_set_indent_for_depth(GTK_TREE_EXPANDER(expander), true);
	gtk_tree_expander_set_hide_expander(GTK_TREE_EXPANDER(expander), false);

	GtkWidget* label = gtk_label_new("aaa");
	//gtk_tree_expander_set_child(GTK_TREE_EXPANDER(expander), label);

	GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_append(GTK_BOX(box), expander);
	gtk_box_append(GTK_BOX(box), label);
	gtk_list_item_set_child(list_item, box);


	//gtk_list_item_set_child(list_item, expander);
}
static void listitem_recycler(GtkSignalListItemFactory* factory,
		GtkListItem* list_item) { // bind

	GtkTreeListRow* tree_list_item = gtk_list_item_get_item(list_item);
	GObject* gobj_branch = gtk_tree_list_row_get_item(tree_list_item);
	atui_branch* branch = g_object_get_data(gobj_branch, "branch");

	GtkWidget* box = gtk_list_item_get_child(list_item);
	GtkWidget* expander = gtk_widget_get_first_child(box);
	GtkWidget* row_label = gtk_widget_get_last_child(box);

	gtk_box_set_spacing(GTK_BOX(box),
		15*gtk_tree_list_row_get_depth(tree_list_item));

//	GtkWidget* expander = gtk_list_item_get_child(list_item);
//	GtkWidget* row_label = gtk_tree_expander_get_child(
//		GTK_TREE_EXPANDER(expander));

	char buff[30];
	sprintf(buff, "%s (depth %i)", branch->name, 
		gtk_tree_list_row_get_depth(tree_list_item));

	gtk_label_set_text(GTK_LABEL(row_label), buff);

}
*/
static void listitem_spawner(GtkSignalListItemFactory* factory,
		GtkListItem* list_item) { // setup

	GtkWidget* expander = gtk_tree_expander_new();
	gtk_tree_expander_set_indent_for_icon(GTK_TREE_EXPANDER(expander), true);
	//gtk_tree_expander_set_indent_for_depth(GTK_TREE_EXPANDER(expander), true);
	//gtk_tree_expander_set_hide_expander(GTK_TREE_EXPANDER(expander), false);

	GtkWidget* label = gtk_label_new(NULL);
	gtk_tree_expander_set_child(GTK_TREE_EXPANDER(expander), label);

	gtk_list_item_set_child(list_item, expander);
}
static void listitem_recycler(GtkSignalListItemFactory* factory,
		GtkListItem* list_item) { // bind

	GtkTreeExpander* expander = GTK_TREE_EXPANDER(
		gtk_list_item_get_child(list_item));
	GtkWidget* row_label = gtk_tree_expander_get_child(expander);

	GtkTreeListRow* tree_list_item = gtk_list_item_get_item(list_item);
	GObject* gobj_branch = gtk_tree_list_row_get_item(tree_list_item);
	atui_branch* branch = g_object_get_data(gobj_branch, "branch");

	char buff[30];
	sprintf(buff, "%s (depth %i)", branch->name,
		gtk_tree_list_row_get_depth(tree_list_item));

	gtk_tree_expander_set_list_row(expander, tree_list_item);
	gtk_label_set_text(GTK_LABEL(row_label), buff);
}

//https://docs.gtk.org/gtk4/signal.SelectionModel.selection-changed.html
static void set_leaves_list(GtkSelectionModel* model,
		guint position, guint n_items, gpointer leaves_model) {

//	 GObject* gobj_branch = gtk_single_selection_get_selected_item(
//		GTK_SINGLE_SELECTION(model));
	GtkTreeListRow* tree_list_item = gtk_single_selection_get_selected_item(
		GTK_SINGLE_SELECTION(model));
		
	GObject* gobj_branch = gtk_tree_list_row_get_item(tree_list_item);
	atui_branch* branch = g_object_get_data(gobj_branch, "branch");
	printf("selection is now: %s\n", branch->name);
}

static void app_activate(GtkApplication* gtkapp, gpointer data) {
	GtkWidget* window = gtk_application_window_new(gtkapp);
	gtk_window_set_title(GTK_WINDOW(window), "YAABE BIOS Editor");
	gtk_window_set_default_size(GTK_WINDOW(window), 200,200);
	GtkWidget* swindow = gtk_scrolled_window_new();
	gtk_window_set_child(GTK_WINDOW(window), swindow);
	gtk_scrolled_window_set_max_content_height(GTK_SCROLLED_WINDOW(swindow), 200);

	atui_branch* root = atui_build_tree();
	//printf("%s\n", root->child_branches[0]->name);
	GListStore* atui_model = atui_gtk_model(root);
	GtkTreeListModel* tlist_atui = gtk_tree_list_model_new(
		G_LIST_MODEL(atui_model), false, true, TLModel_Func, NULL, NULL);

	void* leaves_model;
	GtkSingleSelection* select_mod = gtk_single_selection_new(
	//GtkNoSelection* select_mod = gtk_no_selection_new(
		G_LIST_MODEL(tlist_atui));
	g_signal_connect(select_mod, "selection-changed", 
		G_CALLBACK(set_leaves_list), leaves_model);
	gtk_single_selection_set_autoselect(select_mod,false);
	


	GtkListItemFactory* list_factory = gtk_signal_list_item_factory_new();
	g_signal_connect(list_factory, "setup", G_CALLBACK(listitem_spawner), NULL);
	g_signal_connect(list_factory, "bind", G_CALLBACK(listitem_recycler), NULL);

	GtkWidget* list = gtk_list_view_new(GTK_SELECTION_MODEL(select_mod), list_factory);
	//GtkWidget* list = gtk_list_view_new(GTK_SELECTION_MODEL(tlist_atui), list_factory);
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(swindow), list);

	gtk_window_present(GTK_WINDOW(window));//gtk4.10
	//gtk_widget_show(window);
}


int main(int argc, char* argv[]) {
	int status;

	GtkApplication* yaabe_gtkapp = gtk_application_new("org.yaabe",
		G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (yaabe_gtkapp, "activate", G_CALLBACK(app_activate), NULL);
	status = g_application_run(G_APPLICATION(yaabe_gtkapp), argc, argv);
	g_object_unref(yaabe_gtkapp);
	return status;
}
