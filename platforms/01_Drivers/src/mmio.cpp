/**
 * @file mmio.cpp
 *
 */
#include "mmio.hpp"
#include <cstdint>
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
	}
};

void test(void* ptr)
{
    char buf[16];
    SPI* reg = nullptr;
    reg->init();
//    SPIreg2 reg2(ptr);
//    uint64_t v = reg2.read64(0x04);
}
}
}
