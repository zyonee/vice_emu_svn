# Microsoft Developer Studio Project File - Name="x128" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=x128 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "x128.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "x128.mak" CFG="x128 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "x128 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "x128 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "x128 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\data"
# PROP Intermediate_Dir "libs\x128\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2  /D "WIN32" /D "_WINDOWS" /D "IDE_COMPILE" /D "DONT_USE_UNISTD_H"  /D "NDEBUG" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\" /I "..\\" /I "..\..\..\\" /I "..\..\..\drive" /I "..\..\..\lib\p64" /I "..\..\..\monitor" /I "..\..\..\platform" /I "..\..\..\vdrive"  /D "WIN32" /D "_WINDOWS" /D "IDE_COMPILE" /D "DONT_USE_UNISTD_H"  /D "NDEBUG" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "WIN32" /d "IDE_COMPILE"
# ADD RSC /l 0x409 /i "..\msvc" /i "..\\" /i "..\..\..\\" /d "NDEBUG" /d "WIN32" /d "IDE_COMPILE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 advapi32.lib comctl32.lib comdlg32.lib gdi32.lib kernel32.lib odbc32.lib odbccp32.lib ole32.lib oleaut32.lib shell32.lib user32.lib uuid.lib version.lib winmm.lib winspool.lib wsock32.lib SDLmain.lib SDL.lib opengl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 advapi32.lib comctl32.lib comdlg32.lib gdi32.lib kernel32.lib odbc32.lib odbccp32.lib ole32.lib oleaut32.lib shell32.lib user32.lib uuid.lib version.lib winmm.lib winspool.lib wsock32.lib SDLmain.lib SDL.lib opengl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "x128 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\data"
# PROP Intermediate_Dir "libs\x128\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od  /D "WIN32" /D "_WINDOWS" /D "IDE_COMPILE" /D "DONT_USE_UNISTD_H" /D "_DEBUG" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I ".\" /I "..\\" /I "..\..\..\\" /I "..\..\..\drive" /I "..\..\..\lib\p64" /I "..\..\..\monitor" /I "..\..\..\platform" /I "..\..\..\vdrive"  /D "WIN32" /D "_WINDOWS" /D "IDE_COMPILE" /D "DONT_USE_UNISTD_H" /D "_DEBUG" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "WIN32" /d "IDE_COMPILE"
# ADD RSC /l 0x409 /i "..\msvc" /i "..\\" /i "..\..\..\\" /d "_DEBUG" /d "WIN32" /d "IDE_COMPILE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 advapi32.lib comctl32.lib comdlg32.lib gdi32.lib kernel32.lib odbc32.lib odbccp32.lib ole32.lib oleaut32.lib shell32.lib user32.lib uuid.lib version.lib winmm.lib winspool.lib wsock32.lib SDLmain.lib SDL.lib opengl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /NODEFAULTLIB:msvcrt.lib
# ADD LINK32 advapi32.lib comctl32.lib comdlg32.lib gdi32.lib kernel32.lib odbc32.lib odbccp32.lib ole32.lib oleaut32.lib shell32.lib user32.lib uuid.lib version.lib winmm.lib winspool.lib wsock32.lib SDLmain.lib SDL.lib opengl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /NODEFAULTLIB:msvcrt.lib

!ENDIF

# Begin Target

# Name "x128 - Win32 Release"
# Name "x128 - Win32 Debug"
# Begin Source File

SOURCE="..\..\..\main.c"
# End Source File
# End Target
# End Project
