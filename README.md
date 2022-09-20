# UDP-Debug-Reader

This is a modernized version of the [`UDP-Debug-Reader`](https://github.com/dimok789/loadiine_gx2/tree/master/udp_debug_reader) project by `Dimok` by using the `C++20` standard and `CMake` as build system.

The `UDP-Debug-Reader` is a PC program which can read `UDP` debug logs sent from Wii U homebrew applications to your PC which is very useful for homebrew development.

The Wii U sided logging code itself can e.g. be found in [`libutilswut`](https://github.com/Maschell/libutils/tree/wut) or [directly in `wut`](https://github.com/devkitPro/wut/blob/master/libraries/libwhb/src/log.c) (preferable).

## Compiling

This project uses a standard `CMakeLists.txt` file so compiling should be straight-forward for any platform.

### Windows
```
mkdir WindowsBuild
cd WindowsBuild
cmake ../
```

Now you can enter the `WindowsBuild` folder and open the `.sln` file in [`Visual Studio`](https://visualstudio.microsoft.com) to build from the `IDE`.

### Linux
```
mkdir LinuxBuild
cd LinuxBuild
cmake ../
make
```
Now your binary should be built successfully.

## Usage

The `UDP-Debug-Reader` is a command line application which can be started via double-click (on Windows) or from the command line/terminal. Read the instructions printed on the command line/terminal to learn about the provided features like logging to a file, clearing the output or quitting the `UDP-Debug-Reader`.