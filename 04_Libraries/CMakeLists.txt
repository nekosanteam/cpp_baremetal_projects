cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD   11)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD   17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(BareMetal02_Libraries CXX)
enable_language(C)
enable_language(ASM)

add_library(lib02_Libraries OBJECT src/nkstring.cpp)
target_include_directories(lib02_Libraries
  PUBLIC inc/)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(lib02_Libraries)
endif()
if(COMMAND target_compile_option_baremetal)
  target_compile_option_baremetal(lib02_Libraries)
endif()

if (BUILD_TESTING)
  add_executable(02_Libraries app/main.cpp)
  if(COMMAND target_compile_option_warning)
    target_compile_option_warning(02_Libraries)
  endif()
  target_link_libraries(02_Libraries lib02_Libraries CppUTest CppUTestExt)
  add_test(NAME 02_LIBRARIES_ALL COMMAND 02_Libraries)
endif()
