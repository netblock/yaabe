#include "atomtree.h"
#include "atui.h"
#include "gatui.h"
#include "yaabe_gtk4.h"

int
main(
		int const argc,
		char const* const* const argv
		) {
	GATUITree* atree = NULL;

	if (argc > 1) {
		GError* ferror = NULL;
		atree = gatui_tree_new_from_path(argv[1], &ferror);
		if (ferror) {
			printf("%s\n", ferror->message);
			g_error_free(ferror);
			return 1;
		}
	}

	yaabe_gtk(&atree);
	g_object_unref(atree);

	return 0;
}
