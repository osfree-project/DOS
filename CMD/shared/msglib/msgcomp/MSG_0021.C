#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 26;
const unsigned char E_noChar[] = {
'g', 'e', 't', 'C', 'h', 'a', 'r', '(', 
')', ' ', 'f', 'a', 'i', 'l', 'e', 'd', 
' ', 'n', 'e', 'a', 'r', ' ', 'l', 'i', 
'n', 'e', ' ', '%', 'u', '\0' } ;
