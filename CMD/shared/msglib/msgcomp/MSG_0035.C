#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 62;
const unsigned char E_defKeyword[] = {
'K', 'e', 'y', 'w', 'o', 'r', 'd', ' ', 
'#', '%', 'd', ' ', '(', '%', 's', ' ', 
'-', '>', ' ', '%', 's', ')', ' ', 'i', 
's', ' ', 'd', 'e', 'f', 'i', 'n', 'e', 
'd', ' ', 't', 'w', 'i', 'c', 'e', '\0' } ;
