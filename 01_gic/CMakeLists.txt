cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD   11)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD   17)
set(CMAKE_CXX_EXTENSIONS OFF)

PROJECT(BareMetal01_GIC CXX)
ENABLE_LANGUAGE(C ASM)

add_library(lib01_gic OBJECT src/gicc.cpp)
target_include_directories(lib01_gic
  PUBLIC inc/)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(lib01_gic)
endif()

add_executable(01_gic app/main.cpp
  $<$<PLATFORM_ID:Generic>:app/startup.S>)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(01_gic)
endif()
target_link_libraries(01_gic lib01_gic)
set_target_properties(01_gic
  PROPERTIES LINK_DEPENDS $<$<PLATFORM_ID:Generic>:${CMAKE_SOURCE_DIR}/01_gic/app/ldscript_a64.ld> )
