# Microsoft Developer Studio Project File - Name="arch" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=arch - Win32 Debug
!MESSAGE Dies ist kein g�ltiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und f�hren Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "arch.mak".
!MESSAGE 
!MESSAGE Sie k�nnen beim Ausf�hren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "arch.mak" CFG="arch - Win32 Debug"
!MESSAGE 
!MESSAGE F�r die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "arch - Win32 Release" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE "arch - Win32 Debug" (basierend auf  "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "arch - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "libs\arch\Release"
# PROP Intermediate_Dir "libs\arch\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I ".\msvc" /I ".\\" /I "..\..\\" /I "..\..\drive" /I "..\..\vdrive" /I "..\..\c64" /I "..\..\c128" /I "..\..\vic20" /I "..\..\pet" /I "..\..\cbm2" /I "..\..\raster" /I "..\..\monitor" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "arch - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "libs\arch\Debug"
# PROP Intermediate_Dir "libs\arch\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /I ".\msvc" /I ".\\" /I "..\..\\" /I "..\..\drive" /I "..\..\vdrive" /I "..\..\c64" /I "..\..\c128" /I "..\..\vic20" /I "..\..\pet" /I "..\..\cbm2" /I "..\..\raster" /I "..\..\monitor" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "arch - Win32 Release"
# Name "arch - Win32 Debug"
# Begin Source File

SOURCE=.\archdep.c
# End Source File
# Begin Source File

SOURCE=.\c128kbd.c
# End Source File
# Begin Source File

SOURCE=.\c128ui.c
# End Source File
# Begin Source File

SOURCE=.\c610kbd.c
# End Source File
# Begin Source File

SOURCE=.\c610ui.c
# End Source File
# Begin Source File

SOURCE=.\c64kbd.c
# End Source File
# Begin Source File

SOURCE=.\c64ui.c
# End Source File
# Begin Source File

SOURCE=.\console.c
# End Source File
# Begin Source File

SOURCE=.\dirent.c
# End Source File
# Begin Source File

SOURCE=.\fullscreen.c
# End Source File
# Begin Source File

SOURCE=.\joystick.c
# End Source File
# Begin Source File

SOURCE=.\kbd.c
# End Source File
# Begin Source File

SOURCE=.\main_exit.c
# End Source File
# Begin Source File

SOURCE=.\mouse.c
# End Source File
# Begin Source File

SOURCE=.\petkbd.c
# End Source File
# Begin Source File

SOURCE=.\petui.c
# End Source File
# Begin Source File

SOURCE=.\plus4kbd.c
# End Source File
# Begin Source File

SOURCE=.\plus4ui.c
# End Source File
# Begin Source File

SOURCE=.\statusbar.c
# End Source File
# Begin Source File

SOURCE=.\ui.c
# End Source File
# Begin Source File

SOURCE=.\uiattach.c
# End Source File
# Begin Source File

SOURCE=.\uicbm2set.c
# End Source File
# Begin Source File

SOURCE=.\uicmdline.c
# End Source File
# Begin Source File

SOURCE=.\uiconsole.c
# End Source File
# Begin Source File

SOURCE=.\uidatasette.c
# End Source File
# Begin Source File

SOURCE=.\uidrive.c
# End Source File
# Begin Source File

SOURCE=.\uijoystick.c
# End Source File
# Begin Source File

SOURCE=.\uilib.c
# End Source File
# Begin Source File

SOURCE=.\uimon.c
# End Source File
# Begin Source File

SOURCE=.\uipetset.c
# End Source File
# Begin Source File

SOURCE=.\uireu.c
# End Source File
# Begin Source File

SOURCE=.\uisid.c
# End Source File
# Begin Source File

SOURCE=.\uisnapshot.c
# End Source File
# Begin Source File

SOURCE=.\uisound.c
# End Source File
# Begin Source File

SOURCE=.\uivicii.c
# End Source File
# Begin Source File

SOURCE=.\uivicset.c
# End Source File
# Begin Source File

SOURCE=.\uivideo.c
# End Source File
# Begin Source File

SOURCE=.\vic20kbd.c
# End Source File
# Begin Source File

SOURCE=.\vic20ui.c
# End Source File
# Begin Source File

SOURCE=.\video.c
# End Source File
# Begin Source File

SOURCE=.\vsidui.c
# End Source File
# Begin Source File

SOURCE=.\vsyncarch.c
# End Source File
# Begin Source File

SOURCE=.\winmain.c
# End Source File
# End Target
# End Project
