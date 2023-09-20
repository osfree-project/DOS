#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 71;
const unsigned char E_unknownCS[] = {
'U', 'n', 'k', 'n', 'o', 'w', 'n', ' ', 
'c', 'h', 'a', 'r', 'a', 'c', 't', 'e', 
'r', ' ', 's', 'e', 't', ':', ' ', '"', 
'%', 's', '"', '\0' } ;
