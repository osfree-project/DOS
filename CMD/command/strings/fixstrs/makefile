#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

DESC  = Control file attributes
#defines object file names in format objname.$(O)
SOURCES = fixstrs # porting
# defines additional options for C compiler
TARGET_API = HOST
TARGET_BITS = 32

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
