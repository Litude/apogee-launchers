@ECHO OFF

:START
CLS
SET CHOICES=
@ECHO.
@ECHO [7C[0;1;31m�[0;33m� ��� [1;31m�[0;33m����  [1;31m�[0;33m�[5C[1;31m�[0;33m�[5C[1;31m�[0;33m����  [1;31m�[0;33m�    ��� [1;31m�[0;33m����  [1;31m�[0;33m����  [1;31m�[0;33m����
@ECHO [7C������ ��� �� ��[5C��[5C�� ��� �� �� ��� ����   ����   �� ���
@ECHO [7C[1;30;43m��[1C[0;33m��[1;30;43m�[1C��[0;33m�߲[1;30;43m�[1C��[1C[0;33m��[1;30;43m�[1C��[1C[0;33m��[1;30;43m�[1C��[1C���[1C��[1C��[1C���[1C��[1C[0;33m��[1;30;43m�[1C��[1C[0;33m��[1;30;43m�[1C��[1C���[40m
@ECHO [7C[43m��[1C���[1C��[1C���[1C��[1C���[1C��[1C���[1C��[1C���[1C��[1C��[1C���[1C��[1C���[1C��[1C���[1C��[1C���[40m
@ECHO [7C[43m��[1C���[1C��[1C���[1C������[1C������[1C[40m�[43m����[40m� [43m���������[1C������[1C������[1C��[1C���[40m
@ECHO [23C[37m�[0m� ��� [1m�[0m����  [1m�[0m���� [1m�[0m���� [1m�[0m� ���
@ECHO [23C������ ��� �� �� [1;30;47m�[0m� �� [1;30;47m�[0m� ������
@ECHO [23C[1;30;47m��[1C[0m��[1;30;47m�[1C��[0m�߲[1;30;47m�[1C��[4C��[4C[40m�� [0m��[1;30;47m�[40m
@ECHO [23C[47m��[1C���[1C��[1C���[1C��[4C��[4C��[1C���[40m
@ECHO [23C[47m��[1C���[1C��[1C���[1C��[4C��[4C������[40m
@ECHO.
@ECHO          [0;1;33mDeveloped by Interactive Binary Illusions and SubZero Software
@ECHO                       [0;1;31mCopyright (c) 1993 Apogee Software[0;36m
@ECHO.
@ECHO.
@ECHO                                 Play the Game
@ECHO                                 Music Studio
@ECHO.
@ECHO                               Technical Support
@ECHO                                  Hint Sheet
@ECHO.
@ECHO                                     [1;34mQ[36muit
@ECHO [0;30m                                                                               �[00;37;40m[2A[s
:CHECKBETA

:CHECKBETA
IF EXIST START.EXE GOTO ENABLEBETA
GOTO CHECKGAME

:CHECKGAME
IF EXIST HARRY.EXE GOTO ENABLEGAME
IF EXIST HH1.EXE GOTO ENABLEGAME
SET CHOICES=��%CHOICES%
GOTO CHECKSTUDIO

:CHECKSTUDIO
IF EXIST STUDIO.EXE GOTO ENABLESTUDIO
SET CHOICES=�%CHOICES%
GOTO CHECKHELP

:CHECKHELP
IF EXIST HH-HELP.EXE GOTO ENABLEHELP
IF EXIST HHHELP.EXE GOTO ENABLEHELP
SET CHOICES=�%CHOICES%
GOTO CHECKHINT

:CHECKHINT
IF EXIST HH-HINT.EXE GOTO ENABLEHINT
IF EXIST HHHINT.EXE GOTO ENABLEHINT
SET CHOICES=�%CHOICES%
GOTO CHOICES

:ENABLEGAME
SET CHOICES=�P%CHOICES%
@ECHO [17;33H[1;34mP[36mlay the Game[00;37;40m[u
GOTO CHECKSTUDIO

:ENABLESTUDIO
SET CHOICES=M%CHOICES%
@ECHO [18;33H[1;34mM[36music Studio[00;37;40m[u
GOTO CHECKHELP

:ENABLEHELP
SET CHOICES=T%CHOICES%
@ECHO [20;31H[1;34mT[36mechnical Support[00;37;40m[u
GOTO CHECKHINT

:ENABLEHINT
SET CHOICES=H%CHOICES%
@ECHO [21;34H[1;34mH[36mint Sheet[00;37;40m[u
GOTO CHOICES

:ENABLEBETA
@ECHO [16;23H[1;5;35mBETA VERSION -- DO NOT DISTRIBUTE![00;37;40m[u
@ECHO [17;33H[1;34m             [00;37;40m[u
@ECHO [18;33H[1;34mP[36mlay the Game[00;37;40m[u
@ECHO [20;31H[1;34m      S[36metup      [00;37;40m[u
@ECHO [21;33H[1;34mM[36music Studio[00;37;40m[u
SET CHOICES=��MSP
GOTO CHOICES

:CHOICES
@CHOICE /N /CQ%CHOICES% >> NUL
IF ERRORLEVEL 6 GOTO GAME
IF ERRORLEVEL 5 GOTO SETUP
IF ERRORLEVEL 4 GOTO STUDIO
IF ERRORLEVEL 3 GOTO HELPSHEET
IF ERRORLEVEL 2 GOTO HINTSHEET
IF ERRORLEVEL 1 GOTO EXIT

:GAME
IF EXIST START.EXE GOTO GAMEBETA
IF EXIST HH1.EXE GOTO GAMESHAREWARE
HARRY %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:GAMESHAREWARE
HH1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:GAMEBETA
CLS
IF NOT EXIST HARRY.CFG CONFIG
START %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:SETUP
CLS
CONFIG %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:STUDIO
STUDIO %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:HELPSHEET
IF EXIST HH-HELP.EXE HH-HELP.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
IF EXIST HHHELP.EXE HHHELP.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:HINTSHEET
IF EXIST HH-HINT.EXE HH-HINT.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
IF EXIST HHHINT.EXE HHHINT.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
SET CHOICES=
CLS

:TERM
