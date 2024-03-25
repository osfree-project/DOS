/* rexx */

parse arg dir

call directory dir

call rename 'DEBUG.TXT',    'debug.txt'
call rename 'HISTORY.TXT',  'history.txt'
call rename 'MAKE.BAT',     'make.bat'
call rename 'MAKECM.BAT',   'makecm.bat'
call rename 'MAKECW.BAT',   'makecw.bat'
call rename 'MAKEX.BAT',    'makex.bat'
call rename 'README.TXT',   'readme.txt'

call directory 'src'

call rename 'DEBUG.ASM',    'debug.asm'
call rename 'DEBUGTBL.INC', 'debugtbl.inc'
call rename 'DISASM.INC',   'disasm.inc'
call rename 'DPRINTF.INC',  'dprintf.inc'
call rename 'FPTOSTR.INC',  'fptostr.inc'
call rename 'INSTR.KEY',    'instr.key'
call rename 'INSTR.ORD',    'instr.ord'
call rename 'INSTR.SET',    'instr.set'
call rename 'MKTABLES.C',   'mktables.c'
call rename 'TRAPD.INC',    'trapd.inc'
call rename 'TRAPP.INC',    'trapp.inc'
call rename 'TRAPPL.INC',   'trappl.inc'
call rename 'TRAPR.INC',    'trapr.inc'

call directory '..'
call directory 'Test'

call rename 'CODETS32.ASM', 'codets32.asm'
call rename 'DBGMBR.ASM',   'dbgmbr.asm'
call rename 'HUGESEG.ASM',  'hugeseg.asm'
call rename 'LEAVE.ASM',    'leave.asm'
call rename 'STR32.ASM',    'str32.asm'
call rename 'TESTI2F.ASM',  'testi2f.asm'
call rename 'TESTQQ.ASM',   'testqq.asm'
call rename 'UNREAL.ASM',   'unreal.asm'

call directory '..'
call directory 'Samples'

call rename 'DPMIBK16.ASM', 'dpmibk16.asm'
call rename 'DPMIBK32.ASM', 'dpmibk32.asm'
call rename 'DPMICL16.ASM', 'dpmicl16.asm'
call rename 'DPMICL16.SCR', 'dpmicl16.scr'
call rename 'DPMICL32.ASM', 'dpmicl32.asm'
call rename 'MAKEJ.BAT',    'makej.bat'


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
