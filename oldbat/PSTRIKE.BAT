@ECHO OFF

:START
CLS
@ECHO [1;34m
@ECHO    �����  ���         ���                   ���      �
@ECHO     ����   ��   ���    ��  ��    ���        �����   ��    ���  � ���     ���
@ECHO     �� ��  ��  �����   �����   ��� ��          ��� ����  �� ��  �� ��  ��� ��
@ECHO     �� ��  ��  �� ��   �����   ������           ��  ��   �� ��  �� ��  ������
@ECHO    ������ ���� ������ ��� ����  �����       �����   ���� ����� ��� ���  �����
@ECHO [33m
@ECHO [33m� ��  �[5C��[6C�   �����[6C�����
@ECHO �   � �[5C� �[6C�  ��   �  ��� �[39C[0;33m(tm)[10;1H[1;31m����  [33m�[5C[31m���� [33m��   � ����  �[5C[31m�    [33m�����[6C����� ����� �� �  �� �����
@ECHO [0;31m�[5C[1m����  [0;31m�  � [1;33m� �  � [31m��   ��    [0;31m�    [1;33m�[5C�� ��� �    �  �� �� ���   ��   �
@ECHO  [0;31m�[8C�    � [1m�  � � [0;31m�����[5C�   [1m�  �����[7C�    ����  [33m�� ���   ����  �[13;1H  [0;31m�[11C�  �   ��[16C������[7C�[5C�  �  [1m�� �  �  ��   ��[14;1H[13C[0;31m�[37C�[8C�    �   �   �����
@ECHO [37m
@ECHO                       [1;41m������������������������������������[0;40m
@ECHO                       [1;41m�   [33m1) [37mPlay                        [1;44m�[0;40m
@ECHO                       [1;41m�   [33m2) [37mSound Setup                 �[0;40m
@ECHO                       [1;41m�   [33m3) [37mTechnical Support           [1;44m�[0;40m
@ECHO                       [1;41m�   [33m4) [37mQuit                        �[0;40m
@ECHO                       [1;41m������������������������������������[0;40m
@ECHO.
@ECHO [01;32m                          Developed by JAM Productions
@ECHO [01;35;40m                       Copyright (c) 1994 Apogee Software[00;37;40m
@ECHO [00;30;40m�[00;37;40m������������������������������������������������������������������������������[00;37;40m[1A[s

@CHOICE /N /C:1234
IF ERRORLEVEL 4 GOTO EXIT
IF ERRORLEVEL 3 GOTO HELPSHEET
IF ERRORLEVEL 2 GOTO SETUP
IF ERRORLEVEL 1 GOTO GAME

:GAME
CALL PLANET.BAT %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:SETUP
SETBLAST.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:HELPSHEET
IF EXIST PS-HELP.EXE PS-HELP.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
IF EXIST PSHELP.EXE PSHELP.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
