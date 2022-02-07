cmake_minimum_required(VERSION 3.13)
project(BareMetal05_Libraries CXX)
enable_language(C)
enable_language(ASM)

add_library(05_Libraries OBJECT
  src/nkstring.cpp
  src/nklogger.cpp)
target_include_directories(05_Libraries
  PUBLIC  export/
  PRIVATE inc/)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(05_Libraries)
endif()
if(COMMAND target_compile_option_baremetal)
  target_compile_option_baremetal(05_Libraries)
endif()

if (BUILD_TESTING)
  add_executable(05_LibrariesTest test/main.cpp)
  target_link_libraries(05_LibrariesTest 05_Libraries ntshell CppUTest CppUTestExt)
  add_test(NAME 05_LIBRARIES_ALL COMMAND 05_LibrariesTest)
endif()
