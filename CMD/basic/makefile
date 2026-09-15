#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

DESC = BASIC and BASICA programming language
#defines object file names in format objname.$(O)
SOURCES = bwbasic bwb_cmd bwb_cnd bwb_dio bwb_exp bwb_fnc &
     bwb_inp bwb_int bwb_prn bwb_stc bwb_str bwb_tbl bwb_var &
     bwd_cmd bwd_fun bwx_tty

# defines additional options for C compiler
ADD_COPT = -bc -ml -zc -ox -q -wx  -DHAVE_MSDOS -D__WATCOM__ -3 -DNO_HELP -DNO_MAINTAINER -DNO_OPTION -DNO_NONMS

# additions to install target
INSTALL_ADD = 1
TARGET_API = DOS

!include $(%ROOT)tools/mk/build.mk
!include $(MYDIR)basic.mk

install_add: $(DEST)$(SEP)$(PROJ).com &
             $(DEST)$(SEP)$(PROJ)a.com &
             $(DEST)$(SEP)gw$(PROJ).exe .SYMBOLIC

$(DEST)$(SEP)$(PROJ).com: $(PATH)$(PROJ).exe
 @$(SAY) INST     $^. $(LOG)
 @$(CP) $< $^@ $(BLACKHOLE)

$(DEST)$(SEP)$(PROJ)a.com: $(PATH)$(PROJ).exe
 @$(SAY) INST     $^. $(LOG)
 @$(CP) $< $^@ $(BLACKHOLE)

$(DEST)$(SEP)gw$(PROJ).exe: $(PATH)$(PROJ).exe
 @$(SAY) INST     $^. $(LOG)
 @$(CP) $< $^@ $(BLACKHOLE)

.c: $(PORT_BASE)

.h: $(PORT_BASE)
