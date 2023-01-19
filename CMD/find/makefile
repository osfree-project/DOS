#
# A Makefile for FIND
# (c) osFree project,
# author, date
#

PROJ = find
TRGT = $(PROJ).exe
DESC = Find string in file
#defines object file names in format $(p)objname$(e)
srcfiles = $(p)find$(e) $(p)find_str$(e) $(p)kitten$(e) $(p)tnyprntf$(e)
# defines additional options for C compiler
#ADD_COPT  = -ml -i=$(MYDIR)contrib$(SEP)src
#ADD_LINKOPT = lib $(BLD)lib$(SEP)doscmd_shared.lib

!include $(%ROOT)tools/mk/appsdos.mk

.c: $(MYDIR)contrib$(SEP)src;$(MYDIR)contrib$(SEP)kitten;$(MYDIR)contrib$(SEP)tnyprntf

.h: $(MYDIR)contrib$(SEP)src;$(MYDIR)contrib$(SEP)kitten;$(MYDIR)contrib$(SEP)tnyprntf
