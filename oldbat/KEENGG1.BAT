@ECHO OFF

:START
SET CHOICES=3
CLS
@ECHO  [00;34;40m�����������[01;37;44m��ͻ                                   �  �             [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;37;44m�                                      � ɼ             [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;37;44m�    �ͻ �˻ �˻ �ͻ ˻ � �ͻ �ͻ �ͻ  �͹  �ͻ �ͻ ˻ �[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;37;44m�    � � � � � � �͹ �Ȼ� � � ��  �͹  � Ȼ ��  ��  �Ȼ�[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;37;44m��ͼ �ͼ � � � � � � � ȼ �ͼ �ͼ � �  �  � �ͼ �ͼ � ȼ[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;33;44m�Ŀ �Ŀ �Ŀ �Ŀ �Ŀ � � �Ŀ     �Ŀ �Ŀ �   �Ŀ ڿڿ � �[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;33;44m� � � � � � � � �Ĵ ��� ô      � � �Ĵ �   �Ĵ  ô  ���[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;33;44m��� ��� ��� ��� ���  �  ��� �   ��� � � ��� � � ����  � [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;36;44m            Copyright 1991 Id Software Inc.             [00;34;40m�����������
@ECHO  [00;34;40m�����������[00;36;44m             Published by Apogee Software               [00;34;40m�����������
@ECHO  [00;34;40m�����������[00;30;44m                                                        [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m������������������������������������������������������ͻ[00;30;44m[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m�[01;37;45m Select a Video Mode                                  [01;35;45m�[00;30;44m[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m�[01;37;45m                                                      [01;35;45m�[00;30;44m[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m�[01;35;45m     1) CGA                                  4 Colors [01;35;45m�[00;30;44m[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m�[01;35;45m     2) EGA                                 16 Colors [01;35;45m�[00;30;44m[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m������������������������������������������������������ͼ[00;30;44m[00;34;40m�����������
@ECHO  [00;34;40m�����������[00;30;44m                                                        [00;34;40m�����������
@ECHO  [00;34;40m�����������[00;30;44m                                                        [00;34;40m�����������
@ECHO  [00;34;40m�����������[00;30;44m                                                        [00;34;40m�����������
@ECHO  [00;34;40m�����������[00;30;44m                                                        [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m������������������������������������������������������ͻ[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m�[01;37;45m     3) Exit                                          [01;35;45m�[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m������������������������������������������������������ͼ[00;34;40m�����������[00;37;40m
@ECHO [00;34;40m������������[00;30;44m                                                        [00;34;40m�����������[00;37;40m[79D[1A[s
GOTO COSMETICS

:COSMETICS
IF EXIST GG-HINT.EXE GOTO COS92
IF EXIST GGHINT.EXE GOTO COS92
IF EXIST DEALERS.EXE GOTO COS92
IF EXIST SWCBBS.EXE GOTO COS92
IF EXIST KEEN5.EXE GOTO COSGT
IF EXIST KEEN4.EXE GOTO COSGT
IF EXIST KEEN.EXE GOTO COSFGDM
IF %CHOICES% == EGA GOTO EP5ECHECK
IF %CHOICES% == CGA GOTO EP5CCHECK
GOTO EGACHECK

:COS92
@ECHO [09;38H[01;36;44m2[00;37;40m[u
IF %CHOICES% == EGA GOTO EP5ECHECK
IF %CHOICES% == CGA GOTO EP5CCHECK
GOTO EGACHECK

:COSFGDM
@ECHO [10;24H[01;33;44m      SPECIAL DEMO VERSION      [00;37;40m[u
IF %CHOICES% == EGA GOTO EP5ECHECK
GOTO DEMOENABLE

:COSGT
@ECHO [09;38H[01;36;44m2[00;37;40m[u
@ECHO [10;25H[00;36;44mPublished by Goodtimes Software[00;37;40m[u
GOTO GTENABLE

:EGACHECK
IF EXIST KEEN4E.EXE GOTO EGAENABLE
IF EXIST KEEN5E.EXE GOTO EGAENABLE
SET CHOICES=%CHOICES%�
GOTO CGACHECK

:CGACHECK
IF EXIST KEEN4C.EXE GOTO CGAENABLE
IF EXIST KEEN5C.EXE GOTO CGAENABLE
SET CHOICES=%CHOICES%�
GOTO VIDEOMODE

:EGAENABLE
SET CHOICES=%CHOICES%2
@ECHO [16;19H[01;37;45m2) EGA                                 16 Colors[00;37;40m[u
GOTO CGACHECK

:CGAENABLE
SET CHOICES=%CHOICES%1
@ECHO [15;19H[01;37;45m1) CGA                                  4 Colors[00;37;40m[u
GOTO VIDEOMODE

:DEMOENABLE
SET CHOICES=%CHOICES%2�
@ECHO [16;19H[01;37;45m2) EGA                                 16 Colors[00;37;40m[u
GOTO VIDEOMODE

:GTENABLE
SET CHOICES=32
@ECHO [12;13H[01;35;45m������������������������������������������������������ͻ[u
@ECHO [13;13H[01;35;45m�[01;37;45m Select an Episode                                    [01;35;45m�[u
@ECHO [14;13H[01;35;45m�[01;37;45m                                                      [01;35;45m�[u
@ECHO [15;13H[01;35;45m�[01;35;45m     1) Secret of the Oracle               Episode IV [01;35;45m�[u
@ECHO [16;13H[01;35;45m�[01;35;45m     2) The Armageddon Machine             Episode  V [01;35;45m�[u
@ECHO [17;13H[01;35;45m������������������������������������������������������ͼ[00;37;40m[u
GOTO EP5ECHECK

:VIDEOMODE
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 3 GOTO CGACONF
IF ERRORLEVEL 2 GOTO EGACONF
IF ERRORLEVEL 1 GOTO EXIT

:CGACONF
SET CHOICES=CGA
IF EXIST CGACONF.CKG GOTO EPISODES
IF EXIST EGACONF.CKG GOTO SAVE
@ECHO �>>CGACONF.CKG
GOTO EPISODES

:EGACONF
SET CHOICES=EGA
IF EXIST EGACONF.CKG GOTO EPISODES
IF EXIST CGACONF.CKG GOTO SAVE
@ECHO �>>EGACONF.CKG
GOTO EPISODES

:SAVE
IF EXIST SAVEGAM0.* GOTO WARNING
IF EXIST SAVEGAM1.* GOTO WARNING
IF EXIST SAVEGAM2.* GOTO WARNING
IF EXIST SAVEGAM3.* GOTO WARNING
IF EXIST SAVEGAM4.* GOTO WARNING
IF EXIST SAVEGAM5.* GOTO WARNING
IF EXIST SAVEGAM6.* GOTO WARNING
IF EXIST SAVEGAM7.* GOTO WARNING
IF EXIST SAVEGAM8.* GOTO WARNING
IF EXIST SAVEGAM9.* GOTO WARNING
GOTO CHG%CHOICES%

:WARNING
@ECHO [12;13H[01;31;41m������������������������������������������������������ͻ[u
@ECHO [13;13H[01;31;41m�[05;33;41m      WARNING!   WARNING!   WARNING!   WARNING!       [00m[01;31;41m�[u
@ECHO [14;13H[01;31;41m�[01;37;41m                                                      [01;31;41m�[u
@ECHO [15;13H[01;31;41m�[01;37;41m Changing video mode may cause you to lose all your   [01;31;41m�[u
@ECHO [16;13H[01;31;41m�[01;37;41m current saved games reset your game options.         [01;31;41m�[u
@ECHO [17;13H[01;31;41m�[01;37;41m                                                      [01;31;41m�[u
@ECHO [18;13H[01;31;41m��������������[01;33;41mDO YOU WISH TO PROCEED? [Y/N][01;31;41m�����������ͼ[u
@ECHO [23;19H[01;35;45m3) Exit[00;37;40m[u
@CHOICE /N >> NUL
IF ERRORLEVEL 2 GOTO START
IF ERRORLEVEL 1 GOTO CHG%CHOICES%

:CHGCGA
DEL EGACONF.CKG
@ECHO �>>CGACONF.CKG
GOTO EPISODES

:CHGEGA
DEL CGACONF.CKG
@ECHO �>>EGACONF.CKG
GOTO EPISODES

:EPISODES
@ECHO [12;13H[01;35;45m������������������������������������������������������ͻ[u
@ECHO [13;13H[01;35;45m�[01;37;45m Select an Episode                                    [01;35;45m�[u
@ECHO [14;13H[01;35;45m�[01;37;45m                                                      [01;35;45m�[u
@ECHO [15;13H[01;35;45m�[01;35;45m     1) Secret of the Oracle               Episode IV [01;35;45m�[u
@ECHO [16;13H[01;35;45m�[01;35;45m     2) The Armageddon Machine             Episode  V [01;35;45m�[u
@ECHO [17;13H[01;35;45m������������������������������������������������������ͼ[u
@ECHO [18;13H[00;30;44m                                                        [u
@ECHO [23;19H[01;37;45m3) Exit[00;37;40m[u
IF %CHOICES% == EGA GOTO EP5ECHECK
IF %CHOICES% == CGA GOTO EP5CCHECK

:EP5ECHECK
SET CHOICES=3
IF EXIST KEEN5.EXE GOTO EP5EENABLE
IF EXIST KEEN5E.EXE GOTO EP5EENABLE
SET CHOICES=%CHOICES%�
GOTO EP4ECHECK

:EP4ECHECK
IF EXIST KEEN4.EXE GOTO EP4EENABLE
IF EXIST KEEN4E.EXE GOTO EP4EENABLE
IF EXIST KEEN.EXE GOTO EP4DMENABLE
SET CHOICES=%CHOICES%�
GOTO ECHOICES

:EP5CCHECK
SET CHOICES=3
IF EXIST KEEN5C.EXE GOTO EP5CENABLE
SET CHOICES=%CHOICES%�
GOTO EP4CCHECK

:EP4CCHECK
IF EXIST KEEN4C.EXE GOTO EP4CENABLE
SET CHOICES=%CHOICES%�
GOTO CCHOICES

:EP5EENABLE
SET CHOICES=%CHOICES%2
@ECHO [16;19H[01;37;45m2) The Armageddon Machine             Episode  V[00;37;40m[u
GOTO EP4ECHECK

:EP4EENABLE
SET CHOICES=%CHOICES%1
@ECHO [15;19H[01;37;45m1) Secret of the Oracle               Episode IV[00;37;40m[u
GOTO ECHOICES

:EP5CENABLE
SET CHOICES=%CHOICES%2
@ECHO [16;19H[01;37;45m2) The Armageddon Machine             Episode  V[00;37;40m[u
GOTO EP4CCHECK

:EP4CENABLE
SET CHOICES=%CHOICES%1
@ECHO [15;19H[01;37;45m1) Secret of the Oracle               Episode IV[00;37;40m[u
GOTO CCHOICES

:EP4DMENABLE
SET CHOICES=3�1
@ECHO [16;19H[01;35;45m2) The Armageddon Machine             Episode  V[00;37;40m[u
@ECHO [15;19H[01;37;45m1) Secret of the Oracle               Episode IV[00;37;40m[u
GOTO ECHOICES

:ECHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 3 GOTO KEEN4E
IF ERRORLEVEL 2 GOTO KEEN5E
IF ERRORLEVEL 1 GOTO EXIT

:CCHOICES
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 3 GOTO KEEN4C
IF ERRORLEVEL 2 GOTO KEEN5C
IF ERRORLEVEL 1 GOTO EXIT

:KEEN5E
IF EXIST KEEN5.EXE GOTO KEEN5
IF EXIST KEEN5E.EXE GOTO KEEN5EN

:KEEN5EN
KEEN5E %1 %2 %3 %4 %5 %6 %7 %8 %9
SET CHOICES=EGA
GOTO POSTEPI

:KEEN5
KEEN5 %1 %2 %3 %4 %5 %6 %7 %8 %9
SET CHOICES=EGA
GOTO POSTEPI

:KEEN4E
IF EXIST KEEN4.EXE GOTO KEEN4
IF EXIST KEEN4E.EXE GOTO KEEN4EN
IF EXIST KEEN.EXE GOTO KEENDEMO

:KEEN4EN
KEEN4E %1 %2 %3 %4 %5 %6 %7 %8 %9
SET CHOICES=EGA
GOTO POSTEPI

:KEEN4
KEEN4 %1 %2 %3 %4 %5 %6 %7 %8 %9
SET CHOICES=EGA
GOTO POSTEPI

:KEENDEMO
KEEN %1 %2 %3 %4 %5 %6 %7 %8 %9
SET CHOICES=EGA
GOTO POSTEPI

:KEEN5C
KEEN5C %1 %2 %3 %4 %5 %6 %7 %8 %9
SET CHOICES=CGA
GOTO POSTEPI

:KEEN4C
KEEN4C %1 %2 %3 %4 %5 %6 %7 %8 %9
SET CHOICES=CGA
GOTO POSTEPI

:POSTEPI
@ECHO  [00;34;40m�����������[01;37;44m��ͻ                                   �  �             [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;37;44m�                                      � ɼ             [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;37;44m�    �ͻ �˻ �˻ �ͻ ˻ � �ͻ �ͻ �ͻ  �͹  �ͻ �ͻ ˻ �[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;37;44m�    � � � � � � �͹ �Ȼ� � � ��  �͹  � Ȼ ��  ��  �Ȼ�[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;37;44m��ͼ �ͼ � � � � � � � ȼ �ͼ �ͼ � �  �  � �ͼ �ͼ � ȼ[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;33;44m�Ŀ �Ŀ �Ŀ �Ŀ �Ŀ � � �Ŀ     �Ŀ �Ŀ �   �Ŀ ڿڿ � �[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;33;44m� � � � � � � � �Ĵ ��� ô      � � �Ĵ �   �Ĵ  ô  ���[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;33;44m��� ��� ��� ��� ���  �  ��� �   ��� � � ��� � � ����  � [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;36;44m            Copyright 1991 Id Software Inc.             [00;34;40m�����������
@ECHO  [00;34;40m�����������[00;36;44m             Published by Apogee Software               [00;34;40m�����������
@ECHO  [00;34;40m�����������[00;30;44m                                                        [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m������������������������������������������������������ͻ[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m�[01;37;45m Select an Episode                                    [01;35;45m�[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m�[01;37;45m                                                      [01;35;45m�[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m�[01;35;45m     1) Secret of the Oracle               Episode IV [01;35;45m�[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m�[01;35;45m     2) The Armageddon Machine             Episode  V [01;35;45m�[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m������������������������������������������������������ͼ[00;34;40m�����������
@ECHO  [00;34;40m�����������[00;30;44m                                                        [00;34;40m�����������
@ECHO  [00;34;40m�����������[00;30;44m                                                        [00;34;40m�����������
@ECHO  [00;34;40m�����������[00;30;44m                                                        [00;34;40m�����������
@ECHO  [00;34;40m�����������[00;30;44m                                                        [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m������������������������������������������������������ͻ[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m�[01;37;45m     3) Exit                                          [01;35;45m�[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m������������������������������������������������������ͼ[00;34;40m�����������[00;37;40m
@ECHO [00;34;40m������������[00;30;44m                                                        [00;34;40m�����������[00;37;40m[79D[1A[s
GOTO COSMETICS

:EXIT
CLS
