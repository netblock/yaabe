#include "atomtree.h"
#include "atui.h"
#include "yaabe_gtk4.h"

static const char8_t yaabe_name[] = "YAABE BIOS Editor";
typedef struct yaabegtk_commons {
	struct atom_tree* atomtree_root;
	GtkApplication* yaabe_gtk;

	GtkColumnView* leaves_view; // So branches can set leaves
	GtkColumnView* branches_view; // So we can set the bios during GTK

	// For gtk_widget_set_sensitive() -- don't allow when no bios is loaded
	GtkWidget* save_buttons;
	GtkWidget* reload_button;

} yaabegtk_commons;

static void
_atui_destroy_leaves_with_gtk(
		atui_leaf* const leaves,
		const uint8_t num_leaves
		) {
	for (uint16_t i=0; i < num_leaves; i++) {
		if (leaves[i].child_gobj_cache) {
			for (uint16_t g=0; g < leaves[i].num_gobj; g++) {
				g_object_unref(leaves[i].child_gobj_cache[g]);
			}
			free(leaves[i].child_gobj_cache);
		}
		if (leaves[i].num_child_leaves) {
			_atui_destroy_leaves_with_gtk(
				leaves[i].child_leaves, leaves[i].num_child_leaves
			);
			free(leaves[i].child_leaves);
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
		const bool free_bios
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
generic_label_column_spawner(
		const GtkListItemFactory* const factory,
		GtkListItem* const list_item
		) {
//TODO use https://docs.gtk.org/gtk4/class.Inscription.html
	GtkWidget* const label = gtk_label_new(NULL);
	gtk_label_set_xalign(GTK_LABEL(label), 0);
	gtk_list_item_set_child(list_item, label);
}
static void
leaves_label_column_spawner(
		const GtkListItemFactory* const factory,
		GtkListItem* const list_item
		) {
// setup to spawn a UI skeleton

	GtkWidget* const expander = gtk_tree_expander_new();
	gtk_tree_expander_set_indent_for_icon(GTK_TREE_EXPANDER(expander), true);

	GtkWidget* const label = gtk_label_new(NULL);
	gtk_label_set_xalign(GTK_LABEL(label), 0);
	gtk_tree_expander_set_child(GTK_TREE_EXPANDER(expander), label);

	gtk_list_item_set_child(list_item, expander);
}
static void
leaves_name_column_recycler(
		const GtkListItemFactory* const factory,
		GtkListItem* const list_item) {
// bind data to the UI skeleton

	GtkTreeExpander* const expander = GTK_TREE_EXPANDER(
		gtk_list_item_get_child(list_item)
	);
	GtkWidget* const label = gtk_tree_expander_get_child(expander);

	GtkTreeListRow* const tree_list_item = gtk_list_item_get_item(list_item);
	GObject* const gobj_leaf = gtk_tree_list_row_get_item(tree_list_item);
	atui_leaf* const leaf = g_object_get_data(gobj_leaf, "leaf");
	g_object_unref(gobj_leaf);
	gtk_label_set_text(GTK_LABEL(label), leaf->name);

	gtk_tree_expander_set_list_row(expander, tree_list_item);
}

static void
leaves_offset_column_recycler(
		const GtkListItemFactory* const factory,
		GtkListItem* const list_item,
		gpointer const commonsptr
		) {
// bind data to the UI skeleton

	yaabegtk_commons* const commons = commonsptr;
	GtkWidget* const label = gtk_list_item_get_child(list_item);

	GtkTreeListRow* const tree_list_item = gtk_list_item_get_item(list_item);
	GObject* const gobj_leaf = gtk_tree_list_row_get_item(tree_list_item);
	atui_leaf* const leaf = g_object_get_data(gobj_leaf, "leaf");
	g_object_unref(gobj_leaf);

	char8_t buffer[18];
	if (leaf->type & _ATUI_BITCHILD) {
		sprintf(buffer, "[%u:%u]",
			leaf->bitfield_hi, leaf->bitfield_lo
		);
	} else if (leaf->num_bytes) {
		const uint32_t start = leaf->val - commons->atomtree_root->bios;
		const uint32_t end = (start + leaf->num_bytes -1);
		sprintf(buffer, "[%05X - %05X]", start, end);
	} else {
		buffer[0] = '\0';
	}
	gtk_label_set_text(GTK_LABEL(label), buffer);
}

static void
leaves_textbox_stray(
		const GtkEventControllerFocus* const focus_sense,
		const gpointer const leaf_gptr
		) {
// If the value wasn't applied with enter, sync the text back to the actual
// data when keyboard leaves the textbox
	GtkWidget* const textbox = gtk_event_controller_get_widget(
		GTK_EVENT_CONTROLLER(focus_sense)
	);
	const atui_leaf* const leaf = leaf_gptr;

	char8_t stack_buff[ATUI_LEAVES_STR_BUFFER];
	stack_buff[0] = '\0';
	char8_t* buff = stack_buff;
	const uint16_t has_mallocd = atui_get_to_text(leaf, &buff);
	gtk_editable_set_text(GTK_EDITABLE(textbox), buff);
	if (has_mallocd) {
		free(buff);
	}
}
static void
leaves_val_column_textbox_apply(
		GtkEditable* const textbox,
		gpointer const leaf_gptr
		) {
// Only way to apply the value is to hit enter

	atui_leaf* const leaf = leaf_gptr;

	atui_set_from_text(leaf, gtk_editable_get_text(textbox));

	char8_t stack_buff[ATUI_LEAVES_STR_BUFFER];
	stack_buff[0] = '\0';
	char8_t* buff = stack_buff;
	const uint16_t has_mallocd = atui_get_to_text(leaf, &buff);
	gtk_editable_set_text(textbox, buff);
	if (has_mallocd) {
		free(buff);
	}
}


static void
leaves_val_column_spawner(
		const GtkListItemFactory* const factory,
		GtkListItem* const list_item) {
// setup

	GtkWidget* const textbox = gtk_text_new();
	gtk_text_set_input_purpose(GTK_TEXT(textbox), GTK_INPUT_PURPOSE_DIGITS);

	// for leaves_textbox_stray()
	GtkEventController* const focus_sense = gtk_event_controller_focus_new();
	gtk_widget_add_controller(textbox, focus_sense);
	// widget takes ownership of the controller, no need to unref.

	gtk_list_item_set_child(list_item, textbox);
}
static void
leaves_val_column_recycler(
		const GtkListItemFactory* const factory,
		GtkListItem* const list_item
		) {
// bind

	GtkWidget* const textbox = gtk_list_item_get_child(list_item);

	GtkTreeListRow* const tree_list_item = gtk_list_item_get_item(list_item);
	GObject* const gobj_leaf = gtk_tree_list_row_get_item(tree_list_item);
	atui_leaf* const leaf = g_object_get_data(gobj_leaf, "leaf");
	g_object_unref(gobj_leaf);

	char8_t stack_buff[ATUI_LEAVES_STR_BUFFER];
	stack_buff[0] = '\0';
	char8_t* buff = stack_buff;
	const uint16_t has_mallocd = atui_get_to_text(leaf, &buff);
	gtk_editable_set_text(GTK_EDITABLE(textbox), buff);
	if (has_mallocd) {
		free(buff);
	}

	g_signal_connect(textbox,
		"activate", G_CALLBACK(leaves_val_column_textbox_apply), leaf
	);


	GListModel* const controller_list = gtk_widget_observe_controllers(
		textbox
	);
	GtkEventController* const focus_sense = g_list_model_get_item(
		controller_list, 0
	);
	g_signal_connect(focus_sense,
		"leave", G_CALLBACK(leaves_textbox_stray), leaf
	);
	g_object_unref(controller_list);
	g_object_unref(focus_sense);

}
static void
leaves_val_column_cleaner(
		const GtkListItemFactory* const factory,
		GtkListItem* const list_item
		) {
// unbind
// Signals need to be removed, else they build up

	GtkWidget* const textbox = gtk_list_item_get_child(list_item);

	g_signal_handlers_disconnect_matched(textbox, G_SIGNAL_MATCH_FUNC,
		0,0,NULL,  G_CALLBACK(leaves_val_column_textbox_apply),  NULL
	);

	GListModel* const controller_list = gtk_widget_observe_controllers(textbox);

	GtkEventController* const focus_sense = g_list_model_get_item(
		controller_list, 0
	);
	g_signal_handlers_disconnect_matched(focus_sense, G_SIGNAL_MATCH_FUNC,
		0,0,NULL,  G_CALLBACK(leaves_textbox_stray),  NULL
	);
	g_object_unref(controller_list);
	g_object_unref(focus_sense);
}


static void
atui_leaves_pullin_gliststore(
		atui_leaf* const leaves,
		GListStore* const list,
		const uint16_t num_leaves
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
			g_object_unref(gobj_child);
		}
	}
}
inline static GListModel*
atui_leaves_to_glistmodel(
		atui_leaf* const children,
		const uint16_t num_children
		) {
// Creates a rudimentary model from an array of atui_leaf's
	GListStore* const child_list = g_list_store_new(G_TYPE_OBJECT);
	atui_leaves_pullin_gliststore(children, child_list, num_children);
	return G_LIST_MODEL(child_list);
}

static GListModel*
leaves_tlmodel_func(
		gpointer const parent_ptr,
		const gpointer const d // unused
		) {
// GtkTreeListModelCreateModelFunc for leaves
// Creates the children models for the collapsable tree, of the leaves pane.

	GListModel* children_model = NULL;

	GObject* const gobj_parent = parent_ptr;
	atui_leaf* const parent = g_object_get_data(gobj_parent, "leaf");

	if (parent->type & (ATUI_BITFIELD|ATUI_INLINE|ATUI_DYNARRAY)
			&& (-1 < parent->num_gobj)
			) {
		atui_leaf* leaves;
		uint16_t num_leaves;
		if (NULL == parent->child_gobj_cache) {
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

	GListModel* const leavesmodel = atui_leaves_to_glistmodel(
		branch->leaves, branch->leaf_count
	);

	GtkTreeListModel* const treemodel = gtk_tree_list_model_new(
		leavesmodel, false, true, leaves_tlmodel_func, NULL,NULL
	);
	GtkSelectionModel* const sel_model = GTK_SELECTION_MODEL(
		gtk_no_selection_new(G_LIST_MODEL(treemodel))
	);
	// no_selection takes ownership of treemodel.

	branch->leaves_model = sel_model;
	g_object_ref(sel_model); // to cache
}
static void
set_leaves_list(
		GtkSelectionModel* const model,
		const guint position,
		const guint n_items,
		gpointer const commonsptr
		) {
// Signal callback
// Change the leaves pane's model based on the what is selected in brances
	yaabegtk_commons* const commons = commonsptr;

	GtkTreeListRow* const tree_list_item =
		gtk_single_selection_get_selected_item(GTK_SINGLE_SELECTION(model));
	GObject* const gobj_branch = gtk_tree_list_row_get_item(tree_list_item);
	atui_branch* const branch = g_object_get_data(gobj_branch, "branch");
	g_object_unref(gobj_branch);

	if (NULL == branch->leaves_model) { // if not cached, generate.
		branchleaves_to_treemodel(branch);
	}

	gtk_column_view_set_model(commons->leaves_view,
		branch->leaves_model
	);
}

inline static GtkWidget*
create_leaves_pane(
		yaabegtk_commons* const commons
		) {

	// Columnview abstract
	GtkColumnView* const leaves_list = GTK_COLUMN_VIEW(
		gtk_column_view_new(NULL)
	);
	gtk_column_view_set_reorderable(leaves_list, true);
	gtk_column_view_set_show_row_separators(leaves_list, true);
	commons->leaves_view = leaves_list;

	// Create and attach columns
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
	gtk_column_view_column_set_resizable(column, true);
	gtk_column_view_append_column(leaves_list, column);
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
	gtk_column_view_column_set_resizable(column, true);
	gtk_column_view_column_set_expand(column, true);
	gtk_column_view_append_column(leaves_list, column);
	g_object_unref(column);


	factory = gtk_signal_list_item_factory_new();
	g_signal_connect(factory,
		"setup", G_CALLBACK(generic_label_column_spawner), NULL
	);
	g_signal_connect(factory,
		"bind", G_CALLBACK(leaves_offset_column_recycler), commons
	);
	column = gtk_column_view_column_new("BIOS offset", factory);
	gtk_column_view_column_set_resizable(column, true);
	gtk_column_view_append_column(leaves_list, column);
	g_object_unref(column);


	GtkWidget* const scrolledlist = gtk_scrolled_window_new();
	gtk_scrolled_window_set_child(
		GTK_SCROLLED_WINDOW(scrolledlist), GTK_WIDGET(leaves_list)
	);
	GtkWidget* const frame = gtk_frame_new(NULL);
	gtk_frame_set_child(GTK_FRAME(frame), scrolledlist);

	return frame;
}


static void
atui_branches_pullin_gliststore(
		const atui_branch* const parent,
		GListStore* const list
		) {
	GObject* gobj_child;
	atui_branch* child;
	uint8_t i;
	for (i=0; i < parent->num_inline_branches; i++) {
		atui_branches_pullin_gliststore(parent->inline_branches[i], list);
	}
	for (i=0; i < parent->num_branches; i++) {
		gobj_child = g_object_new(G_TYPE_OBJECT, NULL);
		g_object_set_data(gobj_child, "branch", parent->child_branches[i]);
		g_list_store_append(list, gobj_child);
		g_object_unref(gobj_child);
	}
}
static GListModel*
branch_tlmodel_func(
		gpointer const parent_ptr,
		const gpointer const data
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
atui_gtk_model(
		yaabegtk_commons* const commons
		) {
// Generate the very first model, of the tippy top of the tree, for the
// branches pane

	atui_branch* const atui_root = commons->atomtree_root->atui_root;

	GObject* const gbranch = g_object_new(G_TYPE_OBJECT, NULL);
	g_object_set_data(gbranch, "branch", atui_root);
	GListStore* const ls_model = g_list_store_new(G_TYPE_OBJECT);
	g_list_store_append(ls_model, gbranch);
	g_object_unref(gbranch);

	// TreeList, along with branch_tlmodel_func, creates our collapsable model.
	GtkTreeListModel* const tlist_atui = gtk_tree_list_model_new(
		G_LIST_MODEL(ls_model), false, true, branch_tlmodel_func, NULL,NULL
	);

	GtkSingleSelection* const sel_model = gtk_single_selection_new(
		G_LIST_MODEL(tlist_atui)
	);

	// Change the leaves pane's model based on the what is selected in branches
	g_signal_connect(sel_model,
		"selection-changed", G_CALLBACK(set_leaves_list), commons
	);

	return GTK_SELECTION_MODEL(sel_model);
	// Does not need to be unref'd if used with a new().
	// Needs to be unref'd if used with a set().
}



static void
branch_name_column_spawner(
		const GtkSignalListItemFactory* const factory,
		GtkListItem* const list_item
		) {
// setup
//TODO use https://docs.gtk.org/gtk4/class.Inscription.html

	GtkWidget* const expander = gtk_tree_expander_new();
	gtk_tree_expander_set_indent_for_icon(GTK_TREE_EXPANDER(expander), true);

	GtkWidget* const label = gtk_label_new(NULL);
	gtk_label_set_xalign(GTK_LABEL(label), 0);
	gtk_tree_expander_set_child(GTK_TREE_EXPANDER(expander), label);

	gtk_list_item_set_child(list_item, expander);
}
static void
branch_name_column_recycler(
		GtkSignalListItemFactory* const factory,
		GtkListItem* const list_item
		) {
// bind

	GtkTreeExpander* const expander = GTK_TREE_EXPANDER(
		gtk_list_item_get_child(list_item)
	);
	GtkWidget* const label = gtk_tree_expander_get_child(expander);

	GtkTreeListRow* const tree_list_item = gtk_list_item_get_item(list_item);
	GObject* const gobj_branch = gtk_tree_list_row_get_item(tree_list_item);
	atui_branch* const branch = g_object_get_data(gobj_branch, "branch");
	g_object_unref(gobj_branch);

	gtk_label_set_text(GTK_LABEL(label), branch->name);

	gtk_tree_expander_set_list_row(expander, tree_list_item);
}
static void
branch_type_column_recycler(
		GtkSignalListItemFactory* const factory,
		GtkListItem* const list_item
		) {
// bind

	GtkWidget* const label = gtk_list_item_get_child(list_item);

	GtkTreeListRow* const tree_list_item = gtk_list_item_get_item(list_item);
	GObject* const gobj_branch = gtk_tree_list_row_get_item(tree_list_item);
	atui_branch* const branch = g_object_get_data(gobj_branch, "branch");
	g_object_unref(gobj_branch);

	gtk_label_set_text(GTK_LABEL(label), branch->varname);
}
inline static GtkWidget*
create_branches_pane(
		yaabegtk_commons* const commons,
		GtkSelectionModel* const atui_model
		) {

	// Columnview abstract
	GtkColumnView* const branches_list = GTK_COLUMN_VIEW(
		gtk_column_view_new(atui_model)
	);
	gtk_column_view_set_reorderable(branches_list, true);
	//gtk_column_view_set_show_row_separators(branches_list, true);
	gtk_column_view_set_show_column_separators(branches_list, true);
	commons->branches_view = branches_list;

	// Create and attach columns
	GtkListItemFactory* factory;
	GtkColumnViewColumn* column;


	factory = gtk_signal_list_item_factory_new();
	g_signal_connect(factory,
		"setup", G_CALLBACK(branch_name_column_spawner), NULL
	);
	g_signal_connect(factory,
		"bind", G_CALLBACK(branch_name_column_recycler), NULL
	);
	column = gtk_column_view_column_new("Table", factory);
	gtk_column_view_column_set_resizable(column, true);
	gtk_column_view_column_set_expand(column, true);
	gtk_column_view_append_column(branches_list, column);
	g_object_unref(column);

	factory = gtk_signal_list_item_factory_new();
	g_signal_connect(factory,
		"setup", G_CALLBACK(generic_label_column_spawner), NULL
	);
	g_signal_connect(factory,
		"bind", G_CALLBACK(branch_type_column_recycler), NULL
	);
	column = gtk_column_view_column_new("Struct Type", factory);
	gtk_column_view_column_set_resizable(column, true);
	gtk_column_view_append_column(branches_list, column);
	g_object_unref(column);


	GtkWidget* const scrolledlist = gtk_scrolled_window_new();
	gtk_scrolled_window_set_child(
		GTK_SCROLLED_WINDOW(scrolledlist), GTK_WIDGET(branches_list)
	);
	GtkWidget* const frame = gtk_frame_new(NULL);
	gtk_frame_set_child(GTK_FRAME(frame), scrolledlist);

	return frame;
}





struct atom_tree*
atomtree_from_gfile(
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

	const int64_t filesize = g_file_info_get_size(fi_size);
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
		GError* const ferror,
		const char8_t* const title
		) {
// Simple error popup

	GtkEventController* const escapeclose = gtk_shortcut_controller_new();
	gtk_shortcut_controller_add_shortcut(
		GTK_SHORTCUT_CONTROLLER(escapeclose),
		gtk_shortcut_new(
			gtk_shortcut_trigger_parse_string("Escape"),
			gtk_named_action_new("window.close")
		)
	);

	GtkWindow* const notify_window = GTK_WINDOW(gtk_window_new());

	gtk_widget_add_controller(GTK_WIDGET(notify_window), escapeclose);
	gtk_window_set_title(notify_window, title);
	gtk_window_set_default_size(notify_window, 100,100);
	gtk_window_set_child(notify_window,
		gtk_label_new(ferror->message)
	);

	gtk_window_present(notify_window);
}
inline static void
yaabegtk_load_bios(
		yaabegtk_commons* const commons,
		GFile* const biosfile,
		GError** const ferror_out
		) {
// Processes necessary triggers for loading a bios, except final error handling

	GError* ferror = NULL;

	struct atom_tree* const atree = atomtree_from_gfile(biosfile, &ferror);
	if (ferror) {
		goto ferr;
	}

	if (atree) {
		struct atom_tree* const oldtree = commons->atomtree_root;

		commons->atomtree_root = atree;
		GtkSelectionModel* const newmodel = atui_gtk_model(commons);
		gtk_column_view_set_model(commons->branches_view, newmodel);
		set_leaves_list(newmodel, 0,1, commons);

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
	filer_error_window(ferror, "YAABE Load BIOS");
	ferr_nomsg:
	g_error_free(ferror);
	return;

}
static void
load_button_open_bios(
		GtkWidget* const button,
		gpointer const commonsptr
		) {
// Signal callback

	yaabegtk_commons* const commons = commonsptr;

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
	//TODO https://gitlab.gnome.org/GNOME/xdg-desktop-portal-gnome/-/issues/84
	gtk_file_dialog_set_initial_folder(filer, working_dir);
	g_object_unref(working_dir);

	gtk_file_dialog_open(filer,
		active_window, NULL, filedialog_load_and_set_bios, commons
	);
	g_object_unref(filer);
}


static void
reload_button_reload_bios(
		GtkWidget* const button,
		gpointer const commonsptr
		) {
// signal callback

	yaabegtk_commons* const commons = commonsptr;
	struct atom_tree* const old_tree = commons->atomtree_root;

	struct atom_tree* const new_tree = atombios_parse(
		old_tree->alloced_bios, old_tree->biosfile_size, true
	);
	new_tree->biosfile = old_tree->biosfile;
	new_tree->biosfile_size = old_tree->biosfile_size;
	commons->atomtree_root = new_tree;

	GtkSelectionModel* const newmodel = atui_gtk_model(commons);
	gtk_column_view_set_model(commons->branches_view, newmodel);
	set_leaves_list(newmodel, 0,1, commons);

	g_object_unref(newmodel);
	destroy_atomtree_with_gtk(old_tree, false);
}



static void
save_button_same_file(
		GtkWidget* const button,
		gpointer const commonsptr
		) {
// signal callback

	yaabegtk_commons* const commons = commonsptr;
	GError* ferror = NULL;

	atomtree_save_to_gfile(commons->atomtree_root, &ferror);
	if (ferror) {
		goto ferr;
	}

	return;

	ferr:
	filer_error_window(ferror, "YAABE Save BIOS");
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
	filer_error_window(ferror, "YAABE Save BIOS As");
	ferr_nomsg:
	g_error_free(ferror);
	return;
}
static void
saveas_button_name_bios(
		GtkWidget* const button,
		gpointer const commonsptr
		) {
// Signal callback

	yaabegtk_commons* const commons = commonsptr;

	GtkFileDialog* const filer = gtk_file_dialog_new();
	GtkWindow* const active_window = gtk_application_get_active_window(
		commons->yaabe_gtk
	);
	GFile* const working_dir = g_file_get_parent(
		commons->atomtree_root->biosfile
	);
	gtk_file_dialog_set_initial_folder(filer, working_dir);
	g_object_unref(working_dir);

	gtk_file_dialog_save(filer,
		active_window, NULL, filedialog_saveas_bios, commons
	);
	g_object_unref(filer);
}

inline static GtkWidget*
buttons_box(
		yaabegtk_commons* const commons
		) {

	GtkWidget* const load_button = gtk_button_new_with_label("Load");
	g_signal_connect(load_button,
		"clicked", G_CALLBACK(load_button_open_bios), commons
	);
	GtkWidget* const reload_button = gtk_button_new_with_label("Reload");
	g_signal_connect(reload_button,
		"clicked", G_CALLBACK(reload_button_reload_bios), commons
	);
	GtkWidget* const load_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_append(GTK_BOX(load_buttons),
		gtk_separator_new(GTK_ORIENTATION_HORIZONTAL)
	);
	gtk_box_append(GTK_BOX(load_buttons), load_button);
	gtk_box_append(GTK_BOX(load_buttons), reload_button);


	GtkWidget* const save_button = gtk_button_new_with_label("Save");
	g_signal_connect(save_button,
		"clicked", G_CALLBACK(save_button_same_file), commons
	);
	GtkWidget* const saveas_button = gtk_button_new_with_label("Save As");
	g_signal_connect(saveas_button,
		"clicked", G_CALLBACK(saveas_button_name_bios), commons
	);
	GtkWidget* const save_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_append(GTK_BOX(save_buttons), save_button);
	gtk_box_append(GTK_BOX(save_buttons), saveas_button);


	GtkWidget* const cf_button = gtk_button_new_with_label("Function Tables");
	gtk_widget_set_sensitive(cf_button, false);

	GtkWidget* const buttonboxes = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 30);
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
		const GValue* const value,
		const gdouble x,
		const gdouble y,
		gpointer const commonsptr
		) {
// Load a bios from a drag-n'-drop
// ???  https://gitlab.gnome.org/GNOME/gtk/-/issues/3755

	yaabegtk_commons* const commons = commonsptr;
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

static void
app_activate(
		GtkApplication* const gtkapp,
		gpointer const commonsptr
		) {
/* TODO
If there is no file set during bootup the branches-leaves panes need to be
hidden; when a file is set unhide it.
*/

	yaabegtk_commons* const commons = commonsptr;

	GtkSelectionModel* atui_model = NULL;
	if (commons->atomtree_root) {
		atui_model = atui_gtk_model(commons);
	}

	GtkWidget* const branches_pane = create_branches_pane(commons, atui_model);
	GtkWidget* const leaves_pane = create_leaves_pane(commons);
	GtkWidget* const tree_divider = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_paned_set_resize_start_child(GTK_PANED(tree_divider), true);
	gtk_paned_set_shrink_start_child(GTK_PANED(tree_divider), false);
	gtk_paned_set_resize_end_child(GTK_PANED(tree_divider), true);
	gtk_paned_set_shrink_end_child(GTK_PANED(tree_divider), false);
	//gtk_widget_set_size_request(branches_pane, 34, 50); // 1/3 horizontal
	//gtk_widget_set_size_request(leaves_pane, 66, 50);  // 2/3
	gtk_paned_set_start_child(GTK_PANED(tree_divider), branches_pane);
	gtk_paned_set_end_child(GTK_PANED(tree_divider), leaves_pane);

	if (commons->atomtree_root) {
		set_leaves_list(atui_model, 0,1, commons);
	} else {
		//gtk_widget_set_visible(tree_divider, false);
	}

	// TODO https://docs.gtk.org/gtk4/class.BoxLayout.html
	GtkWidget* const button_pane_complex = gtk_box_new(
		GTK_ORIENTATION_VERTICAL, 5
	);
	GtkWidget* const buttonboxes = buttons_box(commons);
	gtk_widget_set_vexpand(tree_divider, true);
	gtk_box_append(GTK_BOX(button_pane_complex), tree_divider);
	gtk_box_append(GTK_BOX(button_pane_complex), buttonboxes);
	gtk_box_append(GTK_BOX(button_pane_complex),
		gtk_separator_new(GTK_ORIENTATION_HORIZONTAL)
	);


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

	set_editor_titlebar(commons);
	gtk_window_set_default_size(window, 1400,700); // 2:1
	gtk_window_set_child(window, button_pane_complex);
	gtk_window_present(window);

}

int8_t
yaabe_gtk(
		struct atom_tree** const atree
		) {
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
	//yaabegtk_commons* const commons = calloc(1, sizeof(yaabegtk_commons)); // 0'd
	yaabegtk_commons commons;
	commons.atomtree_root = *atree;

	commons.yaabe_gtk = gtk_application_new(NULL, G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(commons.yaabe_gtk,
		"activate", G_CALLBACK(app_activate), &commons
	);
	const int8_t status = g_application_run(
		G_APPLICATION(commons.yaabe_gtk), 0,NULL
	);

	*atree = commons.atomtree_root;
	g_object_unref(commons.yaabe_gtk);
	//free(commons);

	return status;
}
