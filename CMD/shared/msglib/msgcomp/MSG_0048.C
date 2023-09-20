#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 56;
const unsigned char E_cmdAppend[] = {
'%', '-', '%', 'm', };
const static MSGID mid2 = E_invalidCommand;
const static unsigned char sid2[] = {
'\n', 
'V', 'a', 'l', 'i', 'd', ' ', 'a', 'p', 
'p', 'e', 'n', 'd', ' ', 'c', 'o', 'm', 
'm', 'a', 'n', 'd', 's', ' ', 'a', 'r', 
'e', ':', '\n', 
'!', 'a', 'p', 'p', 'e', 'n', 'd', ':', 
'<', 'f', 'i', 'l', 'e', '>', ' ', '.', 
'.', '.', ' ', 't', 'o', ' ', 'a', 'p', 
'p', 'e', 'n', 'd', ' ', 't', 'h', 'e', 
' ', 'b', 'i', 'n', 'a', 'r', 'y', ' ', 
'm', 'e', 's', 's', 'a', 'g', 'e', ' ', 
'l', 'i', 'b', 'r', 'a', 'r', 'y', ' ', 
'<', 'f', 'i', 'l', 'e', '>', ' ', 'a', 
't', ' ', 't', 'h', 'e', ' ', 'e', 'n', 
'd', '\n', 
'\t', 'o', 'f', ' ', 't', 'h', 'e', ' ', 
'b', 'i', 'n', 'a', 'r', 'y', '_', 'f', 
'i', 'l', 'e', '\n', 
'+', ' ', '<', 'f', 'i', 'l', 'e', '>', 
' ', '.', '.', '.', ' ', 'a', 's', ' ', 
'a', 'b', 'o', 'v', 'e', '\0' } ;
