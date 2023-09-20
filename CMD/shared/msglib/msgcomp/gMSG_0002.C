#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 3;
const unsigned char E_UserBreak[] = {
'U', 's', 'e', 'r', ' ', 'b', 'r', 'e', 
'a', 'k', '\0' } ;
