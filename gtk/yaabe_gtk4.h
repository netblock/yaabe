#ifndef YAABE_GTK4_H
#define YAABE_GTK4_H

struct atom_tree*
atomtree_load_from_gfile(
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

int8_t
yaabe_gtk(
		struct atom_tree** atree
		);



void
free_closure(
		gpointer data,
		GClosure* closure
		);
void
free_notify(
		gpointer data
		);

#endif
