#
# A Makefile for DEBUG
# (c) osFree project,
# author, date
#

PROJ      = diskcopy
TRGT      = $(PROJ).exe
DESC      = Binary comparison of files
#defines object file names in format $(p)objname$(e)
srcfiles  = $(p)diskcopy$(e) $(p)drive$(e) $(p)memtypes$(e) $(p)simplcpy$(e) $(p)waitfinp$(e) $(p)tdrvcpy$(e) $(p)scanner$(e) $(p)parser$(e) $(p)recovery$(e) $(p)exepath$(e) $(p)datgen$(e) $(p)fastcopy$(e) $(p)smdskcpy$(e) $(p)lfnapi$(e) $(p)serialnm$(e) &
    $(p)ems$(e) $(p)xms$(e) $(p)mouse$(e) $(p)switchch$(e) $(p)critical$(e) $(p)hicritcl$(e) $(p)lfnchk$(e) &
    $(p)get_line$(e) &
    $(p)db$(e) &
    $(p)catgets$(e) &
    $(p)mkdir95$(e) &
    $(p)ren95$(e) &
    $(p)l2s95$(e) &
    $(p)win95api$(e) &
    $(p)fopen95$(e) &
    $(p)getcwd95$(e) &
    $(p)dir95$(e) &
    $(p)fllpth95$(e) &
    $(p)find95$(e) &
    $(p)open95$(e)


ADD_COPT = -ms -i=$(MYDIR)..$(SEP)include -i=$(MYDIR)..$(SEP)..$(SEP)include
ADD_LINKOPT = lib $(BLD)lib$(SEP)doscmd_shared.lib
JWASM = 1

!include $(%ROOT)tools/mk/appsdos.mk

.c: $(MYDIR)contrib;$(MYDIR)contrib$(SEP)io95;$(MYDIR)contrib$(SEP)cats
.asm: $(MYDIR)contrib
