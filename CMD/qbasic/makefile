# $Id: makefile,v 1.1 2004/08/16 06:27:05 prokushev Exp $

PROJ = edit
TRGT = $(PROJ).exe
DESC = DOS Edit
srcfiles = &
$(p)edit$(e) &
$(p)menus$(e) &
$(p)config$(e) &
$(p)calendar$(e) &
$(p)asciitab$(e)


#ADD_COPT = -ml -sg -i=$(MYDIR)..$(SEP)include #-sg -ml -zc -2 -bt=dos
ADD_COPT = -ml -bc -zc -zt -2 -ox -sg -i=$(MYDIR)..$(SEP)include
ADD_LINKOPT = lib $(BLD)lib$(SEP)dflatp.lib, $(BLD)lib$(SEP)dtools.lib
#UNI2H  = 1
C      = s
#HEAPSIZE = 65535

!include $(%ROOT)tools/mk/appsdos.mk

.c: $(MYDIR)contrib$(SEP)source$(SEP)edit

#.h: $(MYDIR)..$(SEP)include
