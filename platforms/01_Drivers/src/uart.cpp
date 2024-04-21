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
