#include "standard.h"

#include <execinfo.h>

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
		struct error* const err
		) {
	if (strlen(err->message)) {
		switch (err->severity) {
			case ERROR_WARNING:
				fprintf(stderr, "warning: %s\n", err->message);
				break;
			case ERROR_ABORT:
				fprintf(stderr, "error: %s\n", err->message);
				break;
			case ERROR_CRASH:
				fprintf(stderr, "catastrophic error: %s\n", err->message);
				fprintf(stderr, "backtrace:\n");
				err->num_history = backtrace(
					err->bt_history, lengthof(err->bt_history)
				);
				backtrace_symbols_fd(
					err->bt_history, err->num_history,
					STDERR_FILENO
				);
				break;
			case NO_ERROR:
				break;
		};
	}
	switch (err->severity) {
		case ERROR_WARNING: return;
		case ERROR_ABORT: longjmp(err->env, 0);
		case ERROR_CRASH: exit(ERROR_CRASH);
		case NO_ERROR: return;
	};
}
