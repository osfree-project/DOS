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


ADD_COPT = -ml -zc -zt -2 -ox -sg -i=$(MYDIR)..$(SEP)include
ADD_LINKOPT = lib $(BLD)lib$(SEP)dflatp.lib, $(BLD)lib$(SEP)dtools.lib
C      = s
STACKSIZE = 4096

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)edit.mk

.c: $(PORT_BASE)source$(SEP)edit

.h: $(PORT_BASE)source$(SEP)edit

