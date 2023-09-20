#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 126;
const unsigned char E_internalFailure[] = {
'I', 'n', 't', 'e', 'r', 'n', 'a', 'l', 
' ', 'f', 'a', 'i', 'l', 'u', 'r', 'e', 
' ', '#', '%', 'u', '\0' } ;
