#
# A Makefile for FC
# (c) osFree project,
# author, date
#

PROJ = choice
TRGT = $(PROJ).exe
DESC = Ask for user input
#defines object file names in format $(p)objname$(e)
srcfiles = $(p)choice$(e) $(p)kitten$(e)
# defines additional options for C compiler

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)choice.mk

.c: $(PORT_BASE)source$(SEP)choice

.h: $(PORT_BASE)source$(SEP)choice

