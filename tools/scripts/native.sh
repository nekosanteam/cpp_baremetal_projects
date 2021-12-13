#!/bin/sh

SOURCE_ROOT=${1:-.}
export GCC_VERSION=${GCC_VERSION:-}
export GCC_SYSROOT=${GCC_SYSROOT:-/usr/aarch64-linux-gnu/}
export CLANG_VERSION=${CLANG_VERSION:--13}
export CLANG_SYSROOT=${CLANG_SYSROOT:-/usr/aarch64-linux-gnu/}
mkdir -p build_all

TARGET1=build_all/native_gcc
rm -rf $TARGET1
CC=gcc${GCC_VERSION} CXX=g++${GCC_VERSION} cmake $SOURCE_ROOT -B $TARGET1 -G Ninja || exit 1
CC=gcc${GCC_VERSION} CXX=g++${GCC_VERSION} cmake --build $TARGET1

TARGET2=build_all/native_clang
rm -rf $TARGET2
CC=clang${CLANG_VERSION} CXX=clang++${CLANG_VERSION} cmake $SOURCE_ROOT -B $TARGET2 -G Ninja || exit 1
CC=clang${CLANG_VERSION} CXX=clang++${CLANG_VERSION} cmake --build $TARGET2
