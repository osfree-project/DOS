#
# A main Makefile for osFree Command Line tools project
# (c) osFree project,
# valerius, 2006/10/30
#

32_BITS = 0
PROJ      = command
#TRGT      = $(PROJ).com
DESC      = DOS command interpreter

DIRS = port critstrs strings criter cmd suppl lib shell utils
DEST = os2$(SEP)mdos
#XMS_SWAP=1

!include $(%ROOT)tools/mk/all.mk

TARGETS=$(PATH)$(PROJ).com

$(PATH)$(PROJ).lnk: .symbolic

$(PATH)$(PROJ).com: $(PATH)shell$(SEP)$(PROJ).exe $(PATH)infores
!ifneq UNIX TRUE
  @copy /b $(PATH)shell$(SEP)command.exe + $(PATH)infores + $(PATH)criter$(SEP)criter1$(SEP)criter1.com + $(PATH)criter$(SEP)criter.com + $(BLD)$(RELDIR)strings$(SEP)strings.dat $(PATH)command.com
  @copy $(PATH)command.com $(DEST)
!else
  @cat $(PATH)shell$(SEP)command.exe $(PATH)infores $(PATH)criter$(SEP)criter1$(SEP)criter1.com $(PATH)criter$(SEP)criter.com $(BLD)$(RELDIR)strings$(SEP)strings.dat >$(PATH)command.com
  @cp $(PATH)command.com $(DEST)
!endif

$(PATH)infores: $(PATH)shell$(SEP)command.wmp $(PATH)shell$(SEP)command.exe
 @$(BLD)host$(SEP)$(%HOST)$(SEP)$(RELDIR)utils$(SEP)mkinfres.exe -T$(PATH)info.txt $^@ $(PATH)shell$(SEP)command.wmp $(PATH)shell$(SEP)command.exe
