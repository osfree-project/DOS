#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 45;
const unsigned char E_inconsistentnr[] = {
'I', 'n', 'c', 'o', 'n', 's', 'i', 's', 
't', 'e', 'n', 't', ' ', 'n', 'u', 'm', 
'b', 'e', 'r', 's', ' ', 'o', 'f', ' ', 
'i', 'n', 't', 'e', 'r', 'n', 'a', 'l', 
'l', 'y', ' ', 'u', 's', 'e', 'd', ' ', 
'k', 'e', 'y', 'w', 'o', 'r', 'd', 's', 
' ', 'E', 'n', 'g', 'l', 'i', 's', 'h', 
'=', '%', 'u', ',', ' ', 'l', 'n', 'g', 
'=', '%', 'u', '\0' } ;
