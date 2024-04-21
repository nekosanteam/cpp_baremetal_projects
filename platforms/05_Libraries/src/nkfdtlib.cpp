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

/**
 * @file nkfdtlib.cpp
 */
/* reference: https://www.devicetree.org/specification/ [v0.3, v0.4-rc1] */

#include "nkfdtlib.h"

#include <cstdint>

using std::size_t;
using std::uint8_t;
using std::uint32_t;
using std::uintptr_t;

void* memcpy(void* dst, const void* src, size_t n) __attribute__((weak, alias ("nks_memcpy")));

int nks_memcmp(const void* data1, const void* data2, size_t n)
{
    const uint8_t* r1 = (const uint8_t*)data1;
    const uint8_t* r2 = (const uint8_t*)data2;
    
    for (size_t i=0; i<n; i++) {
        if (*r1 != *r2) {
            if (*r1 < *r2) {
                return -1;
            }
            else {
                return 1;
            }
        }
        r1++;
        r2++;
    }

    return 0;
}

void* nks_memcpy(void* dst, const void* src, size_t n)
{
    uint8_t* p1 = (uint8_t*)dst;
    const uint8_t* p2 = (const uint8_t*)src;

    for (size_t i=0; i<n; i++) {
        *p1 = *p2;
        p1++;
        p2++;
    }

    return dst;
}

static size_t nks_strnlen(const char* str, size_t n)
{
    size_t i;

    for (i=0; i<n; i++) {
        if (*str == '\0') {
            return i;
        }
        str++;
    }

    return i;
}

static uint8_t read8(const void* p)
{
    return *(uint8_t*)p;
}

static uint32_t read32(const void* p)
{
    uint32_t r = 0;

    r = (uint32_t)(*((uint8_t*)p));
    r = (r << 8) | (uint32_t)(*(((uint8_t*)p) + 1));
    r = (r << 8) | (uint32_t)(*(((uint8_t*)p) + 2));
    r = (r << 8) | (uint32_t)(*(((uint8_t*)p) + 3));
    return r;
}

static void write8(const void* p, uint8_t v)
{
    *(uint8_t*)p = v;
}

static void write32(const void* p, uint32_t v)
{
    *(uint8_t*)p = (uint8_t)(v & 0x00FF);
    *(((uint8_t*)p) + 1) = (uint8_t)((v >>  8) & 0xFF);
    *(((uint8_t*)p) + 2) = (uint8_t)((v >> 16) & 0xFF);
    *(((uint8_t*)p) + 3) = (uint8_t)((v >> 24) & 0xFF);
}

static inline void* offset_ptr(const void* fdt, size_t offset)
{
    return (void*)(((const uint8_t*)fdt) + offset);
}

static inline size_t round4(size_t s)
{
    return ((s + 3) & ~0x03u);
}

nkfdt_tag nkfdt_get_tag(const void* fdt, size_t offset)
{
    return read32(offset_ptr(fdt, offset));
}

#define UNUSED(v) do { (void)v; } while (0)

struct fdt_header {
    uint32_t totalsize;
    uint32_t off_dt_struct;
    uint32_t off_dt_strings;
    uint32_t off_mem_rsvmap;
    uint32_t version;
    uint32_t last_comp_version;
    uint32_t boot_cpuid_phys;
    uint32_t size_dt_strings;
    uint32_t size_dt_struct;
};

nkfdt_error nkfdt_parse_header(const void* fdt, size_t *nextoffset, struct fdt_header* h)
{
    size_t   offset;
    uint32_t version;
    uint32_t last_comp_version;

    // magic.
    if (nks_memcmp("\xD0\x0D\xFE\xED", offset_ptr(fdt, 0), 4) != 0) {
        return NKFDT_ERROR;
    }
    offset = 4;
    // totalsize.
    if (h) { h->totalsize = read32(offset_ptr(fdt, offset)); }
    offset += 4;
    // off_dt_struct.
    if (h) { h->off_dt_struct = read32(offset_ptr(fdt, offset)); }
    offset += 4;
    // off_dt_strings;
    if (h) { h->off_dt_strings = read32(offset_ptr(fdt, offset)); }
    offset += 4;
    // off_mem_rsvmap;
    if (h) { h->off_mem_rsvmap = read32(offset_ptr(fdt, offset)); }
    offset += 4;
    // version;
    version = read32(offset_ptr(fdt, offset));
    if (h) { h->version = version; }
    offset += 4;
    // last_comp_version.
    last_comp_version = read32(offset_ptr(fdt, offset));
    if (h) { h->last_comp_version = last_comp_version; }
    offset += 4;
    // boot_cpuid_phys.
    if (h) { h->boot_cpuid_phys = read32(offset_ptr(fdt, offset)); }
    offset += 4;
    // size_dt_strings.
    if (h) { h->size_dt_strings = read32(offset_ptr(fdt, offset)); }
    offset += 4;
    // size_dt_struct.
    if (h) { h->size_dt_struct = read32(offset_ptr(fdt, offset)); }
    offset += 4;

    if (version != 0x11) {
        return NKFDT_ERROR;
    }
    if (last_comp_version > 0x10) {
        return NKFDT_ERROR;
    }

    if (nextoffset) {
        *nextoffset = offset;
    }
    return NKFDT_OK;
}

void* nkfdt_skip_node(const void* fdt, size_t* nextoffset, const struct fdt_header* h)
{
    nkfdt_tag tag;
    size_t    len;
    size_t    offset;
    int       level;

    if (nextoffset == NULL) {
        return NULL;
    }
    if (h == NULL) {
        return NULL;
    }
    offset = *nextoffset;
    level = 0;

    do {
        tag = read32(offset_ptr(fdt, offset));
        switch (tag) {
        case NKFDT_BEGIN_NODE:
            offset += 4;
            ++level;
            len = nks_strnlen((char*)(offset_ptr(fdt, offset)), h->size_dt_struct);
            offset += round4(len+1);
            *nextoffset = offset;
            break;

        case NKFDT_END_NODE:
            offset += 4;
            --level;
            *nextoffset = offset;
            break;

        case NKFDT_NOP:
            offset += 4;
            *nextoffset = offset;
            break;
        
        case NKFDT_PROP:
            *nextoffset = offset;
            (void)nkfdt_skip_prop(fdt, nextoffset, h);
            offset = *nextoffset;
            break;

        case NKFDT_END:
            *nextoffset = offset;
            break;

        }
    } while ((level != 0) && (tag != NKFDT_END));

    return offset_ptr(fdt, offset);
}

void* nkfdt_skip_prop(const void* fdt, size_t* nextoffset, const struct fdt_header* h)
{
    nkfdt_tag tag;
    uint32_t  len;
    size_t    str_off;
    size_t    offset;

    if (nextoffset == NULL) {
        return NULL;
    }
    if (h == NULL) {
        return NULL;
    }
    offset = *nextoffset;

    tag = read32(offset_ptr(fdt, offset));
    if (tag != NKFDT_PROP) {
        return NULL;
    }
    offset += 4;
    len     = read32(offset_ptr(fdt, offset));
    offset += 4;
    str_off = read32(offset_ptr(fdt, offset));
    offset += 4;

    offset += round4(len);

    *nextoffset = offset;
    return offset_ptr(fdt, offset);
}

char* nkfdt_get_string(const void* fdt, size_t str_off, int* strlenp, struct fdt_header* h)
{
    char* str;

    str = (char*)offset_ptr(fdt, h->off_dt_strings + str_off);
    if (str == NULL) {
        return NULL;
    }

    if (strlenp) {
        size_t len;
        len = nks_strnlen(str, h->size_dt_strings);
        *strlenp = len;
    }

    return str;
}

int nkfdt_match_node(const void* fdt, size_t* offset, const char* node_name, struct fdt_header* h)
{
    size_t len;

    len = nks_strnlen(node_name, h->size_dt_struct) + 1;
    if (nks_memcmp(node_name, (char*)offset_ptr(fdt, *offset + 4), len) != 0) {
        return 0;
    }
    *offset += 4;
    *offset += round4(len);
    return 1;
}

int nkfdt_match_prop(const void* fdt, size_t* offset, const char* prop_name, struct fdt_header* h)
{
    size_t match_len;
    size_t prop_len;
    size_t str_off;
    char*  prop_str;

    match_len = nks_strnlen(prop_name, h->size_dt_strings) + 1;

    prop_len = read32(offset_ptr(fdt, *offset + 4));
    str_off  = read32(offset_ptr(fdt, *offset + 8));
    prop_str = nkfdt_get_string(fdt, str_off, NULL, h);
    if (prop_str == NULL) {
        return 0;
    }
    if (nks_memcmp(prop_name, prop_str, match_len) != 0) {
        return 0;
    }

    return 1;
}

nkfdt_error nkfdt_get_prop_data(const void* fdt, size_t offset, void* buf, size_t* lenp)
{
    size_t prop_len;

    prop_len = read32(offset_ptr(fdt, offset + 4));
    if ((lenp == NULL) || (*lenp < prop_len)) {
        return NKFDT_ERROR;
    }
    nks_memcpy(buf, offset_ptr(fdt, offset + 12), prop_len);
    *lenp = prop_len;

    return NKFDT_OK;
}

nkfdt_error nkfdt_set_prop_data(const void* fdt, size_t offset, const void* buf, size_t len)
{
    size_t prop_len;

    prop_len = read32(offset_ptr(fdt, offset + 4));
    if (len != prop_len) {
        return NKFDT_ERROR;
    }
    nks_memcpy(offset_ptr(fdt, offset + 12), buf, prop_len);

    return NKFDT_OK;
}
