#
# A main Makefile for FreeCOM
# (c) osFree project,
# author, date
#


PROJ = command
TRGT = $(PROJ).exe
DESC = Command processor

#defines object file names in format objname.$(O)
#XMS_SWAP=1
srcfiles = $(p)cb_catch$(e) $(p)termhook$(e) &
           $(p)xms_crit$(e) $(p)xms_brk$(e) $(p)xms_2e$(e) $(p)cswap$(e) &
!ifdef XMS_SWAP
           $(p)cswapc$(e) &
!endif
           $(p)batch$(e) $(p)cmdtable$(e) $(p)command$(e) $(p)dummies$(e) $(p)expalias$(e)  $(p)init$(e) &
           $(p)kswap$(e) $(p)loadhigh$(e) $(p)module$(e) $(p)redir$(e) $(p)ver$(e)
#DEBUG = all
STACKSIZE = 4096

# defines additional options for C compiler
DEST = none

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)..$(SEP)port$(SEP)freecom.mk

ADD_COPT    = &
!ifdef XMS_SWAP
  -dXMS_SWAP=1 &
!endif
  -dNDEBUG &
#  -dDEBUG &
#  -d2 &
  -ml -dMODEL=l -bt=dos -i=$(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR).. &
  -i=$(PATH)..$(SEP)criter$(SEP)criter1 -i=$(PATH)..$(SEP)strings$(SEP)critstrs &
  -i=$(PORT_BASE)strings -i=$(PORT_BASE)suppl &
  -i=$(PORT_BASE)shell -i=$(PORT_BASE)include &
  -i=$(MYDIR)..$(SEP)..$(SEP)include -i=$(PORT_BASE)

ADD_ASMOPT  = &
!ifdef XMS_SWAP
  -dXMS_SWAP=1 &
!endif
  -dNDEBUG &
#  -dDEBUG &
#  -d2 &
  -ml -dMODEL=l -bt=dos -i=$(PATH)..$(SEP)criter$(SEP)criter1 -i=$(PORT_BASE)strings -i=$(PORT_BASE)suppl -i=$(PORT_BASE)include -i=$(PORT_BASE)shell -i=$(PORT_BASE) &
  -i=$(PATH)..$(SEP)strings$(SEP)critstrs

ADD_LINKOPT = libpath $(%ROOT)build$(SEP)lib lib cmd.lib, lib.lib, suppl.lib, strings.lib

.c:   $(PORT_BASE)shell

.asm: $(PORT_BASE)shell
