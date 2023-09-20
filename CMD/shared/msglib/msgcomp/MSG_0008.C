#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 23;
const unsigned char E_missingInternal[] = {
'I', 'n', 't', 'e', 'r', 'n', 'a', 'l', 
' ', 'u', 's', 'e', 'd', ' ', 'n', 'a', 
'm', 'e', ' ', '#', '%', 'u', ' ', 'm', 
'i', 's', 's', 'i', 'n', 'g', '\0' } ;
