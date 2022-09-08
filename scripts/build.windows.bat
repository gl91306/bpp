::Build Blender++ for Windows
setlocal enableextensions enabledelayedexpansion
cd /D %BPP_ROOT%
if exist bin (
  echo bin directory already exists
) else (
  mkdir bin
)
cd bin
if exist x86_64 (
  echo x86_64 directory already exists
) else (
  mkdir x86_64
)
if exist x86_64_v2 (
  echo x86_64_v2 directory already exists
) else (
  mkdir x86_64_v2
)
if exist x86_64_v3 (
  echo x86_64_v3 directory already exists
) else (
  mkdir x86_64_v3
)
cd x86_64
if exist zlib1.dll (
  echo DLLs already exist inside x86_64 directory
) else (
  xcopy "%BPP_COMPILER%/mingw64/bin/*.dll" "%BPP_ROOT%/bin/x86_64/" /f /g /y /h
)
cd ../x86_64_v2
if exist zlib1.dll (
  echo DLLs already exist inside x86_64_v2 directory
) else (
  xcopy "%BPP_COMPILER%/mingw64/bin/*.dll" "%BPP_ROOT%/bin/x86_64_v2/" /f /g /y /h
)
cd ../x86_64_v3
if exist zlib1.dll (
  echo DLLs already exist inside x86_64_v3 directory
) else (
  xcopy "%BPP_COMPILER%/mingw64/bin/*.dll" "%BPP_ROOT%/bin/x86_64_v3/" /f /g /y /h
)

cd %BPP_ROOT%
if exist obj (
  echo obj directory already exists
) else (
  mkdir obj
)
cd obj
if exist x86_64 (
  echo x86_64 directory already exists
) else (
  mkdir x86_64
)
if exist x86_64_v2 (
  echo x86_64_v2 directory already exists
) else (
  mkdir x86_64_v2
)
if exist x86_64_v3 (
  echo x86_64_v3 directory already exists
) else (
  mkdir x86_64_v3
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