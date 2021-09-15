:START
SET MENUSELECTION=1
@ECHO OFF
CLS
@ECHO.
@ECHO                 [0;1m  [0;31m²²²²²Ü    Ü²²²²²   Ü²²²Ü   ²²²²²²²² ²²²  ²²
@ECHO                   ÛÛÛ  ÛÛ  ÛÛÛß[5CÛÛÛ  ÛÛ    ÛÛÛ    ÛÛÛ  ÛÛ
@ECHO                   [1;33;41m°°°[0;31mÝ [1;33;41m°°[0;31mÝ [1;33;41m°°°[0;31mÝ[5C[1;33;41m°°°[0;31mÝ [1;33;41m°°[0;31mÝ   [1;33;41m°°°[0;31mÝ   [1;33;41m°°°[0;31mÝ [1;33;41m°°[0;31mÝ
@ECHO                   [1;33;41m±±±[0;31mÝ [1;33;41m±±[0;31mÝ [1;33;41m±±±±±[0;31mÝ   [1;33;41m±±±±±±±[0;31mÝ   [1;33;41m±±±[0;31mÝ   [1;33;41m±±±±±±±[0;31mÝ
@ECHO                   [1;33mÛÛÛ[0;31mÝ [1;33mÛÛ[0;31mÝ [1;33mÛÛÛ[6CÛÛÛ[0;31mÝ [1;33mÛÛ[0;31mÝ   [1;33mÛÛÛ[0;31mÝ   [1;33mÛÛÛ[0;31mÝ [1;33mÛÛ[0;31mÝ
@ECHO    [1;37mDeveloped by   [37mÛÛÛÛÛ[41mß[0;31mß  [1;37mÛÛÛÛÛÛÛ[0;31mÝ [1;37mÛÛÛ[0;31mÝ [1;37mÛÛ[0;31mÝ   [1;37mÛÛÛ[0;31mÝ   [1;37mÛÛÛ[0;31mÝ [1;37mÛÛ[0;31mÝ  [1;37mPublished by
@ECHO    [1;37m   Remedy                                                       Apogee
@ECHO    [1;37mEntertainment  [0;31m²²²²²Ü    Ü²²²Ü   ²²²[6C²²²[6C²²²  ²²     [1;37mSoftware
@ECHO                   [0;31mÛÛÛ ßÛÛ  ÛÛÛ  ÛÛ  [41m [40mÛÛ[6C[41m [40mÛÛ[6CÛÛÛ  ÛÛ
@ECHO                   [1;33;41m°°°[0;31mÝ [1;33;41m°°[0;31mÝ [1;33;41m°°°[0;31mÝ [1;33;41m°°[0;31mÝ [1;33;41m°°°[0;31mÝ[5C[1;33;41m°°°[0;31mÝ[5C[1;33;41m°°°[0;31mÝ [1;33;41m°°[0;31mÝ
@ECHO                   [0;31mßßß [1;33mÜ[41m±±[0;31mÝ [1;33;41m±±±±±±±[0;31mÝ [1;33;41m±±±[0;31mÝ[5C[1;33;41m±±±[0;31mÝ[5C[1;33;41m±±±[40mÜÜ[41m±±[0;31mÝ
@ECHO                   [1;33mÛÛÛÛÛÛ[0;31mÛ  [1;33mÛÛÛ[0;31mÝ [1;33mÛÛ[0;31mÝ [1;33mÛÛÛ[41mÜ[0;31mÜ    [1;33mÛÛÛ[41mÜ[0;31mÜ[5C[1;33mßÛÛÛ[41mß[0;31mß
@ECHO                   [1;37mÛÛÛ[0;31mÝ [1;37mÛÛ[0;31mÝ [1;37mÛÛÛ[0;31mÝ [1;37mÛÛ[0;31mÝ  [1;37mßÛÛÛÛÛ[0;31mÝ  [1;37mßÛÛÛÛÛ[0;31mÝ    [1;37mÛÛ[0;31mÝ [37m(tm)
@ECHO.

:DRAWMENU
@ECHO [16;0f[0;33m
IF %MENUSELECTION%==1 ECHO [1;33m[1A
@ECHO                                       Play[0;33m
@ECHO.
IF %MENUSELECTION%==2 ECHO [1;33m[1A
@ECHO                                       Setup[0;33m
@ECHO.
IF %MENUSELECTION%==3 ECHO [1;33m[1A
@ECHO                                 Technical Support[0;33m
@ECHO.
IF %MENUSELECTION%==4 ECHO [1;33m[1A
@ECHO                                       Quit[0;33m
@ECHO.
@ECHO [0;30mÿ[1;37m        [1;37mEsc [0;37mExits                [1;37mUp/Down [0;37mMoves               [1;37mY [0;37mSelects[0m[1A

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
RALLY %1 %2 %3 %4 %5 %6 %7 %8 %9
ECHO.
PAUSE > NUL
GOTO START

:SELECT2
CLS
SETUP %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:SELECT3
CLS
IF EXIST DR-HELP.EXE DR-HELP %1 %2 %3 %4 %5 %6 %7 %8 %9
IF EXIST DRHELP.EXE DRHELP %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:SELECT4
GOTO EXIT

:EXIT
SET MENUSELECTION=
CLS
