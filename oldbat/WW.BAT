@ECHO OFF

:START
SET CHOICES=5
CLS
@ECHO.
@ECHO                        [01;37;45m An Apogee Software Productionÿ[00;37;40m
@ECHO.
@ECHO.
@ECHO                                  [01;33;44m WORD WHIZÿ[00;37;40m
@ECHO.
@ECHO                                  [01;31;41m 1 [01;36;40m Volume 1
@ECHO.
@ECHO                                  [01;31;41m 2 [01;36;40m Volume 2
@ECHO.
@ECHO                                  [01;31;41m 3 [01;36;40m Volume 3
@ECHO.
@ECHO                                  [01;31;41m 4 [01;36;40m Volume 4
@ECHO.
@ECHO                                  [01;33;41m 5 [00;36;40m QUIT
@ECHO.
@ECHO                               [01;37;40mYour choice (pick 1-5)? [01;05;31;40m±[00m
@ECHO.
@ECHO.
@ECHO.
@ECHO.
@ECHO.
@ECHO.
@ECHO.
@ECHO [00;30;40mÿ[01;32;40mÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ[00;37;40m[1A[s
GOTO EP4CHECK

:EP4CHECK
IF EXIST WW4.EXE GOTO EP4ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP3CHECK

:EP3CHECK
IF EXIST WW3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP2CHECK

:EP2CHECK
IF EXIST WW2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP1CHECK

:EP1CHECK
IF EXIST WW1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO CHOICES

:EP4ENABLE
SET CHOICES=%CHOICES%4
@ECHO [13;35H[01;33;41m4[00;37;40m[u
GOTO EP3CHECK

:EP3ENABLE
SET CHOICES=%CHOICES%3
@ECHO [11;35H[01;33;41m3[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [09;35H[01;33;41m2[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [07;35H[01;33;41m1[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 5 GOTO WW1
IF ERRORLEVEL 4 GOTO WW2
IF ERRORLEVEL 3 GOTO WW3
IF ERRORLEVEL 2 GOTO WW4
IF ERRORLEVEL 1 GOTO EXIT

:WW1
CLS
WW1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:WW2
CLS
WW2 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:WW3
CLS
WW3 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:WW4
CLS
WW4 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
