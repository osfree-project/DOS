#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 52;
const unsigned char E_nocmd[] = {
'U', 'n', 'k', 'n', 'o', 'w', 'n', ' ', 
'c', 'o', 'm', 'm', 'a', 'n', 'd', ' ', 
'\'', '%', 's', '\'', '.', '\0' } ;
