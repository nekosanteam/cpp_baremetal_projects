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
    nk::Counting countsNum;
    nk::CountingSimple<uint32_t> countsSimple;
    nk::CountingSpecifyAverage<int32_t> countsAve(30);

    for (i=Min; i<Max; i++) {
        countsNum.inc();
        countsSimple.inc(i);
        countsAve.inc(i);
    }

    printf("min  = %d, %d\n", countsSimple.min(), countsAve.min());
    printf("max  = %d, %d\n", countsSimple.max(), countsAve.max());
    printf("mean = %d, %d\n", countsSimple.mean(), countsAve.mean());
    printf("estimate = %d, %d\n", countsNum.estimate(), countsAve.estimate());
    printf("estimate = %d\n", countsSimple.estimate());
}

int main(int argc, char**argv)
{
    test01();
    return 0;
}
