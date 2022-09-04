# Blender++
A *somewhat experimental* C++ application that can do (well, is *supposed* to do) everything a computer is capable of. That means basically all the programs you currently have installed on your computer conveniently packed into one application. There's a long, **long** way to go until we reach that checkpoint, but I'm just doing what I can for now.

## How to build from source 🛠️
1. Make sure you have the latest version of [`msys2`](https://www.msys2.org/) installed.
2. Set the environment variable `BPP_COMPILER` to the root directory of your msys2 install **(NOT the `mingw-w64` root, for example mine is `D:\src\_compilers\msys2`. Yours is probably `C:\msys64`)**, and set `BPP_ROOT` to the directory where you have cloned this repository (for example mine is `D:\bpp`).
3. Download [VS Code](https://github.com/microsoft/vscode.git) and open it with `code .` in the directory where you cloned the repository.
4. Open `.vscode/tasks.json` and if you have more/less than 4 cores on your system, you can modify the `-j` parameter of mingw32-make via modifying the tasks (<kbd>Control</kbd> + <kbd>F</kbd> + <kbd>-j4</kbd>).
5. Then click `Terminal -> Run Task... -> Build Blender++ (for outsiders)`.
6. **Once you ran the `(for outsiders)` script at least once (and let it finish) then you can use the regular `Build Blender++` task.** Most "errors" thrown while running this are nothing serious and can safely be ignored.

Apple Macintosh/Linux compatibility is planned but not guaranteed (for now). Make a PR please!

## Why did you make this project?
This application is meant to replace all the overpriced proprietary software out there that doesn't give you any freedom. I believe that computer software was meant to be free and open, and some desperate people from 1969 ([yes, literally](https://en.wikipedia.org/wiki/Proprietary_software#Origin)) decided to unnecessarily close monetize it. I know we all have to make a buck or two, but I really don't think software is the way to do that.