#!/bin/sh

export GCC_VERSION=
export CLANG_VERSION=-13
mkdir build_all

TARGET1=build_all/native_gcc
rm -rf $TARGET1
cmake . -B $TARGET1 || exit 1
cmake --build $TARGET1 || exit 1

TARGET2=build_all/native_clang
rm -rf $TARGET2
CC=clang${CLANG_VERSION} CXX=clang++${CLANG_VERSION} cmake . -B $TARGET2 || exit 1
CC=clang${CLANG_VERSION} CXX=clang++${CLANG_VERSION} cmake --build $TARGET2 || exit 1

TARGET3=build_all/aarch64_gcc
rm -rf $TARGET3
cmake . -B $TARGET3 -DCMAKE_TOOLCHAIN_FILE=tools/cmake/aarch64-linux-gcc.cmake
cmake --build $TARGET3

TARGET4=build_all/aarch64_clang
rm -rf $TARGET4
cmake . -B $TARGET4 -DCMAKE_TOOLCHAIN_FILE=tools/cmake/aarch64-linux-clang.cmake
cmake --build $TARGET4

TARGET5=build_all/aarch64_gcc_bare
rm -rf $TARGET5
cmake . -B $TARGET5 -DCMAKE_TOOLCHAIN_FILE=tools/cmake/aarch64-none-gcc.cmake
cmake --build $TARGET5

TARGET6=build_all/aarch64_clang_bare
rm -rf $TARGET6
cmake . -B $TARGET6 -DCMAKE_TOOLCHAIN_FILE=tools/cmake/aarch64-none-clang.cmake
cmake --build $TARGET6
