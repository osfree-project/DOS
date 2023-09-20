#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 22;
const unsigned char E_encloserOpen[] = {
'E', 'n', 'c', 'l', 'o', 's', 'u', 'r', 
'e', ' ', 'v', 'i', 'a', ' ', '%', '%', 
'-', '%', '%', ' ', 'o', 'r', ' ', '%', 
'%', '-', '-', '%', '%', ' ', 'i', 's', 
' ', 'n', 'o', 't', ' ', 'f', 'i', 'n', 
'i', 's', 'h', 'e', 'd', ' ', '(', 'n', 
'e', 'a', 'r', ' ', 'l', 'i', 'n', 'e', 
' ', '%', 'u', ')', '\0' } ;
