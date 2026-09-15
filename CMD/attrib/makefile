#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

DESC      = Control file attributes
#defines object file names in format $(p)objname$(e)
SOURCES   = attrib
TARGET_API = DOS

# defines additional options for C compiler
ADD_COPT  = -ms -3 -ox
#ADD_LINKOPT = lib $(BLD)lib$(SEP)doscmd_shared.lib

!include $(%ROOT)tools/mk/build.mk
!include $(MYDIR)attrib.mk

.c: $(PORT_BASE)

.h: $(PORT_BASE)
