@ECHO OFF

:START
SET CHOICES=4
CLS
@ECHO [00;35;40m  �       �                             �              �                 
@ECHO [01;31;40m               �              �                                 �          
@ECHO [00;35;40m  �   �����˻ �����˻  ���˻   ����˻                                      
@ECHO [01;31;40m�     �����ʼ �����ʼ  ����λ  ����ι           �                          
@ECHO [00;35;40m      �����˻   �˻    �˻ ̹  ����ι  �                   �               
@ECHO [01;31;40m    � �����ι   �ι   ��ʼ ̹  ����μ        �                      �      
@ECHO [00;35;40m   ��������ι   �ι  ������ι  ̹ �λ   �����˻  ����˻  �����˻  �˻  �˻ 
@ECHO [01;31;40m   ��������ʼ   �ʼ  ������ʼ  ȼ  ȼ   �����ʼ  ����ι  �����ʼ  �ʼ  �ʼ 
@ECHO [00;35;40m     �                    �               �˻    ����ι  ���˻    ���˻    
@ECHO [01;31;40m �           �              �             �ι    ����μ  ���ʼ    ����λ   
@ECHO [00;35;40m       �                 �                �ι    ̹ �λ  �����˻  �ι ��˻ 
@ECHO [01;31;40m          �      �                    �   �ʼ    ȼ  ȼ  �����ʼ  �ʼ  �ʼ 
@ECHO [01;34;40m    �                                        The Next Generation: TRIVIA   
@ECHO [00;35;40m                             �           �           �                     
@ECHO [01;36;40m                   Copyright (C) 1990 By Micro F/X Software[01;31;40m        �     �
@ECHO [00;35;40m �          �    [01;33;40mProgram coding and design by George Broussard[00;35;40m          �
@ECHO [01;31;40m                    �       �                     �              �         
@ECHO [00;35;40m      �                           [00;34;40m1) Volume 1[00;35;40m                        �     
@ECHO [01;31;40m                                  [00;34;40m2) Volume 2[01;31;40m                          �   
@ECHO [00;35;40m    �          �        �         [00;34;40m3) Volume 3[00;35;40m          �                   
@ECHO [01;31;40m   �            �                 [01;34;40m4) Quit[01;31;40m                       �          
@ECHO [00;35;40m    �                     �                  �                         �   
@ECHO [01;31;40m                              �                          �                 
@ECHO [00;35;40m           �                                            �                  
@ECHO [00;30;40m�[01;31;40m    �           �            [00;31;40mYour selection... [05m�[00m[01;31;40m�����������������������������[00;37;40m[1A[s
GOTO EP3CHECK

:EP3CHECK
IF EXIST NGT3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%�
GOTO EP2CHECK

:EP2CHECK
IF EXIST NGT2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%�
GOTO EP1CHECK

:EP1CHECK
IF EXIST NGT1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%�
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
