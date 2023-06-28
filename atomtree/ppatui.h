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

#ifndef PPATUI_H
#define PPATUI_H


// to create the allocator function. See atui.c for how it is used.             
#define PPATUI_FUNCIFY(typeprefix, typesuffix, ...) \
    PPATUI_FUNCIFY_HELPER(typeprefix, typesuffix __VA_OPT__(,) __VA_ARGS__)

// to define the header entries for the aformentioned allocator functions.
#define PPATUI_HEADERIFY(typeprefix, typesuffix) _PPATUI_FUNC_NAME(typeprefix, typesuffix)

// to define an array of string-val pairs of an enum.
#define PPATUI_ENUMER(name, ...) \
	const struct atui_enum _atui_enum_##name[] = \
		{_PPATUI_ENUM_ENTRIES(__VA_ARGS__)};
#define _PPATUI_EENTRY(o,estate) {.name=#estate, .val=estate}, 

/***************************** preprocessor hell *****************************/

#define _PPATUI_LEAF_BITNESS(var) _Generic((var), \
	uint8_t*:8, uint16_t*:16, uint32_t*:32, uint64_t*:64, \
	uint8_t:8, uint16_t:16, uint32_t:32, uint64_t:64, \
	default:0\
)


/**** LEAF FANCY FUNCS ***/
/*
The fancy funcions here are about populating the fancy UI representation flags
for the leaves described in PPATUI_FUNCIFY().
That is, bitfield population, and enum and inline association.
*/


// common guts and functions for Fancy. 
#define _PPATUI_FANCY_NOBITFIELD(biosvar) \
	.num_bitfield_children=0, \
	.bitfield_hi=_PPATUI_LEAF_BITNESS(biosvar)-1, .bitfield_lo=0,
#define _PPATUI_FANCY_NOBITFIELD_HARD \
	.num_bitfield_children=0, .bitfield_hi=0, .bitfield_lo=0,

#define _PPATUI_FANCY_NOENUM .enum_options=NULL, .num_enum_opts=0,
#define _PPATUI_FANCY_NOARRAY .array_size=0,

//fancydata is textually packed in () and this unpacks it
#define _PPATUI_FANCYDATA_UNPACK(todepack) _PPATUI_FANCYDATA_UNPACK2 todepack
#define _PPATUI_FANCYDATA_UNPACK2(...) __VA_ARGS__

#define _PPATUI_FANCY_INIT(bios, var, radix, fancytype) \
	{ \
		.name=#var, .type=(radix | fancytype), .auxiliary=NULL, \
		.val=&(bios->var), .total_bits=_PPATUI_LEAF_BITNESS(bios->var),
// Fancy common end


//ATUI_NONE

#define _PPATUI_FANCY_ATUI_NONE(bios, var, radix, fancytype, fancydata) \
	_PPATUI_FANCY_INIT(bios, var, radix, fancytype) \
	_PPATUI_FANCY_NOBITFIELD(bios->var) _PPATUI_FANCY_NOENUM },




//ATUI_ENUM

#define _PPATUI_FANCY_ATUI_ENUM(bios, var, radix, fancytype, enumname) \
	_PPATUI_FANCY_INIT(bios, var, radix, fancytype) \
	.enum_options=_atui_enum_##enumname, \
	.num_enum_opts=sizeof(_atui_enum_##enumname)/sizeof(struct atui_enum), \
	_PPATUI_FANCY_NOBITFIELD(bios->var) },





//ATUI_STRING
//ATUI_ARRAY

#define _PPATUI_FANCY_ATUI_STRING(bios, var, radix, fancytype, fancydata) \
	_PPATUI_FANCY_ATUI_ARRAY(bios, var, radix, fancytype, fancydata) 

#define _PPATUI_FANCY_ATUI_ARRAY(bios, var, radix, fancytype, fancydata) \
	_PPATUI_FANCY_INIT(bios, var, radix, fancytype) \
	.array_size = sizeof(bios->var)/sizeof(bios->var[0]), \
	_PPATUI_FANCY_NOBITFIELD(bios->var) _PPATUI_FANCY_NOENUM },



	


//ATUI_BITFIELD

#define _PPATUI_FANCY_ATUI_BITFIELD(bios, var, radix, fancytype, fancydata) \
	_PPATUI_FANCY_INIT(bios, var, radix, fancytype) \
	.bitfield_hi=_PPATUI_LEAF_BITNESS(bios->var)-1, .bitfield_lo=0, \
	.num_bitfield_children=_PPATUI_FANCYBF_NUMCHILDREN fancydata , \
	_PPATUI_FANCY_NOARRAY  _PPATUI_FANCY_NOENUM }, \
	_PPATUI_BITFIELD_LEAVES(bios->var, _PPATUI_FANCYDATA_UNPACK(fancydata))
// close parent and start on inbred children.

// the 4 is for name,bithi,bitlo,radix set
#define _PPATUI_FANCYBF_NUMCHILDREN(...) \
	 _PP_NUMARG(__VA_ARGS__) / 4

#define _PPA_BFLEAF(biosvar, bfname, bit_end, bit_start, radix) \
	{\
		.val=&(biosvar), .name=#bfname, \
		.type=radix, \
		.total_bits=_PPATUI_LEAF_BITNESS(biosvar), \
		.bitfield_hi=bit_end, .bitfield_lo=bit_start, \
		_PPATUI_FANCY_NOENUM .num_bitfield_children=0, \
		_PPATUI_FANCY_NOARRAY .auxiliary = NULL, \
	},





//ATUI_INLINE

// the meat of ATUI_INLINE is handled in the funcify
#define _PPATUI_FANCY_ATUI_INLINE(bios, var, radix, fancytype, fancydata)\
	_PPATUI_FANCY_INIT(bios, var, radix, fancytype) \
	.val=NULL, \
	_PPATUI_FANCY_NOENUM _PPATUI_FANCY_NOBITFIELD_HARD \
	_PPATUI_FANCY_NOARRAY },

#define _PPATUI_INLEAF_ATUI_NONE(...)
#define _PPATUI_INLEAF_ATUI_BITFIELD(...)
#define _PPATUI_INLEAF_ATUI_ENUM(...)
#define _PPATUI_INLEAF_ATUI_STRING(...)
#define _PPATUI_INLEAF_ATUI_ARRAY(...)
#define _PPATUI_INLEAF_ATUI_DYNARRAY(...)

#define _PPATUI_INLEAF_ATUI_INLINE(typesuffix, instancename)\
	ATUI_MAKE_BRANCH(typesuffix, &(bios->instancename), 0, NULL),
#define _PPATUI_INLEAF(m, var, radix, fancytype, fancydata) \
	_PPATUI_INLEAF_##fancytype(fancydata, var)




// ATUI_DYNARRAY
#define _PPATUI_FANCY_ATUI_DYNARRAY(bios, var, radix, fancytype, fancydata)


/**** LEAF FANCY FUNCS END***/


#define _PPATUI_LEAF(bios, var, radix, fancytype, fancydata) \
	_PPATUI_FANCY_##fancytype(bios, var, radix, fancytype, fancydata)
	// the closing } for the leaf is handled in the fancy pp funcs.



#define _PPATUI_FUNC_NAME(typeprefix, typesuffix) \
	atui_branch* _##typesuffix##_atui( \
		typeprefix typesuffix * bios, \
		unsigned int num_branches, \
		atui_branch** import_children \
	)

#define ATUI_MAKE_BRANCH(typesuffix, bios, num_branches, children) \
	_##typesuffix##_atui(bios, num_branches, children)

// main allocator function
#define PPATUI_FUNCIFY_HELPER(typeprefix, typesuffix, ...) \
_PPATUI_FUNC_NAME(typeprefix, typesuffix) {\
	atui_branch* table = NULL; \
	atui_branch** branches = NULL;\
\
	atui_branch** inliners = NULL;\
	uint16_t num_inliners;\
\
	atui_leaf* leaves = NULL;\
	uint16_t leaves_init_num = 0;\
\
	void* scratch;\
	uint16_t i = 0;\
	uint16_t j = 0;\
	uint16_t k = 0;\
	uint16_t l = 0;\
\
\
	if(PPATUI_NUM_LEAVES(__VA_ARGS__)) {\
		/*counts bitfield*/ \
		const atui_leaf leaves_init[] = { _PPATUI_LEAVES(bios, __VA_ARGS__) };\
		leaves_init_num = sizeof(leaves_init)/sizeof(atui_leaf);\
\
		const atui_branch* inliners_init[] = { \
			_PPATUI_INLINE_BRANCHES(__VA_ARGS__) \
		};\
		num_inliners = sizeof(inliners_init)/sizeof(atui_branch*);\
\
		const atui_leaf dynarray_patterns[] = { \
			_PPATUI_DYNARRAY(ROLL, bios, __VA_ARGS__) \
		};\
		const uint8_t dynarray_pattern_lengths[] = { \
			_PPATUI_DYNARRAY(COUNT, bios, __VA_ARGS__) \
		};\
\
\
		scratch = malloc(\
			sizeof(atui_branch) + \
			(sizeof(atui_branch*) *  num_branches) + \
			sizeof(inliners_init) + \
			sizeof(leaves_init) \
		);\
		table = scratch;\
		scratch = scratch + sizeof(atui_branch);\
		leaves = scratch + num_branches*sizeof(atui_branch*) +\
			sizeof(inliners_init);\
\
\
		j=0; k=0; l=0;\
		for(i=0; i < leaves_init_num; i++) {\
			if (leaves_init[i].type & ATUI_DYNARRAY) {\
				 /*for(k=0; k < */ \
			} else {\
				leaves[j] = leaves_init[i];\
				j++;\
			}\
		}\
\
		if (sizeof(inliners_init)) {\
			inliners = scratch + num_branches*sizeof(atui_branch*);\
			for(i=0; i<num_inliners; i++) {\
				inliners[i] = (atui_branch*) inliners_init[i];\
			}\
			j=0;\
			for(i=0; i<leaves_init_num; i++) {\
				if (leaves[i].type & ATUI_INLINE) {\
					leaves[i].inline_branch = &(inliners[j]);\
					j++;\
				}\
			}\
		}\
\
	} else {\
		scratch = malloc(\
			sizeof(atui_branch) + \
			(sizeof(atui_branch*) * num_branches) \
		); \
		table = scratch;\
		scratch = scratch + sizeof(atui_branch);\
	}\
\
	if (num_branches) {\
		branches = scratch;\
		if (import_children != NULL) {\
			for (i=0; i<num_branches; i++) {\
				branches[i] = import_children[i];\
			}\
		}\
	}\
\
	*table = (atui_branch) {\
		.name=#typesuffix, .leaves=(atui_leaf*)leaves, \
		.leaf_count=leaves_init_num, .atomleaves=bios, \
		.child_branches=branches, .branch_count=num_branches, \
		.inline_branches=inliners, .inline_branch_count=num_inliners, \
		.max_branch_count=num_branches, .max_inline_branch_count=num_inliners, \
	};\
	return table;\
}





#define PPATUI_NUM_LEAVES(...) _PP_NUMARG(__VA_ARGS__)/4




#define _PPATUI_DYNAR_SERVICE(jobbios, var, radix, fancytype, fancydata)\
	_PPATUI_DYNAR_SVCHELPER1(_PPATUI_DYNDA_JB_UNPACK jobbios, \
		var, radix, fancytype, fancydata)
#define _PPATUI_DYNDA_JB_UNPACK(job, bios) job, bios
#define _PPATUI_DYNAR_SVCHELPER1(...) _PPATUI_DYNAR_SVCHELPER2(__VA_ARGS__)
#define _PPATUI_DYNAR_SVCHELPER2(job, bios, var, radix, ftype, fdata) \
	_PPATUI_DYNAR_SVCHELPER3_##ftype(job, bios, var, radix, ftype, fdata)

#define _PPATUI_DYNAR_SVCHELPER3_ATUI_NONE(...)
#define _PPATUI_DYNAR_SVCHELPER3_ATUI_BITFIELD(...)
#define _PPATUI_DYNAR_SVCHELPER3_ATUI_ENUM(...)
#define _PPATUI_DYNAR_SVCHELPER3_ATUI_INLINE(...)
#define _PPATUI_DYNAR_SVCHELPER3_ATUI_ARRAY(...)
#define _PPATUI_DYNAR_SVCHELPER3_ATUI_STRING(...)
#define _PPATUI_DYNAR_SVCHELPER3_ATUI_DYNARRAY(\
		job, bios,var,radix,fancytype,fancydata)\
	_PPATUI_DYNAR_SVCHELPER4(job, bios, _PPATUI_DYNARR_UNPACK fancydata)

//unpack ATUI_DYNARRY's fancydata
#define _PPATUI_DYNARR_UNPACK(\
		pattern_var,pattern_radix,pattern_fancytype,pattern_fancydata,\
		start_pointer, count_var) \
	pattern_var, pattern_radix, pattern_fancytype, pattern_fancydata, \
	start_pointer, count_var

#define _PPATUI_DYNAR_SVCHELPER4(job, ...) \
	_PPATUI_DYNAR_SVCHELPER5_##job(__VA_ARGS__)

//unrolls the pattern into leaves to copy.
//var..fdat is for the pattern
//TODO: use start instead of bios
#define _PPATUI_DYNAR_SVCHELPER5_ROLL(\
		bios, var,radix,fancytype,fancydata, start,count)\
	_PPATUI_LEAF(bios,var,radix,fancytype,fancydata)


// counts the ATUI_DYNARRAY's pattern leaf count. Mainly for bitfields
#define _PPATUI_DYNAR_SVCHELPER5_COUNT(\
		bios,var,radix,fancytype,fancydata, start,count)\
	_PPATUI_DYNAR_SVCHELPER6_COUNT_##fancytype(\
		bios,var,radix,fancytype,fancydata)  ,

#define _PPATUI_DYNAR_SVCHELPER6_COUNT_ATUI_NONE(...) 1
#define _PPATUI_DYNAR_SVCHELPER6_COUNT_ATUI_ENUM(...) 1
#define _PPATUI_DYNAR_SVCHELPER6_COUNT_ATUI_INLINE(...) 1
#define _PPATUI_DYNAR_SVCHELPER6_COUNT_ATUI_ARRAY(...) 1
#define _PPATUI_DYNAR_SVCHELPER6_COUNT_ATUI_STRING(...) 1
#define _PPATUI_DYNAR_SVCHELPER6_COUNT_ATUI_DYNARRAY(...) 1
#define _PPATUI_DYNAR_SVCHELPER6_COUNT_ATUI_BITFIELD(b,v,r,ft, fancydata)\
	_PPATUI_LOOPER(_PPATUI_DYNAR_SVCHELPER7_COUNTER ,, 4, \
		_PPATUI_FANCYDATA_UNPACK fancydata)
#define _PPATUI_DYNAR_SVCHELPER7_COUNTER(...) 1,



#define _PPATUI_LEAVES(bios, ...)\
	_PPATUI_LOOPER(4,1,__VA_ARGS__)\
		(_PPATUI_LEAF, bios, __VA_ARGS__)

#define _PPATUI_BITFIELD_LEAVES(parent_var, ...)\
	_PPATUI_LOOPER(4,2,__VA_ARGS__)\
		(_PPA_BFLEAF, parent_var, __VA_ARGS__)

#define _PPATUI_INLINE_BRANCHES(...)\
	_ppaTUI_LOOPER(4,1,__VA_ARGS__)\
		(_PPATUI_INLEAF ,, __VA_ARGS__)

#define _PPATUI_DYNARRAY(job, bios, ...)\
	_PPATUI_LOOPER(4,1,__VA_ARGS__)\
		(_PPATUI_DYNAR_SERVICE, (job,bios), __VA_ARGS__)


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

#define _PP_ARGCOUNTER_DEPTHCAN( \
_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63,_64,_65,_66,_67,_68,_69,_70,_71,_72,_73,_74,_75,_76,_77,_78,_79,_80,_81,_82,_83,_84,_85,_86,_87,_88,_89,_90,_91,_92,_93,_94,_95,_96,_97,_98,_99,_100,_101,_102,_103,_104,_105,_106,_107,_108,_109,_110,_111,_112,_113,_114,_115,_116,_117,_118,_119,_120,_121,_122,_123,_124,_125,_126,_127,_128,_129,_130,_131,_132,_133,_134,_135,_136,_137,_138,_139,_140,_141,_142,_143,_144,_145,_146,_147,_148,_149,_150,_151,_152,_153,_154,_155,_156,_157,_158,_159,_160,_161,_162,_163,_164,_165,_166,_167,_168,_169,_170,_171,_172,_173,_174,_175,_176,_177,_178,_179,_180,_181,_182,_183,_184,_185,_186,_187,_188,_189,_190,_191,_192,_193,_194,_195,_196,_197,_198,_199,_200,_201,_202,_203,_204,_205,_206,_207,_208,_209,_210,_211,_212,_213,_214,_215,_216,_217,_218,_219,_220,_221,_222,_223,_224,_225,_226,_227,_228,_229,_230,_231,_232,_233,_234,_235,_236,_237,_238,_239,_240,_241,_242,_243,_244,_245,_246,_247,_248,_249,_250,_251,_252,_253,_254,_255,N,...) N

#define _PP_ARGCOUNTER_DEPTHCAN_HELPER(...) _PP_ARGCOUNTER_DEPTHCAN(__VA_ARGS__)
#define _PP_NUMARG(...) \
_PP_ARGCOUNTER_DEPTHCAN_HELPER(__VA_ARGS__ __VA_OPT__(,) _PP_ARGCOUNTER_RULER)




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


generic waterfall loop for functions with 4 unique arguments and 1 common.

The recurse/recusive depth is about the preprocessor "painting blue". That is, 
after the waterfall loop has been used, it becomes undefined within that 
recursion.
In other words, if the f() needs to call a loop, the loop that spun out the 
f() f() f() f()... is no longer usable; the f() needs to call a different
waterfall.
*/

#define _PPATUI_LOOPER(numargs, recurse, ...) \
	_PPATUI_LOOPERH1(numargs, recurse, _PP_NUMARG(__VA_ARGS__))
#define _PPATUI_LOOPERH1(...) _PPATUI_LOOPERH2(__VA_ARGS__)
#define _PPATUI_LOOPERH2(n,r,d) _##n##N##r##R##d

//#define _4N1R0_FLAG // to detect if it's "painted blue"
//#define _4N1R0(...) _4N1R0_FLAG 
#define _4N1R0(...)
#define _4N1R4(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R0(f,o,__VA_ARGS__)
#define _4N1R8(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R4(f,o,__VA_ARGS__)
#define _4N1R12(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R8(f,o,__VA_ARGS__)
#define _4N1R16(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R12(f,o,__VA_ARGS__)
#define _4N1R20(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R16(f,o,__VA_ARGS__)
#define _4N1R24(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R20(f,o,__VA_ARGS__)
#define _4N1R28(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R24(f,o,__VA_ARGS__)
#define _4N1R32(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R28(f,o,__VA_ARGS__)
#define _4N1R36(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R32(f,o,__VA_ARGS__)
#define _4N1R40(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R36(f,o,__VA_ARGS__)
#define _4N1R44(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R40(f,o,__VA_ARGS__)
#define _4N1R48(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R44(f,o,__VA_ARGS__)
#define _4N1R52(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R48(f,o,__VA_ARGS__)
#define _4N1R56(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R52(f,o,__VA_ARGS__)
#define _4N1R60(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R56(f,o,__VA_ARGS__)
#define _4N1R64(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R60(f,o,__VA_ARGS__)
#define _4N1R68(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R64(f,o,__VA_ARGS__)
#define _4N1R72(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R68(f,o,__VA_ARGS__)
#define _4N1R76(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R72(f,o,__VA_ARGS__)
#define _4N1R80(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R76(f,o,__VA_ARGS__)
#define _4N1R84(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R80(f,o,__VA_ARGS__)
#define _4N1R88(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R84(f,o,__VA_ARGS__)
#define _4N1R92(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R88(f,o,__VA_ARGS__)
#define _4N1R96(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R92(f,o,__VA_ARGS__)
#define _4N1R100(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R96(f,o,__VA_ARGS__)
#define _4N1R104(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R100(f,o,__VA_ARGS__)
#define _4N1R108(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R104(f,o,__VA_ARGS__)
#define _4N1R112(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R108(f,o,__VA_ARGS__)
#define _4N1R116(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R112(f,o,__VA_ARGS__)
#define _4N1R120(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R116(f,o,__VA_ARGS__)
#define _4N1R124(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R120(f,o,__VA_ARGS__)
#define _4N1R128(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R124(f,o,__VA_ARGS__)
#define _4N1R132(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R128(f,o,__VA_ARGS__)
#define _4N1R136(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R132(f,o,__VA_ARGS__)
#define _4N1R140(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R136(f,o,__VA_ARGS__)
#define _4N1R144(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R140(f,o,__VA_ARGS__)
#define _4N1R148(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R144(f,o,__VA_ARGS__)
#define _4N1R152(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R148(f,o,__VA_ARGS__)
#define _4N1R156(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R152(f,o,__VA_ARGS__)
#define _4N1R160(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R156(f,o,__VA_ARGS__)
#define _4N1R164(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R160(f,o,__VA_ARGS__)
#define _4N1R168(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R164(f,o,__VA_ARGS__)
#define _4N1R172(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R168(f,o,__VA_ARGS__)
#define _4N1R176(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R172(f,o,__VA_ARGS__)
#define _4N1R180(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R176(f,o,__VA_ARGS__)
#define _4N1R184(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R180(f,o,__VA_ARGS__)
#define _4N1R188(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R184(f,o,__VA_ARGS__)
#define _4N1R192(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R188(f,o,__VA_ARGS__)
#define _4N1R196(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R192(f,o,__VA_ARGS__)
#define _4N1R200(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R196(f,o,__VA_ARGS__)
#define _4N1R204(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R200(f,o,__VA_ARGS__)
#define _4N1R208(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R204(f,o,__VA_ARGS__)
#define _4N1R212(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R208(f,o,__VA_ARGS__)
#define _4N1R216(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R212(f,o,__VA_ARGS__)
#define _4N1R220(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R216(f,o,__VA_ARGS__)
#define _4N1R224(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R220(f,o,__VA_ARGS__)
#define _4N1R228(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R224(f,o,__VA_ARGS__)
#define _4N1R232(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R228(f,o,__VA_ARGS__)
#define _4N1R236(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R232(f,o,__VA_ARGS__)
#define _4N1R240(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R236(f,o,__VA_ARGS__)
#define _4N1R244(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R240(f,o,__VA_ARGS__)
#define _4N1R248(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R244(f,o,__VA_ARGS__)
#define _4N1R252(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R248(f,o,__VA_ARGS__)
#define _4N1R256(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N1R252(f,o,__VA_ARGS__)

//#define _4N2R0_FLAG
//#define _4N2R0(...) _4N2R0_FLAG
#define _4N2R0(...)
#define _4N2R4(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R0(f,o,__VA_ARGS__)
#define _4N2R8(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R4(f,o,__VA_ARGS__)
#define _4N2R12(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R8(f,o,__VA_ARGS__)
#define _4N2R16(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R12(f,o,__VA_ARGS__)
#define _4N2R20(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R16(f,o,__VA_ARGS__)
#define _4N2R24(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R20(f,o,__VA_ARGS__)
#define _4N2R28(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R24(f,o,__VA_ARGS__)
#define _4N2R32(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R28(f,o,__VA_ARGS__)
#define _4N2R36(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R32(f,o,__VA_ARGS__)
#define _4N2R40(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R36(f,o,__VA_ARGS__)
#define _4N2R44(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R40(f,o,__VA_ARGS__)
#define _4N2R48(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R44(f,o,__VA_ARGS__)
#define _4N2R52(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R48(f,o,__VA_ARGS__)
#define _4N2R56(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R52(f,o,__VA_ARGS__)
#define _4N2R60(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R56(f,o,__VA_ARGS__)
#define _4N2R64(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R60(f,o,__VA_ARGS__)
#define _4N2R68(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R64(f,o,__VA_ARGS__)
#define _4N2R72(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R68(f,o,__VA_ARGS__)
#define _4N2R76(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R72(f,o,__VA_ARGS__)
#define _4N2R80(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R76(f,o,__VA_ARGS__)
#define _4N2R84(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R80(f,o,__VA_ARGS__)
#define _4N2R88(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R84(f,o,__VA_ARGS__)
#define _4N2R92(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R88(f,o,__VA_ARGS__)
#define _4N2R96(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R92(f,o,__VA_ARGS__)
#define _4N2R100(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R96(f,o,__VA_ARGS__)
#define _4N2R104(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R100(f,o,__VA_ARGS__)
#define _4N2R108(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R104(f,o,__VA_ARGS__)
#define _4N2R112(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R108(f,o,__VA_ARGS__)
#define _4N2R116(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R112(f,o,__VA_ARGS__)
#define _4N2R120(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R116(f,o,__VA_ARGS__)
#define _4N2R124(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R120(f,o,__VA_ARGS__)
#define _4N2R128(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R124(f,o,__VA_ARGS__)
#define _4N2R132(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R128(f,o,__VA_ARGS__)
#define _4N2R136(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R132(f,o,__VA_ARGS__)
#define _4N2R140(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R136(f,o,__VA_ARGS__)
#define _4N2R144(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R140(f,o,__VA_ARGS__)
#define _4N2R148(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R144(f,o,__VA_ARGS__)
#define _4N2R152(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R148(f,o,__VA_ARGS__)
#define _4N2R156(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R152(f,o,__VA_ARGS__)
#define _4N2R160(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R156(f,o,__VA_ARGS__)
#define _4N2R164(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R160(f,o,__VA_ARGS__)
#define _4N2R168(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R164(f,o,__VA_ARGS__)
#define _4N2R172(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R168(f,o,__VA_ARGS__)
#define _4N2R176(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R172(f,o,__VA_ARGS__)
#define _4N2R180(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R176(f,o,__VA_ARGS__)
#define _4N2R184(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R180(f,o,__VA_ARGS__)
#define _4N2R188(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R184(f,o,__VA_ARGS__)
#define _4N2R192(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R188(f,o,__VA_ARGS__)
#define _4N2R196(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R192(f,o,__VA_ARGS__)
#define _4N2R200(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R196(f,o,__VA_ARGS__)
#define _4N2R204(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R200(f,o,__VA_ARGS__)
#define _4N2R208(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R204(f,o,__VA_ARGS__)
#define _4N2R212(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R208(f,o,__VA_ARGS__)
#define _4N2R216(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R212(f,o,__VA_ARGS__)
#define _4N2R220(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R216(f,o,__VA_ARGS__)
#define _4N2R224(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R220(f,o,__VA_ARGS__)
#define _4N2R228(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R224(f,o,__VA_ARGS__)
#define _4N2R232(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R228(f,o,__VA_ARGS__)
#define _4N2R236(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R232(f,o,__VA_ARGS__)
#define _4N2R240(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R236(f,o,__VA_ARGS__)
#define _4N2R244(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R240(f,o,__VA_ARGS__)
#define _4N2R248(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R244(f,o,__VA_ARGS__)
#define _4N2R252(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R248(f,o,__VA_ARGS__)
#define _4N2R256(f,o,a,b,c,d,...) f(o,a,b,c,d) _4N2R252(f,o,__VA_ARGS__)

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




#endif
