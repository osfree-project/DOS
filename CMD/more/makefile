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

ADD_COPT = -ml -D__MSDOS__
#ADD_LINKOPT = lib $(BLD)lib$(SEP)doscmd_shared.lib
STACKSIZE = 4096

!include $(%ROOT)tools/mk/appsdos.mk

.c: $(MYDIR)contrib$(SEP)src;$(MYDIR)contrib$(SEP)tnyprntf;$(MYDIR)contrib$(SEP)kitten

.h: $(MYDIR)contrib$(SEP)src;$(MYDIR)contrib$(SEP)tnyprntf;$(MYDIR)contrib$(SEP)kitten

#set COMFLAGS=-mt -lt
#set EXEFLAGS=-mc
#set CFLAGS=%EXEFLAGS%-fe=
