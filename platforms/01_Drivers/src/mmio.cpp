/* SPDX-License-Identifier: BSD-1-Clause */
/*
 * Copyright 2023,2024 nekosanteam <1688092+nekosanteam@users.noreply.github.com>. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions
 *    and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS
 * AND CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file mmio.cpp
 *
 */
#include "mmio.hpp"
#include <cstdint>

#include <stdlib.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

namespace nk {
namespace work {

using MMIO::PhyBase;
using SPIreg = MMIO::RegisterTableT<PhyBase<0xc11000000>>;
using MMIO::VirBase;
using SPIreg2 = MMIO::RegisterTableT<VirBase>;

class SPI : public SPIreg {
public:
	void init()
	{
		uint32_t v = read32(0x00);
		write32(0x04, v | 0x01);
	}
};

void test(void* ptr)
{
	//    char buf[16];
	SPI* reg = nullptr;
	reg->init();
	VirBase  spi_base(ptr);
	SPIreg2  reg2(spi_base);
	uint64_t v = reg2.read64(0x04);
	reg2.write32(0x08, v);
}

void mmap_open()
{
	int       fd;
	uintptr_t iomap;

	fd = open("/dev/mem", O_RDWR);
	if (fd < 0) {
		exit(EXIT_FAILURE);
	}

	iomap = (uintptr_t)mmap(0, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x10000000);
	if ((intptr_t)iomap < 0) {
		exit(EXIT_FAILURE);
	}

	munmap((void*)iomap, 0x1000);
	close(fd);
}

} // namespace work
} // namespace bm
