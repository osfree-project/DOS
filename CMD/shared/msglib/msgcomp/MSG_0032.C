#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 27;
const unsigned char E_invalidHlpScreen[] = {
'"', 'E', '_', 'h', 'l', 'p', 'S', 'c', 
'r', 'e', 'e', 'n', '"', ' ', 'm', 'u', 
's', 't', ' ', 'b', 'e', ' ', 'd', 'e', 
'f', 'i', 'n', 'e', 'd', ' ', 'i', 'n', 
' ', 'l', 'o', 'c', 'a', 'l', ' ', 'm', 
'e', 's', 's', 'a', 'g', 'e', ' ', 'f', 
'i', 'l', 'e', 's', ' ', 'o', 'n', 'l', 
'y', ' ', 'a', 'n', 'd', ' ', 'm', 'u', 
's', 't', ' ', 'b', 'e', '\n', 
'\t', 't', 'h', 'e', ' ', 'f', 'i', 'r', 
's', 't', ' ', 'm', 'e', 's', 's', 'a', 
'g', 'e', '!', '\0' } ;
