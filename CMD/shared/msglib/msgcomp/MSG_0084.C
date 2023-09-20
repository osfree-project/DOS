#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 73;
const unsigned char E_unknownMsgLibVersion[] = {
'U', 'n', 'k', 'n', 'o', 'w', 'n', ' ', 
'f', 'o', 'r', 'm', 'a', 't', ' ', 'v', 
'e', 'r', 's', 'i', 'o', 'n', ' ', 'o', 
'f', ' ', 'b', 'i', 'n', 'a', 'r', 'y', 
' ', 'm', 'e', 's', 's', 'a', 'g', 'e', 
' ', 'l', 'i', 'b', 'a', 'r', 'y', ':', 
' ', '"', '%', 'u', '"', '\0' } ;
