#
# A Makefile for DISKCOMP
# (c) osFree project,
# author, date
#

DESC = Compare disks
#defines object file names in format $(p)objname$(e)
SOURCES = diskcomp drive md5 misc
# defines additional options for C compiler
ADD_COPT  = -ml -i=$(MYDIR)..$(SEP)include
TARGET_API = DOS

!include $(%ROOT)tools/mk/build.mk
!include $(MYDIR)diskcomp.mk

.c: $(PORT_BASE)

.h: $(PORT_BASE)
