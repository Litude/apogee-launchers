@ECHO OFF

:START
SET CHOICES=4
CLS
@ECHO.
@ECHO [8C[0;1;33m��[25C��[43m�[0;33m�
@ECHO   [1m�����������[21C�[0;33m��[15C[1m�[0;33m�
@ECHO  [1m�[43m�[0;33m�����[1m�[0;33m����[1m���[18C�[0;33m�[15C[1m�[0;33m�[1m�[0;33m�
@ECHO   �[5C[1m�[0;33m�[5C�[1m�[0;33m�  [1m���[7C��  �[0;33m�[1m��[43m�[0;33m�[9C[1m��[0;33m��[1m�[43m�[6C[40m��    ���[5C��
@ECHO [8C�[0;33m�[6C[1m�[0;33m� [1m�[0;33m���[1m�[0;33m�  [1m���[0;33m��� [1m��[0;33m���[6C[1m����[43m�[0;33m��  [1m�[0;33m�   [1m��[0;33m��[1m�[0;33m� [1m�[0;33m��[1;43m�[40m�[0;33m�  [1m��[0;33m�[1m�[0;33m�
@ECHO [8C[1m�[0;33m�[6C[1m�[0;33m� [1m�[0;33m� [1m��[43m�[3C[40m�[0;33m�    [1m�[0;33m�[1m�[0;33m�[1m�[7C��[43m��[40m�   ��[0;33m�  [1m�[0;33m� [1m��[0;33m� [1m�[43m�[40m�[0;33m�[1;43m�[0;33m� [1m� �[43m�[40m�
@ECHO    �   �[43m�[0;33m�    [1m��[0;33m��  [1m�[43m�[0;33m�[1m�[0;33m��  [1m�[0;33m�    [1m�[0;33m�[1m�[43m�[0;33m��    [1m��[43m�[0;33m��  [1m�����[0;33m�  [1m�[43m�[40m�[0;33m�[1m�[0;33m�  [1m�[43m��[0;33m��  [1m�[43m��[0;33m��
@ECHO     [1m�[43m��[40m������[43m�[0;33m��[29C��[6C�[1m��[0;33m�  [1m� [0;33m� [1m�[0;33m�
@ECHO         ������                  [01;36;40mby Todd Replogle       [1;33m�[43m�[0;33m� [1m�[43m�[40m��[0;33m��
@ECHO                       [01;32;40mCopyright 1991 (c) Scenario Software   [0;33m��
@ECHO                     [01;37;40mPublished by Apogee Software Productions
@ECHO.
@ECHO                         [00;34;40m��������������������������������
@ECHO                         [01;34;44m �[01;34;41m����������������������������[01;34;44m� [00;37;40m
@ECHO                         [01;34;44m �[01;32;41m      Volume Selection      [01;34;44m� [00;37;40m
@ECHO                         [01;34;44m �[01;34;41m                            [01;34;44m� [00;37;40m
@ECHO                         [01;34;44m �[01;31;41m 1) [01;31;41mPrince of Destiny       [01;34;44m� [00;37;40m
@ECHO                         [01;34;44m �[01;31;41m 2) [01;31;41mThe Undead Kingdom      [01;34;44m� [00;37;40m
@ECHO                         [01;34;44m �[01;31;41m 3) [01;31;41mDungeons of Doom        [01;34;44m� [00;37;40m
@ECHO                         [01;34;44m �[01;34;41m                            [01;34;44m� [00;37;40m
@ECHO                         [01;34;44m �[01;37;41m 4) [01;36;41mQuit                    [01;34;44m� [00;37;40m
@ECHO                         [01;34;44m �[01;34;41m����������������������������[01;34;44m� [00;37;40m
@ECHO                         [00;34;40m��������������������������������
@ECHO [00;30;40m�[00;37;40m������������������������������������������������������������������������������[1A[s

:EP3CHECK
IF EXIST DA3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%�
GOTO EP2CHECK

:EP2CHECK
IF EXIST DA2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%�
GOTO EP1CHECK

:EP1CHECK
IF EXIST DA1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%�
GOTO CHOICES

:EP3ENABLE
SET CHOICES=%CHOICES%3
@ECHO [20;28H[01;37;41m3) [01;36;41mDungeons of Doom[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [19;28H[01;37;41m2) [01;36;41mThe Undead Kingdom[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [18;28H[01;37;41m1) [01;36;41mPrince of Destiny[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 4 GOTO DA1
IF ERRORLEVEL 3 GOTO DA2
IF ERRORLEVEL 2 GOTO DA3
IF ERRORLEVEL 1 GOTO EXIT

:DA1
CLS
DA1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:DA2
CLS
DA2 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:DA3
CLS
DA3 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
