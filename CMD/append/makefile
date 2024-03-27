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
ADD_ASMOPT = -I=$(PATH)$(PS)$(MYDIR)macrolib

!include $(%ROOT)tools/mk/appsdos.mk

$(PATH)msg.obj: msg.asm $(PATH)msg.inc

$(PATH)msg.inc: $(PATH)append.txt
  mkmsgf.exe $[@ $(PATH)msg.inc -A -I$(MYDIR)$(PS)$(%OS2TK)$(SEP)inc

$(PATH)append.txt: $(PATH)append.ext
  msgextrt.exe $< $^@

#$(PATH)append.ext: append.asm
#  msgprof append.asm > append.ext

$(PATH)append.ext: .symbolic
 @%create $^@
 @%append $^@ >append.asm
 @%append $^@ <$(%ROOT)build$(SEP)bin$(SEP)os2$(SEP)system$(SEP)oso001.msg
 @%append $^@ DOS1210
 @%append $^@ DOS2046
 @%append $^@ DOS2047
 @%append $^@ DOS2049
 @%append $^@ DOS2050
 @%append $^@ DOS2052
 @%append $^@ DOS3091

