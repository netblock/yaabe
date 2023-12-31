#ifndef YAABE_GTK4_H
#define YAABE_GTK4_H

struct atom_tree*
atomtree_from_gfile(
		GFile* biosfile,
		GError** ferror_out
		);
void
atomtree_save_to_gfile(
		struct atom_tree* atree,
		GError** ferror_out
		);

void
destroy_atomtree_with_gtk(
		struct atom_tree* atree,
		bool free_bios
		);
void
atui_destroy_tree_with_gtk(
		atui_branch* tree
		);

int8_t
yaabe_gtk(
		struct atom_tree** atree
		);

#endif
