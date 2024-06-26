#ifndef GATUI_PRIVATE_H
#define GATUI_PRIVATE_H

#include "gatui.h"
#include "yaabe_gtk4.h"

GtkSelectionModel* const*
gatui_tree_get_enum_models_cache( // for GATUILeaves generation
		GATUITree* self
		);

void
atui_leaves_to_gliststore( // for GATUILeaves generation
		GListStore* list,
		atui_leaf* leaves,
		uint16_t num_leaves,
		GATUITree* root
		);

void
gatui_leaf_emit_val_changed( // single-signal multi-user alert network
		GATUILeaf* self
		);


#endif
