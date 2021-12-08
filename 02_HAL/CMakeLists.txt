cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD   11)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD   17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(BareMetal02_HAL CXX)
enable_language(C)
enable_language(ASM)

add_library(lib02_HAL OBJECT src/gicc.cpp src/mmio.cpp src/uart.cpp)
target_include_directories(lib02_HAL
  PUBLIC inc/)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(lib02_HAL)
endif()
if(COMMAND target_compile_option_baremetal)
  target_compile_option_baremetal(lib02_HAL)
endif()

add_executable(02_HAL test/main.cpp)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(02_HAL)
endif()
target_link_libraries(02_HAL
  lib02_HAL
  lib00_Startup)
if(COMMAND target_link_option_baremetal)
  target_link_option_baremetal(02_HAL ${BareMetal00_Startup_SOURCE_DIR}/${LDSCRIPT})
endif()
