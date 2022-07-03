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
srcfiles = $(p)fixstrs$(e) $(p)porting$(e)
# defines additional options for C compiler
!ifeq %OS LINUX
ADD_COPT = -dLINUX
!endif
ADD_COPT += -dMODEL=l -d2 -db -i=$(BLD)$(RELDIR) -i=$(MYDIR)..$(SEP)include -i=$(MYDIR)..$(SEP)..$(SEP)include -i=$(MYDIR)..$(SEP)suppl
ADD_LINKOPT = debug all

LANG = russian
LNG = $(MYDIR)$(LANG).lng

DEST    = none
PLATFORM =

!include $(%ROOT)/mk/tools.mk

TARGETS = $(PATH)$(PROJ).exe $(BLD)$(RELDIR)strings.h subdirs $(BLD)lib$(SEP)strings.lib
#INSTALL = $(BLD)lib$(SEP)strings.lib

$(PATH)$(PROJ).exe:

$(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)$(SEP)strings.lib: .symbolic
$(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)strings.lib: .symbolic

$(BLD)$(RELDIR)strings.h : $(MYDIR)default.lng $(PATH)$(PROJ).exe
 @$(PATH)$(PROJ).exe /lib /dir $(BLD)$(RELDIR) $(LNG)

$(BLD)$(RELDIR)strings.lib: $(BLD)$(RELDIR)makefile.mk
 @$(MAKE) $(MAKEOPT) -f $< lib

$(BLD)lib$(SEP)strings.lib: $(BLD)$(RELDIR)strings.lib
 $(verbose)$(CP) $< $^@
