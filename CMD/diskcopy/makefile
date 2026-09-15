#
# A Makefile for DEBUG
# (c) osFree project,
# author, date
#

DESC      = Binary comparison of files
#defines object file names in format $(p)objname$(e)
SOURCES  = diskcopy drive memtypes simplcpy waitfinp &
    tdrvcpy scanner parser recovery exepath datgen &
    fastcopy smdskcpy lfnapi serialnm &
    ems xms mouse switchch critical hicritcl lfnchk &
    get_line db catgets mkdir95 ren95 l2s95 win95api &
    fopen95 getcwd95 dir95 fllpth95 find95 open95

TARGET_API = DOS
ADD_COPT = -ml -i=$(MYDIR)..$(SEP)include -i=$(MYDIR)..$(SEP)..$(SEP)include
ADD_LINKOPT = lib $(BLD)lib$(SEP)doscmd_shared.lib
JWASM = 1

!include $(%ROOT)tools/mk/build.mk

.c: $(MYDIR)contrib;$(MYDIR)contrib$(SEP)io95;$(MYDIR)contrib$(SEP)cats
.asm: $(MYDIR)contrib
