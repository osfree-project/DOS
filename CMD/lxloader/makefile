#
# A Makefile for STUB
# (c) osFree project,
# author, date
#

PROJ = lxloader
TRGT = $(PROJ).exe
DESC = DOS Loader Stub for OS/2 executables
#defines object file names in format $(p)objname$(e)
srcfiles = $(p)loader$(e)
# defines additional options for C compiler
ADD_COPT=-i=$(MYDIR)..$(SEP)..$(SEP)include
ADD_LINKOPT = lib dos_shared.lib libpath $(ROOT)build$(SEP)lib

DEST = os2$(SEP)mdos

!include $(%ROOT)tools/mk/appsdos.mk
