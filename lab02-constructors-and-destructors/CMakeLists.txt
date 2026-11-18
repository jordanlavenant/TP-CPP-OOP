cmake_minimum_required(VERSION 3.20)
project(tp02_canvas LANGUAGES CXX)

# Standard C++, not GNU. This is the only one of these settings with no
# per-target form: it is set as the directory default, and therefore also
# applies to the targets added below -- including the ones you will write.
set(CMAKE_CXX_EXTENSIONS OFF)

# The rest of the shared settings are carried by an INTERFACE target: whatever
# links to it inherits them, and a target that does not link to it gets none.
add_library(settings INTERFACE)
target_compile_features(settings INTERFACE cxx_std_20)
target_compile_options(settings INTERFACE
  $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall;-Wextra>
  $<$<CXX_COMPILER_ID:MSVC>:/W4>)

# With no explicit build type, the compiler would get neither optimisation
# nor debug symbols.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

add_library(drawing STATIC src/canvas.cpp src/color.cpp)
target_include_directories(drawing PUBLIC include)
target_link_libraries(drawing PRIVATE settings)

# The drawings produced by the program go into the build directory, so that
# they never get mistaken for source files.
target_compile_definitions(drawing PUBLIC OUT_DIR="${CMAKE_CURRENT_BINARY_DIR}")

add_executable(demo src/main.cpp)
target_link_libraries(demo PRIVATE drawing settings)

# The binary is called "output": so it is ./build/output that you run, and
# ./build/tree.svg that you open in a browser.
set_target_properties(demo PROPERTIES OUTPUT_NAME output)

add_executable(tests tests/test_canvas.cpp)
target_link_libraries(tests PRIVATE drawing settings)

enable_testing()
add_test(NAME canvas COMMAND tests)
