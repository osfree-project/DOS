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

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)find.mk

.c: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;

.h: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;

#.c: $(MYDIR)contrib$(SEP)src;$(MYDIR)contrib$(SEP)kitten;$(MYDIR)contrib$(SEP)tnyprntf

#.h: $(MYDIR)contrib$(SEP)src;$(MYDIR)contrib$(SEP)kitten;$(MYDIR)contrib$(SEP)tnyprntf
