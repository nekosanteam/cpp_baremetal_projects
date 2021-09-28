#!/bin/sh

export GCC_VERSION=${GCC_VERSION:-}
export GCC_SYSROOT=${GCC_SYSROOT:-/usr/aarch64-linux-gnu/}
export CLANG_VERSION=${CLANG_VERSION:--13}
export CLANG_SYSROOT=${CLANG_SYSROOT:-/usr/aarch64-linux-gnu/}
mkdir -p build_all
tools/build_sh/native.sh
tools/build_sh/aarch64.sh
tools/build_sh/aarch64_bare.sh
