; File:
;                          termhook.asm
; Description:
;                       command.com termination hook
;
; This program is free software; you can redistribute it and/or
; modify it under the terms of the GNU General Public License
; as published by the Free Software Foundation; either version
; 2, or (at your option) any later version.
;
; This program is distributed in the hope that it will be useful, but
; WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
; the GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public
; License along with this program; see the file COPYING.  If not,
; write to the Free Software Foundation, 675 Mass Ave,
; Cambridge, MA 02139, USA.
;
;

include model.inc
include stuff.inc

.386

_TEXT  segment word public 'CODE' use16

	public _termAddr

_termAddr:
terminationAddressOffs	DW 0
terminationAddressSegm	DW 0

	extrn _canexit: far
	public _myPID
_myPID	DW 0
	public _origPPID
_origPPID DW 0

	;; central PSP:0xa hook <-> may be called in every circumstance
	public _terminateFreeCOMHook

_terminateFreeCOMHook:
ifndef XMS_SWAP
	dec BYTE PTR [_canexit]
endif
	mov ax, cs				; setup run environment (in this module)
	mov ds, ax
ifdef XMS_SWAP
	extrn localStack: near
	mov ss, ax
	mov sp, localStack

	; Next time we hit here it's != 1 --> no zero flag --> I_AM_DEAD status
	dec BYTE PTR [_canexit]
endif
	jnz I_AM_DEAD

	mov ax, [_myPID]		; our own PSP [in case we arrived here
	mov es, ax				; in some strange ways]

	; Make sure the current PSP hasn't patched to nonsense already
	mov bx, ax
	mov ah, 50h				; Set PSP
	int 21h

	; Reset old termination address
	mov ax, [terminationAddressOffs]
	mov [es:0ah], ax
	mov ax, [terminationAddressSegm]
	mov [es:0ch], ax

	; Drop our "Shell" privileges
	mov ax, [_origPPID]		; original parent process ID
	mov [es:16h], ax

	; Kill the XMS memory block
ifdef XMS_SWAP
	extrn xms_kill: near
	call xms_kill
endif

	; Now, DOS-4C should proceed correctly
	mov ax,04cffh					; and die ...
	int 21h


I_AM_DEAD:								; process 0 can't terminate ...
	movzx dx, dead_loop_string
	mov ah, 9
	int 21h
I_AM_DEAD_loop:
	hlt
	jmp short I_AM_DEAD_loop

dead_loop_string	DB 13,10,7,'Cannot terminate permanent FreeCOM instance'
	DB 13,10,'System halted ... reboot or power off now$'

_TEXT  ends

       end
