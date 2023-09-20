#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 64;
const unsigned char E_noKeyword[] = {
'U', 'n', 'k', 'n', 'o', 'w', 'n', ' ', 
'k', 'e', 'y', 'w', 'o', 'r', 'd', ' ', 
'\'', '%', 's', '\'', '\0' } ;
