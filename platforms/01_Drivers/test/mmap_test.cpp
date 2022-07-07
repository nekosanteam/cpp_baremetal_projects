#include <cstdint>

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

void mmap_open()
{
    int fd;
    uintptr_t iomap;
    uint32_t v32;

    fd = open("/dev/mem", O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    iomap = (uintptr_t)mmap(0, 0x1000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0x10000000);
    if ((intptr_t)iomap < 0) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    v32 = *((volatile uint32_t*)(iomap + 0x40));
    printf("%08x\n", v32);

    munmap((void*)iomap, 0x1000);
    close(fd);
}

int main()
{
    mmap_open();

    return 0;
}
