#include "atomtree.h"

uint8_t
assert_reg_index(
		const struct atom_init_reg_index_format* const index,
		const uint16_t* const expectation
		) {
	for (uint8_t i=0; expectation[i] != END_OF_REG_INDEX_BLOCK; i++) {
		if (index[i].RegIndex != expectation[i]) {
			return 0;
		}
	}
	return 1;
}
