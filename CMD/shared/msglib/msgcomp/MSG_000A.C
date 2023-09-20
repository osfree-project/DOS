#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 22;
const unsigned char E_msgFileHeadStruc[] = {
'E', 'r', 'r', 'o', 'r', ' ', 'i', 'n', 
' ', 'a', ' ', 'h', 'e', 'a', 'd', 'e', 
'r', ' ', 'o', 'f', ' ', 't', 'h', 'e', 
' ', 'm', 'e', 's', 's', 'a', 'g', 'e', 
' ', 'f', 'i', 'l', 'e', ' ', '(', 'n', 
'e', 'a', 'r', ' ', 'l', 'i', 'n', 'e', 
' ', '%', 'u', ')', '\0' } ;
