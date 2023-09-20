#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 42;
const unsigned char E_longMsgStr[] = {
'T', 'h', 'e', 'r', 'e', ' ', 'i', 's', 
' ', 'a', ' ', 'm', 'e', 's', 's', 'a', 
'g', 'e', ' ', 's', 't', 'r', 'i', 'n', 
'g', ' ', 'l', 'o', 'n', 'g', 'e', 'r', 
' ', 't', 'h', 'a', 'n', ' ', '%', 'u', 
' ', 'c', 'h', 'a', 'r', 'a', 'c', 't', 
'e', 'r', 's', '!', '\n', 
'O', 'r', ' ', 'c', 'o', 'n', 't', 'a', 
'i', 'n', 's', ' ', 'N', 'U', 'L', ' ', 
'c', 'h', 'a', 'r', 'a', 'c', 't', 'e', 
'r', 's', '.', '\0' } ;
