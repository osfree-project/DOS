#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 81;
const unsigned char E_syntaxID[] = {
'S', 'y', 'n', 't', 'a', 'x', ' ', 'e', 
'r', 'r', 'o', 'r', ' ', 's', 'c', 'a', 
'n', 'n', 'i', 'n', 'g', ' ', 'n', 'u', 
'm', 'e', 'r', 'i', 'c', 'a', 'l', ' ', 
'<', '-', '>', ' ', 's', 'y', 'm', 'b', 
'o', 'l', 'i', 'c', 'a', 'l', ' ', 'm', 
'e', 's', 's', 'a', 'g', 'e', ' ', 'I', 
'D', ' ', 'm', 'a', 'p', 'p', 'e', 'r', 
' ', 'f', 'i', 'l', 'e', '\n', 
'\'', '%', 's', '\'', ',', ' ', 'i', 'n', 
' ', 'l', 'i', 'n', 'e', ':', '\n', 
'"', '%', 's', '"', '\0' } ;
