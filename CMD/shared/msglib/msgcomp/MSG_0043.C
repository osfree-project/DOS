#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 54;
const unsigned char E_invalidCommand[] = {
'I', 'n', 'v', 'a', 'l', 'i', 'd', ' ', 
'c', 'o', 'm', 'm', 'a', 'n', 'd', ' ', 
'"', '%', 's', '"', '.', '\0' } ;
