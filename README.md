# Sunaba

Sunaba is a Vulkan render engine template with easy Git submodule integration to typical quality-of-life libraries ([IMGUI](https://github.com/ocornut/imgui.git), [Volk](https://github.com/zeux/volk.git), [VMA](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator), [VkBootstrap](https://github.com/charles-lunarg/vk-bootstrap), [GLM](https://github.com/g-truc/glm.git), and [SDL 3](https://github.com/libsdl-org/SDL), and [vulkan-headers](https://github.com/KhronosGroup/Vulkan-Headers)) in a CMake build system. Without any changes, the template is an empty canvas with a single IMGUI modal printing the frame rate.

## Credits and Disclaimers

Much of the code abstractions used are based on Victor Blanco's brilliant [vkguide](vkguide.dev) series, but with some notable changes I made to modernize and make engine setup + workflow easier, including: 

1. Upgrading the windowing library from SDL 2 to SDL 3
2. Integrating the IMGUI docking branch to allow UI to be docked or dragged out of the render window
3. Integrating all dependencies as submodules, improving versioning workflows
4. Integrating Volk to remove dependency on the Vulkan SDK being installed on the target device
5. Making variable names non-abbreviated and adding "m" prefixes on all class member fields

While this is meant to be a blank slate for building render engines, for the code to remain concise and testable I needed to narrow down my target platforms/builds to what I can and care to support. The codebase primarily targets:

1. Windows PCs
2. PCs with GPU drivers that have Vulkan 1.3+ support
3. Visual Studio 2022 builds

It is possible to modify the code to run on other platforms/build setups, but it will need some adjustments to suit your needs.

## Setup

I assume [Cmake](https://cmake.org/) and [Visual Studio 2022](https://visualstudio.microsoft.com/vs/) are already installed on your device (if not, download them). There are several ways to set up a running build:

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
9. Under the newly generated `build/` directory, open `Sunaba.sln`
10. With Visual Studio in focus, press F5 to run a debug build

### Through terminal command cmake
1. Clone this repository
2. Run the following commands at the root of this repository:
```
git submodule update --init --recursive # initialize and update git submodules
cmake . --preset default # configure the CMake build with the default Visual Studio 2022 preset
cmake --build ./build # build the Visual Studio solution
```
3. Under the newly generated `build/` directory, open `Sunaba.sln`
4. With Visual Studio 2022 in focus, press F5 to run a debug build

