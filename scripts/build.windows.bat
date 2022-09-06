::Build Blender++ for Windows
setlocal enableextensions enabledelayedexpansion
cd %BPP_ROOT%
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
if exist zlib1.dll (
  echo DLLs already exist inside bin directory
) else (
  mkdir obj
)
xcopy "%BPP_COMPILER%/mingw64/bin/*.dll" "%BPP_ROOT%/build" /f /g /y

::Number of cores is divided by 2 for keeping the system responsive/preventing Intel Hyperthreading to confuse us
set /A a = %NUMBER_OF_PROCESSORS%
set /A b = a/2
echo Building with %b% cores.

set /p content=<rsrc/buildnumber.txt
set /A content=content+1
(echo %content%)>rsrc/buildnumber2.txt

cd rsrc
del buildnumber.txt
rename buildnumber2.txt buildnumber.txt

cd %BPP_ROOT%

::x86 - Generic
%BPP_COMPILER%/mingw64/bin/mingw32-make -f makefile.windows -j%b% FLAGS="-w -Wall -Wextra -pedantic -fpermissive -pg -g3 -Ofast -flto -m64 -mavx2"