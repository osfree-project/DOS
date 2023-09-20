#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 40;
const unsigned char E_optOatstart[] = {
'O', 'p', 't', 'i', 'o', 'n', ' ', '\'', 
'/', 'O', '\'', ' ', 'm', 'u', 's', 't', 
' ', 'p', 'r', 'e', 'c', 'e', 'e', 'd', 
' ', 't', 'h', 'e', ' ', 'f', 'i', 'r', 
's', 't', ' ', 'f', 'i', 'l', 'e', 'n', 
'a', 'm', 'e', '!', '\0' } ;
