/*
AtomTree iterable interface for UIs.

TODO explain how to add add tables

Here be preprocessor dragons; ATUI 

vim replace patterns that help copypaste structs from atombios.h:
'<,'>s|struct |ATUI_FUNCIFY(|g
'<,'>s|.*uint[0-9]*_t[ ,^I]*|^I|g
'<,'>s|;.*|,|g
'<,'>s|,\n},|\r)|g
*/

#ifndef ATUI_H
#define ATUI_H
#include "atomtree_common.h"


struct atui_enum {
	char* name;
	int val;
};

//just like funcify
/*
#define PPATUI_ENUMER(name, ...) \
const _atui_enum_##name[] = {};
*/

enum atui_type {
	ATUI_NONE = 0b00,
	ATUI_DEC = 0b01,
	ATUI_HEX = 0b10,
	ATUI_BIN = 0b11,

	ATUI_BITFIELD = 1<<3,
	ATUI_ENUM = 1<<4,
	ATUI_STRING = 1<<5
};

typedef struct atui_branch_ atui_branch;
typedef struct atui_leaf_ atui_leaf;
struct atui_leaf_ {
	char name[40];
	char* description;


	unsigned char bits; // number of bits for the leaf
	//unsigned char type; // number of bits for the leaf
	enum atui_type type; // bitfield struct
	int num_bitfield_children;
	struct atui_enum* enum_options; // text val pair
	int num_enum_opts;

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
	int branch_count;

	void* branch_aux; // alternative representation to leaves, if necessary
	atui_leaf* leaves;
	int leaf_count;

	void* atomleaves;
};

void atui_leaf_set_val(atui_leaf* leaf, uint64_t val);
uint64_t atui_leaf_get_val(atui_leaf* leaf);


//atui has auxiliary pointers to hang extra data off of and this deallocator
//doesn't consider.
void atui_destroy_tree(atui_branch* tree);


//temporary until a better strtol api that considers non base 10 inputs
uint64_t strtol_2(const char* str);




/*
TODO better type handling with ATUI_FUNCIFY? strings, enums?
for example, what about
funcify(tablename,
	leafa,0,
	leafb,0,
	leafstr,1,
	leafc,0
)
where the second, the number, denotes a type?
*/



#define _PPATUI_LEAF_BITNESS(var) _Generic((var), \
	uint8_t*:-1, \
	uint8_t:8, uint16_t:16, uint32_t:32, uint64_t:64, \
	default:1\
)

/*
#define _PPATUI_LEAF(var, type) \
{ \
.val=&(bios->var), .name=#var, .bits=_PPATUI_LEAF_BITNESS(bios->var),\
.type=pptype, \
}
*/



/**** LEAF FANCY FUNCS ***/
#define _PPATUI_FANCY_NOBITFIELD .num_bitfield_children=0,
#define _PPATUI_FANCY_NOENUM .enum_options=NULL, .num_enum_opts=0,

#define _PPATUI_FANCY_ATUI_NONE(doesntmatter) _PPATUI_FANCY_NOBITFIELD _PPATUI_FANCY_NOENUM },

#define _PPATUI_FANCY_ATUI_ENUM(enum_array) _PPATUI_FANCY_NOBITFIELD },

#define _PPATUI_FANCY_ATUI_STRING(doesntmatter) _PPATUI_FANCY_NOBITFIELD _PPATUI_FANCY_NOENUM },





// the 3 is for name,bitness,radix trio
#define _PPATUI_FANCYBF_NUMCHILDREN(tablename, ...) \
	 _PP_NUMARG(__VA_ARGS__) / 3

//#define _PPATUI_FANCY_BFCHILDREN_HELPER(tablename, ...) _PPATUI_BITFIELD_LEAVES(__VA_ARGS__)
//#define _PPATUI_FANCY_BFCHILDREN_HELPER(...) _PPATUI_BITFIELD_LEAVES(__VA_ARGS__)


#define _PPATUI_BFLEAF(tablename, var, bitness, radix) {\
.val=&(bios->tablename.var), .name=#var, .bits=bitness, .type=radix, \
.auxiliary = NULL, _PPATUI_FANCY_NOBITFIELD _PPATUI_FANCY_NOENUM \
},

#define _PPATUI_FANCY_ATUI_BITFIELD(args) \
.num_bitfield_children=_PPATUI_FANCYBF_NUMCHILDREN args , \
_PPATUI_FANCY_NOENUM }, \
_PPATUI_BITFIELD_LEAVES args
// close parent and start on inbred children.


/**** LEAF FANCY FUNCS END***/


#define _PPATUI_LEAF(var, radix, fancytype, fancydata) \
{ \
.val=&(bios->var), .name=#var, .bits=_PPATUI_LEAF_BITNESS(bios->var),\
.type=(radix | fancytype), .auxiliary = NULL, \
_PPATUI_FANCY_##fancytype(fancydata)
// the closing } for the leaf is handled in the fancy pp funcs.






#define PPATUI_FUNC_NAME(PP_NAME) \
atui_branch* _##PP_NAME##_atui(struct PP_NAME * bios, unsigned int num_branches, atui_branch** import_children)

#define H(PP_NAME) PPATUI_FUNC_NAME(PP_NAME)
#define ATUI_MAKE_BRANCH(PP_NAME, bios, num_branches, children) _##PP_NAME##_atui(bios, num_branches, children)

#define PPATUI_FUNCIFY(PP_NAME, ...) \
PPATUI_FUNC_NAME(PP_NAME) {\
	unsigned int i = 0;\
	void* scratch;\
	atui_branch* table = NULL; \
	atui_branch** branches = NULL;\
	atui_leaf* leaves = NULL;\
	unsigned int total_leaves = 0;\
\
	if(PPATUI_NUM_LEAVES(__VA_ARGS__)) {\
		const atui_leaf leavinit[] = { PPATUI_LEAVES(__VA_ARGS__) };\
		total_leaves = sizeof(leavinit)/sizeof(atui_leaf);\
		scratch = malloc(\
			sizeof(atui_branch) + \
			(sizeof(atui_branch*) * num_branches) + \
			sizeof(leavinit) \
		);\
		table = scratch;\
		scratch = scratch + sizeof(atui_branch);\
\
		leaves = scratch + num_branches*sizeof(atui_branch*);\
		for(i=0; i < total_leaves; i++) {\
			leaves[i] = leavinit[i];\
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
		.name=#PP_NAME,.leaves=(atui_leaf*)leaves, \
		.leaf_count=total_leaves, .atomleaves=bios, \
		.child_branches=branches, .branch_count=num_branches \
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
		print("#define _PPA_L%i(%s,...) _PPATUI_LEAF(%s) _PPA_L%i(__VA_ARGS__)" % (i+numargs, args, args, i))

Waterfall loop for primary leaves
*/
#define PPATUI_LEAVES(...) _PPATUI_LHELPER1(_PP_NUMARG(__VA_ARGS__), __VA_ARGS__)
#define _PPATUI_LHELPER1(...) _PPATUI_LHELPER2(__VA_ARGS__)
#define _PPATUI_LHELPER2(N,...) _PPA_L##N(__VA_ARGS__)
#define _PPA_L0(...)
#define _PPA_L4(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta)
#define _PPA_L8(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L4(__VA_ARGS__)
#define _PPA_L12(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L8(__VA_ARGS__)
#define _PPA_L16(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L12(__VA_ARGS__)
#define _PPA_L20(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L16(__VA_ARGS__)
#define _PPA_L24(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L20(__VA_ARGS__)
#define _PPA_L28(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L24(__VA_ARGS__)
#define _PPA_L32(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L28(__VA_ARGS__)
#define _PPA_L36(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L32(__VA_ARGS__)
#define _PPA_L40(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L36(__VA_ARGS__)
#define _PPA_L44(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L40(__VA_ARGS__)
#define _PPA_L48(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L44(__VA_ARGS__)
#define _PPA_L52(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L48(__VA_ARGS__)
#define _PPA_L56(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L52(__VA_ARGS__)
#define _PPA_L60(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L56(__VA_ARGS__)
#define _PPA_L64(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L60(__VA_ARGS__)
#define _PPA_L68(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L64(__VA_ARGS__)
#define _PPA_L72(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L68(__VA_ARGS__)
#define _PPA_L76(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L72(__VA_ARGS__)
#define _PPA_L80(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L76(__VA_ARGS__)
#define _PPA_L84(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L80(__VA_ARGS__)
#define _PPA_L88(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L84(__VA_ARGS__)
#define _PPA_L92(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L88(__VA_ARGS__)
#define _PPA_L96(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L92(__VA_ARGS__)
#define _PPA_L100(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L96(__VA_ARGS__)
#define _PPA_L104(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L100(__VA_ARGS__)
#define _PPA_L108(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L104(__VA_ARGS__)
#define _PPA_L112(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L108(__VA_ARGS__)
#define _PPA_L116(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L112(__VA_ARGS__)
#define _PPA_L120(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L116(__VA_ARGS__)
#define _PPA_L124(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L120(__VA_ARGS__)
#define _PPA_L128(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L124(__VA_ARGS__)
#define _PPA_L132(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L128(__VA_ARGS__)
#define _PPA_L136(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L132(__VA_ARGS__)
#define _PPA_L140(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L136(__VA_ARGS__)
#define _PPA_L144(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L140(__VA_ARGS__)
#define _PPA_L148(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L144(__VA_ARGS__)
#define _PPA_L152(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L148(__VA_ARGS__)
#define _PPA_L156(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L152(__VA_ARGS__)
#define _PPA_L160(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L156(__VA_ARGS__)
#define _PPA_L164(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L160(__VA_ARGS__)
#define _PPA_L168(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L164(__VA_ARGS__)
#define _PPA_L172(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L168(__VA_ARGS__)
#define _PPA_L176(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L172(__VA_ARGS__)
#define _PPA_L180(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L176(__VA_ARGS__)
#define _PPA_L184(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L180(__VA_ARGS__)
#define _PPA_L188(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L184(__VA_ARGS__)
#define _PPA_L192(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L188(__VA_ARGS__)
#define _PPA_L196(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L192(__VA_ARGS__)
#define _PPA_L200(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L196(__VA_ARGS__)
#define _PPA_L204(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L200(__VA_ARGS__)
#define _PPA_L208(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L204(__VA_ARGS__)
#define _PPA_L212(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L208(__VA_ARGS__)
#define _PPA_L216(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L212(__VA_ARGS__)
#define _PPA_L220(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L216(__VA_ARGS__)
#define _PPA_L224(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L220(__VA_ARGS__)
#define _PPA_L228(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L224(__VA_ARGS__)
#define _PPA_L232(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L228(__VA_ARGS__)
#define _PPA_L236(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L232(__VA_ARGS__)
#define _PPA_L240(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L236(__VA_ARGS__)
#define _PPA_L244(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L240(__VA_ARGS__)
#define _PPA_L248(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L244(__VA_ARGS__)
#define _PPA_L252(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L248(__VA_ARGS__)
#define _PPA_L256(v,r,t,ta,...) _PPATUI_LEAF(v,r,t,ta) _PPA_L252(__VA_ARGS__)



/*
python script:
def ppatui_leaveshelper(max_entries=32, args="v,b,r"):
	numargs=len(args.split(","))
	for i in range(0,max_entries*numargs, numargs):
		print("#define _BFL%i(t,%s,...) _PPATUI_BFLEAF(t,%s) _BFL%i(t,__VA_ARGS__)" % (i+numargs, args, args, i))

Waterfall loop for bitfield leaves
*/
#define _PPATUI_BITFIELD_LEAVES(table, ...) \
	_PPATUI_BFLHELPER1(table,_PP_NUMARG(__VA_ARGS__), __VA_ARGS__)
#define _PPATUI_BFLHELPER1(table, ...) _PPATUI_BFLHELPER2(table,__VA_ARGS__)
#define _PPATUI_BFLHELPER2(table, N,...) _BFL##N(table, __VA_ARGS__)
#define _PPA_BFL0(...)
#define _BFL3(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL0(t,__VA_ARGS__)
#define _BFL6(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL3(t,__VA_ARGS__)
#define _BFL9(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL6(t,__VA_ARGS__)
#define _BFL12(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL9(t,__VA_ARGS__)
#define _BFL15(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL12(t,__VA_ARGS__)
#define _BFL18(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL15(t,__VA_ARGS__)
#define _BFL21(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL18(t,__VA_ARGS__)
#define _BFL24(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL21(t,__VA_ARGS__)
#define _BFL27(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL24(t,__VA_ARGS__)
#define _BFL30(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL27(t,__VA_ARGS__)
#define _BFL33(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL30(t,__VA_ARGS__)
#define _BFL36(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL33(t,__VA_ARGS__)
#define _BFL39(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL36(t,__VA_ARGS__)
#define _BFL42(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL39(t,__VA_ARGS__)
#define _BFL45(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL42(t,__VA_ARGS__)
#define _BFL48(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL45(t,__VA_ARGS__)
#define _BFL51(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL48(t,__VA_ARGS__)
#define _BFL54(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL51(t,__VA_ARGS__)
#define _BFL57(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL54(t,__VA_ARGS__)
#define _BFL60(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL57(t,__VA_ARGS__)
#define _BFL63(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL60(t,__VA_ARGS__)
#define _BFL66(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL63(t,__VA_ARGS__)
#define _BFL69(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL66(t,__VA_ARGS__)
#define _BFL72(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL69(t,__VA_ARGS__)
#define _BFL75(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL72(t,__VA_ARGS__)
#define _BFL78(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL75(t,__VA_ARGS__)
#define _BFL81(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL78(t,__VA_ARGS__)
#define _BFL84(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL81(t,__VA_ARGS__)
#define _BFL87(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL84(t,__VA_ARGS__)
#define _BFL90(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL87(t,__VA_ARGS__)
#define _BFL93(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL90(t,__VA_ARGS__)
#define _BFL96(t,v,b,r,...) _PPATUI_BFLEAF(t,v,b,r) _BFL93(t,__VA_ARGS__)




H(atom_common_table_header);

H(atom_rom_header_v2_2);
H(atom_master_data_table_v2_1);


// fuck me...
//H(atom_umc_reg_setting_data_block);


H(atom_vram_module_v10);
H(atom_vram_info_header_v2_4);

#endif
