#
# A Makefile for MEM
# (c) osFree project,
# author, date
#

PROJ = mem
TRGT = $(PROJ).exe
DESC = Show memory information
#defines object file names in format $(p)objname$(e)
srcfiles = $(p)mem$(e) $(p)msg$(e) $(p)kitten$(e) $(p)prf$(e)
# defines additional options for C compiler
# we use 80386 here because osFree at least requires 80386
ADD_COPT  = -ms -oahls -j -s -0
ADD_ASMOPT = -I=$(PATH)
JWASM = 1

!include $(%ROOT)tools/mk/appsdos.mk
!include $(MYDIR)mem.mk

.c: $(PORT_BASE)source$(SEP)mem

.h: $(PORT_BASE)source$(SEP)mem

$(PATH)msg.obj: msg.asm $(PATH)msg.inc $(MYDIR)utilmd04.inc

$(PATH)msg.inc: $(PATH)$(PROJ).txt
  $(verbose)$(SAY) MKMSGF   $^.
  $(verbose)$(MC) $[@ $^@ -Q -A -I$(MYDIR)$(PS)$(%OS2TK)$(SEP)inc

$(PATH)$(PROJ).txt: $(PATH)$(PROJ).ext
  $(verbose)$(SAY) MSGEXTRT $^.
  $(verbose)$(ME) $< $^@

$(PATH)$(PROJ).ext: .symbolic
 @%create $^@
 @%append $^@ >assign.asm
 @%append $^@ <$(%ROOT)build$(SEP)bin$(SEP)os2$(SEP)system$(SEP)oso001.msg
 @%append $^@ DOS0087
 @%append $^@ DOS1210
 @%append $^@ DOS3072
 @%append $^@ DOS3122
 @%append $^@ DOS3123
 @%append $^@ DOS3124
 @%append $^@ DOS3330
 @%append $^@ DOS3331
 @%append $^@ DOS3336
 @%append $^@ DOS3337
 @%append $^@ DOS3338
 @%append $^@ DOS3339
 @%append $^@ DOS3341
 @%append $^@ DOS3342
 @%append $^@ DOS3343
 @%append $^@ DOS3344
 @%append $^@ DOS3346
 @%append $^@ DOS3347
 @%append $^@ DOS3348
 @%append $^@ DOS3349
 @%append $^@ DOS3350
 @%append $^@ DOS3351
 @%append $^@ DOS3352
 @%append $^@ DOS3353
 @%append $^@ DOS3354
 @%append $^@ DOS3355
 @%append $^@ DOS3356
 @%append $^@ DOS3362
 @%append $^@ DOS3363
 @%append $^@ DOS3365
 @%append $^@ DOS3366
 @%append $^@ DOS3367
 @%append $^@ DOS3368
 @%append $^@ DOS3369
 @%append $^@ DOS3370
 @%append $^@ DOS3372
 @%append $^@ DOS3375
 @%append $^@ DOS3376
 @%append $^@ DOS3377
 @%append $^@ DOS3378
 @%append $^@ DOS3379
 @%append $^@ DOS3380
 @%append $^@ DOS3381
 @%append $^@ DOS3382
 @%append $^@ DOS3383
 @%append $^@ DOS3384
 @%append $^@ DOS3385
 @%append $^@ DOS3386
 @%append $^@ DOS3387
 @%append $^@ DOS3392
