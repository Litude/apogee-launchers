@ECHO OFF
SET SELECTION=1
:START
KEENGG.EXE %SELECTION%
IF ERRORLEVEL 7 GOTO KEEN5_EXE
IF ERRORLEVEL 6 GOTO KEEN5C_EXE
IF ERRORLEVEL 5 GOTO KEEN5E_EXE
IF ERRORLEVEL 4 GOTO KEEN4_EXE
IF ERRORLEVEL 3 GOTO KEEN4C_EXE
IF ERRORLEVEL 2 GOTO KEEN4E_EXE
IF ERRORLEVEL 1 GOTO KEEN_EXE
GOTO END

:KEEN5_EXE
SET SELECTION=2
SET EXENAME=KEEN5.EXE
GOTO RUN

:KEEN5C_EXE
SET SELECTION=2
SET EXENAME=KEEN5C.EXE
GOTO RUN

:KEEN5E_EXE
SET SELECTION=2
SET EXENAME=KEEN5E.EXE
GOTO RUN

:KEEN4_EXE
SET SELECTION=1
SET EXENAME=KEEN4.EXE
GOTO RUN

:KEEN4C_EXE
SET SELECTION=1
SET EXENAME=KEEN4C.EXE
GOTO RUN

:KEEN4E_EXE
SET SELECTION=1
SET EXENAME=KEEN4E.EXE
GOTO RUN

:KEEN_EXE
SET SELECTION=1
SET EXENAME=KEEN.EXE
GOTO RUN

:RUN
%EXENAME% %1 %2 %3 %4 %5 %6 %7 %8 %9
IF NOT ERRORLEVEL 1 GOTO EXTEND
PAUSE > NUL
GOTO START

:EXTEND
@ECHO [25;00f[00;34;40m������������[00;30;44m                                                        [00;34;40m�����������[00;37;40m[79D[1A
PAUSE > NUL
GOTO START

:END
SET SELECTION=
SET EXENAME=
