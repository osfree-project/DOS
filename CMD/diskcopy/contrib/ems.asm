;;
;;   EMS.ASM - routines to use Extended Memory from a DOS program.
;;
;;   Copyright (C) 2000, 2001 Imre Leber.
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
;; Routines to use Epanded Memory from a DOS program.
;;
;; NOTE: translation from the EMS routines by Cliff Rhodes to NASM by
;;       Imre Leber.
;;
;; The C version was released to the public domain by Cliff Rhodes with
;; no guarantees of any kind.
;;
;; The assembly version is hereby put under GNU General Public License by
;; Imre Leber.
;;
;;*************************************************************************
;; Last changed:
;;
;;      april 16, 2001: Fixed situation where si and di not saved.
;;
.8086


;=============================== DATA =====================================

_DATA	segment word public 'DATA' use16

EMS_INT		EQU	67h      ;; EMS interrupt number.
EMS_VERSION	EQU	32h      ;; Version 3.2 of EMS. 
RES_VERSION	EQU	40h      ;; At least version 4.0 to be resizable.

; EMS service codes.
EMSservice1  EQU	40h    ;; Get EMS status.
EMSservice2  EQU	41h    ;; Get segment address of page 0. 
EMSservice3  EQU	42h    ;; Get total number of expanded pages.
EMSservice4  EQU	43h    ;; Get handle and assign pages to it.
EMSservice5  EQU	44h    ;; Map a page into one of the page frames.
EMSservice6  EQU	45h    ;; Close EMS handle.
EMSservice7  EQU	46h    ;; Get the EMS version number.

ID_LEN 	EQU	8/2
EMS_ID	db "EMMXXXX0" ;; EMS identification string.

;=============================== CODE =====================================

_DATA	ends

_TEXT	segment  word public 'CODE' use16

;==========================================================================
;===                           EMSbaseaddress                           ===
;==========================================================================
;=== unsigned int EMSbaseaddress(void);                                 ===
;===                                                                    ===
;=== Determines if EMS present. If so returns base segment of EMS.      ===
;=== Returns 0 if EMS not available. The base segment is necessary      ===
;=== for mapping EMS memory pages into the user address space (see      ===
;=== EMSmap() below).                                                   ===
;==========================================================================

	public EMSbaseaddress_
EMSbaseaddress_:
        push  es
	push  si
	push  di

        cld

        mov  ax, 3567h
        int  21h

        mov  si, offset EMS_ID
        mov  cx, ID_LEN
        mov  di, 10              ;; EMS_ID must be at offset 10

        repe cmpsw
        je   next

        xor  ax, ax
        jmp  EndOfProc1

next:
        mov  ah, EMSservice2     ;; Get page frame segment.
        int  EMS_INT

        cmp  ah, 0
        je   GotFrame

        xor  ax, ax
        jmp  EndOfProc1

GotFrame:
        mov  ax, bx
        
EndOfProc1:
	pop  di
	pop  si
        pop  es
        ret


;==========================================================================
;===                              EMSversion                            ===
;==========================================================================
;=== int EMSversion(void);                                              ===
;===                                                                    ===
;=== Returns current EMS version, -1 if not found or obsolete.          ===
;==========================================================================

        public EMSversion_
EMSversion_:

        mov  ah, EMSservice7
        int  EMS_INT

        cmp  ah, 0
        jne  NotGood

        cmp  al, EMS_VERSION
        jb   NotGood
        jmp  EndOfProc2

NotGood:
        mov  ax, -1

EndOfProc2:
        ret

;==========================================================================
;===                             EMSstatus                              ===
;==========================================================================
;=== int  EMSstatus(void);                                              ===
;===                                                                    ===
;=== Returns 0 if EMS system OK, -1 if not.                             ===
;==========================================================================

        public EMSstatus_
EMSstatus_:

        mov  ah, EMSservice1
        int  EMS_INT

        cmp  ah, 0
        je   next1

        mov  ax, -1
        jmp  EndOfProc3

next1:
        xor  ax, ax

EndOfProc3:
        ret

;==========================================================================
;===                             EMSpages                               ===
;==========================================================================
;=== int EMSpages(void);                                                ===
;===                                                                    ===
;=== Returns number of free EMS pages (each page is 16k), -1 if error.  === 
;==========================================================================

        public EMSpages_
EMSpages_:

        mov  ah, EMSservice3
        int  EMS_INT

        cmp  ah, 0
        je   next01

        mov  ax, -1
        jmp  EndOfProc4

next01:
        mov  ax, bx

EndOfProc4:
        ret

;==========================================================================
;===                              EMSalloc                              ===
;==========================================================================
;=== int EMSalloc(int pages);                                           ===
;===                                                                    ===
;=== Returns handle to block of size pages or -1 if error.              ===
;===                                                                    ===
;=== NOTE: always free any handles when you are done!.                  ===
;==========================================================================

        public EMSalloc_
EMSalloc_:
        mov  bx, sp

        mov  ah, EMSservice4
        mov  bx, [ss:bx+02h]
        int  EMS_INT

        cmp  ah, 0
        je   next2

        mov  ax, -1
        jmp  EndOfProc5

next2:
        mov  ax, dx

EndOfProc5:
        ret

;==========================================================================
;===                              EMSfree                               ===
;==========================================================================
;=== int EMSfree(int handle);                                           ===
;===                                                                    ===
;=== Frees handle block, returns 0 if successful, -1 if error.          ===
;==========================================================================

        public EMSfree_
EMSfree_:
        mov   bx, sp

        mov  ah, EMSservice6
        mov  dx, [ss:bx+02h]
        int  EMS_INT

        cmp  ah, 0
        je   next3

        mov  ax, -1
        jmp  EndOfProc6

next3:
        xor  ax, ax

EndOfProc6:
        ret

;=============================================================================
;===                                EMSmap                                 ===
;=============================================================================
;=== int  EMSmap(int bank, int handle, int page);                          ===
;===                                                                       ===
;=== Maps page of handle into bank. Returns 0 if successful, -1 if error.  ===
;=== Each handle controls 1 or more 16k pages of EMS memory.               ===
;=== There are four banks 0-3. bank 0 starts at the segment returned by    ===
;=== EMSbaseaddress(), bank 1 starts at that segment with offset 16k, etc. ===
;=============================================================================

        public EMSmap_
EMSmap_:
        push bp
        mov  bp, sp

        mov  ax, [bp+04h]      ; bank.
        mov  bx, [bp+08h]      ; page.
        mov  dx, [bp+06h]      ; handle.
        mov  ah, EMSservice5
        int  EMS_INT

        cmp  ah, 0
        je   EndOfProc7

        mov  ax, -1

EndOfProc7:
        pop  bp
        ret

	if 0
;=========================================================================
;===                            EMSResizable                           ===
;=========================================================================
;=== int EMSResizable();                                               ===
;===                                                                   ===
;=== Returns wether the pages allocated for a certain handle can be    ===
;=== changed.                                                          ===
;=========================================================================

        public EMSResizable_
EMSResizable_:

        mov  ah, EMSservice7                    ;; Get version number, 
        int  EMS_INT

        cmp  al, RES_VERSION                    ;; and see if it is at 
        jb   NotSupported                      ;; least version 4.0.

        mov  ax, 1
        jmp  EndOfProc8

NotSupported:
        xor  ax, ax

EndOfProc8:
        ret

;=========================================================================
;===                            EMSResize                              ===
;=========================================================================
;=== int EMSResize(int handle, int pages);                             ===
;===                                                                   ===
;=== Change the amount of pages allocated for a certain handle.        ===
;===                                                                   ===
;=== Remark: check first wether this function is supported.            ===
;===                                                                   ===
;=== Returns: 0 on success, -1 or error.                               ===
;=========================================================================

        public EMSResize_
EMSResize_:

        push bp
        mov  bp, sp

        mov  ah, 51h
        mov  dx, [bp+04h]
        mov  bx, [bp+06h]
        int  EMS_INT

        cmp  ah, 0
        je   next4

        mov  ax, -1
        jmp  EndOfProc9

next4:
        xor  ax, ax

EndOfProc9:
        pop  bp
        ret

	endif

_TEXT	ends
	end
