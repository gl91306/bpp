# Blender++
An experimental C++ application that is meant to replace all the big dudes who sell software for $600 a year. (Hint: That company's name is a material that people used to make houses out of.)

## How to build from source 🛠️
Make sure you have the latest version of [`msys2`](https://www.msys2.org/) installed. Set the environment variable `BPP_COMPILER` to the root directory of your msys2 install **(NOT the `mingw-w64` root, for example mine is `D:\src\_compilers\msys2`. Yours is probably `C:\msys64`)**, and set `BPP_ROOT` to the directory where you have cloned this repository (for example mine is `D:\bpp`). Open [VS Code](https://github.com/microsoft/vscode.git) and click `Terminal -> Run Task... -> Build Blender++ (for outsiders)`. **Once you ran the `(for outsiders)` script at least once (and let it finish) then you can use the regular `Build Blender++` task.**

In case you have more/less than 4 cores on your system, you can modify the `-j` parameter of mingw32-make via modifying the tasks.json file.

Apple Macintosh/Linux compatibility planned but not guaranteed (for now).