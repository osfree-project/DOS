/* $Id: PORTABLE.H 1.2 1998/08/19 07:27:05 ska Exp ska $
   $Locker: ska $	$Name:  $	$State: Exp $


   $Log: PORTABLE.H $
   Revision 1.2  1998/08/19 07:27:05  ska
   fix: incompatiblies Watcom to other compilers

   Revision 1.1  1998/08/19 06:33:33  ska
   Initial revision

*/

#ifndef __PORTABLE_H
#define __PORTABLE_H

#include <dos.h>
#include <direct.h>
#include <stdlib.h>

#define _AH reg.h.ah
#define _AL reg.h.al
#define _BH reg.h.bh
#define _BL reg.h.bl
#define _CH reg.h.ch
#define _CL reg.h.cl
#define _DH reg.h.dh
#define _DL reg.h.dl
#define _AX reg.x.ax
#define _BX reg.x.bx
#define _CX reg.x.cx
#define _DX reg.x.dx
#define _SI reg.x.si
#define _DI reg.x.di
#define _DS reg.x.ds
#define _ES reg.x.es
#define _CFLAG (reg.x.flags & 1)

/* byte/word/dword type */
typedef unsigned char byte;
typedef unsigned word;
typedef unsigned FLAG;
typedef unsigned FLAG8;

#ifndef _CLIB_
#define peekb(segm,ofs) (*(byte __far*)MK_FP((segm),(ofs)))
#define peekw(segm,ofs) (*(word __far*)MK_FP((segm),(ofs)))
#define pokeb(segm,ofs,value) (peekb((segm),(ofs)) = (byte)(value))
#define pokew(segm,ofs,value) (peekw((segm),(ofs)) = (word)(value))
#endif


#endif
