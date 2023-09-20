#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 66;
const unsigned char E_numberZero[] = {
'N', 'u', 'm', 'b', 'e', 'r', ' ', 'm', 
'u', 's', 't', ' ', 'b', 'e', ' ', 'u', 
'n', 'e', 'q', 'u', 'a', 'l', ' ', 't', 
'o', ' ', 'z', 'e', 'r', 'o', '\0' } ;
