#
# A Makefile for MOVE
# (c) osFree project,
# author, date
#

PROJ = move
TRGT = $(PROJ).exe
DESC = DOS move
srcfiles = &
$(p)move$(e) &
$(p)misc$(e) &
$(p)movedir$(e) &
$(p)tnyprntf$(e) &
$(p)kitten$(e)

# We use 80386 here because osFree at least 80386
ADD_COPT = -mc -D__MSDOS__ -3 -oas -s
STACKSIZE = 4096

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)move.mk

.c: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;

.h: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;

