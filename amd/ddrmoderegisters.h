// Please refer to JESD 250 C. If unavailable consider,
// 2204251615_Samsung-K4Z80325BC-HC14_C2920181.pdf

struct gddr6_mr0 {
	uint16_t WLmrs : 3; // tCWL, 8,9,10,11,12,5,6,7
	uint16_t RLmrs : 4; // tCL, starting from 5. Consider MR8 OP8, MR12 OP3.
	uint16_t TM    : 1; // Test mode
	uint16_t WR    : 4; // tWR, starting from 4
	uint16_t ID    : 4; // MR 0
};

struct gddr6_mr1 {
	uint16_t drive_stren  :1-0 +1; //0=AC60/40 1=AC48/40 2,3 vender specific
	uint16_t data_term    :3-2 +1; //0=disabled 1=60ohm 2=120ohm 3=48ohm
	uint16_t PLLDLL_range :5-4 +1; //min-to-max WCK freq; vendor specific
	uint16_t calib_update :6-6 +1; //calibration engine; 0=enabled 1=disabled
	uint16_t PLLDLL       :7-7 +1; //0=disabled 1=enabled
	uint16_t RDBI         :8-8 +1; //Data Bus Inversion, for reads.  0=enabled
	uint16_t WDBI         :9-9 +1; //Data Bus Inversion, for writes. 1=disabled
	uint16_t CABI        :10-10 +1; //Command-address bus inversion.  0=enabled
	uint16_t PLLDLL_reset:14-11 +1; //1 = reset. self-clears after reset.
	uint16_t ID           :15-12 +1; //MR 1
};


struct gddr6_mr2 {
	uint16_t OCD_up   : 3; // output driver pullup offset. Has Two's Complement
	uint16_t OCD_down : 3; // pulldown. vndr speific. -=decrease +=increase
}
