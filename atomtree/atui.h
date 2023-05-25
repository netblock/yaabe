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

typedef struct atui_branch_ atui_branch;
typedef struct atui_leaf_ atui_leaf;
struct atui_leaf_ {
	char name[40];
	char* description;
	int type;
	char fieldbits; //bitfield portion, if it's a bitfield
	union {
		void*     val;
		uint8_t*  u8;
		uint16_t* u16;
		uint32_t* u32;
		uint64_t* u64;
	};
	void* auxilary;
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

#define ATUI_LEAF_TYPE(var) _Generic((var), \
	uint8_t*:-1, \
	uint8_t:8, uint16_t:16, uint32_t:32, uint64_t:64, \
	default:1\
)

#define LEAF(var) {.val=&(bios->var), .name=#var, .type=ATUI_LEAF_TYPE(bios->var)},


#define ATUI_FUNC_NAME(PP_NAME) \
atui_branch* _##PP_NAME##_atui(struct PP_NAME * bios, unsigned int num_branches, atui_branch** import_children)

#define H(PP_NAME) ATUI_FUNC_NAME(PP_NAME)
#define ATUI_MAKE_BRANCH(PP_NAME, bios, num_branches, children) _##PP_NAME##_atui(bios, num_branches, children)

#define ATUI_FUNCIFY(PP_NAME, ...) \
ATUI_FUNC_NAME(PP_NAME) { \
	int i = 0; \
	void* scratch;\
\
	atui_branch* table = NULL; \
	scratch = malloc( \
		sizeof(atui_branch) + \
		(sizeof(atui_branch*) * num_branches) +  \
		(sizeof(atui_leaf) * PP_NUM_ARG(__VA_ARGS__)) \
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
	if(PP_NUM_ARG(__VA_ARGS__)) { \
		leaves = scratch;\
		atui_leaf leavinit[] = {LEAVES(__VA_ARGS__)};\
		for(i=0; i < PP_NUM_ARG(__VA_ARGS__); i++) {\
			leaves[i] = leavinit[i]; \
		}\
	} \
\
	*table = (atui_branch) { \
		.name=#PP_NAME,.leaves=(atui_leaf*)leaves,\
		.leaf_count=PP_NUM_ARG(__VA_ARGS__), .atomleaves=bios, \
		.child_branches=branches, .branch_count=num_branches \
	}; \
	return table; \
}



// Throw the to-be-counted args into the depthcan and then measure the how
// full the depthcan is with the depthstick.
// Scale both ruler and depthcan if you want to count more than 63 args.
#define PP_ARGCOUNTER_RULER \
	63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40, \
	39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16, \
	15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0
#define PP_ARGCOUNTER_DEPTHCAN_( \
	_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
	_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38, \
	_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56, \
	_57,_58,_59,_60,_61,_62,_63,N,...) N
#define PP_ARGCOUNTER_DEPTHCAN(...) PP_ARGCOUNTER_DEPTHCAN_(__VA_ARGS__)
#define PP_NUM_ARG(...) \
	PP_ARGCOUNTER_DEPTHCAN(__VA_ARGS__ __VA_OPT__(,) PP_ARGCOUNTER_RULER)


//python script:
//for i in range(0,63): print("#define L%i(var,...) LEAF(var) L%i(__VA_ARGS__)" % (i+1, i))

#define LEAVES(...) LEAVES_HELPER1(PP_NUM_ARG(__VA_ARGS__), __VA_ARGS__)
#define LEAVES_HELPER1(...) LEAVES_HELPER2(__VA_ARGS__)
#define LEAVES_HELPER2(N,...) L##N(__VA_ARGS__)
#define L0(...)
#define L1(var,...) LEAF(var)
#define L2(var,...) LEAF(var) L1(__VA_ARGS__)
#define L3(var,...) LEAF(var) L2(__VA_ARGS__)
#define L4(var,...) LEAF(var) L3(__VA_ARGS__)
#define L5(var,...) LEAF(var) L4(__VA_ARGS__)
#define L6(var,...) LEAF(var) L5(__VA_ARGS__)
#define L7(var,...) LEAF(var) L6(__VA_ARGS__)
#define L8(var,...) LEAF(var) L7(__VA_ARGS__)
#define L9(var,...) LEAF(var) L8(__VA_ARGS__)
#define L10(var,...) LEAF(var) L9(__VA_ARGS__)
#define L11(var,...) LEAF(var) L10(__VA_ARGS__)
#define L12(var,...) LEAF(var) L11(__VA_ARGS__)
#define L13(var,...) LEAF(var) L12(__VA_ARGS__)
#define L14(var,...) LEAF(var) L13(__VA_ARGS__)
#define L15(var,...) LEAF(var) L14(__VA_ARGS__)
#define L16(var,...) LEAF(var) L15(__VA_ARGS__)
#define L17(var,...) LEAF(var) L16(__VA_ARGS__)
#define L18(var,...) LEAF(var) L17(__VA_ARGS__)
#define L19(var,...) LEAF(var) L18(__VA_ARGS__)
#define L20(var,...) LEAF(var) L19(__VA_ARGS__)
#define L21(var,...) LEAF(var) L20(__VA_ARGS__)
#define L22(var,...) LEAF(var) L21(__VA_ARGS__)
#define L23(var,...) LEAF(var) L22(__VA_ARGS__)
#define L24(var,...) LEAF(var) L23(__VA_ARGS__)
#define L25(var,...) LEAF(var) L24(__VA_ARGS__)
#define L26(var,...) LEAF(var) L25(__VA_ARGS__)
#define L27(var,...) LEAF(var) L26(__VA_ARGS__)
#define L28(var,...) LEAF(var) L27(__VA_ARGS__)
#define L29(var,...) LEAF(var) L28(__VA_ARGS__)
#define L30(var,...) LEAF(var) L29(__VA_ARGS__)
#define L31(var,...) LEAF(var) L30(__VA_ARGS__)
#define L32(var,...) LEAF(var) L31(__VA_ARGS__)
#define L33(var,...) LEAF(var) L32(__VA_ARGS__)
#define L34(var,...) LEAF(var) L33(__VA_ARGS__)
#define L35(var,...) LEAF(var) L34(__VA_ARGS__)
#define L36(var,...) LEAF(var) L35(__VA_ARGS__)
#define L37(var,...) LEAF(var) L36(__VA_ARGS__)
#define L38(var,...) LEAF(var) L37(__VA_ARGS__)
#define L39(var,...) LEAF(var) L38(__VA_ARGS__)
#define L40(var,...) LEAF(var) L39(__VA_ARGS__)
#define L41(var,...) LEAF(var) L40(__VA_ARGS__)
#define L42(var,...) LEAF(var) L41(__VA_ARGS__)
#define L43(var,...) LEAF(var) L42(__VA_ARGS__)
#define L44(var,...) LEAF(var) L43(__VA_ARGS__)
#define L45(var,...) LEAF(var) L44(__VA_ARGS__)
#define L46(var,...) LEAF(var) L45(__VA_ARGS__)
#define L47(var,...) LEAF(var) L46(__VA_ARGS__)
#define L48(var,...) LEAF(var) L47(__VA_ARGS__)
#define L49(var,...) LEAF(var) L48(__VA_ARGS__)
#define L50(var,...) LEAF(var) L49(__VA_ARGS__)
#define L51(var,...) LEAF(var) L50(__VA_ARGS__)
#define L52(var,...) LEAF(var) L51(__VA_ARGS__)
#define L53(var,...) LEAF(var) L52(__VA_ARGS__)
#define L54(var,...) LEAF(var) L53(__VA_ARGS__)
#define L55(var,...) LEAF(var) L54(__VA_ARGS__)
#define L56(var,...) LEAF(var) L55(__VA_ARGS__)
#define L57(var,...) LEAF(var) L56(__VA_ARGS__)
#define L58(var,...) LEAF(var) L57(__VA_ARGS__)
#define L59(var,...) LEAF(var) L58(__VA_ARGS__)
#define L60(var,...) LEAF(var) L59(__VA_ARGS__)
#define L61(var,...) LEAF(var) L60(__VA_ARGS__)
#define L62(var,...) LEAF(var) L61(__VA_ARGS__)
#define L63(var,...) LEAF(var) L62(__VA_ARGS__)





H(atom_common_table_header);

H(atom_rom_header_v2_2);
H(atom_master_data_table_v2_1);


// fuck me...
//H(atom_umc_reg_setting_data_block);


H(atom_vram_module_v10);
H(atom_vram_info_header_v2_4);

#endif
