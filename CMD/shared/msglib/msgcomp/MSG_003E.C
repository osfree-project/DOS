#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 83;
const unsigned char E_multipleCountryCodes[] = {
'M', 'u', 'l', 't', 'i', 'p', 'l', 'e', 
' ', 'c', 'o', 'u', 'n', 't', 'r', 'y', 
' ', 'c', 'o', 'd', 'e', ' ', 'd', 'e', 
'f', 'i', 'n', 'i', 't', 'i', 'o', 'n', 
' ', 'f', 'o', 'u', 'n', 'd', ' ', 'i', 
'n', ' ', 'f', 'i', 'l', 'e', ':', '\n', 
'%', 's', '\n', 
'i', 'n', ' ', 'k', 'e', 'y', 'w', 'o', 
'r', 'd', ':', '\n', 
'%', 's', '\0' } ;
