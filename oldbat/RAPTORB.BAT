:START
SET MENUSELECTION=1
@ECHO OFF
CLS
@ECHO [10C[0;33;41mÛÛÛÛÛ[12CÛ[12CÛÛÛÛÛÛÛÛÛÛÛÛÛÛ[9CÛÛÛÛÛ[40m
@ECHO [9C[41m±±±±±±±±±[8C±±±[12C±±±±±±±±±±±±±±±[5C±±±±±±±±±±[40m
@ECHO [9C[41m°°[5C°°°[6C°°°[1C°[6C°°°°°[5C°°°[11C°°°°[5C°°°[40m
@ECHO [9C[41m°°[6C°°°[4C°°°[2C°°[4C°°°[2C°°°[3C°°°[3C°°°°°°[3C°°°[7C°°[40m
@ECHO [9C[31m±±[7C±±    ±±±  ±±±   ±±±   ±±±  ±±[33;41m°[2C[31;40m±±    ±±  ±±±[6C±±±
@ECHO [9C±±[5C±±±    ±±±    ±±   ±±±   ±±±  ±±±  ±±[5C±± ±±±    ±±±±
@ECHO [9C±±±±±±±±[5C±±±   ±±±±   ±±±  ±±±   ±±±  ±±[5C±± ±±±±±±±±±
@ECHO [9C±±  ±±±    ±±±±±±±±  ±±±  ±±±±±±±    ±±±   ±±±   ±± ±±±  ±±±
@ECHO [8C²²²   ²²²    ²²²[6C²²²  ²²²[8C²²±[7C²²²  ²²²   ²²²
@ECHO [8C²²²    ²²   ²²²[8C²²  ²²²[8C²²²[12C²²[5C²²²
@ECHO [8C²²²    ²²²  ²²[9C²²² ²²²[8C²²²[12C²²[5C²²²
@ECHO [8C°°°[5C°°°[14C² °°°[10C²[12C°°[6C°°°
@ECHO [7C°°°[6C°°°[16C°°[24C°°°[6C°°°
@ECHO [17C°°°   [1;34mC A L L   O F   T H E   S H A D O W S[11C[0;31m°°[1;30m (tm)
@ECHO [18C[0;31m°°[16C[0;31m°
@ECHO                          [1;5;33mBETA VERSION - DO NOT DISTRIBUTE

:DRAWMENU
@ECHO [18;0f[0;31m
IF %MENUSELECTION%==1 ECHO [1;31m[1A
@ECHO                                       Play[0;31m
@ECHO.
IF %MENUSELECTION%==2 ECHO [1;31m[1A
@ECHO                                       Setup[0;31m
@ECHO.
IF %MENUSELECTION%==3 ECHO [1;31m[1A
@ECHO                                       Quit[0;31m
@ECHO.
@ECHO [0;30mÿ[1;37m        [1;37mESC=[0;37mAbort               [1;37mUP/DOWN=[0;37mSelect               [1;37mY=[0;37mAccept[0m[1A

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
GOTO DRAWMENU

:INCREMENT
IF %MENUSELECTION%==3 SET MENUSELECTION=3
IF %MENUSELECTION%==2 SET MENUSELECTION=3
IF %MENUSELECTION%==1 SET MENUSELECTION=2
GOTO DRAWMENU

:SELECT1
CLS
SET CYGNUS=BETA
RAP %1 %2 %3 %4 %5 %6 %7 %8 %9
ECHO.
PAUSE > NUL
SET CYGNUS=
GOTO START

:SELECT2
CLS
SETUP %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:SELECT3
GOTO EXIT

:EXIT
SET MENUSELECTION=
CLS
