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

!include $(%ROOT)tools/mk/tools.mk
!include $(MYDIR)..$(SEP)..$(SEP)port$(SEP)freecom.mk

!ifeq %OS LINUX
ADD_COPT = -dLINUX
!endif
ADD_COPT += -dMODEL=l -i=$(BLD)$(RELDIR) -i=$(MYDIR)..$(SEP)..$(SEP)..$(SEP)include &
  -i=$(PORT_BASE)include -i=$(MYDIR)..$(SEP)..$(SEP)include &
  -i=$(PORT_BASE)suppl
ADD_LINKOPT = disable 1008 #debug all

.c: $(PORT_BASE)strings
