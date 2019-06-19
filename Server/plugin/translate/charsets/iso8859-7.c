#include "translate.h"

static const t_unicode iso8859_7_g1_chars[] = {
0x00A0, 0x02BD, 0x02BC, 0xfffd, 0xfffd, 0x00A3, 0x00A6, 0x00A7, /* 0xA0-0xA7 */
0x00A8, 0x00A9, 0xfffd, 0x00AB, 0x00AC, 0x00AD, 0xfffd, 0x2015, /* 0xA8-0xAF */
0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x0384, 0x0385, 0x0386, 0x00B7, /* 0xB0-0xB7 */
0x0388, 0x0389, 0x038A, 0x00BB, 0x038C, 0x00BD, 0x038E, 0x038F, /* 0xB8-0xBF */
0x0390, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397, /* 0xC0-0xC7 */
0x0398, 0x0399, 0x039A, 0x039B, 0x039C, 0x039D, 0x039E, 0x039F, /* 0xC8-0xCF */
0x03A0, 0x03A1, 0xfffd, 0x03A3, 0x03A4, 0x03A5, 0x03A6, 0x03A7, /* 0xD0-0xD7 */
0x03A8, 0x03A9, 0x03AA, 0x03AB, 0x03AC, 0x03AD, 0x03AE, 0x03AF, /* 0xD8-0xDF */
0x03B0, 0x03B1, 0x03B2, 0x03B3, 0x03B4, 0x03B5, 0x03B6, 0x03B7, /* 0xE0-0xE7 */
0x03B8, 0x03B9, 0x03BA, 0x03BB, 0x03BC, 0x03BD, 0x03BE, 0x03BF, /* 0xE8-0xEF */
0x03C0, 0x03C1, 0x03C2, 0x03C3, 0x03C4, 0x03C5, 0x03C6, 0x03C7, /* 0xF0-0xF7 */
0x03C8, 0x03C9, 0x03CA, 0x03CB, 0x03CC, 0x03CD, 0x03CE, 0xfffd, /* 0xF8-0xFF */
};
struct char_set iso8859_7_g1 = {
	1,
	CHARS(iso8859_7_g1_chars),
	126, "F", 1, 96, 
};

struct char_set iso8859_7 = {
	.c0 = &ascii_c0,
	.g0 = &ascii_g0,
	.c1 = &ascii_c1,
	.g1 = &iso8859_7_g1,
	.names = { "iso8859-7", 0 }, 
};

CONSTRUCTOR(static void init(void))
{
	register_charset(&iso8859_7_g1);
	register_charset(&iso8859_7);
}
