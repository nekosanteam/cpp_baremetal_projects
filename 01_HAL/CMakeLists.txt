cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD   11)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD   17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(BareMetal01_HAL CXX)
enable_language(C)
enable_language(ASM)

add_library(lib01_HAL OBJECT src/gicc.cpp src/mmio.cpp src/uart.cpp)
target_include_directories(lib01_HAL
  PUBLIC inc/)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(lib01_HAL)
endif()
if(COMMAND target_compile_option_baremetal)
  target_compile_option_baremetal(lib01_HAL)
endif()

add_executable(01_HAL app/main.cpp)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(01_HAL)
endif()
target_link_libraries(01_HAL
  lib01_HAL
  $<$<PLATFORM_ID:Generic>:lib00_Startup>)
if(COMMAND target_link_option_baremetal)
  target_link_option_baremetal(01_HAL ${BareMetal00_Startup_SOURCE_DIR}/app/ldscript_a64.ld)
endif()
