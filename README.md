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

## Thoughts and Plans
The templated classes and functions are awful and I have been putting off choosing the base type I will use because the different options have different appeals but I need to make a choice. 

Ideally, I have more functionality soon; I very much doubt a more complex model will render correctly right now (like I need a depth buffer), but render a cube seemed like a decent place to pause for right now.

I need to clean up the code pretty bad, but that is a project for tomorrow; lots of magic numbers and wacky uncomment code. 