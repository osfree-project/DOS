#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 60;
const unsigned char E_keywords[] = {
'T', 'h', 'e', ' ', '\'', 'i', 'n', 't', 
'e', 'r', 'n', 'a', 'l', ' ', 'k', 'e', 
'y', 'w', 'o', 'r', 'd', 's', '\'', ' ', 
'm', 'e', 's', 's', 'a', 'g', 'e', ' ', 
'o', 'f', ' ', 't', 'h', 'e', ' ', 'g', 
'l', 'o', 'b', 'a', 'l', ' ', 'm', 'e', 
's', 's', 'a', 'g', 'e', ' ', 'f', 'i', 
'l', 'e', ' ', 'i', 's', ' ', 'c', 'o', 
'r', 'r', 'u', 'p', 't', 'e', 'd', '!', 
'\0' } ;
