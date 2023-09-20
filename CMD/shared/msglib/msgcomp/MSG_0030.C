#ifndef _MICROC_
#include <algnbyte.h>
#else 
#define const 
#endif
#include "yerror.h"
static unsigned char errNr = 51;
const unsigned char E_renameFile[] = {
'C', 'a', 'n', 'n', 'o', 't', ' ', 'r', 
'e', 'n', 'a', 'm', 'e', ' ', 'f', 'i', 
'l', 'e', ' ', '\'', '%', 's', '\'', ' ', 
't', 'o', ' ', '\'', '%', 's', '\'', '\0' } ;
