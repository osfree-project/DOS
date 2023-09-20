#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 24;
const unsigned char E_numberHigh[] = {
'N', 'u', 'm', 'b', 'e', 'r', ' ', 'h', 
'i', 'g', 'h', 'e', 'r', ' ', 't', 'h', 
'a', 'n', ' ', '%', 'u', ' ', '(', 'n', 
'e', 'a', 'r', ' ', 'l', 'i', 'n', 'e', 
' ', '%', 'u', ')', '\0' } ;
