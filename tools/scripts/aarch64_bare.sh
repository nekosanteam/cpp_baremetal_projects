#!/bin/sh

SOURCE_ROOT=${1:-.}
export GCC_VERSION=${GCC_VERSION:-}
export GCC_SYSROOT=${GCC_SYSROOT:-/usr/aarch64-linux-gnu/}
export CLANG_VERSION=${CLANG_VERSION:--13}
export CLANG_SYSROOT=${CLANG_SYSROOT:-/usr/aarch64-linux-gnu/}
mkdir -p build_all

TARGET5=build_all/aarch64_gcc_bare
rm -rf $TARGET5
cmake $SOURCE_ROOT -B $TARGET5  -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=tools/cmake/aarch64-none-gcc.cmake
cmake --build $TARGET5

TARGET6=build_all/aarch64_clang_bare
rm -rf $TARGET6
cmake $SOURCE_ROOT -B $TARGET6  -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=tools/cmake/aarch64-none-clang.cmake
cmake --build $TARGET6
