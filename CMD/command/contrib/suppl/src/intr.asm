; File:
;                         intr.asm
; Description:
;       Assembly implementation of calling an interrupt
;
;                    Copyright (c) 2000
;                       Steffen Kaiser
;                       All Rights Reserved
;
; This file is part of FreeDOS.
;
; FreeDOS is free software; you can redistribute it and/or
; modify it under the terms of the GNU General Public License
; as published by the Free Software Foundation; either version
; 2, or (at your option) any later version.
;
; DOS-C is distributed in the hope that it will be useful, but
; WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
; the GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public
; License along with DOS-C; see the file COPYING.  If not,
; write to the Free Software Foundation, Inc.,
; 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
;

include "model.inc"

.8086

COMPILE equ 1

TEXT  segment word public 'CODE' use16

public intrf_
public _intrf_

intrf_:
_intrf_:

ifdef COMPILE
		push	bp			; Standard C entry
		push	es			; gcc-ia16 has es caller-saved
		push	bx
		push	cx
		mov	bx, dx
		push	dx
		push	si
		push	di
		push	ds
		mov	byte ptr [cs:intr_1-1], al
		jmp	short intr_2		; flush the instruction cache
intr_2:
		mov	ah, [bx+18]		; SZAPC flags
		sahf
		mov	ax, [bx]
		mov	cx, [bx+4]
		mov	dx, [bx+6]
		mov	bp, [bx+8]
		mov	si, [bx+10]
		mov	di, [bx+12]
		push	word ptr [bx+14]		; ds
		mov	es, [bx+16]
		mov	bx, [bx+2]
		pop	ds
		int	0
intr_1:
		pushf
		push	ds
		push	bx
		mov	bx, sp
		mov	ds, [ss:bx+6]
		mov	bx, [ss:bx+12]		; address of REGPACK
		mov	[bx], ax
		pop	word ptr [bx+2]
		mov	[bx+4], cx
		mov	[bx+6], dx
		mov	[bx+8], bp
		mov	[bx+10], si
		mov	[bx+12], di
		pop	word ptr [bx+14]
		mov	[bx+16], es
		pop	word ptr [bx+18]

		pop	ds
		pop	di
		pop	si
		pop	dx
		pop	cx
		pop	bx
		pop	es
		pop	bp
		ret					; retf/retn model specific, see model.inc
endif

TEXT  ends

      end
