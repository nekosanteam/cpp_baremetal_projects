#include <stddef.h>
#include <stdint.h>

char buffer[16];

int main(void)
{
    for (int i=0; i<16; i++) {
        buffer[i] = 1;
    }
    return 0;
}
