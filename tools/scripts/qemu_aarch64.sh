#!/bin/sh

# u-boot ビルド： ARCH=arm64, CROSS_COMPILE=aarch64-linux-gnu- を設定。
# make O=build qemu_arm64_defconfig ; cd build; make
qemu-system-aarch64 -M virt -cpu cortex-a53 -nographic -serial mon:stdio -bios u-boot.bin
