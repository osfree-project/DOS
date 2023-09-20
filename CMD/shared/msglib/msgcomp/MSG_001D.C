#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 21;
const unsigned char E_cmdLine[] = {
'C', 'o', 'm', 'm', 'a', 'n', 'd', ' ', 
'l', 'i', 'n', 'e', ' ', 't', 'o', 'o', 
' ', 'l', 'o', 'n', 'g', '\0' } ;
