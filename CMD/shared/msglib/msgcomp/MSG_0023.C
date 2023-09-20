#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 41;
const unsigned char E_openEncl[] = {
'U', 'n', 'f', 'i', 'n', 'i', 's', 'h', 
'e', 'd', ' ', 'o', 'r', ' ', 'i', 'n', 
'v', 'a', 'l', 'i', 'd', ' ', 's', 'p', 
'e', 'c', 'i', 'a', 'l', ' ', 'e', 'n', 
'c', 'l', 'o', 's', 'u', 'r', 'e', ' ', 
'i', 'd', ' ', '\'', '%', 'c', '\'', ' ', 
'n', 'e', 'a', 'r', ' ', 'l', 'i', 'n', 
'e', ' ', '%', 'u', '\0' } ;
