#include "standard.h"
#include "pci_id_lut.h"


int16_t
atomtree_pci_id_bsearch_left(
		struct atomtree_pci_id const* const pci_id_lut,
		uint16_t const pci_id_lut_length,
		union pci_ids_pun const ids
		) {
	// binary search for register_set
	// as a result, it assumes the array is sorted.
	// this algo also finds the leftmost if there are duplicates

	// reserve leftmost bit as flag

	uint16_t left = 0;
	uint16_t mid;
	uint16_t right = pci_id_lut_length;
	while (left != right) {
		mid = (left + right) >> 1;  // bitshift div-by-2
		if (ids.device_vendor <= pci_id_lut[mid].ids.device_vendor) {
			right = mid;
		} else {
			left = mid + 1;
		}
	}
	// left==right. mid will be off by 1, leftwise, if it's unique.
	if (ids.device_vendor == pci_id_lut[left].ids.device_vendor) {
		return left;
	} else {
		return -1;
	}
}

enum amd_asic_type
get_amd_chip_from_pci_id(
		uint16_t const vendor,
		uint16_t const device
		) {
	int16_t const index = atomtree_pci_id_bsearch_left(
		amd_pci_ids, lengthof(amd_pci_ids),
		(union pci_ids_pun const) {.vendor=vendor, .device=device}
	);
	if (-1 < index) {
		return amd_pci_ids[index].chip;
	} else {
		return CHIP_UNKNOWN;
	}
}
