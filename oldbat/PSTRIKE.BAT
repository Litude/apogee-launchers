@ECHO OFF

:START
CLS
@ECHO [1;34m
@ECHO    пллпм  плл         плл                   млп      м
@ECHO     ллмп   лл   ммм    лл  мл    ммм        ппллм   лл    ммм  м ммм     ммм
@ECHO     лл лм  лл  ппмлл   ллмлп   млл лл          плл пллп  лл лл  лл лл  млл лл
@ECHO     лл лл  лл  мл лл   ллллм   ллпппп           лл  лл   лл лл  лл лл  ллпппп
@ECHO    мллмлп мллм плмппм млл пллм  плммп       пммлп   плмп плмлп млл ллм  плммп
@ECHO [33m
@ECHO [33mл мм  л[5Cлл[6Cм   млллм[6Cммммп
@ECHO л   л л[5Cл л[6Cл  лп   п  ппп л[39C[0;33m(tm)[10;1H[1;31mлппп  [33mл[5C[31mлммл [33mлл   л ллмм  л[5C[31mл    [33mммммм[6Cммммп лмммм мл л  лп млллм
@ECHO [0;31mл[5C[1mлллм  [0;31mл  л [1;33mл л  л [31mлм   мп    [0;31mл    [1;33mл[5Cпм ппп л    л  мп лл лмл   лп   п
@ECHO  [0;31mл[8Cп    л [1mл  л л [0;31mплллп[5Cп   [1mм  ппппм[7Cл    лппн  [33mлл лпм   ллмм  л[13;1H  [0;31mп[11Cл  л   лл[16Cпммммп[7Cл[5Cл  л  [1mол л  л  лм   мп[14;1H[13C[0;31mп[37Cп[8Cл    о   л   плллп
@ECHO [37m
@ECHO                       [1;41mлппппппппппппппппппппппппппппппппппл[0;40m
@ECHO                       [1;41mл   [33m1) [37mPlay                        [1;44mл[0;40m
@ECHO                       [1;41mл   [33m2) [37mSound Setup                 л[0;40m
@ECHO                       [1;41mл   [33m3) [37mTechnical Support           [1;44mл[0;40m
@ECHO                       [1;41mл   [33m4) [37mQuit                        л[0;40m
@ECHO                       [1;41mлммммммммммммммммммммммммммммммммммл[0;40m
@ECHO.
@ECHO [01;32m                          Developed by JAM Productions
@ECHO [01;35;40m                       Copyright (c) 1994 Apogee Software[00;37;40m
@ECHO [00;30;40mџ[00;37;40mџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџџ[00;37;40m[1A[s

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
