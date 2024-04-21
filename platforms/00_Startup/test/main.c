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

#include <stddef.h>
#include <stdint.h>

char buffer[16];
void put_message();

int main(void)
{
	for (int i = 0; i < 16; i++) {
		buffer[i] = 1;
	}
	put_message();
	return 0;
}

#if !defined(BM_BAREMETAL)
#if defined(__linux)
#include <sys/syscall.h>
unsigned int bm_sys_write(int fd, const char* buf, int size)
{
	unsigned int ret = 0;

#ifdef __x86_64__
	__asm volatile("syscall"
	               : "=a"(ret)
	               //                 EDI      RSI       RDX
	               : "0"(SYS_write), "D"(fd), "S"(buf), "d"(size)
	               : "rcx", "r11", "memory");
#elif __aarch64__
	__asm volatile("mov x8, __NR_write; "
	               "svc #0");
#endif
	return ret;
}

void put_message()
{
	bm_sys_write(1, "hello,world\n", 13);
}
#else
void put_message() { }
#endif // __linux

#else // BAREMETAL
void put_message() { }
#endif
