#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 22;
const unsigned char E_msgFileHeadErrLvl[] = {
'E', 'r', 'r', 'o', 'r', ' ', 'm', 'e', 
's', 's', 'a', 'g', 'e', 's', ' ', 'n', 
'e', 'e', 'd', ' ', 'a', 'n', ' ', 'e', 
'r', 'r', 'o', 'r', ' ', 'l', 'e', 'v', 
'e', 'l', ' ', '(', 'n', 'e', 'a', 'r', 
' ', 'l', 'i', 'n', 'e', ' ', '%', 'u', 
')', '\0' } ;
