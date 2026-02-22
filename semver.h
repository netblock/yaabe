/*
A semantic versioning interface
V(major, minor, patch)
minor and patch are optional
V(1,0,0) == V(1,0) == V(1); means v1.0.0
*/

#ifndef SEMVER_H
#define SEMVER_H

// use enum? populating MMP triplets eats >1000 lines
typedef union semantic_version {
	uint32_t ver; // to be used against the V() macro
	struct {
		uint8_t patch;
		uint8_t minor;
		uint8_t major;
		uint8_t unused;
	};
} semver;
static_assert(sizeof(semver) == sizeof((semver){}.ver));

#define SET_VER(...) SET_SEMVER_VAL(__VA_ARGS__, 0,0,0)
#define SET_SEMVER_VAL(maj, min, pat, ...) (\
	(semver) {.major=maj, .minor=min, .patch=pat}\
)

#define V(...) SEMVER_VAL(__VA_ARGS__, 0,0,0)
#define _SEMVER_SHIFT(val, field) (\
	((uint32_t)(val & UINT8_MAX)) << (offsetof(semver, field) * CHAR_BIT)\
)
#define SEMVER_VAL(maj, min, pat, ...) (\
	  _SEMVER_SHIFT(maj, major)\
	| _SEMVER_SHIFT(min, minor)\
	| _SEMVER_SHIFT(pat, patch)\
)

static semver const ALT_NOVER = {.ver=V(-1,-1,-1)};

/* python dirtyscript for pretty format
s=''
substr = ""
sub_vers = ()
n_per_line=4
for maj in range(20):
    for min in range(12//n_per_line):
        substr = ""
        for min_sub in range(n_per_line):
            sub_vers = (maj, min*n_per_line + min_sub)
            substr += "v%u_%u" % sub_vers
            substr += " " * ((10 > (min*n_per_line + min_sub)) + (10 > maj))
            substr += "=V(%2u,%2u),   " % sub_vers
        s += "\t"+substr.strip()+"\n"

print(s)

s=''
substr = ""
sub_vers = ()
n_per_line=3
for maj in range(16):
    for min in range(16):
        for pat in range(16//n_per_line):
            substr = ""
            for pat_sub in range(n_per_line):
                sub_vers = (maj, min, pat*n_per_line + pat_sub)
                substr += "v%u_%u_%u" % sub_vers
                substr += " " * ((10 > (pat*n_per_line + pat_sub)) + (10 > maj) + (10 > min))
                substr += "=V(%2u,%2u,%2u),   " % sub_vers
            s += "\t" + substr.strip()+"\n"

print(s)
*/
/*
enum semantic_version_names:uint32_t {
	nover=0,
	v1=1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,

	v1_0  =V( 1, 0),   v1_1  =V( 1, 1),   v1_2  =V( 1, 2),   v1_3  =V( 1, 3),
	v1_4  =V( 1, 4),   v1_5  =V( 1, 5),   v1_6  =V( 1, 6),   v1_7  =V( 1, 7),
	v1_8  =V( 1, 8),   v1_9  =V( 1, 9),   v1_10 =V( 1,10),   v1_11 =V( 1,11),
	v2_0  =V( 2, 0),   v2_1  =V( 2, 1),   v2_2  =V( 2, 2),   v2_3  =V( 2, 3),
	v2_4  =V( 2, 4),   v2_5  =V( 2, 5),   v2_6  =V( 2, 6),   v2_7  =V( 2, 7),
	v2_8  =V( 2, 8),   v2_9  =V( 2, 9),   v2_10 =V( 2,10),   v2_11 =V( 2,11),
	v3_0  =V( 3, 0),   v3_1  =V( 3, 1),   v3_2  =V( 3, 2),   v3_3  =V( 3, 3),
	v3_4  =V( 3, 4),   v3_5  =V( 3, 5),   v3_6  =V( 3, 6),   v3_7  =V( 3, 7),
	v3_8  =V( 3, 8),   v3_9  =V( 3, 9),   v3_10 =V( 3,10),   v3_11 =V( 3,11),
	v4_0  =V( 4, 0),   v4_1  =V( 4, 1),   v4_2  =V( 4, 2),   v4_3  =V( 4, 3),
	v4_4  =V( 4, 4),   v4_5  =V( 4, 5),   v4_6  =V( 4, 6),   v4_7  =V( 4, 7),
	v4_8  =V( 4, 8),   v4_9  =V( 4, 9),   v4_10 =V( 4,10),   v4_11 =V( 4,11),
	v5_0  =V( 5, 0),   v5_1  =V( 5, 1),   v5_2  =V( 5, 2),   v5_3  =V( 5, 3),
	v5_4  =V( 5, 4),   v5_5  =V( 5, 5),   v5_6  =V( 5, 6),   v5_7  =V( 5, 7),
	v5_8  =V( 5, 8),   v5_9  =V( 5, 9),   v5_10 =V( 5,10),   v5_11 =V( 5,11),
	v6_0  =V( 6, 0),   v6_1  =V( 6, 1),   v6_2  =V( 6, 2),   v6_3  =V( 6, 3),
	v6_4  =V( 6, 4),   v6_5  =V( 6, 5),   v6_6  =V( 6, 6),   v6_7  =V( 6, 7),
	v6_8  =V( 6, 8),   v6_9  =V( 6, 9),   v6_10 =V( 6,10),   v6_11 =V( 6,11),
	v7_0  =V( 7, 0),   v7_1  =V( 7, 1),   v7_2  =V( 7, 2),   v7_3  =V( 7, 3),
	v7_4  =V( 7, 4),   v7_5  =V( 7, 5),   v7_6  =V( 7, 6),   v7_7  =V( 7, 7),
	v7_8  =V( 7, 8),   v7_9  =V( 7, 9),   v7_10 =V( 7,10),   v7_11 =V( 7,11),
	v8_0  =V( 8, 0),   v8_1  =V( 8, 1),   v8_2  =V( 8, 2),   v8_3  =V( 8, 3),
	v8_4  =V( 8, 4),   v8_5  =V( 8, 5),   v8_6  =V( 8, 6),   v8_7  =V( 8, 7),
	v8_8  =V( 8, 8),   v8_9  =V( 8, 9),   v8_10 =V( 8,10),   v8_11 =V( 8,11),
	v9_0  =V( 9, 0),   v9_1  =V( 9, 1),   v9_2  =V( 9, 2),   v9_3  =V( 9, 3),
	v9_4  =V( 9, 4),   v9_5  =V( 9, 5),   v9_6  =V( 9, 6),   v9_7  =V( 9, 7),
	v9_8  =V( 9, 8),   v9_9  =V( 9, 9),   v9_10 =V( 9,10),   v9_11 =V( 9,11),
	v10_0 =V(10, 0),   v10_1 =V(10, 1),   v10_2 =V(10, 2),   v10_3 =V(10, 3),
	v10_4 =V(10, 4),   v10_5 =V(10, 5),   v10_6 =V(10, 6),   v10_7 =V(10, 7),
	v10_8 =V(10, 8),   v10_9 =V(10, 9),   v10_10=V(10,10),   v10_11=V(10,11),
	v11_0 =V(11, 0),   v11_1 =V(11, 1),   v11_2 =V(11, 2),   v11_3 =V(11, 3),
	v11_4 =V(11, 4),   v11_5 =V(11, 5),   v11_6 =V(11, 6),   v11_7 =V(11, 7),
	v11_8 =V(11, 8),   v11_9 =V(11, 9),   v11_10=V(11,10),   v11_11=V(11,11),
	v12_0 =V(12, 0),   v12_1 =V(12, 1),   v12_2 =V(12, 2),   v12_3 =V(12, 3),
	v12_4 =V(12, 4),   v12_5 =V(12, 5),   v12_6 =V(12, 6),   v12_7 =V(12, 7),
	v12_8 =V(12, 8),   v12_9 =V(12, 9),   v12_10=V(12,10),   v12_11=V(12,11),
	v13_0 =V(13, 0),   v13_1 =V(13, 1),   v13_2 =V(13, 2),   v13_3 =V(13, 3),
	v13_4 =V(13, 4),   v13_5 =V(13, 5),   v13_6 =V(13, 6),   v13_7 =V(13, 7),
	v13_8 =V(13, 8),   v13_9 =V(13, 9),   v13_10=V(13,10),   v13_11=V(13,11),
	v14_0 =V(14, 0),   v14_1 =V(14, 1),   v14_2 =V(14, 2),   v14_3 =V(14, 3),
	v14_4 =V(14, 4),   v14_5 =V(14, 5),   v14_6 =V(14, 6),   v14_7 =V(14, 7),
	v14_8 =V(14, 8),   v14_9 =V(14, 9),   v14_10=V(14,10),   v14_11=V(14,11),
	v15_0 =V(15, 0),   v15_1 =V(15, 1),   v15_2 =V(15, 2),   v15_3 =V(15, 3),
	v15_4 =V(15, 4),   v15_5 =V(15, 5),   v15_6 =V(15, 6),   v15_7 =V(15, 7),
	v15_8 =V(15, 8),   v15_9 =V(15, 9),   v15_10=V(15,10),   v15_11=V(15,11),
	v16_0 =V(16, 0),   v16_1 =V(16, 1),   v16_2 =V(16, 2),   v16_3 =V(16, 3),
	v16_4 =V(16, 4),   v16_5 =V(16, 5),   v16_6 =V(16, 6),   v16_7 =V(16, 7),
	v16_8 =V(16, 8),   v16_9 =V(16, 9),   v16_10=V(16,10),   v16_11=V(16,11),
	v17_0 =V(17, 0),   v17_1 =V(17, 1),   v17_2 =V(17, 2),   v17_3 =V(17, 3),
	v17_4 =V(17, 4),   v17_5 =V(17, 5),   v17_6 =V(17, 6),   v17_7 =V(17, 7),
	v17_8 =V(17, 8),   v17_9 =V(17, 9),   v17_10=V(17,10),   v17_11=V(17,11),
	v18_0 =V(18, 0),   v18_1 =V(18, 1),   v18_2 =V(18, 2),   v18_3 =V(18, 3),
	v18_4 =V(18, 4),   v18_5 =V(18, 5),   v18_6 =V(18, 6),   v18_7 =V(18, 7),
	v18_8 =V(18, 8),   v18_9 =V(18, 9),   v18_10=V(18,10),   v18_11=V(18,11),
	v19_0 =V(19, 0),   v19_1 =V(19, 1),   v19_2 =V(19, 2),   v19_3 =V(19, 3),
	v19_4 =V(19, 4),   v19_5 =V(19, 5),   v19_6 =V(19, 6),   v19_7 =V(19, 7),
	v19_8 =V(19, 8),   v19_9 =V(19, 9),   v19_10=V(19,10),   v19_11=V(19,11),

	maxver // a test if we're sane or not
};
*/

#endif
