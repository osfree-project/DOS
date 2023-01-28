#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

PROJ      = attrib
TRGT      = $(PROJ).exe
DESC      = Control file attributes
#defines object file names in format $(p)objname$(e)
srcfiles  = $(p)attrib$(e)

# defines additional options for C compiler
ADD_COPT  = -ms -3 -ox
#ADD_LINKOPT = lib $(BLD)lib$(SEP)doscmd_shared.lib

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)attrib.mk

.c: $(PORT_BASE)

.h: $(PORT_BASE)

