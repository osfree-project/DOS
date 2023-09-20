#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 40;
const unsigned char E_unknownInternal[] = {
'U', 'n', 'k', 'n', 'o', 'w', 'n', ' ', 
'o', 'r', ' ', 'i', 'n', 'v', 'a', 'l', 
'i', 'd', ' ', 'i', 'n', 't', 'e', 'r', 
'n', 'a', 'l', ' ', '%', 's', '\0' } ;
