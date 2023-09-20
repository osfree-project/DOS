#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

PROJ = basic
TRGT = $(PROJ).exe
DESC = BASIC and BASICA programming language
#defines object file names in format objname.$(O)
srcfiles = &
$(p)bwbasic$(e) &
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
$(p)bwx_tty$(e)

# defines additional options for C compiler
ADD_COPT = -bc -ml -zc -ox -q -wx -za -DHAVE_MSDOS -D__WATCOM__ -3

# additions to install target
INSTALL_ADD = 1

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)basic.mk

install_add: $(DEST)$(SEP)$(PROJ).com &
             $(DEST)$(SEP)$(PROJ)a.com &
             $(DEST)$(SEP)gw$(PROJ).exe .SYMBOLIC

#$(PATH)$(PROJ1).com:

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

