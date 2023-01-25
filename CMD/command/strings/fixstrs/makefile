#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

PROJ  = fixstrs
DESC  = Control file attributes
TRGT  = $(PROJ).exe
#defines object file names in format objname.$(O)
srcfiles = $(p)fixstrs$(e) # $(p)porting$(e)
# defines additional options for C compiler
!ifeq %OS LINUX
ADD_COPT = -dLINUX
!endif
ADD_COPT += -dMODEL=l -i=$(BLD)$(RELDIR) -i=$(MYDIR)..$(SEP)..$(SEP)..$(SEP)include &
  -i=$(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)include -i=$(MYDIR)..$(SEP)..$(SEP)include &
  -i=$(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)suppl
ADD_LINKOPT = #debug all

!include $(%ROOT)tools/mk/tools.mk

.c: $(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)strings
