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

$(PATH)msg.inc: $(PATH)$(PROJ).txt
  $(verbose)$(SAY) MKMSGF   $^.
  $(verbose)$(MC) -Q -A -I$(MYDIR)$(PS)$(%OS2TK)$(SEP)inc $[@ $^@

$(PATH)$(PROJ).txt: $(PATH)$(PROJ).ext
  $(verbose)$(SAY) MSGEXTRT $^.
  $(verbose)$(ME) $< $^@

#$(PATH)graftabl.ext: graftabl.asm
#  msgprof graftabl.asm > graftabl.ext

$(PATH)$(PROJ).ext: .symbolic
 @%create $^@
 @%append $^@ >graftabl.asm
 @%append $^@ <$(%ROOT)build$(SEP)bin$(SEP)os2$(SEP)system$(SEP)oso001.msg
 @%append $^@ DOS1001
 @%append $^@ DOS1210
 @%append $^@ DOS2010
 @%append $^@ DOS2011
 @%append $^@ DOS2012
 @%append $^@ DOS2013
 @%append $^@ DOS2014
 @%append $^@ DOS2015
 @%append $^@ DOS2016
 @%append $^@ DOS2017
 @%append $^@ DOS2018
 @%append $^@ DOS2019
 @%append $^@ DOS2020
 @%append $^@ DOS2021
 @%append $^@ DOS2022
 @%append $^@ DOS2023
 @%append $^@ DOS2024

