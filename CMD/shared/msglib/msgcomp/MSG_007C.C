#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 100;
const unsigned char E_creatBinLib[] = {
'C', 'a', 'n', 'n', 'o', 't', ' ', 'c', 
'r', 'e', 'a', 't', 'e', ' ', 'b', 'i', 
'n', 'a', 'r', 'y', ' ', 'f', 'i', 'l', 
'e', ':', ' ', '%', 's', '\0' } ;
