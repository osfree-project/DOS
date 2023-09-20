#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 60;
const unsigned char E_noMsgLib[] = {
'T', 'h', 'e', ' ', 'f', 'i', 'l', 'e', 
' ', '"', '%', 's', '"', ' ', 'i', 's', 
' ', 'n', 'o', ' ', 'b', 'i', 'n', 'a', 
'r', 'y', ' ', 'm', 'e', 's', 's', 'a', 
'g', 'e', ' ', 'l', 'i', 'b', 'r', 'a', 
'r', 'y', ',', ' ', 'b', 'e', 'c', 'a', 
'u', 's', 'e', ' ', 'i', 't', '\n', 
'd', 'o', 'e', 's', ' ', 'n', 'o', 't', 
' ', 'c', 'o', 'n', 't', 'a', 'i', 'n', 
' ', 't', 'h', 'e', ' ', 'h', 'e', 'a', 
'd', 'e', 'r', ' ', 'a', 't', ' ', 't', 
'h', 'e', ' ', 'r', 'e', 'q', 'u', 'e', 
's', 't', 'e', 'd', ' ', 'p', 'o', 's', 
'i', 't', 'i', 'o', 'n', '\n', 
'a', 't', ' ', 't', 'h', 'e', ' ', '%', 
'-', '%', 'M', ' ', 'o', 'f', ' ', 't', 
'h', 'e', ' ', 'f', 'i', 'l', 'e', '.', 
'\0' } ;
