cmake_minimum_required(VERSION 3.16)
project(rasterizer VERSION 1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

configure_file(src/rasterizerconfig.h.in src/rasterizerconfig.h)

# Force SDL to build as static library
set(SDL_SHARED OFF CACHE BOOL "Build a SDL shared library (if available)")
set(SDL_STATIC ON CACHE BOOL "Build a SDL static library (if available)")

# Add SDL subdirectory
add_subdirectory(SDL EXCLUDE_FROM_ALL)

# Create executable (remove WIN32 unless you specifically need it)
add_executable(rasterizer)

# Add all source files
target_sources(rasterizer PRIVATE  # Changed to PRIVATE and correct target name
    src/driver.cpp
    src/color.cpp
    src/model.cpp
    src/point.cpp
    src/point3.cpp
    src/transform.cpp
    src/triangle.cpp
    src/utils.cpp
    
    # Headers for IDE
    src/camera.h
    src/color.h
    src/model.h
    src/point.h
    src/point3.h
    src/rendertarget.h
    src/triangle.h
    src/transform.h
    src/utils.h

    # Generated header
    ${CMAKE_BINARY_DIR}/src/rasterizerconfig.h
)

# Set up include directories
target_include_directories(rasterizer PRIVATE 
    src
    ${CMAKE_BINARY_DIR}/src
)

# Link SDL3 statically
target_link_libraries(rasterizer PRIVATE SDL3::SDL3-static)
