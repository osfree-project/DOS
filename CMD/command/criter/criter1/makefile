#
# A Makefile for ATTRIB
# (c) osFree project,
# author, date
#

PROJ = criter1
#TRGT = $(PROJ).exe
DESC = Critical Error & Dummy ^Break handler & Kernel Swap Context
#defines object file names in format objname.$(O)
srcfiles = $(p)criter$(e)

# defines additional options for C compiler
ADD_ASMOPT =  -dDEBUG=1 -dNDEBUG=1 -dAUTO_FAIL  -dMODEL=l -i=$(PATH)..$(SEP)..$(SEP)strings$(SEP)critstrs -i=$(PATH) -i=$(MYDIR)
ADD_LINKOPT = # lib suppl.lib
DEST = none
COM = 1
NOLIBS = 1

!include $(%ROOT)tools/mk/appsdos.mk

TARGETS = $(PATH)context.def $(PATH)$(PROJ).com

.SUFFIXES: .def .x

.def: $(PATH)

.x:   $(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)criter$(SEP)

.asm: $(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)criter$(SEP)

.inc: $(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)criter$(SEP)

$(PATH)context.def: $(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)criter$(SEP)context.x
 @mkctxt.exe $<
 @$(CP) $(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)criter$(SEP)context.h_c $(PATH) $(BLACKHOLE)
 @$(CP) $(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)criter$(SEP)context.inc $(PATH) $(BLACKHOLE)
 @$(CP) $(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)criter$(SEP)context.def $(PATH) $(BLACKHOLE)
 @$(DC) $(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)criter$(SEP)context.h_c $(BLACKHOLE)
 @$(DC) $(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)criter$(SEP)context.inc $(BLACKHOLE)
 @$(DC) $(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)criter$(SEP)context.def $(BLACKHOLE)

$(PATH)criter.obj: $(PATH)context.def $(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)criter$(SEP)criter.asm &
    $(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)criter$(SEP)dmy_cbrk.asm &
    $(MYDIR)..$(SEP)..$(SEP)contrib$(SEP)include$(SEP)stuff.inc
