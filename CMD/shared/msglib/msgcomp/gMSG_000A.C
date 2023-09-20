#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 21;
const unsigned char E_writeFile[] = {
'C', 'a', 'n', 'n', 'o', 't', ' ', 'w', 
'r', 'i', 't', 'e', ' ', 't', 'o', ' ', 
'f', 'i', 'l', 'e', ' ', '\'', '%', 's', 
'\'', '\0' } ;
