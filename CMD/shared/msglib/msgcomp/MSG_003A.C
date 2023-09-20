#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 80;
const unsigned char E_noCountryCodes[] = {
'N', 'o', ' ', '"', 'c', 'o', 'u', 'n', 
't', 'r', 'y', ' ', 'c', 'o', 'd', 'e', 
's', '"', ' ', 'i', 'n', 't', 'e', 'r', 
'n', 'a', 'l', ' ', 'm', 'e', 's', 's', 
'a', 'g', 'e', ' ', 'f', 'o', 'u', 'n', 
'd', ' ', 'i', 'n', ':', '\n', 
'%', 's', '\n', 
'l', 'o', 'o', 'k', 'i', 'n', 'g', ' ', 
'f', 'o', 'r', ' ', 'k', 'e', 'y', 'w', 
'o', 'r', 'd', ':', '\n', 
'%', 's', '\0' } ;
