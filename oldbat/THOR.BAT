@ECHO OFF

:START
SET CHOICES=4
CLS
@ECHO.
@ECHO [01;36;40m                         An Apogee Software Production
@ECHO.
@ECHO                               [01;37;44m The Thor Trilogyÿ
@ECHO.
@ECHO [01;36;40m                             Volume Selection Menu
@ECHO.
@ECHO [01;36;40m                        Copyright 1990 (c) Todd Replogle
@ECHO [00;31;40mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[1A
@ECHO                        [00;32;40m1) Caves of Thor
@ECHO.
@ECHO                        [00;32;40m2) Realm of Thor
@ECHO.
@ECHO                        [00;32;40m3) Thor's Revenge
@ECHO.
@ECHO                        [01;32;40m4) Quit
@ECHO.
@ECHO.
@ECHO.
@ECHO.
@ECHO.
@ECHO                        [01;33;40mPlease select your choice (1-4):[05m_[00m
@ECHO [00;31;40mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[1A
@ECHO [01;34;40m                   The Thor Trilogy Created by Todd Replogle
@ECHO [00;30;40mÿ[01;34;40m                   Published by Apogee Software Productionsÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ[00;37;40m[1A[s
GOTO EP3CHECK

:EP3CHECK
IF EXIST REVENGE.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP2CHECK

:EP2CHECK
IF EXIST REALM.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP1CHECK

:EP1CHECK
IF EXIST CAVES.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO CHOICES

:EP3ENABLE
SET CHOICES=%CHOICES%3
@ECHO [14;24H[01;32;40m3) Thor's Revenge[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [12;24H[01;32;40m2) Realm of Thor[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [10;24H[01;32;40m1) Caves of Thor[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 4 GOTO CAVES
IF ERRORLEVEL 3 GOTO REALM
IF ERRORLEVEL 2 GOTO REVENGE
IF ERRORLEVEL 1 GOTO EXIT

:CAVES
CLS
CAVES %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:REALM
CLS
REALM %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:REVENGE
CLS
REVENGE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
