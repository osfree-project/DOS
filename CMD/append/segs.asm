extern start :near

_TEXT segment word public 'CODE' use16

	  org 100h
          ;.code
EXE_startcode:
          jmp start
          db 80h dup(0)		; Last 128 bytes of cmdline

_TEXT ends

       end EXE_startcode
