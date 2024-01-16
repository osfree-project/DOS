#
# A Makefile for FC
# (c) osFree project,
# author, date
#

PROJ = fc
TRGT = $(PROJ).exe
DESC = File compare
#defines object file names in format $(p)objname$(e)
srcfiles = $(p)fc$(e) $(p)fctools$(e) $(p)kitten$(e) $(p)tnyprntf$(e)
# defines additional options for C compiler
ADD_COPT = -ml

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)fc.mk

.c: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;

.h: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;

