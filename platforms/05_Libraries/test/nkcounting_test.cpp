#include "nkcounting.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void test01()
{
    int i;
    int pos;
    uint32_t Min = 10;
    uint32_t Max = 110;
    nk::CountingSimple<uint32_t> counts;


    for (i=Min; i<Max; i++) {
        counts.update(i);
    }

    printf("min  = %d\n", counts.min());
    printf("max  = %d\n", counts.max());
    printf("mean = %d\n", counts.mean());
}

int main(int argc, char**argv)
{
    test01();
    return 0;
}
