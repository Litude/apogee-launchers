@ECHO OFF

:START
SET CHOICES=6
CLS
@ECHO [24CÜÜ    ÜÜÜ[5CÜÜ[5CÜÜÜÜÜ Ü    ÜÜ
@ECHO [22CÜ[35;47mÜ[40mßÜ[37mßÜÜß[35mÜßÜ[37mßÜ Ü[35;47mÜ[40mßÜ[37mßÜß[35;47mÜ[37;40mß[35mÜßÜß[37mÜ[35;47mÜ[40mß[37mÛ Ü[35;47mÜ[40mßÜ[37mßÜ
@ECHO [21CÛ[35mß[37mÜÛ[35mÜß[37mÛ[35mÜß[37mÜÛ[35mÜß[37mÛÛ[35mßÜ[47mß[37;40mß[35;47mß[37;40mß[35;47mß[37;40mÜ[35;47mß[40mÜß[37mÛßÛ[35mÜß[37mÛÛ[35mßÜ[47mß[37;40mß[35;47mß[37;40mß
@ECHO [20CÛ[35mÜß[47mÜ[37;40mß[35mÜß[37mÛ[35mÜß[47mÜ[40mßÜ[47mß[37;40mÛ[35mÜß[37mÜß[5CÛ[35mÜß[37mÛ Û[35mÜß[37mÛ[35mÜß[37mÜß
@ECHO [20CÛ[35mÜß[37mÜ[35;47mß[40mÜß[37mÛ[35mÜß[37mÜ[35mß[47mÜ[37;40mÜÛ[35mÜß[47mÜ[37;40mÜ[35;47mÜ[37;40mßÜ  Û[35mÜß[37mÛ Û[35mÜß[37mÛ[35mÜß[47mÜ[37;40mÜ[35;47mÜ[37;40mßÜ
@ECHO [20CÛ[35mÜß[37mÛÛ[35mÜß[37mÛ[35mÜß[37mÛ[35;47mß[40mÜß[37mÛÜ[35mßÜßÜ[47mß[37;40mß  Û[35mÜß[37mÛ Û[35mÜß[37mÛÜ[35mßÜßÜ[47mß[37;40mß
@ECHO [21Cßß  ßß ßß  ßß  ßßßß[5Cßß   ßß  ßßßß
@ECHO [11CÜÜ   ÜÜÜÜ   ÜÜ   ÜÜ  ÜÜÜÜÜ Ü   ÜÜ    ÜÜÜÜÜ Ü   Ü   ÜÜÜ   ÜÜÜÜÜ
@ECHO [9CÜ[35;47mÜ[40mßÜ[37mßÜß[35mÜßÜß[47mÜ[37;40mÜÛ[35mßÜ[37mÛ Û[35mÜß[37mÛß[35mÜßÜß[37mÜß[35mÜ[37mßÜÛ[35mÜß[37mÛß[35;47mÜ[37;40mß[35mÜßÜß[37mÜß[35mÜ[37mÛÜß[35mÜ[37mÛÜß[35mÜßÜ[37mßÜß[35mÜßÜß[37mÜß
@ECHO [8CÛ[35mß[37mÜ[47m [35;40mÜß[37mÛ[35mßÜ[47mß[37;40mß[35;47mß[40mÜß[37mÛ[35mßÜ[37mÛ Û[35mÜß[37mÛ[35mßÜ[47mß[37;40mÛÛÛ[35mßÜß[47mÜ[37;40mÛ[35mÜß[37mÛ[35;47mß[37;40mÜ[35;47mß[40mÜß[37mÛßÛ[35mßÜ[37mÛÛ[35mßÜ[37mÛ[35mÜß[37mÜÛ[35mÜß[37mÛ[35mßÜ[47mß[37;40mÛÛ
@ECHO [7CÛ[35mÜß[47mÜ[37;40mß[35mÜß[37mÛ[35mßÜ[37mÛ Ü[35;47mÜ[40mß[37mÛ[35mßÜ[37mÛ Û[35mÜ[47mß[37mÛ[35;40mßÜßÜ[47mß[37;40mÛ[35mßÜ[47mß[40mÜ[37mß[35mÜß[37mÛ  Û[35mÜß[37mÛ Û[35mßÜ[37mÛÛ[35mßÜ[37mÛ[35mÜß[47mÜ[40mßÜ[47mß[37;40mÛ[35mßÜßÜ[47mß[37;40mß
@ECHO [7CÛ[35mÜß[37mÜ[35;47mß[40mÜß[37mÛ[35mßÜ[37mÛ[35;47mÜ[40mßÜ[47mß[37;40mß[35;47mß[40mÜ[37mÛ[35;47mÜ[40mß[37mÜß[47mÛ[35;40mßÜ[37mÛÛÜÛ[35mßÜ[37mÛÜ[35mßÜß[37mÛ  Û[35mÜß[37mÛ Û[35mßÜ[37mÛÛ[35mßÜ[37mÛ[35mÜß[37mÜ[35mß[47mÜ[37;40mÜÛ[35mßÜ[37mÛÛÜ
@ECHO [7CÛ[35mÜß[37mÛ[47m [35;40mÜß[37mÛ[35mßÜßÜ[47mß[37;40mß  ßÜ[35mßÜ[47mß[37;40mß [47mÛ[35;40mßÜßÜß[37mÛ[35mßÜ[37mÛß[35;47mß[40mÜß[37mÛ  Û[35mÜß[37mÛ ß[35;47mß[40mÜßÜß[37mÜÛ[35mÜß[37mÛ[35;47mß[40mÜß[37mÛ[35mßÜßÜß[37mÛ
@ECHO [8Cßß  ßß ßßßß[6Cßß    ßßßßß ßß   ßß    ßß    ßßßß  ßß  ßß ßßßßß
@ECHO [26C[1;36m(c) 1991 by Apogee Software
@ECHO [23C[1;35mWhich volume do you wish to play?
@ECHO [0;35;40m        ÜÜÜÜÜÜ
@ECHO [0;35;40m     ßßß[00;35;47mß[00;35;40mß[00;35;47mßß[00;35;40mß[00;35;47mß[00;35;40mßßß                 [0;36;40m1) Volume 1                   [00;37;40mÜÜÛÛ[00;35;47mÜ[00;36;47mÜ[00;37;40mÛÛÜÜ
@ECHO [37;40m        ßÛßßÛß                    [0;36;40m1) Volume 2                  [00;37;40mßß   [00;35;47mÛ[00;36;47mÛ[00;37;40m   ßß
@ECHO [35;40m         Ü[00;35;47mÜÜ[00;35;40mÜ                     [0;36;40m2) Volume 3                       [00;35;47mÛ[00;36;47mÛ
@ECHO [37;40m      ÜÛß[00;35;40mÛÛÛÛ[00;37;40mßÛÜ                  [0;36;40m4) Volume 4                       [00;35;47mÛ[00;36;47mÛ
@ECHO [37;40m      Û  [00;35;46mß[00;35;40mÛÛ[00;35;46mß[00;37;40m  Û                                                    [00;35;47mÛ[00;36;47mÛ
@ECHO [36;40m        ÛÛ  ÛÛ                    [0;36;40m5) Hint Sheet                     [00;35;47mÛ[00;36;47mÛ
@ECHO [36;40m       ßßß  ßßß                   [1;35;40m6) [1;36;40mQuit
@ECHO [0;30;40mÿ[00;37;40m                                                    ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ[00;37;40m[1A[s
GOTO HINTCHECK

:HINTCHECK
IF EXIST AA-HINT.EXE GOTO HINTENABLE
IF EXIST AAHINT.EXE GOTO HINTENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP4CHECK

:EP4CHECK
IF EXIST AA4.EXE GOTO EP4ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP3CHECK

:EP3CHECK
IF EXIST AA3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP2CHECK

:EP2CHECK
IF EXIST AA2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP1CHECK

:EP1CHECK
IF EXIST AA1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO CHOICES

:HINTENABLE
SET CHOICES=%CHOICES%5
@ECHO [23;35H[01;35;40m5) [1;36;40mHint Sheet[00;37;40m[u
GOTO EP4CHECK

:EP4ENABLE
SET CHOICES=%CHOICES%4
@ECHO [21;35H[01;35;40m4) [1;36;40mVolume 4[00;37;40m[u
GOTO EP3CHECK

:EP3ENABLE
SET CHOICES=%CHOICES%3
@ECHO [20;35H[01;35;40m3) [1;36;40mVolume 3[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [19;35H[01;35;40m2) [1;36;40mVolume 2[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [18;35H[01;35;40m1) [1;36;40mVolume 1[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 6 GOTO AA1
IF ERRORLEVEL 5 GOTO AA2
IF ERRORLEVEL 4 GOTO AA3
IF ERRORLEVEL 3 GOTO AA4
IF ERRORLEVEL 2 GOTO HINTSHEET
IF ERRORLEVEL 1 GOTO EXIT

:HINTSHEET
CLS
IF EXIST AA-HINT.EXE AA-HINT %1 %2 %3 %4 %5 %6 %7 %8 %9
IF EXIST AAHINT.EXE AAHINT %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:AA1
CLS
AA1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:AA2
CLS
AA2 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:AA3
CLS
AA3 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:AA4
CLS
AA4 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
