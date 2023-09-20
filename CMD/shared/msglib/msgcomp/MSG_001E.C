#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 22;
const unsigned char E_exec[] = {
'E', 'r', 'r', 'o', 'r', ' ', 'e', 'x', 
'e', 'c', 'u', 't', 'i', 'n', 'g', ' ', 
'\'', '%', 's', '\'', '\0' } ;
