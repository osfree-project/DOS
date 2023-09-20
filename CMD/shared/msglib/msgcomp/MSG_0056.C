#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 51;
const unsigned char E_invldTempMode[] = {
'I', 'n', 't', 'e', 'r', 'n', 'a', 'l', 
' ', 'f', 'a', 'i', 'l', 'u', 'r', 'e', 
':', ' ', 'I', 'n', 'v', 'a', 'l', 'i', 
'd', ' ', 'm', 'o', 'd', 'e', ' ', 't', 
'o', ' ', 'c', 'r', 'e', 'a', 't', 'e', 
' ', 't', 'e', 'm', 'p', 'o', 'r', 'a', 
'r', 'y', ' ', 'f', 'i', 'l', 'e', '\0' } ;
