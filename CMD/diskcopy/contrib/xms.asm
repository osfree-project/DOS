;;
;;   XMS.ASM - routines to use Extended Memory from a DOS program.
;;
;;   Copyright (C) 1999, 2000, 2001, Imre Leber.
;;
;;   This program is free software; you can redistribute it and/or modify
;;   it under the terms of the GNU General Public License as published by
;;   the Free Software Foundation; either version 2 of the License, or
;;   (at your option) any later version.
;;
;;   This program is distributed in the hope that it will be useful,
;;   but WITHOUT ANY WARRANTY; without even the implied warranty of
;;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;   GNU General Public License for more details.
;;
;;   You should have recieved a copy of the GNU General Public License
;;   along with this program; if not, write to the Free Software
;;   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
;;
;;   If you have any questions, comments, suggestions, or fixes please
;;   email me at:  imre.leber@worlonline.be
;;
;;
;;*************************************************************************
;;
;; XMS.ASM
;;
;; Routines to use Extended Memory, the HMA and upper memory from
;; a DOS program.
;;
;; NOTE: Some of these routines are translations from the XMS routines 
;;       by Cliff Rhodes to NASM by Imre Leber.
;;
;; The C version was released to the public domain by Cliff Rhodes with
;; no guarantees of any kind.
;;
;; The assembly version is hereby put under GNU General Public License by
;; Imre Leber.
;;
;;**************************************************************************
;; version: 24 dec 1999
;;

.8086

;; just to be on the save side.
SaveRegs macro
	push si
	push di
	push ds
	endm

RestoreRegs macro
	pop  ds
	pop  di
	pop  si
	endm

XMS_INT	EQU	002fh     ;; DOS Multiplex interrupt

_DATA	segment word public 'DATA' use16
        
        XMSDriver DD   0
        initFlag  DB  -1

;;struct XMSRequestBlock bd.
bd equ $
nbytes  dd 0    ;; Number of bytes to move
shandle dw 0    ;; Handle of source memory
soffset dd 0    ;; Offset of source in handle's memory area
dhandle dw 0    ;; Handle of destination memory
doffset dd 0    ;; Offset of destination in memory

UMBsize dw 0    ;; size of the last successfully allocated UMB.
_DATA	ends

	assume ds:_DATA
_TEXT	segment word public 'CODE' use16

;*********************** routines for the EMB's **************************

;==========================================================================
;===                        XMMinit (XMSinit)                           ===
;==========================================================================
;=== int  XMMinit(void); or int XMSinit(void);                          ===
;===                                                                    ===
;=== Verifies wether an eXtended Memory Manager is installed.           ===
;===                                                                    ===
;=== Returns 1 if manager found, 0 if not.                              ===
;===                                                                    ===
;=== NOTE:This function should be called before any other XMS function! ===
;==========================================================================

        public XMSinit_
        public XMMinit_
XMSinit_:
XMMinit_:
        push  bp
        SaveRegs

        cmp  [ds:initFlag], -1
        jne  EndOfProc

        mov  [ds:initFlag], 0

        mov  ax, 4300h                ;; Verify XMS manager present.
        int  XMS_INT
        cmp  al, 80h
        je   next
        xor  ax, ax
        jmp  EndOfProc

next:
        mov  ax, 4310h                ;; Get XMS manager entry point.
        int  XMS_INT
        mov  word ptr [ds:XMSDriver], bx     ;; Save entry point.
        mov  word ptr [ds:XMSDriver+02h], es

        xor  ah, ah
        call dword ptr [ds: XMSDriver]    ;; See if at least version 2.0
        cmp  ax, 0200h
        jb   EndOfProc
        
        mov  [ds:initFlag], 1
        
EndOfProc:
        xor  ah, ah
        mov  al, [ds:initFlag]

        RestoreRegs
        pop  bp
        ret

;=========================================================================
;===                           XMScoreleft                             ===
;=========================================================================
;=== long XMScoreleft(void);                                           ===
;===                                                                   ===
;=== Returns number of bytes available in largest free block.          ===
;=========================================================================

        public XMScoreleft_
XMScoreleft_:
        push bp
        SaveRegs

        cmp  [initFlag], 0
        jne  next2

        xor  ax, ax
        xor  dx, dx
        jmp  EndOfProc2

next2:
        mov  ax, 0800h
        call [XMSDriver]
        mov  bx, 1024
        mul  bx

EndOfProc2:
        RestoreRegs
        pop  bp
        ret

;==========================================================================
;===                            XMSalloc                                ===
;==========================================================================
;=== unsigned int XMSalloc(long size);                                  ===
;===                                                                    ===
;=== Attempts to allocate size bytes of extended memory.                ===
;===                                                                    ===
;=== Returns handle if successful, 0 if not.                            ===
;===                                                                    ===
;=== NOTE: Actual size allocated will be the smallest multiple of 1024  ===
;===       that is larger than size.                                    ===
;==========================================================================

        public XMSalloc_
XMSalloc_:
        push bp
        mov  bp, sp

        SaveRegs

        cmp  [initFlag], 0
        jne  next3

        xor  ax, ax
        jmp  EndOfProc3
next3:

      ;;Get the number of 1024 byte units required by size.
        mov  ax, [bp+04h]
        mov  dx, [bp+06h]

        mov  bx, 1024
        div  bx

        cmp  dx, 0
        je   next31

      ;;Add a block for any excess.
        inc  ax

next31:
        mov  dx, ax
        mov  ax, 0900h

        call [XMSDriver]
        cmp  ax, 1
        je   next32

        xor  ax, ax
        jmp  EndOfProc3

next32:
        mov  ax, dx

EndOfProc3:
        RestoreRegs
        pop  bp
        ret

	if 0
;==========================================================================
;===                            XMSrealloc                              ===
;==========================================================================
;===  int XMSrealloc(unsigned int handle, long size);                   ===
;===                                                                    ===
;===  Tries to expand or schrink a certain extended memory block.       ===
;===                                                                    ===
;===  Returns 1 if successful, 0 if not.                                ===
;==========================================================================

        global XMSrealloc_
XMSrealloc_:
        push bp
        mov  bp, sp
        
        mov  ax, [bp+06h]
        mov  dx, [bp+08h]

        mov  bx, 1024
        div  bx

        cmp  dx, 0
        je   next41

      ;;Add a block for any excess.
        inc  ax

next41:
        mov  dx, [bp+04h]
        mov  bx, ax
        mov  ax, 0f00h
        call [XMSDriver]
        
        pop  bp
        ret
	endif
;===========================================================================
;===                            XMSfree                                  ===
;===========================================================================
;=== int  XMSfree(unsigned int handle);                                  ===
;===                                                                     ===
;=== Attempts to free extended memory referred to by handle. Returns 1   ===
;=== if successful, 0 if not.                                            ===
;===========================================================================

        public XMSfree_
XMSfree_:

        push bp
        mov  bp, sp

        SaveRegs

        cmp  byte ptr [initFlag], 0
        jne  next5

        xor  ax, ax
        jmp  EndOfProc5

next5:
        mov  dx, [bp+04h]
        mov  ax, 0a00h

        call [XMSDriver]

EndOfProc5:
        RestoreRegs
        pop  bp
        ret

;------------------------------------------------------------------------
;---                               XMSmove                            ---
;------------------------------------------------------------------------
;--- private: XMSmove                                                 ---
;---                                                                  ---
;--- Copy memory to and from XMS.                                     ---
;---                                                                  ---
;--- in: ax: number of bytes to copy.                                 ---
;---                                                                  ---
;--- out: ax: number of bytes copied (0 if error).                    ---
;------------------------------------------------------------------------

XMSmove:
        push ax
        mov  word ptr [nbytes], ax
        mov  word ptr [nbytes+02h], 0

        mov  si, word ptr bd
        mov  ah, 0Bh
        call [XMSDriver]
        pop  dx
        cmp  ax, 0
        je   EndOfProc6

        mov  ax, dx

EndOfProc6:
        ret

;===========================================================================
;===                           DOStoXMSmove                              ===
;===========================================================================
;=== int  DOStoXMSmove(unsigned int desthandle, long destoff,            ===
;===                   const char *src, unsigned n);                     ===
;===                                                                     ===
;=== Attempts to copy n bytes from DOS src buffer to desthandle memory   ===
;=== area.                                                               ===
;=== Returns number of bytes copied, or 0 on error.                      ===
;===========================================================================

        public DOStoXMSmove_
DOStoXMSmove_:

        push bp
        mov  bp, sp

        SaveRegs

        cmp  byte ptr [initFlag], 0
        jne  next7

        xor  ax, ax
        jmp  EndOfProc7

next7:
        mov  word ptr [shandle], 0

        mov  ax, [bp+04h]
        mov  [dhandle], ax

        mov  ax, [bp+06h]
        mov  word ptr [doffset], ax
        mov  ax, [bp+08h]
        mov  word ptr [doffset+02h], ax

        mov  ax, [bp+0Ah]
        mov  word ptr [soffset],     ax
        mov  ax, ds
        mov  word ptr [soffset+02h], ax

        mov  ax, [bp+0Ch]
        call XMSmove

EndOfProc7:
        RestoreRegs
        pop  bp
        ret

;==========================================================================
;===                            XMStoDOSmove                            ===
;==========================================================================
;=== int  XMStoDOSmove(char *dest, unsigned int srchandle, long srcoff, ===
;===                   unsigned n);                                     ===
;===                                                                    ===
;=== Attempts to copy n bytes to DOS dest buffer from srchandle memory  ===
;=== area.                                                              ===
;===                                                                    ===
;=== Returns number of bytes copied, or 0 on error.                     ===
;==========================================================================

        public XMStoDOSmove_
XMStoDOSmove_:

        push bp
        mov  bp, sp

        SaveRegs

        cmp  byte ptr [initFlag], 0
        jne  next8

        xor  ax, ax
        jmp  EndOfProc8

next8:
        mov  word ptr [dhandle], 0

        mov  ax, [bp+04h]
        mov  word ptr [doffset], ax
        mov  ax, ds
        mov  word ptr [doffset+02h], ax
      
        mov  ax, [bp+06h]
        mov  word ptr [shandle], ax

        mov  ax, [bp+08h]
        mov  word ptr [soffset], ax
        mov  ax, [bp+0Ah]
        mov  word ptr [soffset+02h], ax

        mov  ax, [bp+0Ch]
        call XMSmove

EndOfProc8:
        RestoreRegs
        pop  bp
        ret

;*********************** routines for the HMA ****************************
	ifdef INCLUDEHMA
;==========================================================================
;===                           HMAalloc                                 ===
;==========================================================================
;=== int HMAalloc(void);                                                ===
;===                                                                    ===
;=== Allocates the HMA if it is available.                              ===
;===                                                                    ===
;=== Returns: 1 on success, 0 on failure.                               ===
;==========================================================================

        public _HMAalloc
_HMAalloc:
        SaveRegs

        mov  ah, 01h
        mov  dx, 0FFFFh
        call far [dword XMSDriver]       ;; Allocate HMA.

        cmp  ax, 0
        je   EndOfProc9                  ;; exit on error.

        mov  ah, 03h
        call far [dword XMSDriver]       ;; Open gate A20.

        cmp  ax, 0                       ;; exit on success.
        jne  EndOfProc9

        mov  ah, 02h
        call far [dword XMSDriver]       ;; release the HMA on failure.
        xor  ax, ax

EndOfProc9
        RestoreRegs
        ret

;==========================================================================
;===                           HMAcoreleft                              ===
;==========================================================================
;=== int HMAcoreleft(void);                                             ===
;===                                                                    ===
;=== Returns the size of the HMA in bytes.                              ===
;===                                                                    ===
;=== Remark: Only returns the right size after the HMA has been         ===
;===         succesfully allocated.                                     ===
;==========================================================================

        public _HMAcoreleft
_HMAcoreleft:

        mov  ax, 65520

        ret

;==========================================================================
;===                           HMAfree                                  ===
;==========================================================================
;=== int HMAfree(void);                                                 ===
;===                                                                    ===
;=== Deallocates the HMA.                                               ===
;===                                                                    ===
;=== Only call if the HMA has been successfully allocated.              ===
;==========================================================================

        public _HMAfree
_HMAfree:
        SaveRegs

        mov  ah, 04h
        call far [dword XMSDriver]

        mov  ah, 02h
        call far [dword XMSDriver]

        RestoreRegs
        ret
	endif
;*********************** routines for the UMB's ****************************
	ifdef INCLUDEUMB
;==========================================================================
;===                             UMBalloc                               ===
;==========================================================================
;===  unsigned int UMBalloc(void);                                      ===
;===                                                                    ===
;=== Allocates the largest UMB that can be allocated and returns        ===
;=== it's segment or 0 if error.                                        ===
;===                                                                    ===
;=== Remark: UMB's work with 16 byte blocks.                            ===
;==========================================================================

        public _UMBalloc
_UMBalloc:
        SaveRegs

        mov  ah, 10h
        mov  dx, 0FFFFh
        call far [dword XMSDriver]        ;; Get largest free UMB size.
        mov  ah, 10h
        call far [dword XMSDriver]        ;; Allocate largest UMB.
        
        cmp  ax, 1
        jne  EndOfProc0

        mov  ax, bx
        mov  [UMBsize], dx

EndOfProc0:
        RestoreRegs
        ret

;==========================================================================
;===                             GetUMBSize                             ===
;==========================================================================
;===  unsigned int GetUMBsize(void);                                    ===
;===                                                                    ===
;===  Returns the size of the most recent successfully allocated UMB.   ===
;==========================================================================

        public _GetUMBSize
_GetUMBSize:

        mov  ax, [UMBsize]

        ret

;==========================================================================
;===                              UMBfree                               ===
;==========================================================================
;=== int UMBfree (unsigned int segment);                                ===
;===                                                                    ===
;=== Releases an UMB (returns 1 on success, 0 on error).                ===
;==========================================================================

        public _UMBfree
_UMBfree:
        mov  bx, sp

        SaveRegs

        mov  ah, 11h
        mov  dx, [ss:bx+02h]

        call far [dword XMSDriver]

        RestoreRegs
        ret
	endif

_TEXT	ends
	end
