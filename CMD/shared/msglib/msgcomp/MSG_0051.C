#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 40;
const unsigned char E_misLng[] = {
'A', ' ', 's', 'e', 'c', 'o', 'n', 'd', 
'a', 'r', 'y', ' ', 'd', 'e', 'f', 'i', 
'n', 'i', 't', 'i', 'o', 'n', ' ', 'o', 
'f', ' ', 'l', 'a', 'n', 'g', 'u', 'a', 
'g', 'e', ' ', '%', 'u', ' ', 's', 'p', 
'e', 'c', 'i', 'f', 'i', 'e', 's', ' ', 
't', 'h', 'e', ' ', 'a', 'd', 'd', 'i', 
't', 'i', 'o', 'n', 'a', 'l', '\n', 
'a', 'l', 'i', 'a', 's', ' ', '%', 'u', 
' ', 't', 'h', 'a', 't', ' ', 'd', 'o', 
'e', 's', ' ', 'n', 'o', 't', ' ', 'a', 
'p', 'p', 'e', 'a', 'r', ' ', 'i', 'n', 
' ', 't', 'h', 'e', ' ', 'p', 'r', 'i', 
'm', 'a', 'r', 'y', ' ', 'a', 'l', 'i', 
'a', 's', ' ', 'l', 'i', 's', 't', '.', 
'\0' } ;
