#ifndef ATOMTREE_INTERNAL_H
#define ATOMTREE_INTERNAL_H

struct atomtree_commons {
    struct atom_tree*  atree;
    void* bios;
    struct error     error; // error handling; landing is in atombios_parse
    struct mem_arena alloc_arena;
};


#define offchk(com, bios, size) unlikely(_offchk(com, bios, size))
bool // error
_offchk( // check to see if the bios pointer math is within allocation bounds
		struct atomtree_commons* com,
		void const* bios,
		size_t size
		);

// two-in-one combining offchk and sizeof_flex in a safe way
// ({ gnu c statement expression }) returns error
#define offchk_flex(com, bios, array, count) unlikely(({\
	struct atomtree_commons* const _c = (com);\
	auto const _ptr = (bios);\
	\
	bool err = false;\
	if (_ptr) {\
		err = offchk(_c, _ptr, sizeof(*_ptr));\
		if (!err) {\
			err = offchk(_c, _ptr, sizeof_flex(_ptr, array, count));\
		}\
	}\
	err;\
}))

bool // error
_offreset( // check to see if pointer targets bios, and if it isn't, NULL it.
		struct atomtree_commons* com,
		void const** ptr, // atomtree element that points to bios
		size_t size // size of the bios structure
		);

// casting wrapper for _offreset
// if given two arguments, the size is assumed to be sizeof(*ptr)
#define offrst(com, ptr, ...) _offrst_helper(\
	com, ptr, __VA_ARGS__ __VA_OPT__(,) sizeof(*ptr)\
)
#define _offrst_helper(com, ptr, size, ...) unlikely(_offreset(\
	(com), (void const**) (ptr), (size)\
))

// two-in-one combining offrst and sizeof_flex in a safe way
// ({ gnu c statement expression }) returns error
#define offrst_flex(com, ptr, array, count) unlikely(({\
	auto _at_ptr = (ptr);\
	bool const err = offchk_flex(com, *_at_ptr, array, count);\
	if (err) {\
		*_at_ptr = NULL;\
	}\
	err;\
}))

#endif
