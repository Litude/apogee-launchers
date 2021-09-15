@ECHO OFF
:START
CLS
@ECHO.
@ECHO                        [01;37;45m An Apogee Software Productionÿ[00;37;40m
@ECHO.
@ECHO.
@ECHO                              [01;33;41m SUPER TRIVIA PAKÿ[00;37;40m
@ECHO.
@ECHO                              [01;33;44m 1 [01;36;40m   Next Generation Trivia
@ECHO.
@ECHO                              [01;33;44m 2 [01;36;40m   Word Whiz
@ECHO.
@ECHO                              [01;33;44m 3 [01;36;40m   Trivia Whiz
@ECHO.
@ECHO                              [01;33;44m 4 [01;36;40m   Phrase Master
@ECHO.
@ECHO                              [01;33;44m 5 [01;36;40m   Trek Trivia
@ECHO.
@ECHO                              [01;33;44m 6 [01;36;40m   BONUS GAME
@ECHO.
@ECHO                              [01;33;44m 7 [00;36;40m   QUIT
@ECHO.
@ECHO                           [01;37;40mYour choice (pick 1-7)? [01;05;31;40m±[00m
@ECHO.
@ECHO.
@ECHO.
@CHOICE /N /C1234567 ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ[00;30;40mÿ[00;37;40m[1D
IF ERRORLEVEL 7 GOTO EXIT
IF ERRORLEVEL 6 GOTO BONUS
IF ERRORLEVEL 5 GOTO TREK
IF ERRORLEVEL 4 GOTO PHRASE
IF ERRORLEVEL 3 GOTO TW1
IF ERRORLEVEL 2 GOTO WORDWHIZ
IF ERRORLEVEL 1 GOTO NGT1

:NGT1
CLS
IF NOT EXIST NGT1.EXE GOTO MISSING
NGT1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:WORDWHIZ
CLS
IF NOT EXIST WORDWHIZ.EXE GOTO MISSING
WORDWHIZ %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:TW1
CLS
IF NOT EXIST TW1.EXE GOTO MISSING
TW1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:PHRASE
CLS
IF NOT EXIST PHRASE.COM GOTO MISSING
PHRASE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:TREK
CLS
IF NOT EXIST TREK.EXE GOTO MISSING
TREK %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:BONUS
CLS
IF NOT EXIST BONUS.EXE GOTO MISSING
BONUS %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:MISSING
CLS
@ECHO ERROR CODE 02: File not found
PAUSE
GOTO START

:EXIT
CLS
