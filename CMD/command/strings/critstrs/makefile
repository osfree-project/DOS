#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

LANG = russian
LNG = $(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)strings$(SEP)$(LANG).err
DEST = os2

!include $(%ROOT)tools/mk/all.mk

TARGETS = $(PATH)strings.err
PLATFORM =

.SUFFIXES: .err

.err: $(PATH)

$(PATH)strings.err: $(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)strings$(SEP)DEFAULT.err
 @$(CP) $[@ $(PATH) $(BLACKHOLE)
 @cd $(PATH)
 @critstrs.exe $(LNG) $(BLACKHOLE)
