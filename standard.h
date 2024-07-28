/*
Standard includes, and checks of those standards.
Also generic functions that would be in a standard.
*/
#ifndef STANDARD_H
#define STANDARD_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <assert.h>
#include <ctype.h>

#ifdef C2X_COMPAT
typedef uint8_t char8_t;
#else
#include <uchar.h>
#endif

// weird bugs with sprintf when using _Floatn, but as long as we can assert...
// float/double will be fine.
typedef _Float16 float16_t;
//typedef _Float32 float32_t;
//typedef _Float64 float64_t;
typedef float float32_t;
typedef double float64_t;
//typedef _Float128 float128_t; // currently unnecessary

// we're dealing with a byte-packed little-endian ABI.
static_assert(__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__);
static_assert(CHAR_BIT == 8);
static_assert(sizeof(char) == 1);
static_assert(sizeof(char8_t) == 1);
static_assert(sizeof(uint8_t) == 1);
static_assert(sizeof(uint16_t) == 2);
static_assert(sizeof(uint32_t) == 4);
static_assert(sizeof(uint64_t) == 8);
static_assert(sizeof(int8_t) == 1);
static_assert(sizeof(int16_t) == 2);
static_assert(sizeof(int32_t) == 4);
static_assert(sizeof(int64_t) == 8);
static_assert(sizeof(float16_t) == 2);
static_assert(sizeof(float32_t) == 4);
static_assert(sizeof(float64_t) == 8);
//static_assert(sizeof(float128_t) == 16);
#pragma pack(push, 1)
struct _ninebytes { uint32_t a; uint8_t b; float32_t c; };
struct _tenbytes { int8_t a; uint64_t b; uint8_t c; };
#pragma pack(pop)
static_assert(sizeof(struct _ninebytes) == 9);
static_assert(sizeof(struct _tenbytes) == 10);



#include "qnotation.h"

/******************************************************************************/

#define lengthof(array) (sizeof(array)/sizeof(array[0]))

#define __unused __attribute__((unused))

// TODO stroll that considers 0b prefix?
int64_t
strtoll_2(
		char const* str
		);
uint64_t
strtoull_2(
		char const* str
		);

bool
is_number( // test string if it's a decimal integer
		char const* str
		);

char*
stopcopy( // stpcpy; copy string, returns pointer to \0
		char* restrict dest,
		char const* restrict src
		);
bool
char_in_string( // test if character ch appears anywhere in string
		char ch,
		char const* str
		);

#endif
