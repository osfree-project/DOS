#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 74;
const unsigned char E_mapMismatch[] = {
'M', 'e', 's', 's', 'a', 'g', 'e', ' ', 
'i', 'd', 'e', 'n', 't', 'i', 'f', 'i', 
'c', 'a', 't', 'o', 'r', ' ', 'm', 'i', 
's', 'm', 'a', 't', 'c', 'h', '!', '\n', 
'T', 'r', 'y', ' ', 't', 'o', ' ', 'a', 
's', 's', 'o', 'c', 'i', 'a', 't', 'e', 
' ', 't', 'h', 'e', ' ', 'm', 'e', 's', 
's', 'a', 'g', 'e', ' ', 'I', 'D', ' ', 
'0', 'x', '%', '0', '4', 'x', ' ', 'w', 
'i', 't', 'h', ' ', 't', 'h', 'e', ' ', 
'm', 'e', 's', 's', 'a', 'g', 'e', ' ', 
'\'', '%', 's', '\'', '.', '\n', 
'B', 'u', 't', ' ', 't', 'h', 'e', ' ', 
'b', 'i', 'n', 'a', 'r', 'y', ' ', 'm', 
'e', 's', 's', 'a', 'g', 'e', ' ', 'l', 
'i', 'b', 'r', 'a', 'r', 'y', ' ', 'a', 
'l', 'r', 'e', 'a', 'd', 'y', ' ', 'a', 
's', 's', 'o', 'c', 'i', 'a', 't', 'e', 
'd', ' ', 't', 'h', 'i', 's', ' ', 'I', 
'D', ' ', 'w', 'i', 't', 'h', '\n', 
'm', 'e', 's', 's', 'a', 'g', 'e', ' ', 
'\'', '%', 's', '\'', '.', '\0' } ;
