cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD   11)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD   17)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_FLAGS   "-Wall")
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
PROJECT(BareMetal01_GIC CXX)
ENABLE_LANGUAGE(C ASM)

add_executable(01gicc src/gicc.cpp src/main.cpp)
target_include_directories(01gicc PUBLIC inc/)
