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
    $(p)ems$(e) $(p)xms$(e) $(p)mouse$(e) $(p)switchch$(e) $(p)critical$(e) $(p)hicritcl$(e) $(p)lfnchk$(e)

ADD_COPT = -i=$(MYDIR)..$(SEP)include

!include $(%ROOT)tools/mk/appsdos.mk

.c: $(MYDIR)contrib
.asm: $(MYDIR)contrib
