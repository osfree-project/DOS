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
ADD_ASMOPT =  -dMODEL=l -dDEBUG=1 -dNDEBUG=1 -i=$(PATH)..$(SEP)strings$(SEP)critstrs -i=$(PATH) -i=$(MYDIR)
ADD_LINKOPT = #lib suppl.lib
DEST = none
COM = 1
NOLIBS = 1

!include $(%ROOT)tools/mk/appsdos.mk

TARGETS = $(PATH)context.def subdirs $(PATH)$(PROJ).com

.SUFFIXES: .def .x

.def: $(PATH)

.x: $(MYDIR)..$(SEP)contrib$(SEP)criter$(SEP)

.asm: $(MYDIR)..$(SEP)contrib$(SEP)criter$(SEP)

.inc: $(MYDIR)..$(SEP)contrib$(SEP)criter$(SEP)

$(PATH)context.def: $(MYDIR)..$(SEP)contrib$(SEP)criter$(SEP)context.x
 @mkctxt.exe $<
 @$(CP) $(MYDIR)..$(SEP)contrib$(SEP)criter$(SEP)context.h_c $(PATH) $(BLACKHOLE)
 @$(CP) $(MYDIR)..$(SEP)contrib$(SEP)criter$(SEP)context.inc $(PATH) $(BLACKHOLE)
 @$(CP) $(MYDIR)..$(SEP)contrib$(SEP)criter$(SEP)context.def $(PATH) $(BLACKHOLE)
 @$(DC) $(MYDIR)..$(SEP)contrib$(SEP)criter$(SEP)context.h_c $(BLACKHOLE)
 @$(DC) $(MYDIR)..$(SEP)contrib$(SEP)criter$(SEP)context.inc $(BLACKHOLE)
 @$(DC) $(MYDIR)..$(SEP)contrib$(SEP)criter$(SEP)context.def $(BLACKHOLE)

$(PATH)criter.obj: $(MYDIR)..$(SEP)contrib$(SEP)criter$(SEP)criter.asm $(PATH)context.def &
    $(MYDIR)..$(SEP)contrib$(SEP)criter$(SEP)dmy_cbrk.asm &
    $(MYDIR)..$(SEP)contrib$(SEP)include$(SEP)stuff.inc
