#ifndef GATUI_PRIVATE_H
#define GATUI_PRIVATE_H

#include <glib-object.h>

#include "atomtree.h"
#include "atui.h"
#include "gatui.h"
#include "yaabe_gtk4.h"

void
atui_leaves_to_gliststore( // for GATUILeaves generation
		GListStore* list,
		atui_leaf* leaves,
		uint16_t num_leaves
		);

void
gatui_leaf_emit_val_changed( // single-signal multi-user alert network
		GATUILeaf* const self
		);

#endif
