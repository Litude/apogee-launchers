@ECHO OFF

:START
IF EXIST ROTT.ROT DEL ROTT.ROT
SET CHOICES=4
CLS
@ECHO.
@ECHO [00;34;40m        ��         [01;37;40m���Ŀ ڿ ���Ŀ ���Ŀ     ���Ŀ ���Ŀ    ����Ŀ ڿ  � ���Ŀ
@ECHO [00;34;40m       �[01;33;44m��[00;34;40m�        [01;37;40m����� ô ���¿ ���       ô  � ���        ô   ���Ĵ ���
@ECHO [00;34;40m      ��[01;33;40m��[00;34;40m��       [01;37;40m�� �  �� ����� �����     ����� ��         ��   ��  � �����
@ECHO [00;34;40m     ���[01;33;40m��[00;34;40m���                      [01;37;40m��������[01;30;40m� [01;37;40m�������[01;30;40m� [01;37;40m��[01;30;40m� [01;37;40m������[01;30;40m� [01;37;40m������[01;30;40m�
@ECHO [00;34;40m    ����[01;33;44m��[00;34;40m����                     [01;37;40m�[01;30;47m��������[01;37;40m �[01;30;47m�������[01;37;40m �[01;30;47m �[01;37;40m �[01;30;47m������[01;37;40m �[01;30;47m������
@ECHO [00;34;40m   ������������                       [01;37;40m��[01;30;40m�    [01;37;40m�������[01;30;40m� [01;37;47m� [01;30;40m� [01;37;40m������[01;30;40m� [01;37;40m��[01;30;40m�  [01;37;40m��[01;30;40m�
@ECHO [00;34;40m  ���[01;33;44m���[00;34;40m��[01;33;44m���[00;34;40m���                      [01;37;40m�[00;37;40m�[01;30;40m�    [01;37;40m�[01;30;47m ��� ��[01;37;40m �[00;37;40m�[01;30;40m� [01;37;40m�[00;37;40m�[01;30;47m��� �[01;37;40m �[00;37;40m�[01;30;40m�  [01;37;40m�[00;37;40m�[01;30;40m�
@ECHO [00;34;40m �[01;33;44m����� [00;34;40m��[01;33;44m �����[00;34;40m�  [01;37;40m                   [01;37;40m�[00;37;40m�[01;30;40m�    [01;37;40m�[00;37;40m�[01;30;40m� [01;37;40m�[00;37;40m�[01;30;40m�  [01;37;40m�[00;37;40m�[01;30;40m� [01;37;40m�[00;37;40m�[01;30;40m� [01;37;40m�[00;37;40m�[01;30;40m� [01;37;40m�[00;37;40m�[01;30;40m�  [01;37;40m�[00;37;40m�[01;30;40m�
@ECHO [00;34;40m������������������                    [01;37;40m�[00;37;40m�[01;30;40m�    [01;37;40m�[00;37;40m�[01;30;40m� [01;37;40m�[00;37;47m�[01;37;47m�[01;30;40m� [01;37;40m�[00;37;40m�[01;30;40m� [01;37;40m�[00;37;40m�[01;30;40m� [01;37;40m�[00;37;40m�[01;30;40m� [01;37;40m�[00;37;40m�[01;37;47m���� [01;30;40m� (tm)
@ECHO [00;34;40m                                      [01;30;40m���    ��� ���� ��� ��� ��� ��������
@ECHO [01;36;40m                    Copyright (c) 1995 Apogee Software, Ltd.
@ECHO.
@ECHO [01;34;40m��������������������������������������������������������������������������������[1A
@ECHO [01;37;40m                            ����������������������Ŀ
@ECHO [01;37;40m                            �MISSION SELECTION MENU�
@ECHO [01;37;40m                            ������������������������
@ECHO [01;31;40m                   Pick a number to choose the desired mission
@ECHO.
@ECHO [00;36;40m                          1. The HUNT Begins
@ECHO [00;36;40m                          2. Dark War
@ECHO [00;36;40m                          3. Extreme Rise of the Triad
@ECHO.
@ECHO [01;36;40m                          4. Quit
@ECHO [00;30;40m�[00;37;40m������������������������������������������������������������������������������[00;37;40m[1A[s
GOTO EXTRCHECK

:EXTRCHECK
IF EXIST EXTREME.RTL GOTO EXTRENABLE
SET CHOICES=%CHOICES%�
GOTO DARKCHECK

:DARKCHECK
IF EXIST DARKWAR.WAD GOTO DARKENABLE
SET CHOICES=%CHOICES%�
GOTO HUNTCHECK

:HUNTCHECK
IF EXIST HUNTBGIN.WAD GOTO HUNTENABLE
SET CHOICES=%CHOICES%�
GOTO CHOICES

:EXTRENABLE
SET CHOICES=%CHOICES%3
@ECHO [22;27H[01;36;40m3. Extreme Rise of the Triad[00;37;40m[u
GOTO DARKCHECK

:DARKENABLE
SET CHOICES=%CHOICES%2
@ECHO [21;27H[01;36;40m2. Dark War[00;37;40m[u
GOTO HUNTCHECK

:HUNTENABLE
SET CHOICES=%CHOICES%1
@ECHO [20;27H[01;36;40m1. The HUNT Begins[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 4 GOTO HUNT
IF ERRORLEVEL 3 GOTO DARK
IF ERRORLEVEL 2 GOTO EXTR
IF ERRORLEVEL 1 GOTO EXIT

:HUNT
CLS
@ECHO PHONENUMBER          ~>ROTT.ROT
@ECHO REMOTESOUNDFILE      ~>>ROTT.ROT
@ECHO GAMELEVELFILE        HUNTBGIN.RTL>>ROTT.ROT
@ECHO COMMBATLEVELFILE     HUNTBGIN.RTC>>ROTT.ROT
ROTT %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:DARK
CLS
ROTT %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXTR
CLS
@ECHO PHONENUMBER          ~>ROTT.ROT
@ECHO REMOTESOUNDFILE      ~>>ROTT.ROT
@ECHO GAMELEVELFILE        EXTREME.RTL>>ROTT.ROT
@ECHO COMMBATLEVELFILE     ~>>ROTT.ROT
ROTT %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS