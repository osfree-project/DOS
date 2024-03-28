#
# A Makefile for GRAFTABL
# (c) osFree project,
# author, date
#

PROJ       = graftabl
TRGT       = $(PROJ).com
DESC       = Append directory to search path
srcfiles   = $(p)graftabl2$(e) $(p)msg$(e)
NOLIBS     = 1
COM        = 1
JWASM      = 1
ADD_ASMOPT = -I=$(PATH)$(PS)$(MYDIR)macrolib

!include $(%ROOT)tools/mk/appsdos.mk

$(PATH)msg.obj: msg.asm $(PATH)msg.inc

$(PATH)msg.inc: $(PATH)graftabl.txt
  mkmsgf.exe -A -I$(MYDIR)$(PS)$(%OS2TK)$(SEP)inc $[@ $^@

$(PATH)graftabl.txt: $(PATH)graftabl.ext
  msgextrt.exe $< $^@

#$(PATH)graftabl.ext: graftabl.asm
#  msgprof graftabl.asm > graftabl.ext

$(PATH)graftabl.ext: .symbolic
 @%create $^@
 @%append $^@ >graftabl.asm
 @%append $^@ <$(%ROOT)build$(SEP)bin$(SEP)os2$(SEP)system$(SEP)oso001.msg
 @%append $^@ DOS1001

