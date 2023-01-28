#
# A Makefile for MORE
# (c) osFree project,
# author, date
#

PROJ = more
TRGT = $(PROJ).exe
DESC = DOS MORE
srcfiles = &
$(p)more$(e) &
$(p)tnyprntf$(e) &
$(p)kitten$(e)

# We use 80386 here because osFree at least 80386
ADD_COPT = -mc -D__MSDOS__ -3 -oas -s
STACKSIZE = 4096

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)more.mk

.c: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;

.h: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;


#set COMFLAGS=-mt -lt
#set EXEFLAGS=-mc
#set CFLAGS=%EXEFLAGS%-fe=
