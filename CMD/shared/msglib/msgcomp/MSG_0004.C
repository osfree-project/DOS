#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 22;
const unsigned char E_ANSIToken[] = {
'\'', '%', 's', '\'', ' ', 'i', 's', ' ', 
'n', 'o', ' ', 'A', 'N', 'S', 'I', ' ', 
't', 'o', 'k', 'e', 'n', ' ', '(', 'n', 
'e', 'a', 'r', ' ', 'l', 'i', 'n', 'e', 
' ', '%', 'u', ')', '\0' } ;
