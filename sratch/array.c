#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>


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

struct listofthingies {
	int i;
	struct thingy dada[];
};

struct listofthingies instance = {
	.i = 3,
	.dada = {
		{.a=1, .b=2, .c=3},
		{.a=1, .b=2},
		{.a=1, .c=3},
	}
};

#define strtype(var) _Generic((var), int:"intgr", default:"other")
#define set(var) {.val=&(X.var), .name=#var, .type=strtype(X.var)},

struct printable {
	void* val;
	char name[64];
	char type[64];
};

#define X ttarray[0]
struct printable instance2[] = {
	 set(a)
	 set(b)
};
#undef X

int main(){
	printf("Name: %s .\n", instance2[1].name);
	printf("Type: %s .\n", instance2[1].type);
}
