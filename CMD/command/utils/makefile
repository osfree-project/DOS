#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

PROJ      = mkinfres
#TRGT      = $(PROJ).exe
DESC      = DOS command interpreter
srcfiles = $(p)mkinfres$(e)

!include $(%ROOT)tools/mk/tools.mk
!include $(MYDIR)..$(SEP)port$(SEP)freecom.mk

!ifeq %OS LINUX
ADD_COPT = -dLINUX
!endif
ADD_COPT += -i=$(PORT_BASE)include -i=$(PORT_BASE)suppl

.c: $(PORT_BASE)utils

TARGETS = $(PATH)$(PROJ).exe
