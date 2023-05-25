#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define str(x) #x

struct thingy {
	int a;
	int b;
	int c;
};


struct thingy ttarray[] = {
	{.a=1, .b=2, .c=3},
	{.a=1, .b=2},
	{.a=1, .c=3},
};



typedef struct atui_branch_ atui_branch;
typedef struct atui_leaf_ atui_leaf;
struct atui_leaf_ {
    char name[40];
    char* description;
    uint8_t type;
    char fieldbits; //bitfield portion, if it's a bitfield
    union {
        void*     val;
        uint8_t*  u8;
        uint16_t* u16;
        uint32_t* u32;
        uint64_t* u64;
    };
};
struct  atui_branch_ {
    char name[40];
    char* description;

    atui_branch** child_branches;
    int branch_count;

    atui_leaf* leaves;
    int leaf_count;

    void* atomleaves;
};

struct atom_test { // pretend this is from like atomfirmware.h
    uint32_t antiem;
    uint32_t otheritem;
    uint8_t smolthing;
    uint16_t twobytes;
    uint16_t twobytes1;
    uint16_t twobytes2;
    uint16_t twobytes3;
    uint16_t twobytes4;
    uint16_t twobytes5;
    uint16_t twobytes6;
    uint16_t twobytes7;
    uint16_t twobytes8;
    uint16_t twobytes9;
    uint16_t twobytes10;
};
struct atom_test atest = { //pretend vals from bios
    .antiem = 1, \
    .otheritem = 3, \
    .smolthing = 5, \
    .twobytes = 7,  \
    .twobytes1 = 11 , \
    .twobytes2 = 13 , \
    .twobytes3 = 17 , \
    .twobytes4 = 19 , \
    .twobytes5 = 23 , \
    .twobytes6 = 29 , \
    .twobytes7 = 31 , \
    .twobytes8 = 37 , \
    .twobytes9 = 41 , \
    .twobytes10 = 43 , \
};

/*
https://stackoverflow.com/questions/319328/how-to-write-a-while-loop-with-the-c-preprocessor
https://stackoverflow.com/questions/12447557/can-we-have-recursive-macros
https://gcc.gnu.org/onlinedocs/cpp/index.html#SEC_Contents
https://stackoverflow.com/questions/11317474/macro-to-count-number-of-arguments
*/

#define ATUI_LEAF_TYPE(var) _Generic((var), \
    uint8_t:8, uint16_t:16, uint32_t:32, uint64_t:64, default:1)
//#define LEAF(var) {.val=&(X.var), .name=#var, .type=ATUI_LEAF_TYPE(X.var)},
#define LEAF(var) {.val=&(bios->var), .name=#var, .type=ATUI_LEAF_TYPE(bios->var)},

//#define funcify(name, L, B) 
#define ATUI_FUNCIFY(PP_NAME) \
static inline atui_branch* _##PP_NAME##_atui(struct PP_NAME * bios, \
		int num_branches, atui_branch** import_children) { \
	int i = 0;/*loops*/  \
	atui_branch* table = malloc(sizeof(atui_branch) + \
		num_branches * sizeof(atui_branch*) + \
		PP_NUM_ARG(FUNC_LEAVES) * sizeof(atui_leaf) \
	); \
\
	atui_branch** branches = NULL; \
	if (num_branches) { \
		branches = (atui_branch**)(table + sizeof(atui_branch)); \
		if (import_children != NULL) { \
			for (i=0; i<num_branches; i++) { \
				branches[i] = import_children[i]; \
			} \
		} \
	} \
\
	atui_leaf* leaves = NULL; \
	if(PP_NUM_ARG(FUNC_LEAVES)) { \
		leaves = (atui_leaf*)(table + sizeof(atui_branch) + \
		num_branches * sizeof(atui_branch*) ); \
		atui_leaf leavinit[] = {LEAVES(FUNC_LEAVES)};\
		for (i=PP_NUM_ARG(FUNC_LEAVES); i--; ) {\
			leaves[i] = leavinit[i]; \
		}; \
	/*memcpy(leaves, leavinit, PP_NUM_ARG(FUNC_LEAVES)*sizeof(atui_leaf));*/ \
	} \
\
    *table = (atui_branch) { \
		.name=#PP_NAME, \
		.leaves=leaves, .leaf_count=PP_NUM_ARG(FUNC_LEAVES), .atomleaves=bios, \
		.child_branches=branches, .branch_count=num_branches \
	}; \
	return table; \
}
/*
	atui_leaf leavinit[] = {LEAF(twobytes6) LEAF(twobytes7)};\
}
*/

/*
//#define ar(a, ...)  __VA_OPT__(+1, ar2(__VA_ARGS__))
//#define ar(n, ...) char _c_##__VA_ARGS__##; n = sizeof({_c_##__VA_ARGS__})/sizeof(char);
#define ar(num,...) atui_leaf ppname[] = {{.name=#__VA_ARGS__}};
//#define ar2(num,...) char __VA_ARGS__; num = sizeof({__VA_ARGS__})/sizeof(char)
*/

// Throw the to-be-counted args into the depthcan and then measure the how
// full the depthcan is with the depthstick.
// Scale both dipstick and depthcan if you want to count more than 63 args.
#define PP_ARGCOUNTER_DIPSTICK \
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
	PP_ARGCOUNTER_DEPTHCAN(__VA_ARGS__ __VA_OPT__(,) PP_ARGCOUNTER_DIPSTICK)

#define LEF(...) LEF_H1(PP_NUM_ARG(__VA_ARGS__), __VA_ARGS__)
#define LEF_H1(...) LEF_H2(__VA_ARGS__)
#define LEF_H2(N,...) LE##N(__VA_ARGS__)
#define LE4(_1,_2,_3,_4,...) 420
#define LE5(...) 69


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


//for i in range(0,63): print("#define L%i(var,...) LEAF(var) L%i(__VA_ARGS__)" % (i+1, i))

//put all into header

// DONT HAVE A TRAILING COMMA
#define FUNC_LEAVES antiem, otheritem
ATUI_FUNCIFY(atom_test)
#undef FUNC_LEAVES

struct atom_test2;
#define FUNC_LEAVES
ATUI_FUNCIFY(atom_test2)



int main(){
	struct thingy ttone;
	struct thingy* ttwo = &ttone;
	*ttwo = (struct thingy){.a=1, .b=2, .c=3};

	int num = 0;
	num = LEF(3,2,5,6,8);
	printf("%d\n",num);
	num = LEF(a,b,c,d,); //note trailing comma
	printf("%d\n",num);
	num = LEF(a,b,c,d);
	printf("%d\n",num);

	printf("\n");
	atui_branch* br = _atom_test_atui(NULL,1, NULL);
	br->child_branches[0] =  _atom_test2_atui(NULL,0, NULL);
	printf("%s\n%s\n%s\n", br->name, br->leaves[1].name, 
		br->child_branches[0]->name);

	//num = PP_NUM_ARG(3,2,5,6);
	//num = PP_NUM_ARG(a,b,c);
	//num = PP_NUM_ARG();
}
