/* rexx */

parse arg dir

call directory dir

call rename 'ATTRIB.C',     'attrib.c'
call rename 'ATTRIB.LSM',   'attrib.lsm'
call rename 'TYPES.H',      'types.h'
call rename 'TURBOC.CFG',   'turboc.cfg'
call rename 'STDIO.INC',    'stdio.inc'
call rename 'SETVBUF.INC',  'setvbuf.inc'
call rename 'SETUPIO.INC',  'setupio.inc'
call rename 'MALLOC.INC',   'malloc.inc'
call rename 'MAKEFILE',     'makefile'
call rename 'CC.BAT',       'cc.bat'
call rename 'DOC',          'doc'

call directory 'doc'

call rename 'ATTRIB.TXT',   'attrib.txt'
call rename 'FILES.LST',    'files.lst'
call rename 'HISTORY.TXT',  'history.txt'
call rename 'PLANS.TXT',    'plans.txt'


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
