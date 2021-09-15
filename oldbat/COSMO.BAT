@ECHO OFF

:START
SET CHOICES=4
CLS
@ECHO.
@ECHO [01;31;40m                          ÞÛßßß ÜÜÜ Ûßß ÛÛÜ ÜÜÜ Û Ûßß
@ECHO                           ÞÛ    Û Û ßßÛ ÛÞÞ Û Û   ßßÛ[01;32;40m
@ECHO                           ÞÛÜÜÜ ÛÛÛ ÛÛÛ ÛÞÞ ÛÛÛ   ÛÛÛ[01;31;40m
@ECHO                                            Ü              Ü
@ECHO         ÞÛßßß ÜÜÜ Ûßß ÛÛÜ ß   ÜÜÜ    ßßÛ ÜÜÛ Û Û Ûßß ÛÛÜ ÜÛÜ Û Û ÜÜÜ Ûßß[01;32;40m
@ECHO         ÞÛ    Û Û ßßÛ ÛÞÞ Û   Û      ÛßÛ Û Û Þ Ý Ûß  Û Þ  Û  Û Û Û   Ûß
@ECHO         ÞÛÜÜÜ ÛÛÛ ÛÛÛ ÛÞÞ ÛÛÛ ÛÛÛ    ÛÛÛ ÛÛÛ  Û  ÛÛÛ Û Þ  ÛÛ ÛÛÛ Û   ÛÛÛ
@ECHO.
@ECHO [01;35;40m                        F O R B I D D E N   P L A N E T
@ECHO.
@ECHO [01;33;40m               A game by Todd J. Replogle and Stephen A. Hornback
@ECHO [01;36;40m                 Copyright (c) 1992 Apogee Software Productions
@ECHO.
@ECHO                      [00;34;40mÞ[01;37;44mÉ[01;37;44mÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»[00;34;40mÝ[01;37;40m
@ECHO                      [00;34;40mÞ[01;37;44mº[00;34;43mÝ[01;37;43m                                [00;34;43mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                      [00;34;40mÞ[01;37;44mº[00;34;43mÝ[01;37;43m    ADVENTURE SELECTION MENU    [00;34;43mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                      [00;34;40mÞ[01;37;44mº[00;34;43mÝ[01;37;43m                                [00;34;43mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                      [00;34;40mÞ[01;37;44mº[00;34;43mÝ[00;37;43m 1) Adventure 1                 [00;34;43mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                      [00;34;40mÞ[01;37;44mº[00;34;43mÝ[00;37;43m 2) Adventure 2                 [00;34;43mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                      [00;34;40mÞ[01;37;44mº[00;34;43mÝ[00;37;43m 3) Adventure 3                 [00;34;43mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                      [00;34;40mÞ[01;37;44mº[00;34;43mÝ[01;37;43m                                [00;34;43mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                      [00;34;40mÞ[01;37;44mº[00;34;43mÝ[01;32;43m 4) [01;36;43mQuit                        [00;34;43mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                      [00;34;40mÞ[01;37;44mº[00;34;43mÝ[01;37;43m                                [00;34;43mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO [00;30;40mÿ[00;37;40m                    [00;34;40mÞ[01;37;44mÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼[00;34;40mÝ[00;37;40mÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ[1A[s
GOTO EP3CHECK

:EP3CHECK
IF EXIST COSMO3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP2CHECK

:EP2CHECK
IF EXIST COSMO2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP1CHECK

:EP1CHECK
IF EXIST COSMO1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO CHOICES

:EP3ENABLE
SET CHOICES=%CHOICES%3
@ECHO [21;26H[01;32;43m3) [01;36;43mAdventure 3[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [20;26H[01;32;43m2) [01;36;43mAdventure 2[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [19;26H[01;32;43m1) [01;36;43mAdventure 1[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 4 GOTO COSMO1
IF ERRORLEVEL 3 GOTO COSMO2
IF ERRORLEVEL 2 GOTO COSMO3
IF ERRORLEVEL 1 GOTO EXIT

:COSMO1
CLS
COSMO1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:COSMO2
CLS
COSMO2 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:COSMO3
CLS
COSMO3 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
