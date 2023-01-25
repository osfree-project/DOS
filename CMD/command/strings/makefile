#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

PROJ  = strings
DESC  = Control file attributes
TGT  = $(PROJ).lib
DIRS  = fixstrs critstrs
#defines object file names in format objname.$(O)

LANG = russian
LNG = $(MYDIR)..$(SEP)contrib$(SEP)strings$(SEP)$(LANG).lng

DEST = none

!include $(%ROOT)tools/mk/all.mk

#PLATFORM =

TARGETS = $(BLD)lib$(SEP)$(TGT)
#INSTALL = $(BLD)lib$(SEP)strings.lib

#$(BLD)$(RELDIR)$(TGT): .symbolic
#$(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)strings.lib: .symbolic
#$(BLD)lib$(SEP)strings.lib: .symbolic

$(BLD)$(RELDIR)strings.h: $(MYDIR)..$(SEP)contrib$(SEP)strings$(SEP)DEFAULT.lng
 @$(CP) $(MYDIR)..$(SEP)contrib$(SEP)strings$(SEP)DEFAULT.lng $(BLD)$(RELDIR)
 @$(CP) $(MYDIR)..$(SEP)contrib$(SEP)strings$(SEP)$(LANG).lng $(BLD)$(RELDIR)
 @$(CD) $(BLD)$(RELDIR) && $(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)fixstrs$(SEP)fixstrs.exe /lib /dir $(BLD)$(RELDIR) $(LNG)

$(BLD)$(RELDIR)$(TGT): $(BLD)$(RELDIR)makefile.mk
 @$(MAKE) $(MAKEOPT) -f $< lib

$(BLD)lib$(SEP)$(TGT): $(BLD)$(RELDIR)strings.h subdirs $(BLD)$(RELDIR)$(TGT)
 $(verbose)$(CP) $(BLD)$(RELDIR)$(TGT) $^@
