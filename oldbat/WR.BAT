@ECHO OFF

:START
CLS
@ECHO  [00;35;40m�����������[01;37;45m                                                        [00;35;40m�����������
@ECHO  [00;35;40m�����������[01;33;45m� � � ��Ŀ ��Ŀ ���Ŀ      ��Ŀ ��Ŀ ��Ŀ ��Ŀ �  � ��Ŀ[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;33;45m� � � �  � ����  �  �      ���� ��   ��Ŀ �    �  � ��  [00;35;40m�����������
@ECHO  [00;35;40m�����������[01;33;45m����� ���� � �� �����      � �� ���� ���� ���� ���� ����[00;35;40m�����������
@ECHO  [00;35;40m�����������[00;30;45m                                                        [00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;45m           Copyright (c)  Karen Crowther 1992           [00;35;40m�����������
@ECHO  [00;35;40m�����������[01;36;45m              Published by Apogee Software              [00;35;40m�����������
@ECHO  [00;35;40m�����������[00;30;45m                                                        [00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;46m������������������������������������������������������ͻ[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;46m�[00;30;46m��������������� Episode Selection Menu ���������������[01;37;46m�[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;46m������������������������������������������������������ͼ[00;35;40m�����������
@ECHO  [00;35;40m�����������[00;30;45m                                                        [00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;46m������������������������������������������������������ͻ[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;46m�[01;36;46m     1) Visit Gruzzleville and the Castle             [01;37;46m�[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;46m�[01;36;46m     2) Explore GruzzleBad Caverns                    [01;37;46m�[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;46m�[01;36;46m     3) See the Spooky Haunted House                  [01;37;46m�[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;46m������������������������������������������������������ͼ[00;35;40m�����������
@ECHO  [00;35;40m�����������[00;30;45m                                                        [00;35;40m�����������
@ECHO  [00;35;40m�����������[00;30;45m                                                        [00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;46m������������������������������������������������������ͻ[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;46m�[01;37;46m     4) [00;30;46mQuit                                          [01;37;46m�[00;35;40m�����������
@ECHO  [00;35;40m�����������[01;37;46m������������������������������������������������������ͼ[00;35;40m�����������
@ECHO  [00;35;40m�����������[00;30;45m                                                        [00;35;40m�����������
@ECHO  [00;35;40m�����������[00;30;45m                                                        [00;35;40m�����������
@ECHO [00;30;40m�[00;35;40m�����������[00;30;45m                                                        [00;35;40m�����������[00;37;40m[1A[s
GOTO COSMETICS

:COSMETICS
IF EXIST REDWOOD GOTO COSREDW
IF EXIST VENDINFO.DIZ GOTO COSREDW
IF EXIST DESCRIBE.TMP GOTO COSREDW
IF EXIST WRPLUS.EXE GOTO COSREDW
GOTO PLUSCHECK

:COSREDW
@ECHO [06;57H[01;37;45m4[00;37;40m[u
@ECHO [07;27H[01;36;45m Published by Redwood Games [00;37;40m[u
GOTO PLUSCHECK

:PLUSCHECK
IF EXIST WRPLUS.EXE GOTO PLUSENABLE
SET CHOICES=4�
GOTO EP3CHECK

:EP3CHECK
IF EXIST WR3.EXE GOTO EP3ENABLE
SET CHOICES=%CHOICES%�
GOTO EP2CHECK

:EP2CHECK
IF EXIST WR2.EXE GOTO EP2ENABLE
SET CHOICES=%CHOICES%�
GOTO EP1CHECK

:EP1CHECK
IF EXIST WR1.EXE GOTO EP1ENABLE
SET CHOICES=%CHOICES%�
GOTO CHOICES

:PLUSENABLE
SET CHOICES=54
@ECHO [17;13H[01;37;46m�     [01;37;46m4) [00;30;46mWord Rescue Plus                              [01;37;46m�[00;37;40m[u
@ECHO [18;13H[01;37;46m������������������������������������������������������ͼ[00;37;40m[u
@ECHO [21;19H[01;37;46m5)[00;37;40m[u
GOTO EP3CHECK

:EP3ENABLE
SET CHOICES=%CHOICES%3
@ECHO [16;19H[01;37;46m3) [00;30;46mSee the Spooky Haunted House[00;37;40m[u
GOTO EP2CHECK

:EP2ENABLE
SET CHOICES=%CHOICES%2
@ECHO [15;19H[01;37;46m2) [00;30;46mExplore GruzzleBad Caverns[00;37;40m[u
GOTO EP1CHECK

:EP1ENABLE
SET CHOICES=%CHOICES%1
@ECHO [14;19H[01;37;46m1) [00;30;46mVisit Gruzzleville and the Castle[00;37;40m[u
GOTO CHOICES

:CHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 5 GOTO WR1
IF ERRORLEVEL 4 GOTO WR2
IF ERRORLEVEL 3 GOTO WR3
IF ERRORLEVEL 2 GOTO WRPLUS
IF ERRORLEVEL 1 GOTO EXIT

:WR1
CLS
WR1 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:WR2
CLS
WR2 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:WR3
CLS
WR3 %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:WRPLUS
CLS
WRPLUS %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO START

:EXIT
CLS
