REM @ECHO OFF
REM ======= FreeDOS DFlat+ Builder ========
REM == (c) Aitor Santamaría ===============

ECHO == FreeDOS DFlat+ Build ==
ECHO == (c) Aitor Santamaria ==

IF "*%1" == "*/?" GOTO JMPX

REM Set your MAKE tool here:
SET BMAKETOOL=\freedos\borlandc\bin\make
SET WMAKETOOL=\freedos\watcom\binw\wmake

IF *%2 == * GOTO JMP1
SET COMPILER=%2
GOTO JMP2
:JMP1
SET COMPILER=BC
:JMP2

IF *%3 == * GOTO JMP3
SET MODEL=%3
GOTO JMP4
:JMP3
SET MODEL=l
:JMP4

ECHO Building %1 for compiler %COMPILER%, Model %MODEL%...

IF "%COMPILER%" == "BC" GOTO JMPB

ECHO ON
%WMAKETOOL% -f dflatp.wmk -D MODEL=%MODEL%  %1
@ECHO OFF
GOTO JMPW

:JMPB
ECHO ON
%BMAKETOOL% -f dflatp.mak -D MODEL=%MODEL%  %1
@ECHO OFF


:JMPW
ECHO Building done.
GOTO JMPY

:JMPX
ECHO commandline:   BUILD [ make_target [ compiler  [ model ]]]
ECHO make_target:   target for the makefile (default: ALL)
ECHO compiler:      BC (default) or OW
ECHO model:         T tiny, S small, M medium, C compact, L large (default), H huge.
ECHO                   t: 1 ds/ss/cs, all near. (Borland only)
ECHO                   s: 1 cs, 1 ds/ss, all near.
ECHO                   m: 1 ds/ss, many CS, functions far.
ECHO                   c: 1 ds/ss, 1 cs, heap (malloc'ed data) is far.
ECHO                   l: 1 ds/ss, many CS, functions and heap are far.
ECHO                   h: 1 ss, many CS, many DS (static vars), everything far.


:JMPY
