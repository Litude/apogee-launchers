@ECHO OFF

:START
CLS
@ECHO [0;1m[70C[33m������[0;33m�
@ECHO [63C[1m��  ��[0;33m�[1m��[0;33m�����
@ECHO [6C[1;35mA Fantastic Adventure of[24C[33m�������[0;33m�[1m��[43m�[0;33m�[1m��[0;33m�[1;43m�[40m��[43m�[40m�[0;33m�
@ECHO [6C[1;35mExploration and Survival[15C[33m�����    ����[43m�[0;33m���[1m��[43m�[40m��[0;33m��[1m��[43m��[0;33m��
@ECHO [36C[1m�   ��[0;33m� [1m��[43m�[40m����[0;33m�   [1m��[43m�[0;33m�   [1m�[43m��[40m��[0;33m�[1m���[43m�[40m��[0;33m�
@ECHO [30C[1m��   ���[0;33m� [1m��[0;33m� [1m�[43m�[0;33m� [1m���[0;33m�   [1m��[0;33m�   [1m��[0;33m� [1m��[0;33m�[1m��[43m���[0;33m��
@ECHO [23C[1m��   �����[0;33m� [1m������[0;33m��[1m��[0;33m�  [1m��[0;33m��  [1m��[43m�[0;33m�   [1m�[43m�[0;33m� [1m�[0;33m��  �
@ECHO [18C[1m��[0;33m�  [1m��[0;33m�[1m��[43m�[0;33m��[1m��[0;33m�[1m��[0;33m�[1m����[0;33m� [1m��[0;33m�[1m��[43m�[0;33m��   [1m�[43m�[0;33m�[5C[1;43m�[40m��   [0;33m(tm)
@ECHO [11C[1m������[0;33m�[1m��[43m�[2C[40m��[0;33m�[1m��[0;33m�  [1m�[43m�[0;33m�[1m��[0;33m�[1m���[0;33m��[1m����[43m�[0;33m��[6C[1;43m�[40m�   ��[43m��[0;33m��
@ECHO     [1m�����[43m�[0;33m�[1m��[0;33m�����[1m�����[43m�[0;33m�[1;43m�[40m�[43m�[0;33m�[1m��[43m�[0;33m�[1m���[0;33m� [1m�[43m�[0;33m�   ���[1m�   ��[0;33m� [1m��[0;33m�[1m���[0;33m��
@ECHO    [1m��[0;33m��[1m��[0;33m�[1m���[43m�[40m�[0;33m�   [1m���[0;33m��  [1m����[43m�[0;33m�  [1m�[0;33m��  [1m��[5C���[0;33m� [1m��[0;33m� [1m�[43m�[0;33m�[1m��[0;33m��
@ECHO    [1m����[43m�[0;33m��[1m��[43m��[0;33m��[1m����[43m�[0;33m��    [1m�[0;33m��� [1m���   ����[0;33m�   [1m������[0;33m��[1m��[0;33m�[1m���[43m�[2C[40m��[0;33m�
@ECHO   [1m��[43m��[40m��[0;33m�[1m���[43m�[40m��[0;33m�[1m�[43m��[0;33m��   [1m��  �����[43m��[0;33m� [1m��[0;33m�[1m��[0;33m�  [1m��[0;33m�[1m����[0;33m�[1m��[43m�[0;33m� [1m�����[43m�[0;33m��
@ECHO   [1m��[43m�[40m��[43m�[0;33m�[1m��[43m���[0;33m��[1m�������[0;33m�[1m��[0;33m�  [1m���[0;33m��  [1m��[43m�[0;33m�[1m���[0;33m� [1m��[0;33m�[1m���[0;33m��[1m��[0;33m�    ����
@ECHO   [1m�[43m���[0;33m��   �    [1m����[43m�[0;33m���[1m�[43m�[0;33m�  [1m��[0;33m��  [1m�����[43m�[40m��[0;33m�[1m���[0;33m� [1m�[43m�[0;33m�  ��
@ECHO [17C[1m��[43m�[0;33m�  [1m��[0;33m�  [1m���[0;33m�  [1m��[43m�[0;33m����[1m�[43m�[0;33m� [1m�[0;33m��
@ECHO [17C[1m��[0;33m�  [1m��[43m�[0;33m�  [1m��[0;33m��  [1m�[43m�[0;33m�[5C�[8C[1;31mDesigned by Scott Miller
@ECHO [16C[33m��[43m�[0;33m�  [1m��[0;33m�   [1m�[0;33m��[18C[0;31mAn Apogee Software Production
@ECHO [16C[1;33m�[43m�[0;33m�    ��
@ECHO [17C�[1m
@ECHO                                [37mS[33mtart the game
@ECHO                                 [37mH[33melp & hints
@ECHO                                 [37mI[33mnstructions
@ECHO                                     [37mQ[33muit
@ECHO [0;30m                                                                              �[00;37;40m[1A[s

:CHOICES
@CHOICE /N /C:SHIQ
IF ERRORLEVEL 4 GOTO EXIT
IF ERRORLEVEL 3 GOTO HELPSHEET
IF ERRORLEVEL 2 GOTO HINTSHEET
IF ERRORLEVEL 1 GOTO GAME

:HINTSHEET
IF EXIST HELP.DOC SET TITANICHINT=HELP.DOC
IF EXIST HELP.TXT SET TITANICHINT=HELP.TXT
CLS
TYPE %TITANICHINT%
PAUSE
GOTO START

:HELPSHEET
IF EXIST INSTRUCT.DOC SET TITANICHELP=INSTRUCT.DOC
IF EXIST INSTRUCT.TXT SET TITANICHELP=INSTRUCT.TXT
LIST %TITANICHELP% > NUL
IF NOT ERRORLEVEL 1 GOTO START
LESS %TITANICHELP% > NUL
IF NOT ERRORLEVEL 1 GOTO START
MORE < %TITANICHELP% > NUL
IF NOT ERRORLEVEL 1 GOTO START
CLS
ECHO LIST, LESS or MORE required to display instructions.
PAUSE
GOTO START

:NOTFOUND
ECHO Stuff not found
PAUSE
GOTO START

:LISTHELP
LIST %TITANICHELP%
GOTO START

:MOREHELP
MORE %TITANICHELP%
GOTO START

:GAME
BEYOND
GOTO START

:EXIT
SET TITANICHELP=
SET TITANICHINT=
CLS
