@ECHO OFF

:START
SET CHOICES=5
CLS
@ECHO [0;32m
@ECHO   ������� �������� ��������� ���������  ���������  ������ �������� �� ��������
@ECHO    ��   �� ����      ���� ��  ����  ��    ���� �� ��   ��� ����    �� ���   �
@ECHO    ������   �� ���  �� ���      �����    �� ���   �� �� ��  �� ���      �����
@ECHO    ��       ��  �� ����  ��     ��  ��  ����  ��  ���� ���  ��  ��    �     ��
@ECHO   ����     ���� �� ��   ����   ���� ��� ��   ����  ������  ���� ��    ��������
@ECHO.
@ECHO                     ���������� ������  ������������ ��������
@ECHO                       � �� �  ��   ���  ����������   ���� ��
@ECHO                         ��    �� �� �� ��   ��   ��   �� ��
@ECHO                         ��    ���� ��� ��   ��   ��   ��   ��
@ECHO        [0;32m������          ����    ������   �� ���� ��   ��������       [0;32m�[33m���[32m�
@ECHO     [0;32m���[43m�[40m�[43m��[40m�[43m�[40m���                                                 [0;32m�[33m��[31;43m�[33;40m������[32m�
@ECHO        [0;33m������               [1;31mA Nevada Smith Adventure             [0;33m�[31m��[33m������[31m�[33m�
@ECHO         [0;31m�[43m��[40m�                                                     [0;32;43m�[31;40m�[33m��� ���[31m�[32;43m�[40m
@ECHO     [0;33m ���[31m����[33m���        [1;32mWhich volume do you wish to play?         [0;32;43m�[1C[31;40m�[33m�� ���[31m�[32;43m�[40m
@ECHO     [0;33m �  [31;42m�[40m��[42m�[2C[33;40m�                                                  [0;33m��[31m�[33m������[31m�[33m�
@ECHO        [0;32m��  ��             [31m1) Raiders of the Lost Tomb            [0;32;43m�[33;40m� [31m�[33m���� �[32;43m�[40m
@ECHO     [0;32m  ���  ���            [31m2) Pharaoh's Curse                     [0;32m�[9C�
@ECHO                           [31m3) Temple of Terror
@ECHO                           [31m4) Nevada's Revenge
@ECHO                           [1;32m5) [1;31mQuit
@ECHO.
@ECHO [0;30;40m�[00;37;40m                         [01;33;40m(c) 1990 by Apogee Software�������������������������[00;37;40m[1A[s
GOTO EP4CHECK

:EP4CHECK
IF EXIST PTOMB4.EXE GOTO EP4ENABLE
SET CHOICES=%CHOICES%�
GOTO EP3CHECK

:EP3CHECK
IF EXIST PTOMB3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%�
GOTO EP2CHECK

:EP2CHECK
IF EXIST PTOMB2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%�
GOTO EP1CHECK

:EP1CHECK
IF EXIST PTOMB1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%�
GOTO CHOICES

:EP4ENABLE
SET CHOICES=%CHOICES%4
@ECHO [21;27H[1;32m4) [31mNevada's Revenge[00;37;40m[u
GOTO EP3CHECK

:EP3ENABLE
SET CHOICES=%CHOICES%3
@ECHO [20;27H[1;32m3) [31mTemple of Terror[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [19;27H[1;32m2) [31mPharaoh's Curse[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [18;27H[1;32m1) [31mRaiders of the Lost Tomb[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 5 GOTO PTOMB1
IF ERRORLEVEL 4 GOTO PTOMB2
IF ERRORLEVEL 3 GOTO PTOMB3
IF ERRORLEVEL 2 GOTO PTOMB4
IF ERRORLEVEL 1 GOTO EXIT

:PTOMB1
CLS
PTOMB1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:PTOMB2
CLS
PTOMB2 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:PTOMB3
CLS
PTOMB3 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:PTOMB4
CLS
PTOMB4 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
