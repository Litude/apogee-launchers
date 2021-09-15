@ECHO OFF

:START
SET CHOICES=Q
CLS
@ECHO.
@ECHO [01;37;40m                               THE KROZ TRILOGY
@ECHO.
@ECHO [00;33;40m                Copyright (c) 1990 Apogee Software Productions
@ECHO.
@ECHO [00;33;40m                                by Scott Miller
@ECHO.
@ECHO [00;32;40m                     PLEASE SELECT A VOLUME FROM BELOW...
@ECHO.
@ECHO [00;31;40mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
@ECHO.
@ECHO.
@ECHO                            [01;36;40mCaverns of Kroz II
@ECHO.
@ECHO                            [01;36;40mDungeons of Kroz II
@ECHO.
@ECHO                            [01;36;40mKingdom of Kroz II
@ECHO.
@ECHO                            [01;33;40mQ[01;36;40muit
@ECHO.
@ECHO.
@ECHO.
@ECHO.
@ECHO [00;30;40mÿ[00;37;40mÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ[00;37;40m[1A[s
GOTO EP3CHECK

:EP3CHECK
IF EXIST KINGDOM.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP2CHECK

:EP2CHECK
IF EXIST DUNGEONS.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP1CHECK

:EP1CHECK
IF EXIST CAVERNS.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO PRNTCHOC

:EP3ENABLE
SET CHOICES=%CHOICES%K
@ECHO [18;28H[01;33;40mK[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%D
@ECHO [16;28H[01;33;40mD[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%C
@ECHO [14;28H[01;33;40mC[00;37;40m[u
GOTO PRNTCHOC

:PRNTCHOC
IF %CHOICES% == QKDC ECHO [23;28H[01;37;44mYour choice (C/D/K/Q)? [05mÛ[00m[u
IF %CHOICES% == QÿDC ECHO [23;28H [01;37;44mYour choice (C/D/Q)? [05mÛ[00m [u
IF %CHOICES% == QKÿC ECHO [23;28H [01;37;44mYour choice (C/K/Q)? [05mÛ[00m [u
IF %CHOICES% == QKDÿ ECHO [23;28H [01;37;44mYour choice (D/K/Q)? [05mÛ[00m [u
IF %CHOICES% == QÿÿC ECHO [23;28H  [01;37;44mYour choice (C/Q)? [05mÛ[00m  [u
IF %CHOICES% == QÿDÿ ECHO [23;28H  [01;37;44mYour choice (D/Q)? [05mÛ[00m  [u
IF %CHOICES% == QKÿÿ ECHO [23;28H  [01;37;44mYour choice (K/Q)? [05mÛ[00m  [u
IF %CHOICES% == Qÿÿÿ ECHO [23;28H   [01;37;44mYour choice (Q)? [05mÛ[00m   [u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 4 GOTO CAVERNS
IF ERRORLEVEL 3 GOTO DUNGEONS
IF ERRORLEVEL 2 GOTO KINGDOM
IF ERRORLEVEL 1 GOTO EXIT

:CAVERNS
CLS
CAVERNS %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:DUNGEONS
CLS
DUNGEONS %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:KINGDOM
CLS
KINGDOM %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
