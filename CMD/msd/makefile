# $Id: makefile,v 1.1 2004/08/16 06:27:05 prokushev Exp $

PROJ = msd
TRGT = $(PROJ).exe
DESC = DOS MSD
srcfiles = $(p)msd$(e)


ADD_COPT = -fpi87 -sg -bc -ml -zc -zt -0 -st -ox -wx -q -zm -DHAVE_MSDOS -D__WATCOM__ -i=$(MYDIR)..$(SEP)include -i=$(PORT_BASE)..$(SEP)basic
ADD_LINKOPT = lib $(BLD)lib$(SEP)dflatp.lib, $(BLD)lib$(SEP)dtools.lib
HEAPSIZE = 18k
STACKSIZE = 18k

!include $(%ROOT)tools/mk/appsdos.mk

