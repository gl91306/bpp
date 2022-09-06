::Build Blender++ for Windows
setlocal enableextensions enabledelayedexpansion
cd %BPP_ROOT%
mkdir bin
mkdir obj

::Number of cores is divided by 2 for keeping the system responsive/preventing Intel Hyperthreading to confuse us
set /A a = %NUMBER_OF_PROCESSORS%
set /A b = a/2
echo Building with %b% cores.

::x86 - Generic
%BPP_COMPILER%/mingw64/bin/mingw32-make -f makefile.windows -j%b% -B FLAGS="-w -Wall -Wextra -pedantic -fpermissive -pg -g3 -Ofast -flto -m64 -mavx2 -static-libstdc++ -static-libgcc"