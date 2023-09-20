#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 62;
const unsigned char E_invldLngCode[] = {
'B', 'r', 'o', 'k', 'e', 'n', ' ', 'b', 
'i', 'n', 'a', 'r', 'y', ' ', 'm', 'e', 
's', 's', 'a', 'g', 'e', ' ', 'l', 'i', 
'b', 'r', 'a', 'r', 'y', ' ', '"', '%', 
's', '"', '.', '\n', 
'A', ' ', 'l', 'a', 'n', 'g', 'u', 'a', 
'g', 'e', ' ', 'c', 'o', 'd', 'e', ' ', 
'\'', '0', '\'', ' ', 'w', 'a', 's', ' ', 
'e', 'n', 'c', 'o', 'u', 'n', 't', 'e', 
'r', 'd', '.', '\0' } ;
