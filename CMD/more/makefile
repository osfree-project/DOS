#
# A Makefile for MORE
# (c) osFree project,
# author, date
#

DESC = DOS MORE
SOURCES = more tnyprntf kitten

# We use 80386 here because osFree at least 80386
ADD_COPT = -mc -D__MSDOS__ -3 -oas -s
STACKSIZE = 4096
TARGET_API = DOS

!include $(%ROOT)tools/mk/build.mk
!include $(MYDIR)more.mk

.c: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;

.h: $(PORT_BASE)src;$(PORT_BASE)kitten;$(PORT_BASE)tnyprntf;


#set COMFLAGS=-mt -lt
#set EXEFLAGS=-mc
#set CFLAGS=%EXEFLAGS%-fe=
