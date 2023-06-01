/* rexx */

parse arg dir

call directory dir

call rename 'DOC',          'doc'
call rename 'SOURCE',       'source'

call directory 'doc'

call rename 'DFLATP',       'dflatp'

call directory 'dflatp'

call rename 'BUGS.TXT',     'bugs.txt'
call rename 'DFLATP.LSM',   'dflatp.lsm'
call rename 'DFP100.HTM',   'dfp100.htm'
call rename 'SOURCREF.TXT', 'sourcref.txt'

call directory '..'
call directory '..'

call directory 'source'

call rename 'DFLATP',        'dflatp'
call rename 'HWORLD',        'hworld'
call rename 'INC',           'inc'
call rename 'LIB',           'lib'

call directory 'dflatp'

call rename 'APPLICAT.C',    'applicat.c'
call rename 'BOX.C',         'box.c'
call rename 'BUILD.BAT',     'build.bat'
call rename 'BUTTON.C',      'button.c'
call rename 'CHECKBOX.C',    'checkbox.c'
call rename 'CLASSES.H',     'classes.h'
call rename 'CLIPBORD.C',    'clipbord.c'
call rename 'COMBOBOX.C',    'combobox.c'
call rename 'COMMANDS.H',    'commands.h'
call rename 'COMMDLG.C',     'commdlg.c'
call rename 'CONSOLE.C',     'console.c'
call rename 'DECOMP.C',      'decomp.c'
call rename 'DFALLOC.C',     'dfalloc.c'
call rename 'DFLATMSG.H',    'dflatmsg.h'
call rename 'DFLATP.BLD',    'dflatp.bld'
call rename 'DFLATP.H',      'dflatp.h'
call rename 'DFLATP.MAK',    'dflatp.mak'
call rename 'DFLATP.WMK',    'dflatp.wmk'
call rename 'DFLATP.WCB',    'dflatp.wcb'
call rename 'DFPCOMP.H',     'dfpcomp.h'
call rename 'DFPCORE.H',     'dfpcore.h'
call rename 'DFPTOOLS.H',    'dfptools.h'
call rename 'DIALBOX.C',     'dialbox.c'
call rename 'DIALBOX.H',     'dialbox.h'
call rename 'DIRECT.C',      'direct.c'
call rename 'EDITBOX.C',     'editbox.c'
call rename 'FIXHELP.C',     'fixhelp.c'
call rename 'HELPBOX.C',     'helpbox.c'
call rename 'HELPBOX.H',     'helpbox.h'
call rename 'HTREE.C',       'htree.c'
call rename 'HTREE.H',       'htree.h'
call rename 'HUFFC.C',       'huffc.c'
call rename 'KEYS.C',        'keys.c'
call rename 'KEYS.H',        'keys.h'
call rename 'LISTBOX.C',     'listbox.c'
call rename 'LISTS.C',       'lists.c'
call rename 'LOG.C',         'log.c'
call rename 'LOGGER.C',      'logger.c'
call rename 'MAIN.C',        'main.c'
call rename 'MENU.C',        'menu.c'
call rename 'MENU.H',        'menu.h'
call rename 'MENUBAR.C',     'menubar.c'
call rename 'MESSAGE.C',     'message.c'
call rename 'MOUSE.C',       'mouse.c'
call rename 'MSGBOX.C',      'msgbox.c'
call rename 'NOLOG.C',       'nolog.c'
call rename 'NORMAL.C',      'normal.c'
call rename 'PICTBOX.C',     'pictbox.c'
call rename 'POPDOWN.C',     'popdown.c'
call rename 'PORTAB.C',      'portab.c'
call rename 'PORTAB.H',      'portab.h'
call rename 'RADIO.C',       'radio.c'
call rename 'RECT.C',        'rect.c'
call rename 'RESOURCE.H',    'resource.h'
call rename 'SEARCH.C',      'search.c'
call rename 'SLIDEBOX.C',    'slidebox.c'
call rename 'SPINBUTT.C',    'spinbutt.c'
call rename 'STATBAR.C',     'statbar.c'
call rename 'SYSHELP.C',     'syshelp.c'
call rename 'SYSINT.H',      'sysint.h'
call rename 'SYSMENU.C',     'sysmenu.c'
call rename 'SYSTEM.H',      'system.h'
call rename 'SYSTEMRS.C',    'systemrs.c'
call rename 'TEXT.C',        'text.c'
call rename 'TEXTBOX.C',     'textbox.c'
call rename 'VIDEO.C',       'video.c'
call rename 'VIDEO.H',       'video.h'
call rename 'WATCH.C',       'watch.c'
call rename 'WINDOW.C',      'window.c'

call directory '..'
call directory 'hworld'

call rename 'BUILD_HW.BAT',      'build_hw.bat'
call rename 'HW.MAK',            'hw.mak'
call rename 'HWORLD.C',          'hworld.c'


exit 0
/* ------------------------------------------ */
rename: procedure
src = arg(1)
dst = arg(2)

parse source os .

if os = 'OS/2' | os = 'DOS' | os = 'WINDOWS' |,
   os = 'WINNT' | os = 'WIN32' | os = 'WIN64'
then MV = 'move'
else MV = 'mv'

ret = stream(src, 'c', 'query exists')

if ret \= '' then do
    MV' 'src' 'dst'1'
    MV' 'dst'1 'dst
end

return
/* ------------------------------------------ */
