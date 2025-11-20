#ifndef GATUI_LEAF_H
#define GATUI_LEAF_H
G_BEGIN_DECLS

#define GATUI_TYPE_LEAF gatui_leaf_get_type()
G_DECLARE_FINAL_TYPE(GATUILeaf, gatui_leaf, GATUI, LEAF, GATUINode)

GATUILeaf*
gatui_leaf_new( // including all of is subleaves
		atui_node* leaf
		);

struct atui_leaf_type const*
gatui_leaf_get_atui_type(
		GATUILeaf* self
		);
size_t // total bits
gatui_leaf_get_bitfield_size(
		GATUILeaf* self,
		size_t* end, // optiona; bitfield hi
		size_t* start // optional; bitfield lo
		);

bool // if value to/from text does anything
gatui_leaf_has_textable_value(
		GATUILeaf* self
		);
void
gatui_leaf_set_value_from_text(
		GATUILeaf* self,
		char const* text,
		bool big_endian // for arrays
		);
char* // must be freed
gatui_leaf_value_to_text(
		GATUILeaf* self,
		bool big_endian // for arrays
		);


GtkSelectionModel*
gatui_leaf_get_enum_menu_selection_model( // for ATUI_ENUM
		GATUILeaf* self
		);
char* // must be freed
gatui_leaf_enum_entry_to_text(
		GATUILeaf* self,
		struct atui_enum_entry const* enum_entry
		);
char* // must be freed
gatui_leaf_enum_val_to_text(
		GATUILeaf* self,
		struct atui_enum_entry const* enum_entry
		);
bool // true if successful
gatui_leaf_enum_entry_sets_value( // emtry must be associated
		GATUILeaf* self,
		struct atui_enum_entry const* enum_entry
		);
int16_t // -1 if error, otherwise index
gatui_leaf_enum_entry_get_possible_index(
		GATUILeaf* self
		);
G_END_DECLS
#endif
