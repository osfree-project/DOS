# $Id: makefile,v 1.1 2004/08/16 06:27:05 prokushev Exp $

PROJ = msglib
TRGT = $(PROJ).lib
DESC = MsgLib
srcfiles = &
	$(p)msg2rtrv$(e) &
	$(p)closefd$(e) &
	$(p)dupfd$(e) &
	$(p)getoptx$(e) &
	$(p)hp-cats$(e) &
	$(p)idntstr0$(e) &
	$(p)msg0init$(e) &
	$(p)msg1emit$(e) &
	$(p)msg1gop1$(e) &
	$(p)msg1gop2$(e) &
	$(p)msg1gop3$(e) &
	$(p)msg1gopt$(e) &
	$(p)msg1hlps$(e) &
	$(p)msg1prnt$(e) &
	$(p)msg2cat$(e) &
	$(p)msg2cats$(e) &
	$(p)msg2chg$(e) &
	$(p)msg2clng$(e) &
	$(p)msg2code$(e) &
	$(p)msg2cset$(e) &
	$(p)msg2db$(e) &
	$(p)msg2emit$(e) &
	$(p)msg2free$(e) &
	$(p)msg2gcat$(e) &
	$(p)msg2get$(e) &
	$(p)msg2gop1$(e) &
	$(p)msg2gop2$(e) &
	$(p)msg2gop3$(e) &
	$(p)msg2gopt$(e) &
	$(p)msg2hlps$(e) &
	$(p)msg2icat$(e) &
	$(p)msg2idnt$(e) &
	$(p)msg2init$(e) &
	$(p)msg2lmsg$(e) &
	$(p)msg2lock$(e) &
	$(p)msg2mcat$(e) &
	$(p)msg2prnt$(e) &
	$(p)msg2read$(e) &
	$(p)msg2sclr$(e) &
	$(p)msg2ulck$(e) &
	$(p)msg2ulks$(e) &
	$(p)msgapp$(e) &
	$(p)msgexit$(e) &
	$(p)mtch_cst$(e) &
	$(p)scanlngs$(e) &
	$(p)scanmsg1$(e) &
	$(p)srch_str$(e) &
	$(p)chkansi$(e) &
	$(p)cntry$(e) &
	$(p)valid_mn$(e)

ADD_COPT = -i=$(PORT_BASE)fdos$(SEP)source$(SEP)include

	 # -zc -sg -bt=dos
ADD_LINKOPT = 

#UNI2H = 1

!include $(%ROOT)tools/mk/libsdos.mk
!include $(MYDIR)..$(SEP)port$(SEP)msglib.mk

.c: $(PORT_BASE)fdos$(SEP)source$(SEP)lib$(SEP)msglib

$(PATH)$(PROJ).lib: $(OBJS)
 @$(MAKE) $(MAKEOPT) library=$(PATH)$(PROJ).lib library
