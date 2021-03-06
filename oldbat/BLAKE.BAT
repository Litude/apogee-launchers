@ECHO OFF

:START
CLS
@ECHO [1;32m
@ECHO    �����  ���         ���                   ���      �
@ECHO     ����   ��   ���    ��  ��    ���        �����   ��    ���  � ���     ���
@ECHO     �� ��  ��  �����   �����   ��� ��          ��� ����  �� ��  �� ��  ��� ��
@ECHO     �� ��  ��  �� ��   �����   ������           ��  ��   �� ��  �� ��  ������
@ECHO    ������ ���� ������ ��� ����  �����       �����   ���� ����� ��� ���  �����
@ECHO [33m
@ECHO                 �ķ � .                     ַ     �ķ     �   �
@ECHO                 �ĺ � � �ķ �ķ ���     �ķ �      � � �ķ � �Ķ
@ECHO                 � � � � ��� � � �Ľ     �Ľ �      �Ľ �Ľ � ��� [0;33m(tm)

IF EXIST MAPHEAD.BS6 GOTO REG6VERSION
IF EXIST MAPHEAD.BS3 GOTO REG3VERSION
IF EXIST SNDDATA.BS1 GOTO BETAVERSION
IF EXIST MAPHEAD.BS1 GOTO SWR1VERSION
ECHO.
GOTO MENUDRAW

:REG6VERSION
@ECHO [1;31m                            ** REGISTERED VERSION **
GOTO MENUDRAW
:REG3VERSION
@ECHO [1;31m                  ** REGISTERED VERSION - Episodes 1 thru 3 **
GOTO MENUDRAW
:BETAVERSION
@ECHO [1;31m                    ** BETA VERSION -- DO NOT DISTRIBUTE! **
GOTO MENUDRAW
:SWR1VERSION
@ECHO [1;31m                            ** SHAREWARE VERSION **
GOTO MENUDRAW

:MENUDRAW
@ECHO [37m
@ECHO                       [1;44m������������������������������������[0;40m
@ECHO                       [1;44m�   [0;37;44m1) Play                        [1;44m�[0;40m

IF EXIST SETBLAST.EXE GOTO SOUNDSETUP
:NOSOUNDSETUP
@ECHO                       [1;44m�                                  �[0;40m
@ECHO                       [1;44m�   [0;37;44m2) Technical Support           [1;44m�[0;40m
@ECHO                       [1;44m�   [0;37;44m3) Hint Sheet                  [1;44m�[0;40m
@ECHO                       [1;44m�                                  �[0;40m
@ECHO                       [1;44m�   [33m4) [37mQuit                        �[0;40m
@ECHO                       [1;44m������������������������������������[0;40m
@ECHO.
@ECHO [00;31m                          Developed by JAM Productions
@ECHO [01;35;40m                       Copyright (c) 1993 Apogee Software[00;37;40m
@ECHO [00;30;40m�[00;37;40m������������������������������������������������������������������������������[00;37;40m[1A[s
GOTO 4CHECK

:SOUNDSETUP
@ECHO                       [1;44m�   [33m2) [37mSound Setup                 �[0;40m
@ECHO                       [1;44m�                                  �[0;40m
@ECHO                       [1;44m�   [0;37;44m3) Technical Support           [1;44m�[0;40m
@ECHO                       [1;44m�   [0;37;44m4) Hint Sheet                  [1;44m�[0;40m
@ECHO                       [1;44m�                                  �[0;40m
@ECHO                       [1;44m�   [33m5) [37mQuit                        �[0;40m
@ECHO                       [1;44m������������������������������������[0;40m
@ECHO.
@ECHO [00;31m                          Developed by JAM Productions
@ECHO [01;35;40m                       Copyright (c) 1994 Apogee Software[00;37;40m
@ECHO [00;30;40m�[00;37;40m������������������������������������������������������������������������������[00;37;40m[1A[s
GOTO 5CHECK

:5CHECK
SET CHOICES=5
GOTO 5HINTCHECK

:5HINTCHECK
IF EXIST BS-HINT.EXE GOTO 5HINTENABLE
IF EXIST BSHINT.EXE GOTO 5HINTENABLE
SET CHOICES=%CHOICES%�
GOTO 5HELPCHECK

:5HELPCHECK
IF EXIST BS-HELP.EXE GOTO 5HELPENABLE
IF EXIST BSHELP.EXE GOTO 5HELPENABLE
SET CHOICES=%CHOICES%�
GOTO 5SETUPENABLE

:5GAMECHECK
IF EXIST BSTONE.BAT GOTO 5GAMEENABLE
SET CHOICES=%CHOICES%�
GOTO 5CHOICES

:5HINTENABLE
SET CHOICES=%CHOICES%4
@ECHO [18;27H[01;33;44m4) [37mHint Sheet[00;37;40m[u
GOTO 5HELPCHECK

:5HELPENABLE
SET CHOICES=%CHOICES%3
@ECHO [17;27H[01;33;44m3) [37mTechnical Support[00;37;40m[u
GOTO 5SETUPENABLE

:5SETUPENABLE
SET CHOICES=%CHOICES%2
GOTO 5GAMECHECK

:5GAMEENABLE
SET CHOICES=%CHOICES%1
@ECHO [14;27H[01;33;44m1) [37mPlay[00;37;40m[u
GOTO 5CHOICES

:5CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 5 GOTO GAME
IF ERRORLEVEL 4 GOTO SETUP
IF ERRORLEVEL 3 GOTO HELPSHEET
IF ERRORLEVEL 2 GOTO HINTSHEET
IF ERRORLEVEL 1 GOTO EXIT


:4CHECK
SET CHOICES=4
GOTO 4HINTCHECK

:4HINTCHECK
IF EXIST BS-HINT.EXE GOTO 4HINTENABLE
IF EXIST BSHINT.EXE GOTO 4HINTENABLE
SET CHOICES=%CHOICES%�
GOTO 4HELPCHECK

:4HELPCHECK
IF EXIST BS-HELP.EXE GOTO 4HELPENABLE
IF EXIST BSHELP.EXE GOTO 4HELPENABLE
SET CHOICES=%CHOICES%�
GOTO 4GAMECHECK

:4GAMECHECK
IF EXIST BSTONE.BAT GOTO 4GAMEENABLE
SET CHOICES=%CHOICES%�
GOTO 4CHOICES

:4HINTENABLE
SET CHOICES=%CHOICES%3
@ECHO [17;27H[01;33;44m3) [37mHint Sheet[00;37;40m[u
GOTO 4HELPCHECK

:4HELPENABLE
SET CHOICES=%CHOICES%2
@ECHO [16;27H[01;33;44m2) [37mTechnical Support[00;37;40m[u
GOTO 4GAMECHECK

:4GAMEENABLE
SET CHOICES=%CHOICES%1
@ECHO [14;27H[01;33;44m1) [37mPlay[00;37;40m[u
GOTO 4CHOICES

:4CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 4 GOTO GAME
IF ERRORLEVEL 3 GOTO HELPSHEET
IF ERRORLEVEL 2 GOTO HINTSHEET
IF ERRORLEVEL 1 GOTO EXIT

:GAME
CALL BSTONE.BAT %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:SETUP
SETBLAST.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:HELPSHEET
IF EXIST BS-HELP.EXE BS-HELP.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
IF EXIST BSHELP.EXE BSHELP.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:HINTSHEET
IF EXIST BS-HINT.EXE BS-HINT.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
IF EXIST BSHINT.EXE BSHINT.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
