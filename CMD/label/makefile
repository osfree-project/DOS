#
# A Makefile for LABEL
# (c) osFree project,
# author, date
#

PROJ = label
TRGT = $(PROJ).exe
DESC = Change volume label
#defines object file names in format $(p)objname$(e)
srcfiles = $(p)label$(e) $(p)tnyprntf$(e) &
$(p)kitten$(e)

# defines additional options for C compiler

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)label.mk

.c: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;

.h: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;
