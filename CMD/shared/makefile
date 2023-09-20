#
# Makefile for DOS Commands Shared Library
#

PROJ      = doscmd_shared
TRGT      = $(PROJ).lib
ADD_COPT  = -ml -i=$(MYDIR)..$(SEP)include
srcfiles  = $(p)tcc2wat$(e) $(p)kitten$(e) $(p)prf$(e)
DIRS      = dflatp

TARGETS  = $(PATH)$(TRGT)

!include $(%ROOT)tools/mk/libsdos.mk

$(TARGETS): $(OBJS)
 @$(MAKE) $(MAKEOPT) library=$(TARGETS) library
