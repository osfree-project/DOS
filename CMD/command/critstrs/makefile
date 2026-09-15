#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

DESC = Critical Error Strings compiler
SOURCES = critstrs
ADD_COPT = -i=$(PORT_BASE)include
TARGET_API = HOST
TARGET_BITS = 32

!include $(%ROOT)tools/mk/build.mk
!include $(MYDIR)..$(SEP)port$(SEP)freecom.mk

ADD_COPT = -i=$(PORT_BASE)include

.c: $(PORT_BASE)strings
