#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 124;
const unsigned char E_argMissing[] = {
'A', 'r', 'g', 'u', 'm', 'e', 'n', 't', 
' ', 'o', 'f', ' ', 'o', 'p', 't', 'i', 
'o', 'n', ' ', '\'', '/', '%', 'c', '\'', 
' ', 'n', 'o', 't', ' ', 's', 'p', 'e', 
'c', 'i', 'f', 'i', 'e', 'd', '\0' } ;
