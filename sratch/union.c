#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct A1 {
	int a;
};
struct A2 {
	int a;
	int b;
};
struct A3 {
	int a;
	int b;
	int c;
};

struct A {
	enum {a1=1, a2=2, a3=3} ver;
	union {
	struct A1 a1;
	struct A2 a2;
	struct A3 a3;
	};
};

struct B {
	struct A A;
};
int main() {
	struct B* bee = malloc(sizeof(struct B));
	bee->A.ver = a3;
	struct A* C = &(bee->A);
	bee->A.a3.c = 69;

	switch(bee->A.ver){
		case 3:
			printf("a3\n");
			bee->A.a3;
			printf("%d\n", C->a3.c);
			break;
		case a2:
			printf("a2\n");
			bee->A.a2;
			break;
		case a1:
			printf("a1\n");
			bee->A.a1;
			break;
	}
	free(bee);
}
