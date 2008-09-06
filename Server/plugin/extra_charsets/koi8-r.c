#include "translate.h"

static const t_unicode koi8_r_c1_chars[] = {
0x2500, 0x2502, 0x250C, 0x2510, 0x2514, 0x2518, 0x251C, 0x2524, /* 0x80-0x87 */
0x252C, 0x2534, 0x253C, 0x2580, 0x2584, 0x2588, 0x258C, 0x2590, /* 0x88-0x8F */
0x2591, 0x2592, 0x2593, 0x2320, 0x25A0, 0x2219, 0x221A, 0x2248, /* 0x90-0x97 */
0x2264, 0x2265, 0x00A0, 0x2321, 0x00B0, 0x00B2, 0x00B7, 0x00F7, /* 0x98-0x9F */
};
struct char_set koi8_r_c1 = {
	1,
	CHARS(koi8_r_c1_chars),
	0, "", 0, 32,
};


static const t_unicode koi8_r_g1_chars[] = {
0x2550, 0x2551, 0x2552, 0x0451, 0x2553, 0x2554, 0x2555, 0x2556, /* 0xA0-0xA7 */
0x2557, 0x2558, 0x2559, 0x255A, 0x255B, 0x255C, 0x255D, 0x255E,	/* 0xA8-0xAF */
0x255F, 0x2560, 0x2561, 0x0401, 0x2562, 0x2563, 0x2564, 0x2565,	/* 0xB0-0xB7 */
0x2566, 0x2567, 0x2568, 0x2569, 0x256A, 0x256B, 0x256C, 0x00A9,	/* 0xB8-0xBF */
0x044E, 0x0430, 0x0431, 0x0446, 0x0434, 0x0435, 0x0444, 0x0433,	/* 0xC0-0xC7 */
0x0445, 0x0438, 0x0439, 0x043A, 0x043B, 0x043C, 0x043D, 0x043E,	/* 0xC8-0xCF */
0x043F, 0x044F, 0x0440, 0x0441, 0x0442, 0x0443, 0x0436, 0x0432,	/* 0xD0-0xD7 */
0x044C, 0x044B, 0x0437, 0x0448, 0x044D, 0x0449, 0x0447, 0x044A,	/* 0xD8-0xDF */
0x042E, 0x0410, 0x0411, 0x0426, 0x0414, 0x0415, 0x0424, 0x0413,	/* 0xE0-0xE7 */
0x0425, 0x0418, 0x0419, 0x041A, 0x041B, 0x041C, 0x041D, 0x041E,	/* 0xE8-0xEF */
0x041F, 0x042F, 0x0420, 0x0421, 0x0422, 0x0423, 0x0416, 0x0412,	/* 0xF0-0xF7 */
0x042C, 0x042B, 0x0417, 0x0428, 0x042D, 0x0429, 0x0427, 0x042A,	/* 0xF8-0xFF */
};
struct char_set koi8_r_g1 = {
	1,
	CHARS(koi8_r_g1_chars),
	0, "", 1, 96, 
};

struct char_set koi8_r = {
	.c0 = &ascii_c0,
	.g0 = &ascii_g0,
	.c1 = &koi8_r_c1,
	.g1 = &koi8_r_g1,
	.names = { "koi8-r", 0 },
};

struct char_set koi8_r_safe = {
	.c0 = &ascii_c0,
	.g0 = &ascii_g0,
	.c1 = &ascii_c1,
	.g1 = &koi8_r_g1,
	.names = { "koi8-r-safe", 0 },
};

CONSTRUCTOR(static void init(void))
{
	register_charset(&koi8_r);
	register_charset(&koi8_r_safe);
}
