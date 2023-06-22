cmake_minimum_required(VERSION 3.13)
project(PLATFORMS05_Libraries CXX)
enable_language(C)
enable_language(ASM)

add_library(05_Libraries OBJECT
  src/nkcounting.cpp
  src/nkfdtlib.cpp
  src/nklogger.cpp
  src/nkqueue.cpp
  src/nkstring.cpp)
target_include_directories(05_Libraries
  PUBLIC  export/
  PRIVATE inc/)
target_compile_options(05_Libraries
  PRIVATE -ffunction-sections -Wall -Wno-unused)
if(COMMAND target_compile_option_warning)
  target_compile_option_warning(05_Libraries)
endif()
if(COMMAND target_compile_option_baremetal)
  target_compile_option_baremetal(05_Libraries)
endif()

if (BUILD_TESTING)
  add_executable(05_LibrariesTest test/nkstring_test.cpp)
  target_link_libraries(05_LibrariesTest 05_Libraries CppUTest CppUTestExt)
  add_test(NAME 05_LIBRARIES_ALL COMMAND 05_LibrariesTest)

  add_executable(05_LibrariesConsole test/consoletest.cpp)
  target_link_libraries(05_LibrariesConsole 05_Libraries ntshell)

  add_executable(05_LibrariesMemtest test/memtest.cpp)
#  target_link_libraries(05_LibrariesMemtest 05_Libraries ntshell)

  add_executable(05_BarrierTest test/barrier_test.cpp)
  target_compile_options(05_BarrierTest PRIVATE -O2)
  target_link_libraries(05_BarrierTest -lpthread)

  add_executable(05_LibrariesCountingTest test/nkcounting_test.cpp)
  target_link_libraries(05_LibrariesCountingTest 05_Libraries)

  add_executable(05_LibrariesQueueTest test/nkqueue_test.cpp)
  target_link_libraries(05_LibrariesQueueTest 05_Libraries)

endif()
