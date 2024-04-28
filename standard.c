#include "standard.h"

int64_t
strtoll_2(
		char8_t const* str
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
		char8_t const* str
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
		char8_t const* str
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

char8_t*
stopcopy(
		char8_t* restrict dest,
		char8_t const* restrict src
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
