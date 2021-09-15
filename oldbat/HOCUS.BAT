@ECHO OFF

:START
CLS
@ECHO [1;34;44mßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß[1A
@ECHO [1;37;44m  ÜßÛÛ  ÛÛß                               ÜßÛÛßßÛÛÜ                             ÿ[1A
@ECHO [1;37;44m Û  ÛÛ  ÛÛ                               Û  ÛÛ   ÛÛ                            ÿ[1A
@ECHO [1;37;44m Û  ÛÛ ÜÛÛß  ÜÜÜÜ   ÜÜÜ  ÜÜÜ ÜÜÜ   ÜÜÜ   Û  ÛÛ   ÛÛ  ÜÜÜÜ   ÜÜÜ  ÜÜÜ ÜÜÜ   ÜÜÜ ÿ[1A
@ECHO [1;37;44m  ß ÛÛß ÛÛ  ÛÛ ÛÛÛ ÛÛßßÛ  ÛÛ  ÛÛ  ÛÛ ßß   ß ÛÛÜÜÛß  ÛÛ ÛÛÛ ÛÛßßÛ  ÛÛ  ÛÛ  ÛÛ ßßÿ[1A
@ECHO [1;37;44m    ÛÛ  ÛÛ  ÛÛÜ ÛÛ ÛÛ     ÛÛ  ÛÛ   ßßÛÜ     ÛÛ      ÛÛÜ ÛÛ ÛÛ     ÛÛ  ÛÛ   ßßÛÜÿ[1A
@ECHO [1;37;44m   ÜÛÛ  ÛÛÜ ßÛÛÜÛß ßÛÛÛß  ßÛÛßÛÛß ßÛÜÛß    ÜÛÛÜ     ßÛÛÜÛß ßÛÛÛß  ßÛÛßÛÛß ßÛÜÛßÿ[1A
@ECHO [1;37;44m                                         Üß    ß                           (tm)ÿ[1A
@ECHO [1;34;44mÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ[1A
@ECHO [00;37;40m
@ECHO [00;37;40m     ù                              [1;37;40m ù                             [5mù
@ECHO [00;37;40m       [1mù[00;37;40m                  [5mù[0m                      ù                   ù
@ECHO [00;37;40m                     ù         [1;37mP[31mlay Hocus Pocus[00;37;40m[1m     ù       ù
@ECHO [00;37;40m                        [1mù                     ù                    
@ECHO [00;37;40m                               [1;37mS[31metup[00;37;40m                                     ù
@ECHO [00;37;40m          ù      [5mù[0m                ù                   [5mù           [0;1mù
@ECHO [00;37;40m    ù   ù                      [1;37mT[31mechnical Support[00;37;40m    ù
@ECHO [00;37;40m  [5mù[0m        [1mù             ù                                      ù          ù  ù
@ECHO [00;37;40m  [1mù[00;37;40m                  ù         [1;37mQ[31muit[00;37;40m                   ù  [5mù  
@ECHO [00;37;40m                             ù                            ù
@ECHO [00;37;40m   ù           ù                                  ù                     [1mù
@ECHO.
@ECHO [1;37;44m                         Developed by Moonlite Software                        ÿ[1A
@ECHO [0;34;44m                       [1;37;44mCopyright (c) 1994 Apogee Software                      ÿ[00;37;40m[2A[s
IF "%1"=="/gus" GOTO SETGUS
IF "%1"=="/Gus" GOTO SETGUS
IF "%1"=="/gUs" GOTO SETGUS
IF "%1"=="/guS" GOTO SETGUS
IF "%1"=="/GUs" GOTO SETGUS
IF "%1"=="/gUS" GOTO SETGUS
IF "%1"=="/GUS" GOTO SETGUS
SET HOCUSGUS=FALSE
GOTO CHOICES

:SETGUS
SET HOCUSGUS=TRUE
GOTO CHOICES

:CHOICES
@CHOICE /N /C:PSTQ
IF ERRORLEVEL 4 GOTO EXIT
IF ERRORLEVEL 3 GOTO HELPSHEET
IF ERRORLEVEL 2 GOTO SETUP
IF ERRORLEVEL 1 GOTO GAME

:GAME
CLS
IF %HOCUSGUS%==TRUE GOTO GUSGAME
HOCUS.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
ECHO.
PAUSE > NUL
GOTO START

:GUSGAME
HOCUSG.BAT %2 %3 %4 %5 %6 %7 %8 %9
ECHO.
PAUSE > NUL
GOTO START

:SETUP
SETUP.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:HELPSHEET
IF EXIST HP-HELP.EXE HP-HELP.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
IF EXIST HPHELP.EXE HPHELP.EXE %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
