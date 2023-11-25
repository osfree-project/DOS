#
# A Makefile for JOIN
# (c) osFree project,
# author, date
#

PROJ = join
TRGT = $(PROJ).exe
DESC = join drive to subdirectory
#defines object file names in format $(p)objname$(e)
srcfiles = $(p)join$(e)
# defines additional options for C compiler
ADD_COPT=-i=$(MYDIR)..$(SEP)..$(SEP)include
ADD_LINKOPT = lib dos_shared.lib libpath $(ROOT)build$(SEP)lib

!include $(%ROOT)tools/mk/appsdos.mk
