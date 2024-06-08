#ifndef YAABE_GTK4_H
#define YAABE_GTK4_H

int8_t
yaabe_gtk(
		GATUITree** root
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
