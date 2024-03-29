/* SPDX-License-Identifier: MIT-0 */
#include "gicc.hpp"
#include "mmio.hpp"
#include "uart.hpp"

#include <string>

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	bm::work::UART uart;

	char str[] = "hello,world\r\n";

	uart.init();
	uart.put(str);

	return 0;
}

void operator delete(void* p)
{
	(void)p;
}

void operator delete(void* p, size_t size)
{
	(void)p;
	(void)size;
}
