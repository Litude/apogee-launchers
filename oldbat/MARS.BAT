@ECHO OFF

:START
SET CHOICES=5
CLS
@ECHO [0;32;40m
@ECHO                           ßßßßÛßßß ÛÛ     ÛÛ ÛÛßßßßßß
@ECHO       [1;31m Designed by[0;32m           ÛÛ    ÛÛÜÜÜÜÜÜÛ ÛÛÜÜÜÜÜ     [1;31mCopyright (c)  1991[0;32m
@ECHO       [0;31mTodd Replogle[0;32m          ÛÛ    ÛÛ     ÜÛ ÛÛ          [0;31m Scenario Software[0;32m
@ECHO                              ÛÛ    ÛÛ     ÛÛ ÛÛÜÜÜÜÜÜ
@ECHO.
@ECHO ÛÛßßÛßßÛ ÛÛßßßßßÛ ÛÛßßÛ ÛÛ ÛÛ    ÛÛ ÛÛßßÛßßÛ ÛÛßßßßßß ÛÛßßÛ ÛÛ ßßßßÛßßß ÛÛßßßßßß[1A
@ECHO ÛÛ ÛÛ ÛÛ ÛÛ    ÛÛ ÛÛ ÛÛ ÛÛ ÛÛ    ÛÛ ÛÛ ÛÛ ÛÛ ÛÛÜÜÜÜÜ  ÛÛ ÛÛ ÛÛ    ÛÛ    ÛÛÜÜÜÜÜÜ[1A
@ECHO ÛÛ    ÛÛ ÛÛ    ÛÛ ÛÛ ÛÛ ÛÛ ÛÛ    ÛÛ ÛÛ    ÛÛ ÛÛ       ÛÛ ÛÛ ÛÛ    ÛÛ          ÜÛ[1A
@ECHO ÛÛ    ÛÛ ÛÛÜÜÜÜÜÛ ÛÛ ÛÛÜÜÛ ÛÛÜÜÜÜÜÛ ÛÛ    ÛÛ ÛÛÜÜÜÜÜÜ ÛÛ ÛÛÜÜÛ    ÛÛ    ÜÜÜÜÜÜÜÛ[1A
@ECHO.
@ECHO          ÛÛßßßßßÛ ÛÛßßßßßß      ÛÛßßÛßßÛ ÛÛßßßßßÛ ÛÛßßßßßÛ ÛÛßßßßßß  ÛÛ
@ECHO          ÛÛ    ÛÛ ÛÛÜÜÜÜÜ       ÛÛ ÛÛ ÛÛ ÛÛÜÜÜÜÜÛ ÛÛÜÜÜÜÜÛ ÛÛÜÜÜÜÜÜ  ÛÛ
@ECHO          ÛÛ    ÛÛ ÛÛ            ÛÛ    ÛÛ ÛÛ    ÜÛ ÛÛ   ÜÛ        ÜÛ  ßß
@ECHO          ÛÛÜÜÜÜÜÛ ÛÛ            ÛÛ    ÛÛ ÛÛ    ÛÛ ÛÛ   ÛÛÜ ÜÜÜÜÜÜÜÛ  ÜÛ
@ECHO.
@ECHO        [0;33mÜ[32;43mß[31mÜ[40mÛÛÜ          [1;33mWhich volume do you wish to play?        [0;32mÜßÜ[8CÜ
@ECHO        [33mÛ    [31mÛ                                                    [0;32mß[31;43mßÛ[5C[33;40mÜ[32;41mß[40mÜß
@ECHO        [33mÛ[31mÛÛÛÛÛ                  [31m1) First Contact                    [0;31;43mßÛ[3CÜ[40mÛ
@ECHO       ÜÜÜ[43mÜÜ[40mÜÜÜ                 [31m2) The Pyramid                      [0;33mÛ[31;43mß[40mÜ[33mÜ[31;43mÜß[40m
@ECHO      [33mÛÛ[31mÛÛ[32;43mÜÜ[31;40mÛÛ[33mÛÛ                [31m3) The Fortress                   [0;33mÜÛ[31;43mÜßÜßÜßÜ[33;40mÜ
@ECHO     ÛÛ [31mßÛ[43mÜÜ[40mÛß [33mÛÛ               [31m4) The Face                       [0;33mß[31;43mßÜ[33;40mÜ[31mÜß[33mßÜ[31;43mÜ[40mß
@ECHO        [31mÛÛ  ÛÛ                  [1;32m5) [1;31mQuit                             [0;33mÛ[31mÛ[33mß[31mß[33mÛ[31mÛÜ
@ECHO       [33mÜÛÛ  ÛÛÜ                                                  [0;33mÜÜÛ[31mÛß   ßßßß
@ECHO [00;30;40mÿ[00;37;40m                        [01;32;40mAn Apogee Software Productionÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ[00;37;40m[1A[s
GOTO EP4CHECK

:EP4CHECK
IF EXIST MARS4.EXE GOTO EP4ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP3CHECK

:EP3CHECK
IF EXIST MARS3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP2CHECK

:EP2CHECK
IF EXIST MARS2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP1CHECK

:EP1CHECK
IF EXIST MARS1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO CHOICES

:EP4ENABLE
SET CHOICES=%CHOICES%4
@ECHO [22;32H[01;32m4) [1;31mThe Face[00;37;40m[u
GOTO EP3CHECK

:EP3ENABLE
SET CHOICES=%CHOICES%3
@ECHO [21;32H[01;32m3) [1;31mThe Fortress[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [20;32H[01;32m2) [1;31mThe Pyramid[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [19;32H[01;32m1) [1;31mFirst Contact[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 5 GOTO MARS1
IF ERRORLEVEL 4 GOTO MARS2
IF ERRORLEVEL 3 GOTO MARS3
IF ERRORLEVEL 2 GOTO MARS4
IF ERRORLEVEL 1 GOTO EXIT

:MARS1
CLS
MARS1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:MARS2
CLS
MARS2 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:MARS3
CLS
MARS3 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:MARS4
CLS
MARS4 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
