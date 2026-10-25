#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

DESC  = Control file attributes
TGT  = $(PROJ).lib
DIRS  = fixstrs critstrs
LANG = russian
LNG = $(PORT_BASE)strings$(SEP)$(LANG).lng

DEST = none

!include $(%ROOT)tools/mk/build.mk
!include $(MYDIR)..$(SEP)port$(SEP)freecom.mk

TARGETS = $(BLD)lib$(SEP)$(TGT)

$(BLD)$(RELDIR)strings.h: $(PORT_BASE)strings$(SEP)DEFAULT.lng
 $(verbose)$(CP) $(PORT_BASE)strings$(SEP)DEFAULT.lng $(BLD)$(RELDIR) $(BLACKHOLE)
 $(verbose)$(CP) $(PORT_BASE)strings$(SEP)$(LANG).lng $(BLD)$(RELDIR) $(BLACKHOLE)
 $(verbose)$(CD) $(BLD)$(RELDIR) && $(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)fixstrs$(SEP)fixstrs.exe /lib /dir $(BLD)$(RELDIR) $(LNG)

$(BLD)$(RELDIR)$(TGT): $(BLD)$(RELDIR)makefile.mk
 $(verbose)$(MAKE) $(MAKEOPT) -f $< lib

$(BLD)lib$(SEP)$(TGT): $(BLD)$(RELDIR)strings.h subdirs $(BLD)$(RELDIR)$(TGT)
 $(verbose)$(CP) $(BLD)$(RELDIR)$(TGT) $^@ $(BLACKHOLE)
