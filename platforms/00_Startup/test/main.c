#include <stddef.h>
#include <stdint.h>

char buffer[16];
void put_message();

int main(void)
{
    for (int i=0; i<16; i++) {
        buffer[i] = 1;
    }
    put_message();
    return 0;
}

#if !defined(BAREMETAL)
#if defined(__linux)
#include <sys/syscall.h>
unsigned int
bm_sys_write(int fd, const char* buf, int size)
{
    unsigned int ret;
    __asm volatile (
        "syscall"
        : "=a" (ret)
        //                 EDI      RSI       RDX
        : "0"(SYS_write), "D"(fd), "S"(buf), "d"(size)
        : "rcx", "r11", "memory"
    );
    return ret;
}

void put_message()
{
    bm_sys_write(1, "hello,world\n", 13);
}
#else
void put_message()
{
}
#endif // __linux

#else // BAREMETAL
void put_message()
{
}
#endif
