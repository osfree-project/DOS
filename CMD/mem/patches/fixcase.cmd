/* rexx */

parse arg dir

call directory dir

call rename 'APPINFO',      'appinfo'
call rename 'BIN',          'bin'
call rename 'DOC',          'doc'
call rename 'NLS',          'nls'
call rename 'SOURCE',       'source'

call directory 'source'

call rename 'MEM',          'mem'

call directory 'mem'

call rename 'MKFILES',      'mkfiles'
call rename 'TEST',         'test'
call rename 'BUILD.BAT',    'build.bat'
call rename 'FILELIST.TXT', 'filelist.txt'
call rename 'KITTEN.C',     'kitten.c'
call rename 'KITTEN.H',     'kitten.h'
call rename 'MAKEFILE',     'makefile'
call rename 'MAKENLS.PL',   'makenls.pl'
call rename 'MAKEZIP.BAT',  'makezip.bat'
call rename 'MEM.C',        'mem.c'
call rename 'MEM2.C',       'mem2.c'
call rename 'MEMSUPT.ASM',  'memsupt.asm'
call rename 'MEMTEST.C',    'memtest.c'
call rename 'MUSCHI.PL',    'muschi.pl'
call rename 'PRF.C',        'prf.c'

call directory 'mkfiles'

call rename 'GENERIC.MAK',  'generic.mak'
call rename 'MAKENLS.MAK',  'makenls.mak'
call rename 'NLS.MAK',      'nls.mak'
call rename 'TURBOCPP.MAK', 'turbocpp.mak'
call rename 'WATCOM.MAK',   'watcom.mak'

call directory '..'
call directory '..'

call directory 'appinfo'

call rename 'MEM.DE',        'mem.de'
call rename 'MEM.FR',        'mem.fr'
call rename 'MEM.LSM',       'mem.lsm'
call rename 'MEM.SV',        'mem.sv'
call rename 'MEM.TR',        'mem.tr'

call directory '..'

call directory 'bin'

call rename 'MEM.EXE',        'mem.exe'

call directory '..'

call directory 'nls'

call rename 'MEM.DE',        'mem.de'
call rename 'MEM.EN',        'mem.en'
call rename 'MEM.ES',        'mem.es'
call rename 'MEM.FI',        'mem.fi'
call rename 'MEM.FR',        'mem.fr'
call rename 'MEM.IT',        'mem.it'
call rename 'MEM.NL',        'mem.nl'
call rename 'MEM.PL',        'mem.pl'
call rename 'MEM.SL',        'mem.sl'
call rename 'MEM.SV',        'mem.sv'
call rename 'MEM.TR',        'mem.tr'


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
