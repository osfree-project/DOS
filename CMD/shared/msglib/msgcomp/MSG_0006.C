#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 22;
const unsigned char E_ANSInumericArg[] = {
'\'', '%', 's', '\'', ' ', 'n', 'e', 'e', 
'd', 's', ' ', 'o', 'n', 'e', ' ', 'n', 
'u', 'm', 'e', 'r', 'i', 'c', ' ', 'a', 
'r', 'g', 'u', 'm', 'e', 'n', 't', ' ', 
'(', 'n', 'e', 'a', 'r', ' ', 'l', 'i', 
'n', 'e', ' ', '%', 'u', ')', '\0' } ;
