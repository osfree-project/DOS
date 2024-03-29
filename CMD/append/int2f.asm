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
; INT2F.ASM - Int2Fh hook
;
; 04-06-01  casino_e@terra.es	First version
; 06-01-23  casino_e@terra.es	Searchs for self name in command line (DS:BX)
;                            	instead of command name (DS:SI) for better
;                            	MS compatibility
;


.model small
.8086
.code

public cmdnambuf
public cmdlinbuf
public old_int2f
public int2f

extern p_flags :byte
extern handler :byte
extern parse_cmds :near
extern int21usr   :near
extern append_state  :word
extern usr_int21     :dword
extern append_path   :byte
extern cmd_id        :byte

include useful.inc
include append.inc
include cmdline.inc
include dos.inc

old_int2f	dd	0	; Original INT 2F handler

cmdnambuf	dd	0	; Pointer to command name buffer
cmdlinbuf	dd	0	; Pointer to command line buffer
cmdlen		dw	0	; Real command length

; ===========================================================================
;  INT 2F HOOK
; ===========================================================================
;
int2f:		cmp	ah, 0AEh		; Installable command?
		je	i2fae
		cmp	ah, 0B7h		; APPEND ?
		je	i2fb700
;chain:		jmp	far [cs:old_int2f]	; Nope, chain to old handler
chain:		jmp	dword ptr cs:[old_int2f]	; Nope, chain to old handler

; ---------------------------------------------------------------------------
;  2FAE : INSTALLABLE COMMAND
; ---------------------------------------------------------------------------
;
i2fae:		cmp	dx, 0FFFFh		; Check magic number
		jne	chain

; ----- 2FAE00 : INSTALLABLE COMMAND - INSTALLATION CHECK -------------------
;
		cmp	al, 0
		jne	i2fae01

		call	check_name		; APPEND ?
		jne	chain			; Nope, chain to orig. handler

		mov	al, 0FFh		; Say YES and return
		iret

; ----- 2FAE01 : INSTALLABLE COMMAND - EXECUTE ------------------------------
;
i2fae01:	cmp	al, 1
		jne	chain

		call	check_name		; APPEND ?
		jne	chain

		mov	byte ptr [si], 0		; Do not execute on return

		mov	word ptr cs:[cmdnambuf], si	; Save command name and line
		mov	word ptr cs:[cmdnambuf+2], ds	; buffers
		mov	word ptr cs:[cmdlinbuf], bx	;
		mov	word ptr cs:[cmdlinbuf+2], ds	;

		mov	byte ptr cs:[p_flags], RESIDENT	; Set resident flag
							; and clean the rest

		push	bx
		push	cx
		push	es
		push	si

		xor	cx, cx
		inc	bx			;
		mov	cl, [bx]		; Get cmdline length
		sub	cx, cs:[cmdlen]		; Skip command
		add	bx, cs:[cmdlen]		;
		inc	bx

		push	ds
		pop	es

		mov	si, bx			; Parse cmd line (in es:si,
		call	parse_cmds		; length in cx)

		pop	si
		pop	es
		pop	cx
		pop	bx

		iret

; ---------------------------------------------------------------------------
;  2FB7 : APPEND
; ---------------------------------------------------------------------------
;


; ----- 2FB700 : APPEND - INSTALLATION CHECK --------------------------------
;
i2fb700:	cmp	al, 00h		; MS-DOS APPEND seems to use
		jne	i2fb701			; 0x10 instead.
						;
		mov	al, 0FFh
		iret

; ----- 2FB701 : APPEND - GET APPEND PATH (Microtek) ------------------------
;
i2fb701:	cmp	al, 01h
		jne	i2fb702
		jmp	i2fb704			; Same as 2FB704

; ----- 2FB702 : APPEND - GET VERSION ---------------------------------------
;
i2fb702:	cmp	al, 02h		; In MS-DOS 5.0+ APPEND this
		jne	i2fb703			; is a stub that returns
		mov	ax, 0FDFDh		; 0xFFFF
		iret

; ----- 2FB703 : APPEND - HOOK INT 21 ---------------------------------------
;
i2fb703:	cmp	al, 03h
		jne	i2fb704
		xor	byte ptr cs:[handler], USERHNDL	; Toggle flag
		mov	word ptr cs:[usr_int21], di		; Set user handler
		mov	word ptr cs:[usr_int21+2], es
		push	cs				; Returns append int21
		pop	es				; handler
		mov	di, offset int21usr
		iret

; ----- 2FB704 : APPEND - GET APPEND PATH -----------------------------------
;
i2fb704:	cmp	al, 04h
		jne	i2fb706
		push	cs
		pop	es
		mov	di, offset append_path
		iret

; ----- 2FB706 : APPEND - GET APPEND FUNCTION STATE -------------------------
;
i2fb706:	cmp	al, 06h
		jne	i2fb707
		mov	bx, cs:[append_state]
		iret

; ----- 2FB707 : APPEND - SET APPEND FUNCTION STATE -------------------------
;
i2fb707:	cmp	al, 07h
		jne	i2fb710
		mov	cs:[append_state], bx
		iret

; ----- 2FB710 : APPEND - GET VERSION INFO ----------------------------------
;
i2fb710:	cmp	al, 10h
		jne	i2fb711
		mov	ax, cs:[append_state]
		xor	bx, bx		; Emulate MS-DOS 5.0 APPEND
		xor	cx, cx		;
		mov	dl, 5		;
		mov	dh, 0		;
		iret

; ----- 2FB711 : APPEND - SET RETURN FOUND NAME STATE -----------------------
;
i2fb711:	cmp	al, 11h
		jne	end_i2fb7

		push	ax
		push	bx
		push	es
		@DosCall 51h		; Get caller's PSP pointer
		mov	es, bx
		mov	byte ptr es:[03Dh], 01h	; Set state in caller's PSP
		pop	es
		pop	bx
		pop	ax
		iret

end_i2fb7:	jmp	dword ptr cs:[old_int2f]


; ---------------------------------------------------------------------------
; Function: check_name - Checks if command name is "APPEND"
;
; Args:	    DS:BX      - Command line buffer
;
; Returns:  Set Zero flag if found
;
check_name:	
		push	ax
		push	bx
		push	cx
		push	dx
		push	di
		push	si
		push	es
		mov	cl, [bx+1]	; command line length
		cmp	cl, 6
		jc	ret1		; Less that 6 chars, it's not 'APPEND'
		xor	ch, ch		; Expand to cx
		add	bx, 2		; Points to first char
		push	bx
		cmp	byte ptr [bx+1], ':'	; Drive unit?
		jne	savini
		add	bx, 2		; Skip it
		sub	cx, 2
savini:		mov	dx, bx		; Save it
chkc:		mov	ah, [bx]
		call	isfnc		; Valid filename char?
		jc	chkback	; No, check for backslash
next:		toupper	ah,5
		mov	[bx], ah
		inc	bx
		dec	cx
		jcxz	completed
		jmp	chkc
chkback:	cmp	ah, '\'
		jne	completed
		mov	dx, bx		; Save position
		inc	dx		; skip backslash
		jmp	next
completed:	mov	si, dx
		mov	cs:[cmdlen], bx	; Calculate total command length
		sub	bx, dx		; Calculate length
		pop	dx		; Recover original pointer
		sub	cs:[cmdlen], dx	;
		mov	cx, bx
		cmp	cx, 6		; If its not 6 bytes long, it is not
		jne	ret1		; APPEND
		mov	ax, cs
		mov	es, ax
		mov	di, offset cmd_id	; "APPEND"
		cld
		repe	cmpsb
ret1:		pop	es
		pop	si
		pop	di
		pop	dx
		pop	cx
		pop	bx
		pop	ax
		ret
isfnc:				; Check if char is valid for filename
		push	cx
		push	si
		push	ds
		push	cs
		pop	ds
		mov	cx, nfnccount
		mov	si, offset nfnc
loop1:		lodsb
		cmp	ah, al
		stc
		je	ret2
		loop	loop1
		clc
ret2:		pop	ds
		pop	si
		pop	cx
		ret
nfnc		db	07fh, 03bh,' "/\[]:|<>+=,'
nfnccount	equ	($-nfnc)

       end
