# $Id: makefile,v 1.1 2004/08/16 06:27:05 prokushev Exp $

PROJ = dtools
TRGT = $(PROJ).lib
DESC = D-Flat+
srcfiles = &
	$(p)nolog$(e) &
	$(p)log$(e) &
	$(p)logger$(e) &
	$(p)helpbox$(e) &
	$(p)decomp$(e)


ADD_COPT = -ml -bc -zt -2 -ox -sg -zc
# -zc -sg -bt=dos
ADD_LINKOPT = 

#UNI2H = 1

!include $(%ROOT)tools/mk/libsdos.mk
!include $(MYDIR)..$(SEP)port$(SEP)dflatp.mk

.c: $(PORT_BASE)source$(SEP)dflatp

$(PATH)$(PROJ).lib: $(OBJS)
 @$(MAKE) $(MAKEOPT) library=$(PATH)$(PROJ).lib library
