# $Id: makefile,v 1.1 2004/08/16 06:27:05 prokushev Exp $

PROJ = dflatp
TRGT = $(PROJ).lib
DESC = D-Flat+
srcfiles = &
$(p)window$(e) &
$(p)video$(e) &
$(p)message$(e) &
$(p)mouse$(e) &
$(p)console$(e) &
$(p)textbox$(e) &
$(p)listbox$(e) &
$(p)normal$(e) &
$(p)menu$(e) &
$(p)menubar$(e) &
$(p)popdown$(e) &
$(p)rect$(e) &
$(p)applicat$(e) &
$(p)keys$(e) &
$(p)sysmenu$(e) &
$(p)dialbox$(e) &
$(p)button$(e) &
$(p)commdlg$(e) &
$(p)msgbox$(e) &
$(p)lists$(e) &
$(p)statbar$(e) &
$(p)decomp$(e) &
$(p)editbox$(e) &
$(p)combobox$(e) &
$(p)pictbox$(e) &
$(p)clipbord$(e) &
$(p)search$(e) &
$(p)dfalloc$(e) &
$(p)checkbox$(e) &
$(p)text$(e) &
$(p)radio$(e) &
$(p)spinbutt$(e) &
$(p)watch$(e) &
$(p)slidebox$(e) &
$(p)direct$(e) &
$(p)main$(e) &
$(p)systemrs$(e) &
$(p)syshelp$(e) &
$(p)box$(e) &
$(p)portab$(e)

ADD_COPT = -ml -bc -zt  -2 -ox -zc -sg

	 # -zc -sg -bt=dos
ADD_LINKOPT = 

#UNI2H = 1

!include $(%ROOT)tools/mk/libsdos.mk
!include $(MYDIR)..$(SEP)port$(SEP)dflatp.mk

.c: $(PORT_BASE)source$(SEP)dflatp

$(PATH)$(PROJ).lib: $(OBJS)
 @$(MAKE) $(MAKEOPT) library=$(PATH)$(PROJ).lib library
