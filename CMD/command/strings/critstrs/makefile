#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

LANG = russian
LNG = $(MYDIR)..$(SEP)$(LANG).err
DEST = os2

!include $(%ROOT)/mk/all.mk

TARGETS = $(PATH)strings.err
PLATFORM =

.SUFFIXES: .err

.err: $(PATH)

$(PATH)strings.err: $(MYDIR)..$(SEP)default.err
 @$(CP) $[@ $(PATH) $(BLACKHOLE)
 @critstrs.exe /dir $(PATH) $(LNG) $(BLACKHOLE)
