// https://en.wikipedia.org/wiki/Q_(number_format)

#ifndef QNOTATION_H
#define QNOTATION_H

#define Q_TO_FLOAT(fp_type, q_type) _Generic((q_type),\
	uq6_2_t: (((fp_type)q_type.integer) + ((fp_type)q_type.fraction)/2),\
	uq4_4_t: (((fp_type)q_type.integer) + ((fp_type)q_type.fraction)/4),\
\
	uq14_2_t: (((fp_type)q_type.integer) + ((fp_type)q_type.fraction)/2),\
	uq8_8_t: (((fp_type)q_type.integer) + ((fp_type)q_type.fraction)/8),\
\
	uq30_2_t: (((fp_type)q_type.integer) + ((fp_type)q_type.fraction)/2),\
	uq16_16_t: (((fp_type)q_type.integer) + ((fp_type)q_type.fraction)/16),\
	default: (fp_type)NAN\
)

// unsigned 8-bit
typedef union {
	uint8_t raw;
	struct { uint8_t
		fraction :1-0 +1,
		integer  :7-2 +1;
	};
} uq6_2_t;
typedef union {
	uint8_t raw;
	struct { uint8_t
		fraction :3-0 +1,
		integer  :7-4 +1;
	};
} uq4_4_t;

// unsigned 16-bit
typedef union {
	uint16_t raw;
	struct { uint16_t
		fraction :1-0 +1,
		integer :15-2 +1;
	};
} uq14_2_t;
typedef union {
	uint16_t raw;
	struct { uint16_t
		fraction :7-0 +1,
		integer :15-8 +1;
	};
} uq8_8_t;


// unsigned 32-bit
typedef union {
	uint32_t raw;
	struct { uint32_t
		fraction :1-0 +1,
		integer :31-2 +1;
	};
} uq30_2_t;
typedef union {
	uint32_t raw;
	struct { uint32_t
		fraction :15-0 +1,
		integer :31-16 +1;
	};
} uq16_16_t;



#pragma pack(push, 1)
struct _q_fourteen_bytes {
	// 8-bit
	uq6_2_t a;
	uq4_4_t b;

	// 16-bit
	uq14_2_t c;
	uq8_8_t d;

	// 32-bit
	uq30_2_t e;
	uq16_16_t f;
};
#pragma pack(pop)
static_assert(sizeof(struct _q_fourteen_bytes) == 14);

#endif
