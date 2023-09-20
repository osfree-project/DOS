#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 31;
const unsigned char E_removeDir[] = {
'C', 'a', 'n', 'n', 'o', 't', ' ', 'r', 
'e', 'm', 'o', 'v', 'e', ' ', 'd', 'i', 
'r', 'e', 'c', 't', 'o', 'r', 'y', ' ', 
'\'', '%', 's', '\'', '\0' } ;
