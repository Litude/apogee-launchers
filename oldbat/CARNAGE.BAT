@ECHO OFF
:START
CLS
@ECHO.
@ECHO [0;1m  ��   �[5C�� �����[6C�[7C���    ��   �����    �   ��[5C��  �����
@ECHO   � �  �[5C�� ��   �[6C�[6C�� ��  � �  �  ��[5C�  � �  ��    ��   �
@ECHO   [34m���� [37m�[5C�� ����  � ��   �[5C�   �  [34m���� ����  [37m��   � [34m���� [37m� ��  ����  �
@ECHO   [0;34m�  � [1m����  �� ��   �� [37m� �  �[5C[34m��  �� [0;34m�  � �  �  [1;37m� �  � [0;34m�  � [1m�   � ��   ��
@ECHO [5C[0;34m�[5C�  � �����   [1m�  � �[5C[0;34m�����[5C�   �   [1m�  � �    [0;34m�  ���  �����
@ECHO     �[19C�   ��[14C�   �    �   ��   �[13C[1;30m(tm)[8;1H   [0;34m�[39C�[17C�[1;31m
@ECHO.
@ECHO          Developed by Interactive Binary Illusions and SubZero Software
@ECHO                       [0;1;35mCopyright (c) 1994 Apogee Software
@ECHO.
@ECHO.
@ECHO                            [1;34m-- MAKE A SELECTION --
@ECHO.
@ECHO.
@ECHO                                 [1;34mP[36mlay the Game
@ECHO.
@ECHO                               [1;34mT[36mechnical Support
@ECHO.
@ECHO.
@ECHO                                     [1;34mQ[36muit
@ECHO.
@ECHO [0;30m                                                                               �[00;37;40m[2A[s

@CHOICE /N /CQTP% >> NUL
IF ERRORLEVEL 3 GOTO GAME
IF ERRORLEVEL 2 GOTO HELPSHEET
IF ERRORLEVEL 1 GOTO EXIT

:GAME
CARNAGE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:HELPSHEET
IF EXIST AC-HELP.EXE AC-HELP.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
IF EXIST ACHELP.EXE ACHELP.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
