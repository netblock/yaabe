#include "atomtree.h"
#include "atui.h"
#include "yaabe_gtk4.h"

static const char8_t yaabe_name[] = "YAABE BIOS Editor";
typedef struct yaabegtk_commons {
	struct atom_tree* atomtree_root;
	GtkApplication* yaabe_gtk;

	GtkColumnView* leaves_view; // so branches can set leaves
	GtkListView* branches_view; // so we can set the bios during GTK

	// for gtk_widget_set_sensitive() -- don't allow when no bios is loaded
	GtkWidget* save_buttons;
	GtkWidget* reload_button;

} yaabegtk_commons;

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
// free and unref all the atui branches/leaves and the GTK-relevant stuff
// hanging off of the ->auxiliary.
// See also destroy_atomtree_with_gtk

	uint16_t i = 0;
	uint16_t j = 0;
	uint16_t child_gobj_count;
	struct yaabe_gtkapp_model_cache* submodels;

	// the leaves gobjects should be sunk into the model, and auxiliary points
	// to the model.
	if (tree->auxiliary != NULL) {
		submodels = tree->auxiliary;

		if(submodels->leaves_model != NULL)
			g_object_unref(submodels->leaves_model);

		child_gobj_count = submodels->child_gobj_count;
		for (i=0; i < child_gobj_count; i++)
			g_object_unref(submodels->child_gobj[i]);

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
void destroy_atomtree_with_gtk(struct atom_tree* atree, bool free_bios) {
// free and unref
	if (atree) {
		atui_destroy_tree_with_gtk(atree->atui_root);

		if (free_bios) {
			free(atree->alloced_bios);

			if (atree->biosfile)
				g_object_unref(atree->biosfile);
		}

		free(atree);
	}
}






static void leaves_label_column_spawner(
		GtkListItemFactory* factory, GtkListItem* list_item) {
//setup to spawn a UI skeleton

	GtkWidget* expander = gtk_tree_expander_new();
	gtk_tree_expander_set_indent_for_icon(GTK_TREE_EXPANDER(expander), true);

	GtkWidget* label = gtk_label_new(NULL);
	gtk_tree_expander_set_child(GTK_TREE_EXPANDER(expander), label);

	gtk_list_item_set_child(list_item, expander);
}
static void leaves_name_column_recycler(
		GtkListItemFactory* factory, GtkListItem* list_item) {
//bind data to the UI skeleton

	GtkTreeExpander* expander = GTK_TREE_EXPANDER(
		gtk_list_item_get_child(list_item)
	);
	GtkWidget* label = gtk_tree_expander_get_child(expander);

	GtkTreeListRow* tree_list_item = gtk_list_item_get_item(list_item);
	GObject* gobj_leaf = gtk_tree_list_row_get_item(tree_list_item);
	atui_leaf* leaf = g_object_get_data(gobj_leaf, "leaf");
	g_object_unref(gobj_leaf);
	gtk_label_set_text(GTK_LABEL(label), leaf->name);

	gtk_tree_expander_set_list_row(expander, tree_list_item);
}
static void leaves_offset_column_recycler(
		GtkListItemFactory* factory, GtkListItem* list_item,
		gpointer commonsptr) {
//bind data to the UI skeleton

	yaabegtk_commons* commons = commonsptr;

	GtkTreeExpander* expander = GTK_TREE_EXPANDER(
		gtk_list_item_get_child(list_item)
	);
	GtkWidget* label = gtk_tree_expander_get_child(expander);

	GtkTreeListRow* tree_list_item = gtk_list_item_get_item(list_item);
	GObject* gobj_leaf = gtk_tree_list_row_get_item(tree_list_item);
	atui_leaf* leaf = g_object_get_data(gobj_leaf, "leaf");
	g_object_unref(gobj_leaf);

	char8_t buffer[18];
	if (leaf->type & (ATUI_ANY | ATUI_STRING|ATUI_ARRAY|ATUI_BITFIELD)) {
		if (leaf->type & ATUI_BITCHILD) {
			sprintf(buffer, "[%u:%u]",
				leaf->bitfield_hi, leaf->bitfield_lo
			);
		} else {
			uint32_t start = leaf->val - commons->atomtree_root->bios;
			uint32_t end = (
				start
				+ ((leaf->total_bits/8) * (leaf->array_size))
				- 1
			);
			sprintf(buffer, "[%05X - %05X]", start, end);
		}
	} else {
		buffer[0] = '\0';
	}
	gtk_label_set_text(GTK_LABEL(label), buffer);
}

static void leaves_textbox_stray(
		GtkEventControllerFocus* focus_sense, gpointer leaf_gptr) {
//if the value wasn't applied with enter, sync the text back to the actual data
//when keyboard leaves the textbox
	GtkWidget* textbox = gtk_event_controller_get_widget(
		GTK_EVENT_CONTROLLER(focus_sense)
	);
	atui_leaf* leaf = leaf_gptr;

	char8_t stack_buff[ATUI_LEAVES_STR_BUFFER];
	stack_buff[0] = '\0';
	char8_t* buff = stack_buff;
	uint16_t has_mallocd = atui_get_to_text(leaf, &buff);
	gtk_editable_set_text(GTK_EDITABLE(textbox), buff);
	if (has_mallocd)
		free(buff);
}
static void leaves_val_column_textbox_apply(
		GtkEditable* textbox, gpointer leaf_gptr) {
// only way to apply the value is to hit enter

	atui_leaf* leaf = leaf_gptr;

	atui_set_from_text(leaf, gtk_editable_get_text(textbox));

	char8_t stack_buff[ATUI_LEAVES_STR_BUFFER];
	stack_buff[0] = '\0';
	char8_t* buff = stack_buff;
	uint16_t has_mallocd = atui_get_to_text(leaf, &buff);
	gtk_editable_set_text(textbox, buff);
	if (has_mallocd)
		free(buff);
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

	char8_t stack_buff[ATUI_LEAVES_STR_BUFFER];
	stack_buff[0] = '\0';
	char8_t* buff = stack_buff;
	uint16_t has_mallocd = atui_get_to_text(leaf, &buff);
	gtk_editable_set_text(GTK_EDITABLE(textbox), buff);
	if (has_mallocd)
		free(buff);

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

		if ( 0 == (leaf->type & ATUI_NODISPLAY) ) {
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
inline static GListModel* atui_leaves_to_glistmodel(
		atui_leaf* children, uint16_t num_children) {
// creates a rudimentary model from an array of atui_leaf's

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
// creates the children models for the collapsable tree, of the leaves pane.

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

			uint16_t child_gobj_count = g_list_model_get_n_items(
				children_model
			);
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
// turns the 'level 0' leaves of a branch into a model for the leaves pane.
// Also generates its cache.

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
static void set_leaves_list(
		GtkSelectionModel* model, guint position, guint n_items,
		gpointer commonsptr) {
// signal callback.
// change the leaves pane's model based on the what is selected in brances

	yaabegtk_commons* commons = commonsptr;

	GtkTreeListRow* tree_list_item = gtk_single_selection_get_selected_item(
		GTK_SINGLE_SELECTION(model)
	);
	GObject* gobj_branch = gtk_tree_list_row_get_item(tree_list_item);
	atui_branch* branch = g_object_get_data(gobj_branch, "branch");
	g_object_unref(gobj_branch);

	struct yaabe_gtkapp_model_cache* branch_models = branch->auxiliary;
	if(branch_models->leaves_model == NULL) // if not cached, generate.
		branchleaves_to_treemodel(branch);

	gtk_column_view_set_model(commons->leaves_view,
		branch_models->leaves_model
	);
}

inline static GtkWidget* create_leaves_pane(yaabegtk_commons* commons) {

	// columnview abstract
	GtkWidget* leaves_list = gtk_column_view_new(NULL);
	commons->leaves_view = GTK_COLUMN_VIEW(leaves_list);


	// create and attach columns
	GtkListItemFactory* factory;
	GtkColumnViewColumn* column;


	factory = gtk_signal_list_item_factory_new();
	g_signal_connect(factory,
		"setup", G_CALLBACK(leaves_label_column_spawner), NULL
	);
	g_signal_connect(factory,
		"bind", G_CALLBACK(leaves_name_column_recycler), NULL
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


	factory = gtk_signal_list_item_factory_new();
	g_signal_connect(factory,
		"setup", G_CALLBACK(leaves_label_column_spawner), NULL
	);
	g_signal_connect(factory,
		"bind", G_CALLBACK(leaves_offset_column_recycler), commons
	);
	column = gtk_column_view_column_new("BIOS offset", factory);
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





static GListModel* branch_tlmodel_func(gpointer ptr, gpointer data) {
// GtkTreeListModelCreateModelFunc for branches
// creates the children models for the collapsable tree, of the branches pane.

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
			for(i=0; i < branch_models->child_gobj_count; i++)
				g_list_store_append(children, branch_models->child_gobj[i]);
		}
	}
	return G_LIST_MODEL(children);
}
inline static GtkSelectionModel* atui_gtk_model(yaabegtk_commons* commons) {
// generate the very first model, of the tippy top of the tree, for the
// branches pane

	atui_branch* atui_root = commons->atomtree_root->atui_root;
	alloc_branch_cache(atui_root);

	GObject* gbranch = g_object_new(G_TYPE_OBJECT, NULL);
	g_object_set_data(gbranch, "branch", atui_root);
	GListStore* ls_model = g_list_store_new(G_TYPE_OBJECT);
	g_list_store_append(ls_model, gbranch);
	g_object_unref(gbranch);

	//TreeList, along with branch_tlmodel_func, creates our collapsable model.
	GtkTreeListModel* tlist_atui = gtk_tree_list_model_new(
		G_LIST_MODEL(ls_model), false, true, branch_tlmodel_func, NULL,NULL
	);

	GtkSingleSelection* sel_model = gtk_single_selection_new(
		G_LIST_MODEL(tlist_atui)
	);
	gtk_single_selection_set_autoselect(sel_model, false);
	gtk_single_selection_set_can_unselect(sel_model, true);
	gtk_selection_model_unselect_item(GTK_SELECTION_MODEL(sel_model), 0);

	// change the leaves pane's model based on the what is selected in brances
	g_signal_connect(sel_model,
		"selection-changed", G_CALLBACK(set_leaves_list), commons
	);

	return GTK_SELECTION_MODEL(sel_model);
	// does not need to be unref'd if used with a new().
	// Needs to be unref'd if used with a set().
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
		gtk_list_item_get_child(list_item)
	);
	GtkWidget* row_label = gtk_tree_expander_get_child(expander);

	GtkTreeListRow* tree_list_item = gtk_list_item_get_item(list_item);
	GObject* gobj_branch = gtk_tree_list_row_get_item(tree_list_item);
	atui_branch* branch = g_object_get_data(gobj_branch, "branch");
	g_object_unref(gobj_branch);

	gtk_label_set_text(GTK_LABEL(row_label), branch->name);

	gtk_tree_expander_set_list_row(expander, tree_list_item);
}
inline static GtkWidget* create_branches_pane(
		yaabegtk_commons* commons, GtkSelectionModel* atui_model) {

	GtkListItemFactory* branch_list_factory =
		gtk_signal_list_item_factory_new();
	g_signal_connect(branch_list_factory,
		"setup", G_CALLBACK(branch_listitem_spawner), NULL
	);
	g_signal_connect(branch_list_factory,
		"bind", G_CALLBACK(branch_listitem_recycler), NULL
	);
	GtkWidget* listview = gtk_list_view_new(
		atui_model, branch_list_factory
	);

	commons->branches_view = GTK_LIST_VIEW(listview);

	GtkWidget* scrolledlist = gtk_scrolled_window_new();
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolledlist), listview);
	GtkWidget* frame = gtk_frame_new(NULL);
	gtk_frame_set_child(GTK_FRAME(frame), scrolledlist);

	return frame;
}





struct atom_tree* atomtree_from_gfile(GFile* biosfile, GError** ferror_out) {
// geneate the atom_tree and atui from a GIO File

	GError* ferror = NULL;
	struct atom_tree* atree = NULL;
	void* bios = NULL;

	GFileInputStream* readstream = g_file_read(biosfile, NULL, &ferror);
	if (ferror)
		goto exit1;

	GFileInfo* fi_size = g_file_query_info(biosfile,
		G_FILE_ATTRIBUTE_STANDARD_SIZE, G_FILE_QUERY_INFO_NONE, NULL, &ferror
	);
	if (ferror)
		goto exit2;

	int64_t filesize = g_file_info_get_size(fi_size);
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

	atree = atombios_parse(bios, filesize, true);
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
void atomtree_save_to_gfile(struct atom_tree* atree, GError** ferror_out) {

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
	if (ferror)
		goto ferr0;

	GIOStream* biosstream = G_IO_STREAM(biosfilestream);
	GOutputStream* writestream = g_io_stream_get_output_stream(biosstream);

	g_output_stream_write_all(
		writestream,  atree->alloced_bios,
		atree->biosfile_size,  NULL,NULL,  &ferror
	);
	if (ferror)
		goto ferr1;

	g_output_stream_close(writestream, NULL, &ferror);
	if (ferror)
		goto ferr1;
	g_io_stream_close(biosstream, NULL, &ferror);
	if (ferror)
		goto ferr1;


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

static void set_editor_titlebar(yaabegtk_commons* commons) {
// set the window name to the name of the currently-open bios.

	const char8_t print_format_file[] = "%s (%s)";
	const char8_t print_format_nofile[] = "%s";

	char8_t* filename;
	uint16_t filename_length;
	const char8_t* formatstr;
	if (commons->atomtree_root) {
		filename = g_file_get_basename(commons->atomtree_root->biosfile);
		filename_length = strlen(filename);
		formatstr = print_format_file;
	} else {
		filename = NULL;
		filename_length = 0;
		formatstr = print_format_nofile;
	}

	char8_t* window_title = malloc(
		sizeof(yaabe_name)
		+ filename_length
		+ sizeof(print_format_file) // largest
	);
	sprintf(window_title, formatstr, yaabe_name, filename);

	GtkWindow* editor_window = gtk_application_get_active_window(
		commons->yaabe_gtk
	);
	gtk_window_set_title(editor_window, window_title);

	free(window_title);
	if (filename_length)
		g_free(filename);
}
inline static void filer_error_window(GError* ferror, const char8_t* title) {
// simple error popup

	GtkEventController* escapeclose = gtk_shortcut_controller_new();
	gtk_shortcut_controller_add_shortcut(
		GTK_SHORTCUT_CONTROLLER(escapeclose),
		gtk_shortcut_new(
			gtk_shortcut_trigger_parse_string("Escape"),
			gtk_named_action_new("window.close")
		)
	);

	GtkWindow* notify_window = GTK_WINDOW(gtk_window_new());

	gtk_widget_add_controller(GTK_WIDGET(notify_window), escapeclose);
	gtk_window_set_title(notify_window, title);
	gtk_window_set_default_size(notify_window, 100,100);
	gtk_window_set_child(notify_window,
		gtk_label_new(ferror->message)
	);

	gtk_window_present(notify_window);
}
inline static void yaabegtk_load_bios(
		yaabegtk_commons* commons, GFile* biosfile, GError** ferror_out) {
// processes necessary triggers for loading a bios, except final error handling

	GError* ferror = NULL;

	struct atom_tree* atree = atomtree_from_gfile(biosfile, &ferror);
	if (ferror)
		goto ferr;

	if (atree) {
		struct atom_tree* oldtree = commons->atomtree_root;

		commons->atomtree_root = atree;
		GtkSelectionModel* newmodel = atui_gtk_model(commons);
		gtk_list_view_set_model(commons->branches_view, newmodel);
		gtk_selection_model_select_item(newmodel, 0, true);

		destroy_atomtree_with_gtk(oldtree, true);
		g_object_unref(newmodel);

		if  (gtk_widget_get_sensitive(commons->save_buttons) == false) {
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


static void filedialog_load_and_set_bios(
		GObject* gobj_filedialog, GAsyncResult* asyncfile,
		gpointer commonsptr) {
// AsyncReadyCallback for the file dialog in the load button.

	yaabegtk_commons* commons = commonsptr;
	GtkFileDialog* filer = GTK_FILE_DIALOG(gobj_filedialog);
	GError* ferror = NULL;

	GFile* biosfile = gtk_file_dialog_open_finish(filer, asyncfile, &ferror);
	if (ferror)
		goto ferr_nomsg;

	yaabegtk_load_bios(commons, biosfile, &ferror);
	g_object_unref(biosfile);
	if (ferror)
		goto ferr_msg;
	return;

	ferr_msg:
	filer_error_window(ferror, "YAABE Load BIOS");
	ferr_nomsg:
	g_error_free(ferror);
	return;

}
static void load_button_open_bios(GtkWidget* button, gpointer commonsptr) {
// signal callback

	yaabegtk_commons* commons = commonsptr;

	GtkFileDialog* filer = gtk_file_dialog_new();
	GtkWindow* active_window = gtk_application_get_active_window(
		commons->yaabe_gtk
	);

	GFile* working_dir;
	if (commons->atomtree_root) {
		working_dir = g_file_get_parent(commons->atomtree_root->biosfile);
	}else {
		working_dir = g_file_new_for_path(".");
	}
	//TODO https://gitlab.gnome.org/GNOME/xdg-desktop-portal-gnome/-/issues/84
	gtk_file_dialog_set_initial_folder(filer, working_dir);
	g_object_unref(working_dir);

	gtk_file_dialog_open(filer,
		active_window, NULL, filedialog_load_and_set_bios, commons
	);
	g_object_unref(filer);
}


static void reload_button_reload_bios(GtkWidget* button, gpointer commonsptr) {
// signal callback

	yaabegtk_commons* commons = commonsptr;
	struct atom_tree* old_tree = commons->atomtree_root;

	struct atom_tree* new_tree = atombios_parse(
		old_tree->alloced_bios, old_tree->biosfile_size, true
	);
	new_tree->biosfile = old_tree->biosfile;
	new_tree->biosfile_size = old_tree->biosfile_size;
	commons->atomtree_root = new_tree;

	GtkSelectionModel* newmodel = atui_gtk_model(commons);
	gtk_list_view_set_model(commons->branches_view, newmodel);
	gtk_selection_model_select_item(newmodel, 0, true);

	g_object_unref(newmodel);
	destroy_atomtree_with_gtk(old_tree, false);
}



static void save_button_same_file(GtkWidget* button, gpointer commonsptr) {
// signal callback

	yaabegtk_commons* commons = commonsptr;
	GError* ferror = NULL;

	atomtree_save_to_gfile(commons->atomtree_root, &ferror);
	if (ferror)
		goto ferr;

	return;

	ferr:
	filer_error_window(ferror, "YAABE Save BIOS");
	g_error_free(ferror);
	return;
}

static void filedialog_saveas_bios(
		GObject* gobj_filedialog, GAsyncResult* asyncfile,
		gpointer commonsptr) {
// AsyncReadyCallback for the file dialog in the Save As button.

	yaabegtk_commons* commons = commonsptr;
	GtkFileDialog* filer = GTK_FILE_DIALOG(gobj_filedialog);
	GError* ferror = NULL;

	GFile* new_biosfile = gtk_file_dialog_save_finish(
		filer, asyncfile, &ferror
	);
	if (ferror)
		goto ferr_nomsg;


	GFile* old_biosfile = commons->atomtree_root->biosfile;
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
	filer_error_window(ferror, "YAABE Save BIOS As");
	ferr_nomsg:
	g_error_free(ferror);
	return;
}
static void saveas_button_name_bios(GtkWidget* button, gpointer commonsptr) {
// signal callback

	yaabegtk_commons* commons = commonsptr;

	GtkFileDialog* filer = gtk_file_dialog_new();
	GtkWindow* active_window = gtk_application_get_active_window(
		commons->yaabe_gtk
	);
	GFile* working_dir = g_file_get_parent(commons->atomtree_root->biosfile);
	gtk_file_dialog_set_initial_folder(filer, working_dir);
	g_object_unref(working_dir);

	gtk_file_dialog_save(filer,
		active_window, NULL, filedialog_saveas_bios, commons
	);
	g_object_unref(filer);
}

inline static GtkWidget* buttons_box(yaabegtk_commons* commons) {

	GtkWidget* load_button = gtk_button_new_with_label("Load");
	g_signal_connect(load_button,
		"clicked", G_CALLBACK(load_button_open_bios), commons
	);
	GtkWidget* reload_button = gtk_button_new_with_label("Reload");
	g_signal_connect(reload_button,
		"clicked", G_CALLBACK(reload_button_reload_bios), commons
	);
	GtkWidget* load_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_append(GTK_BOX(load_buttons),
		gtk_separator_new(GTK_ORIENTATION_HORIZONTAL)
	);
	gtk_box_append(GTK_BOX(load_buttons), load_button);
	gtk_box_append(GTK_BOX(load_buttons), reload_button);


	GtkWidget* save_button = gtk_button_new_with_label("Save");
	g_signal_connect(save_button,
		"clicked", G_CALLBACK(save_button_same_file), commons
	);
	GtkWidget* saveas_button = gtk_button_new_with_label("Save As");
	g_signal_connect(saveas_button,
		"clicked", G_CALLBACK(saveas_button_name_bios), commons
	);
	GtkWidget* save_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_append(GTK_BOX(save_buttons), save_button);
	gtk_box_append(GTK_BOX(save_buttons), saveas_button);


	GtkWidget* cf_button = gtk_button_new_with_label("Function Tables");
	gtk_widget_set_sensitive(cf_button, false);

	GtkWidget* buttonboxes = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 30);
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



static gboolean dropped_file_open_bios(
		GtkDropTarget* dropctrl, const GValue* value,  gdouble x,gdouble y,
		gpointer commonsptr) {
// load a bios from a drag-n'-drop
// ???  https://gitlab.gnome.org/GNOME/gtk/-/issues/3755

	yaabegtk_commons* commons = commonsptr;
	GError* ferror = NULL;

	if (G_VALUE_HOLDS(value, G_TYPE_FILE)) {
		GFile* biosfile = g_value_get_object(value);
		yaabegtk_load_bios(commonsptr, biosfile, &ferror);
		if (ferror) {
			filer_error_window(ferror, "YAABE Load dropped BIOS");
			g_error_free(ferror);
			return false;
		}
		return true;
	}
	return false;

}

static void app_activate(GtkApplication* gtkapp, gpointer commonsptr) {
/* TODO
if there is no file set during bootup the branches-leaves panes need to be
hidden; when a file is set unhide it.
*/

	yaabegtk_commons* commons = commonsptr;

	GtkSelectionModel* atui_model = NULL;
	 if (commons->atomtree_root)
		atui_model = atui_gtk_model(commons);

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

	if (commons->atomtree_root) {
		gtk_selection_model_select_item(atui_model, 0, true);
	} else {
		//gtk_widget_set_visible(tree_divider, false);
	}

	// TODO https://docs.gtk.org/gtk4/class.BoxLayout.html
	GtkWidget* button_pane_complex = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	GtkWidget* buttonboxes = buttons_box(commons);
	gtk_widget_set_vexpand(tree_divider, true);
	gtk_box_append(GTK_BOX(button_pane_complex), tree_divider);
	gtk_box_append(GTK_BOX(button_pane_complex), buttonboxes);
	gtk_box_append(GTK_BOX(button_pane_complex),
		gtk_separator_new(GTK_ORIENTATION_HORIZONTAL)
	);


	GtkDropTarget* dropfile = gtk_drop_target_new(G_TYPE_FILE, GDK_ACTION_COPY);
	g_signal_connect(dropfile,
		"drop", G_CALLBACK(dropped_file_open_bios), commons
	);

	GtkWindow* window = GTK_WINDOW(gtk_application_window_new(gtkapp));
	gtk_widget_add_controller(
		GTK_WIDGET(window), GTK_EVENT_CONTROLLER(dropfile)
	);

	set_editor_titlebar(commons);
	gtk_window_set_default_size(window, 800,500);
	gtk_window_set_child(window, button_pane_complex);
	gtk_window_present(window);

}

int8_t yaabe_gtk(struct atom_tree** atree) {
	/* TODO  https://docs.gtk.org/gtk4/visual_index.html

	path bar
	changelog of what was changed before the save? feels hard to impement
	menubar? of what?
		https://github.com/luigifab/awf-extended/blob/levelup/src/awf.c#L692
		file save/load ; about ; light-dark
	extra columns like bit count, description.
		User selectable. Reorderable
	*/

	// TODO better malloc'd?
	//yaabegtk_commons* commons = calloc(1, sizeof(yaabegtk_commons)); // 0'd
	yaabegtk_commons commons;
	commons.atomtree_root = *atree;

	commons.yaabe_gtk = gtk_application_new(NULL, G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(commons.yaabe_gtk,
		"activate", G_CALLBACK(app_activate), &commons
	);
	int16_t status = g_application_run(
		G_APPLICATION(commons.yaabe_gtk), 0,NULL
	);

	*atree = commons.atomtree_root;
	g_object_unref(commons.yaabe_gtk);
	//free(commons);

	return status;
}
