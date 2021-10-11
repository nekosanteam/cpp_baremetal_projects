cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD   11)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD   17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(BareMetal01_GIC CXX)
enable_language(C)
enable_language(ASM)

add_library(lib01_gic OBJECT src/gicc.cpp src/uart.cpp)
target_include_directories(lib01_gic
  PUBLIC inc/)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(lib01_gic)
endif()
if(COMMAND target_compile_option_baremetal)
  target_compile_option_baremetal(lib01_gic)
endif()

add_executable(01_gic app/main.cpp)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(01_gic)
endif()
target_link_libraries(01_gic
  lib01_gic
  $<$<PLATFORM_ID:Generic>:lib00_startup>)
if(COMMAND target_link_option_baremetal)
  target_link_option_baremetal(01_gic ${BareMetal00_Startup_SOURCE_DIR}/app/ldscript_a64.ld)
endif()
