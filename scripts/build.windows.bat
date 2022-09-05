::Build Blender++ for Windows
setlocal enableextensions enabledelayedexpansion
cd %BPP_ROOT%
mkdir bin
mkdir obj

set /A a = %NUMBER_OF_PROCESSORS%
set /A b = a/2
echo Building with %b% cores.

%BPP_COMPILER%/mingw64/bin/mingw32-make -f makefile.windows -j%b%