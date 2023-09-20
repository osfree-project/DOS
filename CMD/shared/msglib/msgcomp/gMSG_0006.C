#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 21;
const unsigned char E_openFile[] = {
'C', 'a', 'n', 'n', 'o', 't', ' ', 'o', 
'p', 'e', 'n', ' ', 'f', 'i', 'l', 'e', 
' ', '\'', '%', 's', '\'', '\0' } ;
