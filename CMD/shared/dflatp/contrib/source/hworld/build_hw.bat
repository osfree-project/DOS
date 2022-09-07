REM Set your MAKE tool here:
SET MAKETOOL=\freedos\borlandc\bin\make

REM REMEMBER! Make TLINK available through path
PATH %PATH%;\FREEDOS\BORLANDC\BIN

%MAKETOOL% -f hw.mak %1
