@ECHO OFF

:START
SET CHOICES=4
CLS
@ECHO.
@ECHO             [01;32;40m������[01;33;40m� [01;32;40m������[01;33;40m� [01;32;40m��[01;33;40m� [01;32;40m��[01;33;40m� [01;32;40m������[01;33;40m� [01;32;40m��������[01;33;40m� [01;32;40m������[01;33;40m� [01;32;40m��[01;33;40m�    
@ECHO             [01;32;40m��[01;33;40m����� [01;32;40m��[01;33;40m��[01;32;40m��[01;33;40m� [01;32;40m��[01;33;40m� [01;32;40m��[01;33;40m� [01;32;40m��[01;33;40m�����    [01;32;40m��[01;33;40m���� [01;32;40m��[01;33;40m��[01;32;40m��[01;33;40m� [01;32;40m��[01;33;40m�    
@ECHO             [01;32;40m��[01;33;40m�     [01;32;40m������[01;33;40m� [01;32;40m������[01;33;40m� [01;32;40m������[01;33;40m�    [01;32;40m��[01;33;40m�    [01;32;40m������[01;33;40m� [01;32;40m��[01;33;40m�    
@ECHO             [01;32;40m��[01;33;40m�     [01;32;40m��[01;33;40m�[01;32;40m��[01;33;40m��  ���[01;32;40m��[01;33;40m�  ���[01;32;40m��[01;33;40m�    [01;32;40m��[01;33;40m�    [01;32;40m��[01;33;40m��[01;32;40m��[01;33;40m� [01;32;40m��[01;33;40m�    
@ECHO             [01;32;40m������[01;33;40m� [01;32;40m��[01;33;40m� [01;32;40m��[01;33;40m� [01;32;40m������[01;33;40m� [01;32;40m������[01;33;40m�    [01;32;40m��[01;33;40m�    [01;32;40m��[01;33;40m� [01;32;40m��[01;33;40m� [01;32;40m������[01;33;40m�
@ECHO              ������  ��  ��  ������  ������     ��     ��  ��  ������
@ECHO                   [01;32;40m������[01;33;40m� [01;32;40m������[01;33;40m� [01;32;40m��[01;33;40m�      [01;32;40m��[01;33;40m� [01;32;40m������[01;33;40m� [01;32;40m������[01;33;40m�
@ECHO                   [01;32;40m��[01;33;40m����� [01;32;40m��[01;33;40m��[01;32;40m��[01;33;40m�  [01;32;40m��[01;33;40m�    [01;32;40m��[01;33;40m�� [01;32;40m��[01;33;40m����� [01;32;40m��[01;33;40m�����
@ECHO                   [01;32;40m��[01;33;40m�     [01;32;40m������[01;33;40m�   [01;32;40m��[01;33;40m�  [01;32;40m��[01;33;40m��  [01;32;40m����[01;33;40m�   [01;32;40m������[01;33;40m�
@ECHO                   [01;32;40m��[01;33;40m�     [01;32;40m��[01;33;40m��[01;32;40m��[01;33;40m�    [01;32;40m��[01;33;40m�[01;32;40m��[01;33;40m��   [01;32;40m��[01;33;40m���    ���[01;32;40m��[01;33;40m�
@ECHO                   [01;32;40m������[01;33;40m� [01;32;40m��[01;33;40m� [01;32;40m��[01;33;40m�     [01;32;40m���[01;33;40m��    [01;32;40m������[01;33;40m� [01;32;40m������[01;33;40m�
@ECHO                    ������  ��  ��      ���      ������  ������
@ECHO       [01;32;40m                       A game by Frank Maddin
@ECHO       [00;32;40m                 Copyright (c) 1991 Apogee Software
@ECHO.
@ECHO                          [00;36;41m����������������������������ķ[01;30;40m
@ECHO        [01;34m���������[00;34m�        [00;36;41m�[01;37;41m   VOLUME SELECTION MENU    [00;36;41m�[01;30;40m        [01;34m���������[00;34m�
@ECHO      [01;34m��[44m��[40m�[44m� �[40m�[44m��[40m�[44m [00;34m�      [00;36;41m�                            �[01;30;40m      [01;34m��[44m��[40m�[44m� �[40m�[44m��[40m�[44m [00;34m�
@ECHO     [01;34m�����[44m [40m�����[44m  �  [40m     [00;36;41m�[01;31;41m 1) Troubles with Twibbles  [00;36;41m�[01;30;40m     [01;34m�����[44m [40m�����[44m  �  [40m
@ECHO      [01;34m�����[44m [40m���[44m  ��[00;34m�      [00;36;41m�[01;31;41m 2) Slugging it Out         [00;36;41m�[01;30;40m      [01;34m�����[44m [40m���[44m  ��[00;34m�
@ECHO        [01;34m����[44m�����[00;34m�        [00;36;41m�[01;31;41m 3) Mylo vs. the Supernova  [00;36;41m�[01;30;40m        [01;34m����[44m�����[00;34m�
@ECHO          [01;34m���[44m �[00;34m�          [00;36;41m�                            �[01;30;40m          [01;34m���[44m �[00;34m�
@ECHO            [01;34m�[00;34m�            [00;36;41m�[01;37;41m 4) [01;33;41mQuit                    [00;36;41m�[01;30;40m            [01;34m�[00;34m�
@ECHO [00;30;40m�[00;37;40m                        [00;36;41m����������������������������Ľ[00;37;40m�����������������������[00;30;40m�[00;37;40m[1A[s

:EP3CHECK
IF EXIST CC3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%�
GOTO EP2CHECK

:EP2CHECK
IF EXIST CC2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%�
GOTO EP1CHECK

:EP1CHECK
IF EXIST CC1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%�
GOTO CHOICES

:EP3ENABLE
SET CHOICES=%CHOICES%3
@ECHO [22;28H[01;37;41m3) [01;33;41mMylo vs. the Supernova[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [21;28H[01;37;41m2) [01;33;41mSlugging it Out[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [20;28H[01;37;41m1) [01;33;41mTroubles with Twibbles[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 4 GOTO CC1
IF ERRORLEVEL 3 GOTO CC2
IF ERRORLEVEL 2 GOTO CC3
IF ERRORLEVEL 1 GOTO EXIT

:CC1
CLS
CC1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:CC2
CLS
CC2 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:CC3
CLS
CC3 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
