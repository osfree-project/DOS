#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 63;
const unsigned char E_synKeyword[] = {
'S', 'y', 'n', 't', 'a', 'x', ' ', 'e', 
'r', 'r', 'o', 'r', ' ', 'i', 'n', ' ', 
'd', 'e', 'f', 'i', 'n', 'i', 't', 'i', 
'o', 'n', ' ', 'o', 'f', ' ', 'k', 'e', 
'y', 'w', 'o', 'r', 'd', ' ', '#', '%', 
'd', '\0' } ;
