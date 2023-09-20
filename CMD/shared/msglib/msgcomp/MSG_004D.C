#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 70;
const unsigned char E_entryTooHigh[] = {
'E', 'n', 't', 'r', 'y', ' ', '#', '%', 
'd', ' ', 'w', 'a', 's', ' ', 'r', 'e', 
'q', 'u', 'e', 's', 't', 'e', 'd', ',', 
' ', 'b', 'u', 't', ' ', 'o', 'n', 'l', 
'y', ' ', '%', 'd', ' ', 'e', 'n', 't', 
'r', 'i', 'e', 's', ' ', 'a', 'r', 'e', 
' ', 's', 't', 'o', 'r', 'e', 'd', ' ', 
'w', 'i', 't', 'h', 'i', 'n', '\n', 
't', 'h', 'e', ' ', 'b', 'i', 'n', 'a', 
'r', 'y', ' ', 'm', 'e', 's', 's', 'a', 
'g', 'e', ' ', 'l', 'i', 'b', 'r', 'a', 
'r', 'y', '.', '\0' } ;
