#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 31;
const unsigned char E_removeFile[] = {
'C', 'a', 'n', 'n', 'o', 't', ' ', 'r', 
'e', 'm', 'o', 'v', 'e', ' ', 'f', 'i', 
'l', 'e', ' ', '\'', '%', 's', '\'', '\0' } ;
