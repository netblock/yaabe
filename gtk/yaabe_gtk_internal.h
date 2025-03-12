#ifndef YAABE_GTK_INTERNAL_H
#define YAABE_GTK_INTERNAL_H

#include "standard.h"
#include "gatui.h"
#include "yaabe_gtk4.h"

struct pane_context {
	GtkColumnView* view; // so branches can set leaves, and loading bios
	GtkPopover* rightclick;
};
typedef struct yaabegtk_commons { // global state tracker
	GATUITree* root;
	GtkApplication* yaabe_gtk;

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

} yaabegtk_commons;


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


// config file
GFile*
get_cached_working_dir(
		);
void
set_cached_working_dir(
		GFile* biosfile
		);

#endif
