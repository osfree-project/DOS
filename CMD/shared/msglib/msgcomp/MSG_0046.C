#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 53;
const unsigned char E_cmdAlias[] = {
'%', '-', '%', 'm', };
const static MSGID mid1 = E_invalidCommand;
const static unsigned char sid1[] = {
'\n', 
'V', 'a', 'l', 'i', 'd', ' ', 'a', 'l', 
'i', 'a', 's', ' ', 'c', 'o', 'm', 'm', 
'a', 'n', 'd', 's', ' ', 'a', 'r', 'e', 
':', '\n', 
'!', 'a', 'l', 'i', 'a', 's', ':', '<', 
'n', 'u', 'm', '1', '>', '+', '<', 'n', 
'u', 'm', '2', '>', ' ', '.', '.', '.', 
' ', 't', 'o', ' ', 'a', 'd', 'd', ' ', 
't', 'h', 'e', ' ', 'a', 'l', 'i', 'a', 
's', ' ', '<', 'n', 'u', 'm', '2', '>', 
' ', 't', 'o', ' ', 'l', 'a', 'n', 'g', 
'u', 'a', 'g', 'e', ' ', '<', 'n', 'u', 
'm', '1', '>', '\n', 
'!', 'a', 'l', 'i', 'a', 's', ':', '<', 
'n', 'u', 'm', '1', '>', '-', '<', 'n', 
'u', 'm', '2', '>', ' ', '.', '.', '.', 
' ', 't', 'o', ' ', 'r', 'e', 'm', 'o', 
'v', 'e', ' ', 't', 'h', 'e', ' ', 'a', 
'l', 'i', 'a', 's', ' ', '<', 'n', 'u', 
'm', '2', '>', ' ', 't', 'o', ' ', 'l', 
'a', 'n', 'g', 'u', 'a', 'g', 'e', ' ', 
'<', 'n', 'u', 'm', '1', '>', '\0' } ;
