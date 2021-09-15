@ECHO OFF

:START
SET CHOICES=4
CLS
@ECHO [00;35;40m  ù       ú                             ú              ø                 
@ECHO [01;31;40m               ù              ø                                 ø          
@ECHO [00;35;40m  ù   ÉËËËËË» ÉËËËËË»  ÉËËË»   ÉËËËË»                                      
@ECHO [01;31;40mù     ÌÎÊÊÊÊ¼ ÈÊÊÊÊÊ¼  ÈÊÊÊÎ»  ÈÊÊÊÎ¹           ù                          
@ECHO [00;35;40m      ÌÎËËËË»   ÉË»    ÉË» Ì¹  ÉËËËÎ¹  ù                   ù               
@ECHO [01;31;40m    ù ÈÊÊÊÎÎ¹   ÌÎ¹   ÉÎÊ¼ Ì¹  ÌÎÊÎÎ¼        ù                      ù      
@ECHO [00;35;40m   ÉËËËËËËÎÎ¹   ÌÎ¹  ÉÎÎËËËÎ¹  Ì¹ ÈÎ»   ÉËËËËË»  ÉËËËË»  ÉËËËËË»  ÉË»  ÉË» 
@ECHO [01;31;40m   ÈÊÊÊÊÊÊÊÊ¼   ÈÊ¼  ÈÊÊÊÊÊÊ¼  È¼  È¼   ÈÊÊÊÊÊ¼  ÈÊÊÊÎ¹  ÈÊÊÊÊÊ¼  ÈÊ¼  ÈÊ¼ 
@ECHO [00;35;40m     ù                    ù               ÉË»    ÉËËËÎ¹  ÉËËË»    ÉËËË»    
@ECHO [01;31;40m ø           ù              ù             ÌÎ¹    ÌÎÊÎÎ¼  ÌÎÊÊ¼    ÌÎÎÊÎ»   
@ECHO [00;35;40m       ú                 ù                ÌÎ¹    Ì¹ ÈÎ»  ÌÎËËËË»  ÌÎ¹ ÈÎË» 
@ECHO [01;31;40m          ø      ù                    ú   ÈÊ¼    È¼  È¼  ÈÊÊÊÊÊ¼  ÈÊ¼  ÈÊ¼ 
@ECHO [01;34;40m    ú                                        The Next Generation: TRIVIA   
@ECHO [00;35;40m                             ø           ú           ú                     
@ECHO [01;36;40m                   Copyright (C) 1990 By Micro F/X Software[01;31;40m        ø     ú
@ECHO [00;35;40m ú          ù    [01;33;40mProgram coding and design by George Broussard[00;35;40m          ù
@ECHO [01;31;40m                    ù       ú                     ú              ù         
@ECHO [00;35;40m      ù                           [00;34;40m1) Volume 1[00;35;40m                        ù     
@ECHO [01;31;40m                                  [00;34;40m2) Volume 2[01;31;40m                          ú   
@ECHO [00;35;40m    ù          ù        ú         [00;34;40m3) Volume 3[00;35;40m          ú                   
@ECHO [01;31;40m   ù            ú                 [01;34;40m4) Quit[01;31;40m                       ø          
@ECHO [00;35;40m    ù                     ø                  ú                         ø   
@ECHO [01;31;40m                              ø                          ú                 
@ECHO [00;35;40m           ú                                            ú                  
@ECHO [00;30;40mÿ[01;31;40m    ø           ù            [00;31;40mYour selection... [05mÛ[00m[01;31;40mÿÿÿÿÿÿÿÿÿÿùÿÿÿÿÿÿÿÿÿÿúÿÿÿÿÿÿÿ[00;37;40m[1A[s
GOTO EP3CHECK

:EP3CHECK
IF EXIST NGT3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP2CHECK

:EP2CHECK
IF EXIST NGT2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO EP1CHECK

:EP1CHECK
IF EXIST NGT1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%ÿ
GOTO CHOICES

:EP3ENABLE
SET CHOICES=%CHOICES%3
@ECHO [20;35H[01;34;40m3) Volume 3[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [19;35H[01;34;40m2) Volume 2[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [18;35H[01;34;40m1) Volume 1[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 4 GOTO NGT1
IF ERRORLEVEL 3 GOTO NGT2
IF ERRORLEVEL 2 GOTO NGT3
IF ERRORLEVEL 1 GOTO EXIT

:NGT1
CLS
NGT1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:NGT2
CLS
NGT2 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:NGT3
CLS
NGT3 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
