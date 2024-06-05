#include "gatui_private.h"

void
atui_leaves_to_gliststore(
		GListStore* const list,
		atui_leaf* const leaves,
		uint16_t const num_leaves,
		GtkSelectionModel** const enum_models_cache
		) {
// If the parent leaf has children, but the parent is labeled with ATUI_SUBONLY,
// adopt them in.
	for (uint16_t i=0; i < num_leaves; i++) {
		atui_leaf* leaf = &(leaves[i]);
		if (leaf->type.disable) {
			if (leaf->type.disable == ATUI_SUBONLY) {
				atui_leaves_to_gliststore(
					list, leaf->child_leaves, leaf->num_child_leaves,
					enum_models_cache
				);
			}
		} else {
			GATUILeaf* gleaf = gatui_leaf_new(leaf, enum_models_cache);
			g_list_store_append(list, gleaf);
			g_object_unref(gleaf);
		}
	}
}

void
generate_enum_models_cache(
		GtkSelectionModel** const enum_models_cache
		) {
	static_assert(UINT8_MAX >= ATUI_ENUM_ARRAY_LENGTH);
	for (uint8_t set_i=0; set_i < ATUI_ENUM_ARRAY_LENGTH; set_i++) {
		struct atui_enum const* atuienum = &(ATUI_ENUM_ARRAY[set_i]);

		GListStore* list = g_list_store_new(G_TYPE_OBJECT);
		for (uint8_t entry_i=0; entry_i < atuienum->num_entries; entry_i++) {
			GObject* gobj_child = g_object_new(G_TYPE_OBJECT, NULL);
			g_object_set_data(gobj_child, "enum",
				(struct atui_enum_entry*)
				&(atuienum->enum_array[entry_i]) // de-const
			);
			g_list_store_append(list, gobj_child);
			g_object_unref(gobj_child);
		}

		GtkSingleSelection* enum_model = gtk_single_selection_new(
			G_LIST_MODEL(list)
		);
		gtk_single_selection_set_can_unselect(enum_model, true);
		gtk_single_selection_set_autoselect(enum_model, false);
		enum_models_cache[set_i] = GTK_SELECTION_MODEL(enum_model);
	}
}

void
unref_enum_models_cache(
		GtkSelectionModel** const enum_models_cache
		) {
	static_assert(UINT8_MAX >= ATUI_ENUM_ARRAY_LENGTH);
	for (uint8_t set_i=0; set_i < ATUI_ENUM_ARRAY_LENGTH; set_i++) {
		g_clear_object(&(enum_models_cache[set_i]));
	}
}
