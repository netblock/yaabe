#include "standard.h"

int64_t
strtoll_2(
		const char8_t* str
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
		const char8_t* str
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
		const char8_t* str
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
		const char8_t* restrict src
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

char8_t*
string_separate(
		char8_t** const restrict running,
		const char8_t* const restrict delimiters
		) {
	// custom strsep-like string tokenizer
	char8_t* const token = *running;
	if (**running) {
		do {
			for (size_t i = 0; delimiters[i]; i++) {
				if (delimiters[i] == **running) {
					**running = '\0';
					(*running)++;
					return token;
				}
			}
			(*running)++;
		} while (**running);
		return token;
	} else {
		return NULL;
	}
}
