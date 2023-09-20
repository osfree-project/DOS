#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 124;
const unsigned char E_argOption[] = {
'O', 'p', 't', 'i', 'o', 'n', ' ', '\'', 
'/', '%', 'c', '\'', ' ', 'm', 'u', 's', 
't', ' ', 'h', 'a', 'v', 'e', ' ', 'a', 
'n', ' ', 'a', 'r', 'g', 'u', 'm', 'e', 
'n', 't', '\0' } ;
