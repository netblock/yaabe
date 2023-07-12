/*
AtomTree iterable interface for UIs.

TODO explain how to add add tables

Here be preprocessor dragons:
ATUI, specifically atui.c is intended to as human-readable as possible,
absrtracting away the programatic consequences of allocation and setup.
This means that ATUI's allocater/instanciator functions have a lot of 
that can be figured out at compile time.

vim replace patterns that help copypaste structs from atombios.h:
'<,'>s|struct |ATUI_FUNCIFY(|g
'<,'>s|.*uint[0-9]*_t[ ,^I]*|^I|g
'<,'>s|;.*|,|g
'<,'>s|,\n},|\r)|g
*/

#ifndef ATUI_H
#define ATUI_H
#include "ppatui.h"
#include <atomtree.h>


// shall be used in an array
struct atui_enum {
	char* name;
	int val;
};

enum i18n_languages {
	LANG_NOLANG = -1,

	LANG_ENGLISH = 0,

	LANG_TOTALLANGS
};

enum atui_type {
	ATUI_NAN = 0b000,
	ATUI_DEC = 0b001,
	ATUI_HEX = 0b010,
	ATUI_OCT = 0b011, // TODO not implemented
	ATUI_BIN = 0b100,
	ATUI_ANY = 0b111,

	ATUI_NODISPLAY = 1<<4,

	ATUI_NONE     = 1<<5, //TODO depricate
	ATUI_NOFANCY  = 1<<5,
	ATUI_BITFIELD = 1<<6,
	ATUI_ENUM     = 1<<7,  // see also PPATUI_FUNCIFY()
	ATUI_STRING   = 1<<8,  // meant for human-readable text
	ATUI_ARRAY    = 1<<9,  // no technical difference from string 
	ATUI_INLINE   = 1<<10, // pull in leaves from other tables
	ATUI_DYNARRAY = 1<<11, // for runtime array lengths
};

typedef struct _atui_branch atui_branch;
typedef struct _atui_leaf atui_leaf;
struct _atui_leaf {
	char name[40];
	const char* varname;
	char* description[LANG_TOTALLANGS];


	enum atui_type type; // bitfield struct
	uint16_t array_size;
	uint8_t total_bits; // number of bits for the leaf

	uint8_t num_bitfield_children;
	uint8_t bitfield_hi; //bitfield range end
	uint8_t bitfield_lo; //bitfield range start

	const struct atui_enum* enum_options; // array of text val pair
	uint8_t num_enum_opts;

	atui_branch** inline_branch;

	union {
		void*     val;
		uint8_t*  u8;
		uint16_t* u16;
		uint32_t* u32;
		uint64_t* u64;
	};

	void* auxiliary; // any extra info to hang off if necessary
};
struct  _atui_branch {
	char name[40];
	char* description;

	atui_branch** child_branches;
	uint8_t branch_count;
	uint8_t max_branch_count;

	atui_branch** inline_branches;
	uint8_t inline_branch_count;
	uint8_t max_inline_branch_count;
	

	atui_leaf* leaves;
	uint16_t leaf_count;
	uint16_t max_leaves;

	void* atomleaves;
	void* auxiliary; // alternative representation to leaves, if necessary
};

// reccomended buffer size for the upcomming text functions
#define ATUI_LEAVES_STR_BUFFER 70

//set the value from a string or array of 8-bit
int atui_set_from_text(atui_leaf* leaf, const char* buffer);
int atui_get_to_text(atui_leaf*, char* buffer);


//set or get the number value from the leaf
void atui_leaf_set_val(atui_leaf* leaf, uint64_t val);
uint64_t atui_leaf_get_val(atui_leaf* leaf);




//TODO stroll that considers 0b prefix?
uint64_t strtoll_2(const char* str);

//atui has auxiliary pointers to hang extra data off of and this deallocator
//doesn't consider.
void atui_destroy_tree(atui_branch* tree);



struct atui_funcify_args {
	void* atomtree;
	// Pointer to the relevant atomtree struct. Mainly for the bios pointer,
	// but is necessary if atomtree-computer data needs to be pulled in. Can be
	// optional depending on defined atui branch; use suggestbios instead.

	void* suggestbios;
	// Optional. A pointer to somewhere in the bios memory; mainly useful for
	// looping across an array within an atom struct.

	uint16_t num_branches;
	// Number of child branches this atui_branch will have.*/

	atui_branch** import_children;
	// If the child branches are preallocated, walk across this. This array
	// must have num_branches elements.
};


// funcify internal structs
struct dynarray_bounds { // for ATUI_DYNARRAY
	uint16_t numleaves; // number of leaves within the pattern.
	uint16_t dynarray_length; // the number of members to the dynamic array.

	void* array_start;
	uint32_t element_size;
	
	atui_branch* (*inl_func)(struct atui_funcify_args*);
	// function pointer to the _atui function, if the pattern is a ATUI_INLINE
};

struct dynarray_inline { // for ATUI_DYNARRAY leaves that has ATUI_INLINE
	atui_branch* (*func)(struct atui_funcify_args*);
	// function pointer to the _atui function for the inline pattern.

	struct atui_funcify_args args;
	// ..and its args. possibly not necessary.
};



PPATUI_HEADERIFY(atom_common_table_header);

PPATUI_HEADERIFY(atom_rom_header_v2_2);
PPATUI_HEADERIFY(atom_master_data_table_v2_1);


// fuck me...
//PPATUI_HEADERIFY(atom_umc_reg_setting_data_block);
PPATUI_HEADERIFY(atom_umc_register_addr_info_access);


PPATUI_HEADERIFY(atom_vram_module_v10);
PPATUI_HEADERIFY(atom_vram_info_header_v2_4);

#endif
