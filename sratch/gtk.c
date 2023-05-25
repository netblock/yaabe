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

static void print_hello(GtkWidget* widget, gpointer data){
	g_print("hi\n");
}


// GTK recycles the abstract UI entities to have good performance when scaling
// to millions of list entries.
static void listitem_spawner(GtkListItemFactory* factory, //setup to spawn a UI skeleton
		GtkListItem* list_item) {

	GtkWidget* label = gtk_label_new(NULL);

	GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 12);
	gtk_box_append(GTK_BOX(box), label);
	gtk_list_item_set_child(list_item, box);
//	gtk_list_item_set_child(list_item, label);
}
static void listitem_recycler(GtkListItemFactory* factory, //bind data to the UI skeleton
		GtkListItem* list_item) {

	GtkWidget* box = gtk_list_item_get_child(list_item);
	GtkWidget* label = gtk_widget_get_first_child(box);
	//GtkWidget* label = gtk_list_item_get_child(list_item);
	GtkStringObject* strobj = gtk_list_item_get_item(list_item);
	gtk_label_set_text(GTK_LABEL(label), gtk_string_object_get_string(strobj));
}



static void app_activate(GtkApplication* gtkapp, gpointer data) {

	GtkWidget* window = gtk_application_window_new(gtkapp);
	gtk_window_set_title(GTK_WINDOW(window), "YAABE BIOS Editor");
	gtk_window_set_default_size(GTK_WINDOW(window), 200,200);
	GtkWidget* swindow = gtk_scrolled_window_new();
	gtk_window_set_child(GTK_WINDOW(window), swindow);
	gtk_scrolled_window_set_max_content_height(GTK_SCROLLED_WINDOW(swindow), 200);


	const char* strings[] = {"a", "bb", "ccc", "dddd", "eeeee", "ffffff", "ggggggg", "hhhhhhhh",
		"iiiiiiiii", "jjjjjjjjjj", "kkkkkkkkkkk","need", "more", "rows", "to", "cause", "scroll",
		"bar", NULL};
	GtkStringList* sl = gtk_string_list_new(strings);
	GtkSingleSelection* single_select = gtk_single_selection_new(G_LIST_MODEL(sl));


	GtkListItemFactory* list_factory = gtk_signal_list_item_factory_new();
	g_signal_connect(list_factory, "setup", G_CALLBACK(listitem_spawner), NULL);
	g_signal_connect(list_factory, "bind", G_CALLBACK(listitem_recycler), NULL);

	GtkWidget* list = gtk_list_view_new(GTK_SELECTION_MODEL(single_select), list_factory);
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(swindow), list);

/*
	GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 12);
	GtkWidget* label = gtk_label_new("aaaaa");
    gtk_box_append(GTK_BOX(box), label);
 	GtkTextBuffer* buffer = gtk_text_buffer_new(NULL);
	GtkWidget* textbox = gtk_text_view_new_with_buffer(buffer);
    gtk_box_append(GTK_BOX(box), textbox);
	gtk_window_set_child (GTK_WINDOW (window), box);
*/

	//and showtime
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
