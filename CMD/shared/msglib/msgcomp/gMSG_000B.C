#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 124;
const unsigned char E_option[] = {
'U', 'n', 'r', 'e', 'c', 'o', 'g', 'n', 
'i', 'z', 'e', 'd', ' ', 'o', 'p', 't', 
'i', 'o', 'n', ' ', '\'', '/', '%', 'c', 
'\'', '\0' } ;
