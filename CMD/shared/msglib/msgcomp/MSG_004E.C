#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 71;
const unsigned char E_noSuchLng[] = {
'N', 'o', ' ', 'd', 'e', 'f', 'i', 'n', 
'i', 't', 'i', 'o', 'n', ' ', 'f', 'o', 
'r', ' ', 'l', 'a', 'n', 'g', 'u', 'a', 
'g', 'e', ' ', '%', 'u', ' ', 'f', 'o', 
'u', 'n', 'd', '.', '\0' } ;
