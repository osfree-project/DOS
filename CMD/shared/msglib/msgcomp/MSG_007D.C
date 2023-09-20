#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 101;
const unsigned char E_backupBinLib[] = {
'C', 'a', 'n', 'n', 'o', 't', ' ', 'c', 
'r', 'e', 'a', 't', 'e', ' ', 'b', 'a', 
'c', 'k', 'u', 'p', ' ', 'f', 'i', 'l', 
'e', ' ', '"', '%', '2', '%', 's', '"', 
'\n', 
'f', 'r', 'o', 'm', ' ', 'b', 'i', 'n', 
'a', 'r', 'y', ' ', 'f', 'i', 'l', 'e', 
' ', '"', '%', '1', '%', 's', '"', '\0' } ;
