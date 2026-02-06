#include "standard.h"
#include "atomtree.h"
#include "atomtree_internal.h"

bool // error
offchk( // check to see if the bios pointer math is within allocation bounds
		struct atomtree_commons* const commons,
		void const* const bios,
		size_t const size
		) {
    struct atom_tree const* const atree = commons->atree;
	void const* const end = atree->alloced_bios + atree->biosfile_size;

	bool const safe = (
		(
			(atree->alloced_bios <= bios)
			&& ((bios+size) < end)
		) || (
			(NULL == bios) || (0 == size)
		)
	);
	// backtrace? line number?
	error_assert(
		&(commons->error), ERROR_WARNING,
		"bad pointer math",
		safe
	);
	return !safe;
}

bool // error
_offreset( // check to see if pointer targets bios, and if it isn't, NULL it.
		struct atomtree_commons* const commons,
		void const** const ptr, // atomtree element that points to bios
		size_t const size // size of the bios structure
		) {
	bool const unsafe = offchk(commons, *ptr, size);
	if (unsafe) {
		*ptr = NULL;
	}
	return unsafe;
}
