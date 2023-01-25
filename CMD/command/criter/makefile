#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

PROJ = criter
#TRGT = $(PROJ).exe
DESC = Critical Error & Dummy ^Break handler & Kernel Swap Context
DIRS = criter1
#defines object file names in format objname.$(O)
srcfiles = $(p)criter$(e)

# defines additional options for C compiler
ADD_ASMOPT = &
  -dNDEBUG &
  -ml -dMODEL=l -i=$(PATH)..$(SEP)strings$(SEP)critstrs -i=$(PATH) -i=$(MYDIR)
ADD_LINKOPT = #lib suppl.lib
DEST = none
COM = 1
NOLIBS = 1

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)..$(SEP)port$(SEP)freecom.mk

TARGETS = $(PATH)context.def subdirs $(PATH)$(PROJ).com

.SUFFIXES: .def .x

.def: $(PATH)

.x:   $(PORT_BASE)criter

.asm: $(PORT_BASE)criter

.inc: $(PORT_BASE)criter

$(PATH)context.def: $(PORT_BASE)criter$(SEP)context.x
 @mkctxt.exe $<
 @$(CP) $(PORT_BASE)criter$(SEP)context.h_c $(PATH) $(BLACKHOLE)
 @$(CP) $(PORT_BASE)criter$(SEP)context.inc $(PATH) $(BLACKHOLE)
 @$(CP) $(PORT_BASE)criter$(SEP)context.def $(PATH) $(BLACKHOLE)
 @$(DC) $(PORT_BASE)criter$(SEP)context.h_c $(BLACKHOLE)
 @$(DC) $(PORT_BASE)criter$(SEP)context.inc $(BLACKHOLE)
 @$(DC) $(PORT_BASE)criter$(SEP)context.def $(BLACKHOLE)

$(PATH)criter.obj: $(PORT_BASE)criter$(SEP)criter.asm $(PATH)context.def &
    $(PORT_BASE)criter$(SEP)dmy_cbrk.asm &
    $(PORT_BASE)include$(SEP)stuff.inc
