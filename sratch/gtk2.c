// still gtk4

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <stdint.h>
/*
cc gtk.c `pkg-config --cflags --libs gtk4`

https://docs.gtk.org/gtk4/section-list-widget.html#list-styles
https://blog.gtk.org/2020/09/05/a-primer-on-gtklistview/
https://toshiocp.github.io/Gtk4-tutorial/sec26.html

https://blog.gtk.org/2020/09/21/gtkcolumnview/

https://developer-old.gnome.org/gtk4/stable/GtkColumnView.html
https://developer-old.gnome.org/gtk4/stable/GtkSelectionModel.html

file browser?: 
https://www.reddit.com/r/gnome/comments/ya3n7t/gtk_file_chooser_has_been_ported_to_gtkcolumnview/


It seems like you create the abstract with gtk_column_view_new(model). You then
add the columns (GtkColumnViewColumn) with gtk_column_view_append_column.
Each column is created with gtk_column_view_column_new, and has its own setup,
bind, etc.
It seems like the data for the columns are packed in your model that you have to manually unpack with the binds. 

Model is a fancy list. create glistmodel via gliststore?
my own structs via G_TYPE_POINTER, or respect the GObject OOP?
*/



/*
Atomtree UI linked tree-list is an iterable API/abstraction for AtomTree that
makes it easy to expose the tables with a user interface.
*/
typedef struct atui_branch_ atui_branch;
typedef struct atui_leaf_ atui_leaf;
#define STRTYPE(var) _Generic((var), \
	uint8_t:8, uint16_t:16, uint32_t:32, uint64_t:64, default:"other")
#define LEAF(var) {.val=&(X.var), .name=#var, .type=STRTYPE(X.var)},
 
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

	atui_branch* child_branches;
	int branch_count;

	atui_leaf* leaves;
	int leaf_count;

	void* atomleaves;
};

void atui_setval(atui_leaf* leaf, uint64_t val) {
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
uint64_t atui_getval(atui_leaf* leaf) {
//	return *(leaf->u64) & ((1<<leaf->type)-1);
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
	char base = 0;
	if ((str[0] == '0') && (str[1] == 'b'))
		base = 2;
	return (uint64_t)strtol(str+base, NULL, base);
}




struct atom_test { // pretend this is from like atomfirmware.h
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


struct atom_test atest = { //pretend vals from bios
	.antiem = 1, \
	.otheritem = 3, \
	.smolthing = 5, \
	.twobytes = 7,	\
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
#define X atest
atui_leaf atomtest_leaves[] = {
	LEAF(antiem)
	LEAF(otheritem)
	LEAF(smolthing)
	LEAF(twobytes)
	LEAF(twobytes1)	
	LEAF(twobytes2)	
	LEAF(twobytes3)	
	LEAF(twobytes4)	
	LEAF(twobytes5)	
	LEAF(twobytes6)	
	LEAF(twobytes7)	
	LEAF(twobytes8)	
	LEAF(twobytes9)	
	LEAF(twobytes10)	
};
#undef X
atui_branch atomtest_branch = {
	.leaves = atomtest_leaves, \
	.leaf_count = sizeof(atomtest_leaves)/sizeof(atui_leaf), \
	.branch_count = 0, \
};

/*
#define LEAF(var) {.val=&(bios.var), .name=#var, .type=STRTYPE(bios.var)},
#define ATUI_FUNKIFY(name, ...) 
so
ATUI_FUNCIFY( atomtest,
	antiem,
	otheritem,
	smolthing,
	twobytes,
	twobytes1,
	twobytes2,
	twobytes3,
	twobytes4,
	twobytes5,
	twobytes6,
	twobytes7
	twobytes8,
	twobytes9,
	twobytes10,
)

// maybe
ATUI_FUNCIFY(atomtest,
	LEAVES(
		...
	),
	BRANCHES(
		...
	)
)

// make this recursive?
// figure out how to attach the input atomtree to the func
// and somehow attach an extra if it needs version decision-making

#define FUNCIFY_LEAVES antiem, otheritem, smolthing, twobytes,
#define FBRANCHES subbranch1, subbr2, branch, fourthbranch
#
ATUI_FUNCIFY(atomtest)
#undef LEAVES
#undef BRANCHES

creates

static atui_branch* _atomtest_atui(struct atomtest* bios) {
	atui_branch* table = malloc(sizeof(atui_branch) + N*sizeof(atui_leaves));
	atui_leaves* leaves = table + sizeof(atui_branch);
	*table = {
		.name = "atomtest", \
		.leaves = leaves, \
		.leaf_count = N, \
		.atomleaves = bios, \
	};

	*leaves = {
		LEAF(antiem)
		LEAF(otheritem)
		LEAF(smolthing)
		LEAF(twobytes)
		...
	};

	return table;
}

where N is a preprocessor calculation
*/

struct atui_gmodel {
	atui_branch* branch;
	GListModel* leaves;
};

/*
how do we deal with mallocs and frees of atui_gmodel?
*/

static GListModel* atui_to_glistmodel(atui_branch* atui_root) {
//https://stackoverflow.com/questions/74838995/gobject-to-hold-a-pointer
// Is GObject boxed type better here?
	atui_branch* branch;
	GObject* gobj_branch;
	GObject* gobj_leaf;
	int branch_i;
	int leaves_i;
	//GListStore* model = g_list_store_new(G_TYPE_POINTER);

	GListStore* leavesmodel = g_list_store_new(G_TYPE_OBJECT);

	branch = atui_root;
	for(leaves_i=0 ; leaves_i < branch->leaf_count ; leaves_i++) {
		gobj_leaf = g_object_new(G_TYPE_OBJECT, NULL);
		g_object_set_data(gobj_leaf, "leaf", &(branch->leaves[leaves_i]));
		g_list_store_append(leavesmodel, gobj_leaf);
	}

	return G_LIST_MODEL(leavesmodel);
}


// GTK recycles the abstract UI entities to have good performance when scaling
// to millions of list entries.
static void key_column_spawner(GtkListItemFactory* factory,
		GtkListItem* list_item) { //setup to spawn a UI skeleton

	gtk_list_item_set_child(list_item, gtk_label_new(NULL));
}
static void key_column_recycler(GtkListItemFactory* factory, 
		GtkListItem* list_item) { //bind data to the UI skeleton

	GtkWidget* label = gtk_list_item_get_child(list_item); // get UI element
	GObject* gobj_leaf = gtk_list_item_get_item(list_item); // get data
	atui_leaf* leaf = g_object_get_data(gobj_leaf, "leaf");
	gtk_label_set_text(GTK_LABEL(label), leaf->name);
}

//https://docs.gtk.org/gtk4/signal.Widget.move-focus.html
// maybe with https://docs.gtk.org/gtk4/signal.SelectionModel.selection-changed.html
static void val_column_textbox_stray(GtkWidget* textbox,
	GtkDirectionType dir, gpointer gpt_leaf) { // unused but should be
	// revert the textbox's text contents back on focus loss
	printf("hi");
	atui_leaf* leaf = gpt_leaf;
	char str_buff[20];
	sprintf(str_buff, "%d", atui_getval(leaf));
	gtk_editable_set_text(GTK_EDITABLE(textbox), str_buff);
}

static void val_column_textbox_changed(GtkEditable* textbox, gpointer gpt_leaf) {
	atui_leaf* leaf = gpt_leaf;
	printf("before: (%d: %d , %d); input: (%s , %d); ",
		leaf->type, atui_getval(leaf), *(leaf->u32), 
		gtk_editable_get_text(textbox), 
		strtol_2(gtk_editable_get_text(textbox)));
	atui_setval(leaf, strtol_2(gtk_editable_get_text(textbox)));
	
	char str_buff[20];
	sprintf(str_buff, "%d", atui_getval(leaf));
	gtk_editable_set_text(textbox, str_buff);
	printf("after: %d (%s; %d)\n",
		atui_getval(leaf), gtk_editable_get_text(textbox), *(leaf->u32));
}
static void val_column_spawner(GtkListItemFactory* factory,
		GtkListItem* list_item) { //setup to spawn a UI skeleton

//	gtk_list_item_set_child(list_item, gtk_label_new(NULL));
	GtkWidget* textbox = gtk_text_new();
	gtk_text_set_input_purpose(GTK_TEXT(textbox), GTK_INPUT_PURPOSE_DIGITS);
	gtk_list_item_set_child(list_item, textbox);
}
static void val_column_recycler(GtkListItemFactory* factory, 
		GtkListItem* list_item) { //bind data to the UI skeleton

	GtkWidget* textbox = gtk_list_item_get_child(list_item); // get UI element
	GObject* gobj_leaf = gtk_list_item_get_item(list_item); // get data
	atui_leaf* leaf = g_object_get_data(gobj_leaf, "leaf");

	//move_cursor(GTK_TEXT(textbox), 

	char str_buff[20];
	int n = sprintf(str_buff, "%d", *(leaf->u16));
	GtkEntryBuffer* buffer = gtk_text_get_buffer(GTK_TEXT(textbox));
	gtk_entry_buffer_set_text(buffer, str_buff, n);

	g_signal_connect(textbox,"activate",
		G_CALLBACK(val_column_textbox_changed), leaf);
	g_signal_connect(textbox,"move-focus",
		G_CALLBACK(val_column_textbox_stray), leaf);

//	gtk_label_set_text(GTK_LABEL(label), "leaf->val");
}



static void app_activate(GtkApplication* gtkapp, gpointer data) {

	GtkWidget* window = gtk_application_window_new(gtkapp);
	gtk_window_set_title(GTK_WINDOW(window), "YAABE BIOS Editor");
	gtk_window_set_default_size(GTK_WINDOW(window), 200,200);
	GtkWidget* swindow = gtk_scrolled_window_new();
	gtk_window_set_child(GTK_WINDOW(window), swindow);
	gtk_scrolled_window_set_max_content_height(
		GTK_SCROLLED_WINDOW(swindow), 200);


	// create model and spawn columview abstract.
	GListModel* model = atui_to_glistmodel(&atomtest_branch);
	GtkNoSelection* select = gtk_no_selection_new(model);
	GtkWidget* columnlist = gtk_column_view_new(GTK_SELECTION_MODEL(select));
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(swindow), columnlist);


	// create the columns and attach them
	GtkListItemFactory* list_factory;
	GtkColumnViewColumn* column;

	list_factory = gtk_signal_list_item_factory_new();
	g_signal_connect(list_factory,"setup",G_CALLBACK(key_column_spawner),NULL);
	g_signal_connect(list_factory,"bind",G_CALLBACK(key_column_recycler),NULL);
	column = gtk_column_view_column_new("letters",list_factory);
	gtk_column_view_append_column(GTK_COLUMN_VIEW(columnlist), column);

	list_factory = gtk_signal_list_item_factory_new();
	g_signal_connect(list_factory,"setup",G_CALLBACK(val_column_spawner),NULL);
	g_signal_connect(list_factory,"bind",G_CALLBACK(val_column_recycler),NULL);
	column = gtk_column_view_column_new("numbers",list_factory);
	gtk_column_view_append_column(GTK_COLUMN_VIEW(columnlist), column);

	gtk_widget_show(window);
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
