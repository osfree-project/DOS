#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 124;
const unsigned char E_nonArgOption[] = {
'O', 'p', 't', 'i', 'o', 'n', ' ', '\'', 
'/', '%', 'c', '\'', ' ', 'c', 'a', 'n', 
'n', 'o', 't', ' ', 'h', 'a', 'v', 'e', 
' ', 'a', 'n', ' ', 'a', 'r', 'g', 'u', 
'm', 'e', 'n', 't', '\0' } ;
