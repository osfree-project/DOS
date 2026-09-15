#
# A Makefile for LABEL
# (c) osFree project,
# author, date
#

DESC = Change volume label
#defines object file names in format $(p)objname$(e)
SOURCES = label tnyprntf kitten
TARGET_API = DOS

!include $(%ROOT)tools/mk/build.mk
!include $(MYDIR)label.mk

.c: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;

.h: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;
