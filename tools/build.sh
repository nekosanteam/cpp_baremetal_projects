#!/bin/sh

TARGET1=build_native_gcc
rm -rf $TARGET1
cmake . -B $TARGET1 || exit 1
cmake --build $TARGET1 || exit 1

TARGET2=build_native_clang
rm -rf $TARGET2
CC=clang CXX=clang++ cmake . -B $TARGET2 || exit 1
CC=clang CXX=clang++ cmake --build $TARGET2 || exit 1

TARGET3=build_aarch64_gcc
rm -rf $TARGET3
cmake . -B $TARGET3 --toolchain tools/cmake/aarch64-linux-gcc.cmake || exit 1
cmake --build $TARGET3

TARGET4=build_aarch64_clang
rm -rf $TARGET4
cmake . -B $TARGET4 --toolchain tools/cmake/aarch64-linux-clang.cmake
cmake --build $TARGET4

TARGET5=build_aarch64_gcc_bare
rm -rf $TARGET5
cmake . -B $TARGET5 --toolchain tools/cmake/aarch64-none-gcc.cmake
cmake --build $TARGET5

TARGET6=build_aarch64_clang_bare
rm -rf $TARGET6
cmake . -B $TARGET6 --toolchain tools/cmake/aarch64-none-clang.cmake
cmake --build $TARGET6
