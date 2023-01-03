> 📜 other templates available at https://github.com/SkyrimScripting/SKSE_Templates

# SKSE - Write to Log File

- [SKSE - Write to Log File](#skse---writing-to-log-files)
  - [What does it do?](#what-does-it-do)
  - [Logging in your own mods](#logging-in-your-own-mods)
  - [Requirements](#requirements)
  - [Project setup](#project-setup)
  - [Setup your own repository](#setup-your-own-repository)

---

A simple SKSE plugin for Skyrim using:

- C++
- CMake
- [CommonLibSSE NG](https://github.com/CharmedBaryon/CommonLibSSE-NG)
  - _automatically downloaded using vcpkg integration of CMake_

> Because this uses CommonLibSSE NG, it supports Skyrim SSE, AE, GOG, and VR!

## What does it do?

It writes to a log file.

Read [`plugin.cpp`](plugin.cpp) and [`logger_annotated.h`](logger_annotated.h) for more details on what it's doing!

I __*highly recommend*__ you create a log file for your mod.

It's useful for:
- your own debugging, while developing the mod
- debugging issues from your users (**ask your users to provide .log files in their bug reports on Nexus/GitHub!**)

## Logging in your own mods

Just use this template!

Or:

1. Copy the contents of [`logger.h`](logger.h)
1. Paste the code at the top of your own `plugin.cpp`
1. Call `SetupLog();` inside of your `SKSEPluginLoad`
1. Bam! Done. Use `logger::info("We did it!");`

Or:

1. Copy the [`logger.h`](logger.h) file from this template into your own mod
1. Write `#include "logger.h"` in your main `plugin.cpp` file
1. Call `SetupLog();` inside of your `SKSEPluginLoad`
1. Bam! Done. Use `logger::info("We did it!");`

> If you plan on using a debugger and would like to see your logs appear inside of your IDE's Debug Console, then use [`logger_with_debugger_support.h`](logger_with_debugger_support.h) instead of [`logger.h`](logger.h).

## Requirements

- [Visual Studio 2022](https://visualstudio.microsoft.com/) (_the free Community edition is fine!_)
- [CMake](https://cmake.org/download/) 3.25.1+ (_please install the Latest Release_)
- [`vcpkg`](https://github.com/microsoft/vcpkg)
  - 1. Clone the repository using git OR [download it as a .zip](https://github.com/microsoft/vcpkg/archive/refs/heads/master.zip)
  - 2. Go into the `vcpkg` folder and double-click on `bootstrap-vcpkg.bat`
  - 3. Edit your system or user Environment Variables and add a new one:
    - Name: `VCPKG_ROOT`  
      Value: `C:\path\to\wherever\your\vcpkg\folder\is`

<img src="https://raw.githubusercontent.com/SkyrimScripting/Resources/main/Screenshots/Setting%20Environment%20Variables/VCPKG_ROOT.png" height="150">

Once you have Visual Studio 2022 installed, you can open this folder in basically any C++ editor, e.g. [VS Code](https://code.visualstudio.com/) or [CLion](https://www.jetbrains.com/clion/) or [Visual Studio](https://visualstudio.microsoft.com/)
- > _for VS Code, if you are not automatically prompted to install the [C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) and [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extensions, please install those and then close VS Code and then open this project as a folder in VS Code_

You may need to click `OK` on a few windows, but the project should automatically run CMake!

It will _automatically_ download [CommonLibSSE NG](https://github.com/CharmedBaryon/CommonLibSSE-NG) and everything you need to get started making your new plugin!

## Project setup

By default, when this project compiles it will output a `.dll` for your SKSE plugin into the `build/` folder.

If you want to configure this project to output your plugin files
into your Skyrim Special Edition's "`Data`" folder:

- Set the `SKYRIM_FOLDER` environment variable to the path of your Skyrim installation  
  e.g. `C:\Program Files (x86)\Steam\steamapps\common\Skyrim Special Edition`

<img src="https://raw.githubusercontent.com/SkyrimScripting/Resources/main/Screenshots/Setting%20Environment%20Variables/SKYRIM_FOLDER.png" height="150">

If you want to configure this project to output your plugin files
into your "`mods`" folder:  
(_for Mod Organizer 2 or Vortex_)

- Set the `SKYRIM_MODS_FOLDER` environment variable to the path of your mods folder:  
  e.g. `C:\Users\<user>\AppData\Local\ModOrganizer\Skyrim Special Edition\mods`  
  e.g. `C:\Users\<user>\AppData\Roaming\Vortex\skyrimse\mods`

<img src="https://raw.githubusercontent.com/SkyrimScripting/Resources/main/Screenshots/Setting%20Environment%20Variables/SKYRIM_MODS_FOLDER.png" height="150">

## Setup your own repository

If you clone this template on GitHub, please:

- Go into `LICENSE` and change the year and change `<YOUR NAME HERE>` to your name.
- Go into `CODE_OF_CONDUCT.md` and change `<YOUR CONTACT INFO HERE>` to your contact information.

It's good to have a `Code of Conduct` and GitHub will show your project's `CODE_OF_CONDUCT.md` in the project sidebar.

If you'd like to know more about open source licenses, see:
- [Licensing a repository](https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/customizing-your-repository/licensing-a-repository)
- [Choose an open source license](https://choosealicense.com/)

**If you use this template, PLEASE release your project as a public open source project.** 💖

**PLEASE DO NOT RELEASE YOUR SKSE PLUGIN ON NEXUS/ETC WITHOUT MAKING THE SOURCE CODE AVAILABLE**
