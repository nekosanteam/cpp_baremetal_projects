cmake_minimum_required(VERSION 3.13)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD     11)
set(CMAKE_C_EXTENSIONS   OFF)
set(CMAKE_CXX_STANDARD   17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(NkPLATFORMS)

add_subdirectory(00_Startup)
add_subdirectory(01_Drivers)
add_subdirectory(02_HAL)
add_subdirectory(03_OS)
add_subdirectory(04_FAL)
add_subdirectory(05_Libraries)
add_subdirectory(06_MAL)
add_subdirectory(07_Platforms)
