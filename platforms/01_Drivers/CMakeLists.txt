cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD   11)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD   17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(BareMetal01_Drivers CXX)
enable_language(C)
enable_language(ASM)

add_library(lib01_Drivers OBJECT src/gicc.cpp src/mmio.cpp src/uart.cpp)
target_include_directories(lib01_Drivers
  PUBLIC inc/)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(lib01_Drivers)
endif()
if(COMMAND target_compile_option_baremetal)
  target_compile_option_baremetal(lib01_Drivers)
endif()

add_executable(01_Drivers test/main.cpp)
if (TARGET 01_Drivers)
  if(COMMAND target_compile_option_warning)
    target_compile_option_warning(01_Drivers)
  endif()
  target_link_libraries(01_Drivers
    lib01_Drivers
    lib00_Startup)
  if(COMMAND target_link_option_baremetal)
    target_link_option_baremetal(01_Drivers ${BareMetal00_Startup_SOURCE_DIR}/${LDSCRIPT})
  endif()
endif()
