@ECHO OFF

:START
SET CHOICES=E
CLS
@ECHO [01;36;40m浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様融[1A
@ECHO � [00;32;40m臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼 [01;36;40m�[1A
@ECHO � [00;32;40m臼臼臼臼臼臼臼[00;30;47m                                                [00;32;40m臼臼臼臼臼臼臼 [01;36;40m�[1A
@ECHO � [00;32;40m臼臼臼臼臼臼臼[00;30;47m     Apogee Software Productions Presents       [00;32;40m葦臼臼臼臼臼臼 [01;36;40m�[1A
@ECHO � [00;32;40m臼臼臼臼臼臼臼[00;30;47m                                                [00;32;40m葦臼臼臼臼臼臼 [01;36;40m�[1A
@ECHO � [00;32;40m臼臼臼臼臼臼臼[01;37;47m                   Paganitzu                    [00;32;40m葦臼臼臼臼臼臼 [01;36;40m�[1A
@ECHO � [00;32;40m臼臼臼臼臼臼臼[01;37;47m               Episode Selection                [00;32;40m葦臼臼臼臼臼臼 [01;36;40m�[1A
@ECHO � [00;32;40m臼臼臼臼臼臼臼[01;37;47m                                                [00;32;40m葦臼臼臼臼臼臼 [01;36;40m�[1A
@ECHO � [00;32;40m臼臼臼臼臼臼臼[00;30;47m    Design and Programming by Keith Schuler     [00;32;40m葦臼臼臼臼臼臼 [01;36;40m�[1A
@ECHO � [00;32;40m臼臼臼臼臼臼臼[00;30;47m        Copyright (c) 1991 by Trilobyte         [00;32;40m葦臼臼臼臼臼臼 [01;36;40m�[1A
@ECHO � [00;32;40m臼臼臼臼臼臼臼[00;30;47m                                                [00;32;40m葦臼臼臼臼臼臼 [01;36;40m�[1A
@ECHO � [00;32;40m臼臼臼臼臼臼臼[00;33;47m               Press 'E' to Exit                [00;32;40m葦臼臼臼臼臼臼 [01;36;40m�[1A
@ECHO � [00;32;40m臼臼臼臼臼臼臼[01;37;47m                                                [00;32;40m葦臼臼臼臼臼臼 [01;36;40m�[1A
@ECHO � [00;32;40m臼臼臼臼臼臼臼臼旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭旭葦臼臼臼臼臼臼 [01;36;40m�[1A
@ECHO � [00;32;40m臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼 [01;36;40m�[1A
@ECHO � [00;32;40m臼�[01;36;40m浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様融[00;32;40m臼� [01;36;40m�[1A
@ECHO � [00;32;40m臼�[01;36;40m�[01;31;40m                    Please select an episode...                     [01;36;40m�[00;32;40m臼� [01;36;40m�[1A
@ECHO � [00;32;40m臼�[01;36;40m�[01;31;40m                                                                    [01;36;40m�[00;32;40m臼� [01;36;40m�[1A
@ECHO � [00;32;40m臼�[01;36;40m�[00;33;40m                   1) Romancing the Rose                            [01;36;40m�[00;32;40m臼� [01;36;40m�[1A
@ECHO � [00;32;40m臼�[01;36;40m�[00;33;40m                   2) Quest for the Silver Dagger                   [01;36;40m�[00;32;40m臼� [01;36;40m�[1A
@ECHO � [00;32;40m臼�[01;36;40m�[00;33;40m                   3) Jewel of the Yucatan                          [01;36;40m�[00;32;40m臼� [01;36;40m�[1A
@ECHO � [00;32;40m臼�[01;36;40m藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕[00;32;40m臼� [01;36;40m�[1A
@ECHO � [00;32;40m臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼臼 [01;36;40m�[1A
@ECHO 藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕[00;37;40m[1A
@ECHO [00;30;40m�[00;37;40m������������������������������������������������������������������������������[00;37;40m[1A[s
GOTO EP3CHECK

:EP3CHECK
IF EXIST PAGA3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%�
GOTO EP2CHECK

:EP2CHECK
IF EXIST PAGA2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%�
GOTO EP1CHECK

:EP1CHECK
IF EXIST PAGA1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%�
GOTO CHOICES

:EP3ENABLE
SET CHOICES=%CHOICES%3
@ECHO [21;26H[01;33;40m3) Jewel of the Yucatan[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [20;26H[01;33;40m2) Quest for the Silver Dagger[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [19;26H[01;33;40m1) Romancing the Rose[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 4 GOTO PAGA1
IF ERRORLEVEL 3 GOTO PAGA2
IF ERRORLEVEL 2 GOTO PAGA3
IF ERRORLEVEL 1 GOTO EXIT

:PAGA1
CLS
PAGA1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:PAGA2
CLS
PAGA2 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:PAGA3
CLS
PAGA3 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
