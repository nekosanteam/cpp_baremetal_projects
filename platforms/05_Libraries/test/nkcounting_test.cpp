#include "nkcounting.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

using std::uint32_t;
using std::printf;

void test01()
{
    int i;
    int pos;
    uint32_t Min = 10;
    uint32_t Max = 110;
    nk::CountingSimple<uint32_t> counts;

    for (i=Min; i<Max; i++) {
        counts.inc(i);
    }

    printf("min  = %d\n", counts.min());
    printf("max  = %d\n", counts.max());
    printf("mean = %d\n", counts.mean());
    printf("estimate = %d\n", counts.estimate());
}

int main(int argc, char**argv)
{
    test01();
    return 0;
}
