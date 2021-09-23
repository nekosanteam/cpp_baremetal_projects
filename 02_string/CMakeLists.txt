cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD   11)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD   17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(BareMetal02_STRING CXX)
enable_language(C)
enable_language(ASM)

add_library(lib02_nkstring OBJECT src/nkstring.cpp)
target_include_directories(lib02_nkstring
  PUBLIC inc/)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(lib02_nkstring)
endif()
if(COMMAND target_compile_option_baremetal)
  target_compile_option_baremetal(lib02_nkstring)
endif()

add_executable(02_string app/main.cpp
  $<$<PLATFORM_ID:Generic>:app/startup_a64.S>)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(02_string)
endif()
target_link_libraries(02_string lib02_nkstring CppUTest CppUTestExt)
if(COMMAND target_link_option_baremetal)
  target_link_option_baremetal(02_string ${PROJECT_SOURCE_DIR}/app/ldscript_a64.ld)
endif()

if (BUILD_TESTING)
  add_test(NAME 02_STRING_ALL COMMAND 02_string)
endif()
