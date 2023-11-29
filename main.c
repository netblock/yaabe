#include "atomtree.h"
#include "atui.h"
#include "yaabe_gtk4.h"

int main(int argc, char8_t** argv) {
	struct atom_tree* atree = NULL;

	if (argc > 1) {
		GError* ferror = NULL;
		GFile* const biosfile = g_file_new_for_path(argv[1]);
		atree = atomtree_from_gfile(biosfile, NULL);
		if (ferror) {
			printf("%s\n", ferror->message);
			g_error_free(ferror);
			return 1;
		}
		if (atree == NULL) {
			printf("bad atree\n");
			return 1;
		}
		g_object_unref(biosfile);
	}

	yaabe_gtk(&atree);
	destroy_atomtree_with_gtk(atree, true);

	return 0;
}
