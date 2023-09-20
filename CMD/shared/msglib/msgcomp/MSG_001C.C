#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 20;
const unsigned char E_longStr[] = {
'A', 'r', 'g', 'u', 'm', 'e', 'n', 't', 
' ', 't', 'o', 'o', ' ', 'l', 'o', 'n', 
'g', ':', ' ', '\'', '%', 's', '\'', '\0' } ;
