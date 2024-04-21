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

#ifndef NKFDTLIB_H_
#define NKFDTLIB_H_
/**
 * @file nkfdtlib.h
 */

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
using std::uint32_t;
using std::uint8_t;
using std::uintptr_t;
#else
#include <stddef.h>
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef int      nkfdt_error;
typedef uint32_t nkfdt_tag;

enum {
	NKFDT_OK = 0,
	NKFDT_ERROR,
};

#define NKFDT_BEGIN_NODE 0x01
#define NKFDT_END_NODE   0x02
#define NKFDT_PROP       0x03
#define NKFDT_NOP        0x04
#define NKFDT_END        0x09

struct fdt_header;

nkfdt_error nkfdt_parse_header(const void* fdt, size_t* nextoffset, struct fdt_header* h);

void* nkfdt_skip_node(const void* fdt, size_t* nextoffset, const struct fdt_header* h);
void* nkfdt_skip_prop(const void* fdt, size_t* nextoffset, const struct fdt_header* h);
char* nkfdt_get_string(const void* fdt, size_t str_off, int* strlenp, struct fdt_header* h);

nkfdt_error nkfdt_get_prop_data(const void* fdt, size_t offset, void* buf, size_t* lenp);
nkfdt_error nkfdt_set_prop_data(const void* fdt, size_t offset, const void* buf, size_t len);

void* nks_memcpy(void* dst, const void* src, size_t n);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* NKFDTLIB_H_ */
