@ECHO OFF

:START
SET CHOICES=6
CLS
@ECHO.
@ECHO [01;34;40m             ÉËËËË»  ÉËËË»    ÉËËËË»  É»    É»  ÉËËËË»      É»     
@ECHO [00;34;40m             ÈÊÎÎÊ¼  ÌÎÊÊÎ»   ÈÊÎÎÊ¼  Ì¹    Ì¹  ÈÊÎÎÊ¼     ÉÎÎ»    
@ECHO [01;34;40m               Ì¹    ÌÎËËÎ¼     Ì¹    ÈÎ»  ÉÎ¼    Ì¹      ÉÎÊÊÎ»   
@ECHO [00;34;40m               Ì¹    ÌÎÊÊÎ»     Ì¹     ÈÎËËÎ¼     Ì¹     ÉÎÎËËÎÎ»  
@ECHO [01;34;40m               Ì¹    Ì¹  ÈÎ»  ÉËÎÎË»    ÈÎÎ¼    ÉËÎÎË»  ÉÎÊÊÊÊÊÊÎ» 
@ECHO [00;34;40m               È¼    È¼   È¼  ÈÊÊÊÊ¼     È¼     ÈÊÊÊÊ¼  È¼      È¼ 
@ECHO [00;34;40m                       É»    É»  É»  É»  ÉËËËË»  ÉËËËËË»         
@ECHO [01;34;40m                       Ì¹ É» Ì¹  Ì¹  Ì¹  ÈÊÎÎÊ¼  ÈÊÊÊÎÎ¼         
@ECHO [00;34;40m                       Ì¹ÉÎÎ»Ì¹  ÌÎËËÎ¹    Ì¹      ÉËÎ¼          
@ECHO [01;34;40m                       ÌÎÎ¼ÈÎÎ¹  ÌÎÊÊÎ¹    Ì¹     ÉÎÊ¼           
@ECHO [00;34;40m                       ÌÎ¼  ÈÎ¹  Ì¹  Ì¹  ÉËÎÎË»  ÉÎÎËËË»         
@ECHO [01;34;40m                       È¼    È¼  È¼  È¼  ÈÊÊÊÊ¼  ÈÊÊÊÊÊ¼       
@ECHO.  
@ECHO [00;35;40m                   Copyright (C) 1990 By Micro F/X Software
@ECHO [00;33;40m                 Program coding and design by George Broussard
@ECHO.
@ECHO [00;31;40m                                  1) Volume 1
@ECHO [00;31;40m                                  2) Volume 2
@ECHO [00;31;40m                                  3) Volume 3
@ECHO [00;31;40m                                  4) Volume 4
@ECHO [00;31;40m                                  5) Volume 5
@ECHO [01;31;40m                                  6) Quit
@ECHO.
@ECHO [00;30;40mÿ[01;32;40m                               Your selection [05mÛ[00mÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ[00;37;40m[1A[s
GOTO EP5CHECK

:EP5CHECK
IF EXIST TW5.EXE GOTO EP5ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP4CHECK

:EP4CHECK
IF EXIST TW4.EXE GOTO EP4ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP3CHECK

:EP3CHECK
IF EXIST TW3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP2CHECK

:EP2CHECK
IF EXIST TW2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP1CHECK

:EP1CHECK
IF EXIST TW1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO CHOICES

:EP5ENABLE
SET CHOICES=%CHOICES%5
@ECHO [22;35H[01;31;40m5) Volume 5[00;37;40m[u
GOTO EP4CHECK

:EP4ENABLE
SET CHOICES=%CHOICES%4
@ECHO [21;35H[01;31;40m4) Volume 4[00;37;40m[u
GOTO EP3CHECK

:EP3ENABLE
SET CHOICES=%CHOICES%3
@ECHO [20;35H[01;31;40m3) Volume 3[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [19;35H[01;31;40m2) Volume 2[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [18;35H[01;31;40m1) Volume 1[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 6 GOTO TW1
IF ERRORLEVEL 5 GOTO TW2
IF ERRORLEVEL 4 GOTO TW3
IF ERRORLEVEL 3 GOTO TW4
IF ERRORLEVEL 2 GOTO TW5
IF ERRORLEVEL 1 GOTO EXIT

:TW1
CLS
TW1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:TW2
CLS
TW2 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:TW3
CLS
TW3 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:TW4
CLS
TW4 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:TW5
CLS
TW5 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
