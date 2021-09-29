#!/bin/sh

SOURCE_ROOT=${1:-.}
export GCC_VERSION=${GCC_VERSION:-}
export GCC_SYSROOT=${GCC_SYSROOT:-/usr/aarch64-linux-gnu/}
export CLANG_VERSION=${CLANG_VERSION:--13}
export CLANG_SYSROOT=${CLANG_SYSROOT:-/usr/aarch64-linux-gnu/}
mkdir -p build_all

TARGET3=build_all/aarch64_gcc
rm -rf $TARGET3
cmake $SOURCE_ROOT -B $TARGET3 -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=tools/cmake/aarch64-linux-gcc.cmake
cmake --build $TARGET3

TARGET4=build_all/aarch64_clang
rm -rf $TARGET4
cmake $SOURCE_ROOT -B $TARGET4 -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=tools/cmake/aarch64-linux-clang.cmake
cmake --build $TARGET4
