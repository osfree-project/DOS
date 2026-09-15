#
# A Makefile for MOVE
# (c) osFree project,
# author, date
#

DESC = DOS move
SOURCES = move misc movedir tnyprntf kitten
TAGET_API = DOS

# We use 80386 here because osFree at least 80386
ADD_COPT = -mc -D__MSDOS__ -3 -oas -s
STACKSIZE = 4096

!include $(%ROOT)tools/mk/build.mk
!include $(MYDIR)move.mk

.c: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;

.h: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;
