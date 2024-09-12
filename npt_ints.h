/*
Non-Power-of-Two integers
Current implementation requires little-endian
*/

#ifndef NPT_INTS_H
#define NPT_INTS_H

#pragma pack(push, 1)

typedef struct {
	uint16_t lo;
	uint8_t  hi;
} uint24_t;
typedef struct {
	int16_t lo;
	int8_t  hi;
} int24_t;

typedef struct {
	uint32_t lo;
	uint16_t hi;
} uint48_t;
typedef struct {
	int32_t lo;
	int16_t hi;
} int48_t;

#pragma pack(pop) // restore old packing

union npt_pt_pun {
    uint24_t u24;
    uint32_t u32;
    int24_t  s24;
    int32_t  s32;

    uint64_t u64;
    uint48_t u48;
    int64_t  s64;
    int48_t  s48;
}; 

// convert a power-of-two integer into its lesser non-power-of-two counterpart
// bits: lower 3/4
#define pt_to_npt_downgrade(pt_ptr) (_Generic((*(pt_ptr)),\
	uint32_t: (union npt_pt_pun) {.u32=*(pt_ptr)}.u24,\
	int32_t:  (union npt_pt_pun) {.s32=*(pt_ptr)}.s24,\
	\
	uint64_t: (union npt_pt_pun) {.u64=*(pt_ptr)}.u48,\
	int64_t:  (union npt_pt_pun) {.s64=*(pt_ptr)}.s48\
))

// convert a power-of-two integer into its greater non-power-of-two counterpart
// bits: 3/2
#define pt_to_npt_upgrade(pt_ptr) (_Generic((*(pt_ptr)),\
	uint16_t: (uint24_t) {.lo=*(pt_ptr)},\
	int16_t:  (int24_t)  {.lo=*(pt_ptr), .hi=0-(*(pt_ptr) < 0)},\
	\
	uint32_t: (uint48_t) {.lo=*(pt_ptr)},\
	int32_t:  (int48_t)  {.lo=*(pt_ptr), .hi=0-(*(pt_ptr) < 0)}\
))

// convert a non-power-of-two integer into its lesser power-of-two counterpart
// bits: lower 2/3
#define npt_to_pt_downgrade(npt_ptr) ((npt)->lo)

// convert a non-power-of-two integer into its greater power-of-two counterpart
// bits: 4/3
#define NPT_TO_PT_UPGRADE_NUM_REMAINING_BITS(npt_ptr)\
	( (sizeof((union npt_pt_pun){}.s64) - sizeof(*(npt_ptr))) * CHAR_BIT )
#define npt_to_pt_upgrade(npt_ptr) (_Generic( (*(npt_ptr)),\
	uint24_t: (union npt_pt_pun) {.u24=*(uint24_t*)(npt_ptr)}.u32,\
	uint48_t: (union npt_pt_pun) {.u48=*(uint48_t*)(npt_ptr)}.u64,\
	int24_t:  npt_to_pt_upgrade_signed(\
		(union npt_pt_pun) {.s24=*(int24_t*)(npt_ptr)},\
		NPT_TO_PT_UPGRADE_NUM_REMAINING_BITS(npt_ptr)\
	).s32,\
	int48_t:  npt_to_pt_upgrade_signed(\
		(union npt_pt_pun) {.s48=*(int48_t*)(npt_ptr)},\
		NPT_TO_PT_UPGRADE_NUM_REMAINING_BITS(npt_ptr)\
	).s64\
))

inline static union npt_pt_pun
npt_to_pt_upgrade_signed(
		union npt_pt_pun pun,
		uint8_t remaining_bits
		) {
	pun.s64 <<= remaining_bits;
	pun.s64 >>= remaining_bits;
	return pun;
}

#endif
