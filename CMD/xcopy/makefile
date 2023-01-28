#
# A Makefile for XCOPY
# (c) osFree project,
# author, date
#

PROJ = xcopy
TRGT = $(PROJ).exe
DESC = Extended COPY tool
#defines object file names in format $(p)objname$(e)
srcfiles = $(p)xcopy$(e) $(p)kitten$(e) $(p)prf$(e)
# defines additional options for C compiler

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)xcopy.mk

.c: $(PORT_BASE)source

.h: $(PORT_BASE)source

