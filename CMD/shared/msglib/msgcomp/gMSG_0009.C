#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 21;
const unsigned char E_readFile[] = {
'C', 'a', 'n', 'n', 'o', 't', ' ', 'r', 
'e', 'a', 'd', ' ', 'f', 'r', 'o', 'm', 
' ', 'f', 'i', 'l', 'e', ' ', '\'', '%', 
's', '\'', '\0' } ;
