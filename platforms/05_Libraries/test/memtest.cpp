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

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <iostream>

using std::size_t;
using std::uint32_t;
using std::cout;
using std::endl;

extern "C" {
size_t memtest_chk01(uint32_t* begin, uint32_t* end, uint32_t pat);
size_t memtest_chk02(uint32_t* begin, uint32_t* end, uint32_t pat);
}

size_t memtest_chk01(uint32_t* begin, uint32_t* end, uint32_t pat)
{
    volatile uint32_t* ptr;

    for (ptr = begin; ptr < end; ptr++) {
        *ptr = pat;
    }
    for (ptr = begin; ptr < end; ptr++) {
        if (*ptr != pat) {
            return (size_t)(ptr - begin);
        }
    }

    return (size_t)(end - begin);
}

size_t memtest_chk02(uint32_t* begin, uint32_t* end, uint32_t pat)
{
    volatile uint32_t* ptr;

    for (ptr = begin; ptr < end; ptr++) {
        *ptr = pat;
    }
    ptr = end;
    do {
        ptr--;
        if (*ptr != pat) {
            return (size_t)(ptr - begin);
        }
    } while (ptr > begin);

    return (size_t)(end - begin);
}

int main(int argc, char** argv)
{
    uint32_t* buf;
    size_t    sz = 1024*1024;
    size_t    ret;

    buf = new uint32_t[sz];

    ret = memtest_chk01(buf, buf+sz, 0);
    cout << "memtest_chk01 = " << ret << endl;

    ret = memtest_chk02(buf, buf+sz, 0xFFFFFFFFu);
    cout << "memtest_chk02 = " << ret << endl;

    return 0;
}
