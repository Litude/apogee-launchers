@ECHO OFF
:START
CLS
:DRAWLOGO
@ECHO [1;36m
@ECHO [35m                                                              [33m   ����������
@ECHO [35m  ��������    �������  �������� �������� ����� ����   �� ���  [33m    �� �� ��
@ECHO [35m   �������   ���� ����  �������  �������  ���   ����  �  ���  [33m �   ������
@ECHO [35m   ��� ����  ���   ���  ���      ���      ���   � ��� �  ��   [33m  \   ����     �
@ECHO [35m   ���  ���� ���   ���  ���      ���      ���   �  ����       [33m   \�����\    /
@ECHO [35m   ���   ��� ���   ���  ���      ���      ���   �   ���       [31m       ��[33m \  /
@ECHO [35m   ���   ��� ���� ����  ���      ���      ���   �    ��       [31m      � �[33m  \/
@ECHO [35m  ���������   �������  ����     ����     ����� ��     � [0;35m(tm)  [1;31m     �  �
@ECHO [34m                                                              [31m    �   �
@ECHO [34m                  Developed by Accursed Toys                  [31m   �    �
@ECHO [32m                                                              [31m  �     �[33m

:DRAWVERSION
IF EXIST BOPSW.EXE GOTO VERSWR
IF EXIST BOPPIN4.LVL GOTO VERULT
IF EXIST BOPPIN.EXE GOTO VERBAS
GOTO DRAWMENU

:VERSWR
@ECHO [1A                      Shareware Version
GOTO DRAWMENU

:VERULT
@ECHO [1A          Registered Version - Super Ultimate Boppin'
GOTO DRAWMENU

:VERBAS
@ECHO [1A              Registered Version - Basic Boppin'
GOTO DRAWMENU

:DRAWMENU
@ECHO.
@ECHO [33m   ����������
@ECHO [33m    �� �� ��                     [33m         P[36mlay
@ECHO [33m �   ������   �
@ECHO [33m  \   ����   /                   [33m         S[36metup
@ECHO [33m   \��������/  
@ECHO [32m       ��                        [33m   T[36mechnical Support
@ECHO [32m      �  �
@ECHO [32m      �  �                       [33m         Q[36muit
@ECHO [32m     �    �   
@ECHO [32m    �      �   
@ECHO [32m    �      � [37m               Copyright (c) 1994 Apogee Software
@ECHO [0;30m                                                                              �[00;37;40m[1A[s

:CHOICES
@CHOICE /N /CQTSP% >> NUL
IF ERRORLEVEL 4 GOTO GAME
IF ERRORLEVEL 3 GOTO SETUP
IF ERRORLEVEL 2 GOTO HELPSHEET
IF ERRORLEVEL 1 GOTO EXIT

:GAME
CLS
IF EXIST BOPSW.EXE GOTO GAMESW
BOPPIN %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:GAMESW
BOPSW %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:SETUP
SETUP %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:HELPSHEET
IF EXIST BOP-HELP.EXE BOP-HELP.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
IF EXIST BOPHELP.EXE BOPHELP.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
