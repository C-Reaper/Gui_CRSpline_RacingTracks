# Project README

## Overview
The project appears to be a simple racing game implemented using C and some external libraries. It includes functionality for creating windows, handling user input, rendering graphics, and playing audio. The project is structured around multiple makefiles for building on different platforms (Linux, Windows, Wine, WebAssembly).

## Features
- **Window Creation**: Supports window creation with specified dimensions.
- **Event Handling**: Handles basic events like frame updates.
- **Rendering**: Renders 2D graphics using custom functions.
- **Audio**: Although not explicitly mentioned, the project includes libraries for audio handling (`-lm -lX11 -lpng -ljpeg`).

## Project Structure
- `build/`: Directory where compiled .exe files are placed.
- `src/`: Contains the source code:
  - `Main.c`: Entry point of the program.
  - Additional `.h` files: Standalone header-based C-files that may be included in Main.c but are not implemented in `.c` files.
- `Makefile.linux`, `Makefile.windows`, `Makefile.wine`, `Makefile.web`: Build configurations for different platforms.

### Prerequisites
- **C/C++ Compiler and Debugger**: GCC, Clang
- **Make utility**
- **Standard Development Tools**
- **Libraries**:
  - Linux: X11, PNG, JPEG
  - Windows: WINAPI (via MSYS2 or similar)
  - Wine: `user32`, `gdi32`, `winmm`
  - WebAssembly: Emscripten

## Build & Run
### Linux
To build and run on Linux:
```bash
cd <Project>
make -f Makefile.linux all
make -f Makefile.linux exe
```

### Windows
To build and run on Windows:
```bash
cd <Project>
make -f Makefile.windows all
make -f Makefile.windows exe
```

### Wine
For cross-compiling to Windows using Wine:
```bash
cd <Project>
make -f Makefile.wine all
make -f Makefile.wine exe
```

### WebAssembly
To build and run on the web using Emscripten:
```bash
cd <Project>
make -f Makefile.web all
make -f Makefile.web exe
```

These commands will compile the project for the specified platform, link the necessary libraries, and produce an executable or output suitable for running.