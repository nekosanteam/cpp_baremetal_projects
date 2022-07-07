/**
 * @file mmio.cpp
 *
 */
#include "mmio.hpp"
#include <cstdint>

#include <stdlib.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

namespace bm {
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
    VirBase spi_base(ptr);
    SPIreg2 reg2(spi_base);
    uint64_t v = reg2.read64(0x04);
}

void mmap_open()
{
    int fd;
    uintptr_t iomap;

    fd = open("/dev/mem", O_RDWR);
    if (fd < 0) {
        exit(EXIT_FAILURE);
    }

    iomap = (uintptr_t)mmap(0, 0x1000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0x10000000);
    if ((intptr_t)iomap < 0) {
        exit(EXIT_FAILURE);
    }

    munmap((void*)iomap, 0x1000);
    close(fd);
}
}
}
