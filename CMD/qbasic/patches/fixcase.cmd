/* rexx */

parse arg dir

call directory dir

call rename 'APPINFO',      'appinfo'
call rename 'BIN',          'bin'
call rename 'DOC',          'doc'
call rename 'SOURCE',       'source'

call directory 'source'

call rename 'EDIT',          'edit'

call directory 'edit'

call rename 'ASCIITAB.C',   'asciitab.c'
call rename 'BUILD_ED.BAT', 'build_ed.bat'
call rename 'CALENDAR.C',   'calendar.c'
call rename 'CONFIG.C',     'config.c'
call rename 'CONFIG.H',     'config.h'
call rename 'EDIT.C',       'edit.c'
call rename 'EDIT.H',       'edit.h'
call rename 'MENUS.C',      'menus.c'

call directory '..'

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
