# $Id: makefile,v 1.1 2004/08/16 06:27:05 prokushev Exp $

PROJ = qbasic
TRGT = $(PROJ).exe
DESC = DOS QBasic
srcfiles = &
$(p)edit$(e) &
$(p)menus$(e) &
$(p)config$(e) &
$(p)calendar$(e) &
$(p)asciitab$(e) &
$(p)bwb_cmd$(e) &
$(p)bwb_cnd$(e) &
$(p)bwb_dio$(e) &
$(p)bwb_exp$(e) &
$(p)bwb_fnc$(e) &
$(p)bwb_inp$(e) &
$(p)bwb_int$(e) &
$(p)bwb_prn$(e) &
$(p)bwb_stc$(e) &
$(p)bwb_str$(e) &
$(p)bwb_tbl$(e) &
$(p)bwb_var$(e) &
$(p)bwd_cmd$(e) &
$(p)bwd_fun$(e) &
$(p)bwx_tty$(e) &
$(p)qbasic$(e)


# defines additional options for C compiler
#ADD_COPT = -bc -ml -zc -ox -q -wx -za -DHAVE_MSDOS -D__WATCOM__ -3

ADD_COPT = -fpi87 -sg -bc -ml -zc -zt -0 -st -ox -wx -q -zm -DHAVE_MSDOS -D__WATCOM__ -i=$(MYDIR)..$(SEP)include -i=$(PORT_BASE)..$(SEP)basic
ADD_LINKOPT = lib $(BLD)lib$(SEP)dflatp.lib, $(BLD)lib$(SEP)dtools.lib
#C      = l
HEAPSIZE = 18k
STACKSIZE = 18k

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)edit.mk

.c: $(PORT_BASE)source$(SEP)edit;$(PORT_BASE)..$(SEP)basic

.h: $(PORT_BASE)source$(SEP)edit;$(PORT_BASE)..$(SEP)basic

