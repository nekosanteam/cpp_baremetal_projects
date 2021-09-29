#!/bin/sh

SOURCE_ROOT=${1:-.}
export GCC_VERSION=${GCC_VERSION:-}
export GCC_SYSROOT=${GCC_SYSROOT:-/usr/aarch64-linux-gnu/}
export CLANG_VERSION=${CLANG_VERSION:--13}
export CLANG_SYSROOT=${CLANG_SYSROOT:-/usr/aarch64-linux-gnu/}
mkdir -p build_all
$SOURCE_ROOT/tools/scripts/native.sh $SOURCE_ROOT
$SOURCE_ROOT/tools/scripts/aarch64.sh $SOURCE_ROOT
$SOURCE_ROOT/tools/scripts/aarch64_bare.sh $SOURCE_ROOT
