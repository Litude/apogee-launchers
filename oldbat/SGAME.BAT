@ECHO OFF
:START
CLS
@ECHO.
@ECHO                        [01;37;45m An Apogee Software Productionÿ[00;37;40m
@ECHO.
@ECHO.
@ECHO                               [01;33;41m SUPER GAME PAKÿ[00;37;40m
@ECHO.
@ECHO                               [01;33;44m 1 [01;36;40m   Shrine of Kroz
@ECHO.
@ECHO                               [01;33;44m 2 [01;36;40m   Raiders of the Forbidden Mine
@ECHO.
@ECHO                               [01;33;44m 3 [01;36;40m   Word Whiz
@ECHO.
@ECHO                               [01;33;44m 4 [01;36;40m   Rogue Runner
@ECHO.
@ECHO                               [01;33;44m 5 [01;36;40m   Trek Trivia
@ECHO.
@ECHO                               [01;33;44m 6 [01;36;40m   Asteroid Rescue
@ECHO.
@ECHO                               [01;33;44m 7 [01;36;40m   Block Five
@ECHO.
@ECHO                               [01;33;44m 8 [00;36;40m   QUIT
@ECHO.
@ECHO                            [01;37;40mYour choice (pick 1-8)? [01;05;31;40m±[00m
@ECHO.
@CHOICE /N /C12345678 ÿ        [00;33;40mRaiders of the Forbidden Mine requires a color graphics card.ÿÿÿÿÿÿÿÿ[00;30;40mÿ[00;37;40m[1D
IF ERRORLEVEL 8 GOTO EXIT
IF ERRORLEVEL 7 GOTO BLOCK5
IF ERRORLEVEL 6 GOTO RESCUE
IF ERRORLEVEL 5 GOTO TREKTRIV
IF ERRORLEVEL 4 GOTO RUNNER
IF ERRORLEVEL 3 GOTO WORDWHIZ
IF ERRORLEVEL 2 GOTO RAIDERS
IF ERRORLEVEL 1 GOTO SHRINE

:SHRINE
CLS
IF NOT EXIST SHRINE.EXE GOTO MISSING
SHRINE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:RAIDERS
CLS
IF NOT EXIST RAIDERS.EXE GOTO MISSING
RAIDERS %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:WORDWHIZ
CLS
IF NOT EXIST WORDWHIZ.EXE GOTO MISSING
WORDWHIZ %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:RUNNER
CLS
IF NOT EXIST RUNNER.EXE GOTO MISSING
RUNNER %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:TREKTRIV
CLS
IF NOT EXIST TREKTRIV.EXE GOTO MISSING
TREKTRIV %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:RESCUE
CLS
IF NOT EXIST RESCUE.EXE GOTO MISSING
RESCUE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:BLOCK5
CLS
IF NOT EXIST BLOCK5.EXE GOTO MISSING
BLOCK5 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:MISSING
CLS
@ECHO ERROR CODE 02: File not found
PAUSE
GOTO START

:EXIT
CLS
