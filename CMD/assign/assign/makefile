PROJ = assign
TRGT = $(PROJ).com
DESC = ASSIGN
#defines object file names in format $(p)objname$(e)
srcfiles = $(p)assign$(e) $(p)msg$(e)
# defines additional options for C compiler
ADD_COPT = -ms -D__WATCOM__
ADD_ASMOPT = -I=$(PATH)$(PS)$(MYDIR)macrolib
COM = 1

!include $(%ROOT)tools/mk/appsdos.mk

.c: $(PATH)

$(PATH)msg.obj: msg.asm $(PATH)msg.inc

$(PATH)assign.obj: assign.c $(PATH)asgn_asc.c

$(PATH)asgn_asc.c: $(PATH)..$(SEP)tsr$(SEP)asgn_tsr.com
  $(verbose)$(SAY) BIN2C    $^.
  $(verbose)bin2c.exe -A module $< > $^@

$(PATH)msg.inc: $(PATH)$(PROJ).txt
  $(verbose)$(SAY) MKMSGF   $^.
  $(verbose)$(MC) $[@ $(PATH)msg.inc -Q -C -I$(MYDIR)$(PS)$(%OS2TK)$(SEP)h

$(PATH)$(PROJ).txt: $(PATH)$(PROJ).ext
  $(verbose)$(SAY) MSGEXTRT $^.
  $(verbose)$(ME) $< $^@

$(PATH)$(PROJ).ext: .symbolic
 @%create $^@
 @%append $^@ >assign.asm
 @%append $^@ <$(%ROOT)build$(SEP)bin$(SEP)os2$(SEP)system$(SEP)oso001.msg
 @%append $^@ DOS1210
 @%append $^@ DOS1459
 @%append $^@ DOS1826
 @%append $^@ DOS3010
 @%append $^@ DOS3026
 @%append $^@ DOS3027
 @%append $^@ DOS3028
 @%append $^@ DOS3029
 @%append $^@ DOS3030
 @%append $^@ DOS3031
 @%append $^@ DOS3032
 @%append $^@ DOS3033
 
