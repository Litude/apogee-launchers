@ECHO OFF

:START
SET CHOICES=5
CLS
@ECHO [0;32m
@ECHO   ßÛÛßßÛÜ ÜßßÛßßßÜ ÜßßÛÛßßßÜ ÜÛßÛÛßßÛÜ  ÜßßÛÛßßßÜ  ÜÛßßÛÜ ÜßßÛßßßÜ ÛÛ ÜÛßßßßßÜ
@ECHO    ÛÛ   ÛÛ ßßÜÜ      ÛßÛÛ Üß  ßÜÜß  Üß    ÛßÛÛ Üß ÜÛ   ÜÛÜ ßßÜÜ    Üß ßÛÜ   ß
@ECHO    ÛÜßÜÛß   ÛÜ ßÛÜ  Ûß ÜÜß      ÜßßßÜ    Ûß ÜÜß   ÛÛ Üß ÛÛ  ÛÜ ßÛÜ      ßßÛÛÜ
@ECHO    ÛÛ       ÛÛ  ÛÛ ÛÛßß  ÛÛ     ÛÛ  ÛÜ  ÛÛßß  ÛÛ  ÛÛÜß ÜÛÛ  ÛÛ  ÛÛ    Ü     ÛÛ
@ECHO   ÜÛÛÜ     ÜÛÛÜ Ûß Ûß   ÜÛÛÜ   ÜÛÛÜ ßÛÜ Ûß   ÜÛÛÜ  ßÛÛÛÛß  ÜÛÛÜ Ûß    ßÛÜÜÜÛÛß
@ECHO.
@ECHO                     ÜÛßßÛÛßßÛÜ ÜÛßßÛÜ  ÜßÛÛßÛÛßÛÛßÜ ÜßßÛßßßÜ
@ECHO                       ß ÛÛ ß  ÜÛ   ÜÛÜ  ÛÛÜÜßßÜÜÛÛ   ßßÜÜ Üß
@ECHO                         ÛÛ    ÛÛ Üß ÛÛ ÛÛ   ßß   ÛÛ   ÛÜ ßÜ
@ECHO                         ÛÛ    ÛÛÜß ÜÛÛ ÛÛ   ÛÛ   ÛÛ   ÛÛ   ÛÜ
@ECHO        [0;32mÜÜÜÜÜÜ          ÜÛÛÜ    ßÛÛÛÛß   ÛÛ ÜÛÛÜ ÛÛ   ÜÛÛÛÛÛÛß       [0;32mÜ[33mÜÜÜ[32mÜ
@ECHO     [0;32mßßß[43mß[40mß[43mßß[40mß[43mß[40mßßß                                                 [0;32mÜ[33mÛß[31;43mÜ[33;40mÜÛÜÛßÛ[32mÜ
@ECHO        [0;33mßÛßßÛß               [1;31mA Nevada Smith Adventure             [0;33mÛ[31mÜß[33mßÜßÜßß[31mÜ[33mÛ
@ECHO         [0;31mÜ[43mÜÜ[40mÜ                                                     [0;32;43mß[31;40mß[33mÜÜÛ ÛÜÜ[31mÛ[32;43mß[40m
@ECHO     [0;33m ÜÛß[31mÛÛÛÛ[33mßÛÜ        [1;32mWhich volume do you wish to play?         [0;32;43mÜ[1C[31;40mÛ[33mÛÜ ÜÛÛ[31mß[32;43mÜ[40m
@ECHO     [0;33m Û  [31;42mß[40mÛÛ[42mß[2C[33;40mÛ                                                  [0;33mÛÛ[31mÜ[33mßßßßßÛ[31mÛ[33mÛ
@ECHO        [0;32mÛÛ  ÛÛ             [31m1) Raiders of the Lost Tomb            [0;32;43mß[33;40mß [31mß[33mÛÛÛß ß[32;43mß[40m
@ECHO     [0;32m  ßßß  ßßß            [31m2) Pharaoh's Curse                     [0;32mß[9Cß
@ECHO                           [31m3) Temple of Terror
@ECHO                           [31m4) Nevada's Revenge
@ECHO                           [1;32m5) [1;31mQuit
@ECHO.
@ECHO [0;30;40mÿ[00;37;40m                         [01;33;40m(c) 1990 by Apogee Softwareÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ[00;37;40m[1A[s
GOTO EP4CHECK

:EP4CHECK
IF EXIST PTOMB4.EXE GOTO EP4ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP3CHECK

:EP3CHECK
IF EXIST PTOMB3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP2CHECK

:EP2CHECK
IF EXIST PTOMB2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP1CHECK

:EP1CHECK
IF EXIST PTOMB1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO CHOICES

:EP4ENABLE
SET CHOICES=%CHOICES%4
@ECHO [21;27H[1;32m4) [31mNevada's Revenge[00;37;40m[u
GOTO EP3CHECK

:EP3ENABLE
SET CHOICES=%CHOICES%3
@ECHO [20;27H[1;32m3) [31mTemple of Terror[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [19;27H[1;32m2) [31mPharaoh's Curse[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [18;27H[1;32m1) [31mRaiders of the Lost Tomb[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 5 GOTO PTOMB1
IF ERRORLEVEL 4 GOTO PTOMB2
IF ERRORLEVEL 3 GOTO PTOMB3
IF ERRORLEVEL 2 GOTO PTOMB4
IF ERRORLEVEL 1 GOTO EXIT

:PTOMB1
CLS
PTOMB1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:PTOMB2
CLS
PTOMB2 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:PTOMB3
CLS
PTOMB3 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:PTOMB4
CLS
PTOMB4 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
