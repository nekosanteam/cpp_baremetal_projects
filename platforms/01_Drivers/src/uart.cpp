/**
 * @file uart.cpp
 * 
 */
#include "uart.hpp"
#include "mmio.hpp"

#include <cstddef>
#include <cstdint>
#include <string>

namespace nk {
namespace work {

using MMIO::Register;

namespace devkit {
constexpr MMIO::PhyAddr UART01_ADDR { 0x09000000 };
} // namespace devkit
namespace qemu {
constexpr MMIO::PhyAddr UART01_ADDR { 0x09000000 };
} // namespace qemu

using qemu::UART01_ADDR;
using UART01_BASE = MMIO::PhyBase<UART01_ADDR>;

constexpr Register<UART01_BASE, 0x0000> DR {};
constexpr Register<UART01_BASE, 0x0018> FR {};
constexpr Register<UART01_BASE, 0x0024> IBRD {};
constexpr Register<UART01_BASE, 0x0028> FBRD {};
constexpr Register<UART01_BASE, 0x002C> LCRH {};
constexpr Register<UART01_BASE, 0x0030> CR {};
constexpr Register<UART01_BASE, 0x0038> IMSC {};
constexpr Register<UART01_BASE, 0x0044> ICR {};

UART::UART() { }

UART::~UART() { }

void UART::init()
{
    CR.set(0);
    ICR.set(0x07ff);
    IBRD.set(2);
    FBRD.set(0x000b);
    LCRH.set(0x0060);
    CR.set(0x0301);
}

void UART::put(char c)
{
    do {
        asm volatile("nop");
    } while ((FR.get() & 0x0020) != 0);
    DR.set(c);
}

void UART::put(const char* str)
{
    char c;

    while ((c = *str++) != '\0') {
        put(c);
    }
}

} // namespace work
} // namespace bm
