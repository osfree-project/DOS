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
ADD_COPT += -dMODEL=l -d2 -db -i=$(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR) -i=$(MYDIR)..$(SEP)include -i=$(MYDIR)..$(SEP)..$(SEP)include -i=$(MYDIR)..$(SEP)suppl
ADD_LINKOPT = debug all

LANG = russian
LNG = $(MYDIR)$(LANG).lng

DEST    = ..$(SEP)..$(SEP)build$(SEP)lib
PLATFORM =

!include $(%ROOT)/mk/tools.mk

TARGETS = $(PATH)$(PROJ).exe $(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)strings.h subdirs $(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)strings.lib
INSTALL = $(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)strings.lib

$(PATH)$(PROJ).exe:

$(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)strings.lib: .symbolic

$(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)strings.h : $(MYDIR)default.lng $(PATH)$(PROJ).exe
 @$(PATH)$(PROJ).exe /lib /dir $(PATH) $(LNG)

$(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)strings.lib: $(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)makefile.mk
 @$(MAKE) $(MAKEOPT) -f $< lib
 @$(MDHIER) $(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)..$(SEP)cmd
 @$(MDHIER) $(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)..$(SEP)lib
 @$(MDHIER) $(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)..$(SEP)shell
