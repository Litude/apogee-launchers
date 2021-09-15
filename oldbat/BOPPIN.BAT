@ECHO OFF
:START
CLS
:DRAWLOGO
@ECHO [1;36m
@ECHO [35m                                                              [33m   лллллллллл
@ECHO [35m  плллпплм    мллпллм  плллпплм плллпплм плллп пллл   лп ллл  [33m    лл лл лл
@ECHO [35m   лллммлп   оллн оллн  лллммлп  лллммлп  ллл   лллл  л  ппл  [33m я   лллллл
@ECHO [35m   ллл пллм  ллл   ллл  ллл      ллл      ллл   л ллл л  пп   [33m  \   лллл     я
@ECHO [35m   ллл  пллн ллл   ллл  ллл      ллл      ллл   л  лллл       [33m   \ЭЭЭлл\    /
@ECHO [35m   ллл   ллн ллл   ллл  ллл      ллл      ллл   л   ллл       [31m       лл[33m \  /
@ECHO [35m   ллл   ллн оллн оллн  ллл      ллл      ллл   л    лл       [31m      л л[33m  \/
@ECHO [35m  млллммллп   пллмллп  мллл     мллл     млллм мл     л [0;35m(tm)  [1;31m     л  л
@ECHO [34m                                                              [31m    л   л
@ECHO [34m                  Developed by Accursed Toys                  [31m   л    л
@ECHO [32m                                                              [31m  л     л[33m

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
@ECHO [33m   лллллллллл
@ECHO [33m    лл лл лл                     [33m         P[36mlay
@ECHO [33m я   лллллл   я
@ECHO [33m  \   лллл   /                   [33m         S[36metup
@ECHO [33m   \ЭЭЭллЭЭЭ/  
@ECHO [32m       лл                        [33m   T[36mechnical Support
@ECHO [32m      л  л
@ECHO [32m      л  л                       [33m         Q[36muit
@ECHO [32m     л    л   
@ECHO [32m    л      л   
@ECHO [32m    л      л [37m               Copyright (c) 1994 Apogee Software
@ECHO [0;30m                                                                              џ[00;37;40m[1A[s

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
