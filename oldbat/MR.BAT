@ECHO OFF

:START
CLS
@ECHO  [00;35;40m�����������[01;37;45m                                                        [00;35;40m�����������
@ECHO  [00;35;40m�����������[01;36;45m���Ŀ ��Ŀ ���Ŀ �  �      ��Ŀ ��Ŀ ��Ŀ ��Ŀ �  � ��Ŀ[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;36;45m� � � ��Ĵ   �   ��Ĵ      ���� ��   ��Ŀ �    �  � ��  [00;35;40m�����������
@ECHO  [00;35;40m�����������[01;36;45m� � � �  �   �   �  �      � �� ���� ���� ���� ���� ����[00;35;40m�����������
@ECHO  [00;35;40m�����������[00;30;45m                                                        [00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;45m           Copyright (c)  Karen Crowther 1992           [00;35;40m�����������
@ECHO  [00;35;40m�����������[01;34;45m              Published by Apogee Software              [00;35;40m�����������
@ECHO  [00;35;40m�����������[00;30;45m                                                        [00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;44m������������������������������������������������������ͻ[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;44m�[01;37;44m��������������� Episode Selection Menu ���������������[01;37;44m�[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;44m������������������������������������������������������ͼ[00;35;40m�����������
@ECHO  [00;35;40m�����������[00;30;45m                                                        [00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;44m������������������������������������������������������ͻ[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;44m�[01;34;44m     1) Visit Volcanos and Ice Caves                  [01;37;44m�[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;44m�[01;34;44m     2) Follow the Gruzzles into Space                [01;37;44m�[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;44m�[01;34;44m     3) See Candy Land                                [01;37;44m�[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;44m������������������������������������������������������ͼ[00;35;40m�����������
@ECHO  [00;35;40m�����������[00;30;45m                                                        [00;35;40m�����������
@ECHO  [00;35;40m�����������[00;30;45m                                                        [00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;44m������������������������������������������������������ͻ[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;44m�[01;33;44m     4) [01;37;44mQuit                                          [01;37;44m�[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;44m������������������������������������������������������ͼ[00;35;40m�����������
@ECHO  [00;35;40m�����������[00;30;45m                                                        [00;35;40m�����������
@ECHO  [00;35;40m�����������[00;30;45m                                                        [00;35;40m�����������
@ECHO [00;30;40m�[00;35;40m�����������[00;30;45m                                                        [00;35;40m�����������[00;37;40m[1A[s
GOTO COSMETICS

:COSMETICS
IF EXIST REDWOOD GOTO COSREDW
IF EXIST VENDINFO.DIZ GOTO COSREDW
IF EXIST DESCRIBE.TMP GOTO COSREDW
IF EXIST MRPLUS.EXE GOTO COSREDW
GOTO PLUSCHECK

:COSREDW
@ECHO [06;57H[01;37;45m4[00;37;40m[u
@ECHO [07;27H[01;34;45m Published by Redwood Games [00;37;40m[u
GOTO PLUSCHECK

:PLUSCHECK
IF EXIST MRPLUS.EXE GOTO PLUSENABLE
SET CHOICES=4�
GOTO EP3CHECK

:EP3CHECK
IF EXIST MR3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%�
GOTO EP2CHECK

:EP2CHECK
IF EXIST MR2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%�
GOTO EP1CHECK

:EP1CHECK
IF EXIST MR1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%�
GOTO CHOICES

:PLUSENABLE
SET CHOICES=54
@ECHO [17;13H[01;37;44m�     [01;33;44m4) [01;37;44mMath Rescue Plus                              [01;37;44m�[00;37;40m[u
@ECHO [18;13H[01;37;44m������������������������������������������������������ͼ[00;37;40m[u
@ECHO [21;19H[01;33;44m5)[00;37;40m[u
GOTO EP3CHECK

:EP3ENABLE
SET CHOICES=%CHOICES%3
@ECHO [16;19H[01;33;44m3) [01;37;44mSee Candy Land[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [15;19H[01;33;44m2) [01;37;44mFollow the Gruzzles into Space[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [14;19H[01;33;44m1) [01;37;44mVisit Volcanos and Ice Caves[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 5 GOTO MR1
IF ERRORLEVEL 4 GOTO MR2
IF ERRORLEVEL 3 GOTO MR3
IF ERRORLEVEL 2 GOTO MRPLUS
IF ERRORLEVEL 1 GOTO EXIT

:MR1
CLS
MR1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:MR2
CLS
MR2 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:MR3
CLS
MR3 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:MRPLUS
CLS
MRPLUS %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
