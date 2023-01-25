#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

PROJ = critstrs
TRGT = $(PROJ).exe
DESC = Critical Error Strings compiler
srcfiles = $(p)critstrs$(e)
ADD_COPT = -i=$(PORT_BASE)include

!include $(%ROOT)tools/mk/tools.mk
!include $(MYDIR)..$(SEP)port$(SEP)freecom.mk

ADD_COPT = -i=$(PORT_BASE)include

.c: $(PORT_BASE)strings
