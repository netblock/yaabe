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
#include "atomtree_common.h"


// shall be used in an array
struct atui_enum {
	char* name;
	int val;
};


enum atui_type {
	ATUI_NONE = 0b000,
	ATUI_DEC  = 0b001,
	ATUI_HEX  = 0b010,
	ATUI_BIN  = 0b011,
	ATUI_ANY  = 0b111,

	ATUI_BITFIELD = 1<<4,
	ATUI_ENUM     = 1<<5, // see also PPATUI_FUNCIFY()
	ATUI_STRING   = 1<<6, // meant for human-readable text
	ATUI_ARRAY    = 1<<7, // no technical difference from string 
	ATUI_INLINE   = 1<<8, // pull in leaves from other tables
};

typedef struct atui_branch_ atui_branch;
typedef struct atui_leaf_ atui_leaf;
struct atui_leaf_ {
	char name[40];
	char* description;


	enum atui_type type; // bitfield struct
	uint8_t array_size;
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
struct  atui_branch_ {
	char name[40];
	char* description;

	atui_branch** child_branches;
	uint8_t branch_count;
	uint8_t max_branch_count;

	atui_branch** inline_branches;
	uint8_t inline_branch_count;
	uint8_t max_inline_branch_count;
	

	void* branch_aux; // alternative representation to leaves, if necessary
	atui_leaf* leaves;
	uint8_t leaf_count;

	void* atomleaves;
};

void atui_leaf_set_val(atui_leaf* leaf, uint64_t val);
uint64_t atui_leaf_get_val(atui_leaf* leaf);


//atui has auxiliary pointers to hang extra data off of and this deallocator
//doesn't consider.
void atui_destroy_tree(atui_branch* tree);


//temporary until a better strtol api that considers non base 10 inputs
uint64_t strtol_2(const char* str);



#define _PPATUI_LEAF_BITNESS(var) _Generic((var), \
	uint8_t*:8, uint16_t*:16, uint32_t*:32, uint64_t*:64, \
	uint8_t:8, uint16_t:16, uint32_t:32, uint64_t:64, \
	default:0\
)


/**** LEAF FANCY FUNCS ***/
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


#define _PPATUI_FANCY_ATUI_NONE(bios, var, radix, fancytype, fancydata) \
	_PPATUI_FANCY_INIT(bios, var, radix, fancytype) \
	_PPATUI_FANCY_NOBITFIELD(bios->var) _PPATUI_FANCY_NOENUM },



#define _PPATUI_FANCY_ATUI_ENUM(bios, var, radix, fancytype, enumname) \
	_PPATUI_FANCY_INIT(bios, var, radix, fancytype) \
	.enum_options=_atui_enum_##enumname, \
	.num_enum_opts=sizeof(_atui_enum_##enumname)/sizeof(struct atui_enum), \
	_PPATUI_FANCY_NOBITFIELD(bios->var) },

#define PPATUI_ENUMER(name, ...) \
	const struct atui_enum _atui_enum_##name[] = \
		{_PPATUI_ENUM_ENTRIES(__VA_ARGS__)};
#define _PPATUI_EENTRY(estate) {.name=#estate, .val=estate}, 



#define _PPATUI_FANCY_ATUI_STRING(bios, var, radix, fancytype, fancydata) \
	_PPATUI_FANCY_ATUI_ARRAY(bios, var, radix, fancytype, fancydata) 

#define _PPATUI_FANCY_ATUI_ARRAY(bios, var, radix, fancytype, fancydata) \
	_PPATUI_FANCY_INIT(bios, var, radix, fancytype) \
	.array_size = sizeof(bios->var)/sizeof(bios->var[0]), \
	_PPATUI_FANCY_NOBITFIELD(bios->var) _PPATUI_FANCY_NOENUM },



#define _PPATUI_FANCY_ATUI_BITFIELD(bios, var, radix, fancytype, fancydata) \
	_PPATUI_FANCY_INIT(bios, var, radix, fancytype) \
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
		.type=(radix|ATUI_BITFIELD), \
		.total_bits=_PPATUI_LEAF_BITNESS(biosvar), \
		.bitfield_hi=bit_end, .bitfield_lo=bit_start, \
		_PPATUI_FANCY_NOENUM _PPATUI_FANCY_NOBITFIELD(biosvar) \
		_PPATUI_FANCY_NOARRAY .auxiliary = NULL, \
	},



#define _PPATUI_FANCY_ATUI_INLINE(bios, var, radix, fancytype, fancydata)\
	.val=NULL, \
	_PPATUI_FANCY_NOENUM _PPATUI_FANCY_NOBITFIELD_HARD \
	_PPATUI_FANCY_NOARRAY },

#define _PPATUI_INLEAF_ATUI_NONE(...)
#define _PPATUI_INLEAF_ATUI_BITFIELD(...)
#define _PPATUI_INLEAF_ATUI_ENUM(...)
#define _PPATUI_INLEAF_ATUI_STRING(...)
#define _PPATUI_INLEAF_ATUI_ARRAY(...)

#define _PPATUI_INLEAF_ATUI_INLINE(pp_name, instancename)\
	ATUI_MAKE_BRANCH(pp_name, &(bios->instancename), 0, NULL),
#define _PPATUI_INLEAF(var, radix, fancytype, fancydata) \
	_PPATUI_INLEAF_##fancytype(fancydata, var)




#define _PPATUI_FANCY_INIT(bios, var, radix, fancytype) \
		.val=&(bios->var), .total_bits=_PPATUI_LEAF_BITNESS(bios->var),
/**** LEAF FANCY FUNCS END***/


#define _PPATUI_LEAF(bios, var, radix, fancytype, fancydata) \
	{ \
		.name=#var, .type=(radix | fancytype), .auxiliary=NULL, \
	_PPATUI_FANCY_##fancytype(bios, var, radix, fancytype, fancydata)
	// the closing } for the leaf is handled in the fancy pp funcs.



#define PPATUI_FUNC_NAME(pp_name) \
	atui_branch* _##pp_name##_atui( \
		struct pp_name * bios, \
		unsigned int num_branches, \
		atui_branch** import_children \
	)

#define H(pp_name) PPATUI_FUNC_NAME(pp_name)
#define ATUI_MAKE_BRANCH(pp_name, bios, num_branches, children) \
	_##pp_name##_atui(bios, num_branches, children)

#define PPATUI_FUNCIFY(pp_name, ...) \
PPATUI_FUNC_NAME(pp_name) {\
	atui_branch* table = NULL; \
	atui_branch** branches = NULL;\
\
	atui_branch** inliners = NULL;\
	uint8_t num_inliners;\
\
	atui_leaf* leaves = NULL;\
	uint8_t total_leaves = 0;\
\
	void* scratch;\
	uint8_t i = 0;\
	uint8_t j = 0;\
\
\
	if(PPATUI_NUM_LEAVES(__VA_ARGS__)) {\
		const atui_leaf leaves_init[] = { _PPATUI_LEAVES(bios, __VA_ARGS__) };\
		total_leaves = sizeof(leaves_init)/sizeof(atui_leaf);\
\
		const atui_branch* inliners_init[] = { \
			_PPATUI_INLINE_BRANCHES(__VA_ARGS__) \
		}; \
		num_inliners = sizeof(inliners_init)/sizeof(atui_branch*);\
\
		/*counts bitfield*/ \
\
		scratch = malloc(\
			sizeof(atui_branch) + \
			(sizeof(atui_branch*) *  num_branches) + \
			sizeof(inliners_init) + \
			sizeof(leaves_init) \
		);\
		table = scratch;\
		scratch = scratch + sizeof(atui_branch);\
\
		leaves = scratch + num_branches*sizeof(atui_branch*) +\
			sizeof(inliners_init);\
		for(i=0; i < total_leaves; i++) {\
			leaves[i] = leaves_init[i];\
		}\
\
		if (sizeof(inliners_init)) {\
			inliners = scratch + num_branches*sizeof(atui_branch*);\
			for(i=0; i<num_inliners; i++) {\
				inliners[i] = (atui_branch*) inliners_init[i];\
			}\
			j=0;\
			for(i=0; i<total_leaves; i++) {\
				if (leaves[i].type & ATUI_INLINE) {\
					leaves[i].inline_branch = &(inliners[j]);\
					j++;\
				}\
			}\
		}\
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
		.name=#pp_name, .leaves=(atui_leaf*)leaves, \
		.leaf_count=total_leaves, .atomleaves=bios, \
		.child_branches=branches, .branch_count=num_branches, \
		.inline_branches=inliners, .inline_branch_count=num_inliners, \
		.max_branch_count=num_branches, .max_inline_branch_count=num_inliners, \
	};\
	return table;\
}



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


#define PPATUI_NUM_LEAVES(...) _PP_NUMARG(__VA_ARGS__)/4

/*
python script:
def ppatui_leaveshelper(max_entries=64, args="v,r,t,ta"):
	numargs=len(args.split(","))
	for i in range(0,max_entries*numargs, numargs):
		print("#define _AL%i(b,%s,...) _PPATUI_LEAF(b,%s) _AL%i(b,__VA_ARGS__)" % (i+numargs, args, args, i))

Waterfall loop for primary leaves
*/
#define _PPATUI_LEAVES(bios, ...) \
	_PPATUI_LHELPER1(bios, _PP_NUMARG(__VA_ARGS__), __VA_ARGS__)
#define _PPATUI_LHELPER1(b, ...) _PPATUI_LHELPER2(b, __VA_ARGS__)
#define _PPATUI_LHELPER2(b, N,...) _AL##N(b, __VA_ARGS__)
#define _AL0(...)
#define _AL4(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta)
#define _AL8(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL4(b,__VA_ARGS__)
#define _AL12(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL8(b,__VA_ARGS__)
#define _AL16(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL12(b,__VA_ARGS__)
#define _AL20(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL16(b,__VA_ARGS__)
#define _AL24(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL20(b,__VA_ARGS__)
#define _AL28(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL24(b,__VA_ARGS__)
#define _AL32(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL28(b,__VA_ARGS__)
#define _AL36(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL32(b,__VA_ARGS__)
#define _AL40(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL36(b,__VA_ARGS__)
#define _AL44(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL40(b,__VA_ARGS__)
#define _AL48(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL44(b,__VA_ARGS__)
#define _AL52(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL48(b,__VA_ARGS__)
#define _AL56(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL52(b,__VA_ARGS__)
#define _AL60(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL56(b,__VA_ARGS__)
#define _AL64(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL60(b,__VA_ARGS__)
#define _AL68(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL64(b,__VA_ARGS__)
#define _AL72(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL68(b,__VA_ARGS__)
#define _AL76(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL72(b,__VA_ARGS__)
#define _AL80(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL76(b,__VA_ARGS__)
#define _AL84(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL80(b,__VA_ARGS__)
#define _AL88(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL84(b,__VA_ARGS__)
#define _AL92(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL88(b,__VA_ARGS__)
#define _AL96(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL92(b,__VA_ARGS__)
#define _AL100(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL96(b,__VA_ARGS__)
#define _AL104(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL100(b,__VA_ARGS__)
#define _AL108(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL104(b,__VA_ARGS__)
#define _AL112(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL108(b,__VA_ARGS__)
#define _AL116(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL112(b,__VA_ARGS__)
#define _AL120(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL116(b,__VA_ARGS__)
#define _AL124(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL120(b,__VA_ARGS__)
#define _AL128(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL124(b,__VA_ARGS__)
#define _AL132(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL128(b,__VA_ARGS__)
#define _AL136(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL132(b,__VA_ARGS__)
#define _AL140(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL136(b,__VA_ARGS__)
#define _AL144(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL140(b,__VA_ARGS__)
#define _AL148(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL144(b,__VA_ARGS__)
#define _AL152(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL148(b,__VA_ARGS__)
#define _AL156(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL152(b,__VA_ARGS__)
#define _AL160(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL156(b,__VA_ARGS__)
#define _AL164(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL160(b,__VA_ARGS__)
#define _AL168(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL164(b,__VA_ARGS__)
#define _AL172(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL168(b,__VA_ARGS__)
#define _AL176(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL172(b,__VA_ARGS__)
#define _AL180(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL176(b,__VA_ARGS__)
#define _AL184(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL180(b,__VA_ARGS__)
#define _AL188(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL184(b,__VA_ARGS__)
#define _AL192(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL188(b,__VA_ARGS__)
#define _AL196(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL192(b,__VA_ARGS__)
#define _AL200(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL196(b,__VA_ARGS__)
#define _AL204(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL200(b,__VA_ARGS__)
#define _AL208(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL204(b,__VA_ARGS__)
#define _AL212(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL208(b,__VA_ARGS__)
#define _AL216(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL212(b,__VA_ARGS__)
#define _AL220(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL216(b,__VA_ARGS__)
#define _AL224(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL220(b,__VA_ARGS__)
#define _AL228(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL224(b,__VA_ARGS__)
#define _AL232(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL228(b,__VA_ARGS__)
#define _AL236(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL232(b,__VA_ARGS__)
#define _AL240(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL236(b,__VA_ARGS__)
#define _AL244(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL240(b,__VA_ARGS__)
#define _AL248(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL244(b,__VA_ARGS__)
#define _AL252(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL248(b,__VA_ARGS__)
#define _AL256(b,v,r,t,ta,...) _PPATUI_LEAF(b,v,r,t,ta) _AL252(b,__VA_ARGS__)


/*
def ppatui_enumhelper(max_entries=32, args="n"):
        numargs=len(args.split(","))
        for i in range(0,max_entries*numargs, numargs):
                print("#define _PPA_EN%i(%s,...) _PPATUI_EENTRY(%s) _PPA_EN%i(__VA_ARGS__)" % (i+numargs, args, args, i))


Waterfall loop for atui enum generator
*/
#define _PPATUI_ENUM_ENTRIES(...) \
	_PPATUI_ENHELPER1(_PP_NUMARG(__VA_ARGS__), __VA_ARGS__)
#define _PPATUI_ENHELPER1(...) _PPATUI_ENHELPER2(__VA_ARGS__)
#define _PPATUI_ENHELPER2(N,...) _PPA_EN##N(__VA_ARGS__)
#define __PPA_EN0(...)
#define _PPA_EN1(n,...) _PPATUI_EENTRY(n)
#define _PPA_EN2(n,...) _PPATUI_EENTRY(n) _PPA_EN1(__VA_ARGS__)
#define _PPA_EN3(n,...) _PPATUI_EENTRY(n) _PPA_EN2(__VA_ARGS__)
#define _PPA_EN4(n,...) _PPATUI_EENTRY(n) _PPA_EN3(__VA_ARGS__)
#define _PPA_EN5(n,...) _PPATUI_EENTRY(n) _PPA_EN4(__VA_ARGS__)
#define _PPA_EN6(n,...) _PPATUI_EENTRY(n) _PPA_EN5(__VA_ARGS__)
#define _PPA_EN7(n,...) _PPATUI_EENTRY(n) _PPA_EN6(__VA_ARGS__)
#define _PPA_EN8(n,...) _PPATUI_EENTRY(n) _PPA_EN7(__VA_ARGS__)
#define _PPA_EN9(n,...) _PPATUI_EENTRY(n) _PPA_EN8(__VA_ARGS__)
#define _PPA_EN10(n,...) _PPATUI_EENTRY(n) _PPA_EN9(__VA_ARGS__)
#define _PPA_EN11(n,...) _PPATUI_EENTRY(n) _PPA_EN10(__VA_ARGS__)
#define _PPA_EN12(n,...) _PPATUI_EENTRY(n) _PPA_EN11(__VA_ARGS__)
#define _PPA_EN13(n,...) _PPATUI_EENTRY(n) _PPA_EN12(__VA_ARGS__)
#define _PPA_EN14(n,...) _PPATUI_EENTRY(n) _PPA_EN13(__VA_ARGS__)
#define _PPA_EN15(n,...) _PPATUI_EENTRY(n) _PPA_EN14(__VA_ARGS__)
#define _PPA_EN16(n,...) _PPATUI_EENTRY(n) _PPA_EN15(__VA_ARGS__)
#define _PPA_EN17(n,...) _PPATUI_EENTRY(n) _PPA_EN16(__VA_ARGS__)
#define _PPA_EN18(n,...) _PPATUI_EENTRY(n) _PPA_EN17(__VA_ARGS__)
#define _PPA_EN19(n,...) _PPATUI_EENTRY(n) _PPA_EN18(__VA_ARGS__)
#define _PPA_EN20(n,...) _PPATUI_EENTRY(n) _PPA_EN19(__VA_ARGS__)
#define _PPA_EN21(n,...) _PPATUI_EENTRY(n) _PPA_EN20(__VA_ARGS__)
#define _PPA_EN22(n,...) _PPATUI_EENTRY(n) _PPA_EN21(__VA_ARGS__)
#define _PPA_EN23(n,...) _PPATUI_EENTRY(n) _PPA_EN22(__VA_ARGS__)
#define _PPA_EN24(n,...) _PPATUI_EENTRY(n) _PPA_EN23(__VA_ARGS__)
#define _PPA_EN25(n,...) _PPATUI_EENTRY(n) _PPA_EN24(__VA_ARGS__)
#define _PPA_EN26(n,...) _PPATUI_EENTRY(n) _PPA_EN25(__VA_ARGS__)
#define _PPA_EN27(n,...) _PPATUI_EENTRY(n) _PPA_EN26(__VA_ARGS__)
#define _PPA_EN28(n,...) _PPATUI_EENTRY(n) _PPA_EN27(__VA_ARGS__)
#define _PPA_EN29(n,...) _PPATUI_EENTRY(n) _PPA_EN28(__VA_ARGS__)
#define _PPA_EN30(n,...) _PPATUI_EENTRY(n) _PPA_EN29(__VA_ARGS__)
#define _PPA_EN31(n,...) _PPATUI_EENTRY(n) _PPA_EN30(__VA_ARGS__)
#define _PPA_EN32(n,...) _PPATUI_EENTRY(n) _PPA_EN31(__VA_ARGS__)



/*
python script:
def ppatui_bfleaveshelper(max_entries=32, args="n,bh,bl,r"):
	numargs=len(args.split(","))
	for i in range(0,max_entries*numargs, numargs):
		print("#define _BFL%i(v,%s,...) _PPA_BFLEAF(v,%s) _BFL%i(v,__VA_ARGS__)" % (i+numargs, args, args, i))

Waterfall loop for bitfield leaves
*/
#define _PPATUI_BITFIELD_LEAVES(parent_var, ...) \
	_PPATUI_BFLHELPER1(parent_var, _PP_NUMARG(__VA_ARGS__), __VA_ARGS__)
#define _PPATUI_BFLHELPER1(v,...) _PPATUI_BFLHELPER2(v,__VA_ARGS__)
#define _PPATUI_BFLHELPER2(v,N,...) _BFL##N(v,__VA_ARGS__)
#define _BFL0(...)
#define _BFL4(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r)
#define _BFL8(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL4(v,__VA_ARGS__)
#define _BFL12(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL8(v,__VA_ARGS__)
#define _BFL16(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL12(v,__VA_ARGS__)
#define _BFL20(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL16(v,__VA_ARGS__)
#define _BFL24(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL20(v,__VA_ARGS__)
#define _BFL28(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL24(v,__VA_ARGS__)
#define _BFL32(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL28(v,__VA_ARGS__)
#define _BFL36(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL32(v,__VA_ARGS__)
#define _BFL40(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL36(v,__VA_ARGS__)
#define _BFL44(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL40(v,__VA_ARGS__)
#define _BFL48(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL44(v,__VA_ARGS__)
#define _BFL52(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL48(v,__VA_ARGS__)
#define _BFL56(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL52(v,__VA_ARGS__)
#define _BFL60(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL56(v,__VA_ARGS__)
#define _BFL64(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL60(v,__VA_ARGS__)
#define _BFL68(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL64(v,__VA_ARGS__)
#define _BFL72(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL68(v,__VA_ARGS__)
#define _BFL76(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL72(v,__VA_ARGS__)
#define _BFL80(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL76(v,__VA_ARGS__)
#define _BFL84(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL80(v,__VA_ARGS__)
#define _BFL88(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL84(v,__VA_ARGS__)
#define _BFL92(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL88(v,__VA_ARGS__)
#define _BFL96(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL92(v,__VA_ARGS__)
#define _BFL100(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL96(v,__VA_ARGS__)
#define _BFL104(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL100(v,__VA_ARGS__)
#define _BFL108(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL104(v,__VA_ARGS__)
#define _BFL112(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL108(v,__VA_ARGS__)
#define _BFL116(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL112(v,__VA_ARGS__)
#define _BFL120(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL116(v,__VA_ARGS__)
#define _BFL124(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL120(v,__VA_ARGS__)
#define _BFL128(v,n,bh,bl,r,...) _PPA_BFLEAF(v,n,bh,bl,r) _BFL124(v,__VA_ARGS__)




/*
python script:
def ppatui_inlineleaveshelper(max_entries=64, args="v,r,t,ta"):
	numargs=len(args.split(","))
	for i in range(0,max_entries*numargs, numargs):
		print("#define _IL%i(%s,...) _PPATUI_INLEAF(%s) _IL%i(__VA_ARGS__)" % (i+numargs, args, args, i))

Waterfall loop for inline leaves
*/
#define _PPATUI_INLINE_BRANCHES(...) \
	_PPATUI_ILHELPER1(_PP_NUMARG(__VA_ARGS__), __VA_ARGS__)
#define _PPATUI_ILHELPER1(...) _PPATUI_ILHELPER2(__VA_ARGS__)
#define _PPATUI_ILHELPER2(N,...) _IL##N(__VA_ARGS__)
#define _IL0(...)
#define _IL4(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta)
#define _IL8(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL4(__VA_ARGS__)
#define _IL12(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL8(__VA_ARGS__)
#define _IL16(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL12(__VA_ARGS__)
#define _IL20(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL16(__VA_ARGS__)
#define _IL24(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL20(__VA_ARGS__)
#define _IL28(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL24(__VA_ARGS__)
#define _IL32(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL28(__VA_ARGS__)
#define _IL36(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL32(__VA_ARGS__)
#define _IL40(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL36(__VA_ARGS__)
#define _IL44(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL40(__VA_ARGS__)
#define _IL48(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL44(__VA_ARGS__)
#define _IL52(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL48(__VA_ARGS__)
#define _IL56(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL52(__VA_ARGS__)
#define _IL60(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL56(__VA_ARGS__)
#define _IL64(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL60(__VA_ARGS__)
#define _IL68(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL64(__VA_ARGS__)
#define _IL72(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL68(__VA_ARGS__)
#define _IL76(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL72(__VA_ARGS__)
#define _IL80(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL76(__VA_ARGS__)
#define _IL84(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL80(__VA_ARGS__)
#define _IL88(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL84(__VA_ARGS__)
#define _IL92(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL88(__VA_ARGS__)
#define _IL96(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL92(__VA_ARGS__)
#define _IL100(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL96(__VA_ARGS__)
#define _IL104(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL100(__VA_ARGS__)
#define _IL108(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL104(__VA_ARGS__)
#define _IL112(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL108(__VA_ARGS__)
#define _IL116(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL112(__VA_ARGS__)
#define _IL120(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL116(__VA_ARGS__)
#define _IL124(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL120(__VA_ARGS__)
#define _IL128(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL124(__VA_ARGS__)
#define _IL132(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL128(__VA_ARGS__)
#define _IL136(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL132(__VA_ARGS__)
#define _IL140(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL136(__VA_ARGS__)
#define _IL144(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL140(__VA_ARGS__)
#define _IL148(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL144(__VA_ARGS__)
#define _IL152(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL148(__VA_ARGS__)
#define _IL156(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL152(__VA_ARGS__)
#define _IL160(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL156(__VA_ARGS__)
#define _IL164(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL160(__VA_ARGS__)
#define _IL168(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL164(__VA_ARGS__)
#define _IL172(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL168(__VA_ARGS__)
#define _IL176(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL172(__VA_ARGS__)
#define _IL180(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL176(__VA_ARGS__)
#define _IL184(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL180(__VA_ARGS__)
#define _IL188(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL184(__VA_ARGS__)
#define _IL192(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL188(__VA_ARGS__)
#define _IL196(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL192(__VA_ARGS__)
#define _IL200(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL196(__VA_ARGS__)
#define _IL204(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL200(__VA_ARGS__)
#define _IL208(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL204(__VA_ARGS__)
#define _IL212(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL208(__VA_ARGS__)
#define _IL216(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL212(__VA_ARGS__)
#define _IL220(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL216(__VA_ARGS__)
#define _IL224(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL220(__VA_ARGS__)
#define _IL228(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL224(__VA_ARGS__)
#define _IL232(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL228(__VA_ARGS__)
#define _IL236(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL232(__VA_ARGS__)
#define _IL240(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL236(__VA_ARGS__)
#define _IL244(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL240(__VA_ARGS__)
#define _IL248(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL244(__VA_ARGS__)
#define _IL252(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL248(__VA_ARGS__)
#define _IL256(v,r,t,ta,...) _PPATUI_INLEAF(v,r,t,ta) _IL252(__VA_ARGS__)





H(atom_common_table_header);

H(atom_rom_header_v2_2);
H(atom_master_data_table_v2_1);


// fuck me...
//H(atom_umc_reg_setting_data_block);


H(atom_vram_module_v10);
H(atom_vram_info_header_v2_4);

#endif
