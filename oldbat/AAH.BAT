@ECHO OFF

:START
SET CHOICES=6
CLS
@ECHO [24C��    ���[5C��[5C����� �    ��
@ECHO [22C�[35;47m�[40m��[37m����[35m���[37m�� �[35;47m�[40m��[37m���[35;47m�[37;40m�[35m����[37m�[35;47m�[40m�[37m� �[35;47m�[40m��[37m��
@ECHO [21C�[35m�[37m��[35m��[37m�[35m��[37m��[35m��[37m��[35m��[47m�[37;40m�[35;47m�[37;40m�[35;47m�[37;40m�[35;47m�[40m��[37m���[35m��[37m��[35m��[47m�[37;40m�[35;47m�[37;40m�
@ECHO [20C�[35m��[47m�[37;40m�[35m��[37m�[35m��[47m�[40m��[47m�[37;40m�[35m��[37m��[5C�[35m��[37m� �[35m��[37m�[35m��[37m��
@ECHO [20C�[35m��[37m�[35;47m�[40m��[37m�[35m��[37m�[35m�[47m�[37;40m��[35m��[47m�[37;40m�[35;47m�[37;40m��  �[35m��[37m� �[35m��[37m�[35m��[47m�[37;40m�[35;47m�[37;40m��
@ECHO [20C�[35m��[37m��[35m��[37m�[35m��[37m�[35;47m�[40m��[37m��[35m����[47m�[37;40m�  �[35m��[37m� �[35m��[37m��[35m����[47m�[37;40m�
@ECHO [21C��  �� ��  ��  ����[5C��   ��  ����
@ECHO [11C��   ����   ��   ��  ����� �   ��    ����� �   �   ���   �����
@ECHO [9C�[35;47m�[40m��[37m���[35m����[47m�[37;40m��[35m��[37m� �[35m��[37m��[35m����[37m��[35m�[37m���[35m��[37m��[35;47m�[37;40m�[35m����[37m��[35m�[37m���[35m�[37m���[35m���[37m���[35m����[37m��
@ECHO [8C�[35m�[37m�[47m [35;40m��[37m�[35m��[47m�[37;40m�[35;47m�[40m��[37m�[35m��[37m� �[35m��[37m�[35m��[47m�[37;40m���[35m���[47m�[37;40m�[35m��[37m�[35;47m�[37;40m�[35;47m�[40m��[37m���[35m��[37m��[35m��[37m�[35m��[37m��[35m��[37m�[35m��[47m�[37;40m��
@ECHO [7C�[35m��[47m�[37;40m�[35m��[37m�[35m��[37m� �[35;47m�[40m�[37m�[35m��[37m� �[35m�[47m�[37m�[35;40m����[47m�[37;40m�[35m��[47m�[40m�[37m�[35m��[37m�  �[35m��[37m� �[35m��[37m��[35m��[37m�[35m��[47m�[40m��[47m�[37;40m�[35m����[47m�[37;40m�
@ECHO [7C�[35m��[37m�[35;47m�[40m��[37m�[35m��[37m�[35;47m�[40m��[47m�[37;40m�[35;47m�[40m�[37m�[35;47m�[40m�[37m��[47m�[35;40m��[37m����[35m��[37m��[35m���[37m�  �[35m��[37m� �[35m��[37m��[35m��[37m�[35m��[37m�[35m�[47m�[37;40m��[35m��[37m���
@ECHO [7C�[35m��[37m�[47m [35;40m��[37m�[35m����[47m�[37;40m�  ��[35m��[47m�[37;40m� [47m�[35;40m�����[37m�[35m��[37m��[35;47m�[40m��[37m�  �[35m��[37m� �[35;47m�[40m����[37m��[35m��[37m�[35;47m�[40m��[37m�[35m�����[37m�
@ECHO [8C��  �� ����[6C��    ����� ��   ��    ��    ����  ��  �� �����
@ECHO [26C[1;36m(c) 1991 by Apogee Software
@ECHO [23C[1;35mWhich volume do you wish to play?
@ECHO [0;35;40m        ������
@ECHO [0;35;40m     ���[00;35;47m�[00;35;40m�[00;35;47m��[00;35;40m�[00;35;47m�[00;35;40m���                 [0;36;40m1) Volume 1                   [00;37;40m����[00;35;47m�[00;36;47m�[00;37;40m����
@ECHO [37;40m        ������                    [0;36;40m1) Volume 2                  [00;37;40m��   [00;35;47m�[00;36;47m�[00;37;40m   ��
@ECHO [35;40m         �[00;35;47m��[00;35;40m�                     [0;36;40m2) Volume 3                       [00;35;47m�[00;36;47m�
@ECHO [37;40m      ���[00;35;40m����[00;37;40m���                  [0;36;40m4) Volume 4                       [00;35;47m�[00;36;47m�
@ECHO [37;40m      �  [00;35;46m�[00;35;40m��[00;35;46m�[00;37;40m  �                                                    [00;35;47m�[00;36;47m�
@ECHO [36;40m        ��  ��                    [0;36;40m5) Hint Sheet                     [00;35;47m�[00;36;47m�
@ECHO [36;40m       ���  ���                   [1;35;40m6) [1;36;40mQuit
@ECHO [0;30;40m�[00;37;40m                                                    �������������������������[00;37;40m[1A[s
GOTO HINTCHECK

:HINTCHECK
IF EXIST AA-HINT.EXE GOTO HINTENABLE
IF EXIST AAHINT.EXE GOTO HINTENABLE
SET CHOICES=%CHOICES%�
GOTO EP4CHECK

:EP4CHECK
IF EXIST AA4.EXE GOTO EP4ENABLE
SET CHOICES=%CHOICES%�
GOTO EP3CHECK

:EP3CHECK
IF EXIST AA3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%�
GOTO EP2CHECK

:EP2CHECK
IF EXIST AA2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%�
GOTO EP1CHECK

:EP1CHECK
IF EXIST AA1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%�
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
