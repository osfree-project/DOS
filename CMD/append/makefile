#
# A Makefile for APPEND
# (c) osFree project,
# author, date
#

PROJ       = append
TRGT       = $(PROJ).com
DESC       = Append directory to search path
srcfiles   = $(p)segs$(e) $(p)environ$(e) $(p)cmdline$(e) $(p)int2f$(e) $(p)int21$(e) $(p)msg$(e) $(p)append$(e) 
NOLIBS     = 1
COM        = 1
JWASM      = 1
ADD_ASMOPT = -I=$(PATH);$(MYDIR)$(SEP)macrolib

!include $(%ROOT)tools/mk/appsdos.mk

$(PATH)msg.obj: msg.asm $(PATH)msg.inc

$(PATH)msg.inc: append.txt
  mkmsgf /A /I$(MYDIR);$(%WATCOM)$(SEP)h$(SEP)os2 append.txt $(PATH)msg.inc

#$(PATH)append.txt: append.ext
#  msgextrt append.ext > append.txt

#$(PATH)append.ext: append.asm
#  msgprof append.asm > append.ext
