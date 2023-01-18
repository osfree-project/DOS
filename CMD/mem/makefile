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
#ADD_COPT  = -ml -i=$(MYDIR)..$(SEP)include
#ADD_LINKOPT = lib $(BLD)lib$(SEP)doscmd_shared.lib

!include $(%ROOT)tools/mk/appsdos.mk

.c: $(MYDIR)contrib2$(SEP)SOURCE$(SEP)MEM

.h: $(MYDIR)contrib2$(SEP)SOURCE$(SEP)MEM
