PROJ = assign
TRGT = $(PROJ).exe
DESC = ASSIGN
#defines object file names in format objname.$(O)
srcfiles = $(p)assign$(e)
# defines additional options for C compiler
ADD_COPT = -ml -D__WATCOM__

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)..$(SEP)port$(SEP)assign.mk


.c: $(PORT_BASE)SOURCE$(SEP)ASSIGN

.h: $(PORT_BASE)SOURCE$(SEP)ASSIGN

