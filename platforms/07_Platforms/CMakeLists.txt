cmake_minimum_required(VERSION 3.13)

add_library(PlatformBase OBJECT src/log.cpp)
target_include_directories(PlatformBase
  PUBLIC export/)

add_executable(07_PlatformBaseTest test/test_base.cpp)
if (TARGET 07_PlatformBaseTest)
  target_link_libraries(07_PlatformBaseTest PRIVATE PlatformBase)
endif()
