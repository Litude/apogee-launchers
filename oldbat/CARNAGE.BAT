@ECHO OFF
:START
CLS
@ECHO.
@ECHO [0;1m  ÛÛ   Û[5CÜÛ ÜÛÛÛÜ[6CÜ[7CÜÛÜ    ÛÛ   ÛÜÜÜÜ    Ü   ÛÛ[5CÜß  ÜÛÛÛÜ
@ECHO   Û Û  Û[5CÛÛ Ûß   ß[6CÛ[6CÛß ßÜ  Û Û  Û  Üß[5CÛ  Û Û  Üß    Ûß   ß
@ECHO   [34mÛÜÜÛ [37mÛ[5CÛÛ ÛÛÜÜ  Û ÛÛ   Û[5CÛ   ß  [34mÛÜÜÛ ÛßßÝ  [37mÛÛ   Û [34mÛÜÜÛ [37mÛ ßÜ  ÛÛÜÜ  Û
@ECHO   [0;34mÛ  Û [1mÛÛÛÜ  ÞÛ ÛÜ   Üß [37mÛ Û  Û[5C[34mÛÜ  Üß [0;34mÛ  Û Û  Û  [1;37mÛ Û  Û [0;34mÛ  Û [1mÛ   Û ÛÜ   Üß
@ECHO [5C[0;34mÛ[5Cß  Þ ßÛÛÛß   [1mÛ  Û Û[5C[0;34mßÛÛÛß[5CÛ   Û   [1mÛ  Û Û    [0;34mÛ  ÛÛÛ  ßÛÛÛß
@ECHO     Û[19CÛ   ÛÛ[14CÛ   ß    Û   ÛÛ   Û[13C[1;30m(tm)[8;1H   [0;34mß[39Cß[17Cß[1;31m
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
@ECHO [0;30m                                                                               ÿ[00;37;40m[2A[s

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
