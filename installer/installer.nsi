;Includes
!include "MUI2.nsh"
!include "LogicLib.nsh"
!include "WinVer.nsh"
!include "x64.nsh"

;Constants
!define PRODUCT_NAME "Blender++"
!define PRODUCT_DESCRIPTION "The app that can do anything"
!define COPYRIGHT "© 2022 Akshat Singh"
!define PRODUCT_VERSION "0.0.1.0"
!define SETUP_VERSION 0.0.1.0

;Attributes
Name "Blender++"
OutFile "Blender++ Setup.exe"
InstallDir "$PROGRAMFILES\Blender++"
InstallDirRegKey HKCU "Software\HackerDaGreat57\Blender++" ""
RequestExecutionLevel user ; user|highest|admin

;Version information
VIProductVersion "${PRODUCT_VERSION}"
VIAddVersionKey "ProductName" "${PRODUCT_NAME}"
VIAddVersionKey "ProductVersion" "${PRODUCT_VERSION}"
VIAddVersionKey "FileDescription" "${PRODUCT_DESCRIPTION}"
VIAddVersionKey "LegalCopyright" "${COPYRIGHT}"
VIAddVersionKey "FileVersion" "${SETUP_VERSION}"

;Modern UI appearance
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\orange-install.ico"
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Header\orange.bmp"
!define MUI_WELCOMEFINISHPAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Wizard\orange.bmp"
!define MUI_FINISHPAGE_NOAUTOCLOSE

;Installer Pages
!insertmacro MUI_PAGE_WELCOME
;!insertmacro MUI_PAGE_LICENSE "${NSISDIR}\Docs\Modern UI\License.txt"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

;Uninstaller Pages
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

;Languages
!insertmacro MUI_LANGUAGE "English"

;Installer Sections
Section "Blender++" MyApp
	SetOutPath $INSTDIR
	;File "My Program.exe"
	;File "Readme.txt"
	;WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

;Uninstaller Sections
Section "Uninstall"
	;Delete "$INSTDIR\Uninstall.exe"
	;RMDir "$INSTDIR"
	;DeleteRegKey /ifempty HKCU "Software\Modern UI Test"
SectionEnd