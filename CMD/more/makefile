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

.c: $(MYDIR)contrib$(SEP)src;$(MYDIR)contrib$(SEP)tnyprntf;$(MYDIR)contrib$(SEP)kitten

.h: $(MYDIR)contrib$(SEP)src;$(MYDIR)contrib$(SEP)tnyprntf;$(MYDIR)contrib$(SEP)kitten

#set COMFLAGS=-mt -lt
#set EXEFLAGS=-mc
#set CFLAGS=%EXEFLAGS%-fe=
