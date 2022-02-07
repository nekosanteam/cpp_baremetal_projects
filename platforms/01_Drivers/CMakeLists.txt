cmake_minimum_required(VERSION 3.13)
project(BareMetal01_Drivers CXX)
enable_language(C)
enable_language(ASM)

add_library(01_Drivers OBJECT src/gicc.cpp src/mmio.cpp src/uart.cpp)
target_include_directories(01_Drivers
  PUBLIC inc/)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(01_Drivers)
endif()
if(COMMAND target_compile_option_baremetal)
  target_compile_option_baremetal(01_Drivers)
endif()

add_executable(01_DriversTest test/main.cpp)
if (TARGET 01_DriversTest)
  if(COMMAND target_compile_option_warning)
    target_compile_option_warning(01_DriversTest)
  endif()
  target_link_libraries(01_DriversTest
    01_Drivers
    00_Startup)
  if(COMMAND target_link_option_baremetal)
    target_link_option_baremetal(01_DriversTest ${BareMetal00_Startup_SOURCE_DIR}/${LDSCRIPT})
  endif()
endif()
