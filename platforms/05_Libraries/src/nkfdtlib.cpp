#include "nkfdtlib.h"

#include <cstdint>

using std::size_t;
using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::uintptr_t;

static int nks_memcmp(const void* data1, const void* data2, size_t n)
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
        }
    }

    return 0;
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

static uint16_t read32(const void* p)
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
    *(uint8_t*)p = (uint8_t)(v & 0x00FF);
    *(((uint8_t*)p) + 1) = (uint8_t)((v >>  8) & 0xFF);
}

static void write32(const void* p, uint32_t v)
{
    *(uint8_t*)p = (uint8_t)(v & 0x00FF);
    *(((uint8_t*)p) + 1) = (uint8_t)((v >>  8) & 0xFF);
    *(((uint8_t*)p) + 2) = (uint8_t)((v >> 16) & 0xFF);
    *(((uint8_t*)p) + 3) = (uint8_t)((v >> 24) & 0xFF);
}

static void* offset_ptr(const void* fdt, int offset)
{
    return (void*)(((const uint8_t*)fdt) + offset);
}

enum {
    NKFDT_OK = 0,
    NKFDT_ERROR,
};

#define NKFDT_BEGIN_NODE 0x01
#define NKFDT_END_NODE   0x02
#define NKFDT_PROP       0x03
#define NKFDT_NOP        0x04
#define NKFDT_END        0x09

nkfdt_error nkfdt_check_header(const void* fdt)
{
    if (nks_memcmp("\xD0\x0D\xFE\xED", fdt, 4) != 0) {
        return NKFDT_ERROR;
    }
    return NKFDT_OK;
}

nkfdt_tag   nkfdt_next_tag(const void* fdt, uint32_t startoffset, uint32_t* nextoffset)
{
    uint32_t offset;

}

nkfdt_error nkfdt_next_node(const void* fdt, uint32_t startoffset, uint32_t* nextoffset)
{

}

nkfdt_error nkfdt_get_property(const void* fdt, uint32_t offset, char** name, int* lenp)
{

}

nkfdt_error nkfdt_set_property(const void* fdt, uint32_t offset, const char* name, const void* val, int len)
{

}
