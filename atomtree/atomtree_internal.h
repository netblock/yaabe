#ifndef ATOMTREE_INTERNAL_H
#define ATOMTREE_INTERNAL_H

struct atomtree_commons {
    struct atom_tree*  atree;
    void* bios;
    struct error     error; // error handling; landing is in atombios_parse
    struct mem_arena alloc_arena;
};


#define _off_helper(offfunc, com, ptr, size, ...) unlikely(offfunc(\
	(com), (ptr), (size)\
))


bool // error
_offchk( // check to see if the bios pointer math is within allocation bounds
		struct atomtree_commons* com,
		void const* bios,
		size_t size
		);

// if given two arguments, the size is assumed to be sizeof(*bios)
#define offchk(com, bios, ...) _off_helper(_offchk,\
	com, bios,  __VA_ARGS__ __VA_OPT__(,) sizeof(*bios)\
)

// two-in-one combining offchk and sizeof_flex in a safe way
// ({ gnu c statement expression }) returns error
#define offchk_flex(com, bios, array, count) unlikely(({\
	struct atomtree_commons* const _c = (com);\
	auto const _ptr = (bios);\
	\
	bool err = false;\
	if (_ptr) {\
		err = offchk(_c, _ptr);\
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
// if given two arguments, the size is assumed to be sizeof(**ptr)
#define offrst(com, ptr, ...) _off_helper(_offreset,\
	com, (void const**) ptr, __VA_ARGS__ __VA_OPT__(,) sizeof(**ptr)\
)

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
