10 REM The IBM Personal Computer Samples
20 REM Version 1.00 (C)Copyright IBM Corp 1981
30 REM Licensed Material - Program Property of IBM
40 REM Author - Glenn Stuart Dardick
50 KEY OFF:SCREEN 0,1:COLOR 15,0,0:WIDTH 40:CLS:LOCATE 5,19:PRINT "IBM"
60 LOCATE 7,12,0:PRINT "Personal Computer"
70 COLOR 10,0:LOCATE 10,9,0:PRINT CHR$(213)+STRING$(21,205)+CHR$(184)
80 LOCATE 11,9,0:PRINT CHR$(179)+"       SAMPLES       "+CHR$(179)
90 LOCATE 12,9,0:PRINT CHR$(179)+STRING$(21,32)+CHR$(179)
100 LOCATE 13,9,0:PRINT CHR$(179)+"    Version 1.00     "+CHR$(179)
110 LOCATE 14,9,0:PRINT CHR$(212)+STRING$(21,205)+CHR$(190)
120 COLOR 15,0:LOCATE 17,7,0:PRINT "(C) Copyright IBM Corp 1981"
130 COLOR 14,0:LOCATE 23,7,0:PRINT "Press space bar to continue"
140 POKE 106,0 'CLEAR KYBD BUFFER
150 CMD$ = INKEY$
160 IF CMD$="" THEN GOTO 150
170 IF CMD$ = CHR$(27) THEN GOTO 360
180 IF CMD$ = " " THEN GOTO 200
190 GOTO 140
200 SCREEN 0,1:COLOR 15,0,0:CLS:LOCATE 5,3:PRINT "SAMPLE PROGRAMS"
210 LOCATE 7,3,0:PRINT  "A - MUSIC    (32k)"
220 LOCATE 8,3,0:PRINT  "B - ART      (32k-Color/Graphics)"
230 LOCATE 9,3,0:PRINT  "C - MORTGAGE (48k)"
240 LOCATE 10,3,0:PRINT "D - CIRCLE   (BASICA-Color/Graphics)"
250 LOCATE 11,3,0:PRINT "E - DONKEY   (BASICA-Color/Graphics)"
251 LOCATE 12,3,0:PRINT "F - PIECHART (BASICA-Color/Graphics)"
252 LOCATE 13,3,0:PRINT "G - BALL     (BASICA-Color/Graphics)"
253 LOCATE 14,3,0:PRINT "H - COLORBAR (32k)"
254 LOCATE 15,3,0:PRINT "I - CALENDAR (32k)"
255 LOCATE 16,3,0:PRINT "J - SPACE    (BASICA-Color/Graphics)"
256 LOCATE 17,3,0:PRINT "ESC KEY - EXIT"
260 LOCATE 19,3,0:PRINT "ENTER LETTER OF PROGRAM"
262 LOCATE 21,3,0:PRINT "NOTE: All of the above programs"
263 LOCATE 22,3,0:PRINT "      require 48k if using BASICA"
270 POKE 106,0 'CLEAR KYBD BUFFER
272 K$ = INKEY$:IF K$ <> "" THEN GOTO 270
275 K$ = INKEY$:IF K$ = "" THEN GOTO 275
280 IF MID$(K$,1,1) = "A" THEN CHAIN "MUSIC",1000
290 IF MID$(K$,1,1) = "B" THEN CHAIN "ART",1000
300 IF MID$(K$,1,1) = "C" THEN CHAIN "MORTGAGE",1000
310 IF MID$(K$,1,1) = "D" THEN CHAIN "CIRCLE",1000
311 IF MID$(K$,1,1) = "E" THEN CHAIN "DONKEY",1000
312 IF MID$(K$,1,1) = "F" THEN CHAIN "PIECHART",1000
313 IF MID$(K$,1,1) = "G" THEN CHAIN "BALL",1000
314 IF MID$(K$,1,1) = "H" THEN CHAIN "COLORBAR",1000
315 IF MID$(K$,1,1) = "I" THEN CHAIN "CALENDAR",1000
316 IF MID$(K$,1,1) = "J" THEN CHAIN "SPACE",1000
318 IF MID$(K$,1,1) = "a" THEN CHAIN "MUSIC",1000
319 IF MID$(K$,1,1) = "b" THEN CHAIN "ART",1000
320 IF MID$(K$,1,1) = "c" THEN CHAIN "MORTGAGE",1000
321 IF MID$(K$,1,1) = "d" THEN CHAIN "CIRCLE",1000
322 IF MID$(K$,1,1) = "e" THEN CHAIN "DONKEY",1000
323 IF MID$(K$,1,1) = "f" THEN CHAIN "PIECHART",1000
324 IF MID$(K$,1,1) = "g" THEN CHAIN "BALL",1000
325 IF MID$(K$,1,1) = "h" THEN CHAIN "COLORBAR",1000
326 IF MID$(K$,1,1) = "i" THEN CHAIN "CALENDAR",1000
327 IF MID$(K$,1,1) = "j" THEN CHAIN "SPACE",1000
340 IF MID$(K$,1,1) = CHR$(27) THEN GOTO 360
350 GOTO 200
360 SCREEN 0,1:COLOR 7,0:CLS:END
1000 GOTO 200
