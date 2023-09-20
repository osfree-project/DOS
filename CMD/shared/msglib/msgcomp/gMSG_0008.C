#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 21;
const unsigned char E_accessFile[] = {
'C', 'a', 'n', 'n', 'o', 't', ' ', 'a', 
'c', 'c', 'e', 's', 's', ' ', 'f', 'i', 
'l', 'e', ' ', '\'', '%', 's', '\'', '\0' } ;
