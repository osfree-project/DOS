; Copyright 2022 S. V. Nickolas.
;
; Permission is hereby granted, free of charge, to any person obtaining a copy 
; of this software and associated documentation files (the "Software"), to 
; deal with the Software without restriction, including without limitation the 
; rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
; sell copies of the Software, and to permit persons to whom the Software is 
; furnished to do so, subject to the following conditions:
;
;   1. Redistributions of source code must retain the above copyright notice, 
;      this list of conditions and the following disclaimers.
;   2. Redistributions in binary form must reproduce the above copyright 
;      notice, this list of conditions and the following disclaimers in the 
;      documentation and/or other materials provided with the distribution.
;   3. The name of the author may not be used to endorse or promote products 
;      derived from this Software without specific prior written permission.
;
; THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED 
; WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
; MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
;
; IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
; SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
; PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
; WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
; OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
; ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

; Revision History:
;
;    07/11/2022  usotsuki
;                Initial version.
;
;    07/11/2022  usotsuki (2)
;                Reduce memory footprint
;
;    07/12/2022  usotsuki
;                Additional documentation/comments
;
;    07/12/2022  usotsuki (2)
;                Fine tuning

; ============================================================================
; WARNING: Do not use MS-DOS's GRAFTABL to try to update the charset buffer of
;          DOSLITE GRAFTABL.  It will fail (lock the system).  Also, MS-DOS's
;          GRAFTABL will not detect the codepage in our GRAFTABL, although we
;          will detect it in theirs.
; ============================================================================

; This is GRAFTABL, a tool for loading the necessary data to render characters
; $80-FF in graphics mode on a CGA.  (Yes, it's that specific.  If you need
; this support for anything else, that is what DISPLAY.SYS is for.)
;
; Technically we could have probably gotten away with only supporting codepage
; 437 - the ROM codepage - but we instead support all the codepages of MS-DOS
; 5 and 6.  This does not affect our resident footprint; only the size of the
; generated binary, because the data is held in the transient portion of the
; file.
;
; If there are questions about the legality of the data, feel free to replace
; it; I believe it does not qualify for copyright under United States law
; (font data is, as far as I know, only copyrightable in the form of vectors)
; but it WAS extracted from a Microsoft CPI, probably that of Windows 95, many
; years ago (2000, to be precise).
;
; Syntax: GRAFTABL [codepage]
;         GRAFTABL /STA[TUS]
;
; If no codepage is specified, 437 is assumed.
; Only three characters of the switch /STATUS are significant, so you could
; type /STATUS, /STA, or /STANDINTHEPLACEWHEREYOUWERE with the same result.
;
; Assemble with NASM using default settings.
; Use the switch -DHELP to assemble in command-line help (adds a small amount
; of heft to the transient portion).

          .8086

	include dos.inc
	
_TEXT segment word public 'CODE' use16
          org       100h

extern TXT_MSG_BAD_PARM1: near
extern TXT_MSG_INCORRECT_DOSVERSION: near
extern TXT_MSG_GRAFTABL_US_LOADED: near
extern TXT_MSG_GRAFTABL_CANADIAN_LOADED: near
extern TXT_MSG_GRAFTABL_PORTUGUESE_LOADED: near
extern TXT_MSG_GRAFTABL_NORDIC_LOADED: near
extern TXT_MSG_GRAFTABL_US_LOADED_ALREADY: near
extern TXT_MSG_GRAFTABL_CANADIAN_LOADED_ALREADY: near
extern TXT_MSG_GRAFTABL_PORTUGUESE_LOADED_ALREADY: near
extern TXT_MSG_GRAFTABL_NORDIC_LOADED_ALREADY: near
extern TXT_MSG_GRAFTABL_NO_CP_LOADED: near
extern TXT_MSG_GRAFTABL_UNKNOWN_LOADED_ALREADY: near
extern TXT_MSG_GRAFTABL_HEBROW_LOADED: near
extern TXT_MSG_QMARK_GRAFTABL: near
extern TXT_MSG_GRAFTABL_MULTI_LOADED_ALREADY: near
extern TXT_MSG_GRAFTABL_MULTI_LOADED: near
extern TXT_MSG_GRAFTABL_HEBROW_LOADED_ALREADY: near

extern printmsg: near

; ============================================================================
; RESIDENT PORTION OF GRAFTABL (entry is replaced)
; ============================================================================

; Start by jumping over the resident part.
; The entry point doubles as the first 3 bytes of space for the font.
; The 2 bytes following the font are used to store the codepage (used by
; GRAFTABL /STA).

entry:    jmp       trans
          db        1021 dup (00h)
lcp:
          dw        0000h

; Old INT2F vector, because we need to chain into it.
; (The default vector, btw, is "Reboot")

old2F:
          dd        0FFFF0000h

; New INT2F handler.
; Supports AX=$B000 or $B001.  See RBIL for details.

new2F:    cmp       ah, 0B0h            ; is it ours?
          je        new2F2
new2F1:       jmp dword ptr [cs:old2F]
new2F2:       or        al, al              ; 0 - are we installed?
          jnz       new2F3
          mov       al, 0FFh            ; yes
          iret
new2F3:       cmp       al, 001h            ; 1 - where are we?
          jne       new2F1
          mov       al, 0FFh
          mov       word ptr ds:[bx], entry
          mov       ds:[bx+2], cs
          iret

; ============================================================================
; TRANSIENT PORTION OF GRAFTABL
; ============================================================================

; ============================================================================
; Returns: 0 = Installed successfully
;          1 = Codepage changed
;          2 = No codepage loaded (e.g., by /STA)
;          3 = Syntax error
;          4 = Incorrect DOS version,
;              will not occur on our code.
; ============================================================================

; Beginning of transient portion.
; Make sure the poor sap isn't using MS-DOS 1.  If he is, die screaming.

trans:    mov       ah, 030h
          int       021h
          xchg      ah, al
          cmp       ax, 00200h
          jae       okdos
          lea	si, TXT_MSG_INCORRECT_DOSVERSION
          call	printmsg
          int       020h                ; DOS 1 EXIT

; Command-line parser.
;
; The command line is stored as a PASCAL string, in the upper half of the Zero
; Page, terminated by a carriage return.  Initial spaces are included.

okdos:    mov       si, 00081h          ; Start of command line
okdos1:       call      killspc
          mov       ah, [si]
          cmp       ah, '/'             ; Switch?
          je        okdos5                  ; Yes, skip forward to process it.
okdos2:       mov       ah, [si]            ; Read digits.
          cmp       ah, 00Dh            ; CR - end of line
          je        okdos14
          cmp       ah, '0'             ; If not a digit, die screaming
          jb        okdos3
          cmp       ah, '9'
          ja        okdos3
          and       ah, 00Fh            ; Mask off the ASCII
          mov       bl, ah              ; Multiply existing value by 10 and
          xor       bh, bh              ;   add our digit to it.
          mov       ax, 0000Ah
          mul       word ptr [codepage]
          add       ax, bx
          mov       word ptr [codepage], ax
          inc       si                  ; Next char
          jmp short okdos2

okdos3:		lea	si, TXT_MSG_BAD_PARM1	;mov       dx, esyn            ; Syntax error, die screaming
		call	printmsg
		jmp	okdos41
okdos4:   call      wrstr
okdos41:  mov       ax, 04C03h
          int       021h                ; EXIT CODE 3
okdos5:       inc       si                  ; Start reading switch.
          cmp       byte ptr [si], '?'      ; /? - show command-line help
          jne       okdos6
          ;mov       dx, ehelp
	  lea       si, TXT_MSG_QMARK_GRAFTABL
	  call	printmsg
          jmp       okdos41                  ; Treat it as an error condition
okdos6:       mov       di, mstatus         ; The switch we need to match.
          mov       bx, si              ; Hold onto the current pointer.
okdos7:       mov       ah, [si]            ; Next char from each string.
          call      smash
          mov       al, [di]
          or        al, al              ; End of string?
          je        okdos11                 ; Yes, so do status.
          cmp       ah, al              ; Char match?
          jne       okdos8                  ; No, so die screaming.
          inc       si                  ; Move up and keep checking.
          inc       di
          jmp short okdos7
okdos8:       mov       dx, eswitch         ; "Invalid switch"
          call      wrstr
          mov       si, bx
okdos9:       mov       ah, [si]            ; Next char of switch
          call      smash
          cmp       ah, ' '             ; Check for delimiters
          je        okdos10                 ;   (space, tab, CR)
          cmp       ah, 009h
          je        okdos10
          cmp       ah, 00Dh
          je        okdos10
          mov       dl, ah              ; Output the character
          mov       ah, 002h
          int       021h
          inc       si                  ; Keep going, until done
          cmp       si, 00100h
          jb        okdos9
okdos10:      mov       dx, ecrlf           ; End with a newline.
          jmp       okdos4

; /STATUS handler.
;
; If GRAFTABL is not installed, die screaming.
; If it is, get the data pointer from it.  (This is actually the same as the
; INT1F vector on known versions.)  On known versions of GRAFTABL, including
; ours, the actual codepage number is stored immediately after the font data
; (i.e., at pointer+$0400 bytes).

okdos11:      mov       ax, 0B000h          ; Check for a running instance.
          int       02Fh
          cmp       al, 0FFh            ; Found it?
          je        okdos12                 ; Yes, jump forward.
          mov       dx, eis             ; Write "GRAFTABL is NOT installed"
          call      wrstr
          mov       dx, enot
          call      wrstr
          jmp short okdos13                 ; Die
okdos12:      mov       bx, whence          ; Get location of GRAFTABL data,
          mov       ax, 0B001h          ;   usually same as the 1F vector
          int       02Fh
          mov       dx, eactive
          call      wrstr
          mov       di, [whence]
          mov       ds, word ptr [whence+2]
          mov       bx, 00400h
          mov       ax, ds:[bx+di]
          push      cs                  ; Restore DS
          pop       ds
          call      wrnum               ; Write the codepage in decimal form.
          mov       dx, ecrlf
          call      wrstr
okdos13:      mov       ax, 04C02h
          int       021h                ; EXIT CODE 2

; Codepage mover/resident installer.
; (This serves both purposes, depending on which is needed.)

okdos14:      cmp       word ptr [codepage], 0  ; Default to 437 if no CP specified
          jne       okdos15
          mov       word ptr [codepage], 437
okdos15:      mov       si, cptab           ; Check our table to see if we have a
          mov       ax, [codepage]      ;   matching font in the binary.
okdos16:      cmp       word ptr [si], 0        ; End of table?
          je        okdos17                 ; Yes, die screaming.
          cmp       ax, [si]            ; A match?
          je        okdos18                 ; Yes, so use it.
          add       si, 4               ; Next entry
          jmp short okdos16
okdos17:	lea	si, TXT_MSG_GRAFTABL_NO_CP_LOADED	;//      mov       dx, ecp             ; "Invalid codepage"
		call	printmsg
          jmp       okdos41
okdos18:      add       si, 2               ; Get address of font
          mov       ax, [si]
          mov       word ptr [cpptr], ax         ; Save it.
          mov       ax, 0B000h          ; Search for existing GRAFTABL
          int       02Fh
          cmp       al, 0FFh            ; Found it.
          je        okdos21
          or        al, al              ; AL=00?
          jz        okdos19                 ; Yes, so safe to install.
          mov       dx, enope           ; Not safe to install, die screaming
          call      wrstr
          mov       ax, 04C02h
          int       021h                ; EXIT CODE 2
okdos19:      mov       word ptr [whence], entry
          mov       word ptr [whence+2], cs
          call      movcp               ; Install codepage
          mov       ax, 0352Fh          ; GETVECT
          int       021h
          mov       word ptr [old2F], bx
          mov       word ptr [old2F+2], es
          mov       ax, 0252Fh          ; Hook INT2F
          mov       dx, new2F
          int       021h
          mov       ax, 0251Fh          ; Hook INT1F
          mov       dx, entry           ; Remember, this doubles as the
          int       021h                ;   address of the font!
          mov       dx, eis             ; "GRAFTABL installed"
          call      wrstr
          mov       dx, einstall
          call      wrstr
          mov       dx, eactive         ; Display new codepage.
          call      wrstr
          mov       ax, [codepage]
          call      wrnum
          mov       dx, ecrlf
          call      wrstr
          mov       ax, word ptr [002Ch]        ; Free up the environment for a little
	  mov       es, ax
          mov       ah, 049h            ;   memory boost
          int       021h
          mov       dx, trans           ; Allow everything preceding the
          test      dx, 0000Fh          ;   transient portion of GRAFTABL to
          jz        okdos20                 ;   remain resident. (Rounded up to
          add       dx, 010h            ;   the next paragraph, because MS-DOS
okdos20:      mov       cl, 4               ;   wants the size in paragraphs.)
          shr       dx, cl
          mov       ax, 03100h
          int       021h                ; TSR EXIT CODE 0

; We found another GRAFTABL.
;
; Copy our data to the existing instance, instead of to our own, then return 1
; (existing codepage table updated).

okdos21:      mov       ax, 0B001h          ; So where is it?
          mov       bx, whence          ; ES:BX gets this.
          int       02Fh
          call      movcp
          ;mov       dx, eupdated        ; Display old codepage.
          ;call      wrstr
          ;mov       ax, [oldcp]
          ;call      wrnum
          ;mov       dx, ecrlf
          ;call      wrstr
          mov       dx, eactive         ; Display new codepage.
          call      wrstr
          mov       ax, [codepage]
          call      wrnum
          mov       dx, ecrlf
          call      wrstr
          mov       ax, 04C01h
          int       021h                ; EXIT CODE 1

; ============================================================================
; COMMON FUNCTIONS
; ============================================================================

; Copy the codepage to the desired location, be it in our memory image, or
; that of another implementation of GRAFTABL.
;
; Input: [codepage]=number of requested codepage.
;        [cpptr]=NEAR pointer to source codepage table.
;        [whence]=FAR pointer to target codepage table.
;
; Output: If applicable, returns the previous codepage number in [oldcp].

movcp:    mov       ax, [codepage]      ; Copy codepage after charset buffer.
          mov       di, [whence]
          mov       ds, word ptr [whence+2]
          mov       bx, 00400h
          mov       cx, ds:[bx+di]
          mov       word ptr cs:[oldcp], cx
          mov       ds:[bx+di], ax
          mov       si, [cpptr]         ; Repurpose the offset and copy the
movcp1:       mov       ah, cs:[si]         ;   actual data to the buffer.
          mov       ds:[di], ah
          inc       si
          inc       di
          dec       bx
          jnz       movcp1
          push      cs                  ; Reset DS.
          pop       ds
          ret                           ; We're outtie.

; Kill whitespace (used by the command parser).
;
; Input: SI=pointer to character in the command line currently being scanned.

killspc:  cmp       byte ptr [si], ' '      ; Keep pushing SI as long as it points
          je        killspc1                  ; to whitespace (space or tab), and is
          cmp       byte ptr [si], 009h     ; not out of the command line area.
          jne       killspc2
killspc1:       inc       si
          cmp       si, 00100h
          jb        killspc
killspc2:       ret

; Smash the case of AH.  Used mainly in the switch parser.
;
; Input: AH=letter to check

smash:    cmp       ah, 'a'             ; Smash lowercase to uppercase.
          jb        smash1
          cmp       ah, 'z'
          ja        smash1
          and       ah, 05Fh
smash1:       ret

; Write number in decimal format.
;
; The "wrstrc" function to output a C string is only used by wrnum, but as
; that function does need it, it is here included.
;
; Input: AX=number to output.

wrnum:    mov       byte ptr [numbuf+6], 0  ; Recycle the end of linbuf2.
          mov       di, numbuf+5        ; (Only does an unsigned word.
wrnum1:       xor       dx, dx              ;  Output will be a C string.)
          mov       bx, 10              ; DECIMAL
          div       bx                  ; AX=(DX:AX)/BX; DX=(DX:AX)%BX
          add       dl, '0'             ; Convert remainder to ASCII
          mov       [di], dl            ; Write it into buffer
          dec       di                  ; Step down
          or        ax, ax              ; Anything left?
          jnz       wrnum1                  ; Yes, so keep going.
          mov       dx, di
          inc       dx                  ; FALL INTO
wrstrc:   push      di
          mov       di, dx
wrstrc1:       mov       ah, 002h            ; PUTCHAR
          mov       dl, [di]
          or        dl, dl              ; Null terminator?
          jz        wrstrc2                  ; Yes, restore di and exit
          int       021h
          inc       di
          jmp short wrstrc1
wrstrc2:       pop       di
          ret

; Write string through DOS function 9; a simple space optimization since it is
; used so frequently.
;
; Input: DX=string, terminated by $

wrstr:    mov       ah, 009h            ; PUTSTR
          int       021h
          ret

; ============================================================================
; BSS
; ============================================================================

; Usually I place BSS at the end of the image and implement it via equates,
; but it's only 16 bytes, so it won't make that much of a difference.
;
; Besides, placing BSS after the codepage data seems wrong, somehow.

codepage: 
          dw        00000h
cpptr:    
          dw        00000h
oldcp:    
          dw        00000h
whence:   
          dd        000000000h
numbuf:   
          db        "00000", 0

; ============================================================================
; MESSAGES/TEXT
; ============================================================================

; Errors.
;
; Note that "Invalid switch" does NOT contain a newline.
; Any arbitrary newline plus terminator is adequate as a place to put "ecrlf".

eswitch:  
          db        "Invalid switch - /$"
ecrlf:    
          db        13, 10, "$"

; Informational messages and message fragments.
;
; Note that "eold" is not accessed directly, but only via fallthrough from
; "eupdated".

enope:
          db        "Not installing GRAFTABL.", 13, 10, "$"
eis:
          db        "GRAFTABL is $"
enot:
          db        "NOT "                        ; FALL INTO
einstall:
          db        "installed.", 13, 10, "$"
eactive:
          db        "Active code page is: $"

; The significant portion of the /STATUS switch.

mstatus:
          db        "STA", 0

; ============================================================================
; GRAFTABL CODEPAGE DATA
; ============================================================================

; Each codepage is stored as follows:
;
;   * cptab contains a list of valid codepages.
;     Each is stored "dw cpnumber, cppointer".  The last one should have a
;     codepage of 0.
;   * Each pointer points to a 1K buffer containing the upper half ($80-FF) of
;     the appropriate character set.
;
; We support the MS-DOS 5/6 stock codepages:
;
;   * 437 - United States
;   * 850 - Western Europe/Latin 1
;   * 852 - Central Europe/Latin 2
;   * 860 - Portuguese
;   * 863 - Canadian French
;   * 865 - Nordic
;   * 866 - Cyrilic
;
; Each character is depicted by 8 bytes of data, one per scanline.

cptab:
          dw        437, CP437
          dw        850, CP850
          dw        852, CP852
          dw        860, CP860
          dw        863, CP863
          dw        865, CP865
          dw        866, CP866
          dw        0,   00000h

CP437:
          db        07Ch, 0C6h, 0C0h, 0C0h, 0C6h, 07Ch, 00Ch, 078h
          db        0CCh, 000h, 0CCh, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        00Ch, 018h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        07Ch, 082h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        0C6h, 000h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        030h, 018h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        030h, 030h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        000h, 000h, 07Eh, 0C0h, 0C0h, 07Eh, 00Ch, 038h
          db        07Ch, 082h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        0C6h, 000h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        030h, 018h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        066h, 000h, 038h, 018h, 018h, 018h, 03Ch, 000h
          db        07Ch, 082h, 038h, 018h, 018h, 018h, 03Ch, 000h
          db        030h, 018h, 000h, 038h, 018h, 018h, 03Ch, 000h
          db        0C6h, 038h, 06Ch, 0C6h, 0FEh, 0C6h, 0C6h, 000h
          db        038h, 06Ch, 07Ch, 0C6h, 0FEh, 0C6h, 0C6h, 000h
          db        018h, 030h, 0FEh, 0C0h, 0F8h, 0C0h, 0FEh, 000h
          db        000h, 000h, 07Eh, 018h, 07Eh, 0D8h, 07Eh, 000h
          db        03Eh, 06Ch, 0CCh, 0FEh, 0CCh, 0CCh, 0CEh, 000h
          db        07Ch, 082h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        0C6h, 000h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        030h, 018h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        078h, 084h, 000h, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        060h, 030h, 0CCh, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        0C6h, 000h, 0C6h, 0C6h, 0C6h, 07Eh, 006h, 0FCh
          db        0C6h, 038h, 06Ch, 0C6h, 0C6h, 06Ch, 038h, 000h
          db        0C6h, 000h, 0C6h, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        018h, 018h, 07Eh, 0C0h, 0C0h, 07Eh, 018h, 018h
          db        038h, 06Ch, 064h, 0F0h, 060h, 066h, 0FCh, 000h
          db        066h, 066h, 03Ch, 07Eh, 018h, 07Eh, 018h, 018h
          db        0F8h, 0CCh, 0CCh, 0FAh, 0C6h, 0CFh, 0C6h, 0C7h
          db        00Eh, 01Bh, 018h, 03Ch, 018h, 0D8h, 070h, 000h
          db        018h, 030h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        00Ch, 018h, 000h, 038h, 018h, 018h, 03Ch, 000h
          db        00Ch, 018h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        018h, 030h, 0CCh, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        076h, 0DCh, 000h, 0DCh, 066h, 066h, 066h, 000h
          db        076h, 0DCh, 000h, 0E6h, 0F6h, 0DEh, 0CEh, 000h
          db        03Ch, 06Ch, 06Ch, 03Eh, 000h, 07Eh, 000h, 000h
          db        038h, 06Ch, 06Ch, 038h, 000h, 07Ch, 000h, 000h
          db        018h, 000h, 018h, 018h, 030h, 063h, 03Eh, 000h
          db        000h, 000h, 000h, 0FEh, 0C0h, 0C0h, 000h, 000h
          db        000h, 000h, 000h, 0FEh, 006h, 006h, 000h, 000h
          db        063h, 0E6h, 06Ch, 07Eh, 033h, 066h, 0CCh, 00Fh
          db        063h, 0E6h, 06Ch, 07Ah, 036h, 06Ah, 0DFh, 006h
          db        018h, 000h, 018h, 018h, 03Ch, 03Ch, 018h, 000h
          db        000h, 033h, 066h, 0CCh, 066h, 033h, 000h, 000h
          db        000h, 0CCh, 066h, 033h, 066h, 0CCh, 000h, 000h
          db        022h, 088h, 022h, 088h, 022h, 088h, 022h, 088h
          db        055h, 0AAh, 055h, 0AAh, 055h, 0AAh, 055h, 0AAh
          db        077h, 0DDh, 077h, 0DDh, 077h, 0DDh, 077h, 0DDh
          db        018h, 018h, 018h, 018h, 018h, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 0F8h, 018h, 018h, 018h
          db        018h, 018h, 0F8h, 018h, 0F8h, 018h, 018h, 018h
          db        036h, 036h, 036h, 036h, 0F6h, 036h, 036h, 036h
          db        000h, 000h, 000h, 000h, 0FEh, 036h, 036h, 036h
          db        000h, 000h, 0F8h, 018h, 0F8h, 018h, 018h, 018h
          db        036h, 036h, 0F6h, 006h, 0F6h, 036h, 036h, 036h
          db        036h, 036h, 036h, 036h, 036h, 036h, 036h, 036h
          db        000h, 000h, 0FEh, 006h, 0F6h, 036h, 036h, 036h
          db        036h, 036h, 0F6h, 006h, 0FEh, 000h, 000h, 000h
          db        036h, 036h, 036h, 036h, 0FEh, 000h, 000h, 000h
          db        018h, 018h, 0F8h, 018h, 0F8h, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 0F8h, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 01Fh, 000h, 000h, 000h
          db        018h, 018h, 018h, 018h, 0FFh, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 0FFh, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 01Fh, 018h, 018h, 018h
          db        000h, 000h, 000h, 000h, 0FFh, 000h, 000h, 000h
          db        018h, 018h, 018h, 018h, 0FFh, 018h, 018h, 018h
          db        018h, 018h, 01Fh, 018h, 01Fh, 018h, 018h, 018h
          db        036h, 036h, 036h, 036h, 037h, 036h, 036h, 036h
          db        036h, 036h, 037h, 030h, 03Fh, 000h, 000h, 000h
          db        000h, 000h, 03Fh, 030h, 037h, 036h, 036h, 036h
          db        036h, 036h, 0F7h, 000h, 0FFh, 000h, 000h, 000h
          db        000h, 000h, 0FFh, 000h, 0F7h, 036h, 036h, 036h
          db        036h, 036h, 037h, 030h, 037h, 036h, 036h, 036h
          db        000h, 000h, 0FFh, 000h, 0FFh, 000h, 000h, 000h
          db        036h, 036h, 0F7h, 000h, 0F7h, 036h, 036h, 036h
          db        018h, 018h, 0FFh, 000h, 0FFh, 000h, 000h, 000h
          db        036h, 036h, 036h, 036h, 0FFh, 000h, 000h, 000h
          db        000h, 000h, 0FFh, 000h, 0FFh, 018h, 018h, 018h
          db        000h, 000h, 000h, 000h, 0FFh, 036h, 036h, 036h
          db        036h, 036h, 036h, 036h, 03Fh, 000h, 000h, 000h
          db        018h, 018h, 01Fh, 018h, 01Fh, 000h, 000h, 000h
          db        000h, 000h, 01Fh, 018h, 01Fh, 018h, 018h, 018h
          db        000h, 000h, 000h, 000h, 03Fh, 036h, 036h, 036h
          db        036h, 036h, 036h, 036h, 0FFh, 036h, 036h, 036h
          db        018h, 018h, 0FFh, 018h, 0FFh, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 0F8h, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 01Fh, 018h, 018h, 018h
          db        0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh
          db        000h, 000h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
          db        0F0h, 0F0h, 0F0h, 0F0h, 0F0h, 0F0h, 0F0h, 0F0h
          db        00Fh, 00Fh, 00Fh, 00Fh, 00Fh, 00Fh, 00Fh, 00Fh
          db        0FFh, 0FFh, 0FFh, 0FFh, 000h, 000h, 000h, 000h
          db        000h, 000h, 076h, 0DCh, 0C8h, 0DCh, 076h, 000h
          db        078h, 0CCh, 0CCh, 0D8h, 0CCh, 0C6h, 0CCh, 000h
          db        0FEh, 0C6h, 0C0h, 0C0h, 0C0h, 0C0h, 0C0h, 000h
          db        000h, 000h, 0FEh, 06Ch, 06Ch, 06Ch, 06Ch, 000h
          db        0FEh, 0C6h, 060h, 030h, 060h, 0C6h, 0FEh, 000h
          db        000h, 000h, 07Eh, 0D8h, 0D8h, 0D8h, 070h, 000h
          db        000h, 000h, 066h, 066h, 066h, 066h, 07Ch, 0C0h
          db        000h, 076h, 0DCh, 018h, 018h, 018h, 018h, 000h
          db        07Eh, 018h, 03Ch, 066h, 066h, 03Ch, 018h, 07Eh
          db        038h, 06Ch, 0C6h, 0FEh, 0C6h, 06Ch, 038h, 000h
          db        038h, 06Ch, 0C6h, 0C6h, 06Ch, 06Ch, 0EEh, 000h
          db        00Eh, 018h, 00Ch, 03Eh, 066h, 066h, 03Ch, 000h
          db        000h, 000h, 07Eh, 0DBh, 0DBh, 07Eh, 000h, 000h
          db        006h, 00Ch, 07Eh, 0DBh, 0DBh, 07Eh, 060h, 0C0h
          db        01Eh, 030h, 060h, 07Eh, 060h, 030h, 01Eh, 000h
          db        000h, 07Ch, 0C6h, 0C6h, 0C6h, 0C6h, 0C6h, 000h
          db        000h, 0FEh, 000h, 0FEh, 000h, 0FEh, 000h, 000h
          db        018h, 018h, 07Eh, 018h, 018h, 000h, 07Eh, 000h
          db        030h, 018h, 00Ch, 018h, 030h, 000h, 07Eh, 000h
          db        00Ch, 018h, 030h, 018h, 00Ch, 000h, 07Eh, 000h
          db        00Eh, 01Bh, 01Bh, 018h, 018h, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 018h, 0D8h, 0D8h, 070h
          db        000h, 018h, 000h, 07Eh, 000h, 018h, 000h, 000h
          db        000h, 076h, 0DCh, 000h, 076h, 0DCh, 000h, 000h
          db        038h, 06Ch, 06Ch, 038h, 000h, 000h, 000h, 000h
          db        000h, 000h, 000h, 018h, 018h, 000h, 000h, 000h
          db        000h, 000h, 000h, 018h, 000h, 000h, 000h, 000h
          db        00Fh, 00Ch, 00Ch, 00Ch, 0ECh, 06Ch, 03Ch, 01Ch
          db        06Ch, 036h, 036h, 036h, 036h, 000h, 000h, 000h
          db        078h, 00Ch, 018h, 030h, 07Ch, 000h, 000h, 000h
          db        000h, 000h, 03Ch, 03Ch, 03Ch, 03Ch, 000h, 000h
          db        000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h

CP850:
          db        07Ch, 0C6h, 0C0h, 0C0h, 0C6h, 07Ch, 00Ch, 078h
          db        0CCh, 000h, 0CCh, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        00Ch, 018h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        07Ch, 082h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        0C6h, 000h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        030h, 018h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        030h, 030h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        000h, 000h, 07Eh, 0C0h, 0C0h, 07Eh, 00Ch, 038h
          db        07Ch, 082h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        0C6h, 000h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        030h, 018h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        066h, 000h, 038h, 018h, 018h, 018h, 03Ch, 000h
          db        07Ch, 082h, 038h, 018h, 018h, 018h, 03Ch, 000h
          db        030h, 018h, 000h, 038h, 018h, 018h, 03Ch, 000h
          db        0C6h, 038h, 06Ch, 0C6h, 0FEh, 0C6h, 0C6h, 000h
          db        038h, 06Ch, 07Ch, 0C6h, 0FEh, 0C6h, 0C6h, 000h
          db        018h, 030h, 0FEh, 0C0h, 0F8h, 0C0h, 0FEh, 000h
          db        000h, 000h, 07Eh, 012h, 0FEh, 090h, 0FEh, 000h
          db        03Eh, 06Ch, 0CCh, 0FEh, 0CCh, 0CCh, 0CEh, 000h
          db        07Ch, 082h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        0C6h, 000h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        030h, 018h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        078h, 084h, 000h, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        060h, 030h, 0CCh, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        0C6h, 000h, 0C6h, 0C6h, 0C6h, 07Eh, 006h, 0FCh
          db        0C6h, 038h, 06Ch, 0C6h, 0C6h, 06Ch, 038h, 000h
          db        0C6h, 000h, 0C6h, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        000h, 002h, 07Ch, 0CEh, 0D6h, 0E6h, 07Ch, 080h
          db        038h, 06Ch, 064h, 0F0h, 060h, 066h, 0FCh, 000h
          db        03Ah, 06Ch, 0CEh, 0D6h, 0E6h, 06Ch, 0B8h, 000h
          db        000h, 0C6h, 06Ch, 038h, 06Ch, 0C6h, 000h, 000h
          db        00Eh, 01Bh, 018h, 03Ch, 018h, 0D8h, 070h, 000h
          db        018h, 030h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        00Ch, 018h, 000h, 038h, 018h, 018h, 03Ch, 000h
          db        00Ch, 018h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        018h, 030h, 0CCh, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        076h, 0DCh, 000h, 0DCh, 066h, 066h, 066h, 000h
          db        076h, 0DCh, 000h, 0E6h, 0F6h, 0DEh, 0CEh, 000h
          db        03Ch, 06Ch, 06Ch, 03Eh, 000h, 07Eh, 000h, 000h
          db        038h, 06Ch, 06Ch, 038h, 000h, 07Ch, 000h, 000h
          db        018h, 000h, 018h, 018h, 030h, 063h, 03Eh, 000h
          db        07Eh, 081h, 0B9h, 0A5h, 0B9h, 0A5h, 081h, 07Eh
          db        000h, 000h, 000h, 0FEh, 006h, 006h, 000h, 000h
          db        063h, 0E6h, 06Ch, 07Eh, 033h, 066h, 0CCh, 00Fh
          db        063h, 0E6h, 06Ch, 07Ah, 036h, 06Ah, 0DFh, 006h
          db        018h, 000h, 018h, 018h, 03Ch, 03Ch, 018h, 000h
          db        000h, 033h, 066h, 0CCh, 066h, 033h, 000h, 000h
          db        000h, 0CCh, 066h, 033h, 066h, 0CCh, 000h, 000h
          db        022h, 088h, 022h, 088h, 022h, 088h, 022h, 088h
          db        055h, 0AAh, 055h, 0AAh, 055h, 0AAh, 055h, 0AAh
          db        077h, 0DDh, 077h, 0DDh, 077h, 0DDh, 077h, 0DDh
          db        018h, 018h, 018h, 018h, 018h, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 0F8h, 018h, 018h, 018h
          db        030h, 060h, 038h, 06Ch, 0C6h, 0FEh, 0C6h, 000h
          db        07Ch, 082h, 038h, 06Ch, 0C6h, 0FEh, 0C6h, 000h
          db        018h, 00Ch, 038h, 06Ch, 0C6h, 0FEh, 0C6h, 000h
          db        07Eh, 081h, 09Dh, 0A1h, 0A1h, 09Dh, 081h, 07Eh
          db        036h, 036h, 0F6h, 006h, 0F6h, 036h, 036h, 036h
          db        036h, 036h, 036h, 036h, 036h, 036h, 036h, 036h
          db        000h, 000h, 0FEh, 006h, 0F6h, 036h, 036h, 036h
          db        036h, 036h, 0F6h, 006h, 0FEh, 000h, 000h, 000h
          db        018h, 018h, 07Eh, 0C0h, 0C0h, 07Eh, 018h, 018h
          db        066h, 066h, 03Ch, 07Eh, 018h, 07Eh, 018h, 018h
          db        000h, 000h, 000h, 000h, 0F8h, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 01Fh, 000h, 000h, 000h
          db        018h, 018h, 018h, 018h, 0FFh, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 0FFh, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 01Fh, 018h, 018h, 018h
          db        000h, 000h, 000h, 000h, 0FFh, 000h, 000h, 000h
          db        018h, 018h, 018h, 018h, 0FFh, 018h, 018h, 018h
          db        076h, 0DCh, 07Ch, 006h, 07Eh, 0C6h, 07Eh, 000h
          db        076h, 0DCh, 038h, 06Ch, 0C6h, 0FEh, 0C6h, 000h
          db        036h, 036h, 037h, 030h, 03Fh, 000h, 000h, 000h
          db        000h, 000h, 03Fh, 030h, 037h, 036h, 036h, 036h
          db        036h, 036h, 0F7h, 000h, 0FFh, 000h, 000h, 000h
          db        000h, 000h, 0FFh, 000h, 0F7h, 036h, 036h, 036h
          db        036h, 036h, 037h, 030h, 037h, 036h, 036h, 036h
          db        000h, 000h, 0FFh, 000h, 0FFh, 000h, 000h, 000h
          db        036h, 036h, 0F7h, 000h, 0F7h, 036h, 036h, 036h
          db        000h, 0C6h, 07Ch, 0C6h, 0C6h, 07Ch, 0C6h, 000h
          db        030h, 07Eh, 00Ch, 07Ch, 0CCh, 0CCh, 078h, 000h
          db        0F8h, 06Ch, 066h, 0F6h, 066h, 06Ch, 0F8h, 000h
          db        07Ch, 082h, 0FEh, 0C0h, 0FCh, 0C0h, 0FEh, 000h
          db        0C6h, 000h, 0FEh, 0C0h, 0FCh, 0C0h, 0FEh, 000h
          db        030h, 018h, 0FEh, 0C0h, 0FCh, 0C0h, 0FEh, 000h
          db        000h, 000h, 038h, 018h, 018h, 018h, 03Ch, 000h
          db        00Ch, 018h, 03Ch, 018h, 018h, 018h, 03Ch, 000h
          db        03Ch, 042h, 03Ch, 018h, 018h, 018h, 03Ch, 000h
          db        066h, 000h, 03Ch, 018h, 018h, 018h, 03Ch, 000h
          db        018h, 018h, 018h, 018h, 0F8h, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 01Fh, 018h, 018h, 018h
          db        0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh
          db        000h, 000h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
          db        018h, 018h, 018h, 000h, 000h, 018h, 018h, 018h
          db        030h, 018h, 03Ch, 018h, 018h, 018h, 03Ch, 000h
          db        0FFh, 0FFh, 0FFh, 0FFh, 000h, 000h, 000h, 000h
          db        030h, 060h, 038h, 06Ch, 0C6h, 06Ch, 038h, 000h
          db        078h, 0CCh, 0CCh, 0D8h, 0CCh, 0C6h, 0CCh, 000h
          db        07Ch, 082h, 038h, 06Ch, 0C6h, 06Ch, 038h, 000h
          db        00Ch, 006h, 038h, 06Ch, 0C6h, 06Ch, 038h, 000h
          db        076h, 0DCh, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        076h, 0DCh, 038h, 06Ch, 0C6h, 06Ch, 038h, 000h
          db        000h, 000h, 066h, 066h, 066h, 066h, 07Ch, 0C0h
          db        0E0h, 060h, 07Ch, 066h, 066h, 07Ch, 060h, 0F0h
          db        0F0h, 060h, 07Ch, 066h, 07Ch, 060h, 0F0h, 000h
          db        018h, 030h, 0C6h, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        07Ch, 082h, 000h, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        060h, 030h, 0C6h, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        018h, 030h, 0C6h, 0C6h, 0C6h, 07Eh, 006h, 0FCh
          db        00Ch, 018h, 066h, 066h, 03Ch, 018h, 03Ch, 000h
          db        0FFh, 000h, 000h, 000h, 000h, 000h, 000h, 000h
          db        00Ch, 018h, 030h, 000h, 000h, 000h, 000h, 000h
          db        000h, 000h, 000h, 07Eh, 000h, 000h, 000h, 000h
          db        018h, 018h, 07Eh, 018h, 018h, 000h, 07Eh, 000h
          db        000h, 000h, 000h, 000h, 000h, 0FFh, 000h, 0FFh
          db        0E1h, 032h, 0E4h, 03Ah, 0F6h, 02Ah, 05Fh, 086h
          db        07Fh, 0DBh, 0DBh, 07Bh, 01Bh, 01Bh, 01Bh, 000h
          db        03Eh, 061h, 03Ch, 066h, 066h, 03Ch, 086h, 07Ch
          db        000h, 018h, 000h, 07Eh, 000h, 018h, 000h, 000h
          db        000h, 000h, 000h, 000h, 000h, 018h, 00Ch, 038h
          db        038h, 06Ch, 06Ch, 038h, 000h, 000h, 000h, 000h
          db        000h, 0C6h, 000h, 000h, 000h, 000h, 000h, 000h
          db        000h, 000h, 000h, 018h, 000h, 000h, 000h, 000h
          db        018h, 038h, 018h, 018h, 03Ch, 000h, 000h, 000h
          db        078h, 00Ch, 038h, 00Ch, 078h, 000h, 000h, 000h
          db        078h, 00Ch, 018h, 030h, 07Ch, 000h, 000h, 000h
          db        000h, 000h, 03Ch, 03Ch, 03Ch, 03Ch, 000h, 000h
          db        000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h

CP852:
          db        03Ch, 066h, 0C0h, 0C0h, 066h, 03Ch, 00Ch, 038h
          db        0CCh, 000h, 0CCh, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        018h, 030h, 078h, 0CCh, 0FCh, 0C0h, 078h, 000h
          db        078h, 084h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        0CCh, 000h, 078h, 00Ch, 07Ch, 0CCh, 07Eh, 000h
          db        030h, 0CCh, 030h, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        018h, 030h, 078h, 0CCh, 0C0h, 0CCh, 078h, 000h
          db        000h, 000h, 078h, 0CCh, 0C0h, 0CCh, 078h, 018h
          db        030h, 036h, 03Ch, 038h, 030h, 070h, 0DCh, 000h
          db        0CCh, 000h, 078h, 0CCh, 0FCh, 0C0h, 078h, 000h
          db        066h, 0CCh, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        000h, 066h, 0CCh, 078h, 0CCh, 0CCh, 078h, 000h
          db        070h, 088h, 070h, 030h, 030h, 030h, 078h, 000h
          db        00Ch, 018h, 0FEh, 00Ch, 030h, 060h, 0FEh, 000h
          db        0C6h, 038h, 06Ch, 0C6h, 0FEh, 0C6h, 0C6h, 000h
          db        00Ch, 018h, 07Ch, 0C6h, 0C0h, 0C6h, 07Ch, 000h
          db        00Ch, 018h, 0FCh, 060h, 078h, 060h, 0FCh, 000h
          db        0CCh, 0D8h, 0C0h, 0C0h, 0C0h, 0C0h, 0FEh, 000h
          db        0CCh, 0D8h, 0C0h, 0C0h, 0C0h, 0C0h, 078h, 000h
          db        078h, 0CCh, 000h, 078h, 0CCh, 0CCh, 078h, 000h
          db        0CCh, 000h, 078h, 0CCh, 0CCh, 0CCh, 078h, 000h
          db        0F6h, 0DCh, 0C0h, 0C0h, 0C0h, 0C0h, 0FEh, 000h
          db        0F6h, 0DCh, 0C0h, 0C0h, 0C0h, 0C0h, 078h, 000h
          db        00Ch, 018h, 07Eh, 0C0h, 07Ch, 006h, 0FCh, 000h
          db        00Ch, 018h, 03Eh, 060h, 03Ch, 006h, 07Ch, 000h
          db        0C6h, 07Ch, 0C6h, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        0C6h, 000h, 0C6h, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        0CCh, 078h, 0FCh, 030h, 030h, 030h, 030h, 000h
          db        0CCh, 078h, 030h, 0FCh, 030h, 030h, 01Eh, 000h
          db        060h, 06Ch, 078h, 070h, 060h, 0E0h, 07Eh, 000h
          db        000h, 0C6h, 06Ch, 038h, 06Ch, 0C6h, 000h, 000h
          db        066h, 03Ch, 03Ch, 066h, 060h, 066h, 03Ch, 000h
          db        00Ch, 018h, 078h, 00Ch, 07Ch, 0CCh, 07Eh, 000h
          db        00Ch, 018h, 038h, 018h, 018h, 018h, 03Ch, 000h
          db        000h, 00Ch, 018h, 078h, 0CCh, 0CCh, 078h, 000h
          db        000h, 018h, 030h, 0CCh, 0CCh, 0CCh, 07Eh, 000h
          db        038h, 06Ch, 0C6h, 0FEh, 0C6h, 0D6h, 018h, 00Eh
          db        000h, 000h, 078h, 00Ch, 07Ch, 0CCh, 076h, 00Fh
          db        066h, 03Ch, 0FEh, 00Ch, 018h, 060h, 0FEh, 000h
          db        066h, 03Ch, 000h, 07Eh, 00Ch, 030h, 07Eh, 000h
          db        0FEh, 0C0h, 0C0h, 0F8h, 0C0h, 0C0h, 0FEh, 01Ch
          db        000h, 000h, 078h, 0CCh, 0FCh, 0C0h, 078h, 01Ch
          db        000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
          db        00Ch, 018h, 000h, 07Eh, 00Ch, 030h, 07Eh, 000h
          db        066h, 03Ch, 07Ch, 0C6h, 0C0h, 0C6h, 07Ch, 000h
          db        000h, 000h, 07Ch, 0C0h, 078h, 00Ch, 0F8h, 038h
          db        000h, 033h, 066h, 0CCh, 066h, 033h, 000h, 000h
          db        000h, 0CCh, 066h, 033h, 066h, 0CCh, 000h, 000h
          db        022h, 088h, 022h, 088h, 022h, 088h, 022h, 088h
          db        055h, 0AAh, 055h, 0AAh, 055h, 0AAh, 055h, 0AAh
          db        0DBh, 077h, 0DBh, 0EEh, 0DBh, 077h, 0DBh, 0EEh
          db        018h, 018h, 018h, 018h, 018h, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 0F8h, 018h, 018h, 018h
          db        00Ch, 018h, 07Ch, 0C6h, 0FEh, 0C6h, 0C6h, 000h
          db        07Ch, 082h, 07Ch, 0C6h, 0FEh, 0C6h, 0C6h, 000h
          db        0CCh, 078h, 0FEh, 0C0h, 0F8h, 0C0h, 0FEh, 000h
          db        078h, 0CCh, 060h, 030h, 018h, 0CCh, 078h, 030h
          db        036h, 036h, 0F6h, 006h, 0F6h, 036h, 036h, 036h
          db        036h, 036h, 036h, 036h, 036h, 036h, 036h, 036h
          db        000h, 000h, 0FEh, 006h, 0F6h, 036h, 036h, 036h
          db        036h, 036h, 0F6h, 006h, 0FEh, 000h, 000h, 000h
          db        018h, 0FEh, 0C6h, 00Ch, 030h, 0C6h, 0FEh, 000h
          db        000h, 018h, 000h, 07Ch, 018h, 030h, 07Ch, 000h
          db        000h, 000h, 000h, 000h, 0F8h, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 01Fh, 000h, 000h, 000h
          db        018h, 018h, 018h, 018h, 0FFh, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 0FFh, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 01Fh, 018h, 018h, 018h
          db        000h, 000h, 000h, 000h, 0FFh, 000h, 000h, 000h
          db        018h, 018h, 018h, 018h, 0FFh, 018h, 018h, 018h
          db        0C6h, 07Ch, 07Ch, 0C6h, 0FEh, 0C6h, 0C6h, 000h
          db        0CCh, 078h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        036h, 036h, 037h, 030h, 03Fh, 000h, 000h, 000h
          db        000h, 000h, 03Fh, 030h, 037h, 036h, 036h, 036h
          db        036h, 036h, 0F7h, 000h, 0FFh, 000h, 000h, 000h
          db        000h, 000h, 0FFh, 000h, 0F7h, 036h, 036h, 036h
          db        036h, 036h, 037h, 030h, 037h, 036h, 036h, 036h
          db        000h, 000h, 0FFh, 000h, 0FFh, 000h, 000h, 000h
          db        036h, 036h, 0F7h, 000h, 0F7h, 036h, 036h, 036h
          db        000h, 042h, 03Ch, 066h, 066h, 03Ch, 042h, 000h
          db        00Ch, 03Eh, 00Ch, 07Ch, 0CCh, 0CCh, 076h, 000h
          db        07Ch, 066h, 066h, 0F6h, 066h, 066h, 07Ch, 000h
          db        0CCh, 078h, 0FCh, 066h, 066h, 066h, 0FCh, 000h
          db        0CCh, 000h, 0FCh, 060h, 078h, 060h, 0FCh, 000h
          db        096h, 066h, 006h, 07Eh, 0C6h, 0C6h, 07Eh, 000h
          db        024h, 018h, 0E6h, 0F6h, 0DEh, 0CEh, 0C6h, 000h
          db        018h, 030h, 078h, 030h, 030h, 030h, 078h, 000h
          db        078h, 084h, 078h, 030h, 030h, 030h, 078h, 000h
          db        0CCh, 078h, 078h, 0CCh, 0FCh, 0C0h, 078h, 000h
          db        018h, 018h, 018h, 018h, 0F8h, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 01Fh, 018h, 018h, 018h
          db        0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh
          db        000h, 000h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
          db        07Eh, 018h, 018h, 018h, 018h, 018h, 020h, 038h
          db        010h, 028h, 0D6h, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        0FFh, 0FFh, 0FFh, 0FFh, 000h, 000h, 000h, 000h
          db        00Ch, 018h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        000h, 078h, 0CCh, 0F8h, 0CCh, 0F8h, 0C0h, 0C0h
          db        07Ch, 082h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        00Ch, 018h, 0E6h, 0F6h, 0DEh, 0CEh, 0C6h, 000h
          db        00Ch, 018h, 0DCh, 0E6h, 0C6h, 0C6h, 0C6h, 000h
          db        066h, 03Ch, 0DCh, 0E6h, 0C6h, 0C6h, 0C6h, 000h
          db        06Ch, 038h, 07Eh, 0E0h, 038h, 00Eh, 0FCh, 000h
          db        06Ch, 038h, 07Ch, 040h, 038h, 004h, 07Ch, 000h
          db        00Ch, 018h, 0FCh, 0C6h, 0FCh, 0D8h, 0CCh, 000h
          db        00Ch, 018h, 0C6h, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        018h, 030h, 0CEh, 0F0h, 0E0h, 0C0h, 0C0h, 000h
          db        066h, 0CCh, 0C6h, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        00Ch, 018h, 0C6h, 0C6h, 066h, 03Eh, 00Ch, 078h
          db        00Ch, 0DEh, 0C6h, 066h, 03Ch, 018h, 030h, 000h
          db        030h, 078h, 030h, 030h, 030h, 038h, 018h, 01Eh
          db        00Ch, 018h, 000h, 000h, 000h, 000h, 000h, 000h
          db        000h, 000h, 000h, 03Ch, 000h, 000h, 000h, 000h
          db        066h, 0CCh, 000h, 000h, 000h, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 000h, 000h, 010h, 01Ch
          db        0D8h, 070h, 000h, 000h, 000h, 000h, 000h, 000h
          db        0C6h, 07Ch, 000h, 000h, 000h, 000h, 000h, 000h
          db        03Ch, 066h, 038h, 06Ch, 06Ch, 038h, 0CCh, 078h
          db        018h, 018h, 000h, 07Eh, 000h, 018h, 018h, 000h
          db        000h, 000h, 000h, 000h, 000h, 000h, 004h, 01Ch
          db        038h, 06Ch, 06Ch, 038h, 000h, 000h, 000h, 000h
          db        066h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
          db        018h, 000h, 000h, 000h, 000h, 000h, 000h, 000h
          db        066h, 0CCh, 000h, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        0D8h, 070h, 0FCh, 0C6h, 0FCh, 0D8h, 0CCh, 000h
          db        0D8h, 070h, 0CEh, 0D8h, 0E0h, 0C0h, 0C0h, 000h
          db        000h, 000h, 03Ch, 03Ch, 03Ch, 03Ch, 000h, 000h
          db        000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h

CP860:
          db        07Ch, 0C6h, 0C0h, 0C0h, 0C6h, 07Ch, 00Ch, 078h
          db        0CCh, 000h, 0CCh, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        00Ch, 018h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        07Ch, 082h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        076h, 0DCh, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        030h, 018h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        030h, 060h, 038h, 06Ch, 0C6h, 0FEh, 0C6h, 000h
          db        000h, 000h, 07Eh, 0C0h, 0C0h, 07Eh, 00Ch, 038h
          db        07Ch, 082h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        07Ch, 082h, 0FEh, 0C0h, 0F8h, 0C0h, 0FEh, 000h
          db        030h, 018h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        00Ch, 018h, 03Ch, 018h, 018h, 018h, 03Ch, 000h
          db        07Ch, 082h, 038h, 06Ch, 0C6h, 06Ch, 038h, 000h
          db        030h, 018h, 000h, 038h, 018h, 018h, 03Ch, 000h
          db        076h, 0DCh, 038h, 06Ch, 0C6h, 0FEh, 0C6h, 000h
          db        07Ch, 082h, 038h, 06Ch, 0C6h, 0FEh, 0C6h, 000h
          db        018h, 030h, 0FEh, 0C0h, 0F8h, 0C0h, 0FEh, 000h
          db        060h, 030h, 038h, 06Ch, 0C6h, 0FEh, 0C6h, 000h
          db        030h, 018h, 0FEh, 0C0h, 0F8h, 0C0h, 0FEh, 000h
          db        07Ch, 082h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        076h, 0DCh, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        030h, 018h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        00Ch, 018h, 0C6h, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        060h, 030h, 0CCh, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        030h, 018h, 03Ch, 018h, 018h, 018h, 03Ch, 000h
          db        076h, 0DCh, 038h, 06Ch, 0C6h, 06Ch, 038h, 000h
          db        0C6h, 000h, 0C6h, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        018h, 018h, 07Eh, 0C0h, 0C0h, 07Eh, 018h, 018h
          db        038h, 06Ch, 064h, 0F0h, 060h, 066h, 0FCh, 000h
          db        030h, 018h, 0C6h, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        0F8h, 0CCh, 0CCh, 0FAh, 0C6h, 0CFh, 0C6h, 0C7h
          db        00Ch, 018h, 038h, 06Ch, 0C6h, 06Ch, 038h, 000h
          db        018h, 030h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        00Ch, 018h, 000h, 038h, 018h, 018h, 03Ch, 000h
          db        00Ch, 018h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        018h, 030h, 0CCh, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        076h, 0DCh, 000h, 0DCh, 066h, 066h, 066h, 000h
          db        076h, 0DCh, 000h, 0E6h, 0F6h, 0DEh, 0CEh, 000h
          db        03Ch, 06Ch, 06Ch, 03Eh, 000h, 07Eh, 000h, 000h
          db        038h, 06Ch, 06Ch, 038h, 000h, 07Ch, 000h, 000h
          db        018h, 000h, 018h, 018h, 030h, 063h, 03Eh, 000h
          db        030h, 018h, 038h, 06Ch, 0C6h, 06Ch, 038h, 000h
          db        000h, 000h, 000h, 0FEh, 006h, 006h, 000h, 000h
          db        063h, 0E6h, 06Ch, 07Eh, 033h, 066h, 0CCh, 00Fh
          db        063h, 0E6h, 06Ch, 07Ah, 036h, 06Ah, 0DFh, 006h
          db        018h, 000h, 018h, 018h, 03Ch, 03Ch, 018h, 000h
          db        000h, 033h, 066h, 0CCh, 066h, 033h, 000h, 000h
          db        000h, 0CCh, 066h, 033h, 066h, 0CCh, 000h, 000h
          db        022h, 088h, 022h, 088h, 022h, 088h, 022h, 088h
          db        055h, 0AAh, 055h, 0AAh, 055h, 0AAh, 055h, 0AAh
          db        077h, 0DDh, 077h, 0DDh, 077h, 0DDh, 077h, 0DDh
          db        018h, 018h, 018h, 018h, 018h, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 0F8h, 018h, 018h, 018h
          db        018h, 018h, 0F8h, 018h, 0F8h, 018h, 018h, 018h
          db        036h, 036h, 036h, 036h, 0F6h, 036h, 036h, 036h
          db        000h, 000h, 000h, 000h, 0FEh, 036h, 036h, 036h
          db        000h, 000h, 0F8h, 018h, 0F8h, 018h, 018h, 018h
          db        036h, 036h, 0F6h, 006h, 0F6h, 036h, 036h, 036h
          db        036h, 036h, 036h, 036h, 036h, 036h, 036h, 036h
          db        000h, 000h, 0FEh, 006h, 0F6h, 036h, 036h, 036h
          db        036h, 036h, 0F6h, 006h, 0FEh, 000h, 000h, 000h
          db        036h, 036h, 036h, 036h, 0FEh, 000h, 000h, 000h
          db        018h, 018h, 0F8h, 018h, 0F8h, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 0F8h, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 01Fh, 000h, 000h, 000h
          db        018h, 018h, 018h, 018h, 0FFh, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 0FFh, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 01Fh, 018h, 018h, 018h
          db        000h, 000h, 000h, 000h, 0FFh, 000h, 000h, 000h
          db        018h, 018h, 018h, 018h, 0FFh, 018h, 018h, 018h
          db        018h, 018h, 01Fh, 018h, 01Fh, 018h, 018h, 018h
          db        036h, 036h, 036h, 036h, 037h, 036h, 036h, 036h
          db        036h, 036h, 037h, 030h, 03Fh, 000h, 000h, 000h
          db        000h, 000h, 03Fh, 030h, 037h, 036h, 036h, 036h
          db        036h, 036h, 0F7h, 000h, 0FFh, 000h, 000h, 000h
          db        000h, 000h, 0FFh, 000h, 0F7h, 036h, 036h, 036h
          db        036h, 036h, 037h, 030h, 037h, 036h, 036h, 036h
          db        000h, 000h, 0FFh, 000h, 0FFh, 000h, 000h, 000h
          db        036h, 036h, 0F7h, 000h, 0F7h, 036h, 036h, 036h
          db        018h, 018h, 0FFh, 000h, 0FFh, 000h, 000h, 000h
          db        036h, 036h, 036h, 036h, 0FFh, 000h, 000h, 000h
          db        000h, 000h, 0FFh, 000h, 0FFh, 018h, 018h, 018h
          db        000h, 000h, 000h, 000h, 0FFh, 036h, 036h, 036h
          db        036h, 036h, 036h, 036h, 03Fh, 000h, 000h, 000h
          db        018h, 018h, 01Fh, 018h, 01Fh, 000h, 000h, 000h
          db        000h, 000h, 01Fh, 018h, 01Fh, 018h, 018h, 018h
          db        000h, 000h, 000h, 000h, 03Fh, 036h, 036h, 036h
          db        036h, 036h, 036h, 036h, 0FFh, 036h, 036h, 036h
          db        018h, 018h, 0FFh, 018h, 0FFh, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 0F8h, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 01Fh, 018h, 018h, 018h
          db        0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh
          db        000h, 000h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
          db        0F0h, 0F0h, 0F0h, 0F0h, 0F0h, 0F0h, 0F0h, 0F0h
          db        00Fh, 00Fh, 00Fh, 00Fh, 00Fh, 00Fh, 00Fh, 00Fh
          db        0FFh, 0FFh, 0FFh, 0FFh, 000h, 000h, 000h, 000h
          db        000h, 000h, 076h, 0DCh, 0C8h, 0DCh, 076h, 000h
          db        078h, 0CCh, 0CCh, 0D8h, 0CCh, 0C6h, 0CCh, 000h
          db        0FEh, 0C6h, 0C0h, 0C0h, 0C0h, 0C0h, 0C0h, 000h
          db        000h, 000h, 0FEh, 06Ch, 06Ch, 06Ch, 06Ch, 000h
          db        0FEh, 0C6h, 060h, 030h, 060h, 0C6h, 0FEh, 000h
          db        000h, 000h, 07Eh, 0D8h, 0D8h, 0D8h, 070h, 000h
          db        000h, 000h, 066h, 066h, 066h, 066h, 07Ch, 0C0h
          db        000h, 076h, 0DCh, 018h, 018h, 018h, 018h, 000h
          db        07Eh, 018h, 03Ch, 066h, 066h, 03Ch, 018h, 07Eh
          db        038h, 06Ch, 0C6h, 0FEh, 0C6h, 06Ch, 038h, 000h
          db        038h, 06Ch, 0C6h, 0C6h, 06Ch, 06Ch, 0EEh, 000h
          db        00Eh, 018h, 00Ch, 03Eh, 066h, 066h, 03Ch, 000h
          db        000h, 000h, 07Eh, 0DBh, 0DBh, 07Eh, 000h, 000h
          db        006h, 00Ch, 07Eh, 0DBh, 0DBh, 07Eh, 060h, 0C0h
          db        01Eh, 030h, 060h, 07Eh, 060h, 030h, 01Eh, 000h
          db        000h, 07Ch, 0C6h, 0C6h, 0C6h, 0C6h, 0C6h, 000h
          db        000h, 0FEh, 000h, 0FEh, 000h, 0FEh, 000h, 000h
          db        018h, 018h, 07Eh, 018h, 018h, 000h, 07Eh, 000h
          db        030h, 018h, 00Ch, 018h, 030h, 000h, 07Eh, 000h
          db        00Ch, 018h, 030h, 018h, 00Ch, 000h, 07Eh, 000h
          db        00Eh, 01Bh, 01Bh, 018h, 018h, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 018h, 0D8h, 0D8h, 070h
          db        000h, 018h, 000h, 07Eh, 000h, 018h, 000h, 000h
          db        000h, 076h, 0DCh, 000h, 076h, 0DCh, 000h, 000h
          db        038h, 06Ch, 06Ch, 038h, 000h, 000h, 000h, 000h
          db        000h, 000h, 000h, 018h, 018h, 000h, 000h, 000h
          db        000h, 000h, 000h, 018h, 000h, 000h, 000h, 000h
          db        00Fh, 00Ch, 00Ch, 00Ch, 0ECh, 06Ch, 03Ch, 01Ch
          db        06Ch, 036h, 036h, 036h, 036h, 000h, 000h, 000h
          db        078h, 00Ch, 018h, 030h, 07Ch, 000h, 000h, 000h
          db        000h, 000h, 03Ch, 03Ch, 03Ch, 03Ch, 000h, 000h
          db        000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h

CP863:
          db        07Ch, 0C6h, 0C0h, 0C0h, 0C6h, 07Ch, 00Ch, 078h
          db        0CCh, 000h, 0CCh, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        00Ch, 018h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        07Ch, 082h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        07Ch, 082h, 038h, 06Ch, 0C6h, 0FEh, 0C6h, 000h
          db        030h, 018h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        07Fh, 0DBh, 0DBh, 07Bh, 01Bh, 01Bh, 01Bh, 000h
          db        000h, 000h, 07Eh, 0C0h, 0C0h, 07Eh, 00Ch, 038h
          db        07Ch, 082h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        0C6h, 000h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        030h, 018h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        066h, 000h, 038h, 018h, 018h, 018h, 03Ch, 000h
          db        07Ch, 082h, 038h, 018h, 018h, 018h, 03Ch, 000h
          db        000h, 000h, 000h, 000h, 000h, 0FFh, 000h, 0FFh
          db        018h, 00Ch, 038h, 06Ch, 0C6h, 0FEh, 0C6h, 000h
          db        03Eh, 061h, 03Ch, 066h, 066h, 03Ch, 086h, 07Ch
          db        018h, 030h, 0FEh, 0C0h, 0F8h, 0C0h, 0FEh, 000h
          db        030h, 018h, 0FEh, 0C0h, 0FCh, 0C0h, 0FEh, 000h
          db        038h, 044h, 0FEh, 0C0h, 0FCh, 0C0h, 0FEh, 000h
          db        07Ch, 082h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        0C6h, 000h, 0FEh, 0C0h, 0FCh, 0C0h, 0FEh, 000h
          db        066h, 000h, 03Ch, 018h, 018h, 018h, 03Ch, 000h
          db        078h, 084h, 000h, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        060h, 030h, 0CCh, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        000h, 0C6h, 07Ch, 0C6h, 0C6h, 07Ch, 0C6h, 000h
          db        07Ch, 082h, 038h, 06Ch, 0C6h, 06Ch, 038h, 000h
          db        0C6h, 000h, 0C6h, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        018h, 018h, 07Eh, 0C0h, 0C0h, 07Eh, 018h, 018h
          db        038h, 06Ch, 064h, 0F0h, 060h, 066h, 0FCh, 000h
          db        060h, 030h, 0C6h, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        07Ch, 082h, 000h, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        00Eh, 01Bh, 018h, 03Ch, 018h, 0D8h, 070h, 000h
          db        018h, 018h, 018h, 000h, 000h, 018h, 018h, 018h
          db        00Ch, 018h, 030h, 000h, 000h, 000h, 000h, 000h
          db        00Ch, 018h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        018h, 030h, 0CCh, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        000h, 0C6h, 000h, 000h, 000h, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 000h, 018h, 00Ch, 078h
          db        078h, 00Ch, 038h, 00Ch, 078h, 000h, 000h, 000h
          db        0FFh, 000h, 000h, 000h, 000h, 000h, 000h, 000h
          db        07Eh, 081h, 03Ch, 018h, 018h, 018h, 03Ch, 000h
          db        000h, 000h, 000h, 0FEh, 0C0h, 0C0h, 000h, 000h
          db        000h, 000h, 000h, 0FEh, 006h, 006h, 000h, 000h
          db        063h, 0E6h, 06Ch, 07Eh, 033h, 066h, 0CCh, 00Fh
          db        063h, 0E6h, 06Ch, 07Ah, 036h, 06Ah, 0DFh, 006h
          db        0E1h, 032h, 064h, 03Ah, 0F6h, 02Ah, 05Fh, 082h
          db        000h, 033h, 066h, 0CCh, 066h, 033h, 000h, 000h
          db        000h, 0CCh, 066h, 033h, 066h, 0CCh, 000h, 000h
          db        022h, 088h, 022h, 088h, 022h, 088h, 022h, 088h
          db        055h, 0AAh, 055h, 0AAh, 055h, 0AAh, 055h, 0AAh
          db        077h, 0DDh, 077h, 0DDh, 077h, 0DDh, 077h, 0DDh
          db        018h, 018h, 018h, 018h, 018h, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 0F8h, 018h, 018h, 018h
          db        018h, 018h, 0F8h, 018h, 0F8h, 018h, 018h, 018h
          db        036h, 036h, 036h, 036h, 0F6h, 036h, 036h, 036h
          db        000h, 000h, 000h, 000h, 0FEh, 036h, 036h, 036h
          db        000h, 000h, 0F8h, 018h, 0F8h, 018h, 018h, 018h
          db        036h, 036h, 0F6h, 006h, 0F6h, 036h, 036h, 036h
          db        036h, 036h, 036h, 036h, 036h, 036h, 036h, 036h
          db        000h, 000h, 0FEh, 006h, 0F6h, 036h, 036h, 036h
          db        036h, 036h, 0F6h, 006h, 0FEh, 000h, 000h, 000h
          db        036h, 036h, 036h, 036h, 0FEh, 000h, 000h, 000h
          db        018h, 018h, 0F8h, 018h, 0F8h, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 0F8h, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 01Fh, 000h, 000h, 000h
          db        018h, 018h, 018h, 018h, 0FFh, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 0FFh, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 01Fh, 018h, 018h, 018h
          db        000h, 000h, 000h, 000h, 0FFh, 000h, 000h, 000h
          db        018h, 018h, 018h, 018h, 0FFh, 018h, 018h, 018h
          db        018h, 018h, 01Fh, 018h, 01Fh, 018h, 018h, 018h
          db        036h, 036h, 036h, 036h, 037h, 036h, 036h, 036h
          db        036h, 036h, 037h, 030h, 03Fh, 000h, 000h, 000h
          db        000h, 000h, 03Fh, 030h, 037h, 036h, 036h, 036h
          db        036h, 036h, 0F7h, 000h, 0FFh, 000h, 000h, 000h
          db        000h, 000h, 0FFh, 000h, 0F7h, 036h, 036h, 036h
          db        036h, 036h, 037h, 030h, 037h, 036h, 036h, 036h
          db        000h, 000h, 0FFh, 000h, 0FFh, 000h, 000h, 000h
          db        036h, 036h, 0F7h, 000h, 0F7h, 036h, 036h, 036h
          db        018h, 018h, 0FFh, 000h, 0FFh, 000h, 000h, 000h
          db        036h, 036h, 036h, 036h, 0FFh, 000h, 000h, 000h
          db        000h, 000h, 0FFh, 000h, 0FFh, 018h, 018h, 018h
          db        000h, 000h, 000h, 000h, 0FFh, 036h, 036h, 036h
          db        036h, 036h, 036h, 036h, 03Fh, 000h, 000h, 000h
          db        018h, 018h, 01Fh, 018h, 01Fh, 000h, 000h, 000h
          db        000h, 000h, 01Fh, 018h, 01Fh, 018h, 018h, 018h
          db        000h, 000h, 000h, 000h, 03Fh, 036h, 036h, 036h
          db        036h, 036h, 036h, 036h, 0FFh, 036h, 036h, 036h
          db        018h, 018h, 0FFh, 018h, 0FFh, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 0F8h, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 01Fh, 018h, 018h, 018h
          db        0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh
          db        000h, 000h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
          db        0F0h, 0F0h, 0F0h, 0F0h, 0F0h, 0F0h, 0F0h, 0F0h
          db        00Fh, 00Fh, 00Fh, 00Fh, 00Fh, 00Fh, 00Fh, 00Fh
          db        0FFh, 0FFh, 0FFh, 0FFh, 000h, 000h, 000h, 000h
          db        000h, 000h, 076h, 0DCh, 0C8h, 0DCh, 076h, 000h
          db        078h, 0CCh, 0CCh, 0D8h, 0CCh, 0C6h, 0CCh, 000h
          db        0FEh, 0C6h, 0C0h, 0C0h, 0C0h, 0C0h, 0C0h, 000h
          db        000h, 000h, 0FEh, 06Ch, 06Ch, 06Ch, 06Ch, 000h
          db        0FEh, 0C6h, 060h, 030h, 060h, 0C6h, 0FEh, 000h
          db        000h, 000h, 07Eh, 0D8h, 0D8h, 0D8h, 070h, 000h
          db        000h, 000h, 066h, 066h, 066h, 066h, 07Ch, 0C0h
          db        000h, 076h, 0DCh, 018h, 018h, 018h, 018h, 000h
          db        07Eh, 018h, 03Ch, 066h, 066h, 03Ch, 018h, 07Eh
          db        038h, 06Ch, 0C6h, 0FEh, 0C6h, 06Ch, 038h, 000h
          db        038h, 06Ch, 0C6h, 0C6h, 06Ch, 06Ch, 0EEh, 000h
          db        00Eh, 018h, 00Ch, 03Eh, 066h, 066h, 03Ch, 000h
          db        000h, 000h, 07Eh, 0DBh, 0DBh, 07Eh, 000h, 000h
          db        006h, 00Ch, 07Eh, 0DBh, 0DBh, 07Eh, 060h, 0C0h
          db        01Eh, 030h, 060h, 07Eh, 060h, 030h, 01Eh, 000h
          db        000h, 07Ch, 0C6h, 0C6h, 0C6h, 0C6h, 0C6h, 000h
          db        000h, 0FEh, 000h, 0FEh, 000h, 0FEh, 000h, 000h
          db        018h, 018h, 07Eh, 018h, 018h, 000h, 07Eh, 000h
          db        030h, 018h, 00Ch, 018h, 030h, 000h, 07Eh, 000h
          db        00Ch, 018h, 030h, 018h, 00Ch, 000h, 07Eh, 000h
          db        00Eh, 01Bh, 01Bh, 018h, 018h, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 018h, 0D8h, 0D8h, 070h
          db        000h, 018h, 000h, 07Eh, 000h, 018h, 000h, 000h
          db        000h, 076h, 0DCh, 000h, 076h, 0DCh, 000h, 000h
          db        038h, 06Ch, 06Ch, 038h, 000h, 000h, 000h, 000h
          db        000h, 000h, 000h, 018h, 018h, 000h, 000h, 000h
          db        000h, 000h, 000h, 018h, 000h, 000h, 000h, 000h
          db        00Fh, 00Ch, 00Ch, 00Ch, 0ECh, 06Ch, 03Ch, 01Ch
          db        06Ch, 036h, 036h, 036h, 036h, 000h, 000h, 000h
          db        078h, 00Ch, 018h, 030h, 07Ch, 000h, 000h, 000h
          db        000h, 000h, 03Ch, 03Ch, 03Ch, 03Ch, 000h, 000h
          db        000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h

CP865:
          db        07Ch, 0C6h, 0C0h, 0C0h, 0C6h, 07Ch, 00Ch, 078h
          db        0CCh, 000h, 0CCh, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        00Ch, 018h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        07Ch, 082h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        0C6h, 000h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        030h, 018h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        030h, 030h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        000h, 000h, 07Eh, 0C0h, 0C0h, 07Eh, 00Ch, 038h
          db        07Ch, 082h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        0C6h, 000h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        030h, 018h, 07Ch, 0C6h, 0FEh, 0C0h, 07Ch, 000h
          db        066h, 000h, 038h, 018h, 018h, 018h, 03Ch, 000h
          db        07Ch, 082h, 038h, 018h, 018h, 018h, 03Ch, 000h
          db        030h, 018h, 000h, 038h, 018h, 018h, 03Ch, 000h
          db        0C6h, 038h, 06Ch, 0C6h, 0FEh, 0C6h, 0C6h, 000h
          db        038h, 06Ch, 07Ch, 0C6h, 0FEh, 0C6h, 0C6h, 000h
          db        018h, 030h, 0FEh, 0C0h, 0F8h, 0C0h, 0FEh, 000h
          db        000h, 000h, 07Eh, 012h, 0FEh, 090h, 0FEh, 000h
          db        03Eh, 06Ch, 0CCh, 0FEh, 0CCh, 0CCh, 0CEh, 000h
          db        07Ch, 082h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        0C6h, 000h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        030h, 018h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        078h, 084h, 000h, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        060h, 030h, 0CCh, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        0C6h, 000h, 0C6h, 0C6h, 0C6h, 07Eh, 006h, 0FCh
          db        0C6h, 038h, 06Ch, 0C6h, 0C6h, 06Ch, 038h, 000h
          db        0C6h, 000h, 0C6h, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        000h, 002h, 07Ch, 0CEh, 0D6h, 0E6h, 07Ch, 080h
          db        038h, 06Ch, 064h, 0F0h, 060h, 066h, 0FCh, 000h
          db        03Ah, 06Ch, 0CEh, 0D6h, 0E6h, 06Ch, 0B8h, 000h
          db        0F8h, 0CCh, 0CCh, 0FAh, 0C6h, 0CFh, 0C6h, 0C7h
          db        00Eh, 01Bh, 018h, 03Ch, 018h, 0D8h, 070h, 000h
          db        018h, 030h, 078h, 00Ch, 07Ch, 0CCh, 076h, 000h
          db        00Ch, 018h, 000h, 038h, 018h, 018h, 03Ch, 000h
          db        00Ch, 018h, 07Ch, 0C6h, 0C6h, 0C6h, 07Ch, 000h
          db        018h, 030h, 0CCh, 0CCh, 0CCh, 0CCh, 076h, 000h
          db        076h, 0DCh, 000h, 0DCh, 066h, 066h, 066h, 000h
          db        076h, 0DCh, 000h, 0E6h, 0F6h, 0DEh, 0CEh, 000h
          db        03Ch, 06Ch, 06Ch, 03Eh, 000h, 07Eh, 000h, 000h
          db        038h, 06Ch, 06Ch, 038h, 000h, 07Ch, 000h, 000h
          db        018h, 000h, 018h, 018h, 030h, 063h, 03Eh, 000h
          db        000h, 000h, 000h, 0FEh, 0C0h, 0C0h, 000h, 000h
          db        000h, 000h, 000h, 0FEh, 006h, 006h, 000h, 000h
          db        063h, 0E6h, 06Ch, 07Eh, 033h, 066h, 0CCh, 00Fh
          db        063h, 0E6h, 06Ch, 07Ah, 036h, 06Ah, 0DFh, 006h
          db        018h, 000h, 018h, 018h, 03Ch, 03Ch, 018h, 000h
          db        000h, 033h, 066h, 0CCh, 066h, 033h, 000h, 000h
          db        000h, 0C6h, 07Ch, 0C6h, 0C6h, 07Ch, 0C6h, 000h
          db        022h, 088h, 022h, 088h, 022h, 088h, 022h, 088h
          db        055h, 0AAh, 055h, 0AAh, 055h, 0AAh, 055h, 0AAh
          db        077h, 0DDh, 077h, 0DDh, 077h, 0DDh, 077h, 0DDh
          db        018h, 018h, 018h, 018h, 018h, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 0F8h, 018h, 018h, 018h
          db        018h, 018h, 0F8h, 018h, 0F8h, 018h, 018h, 018h
          db        036h, 036h, 036h, 036h, 0F6h, 036h, 036h, 036h
          db        000h, 000h, 000h, 000h, 0FEh, 036h, 036h, 036h
          db        000h, 000h, 0F8h, 018h, 0F8h, 018h, 018h, 018h
          db        036h, 036h, 0F6h, 006h, 0F6h, 036h, 036h, 036h
          db        036h, 036h, 036h, 036h, 036h, 036h, 036h, 036h
          db        000h, 000h, 0FEh, 006h, 0F6h, 036h, 036h, 036h
          db        036h, 036h, 0F6h, 006h, 0FEh, 000h, 000h, 000h
          db        036h, 036h, 036h, 036h, 0FEh, 000h, 000h, 000h
          db        018h, 018h, 0F8h, 018h, 0F8h, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 0F8h, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 01Fh, 000h, 000h, 000h
          db        018h, 018h, 018h, 018h, 0FFh, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 0FFh, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 01Fh, 018h, 018h, 018h
          db        000h, 000h, 000h, 000h, 0FFh, 000h, 000h, 000h
          db        018h, 018h, 018h, 018h, 0FFh, 018h, 018h, 018h
          db        018h, 018h, 01Fh, 018h, 01Fh, 018h, 018h, 018h
          db        036h, 036h, 036h, 036h, 037h, 036h, 036h, 036h
          db        036h, 036h, 037h, 030h, 03Fh, 000h, 000h, 000h
          db        000h, 000h, 03Fh, 030h, 037h, 036h, 036h, 036h
          db        036h, 036h, 0F7h, 000h, 0FFh, 000h, 000h, 000h
          db        000h, 000h, 0FFh, 000h, 0F7h, 036h, 036h, 036h
          db        036h, 036h, 037h, 030h, 037h, 036h, 036h, 036h
          db        000h, 000h, 0FFh, 000h, 0FFh, 000h, 000h, 000h
          db        036h, 036h, 0F7h, 000h, 0F7h, 036h, 036h, 036h
          db        018h, 018h, 0FFh, 000h, 0FFh, 000h, 000h, 000h
          db        036h, 036h, 036h, 036h, 0FFh, 000h, 000h, 000h
          db        000h, 000h, 0FFh, 000h, 0FFh, 018h, 018h, 018h
          db        000h, 000h, 000h, 000h, 0FFh, 036h, 036h, 036h
          db        036h, 036h, 036h, 036h, 03Fh, 000h, 000h, 000h
          db        018h, 018h, 01Fh, 018h, 01Fh, 000h, 000h, 000h
          db        000h, 000h, 01Fh, 018h, 01Fh, 018h, 018h, 018h
          db        000h, 000h, 000h, 000h, 03Fh, 036h, 036h, 036h
          db        036h, 036h, 036h, 036h, 0FFh, 036h, 036h, 036h
          db        018h, 018h, 0FFh, 018h, 0FFh, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 0F8h, 000h, 000h, 000h
          db        000h, 000h, 000h, 000h, 01Fh, 018h, 018h, 018h
          db        0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh, 0FFh
          db        000h, 000h, 000h, 000h, 0FFh, 0FFh, 0FFh, 0FFh
          db        0F0h, 0F0h, 0F0h, 0F0h, 0F0h, 0F0h, 0F0h, 0F0h
          db        00Fh, 00Fh, 00Fh, 00Fh, 00Fh, 00Fh, 00Fh, 00Fh
          db        0FFh, 0FFh, 0FFh, 0FFh, 000h, 000h, 000h, 000h
          db        000h, 000h, 076h, 0DCh, 0C8h, 0DCh, 076h, 000h
          db        078h, 0CCh, 0CCh, 0D8h, 0CCh, 0C6h, 0CCh, 000h
          db        0FEh, 0C6h, 0C0h, 0C0h, 0C0h, 0C0h, 0C0h, 000h
          db        000h, 000h, 0FEh, 06Ch, 06Ch, 06Ch, 06Ch, 000h
          db        0FEh, 0C6h, 060h, 030h, 060h, 0C6h, 0FEh, 000h
          db        000h, 000h, 07Eh, 0D8h, 0D8h, 0D8h, 070h, 000h
          db        000h, 000h, 066h, 066h, 066h, 066h, 07Ch, 0C0h
          db        000h, 076h, 0DCh, 018h, 018h, 018h, 018h, 000h
          db        07Eh, 018h, 03Ch, 066h, 066h, 03Ch, 018h, 07Eh
          db        038h, 06Ch, 0C6h, 0FEh, 0C6h, 06Ch, 038h, 000h
          db        038h, 06Ch, 0C6h, 0C6h, 06Ch, 06Ch, 0EEh, 000h
          db        00Eh, 018h, 00Ch, 03Eh, 066h, 066h, 03Ch, 000h
          db        000h, 000h, 07Eh, 0DBh, 0DBh, 07Eh, 000h, 000h
          db        006h, 00Ch, 07Eh, 0DBh, 0DBh, 07Eh, 060h, 0C0h
          db        01Eh, 030h, 060h, 07Eh, 060h, 030h, 01Eh, 000h
          db        000h, 07Ch, 0C6h, 0C6h, 0C6h, 0C6h, 0C6h, 000h
          db        000h, 0FEh, 000h, 0FEh, 000h, 0FEh, 000h, 000h
          db        018h, 018h, 07Eh, 018h, 018h, 000h, 07Eh, 000h
          db        030h, 018h, 00Ch, 018h, 030h, 000h, 07Eh, 000h
          db        00Ch, 018h, 030h, 018h, 00Ch, 000h, 07Eh, 000h
          db        00Eh, 01Bh, 01Bh, 018h, 018h, 018h, 018h, 018h
          db        018h, 018h, 018h, 018h, 018h, 0D8h, 0D8h, 070h
          db        000h, 018h, 000h, 07Eh, 000h, 018h, 000h, 000h
          db        000h, 076h, 0DCh, 000h, 076h, 0DCh, 000h, 000h
          db        038h, 06Ch, 06Ch, 038h, 000h, 000h, 000h, 000h
          db        000h, 000h, 000h, 018h, 018h, 000h, 000h, 000h
          db        000h, 000h, 000h, 018h, 000h, 000h, 000h, 000h
          db        00Fh, 00Ch, 00Ch, 00Ch, 0ECh, 06Ch, 03Ch, 01Ch
          db        06Ch, 036h, 036h, 036h, 036h, 000h, 000h, 000h
          db        078h, 00Ch, 018h, 030h, 07Ch, 000h, 000h, 000h
          db        000h, 000h, 03Ch, 03Ch, 03Ch, 03Ch, 000h, 000h
          db        000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h

CP866:
          incbin  "cp866x8.fnt", 1024

_TEXT ends
	end entry
	