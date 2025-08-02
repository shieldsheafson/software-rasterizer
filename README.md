# Basic Rasterizer

A 3d software rasterizer built in C++ using the SDL library.

## Building

### Prerequisites
- C++17 compatible compiler (GCC, Clang, MSVC)
- CMake 3.16+

### Clone and Build
```
# Clone with submodules
git clone --recursive https://github.com/yourusername/software-rasterizer.git
cd software-rasterizer

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make  # or cmake --build . on Windows
```

## Usage
```
# From build directory
./rasterizer  # Linux/Mac
# or
rasterizer.exe  # Windows
```

You can try to render your own obj files; add the .obj files to input and change the file path in the constructor of model in driver.cpp.

## License
MIT License - see LICENSE file for details