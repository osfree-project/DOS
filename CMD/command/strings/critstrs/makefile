#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

LANG = russian
LNG = $(PORT_BASE)strings$(SEP)$(LANG).err
DEST = os2

!include $(%ROOT)tools/mk/all.mk
!include $(MYDIR)..$(SEP)..$(SEP)port$(SEP)freecom.mk

TARGETS = $(PATH)strings.err
PLATFORM =

.SUFFIXES: .err

.err: $(PATH)

$(PATH)strings.err: $(PORT_BASE)strings$(SEP)DEFAULT.err
 $(verbose)$(CP) $[@ $(PATH) $(BLACKHOLE)
 $(verbose)$(CD) $(PATH) && critstrs.exe $(LNG) $(BLACKHOLE)
