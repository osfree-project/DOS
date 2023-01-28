#
# A Makefile for MORE
# (c) osFree project,
# author, date
#

PROJ = sort
TRGT = $(PROJ).exe
DESC = DOS sort
srcfiles = &
$(p)sort$(e) &
$(p)tnyprntf$(e) &
$(p)kitten$(e)

# We use 80386 here because osFree at least 80386
ADD_COPT = -mc -D__MSDOS__ -3 -oas -s
STACKSIZE = 4096

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)sort.mk

.c: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;

.h: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;

