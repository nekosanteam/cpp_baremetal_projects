#include "gicc.hpp"
#include "mmio.hpp"
#include "uart.hpp"

#include <string>

int main(int argc, char** argv)
{
    work::UART uart;
    char str[] = "hello,world\r\n";

    uart.init();
    uart.put(str);

	return 0;
}

void operator delete(void* p)
{
}

void operator delete(void* p, size_t size)
{
}

