#ifndef YAABE_GTK_INTERNAL_H
#define YAABE_GTK_INTERNAL_H

#include "standard.h"
#include "gatui.h"
#include "yaabe_gtk4.h"

struct pane_context {
	GtkColumnView* view; // so branches can set leaves, and loading bios
	GtkPopover* rightclick;
};
struct yaabe_gtk_search {
	GtkWindow* window;
	GtkWidget* entry;
	GtkWidget* branches_checkbox;
	struct pane_context pane;
	struct gatui_search_flags flags;
};
typedef struct yaabegtk_commons { // global state tracker
	GATUITree* root;
	GtkApplication* yaabe_gtk;
	GtkWindow* yaabe_primary;

	GtkEditable* pathbar;

	// preserve scroll position of the leaves pane if the previous branch is
	// compatible with new selected branch
	float64_t previous_scroll_position;
	GATUIBranch* previous_selection;

	struct pane_context branches;
	struct pane_context leaves;

	// For gtk_widget_set_sensitive() -- don't allow when no bios is loaded
	GtkWidget* save_buttons;
	GtkWidget* reload_buttons;

	char* pathbar_string;

	struct yaabe_gtk_search search;
} yaabegtk_commons;

void
create_about_window(
		yaabegtk_commons* commons
		);

void
yaabe_gtk_scroll_to_object( // scroll to based on a branch/leaf object
		yaabegtk_commons const* commons,
		GATUINode* tree_node
		);
void
yaabe_gtk_scroll_to_path( // /scroll/to/based/on/path
		yaabegtk_commons const* commons,
		char const* path,
		struct atui_path_goto** map_error // optional
		);

void
first_load_restore_path( // from config file
        yaabegtk_commons* commons
        );
void
generic_error_popup(
		char const* primary, // message
		char const* secondary, // message
		GtkApplication* parent_app
		);
void
create_and_set_active_gatui_model(
		yaabegtk_commons* commons,
		GATUITree* new_root
		);
void
set_editor_titlebar(
		yaabegtk_commons* commons
		);

// menus
void
construct_menu_bar(
		yaabegtk_commons* commons
		);
GtkWidget*
construct_loadsave_buttons_box(
		yaabegtk_commons* commons
		);
gboolean
dropped_file_open_bios( // callback for drag-n'-drop open file
		GtkDropTarget* dropctrl,
		GValue const* value,
		gdouble x,
		gdouble y,
		yaabegtk_commons* commons
		);


// panes
void
label_column_setup(
		void const* _null, // swapped-signal:: with factory
		GtkColumnViewCell* column_cell
		);

GtkWidget*
construct_tree_panes(
	yaabegtk_commons* commons
	);


// rightclick
void
branches_rightclick_row_bind( // responsible for rightclick context
		yaabegtk_commons const* commons,
		GtkColumnViewRow* view_row
		);
void
create_branches_rightclick_menu(
		yaabegtk_commons* commons
		);

void
leaves_rightclick_row_bind( // responsible for rightclick context
		yaabegtk_commons const* commons,
		GtkColumnViewRow* view_row
		);
void
create_leaves_rightclick_menu(
		yaabegtk_commons* commons
		);

void
search_rightclick_row_bind( // responsible for rightclick context
		yaabegtk_commons const* commons,
		GtkColumnViewRow* view_row
		);
void
create_search_rightclick_menu(
		yaabegtk_commons* commons
		);

// config file
GFile*
get_cached_working_dir(
		);
void
set_cached_working_dir(
		GFile* biosfile
		);

void
set_cached_scroll_path(
		char const* path
		);

char* // needs to be freed.
get_cached_scroll_path(
		);

// search

void
create_search_window(
		yaabegtk_commons* commons
		);


#endif
