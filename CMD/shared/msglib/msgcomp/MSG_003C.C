#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 82;
const unsigned char E_msgTooLong[] = {
'M', 'e', 's', 's', 'a', 'g', 'e', ' ', 
'\'', '%', 's', '\'', ' ', 't', 'o', 'o', 
' ', 'l', 'o', 'n', 'g', ';', '\n', 
't', 'h', 'e', ' ', 'm', 'e', 's', 's', 
'a', 'g', 'e', ' ', 'm', 'u', 's', 't', 
' ', 'n', 'o', 't', ' ', 'b', 'e', ' ', 
'l', 'o', 'n', 'g', 'e', 'r', ' ', 't', 
'h', 'a', 'n', ' ', '6', '5', '5', '3', 
'5', ' ', 'c', 'h', 'a', 'r', 'c', 't', 
'e', 'r', 's', '.', '\0' } ;
