#
# A Makefile for EDLIN
# (c) osFree project,
# author, date
#

PROJ      = edlin
TRGT      = $(PROJ).com
DESC      = Line editor
srcfiles  = $(p)defines$(e) $(p)dynstr$(e) $(p)edlib$(e) $(p)edlin$(e)
COM       = 1

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)edlin.mk

.c: $(PORT_BASE)

.h: $(PORT_BASE)
