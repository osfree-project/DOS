#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 55;
const unsigned char E_invalidNumber[] = {
'I', 'n', 'v', 'a', 'l', 'i', 'd', ' ', 
'n', 'u', 'm', 'b', 'e', 'r', ' ', 'i', 
'n', ' ', '"', '%', 's', '"', '\0' } ;
