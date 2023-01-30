/* reference: https://www.devicetree.org/specification/ [v0.3, v0.4-rc1] */
#include "nkfdtlib.h"

#include <cstdint>

using std::size_t;
using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::uintptr_t;

int nks_memcmp(const void* data1, const void* data2, size_t n)
{
    const uint8_t* r1 = (const uint8_t*)data1;
    const uint8_t* r2 = (const uint8_t*)data2;
    
    size_t i;

    for (i=0; i<n; i++) {
        if (*r1 != *r2) {
            if (*r1 < *r2) {
                return -1;
            }
            else {
                return 1;
            }
            r1++;
            r2++;
        }
    }

    return 0;
}

void* nks_memcpy(void* dst, const void* src, size_t n)
{
    uint8_t* p1 = (uint8_t*)dst;
    const uint8_t* p2 = (const uint8_t*)src;
    size_t i;

    for (i=0; i<n; i++) {
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

static uint16_t read16(const void* p)
{
    uint16_t r = 0;

    r = (uint16_t)(*((uint8_t*)p));
    r = (r << 8) | (uint16_t)(*(((uint8_t*)p) + 1));
    return r;
}

static uint32_t read32(const void* p)
{
    uint32_t r = 0;

    r = (uint32_t)(*((uint8_t*)p));
    r = (r <<  8) | (uint32_t)(*(((uint8_t*)p) + 1));
    r = (r << 16) | (uint32_t)(*(((uint8_t*)p) + 2));
    r = (r << 24) | (uint32_t)(*(((uint8_t*)p) + 3));
    return r;
}

static void write8(const void* p, uint8_t v)
{
    *(uint8_t*)p = v;
}

static void write16(const void* p, uint16_t v)
{
    *(uint8_t*)p = (uint8_t)(v & 0xFF);
    *(((uint8_t*)p) + 1) = (uint8_t)((v >>  8) & 0xFF);
}

static void write32(const void* p, uint32_t v)
{
    *(uint8_t*)p = (uint8_t)(v & 0x00FF);
    *(((uint8_t*)p) + 1) = (uint8_t)((v >>  8) & 0xFF);
    *(((uint8_t*)p) + 2) = (uint8_t)((v >> 16) & 0xFF);
    *(((uint8_t*)p) + 3) = (uint8_t)((v >> 24) & 0xFF);
}

static void* offset_ptr(const void* fdt, size_t offset)
{
    return (void*)(((const uint8_t*)fdt) + offset);
}

nkfdt_tag nkfdt_get_tag(const void* fdt, size_t offset)
{
    return read32(offset_ptr(fdt, offset));
}

enum {
    NKFDT_OK = 0,
    NKFDT_ERROR,
};

#define UNUSED(v) do { (void)v; } while (0)

#define NKFDT_BEGIN_NODE 0x01
#define NKFDT_END_NODE   0x02
#define NKFDT_PROP       0x03
#define NKFDT_NOP        0x04
#define NKFDT_END        0x09

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
    size_t offset;
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
    if (h) { h->totalsize = version; }
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

static inline size_t round4(size_t s)
{
    return ((s + 3) & ~0x03u);
}

void* nkfdt_skip_node(const void* fdt, size_t* nextoffset, const struct fdt_header* h)
{
    uint32_t tag;
    size_t len;
    size_t offset;

    if (nextoffset == NULL) {
        return NULL;
    }
    if (h == NULL) {
        return NULL;
    }
    offset = *nextoffset;

    tag = read32(offset_ptr(fdt, offset));
    if (tag != NKFDT_BEGIN_NODE) {
        return NULL;
    }
    offset += 4;
    len = nks_strnlen((char*)(offset_ptr(fdt, offset)), h->size_dt_struct);
    len = round4(len+1);
    offset += len;

    do {
        tag = read32(offset_ptr(fdt, offset));
        switch (tag) {
        case NKFDT_BEGIN_NODE:
            *nextoffset = offset;
            (void)nkfdt_skip_node(fdt, nextoffset, h);
            offset = *nextoffset;
            break;

        case NKFDT_END_NODE:
        case NKFDT_END:
            offset += 4;
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
        }
    } while ((tag != NKFDT_END_NODE) && (tag != NKFDT_END));

    return offset_ptr(fdt, offset);
}

void* nkfdt_skip_prop(const void* fdt, size_t* nextoffset, const struct fdt_header* h)
{
    uint32_t tag;
    uint32_t len;
    size_t   str_off;
    size_t   offset;

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

char* nkfdt_get_string(const void* fdt, size_t offset, int* strlenp, struct fdt_header* h)
{

}

nkfdt_error nkfdt_get_prop_data(const void* fdt, size_t offset, void** bufp, int* lenp)
{

}

nkfdt_error nkfdt_set_prop_data(const void* fdt, size_t offset, const void* buf, int len)
{

}
