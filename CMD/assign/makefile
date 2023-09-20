DIRS = port tsr
PROJ = assign
TRGT = $(PROJ).exe
DESC = ASSIGN
#defines object file names in format objname.$(O)
srcfiles = $(p)assign$(e)
# defines additional options for C compiler
ADD_COPT = -bc -ml -zc -ox -q -wx -za -DHAVE_MSDOS -D__WATCOM__

# additions to install target
INSTALL_ADD = 1

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)port$(SEP)assign.mk


.c: $(PORT_BASE)SOURCE$(SEP)ASSIGN

.h: $(PORT_BASE)SOURCE$(SEP)ASSIGN

