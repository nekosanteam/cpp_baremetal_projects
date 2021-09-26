set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CLANG_TRIPLE "aarch64-linux-gnu")
set(CLANG_VERSION $ENV{CLANG_VERSION})
include(_clang-common)

set(BUILD_TESTING OFF)
