@ECHO OFF

:START
SET CHOICES=5
CLS
@ECHO [0;32;40m
@ECHO                           �������� ��     �� ��������
@ECHO       [1;31m Designed by[0;32m           ��    ��������� �������     [1;31mCopyright (c)  1991[0;32m
@ECHO       [0;31mTodd Replogle[0;32m          ��    ��     �� ��          [0;31m Scenario Software[0;32m
@ECHO                              ��    ��     �� ��������
@ECHO.
@ECHO �������� �������� ����� �� ��    �� �������� �������� ����� �� �������� ��������[1A
@ECHO �� �� �� ��    �� �� �� �� ��    �� �� �� �� �������  �� �� ��    ��    ��������[1A
@ECHO ��    �� ��    �� �� �� �� ��    �� ��    �� ��       �� �� ��    ��          ��[1A
@ECHO ��    �� �������� �� ����� �������� ��    �� �������� �� �����    ��    ��������[1A
@ECHO.
@ECHO          �������� ��������      �������� �������� �������� ��������  ��
@ECHO          ��    �� �������       �� �� �� �������� �������� ��������  ��
@ECHO          ��    �� ��            ��    �� ��    �� ��   ��        ��  ��
@ECHO          �������� ��            ��    �� ��    �� ��   ��� ��������  ��
@ECHO.
@ECHO        [0;33m�[32;43m�[31m�[40m���          [1;33mWhich volume do you wish to play?        [0;32m���[8C�
@ECHO        [33m�    [31m�                                                    [0;32m�[31;43m��[5C[33;40m�[32;41m�[40m��
@ECHO        [33m�[31m�����                  [31m1) First Contact                    [0;31;43m��[3C�[40m�
@ECHO       ���[43m��[40m���                 [31m2) The Pyramid                      [0;33m�[31;43m�[40m�[33m�[31;43m��[40m
@ECHO      [33m��[31m��[32;43m��[31;40m��[33m��                [31m3) The Fortress                   [0;33m��[31;43m�������[33;40m�
@ECHO     �� [31m��[43m��[40m�� [33m��               [31m4) The Face                       [0;33m�[31;43m��[33;40m�[31m��[33m��[31;43m�[40m�
@ECHO        [31m��  ��                  [1;32m5) [1;31mQuit                             [0;33m�[31m�[33m�[31m�[33m�[31m��
@ECHO       [33m���  ���                                                  [0;33m���[31m��   ����
@ECHO [00;30;40m�[00;37;40m                        [01;32;40mAn Apogee Software Production�������������������������[00;37;40m[1A[s
GOTO EP4CHECK

:EP4CHECK
IF EXIST MARS4.EXE GOTO EP4ENABLE
SET CHOICES=%CHOICES%�
GOTO EP3CHECK

:EP3CHECK
IF EXIST MARS3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%�
GOTO EP2CHECK

:EP2CHECK
IF EXIST MARS2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%�
GOTO EP1CHECK

:EP1CHECK
IF EXIST MARS1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%�
GOTO CHOICES

:EP4ENABLE
SET CHOICES=%CHOICES%4
@ECHO [22;32H[01;32m4) [1;31mThe Face[00;37;40m[u
GOTO EP3CHECK

:EP3ENABLE
SET CHOICES=%CHOICES%3
@ECHO [21;32H[01;32m3) [1;31mThe Fortress[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [20;32H[01;32m2) [1;31mThe Pyramid[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [19;32H[01;32m1) [1;31mFirst Contact[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 5 GOTO MARS1
IF ERRORLEVEL 4 GOTO MARS2
IF ERRORLEVEL 3 GOTO MARS3
IF ERRORLEVEL 2 GOTO MARS4
IF ERRORLEVEL 1 GOTO EXIT

:MARS1
CLS
MARS1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:MARS2
CLS
MARS2 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:MARS3
CLS
MARS3 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:MARS4
CLS
MARS4 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
