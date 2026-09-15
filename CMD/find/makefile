#
# A Makefile for FIND
# (c) osFree project,
# author, date
#

DESC = Find string in file
SOURCES = find find_str kitten tnyprntf
# defines additional options for C compiler
TARGET_API = DOS

!include $(%ROOT)tools/mk/build.mk
!include $(MYDIR)find.mk

.c: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;

.h: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;

#.c: $(MYDIR)contrib$(SEP)src;$(MYDIR)contrib$(SEP)kitten;$(MYDIR)contrib$(SEP)tnyprntf

#.h: $(MYDIR)contrib$(SEP)src;$(MYDIR)contrib$(SEP)kitten;$(MYDIR)contrib$(SEP)tnyprntf
