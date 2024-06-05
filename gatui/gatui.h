#ifndef GATUI_H
#define GATUI_H

#include "gatui_branch.h"
#include "gatui_leaf.h"

// a cache of selection-model'd simple-gobect of all atui_enum's and their
// entries.
// The purpose of this is to share and deduplicate enum generation
void
generate_enum_models_cache(
		GtkSelectionModel** enum_models_cache
		);
void
unref_enum_models_cache(
		GtkSelectionModel** enum_models_cache
		);
#endif
