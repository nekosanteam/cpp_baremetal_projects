cmake_minimum_required(VERSION 3.14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/tools/cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(CppBareMetal CXX)

include(CompilerWarning)
add_subdirectory(01_gic)
