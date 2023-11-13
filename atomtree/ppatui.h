/*
AtomTree iterable interface for UIs.

Here be preprocessor dragons

For main API use, see atui.h
For ATUI_FUNCIFY headers see atui_includes.h

ppatui.h contains the preprocessor hell for stuff like PPATUI_FUNCIFY()
*/

#ifndef PPATUI_H
#define PPATUI_H

/******************************* MAIN FUNCTIONS *******************************/

// To create the allocator function. See atui.c for how it is used.
#define PPATUI_FUNCIFY(\
		atom_type_prefix, atom_struct_name, atomtree_struct, ...)\
\
	_PPATUI_FUNCIFY_HELPER(atom_type_prefix, atom_struct_name, atomtree_struct\
		 __VA_OPT__(,) __VA_ARGS__)



// Thing to call to instanciate an atui_branch
#define ATUI_MAKE_BRANCH(\
		atom_struct_name, atomtree_pointer, bios_pointer,\
		num_branches, branch_import_pointer)\
\
	_##atom_struct_name##_atui(\
		&(struct atui_funcify_args) {\
			.atomtree = atomtree_pointer,\
			.suggestbios = bios_pointer,\
			.import_children = branch_import_pointer,\
			.num_child_branches = num_branches,\
		}\
	)



// To define an array of string-val pairs of an enum.
#define PPATUI_ENUMER(name, ...)\
\
	static const struct atui_enum const _atui_enum_##name[] =\
		{_PPATUI_ENUM_ENTRIES(__VA_ARGS__)};
#define _PPATUI_EENTRY(o, enum_member) {.name=#enum_member, .val=enum_member},


// To define the header entries for the aformentioned allocator functions.
#define PPATUI_HEADERIFY(atom_struct)\
	atui_branch* PPATUI_FUNC_NAME(atom_struct) (struct atui_funcify_args* args)


// PPATUI function interface:
#define PPATUI_FUNC_NAME(atomstruct)\
	_##atomstruct##_atui

/***************************** PREPROCESSOR HELL *****************************/

// main allocator function
#define _PPATUI_FUNCIFY_HELPER(\
		atomtypeprefix, atomtypesuffix, atomtreestruct, ...)\
PPATUI_HEADERIFY(atomtypesuffix) {\
\
	struct atomtreestruct * atomtree = args->atomtree;\
	atomtypeprefix atomtypesuffix * bios = args->suggestbios;\
\
	void* mallocvoid = NULL; /*temporary malloc partitioning pointer*/\
	atui_branch* table = NULL;\
\
\
	/* child branches: */\
	uint16_t branches_i = 0;\
	atui_branch** branches = NULL;\
\
	uint16_t max_num_child_branches = args->num_child_branches;\
	uint16_t num_child_branches = 0;\
	atui_branch** import_children = args->import_children;\
	uint16_t importchildren_i = 0;\
\
	/* inliners: */\
	atui_branch** inliners = NULL;\
	uint16_t num_inliners = 0;\
\
	/* child branches + inliners: */\
	uint16_t max_branch_count = 0;\
	atui_branch** all_branches = NULL;\
\
\
	atui_leaf* leaves = NULL;\
	uint16_t total_num_leaves = 0;\
	uint16_t max_alloced_leaves = 0;\
\
\
\
	if(_PPATUI_NUM_LEAVES(__VA_ARGS__)) {\
		/* counts bitfield members */\
		uint16_t leavesinit_i = 0;\
		const atui_leaf const leaves_init[] = { _PPATUI_LEAVES(__VA_ARGS__) };\
		const uint16_t leaves_init_num = sizeof(leaves_init)/sizeof(atui_leaf);\
\
\
		atui_branch* const inliners_init[] = {\
			_PPATUI_INLINE_BRANCHES(__VA_ARGS__)\
		};\
		const uint16_t inliners_init_num =\
			sizeof(inliners_init)/sizeof(atui_branch*);\
		num_inliners += inliners_init_num;\
\
\
		/*the leaf patterns for the runtime dynamic arrays.*/\
		uint16_t leafpattern_i = 0;\
		const atui_leaf const dynarray_patterns[] = {\
			_PPATUI_DYNARRAY(ROLL, __VA_ARGS__)\
		};\
		/*bounds contains amount of leaves per pattern, and the dimensions of
		the runtime array*/\
		uint16_t dynentry_i = 0;\
		const struct dynarray_bounds const dynarray_boundaries[] = {\
			_PPATUI_DYNARRAY(BOUNDS, __VA_ARGS__)\
		};\
		const uint8_t num_dynarray_sets =\
			sizeof(dynarray_boundaries) / sizeof(struct dynarray_bounds);\
\
		uint16_t dynarray_total_leaves = 0;\
		dynentry_i = 0;\
		leafpattern_i = 0;\
		for (; dynentry_i < num_dynarray_sets; dynentry_i++) {\
			dynarray_total_leaves +=\
				(dynarray_boundaries[dynentry_i].dynarray_length *\
				dynarray_boundaries[dynentry_i].numleaves);\
			if (dynarray_patterns[leafpattern_i].type & ATUI_INLINE) {\
				num_inliners +=\
					dynarray_boundaries[dynentry_i].dynarray_length;\
			}\
			leafpattern_i += dynarray_boundaries[dynentry_i].numleaves;\
		}\
		max_alloced_leaves = leaves_init_num + dynarray_total_leaves;\
\
\
		mallocvoid = malloc(\
			sizeof(atui_branch)\
			+ (max_num_child_branches + num_inliners) * sizeof(atui_branch*)\
			+ leaves_init_num * sizeof(atui_leaf)\
			+ dynarray_total_leaves * sizeof(atui_leaf)\
		);\
		table = mallocvoid;\
		mallocvoid += sizeof(atui_branch);\
		all_branches = mallocvoid;\
		if (max_num_child_branches) {\
			branches = mallocvoid;\
			mallocvoid += max_num_child_branches * sizeof(atui_branch*);\
		}\
		if (num_inliners) {\
			inliners = mallocvoid;\
			mallocvoid += num_inliners * sizeof(atui_branch*);\
		}\
		leaves = mallocvoid;\
		mallocvoid = NULL; /* we are done partitioning */\
\
\
\
		uint16_t inliners_i = 0;\
		uint16_t leaves_i = 0;\
		/*leavesinit_i = 0;*/\
/* Handle all leaves, not just dynarray: */\
		if (sizeof(dynarray_patterns)) {\
			/* Due to dynarray, the amount of inliners overall might be greater
			than the inliners_init amount:*/\
			uint16_t inlinersinit_i = 0;\
\
			/*if there's more than one ATUI_DYNARRAY in this branch:*/\
			dynentry_i = 0;\
			/*array in the bios:*/\
			void* dynarray_start_ptr = NULL;\
			uint32_t dynarray_elementsize = 0;\
			uint16_t dynarray_length = 0;\
			uint16_t dynarray_biosarray_i = 0;\
			/*leaf playback for each element in the bios array:*/\
			leafpattern_i = 0;\
			uint16_t leafpattern_numleaves = 0;\
			uint16_t leafpattern_start = 0;\
			uint16_t leafpattern_end = 0;\
			atui_branch* (*dynarray_inline_function)(struct atui_funcify_args*)\
				= NULL;\
			struct atui_funcify_args dynarray_inline_function_args = {\
				.atomtree=NULL, .suggestbios=NULL, .import_children=NULL,\
				.num_child_branches=0,\
			};\
\
			leavesinit_i = 0;\
			for (;leavesinit_i < leaves_init_num; leavesinit_i++) {\
\
				if (leaves_init[leavesinit_i].type & ATUI_DYNARRAY) {\
					dynarray_length =\
						dynarray_boundaries[dynentry_i].dynarray_length;\
					leafpattern_numleaves =\
						dynarray_boundaries[dynentry_i].numleaves;\
					dynarray_start_ptr =\
						dynarray_boundaries[dynentry_i].array_start;\
					dynarray_elementsize =\
						dynarray_boundaries[dynentry_i].element_size;\
\
					leaves[leaves_i] = leaves_init[leavesinit_i];\
					leaves[leaves_i].num_child_leaves =\
						dynarray_length * leafpattern_numleaves;\
					leaves_i++;\
\
					leafpattern_end =\
						leafpattern_start + leafpattern_numleaves;\
					if (dynarray_patterns[leafpattern_i].type & ATUI_INLINE) {\
						leafpattern_i = leafpattern_start;\
						dynarray_inline_function =\
							dynarray_boundaries[dynentry_i]\
								.dynarray_inline_function;\
						dynarray_inline_function_args.suggestbios =\
							dynarray_start_ptr;\
						dynarray_biosarray_i = 0;\
						while (dynarray_biosarray_i < dynarray_length) {\
							leaves[leaves_i] =\
								dynarray_patterns[leafpattern_i];\
							leaves[leaves_i].inline_branch =\
								&(inliners[inliners_i]);\
							/* if the name has a index number pattern: */\
							sprintf(leaves[leaves_i].name,\
								leaves[leaves_i].origname,\
								dynarray_biosarray_i\
							);\
							inliners[inliners_i] = dynarray_inline_function(\
								&dynarray_inline_function_args\
							);\
							inliners_i++;\
							leaves_i++;\
							dynarray_inline_function_args.suggestbios +=\
								dynarray_elementsize;\
							dynarray_biosarray_i++;\
						}\
					} else { /* If dynarray: if not inline.  Does bitfield*/\
						dynarray_biosarray_i = 0;\
						while (dynarray_biosarray_i < dynarray_length) {\
							leafpattern_i = leafpattern_start;\
							while (leafpattern_i < leafpattern_end) {\
								leaves[leaves_i] =\
									dynarray_patterns[leafpattern_i];\
								leaves[leaves_i].val = dynarray_start_ptr;\
								leaves_i++;\
								leafpattern_i++;\
							}\
							/* If the name has a index number pattern: */\
							sprintf(\
								leaves[leaves_i-leafpattern_numleaves].name,\
								leaves[leaves_i-leafpattern_numleaves]\
									.origname,\
								dynarray_biosarray_i\
							);\
							dynarray_start_ptr += dynarray_elementsize;\
							dynarray_biosarray_i++;\
						}\
					}\
					leafpattern_start = leafpattern_end;\
					dynentry_i++;\
\
				} else { /* If not dynarray (still has dynarray siblings) */\
					leaves[leaves_i] = leaves_init[leavesinit_i];\
					if (leaves_init[leavesinit_i].type & ATUI_INLINE) {\
						leaves[leaves_i].inline_branch =\
							&(inliners[inliners_i]);\
						inliners[inliners_i] = inliners_init[inlinersinit_i];\
						inliners_i++;\
						inlinersinit_i++;\
					}\
					leaves_i++;\
				}\
			}\
			total_num_leaves = leaves_i;\
\
\
\
/* Handle leaves if there's no dynarray at all: */\
		} else if (inliners_init_num) {\
			inliners_i = 0;\
			for(; inliners_i < num_inliners; inliners_i++) {\
				inliners[inliners_i] = inliners_init[inliners_i];\
			}\
\
			inliners_i = 0;\
			leaves_i = 0;\
			leavesinit_i = 0;\
			for (; leavesinit_i < leaves_init_num; leavesinit_i++){\
				leaves[leaves_i] = leaves_init[leavesinit_i];\
				if (leaves_init[leavesinit_i].type & ATUI_INLINE) {\
					leaves[leaves_i].inline_branch = &(inliners[inliners_i]);\
					inliners[inliners_i] = inliners_init[inliners_i];\
					inliners_i++;\
				}\
				leaves_i++;\
			}\
			total_num_leaves = leaves_i;\
\
\
\
/* Handle leaves if there's no dynarray or inline at all: */\
		} else {\
			leaves_i = 0;\
			leavesinit_i = 0;\
			while(leavesinit_i < leaves_init_num) {\
				leaves[leaves_i] = leaves_init[leavesinit_i];\
				leaves_i++;\
				leavesinit_i++;\
			}\
			total_num_leaves = leaves_i;\
		}\
\
\
\
/* Handle if there's no leaves at all: */\
	} else {\
		mallocvoid = malloc(\
			sizeof(atui_branch)\
			+ (max_num_child_branches * sizeof(atui_branch*))\
		);\
		table = mallocvoid;\
		mallocvoid = mallocvoid + sizeof(atui_branch);\
		all_branches = mallocvoid;\
		branches = mallocvoid;\
		mallocvoid = NULL; /* we are done partitioning */\
	}\
\
\
\
	if (max_num_child_branches) {\
		branches_i = 0;\
		importchildren_i = 0;\
		if (import_children) {\
			while (importchildren_i < max_num_child_branches) {\
				if (import_children[importchildren_i] != NULL) {\
					branches[branches_i] = import_children[importchildren_i];\
					branches_i++;\
				}\
			importchildren_i++;\
			}\
			num_child_branches = branches_i;\
		}\
		for (; branches_i < max_num_child_branches; branches_i++) {\
			branches[branches_i] = NULL;\
		}\
	}\
\
\
\
	*table = (atui_branch) {\
		.name = #atomtypesuffix,\
		.varname = #atomtypesuffix,\
		.description = NULL,\
		.atomleaves = bios,\
		.auxiliary = NULL,\
\
		.child_branches = branches,\
		.num_child_branches = num_child_branches,\
		.max_num_child_branches = max_num_child_branches,\
\
		.inline_branches = inliners,\
		.num_inline_branches = num_inliners,\
		.max_num_inline_branches = num_inliners,\
\
		.all_branches = all_branches,\
		.max_branch_count = (max_num_child_branches + num_inliners),\
\
		.leaves = leaves,\
		.leaf_count = total_num_leaves,\
		.max_leaves = max_alloced_leaves,\
	};\
	return table;\
}







/****************************** LEAF FANCY FUNCS ******************************/
/*
The fancy funcions here are about populating the fancy UI representation flags
for the leaves described in PPATUI_FUNCIFY().
That is, bitfield population, and enum and inline association.
*/


// Common guts and functions for Fancy.

#define _PPATUI_UNPACK1(to_depack)  _PPATUI_UNPACK0 to_depack
#define _PPATUI_UNPACK0(...) __VA_ARGS__

#define _PPATUI_LEAF_BITNESS(var) _Generic((var),\
	uint8_t*:8, uint16_t*:16, uint32_t*:32, uint64_t*:64,\
	uint8_t :8, uint16_t :16, uint32_t :32, uint64_t :64,\
\
	int8_t*:8, int16_t*:16, int32_t*:32, int64_t*:64,\
	int8_t :8, int16_t :16, int32_t :32, int64_t :64,\
\
	char: 8, char*: 8,\
\
	float16_t*:16, float32_t*:32, float64_t*:64,\
	float16_t :16, float32_t :32, float64_t :64,\
\
	default:0\
)
#define _PPATUI_LEAF_SIGNED(var) _Generic((var),\
	int8_t*:ATUI_SIGNED, int16_t*:ATUI_SIGNED, int32_t*:ATUI_SIGNED,\
	int8_t :ATUI_SIGNED, int16_t :ATUI_SIGNED, int32_t :ATUI_SIGNED,\
	int64_t*:ATUI_SIGNED,int64_t :ATUI_SIGNED,\
\
/*	float16_t*:ATUI_SIGNED, float32_t*:ATUI_SIGNED, float64_t*:ATUI_SIGNED,\
	float16_t :ATUI_SIGNED, float32_t :ATUI_SIGNED, float64_t :ATUI_SIGNED,\
*/\
\
	default:0\
)

#define _PPATUI_FANCY_NOBITFIELD(var)\
	.bitfield_hi=_PPATUI_LEAF_BITNESS(var)-1, .bitfield_lo=0,
#define _PPATUI_FANCY_NOBITFIELD_HARD\
	.bitfield_hi=0, .bitfield_lo=0,

#define _PPATUI_FANCY_NOENUM .enum_options=NULL, .num_enum_opts=0,
#define _PPATUI_FANCY_NOARRAY .array_size=0,

#define _PPATUI_FANCY_METALEAF\
	_PPATUI_FANCY_NOBITFIELD_HARD _PPATUI_FANCY_NOENUM _PPATUI_FANCY_NOARRAY


// TODO handle description_data
#define _PPATUI_FANCY_INIT(var, namestr, description_data, radix, fancytype)\
	{\
		.name = #namestr,\
		.origname = #namestr,\
		.varname = #var,\
		.description = NULL,\
		.type = (radix | _PPATUI_LEAF_SIGNED(var) | fancytype),\
		.array_size = 1,\
		.total_bits = _PPATUI_LEAF_BITNESS(var),\
		.num_child_leaves = 0,\
		.val = &(var),\
		.auxiliary = NULL,\

// Fancy common end



// ATUI_NOFANCY

#define _PPATUI_FANCY_ATUI_NOFANCY(\
		var, name, description_data, radix, fancytype, ...)\
	_PPATUI_FANCY_INIT(var, name, description_data, radix, fancytype)\
	_PPATUI_FANCY_NOBITFIELD(var) _PPATUI_FANCY_NOENUM\
	},

// Note the comma. The comma exists to trigger the existence of fancy_data
//#define ATUI_NOFANCY ATUI_NOFANCY ,
// needs to be defined after the enum atui_type; before causes the enum to break



// ATUI_ENUM

#define _PPATUI_FANCY_ATUI_ENUM(\
		var, name, description_data, radix, fancytype, enumname)\
	_PPATUI_FANCY_INIT(var, name, description_data, radix, fancytype)\
	.enum_options = _atui_enum_##enumname,\
	.num_enum_opts = (sizeof(_atui_enum_##enumname)/sizeof(struct atui_enum)),\
	_PPATUI_FANCY_NOBITFIELD(var)\
	},



// ATUI_STRING
// ATUI_ARRAY

#define _PPATUI_FANCY_ATUI_STRING(\
		var, name, description_data, radix, fancytype, ...)\
	_PPATUI_FANCY_ATUI_ARRAY(\
		var, name, description_data, radix, fancytype\
	)

#define _PPATUI_FANCY_ATUI_ARRAY(\
		var, name, description_data, radix, fancytype, ...)\
	_PPATUI_FANCY_INIT(var, name, description_data, radix, fancytype)\
	.array_size = (sizeof(var)/sizeof(var[0])),\
	_PPATUI_FANCY_NOBITFIELD(var)\
	_PPATUI_FANCY_NOENUM\
	},



// ATUI_BITFIELD

#define _ATUI_BITFIELD_NUMLEAVES(...) _PP_NUMARG(__VA_ARGS__)

#define _PPATUI_FANCY_ATUI_BITFIELD(\
		var, name, description_data, radix, fancytype, bitfielddata)\
	_PPATUI_FANCY_INIT(var, name, description_data, radix, fancytype)\
	.bitfield_hi = _PPATUI_LEAF_BITNESS(var) - 1,\
	.bitfield_lo = 0,\
	.num_child_leaves = ( _ATUI_BITFIELD_NUMLEAVES bitfielddata ),\
	_PPATUI_FANCY_NOENUM\
	},\
	_PPATUI_BITFIELD_LEAVES(\
		var, _PPATUI_UNPACK1(bitfielddata)\
	)
// Close parent and start on inbred children.
// ('inbred' because because the bitfiled children also direct children to the
// atui_branch)

#define _PPA_BFLEAF(parent_var, bfleaf)\
	_PPA_BFLEAF_HELPER1(\
		parent_var, _PPATUI_UNPACK1(bfleaf)\
	)
#define _PPA_BFLEAF_HELPER1(...) _PPA_BFLEAF_HELPER2(__VA_ARGS__)
// TODO handle description
#define _PPA_BFLEAF_HELPER2(\
		parent_var,\
		bfname, bit_end, bit_start, radix, description_data)\
	{\
		.name = #bfname,\
		.origname = #bfname,\
		.varname = #parent_var,\
		.description = NULL,\
		.type = (radix | _ATUI_BITCHILD),\
		.array_size = 1,\
		.total_bits = _PPATUI_LEAF_BITNESS(parent_var),\
		.bitfield_hi = bit_end,\
		.bitfield_lo = bit_start,\
		.num_child_leaves = 0,\
		.val = &(parent_var),\
		.auxiliary = NULL,\
		_PPATUI_FANCY_NOENUM\
	},



//ATUI_INLINE

// The meat of ATUI_INLINE is handled in the funcify
#define _PPATUI_FANCY_ATUI_INLINE(\
		var, name, description_data, radix, fancytype, inlinebranch)\
	_PPATUI_FANCY_INIT(var, name, description_data, radix, fancytype)\
	.val = NULL,\
	_PPATUI_FANCY_METALEAF\
	},


// Go through the leaves, find the ATUI_INLINERs, and gather their branches
#define _PPATUI_INBRANCH(m, leafdata)\
	_PPATUI_INBRANCH_HELPER1(_PPATUI_UNPACK0 leafdata)
#define _PPATUI_INBRANCH_HELPER1(...)\
	_PPATUI_INBRANCH_HELPER2(__VA_ARGS__)
#define _PPATUI_INBRANCH_HELPER2(var, name, displaydata, description_data)\
	_PPATUI_INBRANCH_HELPER3(var, _PPATUI_UNPACK0 displaydata)
#define _PPATUI_INBRANCH_HELPER3(...)\
	_PPATUI_INBRANCH_HELPER4(__VA_ARGS__)
#define _PPATUI_INBRANCH_HELPER4(var, radix, fancytype, ...)\
	_PPATUI_INBRANCH_##fancytype(var, __VA_ARGS__)

#define _PPATUI_INBRANCH_ATUI_NOFANCY(...)
#define _PPATUI_INBRANCH_ATUI_BITFIELD(...)
#define _PPATUI_INBRANCH_ATUI_ENUM(...)
#define _PPATUI_INBRANCH_ATUI_STRING(...)
#define _PPATUI_INBRANCH_ATUI_ARRAY(...)
#define _PPATUI_INBRANCH_ATUI_DYNARRAY(...)
#define _PPATUI_INBRANCH_ATUI_INLINE(instancename, atomstruct)\
	ATUI_MAKE_BRANCH(atomstruct, NULL, &(instancename), 0, NULL),



// ATUI_DYNARRAY

// Usually a placeholder. The meat of ATUI_DYNARRAY is handled in the funcify.
//TODO handle description_data
#define _PPATUI_FANCY_ATUI_DYNARRAY(\
		var, namestr, description_data, radix, fancytype, fancydata)\
	{\
		/* numleaves is handled in the dynarray expander func*/\
		.name = #namestr,\
		.origname = #namestr,\
		.varname = #var,\
		.description = NULL,\
		.type = (radix | fancytype),\
		.total_bits = 0,\
		.val = NULL,\
		.auxiliary = NULL,\
		_PPATUI_FANCY_METALEAF\
	},

// Unpack the leaf, and its displaydata from their respective parentheses.
// The variadic passthrough like _PPATUI_LEAF_HELPER1 executes the unpack.
//
// description_data gets moved to the left because fancy_data may not exist,
// due to ATUI_NOFANCY. The alternative is to have each fancy function unpack
// the display_data themselves, which might be more convoluted.
// Another way is to do a preprocessor define of ATUI_NOFANCY; see its section
// for more details
#define _PPATUI_LEAF(unused_o, leafdata)\
	_PPATUI_LEAF_HELPER1(_PPATUI_UNPACK0 leafdata)
#define _PPATUI_LEAF_HELPER1(...)\
	_PPATUI_LEAF_HELPER2(__VA_ARGS__)
#define _PPATUI_LEAF_HELPER2(var, name, display_data, description_data)\
	_PPATUI_LEAF_HELPER3(\
		var, name, description_data, _PPATUI_UNPACK0 display_data\
	)
#define _PPATUI_LEAF_HELPER3(...)\
	_PPATUI_LEAF_HELPER4(__VA_ARGS__)
#define _PPATUI_LEAF_HELPER4(\
		var, name, description_data, radix, fancytype, ...)\
	_PPATUI_FANCY_##fancytype(\
		var, name, description_data, radix, fancytype, __VA_ARGS__\
	)

/**************************** LEAF FANCY FUNCS END ****************************/




/**************************** ATUI_DYNARRAY STUFF *****************************/

// Go through the primary funcify leaves and find the ATUI_DINARRAY
#define _PPATUI_DYNAR_SERVICE(job, leafdata)\
	_PPATUI_DYNAR_SVCHELPER1(job, _PPATUI_UNPACK0 leafdata)
#define _PPATUI_DYNAR_SVCHELPER1(...)\
	_PPATUI_DYNAR_SVCHELPER2(__VA_ARGS__)
// Move description_data to the left because fancydata may not exist due
// to ATUI_NOFANCY:
#define _PPATUI_DYNAR_SVCHELPER2(job, var, name, displaydata, description_data)\
	_PPATUI_DYNAR_SVCHELPER3(\
			job,   var, name, description_data,\
			 _PPATUI_UNPACK0 displaydata\
	)
#define _PPATUI_DYNAR_SVCHELPER3(...)\
	_PPATUI_DYNAR_SVCHELPER4(__VA_ARGS__)
#define _PPATUI_DYNAR_SVCHELPER4(\
		job, var, name, description_data, radix, fancytype, ...)\
	_PPATUI_DYNAR_SVCHELPER5_##fancytype(\
			job, var, name, description_data, radix, __VA_ARGS__\
	) // The variadic may contain the fancydata

#define _PPATUI_DYNAR_SVCHELPER5_ATUI_NOFANCY(...)
#define _PPATUI_DYNAR_SVCHELPER5_ATUI_BITFIELD(...)
#define _PPATUI_DYNAR_SVCHELPER5_ATUI_ENUM(...)
#define _PPATUI_DYNAR_SVCHELPER5_ATUI_INLINE(...)
#define _PPATUI_DYNAR_SVCHELPER5_ATUI_ARRAY(...)
#define _PPATUI_DYNAR_SVCHELPER5_ATUI_STRING(...)
#define _PPATUI_DYNAR_SVCHELPER5_ATUI_DYNARRAY(\
		job, var, name, description_data, radix, fancydata)\
	_PPATUI_DYNAR_SVCHELPER6(\
		job, var, name, description_data, radix,\
		_PPATUI_UNPACK0 fancydata\
	)

#define _PPATUI_DYNAR_SVCHELPER6(job, ...)\
	_PPATUI_DYNAR_SVCHELPER7_##job(__VA_ARGS__)
// var, name, description_data, radix, leaf_pattern, start, count


// Unrolls the pattern into leaves to copy.
#define _PPATUI_DYNAR_SVCHELPER7_ROLL(\
		var, name, description_data, radix, leaf_pattern, start, count)\
	_PPATUI_LEAF(unused_o, leaf_pattern)

// Get the non-pattern metadata for the dynarray
// Struct dynarray_bounds ; see atui.h
#define _PPATUI_DYNAR_SVCHELPER7_BOUNDS(\
		var, name, description_data, radix, leaf_pattern, start, count)\
	{\
		.array_start = start,\
		.element_size = sizeof(start[0]),\
		.dynarray_length = count,\
		.numleaves = _PPATUI_DYNAR_BOUNDS_JOBS(\
			NUMLEAVES, _PPATUI_UNPACK0 leaf_pattern\
		),\
		.dynarray_inline_function = _PPATUI_DYNAR_BOUNDS_JOBS(\
			INLINEFUNC, _PPATUI_UNPACK0 leaf_pattern\
		),\
	},



#define _PPATUI_DYNAR_BOUNDS_JOBS(job, ...)\
	_PPATUI_DYNAR_BOUNDS_JOBS_HELPER0(job, __VA_ARGS__)
#define _PPATUI_DYNAR_BOUNDS_JOBS_HELPER0(\
		job, var, name, displaydata, description_data)\
	_PPATUI_DYNAR_BOUNDS_JOBS_HELPER1(job, _PPATUI_UNPACK0 displaydata)
#define _PPATUI_DYNAR_BOUNDS_JOBS_HELPER1(job, ...)\
	_PPATUI_DYNAR_BOUNDS_JOBS_HELPER2(job, __VA_ARGS__)
#define _PPATUI_DYNAR_BOUNDS_JOBS_HELPER2(job, radix, fancytype, ...)\
	_PPATUI_DYNAR_BOUNDS_HELPER3_##job##_##fancytype(__VA_ARGS__)

#define _PPATUI_DYNAR_BOUNDS_HELPER3_NUMLEAVES_ATUI_NOFANCY(...) 1
#define _PPATUI_DYNAR_BOUNDS_HELPER3_NUMLEAVES_ATUI_ENUM(...)    1
#define _PPATUI_DYNAR_BOUNDS_HELPER3_NUMLEAVES_ATUI_STRING(...)  1
#define _PPATUI_DYNAR_BOUNDS_HELPER3_NUMLEAVES_ATUI_ARRAY(...)   1
#define _PPATUI_DYNAR_BOUNDS_HELPER3_NUMLEAVES_ATUI_INLINE(...)  1
#define _PPATUI_DYNAR_BOUNDS_HELPER3_NUMLEAVES_ATUI_DYNARRAY(...) 0
#define _PPATUI_DYNAR_BOUNDS_HELPER3_NUMLEAVES_ATUI_BITFIELD(bitfields)\
	1 + _ATUI_BITFIELD_NUMLEAVES(_PPATUI_UNPACK0 bitfields )

#define _PPATUI_DYNAR_BOUNDS_HELPER3_INLINEFUNC_ATUI_NOFANCY(...)  NULL
#define _PPATUI_DYNAR_BOUNDS_HELPER3_INLINEFUNC_ATUI_BITFIELD(...) NULL 
#define _PPATUI_DYNAR_BOUNDS_HELPER3_INLINEFUNC_ATUI_ENUM(...)     NULL
#define _PPATUI_DYNAR_BOUNDS_HELPER3_INLINEFUNC_ATUI_STRING(...)   NULL
#define _PPATUI_DYNAR_BOUNDS_HELPER3_INLINEFUNC_ATUI_ARRAY(...)    NULL
#define _PPATUI_DYNAR_BOUNDS_HELPER3_INLINEFUNC_ATUI_DYNARRAY(...) NULL
#define _PPATUI_DYNAR_BOUNDS_HELPER3_INLINEFUNC_ATUI_INLINE(inltable)\
	 PPATUI_FUNC_NAME(inltable)

/************************** ATUI_DYNARRAY STUFF END ***************************/





// looper(config)(data) -> waterfall(data) ; where waterfall is like _1N1R256
#define _PPATUI_LEAVES(...)\
	_PPATUI_LOOPER(1,1,__VA_ARGS__)\
		(_PPATUI_LEAF ,, __VA_ARGS__)

#define _PPATUI_INLINE_BRANCHES(...)\
	_PPATUI_LOOPER(1,1,__VA_ARGS__)\
		(_PPATUI_INBRANCH ,, __VA_ARGS__)

#define _PPATUI_DYNARRAY(job, ...)\
	_PPATUI_LOOPER(1,1,__VA_ARGS__)\
		(_PPATUI_DYNAR_SERVICE, job, __VA_ARGS__)


#define _PPATUI_BITFIELD_LEAVES(datapack, ...)\
	_PPATUI_LOOPER(1,2,__VA_ARGS__)\
		(_PPA_BFLEAF, datapack, __VA_ARGS__)

#define _PPATUI_ENUM_ENTRIES(...)\
	_PPATUI_LOOPER(1,1,__VA_ARGS__)\
		(_PPATUI_EENTRY ,, __VA_ARGS__)


/*
Throw the to-be-counted args into the depthcan and then measure the how
full the depthcan is with the depthstick.
Scale both ruler and depthcan if you want to count more than 63 args.

python script:
for i in range(256): print("%i," % (255-i), end='')
for i in range(1,256): print("_%i," % (i), end='')
*/
#define _PP_ARGCOUNTER_RULER \
255,254,253,252,251,250,249,248,247,246,245,244,243,242,241,240,239,238,237,236,235,234,233,232,231,230,229,228,227,226,225,224,223,222,221,220,219,218,217,216,215,214,213,212,211,210,209,208,207,206,205,204,203,202,201,200,199,198,197,196,195,194,193,192,191,190,189,188,187,186,185,184,183,182,181,180,179,178,177,176,175,174,173,172,171,170,169,168,167,166,165,164,163,162,161,160,159,158,157,156,155,154,153,152,151,150,149,148,147,146,145,144,143,142,141,140,139,138,137,136,135,134,133,132,131,130,129,128,127,126,125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,109,108,107,106,105,104,103,102,101,100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0

#define _PP_ARGCOUNTER_DEPTHCAN(\
_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63,_64,_65,_66,_67,_68,_69,_70,_71,_72,_73,_74,_75,_76,_77,_78,_79,_80,_81,_82,_83,_84,_85,_86,_87,_88,_89,_90,_91,_92,_93,_94,_95,_96,_97,_98,_99,_100,_101,_102,_103,_104,_105,_106,_107,_108,_109,_110,_111,_112,_113,_114,_115,_116,_117,_118,_119,_120,_121,_122,_123,_124,_125,_126,_127,_128,_129,_130,_131,_132,_133,_134,_135,_136,_137,_138,_139,_140,_141,_142,_143,_144,_145,_146,_147,_148,_149,_150,_151,_152,_153,_154,_155,_156,_157,_158,_159,_160,_161,_162,_163,_164,_165,_166,_167,_168,_169,_170,_171,_172,_173,_174,_175,_176,_177,_178,_179,_180,_181,_182,_183,_184,_185,_186,_187,_188,_189,_190,_191,_192,_193,_194,_195,_196,_197,_198,_199,_200,_201,_202,_203,_204,_205,_206,_207,_208,_209,_210,_211,_212,_213,_214,_215,_216,_217,_218,_219,_220,_221,_222,_223,_224,_225,_226,_227,_228,_229,_230,_231,_232,_233,_234,_235,_236,_237,_238,_239,_240,_241,_242,_243,_244,_245,_246,_247,_248,_249,_250,_251,_252,_253,_254,_255,N,...) N

#define _PP_ARGCOUNTER_DEPTHCAN_HELPER(...) _PP_ARGCOUNTER_DEPTHCAN(__VA_ARGS__)
#define _PP_NUMARG(...)\
_PP_ARGCOUNTER_DEPTHCAN_HELPER(__VA_ARGS__ __VA_OPT__(,) _PP_ARGCOUNTER_RULER)

#define _PPATUI_NUM_LEAVES(...) _PP_NUMARG(__VA_ARGS__)



/*
python script:

def ppatui_nloop_helper(max_entries=64, args="a,b,c,d", rec_depth=1):
	numargs=len(args.split(","))
	looper = "_%iN%iR%s(f,o,%s)" % (numargs,rec_depth,"%s", "%s")
	la = looper % ("%i", "%s,..."%args)
	lb = looper % ("%i", "__VA_ARGS__")
	called = "f(o,%s)" % args
	s = "#define %s %s %s" % (la, called, lb)
	for i in range(0,max_entries*numargs, numargs):
		print(s % (i+numargs, i))


Generic waterfall loop for functions with 1 unique argument and 1 common.

The recurse/recusive depth is about the preprocessor "painting blue". That is,
after the waterfall loop has been used, it becomes undefined within that
recursion.
In other words, if the f() needs to call a loop, the loop that spun out the
f() f() f() f()... is no longer usable; the f() needs to call a different
waterfall.
*/
#define _PPATUI_LOOPER(numargs, recurse, ...)\
	_PPATUI_LOOPERH1(numargs, recurse, _PP_NUMARG(__VA_ARGS__))
#define _PPATUI_LOOPERH1(...) _PPATUI_LOOPERH2(__VA_ARGS__)
#define _PPATUI_LOOPERH2(n,r,d) _##n##N##r##R##d

#define _1N1R0(...)
#define _1N1R1(f,o,a,...) f(o,a) _1N1R0(f,o,__VA_ARGS__)
#define _1N1R2(f,o,a,...) f(o,a) _1N1R1(f,o,__VA_ARGS__)
#define _1N1R3(f,o,a,...) f(o,a) _1N1R2(f,o,__VA_ARGS__)
#define _1N1R4(f,o,a,...) f(o,a) _1N1R3(f,o,__VA_ARGS__)
#define _1N1R5(f,o,a,...) f(o,a) _1N1R4(f,o,__VA_ARGS__)
#define _1N1R6(f,o,a,...) f(o,a) _1N1R5(f,o,__VA_ARGS__)
#define _1N1R7(f,o,a,...) f(o,a) _1N1R6(f,o,__VA_ARGS__)
#define _1N1R8(f,o,a,...) f(o,a) _1N1R7(f,o,__VA_ARGS__)
#define _1N1R9(f,o,a,...) f(o,a) _1N1R8(f,o,__VA_ARGS__)
#define _1N1R10(f,o,a,...) f(o,a) _1N1R9(f,o,__VA_ARGS__)
#define _1N1R11(f,o,a,...) f(o,a) _1N1R10(f,o,__VA_ARGS__)
#define _1N1R12(f,o,a,...) f(o,a) _1N1R11(f,o,__VA_ARGS__)
#define _1N1R13(f,o,a,...) f(o,a) _1N1R12(f,o,__VA_ARGS__)
#define _1N1R14(f,o,a,...) f(o,a) _1N1R13(f,o,__VA_ARGS__)
#define _1N1R15(f,o,a,...) f(o,a) _1N1R14(f,o,__VA_ARGS__)
#define _1N1R16(f,o,a,...) f(o,a) _1N1R15(f,o,__VA_ARGS__)
#define _1N1R17(f,o,a,...) f(o,a) _1N1R16(f,o,__VA_ARGS__)
#define _1N1R18(f,o,a,...) f(o,a) _1N1R17(f,o,__VA_ARGS__)
#define _1N1R19(f,o,a,...) f(o,a) _1N1R18(f,o,__VA_ARGS__)
#define _1N1R20(f,o,a,...) f(o,a) _1N1R19(f,o,__VA_ARGS__)
#define _1N1R21(f,o,a,...) f(o,a) _1N1R20(f,o,__VA_ARGS__)
#define _1N1R22(f,o,a,...) f(o,a) _1N1R21(f,o,__VA_ARGS__)
#define _1N1R23(f,o,a,...) f(o,a) _1N1R22(f,o,__VA_ARGS__)
#define _1N1R24(f,o,a,...) f(o,a) _1N1R23(f,o,__VA_ARGS__)
#define _1N1R25(f,o,a,...) f(o,a) _1N1R24(f,o,__VA_ARGS__)
#define _1N1R26(f,o,a,...) f(o,a) _1N1R25(f,o,__VA_ARGS__)
#define _1N1R27(f,o,a,...) f(o,a) _1N1R26(f,o,__VA_ARGS__)
#define _1N1R28(f,o,a,...) f(o,a) _1N1R27(f,o,__VA_ARGS__)
#define _1N1R29(f,o,a,...) f(o,a) _1N1R28(f,o,__VA_ARGS__)
#define _1N1R30(f,o,a,...) f(o,a) _1N1R29(f,o,__VA_ARGS__)
#define _1N1R31(f,o,a,...) f(o,a) _1N1R30(f,o,__VA_ARGS__)
#define _1N1R32(f,o,a,...) f(o,a) _1N1R31(f,o,__VA_ARGS__)
#define _1N1R33(f,o,a,...) f(o,a) _1N1R32(f,o,__VA_ARGS__)
#define _1N1R34(f,o,a,...) f(o,a) _1N1R33(f,o,__VA_ARGS__)
#define _1N1R35(f,o,a,...) f(o,a) _1N1R34(f,o,__VA_ARGS__)
#define _1N1R36(f,o,a,...) f(o,a) _1N1R35(f,o,__VA_ARGS__)
#define _1N1R37(f,o,a,...) f(o,a) _1N1R36(f,o,__VA_ARGS__)
#define _1N1R38(f,o,a,...) f(o,a) _1N1R37(f,o,__VA_ARGS__)
#define _1N1R39(f,o,a,...) f(o,a) _1N1R38(f,o,__VA_ARGS__)
#define _1N1R40(f,o,a,...) f(o,a) _1N1R39(f,o,__VA_ARGS__)
#define _1N1R41(f,o,a,...) f(o,a) _1N1R40(f,o,__VA_ARGS__)
#define _1N1R42(f,o,a,...) f(o,a) _1N1R41(f,o,__VA_ARGS__)
#define _1N1R43(f,o,a,...) f(o,a) _1N1R42(f,o,__VA_ARGS__)
#define _1N1R44(f,o,a,...) f(o,a) _1N1R43(f,o,__VA_ARGS__)
#define _1N1R45(f,o,a,...) f(o,a) _1N1R44(f,o,__VA_ARGS__)
#define _1N1R46(f,o,a,...) f(o,a) _1N1R45(f,o,__VA_ARGS__)
#define _1N1R47(f,o,a,...) f(o,a) _1N1R46(f,o,__VA_ARGS__)
#define _1N1R48(f,o,a,...) f(o,a) _1N1R47(f,o,__VA_ARGS__)
#define _1N1R49(f,o,a,...) f(o,a) _1N1R48(f,o,__VA_ARGS__)
#define _1N1R50(f,o,a,...) f(o,a) _1N1R49(f,o,__VA_ARGS__)
#define _1N1R51(f,o,a,...) f(o,a) _1N1R50(f,o,__VA_ARGS__)
#define _1N1R52(f,o,a,...) f(o,a) _1N1R51(f,o,__VA_ARGS__)
#define _1N1R53(f,o,a,...) f(o,a) _1N1R52(f,o,__VA_ARGS__)
#define _1N1R54(f,o,a,...) f(o,a) _1N1R53(f,o,__VA_ARGS__)
#define _1N1R55(f,o,a,...) f(o,a) _1N1R54(f,o,__VA_ARGS__)
#define _1N1R56(f,o,a,...) f(o,a) _1N1R55(f,o,__VA_ARGS__)
#define _1N1R57(f,o,a,...) f(o,a) _1N1R56(f,o,__VA_ARGS__)
#define _1N1R58(f,o,a,...) f(o,a) _1N1R57(f,o,__VA_ARGS__)
#define _1N1R59(f,o,a,...) f(o,a) _1N1R58(f,o,__VA_ARGS__)
#define _1N1R60(f,o,a,...) f(o,a) _1N1R59(f,o,__VA_ARGS__)
#define _1N1R61(f,o,a,...) f(o,a) _1N1R60(f,o,__VA_ARGS__)
#define _1N1R62(f,o,a,...) f(o,a) _1N1R61(f,o,__VA_ARGS__)
#define _1N1R63(f,o,a,...) f(o,a) _1N1R62(f,o,__VA_ARGS__)
#define _1N1R64(f,o,a,...) f(o,a) _1N1R63(f,o,__VA_ARGS__)
#define _1N1R65(f,o,a,...) f(o,a) _1N1R64(f,o,__VA_ARGS__)
#define _1N1R66(f,o,a,...) f(o,a) _1N1R65(f,o,__VA_ARGS__)
#define _1N1R67(f,o,a,...) f(o,a) _1N1R66(f,o,__VA_ARGS__)
#define _1N1R68(f,o,a,...) f(o,a) _1N1R67(f,o,__VA_ARGS__)
#define _1N1R69(f,o,a,...) f(o,a) _1N1R68(f,o,__VA_ARGS__)
#define _1N1R70(f,o,a,...) f(o,a) _1N1R69(f,o,__VA_ARGS__)
#define _1N1R71(f,o,a,...) f(o,a) _1N1R70(f,o,__VA_ARGS__)
#define _1N1R72(f,o,a,...) f(o,a) _1N1R71(f,o,__VA_ARGS__)
#define _1N1R73(f,o,a,...) f(o,a) _1N1R72(f,o,__VA_ARGS__)
#define _1N1R74(f,o,a,...) f(o,a) _1N1R73(f,o,__VA_ARGS__)
#define _1N1R75(f,o,a,...) f(o,a) _1N1R74(f,o,__VA_ARGS__)
#define _1N1R76(f,o,a,...) f(o,a) _1N1R75(f,o,__VA_ARGS__)
#define _1N1R77(f,o,a,...) f(o,a) _1N1R76(f,o,__VA_ARGS__)
#define _1N1R78(f,o,a,...) f(o,a) _1N1R77(f,o,__VA_ARGS__)
#define _1N1R79(f,o,a,...) f(o,a) _1N1R78(f,o,__VA_ARGS__)
#define _1N1R80(f,o,a,...) f(o,a) _1N1R79(f,o,__VA_ARGS__)
#define _1N1R81(f,o,a,...) f(o,a) _1N1R80(f,o,__VA_ARGS__)
#define _1N1R82(f,o,a,...) f(o,a) _1N1R81(f,o,__VA_ARGS__)
#define _1N1R83(f,o,a,...) f(o,a) _1N1R82(f,o,__VA_ARGS__)
#define _1N1R84(f,o,a,...) f(o,a) _1N1R83(f,o,__VA_ARGS__)
#define _1N1R85(f,o,a,...) f(o,a) _1N1R84(f,o,__VA_ARGS__)
#define _1N1R86(f,o,a,...) f(o,a) _1N1R85(f,o,__VA_ARGS__)
#define _1N1R87(f,o,a,...) f(o,a) _1N1R86(f,o,__VA_ARGS__)
#define _1N1R88(f,o,a,...) f(o,a) _1N1R87(f,o,__VA_ARGS__)
#define _1N1R89(f,o,a,...) f(o,a) _1N1R88(f,o,__VA_ARGS__)
#define _1N1R90(f,o,a,...) f(o,a) _1N1R89(f,o,__VA_ARGS__)
#define _1N1R91(f,o,a,...) f(o,a) _1N1R90(f,o,__VA_ARGS__)
#define _1N1R92(f,o,a,...) f(o,a) _1N1R91(f,o,__VA_ARGS__)
#define _1N1R93(f,o,a,...) f(o,a) _1N1R92(f,o,__VA_ARGS__)
#define _1N1R94(f,o,a,...) f(o,a) _1N1R93(f,o,__VA_ARGS__)
#define _1N1R95(f,o,a,...) f(o,a) _1N1R94(f,o,__VA_ARGS__)
#define _1N1R96(f,o,a,...) f(o,a) _1N1R95(f,o,__VA_ARGS__)
#define _1N1R97(f,o,a,...) f(o,a) _1N1R96(f,o,__VA_ARGS__)
#define _1N1R98(f,o,a,...) f(o,a) _1N1R97(f,o,__VA_ARGS__)
#define _1N1R99(f,o,a,...) f(o,a) _1N1R98(f,o,__VA_ARGS__)
#define _1N1R100(f,o,a,...) f(o,a) _1N1R99(f,o,__VA_ARGS__)
#define _1N1R101(f,o,a,...) f(o,a) _1N1R100(f,o,__VA_ARGS__)
#define _1N1R102(f,o,a,...) f(o,a) _1N1R101(f,o,__VA_ARGS__)
#define _1N1R103(f,o,a,...) f(o,a) _1N1R102(f,o,__VA_ARGS__)
#define _1N1R104(f,o,a,...) f(o,a) _1N1R103(f,o,__VA_ARGS__)
#define _1N1R105(f,o,a,...) f(o,a) _1N1R104(f,o,__VA_ARGS__)
#define _1N1R106(f,o,a,...) f(o,a) _1N1R105(f,o,__VA_ARGS__)
#define _1N1R107(f,o,a,...) f(o,a) _1N1R106(f,o,__VA_ARGS__)
#define _1N1R108(f,o,a,...) f(o,a) _1N1R107(f,o,__VA_ARGS__)
#define _1N1R109(f,o,a,...) f(o,a) _1N1R108(f,o,__VA_ARGS__)
#define _1N1R110(f,o,a,...) f(o,a) _1N1R109(f,o,__VA_ARGS__)
#define _1N1R111(f,o,a,...) f(o,a) _1N1R110(f,o,__VA_ARGS__)
#define _1N1R112(f,o,a,...) f(o,a) _1N1R111(f,o,__VA_ARGS__)
#define _1N1R113(f,o,a,...) f(o,a) _1N1R112(f,o,__VA_ARGS__)
#define _1N1R114(f,o,a,...) f(o,a) _1N1R113(f,o,__VA_ARGS__)
#define _1N1R115(f,o,a,...) f(o,a) _1N1R114(f,o,__VA_ARGS__)
#define _1N1R116(f,o,a,...) f(o,a) _1N1R115(f,o,__VA_ARGS__)
#define _1N1R117(f,o,a,...) f(o,a) _1N1R116(f,o,__VA_ARGS__)
#define _1N1R118(f,o,a,...) f(o,a) _1N1R117(f,o,__VA_ARGS__)
#define _1N1R119(f,o,a,...) f(o,a) _1N1R118(f,o,__VA_ARGS__)
#define _1N1R120(f,o,a,...) f(o,a) _1N1R119(f,o,__VA_ARGS__)
#define _1N1R121(f,o,a,...) f(o,a) _1N1R120(f,o,__VA_ARGS__)
#define _1N1R122(f,o,a,...) f(o,a) _1N1R121(f,o,__VA_ARGS__)
#define _1N1R123(f,o,a,...) f(o,a) _1N1R122(f,o,__VA_ARGS__)
#define _1N1R124(f,o,a,...) f(o,a) _1N1R123(f,o,__VA_ARGS__)
#define _1N1R125(f,o,a,...) f(o,a) _1N1R124(f,o,__VA_ARGS__)
#define _1N1R126(f,o,a,...) f(o,a) _1N1R125(f,o,__VA_ARGS__)
#define _1N1R127(f,o,a,...) f(o,a) _1N1R126(f,o,__VA_ARGS__)
#define _1N1R128(f,o,a,...) f(o,a) _1N1R127(f,o,__VA_ARGS__)
#define _1N1R129(f,o,a,...) f(o,a) _1N1R128(f,o,__VA_ARGS__)
#define _1N1R130(f,o,a,...) f(o,a) _1N1R129(f,o,__VA_ARGS__)
#define _1N1R131(f,o,a,...) f(o,a) _1N1R130(f,o,__VA_ARGS__)
#define _1N1R132(f,o,a,...) f(o,a) _1N1R131(f,o,__VA_ARGS__)
#define _1N1R133(f,o,a,...) f(o,a) _1N1R132(f,o,__VA_ARGS__)
#define _1N1R134(f,o,a,...) f(o,a) _1N1R133(f,o,__VA_ARGS__)
#define _1N1R135(f,o,a,...) f(o,a) _1N1R134(f,o,__VA_ARGS__)
#define _1N1R136(f,o,a,...) f(o,a) _1N1R135(f,o,__VA_ARGS__)
#define _1N1R137(f,o,a,...) f(o,a) _1N1R136(f,o,__VA_ARGS__)
#define _1N1R138(f,o,a,...) f(o,a) _1N1R137(f,o,__VA_ARGS__)
#define _1N1R139(f,o,a,...) f(o,a) _1N1R138(f,o,__VA_ARGS__)
#define _1N1R140(f,o,a,...) f(o,a) _1N1R139(f,o,__VA_ARGS__)
#define _1N1R141(f,o,a,...) f(o,a) _1N1R140(f,o,__VA_ARGS__)
#define _1N1R142(f,o,a,...) f(o,a) _1N1R141(f,o,__VA_ARGS__)
#define _1N1R143(f,o,a,...) f(o,a) _1N1R142(f,o,__VA_ARGS__)
#define _1N1R144(f,o,a,...) f(o,a) _1N1R143(f,o,__VA_ARGS__)
#define _1N1R145(f,o,a,...) f(o,a) _1N1R144(f,o,__VA_ARGS__)
#define _1N1R146(f,o,a,...) f(o,a) _1N1R145(f,o,__VA_ARGS__)
#define _1N1R147(f,o,a,...) f(o,a) _1N1R146(f,o,__VA_ARGS__)
#define _1N1R148(f,o,a,...) f(o,a) _1N1R147(f,o,__VA_ARGS__)
#define _1N1R149(f,o,a,...) f(o,a) _1N1R148(f,o,__VA_ARGS__)
#define _1N1R150(f,o,a,...) f(o,a) _1N1R149(f,o,__VA_ARGS__)
#define _1N1R151(f,o,a,...) f(o,a) _1N1R150(f,o,__VA_ARGS__)
#define _1N1R152(f,o,a,...) f(o,a) _1N1R151(f,o,__VA_ARGS__)
#define _1N1R153(f,o,a,...) f(o,a) _1N1R152(f,o,__VA_ARGS__)
#define _1N1R154(f,o,a,...) f(o,a) _1N1R153(f,o,__VA_ARGS__)
#define _1N1R155(f,o,a,...) f(o,a) _1N1R154(f,o,__VA_ARGS__)
#define _1N1R156(f,o,a,...) f(o,a) _1N1R155(f,o,__VA_ARGS__)
#define _1N1R157(f,o,a,...) f(o,a) _1N1R156(f,o,__VA_ARGS__)
#define _1N1R158(f,o,a,...) f(o,a) _1N1R157(f,o,__VA_ARGS__)
#define _1N1R159(f,o,a,...) f(o,a) _1N1R158(f,o,__VA_ARGS__)
#define _1N1R160(f,o,a,...) f(o,a) _1N1R159(f,o,__VA_ARGS__)
#define _1N1R161(f,o,a,...) f(o,a) _1N1R160(f,o,__VA_ARGS__)
#define _1N1R162(f,o,a,...) f(o,a) _1N1R161(f,o,__VA_ARGS__)
#define _1N1R163(f,o,a,...) f(o,a) _1N1R162(f,o,__VA_ARGS__)
#define _1N1R164(f,o,a,...) f(o,a) _1N1R163(f,o,__VA_ARGS__)
#define _1N1R165(f,o,a,...) f(o,a) _1N1R164(f,o,__VA_ARGS__)
#define _1N1R166(f,o,a,...) f(o,a) _1N1R165(f,o,__VA_ARGS__)
#define _1N1R167(f,o,a,...) f(o,a) _1N1R166(f,o,__VA_ARGS__)
#define _1N1R168(f,o,a,...) f(o,a) _1N1R167(f,o,__VA_ARGS__)
#define _1N1R169(f,o,a,...) f(o,a) _1N1R168(f,o,__VA_ARGS__)
#define _1N1R170(f,o,a,...) f(o,a) _1N1R169(f,o,__VA_ARGS__)
#define _1N1R171(f,o,a,...) f(o,a) _1N1R170(f,o,__VA_ARGS__)
#define _1N1R172(f,o,a,...) f(o,a) _1N1R171(f,o,__VA_ARGS__)
#define _1N1R173(f,o,a,...) f(o,a) _1N1R172(f,o,__VA_ARGS__)
#define _1N1R174(f,o,a,...) f(o,a) _1N1R173(f,o,__VA_ARGS__)
#define _1N1R175(f,o,a,...) f(o,a) _1N1R174(f,o,__VA_ARGS__)
#define _1N1R176(f,o,a,...) f(o,a) _1N1R175(f,o,__VA_ARGS__)
#define _1N1R177(f,o,a,...) f(o,a) _1N1R176(f,o,__VA_ARGS__)
#define _1N1R178(f,o,a,...) f(o,a) _1N1R177(f,o,__VA_ARGS__)
#define _1N1R179(f,o,a,...) f(o,a) _1N1R178(f,o,__VA_ARGS__)
#define _1N1R180(f,o,a,...) f(o,a) _1N1R179(f,o,__VA_ARGS__)
#define _1N1R181(f,o,a,...) f(o,a) _1N1R180(f,o,__VA_ARGS__)
#define _1N1R182(f,o,a,...) f(o,a) _1N1R181(f,o,__VA_ARGS__)
#define _1N1R183(f,o,a,...) f(o,a) _1N1R182(f,o,__VA_ARGS__)
#define _1N1R184(f,o,a,...) f(o,a) _1N1R183(f,o,__VA_ARGS__)
#define _1N1R185(f,o,a,...) f(o,a) _1N1R184(f,o,__VA_ARGS__)
#define _1N1R186(f,o,a,...) f(o,a) _1N1R185(f,o,__VA_ARGS__)
#define _1N1R187(f,o,a,...) f(o,a) _1N1R186(f,o,__VA_ARGS__)
#define _1N1R188(f,o,a,...) f(o,a) _1N1R187(f,o,__VA_ARGS__)
#define _1N1R189(f,o,a,...) f(o,a) _1N1R188(f,o,__VA_ARGS__)
#define _1N1R190(f,o,a,...) f(o,a) _1N1R189(f,o,__VA_ARGS__)
#define _1N1R191(f,o,a,...) f(o,a) _1N1R190(f,o,__VA_ARGS__)
#define _1N1R192(f,o,a,...) f(o,a) _1N1R191(f,o,__VA_ARGS__)
#define _1N1R193(f,o,a,...) f(o,a) _1N1R192(f,o,__VA_ARGS__)
#define _1N1R194(f,o,a,...) f(o,a) _1N1R193(f,o,__VA_ARGS__)
#define _1N1R195(f,o,a,...) f(o,a) _1N1R194(f,o,__VA_ARGS__)
#define _1N1R196(f,o,a,...) f(o,a) _1N1R195(f,o,__VA_ARGS__)
#define _1N1R197(f,o,a,...) f(o,a) _1N1R196(f,o,__VA_ARGS__)
#define _1N1R198(f,o,a,...) f(o,a) _1N1R197(f,o,__VA_ARGS__)
#define _1N1R199(f,o,a,...) f(o,a) _1N1R198(f,o,__VA_ARGS__)
#define _1N1R200(f,o,a,...) f(o,a) _1N1R199(f,o,__VA_ARGS__)
#define _1N1R201(f,o,a,...) f(o,a) _1N1R200(f,o,__VA_ARGS__)
#define _1N1R202(f,o,a,...) f(o,a) _1N1R201(f,o,__VA_ARGS__)
#define _1N1R203(f,o,a,...) f(o,a) _1N1R202(f,o,__VA_ARGS__)
#define _1N1R204(f,o,a,...) f(o,a) _1N1R203(f,o,__VA_ARGS__)
#define _1N1R205(f,o,a,...) f(o,a) _1N1R204(f,o,__VA_ARGS__)
#define _1N1R206(f,o,a,...) f(o,a) _1N1R205(f,o,__VA_ARGS__)
#define _1N1R207(f,o,a,...) f(o,a) _1N1R206(f,o,__VA_ARGS__)
#define _1N1R208(f,o,a,...) f(o,a) _1N1R207(f,o,__VA_ARGS__)
#define _1N1R209(f,o,a,...) f(o,a) _1N1R208(f,o,__VA_ARGS__)
#define _1N1R210(f,o,a,...) f(o,a) _1N1R209(f,o,__VA_ARGS__)
#define _1N1R211(f,o,a,...) f(o,a) _1N1R210(f,o,__VA_ARGS__)
#define _1N1R212(f,o,a,...) f(o,a) _1N1R211(f,o,__VA_ARGS__)
#define _1N1R213(f,o,a,...) f(o,a) _1N1R212(f,o,__VA_ARGS__)
#define _1N1R214(f,o,a,...) f(o,a) _1N1R213(f,o,__VA_ARGS__)
#define _1N1R215(f,o,a,...) f(o,a) _1N1R214(f,o,__VA_ARGS__)
#define _1N1R216(f,o,a,...) f(o,a) _1N1R215(f,o,__VA_ARGS__)
#define _1N1R217(f,o,a,...) f(o,a) _1N1R216(f,o,__VA_ARGS__)
#define _1N1R218(f,o,a,...) f(o,a) _1N1R217(f,o,__VA_ARGS__)
#define _1N1R219(f,o,a,...) f(o,a) _1N1R218(f,o,__VA_ARGS__)
#define _1N1R220(f,o,a,...) f(o,a) _1N1R219(f,o,__VA_ARGS__)
#define _1N1R221(f,o,a,...) f(o,a) _1N1R220(f,o,__VA_ARGS__)
#define _1N1R222(f,o,a,...) f(o,a) _1N1R221(f,o,__VA_ARGS__)
#define _1N1R223(f,o,a,...) f(o,a) _1N1R222(f,o,__VA_ARGS__)
#define _1N1R224(f,o,a,...) f(o,a) _1N1R223(f,o,__VA_ARGS__)
#define _1N1R225(f,o,a,...) f(o,a) _1N1R224(f,o,__VA_ARGS__)
#define _1N1R226(f,o,a,...) f(o,a) _1N1R225(f,o,__VA_ARGS__)
#define _1N1R227(f,o,a,...) f(o,a) _1N1R226(f,o,__VA_ARGS__)
#define _1N1R228(f,o,a,...) f(o,a) _1N1R227(f,o,__VA_ARGS__)
#define _1N1R229(f,o,a,...) f(o,a) _1N1R228(f,o,__VA_ARGS__)
#define _1N1R230(f,o,a,...) f(o,a) _1N1R229(f,o,__VA_ARGS__)
#define _1N1R231(f,o,a,...) f(o,a) _1N1R230(f,o,__VA_ARGS__)
#define _1N1R232(f,o,a,...) f(o,a) _1N1R231(f,o,__VA_ARGS__)
#define _1N1R233(f,o,a,...) f(o,a) _1N1R232(f,o,__VA_ARGS__)
#define _1N1R234(f,o,a,...) f(o,a) _1N1R233(f,o,__VA_ARGS__)
#define _1N1R235(f,o,a,...) f(o,a) _1N1R234(f,o,__VA_ARGS__)
#define _1N1R236(f,o,a,...) f(o,a) _1N1R235(f,o,__VA_ARGS__)
#define _1N1R237(f,o,a,...) f(o,a) _1N1R236(f,o,__VA_ARGS__)
#define _1N1R238(f,o,a,...) f(o,a) _1N1R237(f,o,__VA_ARGS__)
#define _1N1R239(f,o,a,...) f(o,a) _1N1R238(f,o,__VA_ARGS__)
#define _1N1R240(f,o,a,...) f(o,a) _1N1R239(f,o,__VA_ARGS__)
#define _1N1R241(f,o,a,...) f(o,a) _1N1R240(f,o,__VA_ARGS__)
#define _1N1R242(f,o,a,...) f(o,a) _1N1R241(f,o,__VA_ARGS__)
#define _1N1R243(f,o,a,...) f(o,a) _1N1R242(f,o,__VA_ARGS__)
#define _1N1R244(f,o,a,...) f(o,a) _1N1R243(f,o,__VA_ARGS__)
#define _1N1R245(f,o,a,...) f(o,a) _1N1R244(f,o,__VA_ARGS__)
#define _1N1R246(f,o,a,...) f(o,a) _1N1R245(f,o,__VA_ARGS__)
#define _1N1R247(f,o,a,...) f(o,a) _1N1R246(f,o,__VA_ARGS__)
#define _1N1R248(f,o,a,...) f(o,a) _1N1R247(f,o,__VA_ARGS__)
#define _1N1R249(f,o,a,...) f(o,a) _1N1R248(f,o,__VA_ARGS__)
#define _1N1R250(f,o,a,...) f(o,a) _1N1R249(f,o,__VA_ARGS__)
#define _1N1R251(f,o,a,...) f(o,a) _1N1R250(f,o,__VA_ARGS__)
#define _1N1R252(f,o,a,...) f(o,a) _1N1R251(f,o,__VA_ARGS__)
#define _1N1R253(f,o,a,...) f(o,a) _1N1R252(f,o,__VA_ARGS__)
#define _1N1R254(f,o,a,...) f(o,a) _1N1R253(f,o,__VA_ARGS__)
#define _1N1R255(f,o,a,...) f(o,a) _1N1R254(f,o,__VA_ARGS__)
#define _1N1R256(f,o,a,...) f(o,a) _1N1R255(f,o,__VA_ARGS__)

#define _1N2R0(...)
#define _1N2R1(f,o,a,...) f(o,a) _1N2R0(f,o,__VA_ARGS__)
#define _1N2R2(f,o,a,...) f(o,a) _1N2R1(f,o,__VA_ARGS__)
#define _1N2R3(f,o,a,...) f(o,a) _1N2R2(f,o,__VA_ARGS__)
#define _1N2R4(f,o,a,...) f(o,a) _1N2R3(f,o,__VA_ARGS__)
#define _1N2R5(f,o,a,...) f(o,a) _1N2R4(f,o,__VA_ARGS__)
#define _1N2R6(f,o,a,...) f(o,a) _1N2R5(f,o,__VA_ARGS__)
#define _1N2R7(f,o,a,...) f(o,a) _1N2R6(f,o,__VA_ARGS__)
#define _1N2R8(f,o,a,...) f(o,a) _1N2R7(f,o,__VA_ARGS__)
#define _1N2R9(f,o,a,...) f(o,a) _1N2R8(f,o,__VA_ARGS__)
#define _1N2R10(f,o,a,...) f(o,a) _1N2R9(f,o,__VA_ARGS__)
#define _1N2R11(f,o,a,...) f(o,a) _1N2R10(f,o,__VA_ARGS__)
#define _1N2R12(f,o,a,...) f(o,a) _1N2R11(f,o,__VA_ARGS__)
#define _1N2R13(f,o,a,...) f(o,a) _1N2R12(f,o,__VA_ARGS__)
#define _1N2R14(f,o,a,...) f(o,a) _1N2R13(f,o,__VA_ARGS__)
#define _1N2R15(f,o,a,...) f(o,a) _1N2R14(f,o,__VA_ARGS__)
#define _1N2R16(f,o,a,...) f(o,a) _1N2R15(f,o,__VA_ARGS__)
#define _1N2R17(f,o,a,...) f(o,a) _1N2R16(f,o,__VA_ARGS__)
#define _1N2R18(f,o,a,...) f(o,a) _1N2R17(f,o,__VA_ARGS__)
#define _1N2R19(f,o,a,...) f(o,a) _1N2R18(f,o,__VA_ARGS__)
#define _1N2R20(f,o,a,...) f(o,a) _1N2R19(f,o,__VA_ARGS__)
#define _1N2R21(f,o,a,...) f(o,a) _1N2R20(f,o,__VA_ARGS__)
#define _1N2R22(f,o,a,...) f(o,a) _1N2R21(f,o,__VA_ARGS__)
#define _1N2R23(f,o,a,...) f(o,a) _1N2R22(f,o,__VA_ARGS__)
#define _1N2R24(f,o,a,...) f(o,a) _1N2R23(f,o,__VA_ARGS__)
#define _1N2R25(f,o,a,...) f(o,a) _1N2R24(f,o,__VA_ARGS__)
#define _1N2R26(f,o,a,...) f(o,a) _1N2R25(f,o,__VA_ARGS__)
#define _1N2R27(f,o,a,...) f(o,a) _1N2R26(f,o,__VA_ARGS__)
#define _1N2R28(f,o,a,...) f(o,a) _1N2R27(f,o,__VA_ARGS__)
#define _1N2R29(f,o,a,...) f(o,a) _1N2R28(f,o,__VA_ARGS__)
#define _1N2R30(f,o,a,...) f(o,a) _1N2R29(f,o,__VA_ARGS__)
#define _1N2R31(f,o,a,...) f(o,a) _1N2R30(f,o,__VA_ARGS__)
#define _1N2R32(f,o,a,...) f(o,a) _1N2R31(f,o,__VA_ARGS__)
#define _1N2R33(f,o,a,...) f(o,a) _1N2R32(f,o,__VA_ARGS__)
#define _1N2R34(f,o,a,...) f(o,a) _1N2R33(f,o,__VA_ARGS__)
#define _1N2R35(f,o,a,...) f(o,a) _1N2R34(f,o,__VA_ARGS__)
#define _1N2R36(f,o,a,...) f(o,a) _1N2R35(f,o,__VA_ARGS__)
#define _1N2R37(f,o,a,...) f(o,a) _1N2R36(f,o,__VA_ARGS__)
#define _1N2R38(f,o,a,...) f(o,a) _1N2R37(f,o,__VA_ARGS__)
#define _1N2R39(f,o,a,...) f(o,a) _1N2R38(f,o,__VA_ARGS__)
#define _1N2R40(f,o,a,...) f(o,a) _1N2R39(f,o,__VA_ARGS__)
#define _1N2R41(f,o,a,...) f(o,a) _1N2R40(f,o,__VA_ARGS__)
#define _1N2R42(f,o,a,...) f(o,a) _1N2R41(f,o,__VA_ARGS__)
#define _1N2R43(f,o,a,...) f(o,a) _1N2R42(f,o,__VA_ARGS__)
#define _1N2R44(f,o,a,...) f(o,a) _1N2R43(f,o,__VA_ARGS__)
#define _1N2R45(f,o,a,...) f(o,a) _1N2R44(f,o,__VA_ARGS__)
#define _1N2R46(f,o,a,...) f(o,a) _1N2R45(f,o,__VA_ARGS__)
#define _1N2R47(f,o,a,...) f(o,a) _1N2R46(f,o,__VA_ARGS__)
#define _1N2R48(f,o,a,...) f(o,a) _1N2R47(f,o,__VA_ARGS__)
#define _1N2R49(f,o,a,...) f(o,a) _1N2R48(f,o,__VA_ARGS__)
#define _1N2R50(f,o,a,...) f(o,a) _1N2R49(f,o,__VA_ARGS__)
#define _1N2R51(f,o,a,...) f(o,a) _1N2R50(f,o,__VA_ARGS__)
#define _1N2R52(f,o,a,...) f(o,a) _1N2R51(f,o,__VA_ARGS__)
#define _1N2R53(f,o,a,...) f(o,a) _1N2R52(f,o,__VA_ARGS__)
#define _1N2R54(f,o,a,...) f(o,a) _1N2R53(f,o,__VA_ARGS__)
#define _1N2R55(f,o,a,...) f(o,a) _1N2R54(f,o,__VA_ARGS__)
#define _1N2R56(f,o,a,...) f(o,a) _1N2R55(f,o,__VA_ARGS__)
#define _1N2R57(f,o,a,...) f(o,a) _1N2R56(f,o,__VA_ARGS__)
#define _1N2R58(f,o,a,...) f(o,a) _1N2R57(f,o,__VA_ARGS__)
#define _1N2R59(f,o,a,...) f(o,a) _1N2R58(f,o,__VA_ARGS__)
#define _1N2R60(f,o,a,...) f(o,a) _1N2R59(f,o,__VA_ARGS__)
#define _1N2R61(f,o,a,...) f(o,a) _1N2R60(f,o,__VA_ARGS__)
#define _1N2R62(f,o,a,...) f(o,a) _1N2R61(f,o,__VA_ARGS__)
#define _1N2R63(f,o,a,...) f(o,a) _1N2R62(f,o,__VA_ARGS__)
#define _1N2R64(f,o,a,...) f(o,a) _1N2R63(f,o,__VA_ARGS__)


#endif
