#!/bin/sh

SOURCE_ROOT=${1:-.}
export GCC_VERSION=${GCC_VERSION:-}
export GCC_SYSROOT=${GCC_SYSROOT:-/usr/arm-linux-gnueabihf/}
export CLANG_VERSION=${CLANG_VERSION:--13}
export CLANG_SYSROOT=${CLANG_SYSROOT:-/usr/arm-linux-gnueabihf/}
mkdir -p build_all

TARGET9=build_all/armhf_gcc_bare
rm -rf $TARGET9
cmake $SOURCE_ROOT -B $TARGET9  -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=tools/cmake/armhf-none-gcc.cmake
cmake --build $TARGET9

TARGET10=build_all/armhf_clang_bare
rm -rf $TARGET10
cmake $SOURCE_ROOT -B $TARGET10  -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=tools/cmake/armhf-none-clang.cmake
cmake --build $TARGET10
