@ECHO OFF

:INIT
IF EXIST KEEN6E.EXE GOTO START
IF EXIST KEEN6C.EXE GOTO START
IF EXIST KEEN6.EXE GOTO INCOMP
GOTO START

:START
SET CHOICES=3
CLS
@ECHO  [00;34;40m�����������[01;37;44m��ͻ                                   �  �             [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;37;44m�                                      � ɼ             [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;37;44m�    �ͻ �˻ �˻ �ͻ ˻ � �ͻ �ͻ �ͻ  �͹  �ͻ �ͻ ˻ �[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;37;44m�    � � � � � � �͹ �Ȼ� � � ��  �͹  � Ȼ ��  ��  �Ȼ�[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;37;44m��ͼ �ͼ � � � � � � � ȼ �ͼ �ͼ � �  �  � �ͼ �ͼ � ȼ[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;31;44m     �Ŀ �   � �Ŀ ¿ � �Ŀ   �Ŀ �¿ �Ŀ   �¿ � �     [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;31;44m     �Ĵ �   � ô  ���� �Ŀ   �Ĵ  �  ô    � � ���     [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;31;44m     � � ��� � ��� � �� ���   � �  �  ���   � �  �      [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;31;44m         �Ŀ �Ŀ �Ŀ � �   �Ŀ � �¿ �¿ �Ŀ �Ŀ        [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;31;44m         �Ĵ �Ĵ �Ĵ ���   �Ŀ �  �   �  ô  �Ĵ        [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;31;44m         ��� � � ���  �    ��� �  �   �  ��� � �        [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;36;44m            Copyright 1991 Id Software Inc.             [00;34;40m�����������
@ECHO  [00;34;40m�����������[00;36;44m           Published by FormGen Corporation             [00;34;40m�����������
@ECHO  [00;34;40m�����������[00;30;44m                                                        [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m������������������������������������������������������ͻ[00;30;44m[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m�[01;37;45m Select a Video Mode                                  [01;35;45m�[00;30;44m[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m�[01;37;45m                                                      [01;35;45m�[00;30;44m[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m�[01;35;45m     1) CGA                                  4 Colors [01;35;45m�[00;30;44m[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m�[01;35;45m     2) EGA                                 16 Colors [01;35;45m�[00;30;44m[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m������������������������������������������������������ͼ[00;30;44m[00;34;40m�����������
@ECHO  [00;34;40m�����������[00;30;44m                                                        [00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m������������������������������������������������������ͻ[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m�[01;37;45m     3) Exit                                          [01;35;45m�[00;34;40m�����������
@ECHO  [00;34;40m�����������[01;35;45m������������������������������������������������������ͼ[00;34;40m�����������[00;37;40m
@ECHO [00;34;40m������������[00;30;44m                                                        [00;34;40m�����������[00;37;40m[79D[1A[s
GOTO COSMETICS

:COSMETICS
IF EXIST AUDIOHED.CK6 GOTO COS92
IF EXIST CGADICT.CK6 GOTO COS92
IF EXIST CGAHEAD.CK6 GOTO COS92
IF EXIST EGADICT.CK6 GOTO COS92
IF EXIST EGAHEAD.CK6 GOTO COS92
IF EXIST K6DEMO.EXE GOTO COSFGDM
IF EXIST ALIENS.EXE GOTO COSFGDM
IF EXIST BABYSIT.EXE GOTO COSPSDM
GOTO EGACHECK

:COS92
@ECHO [12;38H[01;36;44m2[00;37;40m[u
GOTO EGACHECK

:COSFGDM
@ECHO [13;24H[01;33;44m      SPECIAL DEMO VERSION      [00;37;40m[u
GOTO EGACHECK

:COSPSDM
@ECHO [13;24H[01;33;44m   PROMOTIONAL RELEASE VERSION  [00;37;40m[u
GOTO EGACHECK

:EGACHECK
IF EXIST KEEN6E.EXE GOTO EGAENABLE
IF EXIST K6DEMO.EXE GOTO DEMOENABLE
IF EXIST ALIENS.EXE GOTO DEMOENABLE
IF EXIST BABYSIT.EXE GOTO DEMOENABLE
SET CHOICES=%CHOICES%�
GOTO CGACHECK

:CGACHECK
IF EXIST KEEN6C.EXE GOTO CGAENABLE
SET CHOICES=%CHOICES%�
GOTO VIDEOMODE

:EGAENABLE
SET CHOICES=%CHOICES%2
@ECHO [19;19H[01;37;45m2) EGA                                 16 Colors[00;37;40m[u
GOTO CGACHECK

:CGAENABLE
SET CHOICES=%CHOICES%1
@ECHO [18;19H[01;37;45m1) CGA                                  4 Colors[00;37;40m[u
GOTO VIDEOMODE

:DEMOENABLE
SET CHOICES=%CHOICES%2�
@ECHO [19;19H[01;37;45m2) EGA                                 16 Colors[00;37;40m[u
GOTO VIDEOMODE

:VIDEOMODE
IF NOT EXIST EGASAVE MKDIR EGASAVE
IF NOT EXIST CGASAVE MKDIR CGASAVE
@CHOICE /N /C%CHOICES% >> NUL
IF ERRORLEVEL 3 GOTO CGACONF
IF ERRORLEVEL 2 GOTO EGACONF
IF ERRORLEVEL 1 GOTO EXIT

:CGACONF
IF EXIST CGACONF.CK6 GOTO CGA
IF EXIST EGACONF.CK6 GOTO CHGCGA
@ECHO �>>CGACONF.CK6
GOTO CGA

:EGACONF
IF EXIST EGACONF.CK6 GOTO EGA
IF EXIST CGACONF.CK6 GOTO CHGEGA
@ECHO �>>EGACONF.CK6
GOTO EGA

:CHGCGA
DEL EGASAVE\SAVEGAM?.CK6 >> NUL
IF EXIST SAVEGAM0.CK6 COPY SAVEGAM0.CK6 EGASAVE >> NUL
IF EXIST SAVEGAM1.CK6 COPY SAVEGAM1.CK6 EGASAVE >> NUL
IF EXIST SAVEGAM2.CK6 COPY SAVEGAM2.CK6 EGASAVE >> NUL
IF EXIST SAVEGAM3.CK6 COPY SAVEGAM3.CK6 EGASAVE >> NUL
IF EXIST SAVEGAM4.CK6 COPY SAVEGAM4.CK6 EGASAVE >> NUL
IF EXIST SAVEGAM5.CK6 COPY SAVEGAM5.CK6 EGASAVE >> NUL
IF EXIST CONFIG.CK6 COPY CONFIG.CK6 EGASAVE >> NUL
DEL SAVEGAM?.CK6 >> NUL
DEL CONFIG.CK6 >> NUL
IF EXIST CGASAVE\SAVEGAM0.CK6 COPY CGASAVE\SAVEGAM0.CK6 . >> NUL
IF EXIST CGASAVE\SAVEGAM1.CK6 COPY CGASAVE\SAVEGAM1.CK6 . >> NUL
IF EXIST CGASAVE\SAVEGAM2.CK6 COPY CGASAVE\SAVEGAM2.CK6 . >> NUL
IF EXIST CGASAVE\SAVEGAM3.CK6 COPY CGASAVE\SAVEGAM3.CK6 . >> NUL
IF EXIST CGASAVE\SAVEGAM4.CK6 COPY CGASAVE\SAVEGAM4.CK6 . >> NUL
IF EXIST CGASAVE\SAVEGAM5.CK6 COPY CGASAVE\SAVEGAM5.CK6 . >> NUL
IF EXIST CGASAVE\CONFIG.CK6 COPY CGASAVE\CONFIG.CK6 . >> NUL
DEL EGACONF.CK6
@ECHO �>>CGACONF.CK6
GOTO CGA

:CHGEGA
DEL CGASAVE\SAVEGAM?.CK6 >> NUL
IF EXIST SAVEGAM0.CK6 COPY SAVEGAM0.CK6 CGASAVE >> NUL
IF EXIST SAVEGAM1.CK6 COPY SAVEGAM1.CK6 CGASAVE >> NUL
IF EXIST SAVEGAM2.CK6 COPY SAVEGAM2.CK6 CGASAVE >> NUL
IF EXIST SAVEGAM3.CK6 COPY SAVEGAM3.CK6 CGASAVE >> NUL
IF EXIST SAVEGAM4.CK6 COPY SAVEGAM4.CK6 CGASAVE >> NUL
IF EXIST SAVEGAM5.CK6 COPY SAVEGAM5.CK6 CGASAVE >> NUL
IF EXIST CONFIG.CK6 COPY CONFIG.CK6 CGASAVE >> NUL
DEL SAVEGAM?.CK6 >> NUL
DEL CONFIG.CK6 >> NUL
IF EXIST EGASAVE\SAVEGAM0.CK6 COPY EGASAVE\SAVEGAM0.CK6 . >> NUL
IF EXIST EGASAVE\SAVEGAM1.CK6 COPY EGASAVE\SAVEGAM1.CK6 . >> NUL
IF EXIST EGASAVE\SAVEGAM2.CK6 COPY EGASAVE\SAVEGAM2.CK6 . >> NUL
IF EXIST EGASAVE\SAVEGAM3.CK6 COPY EGASAVE\SAVEGAM3.CK6 . >> NUL
IF EXIST EGASAVE\SAVEGAM4.CK6 COPY EGASAVE\SAVEGAM4.CK6 . >> NUL
IF EXIST EGASAVE\SAVEGAM5.CK6 COPY EGASAVE\SAVEGAM5.CK6 . >> NUL
IF EXIST EGASAVE\CONFIG.CK6 COPY EGASAVE\CONFIG.CK6 . >> NUL
DEL CGACONF.CK6
@ECHO �>>EGACONF.CK6
GOTO EGA

:CGA
IF NOT EXIST KEEN6C.EXE GOTO START
KEEN6C %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO EXIT

:EGA
IF EXIST KEEN6E.EXE GOTO KEEN6E
IF EXIST K6DEMO.EXE GOTO K6DEMO
IF EXIST ALIENS.EXE GOTO ALIENS
IF EXIST BABYSIT.EXE GOTO BABYSIT
GOTO START

:KEEN6E
KEEN6E %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO EXIT

:K6DEMO
K6DEMO %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO EXIT

:ALIENS
ALIENS %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO EXIT

:BABYSIT
BABYSIT %1 %2 %3 %4 %5 %6 %7 %8 %9
GOTO EXIT

:INCOMP
CLS
@ECHO Your game EXE files need to be named KEEN6E.EXE (for the EGA version) and
@ECHO KEEN6C.EXE (for the CGA version) in order for this launcher to work properly!
@ECHO.
PAUSE
GOTO EXIT

:EXIT
SET CHOICES=
CLS
