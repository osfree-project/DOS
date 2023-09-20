#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 42;
const unsigned char E_tooManyMsg[] = {
'T', 'o', 'o', ' ', 'm', 'a', 'n', 'y', 
' ', 'm', 'e', 's', 's', 'a', 'g', 'e', 
's', '\0' } ;
