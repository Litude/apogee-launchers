@ECHO OFF

:START
SET CHOICES=3
CLS
ECHO [?7h[40m[2J[40m[0;1m  [0;33m(tm)  [1m����   ���[5C�����[5C�����[5C���[5C���    ����    �����  ����
ECHO [6C������ ������  ��������  ��������  ������  ������  ������  ������ ������
ECHO [6C[37m��[5C��  ��  �� �� ��  �� �� ��  ��  ��  ��  ��  ��  ��  ��[5C��  ��
ECHO [5C[0;33m�[1;37;43m�[40m�    [0;33m�[1;37;43m�[40m� [0;33m�[1;37;43m�[40m� [0;33m�[1;37;43m�[40m�[0;33m�[1;37;43m�[40m�[0;33m�[1;37;43m�[40m� [0;33m�[1;37;43m�[40m�[0;33m�[1;37;43m�[40m�[0;33m�[1;37;43m�[40m� [0;33m�[1;37;43m�����[40m� [0;33m�[1;37;43m�[40m� [0;33m�[1;37;43m�[40m� [0;33m�[1;37;43m�[40m� [0;33m�[1;37;43m�[40m� [0;33m�[1;37;43m����[40m� [0;33m�[1;37;43m����[40m�
ECHO [5C[0;33m��[5C��  ��  �� �� ��  �� �� ��  ��  ��  ��  ��  ��  ��  ��[5C��  ��
ECHO [5C[1m����   ������ ��������� ��������� ��� ��� ��� ��� ������� �����  ��� ���
ECHO [6C���    ���   �� �� ��  �� �� ��  ��  ��  ��  ��  �����   �����  ��  ��
ECHO    ��  ��  �����  �����   ���[7C[37m"��Ŀ ��Ŀ ��Ŀ ���Ŀ �Ŀ  �  � ��Ŀ
ECHO   [33m��� ��� ������ ������ ������[7C[37m� Ŀ �  � �  �  �  � ���� ��Ĵ ��
ECHO   ��  ��  ��[5C��[5C��  ��[7C���� ���� ���� ����� ���� ���� ����
ECHO  [0;33m�[1;37;43m����[40m�  [0;33m�[1;37;43m����[40m� [0;33m�[1;37;43m����[40m� [0;33m�[1;37;43m�[40m� [0;33m�[1;37;43m�[40m�[10C��Ŀ ��Ŀ �    ��Ŀ ķ � �  �"
ECHO  [0;33m��  ��  ��[5C��[5C��  ��[11C[1;37m� Ŀ ��Ĵ �    ��Ĵ ���� ��Ĵ
ECHO [33m��� ��� �����  �����  ��� ���[11C[37m���� �  � ���� �  � � �� ����
ECHO [33m��  ��  �����  �����  ��  ��                     [16C[0;33m��������[1;36m
ECHO                                                       [9C[0;33m�[1;43m�[40m��������[43m�[0;33m�[1;36m
ECHO            [1;31mCopyright 1991 Id Software Inc.            [7C[0;33m�[1;43m�[40m����[42m�      �[43m�[0;33m�[1;36m
ECHO             [0;31mPublished by Apogee Software              [5C[0;33m�[1;43m�[42m�����  ����    �[43m�[0;33m�[1;36m
ECHO                                                       [5C[0;33m�[1m�[42m�����      ��  ��[0;33m�[1;36m
ECHO                 [1;33m-- SELECT AN EPISODE --               [8C[1;33m����[42m  ��  ��  ��[0;33m�[1;36m
ECHO                [0;35m1) Secret of the Oracle                [10C[1;33;42m�[40m�[42m  ����    ��[0;33m�[1;36m
ECHO                [0;35m2) The Armageddon Machine              [10C[1;33;42m���[30m���    [33m���[43m�[0;33m�[1;36m
ECHO                                                       [0;37m����[47m  [1;30m��[43m�[47m�[43m���[42m�[43m�[33m�[42m�����[43m�[0;33m�[1;36m
ECHO                [1;31m3) [1;36mExit                                [6C[1;30;43m�������[33m�������[0;33m�[1;36m
ECHO                                                       [0;37m����[47m   [1;30m�[43m���[33m�[40m�����[43m�[0;33m�[1;36m
@ECHO [00;30;40m�[01;32;40m������������������������������������������������������������������������������[00;37;40m[1A[s
GOTO COSMETICS

:COSMETICS
IF EXIST GG-HINT.EXE GOTO COS92
IF EXIST GGHINT.EXE GOTO COS92
IF EXIST DEALERS.EXE GOTO COS92
IF EXIST SWCBBS.EXE GOTO COS92
IF EXIST KEEN5.EXE GOTO COSGT
IF EXIST KEEN4.EXE GOTO COSGT
IF EXIST KEEN.EXE GOTO COSFGDM
GOTO EP2CHECK

:COS92
@ECHO [16;25H[01;31;40m2[00;37;40m[u
GOTO EP2CHECK

:COSFGDM
@ECHO [17;11H[01;37;40m      SPECIAL DEMO VERSION      [00;37;40m[u
GOTO EP1CHECK

:COSGT
@ECHO [16;25H[01;31;40m2[00;37;40m[u
@ECHO [17;12H[00;31;40mPublished by Goodtimes Software[00;37;40m[u
GOTO EP2CHECK

:EP2CHECK
IF EXIST KEEN5E.EXE GOTO EP2ENABLE
IF EXIST KEEN5.EXE GOTO EP2ENABLE
IF EXIST KEEN5C.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%�
GOTO EP1CHECK

:EP1CHECK
IF EXIST KEEN4E.EXE GOTO EP1ENABLE
IF EXIST KEEN4.EXE GOTO EP1ENABLE
IF EXIST KEEN.EXE GOTO EP1ENABLE
IF EXIST KEEN4C.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%�
GOTO CHOICES

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [21;16H[01;31;40m2) [01;35;40mThe Armageddon Machine[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [20;16H[01;31;40m1) [01;35;40mSecret of the Oracle[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 3 GOTO KEEN4
IF ERRORLEVEL 2 GOTO KEEN5
IF ERRORLEVEL 1 GOTO EXIT

:KEEN4
IF EXIST KEEN4E.EXE KEEN4E %1 %2 %3 %4 %5 %6 %7 %8 %9
IF EXIST KEEN4.EXE KEEN4 %1 %2 %3 %4 %5 %6 %7 %8 %9
IF EXIST KEEN.EXE KEEN %1 %2 %3 %4 %5 %6 %7 %8 %9
IF EXIST KEEN4C.EXE KEEN4C %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:KEEN5
IF EXIST KEEN5E.EXE KEEN5E %1 %2 %3 %4 %5 %6 %7 %8 %9
IF EXIST KEEN5.EXE KEEN5 %1 %2 %3 %4 %5 %6 %7 %8 %9
IF EXIST KEEN5C.EXE KEEN5C %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS