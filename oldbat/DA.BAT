@ECHO OFF

:START
SET CHOICES=4
CLS
@ECHO.
@ECHO [8C[0;1;33mßÜ[25CÜß[43mß[0;33mÜ
@ECHO   [1mÜÜÜÛÛÛÛÛÛÛÜ[21CÛ[0;33mÜß[15C[1mÛ[0;33mÜ
@ECHO  [1mÛ[43mß[0;33mÛßßßß[1mÛ[0;33mÛßßß[1mßÛÜ[18CÛ[0;33mÛ[15C[1mÛ[0;33mÜ[1mÛ[0;33mÜ
@ECHO   ß[5C[1mÛ[0;33mÛ[5Cß[1mÛ[0;33mÜ  [1mÜÜÜ[7CÜÜ  Û[0;33mÛ[1mÜÛ[43mß[0;33mÜ[9C[1mÜÛ[0;33mÜß[1mÛ[43mÜ[6C[40mÜÜ    ÜÜÜ[5CÜÜ
@ECHO [8CÛ[0;33mÛ[6C[1mÛ[0;33mÛ [1mÛ[0;33mÜßß[1mÛ[0;33mÜ  [1mßÜß[0;33mÜßß [1mÛÛ[0;33mÜßß[6C[1mßÜÜÛ[43mß[0;33mÛß  [1mÛ[0;33mÛ   [1mÜß[0;33mÜß[1mÛ[0;33mÜ [1mÛ[0;33mÜß[1;43mÜ[40mÛ[0;33mÜ  [1mÛÜ[0;33mß[1mß[0;33mÜ
@ECHO [8C[1mÛ[0;33mÛ[6C[1mÛ[0;33mÛ [1mÛ[0;33mÛ [1mÜÛ[43mÜ[3C[40mÛ[0;33mÛ    [1mÛ[0;33mÛ[1mÛ[0;33mÜ[1mÜ[7CÜÛ[43mßß[40mÜ   ÛÛ[0;33mÜ  [1mÛ[0;33mÛ [1mÜÛ[0;33mÛ [1mÛ[43mÜ[40mß[0;33mÜ[1;43mÜ[0;33mß [1mÜ ß[43mß[40mÜ
@ECHO    Ü   Û[43mß[0;33mÛ    [1mÜß[0;33mÜß  [1mß[43mß[0;33mÜ[1mß[0;33mÛß  [1mß[0;33mÛ    [1mß[0;33mÛ[1mß[43mß[0;33mÜß    [1mÜÛ[43mß[0;33mÛß  [1mßÜÜÛÛ[0;33mÛ  [1mß[43mÜ[40mß[0;33mÜ[1mÛ[0;33mÛ  [1mß[43mßß[0;33mÜß  [1mß[43mßß[0;33mÜß
@ECHO     [1mß[43mßß[40mÛÛÛÛÛÛ[43mß[0;33mÜß[29Cßß[6Cß[1mÛÛ[0;33mÛ  [1mÜ [0;33mß [1mÛ[0;33mÛ
@ECHO         ßßßßßß                  [01;36;40mby Todd Replogle       [1;33mß[43mß[0;33mÜ [1mß[43mÜ[40mÜß[0;33mÜß
@ECHO                       [01;32;40mCopyright 1991 (c) Scenario Software   [0;33mßß
@ECHO                     [01;37;40mPublished by Apogee Software Productions
@ECHO.
@ECHO                         [00;34;40mÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
@ECHO                         [01;34;44m Û[01;34;41mßßßßßßßßßßßßßßßßßßßßßßßßßßßß[01;34;44mÛ [00;37;40m
@ECHO                         [01;34;44m Û[01;32;41m      Volume Selection      [01;34;44mÛ [00;37;40m
@ECHO                         [01;34;44m Û[01;34;41m                            [01;34;44mÛ [00;37;40m
@ECHO                         [01;34;44m Û[01;31;41m 1) [01;31;41mPrince of Destiny       [01;34;44mÛ [00;37;40m
@ECHO                         [01;34;44m Û[01;31;41m 2) [01;31;41mThe Undead Kingdom      [01;34;44mÛ [00;37;40m
@ECHO                         [01;34;44m Û[01;31;41m 3) [01;31;41mDungeons of Doom        [01;34;44mÛ [00;37;40m
@ECHO                         [01;34;44m Û[01;34;41m                            [01;34;44mÛ [00;37;40m
@ECHO                         [01;34;44m Û[01;37;41m 4) [01;36;41mQuit                    [01;34;44mÛ [00;37;40m
@ECHO                         [01;34;44m Û[01;34;41mÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ[01;34;44mÛ [00;37;40m
@ECHO                         [00;34;40mßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
@ECHO [00;30;40mÿ[00;37;40mÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ[1A[s

:EP3CHECK
IF EXIST DA3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP2CHECK

:EP2CHECK
IF EXIST DA2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP1CHECK

:EP1CHECK
IF EXIST DA1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO CHOICES

:EP3ENABLE
SET CHOICES=%CHOICES%3
@ECHO [20;28H[01;37;41m3) [01;36;41mDungeons of Doom[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [19;28H[01;37;41m2) [01;36;41mThe Undead Kingdom[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [18;28H[01;37;41m1) [01;36;41mPrince of Destiny[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 4 GOTO DA1
IF ERRORLEVEL 3 GOTO DA2
IF ERRORLEVEL 2 GOTO DA3
IF ERRORLEVEL 1 GOTO EXIT

:DA1
CLS
DA1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:DA2
CLS
DA2 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:DA3
CLS
DA3 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
