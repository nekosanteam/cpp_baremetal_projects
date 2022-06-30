set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(GCC_CROSS_COMPILE "aarch64-linux-gnu-")
set(GCC_VERSION $ENV{GCC_VERSION})
include(_gcc-common)

set(CMAKE_SYSROOT $ENV{GCC_SYSROOT})
set(CMAKE_INCLUDE_PATH ${CMAKE_SYSROOT}/include)
set(CMAKE_LIBRARY_PATH ${CMAKE_SYSROOT}/lib)
set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
