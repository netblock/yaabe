#include "standard.h"

int64_t
strtoll_2(
		char const* str
		) {
	// TODO it seems the C2X's changes for the strto* hasn't landed yet
	uint8_t base = 0; // 0 = auto
	if ((str[0] == '0') && (str[1] == 'b')) {
		base = 2;
		str += 2;
	}
	return strtoll(str, NULL, base);
}
uint64_t
strtoull_2(
		char const* str
		) {
	// TODO it seems the C2X's changes for the strto* hasn't landed yet
	uint8_t base = 0; // 0 = auto
	if ((str[0] == '0') && (str[1] == 'b')) {
		base = 2;
		str += 2;
	}
	return strtoull(str, NULL, base);
}

bool
is_number(
		char const* str
		) {
	// test string if it's a decimal integer
	if (str) {
		do {
			if (0 == isdigit(*str)) {
				return false;
			}
			str++;
		} while (*str);
		return true;
	} else {
		return false;
	}
}

char*
stopcopy(
		char* restrict dest,
		char const* restrict src
		) {
	// custom stpcpy
	while(*src) {
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return dest;
}

bool
char_in_string(
		char const ch,
		char const* str
		) {
	while (*str) {
		if (ch == *str) {
			return true;
		}
		str++;
	}
	return false;
}

void
error_emit(
		struct error* const err,
		char const* const message
		) {
	err->message[0] = '\0';
	if (message) {
		memccpy(err->message, message, '\0', lengthof(err->message));
		err->message[lengthof(err->message)-1] = '\0';
		switch (err->severity) {
			case ERROR_WARNING:
				fprintf(stderr, "Warning: %s\n", err->message);
				break;
			case ERROR_ABORT:
				fprintf(stderr, "Error: %s\n", err->message);
				break;
			case ERROR_CRASH:
				fprintf(stderr, "Catastrophic error: %s\n", err->message);
				break;
			case NO_ERROR:
				break;
		};
	}
	switch (err->severity) {
		case ERROR_WARNING: return;
		case ERROR_ABORT: longjmp(err->env, 0);
		case ERROR_CRASH: abort();
		case NO_ERROR: return;
	};
}


void*
cralloc(
	size_t const size
	) {
	void* const ptr = malloc(size);
	if (ptr) {
		return ptr;
	}
	fprintf(stderr,
		"Catastrophic error: can't get memory from OS. Crashing.\n"
	);
	abort();
}
void*
crealloc(
	void* const old,
	size_t const size
	) {
	void* const ptr = realloc(old, size);
	if (ptr) {
		return ptr;
	}
	fprintf(stderr,
		"Catastrophic error: can't get memory from OS. Crashing.\n"
	);
	abort();
}
void*
cralloc0(
	size_t const size
	) {
	void* const ptr = calloc(1,size);
	if (ptr) {
		return ptr;
	}
	fprintf(stderr,
		"Catastrophic error: can't get memory from OS. Crashing.\n"
	);
	abort();
}


void
arena_init(
		struct mem_arena* const arena,
		size_t const arena_size,
		bool const zeroed
		) {
	if (zeroed) {
		arena->start = cralloc0(arena_size);
	} else {
		arena->start = cralloc(arena_size);
	}
	arena->pos = arena->start;
	arena->end = arena->start + arena_size;
}
void* arena_alloc(
		struct mem_arena* const arena,
		struct error* const err,
		size_t const alloc_size
		) {
	void* const old_pos = arena->pos;
	void* const new_pos = arena->pos + alloc_size;
	error_assert(err, ERROR_ABORT,
		"arena size too small",
		old_pos < arena->end
	);
	arena->pos = new_pos;
	return old_pos;
}

uint32_t
fletcher32(
		const void* data,
		size_t length
		) {
	const uint16_t* pptr = data;
	uint32_t c0 = 0;
	uint32_t c1 = 0;

	length = (length+1) & (~UINT64_C(1));

	while (length) {
		size_t block_length;
		if (length > (360*2)) {
			block_length = 360*2;
		} else {
			block_length = length;
		}
		length -= block_length;
		do {
			c0 += *(pptr++);
			c1 += c0;
			block_length -= 2;
		} while (block_length);
		c0 %= 0xFFFF;
		c1 %= 0xFFFF;
	}
	return (c1 << 16) | c0;
}
