@ECHO OFF

:START
SET CHOICES=6
CLS
@ECHO.
@ECHO [01;34;40m             ����˻  ���˻    ����˻  ɻ    ɻ  ����˻      ɻ     
@ECHO [00;34;40m             ����ʼ  ����λ   ����ʼ  ̹    ̹  ����ʼ     ��λ    
@ECHO [01;34;40m               ̹    ����μ     ̹    �λ  �μ    ̹      ����λ   
@ECHO [00;34;40m               ̹    ����λ     ̹     ����μ     ̹     ������λ  
@ECHO [01;34;40m               ̹    ̹  �λ  ����˻    ��μ    ����˻  ��������λ 
@ECHO [00;34;40m               ȼ    ȼ   ȼ  ����ʼ     ȼ     ����ʼ  ȼ      ȼ 
@ECHO [00;34;40m                       ɻ    ɻ  ɻ  ɻ  ����˻  �����˻         
@ECHO [01;34;40m                       ̹ ɻ ̹  ̹  ̹  ����ʼ  �����μ         
@ECHO [00;34;40m                       ̹��λ̹  ����ι    ̹      ��μ          
@ECHO [01;34;40m                       ��μ��ι  ����ι    ̹     ��ʼ           
@ECHO [00;34;40m                       �μ  �ι  ̹  ̹  ����˻  �����˻         
@ECHO [01;34;40m                       ȼ    ȼ  ȼ  ȼ  ����ʼ  �����ʼ       
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
@ECHO [00;30;40m�[01;32;40m                               Your selection [05m�[00m�������������������������������[00;37;40m[1A[s
GOTO EP5CHECK

:EP5CHECK
IF EXIST TW5.EXE GOTO EP5ENABLE
SET CHOICES=%CHOICES%�
GOTO EP4CHECK

:EP4CHECK
IF EXIST TW4.EXE GOTO EP4ENABLE
SET CHOICES=%CHOICES%�
GOTO EP3CHECK

:EP3CHECK
IF EXIST TW3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%�
GOTO EP2CHECK

:EP2CHECK
IF EXIST TW2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%�
GOTO EP1CHECK

:EP1CHECK
IF EXIST TW1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%�
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
