/*
    This file is part of SUPPL - the supplemental library for DOS
    Copyright (C) 1996-2000 Steffen Kaiser

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
/* Enables the usage of the fast register pseudo vars for non-TURBO
   compilers. That means the port Turbo -> non-Turbo is OK.
   Back not, because the union holds the registers independed on
   real registers.
*/

#ifndef __REGPROTO_H
#define __REGPROTO_H

#include <dos.h>

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

#define asmLabel(a) } a: asm {
#define asmName(a,b) a

#define FAR _far

#ifndef MK_FP
#define MK_FP(seg,off) ((void FAR *)(((long)(seg) << 16)|(unsigned)(off)))
#endif


#endif
