#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 43;
const unsigned char E_invalidSpec[] = {
'I', 'n', 'v', 'a', 'l', 'i', 'd', ' ', 
'o', 'r', ' ', 'i', 'l', 'l', '-', 'f', 
'o', 'r', 'm', 'e', 'd', ' ', 's', 'p', 
'e', 'c', 'i', 'f', 'i', 'c', 'a', 't', 
'i', 'o', 'n', ' ', '\'', '%', 'c', '\'', 
'\0' } ;
