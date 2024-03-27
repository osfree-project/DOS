
;   GRAFTABL.ASM v0.5b
;
;   FreeDOS Utility to load high half of 8x8 character generator
;   to bring national language support to CGA graphics modes
;
;   Copyright (C) 9 Aug 2000 Ilya V. Vasilyev aka AtH//UgF@hMoscow
;   e-mail: hscool@netclub.ru
;   WWW:    http://www.freedos.org/
;
;   This program is free software; you can redistribute it and/or modify
;   it under the terms of the GNU General Public License as published by
;   the Free Software Foundation; either version 2 of the License, or
;   (at your option) any later version.
;
;   This program is distributed in the hope that it will be useful,
;   but WITHOUT ANY WARRANTY; without even the implied warranty of
;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;   GNU General Public License for more details.
;
;   You should have received a copy of the GNU General Public License
;   along with this program; if not, write to the Free Software
;   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
;
; To do:
;   +    /U                     Unload GRAPHICS.COM from memory
;   +    /F                     Update character generator option
;   +    Codepages support of some kind
;
;               .       .       .       .       .       string that rules
.8086


_TEXT segment para public 'CODE' use16

                org	100h
start:          jmp     Install
                align   16

bFont8x8h:      incbin  "cp866x8.fnt", 1024     ; SUPPORTED CODEPAGE

jOld2f:
		DB      0eaH                    ; JMP FAR
dOld2f		DD      -16

New2f:          cmp     ax,0b000H               ; INSTALLATION CHECK?
                jne     jOld2f
                mov     al,-1                   ; Yes, I am installed!
                iret

;-----------------------------
; End of Resident part
;               .       .       .       .       .       string that rules

Install:
                mov     ax,0b000H       ;GRAFTABL.COM - INSTALLATION CHECK
                int     2fH
                or      al,al
                jz      DoInstall

                mov     dx, offset errAlready
                mov     ah,9
                int     21H
                int     20H
DoInstall:
                mov     ax,352fH        ; Get vector 2f
                int     21H
                mov     word ptr [dOld2f],bx
                mov     word ptr [dOld2f+2],es

                mov     dx,New2f
                mov     ax,252fH        ; Set vector 2f
                int     21H

                push    ds              ; Kernel must not can intercept
                sub     ax,ax           ; and put extra stack space, etc.
                mov     ds,ax           ; So we will hardcode vector address
                mov     word ptr ds:[7cH],bFont8x8h
                mov     word ptr ds:[7eH],cs   ; Set vector 1f
                pop     ds

                mov     dx, offset msgOk
                mov     ah,9
                int     21H

                mov     dx,Install
                int     27H

;               .       .       .       .       .       string that rules

msgOk           DB      "GRAPHICS CHARACTERS LOADED", 0dH, 0aH, "$"
;msgUpdate      DB      "GRAPHICS CHARACTERS UPDATED", 0dH, 0aH, "$"
errAlready      DB      "GRAPHICS CHARACTERS ALREADY LOADED", 0dH, 0aH, "$"

_TEXT		ENDS
                END start
