set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(GCC_CROSS_COMPILE "aarch64-linux-gnu-")
set(GCC_VERSION $ENV{GCC_VERSION})
include(_gcc-common)
