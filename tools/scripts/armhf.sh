#!/bin/sh

SOURCE_ROOT=${1:-.}
export GCC_VERSION=${GCC_VERSION:-}
export GCC_SYSROOT=${GCC_SYSROOT:-/usr/arm-linux-gnueabihf/}
export CLANG_VERSION=${CLANG_VERSION:--13}
export CLANG_SYSROOT=${CLANG_SYSROOT:-/usr/arm-linux-gnueabihf/}
mkdir -p build_all

TARGET7=build_all/armhf_gcc
rm -rf $TARGET7
cmake $SOURCE_ROOT -B $TARGET7 -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=tools/cmake/armhf-linux-gcc.cmake
cmake --build $TARGET7

TARGET8=build_all/armhf_clang
rm -rf $TARGET8
cmake $SOURCE_ROOT -B $TARGET8 -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=tools/cmake/armhf-linux-clang.cmake
cmake --build $TARGET8
