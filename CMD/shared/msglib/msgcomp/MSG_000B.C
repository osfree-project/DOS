#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 30;
const unsigned char E_tooManyDefFiles[] = {
'T', 'o', 'o', ' ', 'm', 'u', 'c', 'h', 
' ', 'm', 'e', 's', 's', 'a', 'g', 'e', 
's', '\0' } ;
