#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 61;
const unsigned char E_brokenMsgLib[] = {
'B', 'r', 'o', 'k', 'e', 'n', ' ', 'b', 
'i', 'n', 'a', 'r', 'y', ' ', 'm', 'e', 
's', 's', 'a', 'g', 'e', ' ', 'l', 'i', 
'b', 'r', 'a', 'r', 'y', ' ', '"', '%', 
's', '"', '.', '\n', 
'A', ' ', 'l', 'a', 'n', 'g', 'u', 'a', 
'g', 'e', ' ', 'd', 'e', 'f', 'i', 'n', 
'i', 't', 'i', 'o', 'n', ' ', 'w', 'a', 
's', ' ', 'e', 'x', 'p', 'e', 'c', 't', 
'e', 'd', ' ', 'a', 't', ' ', 'p', 'o', 
's', 'i', 't', 'i', 'o', 'n', ' ', '%', 
'l', 'd', '.', '\0' } ;
