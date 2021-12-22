cmake_minimum_required(VERSION 3.13)
project(BareMetal05_Libraries CXX)
enable_language(C)
enable_language(ASM)

add_library(lib05_Libraries OBJECT src/nkstring.cpp)
target_include_directories(lib05_Libraries
  PUBLIC  export/
  PRIVATE inc/)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(lib05_Libraries)
endif()
if(COMMAND target_compile_option_baremetal)
  target_compile_option_baremetal(lib05_Libraries)
endif()

if (BUILD_TESTING)
  add_executable(05_Libraries test/main.cpp)
  target_link_libraries(05_Libraries lib05_Libraries CppUTest CppUTestExt)
  add_test(NAME 05_LIBRARIES_ALL COMMAND 05_Libraries)
endif()
