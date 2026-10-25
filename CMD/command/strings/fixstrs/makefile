#
# A Makefile for FIXSTRS
# (c) osFree project,
# author, date
#

DESC  = Control file attributes
SOURCES = fixstrs 
TARGET_API = HOST

!include $(%ROOT)tools/mk/build.mk
!include $(MYDIR)..$(SEP)..$(SEP)port$(SEP)freecom.mk

!ifeq %OS LINUX
ADD_COPT = -dLINUX
!endif
ADD_COPT += -dMODEL=l -i=$(BLD)$(RELDIR) -i=$(MYDIR)..$(SEP)..$(SEP)..$(SEP)include &
  -i=$(PORT_BASE)include -i=$(MYDIR)..$(SEP)..$(SEP)include &
  -i=$(PORT_BASE)suppl
ADD_LINKOPT = disable 1008 #debug all

.c: $(PORT_BASE)strings
