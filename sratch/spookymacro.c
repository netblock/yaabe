#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct test {
	int a;
	int b;
	int c;
};
#define settest(ppa,ppb,ppc) {.a = ppa, .b=ppb, .c=ppc}
#define testplatform(args) settest args
#define spooks(s,v, pptest) s = (struct test) pptest##platform(v) ;




/*
for i in range(32): print("1,",end=''
for i in range(1,33): print("_%i," % (i), end='')
*/

//32+1 long
#define _PP_HASARGS_RULER \
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0

#define _PP_HASARGS_DEPTHCAN(\
_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32, N, ...) N

#define _PP_HASARGS_DEPTHCAN_HELPER(...) _PP_HASARGS_DEPTHCAN(__VA_ARGS__)
#define _PP_HASARGS(...)\
	_PP_HASARGS_DEPTHCAN_HELPER(__VA_ARGS__ __VA_OPT__(,) _PP_HASARGS_RULER)

/*
def atui_preprocessor_looper(depth=5, width=3):
	   name = "_ATUI_PPL%i"
	   widthcall = ""
	   for i in range(width):
			   widthcall += name + "("
	   widthcall += "__VA_ARGS__" + ")"*width
	   for i in range(depth):
			   body = widthcall % ((i+1,)*width)
			   print("#define %s(...) %s" % ( name%(i,) , body) )
	   print("#define %s(...) __VA_ARGS__" % (name%(i+1)))
*/
#define _ATUI_PPL(...) _ATUI_PPL0(__VA_ARGS__)
#define _ATUI_PPL0(...) _ATUI_PPL1(_ATUI_PPL1(_ATUI_PPL1(__VA_ARGS__)))
#define _ATUI_PPL1(...) _ATUI_PPL2(_ATUI_PPL2(_ATUI_PPL2(__VA_ARGS__)))
#define _ATUI_PPL2(...) _ATUI_PPL3(_ATUI_PPL3(_ATUI_PPL3(__VA_ARGS__)))
#define _ATUI_PPL3(...) _ATUI_PPL4(_ATUI_PPL4(_ATUI_PPL4(__VA_ARGS__)))
#define _ATUI_PPL4(...) _ATUI_PPL5(_ATUI_PPL5(_ATUI_PPL5(__VA_ARGS__)))
#define _ATUI_PPL5(...) __VA_ARGS__

#define _LCALL(func,common, ...) func(common, __VA_ARGS__)
//#define _LCALL(func,common, ...) OBS(_LCALL_INDI)(func)(common, __VA_ARGS__)
#define _LCALL_INDI(func) func
#define _C4N(fn,cm, a,b,c,d,...) _LCALL(fn,cm, a,b,c,d) _C4N(fn,cm,__VA_ARGS__)

#define EMPTY()
#define DEFER(empt) empt EMPTY()
#define OBS(func) func DEFER(EMPTY)()
#define OBS2(...) __VA_ARGS__
#define _1N_1(fn,cm,a,...) _LCALL(fn,cm,a)\
	OBS(_1N_INDIRECTN)(_PP_HASARGS(__VA_ARGS__))\
		(fn,cm, __VA_ARGS__)
#define _1N_0(...)
#define _1N_INDIRECTN(hasargs) _1N_##hasargs


#define _PPATUI_LOOPER(func, common, numargs, ...) \
	_ATUI_PPL( _1N_1(func, common, __VA_ARGS__))


#define ONES(c, a, ...) 1,
//#define ONES(c, a, ...) OBS(_PPL_IND)()(1) ,
#define _PPL_IND() _ATUI_PPL


int main() {
	int numarr[] = {_PPATUI_LOOPER(ONES ,NULL,1, 1,2,3,4,5)};
	printf("numarr count: %i\n", sizeof(numarr)/sizeof(int));

	struct test ttt;
	spooks(ttt, 
		(1,2,3),
		test
	)
	printf("%i %i %i\n", ttt.a, ttt.b, ttt.c);
	( & ttt ) ->a = 4;
	printf("%i %i %i\n", ttt.a, ttt.b, ttt.c);

	int ar[] = {7,6,5,4,3,2,1,0};
	int ar2[] = {};
	int* arr = ar;
	printf("%i ", *arr); arr+=1;
	printf("%i ", *arr); arr+=1;
	printf("%i \n", *arr); arr+=1;
	printf("%i\n", sizeof(ar2));
}


