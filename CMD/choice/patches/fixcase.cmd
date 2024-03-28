/* rexx */

parse arg dir

call directory dir

call rename 'SOURCE',          'source'
call directory 'source'
call rename 'CHOICE',          'choice'
call directory 'choice'

call rename 'CHOICE.C',     'choice.c'
call rename 'KITTEN.C',     'kitten.c'
call rename 'KITTEN.H',     'kitten.h'
call rename 'PRF.C',        'prf.c'
call rename 'TALLOC.C',     'talloc.c'
call rename 'TCDUMMY.C',    'tcdummy.c'


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
