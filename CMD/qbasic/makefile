# $Id: makefile,v 1.1 2004/08/16 06:27:05 prokushev Exp $

DESC = DOS QBasic
SOURCES = edit menus config calendar asciitab bwb_cmd &
    bwb_cnd bwb_dio bwb_exp bwb_fnc bwb_inp bwb_int bwb_prn &
    bwb_stc bwb_str bwb_tbl bwb_var bwd_cmd bwd_fun bwx_tty &
    qbasic

# defines additional options for C compiler
#ADD_COPT = -bc -ml -zc -ox -q -wx -za -DHAVE_MSDOS -D__WATCOM__ -3

ADD_COPT = -fpi87 -sg -bc -ml -zc -zt -0 -st -ox -wx -q -zm -DHAVE_MSDOS -D__WATCOM__ -i=$(MYDIR)..$(SEP)include -i=$(PORT_BASE)..$(SEP)basic
ADD_LINKOPT = lib $(BLD)lib$(SEP)dflatp.lib, $(BLD)lib$(SEP)dtools.lib
#C      = l
HEAPSIZE = 18k
STACKSIZE = 18k
TARGET_API = DOS

!include $(%ROOT)tools/mk/build.mk
!include $(MYDIR)edit.mk

.c: $(PORT_BASE)source$(SEP)edit;$(PORT_BASE)..$(SEP)basic

.h: $(PORT_BASE)source$(SEP)edit;$(PORT_BASE)..$(SEP)basic
