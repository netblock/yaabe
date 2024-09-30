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
#include <setjmp.h>

#ifdef C2X_COMPAT
typedef uint8_t char8_t;
#define UINT64_WIDTH 64 //IEC_60559_BFP_EXT_C23
#else
#include <uchar.h>
#endif

#undef NULL
#define NULL nullptr

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
static_assert(sizeof(struct {uint32_t a; uint8_t b; float32_t c;}) == 9);
static_assert(sizeof(struct {int8_t a; uint64_t b; uint8_t c;}) == 10);
#pragma pack(pop)


#include "qnotation.h"
#include "npt_ints.h"

/******************************************************************************/

#define lengthof(array) (sizeof(array)/sizeof(array[0]))
#define sizeof_flex_array(array, count) (sizeof((array)[0]) * (count))
#define sizeof_flex(struct_p, array, count) (\
	offsetof(typeof(*(struct_p)), array)\
	+ sizeof_flex_array((struct_p)->array, count)\
)

#define fall __attribute__((fallthrough))
#define __unused __attribute__((unused))
#define __nonstring __attribute__((nonstring))

#if __has_attribute(counted_by)
# define __counted_by(member) __attribute__((counted_by__(member)))
#else
# define __counted_by(member)
#endif


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


enum error_severity:uint8_t {
	NO_ERROR      = 0,
	ERROR_WARNING = 1, // print a warning message and return
	ERROR_ABORT   = 2, // jongjump back to set destination
	ERROR_CRASH   = 3, // gracefully crash
};
struct error { // sorta intended to be a static variable
	char message[128];
	enum error_severity severity;
	jmp_buf env;
};
void // may not return
error_emit( // severity and message must be set before calling
		struct error* err
		);
// convienence macro meant to replace assert() ; msg can by dynamic
// The intent is an error/warning message system that would replace assert()
#define error_assert(errptr, sev, msg, test) do {\
	 if (!(test)) {\
		assert(test);\
		char* walker __unused = memccpy((errptr)->message, msg,\
			'\0', lengthof((errptr)->message)\
		);\
		assert(walker);\
		(errptr)->message[lengthof((errptr)->message)-1] = '\0';\
		\
		(errptr)->severity = sev;\
		error_emit(errptr);\
	}\
} while(0)


void*
cralloc( // crashes if not enough space
	size_t size
	);
void*
crealloc(
	void* old,
	size_t size
	);
void*
cralloc0( // zero-allocates
	size_t size
	);

struct mem_arena {
	void* start;
	void* pos;
	void* end;
};

void
arena_init( // initialise a new arena
		struct mem_arena* arena,
		size_t arena_size,
		bool zeroed
		);
void*
arena_alloc(
		struct mem_arena* arena,
		struct error* err, // required. Errors if here isn't enough room
		size_t alloc_size
		);

#endif
