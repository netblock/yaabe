#ifndef GATUI_LEAF_H
#define GATUI_LEAF_H

#include <glib-object.h>

#include "atomtree.h"
#include "atui.h"

G_BEGIN_DECLS

#define GATUI_TYPE_LEAF gatui_leaf_get_type()
G_DECLARE_FINAL_TYPE(GATUILeaf, gatui_leaf, GATUI, LEAF, GObject)

GATUILeaf*
gatui_leaf_new( // including all of is subleaves
		atui_leaf* leaf
		);

GListModel* // for GtkTreeListModelCreateModelFunc
gatui_leaf_generate_children_model(
		GATUILeaf* self
		);

enum atui_type
gatui_leaf_get_atui_type(
		GATUILeaf* self
		);
uint32_t
gatui_leaf_num_bytes(
		GATUILeaf* self
		);



GVariantType const*
gatui_leaf_get_gvariant_type(
		GATUILeaf* const self
		);
GVariant*
gatui_leaf_get_value(
		GATUILeaf* self
		);
bool
gatui_leaf_set_value(
		GATUILeaf* self,
		GVariant* value
		);

void
gatui_leaf_set_value_from_text(
		GATUILeaf* self,
		char8_t const* text
		);
char8_t*
gatui_leaf_value_to_text(
		GATUILeaf* self
		);


GtkSelectionModel*
gatui_leaf_get_enum_menu_selection_model( // for ATUI_ENUM
		GATUILeaf* self
		);
char8_t*
gatui_leaf_enum_entry_to_text(
		GATUILeaf* self,
		struct atui_enum_entry const* enum_entry
		);
bool
gatui_leaf_enum_entry_sets_value(
		GATUILeaf* self,
		struct atui_enum_entry const* enum_entry
		);


atui_leaf*
gatui_leaf_get_atui(
		GATUILeaf* self
		);

G_END_DECLS
#endif
