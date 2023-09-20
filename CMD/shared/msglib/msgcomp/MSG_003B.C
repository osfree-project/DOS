#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 81;
const unsigned char E_illformedCountryCodes[] = {
'C', 'o', 'u', 'n', 't', 'r', 'y', ' ', 
'c', 'o', 'd', 'e', 's', ' ', 'm', 'u', 
's', 't', ' ', 'c', 'o', 'n', 's', 'i', 
's', 't', ' ', 'o', 'f', ' ', 'd', 'i', 
'g', 'i', 't', 's', ' ', 'o', 'n', 'l', 
'y', ';', '\n', 
'i', 'l', 'l', '-', 'f', 'o', 'r', 'm', 
'e', 'd', ' ', 'c', 'o', 'u', 'n', 't', 
'r', 'y', ' ', 'c', 'o', 'd', 'e', ' ', 
'f', 'o', 'u', 'n', 'd', ' ', 'i', 'n', 
':', '\n', 
'%', 's', '\n', 
'i', 'n', ' ', 'k', 'e', 'y', 'w', 'o', 
'r', 'd', ':', '\n', 
'%', 's', '\0' } ;
