#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 100;
const unsigned char E_multPrep[] = {
'I', 'n', 't', 'e', 'r', 'n', 'a', 'l', 
' ', 'e', 'r', 'r', 'o', 'r', ':', '\n', 
'M', 'u', 't', 'l', 't', 'i', 'p', 'l', 
'e', ' ', 'l', 'a', 'n', 'g', 'u', 'a', 
'g', 'e', ' ', 'd', 'e', 'f', 'i', 'n', 
'i', 't', 'i', 'o', 'n', ' ', 'p', 'r', 
'e', 'p', 'a', 'r', 'a', 't', 'i', 'o', 
'n', '\0' } ;
