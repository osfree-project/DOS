#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 101;
const unsigned char E_joinLng[] = {
'I', 'n', 't', 'e', 'r', 'n', 'a', 'l', 
' ', 'e', 'r', 'r', 'o', 'r', ':', '\n', 
'C', 'a', 'n', 'n', 'o', 't', ' ', 'j', 
'o', 'i', 'n', ' ', 'd', 'e', 'f', 'i', 
'n', 'i', 't', 'i', 'o', 'n', 's', ' ', 
'o', 'f', ' ', 'd', 'i', 'f', 'f', 'e', 
'r', 'e', 'n', 't', ' ', 'l', 'a', 'n', 
'g', 'u', 'a', 'g', 'e', ' ', 'c', 'o', 
'd', 'e', '\0' } ;
