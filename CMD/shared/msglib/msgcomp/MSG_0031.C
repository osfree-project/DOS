#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 50;
const unsigned char E_tmpFile[] = {
'C', 'a', 'n', 'n', 'o', 't', ' ', 'c', 
'r', 'e', 'a', 't', 'e', ' ', 't', 'e', 
'm', 'p', 'o', 'r', 'a', 'r', 'y', ' ', 
'f', 'i', 'l', 'e', '\0' } ;
