#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

PROJ  = fixstrs
DESC  = Control file attributes
TRGT  = strings.lib
DIRS  = critstrs
#defines object file names in format objname.$(O)
srcfiles = $(p)fixstrs$(e) # $(p)porting$(e)
# defines additional options for C compiler
!ifeq %OS LINUX
ADD_COPT = -dLINUX
!endif
ADD_COPT += -dMODEL=l -i=$(BLD)$(RELDIR) -i=$(MYDIR)..$(SEP)contrib$(SEP)include -i=$(MYDIR)..$(SEP)..$(SEP)include -i=$(MYDIR)..$(SEP)contrib$(SEP)suppl
ADD_LINKOPT = #debug all

LANG = russian
LNG = $(MYDIR)..$(SEP)contrib$(SEP)strings$(SEP)$(LANG).lng

DEST    = none
PLATFORM =

!include $(%ROOT)tools/mk/tools.mk

.c: $(MYDIR)..$(SEP)contrib$(SEP)strings

TARGETS = $(PATH)$(PROJ).exe $(BLD)$(RELDIR)strings.h subdirs $(BLD)lib$(SEP)$(TRGT)
#INSTALL = $(BLD)lib$(SEP)strings.lib

$(PATH)$(PROJ).exe:

$(BLD)$(RELDIR)$(TRGT): .symbolic
#$(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)strings.lib: .symbolic
#$(BLD)lib$(SEP)strings.lib: .symbolic

$(BLD)$(RELDIR)strings.h : $(MYDIR)..$(SEP)contrib$(SEP)strings$(SEP)DEFAULT.lng $(PATH)$(PROJ).exe
 @$(CP) $(MYDIR)..$(SEP)contrib$(SEP)strings$(SEP)DEFAULT.lng $(BLD)$(RELDIR)
 @$(CP) $(MYDIR)..$(SEP)contrib$(SEP)strings$(SEP)$(LANG).lng $(BLD)$(RELDIR)
 @cd $(BLD)$(RELDIR)
 @$(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)$(PROJ).exe /lib /dir $(BLD)$(RELDIR) $(LNG)

$(BLD)$(RELDIR)$(TRGT): $(BLD)$(RELDIR)makefile.mk
 @$(MAKE) $(MAKEOPT) -f $< lib

$(BLD)lib$(SEP)$(TRGT): $(BLD)$(RELDIR)$(TRGT)
 $(verbose)$(CP) $< $^@
