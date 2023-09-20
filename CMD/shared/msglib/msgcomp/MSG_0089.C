#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 80;
const unsigned char E_longLine[] = {
'T', 'h', 'e', ' ', 'f', 'i', 'l', 'e', 
' ', '\'', '%', 's', '\'', ' ', 'c', 'o', 
'n', 't', 'a', 'i', 'n', 's', ' ', 'a', 
' ', 'l', 'i', 'n', 'e', ' ', 't', 'h', 
'a', 't', ' ', 'i', 's', ' ', 'l', 'o', 
'n', 'g', 'e', 'r', ' ', 't', 'h', 'a', 
'n', ' ', '%', 'u', ' ', 'c', 'h', 'a', 
'r', 'a', 'c', 't', 'e', 'r', 's', '.', 
'\0' } ;
