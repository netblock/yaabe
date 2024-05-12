#ifndef GATUI_BRANCH_H
#define GATUI_BRANCH_H

#include <glib-object.h>

#include "atomtree.h"
#include "atui.h"

G_BEGIN_DECLS

#define GATUI_TYPE_BRANCH gatui_branch_get_type()
G_DECLARE_FINAL_TYPE(GATUIBranch, gatui_branch, GATUI, BRANCH, GObject)

GATUIBranch*
gatui_branch_new_tree( // including all of its descendants and leaves
		atui_branch* branch
		);

GListModel* // basic model for GtkTreeListModelCreateModelFunc
gatui_branch_generate_children_model(
		GATUIBranch* self
		);

GtkSelectionModel* // no-selection of a tree-model
gatui_branch_get_leaves_model(
		GATUIBranch* self
		);

atui_branch*
gatui_branch_get_atui(
		GATUIBranch* self
		);



G_END_DECLS
#endif
