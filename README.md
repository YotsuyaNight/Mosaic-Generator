Mosaic Generator
================
This program takes an image and creates a mosaic from provided set of icons.

How to build
------------
Prerequisites:
1. **CMake** (build system)
2. **Qt5** (GUI framework) - source code is written using v5.13.0, althought older versions should work too.
3. A working **C++ compiler** (g++)

Build steps:
```
# Clone this repository
$ git clone https://github.com/YotsuyaNight/Mosaic-Generator.git

# CD into new directory: 
$ cd Mosaic-Generator

# Create directory for out-of-source build:
$ mkdir build
$ cd build

# Generate CMake files
$ cmake ..

# Build and install
$ make install
```
`install` directory containing the executables will appear in Mosaic-Generator directory, alongside `build`.
You can run the program by executing `mg` binary form console or your file manager.
