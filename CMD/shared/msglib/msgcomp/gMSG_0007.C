#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 21;
const unsigned char E_createFile[] = {
'C', 'a', 'n', 'n', 'o', 't', ' ', 'c', 
'r', 'e', 'a', 't', 'e', ' ', 'f', 'i', 
'l', 'e', ' ', '\'', '%', 's', '\'', '\0' } ;
