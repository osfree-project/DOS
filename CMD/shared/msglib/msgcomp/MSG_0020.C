#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 25;
const unsigned char E_specFmt[] = {
'S', 'p', 'e', 'c', 'i', 'a', 'l', ' ', 
'f', 'o', 'r', 'm', 'a', 't', ' ', '%', 
'%', '-', '-', '%', '%', ' ', 'e', 'r', 
'r', 'o', 'r', ' ', '(', 'n', 'e', 'a', 
'r', ' ', 'l', 'i', 'n', 'e', ' ', '%', 
'u', ')', '\0' } ;
