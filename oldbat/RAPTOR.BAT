:START
SET MENUSELECTION=1
@ECHO OFF
CLS
@ECHO [10C[0;33;41m�����[12C�[12C��������������[9C�����[40m
@ECHO [9C[41m���������[8C���[12C���������������[5C����������[40m
@ECHO [9C[41m��[5C���[6C���[1C�[6C�����[5C���[11C����[5C���[40m
@ECHO [9C[41m��[6C���[4C���[2C��[4C���[2C���[3C���[3C������[3C���[7C��[40m
@ECHO [9C[31m��[7C��    ���  ���   ���   ���  ��[33;41m�[2C[31;40m��    ��  ���[6C���
@ECHO [9C��[5C���    ���    ��   ���   ���  ���  ��[5C�� ���    ����
@ECHO [9C��������[5C���   ����   ���  ���   ���  ��[5C�� ���������
@ECHO [9C��  ���    ��������  ���  �������    ���   ���   �� ���  ���
@ECHO [8C���   ���    ���[6C���  ���[8C���[7C���  ���   ���
@ECHO [8C���    ��   ���[8C��  ���[8C���[12C��[5C���
@ECHO [8C���    ���  ��[9C��� ���[8C���[12C��[5C���
@ECHO [8C���[5C���[14C� ���[10C�[12C��[6C���
@ECHO [7C���[6C���[16C��[24C���[6C���
@ECHO [17C���   [1;34mC A L L   O F   T H E   S H A D O W S[11C[0;31m��[1;30m (tm)
@ECHO [18C[0;31m��[16C[0;31m�

:DRAWMENU
@ECHO [16;0f[0;31m
IF %MENUSELECTION%==1 ECHO [1;31m[1A
@ECHO                                       Play[0;31m
@ECHO.
IF %MENUSELECTION%==2 ECHO [1;31m[1A
@ECHO                                       Setup[0;31m
@ECHO.
IF %MENUSELECTION%==3 ECHO [1;31m[1A
@ECHO                                 Technical Support[0;31m
@ECHO.
IF %MENUSELECTION%==4 ECHO [1;31m[1A
@ECHO                                       Quit[0;31m
@ECHO.
@ECHO [0;30m�[1;37m        [1;37mESC=[0;37mAbort               [1;37mUP/DOWN=[0;37mSelect               [1;37mY=[0;37mAccept[0m[1A

:CHOICE
@CHOICE /N /C:PHY
IF ERRORLEVEL 4 GOTO EXIT
IF ERRORLEVEL 3 GOTO SELECT%MENUSELECTION%
IF ERRORLEVEL 2 GOTO DECREMENT
IF ERRORLEVEL 1 GOTO INCREMENT
GOTO EXIT

:DECREMENT
IF %MENUSELECTION%==1 SET MENUSELECTION=1
IF %MENUSELECTION%==2 SET MENUSELECTION=1
IF %MENUSELECTION%==3 SET MENUSELECTION=2
IF %MENUSELECTION%==4 SET MENUSELECTION=3
GOTO DRAWMENU

:INCREMENT
IF %MENUSELECTION%==4 SET MENUSELECTION=4
IF %MENUSELECTION%==3 SET MENUSELECTION=4
IF %MENUSELECTION%==2 SET MENUSELECTION=3
IF %MENUSELECTION%==1 SET MENUSELECTION=2
GOTO DRAWMENU

:SELECT1
CLS
RAP %1 %2 %3 %4 %5 %6 %7 %8 %9
ECHO.
PAUSE > NUL
GOTO START

:SELECT2
CLS
SETUP %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:SELECT3
CLS
IF EXIST RAP-HELP.EXE RAP-HELP %1 %2 %3 %4 %5 %6 %7 %8 %9
IF EXIST RAPHELP.EXE RAPHELP %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:SELECT4
GOTO EXIT

:EXIT
SET MENUSELECTION=
CLS
