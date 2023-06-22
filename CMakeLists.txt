cmake_minimum_required(VERSION 3.13)
project(CppBareMetal)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/tools/cmake)

message("CMAKE_SYSTEM:           " ${CMAKE_SYSTEM})
message("CMAKE_SYSTEM_NAME:      " ${CMAKE_SYSTEM_NAME})
message("CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR})
message("CMAKE_CROSSCOMPILING:   " ${CMAKE_CROSSCOMPILING})

include(CTest)
include(CTestCoverageCollectGCOV)
include(BuildBareMetal)
include(CompilerWarning)

#add_subdirectory(external)
add_subdirectory(platforms)
add_subdirectory(src)
