#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 50;
const unsigned char E_reqFnam[] = {
'A', 'd', 'd', '/', 'i', 'n', 's', 'e', 
'r', 't', '/', 'r', 'e', 'm', 'o', 'v', 
'e', '/', 'e', 'x', 't', 'r', 'a', 'c', 
't', ' ', 'o', 'p', 'e', 'r', 'a', 't', 
'i', 'o', 'n', 's', ' ', 'r', 'e', 'q', 
'u', 'i', 'r', 'e', 's', ' ', 'a', ' ', 
'f', 'i', 'l', 'e', '\0' } ;
