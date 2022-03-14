cmake_minimum_required(VERSION 3.13)
project(BM02_HAL CXX)
enable_language(C)
enable_language(ASM)

add_library(02_HAL OBJECT src/intc.cpp src/console.cpp src/timer.cpp src/flash.cpp)
target_include_directories(02_HAL
  PUBLIC  export/
  PRIVATE inc/)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(02_HAL)
endif()
if(COMMAND target_compile_option_baremetal)
  target_compile_option_baremetal(02_HAL)
endif()

#add_executable(02_HAL test/main.cpp)
if (TARGET 02_HALTest)
  if(COMMAND target_compile_option_warning)
    target_compile_option_warning(02_HALTest)
  endif()
  target_link_libraries(02_HALTest
    02_HAL
    01_Drivers
    00_Startup)
  if(COMMAND target_link_option_baremetal)
    target_link_option_baremetal(02_HALTest ${BM00_Startup_SOURCE_DIR}/${LDSCRIPT})
  endif()
endif()
