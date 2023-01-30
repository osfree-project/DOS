#
# A Makefile for MEM
# (c) osFree project,
# author, date
#

PROJ = mem
TRGT = $(PROJ).exe
DESC = Show memory information
#defines object file names in format $(p)objname$(e)
srcfiles = $(p)mem$(e) $(p)kitten$(e) $(p)prf$(e)
# defines additional options for C compiler
# we use 80386 here because osFree at least requires 80386
ADD_COPT  = -ms -oahls -j -s -3

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)mem.mk

.c: $(PORT_BASE)source$(SEP)mem

.h: $(PORT_BASE)source$(SEP)mem

