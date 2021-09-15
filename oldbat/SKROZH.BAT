@ECHO OFF

:START
SET CHOICES=Q
CLS
@ECHO.
@ECHO [01;37;40m                            THE SUPER KROZ TRILOGY
@ECHO.
@ECHO [00;33;40m                Copyright (c) 1990 Apogee Software Productions
@ECHO.
@ECHO [00;33;40m                                by Scott Miller
@ECHO.
@ECHO [00;32;40m                     PLEASE SELECT A VOLUME FROM BELOW...
@ECHO.
@ECHO [00;31;40mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
@ECHO                            [01;36;40mReturn to Kroz
@ECHO.
@ECHO                            [01;36;40mTemple of Kroz
@ECHO.
@ECHO                            [01;36;40mThe Final Crusade of Kroz
@ECHO.
@ECHO.
@ECHO.
@ECHO.
@ECHO                            [01;33;40mQ[01;36;40muit
@ECHO.
@ECHO.
@ECHO.
@ECHO [00;30;40mÿ[00;37;40mÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ[00;37;40m[1A[s
GOTO COSMETICS

:COSMETICS
IF EXIST CASTLE.EXE GOTO COSSOFT
IF EXIST SHRINE.EXE GOTO COSSHRN
GOTO HINTCHECK

:COSSHRN
@ECHO [12;28H[01;36;40mShrine of Kroz[00;37;40m[u
GOTO HINTCHECK

:COSSOFT
@ECHO [02;29H[01;37;40m    CASTLE OF KROZ    [00;37;40m[u
@ECHO [06;27H[00;33;40mPublished by Softdisk, Inc.[00;37;40m[u
@ECHO [08;22H[00;32;40m     PLEASE MAKE A SELECTION...     [00;37;40m[u
@ECHO [12;28H[01;36;40m                         [00;37;40m[u
@ECHO [14;28H[01;33;40mC[01;36;40mastle of Kroz[00;37;40m[u
@ECHO [16;28H[01;33;40mQ[01;36;40muit                     [00;37;40m[u
@ECHO [21;28H[01;36;40m    [00;37;40m[u
@ECHO [23;28H  [01;37;44mYour choice (C/Q)? [05mÛ[00m  [u
SET CHOICES=QÿÿÿC
GOTO CHOICES

:HINTCHECK
IF EXIST KROZHINT.EXE GOTO HINTENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP3CHECK

:EP3CHECK
IF EXIST CRUSADE.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP2CHECK

:EP2CHECK
IF EXIST TEMPLE.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP1CHECK

:EP1CHECK
IF EXIST SHRINE.EXE GOTO SHRNENABLE
IF EXIST CASTLE.EXE GOTO SOFTENABLE
IF EXIST RETURN.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO PRNTCHOC

:HINTENABLE
SET CHOICES=%CHOICES%H
@ECHO [19;28H[01;33;40mH[01;36;40mint Sheet[00;37;40m[u
GOTO EP3CHECK

:EP3ENABLE
SET CHOICES=%CHOICES%F
@ECHO [16;32H[01;33;40mF[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%T
@ECHO [14;28H[01;33;40mT[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%R
@ECHO [12;28H[01;33;40mR[00;37;40m[u
GOTO PRNTCHOC

:SHRNENABLE
SET CHOICES=%CHOICES%S
@ECHO [12;28H[01;33;40mS[00;37;40m[u
GOTO PRNTCHOC

:PRNTCHOC
IF %CHOICES% == QHFTR ECHO [23;27H[01;37;44mYour choice (R/T/F/H/Q)? [05mÛ[00m[u
IF %CHOICES% == QÿFTR ECHO [23;27H [01;37;44mYour choice (R/T/F/Q)? [05mÛ[00m [u
IF %CHOICES% == QHÿTR ECHO [23;27H [01;37;44mYour choice (R/T/H/Q)? [05mÛ[00m [u
IF %CHOICES% == QHFÿR ECHO [23;27H [01;37;44mYour choice (R/F/H/Q)? [05mÛ[00m [u
IF %CHOICES% == QHFTÿ ECHO [23;27H [01;37;44mYour choice (T/F/H/Q)? [05mÛ[00m [u
IF %CHOICES% == QÿÿTR ECHO [23;27H  [01;37;44mYour choice (R/T/Q)? [05mÛ[00m  [u
IF %CHOICES% == QÿFÿR ECHO [23;27H  [01;37;44mYour choice (R/F/Q)? [05mÛ[00m  [u
IF %CHOICES% == QÿFTÿ ECHO [23;27H  [01;37;44mYour choice (T/F/Q)? [05mÛ[00m  [u
IF %CHOICES% == QHÿÿR ECHO [23;27H  [01;37;44mYour choice (R/H/Q)? [05mÛ[00m  [u
IF %CHOICES% == QHÿTÿ ECHO [23;27H  [01;37;44mYour choice (T/H/Q)? [05mÛ[00m  [u
IF %CHOICES% == QHFÿÿ ECHO [23;27H  [01;37;44mYour choice (F/H/Q)? [05mÛ[00m  [u
IF %CHOICES% == QÿÿÿR ECHO [23;27H   [01;37;44mYour choice (R/Q)? [05mÛ[00m   [u
IF %CHOICES% == QÿÿTÿ ECHO [23;27H   [01;37;44mYour choice (T/Q)? [05mÛ[00m   [u
IF %CHOICES% == QÿFÿÿ ECHO [23;27H   [01;37;44mYour choice (F/Q)? [05mÛ[00m   [u
IF %CHOICES% == QHÿÿÿ ECHO [23;27H   [01;37;44mYour choice (H/Q)? [05mÛ[00m   [u
IF %CHOICES% == Qÿÿÿÿ ECHO [23;27H    [01;37;44mYour choice (Q)? [05mÛ[00m    [u

IF %CHOICES% == QHFTS ECHO [23;27H[01;37;44mYour choice (S/T/F/H/Q)? [05mÛ[00m[u
IF %CHOICES% == QÿFTS ECHO [23;27H [01;37;44mYour choice (S/T/F/Q)? [05mÛ[00m [u
IF %CHOICES% == QHÿTS ECHO [23;27H [01;37;44mYour choice (S/T/H/Q)? [05mÛ[00m [u
IF %CHOICES% == QHFÿS ECHO [23;27H [01;37;44mYour choice (S/F/H/Q)? [05mÛ[00m [u
IF %CHOICES% == QÿÿTS ECHO [23;27H  [01;37;44mYour choice (S/T/Q)? [05mÛ[00m  [u
IF %CHOICES% == QÿFÿS ECHO [23;27H  [01;37;44mYour choice (S/F/Q)? [05mÛ[00m  [u
IF %CHOICES% == QHÿÿS ECHO [23;27H  [01;37;44mYour choice (S/H/Q)? [05mÛ[00m  [u
IF %CHOICES% == QÿÿÿS ECHO [23;27H   [01;37;44mYour choice (S/Q)? [05mÛ[00m   [u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 5 GOTO RETURN
IF ERRORLEVEL 4 GOTO TEMPLE
IF ERRORLEVEL 3 GOTO CRUSADE
IF ERRORLEVEL 2 GOTO HINTSHEET
IF ERRORLEVEL 1 GOTO EXIT

:HINTSHEET
CLS
KROZHINT %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:RETURN
CLS
IF EXIST CASTLE.EXE GOTO CASTLE
IF EXIST SHRINE.EXE GOTO SHRINE
RETURN %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:TEMPLE
CLS
TEMPLE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:CRUSADE
CLS
CRUSADE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:CASTLE
CLS
CASTLE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:SHRINE
CLS
SHRINE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
