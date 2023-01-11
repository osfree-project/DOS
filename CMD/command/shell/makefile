#
# A main Makefile for FreeCOM
# (c) osFree project,
# author, date
#


PROJ = command
TRGT = $(PROJ).exe
DESC = Command processor

#defines object file names in format objname.$(O)
XMS_SWAP=1
srcfiles = $(p)cb_catch$(e) $(p)termhook$(e) &
           $(p)xms_crit$(e) $(p)xms_brk$(e) $(p)xms_2e$(e) $(p)cswap$(e) &
!ifdef XMS_SWAP
           $(p)cswapc$(e) &
!endif
           $(p)batch$(e) $(p)cmdtable$(e) $(p)command$(e) $(p)dummies$(e) $(p)expalias$(e)  $(p)init$(e) &
           $(p)kswap$(e) $(p)loadhigh$(e) $(p)module$(e) $(p)redir$(e) $(p)ver$(e) &

# defines additional options for C compiler
DEST = none

ADD_COPT    = &
!ifdef XMS_SWAP
  -dXMS_SWAP=1 &
!endif
  -d2 -db  &
  -dNDEBUG &
#  -dDEBUG &
  -ml -dMODEL=l -bt=dos -i=$(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR).. &
  -i=$(PATH)..$(SEP)criter$(SEP)criter1 -i=$(PATH)..$(SEP)strings$(SEP)critstrs &
  -i=$(MYDIR)..$(SEP)contrib$(SEP)strings -i=$(MYDIR)..$(SEP)contrib$(SEP)suppl &
  -i=$(MYDIR)..$(SEP)contrib$(SEP)shell -i=$(MYDIR)..$(SEP)contrib$(SEP)include &
  -i=$(MYDIR)..$(SEP)..$(SEP)include -i=$(MYDIR)..$(SEP)contrib

ADD_ASMOPT  = &
!ifdef XMS_SWAP
  -dXMS_SWAP=1 &
!endif
  -d2 -db  &
  -dNDEBUG &
#  -dDEBUG &
  -ml -dMODEL=l -bt=dos -i=$(PATH)..$(SEP)criter$(SEP)criter1 -i=$(MYDIR)..$(SEP)contrib$(SEP)strings -i=$(MYDIR)..$(SEP)contrib$(SEP)suppl -i=$(MYDIR)..$(SEP)contrib$(SEP)include -i=$(MYDIR)..$(SEP)contrib$(SEP)shell -i=$(MYDIR)..$(SEP)contrib &
  -i=$(PATH)..$(SEP)strings$(SEP)critstrs

ADD_LINKOPT = debug all libpath $(%ROOT)build$(SEP)lib lib cmd.lib, lib.lib, suppl.lib, strings.lib

!include $(%ROOT)tools/mk/appsdos.mk

.c:   $(MYDIR)..$(SEP)contrib$(SEP)shell

.asm: $(MYDIR)..$(SEP)contrib$(SEP)shell
