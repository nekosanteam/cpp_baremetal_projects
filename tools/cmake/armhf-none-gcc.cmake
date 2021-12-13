set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(GCC_CROSS_COMPILE "arm-linux-gnueabihf-")
set(GCC_VERSION $ENV{GCC_VERSION})
include(_gcc-common)

set(CMAKE_SYSROOT $ENV{GCC_SYSROOT})
set(CMAKE_INCLUDE_PATH ${CMAKE_SYSROOT}/include)
set(CMAKE_LIBRARY_PATH ${CMAKE_SYSROOT}/lib)
set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)

set(BUILD_TESTING OFF CACHE BOOL "don't build testing.")
