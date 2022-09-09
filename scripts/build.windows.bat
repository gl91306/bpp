::Build Blender++ for Windows
setlocal enableextensions enabledelayedexpansion
cd /D %BPP_ROOT%
mkdir bin
cd bin
mkdir x86_64
mkdir x86_64_v2
mkdir x86_64_v3

xcopy "%BPP_COMPILER%/mingw64/bin/*.dll" "%BPP_ROOT%/bin/x86_64/" /f /g /y /h /u
xcopy "%BPP_COMPILER%/mingw64/bin/*.dll" "%BPP_ROOT%/bin/x86_64_v2/" /f /g /y /h /u
xcopy "%BPP_COMPILER%/mingw64/bin/*.dll" "%BPP_ROOT%/bin/x86_64_v3/" /f /g /y /h /u

cd %BPP_ROOT%
mkdir obj
cd obj
mkdir x86_64
mkdir x86_64_v2
mkdir x86_64_v3

cd %BPP_COMPILER%/mingw64/bin
if exist libboost_atomic-mt.dll (
  echo Libraries already installed.
) else (
  pacman -S mingw-w64-x86_64-toolchain --noconfirm
  pacman -S mingw-w64-x86_64-glfw --noconfirm
  pacman -S mingw-w64-x86_64-ncurses --noconfirm
  pacman -S mingw-w64-x86_64-boost --noconfirm
  pacman -Syuu
)

cd %BPP_ROOT%

::Number of cores is divided by 2 for keeping the system responsive/preventing Intel Hyperthreading to confuse us
set /A b = %NUMBER_OF_PROCESSORS%/2
echo Building with %b% cores.

::Increment & save the build number
set /p old=<rsrc/buildnumber.txt
set /A content=old+1
(echo %content%)>rsrc/buildnumber2.txt
cd rsrc
del buildnumber.txt
rename buildnumber2.txt buildnumber.txt

cd /D %BPP_ROOT%

::Increment the build number in the source code file
powershell -Command "(gc "%BPP_ROOT%/src/bpp.cpp") -replace 'v0.0.0.%old%', 'v0.0.0.%content%' | Out-File -encoding ASCII "%BPP_ROOT%/src/bpp.cpp""
powershell -Command "(gc "%BPP_ROOT%/rsrc/bpp.rc") -replace '%old%', '%content%' | Out-File -encoding ASCII "%BPP_ROOT%/rsrc/bpp.rc""

::Ok, the build has been set up. Let's actually compile the stuff now.
%BPP_COMPILER%/mingw64/bin/mingw32-make -f makefile.windows -j%b% x86_64 x86_64_v2 x86_64_v3