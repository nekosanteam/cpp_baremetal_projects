cmake_minimum_required(VERSION 3.13)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/tools/cmake)
project(CppBareMetal)

message("CMAKE_SYSTEM:           " ${CMAKE_SYSTEM})
message("CMAKE_SYSTEM_NAME:      " ${CMAKE_SYSTEM_NAME})
message("CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR})
message("CMAKE_CROSSCOMPILING:   " ${CMAKE_CROSSCOMPILING})

include(CTest)
include(CTestCoverageCollectGCOV)
include(BuildBareMetal)
include(CompilerWarning)
include(FetchLibraries)

add_subdirectory(platforms)
add_subdirectory(src)
