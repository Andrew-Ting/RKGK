# RKGK

RKGK is a Vulkan render engine based on the [Sunaba template](https://github.com/Andrew-Ting/Sunaba).

## Setup

I assume [CMake](https://cmake.org/) and [Visual Studio 2022](https://visualstudio.microsoft.com/vs/) are already installed on your device (if not, download them). There are several ways to set up a running build:

### Quick Setup
1. Clone this repository
2. Double click `setup.bat`. This should get a running release build

### Through CMake-GUI
1. Clone this repository
2. Run `git submodule update --init --recursive` at the root of this repository
3. Open the CMake-GUI (which comes downloaded together with CMake)
4. Set the "Where is the source code:" directory path to the root of the repository
5. In the "Preset" dropdown field, select "default"
6. Click the button "Configure", and specify the generator of the project to be "Visual Studio 17 2022". Otherwise accept all defaults
7. Click the button "Generate"
8. Click the button "Build"
9. Under the newly generated `build/` directory, open `RKGK.sln`
10. With Visual Studio in focus, press F5 to run a debug build

### Through terminal command cmake
1. Clone this repository
2. Run the following commands at the root of this repository:
```
git submodule update --init --recursive # initialize and update git submodules
cmake . --preset default # configure the CMake build with the default Visual Studio 2022 Cmake preset
cmake --build ./build # build the Visual Studio solution
```
3. Under the newly generated `build/` directory, open `RKGK.sln`
4. With Visual Studio 2022 in focus, press F5 to run a debug build