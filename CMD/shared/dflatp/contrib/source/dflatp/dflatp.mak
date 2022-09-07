#
#    FreeDOS DFlat+ Makefile
#
# -- (c) Aitor Santamaria-Merino ---------------------------------------
# Based on FD-Edit Makefile, by Joe Cosentino, Jeremy Davis, Eric Auer
# ----------------------------------------------------------------------
#
# Compile DFlat+ for the Borland C (TurboC) compiler
# ussage:
#
#     make -f dflatp.mak  -D MODEL=%MODEL%  target
#
# Arguments:
#   MODEL   Values: (see build.bat)
#   target  (see below available target list)
#

# ----------------------------------------------------------------------
# Programmer customizable values:
# ----------------------------------------------------------------------

# Borland family compiler
DRIVE = \freedos\borlandc
CC = $(DRIVE)\bin\bcc
LINKER= $(DRIVE)\bin\tlink
LIB = $(DRIVE)\bin\tlib

# Placement for the LIBraries, INCludes and BINaries
OUTPATH_LIB = \FreeDOS\SOURCE\LIB
OUTPATH_INC = \FreeDOS\SOURCE\INC
OUTPATH_BIN = \FreeDOS\BIN

# ----------------------------------------------------------------------
# TARGETS:
# ----------------------------------------------------------------------
# 
# dflatp       The DFlat+ main library
# dfptools     The DFlat+ side tools
# all          all of dflatp, dfptools and dfpdebug
# clean        clean object and lib files

# ----------------------------------------------------------------------
# BEGIN
# ----------------------------------------------------------------------
#

LIBID = $(MODEL)B
BUILDLIST = dflatp.bld
TOOLLIST = +HELPBOX.OBJ  +DECOMP.OBJ

# ### DFlat+ COMPILE DEFAULTS:
# ###  -K ("default char is unsigned")
# ###  -w display warnings
# ###  -w-stv mute the "structure passed by value" warning
# ###  -Os   optimize for size
# ###  -d    merge duplicate strings
# Other posibilities:
# -1 use 186/286 -G for speed -K unsigned char -Z optimize register usage
# -O optimize jumps -M create link map -a word align (handle with care!)
# -f emulate FPU (default) -f- use no FPU -f87 use native FPU
# -r use reg vars -w enable warnings -N add stack checks
# -k use standard stack frame -p use pascal calls ...

COMPILE = $(CC) -m$(MODEL) -c -I$(DRIVE)\include -L$(DRIVE)\lib  -K -w -w-stv -Os -d
LINK= $(LINKER) $(DRIVE)\lib\c0$(MODEL)
LIBS= $(DRIVE)\lib\c$(MODEL)

# ----------------------------------------------------------------------
# TARGETS
# ----------------------------------------------------------------------

all:  dflatp  dfptools
dfptools: dtoolslib  fixhelp.exe  huffc.exe


.c.obj: 
        $(COMPILE) $*.c

dflatp:       dfpcomp.h window.obj video.obj message.obj               \
              mouse.obj console.obj textbox.obj listbox.obj            \
              normal.obj menu.obj menubar.obj popdown.obj              \
              rect.obj applicat.obj keys.obj sysmenu.obj               \
              dialbox.obj button.obj commdlg.obj msgbox.obj            \
              lists.obj statbar.obj decomp.obj editbox.obj             \
              combobox.obj pictbox.obj clipbord.obj search.obj         \
              dfalloc.obj checkbox.obj text.obj radio.obj              \
              spinbutt.obj  watch.obj slidebox.obj direct.obj          \
              main.obj systemrs.obj syshelp.obj  box.obj               \
              portab.c
        if exist dflatp$(LIBID).lib  del dflatp$(LIBID).lib
        $(LIB) dflatp$(LIBID).lib @$(BUILDLIST)
        copy dflatp$(LIBID).lib $(OUTPATH_LIB)
        copy dflatp.h   $(OUTPATH_INC)
        copy resource.h $(OUTPATH_INC)
        copy keys.h     $(OUTPATH_INC)
        copy commands.h $(OUTPATH_INC)
        copy classes.h  $(OUTPATH_INC)
        copy dflatmsg.h $(OUTPATH_INC)
        copy dfpcore.h  $(OUTPATH_INC)
        copy system.h   $(OUTPATH_INC)
        copy portab.h   $(OUTPATH_INC)
        copy dialbox.h  $(OUTPATH_INC)
        copy menu.h     $(OUTPATH_INC)
        

dtoolslib:  nolog.obj  log.obj logger.obj helpbox.obj  decomp.obj 
        if exist dtool?$(LIBID).lib  del dtool?$(LIBID).lib
        $(LIB) dtool0$(LIBID).lib $(TOOLLIST) +NOLOG.OBJ
        $(LIB) dtool1$(LIBID).lib $(TOOLLIST) +LOG.OBJ
        $(LIB) dtool2$(LIBID).lib $(TOOLLIST) +LOGGER.OBJ
        copy dtool?$(LIBID).lib $(OUTPATH_LIB)
        copy dfptools.h $(OUTPATH_INC)

huffc.exe: huffc.obj htree.obj
        $(LINK) huffc htree,$*.exe,$*,$(LIBS)
        copy huffc.exe $(OUTPATH_BIN)

fixhelp.exe: fixhelp.obj decomp.obj
        $(LINK) fixhelp decomp,$*.exe,$*,$(LIBS)
        copy fixhelp.exe $(OUTPATH_BIN)
       
clean:
				echo Cleaning: deleting *.obj and *.lib ...
				del *.obj
				del *.map
				del *.lib


