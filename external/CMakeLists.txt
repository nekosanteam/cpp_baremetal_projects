cmake_minimum_required(VERSION 3.16)
project(NkEXTERNAL)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/../tools/cmake)
endif()
set(EXTERNAL_DIR "${PROJECT_SOURCE_DIR}")
#message("external " ${EXTERNAL_DIR})
include(FetchLibraries)
