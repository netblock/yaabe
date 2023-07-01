#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct abc {
	int a;
	int b;
	int c;
};
struct def {
	int d;
	int e;
	int f;
};

struct abc* func1(struct def* inpt) {
	struct abc* AAA = malloc(sizeof(struct abc));
	AAA->a = inpt->d * 1;
	AAA->b = inpt->e * 1;
	AAA->c = inpt->f * 1;
	return AAA;
}
struct abc* func2(struct def* inpt) {
	struct abc* AAA = malloc(sizeof(struct abc));
	AAA->a = inpt->d * 2;
	AAA->b = inpt->e * 2;
	AAA->c = inpt->f * 2;
	return AAA;
}
struct abc* func3(struct def* inpt) {
	struct abc* AAA = malloc(sizeof(struct abc));
	AAA->a = inpt->d * 3;
	AAA->b = inpt->e * 3;
	AAA->c = inpt->f * 3;
	return AAA;
}

struct abc* (*funcarray[])(struct def*) = {func3, func2, func1};
void* vptr = &(*(int*)0);
int main() {
	printf("%p\n", vptr);
}


