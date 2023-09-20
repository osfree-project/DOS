#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 20;
const unsigned char E_noFarMem[] = {
'F', 'a', 'r', ' ', 'm', 'e', 'm', 'o', 
'r', 'y', ' ', 'f', 'u', 'l', 'l', '\0' } ;
