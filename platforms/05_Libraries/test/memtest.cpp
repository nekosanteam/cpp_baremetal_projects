/* SPDX-License-Identifier: MIT-0 */
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
