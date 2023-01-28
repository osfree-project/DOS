#
# A Makefile for DISKCOMP
# (c) osFree project,
# author, date
#

PROJ = diskcomp
TRGT = $(PROJ).exe
DESC = Compare disks
#defines object file names in format $(p)objname$(e)
srcfiles = $(p)diskcomp$(e) $(p)drive$(e) $(p)md5$(e) $(p)misc$(e)
# defines additional options for C compiler
ADD_COPT  = -ml -i=$(MYDIR)..$(SEP)include

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)diskcomp.mk

.c: $(PORT_BASE)

.h: $(PORT_BASE)

