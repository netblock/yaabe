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


int main() {
	struct test ttt;
	spooks(ttt, 
		(1,2,3),
		test
	)

	printf("%i %i %i\n", ttt.a, ttt.b, ttt.c);
	( & ttt ) ->a = 1;
	printf("%i %i %i\n", ttt.a, ttt.b, ttt.c);
}
