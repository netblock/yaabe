# NSIS installer script to create an installer wizard for windows

#!define nsis_stage_dir = nsis_stage #should be defined via command line

!include MUI2.nsh

Unicode True
!define name "YAABE BIOS Editor"
Name "${name}"
VIAddVersionKey /LANG=0 "ProductName" "${name}"
VIAddVersionKey /LANG=0 "FileVersion" "${yaabe_version}"
VIAddVersionKey /LANG=0 "ProductVersion" "${yaabe_version}"
VIAddVersionKey /LANG=0 "FileDescription" "https://github.com/netblock/yaabe"
VIAddVersionKey /LANG=0 "LegalCopyright" "Copyright Netblock"
VIProductVersion "${yaabe_version}.0"
Outfile "${yaabe_outfile}"
SetCompressor /solid lzma

RequestExecutionLevel admin
#RequestExecutionLevel user # TODO only request admin if install dir needs it
InstallDir "$PROGRAMFILES64\yaabe"
# if previously installed, get previous install location:
InstallDirRegKey HKEY_LOCAL_MACHINE "Software\YAABE" InstallLocation

ShowInstDetails show
!define MUI_ABORTWARNING


#!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "${nsis_stage_dir}\LICENSE"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

#!insertmacro MUI_PAGE_STARTMENU Application $SMPROGRAMS

!define MUI_FINISHPAGE_LINK "YAABE Github page"
!define MUI_FINISHPAGE_LINK_LOCATION "https://github.com/netblock/yaabe"
!define MUI_FINISHPAGE_SHOWREADME ""
!define MUI_FINISHPAGE_SHOWREADME_TEXT "Create Start Menu shortcut"
!define MUI_FINISHPAGE_SHOWREADME_FUNCTION CreateStartShortcut
#!define MUI_FINISHPAGE_RUN
#!define MUI_FINISHPAGE_RUN_TEXT "Run $(^Name)"
#!define MUI_FINISHPAGE_RUN_FUNCTION RunShortcut
# TODO for some reason libgio-2.0-0.dll (2.78.0.0) crashes if YAABE is
# launched via the installer.
!insertmacro MUI_PAGE_FINISH


#!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

Section "YAABE"
	SetShellVarContext all
	SetOutPath "$INSTDIR"
	WriteRegStr HKEY_LOCAL_MACHINE "Software\YAABE" InstallLocation "$INSTDIR"
	WriteRegStr HKEY_LOCAL_MACHINE "Software\YAABE" Version "${yaabe_version}"

	WriteUninstaller uninstall.exe

	File /r "${nsis_stage_dir}\*"
SectionEnd

Section "Uninstall"
	Delete "$instDIR\*.dll"
	Delete "$INSTDIR\yaabe.exe"
	Delete "$INSTDIR\LICENSE"
	Delete "$INSTDIR\uninstall.exe"
	RMDir /r "$INSTDIR\etc"
	RMDir /r "$INSTDIR\share"
	RMDir "$INSTDIR"

	Delete "$SMPROGRAMS\$(^Name).lnk"
	DeleteRegKey HKEY_LOCAL_MACHINE "Software\YAABE"
SectionEnd


Function CreateStartShortcut
	SetShellVarContext all
	CreateShortcut "$SMPrograms\$(^Name).lnk" "$INSTDIR\yaabe.exe"
FunctionEnd

Function RunShortcut
	SetShellVarContext all
	ExecShell "open" "$SMPrograms\$(^Name).lnk"
FunctionEnd
