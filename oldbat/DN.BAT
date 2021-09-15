@ECHO OFF

:START
SET CHOICES=4
CLS
@ECHO.
@ECHO [00;33;40m                    ÜÜ  Ü Ü Ü Ü ÜÜÜ     Ü Ü Ü Ü Ü Ü ÜÜÜ Ü  Ü
@ECHO [00;33;40m                    Û Û Û Û Û/  ÛÜ      Û\Û Û Û Û/  ÛÜ  Û\/Û
@ECHO [00;33;40m                    ÛÜÛ ÛÜÛ Û Û ÛÜÜ     Û Û ÛÜÛ Û Û ÛÜÜ Û  Û
@ECHO.
@ECHO [01;37;40m                          Apogee Software Productions
@ECHO [00;37;40m                            A game by Todd Replogle
@ECHO [01;37;40m                               Copyright (c) 1991
@ECHO.
@ECHO.
@ECHO                 [00;34;40mÞ[01;37;44mÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»[00;34;40mÝ[01;37;40m
@ECHO                 [00;34;40mÞ[01;37;44mº[00;34;41mÝ[01;37;41m                                         [00;34;41mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                 [00;34;40mÞ[01;37;44mº[00;34;41mÝ[01;37;41m       DUKE EPISODE SELECTION MENU       [00;34;41mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                 [00;34;40mÞ[01;37;44mº[00;34;41mÝ[01;37;41m       ---------------------------       [00;34;41mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                 [00;34;40mÞ[01;37;44mº[00;34;41mÝ[01;37;41m                                         [00;34;41mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                 [00;34;40mÞ[01;37;44mº[00;34;41mÝ[01;31;41m 1) Shrapnel City                        [00;34;41mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                 [00;34;40mÞ[01;37;44mº[00;34;41mÝ[01;31;41m 2) Mission: Moonbase                    [00;34;41mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                 [00;34;40mÞ[01;37;44mº[00;34;41mÝ[01;31;41m 3) Trapped in the Future!               [00;34;41mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                 [00;34;40mÞ[01;37;44mº[00;34;41mÝ[01;37;41m                                         [00;34;41mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                 [00;34;40mÞ[01;37;44mº[00;34;41mÝ[01;37;41m 4) Quit                                 [00;34;41mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                 [00;34;40mÞ[01;37;44mº[00;34;41mÝ[01;37;41m                                         [00;34;41mÞ[01;37;44mº[00;34;40mÝ[01;37;40m
@ECHO                 [00;34;40mÞ[01;37;44mÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼[00;34;40mÝ[00;37;40m
@ECHO.
@ECHO.
@ECHO [00;30;40mÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ[00;37;40m[1A[s
GOTO COSMETICS

:COSMETICS
IF EXIST DN-HINT.EXE GOTO COSNUKUM
IF EXIST DNHINT.EXE GOTO COSNUKUM
IF EXIST DEALERS.EXE GOTO COSNUKUM
IF EXIST SWCBBS.EXE GOTO COSNUKUM
GOTO EP3CHECK

:COSNUKUM
@ECHO [02;53H[00;33;40mÜ Ü[00;37;40m[u
@ECHO [03;53H[00;33;40mÛ Û[00;37;40m[u
@ECHO [04;53H[00;33;40mÛÜÛ[00;37;40m[u
GOTO EP3CHECK

:EP3CHECK
IF EXIST DN3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP2CHECK

:EP2CHECK
IF EXIST DN2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP1CHECK

:EP1CHECK
IF EXIST DN1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO CHOICES

:EP3ENABLE
SET CHOICES=%CHOICES%3
@ECHO [18;21H[01;37;41m3) Trapped in the Future![00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [17;21H[01;37;41m2) Mission: Moonbase[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [16;21H[01;37;41m1) Shrapnel City[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 4 GOTO DN1
IF ERRORLEVEL 3 GOTO DN2
IF ERRORLEVEL 2 GOTO DN3
IF ERRORLEVEL 1 GOTO EXIT

:DN1
CLS
DN1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:DN2
CLS
DN2 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:DN3
CLS
DN3 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
