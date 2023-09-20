#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 58;
const unsigned char E_cmdRemove[] = {
'%', '-', '%', 'm', };
const static MSGID mid4 = E_invalidCommand;
const static unsigned char sid4[] = {
'\n', 
'V', 'a', 'l', 'i', 'd', ' ', 'r', 'e', 
'm', 'o', 'v', 'e', ' ', 'c', 'o', 'm', 
'm', 'a', 'n', 'd', 's', ' ', 'a', 'r', 
'e', ':', '\n', 
'!', 'r', 'e', 'm', 'o', 'v', 'e', ':', 
'<', 'n', 'u', 'm', 'b', 'e', 'r', '>', 
' ', '.', '.', '.', ' ', 't', 'o', ' ', 
'r', 'e', 'm', 'o', 'v', 'e', ' ', 'a', 
'l', 'l', ' ', 'd', 'e', 'f', 'i', 'n', 
'i', 't', 'i', 'o', 'n', 's', ' ', 'o', 
'f', ' ', 'l', 'a', 'n', 'g', 'u', 'a', 
'g', 'e', ' ', '<', 'n', 'u', 'm', 'b', 
'e', 'r', '>', '\n', 
'-', '<', 'n', 'u', 'm', 'b', 'e', 'r', 
'>', ' ', '.', '.', '.', ' ', 'a', 's', 
' ', 'a', 'b', 'o', 'v', 'e', '\n', 
'!', 'r', 'e', 'm', 'o', 'v', 'e', ':', 
'#', '<', 'n', 'u', 'm', 'b', 'e', 'r', 
'>', ' ', '.', '.', '.', ' ', 't', 'o', 
' ', 'r', 'e', 'm', 'o', 'v', 'e', ' ', 
't', 'h', 'e', ' ', '<', 'n', 'u', 'm', 
'b', 'e', 'r', '>', 't', 'h', ' ', 'e', 
'n', 't', 'r', 'y', '\n', 
'-', '#', '<', 'n', 'u', 'm', 'b', 'e', 
'r', '>', ' ', '.', '.', '.', ' ', 'a', 
's', ' ', 'a', 'b', 'o', 'v', 'e', '\0' } ;
