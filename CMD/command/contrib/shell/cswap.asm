; $Id$
; File:
;                          cswap.asm
; Description:
;                       command.com swapping
;
;                    Copyright (c) 2001 tom ehlert
;                       All Rights Reserved
;
; This file is part of DOS-C.
;
; DOS-C is free software; you can redistribute it and/or
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
; write to the Free Software Foundation, 675 Mass Ave,
; Cambridge, MA 02139, USA.
;
;

.386

include model.inc
include stuff.inc

_BSS  segment word public 'BSS'  use16 ; transient data (in DS)

 	public _SwapResidentSize
_SwapResidentSize  dw 1

	public _XMSsave
_XMSsave	dw 8
currentSegmOfFreeCOMsave	equ	_XMSsave+8

execSS dw 1
execSP dw 1

_BSS  ends

_DATA segment word public 'DATA' use16

resize_free db 4ah

_DATA ends

ifidn __OUTPUT_FORMAT__,elf ; GCC/ELF: no seg so use linker script symbol
extern _TEXTSEG
else
_TEXT segment word public 'CODE' use16

_TEXTSEG equ _TEXT
endif

	public _dosFCB1
	public _dosFCB2
_dosFCB1 db 37 dup (0)
_dosFCB2 db 37 dup (0)

;;	global _dosCMDTAIL, _dosCMDNAME		use command line from within PSP
	public _dosCMDNAME
;;_dosCMDTAIL  times 128 db 0
_dosCMDNAME db 128 dup (0)
	   db 256 dup (0)
	public localStack
localStack:

	public _dosParamDosExec
_dosParamDosExec db 22	dup (0)


	public _XMSdriverAdress
_XMSdriverAdress dd 0
callXMS macro
	call dword ptr [_XMSdriverAdress]
	endm

 	public _SwapTransientSize
_SwapTransientSize  dw 0

	public _XMSrestore
_XMSrestore	DW 8 dup (0)
xms_handle		equ	_XMSrestore+4
currentSegmOfFreeCOM	equ	_XMSrestore+14

	public _canexit
_canexit	DB 0		; 1 -> can exit; _else_ --> cannot exit
filler  DB 0

    public mySS, mySP
mySS DW 0
mySP DW 0

execRetval dw 0

real_XMSexec:
		int 21h	; shrink/free: first thing done from resident code

		; do exec


;;		mov ax, cs
                   		; ds:dx = ASCIZ program name
;;		mov ds, ax
		movzx  dx,_dosCMDNAME
		       
                        ; es:bx = parameter block
		mov es, cx
		movzx bx, _dosParamDosExec


						; our temporary stack
;;        mov ss, ax
;;        mov  sp,localStack


		mov ax,04b00h		; load & execute
		int 21h

		jc  exec_error
		xor ax,ax


exec_error:
		cld					; don't rely on that

	; reload into memory

        mov cx, cs
        mov ss, cx
        mov  sp,localStack-6	; location on stack of return cs:ip and ds

		; restore:

        mov ds, cx
		mov [execRetval],ax
							; we need some memory

		;; First ensure that FreeCOM is reloaded in low memory
		;; so that LOADHIGH would come into problems
;;ska		mov ax, 5800h		; Get current allocation strategy
;;ska		int 21h
;;ska		mov dx, ax

;;ska		mov ax, 5801h		; Set current allocation strategy
;;ska		mov bx, 0			; low memory / first fit
;;ska		int 21h
		; ignore any errors

		mov ah,48h
		mov bx,[_SwapTransientSize]
		int 21h

;;ska		pushf

		; Restore Alloc Strat
;;ska		mov ax, 5801h		; Set current allocation strategy
;;ska		mov bx, dx
;;ska		int 21h

;;ska		popf
		jc DOS_trouble_while_swapping_in

                                ; calculate relocation factor

		mov bx,ax				; new execute address
		sub bx,[currentSegmOfFreeCOM]		; new address - old address
		push bx					;
		mov  [currentSegmOfFreeCOM],ax	; new prog address

								; restore everything to XMS
		mov ah,0bh
		mov si, _XMSrestore
		callXMS

		pop bx                  ; get relocation factor back

		cmp ax,1
		jnz XMS_trouble_while_swapping_in

		mov bp,sp
		add [bp+2],bx		; relocate return segment

		retf						; done

XMS_err 		db 'XMS copy error$'
DOS_err 		db 'Memory allocation error$'
common_error	db 0dh,0ah,0ah,'FreeCOM: XMSSwap-In: $'

XMS_trouble_while_swapping_in:
	movzx bx, XMS_err
	jmp short trouble_while_swapping_in

DOS_trouble_while_swapping_in:
	movzx bx, DOS_err

trouble_while_swapping_in:
;		push cs							; do some error message
;		pop  ds
		movzx dx, common_error
		mov ah,09
		int 21h

		mov dx,bx
		mov ah,09
		int 21h

terminate_myself:
		mov ax,04cffh					; and die ...
		int 21h

		;; FALL THROUGH for elder FreeCOM kernels that simply ignore
		;; DOS-4C for shells
		extrn _terminateFreeCOMHook: far
		jmp _terminateFreeCOMHook

	public xms_kill
xms_kill:
	; Kill the XMS memory block
	mov dx, [xms_handle]
	or dx, dx
	jz terminate_myself		; no block to deallocate
	mov ah, 0ah				; deallocate XMS memory block
	callXMS
	ret

;
; as I don't know how to set the old interrupt handler
; I write my own
; or we use the TURBO_C _restorezero() and use the
; DOS default handler for that

if 0
MsgZerodivide db 'integer zero divide$'
	global _ZeroDivideInterrupt
_ZeroDivideInterrupt:

		push cs
		pop ds
		mov dx,MsgZerodivide
		mov ah,09
		int 21h

        mov ax,04c7fh       ; terminate with errorlevel 127
        int 21h
		jmp _ZeroDivideInterrupt
endif


;********************************************************************
; *************   END OF RESIDENT AREA ******************************
;********************************************************************
	public _SWAPresidentEnd
_SWAPresidentEnd:

if 0
;
; normal EXEC
;

		public _DosEXEC
_DosEXEC:
						; save ALL registers needed later
		push si
		push di
		push bp
		push ds

		push cs                   		; ds:dx = ASCIZ program name
		pop	 ds

		mov  dx,_dosCMDNAME

		mov [execSS],ss
		mov [execSP],sp

		push cs
		pop  es
		mov bx, _dosParamDosExec

		mov ax,04b00h
		int 21h

		jc      exec_error2  ; if there was an error, the error code is in AX

		xor ax,ax

exec_error2:

		cld					; don't rely on that

		mov ss,[cs:execSS]
		mov sp,[cs:execSP]

		pop ds
		pop bp
		pop di
		pop	si
		retf
endif

;; Added here to make it more easier for the C-part to make a XMS
;; request, because the code:
;;		(*XMSdriverAdress)();
;; is translated into something like:
;;		mov ax, _CODE		;; immediate value
;;		mov es, ax
;;		call DWORD PTR es:[_XMSdriverAdress]
;; detroying AX already holding the API function number

;; To be called with _far_!!
	public XMSrequest
	;; Note: Because [CS:driverAdress] == [residentCS:driverAdress]
	;; we need not use a similiar approach as with XMSexec
XMSrequest:
		jmp dword ptr [cs:_XMSdriverAdress]

;; Added here to make it more easier for the C-part to call functions
;; located in the resident part, because:
;;		_XMSexec();
;; is translated into something like:
;;		nop
;;		push cs			<-> WRONG!!
;;		call _XMSexec
;; now also used to contain code that does not need to be resident.

;;TODO: DS ought to be equal to SS, DS could be reconstructed from
;;	SS at the end of the XMSexec function
		public	_XMSexec
_XMSexec:
						; save ALL registers needed later
ifidn __OUTPUT_FORMAT__,elf 	; GCC: need to preserve es
		push es
endif
		push si
		push di
		push bp

		mov [execSS],ss
		mov [execSP],sp

						; save everything to XMS
		mov ah,0bh
		mov si, _XMSsave
		call dword ptr [cs:_XMSdriverAdress]

;;TODO: test of result

		mov es,[currentSegmOfFreeCOMsave]
						; first time: shrink current psp
		mov ah,[resize_free]
		mov bx,[_SwapResidentSize]

		mov dx, ds
		mov cx, _TEXTSEG
reloc1 equ $-2
		mov ds, cx

        mov [mySS],ss  ; 2E
        mov [mySP],sp  ; 2E

		mov ss, cx		; this stack is definitely large enough AND present
        mov  sp,localStack

		push dx			; save DS of transient portion
		call _TEXTSEG:real_XMSexec
reloc2 equ $-2

ret_from_resident:
		mov ax,[execRetval]

                                    ; relocate segment registers
		add [bp+4],bx				; ds
		pop ds

		mov byte ptr [resize_free],49h ; change to "free" for next times

		add [currentSegmOfFreeCOMsave],bx
		mov cx,[execSS]
		add cx,bx
		mov ss,cx
		mov sp,[execSP]

ifidn MODEL, m                     ; in medium & large need to fixup return segment
		mov bp, sp
		add [bp+8],bx
endif
		pop bp
		pop di
		pop si
ifidn __OUTPUT_FORMAT__,elf 	; GCC: need to preserve es
		pop es
endif
		ret							; done (really), retn/retf based on memory model, see model.inc

_TEXT ends

      end
