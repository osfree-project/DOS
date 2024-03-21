; FreeDOS APPEND
; Copyright (c) 2004 Eduardo Casino <casino_e@terra.es>
;
; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or
; (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program; if not, write to the Free Software
; Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307	USA
;
; 04-06-01  casino_e@terra.es	First version
; 04-06-03  casino_e@terra.es	Add note to help stating that when /E is used,
;				no paths that can appear on the command line.
; 04-06-13  Eric Auer		Make older versions of nasm happy
; 04-06-16  Eric Auer /
;	    casino_e@terra.es	Convert to COM
; 04-06-17  casino_e@terra.es	Put tempDTA and part of cmdline in PSP
; 04-06-18  casino_e@terra.es	Remove unnecessary cs -> ds setting
; 04-06-27  casino_e@terra.es	Back again to EXE (as suggested by Arkady),
;				but just adding a minimalistic EXE header
;				Bug: Now it _really_ frees the environment
; 06-01-23  casino_e@terra.es   Add version string
;
VERSION equ "5.0.0.6"

.model small
.8086

public start
public append_state
public append_path
public append_prefix
public cmd_id

extern p_flags :byte
extern cmdline :word
extern tempDTA :dword
extern old_int2f :dword
extern old_int21 :dword
extern get_environ :near
extern parse_cmds  :near
extern int2f       :near
extern int21       :near

extern TXT_MSG_APPEND_INSTALLED: near
extern TXT_MSG_APPEND_INCORRECT: near
extern TXT_MSG_INCORRECT_DOSVERSION: near
extern TXT_MSG_APPEND_ASSIGN_CONFLICT: near
extern printmsg: near

_TEXT segment

include useful.inc
include cmdline.inc
include append.inc
include dos.inc


cmd_id:
append_prefix	db	"APPEND="
append_path	db 100h dup(0)

append_state	dw	0011000000000001b
;			||||\_________/|
;			||||	 |     +- 0	set if APPEND enabled
;			||||	 +------- 1-11	reserved
;			|||+------------- 12	(DOS 5.0) set if APPEND
;			|||			   applies directory search
;			|||			   even if a drive has been
;			|||			   specified
;			||+-------------- 13	set if /PATH flag active
;			|+--------------- 14	set if /E flag active
;			|			   (environment var APPEND
;			|			    exists)
;			+---------------- 15	set if /X flag active
;
;APPEND_ENABLED	equ	0000000000000001b
;APPEND_SRCHDRV	equ	0001000000000000b
;APPEND_SRCHPTH	equ	0010000000000000b
;APPEND_ENVIRON	equ	0100000000000000b
;APPEND_EXTENDD	equ	1000000000000000b



end_resident:
; ================== END OF RESIDENT CODE ================================

start:		
		@GetVer
		cmp     al,2
		jge     vers_ok		; Version must be 2.x or higher

		lea	si, TXT_MSG_INCORRECT_DOSVERSION
		call	printmsg
		jmp	quit

vers_ok:
		mov     ax,0600h
		int     2fh
		cmp	al,0ffh
		jne	noassign

		lea	si, TXT_MSG_APPEND_ASSIGN_CONFLICT
		call	printmsg
		jmp	quit

noassign:	mov	ax, 0B710h	; Check if we're already installed
		mov	dx, 00000h
		int	2Fh

		cmp	dx, 0000h	; Not installed
		je	install

		cmp	dl, 5		; Check installed version
		jne	wrong
		cmp	dh, 0
		je	installed

wrong:		lea	si, TXT_MSG_APPEND_INCORRECT
		call	printmsg
		jmp	quit

		
installed:	lea	si, TXT_MSG_APPEND_INSTALLED
		call	printmsg

quit:		@Exit	1	; Exit, errorlevel 1

install:	mov	bx, cs

		; points tempDTA to first 128 bytes of PSP and cmdline to last
		; 128 bytes of PSP plus first 128 bytes of program. cmdline
		; already contains 0x80
		;
		mov	word ptr cs:[tempDTA+2], bx
		mov	cs:[cmdline+2], bx

		call	get_environ	; Get PARENT environment

		; Parse command line parameters.
		;
		mov	es, bx		; ES:SI to command line
		mov	si, 80h
		xor	cx, cx
		mov	cl, es:[si]	; Length of command line
		inc	si
		call	parse_cmds
		jc	quit

		; Free some bytes, release environment
		;
		mov	bx, es:[2Ch]	 ; Segment of environment
		@FreeBlok bx		; Free memory

		; Get vect to original int2f handler
		;
		@GetInt	2Fh		; get vector to ES:BX
		mov	ax, es
		mov	word ptr [old_int2f], bx
		mov	word ptr [old_int2f+2], ax

		; Now, install new int2f handler
		;
		@SetInt	2FH, int2f	; DS:DX -> new interrupt handler

		; Get vect to original int21 handler
		;
		@GetInt	21h		; get vector to ES:BX
		mov	ax, es
		mov	word ptr [old_int21], bx
		mov	word ptr [old_int21+2], ax

		; Now, install new int21 handler
		;
		@SetInt	21h, int21	; DS:DX -> new interrupt handler

		mov	byte ptr [p_flags], RESIDENT     ; Set resident flag
						     ; and clean the rest

		; Terminate and stay resident
		;
		mov	dx, offset end_resident+15
		mov	cl, 4
		shr	dx, cl		; Convert to paragraphs

		@TSR	DX, 0	; Errorlevel 0


_TEXT ends

DGROUP group _TEXT

       end
