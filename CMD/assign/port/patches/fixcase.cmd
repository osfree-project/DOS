/* rexx */

parse arg dir

call directory dir

call rename 'APPINFO',      'appinfo'
call rename 'BIN',          'bin'
call rename 'DOC',          'doc'
call rename 'HELP',         'help'
call rename 'SOURCE',       'source'

call directory 'appinfo'

call rename 'ASSIGN.DE',    'assign.de'
call rename 'ASSIGN.FR',    'assign.fr'
call rename 'ASSIGN.LSM',   'assign.lsm'
call rename 'ASSIGN.SV',    'assign.sv'
call rename 'ASSIGN.TR',    'assign.tr'

call directory '..'
call directory 'bin'

call rename 'ASSIGN.COM',  'assign.com'

call directory '..'
call directory 'doc'

call rename 'ASSIGN',      'assign'

call directory 'assign'

call rename 'ASSIGN.1',     'assign.1'
call rename 'BUGS',         'bugs'
call rename 'FILES',        'files'
call rename 'HISTORY',      'history'
call rename 'NOTES',        'notes'

call directory '..'
call directory '..'
call directory 'help'

call rename 'ASSIGN.DE',    'assign.de'
call rename 'ASSIGN.EN',    'assign.en'
call rename 'ASSIGN.ES',    'assign.es'
call rename 'ASSIGN.FR',    'assign.fr'
call rename 'ASSIGN.PTB',   'assign.ptb'
call rename 'ASSIGN.SV',    'assign.sv'
call rename 'ASSIGN.TR',    'assign.tr'

call directory '..'
call directory 'source'

call rename 'ASSIGN',      'assign'

call directory 'assign'

call rename 'ASGN_TSR.ASM',      'asgn_tsr.asm'
call rename 'ASSIGN.1',          'assign.1'
call rename 'ASSIGN.1G',         'assign.1g'
call rename 'ASSIGN.C',          'assign.c'
call rename 'BUGS',              'bugs'
call rename 'COMPILE.BAT',       'compile.bat'
call rename 'DEUTSCH.MSG',       'deutsch.msg'
call rename 'DEUTSCH.NRO',       'deutsch.nro'
call rename 'ELVIS.RC',          'elvis.rc'
call rename 'ENGLISH.MSG',       'english.msg'
call rename 'ENGLISH.NRO',       'english.nro'
call rename 'FILES',             'files'
call rename 'FOREACH.C',         'foreach.c'
call rename 'HISTORY',           'history'
call rename 'MAKEFILE',          'makefile'
call rename 'NOTES',             'notes'
call rename 'YERROR.H',          'yerror.h'


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
