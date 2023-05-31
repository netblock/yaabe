/*
AtomTree iterable interface for UIs.

adding tables

vim replace patterns that help copypaste structs from atombios.h:
'<,'>s|struct |ATUI_FUNCIFY(|g
'<,'>s|.*uint[0-9]*_t[ ,^I]*|^I|g
'<,'>s|;.*|,|g
'<,'>s|,\n},|\r)|g
*/

#ifndef ATUI_H
#define ATUI_H
#include "atomtree_common.h"


struct atui_enumer {
	char* name;
	int val;
};


enum atui_type {
	ATUI_DEC = 0b00,
	ATUI_HEX = 0b01,
	ATUI_BIN = 0b10,

	ATUI_BITFIELD = 1<<3,
	ATUI_ENUM = 1<<4,
};

typedef struct atui_branch_ atui_branch;
typedef struct atui_leaf_ atui_leaf;
struct atui_leaf_ {
	char name[40];
	char* description;


	unsigned char bits; // number of bits for the leaf
	//unsigned char type; // number of bits for the leaf
	enum atui_type type; // bitfield struct
	atui_leaf* bitfield_leaves;
	int num_bitfield_children;
	struct atui_enumer* enum_options; // text val pair
	int num_enum_opts;

	union {
		void*     val;
		uint8_t*  u8;
		uint16_t* u16;
		uint32_t* u32;
		uint64_t* u64;
	};

	void* auxilary; // any extra info to hang off if necessary
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

#define _PPATUI_LEAF(var, pptype) \
	{.val=&(bios->var), .name=#var, .type=pptype, .bits=_PPATUI_LEAF_BITNESS(bios->var)},


#define PPATUI_FUNC_NAME(PP_NAME) \
atui_branch* _##PP_NAME##_atui(struct PP_NAME * bios, unsigned int num_branches, atui_branch** import_children)

#define H(PP_NAME) PPATUI_FUNC_NAME(PP_NAME)
#define ATUI_MAKE_BRANCH(PP_NAME, bios, num_branches, children) _##PP_NAME##_atui(bios, num_branches, children)

#define PPATUI_FUNCIFY(PP_NAME, ...) \
PPATUI_FUNC_NAME(PP_NAME) { \
	int i = 0; \
	void* scratch;\
\
	atui_branch* table = NULL; \
	scratch = malloc( \
		sizeof(atui_branch) + \
		(sizeof(atui_branch*) * num_branches) +  \
		(sizeof(atui_leaf) * PPATUI_NUM_LEAVES(__VA_ARGS__)) \
	); \
	table = scratch;\
	scratch = scratch + sizeof(atui_branch);\
\
	atui_branch** branches = NULL; \
	if (num_branches) { \
		branches = scratch; \
		if (import_children != NULL) { \
			for (i=0; i<num_branches; i++) { \
				branches[i] = import_children[i]; \
			} \
		} \
	} \
	scratch = scratch + num_branches * sizeof(atui_branch*);\
\
	atui_leaf* leaves = NULL; \
	if(PPATUI_NUM_LEAVES(__VA_ARGS__)) { \
		leaves = scratch;\
		atui_leaf leavinit[] = {PPATUI_LEAVES(__VA_ARGS__)};\
		for(i=0; i < PPATUI_NUM_LEAVES(__VA_ARGS__); i++) {\
			leaves[i] = leavinit[i]; \
		}\
	} \
\
	*table = (atui_branch) { \
		.name=#PP_NAME,.leaves=(atui_leaf*)leaves,\
		.leaf_count=PPATUI_NUM_LEAVES(__VA_ARGS__), .atomleaves=bios, \
		.child_branches=branches, .branch_count=num_branches \
	}; \
	return table; \
}


/*
Throw the to-be-counted args into the depthcan and then measure the how
full the depthcan is with the depthstick.
Scale both ruler and depthcan if you want to count more than 63 args.

python script:
for i in range(128): print("%i," % (127-i), end='')
for i in range(1,128): print("_%i," % (i), end='')
*/
#define _PP_ARGCOUNTER_RULER \
	127,126,125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110, \
	109,108,107,106,105,104,103,102,101,100,99,98,97,96,95,94,93,92,91,90,89, \
	88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65, \
	64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41, \
	40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17, \
	16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0
#define _PP_ARGCOUNTER_DEPTHCAN_( \
	_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
	_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38, \
	_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56, \
	_57,_58,_59,_60,_61,_62,_63,_64,_65,_66,_67,_68,_69,_70,_71,_72,_73,_74, \
	_75,_76,_77,_78,_79,_80,_81,_82,_83,_84,_85,_86,_87,_88,_89,_90,_91,_92, \
	_93,_94,_95,_96,_97,_98,_99,_100,_101,_102,_103,_104,_105,_106,_107,_108, \
	_109,_110,_111,_112,_113,_114,_115,_116,_117,_118,_119,_120,_121,_122, \
	_123,_124,_125,_126,_127,N,...) N
#define _PP_ARGCOUNTER_DEPTHCAN(...) _PP_ARGCOUNTER_DEPTHCAN_(__VA_ARGS__)
#define _PP_NUMARG(...) \
	_PP_ARGCOUNTER_DEPTHCAN(__VA_ARGS__ __VA_OPT__(,) _PP_ARGCOUNTER_RULER)

#define PPATUI_NUM_LEAVES(...) _PP_NUMARG(...)/2


//python script:
//for i in range(0,64,2): print("#define _PPA_L%i(var,type,...) _PPATUI_LEAF(var,type) _PPA_L%i(__VA_ARGS__)" % (i+2, i))

#define PPATUI_LEAVES(...) _PPATUI_LHELPER1(_PP_NUMARG(__VA_ARGS__), __VA_ARGS__)
#define _PPATUI_LHELPER1(...) _PPATUI_LHELPER2(__VA_ARGS__)
#define _PPATUI_LHELPER2(N,...) _PPA_L##N(__VA_ARGS__)
#define _PPA_L0(...)
#define _PPA_L2(var,type,...) _PPATUI_LEAF(var,type) _PPA_L0(__VA_ARGS__)
#define _PPA_L4(var,type,...) _PPATUI_LEAF(var,type) _PPA_L2(__VA_ARGS__)
#define _PPA_L6(var,type,...) _PPATUI_LEAF(var,type) _PPA_L4(__VA_ARGS__)
#define _PPA_L8(var,type,...) _PPATUI_LEAF(var,type) _PPA_L6(__VA_ARGS__)
#define _PPA_L10(var,type,...) _PPATUI_LEAF(var,type) _PPA_L8(__VA_ARGS__)
#define _PPA_L12(var,type,...) _PPATUI_LEAF(var,type) _PPA_L10(__VA_ARGS__)
#define _PPA_L14(var,type,...) _PPATUI_LEAF(var,type) _PPA_L12(__VA_ARGS__)
#define _PPA_L16(var,type,...) _PPATUI_LEAF(var,type) _PPA_L14(__VA_ARGS__)
#define _PPA_L18(var,type,...) _PPATUI_LEAF(var,type) _PPA_L16(__VA_ARGS__)
#define _PPA_L20(var,type,...) _PPATUI_LEAF(var,type) _PPA_L18(__VA_ARGS__)
#define _PPA_L22(var,type,...) _PPATUI_LEAF(var,type) _PPA_L20(__VA_ARGS__)
#define _PPA_L24(var,type,...) _PPATUI_LEAF(var,type) _PPA_L22(__VA_ARGS__)
#define _PPA_L26(var,type,...) _PPATUI_LEAF(var,type) _PPA_L24(__VA_ARGS__)
#define _PPA_L28(var,type,...) _PPATUI_LEAF(var,type) _PPA_L26(__VA_ARGS__)
#define _PPA_L30(var,type,...) _PPATUI_LEAF(var,type) _PPA_L28(__VA_ARGS__)
#define _PPA_L32(var,type,...) _PPATUI_LEAF(var,type) _PPA_L30(__VA_ARGS__)
#define _PPA_L34(var,type,...) _PPATUI_LEAF(var,type) _PPA_L32(__VA_ARGS__)
#define _PPA_L36(var,type,...) _PPATUI_LEAF(var,type) _PPA_L34(__VA_ARGS__)
#define _PPA_L38(var,type,...) _PPATUI_LEAF(var,type) _PPA_L36(__VA_ARGS__)
#define _PPA_L40(var,type,...) _PPATUI_LEAF(var,type) _PPA_L38(__VA_ARGS__)
#define _PPA_L42(var,type,...) _PPATUI_LEAF(var,type) _PPA_L40(__VA_ARGS__)
#define _PPA_L44(var,type,...) _PPATUI_LEAF(var,type) _PPA_L42(__VA_ARGS__)
#define _PPA_L46(var,type,...) _PPATUI_LEAF(var,type) _PPA_L44(__VA_ARGS__)
#define _PPA_L48(var,type,...) _PPATUI_LEAF(var,type) _PPA_L46(__VA_ARGS__)
#define _PPA_L50(var,type,...) _PPATUI_LEAF(var,type) _PPA_L48(__VA_ARGS__)
#define _PPA_L52(var,type,...) _PPATUI_LEAF(var,type) _PPA_L50(__VA_ARGS__)
#define _PPA_L54(var,type,...) _PPATUI_LEAF(var,type) _PPA_L52(__VA_ARGS__)
#define _PPA_L56(var,type,...) _PPATUI_LEAF(var,type) _PPA_L54(__VA_ARGS__)
#define _PPA_L58(var,type,...) _PPATUI_LEAF(var,type) _PPA_L56(__VA_ARGS__)
#define _PPA_L60(var,type,...) _PPATUI_LEAF(var,type) _PPA_L58(__VA_ARGS__)
#define _PPA_L62(var,type,...) _PPATUI_LEAF(var,type) _PPA_L60(__VA_ARGS__)
#define _PPA_L64(var,type,...) _PPATUI_LEAF(var,type) _PPA_L62(__VA_ARGS__)
#define _PPA_L66(var,type,...) _PPATUI_LEAF(var,type) _PPA_L64(__VA_ARGS__)
#define _PPA_L68(var,type,...) _PPATUI_LEAF(var,type) _PPA_L66(__VA_ARGS__)
#define _PPA_L70(var,type,...) _PPATUI_LEAF(var,type) _PPA_L68(__VA_ARGS__)
#define _PPA_L72(var,type,...) _PPATUI_LEAF(var,type) _PPA_L70(__VA_ARGS__)
#define _PPA_L74(var,type,...) _PPATUI_LEAF(var,type) _PPA_L72(__VA_ARGS__)
#define _PPA_L76(var,type,...) _PPATUI_LEAF(var,type) _PPA_L74(__VA_ARGS__)
#define _PPA_L78(var,type,...) _PPATUI_LEAF(var,type) _PPA_L76(__VA_ARGS__)
#define _PPA_L80(var,type,...) _PPATUI_LEAF(var,type) _PPA_L78(__VA_ARGS__)
#define _PPA_L82(var,type,...) _PPATUI_LEAF(var,type) _PPA_L80(__VA_ARGS__)
#define _PPA_L84(var,type,...) _PPATUI_LEAF(var,type) _PPA_L82(__VA_ARGS__)
#define _PPA_L86(var,type,...) _PPATUI_LEAF(var,type) _PPA_L84(__VA_ARGS__)
#define _PPA_L88(var,type,...) _PPATUI_LEAF(var,type) _PPA_L86(__VA_ARGS__)
#define _PPA_L90(var,type,...) _PPATUI_LEAF(var,type) _PPA_L88(__VA_ARGS__)
#define _PPA_L92(var,type,...) _PPATUI_LEAF(var,type) _PPA_L90(__VA_ARGS__)
#define _PPA_L94(var,type,...) _PPATUI_LEAF(var,type) _PPA_L92(__VA_ARGS__)
#define _PPA_L96(var,type,...) _PPATUI_LEAF(var,type) _PPA_L94(__VA_ARGS__)
#define _PPA_L98(var,type,...) _PPATUI_LEAF(var,type) _PPA_L96(__VA_ARGS__)
#define _PPA_L100(var,type,...) _PPATUI_LEAF(var,type) _PPA_L98(__VA_ARGS__)
#define _PPA_L102(var,type,...) _PPATUI_LEAF(var,type) _PPA_L100(__VA_ARGS__)
#define _PPA_L104(var,type,...) _PPATUI_LEAF(var,type) _PPA_L102(__VA_ARGS__)
#define _PPA_L106(var,type,...) _PPATUI_LEAF(var,type) _PPA_L104(__VA_ARGS__)
#define _PPA_L108(var,type,...) _PPATUI_LEAF(var,type) _PPA_L106(__VA_ARGS__)
#define _PPA_L110(var,type,...) _PPATUI_LEAF(var,type) _PPA_L108(__VA_ARGS__)
#define _PPA_L112(var,type,...) _PPATUI_LEAF(var,type) _PPA_L110(__VA_ARGS__)
#define _PPA_L114(var,type,...) _PPATUI_LEAF(var,type) _PPA_L112(__VA_ARGS__)
#define _PPA_L116(var,type,...) _PPATUI_LEAF(var,type) _PPA_L114(__VA_ARGS__)
#define _PPA_L118(var,type,...) _PPATUI_LEAF(var,type) _PPA_L116(__VA_ARGS__)
#define _PPA_L120(var,type,...) _PPATUI_LEAF(var,type) _PPA_L118(__VA_ARGS__)
#define _PPA_L122(var,type,...) _PPATUI_LEAF(var,type) _PPA_L120(__VA_ARGS__)
#define _PPA_L124(var,type,...) _PPATUI_LEAF(var,type) _PPA_L122(__VA_ARGS__)
#define _PPA_L126(var,type,...) _PPATUI_LEAF(var,type) _PPA_L124(__VA_ARGS__)
#define _PPA_L128(var,type,...) _PPATUI_LEAF(var,type) _PPA_L126(__VA_ARGS__)





H(atom_common_table_header);

H(atom_rom_header_v2_2);
H(atom_master_data_table_v2_1);


// fuck me...
//H(atom_umc_reg_setting_data_block);


H(atom_vram_module_v10);
H(atom_vram_info_header_v2_4);

#endif
