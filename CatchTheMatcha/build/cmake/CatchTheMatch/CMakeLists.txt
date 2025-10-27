cmake_minimum_required(VERSION 3.15)

# executable name
# version
# optional desc.
# languages
project(
CatchTheMatcha 
VERSION 1.0
DESCRIPTION "A catching game with matcha."
LANGUAGES CXX
)

# setting what C version to use
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# setting the path for the executable
set(
  CMAKE_RUNTIME_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

# setting path for where other libraries should be placed at
set(
  CMAKE_RUNTIME_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

# Add target from which the executable is made
add_executable(CatchTheMatcha ../main.cpp)

if(APPLE)
  set_target_properties(CatchTheMatcha PROPERTIES
    INSTALL_RPATH "@executable_path;@loader_path"
    BUILD_WITH_INSTALL_RPATH TRUE
    MACOSX_RPATH TRUE
  )



endif()
