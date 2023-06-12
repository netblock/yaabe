#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>


int main() {
	uint8_t numbits = 8;
	//uint64_t testnum = (1<<5) | (0b11<<10) | (0b111<<15) | (0b1111<<20);
	uint64_t testnum = 0;
	char pattern[16] = "0b%0";
	sprintf(pattern+4, "%02ub\n", numbits);
	printf(pattern, testnum);
}
