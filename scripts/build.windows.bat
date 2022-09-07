::Build Blender++ for Windows
setlocal enableextensions enabledelayedexpansion
cd /D %BPP_ROOT%
if exist bin (
  echo bin directory already exists
) else (
  mkdir bin
)
if exist obj (
  echo obj directory already exists
) else (
  mkdir obj
)
cd bin
if exist zlib1.dll (
  echo DLLs already exist inside bin directory
) else (
  xcopy "%BPP_COMPILER%/mingw64/bin/*.dll" "%BPP_ROOT%/bin/" /f /g /y /h
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

::Ok, the build has been set up. Let's actually compile the stuff now.
%BPP_COMPILER%/mingw64/bin/mingw32-make -f makefile.windows -j%b% FLAGS="-w -Wall -Wextra -pedantic -fpermissive -pg -g3 -Ofast -flto -m64 -march=x86-64"

::Commit to the repository
git add .
git commit -m "New build: v0.0.0.%content%"
gi