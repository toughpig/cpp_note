`CMakeLists.txt ---cmake---> Makefile`
```bash
cmake [-S source-dir] [-B build-dir] #CMakeLists.txt
cd build-dir
make #Makefile
```
`in-place-make`
```bash
cmake .
```
`out-place-make`
```bash
mkdir build   
cd build
cmake ..
```
`Makefile`
```bash
# Print tracing information.
make --trace
```
# CMakeLists.txt (syntax)
```cmake
# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.5)

# Set the project name
project(hello_cmake)

# Add an executable
add_executable(hello_cmake main.cpp)
```
```cmake
# Variables
# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/Hello.cpp
    src/main.cpp
)

# An alternative to setting specific file names in the SOURCES variable is to use a GLOB command to find files using wildcard pattern matching.
file(GLOB SOURCES "src/*.cpp")

# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})
```
```cmake
# Generate the static library from the library sources
# STATIC --> libhello_library.a
add_library(hello_library STATIC 
    src/Hello.cpp
)

# SHARED --> libhello_library.so
add_library(hello_library SHARED 
    src/Hello.cpp
)
```
```cmake
# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
# -I${hello_headers}
target_include_directories(hello_headers
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

# Add an executable with the above sources
add_executable(hello_binary
    src/main.cpp
)

# link the new hello_library target with the hello_binary target
target_link_libraries( hello_binary
    PRIVATE 
        hello::library
)
```

