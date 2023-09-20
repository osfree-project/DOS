#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 51;
const unsigned char E_cmdView[] = {
'%', '-', '%', 'm', };
const static MSGID mid0 = E_invalidCommand;
const static unsigned char sid0[] = {
'\n', 
'V', 'a', 'l', 'i', 'd', ' ', 'v', 'i', 
'e', 'w', '/', '@', ' ', 'c', 'o', 'm', 
'm', 'a', 'n', 'd', 's', ' ', 'a', 'r', 
'e', ':', '\n', 
'!', 'v', 'i', 'e', 'w', ' ', '.', '.', 
'.', ' ', 't', 'o', ' ', 'v', 'e', 'r', 
'b', 'o', 's', 'e', 'l', 'y', ' ', 'v', 
'i', 'e', 'w', ' ', 'a', 'l', 'l', ' ', 
'e', 'n', 't', 'r', 'i', 'e', 's', '\n', 
'@', '*', ' ', '.', '.', '.', ' ', 'a', 
's', ' ', 'a', 'b', 'o', 'v', 'e', '\n', 
'!', 'v', 'i', 'e', 'w', ':', '#', '<', 
'n', 'u', 'm', 'b', 'e', 'r', '>', ' ', 
'.', '.', '.', ' ', 't', 'o', ' ', 'v', 
'e', 'r', 'b', 'o', 's', 'e', 'l', 'y', 
' ', 'v', 'i', 'e', 'w', ' ', 't', 'h', 
'e', ' ', '<', 'n', 'u', 'm', 'b', 'e', 
'r', '>', 't', 'h', ' ', 'e', 'n', 't', 
'r', 'y', '\n', 
'@', '#', '<', 'n', 'u', 'm', 'b', 'e', 
'r', '>', ' ', '.', '.', '.', ' ', 'a', 
's', ' ', 'a', 'b', 'o', 'v', 'e', '\n', 
'\n', 
'@', ' ', '<', 'f', 'i', 'l', 'e', '>', 
' ', '.', '.', '.', ' ', 't', 'o', ' ', 
'r', 'e', 'a', 'd', ' ', 'a', ' ', 'c', 
'o', 'm', 'm', 'a', 'n', 'd', ' ', 'f', 
'i', 'l', 'e', '\0' } ;
