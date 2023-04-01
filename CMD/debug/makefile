#
# A Makefile for DEBUG
# (c) osFree project,
# author, date
#

PROJ      = debug
TRGT      = $(PROJ).com
DESC      = DOS debugger
#defines object file names in format $(p)objname$(e)
srcfiles  = $(p)debug$(e)
# defines additional options for C compiler
ADD_ASMOPT  = -DPM=0 -DNASM=0
ADD_LINKOPT = lib $(%WATCOM)$(SEP)lib286$(SEP)noemu87.lib
COM = 1
NOLIBS = 1
JWASM  = 1

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)debug.mk

# echo creating debug.com
# rem nasmw debug.asm -D PM=0 -D NASM=1 -O 2 -o debug.com -l debug.lst 
# yasm debug.asm -D PM=0 -D NASM=0 -o debug.com -l debug.lst 
#
# echo creating debugx.com
# rem nasmw debug.asm -D PM=1 -D NASM=1 -O 2 -o debugx.com -l debugx.lst 
# yasm debug.asm -D PM=1 -D NASM=0 -o debugx.com -l debugx.lst 

.asm: $(PORT_BASE)src

.inc: $(PORT_BASE)src
