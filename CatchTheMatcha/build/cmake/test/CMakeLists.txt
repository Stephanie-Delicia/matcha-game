cmake_minimum_required(VERSION 3.23)

# executable name
# version
# optional desc.
# languages
project(
TestProject 
VERSION 1.0
DESCRIPTION "Test for using cmake for macOS."
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

#CMAKE_BINARY_DIR is the directory where we generate the build
# this is preset to the /build dir
# $<CONFIGURATION> is the current build type which is CMAKE_BINARY_DIR

# setting path for where other libraries should be placed at
set(
  CMAKE_LIBRARY_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

# now everything will be in the build folder

# Add target from which the executable is made
add_executable(TestProject test.cpp)

if(APPLE)
  set_target_properties(TestProject PROPERTIES
    INSTALL_RPATH "@executable_path;@loader_path;/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/CatchTheMatcha/lib/sdl3"
    BUILD_WITH_INSTALL_RPATH TRUE
    MACOSX_RPATH TRUE
  )
endif()
# here we would do something like elseif(UNIX) to account for ppl who
# may want to use the executable on other systems
# apple platforms are unix, but not all unix are apple, so we always check
# for APPLE first, then UNIX in the chain of loops

# INSTALL_RPATH lets us set the RPath, which lets cmake know where to search
# for external libraries like SDL

# @executable_path and @loader_path generally mean the same path as the exec
# but if we want to add more paths, we simply do but separate them by ;

# I am guessing this is equivalent to listing the .cpp files for clang on mac
# Actually, actually, rpath basically tells clang where it can start searching
# for these needed files

# now that cmake can find these libraries, we need to tell it how to also build them! With add_subdirectory().
# specifically, this tells cmake to look into a sepcific directory for another CMakeLists.txt.


find_package(SDL3 PATHS "/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/CatchTheMatcha/lib/sdl3/SDL3.framework" CONFIG REQUIRED)

find_package(SDL3_image PATHS "/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/CatchTheMatcha/lib/sdl3/SDL3_image.framework" CONFIG REQUIRED)

find_package(SDL3_ttf PATHS "/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/CatchTheMatcha/lib/sdl3/SDL3_ttf.framework" CONFIG REQUIRED)

if(SDL3_ttf_FOUND)
    message(STATUS "Found SDL3_ttf.")
    message(STATUS "SDL3_ttf_LIBRARIES: ${SDL3_ttf_LIBRARIES}")
    message(STATUS "SDL3_image_LIBRARIES: ${SDL3_image_LIBRARIES}")
    # Proceed with using SDL3
else()
    message(FATAL_ERROR "Could not locate SDL3.")
endif()

# Now, we can link our executable target to the sdl libraries! 
# target to link against
# library targets
target_link_libraries(TestProject
  PRIVATE SDL3::SDL3
  PRIVATE SDL3_image::SDL3_image
  PRIVATE ${SDL3_ttf_LIBRARIES}
)
